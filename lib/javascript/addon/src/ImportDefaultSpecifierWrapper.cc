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

#include "../inc/ImportDefaultSpecifierWrapper.h"
#include <sstream>  
#include <string>   
#include <iomanip>  
#include <algorithm>
#include <cctype>   

#include <nan.h>   

using namespace v8;

namespace columbus { namespace javascript { namespace asg { namespace addon {

Persistent<Function> ImportDefaultSpecifierWrapper::constructor;

void ImportDefaultSpecifierWrapper::Init(Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();                                
                                                                           
  // Prepare constructor template                                          
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);       
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "ImportDefaultSpecifierWrapper"));             
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                       
  NODE_SET_PROTOTYPE_METHOD(tpl, "setLocalIdentifier", setLocalIdentifier);
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
  exports->Set(v8::String::NewFromUtf8(isolate, "ImportDefaultSpecifierWrapper"),                   
               tpl->GetFunction());                                        
}                                                                          


void ImportDefaultSpecifierWrapper::New(const FunctionCallbackInfo<Value>& args) {                             
  Isolate* isolate = Isolate::GetCurrent();                                         
  HandleScope scope(isolate);                                                       
                                                                                    
  if (args.IsConstructCall()) {                                                     
    // Invoked as constructor: `new ImportDefaultSpecifierWrapper(...)`                                        
    Factory* fact = Nan::ObjectWrap::Unwrap<Factory>(args[0]->ToObject()); 
    ImportDefaultSpecifierWrapper* obj = new ImportDefaultSpecifierWrapper(fact);                                                         
    obj->Wrap(args.This());                                                         
    args.GetReturnValue().Set(args.This());                                         
  } else {                                                                          
    // Invoked as plain function `ImportDefaultSpecifierWrapper(...)`, turn into construct call.               
    const int argc = 1;                                                             
    Handle<v8::Value> argv[argc] = { args[0] };                                         
    Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);              
    args.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked()); 
  }                                                                                 
}                                                                                   


ImportDefaultSpecifierWrapper::ImportDefaultSpecifierWrapper(Factory* fact)                        
{                                                   
  ImportDefaultSpecifier = fact->getFactory()->createImportDefaultSpecifierNode();          
}                                                   

ImportDefaultSpecifierWrapper::~ImportDefaultSpecifierWrapper()
{        
}        

void ImportDefaultSpecifierWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {              
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  const unsigned argc = 1;                                                   
  Handle<Value> argv[argc] = { args[0] };                                    
  Local<v8::Function> cons = Local<v8::Function>::New(isolate, constructor);         
  Local<v8::Object> instance = Nan::NewInstance(cons, argc, argv).ToLocalChecked();  
  args.GetReturnValue().Set(instance);                                       
}                                                                            

void ImportDefaultSpecifierWrapper::setLocalIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  IdentifierWrapper* _Identifier1 = ObjectWrap::Unwrap<IdentifierWrapper>(args[0]->ToObject());
  ImportDefaultSpecifierWrapper* _ImportDefaultSpecifier2 = ObjectWrap::Unwrap<ImportDefaultSpecifierWrapper>(args.This());

  _ImportDefaultSpecifier2->ImportDefaultSpecifier->setLocal(_Identifier1->Identifier);
}
void ImportDefaultSpecifierWrapper::addCommentsComment(const v8::FunctionCallbackInfo<v8::Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);              
  CommentWrapper* _Comment1 = ObjectWrap::Unwrap<CommentWrapper>(args[0]->ToObject());
  ImportDefaultSpecifierWrapper* _ImportDefaultSpecifier2 = ObjectWrap::Unwrap<ImportDefaultSpecifierWrapper>(args.This());

  _ImportDefaultSpecifier2->ImportDefaultSpecifier->addComments(_Comment1->Comment);
}
void ImportDefaultSpecifierWrapper::setPath(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  ImportDefaultSpecifierWrapper* _ImportDefaultSpecifier = ObjectWrap::Unwrap<ImportDefaultSpecifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );
  std::string param(*utfStr);
  Range range = _ImportDefaultSpecifier->ImportDefaultSpecifier->getPosition();
  range.setPath( param );
  _ImportDefaultSpecifier->ImportDefaultSpecifier->setPosition( range );
}

