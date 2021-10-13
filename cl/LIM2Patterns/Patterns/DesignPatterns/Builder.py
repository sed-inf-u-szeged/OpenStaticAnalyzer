role = "BuilderClass"
kind = "ndkClass"
category = "DesignPattern"
priority = "Info"
patternName = "Builder"
displayName = "Builder"
description = "Separate the construction of a complex object from its representation so that the same construction process can create different representations."

def CPPisAbstractClass(node):
    if node.getValue("kind") == "ndkClass":
        for method in node.traverse(edge = "edkScope_HasMember", kind = "ndkMethod", reverse = False):
            isVirtual = method.getValue("isVirtual")
            if not method.getValue("isVirtual"):
                return False
    return True

def filter(_node):
    return (_node.getValue("isAbstract") or CPPisAbstractClass(_node)) and _node.getValue("NA") == 0 and _node.getValue("NM") >= 2

def visit(node):
    if filter(node):
        abstractMethod = 0
        ret = False
        resetMethod = False
        director = {
            "privateBuilder" : False,
            "setterMethod" : False,
            "methodUsesBuilder" : False,
            "methods" : {}
        }

        for children in node.traverse(edge = "edkScope_HasMember", kind = "ndkMethod", reverse = False):
            if ((children.getValue("isAbstract") or children.getValue("isVirtual")) and children.getValue("accessibility") == "ackPublic"):
                abstractMethod += 1
        
        for subClass in node.getType().traverse(edge = "edkClass_IsSubclass", kind = "ndkClass", reverse = True):
            attrs = []

            for attr in subClass.traverse(edge = "edkScope_HasMember", kind = "ndkAttribute", reverse = False):
                if attr.getValue("accessibility") == "ackPrivate":
                    attrs.append(attr.getType())

            for method in subClass.traverse(edge = "edkScope_HasMember", kind = "ndkMethod", reverse = False):
                for attr in attrs:
                    if attr.typeEquals(method):
                        ret = True
                if "reset" in method.getValue("name").lower():
                    resetMethod = True

        #multitype cases
        for tft in node.traverse(edge = "edkTypeFormerType_RefersTo", kind = "ndkTypeFormerType", reverse = True):
            for _type in tft.traverse(edge = "edkType_HasTypeFormer", kind = "ndkType", reverse = True):
                for attr in _type.traverse(edge = "edkAttribute_HasType", kind = "ndkAttribute", reverse = True):
                    if attr.getValue("accessibility") == "ackPrivate":
                        director["privateBuilder"] = True
                        for classThatUsesBuilderInterface in attr.traverse(edge = "edkScope_HasMember", kind = "ndkClass", reverse = True):
                            for method in classThatUsesBuilderInterface.traverse(edge = "edkScope_HasMember", kind = "ndkMethod", reverse = False):
                                for param in method.traverse(edge = "edkMethod_HasParameter", kind = "ndkParameter", reverse = False):
                                    if param.typeEquals(attr):
                                        director["setterMethod"] = True
                                for attrAccess in method.traverse(edge = "edkMethod_AccessesAttribute", kind = "ndkAttributeAccess", reverse = False):
                                    for _attr in attrAccess.traverse(edge = "edkAttributeAccess_Attribute", kind = "ndkAttribute", reverse = False):
                                        if attr == _attr:
                                            director["methodUsesBuilder"] = True
                                            for methodCall in method.traverse(edge = "edkMethod_Calls", kind = "ndkMethodCall", reverse = False):
                                                for methodCallMethod in methodCall.traverse(edge = "edkMethodCall_Method", kind = "ndkMethod", reverse = False):
                                                    for parentClass in methodCallMethod.traverse(edge = "edkScope_HasMember", kind = "ndkClass", reverse = True):
                                                        if parentClass == node:
                                                            temp = method.getValue("name")
                                                            director["methods"][temp] = director["methods"][temp]+1 if temp in director["methods"] else 1

        callsNumberBefore = []
        differentCallsNumber = False
        for x in director["methods"]:
            if callsNumberBefore:
                for _x in callsNumberBefore:
                    if _x != director["methods"][x]:
                        differentCallsNumber = True
            callsNumberBefore.append(director["methods"][x])

        if abstractMethod >= 2 and ret and resetMethod and director["privateBuilder"] and director["setterMethod"] and director["methodUsesBuilder"] and len(director["methods"]) >= 2 and differentCallsNumber:
            node.setWarning(patternName = patternName, roleName = role, displayName = displayName, category = category, priority = priority, description = description)
            return "Found py pattern on [" + str(node.getValue("id")) + "]\n"
    return None
