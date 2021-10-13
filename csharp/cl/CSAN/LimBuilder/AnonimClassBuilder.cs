using System;
using System.Collections.Generic;
using System.Linq;
using Columbus.CSAN.Contexts;
using Columbus.CSAN.Metrics.Size;
using Columbus.CSAN.Utils.Info;
using Columbus.Lim.Asg;
using Columbus.Lim.Asg.Nodes.Logical;
using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis.CSharp.Syntax;
using Attribute = Columbus.Lim.Asg.Nodes.Logical.Attribute;
using Type = Columbus.Lim.Asg.Nodes.Type.Type;

namespace Columbus.CSAN.LimBuilder
{
    using AnonimClass = AnonymousObjectCreationExpressionSyntax;
    using AnonimClassMember = AnonymousObjectMemberDeclaratorSyntax;

    internal class AnonimClassBuilder
    {
        private readonly INamedTypeSymbol anonimClass;
        private readonly AnonimClass anonymousObjectCreastionExpression;
        private readonly Class limClass;
        private readonly Dictionary< CSharpSyntaxNode, uint > csharpMap;
        private readonly FileContext fileContext;
        private readonly ProjectContext projectContext;
        private readonly SolutionContext solutionContext;
        private readonly SymbolConverter symbolConverter;
        private readonly EdgeBuilder edgeBuilder;

        public AnonimClassBuilder(INamedTypeSymbol anonimClass, AnonimClass anonymousObjectCreastionExpression, FileContext fileContext)
        {
            this.anonimClass = anonimClass;
            this.anonymousObjectCreastionExpression = anonymousObjectCreastionExpression;
            this.fileContext = fileContext;
            projectContext = fileContext.ProjectContext;
            solutionContext = projectContext.SolutionContext;

            csharpMap = projectContext.CsharpMap;
            symbolConverter = new SymbolConverter(fileContext);
            edgeBuilder = new EdgeBuilder(fileContext);

            limClass = symbolConverter.ConvertToLimNode(anonimClass) as Class;
        }

        /// <summary>
        ///     Anonymous class will be built
        /// </summary>
        public void Build( )
        {
            FillClassProperties();

            foreach ( var member in anonimClass.GetMembers( ) )
            {
                if (!(member is IPropertySymbol propertySymbol))
                    continue;
                if (!(propertySymbol.DeclaringSyntaxReferences.FirstOrDefault()?.GetSyntax() is AnonymousObjectMemberDeclaratorSyntax memberDeclarator))
                    throw new Exception("The property of an anonymous class is not declared by an AnonymousObjectDeclaratorSyntax");
                var getterNode = (Method)symbolConverter.ConvertToLimNode(propertySymbol.GetMethod);
                FillGetterMethodNodeProperties(propertySymbol.GetMethod, getterNode, memberDeclarator);
            }
        }

        private void FillClassProperties()
        {
            limClass.Accessibility = Types.AccessibilityKind.ackInternal;
            limClass.Name = anonimClass.ToString( );

            uint parentId;
            if (fileContext.MethodStack.TryPeek(out var methodInfo))
            {
                parentId = methodInfo.Id;
                methodInfo.Instantiates.Add(new KeyValuePair<uint, bool>(symbolConverter.GetLimType(anonimClass).Id, false));
            }
            else
                parentId = fileContext.ClassStack.Peek().Id;
            var parent = (Scope)solutionContext.LimFactory.getRef(parentId);

            limClass.MangledName = limClass.DemangledName = parent.MangledName + "." + anonimClass;
            limClass.IsCompilerGenerated = true;
            limClass.IsAnonymous = true;
            limClass.ClassKind = Types.ClassKind.clkClass;

            Commons.Common.Safe_Edge( parent, "HasMember", limClass.Id );
            solutionContext.LimOrigin.addCompIdCsharpIdLimIdToMap(projectContext.Component.Id, csharpMap[anonymousObjectCreastionExpression], limClass.Id);
            fileContext.ClassStack.Push( new ClassInfo( limClass.Id ) );
            fileContext.LlocCalculator.CollectLineInfos( anonymousObjectCreastionExpression );
            fileContext.ClassStack.Pop( );
            limClass.SetCLOC( anonymousObjectCreastionExpression );
            edgeBuilder.AddIsContainedInEdge( limClass, anonymousObjectCreastionExpression );
            Commons.Common.Safe_Edge( limClass, "BelongsTo", projectContext.Component.Id );
        }

