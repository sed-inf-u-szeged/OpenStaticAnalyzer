## Reference of source code metrics

Source code metrics are used to quantify different source code characteristics. OpenStaticAnalyzer computes source code metrics for the following source code element kinds: components (e.g. modules), source files, packages, class types, methods and functions.

The calculated metrics are grouped into 6 categories, which are the following:

- **Cohesion metrics:** measure to what extent the source code elements are coherent in the system.

- **Complexity metrics:** measure the complexity of source code elements (typically algorithms).

- **Coupling metrics:** measure the amount of interdependencies of source code elements.

- **Documentation metrics:** measure the amount of comments and documentation of source code elements in the system.

- **Inheritance metrics:** measure the different aspects of the inheritance hierarchy of the system.

- **Size metrics:** measure the basic properties of the analyzed system in terms of different cardinalities (e.g. number of code lines, number of classes or methods).

In the case of the documentation metrics all the comments found immediately before a source code element are considered as its documentation, while the comments contained inside the source code element are considered as its comments.

The following table summarizes the metrics, their abbreviations and their correspondence to different source code element kinds:

  Category               Metric name                              Abbrev.   Method, Function   Class   Module   Package   File   Comp.  
  ---------------------- ---------------------------------------- -------- ------------------ ------- -------- --------- ------ ------- 
  Cohesion metrics       Lack of Cohesion in Methods 5            LCOM5                       X                                         
  Complexity metrics     McCabe's Cyclomatic Complexity           McCC     X                                             X              
                         Nesting Level                            NL       X                  X                                         
                         Nesting Level Else-If                    NLE      X                  X                                         
                         Weighted Methods per Class               WMC                         X                                         
  Coupling metrics       Coupling Between Object classes          CBO                         X                                         
                         Coupling Between Object classes Inverse  CBOI                        X                                         
                         Number of Incoming Invocations           NII      X                  X                                         
                         Number of Outgoing Invocations           NOI      X                  X                                         
                         Response set For Class                   RFC                         X                                         
  Documentation metrics  Comment Density                          CD       X                  X       X        X                        
                         Comment Lines of Code                    CLOC     X                  X       X        X         X              
                         Documentation Lines of Code              DLOC     X                  X                                         
                         Total Comment Density                    TCD      X                  X       X        X                X       
                         Total Comment Lines of Code              TCLOC    X                  X       X        X                X       
  Inheritance metrics    Depth of Inheritance Tree                DIT                         X                                         
                         Number of Ancestors                      NOA                         X                                         
                         Number of Children                       NOC                         X                                         
                         Number of Descendants                    NOD                         X                                         
                         Number of Parents                        NOP                         X                                         
  Size metrics           Lines of Code                            LOC      X                  X       X        X         X              
                         Logical Lines of Code                    LLOC     X                  X       X        X         X              
                         Number of Attributes                     NA                          X       X        X                        
                         Number of Classes                        NCL                                 X        X                        
                         Number of Local Attributes               NLA                         X                                         
                         Number of Local Methods                  NLM                         X                                         
                         Number of Methods                        NM                          X       X        X                        
                         Number of Packages                       NPKG                                         X                        
                         Number of Parameters                     NUMPAR   X                                                            
                         Number of Statements                     NOS      X                  X                          X              
                         Total Lines of Code                      TLOC     X                  X       X        X                X       
                         Total Logical Lines of Code              TLLOC    X                  X       X        X                X       
                         Total Number of Attributes               TNA                         X       X        X                X       
                         Total Number of Classes                  TNCL                                X        X                X       
                         Total Number of Directories              TNDI                                         X                X       
                         Total Number of Files                    TNFI                                         X                X       
                         Total Number of Local Attributes         TNLA                        X                                         
                         Total Number of Local Methods            TNLM                        X                                         
                         Total Number of Methods                  TNM                         X       X        X                X       
                         Total Number of Packages                 TNPKG                                        X                X       
                         Total Number of Statements               TNOS     X                  X       X        X                X       

### Cohesion metrics

#### Lack of Cohesion in Methods 5 (LCOM5) {#LCOM5}

