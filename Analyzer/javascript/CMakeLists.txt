set (PACKAGE_LANG JavaScript)
set (ANALYZER_TARGET_NAME AN-${PACKAGE_LANG})

add_subdirectory (doc/usersguide)

add_custom_target (
    ${ANALYZER_TARGET_NAME}
)
set_visual_studio_project_folder(${ANALYZER_TARGET_NAME} FALSE)

file (MAKE_DIRECTORY
      ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/Demo
      ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/Tools
)

# These functions copy the SOURCE file into different directories of the Analyzer package.
# The second parameter is optional. You can set the name of the target, which will be used for generating the SOURCE.
# The third parameter is also optional. You can set a different name for the SOURCE on which the file will be created in the tools directory.
function (add_custom_generated_copy_dependency_to_root_dir SOURCE)
  add_custom_generated_copy_dependency(${ANALYZER_TARGET_NAME} ${EXECUTABLE_OUTPUT_PATH} ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG} ${ARGV})
endfunction ()

function (add_custom_generated_copy_dependency_to_tools_dir SOURCE)
  add_custom_generated_copy_dependency(${ANALYZER_TARGET_NAME} ${EXECUTABLE_OUTPUT_PATH} ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/Tools ${ARGV})
endfunction ()

add_dependencies(${ANALYZER_TARGET_NAME} ${ANALYZER_COMMON_TARGET_NAME})

add_custom_generated_copy_dependency_to_root_dir (AnalyzerJavaScript${EXE})

add_custom_generated_copy_dependency_to_tools_dir (GraphDump${EXE})
add_custom_generated_copy_dependency_to_tools_dir (GraphMerge${EXE})
add_custom_generated_copy_dependency_to_tools_dir (JSAN2Lim${EXE})

#copy JSAN and ESlintRunner
add_custom_generated_copy_dependency (${ANALYZER_TARGET_NAME} ${EXECUTABLE_OUTPUT_PATH}/node_modules ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/Tools/node_modules jsan jsan_virtual_target jsan DIRECTORY)
add_custom_generated_copy_dependency (${ANALYZER_TARGET_NAME} ${EXECUTABLE_OUTPUT_PATH}/node_modules ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/Tools/node_modules eslintrunner eslintrunner_virtual_target eslintrunner DIRECTORY)

add_custom_generated_copy_dependency_to_tools_dir (rules_javascript.csv AnalyzerJavaScript)
add_custom_generated_copy_dependency_to_tools_dir (general_metadata.md AnalyzerJavaScript)
add_custom_generated_copy_dependency_to_tools_dir (JSAN2ChangePath${EXE})
add_custom_generated_copy_dependency_to_tools_dir (ESLint2Graph${EXE})
add_custom_generated_copy_dependency_to_tools_dir (TSLint.rul.md ESLint2Graph)
add_custom_generated_copy_dependency_to_tools_dir (TSLint.rul_metadata.md ESLint2Graph)
add_custom_generated_copy_dependency_to_tools_dir (LIM2Metrics${EXE})
add_custom_generated_copy_dependency_to_tools_dir (MET.rul.md LIM2Metrics)
add_custom_generated_copy_dependency_to_tools_dir (DuplicatedCodeFinder_javascript${EXE} DuplicatedCodeFinder_javascript DuplicatedCodeFinder${EXE})
add_custom_generated_copy_dependency_to_tools_dir (DCF.rul.md DuplicatedCodeFinder_javascript)
add_custom_generated_copy_dependency_to_tools_dir (MetricHunter_javascript${EXE} MetricHunter_javascript MetricHunter${EXE})
add_custom_generated_copy_dependency_to_tools_dir (MetricHunter_JAVASCRIPT.threshold MetricHunter_javascript_copy_MetricHunter_JAVASCRIPT.threshold MetricHunter.threshold)
add_custom_generated_copy_dependency_to_tools_dir (UserDefinedMetrics${EXE})
add_custom_generated_copy_dependency_to_tools_dir (Sonar2Graph${EXE})

#user's guide
add_custom_generated_copy_dependency(
    ${ANALYZER_TARGET_NAME}
    doc/usersguide
    ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}
    UsersGuide.html
    ${ANALYZER_TARGET_NAME}-UG
)


###Create demo 
#Copy demo analyze scripts
add_custom_copy_target (${ANALYZER_TARGET_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/demo/analyze${SCRIPT_EXT} ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/Demo/analyze${SCRIPT_EXT})

#Extract the demo project zip
add_custom_extract_target (
    ${ANALYZER_TARGET_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/demo/agenda.zip
    ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/Demo
    ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/Demo/agenda
)

copy_licenses()
