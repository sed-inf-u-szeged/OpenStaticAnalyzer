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

#include "lim/inc/lim.h"
#include "lim/inc/messages.h"
#include <sstream>

namespace columbus { namespace lim { namespace asg {
namespace Common {

bool getIsComment(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkComment;
}

bool getIsComponent(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkComponent;
}

bool getIsControlFlowBlock(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkControlFlowBlock;
}

bool getIsNamed(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkNamed ||
    ndk == ndkComponent ||
    ndk == ndkGenericParameter ||
    ndk == ndkAttribute ||
    ndk == ndkClass ||
    ndk == ndkClassGeneric ||
    ndk == ndkClassGenericSpec ||
    ndk == ndkClassGenericInstance ||
    ndk == ndkMethod ||
    ndk == ndkMethodGeneric ||
    ndk == ndkMethodGenericSpec ||
    ndk == ndkMethodGenericInstance ||
    ndk == ndkPackage ||
    ndk == ndkParameter ||
    ndk == ndkFile ||
    ndk == ndkFolder ||
    ndk == ndkFileSystem;
}

bool getIsAttribute(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkAttribute;
}

bool getIsAttributeAccess(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkAttributeAccess;
}

bool getIsClass(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkClass ||
    ndk == ndkClassGeneric ||
    ndk == ndkClassGenericSpec ||
    ndk == ndkClassGenericInstance;
}

bool getIsClassGeneric(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkClassGeneric ||
    ndk == ndkClassGenericSpec;
}

bool getIsClassGenericInstance(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkClassGenericInstance;
}

bool getIsClassGenericSpec(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkClassGenericSpec;
}

bool getIsFriendship(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkFriendship;
}

bool getIsGenericParameter(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkGenericParameter;
}

bool getIsMember(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkMember ||
    ndk == ndkAttribute ||
    ndk == ndkClass ||
    ndk == ndkClassGeneric ||
    ndk == ndkClassGenericSpec ||
    ndk == ndkClassGenericInstance ||
    ndk == ndkMethod ||
    ndk == ndkMethodGeneric ||
    ndk == ndkMethodGenericSpec ||
    ndk == ndkMethodGenericInstance ||
    ndk == ndkPackage;
}

bool getIsMethod(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkMethod ||
    ndk == ndkMethodGeneric ||
    ndk == ndkMethodGenericSpec ||
    ndk == ndkMethodGenericInstance;
}

bool getIsMethodCall(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkMethodCall;
}

bool getIsMethodGeneric(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkMethodGeneric ||
    ndk == ndkMethodGenericSpec;
}

bool getIsMethodGenericInstance(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkMethodGenericInstance;
}

bool getIsMethodGenericSpec(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkMethodGenericSpec;
}

bool getIsPackage(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkPackage;
}

bool getIsParameter(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkParameter;
}

bool getIsScope(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkScope ||
    ndk == ndkClass ||
    ndk == ndkClassGeneric ||
    ndk == ndkClassGenericSpec ||
    ndk == ndkClassGenericInstance ||
    ndk == ndkMethod ||
    ndk == ndkMethodGeneric ||
    ndk == ndkMethodGenericSpec ||
    ndk == ndkMethodGenericInstance ||
    ndk == ndkPackage;
}

bool getIsFSEntry(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkFSEntry ||
    ndk == ndkFile ||
    ndk == ndkFolder;
}

bool getIsFile(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkFile;
}

bool getIsFileSystem(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkFileSystem;
}

bool getIsFolder(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkFolder;
}

bool getIsSimpleType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkSimpleType;
}

bool getIsType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkType;
}

bool getIsTypeFormer(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkTypeFormer ||
    ndk == ndkTypeFormerArray ||
    ndk == ndkTypeFormerMethod ||
    ndk == ndkTypeFormerNonType ||
    ndk == ndkTypeFormerPointer ||
    ndk == ndkTypeFormerType;
}

bool getIsTypeFormerArray(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkTypeFormerArray;
}

bool getIsTypeFormerMethod(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkTypeFormerMethod;
}

bool getIsTypeFormerNonType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkTypeFormerNonType;
}

bool getIsTypeFormerPointer(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkTypeFormerPointer;
}

bool getIsTypeFormerType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkTypeFormerType;
}

