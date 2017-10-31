set (LIBNAME threadpool)

set (SOURCES
    src/ThreadPool.cpp
    
    inc/ThreadPool.h
)

add_library (${LIBNAME} STATIC ${SOURCES})
target_link_libraries (${LIBNAME} boost_thread)
add_dependencies (${LIBNAME} boost)

if (CMAKE_SYSTEM_NAME STREQUAL Linux)
  target_link_libraries (${LIBNAME} rt pthread)
endif()

set_visual_studio_project_folder(${LIBNAME} TRUE)

