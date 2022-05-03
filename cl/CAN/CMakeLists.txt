set (PROGRAM_NAME CAN)

set (SOURCES
    src/main.cpp
)

add_executable(${PROGRAM_NAME} ${SOURCES})
add_dependencies(${PROGRAM_NAME} clang ${COLUMBUS_GLOBAL_DEPENDENCY})
target_link_libraries(${PROGRAM_NAME} common z ${CLANG_COMMON_LIBRARIES} ${COMMON_EXTERNAL_LIBRARIES})
set_visual_studio_project_folder(${PROGRAM_NAME} TRUE)
