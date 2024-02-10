/**
 * @file  
 * @brief Contains the ExecutionReporter class and relevant declarations and interfaces for all IDS projects
 */

#pragma once

#include <memory>

namespace brain
{
    namespace execution_reporter
    {
        class ExecutionReporter
        {
            public:                
            /**
             * @brief Ctor for ExecutionReporter class
             */
            ExecutionReporter();

            /**
             * @brief Dtor for ExecutionReporter class
             */
            ~ExecutionReporter();

            /**
             * @brief Report IDS Started to the domain
             * @return did operation had success
            */
            bool ReportIdsStart();

            /**
             * @brief Report IDS Ended operation to the domain
             * @return did operation had success
            */
            bool ReportIdsTearDown();

            private:

            struct ExecClient;

            std::unique_ptr<ExecClient> m_execClient;
        };     
    }
}
