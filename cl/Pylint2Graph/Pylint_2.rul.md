# ToolDescription
## Default
### ID=Pylint
### Description
  OpenStaticAnalyzer incorporates the [Pylint] tool for coding rule violation checking and imports its results. OpenStaticAnalyzer also associates the issued rule violations with source code elements (i.e. methods, functions, classes, packages, and modules), and calculates metrics for the source code elements, which represent the amount of violations of each ruleset, rule, and priority groups, respectively.

  OpenStaticAnalyzer uses Pylint "as is", without any guaranties that the results of Pylint are correct. All statements of the Pylint license apply here as well. All texts describing the rulesets and the individual rules are copied from Pylint with some minor grammatical fixes.

# Includes
- Pylint_2.rul_metadata.md

# Metrics
## PYLINT_AB
### Default
#### OriginalId=apply-builtin
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Apply Builtin
#### WarningText
  apply built-in referenced

#### HelpText
  Used when the apply built-in function is referenced (missing from Python 3).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_ABIS
### Default
#### OriginalId=anomalous-backslash-in-string
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Anomalous Backslash In String
#### WarningText
  Anomalous backslash in string: '%s'. String constant might be missing an r prefix.

#### HelpText
  Used when a backslash is in a literal string but not as an escape.


#### Tags
- /tool/Pylint
- /general/String Rules

#### Settings
- Priority=Major


## PYLINT_ACI
### Default
#### OriginalId=abstract-class-instantiated
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Abstract Class Instantiated
#### WarningText
  Abstract class %r with abstract methods instantiated

#### HelpText
  Used when an abstract class with `abc.ABCMeta` as metaclass has abstract methods and is instantiated.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Critical


## PYLINT_AD
### Default
#### OriginalId=arguments-differ
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Arguments Differ
#### WarningText
  Parameters differ from %s %r method

#### HelpText
  Used when a method has a different number of arguments than in the implemented interface or in an overridden method.


#### Tags
- /tool/Pylint
- /general/Class Rules

#### Settings
- Priority=Major


## PYLINT_ADOI
### Default
#### OriginalId=attribute-defined-outside-init
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Attribute Defined Outside Init
#### WarningText
  Attribute %r defined outside __init__

#### HelpText
  Used when an instance attribute is defined outside the \_\_init\_\_ method.


#### Tags
- /tool/Pylint
- /general/Class Rules

#### Settings
- Priority=Major


## PYLINT_AE
### Default
#### OriginalId=astroid-error
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=Astroid Error
#### WarningText
  %s: %s

#### HelpText
  Used when an unexpected error occurred while building the Astroid representation. This is usually accompanied by a traceback. Please report such errors!


#### Tags
- /tool/Pylint
- /general/Pylint Checker Rules

#### Settings
- Priority=Blocker


## PYLINT_AFN
### Default
#### OriginalId=assignment-from-none
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Assignment From None
#### WarningText
  Assigning result of a function call, where the function returns None

#### HelpText
  Used when an assignment is done on a function call but the inferred function returns nothing but None.


#### Tags
- /tool/Pylint
- /general/Typecheck Rules

#### Settings
- Priority=Critical


## PYLINT_AFNR
### Default
#### OriginalId=assignment-from-no-return
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Assignment From No Return
#### WarningText
  Assigning result of a function call, where the function has no return

#### HelpText
  Used when an assignment is done on a function call but the inferred function doesn’t return anything.


#### Tags
- /tool/Pylint
- /general/Typecheck Rules

#### Settings
- Priority=Critical


## PYLINT_AM
### Default
#### OriginalId=abstract-method
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Abstract Method
#### WarningText
  Method %r is abstract in class %r but is not overridden

#### HelpText
  Used when an abstract method (i.e. raise NotImplementedError) is not overridden in concrete class.


#### Tags
- /tool/Pylint
- /general/Class Rules

#### Settings
- Priority=Major


## PYLINT_AMBD
### Default
#### OriginalId=access-member-before-definition
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Access Member Before Definition
#### WarningText
  Access to member %r before its definition line %s

#### HelpText
  Used when an instance member is accessed before it’s actually assigned.


#### Tags
- /tool/Pylint
- /general/Class Rules

#### Settings
- Priority=Critical


## PYLINT_ANS
### Default
#### OriginalId=assigning-non-slot
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Assigning Non Slot
#### WarningText
  Assigning to attribute %r not defined in class slots

#### HelpText
  Used when assigning to an attribute not defined in the class slots.


#### Tags
- /tool/Pylint
- /general/Class Rules

#### Settings
- Priority=Critical


## PYLINT_AOT
### Default
#### OriginalId=assert-on-tuple
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Assert On Tuple
#### WarningText
  Assert called on a 2-uple. Did you mean 'assert x,y'?

#### HelpText
  A call of assert on a tuple will always evaluate to true if the tuple is not empty, and will always evaluate to false if it is.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Major


## PYLINT_ATNK
### Default
#### OriginalId=assign-to-new-keyword
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Assign To New Keyword
#### WarningText
  Name %s will become a keyword in Python %s

#### HelpText
  Used when assignment will become invalid in future Python release due to introducing new keyword.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Major


## PYLINT_AUEIS
### Default
#### OriginalId=anomalous-unicode-escape-in-string
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Anomalous Unicode Escape In String
#### WarningText
  Anomalous Unicode escape in byte string: '%s'. String constant might be missing an r or u prefix.

#### HelpText
  Used when an escape like \\u is encountered in a byte string where it has no effect.


#### Tags
- /tool/Pylint
- /general/String Rules

#### Settings
- Priority=Major


## PYLINT_B
### Default
#### OriginalId=backtick
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Backtick
#### WarningText
  Use of the `` operator

