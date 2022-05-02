set (PROGRAM_NAME jsan)

add_copy_custom_target_dir (${PROGRAM_NAME}_copy_sources ${CMAKE_CURRENT_SOURCE_DIR} ${EXECUTABLE_OUTPUT_PATH}/tmp_${PROGRAM_NAME})

add_custom_command (
    OUTPUT ${EXECUTABLE_OUTPUT_PATH}/node_modules/${PROGRAM_NAME}
    COMMAND ${CMAKE_COMMAND} -E copy ${EXECUTABLE_OUTPUT_PATH}/javascriptAddon.node ${EXECUTABLE_OUTPUT_PATH}/tmp_${PROGRAM_NAME}/
    COMMAND ${CALL} npm install ${MSVS_VERSION} > ${CMAKE_CURRENT_BINARY_DIR}/${PROGRAM_NAME}-npm-install.log 2>&1
    COMMAND ${CALL} npm run build -- --no-color -o ${EXECUTABLE_OUTPUT_PATH}/node_modules/${PROGRAM_NAME} > ${CMAKE_CURRENT_BINARY_DIR}/${PROGRAM_NAME}-npm-build.log 2>&1
    WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/tmp_${PROGRAM_NAME}
    DEPENDS javascriptAddon ${EXECUTABLE_OUTPUT_PATH}/tmp_${PROGRAM_NAME}
    COMMENT "Rebuilding ${PROGRAM_NAME}"
)


add_custom_target (
    ${PROGRAM_NAME}_virtual_target
    DEPENDS ${EXECUTABLE_OUTPUT_PATH}/node_modules/${PROGRAM_NAME} javascriptAddon
)


set_visual_studio_project_folder(${PROGRAM_NAME}_virtual_target TRUE)
