## Reference of code duplication metrics

Code cloning (or copy-paste programming) means the copying of an existing piece of source code, pasting it somewhere else, and typically performing smaller modifications on it. Based on the level of similarity between the copied code fragments we can define the following duplication types:

- **Type-1**: the copied code parts are identical code fragments except for variations in whitespace, layout and comments.

- **Type-2**: syntactically identical fragments except for variations in identifier names, literals, type references, whitespace, layout and comments.

- **Type-3**: copied fragments with further modifications such as altered, added, or removed statements, in addition to variations in identifier names, literals, type references, whitespace, layout and comments.

- **Type-4**: the copied code fragments are syntactically different, but they perform the same functionality, i.e. they are semantically the same.

OpenStaticAnalyzer is capable of identifying Type-2 clones, i.e. code fragments that are structurally identical, but may differ in variable names, literals, identifiers, etc.

Two code segments correspond to each other if they are copies of each other. This relation is an equivalence relation and we use the notion of clone classes to the classes of the relation, and the members of the classes will be referred to as clone instances. Owing to the nature of the relation, each clone class must contain at least two clone instances.

Clones are tracked during the source code analysis of consecutive revisions of the analyzed software system. OpenStaticAnalyzer detects suspicious, inconsistently changing code copies, which are called "clone smells". The smells concerning clone classes are the following:

- **Disappearing Clone Class (DCC):** The clone class existed in the previously analyzed revision but it does not exist anymore.

- **Appearing Clone Class (ACC):** The clone class did not exist in the previously analyzed revision.

The smells concerning clone instances are issued only if the containing clone class does not contain any smell. These are the following:

- **Disappearing Clone Instance (DCI):** The clone instance existed in the previously analyzed revision but it does not exist anymore.

- **Appearing Clone Instance (ACI):** The clone instance did not exist in the previously analyzed revision.

- **Moving Clone Instance (MCI):** The clone instance belonged to a different clone class in the previously analyzed revision than its current class.

The following table summarizes the code duplication metrics, their abbreviations, and their correspondence to different source code element types.

  Metric name                       Abbrev.   Clone Instance   Clone Class   Method   Class   Interface   Enum   Package   Comp.  
  --------------------------------- -------- ---------------- ------------- -------- ------- ----------- ------ --------- ------- 
  Clone Age                         CA       X                X                                                                   
  Clone Classes                     CCL                                     X        X       X           X      X         X       
  Clone Complexity                  CCO      X                X             X        X       X           X      X         X       
  Clone Coverage                    CC                                      X        X       X           X      X         X       
  Clone Elimination Effort          CEE                       X                                                           X       
  Clone Elimination Gain            CEG                       X                                                           X       
  Clone Embeddedness                CE       X                X                                                                   
  Clone Instances                   CI                        X             X        X       X           X      X         X       
  Clone Line Coverage               CLC                                     X        X       X           X      X         X       
  Clone Lines of Code               CLLOC    X                X                                                                   
  Clone Logical Line Coverage       CLLC                                    X        X       X           X      X         X       
  Clone Risk                        CR                        X                                                           X       
  Clone Variability                 CV       X                X                                                                   
  Lines of Duplicated Code          LDC                                     X        X       X           X      X         X       
  Logical Lines of Duplicated Code  LLDC                                    X        X       X           X      X         X       
  Normalized Clone Radius           NCR                       X                                                           X       

### Clone metrics

#### Clone Age (CA) {#CA}

**Clone class/clone instance:** number of previously analyzed revisions in which the clone class/clone instance was present + 1.

#### Clone Classes (CCL) {#CCL}

**Method/class/package:** number of clone classes having at least one clone instance in the source code element.

**Component:** number of clone classes having at least one clone instance in the component.

#### Clone Complexity (CCO) {#CCO}

**Clone instance:** the McCabe complexity of the code fragment corresponding to the clone instance.

**Clone class:** sum of CCO of clone instances in the clone class.

