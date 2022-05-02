# ToolDescription
## Default
### ID=FindBugs
### Description
  OpenStaticAnalyzer incorporates the [SpotBugs] tool for coding rule violation checking and imports its results. OpenStaticAnalyzer also associates the issued rule violations with source code elements (i.e. methods, classes, packages, and components), and calculates metrics for the source code elements, which represent the amount of violations of each ruleset, rule, and priority groups, respectively.

  OpenStaticAnalyzer uses SpotBugs "as is", without any guaranties that the results of SpotBugs are correct. All statements of the SpotBugs license apply here as well. All texts describing the rulesets and the individual rules are copied from the configuration files of SpotBugs with some minor grammatical fixes.

# Includes
- cwe_metadata.md
- FindBugs.rul_metadata.md
- owasp_metadata.md
- sei_cert_metadata.md

# Metrics
## FB_ACEJFE
### Default
#### OriginalId=AM_CREATES_EMPTY_JAR_FILE_ENTRY
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Creates Empty Jar File Entry
#### WarningText
  Empty jar file entry created in {1}

#### HelpText
  The code calls `putNextEntry()`, immediately followed by a call to `closeEntry()`. This results in an empty JarFile entry. The contents of the entry should be written to the JarFile between the calls to `putNextEntry()` and `closeEntry()`.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_ACEZFE
### Default
#### OriginalId=AM_CREATES_EMPTY_ZIP_FILE_ENTRY
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Creates Empty Zip File Entry
#### WarningText
  Empty zip file entry created in {1}

#### HelpText
  The code calls `putNextEntry()`, immediately followed by a call to `closeEntry()`. This results in an empty ZipFile entry. The contents of the entry should be written to the ZipFile between the calls to `putNextEntry()` and `closeEntry()`.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_ACF
### Default
#### OriginalId=FI_EXPLICIT_INVOCATION
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Explicit Invocation
#### WarningText
  Explicit invocation of {2} in {1}

#### HelpText
  This method contains an explicit invocation of the `finalize()` method on an object.  Because finalizer methods are supposed to be executed once, and only by the VM, this is a bad idea.

  If a connected set of objects beings finalizable, then the VM will invoke the finalize method on all the finalizable object, possibly at the same time in different threads. Thus, it is a particularly bad idea, in the finalize method for a class X, invoke finalize on objects referenced by X, because they may already be getting finalized in a separate thread.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_ADLIBDC
### Default
#### OriginalId=DMI_BIGDECIMAL_CONSTRUCTED_FROM_DOUBLE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bigdecimal Constructed From Double
#### WarningText
  BigDecimal constructed from {4} in {1}

#### HelpText
  This code creates a BigDecimal from a double value that doesn’t translate well to a decimal number. For example, one might assume that writing new BigDecimal(0.1) in Java creates a BigDecimal which is exactly equal to 0.1 (an unscaled value of 1, with a scale of 1), but it is actually equal to 0.1000000000000000055511151231257827021181583404541015625. You probably want to use the BigDecimal.valueOf(double d) method, which uses the String representation of the double to create the BigDecimal (e.g., BigDecimal.valueOf(0.1) gives 0.1).


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_AOSOCA
### Default
#### OriginalId=AT_OPERATION_SEQUENCE_ON_CONCURRENT_ABSTRACTION
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Operation Sequence On Concurrent Abstraction
#### WarningText
  Sequence of calls to {2} may not be atomic in {1}

#### HelpText
  This code contains a sequence of calls to a concurrent abstraction (such as a concurrent hash map). These calls will not be executed atomically.


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_APFIFC
### Default
#### OriginalId=CI_CONFUSED_INHERITANCE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Confused Inheritance
#### WarningText
  Class {0} is final but declares protected field {1}

#### HelpText
  This class is declared to be final, but declares fields to be protected. Since the class is final, it can not be derived from, and the use of protected is confusing. The access modifier for the field should be changed to private or public to represent the true use for the field.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_BA
### Default
#### OriginalId=BIT_AND
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=And
#### WarningText
  Incompatible bit masks in (e & {2} == {3}) yields a constant result in {1}

#### HelpText
  This method compares an expression of the form (e & C) to D, which will always compare unequal due to the specific values of constants C and D. This may indicate a logic error or typo.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_BAOSB
### Default
#### OriginalId=BIT_ADD_OF_SIGNED_BYTE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Add Of Signed Byte
#### WarningText
  Bitwise add of signed byte value computed in {1}

#### HelpText
  Adds a byte value and a value which is known to have the 8 lower bits clear. Values loaded from a byte array are sign extended to 32 bits before any bitwise operations are performed on the value. Thus, if `b[0]` contains the value `0xff`, and `x` is initially 0, then the code `((x << 8) + b[0])` will sign extend `0xff` to get `0xffffffff`, and thus give the value `0xffffffff` as the result.

  In particular, the following code for packing a byte array into an int is badly wrong:

  ``` java
  int result = 0;
  for(int i = 0; i < 4; i++)
      result = ((result << 8) + b[i]);
  ```

  The following idiom will work instead:

  ``` java
  int result = 0;
  for(int i = 0; i < 4; i++)
      result = ((result << 8) + (b[i] & 0xff));
  ```


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_BAZ
### Default
#### OriginalId=BIT_AND_ZZ
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=And Zz
#### WarningText
  Check to see if ((...) & 0) == 0 in {1}

#### HelpText
  This method compares an expression of the form `(e & 0)` to 0, which will always compare equal. This may indicate a logic error or typo.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_BBAC
### Default
#### OriginalId=BAC_BAD_APPLET_CONSTRUCTOR
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Applet Constructor
#### WarningText
  Bad Applet Constructor relies on uninitialized AppletStub

#### HelpText
  This constructor calls methods in the parent Applet that rely on the AppletStub. Since the AppletStub isn't initialized until the init() method of this applet is called, these methods will not perform correctly.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_BBCTAC
### Default
#### OriginalId=BC_BAD_CAST_TO_ABSTRACT_COLLECTION
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Cast To Abstract Collection
#### WarningText
  Questionable cast from Collection to abstract class {3} in {1}

#### HelpText
  This code casts a Collection to an abstract collection (such as `List`, `Set`, or `Map`). Ensure that you are guaranteed that the object is of the type you are casting to. If all you need is to be able to iterate through a collection, you don’t need to cast it to a Set or List.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_BBCTCC
### Default
#### OriginalId=BC_BAD_CAST_TO_CONCRETE_COLLECTION
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Cast To Concrete Collection
#### WarningText
  Questionable cast from {2} to {3} in {1}

#### HelpText
  This code casts an abstract collection (such as a Collection, List, or Set) to a specific concrete implementation (such as an ArrayList or HashSet). This might not be correct, and it may make your code fragile, since it makes it harder to switch to other concrete implementations at a future point. Unless you have a particular reason to do so, just use the abstract collection class.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_BBIU
### Default
#### OriginalId=BX_BOXING_IMMEDIATELY_UNBOXED
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Boxing Immediately Unboxed
#### WarningText
  Primitive value is boxed and then immediately unboxed in {1}

#### HelpText
  A primitive is boxed, and then immediately unboxed. This probably is due to a manual boxing in a place where an unboxed value is required, thus forcing the compiler to immediately undo the work of the boxing.


#### Tags
- /tool/FindBugs
- /general/Optimization Rules

#### Settings
- Priority=Major


## FB_BBIUTPC
### Default
#### OriginalId=BX_BOXING_IMMEDIATELY_UNBOXED_TO_PERFORM_COERCION
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Boxing Immediately Unboxed To Perform Coercion
#### WarningText
  Primitive value is boxed then unboxed to perform primitive coercion in {1}

#### HelpText
  A primitive boxed value constructed and then immediately converted into a different primitive type (e.g., `new Double(d).intValue()`). Just perform direct primitive coercion (e.g., `(int) d`).


#### Tags
- /tool/FindBugs
- /general/Optimization Rules

#### Settings
- Priority=Major


## FB_BBOA
### Default
#### OriginalId=BOA_BADLY_OVERRIDDEN_ADAPTER
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Badly Overridden Adapter
#### WarningText
  Class {0} overrides a method {1} implemented in super class Adapter wrongly

#### HelpText
  This method overrides a method found in a parent class, where that class is an Adapter that implements a listener defined in the java.awt.event or javax.swing.event package. As a result, this method will not get called when the event occurs.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_BC
### Default
#### OriginalId=FE_TEST_IF_EQUAL_TO_NOT_A_NUMBER
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Test If Equal To Not A Number
#### WarningText
  Doomed test for equality to NaN in {1}

#### HelpText
  This code checks to see if a floating point value is equal to the special Not A Number value (e.g., `if (x == Double.NaN)`). However, because of the special semantics of `NaN`, no value is equal to `Nan`, including `NaN`. Thus, `x == Double.NaN` always evaluates to false. To check to see if a value contained in `x` is the special Not A Number value, use `Double.isNaN(x)` (or `Float.isNaN(x)` if `x` is floating point precision).


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_BEMSWFAO
### Default
#### OriginalId=BC_EQUALS_METHOD_SHOULD_WORK_FOR_ALL_OBJECTS
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Equals Method Should Work For All Objects
#### WarningText
  Equals method for {0} assumes the argument is of type {0.givenClass}

#### HelpText
  The `equals(Object o)` method shouldn’t make any assumptions about the type of `o`. It should simply return false if `o` is not the same type as `this`.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_BIC
### Default
#### OriginalId=BC_IMPOSSIBLE_CAST
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Impossible Cast
#### WarningText
  Impossible cast from {2} to {3} in {1}

#### HelpText
  This cast will always throw a ClassCastException. SpotBugs tracks type information from instanceof checks, and also uses more precise information about the types of values returned from methods and loaded from fields. Thus, it may have more precise information that just the declared type of a variable, and can use this to determine that a cast will always throw an exception at runtime.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Critical


## FB_BID
### Default
#### OriginalId=BC_IMPOSSIBLE_DOWNCAST
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Impossible Downcast
#### WarningText
  Impossible downcast from {2} to {3} in {1}

#### HelpText
  This cast will always throw a ClassCastException. The analysis believes it knows the precise type of the value being cast, and the attempt to downcast it to a subtype will always fail by throwing a ClassCastException.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Critical


## FB_BIOSB
### Default
#### OriginalId=BIT_IOR_OF_SIGNED_BYTE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Ior Of Signed Byte
#### WarningText
  Bitwise OR of signed byte value computed in {1}

#### HelpText
  Loads a byte value (e.g., a value loaded from a byte array or returned by a method with return type byte) and performs a bitwise OR with that value. Byte values are sign extended to 32 bits before any bitwise operations are performed on the value. Thus, if `b[0]` contains the value `0xff`, and `x` is initially 0, then the code `((x << 8) | b[0])` will sign extend `0xff` to get `0xffffffff`, and thus give the value `0xffffffff` as the result.

  In particular, the following code for packing a byte array into an int is badly wrong:

  ``` java
  int result = 0;
  for(int i = 0; i < 4; i++) {
      result = ((result << 8) | b[i]);
  }
  ```

  The following idiom will work instead:

  ``` java
  int result = 0;
  for(int i = 0; i < 4; i++) {
      result = ((result << 8) | (b[i] & 0xff));
  }
  ```


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_BSC
### Default
#### OriginalId=BIT_SIGNED_CHECK
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Signed Check
#### WarningText
  Check for sign of bitwise operation in {1}

#### HelpText
  This method compares an expression such as `((event.detail & SWT.SELECTED) > 0)`. Using bit arithmetic and then comparing with the greater than operator can lead to unexpected results (of course depending on the value of SWT.SELECTED). If SWT.SELECTED is a negative number, this is a candidate for a bug. Even when SWT.SELECTED is not negative, it seems good practice to use ‘!= 0’ instead of ‘&gt; 0’.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_BSCHB
### Default
#### OriginalId=BIT_SIGNED_CHECK_HIGH_BIT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Signed Check High Bit
#### WarningText
  Check for sign of bitwise operation involving {2} in {1}

#### HelpText
  This method compares a bitwise expression such as `((val & CONSTANT) > 0)` where CONSTANT is the negative number. Using bit arithmetic and then comparing with the greater than operator can lead to unexpected results. This comparison is unlikely to work as expected. The good practice is to use ‘!= 0’ instead of ‘&gt; 0’.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_BUACFTO
### Default
#### OriginalId=BX_UNBOXED_AND_COERCED_FOR_TERNARY_OPERATOR
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unboxed And Coerced For Ternary Operator
#### WarningText
  Primitive value is unboxed and coerced for ternary operator in {1}

