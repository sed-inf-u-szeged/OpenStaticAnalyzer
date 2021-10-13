name = "LavaFlow"
role = "deadClass"
kind = "ndkClass"
priority = "Minor"
category = "AntiPattern"
displayName = "Lava Flow, Dead Code"
description = "Dead code and forgotten design information is frozen in an ever-changing design. This is analogous to a Lava Flow with hardening globules of rocky material. The refactored solution includes a configuration management process that eliminates dead code and evolves or refactors design toward increasing quality."

def filter(node):
    return node.instanceOf(kind)

def visit(node):
    if filter(node):
        if len(node.traverse(edge = "edkTypeFormerType_RefersTo", reverse = True)) == 0:
            node.setWarning(patternName = name, roleName = role, category = category, priority = priority, displayName = displayName, description = description)
            return "Found on py [" + str(node.getValue("id")) + "]\n"

        collectedWarnings = {}
        collectedWarnings["unusedMethod"] = []
        collectedWarnings["unusedAttribute"] = []

        for member in node.traverse(edge = "edkScope_HasMember", reverse = False):
            isAttribute = member.instanceOf("ndkAttribute")
            isMethod = member.instanceOf("ndkMethod")

            if isMethod and len(member.traverse(edge = "edkMethodCall_Method", reverse = True)) == 0:
                collectedWarnings["unusedMethod"].append(member)

            if isAttribute and len(member.traverse(edge = "edkAttributeAccess_Attribute", reverse = True)) == 0:
                collectedWarnings["unusedAttribute"].append(member)

        if collectedWarnings["unusedMethod"] or collectedWarnings["unusedAttribute"]:
            node.setWarning(children = collectedWarnings, patternName = name, roleName = role, category = category, priority = priority, displayName = displayName, description = description)
            return "[Found py on '" + str(node.getValue("id")) + "']\n"
    return None
