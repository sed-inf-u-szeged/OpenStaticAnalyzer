/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2018 Department of Software Engineering - University of Szeged
 *
 *  Licensed under Version 1.2 of the EUPL (the "Licence");
 *
 *  You may not use this work except in compliance with the Licence.
 *
 *  You may obtain a copy of the Licence in the LICENSE file or at:
 *
 *  https://joinup.ec.europa.eu/software/page/eupl
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the Licence is distributed on an "AS IS" basis,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the Licence for the specific language governing permissions and
 *  limitations under the Licence.
 */

using System;
using System.IO;
using System.Collections.Generic;
using System.Text;

namespace Columbus.Csharp.Asg.Visitors {

    /// <summary>
    /// Creates XML dump of the ASG.
    /// </summary>
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class VisitorCSHARPML : Visitor {

        /// <summary>The ofstrem into the xml will be written.</summary>
        protected StreamWriter writer;

        /// <summary>Function pointer of a message writer function.</summary>
        protected WriteMessageFunc writeMsg;

        /// <summary>Flag to know if the ID of the nodes have to be written or not.</summary>
        protected bool bNoId;

        /// <summary>Name of the project we are saving</summary>
        protected string projectName;

        /// <summary>Delegate type for the message writer.</summary>
        public delegate void WriteMessageFunc(string message);

        /// <summary>
        /// Constructor of XML generator visitor.
        /// </summary>
        /// <param name="targetStream">[in] StreamWriter to write the output.</param>
        /// <param name="projectName">[in] Name of project - generated into the output.</param>
        /// <param name="encodingFromWriter">[in] The encoding in the XML header will be the StreamWriters encoding.</param>
        /// <param name="writeMessage">[in] Delegate of a message writer function.</param>
        /// <param name="noId">[in] Do not write the ID of the nodes.</param>
        public VisitorCSHARPML(StreamWriter targetStream, string projectName, bool encodingFromWriter, WriteMessageFunc writeMessage, bool noId) : base() {
            writer = targetStream;
            writeMsg = writeMessage;
            bNoId = noId;
            this.projectName = projectName;

        }

        /// <summary>
        /// Begin the XML dumping.
        /// </summary>
        public override void beginVisit() {
            writer.WriteLine("<?xml version='1.0' encoding=\"" + ((writer!=null) ? writer.Encoding.BodyName : "utf-8") + "\"?>");
            writer.WriteLine("<!DOCTYPE Project SYSTEM 'csharp-0.9.dtd'>");
            writer.Write("<Project name='{0}'", projectName);
            writer.Write(" xmlns:base='columbus_csharp_schema/base'");
            writer.Write(" xmlns:expression='columbus_csharp_schema/expression'");
            writer.Write(" xmlns:statement='columbus_csharp_schema/statement'");
            writer.Write(" xmlns:structure='columbus_csharp_schema/structure'");
            writer.WriteLine(">");
        }

        /// <summary>
        /// Finishes the XML dumping.
        /// </summary>
        public override void finishVisit() {
            writer.WriteLine("<Filtered id='id1'/>");
            writer.WriteLine("</Project>");
        }

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.AliasQualifiedNameSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:AliasQualifiedNameSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.AliasQualifiedNameSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:AliasQualifiedNameSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.AnonymousMethodExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:AnonymousMethodExpressionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.AnonymousMethodExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:AnonymousMethodExpressionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.AnonymousObjectCreationExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:AnonymousObjectCreationExpressionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.AnonymousObjectCreationExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:AnonymousObjectCreationExpressionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ArrayCreationExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:ArrayCreationExpressionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ArrayCreationExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:ArrayCreationExpressionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ArrayTypeSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:ArrayTypeSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ArrayTypeSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:ArrayTypeSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.AssignmentExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:AssignmentExpressionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.AssignmentExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:AssignmentExpressionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.AwaitExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:AwaitExpressionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.AwaitExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:AwaitExpressionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.BaseExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:BaseExpressionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.BaseExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:BaseExpressionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.BinaryExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:BinaryExpressionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.BinaryExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:BinaryExpressionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.CastExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:CastExpressionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.CastExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:CastExpressionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.CheckedExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:CheckedExpressionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.CheckedExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:CheckedExpressionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ConditionalAccessExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:ConditionalAccessExpressionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ConditionalAccessExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:ConditionalAccessExpressionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ConditionalExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:ConditionalExpressionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ConditionalExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:ConditionalExpressionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.DefaultExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:DefaultExpressionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.DefaultExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:DefaultExpressionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ElementAccessExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:ElementAccessExpressionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ElementAccessExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:ElementAccessExpressionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ElementBindingExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:ElementBindingExpressionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ElementBindingExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:ElementBindingExpressionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.GenericNameSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:GenericNameSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.GenericNameSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:GenericNameSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.IdentifierNameSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:IdentifierNameSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.IdentifierNameSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:IdentifierNameSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ImplicitArrayCreationExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:ImplicitArrayCreationExpressionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ImplicitArrayCreationExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:ImplicitArrayCreationExpressionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ImplicitElementAccessSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:ImplicitElementAccessSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ImplicitElementAccessSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:ImplicitElementAccessSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.InitializerExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:InitializerExpressionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.InitializerExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:InitializerExpressionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.InterpolatedStringExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:InterpolatedStringExpressionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.InterpolatedStringExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:InterpolatedStringExpressionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.InvocationExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:InvocationExpressionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.InvocationExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:InvocationExpressionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.LiteralExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:LiteralExpressionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.LiteralExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:LiteralExpressionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.MakeRefExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:MakeRefExpressionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.MakeRefExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:MakeRefExpressionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.MemberAccessExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:MemberAccessExpressionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.MemberAccessExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:MemberAccessExpressionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.MemberBindingExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:MemberBindingExpressionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.MemberBindingExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:MemberBindingExpressionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.NullableTypeSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:NullableTypeSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.NullableTypeSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:NullableTypeSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ObjectCreationExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:ObjectCreationExpressionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ObjectCreationExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:ObjectCreationExpressionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.OmittedArraySizeExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:OmittedArraySizeExpressionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.OmittedArraySizeExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:OmittedArraySizeExpressionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.OmittedTypeArgumentSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:OmittedTypeArgumentSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.OmittedTypeArgumentSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:OmittedTypeArgumentSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:ParenthesizedExpressionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:ParenthesizedExpressionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedLambdaExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:ParenthesizedLambdaExpressionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedLambdaExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:ParenthesizedLambdaExpressionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.PointerTypeSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:PointerTypeSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.PointerTypeSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:PointerTypeSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.PostfixUnaryExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:PostfixUnaryExpressionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.PostfixUnaryExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:PostfixUnaryExpressionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.PredefinedTypeSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:PredefinedTypeSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.PredefinedTypeSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:PredefinedTypeSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.PrefixUnaryExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:PrefixUnaryExpressionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.PrefixUnaryExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:PrefixUnaryExpressionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.QualifiedNameSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:QualifiedNameSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.QualifiedNameSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:QualifiedNameSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.QueryExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:QueryExpressionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.QueryExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:QueryExpressionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.RefTypeExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:RefTypeExpressionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.RefTypeExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:RefTypeExpressionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.RefValueExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:RefValueExpressionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.RefValueExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:RefValueExpressionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.SimpleLambdaExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:SimpleLambdaExpressionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.SimpleLambdaExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:SimpleLambdaExpressionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.SizeOfExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:SizeOfExpressionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.SizeOfExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:SizeOfExpressionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.StackAllocArrayCreationExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:StackAllocArrayCreationExpressionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.StackAllocArrayCreationExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:StackAllocArrayCreationExpressionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.ThisExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:ThisExpressionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.ThisExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:ThisExpressionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Expression.TypeOfExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<expression:TypeOfExpressionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Expression.TypeOfExpressionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</expression:TypeOfExpressionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<statement:BlockSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</statement:BlockSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Statement.BreakStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<statement:BreakStatementSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.BreakStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</statement:BreakStatementSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Statement.CheckedStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<statement:CheckedStatementSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.CheckedStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</statement:CheckedStatementSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Statement.ContinueStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<statement:ContinueStatementSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.ContinueStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</statement:ContinueStatementSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Statement.DoStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<statement:DoStatementSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.DoStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</statement:DoStatementSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Statement.EmptyStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<statement:EmptyStatementSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.EmptyStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</statement:EmptyStatementSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Statement.ExpressionStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<statement:ExpressionStatementSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.ExpressionStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</statement:ExpressionStatementSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Statement.FixedStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<statement:FixedStatementSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.FixedStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</statement:FixedStatementSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Statement.ForEachStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<statement:ForEachStatementSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.ForEachStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</statement:ForEachStatementSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Statement.ForStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<statement:ForStatementSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.ForStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</statement:ForStatementSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Statement.GotoStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<statement:GotoStatementSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.GotoStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</statement:GotoStatementSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Statement.IfStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<statement:IfStatementSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.IfStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</statement:IfStatementSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Statement.LabeledStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<statement:LabeledStatementSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.LabeledStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</statement:LabeledStatementSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Statement.LocalDeclarationStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<statement:LocalDeclarationStatementSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.LocalDeclarationStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</statement:LocalDeclarationStatementSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Statement.LockStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<statement:LockStatementSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.LockStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</statement:LockStatementSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Statement.ReturnStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<statement:ReturnStatementSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.ReturnStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</statement:ReturnStatementSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Statement.SwitchStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<statement:SwitchStatementSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.SwitchStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</statement:SwitchStatementSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Statement.ThrowStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<statement:ThrowStatementSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.ThrowStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</statement:ThrowStatementSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Statement.TryStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<statement:TryStatementSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.TryStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</statement:TryStatementSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Statement.UnsafeStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<statement:UnsafeStatementSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.UnsafeStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</statement:UnsafeStatementSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Statement.UsingStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<statement:UsingStatementSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.UsingStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</statement:UsingStatementSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Statement.WhileStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<statement:WhileStatementSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.WhileStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</statement:WhileStatementSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Statement.YieldStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<statement:YieldStatementSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Statement.YieldStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</statement:YieldStatementSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.AccessorDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:AccessorDeclarationSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.AccessorDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:AccessorDeclarationSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.AccessorListSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:AccessorListSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.AccessorListSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:AccessorListSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.AnonymousObjectMemberDeclaratorSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:AnonymousObjectMemberDeclaratorSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.AnonymousObjectMemberDeclaratorSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:AnonymousObjectMemberDeclaratorSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ArgumentListSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:ArgumentListSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ArgumentListSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:ArgumentListSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ArgumentSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:ArgumentSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ArgumentSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:ArgumentSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ArrayRankSpecifierSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:ArrayRankSpecifierSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ArrayRankSpecifierSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:ArrayRankSpecifierSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ArrowExpressionClauseSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:ArrowExpressionClauseSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ArrowExpressionClauseSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:ArrowExpressionClauseSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentListSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:AttributeArgumentListSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentListSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:AttributeArgumentListSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:AttributeArgumentSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:AttributeArgumentSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:AttributeListSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:AttributeListSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.AttributeSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:AttributeSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.AttributeSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:AttributeSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.AttributeTargetSpecifierSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:AttributeTargetSpecifierSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.AttributeTargetSpecifierSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:AttributeTargetSpecifierSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.BaseListSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:BaseListSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.BaseListSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:BaseListSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.BracketedArgumentListSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:BracketedArgumentListSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.BracketedArgumentListSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:BracketedArgumentListSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.BracketedParameterListSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:BracketedParameterListSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.BracketedParameterListSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:BracketedParameterListSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.CaseSwitchLabelSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:CaseSwitchLabelSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.CaseSwitchLabelSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:CaseSwitchLabelSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.CatchClauseSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:CatchClauseSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.CatchClauseSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:CatchClauseSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.CatchDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:CatchDeclarationSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.CatchDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:CatchDeclarationSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.CatchFilterClauseSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:CatchFilterClauseSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.CatchFilterClauseSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:CatchFilterClauseSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ClassDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:ClassDeclarationSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ClassDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:ClassDeclarationSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ClassOrStructConstraintSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:ClassOrStructConstraintSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ClassOrStructConstraintSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:ClassOrStructConstraintSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.CompilationUnitSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:CompilationUnitSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.CompilationUnitSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:CompilationUnitSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ConstructorConstraintSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:ConstructorConstraintSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ConstructorConstraintSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:ConstructorConstraintSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ConstructorDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:ConstructorDeclarationSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ConstructorDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:ConstructorDeclarationSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ConstructorInitializerSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:ConstructorInitializerSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ConstructorInitializerSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:ConstructorInitializerSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:ConversionOperatorDeclarationSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:ConversionOperatorDeclarationSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorMemberCrefSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:ConversionOperatorMemberCrefSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorMemberCrefSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:ConversionOperatorMemberCrefSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.CrefBracketedParameterListSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:CrefBracketedParameterListSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.CrefBracketedParameterListSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:CrefBracketedParameterListSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.CrefParameterListSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:CrefParameterListSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.CrefParameterListSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:CrefParameterListSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.CrefParameterSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:CrefParameterSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.CrefParameterSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:CrefParameterSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.DefaultSwitchLabelSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:DefaultSwitchLabelSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.DefaultSwitchLabelSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:DefaultSwitchLabelSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.DelegateDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:DelegateDeclarationSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.DelegateDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:DelegateDeclarationSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.DestructorDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:DestructorDeclarationSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.DestructorDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:DestructorDeclarationSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ElseClauseSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:ElseClauseSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ElseClauseSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:ElseClauseSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.EnumDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:EnumDeclarationSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.EnumDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:EnumDeclarationSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.EnumMemberDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:EnumMemberDeclarationSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.EnumMemberDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:EnumMemberDeclarationSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.EqualsValueClauseSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:EqualsValueClauseSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.EqualsValueClauseSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:EqualsValueClauseSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.EventDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:EventDeclarationSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.EventDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:EventDeclarationSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.EventFieldDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:EventFieldDeclarationSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.EventFieldDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:EventFieldDeclarationSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ExplicitInterfaceSpecifierSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:ExplicitInterfaceSpecifierSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ExplicitInterfaceSpecifierSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:ExplicitInterfaceSpecifierSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ExternAliasDirectiveSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:ExternAliasDirectiveSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ExternAliasDirectiveSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:ExternAliasDirectiveSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.FieldDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:FieldDeclarationSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.FieldDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:FieldDeclarationSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.FinallyClauseSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:FinallyClauseSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.FinallyClauseSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:FinallyClauseSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.FromClauseSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:FromClauseSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.FromClauseSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:FromClauseSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.GlobalStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:GlobalStatementSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.GlobalStatementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:GlobalStatementSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.GroupClauseSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:GroupClauseSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.GroupClauseSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:GroupClauseSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.IncompleteMemberSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:IncompleteMemberSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.IncompleteMemberSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:IncompleteMemberSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.IndexerDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:IndexerDeclarationSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.IndexerDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:IndexerDeclarationSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.IndexerMemberCrefSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:IndexerMemberCrefSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.IndexerMemberCrefSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:IndexerMemberCrefSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.InterfaceDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:InterfaceDeclarationSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.InterfaceDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:InterfaceDeclarationSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringTextSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:InterpolatedStringTextSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringTextSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:InterpolatedStringTextSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.InterpolationAlignmentClauseSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:InterpolationAlignmentClauseSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.InterpolationAlignmentClauseSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:InterpolationAlignmentClauseSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.InterpolationFormatClauseSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:InterpolationFormatClauseSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.InterpolationFormatClauseSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:InterpolationFormatClauseSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.InterpolationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:InterpolationSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.InterpolationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:InterpolationSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.JoinClauseSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:JoinClauseSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.JoinClauseSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:JoinClauseSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.JoinIntoClauseSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:JoinIntoClauseSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.JoinIntoClauseSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:JoinIntoClauseSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.LetClauseSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:LetClauseSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.LetClauseSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:LetClauseSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.MethodDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:MethodDeclarationSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.MethodDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:MethodDeclarationSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.NameColonSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:NameColonSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.NameColonSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:NameColonSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.NameEqualsSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:NameEqualsSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.NameEqualsSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:NameEqualsSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.NameMemberCrefSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:NameMemberCrefSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.NameMemberCrefSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:NameMemberCrefSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.NamespaceDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:NamespaceDeclarationSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.NamespaceDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:NamespaceDeclarationSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.OperatorDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:OperatorDeclarationSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.OperatorDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:OperatorDeclarationSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.OperatorMemberCrefSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:OperatorMemberCrefSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.OperatorMemberCrefSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:OperatorMemberCrefSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.OrderByClauseSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:OrderByClauseSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.OrderByClauseSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:OrderByClauseSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.OrderingSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:OrderingSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.OrderingSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:OrderingSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ParameterListSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:ParameterListSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ParameterListSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:ParameterListSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.ParameterSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:ParameterSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.ParameterSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:ParameterSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.PropertyDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:PropertyDeclarationSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.PropertyDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:PropertyDeclarationSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.QualifiedCrefSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:QualifiedCrefSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.QualifiedCrefSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:QualifiedCrefSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.QueryBodySyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:QueryBodySyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.QueryBodySyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:QueryBodySyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.QueryContinuationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:QueryContinuationSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.QueryContinuationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:QueryContinuationSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.SelectClauseSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:SelectClauseSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.SelectClauseSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:SelectClauseSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.SimpleBaseTypeSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:SimpleBaseTypeSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.SimpleBaseTypeSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:SimpleBaseTypeSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.StructDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:StructDeclarationSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.StructDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:StructDeclarationSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.SwitchSectionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:SwitchSectionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.SwitchSectionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:SwitchSectionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.SyntaxToken node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:SyntaxToken");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.SyntaxToken node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:SyntaxToken>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.TypeArgumentListSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:TypeArgumentListSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.TypeArgumentListSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:TypeArgumentListSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.TypeConstraintSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:TypeConstraintSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.TypeConstraintSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:TypeConstraintSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.TypeCrefSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:TypeCrefSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.TypeCrefSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:TypeCrefSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:TypeParameterConstraintClauseSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:TypeParameterConstraintClauseSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.TypeParameterListSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:TypeParameterListSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.TypeParameterListSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:TypeParameterListSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.TypeParameterSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:TypeParameterSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.TypeParameterSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:TypeParameterSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.UsingDirectiveSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:UsingDirectiveSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.UsingDirectiveSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:UsingDirectiveSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.VariableDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:VariableDeclarationSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.VariableDeclarationSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:VariableDeclarationSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.VariableDeclaratorSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:VariableDeclaratorSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.VariableDeclaratorSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:VariableDeclaratorSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.WhereClauseSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:WhereClauseSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.WhereClauseSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:WhereClauseSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlCDataSectionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:XmlCDataSectionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlCDataSectionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:XmlCDataSectionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlCommentSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:XmlCommentSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlCommentSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:XmlCommentSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlCrefAttributeSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:XmlCrefAttributeSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlCrefAttributeSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:XmlCrefAttributeSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlElementEndTagSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:XmlElementEndTagSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlElementEndTagSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:XmlElementEndTagSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlElementStartTagSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:XmlElementStartTagSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlElementStartTagSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:XmlElementStartTagSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlElementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:XmlElementSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlElementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:XmlElementSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlEmptyElementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:XmlEmptyElementSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlEmptyElementSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:XmlEmptyElementSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlNameAttributeSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:XmlNameAttributeSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlNameAttributeSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:XmlNameAttributeSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlNameSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:XmlNameSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlNameSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:XmlNameSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlPrefixSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:XmlPrefixSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlPrefixSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:XmlPrefixSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlProcessingInstructionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:XmlProcessingInstructionSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlProcessingInstructionSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:XmlProcessingInstructionSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlTextAttributeSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:XmlTextAttributeSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlTextAttributeSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:XmlTextAttributeSyntax>\n");
}

