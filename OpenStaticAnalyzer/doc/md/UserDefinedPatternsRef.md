## The UserDefinedPatterns module

As opposed to the UserDefinedMetrics module, where extra values could be calculated from already existing metrics, this module offers a way to tag source code elements (or a constellation of source code elements) that satisfy a certain set of arbitrary criteria.
The use originally intended for this module is matching object-oriented design pattern and antipattern instances -- but it can be used for discovering (or enforcing) any occurrence that can be expressed through the Language Independent Model the toolchain uses under the hood.
Example pattern configurations for the most widespread design- and antipatterns can be found in `(Windows/Linux)Tools/Patterns`.

### Usage

The module can be activated with a single extra switch (`-pattern=value`) to the toolchain.
It can either be a single pattern, or a folder containing multiple patterns.
Patterns can either be declarative (.yaml, .xml, or .json files), or procedural (.py python scripts), and in the case of folders, can be mixed arbitrarily.
The declarative way is easier and possibly drier than writing code, so this is the primary entry point for users wishing to express a pattern
It has its limitations, though, as the low-level formulas that do the actual matching can only use data that already exists in the model.

If a pattern needs extra calculations on the fly, it can use the procedural interface, and with it the full expressive capabilities of the python language.
A binding interface is provided so that the python code can interact with the source code elements being visited so that it can calculate its own intermediary values and evaluate its own criteria.
The binding also makes it possible for the pattern code to publish new values to the graph, as well as the main matches -- thereby covering the expressive capabilities of the UserDefinedMetrics tool as well.

### An example pattern

