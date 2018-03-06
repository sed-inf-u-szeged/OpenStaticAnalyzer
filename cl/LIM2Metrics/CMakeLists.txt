set (PROGRAM_NAME LIM2Metrics)

set (SOURCES
    main.cpp
    
    messages.h
)

add_executable(${PROGRAM_NAME} ${SOURCES})
add_dependencies(${PROGRAM_NAME} ${COLUMBUS_GLOBAL_DEPENDENCY})
target_link_libraries(${PROGRAM_NAME} graphsupport lim2graph graph limmetrics lim strtable common csi rul io ${COMMON_EXTERNAL_LIBRARIES})
add_copy_next_to_the_binary_dependency (${PROGRAM_NAME} MET.rul)
set_visual_studio_project_folder(${PROGRAM_NAME} FALSE)


