
set (LIBNAME csi)

set (SOURCES
    src/csi.cpp
    src/PropertyData.cpp

    inc/csi.h
    inc/HeaderData.h
    inc/messages.h
    inc/PropertyData.h 
)

add_library (${LIBNAME} STATIC ${SOURCES})
add_dependencies (${LIBNAME} boost)
set_visual_studio_project_folder(${LIBNAME} TRUE)
