
set (UG_INPUTS
    md/Main.md
    md/SourceCodeMetricsRef.md
    md/CodeDuplicationMetricsRef.md
    md/ESLintRef.md
    ../../../doc/md/UserDefinedMetricsRef.md
    ../../../doc/md/UserDefinedPatternsRef.md
    md/Footnotes.md
)

add_usersguide_generator (${OSA_TARGET_NAME}-UG ../../../doc/style/OpenStaticAnalyzer.css UG_INPUTS)
