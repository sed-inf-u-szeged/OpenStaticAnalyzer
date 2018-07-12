## Reference of source code metrics

Source code metrics are used to quantify different source code characteristics. OpenStaticAnalyzer computes source code metrics for the following source code element kinds: components, source files, classes, methods and functions.

The calculated metrics are grouped into 4 categories, which are the following:

- **Complexity metrics:** measure the complexity of source code elements (typically algorithms).

- **Documentation metrics:** measure the amount of comments and documentation of source code elements in the system.

- **Inheritance metrics:** measure the different aspects of the inheritance hierarchy of the system.

- **Size metrics:** measure the basic properties of the analyzed system in terms of different cardinalities (e.g. number of code lines, number of classes or methods).

The following table summarizes the metrics, their abbreviations and their correspondence to different source code element kinds:

  Category               Metric name                     Abbreviation   Class   Component   File   Function   Method 
  ---------------------- ------------------------------- ------------- ------- ----------- ------ ---------- --------
  Complexity metrics     McCabe's Cyclomatic Complexity  McCC                              X      X          X       
                         Nesting Level                   NL            X                          X          X       
                         Nesting Level Else-If           NLE           X                          X          X       
                         Weighted Methods per Class      WMC           X                                             
  Documentation metrics  API Documentation               AD            X                                             
                         Comment Density                 CD            X                          X          X       
                         Comment Lines of Code           CLOC          X                   X      X          X       
                         Documentation Lines of Code     DLOC          X                          X          X       
                         Public Documented API           PDA           X                                             
                         Public Undocumented API         PUA           X                                             
                         Total API Documentation         TAD                   X                                     
                         Total Comment Density           TCD           X       X                  X          X       
                         Total Comment Lines of Code     TCLOC         X       X                  X          X       
                         Total Public Documented API     TPDA                  X                                     
                         Total Public Undocumented API   TPUA                  X                                     
  Inheritance metrics    Depth of Inheritance Tree       DIT           X                                             
                         Number of Ancestors             NOA           X                                             
                         Number of Children              NOC           X                                             
                         Number of Descendants           NOD           X                                             
  Size metrics           Lines of Code                   LOC           X                   X      X          X       
                         Logical Lines of Code           LLOC          X                   X      X          X       
                         Number of Getters               NG            X                                             
                         Number of Local Getters         NLG           X                                             
                         Number of Local Methods         NLM           X                                             
                         Number of Local Setters         NLS           X                                             
                         Number of Methods               NM            X                                             
                         Number of Parameters            NUMPAR                                   X          X       
                         Number of Setters               NS            X                                             
                         Number of Statements            NOS           X                          X          X       
                         Total Lines of Code             TLOC          X       X                  X          X       
                         Total Logical Lines of Code     TLLOC         X       X                  X          X       
                         Total Number of Classes         TNCL                  X                                     
                         Total Number of Directories     TNDI                  X                                     
                         Total Number of Files           TNFI                  X                                     
                         Total Number of Getters         TNG           X       X                                     
                         Total Number of Local Getters   TNLG          X                                             
                         Total Number of Local Methods   TNLM          X                                             
                         Total Number of Local Setters   TNLS          X                                             
                         Total Number of Methods         TNM           X       X                                     
                         Total Number of Setters         TNS           X       X                                     
                         Total Number of Statements      TNOS          X       X                  X          X       

### Complexity metrics

#### McCabe's Cyclomatic Complexity (McCC) {#McCC}

**Method, Function:** complexity of the method expressed as the number of independent control flow paths in it. It represents a lower bound for the number of possible execution paths in the source code and at the same time it is an upper bound for the minimum number of test cases needed for achieving full branch test coverage. The value of the metric is calculated as the number of the following instructions plus 1: if, else if, for, for...in, for...of, while, do-while, case label (which belongs to a switch instruction), catch clause, conditional expression (?:). Moreover, logical “and” (&amp;&amp;) and logical “or” (||) expressions also add 1 to the value because their short-circuit evaluation can cause branching depending on the first operand. The following instructions are not included: else, switch, try, finally.

**File:** complexity of the file expressed as the number of independent control flow paths in it. It is calculated as the sum of the McCabe’s Cyclomatic Complexity values of the methods can be found in the file.


#### Nesting Level (NL) {#NL}

**Method, Function:** complexity of the method/function expressed as the depth of the maximum embeddedness of its conditional, iteration  and exception handling block scopes. The following instructions are taken into account: if, else-if, else, for, for-in, for-of, while, do-while, switch, try, catch, finally and block statements that are directly inside another block statement. The following instructions do not increase the value by themselves; however, if additional embeddedness can be found in their blocks, they are considered: case and default label (which belong to a switch instruction).

