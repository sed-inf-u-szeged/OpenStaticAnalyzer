set (PROGRAM_NAME LIM2Patterns)

set (SOURCES
    src/Helpers.cpp
    #src/Calculate/CreateCalculate.cpp
    #src/Calculate/Calculate.cpp
    #src/Calculate/CalculateFor.cpp
    #src/Calculate/CalculateFormula.cpp
    #src/Calculate/CalculateIf.cpp
    #src/Calculate/Checker/PatternValidator.cpp
    src/Conditions/Checker/PatternValidator.cpp
    src/Conditions/AllCondition.cpp
    src/Conditions/AndCondition.cpp
    src/Conditions/AnyCondition.cpp
    #src/Conditions/Condition.cpp
    src/Conditions/CreateCondition.cpp
    src/Conditions/ExistsCondition.cpp
    src/Conditions/FormulaCondition.cpp
    src/Conditions/MultiCondition.cpp
    src/Conditions/NandCondition.cpp
    src/Conditions/NodeTypeCondition.cpp
    src/Conditions/NorCondition.cpp
    src/Conditions/NotCondition.cpp
    src/Conditions/OrCondition.cpp
    src/Conditions/XorCondition.cpp
    src/Conditions/PythonCondition.cpp
    src/LIM2Patterns.cpp
    src/PythonBinding.cpp
    src/main.cpp
    
    inc/Helpers.h
    #inc/Calculate/CreateCalculate.h
    #inc/Calculate/Calculate.h
    #inc/Calculate/CalculateFor.h
    #inc/Calculate/CalculateFormula.h
    #inc/Calculate/CalculateIf.h
    #inc/Calculate/Checker/PatternValidator.h
    inc/Conditions/Checker/PatternValidator.h
    inc/Conditions/AllCondition.h
    inc/Conditions/AndCondition.h
    inc/Conditions/AnyCondition.h
    inc/Conditions/Condition.h
    inc/Conditions/Conditions.h
    inc/Conditions/CreateCondition.h
    inc/Conditions/ExistsCondition.h
    inc/Conditions/FormulaCondition.h
    inc/Conditions/MultiCondition.h
    inc/Conditions/NandCondition.h
    inc/Conditions/NodeTypeCondition.h
    inc/Conditions/NorCondition.h
    inc/Conditions/NotCondition.h
    inc/Conditions/OrCondition.h
    inc/Conditions/XorCondition.h
    inc/Conditions/PythonCondition.h
    inc/LIM2Patterns.h
    inc/PythonBinding.h
    inc/messages.h 
)

add_subdirectory(pybind11)
set(PY_PYVER 38)
set(PY_PYVERSION 3.8)
set(PY_FULL_VERSION 3.8.6)
set(EmbedPath ${CMAKE_CURRENT_BINARY_DIR}/Embed)
set(LibPath ${CMAKE_CURRENT_BINARY_DIR}/Lib)
set(EmbedZipPath ${CMAKE_CURRENT_BINARY_DIR}/python-${PY_FULL_VERSION}-embed.zip)
set(LibZipPath ${EmbedPath}/python${PY_PYVER}.zip)
set(PATTERNS_COPY_NAME LIM2Patterns_PatternsCopy)
set(LIBS_COPY_NAME LIM2Patterns_LibCopy)


if(EXISTS ${LibPath})
  file(REMOVE_RECURSE ${LibPath})
endif()

  set(PYTHON_PLATFORM amd64)
  set(HASH 5f95c5a93e2d8a5b077f406bc4dd96e7)
  if(NOT "${CMAKE_GENERATOR_PLATFORM}" MATCHES "(Win64|IA64|x64|arm64|amd64)")
    set(PYTHON_PLATFORM win32)
    set(HASH 7b287a90b33c2a9be55fabc24a7febbb)
  endif()

  message(STATUS "Downloading python-${PY_FULL_VERSION}-embed-${PYTHON_PLATFORM}.zip")
  file(DOWNLOAD https://www.python.org/ftp/python/${PY_FULL_VERSION}/python-${PY_FULL_VERSION}-embed-${PYTHON_PLATFORM}.zip ${EmbedZipPath} EXPECTED_HASH MD5=${HASH})
  file(MAKE_DIRECTORY ${EmbedPath})
  file(MAKE_DIRECTORY ${LibPath})
  message(STATUS "Extracting python embed.")
  execute_process(
      COMMAND ${CMAKE_COMMAND} -E tar xfz ${EmbedZipPath}
      WORKING_DIRECTORY ${EmbedPath}
  )
  message(STATUS "Extracting python lib.")
  execute_process(
      COMMAND ${CMAKE_COMMAND} -E tar xfz ${LibZipPath}
      WORKING_DIRECTORY ${LibPath}
  )
  message(STATUS "Removing excess directories.")
  file(REMOVE_RECURSE ${EmbedPath})
  file(REMOVE ${EmbedZipPath})
  


 # add patterns
add_copy_custom_target_dir(${PATTERNS_COPY_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/Patterns ${EXECUTABLE_OUTPUT_PATH}/Patterns)
# add python libs
add_copy_custom_target_dir(${LIBS_COPY_NAME} ${CMAKE_CURRENT_BINARY_DIR}/Lib ${EXECUTABLE_OUTPUT_PATH}/Lib)

add_executable(${PROGRAM_NAME} ${SOURCES})
add_dependencies(${PROGRAM_NAME} ${PATTERNS_COPY_NAME} ${LIBS_COPY_NAME} ${COLUMBUS_GLOBAL_DEPENDENCY})

# have to python.h manually because of pybind11
target_include_directories(${PROGRAM_NAME} PUBLIC ${COLUMBUS_3RDPARTY_INSTALL_DIR}/include/python${PY_PYVERSION} ${CMAKE_CURRENT_SOURCE_DIR}/pybind11/include)
# preprocessor for building the embedding statically
target_compile_definitions(${PROGRAM_NAME} PUBLIC Py_NO_ENABLE_SHARED )
# not using pybind11::embed or pybind11::pybind11 because that includes the python installed on the system, and not the python in the 3rdparty
target_link_libraries(${PROGRAM_NAME} limmetrics lim2graph lim graph graphsupport rul strtable common csi io yamlcpp python${PY_PYVERSION} ${COMMON_EXTERNAL_LIBRARIES})
# host specific libraries
if (CMAKE_SYSTEM_NAME STREQUAL Windows)
  target_link_libraries(${PROGRAM_NAME} version ws2_32)
else (CMAKE_SYSTEM_NAME STREQUAL Linux)
  target_link_libraries(${PROGRAM_NAME} pthread dl util m)
endif ()
set_visual_studio_project_folder(${PROGRAM_NAME} FALSE)
