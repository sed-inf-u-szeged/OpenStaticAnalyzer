set (LIBNAME java)


set (SOURCES
    src/Factory.cpp
    inc/Factory.h
    src/Filter.cpp
    inc/Filter.h
    src/Types.cpp
    inc/Types.h
    src/ListIterator.cpp
    inc/ListIterator.h
    src/JavaException.cpp
    inc/JavaException.h
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
    src/visitors/VisitorJAVAML.cpp
    inc/visitors/VisitorJAVAML.h
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
    src/visitors/VisitorSimpleEdge.cpp
    inc/visitors/VisitorSimpleEdge.h
    src/java.cpp
    inc/java.h
    src/base/Base.cpp
    inc/base/Base.h
    src/base/BlockComment.cpp
    inc/base/BlockComment.h
    src/base/Comment.cpp
    inc/base/Comment.h
    src/base/Commentable.cpp
    inc/base/Commentable.h
    src/base/JavadocComment.cpp
    inc/base/JavadocComment.h
    src/base/LineComment.cpp
    inc/base/LineComment.h
    src/base/Named.cpp
    inc/base/Named.h
    src/base/NonJavadocComment.cpp
    inc/base/NonJavadocComment.h
    src/base/Positioned.cpp
    inc/base/Positioned.h
    src/base/PositionedWithoutComment.cpp
    inc/base/PositionedWithoutComment.h
    src/expr/AnnotatedTypeExpression.cpp
    inc/expr/AnnotatedTypeExpression.h
    src/expr/Annotation.cpp
    inc/expr/Annotation.h
    src/expr/ArrayAccess.cpp
    inc/expr/ArrayAccess.h
    src/expr/ArrayTypeExpression.cpp
    inc/expr/ArrayTypeExpression.h
    src/expr/Assignment.cpp
    inc/expr/Assignment.h
    src/expr/Binary.cpp
    inc/expr/Binary.h
    src/expr/BooleanLiteral.cpp
    inc/expr/BooleanLiteral.h
    src/expr/CharacterLiteral.cpp
    inc/expr/CharacterLiteral.h
    src/expr/ClassLiteral.cpp
    inc/expr/ClassLiteral.h
    src/expr/Conditional.cpp
    inc/expr/Conditional.h
    src/expr/DoubleLiteral.cpp
    inc/expr/DoubleLiteral.h
    src/expr/Erroneous.cpp
    inc/expr/Erroneous.h
    src/expr/ErroneousTypeExpression.cpp
    inc/expr/ErroneousTypeExpression.h
    src/expr/Expression.cpp
    inc/expr/Expression.h
    src/expr/ExternalTypeExpression.cpp
    inc/expr/ExternalTypeExpression.h
    src/expr/FieldAccess.cpp
    inc/expr/FieldAccess.h
    src/expr/FloatLiteral.cpp
    inc/expr/FloatLiteral.h
    src/expr/FunctionalExpression.cpp
    inc/expr/FunctionalExpression.h
    src/expr/Identifier.cpp
    inc/expr/Identifier.h
    src/expr/InfixExpression.cpp
    inc/expr/InfixExpression.h
    src/expr/InstanceOf.cpp
    inc/expr/InstanceOf.h
    src/expr/IntegerLiteral.cpp
    inc/expr/IntegerLiteral.h
    src/expr/Lambda.cpp
    inc/expr/Lambda.h
    src/expr/Literal.cpp
    inc/expr/Literal.h
    src/expr/LongLiteral.cpp
    inc/expr/LongLiteral.h
    src/expr/MarkerAnnotation.cpp
    inc/expr/MarkerAnnotation.h
    src/expr/MemberReference.cpp
    inc/expr/MemberReference.h
    src/expr/MethodInvocation.cpp
    inc/expr/MethodInvocation.h
    src/expr/NewArray.cpp
    inc/expr/NewArray.h
    src/expr/NewClass.cpp
    inc/expr/NewClass.h
    src/expr/NormalAnnotation.cpp
    inc/expr/NormalAnnotation.h
    src/expr/NullLiteral.cpp
    inc/expr/NullLiteral.h
    src/expr/NumberLiteral.cpp
    inc/expr/NumberLiteral.h
    src/expr/ParenthesizedExpression.cpp
    inc/expr/ParenthesizedExpression.h
    src/expr/PolyExpression.cpp
    inc/expr/PolyExpression.h
    src/expr/PostfixExpression.cpp
    inc/expr/PostfixExpression.h
    src/expr/PrefixExpression.cpp
    inc/expr/PrefixExpression.h
    src/expr/PrimitiveTypeExpression.cpp
    inc/expr/PrimitiveTypeExpression.h
    src/expr/QualifiedTypeExpression.cpp
    inc/expr/QualifiedTypeExpression.h
    src/expr/SimpleTypeExpression.cpp
    inc/expr/SimpleTypeExpression.h
    src/expr/SingleElementAnnotation.cpp
    inc/expr/SingleElementAnnotation.h
    src/expr/StringLiteral.cpp
    inc/expr/StringLiteral.h
    src/expr/Super.cpp
    inc/expr/Super.h
    src/expr/This.cpp
    inc/expr/This.h
    src/expr/TypeApplyExpression.cpp
    inc/expr/TypeApplyExpression.h
    src/expr/TypeCast.cpp
    inc/expr/TypeCast.h
    src/expr/TypeExpression.cpp
    inc/expr/TypeExpression.h
    src/expr/TypeIntersectionExpression.cpp
    inc/expr/TypeIntersectionExpression.h
    src/expr/TypeUnionExpression.cpp
    inc/expr/TypeUnionExpression.h
    src/expr/Unary.cpp
    inc/expr/Unary.h
    src/expr/WildcardExpression.cpp
    inc/expr/WildcardExpression.h
    src/module/Exports.cpp
    inc/module/Exports.h
    src/module/ModuleDirective.cpp
    inc/module/ModuleDirective.h
    src/module/Opens.cpp
    inc/module/Opens.h
    src/module/Provides.cpp
    inc/module/Provides.h
    src/module/Requires.cpp
    inc/module/Requires.h
    src/module/Uses.cpp
    inc/module/Uses.h
    src/statm/Assert.cpp
    inc/statm/Assert.h
    src/statm/BasicFor.cpp
    inc/statm/BasicFor.h
    src/statm/Block.cpp
    inc/statm/Block.h
    src/statm/Break.cpp
    inc/statm/Break.h
    src/statm/Case.cpp
    inc/statm/Case.h
    src/statm/Continue.cpp
    inc/statm/Continue.h
    src/statm/Default.cpp
    inc/statm/Default.h
    src/statm/Do.cpp
    inc/statm/Do.h
    src/statm/Empty.cpp
    inc/statm/Empty.h
    src/statm/EnhancedFor.cpp
    inc/statm/EnhancedFor.h
    src/statm/ExpressionStatement.cpp
    inc/statm/ExpressionStatement.h
    src/statm/For.cpp
    inc/statm/For.h
    src/statm/Handler.cpp
    inc/statm/Handler.h
    src/statm/If.cpp
    inc/statm/If.h
    src/statm/Iteration.cpp
    inc/statm/Iteration.h
    src/statm/Jump.cpp
    inc/statm/Jump.h
    src/statm/LabeledStatement.cpp
    inc/statm/LabeledStatement.h
    src/statm/Return.cpp
    inc/statm/Return.h
    src/statm/Selection.cpp
    inc/statm/Selection.h
    src/statm/Statement.cpp
    inc/statm/Statement.h
    src/statm/Switch.cpp
    inc/statm/Switch.h
    src/statm/SwitchLabel.cpp
    inc/statm/SwitchLabel.h
    src/statm/Synchronized.cpp
    inc/statm/Synchronized.h
    src/statm/Throw.cpp
    inc/statm/Throw.h
    src/statm/Try.cpp
    inc/statm/Try.h
    src/statm/While.cpp
    inc/statm/While.h
    src/struc/AnnotatedElement.cpp
    inc/struc/AnnotatedElement.h
    src/struc/AnnotationType.cpp
    inc/struc/AnnotationType.h
    src/struc/AnnotationTypeElement.cpp
    inc/struc/AnnotationTypeElement.h
    src/struc/AnonymousClass.cpp
    inc/struc/AnonymousClass.h
    src/struc/Class.cpp
    inc/struc/Class.h
    src/struc/ClassDeclaration.cpp
    inc/struc/ClassDeclaration.h
    src/struc/ClassGeneric.cpp
    inc/struc/ClassGeneric.h
    src/struc/CompilationUnit.cpp
    inc/struc/CompilationUnit.h
    src/struc/Declaration.cpp
    inc/struc/Declaration.h
    src/struc/Enum.cpp
    inc/struc/Enum.h
    src/struc/EnumConstant.cpp
    inc/struc/EnumConstant.h
    src/struc/GenericDeclaration.cpp
    inc/struc/GenericDeclaration.h
    src/struc/Import.cpp
    inc/struc/Import.h
    src/struc/InitializerBlock.cpp
    inc/struc/InitializerBlock.h
    src/struc/InstanceInitializerBlock.cpp
    inc/struc/InstanceInitializerBlock.h
    src/struc/Interface.cpp
    inc/struc/Interface.h
    src/struc/InterfaceDeclaration.cpp
    inc/struc/InterfaceDeclaration.h
    src/struc/InterfaceGeneric.cpp
    inc/struc/InterfaceGeneric.h
    src/struc/Member.cpp
    inc/struc/Member.h
    src/struc/Method.cpp
    inc/struc/Method.h
    src/struc/MethodDeclaration.cpp
    inc/struc/MethodDeclaration.h
    src/struc/MethodGeneric.cpp
    inc/struc/MethodGeneric.h
    src/struc/Module.cpp
    inc/struc/Module.h
    src/struc/ModuleDeclaration.cpp
    inc/struc/ModuleDeclaration.h
    src/struc/NamedDeclaration.cpp
    inc/struc/NamedDeclaration.h
    src/struc/NormalMethod.cpp
    inc/struc/NormalMethod.h
    src/struc/Package.cpp
    inc/struc/Package.h
    src/struc/PackageDeclaration.cpp
    inc/struc/PackageDeclaration.h
    src/struc/Parameter.cpp
    inc/struc/Parameter.h
    src/struc/Scope.cpp
    inc/struc/Scope.h
    src/struc/StaticInitializerBlock.cpp
    inc/struc/StaticInitializerBlock.h
    src/struc/TypeDeclaration.cpp
    inc/struc/TypeDeclaration.h
    src/struc/TypeParameter.cpp
    inc/struc/TypeParameter.h
    src/struc/Variable.cpp
    inc/struc/Variable.h
    src/struc/VariableDeclaration.cpp
    inc/struc/VariableDeclaration.h
    src/type/ArrayType.cpp
    inc/type/ArrayType.h
    src/type/BooleanType.cpp
    inc/type/BooleanType.h
    src/type/BoundedWildcardType.cpp
    inc/type/BoundedWildcardType.h
    src/type/ByteType.cpp
    inc/type/ByteType.h
    src/type/CharType.cpp
    inc/type/CharType.h
    src/type/ClassType.cpp
    inc/type/ClassType.h
    src/type/DoubleType.cpp
    inc/type/DoubleType.h
    src/type/ErrorType.cpp
    inc/type/ErrorType.h
    src/type/FloatType.cpp
    inc/type/FloatType.h
    src/type/IntType.cpp
    inc/type/IntType.h
    src/type/IntersectionType.cpp
    inc/type/IntersectionType.h
    src/type/LongType.cpp
    inc/type/LongType.h
    src/type/LowerBoundedWildcardType.cpp
    inc/type/LowerBoundedWildcardType.h
    src/type/MethodType.cpp
    inc/type/MethodType.h
    src/type/ModuleType.cpp
    inc/type/ModuleType.h
    src/type/NoType.cpp
    inc/type/NoType.h
    src/type/NullType.cpp
    inc/type/NullType.h
    src/type/PackageType.cpp
    inc/type/PackageType.h
    src/type/ParameterizedType.cpp
    inc/type/ParameterizedType.h
    src/type/PrimitiveType.cpp
    inc/type/PrimitiveType.h
    src/type/ScopedType.cpp
    inc/type/ScopedType.h
    src/type/ShortType.cpp
    inc/type/ShortType.h
    src/type/Type.cpp
    inc/type/Type.h
    src/type/TypeVariable.cpp
    inc/type/TypeVariable.h
    src/type/UnboundedWildcardType.cpp
    inc/type/UnboundedWildcardType.h
    src/type/UnionType.cpp
    inc/type/UnionType.h
    src/type/UpperBoundedWildcardType.cpp
    inc/type/UpperBoundedWildcardType.h
    src/type/VoidType.cpp
    inc/type/VoidType.h
    src/type/WildcardType.cpp
    inc/type/WildcardType.h
    inc/algorithms/AlgorithmCreates.h
    src/algorithms/AlgorithmCreates.cpp
    inc/visitors/VisitorJANFilter.h
    src/visitors/VisitorJANFilter.cpp
    inc/visitors/VisitorUniqueNames.h
    src/visitors/VisitorUniqueNames.cpp
    inc/messages.h
)

add_library (${LIBNAME} STATIC ${SOURCES})
add_dependencies (${LIBNAME} boost)
set_visual_studio_project_folder(${LIBNAME} TRUE)
