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

#include "python/inc/python.h"
#include "python/inc/messages.h"
#include <sstream>

namespace columbus { namespace python { namespace asg {
namespace Common {

bool getIsComment(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkComment;
}

bool getIsDocstring(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkDocstring;
}

bool getIsNamed(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkNamed ||
    ndk == ndkModule ||
    ndk == ndkAlias ||
    ndk == ndkParameter;
}

bool getIsPositioned(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkPositioned ||
    ndk == ndkComment ||
    ndk == ndkDocstring ||
    ndk == ndkModule ||
    ndk == ndkAlias ||
    ndk == ndkParameter ||
    ndk == ndkArgumentList ||
    ndk == ndkAwait ||
    ndk == ndkAttributeRef ||
    ndk == ndkBinaryArithmetic ||
    ndk == ndkBinaryLogical ||
    ndk == ndkDictComp ||
    ndk == ndkDictionary ||
    ndk == ndkExpressionList ||
    ndk == ndkGeneratorExpression ||
    ndk == ndkIdentifier ||
    ndk == ndkIfExpression ||
    ndk == ndkJoinedStr ||
    ndk == ndkLambda ||
    ndk == ndkList ||
    ndk == ndkListComp ||
    ndk == ndkBytesLiteral ||
    ndk == ndkFloatNumber ||
    ndk == ndkFormattedValue ||
    ndk == ndkImagNumber ||
    ndk == ndkIntegerLiteral ||
    ndk == ndkLongInteger ||
    ndk == ndkStringLiteral ||
    ndk == ndkNamedExpr ||
    ndk == ndkSet ||
    ndk == ndkSetComp ||
    ndk == ndkStarred ||
    ndk == ndkStringConversion ||
    ndk == ndkCall ||
    ndk == ndkEllipsis ||
    ndk == ndkExtSlice ||
    ndk == ndkIndex ||
    ndk == ndkSlice ||
    ndk == ndkSubscription ||
    ndk == ndkUnaryOperation ||
    ndk == ndkYieldExpression ||
    ndk == ndkGenerator ||
    ndk == ndkKeyValue ||
    ndk == ndkKeyword ||
    ndk == ndkBaseSpecifier ||
    ndk == ndkHandler ||
    ndk == ndkClassDef ||
    ndk == ndkFunctionDef ||
    ndk == ndkIf ||
    ndk == ndkFor ||
    ndk == ndkWhile ||
    ndk == ndkTry ||
    ndk == ndkWith ||
    ndk == ndkAssert ||
    ndk == ndkAssign ||
    ndk == ndkAnnAssign ||
    ndk == ndkAugAssign ||
    ndk == ndkBreak ||
    ndk == ndkContinue ||
    ndk == ndkDelete ||
    ndk == ndkExec ||
    ndk == ndkGlobal ||
    ndk == ndkImportStatement ||
    ndk == ndkImportFrom ||
    ndk == ndkNonlocal ||
    ndk == ndkPass ||
    ndk == ndkPrint ||
    ndk == ndkRaise ||
    ndk == ndkReturn ||
    ndk == ndkSuite ||
    ndk == ndkTargetList ||
    ndk == ndkWithItem;
}

bool getIsArgumentList(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkArgumentList;
}

bool getIsAttributeRef(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkAttributeRef;
}

bool getIsAwait(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkAwait;
}

bool getIsBinary(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkBinary ||
    ndk == ndkAttributeRef ||
    ndk == ndkBinaryArithmetic ||
    ndk == ndkBinaryLogical;
}

bool getIsBinaryArithmetic(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkBinaryArithmetic;
}

bool getIsBinaryLogical(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkBinaryLogical;
}

bool getIsBytesLiteral(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkBytesLiteral;
}

bool getIsCall(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkCall;
}

bool getIsDictComp(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkDictComp;
}

bool getIsDictionary(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkDictionary;
}

bool getIsEllipsis(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkEllipsis;
}

bool getIsExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkExpression ||
    ndk == ndkAwait ||
    ndk == ndkAttributeRef ||
    ndk == ndkBinaryArithmetic ||
    ndk == ndkBinaryLogical ||
    ndk == ndkDictComp ||
    ndk == ndkDictionary ||
    ndk == ndkExpressionList ||
    ndk == ndkGeneratorExpression ||
    ndk == ndkIdentifier ||
    ndk == ndkIfExpression ||
    ndk == ndkJoinedStr ||
    ndk == ndkLambda ||
    ndk == ndkList ||
    ndk == ndkListComp ||
    ndk == ndkBytesLiteral ||
    ndk == ndkFloatNumber ||
    ndk == ndkFormattedValue ||
    ndk == ndkImagNumber ||
    ndk == ndkIntegerLiteral ||
    ndk == ndkLongInteger ||
    ndk == ndkStringLiteral ||
    ndk == ndkNamedExpr ||
    ndk == ndkSet ||
    ndk == ndkSetComp ||
    ndk == ndkStarred ||
    ndk == ndkStringConversion ||
    ndk == ndkCall ||
    ndk == ndkEllipsis ||
    ndk == ndkExtSlice ||
    ndk == ndkIndex ||
    ndk == ndkSlice ||
    ndk == ndkSubscription ||
    ndk == ndkUnaryOperation ||
    ndk == ndkYieldExpression;
}

bool getIsExpressionList(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkExpressionList;
}

bool getIsExtSlice(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkExtSlice;
}

bool getIsFloatNumber(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkFloatNumber;
}

bool getIsFormattedValue(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkFormattedValue;
}

bool getIsGenerator(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkGenerator;
}

bool getIsGeneratorExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkGeneratorExpression;
}

bool getIsIdentifier(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkIdentifier;
}

bool getIsIfExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkIfExpression;
}

bool getIsImagNumber(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkImagNumber;
}

bool getIsIndex(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkIndex;
}

bool getIsIntegerLiteral(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkIntegerLiteral;
}

bool getIsJoinedStr(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkJoinedStr;
}

bool getIsKeyValue(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkKeyValue;
}

bool getIsKeyword(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkKeyword;
}

bool getIsLambda(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkLambda;
}

bool getIsList(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkList;
}

bool getIsListComp(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkListComp;
}

bool getIsLiteral(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkLiteral ||
    ndk == ndkBytesLiteral ||
    ndk == ndkFloatNumber ||
    ndk == ndkFormattedValue ||
    ndk == ndkImagNumber ||
    ndk == ndkIntegerLiteral ||
    ndk == ndkLongInteger ||
    ndk == ndkStringLiteral;
}

bool getIsLongInteger(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkLongInteger;
}

bool getIsNamedExpr(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkNamedExpr;
}

bool getIsSet(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkSet;
}

bool getIsSetComp(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkSetComp;
}

bool getIsSlice(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkSlice;
}

bool getIsSlicing(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkSlicing ||
    ndk == ndkEllipsis ||
    ndk == ndkExtSlice ||
    ndk == ndkIndex ||
    ndk == ndkSlice;
}

bool getIsStarred(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkStarred;
}

bool getIsStringConversion(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkStringConversion;
}

bool getIsStringLiteral(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkStringLiteral;
}

bool getIsSubscription(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkSubscription;
}

bool getIsUnary(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkUnary ||
    ndk == ndkCall ||
    ndk == ndkEllipsis ||
    ndk == ndkExtSlice ||
    ndk == ndkIndex ||
    ndk == ndkSlice ||
    ndk == ndkSubscription ||
    ndk == ndkUnaryOperation;
}

bool getIsUnaryOperation(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkUnaryOperation;
}

bool getIsYieldExpression(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkYieldExpression;
}

bool getIsModule(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkModule;
}

bool getIsObject(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkObject;
}

bool getIsPackage(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkPackage;
}

bool getIsAlias(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkAlias;
}

bool getIsAnnAssign(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkAnnAssign;
}

bool getIsAssert(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkAssert;
}

bool getIsAssign(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkAssign ||
    ndk == ndkAnnAssign ||
    ndk == ndkAugAssign;
}

bool getIsAugAssign(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkAugAssign;
}

bool getIsBaseSpecifier(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkBaseSpecifier;
}

bool getIsBreak(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkBreak;
}

bool getIsClassDef(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkClassDef;
}

bool getIsCompoundStatement(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkCompoundStatement ||
    ndk == ndkClassDef ||
    ndk == ndkFunctionDef ||
    ndk == ndkIf ||
    ndk == ndkFor ||
    ndk == ndkWhile ||
    ndk == ndkTry ||
    ndk == ndkWith;
}

bool getIsContinue(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkContinue;
}

bool getIsDelete(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkDelete;
}

bool getIsExec(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkExec;
}

bool getIsFor(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkFor;
}

bool getIsFunctionDef(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkFunctionDef;
}

bool getIsGlobal(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkGlobal;
}

bool getIsHandler(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkHandler;
}

bool getIsIf(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkIf;
}

bool getIsImportFrom(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkImportFrom;
}

bool getIsImportStatement(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkImportStatement ||
    ndk == ndkImportFrom;
}

bool getIsIteration(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkIteration ||
    ndk == ndkFor ||
    ndk == ndkWhile;
}

bool getIsNonlocal(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkNonlocal;
}

bool getIsParameter(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkParameter;
}

bool getIsPass(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkPass;
}

bool getIsPrint(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkPrint;
}

bool getIsRaise(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkRaise;
}

bool getIsReturn(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkReturn;
}

bool getIsSimpleStatement(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkSimpleStatement ||
    ndk == ndkAssert ||
    ndk == ndkAssign ||
    ndk == ndkAnnAssign ||
    ndk == ndkAugAssign ||
    ndk == ndkBreak ||
    ndk == ndkContinue ||
    ndk == ndkDelete ||
    ndk == ndkExec ||
    ndk == ndkGlobal ||
    ndk == ndkImportStatement ||
    ndk == ndkImportFrom ||
    ndk == ndkNonlocal ||
    ndk == ndkPass ||
    ndk == ndkPrint ||
    ndk == ndkRaise ||
    ndk == ndkReturn;
}

bool getIsStatement(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkStatement ||
    ndk == ndkClassDef ||
    ndk == ndkFunctionDef ||
    ndk == ndkIf ||
    ndk == ndkFor ||
    ndk == ndkWhile ||
    ndk == ndkTry ||
    ndk == ndkWith ||
    ndk == ndkAssert ||
    ndk == ndkAssign ||
    ndk == ndkAnnAssign ||
    ndk == ndkAugAssign ||
    ndk == ndkBreak ||
    ndk == ndkContinue ||
    ndk == ndkDelete ||
    ndk == ndkExec ||
    ndk == ndkGlobal ||
    ndk == ndkImportStatement ||
    ndk == ndkImportFrom ||
    ndk == ndkNonlocal ||
    ndk == ndkPass ||
    ndk == ndkPrint ||
    ndk == ndkRaise ||
    ndk == ndkReturn;
}

bool getIsSuite(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkSuite;
}

bool getIsTargetList(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkTargetList;
}

bool getIsTry(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkTry;
}

bool getIsWhile(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkWhile;
}

bool getIsWith(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkWith;
}

bool getIsWithItem(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkWithItem;
}

bool getIsDictType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkDictType;
}

