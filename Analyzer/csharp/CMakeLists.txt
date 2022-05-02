set (PACKAGE_LANG CSharp)
set (ANALYZER_TARGET_NAME AN-${PACKAGE_LANG})

add_subdirectory (doc/usersguide)

add_custom_target (
  ${ANALYZER_TARGET_NAME}
)

set_visual_studio_project_folder(${ANALYZER_TARGET_NAME} FALSE)

file (MAKE_DIRECTORY
  ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/Demo
  ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/${CMAKE_SYSTEM_NAME}Tools
)

# These functions copy the SOURCE file into different directories of the Analyzer package.
# The second parameter is optional. You can set the name of the target, which will be used for generating the SOURCE.
# The third parameter is also optional. You can set a different name for the SOURCE on which the file will be created in the tools directory.
function (add_custom_generated_copy_dependency_to_root_dir SOURCE)
  add_custom_generated_copy_dependency(${ANALYZER_TARGET_NAME} ${EXECUTABLE_OUTPUT_PATH} ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG} ${ARGV})
endfunction ()

function (add_custom_generated_copy_dependency_to_tools_dir SOURCE)
  add_custom_generated_copy_dependency(${ANALYZER_TARGET_NAME} ${EXECUTABLE_OUTPUT_PATH} ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/${CMAKE_SYSTEM_NAME}Tools ${ARGV})
endfunction ()

add_dependencies(${ANALYZER_TARGET_NAME} ${ANALYZER_COMMON_TARGET_NAME})

add_custom_generated_copy_dependency_to_root_dir (AnalyzerCSharp${EXE})

add_custom_generated_copy_dependency_to_tools_dir (rules_csharp.csv AnalyzerCSharp)
add_custom_generated_copy_dependency_to_tools_dir (general_metadata.md AnalyzerCSharp)
add_custom_generated_copy_dependency_to_tools_dir (DuplicatedCodeFinder_csharp${EXE} DuplicatedCodeFinder_csharp DuplicatedCodeFinder${EXE})
add_custom_generated_copy_dependency_to_tools_dir (DCF.rul.md DuplicatedCodeFinder_csharp)
if (CMAKE_SYSTEM_NAME STREQUAL Windows)
  add_custom_generated_copy_dependency_to_tools_dir (FxCop2Graph${EXE})
  add_custom_generated_copy_dependency_to_tools_dir (FxCop.rul.md FxCop2Graph)
  add_custom_generated_copy_dependency_to_tools_dir (FxCop.rul_metadata.md FxCop2Graph)
endif ()
add_custom_generated_copy_dependency_to_tools_dir (GraphDump${EXE})
add_custom_generated_copy_dependency_to_tools_dir (GraphMerge${EXE})
add_custom_generated_copy_dependency_to_tools_dir (LIM2Metrics${EXE})
add_custom_generated_copy_dependency_to_tools_dir (MET.rul.md LIM2Metrics)
add_custom_generated_copy_dependency_to_tools_dir (MetricHunter_csharp${EXE} MetricHunter_csharp MetricHunter${EXE})
add_custom_generated_copy_dependency_to_tools_dir (MetricHunter_CSHARP.threshold MetricHunter_csharp_copy_MetricHunter_CSHARP.threshold MetricHunter.threshold)
add_custom_generated_copy_dependency_to_tools_dir (UserDefinedMetrics${EXE})
add_custom_generated_copy_dependency_to_tools_dir (Sonar2Graph${EXE})
add_custom_generated_copy_dependency_to_tools_dir (Roslyn2Graph${EXE})

foreach (BINARY ${CSAN_BINARIES})
  add_custom_generated_copy_dependency_to_tools_dir (${BINARY} CSAN_virtual_target)
endforeach()


add_custom_generated_copy_dependency(
  ${ANALYZER_TARGET_NAME}
  doc/usersguide
  ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}
  UsersGuide.html
  ${ANALYZER_TARGET_NAME}-UG
)


set (DEMO_SCRIPTS_AND_FILES
  analyze${SCRIPT_EXT}
  softfilter
  hardfilter
)

add_prefix(DEMO_SCRIPTS_AND_FILES ${CMAKE_CURRENT_SOURCE_DIR}/demo/)

add_custom_copy_list_target (
  ${ANALYZER_TARGET_NAME}
  DemoFiles
  DEMO_SCRIPTS_AND_FILES
  ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/Demo
)

add_custom_extract_target (
  ${ANALYZER_TARGET_NAME}
  ${CMAKE_CURRENT_SOURCE_DIR}/demo/log4net-2.0.10.zip
  ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/Demo
  ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/Demo/log4net-2.0.10
)

copy_licenses()