**Class:** number of functionalities of the class. One of the basic principles of object-oriented programming is encapsulation, meaning that attributes belonging together and the operations that use them should be organized into one class, and one class shall implement only one functionality, i.e. its attributes and methods should be coherent. This metric measures the lack of cohesion and computes into how many coherent classes the class could be split. It is calculated by taking a non-directed graph, where the nodes are the implemented local methods of the class and there is an edge between the two nodes if and only if a common (local or inherited) attribute or abstract method is used or a method invokes another. The value of the metric is the number of connected components in the graph not counting those, which contain only constructors.

### Complexity metrics

#### McCabe's Cyclomatic Complexity (McCC) {#McCC}

**Method / Function:** complexity of the method/function expressed as the number of independent control flow paths in it. It represents a lower bound for the number of possible execution paths in the source code and at the same time it is an upper bound for the minimum number of test cases needed for achieving full branch test coverage. The value of the metric is calculated as the number of the following instructions plus 1: if, for, while, except and conditional expression. Moreover, logical “and” and logical “or” expressions also add 1 to the value because their short-circuit evaluation can cause branching depending on the first operand. The following instructions are not included: else, try, finally.

**File:** complexity of the file expressed as the number of independent control flow paths in it. It represents a lower bound for the number of possible execution paths in the source code and at the same time it is an upper bound for the minimum number of test cases needed for achieving full branch test coverage. The value of the metric is calculated as the number of the following instructions plus 1: if, for, while, except and conditional expression. Moreover, logical “and” and logical “or” expressions also add 1 to the value because their short-circuit evaluation can cause branching depending on the first operand. The following instructions are not included: else, try, finally.

#### Nesting Level (NL) {#NL}

**Method / Function:** complexity of the method/function expressed as the depth of the maximum embeddedness of its conditional, iteration and exception handling block scopes. The following instructions are taken into account: if, else-if, else, for, while, with, try, except, finally.

**Class:** complexity of the class expressed as the depth of the maximum embeddedness of its conditional, iteration and exception handling block scopes. It is calculated as the maximum nesting level (NL) of its local methods.

#### Nesting Level Else-If (NLE) {#NLE}

**Method / Function:** complexity of the method/function expressed as the depth of the maximum embeddedness of its conditional, iteration and exception handling block scopes, where in the if-else-if construct only the first if instruction is considered. The following instructions are taken into account: if, else, for, while, with, try, except, finally. The following instructions do not increase the value by themselves; however, if additional embeddedness can be found in their blocks, they are considered: else-if (i.e. in the if-else-if construct the use of else-if does not increase the value of the metric).

**Class:** complexity of the class expressed as the depth of the maximum embeddedness of its conditional, iteration and exception handling block scopes, where in the if-else-if construct only the first if instruction is considered. It is calculated as the maximum nesting level (NLE) of its local methods.

#### Weighted Methods per Class (WMC) {#WMC}

**Class:** complexity of the class expressed as the number of independent control flow paths in it. It is calculated as the sum of the McCabe's Cyclomatic Complexity (McCC) values of its local methods.

### Coupling metrics

#### Coupling Between Object classes (CBO) {#CBO}

**Class:** number of directly used other classes (e.g. by inheritance, function call, type reference, attribute reference). Classes using many other classes highly depend on their environment, so it is difficult to test or reuse them; furthermore, they are very sensitive to the changes in the system.

#### Coupling Between Object classes Inverse (CBOI) {#CBOI}

**Class:** number of other classes, which directly use the class. Classes which are used by many other classes have a high impact on the behavior of the system, and should be modified very carefully and tested intensively.

#### Number of Incoming Invocations (NII) {#NII}

**Method / Function:** number of other methods/functions and attribute initializations which directly call the method/function. If the method/function is invoked several times from the same method/function or attribute initialization, it is counted only once.

**Class:** number of other methods and attribute initializations which directly call the local methods of the class. If a method is invoked several times from the same method or attribute initialization, it is counted only once.

#### Number of Outgoing Invocations (NOI) {#NOI}

**Method / Function:** number of directly called methods/functions. If a method/function is invoked several times, it is counted only once.

**Class:** number of directly called methods of other classes, including method invocations from attribute initializations. If a method is invoked several times, it is counted only once.

#### Response set For Class (RFC) {#RFC}

**Class:** number of local (i.e. not inherited) methods in the class (NLM) plus the number of directly invoked other methods by its methods or attribute initializations (NOI).

### Documentation metrics

#### Comment Density (CD) {#CD}

