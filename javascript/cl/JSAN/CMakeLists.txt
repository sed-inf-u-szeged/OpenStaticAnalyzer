set (PROGRAM_NAME JSAN)

add_custom_target (
    ${PROGRAM_NAME}
    COMMAND npm install ${MSVS_VERSION} > ${CMAKE_CURRENT_BINARY_DIR}/${PROGRAM_NAME}-build.log 2>&1
    DEPENDS javascriptAddon
    WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/node_modules/jsan
)

add_custom_copy_target(${PROGRAM_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/JSAN.js ${EXECUTABLE_OUTPUT_PATH}/node_modules/jsan/JSAN.js)
add_custom_copy_target(${PROGRAM_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/package.json ${EXECUTABLE_OUTPUT_PATH}/node_modules/jsan/package.json)
add_custom_copy_target(${PROGRAM_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src ${EXECUTABLE_OUTPUT_PATH}/node_modules/jsan/src DIRECTORY)

add_custom_generated_copy_dependency(${PROGRAM_NAME} ${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}/ ${EXECUTABLE_OUTPUT_PATH}/node_modules/jsan/ javascriptAddon.node)

set_visual_studio_project_folder(${PROGRAM_NAME} TRUE)

