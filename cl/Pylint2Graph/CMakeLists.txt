set (PROGRAM_NAME Pylint2Graph)

set (SOURCES
    src/main.cpp
    src/Pylint2Graph.cpp
    src/PylintRulMaker.cpp
    src/PylintRunner.cpp
    
    inc/messages.h
    inc/Pylint2Graph.h
    inc/PylintRulMaker.h
    inc/PylintRunner.h 
)

add_executable(${PROGRAM_NAME} ${SOURCES})
add_dependencies(${PROGRAM_NAME} ${COLUMBUS_GLOBAL_DEPENDENCY})
target_link_libraries(${PROGRAM_NAME} python lim2graph graphsupport lim graph rul common csi strtable io ${COMMON_EXTERNAL_LIBRARIES})
add_copy_next_to_the_binary_dependency(${PROGRAM_NAME} Pylint_1.rul)
add_copy_next_to_the_binary_dependency(${PROGRAM_NAME} Pylint_2.rul)
add_copy_next_to_the_binary_dependency(${PROGRAM_NAME} Pylint.conf)
set_visual_studio_project_folder(${PROGRAM_NAME} TRUE)