#### HelpText
  Used when the deprecated “\`\`” (backtick) operator is used instead of the str() function.


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Critical


## PYLINT_BC
### Default
#### OriginalId=bad-continuation
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Continuation
#### WarningText
  Wrong %s indentation%s%s.

#### HelpText
  TODO


#### Tags
- /tool/Pylint
- /general/Format Rules

#### Settings
- Priority=Minor


## PYLINT_BCA
### Default
#### OriginalId=bad-classmethod-argument
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Classmethod Argument
#### WarningText
  Class method %s should have %s as first argument

#### HelpText
  Used when a class method has a first argument named differently than the value specified in valid-classmethod-first-arg option (default to “cls”), recommended to easily differentiate them from regular instance methods.


#### Tags
- /tool/Pylint
- /general/Class Rules

#### Settings
- Priority=Minor


## PYLINT_BD
### Default
#### OriginalId=boolean-datetime
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Boolean Datetime
#### WarningText
  Using datetime.time in a boolean context.

#### HelpText
  Using datetime.time in a boolean context can hide subtle bugs when the time they represent matches midnight UTC. This behaviour was fixed in Python 3.5. See <a href="http://bugs.python.org/issue13936" class="uri" class="uri">http://bugs.python.org/issue13936</a> for reference. This message can’t be emitted when using Python &gt;= 3.5.


#### Tags
- /tool/Pylint
- /general/Stdlib Rules

#### Settings
- Priority=Major


## PYLINT_BE
### Default
#### OriginalId=bare-except
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bare Except
#### WarningText
  No exception type(s) specified

#### HelpText
  Used when an except clause doesn’t specify exceptions type to catch.


#### Tags
- /tool/Pylint
- /general/Exception Rules

#### Settings
- Priority=Major


## PYLINT_BEC
### Default
#### OriginalId=bad-exception-context
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Exception Context
#### WarningText
  Exception context set to something which is not an exception, nor None

#### HelpText
  Used when using the syntax “raise … from …”, where the exception context is not an exception, nor None.


#### Tags
- /tool/Pylint
- /general/Exception Rules

#### Settings
- Priority=Critical


## PYLINT_BEO
### Default
#### OriginalId=bad-except-order
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Except Order
#### WarningText
  Bad except clauses order (%s)

#### HelpText
  Used when except clauses are not in the correct order (from the more specific to the more generic). If you don’t fix the order, some exceptions may not be caught by the most specific handler.


#### Tags
- /tool/Pylint
- /general/Exception Rules

#### Settings
- Priority=Critical


## PYLINT_BFC
### Default
#### OriginalId=bad-format-character
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Format Character
#### WarningText
  Unsupported format character %r (%#02x) at index %d

#### HelpText
  Used when an unsupported format character is used in a format string.


#### Tags
- /tool/Pylint
- /general/String Rules

#### Settings
- Priority=Critical


## PYLINT_BFS
### Default
#### OriginalId=bad-format-string
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Format String
#### WarningText
  Invalid format string

#### HelpText
  Used when a PEP 3101 format string is invalid.


#### Tags
- /tool/Pylint
- /general/String Rules

#### Settings
- Priority=Major


## PYLINT_BFSK
### Default
#### OriginalId=bad-format-string-key
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Format String Key
#### WarningText
  Format string dictionary key should be a string, not %s

#### HelpText
  Used when a format string that uses named conversion specifiers is used with a dictionary whose keys are not all strings.


#### Tags
- /tool/Pylint
- /general/String Rules

#### Settings
- Priority=Major


## PYLINT_BI
### Default
#### OriginalId=bad-indentation
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Indentation
#### WarningText
  Bad indentation. Found %s %s, expected %s

#### HelpText
  Used when an unexpected number of indentation’s tabulations or spaces has been found.


#### Tags
- /tool/Pylint
- /general/Format Rules

#### Settings
- Priority=Major


## PYLINT_BIO
### Default
#### OriginalId=bad-inline-option
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Inline Option
#### WarningText
  Unable to consider inline option %r

#### HelpText
  Used when an inline option is either badly formatted or can't be used inside modules.


#### Tags
- /tool/Pylint
- /general/Pylint Checker Rules

#### Settings
- Priority=Minor


## PYLINT_BMCA
### Default
#### OriginalId=bad-mcs-classmethod-argument
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Mcs Classmethod Argument
#### WarningText
  Metaclass class method %s should have %s as first argument

#### HelpText
  Used when a metaclass class method has a first argument named differently than the value specified in valid-metaclass-classmethod-first-arg option (default to “mcs”), recommended to easily differentiate them from regular instance methods.


#### Tags
- /tool/Pylint
- /general/Class Rules

#### Settings
- Priority=Minor


## PYLINT_BMMA
### Default
#### OriginalId=bad-mcs-method-argument
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Mcs Method Argument
#### WarningText
  Metaclass method %s should have %s as first argument

#### HelpText
  Used when a metaclass method has a first argument named differently than the value specified in valid-classmethod-first-arg option (default to “cls”), recommended to easily differentiate them from regular instance methods.


#### Tags
- /tool/Pylint
- /general/Class Rules

#### Settings
- Priority=Minor


## PYLINT_BN
### Default
#### OriginalId=blacklisted-name
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Blacklisted Name
#### WarningText
  Black listed name "%s"

#### HelpText
  Used when the name is listed in the black list (unauthorized names).


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Minor


## PYLINT_BOE
### Default
#### OriginalId=binary-op-exception
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Binary Op Exception
#### WarningText
  Exception to catch is the result of a binary "%s" operation

#### HelpText
  Used when the exception to catch is of the form “except A or B:”. If intending to catch multiple, rewrite as “except (A, B):”.


#### Tags
- /tool/Pylint
- /general/Exception Rules

#### Settings
- Priority=Major


## PYLINT_BOM
### Default
#### OriginalId=bad-open-mode
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Open Mode
#### WarningText
  "%s" is not a valid mode for open.

#### HelpText
  Python supports: r, w, a\[, x\] modes with b, +, and U (only with r) options. See <a href="http://docs.python.org/2/library/functions.html#open" class="uri" class="uri">http://docs.python.org/2/library/functions.html#open</a>.


#### Tags
- /tool/Pylint
- /general/Stdlib Rules

#### Settings
- Priority=Major


## PYLINT_BOV
### Default
#### OriginalId=bad-option-value
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Option Value
#### WarningText
  Bad option value %r

#### HelpText
  Used when a bad value for an inline option is encountered.


#### Tags
- /tool/Pylint
- /general/Pylint Checker Rules

#### Settings
- Priority=Critical


## PYLINT_BP3I
### Default
#### OriginalId=bad-python3-import
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Python3 Import
#### WarningText
  Module moved in Python 3

#### HelpText
  Used when importing a module that no longer exists in Python 3.


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_BRS
### Default
#### OriginalId=bad-reversed-sequence
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Reversed Sequence
#### WarningText
  The first reversed() argument is not a sequence

#### HelpText
  Used when the first argument to reversed() builtin isn’t a sequence (does not implement \_\_reversed\_\_, nor \_\_getitem\_\_ and \_\_len\_\_.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Critical


## PYLINT_BSA
### Default
#### OriginalId=bad-staticmethod-argument
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Staticmethod Argument
#### WarningText
  Static method with %r as first argument

#### HelpText
  Used when a static method has “self” or a value specified in valid-classmethod-first-arg option or valid-metaclass-classmethod-first-arg option as first argument.


#### Tags
- /tool/Pylint
- /general/Class Rules

#### Settings
- Priority=Major


## PYLINT_BSC
### Default
#### OriginalId=bad-super-call
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Super Call
#### WarningText
  Bad first argument %r given to super()

#### HelpText
  Used when another argument than the current class is given as first argument of the super builtin.


#### Tags
- /tool/Pylint
- /general/Newstyle Rules

#### Settings
- Priority=Critical


## PYLINT_BSFT
### Default
#### OriginalId=bad-string-format-type
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bad String Format Type
#### WarningText
  Argument %r does not match format type %r

#### HelpText
  Used when a type required by format string is not suitable for actual argument type.


#### Tags
- /tool/Pylint
- /general/String Rules

#### Settings
- Priority=Critical


## PYLINT_BSSC
### Default
#### OriginalId=bad-str-strip-call
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Str Strip Call
#### WarningText
  Suspicious argument in %s.%s call

#### HelpText
  The argument to a str.{l,r,}strip call contains a duplicate character.


#### Tags
- /tool/Pylint
- /general/String Rules

#### Settings
- Priority=Critical


## PYLINT_BTI
### Default
#### OriginalId=bad-thread-instantiation
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Thread Instantiation
#### WarningText
  threading.Thread needs the target function

#### HelpText
  The warning is emitted when a threading.Thread class is instantiated without the target function being passed. By default, the first parameter is the group param, not the target param.


#### Tags
- /tool/Pylint
- /general/Stdlib Rules

#### Settings
- Priority=Major


## PYLINT_BW
### Default
#### OriginalId=bad-whitespace
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Whitespace
#### WarningText
  %s space %s %s %s

#### HelpText
  Used when a wrong number of spaces is used around an operator, bracket or block opener.


#### Tags
- /tool/Pylint
- /general/Format Rules

#### Settings
- Priority=Minor


## PYLINT_BaB
### Default
#### OriginalId=basestring-builtin
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Basestring Builtin
#### WarningText
  basestring built-in referenced

#### HelpText
  Used when the basestring built-in function is referenced (missing from Python 3).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_BrE
### Default
#### OriginalId=broad-except
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Broad Except
#### WarningText
  Catching too general exception %s

#### HelpText
  Used when an except catches a too general exception, possibly burying unrelated errors.


#### Tags
- /tool/Pylint
- /general/Exception Rules

#### Settings
- Priority=Major


## PYLINT_BuB
### Default
#### OriginalId=buffer-builtin
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Buffer Builtin
#### WarningText
  buffer built-in referenced

#### HelpText
  Used when the buffer built-in function is referenced (missing from Python 3).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_CB
### Default
#### OriginalId=cmp-builtin
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Cmp Builtin
#### WarningText
  cmp built-in referenced

#### HelpText
  Used when the cmp built-in function is referenced (missing from Python 3).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_CC
### Default
#### OriginalId=chained-comparison
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Chained Comparison
#### WarningText
  Simplify chained comparison between the operands

#### HelpText
  This message is emitted when pylint encounters boolean operation like“a &lt; b and b &lt; c”, suggesting instead to refactor it to “a &lt; b &lt; c”.


#### Tags
- /tool/Pylint
- /general/Refactoring Rules

#### Settings
- Priority=Minor


## PYLINT_CE
### Default
#### OriginalId=comprehension-escape
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Comprehension Escape
#### WarningText
  Using a variable that was bound inside a comprehension

#### HelpText
  Emitted when using a variable, that was bound in a comprehension handler, outside of the comprehension itself. On Python 3 these variables will be deleted outside of the comprehension.


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_CENM
### Default
#### OriginalId=c-extension-no-member
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=C Extension No Member
#### WarningText
  %s %r has no %r member%s, but source is unavailable. Consider adding this module to extension-pkg-whitelist if you want to perform analysis based on run-time introspection of living objects.

#### HelpText
  Used when a variable is accessed for non-existent member of C extension. Due to unavailability of source static analysis is impossible, but it may be performed by introspecting living objects in run-time.


#### Tags
- /tool/Pylint
- /general/Typecheck Rules

#### Settings
- Priority=Minor


## PYLINT_CI
### Default
#### OriginalId=cyclic-import
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Cyclic Import
#### WarningText
  Cyclic import (%s)

#### HelpText
  Used when a cyclic import between two or more modules is detected.


#### Tags
- /tool/Pylint
- /general/Import Rules

#### Settings
- Priority=Minor


## PYLINT_CID
### Default
#### OriginalId=consider-iterating-dictionary
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Consider Iterating Dictionary
#### WarningText
  Consider iterating the dictionary directly instead of calling .keys()

#### HelpText
  Emitted when the keys of a dictionary are iterated through the .keys() method. It is enough to just iterate through the dictionary itself, as in “for key in dictionary”.


#### Tags
- /tool/Pylint
- /general/Refactoring Rules

#### Settings
- Priority=Minor


## PYLINT_CIF
### Default
#### OriginalId=continue-in-finally
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Continue In Finally
#### WarningText
  'continue' not supported inside 'finally' clause

#### HelpText
  Emitted when the `continue` keyword is found inside a finally clause, which is a SyntaxError.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Critical


## PYLINT_CM
### Default
#### OriginalId=cmp-method
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Cmp Method
#### WarningText
  __cmp__ method defined

#### HelpText
  Used when a \_\_cmp\_\_ method is defined (method is not used by Python 3).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_CMI
### Default
#### OriginalId=consider-merging-isinstance
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Consider Merging Isinstance
#### WarningText
  Consider merging these isinstance calls to isinstance(%s, (%s))

#### HelpText
  Used when multiple consecutive isinstance calls can be merged into one.


#### Tags
- /tool/Pylint
- /general/Refactoring Rules

#### Settings
- Priority=Minor


## PYLINT_CNE
### Default
#### OriginalId=catching-non-exception
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Catching Non Exception
#### WarningText
  Catching an exception which doesn't inherit from Exception: %s

#### HelpText
  Used when a class which doesn’t inherit from Exception is used as an exception in an except clause.


#### Tags
- /tool/Pylint
- /general/Exception Rules

#### Settings
- Priority=Critical


## PYLINT_CSV
### Default
#### OriginalId=consider-swap-variables
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Consider Swap Variables
#### WarningText
  Consider using tuple unpacking for swapping variables

#### HelpText
  You do not have to use a temporary variable in order to swap variables. Using “tuple unpacking” to directly swap variables makes the intention more clear.


#### Tags
- /tool/Pylint
- /general/Refactoring Rules

#### Settings
- Priority=Minor


## PYLINT_CUDC
### Default
#### OriginalId=consider-using-dict-comprehension
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Consider Using Dict Comprehension
#### WarningText
  Consider using a dictionary comprehension

#### HelpText
  Although there is nothing syntactically wrong with this code, it is hard to read and can be simplified to a dict comprehension.Also it is faster since you don’t need to create another transient list.


#### Tags
- /tool/Pylint
- /general/Refactoring Rules

#### Settings
- Priority=Minor


## PYLINT_CUE
### Default
#### OriginalId=consider-using-enumerate
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Consider Using Enumerate
#### WarningText
  Consider using enumerate instead of iterating with range and len

#### HelpText
  Emitted when code that iterates with range and len is encountered. Such code can be simplified by using the enumerate builtin.


#### Tags
- /tool/Pylint
- /general/Refactoring Rules

#### Settings
- Priority=Minor


## PYLINT_CUG
### Default
#### OriginalId=consider-using-get
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Consider Using Get
#### WarningText
  Consider using dict.get for getting values from a dict if a key is present or a default if not

#### HelpText
  Using the builtin dict.get for getting a value from a dictionary if a key is present or a default if not, is simpler and considered more idiomatic, although sometimes a bit slower.


#### Tags
- /tool/Pylint
- /general/Refactoring Rules

#### Settings
- Priority=Minor


## PYLINT_CUI
### Default
#### OriginalId=consider-using-in
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Consider Using In
#### WarningText
  Consider merging these comparisons with "in" to %r

#### HelpText
  To check if a variable is equal to one of many values,combine the values into a tuple and check if the variable is contained “in” it instead of checking for equality against each of the values.This is faster and less verbose.


#### Tags
- /tool/Pylint
- /general/Refactoring Rules

#### Settings
- Priority=Minor


## PYLINT_CUJ
### Default
#### OriginalId=consider-using-join
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Consider Using Join
#### WarningText
  Consider using str.join(sequence) for concatenating strings from an iterable

#### HelpText
  Using str.join(sequence) is faster, uses less memory and increases readability compared to for-loop iteration.


#### Tags
- /tool/Pylint
- /general/Refactoring Rules

#### Settings
- Priority=Minor


## PYLINT_CUSC
### Default
#### OriginalId=consider-using-set-comprehension
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Consider Using Set Comprehension
#### WarningText
  Consider using a set comprehension

#### HelpText
  Although there is nothing syntactically wrong with this code, it is hard to read and can be simplified to a set comprehension.Also it is faster since you don’t need to create another transient list.


#### Tags
- /tool/Pylint
- /general/Refactoring Rules

#### Settings
- Priority=Minor


## PYLINT_CUT
### Default
#### OriginalId=consider-using-ternary
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Consider Using Ternary
#### WarningText
  Consider using ternary (%s)

#### HelpText
  Used when one of known pre-python 2.5 ternary syntax is used.


#### Tags
- /tool/Pylint
- /general/Refactoring Rules

#### Settings
- Priority=Minor


## PYLINT_CVFL
### Default
#### OriginalId=cell-var-from-loop
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Cell Var From Loop
#### WarningText
  Cell variable %s defined in loop

#### HelpText
  A variable used in a closure is defined in a loop. This will result in all closures using the same value for the closed-over variable.


#### Tags
- /tool/Pylint
- /general/Variable Rules

#### Settings
- Priority=Major


## PYLINT_CWC
### Default
#### OriginalId=comparison-with-callable
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Comparison With Callable
#### WarningText
  Comparing against a callable, did you omit the parenthesis?

#### HelpText
  This message is emitted when pylint detects that a comparison with a callable was made, which might suggest that some parenthesis were omitted, resulting in potential unwanted behaviour.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Major


## PYLINT_CWI
### Default
#### OriginalId=comparison-with-itself
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Comparison With Itself
#### WarningText
  Redundant comparison - %s

#### HelpText
  Used when something is compared against itself.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Minor


## PYLINT_CWS
### Default
#### OriginalId=confusing-with-statement
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Confusing With Statement
#### WarningText
  Following "as" with another context manager looks like a tuple.

#### HelpText
  Emitted when a `with` statement component returns multiple values and uses name binding with `as` only for a part of those values, as in with ctx() as a, b. This can be misleading, since it’s not clear if the context manager returns a tuple or if the node without a name binding is another context manager.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Major


## PYLINT_CoB
### Default
#### OriginalId=coerce-builtin
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Coerce Builtin
#### WarningText
  coerce built-in referenced

#### HelpText
  Used when the coerce built-in function is referenced (missing from Python 3).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_CoM
### Default
#### OriginalId=coerce-method
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Coerce Method
#### WarningText
  __coerce__ method defined

#### HelpText
  Used when a \_\_coerce\_\_ method is defined (method is not used by Python 3).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_DAN
### Default
#### OriginalId=duplicate-argument-name
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Duplicate Argument Name
#### WarningText
  Duplicate argument name %s in function definition

#### HelpText
  Duplicate argument names in function definitions are syntax errors.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Critical


## PYLINT_DB
### Default
#### OriginalId=duplicate-bases
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Duplicate Bases
#### WarningText
  Duplicate bases for class %r

#### HelpText
  Used when a class has duplicate bases.


#### Tags
- /tool/Pylint
- /general/Class Rules

#### Settings
- Priority=Critical


## PYLINT_DC
### Default
#### OriginalId=duplicate-code
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=Duplicate Code
#### WarningText
  Similar lines in %s files

#### HelpText
  Indicates that a set of similar lines has been detected among multiple file. This usually means that the code should be refactored to avoid this duplication.


#### Tags
- /tool/Pylint
- /general/Similarity Rules

#### Settings
- Priority=Minor


## PYLINT_DDV
### Default
#### OriginalId=dangerous-default-value
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Dangerous Default Value
#### WarningText
  Dangerous default value %s as argument

#### HelpText
  Used when a mutable value as list or dictionary is detected in a default value for an argument.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Major


## PYLINT_DE
### Default
#### OriginalId=duplicate-except
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Duplicate Except
#### WarningText
  Catching previously caught exception type %s

#### HelpText
  Used when an except catches a type that was already caught by a previous handler.


#### Tags
- /tool/Pylint
- /general/Exception Rules

#### Settings
- Priority=Major


## PYLINT_DIF
### Default
#### OriginalId=deprecated-itertools-function
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Deprecated Itertools Function
#### WarningText
  Accessing a deprecated function on the itertools module

#### HelpText
  Used when accessing a function on itertools that has been removed in Python 3.


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_DIM
### Default
#### OriginalId=dict-iter-method
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Dict Iter Method
#### WarningText
  Calling a dict.iter*() method

#### HelpText
  Used for calls to dict.iterkeys(), itervalues() or iteritems() (Python 3 lacks these methods).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_DINI
### Default
#### OriginalId=dict-items-not-iterating
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Dict Items Not Iterating
#### WarningText
  dict.items referenced when not iterating

#### HelpText
  Used when dict.items is referenced in a non-iterating context (returns an iterator in Python 3).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_DK
### Default
#### OriginalId=duplicate-key
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Duplicate Key
#### WarningText
  Duplicate key %r in dictionary

#### HelpText
  Used when a dictionary expression binds the same key multiple times.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Major


## PYLINT_DKNI
### Default
#### OriginalId=dict-keys-not-iterating
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Dict Keys Not Iterating
#### WarningText
  dict.keys referenced when not iterating

#### HelpText
  Used when dict.keys is referenced in a non-iterating context (returns an iterator in Python 3).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_DM
### Default
#### OriginalId=delslice-method
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Delslice Method
#### WarningText
  __delslice__ method defined

#### HelpText
  Used when a \_\_delslice\_\_ method is defined (method is not used by Python 3).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_DOF
### Default
#### OriginalId=deprecated-operator-function
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Deprecated Operator Function
#### WarningText
  Accessing a removed attribute on the operator module

#### HelpText
  Used when accessing a field on operator module that has been removed in Python 3.


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_DP
### Default
#### OriginalId=deprecated-pragma
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=Deprecated Pragma
#### WarningText
  Pragma "%s" is deprecated, use "%s" instead

#### HelpText
  Some inline pylint options have been renamed or reworked, only the most recent form should be used. NOTE:skip-all is only available with pylint &gt;= 0.26.


#### Tags
- /tool/Pylint
- /general/Pylint Checker Rules

#### Settings
- Priority=Minor


## PYLINT_DSF
### Default
#### OriginalId=deprecated-string-function
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Deprecated String Function
#### WarningText
  Accessing a deprecated function on the string module

#### HelpText
  Used when accessing a string function that has been deprecated in Python 3.


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_DSFA
### Default
#### OriginalId=duplicate-string-formatting-argument
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Duplicate String Formatting Argument
#### WarningText
  Duplicate string formatting argument %r, consider passing as named argument

#### HelpText
  Used when we detect that a string formatting is repeating an argument instead of using named string arguments.


#### Tags
- /tool/Pylint
- /general/String Rules

#### Settings
- Priority=Major


## PYLINT_DSTC
### Default
#### OriginalId=deprecated-str-translate-call
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Deprecated Str Translate Call
#### WarningText
  Using str.translate with deprecated deletechars parameters

#### HelpText
  Used when using the deprecated deletechars parameters from str.translate. Use re.sub to remove the desired characters.


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_DTF
### Default
#### OriginalId=deprecated-types-field
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Deprecated Types Field
#### WarningText
  Accessing a deprecated fields on the types module

#### HelpText
  Used when accessing a field on types that has been removed in Python 3.


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_DUF
### Default
#### OriginalId=deprecated-urllib-function
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Deprecated Urllib Function
#### WarningText
  Accessing a removed attribute on the urllib module

#### HelpText
  Used when accessing a field on urllib module that has been removed or moved in Python 3.


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_DVM
### Default
#### OriginalId=dict-view-method
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Dict View Method
#### WarningText
  Calling a dict.view*() method

#### HelpText
  Used for calls to dict.viewkeys(), viewvalues() or viewitems() (Python 3 lacks these methods).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_DVNI
### Default
#### OriginalId=dict-values-not-iterating
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Dict Values Not Iterating
#### WarningText
  dict.values referenced when not iterating

#### HelpText
  Used when dict.values is referenced in a non-iterating context (returns an iterator in Python 3).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_DeM
### Default
#### OriginalId=deprecated-module
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Deprecated Module
#### WarningText
  Uses of a deprecated module %r

#### HelpText
  Used a module marked as deprecated is imported.


#### Tags
- /tool/Pylint
- /general/Import Rules

#### Settings
- Priority=Major


## PYLINT_DeSF
### Default
#### OriginalId=deprecated-sys-function
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Deprecated Sys Function
#### WarningText
  Accessing a removed attribute on the sys module

#### HelpText
  Used when accessing a field on sys module that has been removed in Python 3.


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_DepM
### Default
#### OriginalId=deprecated-method
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Deprecated Method
#### WarningText
  Using deprecated method %s()

#### HelpText
  The method is marked as deprecated and will be removed in a future version of Python. Consider looking for an alternative in the documentation.


#### Tags
- /tool/Pylint
- /general/Stdlib Rules

#### Settings
- Priority=Major


## PYLINT_DiM
### Default
#### OriginalId=div-method
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Div Method
#### WarningText
  __div__ method defined

#### HelpText
  Used when a \_\_div\_\_ method is defined. Using `__truediv__` and setting\_\_div\_\_ = \_\_truediv\_\_ should be preferred.(method is not used by Python 3).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_EB
### Default
#### OriginalId=execfile-builtin
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Execfile Builtin
#### WarningText
  execfile built-in referenced

#### HelpText
  Used when the execfile built-in function is referenced (missing from Python 3).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_ED
### Default
#### OriginalId=empty-docstring
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Empty Docstring
#### WarningText
  Empty %s docstring

#### HelpText
  Used when a module, function, class or method has an empty docstring (it would be too easy ;).


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Minor


## PYLINT_EE
### Default
#### OriginalId=exception-escape
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Exception Escape
#### WarningText
  Using an exception object that was bound by an except handler

#### HelpText
  Emitted when using an exception, that was bound in an except handler, outside of the except handler. On Python 3 these exceptions will be deleted once they get out of the except handler.


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_EMA
### Default
#### OriginalId=exception-message-attribute
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Exception Message Attribute
#### WarningText
  Exception.message removed in Python 3

#### HelpText
  Used when the message attribute is accessed on an Exception. Use str(exception) instead.


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_ENA
### Default
#### OriginalId=expression-not-assigned
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Expression Not Assigned
#### WarningText
  Expression "%s" is assigned to nothing

#### HelpText
  Used when an expression that is not a function call is assigned to nothing. Probably something else was intended.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Major


## PYLINT_EU
### Default
#### OriginalId=eval-used
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Eval Used
#### WarningText
  Use of eval

#### HelpText
  Used when you use the “eval” function, to discourage its usage. Consider using `ast.literal_eval` for safely evaluating strings containing Python expressions from untrusted sources.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Major


## PYLINT_EWH
### Default
#### OriginalId=eq-without-hash
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Eq Without Hash
#### WarningText
  Implementing __eq__ without also implementing __hash__

#### HelpText
  Used when a class implements \_\_eq\_\_ but not \_\_hash\_\_. In Python 2, objects get object.\_\_hash\_\_ as the default implementation, in Python 3 objects get None as their default \_\_hash\_\_ implementation if they also implement \_\_eq\_\_.


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_ExU
### Default
#### OriginalId=exec-used
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Exec Used
#### WarningText
  Use of exec

#### HelpText
  Used when you use the “exec” statement (function for Python 3), to discourage its usage. That doesn’t mean you cannot use it!


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Major


## PYLINT_F
### Default
#### OriginalId=fatal
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=Fatal
#### WarningText


#### HelpText
  Used when an error occurred preventing the analysis of a module (unable to find it for instance).


#### Tags
- /tool/Pylint
- /general/Pylint Checker Rules

#### Settings
- Priority=Blocker


## PYLINT_FB
### Default
#### OriginalId=file-builtin
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=File Builtin
#### WarningText
  file built-in referenced

#### HelpText
  Used when the file built-in function is referenced (missing from Python 3).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_FBNI
### Default
#### OriginalId=filter-builtin-not-iterating
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Filter Builtin Not Iterating
#### WarningText
  filter built-in referenced when not iterating

#### HelpText
  Used when the filter built-in is referenced in a non-iterating context (returns an iterator in Python 3).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_FCS
### Default
#### OriginalId=format-combined-specification
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Format Combined Specification
#### WarningText
  Format string contains both automatic field numbering and manual field specification

#### HelpText
  Used when a PEP 3101 format string contains both automatic field numbering (e.g. ‘{}’) and manual field specification (e.g. ‘{0}’).


#### Tags
- /tool/Pylint
- /general/String Rules

#### Settings
- Priority=Major


## PYLINT_FI
### Default
#### OriginalId=file-ignored
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=File Ignored
#### WarningText
  Ignoring entire file

#### HelpText
  Used to inform that the file will not be checked.


#### Tags
- /tool/Pylint
- /general/Pylint Checker Rules

#### Settings
- Priority=Minor


## PYLINT_FNM
### Default
#### OriginalId=format-needs-mapping
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Format Needs Mapping
#### WarningText
  Expected mapping for format string, not %s

#### HelpText
  Used when a format string that uses named conversion specifiers is used with an argument that is not a mapping.


#### Tags
- /tool/Pylint
- /general/String Rules

#### Settings
- Priority=Critical


## PYLINT_FR
### Default
#### OriginalId=function-redefined
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Function Redefined
#### WarningText
  %s already defined line %s

#### HelpText
  Used when a function / class / method is redefined.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Critical


## PYLINT_Fi
### Default
#### OriginalId=fixme
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Fixme
#### WarningText


#### HelpText
  Used when a warning note as FIXME or XXX is detected.


#### Tags
- /tool/Pylint
- /general/Miscellaneous Rules

#### Settings
- Priority=Major


## PYLINT_GAML
### Default
#### OriginalId=global-at-module-level
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Global At Module Level
#### WarningText
  Using the global statement at the module level

#### HelpText
  Used when you use the “global” statement at the module level since it has no effect.


#### Tags
- /tool/Pylint
- /general/Variable Rules

#### Settings
- Priority=Major


## PYLINT_GM
### Default
#### OriginalId=getslice-method
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Getslice Method
#### WarningText
  __getslice__ method defined

#### HelpText
  Used when a \_\_getslice\_\_ method is defined (method is not used by Python 3).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_GS
### Default
#### OriginalId=global-statement
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Global Statement
#### WarningText
  Using the global statement

#### HelpText
  Used when you use the “global” statement to update a global variable. Pylint just try to discourage this usage. That doesn’t mean you cannot use it!


#### Tags
- /tool/Pylint
- /general/Variable Rules

#### Settings
- Priority=Major


## PYLINT_GVNA
### Default
#### OriginalId=global-variable-not-assigned
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Global Variable Not Assigned
#### WarningText
  Using global for %r but no assignment is done

#### HelpText
  Used when a variable is defined through the “global” statement but no assignment to this variable is done.


#### Tags
- /tool/Pylint
- /general/Variable Rules

#### Settings
- Priority=Major


## PYLINT_GVU
### Default
#### OriginalId=global-variable-undefined
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Global Variable Undefined
#### WarningText
  Global variable %r undefined at the module level

#### HelpText
  Used when a variable is defined through the “global” statement but the variable is not defined in the module scope.


#### Tags
- /tool/Pylint
- /general/Variable Rules

#### Settings
- Priority=Major


## PYLINT_HM
### Default
#### OriginalId=hex-method
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Hex Method
#### WarningText
  __hex__ method defined

#### HelpText
  Used when a \_\_hex\_\_ method is defined (method is not used by Python 3).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_IAO
### Default
#### OriginalId=invalid-all-object
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Invalid All Object
#### WarningText
  Invalid object %r in __all__, must contain only strings

#### HelpText
  Used when an invalid (non-string) object occurs in \_\_all\_\_.


#### Tags
- /tool/Pylint
- /general/Variable Rules

#### Settings
- Priority=Critical


## PYLINT_IB
### Default
#### OriginalId=input-builtin
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Input Builtin
#### WarningText
  input built-in referenced

#### HelpText
  Used when the input built-in is referenced (backwards-incompatible semantics in Python 3).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_ICID
### Default
#### OriginalId=invalid-characters-in-docstring
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Invalid Characters In Docstring
#### WarningText
  Invalid characters %r in a docstring

#### HelpText
  Used when a word in docstring cannot be checked by enchant.


#### Tags
- /tool/Pylint
- /general/Spelling Rules

#### Settings
- Priority=Minor


## PYLINT_IE
### Default
#### OriginalId=import-error
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=Import Error
#### WarningText
  Unable to import %s

#### HelpText
  Used when pylint has been unable to import a module.


#### Tags
- /tool/Pylint
- /general/Import Rules

#### Settings
- Priority=Critical


## PYLINT_IED
### Default
#### OriginalId=invalid-encoded-data
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Invalid Encoded Data
#### WarningText
  Cannot decode using encoding "%s", unexpected byte at position %d

#### HelpText
  Used when a source line cannot be decoded using the specified source file encoding. This message can’t be emitted when using Python &gt;= 3.0.


#### Tags
- /tool/Pylint
- /general/Miscellaneous Rules

#### Settings
- Priority=Major


## PYLINT_IEV
### Default
#### OriginalId=invalid-envvar-value
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Invalid Envvar Value
#### WarningText
  %s does not support %s type argument

#### HelpText
  Env manipulation functions support only string type arguments. See <a href="https://docs.python.org/3/library/os.html#os.getenv" class="uri" class="uri">https://docs.python.org/3/library/os.html#os.getenv</a>.


#### Tags
- /tool/Pylint
- /general/Stdlib Rules

#### Settings
- Priority=Critical


## PYLINT_IFI
### Default
#### OriginalId=invalid-format-index
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Invalid Format Index
#### WarningText
  Using invalid lookup key %r in format specifier %r

#### HelpText
  Used when a PEP 3101 format string uses a lookup specifier ({a\[1\]}), but the argument passed for formatting doesn’t contain or doesn’t have that key as an attribute.


#### Tags
- /tool/Pylint
- /general/String Rules

#### Settings
- Priority=Major


## PYLINT_IIG
### Default
#### OriginalId=init-is-generator
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Init Is Generator
#### WarningText
  __init__ method is a generator

#### HelpText
  Used when the special class method \_\_init\_\_ is turned into a generator by a yield in its body.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Critical


## PYLINT_ILR
### Default
#### OriginalId=invalid-length-returned
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Invalid Length Returned
#### WarningText
  __len__ does not return non-negative integer

#### HelpText
  Used when a \_\_len\_\_ method returns something which is not a non-negative integer.


#### Tags
- /tool/Pylint
- /general/Class Rules

#### Settings
- Priority=Critical


## PYLINT_IM
### Default
#### OriginalId=inconsistent-mro
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Inconsistent Mro
#### WarningText
  Inconsistent method resolution order for class %r

#### HelpText
  Used when a class has an inconsistent method resolution order.


#### Tags
- /tool/Pylint
- /general/Class Rules

#### Settings
- Priority=Critical


## PYLINT_IN
### Default
#### OriginalId=invalid-name
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Invalid Name
#### WarningText
  %s name "%s" doesn't conform to %s

#### HelpText
  Used when the name doesn’t conform to naming rules associated to its type (constant, variable, class…).


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Minor


## PYLINT_INC
### Default
#### OriginalId=inherit-non-class
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Inherit Non Class
#### WarningText
  Inheriting %r, which is not a class.

#### HelpText
  Used when a class inherits from something which is not a class.


#### Tags
- /tool/Pylint
- /general/Class Rules

#### Settings
- Priority=Critical


## PYLINT_IRS
### Default
#### OriginalId=inconsistent-return-statements
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Inconsistent Return Statements
#### WarningText
  Either all return statements in a function should return an expression, or none of them should.

#### HelpText
  According to PEP8, if any return statement returns an expression, any return statements where no value is returned should explicitly state this as return None, and an explicit return statement should be present at the end of the function (if reachable).


#### Tags
- /tool/Pylint
- /general/Refactoring Rules

#### Settings
- Priority=Minor


## PYLINT_IS
### Default
#### OriginalId=import-self
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Import Self
#### WarningText
  Module import itself

#### HelpText
  Used when a module is importing itself.


#### Tags
- /tool/Pylint
- /general/Import Rules

#### Settings
- Priority=Major


## PYLINT_ISAT
### Default
#### OriginalId=invalid-star-assignment-target
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Invalid Star Assignment Target
#### WarningText
  Starred assignment target must be in a list or tuple

#### HelpText
  Emitted when a star expression is used as a starred assignment target.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Critical


## PYLINT_ISC
### Default
#### OriginalId=invalid-str-codec
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Invalid Str Codec
#### WarningText
  non-text encoding used in str.decode

#### HelpText
  Used when using str.encode or str.decode with a non-text encoding. Use codecs module to handle arbitrary codecs.


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_ISCIS
### Default
#### OriginalId=implicit-str-concat-in-sequence
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Implicit Str Concat In Sequence
#### WarningText
  Implicit string concatenation found in %s

#### HelpText
  String literals are implicitly concatenated in a literal iterable definition : maybe a comma is missing ?.


#### Tags
- /tool/Pylint
- /general/String Rules

#### Settings
- Priority=Major


## PYLINT_ISI
### Default
#### OriginalId=invalid-sequence-index
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Invalid Sequence Index
#### WarningText
  Sequence index is not an int, slice, or instance with __index__

#### HelpText
  Used when a sequence type is indexed with an invalid type. Valid types are ints, slices, and objects with an \_\_index\_\_ method.


#### Tags
- /tool/Pylint
- /general/Typecheck Rules

#### Settings
- Priority=Critical


## PYLINT_ISML
### Default
#### OriginalId=import-star-module-level
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Import Star Module Level
#### WarningText
  Import * only allowed at module level

#### HelpText
  Used when the import star syntax is used somewhere else than the module level. This message can’t be emitted when using Python &gt;= 3.0.


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Critical


## PYLINT_ISO
### Default
#### OriginalId=invalid-slots-object
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Invalid Slots Object
#### WarningText
  Invalid object %r in __slots__, must contain only non empty strings

#### HelpText
  Used when an invalid (non-string) object occurs in \_\_slots\_\_.


#### Tags
- /tool/Pylint
- /general/Class Rules

#### Settings
- Priority=Critical


## PYLINT_IUOT
### Default
#### OriginalId=invalid-unary-operand-type
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Invalid Unary Operand Type
#### WarningText


#### HelpText
  Emitted when a unary operand is used on an object which does not support this type of operation.


#### Tags
- /tool/Pylint
- /general/Typecheck Rules

#### Settings
- Priority=Critical


## PYLINT_IdM
### Default
#### OriginalId=idiv-method
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Idiv Method
#### WarningText
  __idiv__ method defined

#### HelpText
  Used when an \_\_idiv\_\_ method is defined. Using `__itruediv__` and setting\_\_idiv\_\_ = \_\_itruediv\_\_ should be preferred.(method is not used by Python 3).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_InB
### Default
#### OriginalId=intern-builtin
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Intern Builtin
#### WarningText
  intern built-in referenced

#### HelpText
  Used when the intern built-in is referenced (Moved to sys.intern in Python 3).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_InE
### Default
#### OriginalId=indexing-exception
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Indexing Exception
#### WarningText
  Indexing exceptions will not work on Python 3

#### HelpText
  Indexing exceptions will not work on Python 3. Use `exception.args[index]` instead.


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_InED
### Default
#### OriginalId=invalid-envvar-default
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Invalid Envvar Default
#### WarningText
  %s default type is %s. Expected str or None.

#### HelpText
  Env manipulation functions return None or str values. Supplying anything different as a default may cause bugs. See <a href="https://docs.python.org/3/library/os.html#os.getenv" class="uri" class="uri">https://docs.python.org/3/library/os.html#os.getenv</a>.


#### Tags
- /tool/Pylint
- /general/Stdlib Rules

#### Settings
- Priority=Major


## PYLINT_InM
### Default
#### OriginalId=invalid-metaclass
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Invalid Metaclass
#### WarningText
  Invalid metaclass %r used

#### HelpText
  Emitted whenever we can detect that a class is using, as a metaclass, something which might be invalid for using as a metaclass.


#### Tags
- /tool/Pylint
- /general/Typecheck Rules

#### Settings
- Priority=Critical


## PYLINT_InS
### Default
#### OriginalId=invalid-slots
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Invalid Slots
#### WarningText
  Invalid __slots__ object

#### HelpText
  Used when an invalid \_\_slots\_\_ is found in class. Only a string, an iterable or a sequence is permitted.


#### Tags
- /tool/Pylint
- /general/Class Rules

#### Settings
- Priority=Critical


## PYLINT_InSI
### Default
#### OriginalId=invalid-slice-index
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Invalid Slice Index
#### WarningText
  Slice index is not an int, None, or instance with __index__

#### HelpText
  Used when a slice index is not an integer, None, or an object with an \_\_index\_\_ method.


#### Tags
- /tool/Pylint
- /general/Typecheck Rules

#### Settings
- Priority=Critical


## PYLINT_KABV
### Default
#### OriginalId=keyword-arg-before-vararg
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Keyword Arg Before Vararg
#### WarningText
  Keyword argument before variable positional arguments list in the definition of %s function

#### HelpText
  When defining a keyword argument before variable positional arguments, one can end up in having multiple values passed for the aforementioned parameter in case the method is called with keyword arguments.


#### Tags
- /tool/Pylint
- /general/Typecheck Rules

#### Settings
- Priority=Major


## PYLINT_LAC
### Default
#### OriginalId=len-as-condition
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Len As Condition
#### WarningText
  Do not use `len(SEQUENCE)` to determine if a sequence is empty

#### HelpText
  Used when Pylint detects that len(sequence) is being used inside a condition to determine if a sequence is empty. Instead of comparing the length to 0, rely on the fact that empty sequences are false.


#### Tags
- /tool/Pylint
- /general/Refactoring Rules

#### Settings
- Priority=Minor


## PYLINT_LB
### Default
#### OriginalId=long-builtin
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Long Builtin
#### WarningText
  long built-in referenced

#### HelpText
  Used when the long built-in function is referenced (missing from Python 3).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_LC
### Default
#### OriginalId=literal-comparison
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Literal Comparison
#### WarningText
  Comparison to literal

#### HelpText
  Used when comparing an object to a literal, which is usually what you do not want to do, since you can compare to a different literal than what was expected altogether.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Minor


## PYLINT_LD
### Default
#### OriginalId=locally-disabled
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=Locally Disabled
#### WarningText
  Locally disabling %s (%s)

#### HelpText
  Used when an inline option disables a message or a messages category.


#### Tags
- /tool/Pylint
- /general/Pylint Checker Rules

#### Settings
- Priority=Minor


## PYLINT_LFI
### Default
#### OriginalId=logging-format-interpolation
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Logging Format Interpolation
#### WarningText
  Use % formatting in logging functions and pass the % parameters as arguments

#### HelpText
  Used when a logging statement has a call form of “logging.&lt;logging method&gt;(format\_string.format(format\_args…))”. Such calls should use % formatting instead, but leave interpolation to the logging function by passing the parameters as arguments.


#### Tags
- /tool/Pylint
- /general/Logging Rules

#### Settings
- Priority=Major


## PYLINT_LFT
### Default
#### OriginalId=logging-format-truncated
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Logging Format Truncated
#### WarningText
  Logging format string ends in middle of conversion specifier

#### HelpText
  Used when a logging statement format string terminates before the end of a conversion specifier.


#### Tags
- /tool/Pylint
- /general/Logging Rules

#### Settings
- Priority=Critical


## PYLINT_LNL
### Default
#### OriginalId=logging-not-lazy
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Logging Not Lazy
#### WarningText
  Specify string format arguments as logging function parameters

#### HelpText
  Used when a logging statement has a call form of “logging.&lt;logging method&gt;(format\_string % (format\_args…))”. Such calls should leave string interpolation to the logging method itself and be written “logging.&lt;logging method&gt;(format\_string, format\_args…)” so that the program may avoid incurring the cost of the interpolation in those cases in which no message will be logged. For more, see <a href="http://www.python.org/dev/peps/pep-0282/" class="uri" class="uri">http://www.python.org/dev/peps/pep-0282/</a>.


#### Tags
- /tool/Pylint
- /general/Logging Rules

#### Settings
- Priority=Major


## PYLINT_LS
### Default
#### OriginalId=long-suffix
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Long Suffix
#### WarningText
  Use of long suffix

#### HelpText
  Used when “l” or “L” is used to mark a long integer. This will not work in Python 3, since `int` and `long` types have merged. This message can’t be emitted when using Python &gt;= 3.0.


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Critical


## PYLINT_LTFA
### Default
#### OriginalId=logging-too-few-args
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Logging Too Few Args
#### WarningText
  Not enough arguments for logging format string

#### HelpText
  Used when a logging format string is given too few arguments.


#### Tags
- /tool/Pylint
- /general/Logging Rules

#### Settings
- Priority=Critical


## PYLINT_LTL
### Default
#### OriginalId=line-too-long
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Line Too Long
#### WarningText
  Line too long (%s/%s)

#### HelpText
  Used when a line is longer than a given number of characters.


#### Tags
- /tool/Pylint
- /general/Format Rules

#### Settings
- Priority=Minor


## PYLINT_LTMA
### Default
#### OriginalId=logging-too-many-args
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Logging Too Many Args
#### WarningText
  Too many arguments for logging format string

#### HelpText
  Used when a logging format string is given too many arguments.


#### Tags
- /tool/Pylint
- /general/Logging Rules

#### Settings
- Priority=Critical


## PYLINT_LUF
### Default
#### OriginalId=logging-unsupported-format
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Logging Unsupported Format
#### WarningText
  Unsupported logging format character %r (%#02x) at index %d

#### HelpText
  Used when an unsupported format character is used in a logging statement format string.


#### Tags
- /tool/Pylint
- /general/Logging Rules

#### Settings
- Priority=Critical


## PYLINT_LoE
### Default
#### OriginalId=lost-exception
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Lost Exception
#### WarningText
  %s statement in finally block may swallow exception

#### HelpText
  Used when a break or a return statement is found inside the finally clause of a try…finally block: the exceptions raised in the try clause will be silently swallowed instead of being re-raised.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Major


## PYLINT_LoFI
### Default
#### OriginalId=logging-fstring-interpolation
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Logging Fstring Interpolation
#### WarningText
  Use % formatting in logging functions and pass the % parameters as arguments

#### HelpText
  Used when a logging statement has a call form of “logging.method(f”…“))”. Such calls should use % formatting instead, but leave interpolation to the logging function by passing the parameters as arguments.


#### Tags
- /tool/Pylint
- /general/Logging Rules

#### Settings
- Priority=Major


## PYLINT_MA
### Default
#### OriginalId=metaclass-assignment
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Metaclass Assignment
#### WarningText
  Assigning to a class's __metaclass__ attribute

#### HelpText
  Used when a metaclass is specified by assigning to \_\_metaclass\_\_ (Python 3 specifies the metaclass as a class statement argument).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_MBNI
### Default
#### OriginalId=map-builtin-not-iterating
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Map Builtin Not Iterating
#### WarningText
  map built-in referenced when not iterating

#### HelpText
  Used when the map built-in is referenced in a non-iterating context (returns an iterator in Python 3).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_MBR
### Default
#### OriginalId=misplaced-bare-raise
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Misplaced Bare Raise
#### WarningText
  The raise statement is not inside an except clause

#### HelpText
  Used when a bare raise is not used inside an except clause. This generates an error, since there are no active exceptions to be reraised. An exception to this rule is represented by a bare raise inside a finally clause, which might work, as long as an exception is raised inside the try block, but it is nevertheless a code smell that must not be relied upon.


#### Tags
- /tool/Pylint
- /general/Exception Rules

#### Settings
- Priority=Critical


## PYLINT_MCC
### Default
#### OriginalId=misplaced-comparison-constant
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Misplaced Comparison Constant
#### WarningText
  Comparison should be %s

#### HelpText
  Used when the constant is placed on the left side of a comparison. It is usually clearer in intent to place it in the right hand side of the comparison.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Minor


## PYLINT_MCF
### Default
#### OriginalId=method-check-failed
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=Method Check Failed
#### WarningText
  Unable to check methods signature (%s / %s)

#### HelpText
  Used when Pylint has been unable to check methods signature compatibility for an unexpected reason. Please report this kind if you don't make sense of it.


#### Tags
- /tool/Pylint
- /general/Class Rules

#### Settings
- Priority=Blocker


## PYLINT_MD
### Default
#### OriginalId=missing-docstring
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Missing Docstring
#### WarningText
  Missing %s docstring

#### HelpText
  Used when a module, function, class or method has no docstring.Some special methods like \_\_init\_\_ doesn’t necessary require a docstring.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Minor


## PYLINT_MF
### Default
#### OriginalId=misplaced-future
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Misplaced Future
#### WarningText
  __future__ import is not the first non docstring statement

#### HelpText
  Python 2.5 and greater require \_\_future\_\_ import to be the first non docstring statement in the module.


#### Tags
- /tool/Pylint
- /general/Import Rules

#### Settings
- Priority=Major


## PYLINT_MFA
### Default
#### OriginalId=missing-format-attribute
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Missing Format Attribute
#### WarningText
  Missing format attribute %r in format specifier %r

#### HelpText
  Used when a PEP 3101 format string uses an attribute specifier ({0.length}), but the argument passed for formatting doesn’t have that attribute.


#### Tags
- /tool/Pylint
- /general/String Rules

#### Settings
- Priority=Major


## PYLINT_MFAK
### Default
#### OriginalId=missing-format-argument-key
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Missing Format Argument Key
#### WarningText
  Missing keyword argument %r for format string

#### HelpText
  Used when a PEP 3101 format string that uses named fields doesn’t receive one or more required keywords.


#### Tags
- /tool/Pylint
- /general/String Rules

#### Settings
- Priority=Major


## PYLINT_MFF
### Default
#### OriginalId=misplaced-format-function
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Misplaced Format Function
#### WarningText
  format function is not called on str

#### HelpText
  Emitted when format function is not called on str object. e.g doing print(“value: {}”).format(123) instead of print(“value: {}”.format(123)). This might not be what the user intended to do.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Critical


## PYLINT_MFN
### Default
#### OriginalId=missing-final-newline
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Missing Final Newline
#### WarningText
  Final newline missing

#### HelpText
  Used when the last line in a file is missing a newline.


#### Tags
- /tool/Pylint
- /general/Format Rules

#### Settings
- Priority=Minor


## PYLINT_MFS
### Default
#### OriginalId=mixed-format-string
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Mixed Format String
#### WarningText
  Mixing named and unnamed conversion specifiers in format string

#### HelpText
  Used when a format string contains both named (e.g. ‘%(foo)d’) and unnamed (e.g. ‘%d’) conversion specifiers. This is also used when a named conversion specifier contains \* for the minimum field width and/or precision.


#### Tags
- /tool/Pylint
- /general/String Rules

#### Settings
- Priority=Critical


## PYLINT_MFSK
### Default
#### OriginalId=missing-format-string-key
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Missing Format String Key
#### WarningText
  Missing key %r in format string dictionary

#### HelpText
  Used when a format string that uses named conversion specifiers is used with a dictionary that doesn’t contain all the keys required by the format string.


#### Tags
- /tool/Pylint
- /general/String Rules

#### Settings
- Priority=Critical


## PYLINT_MH
### Default
#### OriginalId=method-hidden
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Method Hidden
#### WarningText
  An attribute defined in %s line %s hides this method

#### HelpText
  Used when a class defines a method which is hidden by an instance attribute from an ancestor class or set by some client code.


#### Tags
- /tool/Pylint
- /general/Class Rules

#### Settings
- Priority=Critical


## PYLINT_MI
### Default
#### OriginalId=mixed-indentation
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Mixed Indentation
#### WarningText
  Found indentation with %ss instead of %ss

#### HelpText
  Used when there are some mixed tabs and spaces in a module.


#### Tags
- /tool/Pylint
- /general/Format Rules

#### Settings
- Priority=Major


## PYLINT_MK
### Default
#### OriginalId=missing-kwoa
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Missing Kwoa
#### WarningText
  Missing mandatory keyword argument %r in %s call

#### HelpText
  Used when a function call does not pass a mandatory keyword-only argument.


#### Tags
- /tool/Pylint
- /general/Typecheck Rules

#### Settings
- Priority=Critical


## PYLINT_MLE
### Default
#### OriginalId=mixed-line-endings
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Mixed Line Endings
#### WarningText
  Mixed line endings LF and CRLF

#### HelpText
  Used when there are mixed (LF and CRLF) newline signs in a file.


#### Tags
- /tool/Pylint
- /general/Format Rules

#### Settings
- Priority=Minor


## PYLINT_MS
### Default
#### OriginalId=multiple-statements
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Multiple Statements
#### WarningText
  More than one statement on a single line

#### HelpText
  Used when more than on statement are found on the same line.


#### Tags
- /tool/Pylint
- /general/Format Rules

#### Settings
- Priority=Minor


## PYLINT_MSA
### Default
#### OriginalId=missing-super-argument
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Missing Super Argument
#### WarningText
  Missing argument to super()

#### HelpText
  Used when the super builtin didn’t receive an argument. This message can’t be emitted when using Python &gt;= 3.0.


#### Tags
- /tool/Pylint
- /general/Newstyle Rules

#### Settings
- Priority=Critical


## PYLINT_MuI
### Default
#### OriginalId=multiple-imports
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Multiple Imports
#### WarningText
  Multiple imports on one line (%s)

#### HelpText
  Used when import statement importing multiple modules is detected.


#### Tags
- /tool/Pylint
- /general/Import Rules

#### Settings
- Priority=Minor


## PYLINT_NABL
### Default
#### OriginalId=non-ascii-bytes-literal
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Non Ascii Bytes Literal
#### WarningText
  Non-ascii bytes literals not supported in 3.x

#### HelpText
  Used when non-ascii bytes literals are found in a program. They are no longer supported in Python 3. This message can’t be emitted when using Python &gt;= 3.0.


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Critical


## PYLINT_NACM
### Default
#### OriginalId=not-async-context-manager
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Not Async Context Manager
#### WarningText
  Async context manager '%s' doesn't implement __aenter__ and __aexit__.

#### HelpText
  Used when an async context manager is used with an object that does not implement the async context management protocol. This message can’t be emitted when using Python &lt; 3.5.


#### Tags
- /tool/Pylint
- /general/Async Rules

#### Settings
- Priority=Critical


## PYLINT_NAG
### Default
#### OriginalId=nonlocal-and-global
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Nonlocal And Global
#### WarningText
  Name %r is nonlocal and global

#### HelpText
  Emitted when a name is both nonlocal and global.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Critical


## PYLINT_NAI
### Default
#### OriginalId=no-absolute-import
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=No Absolute Import
#### WarningText
  import missing `from __future__ import absolute_import`

#### HelpText
  Used when an import is not accompanied by `from __future__ import absolute_import` (default behaviour in Python 3).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_NAM
### Default
#### OriginalId=not-a-mapping
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Not A Mapping
#### WarningText
  Non-mapping value %s is used in a mapping context

#### HelpText
  Used when a non-mapping value is used in place where mapping is expected.


#### Tags
- /tool/Pylint
- /general/Typecheck Rules

#### Settings
- Priority=Critical


## PYLINT_NC
### Default
#### OriginalId=not-callable
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Not Callable
#### WarningText
  %s is not callable

#### HelpText
  Used when an object being called has been inferred to a non callable object.


#### Tags
- /tool/Pylint
- /general/Typecheck Rules

#### Settings
- Priority=Critical


## PYLINT_NCD
### Default
#### OriginalId=no-classmethod-decorator
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=No Classmethod Decorator
#### WarningText
  Consider using a decorator instead of calling classmethod

#### HelpText
  Used when a class method is defined without using the decorator syntax.


#### Tags
- /tool/Pylint
- /general/Class Rules

#### Settings
- Priority=Minor


## PYLINT_NCM
### Default
#### OriginalId=not-context-manager
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Not Context Manager
#### WarningText
  Context manager '%s' doesn't implement __enter__ and __exit__.

#### HelpText
  Used when an instance in a with statement doesn’t implement the context manager protocol(\_\_enter\_\_/\_\_exit\_\_).


#### Tags
- /tool/Pylint
- /general/Typecheck Rules

#### Settings
- Priority=Critical


## PYLINT_NER
### Default
#### OriginalId=no-else-return
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=No Else Return
#### WarningText
  Unnecessary "%s" after "return"

#### HelpText
  Used in order to highlight an unnecessary block of code following an if containing a return statement. As such, it will warn when it encounters an else following a chain of ifs, all of them containing a return statement.


#### Tags
- /tool/Pylint
- /general/Refactoring Rules

#### Settings
- Priority=Minor


## PYLINT_NI
### Default
#### OriginalId=no-init
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=No Init
#### WarningText
  Class has no __init__ method

#### HelpText
  Used when a class has no \_\_init\_\_ method, neither its parent classes.


#### Tags
- /tool/Pylint
- /general/Class Rules

#### Settings
- Priority=Major


## PYLINT_NIL
### Default
#### OriginalId=not-in-loop
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Not In Loop
#### WarningText
  %r not properly in loop

#### HelpText
  Used when break or continue keywords are used outside a loop.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Critical


## PYLINT_NIR
### Default
#### OriginalId=non-iterator-returned
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Non Iterator Returned
#### WarningText
  __iter__ returns non-iterator

#### HelpText
  Used when an \_\_iter\_\_ method returns something which is not an iterable (i.e. has no `__next__` method).


#### Tags
- /tool/Pylint
- /general/Class Rules

#### Settings
- Priority=Critical


## PYLINT_NM
### Default
#### OriginalId=no-member
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=No Member
#### WarningText
  %s %r has no %r member%s

#### HelpText
  Used when a variable is accessed for an unexistent member.


#### Tags
- /tool/Pylint
- /general/Typecheck Rules

#### Settings
- Priority=Critical


## PYLINT_NMA
### Default
#### OriginalId=no-method-argument
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=No Method Argument
#### WarningText
  Method has no argument

#### HelpText
  Used when a method which should have the bound instance as first argument has no argument defined.


#### Tags
- /tool/Pylint
- /general/Class Rules

#### Settings
- Priority=Critical


## PYLINT_NMC
### Default
#### OriginalId=next-method-called
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Next Method Called
#### WarningText
  Called a next() method on an object

#### HelpText
  Used when an object’s next() method is called (Python 3 uses the next() built-in function).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_NMD
### Default
#### OriginalId=next-method-defined
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Next Method Defined
#### WarningText
  next method defined

#### HelpText
  Used when a next method is defined that would be an iterator in Python 2 but is treated as a normal function in Python 3.


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_NNIM
### Default
#### OriginalId=no-name-in-module
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=No Name In Module
#### WarningText
  No name %r in module %r

#### HelpText
  Used when a name cannot be found in a module.


#### Tags
- /tool/Pylint
- /general/Variable Rules

#### Settings
- Priority=Critical


## PYLINT_NO
### Default
#### OriginalId=nonexistent-operator
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Nonexistent Operator
#### WarningText
  Use of the non-existent %s operator

#### HelpText
  Used when you attempt to use the C-style pre-increment or pre-decrement operator -- and ++, which doesn’t exist in Python.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Critical


## PYLINT_NPIC
### Default
#### OriginalId=non-parent-init-called
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Non Parent Init Called
#### WarningText
  __init__ method from a non direct base class %r is called

#### HelpText
  Used when an \_\_init\_\_ method is called on a class which is not in the direct ancestors for the analysed class.


#### Tags
- /tool/Pylint
- /general/Class Rules

#### Settings
- Priority=Major


## PYLINT_NR
### Default
#### OriginalId=notimplemented-raised
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Notimplemented Raised
#### WarningText
  NotImplemented raised - should raise NotImplementedError

#### HelpText
  Used when NotImplemented is raised instead of NotImplementedError.


#### Tags
- /tool/Pylint
- /general/Exception Rules

#### Settings
- Priority=Critical


## PYLINT_NSA
### Default
#### OriginalId=no-self-argument
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=No Self Argument
#### WarningText
  Method should have "self" as first argument

#### HelpText
  Used when a method has an attribute different the “self” as first argument. This is considered as an error since this is a so common convention that you shouldn’t break it!


#### Tags
- /tool/Pylint
- /general/Class Rules

#### Settings
- Priority=Critical


## PYLINT_NSD
### Default
#### OriginalId=no-staticmethod-decorator
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=No Staticmethod Decorator
#### WarningText
  Consider using a decorator instead of calling staticmethod

#### HelpText
  Used when a static method is defined without using the decorator syntax.


#### Tags
- /tool/Pylint
- /general/Class Rules

#### Settings
- Priority=Minor


## PYLINT_NSU
### Default
#### OriginalId=no-self-use
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=No Self Use
#### WarningText
  Method could be a function

#### HelpText
  Used when a method doesn’t use its bound instance, and so could be written as a function.


#### Tags
- /tool/Pylint
- /general/Class Rules

#### Settings
- Priority=Minor


## PYLINT_NVFP
### Default
#### OriginalId=no-value-for-parameter
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=No Value For Parameter
#### WarningText
  No value for argument %s in %s call

#### HelpText
  Used when a function call passes too few arguments.


#### Tags
- /tool/Pylint
- /general/Typecheck Rules

#### Settings
- Priority=Critical


## PYLINT_NWB
### Default
#### OriginalId=nonlocal-without-binding
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Nonlocal Without Binding
#### WarningText
  nonlocal name %s found without binding

#### HelpText
  Emitted when a nonlocal variable does not have an attached name somewhere in the parent scopes.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Critical


## PYLINT_NoAI
### Default
#### OriginalId=not-an-iterable
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Not An Iterable
#### WarningText
  Non-iterable value %s is used in an iterating context

#### HelpText
  Used when a non-iterable value is used in place where iterable is expected.


#### Tags
- /tool/Pylint
- /general/Typecheck Rules

#### Settings
- Priority=Critical


## PYLINT_NoER
### Default
#### OriginalId=no-else-raise
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=No Else Raise
#### WarningText
  Unnecessary "%s" after "raise"

#### HelpText
  Used in order to highlight an unnecessary block of code following an if containing a raise statement. As such, it will warn when it encounters an else following a chain of ifs, all of them containing a raise statement.


#### Tags
- /tool/Pylint
- /general/Refactoring Rules

#### Settings
- Priority=Minor


## PYLINT_NoM
### Default
#### OriginalId=nonzero-method
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Nonzero Method
#### WarningText
  __nonzero__ method defined

#### HelpText
  Used when a \_\_nonzero\_\_ method is defined (method is not used by Python 3).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_OD
### Default
#### OriginalId=old-division
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Old Division
#### WarningText
  division w/o __future__ statement

#### HelpText
  Used for non-floor division w/o a float literal or `from __future__ import division` (Python 3 returns a float for int division unconditionally).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_OM
### Default
#### OriginalId=oct-method
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Oct Method
#### WarningText
  __oct__ method defined

#### HelpText
  Used when an \_\_oct\_\_ method is defined (method is not used by Python 3).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_ONO
### Default
#### OriginalId=old-ne-operator
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Old Ne Operator
#### WarningText
  Use of the <> operator

#### HelpText
  Used when the deprecated “&lt;&gt;” operator is used instead of “!=”. This is removed in Python 3. This message can’t be emitted when using Python &gt;= 3.0.


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Critical


## PYLINT_OOL
### Default
#### OriginalId=old-octal-literal
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Old Octal Literal
#### WarningText
  Use of old octal literal

#### HelpText
  Used when encountering the old octal syntax, removed in Python 3. To use the new syntax, prepend 0o on the number. This message can’t be emitted when using Python &gt;= 3.0.


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Critical


## PYLINT_ORS
### Default
#### OriginalId=old-raise-syntax
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Old Raise Syntax
#### WarningText
  Use raise ErrorClass(args) instead of raise ErrorClass, args.

#### HelpText
  Used when the alternate raise syntax ‘raise foo, bar’ is used instead of ‘raise foo(bar)’.


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Critical


## PYLINT_PA
### Default
#### OriginalId=protected-access
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Protected Access
#### WarningText
  Access to a protected member %s of a client class

#### HelpText
  Used when a protected member (i.e. class member with a name beginning with an underscore) is access outside the class or a descendant of the class where it’s defined.


#### Tags
- /tool/Pylint
- /general/Class Rules

#### Settings
- Priority=Major


## PYLINT_PE
### Default
#### OriginalId=parse-error
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=Parse Error
#### WarningText
  error while code parsing: %s

#### HelpText
  Used when an exception occurred while building the Astroid representation which could be handled by astroid.


#### Tags
- /tool/Pylint
- /general/Pylint Checker Rules

#### Settings
- Priority=Blocker


## PYLINT_PS
### Default
#### OriginalId=pointless-statement
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Pointless Statement
#### WarningText
  Statement seems to have no effect

#### HelpText
  Used when a statement doesn’t have (or at least seems to) any effect.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Major


## PYLINT_PSS
### Default
#### OriginalId=pointless-string-statement
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Pointless String Statement
#### WarningText
  String statement has no effect

#### HelpText
  Used when a string is used as a statement (which of course has no effect). This is a particular case of W0104 with its own message so you can easily disable it if you’re using those strings as documentation, instead of comments.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Major


## PYLINT_PU
### Default
#### OriginalId=parameter-unpacking
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Parameter Unpacking
#### WarningText
  Parameter unpacking specified

#### HelpText
  Used when parameter unpacking is specified for a function(Python 3 doesn’t allow it).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Critical


## PYLINT_PUV
### Default
#### OriginalId=possibly-unused-variable
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Possibly Unused Variable
#### WarningText
  Possibly unused variable %r

#### HelpText
  Used when a variable is defined but might not be used. The possibility comes from the fact that locals() might be used, which could consume or not the said variable.


#### Tags
- /tool/Pylint
- /general/Variable Rules

#### Settings
- Priority=Major


## PYLINT_PrS
### Default
#### OriginalId=print-statement
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Print Statement
#### WarningText
  print statement used

#### HelpText
  Used when a print statement is used (`print` is a function in Python 3).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Critical


## PYLINT_R
### Default
#### OriginalId=reimported
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Reimported
#### WarningText
  Reimport %r (imported line %s)

#### HelpText
  Used when a module is reimported multiple times.


#### Tags
- /tool/Pylint
- /general/Import Rules

#### Settings
- Priority=Major


## PYLINT_RAFL
### Default
#### OriginalId=redefined-argument-from-local
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Redefined Argument From Local
#### WarningText
  Redefining argument with the local name %r

#### HelpText
  Used when a local name is redefining an argument, which might suggest a potential error. This is taken in account only for a handful of name binding operations, such as for iteration, with statement assignment and exception handler assignment.


#### Tags
- /tool/Pylint
- /general/Refactoring Rules

#### Settings
- Priority=Minor


## PYLINT_RAIG
### Default
#### OriginalId=return-arg-in-generator
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Return Arg In Generator
#### WarningText
  Return with argument inside generator

#### HelpText
  Used when a “return” statement with an argument is found outside in a generator function or method (e.g. with some “yield” statements). This message can’t be emitted when using Python &gt;= 3.3.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Critical


## PYLINT_RB
### Default
#### OriginalId=raw_input-builtin
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Raw_input Builtin
#### WarningText
  raw_input built-in referenced

#### HelpText
  Used when the raw\_input built-in function is referenced (missing from Python 3).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_RBNI
### Default
#### OriginalId=range-builtin-not-iterating
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Range Builtin Not Iterating
#### WarningText
  range built-in referenced when not iterating

#### HelpText
  Used when the range built-in is referenced in a non-iterating context (returns an iterator in Python 3).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_RBT
### Default
#### OriginalId=raising-bad-type
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Raising Bad Type
#### WarningText
  Raising %s while only classes or instances are allowed

#### HelpText
  Used when something which is neither a class, an instance or a string is raised (i.e. a `TypeError` will be raised).


#### Tags
- /tool/Pylint
- /general/Exception Rules

#### Settings
- Priority=Critical


## PYLINT_RBTL
### Default
#### OriginalId=relative-beyond-top-level
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Relative Beyond Top Level
#### WarningText
  Attempted relative import beyond top-level package

#### HelpText
  Used when a relative import tries to access too many levels in the current package.


#### Tags
- /tool/Pylint
- /general/Import Rules

#### Settings
- Priority=Critical


## PYLINT_RCF
### Default
#### OriginalId=raw-checker-failed
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=Raw Checker Failed
#### WarningText
  Unable to run raw checkers on built-in module %s

#### HelpText
  Used to inform that a built-in module has not been checked using the raw checkers.


#### Tags
- /tool/Pylint
- /general/Pylint Checker Rules

#### Settings
- Priority=Minor


## PYLINT_RFT
### Default
#### OriginalId=raising-format-tuple
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Raising Format Tuple
#### WarningText
  Exception arguments suggest string formatting might be intended

#### HelpText
  Used when passing multiple arguments to an exception constructor, the first of them a string literal containing what appears to be placeholders intended for formatting.


#### Tags
- /tool/Pylint
- /general/Exception Rules

#### Settings
- Priority=Major


## PYLINT_RI
### Default
#### OriginalId=relative-import
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Relative Import
#### WarningText
  Relative import %r, should be %r

#### HelpText
  Used when an import relative to the package directory is detected. This message can’t be emitted when using Python &gt;= 3.0.


#### Tags
- /tool/Pylint
- /general/Import Rules

#### Settings
- Priority=Major


## PYLINT_RIH
### Default
#### OriginalId=redefine-in-handler
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Redefine In Handler
#### WarningText
  Redefining name %r from %s in exception handler

#### HelpText
  Used when an exception handler assigns the exception to an existing name.


#### Tags
- /tool/Pylint
- /general/Variable Rules

#### Settings
- Priority=Major


## PYLINT_RII
### Default
#### OriginalId=return-in-init
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Return In Init
#### WarningText
  Explicit return in __init__

#### HelpText
  Used when the special class method \_\_init\_\_ has an explicit return value.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Critical


## PYLINT_RK
### Default
#### OriginalId=repeated-keyword
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Repeated Keyword
#### WarningText
  Got multiple values for keyword argument %r in function call

#### HelpText
  Emitted when a function call got multiple values for a keyword.


#### Tags
- /tool/Pylint
- /general/Typecheck Rules

#### Settings
- Priority=Critical


## PYLINT_RKA
### Default
#### OriginalId=redundant-keyword-arg
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Redundant Keyword Arg
#### WarningText
  Argument %r passed by position and keyword in %s call

#### HelpText
  Used when a function call would result in assigning multiple values to a function parameter, one value from a positional argument and one from a keyword argument.


#### Tags
- /tool/Pylint
- /general/Typecheck Rules

#### Settings
- Priority=Critical


## PYLINT_RM
### Default
#### OriginalId=rdiv-method
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Rdiv Method
#### WarningText
  __rdiv__ method defined

#### HelpText
  Used when a \_\_rdiv\_\_ method is defined. Using `__rtruediv__` and setting\_\_rdiv\_\_ = \_\_rtruediv\_\_ should be preferred.(method is not used by Python 3).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_RNE
### Default
#### OriginalId=raising-non-exception
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Raising Non Exception
#### WarningText
  Raising a new style class which doesn't inherit from BaseException

#### HelpText
  Used when a new style class which doesn’t inherit from BaseException is raised.


#### Tags
- /tool/Pylint
- /general/Exception Rules

#### Settings
- Priority=Critical


## PYLINT_ROF
### Default
#### OriginalId=return-outside-function
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Return Outside Function
#### WarningText
  Return outside function

#### HelpText
  Used when a “return” statement is found outside a function or method.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Critical


## PYLINT_RON
### Default
#### OriginalId=redefined-outer-name
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Redefined Outer Name
#### WarningText
  Redefining name %r from outer scope (line %s)

#### HelpText
  Used when a variable’s name hides a name defined in the outer scope.


#### Tags
- /tool/Pylint
- /general/Variable Rules

#### Settings
- Priority=Major


## PYLINT_RS
### Default
#### OriginalId=raising-string
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Raising String
#### WarningText
  Raising a string exception

#### HelpText
  Used when a string exception is raised. This will not work on Python 3.


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_RUA
### Default
#### OriginalId=redundant-unittest-assert
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Redundant Unittest Assert
#### WarningText
  Redundant use of %s with constant value %r

#### HelpText
  The first argument of assertTrue and assertFalse is a condition. If a constant is passed as parameter, that condition will be always true. In this case a warning should be emitted.


#### Tags
- /tool/Pylint
- /general/Stdlib Rules

#### Settings
- Priority=Major


## PYLINT_ReB
### Default
#### OriginalId=redefined-builtin
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Redefined Builtin
#### WarningText
  Redefining built-in %r

#### HelpText
  Used when a variable or function override a built-in.


#### Tags
- /tool/Pylint
- /general/Variable Rules

#### Settings
- Priority=Major


## PYLINT_RedB
### Default
#### OriginalId=reduce-builtin
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Reduce Builtin
#### WarningText
  reduce built-in referenced

#### HelpText
  Used when the reduce built-in function is referenced (missing from Python 3).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_RelB
### Default
#### OriginalId=reload-builtin
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Reload Builtin
#### WarningText
  reload built-in referenced

#### HelpText
  Used when the reload built-in function is referenced (missing from Python 3). You can use instead imp.reload or importlib.reload.


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_RoB
### Default
#### OriginalId=round-builtin
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Round Builtin
#### WarningText
  round built-in referenced

#### HelpText
  Used when the round built-in is referenced (backwards-incompatible semantics in Python 3).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_SB
### Default
#### OriginalId=standarderror-builtin
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Standarderror Builtin
#### WarningText
  StandardError built-in referenced

#### HelpText
  Used when the StandardError built-in function is referenced (missing from Python 3).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_SBE
### Default
#### OriginalId=simplify-boolean-expression
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Simplify Boolean Expression
#### WarningText
  Boolean expression may be simplified to %s

#### HelpText
  Emitted when redundant pre-python 2.5 ternary syntax is used.


#### Tags
- /tool/Pylint
- /general/Refactoring Rules

#### Settings
- Priority=Minor


## PYLINT_SC
### Default
#### OriginalId=singleton-comparison
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Singleton Comparison
#### WarningText
  Comparison to %s should be %s

#### HelpText
  Used when an expression is compared to singleton values like True, False or None.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Minor


## PYLINT_SCA
### Default
#### OriginalId=self-cls-assignment
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Self Cls Assignment
#### WarningText
  Invalid assignment to %s in method

#### HelpText
  Invalid assignment to self or cls in instance or class method respectively.


#### Tags
- /tool/Pylint
- /general/Variable Rules

#### Settings
- Priority=Major


## PYLINT_SCE
### Default
#### OriginalId=shallow-copy-environ
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Shallow Copy Environ
#### WarningText
  Using copy.copy(os.environ). Use os.environ.copy() instead.

#### HelpText
  os.environ is not a dict object but proxy object, so shallow copy has still effects on original object. See <a href="https://bugs.python.org/issue15373" class="uri" class="uri">https://bugs.python.org/issue15373</a> for reference.


#### Tags
- /tool/Pylint
- /general/Stdlib Rules

#### Settings
- Priority=Major


## PYLINT_SD
### Default
#### OriginalId=signature-differs
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Signature Differs
#### WarningText
  Signature differs from %s %r method

#### HelpText
  Used when a method signature is different than in the implemented interface or in an overridden method.


#### Tags
- /tool/Pylint
- /general/Class Rules

#### Settings
- Priority=Major


## PYLINT_SE
### Default
#### OriginalId=syntax-error
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=Syntax Error
#### WarningText


#### HelpText
  Used when a syntax error is raised for a module.


#### Tags
- /tool/Pylint
- /general/Pylint Checker Rules

#### Settings
- Priority=Critical


## PYLINT_SIE
### Default
#### OriginalId=simplifiable-if-expression
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Simplifiable If Expression
#### WarningText
  The if expression can be replaced with %s

#### HelpText
  Used when an if expression can be replaced with ‘bool(test)’.


#### Tags
- /tool/Pylint
- /general/Refactoring Rules

#### Settings
- Priority=Minor


## PYLINT_SINC
### Default
#### OriginalId=super-init-not-called
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Super Init Not Called
#### WarningText
  __init__ method from base class %r is not called

#### HelpText
  Used when an ancestor class method has an \_\_init\_\_ method which is not called by a derived class.


#### Tags
- /tool/Pylint
- /general/Class Rules

#### Settings
- Priority=Major


## PYLINT_SIR
### Default
#### OriginalId=stop-iteration-return
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Stop Iteration Return
#### WarningText
  Do not raise StopIteration in generator, use return statement instead

#### HelpText
  According to PEP479, the raise of StopIteration to end the loop of a generator may lead to hard to find bugs. This PEP specify that raise StopIteration has to be replaced by a simple return statement.


#### Tags
- /tool/Pylint
- /general/Refactoring Rules

#### Settings
- Priority=Minor


## PYLINT_SIS
### Default
#### OriginalId=simplifiable-if-statement
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Simplifiable If Statement
#### WarningText
  The if statement can be replaced with %s

#### HelpText
  Used when an if statement can be replaced with ‘bool(test)’.


#### Tags
- /tool/Pylint
- /general/Refactoring Rules

#### Settings
- Priority=Minor


## PYLINT_SM
### Default
#### OriginalId=setslice-method
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Setslice Method
#### WarningText
  __setslice__ method defined

#### HelpText
  Used when a \_\_setslice\_\_ method is defined (method is not used by Python 3).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_SMI
### Default
#### OriginalId=sys-max-int
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Sys Max Int
#### WarningText
  sys.maxint removed in Python 3

#### HelpText
  Used when accessing sys.maxint. Use sys.maxsize instead.


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_SNAT
### Default
#### OriginalId=star-needs-assignment-target
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Star Needs Assignment Target
#### WarningText
  Can use starred expression only in assignment target

#### HelpText
  Emitted when a star expression is not used in an assignment target.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Critical


## PYLINT_SP
### Default
#### OriginalId=superfluous-parens
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Superfluous Parens
#### WarningText
  Unnecessary parens after %r keyword

#### HelpText
  Used when a single item in parentheses follows an if, for, or other keyword.


#### Tags
- /tool/Pylint
- /general/Format Rules

#### Settings
- Priority=Minor


## PYLINT_SPPF
### Default
#### OriginalId=subprocess-popen-preexec-fn
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Subprocess Popen Preexec Fn
#### WarningText
  Using preexec_fn keyword which may be unsafe in the presence of threads

#### HelpText
  The preexec\_fn parameter is not safe to use in the presence of threads in your application. The child process could deadlock before exec is called. If you must use it, keep it trivial! Minimize the number of libraries you call into.<a href="https://docs.python.org/3/library/subprocess.html#popen-constructor" class="uri" class="uri">https://docs.python.org/3/library/subprocess.html#popen-constructor</a>.


#### Tags
- /tool/Pylint
- /general/Stdlib Rules

#### Settings
- Priority=Major


## PYLINT_SSUFS
### Default
#### OriginalId=single-string-used-for-slots
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Single String Used For Slots
#### WarningText
  Class __slots__ should be a non-string iterable

#### HelpText
  Used when a class \_\_slots\_\_ is a simple string, rather than an iterable.


#### Tags
- /tool/Pylint
- /general/Class Rules

#### Settings
- Priority=Minor


## PYLINT_SuM
### Default
#### OriginalId=suppressed-message
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=Suppressed Message
#### WarningText
  Suppressed %s (from line %d)

#### HelpText
  A message was triggered on a line, but suppressed explicitly by a disable= comment in the file. This message is not generated for messages that are ignored due to configuration settings.


#### Tags
- /tool/Pylint
- /general/Pylint Checker Rules

#### Settings
- Priority=Minor


## PYLINT_TCT
### Default
#### OriginalId=trailing-comma-tuple
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Trailing Comma Tuple
#### WarningText
  Disallow trailing comma tuple

#### HelpText
  In Python, a tuple is actually created by the comma symbol, not by the parentheses. Unfortunately, one can actually create a tuple by misplacing a trailing comma, which can lead to potential weird bugs in your code. You should always use parentheses explicitly for creating a tuple.


#### Tags
- /tool/Pylint
- /general/Refactoring Rules

#### Settings
- Priority=Minor


## PYLINT_TER
### Default
#### OriginalId=try-except-raise
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Try Except Raise
#### WarningText
  The except handler raises immediately

#### HelpText
  Used when an except handler uses raise as its first or only operator. This is useless because it raises back the exception immediately. Remove the raise operator or the entire try-except-raise block!


#### Tags
- /tool/Pylint
- /general/Exception Rules

#### Settings
- Priority=Major


## PYLINT_TFFA
### Default
#### OriginalId=too-few-format-args
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Too Few Format Args
#### WarningText
  Not enough arguments for format string

#### HelpText
  Used when a format string that uses unnamed conversion specifiers is given too few arguments.


#### Tags
- /tool/Pylint
- /general/String Rules

#### Settings
- Priority=Critical


## PYLINT_TFPM
### Default
#### OriginalId=too-few-public-methods
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Too Few Public Methods
#### WarningText
  Too few public methods (%s/%s)

#### HelpText
  Used when class has too few public methods, so be sure it’s really worth it.


#### Tags
- /tool/Pylint
- /general/Design Rules

#### Settings
- Priority=Minor


## PYLINT_TFS
### Default
#### OriginalId=truncated-format-string
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Truncated Format String
#### WarningText
  Format string ends in middle of conversion specifier

#### HelpText
  Used when a format string terminates before the end of a conversion specifier.


#### Tags
- /tool/Pylint
- /general/String Rules

#### Settings
- Priority=Critical


## PYLINT_TMA
### Default
#### OriginalId=too-many-ancestors
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Too Many Ancestors
#### WarningText
  Too many ancestors (%s/%s)

#### HelpText
  Used when class has too many parent classes, try to reduce this to get a simpler (and so easier to use) class.


#### Tags
- /tool/Pylint
- /general/Design Rules

#### Settings
- Priority=Minor


## PYLINT_TMB
### Default
#### OriginalId=too-many-branches
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Too Many Branches
#### WarningText
  Too many branches (%s/%s)

#### HelpText
  Used when a function or method has too many branches, making it hard to follow.


#### Tags
- /tool/Pylint
- /general/Design Rules

#### Settings
- Priority=Minor


## PYLINT_TMBE
### Default
#### OriginalId=too-many-boolean-expressions
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Too Many Boolean Expressions
#### WarningText
  Too many boolean expressions in if statement (%s/%s)

#### HelpText
  Used when an if statement contains too many boolean expressions.


#### Tags
- /tool/Pylint
- /general/Design Rules

#### Settings
- Priority=Minor


## PYLINT_TMFA
### Default
#### OriginalId=too-many-format-args
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Too Many Format Args
#### WarningText
  Too many arguments for format string

#### HelpText
  Used when a format string that uses unnamed conversion specifiers is given too many arguments.


#### Tags
- /tool/Pylint
- /general/String Rules

#### Settings
- Priority=Critical


## PYLINT_TMIA
### Default
#### OriginalId=too-many-instance-attributes
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Too Many Instance Attributes
#### WarningText
  Too many instance attributes (%s/%s)

#### HelpText
  Used when class has too many instance attributes, try to reduce this to get a simpler (and so easier to use) class.


#### Tags
- /tool/Pylint
- /general/Design Rules

#### Settings
- Priority=Minor


## PYLINT_TML
### Default
#### OriginalId=too-many-lines
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Too Many Lines
#### WarningText
  Too many lines in module (%s/%s)

#### HelpText
  Used when a module has too many lines, reducing its readability.


#### Tags
- /tool/Pylint
- /general/Format Rules

#### Settings
- Priority=Minor


## PYLINT_TMNB
### Default
#### OriginalId=too-many-nested-blocks
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Too Many Nested Blocks
#### WarningText
  Too many nested blocks (%s/%s)

#### HelpText
  Used when a function or a method has too many nested blocks. This makes the code less understandable and maintainable.


#### Tags
- /tool/Pylint
- /general/Refactoring Rules

#### Settings
- Priority=Minor


## PYLINT_TMPM
### Default
#### OriginalId=too-many-public-methods
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Too Many Public Methods
#### WarningText
  Too many public methods (%s/%s)

#### HelpText
  Used when class has too many public methods, try to reduce this to get a simpler (and so easier to use) class.


#### Tags
- /tool/Pylint
- /general/Design Rules

#### Settings
- Priority=Minor


## PYLINT_TMRS
### Default
#### OriginalId=too-many-return-statements
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Too Many Return Statements
#### WarningText
  Too many return statements (%s/%s)

#### HelpText
  Used when a function or method has too many return statement, making it hard to follow.


#### Tags
- /tool/Pylint
- /general/Design Rules

#### Settings
- Priority=Minor


## PYLINT_TMS
### Default
#### OriginalId=too-many-statements
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Too Many Statements
#### WarningText
  Too many statements (%s/%s)

#### HelpText
  Used when a function or method has too many statements. You should then split it in smaller functions / methods.


#### Tags
- /tool/Pylint
- /general/Design Rules

#### Settings
- Priority=Minor


## PYLINT_TMSE
### Default
#### OriginalId=too-many-star-expressions
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Too Many Star Expressions
#### WarningText
  More than one starred expression in assignment

#### HelpText
  Emitted when there are more than one starred expressions (`*x`) in an assignment. This is a SyntaxError.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Critical


## PYLINT_TN
### Default
#### OriginalId=trailing-newlines
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Trailing Newlines
#### WarningText
  Trailing newlines

#### HelpText
  Used when there are trailing blank lines in a file.


#### Tags
- /tool/Pylint
- /general/Format Rules

#### Settings
- Priority=Minor


## PYLINT_TW
### Default
#### OriginalId=trailing-whitespace
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Trailing Whitespace
#### WarningText
  Trailing whitespace

#### HelpText
  Used when there is whitespace between the end of a line and the newline.


#### Tags
- /tool/Pylint
- /general/Format Rules

#### Settings
- Priority=Minor


## PYLINT_ToMA
### Default
#### OriginalId=too-many-arguments
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Too Many Arguments
#### WarningText
  Too many arguments (%s/%s)

#### HelpText
  Used when a function or method takes too many arguments.


#### Tags
- /tool/Pylint
- /general/Design Rules

#### Settings
- Priority=Minor


## PYLINT_ToMFA
### Default
#### OriginalId=too-many-function-args
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Too Many Function Args
#### WarningText
  Too many positional arguments for %s call

#### HelpText
  Used when a function call passes too many positional arguments.


#### Tags
- /tool/Pylint
- /general/Typecheck Rules

#### Settings
- Priority=Critical


## PYLINT_ToML
### Default
#### OriginalId=too-many-locals
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Too Many Locals
#### WarningText
  Too many local variables (%s/%s)

#### HelpText
  Used when a function or method has too many local variables.


#### Tags
- /tool/Pylint
- /general/Design Rules

#### Settings
- Priority=Minor


## PYLINT_U
### Default
#### OriginalId=unreachable
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unreachable
#### WarningText
  Unreachable code

#### HelpText
  Used when there is some code behind a “return” or “raise” statement, which will never be accessed.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Major


## PYLINT_UA
### Default
#### OriginalId=unused-argument
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unused Argument
#### WarningText
  Unused argument %r

#### HelpText
  Used when a function or method argument is not used.


#### Tags
- /tool/Pylint
- /general/Variable Rules

#### Settings
- Priority=Major


## PYLINT_UAO
### Default
#### OriginalId=unsupported-assignment-operation
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unsupported Assignment Operation
#### WarningText
  %r does not support item assignment

#### HelpText
  Emitted when an object does not support item assignment (i.e. doesn’t define \_\_setitem\_\_ method).


#### Tags
- /tool/Pylint
- /general/Typecheck Rules

#### Settings
- Priority=Critical


## PYLINT_UAV
### Default
#### OriginalId=undefined-all-variable
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Undefined All Variable
#### WarningText
  Undefined variable name %r in __all__

#### HelpText
  Used when an undefined variable name is referenced in \_\_all\_\_.


#### Tags
- /tool/Pylint
- /general/Variable Rules

#### Settings
- Priority=Critical


## PYLINT_UB
### Default
#### OriginalId=unicode-builtin
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unicode Builtin
#### WarningText
  unicode built-in referenced

#### HelpText
  Used when the unicode built-in function is referenced (missing from Python 3).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_UBA
### Default
#### OriginalId=used-before-assignment
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Used Before Assignment
#### WarningText
  Using variable %r before assignment

#### HelpText
  Used when a local variable is accessed before its assignment.


#### Tags
- /tool/Pylint
- /general/Variable Rules

#### Settings
- Priority=Critical


## PYLINT_UBO
### Default
#### OriginalId=unsupported-binary-operation
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unsupported Binary Operation
#### WarningText


#### HelpText
  Emitted when a binary arithmetic operation between two operands is not supported.


#### Tags
- /tool/Pylint
- /general/Typecheck Rules

#### Settings
- Priority=Critical


## PYLINT_UCA
### Default
#### OriginalId=using-cmp-argument
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Using Cmp Argument
#### WarningText
  Using the cmp argument for list.sort / sorted

#### HelpText
  Using the cmp argument for list.sort or the sorted builtin should be avoided, since it was removed in Python 3. Using either `key` or `functools.cmp_to_key` should be preferred.


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_UCT
### Default
#### OriginalId=using-constant-test
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Using Constant Test
#### WarningText
  Using a conditional statement with a constant value

#### HelpText
  Emitted when a conditional statement (If or ternary if) uses a constant value for its test. This might not be what the user intended to do.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Major


## PYLINT_UDK
### Default
#### OriginalId=unhashable-dict-key
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unhashable Dict Key
#### WarningText
  Dict key is unhashable

#### HelpText
  Emitted when a dict key is not hashable (i.e. doesn’t define \_\_hash\_\_ method).


#### Tags
- /tool/Pylint
- /general/Typecheck Rules

#### Settings
- Priority=Critical


## PYLINT_UDO
### Default
#### OriginalId=unsupported-delete-operation
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unsupported Delete Operation
#### WarningText
  %r does not support item deletion

#### HelpText
  Emitted when an object does not support item deletion (i.e. doesn’t define \_\_delitem\_\_ method).


#### Tags
- /tool/Pylint
- /general/Typecheck Rules

#### Settings
- Priority=Critical


## PYLINT_UEOL
### Default
#### OriginalId=useless-else-on-loop
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Useless Else On Loop
#### WarningText
  Else clause on loop without a break statement

#### HelpText
  Loops should only have an else clause if they can exit early with a break statement, otherwise the statements under else should be on the same scope as the loop itself.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Major


## PYLINT_UFSA
### Default
#### OriginalId=unused-format-string-argument
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unused Format String Argument
#### WarningText
  Unused format argument %r

#### HelpText
  Used when a PEP 3101 format string that uses named fields is used with an argument that is not required by the format string.


#### Tags
- /tool/Pylint
- /general/String Rules

#### Settings
- Priority=Major


## PYLINT_UFSK
### Default
#### OriginalId=unused-format-string-key
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unused Format String Key
#### WarningText
  Unused key %r in format string dictionary

#### HelpText
  Used when a format string that uses named conversion specifiers is used with a dictionary that contains keys not required by the format string.


#### Tags
- /tool/Pylint
- /general/String Rules

#### Settings
- Priority=Major


## PYLINT_UIA
### Default
#### OriginalId=useless-import-alias
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Useless Import Alias
#### WarningText
  Import alias does not rename original package

#### HelpText
  Used when an import alias is same as original package.e.g using import numpy as numpy instead of import numpy as np.


#### Tags
- /tool/Pylint
- /general/Import Rules

#### Settings
- Priority=Minor


## PYLINT_UIE
### Default
#### OriginalId=unpacking-in-except
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unpacking In Except
#### WarningText
  Implicit unpacking of exceptions is not supported in Python 3

#### HelpText
  Python3 will not allow implicit unpacking of exceptions in except clauses. See <a href="http://www.python.org/dev/peps/pep-3110/" class="uri" class="uri">http://www.python.org/dev/peps/pep-3110/</a>.


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Critical


## PYLINT_UIO
### Default
#### OriginalId=unrecognized-inline-option
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=Unrecognized Inline Option
#### WarningText
  Unrecognized file option %r

#### HelpText
  Used when an unknown inline option is encountered.


#### Tags
- /tool/Pylint
- /general/Pylint Checker Rules

#### Settings
- Priority=Critical


## PYLINT_UKA
### Default
#### OriginalId=unexpected-keyword-arg
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unexpected Keyword Arg
#### WarningText
  Unexpected keyword argument %r in %s call

#### HelpText
  Used when a function call passes a keyword argument that doesn’t correspond to one of the function’s parameter names.


#### Tags
- /tool/Pylint
- /general/Typecheck Rules

#### Settings
- Priority=Critical


## PYLINT_UL
### Default
#### OriginalId=unnecessary-lambda
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unnecessary Lambda
#### WarningText
  Lambda may not be necessary

#### HelpText
  Used when the body of a lambda expression is a function call on the same argument list as the lambda itself; such lambda expressions are in all but a few cases replaceable with the function being called in the body of the lambda.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Major


## PYLINT_ULEF
### Default
#### OriginalId=unexpected-line-ending-format
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unexpected Line Ending Format
#### WarningText
  Unexpected line ending format. There is '%s' while it should be '%s'.

#### HelpText
  Used when there is different newline than expected.


#### Tags
- /tool/Pylint
- /general/Format Rules

#### Settings
- Priority=Minor


## PYLINT_ULV
### Default
#### OriginalId=undefined-loop-variable
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Undefined Loop Variable
#### WarningText
  Using possibly undefined loop variable %r

#### HelpText
  Used when a loop variable (i.e. defined by a for loop or a list comprehension or a generator expression) is used outside the loop.


#### Tags
- /tool/Pylint
- /general/Variable Rules

#### Settings
- Priority=Major


## PYLINT_UMT
### Default
#### OriginalId=unsupported-membership-test
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unsupported Membership Test
#### WarningText
  Value '%s' doesn't support membership test

#### HelpText
  Emitted when an instance in membership test expression doesn’t implement membership protocol (\_\_contains\_\_/\_\_iter\_\_/\_\_getitem\_\_).


#### Tags
- /tool/Pylint
- /general/Typecheck Rules

#### Settings
- Priority=Critical


## PYLINT_UN
### Default
#### OriginalId=unneeded-not
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unneeded Not
#### WarningText
  Consider changing "%s" to "%s"

#### HelpText
  Used when a boolean expression contains an unneeded negation.


#### Tags
- /tool/Pylint
- /general/Refactoring Rules

#### Settings
- Priority=Minor


## PYLINT_UNS
### Default
#### OriginalId=unpacking-non-sequence
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unpacking Non Sequence
#### WarningText
  Attempting to unpack a non-sequence%s

#### HelpText
  Used when something which is not a sequence is used in an unpack assignment.


#### Tags
- /tool/Pylint
- /general/Variable Rules

#### Settings
- Priority=Critical


## PYLINT_UO
### Default
#### OriginalId=unsubscriptable-object
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unsubscriptable Object
#### WarningText
  Value '%s' is unsubscriptable

#### HelpText
  Emitted when a subscripted value doesn’t support subscription (i.e. doesn’t define \_\_getitem\_\_ method or \_\_class\_getitem\_\_ for a class).


#### Tags
- /tool/Pylint
- /general/Typecheck Rules

#### Settings
- Priority=Critical


## PYLINT_UOI
### Default
#### OriginalId=useless-object-inheritance
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Useless Object Inheritance
#### WarningText
  Class %r inherits from object, can be safely removed from bases in python3

#### HelpText
  Used when a class inherit from object, which under python3 is implicit, hence can be safely removed from bases.


#### Tags
- /tool/Pylint
- /general/Class Rules

#### Settings
- Priority=Minor


## PYLINT_UP
### Default
#### OriginalId=unnecessary-pass
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unnecessary Pass
#### WarningText
  Unnecessary pass statement

#### HelpText
  Used when a “pass” statement that can be avoided is encountered.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Major


## PYLINT_UPGD
### Default
#### OriginalId=used-prior-global-declaration
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Used Prior Global Declaration
#### WarningText
  Name %r is used prior to global declaration

#### HelpText
  Emitted when a name is used prior a global declaration, which results in an error since Python 3.6. This message can’t be emitted when using Python &lt; 3.6.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Critical


## PYLINT_UR
### Default
#### OriginalId=useless-return
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Useless Return
#### WarningText
  Useless return at end of function or method

#### HelpText
  Emitted when a single “return” or “return None” statement is found at the end of function or method definition. This statement can safely be removed because Python will implicitly return None.


#### Tags
- /tool/Pylint
- /general/Refactoring Rules

#### Settings
- Priority=Minor


## PYLINT_US
### Default
#### OriginalId=unnecessary-semicolon
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unnecessary Semicolon
#### WarningText
  Unnecessary semicolon

#### HelpText
  Used when a statement is ended by a semi-colon (“;”), which isn’t necessary (that’s python, not C ;).


#### Tags
- /tool/Pylint
- /general/Format Rules

#### Settings
- Priority=Major


## PYLINT_USD
### Default
#### OriginalId=useless-super-delegation
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Useless Super Delegation
#### WarningText
  Useless super delegation in method %r

#### HelpText
  Used whenever we can detect that an overridden method is useless, relying on super() delegation to do the same thing as another method from the MRO.


#### Tags
- /tool/Pylint
- /general/Class Rules

#### Settings
- Priority=Major


## PYLINT_USMI
### Default
#### OriginalId=use-symbolic-message-instead
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Use Symbolic Message Instead
#### WarningText


#### HelpText
  Used when a message is enabled or disabled by id.


#### Tags
- /tool/Pylint
- /general/Miscellaneous Rules

#### Settings
- Priority=Minor


## PYLINT_USMS
### Default
#### OriginalId=unexpected-special-method-signature
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unexpected Special Method Signature
#### WarningText
  The special method %r expects %s param(s), %d %s given

#### HelpText
  Emitted when a special method was defined with an invalid number of parameters. If it has too few or too many, it might not work at all.


#### Tags
- /tool/Pylint
- /general/Class Rules

#### Settings
- Priority=Critical


## PYLINT_UT
### Default
#### OriginalId=unidiomatic-typecheck
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unidiomatic Typecheck
#### WarningText
  Using type() instead of isinstance() for a typecheck.

#### HelpText
  The idiomatic way to perform an explicit typecheck in Python is to use isinstance(x, Y) rather than type(x) == Y, type(x) is Y. Though there are unusual situations where these give different results.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Minor


## PYLINT_UTU
### Default
#### OriginalId=unbalanced-tuple-unpacking
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unbalanced Tuple Unpacking
#### WarningText
  Possible unbalanced tuple unpacking with sequence%s: left side has %d label(s), right side has %d value(s)

#### HelpText
  Used when there is an unbalanced tuple unpacking in assignment.


#### Tags
- /tool/Pylint
- /general/Variable Rules

#### Settings
- Priority=Major


## PYLINT_UV
### Default
#### OriginalId=undefined-variable
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Undefined Variable
#### WarningText
  Undefined variable %r

#### HelpText
  Used when an undefined variable is accessed.


#### Tags
- /tool/Pylint
- /general/Variable Rules

#### Settings
- Priority=Critical


## PYLINT_UWI
### Default
#### OriginalId=unused-wildcard-import
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unused Wildcard Import
#### WarningText
  Unused import %s from wildcard import

#### HelpText
  Used when an imported module or variable is not used from a `'from X import *'` style import.


#### Tags
- /tool/Pylint
- /general/Variable Rules

#### Settings
- Priority=Major


## PYLINT_UnB
### Default
#### OriginalId=unichr-builtin
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unichr Builtin
#### WarningText
  unichr built-in referenced

#### HelpText
  Used when the unichr built-in is referenced (Use chr in Python 3).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_UnI
### Default
#### OriginalId=unused-import
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unused Import
#### WarningText
  Unused %s

#### HelpText
  Used when an imported module or variable is not used.


#### Tags
- /tool/Pylint
- /general/Variable Rules

#### Settings
- Priority=Major


## PYLINT_UnV
### Default
#### OriginalId=unused-variable
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unused Variable
#### WarningText
  Unused variable %r

#### HelpText
  Used when a variable is defined but not used.


#### Tags
- /tool/Pylint
- /general/Variable Rules

#### Settings
- Priority=Major


## PYLINT_UngI
### Default
#### OriginalId=ungrouped-imports
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Ungrouped Imports
#### WarningText
  Imports from package %s are not grouped

#### HelpText
  Used when imports are not grouped by packages.


#### Tags
- /tool/Pylint
- /general/Import Rules

#### Settings
- Priority=Minor


## PYLINT_UsS
### Default
#### OriginalId=useless-suppression
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=Useless Suppression
#### WarningText
  Useless suppression of %s

#### HelpText
  Reported when a message is explicitly disabled for a line or a block of code, but never triggered.


#### Tags
- /tool/Pylint
- /general/Pylint Checker Rules

#### Settings
- Priority=Minor


## PYLINT_WEO
### Default
#### OriginalId=wrong-exception-operation
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Wrong Exception Operation
#### WarningText
  Invalid exception operation. %s

#### HelpText
  Used when an operation is done against an exception, but the operation is not valid for the exception in question. Usually emitted when having binary operations between exceptions in except handlers.


#### Tags
- /tool/Pylint
- /general/Exception Rules

#### Settings
- Priority=Major


## PYLINT_WI
### Default
#### OriginalId=wildcard-import
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Wildcard Import
#### WarningText
  Wildcard import %s

#### HelpText
  Used when `from module import *` is detected.


#### Tags
- /tool/Pylint
- /general/Import Rules

#### Settings
- Priority=Major


## PYLINT_WIO
### Default
#### OriginalId=wrong-import-order
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Wrong Import Order
#### WarningText
  %s should be placed before %s

#### HelpText
  Used when PEP8 import order is not respected (standard imports first, then third-party libraries, then local imports).


#### Tags
- /tool/Pylint
- /general/Import Rules

#### Settings
- Priority=Minor


## PYLINT_WIP
### Default
#### OriginalId=wrong-import-position
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Wrong Import Position
#### WarningText
  Import "%s" should be placed at the top of the module

#### HelpText
  Used when code and imports are mixed.


#### Tags
- /tool/Pylint
- /general/Import Rules

#### Settings
- Priority=Minor


## PYLINT_WSIC
### Default
#### OriginalId=wrong-spelling-in-comment
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Wrong Spelling In Comment
#### WarningText
  Wrong spelling of a word '%s' in a comment:

#### HelpText
  Used when a word in comment is not spelled correctly.


#### Tags
- /tool/Pylint
- /general/Spelling Rules

#### Settings
- Priority=Minor


## PYLINT_WSID
### Default
#### OriginalId=wrong-spelling-in-docstring
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Wrong Spelling In Docstring
#### WarningText
  Wrong spelling of a word '%s' in a docstring:

#### HelpText
  Used when a word in docstring is not spelled correctly.


#### Tags
- /tool/Pylint
- /general/Spelling Rules

#### Settings
- Priority=Minor


## PYLINT_XA
### Default
#### OriginalId=xreadlines-attribute
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Xreadlines Attribute
#### WarningText
  Accessing a removed xreadlines attribute

#### HelpText
  Used when accessing the xreadlines() function on a file stream, removed in Python 3.


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_XB
### Default
#### OriginalId=xrange-builtin
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Xrange Builtin
#### WarningText
  xrange built-in referenced

#### HelpText
  Used when the xrange built-in function is referenced (missing from Python 3).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major


## PYLINT_YIAF
### Default
#### OriginalId=yield-inside-async-function
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Yield Inside Async Function
#### WarningText
  Yield inside async function

#### HelpText
  Used when an `yield` or `yield from` statement is found inside an async function. This message can’t be emitted when using Python &lt; 3.5.


#### Tags
- /tool/Pylint
- /general/Async Rules

#### Settings
- Priority=Critical


## PYLINT_YOF
### Default
#### OriginalId=yield-outside-function
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Yield Outside Function
#### WarningText
  Yield outside function

#### HelpText
  Used when a “yield” statement is found outside a function or method.


#### Tags
- /tool/Pylint
- /general/Basic Rules

#### Settings
- Priority=Critical


## PYLINT_ZBNI
### Default
#### OriginalId=zip-builtin-not-iterating
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Zip Builtin Not Iterating
#### WarningText
  zip built-in referenced when not iterating

#### HelpText
  Used when the zip built-in is referenced in a non-iterating context (returns an iterator in Python 3).


#### Tags
- /tool/Pylint
- /general/Python3 Rules

#### Settings
- Priority=Major