**Class:** complexity of the class expressed as the depth of the maximum embeddedness of its conditional and iteration block scopes. It is calculated as the maximum nesting level (NL) of its local methods.


#### Nesting Level Else-If (NLE) {#NLE}
**Method, Function:** complexity of the method/function expressed as the depth of the maximum embeddedness of its conditional and iteration block scopes, where in the if-else-if construct only the first if instruction is considered. The following instructions are taken into account: if, for, while, conditional expression. The following instructions do not increase the value by themselves; however, if additional embeddedness can be found in their blocks, they are considered: else, else if (i.e. in the if-else-if construct the use of else-if does not increase the value of the metric), try, except, finally.

**Class:** complexity of the class expressed as the depth of the maximum embeddedness of its conditional and iteration block scopes, where in the if-else-if construct only the first if instruction is considered. It is calculated as the maximum nesting level (NLE) of its local methods.


#### Weighted Methods per Class (WMC) {#WMC}

**Class:** complexity of the class expressed as the number of independent control flow paths in it. It is calculated as the sum of the McCabe’s Cyclomatic Complexity (McCC) values of its local methods.


### Documentation metrics

#### API Documentation (AD) {#AD}
**Class:** ratio of the number of documented methods in the class +1 if the class itself is documented to the number of all methods in the class + 1 (the class itself).

#### Comment Density (CD) {#CD}
**Method, Function:** ratio of the comment lines of the method/function (CLOC) to the sum of its comment (CLOC) and logical lines of code (LLOC).

**Class:** ratio of the comment lines of the class (CLOC) to the sum of its comment (CLOC) and logical lines of code (LLOC).


#### Comment Lines of Code (CLOC) {#CLOC}
**Method, Function:** number of comment and documentation code lines of the method/function; however, its anonymous and local classes are not included.

**Class:** number of comment and documentation code lines of the class, including its local methods and attributes; however, its nested, anonymous, and local classes are not included.

**File:** number of comment and documentation code lines of the file.


#### Documentation Lines of Code (DLOC) {#DLOC}

**Method, Function:** number of documentation code lines of the method/function.

**Class:** number of documentation code lines of the class, including its local methods and attributes; however, its nested, anonymous, and local classes are not included.


#### Public Documented API (PDA) {#PDA}

**Class:** number of documented methods in the class (+1 if the class itself is documented); however, the methods of its nested, anonymous, and local classes are not counted.


#### Public Undocumented API (PUA) {#PUA}
**Class:** number of undocumented methods in the class (+1 if the class itself is undocumented); however, the methods of its nested, anonymous, and local classes are not counted.


#### Total API Documentation (TAD) {#TAD}
 
**Component:** ratio of the number of documented classes and methods in the component to the number of all of its classes and methods, including its subcomponents.


#### Total Comment Density (TCD) {#TCD}

**Method/Function:** ratio of the total comment lines of the method/function (TCLOC) to the sum of its total comment (TCLOC) and total logical lines of code (TLLOC).

**Class:** ratio of the total comment lines of the class (TCLOC) to the sum of its total comment (TCLOC) and total logical lines of code (TLLOC).

**Component:** ratio of the total comment lines of the component (TCLOC) to the sum of its total comment (TCLOC) and total logical lines of code (TLLOC).


#### Total Comment Lines of Code (TCLOC) {#TCLOC}

**Method/Function:** number of comment and documentation code lines of the method/function, including its local classes.

**Class:** number of comment and documentation code lines of the class, including its local methods and attributes, as well as its nested and local classes.

**Component:** number of comment and documentation code lines of the component, including its subcomponents.


#### Total Public Documented API (TPDA) {#TPDA}

**Component:** number of documented classes and methods in the component, including the documented classes and methods of its subcomponents.


#### Total Public Undocumented API (TPUA) {#TPUA}

**Component:** number of undocumented classes and methods in the component, including the undocumented classes and methods of its subcomponents.


### Inheritance metrics

#### Depth of Inheritance Tree (DIT) {#DIT}

**Class:** length of the path that leads from the class to its farthest ancestor in the inheritance tree.


#### Number of Ancestors (NOA) {#NOA}

**Class:** number of classes from which the class is directly or indirectly inherited.


#### Number of Children (NOC) {#NOC}

**Class:** number of classes which are directly derived from the class.


#### Number of Descendants (NOD) {#NOD}

**Class:** number of classes which are directly or indirectly derived from the class.


