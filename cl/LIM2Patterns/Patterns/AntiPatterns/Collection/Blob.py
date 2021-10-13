from util.helpers import *

name = "Blob"
role = "BlobClass"
kind = "ndkClass"
category = "AntiPattern"
priority = "Minor"
displayName = "Blob"
description = "Also Known As: Winnebago and The God Class<br> The Blob is found in designs where one class monopolizes the processing, and other classes primarily encapsulate data. This AntiPattern is characterized by a class diagram composed of a single complex controller class surrounded by simple data classes. The key problem here is that the majority of the responsibilities are allocated to a single class."

def visit(node):

  # Number of Local Attributes
  try:
    NLA = node.getValue("NLA")
    if NLA < 0:
      NLA = 0
  except:
    pass

  # Number of Local Methods
  try:
    NLM = node.getValue("NLM")
    if NLM < 0:
      NLM = 0
  except:
    pass

  if NLA + NLM >= 60 or  node.getValue("LLOC") >= 1000:
    node.setWarning(patternName = name, roleName = role, category = category, priority = priority, displayName = displayName, description = description)
    return foundStr(displayName, node)
  
  return None