set (LIBNAME javascript)

set (SOURCES
    src/Factory.cpp
    inc/Factory.h
    src/Filter.cpp
    inc/Filter.h
    src/Types.cpp
    inc/Types.h
    src/ListIterator.cpp
    inc/ListIterator.h
    src/JavascriptException.cpp
    inc/JavascriptException.h
    src/Common.cpp
    inc/Common.h
    src/ReverseEdges.cpp
    inc/ReverseEdges.h
    src/Range.cpp
    inc/Range.h
    src/algorithms/Algorithm.cpp
    inc/algorithms/Algorithm.h
    src/algorithms/AlgorithmPreorder.cpp
    inc/algorithms/AlgorithmPreorder.h
    src/visitors/Visitor.cpp
    inc/visitors/Visitor.h
    src/visitors/VisitorAbstractNodes.cpp
    inc/visitors/VisitorAbstractNodes.h
    src/visitors/VisitorJAVASCRIPTML.cpp
    inc/visitors/VisitorJAVASCRIPTML.h
    src/visitors/VisitorFilter.cpp
    inc/visitors/VisitorFilter.h
    src/visitors/VisitorReverseEdges.cpp
    inc/visitors/VisitorReverseEdges.h
    src/visitors/VisitorSave.cpp
    inc/visitors/VisitorSave.h
    src/visitors/VisitorSubtreeCollector.cpp
    inc/visitors/VisitorSubtreeCollector.h
    src/visitors/VisitorAsgStat.cpp
    inc/visitors/VisitorAsgStat.h
    src/visitors/VisitorGraphml.cpp
    inc/visitors/VisitorGraphml.h
    src/visitors/VisitorSimpleEdge.cpp
    inc/visitors/VisitorSimpleEdge.h
    src/javascript.cpp
    inc/javascript.h
    src/base/Base.cpp
    inc/base/Base.h
    src/base/Comment.cpp
    inc/base/Comment.h
    src/base/Named.cpp
    inc/base/Named.h
    src/base/Positioned.cpp
    inc/base/Positioned.h
    src/base/Program.cpp
    inc/base/Program.h
    src/base/System.cpp
    inc/base/System.h
    src/declaration/ClassDeclaration.cpp
    inc/declaration/ClassDeclaration.h
    src/declaration/Declaration.cpp
    inc/declaration/Declaration.h
    src/declaration/ExportAllDeclaration.cpp
    inc/declaration/ExportAllDeclaration.h
    src/declaration/ExportDefaultDeclaration.cpp
    inc/declaration/ExportDefaultDeclaration.h
    src/declaration/ExportNamedDeclaration.cpp
    inc/declaration/ExportNamedDeclaration.h
    src/declaration/FunctionDeclaration.cpp
    inc/declaration/FunctionDeclaration.h
    src/declaration/ImportDeclaration.cpp
    inc/declaration/ImportDeclaration.h
    src/declaration/ModuleDeclaration.cpp
    inc/declaration/ModuleDeclaration.h
    src/declaration/VariableDeclaration.cpp
    inc/declaration/VariableDeclaration.h
    src/declaration/VariableDeclarator.cpp
    inc/declaration/VariableDeclarator.h
    src/expression/ArrayExpression.cpp
    inc/expression/ArrayExpression.h
    src/expression/ArrowFunctionExpression.cpp
    inc/expression/ArrowFunctionExpression.h
    src/expression/AssignmentExpression.cpp
    inc/expression/AssignmentExpression.h
    src/expression/AwaitExpression.cpp
    inc/expression/AwaitExpression.h
    src/expression/BigIntLiteral.cpp
    inc/expression/BigIntLiteral.h
    src/expression/BinaryExpression.cpp
    inc/expression/BinaryExpression.h
    src/expression/BooleanLiteral.cpp
    inc/expression/BooleanLiteral.h
    src/expression/CallExpression.cpp
    inc/expression/CallExpression.h
    src/expression/ChainElement.cpp
    inc/expression/ChainElement.h
    src/expression/ChainExpression.cpp
    inc/expression/ChainExpression.h
    src/expression/ClassExpression.cpp
    inc/expression/ClassExpression.h
    src/expression/ConditionalExpression.cpp
    inc/expression/ConditionalExpression.h
    src/expression/Expression.cpp
    inc/expression/Expression.h
    src/expression/FunctionExpression.cpp
    inc/expression/FunctionExpression.h
    src/expression/Identifier.cpp
    inc/expression/Identifier.h
    src/expression/ImportExpression.cpp
    inc/expression/ImportExpression.h
    src/expression/Literal.cpp
    inc/expression/Literal.h
    src/expression/LogicalExpression.cpp
    inc/expression/LogicalExpression.h
    src/expression/MemberExpression.cpp
    inc/expression/MemberExpression.h
    src/expression/MetaProperty.cpp
    inc/expression/MetaProperty.h
    src/expression/NewExpression.cpp
    inc/expression/NewExpression.h
    src/expression/NullLiteral.cpp
    inc/expression/NullLiteral.h
    src/expression/NumberLiteral.cpp
    inc/expression/NumberLiteral.h
    src/expression/ObjectExpression.cpp
    inc/expression/ObjectExpression.h
    src/expression/PrivateIdentifier.cpp
    inc/expression/PrivateIdentifier.h
    src/expression/Property.cpp
    inc/expression/Property.h
    src/expression/RegExpLiteral.cpp
    inc/expression/RegExpLiteral.h
    src/expression/SequenceExpression.cpp
    inc/expression/SequenceExpression.h
    src/expression/SpreadElement.cpp
    inc/expression/SpreadElement.h
    src/expression/StringLiteral.cpp
    inc/expression/StringLiteral.h
    src/expression/Super.cpp
    inc/expression/Super.h
    src/expression/TaggedTemplateExpression.cpp
    inc/expression/TaggedTemplateExpression.h
    src/expression/TemplateElement.cpp
    inc/expression/TemplateElement.h
    src/expression/TemplateLiteral.cpp
    inc/expression/TemplateLiteral.h
    src/expression/ThisExpression.cpp
    inc/expression/ThisExpression.h
    src/expression/UnaryExpression.cpp
    inc/expression/UnaryExpression.h
    src/expression/UpdateExpression.cpp
    inc/expression/UpdateExpression.h
    src/expression/YieldExpression.cpp
    inc/expression/YieldExpression.h
    src/statement/ArrayPattern.cpp
    inc/statement/ArrayPattern.h
    src/statement/AssignmentPattern.cpp
    inc/statement/AssignmentPattern.h
    src/statement/BlockStatement.cpp
    inc/statement/BlockStatement.h
    src/statement/BreakStatement.cpp
    inc/statement/BreakStatement.h
    src/statement/CatchClause.cpp
    inc/statement/CatchClause.h
    src/statement/ContinueStatement.cpp
    inc/statement/ContinueStatement.h
    src/statement/DebuggerStatement.cpp
    inc/statement/DebuggerStatement.h
    src/statement/DoWhileStatement.cpp
    inc/statement/DoWhileStatement.h
    src/statement/EmptyStatement.cpp
    inc/statement/EmptyStatement.h
    src/statement/ExpressionStatement.cpp
    inc/statement/ExpressionStatement.h
    src/statement/ForInStatement.cpp
    inc/statement/ForInStatement.h
    src/statement/ForOfStatement.cpp
    inc/statement/ForOfStatement.h
    src/statement/ForStatement.cpp
    inc/statement/ForStatement.h
    src/statement/Function.cpp
    inc/statement/Function.h
    src/statement/IfStatement.cpp
    inc/statement/IfStatement.h
    src/statement/LabeledStatement.cpp
    inc/statement/LabeledStatement.h
    src/statement/ObjectPattern.cpp
    inc/statement/ObjectPattern.h
    src/statement/Pattern.cpp
    inc/statement/Pattern.h
    src/statement/RestElement.cpp
    inc/statement/RestElement.h
    src/statement/ReturnStatement.cpp
    inc/statement/ReturnStatement.h
    src/statement/Statement.cpp
    inc/statement/Statement.h
    src/statement/SwitchCase.cpp
    inc/statement/SwitchCase.h
    src/statement/SwitchStatement.cpp
    inc/statement/SwitchStatement.h
    src/statement/ThrowStatement.cpp
    inc/statement/ThrowStatement.h
    src/statement/TryStatement.cpp
    inc/statement/TryStatement.h
    src/statement/WhileStatement.cpp
    inc/statement/WhileStatement.h
    src/statement/WithStatement.cpp
    inc/statement/WithStatement.h
    src/structure/Class.cpp
    inc/structure/Class.h
    src/structure/ClassBody.cpp
    inc/structure/ClassBody.h
    src/structure/ExportSpecifier.cpp
    inc/structure/ExportSpecifier.h
    src/structure/ImpSpecifier.cpp
    inc/structure/ImpSpecifier.h
    src/structure/ImportDefaultSpecifier.cpp
    inc/structure/ImportDefaultSpecifier.h
    src/structure/ImportNamespaceSpecifier.cpp
    inc/structure/ImportNamespaceSpecifier.h
    src/structure/ImportSpecifier.cpp
    inc/structure/ImportSpecifier.h
    src/structure/MethodDefinition.cpp
    inc/structure/MethodDefinition.h
    src/structure/ModuleSpecifier.cpp
    inc/structure/ModuleSpecifier.h
    src/structure/PropertyDefinition.cpp
    inc/structure/PropertyDefinition.h
    inc/messages.h
)

