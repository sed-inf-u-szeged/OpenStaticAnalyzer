
set (TEMP_BUILD_INFO_FILE ${CMAKE_BINARY_DIR}/BuildInfo-temp.txt)

add_custom_target (
  generate_build_info ALL
  COMMAND git rev-parse --short HEAD > ${TEMP_BUILD_INFO_FILE}
  COMMAND ${CMAKE_COMMAND} -DBINARY_DIR=${CMAKE_BINARY_DIR} -P ${CMAKE_MODULE_PATH}/GenerateBuildInfoH.cmake
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

set_target_properties (generate_build_info PROPERTIES FOLDER ${CMAKE_SUPPORT_FOLDER_NAME})



