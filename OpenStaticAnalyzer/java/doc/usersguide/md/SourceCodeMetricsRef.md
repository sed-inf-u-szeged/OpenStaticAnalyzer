## Reference of source code metrics

Source code metrics are used to quantify different source code characteristics. OpenStaticAnalyzer computes source code metrics for the following source code element kinds: components (e.g. archives), source files, packages, class types (including classes, interfaces, enums and annotations) and methods.

The calculated metrics are grouped into 6 categories, which are the following:

- **Cohesion metrics:** measure to what extent the source code elements are coherent in the system.

- **Complexity metrics:** measure the complexity of source code elements (typically algorithms).

- **Coupling metrics:** measure the amount of interdependencies of source code elements.

- **Documentation metrics:** measure the amount of comments and documentation of source code elements in the system.

- **Inheritance metrics:** measure the different aspects of the inheritance hierarchy of the system.

- **Size metrics:** measure the basic properties of the analyzed system in terms of different cardinalities (e.g. number of code lines, number of classes or methods).

In the case of the documentation metrics all the comments found immediately before a source code element are considered as its documentation, while the comments contained inside the source code element are considered as its comments.

The following table summarizes the metrics, their abbreviations and their correspondence to different source code element kinds:

  Category               Metric name                                  Abbreviation   Annotation   Class   Component   Enum   File   Interface   Method   Package 
  ---------------------- -------------------------------------------- ------------- ------------ ------- ----------- ------ ------ ----------- -------- ---------
  Cohesion metrics       Lack of Cohesion in Methods 5                LCOM5         X            X                   X             X                             
  Complexity metrics     Halstead Calculated Program Length           HCPL                                                                     X                 
                         Halstead Difficulty                          HDIF                                                                     X                 
                         Halstead Effort                              HEFF                                                                     X                 
                         Halstead Number of Delivered Bugs            HNDB                                                                     X                 
                         Halstead Program Length                      HPL                                                                      X                 
                         Halstead Program Vocabulary                  HPV                                                                      X                 
                         Halstead Time Required to Program            HTRP                                                                     X                 
                         Halstead Volume                              HVOL                                                                     X                 
                         Maintainability Index (Microsoft version)    MIMS                                                                     X                 
                         Maintainability Index (Original version)     MI                                                                       X                 
                         Maintainability Index (SEI version)          MISEI                                                                    X                 
                         Maintainability Index (OpenStaticAnalyzer version)  MISM                                                                     X                 
                         McCabe's Cyclomatic Complexity               McCC                                                  X                  X                 
                         Nesting Level                                NL            X            X                   X             X           X                 
                         Nesting Level Else-If                        NLE           X            X                   X             X           X                 
                         Weighted Methods per Class                   WMC           X            X                   X             X                             
  Coupling metrics       Coupling Between Object classes              CBO           X            X                   X             X                             
                         Coupling Between Object classes Inverse      CBOI          X            X                   X             X                             
                         Number of Incoming Invocations               NII           X            X                   X             X           X                 
                         Number of Outgoing Invocations               NOI           X            X                   X             X           X                 
                         Response set For Class                       RFC           X            X                   X             X                             
  Documentation metrics  API Documentation                            AD            X            X                   X             X                    X        
                         Comment Density                              CD            X            X                   X             X           X        X        
                         Comment Lines of Code                        CLOC          X            X                   X      X      X           X        X        
                         Documentation Lines of Code                  DLOC          X            X                   X             X           X                 
                         Public Documented API                        PDA           X            X                   X      X      X                    X        
                         Public Undocumented API                      PUA           X            X                   X      X      X                    X        
                         Total API Documentation                      TAD                                X                                              X        
                         Total Comment Density                        TCD           X            X       X           X             X           X        X        
                         Total Comment Lines of Code                  TCLOC         X            X       X           X             X           X        X        
                         Total Public Documented API                  TPDA                               X                                              X        
                         Total Public Undocumented API                TPUA                               X                                              X        
  Inheritance metrics    Depth of Inheritance Tree                    DIT           X            X                   X             X                             
                         Number of Ancestors                          NOA           X            X                   X             X                             
                         Number of Children                           NOC           X            X                   X             X                             
                         Number of Descendants                        NOD           X            X                   X             X                             
                         Number of Parents                            NOP           X            X                   X             X                             
  Size metrics           Lines of Code                                LOC           X            X                   X      X      X           X        X        
                         Logical Lines of Code                        LLOC          X            X                   X      X      X           X        X        
                         Number of Attributes                         NA            X            X                   X             X                    X        
                         Number of Classes                            NCL                                                                               X        
                         Number of Enums                              NEN                                                                               X        
                         Number of Getters                            NG            X            X                   X             X                    X        
                         Number of Interfaces                         NIN                                                                               X        
                         Number of Local Attributes                   NLA           X            X                   X             X                             
                         Number of Local Getters                      NLG           X            X                   X             X                             
                         Number of Local Methods                      NLM           X            X                   X             X                             
                         Number of Local Public Attributes            NLPA          X            X                   X             X                             
                         Number of Local Public Methods               NLPM          X            X                   X             X                             
                         Number of Local Setters                      NLS           X            X                   X             X                             
                         Number of Methods                            NM            X            X                   X             X                    X        
                         Number of Packages                           NPKG                                                                              X        
                         Number of Parameters                         NUMPAR                                                                   X                 
                         Number of Public Attributes                  NPA           X            X                   X             X                    X        
                         Number of Public Methods                     NPM           X            X                   X             X                    X        
                         Number of Setters                            NS            X            X                   X             X                    X        
                         Number of Statements                         NOS           X            X                   X             X           X                 
                         Total Lines of Code                          TLOC          X            X       X           X             X           X        X        
                         Total Logical Lines of Code                  TLLOC         X            X       X           X             X           X        X        
                         Total Number of Attributes                   TNA           X            X       X           X             X                    X        
                         Total Number of Classes                      TNCL                               X                                              X        
                         Total Number of Directories                  TNDI                               X                                              X        
                         Total Number of Enums                        TNEN                               X                                              X        
                         Total Number of Files                        TNFI                               X                                              X        
                         Total Number of Getters                      TNG           X            X       X           X             X                    X        
                         Total Number of Interfaces                   TNIN                               X                                              X        
                         Total Number of Local Attributes             TNLA          X            X                   X             X                             
                         Total Number of Local Getters                TNLG          X            X                   X             X                             
                         Total Number of Local Methods                TNLM          X            X                   X             X                             
                         Total Number of Local Public Attributes      TNLPA         X            X                   X             X                             
                         Total Number of Local Public Methods         TNLPM         X            X                   X             X                             
                         Total Number of Local Setters                TNLS          X            X                   X             X                             
                         Total Number of Methods                      TNM           X            X       X           X             X                    X        
                         Total Number of Packages                     TNPKG                              X                                              X        
                         Total Number of Public Attributes            TNPA          X            X       X           X             X                    X        
                         Total Number of Public Classes               TNPCL                              X                                              X        
                         Total Number of Public Enums                 TNPEN                              X                                              X        
                         Total Number of Public Interfaces            TNPIN                              X                                              X        
                         Total Number of Public Methods               TNPM          X            X       X           X             X                    X        
                         Total Number of Setters                      TNS           X            X       X           X             X                    X        
                         Total Number of Statements                   TNOS          X            X       X           X             X           X        X        


