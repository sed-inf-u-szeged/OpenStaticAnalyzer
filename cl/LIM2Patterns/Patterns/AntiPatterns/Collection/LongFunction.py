from util.helpers import *

name = "LongFunction"
role = "longFunc"
kind = "ndkMethod"
priority = "Minor"
category = "AntiPattern"
displayName = "Long Function"

def visit(node):
  
  if node.getValue("LLOC") >= 80 or node.getValue("NOS") >= 80 or node.getValue("McCC") >= 10:
    node.setWarning(patternName = name, roleName = role, category = category, priority = priority, displayName = displayName)
    return foundStr(displayName, node)
  
  return None