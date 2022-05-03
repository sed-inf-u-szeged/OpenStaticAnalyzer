set (PROGRAM_NAME CANLink)

set (SOURCES
    src/main.cpp
    
    inc/messages.h
)

add_executable(${PROGRAM_NAME} ${SOURCES})
add_dependencies(${PROGRAM_NAME} ${COLUMBUS_GLOBAL_DEPENDENCY})
target_link_libraries(${PROGRAM_NAME} common io ${COMMON_EXTERNAL_LIBRARIES})
set_visual_studio_project_folder(${PROGRAM_NAME} TRUE)
