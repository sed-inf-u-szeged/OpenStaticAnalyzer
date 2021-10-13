from util.helpers import *

name = "shotgun"
role = "shotgunMethod"
kind = "ndkMethod"
category = "AntiPattern"
priority = "Minor"
displayName = "Shotgun Surgery"
description = "We talk about a Shotgun Surgery when in case of a general modification, we have to make a lot of small changes in a lot of different classes. If we have at least 'Min' references to a function, the function is considered a Shotgun Surgery."

def visit(node):
    try:
        if node.getValue("NII") >= 10:
            node.setWarning(patternName = name, roleName = role, category = category, priority = priority, displayName = displayName, description = description)
            return foundStr(displayName, node)
    except:
        pass
    
    return None