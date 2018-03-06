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

#include "../inc/PBuilder.h"
#include "../inc/messages.h"
#include <fstream>
#include <iostream>

using namespace std;

PBuilder::PBuilder(Factory* factory, bool package_build): factory(factory), package_build(package_build){
}

Factory* PBuilder::getFactory(){
  return factory;
}

void PBuilder::setPath(std::string& path) {
  this->path = path;
}

void PBuilder::setIncreasedPosition(NodeId id, unsigned line, unsigned col, unsigned endline, unsigned endcol){
  setPosition(id, line, col+1, endline, endcol);
}

void PBuilder::setPosition(NodeId id, unsigned line, unsigned col, unsigned endline, unsigned endcol){
  base::Positioned& node = dynamic_cast<base::Positioned&>(factory->getRef(id));
  node.setPosition(Range(factory->getStringTable(), path, line, col, endline, endcol));
}

NodeId PBuilder::findPackage( std::string name ){
  NodeId return_id = 0;
  NodeId node_id = factory->getRoot()->getId();
  while(name.find_first_of("\\/") != std::string::npos){
    module::Package& package = dynamic_cast<module::Package&>(factory->getRef(node_id));
    std::string pname = name.substr(0, name.find_first_of("\\/"));
    if(pname.length() == 0){
      name = "";
      break;
    }
    ListIterator<module::Package> lit = package.getPackageListIteratorBegin();

    bool find = false;
    for(; lit != package.getPackageListIteratorEnd(); ++lit){
      const module::Package& chpackage = *lit;
      if(pname.compare(chpackage.getName()) == 0){
        node_id = chpackage.getId();
        find = true;
        break;
      }
    }
    if(!find)
      break;
    size_t size = name.find_first_of("\\/")+1;
    name = name.substr(size, name.length()-size);
  }
  if(name.find_first_of("\\/") == std::string::npos)
      return_id = node_id;

  return return_id;
}

NodeId PBuilder::buildPackage( std::string name, std::vector<NodeId>& packages ){
  NodeId node_id = factory->getRoot()->getId();
  std::string path;
  while(name.find_first_of("\\/") != std::string::npos){
    module::Package& package = dynamic_cast<module::Package&>(factory->getRef(node_id));
    std::string pname = name.substr(0, name.find_first_of("\\/"));
    if(pname.length() == 0)
      break;

    if (path.size() != 0) {
      path += "/";
    }
    path += pname;
    std::string init_path = path + "/__init__.py";
    ifstream init(init_path.c_str());
    if(init.is_open() || package_build){
      ListIterator<module::Package> lit = package.getPackageListIteratorBegin();

      bool build = true;
      for(; lit != package.getPackageListIteratorEnd(); ++lit){
        const module::Package& chpackage = *lit;
        if(pname.compare(chpackage.getName()) == 0){
          node_id = chpackage.getId();
          build = false;
          break;
        }
      }
      
      if(build){
        module::Package& new_package = dynamic_cast<module::Package&>(*factory->createNode(ndkPackage));
        
        new_package.setName(pname);
        package.addPackage(new_package.getId());
        node_id = new_package.getId();
      }
    }
    size_t size = name.find_first_of("\\/")+1;
    name = name.substr(size, name.length()-size);
  }

  module::Package& package = dynamic_cast<module::Package&>(factory->getRef(node_id));
  for(vector<NodeId>::iterator it = packages.begin(); it != packages.end(); it++){
    package.addPackage(*it);
  }

  return node_id;
}

NodeId PBuilder::buildPackage( std::string name, NodeId parent ){
  module::Package& node = dynamic_cast<module::Package&>(*factory->createNode(ndkPackage));
  node.setName(name);
  if(parent != 0){
    module::Package& parnode = dynamic_cast<module::Package&>(factory->getRef(parent));
    parnode.addPackage(node.getId());
  }

  return node.getId();
}

