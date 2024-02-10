project(IdsPubSub DESCRIPTION "IDS/Portal simple pub/sub example" LANGUAGES CXX C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(proto)
add_subdirectory(ids-service)
add_subdirectory(idsm)
add_subdirectory(PortalCommunicator)
#add_subdirectory(idscore)