**Method/class/package:** sum of CCO of clone instances in the source code element.

**Component:** sum of CCO of clone instances in the component.

#### Clone Coverage (CC) {#CC}

**Method/class/package:** ratio of code covered by code duplications in the source code element to the size of the source code element, expressed in terms of the number of syntactic entities (statements, expressions, etc.).

**Component:** ratio of code covered by code duplications in the component to the size of the component, expressed in terms of the number of syntactic entities (statements, expressions, etc.).

#### Clone Elimination Effort (CEE) {#CEE}

**Clone class:** index of the effort required to eliminate the clone class. It is computed as the product of CI, CE, and NCR.

**Component:** index of the effort required to eliminate all clones from the component. It is computed as the sum of CEE of the clone classes in the component.

#### Clone Elimination Gain (CEG) {#CEG}

**Clone class:** index of the gain resulting from eliminating the clone class. It is computed as the ratio of CR to CEE.

**Component:** index of the gain resulting from eliminating all clones from the component. It is computed as the logistic function of the ratio of CR to CEE.

#### Clone Embeddedness (CE) {#CE}

**Clone instance:** sum of incoming and outgoing references (function calls, variable references, type references; different references to the same entity are counted only once) in the code fragment corresponding to the clone instance, weighted with the number of directory changes between the referenced code fragments.

**Clone class:** sum of CE of the clone instances of the clone class + 1.

#### Clone Instances (CI) {#CI}

**Method/class/package:** number of clone instances in the source code element.

**Component:** number of clone instances in the component.

**Clone class:** number of clone instances in the clone class.

#### Clone Line Coverage (CLC) {#CLC}

**Method/class/package:** ratio of code covered by code duplications in the source code element to the size of the source code element, expressed in terms of lines of code.

**Component:** ratio of code covered by code duplications in the component to the size of the component, expressed in terms of lines of code.

#### Clone Lines of Code (CLLOC) {#CLLOC}

**Clone instance:** length of the clone instance expressed in terms of lines of code.

**Clone class:** average of CLLOC of clone instances belonging to the clone class.

#### Clone Logical Line Coverage (CLLC) {#CLLC}

**Method/class/package:** ratio of code covered by code duplications in the source code element to the size of source code element, expressed in terms of logical lines of code (non-empty, non-comment lines).

**Component:** ratio of code covered by code duplications in the component to the size of the component, expressed in terms of logical lines of code (non-empty, non-comment lines).

#### Clone Risk (CR) {#CR}

**Clone class:** risk index of the existence of the clone class. It is computed as the product of CLLOC, CI, CCO, NCR, and CV.

**Component:** relative risk index of the existence of code duplications in the component. It is computed as the sum of CR of the clone classes in the component, divided by the total logical lines of code (non-empty, non-comment lines) of the component. It expresses the risk index projected to a non-empty, non-comment line of code in the component.

#### Clone Variability (CV) {#CV}

**Clone instance:** instability of the clone instance since it appeared. It is computed as the ratio of the number of previously analyzed revisions when the instance had been changed to its age (CA).

**Clone class:** instability of the clone class since it appeared. It is computed as the ratio of the number of previously analyzed revisions when its contained instances were moved, deleted, or added, to its age (CA), plus the average CV of its clone instances.

#### Lines of Duplicated Code (LDC) {#LDC}

**Method/class/package:** number of code lines covered by code duplications in the source code element.

**Component:** number of code lines covered by code duplications in the component.

#### Logical Lines of Duplicated Code (LLDC) {#LLDC}

**Method/class/package:** number of logical code lines (non-empty, non-comment lines) covered by code duplications in the source code element.

**Component:** The number of logical code lines (non-empty, non-comment lines) covered by code duplications in the component.

#### Normalized Clone Radius (NCR) {#NCR}

**Clone class:** normalized average distance among clone instances belonging to the clone class, expressed in terms of number of directory changes.

**Component:** average of NCR of the clone classes in the component.