### Cohesion metrics

#### Lack of Cohesion in Methods 5 (LCOM5) {#LCOM5}

**Class:** number of functionalities of the class. One of the basic principles of object-oriented programming is encapsulation, meaning that attributes belonging together and the operations that use them should be organized into one class, and one class shall implement only one functionality, i.e. its attributes and methods should be coherent. This metric measures the lack of cohesion and computes into how many coherent classes the class could be split. It is calculated by taking a non-directed graph, where the nodes are the implemented local methods of the class and there is an edge between the two nodes if and only if a common (local or inherited) attribute or abstract method is used or a method invokes another. The value of the metric is the number of connected components in the graph not counting those, which contain only constructors, destructors, getters, or setters.


### Complexity metrics

#### Halstead Calculated Program Length (HCPL) {#HCPL}

**Method:**

 * _n1_: number of distinct operators (semantic meanings of the reserved keywords, semicolons, blocks, and identifiers except in their declarations)
 * _n2_: number of distinct operands (literals - e.g. character, string, and integer literals, - and the identifiers in their declarations)
  
The calculated program length is _n1 * log~2~(n1) + n2 * log~2~(n2)_.


#### Halstead Difficulty (HDIF) {#HDIF}

**Method:**

 * _n1_: number of distinct operators (semantic meanings of the reserved keywords, semicolons, blocks, and identifiers except in their declarations)
 * _n2_: number of distinct operands (literals - e.g. character, string, and integer literals, - and the identifiers in their declarations)
 * _N2_: total number of operands