NodeId PBuilder::AddModule( NodeId module, NodeId package ){
  module::Package& node = dynamic_cast<module::Package&>(factory->getRef(package));
  node.addModule(module);
  return node.getId();
}

void PBuilder::AddObjectRef( NodeId object, NodeId ref ){
  module::Object& node = dynamic_cast<module::Object&>(factory->getRef(object));
  node.addRefersTo(ref);
}

NodeId PBuilder::buildSuite( std::vector<NodeId>& body ){
  statement::Suite& node = dynamic_cast<statement::Suite&>(*factory->createNode(ndkSuite));

  for(vector<NodeId>::iterator it = body.begin(); it != body.end(); it++){
    node.addStatement(*it);
  }

  if (!body.empty()) {
    base::Positioned& first = dynamic_cast<base::Positioned&>(factory->getRef(body.front()));
    base::Positioned& last = dynamic_cast<base::Positioned&>(factory->getRef(body.back()));

    setPosition(node.getId(), first.getPosition().getLine(), first.getPosition().getCol(), last.getPosition().getEndLine(), last.getPosition().getEndCol());
  }

  return node.getId();
}
 
NodeId PBuilder::buildModule( std::string name, NodeId docstring, std::vector<NodeId>& body, std::vector<NodeId>& object, int lloc ){
  module::Module& node = dynamic_cast<module::Module&>(*factory->createNode(ndkModule));
  node.setName(name);
  if (docstring){
    node.setDocstring(docstring);
  }
  for(vector<NodeId>::iterator it = body.begin(); it != body.end(); it++){
    node.addStatement(*it);
  }
  for(vector<NodeId>::iterator it = object.begin(); it != object.end(); it++){
    node.addObject(*it);
  }

  node.setLloc(lloc);

  return node.getId();
}

NodeId PBuilder::buildObject( std::string& name ){
  module::Object& node = dynamic_cast<module::Object&>(*factory->createNode(ndkObject));
  node.setName(name);
  return node.getId();
}

NodeId PBuilder::buildBaseSpecifier( NodeId name ){
  statement::BaseSpecifier& node = dynamic_cast<statement::BaseSpecifier&>(*factory->createNode(ndkBaseSpecifier));
  if (name != 0) {
    node.setName(name);
  }
  return node.getId();
}

NodeId PBuilder::buildBreak( ){
  statement::Break& node = dynamic_cast<statement::Break&>(*factory->createNode(ndkBreak));
  return node.getId();
}

NodeId PBuilder::buildTargetList( std::vector<NodeId>& list ){
  statement::TargetList& node = dynamic_cast<statement::TargetList&>(*factory->createNode(ndkTargetList));
  for(vector<NodeId>::iterator it = list.begin(); it != list.end(); it++){
      node.addTarget(*it);
  }

  if (!list.empty()) {
    base::Positioned& first = dynamic_cast<base::Positioned&>(factory->getRef(list.front()));
    base::Positioned& last = dynamic_cast<base::Positioned&>(factory->getRef(list.back()));

    setPosition(node.getId(), first.getPosition().getLine(), first.getPosition().getCol(), last.getPosition().getEndLine(), last.getPosition().getEndCol());
  }
  
  return node.getId();
}

NodeId PBuilder::buildRaise( NodeId type, NodeId value, NodeId traceback ){
  statement::Raise& node = dynamic_cast<statement::Raise&>(*factory->createNode(ndkRaise));
  node.setTypeExpression(type);
  node.setValueExpression(value);
  node.setTracebackExpression(traceback);
  return node.getId();
}

NodeId PBuilder::buildParameter( std::string name, NodeId obj, ParameterKind kind ){
  statement::Parameter& node = dynamic_cast<statement::Parameter&>(*factory->createNode(ndkParameter));
  node.setName(name);
  node.setKind(kind);
  if(obj != 0) node.setRefersTo(obj);
  return node.getId();
}

