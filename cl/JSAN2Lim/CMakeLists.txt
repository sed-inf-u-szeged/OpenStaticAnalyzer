set (PROGRAM_NAME JSAN2Lim)

set (SOURCES
    src/JSAN2LimVisitor.cpp
    src/HalsteadVisitor.cpp
    src/main.cpp
    
    inc/JSAN2LimVisitor.h
    inc/HalsteadVisitor.h
    inc/messages.h 
)

add_executable(${PROGRAM_NAME} ${SOURCES})
add_dependencies(${PROGRAM_NAME} ${COLUMBUS_GLOBAL_DEPENDENCY})
target_link_libraries(${PROGRAM_NAME} lim javascript strtable common csi io ${COMMON_EXTERNAL_LIBRARIES})
set_visual_studio_project_folder(${PROGRAM_NAME} TRUE)