**Method/Function:** ratio of the comment lines of the method/function (CLOC) to the sum of its comment (CLOC) and logical lines of code (LLOC).

**Class:** ratio of the comment lines of the class (CLOC) to the sum of its comment (CLOC) and logical lines of code (LLOC).

**Module:** ratio of the comment lines of the module (CLOC) to the sum of its comment (CLOC) and logical lines of code (LLOC).

#### Comment Lines of Code (CLOC) {#CLOC}

**Method/Function:** number of comment and documentation code lines of the method/function; however, its  local classes are not included.

**Class:** number of comment and documentation code lines of the class, including its local methods and attributes; however, its nested and local classes are not included.

**Module:** number of comment and documentation code lines of the module.

**File:** number of comment and documentation code lines in the file.

#### Documentation Lines of Code (DLOC) {#DLOC}

**Method/Function:** number of documentation code lines of the method/function.

**Class:** number of documentation code lines of the class, including its local methods and attributes; however, its nested and local classes are not included.

**Module:** number of documentation code lines of the modul.

#### Total Comment Density (TCD) {#TCD}

**Method/Function:** ratio of the total comment lines of the method/function (TCLOC) to the sum of its total comment (TCLOC) and total logical lines of code (TLLOC).

**Class:** ratio of the total comment lines of the class (TCLOC) to the sum of its total comment (TCLOC) and total logical lines of code (TLLOC).

**Module:** ratio of the total comment lines of the module (TCLOC) to the sum of its total comment (TCLOC) and total logical lines of code (TLLOC).

**Package:** ratio of the total comment lines of the package (TCLOC) to the sum of its total comment (TCLOC) and total logical lines of code (TLLOC).

**Component:** ratio of the total comment lines of the component (TCLOC) to the sum of its total comment (TCLOC) and total logical lines of code (TLLOC).

#### Total Comment Lines of Code (TCLOC) {#TCLOC}

**Method/Function:** number of comment and documentation code lines of the method/function, including its local classes.

**Class:** number of comment and documentation code lines of the class, including its local methods and attributes, as well as its nested and local classes.

**Module:** number of comment and documentation code lines of the module.

**Package:** number of comment and documentation code lines of the package, including its subpackages.

**Component:** number of comment and documentation code lines of the component, including its subcomponents.

### Inheritance metrics

#### Depth of Inheritance Tree (DIT) {#DIT}

**Class:** length of the path that leads from the class to its farthest ancestor in the inheritance tree.

#### Number of Ancestors (NOA) {#NOA}

**Class:** number of classes from which the class is directly or indirectly inherited.

#### Number of Children (NOC) {#NOC}

**Class:** number of classes which are directly derived from the class.

#### Number of Descendants (NOD) {#NOD}

**Class:** number of classes, which are directly or indirectly derived from the class.

#### Number of Parents (NOP) {#NOP}

**Class:** number of classes from which the class is directly inherited.

### Size metrics

#### Lines of Code (LOC) {#LOC}

**Method / Function:** number of code lines of the method/function, including empty and comment lines; however, its nested functions are not included.

**Class:** number of code lines of the class, including empty and comment lines, as well as its local methods; however, its nested and local classes are not included.

**Module:** number of code lines of the module, including empty and comment lines.

**Package:** number of code lines of the package, including empty and comment lines; however, its subpackages are not included.

**File:** number of code lines in the file, including empty and comment lines.

#### Logical Lines of Code (LLOC) {#LLOC}

**Method / Function:** number of non-empty and non-comment code lines of the method/function; however, its nested functions are not included.

**Class:** number of non-empty and non-comment code lines of the class, including the non-empty and non-comment lines of its local methods; however, its nested and local classes are not included.

**Module:** number of non-empty and non-comment code lines of the module.

**Package:** number of non-empty and non-comment code lines of the package; however, its subpackages are not included.

**File:** number of non-empty and non-comment code lines in the file.

#### Number of Attributes (NA) {#NA}

**Class:** number of attributes in the class, including the inherited ones; however, the attributes of its nested and local classes are not included.

**Module:** number of attributes in the module.

**Package:** number of attributes in the package; however, attributes of its subpackages are not included.

#### Number of Classes (NCL) {#NCL}

**Module:** number of classes in the module.

**Package:** number of classes in the package; however, the classes of its subpackages are not included.

#### Number of Local Attributes (NLA) {#NLA}

