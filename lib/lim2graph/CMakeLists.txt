set (LIBNAME lim2graph)

set (SOURCES
    src/Lim2GraphConverter.cpp
    src/VisitorGraphConverter.cpp
    
    inc/Lim2GraphConverter.h
    inc/messages.h
    inc/VisitorGraphConverter.h     
)

add_library (${LIBNAME} STATIC ${SOURCES})
add_dependencies (${LIBNAME} lim)
set_visual_studio_project_folder(${LIBNAME} TRUE)