The Halstead difficulty is _n1/2 * N2/n2_.


#### Halstead Effort (HEFF) {#HEFF}

**Method:**

 * _n1_: number of distinct operators (semantic meanings of the reserved keywords, semicolons, blocks, and identifiers except in their declarations)
 * _n2_: number of distinct operands (literals - e.g. character, string, and integer literals, - and the identifiers in their declarations)
 * _N1_: total number of operators
 * _N2_: total number of operands
 * _n : n1 + n2_ (program vocabulary)
 * _N : N1 + N2_ (program length)
 * _V : N * log~2~(n)_ (volume)
 * _D : n1/2 * N2/n2_ (difficulty)

The Halstead effort is _D * V_.

#### Halstead Number of Delivered Bugs (HNDB) {#HNDB}

**Method:**

 * _n1_: number of distinct operators (semantic meanings of the reserved keywords, semicolons, blocks, and identifiers except in their declarations)
 * _n2_: number of distinct operands (literals - e.g. character, string, and integer literals, - and the identifiers in their declarations)
 * _N1_: total number of operators
 * _N2_: total number of operands
 * _n : n1 + n2_ (program vocabulary)
 * _N : N1 + N2_ (program length)
 * _V : N * log~2~(n)_ (volume)
 * _D : n1/2 * N2/n2_ (difficulty)
 * _E : D * V_ (effort)

Number of delivered bugs is _E^2/3^/3000_.


#### Halstead Program Length (HPL) {#HPL}

**Method:**

 * _N1_: total number of operators (semantic meanings of the reserved keywords, semicolons, blocks, and identifiers except in their declarations)
 * _N2_: total number of operands (literals - e.g. character, string, and integer literals, - and the identifiers in their declarations)

Halstead program length is _N1 + N2_.


#### Halstead Program Vocabulary (HPV) {#HPV}

**Method:**

 * _n1_: number of distinct operators (semantic meanings of the reserved keywords, semicolons, blocks, and identifiers except in their declarations)
 * _n2_: number of distinct operands (literals - e.g. character, string, and integer literals, - and the identifiers in their declarations)

Halstead program vocabulary is _n1 + n2_.


#### Halstead Time Required to Program (HTRP) {#HTRP}

**Method:**

 * _n1_: number of distinct operators (semantic meanings of the reserved keywords, semicolons, blocks, and identifiers except in their declarations)
 * _n2_: number of distinct operands (literals - e.g. character, string, and integer literals, - and the identifiers in their declarations)
 * _N1_: total number of operators
 * _N2_: total number of operands
 * _n : n1 + n2_ (program vocabulary)
 * _N : N1 + N2_ (program length)
 * _V : N * log~2~(n)_ (volume)
 * _D : n1/2 * N2/n2_ (difficulty)
 * _E : D * V_ (effort)

Halstead time required to program is _E/18_ seconds.


#### Halstead Volume (HVOL) {#HVOL}

**Method:**

 * _n1_: number of distinct operators (semantic meanings of the reserved keywords, semicolons, blocks, and identifiers except in their declarations)
 * _n2_: number of distinct operands (literals - e.g. character, string, and integer literals, - and the identifiers in their declarations)
 * _N1_: total number of operators
 * _N2_: total number of operands
 * _n : n1 + n2_ (program vocabulary)
 * _N : N1 + N2_ (program length)

The Halstead volume is _N * log~2~(n)_.


#### Maintainability Index (Microsoft version) (MIMS) {#MIMS}

 * _HVOL_: Halstead Volume
 * _McCC_: McCabe's cyclomatic complexity
 * _LLOC_: logical lines of code
 
The Maintainability Index used by Microsoft's Visual Studio is computed by the following formula:

