name = "Composite"
role = "compMainClass"
kind = "ndkClass"
category = "DesignPattern"
priority = "Info"
displayName = "Composite"
description = "Composites that contain Components, each of which could be a Composite."

def filter(node):
    return node.getValue("isAbstract") or node.getValue("classKind") == "clkInterface"

def visit(node):
    if filter(node):
        if node.getValue("NM") >= 1 :
            methodCond = False
            compositeCond = False
            children = {
                "leaf" : [],
                "composite" : []
            }

            for method in node.traverse(edge = "edkScope_HasMember", kind = "ndkMethod", reverse = False):
                if method.getValue("isAbstract") or method.getValue("isVirtual"):
                    methodCond = True

            for compSubClass in node.getType().traverse(edge = "edkClass_IsSubclass", kind = "ndkClass", reverse = True):
                addedToComp = False
                for attr in compSubClass.traverse(edge = "edkScope_HasMember", kind = "ndkAttribute", reverse = False):
                    if attr.typeEquals(node):
                        compositeCond = True
                        addedToComp = True
                        children["composite"].append(compSubClass)
                if not addedToComp:
                    children["leaf"].append(compSubClass)

            if methodCond and compositeCond:
                node.setWarning(patternName = name, children = children, roleName = role, category = category, priority = priority, displayName = displayName, description = description)
                return "Found on py [" + str(node.getValue("id")) + "]\n"
    return None