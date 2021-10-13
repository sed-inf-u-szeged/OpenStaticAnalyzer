name = "chainOfResp"
role = "chainClasses"
kind = "ndkClass"
priority = "Info"
displayName = "Chain of Responsibility"
description = "Chain of Responsibility is behavioral design pattern that allows passing request along the chain of potential handlers until one of them handles request."

def filter(node):
  return node.getValue("isAbstract")

def visit(node):
  if filter(node):
    methodHasClassParam = False
    instanceAttrIsAccessed = False
    hasRecursiveMethod = False
    subClassesCallsHandle = False
    hasBaseAttr = False
    subClassNumber = 0
    handleMethodNames = []
    baseClasses = []

    # collecting interface base classes
    for baseClassType in node.traverse(edge = "edkClass_IsSubclass", kind = "ndkType", reverse = False):
      if baseClassType.getValue("classKind") == "clkInterface" or baseClassType.getValue("isAbstract"):
        try:
          cl = baseClassType.getClass()
          baseClasses.append(cl)
        except Exception as x:
          continue

    # if there is no interface/abstract base classes, its probably not a Chain of Responsibility
    if not baseClasses:
      return None

    # checking if there is an attribute that has the base interface as a type 
    for attr in node.traverse(edge = "edkScope_HasMember", kind = "ndkAttribute", reverse = False):
      try:
        if attr.getType().getClass() in baseClasses:
          hasBaseAttr = True
      except:
        return None

    for method in node.traverse(edge = "edkScope_HasMember", kind = "ndkMethod", reverse = False):

      # searching for methods that can HANDLE the chain
      if method.getValue("methodKind") != "mekConstructor":
        if method.getValue("accessibility") == "ackPublic" and any([method.getValue("isVirtual"), method.getValue("isAbstract")]):
          for methodAccAttr in method.traverse(edge = "edkMethod_AccessesAttribute", kind = "ndkAttributeAccess"):
            for handlesAttr in methodAccAttr.traverse(edge = "edkAttributeAccess_Attribute", kind = "ndkAttribute"):
              if handlesAttr.getType().getClass() in baseClasses:
                for methodCall in method.traverse(edge = "edkMethod_Calls", kind = "ndkMethodCall"):
                  for _method in methodCall.traverse(edge = "edkMethodCall_Method", kind = "ndkMethod"):
                    if method.getValue("name") == _method.getValue("name"):
                      # collect every method that can be a "Handle"
                      handleMethodNames.append(method.getValue("name"))
                      hasRecursiveMethod = True

      # searching for a setNext method
      if method.getValue("accessibility") == "ackPublic" and any(substr in str(method.getValue("name")).lower() for substr in ["add","push","insert","emplace","set"]):
        for baseParam in method.traverse(edge = "edkMethod_HasParameter", kind = "ndkParameter"):
          try:
            if baseParam.getType().getClass() in baseClasses:
              methodHasClassParam = True
              break
          except Exception as x:
            pass
        
        # setNext accesses the attribute
        for methodAccAttr in method.traverse(edge = "edkMethod_AccessesAttribute", kind = "ndkAttributeAccess"):
          for handlesAttr in methodAccAttr.traverse(edge = "edkAttributeAccess_Attribute", kind = "ndkAttribute"):
            if handlesAttr.getType().getClass() in baseClasses:
              instanceAttrIsAccessed = True
              break

    # checking the sub classes 
    for subClass in node.getType().traverse(edge = "edkClass_IsSubclass", kind = "ndkClass", reverse = True):
      subClassNumber += 1
      subClassesCallsHandle = False
      for method in subClass.traverse(edge = "edkScope_HasMember", kind = "ndkMethod", reverse = False):
        if method.getValue("methodKind") != "mekConstructor" and method.getValue("accessibility") == "ackPublic":
          # doesnt have attribute acces edge, because it uses the attribute from base? 
          for methodCall in method.traverse(edge = "edkMethod_Calls", kind = "ndkMethodCall"):
            for _method in methodCall.traverse(edge = "edkMethodCall_Method", kind = "ndkMethod"):
              if method.getValue("name") == _method.getValue("name") and method.getValue("name") in handleMethodNames:
                subClassesCallsHandle = True

    if hasBaseAttr and methodHasClassParam and instanceAttrIsAccessed and hasRecursiveMethod and subClassesCallsHandle and subClassNumber >= 2:
      collectWarning = {"chainedDerivedClass" : []}
      for subClass in node.getType().traverse(edge = "edkClass_IsSubclass", kind = "ndkClass", reverse = True):
        collectWarning["chainedDerivedClass"].append(subClass)

      node.setWarning(children = collectWarning, patternName = name, roleName = role, priority = priority, displayName = displayName, description = description )
      return "Found py pattern on [" + str(node.getValue("id")) + "]\n"
  return None