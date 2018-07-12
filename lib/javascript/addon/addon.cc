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

#include <nan.h>                           
#include "Factory.h"         
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
                                           
                                           
                                           
void InitAll(v8::Local<v8::Object> exports) {     
  columbus::javascript::asg::addon::Factory::Init(exports);           
  columbus::javascript::asg::addon::SystemWrapper::Init(exports);           
  columbus::javascript::asg::addon::CommentWrapper::Init(exports);           
  columbus::javascript::asg::addon::ModuleDeclarationWrapper::Init(exports);           
  columbus::javascript::asg::addon::VariableDeclaratorWrapper::Init(exports);           
  columbus::javascript::asg::addon::PropertyWrapper::Init(exports);           
  columbus::javascript::asg::addon::SpreadElementWrapper::Init(exports);           
  columbus::javascript::asg::addon::SuperWrapper::Init(exports);           
  columbus::javascript::asg::addon::TemplateElementWrapper::Init(exports);           
  columbus::javascript::asg::addon::CatchClauseWrapper::Init(exports);           
  columbus::javascript::asg::addon::FunctionWrapper::Init(exports);           
  columbus::javascript::asg::addon::SwitchCaseWrapper::Init(exports);           
  columbus::javascript::asg::addon::ClassBodyWrapper::Init(exports);           
  columbus::javascript::asg::addon::MethodDefinitionWrapper::Init(exports);           
  columbus::javascript::asg::addon::ProgramWrapper::Init(exports);           
  columbus::javascript::asg::addon::IdentifierWrapper::Init(exports);           
  columbus::javascript::asg::addon::ExportNamedDeclarationWrapper::Init(exports);           
  columbus::javascript::asg::addon::ImportDeclarationWrapper::Init(exports);           
  columbus::javascript::asg::addon::ArrayExpressionWrapper::Init(exports);           
  columbus::javascript::asg::addon::ArrowFunctionExpressionWrapper::Init(exports);           
  columbus::javascript::asg::addon::AssignmentExpressionWrapper::Init(exports);           
  columbus::javascript::asg::addon::AwaitExpressionWrapper::Init(exports);           
  columbus::javascript::asg::addon::BinaryExpressionWrapper::Init(exports);           
  columbus::javascript::asg::addon::CallExpressionWrapper::Init(exports);           
  columbus::javascript::asg::addon::ClassExpressionWrapper::Init(exports);           
  columbus::javascript::asg::addon::ConditionalExpressionWrapper::Init(exports);           
  columbus::javascript::asg::addon::FunctionExpressionWrapper::Init(exports);           
  columbus::javascript::asg::addon::LogicalExpressionWrapper::Init(exports);           
  columbus::javascript::asg::addon::MemberExpressionWrapper::Init(exports);           
  columbus::javascript::asg::addon::MetaPropertyWrapper::Init(exports);           
  columbus::javascript::asg::addon::NewExpressionWrapper::Init(exports);           
  columbus::javascript::asg::addon::ObjectExpressionWrapper::Init(exports);           
  columbus::javascript::asg::addon::SequenceExpressionWrapper::Init(exports);           
  columbus::javascript::asg::addon::TaggedTemplateExpressionWrapper::Init(exports);           
  columbus::javascript::asg::addon::TemplateLiteralWrapper::Init(exports);           
  columbus::javascript::asg::addon::ThisExpressionWrapper::Init(exports);           
  columbus::javascript::asg::addon::UnaryExpressionWrapper::Init(exports);           
  columbus::javascript::asg::addon::UpdateExpressionWrapper::Init(exports);           
  columbus::javascript::asg::addon::YieldExpressionWrapper::Init(exports);           
  columbus::javascript::asg::addon::BooleanLiteralWrapper::Init(exports);           
  columbus::javascript::asg::addon::NullLiteralWrapper::Init(exports);           
  columbus::javascript::asg::addon::NumberLiteralWrapper::Init(exports);           
  columbus::javascript::asg::addon::RegExpLiteralWrapper::Init(exports);           
  columbus::javascript::asg::addon::StringLiteralWrapper::Init(exports);           
  columbus::javascript::asg::addon::AssignmentPropertyWrapper::Init(exports);           
  columbus::javascript::asg::addon::ArrayPatternWrapper::Init(exports);           
  columbus::javascript::asg::addon::AssignmentPatternWrapper::Init(exports);           
  columbus::javascript::asg::addon::ObjectPatternWrapper::Init(exports);           
  columbus::javascript::asg::addon::RestElementWrapper::Init(exports);           
  columbus::javascript::asg::addon::BlockStatementWrapper::Init(exports);           
  columbus::javascript::asg::addon::BreakStatementWrapper::Init(exports);           
  columbus::javascript::asg::addon::ContinueStatementWrapper::Init(exports);           
  columbus::javascript::asg::addon::DebuggerStatementWrapper::Init(exports);           
  columbus::javascript::asg::addon::EmptyStatementWrapper::Init(exports);           
  columbus::javascript::asg::addon::ExpressionStatementWrapper::Init(exports);           
  columbus::javascript::asg::addon::ForInStatementWrapper::Init(exports);           
  columbus::javascript::asg::addon::ForStatementWrapper::Init(exports);           
  columbus::javascript::asg::addon::IfStatementWrapper::Init(exports);           
  columbus::javascript::asg::addon::LabeledStatementWrapper::Init(exports);           
  columbus::javascript::asg::addon::ReturnStatementWrapper::Init(exports);           
  columbus::javascript::asg::addon::SwitchStatementWrapper::Init(exports);           
  columbus::javascript::asg::addon::ThrowStatementWrapper::Init(exports);           
  columbus::javascript::asg::addon::TryStatementWrapper::Init(exports);           
  columbus::javascript::asg::addon::WhileStatementWrapper::Init(exports);           
  columbus::javascript::asg::addon::WithStatementWrapper::Init(exports);           
  columbus::javascript::asg::addon::ClassDeclarationWrapper::Init(exports);           
  columbus::javascript::asg::addon::ExportSpecifierWrapper::Init(exports);           
  columbus::javascript::asg::addon::FunctionDeclarationWrapper::Init(exports);           
  columbus::javascript::asg::addon::ExportAllDeclarationWrapper::Init(exports);           
  columbus::javascript::asg::addon::ExportDefaultDeclarationWrapper::Init(exports);           
  columbus::javascript::asg::addon::VariableDeclarationWrapper::Init(exports);           
  columbus::javascript::asg::addon::ForOfStatementWrapper::Init(exports);           
  columbus::javascript::asg::addon::DoWhileStatementWrapper::Init(exports);           
  columbus::javascript::asg::addon::ImportDefaultSpecifierWrapper::Init(exports);           
  columbus::javascript::asg::addon::ImportNamespaceSpecifierWrapper::Init(exports);           
  columbus::javascript::asg::addon::ImportSpecifierWrapper::Init(exports);           
}                                          
                                           
NODE_MODULE(javascriptaddon, InitAll)              
