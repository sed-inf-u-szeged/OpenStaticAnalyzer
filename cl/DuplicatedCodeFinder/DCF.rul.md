# ToolDescription
## Default
### ID=DCF
### Description
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

# Includes
- general_metadata.md

# Metrics
## CA
### Default
#### Enabled=true
#### NumericType=true
#### Warning=false
#### DisplayName=Clone Age
#### HelpText


#### Tags
- /general/Clone
- /internal/csv_column
- /internal/metric_group/Clone
- /tool/OpenStaticAnalyzer/DCF

#### Settings
- Max=0
- Min=0

### c -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone class/clone instance:** number of previously analyzed revisions in which the clone class/clone instance was present + 1.

#### Calculated
- CloneClass
- CloneInstance

#### Tags

### cpp -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone class/clone instance:** number of previously analyzed revisions in which the clone class/clone instance was present + 1.

#### Calculated
- CloneClass
- CloneInstance

#### Tags

### csharp -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone class/clone instance:** number of previously analyzed revisions in which the clone class/clone instance was present + 1.

#### Calculated
- CloneClass
- CloneInstance

#### Tags

### java -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone class/clone instance:** number of previously analyzed revisions in which the clone class/clone instance was present + 1.

#### Calculated
- CloneClass
- CloneInstance

#### Tags

### javascript -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone class, clone instance:** number of previously analyzed revisions in which the clone class/clone instance was present + 1.

#### Calculated
- CloneClass
- CloneInstance

#### Tags

### python -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone class/clone instance:** number of previously analyzed revisions in which the clone class/clone instance was present + 1.

#### Calculated
- CloneClass
- CloneInstance

#### Tags

### rpg -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone class/clone instance:** number of previously analyzed revisions in which the clone class/clone instance was present + 1.

#### Calculated
- CloneClass
- CloneInstance

#### Tags


## CC
### Default
#### Enabled=true
#### NumericType=true
#### Warning=false
#### DisplayName=Clone Coverage
#### HelpText


#### Tags
- /general/Clone
- /internal/csv_column
- /internal/metric_group/Clone
- /tool/OpenStaticAnalyzer/DCF

#### Settings
- Max=0
- Min=0

### c -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Method/class/package:** ratio of code covered by code duplications in the source code element to the size of the source code element, expressed in terms of the number of syntactic entities (statements, expressions, etc.).
  **Component:** ratio of code covered by code duplications in the component to the size of the component, expressed in terms of the number of syntactic entities (statements, expressions, etc.).

#### Calculated
- Component
- Enum
- Function
- Structure
- Union

#### Tags

### cpp -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Method/Function/Union/Enum/class/Structure/Namespace:** ratio of code covered by code duplications in the source code element to the size of the source code element, expressed in terms of the number of syntactic entities (statements, expressions, etc.).
  **Component:** ratio of code covered by code duplications in the component to the size of the component, expressed in terms of the number of syntactic entities (statements, expressions, etc.).

#### Calculated
- Class
- Component
- Enum
- Function
- Interface
- Method
- Namespace
- Structure
- Union

#### Tags

### csharp -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Method/Interface/Enum/class/Structure/Namespace:** ratio of code covered by code duplications in the source code element to the size of the source code element, expressed in terms of the number of syntactic entities (statements, expressions, etc.).
  **Component:** ratio of code covered by code duplications in the component to the size of the component, expressed in terms of the number of syntactic entities (statements, expressions, etc.).

#### Calculated
- Class
- Component
- Enum
- Interface
- Method
- Namespace
- Structure

#### Tags

### java -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Method/class/package:** ratio of code covered by code duplications in the source code element to the size of the source code element, expressed in terms of the number of syntactic entities (statements, expressions, etc.).
  **Component:** ratio of code covered by code duplications in the component to the size of the component, expressed in terms of the number of syntactic entities (statements, expressions, etc.).

#### Calculated
- Annotation
- Class
- Component
- Enum
- Interface
- Method
- Package

#### Tags

### javascript -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Method, function, class:** ratio of code covered by code duplications in the source code element to the size of the source code element, expressed in terms of the number of syntactic entities (statements, expressions, etc.).

  **Component:** ratio of code covered by code duplications in the component to the size of the component, expressed in terms of the number of syntactic entities (statements, expressions, etc.).

#### Calculated
- Class
- Component
- Function
- Method

#### Tags

### python -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Function/method/class/module/package:** ratio of code covered by code duplications in the source code element to the size of the source code element, expressed in terms of the number of syntactic entities (statements, expressions, etc.).
  **Component:** ratio of code covered by code duplications in the component to the size of the component, expressed in terms of the number of syntactic entities (statements, expressions, etc.).

#### Calculated
- Class
- Component
- Function
- Method
- Module
- Package

#### Tags

### rpg -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Subroutine/procedure/program/system:** ratio of code covered by code duplications in the source code element to the size of the source code element, expressed in terms of the number of syntactic entities (statements, expressions, etc.).
  **Component:** ratio of code covered by code duplications in the component to the size of the component, expressed in terms of the number of syntactic entities (statements, expressions, etc.).

#### Calculated
- Component
- Procedure
- Program
- Subroutine
- System

#### Tags


## CCL
### Default
#### Enabled=true
#### NumericType=true
#### Warning=false
#### DisplayName=Clone Classes
#### HelpText