_MIMS = max(0,(171 - 5.2 * ln(HVOL) - 0.23 * (McCC) - 16.2 * ln(LLOC)) * 100 / 171)_

#### Maintainability Index (Original version) (MI) {#MI}

 * _HVOL_: Halstead Volume
 * _McCC_: McCabe's cyclomatic complexity
 * _LLOC_: logical lines of code
 
The original Maintainability Index is computed by the following formula:

_MI = 171 - 5.2 * ln(HVOL) - 0.23 * (McCC) - 16.2 * ln(LLOC)_

#### Maintainability Index (SEI version) (MISEI) {#MISEI}

 * _HVOL_: Halstead Volume
 * _McCC_: McCabe's cyclomatic complexity
 * _LLOC_: logical lines of code
 * _CD_: comment density
 
The Maintainability Index derived by the Software Engineering Institute (SEI) is computed by the following formula:

_MISEI = 171 - 5.2 * log~2~(HVOL) - 0.23 * McCC - 16.2 * log~2~(LLOC) + 50 * sin(sqrt(2.4 * CD))_

#### Maintainability Index (OpenStaticAnalyzer version) (MISM) {#MISM}

 * _HVOL_: Halstead Volume
 * _McCC_: McCabe's cyclomatic complexity
 * _LLOC_: logical lines of code
 * _CD_: comment density
 
The Maintainability Index proposed by OpenStaticAnalyzer combines the different scaling approach from Microsoft's version with the inclusion of comment percentage from the Software Engineering Institute (SEI) version into the following formula:

_MISM = max(0, (171 - 5.2 * log~2~(HVOL) - 0.23 * McCC - 16.2 * log~2~(LLOC) + 50 * sin(sqrt(2.4 * CD))) * 100 / 171)_


#### McCabe's Cyclomatic Complexity (McCC) {#McCC}

**Method:** complexity of the method expressed as the number of independent control flow paths in it. It represents a lower bound for the number of possible execution paths in the source code and at the same time it is an upper bound for the minimum number of test cases needed for achieving full branch test coverage. The value of the metric is calculated as the number of the following instructions plus 1: if, for, foreach, while, do-while, case label (which belongs to a switch instruction), catch, conditional statement (?:). Moreover, logical "and" (&&) and logical "or" (||) expressions also add 1 to the value because their short-circuit evaluation can cause branching depending on the first operand. The following instructions are not included: else, switch, default label (which belongs to a switch instruction), try, finally.

**File:** complexity of the file expressed as the number of independent control flow paths in it. It is calculated as the sum of the McCabe's Cyclomatic Complexity values of the methods can be found in the file.


#### Nesting Level (NL) {#NL}

**Method:** complexity of the method expressed as the depth of the maximum embeddedness of its conditional, iteration and exception handling block scopes. The following instructions are taken into account: if, else-if, else, for, while, do-while, switch, try, catch, finally and block statements that are directly inside another block statement. The following instructions do not increase the value by themselves; however, if additional embeddednesses can be found in their blocks, they are considered: case and default label (which belong to a switch instruction).

**Class:** complexity of the class expressed as the depth of the maximum embeddedness of its conditional, iteration and exception handling block scopes. It is calculated as the maximum nesting level (NL) of its local methods and init blocks.


#### Nesting Level Else-If (NLE) {#NLE}

**Method:** complexity of the method expressed as the depth of the maximum embeddedness of its conditional, iteration and exception handling block scopes, where in the if-else-if construct only the first if instruction is considered. The following instructions are taken into account: if, else, for, while, do-while, switch, try, catch, finally and block statements that are directly inside another block statement. The following instructions do not increase the value by themselves; however, if additional embeddednesses can be found in their blocks, they are considered: else-if (i.e. in the if-else-if construct the use of else-if does not increase the value of the metric), case and default label (which belong to a switch instruction).

**Class:** complexity of the class expressed as the depth of the maximum embeddedness of its conditional, iteration and exception handling block scopes, where in the if-else-if construct only the first if instruction is considered. It is calculated as the maximum nesting level (NLE) of its local methods and init blocks.


#### Weighted Methods per Class (WMC) {#WMC}

**Class:** complexity of the class expressed as the number of independent control flow paths in it. It is calculated as the sum of the McCabe's Cyclomatic Complexity (McCC) values of its local methods and init blocks.