NodeId PBuilder::buildPrint( bool nl, NodeId dest, NodeId expression_list ){
  statement::Print& node = dynamic_cast<statement::Print&>(*factory->createNode(ndkPrint));
  node.setNl(nl);
  node.setExpressionList(expression_list);
  node.setDestination(dest);
  return node.getId();
}

NodeId PBuilder::buildPass( ){
  statement::Pass& node = dynamic_cast<statement::Pass&>(*factory->createNode(ndkPass));
  return node.getId();
}

NodeId PBuilder::buildAssert( NodeId test, NodeId msg ){
  statement::Assert& node = dynamic_cast<statement::Assert&>(*factory->createNode(ndkAssert));
  node.setTestExpression(test);
  node.setMsgExpression(msg);
  return node.getId();
}

NodeId PBuilder::buildExec( NodeId expression, NodeId globals, NodeId locals ){
  statement::Exec& node = dynamic_cast<statement::Exec&>(*factory->createNode(ndkExec));
  node.setExpression(expression);
  if(globals != 0) node.setGlobals(globals);
  if(locals != 0) node.setLocals(locals);
  return node.getId();
}

NodeId PBuilder::buildReturn( NodeId expression ){
  statement::Return& node = dynamic_cast<statement::Return&>(*factory->createNode(ndkReturn));
  node.setExpression(expression);
  return node.getId();
}

NodeId PBuilder::buildIf( NodeId test, NodeId body, NodeId else_body ){
  statement::If& node = dynamic_cast<statement::If&>(*factory->createNode(ndkIf));
  node.setBody(body);
  if(else_body != 0) node.setElseBody(else_body);
  node.setTestExpression(test);
  return node.getId();
}

NodeId PBuilder::buildImportStatement( std::vector<NodeId>& names ){
  statement::ImportStatement& node = dynamic_cast<statement::ImportStatement&>(*factory->createNode(ndkImportStatement));
  for(vector<NodeId>::iterator it = names.begin(); it != names.end(); it++){
    node.addAlias(*it);
  }
  return node.getId();
}

NodeId PBuilder::buildImportFrom( std::vector<NodeId>& names, std::string module_name, int level ){
  statement::ImportFrom& node = dynamic_cast<statement::ImportFrom&>(*factory->createNode(ndkImportFrom));
  for(vector<NodeId>::iterator it = names.begin(); it != names.end(); it++){
    node.addAlias(*it);
  }
  node.setModulname(module_name);
  node.setLevel(level);
  return node.getId();
}

NodeId PBuilder::buildHandler( NodeId type, NodeId name, NodeId body ){
  statement::Handler& node = dynamic_cast<statement::Handler&>(*factory->createNode(ndkHandler));
  node.setExceptBody(body);
  if(type != 0) node.setType(type);
  if (name != 0) node.setName(name);

  return node.getId();
}

NodeId PBuilder::buildContinue( ){
  statement::Continue& node = dynamic_cast<statement::Continue&>(*factory->createNode(ndkContinue));
  return node.getId();
}

NodeId PBuilder::buildDelete( NodeId list ){
  statement::Delete& node = dynamic_cast<statement::Delete&>(*factory->createNode(ndkDelete));
  node.setTargetList(list);
  return node.getId();
}

NodeId PBuilder::buildAssign( NodeId list, NodeId expression ){
  statement::Assign& node = dynamic_cast<statement::Assign&>(*factory->createNode(ndkAssign));
  node.setTargetList(list);
  node.setExpression(expression);
  return node.getId();
}