void ImportDefaultSpecifierWrapper::setLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ImportDefaultSpecifierWrapper* _ImportDefaultSpecifier = ObjectWrap::Unwrap<ImportDefaultSpecifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ImportDefaultSpecifier->ImportDefaultSpecifier->getPosition();
  range.setLine( ui );
  _ImportDefaultSpecifier->ImportDefaultSpecifier->setPosition( range );
}

void ImportDefaultSpecifierWrapper::setCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ImportDefaultSpecifierWrapper* _ImportDefaultSpecifier = ObjectWrap::Unwrap<ImportDefaultSpecifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ImportDefaultSpecifier->ImportDefaultSpecifier->getPosition();
  range.setCol( ui );
  _ImportDefaultSpecifier->ImportDefaultSpecifier->setPosition( range );
}

void ImportDefaultSpecifierWrapper::setEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ImportDefaultSpecifierWrapper* _ImportDefaultSpecifier = ObjectWrap::Unwrap<ImportDefaultSpecifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ImportDefaultSpecifier->ImportDefaultSpecifier->getPosition();
  range.setEndLine( ui );
  _ImportDefaultSpecifier->ImportDefaultSpecifier->setPosition( range );
}

void ImportDefaultSpecifierWrapper::setEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ImportDefaultSpecifierWrapper* _ImportDefaultSpecifier = ObjectWrap::Unwrap<ImportDefaultSpecifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ImportDefaultSpecifier->ImportDefaultSpecifier->getPosition();
  range.setEndCol( ui );
  _ImportDefaultSpecifier->ImportDefaultSpecifier->setPosition( range );
}

void ImportDefaultSpecifierWrapper::setWideLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ImportDefaultSpecifierWrapper* _ImportDefaultSpecifier = ObjectWrap::Unwrap<ImportDefaultSpecifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ImportDefaultSpecifier->ImportDefaultSpecifier->getPosition();
  range.setWideLine( ui );
  _ImportDefaultSpecifier->ImportDefaultSpecifier->setPosition( range );
}

void ImportDefaultSpecifierWrapper::setWideCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ImportDefaultSpecifierWrapper* _ImportDefaultSpecifier = ObjectWrap::Unwrap<ImportDefaultSpecifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ImportDefaultSpecifier->ImportDefaultSpecifier->getPosition();
  range.setWideCol( ui );
  _ImportDefaultSpecifier->ImportDefaultSpecifier->setPosition( range );
}

void ImportDefaultSpecifierWrapper::setWideEndLine(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ImportDefaultSpecifierWrapper* _ImportDefaultSpecifier = ObjectWrap::Unwrap<ImportDefaultSpecifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ImportDefaultSpecifier->ImportDefaultSpecifier->getPosition();
  range.setWideEndLine( ui );
  _ImportDefaultSpecifier->ImportDefaultSpecifier->setPosition( range );
}

void ImportDefaultSpecifierWrapper::setWideEndCol(const FunctionCallbackInfo<Value>& args){ 
  Isolate* isolate = Isolate::GetCurrent();                                  
  HandleScope scope(isolate);                                                
                                                                             
  ImportDefaultSpecifierWrapper* _ImportDefaultSpecifier = ObjectWrap::Unwrap<ImportDefaultSpecifierWrapper>(args.This());
  v8::String::Utf8Value utfStr( args[0]->ToString() );                       
  std::string param(*utfStr);                                                
  std::istringstream is(param);
  unsigned int ui;
  is >> ui;
  Range range = _ImportDefaultSpecifier->ImportDefaultSpecifier->getPosition();
  range.setWideEndCol( ui );
  _ImportDefaultSpecifier->ImportDefaultSpecifier->setPosition( range );
}

}}}} //end of namespaces