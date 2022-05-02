

message ("C++ Compiler:" ${CMAKE_CXX_COMPILER_ID} "-" ${CMAKE_CXX_COMPILER_VERSION} " " (${CMAKE_CXX_COMPILER}))
message ("C Compiler:" ${CMAKE_C_COMPILER_ID} "-" ${CMAKE_C_COMPILER_VERSION} " " (${CMAKE_C_COMPILER}))
if (NOT CMAKE_CXX_COMPILER_ID MATCHES GNU|Clang|MSVC)
  message("ERROR: Not supported compiler!")
endif()


set (COLUMBUS_PLATFORM_NAME x64)
set (VS_PLATFORM x64)
set (VS_PLATFORM_DIR x64/)
set (PYTHON_PLATFORM_NAME amd64)

if (CMAKE_SYSTEM_NAME STREQUAL Windows)
  set (SCRIPT_EXT .bat)
  set (CALL call)
elseif (CMAKE_SYSTEM_NAME STREQUAL Linux OR CMAKE_SYSTEM_NAME STREQUAL Darwin)
  set (SCRIPT_EXT .sh)
  set (COMMAND_PREFIX ./)
  set (CALL)
else ()
  message (FATAL_ERROR "Unknown system:${CMAKE_SYSTEM_NAME}")
endif()

set (COLUMBUS_PLATFORM_DEPENDENT_DIR ${COLUMBUS_PLATFORM_NAME})
set (EXE ${CMAKE_EXECUTABLE_SUFFIX})


# Sets the msvs for the node-gyp required for the javascript
if(MSVC)
  if(${CMAKE_VS_PLATFORM_TOOLSET} STREQUAL "v90")
    set (MSVS_VERSION "--msvs_version=2008")
  elseif(${CMAKE_VS_PLATFORM_TOOLSET} STREQUAL "v100")
    set (MSVS_VERSION "--msvs_version=2010")
  elseif(${CMAKE_VS_PLATFORM_TOOLSET} STREQUAL "v110")
    set (MSVS_VERSION "--msvs_version=2012")
  elseif(${CMAKE_VS_PLATFORM_TOOLSET} STREQUAL "v120")
    set (MSVS_VERSION "--msvs_version=2013")
  elseif(${CMAKE_VS_PLATFORM_TOOLSET} STREQUAL "v140")
    set (MSVS_VERSION "--msvs_version=2015")
  elseif(${CMAKE_VS_PLATFORM_TOOLSET} STREQUAL "v141")
    set (MSVS_VERSION "--msvs_version=2017")
  elseif(${CMAKE_VS_PLATFORM_TOOLSET} STREQUAL "v142")
    set (MSVS_VERSION "--msvs_version=2019")
  endif()
endif()
