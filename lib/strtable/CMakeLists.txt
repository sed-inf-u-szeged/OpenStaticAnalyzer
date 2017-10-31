set (LIBNAME strtable)

set (SOURCES
    src/StrTable.cpp
    src/RefDistributorStrTable.cpp
    
    inc/messages.h
    inc/RefDistributorStrTable.h
    inc/StrTable.h     
)

add_library (${LIBNAME} STATIC ${SOURCES})
add_dependencies (${LIBNAME} boost)
set_visual_studio_project_folder(${LIBNAME} TRUE)
