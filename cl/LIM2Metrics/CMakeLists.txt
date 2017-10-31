set (PROGRAM_NAME LIM2Metrics)

set (SOURCES
    main.cpp
    
    messages.h
)

function (add_language_config LANG)
  add_executable(${PROGRAM_NAME}_${LANG} ${SOURCES})
  add_dependencies(${PROGRAM_NAME}_${LANG} ${COLUMBUS_GLOBAL_DEPENDENCY})
  target_link_libraries(${PROGRAM_NAME}_${LANG} graphsupport lim2graph graph limmetrics_${LANG} lim strtable common csi rul io ${COMMON_EXTERNAL_LIBRARIES})
  set_schema_language_compiler_settings(${PROGRAM_NAME}_${LANG} ${LANG})
  add_copy_next_to_the_binary_dependency (${PROGRAM_NAME}_${LANG} MET.rul)
  set_visual_studio_project_folder(${PROGRAM_NAME}_${LANG} FALSE)
#  Can not use atm because it tries to generate the pch for all targets
#  set_target_properties(${PROGRAM_NAME}_${LANG} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "${CMAKE_CURRENT_SOURCE_DIR}/inc/common.h")
#  cotire (${PROGRAM_NAME}_${LANG})
endfunction()

add_language_config(java)


