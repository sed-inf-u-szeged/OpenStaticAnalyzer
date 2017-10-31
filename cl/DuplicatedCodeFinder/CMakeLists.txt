set (PROGRAM_NAME DuplicatedCodeFinder)

set (SOURCES
    src/AbstractFilter.cpp
    src/CloneLengthFilter.cpp
    src/ClonePositioned.cpp
    src/CloneVisitorBase.cpp
    src/common.cpp
    src/CoverageVisitorBase.cpp
    src/dcm.cpp
    src/JCoverageVisitor.cpp
    src/JNodeEmbeddednessVisitor.cpp
    src/LanguageFactory.cpp
    src/main.cpp
    src/RepeatingLinesFilter.cpp
    src/StatementFilter.cpp
    
    inc/AbstractFilter.h
    inc/Aligner.h
    inc/CloneLengthFilter.h
    inc/CloneOccuranceFilter.h
    inc/ClonePositioned.h
    inc/CloneVisitorBase.h
    inc/common.h
    inc/Config.h
    inc/CoverageVisitorBase.h
    inc/dcm.h
    inc/DistanceVisitor.h
    inc/Interval.h
    inc/JCoverageVisitor.h
    inc/LanguageFactory.h
    inc/messages.h
    inc/NamedVisitor.h
    inc/RepeatingLinesFilter.h
    inc/StatementFilter.h
    inc/types.h
    inc/Visitors/JNodeEmbeddednessVisitor.h
    inc/Visitors/NodeEmbeddednessVisitorBase.h
)

function (add_language_config LANG)
  add_executable(${PROGRAM_NAME}_${LANG} ${SOURCES})
  add_dependencies(${PROGRAM_NAME}_${LANG} ${COLUMBUS_GLOBAL_DEPENDENCY})
  target_link_libraries(${PROGRAM_NAME}_${LANG} genealogy graphsupport lim2graph graph lim strtable common csi rul io ${COMMON_EXTERNAL_LIBRARIES})
  set_schema_language_compiler_settings(${PROGRAM_NAME}_${LANG} ${LANG})
  add_copy_next_to_the_binary_dependency (${PROGRAM_NAME}_${LANG} DCF.rul)
  set_visual_studio_project_folder(${PROGRAM_NAME}_${LANG} FALSE)
#  Can not use atm because it tries to generate the pch for all targets
#  set_target_properties(${PROGRAM_NAME}_${LANG} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "${CMAKE_CURRENT_SOURCE_DIR}/inc/common.h")
#  cotire (${PROGRAM_NAME}_${LANG})
endfunction()

add_language_config(java)