**Class:** number of local (i.e. not inherited) attributes in the class; however, the attributes of nested and local classes are not included.

#### Number of Local Methods (NLM) {#NLM}

**Class:** number of local (i.e. not inherited) methods in the class; however, the methods of nested and local classes are not included.

#### Number of Methods (NM) {#NM}

**Class:** number of methods/functions in the class, including the inherited ones; however, the methods of its nested and local classes are not included. Methods that override abstract methods are not counted.

**Module:** number of methods in the module.

**Package:** number of methods in the package; however, methods of its subpackages are not included.

#### Number of Packages (NPKG) {#NPKG}

**Package:** number of directly contained subpackages of the package.

#### Number of Parameters (NUMPAR) {#NUMPAR}

**Method / Function:** number of the parameters of the method/function. The varargs and kwargs parameters counts as one.

#### Number of Statements (NOS) {#NOS}

**Method / Function:** number of statements in the method/function; however, the statements of its nested functions are not included.

**Class:** number of statements in the class; however, the statements of its nested and local classes are not included.

**File:** number of statements in the file.

#### Total Lines of Code (TLOC) {#TLOC}

**Method / Function:** number of code lines of the method/function, including empty and comment lines, as well as its nested functions.

**Class:** number of code lines of the class, including empty and comment lines, as well as its nested and local classes.

**Module:** number of code lines of the module, including empty and comment lines.

**Package:** number of code lines of the package, including empty and comment lines, as well as its subpackages.

**Component:** number of code lines of the component, including empty and comment lines, as well as its subcomponents.

#### Total Logical Lines of Code (TLLOC) {#TLLOC}

**Method / Function:** number of non-empty and non-comment code lines of the method/function, including the non-empty and non-comment lines of its nested functions.

**Class:** number of non-empty and non-comment code lines of the class, including the non-empty and non-comment code lines of its nested and local classes.

**Module:** number of non-empty and non-comment code lines of the module.

**Package:** number of non-empty and non-comment code lines of the package, including its subpackages.

**Component:** number of non-empty and non-comment code lines of the component, including its subcomponents.

#### Total Number of Attributes (TNA) {#TNA}

**Class:** number of attributes in the class, including the inherited ones, as well as the inherited and local attributes of its nested and local classes.

**Module:** number of attributes in the module.

**Package:** number of attributes in the package, including the attributes of its subpackages.

**Component:** number of attributes in the component, including the attributes of its subcomponents.

#### Total Number of Classes (TNCL) {#TNCL}

**Module:** number of classes in the module.

**Package:** number of classes in the package, including the classes of its subpackages.

**Component:** number of classes in the component, including the classes of its subcomponents.

#### Total Number of Directories[^3] (TNDI) {#TNDI}

**Package:** number of directories that belong to the package, including the directories of its subpackages.

**Component:** number of directories that belong to the component, including its subcomponents.

#### Total Number of Files (TNFI) {#TNFI}

**Package:** number of files that belong to the package, including the files of its subpackages.

**Component:** number of files that belong to the component, including its subcomponents.

#### Total Number of Local Attributes (TNLA) {#TNLA}

**Class:** number of local (i.e. not inherited) attributes in the class, including the attributes of its nested and local classes.

#### Total Number of Local Methods (TNLM) {#TNLM}

**Class:** number of local (i.e. not inherited) methods in the class, including the local methods of its nested and local classes.

#### Total Number of Methods (TNM) {#TNM}

**Class:** number of methods/functions in the class, including the inherited ones, as well as the inherited and local methods of its nested and local classes. Methods that override abstract methods are not counted.

**Package:** number of methods in the module.

**Package:** number of methods in the package, including the methods of its subpackages.

**Component:** number of methods in the component, including the methods of its subcomponents.

#### Total Number of Packages (TNPKG) {#TNPKG}

**Package:** number of subpackages in the package, including all directly or indirectly contained subpackages.

**Component:** number of packages and subpackages that belong to the component, including its subcomponents.

#### Total Number of Statements (TNOS) {#TNOS}

**Method / Function:** number of statements in the method/function, including the statements of its nested functions.

**Class**: number of statements in the class, including the statements of its nested and local classes.

**Module:** number of statements in the module.

**Package:** number of statements in the package, including the statements of its subpackages.

**Component:** number of statements in the component, including the statements of its subcomponents.
