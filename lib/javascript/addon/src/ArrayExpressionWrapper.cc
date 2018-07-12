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

#include "../inc/ArrayExpressionWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> ArrayExpressionWrapper::constructor;

void ArrayExpressionWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "ArrayExpressionWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
  NODE_SET_PROTOTYPE_METHOD(tpl, "addElementsSpreadElement", addElementsSpreadElement);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addElementsArrayExpression", addElementsArrayExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addElementsArrowFunctionExpression", addElementsArrowFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addElementsAssignmentExpression", addElementsAssignmentExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addElementsAwaitExpression", addElementsAwaitExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addElementsBinaryExpression", addElementsBinaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addElementsCallExpression", addElementsCallExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addElementsClassExpression", addElementsClassExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addElementsConditionalExpression", addElementsConditionalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addElementsFunctionExpression", addElementsFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addElementsIdentifier", addElementsIdentifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addElementsBooleanLiteral", addElementsBooleanLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addElementsNullLiteral", addElementsNullLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addElementsNumberLiteral", addElementsNumberLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addElementsRegExpLiteral", addElementsRegExpLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addElementsStringLiteral", addElementsStringLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addElementsLogicalExpression", addElementsLogicalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addElementsMemberExpression", addElementsMemberExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addElementsMetaProperty", addElementsMetaProperty);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addElementsNewExpression", addElementsNewExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addElementsObjectExpression", addElementsObjectExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addElementsSequenceExpression", addElementsSequenceExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addElementsTaggedTemplateExpression", addElementsTaggedTemplateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addElementsTemplateLiteral", addElementsTemplateLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addElementsThisExpression", addElementsThisExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addElementsUnaryExpression", addElementsUnaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addElementsUpdateExpression", addElementsUpdateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addElementsYieldExpression", addElementsYieldExpression);
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
  exports->Set(v8::String::NewFromUtf8(isolate, "ArrayExpressionWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void ArrayExpressionWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new ArrayExpressionWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    ArrayExpressionWrapper* obj = new ArrayExpressionWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `ArrayExpressionWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


ArrayExpressionWrapper::ArrayExpressionWrapper(Factory* fact)                        
{                                                   
  ArrayExpression = fact->getFactory()->createArrayExpressionNode();          
}                                                   

ArrayExpressionWrapper::~ArrayExpressionWrapper()
{        
}        

void ArrayExpressionWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void ArrayExpressionWrapper::addElementsSpreadElement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SpreadElementWrapper* _SpreadElement1 = ObjectWrap::Unwrap<SpreadElementWrapper>(args[0]->ToObject());
  ArrayExpressionWrapper* _ArrayExpression2 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());

  _ArrayExpression2->ArrayExpression->addElements(_SpreadElement1->SpreadElement);
}
void ArrayExpressionWrapper::addElementsArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  ArrayExpressionWrapper* _ArrayExpression2 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());

  _ArrayExpression2->ArrayExpression->addElements(_ArrayExpression1->ArrayExpression);
}
void ArrayExpressionWrapper::addElementsArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  ArrayExpressionWrapper* _ArrayExpression2 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());

  _ArrayExpression2->ArrayExpression->addElements(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void ArrayExpressionWrapper::addElementsAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  ArrayExpressionWrapper* _ArrayExpression2 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());

  _ArrayExpression2->ArrayExpression->addElements(_AssignmentExpression1->AssignmentExpression);
}
void ArrayExpressionWrapper::addElementsAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  ArrayExpressionWrapper* _ArrayExpression2 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());

  _ArrayExpression2->ArrayExpression->addElements(_AwaitExpression1->AwaitExpression);
}
void ArrayExpressionWrapper::addElementsBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  ArrayExpressionWrapper* _ArrayExpression2 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());

  _ArrayExpression2->ArrayExpression->addElements(_BinaryExpression1->BinaryExpression);
}
void ArrayExpressionWrapper::addElementsCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  ArrayExpressionWrapper* _ArrayExpression2 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());

  _ArrayExpression2->ArrayExpression->addElements(_CallExpression1->CallExpression);
}
void ArrayExpressionWrapper::addElementsClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  ArrayExpressionWrapper* _ArrayExpression2 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());

  _ArrayExpression2->ArrayExpression->addElements(_ClassExpression1->ClassExpression);
}
void ArrayExpressionWrapper::addElementsConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  ArrayExpressionWrapper* _ArrayExpression2 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());

  _ArrayExpression2->ArrayExpression->addElements(_ConditionalExpression1->ConditionalExpression);
}
void ArrayExpressionWrapper::addElementsFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  ArrayExpressionWrapper* _ArrayExpression2 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());

  _ArrayExpression2->ArrayExpression->addElements(_FunctionExpression1->FunctionExpression);
}
void ArrayExpressionWrapper::addElementsIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  ArrayExpressionWrapper* _ArrayExpression2 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());

  _ArrayExpression2->ArrayExpression->addElements(_Identifier1->Identifier);
}
void ArrayExpressionWrapper::addElementsBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  ArrayExpressionWrapper* _ArrayExpression2 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());

  _ArrayExpression2->ArrayExpression->addElements(_BooleanLiteral1->BooleanLiteral);
}
void ArrayExpressionWrapper::addElementsNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  ArrayExpressionWrapper* _ArrayExpression2 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());

  _ArrayExpression2->ArrayExpression->addElements(_NullLiteral1->NullLiteral);
}
void ArrayExpressionWrapper::addElementsNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  ArrayExpressionWrapper* _ArrayExpression2 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());

  _ArrayExpression2->ArrayExpression->addElements(_NumberLiteral1->NumberLiteral);
}
void ArrayExpressionWrapper::addElementsRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  ArrayExpressionWrapper* _ArrayExpression2 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());

  _ArrayExpression2->ArrayExpression->addElements(_RegExpLiteral1->RegExpLiteral);
}
void ArrayExpressionWrapper::addElementsStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  ArrayExpressionWrapper* _ArrayExpression2 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());

  _ArrayExpression2->ArrayExpression->addElements(_StringLiteral1->StringLiteral);
}
void ArrayExpressionWrapper::addElementsLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  ArrayExpressionWrapper* _ArrayExpression2 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());

  _ArrayExpression2->ArrayExpression->addElements(_LogicalExpression1->LogicalExpression);
}
void ArrayExpressionWrapper::addElementsMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  ArrayExpressionWrapper* _ArrayExpression2 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());

  _ArrayExpression2->ArrayExpression->addElements(_MemberExpression1->MemberExpression);
}
void ArrayExpressionWrapper::addElementsMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  ArrayExpressionWrapper* _ArrayExpression2 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());

  _ArrayExpression2->ArrayExpression->addElements(_MetaProperty1->MetaProperty);
}
void ArrayExpressionWrapper::addElementsNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  ArrayExpressionWrapper* _ArrayExpression2 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());

  _ArrayExpression2->ArrayExpression->addElements(_NewExpression1->NewExpression);
}
void ArrayExpressionWrapper::addElementsObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  ArrayExpressionWrapper* _ArrayExpression2 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());

  _ArrayExpression2->ArrayExpression->addElements(_ObjectExpression1->ObjectExpression);
}
void ArrayExpressionWrapper::addElementsSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  ArrayExpressionWrapper* _ArrayExpression2 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());

  _ArrayExpression2->ArrayExpression->addElements(_SequenceExpression1->SequenceExpression);
}
void ArrayExpressionWrapper::addElementsTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  ArrayExpressionWrapper* _ArrayExpression2 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());

  _ArrayExpression2->ArrayExpression->addElements(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void ArrayExpressionWrapper::addElementsTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  ArrayExpressionWrapper* _ArrayExpression2 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());

  _ArrayExpression2->ArrayExpression->addElements(_TemplateLiteral1->TemplateLiteral);
}
void ArrayExpressionWrapper::addElementsThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  ArrayExpressionWrapper* _ArrayExpression2 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());

  _ArrayExpression2->ArrayExpression->addElements(_ThisExpression1->ThisExpression);
}
void ArrayExpressionWrapper::addElementsUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  ArrayExpressionWrapper* _ArrayExpression2 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());

  _ArrayExpression2->ArrayExpression->addElements(_UnaryExpression1->UnaryExpression);
}
void ArrayExpressionWrapper::addElementsUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  ArrayExpressionWrapper* _ArrayExpression2 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());

  _ArrayExpression2->ArrayExpression->addElements(_UpdateExpression1->UpdateExpression);
}
void ArrayExpressionWrapper::addElementsYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  ArrayExpressionWrapper* _ArrayExpression2 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());

  _ArrayExpression2->ArrayExpression->addElements(_YieldExpression1->YieldExpression);
}
void ArrayExpressionWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  ArrayExpressionWrapper* _ArrayExpression2 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());

  _ArrayExpression2->ArrayExpression->addComments(_Comment1->Comment);
}
void ArrayExpressionWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  ArrayExpressionWrapper* _ArrayExpression = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _ArrayExpression->ArrayExpression->getPosition();
  range.setPath( param );
  _ArrayExpression->ArrayExpression->setPosition( range );
}

void ArrayExpressionWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ArrayExpressionWrapper* _ArrayExpression = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ArrayExpression->ArrayExpression->getPosition();
  range.setLine( ui );
  _ArrayExpression->ArrayExpression->setPosition( range );
}

void ArrayExpressionWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ArrayExpressionWrapper* _ArrayExpression = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ArrayExpression->ArrayExpression->getPosition();
  range.setCol( ui );
  _ArrayExpression->ArrayExpression->setPosition( range );
}

void ArrayExpressionWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ArrayExpressionWrapper* _ArrayExpression = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ArrayExpression->ArrayExpression->getPosition();
  range.setEndLine( ui );
  _ArrayExpression->ArrayExpression->setPosition( range );
}

void ArrayExpressionWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ArrayExpressionWrapper* _ArrayExpression = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ArrayExpression->ArrayExpression->getPosition();
  range.setEndCol( ui );
  _ArrayExpression->ArrayExpression->setPosition( range );
}

void ArrayExpressionWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ArrayExpressionWrapper* _ArrayExpression = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ArrayExpression->ArrayExpression->getPosition();
  range.setWideLine( ui );
  _ArrayExpression->ArrayExpression->setPosition( range );
}

void ArrayExpressionWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ArrayExpressionWrapper* _ArrayExpression = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ArrayExpression->ArrayExpression->getPosition();
  range.setWideCol( ui );
  _ArrayExpression->ArrayExpression->setPosition( range );
}

void ArrayExpressionWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ArrayExpressionWrapper* _ArrayExpression = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ArrayExpression->ArrayExpression->getPosition();
  range.setWideEndLine( ui );
  _ArrayExpression->ArrayExpression->setPosition( range );
}

void ArrayExpressionWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ArrayExpressionWrapper* _ArrayExpression = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ArrayExpression->ArrayExpression->getPosition();
  range.setWideEndCol( ui );
  _ArrayExpression->ArrayExpression->setPosition( range );
}

}}}} //end of namespaces