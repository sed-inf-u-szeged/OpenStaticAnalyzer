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

#include "Factory.h"                                                                               
#include "javascript/inc/javascript.h"                                                                                    
#include "javascript/inc/messages.h"                                                                              
                                                                                                            
                                                                                                            
namespace columbus { namespace javascript { namespace asg { namespace addon {                                       
                                                                                                            
columbus::RefDistributorStrTable* Factory::strTable = new columbus::RefDistributorStrTable();               
columbus::javascript::asg::Factory* Factory::factory = new columbus::javascript::asg::Factory(*strTable);   
                                                                                                            
Nan::Persistent<v8::Function> Factory::constructor;                                                             
                                                                                                            
Factory::Factory()                                                                                          
{                                                                                                           
}                                                                                                           
                                                                                                            
Factory::~Factory() {                                                                                       
                                                                                                            
}                                                                                                           
void Factory::Init(v8::Local<v8::Object> exports) {                                                         
  Nan::HandleScope scope;                                                    
                                                                             
  // Prepare constructor template                                            
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New); 
  tpl->SetClassName(Nan::New("Factory").ToLocalChecked());                 
  tpl->InstanceTemplate()->SetInternalFieldCount(1);                         
                                                                             
  Nan::SetPrototypeMethod(tpl, "saveAST", SaveAST);                        
  NODE_SET_PROTOTYPE_METHOD(tpl, "getRoot", getRoot);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createCommentWrapper", createCommentWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createModuleDeclarationWrapper", createModuleDeclarationWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createVariableDeclaratorWrapper", createVariableDeclaratorWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createPropertyWrapper", createPropertyWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createSpreadElementWrapper", createSpreadElementWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createSuperWrapper", createSuperWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createTemplateElementWrapper", createTemplateElementWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createCatchClauseWrapper", createCatchClauseWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createFunctionWrapper", createFunctionWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createSwitchCaseWrapper", createSwitchCaseWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createClassBodyWrapper", createClassBodyWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createMethodDefinitionWrapper", createMethodDefinitionWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createProgramWrapper", createProgramWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createIdentifierWrapper", createIdentifierWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createExportNamedDeclarationWrapper", createExportNamedDeclarationWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createImportDeclarationWrapper", createImportDeclarationWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createArrayExpressionWrapper", createArrayExpressionWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createArrowFunctionExpressionWrapper", createArrowFunctionExpressionWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createAssignmentExpressionWrapper", createAssignmentExpressionWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createAwaitExpressionWrapper", createAwaitExpressionWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createBinaryExpressionWrapper", createBinaryExpressionWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createCallExpressionWrapper", createCallExpressionWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createClassExpressionWrapper", createClassExpressionWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createConditionalExpressionWrapper", createConditionalExpressionWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createFunctionExpressionWrapper", createFunctionExpressionWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createLogicalExpressionWrapper", createLogicalExpressionWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createMemberExpressionWrapper", createMemberExpressionWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createMetaPropertyWrapper", createMetaPropertyWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createNewExpressionWrapper", createNewExpressionWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createObjectExpressionWrapper", createObjectExpressionWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createSequenceExpressionWrapper", createSequenceExpressionWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createTaggedTemplateExpressionWrapper", createTaggedTemplateExpressionWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createTemplateLiteralWrapper", createTemplateLiteralWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createThisExpressionWrapper", createThisExpressionWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createUnaryExpressionWrapper", createUnaryExpressionWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createUpdateExpressionWrapper", createUpdateExpressionWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createYieldExpressionWrapper", createYieldExpressionWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createBooleanLiteralWrapper", createBooleanLiteralWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createNullLiteralWrapper", createNullLiteralWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createNumberLiteralWrapper", createNumberLiteralWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createRegExpLiteralWrapper", createRegExpLiteralWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createStringLiteralWrapper", createStringLiteralWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createAssignmentPropertyWrapper", createAssignmentPropertyWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createArrayPatternWrapper", createArrayPatternWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createAssignmentPatternWrapper", createAssignmentPatternWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createObjectPatternWrapper", createObjectPatternWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createRestElementWrapper", createRestElementWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createBlockStatementWrapper", createBlockStatementWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createBreakStatementWrapper", createBreakStatementWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createContinueStatementWrapper", createContinueStatementWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createDebuggerStatementWrapper", createDebuggerStatementWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createEmptyStatementWrapper", createEmptyStatementWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createExpressionStatementWrapper", createExpressionStatementWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createForInStatementWrapper", createForInStatementWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createForStatementWrapper", createForStatementWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createIfStatementWrapper", createIfStatementWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createLabeledStatementWrapper", createLabeledStatementWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createReturnStatementWrapper", createReturnStatementWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createSwitchStatementWrapper", createSwitchStatementWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createThrowStatementWrapper", createThrowStatementWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createTryStatementWrapper", createTryStatementWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createWhileStatementWrapper", createWhileStatementWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createWithStatementWrapper", createWithStatementWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createClassDeclarationWrapper", createClassDeclarationWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createExportSpecifierWrapper", createExportSpecifierWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createFunctionDeclarationWrapper", createFunctionDeclarationWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createExportAllDeclarationWrapper", createExportAllDeclarationWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createExportDefaultDeclarationWrapper", createExportDefaultDeclarationWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createVariableDeclarationWrapper", createVariableDeclarationWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createForOfStatementWrapper", createForOfStatementWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createDoWhileStatementWrapper", createDoWhileStatementWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createImportDefaultSpecifierWrapper", createImportDefaultSpecifierWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createImportNamespaceSpecifierWrapper", createImportNamespaceSpecifierWrapper);
  NODE_SET_PROTOTYPE_METHOD(tpl, "createImportSpecifierWrapper", createImportSpecifierWrapper);
  constructor.Reset(tpl->GetFunction());                                     
  exports->Set(Nan::New("Factory").ToLocalChecked(), tpl->GetFunction());
}                                                                                                           
                                                                                                            
                                                                                                            
void Factory::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {                                         
  if (info.IsConstructCall()) {                                             
  	// Invoked as constructor: `new MyObject(...)`                          
  	Factory* obj = new Factory();                                           
  	obj->Wrap(info.This());                                                 
  	info.GetReturnValue().Set(info.This());                                 
  }                                                                         
  else {                                                                    
  	// Invoked as plain function `MyObject(...)`, turn into construct call. 
  	v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);     
  	info.GetReturnValue().Set(Nan::NewInstance(cons, 0, NULL).ToLocalChecked() );  
  }                                                                         
}                                                                                                           
                                                                                                            
                                                                                                            
                                                                                                            
void Factory::getRoot(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  SystemWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createCommentWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  CommentWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createModuleDeclarationWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  ModuleDeclarationWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createVariableDeclaratorWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  VariableDeclaratorWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createPropertyWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  PropertyWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createSpreadElementWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  SpreadElementWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createSuperWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  SuperWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createTemplateElementWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  TemplateElementWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createCatchClauseWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  CatchClauseWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createFunctionWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  FunctionWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createSwitchCaseWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  SwitchCaseWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createClassBodyWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  ClassBodyWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createMethodDefinitionWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  MethodDefinitionWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createProgramWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  ProgramWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createIdentifierWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  IdentifierWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createExportNamedDeclarationWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  ExportNamedDeclarationWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createImportDeclarationWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  ImportDeclarationWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createArrayExpressionWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  ArrayExpressionWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createArrowFunctionExpressionWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  ArrowFunctionExpressionWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createAssignmentExpressionWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  AssignmentExpressionWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createAwaitExpressionWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  AwaitExpressionWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createBinaryExpressionWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  BinaryExpressionWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createCallExpressionWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  CallExpressionWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createClassExpressionWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  ClassExpressionWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createConditionalExpressionWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  ConditionalExpressionWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createFunctionExpressionWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  FunctionExpressionWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createLogicalExpressionWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  LogicalExpressionWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createMemberExpressionWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  MemberExpressionWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createMetaPropertyWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  MetaPropertyWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createNewExpressionWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  NewExpressionWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createObjectExpressionWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  ObjectExpressionWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createSequenceExpressionWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  SequenceExpressionWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createTaggedTemplateExpressionWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  TaggedTemplateExpressionWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createTemplateLiteralWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  TemplateLiteralWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createThisExpressionWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  ThisExpressionWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createUnaryExpressionWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  UnaryExpressionWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createUpdateExpressionWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  UpdateExpressionWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createYieldExpressionWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  YieldExpressionWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createBooleanLiteralWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  BooleanLiteralWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createNullLiteralWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  NullLiteralWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createNumberLiteralWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  NumberLiteralWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createRegExpLiteralWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  RegExpLiteralWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createStringLiteralWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  StringLiteralWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createAssignmentPropertyWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  AssignmentPropertyWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createArrayPatternWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  ArrayPatternWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createAssignmentPatternWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  AssignmentPatternWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createObjectPatternWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  ObjectPatternWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createRestElementWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  RestElementWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createBlockStatementWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  BlockStatementWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createBreakStatementWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  BreakStatementWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createContinueStatementWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  ContinueStatementWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createDebuggerStatementWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  DebuggerStatementWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createEmptyStatementWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  EmptyStatementWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createExpressionStatementWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  ExpressionStatementWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createForInStatementWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  ForInStatementWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createForStatementWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  ForStatementWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createIfStatementWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  IfStatementWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createLabeledStatementWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  LabeledStatementWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createReturnStatementWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  ReturnStatementWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createSwitchStatementWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  SwitchStatementWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createThrowStatementWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  ThrowStatementWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createTryStatementWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  TryStatementWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createWhileStatementWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  WhileStatementWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createWithStatementWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  WithStatementWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createClassDeclarationWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  ClassDeclarationWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createExportSpecifierWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  ExportSpecifierWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createFunctionDeclarationWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  FunctionDeclarationWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createExportAllDeclarationWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  ExportAllDeclarationWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createExportDefaultDeclarationWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  ExportDefaultDeclarationWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createVariableDeclarationWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  VariableDeclarationWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createForOfStatementWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  ForOfStatementWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createDoWhileStatementWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  DoWhileStatementWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createImportDefaultSpecifierWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  ImportDefaultSpecifierWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createImportNamespaceSpecifierWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  ImportNamespaceSpecifierWrapper::NewInstance(args);                                                
}                                                                              
void Factory::createImportSpecifierWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();                                    
  HandleScope scope(isolate);                                                  
                                                                               
