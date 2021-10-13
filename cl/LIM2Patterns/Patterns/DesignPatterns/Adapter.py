name = "Adapter"
role = "adapterClass"
kind = "ndkClass"
category = "DesignPattern"
priority = "Info"
displayName = "Adapter"
description = "The Adapter acts as a wrapper between two objects. It catches calls for one object and transforms them to format and interface recognizable by the second object."

def filter(node):
    return node.instanceOf(kind)

def visit(node):
    if filter(node):
        parentIsInterface = False
        parents = []
        attrTypes = []
        # can give false output because there is not no concrete definition of "Adaptee"
        adapteeIsNotFromSameInterface = True
        hasConstructor = False

        for parentClassType in node.traverse(edge = "edkClass_IsSubclass", kind = "ndkType", reverse = False):
            try:
                # try/except because of java cases
                parent = parentClassType.getClass()
            except Exception as x:
                print(node, x)
                continue
            if parent.instanceOf("ndkClass") and (parent.getValue("classKind") == "clkInterface" or parent.getValue("isAbstract")):
                parentIsInterface = True
                parents.append(parentClassType)

        for attr in node.traverse(edge = "edkScope_HasMember", kind = "ndkAttribute", reverse = False):
            if attr.getValue("accessibility") == "ackPrivate":
                try:
                    # try/except because of c++ cases
                    attrTypeClass = attr.getType().getClass()
                except Exception as x:
                    print(node, x)
                    continue
                attrTypes.append(attr.getType())
                for parentClassType in attrTypeClass.traverse(edge = "edkClass_IsSubclass", kind = "ndkType", reverse = False):
                    if parentClassType in parents:
                        adapteeIsNotFromSameInterface = False

        for method in node.traverse(edge = "edkScope_HasMember", kind = "ndkMethod", reverse = False):
            if method.getValue("methodKind") == "mekConstructor":
                for param in method.traverse(edge = "edkMethod_HasParameter", kind = "ndkParameter", reverse = False):
                    if param.getType() in attrTypes:
                        hasConstructor = True

        if parentIsInterface and adapteeIsNotFromSameInterface and hasConstructor:
            node.setWarning(patternName = name, roleName = role, category = category, priority = priority, displayName = displayName, description = description)
            return "[Found on py " + str(node.getValue("id")) + "]\n"

    return None