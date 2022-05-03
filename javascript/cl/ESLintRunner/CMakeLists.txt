set (PROGRAM_NAME eslintrunner)

add_custom_target (
    ${PROGRAM_NAME}_install
    COMMAND npm install > ${CMAKE_CURRENT_BINARY_DIR}/${PROGRAM_NAME}-npm-install.log 2>&1
    WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/tmp_${PROGRAM_NAME}
)

add_custom_copy_target(${PROGRAM_NAME}_install ${CMAKE_CURRENT_SOURCE_DIR} ${EXECUTABLE_OUTPUT_PATH}/tmp_${PROGRAM_NAME} DIRECTORY)
set_target_properties (${PROGRAM_NAME}_install PROPERTIES FOLDER ${CMAKE_SUPPORT_FOLDER_NAME})

add_custom_target (
    ${PROGRAM_NAME}_build
    COMMAND npm run build -- --no-color -o ${EXECUTABLE_OUTPUT_PATH}/node_modules/${PROGRAM_NAME} > ${CMAKE_CURRENT_BINARY_DIR}/${PROGRAM_NAME}-npm-build.log 2>&1
    DEPENDS ${PROGRAM_NAME}_install
    WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/tmp_${PROGRAM_NAME}
)

set_target_properties (${PROGRAM_NAME}_build PROPERTIES FOLDER ${CMAKE_SUPPORT_FOLDER_NAME})

add_custom_target(
    ${PROGRAM_NAME}_modules
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${EXECUTABLE_OUTPUT_PATH}/tmp_${PROGRAM_NAME}/node_modules/ ${EXECUTABLE_OUTPUT_PATH}/node_modules/${PROGRAM_NAME}/node_modules/
    DEPENDS ${PROGRAM_NAME}_build
)

add_custom_target (
    ${PROGRAM_NAME}_virtual_target
    # from cmake 3.17
    # COMMAND ${CMAKE_COMMAND} -E rm -rf ${EXECUTABLE_OUTPUT_PATH}/tmp_${PROGRAM_NAME}
    # until cmake 3.16
    COMMAND ${CMAKE_COMMAND} -E remove_directory -rf ${EXECUTABLE_OUTPUT_PATH}/tmp_${PROGRAM_NAME}
    DEPENDS ${PROGRAM_NAME}_modules
)

set_visual_studio_project_folder(${PROGRAM_NAME}_virtual_target TRUE)
