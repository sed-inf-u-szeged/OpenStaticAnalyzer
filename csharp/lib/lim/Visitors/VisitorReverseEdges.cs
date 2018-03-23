/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2017 Department of Software Engineering - University of Szeged
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
using System.Linq;
using System.Collections.Generic;
using System.Text;


namespace Columbus.Lim.Asg.Visitors {

    /// <summary>
    /// Collects the inverse relation of any "one way" defined edges.
    /// </summary>
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class VisitorReverseEdges : VisitorAbstractNodes {

        private ReverseEdges revEdges;
        public VisitorReverseEdges(ReverseEdges reverseEdges) : base() {
            revEdges = reverseEdges;
        }

        public override void visit(Columbus.Lim.Asg.Nodes.Base.Base node, bool callVirtualBase) {
          uint id = node.Id;
          if (revEdges.reContainer[(int)id] == null) {
            revEdges.reContainer[(int)id] = new Dictionary<Types.EdgeKind, LinkedList<uint>>();
          }
        }

        public override void visitComponent_Contains(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkComponent_Contains);
        }

        public override void visitComponent_HasFiles(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkComponent_HasFiles);
        }

        public override void visitControlFlowBlock_Calls(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkControlFlowBlock_Calls);
        }

        public override void visitControlFlowBlock_Pred(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkControlFlowBlock_Pred);
        }

        public override void visitNamed_DependsOn(uint begin, uint end, string ac) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkNamed_DependsOn);
        }

        public override void visitAttribute_Calls(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkAttribute_Calls);
        }

        public override void visitAttribute_HasType(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkAttribute_HasType);
        }

        public override void visitAttributeAccess_Attribute(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkAttributeAccess_Attribute);
        }

        public override void visitClass_GrantsFriendship(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkClass_GrantsFriendship);
        }

        public override void visitClass_IsSubclass(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkClass_IsSubclass);
        }

        public override void visitClassGeneric_HasGenericParameter(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkClassGeneric_HasGenericParameter);
        }

        public override void visitClassGenericInstance_HasArguments(uint begin, uint end, Types.TypeArgumentConstraintKind ac) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkClassGenericInstance_HasArguments);
        }

        public override void visitClassGenericSpec_HasArguments(uint begin, uint end, Types.TypeArgumentConstraintKind ac) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkClassGenericSpec_HasArguments);
        }

        public override void visitClassGenericSpec_Specialize(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkClassGenericSpec_Specialize);
        }

        public override void visitFriendship_Friend(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkFriendship_Friend);
        }

        public override void visitGenericParameter_HasParameterConstraint(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkGenericParameter_HasParameterConstraint);
        }

        public override void visitMember_Aggregated(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkMember_Aggregated);
        }

        public override void visitMember_BelongsTo(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkMember_BelongsTo);
        }

        public override void visitMember_CompilationUnit(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkMember_CompilationUnit);
        }

        public override void visitMember_Declares(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkMember_Declares);
        }

        public override void visitMember_HasComment(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkMember_HasComment);
        }

        public override void visitMember_Instance(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkMember_Instance);
        }

        public override void visitMember_IsContainedIn(uint begin, uint end, SourcePosition ac) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkMember_IsContainedIn);
        }

        public override void visitMember_LanguageVariant(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkMember_LanguageVariant);
        }

        public override void visitMember_Uses(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkMember_Uses);
        }

        public override void visitMember_Variant(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkMember_Variant);
        }

        public override void visitMethod_AccessesAttribute(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkMethod_AccessesAttribute);
        }

        public override void visitMethod_Calls(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkMethod_Calls);
        }

        public override void visitMethod_CanThrow(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkMethod_CanThrow);
        }

        public override void visitMethod_HasControlFlowBlock(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkMethod_HasControlFlowBlock);
        }

        public override void visitMethod_HasParameter(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkMethod_HasParameter);
        }

        public override void visitMethod_Instantiates(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkMethod_Instantiates);
        }

        public override void visitMethod_Returns(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkMethod_Returns);
        }

        public override void visitMethod_Throws(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkMethod_Throws);
        }

        public override void visitMethodCall_Method(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkMethodCall_Method);
        }

        public override void visitMethodGeneric_HasGenericParameter(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkMethodGeneric_HasGenericParameter);
        }

        public override void visitMethodGenericInstance_HasArguments(uint begin, uint end, Types.TypeArgumentConstraintKind ac) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkMethodGenericInstance_HasArguments);
        }

        public override void visitMethodGenericSpec_HasArguments(uint begin, uint end, Types.TypeArgumentConstraintKind ac) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkMethodGenericSpec_HasArguments);
        }

        public override void visitMethodGenericSpec_Specialize(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkMethodGenericSpec_Specialize);
        }

        public override void visitParameter_HasType(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkParameter_HasType);
        }

        public override void visitScope_HasMember(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkScope_HasMember);
        }

        public override void visitFile_HasComment(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkFile_HasComment);
        }

        public override void visitFile_Includes(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkFile_Includes);
        }

        public override void visitFileSystem_HasFSEntry(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkFileSystem_HasFSEntry);
        }

        public override void visitFolder_Contains(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkFolder_Contains);
        }

        public override void visitType_HasTypeFormer(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkType_HasTypeFormer);
        }

        public override void visitTypeFormerMethod_HasParameterType(uint begin, uint end, Types.ParameterKind ac) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkTypeFormerMethod_HasParameterType);
        }

        public override void visitTypeFormerMethod_HasReturnType(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkTypeFormerMethod_HasReturnType);
        }

        public override void visitTypeFormerType_RefersTo(uint begin, uint end) {
          revEdges.insertEdge(end, begin, Types.EdgeKind.edkTypeFormerType_RefersTo);
        }

        }
}