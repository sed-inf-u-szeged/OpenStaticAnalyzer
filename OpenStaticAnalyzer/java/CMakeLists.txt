set (PACKAGE_LANG Java)
set (OSA_TARGET_NAME OSA-${PACKAGE_LANG})

add_subdirectory (doc/usersguide)

add_custom_target (
    ${OSA_TARGET_NAME}
)
set_visual_studio_project_folder(${OSA_TARGET_NAME} FALSE)

file (MAKE_DIRECTORY
      ${OSA_PACKAGE_DIR}/${PACKAGE_LANG}/Demo
      ${OSA_PACKAGE_DIR}/${PACKAGE_LANG}/${CMAKE_SYSTEM_NAME}Tools
      ${OSA_PACKAGE_DIR}/${PACKAGE_LANG}/${CMAKE_SYSTEM_NAME}Wrapper/WrapperBins/Tools
      ${OSA_PACKAGE_DIR}/${PACKAGE_LANG}/${CMAKE_SYSTEM_NAME}Wrapper/WrapperBins/Tools/PMD
)

# These functions copy the SOURCE file into different directories of the OpenStaticAnalyzer package.
# The second parameter is optional. You can set the name of the target, which will be used for generating the SOURCE.
# The third parameter is also optional. You can set a different name for the SOURCE on which the file will be created in the tools directory.
function (add_custom_generated_copy_dependency_to_root_dir SOURCE)
  add_custom_generated_copy_dependency(${OSA_TARGET_NAME} ${EXECUTABLE_OUTPUT_PATH} ${OSA_PACKAGE_DIR}/${PACKAGE_LANG} ${ARGV})
endfunction ()

function (add_custom_generated_copy_dependency_to_tools_dir SOURCE)
  add_custom_generated_copy_dependency(${OSA_TARGET_NAME} ${EXECUTABLE_OUTPUT_PATH} ${OSA_PACKAGE_DIR}/${PACKAGE_LANG}/${CMAKE_SYSTEM_NAME}Tools ${ARGV})
endfunction ()

function (add_custom_generated_copy_dependency_to_wrapper_dir SOURCE)
  add_custom_generated_copy_dependency(${OSA_TARGET_NAME} ${EXECUTABLE_OUTPUT_PATH} ${OSA_PACKAGE_DIR}/${PACKAGE_LANG}/${CMAKE_SYSTEM_NAME}Wrapper/WrapperBins ${ARGV})
endfunction ()

function (add_custom_generated_copy_dependency_to_wrapper_tools_dir SOURCE)
  add_custom_generated_copy_dependency(${OSA_TARGET_NAME} ${EXECUTABLE_OUTPUT_PATH} ${OSA_PACKAGE_DIR}/${PACKAGE_LANG}/${CMAKE_SYSTEM_NAME}Wrapper/WrapperBins/Tools ${ARGV})
endfunction ()

add_custom_generated_copy_dependency_to_root_dir (OpenStaticAnalyzerJava${EXE})

add_custom_generated_copy_dependency_to_tools_dir (rules_java.csv OpenStaticAnalyzerJava)
add_custom_generated_copy_dependency_to_tools_dir (DuplicatedCodeFinder_java${EXE} DuplicatedCodeFinder_java DuplicatedCodeFinder${EXE})
add_custom_generated_copy_dependency_to_tools_dir (DCF.rul DuplicatedCodeFinder_java_copy_DCF.rul)
add_custom_generated_copy_dependency_to_tools_dir (FindBugs2Graph${EXE})
add_custom_generated_copy_dependency_to_tools_dir (FindBugs.rul FindBugs2Graph_copy_FindBugs.rul)
add_custom_generated_copy_dependency_to_tools_dir (GraphDump${EXE})
add_custom_generated_copy_dependency_to_tools_dir (GraphMerge${EXE})
add_custom_generated_copy_dependency_to_tools_dir (JAN2ChangePath${EXE})
add_custom_generated_copy_dependency_to_tools_dir (JAN2Lim${EXE})
add_custom_generated_copy_dependency_to_tools_dir (JANFilter${EXE})
add_custom_generated_copy_dependency_to_tools_dir (LIM2Metrics${EXE})
add_custom_generated_copy_dependency_to_tools_dir (MET.rul LIM2Metrics)
add_custom_generated_copy_dependency_to_tools_dir (MetricHunter_java${EXE} MetricHunter_java MetricHunter${EXE})
add_custom_generated_copy_dependency_to_tools_dir (MetricHunter_JAVA.threshold MetricHunter_java_copy_MetricHunter_JAVA.threshold MetricHunter.threshold)
add_custom_generated_copy_dependency_to_tools_dir (PMD2Graph${EXE})
add_custom_generated_copy_dependency_to_tools_dir (PMD.rul PMD2Graph)

