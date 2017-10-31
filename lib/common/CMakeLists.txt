set (LIBNAME common)

set (SOURCES
    src/math/optimization/sa_problem.cpp
    src/math/common.cpp
    src/Arguments.cpp
    src/DirectoryFilter.cpp
    src/FileSup.cpp
    src/Stat.cpp
    src/StringSup.cpp
    src/WriteMessage.cpp
    
    inc/Arguments.h
    inc/DirectoryFilter.h
    inc/FileSup.h
    inc/math/common.h
    inc/math/linear/hungarian_method.h
    inc/math/optimization/sa_problem.h
    inc/messages.h
    inc/PlatformDependentDefines.h
    inc/sllist.h
    inc/Stat.h
    inc/StringSup.h
    inc/WriteMessage.h     
)

add_library (${LIBNAME} STATIC ${SOURCES})
target_link_libraries (${LIBNAME} boost_filesystem boost_system boost_regex)
if (CMAKE_SYSTEM_NAME STREQUAL Windows)
  target_link_libraries (${LIBNAME} psapi shlwapi)
endif()

add_dependencies (${LIBNAME} boost)
set_visual_studio_project_folder(${LIBNAME} TRUE)
