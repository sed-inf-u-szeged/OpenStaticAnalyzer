name = "abstractFactory"
role = "factoryClass"
kind = "ndkClass"
category = "DesignPattern"
priority = "Info"
displayName = "Abstract Factory"
description = "Provide a level of indirection that abstracts the creation of families of related or dependent objects without directly specifying their concrete classes. The \"factory\" object has the responsibility for providing creation services for the entire platform family. Clients never create platform objects directly, they ask the factory to do that for them."

def filter(_node):
    return (_node.getValue("isAbstract") or _node.getValue("classKind") == "clkInterface") and _node.getValue("NA") == 0 and _node.getValue("NM") >= 2

def visit(node):
    if filter(node):
        childCondition = 0
        abstractMethods = []

        for method in node.traverse(edge = "edkScope_HasMember", kind = "ndkMethod", reverse = False):
            if ((method.getValue("isAbstract") or method.getValue("isVirtual")) and method.getValue("accessibility") == "ackPublic"):
                childCondition += 1
                abstractMethods.append(method)

        if childCondition >= 2:
            kindOfAbstractClass = node.getType()
            derivedNumber = 0

            for subClass in kindOfAbstractClass.traverse(edge = "edkClass_IsSubclass", kind = "ndkClass", reverse = True):
                derivedNumber += 1
                # is override factory method
                subClassMethods = subClass.traverse(edge = "edkScope_HasMember", kind = "ndkMethod", reverse = False)
                for method in abstractMethods:
                    abstractMethodName = method.getValue("name")
                    condition = False
                    returnTypeIsInstance = False
                    for subMethod in subClassMethods:
                        subClassMethodName = subMethod.getValue("name")
                        # has override
                        if not condition and abstractMethodName == subClassMethodName:
                            # doesnt instintiate the return type
                            for _type in subMethod.traverse(edge = "edkMethod_Instantiates", kind = "ndkType", reverse = False) :
                                if _type.typeEquals(subMethod):
                                    return None #instintiates return type
                                try:
                                    for parentClassOfInstintiatedObj in _type.getClass().traverse(edge = "edkClass_IsSubclass", kind = "ndkType", reverse = False) :
                                        try:
                                            if parentClassOfInstintiatedObj.getClass().typeEquals(subMethod.getType().getClass()):
                                                returnTypeIsInstance = True
                                        except:
                                            pass
                                except:
                                    pass
                            condition = True
                    
                    if not condition or not returnTypeIsInstance:
                        return None

            if derivedNumber >= 2:
                node.setWarning(name, role, displayName, category, priority, description)
                return "Found py pattern on [" + str(node.getValue("id")) + "]\n"
    return None