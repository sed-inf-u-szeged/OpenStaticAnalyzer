set (PROGRAM_NAME JAN)
set (BIN_DIR ${PROGRAM_NAME}/bin)

set (GRADLE_BUILD_TARGET ${PROGRAM_NAME}_build)
set (GENERATED_FILES ${BIN_DIR}/${PROGRAM_NAME}.jar)



add_custom_command (
    OUTPUT ${GENERATED_FILES}
    COMMAND gradle${GRADLE_POSTFIX} --no-daemon --parallel --offline -b ${CMAKE_CURRENT_SOURCE_DIR}/build.gradle -PbuildDir=${CMAKE_CURRENT_BINARY_DIR} -PgeneratedRevisionDir=${CMAKE_CURRENT_BINARY_DIR}/../../lib/revision/src > ${CMAKE_CURRENT_BINARY_DIR}/${PROGRAM_NAME}-build.log
    DEPENDS java_revision
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_target (
    ${GRADLE_BUILD_TARGET}
    DEPENDS ${GENERATED_FILES}
)

set_target_properties (${GRADLE_BUILD_TARGET} PROPERTIES FOLDER ${CMAKE_SUPPORT_FOLDER_NAME})

add_custom_target (
    ${PROGRAM_NAME}
    DEPENDS ${GRADLE_BUILD_TARGET}
)


add_custom_generated_copy_dependency(${PROGRAM_NAME} ${BIN_DIR} ${EXECUTABLE_OUTPUT_PATH} ${PROGRAM_NAME}.jar ${GRADLE_BUILD_TARGET})
add_copy_next_to_the_binary_dependency(${PROGRAM_NAME} toolchain.ini)

set_visual_studio_project_folder(${PROGRAM_NAME} TRUE)
