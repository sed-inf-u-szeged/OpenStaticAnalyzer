set (LIBNAME graphsupport)

set (SOURCES
    src/CsvExporter.cpp
    src/GraphConstants.cpp
    src/GraphRangeIndexer.cpp
    src/JVMuniquenameGenerator.cpp
    src/Metric.cpp
    src/MetricSum.cpp
    src/RulBuilder.cpp
    src/SarifExporter.cpp
    
    inc/CsvExporter.h
    inc/GraphConstants.h
    inc/GraphRangeIndexer.h
    inc/JVMuniquenameGenerator.h
    inc/messages.h
    inc/Metric.h
    inc/MetricSum.h
    inc/RulBuilder.h   
    inc/SarifExporter.h  
)

add_library (${LIBNAME} STATIC ${SOURCES})
add_dependencies (${LIBNAME} boost)
set_visual_studio_project_folder(${LIBNAME} TRUE)
