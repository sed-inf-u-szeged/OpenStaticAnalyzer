set (PROGRAM_NAME CAN2Lim)

set (SOURCES
    src/ASTConversionInfo.cpp
    inc/ASTConversionInfo.h
    src/ASTVisitor.cpp
    inc/ASTVisitor.h
    src/main.cpp
    src/MergeUID.cpp
    inc/MergeUID.h
    inc/messages.h
    src/CommentProcessor.cpp
    inc/CommentProcessor.h
    src/Linker.cpp
    inc/Linker.h
    src/clangHelpers.cpp
    inc/clangHelpers.h
)

add_executable(${PROGRAM_NAME} ${SOURCES})
add_dependencies(${PROGRAM_NAME} clang ${COLUMBUS_GLOBAL_DEPENDENCY})
target_link_libraries(${PROGRAM_NAME} clangsupport lim threadpool strtable common csi io ${CLANG_COMMON_LIBRARIES} ${COMMON_EXTERNAL_LIBRARIES})
set_visual_studio_project_folder(${PROGRAM_NAME} TRUE)