add_library (${LIBNAME} STATIC ${SOURCES})
add_dependencies (${LIBNAME} boost)
set_visual_studio_project_folder(${LIBNAME} TRUE)


####################### Addon #######################################

set (ADDON_NAME ${LIBNAME}Addon)
set (ADDON_SUBDIR addon)
set (ADDON_BINARY ${EXECUTABLE_OUTPUT_PATH}/${ADDON_NAME}.node)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  set(GYP_CONFIG "--debug")
endif()


configure_file(${CMAKE_CURRENT_SOURCE_DIR}/osa.gyp ${CMAKE_CURRENT_SOURCE_DIR}/${ADDON_SUBDIR}/osa.gyp)

add_custom_command(
  OUTPUT ${ADDON_BINARY}
  DEPENDS javascript common csi strtable io ${CMAKE_CURRENT_SOURCE_DIR}/osa.gyp
  COMMAND npm install ${MSVS_VERSION} ${GYP_CONFIG} > ${CMAKE_CURRENT_BINARY_DIR}/${ADDON_NAME}-build.log 2>&1
  COMMAND ${CMAKE_COMMAND} -E touch_nocreate ${ADDON_BINARY}
  COMMENT "Creating ${ADDON_BINARY}"
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${ADDON_SUBDIR}
)

add_custom_target(
  ${ADDON_NAME}
  DEPENDS ${ADDON_BINARY}
)

set_visual_studio_project_folder(${ADDON_NAME} TRUE)
