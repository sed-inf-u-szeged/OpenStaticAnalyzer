set (PROGRAM_NAME FxCop2Graph)

set (SOURCES
    src/FindLimNode.cpp
    src/FxCop2Graph.cpp
    src/main.cpp
    src/ReportConverter.cpp
    src/RuleConverter.cpp
    
    inc/Config.h
    inc/FindLimNode.h
    inc/FxCop2Graph.h
    inc/messages.h
    inc/ReportConverter.h
    inc/RuleConverter.h 
)

add_executable(${PROGRAM_NAME} ${SOURCES})
add_dependencies(${PROGRAM_NAME} ${COLUMBUS_GLOBAL_DEPENDENCY})
target_link_libraries(${PROGRAM_NAME} lim2graph graphsupport lim graph rul common csi strtable io ${COMMON_EXTERNAL_LIBRARIES})
add_copy_next_to_the_binary_dependency(${PROGRAM_NAME} FxCop.rul)
set_visual_studio_project_folder(${PROGRAM_NAME} TRUE)
