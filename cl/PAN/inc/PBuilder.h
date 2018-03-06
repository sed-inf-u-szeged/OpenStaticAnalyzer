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

#ifndef __PBUILDER_H_
#define __PBUILDER_H_

#include <python/inc/python.h>

using namespace columbus;
using namespace columbus::python::asg;

namespace columbus {

class PBuilder {
private:
  Factory* factory;
  std::string path;
  bool package_build;

public:

  PBuilder(Factory* factory, bool package_build);
  Factory* getFactory();

  void setPath(std::string& path);
  void setPosition(NodeId node, unsigned line, unsigned col, unsigned endline, unsigned endcol);
  void setIncreasedPosition(NodeId node, unsigned line, unsigned col, unsigned endline, unsigned endcol);

  NodeId AddModule( NodeId module, NodeId package );
  void AddObjectRef( NodeId object, NodeId ref );
  NodeId findPackage( std::string name );

  NodeId buildPackage( std::string name, std::vector<NodeId>& package );
  NodeId buildPackage( std::string name, NodeId parent = 0 );
  NodeId buildSuite( std::vector<NodeId>& body );
  NodeId buildModule( std::string name, NodeId docstring, std::vector<NodeId>& body, std::vector<NodeId>& object, int lloc );
  NodeId buildObject( std::string& name );
  NodeId buildBaseSpecifier( NodeId name );
  NodeId buildBreak( );
  NodeId buildTargetList( std::vector<NodeId>& list );
  NodeId buildRaise( NodeId type, NodeId value, NodeId traceback );
  NodeId buildParameter( std::string name, NodeId obj, ParameterKind kind );
  NodeId buildPrint( bool nl, NodeId dest, NodeId expression_list );
  NodeId buildPass( );
  NodeId buildAssert( NodeId test, NodeId msg );
  NodeId buildExec( NodeId expression, NodeId globals, NodeId locals );
  NodeId buildReturn( NodeId expression );
  NodeId buildIf( NodeId test, NodeId body, NodeId else_body );
  NodeId buildImportStatement( std::vector<NodeId>& names );
  NodeId buildImportFrom( std::vector<NodeId>& names, std::string module_name, int level );
  NodeId buildHandler( NodeId type, NodeId name, NodeId body );
  NodeId buildContinue( );
  NodeId buildDelete( NodeId list );
  NodeId buildAssign( NodeId list, NodeId expression );
  NodeId buildFunctionDef( std::string name, NodeId docstring, NodeId body, std::vector<NodeId>& parameter_list, std::vector<NodeId>& decorator_list, std::vector<NodeId>& local_object, NodeId object, int lloc );
  NodeId buildGlobal( std::vector<NodeId>& identifier );
  NodeId buildWith( NodeId body, NodeId target, NodeId expression );
  NodeId buildWhile( NodeId test, NodeId body, NodeId else_body );
  NodeId buildTryFinal( NodeId body, NodeId finally_body );
  NodeId buildAugAssign( NodeId target_list, NodeId expression, AssignmentKind kind );
  NodeId buildClassDef( std::string name, NodeId docstring, NodeId body, std::vector<NodeId>& base, std::vector<NodeId>& decorator_list, std::vector<NodeId>& local_object, NodeId object, int lloc );
  NodeId buildTryExcept( std::vector<NodeId>& handlerl, NodeId body, NodeId else_body );
  NodeId buildFor( NodeId target_list, NodeId body, NodeId else_body, NodeId expression_list );
  NodeId buildAlias( std::string name, std::string alias );
  NodeId buildKeyValue( NodeId key, NodeId value );
  NodeId buildIfExpression( NodeId test, NodeId body, NodeId else_body );
  NodeId buildExpressionList( std::vector<NodeId>& list, bool yield );
  NodeId buildStringLiteral( std::string value );
  NodeId buildDocstring( std::string value );
  NodeId buildComment( std::string value );
  NodeId buildKeyword( NodeId identifier, NodeId keyword );
  NodeId buildListComp( NodeId expression, std::vector<NodeId>& generators );
  NodeId buildIdentifier( std::string name, NodeId object );
  NodeId buildLambda( std::vector<NodeId>& parameter_list, std::vector<NodeId>& object_list, NodeId expression);
  NodeId buildFloatNumber( float value );
  NodeId buildImagNumber( double im, double real );
  NodeId buildGeneratorExpression( NodeId expr, std::vector<NodeId>& generators );
  NodeId buildAttributeRef( NodeId identifier, NodeId primary );
  NodeId buildIntegerLiteral( int value );
  NodeId buildBinaryLogical( std::vector<NodeId>& operands, BinaryLogicalKind kind );
  NodeId buildSlice( NodeId upper_bound, NodeId lower_bound, NodeId stride );
  NodeId buildLongInteger( int value );
  NodeId buildCall( NodeId argument_list, NodeId primary );
  NodeId buildSubscription( NodeId slicing, NodeId primary );
  NodeId buildList( std::vector<NodeId>& expression_list, bool isTuple );
  NodeId buildBinaryArithmetic(  NodeId left, NodeId right, BinaryArithmeticKind kind );
  NodeId buildUnaryOperation( NodeId expr, UnaryKind kind );
  NodeId buildExtSlice( std::vector<NodeId>& slice_item, NodeId primary );
  NodeId buildCompare( NodeId left, std::vector<NodeId>& operands, std::vector<BinaryLogicalKind>& kinds );
  NodeId buildStringConversion( NodeId expression_list );
  NodeId buildYield( NodeId expression_list );
  NodeId buildDictionary( std::vector<NodeId>& key_value_list );
  NodeId buildGenerator( NodeId identifier, NodeId iter, std::vector<NodeId>& ifexp );
  NodeId buildEllipsis( );
  NodeId buildIndex( NodeId value );
  NodeId buildArgumentList( NodeId list, std::vector<NodeId>& keyword_arg, NodeId dictionary_arg, NodeId tuple_arg );

  // python 2.7 features
  NodeId buildSet( std::vector<NodeId>& expression_list );
  NodeId buildSetComp( NodeId expression, std::vector<NodeId>& generators );
  NodeId buildDictComp( NodeId key_value, std::vector<NodeId>& generators );

};
}

#endif