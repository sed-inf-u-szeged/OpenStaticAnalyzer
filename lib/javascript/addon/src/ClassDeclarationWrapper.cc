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

#include "../inc/ClassDeclarationWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> ClassDeclarationWrapper::constructor;

void ClassDeclarationWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "ClassDeclarationWrapper"));             
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
  exports->Set(v8::String::NewFromUtf8(isolate, "ClassDeclarationWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void ClassDeclarationWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new ClassDeclarationWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    ClassDeclarationWrapper* obj = new ClassDeclarationWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `ClassDeclarationWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


ClassDeclarationWrapper::ClassDeclarationWrapper(Factory* fact)                        
{                                                   
  ClassDeclaration = fact->getFactory()->createClassDeclarationNode();          
}                                                   

ClassDeclarationWrapper::~ClassDeclarationWrapper()
{        
}        

void ClassDeclarationWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void ClassDeclarationWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  ClassDeclarationWrapper* _ClassDeclaration2 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());

  _ClassDeclaration2->ClassDeclaration->addComments(_Comment1->Comment);
}
void ClassDeclarationWrapper::setBodyClassBody(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassBodyWrapper* _ClassBody1 = ObjectWrap::Unwrap<ClassBodyWrapper>(args[0]->ToObject());
  ClassDeclarationWrapper* _ClassDeclaration2 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());

  _ClassDeclaration2->ClassDeclaration->setBody(_ClassBody1->ClassBody);
}
void ClassDeclarationWrapper::setSuperClassArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  ClassDeclarationWrapper* _ClassDeclaration2 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());

  _ClassDeclaration2->ClassDeclaration->setSuperClass(_ArrayExpression1->ArrayExpression);
}
void ClassDeclarationWrapper::setSuperClassArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  ClassDeclarationWrapper* _ClassDeclaration2 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());

  _ClassDeclaration2->ClassDeclaration->setSuperClass(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void ClassDeclarationWrapper::setSuperClassAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  ClassDeclarationWrapper* _ClassDeclaration2 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());

  _ClassDeclaration2->ClassDeclaration->setSuperClass(_AssignmentExpression1->AssignmentExpression);
}
void ClassDeclarationWrapper::setSuperClassAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  ClassDeclarationWrapper* _ClassDeclaration2 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());

  _ClassDeclaration2->ClassDeclaration->setSuperClass(_AwaitExpression1->AwaitExpression);
}
void ClassDeclarationWrapper::setSuperClassBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  ClassDeclarationWrapper* _ClassDeclaration2 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());

  _ClassDeclaration2->ClassDeclaration->setSuperClass(_BinaryExpression1->BinaryExpression);
}
void ClassDeclarationWrapper::setSuperClassCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  ClassDeclarationWrapper* _ClassDeclaration2 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());

  _ClassDeclaration2->ClassDeclaration->setSuperClass(_CallExpression1->CallExpression);
}
void ClassDeclarationWrapper::setSuperClassClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  ClassDeclarationWrapper* _ClassDeclaration2 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());

  _ClassDeclaration2->ClassDeclaration->setSuperClass(_ClassExpression1->ClassExpression);
}
void ClassDeclarationWrapper::setSuperClassConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  ClassDeclarationWrapper* _ClassDeclaration2 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());

  _ClassDeclaration2->ClassDeclaration->setSuperClass(_ConditionalExpression1->ConditionalExpression);
}
void ClassDeclarationWrapper::setSuperClassFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  ClassDeclarationWrapper* _ClassDeclaration2 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());

  _ClassDeclaration2->ClassDeclaration->setSuperClass(_FunctionExpression1->FunctionExpression);
}
void ClassDeclarationWrapper::setSuperClassIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  ClassDeclarationWrapper* _ClassDeclaration2 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());

  _ClassDeclaration2->ClassDeclaration->setSuperClass(_Identifier1->Identifier);
}
void ClassDeclarationWrapper::setSuperClassBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  ClassDeclarationWrapper* _ClassDeclaration2 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());

  _ClassDeclaration2->ClassDeclaration->setSuperClass(_BooleanLiteral1->BooleanLiteral);
}
void ClassDeclarationWrapper::setSuperClassNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  ClassDeclarationWrapper* _ClassDeclaration2 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());

  _ClassDeclaration2->ClassDeclaration->setSuperClass(_NullLiteral1->NullLiteral);
}
void ClassDeclarationWrapper::setSuperClassNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  ClassDeclarationWrapper* _ClassDeclaration2 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());

  _ClassDeclaration2->ClassDeclaration->setSuperClass(_NumberLiteral1->NumberLiteral);
}
void ClassDeclarationWrapper::setSuperClassRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  ClassDeclarationWrapper* _ClassDeclaration2 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());

  _ClassDeclaration2->ClassDeclaration->setSuperClass(_RegExpLiteral1->RegExpLiteral);
}
void ClassDeclarationWrapper::setSuperClassStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  ClassDeclarationWrapper* _ClassDeclaration2 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());

  _ClassDeclaration2->ClassDeclaration->setSuperClass(_StringLiteral1->StringLiteral);
}
void ClassDeclarationWrapper::setSuperClassLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  ClassDeclarationWrapper* _ClassDeclaration2 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());

  _ClassDeclaration2->ClassDeclaration->setSuperClass(_LogicalExpression1->LogicalExpression);
}
void ClassDeclarationWrapper::setSuperClassMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  ClassDeclarationWrapper* _ClassDeclaration2 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());

  _ClassDeclaration2->ClassDeclaration->setSuperClass(_MemberExpression1->MemberExpression);
}
void ClassDeclarationWrapper::setSuperClassMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  ClassDeclarationWrapper* _ClassDeclaration2 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());

  _ClassDeclaration2->ClassDeclaration->setSuperClass(_MetaProperty1->MetaProperty);
}
void ClassDeclarationWrapper::setSuperClassNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  ClassDeclarationWrapper* _ClassDeclaration2 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());

  _ClassDeclaration2->ClassDeclaration->setSuperClass(_NewExpression1->NewExpression);
}
void ClassDeclarationWrapper::setSuperClassObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  ClassDeclarationWrapper* _ClassDeclaration2 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());

  _ClassDeclaration2->ClassDeclaration->setSuperClass(_ObjectExpression1->ObjectExpression);
}
void ClassDeclarationWrapper::setSuperClassSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  ClassDeclarationWrapper* _ClassDeclaration2 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());

  _ClassDeclaration2->ClassDeclaration->setSuperClass(_SequenceExpression1->SequenceExpression);
}
void ClassDeclarationWrapper::setSuperClassTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  ClassDeclarationWrapper* _ClassDeclaration2 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());

  _ClassDeclaration2->ClassDeclaration->setSuperClass(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void ClassDeclarationWrapper::setSuperClassTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  ClassDeclarationWrapper* _ClassDeclaration2 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());

  _ClassDeclaration2->ClassDeclaration->setSuperClass(_TemplateLiteral1->TemplateLiteral);
}
void ClassDeclarationWrapper::setSuperClassThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  ClassDeclarationWrapper* _ClassDeclaration2 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());

  _ClassDeclaration2->ClassDeclaration->setSuperClass(_ThisExpression1->ThisExpression);
}
void ClassDeclarationWrapper::setSuperClassUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  ClassDeclarationWrapper* _ClassDeclaration2 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());

  _ClassDeclaration2->ClassDeclaration->setSuperClass(_UnaryExpression1->UnaryExpression);
}
void ClassDeclarationWrapper::setSuperClassUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  ClassDeclarationWrapper* _ClassDeclaration2 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());

  _ClassDeclaration2->ClassDeclaration->setSuperClass(_UpdateExpression1->UpdateExpression);
}
void ClassDeclarationWrapper::setSuperClassYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  ClassDeclarationWrapper* _ClassDeclaration2 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());

  _ClassDeclaration2->ClassDeclaration->setSuperClass(_YieldExpression1->YieldExpression);
}
void ClassDeclarationWrapper::setIdentifierIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  ClassDeclarationWrapper* _ClassDeclaration2 = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());

  _ClassDeclaration2->ClassDeclaration->setIdentifier(_Identifier1->Identifier);
}
void ClassDeclarationWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  ClassDeclarationWrapper* _ClassDeclaration = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _ClassDeclaration->ClassDeclaration->getPosition();
  range.setPath( param );
  _ClassDeclaration->ClassDeclaration->setPosition( range );
}

void ClassDeclarationWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ClassDeclarationWrapper* _ClassDeclaration = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ClassDeclaration->ClassDeclaration->getPosition();
  range.setLine( ui );
  _ClassDeclaration->ClassDeclaration->setPosition( range );
}

void ClassDeclarationWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ClassDeclarationWrapper* _ClassDeclaration = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ClassDeclaration->ClassDeclaration->getPosition();
  range.setCol( ui );
  _ClassDeclaration->ClassDeclaration->setPosition( range );
}

void ClassDeclarationWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ClassDeclarationWrapper* _ClassDeclaration = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ClassDeclaration->ClassDeclaration->getPosition();
  range.setEndLine( ui );
  _ClassDeclaration->ClassDeclaration->setPosition( range );
}

void ClassDeclarationWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ClassDeclarationWrapper* _ClassDeclaration = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ClassDeclaration->ClassDeclaration->getPosition();
  range.setEndCol( ui );
  _ClassDeclaration->ClassDeclaration->setPosition( range );
}

void ClassDeclarationWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ClassDeclarationWrapper* _ClassDeclaration = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ClassDeclaration->ClassDeclaration->getPosition();
  range.setWideLine( ui );
  _ClassDeclaration->ClassDeclaration->setPosition( range );
}

void ClassDeclarationWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ClassDeclarationWrapper* _ClassDeclaration = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ClassDeclaration->ClassDeclaration->getPosition();
  range.setWideCol( ui );
  _ClassDeclaration->ClassDeclaration->setPosition( range );
}

void ClassDeclarationWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ClassDeclarationWrapper* _ClassDeclaration = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ClassDeclaration->ClassDeclaration->getPosition();
  range.setWideEndLine( ui );
  _ClassDeclaration->ClassDeclaration->setPosition( range );
}

void ClassDeclarationWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ClassDeclarationWrapper* _ClassDeclaration = ObjectWrap::Unwrap<ClassDeclarationWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ClassDeclaration->ClassDeclaration->getPosition();
  range.setWideEndCol( ui );
  _ClassDeclaration->ClassDeclaration->setPosition( range );
}

}}}} //end of namespaces