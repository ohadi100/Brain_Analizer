/**
 * @file
 * @brief This file contains the constants of brain configuration.
 *        For more information you can consult the confluenca page
 * https://devstack.vwgroup.com/confluence/display/IDSVW/Configuration+file+for+PPE
 */
#ifndef BRAIN_CONFIG_CONSTANTS_HPP
#define BRAIN_CONFIG_CONSTANTS_HPP

#include <common/utils/types/string.hpp>  // for common::types::StringKey
#include <string>

namespace brain
{

// parasoft-begin-suppress AUTOSAR-M3_4_1-b "This is current approach to have all the names of configuration items in
// one file"
namespace config_keys
{
using ConfigKeyType                                        = common::types::StringKey const;
static constexpr char BRAIN_NOTIFICATIONS_PLAYER_ENABLED[] = "brain_notifications_player_enabled";
static constexpr char BRAIN_NOTIFICATIONS_PLAYER_FILE[]    = "brain_notifications_player_file";

/**
 * @brief Timestamp of the creation of previous periodic IDS statistics.
 */
static constexpr char PERIODIC_STATISTICS_PREVIOUS_TS[] = "periodic_statistics_previous_ts";

/**
 * @brief Amount of time between generations of periodic statistics.
 */
static constexpr char IDS_PERIODIC_STATISTICS_SEND_INTERVAL_SECS[] = "ids_periodic_statistics_send_interval_secs";

/**
 * @brief The time in the day in which the credit is re-charged.
 */
static constexpr char CREDIT_RECHARGE_TIME_IN_DAY[] = "credit_recharge_time_in_day";

/**
 * @brief Amount of credit in bytes.
 */
static constexpr char CREDIT_DAY_LIMIT_BYTES[] = "credit_day_limit_bytes";

static constexpr char SENDER_GRACE_PERIOD[] = "sender_grace_period";
static constexpr char VEHICLE_TYPE[]        = "vehicleType";
static constexpr char VEHICLE_GUID[]        = "vehicleGuid";

static constexpr char UNLIMITED_CREDIT_FOR_REPORT[] = "unlimited_credit_for_report";

/**
 * @brief Maximum waiting time for keep alive received from the various sensors before sending alert.
 */
static constexpr char KEEP_ALIVE_TIMEOUT_PERIOD[] = "ids_keep_alive_timeout_period";

/**
 * @briefrate threshold used in token bucket algorithm when computing the process crash rate
 */
static constexpr char PROCESS_CRASH_RATE_ALERT_TOKEN_BUCKET_THRESHOLD[]
    = "process_crash_rate_alert_token_bucket_threshold";

/**
 * @brief Rate burst used in token bucket algorithm when computing the process crash rate
 */
static constexpr char PROCESS_CRASH_RATE_ALERT_TOKEN_BUCKET_BURST[] = "process_crash_rate_alert_token_bucket_burst";

/**
 * @brief Rate threshold used in token bucket algorithm when computing the aggregate crash rate
 */
static constexpr char AGGREGATE_CRASH_RATE_ALERT_TOKEN_BUCKET_THRESHOLD[]
    = "aggregate_crash_rate_alert_token_bucket_threshold";

/**
 * @brief Rate burst used in token bucket algorithm when computing the aggregate crash rate
 */
static constexpr char AGGREGATE_CRASH_RATE_ALERT_TOKEN_BUCKET_BURST[] = "aggregate_crash_rate_alert_token_bucket_burst";

/**
 * @brief Minimum/maximum waiting time for next retransmission on http response like 503/504.
 */
static constexpr char BACKEND_RESPONSE_RETRANS_MIN_SEC[] = "backend_response_retrans_min_sec";
static constexpr char BACKEND_RESPONSE_RETRANS_MAX_SEC[] = "backend_response_retrans_max_sec";
/**
 * @brief maximum repetition to BackEnd on http response like 503/504.
 */
static constexpr char BACKEND_RESPONSE_RETRANS_MAX_RETRANS[] = "backend_response_retrans_max_retrans";

/**
 * @brief Enable backend report debugging by dumping the entire report in the logs
 * @note default value: false
 * @note variable type: bool
 */
static constexpr char ENABLE_BACKEND_REPORT_DEBUGGING[] = "enable_backend_report_debugging";

/**
 * @brief UDS path.
 * @note default value: Empty string
 * @note variable type: string
 */
static constexpr char UDS_PATH[] = "uds_path";

/**
 * @brief UDS path simulation.
 * @note default value: Empty string
 * @note variable type: string
 */
static constexpr char UDS_PATH_SIMULATION[] = "uds_path_simulation";

/**
 * @brief UDS communicator status.
 * @note default value: true
 * @note variable type: string
 */
static constexpr char UDS_COMMUNICATOR_STATUS[] = "uds_communicator_status";

/**
 * @brief GSDP communicator status.
 * @note default value: true
 * @note variable type: string
 */
static constexpr char GSDP_COMMUNICATOR_STATUS[] = "gsdp_communicator_status";

/**
 * @brief SE small communicator status.
 * @note default value: true
 * @note variable type: string
 */
static constexpr char SE_SMALL_COMMUNICATOR_STATUS[] = "se_small_communicator_status";

/**
 * @brief SE normal communicator status.
 * @note default value: true
 * @note variable type: string
 */
static constexpr char SE_NORMAL_COMMUNICATOR_STATUS[] = "se_normal_communicator_status";

/**
 * @brief SACID communicator status.
 * @note default value: true
 * @note variable type: string
 */
static constexpr char SACID_COMMUNICATOR_STATUS[] = "sacid_communicator_status";

/**
 * @brief [optional] List of instances ids for the SecurityEventNormal communicator to register
 * @note default value: empty list - in absence of the field, returned empty vector to indicate
 * all instances (no MVP version)
 * @note variable type: vector
 */
static constexpr char COMM_SE_NORMAL_INSTANCES[] = "comm_se_normal_instances";

/**
 * @brief [optional] List of instances ids for the SecurityEventSmall communicator to register
 * @note default value: empty list - in absence of the field, returned empty vector to indicate
 * all instances (no MVP version)
 * @note variable type: vector
 */
static constexpr char COMM_SE_SMALL_INSTANCES[] = "comm_se_small_instances";

/**
 * @brief Indicator which says if the PM should be used for storing and reading the events
 *         if false - they will be read directly from ram
 * @note default value: True - meaning the writing in readin
 * @note variable type: bool
 */
static constexpr char EVENT_STORAGE_PM_STATUS[] = "event_storage_pm_status";

/**
 * @brief Counter logger  status.
 * @note default value: true
 * @note variable type: string
 */
static constexpr char COUNTER_LOGGER_STATUS[] = "counter_logger_status";

/**
 * @brief When status is set to "true", even in debug log level the logs are first written into a queue before being
 * printed in a separate thread
 * @note default value: true
 * @note variable type: string
 */
static constexpr char ENABLE_QUEUE_LOG_IN_DEBUG_LEVEL_STATUS[] = "enable_queue_log_in_debug_level_status";

/**
 * @brief A bitmask to indicate the Log levels to enable. order of bits: 6|5|4|3|2|1|0 <=>
 * VERBOSE|DEBUG|INFO|WARNING|ERROR|FATAL|CLEAN example: bitmask = 0x14 => (0001|0100) => enable only INFO and ERROR
 * logs
 * @note default value: 0x10 - INFO LEVEL without ERR and WAR need to change in next version!
 * @note variable type: string
 */
static constexpr char LOG_LEVEL_BM[] = "log_level_bitmask";

/**
 * @brief The interval in milliseconds used to suppress repeated error or warning logs
 * The log is identified by the source file path and line number.
 * @note default value: 0 - no log suppression
 * @note variable type: number
 */
static constexpr char REPEATED_LOG_SUPRESSION_INTERVAL_MS[] = "repeated_log_supression_interval_ms";

/**
 * @brief The rate, expressed in logs/sec, at which the logs are printed when using a queue
 * with a secondary logging thread. If set to 0, then the logs are printed without rate
 * limitation (as fast as possible).
 * @note default value: 10
 * @note variable type: number
 */
static constexpr char LOG_PRINT_RATE_HZ[] = "log_print_rate_hz";

/**
 * @brief The burst is the total capacity of the token bucket used for log rate limitation.
 * The log burst must be greater or equal than the log rate.
 * @note default value: 10
 * @note variable type: number
 */
static constexpr char LOG_PRINT_BURST[] = "log_print_burst";

/**
 * @brief The period, expressed in milliseconds, after which the token bucket is refilled,
 * if needed. The token refill period cannot be 0.
 * @note default value: 10
 * @note variable type: number
 */
static constexpr char LOG_TOKEN_REFILL_PERIOD_MS[] = "log_token_refill_period_ms";

/**
 * @brief Amount of time between generations of periodic reports.
 * @note variable type: string
 */
static constexpr char COUNTER_LOGGER_INTERVAL_SECS[] = "counter_logger_interval_secs";

/**
 * @brief Number of SDs to accumulate before forwarding handling from the gsdp communicator to the notification handler
 * @note variable type: number
 */
static constexpr char GSDP_FLUSH_THRESHOLD[] = "gsdp_flush_threshold";

/**
 * @brief The maximum size if the string type in a JSON object received from DHM
 * @note default value: 1024
 * @note variable type: number
 */
static constexpr char MAXIMUM_SIZE_STRING_TYPE[] = "maximum_size_string_type";

/**
 * @brief Number of SDs to accumulate before forwarding handling from the security event small communciator to the
 * notification handler
 * @note variable type: number
 */
static constexpr char SECURITY_EVENT_SMALL_FLUSH_THRESHOLD[] = "security_event_small_flush_threshold";

/**
 * @brief Number of SDs to accumulate before forwarding handling from the security event communciator to the
 * notification handler
 * @note variable type: number
 */
static constexpr char SECURITY_EVENT_NORMAL_FLUSH_THRESHOLD[] = "security_event_normal_flush_threshold";

/**
 * @brief Interval of polling SOME/IP field samples, measured in seconds. Defaults to 1
 * @note variable type: number
 */
static constexpr char SOMEIP_SAMPLE_HANDLING_INTERVAL[] = "someip_sample_handling_interval";

/**
 * @brief Number of seconds after which the SACID report is generated. Aggregate the counters over time period of
 * 60 minutes of Clamp-15-ON state (IDS-Core running time).
 * Default value 3600U
 * @note variable type: uint32_t
 */
static constexpr char SACID_REPORT_GENERATION_PERIOD[] = "SACID_report_generation_period";

/**
 * @brief The max size of the table is 100 rows with the key as defined in GROUP_BY.
 * All additonal counter keys will be ignored and an error printed in the log.
 * Default value 100U
 * @note variable type: uint32_t
 */
static constexpr char SACID_MAX_SIZE_OF_TABLE[] = "SACID_max_size_of_table";

/**
 * @brief The variable to define HCP5 switch traffic monitoring token bucket params
 * [0] - rate, [1] - burst
 * Default value [100000000, 20000]
 * @note variable type: vector[uint32_t]
 */
static constexpr char HCP5_SWITCH_TRAFIC_MONITORING_TOKEN_BUCKET_PARAMS[]
    = "hcp5_switch_traffic_monitoring_token_bucket_params";

// Sensor noise filter
static constexpr char QLAH_HOST_SENSOR_NOISE_FILTER_PARAMS[]        = "qlah_host_sensor_noise_filter_params";
static constexpr char QLAH_ETH_SENSOR_NOISE_FILTER_PARAMS[]         = "qlah_eth_sensor_noise_filter_params";
static constexpr char SWPAC_KERNEL_LOG_SENSOR_NOISE_FILTER_PARAMS[] = "swpac_kernel_log_sensor_noise_filter_params";
static constexpr char SWPAC_TLS_ERROR_REPORT_SENSOR_NOISE_FILTER_PARAMS[]
    = "swpac_tls_error_report_sensor_noise_filter_params";
static constexpr char SWPAC_PROCESS_PERFORMANCE_SENSOR_NOISE_FILTER_PARAMS[]
    = "swpac_process_performance_sensor_noise_filter_params";
static constexpr char SECURITY_EVENT_SENSOR_NOISE_FILTER_PARAMS[] = "security_event_sensor_noise_filter_params";
static constexpr char INTELLIGENT_SENSOR_NOISE_FILTER_PARAMS[]    = "intelligent_sensor_noise_filter_params";
static constexpr char SACID_SENSOR_NOISE_FILTER_PARAMS[]          = "sacid_sensor_noise_filter_params";

// Group noise filter
static constexpr char PERIODIC_GROUP_NOISE_FILTER_PARAMS[]        = "periodic_group_noise_filter_params";
static constexpr char QLAH_ETH_GROUP_NOISE_FILTER_PARAMS[]        = "qlah_eth_group_noise_filter_params";
static constexpr char QLAH_HOST_GROUP_NOISE_FILTER_PARAMS[]       = "qlah_host_group_noise_filter_params";
static constexpr char SWPAC_TLS_ERROR_GROUP_NOISE_FILTER_PARAMS[] = "swpac_tls_error_group_noise_filter_params";
static constexpr char SECURITY_EVENT_GROUP_NOISE_FILTER_PARAMS[]  = "security_event_group_noise_filter_params";
static constexpr char INTELLIGENT_GROUP_NOISE_FILTER_PARAMS[]     = "intelligent_group_noise_filter_params";

// Sender WRR weights
static constexpr char SENDER_QUEUE_CRITICAL_PARAMS[]  = "sender_queue_critical_params";
static constexpr char SENDER_QUEUE_IMPORTANT_PARAMS[] = "sender_queue_important_params";
static constexpr char SENDER_QUEUE_NORMAL_PARAMS[]    = "sender_queue_normal_params";
static constexpr char SENDER_QUEUE_LOW_PARAMS[]       = "sender_queue_low_params";

// Event priorities (0=critical, 3=low)
static constexpr char EVENT_PRIORITY_PERIODIC_STATISTICS[] = "event_priority_periodic_statistics";
static constexpr char EVENT_PRIORITY_DHM[]                 = "event_priority_DHM";
static constexpr char EVENT_PRIORITY_QLAH_ETH[]            = "event_priority_qlah_eth";
static constexpr char EVENT_PRIORITY_QLAH_HOST[]           = "event_priority_qlah_host";
static constexpr char EVENT_PRIORITY_SECURITY_EVENT[]      = "event_priority_security_event";
static constexpr char EVENT_PRIORITY_INTELLIGENT_SENSOR[]  = "event_priority_intelligent_sensor";
static constexpr char EVENT_PRIORITY_SACID_CAN_EVENT[]     = "event_priority_sacid_can_event";

// NAT table
static constexpr char MAX_NAT_TABLE_SIZE[] = "max_nat_table_size";

/**
 * @brief SecurityEvents blacklisted event id, SE from this list will not be processed
 * when blacklisting the security event ids, in the json config file please specify it
 * under:     "security_events_blacklist" : [5, 6, 7, 8]
 * keyword. The ID's introduced here shall be decimal numbers, comma separated.
 * @note default value: empty list
 * @note variable type: vector[uint32_t]
 */
static constexpr char SECURITY_EVENTS_BLACKLIST_CONFIG[] = "security_events_blacklist";

/**
 * @brief This is the default alert limit for all the alerts that don't have a custom limit.
 * The limit is reseted when the periodic report is sent
 * @note default value: 100U
 * @note variable type: uint32_t
 */
static constexpr char DEFAULT_ALERT_LIMIT[] = "default_alert_limit";

/**
 * @brief This is the default alert limit for all the alerts that are originated by critical security events
 * @note default value: if key is missing the DEFAULT_ALERT_LIMIT value is used
 * @note variable type: uint32_t
 */
static constexpr char CRITICAL_SECURITY_EVENT_ALERT_DEFAULT_LIMIT[] = "criticalSecurityEventAlert_default_limit";
/**
 * @brief This is the alert limit for all the alerts that are originated by unknown Event IDs.
 * @note default value: if key is missing the DEFAULT_ALERT_LIMIT value is used
 * @note variable type: uint32_t
 */
static constexpr char UNKNOWN_EVENT_ID_ALERT_LIMIT[] = "unknownEventIdAlert_limit";
/**
 * @brief If the number of unknown Event IDs exceed an unknownEventIdAlert_max_number, those that exceed shall be
 * dropped an counted.
 * @note default value: if key is missing the DEFAULT_ALERT_LIMIT value is used
 * @note variable type: uint32_t
 */
static constexpr char UNKNOWN_EVENT_ID_ALERT_MAX_NUMBER[] = "unknownEventIdAlert_max_number";

/**
 * @brief Each element in the list shall be comprised of the following fields: [idsMInstanceID, sensorInstanceID,
 * eventDefinitionId, limit].
 * @note default value: if key is missing the DEFAULT_ALERT_LIMIT value is used
 * @note variable type: std::vector<std:vector<uint32_t>>
 */
static constexpr char CRITICAL_SECURITY_EVENT_ALERT_LIMITS_PER_KEY[] = "criticalSecurityEventAlert_limits_per_key";

/**
 * @brief This is the alert limitation for the Os log Kernel Panic dhm incident
 * @note default value: if key is missing the DEFAULT_ALERT_LIMIT value is used
 * @note variable type: uint32_t
 */
static constexpr char DHM_OS_LOG_REGEX_KERNEL_PANIC_ALERT_LIMIT[] = "dhmOsLogRegexKernelPanicAlert_limit";

/**
 * @brief This is the alert limitation for the TLS Error Reports dhm incident
 * @note default value: if key is missing the DEFAULT_ALERT_LIMIT value is used
 * @note variable type: uint32_t
 */
static constexpr char DHM_TER_INCIDENT_ALERT_LIMIT[] = "dhmTerIncidentAlert_limit";

/**
 * @brief This is the alert limitation for maximum allowed size of the string type DHM incident
 * @note default value: if key is missing the DEFAULT_ALERT_LIMIT value is used
 * @note variable type: uint32_t
 */
static constexpr char DHM_INCIDENT_STRING_SIZE_ALERT_LIMIT[] = "dhmIncidentStringSizeAlert_limit";

/**
 * @brief This is the alert limitation for DHM unknown constraint id
 * @note default value: if key is missing the DEFAULT_ALERT_LIMIT value is used
 * @note variable type: uint32_t
 */
static constexpr char DHM_Incident_With_Unknown_Constraint_Id_Alert_Limit[]
    = "dhm_incident_with_unknown_constraint_id_alert_limit";

/**
 * @brief If the number of unknown Constraint IDs alerts exceed this limit, those that exceed shall be dropped an
 * counted.
 * @note default value: if key is missing the DEFAULT_ALERT_LIMIT value is used
 * @note variable type: uint32_t
 */
static constexpr char DHM_Incident_With_Unknown_Constraint_Id_Alert_Max_Number[]
    = "dhm_incident_with_unknown_constraint_id_alert_max_number";

/**
 * @brief If the number of qlah unknown protocol dropped alerts exceed this limit, those that exceed shall be dropped an
 * counted.
 * @note default value: if key is missing the DEFAULT_ALERT_LIMIT value is used
 * @note variable type: uint32_t
 */
static constexpr char QLAH_Unknown_Protocol_Dropped_Frames_Counter_Alert_Limit[]
    = "qlah_unknown_protocol_dropped_frames_counter_alert_limit";

/**
 * @brief If the number of qlah illegal vlan dropped frames counter alert exceed this limit, those that exceed shall be
 * dropped an counted.
 * @note default value: if key is missing the DEFAULT_ALERT_LIMIT value is used
 * @note variable type: uint32_t
 */
static constexpr char QLAH_ILLEGAL_VLAN_DROP_VALUE_Alert_limit[] = "qlah_illegal_vlan_drop_value_alert_limit";

/**
 * @brief Memory Total size for HCP3 partition SYS in KB
 * @note default value: if key is missing value 256 is used
 * @note variable type: uint32_t
 */
static constexpr char HCP3_HOST_SYS_MEM_TOTAL[] = "HCP3_host_SYS_MemTotal";

/**
 * @brief Memory Total size for HCP3 partition IVI in KB
 * @note default value: if key is missing value 256 is used
 * @note variable type: uint32_t
 */
static constexpr char HCP3_HOST_IVI_MEM_TOTAL[] = "HCP3_host_IVI_MemTotal";

/**
 * @brief Memory Total size for ConMod partition NAD in KB
 * @note default value: if key is missing value 256 is used
 * @note variable type: uint32_t
 */
static constexpr char CONMOD_MEM_TOTAL[] = "ConMod_MemTotal";

/**
 * @brief Memory Total size for HCP4 partition M1, core 0 in KB
 * @note default value: if key is missing value 256 is used
 * @note variable type: uint32_t
 */
static constexpr char HCP4_M1_C0_MEM_TOTAL[] = "HCP4_M1_C0_MemTotal";

/**
 * @brief Memory Total size for HCP4 partition M1, core 1 in KB
 * @note default value: if key is missing value 256 is used
 * @note variable type: uint32_t
 */
static constexpr char HCP4_M1_C1_MEM_TOTAL[] = "HCP4_M1_C1_MemTotal";

/**
 * @brief Memory Total size for HCP4 partition M1, core 2 in KB
 * @note default value: if key is missing value 256 is used
 * @note variable type: uint32_t
 */
static constexpr char HCP4_M1_C2_MEM_TOTAL[] = "HCP4_M1_C2_MemTotal";

/**
 * @brief Memory Total size for HCP4 partition M1, core 3 in KB
 * @note default value: if key is missing value 256 is used
 * @note variable type: uint32_t
 */
static constexpr char HCP4_M1_C3_MEM_TOTAL[] = "HCP4_M1_C3_MemTotal";

/**
 * @brief Memory Total size for HCP4partition M1, core 4 in KB
 * @note default value: if key is missing value 256 is used
 * @note variable type: uint32_t
 */
static constexpr char HCP4_M1_C4_MEM_TOTAL[] = "HCP4_M1_C4_MemTotal";

/**
 * @brief Memory Total size for HCP4 partition M1, core 5 in KB
 * @note default value: if key is missing value 256 is used
 * @note variable type: uint32_t
 */
static constexpr char HCP4_M1_C5_MEM_TOTAL[] = "HCP4_M1_C5_MemTotal";

/**
 * @brief Memory Total size for partition M2_1, core 0 in KB
 * @note default value: if key is missing value 256 is used
 * @note variable type: uint32_t
 */
static constexpr char HCP4_M2_1_C0_MEM_TOTAL[] = "HCP4_M2_1_C0_MemTotal";

/**
 * @brief Memory Total size for HCP4 partition M2_1, core 1 in KB
 * @note default value: if key is missing value 256 is used
 * @note variable type: uint32_t
 */
static constexpr char HCP4_M2_1_C1_MEM_TOTAL[] = "HCP4_M2_1_C1_MemTotal";

/**
 * @brief Memory Total size for HCP4 partition M2_2, core 2 in KB
 * @note default value: if key is missing value 256 is used
 * @note variable type: uint32_t
 */
static constexpr char HCP4_M2_2_C2_MEM_TOTAL[] = "HCP4_M2_2_C2_MemTotal";

/**
 * @brief Memory Total size for HCP4 partition M2_2, core 3 in KB
 * @note default value: if key is missing value 256 is used
 * @note variable type: uint32_t
 */
static constexpr char HCP4_M2_2_C3_MEM_TOTAL[] = "HCP4_M2_2_C3_MemTotal";

/**
 * @brief process memory percentage usage alert threshold for ConMod and HCP3 host sensors
 * @note default value: if key is missing value 50 is used
 * @note variable type: uint8_t
 */
static constexpr char MEMORY_USAGE_ALERT_THRESHOLD_PER_PROCESS[]
    = "process_memory_percentage_usage_alert_threshold_per_process";

/**
 * @brief process memory percentage usage alert threshold for HCP4 sensor
 * @note default value: if key is missing value 90 is used
 * @note variable type: uint8_t
 */
static constexpr char MEMORY_USAGE_ALERT_THRESHOLD_PER_CORE[]
    = "process_memory_percentage_usage_alert_threshold_per_core";

/**
 * @brief process memory percentage usage alert threshold for HCP3 SE sensor
 * @note default value: if key is missing value 90 is used
 * @note variable type: uint8_t
 */
static constexpr char MEMORY_USAGE_ALERT_THRESHOLD_PER_PARTITION[]
    = "process_memory_percentage_usage_alert_threshold_per_partition";

/**
 * @brief process cpu percentage usage alert threshold for ConMod and HCP3 host sensors
 * @note default value: if key is missing value 70 is used
 * @note variable type: uint8_t
 */
static constexpr char CPU_USAGE_ALERT_THRESHOLD_PER_PROCESS[]
    = "process_cpu_percentage_usage_alert_threshold_per_process";

/**
 * @brief process cpu percentage usage alert threshold for HCP4 sensor
 * @note default value: if key is missing value 90 is used
 * @note variable type: uint8_t
 */
static constexpr char CPU_USAGE_ALERT_THRESHOLD_PER_CORE[] = "process_cpu_percentage_usage_alert_threshold_per_core";

/**
 * @brief process cpu percentage usage alert threshold for HCP3 SE sensor
 * @note default value: if key is missing value 90 is used
 * @note variable type: uint8_t
 */
static constexpr char CPU_USAGE_ALERT_THRESHOLD_PER_PARTITION[]
    = "process_cpu_percentage_usage_alert_threshold_per_partition";

/**
 * @brief disable the feature about GDC campaing availablity. If the feature is enabled, if there is no campaing,
 * IDSCore is disable, if the camaping is avaliable the IDSCore will be enabled.
 * @note default value: false
 * @note variable type: bool
 */
static constexpr char DISABLE_FEATURE_IDSENABLEDISABLE_ON_CAMPAIGN_AVAILABILITY[]
    = "disable_feature_idsenabledisable_on_campaign_availability";

/**
 * @brief GDC maximum message size value
 * @note default value: 256 kb
 * @note variable type: uint32_t
 */
static constexpr char GDC_MAXIMUM_MESSAGE_SIZE[] = "gdc_maximum_message_size";

/**
 * @brief GDC maximum messages allowed in drop entries list size
 * @note default value: 100
 * @note variable type: uint16_t
 */
static constexpr char GDC_MAXIMUM_DROP_ENTRIES_SIZE[] = "gdc_maximum_drop_entries_list_size";


/**
 * @brief List of CAN ids that are need to state in report.
 *        Since JSON does not supports hex numbers, the CAN ids have to be in decimal format.
 * @note  variable type: vector<uint32_t>
 */
static constexpr char CAN_ALGORITHM_STATED_CAN_IDS[] = "can_algorithm_stated_can_ids";

/**
 * @brief: List of CAN ids that are muted for being too noisy, in order
 *         to avoid superfluous data usage. Since JSON does not supports
 *         hex numbers, the CAN ids have to be in decimal format.
 * @type: vector<uint32_t>
 */
static constexpr char CAN_ALGORITHM_MUTED_CAN_IDS[] = "can_algorithm_muted_can_ids";

}  // namespace config_keys
// parasoft-end-suppress AUTOSAR-M3_4_1-b

}  // namespace brain

#endif  // BRAIN_CONFIG_CONSTANTS_HPP
