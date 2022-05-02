set (PROGRAM_NAME eslintrunner)

add_copy_custom_target_dir (${PROGRAM_NAME}_copy_sources ${CMAKE_CURRENT_SOURCE_DIR} ${EXECUTABLE_OUTPUT_PATH}/tmp_${PROGRAM_NAME})

add_custom_command (
    OUTPUT ${EXECUTABLE_OUTPUT_PATH}/node_modules/${PROGRAM_NAME}
    COMMAND ${CALL} npm install > ${CMAKE_CURRENT_BINARY_DIR}/${PROGRAM_NAME}-npm-install.log 2>&1
    COMMAND ${CALL} npm run build -- --no-color -o ${EXECUTABLE_OUTPUT_PATH}/node_modules/${PROGRAM_NAME} > ${CMAKE_CURRENT_BINARY_DIR}/${PROGRAM_NAME}-npm-build.log 2>&1
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${EXECUTABLE_OUTPUT_PATH}/tmp_${PROGRAM_NAME}/node_modules/ ${EXECUTABLE_OUTPUT_PATH}/node_modules/${PROGRAM_NAME}/node_modules/
    WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/tmp_${PROGRAM_NAME}
    DEPENDS ${EXECUTABLE_OUTPUT_PATH}/tmp_${PROGRAM_NAME}
    COMMENT "Rebuilding ${PROGRAM_NAME}"
)


add_custom_target (
    ${PROGRAM_NAME}_virtual_target
    DEPENDS ${EXECUTABLE_OUTPUT_PATH}/node_modules/${PROGRAM_NAME}
)

set_visual_studio_project_folder(${PROGRAM_NAME}_virtual_target TRUE)
