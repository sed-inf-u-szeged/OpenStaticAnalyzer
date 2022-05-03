
# add_prefix function adds ${PREFIX} prefix to all elements of the ${LIST_VARIABLE}
function (add_prefix LIST_VARIABLE PREFIX)
  foreach (ELEMENT ${${LIST_VARIABLE}})
    set (REPLACED ${REPLACED} ${PREFIX}${ELEMENT})
  endforeach()
  set (${LIST_VARIABLE} ${REPLACED} PARENT_SCOPE)
endfunction ()

# add_postfix function adds ${POSTFIX} postfix to all elements of the ${LIST_VARIABLE}
function (add_postfix LIST_VARIABLE POSTFIX)
  foreach (ELEMENT ${${LIST_VARIABLE}})
    set (REPLACED ${REPLACED} ${ELEMENT}${POSTFIX})
  endforeach()
  set (${LIST_VARIABLE} ${REPLACED} PARENT_SCOPE)
endfunction ()

# add schema language dependent compiler options to the given target
function (set_schema_language_compiler_settings TARGET SCHEMA)
  if (SCHEMA STREQUAL "cpp")
    target_compile_definitions(${TARGET} PUBLIC SCHEMA_CPP)
  elseif (SCHEMA STREQUAL "java")
    target_compile_definitions(${TARGET} PUBLIC SCHEMA_JAVA)
    target_link_libraries(${TARGET} java)
  elseif (SCHEMA STREQUAL "python")
    target_compile_definitions(${TARGET} PUBLIC SCHEMA_PYTHON)
    target_link_libraries(${TARGET} python)
  elseif (SCHEMA STREQUAL "csharp")
    target_compile_definitions(${TARGET} PUBLIC SCHEMA_CSHARP)
    target_link_libraries(${TARGET} csharp)
  elseif (SCHEMA STREQUAL "javascript")
    target_compile_definitions(${TARGET} PUBLIC SCHEMA_JAVASCRIPT)
    target_link_libraries(${TARGET} javascript)
  else ()
    message (FATAL_ERROR "Unknown schema language: ${SCHEMA}")
  endif ()
endfunction ()

# Get relative name of the curre directory. If REMOVE_CURRENT is TRUE than the path of the parent folder is returned instead of the current one.
function (get_relative_folder_of_the_current_source_directory FOLDER_VARIABLE REMOVE_CURRENT)
  if (${REMOVE_CURRENT})
    set (PARENT_DIR /..)
  endif()
  get_filename_component (TEMP_DIR ${CMAKE_CURRENT_SOURCE_DIR}${PARENT_DIR} ABSOLUTE)
  string(REPLACE ${CMAKE_SOURCE_DIR}/ "" RELATIVE_PATH  ${TEMP_DIR})
  set (${FOLDER_VARIABLE} ${RELATIVE_PATH} PARENT_SCOPE)
endfunction()

# Put the projects into the corresponding logical folders in the VS
function (set_visual_studio_project_folder TARGET REMOVE_CURRENT)
  get_relative_folder_of_the_current_source_directory (FOLDER_VAR ${REMOVE_CURRENT})
  set_target_properties (${TARGET} PROPERTIES FOLDER Columbus/${FOLDER_VAR})
  set (ADDITIONAL_SOURCES ${ARGN})
  add_prefix (SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/)
  add_prefix (ADDITIONAL_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/)
  source_group (TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES} ${ADDITIONAL_SOURCES})
endfunction ()


# Replace the ${FROM} parameter in all the compiler flag lists to ${TO}
function (replace_compiler_options FROM TO)
  set(CompilerFlags
      CMAKE_CXX_FLAGS
      CMAKE_CXX_FLAGS_DEBUG
      CMAKE_CXX_FLAGS_RELEASE
      CMAKE_C_FLAGS
      CMAKE_C_FLAGS_DEBUG
      CMAKE_C_FLAGS_RELEASE
  )

  foreach(CompilerFlag ${CompilerFlags})
    string(REPLACE "${FROM}" "${TO}" ${CompilerFlag} "${${CompilerFlag}}")
    set (${CompilerFlag} ${${CompilerFlag}} PARENT_SCOPE)
  endforeach()
endfunction ()

