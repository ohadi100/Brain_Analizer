#include "FileSystemCommunicator.hpp"
#include "common/utils/logger/Logger.hpp"

#include <fstream>
#include <sstream>

using brain::engines::Engine;
using common::folder_monitor::FolderMonitor;
using communicator::fileSystemComm::FileSystemCommunicator;

FileSystemCommunicator::FileSystemCommunicator(std::vector<std::shared_ptr<Engine>> const& generator,
                                               DiagnosticsManagerPtr                       diagManager)
  : m_generator{generator, diagManager}
{
}

FileSystemCommunicator::~FileSystemCommunicator()
{
    StopService();
}

void
FileSystemCommunicator::InitService()
{
    m_folderMonitor = std::make_unique<FolderMonitor>("/run/machine_tmp/", this);
    m_folderMonitor->Init();
}

void
FileSystemCommunicator::StopService()
{
    if (m_folderMonitor)
    {
        m_folderMonitor->stop();
    }
}

bool
FileSystemCommunicator::HandleFileAction(const std::string& filePath)
{
    LOG_DEBUG << "received file = " << filePath << LOG_NOOP;

    std::ifstream     t(filePath);
    std::stringstream buffer;
    buffer << t.rdbuf();

    t.close();

    // remove parsed file
    int status = std::remove(filePath.c_str());

    if (0 != status)
    {
        LOG_INFO << "error deleting file: " << filePath << " with error " << status << LOG_NOOP;
    }

    return m_generator.ParseAndGenerateSensor(buffer.str());
}