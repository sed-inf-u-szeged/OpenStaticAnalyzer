name = "Singleton"
kind = "ndkClass"
role = "SingletonClass"
category = "DesignPattern"
priority = "Info"
description = "Application needs one, and only one, instance of an object. Additionally, lazy initialization and global access are necessary."
displayName = "Singleton"

def visit(node):
    instanceAttribute = False
    getInstanceMethod = False

    for attr in node.traverse(edge = "edkScope_HasMember", kind = "ndkAttribute"):
        if attr.getValue("accessibility") == "ackPrivate" and attr.getValue("isStatic") and attr.typeSimilar(node):
            instanceAttribute = True

    for method in node.traverse(edge = "edkScope_HasMember", kind = "ndkMethod"):
        if method.getValue("accessibility") == "ackPublic" and method.getValue("isStatic") and method.typeSimilar(node):
            getInstanceMethod = True

    for method in node.traverse(edge = "edkScope_HasMember", kind = "ndkMethod"):
        if method.getValue("methodKind") == "mekConstructor":
            if method.getValue("accessibility") != "ackPrivate" and method.getValue("accessibility") != "ackProtected":
                return None

    if instanceAttribute and getInstanceMethod:
        node.setWarning(patternName = name, roleName = role, category = category, priority = priority, displayName = displayName, description = description)
        return "Found on py [" + str(node.getValue("id")) + "]\n"
    return None