add_custom_generated_copy_dependency_to_wrapper_dir (AntWrapper${EXE})
add_custom_generated_copy_dependency_to_wrapper_dir (EnvironmentSetup${EXE})
add_custom_generated_copy_dependency_to_wrapper_dir (JarWrapper${EXE})
add_custom_generated_copy_dependency_to_wrapper_dir (JavacWrapper${EXE})
add_custom_generated_copy_dependency_to_wrapper_dir (WrapperEnvironmentConfig${EXE})
add_custom_generated_copy_dependency_to_wrapper_dir (exewrapper${EXE})

add_custom_generated_copy_dependency_to_wrapper_tools_dir (JANLink${EXE})
add_custom_generated_copy_dependency_to_wrapper_tools_dir (GenericConfig${EXE})

add_custom_generated_copy_dependency_to_wrapper_tools_dir (JAN.jar JAN)
add_custom_generated_copy_dependency_to_wrapper_tools_dir (toolchain.ini JAN)

add_custom_generated_copy_dependency_to_wrapper_tools_dir (JColumbusAntWrapper.jar JColumbusAntWrapper)

add_custom_generated_copy_dependency(
    ${OSA_TARGET_NAME}
    doc/usersguide
    ${OSA_PACKAGE_DIR}/${PACKAGE_LANG}
    UsersGuide.html
    ${OSA_TARGET_NAME}-UG
)

add_custom_generated_copy_dependency(
    ${OSA_TARGET_NAME}
    ${EXECUTABLE_OUTPUT_PATH}
    ${OSA_PACKAGE_DIR}/${PACKAGE_LANG}/${CMAKE_SYSTEM_NAME}Wrapper/WrapperBins/Tools/PMD
    PMD-config.xml
    PMD2Graph
)

set (DEMO_SCRIPTS_AND_FILES
    analyze-ant${SCRIPT_EXT}
    analyze-dir${SCRIPT_EXT}
    analyze-maven${SCRIPT_EXT}
    build-ant${SCRIPT_EXT}
    build-maven${SCRIPT_EXT}
    SoftFilter.txt
    fbfilelist.txt
)

add_prefix(DEMO_SCRIPTS_AND_FILES ${CMAKE_CURRENT_SOURCE_DIR}/demo/)

add_custom_copy_list_target (
    ${OSA_TARGET_NAME}
    DemoFiles
    DEMO_SCRIPTS_AND_FILES
    ${OSA_PACKAGE_DIR}/${PACKAGE_LANG}/Demo
)