### Coupling metrics

#### Coupling Between Object classes (CBO) {#CBO}

**Class:** number of directly used other classes (e.g. by inheritance, function call, type reference, attribute reference). Classes using many other classes highly depend on their environment, so it is difficult to test or reuse them; furthermore, they are very sensitive to the changes in the system.


#### Coupling Between Object classes Inverse (CBOI) {#CBOI}

**Class:** number of other classes, which directly use the class. Classes which are used by many other classes have a high impact on the behavior of the system, and should be modified very carefully and tested intensively.


#### Number of Incoming Invocations (NII) {#NII}

**Method:** number of other methods and attribute initializations which directly call the method. If the method is invoked several times from the same method or attribute initialization, it is counted only once.

**Class:** number of other methods and attribute initializations which directly call the local methods of the class. If a method is invoked several times from the same method or attribute initialization, it is counted only once.


#### Number of Outgoing Invocations (NOI) {#NOI}

**Method:** number of directly called methods. If a method is invoked several times, it is counted only once.

**Class:** number of directly called methods of other classes, including method invocations from attribute initializations. If a method is invoked several times, it is counted only once.


#### Response set For Class (RFC) {#RFC}

**Class:** number of local (i.e. not inherited) methods in the class (NLM) plus the number of directly invoked other methods by its methods or attribute initializations (NOI).


### Documentation metrics

#### API Documentation (AD) {#AD}

**Class:** ratio of the number of documented public methods in the class +1 if the class itself is documented to the number of all public methods in the class + 1 (the class itself); however, the nested, anonymous, and local classes are not included.

**Package:** ratio of the number of documented public classes and methods in the package to the number of all of its public classes and methods; however, the classes and methods of its subpackages are not included.


#### Comment Density (CD) {#CD}

**Method:** ratio of the comment lines of the method (CLOC) to the sum of its comment (CLOC) and logical lines of code (LLOC).

**Class**: ratio of the comment lines of the class (CLOC) to the sum of its comment (CLOC) and logical lines of code (LLOC).

**Package:** ratio of the comment lines of the package (CLOC) to the sum of its comment (CLOC) and logical lines of code (LLOC).


#### Comment Lines of Code (CLOC) {#CLOC}

**Method**: number of comment and documentation code lines of the method; however, its anonymous and local classes are not included.

**Class:** number of comment and documentation code lines of the class, including its local methods and attributes; however, its nested, anonymous, and local classes are not included.

**File:** number of comment and documentation code lines of the file.

**Package:** number of comment and documentation code lines of the package; however, its subpackages are not included.


#### Documentation Lines of Code (DLOC) {#DLOC}

**Method**: number of documentation code lines of the method.

**Class:** number of documentation code lines of the class, including its local methods and attributes; however, its nested, anonymous, and local classes are not included.


#### Public Documented API (PDA) {#PDA}

**Class:** number of documented public methods in the class (+1 if the class itself is documented); however, the methods of its nested, anonymous, and local classes are not counted.

**File:** number of documented public classes and methods in the file.

**Package:** number of documented public classes and methods in the package; however, the classes and methods of its subpackages are not counted.


#### Public Undocumented API (PUA) {#PUA}

**Class:** number of undocumented public methods in the class (+1 if the class itself is undocumented); however, the methods of its nested, anonymous, and local classes are not counted.

**File:** number of undocumented public classes and methods in the file.

**Package:** number of undocumented public classes and methods in the package; however, the classes and methods of its subpackages are not counted.


#### Total API Documentation (TAD) {#TAD}

**Package:** ratio of the number of documented public classes and methods in the package to the number of all of its public classes and methods, including its subpackages.

**Component:** ratio of the number of documented public classes and methods in the component to the number of all of its public classes and methods, including its subcomponents.


#### Total Comment Density (TCD) {#TCD}

**Method:** ratio of the total comment lines of the method (TCLOC) to the sum of its total comment (TCLOC) and total logical lines of code (TLLOC).

**Class:** ratio of the total comment lines of the class (TCLOC) to the sum of its total comment (TCLOC) and total logical lines of code (TLLOC).

**Package:** ratio of the total comment lines of the package (TCLOC) to the sum of its total comment (TCLOC) and total logical lines of code (TLLOC).