#### Tags
- /general/Clone
- /internal/csv_column
- /internal/metric_group/Clone
- /tool/OpenStaticAnalyzer/DCF

#### Settings
- Max=0
- Min=0

### c -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Method:** number of clone classes having at least one clone instance in the source code element.
  **Component:** number of clone classes having at least one clone instance in the component.

#### Calculated
- Component
- Enum
- Function
- Structure
- Union

#### Tags

### cpp -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Method/class/package:** number of clone classes having at least one clone instance in the source code element.
  **Component:** number of clone classes having at least one clone instance in the component.

#### Calculated
- Class
- Component
- Enum
- Function
- Interface
- Method
- Namespace
- Structure
- Union

#### Tags

### csharp -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Method/class/structure/interface/namespace:** number of clone classes having at least one clone instance in the source code element.
  **Component:** number of clone classes having at least one clone instance in the component.

#### Calculated
- Class
- Component
- Enum
- Interface
- Method
- Namespace
- Structure

#### Tags

### java -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Method/class/package:** number of clone classes having at least one clone instance in the source code element.
  **Component:** number of clone classes having at least one clone instance in the component.

#### Calculated
- Annotation
- Class
- Component
- Enum
- Interface
- Method
- Package

#### Tags

### javascript -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Method, function, class:** number of clone classes having at least one clone instance in the source code element.

  **Component:** number of clone classes having at least one clone instance in the component.

#### Calculated
- Class
- Component
- Function
- Method

#### Tags

### python -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Function/method/class/module/package:** number of clone classes having at least one clone instance in the source code element.
  **Component:** number of clone classes having at least one clone instance in the component.

#### Calculated
- Class
- Component
- Function
- Method
- Module
- Package

#### Tags

### rpg -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Subroutine/procedure/program/system:** number of clone classes having at least one clone instance in the source code element.
  **Component:** number of clone classes having at least one clone instance in the component.

#### Calculated
- Component
- Procedure
- Program
- Subroutine
- System

#### Tags


## CCO
### Default
#### Enabled=true
#### NumericType=true
#### Warning=false
#### DisplayName=Clone Complexity
#### HelpText


#### Tags
- /general/Clone
- /internal/csv_column
- /internal/metric_group/Clone
- /tool/OpenStaticAnalyzer/DCF

#### Settings
- Max=0
- Min=0

### c -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone instance:** the McCabe complexity of the code fragment corresponding to the clone instance.
  **Clone class:** sum of CCO of clone instances in the clone class.
  **Function/method/class/module/package:** sum of CCO of clone instances in the source code element.
  **Component:** sum of CCO of clone instances in the component.

#### Calculated
- CloneClass
- CloneInstance
- Component
- Enum
- Function
- Structure
- Union

#### Tags

### cpp -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone instance:** the McCabe complexity of the code fragment corresponding to the clone instance.
  **Clone class:** sum of CCO of clone instances in the clone class.
  **Function/method/class/module/package:** sum of CCO of clone instances in the source code element.
  **Component:** sum of CCO of clone instances in the component.

#### Calculated
- Class
- CloneClass
- CloneInstance
- Component
- Enum
- Function
- Interface
- Method
- Namespace
- Structure
- Union

#### Tags

### csharp -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone instance:** the McCabe complexity of the code fragment corresponding to the clone instance.
  **Clone class:** sum of CCO of clone instances in the clone class.
  **Method/class/interface/namespace/structure:** sum of CCO of clone instances in the source code element.
  **Component:** sum of CCO of clone instances in the component.

#### Calculated
- Class
- CloneClass
- CloneInstance
- Component
- Enum
- Interface
- Method
- Namespace
- Structure

#### Tags

### java -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone instance:** the McCabe complexity of the code fragment corresponding to the clone instance.
  **Clone class:** sum of CCO of clone instances in the clone class.
  **Method/class/package:** sum of CCO of clone instances in the source code element.
  **Component:** sum of CCO of clone instances in the component.

#### Calculated
- Annotation
- Class
- CloneClass
- CloneInstance
- Component
- Enum
- Interface
- Method
- Package

#### Tags

### javascript -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone instance:** the McCabe complexity of the code fragment corresponding to the clone instance.

  **Clone class:** sum of CCO of clone instances in the clone class.

  **Method, function, class:** sum of CCO of clone instances in the source code element.

  **Component:** sum of CCO of clone instances in the component.

#### Calculated
- Class
- CloneClass
- CloneInstance
- Component
- Function
- Method

#### Tags

### python -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone instance:** the McCabe complexity of the code fragment corresponding to the clone instance.
  **Clone class:** sum of CCO of clone instances in the clone class.
  **Function/method/class/module/package:** sum of CCO of clone instances in the source code element.
  **Component:** sum of CCO of clone instances in the component.

#### Calculated
- Class
- CloneClass
- CloneInstance
- Component
- Function
- Method
- Module
- Package

#### Tags

### rpg -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone instance:** the McCabe complexity of the code fragment corresponding to the clone instance.
  **Clone class:** sum of CCO of clone instances in the clone class.
  **Subroutine/procedure/program/system:** sum of CCO of clone instances in the source code element.
  **Component:** sum of CCO of clone instances in the component.

