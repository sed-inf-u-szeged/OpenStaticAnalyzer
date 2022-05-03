set (LIBNAME clangsupport)

set (SOURCES
    ASTIDMapGenerator.cpp
    ASTLoader.cpp
    ASTFilter.cpp
    ASTSupport.cpp
    
    ASTIDMapGenerator.h
    ASTLoader.h
    ASTFilter.h
    ASTSupport.h
    messages.h
    CANCommon.h
)

add_library (${LIBNAME} STATIC ${SOURCES})
add_dependencies (${LIBNAME} lim common clang)
set_visual_studio_project_folder(${LIBNAME} TRUE)