**Component:** ratio of the total comment lines of the component (TCLOC) to the sum of its total comment (TCLOC) and total logical lines of code (TLLOC).


#### Total Comment Lines of Code (TCLOC) {#TCLOC}

**Method**: number of comment and documentation code lines of the method, including its anonymous and local classes.

**Class:** number of comment and documentation code lines of the class, including its local methods and attributes, as well as its nested, anonymous, and local classes.

**Package:** number of comment and documentation code lines of the package, including its subpackages.

**Component:** number of comment and documentation code lines of the component, including its subcomponents.


#### Total Public Documented API (TPDA) {#TPDA}

**Package:** number of documented public classes and methods in the package, including the documented public classes and methods of its subpackages.

**Component:** number of documented public classes and methods in the component, including the documented public classes and methods of its subcomponents.


#### Total Public Undocumented API (TPUA) {#TPUA}

**Package:** number of undocumented public classes and methods in the package, including the undocumented public classes and methods of its subpackages.

**Component:** number of undocumented public classes and methods in the component, including the undocumented public classes and methods of its subcomponents.


### Inheritance metrics

#### Depth of Inheritance Tree (DIT) {#DIT}

**Class:** length of the path that leads from the class to its farthest ancestor in the inheritance tree.


#### Number of Ancestors (NOA) {#NOA}

**Class:** number of classes, interfaces, enums and annotations from which the class is directly or indirectly inherited.


#### Number of Children (NOC) {#NOC}

**Class:** number of classes, interfaces, enums and annotations which are directly derived from the class.


#### Number of Descendants (NOD) {#NOD}

**Class:** number of classes, interfaces, enums, annotations, which are directly or indirectly derived from the class.


#### Number of Parents (NOP) {#NOP}

**Class:** number of classes, interfaces, enums and annotations from which the class is directly inherited.


### Size metrics

#### Lines of Code (LOC) {#LOC}

**Method**: number of code lines of the method, including empty and comment lines; however, its anonymous and local classes are not included.

**Class:** number of code lines of the class, including empty and comment lines, as well as its local methods; however, its nested, anonymous, and local classes are not included.

**File:** number of code lines of the file.

**Package:** number of code lines of the package, including empty and comment lines; however, its subpackages are not included.


#### Logical Lines of Code (LLOC) {#LLOC}

**Method:** number of non-empty and non-comment code lines of the method; however, its anonymous and local classes are not included.

**Class:** number of non-empty and non-comment code lines of the class, including the non-empty and non-comment lines of its local methods; however, its nested, anonymous, and local classes are not included.

**File:** number of non-empty and non-comment code lines of the file.

**Package:** number of non-empty and non-comment code lines of the package; however, its subpackages are not included.



#### Number of Attributes (NA) {#NA}

**Class:** number of attributes in the class, including the inherited ones; however, the attributes of its nested, anonymous, and local classes are not included.

**Package:** number of attributes in the package; however, attributes of its subpackages are not included.


#### Number of Classes (NCL) {#NCL}

**Package:** number of classes in the package; however, the classes of its subpackages are not included.


#### Number of Enums (NEN) {#NEN}

**Package:** number of enums in the package; however, the enums of its subpackages are not included.


#### Number of Getters (NG) {#NG}

**Class:** number of getter methods in the class, including the inherited ones; however, the getter methods of its nested, anonymous, and local classes are not included. Methods that override abstract methods are not counted.

**Package**: number of getter methods in the package; however, getter methods of its subpackages are not included.


#### Number of Interfaces (NIN) {#NIN}

**Package:** number of interfaces in the package; however, the interfaces of its subpackages are not included.


#### Number of Local Attributes (NLA) {#NLA}

**Class:** number of local (i.e. not inherited) attributes in the class; however, the attributes of nested, anonymous, and local classes are not included.


#### Number of Local Getters (NLG) {#NLG}

**Class:** number of local (i.e. not inherited) getter methods in the class; however, the getter methods of its nested, anonymous, and local classes are not included. Methods that override abstract methods are not counted.


#### Number of Local Methods (NLM) {#NLM}

**Class:** number of local (i.e. not inherited) methods in the class; however, the methods of nested, anonymous, and local classes are not included.


