set (PROGRAM_NAME JSAN)

add_custom_target (
    ${PROGRAM_NAME}_install
    COMMAND npm install ${MSVS_VERSION} > ${CMAKE_CURRENT_BINARY_DIR}/${PROGRAM_NAME}-npm-install.log 2>&1
    DEPENDS javascriptAddon
    WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/tmp_jsan
)

add_custom_copy_target(${PROGRAM_NAME}_install ${CMAKE_CURRENT_SOURCE_DIR} ${EXECUTABLE_OUTPUT_PATH}/tmp_jsan DIRECTORY)
add_custom_generated_copy_dependency (${PROGRAM_NAME}_install ${EXECUTABLE_OUTPUT_PATH} ${EXECUTABLE_OUTPUT_PATH}/tmp_jsan javascriptAddon.node)

set_target_properties (${PROGRAM_NAME}_install PROPERTIES FOLDER ${CMAKE_SUPPORT_FOLDER_NAME})

add_custom_target (
    ${PROGRAM_NAME}_build
    COMMAND npm run build -- --no-color -o ${EXECUTABLE_OUTPUT_PATH}/node_modules/jsan > ${CMAKE_CURRENT_BINARY_DIR}/${PROGRAM_NAME}-npm-build.log 2>&1
    DEPENDS ${PROGRAM_NAME}_install
    WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/tmp_jsan
)

set_target_properties (${PROGRAM_NAME}_build PROPERTIES FOLDER ${CMAKE_SUPPORT_FOLDER_NAME})

add_custom_target (
    ${PROGRAM_NAME}_virtual_target
    # from cmake 3.17
    # COMMAND ${CMAKE_COMMAND} -E rm -rf ${EXECUTABLE_OUTPUT_PATH}/tmp_jsan
    # until cmake 3.16
    COMMAND ${CMAKE_COMMAND} -E remove_directory -rf ${EXECUTABLE_OUTPUT_PATH}/tmp_jsan
    DEPENDS ${PROGRAM_NAME}_build
)

add_custom_generated_copy_dependency (${PROGRAM_NAME}_virtual_target ${EXECUTABLE_OUTPUT_PATH} ${EXECUTABLE_OUTPUT_PATH}/node_modules/jsan/ javascriptAddon.node)

set_visual_studio_project_folder(${PROGRAM_NAME}_virtual_target TRUE)
