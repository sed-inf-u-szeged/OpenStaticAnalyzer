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

namespace Columbus.Lim.Asg.Visitors {

    /// <summary>
    /// Creates XML dump of the ASG.
    /// </summary>
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class VisitorLIMML : Visitor {

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
        public VisitorLIMML(StreamWriter targetStream, string projectName, bool encodingFromWriter, WriteMessageFunc writeMessage, bool noId) : base() {
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
            writer.WriteLine("<!DOCTYPE Project SYSTEM 'lim-3.0.28.dtd'>");
            writer.Write("<Project name='{0}'", projectName);
            writer.Write(" xmlns:base='columbus_lim_schema/base'");
            writer.Write(" xmlns:logical='columbus_lim_schema/logical'");
            writer.Write(" xmlns:physical='columbus_lim_schema/physical'");
            writer.Write(" xmlns:type='columbus_lim_schema/type'");
            writer.WriteLine(">");
        }

        /// <summary>
        /// Finishes the XML dumping.
        /// </summary>
        public override void finishVisit() {
            writer.WriteLine("<Filtered id='id1'/>");
            writer.WriteLine("</Project>");
        }

public override void visit(Columbus.Lim.Asg.Nodes.Base.Comment node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<base:Comment");
  writeAttributes(node,false,true);
  writer.Write("/>\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Lim.Asg.Nodes.Base.Comment node, bool callVirtualBase) {
}

public override void visit(Columbus.Lim.Asg.Nodes.Base.Component node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<base:Component");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Lim.Asg.Nodes.Base.Component node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</base:Component>\n");
}

public override void visit(Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<base:ControlFlowBlock");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</base:ControlFlowBlock>\n");
}

public override void visit(Columbus.Lim.Asg.Nodes.Logical.Attribute node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<logical:Attribute");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.Attribute node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</logical:Attribute>\n");
}

public override void visit(Columbus.Lim.Asg.Nodes.Logical.AttributeAccess node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<logical:AttributeAccess");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.AttributeAccess node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</logical:AttributeAccess>\n");
}

public override void visit(Columbus.Lim.Asg.Nodes.Logical.Class node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<logical:Class");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.Class node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</logical:Class>\n");
}

public override void visit(Columbus.Lim.Asg.Nodes.Logical.ClassGeneric node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<logical:ClassGeneric");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.ClassGeneric node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</logical:ClassGeneric>\n");
}

public override void visit(Columbus.Lim.Asg.Nodes.Logical.ClassGenericInstance node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<logical:ClassGenericInstance");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.ClassGenericInstance node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</logical:ClassGenericInstance>\n");
}

public override void visit(Columbus.Lim.Asg.Nodes.Logical.ClassGenericSpec node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<logical:ClassGenericSpec");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.ClassGenericSpec node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</logical:ClassGenericSpec>\n");
}

public override void visit(Columbus.Lim.Asg.Nodes.Logical.Friendship node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<logical:Friendship");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.Friendship node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</logical:Friendship>\n");
}

public override void visit(Columbus.Lim.Asg.Nodes.Logical.GenericParameter node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<logical:GenericParameter");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.GenericParameter node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</logical:GenericParameter>\n");
}

public override void visit(Columbus.Lim.Asg.Nodes.Logical.Method node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<logical:Method");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.Method node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</logical:Method>\n");
}

public override void visit(Columbus.Lim.Asg.Nodes.Logical.MethodCall node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<logical:MethodCall");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.MethodCall node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</logical:MethodCall>\n");
}

public override void visit(Columbus.Lim.Asg.Nodes.Logical.MethodGeneric node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<logical:MethodGeneric");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.MethodGeneric node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</logical:MethodGeneric>\n");
}

public override void visit(Columbus.Lim.Asg.Nodes.Logical.MethodGenericInstance node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<logical:MethodGenericInstance");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.MethodGenericInstance node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</logical:MethodGenericInstance>\n");
}

public override void visit(Columbus.Lim.Asg.Nodes.Logical.MethodGenericSpec node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<logical:MethodGenericSpec");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.MethodGenericSpec node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</logical:MethodGenericSpec>\n");
}

public override void visit(Columbus.Lim.Asg.Nodes.Logical.Package node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<logical:Package");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.Package node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</logical:Package>\n");
}

public override void visit(Columbus.Lim.Asg.Nodes.Logical.Parameter node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<logical:Parameter");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Lim.Asg.Nodes.Logical.Parameter node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</logical:Parameter>\n");
}

