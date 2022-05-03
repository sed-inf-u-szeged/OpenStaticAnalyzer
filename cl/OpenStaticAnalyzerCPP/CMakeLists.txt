set (PROGRAM_NAME OpenStaticAnalyzerCPP)

set (SOURCES
    src/Task.cpp
    src/main.cpp
    
    inc/messages.h
    inc/Properties.h
    inc/Task.h 
)

add_executable(${PROGRAM_NAME} ${SOURCES})
add_dependencies(${PROGRAM_NAME} ${COLUMBUS_GLOBAL_DEPENDENCY})
target_link_libraries(${PROGRAM_NAME} archivecpp lim controller graph graphsupport threadpool rul strtable common csi io ${COMMON_EXTERNAL_LIBRARIES})
add_copy_next_to_the_binary_dependency(${PROGRAM_NAME} rules_cpp.csv)
set_visual_studio_project_folder(${PROGRAM_NAME} TRUE)

if (APPLE)
find_library(corefoundation_lib CoreFoundation)
find_library(coreservices_lib CoreServices)
set(frameworks
    ${coreservices_lib}
    ${corefoundation_lib})
target_link_libraries(${PROGRAM_NAME} ${frameworks})
endif (APPLE)
