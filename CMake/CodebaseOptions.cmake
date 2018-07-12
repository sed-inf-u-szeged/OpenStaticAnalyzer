
# Global options required for compiling the code base
configure_file (config/columbus_config.h.in columbus_config.h)
include_directories (${CMAKE_BINARY_DIR})
include_directories (${CMAKE_BINARY_DIR}/lib)
include_directories (${CMAKE_SOURCE_DIR}/inc)
include_directories (${CMAKE_SOURCE_DIR}/lib)
include_directories (${CMAKE_SOURCE_DIR}/wrapper)

# Compiler standard options
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

option (STRIP "Strip all symbols from the binaries" OFF)

# Compiler warning settings
if (MSVC)
  # For ninja builds on windows we set the CMAKE_VS_PLATFORM_TOOLSET to V140 (VS2015)
  if (NOT CMAKE_VS_PLATFORM_TOOLSET)
    set (CMAKE_VS_PLATFORM_TOOLSET V140 CACHE STRING "" FORCE)
  endif ()

  # Disable some common compiler warnings end enable parallel build
  set (EXTRA_COMPILER_OPTIONS "/wd4996 /wd4267 /wd4786 /wd4996 /MP /EHsc")

  # In Release builds enable Whole Program Optimization and Compile Time Code Generation
  set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /GL")
  set (CMAKE_C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /GL")
  set (CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG")
  set (CMAKE_STATIC_LINKER_FLAGS_RELEASE "${CMAKE_STATIC_LINKER_FLAGS_RELEASE} /LTCG")

  # The MSVCRT library is the DLL version of the CRT. (/MD) Since we use static CRT no MSVCRT is needed.
  set (CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /NODEFAULTLIB:MSVCRT")

  # The MSVCRTD library is the debug DLL version of the CRT. (/MDd) Since we use static CRT no MSVCRTD is needed.
  set (CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /NODEFAULTLIB:MSVCRTD")

  # Replace the default MultiThreadedDLL runtime to MultiThreaded.
  replace_compiler_options (/MD /MT)
  replace_compiler_options (/MDd /MTd)

  # Set some global macro definitions requred for use boost and xerces
  add_definitions(-DBOOST_ALL_NO_LIB -DXERCES_STATIC_LIBRARY)

elseif (CMAKE_SYSTEM_NAME STREQUAL Linux)

  # Enable compiler warnings and use fPIC option
  set (EXTRA_COMPILER_OPTIONS "-Wall -fPIC")

  if (STRIP)
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s")
  endif ()

  set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++ -static-libgcc")

endif ()

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_COMPILER_OPTIONS}")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_COMPILER_OPTIONS}")

# Common global dependencies
set (COLUMBUS_GLOBAL_DEPENDENCY generate_build_info)

set (COLUMBUS_3RDPARTY_INSTALL_DIR ${CMAKE_BINARY_DIR}/3rdparty/install)
set (COLUMBUS_3RDPARTY_SOURCE_DIR ${CMAKE_SOURCE_DIR}/3rdparty)

include_directories (SYSTEM ${COLUMBUS_3RDPARTY_INSTALL_DIR}/include)
link_directories (${COLUMBUS_3RDPARTY_INSTALL_DIR}/lib)

if (CMAKE_SYSTEM_NAME STREQUAL Windows)
  set (MVN_POSTFIX .bat)
  set (GRADLE_POSTFIX .bat)
endif ()