#### Number of Local Public Attributes (NLPA) {#NLPA}

**Class:** number of local (i.e. not inherited) public attributes in the class; however, the attributes of nested, anonymous, and local classes are not included.


#### Number of Local Public Methods (NLPM) {#NLPM}

**Class:** number of local (i.e. not inherited) public methods in the class; however, the methods of nested, anonymous, and local classes are not included.


#### Number of Local Setters (NLS) {#NLS}

**Class:** number of local (i.e. not inherited) setter methods in the class; however, the setter methods of its nested, anonymous, and local classes are not included. Methods that override abstract methods are not counted.


#### Number of Methods (NM) {#NM}

**Class:** number of methods in the class, including the inherited ones; however, the methods of its nested, anonymous and local classes are not included. Methods that override abstract methods are not counted.

**Package:** number of methods in the package; however, methods of its subpackages are not included.


#### Number of Packages (NPKG) {#NPKG}

**Package:** number of directly contained subpackages of the package.


#### Number of Parameters (NUMPAR) {#NUMPAR}

**Method**: number of the parameters of the method. The varargs parameter counts as one.


#### Number of Public Attributes (NPA) {#NPA}

**Class:** number of public attributes in the class, including the inherited ones; however, the public attributes of its nested, anonymous, and local classes are not included.

**Package:** number of public attributes in the package; however, the public attributes of its subpackages are not included.


#### Number of Public Methods (NPM) {#NPM}

**Class:** number of public methods in the class, including the inherited ones; however, the public methods of nested, anonymous, and local classes are not included. Methods that override abstract methods are not counted.

**Package:** number of public methods in the package; however, the public methods of its subpackages are not included.


#### Number of Setters (NS) {#NS}

**Class:** number of setter methods in the class, including the inherited ones; however, the setter methods of its nested, anonymous, and local classes are not included. Methods that override abstract methods are not counted.

**Package:** number of setter methods in the package; however, setter methods of its subpackages are not included.


#### Number of Statements (NOS) {#NOS}

**Method:** number of statements in the method; however, the statements of its anonymous and local classes are not included.

**Class:** number of statements in the class; however, the statements of its nested, anonymous, and local classes are not included.


#### Total Lines of Code (TLOC) {#TLOC}

**Method**: number of code lines of the method, including empty and comment lines, as well as its anonymous and local classes.

**Class:** number of code lines of the class, including empty and comment lines, as well as its local methods, anonymous, local, and nested classes.

**Package:** number of code lines of the package, including empty and comment lines, as well as its subpackages.

**Component:** number of code lines of the component, including empty and comment lines, as well as its subcomponents.


#### Total Logical Lines of Code (TLLOC) {#TLLOC}

**Method**: number of non-empty and non-comment code lines of the method, including the non-empty and non-comment lines of its anonymous and local classes.

**Class:** number of non-empty and non-comment code lines of the class, including the non-empty and non-comment code lines of its local methods, anonymous, local, and nested classes.

**Package:** number of non-empty and non-comment code lines of the package, including its subpackages.

**Component:** number of non-empty and non-comment code lines of the component, including its subcomponents.


#### Total Number of Attributes (TNA) {#TNA}

**Class:** number of attributes in the class, including the inherited ones, as well as the inherited and local attributes of its nested, anonymous and local classes.

**Package:** number of attributes in the package, including the attributes of its subpackages.

**Component:** number of attributes in the component, including the attributes of its subcomponents.


#### Total Number of Classes (TNCL) {#TNCL}

**Package:** number of classes in the package, including the classes of its subpackages.

**Component:** number of classes in the component, including the classes of its subcomponents.


#### Total Number of Directories[^7] (TNDI) {#TNDI}

**Package:** number of directories that belong to the package, including the directories of its subpackages.

**Component:** number of directories that belong to the component, including its subcomponents.


#### Total Number of Enums (TNEN) {#TNEN}

**Package:** number of enums in the package, including the enums of its subpackages.

**Component:** number of enums in the component, including the enums of its subcomponents.


#### Total Number of Files (TNFI) {#TNFI}

**Package:** number of files that belong to the package, including the files of its subpackages.

**Component:** number of files that belong to the component, including its subcomponents.