NodeId PBuilder::buildFunctionDef( std::string name, NodeId docstring, NodeId body, std::vector<NodeId>& parameter_list, std::vector<NodeId>& decorator_list, std::vector<NodeId>& local_object, NodeId object, int lloc ){
  statement::FunctionDef& node = dynamic_cast<statement::FunctionDef&>(*factory->createNode(ndkFunctionDef));
  node.setBody(body);
  node.setName(name);
  if (docstring){
    node.setDocstring(docstring);
  }
  for(vector<NodeId>::iterator it = parameter_list.begin(); it != parameter_list.end(); it++){
    node.addParameter(*it);
  }
  for(vector<NodeId>::iterator it = decorator_list.begin(); it != decorator_list.end(); it++){
    node.addDecorator(*it);
  }
  for(vector<NodeId>::iterator it = local_object.begin(); it != local_object.end(); it++){
    node.addObject(*it);
  }

  node.setLloc(lloc);

  node.setRefersTo(object);

  return node.getId();
}

NodeId PBuilder::buildGlobal( std::vector<NodeId>& identifier ){
  statement::Global& node = dynamic_cast<statement::Global&>(*factory->createNode(ndkGlobal));
  for(vector<NodeId>::iterator it = identifier.begin(); it != identifier.end(); it++){
    node.addIdentifier(*it);
  }
  return node.getId();
}

NodeId PBuilder::buildWith( NodeId body, NodeId target, NodeId expression ){
  statement::With& node = dynamic_cast<statement::With&>(*factory->createNode(ndkWith));
  node.setBody(body);

  vector<NodeId> targets;
  if (target) targets.push_back(target);
  node.setTargetList(buildTargetList(targets));

  node.setExpression(expression);
  return node.getId();
}

NodeId PBuilder::buildWhile( NodeId test, NodeId body, NodeId else_body ){
  statement::While& node = dynamic_cast<statement::While&>(*factory->createNode(ndkWhile));
  node.setTestExpression(test);
  node.setBody(body);
  if(else_body != 0) node.setElseBody(else_body);
  return node.getId();
}

NodeId PBuilder::buildTryFinal( NodeId body, NodeId finally_body ){
  statement::TryFinal& node = dynamic_cast<statement::TryFinal&>(*factory->createNode(ndkTryFinal));
  node.setBody(body);
  if(finally_body != 0) node.setFinallyBody(finally_body);
  return node.getId();
}

NodeId PBuilder::buildAugAssign( NodeId target_list, NodeId expression, AssignmentKind kind ){
  statement::AugAssign& node = dynamic_cast<statement::AugAssign&>(*factory->createNode(ndkAugAssign));
  node.setTargetList(target_list);
  node.setExpression(expression);
  node.setKind(kind);
  return node.getId();
}

NodeId PBuilder::buildClassDef( std::string name, NodeId docstring, NodeId body, std::vector<NodeId>& base, std::vector<NodeId>& decorator_list, std::vector<NodeId>& local_object, NodeId object, int lloc ){
  statement::ClassDef& node = dynamic_cast<statement::ClassDef&>(*factory->createNode(ndkClassDef));
  node.setBody(body);
  node.setName(name);
  if (docstring){
    node.setDocstring(docstring);
  }
  for(vector<NodeId>::iterator it = base.begin(); it != base.end(); it++){
    node.addBaseSpecifier(*it);
  }
  for(vector<NodeId>::iterator it = decorator_list.begin(); it != decorator_list.end(); it++){
    node.addDecorator(*it);
  }
  for(vector<NodeId>::iterator it = local_object.begin(); it != local_object.end(); it++){
    node.addObject(*it);
  }

  node.setLloc(lloc);

  node.setRefersTo(object);
  return node.getId();
}

NodeId PBuilder::buildTryExcept( std::vector<NodeId>& handlerl, NodeId body, NodeId else_body ){
  statement::TryExcept& node = dynamic_cast<statement::TryExcept&>(*factory->createNode(ndkTryExcept));
  
  for(vector<NodeId>::iterator it = handlerl.begin(); it != handlerl.end(); it++){
    node.addHandler(*it);
  }

  if(body != 0) node.setBody(body);
  if(else_body != 0) node.setElseBody(else_body);
  return node.getId();
}

