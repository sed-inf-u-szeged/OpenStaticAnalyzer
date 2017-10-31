set (LIBNAME rul)

set (SOURCES
    src/RulHandler.cpp

    inc/messages.h
    inc/RulHandler.h
)

add_library (${LIBNAME} STATIC ${SOURCES})
target_link_libraries (${LIBNAME} xerces-c)

if (CMAKE_SYSTEM_NAME STREQUAL Linux)
  target_link_libraries (${LIBNAME} pthread)
endif()

set_visual_studio_project_folder(${LIBNAME} TRUE)
