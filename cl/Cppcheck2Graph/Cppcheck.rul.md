# ToolDescription
## Default
### ID=Cppcheck
### Description
  Cppcheck is a static analysis tool for C/C++ code. Unlike C/C++ compilers and many other analysis tools it does not detect syntax errors in the code. Cppcheck primarily detects the types of bugs that the compilers normally do not detect. The goal is to detect only real errors in the code (i.e. have zero false positives).

  OpenStaticAnalyzer uses Cppcheck "as is", without any guaranties that the results of Cppcheck are correct. All statements of the Cppcheck license apply here as well. All texts describing the rulesets and the individual rules are copied from the cppcheck with some minor grammatical fixes.

# Includes
- Cppcheck.rul_metadata.md

# Metrics
## CPPCHECK_AATI
### Default
#### OriginalId=AssignmentAddressToInteger
#### Enabled=true
#### Warning=true
#### DisplayName=Assignment Address To Integer
#### HelpText
  Assigning a pointer to an integer (int/long/etc) is not portable across different platforms and compilers. For example in 32-bit Windows and linux they are same width, but in 64-bit Windows and linux they are of different width. In worst case you end up assigning 64-bit address to 32-bit integer. The safe way is to store addresses only in pointer types (or typedefs like uintptr_t).

#### Tags
- /general/Portability Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_ABTF
### Default
#### OriginalId=assignBoolToFloat
#### Enabled=true
#### Warning=true
#### DisplayName=Assign Bool To Float
#### HelpText
  Boolean value assigned to floating point variable.

#### Tags
- /general/Performance Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_ABTP
### Default
#### OriginalId=assignBoolToPointer
#### Enabled=true
#### Warning=true
#### DisplayName=Assign Bool To Pointer
#### HelpText
  Boolean value assigned to pointer.

#### Tags
- /general/Simple Type Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_AF
### Default
#### OriginalId=accessForwarded
#### Enabled=true
#### Warning=true
#### DisplayName=Access Forwarded
#### HelpText
  Access of forwarded variable 'v'.

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_AIA
### Default
#### OriginalId=assignmentInAssert
#### Enabled=true
#### Warning=true
#### DisplayName=Assignment In Assert
#### HelpText
  Variable 'var' is modified inside assert statement. Assert statements are removed from release builds so the code inside assert statement is not executed. If the code is needed also in release builds, this is a bug.

#### Tags
- /general/Side Effect Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_AIC
### Default
#### OriginalId=assignmentInCondition
#### Enabled=true
#### Warning=true
#### DisplayName=Assignment In Condition
#### HelpText
  Suspicious assignment in condition. Condition 'x=y' is always true.

#### Tags
- /general/Suspicious Construct Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_AID
### Default
#### OriginalId=autovarInvalidDeallocation
#### Enabled=true
#### Warning=true
#### DisplayName=Autovar Invalid Deallocation
#### HelpText
  The deallocation of an auto-variable results in undefined behaviour. You should only free memory that has been allocated dynamically.

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_AIE
### Default
#### OriginalId=assignIfError
#### Enabled=true
#### Warning=true
#### DisplayName=Assign If Error
#### HelpText
  Mismatching assignment and comparison, comparison '' is always false.

#### Tags
- /general/Conditional Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_AIOOB
### Default
#### OriginalId=arrayIndexOutOfBounds
#### Enabled=true
#### Warning=true
#### DisplayName=Array Index Out Of Bounds
#### HelpText
  Array 'arr[16]' accessed at index 16, which is out of bounds.

#### Tags
- /general/Buffer Overrun Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_AIOOBC
### Default
#### OriginalId=arrayIndexOutOfBoundsCond
#### Enabled=true
#### Warning=true
#### DisplayName=Array Index Out Of Bounds Cond
#### HelpText
  Array 'arr[16]' accessed at index 16, which is out of bounds.

#### Tags
- /general/Buffer Overrun Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_AITA
### Default
#### OriginalId=AssignmentIntegerToAddress
#### Enabled=true
#### Warning=true
#### DisplayName=Assignment Integer To Address
#### HelpText
  Assigning an integer (int/long/etc) to a pointer is not portable across different platforms and compilers. For example in 32-bit Windows and linux they are same width, but in 64-bit Windows and linux they are of different width. In worst case you end up assigning 64-bit integer to 32-bit pointer. The safe way is to store addresses only in pointer types (or typedefs like uintptr_t).

#### Tags
- /general/Portability Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_AITC
### Default
#### OriginalId=arrayIndexThenCheck
#### Enabled=true
#### Warning=true
#### DisplayName=Array Index Then Check
#### HelpText
  Defensive programming: The variable 'i' is used as an array index before it is checked that is within limits. This can mean that the array might be accessed out of bounds. Reorder conditions such as '(a[i] && i < 10)' to '(i < 10 && a[i])'. That way the array will not be accessed if the index is out of limits.

#### Tags
- /general/Buffer Overrun Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_AM
### Default
#### OriginalId=accessMoved
#### Enabled=true
#### Warning=true
#### DisplayName=Access Moved
#### HelpText
  Access of moved variable 'v'.

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_AOOVP
### Default
#### OriginalId=arithOperationsOnVoidPointer
#### Enabled=true
#### Warning=true
#### DisplayName=Arithmetic Operations On Void Pointer
#### HelpText
  'varname' is of type 'vartype'. When using void pointers in calculations, the behaviour is undefined. Arithmetic operations on 'void *' is a GNU C extension, which defines the 'sizeof(void)' to be 1.

#### Tags
- /general/Sizeof Operator Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_AOSBLU
### Default
#### OriginalId=operatorEqShouldBeLeftUnimplemented
#### Enabled=true
#### Warning=true
#### DisplayName=Assignment Operator Should Be Left Unimplemented
#### HelpText
  'operator=' should either return reference to 'this' instance or be declared private and left unimplemented.

#### Tags
- /general/Object Orientedness Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_AV
### Default
#### OriginalId=autoVariables
#### Enabled=true
#### Warning=true
#### DisplayName=Auto Variables
#### HelpText
  Dangerous assignment - the function parameter is assigned the address of a local auto-variable. Local auto-variables are reserved from the stack which is freed when the function ends. So the pointer to a local variable is invalid after the function ends.

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_AWSE
### Default
#### OriginalId=assertWithSideEffect
#### Enabled=true
#### Warning=true
#### DisplayName=Assert With Side Effect
#### HelpText
  Non-pure function: 'function' is called inside assert statement. Assert statements are removed from release builds so the code inside assert statement is not executed. If the code is needed also in release builds, this is a bug.

#### Tags
- /general/Side Effect Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_BAOOB
### Default
#### OriginalId=bufferAccessOutOfBounds
#### Enabled=true
#### Warning=true
#### DisplayName=Buffer Access Out Of Bounds
#### HelpText
  Buffer is accessed out of bounds: buf

#### Tags
- /general/Buffer Overrun Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_BBC
### Default
#### OriginalId=badBitmaskCheck
#### Enabled=true
#### Warning=true
#### DisplayName=Bad Bitmask Check
#### HelpText
  Result of operator '|' is always true if one operand is non-zero. Did you intend to use '&'?

#### Tags
- /general/Conditional Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_BFE
### Default
#### OriginalId=boostForeachError
#### Enabled=true
#### Warning=true
#### DisplayName=Boost Foreach Error
#### HelpText
  BOOST_FOREACH caches the end() iterator. It's undefined behavior if you modify the container inside.

#### Tags
- /general/Boost Library Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_BOB
### Default
#### OriginalId=bitwiseOnBoolean
#### Enabled=true
#### Warning=true
#### DisplayName=Bitwise On Boolean
#### HelpText
  Boolean expression 'expression' is used in bitwise operation. Did you mean '&&'?

#### Tags
- /general/Simple Type Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_CAF
### Default
#### OriginalId=knownConditionTrueFalse
#### Enabled=true
#### Warning=true
#### DisplayName=Condition is Always False
#### HelpText
  Condition 'x' is always false

#### Tags
- /general/Conditional Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_CAI
### Default
#### OriginalId=unknownSignCharArrayIndex
#### Enabled=true
#### Warning=true
#### DisplayName=Character Array Index
#### HelpText
  'char' type used as array index. Values greater than 127 will be treated depending on whether 'char' is signed or unsigned on target platform.

#### Tags
- /general/Simple Type Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_CATIAR
### Default
#### OriginalId=CastAddressToIntegerAtReturn
#### Enabled=true
#### Warning=true
#### DisplayName=Cast Address To Integer At Return
#### HelpText
  Returning an address value in a function with integer (int/long/etc) return type is not portable across different platforms and compilers. For example in 32-bit Windows and Linux they are same width, but in 64-bit Windows and Linux they are of different width. In worst case you end up casting 64-bit address down to 32-bit integer. The safe way is to always return an integer.

#### Tags
- /general/Portability Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_CBEWI
### Default
#### OriginalId=compareBoolExpressionWithInt
#### Enabled=true
#### Warning=true
#### DisplayName=Compare Bool Expression With Int
#### HelpText
  Comparison of a boolean expression with an integer other than 0 or 1.

#### Tags
- /general/Simple Type Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_CBO
### Default
#### OriginalId=charBitOp
#### Enabled=true
#### Warning=true
#### DisplayName=Char Bit Op
#### HelpText
  When using 'char' variables in bit operations, sign extension can generate unexpected results. For example:
  ``` cpp
    char c = 0x80;
    int i = 0 | c;
    if (i & 0x8000)
        printf("not expected");
  ```
  The "not expected" will be printed on the screen.

#### Tags
- /general/Simple Type Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_CCAEO
### Default
#### OriginalId=copyCtorAndEqOperator
#### Enabled=true
#### Warning=true
#### DisplayName=Copy Constructor And Eq Operator
#### HelpText
  The class 'class' has 'operator=' but lack of 'copy constructor'.

#### Tags
- /general/Object Orientedness Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_CCALC
### Default
#### OriginalId=clarifyCalculation
#### Enabled=true
#### Warning=true
#### DisplayName=Clarify Calculation
#### HelpText
  Suspicious calculation. Please use parentheses to clarify the code. The code ''a+b?c:d'' should be written as either ''(a+b)?c:d'' or ''a+(b?c:d)''.

#### Tags
- /general/Readability and Consistency Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_CCITCAB
### Default
#### OriginalId=checkCastIntToCharAndBack
#### Enabled=true
#### Warning=true
#### DisplayName=Check Cast Int To Char And Back
#### HelpText
  When saving func_name() return value in char variable there is loss of precision.  When func_name() returns EOF this value is truncated. Comparing the char variable with EOF can have unexpected results. For instance a loop "while (EOF != (c = func_name());" loops forever on some compilers/platforms and on other compilers/platforms it will stop when the file contains a matching character.

#### Tags
- /general/Simple Type Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_CCM
### Default
#### OriginalId=coutCerrMisusage
#### Enabled=true
#### Warning=true
#### DisplayName=Cout Cerr Misusage
#### HelpText
  Invalid usage of output stream: '<< std::cout'.

#### Tags
- /general/Input Output Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_CCOND
### Default
#### OriginalId=clarifyCondition
#### Enabled=true
#### Warning=true
#### DisplayName=Clarify Condition
#### HelpText
  Suspicious condition (assignment + comparison); Clarify expression with parentheses.

#### Tags
- /general/Conditional Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_CCPC
### Default
#### OriginalId=copyCtorPointerCopying
#### Enabled=true
#### Warning=true
#### DisplayName=Copy Ctor Pointer Copying
#### HelpText
  Value of pointer 'var', which points to allocated memory, is copied in copy constructor instead of allocating new memory.

#### Tags
- /general/Object Orientedness Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_CE
### Default
#### OriginalId=comparisonError
#### Enabled=true
#### Warning=true
#### DisplayName=Comparison Error
#### HelpText
  The expression '(X & 0x6) == 0x1' is always false. Check carefully constants and operators used, these errors might be hard to spot sometimes. In case of complex expression it might help to split it to separate expressions.

