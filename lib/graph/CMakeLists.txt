set (LIBNAME graph)

set (SOURCES
    src/Attribute.cpp
    src/BGraph.cpp
    src/Edge.cpp
    src/Exceptions.cpp
    src/GraphSchemaReader.cpp
    src/GraphXmlHandler.cpp
    src/Node.cpp
    
    inc/Attribute.h
    inc/BGraph.h
    inc/BoostInit.h
    inc/Edge.h
    inc/Exceptions.h
    inc/graph.h
    inc/Node.h     
)

add_library (${LIBNAME} STATIC ${SOURCES})
add_dependencies (${LIBNAME} boost)
target_link_libraries (${LIBNAME} INTERFACE PUBLIC io jsoncpp)
set_visual_studio_project_folder(${LIBNAME} TRUE)
