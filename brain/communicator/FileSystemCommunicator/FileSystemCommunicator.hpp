/**
 * @file
 * @brief     The SomeIPCommunicator is a communicator class for SOME/IP
 */
#ifndef FILE_SYSTEM_COMMUNICATOR_HPP
#define FILE_SYSTEM_COMMUNICATOR_HPP

#include <memory>
#include <unordered_map>
#include <vector>

#include "FileAction.hpp"
#include "FolderMonitor.hpp"
#include "SensorGenerator.hpp"
#include "brain/engines/Engine.hpp"

namespace communicator
{
namespace fileSystemComm
{

class FileSystemCommunicator : public common::file_action::FileAction
{
public:
    using DiagnosticsManagerPtr = brain::diagnostics::DiagnosticsManagerInterface::Pointer;

    explicit FileSystemCommunicator(std::vector<std::shared_ptr<brain::engines::Engine>> const& generator,
                                    DiagnosticsManagerPtr                                       diagManager);
    virtual ~FileSystemCommunicator();

    /**
     * @brief    default copy constructor
     */
    FileSystemCommunicator(const FileSystemCommunicator& other) = delete;

    /**
     * @brief    default move constructor
     */
    FileSystemCommunicator(FileSystemCommunicator&& other) = delete;

    /**
     * @brief    default copy assignment operator
     */
    FileSystemCommunicator& operator=(FileSystemCommunicator const&) = delete;

    /**
     * @brief   default move assignment operator
     */
    FileSystemCommunicator& operator=(FileSystemCommunicator&&) = delete;

    void InitService();
    void StopService();

    bool HandleFileAction(const std::string& filePath) override;

private:
    std::unique_ptr<common::folder_monitor::FolderMonitor> m_folderMonitor;
    common::sensor_genarotor::SensorGenerator              m_generator;
};
}  // namespace fileSystemComm
}  // namespace communicator


#endif  // FILE_SYSTEM_COMMUNICATOR_HPP