public override void visit(Columbus.Csharp.Asg.Nodes.Structure.XmlTextSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<structure:XmlTextSyntax");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Csharp.Asg.Nodes.Structure.XmlTextSyntax node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</structure:XmlTextSyntax>\n");
}

public override void visitAliasQualifiedNameSyntax_Alias(uint begin, uint end) {
    createIndentation();
    writer.Write("<AliasQualifiedNameSyntax_Alias>\n");
    incDepth();
}

public override void visitEndAliasQualifiedNameSyntax_Alias(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</AliasQualifiedNameSyntax_Alias>\n");
}

public override void visitAliasQualifiedNameSyntax_Name(uint begin, uint end) {
    createIndentation();
    writer.Write("<AliasQualifiedNameSyntax_Name>\n");
    incDepth();
}

public override void visitEndAliasQualifiedNameSyntax_Name(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</AliasQualifiedNameSyntax_Name>\n");
}

public override void visitAnonymousFunctionExpressionSyntax_Body(uint begin, uint end) {
    createIndentation();
    writer.Write("<AnonymousFunctionExpressionSyntax_Body>\n");
    incDepth();
}

public override void visitEndAnonymousFunctionExpressionSyntax_Body(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</AnonymousFunctionExpressionSyntax_Body>\n");
}

public override void visitAnonymousMethodExpressionSyntax_ParameterList(uint begin, uint end) {
    createIndentation();
    writer.Write("<AnonymousMethodExpressionSyntax_ParameterList>\n");
    incDepth();
}

public override void visitEndAnonymousMethodExpressionSyntax_ParameterList(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</AnonymousMethodExpressionSyntax_ParameterList>\n");
}

public override void visitAnonymousObjectCreationExpressionSyntax_Initializers(uint begin, uint end) {
    createIndentation();
    writer.Write("<AnonymousObjectCreationExpressionSyntax_Initializers>\n");
    incDepth();
}

public override void visitEndAnonymousObjectCreationExpressionSyntax_Initializers(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</AnonymousObjectCreationExpressionSyntax_Initializers>\n");
}

public override void visitArrayCreationExpressionSyntax_Initializer(uint begin, uint end) {
    createIndentation();
    writer.Write("<ArrayCreationExpressionSyntax_Initializer>\n");
    incDepth();
}

public override void visitEndArrayCreationExpressionSyntax_Initializer(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ArrayCreationExpressionSyntax_Initializer>\n");
}

public override void visitArrayCreationExpressionSyntax_Type(uint begin, uint end) {
    createIndentation();
    writer.Write("<ArrayCreationExpressionSyntax_Type>\n");
    incDepth();
}

public override void visitEndArrayCreationExpressionSyntax_Type(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ArrayCreationExpressionSyntax_Type>\n");
}

public override void visitArrayTypeSyntax_ElementType(uint begin, uint end) {
    createIndentation();
    writer.Write("<ArrayTypeSyntax_ElementType>\n");
    incDepth();
}

public override void visitEndArrayTypeSyntax_ElementType(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ArrayTypeSyntax_ElementType>\n");
}

public override void visitArrayTypeSyntax_RankSpecifiers(uint begin, uint end) {
    createIndentation();
    writer.Write("<ArrayTypeSyntax_RankSpecifiers>\n");
    incDepth();
}

public override void visitEndArrayTypeSyntax_RankSpecifiers(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ArrayTypeSyntax_RankSpecifiers>\n");
}

