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

#include "../inc/MethodDefinitionWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> MethodDefinitionWrapper::constructor;

void MethodDefinitionWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "MethodDefinitionWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyArrayExpression", setKeyArrayExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyArrowFunctionExpression", setKeyArrowFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyAssignmentExpression", setKeyAssignmentExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyAwaitExpression", setKeyAwaitExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyBinaryExpression", setKeyBinaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyCallExpression", setKeyCallExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyClassExpression", setKeyClassExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyConditionalExpression", setKeyConditionalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyFunctionExpression", setKeyFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyIdentifier", setKeyIdentifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyBooleanLiteral", setKeyBooleanLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyNullLiteral", setKeyNullLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyNumberLiteral", setKeyNumberLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyRegExpLiteral", setKeyRegExpLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyStringLiteral", setKeyStringLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyLogicalExpression", setKeyLogicalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyMemberExpression", setKeyMemberExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyMetaProperty", setKeyMetaProperty);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyNewExpression", setKeyNewExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyObjectExpression", setKeyObjectExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeySequenceExpression", setKeySequenceExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyTaggedTemplateExpression", setKeyTaggedTemplateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyTemplateLiteral", setKeyTemplateLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyThisExpression", setKeyThisExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyUnaryExpression", setKeyUnaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyUpdateExpression", setKeyUpdateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyYieldExpression", setKeyYieldExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setValueFunctionExpression", setValueFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addCommentsComment", addCommentsComment);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setKind", setKind);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setComputed", setComputed);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setStatic", setStatic);
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
  exports->Set(v8::String::NewFromUtf8(isolate, "MethodDefinitionWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void MethodDefinitionWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new MethodDefinitionWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    MethodDefinitionWrapper* obj = new MethodDefinitionWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `MethodDefinitionWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


MethodDefinitionWrapper::MethodDefinitionWrapper(Factory* fact)                        
{                                                   
  MethodDefinition = fact->getFactory()->createMethodDefinitionNode();          
}                                                   

MethodDefinitionWrapper::~MethodDefinitionWrapper()
{        
}        

void MethodDefinitionWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void MethodDefinitionWrapper::setKeyArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  MethodDefinitionWrapper* _MethodDefinition2 = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());

  _MethodDefinition2->MethodDefinition->setKey(_ArrayExpression1->ArrayExpression);
}
void MethodDefinitionWrapper::setKeyArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  MethodDefinitionWrapper* _MethodDefinition2 = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());

  _MethodDefinition2->MethodDefinition->setKey(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void MethodDefinitionWrapper::setKeyAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  MethodDefinitionWrapper* _MethodDefinition2 = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());

  _MethodDefinition2->MethodDefinition->setKey(_AssignmentExpression1->AssignmentExpression);
}
void MethodDefinitionWrapper::setKeyAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  MethodDefinitionWrapper* _MethodDefinition2 = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());

  _MethodDefinition2->MethodDefinition->setKey(_AwaitExpression1->AwaitExpression);
}
void MethodDefinitionWrapper::setKeyBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  MethodDefinitionWrapper* _MethodDefinition2 = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());

  _MethodDefinition2->MethodDefinition->setKey(_BinaryExpression1->BinaryExpression);
}
void MethodDefinitionWrapper::setKeyCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  MethodDefinitionWrapper* _MethodDefinition2 = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());

  _MethodDefinition2->MethodDefinition->setKey(_CallExpression1->CallExpression);
}
void MethodDefinitionWrapper::setKeyClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  MethodDefinitionWrapper* _MethodDefinition2 = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());

  _MethodDefinition2->MethodDefinition->setKey(_ClassExpression1->ClassExpression);
}
void MethodDefinitionWrapper::setKeyConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  MethodDefinitionWrapper* _MethodDefinition2 = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());

  _MethodDefinition2->MethodDefinition->setKey(_ConditionalExpression1->ConditionalExpression);
}
void MethodDefinitionWrapper::setKeyFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  MethodDefinitionWrapper* _MethodDefinition2 = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());

  _MethodDefinition2->MethodDefinition->setKey(_FunctionExpression1->FunctionExpression);
}
void MethodDefinitionWrapper::setKeyIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  MethodDefinitionWrapper* _MethodDefinition2 = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());

  _MethodDefinition2->MethodDefinition->setKey(_Identifier1->Identifier);
}
void MethodDefinitionWrapper::setKeyBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  MethodDefinitionWrapper* _MethodDefinition2 = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());

  _MethodDefinition2->MethodDefinition->setKey(_BooleanLiteral1->BooleanLiteral);
}
void MethodDefinitionWrapper::setKeyNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  MethodDefinitionWrapper* _MethodDefinition2 = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());

  _MethodDefinition2->MethodDefinition->setKey(_NullLiteral1->NullLiteral);
}
void MethodDefinitionWrapper::setKeyNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  MethodDefinitionWrapper* _MethodDefinition2 = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());

  _MethodDefinition2->MethodDefinition->setKey(_NumberLiteral1->NumberLiteral);
}
void MethodDefinitionWrapper::setKeyRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  MethodDefinitionWrapper* _MethodDefinition2 = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());

  _MethodDefinition2->MethodDefinition->setKey(_RegExpLiteral1->RegExpLiteral);
}
void MethodDefinitionWrapper::setKeyStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  MethodDefinitionWrapper* _MethodDefinition2 = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());

  _MethodDefinition2->MethodDefinition->setKey(_StringLiteral1->StringLiteral);
}
void MethodDefinitionWrapper::setKeyLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  MethodDefinitionWrapper* _MethodDefinition2 = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());

  _MethodDefinition2->MethodDefinition->setKey(_LogicalExpression1->LogicalExpression);
}
void MethodDefinitionWrapper::setKeyMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  MethodDefinitionWrapper* _MethodDefinition2 = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());

  _MethodDefinition2->MethodDefinition->setKey(_MemberExpression1->MemberExpression);
}
void MethodDefinitionWrapper::setKeyMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  MethodDefinitionWrapper* _MethodDefinition2 = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());

  _MethodDefinition2->MethodDefinition->setKey(_MetaProperty1->MetaProperty);
}
void MethodDefinitionWrapper::setKeyNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  MethodDefinitionWrapper* _MethodDefinition2 = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());

  _MethodDefinition2->MethodDefinition->setKey(_NewExpression1->NewExpression);
}
void MethodDefinitionWrapper::setKeyObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  MethodDefinitionWrapper* _MethodDefinition2 = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());

  _MethodDefinition2->MethodDefinition->setKey(_ObjectExpression1->ObjectExpression);
}
void MethodDefinitionWrapper::setKeySequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  MethodDefinitionWrapper* _MethodDefinition2 = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());

  _MethodDefinition2->MethodDefinition->setKey(_SequenceExpression1->SequenceExpression);
}
void MethodDefinitionWrapper::setKeyTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  MethodDefinitionWrapper* _MethodDefinition2 = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());

  _MethodDefinition2->MethodDefinition->setKey(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void MethodDefinitionWrapper::setKeyTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  MethodDefinitionWrapper* _MethodDefinition2 = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());

  _MethodDefinition2->MethodDefinition->setKey(_TemplateLiteral1->TemplateLiteral);
}
void MethodDefinitionWrapper::setKeyThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  MethodDefinitionWrapper* _MethodDefinition2 = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());

  _MethodDefinition2->MethodDefinition->setKey(_ThisExpression1->ThisExpression);
}
void MethodDefinitionWrapper::setKeyUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  MethodDefinitionWrapper* _MethodDefinition2 = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());

  _MethodDefinition2->MethodDefinition->setKey(_UnaryExpression1->UnaryExpression);
}
void MethodDefinitionWrapper::setKeyUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  MethodDefinitionWrapper* _MethodDefinition2 = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());

  _MethodDefinition2->MethodDefinition->setKey(_UpdateExpression1->UpdateExpression);
}
void MethodDefinitionWrapper::setKeyYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  MethodDefinitionWrapper* _MethodDefinition2 = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());

  _MethodDefinition2->MethodDefinition->setKey(_YieldExpression1->YieldExpression);
}
void MethodDefinitionWrapper::setValueFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  MethodDefinitionWrapper* _MethodDefinition2 = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());

  _MethodDefinition2->MethodDefinition->setValue(_FunctionExpression1->FunctionExpression);
}
void MethodDefinitionWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  MethodDefinitionWrapper* _MethodDefinition2 = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());

  _MethodDefinition2->MethodDefinition->addComments(_Comment1->Comment);
}
void MethodDefinitionWrapper::setKind(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  MethodDefinitionWrapper* _MethodDefinition = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  if( param == "mdkConstructor" ){
    _MethodDefinition->MethodDefinition->setKind( mdkConstructor );
  }
  if( param == "mdkMethod" ){
    _MethodDefinition->MethodDefinition->setKind( mdkMethod );
  }
  if( param == "mdkGet" ){
    _MethodDefinition->MethodDefinition->setKind( mdkGet );
  }
  if( param == "mdkSet" ){
    _MethodDefinition->MethodDefinition->setKind( mdkSet );
  }
}
void MethodDefinitionWrapper::setComputed(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  MethodDefinitionWrapper* _MethodDefinition = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::transform(param.begin(), param.end(), param.begin(), ::tolower);
  std::istringstream is(param);                                    
  bool b;                                                        
  is >> std::boolalpha >> b;                                     
  _MethodDefinition->MethodDefinition->setComputed( b );
}
void MethodDefinitionWrapper::setStatic(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  MethodDefinitionWrapper* _MethodDefinition = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::transform(param.begin(), param.end(), param.begin(), ::tolower);
  std::istringstream is(param);                                    
  bool b;                                                        
  is >> std::boolalpha >> b;                                     
  _MethodDefinition->MethodDefinition->setStatic( b );
}
void MethodDefinitionWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  MethodDefinitionWrapper* _MethodDefinition = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _MethodDefinition->MethodDefinition->getPosition();
  range.setPath( param );
  _MethodDefinition->MethodDefinition->setPosition( range );
}

void MethodDefinitionWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  MethodDefinitionWrapper* _MethodDefinition = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _MethodDefinition->MethodDefinition->getPosition();
  range.setLine( ui );
  _MethodDefinition->MethodDefinition->setPosition( range );
}

void MethodDefinitionWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  MethodDefinitionWrapper* _MethodDefinition = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _MethodDefinition->MethodDefinition->getPosition();
  range.setCol( ui );
  _MethodDefinition->MethodDefinition->setPosition( range );
}

void MethodDefinitionWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  MethodDefinitionWrapper* _MethodDefinition = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _MethodDefinition->MethodDefinition->getPosition();
  range.setEndLine( ui );
  _MethodDefinition->MethodDefinition->setPosition( range );
}

void MethodDefinitionWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  MethodDefinitionWrapper* _MethodDefinition = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _MethodDefinition->MethodDefinition->getPosition();
  range.setEndCol( ui );
  _MethodDefinition->MethodDefinition->setPosition( range );
}

void MethodDefinitionWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  MethodDefinitionWrapper* _MethodDefinition = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _MethodDefinition->MethodDefinition->getPosition();
  range.setWideLine( ui );
  _MethodDefinition->MethodDefinition->setPosition( range );
}

void MethodDefinitionWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  MethodDefinitionWrapper* _MethodDefinition = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _MethodDefinition->MethodDefinition->getPosition();
  range.setWideCol( ui );
  _MethodDefinition->MethodDefinition->setPosition( range );
}

void MethodDefinitionWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  MethodDefinitionWrapper* _MethodDefinition = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _MethodDefinition->MethodDefinition->getPosition();
  range.setWideEndLine( ui );
  _MethodDefinition->MethodDefinition->setPosition( range );
}

void MethodDefinitionWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  MethodDefinitionWrapper* _MethodDefinition = ObjectWrap::Unwrap<MethodDefinitionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _MethodDefinition->MethodDefinition->getPosition();
  range.setWideEndCol( ui );
  _MethodDefinition->MethodDefinition->setPosition( range );
}

}}}} //end of namespaces