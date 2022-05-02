set (PACKAGE_LANG CPP)
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
      ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/${CMAKE_SYSTEM_NAME}Wrapper/WrapperBins/Tools/cppcheck
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

function (add_custom_generated_copy_dependency_to_cppcheck_dir SOURCE)
  add_custom_generated_copy_dependency(${ANALYZER_TARGET_NAME} ${COLUMBUS_3RDPARTY_INSTALL_DIR}/bin ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/${CMAKE_SYSTEM_NAME}Wrapper/WrapperBins/Tools/cppcheck ${ARGV})
endfunction ()

add_dependencies(${ANALYZER_TARGET_NAME} ${ANALYZER_COMMON_TARGET_NAME})

add_custom_generated_copy_dependency_to_root_dir (AnalyzerCPP${EXE})

add_custom_generated_copy_dependency_to_tools_dir (rules_cpp.csv AnalyzerCPP)
add_custom_generated_copy_dependency_to_tools_dir (general_metadata.md AnalyzerCPP)
add_custom_generated_copy_dependency_to_tools_dir (CAN2Lim${EXE})
add_custom_generated_copy_dependency_to_tools_dir (Cppcheck2Graph${EXE})
add_custom_generated_copy_dependency_to_tools_dir (Cppcheck.rul.md Cppcheck2Graph)
add_custom_generated_copy_dependency_to_tools_dir (Cppcheck.rul_metadata.md Cppcheck2Graph)
add_custom_generated_copy_dependency_to_tools_dir (DuplicatedCodeFinder_cpp${EXE} DuplicatedCodeFinder_cpp DuplicatedCodeFinder${EXE})
add_custom_generated_copy_dependency_to_tools_dir (DCF.rul.md DuplicatedCodeFinder_cpp)
add_custom_generated_copy_dependency_to_tools_dir (ClangTidy2Graph${EXE})
add_custom_generated_copy_dependency_to_tools_dir (ClangTidy.rul.md ClangTidy2Graph)
add_custom_generated_copy_dependency_to_tools_dir (ClangTidy.rul_metadata.md ClangTidy2Graph)
add_custom_generated_copy_dependency_to_tools_dir (GraphDump${EXE})
add_custom_generated_copy_dependency_to_tools_dir (GraphMerge${EXE})
add_custom_generated_copy_dependency_to_tools_dir (LIM2Metrics${EXE})
add_custom_generated_copy_dependency_to_tools_dir (MET.rul.md LIM2Metrics)
add_custom_generated_copy_dependency_to_tools_dir (MetricHunter_cpp${EXE} MetricHunter_cpp MetricHunter${EXE})
add_custom_generated_copy_dependency_to_tools_dir (MetricHunter_CPP.threshold MetricHunter_cpp_copy_MetricHunter_CPP.threshold MetricHunter.threshold)
add_custom_generated_copy_dependency_to_tools_dir (UserDefinedMetrics${EXE})
add_custom_generated_copy_dependency_to_tools_dir (Sonar2Graph${EXE})

if (CMAKE_SYSTEM_NAME STREQUAL Linux)
  add_custom_generated_copy_dependency_to_wrapper_dir (ArWrapper${EXE})
  add_custom_generated_copy_dependency_to_wrapper_dir (AsWrapper${EXE})
  add_custom_generated_copy_dependency_to_wrapper_dir (CopyMoveWrapper${EXE})
  add_custom_generated_copy_dependency_to_wrapper_dir (ClangWrapper${EXE})
  add_custom_generated_copy_dependency_to_wrapper_dir (LdWrapper${EXE})
  add_custom_generated_copy_dependency_to_wrapper_dir (LnWrapper${EXE})

elseif (CMAKE_SYSTEM_NAME STREQUAL Windows)
  add_custom_generated_copy_dependency_to_wrapper_dir (ClWrapper${EXE})
  add_custom_generated_copy_dependency_to_wrapper_dir (LibWrapper${EXE})
  add_custom_generated_copy_dependency_to_wrapper_dir (LinkWrapper${EXE})
  add_custom_generated_copy_dependency_to_wrapper_dir (VsbuildWrapper${EXE})
