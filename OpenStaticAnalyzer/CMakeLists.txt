set (OSA_PACKAGE_NAME OpenStaticAnalyzer-${PROJECT_VERSION}-${COLUMBUS_PLATFORM_NAME}-${CMAKE_SYSTEM_NAME})
set (OSA_PACKAGE_DIR ${CMAKE_CURRENT_BINARY_DIR}/${OSA_PACKAGE_NAME})
set (OSA_PACKAGE_DIR ${CMAKE_CURRENT_BINARY_DIR}/${OSA_PACKAGE_NAME} PARENT_SCOPE)

set (OSA_TARGET_NAME OpenStaticAnalyzer-Package)

if (CMAKE_SYSTEM_NAME STREQUAL Windows)
  set (COMPRESS_COMMAND tar cf ${OSA_PACKAGE_NAME}.zip --format=zip ${OSA_PACKAGE_NAME})
elseif (CMAKE_SYSTEM_NAME STREQUAL Linux)
  set (COMPRESS_COMMAND tar czf ${OSA_PACKAGE_NAME}.tgz ${OSA_PACKAGE_NAME})
endif ()

add_custom_target (
    ${OSA_TARGET_NAME}
    DEPENDS OSA-Java
    DEPENDS OSA-CPP
    DEPENDS OSA-Python
    DEPENDS OSA-CSharp
    DEPENDS OSA-JavaScript
    COMMAND ${CMAKE_COMMAND} -E ${COMPRESS_COMMAND}
)

set_visual_studio_project_folder(${OSA_TARGET_NAME} FALSE)

set (DOC_FILES
    readme.txt
)

add_prefix(DOC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/doc/)

add_custom_copy_list_target (${OSA_TARGET_NAME}
                             DocFiles
                             DOC_FILES
                             ${OSA_PACKAGE_DIR}
)


add_custom_generated_copy_dependency (${OSA_TARGET_NAME} ${CMAKE_BINARY_DIR}/java/lib/bin ${OSA_PACKAGE_DIR}/GraphAPI/Graphlib graphlib.jar java_graphlib)
add_custom_generated_copy_dependency (${OSA_TARGET_NAME} ${CMAKE_BINARY_DIR}/java/lib/graphlib/build ${OSA_PACKAGE_DIR}/GraphAPI/Graphlib doc java_graphlib doc DIRECTORY)
add_custom_generated_copy_dependency (${OSA_TARGET_NAME} ${CMAKE_BINARY_DIR}/java/lib/bin ${OSA_PACKAGE_DIR}/GraphAPI/Graphsupportlib graphsupportlib.jar java_graphsupportlib)
#add_custom_generated_copy_dependency (${OSA_TARGET_NAME} ${CMAKE_BINARY_DIR}/java/lib/graphsupport/build ${OSA_PACKAGE_DIR}/GraphAPI/Graphsupportlib doc java_graphsupportlib DIRECTORY)
add_custom_copy_target (${OSA_TARGET_NAME} ${CMAKE_SOURCE_DIR}/java/cl/GraphExample/src ${OSA_PACKAGE_DIR}/GraphAPI/GraphExample/src DIRECTORY)
add_custom_copy_target (${OSA_TARGET_NAME} ${CMAKE_SOURCE_DIR}/java/cl/GraphExample/build_openstaticanalyzer_package.xml ${OSA_PACKAGE_DIR}/GraphAPI/GraphExample/build.xml)

function (copy_licenses)
  file (GLOB LICENSE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Licenses/*)

  add_custom_copy_list_target (
    ${OSA_TARGET_NAME}
    Licenses
    LICENSE_FILES
    ${OSA_PACKAGE_DIR}/Licenses
  )
endfunction ()

add_subdirectory (cpp)
add_subdirectory (java)
add_subdirectory (python)
add_subdirectory (csharp)
add_subdirectory (javascript)

copy_licenses()
