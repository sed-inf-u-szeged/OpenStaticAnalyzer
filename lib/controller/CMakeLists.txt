set (LIBNAME controller)

set (SOURCES
    src/Controller.cpp
    src/ProfileCommon.cpp
    src/ProfileHandler.cpp
    src/Task.cpp

    inc/messages.h
    inc/Controller.h
    inc/ProfileCommon.h
    inc/ProfileHandler.h
    inc/Properties.h
    inc/Task.h
)

add_library (${LIBNAME} STATIC ${SOURCES})
add_dependencies (${LIBNAME} boost)
set_visual_studio_project_folder(${LIBNAME} TRUE)
