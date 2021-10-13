#Bridge description:
# 1) The node we trything to find is a class, if its an interface/abstract, it must have 2 class that inherits it, if its a regular class then it must have 1 class that inherits it, and must have:
#   1.1) A protected attribute, its type is an interface/abstract (not self)
#   1.2) Only 1 method besides constructors/destructors, has to be virtual/abstract and must use the attribute described in 1.1
#   1.3) A contructor that has a same paramater as 1.1 attribute has
#   1.4) The attribute's type, must be a class that is interface/abstract:
#       1.4.1) inherited 2+ times
#       1.4.2) 1+ virtual/abstract method

kind = "ndkClass"
name = "Bridge"
roleName = "bridgeClass"
priority = "Info"
category = "DesignPattern"
displayName = name
description = "Bridge is a structural design pattern that divides business logic or huge class into separate class hierarchies that can be developed independently."

def filter(_node):
    return _node.getValue("NA") >= 1 and _node.getValue("NM") >= 2

def visit(node):
    if filter(node):
        attrTypes = []
        abstractNodeNumbers = 0
        ctorAccessesAttr = False
        numberOfMethodBesideCtor = 0
        impCond = dict()

        # 1)
        if not node.getValue("isAbstract") and node.getValue("classKind") == "clkClass":
            abstractNodeNumbers = 1
        abstractNodeNumbers += len(node.getType().traverse(edge = "edkClass_IsSubclass", kind = "ndkClass", reverse = True))

        # 1.1)
        for attr in node.traverse(edge = "edkScope_HasMember", kind = "ndkAttribute", reverse = False):
            if attr.getValue("accessibility") == "ackProtected":
                # unknon cases
                try:
                    parentClass = attr.getType().getClass() # ndkType 
                except Exception as x:
                    print(x, node)
                    continue

                if parentClass.getValue("classKind") == "clkInterface" or parentClass.getValue("isAbstract") or parentClass.getValue("isVirtual"):
                    _type = parentClass.getType()
                    attrTypes.append(_type)
                    impCond[parentClass.getValue("name")] = dict()
                    impCond[parentClass.getValue("name")]["numberOfDesc"] = len(_type.traverse(edge = "edkClass_IsSubclass", kind = "ndkClass", reverse = True))
                    impCond[parentClass.getValue("name")]["atleastOneVirtualMethod"] = False
                    # 1.4.1)
                    for methodInSubClass in parentClass.traverse(edge = "edkScope_HasMember", kind = "ndkMethod", reverse = False):
                        # 1.4.2)
                        if methodInSubClass.getValue("isAbstract") or methodInSubClass.getValue("isVirtual"):
                            impCond[parentClass.getValue("name")]["atleastOneVirtualMethod"] = True
        
        for method in node.traverse(edge = "edkScope_HasMember", kind = "ndkMethod", reverse = False):
            # 1.3)
            if method.getValue("methodKind") == "mekConstructor":
                for parameter in method.traverse(edge = "edkMethod_HasParameter", kind = "ndkParameter", reverse = False):
                    try:
                        if parameter.getType().getClass().getType() in attrTypes:
                            for accAttr in method.traverse(edge = "edkMethod_AccessesAttribute", kind = "ndkAttributeAccess", reverse = False):
                                for attrAccAttr in accAttr.traverse(edge = "edkAttributeAccess_Attribute", kind = "ndkAttribute", reverse = False):
                                    if parameter.getType() == attrAccAttr.getType():
                                        ctorAccessesAttr = True
                    except Exception as x:
                        continue
            # 1.2)
            elif method.getValue("methodKind") == "mekNormal":
                numberOfMethodBesideCtor += 1


        _impCond = True
        for temp in impCond:
            if (_impCond and (impCond[temp]["numberOfDesc"] == 0 or not impCond[temp]["atleastOneVirtualMethod"])):
                _impCond = False

        if _impCond and ctorAccessesAttr and numberOfMethodBesideCtor == 1 and abstractNodeNumbers >= 2:
            node.setWarning(patternName = name, roleName = roleName, displayName = displayName, category = category, priority = priority, description = description)
            return "[Found on py '" + str(node.getValue("id")) + "']\n"
    return None