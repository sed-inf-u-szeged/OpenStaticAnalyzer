name = "Prototype"
role = "cloneableClass"
kind = "ndkClass"
category = "DesignPattern"
priority = "Info"
displayName = "Prototype"
description = "The Factory knows how to find the correct Prototype, and each Product knows how to spawn new instances of itself."

def filter(node):
    return node.getValue("classKind") == "clkInterface" or node.getValue("isAbstract")

def visit(node):
    if filter(node):
        anyCond = False
        cloneMethods = []
        for method in node.traverse(edge = "edkScope_HasMember", kind = "ndkMethod", reverse = False):
            # by checking the method to be abstract/virtual, we ensure that it will be overwritten in the child classes
            if method.getValue("methodKind") == "mekNormal" and method.getValue("accessibility") == "ackPublic" and method.typeEquals(node) and any(_name in method.getValue("name").lower() for _name in ["clone","copy"]) and any([method.getValue("isAbstract"), method.getValue("isVirtual")]):
                anyCond = True
                cloneMethods.append(method)
                break
            if method.getValue("methodKind") == "mekConstructor" and method.getValue("accessibility") == "ackPublic":
                return None

        # has a subclass
        anyCond = False if len(node.getType().traverse(edge = "edkClass_IsSubclass", kind = "ndkClass", reverse = True)) == 0 else True
        for subClass in node.getType().traverse(edge = "edkClass_IsSubclass", kind = "ndkClass", reverse = True):
            for method in subClass.traverse(edge = "edkScope_HasMember", kind = "ndkMethod", reverse = False):
                methodName = method.getValue("name")
                methodReturnType = method.getValue("returnType")
                for _method in cloneMethods:
                    _methodName = _method.getValue("name")
                    _methodReturnType = _method.getValue("returnType")
                    # method is a clone method
                    if methodName == _methodName and methodReturnType == _methodReturnType:
                        if not subClass.getType() in method.traverse(edge = "edkMember_Uses", kind = "ndkType", reverse = False):
                            return None

        if anyCond:
            node.setWarning(patternName = name, roleName = role, category = category, priority = priority, displayName = displayName, description = description)
            return "Found on py [" + str(node.getValue("id")) + "]\n"

    return None