#### Calculated
- CloneClass
- CloneInstance
- Component
- Procedure
- Program
- Subroutine
- System

#### Tags


## CE
### Default
#### Enabled=true
#### NumericType=true
#### Warning=false
#### DisplayName=Clone Embeddedness
#### HelpText


#### Tags
- /general/Clone
- /internal/csv_column
- /internal/metric_group/Clone
- /tool/OpenStaticAnalyzer/DCF

#### Settings
- Max=0
- Min=0

### c -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone instance:** sum of incoming and outgoing references (function calls, variable references, type references; different references to the same entity are counted only once) in the code fragment corresponding to the clone instance, weighted with the number of directory changes between the referenced code fragments.
  **Clone class:** sum of CE of the clone instances of the clone class + 1.

#### Calculated
- CloneClass
- CloneInstance

#### Tags

### cpp -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone instance:** sum of incoming and outgoing references (function calls, variable references, type references; different references to the same entity are counted only once) in the code fragment corresponding to the clone instance, weighted with the number of directory changes between the referenced code fragments.
  **Clone class:** sum of CE of the clone instances of the clone class + 1.

#### Calculated
- CloneClass
- CloneInstance

#### Tags

### csharp -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone instance:** sum of incoming and outgoing references (function calls, variable references, type references; different references to the same entity are counted only once) in the code fragment corresponding to the clone instance, weighted with the number of directory changes between the referenced code fragments.
  **Clone class:** sum of CE of the clone instances of the clone class + 1.

#### Calculated
- CloneClass
- CloneInstance

#### Tags

### java -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone instance:** sum of incoming and outgoing references (function calls, variable references, type references; different references to the same entity are counted only once) in the code fragment corresponding to the clone instance, weighted with the number of directory changes between the referenced code fragments.
  **Clone class:** sum of CE of the clone instances of the clone class + 1.

#### Calculated
- CloneClass
- CloneInstance

#### Tags

### javascript -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone instance:** sum of incoming and outgoing references (function calls, variable references, type references; different references to the same entity are counted only once) in the code fragment corresponding to the clone instance, weighted with the number of directory changes between the referenced code fragments.

  **Clone class:** sum of CE of the clone instances of the clone class + 1.

#### Calculated
- CloneClass
- CloneInstance

#### Tags

### python -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone instance:** sum of incoming and outgoing references (function calls, variable references, type references; different references to the same entity are counted only once) in the code fragment corresponding to the clone instance, weighted with the number of directory changes between the referenced code fragments.
  **Clone class:** sum of CE of the clone instances of the clone class + 1.

#### Calculated
- CloneClass
- CloneInstance

#### Tags

### rpg -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone instance:** sum of incoming and outgoing references (subroutine calls, procedure calls, variable references; different references to the same entity are counted only once) in the code fragment corresponding to the clone instance, weighted with the number of directory changes between the referenced code fragments.
  **Clone class:** sum of CE of the clone instances of the clone class + 1.

#### Calculated
- CloneClass
- CloneInstance

#### Tags


## CEE
### Default
#### Enabled=true
#### NumericType=true
#### Warning=false
#### DisplayName=Clone Elimination Effort
#### HelpText


#### Tags
- /general/Clone
- /internal/csv_column
- /internal/metric_group/Clone
- /tool/OpenStaticAnalyzer/DCF

#### Settings
- Max=0
- Min=0

### c -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone class:** index of the effort required to eliminate the clone class. It is computed as the product of CI, CE, and NCR.
  **Component:** index of the effort required to eliminate all clones from the component. It is computed as the sum of CEE of the clone classes in the component.

#### Calculated
- CloneClass
- Component

#### Tags

### cpp -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone class:** index of the effort required to eliminate the clone class. It is computed as the product of CI, CE, and NCR.
  **Component:** index of the effort required to eliminate all clones from the component. It is computed as the sum of CEE of the clone classes in the component.

#### Calculated
- CloneClass
- Component

#### Tags

### csharp -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone class:** index of the effort required to eliminate the clone class. It is computed as the product of CI, CE, and NCR.
  **Component:** index of the effort required to eliminate all clones from the component. It is computed as the sum of CEE of the clone classes in the component.

#### Calculated
- CloneClass
- Component

#### Tags

### java -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone class:** index of the effort required to eliminate the clone class. It is computed as the product of CI, CE, and NCR.
  **Component:** index of the effort required to eliminate all clones from the component. It is computed as the sum of CEE of the clone classes in the component.

#### Calculated
- CloneClass
- Component

#### Tags

### javascript -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone class:** index of the effort required to eliminate the clone class. It is computed as the product of CI, CE, and NCR.

  **Component:** index of the effort required to eliminate all clones from the component. It is computed as the sum of CEE of the clone classes in the component.

#### Calculated
- CloneClass
- Component

#### Tags

### python -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone class:** index of the effort required to eliminate the clone class. It is computed as the product of CI, CE, and NCR.
  **Component:** index of the effort required to eliminate all clones from the component. It is computed as the sum of CEE of the clone classes in the component.

#### Calculated
- CloneClass
- Component

#### Tags

### rpg -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone class:** index of the effort required to eliminate the clone class. It is computed as the product of CI, CE, and NCR.
  **Component:** index of the effort required to eliminate all clones from the component. It is computed as the sum of CEE of the clone classes in the component.

