/**
 * @file
 * @brief     This file contains functions for file system.
 .
 */
#ifndef FILE_ACTION_HPP
#define FILE_ACTION_HPP

#include <string>
#include <thread>
#include <functional>

namespace common
{
    namespace file_action
    {
        class FileAction
        {
        public:
            FileAction() = default;
            
            virtual ~FileAction() = default;

            /**
             * @brief    default copy constructor
             */
            FileAction(const FileAction& other) = delete;

            /**
             * @brief    default move constructor
             */
            FileAction(FileAction&& other) = delete;

            /**
             * @brief    default copy assignment operator
             */
            FileAction& operator=(FileAction const&) = delete;

            /**
             * @brief   default move assignment operator
             */
            FileAction& operator=(FileAction&&) = delete;

            virtual bool HandleFileAction(const std::string &filePath) = 0;
        };

    } // namespace file_action

} // namespace common_ids

#endif // FILE_ACTION_HPP