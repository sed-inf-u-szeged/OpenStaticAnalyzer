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

#ifndef _JAVASCRIPT_ADDON_FACTORY_H_
#define _JAVASCRIPT_ADDON_FACTORY_H_

#include "javascript/inc/javascript.h"
#include <nan.h>
#include "inc/SystemWrapper.h"
#include "inc/CommentWrapper.h"
#include "inc/ModuleDeclarationWrapper.h"
#include "inc/VariableDeclaratorWrapper.h"
#include "inc/PropertyWrapper.h"
#include "inc/SpreadElementWrapper.h"
#include "inc/SuperWrapper.h"
#include "inc/TemplateElementWrapper.h"
#include "inc/CatchClauseWrapper.h"
#include "inc/FunctionWrapper.h"
#include "inc/SwitchCaseWrapper.h"
#include "inc/ClassBodyWrapper.h"
#include "inc/MethodDefinitionWrapper.h"
#include "inc/ProgramWrapper.h"
#include "inc/IdentifierWrapper.h"
#include "inc/ExportNamedDeclarationWrapper.h"
#include "inc/ImportDeclarationWrapper.h"
#include "inc/ArrayExpressionWrapper.h"
#include "inc/ArrowFunctionExpressionWrapper.h"
#include "inc/AssignmentExpressionWrapper.h"
#include "inc/AwaitExpressionWrapper.h"
#include "inc/BinaryExpressionWrapper.h"
#include "inc/CallExpressionWrapper.h"
#include "inc/ClassExpressionWrapper.h"
#include "inc/ConditionalExpressionWrapper.h"
#include "inc/FunctionExpressionWrapper.h"
#include "inc/LogicalExpressionWrapper.h"
#include "inc/MemberExpressionWrapper.h"
#include "inc/MetaPropertyWrapper.h"
#include "inc/NewExpressionWrapper.h"
#include "inc/ObjectExpressionWrapper.h"
#include "inc/SequenceExpressionWrapper.h"
#include "inc/TaggedTemplateExpressionWrapper.h"
#include "inc/TemplateLiteralWrapper.h"
#include "inc/ThisExpressionWrapper.h"
#include "inc/UnaryExpressionWrapper.h"
#include "inc/UpdateExpressionWrapper.h"
#include "inc/YieldExpressionWrapper.h"
#include "inc/BooleanLiteralWrapper.h"
#include "inc/NullLiteralWrapper.h"
#include "inc/NumberLiteralWrapper.h"
#include "inc/RegExpLiteralWrapper.h"
#include "inc/StringLiteralWrapper.h"
#include "inc/AssignmentPropertyWrapper.h"
#include "inc/ArrayPatternWrapper.h"
#include "inc/AssignmentPatternWrapper.h"
#include "inc/ObjectPatternWrapper.h"
#include "inc/RestElementWrapper.h"
#include "inc/BlockStatementWrapper.h"
#include "inc/BreakStatementWrapper.h"
#include "inc/ContinueStatementWrapper.h"
#include "inc/DebuggerStatementWrapper.h"
#include "inc/EmptyStatementWrapper.h"
#include "inc/ExpressionStatementWrapper.h"
#include "inc/ForInStatementWrapper.h"
#include "inc/ForStatementWrapper.h"
#include "inc/IfStatementWrapper.h"
#include "inc/LabeledStatementWrapper.h"
#include "inc/ReturnStatementWrapper.h"
#include "inc/SwitchStatementWrapper.h"
#include "inc/ThrowStatementWrapper.h"
#include "inc/TryStatementWrapper.h"
#include "inc/WhileStatementWrapper.h"
#include "inc/WithStatementWrapper.h"
#include "inc/ClassDeclarationWrapper.h"
#include "inc/ExportSpecifierWrapper.h"
#include "inc/FunctionDeclarationWrapper.h"
#include "inc/ExportAllDeclarationWrapper.h"
#include "inc/ExportDefaultDeclarationWrapper.h"
#include "inc/VariableDeclarationWrapper.h"
#include "inc/ForOfStatementWrapper.h"
#include "inc/DoWhileStatementWrapper.h"
#include "inc/ImportDefaultSpecifierWrapper.h"
#include "inc/ImportNamespaceSpecifierWrapper.h"
#include "inc/ImportSpecifierWrapper.h"
namespace columbus { namespace javascript { namespace asg { namespace addon { 
class Factory : public Nan::ObjectWrap {                                                 
  public:                                                                                
    static void Init(v8::Local<v8::Object> exports);                                     
                                                                                         
                                                                                         
    static void getRoot(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createCommentWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createModuleDeclarationWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createVariableDeclaratorWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createPropertyWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createSpreadElementWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createSuperWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createTemplateElementWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createCatchClauseWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createFunctionWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createSwitchCaseWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createClassBodyWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createMethodDefinitionWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createProgramWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createIdentifierWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createExportNamedDeclarationWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createImportDeclarationWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createArrayExpressionWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createArrowFunctionExpressionWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createAssignmentExpressionWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createAwaitExpressionWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createBinaryExpressionWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createCallExpressionWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createClassExpressionWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createConditionalExpressionWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createFunctionExpressionWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createLogicalExpressionWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createMemberExpressionWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createMetaPropertyWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createNewExpressionWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createObjectExpressionWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createSequenceExpressionWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createTaggedTemplateExpressionWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createTemplateLiteralWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createThisExpressionWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createUnaryExpressionWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createUpdateExpressionWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createYieldExpressionWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createBooleanLiteralWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createNullLiteralWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createNumberLiteralWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createRegExpLiteralWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createStringLiteralWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createAssignmentPropertyWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createArrayPatternWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createAssignmentPatternWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createObjectPatternWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createRestElementWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createBlockStatementWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createBreakStatementWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createContinueStatementWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createDebuggerStatementWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createEmptyStatementWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createExpressionStatementWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createForInStatementWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createForStatementWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createIfStatementWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createLabeledStatementWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createReturnStatementWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createSwitchStatementWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createThrowStatementWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createTryStatementWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createWhileStatementWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createWithStatementWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createClassDeclarationWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createExportSpecifierWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createFunctionDeclarationWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createExportAllDeclarationWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createExportDefaultDeclarationWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createVariableDeclarationWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createForOfStatementWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createDoWhileStatementWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createImportDefaultSpecifierWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createImportNamespaceSpecifierWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    static void createImportSpecifierWrapper(const v8::FunctionCallbackInfo<v8::Value>& args);   
    columbus::javascript::asg::Factory* getFactory(){ return factory; }                          
                                                                                         
  private:                                                                               
    explicit Factory();                                                                  
    virtual ~Factory();                                                                  
    static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);                   
    static Nan::Persistent<v8::Function> constructor;                                    
    static columbus::RefDistributorStrTable* strTable;                                   
    static columbus::javascript::asg::Factory* factory;                                  
    static void SaveAST(const Nan::FunctionCallbackInfo<v8::Value>& info);               
}; // Factory                                                                            
}}}}//end of namespaces
#endif