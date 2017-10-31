set (LIBNAME genealogy)

set (SOURCES
    src/Factory.cpp
    inc/Factory.h
    src/Types.cpp
    inc/Types.h
    src/ListIterator.cpp
    inc/ListIterator.h
    src/GenealogyException.cpp
    inc/GenealogyException.h
    src/Common.cpp
    inc/Common.h
    src/ReverseEdges.cpp
    inc/ReverseEdges.h
    src/algorithms/Algorithm.cpp
    inc/algorithms/Algorithm.h
    src/algorithms/AlgorithmPreorder.cpp
    inc/algorithms/AlgorithmPreorder.h
    src/visitors/Visitor.cpp
    inc/visitors/Visitor.h
    src/visitors/VisitorAbstractNodes.cpp
    inc/visitors/VisitorAbstractNodes.h
    src/visitors/VisitorGENEALOGYML.cpp
    inc/visitors/VisitorGENEALOGYML.h
    src/visitors/VisitorReverseEdges.cpp
    inc/visitors/VisitorReverseEdges.h
    src/visitors/VisitorSave.cpp
    inc/visitors/VisitorSave.h
    src/visitors/VisitorSubtreeCollector.cpp
    inc/visitors/VisitorSubtreeCollector.h
    src/visitors/VisitorGraphml.cpp
    inc/visitors/VisitorGraphml.h
    src/visitors/VisitorSimpleEdge.cpp
    inc/visitors/VisitorSimpleEdge.h
    src/genealogy.cpp
    inc/genealogy.h
    src/nodes/Base.cpp
    inc/nodes/Base.h
    src/nodes/Project.cpp
    inc/nodes/Project.h
    src/nodes/Trackable.cpp
    inc/nodes/Trackable.h
    src/nodes/Component.cpp
    inc/nodes/Component.h
    src/nodes/SourceCodeElement.cpp
    inc/nodes/SourceCodeElement.h
    src/nodes/System.cpp
    inc/nodes/System.h
    src/nodes/Clone.cpp
    inc/nodes/Clone.h
    src/nodes/StructuralClone.cpp
    inc/nodes/StructuralClone.h
    src/nodes/CloneClass.cpp
    inc/nodes/CloneClass.h
    src/nodes/CloneInstance.cpp
    inc/nodes/CloneInstance.h
    src/nodes/DataClumpsClass.cpp
    inc/nodes/DataClumpsClass.h
    src/nodes/DataClumps.cpp
    inc/nodes/DataClumps.h
    src/nodes/DataElement.cpp
    inc/nodes/DataElement.h
    src/nodes/SwitchStatementClass.cpp
    inc/nodes/SwitchStatementClass.h
    src/nodes/SwitchStatement.cpp
    inc/nodes/SwitchStatement.h
    src/nodes/CaseLabel.cpp
    inc/nodes/CaseLabel.h
    inc/messages.h
)


add_library (${LIBNAME} STATIC ${SOURCES})
add_dependencies (${LIBNAME} boost)
set_target_properties(${LIBNAME} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "${CMAKE_CURRENT_SOURCE_DIR}/inc/${LIBNAME}.h")
add_pch_generation(${LIBNAME} boost)
set_visual_studio_project_folder(${LIBNAME} TRUE)
