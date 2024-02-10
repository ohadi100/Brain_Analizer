# Place here all the paths that all projects use

set(BRAIN_INCLUDE_PATHS
    ${CMAKE_CURRENT_LIST_DIR} # Adding the root dir to adjust to legacy implementation of full path includes
    ${CMAKE_CURRENT_LIST_DIR}/app
    ${CMAKE_CURRENT_LIST_DIR}/main
    ${CMAKE_CURRENT_LIST_DIR}/main/Base
    ${CMAKE_CURRENT_LIST_DIR}/communicator
    ${CMAKE_CURRENT_LIST_DIR}/communicator/periodic
    ${CMAKE_CURRENT_LIST_DIR}/config
    ${CMAKE_CURRENT_LIST_DIR}/diagnostics/interface
    ${CMAKE_CURRENT_LIST_DIR}/engines
    ${CMAKE_CURRENT_LIST_DIR}/engines/serializer
    ${CMAKE_CURRENT_LIST_DIR}/engines/dispatcher
    ${CMAKE_CURRENT_LIST_DIR}/security_events
    ${CMAKE_CURRENT_LIST_DIR}/events
    ${CMAKE_CURRENT_LIST_DIR}/histograms
    ${CMAKE_CURRENT_LIST_DIR}/messageRepository
    ${CMAKE_CURRENT_LIST_DIR}/messageRepository/interface
    ${CMAKE_CURRENT_LIST_DIR}/noise_filter
    ${CMAKE_CURRENT_LIST_DIR}/noise_filter/event_noise_filter
    ${CMAKE_CURRENT_LIST_DIR}/noise_filter/sensor_noise_filter
    ${CMAKE_CURRENT_LIST_DIR}/sender
    ${CMAKE_CURRENT_LIST_DIR}/sender/publishers/interface
    ${CMAKE_CURRENT_LIST_DIR}/sender/publishers/GDC_12
    ${CMAKE_CURRENT_LIST_DIR}/sender/publishers/GDC_20
    ${CMAKE_CURRENT_LIST_DIR}/sender/publishers/http_publisher
    ${CMAKE_CURRENT_LIST_DIR}/sender/publishers/ids_proxy_someip
    ${CMAKE_CURRENT_LIST_DIR}/sender/publishers/utils/message_size_check
    ${CMAKE_CURRENT_LIST_DIR}/sensor_data
    ${CMAKE_CURRENT_LIST_DIR}/utils/execution_reporter
    ${CMAKE_CURRENT_LIST_DIR}/utils/power_state_adapter
    ${CMAKE_CURRENT_LIST_DIR}/utils/supervision_adapter
    ${CMAKE_CURRENT_LIST_DIR}/utils/log_handlers
    ${CMAKE_CURRENT_LIST_DIR}/utils/ipv6Address # ToDo - move to common
    ${CMAKE_CURRENT_LIST_DIR}/utils/nanopb # ToDO - move to ext
    ${CMAKE_CURRENT_LIST_DIR}/utils/vehicle_data
)
