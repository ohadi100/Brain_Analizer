/**
 * @file  
 * @brief Contains the SupervisionAdapter class and relevant declarations and interfaces for all IDS projects
 */

#pragma once

#include <string>

namespace brain
{
namespace supervision
{
/**
 * @class SupervisionAdapter
 * @brief Adapter class for the supervision entity in the IDS domain
 */
class SupervisionAdapter 
{
public:
    /**
     * @brief   Object constructor
     * 
     * @param   instanceID - IDS name for supervision in the domain
     * @param   supervisionID - IDS id for the report
     */
    SupervisionAdapter(const std::string& instanceID, uint32_t supervisionID);

    /**
     * @brief Object destructor
     */
    ~SupervisionAdapter();

    /**
     * @brief   Initiate communication with supervisor
     * @return  did registration succed
     */
    bool RegisterSupervision();

    /**
     * @brief   Initiate communication with supervisor
     */
    void ReportToSuperviser();

private:
     /* brief   Holder of specific to platform entities - as they need to be referenced for reporting and differ with the platofrm */
    class ClientMembers;

    std::string                    m_instanceID;
    uint32_t                       m_supervisionID;
    std::shared_ptr<ClientMembers> m_clientMembers;
};

} // namespace supervision
} // namespace brain
