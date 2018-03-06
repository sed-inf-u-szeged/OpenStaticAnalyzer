set (PROGRAM_NAME PAN2Lim)

set (SOURCES
    src/main.cpp
    src/python2lim.cpp
    
    inc/messages.h
    inc/python2lim.h     
)

add_executable(${PROGRAM_NAME} ${SOURCES})
add_dependencies(${PROGRAM_NAME} ${COLUMBUS_GLOBAL_DEPENDENCY})
target_link_libraries(${PROGRAM_NAME} lim python strtable common csi io ${COMMON_EXTERNAL_LIBRARIES})
set_visual_studio_project_folder(${PROGRAM_NAME} TRUE)