bool getIsAPSpecNode(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkComment ||
    ndk == ndkComponent ||
    ndk == ndkAttributeAccess ||
    ndk == ndkFriendship ||
    ndk == ndkMethodCall ||
    ndk == ndkFileSystem ||
    ndk == ndkSimpleType ||
    ndk == ndkType ||
    ndk == ndkTypeFormerArray ||
    ndk == ndkTypeFormerMethod ||
    ndk == ndkTypeFormerNonType ||
    ndk == ndkTypeFormerPointer ||
    ndk == ndkTypeFormerType;
}

bool getIsComposite(const base::Base& node) {
  return !getIsNotComposite(node);
}

bool getIsNotComposite(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkComment ||
    ndk == ndkControlFlowBlock ||
    ndk == ndkComponent ||
    ndk == ndkGenericParameter ||
    ndk == ndkAttribute ||
    ndk == ndkClass ||
    ndk == ndkClassGenericInstance ||
    ndk == ndkPackage ||
    ndk == ndkParameter ||
    ndk == ndkFile ||
    ndk == ndkAttributeAccess ||
    ndk == ndkFriendship ||
    ndk == ndkMethodCall ||
    ndk == ndkSimpleType ||
    ndk == ndkType ||
    ndk == ndkTypeFormerArray ||
    ndk == ndkTypeFormerMethod ||
    ndk == ndkTypeFormerNonType ||
    ndk == ndkTypeFormerPointer ||
    ndk == ndkTypeFormerType;
}

const std::string toString(NodeId id) {
  std::stringstream s;
  s << id;
  return s.str();
}

bool getIsBaseClassKind(NodeKind what, NodeKind base) {
  NodeKind type = what;
  if (type == base)
    return true;
  switch (type) {
      case ndkBase:
        return false;
      case ndkComment:
        return getIsBaseClassKind(ndkBase, base);
      case ndkComponent:
        return getIsBaseClassKind(ndkNamed, base);
      case ndkControlFlowBlock:
        return getIsBaseClassKind(ndkBase, base);
      case ndkNamed:
        return getIsBaseClassKind(ndkBase, base);
      case ndkAttribute:
        return getIsBaseClassKind(ndkMember, base);
      case ndkAttributeAccess:
        return getIsBaseClassKind(ndkBase, base);
      case ndkClass:
        return getIsBaseClassKind(ndkScope, base);
      case ndkClassGeneric:
        return getIsBaseClassKind(ndkClass, base);
      case ndkClassGenericInstance:
        return getIsBaseClassKind(ndkClass, base);
      case ndkClassGenericSpec:
        return getIsBaseClassKind(ndkClassGeneric, base);
      case ndkFriendship:
        return getIsBaseClassKind(ndkBase, base);
      case ndkGenericParameter:
        return getIsBaseClassKind(ndkNamed, base);
      case ndkMember:
        return getIsBaseClassKind(ndkNamed, base);
      case ndkMethod:
        return getIsBaseClassKind(ndkScope, base);
      case ndkMethodCall:
        return getIsBaseClassKind(ndkBase, base);
      case ndkMethodGeneric:
        return getIsBaseClassKind(ndkMethod, base);
      case ndkMethodGenericInstance:
        return getIsBaseClassKind(ndkMethod, base);
      case ndkMethodGenericSpec:
        return getIsBaseClassKind(ndkMethodGeneric, base);
      case ndkPackage:
        return getIsBaseClassKind(ndkScope, base);
      case ndkParameter:
        return getIsBaseClassKind(ndkNamed, base);
      case ndkScope:
        return getIsBaseClassKind(ndkMember, base);
      case ndkFSEntry:
        return getIsBaseClassKind(ndkNamed, base);
      case ndkFile:
        return getIsBaseClassKind(ndkFSEntry, base);
      case ndkFileSystem:
        return getIsBaseClassKind(ndkNamed, base);
      case ndkFolder:
        return getIsBaseClassKind(ndkFSEntry, base);
      case ndkSimpleType:
        return getIsBaseClassKind(ndkBase, base);
      case ndkType:
        return getIsBaseClassKind(ndkBase, base);
      case ndkTypeFormer:
        return getIsBaseClassKind(ndkBase, base);
      case ndkTypeFormerArray:
        return getIsBaseClassKind(ndkTypeFormer, base);
      case ndkTypeFormerMethod:
        return getIsBaseClassKind(ndkTypeFormer, base);
      case ndkTypeFormerNonType:
        return getIsBaseClassKind(ndkTypeFormer, base);
      case ndkTypeFormerPointer:
        return getIsBaseClassKind(ndkTypeFormer, base);
      case ndkTypeFormerType:
        return getIsBaseClassKind(ndkTypeFormer, base);
      default:
        return false;
  }
  return false;
}

