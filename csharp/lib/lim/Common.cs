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
using System.Text;

namespace Columbus.Lim.Asg {

    /// <summary>
    /// Contains general graph algorithms and common functions.
    /// </summary>
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class Common {

        /// <summary>
        /// Decides whether the node is base::Comment or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is base::Comment.</returns>
        public static bool getIsComment(Columbus.Lim.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Lim.Asg.Nodes.Base.Comment);
        }

        /// <summary>
        /// Decides whether the node is base::Component or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is base::Component.</returns>
        public static bool getIsComponent(Columbus.Lim.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Lim.Asg.Nodes.Base.Component);
        }

        /// <summary>
        /// Decides whether the node is base::ControlFlowBlock or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is base::ControlFlowBlock.</returns>
        public static bool getIsControlFlowBlock(Columbus.Lim.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Lim.Asg.Nodes.Base.ControlFlowBlock);
        }

        /// <summary>
        /// Decides whether the node is base::Named or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is base::Named.</returns>
        public static bool getIsNamed(Columbus.Lim.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Lim.Asg.Nodes.Base.Named);
        }

        /// <summary>
        /// Decides whether the node is logical::Attribute or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is logical::Attribute.</returns>
        public static bool getIsAttribute(Columbus.Lim.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Lim.Asg.Nodes.Logical.Attribute);
        }

        /// <summary>
        /// Decides whether the node is logical::AttributeAccess or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is logical::AttributeAccess.</returns>
        public static bool getIsAttributeAccess(Columbus.Lim.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Lim.Asg.Nodes.Logical.AttributeAccess);
        }

        /// <summary>
        /// Decides whether the node is logical::Class or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is logical::Class.</returns>
        public static bool getIsClass(Columbus.Lim.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Lim.Asg.Nodes.Logical.Class);
        }

        /// <summary>
        /// Decides whether the node is logical::ClassGeneric or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is logical::ClassGeneric.</returns>
        public static bool getIsClassGeneric(Columbus.Lim.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Lim.Asg.Nodes.Logical.ClassGeneric);
        }

        /// <summary>
        /// Decides whether the node is logical::ClassGenericInstance or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is logical::ClassGenericInstance.</returns>
        public static bool getIsClassGenericInstance(Columbus.Lim.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Lim.Asg.Nodes.Logical.ClassGenericInstance);
        }

        /// <summary>
        /// Decides whether the node is logical::ClassGenericSpec or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is logical::ClassGenericSpec.</returns>
        public static bool getIsClassGenericSpec(Columbus.Lim.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Lim.Asg.Nodes.Logical.ClassGenericSpec);
        }

        /// <summary>
        /// Decides whether the node is logical::Friendship or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is logical::Friendship.</returns>
        public static bool getIsFriendship(Columbus.Lim.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Lim.Asg.Nodes.Logical.Friendship);
        }

        /// <summary>
        /// Decides whether the node is logical::GenericParameter or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is logical::GenericParameter.</returns>
        public static bool getIsGenericParameter(Columbus.Lim.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Lim.Asg.Nodes.Logical.GenericParameter);
        }

        /// <summary>
        /// Decides whether the node is logical::Member or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is logical::Member.</returns>
        public static bool getIsMember(Columbus.Lim.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Lim.Asg.Nodes.Logical.Member);
        }

        /// <summary>
        /// Decides whether the node is logical::Method or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is logical::Method.</returns>
        public static bool getIsMethod(Columbus.Lim.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Lim.Asg.Nodes.Logical.Method);
        }

        /// <summary>
        /// Decides whether the node is logical::MethodCall or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is logical::MethodCall.</returns>
        public static bool getIsMethodCall(Columbus.Lim.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Lim.Asg.Nodes.Logical.MethodCall);
        }

        /// <summary>
        /// Decides whether the node is logical::MethodGeneric or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is logical::MethodGeneric.</returns>
        public static bool getIsMethodGeneric(Columbus.Lim.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Lim.Asg.Nodes.Logical.MethodGeneric);
        }

        /// <summary>
        /// Decides whether the node is logical::MethodGenericInstance or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is logical::MethodGenericInstance.</returns>
        public static bool getIsMethodGenericInstance(Columbus.Lim.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Lim.Asg.Nodes.Logical.MethodGenericInstance);
        }

        /// <summary>
        /// Decides whether the node is logical::MethodGenericSpec or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is logical::MethodGenericSpec.</returns>
        public static bool getIsMethodGenericSpec(Columbus.Lim.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Lim.Asg.Nodes.Logical.MethodGenericSpec);
        }

        /// <summary>
        /// Decides whether the node is logical::Package or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is logical::Package.</returns>
        public static bool getIsPackage(Columbus.Lim.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Lim.Asg.Nodes.Logical.Package);
        }

        /// <summary>
        /// Decides whether the node is logical::Parameter or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is logical::Parameter.</returns>
        public static bool getIsParameter(Columbus.Lim.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Lim.Asg.Nodes.Logical.Parameter);
        }

        /// <summary>
        /// Decides whether the node is logical::Scope or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is logical::Scope.</returns>
        public static bool getIsScope(Columbus.Lim.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Lim.Asg.Nodes.Logical.Scope);
        }

        /// <summary>
        /// Decides whether the node is physical::FSEntry or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is physical::FSEntry.</returns>
        public static bool getIsFSEntry(Columbus.Lim.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Lim.Asg.Nodes.Physical.FSEntry);
        }

        /// <summary>
        /// Decides whether the node is physical::File or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is physical::File.</returns>
        public static bool getIsFile(Columbus.Lim.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Lim.Asg.Nodes.Physical.File);
        }

        /// <summary>
        /// Decides whether the node is physical::FileSystem or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is physical::FileSystem.</returns>
        public static bool getIsFileSystem(Columbus.Lim.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Lim.Asg.Nodes.Physical.FileSystem);
        }

        /// <summary>
        /// Decides whether the node is physical::Folder or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is physical::Folder.</returns>
        public static bool getIsFolder(Columbus.Lim.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Lim.Asg.Nodes.Physical.Folder);
        }

        /// <summary>
        /// Decides whether the node is type::SimpleType or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is type::SimpleType.</returns>
        public static bool getIsSimpleType(Columbus.Lim.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Lim.Asg.Nodes.Type.SimpleType);
        }

        /// <summary>
        /// Decides whether the node is type::Type or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is type::Type.</returns>
        public static bool getIsType(Columbus.Lim.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Lim.Asg.Nodes.Type.Type);
        }

        /// <summary>
        /// Decides whether the node is type::TypeFormer or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is type::TypeFormer.</returns>
        public static bool getIsTypeFormer(Columbus.Lim.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Lim.Asg.Nodes.Type.TypeFormer);
        }

        /// <summary>
        /// Decides whether the node is type::TypeFormerArray or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is type::TypeFormerArray.</returns>
        public static bool getIsTypeFormerArray(Columbus.Lim.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Lim.Asg.Nodes.Type.TypeFormerArray);
        }

        /// <summary>
        /// Decides whether the node is type::TypeFormerMethod or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is type::TypeFormerMethod.</returns>
        public static bool getIsTypeFormerMethod(Columbus.Lim.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Lim.Asg.Nodes.Type.TypeFormerMethod);
        }

        /// <summary>
        /// Decides whether the node is type::TypeFormerNonType or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is type::TypeFormerNonType.</returns>
        public static bool getIsTypeFormerNonType(Columbus.Lim.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Lim.Asg.Nodes.Type.TypeFormerNonType);
        }

        /// <summary>
        /// Decides whether the node is type::TypeFormerPointer or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is type::TypeFormerPointer.</returns>
        public static bool getIsTypeFormerPointer(Columbus.Lim.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Lim.Asg.Nodes.Type.TypeFormerPointer);
        }

        /// <summary>
        /// Decides whether the node is type::TypeFormerType or not.
        /// </summary>
        /// <param name="node">[in] The node whose kind is examined.</param>
        /// <returns>Returns true if the node is type::TypeFormerType.</returns>
        public static bool getIsTypeFormerType(Columbus.Lim.Asg.Nodes.Base.Base node) {
            return (node is Columbus.Lim.Asg.Nodes.Type.TypeFormerType);
        }

        /// <summary>
        /// Decides whether the 'baseKind' is one of the base kinds (transitive) of 'what'.
        /// </summary>
        /// <param name="what">[in] The examined node kind.</param>
        /// <param name="baseKind">[in] The base node kind.</param>
        /// <returns>Returns true if 'baseKind' is a basekind of 'what'.</returns>
        public static bool getIsBaseClassKind(Types.NodeKind what, Types.NodeKind baseKind) {
            Types.NodeKind type = what;

            while (type != baseKind) {
                switch (type) {
                    case Types.NodeKind.ndkBase:
                        return false;
                    case Types.NodeKind.ndkComment:
                        type = Types.NodeKind.ndkBase;
                        break;
                    case Types.NodeKind.ndkComponent:
                        type = Types.NodeKind.ndkNamed;
                        break;
                    case Types.NodeKind.ndkControlFlowBlock:
                        type = Types.NodeKind.ndkBase;
                        break;
                    case Types.NodeKind.ndkNamed:
                        type = Types.NodeKind.ndkBase;
                        break;
                    case Types.NodeKind.ndkAttribute:
                        type = Types.NodeKind.ndkMember;
                        break;
                    case Types.NodeKind.ndkAttributeAccess:
                        type = Types.NodeKind.ndkBase;
                        break;
                    case Types.NodeKind.ndkClass:
                        type = Types.NodeKind.ndkScope;
                        break;
                    case Types.NodeKind.ndkClassGeneric:
                        type = Types.NodeKind.ndkClass;
                        break;
                    case Types.NodeKind.ndkClassGenericInstance:
                        type = Types.NodeKind.ndkClass;
                        break;
                    case Types.NodeKind.ndkClassGenericSpec:
                        type = Types.NodeKind.ndkClassGeneric;
                        break;
                    case Types.NodeKind.ndkFriendship:
                        type = Types.NodeKind.ndkBase;
                        break;
                    case Types.NodeKind.ndkGenericParameter:
                        type = Types.NodeKind.ndkNamed;
                        break;
                    case Types.NodeKind.ndkMember:
                        type = Types.NodeKind.ndkNamed;
                        break;
                    case Types.NodeKind.ndkMethod:
                        type = Types.NodeKind.ndkScope;
                        break;
                    case Types.NodeKind.ndkMethodCall:
                        type = Types.NodeKind.ndkBase;
                        break;
                    case Types.NodeKind.ndkMethodGeneric:
                        type = Types.NodeKind.ndkMethod;
                        break;
                    case Types.NodeKind.ndkMethodGenericInstance:
                        type = Types.NodeKind.ndkMethod;
                        break;
                    case Types.NodeKind.ndkMethodGenericSpec:
                        type = Types.NodeKind.ndkMethodGeneric;
                        break;
                    case Types.NodeKind.ndkPackage:
                        type = Types.NodeKind.ndkScope;
                        break;
                    case Types.NodeKind.ndkParameter:
                        type = Types.NodeKind.ndkNamed;
                        break;
                    case Types.NodeKind.ndkScope:
                        type = Types.NodeKind.ndkMember;
                        break;
                    case Types.NodeKind.ndkFSEntry:
                        type = Types.NodeKind.ndkNamed;
                        break;
                    case Types.NodeKind.ndkFile:
                        type = Types.NodeKind.ndkFSEntry;
                        break;
                    case Types.NodeKind.ndkFileSystem:
                        type = Types.NodeKind.ndkNamed;
                        break;
                    case Types.NodeKind.ndkFolder:
                        type = Types.NodeKind.ndkFSEntry;
                        break;
                    case Types.NodeKind.ndkSimpleType:
                        type = Types.NodeKind.ndkBase;
                        break;
                    case Types.NodeKind.ndkType:
                        type = Types.NodeKind.ndkBase;
                        break;
                    case Types.NodeKind.ndkTypeFormer:
                        type = Types.NodeKind.ndkBase;
                        break;
                    case Types.NodeKind.ndkTypeFormerArray:
                        type = Types.NodeKind.ndkTypeFormer;
                        break;
                    case Types.NodeKind.ndkTypeFormerMethod:
                        type = Types.NodeKind.ndkTypeFormer;
                        break;
                    case Types.NodeKind.ndkTypeFormerNonType:
                        type = Types.NodeKind.ndkTypeFormer;
                        break;
                    case Types.NodeKind.ndkTypeFormerPointer:
                        type = Types.NodeKind.ndkTypeFormer;
                        break;
                    case Types.NodeKind.ndkTypeFormerType:
                        type = Types.NodeKind.ndkTypeFormer;
                        break;
                }
            }

            return true;
        }

        /// <summary>
        /// Decides whether the node is compiste or not.
        /// </summary>
        /// <param name="node">[in] The node which is being examined.</param>
        /// <returns>Returns true if the node is composite.</returns>
        public static bool getIsComposite(Columbus.Lim.Asg.Nodes.Base.Base node) {
            return !getIsNotComposite(node);
        }

        /// <summary>
        /// Decides whether the node is compiste or not.
        /// </summary>
        /// <param name="node">[in] The node which is being examined.</param>
        /// <returns>Returns true if the node is not composite.</returns>
        public static bool getIsNotComposite(Columbus.Lim.Asg.Nodes.Base.Base node) {
            Types.NodeKind ndk = node.NodeKind;
            return
                ndk == Types.NodeKind.ndkBase ||
                ndk == Types.NodeKind.ndkComment ||
                ndk == Types.NodeKind.ndkControlFlowBlock ||
                ndk == Types.NodeKind.ndkNamed ||
                ndk == Types.NodeKind.ndkComponent ||
                ndk == Types.NodeKind.ndkGenericParameter ||
                ndk == Types.NodeKind.ndkMember ||
                ndk == Types.NodeKind.ndkAttribute ||
                ndk == Types.NodeKind.ndkScope ||
                ndk == Types.NodeKind.ndkClass ||
                ndk == Types.NodeKind.ndkClassGenericInstance ||
                ndk == Types.NodeKind.ndkPackage ||
                ndk == Types.NodeKind.ndkParameter ||
                ndk == Types.NodeKind.ndkFSEntry ||
                ndk == Types.NodeKind.ndkFile ||
                ndk == Types.NodeKind.ndkAttributeAccess ||
                ndk == Types.NodeKind.ndkFriendship ||
                ndk == Types.NodeKind.ndkMethodCall ||
                ndk == Types.NodeKind.ndkSimpleType ||
                ndk == Types.NodeKind.ndkType ||
                ndk == Types.NodeKind.ndkTypeFormer ||
                ndk == Types.NodeKind.ndkTypeFormerArray ||
                ndk == Types.NodeKind.ndkTypeFormerMethod ||
                ndk == Types.NodeKind.ndkTypeFormerNonType ||
                ndk == Types.NodeKind.ndkTypeFormerPointer ||
                ndk == Types.NodeKind.ndkTypeFormerType;
        }

        /// <summary>
        /// Returns true if the node exists and is not filtered out.
        /// </summary>
        /// <param name="id">[in] The examined node ID.</param>
        /// <returns>True if the node exists and is not filtered out.</returns>
        public static bool getIsValid(uint id) {
            return id > 1;
        }

