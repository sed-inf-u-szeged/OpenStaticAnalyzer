set (GENERATED_FILES
     ${CMAKE_CURRENT_BINARY_DIR}/../bin/graphsupportlib.jar
     ${CMAKE_CURRENT_BINARY_DIR}/build/doc
)

set (TARGET_NAME java_graphsupportlib)

add_custom_command (
    OUTPUT ${GENERATED_FILES}
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/build_osa.xml java_graphlib
    COMMAND ant -f build_osa.xml -Dbuild=${CMAKE_CURRENT_BINARY_DIR}/build -Dbin=${CMAKE_CURRENT_BINARY_DIR}/../bin > ${CMAKE_CURRENT_BINARY_DIR}/ant.log
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target (
    ${TARGET_NAME}
    DEPENDS ${GENERATED_FILES}
)

set_target_properties (${TARGET_NAME} PROPERTIES FOLDER ${CMAKE_SUPPORT_FOLDER_NAME})

