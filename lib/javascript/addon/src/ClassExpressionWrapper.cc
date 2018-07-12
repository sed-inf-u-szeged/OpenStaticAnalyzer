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

#include "../inc/ClassExpressionWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> ClassExpressionWrapper::constructor;

void ClassExpressionWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "ClassExpressionWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
  NODE_SET_PROTOTYPE_METHOD(tpl, "addCommentsComment", addCommentsComment);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setBodyClassBody", setBodyClassBody);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setSuperClassArrayExpression", setSuperClassArrayExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setSuperClassArrowFunctionExpression", setSuperClassArrowFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setSuperClassAssignmentExpression", setSuperClassAssignmentExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setSuperClassAwaitExpression", setSuperClassAwaitExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setSuperClassBinaryExpression", setSuperClassBinaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setSuperClassCallExpression", setSuperClassCallExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setSuperClassClassExpression", setSuperClassClassExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setSuperClassConditionalExpression", setSuperClassConditionalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setSuperClassFunctionExpression", setSuperClassFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setSuperClassIdentifier", setSuperClassIdentifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setSuperClassBooleanLiteral", setSuperClassBooleanLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setSuperClassNullLiteral", setSuperClassNullLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setSuperClassNumberLiteral", setSuperClassNumberLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setSuperClassRegExpLiteral", setSuperClassRegExpLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setSuperClassStringLiteral", setSuperClassStringLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setSuperClassLogicalExpression", setSuperClassLogicalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setSuperClassMemberExpression", setSuperClassMemberExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setSuperClassMetaProperty", setSuperClassMetaProperty);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setSuperClassNewExpression", setSuperClassNewExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setSuperClassObjectExpression", setSuperClassObjectExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setSuperClassSequenceExpression", setSuperClassSequenceExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setSuperClassTaggedTemplateExpression", setSuperClassTaggedTemplateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setSuperClassTemplateLiteral", setSuperClassTemplateLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setSuperClassThisExpression", setSuperClassThisExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setSuperClassUnaryExpression", setSuperClassUnaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setSuperClassUpdateExpression", setSuperClassUpdateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setSuperClassYieldExpression", setSuperClassYieldExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setIdentifierIdentifier", setIdentifierIdentifier);
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
  exports->Set(v8::String::NewFromUtf8(isolate, "ClassExpressionWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void ClassExpressionWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new ClassExpressionWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    ClassExpressionWrapper* obj = new ClassExpressionWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `ClassExpressionWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


ClassExpressionWrapper::ClassExpressionWrapper(Factory* fact)                        
{                                                   
  ClassExpression = fact->getFactory()->createClassExpressionNode();          
}                                                   

ClassExpressionWrapper::~ClassExpressionWrapper()
{        
}        

void ClassExpressionWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void ClassExpressionWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  ClassExpressionWrapper* _ClassExpression2 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());

  _ClassExpression2->ClassExpression->addComments(_Comment1->Comment);
}
void ClassExpressionWrapper::setBodyClassBody(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassBodyWrapper* _ClassBody1 = ObjectWrap::Unwrap<ClassBodyWrapper>(args[0]->ToObject());
  ClassExpressionWrapper* _ClassExpression2 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());

  _ClassExpression2->ClassExpression->setBody(_ClassBody1->ClassBody);
}
void ClassExpressionWrapper::setSuperClassArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  ClassExpressionWrapper* _ClassExpression2 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());

  _ClassExpression2->ClassExpression->setSuperClass(_ArrayExpression1->ArrayExpression);
}
void ClassExpressionWrapper::setSuperClassArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  ClassExpressionWrapper* _ClassExpression2 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());

  _ClassExpression2->ClassExpression->setSuperClass(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void ClassExpressionWrapper::setSuperClassAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  ClassExpressionWrapper* _ClassExpression2 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());

  _ClassExpression2->ClassExpression->setSuperClass(_AssignmentExpression1->AssignmentExpression);
}
void ClassExpressionWrapper::setSuperClassAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  ClassExpressionWrapper* _ClassExpression2 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());

  _ClassExpression2->ClassExpression->setSuperClass(_AwaitExpression1->AwaitExpression);
}
void ClassExpressionWrapper::setSuperClassBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  ClassExpressionWrapper* _ClassExpression2 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());

  _ClassExpression2->ClassExpression->setSuperClass(_BinaryExpression1->BinaryExpression);
}
void ClassExpressionWrapper::setSuperClassCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  ClassExpressionWrapper* _ClassExpression2 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());

  _ClassExpression2->ClassExpression->setSuperClass(_CallExpression1->CallExpression);
}
void ClassExpressionWrapper::setSuperClassClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  ClassExpressionWrapper* _ClassExpression2 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());

  _ClassExpression2->ClassExpression->setSuperClass(_ClassExpression1->ClassExpression);
}
void ClassExpressionWrapper::setSuperClassConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  ClassExpressionWrapper* _ClassExpression2 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());

  _ClassExpression2->ClassExpression->setSuperClass(_ConditionalExpression1->ConditionalExpression);
}
void ClassExpressionWrapper::setSuperClassFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  ClassExpressionWrapper* _ClassExpression2 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());

  _ClassExpression2->ClassExpression->setSuperClass(_FunctionExpression1->FunctionExpression);
}
void ClassExpressionWrapper::setSuperClassIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  ClassExpressionWrapper* _ClassExpression2 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());

  _ClassExpression2->ClassExpression->setSuperClass(_Identifier1->Identifier);
}
void ClassExpressionWrapper::setSuperClassBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  ClassExpressionWrapper* _ClassExpression2 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());

  _ClassExpression2->ClassExpression->setSuperClass(_BooleanLiteral1->BooleanLiteral);
}
void ClassExpressionWrapper::setSuperClassNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  ClassExpressionWrapper* _ClassExpression2 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());

  _ClassExpression2->ClassExpression->setSuperClass(_NullLiteral1->NullLiteral);
}
void ClassExpressionWrapper::setSuperClassNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  ClassExpressionWrapper* _ClassExpression2 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());

  _ClassExpression2->ClassExpression->setSuperClass(_NumberLiteral1->NumberLiteral);
}
void ClassExpressionWrapper::setSuperClassRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  ClassExpressionWrapper* _ClassExpression2 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());

  _ClassExpression2->ClassExpression->setSuperClass(_RegExpLiteral1->RegExpLiteral);
}
void ClassExpressionWrapper::setSuperClassStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  ClassExpressionWrapper* _ClassExpression2 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());

  _ClassExpression2->ClassExpression->setSuperClass(_StringLiteral1->StringLiteral);
}
void ClassExpressionWrapper::setSuperClassLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  ClassExpressionWrapper* _ClassExpression2 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());

  _ClassExpression2->ClassExpression->setSuperClass(_LogicalExpression1->LogicalExpression);
}
void ClassExpressionWrapper::setSuperClassMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  ClassExpressionWrapper* _ClassExpression2 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());

  _ClassExpression2->ClassExpression->setSuperClass(_MemberExpression1->MemberExpression);
}
void ClassExpressionWrapper::setSuperClassMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  ClassExpressionWrapper* _ClassExpression2 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());

  _ClassExpression2->ClassExpression->setSuperClass(_MetaProperty1->MetaProperty);
}
void ClassExpressionWrapper::setSuperClassNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  ClassExpressionWrapper* _ClassExpression2 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());

  _ClassExpression2->ClassExpression->setSuperClass(_NewExpression1->NewExpression);
}
void ClassExpressionWrapper::setSuperClassObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  ClassExpressionWrapper* _ClassExpression2 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());

  _ClassExpression2->ClassExpression->setSuperClass(_ObjectExpression1->ObjectExpression);
}
void ClassExpressionWrapper::setSuperClassSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  ClassExpressionWrapper* _ClassExpression2 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());

  _ClassExpression2->ClassExpression->setSuperClass(_SequenceExpression1->SequenceExpression);
}
void ClassExpressionWrapper::setSuperClassTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  ClassExpressionWrapper* _ClassExpression2 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());

  _ClassExpression2->ClassExpression->setSuperClass(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void ClassExpressionWrapper::setSuperClassTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  ClassExpressionWrapper* _ClassExpression2 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());

  _ClassExpression2->ClassExpression->setSuperClass(_TemplateLiteral1->TemplateLiteral);
}
void ClassExpressionWrapper::setSuperClassThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  ClassExpressionWrapper* _ClassExpression2 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());

  _ClassExpression2->ClassExpression->setSuperClass(_ThisExpression1->ThisExpression);
}
void ClassExpressionWrapper::setSuperClassUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  ClassExpressionWrapper* _ClassExpression2 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());

  _ClassExpression2->ClassExpression->setSuperClass(_UnaryExpression1->UnaryExpression);
}
void ClassExpressionWrapper::setSuperClassUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  ClassExpressionWrapper* _ClassExpression2 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());

  _ClassExpression2->ClassExpression->setSuperClass(_UpdateExpression1->UpdateExpression);
}
void ClassExpressionWrapper::setSuperClassYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  ClassExpressionWrapper* _ClassExpression2 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());

  _ClassExpression2->ClassExpression->setSuperClass(_YieldExpression1->YieldExpression);
}
void ClassExpressionWrapper::setIdentifierIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  ClassExpressionWrapper* _ClassExpression2 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());

  _ClassExpression2->ClassExpression->setIdentifier(_Identifier1->Identifier);
}
void ClassExpressionWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  ClassExpressionWrapper* _ClassExpression = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _ClassExpression->ClassExpression->getPosition();
  range.setPath( param );
  _ClassExpression->ClassExpression->setPosition( range );
}

void ClassExpressionWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ClassExpressionWrapper* _ClassExpression = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ClassExpression->ClassExpression->getPosition();
  range.setLine( ui );
  _ClassExpression->ClassExpression->setPosition( range );
}

void ClassExpressionWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ClassExpressionWrapper* _ClassExpression = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ClassExpression->ClassExpression->getPosition();
  range.setCol( ui );
  _ClassExpression->ClassExpression->setPosition( range );
}

void ClassExpressionWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ClassExpressionWrapper* _ClassExpression = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ClassExpression->ClassExpression->getPosition();
  range.setEndLine( ui );
  _ClassExpression->ClassExpression->setPosition( range );
}

void ClassExpressionWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ClassExpressionWrapper* _ClassExpression = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ClassExpression->ClassExpression->getPosition();
  range.setEndCol( ui );
  _ClassExpression->ClassExpression->setPosition( range );
}

void ClassExpressionWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ClassExpressionWrapper* _ClassExpression = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ClassExpression->ClassExpression->getPosition();
  range.setWideLine( ui );
  _ClassExpression->ClassExpression->setPosition( range );
}

void ClassExpressionWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ClassExpressionWrapper* _ClassExpression = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ClassExpression->ClassExpression->getPosition();
  range.setWideCol( ui );
  _ClassExpression->ClassExpression->setPosition( range );
}

void ClassExpressionWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ClassExpressionWrapper* _ClassExpression = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ClassExpression->ClassExpression->getPosition();
  range.setWideEndLine( ui );
  _ClassExpression->ClassExpression->setPosition( range );
}

void ClassExpressionWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ClassExpressionWrapper* _ClassExpression = ObjectWrap::Unwrap<ClassExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ClassExpression->ClassExpression->getPosition();
  range.setWideEndCol( ui );
  _ClassExpression->ClassExpression->setPosition( range );
}

}}}} //end of namespaces