        private Attribute CreateCompilerGeneratedAttributeNode(ISymbol member, Type limType, AnonymousObjectMemberDeclaratorSyntax memberDeclarator)
        {
            var limAttribute = solutionContext.LimFactory.createAttributeNode();
            limAttribute.Name = member.Name.Substring( "get_".Length );
            limAttribute.MangledName = limClass.MangledName + "." + limAttribute.Name;
            limAttribute.DemangledName = limAttribute.MangledName;
            limAttribute.addHasType( limType );
            limAttribute.Language = Types.LanguageKind.lnkCsharp;
            limAttribute.IsCompilerGenerated = true;
            limAttribute.addBelongsTo(projectContext.Component);

            if (memberDeclarator.NameEquals == null)
                edgeBuilder.AddIsContainedInEdge(limAttribute, memberDeclarator);
            else
                edgeBuilder.AddIsContainedInEdge(limAttribute, memberDeclarator.NameEquals.Name);

            return limAttribute;
        }

        /// <summary>
        ///     Common Method's properties filler
        /// </summary>
        /// <param name="member">Actual Method symbol</param>
        /// <param name="node">Actual</param>
        /// <param name="limClass"></param>
        private void CommonMethodProperties( ISymbol member, Method node )
        {
            node.Name = member.Name;
            node.MangledName = node.DemangledName = string.Format( "{0}.{1}", limClass.MangledName, node.Name );
            node.IsCompilerGenerated = true;
            node.NumberOfBranches = 1;
            node.Accessibility = Types.AccessibilityKind.ackPublic;
            node.addBelongsTo(projectContext.Component);

            limClass.addHasMember( node );
        }

        /// <summary>
        ///     Fill anonymous class's method properties
        /// </summary>
        /// <param name="member">Method's symbol</param>
        /// <param name="node">Actual node from LIM</param>
        /// <param name="anonymousObjectMemberDeclarator"></param>
        private void FillGetterMethodNodeProperties( ISymbol member, Method node, AnonymousObjectMemberDeclaratorSyntax anonymousObjectMemberDeclarator )
        {
            var returnType = ( ( IMethodSymbol ) member ).ReturnType;
            var limType = symbolConverter.GetLimType(returnType);
            GenerateAttributeAccess( member, node, limType, anonymousObjectMemberDeclarator );
            CommonMethodProperties( member, node );
            node.NumberOfStatements = 1;
            node.addReturns( limType );
            node.MethodKind = Types.MethodKind.mekGet;

            solutionContext.LimOrigin.addCompIdCsharpIdLimIdToMap(projectContext.Component.Id, csharpMap[anonymousObjectMemberDeclarator], node.Id);
            node.SetCLOC(anonymousObjectMemberDeclarator);
            fileContext.MethodStack.Push(new MethodInfo(node.Id));
            fileContext.RoslynVisitor.Visit(anonymousObjectMemberDeclarator.Expression);
            fileContext.LlocCalculator.CollectLineInfos(anonymousObjectMemberDeclarator);
            fileContext.RoslynVisitor.FillFromMethodStack(fileContext.MethodStack.Pop(), false);
            symbolConverter.CreateCommentNode(anonymousObjectMemberDeclarator, member);
            edgeBuilder.AddIsContainedInEdge(node, anonymousObjectMemberDeclarator);
        }

        /// <summary>
        ///     Generate Attribute node and connect to the Method node
        /// </summary>
        /// <param name="member">Actual IMethodSymbol reference</param>
        /// <param name="node">Method node which connect to Attribute through AttributeAccess</param>
        /// <param name="limType">Attribute node's type</param>
        private void GenerateAttributeAccess( ISymbol member, Method node, Type limType, AnonymousObjectMemberDeclaratorSyntax memberDeclarator )
        {
            var limAttribute = CreateCompilerGeneratedAttributeNode( member, limType, memberDeclarator );
            var ac = solutionContext.LimFactory.createAttributeAccessNode(limAttribute.Id);
            node.addAccessesAttribute( ac );
            limClass.addHasMember( limAttribute );
        }
    }
}
