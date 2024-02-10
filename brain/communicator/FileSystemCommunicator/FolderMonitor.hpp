/**
 * @file
 * @brief     This file contains functions for file system.
 */
#ifndef FOLDER_MONITOR_HPP
#define FOLDER_MONITOR_HPP

#include "common/utils/conditionalSleep/ConditionalSleep.hpp"
#include "FileAction.hpp"

#include <functional>
#include <string>
#include <thread>

using common::file_action::FileAction;

namespace common
{
namespace folder_monitor
{

static constexpr uint64_t folder_monitor_cycle_time_ms{5000U};

class FolderMonitor
{
public:
    explicit FolderMonitor(const std::string& filePath, FileAction* fileHandler, uint64_t sleepMs = folder_monitor_cycle_time_ms);
    
    ~FolderMonitor();

    /**
     * @brief    default copy constructor
     */
    FolderMonitor(const FolderMonitor& other) = delete;

    /**
     * @brief    default move constructor
     */
    FolderMonitor(FolderMonitor&& other) = default;

    /**
     * @brief    default copy assignment operator
     */
    FolderMonitor& operator=(FolderMonitor const&) = delete;

    /**
     * @brief   default move assignment operator
     */
    FolderMonitor& operator=(FolderMonitor&&) = default;

    bool Init();
    void stop();

private:
    bool        m_runFlag{};
    std::string m_folderPath;
    FileAction* m_action{nullptr};

    std::thread              m_folderMonitorThread;
    common::ConditionalSleep m_folderMonitorSleeper;
    uint64_t                 m_sleepMs{0U};
};

}  // namespace folder_monitor

}  // namespace common

#endif  // FOLDER_MONITOR_HPP