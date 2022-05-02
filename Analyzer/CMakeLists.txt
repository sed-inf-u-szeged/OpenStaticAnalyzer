set (ANALYZER_PACKAGE_NAME OpenStaticAnalyzer-${PROJECT_VERSION}-${COLUMBUS_PLATFORM_NAME}-${CMAKE_SYSTEM_NAME})
set (ANALYZER_PACKAGE_DIR ${CMAKE_CURRENT_BINARY_DIR}/${ANALYZER_PACKAGE_NAME})
set (ANALYZER_PACKAGE_DIR ${CMAKE_CURRENT_BINARY_DIR}/${ANALYZER_PACKAGE_NAME} PARENT_SCOPE)
set (ANALYZER_COMMON_TARGET_NAME  Analyzer-Common)

set (ANALYZER_TARGET_NAME Analyzer-Package)



function (add_custom_generated_copy_dependency_to_common_dir)
  add_custom_generated_copy_dependency(${ANALYZER_COMMON_TARGET_NAME} ${EXECUTABLE_OUTPUT_PATH} ${ANALYZER_PACKAGE_DIR}/${PACKAGE_LANG}/Common ${ARGV})
endfunction ()

add_custom_target (
    ${ANALYZER_COMMON_TARGET_NAME}
)
set_target_properties (${ANALYZER_COMMON_TARGET_NAME} PROPERTIES FOLDER ${CMAKE_SUPPORT_FOLDER_NAME})

add_custom_generated_copy_dependency_to_common_dir(python-modules python3.8 python-modules DIRECTORY)
add_custom_generated_copy_dependency_to_common_dir(LIM2Patterns${EXE})
add_custom_generated_copy_dependency_to_common_dir(Patterns LIM2Patterns Patterns DIRECTORY)

if (CMAKE_SYSTEM_NAME STREQUAL Windows)
  set (COMPRESS_COMMAND tar cf ${ANALYZER_PACKAGE_NAME}.zip --format=zip ${ANALYZER_PACKAGE_NAME})
elseif (CMAKE_SYSTEM_NAME STREQUAL Linux)
  set (COMPRESS_COMMAND tar czf ${ANALYZER_PACKAGE_NAME}.tgz ${ANALYZER_PACKAGE_NAME})
endif ()

add_custom_target (
    ${ANALYZER_TARGET_NAME}
    DEPENDS AN-Java
    DEPENDS AN-CPP
    DEPENDS AN-Python
    DEPENDS AN-CSharp
    DEPENDS AN-JavaScript
    COMMAND ${CMAKE_COMMAND} -E ${COMPRESS_COMMAND}
)


set_visual_studio_project_folder(${ANALYZER_TARGET_NAME} FALSE)

set (DOC_FILES
    readme.txt
)

add_prefix(DOC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/doc/)

add_custom_copy_list_target (${ANALYZER_TARGET_NAME}
                             DocFiles
                             DOC_FILES
                             ${ANALYZER_PACKAGE_DIR}
)

add_custom_generated_copy_dependency (${ANALYZER_TARGET_NAME} ${CMAKE_BINARY_DIR}/java/lib/bin ${ANALYZER_PACKAGE_DIR}/GraphAPI/Graphlib graphlib.jar java_graphlib)
add_custom_generated_copy_dependency (${ANALYZER_TARGET_NAME} ${CMAKE_BINARY_DIR}/java/lib/graphlib/build ${ANALYZER_PACKAGE_DIR}/GraphAPI/Graphlib doc java_graphlib doc DIRECTORY)
add_custom_generated_copy_dependency (${ANALYZER_TARGET_NAME} ${CMAKE_BINARY_DIR}/java/lib/bin ${ANALYZER_PACKAGE_DIR}/GraphAPI/Graphsupportlib graphsupportlib.jar java_graphsupportlib)
#add_custom_generated_copy_dependency (${ANALYZER_TARGET_NAME} ${CMAKE_BINARY_DIR}/java/lib/graphsupport/build ${ANALYZER_PACKAGE_DIR}/GraphAPI/Graphsupportlib doc java_graphsupportlib DIRECTORY)
add_custom_copy_target (${ANALYZER_TARGET_NAME} ${CMAKE_SOURCE_DIR}/java/cl/GraphExample/src ${ANALYZER_PACKAGE_DIR}/GraphAPI/GraphExample/src DIRECTORY)
add_custom_copy_target (${ANALYZER_TARGET_NAME} ${CMAKE_SOURCE_DIR}/java/cl/GraphExample/build_package.xml ${ANALYZER_PACKAGE_DIR}/GraphAPI/GraphExample/build.xml)

function (copy_licenses)
  file (GLOB LICENSE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Licenses/*)

  add_custom_copy_list_target (
    ${ANALYZER_TARGET_NAME}
    Licenses
    LICENSE_FILES
    ${ANALYZER_PACKAGE_DIR}/Licenses
  )
endfunction ()

add_subdirectory (common)
add_subdirectory (cpp)
add_subdirectory (java)
add_subdirectory (python)
add_subdirectory (csharp)
add_subdirectory (javascript)

copy_licenses()
