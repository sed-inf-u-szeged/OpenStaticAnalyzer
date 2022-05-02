set (PROGRAM_NAME Sonar2Graph)

set (SOURCES
    src/main.cpp

    inc/messages.h
)

add_executable(${PROGRAM_NAME} ${SOURCES})
add_dependencies(${PROGRAM_NAME} openssl ${COLUMBUS_GLOBAL_DEPENDENCY})
target_link_libraries(${PROGRAM_NAME} lim2graph graphsupport lim csi rul graph strtable common ${OPENSSL_LIBRARIES} ${COMMON_EXTERNAL_LIBRARIES})
add_copy_next_to_the_binary_dependency(${PROGRAM_NAME} sonar_tag_metadata.md)
set_visual_studio_project_folder(${PROGRAM_NAME} TRUE)
