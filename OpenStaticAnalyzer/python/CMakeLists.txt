set (PACKAGE_LANG Python)
set (OSA_TARGET_NAME OSA-${PACKAGE_LANG})

add_subdirectory (doc/usersguide)

add_custom_target (
    ${OSA_TARGET_NAME}
)
set_visual_studio_project_folder(${OSA_TARGET_NAME} FALSE)

file (MAKE_DIRECTORY
      ${OSA_PACKAGE_DIR}/${PACKAGE_LANG}/Demo
      ${OSA_PACKAGE_DIR}/${PACKAGE_LANG}/Tools
)

# These functions copy the SOURCE file into different directories of the OpenStaticAnalyzer package.
# The second parameter is optional. You can set the name of the target, which will be used for generating the SOURCE.
# The third parameter is also optional. You can set a different name for the SOURCE on which the file will be created in the tools directory.
function (add_custom_generated_copy_dependency_to_root_dir SOURCE)
  add_custom_generated_copy_dependency(${OSA_TARGET_NAME} ${EXECUTABLE_OUTPUT_PATH} ${OSA_PACKAGE_DIR}/${PACKAGE_LANG} ${ARGV})
endfunction ()

function (add_custom_generated_copy_dependency_to_tools_dir SOURCE)
  add_custom_generated_copy_dependency(${OSA_TARGET_NAME} ${EXECUTABLE_OUTPUT_PATH} ${OSA_PACKAGE_DIR}/${PACKAGE_LANG}/Tools ${ARGV})
endfunction ()

add_custom_generated_copy_dependency_to_root_dir (OpenStaticAnalyzerPython${EXE})

add_custom_generated_copy_dependency_to_tools_dir (rules_python.csv OpenStaticAnalyzerPython)
add_custom_generated_copy_dependency_to_tools_dir (DuplicatedCodeFinder_python${EXE} DuplicatedCodeFinder_python DuplicatedCodeFinder${EXE})
add_custom_generated_copy_dependency_to_tools_dir (DCF.rul DuplicatedCodeFinder_python_copy_DCF.rul)
add_custom_generated_copy_dependency_to_tools_dir (GraphDump${EXE})
add_custom_generated_copy_dependency_to_tools_dir (GraphMerge${EXE})
add_custom_generated_copy_dependency_to_tools_dir (LIM2Metrics${EXE})
add_custom_generated_copy_dependency_to_tools_dir (MET.rul LIM2Metrics)
add_custom_generated_copy_dependency_to_tools_dir (MetricHunter_python${EXE} MetricHunter_python MetricHunter${EXE})
add_custom_generated_copy_dependency_to_tools_dir (MetricHunter_PYTHON.threshold MetricHunter_python_copy_MetricHunter_PYTHON.threshold MetricHunter.threshold)
add_custom_generated_copy_dependency_to_tools_dir (PAN2${EXE})
add_custom_generated_copy_dependency_to_tools_dir (PAN3${EXE})
add_custom_generated_copy_dependency_to_tools_dir (PAN2Lim${EXE})
add_custom_generated_copy_dependency_to_tools_dir (Pylint2Graph${EXE})
add_custom_generated_copy_dependency_to_tools_dir (Pylint.rul Pylint2Graph)
add_custom_generated_copy_dependency_to_tools_dir (Pylint.conf Pylint2Graph)

add_custom_generated_copy_dependency(
    ${OSA_TARGET_NAME}
    doc/usersguide
    ${OSA_PACKAGE_DIR}/${PACKAGE_LANG}
    UsersGuide.html
    ${OSA_TARGET_NAME}-UG
)

add_custom_copy_target (${OSA_TARGET_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/demo/analyze${SCRIPT_EXT} ${OSA_PACKAGE_DIR}/${PACKAGE_LANG}/Demo/analyze${SCRIPT_EXT})

if (CMAKE_SYSTEM_NAME STREQUAL Linux)
  add_custom_copy_target (${OSA_TARGET_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/demo/filter_linux.txt ${OSA_PACKAGE_DIR}/${PACKAGE_LANG}/Demo/filter.txt)
elseif (CMAKE_SYSTEM_NAME STREQUAL Windows)
  add_custom_copy_target (${OSA_TARGET_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/demo/filter_win.txt ${OSA_PACKAGE_DIR}/${PACKAGE_LANG}/Demo/filter.txt)
endif ()

add_custom_extract_target (
    ${OSA_TARGET_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/demo/ceilometer.zip
    ${OSA_PACKAGE_DIR}/${PACKAGE_LANG}/Demo
    ${OSA_PACKAGE_DIR}/${PACKAGE_LANG}/Demo/ceilometer
)

add_custom_copy_target (
    ${OSA_TARGET_NAME}
    ${COLUMBUS_3RDPARTY_SOURCE_DIR}/python/pylint
    ${OSA_PACKAGE_DIR}/${PACKAGE_LANG}/Tools/python
    DIRECTORY
)

copy_licenses()