public override void visit(Columbus.Lim.Asg.Nodes.Physical.File node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<physical:File");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Lim.Asg.Nodes.Physical.File node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</physical:File>\n");
}

public override void visit(Columbus.Lim.Asg.Nodes.Physical.FileSystem node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<physical:FileSystem");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Lim.Asg.Nodes.Physical.FileSystem node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</physical:FileSystem>\n");
}

public override void visit(Columbus.Lim.Asg.Nodes.Physical.Folder node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<physical:Folder");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Lim.Asg.Nodes.Physical.Folder node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</physical:Folder>\n");
}

public override void visit(Columbus.Lim.Asg.Nodes.Type.SimpleType node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<type:SimpleType");
  writeAttributes(node,false,true);
  writer.Write("/>\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Lim.Asg.Nodes.Type.SimpleType node, bool callVirtualBase) {
}

public override void visit(Columbus.Lim.Asg.Nodes.Type.Type node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<type:Type");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Lim.Asg.Nodes.Type.Type node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</type:Type>\n");
}

public override void visit(Columbus.Lim.Asg.Nodes.Type.TypeFormerArray node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<type:TypeFormerArray");
  writeAttributes(node,false,true);
  writer.Write("/>\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Lim.Asg.Nodes.Type.TypeFormerArray node, bool callVirtualBase) {
}

public override void visit(Columbus.Lim.Asg.Nodes.Type.TypeFormerMethod node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<type:TypeFormerMethod");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Lim.Asg.Nodes.Type.TypeFormerMethod node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</type:TypeFormerMethod>\n");
}

