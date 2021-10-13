name = "Poltergeists"
role = "poltergeistsClass"
kind = "ndkClass"
category = "AntiPattern"
priority = "Minor"
displayName = "Functional Decomposition"
description = "Also Known As: Gypsy , Proliferation of Classes , and Big DoIt Controller Class<br>Poltergeists are classes with limited responsibilities and roles to play in the system; therefore, their effective life cycle is quite brief. Poltergeists clutter software designs, creating unnecessary abstractions; they are excessively complex, hard to understand, and hard to maintain."

def visit(node):
  
  if node.getValue("classKind") != "clkInterface" and node.getValue("NA") == 0:
    node.setWarning(patternName = name, roleName = role, category = category, priority = priority, displayName = displayName, description = description)
    return "[Found on py " + str(node.getValue("id")) + "]\n"
  
  return None