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

#include "../inc/SwitchStatementWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> SwitchStatementWrapper::constructor;

void SwitchStatementWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "SwitchStatementWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDiscriminantArrayExpression", setDiscriminantArrayExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDiscriminantArrowFunctionExpression", setDiscriminantArrowFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDiscriminantAssignmentExpression", setDiscriminantAssignmentExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDiscriminantAwaitExpression", setDiscriminantAwaitExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDiscriminantBinaryExpression", setDiscriminantBinaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDiscriminantCallExpression", setDiscriminantCallExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDiscriminantClassExpression", setDiscriminantClassExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDiscriminantConditionalExpression", setDiscriminantConditionalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDiscriminantFunctionExpression", setDiscriminantFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDiscriminantIdentifier", setDiscriminantIdentifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDiscriminantBooleanLiteral", setDiscriminantBooleanLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDiscriminantNullLiteral", setDiscriminantNullLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDiscriminantNumberLiteral", setDiscriminantNumberLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDiscriminantRegExpLiteral", setDiscriminantRegExpLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDiscriminantStringLiteral", setDiscriminantStringLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDiscriminantLogicalExpression", setDiscriminantLogicalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDiscriminantMemberExpression", setDiscriminantMemberExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDiscriminantMetaProperty", setDiscriminantMetaProperty);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDiscriminantNewExpression", setDiscriminantNewExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDiscriminantObjectExpression", setDiscriminantObjectExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDiscriminantSequenceExpression", setDiscriminantSequenceExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDiscriminantTaggedTemplateExpression", setDiscriminantTaggedTemplateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDiscriminantTemplateLiteral", setDiscriminantTemplateLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDiscriminantThisExpression", setDiscriminantThisExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDiscriminantUnaryExpression", setDiscriminantUnaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDiscriminantUpdateExpression", setDiscriminantUpdateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setDiscriminantYieldExpression", setDiscriminantYieldExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addCasesSwitchCase", addCasesSwitchCase);
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
  exports->Set(v8::String::NewFromUtf8(isolate, "SwitchStatementWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void SwitchStatementWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new SwitchStatementWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    SwitchStatementWrapper* obj = new SwitchStatementWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `SwitchStatementWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


SwitchStatementWrapper::SwitchStatementWrapper(Factory* fact)                        
{                                                   
  SwitchStatement = fact->getFactory()->createSwitchStatementNode();          
}                                                   

SwitchStatementWrapper::~SwitchStatementWrapper()
{        
}        

void SwitchStatementWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void SwitchStatementWrapper::setDiscriminantArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  SwitchStatementWrapper* _SwitchStatement2 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());

  _SwitchStatement2->SwitchStatement->setDiscriminant(_ArrayExpression1->ArrayExpression);
}
void SwitchStatementWrapper::setDiscriminantArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  SwitchStatementWrapper* _SwitchStatement2 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());

  _SwitchStatement2->SwitchStatement->setDiscriminant(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void SwitchStatementWrapper::setDiscriminantAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  SwitchStatementWrapper* _SwitchStatement2 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());

  _SwitchStatement2->SwitchStatement->setDiscriminant(_AssignmentExpression1->AssignmentExpression);
}
void SwitchStatementWrapper::setDiscriminantAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  SwitchStatementWrapper* _SwitchStatement2 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());

  _SwitchStatement2->SwitchStatement->setDiscriminant(_AwaitExpression1->AwaitExpression);
}
void SwitchStatementWrapper::setDiscriminantBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  SwitchStatementWrapper* _SwitchStatement2 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());

  _SwitchStatement2->SwitchStatement->setDiscriminant(_BinaryExpression1->BinaryExpression);
}
void SwitchStatementWrapper::setDiscriminantCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  SwitchStatementWrapper* _SwitchStatement2 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());

  _SwitchStatement2->SwitchStatement->setDiscriminant(_CallExpression1->CallExpression);
}
void SwitchStatementWrapper::setDiscriminantClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  SwitchStatementWrapper* _SwitchStatement2 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());

  _SwitchStatement2->SwitchStatement->setDiscriminant(_ClassExpression1->ClassExpression);
}
void SwitchStatementWrapper::setDiscriminantConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  SwitchStatementWrapper* _SwitchStatement2 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());

  _SwitchStatement2->SwitchStatement->setDiscriminant(_ConditionalExpression1->ConditionalExpression);
}
void SwitchStatementWrapper::setDiscriminantFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  SwitchStatementWrapper* _SwitchStatement2 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());

  _SwitchStatement2->SwitchStatement->setDiscriminant(_FunctionExpression1->FunctionExpression);
}
void SwitchStatementWrapper::setDiscriminantIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  SwitchStatementWrapper* _SwitchStatement2 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());

  _SwitchStatement2->SwitchStatement->setDiscriminant(_Identifier1->Identifier);
}
void SwitchStatementWrapper::setDiscriminantBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  SwitchStatementWrapper* _SwitchStatement2 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());

  _SwitchStatement2->SwitchStatement->setDiscriminant(_BooleanLiteral1->BooleanLiteral);
}
void SwitchStatementWrapper::setDiscriminantNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  SwitchStatementWrapper* _SwitchStatement2 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());

  _SwitchStatement2->SwitchStatement->setDiscriminant(_NullLiteral1->NullLiteral);
}
void SwitchStatementWrapper::setDiscriminantNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  SwitchStatementWrapper* _SwitchStatement2 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());

  _SwitchStatement2->SwitchStatement->setDiscriminant(_NumberLiteral1->NumberLiteral);
}
void SwitchStatementWrapper::setDiscriminantRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  SwitchStatementWrapper* _SwitchStatement2 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());

  _SwitchStatement2->SwitchStatement->setDiscriminant(_RegExpLiteral1->RegExpLiteral);
}
void SwitchStatementWrapper::setDiscriminantStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  SwitchStatementWrapper* _SwitchStatement2 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());

  _SwitchStatement2->SwitchStatement->setDiscriminant(_StringLiteral1->StringLiteral);
}
void SwitchStatementWrapper::setDiscriminantLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  SwitchStatementWrapper* _SwitchStatement2 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());

  _SwitchStatement2->SwitchStatement->setDiscriminant(_LogicalExpression1->LogicalExpression);
}
void SwitchStatementWrapper::setDiscriminantMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  SwitchStatementWrapper* _SwitchStatement2 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());

  _SwitchStatement2->SwitchStatement->setDiscriminant(_MemberExpression1->MemberExpression);
}
void SwitchStatementWrapper::setDiscriminantMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  SwitchStatementWrapper* _SwitchStatement2 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());

  _SwitchStatement2->SwitchStatement->setDiscriminant(_MetaProperty1->MetaProperty);
}
void SwitchStatementWrapper::setDiscriminantNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  SwitchStatementWrapper* _SwitchStatement2 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());

  _SwitchStatement2->SwitchStatement->setDiscriminant(_NewExpression1->NewExpression);
}
void SwitchStatementWrapper::setDiscriminantObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  SwitchStatementWrapper* _SwitchStatement2 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());

  _SwitchStatement2->SwitchStatement->setDiscriminant(_ObjectExpression1->ObjectExpression);
}
void SwitchStatementWrapper::setDiscriminantSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  SwitchStatementWrapper* _SwitchStatement2 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());

  _SwitchStatement2->SwitchStatement->setDiscriminant(_SequenceExpression1->SequenceExpression);
}
void SwitchStatementWrapper::setDiscriminantTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  SwitchStatementWrapper* _SwitchStatement2 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());

  _SwitchStatement2->SwitchStatement->setDiscriminant(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void SwitchStatementWrapper::setDiscriminantTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  SwitchStatementWrapper* _SwitchStatement2 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());

  _SwitchStatement2->SwitchStatement->setDiscriminant(_TemplateLiteral1->TemplateLiteral);
}
void SwitchStatementWrapper::setDiscriminantThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  SwitchStatementWrapper* _SwitchStatement2 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());

  _SwitchStatement2->SwitchStatement->setDiscriminant(_ThisExpression1->ThisExpression);
}
void SwitchStatementWrapper::setDiscriminantUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  SwitchStatementWrapper* _SwitchStatement2 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());

  _SwitchStatement2->SwitchStatement->setDiscriminant(_UnaryExpression1->UnaryExpression);
}
void SwitchStatementWrapper::setDiscriminantUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  SwitchStatementWrapper* _SwitchStatement2 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());

  _SwitchStatement2->SwitchStatement->setDiscriminant(_UpdateExpression1->UpdateExpression);
}
void SwitchStatementWrapper::setDiscriminantYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  SwitchStatementWrapper* _SwitchStatement2 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());

  _SwitchStatement2->SwitchStatement->setDiscriminant(_YieldExpression1->YieldExpression);
}
void SwitchStatementWrapper::addCasesSwitchCase(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SwitchCaseWrapper* _SwitchCase1 = ObjectWrap::Unwrap<SwitchCaseWrapper>(args[0]->ToObject());
  SwitchStatementWrapper* _SwitchStatement2 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());

  _SwitchStatement2->SwitchStatement->addCases(_SwitchCase1->SwitchCase);
}
void SwitchStatementWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  SwitchStatementWrapper* _SwitchStatement2 = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());

  _SwitchStatement2->SwitchStatement->addComments(_Comment1->Comment);
}
void SwitchStatementWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  SwitchStatementWrapper* _SwitchStatement = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _SwitchStatement->SwitchStatement->getPosition();
  range.setPath( param );
  _SwitchStatement->SwitchStatement->setPosition( range );
}

void SwitchStatementWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  SwitchStatementWrapper* _SwitchStatement = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _SwitchStatement->SwitchStatement->getPosition();
  range.setLine( ui );
  _SwitchStatement->SwitchStatement->setPosition( range );
}

void SwitchStatementWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  SwitchStatementWrapper* _SwitchStatement = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _SwitchStatement->SwitchStatement->getPosition();
  range.setCol( ui );
  _SwitchStatement->SwitchStatement->setPosition( range );
}

void SwitchStatementWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  SwitchStatementWrapper* _SwitchStatement = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _SwitchStatement->SwitchStatement->getPosition();
  range.setEndLine( ui );
  _SwitchStatement->SwitchStatement->setPosition( range );
}

void SwitchStatementWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  SwitchStatementWrapper* _SwitchStatement = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _SwitchStatement->SwitchStatement->getPosition();
  range.setEndCol( ui );
  _SwitchStatement->SwitchStatement->setPosition( range );
}

void SwitchStatementWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  SwitchStatementWrapper* _SwitchStatement = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _SwitchStatement->SwitchStatement->getPosition();
  range.setWideLine( ui );
  _SwitchStatement->SwitchStatement->setPosition( range );
}

void SwitchStatementWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  SwitchStatementWrapper* _SwitchStatement = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _SwitchStatement->SwitchStatement->getPosition();
  range.setWideCol( ui );
  _SwitchStatement->SwitchStatement->setPosition( range );
}

void SwitchStatementWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  SwitchStatementWrapper* _SwitchStatement = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _SwitchStatement->SwitchStatement->getPosition();
  range.setWideEndLine( ui );
  _SwitchStatement->SwitchStatement->setPosition( range );
}

void SwitchStatementWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  SwitchStatementWrapper* _SwitchStatement = ObjectWrap::Unwrap<SwitchStatementWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _SwitchStatement->SwitchStatement->getPosition();
  range.setWideEndCol( ui );
  _SwitchStatement->SwitchStatement->setPosition( range );
}

}}}} //end of namespaces