const std::string toString(AccessibilityKind kind) {
  switch (kind) {
    case ackInternal: return "ackInternal";
    case ackInternalProtected: return "ackInternalProtected";
    case ackNone: return "ackNone";
    case ackPackagePrivate: return "ackPackagePrivate";
    case ackPrivate: return "ackPrivate";
    case ackProtected: return "ackProtected";
    case ackProtectedInternal: return "ackProtectedInternal";
    case ackPublic: return "ackPublic";
    default: throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(AnalysisTimeKind kind) {
  switch (kind) {
    case atkNow: return "atkNow";
    case atkBefore: return "atkBefore";
    case atkNever: return "atkNever";
    default: throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(ClassKind kind) {
  switch (kind) {
    case clkAnnotation: return "clkAnnotation";
    case clkClass: return "clkClass";
    case clkDelegate: return "clkDelegate";
    case clkEnum: return "clkEnum";
    case clkInterface: return "clkInterface";
    case clkStruct: return "clkStruct";
    case clkUnion: return "clkUnion";
    default: throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(GenericParameterKind kind) {
  switch (kind) {
    case gpkConstraint: return "gpkConstraint";
    case gpkNonType: return "gpkNonType";
    case gpkNonTypePack: return "gpkNonTypePack";
    case gpkTemplate: return "gpkTemplate";
    case gpkTemplatePack: return "gpkTemplatePack";
    case gpkType: return "gpkType";
    case gpkTypePack: return "gpkTypePack";
    default: throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(LanguageKind kind) {
  switch (kind) {
    case lnkNotSet: return "lnkNotSet";
    case lnkC: return "lnkC";
    case lnkCpp: return "lnkCpp";
    case lnkJava: return "lnkJava";
    case lnkCsharp: return "lnkCsharp";
    case lnkSql: return "lnkSql";
    case lnkMagic: return "lnkMagic";
    case lnkRpg: return "lnkRpg";
    case lnkPython: return "lnkPython";
    case lnkJavaScript: return "lnkJavaScript";
    default: throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(MethodKind kind) {
  switch (kind) {
    case mekAdd: return "mekAdd";
    case mekConstructor: return "mekConstructor";
    case mekDestructor: return "mekDestructor";
    case mekGet: return "mekGet";
    case mekMenu: return "mekMenu";
    case mekNormal: return "mekNormal";
    case mekOperator: return "mekOperator";
    case mekRemove: return "mekRemove";
    case mekSet: return "mekSet";
    case mekSubroutine: return "mekSubroutine";
    default: throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(PackageKind kind) {
  switch (kind) {
    case pkPackage: return "pkPackage";
    case pkModule: return "pkModule";
    default: throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(ParameterKind kind) {
  switch (kind) {
    case pmkIn: return "pmkIn";
    case pmkInOut: return "pmkInOut";
    case pmkOut: return "pmkOut";
    default: throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(PointerKind kind) {
  switch (kind) {
    case ptkPointer: return "ptkPointer";
    case ptkReference: return "ptkReference";
    default: throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(RealizationLevel kind) {
  switch (kind) {
    case relDeclares: return "relDeclares";
    case relDefines: return "relDefines";
    default: throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(SimpleTypeKind kind) {
  switch (kind) {
    case stkBoolean: return "stkBoolean";
    case stkByte: return "stkByte";
    case stkCharacter: return "stkCharacter";
    case stkDecimal: return "stkDecimal";
    case stkDouble: return "stkDouble";
    case stkFloat: return "stkFloat";
    case stkInteger: return "stkInteger";
    case stkLong: return "stkLong";
    case stkObject: return "stkObject";
    case stkShort: return "stkShort";
    case stkSingle: return "stkSingle";
    case stkString: return "stkString";
    case stkUnicode: return "stkUnicode";
    case stkUnknown: return "stkUnknown";
    case stkUnsignedCharacter: return "stkUnsignedCharacter";
    case stkUnsignedInteger: return "stkUnsignedInteger";
    case stkUnsignedLong: return "stkUnsignedLong";
    case stkUnsignedShort: return "stkUnsignedShort";
    case stkVoid: return "stkVoid";
    default: throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(TypeArgumentConstraintKind kind) {
  switch (kind) {
    case tackLowerBounded: return "tackLowerBounded";
    case tackNone: return "tackNone";
    case tackUnbounded: return "tackUnbounded";
    case tackUpperBounded: return "tackUpperBounded";
    default: throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(NodeKind kind) {
  switch (kind) {
    case ndkBase: return "ndkBase";
    case ndkComment: return "ndkComment";
    case ndkComponent: return "ndkComponent";
    case ndkControlFlowBlock: return "ndkControlFlowBlock";
    case ndkNamed: return "ndkNamed";
    case ndkAttribute: return "ndkAttribute";
    case ndkAttributeAccess: return "ndkAttributeAccess";
    case ndkClass: return "ndkClass";
    case ndkClassGeneric: return "ndkClassGeneric";
    case ndkClassGenericInstance: return "ndkClassGenericInstance";
    case ndkClassGenericSpec: return "ndkClassGenericSpec";
    case ndkFriendship: return "ndkFriendship";
    case ndkGenericParameter: return "ndkGenericParameter";
    case ndkMember: return "ndkMember";
    case ndkMethod: return "ndkMethod";
    case ndkMethodCall: return "ndkMethodCall";
    case ndkMethodGeneric: return "ndkMethodGeneric";
    case ndkMethodGenericInstance: return "ndkMethodGenericInstance";
    case ndkMethodGenericSpec: return "ndkMethodGenericSpec";
    case ndkPackage: return "ndkPackage";
    case ndkParameter: return "ndkParameter";
    case ndkScope: return "ndkScope";
    case ndkFSEntry: return "ndkFSEntry";
    case ndkFile: return "ndkFile";
    case ndkFileSystem: return "ndkFileSystem";
    case ndkFolder: return "ndkFolder";
    case ndkSimpleType: return "ndkSimpleType";
    case ndkType: return "ndkType";
    case ndkTypeFormer: return "ndkTypeFormer";
    case ndkTypeFormerArray: return "ndkTypeFormerArray";
    case ndkTypeFormerMethod: return "ndkTypeFormerMethod";
    case ndkTypeFormerNonType: return "ndkTypeFormerNonType";
    case ndkTypeFormerPointer: return "ndkTypeFormerPointer";
    case ndkTypeFormerType: return "ndkTypeFormerType";
    default: throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(EdgeKind kind) {
  switch (kind) {
    case edkComponent_Contains: return "edkComponent_Contains";
    case edkComponent_HasFiles: return "edkComponent_HasFiles";
    case edkControlFlowBlock_Calls: return "edkControlFlowBlock_Calls";
    case edkControlFlowBlock_Pred: return "edkControlFlowBlock_Pred";
    case edkNamed_DependsOn: return "edkNamed_DependsOn";
    case edkAttribute_Calls: return "edkAttribute_Calls";
    case edkAttribute_HasType: return "edkAttribute_HasType";
    case edkAttributeAccess_Attribute: return "edkAttributeAccess_Attribute";
    case edkClass_GrantsFriendship: return "edkClass_GrantsFriendship";
    case edkClass_IsSubclass: return "edkClass_IsSubclass";
    case edkClassGeneric_HasGenericParameter: return "edkClassGeneric_HasGenericParameter";
    case edkClassGenericInstance_HasArguments: return "edkClassGenericInstance_HasArguments";
    case edkClassGenericSpec_HasArguments: return "edkClassGenericSpec_HasArguments";
    case edkClassGenericSpec_Specialize: return "edkClassGenericSpec_Specialize";
    case edkFriendship_Friend: return "edkFriendship_Friend";
    case edkGenericParameter_HasParameterConstraint: return "edkGenericParameter_HasParameterConstraint";
    case edkMember_Aggregated: return "edkMember_Aggregated";
    case edkMember_BelongsTo: return "edkMember_BelongsTo";
    case edkMember_CompilationUnit: return "edkMember_CompilationUnit";
    case edkMember_Declares: return "edkMember_Declares";
    case edkMember_HasComment: return "edkMember_HasComment";
    case edkMember_Instance: return "edkMember_Instance";
    case edkMember_IsContainedIn: return "edkMember_IsContainedIn";
    case edkMember_LanguageVariant: return "edkMember_LanguageVariant";
    case edkMember_Uses: return "edkMember_Uses";
    case edkMember_Variant: return "edkMember_Variant";
    case edkMethod_AccessesAttribute: return "edkMethod_AccessesAttribute";
    case edkMethod_Calls: return "edkMethod_Calls";
    case edkMethod_CanThrow: return "edkMethod_CanThrow";
    case edkMethod_HasControlFlowBlock: return "edkMethod_HasControlFlowBlock";
    case edkMethod_HasParameter: return "edkMethod_HasParameter";
    case edkMethod_Instantiates: return "edkMethod_Instantiates";
    case edkMethod_Returns: return "edkMethod_Returns";
    case edkMethod_Throws: return "edkMethod_Throws";
    case edkMethodCall_Method: return "edkMethodCall_Method";
    case edkMethodGeneric_HasGenericParameter: return "edkMethodGeneric_HasGenericParameter";
    case edkMethodGenericInstance_HasArguments: return "edkMethodGenericInstance_HasArguments";
    case edkMethodGenericSpec_HasArguments: return "edkMethodGenericSpec_HasArguments";
    case edkMethodGenericSpec_Specialize: return "edkMethodGenericSpec_Specialize";
    case edkParameter_HasType: return "edkParameter_HasType";
    case edkScope_HasMember: return "edkScope_HasMember";
    case edkFile_HasComment: return "edkFile_HasComment";
    case edkFile_Includes: return "edkFile_Includes";
    case edkFileSystem_HasFSEntry: return "edkFileSystem_HasFSEntry";
    case edkFolder_Contains: return "edkFolder_Contains";
    case edkType_HasTypeFormer: return "edkType_HasTypeFormer";
    case edkTypeFormerMethod_HasParameterType: return "edkTypeFormerMethod_HasParameterType";
    case edkTypeFormerMethod_HasReturnType: return "edkTypeFormerMethod_HasReturnType";
    case edkTypeFormerType_RefersTo: return "edkTypeFormerType_RefersTo";
    default: throw LimException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

bool getIsValid(NodeId id) {
  return id > 1;
}

double SimilarityMinimum = 0.1;

double getSimilarityMinimum() {
  return SimilarityMinimum;
}

void setSimilarityMinimum(double value) {
  SimilarityMinimum = value;
}

double SimilarityMinForStrings = 0.0;

double getSimilarityMinForStrings() {
  return SimilarityMinForStrings;
}

void setSimilarityMinForStrings(double value) {
  SimilarityMinForStrings = value;
}

double SimilarityMinForEdges = 0.0;

double getSimilarityMinForEdges() {
  return SimilarityMinForEdges;
}

void setSimilarityMinForEdges(double value) {
  SimilarityMinForEdges = value;
}


const std::string toString(Language language) {
  switch (language) {
    case limLangOther: return "Other";
    case limLangC: return "C";
    case limLangCpp: return "C++";
    case limLangJava: return "Java";
    case limLangCsharp: return "C#";
    case limLangFsql: return "Fsql";
    case limLangPython: return "Python";
    case limLangJavaScript: return "JavaScript";
    default: throw LimException(COLUMBUS_LOCATION, CMSG_EX_COMMON_INVALID_LANGUAGE);
  }
}

const std::string toString(ClassDiagramLinkKind linkKind) {
  switch (linkKind) {
    case cdlUnknown: return "Unknown Connection";
    case cdlAssoc: /* the same as the next one */
    case cdlAssocD: return "Association";
    case cdlAggregatedBy: return "Aggregated by";
    case cdlAggregates: return "Aggregates";
    case cdlComposedBy: return "Composed by";
    case cdlComposes: return "Composes";
    case cdlParent: return "Parent";
    case cdlChild: return "Child";
    case cdlRealizedBy: return "Realized by";
    case cdlRealizes: return "Realizes";
    case cdlAOwnedBy: return "Attribute Owned by";
    case cdlAOwns: return "Owns Attribute";
    case cdlCOwnedBy: return "Class Contained by";
    case cdlCOwns: return "Contains Class";
    case cdlMOwnedBy: return "Method Owned by";
    case cdlMOwns: return "Owns Method";
    case cdlPOwnedBy: return "Owned by Package";
    case cdlPOwns: return "Package Owns";
    case cdlHasType: return "Has type";
    default: throw LimException(COLUMBUS_LOCATION, CMSG_EX_COMMON_UNKNOWN_CLASSDIAGRAM_KIND);
  }
}

const std::string toString(ClassDiagramLinkMultiplicity linkMult) {
  switch(linkMult) {
    case cdmZero: return "0";
    case cdmOne: return "1";
    case cdmMany: return "+";
    case cdmAny: return "*";
    default: throw LimException(COLUMBUS_LOCATION, CMSG_EX_COMMON_UNKNOWN_CLASSDIAGRAM_LINK_MULTIPLICITY);
  }
}

const std::string toSrcString(ClassKind kind) {
  switch (kind) {
    case clkClass: return "Class";
    case clkStruct: return "Struct";
    case clkUnion: return "Union";
    case clkInterface: return "Interface";
    case clkEnum: return "Enum";
    case clkAnnotation: return "Annotation";
    case clkDelegate: return "Delegate";
    default: throw LimException(COLUMBUS_LOCATION, CMSG_EX_COMMON_INVALID_CLASSKIND);
  }
}

NodeId getScopeParent(const base::Base& node) {
  const base::Base* n = &node;
  while (n->getId() != node.getFactory().getRoot()->getId() && n->getParent()) {
    n = n->getParent();
    if (getIsScope(*n))
      return n->getId();
  }
  return 0;
}

const std::string getScopedName(const base::Named& node) {
  NodeId rootId = node.getFactory().getRoot()->getId();

  // the name of the root can be used only its own name
  if (node.getId() == rootId)
    return node.getName();

  std::string ret(node.getName());
  NodeId scopeId = getScopeParent(node);
  while (scopeId && scopeId != rootId) {
    const logical::Scope& scope = (const logical::Scope&)node.getFactory().getRef(scopeId);
    ret = scope.getName() + node.getFactory().getScopeSeparator() + ret;
    scopeId = getScopeParent(scope);
  }
  return ret;
}

const std::string getUniqueName(const lim::asg::logical::Method& node) {
	return node.getName(); // TODO: implementing the unique name
}

NodeId getPackageParent(const base::Base& node) {
  const base::Base* n = &node;
  while (n->getId() != node.getFactory().getRoot()->getId() && n->getParent()) {
    n = n->getParent();
    if (n->getNodeKind() == ndkPackage)
      return n->getId();
  }
  return 0;
}

std::string getFullPath(const lim::asg::physical::FSEntry& node, const char separator /*= DIRDIVCHAR*/) {
  std::string str = node.getName();

  const lim::asg::base::Base* n = node.getParent();
  while (n) {
    if (!lim::asg::Common::getIsFSEntry(*n)) {
      break;
    }
    const std::string& name = static_cast<const lim::asg::physical::FSEntry*>(n)->getName();
    if (name == "/" || name == "\\") {
      str = name + str;
    } else {
      str = name + separator + str;
    }
    n = n->getParent();
  }

  return str;
}

const logical::MethodGeneric* getMethodPrototype(const ReverseEdges& revEdges, const logical::MethodGenericInstance& methodInstance){
  const unsigned int id = methodInstance.getId();
  ListIterator<base::Base> it = revEdges.constIteratorBegin(id, edkMember_Instance);
  if (it != revEdges.constIteratorEnd(id, edkMember_Instance)) {
    if (Common::getIsMethodGeneric(*it)) {
      return (const logical::MethodGeneric*)(&(*it));
    }
  }

  return NULL;
}

const logical::ClassGeneric* getClassPrototype(const ReverseEdges& revEdges, const logical::ClassGenericInstance& classInstance){
  const unsigned int id = classInstance.getId();
  ListIterator<base::Base> it = revEdges.constIteratorBegin(id, edkMember_Instance);
  if (it != revEdges.constIteratorEnd(id, edkMember_Instance)) {
    if (Common::getIsClassGeneric(*it)) {
      return (const logical::ClassGeneric*)(&(*it));
    }
  }

  return NULL;
}


// main implementation
int _collectFamilyByLevel(
  const ReverseEdges& revEdges,
  const logical::Class& node,
  std::set<const logical::Class*>& family,
  int maxLevel,
  int currentLevel,
  bool up,
  InheritanceCache* cache,
  std::set<const logical::Class*>& lineage
)
{
  int depth = 0;

  if ( currentLevel > maxLevel ) return depth + 1;
  
  // pre-collecting the related classes in the given direction
  std::set<const logical::Class*> subclasses;

  if ( up ) // searching parents
  {
    ListIterator<type::Type> subclassTypeIt = node.getIsSubclassListIteratorBegin();
    for ( ; subclassTypeIt != node.getIsSubclassListIteratorEnd(); ++subclassTypeIt )
    {
      if ( subclassTypeIt->getTypeFormerSize() == 1 )
      {
        ListIterator<type::TypeFormer> typeFormer = subclassTypeIt->getTypeFormerListIteratorBegin();

        if ( typeFormer != subclassTypeIt->getTypeFormerListIteratorEnd() && Common::getIsTypeFormerType(*typeFormer) )
        {
          const type::TypeFormerType &typeFormerType = (type::TypeFormerType&) (*typeFormer);
          const base::Base *relative = typeFormerType.getRefersTo();

          if ( relative && Common::getIsClass(*relative) )
          {
            subclasses.insert( (const logical::Class*) relative );
          }
        }
      }
    }
  }
  else // searching children
  {
    // from Class back to TypeFormerTypes
    ListIterator<base::Base> typeFormerTypeIt = revEdges.constIteratorBegin( node.getId(), edkTypeFormerType_RefersTo );
    for ( ; typeFormerTypeIt != revEdges.constIteratorEnd( node.getId(), edkTypeFormerType_RefersTo ); ++typeFormerTypeIt )
    {
      // from TypeFormerType back to Types
      ListIterator<base::Base> typeIt = revEdges.constIteratorBegin( typeFormerTypeIt->getId(), edkType_HasTypeFormer );
      for ( ; typeIt != revEdges.constIteratorEnd( typeFormerTypeIt->getId(), edkType_HasTypeFormer ); ++typeIt )
      {
        // Types are relevant only if they have one TypeFormers
        if ( ((type::Type&) (*typeIt)).getTypeFormerSize() != 1 ) continue;

        // from Type back to Classes that refer to the Type as its subclass
        ListIterator<base::Base> subclassIt = revEdges.constIteratorBegin( typeIt->getId(), edkClass_IsSubclass );
        for ( ; subclassIt != revEdges.constIteratorEnd( typeIt->getId(), edkClass_IsSubclass ); ++subclassIt )
        {
          subclasses.insert( & (const logical::Class&) (*subclassIt) );
        }
      }
    }
  }

  std::set<const logical::Class*>::const_iterator relativeIt = subclasses.begin();
  for ( ; relativeIt != subclasses.end(); ++relativeIt )
  {
    const logical::Class* relative = *relativeIt;

    // stepping from declarations to their definitions
    if ( relative->getDeclares() )
    {
      relative = dynamic_cast<const logical::Class*>( relative->getDeclares() );
    }
    
    // stepping from instances to their generic classes
    if ( Common::getIsClassGenericInstance(*relative) )
    {
      const logical::ClassGenericInstance* baseInstanceClass = (const logical::ClassGenericInstance*) relative;
      ListIterator<base::Base> it = revEdges.constIteratorBegin(baseInstanceClass->getId(), edkMember_Instance);
      if (it != revEdges.constIteratorEnd(baseInstanceClass->getId(), edkMember_Instance))
      {
        if (Common::getIsClassGeneric(*it))
        {
          relative = & (const logical::ClassGeneric&) ( *it );
        }
        else continue;
      }
      else continue;
    }

    // stepping from specializations to their generic classes
    while ( Common::getIsClassGenericSpec(*relative) )
    {
      const logical::ClassGenericSpec* baseSpecClass = (const logical::ClassGenericSpec*) relative;
      if ( baseSpecClass->getSpecialize() )
      {
        relative = baseSpecClass->getSpecialize();
      }
      else break;
    }
    // If the specialize edge was missing
    if ( Common::getIsClassGenericSpec(*relative) ) continue;

    // checking whether there are cycles in the inheritance
    // if so, simply skip this relative
    std::set<const logical::Class*>::const_iterator cycle = lineage.find( relative );
    if ( cycle != lineage.end() ) continue;
    
    // adding the real relative
    family.insert( relative );

    std::set<const logical::Class*> newFamily;
    int childDepth;
    bool miss = true;

    // if cache hit, use those values
    if ( cache )
    {
      InheritanceCache::const_iterator ci = cache->find( relative );
      if ( ci != cache->end() )
      {
        newFamily.insert( ci->second.nodes.begin(), ci->second.nodes.end() );
        childDepth = ci->second.depth;
        miss = false;
      }
    }

    // if cache miss, recursive call
    if ( miss )
    {
      lineage.insert( relative );
      childDepth = _collectFamilyByLevel( revEdges, *relative, newFamily, maxLevel, currentLevel + 1, up, cache, lineage );

      // check descendants for the instances too
      if ( ! up ) {
        ListIterator<lim::asg::logical::Member> genInstanceIt = relative->getInstanceListIteratorBegin();
        for ( ; genInstanceIt != relative->getInstanceListIteratorEnd(); ++genInstanceIt) {
          if ( Common::getIsClassGenericInstance( *genInstanceIt ) ) {
            const lim::asg::logical::ClassGenericInstance& cgi = dynamic_cast<const logical::ClassGenericInstance&>(*genInstanceIt);
            int tempDepth = _collectFamilyByLevel( revEdges, cgi, newFamily, maxLevel, currentLevel + 1, up, cache, lineage );
            if ( tempDepth > childDepth ) {
              childDepth = tempDepth;
            }
          }
        }
      }

      lineage.erase( relative );
    }

    // merge values
    family.insert( newFamily.begin(), newFamily.end() );
    depth = childDepth > depth ? childDepth : depth;

    if ( cache && miss )
    {
      InheritanceData id;
      id.depth = childDepth;
      id.nodes = std::set<const logical::Class*>( newFamily );
      cache->insert( std::make_pair( relative, id ) );
    }

  } // SubClass iterator

  return depth + 1;
}

// wrapper for default reference-type argument
int collectFamilyByLevel(
  const ReverseEdges& revEdges,
  const logical::Class& node,
  std::set<const logical::Class*>& family,
  int maxLevel,
  int currentLevel,
  bool up,
  InheritanceCache* cache
)
{
  std::set<const logical::Class*> lineageRef;
  return _collectFamilyByLevel( revEdges, node, family, maxLevel, currentLevel, up, cache, lineageRef );
}

void collectParents( const ReverseEdges& revEdges, const logical::Class& node, std::set<const logical::Class*>& parents, InheritanceCache* cache )
{
  collectFamilyByLevel( revEdges, node, parents, 1, 1, true, cache );
}

int collectAncestors( const ReverseEdges& revEdges, const logical::Class& node, std::set<const logical::Class*>& ancestors, InheritanceCache* cache )
{
  return collectFamilyByLevel( revEdges, node, ancestors, INT_MAX, 1, true, cache );
}

void collectChildren( const ReverseEdges& revEdges, const logical::Class& node, std::set<const logical::Class*>& children, InheritanceCache* cache )
{
  collectFamilyByLevel( revEdges, node, children, 1, 1, false, cache );
}

int collectDescendants( const ReverseEdges& revEdges, const logical::Class& node, std::set<const logical::Class*>& descendants, InheritanceCache* cache )
{
  return collectFamilyByLevel( revEdges, node, descendants, INT_MAX, 1, false, cache );
}


/*

bool getHasMorePositions(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkClass ||
    ndk == ndkClassGeneric ||
    ndk == ndkPackage;
}

void collectCallees(const logical::Method& node, std::set<NodeId>& callees) {
  ListIteratorAssocUShort it = node.getCallsListIteratorAssoc();
  while (it.hasNext()) {
    const base::Base& n = it.next();
    if (Common::getIsMethodGenericInstance(n)) {
       NodeId instId = ((const type::MethodGenericInstance&)n).getInstantiates();
       if (Common::getIsValid(instId))
         callees.insert(instId);
    } else { // Method or MethodGeneric
      callees.insert(n.getId());
    }
  }
}

void collectCallers(const ReverseEdges& revEdges, const logical::Method& node, std::set<NodeId>& callers) {
  ListIterator callIt = revEdges.constIterator(node.getId(), edkMethodCalls);
  while (callIt.hasNext()) {
    callers.insert(callIt.next().getId());
  }

  ListIterator instIt = revEdges.constIterator(node.getId(), edkMethodGenericInstanceInstantiates);
  while (instIt.hasNext()) {
    const base::Base& inst = instIt.next();
    ListIterator callIt = revEdges.constIterator(inst.getId(), edkMethodCalls);
    while (callIt.hasNext()) {
      callers.insert(callIt.next().getId());
    }
  }
}

*/} // Common 

}}}
