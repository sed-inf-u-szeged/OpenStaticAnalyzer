set (PROGRAM_NAME RuleManager)

set (SOURCES
    src/main.cpp
    src/MD.cpp
    src/UGRefGenerator.cpp
    
    inc/MD.h
    inc/UGRefGenerator.h
)

add_executable(${PROGRAM_NAME} ${SOURCES})
add_dependencies(${PROGRAM_NAME} ${COLUMBUS_GLOBAL_DEPENDENCY})
target_link_libraries(${PROGRAM_NAME} rul ${COMMON_EXTERNAL_LIBRARIES})
set_visual_studio_project_folder(${PROGRAM_NAME} TRUE)
