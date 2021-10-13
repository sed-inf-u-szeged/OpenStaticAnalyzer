set (PROGRAM_NAME UserDefinedMetrics)

set (SOURCES
    main.cpp
    inc/messages.h
    inc/UdmFunction.h
    inc/UdmNode.h
    inc/UdmHelpers.h
    inc/UdmCommon.h
    src/UdmFunction.cpp
    src/UdmNode.cpp
    src/UdmHelpers.cpp
    src/UdmCommon.cpp
)

add_executable(${PROGRAM_NAME} ${SOURCES})
add_dependencies(${PROGRAM_NAME} ${COLUMBUS_GLOBAL_DEPENDENCY})
target_link_libraries(${PROGRAM_NAME} graphsupport graph  strtable common csi rul io ${COMMON_EXTERNAL_LIBRARIES})
set_visual_studio_project_folder(${PROGRAM_NAME} TRUE)

if (MSVC)
   target_compile_options(${PROGRAM_NAME} PRIVATE "/bigobj")
endif ()


