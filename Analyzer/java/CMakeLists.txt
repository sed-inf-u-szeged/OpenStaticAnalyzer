set (PACKAGE_LANG Java)
set (ANALYZER_TARGET_NAME AN-${PACKAGE_LANG})

add_subdirectory (doc/usersguide)

add_custom_target (
    ${ANALYZER_TARGET_NAME}
)
set_visual_studio_project_folder(${ANALYZER_TARGET_NAME} FALSE)

file (MAKE_DIRECTORY
      ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/Demo
      ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/${CMAKE_SYSTEM_NAME}Tools
      ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/${CMAKE_SYSTEM_NAME}Wrapper/WrapperBins/Tools
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

function (add_custom_generated_copy_dependency_to_wrapper_dir SOURCE)
  add_custom_generated_copy_dependency(${ANALYZER_TARGET_NAME} ${EXECUTABLE_OUTPUT_PATH} ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/${CMAKE_SYSTEM_NAME}Wrapper/WrapperBins ${ARGV})
endfunction ()

function (add_custom_generated_copy_dependency_to_wrapper_tools_dir SOURCE)
  add_custom_generated_copy_dependency(${ANALYZER_TARGET_NAME} ${EXECUTABLE_OUTPUT_PATH} ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/${CMAKE_SYSTEM_NAME}Wrapper/WrapperBins/Tools ${ARGV})
endfunction ()

add_dependencies(${ANALYZER_TARGET_NAME} ${ANALYZER_COMMON_TARGET_NAME})

add_custom_generated_copy_dependency_to_root_dir (AnalyzerJava${EXE})

add_custom_generated_copy_dependency_to_tools_dir (rules_java.csv AnalyzerJava)
add_custom_generated_copy_dependency_to_tools_dir (general_metadata.md CommonTagMetadata_copy_general_metadata.md)
add_custom_generated_copy_dependency_to_tools_dir (cwe_metadata.md CommonTagMetadata_copy_cwe_metadata.md)
add_custom_generated_copy_dependency_to_tools_dir (owasp_metadata.md CommonTagMetadata_copy_owasp_metadata.md)
add_custom_generated_copy_dependency_to_tools_dir (sei_cert_metadata.md CommonTagMetadata_copy_sei_cert_metadata.md)
add_custom_generated_copy_dependency_to_tools_dir (DuplicatedCodeFinder_java${EXE} DuplicatedCodeFinder_java DuplicatedCodeFinder${EXE})
add_custom_generated_copy_dependency_to_tools_dir (DCF.rul.md DuplicatedCodeFinder_java)
add_custom_generated_copy_dependency_to_tools_dir (FindBugs2Graph${EXE})
add_custom_generated_copy_dependency_to_tools_dir (FindBugs.rul.md FindBugs2Graph_copy_FindBugs.rul.md)
add_custom_generated_copy_dependency_to_tools_dir (FindBugs.rul_metadata.md FindBugs2Graph_copy_FindBugs.rul_metadata.md)
add_custom_generated_copy_dependency_to_tools_dir (GraphDump${EXE})
add_custom_generated_copy_dependency_to_tools_dir (GraphMerge${EXE})
add_custom_generated_copy_dependency_to_tools_dir (JAN2ChangePath${EXE})
add_custom_generated_copy_dependency_to_tools_dir (JAN2Lim${EXE})
add_custom_generated_copy_dependency_to_tools_dir (JANFilter${EXE})
add_custom_generated_copy_dependency_to_tools_dir (LIM2Metrics${EXE})
add_custom_generated_copy_dependency_to_tools_dir (MET.rul.md LIM2Metrics)
add_custom_generated_copy_dependency_to_tools_dir (MetricHunter_java${EXE} MetricHunter_java MetricHunter${EXE})
add_custom_generated_copy_dependency_to_tools_dir (MetricHunter_JAVA.threshold MetricHunter_java_copy_MetricHunter_JAVA.threshold MetricHunter.threshold)
add_custom_generated_copy_dependency_to_tools_dir (PMD2Graph${EXE})
add_custom_generated_copy_dependency_to_tools_dir (PMD.rul.md PMD2Graph)
add_custom_generated_copy_dependency_to_tools_dir (PMD.rul_metadata.md PMD2Graph_copy_PMD.rul_metadata.md)
add_custom_generated_copy_dependency_to_tools_dir (UserDefinedMetrics${EXE})
add_custom_generated_copy_dependency_to_tools_dir (Sonar2Graph${EXE})
add_custom_generated_copy_dependency_to_tools_dir (sonar_tag_metadata.md Sonar2Graph_copy_sonar_tag_metadata.md)

add_custom_generated_copy_dependency_to_wrapper_tools_dir (GenericConfig${EXE})
add_custom_generated_copy_dependency_to_wrapper_tools_dir (JAN.jar JAN)
add_custom_generated_copy_dependency_to_wrapper_tools_dir (jdk.compiler.jar JAN)
add_custom_generated_copy_dependency_to_wrapper_tools_dir (toolchain.ini JAN)

add_custom_generated_copy_dependency(
    ${ANALYZER_TARGET_NAME}
    doc/usersguide
    ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}
    UsersGuide.html
    ${ANALYZER_TARGET_NAME}-UG
)

add_custom_generated_copy_dependency(
    ${ANALYZER_TARGET_NAME}
    ${EXECUTABLE_OUTPUT_PATH}
    ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/${CMAKE_SYSTEM_NAME}Wrapper/WrapperBins/Tools/PMD
    PMD-config.xml
    PMD2Graph
)

set (DEMO_SCRIPTS_AND_FILES
    analyze-dir${SCRIPT_EXT}
    SoftFilter.txt
    fbfilelist.txt
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
    ${CMAKE_CURRENT_SOURCE_DIR}/demo/log4j-1.2.17.zip
    ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/Demo
    ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/Demo/apache-log4j-1.2.17
)

add_custom_extract_target (
    ${ANALYZER_TARGET_NAME}
    ${COLUMBUS_3RDPARTY_INSTALL_DIR}/spotbugs.zip
    ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/${CMAKE_SYSTEM_NAME}Wrapper/WrapperBins/Tools
    ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/${CMAKE_SYSTEM_NAME}Wrapper/WrapperBins/Tools/spotbugs/bin
    spotbugs
)

add_custom_extract_target (
    ${ANALYZER_TARGET_NAME}
    ${COLUMBUS_3RDPARTY_INSTALL_DIR}/PMD.zip
    ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/${CMAKE_SYSTEM_NAME}Wrapper/WrapperBins/Tools
    ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/${CMAKE_SYSTEM_NAME}Wrapper/WrapperBins/Tools/PMD/bin
    PMD
)

copy_licenses()
