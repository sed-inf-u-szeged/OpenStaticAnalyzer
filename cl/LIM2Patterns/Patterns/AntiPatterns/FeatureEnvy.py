from util.helpers import *

name = "featureEnvy"
role = "envyMethod"
kind = "ndkMethod"
priority = "Minor"
category = "AntiPattern"
displayName = "Feature Envy"
description = "A method accesses the data of another object more than its own data."

def filter(node):
    return node.getValue("kind") == kind

def visit(node):
    if filter(node):
        parent = node.getParent()
        localAccess = 0
        foreignAccess = 0
        for methodAccAttr in node.traverse(edge = "edkMethod_AccessesAttribute", kind = "ndkAttributeAccess", reverse = False):
            for attr in methodAccAttr.traverse(edge = "edkAttributeAccess_Attribute", kind = "ndkAttribute", reverse = False):
                for methodUsesThisClass in attr.traverse(edge = "edkScope_HasMember", kind = "ndkClass", reverse = True):
                    if parent == methodUsesThisClass:
                        localAccess += 1
                    else:
                        foreignAccess += 1
        
        if (localAccess + foreignAccess >= 5) and (foreignAccess / (foreignAccess + localAccess) >= 0.8) :
            node.setWarning(patternName = name, roleName = role, category = category, description = description, displayName = displayName, priority = priority)
            return foundStr(displayName, node)
    return None