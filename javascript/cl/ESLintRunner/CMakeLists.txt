set (PROGRAM_NAME ESLintRunner)

add_custom_target (
    ${PROGRAM_NAME}
    COMMAND npm install ${MSVS_VERSION} > ${CMAKE_CURRENT_BINARY_DIR}/${PROGRAM_NAME}-build.log 2>&1
    DEPENDS javascript
    WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/node_modules/eslintrunner
)

add_custom_copy_target(${PROGRAM_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/${PROGRAM_NAME}.js ${EXECUTABLE_OUTPUT_PATH}/node_modules/eslintrunner/${PROGRAM_NAME}.js)
add_custom_copy_target(${PROGRAM_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src ${EXECUTABLE_OUTPUT_PATH}/node_modules/eslintrunner/src DIRECTORY)
add_custom_copy_target(${PROGRAM_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/package.json ${EXECUTABLE_OUTPUT_PATH}/node_modules/eslintrunner/package.json)
add_custom_copy_target(${PROGRAM_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/eslint.json ${EXECUTABLE_OUTPUT_PATH}/node_modules/eslintrunner/eslint.json)
add_custom_copy_target(${PROGRAM_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/OpenStaticAnalyzerFormater.js ${EXECUTABLE_OUTPUT_PATH}/node_modules/eslintrunner/OpenStaticAnalyzerFormater.js)

set_visual_studio_project_folder(${PROGRAM_NAME} TRUE)
