set (LIBNAME jsoncpp)

set (SOURCES
    src/json_reader.cpp
    src/json_value.cpp
    src/json_valueiterator.inl
    src/json_writer.cpp
    
    inc/allocator.h
    inc/assertions.h
    inc/autolink.h
    inc/config.h
    inc/features.h
    inc/forwards.h
    inc/json.h
    inc/json_tool.h
    inc/reader.h
    inc/value.h
    inc/version.h
    inc/writer.h
)

add_library (${LIBNAME} STATIC ${SOURCES})
add_dependencies (${LIBNAME} boost)
set_visual_studio_project_folder(${LIBNAME} TRUE)
