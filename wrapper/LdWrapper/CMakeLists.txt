set (PROGRAM_NAME LdWrapper)

set (SOURCES
    main.cpp
    LdWrapper.cpp
    
    LdWrapper.h
)

add_executable (${PROGRAM_NAME} ${SOURCES})
add_dependencies (${PROGRAM_NAME} ${COLUMBUS_GLOBAL_DEPENDENCY})
target_link_libraries (${PROGRAM_NAME} common abstractwrapper ${COMMON_EXTERNAL_LIBRARIES})
set_visual_studio_project_folder (${PROGRAM_NAME} TRUE)
