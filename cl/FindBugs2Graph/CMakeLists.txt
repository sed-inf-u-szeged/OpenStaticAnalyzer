set (PROGRAM_NAME FindBugs2Graph)

set (SOURCES
    src/main.cpp
    src/ResultConverter.cpp
    src/RuleConverter.cpp
    
    inc/messages.h
    inc/ResultConverter.h
    inc/RuleConverter.h 
)

add_executable(${PROGRAM_NAME} ${SOURCES})
add_dependencies(${PROGRAM_NAME} ${COLUMBUS_GLOBAL_DEPENDENCY})
target_link_libraries(${PROGRAM_NAME} lim2graph graphsupport lim graph rul common csi strtable io ${COMMON_EXTERNAL_LIBRARIES})
add_copy_next_to_the_binary_dependency(${PROGRAM_NAME} FindBugs.rul.md)
add_copy_next_to_the_binary_dependency(${PROGRAM_NAME} FindBugs.rul_metadata.md)
add_dependencies(${PROGRAM_NAME} CommonTagMetadata_copy_cwe_metadata.md CommonTagMetadata_copy_owasp_metadata.md CommonTagMetadata_copy_sei_cert_metadata.md)
set_visual_studio_project_folder(${PROGRAM_NAME} TRUE)
