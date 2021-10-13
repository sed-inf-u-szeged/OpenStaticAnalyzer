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

#ifndef _PYTHON_H_
#define _PYTHON_H_

/**
* \file PYTHON.h
* \brief Header can be used for precompiled header.
*/
/*********** Options *************************
 *  SchemaGenerator0190980bbb
 *  IndentInNamespace = 1
 *  IndentInClass = 1
 *  IndentUnderPubProtPri = 1
 *  UseShortRange = true
 *  ACommonGetIsForLeaf = true
 *  AlgPreorderSafeMode = true
 *  GenerateInOutForComment = true
 *  GenerateFilter = true
 *  GenerateReverseEdges = true
 *  GenerateAsgStat = false
 *  GenerateSpecFilterVisitor = false
 *  GenerateSpecXml = false
 *  GenerateDOT = false
 *  GenerateGraphml = false
 *  GenerateJSON = false
 *  GenerateSerialize = false
 *  GenerateParentEdge = true
 *  FactoryModes = 
 *  APIVersion = 2.0.12
 *  BinaryVersion = 2.0.12
 *  CSIHeaderText = PythonLanguage
 *********************************************/
#include <list>
#include <cstring>
#include <map>
#include <set>
#include <string>
#include <boost/crc.hpp>

#include "Forwards.h"

// externals
#include "AsgCommon.h"
#include "strtable/inc/RefDistributorStrTable.h"
#include "csi/inc/csi.h"
#include "Exception.h"

#include "Constant.h"
#include "Types.h"
#include "Range.h"
#include "PythonException.h"
#include "ListIterator.h"
#include "Common.h"
#include "ReverseEdges.h"


 /***********************NODES******************/
#include "base/Base.h"
#include "base/Positioned.h"
#include "module/Object.h"
#include "module/Package.h"
#include "type/Type.h"
#include "base/Comment.h"
#include "base/Docstring.h"
#include "base/Named.h"
#include "expression/ArgumentList.h"
#include "expression/Expression.h"
#include "expression/Generator.h"
#include "expression/KeyValue.h"
#include "expression/Keyword.h"
#include "statement/BaseSpecifier.h"
#include "statement/Handler.h"
#include "statement/Statement.h"
#include "statement/Suite.h"
#include "statement/TargetList.h"
#include "statement/WithItem.h"
#include "type/DictType.h"
#include "type/ReferenceType.h"
#include "type/SequenceType.h"
#include "type/SimpleType.h"
#include "module/Module.h"
#include "statement/Alias.h"
#include "statement/Parameter.h"
#include "expression/Await.h"
#include "expression/Binary.h"
#include "expression/DictComp.h"
#include "expression/Dictionary.h"
#include "expression/ExpressionList.h"
#include "expression/GeneratorExpression.h"
#include "expression/Identifier.h"
#include "expression/IfExpression.h"
#include "expression/JoinedStr.h"
#include "expression/Lambda.h"
#include "expression/List.h"
#include "expression/ListComp.h"
#include "expression/Literal.h"
#include "expression/NamedExpr.h"
#include "expression/Set.h"
#include "expression/SetComp.h"
#include "expression/Starred.h"
#include "expression/StringConversion.h"
#include "expression/Unary.h"
#include "expression/YieldExpression.h"
#include "statement/CompoundStatement.h"
#include "statement/SimpleStatement.h"
#include "expression/AttributeRef.h"
#include "expression/BinaryArithmetic.h"
#include "expression/BinaryLogical.h"
#include "expression/BytesLiteral.h"
#include "expression/FloatNumber.h"
#include "expression/FormattedValue.h"
#include "expression/ImagNumber.h"
#include "expression/IntegerLiteral.h"
#include "expression/LongInteger.h"
#include "expression/StringLiteral.h"
#include "expression/Call.h"
#include "expression/Slicing.h"
#include "expression/Subscription.h"
#include "expression/UnaryOperation.h"
#include "statement/ClassDef.h"
#include "statement/FunctionDef.h"
#include "statement/If.h"
#include "statement/Iteration.h"
#include "statement/Try.h"
#include "statement/With.h"
#include "statement/Assert.h"
#include "statement/Assign.h"
#include "statement/Break.h"
#include "statement/Continue.h"
#include "statement/Delete.h"
#include "statement/Exec.h"
#include "statement/Global.h"
#include "statement/ImportStatement.h"
#include "statement/Nonlocal.h"
#include "statement/Pass.h"
#include "statement/Print.h"
#include "statement/Raise.h"
#include "statement/Return.h"
#include "expression/Ellipsis.h"
#include "expression/ExtSlice.h"
#include "expression/Index.h"
#include "expression/Slice.h"
#include "statement/For.h"
#include "statement/While.h"
#include "statement/AnnAssign.h"
#include "statement/AugAssign.h"
#include "statement/ImportFrom.h"


#include "Filter.h"
#include "Factory.h"

#include "visitors/Visitor.h"
#include "visitors/VisitorAbstractNodes.h"
#include "visitors/VisitorPYTHONML.h"
#include "visitors/VisitorFilter.h"
#include "visitors/VisitorReverseEdges.h"
#include "visitors/VisitorSave.h"
#include "visitors/VisitorSubtreeCollector.h"
#include "visitors/VisitorSimpleEdge.h"
#include "Range.h"

#include "algorithms/Algorithm.h"
#include "algorithms/AlgorithmPreorder.h"
#include "PythonCollector.h"

#endif

