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
#include <node_api.h>


#include "inc/SystemWrapper.h"
#include "inc/CommentWrapper.h"
#include "inc/ModuleDeclarationWrapper.h"
#include "inc/VariableDeclaratorWrapper.h"
#include "inc/ChainElementWrapper.h"
#include "inc/PrivateIdentifierWrapper.h"
#include "inc/PropertyWrapper.h"
#include "inc/SpreadElementWrapper.h"
#include "inc/SuperWrapper.h"
#include "inc/TemplateElementWrapper.h"
#include "inc/CatchClauseWrapper.h"
#include "inc/FunctionWrapper.h"
#include "inc/SwitchCaseWrapper.h"
#include "inc/ClassBodyWrapper.h"
#include "inc/MethodDefinitionWrapper.h"
#include "inc/PropertyDefinitionWrapper.h"
#include "inc/ProgramWrapper.h"
#include "inc/IdentifierWrapper.h"
#include "inc/ExportNamedDeclarationWrapper.h"
#include "inc/ImportDeclarationWrapper.h"
#include "inc/CallExpressionWrapper.h"
#include "inc/MemberExpressionWrapper.h"
#include "inc/ArrayExpressionWrapper.h"
#include "inc/ArrowFunctionExpressionWrapper.h"
#include "inc/AssignmentExpressionWrapper.h"
#include "inc/AwaitExpressionWrapper.h"
#include "inc/BinaryExpressionWrapper.h"
#include "inc/ChainExpressionWrapper.h"
#include "inc/ClassExpressionWrapper.h"
#include "inc/ConditionalExpressionWrapper.h"
#include "inc/FunctionExpressionWrapper.h"
#include "inc/ImportExpressionWrapper.h"
#include "inc/LogicalExpressionWrapper.h"
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
#include "inc/BigIntLiteralWrapper.h"
#include "inc/BooleanLiteralWrapper.h"
#include "inc/NullLiteralWrapper.h"
#include "inc/NumberLiteralWrapper.h"
#include "inc/RegExpLiteralWrapper.h"
#include "inc/StringLiteralWrapper.h"
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
#define DECLARE_NAPI_METHOD(name, func) \
  { name, 0, func, 0, 0, 0, napi_default, 0 } 


namespace columbus { namespace javascript { namespace asg { namespace addon { 
class Factory {
  public:
    static napi_value Init(napi_env env, napi_value& exports);
    static void Destructor(napi_env env, void* nativeObject, void* finalize_hint);

  private:
    explicit Factory();
    ~Factory();

