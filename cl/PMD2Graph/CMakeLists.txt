set (PROGRAM_NAME PMD2Graph)

set (SOURCES
    PMD/PMDStrategy-config.cpp
    PMD/PMDStrategy-csv.cpp
    PMD/PMDStrategy.h
    PMD/PMDStrategy-rul.cpp
    CheckerStrategy.cpp
    MetricTree.cpp
    main.cpp
    
    CheckerStrategy.h
    messages.h
    MetricTree.h
    PMD/PMDStrategy.h     
)

add_executable(${PROGRAM_NAME} ${SOURCES})
add_dependencies(${PROGRAM_NAME} ${COLUMBUS_GLOBAL_DEPENDENCY})
target_link_libraries(${PROGRAM_NAME} lim2graph lim csi rul graph graphsupport io strtable common ${COMMON_EXTERNAL_LIBRARIES})
add_copy_next_to_the_binary_dependency (${PROGRAM_NAME} PMD/PMD.rul.md)
add_copy_next_to_the_binary_dependency (${PROGRAM_NAME} PMD/PMD.rul_metadata.md)
add_dependencies(${PROGRAM_NAME} CommonTagMetadata_copy_cwe_metadata.md CommonTagMetadata_copy_sei_cert_metadata.md)
add_copy_next_to_the_binary_dependency (${PROGRAM_NAME} PMD/PMD-config.xml)
set_visual_studio_project_folder(${PROGRAM_NAME} TRUE)