bool getIsReferenceType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkReferenceType;
}

bool getIsSequenceType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkSequenceType;
}

bool getIsSimpleType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkSimpleType;
}

bool getIsType(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkType ||
    ndk == ndkDictType ||
    ndk == ndkReferenceType ||
    ndk == ndkSequenceType ||
    ndk == ndkSimpleType;
}

bool getIsAPSpecNode(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkComment ||
    ndk == ndkDocstring ||
    ndk == ndkDictType ||
    ndk == ndkReferenceType ||
    ndk == ndkSequenceType ||
    ndk == ndkSimpleType;
}

bool getIsComposite(const base::Base& node) {
  return !getIsNotComposite(node);
}

bool getIsNotComposite(const base::Base& node) {
  NodeKind ndk = node.getNodeKind();
  return
    ndk == ndkComment ||
    ndk == ndkDocstring ||
    ndk == ndkAlias ||
    ndk == ndkIdentifier ||
    ndk == ndkBytesLiteral ||
    ndk == ndkFloatNumber ||
    ndk == ndkImagNumber ||
    ndk == ndkIntegerLiteral ||
    ndk == ndkLongInteger ||
    ndk == ndkStringLiteral ||
    ndk == ndkBreak ||
    ndk == ndkContinue ||
    ndk == ndkPass ||
    ndk == ndkObject ||
    ndk == ndkDictType ||
    ndk == ndkReferenceType ||
    ndk == ndkSequenceType ||
    ndk == ndkSimpleType;
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
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkDocstring:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkNamed:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkPositioned:
        return getIsBaseClassKind(ndkBase, base);
      case ndkArgumentList:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkAttributeRef:
        return getIsBaseClassKind(ndkBinary, base);
      case ndkAwait:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkBinary:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkBinaryArithmetic:
        return getIsBaseClassKind(ndkBinary, base);
      case ndkBinaryLogical:
        return getIsBaseClassKind(ndkBinary, base);
      case ndkBytesLiteral:
        return getIsBaseClassKind(ndkLiteral, base);
      case ndkCall:
        return getIsBaseClassKind(ndkUnary, base);
      case ndkDictComp:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkDictionary:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkEllipsis:
        return getIsBaseClassKind(ndkSlicing, base);
      case ndkExpression:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkExpressionList:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkExtSlice:
        return getIsBaseClassKind(ndkSlicing, base);
      case ndkFloatNumber:
        return getIsBaseClassKind(ndkLiteral, base);
      case ndkFormattedValue:
        return getIsBaseClassKind(ndkLiteral, base);
      case ndkGenerator:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkGeneratorExpression:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkIdentifier:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkIfExpression:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkImagNumber:
        return getIsBaseClassKind(ndkLiteral, base);
      case ndkIndex:
        return getIsBaseClassKind(ndkSlicing, base);
      case ndkIntegerLiteral:
        return getIsBaseClassKind(ndkLiteral, base);
      case ndkJoinedStr:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkKeyValue:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkKeyword:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkLambda:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkList:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkListComp:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkLiteral:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkLongInteger:
        return getIsBaseClassKind(ndkLiteral, base);
      case ndkNamedExpr:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkSet:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkSetComp:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkSlice:
        return getIsBaseClassKind(ndkSlicing, base);
      case ndkSlicing:
        return getIsBaseClassKind(ndkUnary, base);
      case ndkStarred:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkStringConversion:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkStringLiteral:
        return getIsBaseClassKind(ndkLiteral, base);
      case ndkSubscription:
        return getIsBaseClassKind(ndkUnary, base);
      case ndkUnary:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkUnaryOperation:
        return getIsBaseClassKind(ndkUnary, base);
      case ndkYieldExpression:
        return getIsBaseClassKind(ndkExpression, base);
      case ndkModule:
        return getIsBaseClassKind(ndkNamed, base);
      case ndkObject:
        return getIsBaseClassKind(ndkBase, base);
      case ndkPackage:
        return getIsBaseClassKind(ndkBase, base);
      case ndkAlias:
        return getIsBaseClassKind(ndkNamed, base);
      case ndkAnnAssign:
        return getIsBaseClassKind(ndkAssign, base);
      case ndkAssert:
        return getIsBaseClassKind(ndkSimpleStatement, base);
      case ndkAssign:
        return getIsBaseClassKind(ndkSimpleStatement, base);
      case ndkAugAssign:
        return getIsBaseClassKind(ndkAssign, base);
      case ndkBaseSpecifier:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkBreak:
        return getIsBaseClassKind(ndkSimpleStatement, base);
      case ndkClassDef:
        return getIsBaseClassKind(ndkCompoundStatement, base);
      case ndkCompoundStatement:
        return getIsBaseClassKind(ndkStatement, base);
      case ndkContinue:
        return getIsBaseClassKind(ndkSimpleStatement, base);
      case ndkDelete:
        return getIsBaseClassKind(ndkSimpleStatement, base);
      case ndkExec:
        return getIsBaseClassKind(ndkSimpleStatement, base);
      case ndkFor:
        return getIsBaseClassKind(ndkIteration, base);
      case ndkFunctionDef:
        return getIsBaseClassKind(ndkCompoundStatement, base);
      case ndkGlobal:
        return getIsBaseClassKind(ndkSimpleStatement, base);
      case ndkHandler:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkIf:
        return getIsBaseClassKind(ndkCompoundStatement, base);
      case ndkImportFrom:
        return getIsBaseClassKind(ndkImportStatement, base);
      case ndkImportStatement:
        return getIsBaseClassKind(ndkSimpleStatement, base);
      case ndkIteration:
        return getIsBaseClassKind(ndkCompoundStatement, base);
      case ndkNonlocal:
        return getIsBaseClassKind(ndkSimpleStatement, base);
      case ndkParameter:
        return getIsBaseClassKind(ndkNamed, base);
      case ndkPass:
        return getIsBaseClassKind(ndkSimpleStatement, base);
      case ndkPrint:
        return getIsBaseClassKind(ndkSimpleStatement, base);
      case ndkRaise:
        return getIsBaseClassKind(ndkSimpleStatement, base);
      case ndkReturn:
        return getIsBaseClassKind(ndkSimpleStatement, base);
      case ndkSimpleStatement:
        return getIsBaseClassKind(ndkStatement, base);
      case ndkStatement:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkSuite:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkTargetList:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkTry:
        return getIsBaseClassKind(ndkCompoundStatement, base);
      case ndkWhile:
        return getIsBaseClassKind(ndkIteration, base);
      case ndkWith:
        return getIsBaseClassKind(ndkCompoundStatement, base);
      case ndkWithItem:
        return getIsBaseClassKind(ndkPositioned, base);
      case ndkDictType:
        return getIsBaseClassKind(ndkType, base);
      case ndkReferenceType:
        return getIsBaseClassKind(ndkType, base);
      case ndkSequenceType:
        return getIsBaseClassKind(ndkType, base);
      case ndkSimpleType:
        return getIsBaseClassKind(ndkType, base);
      case ndkType:
        return getIsBaseClassKind(ndkBase, base);
      default:
        return false;
  }
  return false;
}