NodeId PBuilder::buildFor(NodeId target_list, NodeId body, NodeId else_body, NodeId expression_list ){
  statement::For& node = dynamic_cast<statement::For&>(*factory->createNode(ndkFor));
  node.setBody(body);
  if(else_body != 0) node.setElseBody(else_body);
  node.setTargetList(target_list);
  node.setExpressionList(expression_list);
  return node.getId();
}

NodeId PBuilder::buildAlias( std::string name, std::string alias ){
  statement::Alias& node = dynamic_cast<statement::Alias&>(*factory->createNode(ndkAlias));
  node.setName(name);
  node.setAlias(alias);
  return node.getId();
}

NodeId PBuilder::buildKeyValue( NodeId key, NodeId value ){
  expression::KeyValue& node = dynamic_cast<expression::KeyValue&>(*factory->createNode(ndkKeyValue));
  node.setKey(key);
  node.setValue(value);

  if (key != 0)
  {
    base::Positioned& first = dynamic_cast<base::Positioned&>(factory->getRef(key));
    base::Positioned& last = dynamic_cast<base::Positioned&>(factory->getRef(value));

    setPosition(node.getId(), first.getPosition().getLine(), first.getPosition().getCol(), last.getPosition().getEndLine(), last.getPosition().getEndCol());
  }

  return node.getId();
}

NodeId PBuilder::buildIfExpression( NodeId test, NodeId body, NodeId else_body ){
  expression::IfExpression& node = dynamic_cast<expression::IfExpression&>(*factory->createNode(ndkIfExpression));
  node.setTest(test);
  node.setBody(body);
  node.setElseBody(else_body);
  return node.getId();
}

NodeId PBuilder::buildExpressionList( std::vector<NodeId>& list, bool yield ){
  expression::ExpressionList& node = dynamic_cast<expression::ExpressionList&>(*factory->createNode(ndkExpressionList));
  node.setIsYieldExpression(yield);
  for(vector<NodeId>::iterator it = list.begin(); it != list.end(); it++){
    node.addExpression(*it);
  }

   if (!list.empty()) {
    expression::Expression& first = dynamic_cast<expression::Expression&>(factory->getRef(list.front()));
    expression::Expression& last = dynamic_cast<expression::Expression&>(factory->getRef(list.back()));

    setPosition(node.getId(), first.getPosition().getLine(), first.getPosition().getCol(), last.getPosition().getEndLine(), last.getPosition().getEndCol());
  }

  return node.getId();
}

NodeId PBuilder::buildArgumentList( NodeId list, std::vector<NodeId>& keyword_arg, NodeId dictionary_arg, NodeId tuple_arg ){
  expression::ArgumentList& node = dynamic_cast<expression::ArgumentList&>(*factory->createNode(ndkArgumentList));
  if(list != 0) node.setPositionalArguments(list);
  if(dictionary_arg != 0) node.setDictionary(dictionary_arg);
  for(vector<NodeId>::iterator it = keyword_arg.begin(); it != keyword_arg.end(); it++){
    node.addKeyword(*it);
  }
  if(tuple_arg != 0) node.setTuple(tuple_arg);

  return node.getId();
}

NodeId PBuilder::buildStringLiteral( std::string value ){
  expression::StringLiteral& node = dynamic_cast<expression::StringLiteral&>(*factory->createNode(ndkStringLiteral));
  node.setValue(value);
  return node.getId();
}

NodeId PBuilder::buildDocstring( std::string value ){
  base::Docstring& node = factory->createDocstring();
  node.setText(value);
  return node.getId();
}

NodeId PBuilder::buildComment( std::string value ){
  base::Comment& node = dynamic_cast<base::Comment&>(factory->createComment());
  node.setText(value);
  return node.getId();
}

NodeId PBuilder::buildKeyword( NodeId identifier, NodeId keyword ){
  expression::Keyword& node = dynamic_cast<expression::Keyword&>(*factory->createNode(ndkKeyword));
  node.setKey(identifier);
  node.setValue(keyword);
  return node.getId();
}

