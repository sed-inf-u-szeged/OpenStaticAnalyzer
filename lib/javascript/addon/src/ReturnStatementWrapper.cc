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

#include "../inc/ReturnStatementWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> ReturnStatementWrapper::constructor;

void ReturnStatementWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "ReturnStatementWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentArrayExpression", setArgumentArrayExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentArrowFunctionExpression", setArgumentArrowFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentAssignmentExpression", setArgumentAssignmentExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentAwaitExpression", setArgumentAwaitExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentBinaryExpression", setArgumentBinaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentCallExpression", setArgumentCallExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentClassExpression", setArgumentClassExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentConditionalExpression", setArgumentConditionalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentFunctionExpression", setArgumentFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentIdentifier", setArgumentIdentifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentBooleanLiteral", setArgumentBooleanLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentNullLiteral", setArgumentNullLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentNumberLiteral", setArgumentNumberLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentRegExpLiteral", setArgumentRegExpLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentStringLiteral", setArgumentStringLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentLogicalExpression", setArgumentLogicalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentMemberExpression", setArgumentMemberExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentMetaProperty", setArgumentMetaProperty);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentNewExpression", setArgumentNewExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentObjectExpression", setArgumentObjectExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentSequenceExpression", setArgumentSequenceExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentTaggedTemplateExpression", setArgumentTaggedTemplateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentTemplateLiteral", setArgumentTemplateLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentThisExpression", setArgumentThisExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentUnaryExpression", setArgumentUnaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentUpdateExpression", setArgumentUpdateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setArgumentYieldExpression", setArgumentYieldExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addCommentsComment", addCommentsComment);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setPath", setPath);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLine", setLine);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setCol", setCol);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setEndLine", setEndLine);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setEndCol", setEndCol);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setWideLine", setWideLine);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setWideCol", setWideCol);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setWideEndLine", setWideEndLine);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setWideEndCol", setWideEndCol);
                                                                           
  constructor.Reset(isolate, tpl->GetFunction());                          
  exports->Set(v8::String::NewFromUtf8(isolate, "ReturnStatementWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void ReturnStatementWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new ReturnStatementWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    ReturnStatementWrapper* obj = new ReturnStatementWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `ReturnStatementWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


ReturnStatementWrapper::ReturnStatementWrapper(Factory* fact)                        
{                                                   
  ReturnStatement = fact->getFactory()->createReturnStatementNode();          
}                                                   

ReturnStatementWrapper::~ReturnStatementWrapper()
{        
}        

void ReturnStatementWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void ReturnStatementWrapper::setArgumentArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  ReturnStatementWrapper* _ReturnStatement2 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args.This());

  _ReturnStatement2->ReturnStatement->setArgument(_ArrayExpression1->ArrayExpression);
}
void ReturnStatementWrapper::setArgumentArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  ReturnStatementWrapper* _ReturnStatement2 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args.This());

  _ReturnStatement2->ReturnStatement->setArgument(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void ReturnStatementWrapper::setArgumentAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  ReturnStatementWrapper* _ReturnStatement2 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args.This());

  _ReturnStatement2->ReturnStatement->setArgument(_AssignmentExpression1->AssignmentExpression);
}
void ReturnStatementWrapper::setArgumentAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  ReturnStatementWrapper* _ReturnStatement2 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args.This());

  _ReturnStatement2->ReturnStatement->setArgument(_AwaitExpression1->AwaitExpression);
}
void ReturnStatementWrapper::setArgumentBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  ReturnStatementWrapper* _ReturnStatement2 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args.This());

  _ReturnStatement2->ReturnStatement->setArgument(_BinaryExpression1->BinaryExpression);
}
void ReturnStatementWrapper::setArgumentCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  ReturnStatementWrapper* _ReturnStatement2 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args.This());

  _ReturnStatement2->ReturnStatement->setArgument(_CallExpression1->CallExpression);
}
void ReturnStatementWrapper::setArgumentClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  ReturnStatementWrapper* _ReturnStatement2 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args.This());

  _ReturnStatement2->ReturnStatement->setArgument(_ClassExpression1->ClassExpression);
}
void ReturnStatementWrapper::setArgumentConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  ReturnStatementWrapper* _ReturnStatement2 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args.This());

  _ReturnStatement2->ReturnStatement->setArgument(_ConditionalExpression1->ConditionalExpression);
}
void ReturnStatementWrapper::setArgumentFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  ReturnStatementWrapper* _ReturnStatement2 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args.This());

  _ReturnStatement2->ReturnStatement->setArgument(_FunctionExpression1->FunctionExpression);
}
void ReturnStatementWrapper::setArgumentIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  ReturnStatementWrapper* _ReturnStatement2 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args.This());

  _ReturnStatement2->ReturnStatement->setArgument(_Identifier1->Identifier);
}
void ReturnStatementWrapper::setArgumentBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  ReturnStatementWrapper* _ReturnStatement2 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args.This());

  _ReturnStatement2->ReturnStatement->setArgument(_BooleanLiteral1->BooleanLiteral);
}
void ReturnStatementWrapper::setArgumentNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  ReturnStatementWrapper* _ReturnStatement2 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args.This());

  _ReturnStatement2->ReturnStatement->setArgument(_NullLiteral1->NullLiteral);
}
void ReturnStatementWrapper::setArgumentNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  ReturnStatementWrapper* _ReturnStatement2 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args.This());

  _ReturnStatement2->ReturnStatement->setArgument(_NumberLiteral1->NumberLiteral);
}
void ReturnStatementWrapper::setArgumentRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  ReturnStatementWrapper* _ReturnStatement2 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args.This());

  _ReturnStatement2->ReturnStatement->setArgument(_RegExpLiteral1->RegExpLiteral);
}
void ReturnStatementWrapper::setArgumentStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  ReturnStatementWrapper* _ReturnStatement2 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args.This());

  _ReturnStatement2->ReturnStatement->setArgument(_StringLiteral1->StringLiteral);
}
void ReturnStatementWrapper::setArgumentLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  ReturnStatementWrapper* _ReturnStatement2 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args.This());

  _ReturnStatement2->ReturnStatement->setArgument(_LogicalExpression1->LogicalExpression);
}
void ReturnStatementWrapper::setArgumentMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  ReturnStatementWrapper* _ReturnStatement2 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args.This());

  _ReturnStatement2->ReturnStatement->setArgument(_MemberExpression1->MemberExpression);
}
void ReturnStatementWrapper::setArgumentMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  ReturnStatementWrapper* _ReturnStatement2 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args.This());

  _ReturnStatement2->ReturnStatement->setArgument(_MetaProperty1->MetaProperty);
}
void ReturnStatementWrapper::setArgumentNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  ReturnStatementWrapper* _ReturnStatement2 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args.This());

  _ReturnStatement2->ReturnStatement->setArgument(_NewExpression1->NewExpression);
}
void ReturnStatementWrapper::setArgumentObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  ReturnStatementWrapper* _ReturnStatement2 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args.This());

  _ReturnStatement2->ReturnStatement->setArgument(_ObjectExpression1->ObjectExpression);
}
void ReturnStatementWrapper::setArgumentSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  ReturnStatementWrapper* _ReturnStatement2 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args.This());

  _ReturnStatement2->ReturnStatement->setArgument(_SequenceExpression1->SequenceExpression);
}
void ReturnStatementWrapper::setArgumentTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  ReturnStatementWrapper* _ReturnStatement2 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args.This());

  _ReturnStatement2->ReturnStatement->setArgument(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void ReturnStatementWrapper::setArgumentTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  ReturnStatementWrapper* _ReturnStatement2 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args.This());

  _ReturnStatement2->ReturnStatement->setArgument(_TemplateLiteral1->TemplateLiteral);
}
void ReturnStatementWrapper::setArgumentThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  ReturnStatementWrapper* _ReturnStatement2 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args.This());

  _ReturnStatement2->ReturnStatement->setArgument(_ThisExpression1->ThisExpression);
}
void ReturnStatementWrapper::setArgumentUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  ReturnStatementWrapper* _ReturnStatement2 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args.This());

  _ReturnStatement2->ReturnStatement->setArgument(_UnaryExpression1->UnaryExpression);
}
void ReturnStatementWrapper::setArgumentUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  ReturnStatementWrapper* _ReturnStatement2 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args.This());

  _ReturnStatement2->ReturnStatement->setArgument(_UpdateExpression1->UpdateExpression);
}
void ReturnStatementWrapper::setArgumentYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  ReturnStatementWrapper* _ReturnStatement2 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args.This());

  _ReturnStatement2->ReturnStatement->setArgument(_YieldExpression1->YieldExpression);
}
void ReturnStatementWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  ReturnStatementWrapper* _ReturnStatement2 = ObjectWrap::Unwrap<ReturnStatementWrapper>(args.This());

  _ReturnStatement2->ReturnStatement->addComments(_Comment1->Comment);
}
void ReturnStatementWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  ReturnStatementWrapper* _ReturnStatement = ObjectWrap::Unwrap<ReturnStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _ReturnStatement->ReturnStatement->getPosition();
  range.setPath( param );
  _ReturnStatement->ReturnStatement->setPosition( range );
}

void ReturnStatementWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ReturnStatementWrapper* _ReturnStatement = ObjectWrap::Unwrap<ReturnStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ReturnStatement->ReturnStatement->getPosition();
  range.setLine( ui );
  _ReturnStatement->ReturnStatement->setPosition( range );
}

void ReturnStatementWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ReturnStatementWrapper* _ReturnStatement = ObjectWrap::Unwrap<ReturnStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ReturnStatement->ReturnStatement->getPosition();
  range.setCol( ui );
  _ReturnStatement->ReturnStatement->setPosition( range );
}

void ReturnStatementWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ReturnStatementWrapper* _ReturnStatement = ObjectWrap::Unwrap<ReturnStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ReturnStatement->ReturnStatement->getPosition();
  range.setEndLine( ui );
  _ReturnStatement->ReturnStatement->setPosition( range );
}

void ReturnStatementWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ReturnStatementWrapper* _ReturnStatement = ObjectWrap::Unwrap<ReturnStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ReturnStatement->ReturnStatement->getPosition();
  range.setEndCol( ui );
  _ReturnStatement->ReturnStatement->setPosition( range );
}

void ReturnStatementWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ReturnStatementWrapper* _ReturnStatement = ObjectWrap::Unwrap<ReturnStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ReturnStatement->ReturnStatement->getPosition();
  range.setWideLine( ui );
  _ReturnStatement->ReturnStatement->setPosition( range );
}

void ReturnStatementWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ReturnStatementWrapper* _ReturnStatement = ObjectWrap::Unwrap<ReturnStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ReturnStatement->ReturnStatement->getPosition();
  range.setWideCol( ui );
  _ReturnStatement->ReturnStatement->setPosition( range );
}

void ReturnStatementWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ReturnStatementWrapper* _ReturnStatement = ObjectWrap::Unwrap<ReturnStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ReturnStatement->ReturnStatement->getPosition();
  range.setWideEndLine( ui );
  _ReturnStatement->ReturnStatement->setPosition( range );
}

void ReturnStatementWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ReturnStatementWrapper* _ReturnStatement = ObjectWrap::Unwrap<ReturnStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ReturnStatement->ReturnStatement->getPosition();
  range.setWideEndCol( ui );
  _ReturnStatement->ReturnStatement->setPosition( range );
}

}}}} //end of namespaces