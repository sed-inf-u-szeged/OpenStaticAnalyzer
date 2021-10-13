set (PROGRAM_NAME JAN)
set (BIN_DIR ${PROGRAM_NAME}/bin)

set (GRADLE_BUILD_TARGET ${PROGRAM_NAME}_build)
set (GENERATED_FILES ${BIN_DIR}/${PROGRAM_NAME}.jar)

set (GRADLE_FAKE_DEP ${PROGRAM_NAME}_gradle)
set_source_files_properties (${GRADLE_FAKE_DEP} PROPERTIES SYMBOLIC TRUE)

add_custom_command (
    OUTPUT ${GRADLE_FAKE_DEP}
    COMMAND gradle${GRADLE_POSTFIX} --no-daemon --parallel --offline -b ${CMAKE_CURRENT_SOURCE_DIR}/build.gradle -PbuildDir=${CMAKE_CURRENT_BINARY_DIR} -PschemaGeneratorPath=${EXECUTABLE_OUTPUT_PATH}/SchemaGenerator${EXE} -PgeneratedRevisionDir=${CMAKE_CURRENT_BINARY_DIR}/../../lib/revision/src > ${CMAKE_CURRENT_BINARY_DIR}/${PROGRAM_NAME}-build.log
    DEPENDS java_revision
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Building JAN"
)

add_custom_target (
    ${GRADLE_BUILD_TARGET}
    DEPENDS ${GRADLE_FAKE_DEP}
)

set_target_properties (${GRADLE_BUILD_TARGET} PROPERTIES FOLDER ${CMAKE_SUPPORT_FOLDER_NAME})

add_custom_target (
    ${PROGRAM_NAME}
    DEPENDS ${GRADLE_BUILD_TARGET}
)

add_custom_generated_copy_dependency(${PROGRAM_NAME} ${BIN_DIR} ${EXECUTABLE_OUTPUT_PATH} ${PROGRAM_NAME}.jar ${GRADLE_BUILD_TARGET})
add_custom_generated_copy_dependency(${PROGRAM_NAME} ${BIN_DIR} ${EXECUTABLE_OUTPUT_PATH} jdk.compiler.jar ${GRADLE_BUILD_TARGET})
add_copy_next_to_the_binary_dependency(${PROGRAM_NAME} toolchain.ini)

set_visual_studio_project_folder(${PROGRAM_NAME} TRUE)