#### Tags
- /general/Conditional Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_CEBV
### Default
#### OriginalId=catchExceptionByValue
#### Enabled=true
#### Warning=true
#### DisplayName=Catch Exception By Value
#### HelpText
  The exception is caught by value. It could be caught as a (const) reference which is usually recommended in C++.

#### Tags
- /general/Exception Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_CFIATOF
### Default
#### OriginalId=comparisonFunctionIsAlwaysTrueOrFalse
#### Enabled=true
#### Warning=true
#### DisplayName=Comparison Function Is Always True Or False
#### HelpText
  The function isless is designed to compare two variables. Calling this function with one variable (varName) for both parameters leads to a statement which is always false.

#### Tags
- /general/Conditional Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_CITAAR
### Default
#### OriginalId=CastIntegerToAddressAtReturn
#### Enabled=true
#### Warning=true
#### DisplayName=Cast Integer To Address At Return
#### HelpText
  Returning an integer (int/long/etc) in a function with pointer return type is not portable across different platforms and compilers. For example in 32-bit Windows and Linux they are same width, but in 64-bit Windows and Linux they are of different width. In worst case you end up casting 64-bit integer down to 32-bit pointer. The safe way is to always return a pointer.

#### Tags
- /general/Portability Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_CLWCPC
### Default
#### OriginalId=charLiteralWithCharPtrCompare
#### Enabled=true
#### Warning=true
#### DisplayName=Char Literal With Char Ptr Compare
#### HelpText
  Char literal compared with pointer 'foo'. Did you intend to dereference it?

#### Tags
- /general/Simple Type Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_COBWBE
### Default
#### OriginalId=comparisonOfBoolWithBoolError
#### Enabled=true
#### Warning=true
#### DisplayName=Comparison Of Bool With Bool Error
#### HelpText
  The variable 'var_name' is of type 'bool' and comparing 'bool' value using relational (<, >, <= or >=) operator could cause unexpected results.

#### Tags
- /general/Simple Type Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_COBWIC
### Default
#### OriginalId=comparisonOfBoolWithInvalidComparator
#### Enabled=true
#### Warning=true
#### DisplayName=Comparison Of Bool With Invalid Comparator
#### HelpText
  The result of the expression 'expression' is of type 'bool'. Comparing 'bool' value using relational (<, >, <= or >=) operator could cause unexpected results.

#### Tags
- /general/Conditional Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_COFRBE
### Default
#### OriginalId=comparisonOfFuncReturningBoolError
#### Enabled=true
#### Warning=true
#### DisplayName=Comparison Of Func Returning Bool Error
#### HelpText
  The return type of function 'func_name' is 'bool' and result is of type 'bool'. Comparing 'bool' value using relational (<, >, <= or >=) operator could cause unexpected results.

#### Tags
- /general/Simple Type Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_COOB
### Default
#### OriginalId=containerOutOfBounds
#### Enabled=true
#### Warning=true
#### DisplayName=Container Out Of Bounds
#### HelpText
  Out of bounds access in expression 'container[x]'

#### Tags
- /general/STL Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_COTFRBE
### Default
#### OriginalId=comparisonOfTwoFuncsReturningBoolError
#### Enabled=true
#### Warning=true
#### DisplayName=Comparison Of Two Funcs Returning Bool Error
#### HelpText
  The return type of function 'func_name1' and function 'func_name2' is 'bool' and result is of type 'bool'. Comparing 'bool' value using relational (<, >, <= or >=) operator could cause unexpected results.

#### Tags
- /general/Simple Type Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_CP
### Default
#### OriginalId=comparePointers
#### Enabled=true
#### Warning=true
#### DisplayName=Compare Pointers
#### HelpText
  Comparing pointers that point to different objects

#### Tags
- /general/Suspicious Construct Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_CS
### Default
#### OriginalId=constStatement
#### Enabled=true
#### Warning=true
#### DisplayName=Const Statement
#### HelpText
  Redundant code: Found a statement that begins with type constant.

#### Tags
- /general/Suspicious Construct Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_CSC
### Default
#### OriginalId=cstyleCast
#### Enabled=true
#### Warning=true
#### DisplayName=Cstyle Cast
#### HelpText
  C-style pointer casting detected. C++ offers four different kinds of casts as replacements: static_cast, const_cast, dynamic_cast and reinterpret_cast. A C-style cast could evaluate to any of those automatically, thus it is considered safer if the programmer explicitly states which kind of cast is expected. See also: https://www.securecoding.cert.org/confluence/display/cplusplus/EXP05-CPP.+Do+not+use+C-style+casts.

#### Tags
- /general/Readability and Consistency Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_CSR
### Default
#### OriginalId=commaSeparatedReturn
#### Enabled=true
#### Warning=true
#### DisplayName=Comma Separated Return
#### HelpText
  Comma is used in return statement. When comma is used in a return statement it can easily be misread as a semicolon. For example in the code below the value of 'b' is returned if the condition is true, but it is easy to think that 'a+1' is returned:
  ``` cpp
    if (x)
        return a + 1,
    b++;
  ```
  However it can be useful to use comma in macros. Cppcheck does not warn when such a macro is then used in a return statement, it is less likely such code is misunderstood.

#### Tags
- /general/Readability and Consistency Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_CSTAT
### Default
#### OriginalId=clarifyStatement
#### Enabled=true
#### Warning=true
#### DisplayName=Clarify Statement
#### HelpText
  A statement like '*A++;' might not do what you intended. Postfix 'operator++' is executed before 'operator*'. Thus, the dereference is meaningless. Did you intend to write '(*A)++;'?

#### Tags
- /general/Readability and Consistency Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_CV
### Default
#### OriginalId=constVariable
#### Enabled=true
#### Warning=true
#### DisplayName=Const Variable
#### HelpText
  Variable 'x' can be declared with const

#### Tags
- /general/Readability and Consistency Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_DAE
### Default
#### OriginalId=duplicateAssignExpression
#### Enabled=true
#### Warning=true
#### DisplayName=Duplicate Assign Expression
#### HelpText
  Finding variables 'x' and 'x' that are assigned the same expression is suspicious and might indicate a cut and paste or logic error. Please examine this code carefully to determine if it is correct.

#### Tags
- /general/Suspicious Construct Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_DAR
### Default
#### OriginalId=deallocret
#### Enabled=true
#### Warning=true
#### DisplayName=Deallocret
#### HelpText
  Returning/dereferencing 'p' after it is deallocated / released

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_DBRANCH
### Default
#### OriginalId=duplicateBranch
#### Enabled=true
#### Warning=true
#### DisplayName=Duplicate Branch
#### HelpText
  Finding the same code in an 'if' and related 'else' branch is suspicious and might indicate a cut and paste or logic error. Please examine this code carefully to determine if it is correct.

#### Tags
- /general/Suspicious Construct Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_DBREAK
### Default
#### OriginalId=duplicateBreak
#### Enabled=true
#### Warning=true
#### DisplayName=Duplicate Break
#### HelpText
  Consecutive return, break, continue, goto or throw statements are unnecessary. The second statement can never be executed, and so should be removed.

#### Tags
- /general/Unreachable Code Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_DCOND
### Default
#### OriginalId=duplicateCondition
#### Enabled=true
#### Warning=true
#### DisplayName=Duplicate Condition
#### HelpText
  The if condition is the same as the previous if condition

#### Tags
- /general/Conditional Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_DCONDA
### Default
#### OriginalId=duplicateConditionalAssign
#### Enabled=true
#### Warning=true
#### DisplayName=Duplicate Condition and Assignement
#### HelpText
  Duplicate expression for the condition and assignment.

#### Tags
- /general/Conditional Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_DD
### Default
#### OriginalId=deallocDealloc
#### Enabled=true
#### Warning=true
#### DisplayName=Dealloc Dealloc
#### HelpText
  Deallocating a deallocated pointer: varname

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_DET
### Default
#### OriginalId=duplicateExpressionTernary
#### Enabled=true
#### Warning=true
#### DisplayName=Duplicate Expression Ternary
#### HelpText
  Finding the same expression in both branches of ternary operator is suspicious as the same code is executed regardless of the condition.

#### Tags
- /general/Suspicious Construct Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_DEXPR
### Default
#### OriginalId=duplicateExpression
#### Enabled=true
#### Warning=true
#### DisplayName=Duplicate Expression
#### HelpText
  Finding the same expression on both sides of an operator is suspicious and might indicate a cut and paste or logic error. Please examine this code carefully to determine if it is correct.

#### Tags
- /general/Suspicious Construct Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_DF
### Default
#### OriginalId=doubleFree
#### Enabled=true
#### Warning=true
#### DisplayName=Double Free
#### HelpText
  Memory pointed to by 'varname' is freed twice.

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_DII
### Default
#### OriginalId=derefInvalidIterator
#### Enabled=true
#### Warning=true
#### DisplayName=Deref Invalid Iterator
#### HelpText
  Possible dereference of an invalid iterator: i. Make sure to check that the iterator is valid before dereferencing it - not after.

#### Tags
- /general/STL Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_DIM
### Default
#### OriginalId=duplInheritedMember
#### Enabled=true
#### Warning=true
#### DisplayName=Dupl Inherited Member
#### HelpText
  The class 'class' defines member variable with name 'variable' also defined in its parent class 'class'.

#### Tags
- /general/Object Orientedness Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_DL
### Default
#### OriginalId=danglingLifetime
#### Enabled=true
#### Warning=true
#### DisplayName=Dangling Lifetime
#### HelpText
  Non-local variable 'x' will use object.

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_DR
### Default
#### OriginalId=danglingReference
#### Enabled=true
#### Warning=true
#### DisplayName=Dangling Reference
#### HelpText
  Non-local reference variable 'x' to local variable 'y'

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_DSO
### Default
#### OriginalId=divideSizeof
#### Enabled=true
#### Warning=true
#### DisplayName=Divide Sizeof
#### HelpText
  Division of result of sizeof() on pointer type. sizeof() returns the size of the pointer, not the size of the memory area it points to.