#### HelpText
  A wrapped primitive value is unboxed and converted to another primitive type as part of the evaluation of a conditional ternary operator (the `b ? e1 : e2` operator). The semantics of Java mandate that if `e1` and `e2` are wrapped numeric values, the values are unboxed and converted/coerced to their common type (e.g, if `e1` is of type `Integer` and `e2` is of type `Float`, then `e1` is unboxed, converted to a floating point value, and boxed. See JLS Section 15.25.


#### Tags
- /tool/FindBugs
- /general/Optimization Rules

#### Settings
- Priority=Major


## FB_BUC
### Default
#### OriginalId=BC_UNCONFIRMED_CAST
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unconfirmed Cast
#### WarningText
  Unchecked/unconfirmed cast from {2} to {3} in {1}

#### HelpText
  This cast is unchecked, and not all instances of the type casted from can be cast to the type it is being cast to. Check that your program logic ensures that this cast will not fail.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_BUCORV
### Default
#### OriginalId=BC_UNCONFIRMED_CAST_OF_RETURN_VALUE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unconfirmed Cast Of Return Value
#### WarningText
  Unchecked/unconfirmed cast from {2} to {3} of return value in {1}

#### HelpText
  This code performs an unchecked cast of the return value of a method. The code might be calling the method in such a way that the cast is guaranteed to be safe, but SpotBugs is unable to verify that the cast is safe. Check that your program logic ensures that this cast will not fail.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_BUIR
### Default
#### OriginalId=BX_UNBOXING_IMMEDIATELY_REBOXED
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unboxing Immediately Reboxed
#### WarningText
  Boxed value is unboxed and then immediately reboxed in {1}

#### HelpText
  A boxed value is unboxed and then immediately reboxed.


#### Tags
- /tool/FindBugs
- /general/Optimization Rules

#### Settings
- Priority=Major


## FB_BVI
### Default
#### OriginalId=BC_VACUOUS_INSTANCEOF
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Vacuous Instanceof
#### WarningText
  instanceof will always return true for all non-null values in {1}, since all {2} are instances of {3}

#### HelpText
  This instanceof test will always return true (unless the value being tested is null). Although this is safe, make sure it isn’t an indication of some misunderstanding or some other logic error. If you really want to test the value for being null, perhaps it would be clearer to do better to do a null test rather than an instanceof test.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_BWAP
### Default
#### OriginalId=BSHIFT_WRONG_ADD_PRIORITY
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Wrong Add Priority
#### WarningText
  Possible bad parsing of shift operation in {1}

#### HelpText
  The code performs an operation like (x &lt;&lt; 8 + y). Although this might be correct, probably it was meant to perform (x &lt;&lt; 8) + y, but shift operation has a lower precedence, so it’s actually parsed as x &lt;&lt; (8 + y).


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_BcII
### Default
#### OriginalId=BC_IMPOSSIBLE_INSTANCEOF
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Impossible Instanceof
#### WarningText
  instanceof will always return false in {1}, since a {2} can't be a {3}

#### HelpText
  This instanceof test will always return false. Although this is safe, make sure it isn’t an indication of some misunderstanding or some other logic error.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Critical


## FB_BiI
### Default
#### OriginalId=BIT_IOR
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Ior
#### WarningText
  Incompatible bit masks in (e | {2} == {3}) yields constant result in {1}

#### HelpText
  This method compares an expression of the form `(e | C)` to D. which will always compare unequal due to the specific values of constants C and D. This may indicate a logic error or typo.

  Typically, this bug occurs because the code wants to perform a membership test in a bit set, but uses the bitwise OR operator (“|”) instead of bitwise AND (“&”).

  Also such bug may appear in expressions like `(e & A | B) == C` which is parsed like `((e & A) | B) == C` while `(e & (A | B)) == C` was intended.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_CAS
### Default
#### OriginalId=CO_ABSTRACT_SELF
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Abstract Self
#### WarningText
  Abstract {0} defines compareTo({0.givenClass}) method

#### HelpText
  This class defines a covariant version of \`compareTo()\`.  To correctly override the \`compareTo()\` method in the \`Comparable\` interface, the parameter of \`compareTo()\` must have type \`java.lang.Object\`.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_CCAES
### Default
#### OriginalId=CAA_COVARIANT_ARRAY_ELEMENT_STORE
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=Covariant Array Element Store
#### WarningText
  Value of type {2} is stored into array which element type is {3}

#### HelpText
  Value is stored into the array and the value type doesn't match the array type. It's known from the analysis that actual array type is narrower than the declared type of its variable or field and this assignment doesn't satisfy the original array type. This assignment may cause ArrayStoreException at runtime.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_CCAF
### Default
#### OriginalId=CAA_COVARIANT_ARRAY_FIELD
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=Covariant Array Field
#### WarningText
  Array of type {2} is assigned to the field of type {3}

#### HelpText
  Array of covariant type is assigned to a field. This is confusing and may lead to ArrayStoreException at runtime if the reference of some other type will be stored in this array later like in the following code: \`\`\` {.java} Number\[\] arr = new Integer\[10\]; arr\[0\] = 1.0; \`\`\` Consider changing the type of created array or the field type.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_CCAL
### Default
#### OriginalId=CAA_COVARIANT_ARRAY_LOCAL
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=Covariant Array Local
#### WarningText
  Array of type {2} is assigned to the variable of type {3}

#### HelpText
  Array of covariant type is assigned to a local variable. This is confusing and may lead to ArrayStoreException at runtime if the reference of some other type will be stored in this array later like in the following code: \`\`\` {.java} Number\[\] arr = new Integer\[10\]; arr\[0\] = 1.0; \`\`\` Consider changing the type of created array or the local variable type.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_CCAR
### Default
#### OriginalId=CAA_COVARIANT_ARRAY_RETURN
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=Covariant Array Return
#### WarningText
  Array of type {2} is returned from the method which return type is {3}

#### HelpText
  Array of covariant type is returned from the method. This is confusing and may lead to ArrayStoreException at runtime if the calling code will try to store the reference of some other type in the returned array. Consider changing the type of created array or the method return type.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_CCD
### Default
#### OriginalId=CD_CIRCULAR_DEPENDENCY
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=Circular Dependency
#### WarningText
  Class {0} has a circular dependency with other classes

#### HelpText
  This class has a circular dependency with other classes. This makes building these classes difficult, as each is dependent on the other to build correctly. Consider using interfaces to break the hard dependency.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_CCEWTA
### Default
#### OriginalId=BC_IMPOSSIBLE_DOWNCAST_OF_TOARRAY
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Impossible Downcast Of Toarray
#### WarningText
  Impossible downcast of toArray() result to {3} in {1}

#### HelpText
  This code is casting the result of calling `toArray()` on a collection to a type more specific than `Object[]`, as in:

  ``` java
  String[] getAsArray(Collection<String> c) {
      return (String[]) c.toArray();
  }
  ```

  This will usually fail by throwing a ClassCastException. The `toArray()` of almost all collections return an `Object[]`. They can’t really do anything else, since the Collection object has no reference to the declared generic type of the collection.

  The correct way to do get an array of a specific type from a collection is to use `c.toArray(new String[]);` or `c.toArray(new String[c.size()]);` (the latter is slightly more efficient).

  There is one common/known exception to this. The `toArray()` method of lists returned by `Arrays.asList(...)` will return a covariantly typed array. For example, `Arrays.asArray(new String[] { "a" }).toArray()` will return a `String []`. SpotBugs attempts to detect and suppress such cases, but may miss some.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Critical


## FB_CCIF
### Default
#### OriginalId=CO_COMPARETO_INCORRECT_FLOATING
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Compareto Incorrect Floating
#### WarningText
  {1} incorrectly handles {2} value

#### HelpText
  This method compares double or float values using pattern like this: val1 &gt; val2 ? 1 : val1 &lt; val2 ? -1 : 0. This pattern works incorrectly for -0.0 and NaN values which may result in incorrect sorting result or broken collection (if compared values are used as keys). Consider using Double.compare or Float.compare static methods which handle all the special cases correctly.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_CCRMV
### Default
#### OriginalId=CO_COMPARETO_RESULTS_MIN_VALUE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Compareto Results Min Value
#### WarningText
  {1} returns Integer.MIN_VALUE, which can't be negated

#### HelpText
  In some situation, this compareTo or compare method returns the constant Integer.MIN\_VALUE, which is an exceptionally bad practice. The only thing that matters about the return value of compareTo is the sign of the result. But people will sometimes negate the return value of compareTo, expecting that this will negate the sign of the result. And it will, except in the case where the value returned is Integer.MIN\_VALUE. So just return -1 rather than Integer.MIN\_VALUE.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_CICBNC
### Default
#### OriginalId=CN_IMPLEMENTS_CLONE_BUT_NOT_CLONEABLE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Implements Clone But Not Cloneable
#### WarningText
  {0} defines clone() but doesn't implement Cloneable

#### HelpText
  This class defines a clone() method but the class doesn’t implement Cloneable. There are some situations in which this is OK (e.g., you want to control how subclasses can clone themselves), but just make sure that this is what you intended.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_CNC
### Default
#### OriginalId=NM_CLASS_NAMING_CONVENTION
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Class Naming Convention
#### WarningText
  The class name {0} doesn't start with an upper case letter

#### HelpText
  Class names should be nouns, in mixed case with the first letter of each internal word capitalized. Try to keep your class names simple and descriptive. Use whole words-avoid acronyms and abbreviations (unless the abbreviation is much more widely used than the long form, such as URL or HTML).


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_CRCV
### Default
#### OriginalId=CNT_ROUGH_CONSTANT_VALUE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Rough Constant Value
#### WarningText
  Rough value of {3} found: {2}

#### HelpText
  It’s recommended to use the predefined library constant for code clarity and better precision.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_CSNO
### Default
#### OriginalId=CO_SELF_NO_OBJECT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Self No Object
#### WarningText
  {0} defines compareTo({0.givenClass}) method but not compareTo(Object)

#### HelpText
  This class defines a covariant version of \`compareTo()\`.  To correctly override the \`compareTo()\` method in the \`Comparable\` interface, the parameter of \`compareTo()\` must have type \`java.lang.Object\`.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_ClMMIC
### Default
#### OriginalId=CN_IDIOM
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Idiom
#### WarningText
  Class {0} implements Cloneable but does not define or use clone method

#### HelpText
  Class implements Cloneable but does not define or use the clone method.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_DAINVTR
### Default
#### OriginalId=DMI_ANNOTATION_IS_NOT_VISIBLE_TO_REFLECTION
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Annotation Is Not Visible To Reflection
#### WarningText
  Use of reflection to check for the presence the annotation {3} which doesn't have runtime retention, in {1}

#### HelpText
  Unless an annotation has itself been annotated with <span class="citation" data-cites="Retention">@Retention</span>(RetentionPolicy.RUNTIME), the annotation can’t be observed using reflection (e.g., by using the isAnnotationPresent method). .


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_DAWO
### Default
#### OriginalId=DMI_ARGUMENTS_WRONG_ORDER
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Arguments Wrong Order
#### WarningText
  Arguments in wrong order for invocation of {2.name} in {1}

#### HelpText
  The arguments to this method call seem to be in the wrong order. For example, a call `Preconditions.checkNotNull("message", message)` has reserved arguments: the value to be checked is the first argument.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_DBC
### Default
#### OriginalId=DM_BOOLEAN_CTOR
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Boolean Ctor
#### WarningText
  {1} invokes inefficient Boolean constructor; use Boolean.valueOf(...) instead

#### HelpText
  Creating new instances of `java.lang.Boolean` wastes memory, since `Boolean` objects are immutable and there are only two useful values of this type.  Use the `Boolean.valueOf()` method (or Java 1.5 autoboxing) to create `Boolean` objects instead.


#### Tags
- /tool/FindBugs
- /general/Optimization Rules

#### Settings
- Priority=Major


## FB_DBM
### Default
#### OriginalId=DMI_BAD_MONTH
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Month
#### WarningText
  Bad month value of {2} passed to {3} in {1}

#### HelpText
  This code passes a constant month value outside the expected range of 0..11 to a method.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_DBMOU
### Default
#### OriginalId=DMI_BLOCKING_METHODS_ON_URL
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Blocking Methods On Url
#### WarningText
  Invocation of {2}, which blocks to do domain name resolution, in {1}

#### HelpText
  The equals and hashCode method of URL perform domain name resolution, this can result in a big performance hit. See <a href="http://michaelscharf.blogspot.com/2006/11/javaneturlequals-and-hashcode-make.html" class="uri" class="uri">http://michaelscharf.blogspot.com/2006/11/javaneturlequals-and-hashcode-make.html</a> for more information. Consider using `java.net.URI` instead.


#### Tags
- /tool/FindBugs
- /general/Optimization Rules

#### Settings
- Priority=Major


## FB_DBPFC
### Default
#### OriginalId=DM_BOXED_PRIMITIVE_FOR_COMPARE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Boxed Primitive For Compare
#### WarningText
  Primitive is boxed to call {2}: use {3} instead

#### HelpText
  A boxed primitive is created just to call compareTo method. It’s more efficient to use static compare method (for double and float since Java 1.4, for other primitive types since Java 1.7) which works on primitives directly.


#### Tags
- /tool/FindBugs
- /general/Optimization Rules

#### Settings
- Priority=Major


## FB_DBPFP
### Default
#### OriginalId=DM_BOXED_PRIMITIVE_FOR_PARSING
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Boxed Primitive For Parsing
#### WarningText
  Boxing/unboxing to parse a primitive {1}

#### HelpText
  A boxed primitive is created from a String, just to extract the unboxed primitive value. It is more efficient to just call the static parseXXX method.


#### Tags
- /tool/FindBugs
- /general/Optimization Rules

#### Settings
- Priority=Major


## FB_DBPT
### Default
#### OriginalId=DM_BOXED_PRIMITIVE_TOSTRING
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Boxed Primitive Tostring
#### WarningText
  Primitive boxed just to call toString in {1}

#### HelpText
  A boxed primitive is allocated just to call toString(). It is more effective to just use the static form of toString which takes the primitive value. So,

  | Replace…                     | With this…             |
  |------------------------------|------------------------|
  | new Integer(1).toString()    | Integer.toString(1)    |
  | new Long(1).toString()       | Long.toString(1)       |
  | new Float(1.0).toString()    | Float.toString(1.0)    |
  | new Double(1.0).toString()   | Double.toString(1.0)   |
  | new Byte(1).toString()       | Byte.toString(1)       |
  | new Short(1).toString()      | Short.toString(1)      |
  | new Boolean(true).toString() | Boolean.toString(true) |




#### Tags
- /tool/FindBugs
- /general/Optimization Rules

#### Settings
- Priority=Major


## FB_DCCIDP
### Default
#### OriginalId=DP_CREATE_CLASSLOADER_INSIDE_DO_PRIVILEGED
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Create Classloader Inside Do Privileged
#### WarningText
  {1} creates a {2} classloader, which should be performed within a doPrivileged block

#### HelpText
  This code creates a classloader, which needs permission if a security manage is installed. If this code might be invoked by code that does not have security permissions, then the classloader creation needs to occur inside a doPrivileged block.


#### Tags
- /tool/FindBugs
- /general/Security Code Guideline Rules
- /collection/SEI CERT/SEC03-J

#### Settings
- Priority=Info


## FB_DCDP
### Default
#### OriginalId=DMI_CONSTANT_DB_PASSWORD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Constant Db Password
#### WarningText
  Hardcoded constant database password in {1}

#### HelpText
  This code creates a database connect using a hardcoded, constant password. Anyone with access to either the source code or the compiled code can easily learn the password.


#### Tags
- /tool/FindBugs
- /general/Vulnerability Rules
- /collection/SEI CERT/MSC03-J
- /collection/CWE/259
- /collection/CWE/798
- /collection/CWE/547
- /collection/OWASP/A05:2021

#### Settings
- Priority=Major


## FB_DCL
### Default
#### OriginalId=DC_DOUBLECHECK
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Doublecheck
#### WarningText
  Possible doublecheck on {2} in {1}

#### HelpText
  This method may contain an instance of double-checked locking.  This idiom is not correct according to the semantics of the Java memory model.  For more information, see the web page <a href="http://www.cs.umd.edu/~pugh/java/memoryModel/DoubleCheckedLocking.html" class="uri" class="uri">http://www.cs.umd.edu/~pugh/java/memoryModel/DoubleCheckedLocking.html</a>.


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_DCNFH
### Default
#### OriginalId=DMI_CALLING_NEXT_FROM_HASNEXT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Calling Next From Hasnext
#### WarningText
  {1} invokes {2.givenClass}

#### HelpText
  The hasNext() method invokes the next() method. This is almost certainly wrong, since the hasNext() method is not supposed to change the state of the iterator, and the next method is supposed to change the state of the iterator.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_DCOU
### Default
#### OriginalId=DMI_COLLECTION_OF_URLS
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Collection Of Urls
#### WarningText
  {1} is or uses a map or set of URLs, which can be a performance hog

#### HelpText
  This method or field is or uses a Map or Set of URLs. Since both the equals and hashCode method of URL perform domain name resolution, this can result in a big performance hit. See <a href="http://michaelscharf.blogspot.com/2006/11/javaneturlequals-and-hashcode-make.html" class="uri" class="uri">http://michaelscharf.blogspot.com/2006/11/javaneturlequals-and-hashcode-make.html</a> for more information. Consider using `java.net.URI` instead.


#### Tags
- /tool/FindBugs
- /general/Optimization Rules

#### Settings
- Priority=Major


## FB_DCSNCT
### Default
#### OriginalId=DMI_COLLECTIONS_SHOULD_NOT_CONTAIN_THEMSELVES
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Collections Should Not Contain Themselves
#### WarningText
  Collections should not contain themselves in call to {2.givenClass}

#### HelpText
  This call to a generic collection’s method would only make sense if a collection contained itself (e.g., if `s.contains(s)` were true). This is unlikely to be true and would cause problems if it were true (such as the computation of the hash code resulting in infinite recursion). It is likely that the wrong value is being passed as a parameter.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_DCTR
### Default
#### OriginalId=RU_INVOKE_RUN
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Invoke Run
#### WarningText
  {1} explicitly invokes run on a thread (did you mean to start it instead?)

#### HelpText
  This method explicitly invokes `run()` on an object.  In general, classes implement the `Runnable` interface because they are going to have their `run()` method invoked in a new thread, in which case `Thread.start()` is the right method to call.


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_DDB
### Default
#### OriginalId=DB_DUPLICATE_BRANCHES
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Duplicate Branches
#### WarningText
  {1} uses the same code for two branches

#### HelpText
  This method uses the same code to implement two branches of a conditional branch. Check to ensure that this isn’t a coding mistake.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_DDE
### Default
#### OriginalId=DM_DEFAULT_ENCODING
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Default Encoding
#### WarningText
  Found reliance on default encoding in {1}: {2}

#### HelpText
  Found a call to a method which will perform a byte to String (or String to byte) conversion, and will assume that the default platform encoding is suitable. This will cause the application behaviour to vary between platforms. Use an alternative API and specify a charset name or Charset object explicitly.


#### Tags
- /tool/FindBugs
- /general/Internationalization Rules

#### Settings
- Priority=Info


## FB_DDIDP
### Default
#### OriginalId=DP_DO_INSIDE_DO_PRIVILEGED
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Do Inside Do Privileged
#### WarningText
  Invocation of {2}, which should be invoked from within a doPrivileged block, in {1}

#### HelpText
  This code invokes a method that requires a security permission check. If this code will be granted security permissions, but might be invoked by code that does not have security permissions, then the invocation needs to occur inside a doPrivileged block.


#### Tags
- /tool/FindBugs
- /general/Security Code Guideline Rules
- /collection/SEI CERT/SEC52-J
- /collection/SEI CERT/SEC00-J
- /collection/CWE/266

#### Settings
- Priority=Info


## FB_DDLS
### Default
#### OriginalId=DLS_DEAD_LOCAL_STORE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Dead Local Store
#### WarningText
  Dead store to {2} in {1}

#### HelpText
  This instruction assigns a value to a local variable, but the value is not read or used in any subsequent instruction. Often, this indicates an error, because the value computed is never used.

  Note that Sun’s javac compiler often generates dead stores for final local variables. Because SpotBugs is a bytecode-based tool, there is no easy way to eliminate these false positives.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_DDLSIR
### Default
#### OriginalId=DLS_DEAD_LOCAL_STORE_IN_RETURN
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Dead Local Store In Return
#### WarningText
  Useless assignment in return from {1}

#### HelpText
  This statement assigns to a local variable in a return statement. This assignment has effect. Please verify that this statement does the right thing.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_DDLSON
### Default
#### OriginalId=DLS_DEAD_LOCAL_STORE_OF_NULL
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Dead Local Store Of Null
#### WarningText
  Dead store of null to {2} in {1}

#### HelpText
  The code stores null into a local variable, and the stored value is not read. This store may have been introduced to assist the garbage collector, but as of Java SE 6.0, this is no longer needed or useful.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_DDLSSF
### Default
#### OriginalId=DLS_DEAD_LOCAL_STORE_SHADOWS_FIELD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Dead Local Store Shadows Field
#### WarningText
  Dead store to {2} rather than field with same name in {1}

#### HelpText
  This instruction assigns a value to a local variable, but the value is not read or used in any subsequent instruction. Often, this indicates an error, because the value computed is never used. There is a field with the same name as the local variable. Did you mean to assign to that variable instead?


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_DDSC
### Default
#### OriginalId=DB_DUPLICATE_SWITCH_CLAUSES
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Duplicate Switch Clauses
#### WarningText
  {1} uses the same code for two switch clauses

#### HelpText
  This method uses the same code to implement two clauses of a switch statement. This could be a case of duplicate code, but it might also indicate a coding mistake.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_DDSOCL
### Default
#### OriginalId=DLS_DEAD_STORE_OF_CLASS_LITERAL
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Dead Store Of Class Literal
#### WarningText
  Dead store of {3}.class in {1}

#### HelpText
  This instruction assigns a class literal to a variable and then never uses it. [The behavior of this differs in Java 1.4 and in Java 5.](http://www.oracle.com/technetwork/java/javase/compatibility-137462.html#literal) In Java 1.4 and earlier, a reference to `Foo.class` would force the static initializer for `Foo` to be executed, if it has not been executed already. In Java 5 and later, it does not.

  See Sun’s [article on Java SE compatibility](http://www.oracle.com/technetwork/java/javase/compatibility-137462.html#literal) for more details and examples, and suggestions on how to force class initialization in Java 5.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_DEDP
### Default
#### OriginalId=DMI_EMPTY_DB_PASSWORD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Empty Db Password
#### WarningText
  Empty database password in {1}

#### HelpText
  This code creates a database connect using a blank or empty password. This indicates that the database is not protected by a password.


#### Tags
- /tool/FindBugs
- /general/Vulnerability Rules
- /collection/CWE/256
- /collection/CWE/258
- /collection/CWE/522
- /collection/OWASP/A04:2021

#### Settings
- Priority=Major


## FB_DESMREO
### Default
#### OriginalId=DMI_ENTRY_SETS_MAY_REUSE_ENTRY_OBJECTS
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Entry Sets May Reuse Entry Objects
#### WarningText
  Adding elements of an entry set may fail due to reuse of {2.simpleClass}.Entry object in {1}

#### HelpText
  The entrySet() method is allowed to return a view of the underlying Map in which a single Entry object is reused and returned during the iteration. As of Java 1.6, both IdentityHashMap and EnumMap did so. When iterating through such a Map, the Entry value is only valid until you advance to the next iteration. If, for example, you try to pass such an entrySet to an addAll method, things will go badly wrong.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_DFATCMSOSTPE
### Default
#### OriginalId=DMI_FUTILE_ATTEMPT_TO_CHANGE_MAXPOOL_SIZE_OF_SCHEDULED_THREAD_POOL_EXECUTOR
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Futile Attempt To Change Maxpool Size Of Scheduled Thread Pool Executor
#### WarningText
  Futile attempt to change max pool size of ScheduledThreadPoolExecutor in {1}

#### HelpText
  ([Javadoc](http://docs.oracle.com/javase/6/docs/api/java/util/concurrent/ScheduledThreadPoolExecutor.html)) While ScheduledThreadPoolExecutor inherits from ThreadPoolExecutor, a few of the inherited tuning methods are not useful for it. In particular, because it acts as a fixed-sized pool using corePoolSize threads and an unbounded queue, adjustments to maximumPoolSize have no useful effect.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_DFNC
### Default
#### OriginalId=DM_FP_NUMBER_CTOR
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Fp Number Ctor
#### WarningText
  {1} invokes inefficient {2} constructor; use {3} instead

#### HelpText
  Using `new Double(double)` is guaranteed to always result in a new object whereas `Double.valueOf(double)` allows caching of values to be done by the compiler, class library, or JVM. Using of cached values avoids object allocation and the code will be faster.

  Unless the class must be compatible with JVMs predating Java 1.5, use either autoboxing or the `valueOf()` method when creating instances of `Double` and `Float`.


#### Tags
- /tool/FindBugs
- /general/Optimization Rules

#### Settings
- Priority=Major


## FB_DHAF
### Default
#### OriginalId=DMI_HARDCODED_ABSOLUTE_FILENAME
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Hardcoded Absolute Filename
#### WarningText
  Hard coded reference to an absolute pathname in {1}

#### HelpText
  This code constructs a File object using a hard coded to an absolute pathname (e.g., `new File("/home/dannyc/workspace/j2ee/src/share/com/sun/enterprise/deployment");`


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_DIHOA
### Default
#### OriginalId=DMI_INVOKING_HASHCODE_ON_ARRAY
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Invoking Hashcode On Array
#### WarningText
  Invocation of hashCode on array in {1}

#### HelpText
  The code invokes hashCode on an array. Calling hashCode on an array returns the same value as System.identityHashCode, and ignores the contents and length of the array. If you need a hashCode that depends on the contents of an array `a`, use `java.util.Arrays.hashCode(a)`.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_DIMM
### Default
#### OriginalId=DM_INVALID_MIN_MAX
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Invalid Min Max
#### WarningText
  Incorrect combination of Math.max and Math.min: this code always returns {2}

#### HelpText
  This code tries to limit the value bounds using the construct like Math.min(0, Math.max(100, value)). However the order of the constants is incorrect: it should be Math.min(100, Math.max(0, value)). As the result this code always produces the same result (or NaN if the value is NaN).


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_DITOA
### Default
#### OriginalId=DMI_INVOKING_TOSTRING_ON_ARRAY
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Invoking Tostring On Array
#### WarningText
  Invocation of toString on {2.givenClass} in {1}

#### HelpText
  The code invokes toString on an array, which will generate a fairly useless result such as \[C@16f0472. Consider using Arrays.toString to convert the array into a readable String that gives the contents of the array. See Programming Puzzlers, chapter 3, puzzle 12.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_DITOAA
### Default
#### OriginalId=DMI_INVOKING_TOSTRING_ON_ANONYMOUS_ARRAY
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Invoking Tostring On Anonymous Array
#### WarningText
  Invocation of toString on an unnamed array in {1}

#### HelpText
  The code invokes toString on an (anonymous) array. Calling toString on an array generates a fairly useless result such as \[C@16f0472. Consider using Arrays.toString to convert the array into a readable String that gives the contents of the array. See Programming Puzzlers, chapter 3, puzzle 12.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_DLBTDIOI
### Default
#### OriginalId=DMI_LONG_BITS_TO_DOUBLE_INVOKED_ON_INT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Long Bits To Double Invoked On Int
#### WarningText
  Double.longBitsToDouble invoked on an int in {1}

#### HelpText
  The Double.longBitsToDouble method is invoked, but a 32 bit int value is passed as an argument. This almost certainly is not intended and is unlikely to give the intended result.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_DLNLISS
### Default
#### OriginalId=SF_SWITCH_NO_DEFAULT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Switch No Default
#### WarningText
  Switch statement found in {1} where default case is missing

#### HelpText
  This method contains a switch statement where default case is missing. Usually you need to provide a default case.

  Because the analysis only looks at the generated bytecode, this warning can be incorrect triggered if the default case is at the end of the switch statement and the switch statement doesn’t contain break statements for other cases.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_DMD
### Default
#### OriginalId=DE_MIGHT_DROP
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Might Drop
#### WarningText
  {1} might drop {2}

#### HelpText
  This method might drop an exception.  In general, exceptions should be handled or reported in some way, or they should be thrown out of the method.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_DMI
### Default
#### OriginalId=DE_MIGHT_IGNORE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Might Ignore
#### WarningText
  {1} might ignore {2}

#### HelpText
  This method might ignore an exception.  In general, exceptions should be handled or reported in some way, or they should be thrown out of the method.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_DMWOC
### Default
#### OriginalId=DM_MONITOR_WAIT_ON_CONDITION
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Monitor Wait On Condition
#### WarningText
  Monitor wait() called on a Condition in {1}

#### HelpText
  This method calls `wait()` on a `java.util.concurrent.locks.Condition` object.  Waiting for a `Condition` should be done using one of the `await()` methods defined by the `Condition` interface.


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_DNCGCE
### Default
#### OriginalId=DM_GC
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Gc
#### WarningText
  {1} forces garbage collection; extremely dubious except in benchmarking code

#### HelpText
  Code explicitly invokes garbage collection. Except for specific use in benchmarking, this is very dubious.

  In the past, situations where people have explicitly invoked the garbage collector in routines such as close or finalize methods has led to huge performance black holes. Garbage collection can be expensive. Any situation that forces hundreds or thousands of garbage collections will bring the machine to a crawl.


#### Tags
- /tool/FindBugs
- /general/Optimization Rules

#### Settings
- Priority=Major


## FB_DNCSE
### Default
#### OriginalId=DM_EXIT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Exit
#### WarningText
  {1} invokes System.exit(...), which shuts down the entire virtual machine

#### HelpText
  Invoking System.exit shuts down the entire Java virtual machine. This should only been done when it is appropriate. Such calls make it hard or impossible for your code to be invoked by other code. Consider throwing a RuntimeException instead.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_DNOW
### Default
#### OriginalId=DMI_NONSERIALIZABLE_OBJECT_WRITTEN
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Nonserializable Object Written
#### WarningText
  Non serializable {2} written to ObjectOutput in {1}

#### HelpText
  This code seems to be passing a non-serializable object to the ObjectOutput.writeObject method. If the object is, indeed, non-serializable, an error will result.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_DNUT
### Default
#### OriginalId=DMI_THREAD_PASSED_WHERE_RUNNABLE_EXPECTED
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Thread Passed Where Runnable Expected
#### WarningText
  Thread passed where Runnable expected in {1}

#### HelpText
  A Thread object is passed as a parameter to a method where a Runnable is expected. This is rather unusual, and may indicate a logic error or cause unexpected behavior.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_DNVN
### Default
#### OriginalId=DM_NEXTINT_VIA_NEXTDOUBLE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Nextint Via Nextdouble
#### WarningText
  {1} uses the nextDouble method of Random to generate a random integer; using nextInt is more efficient

#### HelpText
  If `r` is a `java.util.Random`, you can generate a random number from `0` to `n-1` using `r.nextInt(n)`, rather than using `(int)(r.nextDouble() * n)`.

  The argument to nextInt must be positive. If, for example, you want to generate a random value from -99 to 0, use `-r.nextInt(100)`.


#### Tags
- /tool/FindBugs
- /general/Optimization Rules

#### Settings
- Priority=Major


## FB_DOI
### Default
#### OriginalId=DLS_OVERWRITTEN_INCREMENT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Overwritten Increment
#### WarningText
  Overwritten increment in {1}

#### HelpText
  The code performs an increment operation (e.g., `i++`) and then immediately overwrites it. For example, `i = i++` immediately overwrites the incremented value with the original value.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_DPC
### Default
#### OriginalId=DC_PARTIALLY_CONSTRUCTED
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Partially Constructed
#### WarningText
  Possible exposure of partially initialized object in {1}

#### HelpText
  Looks like this method uses lazy field initialization with double-checked locking. While the field is correctly declared as volatile, it’s possible that the internal structure of the object is changed after the field assignment, thus another thread may see the partially initialized object.

  To fix this problem consider storing the object into the local variable first and save it to the volatile field only after it’s fully constructed.


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_DRFOE
### Default
#### OriginalId=DM_RUN_FINALIZERS_ON_EXIT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Run Finalizers On Exit
#### WarningText
  {1} invokes dangerous method runFinalizersOnExit

#### HelpText
  *Never call System.runFinalizersOnExit or Runtime.runFinalizersOnExit for any reason: they are among the most dangerous methods in the Java libraries.* – Joshua Bloch


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_DRUOO
### Default
#### OriginalId=DMI_RANDOM_USED_ONLY_ONCE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Random Used Only Once
#### WarningText
  Random object created and used only once in {1}

#### HelpText
  This code creates a java.util.Random object, uses it to generate one random number, and then discards the Random object. This produces mediocre quality random numbers and is inefficient. If possible, rewrite the code so that the Random object is created once and saved, and each time a new random number is required invoke a method on the existing Random object to obtain it.

  If it is important that the generated Random numbers not be guessable, you *must* not create a new Random for each random number; the values are too easily guessable. You should strongly consider using a java.security.SecureRandom instead (and avoid allocating a new SecureRandom for each random number needed).


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_DSC
### Default
#### OriginalId=DM_STRING_CTOR
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=String Ctor
#### WarningText
  {1} invokes inefficient new String(String) constructor

#### HelpText
  Using the `java.lang.String(String)` constructor wastes memory because the object so constructed will be functionally indistinguishable from the `String` passed as a parameter.  Just use the argument `String` directly.


#### Tags
- /tool/FindBugs
- /general/Optimization Rules

#### Settings
- Priority=Major


## FB_DSOB
### Default
#### OriginalId=DL_SYNCHRONIZATION_ON_BOOLEAN
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Synchronization On Boolean
#### WarningText
  Synchronization on Boolean in {1}

#### HelpText
  The code synchronizes on a boxed primitive constant, such as a Boolean.

  ``` java
  private static Boolean inited = Boolean.FALSE;
  ...
  synchronized(inited) {
      if (!inited) {
          init();
          inited = Boolean.TRUE;
      }
  }
  ...
  ```

  Since there normally exist only two Boolean objects, this code could be synchronizing on the same object as other, unrelated code, leading to unresponsiveness and possible deadlock.

  See CERT [CON08-J. Do not synchronize on objects that may be reused](https://www.securecoding.cert.org/confluence/display/java/CON08-J.+Do+not+synchronize+on+objects+that+may+be+reused) for more information.


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_DSOBP
### Default
#### OriginalId=DL_SYNCHRONIZATION_ON_BOXED_PRIMITIVE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Synchronization On Boxed Primitive
#### WarningText
  Synchronization on {2} in {1}

#### HelpText
  The code synchronizes on a boxed primitive constant, such as an Integer.

  ``` java
  private static Integer count = 0;
  ...
  synchronized(count) {
      count++;
  }
  ...
  ```

  Since Integer objects can be cached and shared, this code could be synchronizing on the same object as other, unrelated code, leading to unresponsiveness and possible deadlock.

  See CERT [CON08-J. Do not synchronize on objects that may be reused](https://www.securecoding.cert.org/confluence/display/java/CON08-J.+Do+not+synchronize+on+objects+that+may+be+reused) for more information.


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_DSOSC
### Default
#### OriginalId=DL_SYNCHRONIZATION_ON_SHARED_CONSTANT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Synchronization On Shared Constant
#### WarningText
  Synchronization on interned String in {1}

#### HelpText
  The code synchronizes on interned String.

  ``` java
  private static String LOCK = "LOCK";
  ...
  synchronized(LOCK) {
      ...
  }
  ...
  ```

  Constant Strings are interned and shared across all other classes loaded by the JVM. Thus, this code is locking on something that other code might also be locking. This could result in very strange and hard to diagnose blocking and deadlock behavior. See <a href="http://www.javalobby.org/java/forums/t96352.html" class="uri" class="uri">http://www.javalobby.org/java/forums/t96352.html</a> and <a href="http://jira.codehaus.org/browse/JETTY-352" class="uri" class="uri">http://jira.codehaus.org/browse/JETTY-352</a>.

  See CERT [CON08-J. Do not synchronize on objects that may be reused](https://www.securecoding.cert.org/confluence/display/java/CON08-J.+Do+not+synchronize+on+objects+that+may+be+reused) for more information.


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_DSOUBP
### Default
#### OriginalId=DL_SYNCHRONIZATION_ON_UNSHARED_BOXED_PRIMITIVE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Synchronization On Unshared Boxed Primitive
#### WarningText
  Synchronization on {2} in {1}

#### HelpText
  The code synchronizes on an apparently unshared boxed primitive, such as an Integer.

  ``` java
  private static final Integer fileLock = new Integer(1);
  ...
  synchronized(fileLock) {
      .. do something ..
  }
  ...
  ```

  It would be much better, in this code, to redeclare fileLock as

  ``` java
  private static final Object fileLock = new Object();
  ```

  The existing code might be OK, but it is confusing and a future refactoring, such as the “Remove Boxing” refactoring in IntelliJ, might replace this with the use of an interned Integer object shared throughout the JVM, leading to very confusing behavior and potential deadlock.


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_DSTPEWZCT
### Default
#### OriginalId=DMI_SCHEDULED_THREAD_POOL_EXECUTOR_WITH_ZERO_CORE_THREADS
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Scheduled Thread Pool Executor With Zero Core Threads
#### WarningText
  Creation of ScheduledThreadPoolExecutor with zero core threads in {1}

#### HelpText
  ([Javadoc](http://docs.oracle.com/javase/6/docs/api/java/util/concurrent/ScheduledThreadPoolExecutor.html#ScheduledThreadPoolExecutor%28int%29)) A ScheduledThreadPoolExecutor with zero core threads will never execute anything; changes to the max pool size are ignored.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_DSVC
### Default
#### OriginalId=DM_STRING_VOID_CTOR
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=String Void Ctor
#### WarningText
  {1} invokes inefficient new String() constructor

#### HelpText
  Creating a new `java.lang.String` object using the no-argument constructor wastes memory because the object so created will be functionally indistinguishable from the empty string constant `""`.  Java guarantees that identical string constants will be represented by the same `String` object.  Therefore, you should just use the empty string constant directly.


#### Tags
- /tool/FindBugs
- /general/Optimization Rules

#### Settings
- Priority=Major


## FB_DUM
### Default
#### OriginalId=DMI_UNSUPPORTED_METHOD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unsupported Method
#### WarningText
  Call to unsupported method {2} in {1}

#### HelpText
  All targets of this method invocation throw an UnsupportedOperationException.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_DURTCC
### Default
#### OriginalId=DMI_USING_REMOVEALL_TO_CLEAR_COLLECTION
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Using Removeall To Clear Collection
#### WarningText
  removeAll used to clear a collection in {1}

#### HelpText
  If you want to remove all elements from a collection `c`, use `c.clear`, not `c.removeAll(c)`. Calling `c.removeAll(c)` to clear a collection is less clear, susceptible to errors from typos, less efficient and for some collections, might throw a `ConcurrentModificationException`.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_DUS
### Default
#### OriginalId=DMI_USELESS_SUBSTRING
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Useless Substring
#### WarningText
  {1} invokes substring(0), which returns the original value

#### HelpText
  This code invokes substring(0) on a String, which returns the original value.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_DUT
### Default
#### OriginalId=DM_USELESS_THREAD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Useless Thread
#### WarningText
  {1} creates a thread using the default empty run method

#### HelpText
  This method creates a thread without specifying a run method either by deriving from the Thread class, or by passing a Runnable object. This thread, then, does nothing but waste time.


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_DVCTEM
### Default
#### OriginalId=DMI_VACUOUS_CALL_TO_EASYMOCK_METHOD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Vacuous Call To Easymock Method
#### WarningText
  Useless/vacuous call to {2} in {1}

#### HelpText
  This call doesn’t pass any objects to the EasyMock method, so the call doesn’t do anything.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_DVSCC
### Default
#### OriginalId=DMI_VACUOUS_SELF_COLLECTION_CALL
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Vacuous Self Collection Call
#### WarningText
  For any collection c, calling c.{2.name}(c) doesn't make sense

#### HelpText
  This call doesn’t make sense. For any collection `c`, calling `c.containsAll(c)` should always be true, and `c.retainAll(c)` should have no effect.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_DmD
### Default
#### OriginalId=DMI_DOH
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Doh
#### WarningText
  D'oh! A nonsensical invocation of {2.nameAndSignature} in {1}

#### HelpText
  This partical method invocation doesn’t make sense, for reasons that should be apparent from inspection.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_EAAN
### Default
#### OriginalId=EC_ARRAY_AND_NONARRAY
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Array And Nonarray
#### WarningText
  Calling {3.simpleClass}.equals({2.simpleClass}) in {1}

#### HelpText
  This method invokes the .equals(Object o) to compare an array and a reference that doesn’t seem to be an array. If things being compared are of different types, they are guaranteed to be unequal and the comparison is almost certainly an error. Even if they are both arrays, the equals method on arrays only determines of the two arrays are the same object. To compare the contents of the arrays, use java.util.Arrays.equals(Object\[\], Object\[\]).


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_EAF
### Default
#### OriginalId=EQ_ALWAYS_FALSE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Always False
#### WarningText
  {1} always returns false

#### HelpText
  This class defines an equals method that always returns false. This means that an object is not equal to itself, and it is impossible to create useful Maps or Sets of this class. More fundamentally, it means that equals is not reflexive, one of the requirements of the equals method.

  The likely intended semantics are object identity: that an object is equal to itself. This is the behavior inherited from class `Object`. If you need to override an equals inherited from a different superclass, you can use:

  ``` java
  public boolean equals(Object o) {
      return this == o;
  }
  ```


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_EAS
### Default
#### OriginalId=EQ_ABSTRACT_SELF
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Abstract Self
#### WarningText
  Abstract {0} defines equals({0.givenClass}) method

#### HelpText
  This class defines a covariant version of `equals()`.  To correctly override the `equals()` method in `java.lang.Object`, the parameter of `equals()` must have type `java.lang.Object`.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_EAT
### Default
#### OriginalId=EQ_ALWAYS_TRUE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Always True
#### WarningText
  {1} always returns true

#### HelpText
  This class defines an equals method that always returns true. This is imaginative, but not very smart. Plus, it means that the equals method is not symmetric.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_EBAC
### Default
#### OriginalId=EC_BAD_ARRAY_COMPARE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Array Compare
#### WarningText
  Using .equals to compare two {2.simpleClass}'s, (equivalent to ==) in {1}

#### HelpText
  This method invokes the .equals(Object o) method on an array. Since arrays do not override the equals method of Object, calling equals on an array is the same as comparing their addresses. To compare the contents of the arrays, use `java.util.Arrays.equals(Object[], Object[])`. To compare the addresses of the arrays, it would be less confusing to explicitly check pointer equality using `==`.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_ECCN
### Default
#### OriginalId=EQ_COMPARING_CLASS_NAMES
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Comparing Class Names
#### WarningText
  {1} compares class names rather than class objects

#### HelpText
  This method checks to see if two objects are the same class by checking to see if the names of their classes are equal. You can have different classes with the same name if they are loaded by different class loaders. Just check to see if the class objects are the same.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_ECFONCWT
### Default
#### OriginalId=EQ_CHECK_FOR_OPERAND_NOT_COMPATIBLE_WITH_THIS
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Check For Operand Not Compatible With This
#### WarningText
  {1} checks for operand being a {2.givenClass}

#### HelpText
  This equals method is checking to see if the argument is some incompatible type (i.e., a class that is neither a supertype nor subtype of the class that defines the equals method). For example, the Foo class might have an equals method that looks like:

  ``` java
  public boolean equals(Object o) {
      if (o instanceof Foo)
          return name.equals(((Foo)o).name);
      else if (o instanceof String)
          return name.equals(o);
      else return false;
  }
  ```

  This is considered bad practice, as it makes it very hard to implement an equals method that is symmetric and transitive. Without those properties, very unexpected behaviors are possible.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_ECPSWE
### Default
#### OriginalId=ES_COMPARING_PARAMETER_STRING_WITH_EQ
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Comparing Parameter String With Eq
#### WarningText
  Comparison of String parameter using == or != in {1}

#### HelpText
  This code compares a `java.lang.String` parameter for reference equality using the == or != operators. Requiring callers to pass only String constants or interned strings to a method is unnecessarily fragile, and rarely leads to measurable performance gains. Consider using the `equals(Object)` method instead.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_ECSWE
### Default
#### OriginalId=ES_COMPARING_STRINGS_WITH_EQ
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Comparing Strings With Eq
#### WarningText
  Comparison of String objects using == or != in {1}

#### HelpText
  This code compares `java.lang.String` objects for reference equality using the == or != operators. Unless both strings are either constants in a source file, or have been interned using the `String.intern()` method, the same string value may be represented by two different String objects. Consider using the `equals(Object)` method instead.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_ECUOE
### Default
#### OriginalId=EQ_COMPARETO_USE_OBJECT_EQUALS
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Compareto Use Object Equals
#### WarningText
  {0} defines {1.givenClass} and uses Object.equals()

#### HelpText
  This class defines a `compareTo(...)` method but inherits its `equals()` method from `java.lang.Object`. Generally, the value of compareTo should return zero if and only if equals returns true. If this is violated, weird and unpredictable failures will occur in classes such as PriorityQueue. In Java 5 the PriorityQueue.remove method uses the compareTo method, while in Java 6 it uses the equals method.

  From the JavaDoc for the compareTo method in the Comparable interface:

  > It is strongly recommended, but not strictly required that `(x.compareTo(y)==0) == (x.equals(y))`. Generally speaking, any class that implements the Comparable interface and violates this condition should clearly indicate this fact. The recommended language is “Note: this class has a natural ordering that is inconsistent with equals.”


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_EDDEFE
### Default
#### OriginalId=EQ_DONT_DEFINE_EQUALS_FOR_ENUM
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Dont Define Equals For Enum
#### WarningText
  Enum {0} defines equals({0.givenClass})

#### HelpText
  This class defines an enumeration, and equality on enumerations are defined using object identity. Defining a covariant equals method for an enumeration value is exceptionally bad practice, since it would likely result in having two different enumeration values that compare as equals using the covariant enum method, and as not equal when compared normally. Don’t do it.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_EDOE
### Default
#### OriginalId=EQ_DOESNT_OVERRIDE_EQUALS
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Doesnt Override Equals
#### WarningText
  {0} doesn't override {2.givenClass}

#### HelpText
  This class extends a class that defines an equals method and adds fields, but doesn’t define an equals method itself. Thus, equality on instances of this class will ignore the identity of the subclass and the added fields. Be sure this is what is intended, and that you don’t need to override the equals method. Even if you don’t need to override the equals method, consider overriding it anyway to document the fact that the equals method for the subclass just return the result of invoking super.equals(o).


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_EER
### Default
#### OriginalId=EI_EXPOSE_REP
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Expose Rep
#### WarningText
  {1} may expose internal representation by returning {2.givenClass}

#### HelpText
  Returning a reference to a mutable object value stored in one of the object's fields exposes the internal representation of the object.  If instances are accessed by untrusted code, and unchecked changes to the mutable object would compromise security or other important properties, you will need to do something different. Returning a new copy of the object is better approach in many situations.


#### Tags
- /tool/FindBugs
- /general/Security Code Guideline Rules

#### Settings
- Priority=Info


## FB_EESR
### Default
#### OriginalId=EI_EXPOSE_STATIC_REP2
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Expose Static Rep2
#### WarningText
  {1} may expose internal static state by storing a mutable object into a static field {2}

#### HelpText
  This code stores a reference to an externally mutable object into a static field. If unchecked changes to the mutable object would compromise security or other important properties, you will need to do something different. Storing a copy of the object is better approach in many situations.


#### Tags
- /tool/FindBugs
- /general/Security Code Guideline Rules
- /collection/SEI CERT/OBJ13-J
- /collection/CWE/607

#### Settings
- Priority=Info


## FB_EF
### Default
#### OriginalId=FI_EMPTY
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Empty
#### WarningText
  {1} is empty and should be deleted

#### HelpText
  Empty `finalize()` methods are useless, so they should be deleted.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_EGACC
### Default
#### OriginalId=EQ_GETCLASS_AND_CLASS_CONSTANT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Getclass And Class Constant
#### WarningText
  {1} fails for subtypes

#### HelpText
  This class has an equals method that will be broken if it is inherited by subclasses. It compares a class literal with the class of the argument (e.g., in class `Foo` it might check if `Foo.class == o.getClass()`). It is better to check if `this.getClass() == o.getClass()`.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_EIAC
### Default
#### OriginalId=EC_INCOMPATIBLE_ARRAY_COMPARE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Incompatible Array Compare
#### WarningText
  Using equals to compare a {2.simpleClass} and a {3.simpleClass} in {1}

#### HelpText
  This method invokes the .equals(Object o) to compare two arrays, but the arrays of of incompatible types (e.g., String\[\] and StringBuffer\[\], or String\[\] and int\[\]). They will never be equal. In addition, when equals(…) is used to compare arrays it only checks to see if they are the same array, and ignores the contents of the arrays.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_ENA
### Default
#### OriginalId=EC_NULL_ARG
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Null Arg
#### WarningText
  Call to equals(null) in {1}

#### HelpText
  This method calls equals(Object), passing a null value as the argument. According to the contract of the equals() method, this call should always return `false`.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_EOENS
### Default
#### OriginalId=EQ_OVERRIDING_EQUALS_NOT_SYMMETRIC
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Overriding Equals Not Symmetric
#### WarningText
  {1.class} overrides equals in {2.class.givenClass} and may not be symmetric

#### HelpText
  This class defines an equals method that overrides an equals method in a superclass. Both equals methods use `instanceof` in the determination of whether two objects are equal. This is fraught with peril, since it is important that the equals method is symmetrical (in other words, `a.equals(b) == b.equals(a)`). If B is a subtype of A, and A’s equals method checks that the argument is an instanceof A, and B’s equals method checks that the argument is an instanceof B, it is quite likely that the equivalence relation defined by these methods is not symmetric.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_EONO
### Default
#### OriginalId=EQ_OTHER_NO_OBJECT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Other No Object
#### WarningText
  {0} defines {1.givenClass} method that doesn't override equals(Object)

#### HelpText
  This class defines an `equals()` method, that doesn’t override the normal `equals(Object)` method defined in the base `java.lang.Object` class.  Instead, it inherits an `equals(Object)` method from a superclass. The class should probably define a `boolean equals(Object)` method.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_EOUO
### Default
#### OriginalId=EQ_OTHER_USE_OBJECT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Other Use Object
#### WarningText
  {0} defines {1.givenClass} method and uses Object.equals(Object)

#### HelpText
  This class defines an `equals()` method, that doesn’t override the normal `equals(Object)` method defined in the base `java.lang.Object` class.  The class should probably define a `boolean equals(Object)` method.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_ESB
### Default
#### OriginalId=ESync_EMPTY_SYNC
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Empty Sync
#### WarningText
  Empty synchronized block in {1}

#### HelpText
  The code contains an empty synchronized block:

  ``` java
  synchronized() {
  }
  ```

  Empty synchronized blocks are far more subtle and hard to use correctly than most people recognize, and empty synchronized blocks are almost never a better solution than less contrived solutions.


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_ESNO
### Default
#### OriginalId=EQ_SELF_NO_OBJECT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Self No Object
#### WarningText
  {0} defines equals({0.givenClass}) method but not equals(Object)

#### HelpText
  This class defines a covariant version of `equals()`.  To correctly override the `equals()` method in `java.lang.Object`, the parameter of `equals()` must have type `java.lang.Object`.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_ESUO
### Default
#### OriginalId=EQ_SELF_USE_OBJECT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Self Use Object
#### WarningText
  {0} defines equals({0.givenClass}) method and uses Object.equals(Object)

#### HelpText
  This class defines a covariant version of the `equals()` method, but inherits the normal `equals(Object)` method defined in the base `java.lang.Object` class.  The class should probably define a `boolean equals(Object)` method.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_EU
### Default
#### OriginalId=EQ_UNUSUAL
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unusual
#### WarningText
  {1} is unusual

#### HelpText
  This class doesn’t do any of the patterns we recognize for checking that the type of the argument is compatible with the type of the `this` object. There might not be anything wrong with this code, but it is worth reviewing.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_EUCAI
### Default
#### OriginalId=EC_UNRELATED_CLASS_AND_INTERFACE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unrelated Class And Interface
#### WarningText
  Call to {3.simpleClass}.equals({2.simpleClass}) in {1}

#### HelpText
  This method calls equals(Object) on two references, one of which is a class and the other an interface, where neither the class nor any of its non-abstract subclasses implement the interface. Therefore, the objects being compared are unlikely to be members of the same class at runtime (unless some application classes were not analyzed, or dynamic class loading can occur at runtime). According to the contract of equals(), objects of different classes should always compare as unequal; therefore, according to the contract defined by java.lang.Object.equals(Object), the result of this comparison will always be false at runtime.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_EUI
### Default
#### OriginalId=EC_UNRELATED_INTERFACES
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unrelated Interfaces
#### WarningText
  Call to {3.simpleClass}.equals({2.simpleClass}) in {1}

#### HelpText
  This method calls equals(Object) on two references of unrelated interface types, where neither is a subtype of the other, and there are no known non-abstract classes which implement both interfaces. Therefore, the objects being compared are unlikely to be members of the same class at runtime (unless some application classes were not analyzed, or dynamic class loading can occur at runtime). According to the contract of equals(), objects of different classes should always compare as unequal; therefore, according to the contract defined by java.lang.Object.equals(Object), the result of this comparison will always be false at runtime.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_EUT
### Default
#### OriginalId=EC_UNRELATED_TYPES
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unrelated Types
#### WarningText
  Call to {3.simpleClass}.equals({2.simpleClass}) in {1}

#### HelpText
  This method calls equals(Object) on two references of different class types and analysis suggests they will be to objects of different classes at runtime. Further, examination of the equals methods that would be invoked suggest that either this call will always return false, or else the equals method is not be symmetric (which is a property required by the contract for equals in class Object).


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_EUTUPE
### Default
#### OriginalId=EC_UNRELATED_TYPES_USING_POINTER_EQUALITY
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unrelated Types Using Pointer Equality
#### WarningText
  Using pointer equality to compare a {2.givenClass} with a {3.givenClass} in {1}

#### HelpText
  This method uses pointer equality to compare two references that seem to be of different types. The result of this comparison will always be false at runtime.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_EiER
### Default
#### OriginalId=EI_EXPOSE_REP2
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Expose Rep2
#### WarningText
  {1} may expose internal representation by storing an externally mutable object into {2.givenClass}

#### HelpText
  This code stores a reference to an externally mutable object into the internal representation of the object.  If instances are accessed by untrusted code, and unchecked changes to the mutable object would compromise security or other important properties, you will need to do something different. Storing a copy of the object is better approach in many situations.


#### Tags
- /tool/FindBugs
- /general/Security Code Guideline Rules
- /collection/SEI CERT/OBJ04-J
- /collection/SEI CERT/OBJ05-J
- /collection/CWE/374
- /collection/CWE/375

#### Settings
- Priority=Info


## FB_FDNCSF
### Default
#### OriginalId=FI_MISSING_SUPER_CALL
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Missing Super Call
#### WarningText
  {1} missing call to super.finalize(), so {2}.finalize() doesn't get called

#### HelpText
  This `finalize()` method does not make a call to its superclass’s `finalize()` method.  So, any finalizer actions defined for the superclass will not be performed.  Add a call to `super.finalize()`.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_FFNF
### Default
#### OriginalId=FI_FINALIZER_NULLS_FIELDS
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Finalizer Nulls Fields
#### WarningText
  {3} is set to null inside finalize method in {1.class}

#### HelpText
  This finalizer nulls out fields. This is usually an error, as it does not aid garbage collection, and the object is going to be garbage collected anyway.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_FFONF
### Default
#### OriginalId=FI_FINALIZER_ONLY_NULLS_FIELDS
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Finalizer Only Nulls Fields
#### WarningText
  {1} only nulls fields

#### HelpText
  This finalizer does nothing except null out fields. This is completely pointless, and requires that the object be garbage collected, finalized, and then garbage collected again. You should just remove the finalize method.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_FFPE
### Default
#### OriginalId=FE_FLOATING_POINT_EQUALITY
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Floating Point Equality
#### WarningText
  Test for floating point equality in {1}

#### HelpText
  This operation compares two floating point values for equality. Because floating point calculations may involve rounding, calculated float and double values may not be accurate. For values that must be precise, such as monetary values, consider using a fixed-precision type such as BigDecimal. For values that need not be precise, consider comparing for equality within some range, for example: `if ( Math.abs(x - y) < .0000001 )`. See the Java Language Specification, section 4.2.4.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_FMEW
### Default
#### OriginalId=FB_MISSING_EXPECTED_WARNING
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Missing Expected Warning
#### WarningText
  Missing expected or desired {2} SpotBugs warning in {1}

#### HelpText
  SpotBugs didn’t generate generated a warning that, according to a <span class="citation" data-cites="ExpectedWarning">@ExpectedWarning</span> annotated, is expected or desired.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_FMUFP
### Default
#### OriginalId=FL_MATH_USING_FLOAT_PRECISION
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Math Using Float Precision
#### WarningText
  {1} performs math using floating point precision

#### HelpText
  The method performs math operations using floating point precision. Floating point precision is very imprecise. For example, 16777216.0f + 1.0f = 16777216.0f. Consider using double math instead.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_FNS
### Default
#### OriginalId=FI_NULLIFY_SUPER
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Nullify Super
#### WarningText
  {1} is nullifying {2}.finalize(); is this intended?

#### HelpText
  This empty `finalize()` method explicitly negates the effect of any finalizer defined by its superclass.  Any finalizer actions defined for the superclass will not be performed.  Unless this is intended, delete this method.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_FSBP
### Default
#### OriginalId=FI_PUBLIC_SHOULD_BE_PROTECTED
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Public Should Be Protected
#### WarningText
  {1} is public; should be protected

#### HelpText
  A class’s `finalize()` method should have protected access, not public.


#### Tags
- /tool/FindBugs
- /general/Security Code Guideline Rules
- /collection/CWE/584

#### Settings
- Priority=Info


## FB_FU
### Default
#### OriginalId=FI_USELESS
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Useless
#### WarningText
  {1} does nothing except call super.finalize(); delete it

#### HelpText
  The only thing this `finalize()` method does is call the superclass’s `finalize()` method, making it redundant.  Delete it.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_FUW
### Default
#### OriginalId=FB_UNEXPECTED_WARNING
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unexpected Warning
#### WarningText
  Unexpected/undesired {2} SpotBugs warning in {1}

#### HelpText
  SpotBugs generated a warning that, according to a <span class="citation" data-cites="NoWarning">@NoWarning</span> annotated, is unexpected or undesired.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_GUT
### Default
#### OriginalId=GC_UNRELATED_TYPES
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unrelated Types
#### WarningText
  {2.givenClass} is incompatible with expected argument type {3.givenClass} in {1}

#### HelpText
  This call to a generic collection method contains an argument with an incompatible class from that of the collection’s parameter (i.e., the type of the argument is neither a supertype nor a subtype of the corresponding generic type argument). Therefore, it is unlikely that the collection contains any objects that are equal to the method argument used here. Most likely, the wrong value is being passed to the method.

  In general, instances of two unrelated classes are not equal. For example, if the `Foo` and `Bar` classes are not related by subtyping, then an instance of `Foo` should not be equal to an instance of `Bar`. Among other issues, doing so will likely result in an equals method that is not symmetrical. For example, if you define the `Foo` class so that a `Foo` can be equal to a `String`, your equals method isn’t symmetrical since a `String` can only be equal to a `String`.

  In rare cases, people do define nonsymmetrical equals methods and still manage to make their code work. Although none of the APIs document or guarantee it, it is typically the case that if you check if a `Collection<String>` contains a `Foo`, the equals method of argument (e.g., the equals method of the `Foo` class) used to perform the equality checks.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_GUTIGC
### Default
#### OriginalId=GC_UNCHECKED_TYPE_IN_GENERIC_CALL
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unchecked Type In Generic Call
#### WarningText
  Unchecked argument of type Object provided where type {3.givenClass} is expected in {1}

#### HelpText
  This call to a generic collection method passes an argument while compile type Object where a specific type from the generic type parameters is expected. Thus, neither the standard Java type system nor static analysis can provide useful information on whether the object being passed as a parameter is of an appropriate type.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_HENH
### Default
#### OriginalId=HE_EQUALS_NO_HASHCODE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Equals No Hashcode
#### WarningText
  {0} defines equals but not hashCode

#### HelpText
  This class overrides `equals(Object)`, but does not override `hashCode()`.  Therefore, the class may violate the invariant that equal objects must have equal hashcodes.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_HEUH
### Default
#### OriginalId=HE_EQUALS_USE_HASHCODE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Equals Use Hashcode
#### WarningText
  {0} defines equals and uses Object.hashCode()

#### HelpText
  This class overrides `equals(Object)`, but does not override `hashCode()`, and inherits the implementation of `hashCode()` from `java.lang.Object` (which returns the identity hash code, an arbitrary value assigned to the object by the VM).  Therefore, the class is very likely to violate the invariant that equal objects must have equal hashcodes.

  If you don’t think instances of this class will ever be inserted into a HashMap/HashTable, the recommended `hashCode` implementation to use is:

  ``` java
  public int hashCode() {
      assert false : "hashCode not designed";
      return 42; // any arbitrary constant will do
  }
  ```


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_HHNE
### Default
#### OriginalId=HE_HASHCODE_NO_EQUALS
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Hashcode No Equals
#### WarningText
  {0} defines hashCode but not equals

#### HelpText
  This class defines a `hashCode()` method but not an `equals()` method.  Therefore, the class may violate the invariant that equal objects must have equal hashcodes.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_HHSSC
### Default
#### OriginalId=HSC_HUGE_SHARED_STRING_CONSTANT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Huge Shared String Constant
#### WarningText
  {1} is initialized to a string constant {2} characters long that is duplicated in {3} other class files

#### HelpText
  A large String constant is duplicated across multiple class files. This is likely because a final field is initialized to a String constant, and the Java language mandates that all references to a final field from other classes be inlined into that classfile. See [JDK bug 6447475](http://bugs.java.com/bugdatabase/view_bug.do?bug_id=6447475) for a description of an occurrence of this bug in the JDK and how resolving it reduced the size of the JDK by 1 megabyte.


#### Tags
- /tool/FindBugs
- /general/Optimization Rules

#### Settings
- Priority=Major


## FB_HHUOE
### Default
#### OriginalId=HE_HASHCODE_USE_OBJECT_EQUALS
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Hashcode Use Object Equals
#### WarningText
  {0} defines hashCode and uses Object.equals()

#### HelpText
  This class defines a `hashCode()` method but inherits its `equals()` method from `java.lang.Object` (which defines equality by comparing object references).  Although this will probably satisfy the contract that equal objects must have equal hashcodes, it is probably not what was intended by overriding the `hashCode()` method.  (Overriding `hashCode()` implies that the object’s identity is based on criteria more complicated than simple reference equality.)

  If you don’t think instances of this class will ever be inserted into a HashMap/HashTable, the recommended `hashCode` implementation to use is:

  ``` java
  public int hashCode() {
      assert false : "hashCode not designed";
      return 42; // any arbitrary constant will do
  }
  ```


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_HIEUH
### Default
#### OriginalId=HE_INHERITS_EQUALS_USE_HASHCODE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Inherits Equals Use Hashcode
#### WarningText
  {0} inherits equals and uses Object.hashCode()

#### HelpText
  This class inherits `equals(Object)` from an abstract superclass, and `hashCode()` from `java.lang.Object` (which returns the identity hash code, an arbitrary value assigned to the object by the VM).  Therefore, the class is very likely to violate the invariant that equal objects must have equal hashcodes.

  If you don’t want to define a hashCode method, and/or don’t believe the object will ever be put into a HashMap/Hashtable, define the `hashCode()` method to throw `UnsupportedOperationException`.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_HRPTC
### Default
#### OriginalId=HRS_REQUEST_PARAMETER_TO_COOKIE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Request Parameter To Cookie
#### WarningText
  HTTP cookie formed from untrusted input in {1}

#### HelpText
  This code constructs an HTTP Cookie using an untrusted HTTP parameter. If this cookie is added to an HTTP response, it will allow a HTTP response splitting vulnerability. See <a href="http://en.wikipedia.org/wiki/HTTP_response_splitting" class="uri" class="uri">http://en.wikipedia.org/wiki/HTTP_response_splitting</a> for more information.

  SpotBugs looks only for the most blatant, obvious cases of HTTP response splitting. If SpotBugs found *any*, you *almost certainly* have more vulnerabilities that SpotBugs doesn’t report. If you are concerned about HTTP response splitting, you should seriously consider using a commercial static analysis or pen-testing tool.


#### Tags
- /tool/FindBugs
- /general/Vulnerability 
- /collection/CWE/113
- /collection/OWASP/A03:2021

#### Settings
- Priority=Major


## FB_HRPTHH
### Default
#### OriginalId=HRS_REQUEST_PARAMETER_TO_HTTP_HEADER
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Request Parameter To Http Header
#### WarningText
  HTTP parameter directly written to HTTP header output in {1}

#### HelpText
  This code directly writes an HTTP parameter to an HTTP header, which allows for a HTTP response splitting vulnerability. See <a href="http://en.wikipedia.org/wiki/HTTP_response_splitting" class="uri" class="uri">http://en.wikipedia.org/wiki/HTTP_response_splitting</a> for more information.

  SpotBugs looks only for the most blatant, obvious cases of HTTP response splitting. If SpotBugs found *any*, you *almost certainly* have more vulnerabilities that SpotBugs doesn’t report. If you are concerned about HTTP response splitting, you should seriously consider using a commercial static analysis or pen-testing tool.


#### Tags
- /tool/FindBugs
- /general/Vulnerability Rules
- /collection/CWE/113
- /collection/OWASP/A03:2021

#### Settings
- Priority=Major


## FB_HSDHOUC
### Default
#### OriginalId=HE_SIGNATURE_DECLARES_HASHING_OF_UNHASHABLE_CLASS
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Signature Declares Hashing Of Unhashable Class
#### WarningText
  {2} doesn't define a hashCode() method but it is used in a hashed context in {1}

#### HelpText
  A method, field or class declares a generic signature where a non-hashable class is used in context where a hashable class is required. A class that declares an equals method but inherits a hashCode() method from Object is unhashable, since it doesn’t fulfill the requirement that equal objects have equal hashCodes.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_HUOUC
### Default
#### OriginalId=HE_USE_OF_UNHASHABLE_CLASS
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Use Of Unhashable Class
#### WarningText
  {2} doesn't define a hashCode() method but is used in a hashed data structure in {1}

#### HelpText
  A class defines an equals(Object) method but not a hashCode() method, and thus doesn’t fulfill the requirement that equal objects have equal hashCodes. An instance of this class is used in a hash data structure, making the need to fix this problem of highest importance.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_IACCO
### Default
#### OriginalId=IM_AVERAGE_COMPUTATION_COULD_OVERFLOW
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Average Computation Could Overflow
#### WarningText
  Computation of average could overflow in {1}

#### HelpText
  The code computes the average of two integers using either division or signed right shift, and then uses the result as the index of an array. If the values being averaged are very large, this can overflow (resulting in the computation of a negative average). Assuming that the result is intended to be nonnegative, you can use an unsigned right shift instead. In other words, rather that using `(low+high)/2`, use `(low+high) >>> 1`

  This bug exists in many earlier implementations of binary search and merge sort. Martin Buchholz [found and fixed it](http://bugs.java.com/bugdatabase/view_bug.do?bug_id=6412541) in the JDK libraries, and Joshua Bloch [widely publicized the bug pattern](http://googleresearch.blogspot.com/2006/06/extra-extra-read-all-about-it-nearly.html).


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_IAIOIOOM
### Default
#### OriginalId=IA_AMBIGUOUS_INVOCATION_OF_INHERITED_OR_OUTER_METHOD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Ambiguous Invocation Of Inherited Or Outer Method
#### WarningText
  Potentially ambiguous invocation of either an outer or inherited method {2} in {1}

#### HelpText
  An inner class is invoking a method that could be resolved to either a inherited method or a method defined in an outer class. For example, you invoke `foo(17)`, which is defined in both a superclass and in an outer method. By the Java semantics, it will be resolved to invoke the inherited method, but this may not be what you intend.

  If you really intend to invoke the inherited method, invoke it by invoking the method on super (e.g., invoke super.foo(17)), and thus it will be clear to other readers of your code and to SpotBugs that you want to invoke the inherited method, not the method in the outer class.

  If you call `this.foo(17)`, then the inherited method will be invoked. However, since SpotBugs only looks at classfiles, it can’t tell the difference between an invocation of `this.foo(17)` and `foo(17)`, it will still complain about a potential ambiguous invocation.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_IAMIFRM
### Default
#### OriginalId=IJU_ASSERT_METHOD_INVOKED_FROM_RUN_METHOD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Assert Method Invoked From Run Method
#### WarningText
  JUnit assertion in {1} will not be noticed by JUnit

#### HelpText
  A JUnit assertion is performed in a run method. Failed JUnit assertions just result in exceptions being thrown. Thus, if this exception occurs in a thread other than the thread that invokes the test method, the exception will terminate the thread but not result in the test failing.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_IATOOS
### Default
#### OriginalId=IO_APPENDING_TO_OBJECT_OUTPUT_STREAM
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Appending To Object Output Stream
#### WarningText
  Doomed attempt to append to an object output stream in {1}

#### HelpText
  This code opens a file in append mode and then wraps the result in an object output stream. This won’t allow you to append to an existing object output stream stored in a file. If you want to be able to append to an object output stream, you need to keep the object output stream open.

  The only situation in which opening a file in append mode and the writing an object output stream could work is if on reading the file you plan to open it in random access mode and seek to the byte offset where the append started.

  TODO: example.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_IBCFO
### Default
#### OriginalId=IM_BAD_CHECK_FOR_ODD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Check For Odd
#### WarningText
  Check for oddness that won't work for negative numbers in {1}

#### HelpText
  The code uses x % 2 == 1 to check to see if a value is odd, but this won’t work for negative numbers (e.g., (-5) % 2 == -1). If this code is intending to check for oddness, consider using x & 1 == 1, or x % 2 != 0.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_IBCWIV
### Default
#### OriginalId=INT_BAD_COMPARISON_WITH_INT_VALUE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Comparison With Int Value
#### WarningText
  Bad comparison of int with {2} in {1}

#### HelpText
  This code compares an int value with a long constant that is outside the range of values that can be represented as an int value. This comparison is vacuous and possibly incorrect.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_IBCWNV
### Default
#### OriginalId=INT_BAD_COMPARISON_WITH_NONNEGATIVE_VALUE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Comparison With Nonnegative Value
#### WarningText
  Bad comparison of nonnegative value with {2} in {1}

#### HelpText
  This code compares a value that is guaranteed to be non-negative with a negative constant or zero.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_IBCWSB
### Default
#### OriginalId=INT_BAD_COMPARISON_WITH_SIGNED_BYTE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Comparison With Signed Byte
#### WarningText
  Bad comparison of signed byte with {2} in {1}

#### HelpText
  Signed bytes can only have a value in the range -128 to 127. Comparing a signed byte with a value outside that range is vacuous and likely to be incorrect. To convert a signed byte `b` to an unsigned value in the range 0..255, use `0xff & b`.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_IBRB1
### Default
#### OriginalId=INT_BAD_REM_BY_1
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Rem By 1
#### WarningText
  Integer remainder modulo 1 computed in {1}

#### HelpText
  Any expression (exp % 1) is guaranteed to always return zero. Did you mean (exp & 1) or (exp % 2) instead?


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_IBSA
### Default
#### OriginalId=ICAST_BAD_SHIFT_AMOUNT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Shift Amount
#### WarningText
  32 bit int shifted by {2} bits in {1}

#### HelpText
  The code performs shift of a 32 bit int by a constant amount outside the range -31..31. The effect of this is to use the lower 5 bits of the integer value to decide how much to shift by (e.g., shifting by 40 bits is the same as shifting by 8 bits, and shifting by 32 bits is the same as shifting by zero bits). This probably isn’t what was expected, and it is at least confusing.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_IBSM
### Default
#### OriginalId=IJU_BAD_SUITE_METHOD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Suite Method
#### WarningText
  Bad declaration for suite method in {0}

#### HelpText
  Class is a JUnit TestCase and defines a suite() method. However, the suite method needs to be declared as either

  ``` java
  public static junit.framework.Test suite()
  ```

  or

  ``` java
  public static junit.framework.TestSuite suite()
  ```


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_ICATI
### Default
#### OriginalId=IL_CONTAINER_ADDED_TO_ITSELF
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Container Added To Itself
#### WarningText
  A collection is added to itself in {1}

#### HelpText
  A collection is added to itself. As a result, computing the hashCode of this set will throw a StackOverflowException.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_IDCI
### Default
#### OriginalId=IMSE_DONT_CATCH_IMSE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Dont Catch Imse
#### WarningText
  Dubious catching of IllegalMonitorStateException in {1}

#### HelpText
  IllegalMonitorStateException is generally only thrown in case of a design flaw in your code (calling wait or notify on an object you do not hold a lock on).


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_IEGLIL
### Default
#### OriginalId=IIL_ELEMENTS_GET_LENGTH_IN_LOOP
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=Elements Get Length In Loop
#### WarningText
  {1} calls NodeList.getLength() in a loop for getElementsByTagName return value

#### HelpText
  The method calls NodeList.getLength() inside the loop and NodeList was produced by getElementsByTagName call. This NodeList doesn't store its length, but computes it every time in not very optimal way. Consider storing the length to the variable before the loop.


#### Tags
- /tool/FindBugs
- /general/Optimization Rules

#### Settings
- Priority=Major


## FB_IFNG
### Default
#### OriginalId=IS_FIELD_NOT_GUARDED
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Field Not Guarded
#### WarningText
  {1.givenClass} not guarded against concurrent access; locked {2}% of time

#### HelpText
  This field is annotated with net.jcip.annotations.GuardedBy or javax.annotation.concurrent.GuardedBy, but can be accessed in a way that seems to violate those annotations.


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_II2LAI
### Default
#### OriginalId=ICAST_INT_2_LONG_AS_INSTANT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Int 2 Long As Instant
#### WarningText
  int converted to long and passed as absolute time to {2} in {1}

#### HelpText
  This code converts a 32-bit int value to a 64-bit long value, and then passes that value for a method parameter that requires an absolute time value. An absolute time value is the number of milliseconds since the standard base time known as “the epoch”, namely January 1, 1970, 00:00:00 GMT. For example, the following method, intended to convert seconds since the epoch into a Date, is badly broken:

  ``` java
  Date getDate(int seconds) { return new Date(seconds * 1000); }
  ```

  The multiplication is done using 32-bit arithmetic, and then converted to a 64-bit value. When a 32-bit value is converted to 64-bits and used to express an absolute time value, only dates in December 1969 and January 1970 can be represented.

  Correct implementations for the above method are:

  ``` java
  // Fails for dates after 2037
  Date getDate(int seconds) { return new Date(seconds * 1000L); }

  // better, works for all dates
  Date getDate(long seconds) { return new Date(seconds * 1000); }
  ```


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_IIC
### Default
#### OriginalId=IC_INIT_CIRCULARITY
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Init Circularity
#### WarningText
  Initialization circularity between {0} and {1}

#### HelpText
  A circularity was detected in the static initializers of the two classes referenced by the bug instance.  Many kinds of unexpected behavior may arise from such circularity.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_IICTD
### Default
#### OriginalId=ICAST_IDIV_CAST_TO_DOUBLE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Idiv Cast To Double
#### WarningText
  Integral division result cast to double or float in {1}

#### HelpText
  This code casts the result of an integral division (e.g., int or long division) operation to double or float. Doing division on integers truncates the result to the integer value closest to zero. The fact that the result was cast to double suggests that this precision should have been retained. What was probably meant was to cast one or both of the operands to double *before* performing the division. Here is an example:

  ``` java
  int x = 2;
  int y = 5;
  // Wrong: yields result 0.0
  double value1 = x / y;

  // Right: yields result 0.4
  double value2 = x / (double) y;
  ```


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_IICTDPTC
### Default
#### OriginalId=ICAST_INT_CAST_TO_DOUBLE_PASSED_TO_CEIL
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Int Cast To Double Passed To Ceil
#### WarningText
  Integral value cast to double and then passed to Math.ceil in {1}

#### HelpText
  This code converts an integral value (e.g., int or long) to a double precision floating point number and then passing the result to the Math.ceil() function, which rounds a double to the next higher integer value. This operation should always be a no-op, since the converting an integer to a double should give a number with no fractional part. It is likely that the operation that generated the value to be passed to Math.ceil was intended to be performed using double precision floating point arithmetic.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_IICTFPTR
### Default
#### OriginalId=ICAST_INT_CAST_TO_FLOAT_PASSED_TO_ROUND
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Int Cast To Float Passed To Round
#### WarningText
  int value cast to float and then passed to Math.round in {1}

#### HelpText
  This code converts an int value to a float precision floating point number and then passing the result to the Math.round() function, which returns the int/long closest to the argument. This operation should always be a no-op, since the converting an integer to a float should give a number with no fractional part. It is likely that the operation that generated the value to be passed to Math.round was intended to be performed using floating point arithmetic.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_IIIO
### Default
#### OriginalId=IIO_INEFFICIENT_INDEX_OF
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=Inefficient Index Of
#### WarningText
  {1} uses String.indexOf(String) instead of String.indexOf(int)

#### HelpText
  This code passes a constant string of length 1 to String.indexOf(). It is more efficient to use the integer implementations of String.indexOf(). f. e. call \`myString.indexOf('.')\` instead of \`myString.indexOf(".")\`


#### Tags
- /tool/FindBugs
- /general/Optimization Rules

#### Settings
- Priority=Major


## FB_IIL
### Default
#### OriginalId=IL_INFINITE_LOOP
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Infinite Loop
#### WarningText
  There is an apparent infinite loop in {1}

#### HelpText
  This loop doesn’t seem to have a way to terminate (other than by perhaps throwing an exception).


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_IILIO
### Default
#### OriginalId=IIO_INEFFICIENT_LAST_INDEX_OF
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=Inefficient Last Index Of
#### WarningText
  {1} uses String.lastIndexOf(String) instead of String.lastIndexOf(int)

#### HelpText
  This code passes a constant string of length 1 to String.lastIndexOf(). It is more efficient to use the integer implementations of String.lastIndexOf(). f. e. call \`myString.lastIndexOf('.')\` instead of \`myString.lastIndexOf(".")\`


#### Tags
- /tool/FindBugs
- /general/Optimization Rules

#### Settings
- Priority=Major


## FB_IIMA
### Default
#### OriginalId=IMA_INEFFICIENT_MEMBER_ACCESS
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=Inefficient Member Access
#### WarningText
  {1} accesses to a private member variable of owning class

#### HelpText
  This method of an inner class reads from or writes to a private member variable of the owning class, or calls a private method of the owning class. The compiler must generate a special method to access this private member, causing this to be less efficient. Relaxing the protection of the member variable or method will allow the compiler to treat this as a normal access.


#### Tags
- /tool/FindBugs
- /general/Optimization Rules

#### Settings
- Priority=Major


## FB_IIMCTL
### Default
#### OriginalId=ICAST_INTEGER_MULTIPLY_CAST_TO_LONG
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Integer Multiply Cast To Long
#### WarningText
  Result of integer multiplication cast to long in {1}

#### HelpText
  This code performs integer multiply and then converts the result to a long, as in:

  ``` java
  long convertDaysToMilliseconds(int days) { return 1000*3600*24*days; }
  ```

  If the multiplication is done using long arithmetic, you can avoid the possibility that the result will overflow. For example, you could fix the above code to:

  ``` java
  long convertDaysToMilliseconds(int days) { return 1000L*3600*24*days; }
  ```

  or

  ``` java
  static final long MILLISECONDS_PER_DAY = 24L*3600*1000;
  long convertDaysToMilliseconds(int days) { return days * MILLISECONDS_PER_DAY; }
  ```


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_IIRL
### Default
#### OriginalId=IL_INFINITE_RECURSIVE_LOOP
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Infinite Recursive Loop
#### WarningText
  There is an apparent infinite recursive loop in {1}

#### HelpText
  This method unconditionally invokes itself. This would seem to indicate an infinite recursive loop that will result in a stack overflow.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_IIS
### Default
#### OriginalId=IS2_INCONSISTENT_SYNC
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Inconsistent Sync
#### WarningText
  Inconsistent synchronization of {1}; locked {2}% of time

#### HelpText
  The fields of this class appear to be accessed inconsistently with respect to synchronization.  This bug report indicates that the bug pattern detector judged that

  -   The class contains a mix of locked and unlocked accesses,
  -   The class is **not** annotated as javax.annotation.concurrent.NotThreadSafe,
  -   At least one locked access was performed by one of the class’s own methods, and
  -   The number of unsynchronized field accesses (reads and writes) was no more than one third of all accesses, with writes being weighed twice as high as reads

  A typical bug matching this bug pattern is forgetting to synchronize one of the methods in a class that is intended to be thread-safe.

  You can select the nodes labeled “Unsynchronized access” to show the code locations where the detector believed that a field was accessed without synchronization.

  Note that there are various sources of inaccuracy in this detector; for example, the detector cannot statically detect all situations in which a lock is held.  Also, even when the detector is accurate in distinguishing locked vs. unlocked accesses, the code in question may still be correct.


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_IISC
### Default
#### OriginalId=ISC_INSTANTIATE_STATIC_CLASS
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Instantiate Static Class
#### WarningText
  {1} needlessly instantiates a class that only supplies static methods

#### HelpText
  This class allocates an object that is based on a class that only supplies static methods. This object does not need to be created, just access the static methods directly using the class name as a qualifier.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_IMROI
### Default
#### OriginalId=IM_MULTIPLYING_RESULT_OF_IREM
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Multiplying Result Of Irem
#### WarningText
  Integer multiple of result of integer remainder in {1}

#### HelpText
  The code multiplies the result of an integer remaining by an integer constant. Be sure you don’t have your operator precedence confused. For example i % 60 \* 1000 is (i % 60) \* 1000, not i % (60 \* 1000).


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_INSE
### Default
#### OriginalId=IT_NO_SUCH_ELEMENT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=No Such Element
#### WarningText
  {1} can't throw NoSuchElementException

#### HelpText
  This class implements the `java.util.Iterator` interface.  However, its `next()` method is not capable of throwing `java.util.NoSuchElementException`.  The `next()` method should be changed so it throws `NoSuchElementException` if is called when there are no more elements to return.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_INT
### Default
#### OriginalId=IJU_NO_TESTS
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=No Tests
#### WarningText
  TestCase {0} has no tests

#### HelpText
  Class is a JUnit TestCase but has not implemented any test methods.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_IPCIL
### Default
#### OriginalId=IIL_PATTERN_COMPILE_IN_LOOP
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=Pattern Compile In Loop
#### WarningText
  {1} calls Pattern.compile with the constant arguments in a loop

#### HelpText
  The method calls Pattern.compile inside the loop passing the constant arguments. If the Pattern should be used several times there's no reason to compile it for each loop iteration. Move this call outside of the loop or even into static final field.


#### Tags
- /tool/FindBugs
- /general/Optimization Rules

#### Settings
- Priority=Major


## FB_IPCILI
### Default
#### OriginalId=IIL_PATTERN_COMPILE_IN_LOOP_INDIRECT
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=Pattern Compile In Loop Indirect
#### WarningText
  {1} compiles the regular expression in a loop

#### HelpText
  The method creates the same regular expression inside the loop, so it will be compiled every iteration. It would be more optimal to precompile this regular expression using Pattern.compile outside of the loop.


#### Tags
- /tool/FindBugs
- /general/Optimization Rules

#### Settings
- Priority=Major


## FB_IPIDBO
### Default
#### OriginalId=IP_PARAMETER_IS_DEAD_BUT_OVERWRITTEN
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Parameter Is Dead But Overwritten
#### WarningText
  The parameter {2} to {1} is dead upon entry but overwritten

#### HelpText
  The initial value of this parameter is ignored, and the parameter is overwritten here. This often indicates a mistaken belief that the write to the parameter will be conveyed back to the caller.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_IPSIL
### Default
#### OriginalId=IIL_PREPARE_STATEMENT_IN_LOOP
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=Prepare Statement In Loop
#### WarningText
  {1} calls prepareStatement with the constant arguments in a loop

#### HelpText
  The method calls Connection.prepareStatement inside the loop passing the constant arguments. If the PreparedStatement should be executed several times there's no reason to recreate it for each loop iteration. Move this call outside of the loop.


#### Tags
- /tool/FindBugs
- /general/Optimization Rules

#### Settings
- Priority=Major


## FB_IQURS
### Default
#### OriginalId=ICAST_QUESTIONABLE_UNSIGNED_RIGHT_SHIFT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Questionable Unsigned Right Shift
#### WarningText
  Unsigned right shift cast to short/byte in {1}

#### HelpText
  The code performs an unsigned right shift, whose result is then cast to a short or byte, which discards the upper bits of the result. Since the upper bits are discarded, there may be no difference between a signed and unsigned right shift (depending upon the size of the shift).


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_ISNS
### Default
#### OriginalId=IJU_SETUP_NO_SUPER
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Setup No Super
#### WarningText
  TestCase {0} defines setUp that doesn't call super.setUp()

#### HelpText
  Class is a JUnit TestCase and implements the setUp method. The setUp method should call super.setUp(), but doesn’t.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_ISUSDI
### Default
#### OriginalId=IC_SUPERCLASS_USES_SUBCLASS_DURING_INITIALIZATION
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Superclass Uses Subclass During Initialization
#### WarningText
  Initialization of {0} accesses class {2}, which isn't initialized yet

#### HelpText
  During the initialization of a class, the class makes an active use of a subclass. That subclass will not yet be initialized at the time of this use. For example, in the following code, `foo` will be null.

  ``` java
  public class CircularClassInitialization {
      static class InnerClassSingleton extends CircularClassInitialization {
          static InnerClassSingleton singleton = new InnerClassSingleton();
      }

      static CircularClassInitialization foo = InnerClassSingleton.singleton;
  }
  ```


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_ITGC
### Default
#### OriginalId=DM_NEW_FOR_GETCLASS
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=New For Getclass
#### WarningText
  {1} allocates an object, only to get the class object

#### HelpText
  This method allocates an object just to call getClass() on it, in order to retrieve the Class object for it. It is simpler to just access the .class property of the class.


#### Tags
- /tool/FindBugs
- /general/Optimization Rules

#### Settings
- Priority=Major


## FB_ITNS
### Default
#### OriginalId=IJU_TEARDOWN_NO_SUPER
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Teardown No Super
#### WarningText
  TestCase {0} defines tearDown that doesn't call super.tearDown()

#### HelpText
  Class is a JUnit TestCase and implements the tearDown method. The tearDown method should call super.tearDown(), but doesn’t.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_IVBO
### Default
#### OriginalId=INT_VACUOUS_BIT_OPERATION
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Vacuous Bit Operation
#### WarningText
  Vacuous {2} operation on {3} in {1}

#### HelpText
  This is an integer bit operation (and, or, or exclusive or) that doesn’t do any useful work (e.g., `v & 0xffffffff`).


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_IVC
### Default
#### OriginalId=INT_VACUOUS_COMPARISON
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Vacuous Comparison
#### WarningText
  Vacuous comparison of integer value {1}

#### HelpText
  There is an integer comparison that always returns the same value (e.g., x &lt;= Integer.MAX\_VALUE).


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_JDAIIT
### Default
#### OriginalId=JUA_DONT_ASSERT_INSTANCEOF_IN_TESTS
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=Dont Assert Instanceof In Tests
#### WarningText
   Assertion of type {0} in {2} at {3} may hide useful information about why a cast may have failed.

#### HelpText
  Asserting type checks in tests is not recommended as a class cast exception message could better indicate the cause of an instance of the wrong class being used than an instanceof assertion. When debugging tests that fail due to bad casts, it may be more useful to observe the output of the resulting ClassCastException which could provide information about the actual encountered type. Asserting the type before casting would instead result in a less informative \`"false is not true"\` message. If JUnit is used with hamcrest, the \[\`IsInstanceOf\`\](https://junit.org/junit4/javadoc/latest/index.html?org/hamcrest/core/IsInstanceOf.html) class from hamcrest could be used instead.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_JFIFIIC
### Default
#### OriginalId=JCIP_FIELD_ISNT_FINAL_IN_IMMUTABLE_CLASS
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Field Isnt Final In Immutable Class
#### WarningText
  {1.givenClass} should be final since {0} is marked as Immutable.

#### HelpText
  The class is annotated with net.jcip.annotations.Immutable or javax.annotation.concurrent.Immutable, and the rules for those annotations require that all fields are final. .


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_JJCWRTA
### Default
#### OriginalId=JML_JSR166_CALLING_WAIT_RATHER_THAN_AWAIT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Jsr166 Calling Wait Rather Than Await
#### WarningText
  Calling {2.name} rather than {3.name} in {1}

#### HelpText
  This method calls `wait()`, `notify()` or `notifyAll()()` on an object that also provides an `await()`, `signal()`, `signalAll()` method (such as util.concurrent Condition objects). This probably isn’t what you want, and even if you do want it, you should consider changing your design, as other developers will find it exceptionally confusing.


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_JJLM
### Default
#### OriginalId=JLM_JSR166_LOCK_MONITORENTER
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Jsr166 Lock Monitorenter
#### WarningText
  Synchronization performed on {2} in {1}

#### HelpText
  This method performs synchronization on an object that implements java.util.concurrent.locks.Lock. Such an object is locked/unlocked using `acquire()`/`release()` rather than using the `synchronized (...)` construct.


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_JJUM
### Default
#### OriginalId=JLM_JSR166_UTILCONCURRENT_MONITORENTER
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Jsr166 Utilconcurrent Monitorenter
#### WarningText
  Synchronization performed on {2} in {1}

#### HelpText
  This method performs synchronization on an object that is an instance of a class from the java.util.concurrent package (or its subclasses). Instances of these classes have their own concurrency control mechanisms that are orthogonal to the synchronization provided by the Java keyword `synchronized`. For example, synchronizing on an `AtomicBoolean` will not prevent other threads from modifying the `AtomicBoolean`.

  Such code may be correct, but should be carefully reviewed and documented, and may confuse people who have to maintain the code at a later date.


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_JSONSOIS
### Default
#### OriginalId=J2EE_STORE_OF_NON_SERIALIZABLE_OBJECT_INTO_SESSION
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Store Of Non Serializable Object Into Session
#### WarningText
  Store of non serializable {2} into HttpSession in {1}

#### HelpText
  This code seems to be storing a non-serializable object into an HttpSession. If this session is passivated or migrated, an error will result.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_JUSS
### Default
#### OriginalId=IJU_SUITE_NOT_STATIC
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Suite Not Static
#### WarningText
  TestCase {0} implements a non-static suite method

#### HelpText
  Class is a JUnit TestCase and implements the suite() method. The suite method should be declared as being static, but isn’t.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_LLIS
### Default
#### OriginalId=LI_LAZY_INIT_STATIC
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Lazy Init Static
#### WarningText
  Incorrect lazy initialization of static field {2} in {1}

#### HelpText
  This method contains an unsynchronized lazy initialization of a non-volatile static field. Because the compiler or processor may reorder instructions, threads are not guaranteed to see a completely initialized object, *if the method can be called by multiple threads*. You can make the field volatile to correct the problem. For more information, see the [Java Memory Model web site](http://www.cs.umd.edu/~pugh/java/memoryModel/).


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_LLIUS
### Default
#### OriginalId=LI_LAZY_INIT_UPDATE_STATIC
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Lazy Init Update Static
#### WarningText
  Incorrect lazy initialization and update of static field {2} in {1}

#### HelpText
  This method contains an unsynchronized lazy initialization of a static field. After the field is set, the object stored into that location is further updated or accessed. The setting of the field is visible to other threads as soon as it is set. If the further accesses in the method that set the field serve to initialize the object, then you have a *very serious* multithreading bug, unless something else prevents any other thread from accessing the stored object until it is fully initialized.

  Even if you feel confident that the method is never called by multiple threads, it might be better to not set the static field until the value you are setting it to is fully populated/initialized.


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_LLLDTWR
### Default
#### OriginalId=LG_LOST_LOGGER_DUE_TO_WEAK_REFERENCE
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=Lost Logger Due To Weak Reference
#### WarningText
  Changes to logger could be lost in {1}

#### HelpText
  OpenJDK introduces a potential incompatibility. In particular, the java.util.logging.Logger behavior has changed. Instead of using strong references, it now uses weak references internally. That's a reasonable change, but unfortunately some code relies on the old behavior - when changing logger configuration, it simply drops the logger reference. That means that the garbage collector is free to reclaim that memory, which means that the logger configuration is lost. For example, consider: \`\`\` {.java} public static void initLogging() throws Exception { Logger logger = Logger.getLogger("edu.umd.cs"); logger.addHandler(new FileHandler()); // call to change logger configuration logger.setUseParentHandlers(false); // another call to change logger configuration } \`\`\` The logger reference is lost at the end of the method (it doesn't escape the method), so if you have a garbage collection cycle just after the call to initLogging, the logger configuration is lost (because Logger only keeps weak references). \`\`\` {.java} public static void main(String\[\] args) throws Exception { initLogging(); // adds a file handler to the logger System.gc(); // logger configuration lost Logger.getLogger("edu.umd.cs").info("Some message"); // this isn't logged to the file as expected } \`\`\` \*Ulf Ochsenfahrt and Eric Fellheimer\*


#### Tags
- /tool/FindBugs
- /general/Experimental Rules

#### Settings
- Priority=Info


## FB_MBIS
### Default
#### OriginalId=SF_SWITCH_FALLTHROUGH
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Switch Fallthrough
#### WarningText
  Switch statement found in {1} where one case falls through to the next case

#### HelpText
  This method contains a switch statement where one case branch will fall through to the next case. Usually you need to end this case with a break or return.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_MCBF
### Default
#### OriginalId=MS_CANNOT_BE_FINAL
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Cannot Be Final
#### WarningText
  {1} isn't final and can't be protected from malicious code

#### HelpText
  A mutable static field could be changed by malicious code or by accident from another package. Unfortunately, the way the field is used doesn’t allow any easy fix to this problem.


#### Tags
- /tool/FindBugs
- /general/Security Code Guideline Rules
- /collection/SEI CERT/OBJ01-J
- /collection/SEI CERT/OBJ13-J
- /collection/CWE/500
- /collection/CWE/607

#### Settings
- Priority=Info


## FB_MCMF
### Default
#### OriginalId=MF_CLASS_MASKS_FIELD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Class Masks Field
#### WarningText
  Field {1.givenClass} masks field in superclass {2.class}

#### HelpText
  This class defines a field with the same name as a visible instance field in a superclass. This is confusing, and may indicate an error if methods update or access one of the fields when they wanted the other.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_MEFS
### Default
#### OriginalId=ME_ENUM_FIELD_SETTER
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Enum Field Setter
#### WarningText
  {1} unconditionally sets the field {2.name}

#### HelpText
  This public method declared in public enum unconditionally sets enum field, thus this field can be changed by malicious code or by accident from another package. Though mutable enum fields may be used for lazy initialization, it’s a bad practice to expose them to the outer world. Consider removing this method or declaring it package-private.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_MFP
### Default
#### OriginalId=MS_FINAL_PKGPROTECT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Final Pkgprotect
#### WarningText
  {1} should be both final and package protected

#### HelpText
  A mutable static field could be changed by malicious code or by accident from another package. The field could be made package protected and/or made final to avoid this vulnerability.


#### Tags
- /tool/FindBugs
- /general/Security Code Guideline Rules
- /collection/SEI CERT/OBJ10-J
- /collection/CWE/493
- /collection/CWE/500

#### Settings
- Priority=Info


## FB_MMA
### Default
#### OriginalId=MS_MUTABLE_ARRAY
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Mutable Array
#### WarningText
  {1} is a mutable array

#### HelpText
  A final static field references an array and can be accessed by malicious code or by accident from another package. This code can freely modify the contents of the array.


#### Tags
- /tool/FindBugs
- /general/Security Code Guideline Rules
- /collection/SEI CERT/OBJ01-J
- /collection/SEI CERT/OBJ13-J
- /collection/CWE/607

#### Settings
- Priority=Info


## FB_MMC
### Default
#### OriginalId=MS_MUTABLE_COLLECTION
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Mutable Collection
#### WarningText
  {1} is a mutable collection

#### HelpText
  A mutable collection instance is assigned to a final static field, thus can be changed by malicious code or by accident from another package. Consider wrapping this field into Collections.unmodifiableSet/List/Map/etc. to avoid this vulnerability.


#### Tags
- /tool/FindBugs
- /general/Security Code Guideline Rules

#### Settings
- Priority=Info


## FB_MMCP
### Default
#### OriginalId=MS_MUTABLE_COLLECTION_PKGPROTECT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Mutable Collection Pkgprotect
#### WarningText
  {1} is a mutable collection which should be package protected

#### HelpText
  A mutable collection instance is assigned to a final static field, thus can be changed by malicious code or by accident from another package. The field could be made package protected to avoid this vulnerability. Alternatively you may wrap this field into Collections.unmodifiableSet/List/Map/etc. to avoid this vulnerability.


#### Tags
- /tool/FindBugs
- /general/Security Code Guideline Rules

#### Settings
- Priority=Info


## FB_MMEF
### Default
#### OriginalId=ME_MUTABLE_ENUM_FIELD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Mutable Enum Field
#### WarningText
  {1} field is public and mutable

#### HelpText
  A mutable public field is defined inside a public enum, thus can be changed by malicious code or by accident from another package. Though mutable enum fields may be used for lazy initialization, it’s a bad practice to expose them to the outer world. Consider declaring this field final and/or package-private.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_MMH
### Default
#### OriginalId=MS_MUTABLE_HASHTABLE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Mutable Hashtable
#### WarningText
  {1} is a mutable Hashtable

#### HelpText
  A final static field references a Hashtable and can be accessed by malicious code or by accident from another package. This code can freely modify the contents of the Hashtable.


#### Tags
- /tool/FindBugs
- /general/Security Code Guideline Rules
- /collection/SEI CERT/OBJ01-J
- /collection/SEI CERT/OBJ13-J
- /collection/CWE/607

#### Settings
- Priority=Info


## FB_MMMF
### Default
#### OriginalId=MF_METHOD_MASKS_FIELD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Method Masks Field
#### WarningText
  {1} defines a variable that obscures field {2.givenClass}

#### HelpText
  This method defines a local variable with the same name as a field in this class or a superclass. This may cause the method to read an uninitialized value from the field, leave the field uninitialized, or both.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_MMN
### Default
#### OriginalId=MWN_MISMATCHED_NOTIFY
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Mismatched Notify
#### WarningText
  Mismatched notify() in {1}

#### HelpText
  This method calls Object.notify() or Object.notifyAll() without obviously holding a lock on the object.  Calling notify() or notifyAll() without a lock held will result in an `IllegalMonitorStateException` being thrown.


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_MMSF
### Default
#### OriginalId=MSF_MUTABLE_SERVLET_FIELD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Mutable Servlet Field
#### WarningText
  {1} is a mutable servlet field

#### HelpText
  A web server generally only creates one instance of servlet or JSP class (i.e., treats the class as a Singleton), and will have multiple threads invoke methods on that instance to service multiple simultaneous requests. Thus, having a mutable instance field generally creates race conditions.


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_MMW
### Default
#### OriginalId=MWN_MISMATCHED_WAIT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Mismatched Wait
#### WarningText
  Mismatched wait() in {1}

#### HelpText
  This method calls Object.wait() without obviously holding a lock on the object.  Calling wait() without a lock held will result in an `IllegalMonitorStateException` being thrown.


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_MOP
### Default
#### OriginalId=MS_OOI_PKGPROTECT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Ooi Pkgprotect
#### WarningText
  {1} should be moved out of an interface and made package protected

#### HelpText
  A final static field that is defined in an interface references a mutable object such as an array or hashtable. This mutable object could be changed by malicious code or by accident from another package. To solve this, the field needs to be moved to a class and made package protected to avoid this vulnerability.


#### Tags
- /tool/FindBugs
- /general/Security Code Guideline Rules
- /collection/SEI CERT/OBJ01-J
- /collection/SEI CERT/OBJ13-J
- /collection/CWE/607

#### Settings
- Priority=Info


## FB_MP
### Default
#### OriginalId=MS_PKGPROTECT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Pkgprotect
#### WarningText
  {1} should be package protected

#### HelpText
  A mutable static field could be changed by malicious code or by accident. The field could be made package protected to avoid this vulnerability.


#### Tags
- /tool/FindBugs
- /general/Security Code Guideline Rules
- /collection/SEI CERT/OBJ01-J
- /collection/CWE/766

#### Settings
- Priority=Info


## FB_MRIA
### Default
#### OriginalId=MS_EXPOSE_REP
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Expose Rep
#### WarningText
  Public static {1} may expose internal representation by returning {2.givenClass}

#### HelpText
  A public static method returns a reference to an array that is part of the static state of the class. Any code that calls this method can freely modify the underlying array. One fix is to return a copy of the array.


#### Tags
- /tool/FindBugs
- /general/Security Code Guideline Rules
- /collection/SEI CERT/OBJ05-J
- /collection/SEI CERT/OBJ13-J
- /collection/CWE/375
- /collection/CWE/582

#### Settings
- Priority=Info


## FB_MSBF
### Default
#### OriginalId=MS_SHOULD_BE_FINAL
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Should Be Final
#### WarningText
  {1} isn't final but should be

#### HelpText
  This static field public but not final, and could be changed by malicious code or by accident from another package. The field could be made final to avoid this vulnerability.


#### Tags
- /tool/FindBugs
- /general/Security Code Guideline Rules
- /collection/SEI CERT/OBJ10-J
- /collection/CWE/493
- /collection/CWE/500

#### Settings
- Priority=Info


## FB_MSBRTBF
### Default
#### OriginalId=MS_SHOULD_BE_REFACTORED_TO_BE_FINAL
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Should Be Refactored To Be Final
#### WarningText
  {1} isn't final but should be refactored to be so

#### HelpText
  This static field public but not final, and could be changed by malicious code or by accident from another package. The field could be made final to avoid this vulnerability. However, the static initializer contains more than one write to the field, so doing so will require some refactoring.


#### Tags
- /tool/FindBugs
- /general/Security Code Guideline Rules
- /collection/SEI CERT/OBJ10-J
- /collection/CWE/493
- /collection/CWE/500

#### Settings
- Priority=Info


## FB_MSOFTGCTF
### Default
#### OriginalId=ML_SYNC_ON_FIELD_TO_GUARD_CHANGING_THAT_FIELD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Sync On Field To Guard Changing That Field
#### WarningText
  Synchronization on {2.givenClass} in futile attempt to guard it

#### HelpText
  This method synchronizes on a field in what appears to be an attempt to guard against simultaneous updates to that field. But guarding a field gets a lock on the referenced object, not on the field. This may not provide the mutual exclusion you need, and other threads might be obtaining locks on the referenced objects (for other purposes). An example of this pattern would be:

  ``` java
  private Long myNtfSeqNbrCounter = new Long(0);
  private Long getNotificationSequenceNumber() {
       Long result = null;
       synchronized(myNtfSeqNbrCounter) {
           result = new Long(myNtfSeqNbrCounter.longValue() + 1);
           myNtfSeqNbrCounter = new Long(result.longValue());
       }
       return result;
  }
  ```


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_MSOUF
### Default
#### OriginalId=ML_SYNC_ON_UPDATED_FIELD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Sync On Updated Field
#### WarningText
  {1} synchronizes on updated field {2.givenClass}

#### HelpText
  This method synchronizes on an object referenced from a mutable field. This is unlikely to have useful semantics, since different threads may be synchronizing on different objects.


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_MSSIF
### Default
#### OriginalId=MTIA_SUSPECT_SERVLET_INSTANCE_FIELD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Suspect Servlet Instance Field
#### WarningText
  Class {0} extends Servlet class and uses instance variables

#### HelpText
  This class extends from a Servlet class, and uses an instance member variable. Since only one instance of a Servlet class is created by the J2EE framework, and used in a multithreaded way, this paradigm is highly discouraged and most likely problematic. Consider only using method local variables.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_MSVUID
### Default
#### OriginalId=SE_NO_SERIALVERSIONID
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=No Serialversionid
#### WarningText
  {0} is Serializable; consider declaring a serialVersionUID

#### HelpText
  This class implements the `Serializable` interface, but does not define a `serialVersionUID` field.  A change as simple as adding a reference to a .class object will add synthetic fields to the class, which will unfortunately change the implicit serialVersionUID (e.g., adding a reference to `String.class` will generate a static field `class$java$lang$String`). Also, different source code to bytecode compilers may use different naming conventions for synthetic variables generated for references to class objects or inner classes. To ensure interoperability of Serializable across versions, consider adding an explicit serialVersionUID.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_MWSNAEC
### Default
#### OriginalId=NM_METHOD_CONSTRUCTOR_CONFUSION
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Method Constructor Confusion
#### WarningText
  {1} was probably intended to be a constructor

#### HelpText
  This regular method has the same name as the class it is defined in. It is likely that this was intended to be a constructor. If it was intended to be a constructor, remove the declaration of a void return value. If you had accidentally defined this method, realized the mistake, defined a proper constructor but can’t get rid of this method due to backwards compatibility, deprecate the method.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_MeNC
### Default
#### OriginalId=NM_METHOD_NAMING_CONVENTION
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Method Naming Convention
#### WarningText
  The method name {1} doesn't start with a lower case letter

#### HelpText
  Methods should be verbs, in mixed case with the first letter lowercase, with the first letter of each internal word capitalized.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_MtSSIF
### Default
#### OriginalId=MTIA_SUSPECT_STRUTS_INSTANCE_FIELD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Suspect Struts Instance Field
#### WarningText
  Class {0} extends Struts Action class and uses instance variables

#### HelpText
  This class extends from a Struts Action class, and uses an instance member variable. Since only one instance of a struts Action class is created by the Struts framework, and used in a multithreaded way, this paradigm is highly discouraged and most likely problematic. Consider only using method local variables. Only instance fields that are written outside of a monitor are reported.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_NAMBN
### Default
#### OriginalId=NP_ARGUMENT_MIGHT_BE_NULL
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Argument Might Be Null
#### WarningText
  {1} does not check for null argument

#### HelpText
  A parameter to this method has been identified as a value that should always be checked to see whether or not it is null, but it is being dereferenced without a preceding null check.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_NAN
### Default
#### OriginalId=NP_ALWAYS_NULL
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Always Null
#### WarningText
  Null pointer dereference of {2.givenClass} in {1}

#### HelpText
  A null pointer is dereferenced here.  This will lead to a `NullPointerException` when the code is executed.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_NANE
### Default
#### OriginalId=NP_ALWAYS_NULL_EXCEPTION
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Always Null Exception
#### WarningText
  Null pointer dereference of {2.givenClass} in {1} on exception path

#### HelpText
  A pointer which is null on an exception path is dereferenced here.  This will lead to a `NullPointerException` when the code is executed.  Note that because SpotBugs currently does not prune infeasible exception paths, this may be a false warning.

  Also note that SpotBugs considers the default case of a switch statement to be an exception path, since the default case is often infeasible.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_NBE
### Default
#### OriginalId=NM_BAD_EQUAL
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Equal
#### WarningText
  Class {0} defines equal(Object); should it be equals(Object)?

#### HelpText
  This class defines a method `equal(Object)`.  This method does not override the `equals(Object)` method in `java.lang.Object`, which is probably what was intended.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_NBRN
### Default
#### OriginalId=NP_BOOLEAN_RETURN_NULL
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Boolean Return Null
#### WarningText
  {1} has Boolean return type and returns explicit null

#### HelpText
  A method that returns either Boolean.TRUE, Boolean.FALSE or null is an accident waiting to happen. This method can be invoked as though it returned a value of type boolean, and the compiler will insert automatic unboxing of the Boolean value. If a null value is returned, this will result in a NullPointerException.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_NC
### Default
#### OriginalId=NM_CONFUSING
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Confusing
#### WarningText
  Confusing to have methods {1} and {3}

#### HelpText
  The referenced methods have names that differ only by capitalization.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_NCN
### Default
#### OriginalId=NP_CLOSING_NULL
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Closing Null
#### WarningText
  Can't close {2.givenClass} since it is always null in {1}

#### HelpText
  close() is being invoked on a value that is always null. If this statement is executed, a null pointer exception will occur. But the big risk here you never close something that should be closed.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_NCNE
### Default
#### OriginalId=NM_CLASS_NOT_EXCEPTION
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Class Not Exception
#### WarningText
  Class {0} is not derived from an Exception, even though it is named as such

#### HelpText
  This class is not derived from another exception, but ends with ‘Exception’. This will be confusing to users of this class.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_NDNSC
### Default
#### OriginalId=NS_DANGEROUS_NON_SHORT_CIRCUIT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Dangerous Non Short Circuit
#### WarningText
  Potentially dangerous use of non-short-circuit logic in {1}

#### HelpText
  This code seems to be using non-short-circuit logic (e.g., & or |) rather than short-circuit logic (&& or ||). In addition, it seem possible that, depending on the value of the left hand side, you might not want to evaluate the right hand side (because it would have side effects, could cause an exception or could be expensive.

  Non-short-circuit logic causes both sides of the expression to be evaluated even when the result can be inferred from knowing the left-hand side. This can be less efficient and can result in errors if the left-hand side guards cases when evaluating the right-hand side can generate an error.

  See [the Java Language Specification](https://docs.oracle.com/javase/specs/jls/se7/html/jls-15.html#jls-15.22.2) for details.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_NDORV
### Default
#### OriginalId=NP_DEREFERENCE_OF_READLINE_VALUE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Dereference Of Readline Value
#### WarningText
  Dereference of the result of readLine() without nullcheck in {1}

#### HelpText
  The result of invoking readLine() is dereferenced without checking to see if the result is null. If there are no more lines of text to read, readLine() will return null and dereferencing that will generate a null pointer exception.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules
- /collection/SEI CERT/EXP01-J

#### Settings
- Priority=Info


## FB_NFKUAI
### Default
#### OriginalId=NM_FUTURE_KEYWORD_USED_AS_IDENTIFIER
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Future Keyword Used As Identifier
#### WarningText
  {1} uses {2} for a variable name, which is a keyword in later versions of Java

#### HelpText
  The identifier is a word that is reserved as a keyword in later versions of Java, and your code will need to be changed in order to compile it in later versions of Java.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_NFKUAMI
### Default
#### OriginalId=NM_FUTURE_KEYWORD_USED_AS_MEMBER_IDENTIFIER
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Future Keyword Used As Member Identifier
#### WarningText
  {1} conflicts with a keyword in a more recent version of Java

#### HelpText
  This identifier is used as a keyword in later versions of Java. This code, and any code that references this API, will need to be changed in order to compile it in later versions of Java.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_NFNC
### Default
#### OriginalId=NM_FIELD_NAMING_CONVENTION
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Field Naming Convention
#### WarningText
  The field name {1} doesn't start with a lower case letter

#### HelpText
  Names of fields that are not final should be in mixed case with a lowercase first letter and the first letters of subsequent words capitalized.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_NGD
### Default
#### OriginalId=NP_GUARANTEED_DEREF
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Guaranteed Deref
#### WarningText
  {2.givenClass} could be null and is guaranteed to be dereferenced in {1}

#### HelpText
  There is a statement or branch that if executed guarantees that a value is null at this point, and that value that is guaranteed to be dereferenced (except on forward paths involving runtime exceptions).

  Note that a check such as `if (x == null) throw new NullPointerException();` is treated as a dereference of `x`.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_NGDOEP
### Default
#### OriginalId=NP_GUARANTEED_DEREF_ON_EXCEPTION_PATH
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Guaranteed Deref On Exception Path
#### WarningText
  {2.name} is null guaranteed to be dereferenced in {1} on exception path

#### HelpText
  There is a statement or branch on an exception path that if executed guarantees that a value is null at this point, and that value that is guaranteed to be dereferenced (except on forward paths involving runtime exceptions).


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_NIDOR
### Default
#### OriginalId=NP_IMMEDIATE_DEREFERENCE_OF_READLINE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Immediate Dereference Of Readline
#### WarningText
  Immediate dereference of the result of readLine() in {1}

#### HelpText
  The result of invoking readLine() is immediately dereferenced. If there are no more lines of text to read, readLine() will return null and dereferencing that will generate a null pointer exception.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_NLOKNV
### Default
#### OriginalId=NP_LOAD_OF_KNOWN_NULL_VALUE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Load Of Known Null Value
#### WarningText
  Load of known null value in {1}

#### HelpText
  The variable referenced at this point is known to be null due to an earlier check against null. Although this is valid, it might be a mistake (perhaps you intended to refer to a different variable, or perhaps the earlier check to see if the variable is null should have been a check to see if it was non-null).


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_NLT
### Default
#### OriginalId=NM_LCASE_TOSTRING
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Lcase Tostring
#### WarningText
  Class {0} defines tostring(); should it be toString()?

#### HelpText
  This class defines a method called `tostring()`.  This method does not override the `toString()` method in `java.lang.Object`, which is probably what was intended.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_NMPTA
### Default
#### OriginalId=NP_METHOD_PARAMETER_TIGHTENS_ANNOTATION
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Method Parameter Tightens Annotation
#### WarningText
  Method {1} overrides the nullness annotation of parameter {2} in an incompatible way

#### HelpText
  A method should always implement the contract of a method it overrides. Thus, if a method takes a parameter that is marked as <span class="citation" data-cites="Nullable">@Nullable</span>, you shouldn’t override that method in a subclass with a method where that parameter is <span class="citation" data-cites="Nonnull">@Nonnull</span>. Doing so violates the contract that the method should handle a null parameter.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_NMRRA
### Default
#### OriginalId=NP_METHOD_RETURN_RELAXING_ANNOTATION
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Method Return Relaxing Annotation
#### WarningText
  Method {1} overrides the return value nullness annotation in an incompatible way.

#### HelpText
  A method should always implement the contract of a method it overrides. Thus, if a method takes is annotated as returning a <span class="citation" data-cites="Nonnull">@Nonnull</span> value, you shouldn’t override that method in a subclass with a method annotated as returning a <span class="citation" data-cites="Nullable">@Nullable</span> or <span class="citation" data-cites="CheckForNull">@CheckForNull</span> value. Doing so violates the contract that the method shouldn’t return null.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_NNFNIIC
### Default
#### OriginalId=NP_NONNULL_FIELD_NOT_INITIALIZED_IN_CONSTRUCTOR
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Nonnull Field Not Initialized In Constructor
#### WarningText
  Non-null field {2.name} is not initialized by {1}

#### HelpText
  The field is marked as non-null, but isn’t written to by the constructor. The field might be initialized elsewhere during constructor, or might always be initialized before use.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_NNI
### Default
#### OriginalId=NP_NULL_INSTANCEOF
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Null Instanceof
#### WarningText
  A known null value is checked to see if it is an instance of {2} in {1}

#### HelpText
  This instanceof test will always return false, since the value being checked is guaranteed to be null. Although this is safe, make sure it isn’t an indication of some misunderstanding or some other logic error.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_NNN
### Default
#### OriginalId=NN_NAKED_NOTIFY
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Naked Notify
#### WarningText
  Naked notify in {1}

#### HelpText
  A call to `notify()` or `notifyAll()` was made without any (apparent) accompanying modification to mutable object state.  In general, calling a notify method on a monitor is done because some condition another thread is waiting for has become true.  However, for the condition to be meaningful, it must involve a heap object that is visible to both threads.

  This bug does not necessarily indicate an error, since the change to mutable object state may have taken place in a method which then called the method containing the notification.


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_NNNN
### Default
#### OriginalId=NO_NOTIFY_NOT_NOTIFYALL
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Notify Not Notifyall
#### WarningText
  Using notify rather than notifyAll in {1}

#### HelpText
  This method calls `notify()` rather than `notifyAll()`.  Java monitors are often used for multiple conditions.  Calling `notify()` only wakes up one thread, meaning that the thread woken up might not be the one waiting for the condition that the caller just satisfied.


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_NNOSP
### Default
#### OriginalId=NP_NULL_ON_SOME_PATH
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Null On Some Path
#### WarningText
  Possible null pointer dereference of {2.givenClass} in {1}

#### HelpText
  There is a branch of statement that, *if executed,* guarantees that a null value will be dereferenced, which would generate a `NullPointerException` when the code is executed. Of course, the problem might be that the branch or statement is infeasible and that the null pointer exception can’t ever be executed; deciding that is beyond the ability of SpotBugs.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_NNOSPE
### Default
#### OriginalId=NP_NULL_ON_SOME_PATH_EXCEPTION
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Null On Some Path Exception
#### WarningText
  Possible null pointer dereference of {2.givenClass} in {1} on exception path

#### HelpText
  A reference value which is null on some exception control path is dereferenced here.  This may lead to a `NullPointerException` when the code is executed.  Note that because SpotBugs currently does not prune infeasible exception paths, this may be a false warning.

  Also note that SpotBugs considers the default case of a switch statement to be an exception path, since the default case is often infeasible.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_NNOSPFRV
### Default
#### OriginalId=NP_NULL_ON_SOME_PATH_FROM_RETURN_VALUE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Null On Some Path From Return Value
#### WarningText
  Possible null pointer dereference in {1} due to return value of called method

#### HelpText
  The return value from a method is dereferenced without a null check, and the return value of that method is one that should generally be checked for null. This may lead to a `NullPointerException` when the code is executed.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_NNOSPMBI
### Default
#### OriginalId=NP_NULL_ON_SOME_PATH_MIGHT_BE_INFEASIBLE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Null On Some Path Might Be Infeasible
#### WarningText
  Possible null pointer dereference of {2.givenClass} on branch that might be infeasible in {1}

#### HelpText
  There is a branch of statement that, *if executed,* guarantees that a null value will be dereferenced, which would generate a `NullPointerException` when the code is executed. Of course, the problem might be that the branch or statement is infeasible and that the null pointer exception can’t ever be executed; deciding that is beyond the ability of SpotBugs. Due to the fact that this value had been previously tested for nullness, this is a definite possibility.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_NNPD
### Default
#### OriginalId=NP_NULL_PARAM_DEREF
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Null Param Deref
#### WarningText
  Null passed for non-null parameter of {2.givenClass} in {1}

#### HelpText
  This method call passes a null value for a non-null method parameter. Either the parameter is annotated as a parameter that should always be non-null, or analysis has shown that it will always be dereferenced.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules
- /collection/SEI CERT/EXP01-J

#### Settings
- Priority=Major


## FB_NNPDATD
### Default
#### OriginalId=NP_NULL_PARAM_DEREF_ALL_TARGETS_DANGEROUS
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Null Param Deref All Targets Dangerous
#### WarningText
  Null passed for non-null parameter of {2.givenClass} in {1}

#### HelpText
  A possibly-null value is passed at a call site where all known target methods require the parameter to be non-null. Either the parameter is annotated as a parameter that should always be non-null, or analysis has shown that it will always be dereferenced.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_NNPDN
### Default
#### OriginalId=NP_NULL_PARAM_DEREF_NONVIRTUAL
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Null Param Deref Nonvirtual
#### WarningText
  Non-virtual method call in {1} passes null for non-null parameter of {2.givenClass}

#### HelpText
  A possibly-null value is passed to a non-null method parameter. Either the parameter is annotated as a parameter that should always be non-null, or analysis has shown that it will always be dereferenced.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_NNPV
### Default
#### OriginalId=NP_NONNULL_PARAM_VIOLATION
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Nonnull Param Violation
#### WarningText
  Null passed for non-null parameter of {2.givenClass} in {1}

#### HelpText
  This method passes a null value as the parameter of a method which must be non-null. Either this parameter has been explicitly marked as <span class="citation" data-cites="Nonnull">@Nonnull</span>, or analysis has determined that this parameter is always dereferenced.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_NNRV
### Default
#### OriginalId=NP_NONNULL_RETURN_VIOLATION
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Nonnull Return Violation
#### WarningText
  {1} may return null, but is declared @Nonnull

#### HelpText
  This method may return a null value, but the method (or a superclass method which it overrides) is declared to return <span class="citation" data-cites="Nonnull">@Nonnull</span>.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_NNSC
### Default
#### OriginalId=NS_NON_SHORT_CIRCUIT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Non Short Circuit
#### WarningText
  Questionable use of non-short-circuit logic in {1}

#### HelpText
  This code seems to be using non-short-circuit logic (e.g., & or |) rather than short-circuit logic (&& or ||). Non-short-circuit logic causes both sides of the expression to be evaluated even when the result can be inferred from knowing the left-hand side. This can be less efficient and can result in errors if the left-hand side guards cases when evaluating the right-hand side can generate an error.

  See [the Java Language Specification](https://docs.oracle.com/javase/specs/jls/se7/html/jls-15.html#jls-15.22.2) for details.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_NORN
### Default
#### OriginalId=NP_OPTIONAL_RETURN_NULL
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Optional Return Null
#### WarningText
  {1} has Optional return type and returns explicit null

#### HelpText
  The usage of Optional return type (java.util.Optional or com.google.common.base.Optional) always means that explicit null returns were not desired by design. Returning a null value in such case is a contract violation and will most likely break client code.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_NPMBNBMAN
### Default
#### OriginalId=NP_PARAMETER_MUST_BE_NONNULL_BUT_MARKED_AS_NULLABLE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Parameter Must Be Nonnull But Marked As Nullable
#### WarningText
  {2} must be non-null but is marked as nullable

#### HelpText
  This parameter is always used in a way that requires it to be non-null, but the parameter is explicitly annotated as being Nullable. Either the use of the parameter or the annotation is wrong.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_NSANCF
### Default
#### OriginalId=NP_SYNC_AND_NULL_CHECK_FIELD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Sync And Null Check Field
#### WarningText
  In {1} the field {2.givenClass} is synchronized on and then checked if null.

#### HelpText
  Since the field is synchronized on, it seems not likely to be null. If it is null and then synchronized on a NullPointerException will be thrown and the check would be pointless. Better to synchronize on another field.


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_NSINF
### Default
#### OriginalId=NP_STORE_INTO_NONNULL_FIELD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Store Into Nonnull Field
#### WarningText
  Store of null value into field {2.givenClass} annotated @Nonnull in {1}

#### HelpText
  A value that could be null is stored into a field that has been annotated as <span class="citation" data-cites="Nonnull">@Nonnull</span>.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_NSSNAI
### Default
#### OriginalId=NM_SAME_SIMPLE_NAME_AS_INTERFACE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Same Simple Name As Interface
#### WarningText
  The class name {0} shadows the simple name of implemented interface {1}

#### HelpText
  This class/interface has a simple name that is identical to that of an implemented/extended interface, except that the interface is in a different package (e.g., `alpha.Foo` extends `beta.Foo`). This can be exceptionally confusing, create lots of situations in which you have to look at import statements to resolve references and creates many opportunities to accidentally define methods that do not override methods in their superclasses.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_NSSNAS
### Default
#### OriginalId=NM_SAME_SIMPLE_NAME_AS_SUPERCLASS
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Same Simple Name As Superclass
#### WarningText
  The class name {0} shadows the simple name of the superclass {1}

#### HelpText
  This class has a simple name that is identical to that of its superclass, except that its superclass is in a different package (e.g., `alpha.Foo` extends `beta.Foo`). This can be exceptionally confusing, create lots of situations in which you have to look at import statements to resolve references and creates many opportunities to accidentally define methods that do not override methods in their superclasses.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_NTCRN
### Default
#### OriginalId=NP_TOSTRING_COULD_RETURN_NULL
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Tostring Could Return Null
#### WarningText
  {1} may return null

#### HelpText
  This toString method seems to return null in some circumstances. A liberal reading of the spec could be interpreted as allowing this, but it is probably a bad idea and could cause other code to break. Return the empty string or some other appropriate string rather than null.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules
- /collection/SEI CERT/EXP01-J

#### Settings
- Priority=Major


## FB_NUF
### Default
#### OriginalId=NP_UNWRITTEN_FIELD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unwritten Field
#### WarningText
  Read of unwritten field {2.name} in {1}

#### HelpText
  The program is dereferencing a field that does not seem to ever have a non-null value written to it. Unless the field is initialized via some mechanism not seen by the analysis, dereferencing this value will generate a null pointer exception.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_NUPOPF
### Default
#### OriginalId=NP_UNWRITTEN_PUBLIC_OR_PROTECTED_FIELD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unwritten Public Or Protected Field
#### WarningText
  Read of unwritten public or protected field {2.name} in {1}

#### HelpText
  The program is dereferencing a public or protected field that does not seem to ever have a non-null value written to it. Unless the field is initialized via some mechanism not seen by the analysis, dereferencing this value will generate a null pointer exception.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_NVC
### Default
#### OriginalId=NM_VERY_CONFUSING
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Very Confusing
#### WarningText
  VERY confusing to have methods {1} and {3}

#### HelpText
  The referenced methods have names that differ only by capitalization. This is very confusing because if the capitalization were identical then one of the methods would override the other.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_NVCI
### Default
#### OriginalId=NM_VERY_CONFUSING_INTENTIONAL
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Very Confusing Intentional
#### WarningText
  VERY confusing (but perhaps intentional) to have methods {1} and {3}

#### HelpText
  The referenced methods have names that differ only by capitalization. This is very confusing because if the capitalization were identical then one of the methods would override the other. From the existence of other methods, it seems that the existence of both of these methods is intentional, but is sure is confusing. You should try hard to eliminate one of them, unless you are forced to have both due to frozen APIs.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_NWP
### Default
#### OriginalId=NM_WRONG_PACKAGE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Wrong Package
#### WarningText
  {1} doesn't override method in superclass because parameter type {4} doesn't match superclass parameter type {5}

#### HelpText
  The method in the subclass doesn’t override a similar method in a superclass because the type of a parameter doesn’t exactly match the type of the corresponding parameter in the superclass. For example, if you have:

  ``` java
  import alpha.Foo;

  public class A {
      public int f(Foo x) { return 17; }
  }
  ----
  import beta.Foo;

  public class B extends A {
      public int f(Foo x) { return 42; }
  }
  ```

  The `f(Foo)` method defined in class `B` doesn’t override the `f(Foo)` method defined in class `A`, because the argument types are `Foo`’s from different packages.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_NWPI
### Default
#### OriginalId=NM_WRONG_PACKAGE_INTENTIONAL
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Wrong Package Intentional
#### WarningText
  {1} doesn't override method in superclass because parameter type {4} doesn't match superclass parameter type {5}

#### HelpText
  The method in the subclass doesn’t override a similar method in a superclass because the type of a parameter doesn’t exactly match the type of the corresponding parameter in the superclass. For example, if you have:

  ``` java
  import alpha.Foo;

  public class A {
      public int f(Foo x) { return 17; }
  }
  ----
  import beta.Foo;

  public class B extends A {
      public int f(Foo x) { return 42; }
      public int f(alpha.Foo x) { return 27; }
  }
  ```

  The `f(Foo)` method defined in class `B` doesn’t override the `f(Foo)` method defined in class `A`, because the argument types are `Foo`’s from different packages.

  In this case, the subclass does define a method with a signature identical to the method in the superclass, so this is presumably understood. However, such methods are exceptionally confusing. You should strongly consider removing or deprecating the method with the similar but not identical signature.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_OMMIS
### Default
#### OriginalId=OVERRIDING_METHODS_MUST_INVOKE_SUPER
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Methods Must Invoke Super
#### WarningText
  Super method is annotated with @OverridingMethodsMustInvokeSuper, but {1} isn't calling the super method.

#### HelpText
  Super method is annotated with <span class="citation" data-cites="OverridingMethodsMustInvokeSuper">@OverridingMethodsMustInvokeSuper</span>, but the overriding method isn’t calling the super method.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_OODR
### Default
#### OriginalId=ODR_OPEN_DATABASE_RESOURCE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Open Database Resource
#### WarningText
  {1} may fail to close {2.excludingPackage}

#### HelpText
  The method creates a database resource (such as a database connection or row set), does not assign it to any fields, pass it to other methods, or return it, and does not appear to close the object on all paths out of the method.  Failure to close database resources on all paths out of a method may result in poor performance, and could cause the application to have problems communicating with the database.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_OODREP
### Default
#### OriginalId=ODR_OPEN_DATABASE_RESOURCE_EXCEPTION_PATH
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Open Database Resource Exception Path
#### WarningText
  {1} may fail to close database resource on exception

#### HelpText
  The method creates a database resource (such as a database connection or row set), does not assign it to any fields, pass it to other methods, or return it, and does not appear to close the object on all exception paths out of the method.  Failure to close database resources on all paths out of a method may result in poor performance, and could cause the application to have problems communicating with the database.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_OOS
### Default
#### OriginalId=OS_OPEN_STREAM
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Open Stream
#### WarningText
  {1} may fail to close stream

#### HelpText
  The method creates an IO stream object, does not assign it to any fields, pass it to other methods that might close it, or return it, and does not appear to close the stream on all paths out of the method.  This may result in a file descriptor leak.  It is generally a good idea to use a `finally` block to ensure that streams are closed.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_OOSEP
### Default
#### OriginalId=OS_OPEN_STREAM_EXCEPTION_PATH
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Open Stream Exception Path
#### WarningText
  {1} may fail to close stream on exception

#### HelpText
  The method creates an IO stream object, does not assign it to any fields, pass it to other methods, or return it, and does not appear to close it on all possible exception paths out of the method.  This may result in a file descriptor leak.  It is generally a good idea to use a `finally` block to ensure that streams are closed.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_OTAC
### Default
#### OriginalId=ITA_INEFFICIENT_TO_ARRAY
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=Inefficient To Array
#### WarningText
  {1} uses Collection.toArray() with zero-length array argument

#### HelpText
  This method uses the toArray() method of a collection derived class, and passes in a zero-length prototype array argument. It is more efficient to use \`myCollection.toArray(new Foo\[myCollection.size()\])\` If the array passed in is big enough to store all of the elements of the collection, then it is populated and returned directly. This avoids the need to create a second array (by reflection) to return as the result.


#### Tags
- /tool/FindBugs
- /general/Optimization Rules

#### Settings
- Priority=Major


## FB_OUO
### Default
#### OriginalId=OBL_UNSATISFIED_OBLIGATION
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=Unsatisfied Obligation
#### WarningText
  {1} may fail to clean up {2}

#### HelpText
  This method may fail to clean up (close, dispose of) a stream, database object, or other resource requiring an explicit cleanup operation. In general, if a method opens a stream or other resource, the method should use a try/finally block to ensure that the stream or resource is cleaned up before the method returns. This bug pattern is essentially the same as the OS\\\_OPEN\\\_STREAM and ODR\\\_OPEN\\\_DATABASE\\\_RESOURCE bug patterns, but is based on a different (and hopefully better) static analysis technique. We are interested is getting feedback about the usefulness of this bug pattern. For sending feedback, check: - \[contributing guideline\](https://github.com/spotbugs/spotbugs/blob/master/CONTRIBUTING.md) - \[malinglist\](https://github.com/spotbugs/discuss/issues?q=) In particular, the false-positive suppression heuristics for this bug pattern have not been extensively tuned, so reports about false positives are helpful to us. See Weimer and Necula, \*Finding and Preventing Run-Time Error Handling Mistakes\*, for a description of the analysis technique.


#### Tags
- /tool/FindBugs
- /general/Experimental Rules

#### Settings
- Priority=Info


## FB_OUOEE
### Default
#### OriginalId=OBL_UNSATISFIED_OBLIGATION_EXCEPTION_EDGE
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=Unsatisfied Obligation Exception Edge
#### WarningText
  {1} may fail to clean up {2} on checked exception

#### HelpText
  This method may fail to clean up (close, dispose of) a stream, database object, or other resource requiring an explicit cleanup operation. In general, if a method opens a stream or other resource, the method should use a try/finally block to ensure that the stream or resource is cleaned up before the method returns. This bug pattern is essentially the same as the OS\\\_OPEN\\\_STREAM and ODR\\\_OPEN\\\_DATABASE\\\_RESOURCE bug patterns, but is based on a different (and hopefully better) static analysis technique. We are interested is getting feedback about the usefulness of this bug pattern. For sending feedback, check: - \[contributing guideline\](https://github.com/spotbugs/spotbugs/blob/master/CONTRIBUTING.md) - \[malinglist\](https://github.com/spotbugs/discuss/issues?q=) In particular, the false-positive suppression heuristics for this bug pattern have not been extensively tuned, so reports about false positives are helpful to us. See Weimer and Necula, \*Finding and Preventing Run-Time Error Handling Mistakes\*, for a description of the analysis technique.


#### Tags
- /tool/FindBugs
- /general/Experimental Rules

#### Settings
- Priority=Info


## FB_PAPT
### Default
#### OriginalId=PT_ABSOLUTE_PATH_TRAVERSAL
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Absolute Path Traversal
#### WarningText
  Absolute path traversal in {1}

#### HelpText
  The software uses an HTTP request parameter to construct a pathname that should be within a restricted directory, but it does not properly neutralize absolute path sequences such as “/abs/path” that can resolve to a location that is outside of that directory. See <a href="http://cwe.mitre.org/data/definitions/36.html" class="uri" class="uri">http://cwe.mitre.org/data/definitions/36.html</a> for more information.

  SpotBugs looks only for the most blatant, obvious cases of absolute path traversal. If SpotBugs found *any*, you *almost certainly* have more vulnerabilities that SpotBugs doesn’t report. If you are concerned about absolute path traversal, you should seriously consider using a commercial static analysis or pen-testing tool.


#### Tags
- /tool/FindBugs
- /general/Vulnerability Rules
- /collection/SEI CERT/FIO16-J
- /collection/CWE/36
- /collection/CWE/22
- /collection/CWE/647
- /collection/CWE/171
- /collection/OWASP/A01:2021

#### Settings
- Priority=Major


## FB_PCI
### Default
#### OriginalId=CN_IDIOM_NO_SUPER_CALL
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Idiom No Super Call
#### WarningText
  {1} does not call super.clone()

#### HelpText
  This non-final class defines a clone() method that does not call super.clone(). If this class (“*A*”) is extended by a subclass (“*B*”), and the subclass *B* calls super.clone(), then it is likely that *B*’s clone() method will return an object of type *A*, which violates the standard contract for clone().

  If all clone() methods call super.clone(), then they are guaranteed to use Object.clone(), which always returns an object of the correct type.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_PDREOII
### Default
#### OriginalId=PZ_DONT_REUSE_ENTRY_OBJECTS_IN_ITERATORS
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Dont Reuse Entry Objects In Iterators
#### WarningText
  {0} is both an Iterator and a Map.Entry

#### HelpText
  The entrySet() method is allowed to return a view of the underlying Map in which an Iterator and Map.Entry. This clever idea was used in several Map implementations, but introduces the possibility of nasty coding mistakes. If a map `m` returns such an iterator for an entrySet, then `c.addAll(m.entrySet())` will go badly wrong. All of the Map implementations in OpenJDK 1.7 have been rewritten to avoid this, you should to.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_PPS
### Default
#### OriginalId=PS_PUBLIC_SEMAPHORES
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Public Semaphores
#### WarningText
  Class {0} exposes synchronization and semaphores in its public interface

#### HelpText
  This class uses synchronization along with wait(), notify() or notifyAll() on itself (the this reference). Client classes that use this class, may, in addition, use an instance of this class as a synchronizing object. Because two classes are using the same object for synchronization, Multithread correctness is suspect. You should not synchronize nor call semaphore methods on a public reference. Consider using a internal private member variable to control synchronization.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_PPZLA
### Default
#### OriginalId=PZLA_PREFER_ZERO_LENGTH_ARRAYS
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Prefer Zero Length Arrays
#### WarningText
  Should {1} return a zero length array rather than null?

#### HelpText
  It is often a better design to return a length zero array rather than a null reference to indicate that there are no results (i.e., an empty list of results). This way, no explicit check for null is needed by clients of the method.

  On the other hand, using null to indicate “there is no answer to this question” is probably appropriate. For example, `File.listFiles()` returns an empty list if given a directory containing no files, and returns null if the file is not a directory.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_PRPT
### Default
#### OriginalId=PT_RELATIVE_PATH_TRAVERSAL
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Relative Path Traversal
#### WarningText
  Relative path traversal in {1}

#### HelpText
  The software uses an HTTP request parameter to construct a pathname that should be within a restricted directory, but it does not properly neutralize sequences such as “..” that can resolve to a location that is outside of that directory. See <a href="http://cwe.mitre.org/data/definitions/23.html" class="uri" class="uri">http://cwe.mitre.org/data/definitions/23.html</a> for more information.

  SpotBugs looks only for the most blatant, obvious cases of relative path traversal. If SpotBugs found *any*, you *almost certainly* have more vulnerabilities that SpotBugs doesn’t report. If you are concerned about relative path traversal, you should seriously consider using a commercial static analysis or pen-testing tool.


#### Tags
- /tool/FindBugs
- /general/Vulnerability Rules
- /collection/SEI CERT/FIO16-J
- /collection/CWE/23
- /collection/CWE/171
- /collection/CWE/647
- /collection/OWASP/A01:2021

#### Settings
- Priority=Major


## FB_QQBA
### Default
#### OriginalId=QBA_QUESTIONABLE_BOOLEAN_ASSIGNMENT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Questionable Boolean Assignment
#### WarningText
  {1} assigns boolean literal in boolean expression

#### HelpText
  This method assigns a literal boolean value (true or false) to a boolean variable inside an if or while expression. Most probably this was supposed to be a boolean comparison using ==, not an assignment using =.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_QQFL
### Default
#### OriginalId=QF_QUESTIONABLE_FOR_LOOP
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Questionable For Loop
#### WarningText
  Complicated, subtle or wrong increment in for-loop {1}

#### HelpText
  Are you sure this for loop is incrementing the correct variable? It appears that another variable is being initialized and checked by the for loop.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_R0TI
### Default
#### OriginalId=RV_01_TO_INT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=01 To Int
#### WarningText
  {1} uses generates a random value from 0 to 1 and then coerces that value to the integer 0

#### HelpText
  A random value from 0 to 1 is being coerced to the integer value 0. You probably want to multiply the random value by something else before coercing it to an integer, or use the `Random.nextInt(n)` method.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_RAI
### Default
#### OriginalId=RANGE_ARRAY_INDEX
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Array Index
#### WarningText
  Array index is out of bounds: {3}

#### HelpText
  Array operation is performed, but array index is out of bounds, which will result in ArrayIndexOutOfBoundsException at runtime.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Critical


## FB_RAL
### Default
#### OriginalId=RANGE_ARRAY_LENGTH
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Array Length
#### WarningText
  Array length is out of bounds: {3}

#### HelpText
  Method is called with array parameter and length parameter, but the length is out of bounds. This will result in IndexOutOfBoundsException at runtime.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Critical


## FB_RAO
### Default
#### OriginalId=RANGE_ARRAY_OFFSET
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Array Offset
#### WarningText
  Array offset is out of bounds: {3}

#### HelpText
  Method is called with array parameter and offset parameter, but the offset is out of bounds. This will result in IndexOutOfBoundsException at runtime.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Critical


## FB_RAVOH
### Default
#### OriginalId=RV_ABSOLUTE_VALUE_OF_HASHCODE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Absolute Value Of Hashcode
#### WarningText
  Bad attempt to compute absolute value of signed 32-bit hashcode in {1}

#### HelpText
  This code generates a hashcode and then computes the absolute value of that hashcode. If the hashcode is `Integer.MIN_VALUE`, then the result will be negative as well (since `Math.abs(Integer.MIN_VALUE) == Integer.MIN_VALUE`).

  One out of 2^32 strings have a hashCode of Integer.MIN\_VALUE, including “polygenelubricants” “GydZG\_” and “”DESIGNING WORKHOUSES“.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_RAVORI
### Default
#### OriginalId=RV_ABSOLUTE_VALUE_OF_RANDOM_INT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Absolute Value Of Random Int
#### WarningText
  Bad attempt to compute absolute value of signed random integer in {1}

#### HelpText
  This code generates a random signed integer and then computes the absolute value of that random integer. If the number returned by the random number generator is `Integer.MIN_VALUE`, then the result will be negative as well (since `Math.abs(Integer.MIN_VALUE) == Integer.MIN_VALUE`). (Same problem arises for long values as well).


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_RBSFRE
### Default
#### OriginalId=RE_BAD_SYNTAX_FOR_REGULAR_EXPRESSION
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Syntax For Regular Expression
#### WarningText
  Invalid syntax for regular expression in {1}

#### HelpText
  The code here uses a regular expression that is invalid according to the syntax for regular expressions. This statement will throw a PatternSyntaxException when executed.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_RCCFSRV
### Default
#### OriginalId=RV_CHECK_COMPARETO_FOR_SPECIFIC_RETURN_VALUE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Check Compareto For Specific Return Value
#### WarningText
  Check to see if return value of {2.givenClass} is equal to {3}

#### HelpText
  This code invoked a compareTo or compare method, and checks to see if the return value is a specific value, such as 1 or -1. When invoking these methods, you should only check the sign of the result, not for any specific non-zero value. While many or most compareTo and compare methods only return -1, 0 or 1, some of them will return other values.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_RCE
### Default
#### OriginalId=REC_CATCH_EXCEPTION
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Catch Exception
#### WarningText
  Exception is caught when Exception is not thrown in {1}

#### HelpText
  This method uses a try-catch block that catches Exception objects, but Exception is not thrown within the try block, and RuntimeException is not explicitly caught. It is a common bug pattern to say try { … } catch (Exception e) { something } as a shorthand for catching a number of types of exception each of whose catch blocks is identical, but this construct also accidentally catches RuntimeException as well, masking potential bugs.

  A better approach is to either explicitly catch the specific exceptions that are thrown, or to explicitly catch RuntimeException exception, rethrow it, and then catch all non-Runtime Exceptions, as shown below:

  ``` java
  try {
      ...
  } catch (RuntimeException e) {
      throw e;
  } catch (Exception e) {
      ... deal with all non-runtime exceptions ...
  }
  ```


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_RCFPI
### Default
#### OriginalId=RV_CHECK_FOR_POSITIVE_INDEXOF
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Check For Positive Indexof
#### WarningText
  {1} checks to see if result of String.indexOf is positive

#### HelpText
  The method invokes String.indexOf and checks to see if the result is positive or non-positive. It is much more typical to check to see if the result is negative or non-negative. It is positive only if the substring checked for occurs at some place other than at the beginning of the String.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_RCUFSARE
### Default
#### OriginalId=RE_CANT_USE_FILE_SEPARATOR_AS_REGULAR_EXPRESSION
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Cant Use File Separator As Regular Expression
#### WarningText
  File.separator used for regular expression in {1}

#### HelpText
  The code here uses `File.separator` where a regular expression is required. This will fail on Windows platforms, where the `File.separator` is a backslash, which is interpreted in a regular expression as an escape character. Among other options, you can just use `File.separatorChar=='\\' ? "\\\\" : File.separator` instead of `File.separator`


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_RDJNCR
### Default
#### OriginalId=RV_DONT_JUST_NULL_CHECK_READLINE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Dont Just Null Check Readline
#### WarningText
  {1} discards result of readLine after checking if it is non-null

#### HelpText
  The value returned by readLine is discarded after checking to see if the return value is non-null. In almost all situations, if the result is non-null, you will want to use that non-null value. Calling readLine again will give you a different line.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_REARTN
### Default
#### OriginalId=NP_CLONE_COULD_RETURN_NULL
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Clone Could Return Null
#### WarningText
  {1} may return null

#### HelpText
  This clone method seems to return null in some circumstances, but clone is never allowed to return a null value. If you are convinced this path is unreachable, throw an AssertionError instead.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_RENT
### Default
#### OriginalId=RV_EXCEPTION_NOT_THROWN
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Exception Not Thrown
#### WarningText
  {2.givenClass} not thrown in {1}

#### HelpText
  This code creates an exception (or error) object, but doesn’t do anything with it. For example, something like

  ``` java
  if (x < 0) {
      new IllegalArgumentException("x must be nonnegative");
  }
  ```

  It was probably the intent of the programmer to throw the created exception:

  ``` java
  if (x < 0) {
      throw new IllegalArgumentException("x must be nonnegative");
  }
  ```


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_RNC
### Default
#### OriginalId=RR_NOT_CHECKED
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Not Checked
#### WarningText
  {1} ignores result of {2}

#### HelpText
  This method ignores the return value of one of the variants of \`java.io.InputStream.read()\` which can return multiple bytes.  If the return value is not checked, the caller will not be able to correctly handle the case where fewer bytes were read than the caller requested.  This is a particularly insidious kind of bug, because in many programs, reads from input streams usually do read the full amount of data requested, causing the program to fail only sporadically.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_RNROC
### Default
#### OriginalId=RV_NEGATING_RESULT_OF_COMPARETO
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Negating Result Of Compareto
#### WarningText
  {1} negates the return value of {2}

#### HelpText
  This code negatives the return value of a compareTo or compare method. This is a questionable or bad programming practice, since if the return value is Integer.MIN\_VALUE, negating the return value won’t negate the sign of the result. You can achieve the same intended result by reversing the order of the operands rather than by negating the results.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_RPUP
### Default
#### OriginalId=RE_POSSIBLE_UNINTENDED_PATTERN
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Possible Unintended Pattern
#### WarningText
  "." or "|" used for regular expression in {1}

#### HelpText
  A String function is being invoked and “.” or “|” is being passed to a parameter that takes a regular expression as an argument. Is this what you intended? For example

  -   s.replaceAll(“.”, “/”) will return a String in which *every* character has been replaced by a ‘/’ character
  -   s.split(“.”) *always* returns a zero length array of String
  -   “ab|cd”.replaceAll(“|”, “/”) will return “/a/b/|/c/d/”
  -   “ab|cd”.split(“|”) will return array with six (!) elements: \[, a, b, |, c, d\]



#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_RRC
### Default
#### OriginalId=RC_REF_COMPARISON
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Ref Comparison
#### WarningText
  Suspicious comparison of {2} references in {1}

#### HelpText
  This method compares two reference values using the == or != operator, where the correct way to compare instances of this type is generally with the equals() method. It is possible to create distinct instances that are equal but do not compare as == since they are different objects. Examples of classes which should generally not be compared by reference are java.lang.Integer, java.lang.Float, etc.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_RRCBP
### Default
#### OriginalId=RC_REF_COMPARISON_BAD_PRACTICE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Ref Comparison Bad Practice
#### WarningText
  Suspicious comparison of a {2} reference to constant in {1}

#### HelpText
  This method compares a reference value to a constant using the == or != operator, where the correct way to compare instances of this type is generally with the equals() method. It is possible to create distinct instances that are equal but do not compare as == since they are different objects. Examples of classes which should generally not be compared by reference are java.lang.Integer, java.lang.Float, etc.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_RRCBPB
### Default
#### OriginalId=RC_REF_COMPARISON_BAD_PRACTICE_BOOLEAN
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Ref Comparison Bad Practice Boolean
#### WarningText
  Suspicious comparison of Boolean references in {1}

#### HelpText
  This method compares two Boolean values using the == or != operator. Normally, there are only two Boolean values (Boolean.TRUE and Boolean.FALSE), but it is possible to create other Boolean objects using the `new Boolean(b)` constructor. It is best to avoid such objects, but if they do exist, then checking Boolean objects for equality using == or != will give results than are different than you would get using `.equals(...)`.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_RRCONANV
### Default
#### OriginalId=RCN_REDUNDANT_COMPARISON_OF_NULL_AND_NONNULL_VALUE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Redundant Comparison Of Null And Nonnull Value
#### WarningText
  Redundant comparison of non-null value to null in {1}

#### HelpText
  This method contains a reference known to be non-null with another reference known to be null.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_RRCT
### Default
#### OriginalId=RpC_REPEATED_CONDITIONAL_TEST
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Repeated Conditional Test
#### WarningText
  Repeated conditional test in {1}

#### HelpText
  The code contains a conditional test is performed twice, one right after the other (e.g., `x == 0 || x == 0`). Perhaps the second occurrence is intended to be something else (e.g., `x == 0 || y == 0`).


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_RRCTNV
### Default
#### OriginalId=RCN_REDUNDANT_COMPARISON_TWO_NULL_VALUES
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Redundant Comparison Two Null Values
#### WarningText
  Redundant comparison of two null values in {1}

#### HelpText
  This method contains a redundant comparison of two references known to both be definitely null.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_RRI
### Default
#### OriginalId=RI_REDUNDANT_INTERFACES
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Redundant Interfaces
#### WarningText
  Class {0} implements same interface as superclass

#### HelpText
  This class declares that it implements an interface that is also implemented by a superclass. This is redundant because once a superclass implements an interface, all subclasses by default also implement this interface. It may point out that the inheritance hierarchy has changed since this class was created, and consideration should be given to the ownership of the interface’s implementation.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_RRNONV
### Default
#### OriginalId=RCN_REDUNDANT_NULLCHECK_OF_NONNULL_VALUE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Redundant Nullcheck Of Nonnull Value
#### WarningText
  Redundant nullcheck of {2}, which is known to be non-null in {1}

#### HelpText
  This method contains a redundant check of a known non-null value against the constant null.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_RRNWHBAN
### Default
#### OriginalId=RCN_REDUNDANT_NULLCHECK_WOULD_HAVE_BEEN_A_NPE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Redundant Nullcheck Would Have Been A Npe
#### WarningText
  Nullcheck of {2.givenClass} at {4.lineNumber} of value previously dereferenced in {1}

#### HelpText
  A value is checked here to see whether it is null, but this value can’t be null because it was previously dereferenced and if it were null a null pointer exception would have occurred at the earlier dereference. Essentially, this code and the previous dereference disagree as to whether this value is allowed to be null. Either the check is redundant or the previous dereference is erroneous.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_RROH
### Default
#### OriginalId=RV_REM_OF_HASHCODE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Rem Of Hashcode
#### WarningText
  Remainder of hashCode could be negative in {1}

#### HelpText
  This code computes a hashCode, and then computes the remainder of that value modulo another value. Since the hashCode can be negative, the result of the remainder operation can also be negative.

  Assuming you want to ensure that the result of your computation is nonnegative, you may need to change your code. If you know the divisor is a power of 2, you can use a bitwise and operator instead (i.e., instead of using `x.hashCode()%n`, use `x.hashCode()&(n-1)`). This is probably faster than computing the remainder as well. If you don’t know that the divisor is a power of 2, take the absolute value of the result of the remainder operation (i.e., use `Math.abs(x.hashCode()%n)`).


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_RRORI
### Default
#### OriginalId=RV_REM_OF_RANDOM_INT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Rem Of Random Int
#### WarningText
  Remainder of 32-bit signed random integer computed in {1}

#### HelpText
  This code generates a random signed integer and then computes the remainder of that value modulo another value. Since the random number can be negative, the result of the remainder operation can also be negative. Be sure this is intended, and strongly consider using the Random.nextInt(int) method instead.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_RRS
### Default
#### OriginalId=RS_READOBJECT_SYNC
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Readobject Sync
#### WarningText
  {0}'s readObject method is synchronized

#### HelpText
  This serializable class defines a `readObject()` which is synchronized.  By definition, an object created by deserialization is only reachable by one thread, and thus there is no need for `readObject()` to be synchronized.  If the `readObject()` method itself is causing the object to become visible to another thread, that is an example of very dubious coding style.


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_RRVI
### Default
#### OriginalId=RV_RETURN_VALUE_IGNORED
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Return Value Ignored
#### WarningText
  Return value of {2.givenClass} ignored in {1}

#### HelpText
  The return value of this method should be checked. One common cause of this warning is to invoke a method on an immutable object, thinking that it updates the object. For example, in the following code fragment,

  ``` java
  String dateString = getHeaderField(name);
  dateString.trim();
  ```

  the programmer seems to be thinking that the trim() method will update the String referenced by dateString. But since Strings are immutable, the trim() function returns a new String value, which is being ignored here. The code should be corrected to:

  ``` java
  String dateString = getHeaderField(name);
  dateString = dateString.trim();
  ```


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_RRVIBP
### Default
#### OriginalId=RV_RETURN_VALUE_IGNORED_BAD_PRACTICE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Return Value Ignored Bad Practice
#### WarningText
  Exceptional return value of {2} ignored in {1}

#### HelpText
  This method returns a value that is not checked. The return value should be checked since it can indicate an unusual or unexpected function execution. For example, the `File.delete()` method returns false if the file could not be successfully deleted (rather than throwing an Exception). If you don’t check the result, you won’t notice if the method invocation signals unexpected behavior by returning an atypical return value.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_RRVII
### Default
#### OriginalId=RV_RETURN_VALUE_IGNORED_INFERRED
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Return Value Ignored Inferred
#### WarningText
  Return value of {2.givenClass} ignored, is this OK in {1}

#### HelpText
  This code calls a method and ignores the return value. The return value is the same type as the type the method is invoked on, and from our analysis it looks like the return value might be important (e.g., like ignoring the return value of `String.toLowerCase()`).

  We are guessing that ignoring the return value might be a bad idea just from a simple analysis of the body of the method. You can use a <span class="citation" data-cites="CheckReturnValue">@CheckReturnValue</span> annotation to instruct SpotBugs as to whether ignoring the return value of this method is important or acceptable.

  Please investigate this closely to decide whether it is OK to ignore the return value.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_RRVINSE
### Default
#### OriginalId=RV_RETURN_VALUE_IGNORED_NO_SIDE_EFFECT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Return Value Ignored No Side Effect
#### WarningText
  Return value of {2.givenClass} ignored, but method has no side effect

#### HelpText
  This code calls a method and ignores the return value. However our analysis shows that the method (including its implementations in subclasses if any) does not produce any effect other than return value. Thus this call can be removed.

  We are trying to reduce the false positives as much as possible, but in some cases this warning might be wrong. Common false-positive cases include:

  -   The method is designed to be overridden and produce a side effect in other projects which are out of the scope of the analysis.

  -   The method is called to trigger the class loading which may have a side effect.

  -   The method is called just to get some exception.

  If you feel that our assumption is incorrect, you can use a <span class="citation" data-cites="CheckReturnValue">@CheckReturnValue</span> annotation to instruct SpotBugs that ignoring the return value of this method is acceptable.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_RRVOPI
### Default
#### OriginalId=RV_RETURN_VALUE_OF_PUTIFABSENT_IGNORED
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Return Value Of Putifabsent Ignored
#### WarningText
  Return value of putIfAbsent is ignored, but {4} is reused in {1}

#### HelpText
  The `putIfAbsent` method is typically used to ensure that a single value is associated with a given key (the first value for which put if absent succeeds). If you ignore the return value and retain a reference to the value passed in, you run the risk of retaining a value that is not the one that is associated with the key in the map. If it matters which one you use and you use the one that isn’t stored in the map, your program will behave incorrectly.


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_RSI
### Default
#### OriginalId=RANGE_STRING_INDEX
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=String Index
#### WarningText
  String index is out of bounds when calling {5}: {3}

#### HelpText
  String method is called and specified string index is out of bounds. This will result in StringIndexOutOfBoundsException at runtime.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Critical


## FB_RcRNONV
### Default
#### OriginalId=RCN_REDUNDANT_NULLCHECK_OF_NULL_VALUE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Redundant Nullcheck Of Null Value
#### WarningText
  Redundant nullcheck of {2} which is known to be null in {1}

#### HelpText
  This method contains a redundant check of a known null value against the constant null.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_SBF
### Default
#### OriginalId=SE_BAD_FIELD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Field
#### WarningText
  Class {0} defines non-transient non-serializable instance field {1.name}

#### HelpText
  This Serializable class defines a non-primitive instance field which is neither transient, Serializable, or `java.lang.Object`, and does not appear to implement the `Externalizable` interface or the `readObject()` and `writeObject()` methods.  Objects of this class will not be deserialized correctly if a non-Serializable object is stored in this field.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_SBFIC
### Default
#### OriginalId=SE_BAD_FIELD_INNER_CLASS
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Field Inner Class
#### WarningText
  {0} is serializable but also an inner class of a non-serializable class

#### HelpText
  This Serializable class is an inner class of a non-serializable class. Thus, attempts to serialize it will also attempt to associate instance of the outer class with which it is associated, leading to a runtime error.

  If possible, making the inner class a static inner class should solve the problem. Making the outer class serializable might also work, but that would mean serializing an instance of the inner class would always also serialize the instance of the outer class, which it often not what you really want.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_SBFS
### Default
#### OriginalId=SE_BAD_FIELD_STORE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Field Store
#### WarningText
  {2} stored into non-transient field {1.givenClass}

#### HelpText
  A non-serializable value is stored into a non-transient field of a serializable class.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_SBPSA
### Default
#### OriginalId=SQL_BAD_PREPARED_STATEMENT_ACCESS
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Prepared Statement Access
#### WarningText
  {1} attempts to access a prepared statement parameter with index 0

#### HelpText
  A call to a setXXX method of a prepared statement was made where the parameter index is 0. As parameter indexes start at index 1, this is always a mistake.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_SBRA
### Default
#### OriginalId=SQL_BAD_RESULTSET_ACCESS
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Bad Resultset Access
#### WarningText
  {1} attempts to access a result set field with index 0

#### HelpText
  A call to getXXX or updateXXX methods of a result set was made where the field index is 0. As ResultSet fields start at index 1, this is always a mistake.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_SCSBS
### Default
#### OriginalId=SE_COMPARATOR_SHOULD_BE_SERIALIZABLE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Comparator Should Be Serializable
#### WarningText
  {0} implements Comparator but not Serializable

#### HelpText
  This class implements the `Comparator` interface. You should consider whether or not it should also implement the `Serializable` interface. If a comparator is used to construct an ordered collection such as a `TreeMap`, then the `TreeMap` will be serializable only if the comparator is also serializable. As most comparators have little or no state, making them serializable is generally easy and good defensive programming.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_SCTB
### Default
#### OriginalId=SKIPPED_CLASS_TOO_BIG
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=Class Too Big
#### WarningText
  {0} is too big for analysis

#### HelpText
  This class is bigger than can be effectively handled, and was not fully analyzed for errors.


#### Tags
- /tool/FindBugs
- /general/Experimental Rules

#### Settings
- Priority=Info


## FB_SDSDTSF
### Default
#### OriginalId=SF_DEAD_STORE_DUE_TO_SWITCH_FALLTHROUGH
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Dead Store Due To Switch Fallthrough
#### WarningText
  Value of {2.givenClass} from previous case is overwritten here due to switch statement fall through

#### HelpText
  A value stored in the previous switch case is overwritten here due to a switch fall through. It is likely that you forgot to put a break or return at the end of the previous case.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_SDSDTSFTT
### Default
#### OriginalId=SF_DEAD_STORE_DUE_TO_SWITCH_FALLTHROUGH_TO_THROW
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Dead Store Due To Switch Fallthrough To Throw
#### WarningText
  Value of {2.givenClass} from previous case is lost here due to switch statement fall through to throw

#### HelpText
  A value stored in the previous switch case is ignored here due to a switch fall through to a place where an exception is thrown. It is likely that you forgot to put a break or return at the end of the previous case.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_SFDA
### Default
#### OriginalId=SA_FIELD_DOUBLE_ASSIGNMENT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Field Double Assignment
#### WarningText
  Double assignment of field {2.givenClass} in {1}

#### HelpText
  This method contains a double assignment of a field; e.g.

  ``` java
  int x,y;
  public void foo() {
      x = x = 17;
  }
  ```

  Assigning to a field twice is useless, and may indicate a logic error or typo.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_SFSA
### Default
#### OriginalId=SA_FIELD_SELF_ASSIGNMENT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Field Self Assignment
#### WarningText
  Self assignment of field {2.givenClass} in {1}

#### HelpText
  This method contains a self assignment of a field; e.g.

  ``` java
  int x;
  public void foo() {
      x = x;
  }
  ```

  Such assignments are useless, and may indicate a logic error or typo.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_SFSC
### Default
#### OriginalId=SA_FIELD_SELF_COMPARISON
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Field Self Comparison
#### WarningText
  Self comparison of {2.givenClass} with itself in {1}

#### HelpText
  This method compares a field with itself, and may indicate a typo or a logic error. Make sure that you are comparing the right things.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_SHMN
### Default
#### OriginalId=NM_LCASE_HASHCODE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Lcase Hashcode
#### WarningText
  Class {0} defines hashcode(); should it be hashCode()?

#### HelpText
  This class defines a method called `hashcode()`.  This method does not override the `hashCode()` method in `java.lang.Object`, which is probably what was intended.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_SIBFA
### Default
#### OriginalId=SI_INSTANCE_BEFORE_FINALS_ASSIGNED
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Instance Before Finals Assigned
#### WarningText
  Static initializer for {0} creates instance before all static final fields assigned

#### HelpText
  The class’s static initializer creates an instance of the class before all of the static final fields are assigned.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_SIC
### Default
#### OriginalId=SE_INNER_CLASS
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Inner Class
#### WarningText
  {0} is serializable and an inner class

#### HelpText
  This Serializable class is an inner class. Any attempt to serialize it will also serialize the associated outer instance. The outer instance is serializable, so this won’t fail, but it might serialize a lot more data than intended. If possible, making the inner class a static inner class (also known as a nested class) should solve the problem.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_SIOC
### Default
#### OriginalId=STI_INTERRUPTED_ON_CURRENTTHREAD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Interrupted On Currentthread
#### WarningText
  {1} makes an unneeded call to currentThread() just to call interrupted()

#### HelpText
  This method invokes the Thread.currentThread() call, just to call the interrupted() method. As interrupted() is a static method, is more simple and clear to use Thread.interrupted().


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_SIOSCI
### Default
#### OriginalId=STCAL_INVOKE_ON_STATIC_CALENDAR_INSTANCE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Invoke On Static Calendar Instance
#### WarningText
  Call to method of static java.util.Calendar in {1}

#### HelpText
  Even though the JavaDoc does not contain a hint about it, Calendars are inherently unsafe for multithreaded use. The detector has found a call to an instance of Calendar that has been obtained via a static field. This looks suspicious.

  For more information on this see [JDK Bug \#6231579](http://bugs.java.com/bugdatabase/view_bug.do?bug_id=6231579) and [JDK Bug \#6178997](http://bugs.java.com/bugdatabase/view_bug.do?bug_id=6178997).


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_SIOSDFI
### Default
#### OriginalId=STCAL_INVOKE_ON_STATIC_DATE_FORMAT_INSTANCE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Invoke On Static Date Format Instance
#### WarningText
  Call to method of static java.text.DateFormat in {1}

#### HelpText
  As the JavaDoc states, DateFormats are inherently unsafe for multithreaded use. The detector has found a call to an instance of DateFormat that has been obtained via a static field. This looks suspicious.

  For more information on this see [JDK Bug \#6231579](http://bugs.java.com/bugdatabase/view_bug.do?bug_id=6231579) and [JDK Bug \#6178997](http://bugs.java.com/bugdatabase/view_bug.do?bug_id=6178997).


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_SIOU
### Default
#### OriginalId=STI_INTERRUPTED_ON_UNKNOWNTHREAD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Interrupted On Unknownthread
#### WarningText
  {1} invokes static Thread.interrupted() method on thread instance

#### HelpText
  This method invokes the Thread.interrupted() method on a Thread object that appears to be a Thread object that is not the current thread. As the interrupted() method is static, the interrupted method will be called on a different object than the one the author intended.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_SISBS
### Default
#### OriginalId=SIC_INNER_SHOULD_BE_STATIC
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Inner Should Be Static
#### WarningText
  Should {0} be a _static_ inner class?

#### HelpText
  This class is an inner class, but does not use its embedded reference to the object which created it.  This reference makes the instances of the class larger, and may keep the reference to the creator object alive longer than necessary.  If possible, the class should be made static.


#### Tags
- /tool/FindBugs
- /general/Optimization Rules

#### Settings
- Priority=Major


## FB_SISBSA
### Default
#### OriginalId=SIC_INNER_SHOULD_BE_STATIC_ANON
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Inner Should Be Static Anon
#### WarningText
  The class {0} could be refactored into a named _static_ inner class

#### HelpText
  This class is an inner class, but does not use its embedded reference to the object which created it.  This reference makes the instances of the class larger, and may keep the reference to the creator object alive longer than necessary.  If possible, the class should be made into a *static* inner class. Since anonymous inner classes cannot be marked as static, doing this will require refactoring the inner class so that it is a named inner class.


#### Tags
- /tool/FindBugs
- /general/Optimization Rules

#### Settings
- Priority=Major


## FB_SISBSNT
### Default
#### OriginalId=SIC_INNER_SHOULD_BE_STATIC_NEEDS_THIS
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Inner Should Be Static Needs This
#### WarningText
  The class {0} could be refactored into a _static_ inner class

#### HelpText
  This class is an inner class, but does not use its embedded reference to the object which created it except during construction of the inner object.  This reference makes the instances of the class larger, and may keep the reference to the creator object alive longer than necessary.  If possible, the class should be made into a *static* inner class. Since the reference to the outer object is required during construction of the inner instance, the inner class will need to be refactored so as to pass a reference to the outer instance to the constructor for the inner class.


#### Tags
- /tool/FindBugs
- /general/Optimization Rules

#### Settings
- Priority=Major


## FB_SLDA
### Default
#### OriginalId=SA_LOCAL_DOUBLE_ASSIGNMENT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Local Double Assignment
#### WarningText
  Double assignment of {2} in {1}

#### HelpText
  This method contains a double assignment of a local variable; e.g.

  ``` java
  public void foo() {
      int x,y;
      x = x = 17;
  }
  ```

  Assigning the same value to a variable twice is useless, and may indicate a logic error or typo.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_SLSA
### Default
#### OriginalId=SA_LOCAL_SELF_ASSIGNMENT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Local Self Assignment
#### WarningText
  Self assignment of {2} in {1}

#### HelpText
  This method contains a self assignment of a local variable; e.g.

  ``` java
  public void foo() {
      int x = 3;
      x = x;
  }
  ```

  Such assignments are useless, and may indicate a logic error or typo.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_SLSAIOF
### Default
#### OriginalId=SA_LOCAL_SELF_ASSIGNMENT_INSTEAD_OF_FIELD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Local Self Assignment Instead Of Field
#### WarningText
  Self assignment of {2} rather than assigned to field in {1}

#### HelpText
  This method contains a self assignment of a local variable, and there is a field with an identical name. assignment appears to have been ; e.g.

  ``` java
      int foo;
      public void setFoo(int foo) {
          foo = foo;
      }
  ```

  The assignment is useless. Did you mean to assign to the field instead?


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_SLSC
### Default
#### OriginalId=SA_LOCAL_SELF_COMPARISON
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Local Self Comparison
#### WarningText
  Self comparison of {2} with itself {1}

#### HelpText
  This method compares a local variable with itself, and may indicate a typo or a logic error. Make sure that you are comparing the right things.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_SMMBP
### Default
#### OriginalId=SE_METHOD_MUST_BE_PRIVATE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Method Must Be Private
#### WarningText
  The method {1.givenClass} must be private to be invoked in serialization/deserialization of {0}

#### HelpText
  This class implements the `Serializable` interface, and defines a method for custom serialization/deserialization. But since that method isn’t declared private, it will be silently ignored by the serialization/deserialization API.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_SNC
### Default
#### OriginalId=SR_NOT_CHECKED
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Not Checked
#### WarningText
  {1} ignores result of {2}

#### HelpText
  This method ignores the return value of `java.io.InputStream.skip()` which can skip multiple bytes.  If the return value is not checked, the caller will not be able to correctly handle the case where fewer bytes were skipped than the caller requested.  This is a particularly insidious kind of bug, because in many programs, skips from input streams usually do skip the full amount of data requested, causing the program to fail only sporadically. With Buffered streams, however, skip() will only skip data in the buffer, and will routinely fail to skip the requested number of bytes.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_SNS
### Default
#### OriginalId=SE_NONFINAL_SERIALVERSIONID
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Nonfinal Serialversionid
#### WarningText
  {1} isn't final

#### HelpText
  This class defines a `serialVersionUID` field that is not final.  The field should be made final if it is intended to specify the version UID for purposes of serialization.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_SNSC
### Default
#### OriginalId=SE_NO_SUITABLE_CONSTRUCTOR
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=No Suitable Constructor
#### WarningText
  {0} is Serializable but its superclass doesn't define an accessible void constructor

#### HelpText
  This class implements the `Serializable` interface and its superclass does not. When such an object is deserialized, the fields of the superclass need to be initialized by invoking the void constructor of the superclass. Since the superclass does not have one, serialization and deserialization will fail at runtime.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_SNSCFE
### Default
#### OriginalId=SE_NO_SUITABLE_CONSTRUCTOR_FOR_EXTERNALIZATION
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=No Suitable Constructor For Externalization
#### WarningText
  {0} is Externalizable but doesn't define a void constructor

#### HelpText
  This class implements the `Externalizable` interface, but does not define a public void constructor. When Externalizable objects are deserialized, they first need to be constructed by invoking the public void constructor. Since this class does not have one, serialization and deserialization will fail at runtime.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_SNSPTE
### Default
#### OriginalId=SQL_NONCONSTANT_STRING_PASSED_TO_EXECUTE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Nonconstant String Passed To Execute
#### WarningText
  {1} passes a nonconstant String to an execute or addBatch method on an SQL statement

#### HelpText
  The method invokes the execute or addBatch method on an SQL statement with a String that seems to be dynamically generated. Consider using a prepared statement instead. It is more efficient and less vulnerable to SQL injection attacks.


#### Tags
- /tool/FindBugs
- /general/Vulnerability Rules
- /collection/SEI CERT/IDS00-J
- /collection/CWE/20
- /collection/CWE/89
- /collection/CWE/116
- /collection/CWE/943
- /collection/OWASP/A03:2021

#### Settings
- Priority=Major


## FB_SPRRNI
### Default
#### OriginalId=SE_PRIVATE_READ_RESOLVE_NOT_INHERITED
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Private Read Resolve Not Inherited
#### WarningText
  Private readResolve method in {0} not inherited by subclasses.

#### HelpText
  This class defines a private readResolve method. Since it is private, it won’t be inherited by subclasses. This might be intentional and OK, but should be reviewed to ensure it is what is intended.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_SPSGFNS
### Default
#### OriginalId=SQL_PREPARED_STATEMENT_GENERATED_FROM_NONCONSTANT_STRING
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Prepared Statement Generated From Nonconstant String
#### WarningText
  A prepared statement is generated from a nonconstant String in {1}

#### HelpText
  The code creates an SQL prepared statement from a nonconstant String. If unchecked, tainted data from a user is used in building this String, SQL injection could be used to make the prepared statement do something unexpected and undesirable.


#### Tags
- /tool/FindBugs
- /general/Vulnerability Rules
- /collection/SEI CERT/IDS00-J
- /collection/CWE/20
- /collection/CWE/89
- /collection/CWE/116
- /collection/CWE/943
- /collection/OWASP/A03:2021

#### Settings
- Priority=Major


## FB_SRRIS
### Default
#### OriginalId=SE_READ_RESOLVE_IS_STATIC
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Read Resolve Is Static
#### WarningText
  {1} should be declared as an instance method rather than a static method

#### HelpText
  In order for the readResolve method to be recognized by the serialization mechanism, it must not be declared as a static method.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_SRRMRO
### Default
#### OriginalId=SE_READ_RESOLVE_MUST_RETURN_OBJECT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Read Resolve Must Return Object
#### WarningText
  The method {1} must be declared with a return type of Object rather than {1.returnType}

#### HelpText
  In order for the readResolve method to be recognized by the serialization mechanism, it must be declared to have a return type of Object.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_SSBS
### Default
#### OriginalId=SS_SHOULD_BE_STATIC
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Should Be Static
#### WarningText
  Unread field: {1}; should this field be static?

#### HelpText
  This class contains an instance final field that is initialized to a compile-time static value. Consider making the field static.


#### Tags
- /tool/FindBugs
- /general/Optimization Rules

#### Settings
- Priority=Major


## FB_SSCI
### Default
#### OriginalId=STCAL_STATIC_CALENDAR_INSTANCE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Static Calendar Instance
#### WarningText
  {1} is static field of type java.util.Calendar, which isn't thread safe

#### HelpText
  Even though the JavaDoc does not contain a hint about it, Calendars are inherently unsafe for multithreaded use. Sharing a single instance across thread boundaries without proper synchronization will result in erratic behavior of the application. Under 1.4 problems seem to surface less often than under Java 5 where you will probably see random ArrayIndexOutOfBoundsExceptions or IndexOutOfBoundsExceptions in sun.util.calendar.BaseCalendar.getCalendarDateFromFixedDate().

  You may also experience serialization problems.

  Using an instance field is recommended.

  For more information on this see [JDK Bug \#6231579](http://bugs.java.com/bugdatabase/view_bug.do?bug_id=6231579) and [JDK Bug \#6178997](http://bugs.java.com/bugdatabase/view_bug.do?bug_id=6178997).


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_SSI
### Default
#### OriginalId=SIO_SUPERFLUOUS_INSTANCEOF
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Superfluous Instanceof
#### WarningText
  {1} does an unnecessary type check using instanceof operator when it can be determined statically

#### HelpText
  Type check performed using the instanceof operator where it can be statically determined whether the object is of the type requested.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_SSIC
### Default
#### OriginalId=SC_START_IN_CTOR
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Start In Ctor
#### WarningText
  {1} invokes {2}

#### HelpText
  The constructor starts a thread. This is likely to be wrong if the class is ever extended/subclassed, since the thread will be started before the subclass constructor is started.


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_SSMIIST
### Default
#### OriginalId=SW_SWING_METHODS_INVOKED_IN_SWING_THREAD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Swing Methods Invoked In Swing Thread
#### WarningText
  Call to swing method in {1} needs to be performed in Swing event thread

#### HelpText
  ([From JDC Tech Tip](http://web.archive.org/web/20090526170426/http://java.sun.com/developer/JDCTechTips/2003/tt1208.html)): The Swing methods show(), setVisible(), and pack() will create the associated peer for the frame. With the creation of the peer, the system creates the event dispatch thread. This makes things problematic because the event dispatch thread could be notifying listeners while pack and validate are still processing. This situation could result in two threads going through the Swing component-based GUI – it’s a serious flaw that could result in deadlocks or other related threading issues. A pack call causes components to be realized. As they are being realized (that is, not necessarily visible), they could trigger listener notification on the event dispatch thread.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_SSOF
### Default
#### OriginalId=SP_SPIN_ON_FIELD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Spin On Field
#### WarningText
  Spinning on {2.givenClass} in {1}

#### HelpText
  This method spins in a loop which reads a field.  The compiler may legally hoist the read out of the loop, turning the code into an infinite loop.  The class should be changed so it uses proper synchronization (including wait and notify calls).


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_SSSDFI
### Default
#### OriginalId=STCAL_STATIC_SIMPLE_DATE_FORMAT_INSTANCE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Static Simple Date Format Instance
#### WarningText
  {1} is a static field of type java.text.DateFormat, which isn't thread safe

#### HelpText
  As the JavaDoc states, DateFormats are inherently unsafe for multithreaded use. Sharing a single instance across thread boundaries without proper synchronization will result in erratic behavior of the application.

  You may also experience serialization problems.

  Using an instance field is recommended.

  For more information on this see [JDK Bug \#6231579](http://bugs.java.com/bugdatabase/view_bug.do?bug_id=6231579) and [JDK Bug \#6178997](http://bugs.java.com/bugdatabase/view_bug.do?bug_id=6178997).


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_SSWLH
### Default
#### OriginalId=SWL_SLEEP_WITH_LOCK_HELD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Sleep With Lock Held
#### WarningText
  {1} calls Thread.sleep() with a lock held

#### HelpText
  This method calls Thread.sleep() with a lock held. This may result in very poor performance and scalability, or a deadlock, since other threads may be waiting to acquire the lock. It is a much better idea to call wait() on the lock, which releases the lock and allows other threads to run.


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_STDE
### Default
#### OriginalId=SIC_THREADLOCAL_DEADLY_EMBRACE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Threadlocal Deadly Embrace
#### WarningText
  {0} needs to be _static_ to avoid a deadly embrace with {1}

#### HelpText
  This class is an inner class, but should probably be a static inner class. As it is, there is a serious danger of a deadly embrace between the inner class and the thread local in the outer class. Because the inner class isn’t static, it retains a reference to the outer class. If the thread local contains a reference to an instance of the inner class, the inner and outer instance will both be reachable and not eligible for garbage collection.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_STFNR
### Default
#### OriginalId=SE_TRANSIENT_FIELD_NOT_RESTORED
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Transient Field Not Restored
#### WarningText
  The field {1} is transient but isn't set by deserialization

#### HelpText
  This class contains a field that is updated at multiple places in the class, thus it seems to be part of the state of the class. However, since the field is marked as transient and not set in readObject or readResolve, it will contain the default value in any deserialized instance of the class.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_STFONC
### Default
#### OriginalId=SE_TRANSIENT_FIELD_OF_NONSERIALIZABLE_CLASS
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Transient Field Of Nonserializable Class
#### WarningText
  {1.givenClass} is transient but {0} isn't Serializable

#### HelpText
  The field is marked as transient, but the class isn’t Serializable, so marking it as transient has absolutely no effect. This may be leftover marking from a previous version of the code in which the class was transient, or it may indicate a misunderstanding of how serialization works.

  *This bug is reported only if special option `reportTransientFieldOfNonSerializableClass` is set.*


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_STS
### Default
#### OriginalId=DM_STRING_TOSTRING
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=String Tostring
#### WarningText
  {1} invokes toString() method on a String

#### HelpText
  Calling `String.toString()` is just a redundant operation. Just use the String.


#### Tags
- /tool/FindBugs
- /general/Optimization Rules

#### Settings
- Priority=Major


## FB_SWTSFIM
### Default
#### OriginalId=ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Write To Static From Instance Method
#### WarningText
  Write to static field {2} from instance method {1}

#### HelpText
  This instance method writes to a static field. This is tricky to get correct if multiple instances are being manipulated, and generally bad practice.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_SaFSC
### Default
#### OriginalId=SA_FIELD_SELF_COMPUTATION
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Field Self Computation
#### WarningText
  Nonsensical self computation of {2.givenClass} with itself in {1}

#### HelpText
  This method performs a nonsensical computation of a field with another reference to the same field (e.g., x&x or x-x). Because of the nature of the computation, this operation doesn’t seem to make sense, and may indicate a typo or a logic error. Double check the computation.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_SaLSC
### Default
#### OriginalId=SA_LOCAL_SELF_COMPUTATION
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Local Self Computation
#### WarningText
  Nonsensical self computation of {2} with itself in {1}

#### HelpText
  This method performs a nonsensical computation of a local variable with another reference to the same variable (e.g., x&x or x-x). Because of the nature of the computation, this operation doesn’t seem to make sense, and may indicate a typo or a logic error. Double check the computation.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_SeNS
### Default
#### OriginalId=SE_NONLONG_SERIALVERSIONID
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Nonlong Serialversionid
#### WarningText
  {1} isn't long

#### HelpText
  This class defines a `serialVersionUID` field that is not long.  The field should be made long if it is intended to specify the version UID for purposes of serialization.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_SeNoS
### Default
#### OriginalId=SE_NONSTATIC_SERIALVERSIONID
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Nonstatic Serialversionid
#### WarningText
  {1} isn't static

#### HelpText
  This class defines a `serialVersionUID` field that is not static.  The field should be made static if it is intended to specify the version UID for purposes of serialization.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_TAVUWNR
### Default
#### OriginalId=TQ_ALWAYS_VALUE_USED_WHERE_NEVER_REQUIRED
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Always Value Used Where Never Required
#### WarningText
  Value annotated as carrying type qualifier {2.simpleName} used where a value that must not carry that qualifier is required

#### HelpText
  A value specified as carrying a type qualifier annotation is consumed in a location or locations requiring that the value not carry that annotation.

  More precisely, a value annotated with a type qualifier specifying when=ALWAYS is guaranteed to reach a use or uses where the same type qualifier specifies when=NEVER.

  For example, say that <span class="citation" data-cites="NonNegative">@NonNegative</span> is a nickname for the type qualifier annotation <span class="citation" data-cites="Negative">@Negative</span>(when=When.NEVER). The following code will generate this warning because the return statement requires a <span class="citation" data-cites="NonNegative">@NonNegative</span> value, but receives one that is marked as <span class="citation" data-cites="Negative">@Negative</span>.

  ``` java
  public @NonNegative Integer example(@Negative Integer value) {
      return value;
  }
  ```


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_TCVWITQ
### Default
#### OriginalId=TQ_COMPARING_VALUES_WITH_INCOMPATIBLE_TYPE_QUALIFIERS
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Comparing Values With Incompatible Type Qualifiers
#### WarningText
  Value annotated as having the type qualifier {2.simpleName} is compared for equality with a value that never has that qualifier

#### HelpText
  A value specified as carrying a type qualifier annotation is compared with a value that doesn’t ever carry that qualifier.

  More precisely, a value annotated with a type qualifier specifying when=ALWAYS is compared with a value that where the same type qualifier specifies when=NEVER.

  For example, say that <span class="citation" data-cites="NonNegative">@NonNegative</span> is a nickname for the type qualifier annotation <span class="citation" data-cites="Negative">@Negative</span>(when=When.NEVER). The following code will generate this warning because the return statement requires a <span class="citation" data-cites="NonNegative">@NonNegative</span> value, but receives one that is marked as <span class="citation" data-cites="Negative">@Negative</span>.

  ``` java
  public boolean example(@Negative Integer value1, @NonNegative Integer value2) {
      return value1.equals(value2);
  }
  ```


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_TEUSVRAS
### Default
#### OriginalId=TQ_EXPLICIT_UNKNOWN_SOURCE_VALUE_REACHES_ALWAYS_SINK
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Explicit Unknown Source Value Reaches Always Sink
#### WarningText
  Value is required to always be {2.simpleName}, but is explicitly annotated as unknown with regards to {2.simpleName}

#### HelpText
  A value is used in a way that requires it to be always be a value denoted by a type qualifier, but there is an explicit annotation stating that it is not known where the value is required to have that type qualifier. Either the usage or the annotation is incorrect.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_TEUSVRNS
### Default
#### OriginalId=TQ_EXPLICIT_UNKNOWN_SOURCE_VALUE_REACHES_NEVER_SINK
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Explicit Unknown Source Value Reaches Never Sink
#### WarningText
  Value is required never be {2.simpleName}, but is explicitly annotated as unknown with regards to {2.simpleName}

#### HelpText
  A value is used in a way that requires it to be never be a value denoted by a type qualifier, but there is an explicit annotation stating that it is not known where the value is prohibited from having that type qualifier. Either the usage or the annotation is incorrect.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_TMSVRAS
### Default
#### OriginalId=TQ_MAYBE_SOURCE_VALUE_REACHES_ALWAYS_SINK
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Maybe Source Value Reaches Always Sink
#### WarningText
  Value that might not carry the {2.simpleName} annotation is always used in a way that requires that type qualifier

#### HelpText
  A value that is annotated as possibility not being an instance of the values denoted by the type qualifier, and the value is guaranteed to be used in a way that requires values denoted by that type qualifier.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_TMSVRNS
### Default
#### OriginalId=TQ_MAYBE_SOURCE_VALUE_REACHES_NEVER_SINK
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Maybe Source Value Reaches Never Sink
#### WarningText
  Value that might carry the {2.simpleName} annotation is always used in a way that prohibits it from having that type qualifier

#### HelpText
  A value that is annotated as possibility being an instance of the values denoted by the type qualifier, and the value is guaranteed to be used in a way that prohibits values denoted by that type qualifier.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_TNVUWAR
### Default
#### OriginalId=TQ_NEVER_VALUE_USED_WHERE_ALWAYS_REQUIRED
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Never Value Used Where Always Required
#### WarningText
  Value annotated as never carrying type qualifier {2.simpleName} used where value carrying that qualifier is required

#### HelpText
  A value specified as not carrying a type qualifier annotation is guaranteed to be consumed in a location or locations requiring that the value does carry that annotation.

  More precisely, a value annotated with a type qualifier specifying when=NEVER is guaranteed to reach a use or uses where the same type qualifier specifies when=ALWAYS.

  TODO: example


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_TTLW
### Default
#### OriginalId=TLW_TWO_LOCK_WAIT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Two Lock Wait
#### WarningText
  wait() with two locks held in {1}

#### HelpText
  Waiting on a monitor while two locks are held may cause deadlock.   Performing a wait only releases the lock on the object being waited on, not any other locks.   This not necessarily a bug, but is worth examining closely.


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_TUVUWASR
### Default
#### OriginalId=TQ_UNKNOWN_VALUE_USED_WHERE_ALWAYS_STRICTLY_REQUIRED
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unknown Value Used Where Always Strictly Required
#### WarningText
  Value without a type qualifier is used in a place that requires a {2.simpleName} annotation

#### HelpText
  A value is being used in a way that requires the value be annotation with a type qualifier. The type qualifier is strict, so the tool rejects any values that do not have the appropriate annotation.

  To coerce a value to have a strict annotation, define an identity function where the return value is annotated with the strict annotation. This is the only way to turn a non-annotated value into a value with a strict type qualifier annotation.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_UFNIIC
### Default
#### OriginalId=UWF_FIELD_NOT_INITIALIZED_IN_CONSTRUCTOR
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Field Not Initialized In Constructor
#### WarningText
  {1.givenClass} not initialized in constructor and dereferenced in {2}

#### HelpText
  This field is never initialized within any constructor, and is therefore could be null after the object is constructed. Elsewhere, it is loaded and dereferenced without a null check. This could be a either an error or a questionable design, since it means a null pointer exception will be generated if that field is dereferenced before being initialized.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_UIUG
### Default
#### OriginalId=UI_INHERITANCE_UNSAFE_GETRESOURCE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Inheritance Unsafe Getresource
#### WarningText
  Usage of GetResource in {1} may be unsafe if class is extended

#### HelpText
  Calling `this.getClass().getResource(...)` could give results other than expected if this class is extended by a class in another package.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_ULWCC
### Default
#### OriginalId=DM_CONVERT_CASE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Convert Case
#### WarningText
  Use of non-localized String.toUpperCase() or String.toLowerCase() in {1}

#### HelpText
  A String is being converted to upper or lowercase, using the platform’s default encoding. This may result in improper conversions when used with international characters. Use the

  -   String.toUpperCase( Locale l )
  -   String.toLowerCase( Locale l )

  versions instead.


#### Tags
- /tool/FindBugs
- /general/Internationalization Rules

#### Settings
- Priority=Info


## FB_UNCIE
### Default
#### OriginalId=NP_EQUALS_SHOULD_HANDLE_NULL_ARGUMENT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Equals Should Handle Null Argument
#### WarningText
  {1} does not check for null argument

#### HelpText
  This implementation of equals(Object) violates the contract defined by java.lang.Object.equals() because it does not check for null being passed as the argument. All equals() methods should return false if passed a null value.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_UNF
### Default
#### OriginalId=UWF_NULL_FIELD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Null Field
#### WarningText
  Field only ever set to null: {1}

#### HelpText
  All writes to this field are of the constant value null, and thus all reads of the field will return null. Check for errors, or remove it if it is useless.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_UPF
### Default
#### OriginalId=DLS_DEAD_LOCAL_INCREMENT_IN_RETURN
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Dead Local Increment In Return
#### WarningText
  Useless increment in return from {1}

#### HelpText
  This statement has a return such as `return x++;`. A postfix increment/decrement does not impact the value of the expression, so this increment/decrement has no effect. Please verify that this statement does the right thing.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_USBFSA
### Default
#### OriginalId=SBSC_USE_STRINGBUFFER_CONCATENATION
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Use Stringbuffer Concatenation
#### WarningText
  {1} concatenates strings using + in a loop

#### HelpText
  The method seems to be building a String using concatenation in a loop. In each iteration, the String is converted to a StringBuffer/StringBuilder, appended to, and converted back to a String. This can lead to a cost quadratic in the number of iterations, as the growing string is recopied in each iteration.

  Better performance can be obtained by using a StringBuffer (or StringBuilder in Java 1.5) explicitly.

  For example:

  ``` java
  // This is bad
  String s = "";
  for (int i = 0; i < field.length; ++i) {
      s = s + field[i];
  }

  // This is better
  StringBuffer buf = new StringBuffer();
  for (int i = 0; i < field.length; ++i) {
      buf.append(field[i]);
  }
  String s = buf.toString();
  ```


#### Tags
- /tool/FindBugs
- /general/Optimization Rules

#### Settings
- Priority=Major


## FB_USSUG
### Default
#### OriginalId=UG_SYNC_SET_UNSYNC_GET
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Sync Set Unsync Get
#### WarningText
  {1} is unsynchronized, {2} is synchronized

#### HelpText
  This class contains similarly-named get and set methods where the set method is synchronized and the get method is not.  This may result in incorrect behavior at runtime, as callers of the get method will not necessarily see a consistent state for the object.  The get method should be made synchronized.


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_UUAM
### Default
#### OriginalId=USM_USELESS_ABSTRACT_METHOD
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=Useless Abstract Method
#### WarningText
  Abstract Method {1} is already defined in implemented interface

#### HelpText
  This abstract method is already defined in an interface that is implemented by this abstract class. This method can be removed, as it provides no additional value.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_UUCF
### Default
#### OriginalId=UCF_USELESS_CONTROL_FLOW
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Useless Control Flow
#### WarningText
  Useless control flow in {1}

#### HelpText
  This method contains a useless control flow statement, where control flow continues onto the same place regardless of whether or not the branch is taken. For example, this is caused by having an empty statement block for an `if` statement:

  ``` java
  if (argv.length == 0) {
      // TODO: handle this case
  }
  ```


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_UUCFNL
### Default
#### OriginalId=UCF_USELESS_CONTROL_FLOW_NEXT_LINE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Useless Control Flow Next Line
#### WarningText
  Useless control flow to next line in {1}

#### HelpText
  This method contains a useless control flow statement in which control flow follows to the same or following line regardless of whether or not the branch is taken. Often, this is caused by inadvertently using an empty statement as the body of an `if` statement, e.g.:

  ``` java
  if (argv.length == 1);
      System.out.println("Hello, " + argv[0]);
  ```


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_UUCT
### Default
#### OriginalId=UC_USELESS_CONDITION_TYPE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Useless Condition Type
#### WarningText
  Useless condition: it's always {2} because variable type is {3}

#### HelpText
  This condition always produces the same result due to the type range of the involved variable. Probably something else was meant or the condition can be removed.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_UUCo
### Default
#### OriginalId=UC_USELESS_CONDITION
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Useless Condition
#### WarningText
  Useless condition: it's known that {2} at this point

#### HelpText
  This condition always produces the same result as the value of the involved variable that was narrowed before. Probably something else was meant or the condition can be removed.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_UUF
### Default
#### OriginalId=URF_UNREAD_FIELD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unread Field
#### WarningText
  Unread field: {1}

#### HelpText
  This field is never read.  Consider removing it from the class.


#### Tags
- /tool/FindBugs
- /general/Optimization Rules

#### Settings
- Priority=Major


## FB_UUL
### Default
#### OriginalId=UL_UNRELEASED_LOCK
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unreleased Lock
#### WarningText
  {1} does not release lock on all paths

#### HelpText
  This method acquires a JSR-166 (`java.util.concurrent`) lock, but does not release it on all paths out of the method. In general, the correct idiom for using a JSR-166 lock is:

  ``` java
  Lock l = ...;
  l.lock();
  try {
      // do something
  } finally {
      l.unlock();
  }
  ```


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_UULEP
### Default
#### OriginalId=UL_UNRELEASED_LOCK_EXCEPTION_PATH
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unreleased Lock Exception Path
#### WarningText
  {1} does not release lock on all exception paths

#### HelpText
  This method acquires a JSR-166 (`java.util.concurrent`) lock, but does not release it on all exception paths out of the method. In general, the correct idiom for using a JSR-166 lock is:

  ``` java
  Lock l = ...;
  l.lock();
  try {
      // do something
  } finally {
      l.unlock();
  }
  ```


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_UUM
### Default
#### OriginalId=UM_UNNECESSARY_MATH
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unnecessary Math
#### WarningText
  Method calls static Math class method on a constant value

#### HelpText
  This method uses a static method from java.lang.Math on a constant value. This method’s result in this case, can be determined statically, and is faster and sometimes more accurate to just use the constant. Methods detected are:

  | Method    | Parameter  |
  |-----------|------------|
  | abs       | -any-      |
  | acos      | 0.0 or 1.0 |
  | asin      | 0.0 or 1.0 |
  | atan      | 0.0 or 1.0 |
  | atan2     | 0.0        |
  | cbrt      | 0.0 or 1.0 |
  | ceil      | -any-      |
  | cos       | 0.0        |
  | cosh      | 0.0        |
  | exp       | 0.0 or 1.0 |
  | expm1     | 0.0        |
  | floor     | -any-      |
  | log       | 0.0 or 1.0 |
  | log10     | 0.0 or 1.0 |
  | rint      | -any-      |
  | round     | -any-      |
  | sin       | 0.0        |
  | sinh      | 0.0        |
  | sqrt      | 0.0 or 1.0 |
  | tan       | 0.0        |
  | tanh      | 0.0        |
  | toDegrees | 0.0 or 1.0 |
  | toRadians | 0.0        |




#### Tags
- /tool/FindBugs
- /general/Optimization Rules

#### Settings
- Priority=Major


## FB_UUMOAC
### Default
#### OriginalId=UMAC_UNCALLABLE_METHOD_OF_ANONYMOUS_CLASS
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Uncallable Method Of Anonymous Class
#### WarningText
  Uncallable method {1} defined in anonymous class

#### HelpText
  This anonymous class defines a method that is not directly invoked and does not override a method in a superclass. Since methods in other classes cannot directly invoke methods declared in an anonymous class, it seems that this method is uncallable. The method might simply be dead code, but it is also possible that the method is intended to override a method declared in a superclass, and due to a typo or other error the method does not, in fact, override the method it is intended to.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_UUO
### Default
#### OriginalId=UC_USELESS_OBJECT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Useless Object
#### WarningText
  Useless object stored in variable {2} of method {1}

#### HelpText
  Our analysis shows that this object is useless. It’s created and modified, but its value never go outside of the method or produce any side-effect. Either there is a mistake and object was intended to be used or it can be removed.

  This analysis rarely produces false-positives. Common false-positive cases include:

  -   This object used to implicitly throw some obscure exception.

  -   This object used as a stub to generalize the code.

  -   This object used to hold strong references to weak/soft-referenced objects.




#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_UUOS
### Default
#### OriginalId=UC_USELESS_OBJECT_STACK
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Useless Object Stack
#### WarningText
  Useless object created in method {1}

#### HelpText
  This object is created just to perform some modifications which don’t have any side-effect. Probably something else was meant or the object can be removed.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_UUPM
### Default
#### OriginalId=UPM_UNCALLED_PRIVATE_METHOD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Uncalled Private Method
#### WarningText
  Private method {1} is never called

#### HelpText
  This private method is never called. Although it is possible that the method will be invoked through reflection, it is more likely that the method is never used, and should be removed.


#### Tags
- /tool/FindBugs
- /general/Optimization Rules

#### Settings
- Priority=Major


## FB_UUPOPF
### Default
#### OriginalId=URF_UNREAD_PUBLIC_OR_PROTECTED_FIELD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unread Public Or Protected Field
#### WarningText
  Unread public/protected field: {1}

#### HelpText
  This field is never read.  The field is public or protected, so perhaps it is intended to be used with classes not seen as part of the analysis. If not, consider removing it from the class.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_UUR
### Default
#### OriginalId=UR_UNINIT_READ
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Uninit Read
#### WarningText
  Uninitialized read of {2.name} in {1}

#### HelpText
  This constructor reads a field which has not yet been assigned a value.  This is often caused when the programmer mistakenly uses the field instead of one of the constructor’s parameters.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_UURCFSC
### Default
#### OriginalId=UR_UNINIT_READ_CALLED_FROM_SUPER_CONSTRUCTOR
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Uninit Read Called From Super Constructor
#### WarningText
  {2.name} isn't initialized in {1} when invoked from constructor for superclass

#### HelpText
  This method is invoked in the constructor of the superclass. At this point, the fields of the class have not yet initialized.

  To make this more concrete, consider the following classes:

  ``` java
  abstract class A {
      int hashCode;
      abstract Object getValue();

      A() {
          hashCode = getValue().hashCode();
      }
  }

  class B extends A {
      Object value;

      B(Object v) {
          this.value = v;
      }

      Object getValue() {
          return value;
      }
  }
  ```

  When a `B` is constructed, the constructor for the `A` class is invoked *before* the constructor for `B` sets `value`. Thus, when the constructor for `A` invokes `getValue`, an uninitialized value is read for `value`.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_UUSM
### Default
#### OriginalId=USM_USELESS_SUBCLASS_METHOD
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=Useless Subclass Method
#### WarningText
  {1} superfluously delegates to parent class method

#### HelpText
  This derived method merely calls the same superclass method passing in the exact parameters received. This method can be removed, as it provides no additional value.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_UUVM
### Default
#### OriginalId=UC_USELESS_VOID_METHOD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Useless Void Method
#### WarningText
  Method {1} seems to be useless

#### HelpText
  Our analysis shows that this non-empty void method does not actually perform any useful work. Please check it: probably there’s a mistake in its code or its body can be fully removed.

  We are trying to reduce the false positives as much as possible, but in some cases this warning might be wrong. Common false-positive cases include:

  -   The method is intended to trigger loading of some class which may have a side effect.
  -   The method is intended to implicitly throw some obscure exception.



#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_UUW
### Default
#### OriginalId=UW_UNCOND_WAIT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Uncond Wait
#### WarningText
  Unconditional wait in {1}

#### HelpText
  This method contains a call to `java.lang.Object.wait()` which is not guarded by conditional control flow.  The code should verify that condition it intends to wait for is not already satisfied before calling wait; any previous notifications will be ignored.


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_UWOC
### Default
#### OriginalId=DM_NUMBER_CTOR
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Number Ctor
#### WarningText
  {1} invokes inefficient {2} constructor; use {3} instead

#### HelpText
  Using `new Integer(int)` is guaranteed to always result in a new object whereas `Integer.valueOf(int)` allows caching of values to be done by the compiler, class library, or JVM. Using of cached values avoids object allocation and the code will be faster.

  Values between -128 and 127 are guaranteed to have corresponding cached instances and using `valueOf` is approximately 3.5 times faster than using constructor. For values outside the constant range the performance of both styles is the same.

  Unless the class must be compatible with JVMs predating Java 1.5, use either autoboxing or the `valueOf()` method when creating instances of `Long`, `Integer`, `Short`, `Character`, and `Byte`.


#### Tags
- /tool/FindBugs
- /general/Optimization Rules

#### Settings
- Priority=Major


## FB_UuUF
### Default
#### OriginalId=UUF_UNUSED_FIELD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unused Field
#### WarningText
  Unused field: {1}

#### HelpText
  This field is never used.  Consider removing it from the class.


#### Tags
- /tool/FindBugs
- /general/Optimization Rules

#### Settings
- Priority=Major


## FB_UuUPOPF
### Default
#### OriginalId=UUF_UNUSED_PUBLIC_OR_PROTECTED_FIELD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unused Public Or Protected Field
#### WarningText
  Unused public or protected field: {1}

#### HelpText
  This field is never used.  The field is public or protected, so perhaps it is intended to be used with classes not seen as part of the analysis. If not, consider removing it from the class.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_UwUF
### Default
#### OriginalId=UWF_UNWRITTEN_FIELD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unwritten Field
#### WarningText
  Unwritten field: {1}

#### HelpText
  This field is never written.  All reads of it will return the default value. Check for errors (should it have been initialized?), or remove it if it is useless.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_UwUPOPF
### Default
#### OriginalId=UWF_UNWRITTEN_PUBLIC_OR_PROTECTED_FIELD
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Unwritten Public Or Protected Field
#### WarningText
  Unwritten public or protected field: {1}

#### HelpText
  No writes were seen to this public/protected field.  All reads of it will return the default value. Check for errors (should it have been initialized?), or remove it if it is useless.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info


## FB_VFSUN
### Default
#### OriginalId=VA_FORMAT_STRING_USES_NEWLINE
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Format String Uses Newline
#### WarningText
  Format string should use %n rather than \n in {1}

#### HelpText
  This format string includes a newline character (\\n). In format strings, it is generally preferable to use %n, which will produce the platform-specific line separator.


#### Tags
- /tool/FindBugs
- /general/Bad Practice Rules

#### Settings
- Priority=Major


## FB_VPAPTOV
### Default
#### OriginalId=VA_PRIMITIVE_ARRAY_PASSED_TO_OBJECT_VARARG
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Primitive Array Passed To Object Vararg
#### WarningText
  {2} passed to varargs method {3} in {1}

#### HelpText
  This code passes a primitive array to a function that takes a variable number of object arguments. This creates an array of length one to hold the primitive array and passes it to the function.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_VUR
### Default
#### OriginalId=VR_UNRESOLVABLE_REFERENCE
#### Enabled=false
#### NumericType=true
#### Warning=true
#### DisplayName=Unresolvable Reference
#### WarningText
  Unresolvable reference to {1} by {0}

#### HelpText
  This class makes a reference to a class or method that can not be resolved using against the libraries it is being analyzed with.


#### Tags
- /tool/FindBugs
- /general/Correctness Rules

#### Settings
- Priority=Major


## FB_VVI
### Default
#### OriginalId=VO_VOLATILE_INCREMENT
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Volatile Increment
#### WarningText
  Increment of volatile field {2} in {1}

#### HelpText
  This code increments a volatile field. Increments of volatile fields aren’t atomic. If more than one thread is incrementing the field at the same time, increments could be lost.


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_VVRTA
### Default
#### OriginalId=VO_VOLATILE_REFERENCE_TO_ARRAY
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Volatile Reference To Array
#### WarningText
  {1} is a volatile reference to an array; the array elements are non-volatile

#### HelpText
  This declares a volatile reference to an array, which might not be what you want. With a volatile reference to an array, reads and writes of the reference to the array are treated as volatile, but the array elements are non-volatile. To get volatile array elements, you will need to use one of the atomic array classes in java.util.concurrent (provided in Java 5.0).


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_WANIL
### Default
#### OriginalId=WA_AWAIT_NOT_IN_LOOP
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Await Not In Loop
#### WarningText
  Condition.await() not in loop in {1}

#### HelpText
  This method contains a call to `java.util.concurrent.await()` (or variants) which is not in a loop.  If the object is used for multiple conditions, the condition the caller intended to wait for might not be the one that actually occurred.


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_WNIL
### Default
#### OriginalId=WA_NOT_IN_LOOP
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Not In Loop
#### WarningText
  Wait not in loop in {1}

#### HelpText
  This method contains a call to `java.lang.Object.wait()` which is not in a loop.  If the monitor is used for multiple conditions, the condition the caller intended to wait for might not be the one that actually occurred.


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_WUGRTCL
### Default
#### OriginalId=WL_USING_GETCLASS_RATHER_THAN_CLASS_LITERAL
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Using Getclass Rather Than Class Literal
#### WarningText
  Synchronization on getClass rather than class literal in {1}

#### HelpText
  This instance method synchronizes on `this.getClass()`. If this class is subclassed, subclasses will synchronize on the class object for the subclass, which isn’t likely what was intended. For example, consider this code from java.awt.Label:

  ``` java
  private static final String base = "label";
  private static int nameCounter = 0;

  String constructComponentName() {
      synchronized (getClass()) {
          return base + nameCounter++;
      }
  }
  ```

  Subclasses of `Label` won’t synchronize on the same subclass, giving rise to a datarace. Instead, this code should be synchronizing on `Label.class`

  ``` java
  private static final String base = "label";
  private static int nameCounter = 0;

  String constructComponentName() {
      synchronized (Label.class) {
          return base + nameCounter++;
      }
  }
  ```

  Bug pattern contributed by Jason Mehrens


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_WWMI
### Default
#### OriginalId=WMI_WRONG_MAP_ITERATOR
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Wrong Map Iterator
#### WarningText
  {1} makes inefficient use of keySet iterator instead of entrySet iterator

#### HelpText
  This method accesses the value of a Map entry, using a key that was retrieved from a keySet iterator. It is more efficient to use an iterator on the entrySet of the map, to avoid the Map.get(key) lookup.


#### Tags
- /tool/FindBugs
- /general/Optimization Rules

#### Settings
- Priority=Major


## FB_WWS
### Default
#### OriginalId=WS_WRITEOBJECT_SYNC
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Writeobject Sync
#### WarningText
  {0}'s writeObject method is synchronized but nothing else is

#### HelpText
  This class has a `writeObject()` method which is synchronized; however, no other method of the class is synchronized.


#### Tags
- /tool/FindBugs
- /general/Multithreaded Correctness Rules

#### Settings
- Priority=Major


## FB_XRPTJW
### Default
#### OriginalId=XSS_REQUEST_PARAMETER_TO_JSP_WRITER
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Request Parameter To Jsp Writer
#### WarningText
  HTTP parameter directly written to JSP output, giving reflected XSS vulnerability in {1.class}

#### HelpText
  This code directly writes an HTTP parameter to JSP output, which allows for a cross site scripting vulnerability. See <a href="http://en.wikipedia.org/wiki/Cross-site_scripting" class="uri" class="uri">http://en.wikipedia.org/wiki/Cross-site_scripting</a> for more information.

  SpotBugs looks only for the most blatant, obvious cases of cross site scripting. If SpotBugs found *any*, you *almost certainly* have more cross site scripting vulnerabilities that SpotBugs doesn’t report. If you are concerned about cross site scripting, you should seriously consider using a commercial static analysis or pen-testing tool.


#### Tags
- /tool/FindBugs
- /general/Vulnerability Rules
- /collection/CWE/79
- /collection/OWASP/A03:2021

#### Settings
- Priority=Major


## FB_XRPTSE
### Default
#### OriginalId=XSS_REQUEST_PARAMETER_TO_SEND_ERROR
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Request Parameter To Send Error
#### WarningText
  HTTP parameter written to Servlet error page in {1}

#### HelpText
  This code directly writes an HTTP parameter to a Server error page (using HttpServletResponse.sendError). Echoing this untrusted input allows for a reflected cross site scripting vulnerability. See <a href="http://en.wikipedia.org/wiki/Cross-site_scripting" class="uri" class="uri">http://en.wikipedia.org/wiki/Cross-site_scripting</a> for more information.

  SpotBugs looks only for the most blatant, obvious cases of cross site scripting. If SpotBugs found *any*, you *almost certainly* have more cross site scripting vulnerabilities that SpotBugs doesn’t report. If you are concerned about cross site scripting, you should seriously consider using a commercial static analysis or pen-testing tool.


#### Tags
- /tool/FindBugs
- /general/Vulnerability Rules
- /collection/CWE/79
- /collection/OWASP/A03:2021

#### Settings
- Priority=Major


## FB_XRPTSW
### Default
#### OriginalId=XSS_REQUEST_PARAMETER_TO_SERVLET_WRITER
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Request Parameter To Servlet Writer
#### WarningText
  HTTP parameter written to Servlet output in {1}

#### HelpText
  This code directly writes an HTTP parameter to Servlet output, which allows for a reflected cross site scripting vulnerability. See <a href="http://en.wikipedia.org/wiki/Cross-site_scripting" class="uri" class="uri">http://en.wikipedia.org/wiki/Cross-site_scripting</a> for more information.

  SpotBugs looks only for the most blatant, obvious cases of cross site scripting. If SpotBugs found *any*, you *almost certainly* have more cross site scripting vulnerabilities that SpotBugs doesn’t report. If you are concerned about cross site scripting, you should seriously consider using a commercial static analysis or pen-testing tool.


#### Tags
- /tool/FindBugs
- /general/Vulnerability Rules
- /collection/CWE/79
- /collection/OWASP/A03:2021

#### Settings
- Priority=Major


## FB_XXFB
### Default
#### OriginalId=XFB_XML_FACTORY_BYPASS
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Xml Factory Bypass
#### WarningText
  {1} directly allocates a specific implementation of xml interfaces

#### HelpText
  This method allocates a specific implementation of an xml interface. It is preferable to use the supplied factory classes to create these objects so that the implementation can be changed at runtime. See

  -   javax.xml.parsers.DocumentBuilderFactory
  -   javax.xml.parsers.SAXParserFactory
  -   javax.xml.transform.TransformerFactory
  -   org.w3c.dom.Document.create*XXXX*

  for details.


#### Tags
- /tool/FindBugs
- /general/Dodgy Code Rules

#### Settings
- Priority=Info
