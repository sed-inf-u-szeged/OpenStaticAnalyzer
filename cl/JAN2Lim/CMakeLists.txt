set (PROGRAM_NAME JAN2Lim)

set (SOURCES
    src/CheckVisitor.cpp
    src/CommentVisitor.cpp
    src/HalsteadVisitor.cpp
    src/JAN2LimVisitor.cpp
    src/main.cpp
    
    inc/CheckVisitor.h
    inc/CommentVisitor.h
    inc/HalsteadVisitor.h
    inc/JAN2LimVisitor.h
    inc/messages.h 
)

add_executable(${PROGRAM_NAME} ${SOURCES})
add_dependencies(${PROGRAM_NAME} ${COLUMBUS_GLOBAL_DEPENDENCY})
target_link_libraries(${PROGRAM_NAME} lim java strtable common csi io ${COMMON_EXTERNAL_LIBRARIES})
set_visual_studio_project_folder(${PROGRAM_NAME} TRUE)