NodeId PBuilder::buildListComp( NodeId expression, std::vector<NodeId>& generators  ){
  expression::ListComp& node = dynamic_cast<expression::ListComp&>(*factory->createNode(ndkListComp));
  node.setExpression(expression);
  for(vector<NodeId>::iterator it = generators.begin(); it != generators.end(); it++){
    node.addGenerator(*it);
  }

 if (!generators.empty()) {
    base::Positioned& first = dynamic_cast<base::Positioned&>(factory->getRef(generators.front()));
    base::Positioned& last = dynamic_cast<base::Positioned&>(factory->getRef(generators.back()));

    setPosition(node.getId(), first.getPosition().getLine(), first.getPosition().getCol(), last.getPosition().getEndLine(), last.getPosition().getEndCol());
  }

  return node.getId();
}

NodeId PBuilder::buildIdentifier( std::string name, NodeId object ){
  expression::Identifier& node = dynamic_cast<expression::Identifier&>(*factory->createNode(ndkIdentifier));
  node.setName(name);
  if(object != 0)
    node.setRefersTo(object);
  return node.getId();
}


NodeId PBuilder::buildLambda( std::vector<NodeId>& parameter_list, std::vector<NodeId>& object_list, NodeId expression ){
  expression::Lambda& node = dynamic_cast<expression::Lambda&>(*factory->createNode(ndkLambda));
  if (Common::getIsExpression(factory->getRef(expression)))
    node.setExpression(expression);
  for(vector<NodeId>::iterator it = parameter_list.begin(); it != parameter_list.end(); it++){
    node.addParameter(*it);
  }
  for(vector<NodeId>::iterator it = object_list.begin(); it != object_list.end(); it++){
    node.addObject(*it);
  }
  return node.getId();
}

NodeId PBuilder::buildFloatNumber( float value ){
  expression::FloatNumber& node = dynamic_cast<expression::FloatNumber&>(*factory->createNode(ndkFloatNumber));
  node.setValue(value);
  return node.getId();
}

NodeId PBuilder::buildImagNumber( double im, double real ){
  expression::ImagNumber& node = dynamic_cast<expression::ImagNumber&>(*factory->createNode(ndkImagNumber));
  node.setIm(im);
  node.setReal(real);
  return node.getId();
}

NodeId PBuilder::buildGeneratorExpression( NodeId expr, std::vector<NodeId>& generators ){
  expression::GeneratorExpression& node = dynamic_cast<expression::GeneratorExpression&>(*factory->createNode(ndkGeneratorExpression));
  node.setExpression(expr);
  for(vector<NodeId>::iterator it = generators.begin(); it != generators.end(); it++){
    node.addGenerator(*it);
  }

  if (!generators.empty()) {
    base::Positioned& first = dynamic_cast<base::Positioned&>(factory->getRef(generators.front()));
    base::Positioned& last = dynamic_cast<base::Positioned&>(factory->getRef(generators.back()));

    setPosition(node.getId(), first.getPosition().getLine(), first.getPosition().getCol(), last.getPosition().getEndLine(), last.getPosition().getEndCol());
  }

  return node.getId();
}

NodeId PBuilder::buildAttributeRef( NodeId identifier, NodeId primary ){
  expression::AttributeRef& node = dynamic_cast<expression::AttributeRef&>(*factory->createNode(ndkAttributeRef));
  node.setRightExpression(identifier);
  if(primary != 0) node.setLeftExpression(primary);
  return node.getId();
}

NodeId PBuilder::buildIntegerLiteral( int value ){
  expression::IntegerLiteral& node = dynamic_cast<expression::IntegerLiteral&>(*factory->createNode(ndkIntegerLiteral));
  node.setValue(value);
  return node.getId();
}