endif ()

add_custom_generated_copy_dependency_to_wrapper_dir (WrapperEnvironmentConfig${EXE})
add_custom_generated_copy_dependency_to_wrapper_dir (exewrapper${EXE})

add_custom_generated_copy_dependency_to_wrapper_tools_dir (AnalyzerWrapperConfig${EXE})
add_custom_generated_copy_dependency_to_wrapper_tools_dir (CAN${EXE})
add_custom_generated_copy_dependency_to_wrapper_tools_dir (CANConfig${EXE})
add_custom_generated_copy_dependency_to_wrapper_tools_dir (CANLib${EXE})
add_custom_generated_copy_dependency_to_wrapper_tools_dir (CANLink${EXE})

add_custom_generated_copy_dependency(${ANALYZER_TARGET_NAME} ${COLUMBUS_3RDPARTY_INSTALL_DIR}/lib ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/${CMAKE_SYSTEM_NAME}Wrapper/WrapperBins/Tools clang clang clang DIRECTORY)
add_custom_generated_copy_dependency(${ANALYZER_TARGET_NAME} ${COLUMBUS_3RDPARTY_INSTALL_DIR}/bin ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/${CMAKE_SYSTEM_NAME}Wrapper/WrapperBins/Tools clang-tidy${EXE} clang clang-tidy${EXE})


if (CMAKE_SYSTEM_NAME STREQUAL Windows)
  add_custom_generated_copy_dependency_to_wrapper_tools_dir (ParamCheck${EXE})
endif ()

add_custom_generated_copy_dependency(
    ${ANALYZER_TARGET_NAME}
    doc/usersguide
    ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}
    UsersGuide.html
    ${ANALYZER_TARGET_NAME}-UG
)


add_custom_copy_target (${ANALYZER_TARGET_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/demo/analyze${SCRIPT_EXT} ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/Demo/analyze${SCRIPT_EXT})

if (CMAKE_SYSTEM_NAME STREQUAL Linux)
  add_custom_copy_target (${ANALYZER_TARGET_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/demo/build${SCRIPT_EXT} ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/Demo/build${SCRIPT_EXT})
  add_custom_copy_target (${ANALYZER_TARGET_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/demo/softfilter-linux ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/Demo/softfilter)
elseif (CMAKE_SYSTEM_NAME STREQUAL Darwin)
  add_custom_copy_target (${ANALYZER_TARGET_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/demo/build${SCRIPT_EXT} ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/Demo/build${SCRIPT_EXT})
  add_custom_copy_target (${ANALYZER_TARGET_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/demo/softfilter-darwin ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/Demo/softfilter)
elseif (CMAKE_SYSTEM_NAME STREQUAL Windows)
  add_custom_copy_target (${ANALYZER_TARGET_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/demo/build-win-x64${SCRIPT_EXT} ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/Demo/build${SCRIPT_EXT})
  add_custom_copy_target (${ANALYZER_TARGET_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/demo/softfilter-windows ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/Demo/softfilter)
endif ()

add_custom_extract_target (
    ${ANALYZER_TARGET_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/demo/log4cplus-1.1.0.zip
    ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/Demo
    ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/Demo/log4cplus-1.1.0
)

add_custom_generated_copy_dependency(${ANALYZER_TARGET_NAME} ${COLUMBUS_3RDPARTY_INSTALL_DIR}/bin ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/${CMAKE_SYSTEM_NAME}Wrapper/WrapperBins/Tools/cppcheck cppcheck${EXE})
add_custom_generated_copy_dependency(${ANALYZER_TARGET_NAME} ${COLUMBUS_3RDPARTY_INSTALL_DIR}/share/Cppcheck ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/${CMAKE_SYSTEM_NAME}Wrapper/WrapperBins/Tools/cppcheck cfg cppcheck cfg DIRECTORY)