public static bool getIsAPSpecNode(Columbus.Lim.Asg.Nodes.Base.Base node) {
  Types.NodeKind ndk = node.NodeKind;
  return
    ndk == Types.NodeKind.ndkComment ||
    ndk == Types.NodeKind.ndkComponent ||
    ndk == Types.NodeKind.ndkAttributeAccess ||
    ndk == Types.NodeKind.ndkFriendship ||
    ndk == Types.NodeKind.ndkMethodCall ||
    ndk == Types.NodeKind.ndkFileSystem ||
    ndk == Types.NodeKind.ndkSimpleType ||
    ndk == Types.NodeKind.ndkType ||
    ndk == Types.NodeKind.ndkTypeFormerArray ||
    ndk == Types.NodeKind.ndkTypeFormerMethod ||
    ndk == Types.NodeKind.ndkTypeFormerNonType ||
    ndk == Types.NodeKind.ndkTypeFormerPointer ||
    ndk == Types.NodeKind.ndkTypeFormerType;
}

﻿	public static string GetFullPath(Nodes.Physical.FSEntry node, char separator = '\\')
    {
            string str = node.Name;

            Nodes.Base.Base n = node.Factory.getRef( node.Parent );
            while (n != null)
            {
                if (!getIsFSEntry(n))
                {
                    break;
                }
                string name = (n as Nodes.Physical.FSEntry).Name;
                if (name == "/" || name == "\\")
                {
                    str = name + str;
                }
                else
                {
                    str = name + separator + str;
                }
                n = n.Factory.getRef(n.Parent);
            }

            return str;
    }    }

}
