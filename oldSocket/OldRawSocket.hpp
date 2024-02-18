/**
 * @file      RawSocket.hpp
 * @brief     A class that deals with opening and reading from a Raw Socket

 */
#pragma once

#include <string>
#include <thread>
#include "common/ids_socket/BaseSocket.hpp"

#define MAC_LEN 6

namespace common
{
    namespace ids_socket
    {

        /**
         * @class   RawSocket
         * @brief   The RawSocket class is implement the IBaseSocket interface.
                    The RawSocket class implement the all abstract class of IBaseSocket.
                    It allocate socket, bind it and wait for a connection.
                    It also wait to receive packets and data messages.
         */
        class RawSocket : public IBaseSocket
        {

        public:
            /**
             * @fn      RawSocket(std::string const ifName, int ethType, const unsigned char * mrAddres)
             * @brief   Constructor
             * @param   none
             * @return  none
             */
            RawSocket(const std::string& ifName, const int& ethType);

            /**
             * @fn      virtual ~RawSocket()
             * @brief   Destructor
             * @param   none
             * @return  none
             */
            virtual ~RawSocket();

            /**
             * @fn      bool Connect()
             * @brief   Connect to the Unix Domain Socket. The socket is changed to non-blocking mode
             * @param   none
             * @return  bool - true if successful, false otherwise
             */
            bool Connect();

            /**
             * @fn      bool Receive(char * const buffer, uint32_t const bufLen, uint32_t const timeout)
             * @brief   Allocates a new buffer for the received data. Should be fread by the user of this function
             * @param   char * buffer as outval buffer
             * @return  bool - true if successful, false otherwise
             */
            bool Receive(char *const buffer, uint32_t const bufLen, uint32_t const timeout);

            /**
             * @fn      bool Receive(char ** const buffer, uint32_t * const bufLen, uint32_t const timeout)
             * @brief   Receive data and allocate a buffer. The buffer is valid until next call to Receive or Close
             * @param   char ** buffer as outval buffer
             * @return  true if successful, false otherwise
             */
            bool Receive(char **const buffer, uint32_t *const bufLen, uint32_t const timeout);

            /**
             * @fn      bool Receive(char ** const buffer, uint32_t * const bufLen)
             * @brief   Receive data and allocate a buffer. The buffer is valid until next call to Receive or Close
             * @param   char ** buffer as outval buffer
             * @return  true if successful, false otherwise
             */
            bool Receive(char **const buffer, uint32_t *const bufLen);

            /**
             * @fn      bool Close()
             * @brief   Close the socket
             * @param   none
             * @return  none
             */
            void Close();

            /**
             * @fn      char * GetBufferData(char * buffer)
             * @brief   return the right offset of the buffer data.
             * @param   char * buffer the original pointer.
             * @param   uint32_t& buflen - outparam - the current buflen
             * @param   uint32_t const offset - the offset to move
             * @return  char * the pointer to the right offset.
             */
            char *GetBufferData(char *buffer, uint32_t &buflen, uint32_t const offset);

            /**
             * @fn      bool IsConnected()
             * @brief   return if socket connected or not.
             * @return  bool true if connected, false if not.
             */
            bool IsConnected();

        private:
            struct tpacket_block_desc *getBlockPtr(void) noexcept;
            void flushBlock(void);

            std::string m_ifName;
            int m_ethType;
            const unsigned char m_mrAddress[MAC_LEN] = {0x33, 0x33, 0x00, 0x00, 0x00, 0x10};
            int m_rawsockfd;

            std::string const m_fileName;
            bool m_isConnected;

            uint8_t *m_mmap;            /* RX ring memory map */
            unsigned int m_curBlock;    /* Block index inside the ring that we currently read from */
            unsigned int m_curFrames;   /* Total frames inside the block that we currently read from */
            unsigned int m_curFrameIdx; /* Next frame index inside the block that we currently read from */
            unsigned int m_curOffset;   /* Offset of next frame inside the block that we currently read from */
        };

    } // namespace ids_socket
} // namespace common
