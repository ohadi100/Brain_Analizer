#include "CanCommunicator.hpp"
#include "Logger.hpp"
#include "brain/canPdu/CanPduData.hpp"

#include <string.h>

using brain::brain_communicator::can_communicator::CanCommunicator;


constexpr char CanCommunicator::INTERFACE_NAME[];

CanCommunicator::CanCommunicator(Communicator::SensorDataQueuesManagerPtr queuesManager)
  : m_activatedOnce(false)
  , m_terminationFlag(false)
  , m_socket(new RawSocket(INTERFACE_NAME, 0x08FFU))
  , m_thread(nullptr)
  , m_queuesManager(queuesManager)

{
    if (nullptr == m_socket)
    {
        LOG_ERROR << "Failed to create CAN socket" << LOG_NOOP;
        KillCommunication();
    }

    LOG_INFO << "CAN communicator created" << LOG_NOOP;

    m_communicatorId = CommunicatorId::CAN;
}

CanCommunicator::~CanCommunicator()
{
    KillCommunication();
}

void
CanCommunicator::Start()
{
    // Note: doing this inside the thread itself would be a race condition with stopThread.
    m_terminationFlag.store(false);

    if (nullptr == m_thread)
    {
        m_thread = new std::thread(&CanCommunicator::CanThreadhandler, this);
        if (nullptr == m_thread)
        {
            LOG_ERROR << "Failed to run CAN thread" << LOG_NOOP;
            KillCommunication();
        }
    }

    LOG_INFO << "CAN communicator init success" << LOG_NOOP;
}

void
CanCommunicator::Stop()
{
    KillCommunication();
}


void
CanCommunicator::CanThreadhandler()
{
    bool res = false;

    if ((nullptr != m_socket))
    {
        if (false == m_socket->Connect())
        {
            LOG_ERROR << "connect to CanPdu socket failed" << LOG_NOOP;
            return;
        }
        else
        {
            LOG_INFO << "SELF_TEST: connected to CanPdu socket" << LOG_NOOP;
        }
    }
    else
    {
        LOG_ERROR << "CAN socket was not created" << LOG_NOOP;
        return;
    }

    while (m_terminationFlag == false)
    {
        if (!m_socket->IsConnected())
        {
            LOG_ERROR << "Can socket disconected, stoping can thread loop" << LOG_NOOP;
            break;
        }

        char     buffer[brain::can_pdu::CanPduData::ETH_TNL_MAX_BUFFER_LENGTH];
        char*    pBuffer = buffer;
        uint32_t buflen  = 0U;  // for PcapSocket or RX RING

        res = m_socket->Receive(&pBuffer, &buflen, TIME_INTERVAL);
        if (false == res)
        {
            LOG_ERROR << "Failed to recive data from socket" << LOG_NOOP;
        }

        LOG_DEBUG << "recive data from socket with size:" << buflen << LOG_NOOP;

        if (buflen > brain::can_pdu::CanPduData::ETH_TNL_MAX_BUFFER_LENGTH)
        {
            LOG_ERROR << "buffer length: " << buflen << " is bigger then max length"
                      << brain::can_pdu::CanPduData::ETH_TNL_MAX_BUFFER_LENGTH << LOG_NOOP;
            continue;
        }


        if (buflen < sizeof(brain::can_pdu::IdsFrame))
        {
            LOG_ERROR << "Invalid Can Pdu data size: " << buflen << LOG_NOOP;
            continue;
        }

        brain::can_pdu::IdsFrame* frame = reinterpret_cast<brain::can_pdu::IdsFrame*>(pBuffer);

        // Checking ethhdr and ethtnlhdr information
        if (frame->ethhdr.h_proto != brain::can_pdu::ETH_TNL_PROTO)
        {
            LOG_ERROR << "Invalid Eth header proto recived: " << std::hex << (unsigned)frame->ethhdr.h_proto
                      << " expected: " << std::hex << brain::can_pdu::ETH_TNL_PROTO << LOG_NOOP;
            continue;
        }

        if (frame->ethtnlhdr.frameId != brain::can_pdu::ETH_TNL_IDS_FRAME_ID_R7
            && frame->ethtnlhdr.frameId != brain::can_pdu::ETH_TNL_IDS_FRAME_ID_CR)
        {
            LOG_ERROR << "Invalid EthTnl header frameId recived: " << std::hex << (unsigned)frame->ethtnlhdr.frameId
                      << " expected: " << std::hex << brain::can_pdu::ETH_TNL_IDS_FRAME_ID_R7 << " or: " << std::hex
                      << brain::can_pdu::ETH_TNL_IDS_FRAME_ID_CR << LOG_NOOP;
            continue;
        }

        std::unique_ptr<brain::can_pdu::CanPduData> canData = std::make_unique<brain::can_pdu::CanPduData>();
        memcpy(canData->m_buffer, pBuffer, buflen);
        canData->m_bufferSize = buflen;
        canData->SetTag(common::sensor_data::SensorDataTag::SD_CAN_PDU_EVENT);

        m_queuesManager->AddNotificationToQueue(std::move(canData));
    }
}

void
CanCommunicator::StopCanThread() noexcept
{
    LOG_INFO << "CanCommunicator::StopCanThread - Starting CAN handler thread termination" << LOG_NOOP;

    m_terminationFlag.store(true);

    if (m_thread != nullptr)
    {
        LOG_DEBUG << "CanCommunicator::StopCanThread - Running join on CAN handler thread" << LOG_NOOP;

        if (m_thread->joinable())
        {
            m_thread->join();
        }

        delete m_thread;
        m_thread = nullptr;
    }

    LOG_INFO << "Stopped the handler thread" << LOG_NOOP;
}

void
CanCommunicator::KillCommunication() noexcept
{
    StopCanThread();

    if (nullptr != m_socket)
    {
        if (true == m_socket->IsConnected())
        {
            m_socket->Close();
        }
    }
}