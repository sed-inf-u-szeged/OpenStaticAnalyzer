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
    /// Contains some predefined types.
    /// </summary>
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class Types {

        /// <summary>
        /// Validation kind for the ASG.
        /// </summary>
        [Flags]
        public enum AsgValidationKind {

            /// <summary>The ASG is valid.</summary>
            avkValid = 1,

            /// <summary>The ASG does not contain the FileType information.</summary>
            avkMissingFileType = 2,

            /// <summary>The ASG contains wrong FileType information.</summary>
            avkWrongFileType = 4,

            /// <summary>The ASG does not contain the ApiVersion information.</summary>
            avkMissingApiVersion = 8,

            /// <summary>The ASG contains wrong ApiVersion information.</summary>
            avkWrongApiVersion = 16,

            /// <summary>The ASG does not contain the BinaryVersion information.</summary>
            avkMissingBinaryVersion = 32,

            /// <summary>The ASG contains wrong BinaryVersion information.</summary>
            avkWrongBinaryVersion = 64,

            /// <summary>An unknow error occured when reading the ASG.</summary>
            avkUnknownError = 128

        }

        /// <summary>
        /// Enumeration for the AccessibilityKind kind.
        /// </summary>
        public enum AccessibilityKind {

            /// <summary>Value if the AccessibilityKind is Internal.</summary>
            ackInternal,

            /// <summary>Value if the AccessibilityKind is InternalProtected.</summary>
            ackInternalProtected,

            /// <summary>Value if the AccessibilityKind is None.</summary>
            ackNone,

            /// <summary>Value if the AccessibilityKind is PackagePrivate.</summary>
            ackPackagePrivate,

            /// <summary>Value if the AccessibilityKind is Private.</summary>
            ackPrivate,

            /// <summary>Value if the AccessibilityKind is Protected.</summary>
            ackProtected,

            /// <summary>Value if the AccessibilityKind is ProtectedInternal.</summary>
            ackProtectedInternal,

            /// <summary>Value if the AccessibilityKind is Public.</summary>
            ackPublic

        }

        /// <summary>
        /// Enumeration for the AnalysisTimeKind kind.
        /// </summary>
        public enum AnalysisTimeKind {

            /// <summary>Value if the AnalysisTimeKind is Now.</summary>
            atkNow,

            /// <summary>Value if the AnalysisTimeKind is Before.</summary>
            atkBefore,

            /// <summary>Value if the AnalysisTimeKind is Never.</summary>
            atkNever

        }

        /// <summary>
        /// Enumeration for the ClassKind kind.
        /// </summary>
        public enum ClassKind {

            /// <summary>Value if the ClassKind is Annotation.</summary>
            clkAnnotation,

            /// <summary>Value if the ClassKind is Class.</summary>
            clkClass,

            /// <summary>Value if the ClassKind is Delegate.</summary>
            clkDelegate,

            /// <summary>Value if the ClassKind is Enum.</summary>
            clkEnum,

            /// <summary>Value if the ClassKind is Interface.</summary>
            clkInterface,

            /// <summary>Value if the ClassKind is Struct.</summary>
            clkStruct,

            /// <summary>Value if the ClassKind is Union.</summary>
            clkUnion

        }

        /// <summary>
        /// Enumeration for the GenericParameterKind kind.
        /// </summary>
        public enum GenericParameterKind {

            /// <summary>Value if the GenericParameterKind is Constraint.</summary>
            gpkConstraint,

            /// <summary>Value if the GenericParameterKind is NonType.</summary>
            gpkNonType,

            /// <summary>Value if the GenericParameterKind is NonTypePack.</summary>
            gpkNonTypePack,

            /// <summary>Value if the GenericParameterKind is Template.</summary>
            gpkTemplate,

            /// <summary>Value if the GenericParameterKind is TemplatePack.</summary>
            gpkTemplatePack,

            /// <summary>Value if the GenericParameterKind is Type.</summary>
            gpkType,

            /// <summary>Value if the GenericParameterKind is TypePack.</summary>
            gpkTypePack

        }

        /// <summary>
        /// Enumeration for the LanguageKind kind.
        /// </summary>
        public enum LanguageKind {

            /// <summary>Value if the LanguageKind is NotSet.</summary>
            lnkNotSet,

            /// <summary>Value if the LanguageKind is C.</summary>
            lnkC,

            /// <summary>Value if the LanguageKind is Cpp.</summary>
            lnkCpp,

            /// <summary>Value if the LanguageKind is Java.</summary>
            lnkJava,

            /// <summary>Value if the LanguageKind is Csharp.</summary>
            lnkCsharp,

            /// <summary>Value if the LanguageKind is Sql.</summary>
            lnkSql,

            /// <summary>Value if the LanguageKind is Magic.</summary>
            lnkMagic,

            /// <summary>Value if the LanguageKind is Rpg.</summary>
            lnkRpg,

            /// <summary>Value if the LanguageKind is Python.</summary>
            lnkPython,

            /// <summary>Value if the LanguageKind is Javascript.</summary>
            lnkJavascript

        }

        /// <summary>
        /// Enumeration for the MethodKind kind.
        /// </summary>
        public enum MethodKind {

            /// <summary>Value if the MethodKind is Add.</summary>
            mekAdd,

            /// <summary>Value if the MethodKind is Constructor.</summary>
            mekConstructor,

            /// <summary>Value if the MethodKind is Destructor.</summary>
            mekDestructor,

            /// <summary>Value if the MethodKind is Get.</summary>
            mekGet,

            /// <summary>Value if the MethodKind is Menu.</summary>
            mekMenu,

            /// <summary>Value if the MethodKind is Normal.</summary>
            mekNormal,

            /// <summary>Value if the MethodKind is Operator.</summary>
            mekOperator,

            /// <summary>Value if the MethodKind is Remove.</summary>
            mekRemove,

            /// <summary>Value if the MethodKind is Set.</summary>
            mekSet,

            /// <summary>Value if the MethodKind is Subroutine.</summary>
            mekSubroutine

        }

        /// <summary>
        /// Enumeration for the PackageKind kind.
        /// </summary>
        public enum PackageKind {

            /// <summary>Value if the PackageKind is Package.</summary>
            pkPackage,

            /// <summary>Value if the PackageKind is Module.</summary>
            pkModule

        }

        /// <summary>
        /// Enumeration for the ParameterKind kind.
        /// </summary>
        public enum ParameterKind {

            /// <summary>Value if the ParameterKind is In.</summary>
            pmkIn,

            /// <summary>Value if the ParameterKind is InOut.</summary>
            pmkInOut,

            /// <summary>Value if the ParameterKind is Out.</summary>
            pmkOut

        }

        /// <summary>
        /// Enumeration for the PointerKind kind.
        /// </summary>
        public enum PointerKind {

            /// <summary>Value if the PointerKind is Pointer.</summary>
            ptkPointer,

            /// <summary>Value if the PointerKind is Reference.</summary>
            ptkReference

        }

        /// <summary>
        /// Enumeration for the RealizationLevel kind.
        /// </summary>
        public enum RealizationLevel {

            /// <summary>Value if the RealizationLevel is Declares.</summary>
            relDeclares,

            /// <summary>Value if the RealizationLevel is Defines.</summary>
            relDefines

        }

        /// <summary>
        /// Enumeration for the SimpleTypeKind kind.
        /// </summary>
        public enum SimpleTypeKind {

            /// <summary>Value if the SimpleTypeKind is Boolean.</summary>
            stkBoolean,

            /// <summary>Value if the SimpleTypeKind is Byte.</summary>
            stkByte,

            /// <summary>Value if the SimpleTypeKind is Character.</summary>
            stkCharacter,

            /// <summary>Value if the SimpleTypeKind is Decimal.</summary>
            stkDecimal,

            /// <summary>Value if the SimpleTypeKind is Double.</summary>
            stkDouble,

            /// <summary>Value if the SimpleTypeKind is Float.</summary>
            stkFloat,

            /// <summary>Value if the SimpleTypeKind is Integer.</summary>
            stkInteger,

            /// <summary>Value if the SimpleTypeKind is Long.</summary>
            stkLong,

            /// <summary>Value if the SimpleTypeKind is Object.</summary>
            stkObject,

            /// <summary>Value if the SimpleTypeKind is Short.</summary>
            stkShort,

            /// <summary>Value if the SimpleTypeKind is Single.</summary>
            stkSingle,

            /// <summary>Value if the SimpleTypeKind is String.</summary>
            stkString,

            /// <summary>Value if the SimpleTypeKind is Unicode.</summary>
            stkUnicode,

            /// <summary>Value if the SimpleTypeKind is Unknown.</summary>
            stkUnknown,

            /// <summary>Value if the SimpleTypeKind is UnsignedCharacter.</summary>
            stkUnsignedCharacter,

            /// <summary>Value if the SimpleTypeKind is UnsignedInteger.</summary>
            stkUnsignedInteger,

            /// <summary>Value if the SimpleTypeKind is UnsignedLong.</summary>
            stkUnsignedLong,

            /// <summary>Value if the SimpleTypeKind is UnsignedShort.</summary>
            stkUnsignedShort,

            /// <summary>Value if the SimpleTypeKind is Void.</summary>
            stkVoid

        }

        /// <summary>
        /// Enumeration for the TypeArgumentConstraintKind kind.
        /// </summary>
        public enum TypeArgumentConstraintKind {

            /// <summary>Value if the TypeArgumentConstraintKind is LowerBounded.</summary>
            tackLowerBounded,

            /// <summary>Value if the TypeArgumentConstraintKind is None.</summary>
            tackNone,

            /// <summary>Value if the TypeArgumentConstraintKind is Unbounded.</summary>
            tackUnbounded,

            /// <summary>Value if the TypeArgumentConstraintKind is UpperBounded.</summary>
            tackUpperBounded

        }

        /// <summary>
        /// Enumeration for the NodeKind kind.
        /// </summary>
        public enum NodeKind {

            /// <summary>Value if the NodeKind is Base.</summary>
            ndkBase,

            /// <summary>Value if the NodeKind is Comment.</summary>
            ndkComment,

            /// <summary>Value if the NodeKind is Component.</summary>
            ndkComponent,

            /// <summary>Value if the NodeKind is ControlFlowBlock.</summary>
            ndkControlFlowBlock,

            /// <summary>Value if the NodeKind is Named.</summary>
            ndkNamed,

            /// <summary>Value if the NodeKind is Attribute.</summary>
            ndkAttribute,

            /// <summary>Value if the NodeKind is AttributeAccess.</summary>
            ndkAttributeAccess,

            /// <summary>Value if the NodeKind is Class.</summary>
            ndkClass,

            /// <summary>Value if the NodeKind is ClassGeneric.</summary>
            ndkClassGeneric,

            /// <summary>Value if the NodeKind is ClassGenericInstance.</summary>
            ndkClassGenericInstance,

            /// <summary>Value if the NodeKind is ClassGenericSpec.</summary>
            ndkClassGenericSpec,

            /// <summary>Value if the NodeKind is Friendship.</summary>
            ndkFriendship,

            /// <summary>Value if the NodeKind is GenericParameter.</summary>
            ndkGenericParameter,

            /// <summary>Value if the NodeKind is Member.</summary>
            ndkMember,

            /// <summary>Value if the NodeKind is Method.</summary>
            ndkMethod,

            /// <summary>Value if the NodeKind is MethodCall.</summary>
            ndkMethodCall,

            /// <summary>Value if the NodeKind is MethodGeneric.</summary>
            ndkMethodGeneric,

            /// <summary>Value if the NodeKind is MethodGenericInstance.</summary>
            ndkMethodGenericInstance,

            /// <summary>Value if the NodeKind is MethodGenericSpec.</summary>
            ndkMethodGenericSpec,

            /// <summary>Value if the NodeKind is Package.</summary>
            ndkPackage,

            /// <summary>Value if the NodeKind is Parameter.</summary>
            ndkParameter,

            /// <summary>Value if the NodeKind is Scope.</summary>
            ndkScope,

            /// <summary>Value if the NodeKind is FSEntry.</summary>
            ndkFSEntry,

            /// <summary>Value if the NodeKind is File.</summary>
            ndkFile,

            /// <summary>Value if the NodeKind is FileSystem.</summary>
            ndkFileSystem,

            /// <summary>Value if the NodeKind is Folder.</summary>
            ndkFolder,

            /// <summary>Value if the NodeKind is SimpleType.</summary>
            ndkSimpleType,

            /// <summary>Value if the NodeKind is Type.</summary>
            ndkType,

            /// <summary>Value if the NodeKind is TypeFormer.</summary>
            ndkTypeFormer,

            /// <summary>Value if the NodeKind is TypeFormerArray.</summary>
            ndkTypeFormerArray,

            /// <summary>Value if the NodeKind is TypeFormerMethod.</summary>
            ndkTypeFormerMethod,

            /// <summary>Value if the NodeKind is TypeFormerNonType.</summary>
            ndkTypeFormerNonType,

            /// <summary>Value if the NodeKind is TypeFormerPointer.</summary>
            ndkTypeFormerPointer,

            /// <summary>Value if the NodeKind is TypeFormerType.</summary>
            ndkTypeFormerType

        }

        /// <summary>
        /// Enumeration for the EdgeKind kind.
        /// </summary>
        public enum EdgeKind {

            /// <summary>Value if the EdgeKind is Component_Contains.</summary>
            edkComponent_Contains,

            /// <summary>Value if the EdgeKind is Component_HasFiles.</summary>
            edkComponent_HasFiles,

            /// <summary>Value if the EdgeKind is ControlFlowBlock_Calls.</summary>
            edkControlFlowBlock_Calls,

            /// <summary>Value if the EdgeKind is ControlFlowBlock_Pred.</summary>
            edkControlFlowBlock_Pred,

            /// <summary>Value if the EdgeKind is Named_DependsOn.</summary>
            edkNamed_DependsOn,

            /// <summary>Value if the EdgeKind is Attribute_Calls.</summary>
            edkAttribute_Calls,

            /// <summary>Value if the EdgeKind is Attribute_HasType.</summary>
            edkAttribute_HasType,

            /// <summary>Value if the EdgeKind is AttributeAccess_Attribute.</summary>
            edkAttributeAccess_Attribute,

            /// <summary>Value if the EdgeKind is Class_GrantsFriendship.</summary>
            edkClass_GrantsFriendship,

            /// <summary>Value if the EdgeKind is Class_IsSubclass.</summary>
            edkClass_IsSubclass,

            /// <summary>Value if the EdgeKind is ClassGeneric_HasGenericParameter.</summary>
            edkClassGeneric_HasGenericParameter,

            /// <summary>Value if the EdgeKind is ClassGenericInstance_HasArguments.</summary>
            edkClassGenericInstance_HasArguments,

            /// <summary>Value if the EdgeKind is ClassGenericSpec_HasArguments.</summary>
            edkClassGenericSpec_HasArguments,

            /// <summary>Value if the EdgeKind is ClassGenericSpec_Specialize.</summary>
            edkClassGenericSpec_Specialize,

            /// <summary>Value if the EdgeKind is Friendship_Friend.</summary>
            edkFriendship_Friend,

            /// <summary>Value if the EdgeKind is GenericParameter_HasParameterConstraint.</summary>
            edkGenericParameter_HasParameterConstraint,

            /// <summary>Value if the EdgeKind is Member_Aggregated.</summary>
            edkMember_Aggregated,

            /// <summary>Value if the EdgeKind is Member_BelongsTo.</summary>
            edkMember_BelongsTo,

            /// <summary>Value if the EdgeKind is Member_CompilationUnit.</summary>
            edkMember_CompilationUnit,

            /// <summary>Value if the EdgeKind is Member_Declares.</summary>
            edkMember_Declares,

            /// <summary>Value if the EdgeKind is Member_HasComment.</summary>
            edkMember_HasComment,

            /// <summary>Value if the EdgeKind is Member_Instance.</summary>
            edkMember_Instance,

            /// <summary>Value if the EdgeKind is Member_IsContainedIn.</summary>
            edkMember_IsContainedIn,

            /// <summary>Value if the EdgeKind is Member_LanguageVariant.</summary>
            edkMember_LanguageVariant,

            /// <summary>Value if the EdgeKind is Member_Uses.</summary>
            edkMember_Uses,

            /// <summary>Value if the EdgeKind is Member_Variant.</summary>
            edkMember_Variant,

            /// <summary>Value if the EdgeKind is Method_AccessesAttribute.</summary>
            edkMethod_AccessesAttribute,

            /// <summary>Value if the EdgeKind is Method_Calls.</summary>
            edkMethod_Calls,

            /// <summary>Value if the EdgeKind is Method_CanThrow.</summary>
            edkMethod_CanThrow,

            /// <summary>Value if the EdgeKind is Method_HasControlFlowBlock.</summary>
            edkMethod_HasControlFlowBlock,

            /// <summary>Value if the EdgeKind is Method_HasParameter.</summary>
            edkMethod_HasParameter,

            /// <summary>Value if the EdgeKind is Method_Instantiates.</summary>
            edkMethod_Instantiates,

            /// <summary>Value if the EdgeKind is Method_Returns.</summary>
            edkMethod_Returns,

            /// <summary>Value if the EdgeKind is Method_Throws.</summary>
            edkMethod_Throws,

            /// <summary>Value if the EdgeKind is MethodCall_Method.</summary>
            edkMethodCall_Method,

            /// <summary>Value if the EdgeKind is MethodGeneric_HasGenericParameter.</summary>
            edkMethodGeneric_HasGenericParameter,

            /// <summary>Value if the EdgeKind is MethodGenericInstance_HasArguments.</summary>
            edkMethodGenericInstance_HasArguments,

            /// <summary>Value if the EdgeKind is MethodGenericSpec_HasArguments.</summary>
            edkMethodGenericSpec_HasArguments,

            /// <summary>Value if the EdgeKind is MethodGenericSpec_Specialize.</summary>
            edkMethodGenericSpec_Specialize,

            /// <summary>Value if the EdgeKind is Parameter_HasType.</summary>
            edkParameter_HasType,

            /// <summary>Value if the EdgeKind is Scope_HasMember.</summary>
            edkScope_HasMember,

            /// <summary>Value if the EdgeKind is File_HasComment.</summary>
            edkFile_HasComment,

            /// <summary>Value if the EdgeKind is File_Includes.</summary>
            edkFile_Includes,

            /// <summary>Value if the EdgeKind is FileSystem_HasFSEntry.</summary>
            edkFileSystem_HasFSEntry,

            /// <summary>Value if the EdgeKind is Folder_Contains.</summary>
            edkFolder_Contains,

            /// <summary>Value if the EdgeKind is Type_HasTypeFormer.</summary>
            edkType_HasTypeFormer,

            /// <summary>Value if the EdgeKind is TypeFormerMethod_HasParameterType.</summary>
            edkTypeFormerMethod_HasParameterType,

            /// <summary>Value if the EdgeKind is TypeFormerMethod_HasReturnType.</summary>
            edkTypeFormerMethod_HasReturnType,

            /// <summary>Value if the EdgeKind is TypeFormerType_RefersTo.</summary>
            edkTypeFormerType_RefersTo

        }

    }

}