### Size metrics

#### Lines of Code (LOC) {#LOC}

**Method, Function:** number of code lines of the method/function, including empty and comment lines; however, its anonymous and local classes are not included.

**Class:** number of code lines of the class, including empty and comment lines, as well as its local methods; however, its nested, anonymous, and local classes are not included.

**File:** number of code lines of the file, including empty and comment lines.


#### Logical Lines of Code (LLOC) {#LLOC}

**Method, Function:** number of non-empty and non-comment code lines of the method/function; however, its anonymous and local functions are not included.

**Class:** number of non-empty and non-comment code lines of the class, including the non-empty and non-comment lines of its local methods; however, its nested, anonymous, and local classes are not included.

**File:** number of non-empty and non-comment code lines of the file.


#### Number of Getters (NG) {#NG}

**Class:** number of getter methods in the class, including the inherited ones.


#### Number of Local Getters (NLG) {#NLG}

**Class:** number of local (i.e. not inherited) getter methods in the class; however, the getter methods of its nested, anonymous, and local classes are not included. Methods that override abstract methods are not counted.


#### Number of Local Methods (NLM) {#NLM}

**Class:** number of local (i.e. not inherited) methods in the class.


#### Number of Local Setters (NLS) {#NLS}

**Class:** number of local (i.e. not inherited) setter methods in the class.


#### Number of Methods (NM) {#NM}

**Class:** number of methods in the class, including the inherited ones.


#### Number of Parameters (NUMPAR) {#NUMPAR}

**Method, Function:** number of the parameters of the method. Counts only the explicitly given number of parameters ('arguments' object is not counted).


#### Number of Setters (NS) {#NS}

**Class:** number of setter methods in the class, including the inherited ones.


#### Number of Statements (NOS) {#NOS}

**Method, Function:** number of statements in the method.

**Class:** number of statements in the class.

**File:** number of statements in the file.


#### Total Lines of Code (TLOC) {#TLOC}

**Method, Function:** number of code lines of the method/function, including empty and comment lines, as well as its nested functions.

**Class:** number of code lines of the class, including empty and comment lines, as well as its nested and local classes.

**Component:** number of code lines of the component, including empty and comment lines, as well as its subcomponents.


#### Total Logical Lines of Code (TLLOC) {#TLLOC}

**Method, Function:** number of non-empty and non-comment code lines of the method/function, including the non-empty and non-comment lines of its nested functions.

**Class:** number of non-empty and non-comment code lines of the class, including the non-empty and non-comment code lines of its nested and local classes.

**Component:** number of non-empty and non-comment code lines of the component, including its subcomponents.


#### Total Number of Classes (TNCL) {#TNCL}

**Component:** number of classes in the component, including the classes of its subcomponents.


#### Total Number of Directories (TNDI) {#TNDI}

**Component:** number of directories that belong to the component, including its subcomponents.


#### Total Number of Files (TNFI) {#TNFI}

**Component:** number of files that belong to the component, including its subcomponents.


#### Total Number of Getters (TNG) {#TNG}

**Class:** number of getter methods in the class, including the inherited ones, as well as the inherited and local getter methods of its nested, anonymous and local classes.

**Component:** number of getter methods in the component, including the getter methods of its subcomponents.


#### Total Number of Local Getters (TNLG) {#TNLG}

**Class:** number of local (i.e. not inherited) getter methods in the class, including the local getter methods of its nested, anonymous, and local classes.


#### Total Number of Local Methods (TNLM) {#TNLM}

**Class:** number of local (i.e. not inherited) methods in the class, including the local methods of its nested and local classes.


#### Total Number of Local Setters (TNLS) {#TNLS}

**Class:** number of local (i.e. not inherited) setter methods in the class, including the local setter methods of its nested, anonymous, and local classes.


#### Total Number of Methods (TNM) {#TNM}

**Class:** number of methods in the class, including the inherited ones, as well as the inherited and local methods of its nested, anonymous, and local classes.

**Component:** number of methods in the component, including the methods of its subcomponents.


#### Total Number of Setters (TNS) {#TNS}

**Class:** number of setter methods in the class, including the inherited ones, as well as the inherited and local setter methods of its nested, anonymous and local classes.

**Component:** number of setter methods in the component, including the setter methods of its subcomponents.


#### Total Number of Statements (TNOS) {#TNOS}

**Method, Function:** number of statements in the method/function, including the statements of its nested functions.Class: number of statements in the class, including the statements of its nested and local classes.Component: number of statements in the component, including the statements of its subcomponents.


