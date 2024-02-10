#include <ara-api/inc/ara/phm/phm_client.hpp>
#include <ara-api/inc/ara/phm/health_channel_api.hpp>
#include <ara-api/inc/ara/phm/supervision_entity_api.hpp>

#include "Logger.hpp"
#include "SupervisionAdapter.hpp"

namespace brain 
{
namespace supervision
{
class SupervisionAdapter::ClientMembers 
{
public:
    ClientMembers() = default;

    /**
     * @brief Initialize entities 
     * @param instanceID - IDS instance ID
     */
    void Init(const char* instanceID)
    {
        m_phm_client = std::make_unique<ara::phm::Phm_client>(instanceID);
        m_supervision_entity = std::make_unique<ara::phm::SupervisionEntity>(*m_phm_client);
        m_health_channel = std::make_unique<ara::phm::HealthChannel>(*m_phm_client);
    }

    /**
     * @brief Get the Supervisor object for report [mind that ClientMembers by design will encapsulate the report itself]
     * @return ara::phm::SupervisionEntity* supervision entiry
     */
    ara::phm::SupervisionEntity* GetSupervisor() const
    {
        return m_supervision_entity.get();
    }
private:
    std::unique_ptr<ara::phm::Phm_client>        m_phm_client;
    std::unique_ptr<ara::phm::SupervisionEntity> m_supervision_entity;
    std::unique_ptr<ara::phm::HealthChannel>     m_health_channel;    
};

SupervisionAdapter::SupervisionAdapter(const std::string& instanceID, uint32_t supervisionID)
                        : m_instanceID(instanceID)
                        , m_supervisionID(supervisionID)
                        , m_clientMembers(std::make_unique<ClientMembers>())
{
}

SupervisionAdapter::~SupervisionAdapter() 
{
}

bool SupervisionAdapter::RegisterSupervision()
{
    LOG_INFO << "Initializing Supervision for IDS, instance ID: " << m_instanceID
             << " supervision IDS: " << m_supervisionID << LOG_NOOP;
    m_clientMembers->Init(m_instanceID.c_str());
    return true;
}

void SupervisionAdapter::ReportToSuperviser()
{
    LOG_INFO << "Reporting alive IDS to ICAS Supervisor" << LOG_NOOP;
    m_clientMembers->GetSupervisor()->CheckpointReached(m_supervisionID, m_supervisionID);
}

} // namespace supervision
} // namespace brain 
