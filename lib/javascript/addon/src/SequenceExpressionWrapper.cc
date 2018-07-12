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

#include "../inc/SequenceExpressionWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> SequenceExpressionWrapper::constructor;

void SequenceExpressionWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "SequenceExpressionWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
  NODE_SET_PROTOTYPE_METHOD(tpl, "addExpressionsArrayExpression", addExpressionsArrayExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addExpressionsArrowFunctionExpression", addExpressionsArrowFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addExpressionsAssignmentExpression", addExpressionsAssignmentExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addExpressionsAwaitExpression", addExpressionsAwaitExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addExpressionsBinaryExpression", addExpressionsBinaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addExpressionsCallExpression", addExpressionsCallExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addExpressionsClassExpression", addExpressionsClassExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addExpressionsConditionalExpression", addExpressionsConditionalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addExpressionsFunctionExpression", addExpressionsFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addExpressionsIdentifier", addExpressionsIdentifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addExpressionsBooleanLiteral", addExpressionsBooleanLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addExpressionsNullLiteral", addExpressionsNullLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addExpressionsNumberLiteral", addExpressionsNumberLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addExpressionsRegExpLiteral", addExpressionsRegExpLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addExpressionsStringLiteral", addExpressionsStringLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addExpressionsLogicalExpression", addExpressionsLogicalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addExpressionsMemberExpression", addExpressionsMemberExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addExpressionsMetaProperty", addExpressionsMetaProperty);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addExpressionsNewExpression", addExpressionsNewExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addExpressionsObjectExpression", addExpressionsObjectExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addExpressionsSequenceExpression", addExpressionsSequenceExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addExpressionsTaggedTemplateExpression", addExpressionsTaggedTemplateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addExpressionsTemplateLiteral", addExpressionsTemplateLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addExpressionsThisExpression", addExpressionsThisExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addExpressionsUnaryExpression", addExpressionsUnaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addExpressionsUpdateExpression", addExpressionsUpdateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addExpressionsYieldExpression", addExpressionsYieldExpression);
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
  exports->Set(v8::String::NewFromUtf8(isolate, "SequenceExpressionWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void SequenceExpressionWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new SequenceExpressionWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    SequenceExpressionWrapper* obj = new SequenceExpressionWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `SequenceExpressionWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


SequenceExpressionWrapper::SequenceExpressionWrapper(Factory* fact)                        
{                                                   
  SequenceExpression = fact->getFactory()->createSequenceExpressionNode();          
}                                                   

SequenceExpressionWrapper::~SequenceExpressionWrapper()
{        
}        

void SequenceExpressionWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void SequenceExpressionWrapper::addExpressionsArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  SequenceExpressionWrapper* _SequenceExpression2 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args.This());

  _SequenceExpression2->SequenceExpression->addExpressions(_ArrayExpression1->ArrayExpression);
}
void SequenceExpressionWrapper::addExpressionsArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  SequenceExpressionWrapper* _SequenceExpression2 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args.This());

  _SequenceExpression2->SequenceExpression->addExpressions(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void SequenceExpressionWrapper::addExpressionsAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  SequenceExpressionWrapper* _SequenceExpression2 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args.This());

  _SequenceExpression2->SequenceExpression->addExpressions(_AssignmentExpression1->AssignmentExpression);
}
void SequenceExpressionWrapper::addExpressionsAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  SequenceExpressionWrapper* _SequenceExpression2 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args.This());

  _SequenceExpression2->SequenceExpression->addExpressions(_AwaitExpression1->AwaitExpression);
}
void SequenceExpressionWrapper::addExpressionsBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  SequenceExpressionWrapper* _SequenceExpression2 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args.This());

  _SequenceExpression2->SequenceExpression->addExpressions(_BinaryExpression1->BinaryExpression);
}
void SequenceExpressionWrapper::addExpressionsCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  SequenceExpressionWrapper* _SequenceExpression2 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args.This());

  _SequenceExpression2->SequenceExpression->addExpressions(_CallExpression1->CallExpression);
}
void SequenceExpressionWrapper::addExpressionsClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  SequenceExpressionWrapper* _SequenceExpression2 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args.This());

  _SequenceExpression2->SequenceExpression->addExpressions(_ClassExpression1->ClassExpression);
}
void SequenceExpressionWrapper::addExpressionsConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  SequenceExpressionWrapper* _SequenceExpression2 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args.This());

  _SequenceExpression2->SequenceExpression->addExpressions(_ConditionalExpression1->ConditionalExpression);
}
void SequenceExpressionWrapper::addExpressionsFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  SequenceExpressionWrapper* _SequenceExpression2 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args.This());

  _SequenceExpression2->SequenceExpression->addExpressions(_FunctionExpression1->FunctionExpression);
}
void SequenceExpressionWrapper::addExpressionsIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  SequenceExpressionWrapper* _SequenceExpression2 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args.This());

  _SequenceExpression2->SequenceExpression->addExpressions(_Identifier1->Identifier);
}
void SequenceExpressionWrapper::addExpressionsBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  SequenceExpressionWrapper* _SequenceExpression2 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args.This());

  _SequenceExpression2->SequenceExpression->addExpressions(_BooleanLiteral1->BooleanLiteral);
}
void SequenceExpressionWrapper::addExpressionsNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  SequenceExpressionWrapper* _SequenceExpression2 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args.This());

  _SequenceExpression2->SequenceExpression->addExpressions(_NullLiteral1->NullLiteral);
}
void SequenceExpressionWrapper::addExpressionsNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  SequenceExpressionWrapper* _SequenceExpression2 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args.This());

  _SequenceExpression2->SequenceExpression->addExpressions(_NumberLiteral1->NumberLiteral);
}
void SequenceExpressionWrapper::addExpressionsRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  SequenceExpressionWrapper* _SequenceExpression2 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args.This());

  _SequenceExpression2->SequenceExpression->addExpressions(_RegExpLiteral1->RegExpLiteral);
}
void SequenceExpressionWrapper::addExpressionsStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  SequenceExpressionWrapper* _SequenceExpression2 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args.This());

  _SequenceExpression2->SequenceExpression->addExpressions(_StringLiteral1->StringLiteral);
}
void SequenceExpressionWrapper::addExpressionsLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  SequenceExpressionWrapper* _SequenceExpression2 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args.This());

  _SequenceExpression2->SequenceExpression->addExpressions(_LogicalExpression1->LogicalExpression);
}
void SequenceExpressionWrapper::addExpressionsMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  SequenceExpressionWrapper* _SequenceExpression2 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args.This());

  _SequenceExpression2->SequenceExpression->addExpressions(_MemberExpression1->MemberExpression);
}
void SequenceExpressionWrapper::addExpressionsMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  SequenceExpressionWrapper* _SequenceExpression2 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args.This());

  _SequenceExpression2->SequenceExpression->addExpressions(_MetaProperty1->MetaProperty);
}
void SequenceExpressionWrapper::addExpressionsNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  SequenceExpressionWrapper* _SequenceExpression2 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args.This());

  _SequenceExpression2->SequenceExpression->addExpressions(_NewExpression1->NewExpression);
}
void SequenceExpressionWrapper::addExpressionsObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  SequenceExpressionWrapper* _SequenceExpression2 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args.This());

  _SequenceExpression2->SequenceExpression->addExpressions(_ObjectExpression1->ObjectExpression);
}
void SequenceExpressionWrapper::addExpressionsSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  SequenceExpressionWrapper* _SequenceExpression2 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args.This());

  _SequenceExpression2->SequenceExpression->addExpressions(_SequenceExpression1->SequenceExpression);
}
void SequenceExpressionWrapper::addExpressionsTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  SequenceExpressionWrapper* _SequenceExpression2 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args.This());

  _SequenceExpression2->SequenceExpression->addExpressions(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void SequenceExpressionWrapper::addExpressionsTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  SequenceExpressionWrapper* _SequenceExpression2 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args.This());

  _SequenceExpression2->SequenceExpression->addExpressions(_TemplateLiteral1->TemplateLiteral);
}
void SequenceExpressionWrapper::addExpressionsThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  SequenceExpressionWrapper* _SequenceExpression2 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args.This());

  _SequenceExpression2->SequenceExpression->addExpressions(_ThisExpression1->ThisExpression);
}
void SequenceExpressionWrapper::addExpressionsUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  SequenceExpressionWrapper* _SequenceExpression2 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args.This());

  _SequenceExpression2->SequenceExpression->addExpressions(_UnaryExpression1->UnaryExpression);
}
void SequenceExpressionWrapper::addExpressionsUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  SequenceExpressionWrapper* _SequenceExpression2 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args.This());

  _SequenceExpression2->SequenceExpression->addExpressions(_UpdateExpression1->UpdateExpression);
}
void SequenceExpressionWrapper::addExpressionsYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  SequenceExpressionWrapper* _SequenceExpression2 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args.This());

  _SequenceExpression2->SequenceExpression->addExpressions(_YieldExpression1->YieldExpression);
}
void SequenceExpressionWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  SequenceExpressionWrapper* _SequenceExpression2 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args.This());

  _SequenceExpression2->SequenceExpression->addComments(_Comment1->Comment);
}
void SequenceExpressionWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  SequenceExpressionWrapper* _SequenceExpression = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _SequenceExpression->SequenceExpression->getPosition();
  range.setPath( param );
  _SequenceExpression->SequenceExpression->setPosition( range );
}

void SequenceExpressionWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  SequenceExpressionWrapper* _SequenceExpression = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _SequenceExpression->SequenceExpression->getPosition();
  range.setLine( ui );
  _SequenceExpression->SequenceExpression->setPosition( range );
}

void SequenceExpressionWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  SequenceExpressionWrapper* _SequenceExpression = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _SequenceExpression->SequenceExpression->getPosition();
  range.setCol( ui );
  _SequenceExpression->SequenceExpression->setPosition( range );
}

void SequenceExpressionWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  SequenceExpressionWrapper* _SequenceExpression = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _SequenceExpression->SequenceExpression->getPosition();
  range.setEndLine( ui );
  _SequenceExpression->SequenceExpression->setPosition( range );
}

void SequenceExpressionWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  SequenceExpressionWrapper* _SequenceExpression = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _SequenceExpression->SequenceExpression->getPosition();
  range.setEndCol( ui );
  _SequenceExpression->SequenceExpression->setPosition( range );
}

void SequenceExpressionWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  SequenceExpressionWrapper* _SequenceExpression = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _SequenceExpression->SequenceExpression->getPosition();
  range.setWideLine( ui );
  _SequenceExpression->SequenceExpression->setPosition( range );
}

void SequenceExpressionWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  SequenceExpressionWrapper* _SequenceExpression = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _SequenceExpression->SequenceExpression->getPosition();
  range.setWideCol( ui );
  _SequenceExpression->SequenceExpression->setPosition( range );
}

void SequenceExpressionWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  SequenceExpressionWrapper* _SequenceExpression = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _SequenceExpression->SequenceExpression->getPosition();
  range.setWideEndLine( ui );
  _SequenceExpression->SequenceExpression->setPosition( range );
}

void SequenceExpressionWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  SequenceExpressionWrapper* _SequenceExpression = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _SequenceExpression->SequenceExpression->getPosition();
  range.setWideEndCol( ui );
  _SequenceExpression->SequenceExpression->setPosition( range );
}

}}}} //end of namespaces