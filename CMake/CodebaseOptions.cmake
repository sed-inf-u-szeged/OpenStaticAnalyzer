
# Global options required for compiling the code base
configure_file (config/columbus_config.h.in columbus_config.h)
include_directories (${CMAKE_BINARY_DIR})
include_directories (${CMAKE_BINARY_DIR}/lib)
include_directories (${CMAKE_SOURCE_DIR}/inc)
include_directories (${CMAKE_SOURCE_DIR}/lib)
include_directories (${CMAKE_SOURCE_DIR}/wrapper)

# Compiler standard options
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

option (STRIP "Strip all symbols from the binaries" OFF)

add_definitions(-DBOOST_ALLOW_DEPRECATED_HEADERS -DBOOST_DISABLE_PRAGMA_MESSAGE)

set (COLUMBUS_3RDPARTY_INSTALL_DIR ${CMAKE_BINARY_DIR}/3rdparty/install)
set (COLUMBUS_3RDPARTY_SOURCE_DIR ${CMAKE_SOURCE_DIR}/3rdparty)

# Compiler warning settings
if (MSVC)
  # Disable some common compiler warnings end enable parallel build
  set (EXTRA_COMPILER_OPTIONS "/WX /wd4996 /wd4267 /wd4786 /wd4244 /wd4068 /MP /EHsc /experimental:external /external:W0 /external:I ${COLUMBUS_3RDPARTY_INSTALL_DIR}/include")

  # In Release builds enable Whole Program Optimization and Compile Time Code Generation
  set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /GL")
  set (CMAKE_C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /GL")
  set (CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG")
  set (CMAKE_STATIC_LINKER_FLAGS_RELEASE "${CMAKE_STATIC_LINKER_FLAGS_RELEASE} /LTCG")

  # The MSVCRT library is the DLL version of the CRT. (/MD) Since we use static CRT no MSVCRT is needed.
  set (CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /NODEFAULTLIB:MSVCRT /STACK:10485760")

  # The MSVCRTD library is the debug DLL version of the CRT. (/MDd) Since we use static CRT no MSVCRTD is needed.
  set (CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /NODEFAULTLIB:MSVCRTD /STACK:10485760")

  # Change the default MultiThreadedDLL runtime to MultiThreaded.
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

  # Set some global macro definitions requred for use boost and xerces
  add_definitions(-DBOOST_ALL_NO_LIB -DXERCES_STATIC_LIBRARY)

elseif (CMAKE_SYSTEM_NAME STREQUAL Linux)

  # Enable compiler warnings and use fPIC option
  set (EXTRA_COMPILER_OPTIONS "-Wall -Werror -Wno-unused-local-typedefs -Wno-unknown-pragmas -fPIC")
  set (EXTRA_CXX_FLAGS "-Wno-overloaded-virtual")

  if (STRIP)
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s")
  endif ()

  set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++ -static-libgcc")

endif ()

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_COMPILER_OPTIONS} ${EXTRA_CXX_FLAGS}")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_COMPILER_OPTIONS}")

# Common global dependencies
set (COLUMBUS_GLOBAL_DEPENDENCY generate_build_info)

if (CMAKE_SYSTEM_NAME STREQUAL Linux)
  include_directories (SYSTEM ${COLUMBUS_3RDPARTY_INSTALL_DIR}/include)
endif ()
link_directories (${COLUMBUS_3RDPARTY_INSTALL_DIR}/lib)

if (CMAKE_SYSTEM_NAME STREQUAL Windows)
  set (MVN_POSTFIX .bat)
  set (GRADLE_POSTFIX .bat)
endif ()