NodeId PBuilder::buildBinaryLogical( std::vector<NodeId>& operands, BinaryLogicalKind kind ){
  size_t numOperands = operands.size();
  if (numOperands < 2)
    throw PythonException(COLUMBUS_LOCATION, CMSG_EX_WRONG_NUM_OP);

  expression::BinaryLogical *expr = NULL;
  expression::BinaryLogical *tmp = NULL;
  for (size_t i = 1; i < numOperands; ++i) {
    expr = dynamic_cast<expression::BinaryLogical*>(factory->createNode(ndkBinaryLogical));
    if (tmp)
      expr->setLeftExpression(tmp->getId());
    else
      expr->setLeftExpression(operands[i-1]);
    expr->setRightExpression(operands[i]);
    expr->setKind(kind);
    tmp = expr;
  }
  return expr->getId();
}

NodeId PBuilder::buildSlice( NodeId upper_bound, NodeId lower_bound, NodeId stride ){
  expression::Slice& node = dynamic_cast<expression::Slice&>(*factory->createNode(ndkSlice));
  if(upper_bound != 0) node.setUpperBound(upper_bound);
  if(lower_bound != 0) node.setLowerBound(lower_bound);
  if(stride != 0) node.setStride(stride);
  return node.getId();
}

NodeId PBuilder::buildLongInteger( int value ){
  expression::LongInteger& node = dynamic_cast<expression::LongInteger&>(*factory->createNode(ndkLongInteger));
  node.setValue(value);
  return node.getId();
}

NodeId PBuilder::buildCall( NodeId argument_list, NodeId primary ){
  expression::Call& node = dynamic_cast<expression::Call&>(*factory->createNode(ndkCall));
  node.setArgumentList(argument_list);
  if(primary != 0) node.setExpression(primary);
  return node.getId();
}

NodeId PBuilder::buildSubscription( NodeId slice, NodeId value ){
  expression::Subscription& node = dynamic_cast<expression::Subscription&>(*factory->createNode(ndkSubscription));
  node.setSlicing(slice);
  if(value != 0) node.setExpression(value);
  return node.getId();
}

NodeId PBuilder::buildList( vector<NodeId>& expression_list, bool isTuple ){
  expression::List& node = dynamic_cast<expression::List&>(*factory->createNode(ndkList));
  node.setIsTuple(isTuple);
  for(vector<NodeId>::iterator it = expression_list.begin(); it != expression_list.end(); it++){
    node.addExpression(*it);
  }
  return node.getId();
}

NodeId PBuilder::buildBinaryArithmetic( NodeId left, NodeId right, BinaryArithmeticKind kind ){
  expression::BinaryArithmetic& node = dynamic_cast<expression::BinaryArithmetic&>(*factory->createNode(ndkBinaryArithmetic));
  node.setLeftExpression(left);
  node.setRightExpression(right);
  node.setKind(kind);
  return node.getId();
}

NodeId PBuilder::buildUnaryOperation( NodeId expr, UnaryKind kind ){
  expression::UnaryOperation& node = dynamic_cast<expression::UnaryOperation&>(*factory->createNode(ndkUnaryOperation));
  node.setExpression(expr);
  node.setKind(kind);
  return node.getId();
}

NodeId PBuilder::buildExtSlice( vector<NodeId>& slice_item, NodeId primary ){
  expression::ExtSlice& node = dynamic_cast<expression::ExtSlice&>(*factory->createNode(ndkExtSlice));
  for(vector<NodeId>::iterator it = slice_item.begin(); it != slice_item.end(); it++){
    node.addItem(*it);
  }

  if (!slice_item.empty()) {
    base::Positioned& first = dynamic_cast<base::Positioned&>(factory->getRef(slice_item.front()));
    base::Positioned& last = dynamic_cast<base::Positioned&>(factory->getRef(slice_item.back()));

    setPosition(node.getId(), first.getPosition().getLine(), first.getPosition().getCol(), last.getPosition().getEndLine(), last.getPosition().getEndCol());
  }

  if(primary != 0) node.setExpression(primary);
  return node.getId();
}

