set (TOOLS_REF_MD ToolsRef.md)
set (CREATE_TOOLS_REF_TARGET ${ANALYZER_TARGET_NAME}-${TOOLS_REF_MD})
set (METRIC_RULS MET.rul.md DCF.rul.md)
set (ANALYZER_RULS)
set (3RD_PARTY_RULS Pylint_2.rul.md)
set (METADATA general_metadata.md Pylint_2.rul_metadata.md)
set (OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/${TOOLS_REF_MD})

create_tools_ref_from_ruls (${CREATE_TOOLS_REF_TARGET} "python" "${METRIC_RULS}" "${ANALYZER_RULS}" "${3RD_PARTY_RULS}" "${METADATA}" ${OUTPUT_PATH})
add_dependencies(${CREATE_TOOLS_REF_TARGET}
    CommonTagMetadata_copy_general_metadata.md
    LIM2Metrics_copy_MET.rul.md
    DuplicatedCodeFinder_copy_DCF.rul.md
    Pylint2Graph_copy_Pylint_2.rul.md
    Pylint2Graph_copy_Pylint_2.rul_metadata.md
)

set (UG_INPUTS
    md/Main.md
    ${OUTPUT_PATH}
    ../../../doc/md/UserDefinedMetricsRef.md
    ../../../doc/md/UserDefinedPatternsRef.md
    md/Footnotes.md
)

add_usersguide_generator (${ANALYZER_TARGET_NAME}-UG ../../../doc/style/Analyzer.css UG_INPUTS)
add_dependencies(${ANALYZER_TARGET_NAME}-UG ${CREATE_TOOLS_REF_TARGET})