public override void visit(Columbus.Lim.Asg.Nodes.Type.TypeFormerNonType node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<type:TypeFormerNonType");
  writeAttributes(node,false,true);
  writer.Write("/>\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Lim.Asg.Nodes.Type.TypeFormerNonType node, bool callVirtualBase) {
}

public override void visit(Columbus.Lim.Asg.Nodes.Type.TypeFormerPointer node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<type:TypeFormerPointer");
  writeAttributes(node,false,true);
  writer.Write("/>\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Lim.Asg.Nodes.Type.TypeFormerPointer node, bool callVirtualBase) {
}

public override void visit(Columbus.Lim.Asg.Nodes.Type.TypeFormerType node, bool callVirtualBase) {
  createIndentation();
  writer.Write("<type:TypeFormerType");
  writeAttributes(node,false,true);
  writer.Write(">\n");

  writeAttributes(node,true,true);
}

public override void visitEnd(Columbus.Lim.Asg.Nodes.Type.TypeFormerType node, bool callVirtualBase) {
  createIndentation();
  writer.Write("</type:TypeFormerType>\n");
}

public override void visitComponent_Contains(uint begin, uint end) {
    createIndentation();
    writer.Write("<Component_Contains ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndComponent_Contains(uint begin, uint end) {
}

public override void visitComponent_HasFiles(uint begin, uint end) {
    createIndentation();
    writer.Write("<Component_HasFiles ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndComponent_HasFiles(uint begin, uint end) {
}

public override void visitControlFlowBlock_Calls(uint begin, uint end) {
    createIndentation();
    writer.Write("<ControlFlowBlock_Calls ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndControlFlowBlock_Calls(uint begin, uint end) {
}

public override void visitControlFlowBlock_Pred(uint begin, uint end) {
    createIndentation();
    writer.Write("<ControlFlowBlock_Pred ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndControlFlowBlock_Pred(uint begin, uint end) {
}

public override void visitNamed_DependsOn(uint begin, uint end, string ac) {
    createIndentation();
    writer.Write("<Named_DependsOn ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("' value='" + ac + "'/>\n");
}

public override void visitEndNamed_DependsOn(uint begin, uint end, string ac) {
}

public override void visitAttribute_Calls(uint begin, uint end) {
    createIndentation();
    writer.Write("<Attribute_Calls ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndAttribute_Calls(uint begin, uint end) {
}

public override void visitAttribute_HasType(uint begin, uint end) {
    createIndentation();
    writer.Write("<Attribute_HasType ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndAttribute_HasType(uint begin, uint end) {
}

public override void visitAttributeAccess_Attribute(uint begin, uint end) {
    createIndentation();
    writer.Write("<AttributeAccess_Attribute ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndAttributeAccess_Attribute(uint begin, uint end) {
}

public override void visitClass_GrantsFriendship(uint begin, uint end) {
    createIndentation();
    writer.Write("<Class_GrantsFriendship ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndClass_GrantsFriendship(uint begin, uint end) {
}

public override void visitClass_IsSubclass(uint begin, uint end) {
    createIndentation();
    writer.Write("<Class_IsSubclass ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndClass_IsSubclass(uint begin, uint end) {
}

public override void visitClassGeneric_HasGenericParameter(uint begin, uint end) {
    createIndentation();
    writer.Write("<ClassGeneric_HasGenericParameter>\n");
    incDepth();
}

public override void visitEndClassGeneric_HasGenericParameter(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</ClassGeneric_HasGenericParameter>\n");
}

public override void visitClassGenericInstance_HasArguments(uint begin, uint end, Types.TypeArgumentConstraintKind ac) {
    createIndentation();
    writer.Write("<ClassGenericInstance_HasArguments ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("' value='" + ac.ToString() + "'/>\n");
}

public override void visitEndClassGenericInstance_HasArguments(uint begin, uint end, Types.TypeArgumentConstraintKind ac) {
}

public override void visitClassGenericSpec_HasArguments(uint begin, uint end, Types.TypeArgumentConstraintKind ac) {
    createIndentation();
    writer.Write("<ClassGenericSpec_HasArguments ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("' value='" + ac.ToString() + "'/>\n");
}

public override void visitEndClassGenericSpec_HasArguments(uint begin, uint end, Types.TypeArgumentConstraintKind ac) {
}

public override void visitClassGenericSpec_Specialize(uint begin, uint end) {
    createIndentation();
    writer.Write("<ClassGenericSpec_Specialize ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndClassGenericSpec_Specialize(uint begin, uint end) {
}

public override void visitFriendship_Friend(uint begin, uint end) {
    createIndentation();
    writer.Write("<Friendship_Friend ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndFriendship_Friend(uint begin, uint end) {
}

public override void visitGenericParameter_HasParameterConstraint(uint begin, uint end) {
    createIndentation();
    writer.Write("<GenericParameter_HasParameterConstraint ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndGenericParameter_HasParameterConstraint(uint begin, uint end) {
}

public override void visitMember_Aggregated(uint begin, uint end) {
    createIndentation();
    writer.Write("<Member_Aggregated ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndMember_Aggregated(uint begin, uint end) {
}

public override void visitMember_BelongsTo(uint begin, uint end) {
    createIndentation();
    writer.Write("<Member_BelongsTo ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndMember_BelongsTo(uint begin, uint end) {
}

public override void visitMember_CompilationUnit(uint begin, uint end) {
    createIndentation();
    writer.Write("<Member_CompilationUnit ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndMember_CompilationUnit(uint begin, uint end) {
}

public override void visitMember_Declares(uint begin, uint end) {
    createIndentation();
    writer.Write("<Member_Declares ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndMember_Declares(uint begin, uint end) {
}

public override void visitMember_HasComment(uint begin, uint end) {
    createIndentation();
    writer.Write("<Member_HasComment ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndMember_HasComment(uint begin, uint end) {
}

public override void visitMember_Instance(uint begin, uint end) {
    createIndentation();
    writer.Write("<Member_Instance ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndMember_Instance(uint begin, uint end) {
}

public override void visitMember_IsContainedIn(uint begin, uint end, SourcePosition ac) {
    createIndentation();
    writer.Write("<Member_IsContainedIn ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'>\n");
    incDepth();
    createIndentation();
    writer.Write("<SourcePosition");
    writeAttributes(ac,false);
    writer.Write("/>\n");
}

public override void visitEndMember_IsContainedIn(uint begin, uint end, SourcePosition ac) {
    decDepth();
    createIndentation();
    writer.Write("</Member_IsContainedIn>\n");
}

public override void visitMember_LanguageVariant(uint begin, uint end) {
    createIndentation();
    writer.Write("<Member_LanguageVariant ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndMember_LanguageVariant(uint begin, uint end) {
}

public override void visitMember_Uses(uint begin, uint end) {
    createIndentation();
    writer.Write("<Member_Uses ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndMember_Uses(uint begin, uint end) {
}

public override void visitMember_Variant(uint begin, uint end) {
    createIndentation();
    writer.Write("<Member_Variant ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndMember_Variant(uint begin, uint end) {
}

public override void visitMethod_AccessesAttribute(uint begin, uint end) {
    createIndentation();
    writer.Write("<Method_AccessesAttribute ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndMethod_AccessesAttribute(uint begin, uint end) {
}

public override void visitMethod_Calls(uint begin, uint end) {
    createIndentation();
    writer.Write("<Method_Calls ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndMethod_Calls(uint begin, uint end) {
}

public override void visitMethod_CanThrow(uint begin, uint end) {
    createIndentation();
    writer.Write("<Method_CanThrow ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndMethod_CanThrow(uint begin, uint end) {
}

public override void visitMethod_HasControlFlowBlock(uint begin, uint end) {
    createIndentation();
    writer.Write("<Method_HasControlFlowBlock>\n");
    incDepth();
}

public override void visitEndMethod_HasControlFlowBlock(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</Method_HasControlFlowBlock>\n");
}

public override void visitMethod_HasParameter(uint begin, uint end) {
    createIndentation();
    writer.Write("<Method_HasParameter>\n");
    incDepth();
}

public override void visitEndMethod_HasParameter(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</Method_HasParameter>\n");
}

public override void visitMethod_Instantiates(uint begin, uint end) {
    createIndentation();
    writer.Write("<Method_Instantiates ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndMethod_Instantiates(uint begin, uint end) {
}

public override void visitMethod_Returns(uint begin, uint end) {
    createIndentation();
    writer.Write("<Method_Returns ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndMethod_Returns(uint begin, uint end) {
}

public override void visitMethod_Throws(uint begin, uint end) {
    createIndentation();
    writer.Write("<Method_Throws ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndMethod_Throws(uint begin, uint end) {
}

public override void visitMethodCall_Method(uint begin, uint end) {
    createIndentation();
    writer.Write("<MethodCall_Method ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndMethodCall_Method(uint begin, uint end) {
}

public override void visitMethodGeneric_HasGenericParameter(uint begin, uint end) {
    createIndentation();
    writer.Write("<MethodGeneric_HasGenericParameter>\n");
    incDepth();
}

public override void visitEndMethodGeneric_HasGenericParameter(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</MethodGeneric_HasGenericParameter>\n");
}

public override void visitMethodGenericInstance_HasArguments(uint begin, uint end, Types.TypeArgumentConstraintKind ac) {
    createIndentation();
    writer.Write("<MethodGenericInstance_HasArguments ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("' value='" + ac.ToString() + "'/>\n");
}

public override void visitEndMethodGenericInstance_HasArguments(uint begin, uint end, Types.TypeArgumentConstraintKind ac) {
}

public override void visitMethodGenericSpec_HasArguments(uint begin, uint end, Types.TypeArgumentConstraintKind ac) {
    createIndentation();
    writer.Write("<MethodGenericSpec_HasArguments ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("' value='" + ac.ToString() + "'/>\n");
}

public override void visitEndMethodGenericSpec_HasArguments(uint begin, uint end, Types.TypeArgumentConstraintKind ac) {
}

public override void visitMethodGenericSpec_Specialize(uint begin, uint end) {
    createIndentation();
    writer.Write("<MethodGenericSpec_Specialize ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndMethodGenericSpec_Specialize(uint begin, uint end) {
}

public override void visitParameter_HasType(uint begin, uint end) {
    createIndentation();
    writer.Write("<Parameter_HasType ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndParameter_HasType(uint begin, uint end) {
}

public override void visitScope_HasMember(uint begin, uint end) {
    createIndentation();
    writer.Write("<Scope_HasMember ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndScope_HasMember(uint begin, uint end) {
}

public override void visitFile_HasComment(uint begin, uint end) {
    createIndentation();
    writer.Write("<File_HasComment ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndFile_HasComment(uint begin, uint end) {
}

public override void visitFile_Includes(uint begin, uint end) {
    createIndentation();
    writer.Write("<File_Includes ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndFile_Includes(uint begin, uint end) {
}

public override void visitFileSystem_HasFSEntry(uint begin, uint end) {
    createIndentation();
    writer.Write("<FileSystem_HasFSEntry>\n");
    incDepth();
}

public override void visitEndFileSystem_HasFSEntry(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</FileSystem_HasFSEntry>\n");
}

public override void visitFolder_Contains(uint begin, uint end) {
    createIndentation();
    writer.Write("<Folder_Contains>\n");
    incDepth();
}

public override void visitEndFolder_Contains(uint begin, uint end) {
    decDepth();
    createIndentation();
    writer.Write("</Folder_Contains>\n");
}

public override void visitType_HasTypeFormer(uint begin, uint end) {
    createIndentation();
    writer.Write("<Type_HasTypeFormer ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndType_HasTypeFormer(uint begin, uint end) {
}

public override void visitTypeFormerMethod_HasParameterType(uint begin, uint end, Types.ParameterKind ac) {
    createIndentation();
    writer.Write("<TypeFormerMethod_HasParameterType ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("' value='" + ac.ToString() + "'/>\n");
}

public override void visitEndTypeFormerMethod_HasParameterType(uint begin, uint end, Types.ParameterKind ac) {
}

public override void visitTypeFormerMethod_HasReturnType(uint begin, uint end) {
    createIndentation();
    writer.Write("<TypeFormerMethod_HasReturnType ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndTypeFormerMethod_HasReturnType(uint begin, uint end) {
}

public override void visitTypeFormerType_RefersTo(uint begin, uint end) {
    createIndentation();
    writer.Write("<TypeFormerType_RefersTo ref='");
    if (!bNoId)
      writer.Write("id" + end);
    writer.Write("'/>\n");
}

public override void visitEndTypeFormerType_RefersTo(uint begin, uint end) {
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

public void writeAttributes(Columbus.Lim.Asg.Nodes.Base.Base node,bool composite, bool bWithParent = true ) {
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

public void writeAttributes(Columbus.Lim.Asg.Nodes.Base.Comment node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Lim.Asg.Nodes.Base.Base)node,composite,false);

  if (!composite) {
    writer.Write(" text='" + chk(node.Text) + "'");
  }
}

public void writeAttributes(Columbus.Lim.Asg.Nodes.Base.Component node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Lim.Asg.Nodes.Base.Named)node,composite,false);

  if (!composite) {
    writer.Write(" TLLOC='" + node.TLLOC + "'");
  }
  if (!composite) {
    writer.Write(" TLOC='" + node.TLOC + "'");
  }
  if (!composite) {
    writer.Write(" analysisTime='" + node.AnalysisTime.ToString() + "'");
  }
  if (!composite) {
    writer.Write(" changesetID='" + chk(node.ChangesetID) + "'");
  }
  if (!composite) {
    writer.Write(" shortName='" + chk(node.ShortName) + "'");
  }
}

public void writeAttributes(Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Lim.Asg.Nodes.Base.Base)node,composite,false);

}

public void writeAttributes(Columbus.Lim.Asg.Nodes.Base.Named node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Lim.Asg.Nodes.Base.Base)node,composite,false);

  if (!composite) {
    writer.Write(" name='" + chk(node.Name) + "'");
  }
}

public void writeAttributes(Columbus.Lim.Asg.Nodes.Logical.Attribute node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Lim.Asg.Nodes.Logical.Member)node,composite,false);

}

public void writeAttributes(Columbus.Lim.Asg.Nodes.Logical.AttributeAccess node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Lim.Asg.Nodes.Base.Base)node,composite,false);

  if (!composite) {
    writer.Write(" accesses='" + chk(node.Accesses) + "'");
  }
}

public void writeAttributes(Columbus.Lim.Asg.Nodes.Logical.Class node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Lim.Asg.Nodes.Logical.Scope)node,composite,false);

  if (!composite) {
    writer.Write(" classKind='" + node.ClassKind.ToString() + "'");
  }
  if (!composite) {
    writer.Write(" isAbstract='" + (node.IsAbstract ? "true" : "false") + "'");
  }
  if (!composite) {
    writer.Write(" objectSize='" + node.ObjectSize + "'");
  }
}

public void writeAttributes(Columbus.Lim.Asg.Nodes.Logical.ClassGeneric node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Lim.Asg.Nodes.Logical.Class)node,composite,false);

}

public void writeAttributes(Columbus.Lim.Asg.Nodes.Logical.ClassGenericInstance node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Lim.Asg.Nodes.Logical.Class)node,composite,false);

  if (!composite) {
    writer.Write(" isRealInstance='" + (node.IsRealInstance ? "true" : "false") + "'");
  }
}

public void writeAttributes(Columbus.Lim.Asg.Nodes.Logical.ClassGenericSpec node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Lim.Asg.Nodes.Logical.ClassGeneric)node,composite,false);

}

public void writeAttributes(Columbus.Lim.Asg.Nodes.Logical.Friendship node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Lim.Asg.Nodes.Base.Base)node,composite,false);

  if (!composite) {
    writer.Write(" grants='" + chk(node.Grants) + "'");
  }
}

public void writeAttributes(Columbus.Lim.Asg.Nodes.Logical.GenericParameter node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Lim.Asg.Nodes.Base.Named)node,composite,false);

  if (!composite) {
    writer.Write(" genericParameterKind='" + node.GenericParameterKind.ToString() + "'");
  }
}

public void writeAttributes(Columbus.Lim.Asg.Nodes.Logical.Member node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Lim.Asg.Nodes.Base.Named)node,composite,false);

  if (!composite) {
    writer.Write(" accessibility='" + node.Accessibility.ToString() + "'");
  }
  if (!composite) {
    writer.Write(" commentLines='" + node.CommentLines + "'");
  }
  if (!composite) {
    writer.Write(" demangledName='" + chk(node.DemangledName) + "'");
  }
  if (!composite) {
    writer.Write(" isCompilerGenerated='" + (node.IsCompilerGenerated ? "true" : "false") + "'");
  }
  if (!composite) {
    writer.Write(" isStatic='" + (node.IsStatic ? "true" : "false") + "'");
  }
  if (!composite) {
    writer.Write(" language='" + node.Language.ToString() + "'");
  }
  if (!composite) {
    writer.Write(" mangledName='" + chk(node.MangledName) + "'");
  }
}

public void writeAttributes(Columbus.Lim.Asg.Nodes.Logical.Method node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Lim.Asg.Nodes.Logical.Scope)node,composite,false);

  if (!composite) {
    writer.Write(" distinctOperands='" + node.DistinctOperands + "'");
  }
  if (!composite) {
    writer.Write(" distinctOperators='" + node.DistinctOperators + "'");
  }
  if (!composite) {
    writer.Write(" isAbstract='" + (node.IsAbstract ? "true" : "false") + "'");
  }
  if (!composite) {
    writer.Write(" isVirtual='" + (node.IsVirtual ? "true" : "false") + "'");
  }
  if (!composite) {
    writer.Write(" methodKind='" + node.MethodKind.ToString() + "'");
  }
  if (!composite) {
    writer.Write(" nestingLevel='" + node.NestingLevel + "'");
  }
  if (!composite) {
    writer.Write(" nestingLevelElseIf='" + node.NestingLevelElseIf + "'");
  }
  if (!composite) {
    writer.Write(" numberOfBranches='" + node.NumberOfBranches + "'");
  }
  if (!composite) {
    writer.Write(" numberOfStatements='" + node.NumberOfStatements + "'");
  }
  if (!composite) {
    writer.Write(" totalOperands='" + node.TotalOperands + "'");
  }
  if (!composite) {
    writer.Write(" totalOperators='" + node.TotalOperators + "'");
  }
}

public void writeAttributes(Columbus.Lim.Asg.Nodes.Logical.MethodCall node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Lim.Asg.Nodes.Base.Base)node,composite,false);

  if (!composite) {
    writer.Write(" calls='" + chk(node.Calls) + "'");
  }
}

public void writeAttributes(Columbus.Lim.Asg.Nodes.Logical.MethodGeneric node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Lim.Asg.Nodes.Logical.Method)node,composite,false);

}

public void writeAttributes(Columbus.Lim.Asg.Nodes.Logical.MethodGenericInstance node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Lim.Asg.Nodes.Logical.Method)node,composite,false);

  if (!composite) {
    writer.Write(" isRealInstance='" + (node.IsRealInstance ? "true" : "false") + "'");
  }
}

public void writeAttributes(Columbus.Lim.Asg.Nodes.Logical.MethodGenericSpec node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Lim.Asg.Nodes.Logical.MethodGeneric)node,composite,false);

}

public void writeAttributes(Columbus.Lim.Asg.Nodes.Logical.Package node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Lim.Asg.Nodes.Logical.Scope)node,composite,false);

  if (!composite) {
    writer.Write(" packageKind='" + node.PackageKind.ToString() + "'");
  }
}

public void writeAttributes(Columbus.Lim.Asg.Nodes.Logical.Parameter node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Lim.Asg.Nodes.Base.Named)node,composite,false);

  if (!composite) {
    writer.Write(" paramKind='" + node.ParamKind.ToString() + "'");
  }
}

public void writeAttributes(Columbus.Lim.Asg.Nodes.Logical.Scope node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Lim.Asg.Nodes.Logical.Member)node,composite,false);

  if (!composite) {
    writer.Write(" LLOC='" + node.LLOC + "'");
  }
  if (!composite) {
    writer.Write(" LOC='" + node.LOC + "'");
  }
  if (!composite) {
    writer.Write(" TLLOC='" + node.TLLOC + "'");
  }
  if (!composite) {
    writer.Write(" TLOC='" + node.TLOC + "'");
  }
  if (!composite) {
    writer.Write(" isAnonymous='" + (node.IsAnonymous ? "true" : "false") + "'");
  }
}

public void writeAttributes(Columbus.Lim.Asg.Nodes.Physical.FSEntry node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Lim.Asg.Nodes.Base.Named)node,composite,false);

}

public void writeAttributes(Columbus.Lim.Asg.Nodes.Physical.File node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Lim.Asg.Nodes.Physical.FSEntry)node,composite,false);

  if (!composite) {
    writer.Write(" CLOC='" + node.CLOC + "'");
  }
  if (!composite) {
    writer.Write(" LLOC='" + node.LLOC + "'");
  }
  if (!composite) {
    writer.Write(" LOC='" + node.LOC + "'");
  }
  if (!composite) {
    writer.Write(" numberOfBranches='" + node.NumberOfBranches + "'");
  }
}

