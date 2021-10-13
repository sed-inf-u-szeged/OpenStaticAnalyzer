from util.helpers import *

name = "TemporaryField"
role = "tempAttr"
kind = "ndkAttribute"
priority = "Major"
category = "AntiPattern"
description = "Temporary fields get their values (and thus are needed by objects) only under certain circumstances. Outside of these circumstances, they are empty."
displayName = "Temporary Field"

def filter(node):
  return node.instanceOf(kind) and node.getValue("accessibility") != "ackPublic" and not node.getValue("name").isupper()

def visit(node):
  if filter(node):
    parent = node.getParent()
    accessMapSize = 0
    for attrAccAttr in node.traverse(edge = "edkAttributeAccess_Attribute", reverse = True):
      for methodAccAttr in attrAccAttr.traverse(edge = "edkMethod_AccessesAttribute", reverse = True):
        for methodParent in methodAccAttr.traverse(edge = "edkScope_HasMember", reverse = True):
          if parent == methodParent:
            accessMapSize += 1
    # condition check
    # Number of Local Methods
    numberOfMethods = len(getLocalMethods(parent))
    if isStatic(node):
      numberOfMethods = len(getLocalMethods(parent, static = True))

    if numberOfMethods > 0:
      tf = accessMapSize / numberOfMethods
      if tf < 0.1: #max ratio
        node.setMetric("tf", tf)
        node.setWarning(children = {}, patternName = name, roleName = role, displayName = displayName, category = category, priority = priority, description = description)
        return foundStr(displayName, node)
  return None