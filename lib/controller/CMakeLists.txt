set (LIBNAME controller)

set (SOURCES
    src/Controller.cpp
    src/ProfileCommon.cpp
    src/ProfileHandler.cpp
    src/Task.cpp
    src/DirectedAcyclicGraph.cpp

    inc/messages.h
    inc/Controller.h
    inc/ProfileCommon.h
    inc/ProfileHandler.h
    inc/Properties.h
    inc/Task.h
    inc/DirectedAcyclicGraph.h
)

add_library (${LIBNAME} STATIC ${SOURCES})
add_dependencies (${LIBNAME} boost)
target_link_libraries(${LIBNAME} rul)
set_visual_studio_project_folder(${LIBNAME} TRUE)
