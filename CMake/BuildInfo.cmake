
set (BUILD_INFO_FILE ${CMAKE_BINARY_DIR}/BuildInfo.txt)
set (BUILD_INFO_H_FILE ${CMAKE_BINARY_DIR}/BuildInfo.h)

add_custom_command (
  OUTPUT ${BUILD_INFO_FILE} ${BUILD_INFO_H_FILE}
  COMMAND git rev-parse --short HEAD > ${BUILD_INFO_FILE}
  COMMAND ${CMAKE_COMMAND} -DBINARY_DIR=${CMAKE_BINARY_DIR} -P ${CMAKE_MODULE_PATH}/GenerateBuildInfoH.cmake
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  DEPENDS ${CMAKE_SOURCE_DIR}/.git/HEAD
)

add_custom_target (
  generate_build_info ALL
  DEPENDS ${BUILD_INFO_FILE} ${BUILD_INFO_H_FILE}
)

set_target_properties (generate_build_info PROPERTIES FOLDER ${CMAKE_SUPPORT_FOLDER_NAME})



