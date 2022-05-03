set (PROGRAM_NAME ClangTidy2Graph)

set (SOURCES
    src/main.cpp
    src/ResultConverter.cpp
    
    inc/messages.h
    inc/defines.h
    inc/ResultConverter.h
)

add_executable(${PROGRAM_NAME} ${SOURCES})
add_dependencies(${PROGRAM_NAME} ${COLUMBUS_GLOBAL_DEPENDENCY})
target_link_libraries(${PROGRAM_NAME} lim2graph graphsupport lim graph rul common csi strtable io ${COMMON_EXTERNAL_LIBRARIES})
add_copy_next_to_the_binary_dependency(${PROGRAM_NAME} ClangTidy.rul)
set_visual_studio_project_folder(${PROGRAM_NAME} TRUE)