#### Total Number of Getters (TNG) {#TNG}

**Class:** number of getter methods in the class, including the inherited ones, as well as the inherited and local getter methods of its nested, anonymous and local classes.

**Package:** number of getter methods in the package, including the getter methods of its subpackages.

**Component:** number of getter methods in the component, including the getter methods of its subcomponents.


#### Total Number of Interfaces (TNIN) {#TNIN}

**Package:** number of interfaces in the package, including the interfaces of its subpackages.

**Component:** number of interfaces in the component, including the interfaces of its subcomponents.


#### Total Number of Local Attributes (TNLA) {#TNLA}

**Class:** number of local (i.e. not inherited) attributes in the class, including the attributes of its nested, anonymous, and local classes.


#### Total Number of Local Getters (TNLG) {#TNLG}

**Class:** number of local (i.e. not inherited) getter methods in the class, including the local getter methods of its nested, anonymous, and local classes.


#### Total Number of Local Methods (TNLM) {#TNLM}

**Class:** number of local (i.e. not inherited) methods in the class, including the local methods of its nested, anonymous, and local classes.


#### Total Number of Local Public Attributes (TNLPA) {#TNLPA}

**Class:** number of local (i.e. not inherited) public attributes in the class, including the local public attributes of its nested, anonymous, and local classes.


#### Total Number of Local Public Methods (TNLPM) {#TNLPM}

**Class:** number of local (i.e. not inherited) public methods in the class, including the local methods of its nested, anonymous, and local classes.


#### Total Number of Local Setters (TNLS) {#TNLS}

**Class:** number of local (i.e. not inherited) setter methods in the class, including the local setter methods of its nested, anonymous, and local classes.


#### Total Number of Methods (TNM) {#TNM}

**Class:** number of methods in the class, including the inherited ones, as well as the inherited and local methods of its nested, anonymous, and local classes. Methods that override abstract methods are not counted.

**Package:** number of methods in the package, including the methods of its subpackages.

**Component:** number of methods in the component, including the methods of its subcomponents.


#### Total Number of Packages (TNPKG) {#TNPKG}

**Package:** number of subpackages in the package, including all directly or indirectly contained subpackages.

**Component:** number of packages and subpackages that belong to the component, including its subcomponents.


#### Total Number of Public Attributes (TNPA) {#TNPA}

**Class:** number of public attributes in the class, including the inherited ones, as well as the inherited and local public attributes of its nested, anonymous, and local classes.

**Package:** number of public attributes in the package, including the public attributes of its subpackages.

**Component:** number of public attributes in the component, including the public attributes of its subcomponents.


#### Total Number of Public Classes (TNPCL) {#TNPCL}

**Package:** number of public classes in the package, including the public classes of its subpackages.

**Component:** number of public classes in the component, including the public classes of its subcomponents.


#### Total Number of Public Enums (TNPEN) {#TNPEN}

**Package:** number of public enums in the package, including the public enums of its subpackages.

**Component:** number of public enums in the component, including the public enums of its subcomponents.


#### Total Number of Public Interfaces (TNPIN) {#TNPIN}

**Package:** number of public interfaces in the package, including the public interfaces of its subpackages.

**Component:** number of public interfaces in the component, including the public interfaces of its subcomponents.


#### Total Number of Public Methods (TNPM) {#TNPM}

**Class:** number of public methods in the class, including the inherited ones, as well as the inherited and local public methods of its nested, anonymous, and local classes.

**Package:** number of public methods in the package, including the public methods of its subpackages.

**Component:** number of public methods in the component, including the public methods of its subcomponents.


#### Total Number of Setters (TNS) {#TNS}

**Class:** number of setter methods in the class, including the inherited ones, as well as the inherited and local setter methods of its nested, anonymous and local classes.

**Package:** number of setter methods in the package, including the setter methods of its subpackages.

**Component:** number of setter methods in the component, including the setter methods of its subcomponents.


#### Total Number of Statements (TNOS) {#TNOS}

**Method:** number of statements in the method, including the statements of its anonymous and local classes.

**Class:** number of statements in the class, including the statements of its nested, anonymous, and local classes.

**Package:** number of statements in the package, including the statements of its subpackages.

**Component:** number of statements in the component, including the statements of its subcomponents.