public void writeAttributes(Columbus.Lim.Asg.Nodes.Physical.FileSystem node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Lim.Asg.Nodes.Base.Named)node,composite,false);

}

public void writeAttributes(Columbus.Lim.Asg.Nodes.Physical.Folder node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Lim.Asg.Nodes.Physical.FSEntry)node,composite,false);

}

public void writeAttributes(Columbus.Lim.Asg.Nodes.Type.SimpleType node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Lim.Asg.Nodes.Base.Base)node,composite,false);

  if (!composite) {
    writer.Write(" simpleTypeKind='" + node.SimpleTypeKind.ToString() + "'");
  }
}

public void writeAttributes(Columbus.Lim.Asg.Nodes.Type.Type node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Lim.Asg.Nodes.Base.Base)node,composite,false);

  if (!composite) {
    writer.Write(" refers='" + chk(node.Refers) + "'");
  }
}

public void writeAttributes(Columbus.Lim.Asg.Nodes.Type.TypeFormer node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Lim.Asg.Nodes.Base.Base)node,composite,false);

}

public void writeAttributes(Columbus.Lim.Asg.Nodes.Type.TypeFormerArray node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Lim.Asg.Nodes.Type.TypeFormer)node,composite,false);

}

public void writeAttributes(Columbus.Lim.Asg.Nodes.Type.TypeFormerMethod node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Lim.Asg.Nodes.Type.TypeFormer)node,composite,false);

}

