set (PROGRAM_NAME Roslyn2Graph)

set (SOURCES
    src/main.cpp
    src/ResultConverter.cpp
    src/XMLParser.cpp

    inc/defines.h
    inc/messages.h
    inc/ResultConverter.h
    inc/XMLParser.h
)

add_executable(${PROGRAM_NAME} ${SOURCES})
add_dependencies(${PROGRAM_NAME} ${COLUMBUS_GLOBAL_DEPENDENCY})
target_link_libraries(${PROGRAM_NAME} lim2graph graphsupport lim graph rul common csi strtable io ${COMMON_EXTERNAL_LIBRARIES})
set_visual_studio_project_folder(${PROGRAM_NAME} TRUE)
