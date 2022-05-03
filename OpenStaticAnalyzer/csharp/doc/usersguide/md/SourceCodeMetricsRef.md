## Reference of source code metrics

Source code metrics are used to quantify different source code characteristics. OpenStaticAnalyzer computes source code metrics for the following source code element kinds: components (e.g. C# assemblies), source files, namespaces, types (including classes, interfaces, enums and structures) and methods.

The calculated metrics are grouped into 6 categories, which are the following:

- **Cohesion metrics:** measure to what extent the source code elements are coherent in the system.

- **Complexity metrics:** measure the complexity of source code elements (typically algorithms).

- **Coupling metrics:** measure the amount of interdependencies of source code elements.

- **Documentation metrics:** measure the amount of comments and documentation of source code elements in the system.

- **Inheritance metrics:** measure the different aspects of the inheritance hierarchy of the system.

- **Size metrics:** measure the basic properties of the analyzed system in terms of different cardinalities (e.g. number of code lines, number of classes or methods).

In the case of the documentation metrics all the comments found immediately before a source code element are considered as its documentation, while the comments contained inside the source code element are considered as its comments.

The following table summarizes the metrics, their abbreviations and their correspondence to different source code element kinds:

  Category               Metric name                              Abbreviation   Class   Component   Delegate   Enum   File   Interface   Method   Namespace   Structure
  ---------------------- ---------------------------------------- ------------- ------- ----------- ---------- ------ ------ ----------- -------- ----------- -----------
  Cohesion metrics       Lack of Cohesion in Methods 5            LCOM5         X                                                                             X
  Complexity metrics     McCabe's Cyclomatic Complexity           McCC                                                X                  X
                         Weighted Methods per Class               WMC           X                                                                             X
  Coupling metrics       Coupling Between Object classes          CBO           X                                            X                                X
                         Number of Outgoing Invocations           NOI           X                                                        X                    X
                         Response set For Class                   RFC           X                                                                             X
  Documentation metrics  API Documentation                        AD            X                              X             X                    X           X
                         Comment Density                          CD            X                   X                                    X        X           X
                         Documentation Lines of Code              DLOC          X                   X          X             X           X                    X
                         Public Documented API                    PDA           X                                     X      X                    X           X
                         Public Undocumented API                  PUA           X                                     X      X                    X           X
                         Total API Documentation                  TAD                   X                                                         X
                         Total Comment Lines of Code              TCLOC         X       X           X                        X           X        X           X
                         Total Public Documented API              TPDA                  X                                                         X
                         Total Public Undocumented API            TPUA                  X                                                         X
  Inheritance metrics    Depth of Inheritance Tree                DIT           X                                            X                                X
                         Number of Ancestors                      NOA           X                                            X                                X
                         Number of Children                       NOC           X                                            X                                X
                         Number of Descendants                    NOD           X                                            X                                X
                         Number of Parents                        NOP           X                                            X                                X
  Size metrics           Lines of Code                            LOC           X                   X          X      X      X           X        X           X
                         Logical Lines of Code                    LLOC          X                   X          X      X      X           X        X           X
                         Number of Classes                        NCL                                                                             X
                         Number of Enums                          NEN                                                                             X
                         Number of Getters                        NG            X                                            X                    X           X
                         Number of Interfaces                     NIN                                                                             X
                         Number of Local Getters                  NLG           X                                            X                                X
                         Number of Local Methods                  NLM           X                                            X                                X
                         Number of Local Public Methods           NLPM          X                                            X                                X
                         Number of Local Setters                  NLS           X                                            X                                X
                         Number of Methods                        NM            X                                            X                    X           X
                         Number of Packages                       NPKG                                                                            X
                         Number of Parameters                     NUMPAR                                                                 X
                         Number of Public Methods                 NPM           X                                            X                    X           X
                         Number of Setters                        NS            X                                            X                    X           X
                         Number of Statements                     NOS           X                                                        X                    X
                         Number of Structures                     NST                                                                             X
                         Total Lines of Code                      TLOC          X       X           X          X             X           X        X           X
                         Total Logical Lines of Code              TLLOC         X       X           X          X             X           X        X           X
                         Total Number of Classes                  TNCL                  X                                                         X
                         Total Number of Directories              TNDI                  X                                                         X
                         Total Number of Enums                    TNEN                  X                                                         X
                         Total Number of Files                    TNFI                  X                                                         X
                         Total Number of Getters                  TNG           X       X                                    X                    X           X
                         Total Number of Interfaces               TNIN                  X                                                         X
                         Total Number of Local Getters            TNLG          X       X                                    X                                X
                         Total Number of Local Methods            TNLM          X       X                                    X                                X
                         Total Number of Local Public Methods     TNLPM         X       X                                    X                                X
                         Total Number of Local Setters            TNLS          X       X                                    X                                X
                         Total Number of Methods                  TNM           X       X                                    X                    X           X
                         Total Number of Packages                 TNPKG                 X                                                         X
                         Total Number of Public Classes           TNPCL                 X                                                         X
                         Total Number of Public Enums             TNPEN                 X                                                         X
                         Total Number of Public Interfaces        TNPIN                 X                                                         X
                         Total Number of Public Methods           TNPM          X       X                                    X                    X           X
                         Total Number of Public Structures        TNPST                 X                                                         X
                         Total Number of Setters                  TNS           X       X                                    X                    X           X
                         Total Number of Statements               TNOS          X       X                                                X        X           X
                         Total Number of Structures               TNST                  X                                                         X

### Cohesion metrics

#### Lack of Cohesion in Methods 5 (LCOM5) {#LCOM5}

**Class, Structure:** number of functionalities of the class. One of the basic principles of object-oriented programming is encapsulation, meaning that attributes belonging together and the operations that use them should be organized into one class, and one class shall implement only one functionality, i.e. its attributes and methods should be coherent. This metric measures the lack of cohesion and computes into how many coherent classes the class could be split. It is calculated by taking a non-directed graph, where the nodes are the implemented local methods of the class and there is an edge between the two nodes if and only if a common (local or inherited) attribute or abstract method is used or a method invokes another. The value of the metric is the number of connected components in the graph except the ones that contain only constructors, destructors, getters or setters -- as they are integral parts of the class.

### Complexity metrics

#### McCabe's Cyclomatic Complexity (McCC) {#McCC}

**Method:** complexity of the method expressed as the number of independent control flow paths in it. It represents a lower bound for the number of possible execution paths in the source code and at the same time it is an upper bound for the minimum number of test cases needed for achieving full branch test coverage. The value of the metric is initially 1 which increases by 1 for each occurence of the following instructions: if, for, foreach, while, do-while, case label (label that belongs to a switch instruction), catch (handler that belongs to a try block), conditional statement (?:) and conditional access operators (?. and ?[]). Moreover, logical and (&&), logical or (||) and null coalescing (??) expressions also add to the final value because their short-circuit evalutaion can cause branching depending on the first operand. The following language elements do not increase the value: else, try, switch, default label (default label that belongs to a switch instruction), finally.

#### Weighted Methods per Class (WMC) {#WMC}

**Class, Structure:** complexity of the class expressed as the number of independent control flow paths in it. It is calculated as the sum of the McCabe's Cyclomatic Complexity (McCC) values of its local methods.

### Coupling metrics

#### Coupling Between Object classes (CBO) {#CBO}

**Class, Structure:** number of directly used other classes (e.g. by inheritance, function call, type reference, attribute reference). Classes using many other classes highly depend on their environment, so it is difficult to test or reuse them; furthermore, they are very sensitive to the changes in the system.

#### Number of Outgoing Invocations (NOI) {#NOI}

**Method:** number of directly called methods. If a method is invoked several times, it is counted only once.

**Class, Structure:** number of directly called methods of other classes, including method invocations from attribute initializations. If a method is invoked several times, it is counted only once.

#### Response set For Class (RFC) {#RFC}

**Class, Structure:** number of local (i.e. not inherited) methods in the class (NLM) plus the number of directly invoked other methods by its methods or attribute initializations (NOI).

### Documentation metrics

#### API Documentation (AD) {#AD}

**Class, Structure:** ratio of the number of documented public methods in the class +1 if the class itself is documented to the number of all public methods in the class + 1 (the class itself); however, the nested and anonymous classes are not included.

**Namespace:** ratio of the number of documented public classes and methods in the namespace to the number of all of its public classes and methods; however, the classes and methods of its subnamespaces are not included.

#### Comment Lines of Code (CLOC) {#CLOC}

**Method:** number of comment and documentation code lines of the method; however, its anonymous classes are not included.

**Class, Structure:** number of comment and documentation code lines of the class, including its local methods and attributes; however, its nested and anonymous classes are not included.

**Namespace:** number of comment and documentation code lines of the namespace; however, its subnamespaces are not included.

#### Documentation Lines of Code (DLOC) {#DLOC}

**Method:** number of documentation code lines of the method.

**Class, Structure:** number of documentation code lines of the class, including its local methods and attributes; however, its nested and anonymous classes are not included.

#### Public Documented API (PDA) {#PDA}

**Class, Structure:** the number of the documented public methods of the class (+1 if the class itself is documented). When calculating the metrics the nested, anonymous or local classes found in the class and their methods are not calculated.

**Namespace:** the number of the documented public classes and public documented methods found in the namespace. When calculating the metric, classes and methods found in the subnamespaces of the namespace are not taken into account.

#### Public Undocumented API (PUA) {#PUA}

**Class, Structure:** the number of the undocumented public methods of the class (+1 if the class itself is undocumented). When calculating the metrics the nested, anonymous or local classes to be found in the class and their methods are not calculated.

**Namespace:** the number of the undocumented public classes and undocumented public methods to be found in the namespace. When calculating the metric, classes and methods to be found in the subnamespaces of the namespace are not taken into account.

#### Total API Documentation (TAD) {#TAD}

**Namespace:** ratio of the number of documented public classes and methods in the namespace to the number of all of its public classes and methods, including its subnamespaces.

**Component:** ratio of the number of documented public classes and methods in the component to the number of all of its public classes and methods, including its subcomponents.

#### Total Comment Lines of Code (TCLOC) {#TCLOC}

**Method:** number of comment and documentation code lines of the method, including its anonymous classes.

**Class, Structure:** number of comment and documentation code lines of the class, including its local methods and attributes, as well as its nested and anonymous classes.

**Namespace:** number of comment and documentation code lines of the namespace, including its subnamespaces.

**Component:** number of comment and documentation code lines of the component, including its subcomponents.

#### Total Public Documented API (TPDA) {#TPDA}

**Namespace:** the number of the public documented classes and their public documented methods found in the namespace. When calculating the metric, classes and methods found in subnamespaces of the namespace are also taken into account.

**Component:** the number of public documented classes and public documented methods found in the component, where in calculating the metric, classes and methods to be found in subcomponents of the component are also taken into account.

#### Total Public Undocumented API (TPUA) {#TPUA}

**Namespace:** the number of the public undocumented classes and their public undocumented methods found in the namespace. When calculating the metric, classes and methods found in subnamespaces of the namespace are also taken into account.

**Component:** the number of public undocumented classes and public undocumented methods found in the component, where in calculating the metric, classes and methods to be found in subcomponents of the component are also taken into account.

### Inheritance metrics

#### Depth of Inheritance Tree (DIT) {#DIT}

**Class, Structure:** length of the path that leads from the class to its farthest ancestor in the inheritance tree.

#### Number of Ancestors (NOA) {#NOA}

**Class, Structure:** number of classes and interfaces from which the class is directly or indirectly inherited.

#### Number of Children (NOC) {#NOC}

**Class, Structure:** number of classes and interfaces which are directly derived from the class.

#### Number of Descendants (NOD) {#NOD}

**Class, Structure:** number of classes and interfaces which are directly or indirectly derived from the class.

#### Number of Parents (NOP) {#NOP}

**Class, Structure:** number of classes and interfaces from which the class is directly inherited.

### Size metrics

#### Lines of Code (LOC) {#LOC}

**Method:** number of code lines of the method, including empty and comment lines; however, its anonymous classes are not included.

**Class, Structure:** number of code lines of the class, including empty and comment lines, as well as its local methods; however, its nested and anonymous classes are not included.

**Namespace:** number of code lines of the namespace, including empty and comment lines; however, its subnamespaces are not included.

#### Logical Lines of Code (LLOC) {#LLOC}

**Method:** number of non-empty and non-comment code lines of the method; however, its anonymous classes are not included.

**Class, Structure:** number of non-empty and non-comment code lines of the class, including the non-empty and non-comment lines of its local methods; however, its nested and anonymous classes are not included.

**Namespace:** number of non-empty and non-comment code lines of the namespace; however, its subnamespaces are not included.

**File:** number of non-empty and non-comment code lines of the file.

#### Number of Classes (NCL) {#NCL}

**Namespace:** number of classes in the namespace; however, the classes of its subnamespaces are not included.

#### Number of Enums (NEN) {#NEN}

**Namespace:** number of enums in the namespace; however, the enums of its subnamespaces are not included.

#### Number of Getters (NG) {#NG}

**Class, Structure:** number of getter methods in the class, including the inherited ones; however, the getter methods of its nested and anonymous classes are not included. Methods that override abstract methods are not counted.

**Namespace:** number of getter methods in the namespace; however, getter methods of its subnamespaces are not included.

#### Number of Interfaces (NIN) {#NIN}

**Namespace:** number of interfaces in the namespace; however, the interfaces of its subnamespaces are not included.

#### Number of Local Getters (NLG) {#NLG}

**Class, Structure:** number of local (i.e. not inherited) getter methods in the class; however, the getter methods of its nested and anonymous classes are not included. Methods that override abstract methods are not counted.

#### Number of Local Methods (NLM) {#NLM}

**Class, Structure:** number of local (i.e. not inherited) methods in the class; however, the methods of nested and anonymous classes are not included.

#### Number of Local Public Methods (NLPM) {#NLPM}

**Class, Structure:** number of local (i.e. not inherited) public methods in the class; however, the methods of nested and anonymous classes are not included.

#### Number of Local Setters (NLS) {#NLS}

**Class, Structure:** number of local (i.e. not inherited) setter methods in the class; however, the setter methods of its nested and anonymous classes are not included. Methods that override abstract methods are not counted.

#### Number of Methods (NM) {#NM}

**Class, Structure:** number of methods in the class, including the inherited ones; however, the methods of its nested and anonymous classes are not included. Methods that override abstract methods are not counted.

**Namespace:** number of methods in the namespace; however, methods of its subnamespaces are not included.

#### Number of Packages (NPKG) {#NPKG}

**Namespace:** number of directly contained subnamespaces of the namespace.

#### Number of Parameters (NUMPAR) {#NUMPAR}

**Method:** number of the parameters of the method. The varargs parameter counts as one.

#### Number of Public Methods (NPM) {#NPM}

**Class, Structure:** number of public methods in the class, including the inherited ones; however, the public methods of nested and anonymous classes are not included. Methods that override abstract methods are not counted.

**Namespace:** number of public methods in the namespace; however, the public methods of its subnamespaces are not included.

#### Number of Setters (NS) {#NS}

**Class, Structure:** number of setter methods in the class, including the inherited ones; however, the setter methods of its nested and anonymous classes are not included. Methods that override abstract methods are not counted.

**Namespace:** number of setter methods in the namespace; however, setter methods of its subnamespaces are not included.

#### Number of Statements (NOS) {#NOS}

**Method:** number of statements in the method; however, the statements of its anonymous classes are not included.

**Class, Structure:** number of statements in the class; however, the statements of its nested and anonymous classes are not included.

#### Number of Structures (NST) {#NST}

**Namespace:** number of structures in the namespace; however, the structures of its subnamespaces are not included.

#### Total Lines of Code (TLOC) {#TLOC}

**Method:** number of code lines of the method, including empty and comment lines, as well as its anonymous classes.

**Class, Structure:** number of code lines of the class, including empty and comment lines, as well as its local methods, anonymous and nested classes.

**Namespace:** number of code lines of the namespace, including empty and comment lines, as well as its subnamespaces.

**Component:** number of code lines of the component, including empty and comment lines, as well as its subcomponents.

#### Total Logical Lines of Code (TLLOC) {#TLLOC}

**Method:** number of non-empty and non-comment code lines of the method, including the non-empty and non-comment lines of its anonymous classes.

**Class, Structure:** number of non-empty and non-comment code lines of the class, including the non-empty and non-comment code lines of its local methods, anonymous and nested classes.

**Namespace:** number of non-empty and non-comment code lines of the namespace, including its subnamespaces.

**Component:** number of non-empty and non-comment code lines of the component, including its subcomponents.

#### Total Number of Classes (TNCL) {#TNCL}

**Namespace:** number of classes in the namespace, including the classes of its subnamespaces.

**Component:** number of classes in the component, including the classes of its subcomponents.

#### Total Number of Directories (TNDI) {#TNDI}

**Namespace:** number of directories that belong to the namespace, including the directories of its subnamespaces.

**Component:** number of directories that belong to the component, including its subcomponents.

#### Total Number of Enums (TNEN) {#TNEN}

**Namespace:** number of enums in the namespace, including the enums of its subnamespaces.

**Component:** number of enums in the component, including the enums of its subcomponents.

#### Total Number of Files (TNFI) {#TNFI}

**Namespace:** number of files that belong to the namespace, including the files of its subnamespaces.

**Component:** number of files that belong to the component, including its subcomponents.

#### Total Number of Getters (TNG) {#TNG}

**Class, Structure:** number of getter methods in the class, including the inherited ones, as well as the inherited and local getter methods of its nested and anonymous classes.

**Namespace:** number of getter methods in the namespace, including the getter methods of its subnamespaces.

**Component:** number of getter methods in the component, including the getter methods of its subcomponents.

#### Total Number of Interfaces (TNIN) {#TNIN}

**Namespace:** number of interfaces in the namespace, including the interfaces of its subnamespaces.

**Component:** number of interfaces in the component, including the interfaces of its subcomponents.

#### Total Number of Local Getters (TNLG) {#TNLG}

**Class, Structure:** number of local (i.e. not inherited) getter methods in the class, including the local getter methods of its nested and anonymous classes.

#### Total Number of Local Methods (TNLM) {#TNLM}

**Class, Structure:** number of local (i.e. not inherited) methods in the class, including the local methods of its nested and anonymous classes.

#### Total Number of Local Public Methods (TNLPM) {#TNLPM}

**Class, Structure:** number of local (i.e. not inherited) public methods in the class, including the local methods of its nested and anonymous classes.

#### Total Number of Local Setters (TNLS) {#TNLS}

**Class, Structure:** number of local (i.e. not inherited) setter methods in the class, including the local setter methods of its nested and anonymous classes.

#### Total Number of Methods (TNM) {#TNM}

**Class, Structure:** number of methods in the class, including the inherited ones, as well as the inherited and local methods of its nested and anonymous classes. Methods that override abstract methods are not counted.

**Namespace:** number of methods in the namespace, including the methods of its subnamespaces.

**Component:** number of methods in the component, including the methods of its subcomponents.

#### Total Number of Packages (TNPKG) {#TNPKG}

**Namespace:** number of subnamespaces in the namespace, including all directly or indirectly contained subnamespaces.

**Component:** number of namespaces and subnamespaces that belong to the component, including its subcomponents.

**Namespace:** number of public attributes in the namespace, including the public attributes of its subnamespaces.

**Component:** number of public attributes in the component, including the public attributes of its subcomponents.

#### Total Number of Public Classes (TNPCL) {#TNPCL}

**Namespace:** number of public classes in the namespace, including the public classes of its subnamespaces.

**Component:** number of public classes in the component, including the public classes of its subcomponents.

#### Total Number of Public Enums (TNPEN) {#TNPEN}

**Namespace:** number of public enums in the namespace, including the public enums of its subnamespaces.

**Component:** number of public enums in the component, including the public enums of its subcomponents.

#### Total Number of Public Interfaces (TNPIN) {#TNPIN}

**Namespace:** number of public interfaces in the namespace, including the public interfaces of its subnamespaces.

**Component:** number of public interfaces in the component, including the public interfaces of its subcomponents.

#### Total Number of Public Methods (TNPM) {#TNPM}

**Class, Structure:** number of public methods in the class, including the inherited ones, as well as the inherited and local public methods of its nested and anonymous classes.

**Namespace:** number of public methods in the namespace, including the public methods of its subnamespaces.

**Component:** number of public methods in the component, including the public methods of its subcomponents.

#### Total Number of Public Structures (TNPST) {#TNPST}

**Namespace:** number of public structures in the namespace, including the public structures of its subnamespaces.

**Component:** number of public structures in the component, including the public structures of its subcomponents.

#### Total Number of Setters (TNS) {#TNS}

**Class, Structure:** number of setter methods in the class, including the inherited ones, as well as the inherited and local setter methods of its nested and anonymous classes.

**Namespace:** number of setter methods in the namespace, including the setter methods of its subnamespaces.

**Component:** number of setter methods in the component, including the setter methods of its subcomponents.

#### Total Number of Statements (TNOS) {#TNOS}

**Method:** number of statements in the method, including the statements of its anonymous classes.

**Class, Structure:** number of statements in the class, including the statements of its nested and anonymous classes.

**Namespace:** number of statements in the namespace, including the statements of its subnamespaces.

**Component:** number of statements in the component, including the statements of its subcomponents.

#### Total Number of Structures (TNST) {#TNST}

**Namespace:** number of structures in the namespace, including the structures of its subnamespaces.

**Component:** number of structures in the component, including the structures of its subcomponents.
