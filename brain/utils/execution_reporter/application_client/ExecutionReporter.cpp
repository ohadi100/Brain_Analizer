#include "../ExecutionReporter.hpp"
#include <ara/exec/application_client.hpp>

namespace brain
{
namespace execution_reporter
{

struct ExecutionReporter::ExecClient
{
    ara::exec::ApplicationClient client;
};

ExecutionReporter::ExecutionReporter(): m_execClient(std::make_unique<ExecutionReporter::ExecClient>())
{
}

ExecutionReporter::~ExecutionReporter() = default; // Important to make Dtor in C file after ExecClient type is complete


bool ExecutionReporter::ReportIdsStart()
{   
    m_execClient->client.ReportApplicationState(ara::exec::ApplicationState::kRunning);
    return true;
}

bool ExecutionReporter::ReportIdsTearDown()
{
    m_execClient->client.ReportApplicationState(ara::exec::ApplicationState::kTerminating);
    return true;
}

} // namespace execution_reporter
} // namespace brain