  ImportSpecifierWrapper::NewInstance(args);                                                
}                                                                              
                                                                                                            
inline bool ends_with(std::string const & value, std::string const & ending)
{                                                                           
    if (ending.size() > value.size()) return false;                         
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());      
}                                                                           
void Factory::SaveAST(const Nan::FunctionCallbackInfo<v8::Value>& info) {                                   
  std::string filename = info[0]->IsUndefined() ? "out" : std::string(*v8::String::Utf8Value(info[0]));   
  bool createJSML = info[0]->IsUndefined()? false : info[1]->BooleanValue();
                                                                                                            
                                                                                                            
  std::list<HeaderData*> headerList;                                                                        
  columbus::PropertyData header;                                                                            
  headerList.push_back(&header);                                                                            
                                                                                                            
  factory->save( filename, headerList);                                                                     
                                                                                                            
  if(createJSML){
    if(ends_with(filename, ".jssi")){                                                                       
      filename = filename.substr(0,filename.size()- 5);                                                       
    }                                                                                                         
    std::string jsmlFile = filename + ".jsml";                                                              
    common::WriteMsg::write(CMSG_STAGE_JSML_DUMP);                                                            
    std::ofstream ofs(jsmlFile.c_str());                                                                      
    if (!ofs.is_open()) {                                                                                     
      common::WriteMsg::write(CMSG_CANNOT_OPEN_FILE, jsmlFile.c_str());                                       
    } else {                                                                                                  
      javascript::asg::VisitorJAVASCRIPTML visitor(ofs, "", NULL);                                          
      javascript::asg::AlgorithmPreorder().run(*factory, visitor);                                            
      ofs.close();                                                                                            
      common::WriteMsg::write(CMSG_STAGE_DONE);                                                               
    }                                                                                                         
  }
}                                                                                                           
                                                                                                            
                                                                                                            
}}}}                                                                                                        