To get an idea how the two methods work, let's consider an example first.
If we wanted to discover instances of the [Singleton](https://refactoring.guru/design-patterns/singleton) design pattern, we could phrase our requirements along the lines of:

- A class with only non-public constructors.
- A private static member attribute whose type is the class itself.
- A public static member function whose return type is the class itself.

When a class satisfying all these conditions is found, we expect an output like the following:

```txt
Pattern 'Singleton' has been found on 'SingletonExample'
Source : path/to/file.cpp [8,39,5,6]
Role 'SingletonClass' fits on 'SingletonExample' (nodeid '107'), path/to/file.cpp [8,39,5,6]
```

Additionally, this information would be tagged on the appropriate graph node, and be a part of the official output of the toolchain.
Since the requirements of the Singleton pattern are relatively simple, we can start with the declarative method.

### The declarative method


A usual pattern description consists of some metadata (pattern name, what kind of source code element we're looking for, what it is called within the pattern, etc.) and then a set of conditions we want to check.
These conditions can be:

- Formulas, that are checked against the node in question.
- Context switches, where we can travel from the current node to another by the edges defined in the LIM model. For this, we can specify the edge to travel, the direction to travel in, the kinds of nodes we want to enumerate on the other end, what name we want to refer to these end nodes, and some nested conditions we want to match against them.
- Logical combinations, as in "and", "or", etc., where we can combine multiple formulas or context switches.

The best way to dive into the language is through an example.
We could use either yaml, xml, or json, but yaml will be considered the default from now on.
So, following the above guidelines, the Singleton description (with some additional, verbose annotation) would look something like this:

```yaml
# we start by specifying the relevant metadata
# the names `name`, `kind`, `role`, etc. 
# are all keywords so matches can automatically have their metadata added to them in the graph
name : Singleton
kind : ndkClass
role : SingletonClass
category: DesignPattern
priority: Info
description: >
  Application needs one, and only one, instance of an object.
  Additionally, lazy initialization and global access are necessary.
displayName: Singleton

# and then move on to the conditions we want to match
conditions:

  # 1, the "instance" condition, where we check that the class has a private static attribute whose type is the class itself
  # 2, this is implemented using a context switch to the class' member attributes, and then 3 nested conditions to check if 
  #    the attribute is private, static, and matches the type of the class
  # 3, the context switch is an `any`, since we're already happy if at least one attribute satisfies our nested conditions 
  #    -- but we could also use the other two context switches, `all` and `exists`
  # 4, everything we name in the `role` clause can then be used as a variable in any further condition
  # 5, note that `accessibility` and `isStatic` are built-in node characteristics from LIM, and ndkAttribute/ackPrivate 
  #    are LIM constants
  # 6, to help bridge the divide between the logical and type hierarchies, we can refer to a node's type using the 
  #    "node.type" shorthand
  - any :
      direction : forward
      edge : edkScope_HasMember
      kind : ndkAttribute
      role : attr1* # the trailing asterisk means that we don't want to include this attribute among the results
      conditions :
        - accessibility == ackPrivate
        - isStatic == true
        - type == SingletonClass.type
  # the "getInstance" condition, where we check that the class has a public static method that returns the class type
  # implementation is nearly identical to the above, only now we check ndkMethods instead of ndkAttributes
  # the `filter` clause pre-filters which nodes the subsequent conditions apply to -- in this case, 
  # we are only looking for a normal method (so, not a constructor or destructor)
  - any :
      direction : forward
      edge : edkScope_HasMember
      type : ndkMethod
      role : m1*
      filters:
        - methodKind == mekNormal
      conditions :
        - isStatic == true
        - accessibility == ackPublic
        - returnType == SingletonClass.type
  # and finally the "constructor" condition, where we check that none of the class' contructors are public
  # here we use the `all` context switch because we need to make sure that all constructors match our non-public requirement
  # we also encounter the `or` combination condition to round out condition kinds (the others are `and`, and `not`)
  - all :
      direction : forward
      edge : edkScope_HasMember
      kind : ndkMethod
      role : m2*
      filters:
        - methodKind == mekConstructor
      conditions:
        - or :
          - accessibility == ackPrivate
          - accessibility == ackProtected
  # multiple conditions inside a `conditions` clause are implicitly joined by `and`, so all three of the above conditions 
  # must be met for a class to be considered an instance of the Singleton pattern
```

With the mixture of formulas, context switches, and logical combinations, many patterns can be described.


### Declarative reference

The basic analysis procedure usually leads to the following artifacts (among others) in increasing abstraction: Source code, language-specific model (ASG), language-independent model (LIM), result graph (graph).
Since we are in language-independent territory here, the ASG does not concern us; but both the LIM and the graph are worth becoming familiar with, to help us fully utilize the capabilities of the pattern matching process.

LIM can be mostly thought of as the Object-oriented design level view of the whole system.
It contains packages, classes, methods, attributes, and appropriate connections (edges) among these (for a full list of nodes and edges, please refer to the LIM introduction).
It is a "lossy" conversion from the ASG, as the internals of the methods (so every statement, expression, local variable, etc.) is lost.
But the overall structure remains, which is the important part for pattern detection.

The graph, on the other hand, is the result structure (the main output, so to speak) of the analysis process.
It contains not only the corresponding nodes from the LIM, but also computed values like numeric metrics, source code position-based warnings, and other metadata to facilitate its many visual representations later.
Pattern matches we discover also go onto the graph in the form of positioned warnings (possibly spanning across multiple nodes if the pattern has multiple roles).
Additionally, we can use the graph as an "input" as well, and incorporate previously calculated values into the formulas of our pattern matching.

With this in mind, let's see what the declarative method can offer us:

#### Metadata reference:

- `name` (**required**) : The name of the pattern, its value is scalar (string/text).
- `kind` (**required**) : The kind of the LIM node where the pattern matching begins, its value is scalar (string/text), refer to LIM's `NodeKind`.
- `role` (**required**) : The name of the matched pattern on the given node, its value is scalar (string/text).
- `category` : Metadata for generating a rule for the pattern on the Graph, its value is scalar (string/text) \[**DesignPattern**/**AntiPattern**/**CustomPatternName**\]. By default its value is **DesignPattern**.
- `priority` : Metadata for generating a rule for the pattern on the Graph, its value is scalar (string/text) \[**Info**, **Minor**, **Major**, **Critical**, **Blocker**\]. By default its value is **Info**.
- `description` : Metadata for generating a rule for the pattern on the Graph. The description of the pattern.
- `displayName` : Metadata for generating a rule for the pattern on the Graph. The name of the pattern that will be visible in 3rd party programs.
- `filters` : Its value is a sequence, each entry is a condition. It filters the node, and only checks the conditions if the node satisfies the conditions described by the filter.
- `conditions` : Its value is a sequence, each entry is a condition. If this is not defined, the pattern matching will return true by default.

#### Context switches:

- `all`/`any` : Pattern matching returns true, if all/any of the conditions are matching, its values are maps (key/value pairs): 
  - `direction` : Sets the direction of the visiting, its value is scalar (string/text) \[**forward**, **reverse**\]. By default its value is **forward**.
  - `from` : The starting node of the visiting, its value is scalar (string/text), can contain a roleName or/and class/type/parent hierarchy helpers (e.g., `from : myRoleName.parent.type`). By default its value is **this** (current node)
  - `edge` (**required**) : The name of the edge, its value is scalar (string/text), refer to LIM's `EdgeKind`.
  - `kind` (**required**) : The kind of the LIM node where the pattern matching begins, its value is scalar (string/text), refer to LIM's `NodeKind`.
  - `role` (**required**) : The name of the matched pattern on the given node, its value is scalar (string/text).
  - `filters` (not-required)
  - `conditions` (not-required)

#### Logical combinations:

- `or` : Its value is a sequence, each entry is a condition (or a hierarchy switch). Returns true if any condition under it returns true.
- `and` : Its value is a sequence, each entry is a condition (or a hierarchy switch). Returns true if every condition under it returns true.
- `xor` : Its value is a sequence, each entry is a condition (or a hierarchy switch). Returns true if the number of true conditions under it is an odd number.
- `not` : Negate a single condition
- `nor` : Like "or" but negated
- `nand` : Like "and" but negated
- `exists` : Its values are maps (key/value pairs), checks whether the given edge exists on the given node or not:
  - `direction` : Sets the direction of the visiting, its value is scalar (string/text) \[**forward**, **reverse**\]. By default its value is **forward**.
  - `from` : The starting node of the visiting, its value is scalar (string/text), can contain a roleName or/and class/type/parent hierarchy helpers (eg., `from : myRoleName.parent.type`). By default its value is **this** (current node)
  - `edge` (**required**) : The name of the edge, its value is scalar (string/text), refer to LIM's `EdgeKind`.


#### List of exact formula capabilities
  
Any value that is available on the Graph. Refer to the whole documentation for what various tools output to the graph, and how. We recommend looking into the [Source Code Metrics](#reference-of-source-code-metrics) first.
Referable LIM values:

Reference name   Return type    FileSystem   File   Package   Component   Scope   Class   Attribute   Method   Parameter   Type   Every Node  Description  
---------------- ------------- ------------ ------ --------- ----------- ------- ------- ----------- -------- ----------- ------ ------------ -----------------------------------------------------------------------------
id               int                                                                                                              X           Returns the ID of the node as a number
parameterSize    int                                                                                  X                                       Returns the number of parameter the method has
isStatic         bool                               X                     X       X       X           X                                       Returns true/false if the LIM node is static
isVirtual        bool                                                                                 X                                       Returns true/false if the LIM node is virtual
isAbstract       bool                                                             X                   X                                       Returns true/false if the LIM node is abstract
isAnonymous      bool                               X                     X       X                   X                                       Returns true/false if the LIM node is anonymous
accessibility    string                             X                     X       X       X           X                                       Returns the accessibility `AccessibilityKind` as a text
classKind        string                                                           X                                                           Returns the kind of a class `ClassKind` as a text
methodKind       string                                                                               X                                       Returns the kind of a method `MethodKind` as a text
name             string         X            X      X         X           X       X       X           X        X                              Returns the name of the node as a text
kind             string                                                                                                           X           Returns the kind of a node `NodeKind` as a text                       
paramKind        string                                                                                        X                              Returns the kind of a parameter `ParameterKind` as a text   
simpleTypeKind   string                                                                                                    X                  Returns the type of a simpleKind `SimpleTypeKind` as a text  
pointerKind      string                                                                                                    X                  Returns the kind of a `PointerKind` as a text    
returnType       LIM::Node                                                                            X                                       A logical::Type node of the method returns
type             LIM::Node                                                        X       X           X        X                              A logical::Type node
class            LIM::Node                                                                                                 X                  A logical::Class node
parent           LIM::Node                                                        X       X           X        X                              A logical::... node of the parent

With these values, arbitrary expressions can be created using basic arithmetic operators (`+`, `-`, `*`, `/`) and boolean comparisons (`==`, `!=`, `~=`, `>`, `>=`, `<`, `<=`).


#### Commonly used context switches

- `edkScope_HasMember` : from classes to member methods/attributes (and back).
- `edkClass_IsSubclass` : from classes to their descendants (and back).
- `edkMethod_HasParameter` : from methods to their parameters (and back).
- ...for a complete list, refer to the LIM introduction post.




### A more complex pattern

There can be instances, however, where the declarative method is just not expressive enough.
For example, when we need more complex combinations than "any" or "all".
Or when a temporary value needs to be computed before a condition could be evaluated.

An example taking advantage of this increased expressive power is the [Feature Envy](https://refactoring.guru/smells/feature-envy) antipattern, where our match requirement can be summarized like the following:

- First, we need to calculate the occurrences of local and foreign attribute accesses.
- Then the condition is to check whether there are "enough" attribute accesses, and if so, whether the percentage of foreign accesses is above a certain threshold.




### The procedural method

For these cases, there's also a python binding for the whole pattern matching process, where a custom python script can access the source code elements through a standardized node interface.
This interface provides ways to read the same values, to switch contexts through the same edges, or to manually place pattern matches on the graph.
But on top of this, it also provides free reign to calculate arbitrary values, iterate subsets, perform conditional execution, etc.
A script for Feature Envy would look something like this:

```python
# the same metadata, only now in the form of "global" variables
name = "featureEnvy"
role = "envyMethod"
kind = "ndkMethod"
priority = "Minor"
category = "AntiPattern"
displayName = "Feature Envy"
description = "A method accesses the data of another object more than its own data."

# the `visit` method is the entry point for the pattern matching, which is called for each node of the appropriate type
# nodes here are of a special NodeBinding type that allows python access to everything we've seen from the declarative section
# only now, we can use that data to perform arbitrary calculations
def visit(node):
 parent = node.getParent()
 localAccess = 0
 foreignAccess = 0
 # context switches are now done using the `traverse` method
 for methodAccAttr in node.traverse(edge = "edkMethod_AccessesAttribute", reverse = False):
  for attrAccAttr in methodAccAttr.traverse(edge = "edkAttributeAccess_Attribute", reverse = False):
   for methodUsesThisClass in attrAccAttr.traverse(edge = "edkScope_HasMember", nodeKind = "ndkClass", reverse = True):
    # but once the destination is reached, we can increment counters
    if parent == methodUsesThisClass:
     localAccess += 1
    else:
     foreignAccess += 1
    
  # if the number of attribute accesses surpasses a certain limit (5, in this case), and at least 80% of those were 
  # directed towards a foreign attribute, we officially call the class "envious"
  if (localAccess + foreignAccess >= 5) and (foreignAccess / (foreignAccess + localAccess) >= 0.8) :
    node.setWarning(
     patternName = name, 
     roleName = role, 
     category = category, 
     description = description, 
     displayName = displayName, 
     priority = priority
    )
```

Of course, anything that could be done with the declarative method can also be done using the procedural method.
As an illustration, the Singleton pattern from above could be rewritten like so:

```python
name = "Singleton"
role = "Singleton"
kind = "ndkClass"
category = "DesignPattern"
priority = "Info"
description = """Application needs one, and only one, instance of an object. Additionally, 
                 lazy initialization and global access are necessary."""
displayName = "Singleton"

def visit(node):

 hasInstance = False
 for attr1 in node.traverse("edkScope_HasMember", nodeKind = "ndkAttribute"):
  if (
    attr1.getValue("accessibility") == "ackPrivate" and 
    attr1.getValue("isStatic") == True and 
    attr1.type_equals(node)
   ):
   hasInstance = True
   break

 getInstance = False
 for m1 in node.traverse("edkScope_HasMember", nodeKind = "ndkMethod"):
  if (
    m1.getValue("methodKind") == "mekNormal" and 
    m1.getValue("accessibility") == "ackPublic" and 
    m1.getValue("isStatic") == True and 
    m1.type_equals(node)
   ):
   getInstance = True
   break

 constr = True
 for m2 in node.traverse("edkScope_HasMember", nodeKind = "ndkMethod"):
  if m2.getValue("methodKind") != "mekConstructor": continue
  if m2.getValue("accessibility") == "ackPublic":
   constr = False
   break

 if hasInstance and getInstance and constr:
  node.setWarning(name, role, displayName, category, priority, description)
```



### Procedural reference

There are two distinguished top-level names for pattern-matching python scripts:

1. `kind`: which is the same as the top-level `kind` attribute was for the declarative method, namely it pre-filters the node kinds being visited when checking for this pattern.
2. `visit`: which is the entry point for the evaluation of each (appropriate) source code node in the input program. Its only parameter is the node currently being visited, in the form of a `NodeBinding` object, described below. Optionally, any value returned from this visit function (while otherwise ignored) will be logged to the standard output for debugging purposes.

The `NodeBinding` objects can be interacted with using the following methods:

- `getValue(name)`: the main way to read data from the current node. First, it looks for distinguished keywords (please refer to the declarative method for a complete list), and if it can't find the reference there, it looks for an arbitrary Graph node attribute with the same name. This method can therefore be used to retrieve both LIM and Graph values.
- `setMetric(name, value)`: the pair of `getValue`, only it writes data instead of retrieving it. It is important to note, though, that it cannot alter any LIM-related data, and can only set attributes in the Graph.
- `getType()` / `getClass()` / `getParent()`: the same bridge between the logical and type hierarchies that was provided as `.type`, `.class` and `.parent` in the declarative method. Returns another `NodeBinding` referring to the starting node's type / class / parent, respectively.
- `traverse(edge, kind, reverse=False)`: performs the previously mentioned context switches between nodes by traversing specific edges. `kind` can be specified if we only want to traverse those kinds of nodes on the other end of the given edges. `reverse` reverses the direction of the edge traversal, listing the nodes that point to this node by the given edge, not the nodes this node points to.
- `typeEquals(other)` / `typeSimilar(other)`: performs type-related checks. `typeEquals` is true only if the current node's type and the type of the `other` parameter are the same, while `typeSimilar` is also true if they have some heuristic-based connection. For example, if one is a custom class, and the other is a list containing custom class instances.
- equality / inequality checks are overridden for `NodeBindings`, so identity checks can be performed using the usual `==` and `!=` operators.
- `setWarning(name, role, displayName, category, priority, description, children)`: sets match results on the Graph. `name`, `role`, `displayName`, `category`, `priority`, and `description` are just the usual metadata accompanying the match, while `children` is an optional python `dict` containing the sub-roles of the pattern.

For an example of sub-roles, consider the [Composite](https://sourcemaking.com/design_patterns/composite) pattern, where we might want to indicate the Component and Leaf participants of the pattern as well. In this case, we might call `setWarning` something like this:

```python
node.setWarning('Composite', 'Composite', 'Composite', 'DesignPattern', 'Minor', 'lorem ipsum', {
  'Component': component_node,
  'Leaf': [leaf_node_1, leaf_node_2]
})
```

According to the above, sub-roles can be individual nodes or node lists, which will refer back to the original pattern match.

### Predefined Design patterns

The OpenStaticAnalyzer tool comes with a catalogue of predefined design patterns, listed below.

#### [**Abstract Factory**](https://sourcemaking.com/design_patterns/abstract_factory)
A pattern that provides an interface for creating families of related or dependent objects without specifying their concrete classes. 

**Interpreted as**: a stateless abstract class with at least two abstract methods, both of which return an abstract type. Furthermore, we check the existence of at least two derived classes that implement those two abstract methods of the base class, and instantiate concrete objects *derived* from original return types. The former condition (two or more abstract methods) refers to the "families of related objects" part, while the latter (instantiation of derived objects instead of the original return values) is the characteristic of factories.

#### [**Adapter**](https://sourcemaking.com/design_patterns/adapter)
A pattern acting as a wrapper between two objects, catching calls for one object and transforming them to a format and interface recognizable by the second object. 

**Interpreted as**: a class that meets all three of the following conditions:

  - it implements an interface (showing that it is trying to adapt *to* something),
  - it contains a class-type attribute that does **not** implement the same interface (showing that it is trying to adapt *from* something), and
  - it has a constructor with the adaptee's type (showing that it is created by wrapping something).

#### [**Bridge**](https://sourcemaking.com/design_patterns/bridge)
A pattern that decouples an abstraction from its implementation so that the two can vary independently. It represents the connection of two different inheritance hierarchies through composition.

**Interpreted as**: the head of the first class hierarchy (so at least two child classes for interfaces, or one child for instantiable classes), where:

  - it has a private attribute referencing the head of the second, different hierarchy (again, with at least two child classes for interfaces, or one child for instantiable classes), and
  - a contructor and at least one "normal" method that uses this attribute.

#### [**Builder**](https://sourcemaking.com/design_patterns/builder)
A pattern that separates the construction of a complex object from its representation so that the same construction process can create different representations. 

**Interpreted as**: an abstract class that meets all of the following conditions:

  - doesn't have any attributes,
  - has at least two abstract methods,
  - has at least one child class containing a "build" method (that returns a private attribute) and "reset" method (whose name is checked semantically), and
  - is used in a "Director" class, where
    - it's a private attribute,
    - used by at least two different methods, and
    - the different methods access it a different amount of times.


#### [**Chain of Responsibility**](https://sourcemaking.com/design_patterns/chain_of_responsibility)
A pattern that makes it possible to avoid coupling the sender of a request to its receiver by giving more than one object a chance to handle the request. It "chains" the receiving objects and passes the request along the chain until an object handles it.

**Interpreted as**: an abstact class that satisfies all of the following conditions:

  - contains a private attribute with its own type (referring to the next handler in the chain),
  - has a setter for this attribute,
  - can recursively call itself on this private attribute, and
  - it has at least two child classes that override the specific handling logic.

#### [**Composite**](https://sourcemaking.com/design_patterns/composite)
A pattern that composes objects into tree structures to represent whole-part hierarchies. Composite lets clients treat individual objects and compositions of objects uniformly.

**Interpreted as**: an abstract class or interface (called Component) that has multiple child classes, at least one of which contains a private attribute of the Component's type.

<!-- missing, TODO!
- [**Factory Method**](https://sourcemaking.com/design_patterns/factory_method)
a pattern that defines an interface for creating an object, but lets subclasses decide which concrete class to instantiate. Factory Method lets a class defer instantiation to subclasses. 

  **Interpreted as**: TODO. -->

#### [**Object Pool**](https://sourcemaking.com/design_patterns/object_pool)
A pattern that can offer a significant performance boost in situations where 1) the cost of initializing a class instance is high, 2) the rate of instantiation of a class is high, and 3) the number of instantiations in use at any one time is low. It achieves this by maintaining a limited pool of reusable instances.

  **Interpreted as**: a class that satisfies all of the following conditions:

  - has at least one attribute (referencing the object pool itself),
  - all of its attributes are private (so that we're forced to use the sharing interface),
  - has at least five methods (related to the getting/releasing/capacity settings of the pool),
  - and extends the Singleton requirements (private constructor, public static instance getter).

#### [**Prototype**](https://sourcemaking.com/design_patterns/prototype)
A pattern that specifies the kinds of objects to create by using a prototypical instance, and creates new objects by copying this prototype.

  **Interpreted as**: a class that has a virtual cloning/copying method (according to its naming convention) that returns its own type, and at least one child class that overrides this method with a covariant return type.

#### [**Singleton**](https://sourcemaking.com/design_patterns/singleton)
A pattern that ensures that a class has only one instance, and provides a global point of access to it, thereby achieving lazy (or "just-in-time") initialization.

  **Interpreted as**: a class that safisfies all three of the following conditions:

  - it only has private constructors, thereby making it impossible for users to instantiate normally,
  - it has a private, static field of its own type (supposedly containing the single instance everyone shares), and
  - it has a public, static getter method that accesses the instance attribute and returns its type.

### Predefined Anti patterns

The OpenStaticAnalyzer tool comes with a catalogue of predefined antipatterns, listed below.

#### [**Feature Envy**](https://sourcemaking.com/refactoring/smells/feature-envy)
Happens when a method accesses the data of another object more than its own data.

  **Interpreted as**: a class that accesses at least 5 attributes, and the ratio of foreign attributes among these (as opposed to local ones) exceeds 80%.

<!-- currently disabled
#### [**Lava Flow**](https://sourcemaking.com/antipatterns/lava-flow)
dead code and forgotten design information that is frozen in an ever-changing design. This is analogous to a Lava Flow with hardening globules of rocky material. The refactored solution includes a configuration management process that eliminates dead code and evolves or refactors design toward increasing quality.

  **Interpreted as**: a class that has statically unreferenced methods or attributes.
-->

<!-- currently disabled
#### [**Lazy Class**](https://sourcemaking.com/refactoring/smells/lazy-class)
A class that is (or became) too small and inactive to merit the attention and maintenance energy it demands simply by existing. Usually, its only functionality is delegating tasks to other classes.

  **Interpreted as**: a class whose CBO metric is at least 5 (signaling that it is tightly coupled to many classes) and whose WMC metric is at most 10 (signaling that it doesn't perform any complex logic itself).
-->

#### [**Long Method**](https://sourcemaking.com/refactoring/smells/long-method)
A method that contains too many lines of code or is too complex (and therefore should be broken up into more manageable pieces).

  **Interpreted as**: a function or method where either of the following three conditions are met:

  - logical lines of code exceed 80,
  - number of statements exceeds 80, or
  - the McCabe complexity exceeds 10.

#### [**Long Parameter List**](https://sourcemaking.com/refactoring/smells/long-parameter-list)
A method that has too many parameters, usually signaling that multiple algorithms have been merged, or that subsets of the parameter list should be encapsulated into their own class.

  **Interpreted as**: a method that has more than 6 parameters.

<!-- currently disabled
#### [**Poltergeist**](https://sourcemaking.com/antipatterns/poltergeists)
a class with limited responsibilities and roles to play in the system. Poltergeists clutter software designs, creating unnecessary abstractions; they are excessively complex, hard to understand, and hard to maintain. They usually manifest by just calling other class' functionalities without representing a standalone object themselves.

  **Interpreted as**: A non-interface class that does not have any attributes.
-->

#### [**Refused Bequest**](https://sourcemaking.com/refactoring/smells/refused-bequest)
Happens when a subclass uses only some of the methods and properties it inherited from its parents, which usually signals that inheritance was the incorrect choice of code reuse (and should be replaced with delegation).

  **Interpreted as**: A class that inherits protected attributes or methods that it doesn't ever access.

#### [**Shotgun Surgery**](https://sourcemaking.com/refactoring/smells/shotgun-surgery)
Happens when making any functionally coherent modification requires that developers make many small changes to many different classes. Usually signals that the class(es) implementing the feature are too closely coupled to other parts of the system.

  **Interpreted as**: A method that has more than 10 incoming invocation.

<!-- currently disabled
#### [**Temporary Field**](https://sourcemaking.com/refactoring/smells/temporary-field)
A data field (or attribute) that gets a value (and is needed) only under certain circumstances. Outside of these circumstances, it is empty, which usually means that it should be a parameter of the algorithm actually using it.

  **Interpreted as**: an attribute that's used by less than 10% of the class' methods.
-->

#### [**The Blob**](https://sourcemaking.com/antipatterns/the-blob)
Also known as God Class or Large Class Code, the blob is a class that monopolizes the processing, while other classes primarily encapsulate data only. It is a thin layer of object orientation to hide a design philosophy that is essentially still procedural.

  **Interpreted as**: a class where:

  - the combined number of methods and attributes exceeds 60, or
  - the logical lines of source code exceed 1000.
