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

#include "../inc/TaggedTemplateExpressionWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> TaggedTemplateExpressionWrapper::constructor;

void TaggedTemplateExpressionWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "TaggedTemplateExpressionWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTagArrayExpression", setTagArrayExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTagArrowFunctionExpression", setTagArrowFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTagAssignmentExpression", setTagAssignmentExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTagAwaitExpression", setTagAwaitExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTagBinaryExpression", setTagBinaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTagCallExpression", setTagCallExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTagClassExpression", setTagClassExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTagConditionalExpression", setTagConditionalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTagFunctionExpression", setTagFunctionExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTagIdentifier", setTagIdentifier);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTagBooleanLiteral", setTagBooleanLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTagNullLiteral", setTagNullLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTagNumberLiteral", setTagNumberLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTagRegExpLiteral", setTagRegExpLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTagStringLiteral", setTagStringLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTagLogicalExpression", setTagLogicalExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTagMemberExpression", setTagMemberExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTagMetaProperty", setTagMetaProperty);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTagNewExpression", setTagNewExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTagObjectExpression", setTagObjectExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTagSequenceExpression", setTagSequenceExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTagTaggedTemplateExpression", setTagTaggedTemplateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTagTemplateLiteral", setTagTemplateLiteral);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTagThisExpression", setTagThisExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTagUnaryExpression", setTagUnaryExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTagUpdateExpression", setTagUpdateExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setTagYieldExpression", setTagYieldExpression);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setQuasiTemplateLiteral", setQuasiTemplateLiteral);
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
  exports->Set(v8::String::NewFromUtf8(isolate, "TaggedTemplateExpressionWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void TaggedTemplateExpressionWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new TaggedTemplateExpressionWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    TaggedTemplateExpressionWrapper* obj = new TaggedTemplateExpressionWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `TaggedTemplateExpressionWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


TaggedTemplateExpressionWrapper::TaggedTemplateExpressionWrapper(Factory* fact)                        
{                                                   
  TaggedTemplateExpression = fact->getFactory()->createTaggedTemplateExpressionNode();          
}                                                   

TaggedTemplateExpressionWrapper::~TaggedTemplateExpressionWrapper()
{        
}        

void TaggedTemplateExpressionWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void TaggedTemplateExpressionWrapper::setTagArrayExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrayExpressionWrapper* _ArrayExpression1 = ObjectWrap::Unwrap<ArrayExpressionWrapper>(args[0]->ToObject());
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression2 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());

  _TaggedTemplateExpression2->TaggedTemplateExpression->setTag(_ArrayExpression1->ArrayExpression);
}
void TaggedTemplateExpressionWrapper::setTagArrowFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ArrowFunctionExpressionWrapper* _ArrowFunctionExpression1 = ObjectWrap::Unwrap<ArrowFunctionExpressionWrapper>(args[0]->ToObject());
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression2 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());

  _TaggedTemplateExpression2->TaggedTemplateExpression->setTag(_ArrowFunctionExpression1->ArrowFunctionExpression);
}
void TaggedTemplateExpressionWrapper::setTagAssignmentExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AssignmentExpressionWrapper* _AssignmentExpression1 = ObjectWrap::Unwrap<AssignmentExpressionWrapper>(args[0]->ToObject());
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression2 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());

  _TaggedTemplateExpression2->TaggedTemplateExpression->setTag(_AssignmentExpression1->AssignmentExpression);
}
void TaggedTemplateExpressionWrapper::setTagAwaitExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  AwaitExpressionWrapper* _AwaitExpression1 = ObjectWrap::Unwrap<AwaitExpressionWrapper>(args[0]->ToObject());
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression2 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());

  _TaggedTemplateExpression2->TaggedTemplateExpression->setTag(_AwaitExpression1->AwaitExpression);
}
void TaggedTemplateExpressionWrapper::setTagBinaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BinaryExpressionWrapper* _BinaryExpression1 = ObjectWrap::Unwrap<BinaryExpressionWrapper>(args[0]->ToObject());
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression2 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());

  _TaggedTemplateExpression2->TaggedTemplateExpression->setTag(_BinaryExpression1->BinaryExpression);
}
void TaggedTemplateExpressionWrapper::setTagCallExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CallExpressionWrapper* _CallExpression1 = ObjectWrap::Unwrap<CallExpressionWrapper>(args[0]->ToObject());
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression2 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());

  _TaggedTemplateExpression2->TaggedTemplateExpression->setTag(_CallExpression1->CallExpression);
}
void TaggedTemplateExpressionWrapper::setTagClassExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ClassExpressionWrapper* _ClassExpression1 = ObjectWrap::Unwrap<ClassExpressionWrapper>(args[0]->ToObject());
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression2 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());

  _TaggedTemplateExpression2->TaggedTemplateExpression->setTag(_ClassExpression1->ClassExpression);
}
void TaggedTemplateExpressionWrapper::setTagConditionalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ConditionalExpressionWrapper* _ConditionalExpression1 = ObjectWrap::Unwrap<ConditionalExpressionWrapper>(args[0]->ToObject());
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression2 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());

  _TaggedTemplateExpression2->TaggedTemplateExpression->setTag(_ConditionalExpression1->ConditionalExpression);
}
void TaggedTemplateExpressionWrapper::setTagFunctionExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  FunctionExpressionWrapper* _FunctionExpression1 = ObjectWrap::Unwrap<FunctionExpressionWrapper>(args[0]->ToObject());
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression2 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());

  _TaggedTemplateExpression2->TaggedTemplateExpression->setTag(_FunctionExpression1->FunctionExpression);
}
void TaggedTemplateExpressionWrapper::setTagIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression2 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());

  _TaggedTemplateExpression2->TaggedTemplateExpression->setTag(_Identifier1->Identifier);
}
void TaggedTemplateExpressionWrapper::setTagBooleanLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  BooleanLiteralWrapper* _BooleanLiteral1 = ObjectWrap::Unwrap<BooleanLiteralWrapper>(args[0]->ToObject());
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression2 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());

  _TaggedTemplateExpression2->TaggedTemplateExpression->setTag(_BooleanLiteral1->BooleanLiteral);
}
void TaggedTemplateExpressionWrapper::setTagNullLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NullLiteralWrapper* _NullLiteral1 = ObjectWrap::Unwrap<NullLiteralWrapper>(args[0]->ToObject());
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression2 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());

  _TaggedTemplateExpression2->TaggedTemplateExpression->setTag(_NullLiteral1->NullLiteral);
}
void TaggedTemplateExpressionWrapper::setTagNumberLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NumberLiteralWrapper* _NumberLiteral1 = ObjectWrap::Unwrap<NumberLiteralWrapper>(args[0]->ToObject());
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression2 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());

  _TaggedTemplateExpression2->TaggedTemplateExpression->setTag(_NumberLiteral1->NumberLiteral);
}
void TaggedTemplateExpressionWrapper::setTagRegExpLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  RegExpLiteralWrapper* _RegExpLiteral1 = ObjectWrap::Unwrap<RegExpLiteralWrapper>(args[0]->ToObject());
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression2 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());

  _TaggedTemplateExpression2->TaggedTemplateExpression->setTag(_RegExpLiteral1->RegExpLiteral);
}
void TaggedTemplateExpressionWrapper::setTagStringLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  StringLiteralWrapper* _StringLiteral1 = ObjectWrap::Unwrap<StringLiteralWrapper>(args[0]->ToObject());
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression2 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());

  _TaggedTemplateExpression2->TaggedTemplateExpression->setTag(_StringLiteral1->StringLiteral);
}
void TaggedTemplateExpressionWrapper::setTagLogicalExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  LogicalExpressionWrapper* _LogicalExpression1 = ObjectWrap::Unwrap<LogicalExpressionWrapper>(args[0]->ToObject());
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression2 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());

  _TaggedTemplateExpression2->TaggedTemplateExpression->setTag(_LogicalExpression1->LogicalExpression);
}
void TaggedTemplateExpressionWrapper::setTagMemberExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MemberExpressionWrapper* _MemberExpression1 = ObjectWrap::Unwrap<MemberExpressionWrapper>(args[0]->ToObject());
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression2 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());

  _TaggedTemplateExpression2->TaggedTemplateExpression->setTag(_MemberExpression1->MemberExpression);
}
void TaggedTemplateExpressionWrapper::setTagMetaProperty(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  MetaPropertyWrapper* _MetaProperty1 = ObjectWrap::Unwrap<MetaPropertyWrapper>(args[0]->ToObject());
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression2 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());

  _TaggedTemplateExpression2->TaggedTemplateExpression->setTag(_MetaProperty1->MetaProperty);
}
void TaggedTemplateExpressionWrapper::setTagNewExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  NewExpressionWrapper* _NewExpression1 = ObjectWrap::Unwrap<NewExpressionWrapper>(args[0]->ToObject());
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression2 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());

  _TaggedTemplateExpression2->TaggedTemplateExpression->setTag(_NewExpression1->NewExpression);
}
void TaggedTemplateExpressionWrapper::setTagObjectExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ObjectExpressionWrapper* _ObjectExpression1 = ObjectWrap::Unwrap<ObjectExpressionWrapper>(args[0]->ToObject());
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression2 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());

  _TaggedTemplateExpression2->TaggedTemplateExpression->setTag(_ObjectExpression1->ObjectExpression);
}
void TaggedTemplateExpressionWrapper::setTagSequenceExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  SequenceExpressionWrapper* _SequenceExpression1 = ObjectWrap::Unwrap<SequenceExpressionWrapper>(args[0]->ToObject());
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression2 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());

  _TaggedTemplateExpression2->TaggedTemplateExpression->setTag(_SequenceExpression1->SequenceExpression);
}
void TaggedTemplateExpressionWrapper::setTagTaggedTemplateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression1 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args[0]->ToObject());
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression2 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());

  _TaggedTemplateExpression2->TaggedTemplateExpression->setTag(_TaggedTemplateExpression1->TaggedTemplateExpression);
}
void TaggedTemplateExpressionWrapper::setTagTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression2 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());

  _TaggedTemplateExpression2->TaggedTemplateExpression->setTag(_TemplateLiteral1->TemplateLiteral);
}
void TaggedTemplateExpressionWrapper::setTagThisExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  ThisExpressionWrapper* _ThisExpression1 = ObjectWrap::Unwrap<ThisExpressionWrapper>(args[0]->ToObject());
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression2 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());

  _TaggedTemplateExpression2->TaggedTemplateExpression->setTag(_ThisExpression1->ThisExpression);
}
void TaggedTemplateExpressionWrapper::setTagUnaryExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UnaryExpressionWrapper* _UnaryExpression1 = ObjectWrap::Unwrap<UnaryExpressionWrapper>(args[0]->ToObject());
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression2 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());

  _TaggedTemplateExpression2->TaggedTemplateExpression->setTag(_UnaryExpression1->UnaryExpression);
}
void TaggedTemplateExpressionWrapper::setTagUpdateExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  UpdateExpressionWrapper* _UpdateExpression1 = ObjectWrap::Unwrap<UpdateExpressionWrapper>(args[0]->ToObject());
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression2 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());

  _TaggedTemplateExpression2->TaggedTemplateExpression->setTag(_UpdateExpression1->UpdateExpression);
}
void TaggedTemplateExpressionWrapper::setTagYieldExpression(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  YieldExpressionWrapper* _YieldExpression1 = ObjectWrap::Unwrap<YieldExpressionWrapper>(args[0]->ToObject());
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression2 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());

  _TaggedTemplateExpression2->TaggedTemplateExpression->setTag(_YieldExpression1->YieldExpression);
}
void TaggedTemplateExpressionWrapper::setQuasiTemplateLiteral(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  TemplateLiteralWrapper* _TemplateLiteral1 = ObjectWrap::Unwrap<TemplateLiteralWrapper>(args[0]->ToObject());
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression2 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());

  _TaggedTemplateExpression2->TaggedTemplateExpression->setQuasi(_TemplateLiteral1->TemplateLiteral);
}
void TaggedTemplateExpressionWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression2 = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());

  _TaggedTemplateExpression2->TaggedTemplateExpression->addComments(_Comment1->Comment);
}
void TaggedTemplateExpressionWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _TaggedTemplateExpression->TaggedTemplateExpression->getPosition();
  range.setPath( param );
  _TaggedTemplateExpression->TaggedTemplateExpression->setPosition( range );
}

void TaggedTemplateExpressionWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _TaggedTemplateExpression->TaggedTemplateExpression->getPosition();
  range.setLine( ui );
  _TaggedTemplateExpression->TaggedTemplateExpression->setPosition( range );
}

void TaggedTemplateExpressionWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _TaggedTemplateExpression->TaggedTemplateExpression->getPosition();
  range.setCol( ui );
  _TaggedTemplateExpression->TaggedTemplateExpression->setPosition( range );
}

void TaggedTemplateExpressionWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _TaggedTemplateExpression->TaggedTemplateExpression->getPosition();
  range.setEndLine( ui );
  _TaggedTemplateExpression->TaggedTemplateExpression->setPosition( range );
}

void TaggedTemplateExpressionWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _TaggedTemplateExpression->TaggedTemplateExpression->getPosition();
  range.setEndCol( ui );
  _TaggedTemplateExpression->TaggedTemplateExpression->setPosition( range );
}

void TaggedTemplateExpressionWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _TaggedTemplateExpression->TaggedTemplateExpression->getPosition();
  range.setWideLine( ui );
  _TaggedTemplateExpression->TaggedTemplateExpression->setPosition( range );
}

void TaggedTemplateExpressionWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _TaggedTemplateExpression->TaggedTemplateExpression->getPosition();
  range.setWideCol( ui );
  _TaggedTemplateExpression->TaggedTemplateExpression->setPosition( range );
}

void TaggedTemplateExpressionWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _TaggedTemplateExpression->TaggedTemplateExpression->getPosition();
  range.setWideEndLine( ui );
  _TaggedTemplateExpression->TaggedTemplateExpression->setPosition( range );
}

void TaggedTemplateExpressionWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  TaggedTemplateExpressionWrapper* _TaggedTemplateExpression = ObjectWrap::Unwrap<TaggedTemplateExpressionWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _TaggedTemplateExpression->TaggedTemplateExpression->getPosition();
  range.setWideEndCol( ui );
  _TaggedTemplateExpression->TaggedTemplateExpression->setPosition( range );
}

}}}} //end of namespaces