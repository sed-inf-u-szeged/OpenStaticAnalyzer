from util.helpers import *

name = "LazyClass"
role = "lazyClass"
kind = "ndkClass"
priority = "Minor"
category = "AntiPattern"
displayName = "Lazy Class"
description = "Understanding and maintaining classes always costs time and money. So if a class doesn’t do enough to earn your attention, it should be deleted."

def visit(node):
  if not isClassNested(node) and node.getValue("CBO") >= 5 and node.getValue("WMC") <= 10:
    node.setWarning(patternName = name, roleName = role, category = category, priority = priority, displayName = displayName, description = description)
    return foundStr(displayName, node)
  
  return None