public override void visitAssignmentExpressionSyntax_EventAccessorCall(uint begin, uint end) {
    createIndentation();
    writer.Write("<AssignmentExpressionSyntax_EventAccessorCall ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndAssignmentExpressionSyntax_EventAccessorCall(uint begin, uint end) {
}

public override void visitAssignmentExpressionSyntax_Left(uint begin, uint end) {
    createIndentation();
    writer.Write("<AssignmentExpressionSyntax_Left>\n");
    incDepth();
}

public override void visitEndAssignmentExpressionSyntax_Left(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</AssignmentExpressionSyntax_Left>\n");
}

public override void visitAssignmentExpressionSyntax_OverloadedOperatorCall(uint begin, uint end) {
    createIndentation();
    writer.Write("<AssignmentExpressionSyntax_OverloadedOperatorCall ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndAssignmentExpressionSyntax_OverloadedOperatorCall(uint begin, uint end) {
}

public override void visitAssignmentExpressionSyntax_Right(uint begin, uint end) {
    createIndentation();
    writer.Write("<AssignmentExpressionSyntax_Right>\n");
    incDepth();
}

public override void visitEndAssignmentExpressionSyntax_Right(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</AssignmentExpressionSyntax_Right>\n");
}

public override void visitAwaitExpressionSyntax_Expression(uint begin, uint end) {
    createIndentation();
    writer.Write("<AwaitExpressionSyntax_Expression>\n");
    incDepth();
}

public override void visitEndAwaitExpressionSyntax_Expression(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</AwaitExpressionSyntax_Expression>\n");
}

public override void visitBinaryExpressionSyntax_Left(uint begin, uint end) {
    createIndentation();
    writer.Write("<BinaryExpressionSyntax_Left>\n");
    incDepth();
}

public override void visitEndBinaryExpressionSyntax_Left(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</BinaryExpressionSyntax_Left>\n");
}

public override void visitBinaryExpressionSyntax_OverloadedOperatorCall(uint begin, uint end) {
    createIndentation();
    writer.Write("<BinaryExpressionSyntax_OverloadedOperatorCall ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndBinaryExpressionSyntax_OverloadedOperatorCall(uint begin, uint end) {
}

public override void visitBinaryExpressionSyntax_Right(uint begin, uint end) {
    createIndentation();
    writer.Write("<BinaryExpressionSyntax_Right>\n");
    incDepth();
}

public override void visitEndBinaryExpressionSyntax_Right(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</BinaryExpressionSyntax_Right>\n");
}

public override void visitCastExpressionSyntax_ConversionOperatorCall(uint begin, uint end) {
    createIndentation();
    writer.Write("<CastExpressionSyntax_ConversionOperatorCall ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndCastExpressionSyntax_ConversionOperatorCall(uint begin, uint end) {
}

public override void visitCastExpressionSyntax_Expression(uint begin, uint end) {
    createIndentation();
    writer.Write("<CastExpressionSyntax_Expression>\n");
    incDepth();
}

public override void visitEndCastExpressionSyntax_Expression(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</CastExpressionSyntax_Expression>\n");
}

public override void visitCastExpressionSyntax_Type(uint begin, uint end) {
    createIndentation();
    writer.Write("<CastExpressionSyntax_Type>\n");
    incDepth();
}

public override void visitEndCastExpressionSyntax_Type(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</CastExpressionSyntax_Type>\n");
}

public override void visitCheckedExpressionSyntax_Expression(uint begin, uint end) {
    createIndentation();
    writer.Write("<CheckedExpressionSyntax_Expression>\n");
    incDepth();
}

public override void visitEndCheckedExpressionSyntax_Expression(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</CheckedExpressionSyntax_Expression>\n");
}

public override void visitConditionalAccessExpressionSyntax_Expression(uint begin, uint end) {
    createIndentation();
    writer.Write("<ConditionalAccessExpressionSyntax_Expression>\n");
    incDepth();
}

public override void visitEndConditionalAccessExpressionSyntax_Expression(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ConditionalAccessExpressionSyntax_Expression>\n");
}

public override void visitConditionalAccessExpressionSyntax_WhenNotNull(uint begin, uint end) {
    createIndentation();
    writer.Write("<ConditionalAccessExpressionSyntax_WhenNotNull>\n");
    incDepth();
}

public override void visitEndConditionalAccessExpressionSyntax_WhenNotNull(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ConditionalAccessExpressionSyntax_WhenNotNull>\n");
}

public override void visitConditionalExpressionSyntax_Condition(uint begin, uint end) {
    createIndentation();
    writer.Write("<ConditionalExpressionSyntax_Condition>\n");
    incDepth();
}

public override void visitEndConditionalExpressionSyntax_Condition(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ConditionalExpressionSyntax_Condition>\n");
}

public override void visitConditionalExpressionSyntax_WhenFalse(uint begin, uint end) {
    createIndentation();
    writer.Write("<ConditionalExpressionSyntax_WhenFalse>\n");
    incDepth();
}

public override void visitEndConditionalExpressionSyntax_WhenFalse(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ConditionalExpressionSyntax_WhenFalse>\n");
}

public override void visitConditionalExpressionSyntax_WhenTrue(uint begin, uint end) {
    createIndentation();
    writer.Write("<ConditionalExpressionSyntax_WhenTrue>\n");
    incDepth();
}

public override void visitEndConditionalExpressionSyntax_WhenTrue(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ConditionalExpressionSyntax_WhenTrue>\n");
}

public override void visitDefaultExpressionSyntax_Type(uint begin, uint end) {
    createIndentation();
    writer.Write("<DefaultExpressionSyntax_Type>\n");
    incDepth();
}

public override void visitEndDefaultExpressionSyntax_Type(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</DefaultExpressionSyntax_Type>\n");
}

public override void visitElementAccessExpressionSyntax_AccessorCall(uint begin, uint end) {
    createIndentation();
    writer.Write("<ElementAccessExpressionSyntax_AccessorCall ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndElementAccessExpressionSyntax_AccessorCall(uint begin, uint end) {
}

public override void visitElementAccessExpressionSyntax_ArgumentList(uint begin, uint end) {
    createIndentation();
    writer.Write("<ElementAccessExpressionSyntax_ArgumentList>\n");
    incDepth();
}

public override void visitEndElementAccessExpressionSyntax_ArgumentList(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ElementAccessExpressionSyntax_ArgumentList>\n");
}

public override void visitElementAccessExpressionSyntax_Expression(uint begin, uint end) {
    createIndentation();
    writer.Write("<ElementAccessExpressionSyntax_Expression>\n");
    incDepth();
}

public override void visitEndElementAccessExpressionSyntax_Expression(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ElementAccessExpressionSyntax_Expression>\n");
}

public override void visitElementBindingExpressionSyntax_ArgumentList(uint begin, uint end) {
    createIndentation();
    writer.Write("<ElementBindingExpressionSyntax_ArgumentList>\n");
    incDepth();
}

public override void visitEndElementBindingExpressionSyntax_ArgumentList(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ElementBindingExpressionSyntax_ArgumentList>\n");
}

public override void visitGenericNameSyntax_TypeArgumentList(uint begin, uint end) {
    createIndentation();
    writer.Write("<GenericNameSyntax_TypeArgumentList>\n");
    incDepth();
}

public override void visitEndGenericNameSyntax_TypeArgumentList(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</GenericNameSyntax_TypeArgumentList>\n");
}

public override void visitIdentifierNameSyntax_AccessorCall(uint begin, uint end) {
    createIndentation();
    writer.Write("<IdentifierNameSyntax_AccessorCall ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndIdentifierNameSyntax_AccessorCall(uint begin, uint end) {
}

public override void visitIdentifierNameSyntax_Declaration(uint begin, uint end) {
    createIndentation();
    writer.Write("<IdentifierNameSyntax_Declaration ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndIdentifierNameSyntax_Declaration(uint begin, uint end) {
}

public override void visitImplicitArrayCreationExpressionSyntax_Initializer(uint begin, uint end) {
    createIndentation();
    writer.Write("<ImplicitArrayCreationExpressionSyntax_Initializer>\n");
    incDepth();
}

public override void visitEndImplicitArrayCreationExpressionSyntax_Initializer(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ImplicitArrayCreationExpressionSyntax_Initializer>\n");
}

public override void visitImplicitElementAccessSyntax_ArgumentList(uint begin, uint end) {
    createIndentation();
    writer.Write("<ImplicitElementAccessSyntax_ArgumentList>\n");
    incDepth();
}

public override void visitEndImplicitElementAccessSyntax_ArgumentList(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ImplicitElementAccessSyntax_ArgumentList>\n");
}

public override void visitInitializerExpressionSyntax_Expressions(uint begin, uint end) {
    createIndentation();
    writer.Write("<InitializerExpressionSyntax_Expressions>\n");
    incDepth();
}

public override void visitEndInitializerExpressionSyntax_Expressions(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</InitializerExpressionSyntax_Expressions>\n");
}

public override void visitInterpolatedStringExpressionSyntax_Contents(uint begin, uint end) {
    createIndentation();
    writer.Write("<InterpolatedStringExpressionSyntax_Contents>\n");
    incDepth();
}

public override void visitEndInterpolatedStringExpressionSyntax_Contents(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</InterpolatedStringExpressionSyntax_Contents>\n");
}

public override void visitInvocationExpressionSyntax_ArgumentList(uint begin, uint end) {
    createIndentation();
    writer.Write("<InvocationExpressionSyntax_ArgumentList>\n");
    incDepth();
}

public override void visitEndInvocationExpressionSyntax_ArgumentList(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</InvocationExpressionSyntax_ArgumentList>\n");
}

public override void visitInvocationExpressionSyntax_Expression(uint begin, uint end) {
    createIndentation();
    writer.Write("<InvocationExpressionSyntax_Expression>\n");
    incDepth();
}

public override void visitEndInvocationExpressionSyntax_Expression(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</InvocationExpressionSyntax_Expression>\n");
}

public override void visitInvocationExpressionSyntax_MethodCall(uint begin, uint end) {
    createIndentation();
    writer.Write("<InvocationExpressionSyntax_MethodCall ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndInvocationExpressionSyntax_MethodCall(uint begin, uint end) {
}

public override void visitMakeRefExpressionSyntax_Expression(uint begin, uint end) {
    createIndentation();
    writer.Write("<MakeRefExpressionSyntax_Expression>\n");
    incDepth();
}

public override void visitEndMakeRefExpressionSyntax_Expression(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</MakeRefExpressionSyntax_Expression>\n");
}

public override void visitMemberAccessExpressionSyntax_Expression(uint begin, uint end) {
    createIndentation();
    writer.Write("<MemberAccessExpressionSyntax_Expression>\n");
    incDepth();
}

public override void visitEndMemberAccessExpressionSyntax_Expression(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</MemberAccessExpressionSyntax_Expression>\n");
}

public override void visitMemberAccessExpressionSyntax_Name(uint begin, uint end) {
    createIndentation();
    writer.Write("<MemberAccessExpressionSyntax_Name>\n");
    incDepth();
}

public override void visitEndMemberAccessExpressionSyntax_Name(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</MemberAccessExpressionSyntax_Name>\n");
}

public override void visitMemberBindingExpressionSyntax_Name(uint begin, uint end) {
    createIndentation();
    writer.Write("<MemberBindingExpressionSyntax_Name>\n");
    incDepth();
}

public override void visitEndMemberBindingExpressionSyntax_Name(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</MemberBindingExpressionSyntax_Name>\n");
}

public override void visitNullableTypeSyntax_ElementType(uint begin, uint end) {
    createIndentation();
    writer.Write("<NullableTypeSyntax_ElementType>\n");
    incDepth();
}

public override void visitEndNullableTypeSyntax_ElementType(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</NullableTypeSyntax_ElementType>\n");
}

public override void visitObjectCreationExpressionSyntax_ArgumentList(uint begin, uint end) {
    createIndentation();
    writer.Write("<ObjectCreationExpressionSyntax_ArgumentList>\n");
    incDepth();
}

public override void visitEndObjectCreationExpressionSyntax_ArgumentList(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ObjectCreationExpressionSyntax_ArgumentList>\n");
}

public override void visitObjectCreationExpressionSyntax_ConstructorCall(uint begin, uint end) {
    createIndentation();
    writer.Write("<ObjectCreationExpressionSyntax_ConstructorCall ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndObjectCreationExpressionSyntax_ConstructorCall(uint begin, uint end) {
}

public override void visitObjectCreationExpressionSyntax_Initializer(uint begin, uint end) {
    createIndentation();
    writer.Write("<ObjectCreationExpressionSyntax_Initializer>\n");
    incDepth();
}

public override void visitEndObjectCreationExpressionSyntax_Initializer(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ObjectCreationExpressionSyntax_Initializer>\n");
}

public override void visitObjectCreationExpressionSyntax_Type(uint begin, uint end) {
    createIndentation();
    writer.Write("<ObjectCreationExpressionSyntax_Type>\n");
    incDepth();
}

public override void visitEndObjectCreationExpressionSyntax_Type(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ObjectCreationExpressionSyntax_Type>\n");
}

public override void visitParenthesizedExpressionSyntax_Expression(uint begin, uint end) {
    createIndentation();
    writer.Write("<ParenthesizedExpressionSyntax_Expression>\n");
    incDepth();
}

public override void visitEndParenthesizedExpressionSyntax_Expression(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ParenthesizedExpressionSyntax_Expression>\n");
}

public override void visitParenthesizedLambdaExpressionSyntax_ParameterList(uint begin, uint end) {
    createIndentation();
    writer.Write("<ParenthesizedLambdaExpressionSyntax_ParameterList>\n");
    incDepth();
}

public override void visitEndParenthesizedLambdaExpressionSyntax_ParameterList(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ParenthesizedLambdaExpressionSyntax_ParameterList>\n");
}

public override void visitPointerTypeSyntax_ElementType(uint begin, uint end) {
    createIndentation();
    writer.Write("<PointerTypeSyntax_ElementType>\n");
    incDepth();
}

public override void visitEndPointerTypeSyntax_ElementType(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</PointerTypeSyntax_ElementType>\n");
}

public override void visitPostfixUnaryExpressionSyntax_Operand(uint begin, uint end) {
    createIndentation();
    writer.Write("<PostfixUnaryExpressionSyntax_Operand>\n");
    incDepth();
}

public override void visitEndPostfixUnaryExpressionSyntax_Operand(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</PostfixUnaryExpressionSyntax_Operand>\n");
}

public override void visitPostfixUnaryExpressionSyntax_OverloadedOperatorCall(uint begin, uint end) {
    createIndentation();
    writer.Write("<PostfixUnaryExpressionSyntax_OverloadedOperatorCall ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndPostfixUnaryExpressionSyntax_OverloadedOperatorCall(uint begin, uint end) {
}

public override void visitPrefixUnaryExpressionSyntax_Operand(uint begin, uint end) {
    createIndentation();
    writer.Write("<PrefixUnaryExpressionSyntax_Operand>\n");
    incDepth();
}

public override void visitEndPrefixUnaryExpressionSyntax_Operand(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</PrefixUnaryExpressionSyntax_Operand>\n");
}

public override void visitPrefixUnaryExpressionSyntax_OverloadedOperatorCall(uint begin, uint end) {
    createIndentation();
    writer.Write("<PrefixUnaryExpressionSyntax_OverloadedOperatorCall ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndPrefixUnaryExpressionSyntax_OverloadedOperatorCall(uint begin, uint end) {
}

public override void visitQualifiedNameSyntax_Left(uint begin, uint end) {
    createIndentation();
    writer.Write("<QualifiedNameSyntax_Left>\n");
    incDepth();
}

public override void visitEndQualifiedNameSyntax_Left(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</QualifiedNameSyntax_Left>\n");
}

public override void visitQualifiedNameSyntax_Right(uint begin, uint end) {
    createIndentation();
    writer.Write("<QualifiedNameSyntax_Right>\n");
    incDepth();
}

public override void visitEndQualifiedNameSyntax_Right(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</QualifiedNameSyntax_Right>\n");
}

public override void visitQueryExpressionSyntax_Body(uint begin, uint end) {
    createIndentation();
    writer.Write("<QueryExpressionSyntax_Body>\n");
    incDepth();
}

public override void visitEndQueryExpressionSyntax_Body(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</QueryExpressionSyntax_Body>\n");
}

public override void visitQueryExpressionSyntax_FromClause(uint begin, uint end) {
    createIndentation();
    writer.Write("<QueryExpressionSyntax_FromClause>\n");
    incDepth();
}

public override void visitEndQueryExpressionSyntax_FromClause(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</QueryExpressionSyntax_FromClause>\n");
}

public override void visitRefTypeExpressionSyntax_Expression(uint begin, uint end) {
    createIndentation();
    writer.Write("<RefTypeExpressionSyntax_Expression>\n");
    incDepth();
}

public override void visitEndRefTypeExpressionSyntax_Expression(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</RefTypeExpressionSyntax_Expression>\n");
}

public override void visitRefValueExpressionSyntax_Expression(uint begin, uint end) {
    createIndentation();
    writer.Write("<RefValueExpressionSyntax_Expression>\n");
    incDepth();
}

public override void visitEndRefValueExpressionSyntax_Expression(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</RefValueExpressionSyntax_Expression>\n");
}

public override void visitRefValueExpressionSyntax_Type(uint begin, uint end) {
    createIndentation();
    writer.Write("<RefValueExpressionSyntax_Type>\n");
    incDepth();
}

public override void visitEndRefValueExpressionSyntax_Type(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</RefValueExpressionSyntax_Type>\n");
}

public override void visitSimpleLambdaExpressionSyntax_Parameter(uint begin, uint end) {
    createIndentation();
    writer.Write("<SimpleLambdaExpressionSyntax_Parameter>\n");
    incDepth();
}

public override void visitEndSimpleLambdaExpressionSyntax_Parameter(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</SimpleLambdaExpressionSyntax_Parameter>\n");
}

public override void visitSizeOfExpressionSyntax_Type(uint begin, uint end) {
    createIndentation();
    writer.Write("<SizeOfExpressionSyntax_Type>\n");
    incDepth();
}

public override void visitEndSizeOfExpressionSyntax_Type(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</SizeOfExpressionSyntax_Type>\n");
}

public override void visitStackAllocArrayCreationExpressionSyntax_Type(uint begin, uint end) {
    createIndentation();
    writer.Write("<StackAllocArrayCreationExpressionSyntax_Type>\n");
    incDepth();
}

public override void visitEndStackAllocArrayCreationExpressionSyntax_Type(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</StackAllocArrayCreationExpressionSyntax_Type>\n");
}

public override void visitTypeOfExpressionSyntax_Type(uint begin, uint end) {
    createIndentation();
    writer.Write("<TypeOfExpressionSyntax_Type>\n");
    incDepth();
}

public override void visitEndTypeOfExpressionSyntax_Type(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</TypeOfExpressionSyntax_Type>\n");
}

public override void visitTypeSyntax_OriginalDefinition(uint begin, uint end) {
    createIndentation();
    writer.Write("<TypeSyntax_OriginalDefinition ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndTypeSyntax_OriginalDefinition(uint begin, uint end) {
}

public override void visitBlockSyntax_Statements(uint begin, uint end) {
    createIndentation();
    writer.Write("<BlockSyntax_Statements>\n");
    incDepth();
}

public override void visitEndBlockSyntax_Statements(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</BlockSyntax_Statements>\n");
}

public override void visitCheckedStatementSyntax_Block(uint begin, uint end) {
    createIndentation();
    writer.Write("<CheckedStatementSyntax_Block>\n");
    incDepth();
}

public override void visitEndCheckedStatementSyntax_Block(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</CheckedStatementSyntax_Block>\n");
}

public override void visitDoStatementSyntax_Condition(uint begin, uint end) {
    createIndentation();
    writer.Write("<DoStatementSyntax_Condition>\n");
    incDepth();
}

public override void visitEndDoStatementSyntax_Condition(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</DoStatementSyntax_Condition>\n");
}

public override void visitDoStatementSyntax_Statement(uint begin, uint end) {
    createIndentation();
    writer.Write("<DoStatementSyntax_Statement>\n");
    incDepth();
}

public override void visitEndDoStatementSyntax_Statement(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</DoStatementSyntax_Statement>\n");
}

public override void visitExpressionStatementSyntax_Expression(uint begin, uint end) {
    createIndentation();
    writer.Write("<ExpressionStatementSyntax_Expression>\n");
    incDepth();
}

public override void visitEndExpressionStatementSyntax_Expression(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ExpressionStatementSyntax_Expression>\n");
}

public override void visitFixedStatementSyntax_Declaration(uint begin, uint end) {
    createIndentation();
    writer.Write("<FixedStatementSyntax_Declaration>\n");
    incDepth();
}

public override void visitEndFixedStatementSyntax_Declaration(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</FixedStatementSyntax_Declaration>\n");
}

public override void visitFixedStatementSyntax_Statement(uint begin, uint end) {
    createIndentation();
    writer.Write("<FixedStatementSyntax_Statement>\n");
    incDepth();
}

public override void visitEndFixedStatementSyntax_Statement(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</FixedStatementSyntax_Statement>\n");
}

public override void visitForEachStatementSyntax_Expression(uint begin, uint end) {
    createIndentation();
    writer.Write("<ForEachStatementSyntax_Expression>\n");
    incDepth();
}

public override void visitEndForEachStatementSyntax_Expression(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ForEachStatementSyntax_Expression>\n");
}

public override void visitForEachStatementSyntax_Statement(uint begin, uint end) {
    createIndentation();
    writer.Write("<ForEachStatementSyntax_Statement>\n");
    incDepth();
}

public override void visitEndForEachStatementSyntax_Statement(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ForEachStatementSyntax_Statement>\n");
}

public override void visitForEachStatementSyntax_Type(uint begin, uint end) {
    createIndentation();
    writer.Write("<ForEachStatementSyntax_Type>\n");
    incDepth();
}

public override void visitEndForEachStatementSyntax_Type(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ForEachStatementSyntax_Type>\n");
}

public override void visitForStatementSyntax_Condition(uint begin, uint end) {
    createIndentation();
    writer.Write("<ForStatementSyntax_Condition>\n");
    incDepth();
}

public override void visitEndForStatementSyntax_Condition(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ForStatementSyntax_Condition>\n");
}

public override void visitForStatementSyntax_Declaration(uint begin, uint end) {
    createIndentation();
    writer.Write("<ForStatementSyntax_Declaration>\n");
    incDepth();
}

public override void visitEndForStatementSyntax_Declaration(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ForStatementSyntax_Declaration>\n");
}

public override void visitForStatementSyntax_Incrementors(uint begin, uint end) {
    createIndentation();
    writer.Write("<ForStatementSyntax_Incrementors>\n");
    incDepth();
}

public override void visitEndForStatementSyntax_Incrementors(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ForStatementSyntax_Incrementors>\n");
}

public override void visitForStatementSyntax_Initializers(uint begin, uint end) {
    createIndentation();
    writer.Write("<ForStatementSyntax_Initializers>\n");
    incDepth();
}

public override void visitEndForStatementSyntax_Initializers(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ForStatementSyntax_Initializers>\n");
}

public override void visitForStatementSyntax_Statement(uint begin, uint end) {
    createIndentation();
    writer.Write("<ForStatementSyntax_Statement>\n");
    incDepth();
}

public override void visitEndForStatementSyntax_Statement(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ForStatementSyntax_Statement>\n");
}

public override void visitGotoStatementSyntax_Expression(uint begin, uint end) {
    createIndentation();
    writer.Write("<GotoStatementSyntax_Expression>\n");
    incDepth();
}

public override void visitEndGotoStatementSyntax_Expression(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</GotoStatementSyntax_Expression>\n");
}

public override void visitIfStatementSyntax_Condition(uint begin, uint end) {
    createIndentation();
    writer.Write("<IfStatementSyntax_Condition>\n");
    incDepth();
}

public override void visitEndIfStatementSyntax_Condition(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</IfStatementSyntax_Condition>\n");
}

public override void visitIfStatementSyntax_Else(uint begin, uint end) {
    createIndentation();
    writer.Write("<IfStatementSyntax_Else>\n");
    incDepth();
}

public override void visitEndIfStatementSyntax_Else(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</IfStatementSyntax_Else>\n");
}

public override void visitIfStatementSyntax_Statement(uint begin, uint end) {
    createIndentation();
    writer.Write("<IfStatementSyntax_Statement>\n");
    incDepth();
}

public override void visitEndIfStatementSyntax_Statement(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</IfStatementSyntax_Statement>\n");
}

public override void visitLabeledStatementSyntax_Statement(uint begin, uint end) {
    createIndentation();
    writer.Write("<LabeledStatementSyntax_Statement>\n");
    incDepth();
}

public override void visitEndLabeledStatementSyntax_Statement(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</LabeledStatementSyntax_Statement>\n");
}

public override void visitLocalDeclarationStatementSyntax_Declaration(uint begin, uint end) {
    createIndentation();
    writer.Write("<LocalDeclarationStatementSyntax_Declaration>\n");
    incDepth();
}

public override void visitEndLocalDeclarationStatementSyntax_Declaration(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</LocalDeclarationStatementSyntax_Declaration>\n");
}

public override void visitLockStatementSyntax_Expression(uint begin, uint end) {
    createIndentation();
    writer.Write("<LockStatementSyntax_Expression>\n");
    incDepth();
}

public override void visitEndLockStatementSyntax_Expression(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</LockStatementSyntax_Expression>\n");
}

public override void visitLockStatementSyntax_Statement(uint begin, uint end) {
    createIndentation();
    writer.Write("<LockStatementSyntax_Statement>\n");
    incDepth();
}

public override void visitEndLockStatementSyntax_Statement(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</LockStatementSyntax_Statement>\n");
}

public override void visitReturnStatementSyntax_Expression(uint begin, uint end) {
    createIndentation();
    writer.Write("<ReturnStatementSyntax_Expression>\n");
    incDepth();
}

public override void visitEndReturnStatementSyntax_Expression(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ReturnStatementSyntax_Expression>\n");
}

public override void visitSwitchStatementSyntax_Expression(uint begin, uint end) {
    createIndentation();
    writer.Write("<SwitchStatementSyntax_Expression>\n");
    incDepth();
}

public override void visitEndSwitchStatementSyntax_Expression(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</SwitchStatementSyntax_Expression>\n");
}

public override void visitSwitchStatementSyntax_Sections(uint begin, uint end) {
    createIndentation();
    writer.Write("<SwitchStatementSyntax_Sections>\n");
    incDepth();
}

public override void visitEndSwitchStatementSyntax_Sections(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</SwitchStatementSyntax_Sections>\n");
}

public override void visitThrowStatementSyntax_Expression(uint begin, uint end) {
    createIndentation();
    writer.Write("<ThrowStatementSyntax_Expression>\n");
    incDepth();
}

public override void visitEndThrowStatementSyntax_Expression(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ThrowStatementSyntax_Expression>\n");
}

public override void visitTryStatementSyntax_Block(uint begin, uint end) {
    createIndentation();
    writer.Write("<TryStatementSyntax_Block>\n");
    incDepth();
}

public override void visitEndTryStatementSyntax_Block(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</TryStatementSyntax_Block>\n");
}

public override void visitTryStatementSyntax_Catches(uint begin, uint end) {
    createIndentation();
    writer.Write("<TryStatementSyntax_Catches>\n");
    incDepth();
}

public override void visitEndTryStatementSyntax_Catches(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</TryStatementSyntax_Catches>\n");
}

public override void visitTryStatementSyntax_Finally(uint begin, uint end) {
    createIndentation();
    writer.Write("<TryStatementSyntax_Finally>\n");
    incDepth();
}

public override void visitEndTryStatementSyntax_Finally(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</TryStatementSyntax_Finally>\n");
}

public override void visitUnsafeStatementSyntax_Block(uint begin, uint end) {
    createIndentation();
    writer.Write("<UnsafeStatementSyntax_Block>\n");
    incDepth();
}

public override void visitEndUnsafeStatementSyntax_Block(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</UnsafeStatementSyntax_Block>\n");
}

public override void visitUsingStatementSyntax_Declaration(uint begin, uint end) {
    createIndentation();
    writer.Write("<UsingStatementSyntax_Declaration>\n");
    incDepth();
}

public override void visitEndUsingStatementSyntax_Declaration(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</UsingStatementSyntax_Declaration>\n");
}

public override void visitUsingStatementSyntax_Expression(uint begin, uint end) {
    createIndentation();
    writer.Write("<UsingStatementSyntax_Expression>\n");
    incDepth();
}

public override void visitEndUsingStatementSyntax_Expression(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</UsingStatementSyntax_Expression>\n");
}

public override void visitUsingStatementSyntax_Statement(uint begin, uint end) {
    createIndentation();
    writer.Write("<UsingStatementSyntax_Statement>\n");
    incDepth();
}

public override void visitEndUsingStatementSyntax_Statement(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</UsingStatementSyntax_Statement>\n");
}

public override void visitWhileStatementSyntax_Condition(uint begin, uint end) {
    createIndentation();
    writer.Write("<WhileStatementSyntax_Condition>\n");
    incDepth();
}

public override void visitEndWhileStatementSyntax_Condition(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</WhileStatementSyntax_Condition>\n");
}

public override void visitWhileStatementSyntax_Statement(uint begin, uint end) {
    createIndentation();
    writer.Write("<WhileStatementSyntax_Statement>\n");
    incDepth();
}

public override void visitEndWhileStatementSyntax_Statement(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</WhileStatementSyntax_Statement>\n");
}

public override void visitYieldStatementSyntax_Expression(uint begin, uint end) {
    createIndentation();
    writer.Write("<YieldStatementSyntax_Expression>\n");
    incDepth();
}

public override void visitEndYieldStatementSyntax_Expression(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</YieldStatementSyntax_Expression>\n");
}

public override void visitAccessorDeclarationSyntax_AttributeLists(uint begin, uint end) {
    createIndentation();
    writer.Write("<AccessorDeclarationSyntax_AttributeLists>\n");
    incDepth();
}

public override void visitEndAccessorDeclarationSyntax_AttributeLists(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</AccessorDeclarationSyntax_AttributeLists>\n");
}

public override void visitAccessorDeclarationSyntax_Body(uint begin, uint end) {
    createIndentation();
    writer.Write("<AccessorDeclarationSyntax_Body>\n");
    incDepth();
}

public override void visitEndAccessorDeclarationSyntax_Body(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</AccessorDeclarationSyntax_Body>\n");
}

public override void visitAccessorListSyntax_Accessors(uint begin, uint end) {
    createIndentation();
    writer.Write("<AccessorListSyntax_Accessors>\n");
    incDepth();
}

public override void visitEndAccessorListSyntax_Accessors(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</AccessorListSyntax_Accessors>\n");
}

public override void visitAnonymousObjectMemberDeclaratorSyntax_Expression(uint begin, uint end) {
    createIndentation();
    writer.Write("<AnonymousObjectMemberDeclaratorSyntax_Expression>\n");
    incDepth();
}

public override void visitEndAnonymousObjectMemberDeclaratorSyntax_Expression(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</AnonymousObjectMemberDeclaratorSyntax_Expression>\n");
}

public override void visitAnonymousObjectMemberDeclaratorSyntax_NameEquals(uint begin, uint end) {
    createIndentation();
    writer.Write("<AnonymousObjectMemberDeclaratorSyntax_NameEquals>\n");
    incDepth();
}

public override void visitEndAnonymousObjectMemberDeclaratorSyntax_NameEquals(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</AnonymousObjectMemberDeclaratorSyntax_NameEquals>\n");
}

public override void visitArgumentSyntax_Expression(uint begin, uint end) {
    createIndentation();
    writer.Write("<ArgumentSyntax_Expression>\n");
    incDepth();
}

public override void visitEndArgumentSyntax_Expression(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ArgumentSyntax_Expression>\n");
}

public override void visitArgumentSyntax_NameColon(uint begin, uint end) {
    createIndentation();
    writer.Write("<ArgumentSyntax_NameColon>\n");
    incDepth();
}

public override void visitEndArgumentSyntax_NameColon(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ArgumentSyntax_NameColon>\n");
}

public override void visitArrayRankSpecifierSyntax_Sizes(uint begin, uint end) {
    createIndentation();
    writer.Write("<ArrayRankSpecifierSyntax_Sizes>\n");
    incDepth();
}

public override void visitEndArrayRankSpecifierSyntax_Sizes(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ArrayRankSpecifierSyntax_Sizes>\n");
}

public override void visitArrowExpressionClauseSyntax_Expression(uint begin, uint end) {
    createIndentation();
    writer.Write("<ArrowExpressionClauseSyntax_Expression>\n");
    incDepth();
}

public override void visitEndArrowExpressionClauseSyntax_Expression(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ArrowExpressionClauseSyntax_Expression>\n");
}

public override void visitAttributeArgumentListSyntax_Arguments(uint begin, uint end) {
    createIndentation();
    writer.Write("<AttributeArgumentListSyntax_Arguments>\n");
    incDepth();
}

public override void visitEndAttributeArgumentListSyntax_Arguments(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</AttributeArgumentListSyntax_Arguments>\n");
}

public override void visitAttributeArgumentSyntax_Expression(uint begin, uint end) {
    createIndentation();
    writer.Write("<AttributeArgumentSyntax_Expression>\n");
    incDepth();
}

public override void visitEndAttributeArgumentSyntax_Expression(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</AttributeArgumentSyntax_Expression>\n");
}

public override void visitAttributeArgumentSyntax_NameColon(uint begin, uint end) {
    createIndentation();
    writer.Write("<AttributeArgumentSyntax_NameColon>\n");
    incDepth();
}

public override void visitEndAttributeArgumentSyntax_NameColon(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</AttributeArgumentSyntax_NameColon>\n");
}

public override void visitAttributeArgumentSyntax_NameEquals(uint begin, uint end) {
    createIndentation();
    writer.Write("<AttributeArgumentSyntax_NameEquals>\n");
    incDepth();
}

public override void visitEndAttributeArgumentSyntax_NameEquals(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</AttributeArgumentSyntax_NameEquals>\n");
}

public override void visitAttributeListSyntax_Attributes(uint begin, uint end) {
    createIndentation();
    writer.Write("<AttributeListSyntax_Attributes>\n");
    incDepth();
}

public override void visitEndAttributeListSyntax_Attributes(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</AttributeListSyntax_Attributes>\n");
}

public override void visitAttributeListSyntax_Target(uint begin, uint end) {
    createIndentation();
    writer.Write("<AttributeListSyntax_Target>\n");
    incDepth();
}

public override void visitEndAttributeListSyntax_Target(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</AttributeListSyntax_Target>\n");
}

public override void visitAttributeSyntax_ArgumentList(uint begin, uint end) {
    createIndentation();
    writer.Write("<AttributeSyntax_ArgumentList>\n");
    incDepth();
}

public override void visitEndAttributeSyntax_ArgumentList(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</AttributeSyntax_ArgumentList>\n");
}

public override void visitAttributeSyntax_Name(uint begin, uint end) {
    createIndentation();
    writer.Write("<AttributeSyntax_Name>\n");
    incDepth();
}

public override void visitEndAttributeSyntax_Name(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</AttributeSyntax_Name>\n");
}

public override void visitBaseArgumentListSyntax_Arguments(uint begin, uint end) {
    createIndentation();
    writer.Write("<BaseArgumentListSyntax_Arguments>\n");
    incDepth();
}

public override void visitEndBaseArgumentListSyntax_Arguments(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</BaseArgumentListSyntax_Arguments>\n");
}

public override void visitBaseCrefParameterListSyntax_Parameters(uint begin, uint end) {
    createIndentation();
    writer.Write("<BaseCrefParameterListSyntax_Parameters>\n");
    incDepth();
}

public override void visitEndBaseCrefParameterListSyntax_Parameters(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</BaseCrefParameterListSyntax_Parameters>\n");
}

public override void visitBaseFieldDeclarationSyntax_AttributeLists(uint begin, uint end) {
    createIndentation();
    writer.Write("<BaseFieldDeclarationSyntax_AttributeLists>\n");
    incDepth();
}

public override void visitEndBaseFieldDeclarationSyntax_AttributeLists(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</BaseFieldDeclarationSyntax_AttributeLists>\n");
}

public override void visitBaseFieldDeclarationSyntax_Declaration(uint begin, uint end) {
    createIndentation();
    writer.Write("<BaseFieldDeclarationSyntax_Declaration>\n");
    incDepth();
}

public override void visitEndBaseFieldDeclarationSyntax_Declaration(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</BaseFieldDeclarationSyntax_Declaration>\n");
}

public override void visitBaseListSyntax_Types(uint begin, uint end) {
    createIndentation();
    writer.Write("<BaseListSyntax_Types>\n");
    incDepth();
}

public override void visitEndBaseListSyntax_Types(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</BaseListSyntax_Types>\n");
}

public override void visitBaseMethodDeclarationSyntax_AccessedEnumMembers(uint begin, uint end) {
    createIndentation();
    writer.Write("<BaseMethodDeclarationSyntax_AccessedEnumMembers ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndBaseMethodDeclarationSyntax_AccessedEnumMembers(uint begin, uint end) {
}

public override void visitBaseMethodDeclarationSyntax_AttributeLists(uint begin, uint end) {
    createIndentation();
    writer.Write("<BaseMethodDeclarationSyntax_AttributeLists>\n");
    incDepth();
}

public override void visitEndBaseMethodDeclarationSyntax_AttributeLists(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</BaseMethodDeclarationSyntax_AttributeLists>\n");
}

public override void visitBaseMethodDeclarationSyntax_Body(uint begin, uint end) {
    createIndentation();
    writer.Write("<BaseMethodDeclarationSyntax_Body>\n");
    incDepth();
}

public override void visitEndBaseMethodDeclarationSyntax_Body(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</BaseMethodDeclarationSyntax_Body>\n");
}

public override void visitBaseMethodDeclarationSyntax_ParameterList(uint begin, uint end) {
    createIndentation();
    writer.Write("<BaseMethodDeclarationSyntax_ParameterList>\n");
    incDepth();
}

public override void visitEndBaseMethodDeclarationSyntax_ParameterList(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</BaseMethodDeclarationSyntax_ParameterList>\n");
}

public override void visitBaseParameterListSyntax_Parameters(uint begin, uint end) {
    createIndentation();
    writer.Write("<BaseParameterListSyntax_Parameters>\n");
    incDepth();
}

public override void visitEndBaseParameterListSyntax_Parameters(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</BaseParameterListSyntax_Parameters>\n");
}

public override void visitBasePropertyDeclarationSyntax_AccessorList(uint begin, uint end) {
    createIndentation();
    writer.Write("<BasePropertyDeclarationSyntax_AccessorList>\n");
    incDepth();
}

public override void visitEndBasePropertyDeclarationSyntax_AccessorList(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</BasePropertyDeclarationSyntax_AccessorList>\n");
}

public override void visitBasePropertyDeclarationSyntax_AttributeLists(uint begin, uint end) {
    createIndentation();
    writer.Write("<BasePropertyDeclarationSyntax_AttributeLists>\n");
    incDepth();
}

public override void visitEndBasePropertyDeclarationSyntax_AttributeLists(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</BasePropertyDeclarationSyntax_AttributeLists>\n");
}

public override void visitBasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier(uint begin, uint end) {
    createIndentation();
    writer.Write("<BasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier>\n");
    incDepth();
}

public override void visitEndBasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</BasePropertyDeclarationSyntax_ExplicitInterfaceSpecifier>\n");
}

public override void visitBasePropertyDeclarationSyntax_Type(uint begin, uint end) {
    createIndentation();
    writer.Write("<BasePropertyDeclarationSyntax_Type>\n");
    incDepth();
}

public override void visitEndBasePropertyDeclarationSyntax_Type(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</BasePropertyDeclarationSyntax_Type>\n");
}

public override void visitBaseTypeDeclarationSyntax_AttributeLists(uint begin, uint end) {
    createIndentation();
    writer.Write("<BaseTypeDeclarationSyntax_AttributeLists>\n");
    incDepth();
}

public override void visitEndBaseTypeDeclarationSyntax_AttributeLists(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</BaseTypeDeclarationSyntax_AttributeLists>\n");
}

public override void visitBaseTypeDeclarationSyntax_BaseList(uint begin, uint end) {
    createIndentation();
    writer.Write("<BaseTypeDeclarationSyntax_BaseList>\n");
    incDepth();
}

public override void visitEndBaseTypeDeclarationSyntax_BaseList(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</BaseTypeDeclarationSyntax_BaseList>\n");
}

public override void visitBaseTypeSyntax_Type(uint begin, uint end) {
    createIndentation();
    writer.Write("<BaseTypeSyntax_Type>\n");
    incDepth();
}

public override void visitEndBaseTypeSyntax_Type(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</BaseTypeSyntax_Type>\n");
}

public override void visitCaseSwitchLabelSyntax_Value(uint begin, uint end) {
    createIndentation();
    writer.Write("<CaseSwitchLabelSyntax_Value>\n");
    incDepth();
}

public override void visitEndCaseSwitchLabelSyntax_Value(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</CaseSwitchLabelSyntax_Value>\n");
}

public override void visitCatchClauseSyntax_Block(uint begin, uint end) {
    createIndentation();
    writer.Write("<CatchClauseSyntax_Block>\n");
    incDepth();
}

public override void visitEndCatchClauseSyntax_Block(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</CatchClauseSyntax_Block>\n");
}

public override void visitCatchClauseSyntax_Declaration(uint begin, uint end) {
    createIndentation();
    writer.Write("<CatchClauseSyntax_Declaration>\n");
    incDepth();
}

public override void visitEndCatchClauseSyntax_Declaration(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</CatchClauseSyntax_Declaration>\n");
}

public override void visitCatchClauseSyntax_Filter(uint begin, uint end) {
    createIndentation();
    writer.Write("<CatchClauseSyntax_Filter>\n");
    incDepth();
}

public override void visitEndCatchClauseSyntax_Filter(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</CatchClauseSyntax_Filter>\n");
}

public override void visitCatchDeclarationSyntax_Type(uint begin, uint end) {
    createIndentation();
    writer.Write("<CatchDeclarationSyntax_Type>\n");
    incDepth();
}

public override void visitEndCatchDeclarationSyntax_Type(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</CatchDeclarationSyntax_Type>\n");
}

public override void visitCatchFilterClauseSyntax_FilterExpression(uint begin, uint end) {
    createIndentation();
    writer.Write("<CatchFilterClauseSyntax_FilterExpression>\n");
    incDepth();
}

public override void visitEndCatchFilterClauseSyntax_FilterExpression(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</CatchFilterClauseSyntax_FilterExpression>\n");
}

public override void visitCompilationUnitSyntax_AttributeLists(uint begin, uint end) {
    createIndentation();
    writer.Write("<CompilationUnitSyntax_AttributeLists>\n");
    incDepth();
}

public override void visitEndCompilationUnitSyntax_AttributeLists(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</CompilationUnitSyntax_AttributeLists>\n");
}

public override void visitCompilationUnitSyntax_Externs(uint begin, uint end) {
    createIndentation();
    writer.Write("<CompilationUnitSyntax_Externs>\n");
    incDepth();
}

public override void visitEndCompilationUnitSyntax_Externs(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</CompilationUnitSyntax_Externs>\n");
}

public override void visitCompilationUnitSyntax_Members(uint begin, uint end) {
    createIndentation();
    writer.Write("<CompilationUnitSyntax_Members>\n");
    incDepth();
}

public override void visitEndCompilationUnitSyntax_Members(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</CompilationUnitSyntax_Members>\n");
}

public override void visitCompilationUnitSyntax_Usings(uint begin, uint end) {
    createIndentation();
    writer.Write("<CompilationUnitSyntax_Usings>\n");
    incDepth();
}

public override void visitEndCompilationUnitSyntax_Usings(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</CompilationUnitSyntax_Usings>\n");
}

public override void visitConstructorDeclarationSyntax_Initializer(uint begin, uint end) {
    createIndentation();
    writer.Write("<ConstructorDeclarationSyntax_Initializer>\n");
    incDepth();
}

public override void visitEndConstructorDeclarationSyntax_Initializer(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ConstructorDeclarationSyntax_Initializer>\n");
}

public override void visitConstructorInitializerSyntax_ArgumentList(uint begin, uint end) {
    createIndentation();
    writer.Write("<ConstructorInitializerSyntax_ArgumentList>\n");
    incDepth();
}

public override void visitEndConstructorInitializerSyntax_ArgumentList(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ConstructorInitializerSyntax_ArgumentList>\n");
}

public override void visitConstructorInitializerSyntax_ConstructorCall(uint begin, uint end) {
    createIndentation();
    writer.Write("<ConstructorInitializerSyntax_ConstructorCall ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndConstructorInitializerSyntax_ConstructorCall(uint begin, uint end) {
}

public override void visitConversionOperatorDeclarationSyntax_ExpressionBody(uint begin, uint end) {
    createIndentation();
    writer.Write("<ConversionOperatorDeclarationSyntax_ExpressionBody>\n");
    incDepth();
}

public override void visitEndConversionOperatorDeclarationSyntax_ExpressionBody(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ConversionOperatorDeclarationSyntax_ExpressionBody>\n");
}

public override void visitConversionOperatorDeclarationSyntax_Type(uint begin, uint end) {
    createIndentation();
    writer.Write("<ConversionOperatorDeclarationSyntax_Type>\n");
    incDepth();
}

public override void visitEndConversionOperatorDeclarationSyntax_Type(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ConversionOperatorDeclarationSyntax_Type>\n");
}

public override void visitConversionOperatorMemberCrefSyntax_Parameters(uint begin, uint end) {
    createIndentation();
    writer.Write("<ConversionOperatorMemberCrefSyntax_Parameters>\n");
    incDepth();
}

public override void visitEndConversionOperatorMemberCrefSyntax_Parameters(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ConversionOperatorMemberCrefSyntax_Parameters>\n");
}

public override void visitConversionOperatorMemberCrefSyntax_Type(uint begin, uint end) {
    createIndentation();
    writer.Write("<ConversionOperatorMemberCrefSyntax_Type>\n");
    incDepth();
}

public override void visitEndConversionOperatorMemberCrefSyntax_Type(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ConversionOperatorMemberCrefSyntax_Type>\n");
}

public override void visitCrefParameterSyntax_Type(uint begin, uint end) {
    createIndentation();
    writer.Write("<CrefParameterSyntax_Type>\n");
    incDepth();
}

public override void visitEndCrefParameterSyntax_Type(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</CrefParameterSyntax_Type>\n");
}

public override void visitDelegateDeclarationSyntax_AttributeLists(uint begin, uint end) {
    createIndentation();
    writer.Write("<DelegateDeclarationSyntax_AttributeLists>\n");
    incDepth();
}

public override void visitEndDelegateDeclarationSyntax_AttributeLists(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</DelegateDeclarationSyntax_AttributeLists>\n");
}

public override void visitDelegateDeclarationSyntax_ConstraintClauses(uint begin, uint end) {
    createIndentation();
    writer.Write("<DelegateDeclarationSyntax_ConstraintClauses>\n");
    incDepth();
}

public override void visitEndDelegateDeclarationSyntax_ConstraintClauses(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</DelegateDeclarationSyntax_ConstraintClauses>\n");
}

public override void visitDelegateDeclarationSyntax_ParameterList(uint begin, uint end) {
    createIndentation();
    writer.Write("<DelegateDeclarationSyntax_ParameterList>\n");
    incDepth();
}

public override void visitEndDelegateDeclarationSyntax_ParameterList(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</DelegateDeclarationSyntax_ParameterList>\n");
}

public override void visitDelegateDeclarationSyntax_ReturnType(uint begin, uint end) {
    createIndentation();
    writer.Write("<DelegateDeclarationSyntax_ReturnType>\n");
    incDepth();
}

public override void visitEndDelegateDeclarationSyntax_ReturnType(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</DelegateDeclarationSyntax_ReturnType>\n");
}

public override void visitElseClauseSyntax_Statement(uint begin, uint end) {
    createIndentation();
    writer.Write("<ElseClauseSyntax_Statement>\n");
    incDepth();
}

public override void visitEndElseClauseSyntax_Statement(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ElseClauseSyntax_Statement>\n");
}

public override void visitEnumDeclarationSyntax_Members(uint begin, uint end) {
    createIndentation();
    writer.Write("<EnumDeclarationSyntax_Members>\n");
    incDepth();
}

public override void visitEndEnumDeclarationSyntax_Members(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</EnumDeclarationSyntax_Members>\n");
}

public override void visitEnumMemberDeclarationSyntax_AttributeLists(uint begin, uint end) {
    createIndentation();
    writer.Write("<EnumMemberDeclarationSyntax_AttributeLists>\n");
    incDepth();
}

public override void visitEndEnumMemberDeclarationSyntax_AttributeLists(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</EnumMemberDeclarationSyntax_AttributeLists>\n");
}

public override void visitEnumMemberDeclarationSyntax_EqualsValue(uint begin, uint end) {
    createIndentation();
    writer.Write("<EnumMemberDeclarationSyntax_EqualsValue>\n");
    incDepth();
}

public override void visitEndEnumMemberDeclarationSyntax_EqualsValue(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</EnumMemberDeclarationSyntax_EqualsValue>\n");
}

public override void visitEqualsValueClauseSyntax_Value(uint begin, uint end) {
    createIndentation();
    writer.Write("<EqualsValueClauseSyntax_Value>\n");
    incDepth();
}

public override void visitEndEqualsValueClauseSyntax_Value(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</EqualsValueClauseSyntax_Value>\n");
}

public override void visitExplicitInterfaceSpecifierSyntax_Name(uint begin, uint end) {
    createIndentation();
    writer.Write("<ExplicitInterfaceSpecifierSyntax_Name>\n");
    incDepth();
}

public override void visitEndExplicitInterfaceSpecifierSyntax_Name(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ExplicitInterfaceSpecifierSyntax_Name>\n");
}

public override void visitFinallyClauseSyntax_Block(uint begin, uint end) {
    createIndentation();
    writer.Write("<FinallyClauseSyntax_Block>\n");
    incDepth();
}

public override void visitEndFinallyClauseSyntax_Block(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</FinallyClauseSyntax_Block>\n");
}

public override void visitFromClauseSyntax_Expression(uint begin, uint end) {
    createIndentation();
    writer.Write("<FromClauseSyntax_Expression>\n");
    incDepth();
}

public override void visitEndFromClauseSyntax_Expression(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</FromClauseSyntax_Expression>\n");
}

public override void visitFromClauseSyntax_Type(uint begin, uint end) {
    createIndentation();
    writer.Write("<FromClauseSyntax_Type>\n");
    incDepth();
}

public override void visitEndFromClauseSyntax_Type(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</FromClauseSyntax_Type>\n");
}

public override void visitGlobalStatementSyntax_Statement(uint begin, uint end) {
    createIndentation();
    writer.Write("<GlobalStatementSyntax_Statement>\n");
    incDepth();
}

public override void visitEndGlobalStatementSyntax_Statement(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</GlobalStatementSyntax_Statement>\n");
}

public override void visitGroupClauseSyntax_ByExpression(uint begin, uint end) {
    createIndentation();
    writer.Write("<GroupClauseSyntax_ByExpression>\n");
    incDepth();
}

public override void visitEndGroupClauseSyntax_ByExpression(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</GroupClauseSyntax_ByExpression>\n");
}

public override void visitGroupClauseSyntax_GroupExpression(uint begin, uint end) {
    createIndentation();
    writer.Write("<GroupClauseSyntax_GroupExpression>\n");
    incDepth();
}

public override void visitEndGroupClauseSyntax_GroupExpression(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</GroupClauseSyntax_GroupExpression>\n");
}

public override void visitIncompleteMemberSyntax_AttributeLists(uint begin, uint end) {
    createIndentation();
    writer.Write("<IncompleteMemberSyntax_AttributeLists>\n");
    incDepth();
}

public override void visitEndIncompleteMemberSyntax_AttributeLists(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</IncompleteMemberSyntax_AttributeLists>\n");
}

public override void visitIncompleteMemberSyntax_Type(uint begin, uint end) {
    createIndentation();
    writer.Write("<IncompleteMemberSyntax_Type>\n");
    incDepth();
}

public override void visitEndIncompleteMemberSyntax_Type(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</IncompleteMemberSyntax_Type>\n");
}

public override void visitIndexerDeclarationSyntax_ExpressionBody(uint begin, uint end) {
    createIndentation();
    writer.Write("<IndexerDeclarationSyntax_ExpressionBody>\n");
    incDepth();
}

public override void visitEndIndexerDeclarationSyntax_ExpressionBody(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</IndexerDeclarationSyntax_ExpressionBody>\n");
}

public override void visitIndexerDeclarationSyntax_ParameterList(uint begin, uint end) {
    createIndentation();
    writer.Write("<IndexerDeclarationSyntax_ParameterList>\n");
    incDepth();
}

public override void visitEndIndexerDeclarationSyntax_ParameterList(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</IndexerDeclarationSyntax_ParameterList>\n");
}

public override void visitIndexerMemberCrefSyntax_Parameters(uint begin, uint end) {
    createIndentation();
    writer.Write("<IndexerMemberCrefSyntax_Parameters>\n");
    incDepth();
}

public override void visitEndIndexerMemberCrefSyntax_Parameters(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</IndexerMemberCrefSyntax_Parameters>\n");
}

public override void visitInterpolationAlignmentClauseSyntax_Value(uint begin, uint end) {
    createIndentation();
    writer.Write("<InterpolationAlignmentClauseSyntax_Value>\n");
    incDepth();
}

public override void visitEndInterpolationAlignmentClauseSyntax_Value(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</InterpolationAlignmentClauseSyntax_Value>\n");
}

public override void visitInterpolationSyntax_AlignmentClause(uint begin, uint end) {
    createIndentation();
    writer.Write("<InterpolationSyntax_AlignmentClause>\n");
    incDepth();
}

public override void visitEndInterpolationSyntax_AlignmentClause(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</InterpolationSyntax_AlignmentClause>\n");
}

public override void visitInterpolationSyntax_Expression(uint begin, uint end) {
    createIndentation();
    writer.Write("<InterpolationSyntax_Expression>\n");
    incDepth();
}

public override void visitEndInterpolationSyntax_Expression(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</InterpolationSyntax_Expression>\n");
}

public override void visitInterpolationSyntax_FormatClause(uint begin, uint end) {
    createIndentation();
    writer.Write("<InterpolationSyntax_FormatClause>\n");
    incDepth();
}

public override void visitEndInterpolationSyntax_FormatClause(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</InterpolationSyntax_FormatClause>\n");
}

public override void visitJoinClauseSyntax_InExpression(uint begin, uint end) {
    createIndentation();
    writer.Write("<JoinClauseSyntax_InExpression>\n");
    incDepth();
}

public override void visitEndJoinClauseSyntax_InExpression(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</JoinClauseSyntax_InExpression>\n");
}

public override void visitJoinClauseSyntax_Into(uint begin, uint end) {
    createIndentation();
    writer.Write("<JoinClauseSyntax_Into>\n");
    incDepth();
}

public override void visitEndJoinClauseSyntax_Into(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</JoinClauseSyntax_Into>\n");
}

public override void visitJoinClauseSyntax_LeftExpression(uint begin, uint end) {
    createIndentation();
    writer.Write("<JoinClauseSyntax_LeftExpression>\n");
    incDepth();
}

public override void visitEndJoinClauseSyntax_LeftExpression(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</JoinClauseSyntax_LeftExpression>\n");
}

public override void visitJoinClauseSyntax_RightExpression(uint begin, uint end) {
    createIndentation();
    writer.Write("<JoinClauseSyntax_RightExpression>\n");
    incDepth();
}

public override void visitEndJoinClauseSyntax_RightExpression(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</JoinClauseSyntax_RightExpression>\n");
}

public override void visitJoinClauseSyntax_Type(uint begin, uint end) {
    createIndentation();
    writer.Write("<JoinClauseSyntax_Type>\n");
    incDepth();
}

public override void visitEndJoinClauseSyntax_Type(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</JoinClauseSyntax_Type>\n");
}

public override void visitLetClauseSyntax_Expression(uint begin, uint end) {
    createIndentation();
    writer.Write("<LetClauseSyntax_Expression>\n");
    incDepth();
}

public override void visitEndLetClauseSyntax_Expression(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</LetClauseSyntax_Expression>\n");
}

public override void visitMethodDeclarationSyntax_ConstraintClauses(uint begin, uint end) {
    createIndentation();
    writer.Write("<MethodDeclarationSyntax_ConstraintClauses>\n");
    incDepth();
}

public override void visitEndMethodDeclarationSyntax_ConstraintClauses(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</MethodDeclarationSyntax_ConstraintClauses>\n");
}

public override void visitMethodDeclarationSyntax_ExplicitInterfaceSpecifier(uint begin, uint end) {
    createIndentation();
    writer.Write("<MethodDeclarationSyntax_ExplicitInterfaceSpecifier>\n");
    incDepth();
}

public override void visitEndMethodDeclarationSyntax_ExplicitInterfaceSpecifier(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</MethodDeclarationSyntax_ExplicitInterfaceSpecifier>\n");
}

public override void visitMethodDeclarationSyntax_ExpressionBody(uint begin, uint end) {
    createIndentation();
    writer.Write("<MethodDeclarationSyntax_ExpressionBody>\n");
    incDepth();
}

public override void visitEndMethodDeclarationSyntax_ExpressionBody(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</MethodDeclarationSyntax_ExpressionBody>\n");
}

public override void visitMethodDeclarationSyntax_ReturnType(uint begin, uint end) {
    createIndentation();
    writer.Write("<MethodDeclarationSyntax_ReturnType>\n");
    incDepth();
}

public override void visitEndMethodDeclarationSyntax_ReturnType(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</MethodDeclarationSyntax_ReturnType>\n");
}

public override void visitNameColonSyntax_Name(uint begin, uint end) {
    createIndentation();
    writer.Write("<NameColonSyntax_Name>\n");
    incDepth();
}

public override void visitEndNameColonSyntax_Name(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</NameColonSyntax_Name>\n");
}

public override void visitNameEqualsSyntax_Name(uint begin, uint end) {
    createIndentation();
    writer.Write("<NameEqualsSyntax_Name>\n");
    incDepth();
}

public override void visitEndNameEqualsSyntax_Name(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</NameEqualsSyntax_Name>\n");
}

public override void visitNameMemberCrefSyntax_Name(uint begin, uint end) {
    createIndentation();
    writer.Write("<NameMemberCrefSyntax_Name>\n");
    incDepth();
}

public override void visitEndNameMemberCrefSyntax_Name(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</NameMemberCrefSyntax_Name>\n");
}

public override void visitNameMemberCrefSyntax_Parameters(uint begin, uint end) {
    createIndentation();
    writer.Write("<NameMemberCrefSyntax_Parameters>\n");
    incDepth();
}

public override void visitEndNameMemberCrefSyntax_Parameters(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</NameMemberCrefSyntax_Parameters>\n");
}

public override void visitNamespaceDeclarationSyntax_Externs(uint begin, uint end) {
    createIndentation();
    writer.Write("<NamespaceDeclarationSyntax_Externs>\n");
    incDepth();
}

public override void visitEndNamespaceDeclarationSyntax_Externs(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</NamespaceDeclarationSyntax_Externs>\n");
}

public override void visitNamespaceDeclarationSyntax_Members(uint begin, uint end) {
    createIndentation();
    writer.Write("<NamespaceDeclarationSyntax_Members>\n");
    incDepth();
}

public override void visitEndNamespaceDeclarationSyntax_Members(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</NamespaceDeclarationSyntax_Members>\n");
}

public override void visitNamespaceDeclarationSyntax_Name(uint begin, uint end) {
    createIndentation();
    writer.Write("<NamespaceDeclarationSyntax_Name>\n");
    incDepth();
}

public override void visitEndNamespaceDeclarationSyntax_Name(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</NamespaceDeclarationSyntax_Name>\n");
}

public override void visitNamespaceDeclarationSyntax_Usings(uint begin, uint end) {
    createIndentation();
    writer.Write("<NamespaceDeclarationSyntax_Usings>\n");
    incDepth();
}

public override void visitEndNamespaceDeclarationSyntax_Usings(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</NamespaceDeclarationSyntax_Usings>\n");
}

public override void visitOperatorDeclarationSyntax_ExpressionBody(uint begin, uint end) {
    createIndentation();
    writer.Write("<OperatorDeclarationSyntax_ExpressionBody>\n");
    incDepth();
}

public override void visitEndOperatorDeclarationSyntax_ExpressionBody(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</OperatorDeclarationSyntax_ExpressionBody>\n");
}

public override void visitOperatorDeclarationSyntax_ReturnType(uint begin, uint end) {
    createIndentation();
    writer.Write("<OperatorDeclarationSyntax_ReturnType>\n");
    incDepth();
}

public override void visitEndOperatorDeclarationSyntax_ReturnType(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</OperatorDeclarationSyntax_ReturnType>\n");
}

public override void visitOperatorMemberCrefSyntax_Parameters(uint begin, uint end) {
    createIndentation();
    writer.Write("<OperatorMemberCrefSyntax_Parameters>\n");
    incDepth();
}

public override void visitEndOperatorMemberCrefSyntax_Parameters(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</OperatorMemberCrefSyntax_Parameters>\n");
}

public override void visitOrderByClauseSyntax_Orderings(uint begin, uint end) {
    createIndentation();
    writer.Write("<OrderByClauseSyntax_Orderings>\n");
    incDepth();
}

public override void visitEndOrderByClauseSyntax_Orderings(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</OrderByClauseSyntax_Orderings>\n");
}

public override void visitOrderingSyntax_Expression(uint begin, uint end) {
    createIndentation();
    writer.Write("<OrderingSyntax_Expression>\n");
    incDepth();
}

public override void visitEndOrderingSyntax_Expression(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</OrderingSyntax_Expression>\n");
}

public override void visitParameterSyntax_AttributeLists(uint begin, uint end) {
    createIndentation();
    writer.Write("<ParameterSyntax_AttributeLists>\n");
    incDepth();
}

public override void visitEndParameterSyntax_AttributeLists(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ParameterSyntax_AttributeLists>\n");
}

public override void visitParameterSyntax_Default(uint begin, uint end) {
    createIndentation();
    writer.Write("<ParameterSyntax_Default>\n");
    incDepth();
}

public override void visitEndParameterSyntax_Default(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ParameterSyntax_Default>\n");
}

public override void visitParameterSyntax_Type(uint begin, uint end) {
    createIndentation();
    writer.Write("<ParameterSyntax_Type>\n");
    incDepth();
}

public override void visitEndParameterSyntax_Type(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ParameterSyntax_Type>\n");
}

public override void visitPropertyDeclarationSyntax_ExpressionBody(uint begin, uint end) {
    createIndentation();
    writer.Write("<PropertyDeclarationSyntax_ExpressionBody>\n");
    incDepth();
}

public override void visitEndPropertyDeclarationSyntax_ExpressionBody(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</PropertyDeclarationSyntax_ExpressionBody>\n");
}

public override void visitPropertyDeclarationSyntax_Initializer(uint begin, uint end) {
    createIndentation();
    writer.Write("<PropertyDeclarationSyntax_Initializer>\n");
    incDepth();
}

public override void visitEndPropertyDeclarationSyntax_Initializer(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</PropertyDeclarationSyntax_Initializer>\n");
}

public override void visitQualifiedCrefSyntax_Container(uint begin, uint end) {
    createIndentation();
    writer.Write("<QualifiedCrefSyntax_Container>\n");
    incDepth();
}

public override void visitEndQualifiedCrefSyntax_Container(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</QualifiedCrefSyntax_Container>\n");
}

public override void visitQualifiedCrefSyntax_Member(uint begin, uint end) {
    createIndentation();
    writer.Write("<QualifiedCrefSyntax_Member>\n");
    incDepth();
}

public override void visitEndQualifiedCrefSyntax_Member(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</QualifiedCrefSyntax_Member>\n");
}

public override void visitQueryBodySyntax_Clauses(uint begin, uint end) {
    createIndentation();
    writer.Write("<QueryBodySyntax_Clauses>\n");
    incDepth();
}

public override void visitEndQueryBodySyntax_Clauses(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</QueryBodySyntax_Clauses>\n");
}

public override void visitQueryBodySyntax_Continuation(uint begin, uint end) {
    createIndentation();
    writer.Write("<QueryBodySyntax_Continuation>\n");
    incDepth();
}

public override void visitEndQueryBodySyntax_Continuation(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</QueryBodySyntax_Continuation>\n");
}

public override void visitQueryBodySyntax_SelectOrGroup(uint begin, uint end) {
    createIndentation();
    writer.Write("<QueryBodySyntax_SelectOrGroup>\n");
    incDepth();
}

public override void visitEndQueryBodySyntax_SelectOrGroup(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</QueryBodySyntax_SelectOrGroup>\n");
}

public override void visitQueryContinuationSyntax_Body(uint begin, uint end) {
    createIndentation();
    writer.Write("<QueryContinuationSyntax_Body>\n");
    incDepth();
}

public override void visitEndQueryContinuationSyntax_Body(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</QueryContinuationSyntax_Body>\n");
}

public override void visitSelectClauseSyntax_Expression(uint begin, uint end) {
    createIndentation();
    writer.Write("<SelectClauseSyntax_Expression>\n");
    incDepth();
}

public override void visitEndSelectClauseSyntax_Expression(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</SelectClauseSyntax_Expression>\n");
}

public override void visitSwitchSectionSyntax_Labels(uint begin, uint end) {
    createIndentation();
    writer.Write("<SwitchSectionSyntax_Labels>\n");
    incDepth();
}

public override void visitEndSwitchSectionSyntax_Labels(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</SwitchSectionSyntax_Labels>\n");
}

public override void visitSwitchSectionSyntax_Statements(uint begin, uint end) {
    createIndentation();
    writer.Write("<SwitchSectionSyntax_Statements>\n");
    incDepth();
}

public override void visitEndSwitchSectionSyntax_Statements(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</SwitchSectionSyntax_Statements>\n");
}

public override void visitTypeArgumentListSyntax_Arguments(uint begin, uint end) {
    createIndentation();
    writer.Write("<TypeArgumentListSyntax_Arguments>\n");
    incDepth();
}

public override void visitEndTypeArgumentListSyntax_Arguments(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</TypeArgumentListSyntax_Arguments>\n");
}

public override void visitTypeConstraintSyntax_Type(uint begin, uint end) {
    createIndentation();
    writer.Write("<TypeConstraintSyntax_Type>\n");
    incDepth();
}

public override void visitEndTypeConstraintSyntax_Type(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</TypeConstraintSyntax_Type>\n");
}

public override void visitTypeCrefSyntax_Type(uint begin, uint end) {
    createIndentation();
    writer.Write("<TypeCrefSyntax_Type>\n");
    incDepth();
}

public override void visitEndTypeCrefSyntax_Type(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</TypeCrefSyntax_Type>\n");
}

public override void visitTypeDeclarationSyntax_ConstraintClauses(uint begin, uint end) {
    createIndentation();
    writer.Write("<TypeDeclarationSyntax_ConstraintClauses>\n");
    incDepth();
}

public override void visitEndTypeDeclarationSyntax_ConstraintClauses(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</TypeDeclarationSyntax_ConstraintClauses>\n");
}

public override void visitTypeDeclarationSyntax_Members(uint begin, uint end) {
    createIndentation();
    writer.Write("<TypeDeclarationSyntax_Members>\n");
    incDepth();
}

public override void visitEndTypeDeclarationSyntax_Members(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</TypeDeclarationSyntax_Members>\n");
}

public override void visitTypeDeclarationSyntax_TypeParameterList(uint begin, uint end) {
    createIndentation();
    writer.Write("<TypeDeclarationSyntax_TypeParameterList>\n");
    incDepth();
}

public override void visitEndTypeDeclarationSyntax_TypeParameterList(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</TypeDeclarationSyntax_TypeParameterList>\n");
}

public override void visitTypeParameterConstraintClauseSyntax_Constraints(uint begin, uint end) {
    createIndentation();
    writer.Write("<TypeParameterConstraintClauseSyntax_Constraints>\n");
    incDepth();
}

public override void visitEndTypeParameterConstraintClauseSyntax_Constraints(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</TypeParameterConstraintClauseSyntax_Constraints>\n");
}

public override void visitTypeParameterConstraintClauseSyntax_Name(uint begin, uint end) {
    createIndentation();
    writer.Write("<TypeParameterConstraintClauseSyntax_Name>\n");
    incDepth();
}

public override void visitEndTypeParameterConstraintClauseSyntax_Name(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</TypeParameterConstraintClauseSyntax_Name>\n");
}

public override void visitTypeParameterListSyntax_Parameters(uint begin, uint end) {
    createIndentation();
    writer.Write("<TypeParameterListSyntax_Parameters ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndTypeParameterListSyntax_Parameters(uint begin, uint end) {
}

public override void visitTypeParameterSyntax_AttributeLists(uint begin, uint end) {
    createIndentation();
    writer.Write("<TypeParameterSyntax_AttributeLists>\n");
    incDepth();
}

public override void visitEndTypeParameterSyntax_AttributeLists(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</TypeParameterSyntax_AttributeLists>\n");
}

public override void visitUsingDirectiveSyntax_Alias(uint begin, uint end) {
    createIndentation();
    writer.Write("<UsingDirectiveSyntax_Alias>\n");
    incDepth();
}

public override void visitEndUsingDirectiveSyntax_Alias(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</UsingDirectiveSyntax_Alias>\n");
}

public override void visitUsingDirectiveSyntax_Name(uint begin, uint end) {
    createIndentation();
    writer.Write("<UsingDirectiveSyntax_Name>\n");
    incDepth();
}

public override void visitEndUsingDirectiveSyntax_Name(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</UsingDirectiveSyntax_Name>\n");
}

public override void visitVariableDeclarationSyntax_Type(uint begin, uint end) {
    createIndentation();
    writer.Write("<VariableDeclarationSyntax_Type>\n");
    incDepth();
}

public override void visitEndVariableDeclarationSyntax_Type(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</VariableDeclarationSyntax_Type>\n");
}

public override void visitVariableDeclarationSyntax_Variables(uint begin, uint end) {
    createIndentation();
    writer.Write("<VariableDeclarationSyntax_Variables>\n");
    incDepth();
}

public override void visitEndVariableDeclarationSyntax_Variables(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</VariableDeclarationSyntax_Variables>\n");
}

public override void visitVariableDeclaratorSyntax_ArgumentList(uint begin, uint end) {
    createIndentation();
    writer.Write("<VariableDeclaratorSyntax_ArgumentList>\n");
    incDepth();
}

public override void visitEndVariableDeclaratorSyntax_ArgumentList(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</VariableDeclaratorSyntax_ArgumentList>\n");
}

public override void visitVariableDeclaratorSyntax_Initializer(uint begin, uint end) {
    createIndentation();
    writer.Write("<VariableDeclaratorSyntax_Initializer>\n");
    incDepth();
}

public override void visitEndVariableDeclaratorSyntax_Initializer(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</VariableDeclaratorSyntax_Initializer>\n");
}

public override void visitWhereClauseSyntax_Condition(uint begin, uint end) {
    createIndentation();
    writer.Write("<WhereClauseSyntax_Condition>\n");
    incDepth();
}

public override void visitEndWhereClauseSyntax_Condition(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</WhereClauseSyntax_Condition>\n");
}

public override void visitXmlAttributeSyntax_Name(uint begin, uint end) {
    createIndentation();
    writer.Write("<XmlAttributeSyntax_Name>\n");
    incDepth();
}

public override void visitEndXmlAttributeSyntax_Name(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</XmlAttributeSyntax_Name>\n");
}

public override void visitXmlCrefAttributeSyntax_Cref(uint begin, uint end) {
    createIndentation();
    writer.Write("<XmlCrefAttributeSyntax_Cref>\n");
    incDepth();
}

public override void visitEndXmlCrefAttributeSyntax_Cref(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</XmlCrefAttributeSyntax_Cref>\n");
}

public override void visitXmlElementEndTagSyntax_Name(uint begin, uint end) {
    createIndentation();
    writer.Write("<XmlElementEndTagSyntax_Name>\n");
    incDepth();
}

public override void visitEndXmlElementEndTagSyntax_Name(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</XmlElementEndTagSyntax_Name>\n");
}

public override void visitXmlElementStartTagSyntax_Attributes(uint begin, uint end) {
    createIndentation();
    writer.Write("<XmlElementStartTagSyntax_Attributes>\n");
    incDepth();
}

public override void visitEndXmlElementStartTagSyntax_Attributes(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</XmlElementStartTagSyntax_Attributes>\n");
}

public override void visitXmlElementStartTagSyntax_Name(uint begin, uint end) {
    createIndentation();
    writer.Write("<XmlElementStartTagSyntax_Name>\n");
    incDepth();
}

public override void visitEndXmlElementStartTagSyntax_Name(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</XmlElementStartTagSyntax_Name>\n");
}

public override void visitXmlElementSyntax_Content(uint begin, uint end) {
    createIndentation();
    writer.Write("<XmlElementSyntax_Content>\n");
    incDepth();
}

public override void visitEndXmlElementSyntax_Content(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</XmlElementSyntax_Content>\n");
}

public override void visitXmlElementSyntax_EndTag(uint begin, uint end) {
    createIndentation();
    writer.Write("<XmlElementSyntax_EndTag>\n");
    incDepth();
}

public override void visitEndXmlElementSyntax_EndTag(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</XmlElementSyntax_EndTag>\n");
}

public override void visitXmlElementSyntax_StartTag(uint begin, uint end) {
    createIndentation();
    writer.Write("<XmlElementSyntax_StartTag>\n");
    incDepth();
}

public override void visitEndXmlElementSyntax_StartTag(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</XmlElementSyntax_StartTag>\n");
}

public override void visitXmlEmptyElementSyntax_Attributes(uint begin, uint end) {
    createIndentation();
    writer.Write("<XmlEmptyElementSyntax_Attributes>\n");
    incDepth();
}

public override void visitEndXmlEmptyElementSyntax_Attributes(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</XmlEmptyElementSyntax_Attributes>\n");
}

public override void visitXmlEmptyElementSyntax_Name(uint begin, uint end) {
    createIndentation();
    writer.Write("<XmlEmptyElementSyntax_Name>\n");
    incDepth();
}

public override void visitEndXmlEmptyElementSyntax_Name(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</XmlEmptyElementSyntax_Name>\n");
}

public override void visitXmlNameAttributeSyntax_Identifier(uint begin, uint end) {
    createIndentation();
    writer.Write("<XmlNameAttributeSyntax_Identifier>\n");
    incDepth();
}

public override void visitEndXmlNameAttributeSyntax_Identifier(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</XmlNameAttributeSyntax_Identifier>\n");
}

public override void visitXmlNameSyntax_Prefix(uint begin, uint end) {
    createIndentation();
    writer.Write("<XmlNameSyntax_Prefix>\n");
    incDepth();
}

public override void visitEndXmlNameSyntax_Prefix(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</XmlNameSyntax_Prefix>\n");
}

public override void visitXmlProcessingInstructionSyntax_Name(uint begin, uint end) {
    createIndentation();
    writer.Write("<XmlProcessingInstructionSyntax_Name>\n");
    incDepth();
}

public override void visitEndXmlProcessingInstructionSyntax_Name(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</XmlProcessingInstructionSyntax_Name>\n");
}

        /// <summary>
        /// Creates the indentation according to the depth.
        /// </summary>
        protected void createIndentation() {
            if (depth != 0)
                writer.Write((new string('\t', (int)depth)));
        }

        /// <summary>
        /// Replaces the invalid characters for XML in the string.
        /// </summary>
        protected string chk(string str) {
            return str.Replace("&", "&amp;").Replace("<", "&lt;").Replace(">", "&gt;").Replace("'", "&apos;").Replace("\"", "&quot;").Replace("\n", "&#10;").Replace("\r", "&#13;").Replace("\t", "&#09;");
        }

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Base.Base node,bool composite, bool bWithParent = true ) {
  if (!composite) {
    writer.Write(" id='");
    if (!bNoId)
      writer.Write("id" + node.Id);
    writer.Write("'");

  }
  if (!composite) {
    writer.Write(" parent='");
    if (!bNoId)
      writer.Write("id" + ((node.Parent > 0) ? node.Parent : 0));
    writer.Write("'");

  }
  if (!composite) {
  }
}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Base.Positioned node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Base)node,composite,false);

  if (composite) {
    incDepth();
    createIndentation();
    writer.Write("<SourcePosition name='position'");
    writeAttributes(node.Position,false);
    writer.Write("/>\n");
    decDepth();
  }
}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.AliasQualifiedNameSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.NameSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.AnonymousFunctionExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node,composite,false);

  if (!composite) {
    writer.Write(" identifier='" + chk(node.Identifier) + "'");
  }
}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.AnonymousMethodExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.AnonymousFunctionExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.AnonymousObjectCreationExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node,composite,false);

  if (!composite) {
    writer.Write(" identifier='" + chk(node.Identifier) + "'");
  }
}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.ArrayCreationExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.ArrayTypeSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.AssignmentExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.AwaitExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.BaseExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.InstanceExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.BinaryExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.CastExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.CheckedExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.ConditionalAccessExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.ConditionalExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.DefaultExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.ElementAccessExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.ElementBindingExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.GenericNameSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.SimpleNameSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.IdentifierNameSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.SimpleNameSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.ImplicitArrayCreationExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.ImplicitElementAccessSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.InitializerExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.InstanceExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.InterpolatedStringExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.InvocationExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.LambdaExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.AnonymousFunctionExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.LiteralExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node,composite,false);

  if (!composite) {
    writer.Write(" token='" + chk(node.Token) + "'");
  }
}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.MakeRefExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.MemberAccessExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.MemberBindingExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.NameSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.NullableTypeSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.ObjectCreationExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.OmittedArraySizeExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.OmittedTypeArgumentSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.ParenthesizedLambdaExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.LambdaExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.PointerTypeSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.PostfixUnaryExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.PredefinedTypeSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.PrefixUnaryExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.QualifiedNameSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.NameSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.QueryExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.RefTypeExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.RefValueExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.SimpleLambdaExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.LambdaExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.SimpleNameSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.NameSyntax)node,composite,false);

  if (!composite) {
    writer.Write(" identifier='" + chk(node.Identifier) + "'");
  }
}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.SizeOfExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.StackAllocArrayCreationExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.ThisExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.InstanceExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.TypeOfExpressionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Expression.TypeSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Expression.ExpressionSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Statement.BlockSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Statement.BreakStatementSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Statement.CheckedStatementSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Statement.ContinueStatementSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Statement.DoStatementSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Statement.EmptyStatementSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Statement.ExpressionStatementSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Statement.FixedStatementSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Statement.ForEachStatementSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node,composite,false);

  if (!composite) {
    writer.Write(" identifier='" + chk(node.Identifier) + "'");
  }
}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Statement.ForStatementSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Statement.GotoStatementSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Statement.IfStatementSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Statement.LabeledStatementSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node,composite,false);

  if (!composite) {
    writer.Write(" identifier='" + chk(node.Identifier) + "'");
  }
}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Statement.LocalDeclarationStatementSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Statement.LockStatementSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Statement.ReturnStatementSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Statement.SwitchStatementSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Statement.ThrowStatementSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Statement.TryStatementSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Statement.UnsafeStatementSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Statement.UsingStatementSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Statement.WhileStatementSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Statement.YieldStatementSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Statement.StatementSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.AccessorDeclarationSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

  if (!composite) {
    writer.Write(" identifier='" + chk(node.Identifier) + "'");
  }
}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.AccessorListSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.AnonymousObjectMemberDeclaratorSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.ArgumentListSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.BaseArgumentListSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.ArgumentSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.ArrayRankSpecifierSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.ArrowExpressionClauseSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentListSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.AttributeArgumentSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.AttributeListSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.AttributeSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.AttributeTargetSpecifierSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

  if (!composite) {
    writer.Write(" identifier='" + chk(node.Identifier) + "'");
  }
}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.BaseArgumentListSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.BaseCrefParameterListSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.BaseFieldDeclarationSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.BaseListSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.BaseMethodDeclarationSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.BaseParameterListSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.BasePropertyDeclarationSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.BaseTypeDeclarationSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)node,composite,false);

  if (!composite) {
    writer.Write(" identifier='" + chk(node.Identifier) + "'");
  }
}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.BaseTypeSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.BracketedArgumentListSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.BaseArgumentListSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.BracketedParameterListSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.BaseParameterListSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.CaseSwitchLabelSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.SwitchLabelSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.CatchClauseSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.CatchDeclarationSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.CatchFilterClauseSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.ClassDeclarationSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.TypeDeclarationSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.ClassOrStructConstraintSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.CompilationUnitSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.ConstructorConstraintSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.ConstructorDeclarationSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.BaseMethodDeclarationSyntax)node,composite,false);

  if (!composite) {
    writer.Write(" identifier='" + chk(node.Identifier) + "'");
  }
}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.ConstructorInitializerSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorDeclarationSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.BaseMethodDeclarationSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.ConversionOperatorMemberCrefSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.MemberCrefSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.CrefBracketedParameterListSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.BaseCrefParameterListSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.CrefParameterListSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.BaseCrefParameterListSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.CrefParameterSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.CrefSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.DefaultSwitchLabelSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.SwitchLabelSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.DelegateDeclarationSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)node,composite,false);

  if (!composite) {
    writer.Write(" identifier='" + chk(node.Identifier) + "'");
  }
}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.DestructorDeclarationSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.BaseMethodDeclarationSyntax)node,composite,false);

  if (!composite) {
    writer.Write(" identifier='" + chk(node.Identifier) + "'");
  }
}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.ElseClauseSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.EnumDeclarationSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.BaseTypeDeclarationSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.EnumMemberDeclarationSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)node,composite,false);

  if (!composite) {
    writer.Write(" identifier='" + chk(node.Identifier) + "'");
  }
}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.EqualsValueClauseSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.EventDeclarationSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.BasePropertyDeclarationSyntax)node,composite,false);

  if (!composite) {
    writer.Write(" identifier='" + chk(node.Identifier) + "'");
  }
}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.EventFieldDeclarationSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.BaseFieldDeclarationSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.ExplicitInterfaceSpecifierSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.ExternAliasDirectiveSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

  if (!composite) {
    writer.Write(" identifier='" + chk(node.Identifier) + "'");
  }
}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.FieldDeclarationSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.BaseFieldDeclarationSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.FinallyClauseSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.FromClauseSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax)node,composite,false);

  if (!composite) {
    writer.Write(" identifier='" + chk(node.Identifier) + "'");
  }
}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.GlobalStatementSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.GroupClauseSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.SelectOrGroupClauseSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.IncompleteMemberSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.IndexerDeclarationSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.BasePropertyDeclarationSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.IndexerMemberCrefSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.MemberCrefSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.InterfaceDeclarationSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.TypeDeclarationSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringContentSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringTextSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringContentSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.InterpolationAlignmentClauseSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.InterpolationFormatClauseSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.InterpolationSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.InterpolatedStringContentSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.JoinClauseSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax)node,composite,false);

  if (!composite) {
    writer.Write(" identifier='" + chk(node.Identifier) + "'");
  }
}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.JoinIntoClauseSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

  if (!composite) {
    writer.Write(" identifier='" + chk(node.Identifier) + "'");
  }
}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.LetClauseSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax)node,composite,false);

  if (!composite) {
    writer.Write(" identifier='" + chk(node.Identifier) + "'");
  }
}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.MemberCrefSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.CrefSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.MethodDeclarationSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.BaseMethodDeclarationSyntax)node,composite,false);

  if (!composite) {
    writer.Write(" identifier='" + chk(node.Identifier) + "'");
  }
}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.NameColonSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.NameEqualsSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.NameMemberCrefSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.MemberCrefSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.NamespaceDeclarationSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.MemberDeclarationSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.OperatorDeclarationSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.BaseMethodDeclarationSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.OperatorMemberCrefSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.MemberCrefSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.OrderByClauseSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.OrderingSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.ParameterListSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.BaseParameterListSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.ParameterSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

  if (!composite) {
    writer.Write(" identifier='" + chk(node.Identifier) + "'");
  }
}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.PropertyDeclarationSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.BasePropertyDeclarationSyntax)node,composite,false);

  if (!composite) {
    writer.Write(" identifier='" + chk(node.Identifier) + "'");
  }
}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.QualifiedCrefSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.CrefSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.QueryBodySyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.QueryContinuationSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

  if (!composite) {
    writer.Write(" identifier='" + chk(node.Identifier) + "'");
  }
}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.SelectClauseSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.SelectOrGroupClauseSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.SelectOrGroupClauseSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.SimpleBaseTypeSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.BaseTypeSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.StructDeclarationSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.TypeDeclarationSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.SwitchLabelSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.SwitchSectionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.SyntaxToken node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.TypeArgumentListSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.TypeConstraintSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.TypeCrefSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.CrefSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.TypeDeclarationSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.BaseTypeDeclarationSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintClauseSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.TypeParameterConstraintSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.TypeParameterListSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.TypeParameterSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

  if (!composite) {
    writer.Write(" identifier='" + chk(node.Identifier) + "'");
  }
}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.UsingDirectiveSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.VariableDeclarationSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.VariableDeclaratorSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

  if (!composite) {
    writer.Write(" identifier='" + chk(node.Identifier) + "'");
  }
}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.WhereClauseSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.QueryClauseSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.XmlAttributeSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.XmlCDataSectionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.XmlCommentSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.XmlCrefAttributeSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.XmlAttributeSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.XmlElementEndTagSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.XmlElementStartTagSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.XmlElementSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.XmlEmptyElementSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.XmlNameAttributeSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.XmlAttributeSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.XmlNameSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.XmlPrefixSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Base.Positioned)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.XmlProcessingInstructionSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.XmlTextAttributeSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.XmlAttributeSyntax)node,composite,false);

}

public void writeAttributes(Columbus.Csharp.Asg.Nodes.Structure.XmlTextSyntax node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Csharp.Asg.Nodes.Structure.XmlNodeSyntax)node,composite,false);

}

        /// <summary>
        /// Writes out the attributes of the SourcePosition node.
        /// </summary>
protected void writeAttributes(SourcePosition compType,bool composite) {
  if (!composite) {
    writer.Write(" endColumn='" + compType.EndColumn + "'");
  }
  if (!composite) {
    writer.Write(" endLine='" + compType.EndLine + "'");
  }
  if (!composite) {
    writer.Write(" fileName='" + chk(compType.FileName) + "'");
  }
  if (!composite) {
    writer.Write(" startColumn='" + compType.StartColumn + "'");
  }
  if (!composite) {
    writer.Write(" startLine='" + compType.StartLine + "'");
  }
}

            }

}