#### Calculated
- CloneClass
- Component

#### Tags


## CEG
### Default
#### Enabled=true
#### NumericType=true
#### Warning=false
#### DisplayName=Clone Elimination Gain
#### HelpText


#### Tags
- /general/Clone
- /internal/csv_column
- /internal/metric_group/Clone
- /tool/OpenStaticAnalyzer/DCF

#### Settings
- Max=0
- Min=0

### c -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone class:** index of the gain resulting from eliminating the clone class. It is computed as the ratio of CR to CEE.
  **Component:** index of the gain resulting from eliminating all clones from the component. It is computed as the logistic function of the ratio of CR to CEE.

#### Calculated
- CloneClass
- Component

#### Tags

### cpp -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone class:** index of the gain resulting from eliminating the clone class. It is computed as the ratio of CR to CEE.
  **Component:** index of the gain resulting from eliminating all clones from the component. It is computed as the logistic function of the ratio of CR to CEE.

#### Calculated
- CloneClass
- Component

#### Tags

### csharp -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone class:** index of the gain resulting from eliminating the clone class. It is computed as the ratio of CR to CEE.
  **Component:** index of the gain resulting from eliminating all clones from the component. It is computed as the logistic function of the ratio of CR to CEE.

#### Calculated
- CloneClass
- Component

#### Tags

### java -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone class:** index of the gain resulting from eliminating the clone class. It is computed as the ratio of CR to CEE.
  **Component:** index of the gain resulting from eliminating all clones from the component. It is computed as the logistic function of the ratio of CR to CEE.

#### Calculated
- CloneClass
- Component

#### Tags

### javascript -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone class:** index of the gain resulting from eliminating the clone class. It is computed as the ratio of CR to CEE. Component: index of the gain resulting from eliminating all clones from the component. It is computed as the logistic function of the ratio of CR to CEE.

#### Calculated
- CloneClass
- Component

#### Tags

### python -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone class:** index of the gain resulting from eliminating the clone class. It is computed as the ratio of CR to CEE.
  **Component:** index of the gain resulting from eliminating all clones from the component. It is computed as the logistic function of the ratio of CR to CEE.

#### Calculated
- CloneClass
- Component

#### Tags

### rpg -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone class:** index of the gain resulting from eliminating the clone class. It is computed as the ratio of CR to CEE.
  **Component:** index of the gain resulting from eliminating all clones from the component. It is computed as the logistic function of the ratio of CR to CEE.

#### Calculated
- CloneClass
- Component

#### Tags


## CI
### Default
#### Enabled=true
#### NumericType=true
#### Warning=false
#### DisplayName=Clone Instances
#### HelpText


#### Tags
- /general/Clone
- /internal/csv_column
- /internal/metric_group/Clone
- /tool/OpenStaticAnalyzer/DCF

#### Settings
- Max=0
- Min=0

### c -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Structure/Union/Enum/Function:** number of clone instances in the source code element.
  **Component:** number of clone instances in the component.
  **Clone class:** number of clone instances in the clone class.

#### Calculated
- CloneClass
- Component
- Enum
- Function
- Structure
- Union

#### Tags

### cpp -> Default
#### Enabled=true
#### HelpText
  **Method/class/package:** number of clone instances in the source code element.
  **Component:** number of clone instances in the component.
  **Clone class:** number of clone instances in the clone class.

#### Calculated
- Class
- CloneClass
- Component
- Enum
- Function
- Interface
- Method
- Namespace
- Structure
- Union

#### Tags

### csharp -> Default
#### Enabled=true
#### HelpText
  **Method/class/Namespace:** number of clone instances in the source code element.
  **Component:** number of clone instances in the component.
  **Clone class:** number of clone instances in the clone class.

#### Calculated
- Class
- CloneClass
- Component
- Enum
- Interface
- Method
- Namespace
- Structure

#### Tags

### java -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Method/class/package:** number of clone instances in the source code element.
  **Component:** number of clone instances in the component.
  **Clone class:** number of clone instances in the clone class.

#### Calculated
- Annotation
- Class
- CloneClass
- Component
- Enum
- Interface
- Method
- Package

#### Tags

### javascript -> Default
#### Enabled=true
#### HelpText
  **Method, function, class:** number of clone instances in the source code element.

  **Component:** number of clone instances in the component.

  **Clone class:** number of clone instances in the clone class.

#### Calculated
- Class
- CloneClass
- Component
- Function
- Method

#### Tags

### python -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Function/method/class/module/package:** number of clone instances in the source code element.
  **Component:** number of clone instances in the component.
  **Clone class:** number of clone instances in the clone class.

#### Calculated
- Class
- CloneClass
- Component
- Function
- Method
- Module
- Package

#### Tags

### rpg -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Subroutine/procedure/program/system:** number of clone instances in the source code element.
  **Component:** number of clone instances in the component.
  **Clone class:** number of clone instances in the clone class.

#### Calculated
- CloneClass
- Component
- Procedure
- Program
- Subroutine
- System

#### Tags


## CLC
### Default
#### Enabled=true
#### NumericType=true
#### Warning=false
#### DisplayName=Clone Line Coverage
#### HelpText


