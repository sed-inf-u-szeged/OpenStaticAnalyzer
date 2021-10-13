from util.helpers import *

name = "LongParamSize"
role = "tooManyParam"
kind = "ndkMethod"
category = "AntiPattern"
priority = "Minor"
displayName = "Long Parameter Size"
description = "In object-oriented programing we do not have to pass every parameter to a function or a method, only the ones that are necessary for the good operation. Long parameter lists can be hard to understand, they become inconsistent and hard to change. If a function has at least 'Min' parameters, we consider it a Long Parameter List bad smell."

def visit(node):
  
  try:
    if node.getValue("parameterSize") >= 7:
      node.setWarning(patternName = name, roleName = role, category = category, priority = priority, displayName = displayName, description = description)
      return foundStr(displayName, node)
  except:
    pass
  
  return None