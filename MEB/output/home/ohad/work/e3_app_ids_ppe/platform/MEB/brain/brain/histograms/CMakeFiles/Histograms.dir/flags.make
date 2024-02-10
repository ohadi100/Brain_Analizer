# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

# compile CXX with /home/ohad/icas-1-sdk/toolchains/qemu-arm64-evo/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++
CXX_FLAGS = --sysroot=/home/ohad/icas-1-sdk/toolchains/qemu-arm64-evo/sysroots/cortexa57-cortexa53-poky-linux -D_QEMU_ARM64_EVO -Wall -std=c++14 -pthread -fstack-protector-strong -ffunction-sections -fdata-sections -DARA_COM_SIMPLE_UTF8_STRING_SERIALIZATION -DARA_COM_DEFAULT_STRUCT_LENGTH_FIELD_4BYTES -Werror -Wextra -Wno-return-type -pedantic -fdiagnostics-color=always -Wno-sized-deallocation -ggdb -Wl,-z,relro,-z,now -pthread -Wall -D_GLIBCXX_USE_NANOSLEEP -Wno-error=type-limits -DLINUX -DHAS_VSOMEIP_BINDING -s -DLinux -DBOOST_DISABLE_CURRENT_FUNCTION -fPIC -fPIE -Wextra -O3 -DNDEBUG -D_FORTIFY_SOURCE=2 -O2 -D_HAS_VSOMEIP_BINDING -fPIC   -fstack-protector-strong -std=c++14

CXX_DEFINES = -DGIT_BRANCH="" -DGIT_REVISION="" -DIDS_BUILD="" -DLINUX -DMEB_PLATFORM=1 -DMEMORY_MANAGER_SIMULATION -DRELEASE=1 -D_GLIBCXX_USE_NANOSLEEP

CXX_INCLUDES = -isystem /home/ohad/icas-1-sdk/toolchains/qemu-arm64-evo/sysroots/x86_64-pokysdk-linux/usr/lib/aarch64-poky-linux/gcc/aarch64-poky-linux/10.2.0/include -isystem /home/ohad/icas-1-sdk/toolchains/qemu-arm64-evo/sysroots/x86_64-pokysdk-linux/usr/lib/aarch64-poky-linux/gcc/aarch64-poky-linux/10.2.0/include-fixed -isystem /home/ohad/icas-1-sdk/toolchains/qemu-arm64-evo/sysroots/cortexa57-cortexa53-poky-linux/usr/include/c++/10.2.0 -isystem /home/ohad/icas-1-sdk/toolchains/qemu-arm64-evo/sysroots/cortexa57-cortexa53-poky-linux/usr/include/c++/10.2.0/aarch64-poky-linux -isystem /home/ohad/icas-1-sdk/toolchains/qemu-arm64-evo/sysroots/cortexa57-cortexa53-poky-linux/usr/include -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/alive_supervision -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/persistent_memory -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/persistent_memory/mock -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/persistent_memory/factory -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/persistent_memory/interface -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/persistent_memory/persistent_map -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/persistent_memory/watchdog -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/configuration -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/counter_manager -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/mocks -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/notification_handler -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/sensor_data -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/shutdown_and_enabler -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/shutdown_and_enabler/ids_enabler -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/thread_handler -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/utils/conditionalSleep -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/utils/CPP -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/utils/diagnostics -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/utils/GUID -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/utils/jsonUtils -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/utils/logger -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/utils/os -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/utils/random -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/utils/singleQueue -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/utils/types -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/utils/timer -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/utils/os/linux -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/utils/wrr -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/utils/os/time -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/version -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/app -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/main -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/main/Base -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/communicator -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/communicator/periodic -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/config -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/diagnostics/interface -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/engines -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/engines/serializer -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/engines/dispatcher -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/security_events -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/events -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/histograms -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/messageRepository -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/messageRepository/interface -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/noise_filter -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/noise_filter/event_noise_filter -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/noise_filter/sensor_noise_filter -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/sender -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/sender/publishers/interface -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/sender/publishers/GDC_12 -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/sender/publishers/GDC_20 -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/sender/publishers/http_publisher -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/sender/publishers/ids_proxy_someip -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/sender/publishers/utils/message_size_check -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/sensor_data -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/execution_reporter -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/power_state_adapter -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/supervision_adapter -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/log_handlers -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/ipv6Address -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/nanopb -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/vehicle_data -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/main/MEB -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/engines/MEB -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/utils/log_handlers/aralog_legacy -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/generated -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/communicator/legacySomeip -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/brain/communicator/CanCommunicator -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/ext/histogram-lib/include -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/ext/jsoncpp/linux/jsoncpp/include -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/ext/histogram-lib/src/policer -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/counter_manager/counters -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/mocks/ids_socket -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/utils/socket -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/mocks/unix_domain_socket -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/utils/stateMachine -I/home/ohad/work/e3_app_ids_ppe/platform/MEB/brain/common/utils/typeCasting 

