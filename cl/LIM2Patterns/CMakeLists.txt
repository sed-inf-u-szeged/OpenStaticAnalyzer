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

set(PY_PYVERSION 3.8)

add_executable(${PROGRAM_NAME} ${SOURCES})
add_dependencies(${PROGRAM_NAME} python${PY_PYVERSION} pybind11 ${COLUMBUS_GLOBAL_DEPENDENCY})
add_custom_copy_target(${PROGRAM_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/Patterns ${EXECUTABLE_OUTPUT_PATH}/Patterns DIRECTORY)

# have to python.h manually because of pybind11
target_include_directories(${PROGRAM_NAME} PRIVATE ${COLUMBUS_3RDPARTY_INSTALL_DIR}/include/python${PY_PYVERSION})
# preprocessor for building the embedding statically
target_compile_definitions(${PROGRAM_NAME} PRIVATE Py_NO_ENABLE_SHARED )

if (CMAKE_SYSTEM_NAME STREQUAL Linux OR CMAKE_SYSTEM_NAME STREQUAL Darwin)
  target_link_options(${PROGRAM_NAME} PRIVATE "LINKER:-E")
endif()

# not using pybind11::embed or pybind11::pybind11 because that includes the python installed on the system, and not the python in the 3rdparty
target_link_libraries(${PROGRAM_NAME} limmetrics lim2graph lim graph graphsupport rul strtable common csi io yamlcpp python${PY_PYVERSION} ${COMMON_EXTERNAL_LIBRARIES})
# host specific libraries
if (CMAKE_SYSTEM_NAME STREQUAL Windows)
  target_link_libraries(${PROGRAM_NAME} version ws2_32)
else (CMAKE_SYSTEM_NAME STREQUAL Linux)
  target_link_libraries(${PROGRAM_NAME} pthread dl util m)
endif ()
set_visual_studio_project_folder(${PROGRAM_NAME} TRUE)
