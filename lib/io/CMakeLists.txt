set (LIBNAME io)

set (SOURCES
    src/BinaryIO.cpp
    src/CsvIO.cpp
    src/GraphmlIO.cpp
    src/ioBase.cpp
    src/SimpleXmlIO.cpp
    src/XmlHandler.cpp
    src/ZippedIO.cpp

    inc/BinaryIO.h
    inc/CsvIO.h
    inc/GraphmlIO.h
    inc/ioBase.h
    inc/IO.h
    inc/messages.h
    inc/SimpleXmlIO.h
    inc/ZippedIO.h
)

add_library (${LIBNAME} STATIC ${SOURCES})
target_link_libraries (${LIBNAME} boost_iostreams z)
add_dependencies (${LIBNAME} boost)
set_visual_studio_project_folder(${LIBNAME} TRUE)