public void writeAttributes(Columbus.Lim.Asg.Nodes.Type.TypeFormerNonType node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Lim.Asg.Nodes.Type.TypeFormer)node,composite,false);

}

public void writeAttributes(Columbus.Lim.Asg.Nodes.Type.TypeFormerPointer node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Lim.Asg.Nodes.Type.TypeFormer)node,composite,false);

  if (!composite) {
    writer.Write(" pointerKind='" + node.PointerKind.ToString() + "'");
  }
}

public void writeAttributes(Columbus.Lim.Asg.Nodes.Type.TypeFormerType node,bool composite, bool bWithParent = true ) {
  writeAttributes((Columbus.Lim.Asg.Nodes.Type.TypeFormer)node,composite,false);

}

        /// <summary>
        /// Writes out the attributes of the SourcePosition node.
        /// </summary>
protected void writeAttributes(SourcePosition compType,bool composite) {
  if (!composite) {
    writer.Write(" realizationLevel='" + compType.RealizationLevel + "'");
  }
  if (!composite) {
    writer.Write(" line='" + compType.Line + "'");
  }
  if (!composite) {
    writer.Write(" column='" + compType.Column + "'");
  }
  if (!composite) {
    writer.Write(" endLine='" + compType.EndLine + "'");
  }
  if (!composite) {
    writer.Write(" endColumn='" + compType.EndColumn + "'");
  }
}

            }

}
