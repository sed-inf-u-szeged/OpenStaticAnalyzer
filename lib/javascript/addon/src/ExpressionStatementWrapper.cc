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

#include "../inc/ExpressionStatementWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> ExpressionStatementWrapper::constructor;

void ExpressionStatementWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "ExpressionStatementWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
  NODE_SET_PROTOTYPE_METHOD(tpl, "setExpressionArrayExpression", setExpressionArrayExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setExpressionArrowFunctionExpression", setExpressionArrowFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setExpressionAssignmentExpression", setExpressionAssignmentExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setExpressionAwaitExpression", setExpressionAwaitExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setExpressionBinaryExpression", setExpressionBinaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setExpressionCallExpression", setExpressionCallExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setExpressionClassExpression", setExpressionClassExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setExpressionConditionalExpression", setExpressionConditionalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setExpressionFunctionExpression", setExpressionFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setExpressionIdentifier", setExpressionIdentifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setExpressionBooleanLiteral", setExpressionBooleanLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setExpressionNullLiteral", setExpressionNullLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setExpressionNumberLiteral", setExpressionNumberLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setExpressionRegExpLiteral", setExpressionRegExpLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setExpressionStringLiteral", setExpressionStringLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setExpressionLogicalExpression", setExpressionLogicalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setExpressionMemberExpression", setExpressionMemberExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setExpressionMetaProperty", setExpressionMetaProperty);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setExpressionNewExpression", setExpressionNewExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setExpressionObjectExpression", setExpressionObjectExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setExpressionSequenceExpression", setExpressionSequenceExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setExpressionTaggedTemplateExpression", setExpressionTaggedTemplateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setExpressionTemplateLiteral", setExpressionTemplateLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setExpressionThisExpression", setExpressionThisExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setExpressionUnaryExpression", setExpressionUnaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setExpressionUpdateExpression", setExpressionUpdateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setExpressionYieldExpression", setExpressionYieldExpression);
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
  exports->Set(v8::String::NewFromUtf8(isolate, "ExpressionStatementWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void ExpressionStatementWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new ExpressionStatementWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    ExpressionStatementWrapper* obj = new ExpressionStatementWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `ExpressionStatementWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


ExpressionStatementWrapper::ExpressionStatementWrapper(Factory* fact)                        
{                                                   
  ExpressionStatement = fact->getFactory()->createExpressionStatementNode();          
}                                                   

ExpressionStatementWrapper::~ExpressionStatementWrapper()
{        
}        

void ExpressionStatementWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void ExpressionStatementWrapper::setExpressionArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  ExpressionStatementWrapper* _ExpressionStatement2 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args.This());

  _ExpressionStatement2->ExpressionStatement->setExpression(_ArrayExpression1->ArrayExpression);
}
void ExpressionStatementWrapper::setExpressionArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  ExpressionStatementWrapper* _ExpressionStatement2 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args.This());

  _ExpressionStatement2->ExpressionStatement->setExpression(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void ExpressionStatementWrapper::setExpressionAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  ExpressionStatementWrapper* _ExpressionStatement2 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args.This());

  _ExpressionStatement2->ExpressionStatement->setExpression(_AssignmentExpression1->AssignmentExpression);
}
void ExpressionStatementWrapper::setExpressionAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  ExpressionStatementWrapper* _ExpressionStatement2 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args.This());

  _ExpressionStatement2->ExpressionStatement->setExpression(_AwaitExpression1->AwaitExpression);
}
void ExpressionStatementWrapper::setExpressionBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  ExpressionStatementWrapper* _ExpressionStatement2 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args.This());

  _ExpressionStatement2->ExpressionStatement->setExpression(_BinaryExpression1->BinaryExpression);
}
void ExpressionStatementWrapper::setExpressionCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  ExpressionStatementWrapper* _ExpressionStatement2 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args.This());

  _ExpressionStatement2->ExpressionStatement->setExpression(_CallExpression1->CallExpression);
}
void ExpressionStatementWrapper::setExpressionClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  ExpressionStatementWrapper* _ExpressionStatement2 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args.This());

  _ExpressionStatement2->ExpressionStatement->setExpression(_ClassExpression1->ClassExpression);
}
void ExpressionStatementWrapper::setExpressionConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  ExpressionStatementWrapper* _ExpressionStatement2 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args.This());

  _ExpressionStatement2->ExpressionStatement->setExpression(_ConditionalExpression1->ConditionalExpression);
}
void ExpressionStatementWrapper::setExpressionFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  ExpressionStatementWrapper* _ExpressionStatement2 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args.This());

  _ExpressionStatement2->ExpressionStatement->setExpression(_FunctionExpression1->FunctionExpression);
}
void ExpressionStatementWrapper::setExpressionIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  ExpressionStatementWrapper* _ExpressionStatement2 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args.This());

  _ExpressionStatement2->ExpressionStatement->setExpression(_Identifier1->Identifier);
}
void ExpressionStatementWrapper::setExpressionBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  ExpressionStatementWrapper* _ExpressionStatement2 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args.This());

  _ExpressionStatement2->ExpressionStatement->setExpression(_BooleanLiteral1->BooleanLiteral);
}
void ExpressionStatementWrapper::setExpressionNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  ExpressionStatementWrapper* _ExpressionStatement2 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args.This());

  _ExpressionStatement2->ExpressionStatement->setExpression(_NullLiteral1->NullLiteral);
}
void ExpressionStatementWrapper::setExpressionNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  ExpressionStatementWrapper* _ExpressionStatement2 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args.This());

  _ExpressionStatement2->ExpressionStatement->setExpression(_NumberLiteral1->NumberLiteral);
}
void ExpressionStatementWrapper::setExpressionRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  ExpressionStatementWrapper* _ExpressionStatement2 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args.This());

  _ExpressionStatement2->ExpressionStatement->setExpression(_RegExpLiteral1->RegExpLiteral);
}
void ExpressionStatementWrapper::setExpressionStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  ExpressionStatementWrapper* _ExpressionStatement2 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args.This());

  _ExpressionStatement2->ExpressionStatement->setExpression(_StringLiteral1->StringLiteral);
}
void ExpressionStatementWrapper::setExpressionLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  ExpressionStatementWrapper* _ExpressionStatement2 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args.This());

  _ExpressionStatement2->ExpressionStatement->setExpression(_LogicalExpression1->LogicalExpression);
}
void ExpressionStatementWrapper::setExpressionMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  ExpressionStatementWrapper* _ExpressionStatement2 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args.This());

  _ExpressionStatement2->ExpressionStatement->setExpression(_MemberExpression1->MemberExpression);
}
void ExpressionStatementWrapper::setExpressionMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  ExpressionStatementWrapper* _ExpressionStatement2 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args.This());

  _ExpressionStatement2->ExpressionStatement->setExpression(_MetaProperty1->MetaProperty);
}
void ExpressionStatementWrapper::setExpressionNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  ExpressionStatementWrapper* _ExpressionStatement2 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args.This());

  _ExpressionStatement2->ExpressionStatement->setExpression(_NewExpression1->NewExpression);
}
void ExpressionStatementWrapper::setExpressionObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  ExpressionStatementWrapper* _ExpressionStatement2 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args.This());

  _ExpressionStatement2->ExpressionStatement->setExpression(_ObjectExpression1->ObjectExpression);
}
void ExpressionStatementWrapper::setExpressionSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  ExpressionStatementWrapper* _ExpressionStatement2 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args.This());

  _ExpressionStatement2->ExpressionStatement->setExpression(_SequenceExpression1->SequenceExpression);
}
void ExpressionStatementWrapper::setExpressionTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  ExpressionStatementWrapper* _ExpressionStatement2 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args.This());

  _ExpressionStatement2->ExpressionStatement->setExpression(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void ExpressionStatementWrapper::setExpressionTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  ExpressionStatementWrapper* _ExpressionStatement2 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args.This());

  _ExpressionStatement2->ExpressionStatement->setExpression(_TemplateLiteral1->TemplateLiteral);
}
void ExpressionStatementWrapper::setExpressionThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  ExpressionStatementWrapper* _ExpressionStatement2 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args.This());

  _ExpressionStatement2->ExpressionStatement->setExpression(_ThisExpression1->ThisExpression);
}
void ExpressionStatementWrapper::setExpressionUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  ExpressionStatementWrapper* _ExpressionStatement2 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args.This());

  _ExpressionStatement2->ExpressionStatement->setExpression(_UnaryExpression1->UnaryExpression);
}
void ExpressionStatementWrapper::setExpressionUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  ExpressionStatementWrapper* _ExpressionStatement2 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args.This());

  _ExpressionStatement2->ExpressionStatement->setExpression(_UpdateExpression1->UpdateExpression);
}
void ExpressionStatementWrapper::setExpressionYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  ExpressionStatementWrapper* _ExpressionStatement2 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args.This());

  _ExpressionStatement2->ExpressionStatement->setExpression(_YieldExpression1->YieldExpression);
}
void ExpressionStatementWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  ExpressionStatementWrapper* _ExpressionStatement2 = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args.This());

  _ExpressionStatement2->ExpressionStatement->addComments(_Comment1->Comment);
}
void ExpressionStatementWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  ExpressionStatementWrapper* _ExpressionStatement = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _ExpressionStatement->ExpressionStatement->getPosition();
  range.setPath( param );
  _ExpressionStatement->ExpressionStatement->setPosition( range );
}

void ExpressionStatementWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExpressionStatementWrapper* _ExpressionStatement = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExpressionStatement->ExpressionStatement->getPosition();
  range.setLine( ui );
  _ExpressionStatement->ExpressionStatement->setPosition( range );
}

void ExpressionStatementWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExpressionStatementWrapper* _ExpressionStatement = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExpressionStatement->ExpressionStatement->getPosition();
  range.setCol( ui );
  _ExpressionStatement->ExpressionStatement->setPosition( range );
}

void ExpressionStatementWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExpressionStatementWrapper* _ExpressionStatement = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExpressionStatement->ExpressionStatement->getPosition();
  range.setEndLine( ui );
  _ExpressionStatement->ExpressionStatement->setPosition( range );
}

void ExpressionStatementWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExpressionStatementWrapper* _ExpressionStatement = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExpressionStatement->ExpressionStatement->getPosition();
  range.setEndCol( ui );
  _ExpressionStatement->ExpressionStatement->setPosition( range );
}

void ExpressionStatementWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExpressionStatementWrapper* _ExpressionStatement = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExpressionStatement->ExpressionStatement->getPosition();
  range.setWideLine( ui );
  _ExpressionStatement->ExpressionStatement->setPosition( range );
}

void ExpressionStatementWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExpressionStatementWrapper* _ExpressionStatement = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExpressionStatement->ExpressionStatement->getPosition();
  range.setWideCol( ui );
  _ExpressionStatement->ExpressionStatement->setPosition( range );
}

void ExpressionStatementWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExpressionStatementWrapper* _ExpressionStatement = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExpressionStatement->ExpressionStatement->getPosition();
  range.setWideEndLine( ui );
  _ExpressionStatement->ExpressionStatement->setPosition( range );
}

void ExpressionStatementWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ExpressionStatementWrapper* _ExpressionStatement = ObjectWrap::Unwrap<ExpressionStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ExpressionStatement->ExpressionStatement->getPosition();
  range.setWideEndCol( ui );
  _ExpressionStatement->ExpressionStatement->setPosition( range );
}

}}}} //end of namespaces