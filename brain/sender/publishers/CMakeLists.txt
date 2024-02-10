message(STATUS "CMake process for publishers start")

add_subdirectory(utils)

# TODO fix according cmake guidline IDSPPE-1456
# SSP_Publisher
if((DEFINED ENV{SSP_PLATFORM}) OR (DEFINED ENV{SSP_SIMULATION}) OR (DEFINED ENV{SSP_PLATFORM_TEST}))
    message(STATUS "SSP Publisher")
    add_subdirectory(GDC_20)
# HTTPS/GDC Publisher
else() 
        if((DEFINED ENV{SIMULATION}) AND (NOT DEFINED ENV{SSP_PLATFORM_TEST}))
                if (NOT DEFINED ENV{SSP_SIMULATION})
                        add_subdirectory(GDC_12)
                else()
                        add_subdirectory(https_publisher)
                endif()
        endif()

        if(DEFINED EEE_PLATFORM)
                if (NOT DEFINED HTTPS_PUBLISHER)
                        add_subdirectory(GDC_12)
                else()
                        add_subdirectory(https_publisher)
                endif()
        endif()
endif()

message(STATUS "End of CMake process for publishers")