#### Tags
- /general/Clone
- /internal/csv_column
- /internal/metric_group/Clone
- /tool/OpenStaticAnalyzer/DCF

#### Settings
- Max=0
- Min=0

### c -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Function/method/class/module/package:** ratio of code covered by code duplications in the source code element to the size of the source code element, expressed in terms of lines of code.
  **Component:** ratio of code covered by code duplications in the component to the size of the component, expressed in terms of lines of code.

#### Calculated
- Component
- Enum
- Function
- Structure
- Union

#### Tags

### cpp -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Function/method/class/module/package:** ratio of code covered by code duplications in the source code element to the size of the source code element, expressed in terms of lines of code.
  **Component:** ratio of code covered by code duplications in the component to the size of the component, expressed in terms of lines of code.

#### Calculated
- Class
- Component
- Enum
- Function
- Interface
- Method
- Namespace
- Structure
- Union

#### Tags

### csharp -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Method/class/interface/namespace:** ratio of code covered by code duplications in the source code element to the size of the source code element, expressed in terms of lines of code.
  **Component:** ratio of code covered by code duplications in the component to the size of the component, expressed in terms of lines of code.

#### Calculated
- Class
- Component
- Enum
- Interface
- Method
- Namespace
- Structure

#### Tags

### java -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Method/class/package:** ratio of code covered by code duplications in the source code element to the size of the source code element, expressed in terms of lines of code.
  **Component:** ratio of code covered by code duplications in the component to the size of the component, expressed in terms of lines of code.

#### Calculated
- Annotation
- Class
- Component
- Enum
- Interface
- Method
- Package

#### Tags

### javascript -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Method, function, class:** ratio of code covered by code duplications in the source code element to the size of the source code element, expressed in terms of lines of code.

  **Component:** ratio of code covered by code duplications in the component to the size of the component, expressed in terms of lines of code.

#### Calculated
- Class
- Component
- Function
- Method

#### Tags

### python -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Function/method/class/module/package:** ratio of code covered by code duplications in the source code element to the size of the source code element, expressed in terms of lines of code.
  **Component:** ratio of code covered by code duplications in the component to the size of the component, expressed in terms of lines of code.

#### Calculated
- Class
- Component
- Function
- Method
- Module
- Package

#### Tags

### rpg -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Subroutine/procedure/program/system:** ratio of code covered by code duplications in the source code element to the size of the source code element, expressed in terms of lines of code.
  **Component:** ratio of code covered by code duplications in the component to the size of the component, expressed in terms of lines of code.

#### Calculated
- Component
- Procedure
- Program
- Subroutine
- System

#### Tags


## CLLC
### Default
#### Enabled=true
#### NumericType=true
#### Warning=false
#### DisplayName=Clone Logical Line Coverage
#### HelpText


#### Tags
- /general/Clone
- /internal/csv_column
- /internal/metric_group/Clone
- /tool/OpenStaticAnalyzer/DCF

#### Settings
- Max=0
- Min=0

### c -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Function/method/class/module/package:** ratio of code covered by code duplications in the source code element to the size of source code element, expressed in terms of logical lines of code (non-empty, non-comment lines).
  **Component:** ratio of code covered by code duplications in the component to the size of the component, expressed in terms of logical lines of code (non-empty, non-comment lines).

#### Calculated
- Component
- Enum
- Function
- Structure
- Union

#### Tags

### cpp -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Function/method/class/module/package:** ratio of code covered by code duplications in the source code element to the size of source code element, expressed in terms of logical lines of code (non-empty, non-comment lines).
  **Component:** ratio of code covered by code duplications in the component to the size of the component, expressed in terms of logical lines of code (non-empty, non-comment lines).

#### Calculated
- Class
- Component
- Enum
- Function
- Interface
- Method
- Namespace
- Structure
- Union

#### Tags

### csharp -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Method/class/module/namespace:** ratio of code covered by code duplications in the source code element to the size of source code element, expressed in terms of logical lines of code (non-empty, non-comment lines).
  **Component:** ratio of code covered by code duplications in the component to the size of the component, expressed in terms of logical lines of code (non-empty, non-comment lines).

#### Calculated
- Class
- Component
- Enum
- Interface
- Method
- Namespace
- Structure

#### Tags

### java -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Method/class/package:** ratio of code covered by code duplications in the source code element to the size of source code element, expressed in terms of logical lines of code (non-empty, non-comment lines).
  **Component:** ratio of code covered by code duplications in the component to the size of the component, expressed in terms of logical lines of code (non-empty, non-comment lines).

#### Calculated
- Annotation
- Class
- Component
- Enum
- Interface
- Method
- Package

#### Tags

### javascript -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Method, function, class:** ratio of code covered by code duplications in the source code element to the size of source code element, expressed in terms of logical lines of code (non-empty, non-comment lines).

  **Component:** ratio of code covered by code duplications in the component to the size of the component, expressed in terms of logical lines of code (non-empty, non-comment lines).

#### Calculated
- Class
- Component
- Function
- Method

#### Tags

### python -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Function/method/class/module/package:** ratio of code covered by code duplications in the source code element to the size of source code element, expressed in terms of logical lines of code (non-empty, non-comment lines).
  **Component:** ratio of code covered by code duplications in the component to the size of the component, expressed in terms of logical lines of code (non-empty, non-comment lines).

