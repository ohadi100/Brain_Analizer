# Project Name and definition:
project("CampaignConfiguration"
        VERSION 1.0.0
        DESCRIPTION "General utilities for the brain library")

add_library(CampaignConfiguration CampaignConfiguration.pb.cc)
set_source_files_properties(CampaignConfiguration.pb.cc PROPERTIES COMPILE_FLAGS -Wno-missing-declarations)

# Project include and link definitions:
target_include_directories(CampaignConfiguration PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
