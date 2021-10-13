#nested class inside method
def isClassNested(node):
    if node.instanceOf("ndkClass"):
        if len(node.traverse(edge = "edkScope_HasMember", kind = "ndkMethod", reverse = True)) > 0:
            return True
    return False

def getLocalMethods(node, static = False):
    retArr = []
    if node.instanceOf("ndkClass"):
        for _methodNode in node.traverse(edge = "edkScope_HasMember", kind = "ndkMethod", reverse = False):
            if _methodNode.getValue("isStatic") == static:
                retArr.append(_methodNode)
    return retArr

def isStatic(node):
    return node.getValue("isStatic")

def foundStr(name, node):
    return f'Found pattern "{name}" on L{node.getValue("id")}\n'