#### Calculated
- Class
- Component
- Function
- Method
- Module
- Package

#### Tags

### rpg -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Subroutine/procedure/program/system:** ratio of code covered by code duplications in the source code element to the size of source code element, expressed in terms of logical lines of code (non-empty, non-comment lines).
  **Component:** ratio of code covered by code duplications in the component to the size of the component, expressed in terms of logical lines of code (non-empty, non-comment lines).

#### Calculated
- Component
- Procedure
- Program
- Subroutine
- System

#### Tags


## CLLOC
### Default
#### Enabled=false
#### NumericType=true
#### Warning=false
#### DisplayName=Clone Lines of Code
#### HelpText


#### Calculated
- CloneClass
- CloneInstance

#### Tags
- /general/Clone
- /internal/csv_column
- /internal/metric_group/Clone
- /tool/OpenStaticAnalyzer/DCF

#### Settings
- Max=0
- Min=0

### cpp -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone instance:** length of the clone instance expressed in terms of lines of code.
  **Clone class:** average of CLLOC of clone instances belonging to the clone class.

#### Calculated
- CloneClass
- CloneInstance

#### Tags

### csharp -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone instance:** length of the clone instance expressed in terms of lines of code.
  **Clone class:** average of CLLOC of clone instances belonging to the clone class.

#### Calculated
- CloneClass
- CloneInstance

#### Tags

### java -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone instance:** length of the clone instance expressed in terms of lines of code.
  **Clone class:** average of CLLOC of clone instances belonging to the clone class.

#### Calculated
- CloneClass
- CloneInstance

#### Tags

### javascript -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone instance:** length of the clone instance expressed in terms of lines of code.

  **Clone class:** average of CLLOC of clone instances belonging to the clone class.

#### Calculated
- CloneClass
- CloneInstance

#### Tags

### python -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone instance:** length of the clone instance expressed in terms of lines of code.
  **Clone class:** average of CLLOC of clone instances belonging to the clone class.

#### Calculated
- CloneClass
- CloneInstance

#### Tags

### rpg -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone instance:** length of the clone instance expressed in terms of lines of code.
  **Clone class:** average of CLLOC of clone instances belonging to the clone class.

#### Calculated
- CloneClass
- CloneInstance

#### Tags


## CR
### Default
#### Enabled=true
#### NumericType=true
#### Warning=false
#### DisplayName=Clone Risk
#### HelpText


#### Tags
- /general/Clone
- /internal/csv_column
- /internal/metric_group/Clone
- /tool/OpenStaticAnalyzer/DCF

#### Settings
- Max=0
- Min=0

### c -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone class:** risk index of the existence of the clone class. It is computed as the product of CLLOC, CI, CCO, NCR, and CV.
  **Component:** relative risk index of the existence of code duplications in the component. It is computed as the sum of CR of the clone classes in the component, divided by the total logical lines of code (non-empty, non-comment lines) of the component. It expresses the risk index projected to a non-empty, non-comment line of code in the component.

#### Calculated
- CloneClass
- Component

#### Tags

### cpp -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone class:** risk index of the existence of the clone class. It is computed as the product of CLLOC, CI, CCO, NCR, and CV.
  **Component:** relative risk index of the existence of code duplications in the component. It is computed as the sum of CR of the clone classes in the component, divided by the total logical lines of code (non-empty, non-comment lines) of the component. It expresses the risk index projected to a non-empty, non-comment line of code in the component.

#### Calculated
- CloneClass
- Component

#### Tags

### csharp -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone class:** risk index of the existence of the clone class. It is computed as the product of CLLOC, CI, CCO, NCR, and CV.
  **Component:** relative risk index of the existence of code duplications in the component. It is computed as the sum of CR of the clone classes in the component, divided by the total logical lines of code (non-empty, non-comment lines) of the component. It expresses the risk index projected to a non-empty, non-comment line of code in the component.

#### Calculated
- CloneClass
- Component

#### Tags

### java -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone class:** risk index of the existence of the clone class. It is computed as the product of CLLOC, CI, CCO, NCR, and CV.
  **Component:** relative risk index of the existence of code duplications in the component. It is computed as the sum of CR of the clone classes in the component, divided by the total logical lines of code (non-empty, non-comment lines) of the component. It expresses the risk index projected to a non-empty, non-comment line of code in the component.

#### Calculated
- CloneClass
- Component

#### Tags

### javascript -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone class:** risk index of the existence of the clone class. It is computed as the product of CLLOC, CI, CCO, NCR, and CV.

  **Component:** relative risk index of the existence of code duplications in the component. It is computed as the sum of CR of the clone classes in the component, divided by the total logical lines of code (non-empty, non-comment lines) of the component. It expresses the risk index projected to a non-empty, non-comment line of code in the component.

#### Calculated
- CloneClass
- Component

#### Tags

### python -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone class:** risk index of the existence of the clone class. It is computed as the product of CLLOC, CI, CCO, NCR, and CV.
  **Component:** relative risk index of the existence of code duplications in the component. It is computed as the sum of CR of the clone classes in the component, divided by the total logical lines of code (non-empty, non-comment lines) of the component. It expresses the risk index projected to a non-empty, non-comment line of code in the component.

#### Calculated
- CloneClass
- Component

#### Tags

