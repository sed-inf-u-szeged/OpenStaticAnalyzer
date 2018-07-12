set (PROGRAM_NAME DuplicatedCodeFinder)

set (SOURCES
    src/AbstractFilter.cpp
    src/CloneLengthFilter.cpp
    src/ClonePositioned.cpp
    src/CloneVisitorBase.cpp
    src/common.cpp
    src/CoverageVisitorBase.cpp
    src/CSCoverageVisitor.cpp
    src/CSNodeEmbeddednessVisitor.cpp
    src/dcm.cpp
    src/JCoverageVisitor.cpp
    src/JNodeEmbeddednessVisitor.cpp
    src/JSNodeEmbeddedVisitor.cpp
    src/JSCoverageVisitor.cpp
    src/LanguageFactory.cpp
    src/main.cpp
    src/PNodeEmbeddednessVisitor.cpp
    src/RepeatingLinesFilter.cpp
    src/StatementFilter.cpp
    
    inc/AbstractFilter.h
    inc/Aligner.h
    inc/CloneLengthFilter.h
    inc/CloneOccuranceFilter.h
    inc/ClonePositioned.h
    inc/common.h
    inc/Config.h
    inc/dcm.h
    inc/Interval.h
    inc/LanguageFactory.h
    inc/messages.h
    inc/RepeatingLinesFilter.h
    inc/StatementFilter.h
    inc/types.h
    inc/Visitors/CloneVisitorBase.h
    inc/Visitors/CoverageVisitorBase.h
    inc/Visitors/CSCoverageVisitor.h
    inc/Visitors/CSharpNamedVisitor.h
    inc/Visitors/CSNodeEmbeddednessVisitor.h
    inc/Visitors/DistanceVisitor.h
    inc/Visitors/JCoverageVisitor.h
    inc/Visitors/JNodeEmbeddednessVisitor.h
    inc/Visitors/JSCoverageVisitor.h
    inc/Visitors/JSNodeEmbeddedVisitor.h
    inc/Visitors/NamedVisitor.h
    inc/Visitors/NodeEmbeddednessVisitorBase.h
    inc/Visitors/PCoverageVisitor.h
    inc/Visitors/PNodeEmbeddednessVisitor.h
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
add_language_config(python)
add_language_config(csharp)
add_language_config(javascript)

