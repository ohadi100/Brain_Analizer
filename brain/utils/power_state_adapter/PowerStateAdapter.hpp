#pragma once

#include <functional>
#include <memory>
#include <string>

namespace brain
{
namespace power_state
{

class PowerStateAdapter
{
public:
    using SwitchStateCallBack = std::function<bool(const std::string&)>;

    /**
     * @brief   Constructor
     * @param   switchStateCb - callback to be called on switch to new state
     * @param   idsComponentName - component name in the domain
     */
    PowerStateAdapter(SwitchStateCallBack switchStateCb, std::string const& idsComponentName);

    /**
     * @brief   Initiate communication with power management, register call back for the switch call
     */
    void Register();

private:
    SwitchStateCallBack m_switchStateCb;
    std::string         m_idsComponentName;
};

}  // namespace power_state
}  // namespace brain