const std::string toString(AssignmentKind kind) {
  switch (kind) {
    case askAdd: return "askAdd";
    case askSub: return "askSub";
    case askMult: return "askMult";
    case askMatMult: return "askMatMult";
    case askDiv: return "askDiv";
    case askMod: return "askMod";
    case askPow: return "askPow";
    case askLShift: return "askLShift";
    case askRShift: return "askRShift";
    case askBitOr: return "askBitOr";
    case askBitXor: return "askBitXor";
    case askBitAnd: return "askBitAnd";
    case askFloorDiv: return "askFloorDiv";
    default: throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(BinaryArithmeticKind kind) {
  switch (kind) {
    case bakMultiplication: return "bakMultiplication";
    case bakMatrixMultiplication: return "bakMatrixMultiplication";
    case bakDivision: return "bakDivision";
    case bakFloorDivision: return "bakFloorDivision";
    case bakModulo: return "bakModulo";
    case bakAddition: return "bakAddition";
    case bakSubtraction: return "bakSubtraction";
    case bakPow: return "bakPow";
    case bakLShift: return "bakLShift";
    case bakRShift: return "bakRShift";
    case bakBitOr: return "bakBitOr";
    case bakBitXor: return "bakBitXor";
    case bakBitAnd: return "bakBitAnd";
    default: throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(BinaryLogicalKind kind) {
  switch (kind) {
    case blkEq: return "blkEq";
    case blkNotEq: return "blkNotEq";
    case blkLt: return "blkLt";
    case blkLtE: return "blkLtE";
    case blkGt: return "blkGt";
    case blkGtE: return "blkGtE";
    case blkIs: return "blkIs";
    case blkIsNot: return "blkIsNot";
    case blkIn: return "blkIn";
    case blkNotIn: return "blkNotIn";
    case blkAnd: return "blkAnd";
    case blkOr: return "blkOr";
    default: throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(OriginKind kind) {
  switch (kind) {
    case orkAnalyzer: return "orkAnalyzer";
    case orkGenerator: return "orkGenerator";
    default: throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(ParameterKind kind) {
  switch (kind) {
    case pmkNormal: return "pmkNormal";
    case pmkKwarg: return "pmkKwarg";
    case pmkVararg: return "pmkVararg";
    case pmkKwonlyarg: return "pmkKwonlyarg";
    case pmkPosonlyarg: return "pmkPosonlyarg";
    default: throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(SequenceTypeKind kind) {
  switch (kind) {
    case sekString: return "sekString";
    case sekList: return "sekList";
    case sekTuple: return "sekTuple";
    default: throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(SimpleTypeKind kind) {
  switch (kind) {
    case stkInteger: return "stkInteger";
    case stkLong: return "stkLong";
    case stkFloat: return "stkFloat";
    case stkImaginary: return "stkImaginary";
    case stkBoolean: return "stkBoolean";
    case stkNone: return "stkNone";
    case stkUnknown: return "stkUnknown";
    default: throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(UnaryKind kind) {
  switch (kind) {
    case unkInvert: return "unkInvert";
    case unkNot: return "unkNot";
    case unkPlus: return "unkPlus";
    case unkMinus: return "unkMinus";
    default: throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(NodeKind kind) {
  switch (kind) {
    case ndkBase: return "ndkBase";
    case ndkComment: return "ndkComment";
    case ndkDocstring: return "ndkDocstring";
    case ndkNamed: return "ndkNamed";
    case ndkPositioned: return "ndkPositioned";
    case ndkArgumentList: return "ndkArgumentList";
    case ndkAttributeRef: return "ndkAttributeRef";
    case ndkAwait: return "ndkAwait";
    case ndkBinary: return "ndkBinary";
    case ndkBinaryArithmetic: return "ndkBinaryArithmetic";
    case ndkBinaryLogical: return "ndkBinaryLogical";
    case ndkBytesLiteral: return "ndkBytesLiteral";
    case ndkCall: return "ndkCall";
    case ndkDictComp: return "ndkDictComp";
    case ndkDictionary: return "ndkDictionary";
    case ndkEllipsis: return "ndkEllipsis";
    case ndkExpression: return "ndkExpression";
    case ndkExpressionList: return "ndkExpressionList";
    case ndkExtSlice: return "ndkExtSlice";
    case ndkFloatNumber: return "ndkFloatNumber";
    case ndkFormattedValue: return "ndkFormattedValue";
    case ndkGenerator: return "ndkGenerator";
    case ndkGeneratorExpression: return "ndkGeneratorExpression";
    case ndkIdentifier: return "ndkIdentifier";
    case ndkIfExpression: return "ndkIfExpression";
    case ndkImagNumber: return "ndkImagNumber";
    case ndkIndex: return "ndkIndex";
    case ndkIntegerLiteral: return "ndkIntegerLiteral";
    case ndkJoinedStr: return "ndkJoinedStr";
    case ndkKeyValue: return "ndkKeyValue";
    case ndkKeyword: return "ndkKeyword";
    case ndkLambda: return "ndkLambda";
    case ndkList: return "ndkList";
    case ndkListComp: return "ndkListComp";
    case ndkLiteral: return "ndkLiteral";
    case ndkLongInteger: return "ndkLongInteger";
    case ndkNamedExpr: return "ndkNamedExpr";
    case ndkSet: return "ndkSet";
    case ndkSetComp: return "ndkSetComp";
    case ndkSlice: return "ndkSlice";
    case ndkSlicing: return "ndkSlicing";
    case ndkStarred: return "ndkStarred";
    case ndkStringConversion: return "ndkStringConversion";
    case ndkStringLiteral: return "ndkStringLiteral";
    case ndkSubscription: return "ndkSubscription";
    case ndkUnary: return "ndkUnary";
    case ndkUnaryOperation: return "ndkUnaryOperation";
    case ndkYieldExpression: return "ndkYieldExpression";
    case ndkModule: return "ndkModule";
    case ndkObject: return "ndkObject";
    case ndkPackage: return "ndkPackage";
    case ndkAlias: return "ndkAlias";
    case ndkAnnAssign: return "ndkAnnAssign";
    case ndkAssert: return "ndkAssert";
    case ndkAssign: return "ndkAssign";
    case ndkAugAssign: return "ndkAugAssign";
    case ndkBaseSpecifier: return "ndkBaseSpecifier";
    case ndkBreak: return "ndkBreak";
    case ndkClassDef: return "ndkClassDef";
    case ndkCompoundStatement: return "ndkCompoundStatement";
    case ndkContinue: return "ndkContinue";
    case ndkDelete: return "ndkDelete";
    case ndkExec: return "ndkExec";
    case ndkFor: return "ndkFor";
    case ndkFunctionDef: return "ndkFunctionDef";
    case ndkGlobal: return "ndkGlobal";
    case ndkHandler: return "ndkHandler";
    case ndkIf: return "ndkIf";
    case ndkImportFrom: return "ndkImportFrom";
    case ndkImportStatement: return "ndkImportStatement";
    case ndkIteration: return "ndkIteration";
    case ndkNonlocal: return "ndkNonlocal";
    case ndkParameter: return "ndkParameter";
    case ndkPass: return "ndkPass";
    case ndkPrint: return "ndkPrint";
    case ndkRaise: return "ndkRaise";
    case ndkReturn: return "ndkReturn";
    case ndkSimpleStatement: return "ndkSimpleStatement";
    case ndkStatement: return "ndkStatement";
    case ndkSuite: return "ndkSuite";
    case ndkTargetList: return "ndkTargetList";
    case ndkTry: return "ndkTry";
    case ndkWhile: return "ndkWhile";
    case ndkWith: return "ndkWith";
    case ndkWithItem: return "ndkWithItem";
    case ndkDictType: return "ndkDictType";
    case ndkReferenceType: return "ndkReferenceType";
    case ndkSequenceType: return "ndkSequenceType";
    case ndkSimpleType: return "ndkSimpleType";
    case ndkType: return "ndkType";
    default: throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
  }
}

const std::string toString(EdgeKind kind) {
  switch (kind) {
    case edkPositioned_Comments: return "edkPositioned_Comments";
    case edkArgumentList_HasPositionalArguments: return "edkArgumentList_HasPositionalArguments";
    case edkArgumentList_HasDictionary: return "edkArgumentList_HasDictionary";
    case edkArgumentList_HasKeyword: return "edkArgumentList_HasKeyword";
    case edkArgumentList_HasTuple: return "edkArgumentList_HasTuple";
    case edkAwait_HasValue: return "edkAwait_HasValue";
    case edkBinary_HasLeftExpression: return "edkBinary_HasLeftExpression";
    case edkBinary_HasRightExpression: return "edkBinary_HasRightExpression";
    case edkCall_HasArgumentList: return "edkCall_HasArgumentList";
    case edkCall_RefersTo: return "edkCall_RefersTo";
    case edkDictComp_HasKeyValue: return "edkDictComp_HasKeyValue";
    case edkDictComp_HasGenerator: return "edkDictComp_HasGenerator";
    case edkDictionary_HasKeyValue: return "edkDictionary_HasKeyValue";
    case edkExpression_HasType: return "edkExpression_HasType";
    case edkExpressionList_HasExpression: return "edkExpressionList_HasExpression";
    case edkExtSlice_HasItem: return "edkExtSlice_HasItem";
    case edkFormattedValue_HasValue: return "edkFormattedValue_HasValue";
    case edkFormattedValue_HasFormatSpec: return "edkFormattedValue_HasFormatSpec";
    case edkGenerator_HasCondition: return "edkGenerator_HasCondition";
    case edkGenerator_HasIter: return "edkGenerator_HasIter";
    case edkGenerator_HasTarget: return "edkGenerator_HasTarget";
    case edkGeneratorExpression_HasExpression: return "edkGeneratorExpression_HasExpression";
    case edkGeneratorExpression_HasGenerator: return "edkGeneratorExpression_HasGenerator";
    case edkIdentifier_RefersTo: return "edkIdentifier_RefersTo";
    case edkIfExpression_HasBody: return "edkIfExpression_HasBody";
    case edkIfExpression_HasElseBody: return "edkIfExpression_HasElseBody";
    case edkIfExpression_HasTest: return "edkIfExpression_HasTest";
    case edkJoinedStr_HasValue: return "edkJoinedStr_HasValue";
    case edkKeyValue_HasKey: return "edkKeyValue_HasKey";
    case edkKeyValue_HasValue: return "edkKeyValue_HasValue";
    case edkKeyword_HasKey: return "edkKeyword_HasKey";
    case edkKeyword_HasValue: return "edkKeyword_HasValue";
    case edkLambda_HasObject: return "edkLambda_HasObject";
    case edkLambda_HasParameter: return "edkLambda_HasParameter";
    case edkLambda_HasExpression: return "edkLambda_HasExpression";
    case edkList_HasExpression: return "edkList_HasExpression";
    case edkListComp_HasExpression: return "edkListComp_HasExpression";
    case edkListComp_HasGenerator: return "edkListComp_HasGenerator";
    case edkNamedExpr_HasTarget: return "edkNamedExpr_HasTarget";
    case edkNamedExpr_HasValue: return "edkNamedExpr_HasValue";
    case edkSet_HasExpression: return "edkSet_HasExpression";
    case edkSetComp_HasExpression: return "edkSetComp_HasExpression";
    case edkSetComp_HasGenerator: return "edkSetComp_HasGenerator";
    case edkSlice_HasLowerBound: return "edkSlice_HasLowerBound";
    case edkSlice_HasStride: return "edkSlice_HasStride";
    case edkSlice_HasUpperBound: return "edkSlice_HasUpperBound";
    case edkStarred_HasValue: return "edkStarred_HasValue";
    case edkStringConversion_HasExpressionList: return "edkStringConversion_HasExpressionList";
    case edkSubscription_HasSlicing: return "edkSubscription_HasSlicing";
    case edkUnary_HasExpression: return "edkUnary_HasExpression";
    case edkYieldExpression_HasExpression: return "edkYieldExpression_HasExpression";
    case edkModule_HasObject: return "edkModule_HasObject";
    case edkModule_HasStatement: return "edkModule_HasStatement";
    case edkModule_Docstring: return "edkModule_Docstring";
    case edkObject_RefersTo: return "edkObject_RefersTo";
    case edkObject_HasType: return "edkObject_HasType";
    case edkPackage_HasModule: return "edkPackage_HasModule";
    case edkPackage_HasPackage: return "edkPackage_HasPackage";
    case edkAlias_RefersTo: return "edkAlias_RefersTo";
    case edkAnnAssign_HasAnnotation: return "edkAnnAssign_HasAnnotation";
    case edkAssert_HasMsgExpression: return "edkAssert_HasMsgExpression";
    case edkAssert_HasTestExpression: return "edkAssert_HasTestExpression";
    case edkAssign_HasExpression: return "edkAssign_HasExpression";
    case edkAssign_HasTargetList: return "edkAssign_HasTargetList";
    case edkBaseSpecifier_HasName: return "edkBaseSpecifier_HasName";
    case edkBaseSpecifier_DerivesFrom: return "edkBaseSpecifier_DerivesFrom";
    case edkClassDef_HasObject: return "edkClassDef_HasObject";
    case edkClassDef_HasBaseSpecifier: return "edkClassDef_HasBaseSpecifier";
    case edkClassDef_HasKeyword: return "edkClassDef_HasKeyword";
    case edkClassDef_HasDecorator: return "edkClassDef_HasDecorator";
    case edkClassDef_RefersTo: return "edkClassDef_RefersTo";
    case edkClassDef_Docstring: return "edkClassDef_Docstring";
    case edkCompoundStatement_HasBody: return "edkCompoundStatement_HasBody";
    case edkDelete_HasTargetList: return "edkDelete_HasTargetList";
    case edkExec_HasExpression: return "edkExec_HasExpression";
    case edkExec_HasGlobals: return "edkExec_HasGlobals";
    case edkExec_HasLocals: return "edkExec_HasLocals";
    case edkFor_HasExpressionList: return "edkFor_HasExpressionList";
    case edkFor_HasTargetList: return "edkFor_HasTargetList";
    case edkFunctionDef_HasDecorator: return "edkFunctionDef_HasDecorator";
    case edkFunctionDef_HasObject: return "edkFunctionDef_HasObject";
    case edkFunctionDef_HasParameter: return "edkFunctionDef_HasParameter";
    case edkFunctionDef_HasReturnAnnotation: return "edkFunctionDef_HasReturnAnnotation";
    case edkFunctionDef_RefersTo: return "edkFunctionDef_RefersTo";
    case edkFunctionDef_ReturnType: return "edkFunctionDef_ReturnType";
    case edkFunctionDef_Docstring: return "edkFunctionDef_Docstring";
    case edkGlobal_HasIdentifier: return "edkGlobal_HasIdentifier";
    case edkHandler_HasName: return "edkHandler_HasName";
    case edkHandler_HasExceptBody: return "edkHandler_HasExceptBody";
    case edkHandler_HasType: return "edkHandler_HasType";
    case edkIf_HasElseBody: return "edkIf_HasElseBody";
    case edkIf_HasTestExpression: return "edkIf_HasTestExpression";
    case edkImportStatement_HasAlias: return "edkImportStatement_HasAlias";
    case edkIteration_HasElseBody: return "edkIteration_HasElseBody";
    case edkNonlocal_HasIdentifier: return "edkNonlocal_HasIdentifier";
    case edkParameter_HasDefaultValue: return "edkParameter_HasDefaultValue";
    case edkParameter_HasAnnotation: return "edkParameter_HasAnnotation";
    case edkParameter_RefersTo: return "edkParameter_RefersTo";
    case edkPrint_HasExpressionList: return "edkPrint_HasExpressionList";
    case edkPrint_HasDestination: return "edkPrint_HasDestination";
    case edkRaise_HasType: return "edkRaise_HasType";
    case edkRaise_HasValue: return "edkRaise_HasValue";
    case edkRaise_HasTraceback: return "edkRaise_HasTraceback";
    case edkRaise_HasException: return "edkRaise_HasException";
    case edkRaise_HasCause: return "edkRaise_HasCause";
    case edkReturn_HasExpression: return "edkReturn_HasExpression";
    case edkSuite_HasStatement: return "edkSuite_HasStatement";
    case edkTargetList_HasTarget: return "edkTargetList_HasTarget";
    case edkTry_HasHandler: return "edkTry_HasHandler";
    case edkTry_HasElseBody: return "edkTry_HasElseBody";
    case edkTry_HasFinallyBody: return "edkTry_HasFinallyBody";
    case edkWhile_HasTestExpression: return "edkWhile_HasTestExpression";
    case edkWith_HasWithItem: return "edkWith_HasWithItem";
    case edkWithItem_HasContext: return "edkWithItem_HasContext";
    case edkWithItem_HasTarget: return "edkWithItem_HasTarget";
    case edkReferenceType_RefersTo: return "edkReferenceType_RefersTo";
    default: throw PythonException(COLUMBUS_LOCATION, CMSG_EX_INVALID_NODE_KIND);
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


      const std::string getQualifiedName(const base::Base& node){
        Factory& fact = node.getFactory();
        std::string parent_name = "";
        std::string ret = "";

        if (node.getId() == fact.getRoot()->getId())
          return "Python";

        base::Base* parent = node.getParent();
        if (!parent)
          return "";

        switch (node.getNodeKind()){
          case ndkPackage:
            {
              if (parent != fact.getRoot()) parent_name = getQualifiedName(*parent);
              ret = dynamic_cast<const module::Package&>(node).getName();
              break;
            }
          case ndkModule:
            {
              if (parent != fact.getRoot()) parent_name = getQualifiedName(*parent);
              ret = dynamic_cast<const module::Module&>(node).getName();
              break;
            }
          case ndkFunctionDef:
            {
              if (parent != fact.getRoot()) parent_name = getQualifiedName(*parent);
              ret = dynamic_cast<const statement::FunctionDef&>(node).getName();
              break;
            }
          case ndkClassDef:
            {
              if (parent != fact.getRoot()) parent_name = getQualifiedName(*parent);
              ret = dynamic_cast<const statement::ClassDef&>(node).getName();
              break;
            }
          case ndkIdentifier:
            {
              if (parent != fact.getRoot()) parent_name = getQualifiedName(*parent);
              ret = dynamic_cast<const expression::Identifier&>(node).getName();
              break;
            }
          case ndkParameter:
            {
              if (parent != fact.getRoot()) parent_name = getQualifiedName(*parent);
              ret = dynamic_cast<const statement::Parameter&>(node).getName();
              break;
            }
          default:
            {
              ret = getQualifiedName(*parent);
            }
        }
        if (!parent_name.empty()) {
          ret = parent_name + "." + ret;
        }

        return ret;
      }

      const std::string getUniqueName(const base::Base& node){
        if (node.getId() == node.getFactory().getRoot()->getId())
          return "Python";

        if (!node.getParent())
          return "";

        std::string ret;
        std::string name = getQualifiedName(node);

        switch(node.getNodeKind()){
          case ndkPackage:
            {
              ret = "~Pk";
              break;
            }
          case ndkModule:
            {
              ret = "~Mo";
              break;
            }
          case ndkFunctionDef:
            {
              ret = "~Fn";
              break;
            }
          case ndkClassDef:
            {
              ret = "~Cl";
              break;
            }
          case ndkIdentifier:
            {
              ret = "~At";
              break;
            }
          case ndkParameter:
            {
              ret = "~At";
              break;
            }
          default:
            {
              ret = "";
            }
        }

        return name + ret;
      }
      
      char* getUniqueNameForComponent(char* compName) {
        return compName;
      }

      bool getIsMemberNode(const base::Base& node) {
        switch (node.getNodeKind()) {
          case ndkPackage:
          case ndkModule:
          case ndkClassDef:
          case ndkFunctionDef:
            return true;
          default:
            return false;
        }
      }

      base::Base* getScopeParent(const base::Base& node) {
        Factory& fact = node.getFactory();
        if (&node == fact.getRoot())
          return NULL;

        base::Base* n = node.getParent();
        while (n) {
          switch (n->getNodeKind()) {
            case ndkPackage:
            case ndkModule:
            case ndkFunctionDef:
            case ndkClassDef:
              return n;
            default:
              break;
          }
          n = n->getParent();
        }

        return NULL;
      }} // Common 

}}}