#### Tags
- /general/Sizeof Operator Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_DTL
### Default
#### OriginalId=danglingTemporaryLifetime
#### Enabled=true
#### Warning=true
#### DisplayName=Dangling Temporary Lifetime
#### HelpText
  Using object to temporary.

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_DTR
### Default
#### OriginalId=danglingTempReference
#### Enabled=true
#### Warning=true
#### DisplayName=Dangling Temporary Reference
#### HelpText
  Using reference to dangling temporary.

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_DU
### Default
#### OriginalId=deallocuse
#### Enabled=true
#### Warning=true
#### DisplayName=Deallocuse
#### HelpText
  Dereferencing 'varname' after it is deallocated / released

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_DUOS
### Default
#### OriginalId=uninitstring
#### Enabled=true
#### Warning=true
#### DisplayName=Dangerous Use Of Strncpy
#### HelpText
  Dangerous usage of 'varname' (strncpy doesn't always null-terminate it).

#### Tags
- /general/Initialization Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_DVT
### Default
#### OriginalId=duplicateValueTernary
#### Enabled=true
#### Warning=true
#### DisplayName=Duplicate Value Ternary
#### HelpText
  Finding the same value in both branches of ternary operator is suspicious as the same code is executed regardless of the condition.

#### Tags
- /general/Suspicious Construct Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_ED
### Default
#### OriginalId=eraseDereference
#### Enabled=true
#### Warning=true
#### DisplayName=Erase Dereference
#### HelpText
  The iterator 'iter' is invalid before being assigned. Dereferencing or comparing it with another iterator is invalid operation.

#### Tags
- /general/STL Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_EDT
### Default
#### OriginalId=exceptDeallocThrow
#### Enabled=true
#### Warning=true
#### DisplayName=Except Dealloc Throw
#### HelpText
  Exception thrown in invalid state, 'p' points at deallocated memory.

#### Tags
- /general/Exception Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_ERC
### Default
#### OriginalId=exceptRethrowCopy
#### Enabled=true
#### Warning=true
#### DisplayName=Except Rethrow Copy
#### HelpText
  Rethrowing an exception with 'throw varname;' creates an unnecessary copy of 'varname'. To rethrow the caught exception without unnecessary copying or slicing, use a bare 'throw;'.

#### Tags
- /general/Exception Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_ETID
### Default
#### OriginalId=exceptThrowInDestructor
#### Enabled=true
#### Warning=true
#### DisplayName=Except Throw In Destructor
#### HelpText
  The class Class is not safe because its destructor throws an exception. If Class is used and an exception is thrown that is caught in an outer scope the program will terminate.

#### Tags
- /general/Exception Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_FAND
### Default
#### OriginalId=funcArgNamesDifferent
#### Enabled=true
#### Warning=true
#### DisplayName=Function Argument Names Different
#### HelpText
  Function 'function' argument 2 names different: declaration 'A' definition 'B'.

#### Tags
- /general/Readability and Consistency Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_FAOD
### Default
#### OriginalId=funcArgOrderDifferent
#### Enabled=true
#### Warning=true
#### DisplayName=Function Argument Order Different
#### HelpText
  Function 'function' argument order different: declaration '' definition ''

#### Tags
- /general/Readability and Consistency Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_FC
### Default
#### OriginalId=functionConst
#### Enabled=true
#### Warning=true
#### DisplayName=Function Const
#### HelpText
  The member function 'class::function' can be made a const function. Making this function 'const' should not cause compiler errors. Even though the function can be made const function technically it may not make sense conceptually. Think about your design and the task of the function first - is it a function that must not change object internal state?

#### Tags
- /general/Object Orientedness Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_FCO
### Default
#### OriginalId=floatConversionOverflow
#### Enabled=true
#### Warning=true
#### DisplayName=Float Conversion Overflow
#### HelpText
  Undefined behaviour: float (1e+100) to integer conversion overflow.

#### Tags
- /general/Simple Type Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_FOIS
### Default
#### OriginalId=fflushOnInputStream
#### Enabled=true
#### Warning=true
#### DisplayName=Fflush On Input Stream
#### HelpText
  fflush() called on input stream 'stdin' may result in undefined behaviour on non-linux systems.

#### Tags
- /general/Input Output Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_FS
### Default
#### OriginalId=functionStatic
#### Enabled=true
#### Warning=true
#### DisplayName=Function Static
#### HelpText
  The member function 'class::function' can be made a static function. Making a function static can bring a performance benefit since no 'this' instance is passed to the function. This change should not cause compiler errors but it does not necessarily make sense conceptually. Think about your design and the task of the function first - is it a function that must not access members of class instances? And maybe it is more appropriate to move this function to a unnamed namespace.

#### Tags
- /general/Object Orientedness Rules
- /tool/Cppcheck

#### Settings
- Priority=Major


## CPPCHECK_GLG
### Default
#### OriginalId=globalLockGuard
#### Enabled=true
#### Warning=true
#### DisplayName=Global Lock Guard
#### HelpText
  Lock guard is defined globally. Lock guards are intended to be local. A global lock guard could lead to a deadlock since it won't unlock until the end of the program.

#### Tags
- /general/Multithreading Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_IAF
### Default
#### OriginalId=incompleteArrayFill
#### Enabled=true
#### Warning=true
#### DisplayName=Incomplete Array Fill
#### HelpText
  The array 'buffer' is filled incompletely. The function 'memset()' needs the size given in bytes, but an element of the given array is larger than one byte. Did you forget to multiply the size with 'sizeof(*buffer)'?

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_IB
### Default
#### OriginalId=incrementboolean
#### Enabled=true
#### Warning=true
#### DisplayName=Increment Boolean
#### HelpText
  The operand of a postfix increment operator may be of type bool but it is deprecated by C++ Standard (Annex D-1) and the operand is always set to true. You should assign it the value 'true' instead.

#### Tags
- /general/Simple Type Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_IC
### Default
#### OriginalId=invalidContainer
#### Enabled=true
#### Warning=true
#### DisplayName=Invalid Container
#### HelpText
  Using object that may be invalid.

#### Tags
- /general/STL Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_ICAEE
### Default
#### OriginalId=identicalConditionAfterEarlyExit
#### Enabled=true
#### Warning=true
#### DisplayName=Identical Condition After Early Exit
#### HelpText
  Identical condition 'x', second condition is always false

#### Tags
- /general/Conditional Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_ICBE
### Default
#### OriginalId=incorrectCharBooleanError
#### Enabled=true
#### Warning=true
#### DisplayName=Incorrect Char Boolean Error
#### HelpText
  Conversion of char literal 'x' to bool always evaluates to true.

#### Tags
- /general/Simple Type Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_ICL
### Default
#### OriginalId=invalidContainerLoop
#### Enabled=true
#### Warning=true
#### DisplayName=Invalid Container Loop
#### HelpText
  Calling 'erase' while iterating the container is invalid.

#### Tags
- /general/STL Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_IF
### Default
#### OriginalId=invalidFree
#### Enabled=true
#### Warning=true
#### DisplayName=Invalid Free
#### HelpText
  Mismatching address is freed. The address you get from malloc() must be freed without offset.

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_IFA
### Default
#### OriginalId=invalidFunctionArg
#### Enabled=true
#### Warning=true
#### DisplayName=Invalid Function Arguments
#### HelpText
  Invalid func_name() argument nr 1. The value is 0 or 1 (boolean) but the valid values are '1:4'.

#### Tags
- /general/API Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_IFAB
### Default
#### OriginalId=invalidFunctionArgBool
#### Enabled=true
#### Warning=true
#### DisplayName=Invalid Function Argument Boolean
#### HelpText
  Invalid func_name() argument nr 1. A non-boolean value is required.

#### Tags
- /general/API Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_IFAS
### Default
#### OriginalId=invalidFunctionArgStr
#### Enabled=true
#### Warning=true
#### DisplayName=Invalid Function Argument String
#### HelpText
  Invalid func_name() argument nr 1. A nul-terminated string is required.

#### Tags
- /general/API Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_IIC
### Default
#### OriginalId=identicalInnerCondition
#### Enabled=true
#### Warning=true
#### DisplayName=Identical Inner Condition
#### HelpText
  Identical inner 'if' condition is always true (outer condition is 'x' and inner condition is 'x').

#### Tags
- /general/Conditional Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_IIT
### Default
#### OriginalId=invalidIterator1
#### Enabled=true
#### Warning=true
#### DisplayName=Invalid Iterator1
#### HelpText
  Invalid iterator: iterator

#### Tags
- /general/STL Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_IL
### Default
#### OriginalId=initializerList
#### Enabled=true
#### Warning=true
#### DisplayName=Initializer List
#### HelpText
  Member variable 'class::variable' is in the wrong place in the initializer list. Members are initialized in the order they are declared, not in the order they are in the initializer list.  Keeping the initializer list in the same order that the members were declared prevents order dependent initialization errors.

#### Tags
- /general/Object Orientedness Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_ILME
### Default
#### OriginalId=invalidLengthModifierError
#### Enabled=true
#### Warning=true
#### DisplayName=Invalid Length Modifier Error
#### HelpText
  'I' in format string (no. 1) is a length modifier and cannot be used without a conversion specifier.

#### Tags
- /general/API Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_ILO
### Default
#### OriginalId=incorrectLogicOperator
#### Enabled=true
#### Warning=true
#### DisplayName=Incorrect Logic Operator
#### HelpText
  Logical disjunction always evaluates to true: foo > 3 && foo < 4. Are these conditions necessary? Did you intend to use && instead? Are the numbers correct? Are you comparing the correct variables?

#### Tags
- /general/Conditional Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_ILT
### Default
#### OriginalId=invalidLifetime
#### Enabled=true
#### Warning=true
#### DisplayName=Invalid Lifetime
#### HelpText
  Using object that is out of scope.

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_IO
### Default
#### OriginalId=integerOverflow
#### Enabled=true
#### Warning=true
#### DisplayName=Integer Overflow
#### HelpText
  Signed integer overflow for expression ''.

#### Tags
- /general/Simple Type Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_IOWP
### Default
#### OriginalId=IOWithoutPositioning
#### Enabled=true
#### Warning=true
#### DisplayName=IO Without Positioning
#### HelpText
  Read and write operations without a call to a positioning function (fseek, fsetpos or rewind) or fflush in between result in undefined behaviour.

#### Tags
- /general/Input Output Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_IPATF
### Default
#### OriginalId=invalidPrintfArgType_float
#### Enabled=true
#### Warning=true
#### DisplayName=Invalid Printf Arg Type_float
#### HelpText
  %f in format string (no. 1) requires 'double' but the argument type is Unknown.

#### Tags
- /general/Input Output Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_IPATN
### Default
#### OriginalId=invalidPrintfArgType_n
#### Enabled=true
#### Warning=true
#### DisplayName=Invalid Printf Arg Type_n
#### HelpText
  %n in format string (no. 1) requires 'int *' but the argument type is Unknown.

#### Tags
- /general/Input Output Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_IPATP
### Default
#### OriginalId=invalidPrintfArgType_p
#### Enabled=true
#### Warning=true
#### DisplayName=Invalid Printf Arg Type_p
#### HelpText
  %p in format string (no. 1) requires an address but the argument type is Unknown.

#### Tags
- /general/Input Output Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_IPATS
### Default
#### OriginalId=invalidPrintfArgType_s
#### Enabled=true
#### Warning=true
#### DisplayName=Invalid Printf Arg Type_s
#### HelpText
  %s in format string (no. 1) requires 'char *' but the argument type is Unknown.

#### Tags
- /general/Input Output Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_IPATSI
### Default
#### OriginalId=invalidPrintfArgType_sint
#### Enabled=true
#### Warning=true
#### DisplayName=Invalid Printf Arg Type_sint
#### HelpText
  %i in format string (no. 1) requires 'int' but the argument type is Unknown.

#### Tags
- /general/Input Output Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_IPATUI
### Default
#### OriginalId=invalidPrintfArgType_uint
#### Enabled=true
#### Warning=true
#### DisplayName=Invalid Printf Arg Type_uint
#### HelpText
  %u in format string (no. 1) requires 'unsigned int' but the argument type is Unknown.

#### Tags
- /general/Input Output Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_IPC
### Default
#### OriginalId=invalidPointerCast
#### Enabled=true
#### Warning=true
#### DisplayName=Invalid Pointer Cast
#### HelpText
  Casting between float * and double * which have an incompatible binary data representation.

#### Tags
- /general/Simple Type Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_IRV
### Default
#### OriginalId=ignoredReturnValue
#### Enabled=true
#### Warning=true
#### DisplayName=Ignored Return Value
#### HelpText
  Return value of function malloc() is not used.

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_IS
### Default
#### OriginalId=invalidscanf
#### Enabled=true
#### Warning=true
#### DisplayName=Invalid Scanf
#### HelpText
  scanf() without field width limits can crash with huge input data. Add a field width specifier to fix this problem.

  Sample program that can crash:
  ``` cpp
  #include <stdio.h>
  int main()
  {
      char c[5];
      scanf("%s", c);
      return 0;
  }
  ```

  Typing in 5 or more characters may make the program crash. The correct usage here is 'scanf("%4s", c);', as the maximum field width does not include the terminating null byte.
  Source: http://linux.die.net/man/3/scanf
  Source: http://www.opensource.apple.com/source/xnu/xnu-1456.1.26/libkern/stdio/scanf.c

#### Tags
- /general/Input Output Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_ISATF
### Default
#### OriginalId=invalidScanfArgType_float
#### Enabled=true
#### Warning=true
#### DisplayName=Invalid Scanf Arg Type_float
#### HelpText
  %f in format string (no. 1) requires 'float *' but the argument type is Unknown.

#### Tags
- /general/Input Output Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_ISATI
### Default
#### OriginalId=invalidScanfArgType_int
#### Enabled=true
#### Warning=true
#### DisplayName=Invalid Scanf Arg Type_int
#### HelpText
  %d in format string (no. 1) requires 'int *' but the argument type is Unknown.

#### Tags
- /general/Input Output Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_ISATS
### Default
#### OriginalId=invalidScanfArgType_s
#### Enabled=true
#### Warning=true
#### DisplayName=Invalid Scanf Arg Type_s
#### HelpText
  %s in format string (no. 1) requires a 'char *' but the argument type is Unknown.

#### Tags
- /general/Input Output Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_ISBE
### Default
#### OriginalId=incorrectStringBooleanError
#### Enabled=true
#### Warning=true
#### DisplayName=Incorrect String Boolean Error
#### HelpText
  Conversion of string literal "Hello World" to bool always evaluates to true.

#### Tags
- /general/Simple Type Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_ISC
### Default
#### OriginalId=incorrectStringCompare
#### Enabled=true
#### Warning=true
#### DisplayName=Incorrect String Compare
#### HelpText
  String literal "Hello World" doesn't match length argument for substr().

#### Tags
- /general/Simple Type Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_ISFW
### Default
#### OriginalId=invalidScanfFormatWidth
#### Enabled=true
#### Warning=true
#### DisplayName=Invalid Scanf Format Width
#### HelpText
  Width 5 given in format string (no. 10) is larger than destination buffer '[0]', use %-1s to prevent overflowing it.

#### Tags
- /general/Input Output Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_ISFWS
### Default
#### OriginalId=invalidScanfFormatWidth_smaller
#### Enabled=true
#### Warning=true
#### DisplayName=Invalid Smaller Scanf Format Width
#### HelpText
  Width -1 given in format string (no. 99) is smaller than destination buffer '[0]'.

#### Tags
- /general/Input Output Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_ITFO
### Default
#### OriginalId=invalidTestForOverflow
#### Enabled=true
#### Warning=true
#### DisplayName=Invalid Test For Overflow
#### HelpText
  Invalid test for overflow 'x + c < x'; signed integer overflow is undefined behavior. Some mainstream compilers remove such overflow tests when optimising the code and assume it's always false.

#### Tags
- /general/Conditional Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_KA
### Default
#### OriginalId=knownArgument
#### Enabled=true
#### Warning=true
#### DisplayName=Known Argument
#### HelpText
  Argument 'x-x' to function 'func' is always 0. It does not matter what value 'x' has.

#### Tags
- /general/Suspicious Construct Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_KAHVE
### Default
#### OriginalId=knownArgumentHiddenVariableExpression
#### Enabled=true
#### Warning=true
#### DisplayName=Known Argument Hidden Variable Expression
#### HelpText
  Argument 'x*0' to function 'func' is always 0. Constant literal calculation disable/hide variable expression 'x'.

#### Tags
- /general/Suspicious Construct Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_KEC
### Default
#### OriginalId=knownEmptyContainer
#### Enabled=true
#### Warning=true
#### DisplayName=Known Empty Container
#### HelpText
  Iterating over container 'var' that is always empty.

#### Tags
- /general/Suspicious Construct Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_LM
### Default
#### OriginalId=localMutex
#### Enabled=true
#### Warning=true
#### DisplayName=Local Mutex
#### HelpText
  The lock is ineffective because the mutex is locked at the same scope as the mutex itself.

#### Tags
- /general/Multithreading Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_LNVFC
### Default
#### OriginalId=leakNoVarFunctionCall
#### Enabled=true
#### Warning=true
#### DisplayName=Leak No Var Function Call
#### HelpText
  Allocation with funcName, funcName doesn't release it.

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_LRVNU
### Default
#### OriginalId=leakReturnValNotUsed
#### Enabled=true
#### Warning=true
#### DisplayName=Leak Return Val Not Used
#### HelpText
  Return value of allocation function 'funcName' is not stored.

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_MAD
### Default
#### OriginalId=mismatchAllocDealloc
#### Enabled=true
#### Warning=true
#### DisplayName=Mismatch Alloc Dealloc
#### HelpText
  Mismatching allocation and deallocation: varname

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_MATF
### Default
#### OriginalId=moduloAlwaysTrueFalse
#### Enabled=true
#### Warning=true
#### DisplayName=Modulo Always True False
#### HelpText
  Comparison of modulo result is predetermined, because it is always less than 1.

#### Tags
- /general/Conditional Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_MBA
### Default
#### OriginalId=mismatchingBitAnd
#### Enabled=true
#### Warning=true
#### DisplayName=Mismatching Bit And
#### HelpText
  Mismatching bitmasks. Result is always 0 (X = Y & 0xf0; Z = X & 0x1; => Z=0).

#### Tags
- /general/Conditional Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_MC
### Default
#### OriginalId=memsetClass
#### Enabled=true
#### Warning=true
#### DisplayName=Memset Class
#### HelpText
  Using 'memfunc' on class that contains a classname is unsafe, because constructor, destructor and copy operator calls are omitted. These are necessary for this non-POD type to ensure that a valid object is created.

#### Tags
- /general/Object Orientedness Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_MCE
### Default
#### OriginalId=mismatchingContainerExpression
#### Enabled=true
#### Warning=true
#### DisplayName=Mismatching Container Expression
#### HelpText
  Iterators to containers from different expressions 'v1' and 'v2' are used together.

#### Tags
- /general/Suspicious Construct Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_MCF
### Default
#### OriginalId=memsetClassFloat
#### Enabled=true
#### Warning=true
#### DisplayName=Memset Class Float
#### HelpText
  Using memset() on class which contains a floating point number. This is not portable because memset() sets each byte of a block of memory to a specific value and the actual representation of a floating-point value is implementation defined. Note: In case of an IEEE754-1985 compatible implementation setting all bits to zero results in the value 0.0.

#### Tags
- /general/Object Orientedness Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_MCI
### Default
#### OriginalId=mismatchingContainerIterator
#### Enabled=true
#### Warning=true
#### DisplayName=Mismatching Container Iterator
#### HelpText
  Iterator 'it' from different container 'v1' are used together.

#### Tags
- /general/STL Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_MCOND
### Default
#### OriginalId=multiCondition
#### Enabled=true
#### Warning=true
#### DisplayName=Multi Condition
#### HelpText
  Expression is always false because 'else if' condition matches previous condition at line 1.

#### Tags
- /general/Conditional Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_MCR
### Default
#### OriginalId=memsetClassReference
#### Enabled=true
#### Warning=true
#### DisplayName=Memset Class Reference
#### HelpText
  Using 'memfunc' on class that contains a reference.

#### Tags
- /general/Object Orientedness Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_MF
### Default
#### OriginalId=memsetFloat
#### Enabled=true
#### Warning=true
#### DisplayName=Memset Float
#### HelpText
  The 2nd memset() argument 'varname' is a float, its representation is implementation defined. memset() is used to set each byte of a block of memory to a specific value and the actual representation of a floating-point value is implementation defined.

#### Tags
- /general/Simple Type Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_ML
### Default
#### OriginalId=memleak
#### Enabled=true
#### Warning=true
#### DisplayName=Memleak
#### HelpText
  Memory leak: varname

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_MMC
### Default
#### OriginalId=mismatchingContainers
#### Enabled=true
#### Warning=true
#### DisplayName=Mismatching Containers
#### HelpText
  Iterators of different containers 'v1' and 'v2' are used together.

#### Tags
- /general/STL Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_MO
### Default
#### OriginalId=missingOverride
#### Enabled=true
#### Warning=true
#### DisplayName=Missing Override
#### HelpText
  The function '' overrides a function in a base class but is not marked with a 'override' specifier.

#### Tags
- /general/Readability and Consistency Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_MOCE
### Default
#### OriginalId=mallocOnClassError
#### Enabled=true
#### Warning=true
#### DisplayName=Malloc On Class Error
#### HelpText
  Memory for class instance allocated with malloc(), but class a std::string. This is unsafe, since no constructor is called and class members remain uninitialized. Consider using 'new' instead.

#### Tags
- /general/Object Orientedness Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_MOCW
### Default
#### OriginalId=mallocOnClassWarning
#### Enabled=true
#### Warning=true
#### DisplayName=Malloc On Class Warning
#### HelpText
  Memory for class instance allocated with malloc(), but class provides constructors. This is unsafe, since no constructor is called and class members remain uninitialized. Consider using 'new' instead.

#### Tags
- /general/Object Orientedness Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_MOO
### Default
#### OriginalId=moduloofone
#### Enabled=true
#### Warning=true
#### DisplayName=Modulo Of One
#### HelpText
  Modulo of one is always equal to zero

#### Tags
- /general/Suspicious Construct Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_MOR
### Default
#### OriginalId=memleakOnRealloc
#### Enabled=true
#### Warning=true
#### DisplayName=Memleak On Realloc
#### HelpText
  Common realloc mistake: 'varname' nulled but not freed upon failure

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_MRFAO
### Default
#### OriginalId=operatorEqMissingReturnStatement
#### Enabled=true
#### Warning=true
#### DisplayName=Missing Return From Assignement Operator
#### HelpText
  No 'return' statement in non-void function causes undefined behavior.

#### Tags
- /general/Object Orientedness Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_MS
### Default
#### OriginalId=mismatchSize
#### Enabled=true
#### Warning=true
#### DisplayName=Mismatch Size
#### HelpText
  The allocated size sz is not a multiple of the underlying type's size.

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_MSO
### Default
#### OriginalId=multiplySizeof
#### Enabled=true
#### Warning=true
#### DisplayName=Multiply Sizeof
#### HelpText
  Multiplying sizeof() with sizeof() indicates a logic error.

#### Tags
- /general/Sizeof Operator Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_MVOOR
### Default
#### OriginalId=memsetValueOutOfRange
#### Enabled=true
#### Warning=true
#### DisplayName=Memset Value Out Of Range
#### HelpText
  The 2nd memset() argument 'varname' doesn't fit into an 'unsigned char'. The 2nd parameter is passed as an 'int', but the function fills the block of memory using the 'unsigned char' conversion of this value.

#### Tags
- /general/API Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_MZB
### Default
#### OriginalId=memsetZeroBytes
#### Enabled=true
#### Warning=true
#### DisplayName=Memset Zero Bytes
#### HelpText
  memset() called to fill 0 bytes. The second and third arguments might be inverted. The function memset ( void * ptr, int value, size_t num ) sets the first num bytes of the block of memory pointed by ptr to the specified value.

#### Tags
- /general/API Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_NAO
### Default
#### OriginalId=noOperatorEq
#### Enabled=true
#### Warning=true
#### DisplayName=No Assignment Operator
#### HelpText
  Class 'class' does not have a operator= which is recommended since it has dynamic memory/resource allocation(s).

#### Tags
- /general/Object Orientedness Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_NC
### Default
#### OriginalId=noConstructor
#### Enabled=true
#### Warning=true
#### DisplayName=No Constructor
#### HelpText
  The class 'classname' does not have a constructor although it has private member variables. Member variables of builtin types are left uninitialized when the class is instantiated. That may cause bugs or undefined behavior.

#### Tags
- /general/Object Orientedness Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_NCC
### Default
#### OriginalId=noCopyConstructor
#### Enabled=true
#### Warning=true
#### DisplayName=No Copy Constructor
#### HelpText
  Class 'class' does not have a copy constructor which is recommended since it has dynamic memory/resource allocation(s).

#### Tags
- /general/Object Orientedness Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_NCETR
### Default
#### OriginalId=rethrowNoCurrentException
#### Enabled=true
#### Warning=true
#### DisplayName=No Current Exception To Rethrow 
#### HelpText
  Rethrowing current exception with 'throw;', it seems there is no current exception to rethrow. If there is no current exception this calls std::terminate(). More: https://isocpp.org/wiki/faq/exceptions#throw-without-an-object

#### Tags
- /general/Suspicious Construct Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_NCI
### Default
#### OriginalId=negativeContainerIndex
#### Enabled=true
#### Warning=true
#### DisplayName=Negative Container Index
#### HelpText
  Array index -1 is out of bounds.

#### Tags
- /general/Buffer Overrun Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_ND
### Default
#### OriginalId=noDestructor
#### Enabled=true
#### Warning=true
#### DisplayName=No Destructor
#### HelpText
  Class 'class' does not have a destructor which is recommended since it has dynamic memory/resource allocation(s).

#### Tags
- /general/Object Orientedness Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_NEC
### Default
#### OriginalId=noExplicitConstructor
#### Enabled=true
#### Warning=true
#### DisplayName=No Explicit Constructor
#### HelpText
  Class 'classname' has a constructor with 1 argument that is not explicit. Such constructors should in general be explicit for type safety reasons. Using the explicit keyword in the constructor means some mistakes when using the class can be avoided.

#### Tags
- /general/Object Orientedness Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_NI
### Default
#### OriginalId=negativeIndex
#### Enabled=true
#### Warning=true
#### DisplayName=Negative Index
#### HelpText
  Negative array index

#### Tags
- /general/Buffer Overrun Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_NIAE
### Default
#### OriginalId=nanInArithmeticExpression
#### Enabled=true
#### Warning=true
#### DisplayName=Nan In Arithmetic Expression
#### HelpText
  Using NaN/Inf in a computation. Although nothing bad really happens, it is suspicious.

#### Tags
- /general/Suspicious Construct Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_NP
### Default
#### OriginalId=nullPointer
#### Enabled=true
#### Warning=true
#### DisplayName=Null Pointer
#### HelpText
  Null pointer dereference

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_NPDWDA
### Default
#### OriginalId=nullPointerDefaultArg
#### Enabled=true
#### Warning=true
#### DisplayName=NULL Pointer Dereference With Default Argument
#### HelpText
  Possible null pointer dereference if the default parameter value is used: pointer

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_OERRT
### Default
#### OriginalId=operatorEqRetRefThis
#### Enabled=true
#### Warning=true
#### DisplayName=Operator Eq Ret Ref This
#### HelpText
  'operator=' should return reference to 'this' instance.

#### Tags
- /general/Object Orientedness Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_OETS
### Default
#### OriginalId=operatorEqToSelf
#### Enabled=true
#### Warning=true
#### DisplayName=Operator Eq To Self
#### HelpText
  'operator=' should check for assignment to self to ensure that each block of dynamically allocated memory is owned and managed by only one instance of the class.

#### Tags
- /general/Object Orientedness Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_OEVE
### Default
#### OriginalId=operatorEqVarError
#### Enabled=true
#### Warning=true
#### DisplayName=Operator Eq Var Error
#### HelpText
  Member variable 'classname::' is not assigned a value in 'classname::operator='.

#### Tags
- /general/Object Orientedness Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_OI
### Default
#### OriginalId=objectIndex
#### Enabled=true
#### Warning=true
#### DisplayName=Object Index
#### HelpText
  The address of local variable '' is accessed at non-zero index.

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_OIC
### Default
#### OriginalId=oppositeInnerCondition
#### Enabled=true
#### Warning=true
#### DisplayName=Opposite Inner Condition
#### HelpText
  Opposite inner 'if' condition leads to a dead code block (outer condition is 'x' and inner condition is '!x').

#### Tags
- /general/Conditional Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_OPE
### Default
#### OriginalId=oppositeExpression
#### Enabled=true
#### Warning=true
#### DisplayName=Opposite Expression
#### HelpText
  Finding the opposite expression on both sides of an operator is suspicious and might indicate a cut and paste or logic error. Please examine this code carefully to determine if it is correct.

#### Tags
- /general/Suspicious Construct Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_OS
### Default
#### OriginalId=overlappingStrcmp
#### Enabled=true
#### Warning=true
#### DisplayName=Overlapping Strcmp
#### HelpText
  The expression 'strcmp(x,"def") != 0' is suspicious. It overlaps 'strcmp(x,"abc") == 0'.

#### Tags
- /general/Suspicious Construct Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_PAB
### Default
#### OriginalId=pointerArithBool
#### Enabled=true
#### Warning=true
#### DisplayName=Pointer Arith Bool
#### HelpText
  Converting pointer arithmetic result to bool. The boolean result is always true unless there is pointer arithmetic overflow, and overflow is undefined behaviour. Probably a dereference is forgotten.

#### Tags
- /general/Simple Type Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_PAE
### Default
#### OriginalId=publicAllocationError
#### Enabled=true
#### Warning=true
#### DisplayName=Public Allocation Error
#### HelpText
  Possible leak in public function. The pointer 'varname' is not deallocated before it is allocated.

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_PANC
### Default
#### OriginalId=pointerAdditionResultNotNull
#### Enabled=true
#### Warning=true
#### DisplayName=Pointer Addition Null Check
#### HelpText
  Comparison is wrong. Result of 'ptr+1' can't be 0 unless there is pointer overflow, and pointer overflow is undefined behaviour.

#### Tags
- /general/Conditional Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_PAORCWN
### Default
#### OriginalId=nullPointerArithmeticRedundantCheck
#### Enabled=true
#### Warning=true
#### DisplayName=Pointer Arithmetic Or Redundant Check With NULL
#### HelpText
  Either the condition is redundant or there is pointer arithmetic with NULL pointer.

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_PAWN
### Default
#### OriginalId=nullPointerArithmetic
#### Enabled=true
#### Warning=true
#### DisplayName=Pointer Arithmetic With NULL
#### HelpText
  Pointer arithmetic with NULL pointer.

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_PBV
### Default
#### OriginalId=passedByValue
#### Enabled=true
#### Warning=true
#### DisplayName=Passed By Value
#### HelpText
  Parameter 'parametername' is passed by value. It could be passed as a const reference which is usually faster and recommended in C++.

#### Tags
- /general/Performance Rules
- /tool/Cppcheck

#### Settings
- Priority=Major


## CPPCHECK_PED
### Default
#### OriginalId=preprocessorErrorDirective
#### Enabled=false
#### Warning=true
#### DisplayName=Preprocessor Error Directive
#### HelpText
  #error message

#### Tags
- /general/Preprocessor Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_PLTZ
### Default
#### OriginalId=pointerLessThanZero
#### Enabled=true
#### Warning=true
#### DisplayName=Pointer Less Than Zero
#### HelpText
  A pointer can not be negative so it is either pointless or an error to check if it is.

#### Tags
- /general/Simple Type Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_PO
### Default
#### OriginalId=postfixOperator
#### Enabled=true
#### Warning=true
#### DisplayName=Postfix Operator
#### HelpText
  Prefix ++/-- operators should be preferred for non-primitive types. Pre-increment/decrement can be more efficient than post-increment/decrement. Post-increment/decrement usually involves keeping a copy of the previous value around and adds a little extra code.

#### Tags
- /general/Performance Rules
- /tool/Cppcheck

#### Settings
- Priority=Major


## CPPCHECK_POOB
### Default
#### OriginalId=pointerOutOfBounds
#### Enabled=true
#### Warning=true
#### DisplayName=Pointer Out Of Bounds
#### HelpText
  Pointer arithmetic overflow.

#### Tags
- /general/Buffer Overrun Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_PP
### Default
#### OriginalId=pointerPositive
#### Enabled=true
#### Warning=true
#### DisplayName=Pointer Positive
#### HelpText
  A pointer can not be negative so it is either pointless or an error to check if it is not.

#### Tags
- /general/Simple Type Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_PS
### Default
#### OriginalId=pointerSize
#### Enabled=true
#### Warning=true
#### DisplayName=Pointer Size
#### HelpText
  Size of pointer 'varname' used instead of size of its data. This is likely to lead to a buffer overflow. You probably intend to write 'sizeof(*varname)'.

#### Tags
- /general/Sizeof Operator Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_PVC
### Default
#### OriginalId=pureVirtualCall
#### Enabled=true
#### Warning=true
#### DisplayName=Pure Virtual Call
#### HelpText
  Call of pure virtual function 'f' in constructor. The call will fail during runtime.

#### Tags
- /general/Object Orientedness Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_RA
### Default
#### OriginalId=redundantAssignment
#### Enabled=true
#### Warning=true
#### DisplayName=Redundant Assignment
#### HelpText
  Variable 'var' is reassigned a value before the old one has been used.

#### Tags
- /general/Performance Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_RAID
### Default
#### OriginalId=raceAfterInterlockedDecrement
#### Enabled=true
#### Warning=true
#### DisplayName=Race After Interlocked Decrement
#### HelpText
  Race condition: non-interlocked access after InterlockedDecrement(). Use InterlockedDecrement() return value instead.

#### Tags
- /general/Multithreading Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_RAIS
### Default
#### OriginalId=redundantAssignInSwitch
#### Enabled=true
#### Warning=true
#### DisplayName=Redundant Assign In Switch
#### HelpText
  Variable 'var' is reassigned a value before the old one has been used. 'break;' missing?

#### Tags
- /general/Suspicious Construct Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_RAOAV
### Default
#### OriginalId=returnAddressOfAutoVariable
#### Enabled=true
#### Warning=true
#### DisplayName=Return Address Of Auto Variable
#### HelpText
  Address of an auto-variable returned.

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_RAOFP
### Default
#### OriginalId=returnAddressOfFunctionParameter
#### Enabled=true
#### Warning=true
#### DisplayName=Return Address Of Function Parameter
#### HelpText
  Address of the function parameter 'parameter' becomes invalid after the function exits because function parameters are stored on the stack which is freed when the function exits. Thus the returned value is invalid.

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_RBOIS
### Default
#### OriginalId=redundantBitwiseOperationInSwitch
#### Enabled=true
#### Warning=true
#### DisplayName=Redundant Bitwise Operation In Switch
#### HelpText
  Redundant bitwise operation on 'varname' in 'switch' statement. 'break;' missing?

#### Tags
- /general/Suspicious Construct Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_RCIS
### Default
#### OriginalId=redundantCopyInSwitch
#### Enabled=true
#### Warning=true
#### DisplayName=Redundant Copy In Switch
#### HelpText
  Buffer 'var' is being written before its old content has been used. 'break;' missing?

#### Tags
- /general/Suspicious Construct Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_RCLC
### Default
#### OriginalId=redundantCopyLocalConst
#### Enabled=true
#### Warning=true
#### DisplayName=Redundant Copy Local Const
#### HelpText
  The const variable 'varname' is assigned a copy of the data. You can avoid the unnecessary data copying by converting 'varname' to const reference.

#### Tags
- /general/Performance Rules
- /tool/Cppcheck

#### Settings
- Priority=Major


## CPPCHECK_RCOND
### Default
#### OriginalId=redundantCondition
#### Enabled=true
#### Warning=true
#### DisplayName=Redundant Condition
#### HelpText
  Redundant condition: If x > 11 the condition x > 10 is always true.

#### Tags
- /general/Conditional Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_RCPY
### Default
#### OriginalId=redundantCopy
#### Enabled=true
#### Warning=true
#### DisplayName=Redundant Copy
#### HelpText
  Buffer 'var' is being written before its old content has been used.

#### Tags
- /general/Performance Rules
- /tool/Cppcheck

#### Settings
- Priority=Major


## CPPCHECK_RDL
### Default
#### OriginalId=returnDanglingLifetime
#### Enabled=true
#### Warning=true
#### DisplayName=Return Dangling Lifetime
#### HelpText
  Returning object that will be invalid when returning.

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_REC
### Default
#### OriginalId=reademptycontainer
#### Enabled=true
#### Warning=true
#### DisplayName=Read Empty Container
#### HelpText
  Reading from empty STL container 'var'

#### Tags
- /general/STL Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_RF
### Default
#### OriginalId=returnReference
#### Enabled=true
#### Warning=true
#### DisplayName=Return Reference
#### HelpText
  Reference to local variable returned.

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_RI
### Default
#### OriginalId=redundantInitialization
#### Enabled=true
#### Warning=true
#### DisplayName=Redundant Initialization
#### HelpText
  Redundant initialization for 'var'. The initialized value is overwritten before it is read.

#### Tags
- /general/Initialization Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_RIR
### Default
#### OriginalId=redundantIfRemove
#### Enabled=true
#### Warning=true
#### DisplayName=Redundant If Remove
#### HelpText
  Redundant checking of STL container element existence before removing it. It is safe to call the remove method on a non-existing element.

#### Tags
- /general/STL Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_RL
### Default
#### OriginalId=resourceLeak
#### Enabled=true
#### Warning=true
#### DisplayName=Resource Leak
#### HelpText
  Resource leak: varname

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_RLV
### Default
#### OriginalId=returnLocalVariable
#### Enabled=true
#### Warning=true
#### DisplayName=Return Local Variable
#### HelpText
  Pointer to local array variable returned.

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_RNBIBF
### Default
#### OriginalId=returnNonBoolInBooleanFunction
#### Enabled=true
#### Warning=true
#### DisplayName=Return Address Of Auto Variable
#### HelpText
  Non-boolean value returned from function returning bool

#### Tags
- /general/Suspicious Construct Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_RNPC
### Default
#### OriginalId=nullPointerRedundantCheck
#### Enabled=true
#### Warning=true
#### DisplayName=Redundant NULL Pointer Check
#### HelpText
  Either the condition is redundant or there is possible null pointer dereference: pointer.

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_RPO
### Default
#### OriginalId=redundantPointerOp
#### Enabled=true
#### Warning=true
#### DisplayName=Redundant Pointer Operation
#### HelpText
  Redundant pointer operation on 'varname' - it's already a pointer.

#### Tags
- /general/Suspicious Construct Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_RTF
### Default
#### OriginalId=returnTempReference
#### Enabled=true
#### Warning=true
#### DisplayName=Return Temp Reference
#### HelpText
  Reference to temporary returned.

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_RWOF
### Default
#### OriginalId=readWriteOnlyFile
#### Enabled=true
#### Warning=true
#### DisplayName=Read Write Only File
#### HelpText
  Read operation on a file that was opened only for writing.

#### Tags
- /general/Input Output Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_SA
### Default
#### OriginalId=selfAssignment
#### Enabled=true
#### Warning=true
#### DisplayName=Self Assignment
#### HelpText
  Redundant assignment of 'varname' to itself.

#### Tags
- /general/Suspicious Construct Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_SAR
### Default
#### OriginalId=shadowArgument
#### Enabled=true
#### Warning=true
#### DisplayName=Shadow Argument
#### HelpText
  Local variable 'argument' shadows outer argument

#### Tags
- /general/Readability and Consistency Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_SBN
### Default
#### OriginalId=shiftNegative
#### Enabled=true
#### Warning=true
#### DisplayName=Shift By Negative
#### HelpText
  Shifting by a negative value is undefined behaviour

#### Tags
- /general/Simple Type Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_SC
### Default
#### OriginalId=signConversion
#### Enabled=true
#### Warning=true
#### DisplayName=Sign Conversion
#### HelpText
  Expression 'var' can have a negative value. That is converted to an unsigned value and used in an unsigned calculation.

#### Tags
- /general/Simple Type Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_SCAI
### Default
#### OriginalId=signedCharArrayIndex
#### Enabled=true
#### Warning=true
#### DisplayName=Signed Char Array Index
#### HelpText
  Signed 'char' type used as array index. If the value can be greater than 127 there will be a buffer underflow because of sign extension.

#### Tags
- /general/Simple Type Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_SCP
### Default
#### OriginalId=stlcstrParam
#### Enabled=true
#### Warning=true
#### DisplayName=Stlcstr Param
#### HelpText
  The conversion from const char* as returned by c_str() to std::string creates an unnecessary string copy. Solve that by directly passing the string.

#### Tags
- /general/STL Rules
- /tool/Cppcheck

#### Settings
- Priority=Major


## CPPCHECK_SCR
### Default
#### OriginalId=stlcstrReturn
#### Enabled=true
#### Warning=true
#### DisplayName=Stlcstr Return
#### HelpText
  The conversion from const char* as returned by c_str() to std::string creates an unnecessary string copy. Solve that by directly returning the string.

#### Tags
- /general/STL Rules
- /tool/Cppcheck

#### Settings
- Priority=Major


## CPPCHECK_SCT
### Default
#### OriginalId=stlcstrthrow
#### Enabled=true
#### Warning=true
#### DisplayName=Stlcstr Throw
#### HelpText
  Dangerous usage of c_str(). The string is destroyed after the c_str() call so the thrown pointer is invalid.

#### Tags
- /general/STL Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_SF
### Default
#### OriginalId=shadowFunction
#### Enabled=true
#### Warning=true
#### DisplayName=Shadow Function
#### HelpText
  Local variable 'function' shadows outer function

#### Tags
- /general/Readability and Consistency Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_SI
### Default
#### OriginalId=selfInitialization
#### Enabled=true
#### Warning=true
#### DisplayName=Self Initialization
#### HelpText
  Member variable 'var' is initialized by itself.

#### Tags
- /general/Object Orientedness Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_SIE
### Default
#### OriginalId=sameIteratorExpression
#### Enabled=true
#### Warning=true
#### DisplayName=Same Iterator Expression
#### HelpText
  Same iterators expression are used for algorithm.

#### Tags
- /general/Performance Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_SIWDC1
### Default
#### OriginalId=iterators1
#### Enabled=true
#### Warning=true
#### DisplayName=Same Iterator With Different Containers1
#### HelpText
  Same iterator is used with different containers 'container1' and 'container2'.

#### Tags
- /general/STL Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_SIWDC2
### Default
#### OriginalId=iterators2
#### Enabled=true
#### Warning=true
#### DisplayName=Same Iterator With Different Containers2
#### HelpText
  Same iterator is used with different containers 'container0' and 'container1'.

#### Tags
- /general/STL Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_SIWDC3
### Default
#### OriginalId=iterators3
#### Enabled=true
#### Warning=true
#### DisplayName=Same Iterator With Different Containers3
#### HelpText
  Same iterator is used with containers 'container' that are defined in different scopes.

#### Tags
- /general/STL Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_SLW
### Default
#### OriginalId=stringLiteralWrite
#### Enabled=true
#### Warning=true
#### DisplayName=String Literal Write
#### HelpText
  Modifying string literal directly or indirectly is undefined behaviour.

#### Tags
- /general/Simple Type Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_SN
### Default
#### OriginalId=shiftNegativeLHS
#### Enabled=true
#### Warning=true
#### DisplayName=Shift Negative
#### HelpText
  Shifting a negative value is technically undefined behaviour

#### Tags
- /general/Simple Type Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_SOAF
### Default
#### OriginalId=seekOnAppendedFile
#### Enabled=true
#### Warning=true
#### DisplayName=Seek On Appended File
#### HelpText
  Repositioning operation performed on a file opened in append mode has no effect.

#### Tags
- /general/Input Output Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_SOC
### Default
#### OriginalId=sizeofCalculation
#### Enabled=true
#### Warning=true
#### DisplayName=Sizeof Calculation
#### HelpText
  Found calculation inside sizeof().

#### Tags
- /general/Sizeof Operator Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_SOD
### Default
#### OriginalId=sprintfOverlappingData
#### Enabled=true
#### Warning=true
#### DisplayName=Sprintf Overlapping Data
#### HelpText
  The variable 'varname' is used both as a parameter and as destination in s[n]printf(). The origin and destination buffers overlap. Quote from glibc (C-library) documentation (http://www.gnu.org/software/libc/manual/html_mono/libc.html#Formatted-Output-Functions): "If copying takes place between objects that overlap as a result of a call to sprintf() or snprintf(), the results are undefined."

#### Tags
- /general/Simple Type Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_SODMF
### Default
#### OriginalId=sizeofDivisionMemfunc
#### Enabled=true
#### Warning=true
#### DisplayName=Sizeof Division Memfunc
#### HelpText
  Division by result of sizeof(). memset() expects a size in bytes, did you intend to multiply instead?

#### Tags
- /general/Sizeof Operator Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_SODVP
### Default
#### OriginalId=sizeofDereferencedVoidPointer
#### Enabled=true
#### Warning=true
#### DisplayName=Sizeof Dereferenced Void Pointer
#### HelpText
  '*varname' is of type 'void', the behaviour of 'sizeof(void)' is not covered by the ISO C standard. A value for 'sizeof(void)' is defined only as part of a GNU C extension, which defines 'sizeof(void)' to be 1.

#### Tags
- /general/Sizeof Operator Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_SOFC
### Default
#### OriginalId=sizeofFunctionCall
#### Enabled=true
#### Warning=true
#### DisplayName=Sizeof Function Call
#### HelpText
  Found function call inside sizeof().

#### Tags
- /general/Sizeof Operator Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_SOSO
### Default
#### OriginalId=sizeofsizeof
#### Enabled=true
#### Warning=true
#### DisplayName=Sizeof Sizeof
#### HelpText
  Calling sizeof for 'sizeof looks like a suspicious code and most likely there should be just one 'sizeof'. The current code is equivalent to 'sizeof(size_t)'

#### Tags
- /general/Sizeof Operator Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_SOV
### Default
#### OriginalId=sizeofVoid
#### Enabled=true
#### Warning=true
#### DisplayName=Sizeof Void
#### HelpText
  Behaviour of 'sizeof(void)' is not covered by the ISO C standard. A value for 'sizeof(void)' is defined only as part of a GNU C extension, which defines 'sizeof(void)' to be 1.

#### Tags
- /general/Sizeof Operator Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_SOWNP
### Default
#### OriginalId=sizeofwithnumericparameter
#### Enabled=true
#### Warning=true
#### DisplayName=Sizeof With Numeric Parameter
#### HelpText
  It is unusual to use a constant value with sizeof. For example, 'sizeof(10)' returns 4 (in 32-bit systems) or 8 (in 64-bit systems) instead of 10. 'sizeof('A')' and 'sizeof(char)' can return different results.

#### Tags
- /general/Sizeof Operator Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_SOWSAP
### Default
#### OriginalId=sizeofwithsilentarraypointer
#### Enabled=true
#### Warning=true
#### DisplayName=Sizeof With Silent Array Pointer
#### HelpText
  Using 'sizeof' for array given as function argument returns the size of a pointer. It does not return the size of the whole array in bytes as might be expected. For example, this code:
  ``` cpp
     int f(char a[100]) {
         return sizeof(a);
     }
  ```
  returns 4 (in 32-bit systems) or 8 (in 64-bit systems) instead of 100 (the size of the array in bytes).

#### Tags
- /general/Sizeof Operator Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_SPC
### Default
#### OriginalId=strPlusChar
#### Enabled=true
#### Warning=true
#### DisplayName=Str Plus Char
#### HelpText
  Unusual pointer arithmetic. A value of type 'char' is added to a string literal.

#### Tags
- /general/Simple Type Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_SS
### Default
#### OriginalId=suspiciousSemicolon
#### Enabled=true
#### Warning=true
#### DisplayName=Suspicious Semicolon
#### HelpText
  Suspicious use of ; at the end of '' statement.

#### Tags
- /general/Readability and Consistency Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_SSC
### Default
#### OriginalId=staticStringCompare
#### Enabled=true
#### Warning=true
#### DisplayName=Static String Compare
#### HelpText
  The compared strings, 'str1' and 'str2', are always unequal. Therefore the comparison is unnecessary and looks suspicious.

#### Tags
- /general/Simple Type Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_STLB
### Default
#### OriginalId=stlBoundaries
#### Enabled=true
#### Warning=true
#### DisplayName=Stl Boundaries
#### HelpText
  Iterator compared with operator<. This is dangerous since the order of items in the container is not guaranteed. One should use operator!= instead to compare iterators.

#### Tags
- /general/STL Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_STLC
### Default
#### OriginalId=stlcstr
#### Enabled=true
#### Warning=true
#### DisplayName=Stlcstr
#### HelpText
  Dangerous usage of c_str(). The c_str() return value is only valid until its string is deleted.

#### Tags
- /general/STL Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_STLFBI
### Default
#### OriginalId=stlFindInsert
#### Enabled=true
#### Warning=true
#### DisplayName=Stl Find Before Insert
#### HelpText
  Searching before insertion is not necessary.

#### Tags
- /general/STL Rules
- /tool/Cppcheck

#### Settings
- Priority=Major


## CPPCHECK_STLIF
### Default
#### OriginalId=stlIfFind
#### Enabled=true
#### Warning=true
#### DisplayName=Stl If Find
#### HelpText
  Suspicious condition. The result of find() is an iterator, but it is not properly checked.

#### Tags
- /general/STL Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_STLISF
### Default
#### OriginalId=stlIfStrFind
#### Enabled=true
#### Warning=true
#### DisplayName=Stl If Str Find
#### HelpText
  Either inefficient or wrong usage of string::find(). string::starts_with() will be faster if string::find's result is compared with 0, because it will not scan the whole string. If your intention is to check that there are no findings in the string, you should compare with std::string::npos.

#### Tags
- /general/STL Rules
- /tool/Cppcheck

#### Settings
- Priority=Major


## CPPCHECK_STLMC
### Default
#### OriginalId=StlMissingComparison
#### Enabled=true
#### Warning=true
#### DisplayName=Stl Missing Comparison
#### HelpText
  The iterator incrementing is suspicious - it is incremented at line  and then at line . The loop might unintentionally skip an element in the container. There is no comparison between these increments to prevent that the iterator is incremented beyond the end.

#### Tags
- /general/STL Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_STLOOB
### Default
#### OriginalId=stlOutOfBounds
#### Enabled=true
#### Warning=true
#### DisplayName=Stl Out Of Bounds
#### HelpText
  When i==foo.size(), foo[i] is out of bounds.

#### Tags
- /general/STL Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_STLS
### Default
#### OriginalId=stlSize
#### Enabled=true
#### Warning=true
#### DisplayName=Stl Size
#### HelpText
  Checking for 'list' emptiness might be inefficient. Using list.empty() instead of list.size() can be faster. list.size() can take linear time but list.empty() is guaranteed to take constant time.

#### Tags
- /general/STL Rules
- /tool/Cppcheck

#### Settings
- Priority=Major


## CPPCHECK_STMB
### Default
#### OriginalId=shiftTooManyBits
#### Enabled=true
#### Warning=true
#### DisplayName=Shift Too Many Bits
#### HelpText
  Shifting 32-bit value by 40 bits is undefined behaviour

#### Tags
- /general/Simple Type Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_STMBS
### Default
#### OriginalId=shiftTooManyBitsSigned
#### Enabled=true
#### Warning=true
#### DisplayName=Shift Too Many Bits Signed
#### HelpText
  Shifting signed 32-bit value by 31 bits is implementation-defined behaviour

#### Tags
- /general/Simple Type Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_STRCMP
### Default
#### OriginalId=stringCompare
#### Enabled=true
#### Warning=true
#### DisplayName=String Compare
#### HelpText
  The compared strings, 'varname1' and 'varname2', are identical. This could be a logic bug.

#### Tags
- /general/Simple Type Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_SUSPC
### Default
#### OriginalId=suspiciousCase
#### Enabled=true
#### Warning=true
#### DisplayName=Suspicious Case
#### HelpText
  Using an operator like '||' in a case label is suspicious. Did you intend to use a bitwise operator, multiple case labels or if/else instead?

#### Tags
- /general/Suspicious Construct Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_SV
### Default
#### OriginalId=shadowVariable
#### Enabled=true
#### Warning=true
#### DisplayName=Shadow Variable
#### HelpText
  Local variable 'variable' shadows outer variable

#### Tags
- /general/Readability and Consistency Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_TINF
### Default
#### OriginalId=throwInNoexceptFunction
#### Enabled=true
#### Warning=true
#### DisplayName=Throw In Noexcept Function
#### HelpText
  Exception thrown in function declared not to throw exceptions.

#### Tags
- /general/Exception Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_TLCA
### Default
#### OriginalId=truncLongCastAssignment
#### Enabled=true
#### Warning=true
#### DisplayName=Trunc Long Cast Assignment
#### HelpText
  int result is assigned to long variable. If the variable is long to avoid loss of information, then there is loss of information. To avoid loss of information you must cast a calculation operand to long, for example 'l = a * b;' => 'l = (long)a * b;'.

#### Tags
- /general/Simple Type Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_TLCR
### Default
#### OriginalId=truncLongCastReturn
#### Enabled=true
#### Warning=true
#### DisplayName=Trunc Long Cast Return
#### HelpText
  int result is returned as long value. If the return value is long to avoid loss of information, then there is loss of information. To avoid loss of information you must cast a calculation operand to long, for example 'return a*b;' => 'return (long)a*b'.

#### Tags
- /general/Simple Type Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_TS
### Default
#### OriginalId=thisSubtraction
#### Enabled=true
#### Warning=true
#### DisplayName=This Subtraction
#### HelpText
  Suspicious pointer subtraction. Did you intend to write '->'?

#### Tags
- /general/Object Orientedness Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_TUAF
### Default
#### OriginalId=thisUseAfterFree
#### Enabled=true
#### Warning=true
#### DisplayName=This Is Used After Free
#### HelpText
  Using member 'x' when 'this' might be invalid

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_UA
### Default
#### OriginalId=leakUnsafeArgAlloc
#### Enabled=true
#### Warning=true
#### DisplayName=Unsafe allocation
#### HelpText
  Unsafe allocation. If funcName() throws, memory could be leaked. Use make_shared<int>() instead.

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_UAA
### Default
#### OriginalId=uselessAssignmentArg
#### Enabled=true
#### Warning=true
#### DisplayName=Useless Assignment Arg
#### HelpText
  Assignment of function parameter has no effect outside the function.

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_UAPARG
### Default
#### OriginalId=uselessAssignmentPtrArg
#### Enabled=true
#### Warning=true
#### DisplayName=Useless Assignment Ptr Arg
#### HelpText
  Assignment of function parameter has no effect outside the function. Did you forget dereferencing it?

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_UAV
### Default
#### OriginalId=unassignedVariable
#### Enabled=true
#### Warning=true
#### DisplayName=Unassigned Variable
#### HelpText
  Variable 'varname' is not assigned a value.

#### Tags
- /general/Unnecessary and Unused Code Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_UCC
### Default
#### OriginalId=uselessCallsCompare
#### Enabled=true
#### Warning=true
#### DisplayName=Useless Calls Compare
#### HelpText
  'std::string::find()' returns zero when given itself as parameter (str.find(str)). As it is currently the code is inefficient. It is possible either the string searched ('str') or searched for ('str') is wrong.

#### Tags
- /general/STL Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_UCCL
### Default
#### OriginalId=unsafeClassCanLeak
#### Enabled=true
#### Warning=true
#### DisplayName=Unsafe Class Can Leak
#### HelpText
  The class 'class' is unsafe, wrong usage can cause memory/resource leaks for 'class::varname'. This can for instance be fixed by adding proper cleanup in the destructor.

#### Tags
- /general/Memory Handling Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_UCE
### Default
#### OriginalId=uselessCallsEmpty
#### Enabled=true
#### Warning=true
#### DisplayName=Useless Calls Empty
#### HelpText
  Ineffective call of function 'empty()'. Did you intend to call 'clear()' instead?

#### Tags
- /general/STL Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_UCF
### Default
#### OriginalId=useClosedFile
#### Enabled=true
#### Warning=true
#### DisplayName=Use Closed File
#### HelpText
  Used file that is not opened.

#### Tags
- /general/Input Output Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_UCR
### Default
#### OriginalId=uselessCallsRemove
#### Enabled=true
#### Warning=true
#### DisplayName=Useless Calls Remove
#### HelpText
  The return value of std::remove() is ignored. This function returns an iterator to the end of the range containing those elements that should be kept. Elements past new end remain valid but with unspecified values. Use the erase method of the container to delete them.

#### Tags
- /general/STL Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_UCRM
### Default
#### OriginalId=unsafeClassRefMember
#### Enabled=true
#### Warning=true
#### DisplayName=Unsafe Class Reference Member
#### HelpText
  Unsafe class checking: The const reference member 'UnsafeClass::var' is initialized by a const reference constructor argument. You need to be careful about lifetime issues. If you pass a local variable or temporary value in this constructor argument, be extra careful. If the argument is always some global object that is never destroyed then this is safe usage. However it would be defensive to make the member 'UnsafeClass::var' a non-reference variable or a smart pointer.

#### Tags
- /general/Initialization Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_UCS
### Default
#### OriginalId=uselessCallsSwap
#### Enabled=true
#### Warning=true
#### DisplayName=Useless Calls Swap
#### HelpText
  The 'swap()' function has no logical effect when given itself as parameter (str.swap(str)). As it is currently the code is inefficient. Is the object or the parameter wrong here?

#### Tags
- /general/STL Rules
- /tool/Cppcheck

#### Settings
- Priority=Major


## CPPCHECK_UCSS
### Default
#### OriginalId=uselessCallsSubstr
#### Enabled=true
#### Warning=true
#### DisplayName=Useless Calls Substr
#### HelpText
  Ineffective call of function 'substr' because it returns a copy of the object. Use operator= instead.

#### Tags
- /general/STL Rules
- /tool/Cppcheck

#### Settings
- Priority=Major


## CPPCHECK_UDMV
### Default
#### OriginalId=uninitDerivedMemberVar
#### Enabled=true
#### Warning=true
#### DisplayName=Uninitialized Derived Member Variable
#### HelpText
  Member variable 'classname::varname' is not initialized in the constructor. Maybe it should be initialized directly in the class classname?

#### Tags
- /general/Initialization Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_UDPMV
### Default
#### OriginalId=uninitDerivedMemberVarPrivate
#### Enabled=true
#### Warning=true
#### DisplayName=Uninitialized Derived Private Member Variable
#### HelpText
  Member variable 'classname::varnamepriv' is not initialized in the constructor. Maybe it should be initialized directly in the class classname?

#### Tags
- /general/Initialization Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_UEO
### Default
#### OriginalId=unknownEvaluationOrder
#### Enabled=true
#### Warning=true
#### DisplayName=Unknown Evaluation Order
#### HelpText
  Expression 'x = x++;' depends on order of evaluation of side effects

#### Tags
- /general/Side Effect Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_UES
### Default
#### OriginalId=unhandledExceptionSpecification
#### Enabled=true
#### Warning=true
#### DisplayName=Unhandled Exception Specification
#### HelpText
  Unhandled exception specification when calling function foo(). Either use a try/catch around the function call, or add a exception specification for funcname() also.

#### Tags
- /general/Exception Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_UID
### Default
#### OriginalId=uninitdata
#### Enabled=true
#### Warning=true
#### DisplayName=Uninitialized Data
#### HelpText
  Memory is allocated but not initialized: varname

#### Tags
- /general/Initialization Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_UIL
### Default
#### OriginalId=useInitializationList
#### Enabled=true
#### Warning=true
#### DisplayName=Use Initialization List
#### HelpText
  When an object of a class is created, the constructors of all member variables are called consecutively in the order the variables are declared, even if you don't explicitly write them to the initialization list. You could avoid assigning 'variable' a value by passing the value to the constructor in the initialization list.

#### Tags
- /general/Object Orientedness Rules
- /tool/Cppcheck

#### Settings
- Priority=Major


## CPPCHECK_UISM
### Default
#### OriginalId=uninitStructMember
#### Enabled=true
#### Warning=true
#### DisplayName=Uninit Struct Member
#### HelpText
  Uninitialized struct member: a.b

#### Tags
- /general/Initialization Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_UIV
### Default
#### OriginalId=uninitvar
#### Enabled=true
#### Warning=true
#### DisplayName=Uninitialized Variable
#### HelpText
  Uninitialized variable: varname

#### Tags
- /general/Initialization Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_UL
### Default
#### OriginalId=unusedLabel
#### Enabled=true
#### Warning=true
#### DisplayName=Unused Label
#### HelpText
  Label '' is not used.

#### Tags
- /general/Unnecessary and Unused Code Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_ULITC
### Default
#### OriginalId=unusedLabelConfiguration
#### Enabled=true
#### Warning=true
#### DisplayName=Unused Label In This Configuration
#### HelpText
  Label '' is not used. There is #if in function body so the label might be used in code that is removed by the preprocessor.

#### Tags
- /general/Unnecessary and Unused Code Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_ULTZ
### Default
#### OriginalId=unsignedLessThanZero
#### Enabled=true
#### Warning=true
#### DisplayName=Unsigned Less Than Zero
#### HelpText
  The unsigned expression 'varname' will never be negative so it is either pointless or an error to check if it is.

#### Tags
- /general/Simple Type Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_UMV
### Default
#### OriginalId=uninitMemberVar
#### Enabled=true
#### Warning=true
#### DisplayName=Uninitialized Member Variable
#### HelpText
  Member variable 'classname::varname' is not initialized in the constructor.

#### Tags
- /general/Object Orientedness Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_UP
### Default
#### OriginalId=unsignedPositive
#### Enabled=true
#### Warning=true
#### DisplayName=Unsigned Positive
#### HelpText
  Unsigned expression 'varname' can't be negative so it is unnecessary to test it.

#### Tags
- /general/Simple Type Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_UPF
### Default
#### OriginalId=unusedPrivateFunction
#### Enabled=true
#### Warning=true
#### DisplayName=Unused Private Function
#### HelpText
  Unused private function: 'classname::funcname'

#### Tags
- /general/Object Orientedness Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_UPMC
### Default
#### OriginalId=unpreciseMathCall
#### Enabled=true
#### Warning=true
#### DisplayName=Unprecise Math Call
#### HelpText
  Expression '1 - erf(x)' can be replaced by 'erfc(x)' to avoid loss of precision.

#### Tags
- /general/API Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_UPMV
### Default
#### OriginalId=uninitMemberVarPrivate
#### Enabled=true
#### Warning=true
#### DisplayName=Uninitialized Private Member Variable
#### HelpText
  Member variable 'classname::varnamepriv' is not initialized in the constructor.

#### Tags
- /general/Initialization Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_URC
### Default
#### OriginalId=unreachableCode
#### Enabled=true
#### Warning=true
#### DisplayName=Unreachable Code
#### HelpText
  Statements following return, break, continue, goto or throw will never be executed.

#### Tags
- /general/Unreachable Code Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_URV
### Default
#### OriginalId=unreadVariable
#### Enabled=true
#### Warning=true
#### DisplayName=Unread Variable
#### HelpText
  Variable 'varname' is assigned a value that is never used.

#### Tags
- /general/Unnecessary and Unused Code Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_USA
### Default
#### OriginalId=useStlAlgorithm
#### Enabled=true
#### Warning=true
#### DisplayName=Use STL Algorithm
#### HelpText
  Consider using  algorithm instead of a raw loop.

#### Tags
- /general/STL Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_USL
### Default
#### OriginalId=unusedLabelSwitch
#### Enabled=true
#### Warning=true
#### DisplayName=Unused Switch Label
#### HelpText
  Label '' is not used. Should this be a 'case' of the enclosing switch()?

#### Tags
- /general/Unnecessary and Unused Code Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_USLITC
### Default
#### OriginalId=unusedLabelSwitchConfiguration
#### Enabled=true
#### Warning=true
#### DisplayName=Unused Switch Label in This Configuration
#### HelpText
  Label '' is not used. There is #if in function body so the label might be used in code that is removed by the preprocessor. Should this be a 'case' of the enclosing switch()?

#### Tags
- /general/Unnecessary and Unused Code Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_UUAM
### Default
#### OriginalId=unusedAllocatedMemory
#### Enabled=true
#### Warning=true
#### DisplayName=Unused Allocated Memory
#### HelpText
  Variable 'varname' is allocated memory that is never used.

#### Tags
- /general/Unnecessary and Unused Code Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_UUF
### Default
#### OriginalId=unusedFunction
#### Enabled=true
#### Warning=true
#### DisplayName=Unused Function
#### HelpText
  The function 'funcName' is never used.

#### Tags
- /general/Unnecessary and Unused Code Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_UUSM
### Default
#### OriginalId=unusedStructMember
#### Enabled=true
#### Warning=true
#### DisplayName=Unused Struct Member
#### HelpText
  struct member 'structname::variable' is never used.

#### Tags
- /general/Unnecessary and Unused Code Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_UUSO
### Default
#### OriginalId=unusedScopedObject
#### Enabled=true
#### Warning=true
#### DisplayName=Unused Scoped Object
#### HelpText
  Instance of 'varname' object is destroyed immediately.

#### Tags
- /general/Suspicious Construct Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_UUV
### Default
#### OriginalId=unusedVariable
#### Enabled=true
#### Warning=true
#### DisplayName=Unused Variable
#### HelpText
  Unused variable: varname

#### Tags
- /general/Unnecessary and Unused Code Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_VAEM
### Default
#### OriginalId=va_end_missing
#### Enabled=true
#### Warning=true
#### DisplayName=Va_end Missing
#### HelpText
  va_list 'vl' was opened but not closed by va_end().

#### Tags
- /general/Variable Argument Related Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_VALUBS
### Default
#### OriginalId=va_list_usedBeforeStarted
#### Enabled=true
#### Warning=true
#### DisplayName=Va_list Used Before Started
#### HelpText
  va_list 'vl' used before va_start() was called.

#### Tags
- /general/Variable Argument Related Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_VASRP
### Default
#### OriginalId=va_start_referencePassed
#### Enabled=true
#### Warning=true
#### DisplayName=Va_start Reference Passed
#### HelpText
  Using reference 'arg1' as parameter for va_start() results in undefined behaviour.

#### Tags
- /general/Variable Argument Related Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_VASSC
### Default
#### OriginalId=va_start_subsequentCalls
#### Enabled=true
#### Warning=true
#### DisplayName=Va_start Subsequent Calls
#### HelpText
  va_start() or va_copy() called subsequently on 'vl' without va_end() in between.

#### Tags
- /general/Variable Argument Related Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_VASWP
### Default
#### OriginalId=va_start_wrongParameter
#### Enabled=true
#### Warning=true
#### DisplayName=Va_start Wrong Parameter
#### HelpText
  'arg1' given to va_start() is not last named argument of the function. Did you intend to pass 'arg2'?

#### Tags
- /general/Variable Argument Related Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_VCIC
### Default
#### OriginalId=virtualCallInConstructor
#### Enabled=true
#### Warning=true
#### DisplayName=Virtual Call In Constructor
#### HelpText
  Virtual function 'f' is called from constructor '' at line 1. Dynamic binding is not used.

#### Tags
- /general/Object Orientedness Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_VCWSL
### Default
#### OriginalId=literalWithCharPtrCompare
#### Enabled=true
#### Warning=true
#### DisplayName=Variable Comparison With String Literal
#### HelpText
  String literal compared with variable 'foo'. Did you intend to use strcmp() instead?

#### Tags
- /general/Simple Type Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_VD
### Default
#### OriginalId=virtualDestructor
#### Enabled=true
#### Warning=true
#### DisplayName=Virtual Destructor
#### HelpText
  Class 'Base' which is inherited by class 'Derived' does not have a virtual destructor. If you destroy instances of the derived class by deleting a pointer that points to the base class, only the destructor of the base class is executed. Thus, dynamic memory that is managed by the derived class could leak. This can be avoided by adding a virtual destructor to the base class.

#### Tags
- /general/Object Orientedness Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_VFNUB
### Default
#### OriginalId=varFuncNullUB
#### Enabled=true
#### Warning=true
#### DisplayName=Var Func Null UB
#### HelpText
  Passing NULL after the last typed argument to a variadic function leads to undefined behaviour.
  The C99 standard, in section 7.15.1.1, states that if the type used by va_arg() is not compatible with the type of the actual next argument (as promoted according to the default argument promotions), the behavior is undefined.
  The value of the NULL macro is an implementation-defined null pointer constant (7.17), which can be any integer constant expression with the value 0, or such an expression casted to (void*) (6.3.2.3). This includes values like 0, 0L, or even 0LL.
  In practice on common architectures, this will cause real crashes if sizeof(int) != sizeof(void*), and NULL is defined to 0 or any other null pointer constant that promotes to int.
  To reproduce you might be able to use this little code example on 64bit platforms. If the output includes "ERROR", the sentinel had only 4 out of 8 bytes initialized to zero and was not detected as the final argument to stop argument processing via va_arg(). Changing the 0 to (void*)0 or 0L will make the "ERROR" output go away.
  ``` cpp
  #include <stdarg.h>
  #include <stdio.h>
  void f(char *s, ...) {
      va_list ap;
      va_start(ap,s);
      for (;;) {
          char *p = va_arg(ap,char*);
          printf("%018p, %s\n", p, (long)p & 255 ? p : "");
          if(!p) break;
      }
      va_end(ap);
  }

  void g() {
      char *s2 = "x";
      char *s3 = "ERROR";

      // changing 0 to 0L for the 7th argument (which is intended to act as sentinel) makes the error go away on x86_64
      f("first", s2, s2, s2, s2, s2, 0, s3, (char*)0);
  }

  void h() {
      int i;
      volatile unsigned char a[1000];
      for (i = 0; i<sizeof(a); i++)
          a[i] = -1;
  }

  int main() {
      h();
      g();
      return 0;
  }
  ```

#### Tags
- /general/Variable Argument Related Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_VS
### Default
#### OriginalId=variableScope
#### Enabled=true
#### Warning=true
#### DisplayName=Variable Scope
#### HelpText
  The scope of the variable 'varname' can be reduced. Warning: Be careful when fixing this message, especially when there are inner loops. Here is an example where cppcheck will write that the scope for 'i' can be reduced:
  ``` cpp
  void f(int x)
  {
      int i = 0;
      if (x) {
          // it's safe to move 'int i = 0;' here
          for (int n = 0; n < 10; ++n) {
              // it is possible but not safe to move 'int i = 0;' here
              do_something(&i);
          }
      }
  }
  When you see this message it is always safe to reduce the variable scope 1 level.
  ```
  
#### Tags
- /general/Readability and Consistency Rules
- /tool/Cppcheck

#### Settings
- Priority=Minor


## CPPCHECK_WMC
### Default
#### OriginalId=wrongmathcall
#### Enabled=true
#### Warning=true
#### DisplayName=Wrong Math Call
#### HelpText
  Passing value '#' to #() leads to implementation-defined result.

#### Tags
- /general/API Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_WPPS
### Default
#### OriginalId=wrongPipeParameterSize
#### Enabled=true
#### Warning=true
#### DisplayName=Wrong Pipe Parameter Size
#### HelpText
  The pipe()/pipe2() system command takes an argument, which is an array of exactly two integers.
  The variable 'varname' is an array of size dimension, which does not match.

#### Tags
- /general/API Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_WPSAN
### Default
#### OriginalId=wrongPrintfScanfArgNum
#### Enabled=true
#### Warning=true
#### DisplayName=Wrong Printf Scanf Arg Num
#### HelpText
  printf format string requires 3 parameters but only 2 are given.

#### Tags
- /general/Input Output Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_WPSPPE
### Default
#### OriginalId=wrongPrintfScanfParameterPositionError
#### Enabled=true
#### Warning=true
#### DisplayName=Wrong Printf Scanf Parameter Position Error
#### HelpText
  printf: referencing parameter 2 while 1 arguments given

#### Tags
- /general/Input Output Rules
- /tool/Cppcheck

#### Settings
- Priority=Critical


## CPPCHECK_WROF
### Default
#### OriginalId=writeReadOnlyFile
#### Enabled=true
#### Warning=true
#### DisplayName=Write Read Only File
#### HelpText
  Write operation on a file that was opened only for reading.

#### Tags
- /general/Input Output Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_ZD
### Default
#### OriginalId=zerodiv
#### Enabled=true
#### Warning=true
#### DisplayName=Zerodiv
#### HelpText
  Division by zero.

#### Tags
- /general/Division Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker


## CPPCHECK_ZDC
### Default
#### OriginalId=zerodivcond
#### Enabled=true
#### Warning=true
#### DisplayName=Zerodivcond
#### HelpText
  Either the condition is redundant or there is division by zero.

#### Tags
- /general/Division Rules
- /tool/Cppcheck

#### Settings
- Priority=Blocker
