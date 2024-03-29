cmake_minimum_required (VERSION 3.19.0)

# Set the default build type to release
if (NOT CMAKE_BUILD_TYPE )
  set (CMAKE_BUILD_TYPE Release CACHE STRING "Build Type: Release or Debug" FORCE)
endif()

project (OSA VERSION 5.1.0)

set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${EXECUTABLE_OUTPUT_PATH})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${EXECUTABLE_OUTPUT_PATH})
set (LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE  ${LIBRARY_OUTPUT_PATH})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG  ${LIBRARY_OUTPUT_PATH})
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
set (CMAKE_SUPPORT_FOLDER_NAME CMakeSupportTargets)

set_property (GLOBAL PROPERTY USE_FOLDERS ON)

include (BuildInfo)
include (Clang)
include (UtilityFunctions)
include (PlatformOptions)
include (CodebaseOptions)
include (Common)

add_subdirectory (cl/CAN)
add_subdirectory (cl/CAN2Lim)
add_subdirectory (cl/CANConfig)
add_subdirectory (cl/CANLib)
add_subdirectory (cl/CANLink)
add_subdirectory (cl/ClangTidy2Graph)
add_subdirectory (cl/Cppcheck2Graph)
add_subdirectory (cl/DCF-CPP)

add_subdirectory (cl/DuplicatedCodeFinder)
add_subdirectory (cl/ESLint2Graph)
add_subdirectory (cl/FindBugs2Graph)
add_subdirectory (cl/FxCop2Graph)
add_subdirectory (cl/GenericConfig)
add_subdirectory (cl/GraphDump)
add_subdirectory (cl/GraphMerge)
add_subdirectory (cl/JAN2ChangePath)
add_subdirectory (cl/JAN2Lim)
add_subdirectory (cl/JANFilter)
add_subdirectory (cl/JSAN2ChangePath)
add_subdirectory (cl/JSAN2Lim)
add_subdirectory (cl/LIM2Patterns)
add_subdirectory (cl/LIM2Metrics)
add_subdirectory (cl/MetricHunter)
add_subdirectory (cl/PAN)
add_subdirectory (cl/PAN2Lim)
add_subdirectory (cl/ParamCheck)
add_subdirectory (cl/PMD2Graph)
add_subdirectory (cl/Pylint2Graph)
add_subdirectory (cl/Roslyn2Graph)
add_subdirectory (cl/RuleManager)
add_subdirectory (cl/Sonar2Graph)
add_subdirectory (cl/AnalyzerCPP)
add_subdirectory (cl/AnalyzerCSharp)
add_subdirectory (cl/AnalyzerJava)
add_subdirectory (cl/AnalyzerJavaScript)
add_subdirectory (cl/AnalyzerPython)
add_subdirectory (cl/UserDefinedMetrics)

add_subdirectory (wrapper/AbstractWrapperLib)
add_subdirectory (wrapper/AnalyzerWrapperConfig)
add_subdirectory (wrapper/ArWrapper)
add_subdirectory (wrapper/AsWrapper)
add_subdirectory (wrapper/ClWrapper)
add_subdirectory (wrapper/ClangWrapper)
add_subdirectory (wrapper/CopyMoveWrapper)
add_subdirectory (wrapper/EnvironmentSetup)
add_subdirectory (wrapper/exewrapper)
add_subdirectory (wrapper/LdWrapper)
add_subdirectory (wrapper/LibWrapper)
add_subdirectory (wrapper/LinkWrapper)
add_subdirectory (wrapper/LnWrapper)
add_subdirectory (wrapper/VsbuildWrapper)
add_subdirectory (wrapper/WrapperEnvironmentConfig)

add_subdirectory (lib/archivecpp)
add_subdirectory (lib/clangsupport)
add_subdirectory (lib/common)
add_subdirectory (lib/controller)
add_subdirectory (lib/csharp)
add_subdirectory (lib/csi)
add_subdirectory (lib/genealogy)
add_subdirectory (lib/graph)
add_subdirectory (lib/graphsupport)
add_subdirectory (lib/io)
add_subdirectory (lib/java)
add_subdirectory (lib/javascript)
add_subdirectory (lib/jsoncpp)
add_subdirectory (lib/lim)
add_subdirectory (lib/lim2graph)
add_subdirectory (lib/limmetrics)
add_subdirectory (lib/python)
add_subdirectory (lib/rul)
add_subdirectory (lib/strtable)
add_subdirectory (lib/threadpool)
add_subdirectory (lib/yamlcpp)

add_subdirectory (java/lib/revision)
add_subdirectory (java/lib/graphlib)
add_subdirectory (java/lib/graphsupportlib)
add_subdirectory (java/cl/JAN)

add_subdirectory (javascript/cl/JSAN)
add_subdirectory (javascript/cl/ESLintRunner)

add_subdirectory (csharp)

add_subdirectory (3rdparty)
add_subdirectory (Analyzer)

