set (PROGRAM_NAME JColumbusAntWrapper)

set (BIN_DIR ${PROGRAM_NAME}/bin)

set (GRADLE_BUILD_TARGET ${PROGRAM_NAME}_build)
set (GENERATED_FILES ${BIN_DIR}/JColumbusAntWrapper.jar)

add_custom_command (
	OUTPUT ${GENERATED_FILES}
    COMMAND gradle${GRADLE_POSTFIX} --no-daemon --parallel --offline -b ${CMAKE_CURRENT_SOURCE_DIR}/build.gradle -PbuildDir=${CMAKE_CURRENT_BINARY_DIR} > ${CMAKE_CURRENT_BINARY_DIR}/${PROGRAM_NAME}-build.log
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

add_custom_generated_copy_dependency(${PROGRAM_NAME} ${BIN_DIR} ${EXECUTABLE_OUTPUT_PATH} JColumbusAntWrapper.jar ${GRADLE_BUILD_TARGET})
set_visual_studio_project_folder(${PROGRAM_NAME} TRUE)
