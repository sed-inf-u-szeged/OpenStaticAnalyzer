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

#include "../inc/TemplateLiteralWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> TemplateLiteralWrapper::constructor;

void TemplateLiteralWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "TemplateLiteralWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
  NODE_SET_PROTOTYPE_METHOD(tpl, "addQuasisTemplateElement", addQuasisTemplateElement);
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
  exports->Set(v8::String::NewFromUtf8(isolate, "TemplateLiteralWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void TemplateLiteralWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new TemplateLiteralWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    TemplateLiteralWrapper* obj = new TemplateLiteralWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `TemplateLiteralWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


TemplateLiteralWrapper::TemplateLiteralWrapper(Factory* fact)                        
{                                                   
  TemplateLiteral = fact->getFactory()->createTemplateLiteralNode();          
}                                                   

TemplateLiteralWrapper::~TemplateLiteralWrapper()
{        
}        

void TemplateLiteralWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void TemplateLiteralWrapper::addQuasisTemplateElement(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateElementWrapper* _TemplateElement1 = ObjectWrap::Unwrap<TemplateElementWrapper>(args[0]->ToObject());
  TemplateLiteralWrapper* _TemplateLiteral2 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());

  _TemplateLiteral2->TemplateLiteral->addQuasis(_TemplateElement1->TemplateElement);
}
void TemplateLiteralWrapper::addExpressionsArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  TemplateLiteralWrapper* _TemplateLiteral2 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());

  _TemplateLiteral2->TemplateLiteral->addExpressions(_ArrayExpression1->ArrayExpression);
}
void TemplateLiteralWrapper::addExpressionsArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  TemplateLiteralWrapper* _TemplateLiteral2 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());

  _TemplateLiteral2->TemplateLiteral->addExpressions(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void TemplateLiteralWrapper::addExpressionsAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  TemplateLiteralWrapper* _TemplateLiteral2 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());

  _TemplateLiteral2->TemplateLiteral->addExpressions(_AssignmentExpression1->AssignmentExpression);
}
void TemplateLiteralWrapper::addExpressionsAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  TemplateLiteralWrapper* _TemplateLiteral2 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());

  _TemplateLiteral2->TemplateLiteral->addExpressions(_AwaitExpression1->AwaitExpression);
}
void TemplateLiteralWrapper::addExpressionsBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  TemplateLiteralWrapper* _TemplateLiteral2 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());

  _TemplateLiteral2->TemplateLiteral->addExpressions(_BinaryExpression1->BinaryExpression);
}
void TemplateLiteralWrapper::addExpressionsCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  TemplateLiteralWrapper* _TemplateLiteral2 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());

  _TemplateLiteral2->TemplateLiteral->addExpressions(_CallExpression1->CallExpression);
}
void TemplateLiteralWrapper::addExpressionsClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  TemplateLiteralWrapper* _TemplateLiteral2 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());

  _TemplateLiteral2->TemplateLiteral->addExpressions(_ClassExpression1->ClassExpression);
}
void TemplateLiteralWrapper::addExpressionsConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  TemplateLiteralWrapper* _TemplateLiteral2 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());

  _TemplateLiteral2->TemplateLiteral->addExpressions(_ConditionalExpression1->ConditionalExpression);
}
void TemplateLiteralWrapper::addExpressionsFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  TemplateLiteralWrapper* _TemplateLiteral2 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());

  _TemplateLiteral2->TemplateLiteral->addExpressions(_FunctionExpression1->FunctionExpression);
}
void TemplateLiteralWrapper::addExpressionsIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  TemplateLiteralWrapper* _TemplateLiteral2 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());

  _TemplateLiteral2->TemplateLiteral->addExpressions(_Identifier1->Identifier);
}
void TemplateLiteralWrapper::addExpressionsBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  TemplateLiteralWrapper* _TemplateLiteral2 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());

  _TemplateLiteral2->TemplateLiteral->addExpressions(_BooleanLiteral1->BooleanLiteral);
}
void TemplateLiteralWrapper::addExpressionsNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  TemplateLiteralWrapper* _TemplateLiteral2 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());

  _TemplateLiteral2->TemplateLiteral->addExpressions(_NullLiteral1->NullLiteral);
}
void TemplateLiteralWrapper::addExpressionsNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  TemplateLiteralWrapper* _TemplateLiteral2 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());

  _TemplateLiteral2->TemplateLiteral->addExpressions(_NumberLiteral1->NumberLiteral);
}
void TemplateLiteralWrapper::addExpressionsRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  TemplateLiteralWrapper* _TemplateLiteral2 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());

  _TemplateLiteral2->TemplateLiteral->addExpressions(_RegExpLiteral1->RegExpLiteral);
}
void TemplateLiteralWrapper::addExpressionsStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  TemplateLiteralWrapper* _TemplateLiteral2 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());

  _TemplateLiteral2->TemplateLiteral->addExpressions(_StringLiteral1->StringLiteral);
}
void TemplateLiteralWrapper::addExpressionsLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  TemplateLiteralWrapper* _TemplateLiteral2 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());

  _TemplateLiteral2->TemplateLiteral->addExpressions(_LogicalExpression1->LogicalExpression);
}
void TemplateLiteralWrapper::addExpressionsMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  TemplateLiteralWrapper* _TemplateLiteral2 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());

  _TemplateLiteral2->TemplateLiteral->addExpressions(_MemberExpression1->MemberExpression);
}
void TemplateLiteralWrapper::addExpressionsMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  TemplateLiteralWrapper* _TemplateLiteral2 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());

  _TemplateLiteral2->TemplateLiteral->addExpressions(_MetaProperty1->MetaProperty);
}
void TemplateLiteralWrapper::addExpressionsNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  TemplateLiteralWrapper* _TemplateLiteral2 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());

  _TemplateLiteral2->TemplateLiteral->addExpressions(_NewExpression1->NewExpression);
}
void TemplateLiteralWrapper::addExpressionsObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  TemplateLiteralWrapper* _TemplateLiteral2 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());

  _TemplateLiteral2->TemplateLiteral->addExpressions(_ObjectExpression1->ObjectExpression);
}
void TemplateLiteralWrapper::addExpressionsSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  TemplateLiteralWrapper* _TemplateLiteral2 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());

  _TemplateLiteral2->TemplateLiteral->addExpressions(_SequenceExpression1->SequenceExpression);
}
void TemplateLiteralWrapper::addExpressionsTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  TemplateLiteralWrapper* _TemplateLiteral2 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());

  _TemplateLiteral2->TemplateLiteral->addExpressions(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void TemplateLiteralWrapper::addExpressionsTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  TemplateLiteralWrapper* _TemplateLiteral2 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());

  _TemplateLiteral2->TemplateLiteral->addExpressions(_TemplateLiteral1->TemplateLiteral);
}
void TemplateLiteralWrapper::addExpressionsThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  TemplateLiteralWrapper* _TemplateLiteral2 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());

  _TemplateLiteral2->TemplateLiteral->addExpressions(_ThisExpression1->ThisExpression);
}
void TemplateLiteralWrapper::addExpressionsUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  TemplateLiteralWrapper* _TemplateLiteral2 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());

  _TemplateLiteral2->TemplateLiteral->addExpressions(_UnaryExpression1->UnaryExpression);
}
void TemplateLiteralWrapper::addExpressionsUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  TemplateLiteralWrapper* _TemplateLiteral2 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());

  _TemplateLiteral2->TemplateLiteral->addExpressions(_UpdateExpression1->UpdateExpression);
}
void TemplateLiteralWrapper::addExpressionsYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  TemplateLiteralWrapper* _TemplateLiteral2 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());

  _TemplateLiteral2->TemplateLiteral->addExpressions(_YieldExpression1->YieldExpression);
}
void TemplateLiteralWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  TemplateLiteralWrapper* _TemplateLiteral2 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());

  _TemplateLiteral2->TemplateLiteral->addComments(_Comment1->Comment);
}
void TemplateLiteralWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  TemplateLiteralWrapper* _TemplateLiteral = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _TemplateLiteral->TemplateLiteral->getPosition();
  range.setPath( param );
  _TemplateLiteral->TemplateLiteral->setPosition( range );
}

void TemplateLiteralWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  TemplateLiteralWrapper* _TemplateLiteral = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _TemplateLiteral->TemplateLiteral->getPosition();
  range.setLine( ui );
  _TemplateLiteral->TemplateLiteral->setPosition( range );
}

void TemplateLiteralWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  TemplateLiteralWrapper* _TemplateLiteral = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _TemplateLiteral->TemplateLiteral->getPosition();
  range.setCol( ui );
  _TemplateLiteral->TemplateLiteral->setPosition( range );
}

void TemplateLiteralWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  TemplateLiteralWrapper* _TemplateLiteral = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _TemplateLiteral->TemplateLiteral->getPosition();
  range.setEndLine( ui );
  _TemplateLiteral->TemplateLiteral->setPosition( range );
}

void TemplateLiteralWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  TemplateLiteralWrapper* _TemplateLiteral = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _TemplateLiteral->TemplateLiteral->getPosition();
  range.setEndCol( ui );
  _TemplateLiteral->TemplateLiteral->setPosition( range );
}

void TemplateLiteralWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  TemplateLiteralWrapper* _TemplateLiteral = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _TemplateLiteral->TemplateLiteral->getPosition();
  range.setWideLine( ui );
  _TemplateLiteral->TemplateLiteral->setPosition( range );
}

void TemplateLiteralWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  TemplateLiteralWrapper* _TemplateLiteral = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _TemplateLiteral->TemplateLiteral->getPosition();
  range.setWideCol( ui );
  _TemplateLiteral->TemplateLiteral->setPosition( range );
}

void TemplateLiteralWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  TemplateLiteralWrapper* _TemplateLiteral = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _TemplateLiteral->TemplateLiteral->getPosition();
  range.setWideEndLine( ui );
  _TemplateLiteral->TemplateLiteral->setPosition( range );
}

void TemplateLiteralWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  TemplateLiteralWrapper* _TemplateLiteral = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _TemplateLiteral->TemplateLiteral->getPosition();
  range.setWideEndCol( ui );
  _TemplateLiteral->TemplateLiteral->setPosition( range );
}

}}}} //end of namespaces