### rpg -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone class:** risk index of the existence of the clone class. It is computed as the product of CLLOC, CI, CCO, NCR, and CV.
  **Component:** relative risk index of the existence of code duplications in the component. It is computed as the sum of CR of the clone classes in the component, divided by the total logical lines of code (non-empty, non-comment lines) of the component. It expresses the risk index projected to a non-empty, non-comment line of code in the component.

#### Calculated
- CloneClass
- Component

#### Tags


## CV
### Default
#### Enabled=true
#### NumericType=true
#### Warning=false
#### DisplayName=Clone Variability
#### HelpText


#### Tags
- /general/Clone
- /internal/csv_column
- /internal/metric_group/Clone
- /tool/OpenStaticAnalyzer/DCF

#### Settings
- Max=0
- Min=0

### c -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone instance:** instability of the clone instance since it appeared. It is computed as the ratio of the number of previously analyzed revisions when the instance had been changed to its age (CA).
  **Clone class:** instability of the clone class since it appeared. It is computed as the ratio of the number of previously analyzed revisions when its contained instances were moved, deleted, or added, to its age (CA), plus the average CV of its clone instances.

#### Calculated
- CloneClass
- CloneInstance

#### Tags

### cpp -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone instance:** instability of the clone instance since it appeared. It is computed as the ratio of the number of previously analyzed revisions when the instance had been changed to its age (CA).
  **Clone class:** instability of the clone class since it appeared. It is computed as the ratio of the number of previously analyzed revisions when its contained instances were moved, deleted, or added, to its age (CA), plus the average CV of its clone instances.

#### Calculated
- CloneClass
- CloneInstance

#### Tags

### csharp -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone instance:** instability of the clone instance since it appeared. It is computed as the ratio of the number of previously analyzed revisions when the instance had been changed to its age (CA).
  **Clone class:** instability of the clone class since it appeared. It is computed as the ratio of the number of previously analyzed revisions when its contained instances were moved, deleted, or added, to its age (CA), plus the average CV of its clone instances.

#### Calculated
- CloneClass
- CloneInstance

#### Tags

### java -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone instance:** instability of the clone instance since it appeared. It is computed as the ratio of the number of previously analyzed revisions when the instance had been changed to its age (CA).
  **Clone class:** instability of the clone class since it appeared. It is computed as the ratio of the number of previously analyzed revisions when its contained instances were moved, deleted, or added, to its age (CA), plus the average CV of its clone instances.

#### Calculated
- CloneClass
- CloneInstance

#### Tags

### javascript -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone instance:** instability of the clone instance since it appeared. It is computed as the ratio of the number of previously analyzed revisions when the instance had been changed to its age (CA).

  **Clone class:** instability of the clone class since it appeared. It is computed as the ratio of the number of previously analyzed revisions when its contained instances were moved, deleted, or added, to its age (CA), plus the average CV of its clone instances.

#### Calculated
- CloneClass
- CloneInstance

#### Tags

### python -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone instance:** instability of the clone instance since it appeared. It is computed as the ratio of the number of previously analyzed revisions when the instance had been changed to its age (CA).
  **Clone class:** instability of the clone class since it appeared. It is computed as the ratio of the number of previously analyzed revisions when its contained instances were moved, deleted, or added, to its age (CA), plus the average CV of its clone instances.

#### Calculated
- CloneClass
- CloneInstance

#### Tags

### rpg -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone instance:** instability of the clone instance since it appeared. It is computed as the ratio of the number of previously analyzed revisions when the instance had been changed to its age (CA).
  **Clone class:** instability of the clone class since it appeared. It is computed as the ratio of the number of previously analyzed revisions when its contained instances were moved, deleted, or added, to its age (CA), plus the average CV of its clone instances.

#### Calculated
- CloneClass
- CloneInstance

#### Tags


## LDC
### Default
#### Enabled=true
#### NumericType=true
#### Warning=false
#### DisplayName=Lines of Duplicated Code
#### HelpText


#### Tags
- /general/Clone
- /internal/csv_column
- /internal/metric_group/Clone
- /tool/OpenStaticAnalyzer/DCF

#### Settings
- Max=0
- Min=0

### c -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Function/method/class/module/package:** number of code lines covered by code duplications in the source code element.
  **Component:** number of code lines covered by code duplications in the component.

#### Calculated
- Component
- Enum
- Function
- Structure
- Union

#### Tags

### cpp -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Function/method/class/module/package:** number of code lines covered by code duplications in the source code element.
  **Component:** number of code lines covered by code duplications in the component.

#### Calculated
- Class
- Component
- Enum
- Function
- Interface
- Method
- Namespace
- Structure
- Union

#### Tags

### csharp -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Method/class/interface/namespace:** number of code lines covered by code duplications in the source code element.
  **Component:** number of code lines covered by code duplications in the component.

#### Calculated
- Class
- Component
- Enum
- Interface
- Method
- Namespace
- Structure

#### Tags

### java -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Method/class/package:** number of code lines covered by code duplications in the source code element.
  **Component:** number of code lines covered by code duplications in the component.

#### Calculated
- Annotation
- Class
- Component
- Enum
- Interface
- Method
- Package

#### Tags

### javascript -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Method, function, class:** number of code lines covered by code duplications in the source code element.

  **Component:** number of code lines covered by code duplications in the component.

