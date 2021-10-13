set (PROGRAM_NAME MetricHunter)

set (SOURCES
    src/main.cpp
    src/MetricChecker.cpp
    src/Threshold.cpp
    src/ThresholdReader.cpp
    
    inc/defines.h
    inc/Helper.h
    inc/messages.h
    inc/MetricChecker.h
    inc/Threshold.h
    inc/ThresholdReader.h 
)

function (add_language_config LANG)
  add_executable(${PROGRAM_NAME}_${LANG} ${SOURCES})
  add_dependencies(${PROGRAM_NAME}_${LANG} ${COLUMBUS_GLOBAL_DEPENDENCY})
  target_link_libraries(${PROGRAM_NAME}_${LANG} graphsupport graph strtable common csi rul io ${COMMON_EXTERNAL_LIBRARIES})
  set_schema_language_compiler_settings(${PROGRAM_NAME}_${LANG} ${LANG})
  string (TOUPPER ${LANG} UPPER_CASE_LANG)
  add_copy_next_to_the_binary_dependency (${PROGRAM_NAME}_${LANG} MetricHunter_${UPPER_CASE_LANG}.threshold)
  set_visual_studio_project_folder(${PROGRAM_NAME}_${LANG} FALSE)
endfunction()

add_language_config(cpp)
add_language_config(java)
add_language_config(javascript)
add_language_config(python)
add_language_config(csharp)
