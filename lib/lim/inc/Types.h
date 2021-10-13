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

#ifndef _LIM_TYPES_H_
#define _LIM_TYPES_H_

/**
* \file Types.h
* \brief Contains declaration of internal types.
*/

namespace columbus { namespace lim { namespace asg {
  enum AccessibilityKind {
    ackInternal,
    ackInternalProtected,
    ackNone,
    ackPackagePrivate,
    ackPrivate,
    ackProtected,
    ackProtectedInternal,
    ackPublic,
    ackLAST
  };

  enum AnalysisTimeKind {
    atkNow,
    atkBefore,
    atkNever,
    atkLAST
  };

  enum ClassKind {
    clkAnnotation,
    clkCategory,
    clkClass,
    clkDelegate,
    clkEnum,
    clkExtension,
    clkInterface,
    clkProtocol,
    clkStruct,
    clkUnion,
    clkLAST
  };

  enum GenericParameterKind {
    gpkConstraint,
    gpkNonType,
    gpkNonTypePack,
    gpkTemplate,
    gpkTemplatePack,
    gpkType,
    gpkTypePack,
    gpkLAST
  };

  enum LanguageKind {
    lnkNotSet,
    lnkC,
    lnkCpp,
    lnkJava,
    lnkCsharp,
    lnkSql,
    lnkMagic,
    lnkRpg,
    lnkPython,
    lnkJavaScript,
    lnkLAST
  };

  enum MethodKind {
    mekAdd,
    mekConstructor,
    mekDestructor,
    mekGet,
    mekMenu,
    mekNormal,
    mekOperator,
    mekRemove,
    mekSet,
    mekSubroutine,
    mekLAST
  };

  enum PackageKind {
    pkPackage,
    pkModule,
    pkLAST
  };

  enum ParameterKind {
    pmkIn,
    pmkInOut,
    pmkOut,
    pmkLAST
  };

  enum PointerKind {
    ptkPointer,
    ptkReference,
    ptkLAST
  };

  enum RealizationLevel {
    relDeclares,
    relDefines,
    relLAST
  };

  enum SimpleTypeKind {
    stkBoolean,
    stkByte,
    stkCharacter,
    stkDecimal,
    stkDouble,
    stkFloat,
    stkInteger,
    stkLong,
    stkObject,
    stkShort,
    stkSingle,
    stkString,
    stkUnicode,
    stkUnknown,
    stkUnsignedCharacter,
    stkUnsignedInteger,
    stkUnsignedLong,
    stkUnsignedShort,
    stkVoid,
    stkLAST
  };

  enum TypeArgumentConstraintKind {
    tackLowerBounded,
    tackNone,
    tackUnbounded,
    tackUpperBounded,
    tackLAST
  };

  enum NodeKind {
    ndkBase,
    ndkComment,
    ndkComponent,
    ndkControlFlowBlock,
    ndkNamed,
    ndkAttribute,
    ndkAttributeAccess,
    ndkClass,
    ndkClassGeneric,
    ndkClassGenericInstance,
    ndkClassGenericSpec,
    ndkFriendship,
    ndkGenericParameter,
    ndkMember,
    ndkMethod,
    ndkMethodCall,
    ndkMethodGeneric,
    ndkMethodGenericInstance,
    ndkMethodGenericSpec,
    ndkPackage,
    ndkParameter,
    ndkScope,
    ndkFSEntry,
    ndkFile,
    ndkFileSystem,
    ndkFolder,
    ndkSimpleType,
    ndkType,
    ndkTypeFormer,
    ndkTypeFormerArray,
    ndkTypeFormerMethod,
    ndkTypeFormerNonType,
    ndkTypeFormerPointer,
    ndkTypeFormerType,
    ndkLAST
  };