    static napi_value New(napi_env env, napi_callback_info info);
    static napi_value SaveAST(napi_env env, napi_callback_info info);
    static napi_value LoadAST(napi_env env, napi_callback_info info);
    static napi_value Clear(napi_env env, napi_callback_info info);
    static napi_value getRoot(napi_env env, napi_callback_info info);   
    static napi_value createCommentWrapper(napi_env env, napi_callback_info info);
    static napi_value createModuleDeclarationWrapper(napi_env env, napi_callback_info info);
    static napi_value createVariableDeclaratorWrapper(napi_env env, napi_callback_info info);
    static napi_value createChainElementWrapper(napi_env env, napi_callback_info info);
    static napi_value createPrivateIdentifierWrapper(napi_env env, napi_callback_info info);
    static napi_value createPropertyWrapper(napi_env env, napi_callback_info info);
    static napi_value createSpreadElementWrapper(napi_env env, napi_callback_info info);
    static napi_value createSuperWrapper(napi_env env, napi_callback_info info);
    static napi_value createTemplateElementWrapper(napi_env env, napi_callback_info info);
    static napi_value createCatchClauseWrapper(napi_env env, napi_callback_info info);
    static napi_value createFunctionWrapper(napi_env env, napi_callback_info info);
    static napi_value createSwitchCaseWrapper(napi_env env, napi_callback_info info);
    static napi_value createClassBodyWrapper(napi_env env, napi_callback_info info);
    static napi_value createMethodDefinitionWrapper(napi_env env, napi_callback_info info);
    static napi_value createPropertyDefinitionWrapper(napi_env env, napi_callback_info info);
    static napi_value createProgramWrapper(napi_env env, napi_callback_info info);
    static napi_value createIdentifierWrapper(napi_env env, napi_callback_info info);
    static napi_value createExportNamedDeclarationWrapper(napi_env env, napi_callback_info info);
    static napi_value createImportDeclarationWrapper(napi_env env, napi_callback_info info);
    static napi_value createCallExpressionWrapper(napi_env env, napi_callback_info info);
    static napi_value createMemberExpressionWrapper(napi_env env, napi_callback_info info);
    static napi_value createArrayExpressionWrapper(napi_env env, napi_callback_info info);
    static napi_value createArrowFunctionExpressionWrapper(napi_env env, napi_callback_info info);
    static napi_value createAssignmentExpressionWrapper(napi_env env, napi_callback_info info);
    static napi_value createAwaitExpressionWrapper(napi_env env, napi_callback_info info);
    static napi_value createBinaryExpressionWrapper(napi_env env, napi_callback_info info);
    static napi_value createChainExpressionWrapper(napi_env env, napi_callback_info info);
    static napi_value createClassExpressionWrapper(napi_env env, napi_callback_info info);
    static napi_value createConditionalExpressionWrapper(napi_env env, napi_callback_info info);
    static napi_value createFunctionExpressionWrapper(napi_env env, napi_callback_info info);
    static napi_value createImportExpressionWrapper(napi_env env, napi_callback_info info);
    static napi_value createLogicalExpressionWrapper(napi_env env, napi_callback_info info);
    static napi_value createMetaPropertyWrapper(napi_env env, napi_callback_info info);
    static napi_value createNewExpressionWrapper(napi_env env, napi_callback_info info);
    static napi_value createObjectExpressionWrapper(napi_env env, napi_callback_info info);
    static napi_value createSequenceExpressionWrapper(napi_env env, napi_callback_info info);
    static napi_value createTaggedTemplateExpressionWrapper(napi_env env, napi_callback_info info);
    static napi_value createTemplateLiteralWrapper(napi_env env, napi_callback_info info);
    static napi_value createThisExpressionWrapper(napi_env env, napi_callback_info info);
    static napi_value createUnaryExpressionWrapper(napi_env env, napi_callback_info info);
    static napi_value createUpdateExpressionWrapper(napi_env env, napi_callback_info info);
    static napi_value createYieldExpressionWrapper(napi_env env, napi_callback_info info);
    static napi_value createBigIntLiteralWrapper(napi_env env, napi_callback_info info);
    static napi_value createBooleanLiteralWrapper(napi_env env, napi_callback_info info);
    static napi_value createNullLiteralWrapper(napi_env env, napi_callback_info info);
    static napi_value createNumberLiteralWrapper(napi_env env, napi_callback_info info);
    static napi_value createRegExpLiteralWrapper(napi_env env, napi_callback_info info);
    static napi_value createStringLiteralWrapper(napi_env env, napi_callback_info info);
    static napi_value createArrayPatternWrapper(napi_env env, napi_callback_info info);
    static napi_value createAssignmentPatternWrapper(napi_env env, napi_callback_info info);
    static napi_value createObjectPatternWrapper(napi_env env, napi_callback_info info);
    static napi_value createRestElementWrapper(napi_env env, napi_callback_info info);
    static napi_value createBlockStatementWrapper(napi_env env, napi_callback_info info);
    static napi_value createBreakStatementWrapper(napi_env env, napi_callback_info info);
    static napi_value createContinueStatementWrapper(napi_env env, napi_callback_info info);
    static napi_value createDebuggerStatementWrapper(napi_env env, napi_callback_info info);
    static napi_value createEmptyStatementWrapper(napi_env env, napi_callback_info info);
    static napi_value createExpressionStatementWrapper(napi_env env, napi_callback_info info);
    static napi_value createForInStatementWrapper(napi_env env, napi_callback_info info);
    static napi_value createForStatementWrapper(napi_env env, napi_callback_info info);
    static napi_value createIfStatementWrapper(napi_env env, napi_callback_info info);
    static napi_value createLabeledStatementWrapper(napi_env env, napi_callback_info info);
    static napi_value createReturnStatementWrapper(napi_env env, napi_callback_info info);
    static napi_value createSwitchStatementWrapper(napi_env env, napi_callback_info info);
    static napi_value createThrowStatementWrapper(napi_env env, napi_callback_info info);
    static napi_value createTryStatementWrapper(napi_env env, napi_callback_info info);
    static napi_value createWhileStatementWrapper(napi_env env, napi_callback_info info);
    static napi_value createWithStatementWrapper(napi_env env, napi_callback_info info);
    static napi_value createClassDeclarationWrapper(napi_env env, napi_callback_info info);
    static napi_value createExportSpecifierWrapper(napi_env env, napi_callback_info info);
    static napi_value createFunctionDeclarationWrapper(napi_env env, napi_callback_info info);
    static napi_value createExportAllDeclarationWrapper(napi_env env, napi_callback_info info);
    static napi_value createExportDefaultDeclarationWrapper(napi_env env, napi_callback_info info);
    static napi_value createVariableDeclarationWrapper(napi_env env, napi_callback_info info);
    static napi_value createForOfStatementWrapper(napi_env env, napi_callback_info info);
    static napi_value createDoWhileStatementWrapper(napi_env env, napi_callback_info info);
    static napi_value createImportDefaultSpecifierWrapper(napi_env env, napi_callback_info info);
    static napi_value createImportNamespaceSpecifierWrapper(napi_env env, napi_callback_info info);
    static napi_value createImportSpecifierWrapper(napi_env env, napi_callback_info info);
    static napi_ref constructor;
    napi_env env_;
    napi_ref wrapper_;

    columbus::RefDistributorStrTable* strTable;
    columbus::javascript::asg::Factory* factory;
}; // Factory
}}}}//end of namespaces
#endif