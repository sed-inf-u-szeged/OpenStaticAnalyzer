from util.helpers import *

name = "refusedBeq"
role = "refBeqClass"
kind = "ndkClass"
priority = "Minor"
category = "AntiPattern"
displayName = "Refused Bequest"
description = "If a subclass uses only some of the methods and properties inherited from its parents, the hierarchy is off-kilter. The unneeded methods may simply go unused or be redefined and give off exceptions."

# recursively searches for classes that extends from "node" class
def collectDescendantMap(node):
  descMap = []
  try:
    for _node in node.getType().traverse("edkClass_IsSubclass", True):
      descMap.append(_node)
      for _desc in collectDescendantMap(_node):
        descMap.append(_desc)
  except Exception as _:
    return descMap
  return descMap

def get_id(node):
  return node.getValue("id")

# újitott verzió
def visit(node):
  descendantSet = collectDescendantMap(node)
  collectNotUsesMethod = set()
  collectNotUsesAttribute = set()

  for member in node.traverse("edkScope_HasMember"):
    if member.getValue("accessibility") == "ackProtected":
      if member.instanceOf("ndkAttribute"):
        # make warning if there is no 'edkAttributeAccess_Attribute' edge to be travel to
        attributeIsBeingUsed = False
        for attrAcc in member.traverse("edkAttributeAccess_Attribute", reverse = True):
          for methAttrAcc in attrAcc.traverse("edkMethod_AccessesAttribute", reverse = True):
            method = methAttrAcc
            try:
              methodParent = method.getParent()
              if methodParent.getValue("kind") == "ndkClass":
                attributeIsBeingUsed = True
                break
            except:
              pass
        if not attributeIsBeingUsed:
          collectNotUsesAttribute.add(member)

      # child class doesnt override the the abstract/virtual functions
      # and does not uses the base class methods
      elif member.instanceOf("ndkMethod") :
        for desc in descendantSet:
            methodIsBeingUsed = False
            for methCallMethod in member.traverse("edkMethodCall_Method", reverse = True):
              for methCall in methCallMethod.traverse("edkMethod_Calls", reverse = True):
                method = methCall
                methodParent = method.getParent()
                if methodParent.getValue("kind") == "ndkClass":
                  methodIsBeingUsed = True
                  break
            if not methodIsBeingUsed:
              collectNotUsesMethod.add(member)
      else:
        continue

  # if there is any collected warning 
  if collectNotUsesMethod or collectNotUsesAttribute:
    _dict = {"methodIsNotUsed":[],"attributeIsNotUsed":[]}

    for temp in collectNotUsesAttribute:
      _dict["attributeIsNotUsed"].append(temp)
    for temp in collectNotUsesMethod:
      _dict["methodIsNotUsed"].append(temp)

    _dict["attributeIsNotUsed"].sort(key=get_id)
    _dict["methodIsNotUsed"].sort(key=get_id)

    node.setWarning(name, role, _dict, displayName, category, priority, description)
    return foundStr(displayName, node)
  return None