NodeId PBuilder::buildCompare( NodeId left, std::vector<NodeId>& operands, std::vector<BinaryLogicalKind>& kinds ){
  size_t numOperands = operands.size();
  size_t numOps = kinds.size();
  if (numOperands == 0 || numOperands != numOps)
    throw PythonException(COLUMBUS_LOCATION, CMSG_EX_WRONG_NUM_OP_OR_OP);

  expression::BinaryLogical *expr = NULL;
  expression::BinaryLogical *tmp = NULL;
  for (size_t i = 0; i < numOperands; ++i) {
    expr = dynamic_cast<expression::BinaryLogical*>(factory->createNode(ndkBinaryLogical));
    if (tmp)
      expr->setLeftExpression(tmp->getId());
    else
      expr->setLeftExpression(left);
    expr->setRightExpression(operands[i]);
    expr->setKind(kinds[i]);
    tmp = expr;
  }
  return expr->getId();
}

NodeId PBuilder::buildStringConversion( NodeId expression_list ){
  expression::StringConversion& node = dynamic_cast<expression::StringConversion&>(*factory->createNode(ndkStringConversion));
  node.setExpressionList(expression_list);
  return node.getId();
}

NodeId PBuilder::buildYield( NodeId expression_list ){
  expression::YieldExpression& node = dynamic_cast<expression::YieldExpression&>(*factory->createNode(ndkYieldExpression));
  node.setYieldExpression(expression_list);
  return node.getId();
}

NodeId PBuilder::buildDictionary( std::vector<NodeId>& key_value_list ){
  expression::Dictionary& node = dynamic_cast<expression::Dictionary&>(*factory->createNode(ndkDictionary));
  for(vector<NodeId>::iterator it = key_value_list.begin(); it != key_value_list.end(); it++){
    node.addKeyValue(*it);
  }
  return node.getId();
}

NodeId PBuilder::buildGenerator( NodeId identifier, NodeId iter, std::vector<NodeId>& ifexp ){
  expression::Generator& node = dynamic_cast<expression::Generator&>(*factory->createNode(ndkGenerator));
  node.setTarget(identifier);
  node.setIter(iter);
  for(vector<NodeId>::iterator it = ifexp.begin(); it != ifexp.end(); it++){
    node.addCondition(*it);
  }
  return node.getId();
}

NodeId PBuilder::buildEllipsis( ){
  expression::Ellipsis& node = dynamic_cast<expression::Ellipsis&>(*factory->createNode(ndkEllipsis));
  return node.getId();
}

NodeId PBuilder::buildIndex( NodeId value ){
  expression::Index& node = dynamic_cast<expression::Index&>(*factory->createNode(ndkIndex));
  node.setExpression(value);
  return node.getId();
}

NodeId PBuilder::buildSet( std::vector<NodeId>& expression_list ) {
  expression::Set& node = dynamic_cast<expression::Set&>(*factory->createNode(ndkSet));
  for (vector<NodeId>::iterator it = expression_list.begin(); it != expression_list.end(); ++it) {
    node.addExpression(*it);
  }
  return node.getId();
}

NodeId PBuilder::buildSetComp( NodeId expression, std::vector<NodeId>& generators ) {
  expression::SetComp& node = dynamic_cast<expression::SetComp&>(*factory->createNode(ndkSetComp));
  if (expression) node.setExpression(expression);
  for (vector<NodeId>::iterator it = generators.begin(); it != generators.end(); ++it) {
    node.addGenerator(*it);
  }
  return node.getId();
}

NodeId PBuilder::buildDictComp( NodeId key_value, std::vector<NodeId>& generators ) {
  expression::DictComp& node = dynamic_cast<expression::DictComp&>(*factory->createNode(ndkDictComp));
  if (key_value) node.setKeyValue(key_value);
  for (vector<NodeId>::iterator it = generators.begin(); it != generators.end(); ++it) {
    node.addGenerator(*it);
  }
  return node.getId();
}


