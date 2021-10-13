#include "Factory.h"
#include "javascript/inc/javascript.h"
#include "javascript/inc/messages.h"
#include <assert.h>


namespace columbus { namespace javascript { namespace asg { namespace addon {


napi_ref Factory::constructor;

Factory::Factory(): env_(nullptr), wrapper_(nullptr) {}

Factory::~Factory() { napi_delete_reference(env_, wrapper_); }

void Factory::Destructor(napi_env env, void* nativeObject, void* ) {
    Factory* obj = reinterpret_cast<Factory*>(nativeObject);
    delete obj->strTable;
    delete obj->factory;
    obj->~Factory();
}

napi_value Factory::Init(napi_env env, napi_value& exports) {
    napi_status status;

    napi_property_descriptor props [] = {
        DECLARE_NAPI_METHOD("getRoot", getRoot),
        DECLARE_NAPI_METHOD("createCommentWrapper", createCommentWrapper),
        DECLARE_NAPI_METHOD("createModuleDeclarationWrapper", createModuleDeclarationWrapper),
        DECLARE_NAPI_METHOD("createVariableDeclaratorWrapper", createVariableDeclaratorWrapper),
        DECLARE_NAPI_METHOD("createPropertyWrapper", createPropertyWrapper),
        DECLARE_NAPI_METHOD("createSpreadElementWrapper", createSpreadElementWrapper),
        DECLARE_NAPI_METHOD("createSuperWrapper", createSuperWrapper),
        DECLARE_NAPI_METHOD("createTemplateElementWrapper", createTemplateElementWrapper),
        DECLARE_NAPI_METHOD("createCatchClauseWrapper", createCatchClauseWrapper),
        DECLARE_NAPI_METHOD("createFunctionWrapper", createFunctionWrapper),
        DECLARE_NAPI_METHOD("createSwitchCaseWrapper", createSwitchCaseWrapper),
        DECLARE_NAPI_METHOD("createClassBodyWrapper", createClassBodyWrapper),
        DECLARE_NAPI_METHOD("createMethodDefinitionWrapper", createMethodDefinitionWrapper),
        DECLARE_NAPI_METHOD("createProgramWrapper", createProgramWrapper),
        DECLARE_NAPI_METHOD("createIdentifierWrapper", createIdentifierWrapper),
        DECLARE_NAPI_METHOD("createExportNamedDeclarationWrapper", createExportNamedDeclarationWrapper),
        DECLARE_NAPI_METHOD("createImportDeclarationWrapper", createImportDeclarationWrapper),
        DECLARE_NAPI_METHOD("createArrayExpressionWrapper", createArrayExpressionWrapper),
        DECLARE_NAPI_METHOD("createArrowFunctionExpressionWrapper", createArrowFunctionExpressionWrapper),
        DECLARE_NAPI_METHOD("createAssignmentExpressionWrapper", createAssignmentExpressionWrapper),
        DECLARE_NAPI_METHOD("createAwaitExpressionWrapper", createAwaitExpressionWrapper),
        DECLARE_NAPI_METHOD("createBinaryExpressionWrapper", createBinaryExpressionWrapper),
        DECLARE_NAPI_METHOD("createCallExpressionWrapper", createCallExpressionWrapper),
        DECLARE_NAPI_METHOD("createClassExpressionWrapper", createClassExpressionWrapper),
        DECLARE_NAPI_METHOD("createConditionalExpressionWrapper", createConditionalExpressionWrapper),
        DECLARE_NAPI_METHOD("createFunctionExpressionWrapper", createFunctionExpressionWrapper),
        DECLARE_NAPI_METHOD("createLogicalExpressionWrapper", createLogicalExpressionWrapper),
        DECLARE_NAPI_METHOD("createMemberExpressionWrapper", createMemberExpressionWrapper),
        DECLARE_NAPI_METHOD("createMetaPropertyWrapper", createMetaPropertyWrapper),
        DECLARE_NAPI_METHOD("createNewExpressionWrapper", createNewExpressionWrapper),
        DECLARE_NAPI_METHOD("createObjectExpressionWrapper", createObjectExpressionWrapper),
        DECLARE_NAPI_METHOD("createSequenceExpressionWrapper", createSequenceExpressionWrapper),
        DECLARE_NAPI_METHOD("createTaggedTemplateExpressionWrapper", createTaggedTemplateExpressionWrapper),
        DECLARE_NAPI_METHOD("createTemplateLiteralWrapper", createTemplateLiteralWrapper),
        DECLARE_NAPI_METHOD("createThisExpressionWrapper", createThisExpressionWrapper),
        DECLARE_NAPI_METHOD("createUnaryExpressionWrapper", createUnaryExpressionWrapper),
        DECLARE_NAPI_METHOD("createUpdateExpressionWrapper", createUpdateExpressionWrapper),
        DECLARE_NAPI_METHOD("createYieldExpressionWrapper", createYieldExpressionWrapper),
        DECLARE_NAPI_METHOD("createBooleanLiteralWrapper", createBooleanLiteralWrapper),
        DECLARE_NAPI_METHOD("createNullLiteralWrapper", createNullLiteralWrapper),
        DECLARE_NAPI_METHOD("createNumberLiteralWrapper", createNumberLiteralWrapper),
        DECLARE_NAPI_METHOD("createRegExpLiteralWrapper", createRegExpLiteralWrapper),
        DECLARE_NAPI_METHOD("createStringLiteralWrapper", createStringLiteralWrapper),
        DECLARE_NAPI_METHOD("createAssignmentPropertyWrapper", createAssignmentPropertyWrapper),
        DECLARE_NAPI_METHOD("createArrayPatternWrapper", createArrayPatternWrapper),
        DECLARE_NAPI_METHOD("createAssignmentPatternWrapper", createAssignmentPatternWrapper),
        DECLARE_NAPI_METHOD("createObjectPatternWrapper", createObjectPatternWrapper),
        DECLARE_NAPI_METHOD("createRestElementWrapper", createRestElementWrapper),
        DECLARE_NAPI_METHOD("createBlockStatementWrapper", createBlockStatementWrapper),
        DECLARE_NAPI_METHOD("createBreakStatementWrapper", createBreakStatementWrapper),
        DECLARE_NAPI_METHOD("createContinueStatementWrapper", createContinueStatementWrapper),
        DECLARE_NAPI_METHOD("createDebuggerStatementWrapper", createDebuggerStatementWrapper),
        DECLARE_NAPI_METHOD("createEmptyStatementWrapper", createEmptyStatementWrapper),
        DECLARE_NAPI_METHOD("createExpressionStatementWrapper", createExpressionStatementWrapper),
        DECLARE_NAPI_METHOD("createForInStatementWrapper", createForInStatementWrapper),
        DECLARE_NAPI_METHOD("createForStatementWrapper", createForStatementWrapper),
        DECLARE_NAPI_METHOD("createIfStatementWrapper", createIfStatementWrapper),
        DECLARE_NAPI_METHOD("createLabeledStatementWrapper", createLabeledStatementWrapper),
        DECLARE_NAPI_METHOD("createReturnStatementWrapper", createReturnStatementWrapper),
        DECLARE_NAPI_METHOD("createSwitchStatementWrapper", createSwitchStatementWrapper),
        DECLARE_NAPI_METHOD("createThrowStatementWrapper", createThrowStatementWrapper),
        DECLARE_NAPI_METHOD("createTryStatementWrapper", createTryStatementWrapper),
        DECLARE_NAPI_METHOD("createWhileStatementWrapper", createWhileStatementWrapper),
        DECLARE_NAPI_METHOD("createWithStatementWrapper", createWithStatementWrapper),
        DECLARE_NAPI_METHOD("createClassDeclarationWrapper", createClassDeclarationWrapper),
        DECLARE_NAPI_METHOD("createExportSpecifierWrapper", createExportSpecifierWrapper),
        DECLARE_NAPI_METHOD("createFunctionDeclarationWrapper", createFunctionDeclarationWrapper),
        DECLARE_NAPI_METHOD("createExportAllDeclarationWrapper", createExportAllDeclarationWrapper),
        DECLARE_NAPI_METHOD("createExportDefaultDeclarationWrapper", createExportDefaultDeclarationWrapper),
        DECLARE_NAPI_METHOD("createVariableDeclarationWrapper", createVariableDeclarationWrapper),
        DECLARE_NAPI_METHOD("createForOfStatementWrapper", createForOfStatementWrapper),
        DECLARE_NAPI_METHOD("createDoWhileStatementWrapper", createDoWhileStatementWrapper),
        DECLARE_NAPI_METHOD("createImportDefaultSpecifierWrapper", createImportDefaultSpecifierWrapper),
        DECLARE_NAPI_METHOD("createImportNamespaceSpecifierWrapper", createImportNamespaceSpecifierWrapper),
        DECLARE_NAPI_METHOD("createImportSpecifierWrapper", createImportSpecifierWrapper),
        DECLARE_NAPI_METHOD("saveAST", SaveAST),
        DECLARE_NAPI_METHOD("loadAST", LoadAST),
        DECLARE_NAPI_METHOD("clear", Clear)
    };

    napi_value cons;
    status = napi_define_class(env, "Factory", NAPI_AUTO_LENGTH, New, nullptr, sizeof(props) / sizeof(*props), props, &cons);
    assert(status == napi_ok);

    status = napi_create_reference(env, cons, 1, &constructor);
    assert(status == napi_ok);

    status = napi_set_named_property(env, exports, "Factory", cons);
    assert(status == napi_ok);

    return exports;
}


napi_value Factory::New(napi_env env, napi_callback_info info) {
    napi_status status;

    napi_value target;
    status = napi_get_new_target(env, info, &target);
    assert(status == napi_ok);

    bool is_constructor = target != nullptr;

    if (is_constructor) {
        // Invoked as constructor: `new Factory()`
        napi_value jsthis;
        status = napi_get_cb_info(env, info, nullptr, nullptr, &jsthis, nullptr);
        assert(status == napi_ok);

        Factory* obj = new Factory();
        obj->strTable = new columbus::RefDistributorStrTable();
        obj->factory = new columbus::javascript::asg::Factory(*obj->strTable);
        obj->env_ = env;
        status = napi_wrap(env, jsthis, reinterpret_cast<void*>(obj), Factory::Destructor, nullptr,  &obj->wrapper_);        assert(status == napi_ok);

        return jsthis;
    }
    else{
        //Factory() was called without new keyword -> turn into constructor call
        status = napi_get_cb_info(env, info, nullptr, nullptr, nullptr, nullptr);
        assert(status == napi_ok);

        napi_value cons;
        status = napi_get_reference_value(env, constructor, &cons);
        assert(status == napi_ok);

        napi_value instance;
        status = napi_new_instance(env, cons, 0, nullptr, &instance);
        assert(status == napi_ok);

        return instance;
    }
}


napi_value Factory::getRoot(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    base::System* node;
    node = obj->factory->getRoot();
    

    napi_value instance;
    status = SystemWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createCommentWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    base::Comment* node;
    node = obj->factory->createCommentNode();
    

    napi_value instance;
    status = CommentWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createModuleDeclarationWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    declaration::ModuleDeclaration* node;
    node = obj->factory->createModuleDeclarationNode();
    

    napi_value instance;
    status = ModuleDeclarationWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createVariableDeclaratorWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    declaration::VariableDeclarator* node;
    node = obj->factory->createVariableDeclaratorNode();
    

    napi_value instance;
    status = VariableDeclaratorWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createPropertyWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    expression::Property* node;
    node = obj->factory->createPropertyNode();
    

    napi_value instance;
    status = PropertyWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createSpreadElementWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    expression::SpreadElement* node;
    node = obj->factory->createSpreadElementNode();
    

    napi_value instance;
    status = SpreadElementWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createSuperWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    expression::Super* node;
    node = obj->factory->createSuperNode();
    

    napi_value instance;
    status = SuperWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createTemplateElementWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    expression::TemplateElement* node;
    node = obj->factory->createTemplateElementNode();
    

    napi_value instance;
    status = TemplateElementWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createCatchClauseWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    statement::CatchClause* node;
    node = obj->factory->createCatchClauseNode();
    

    napi_value instance;
    status = CatchClauseWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createFunctionWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    statement::Function* node;
    node = obj->factory->createFunctionNode();
    

    napi_value instance;
    status = FunctionWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createSwitchCaseWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    statement::SwitchCase* node;
    node = obj->factory->createSwitchCaseNode();
    

    napi_value instance;
    status = SwitchCaseWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createClassBodyWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    structure::ClassBody* node;
    node = obj->factory->createClassBodyNode();
    

    napi_value instance;
    status = ClassBodyWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createMethodDefinitionWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    structure::MethodDefinition* node;
    node = obj->factory->createMethodDefinitionNode();
    

    napi_value instance;
    status = MethodDefinitionWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createProgramWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    base::Program* node;
    node = obj->factory->createProgramNode();
    

    napi_value instance;
    status = ProgramWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createIdentifierWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    expression::Identifier* node;
    node = obj->factory->createIdentifierNode();
    

    napi_value instance;
    status = IdentifierWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createExportNamedDeclarationWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    declaration::ExportNamedDeclaration* node;
    node = obj->factory->createExportNamedDeclarationNode();
    

    napi_value instance;
    status = ExportNamedDeclarationWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createImportDeclarationWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    declaration::ImportDeclaration* node;
    node = obj->factory->createImportDeclarationNode();
    

    napi_value instance;
    status = ImportDeclarationWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createArrayExpressionWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    expression::ArrayExpression* node;
    node = obj->factory->createArrayExpressionNode();
    

    napi_value instance;
    status = ArrayExpressionWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createArrowFunctionExpressionWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    expression::ArrowFunctionExpression* node;
    node = obj->factory->createArrowFunctionExpressionNode();
    

    napi_value instance;
    status = ArrowFunctionExpressionWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createAssignmentExpressionWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    expression::AssignmentExpression* node;
    node = obj->factory->createAssignmentExpressionNode();
    

    napi_value instance;
    status = AssignmentExpressionWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createAwaitExpressionWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    expression::AwaitExpression* node;
    node = obj->factory->createAwaitExpressionNode();
    

    napi_value instance;
    status = AwaitExpressionWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createBinaryExpressionWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    expression::BinaryExpression* node;
    node = obj->factory->createBinaryExpressionNode();
    

    napi_value instance;
    status = BinaryExpressionWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createCallExpressionWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    expression::CallExpression* node;
    node = obj->factory->createCallExpressionNode();
    

    napi_value instance;
    status = CallExpressionWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createClassExpressionWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    expression::ClassExpression* node;
    node = obj->factory->createClassExpressionNode();
    

    napi_value instance;
    status = ClassExpressionWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createConditionalExpressionWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    expression::ConditionalExpression* node;
    node = obj->factory->createConditionalExpressionNode();
    

    napi_value instance;
    status = ConditionalExpressionWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createFunctionExpressionWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    expression::FunctionExpression* node;
    node = obj->factory->createFunctionExpressionNode();
    

    napi_value instance;
    status = FunctionExpressionWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createLogicalExpressionWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    expression::LogicalExpression* node;
    node = obj->factory->createLogicalExpressionNode();
    

    napi_value instance;
    status = LogicalExpressionWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createMemberExpressionWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    expression::MemberExpression* node;
    node = obj->factory->createMemberExpressionNode();
    

    napi_value instance;
    status = MemberExpressionWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createMetaPropertyWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    expression::MetaProperty* node;
    node = obj->factory->createMetaPropertyNode();
    

    napi_value instance;
    status = MetaPropertyWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createNewExpressionWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    expression::NewExpression* node;
    node = obj->factory->createNewExpressionNode();
    

    napi_value instance;
    status = NewExpressionWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createObjectExpressionWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    expression::ObjectExpression* node;
    node = obj->factory->createObjectExpressionNode();
    

    napi_value instance;
    status = ObjectExpressionWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createSequenceExpressionWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    expression::SequenceExpression* node;
    node = obj->factory->createSequenceExpressionNode();
    

    napi_value instance;
    status = SequenceExpressionWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createTaggedTemplateExpressionWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    expression::TaggedTemplateExpression* node;
    node = obj->factory->createTaggedTemplateExpressionNode();
    

    napi_value instance;
    status = TaggedTemplateExpressionWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createTemplateLiteralWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    expression::TemplateLiteral* node;
    node = obj->factory->createTemplateLiteralNode();
    

    napi_value instance;
    status = TemplateLiteralWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createThisExpressionWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    expression::ThisExpression* node;
    node = obj->factory->createThisExpressionNode();
    

    napi_value instance;
    status = ThisExpressionWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createUnaryExpressionWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    expression::UnaryExpression* node;
    node = obj->factory->createUnaryExpressionNode();
    

    napi_value instance;
    status = UnaryExpressionWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createUpdateExpressionWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    expression::UpdateExpression* node;
    node = obj->factory->createUpdateExpressionNode();
    

    napi_value instance;
    status = UpdateExpressionWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createYieldExpressionWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    expression::YieldExpression* node;
    node = obj->factory->createYieldExpressionNode();
    

    napi_value instance;
    status = YieldExpressionWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createBooleanLiteralWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    expression::BooleanLiteral* node;
    node = obj->factory->createBooleanLiteralNode();
    

    napi_value instance;
    status = BooleanLiteralWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createNullLiteralWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    expression::NullLiteral* node;
    node = obj->factory->createNullLiteralNode();
    

    napi_value instance;
    status = NullLiteralWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createNumberLiteralWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    expression::NumberLiteral* node;
    node = obj->factory->createNumberLiteralNode();
    

    napi_value instance;
    status = NumberLiteralWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createRegExpLiteralWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    expression::RegExpLiteral* node;
    node = obj->factory->createRegExpLiteralNode();
    

    napi_value instance;
    status = RegExpLiteralWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createStringLiteralWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    expression::StringLiteral* node;
    node = obj->factory->createStringLiteralNode();
    

    napi_value instance;
    status = StringLiteralWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createAssignmentPropertyWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    expression::AssignmentProperty* node;
    node = obj->factory->createAssignmentPropertyNode();
    

    napi_value instance;
    status = AssignmentPropertyWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createArrayPatternWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    statement::ArrayPattern* node;
    node = obj->factory->createArrayPatternNode();
    

    napi_value instance;
    status = ArrayPatternWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createAssignmentPatternWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    statement::AssignmentPattern* node;
    node = obj->factory->createAssignmentPatternNode();
    

    napi_value instance;
    status = AssignmentPatternWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createObjectPatternWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    statement::ObjectPattern* node;
    node = obj->factory->createObjectPatternNode();
    

    napi_value instance;
    status = ObjectPatternWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createRestElementWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    statement::RestElement* node;
    node = obj->factory->createRestElementNode();
    

    napi_value instance;
    status = RestElementWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createBlockStatementWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    statement::BlockStatement* node;
    node = obj->factory->createBlockStatementNode();
    

    napi_value instance;
    status = BlockStatementWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createBreakStatementWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    statement::BreakStatement* node;
    node = obj->factory->createBreakStatementNode();
    

    napi_value instance;
    status = BreakStatementWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createContinueStatementWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    statement::ContinueStatement* node;
    node = obj->factory->createContinueStatementNode();
    

    napi_value instance;
    status = ContinueStatementWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createDebuggerStatementWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    statement::DebuggerStatement* node;
    node = obj->factory->createDebuggerStatementNode();
    

    napi_value instance;
    status = DebuggerStatementWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createEmptyStatementWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    statement::EmptyStatement* node;
    node = obj->factory->createEmptyStatementNode();
    

    napi_value instance;
    status = EmptyStatementWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createExpressionStatementWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    statement::ExpressionStatement* node;
    node = obj->factory->createExpressionStatementNode();
    

    napi_value instance;
    status = ExpressionStatementWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createForInStatementWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    statement::ForInStatement* node;
    node = obj->factory->createForInStatementNode();
    

    napi_value instance;
    status = ForInStatementWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createForStatementWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    statement::ForStatement* node;
    node = obj->factory->createForStatementNode();
    

    napi_value instance;
    status = ForStatementWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createIfStatementWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    statement::IfStatement* node;
    node = obj->factory->createIfStatementNode();
    

    napi_value instance;
    status = IfStatementWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createLabeledStatementWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    statement::LabeledStatement* node;
    node = obj->factory->createLabeledStatementNode();
    

    napi_value instance;
    status = LabeledStatementWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createReturnStatementWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    statement::ReturnStatement* node;
    node = obj->factory->createReturnStatementNode();
    

    napi_value instance;
    status = ReturnStatementWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createSwitchStatementWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    statement::SwitchStatement* node;
    node = obj->factory->createSwitchStatementNode();
    

    napi_value instance;
    status = SwitchStatementWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createThrowStatementWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    statement::ThrowStatement* node;
    node = obj->factory->createThrowStatementNode();
    

    napi_value instance;
    status = ThrowStatementWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createTryStatementWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    statement::TryStatement* node;
    node = obj->factory->createTryStatementNode();
    

    napi_value instance;
    status = TryStatementWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createWhileStatementWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    statement::WhileStatement* node;
    node = obj->factory->createWhileStatementNode();
    

    napi_value instance;
    status = WhileStatementWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createWithStatementWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    statement::WithStatement* node;
    node = obj->factory->createWithStatementNode();
    

    napi_value instance;
    status = WithStatementWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createClassDeclarationWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    declaration::ClassDeclaration* node;
    node = obj->factory->createClassDeclarationNode();
    

    napi_value instance;
    status = ClassDeclarationWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createExportSpecifierWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    structure::ExportSpecifier* node;
    node = obj->factory->createExportSpecifierNode();
    

    napi_value instance;
    status = ExportSpecifierWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createFunctionDeclarationWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    declaration::FunctionDeclaration* node;
    node = obj->factory->createFunctionDeclarationNode();
    

    napi_value instance;
    status = FunctionDeclarationWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createExportAllDeclarationWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    declaration::ExportAllDeclaration* node;
    node = obj->factory->createExportAllDeclarationNode();
    

    napi_value instance;
    status = ExportAllDeclarationWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createExportDefaultDeclarationWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    declaration::ExportDefaultDeclaration* node;
    node = obj->factory->createExportDefaultDeclarationNode();
    

    napi_value instance;
    status = ExportDefaultDeclarationWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createVariableDeclarationWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    declaration::VariableDeclaration* node;
    node = obj->factory->createVariableDeclarationNode();
    

    napi_value instance;
    status = VariableDeclarationWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createForOfStatementWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    statement::ForOfStatement* node;
    node = obj->factory->createForOfStatementNode();
    

    napi_value instance;
    status = ForOfStatementWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createDoWhileStatementWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    statement::DoWhileStatement* node;
    node = obj->factory->createDoWhileStatementNode();
    

    napi_value instance;
    status = DoWhileStatementWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createImportDefaultSpecifierWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    structure::ImportDefaultSpecifier* node;
    node = obj->factory->createImportDefaultSpecifierNode();
    

    napi_value instance;
    status = ImportDefaultSpecifierWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createImportNamespaceSpecifierWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    structure::ImportNamespaceSpecifier* node;
    node = obj->factory->createImportNamespaceSpecifierNode();
    

    napi_value instance;
    status = ImportNamespaceSpecifierWrapper::NewInstance(env, node, &instance);

    return instance;
}
napi_value Factory::createImportSpecifierWrapper(napi_env env, napi_callback_info info) {
    napi_status status;
    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    structure::ImportSpecifier* node;
    node = obj->factory->createImportSpecifierNode();
    

    napi_value instance;
    status = ImportSpecifierWrapper::NewInstance(env, node, &instance);

    return instance;
}
inline bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}
napi_value Factory::SaveAST(napi_env env, napi_callback_info info) {
    bool dumpJAVASCRIPTML = false;
    napi_status status;

    size_t argc = 2;
    napi_value args[2], jsthis;
    status = napi_get_cb_info(env, info, &argc, args, &jsthis, nullptr);
    assert(status == napi_ok);

    if (argc != 1 && argc != 2) {
        napi_throw_type_error(env, nullptr, "Wrong number of arguments"); 
        return nullptr;
    }
    napi_valuetype paramtype0;
    status = napi_typeof(env, args[0], &paramtype0);
    assert(status == napi_ok);

    if(paramtype0 != napi_string){
        napi_throw_type_error(env, nullptr, "First argument should be a string!"); 
        return nullptr;
    }

    if(argc == 2){
    napi_valuetype paramtype1;
        status = napi_typeof(env, args[1], &paramtype1);
        assert(status == napi_ok);

        if(paramtype1 != napi_boolean){
            napi_throw_type_error(env, nullptr, "Second argument should be a boolean!"); 
            return nullptr;
        }

        status = napi_get_value_bool(env, args[1], &dumpJAVASCRIPTML);
        assert(status == napi_ok);

    }

    char buffer[1024];
    size_t buffer_size = 1024, result_size = 0;
    status = napi_get_value_string_utf8(env, args[0], buffer, buffer_size, &result_size);
    assert(status == napi_ok);

    std::string filename(buffer);
    std::list<HeaderData*> headerList;
    columbus::PropertyData header;
    headerList.push_back(&header);
    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    obj->factory->save( filename, headerList);
    if(dumpJAVASCRIPTML){
        if(ends_with(filename, ".jssi")){
            filename = filename.substr(0,filename.size()- 5);
        }
        std::string dumpFileName = filename + ".jsml";
        common::WriteMsg::write(common::WriteMsg::mlNormal, "Dumping javascript schema instance into file: %s...", dumpFileName.c_str());
        std::ofstream ofs(dumpFileName.c_str());
        if (!ofs.is_open()) {
            common::WriteMsg::write(CMSG_CANNOT_OPEN_FILE, dumpFileName.c_str());
        } else {
            javascript::asg::VisitorJAVASCRIPTML visitor(ofs, "", NULL);
            javascript::asg::AlgorithmPreorder().run(*obj->factory, visitor);
            ofs.close();
            common::WriteMsg::write(CMSG_STAGE_DONE);
        }
    }
    return nullptr;
}
napi_value Factory::LoadAST(napi_env env, napi_callback_info info) {
    napi_status status;

    size_t argc = 1;
    napi_value args[1], jsthis;
    status = napi_get_cb_info(env, info, &argc, args, &jsthis, nullptr);
    assert(status == napi_ok);

    if (argc != 1) {
        napi_throw_type_error(env, nullptr, "Wrong number of arguments"); 
        return nullptr;
    }
    napi_valuetype paramtype0;
    status = napi_typeof(env, args[0], &paramtype0);
    assert(status == napi_ok);

    if(paramtype0 != napi_string){
        napi_throw_type_error(env, nullptr, "First argument should be a string!"); 
        return nullptr;
    }

    char buffer[1024];
    size_t buffer_size = 1024, result_size = 0;
    status = napi_get_value_string_utf8(env, args[0], buffer, buffer_size, &result_size);
    assert(status == napi_ok);

    std::string filename(buffer);
    std::list<HeaderData*> headerList;
    columbus::PropertyData header;
    headerList.push_back(&header);
    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    obj->factory->load( filename.c_str(), headerList);
    return nullptr;
}
napi_value Factory::Clear(napi_env env, napi_callback_info info) {
    napi_status status;

    napi_value jsthis;
    status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr); 
    assert(status == napi_ok);

    Factory* obj;
    status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    assert(status == napi_ok);

    obj->factory->clear();
    return nullptr;
}
}}}}
