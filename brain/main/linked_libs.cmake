# The main and the IdsMainFlow are linked to most of the libraries in IDS.
# This file is made to mention those libraries once for all projects and make sure the names that are given to libraries are uniform

# main.cpp target is built differently under each platform - but the linkage is the same for all main's 
set(LINK_TO_MAIN 
    common_ids
    LogAdapter
    IdsMainFlow  # Includes both IdsMainFlowBase.cpp and IdsMainFlow.cpp
    ExecutionReporter
)

# Same libraries will be linked to all IdsMainFlow classes 
set(LINK_TO_MAIN_FLOW
    common_ids
    PowerStateAdapter
    SupervisionAdapter
    AraPersistentMemory # ToDo - change name to uniform (e.g. PersistentMemoryHandler)
    MessageRepository
    Sender
    ExceededMessageSizeCheck
    NanoPB
    EngineDispatcher
)
