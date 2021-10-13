set (LIBNAME limmetrics)

set (SOURCES
    src/Containers.cpp
    src/LimMetrics.cpp
    src/MetricHandler.cpp
    src/metrics/Aggregates.cpp
    src/metrics/CBO.cpp
    src/metrics/Documentation.cpp
    src/metrics/Halstead.cpp
    src/metrics/Inheritance.cpp
    src/metrics/LCOM5.cpp
    src/metrics/LOC.cpp
    src/metrics/McCC.cpp
    src/metrics/NA.cpp
    src/metrics/NCL.cpp
    src/metrics/NII.cpp
    src/metrics/NL.cpp
    src/metrics/NM.cpp
    src/metrics/NOI.cpp
    src/metrics/NOS.cpp
    src/metrics/NPKG.cpp
    src/metrics/NUMPAR.cpp
    src/metrics/RFC.cpp
    src/metrics/TNFI.cpp
    src/metrics/WMC.cpp
    src/NodeWrapper.cpp
    src/RulParser.cpp
    
    inc/Containers.h
    inc/Defines.h
    inc/LimMetrics.h
    inc/Messages.h
    inc/MetricHandler.h
    inc/metrics/Aggregates.h
    inc/metrics/CBO.h
    inc/metrics/Documentation.h
    inc/metrics/Halstead.h
    inc/metrics/Inheritance.h
    inc/metrics/LCOM5.h
    inc/metrics/LOC.h
    inc/metrics/McCC.h
    inc/metrics/NA.h
    inc/metrics/NCL.h
    inc/metrics/NII.h
    inc/metrics/NL.h
    inc/metrics/NM.h
    inc/metrics/NOI.h
    inc/metrics/NOS.h
    inc/metrics/NPKG.h
    inc/metrics/NUMPAR.h
    inc/metrics/RFC.h
    inc/metrics/TNFI.h
    inc/metrics/WMC.h
    inc/NodeWrapper.h
    inc/RulParser.h     
)

add_library (${LIBNAME} STATIC ${SOURCES})
add_dependencies (${LIBNAME} lim)
set_visual_studio_project_folder(${LIBNAME} FALSE)

