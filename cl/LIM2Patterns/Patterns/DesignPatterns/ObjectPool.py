name = "objectPool"
role = "poolClass"
kind = "ndkClass"
priority = "Info"
category = "DesignPattern"
displayName = "Oject Pool"
description = "The Object Pool lets others \"check out\" objects from its pool, when those objects are no longer needed by their processes, they are returned to the pool in order to be reused."

def visit(node):
    if not (node.getValue("NA") >= 1) :
        return None
    if not (node.getValue("NM") >= 5) :
        return None

    condition = False
    
    for member in node.traverse(edge = "edkScope_HasMember", kind = "ndkAttribute", reverse = False):
        
        # attributes must be private
        if member.getValue("accessibility") != "ackPrivate":
            return None

        # there is a get method for every attribute (resuable + instance)
        condition = False
        for _member in node.traverse(edge = "edkScope_HasMember", reverse = False):
            if _member.instanceOf("ndkMethod") and member.typeSimilar(_member):
                condition = True
        if not condition:
            return None

    for member in node.traverse(edge = "edkScope_HasMember", kind = "ndkMethod", reverse = False):
        # check every non constructor method to be public
        if member.getValue("methodKind") != "mekConstructor" and member.getValue("accessibility") != "ackPublic":
            return None
        
        # check every constructor to be private
        if member.getValue("methodKind") == "mekConstructor" and member.getValue("accessibility") != "ackPrivate":
            return None

        # check if there is a method that returns an objectpool instance
        if member.getValue("methodKind") != "mekConstructor" and (member.getValue("isStatic") or member.getValue("accessibility") == "ackPublic" or member.typeEquals(node)):
            condition = True

    if condition:
        node.setWarning(patternName = name, roleName = role, category = category, priority = priority, displayName = displayName, description = description)
        return "Found on py [" + str(node.getValue("id")) + "]\n"

    return None 