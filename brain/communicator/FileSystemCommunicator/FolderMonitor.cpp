#include "FolderMonitor.hpp"
#include "common/utils/logger/Logger.hpp"
#include "common/utils/os/filesystem.hpp"

using common::folder_monitor::FolderMonitor;

FolderMonitor::FolderMonitor(const std::string& filePath, FileAction* fileHandler, uint64_t sleepMs)
  : m_runFlag{false}
  , m_folderPath{filePath}
  , m_action{fileHandler}
  , m_sleepMs{sleepMs}
{
}

FolderMonitor::~FolderMonitor()
{
    stop();
}

bool
FolderMonitor::Init()
{
    if (m_runFlag)
    {
        LOG_DEBUG << "BrainApp::createFolderMonitorThread - folder monitor thread already created" << LOG_NOOP;
        return false;
    }

    m_runFlag = true;

    LOG_DEBUG << "BrainApp::createFolderMonitorThread - Creating folder monitor thread" << LOG_NOOP;

    m_folderMonitorThread = std::thread([this]() {
        LOG_DEBUG << "BrainApp::createFolderMonitorThread - folder monitor thread is starting" << LOG_NOOP;

        std::vector<std::string> fileList;
        while (this->m_runFlag)
        {
            if (common::get_files_in_dir(m_folderPath, fileList) != false)
            {
                /* print all the files and directories within directory */
                for (auto& file : fileList)
                {
                    LOG_DEBUG << "in monitored folder: " << file << LOG_NOOP;
                    if (file.substr(file.find(".") + 1) == "json")
                    {
                        this->m_action->HandleFileAction(this->m_folderPath + file);
                    }
                }
            }

            fileList.clear();
            m_folderMonitorSleeper.SleepMilliseconds(m_sleepMs);
        }
    });

    return true;
}

void
FolderMonitor::stop()
{
    m_runFlag = false;

    m_folderMonitorSleeper.WakeUp();

    if (m_folderMonitorThread.joinable())
    {
        m_folderMonitorThread.join();
    }
}