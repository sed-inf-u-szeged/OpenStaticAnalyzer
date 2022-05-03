set (LIBNAME archivecpp)

set (SOURCES
    src/ArchiveHandler.cpp
    
    inc/ArchiveHandler.h
    inc/messages.h     
)

add_library (${LIBNAME} STATIC ${SOURCES})
target_link_libraries (${LIBNAME} miniz)
set_visual_studio_project_folder(${LIBNAME} TRUE)