add_custom_extract_target (
    ${OSA_TARGET_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/demo/log4j-1.2.17.zip
    ${OSA_PACKAGE_DIR}/${PACKAGE_LANG}/Demo
    ${OSA_PACKAGE_DIR}/${PACKAGE_LANG}/Demo/apache-log4j-1.2.17
)

add_custom_extract_target (
    ${OSA_TARGET_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/demo/log4j-2.3-src.zip
    ${OSA_PACKAGE_DIR}/${PACKAGE_LANG}/Demo
    ${OSA_PACKAGE_DIR}/${PACKAGE_LANG}/Demo/apache-log4j-2.3-src
)

add_custom_extract_target (
    ${OSA_TARGET_NAME}
    ${COLUMBUS_3RDPARTY_SOURCE_DIR}/findbugs/findbugs-3.0.0.tar.gz
    ${OSA_PACKAGE_DIR}/${PACKAGE_LANG}/${CMAKE_SYSTEM_NAME}Wrapper/WrapperBins/Tools
    ${OSA_PACKAGE_DIR}/${PACKAGE_LANG}/${CMAKE_SYSTEM_NAME}Wrapper/WrapperBins/Tools/findbugs-3.0.0
)

add_custom_extract_target (
    ${OSA_TARGET_NAME}
    ${COLUMBUS_3RDPARTY_INSTALL_DIR}/PMD.zip
    ${OSA_PACKAGE_DIR}/${PACKAGE_LANG}/${CMAKE_SYSTEM_NAME}Wrapper/WrapperBins/Tools
    ${OSA_PACKAGE_DIR}/${PACKAGE_LANG}/${CMAKE_SYSTEM_NAME}Wrapper/WrapperBins/Tools/PMD/bin
    PMD
)

set (WRAPPER_TOOLS_DIR ${OSA_PACKAGE_DIR}/${PACKAGE_LANG}/${CMAKE_SYSTEM_NAME}Wrapper/WrapperBins/Tools)
set (MAVEN_PLUGIN_DIR ${CMAKE_SOURCE_DIR}/java/columbus-toolchain-maven-plugin)

add_custom_create_file_target (
    ${OSA_TARGET_NAME}
    ${WRAPPER_TOOLS_DIR}/OpenStaticAnalyzer-maven-plugin-3.0.jar
    ${WRAPPER_TOOLS_DIR}/OpenStaticAnalyzer-Maven-plugin-mojo-executer-2.2.1.jar
    ${WRAPPER_TOOLS_DIR}/OpenStaticAnalyzer-Maven-plugin-mojo-executer-2.2.1.pom
    ${WRAPPER_TOOLS_DIR}/OpenStaticAnalyzer-Maven-plugin-mojo-executer-3.0.jar
    ${WRAPPER_TOOLS_DIR}/OpenStaticAnalyzer-Maven-plugin-mojo-executer-3.0.pom
    ${WRAPPER_TOOLS_DIR}/OpenStaticAnalyzer-Maven-plugin-mojo-executer-3.1.jar
    ${WRAPPER_TOOLS_DIR}/OpenStaticAnalyzer-Maven-plugin-mojo-executer-3.1.pom
    ${WRAPPER_TOOLS_DIR}/OpenStaticAnalyzer-maven-plugin-3.0-V2.pom
    ${WRAPPER_TOOLS_DIR}/OpenStaticAnalyzer-maven-plugin-3.0-V3.pom
    ${WRAPPER_TOOLS_DIR}/OpenStaticAnalyzer-maven-plugin-3.0-V31.pom
    ${OSA_PACKAGE_DIR}/${PACKAGE_LANG}/installMavenWrapper${SCRIPT_EXT}
    COMMAND mvn${MVN_POSTFIX} install -f ${MAVEN_PLUGIN_DIR}/ext/mojoExecutorModule/v3/pom.xml > ${CMAKE_CURRENT_BINARY_DIR}/v3install.log
    COMMAND mvn${MVN_POSTFIX} install -f ${MAVEN_PLUGIN_DIR}/ext/mojoExecutorModule/v31/pom.xml > ${CMAKE_CURRENT_BINARY_DIR}/v31install.log
    COMMAND ${CMAKE_COMMAND} -E env OSA_DIR=${OSA_PACKAGE_DIR}/${PACKAGE_LANG} mvn${MVN_POSTFIX} install -f ${MAVEN_PLUGIN_DIR}/pom.xml > ${CMAKE_CURRENT_BINARY_DIR}/plugininstall.log
)


copy_licenses()