  enum EdgeKind {
    edkComponent_CompilationUnit,
    edkComponent_Contains,
    edkComponent_HasFiles,
    edkControlFlowBlock_Calls,
    edkControlFlowBlock_Pred,
    edkNamed_DependsOn,
    edkAttribute_Calls,
    edkAttribute_HasType,
    edkAttributeAccess_Attribute,
    edkClass_Extends,
    edkClass_GrantsFriendship,
    edkClass_IsSubclass,
    edkClassGeneric_HasGenericParameter,
    edkClassGenericInstance_HasArguments,
    edkClassGenericSpec_HasArguments,
    edkClassGenericSpec_Specialize,
    edkFriendship_Friend,
    edkGenericParameter_HasParameterConstraint,
    edkMember_Aggregated,
    edkMember_BelongsTo,
    edkMember_CompilationUnit,
    edkMember_Declares,
    edkMember_HasComment,
    edkMember_Instance,
    edkMember_IsContainedIn,
    edkMember_LanguageVariant,
    edkMember_Uses,
    edkMember_Variant,
    edkMethod_AccessesAttribute,
    edkMethod_Calls,
    edkMethod_CanThrow,
    edkMethod_HasControlFlowBlock,
    edkMethod_HasParameter,
    edkMethod_Instantiates,
    edkMethod_Returns,
    edkMethod_Throws,
    edkMethodCall_Method,
    edkMethodGeneric_HasGenericParameter,
    edkMethodGenericInstance_HasArguments,
    edkMethodGenericSpec_HasArguments,
    edkMethodGenericSpec_Specialize,
    edkParameter_HasType,
    edkScope_HasMember,
    edkFile_HasComment,
    edkFile_Includes,
    edkFileSystem_HasFSEntry,
    edkFolder_Contains,
    edkType_HasTypeFormer,
    edkTypeFormerMethod_HasParameterType,
    edkTypeFormerMethod_HasReturnType,
    edkTypeFormerType_RefersTo,
    edkLAST
  };

  /** \brief Association class types. */
  enum AssocClassType {
    acNone,
    acString,
    acTypeArgumentConstraintKind,
    acSourcePosition,
    acParameterKind
  };


  /**
  * \brief The possible languages the lim can distinguish.
  */
  enum Language {
    limLangOther,
    limLangC,
    limLangCpp,
    limLangJava,
    limLangCsharp,
    limLangFsql,
    limLangPython,
    limLangRpg,
    limLangJavaScript,
  };

  /**
  * \brief The possible link kinds of ClassDiagram.
  */
  enum ClassDiagramLinkKind {
    cdlUnknown,         ///< \brief ismeretlen kapcsolat
    cdlAssoc,           ///< \brief iranyitatlan asszociacio
    cdlAssocD,          ///< \brief iranyitott asszociacio
    cdlAggregatedBy,    ///< \brief aggregalo osztaly fele
    cdlAggregates,      ///< \brief aggregalt osztaly fele
    cdlComposedBy,      ///< \brief tartalmazo osztaly fele
    cdlComposes,        ///< \brief tartalmazott osztaly fele
    cdlParent,          ///< \brief ososztaly fele
    cdlChild,           ///< \brief gyerekosztaly fele
    cdlRealizedBy,      ///< \brief realizalo osztaly fele
    cdlRealizes,        ///< \brief realizalt osztaly fele
    cdlAOwnedBy,        ///< \brief attributumot tartalmazo scope fele
    cdlAOwns,           ///< \brief tartalmazott attributum fele
    cdlCOwnedBy,        ///< \brief osztalyt tartalmazo scope fele
    cdlCOwns,           ///< \brief tartalmazott osztaly fele
    cdlMOwnedBy,        ///< \brief metodust tartalmazo scope fele
    cdlMOwns,           ///< \brief tartalmazott metodus fele
    cdlPOwnedBy,        ///< \brief tartalmazo csomag fele
    cdlPOwns,           ///< \brief tartalmazott csomag fele
    cdlXOwns,           ///< \brief meta-el
    cdlHasType          ///< \brief tipus fele (attrubutum: tipus, metodus: visszateresi ertek)
  };

  /**
  * \brief The possible multyplicities of ClassDiagram.
  */
  enum ClassDiagramLinkMultiplicity {
    cdmZero,            ///< \brief represents 0 multiplicity
    cdmOne,             ///< \brief represents 1 multiplicity
    cdmMany,            ///< \brief represents + multiplicity
    cdmAny              ///< \brief represents * multiplicity
  };
  
  enum ClassDiagramAttrType {
    cdtValue,           ///< \brief represents a simple value attribute
    cdtReference,       ///< \brief represents a reference attribute
    cdtPointer          ///< \brief represents a pointer attribute
  };

typedef std::map<columbus::Key, std::set<NodeId> > MangledNameKey2LimId;

}}}
#endif