# Add a custom copy target dependency to the ${TARGET_NAME} target, which will copy the ${FILE_NAME}
# file from the source directory next to the binary executable in the output directory.
function (add_copy_next_to_the_binary_dependency TARGET_NAME FILE_NAME)
  get_filename_component (CUSTOM_DESTINATION_NAME ${FILE_NAME} NAME)
  add_custom_copy_target(${TARGET_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/${FILE_NAME} ${EXECUTABLE_OUTPUT_PATH}/${CUSTOM_DESTINATION_NAME})
endfunction ()


# Add a ${TARGET_NAME} named custom copy target, which will copy the ${SOURCE}
# file to the ${DESTINATION}.
function (add_copy_custom_target TARGET_NAME SOURCE DESTINATION)
  add_custom_command (
    DEPENDS ${SOURCE}
    MAIN_DEPENDENCY ${SOURCE}
    OUTPUT ${DESTINATION}
    COMMAND ${CMAKE_COMMAND} -E copy ${SOURCE} ${DESTINATION}
    COMMENT "Copying ${SOURCE} to ${DESTINATION}"
  )
  add_custom_target (
    ${TARGET_NAME}
    DEPENDS ${DESTINATION}
  )
  set_target_properties (${TARGET_NAME} PROPERTIES FOLDER ${CMAKE_SUPPORT_FOLDER_NAME})
endfunction()


# Add a ${TARGET_NAME} named custom copy target, which will copy the ${SOURCE}
# directory to the ${DESTINATION}. It recognises changes in the source directory
# except the file deletion!
function (add_copy_custom_target_dir TARGET_NAME SOURCE DESTINATION)
  file (GLOB_RECURSE SOURCE_DEPS CONFIGURE_DEPENDS "${SOURCE}/*")
  list (APPEND SOURCE_DEPS ${SOURCE})

  foreach(SRC ${SOURCE_DEPS})
    string(REPLACE "${SOURCE}" "${DESTINATION}" REPLACED ${SRC} )
    list (APPEND OUTPUTS ${REPLACED})
  endforeach()

  add_custom_command (
    DEPENDS ${SOURCE_DEPS}
    MAIN_DEPENDENCY ${SOURCE}
    OUTPUT ${OUTPUTS}
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${DESTINATION}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${SOURCE} ${DESTINATION}
    COMMENT "Copying ${SOURCE} to ${DESTINATION}"
  )
  add_custom_target (
    ${TARGET_NAME}
    DEPENDS ${OUTPUTS}
  )
  set_target_properties (${TARGET_NAME} PROPERTIES FOLDER ${CMAKE_SUPPORT_FOLDER_NAME})
endfunction()


# Add a custom copy target dependency to the ${TARGET_NAME} target, which will copy the ${SOURCE} to the ${DESTINATION}.
# If 4th parameter is set then directory copy is used instead of file copy.
function (add_custom_copy_target TARGET_NAME SOURCE DESTINATION)
  get_filename_component (CUSTOM_TARGET_NAME ${SOURCE} NAME)
  set (CUSTOM_TARGET_NAME ${TARGET_NAME}_copy_${CUSTOM_TARGET_NAME})

  if (${ARGC} LESS 4)
    add_copy_custom_target(${CUSTOM_TARGET_NAME} ${SOURCE} ${DESTINATION})
  else ()
    add_copy_custom_target_dir(${CUSTOM_TARGET_NAME} ${SOURCE} ${DESTINATION})
  endif ()

  add_dependencies (${TARGET_NAME} ${CUSTOM_TARGET_NAME})
endfunction ()


# Add a custom copy target (with name ${TARGET_NAME}_copy_${COPY_NAME}) dependency to the ${TARGET_NAME} target,
# which will copy all the items of the ${SOURCE_VARIABLE} list to the ${DESTINATION_DIR}.
function (add_custom_copy_list_target TARGET_NAME COPY_NAME SOURCE_VARIABLE DESTINATION_DIR)

  foreach (SOURCE IN LISTS ${SOURCE_VARIABLE})
    get_filename_component (SOURCE_NAME ${SOURCE} NAME)
    set (DESTINATION ${DESTINATION_DIR}/${SOURCE_NAME})
    set (DESTINATION_FILES ${DESTINATION_FILES} ${DESTINATION})
    add_custom_command (
      DEPENDS ${SOURCE}
      MAIN_DEPENDENCY ${SOURCE}
      OUTPUT ${DESTINATION}
      COMMAND ${CMAKE_COMMAND} -E copy ${SOURCE} ${DESTINATION}
      COMMENT "Copying ${SOURCE}"
    )
  endforeach ()

  set (CUSTOM_TARGET_NAME ${TARGET_NAME}_copy_${COPY_NAME})
  add_custom_target (
    ${CUSTOM_TARGET_NAME}
    DEPENDS ${DESTINATION_FILES}
  )
  add_dependencies (${TARGET_NAME} ${CUSTOM_TARGET_NAME})
  set_target_properties (${CUSTOM_TARGET_NAME} PROPERTIES FOLDER ${CMAKE_SUPPORT_FOLDER_NAME})
endfunction ()

# Add a custom extract target dependency to the ${TARGET_NAME} target, which
# will extract the ${SOURCE} to the ${DESTINATION_DIR}. The ${EXTRACTED} parameter
function (add_custom_extract_target TARGET_NAME SOURCE DESTINATION_DIR EXTRACTED)
  set_source_files_properties(${SOURCE} PROPERTIES GENERATED TRUE)
  add_custom_command (
    DEPENDS ${SOURCE}
    MAIN_DEPENDENCY ${SOURCE}
    OUTPUT ${EXTRACTED}
    COMMAND ${CMAKE_COMMAND} -E tar xf ${SOURCE}
    COMMENT "Extracting ${SOURCE}"
    WORKING_DIRECTORY ${DESTINATION_DIR}
  )
  get_filename_component (CUSTOM_TARGET_NAME ${SOURCE} NAME)
  set (CUSTOM_TARGET_NAME ${TARGET_NAME}_extract_${CUSTOM_TARGET_NAME})
  add_custom_target (
    ${CUSTOM_TARGET_NAME}
    DEPENDS ${EXTRACTED} ${ARGN}
  )
  add_dependencies (${TARGET_NAME} ${CUSTOM_TARGET_NAME})
  set_target_properties (${CUSTOM_TARGET_NAME} PROPERTIES FOLDER ${CMAKE_SUPPORT_FOLDER_NAME})
endfunction ()

# Add custom target for generate html usersguide from the given markdown inputs by the given css
function (add_usersguide_generator TARGET_NAME CSS INPUTS_VARIABLE)
  set (OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/UsersGuide.html)
  add_custom_command (
      OUTPUT ${OUTPUT_FILE}
      DEPENDS ${${INPUTS_VARIABLE}} ${CSS}
      COMMAND pandoc -S --toc --normalize -f markdown --self-contained -t html5 -o ${OUTPUT_FILE} -c ${CSS} ${${INPUTS_VARIABLE}}
      COMMENT "Generating ${OUTPUT_FILE}"
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )

  add_custom_target (
      ${TARGET_NAME}
      DEPENDS ${OUTPUT_FILE}
  )
  set_visual_studio_project_folder(${TARGET_NAME} FALSE)
endfunction()

# Add custom target for creating custom files
function (add_custom_create_file_target TARGET_NAME OUTPUT_FILE)
  add_custom_command (
     OUTPUT ${OUTPUT_FILE}
     ${ARGN}
  )

  get_filename_component (CUSTOM_TARGET_NAME ${OUTPUT_FILE} NAME)
  set (CUSTOM_TARGET_NAME ${TARGET_NAME}_create_${CUSTOM_TARGET_NAME})

  add_custom_target (
    ${CUSTOM_TARGET_NAME}
    DEPENDS ${OUTPUT_FILE}
  )
  add_dependencies (${TARGET_NAME} ${CUSTOM_TARGET_NAME})
  set_target_properties (${CUSTOM_TARGET_NAME} PROPERTIES FOLDER ${CMAKE_SUPPORT_FOLDER_NAME})
endfunction()

# Add copy step dependency to the given TARGET, which copies the generated SOURCE file to the DESTINATION_PREFIX directory.
# The 5th parameter is optional. You can set the name of the target, which will be used for generating the SOURCE. If it is not set then the file name of the SOURCE without directory or longest extension will be used.
# The 6th parameter is also optional. You can set a different name for the SOURCE on which the file will be created in the destination directory. If it is not set then the SOURCE name will be used.
# If a 7th parameter exists (with any value) then directory copy will be used instead of the file copy.
function (add_custom_generated_copy_dependency TARGET SOURCE_PREFIX DESTINATION_PREFIX SOURCE)
  if (${ARGC} LESS 6)
    set (DESTINATION ${SOURCE})
  else()
    set (DESTINATION ${ARGV5})
  endif ()

  if (${ARGC} LESS 5)
    get_filename_component(SOURCE_NAME_WE ${SOURCE} NAME_WE)
    set (DEPENDS_ON ${SOURCE_NAME_WE})
  else()
    set (DEPENDS_ON ${ARGV4})
  endif ()

  set_source_files_properties( ${SOURCE_PREFIX}/${SOURCE} PROPERTIES GENERATED TRUE)
  add_custom_copy_target (${TARGET} ${SOURCE_PREFIX}/${SOURCE} ${DESTINATION_PREFIX}/${DESTINATION} ${ARGV6})
  add_dependencies (${TARGET}_copy_${SOURCE} ${DEPENDS_ON})
endfunction ()