#### Calculated
- Class
- Component
- Function
- Method

#### Tags

### python -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Function/method/class/module/package:** number of code lines covered by code duplications in the source code element.
  **Component:** number of code lines covered by code duplications in the component.

#### Calculated
- Class
- Component
- Function
- Method
- Module
- Package

#### Tags

### rpg -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Subroutine/procedure/program/system:** number of code lines covered by code duplications in the source code element.
  **Component:** number of code lines covered by code duplications in the component.

#### Calculated
- Component
- Procedure
- Program
- Subroutine
- System

#### Tags


## LLDC
### Default
#### Enabled=true
#### NumericType=true
#### Warning=false
#### DisplayName=Logical Lines of Duplicated Code
#### HelpText


#### Tags
- /general/Clone
- /internal/csv_column
- /internal/metric_group/Clone
- /tool/OpenStaticAnalyzer/DCF

#### Settings
- Max=0
- Min=0

### c -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Function/method/class/module/package:** number of logical code lines (non-empty, non-comment lines) covered by code duplications in the source code element.
  **Component:** The number of logical code lines (non-empty, non-comment lines) covered by code duplications in the component.

#### Calculated
- Component
- Enum
- Function
- Structure
- Union

#### Tags

### cpp -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Function/method/class/module/package:** number of logical code lines (non-empty, non-comment lines) covered by code duplications in the source code element.
  **Component:** The number of logical code lines (non-empty, non-comment lines) covered by code duplications in the component.

#### Calculated
- Class
- Component
- Enum
- Function
- Interface
- Method
- Namespace
- Structure
- Union

#### Tags

### csharp -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Method/class/interface/namespace:** number of logical code lines (non-empty, non-comment lines) covered by code duplications in the source code element.
  **Component:** The number of logical code lines (non-empty, non-comment lines) covered by code duplications in the component.

#### Calculated
- Class
- Component
- Enum
- Interface
- Method
- Namespace
- Structure

#### Tags

### java -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Method/class/package:** number of logical code lines (non-empty, non-comment lines) covered by code duplications in the source code element.
  **Component:** The number of logical code lines (non-empty, non-comment lines) covered by code duplications in the component.

#### Calculated
- Annotation
- Class
- Component
- Enum
- Interface
- Method
- Package

#### Tags

### javascript -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Method, function, class:** number of logical code lines (non-empty, non-comment lines) covered by code duplications in the source code element.

  **Component:** The number of logical code lines (non-empty, non-comment lines) covered by code duplications in the component.

#### Calculated
- Class
- Component
- Function
- Method

#### Tags

### python -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Function/method/class/module/package:** number of logical code lines (non-empty, non-comment lines) covered by code duplications in the source code element.
  **Component:** The number of logical code lines (non-empty, non-comment lines) covered by code duplications in the component.

#### Calculated
- Class
- Component
- Function
- Method
- Module
- Package

#### Tags

### rpg -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Subroutine/procedure/program/system:** number of logical code lines (non-empty, non-comment lines) covered by code duplications in the source code element.
  **Component:** The number of logical code lines (non-empty, non-comment lines) covered by code duplications in the component.

#### Calculated
- Component
- Procedure
- Program
- Subroutine
- System

#### Tags


## NCR
### Default
#### Enabled=true
#### NumericType=true
#### Warning=false
#### DisplayName=Normalized Clone Radius
#### HelpText


#### Tags
- /general/Clone
- /internal/csv_column
- /internal/metric_group/Clone
- /tool/OpenStaticAnalyzer/DCF

#### Settings
- Max=0
- Min=0

### c -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone class:** normalized average distance among clone instances belonging to the clone class, expressed in terms of number of directory changes.
  **Component:** average of NCR of the clone classes in the component.

#### Calculated
- CloneClass
- Component

#### Tags

### cpp -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone class:** normalized average distance among clone instances belonging to the clone class, expressed in terms of number of directory changes.
  **Component:** average of NCR of the clone classes in the component.

#### Calculated
- CloneClass
- Component

#### Tags

### csharp -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone class:** normalized average distance among clone instances belonging to the clone class, expressed in terms of number of directory changes.
  **Component:** average of NCR of the clone classes in the component.

#### Calculated
- CloneClass
- Component

#### Tags

### java -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone class:** normalized average distance among clone instances belonging to the clone class, expressed in terms of number of directory changes.
  **Component:** average of NCR of the clone classes in the component.

#### Calculated
- CloneClass
- Component

#### Tags

### javascript -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone class:** normalized average distance among clone instances belonging to the clone class, expressed in terms of number of directory changes.

  **Component:** average of NCR of the clone classes in the component.

#### Calculated
- CloneClass
- Component

#### Tags

### python -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone class:** normalized average distance among clone instances belonging to the clone class, expressed in terms of number of directory changes.
  **Component:** average of NCR of the clone classes in the component.

#### Calculated
- CloneClass
- Component

#### Tags

### rpg -> Default
#### Enabled=true
#### Warning=false
#### HelpText
  **Clone class:** normalized average distance among clone instances belonging to the clone class, expressed in terms of number of directory changes.
  **Component:** average of NCR of the clone classes in the component.

#### Calculated
- CloneClass
- Component

#### Tags
