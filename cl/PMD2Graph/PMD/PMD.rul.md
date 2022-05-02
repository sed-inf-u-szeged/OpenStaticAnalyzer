# ToolDescription
## Default
### ID=PMD
### Description
  OpenStaticAnalyzer incorporates the [PMD] tool for coding rule violation checking and imports its results. OpenStaticAnalyzer also associates the issued rule violations with source code elements (i.e. methods, classes, packages, and components), and calculates metrics for the source code elements, which represent the amount of violations of each ruleset, rule, and priority groups, respectively.

  OpenStaticAnalyzer uses PMD "as is", without any guaranties that the results of PMD are correct. All statements of the PMD license apply here as well. All texts describing the rulesets and the individual rules are copied from its official home page with some minor grammatical fixes.

# Includes
- cwe_metadata.md
- PMD.rul_metadata.md
- sei_cert_metadata.md

# Metrics
## PMD_AAA
### Default
#### OriginalId=AvoidAccessibilityAlteration
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Accessibility Alteration
#### HelpText
  Methods such as getDeclaredConstructors(), getDeclaredConstructor(Class\[\]) and setAccessible(), as the interface PrivilegedAction, allow for the runtime alteration of variable, class, or method visibility, even if they are private. This violates the principle of encapsulation.

  Example(s):

  ``` java
  import java.lang.reflect.AccessibleObject;
  import java.lang.reflect.Method;
  import java.security.PrivilegedAction;

  public class Violation {
    public void invalidCallsInMethod() throws SecurityException, NoSuchMethodException {
      // Possible call to forbidden getDeclaredConstructors
      Class[] arrayOfClass = new Class[1];
      this.getClass().getDeclaredConstructors();
      this.getClass().getDeclaredConstructor(arrayOfClass);
      Class clazz = this.getClass();
      clazz.getDeclaredConstructor(arrayOfClass);
      clazz.getDeclaredConstructors();
        // Possible call to forbidden setAccessible
      clazz.getMethod("", arrayOfClass).setAccessible(false);
      AccessibleObject.setAccessible(null, false);
      Method.setAccessible(null, false);
      Method[] methodsArray = clazz.getMethods();
      int nbMethod;
      for ( nbMethod = 0; nbMethod < methodsArray.length; nbMethod++ ) {
        methodsArray[nbMethod].setAccessible(false);
      }

        // Possible call to forbidden PrivilegedAction
      PrivilegedAction priv = (PrivilegedAction) new Object(); priv.run();
    }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Major


## PMD_AAAI
### Default
#### OriginalId=AvoidAssertAsIdentifier
#### Enabled=false
#### Warning=true
#### DisplayName=Avoid Assert As Identifier
#### HelpText
  Use of the term 'assert' will conflict with newer versions of Java since it is a reserved word.

  Example(s):

  ```java
  public class A {
      public class Foo {
          String assert = "foo";
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Minor


## PMD_AAL
### Default
#### OriginalId=AvoidArrayLoops
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Array Loops
#### HelpText
  Instead of manually copying data between two arrays, use the efficient Arrays.copyOf or System.arraycopy method instead.

  Example(s):

  ``` java
  public class Test {
      public void bar() {
          int[] a = new int[10];
          int[] b = new int[10];
          for (int i=0;i<10;i++) {
              b[i]=a[i];
          }

          int[] c = new int[10];
          // this will trigger the rule
          for (int i=0;i<10;i++) {
              b[i]=a[c[i]];
          }
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Performance Rules

#### Settings
- Priority=Major


## PMD_ABSALIL
### Default
#### OriginalId=AvoidBranchingStatementAsLastInLoop
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Branching Statement As Last In Loop
#### HelpText
  Using a branching statement as the last part of a loop may be a bug, and/or is confusing. Ensure that the usage is not a bug, or consider using another approach.

  Example(s):

  ``` java
  // unusual use of branching statement in a loop
  for (int i = 0; i < 10; i++) {
      if (i*i <= 25) {
          continue;
      }
      break;
  }

  // this makes more sense...
  for (int i = 0; i < 10; i++) {
      if (i*i > 25) {
          break;
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Major


## PMD_ACDC
### Default
#### OriginalId=AvoidCalendarDateCreation
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Calendar Date Creation
#### HelpText
  Problem: A Calendar is a heavyweight object and expensive to create.

  Solution: Use `new Date()`, Java 8+ `java.time.LocalDateTime.now()` or `ZonedDateTime.now()`.

  Example(s):

  ``` java
  import java.time.LocalDateTime;
  import java.util.Calendar;
  import java.util.Date;

  public class DateStuff {
      private Date bad1() {
          return Calendar.getInstance().getTime(); // now
      }
      private Date good1a() {
          return new Date(); // now
      }
      private LocalDateTime good1b() {
          return LocalDateTime.now();
      }
      private long bad2() {
          return Calendar.getInstance().getTimeInMillis();
      }
      private long good2() {
          return System.currentTimeMillis();
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Performance Rules

#### Settings
- Priority=Minor


## PMD_ACF
### Default
#### OriginalId=AvoidCallingFinalize
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Calling Finalize
#### HelpText
  The method Object.finalize() is called by the garbage collector on an object when garbage collection determines that there are no more references to the object. It should not be invoked by application logic.

  Note that Oracle has declared Object.finalize() as deprecated since JDK 9.

  Example(s):

  ``` java
  void foo() {
      Bar b = new Bar();
      b.finalize();
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Major


## PMD_ACG
### Default
#### OriginalId=AccessorClassGeneration
#### Enabled=false
#### Warning=true
#### DisplayName=Accessor Class Generation
#### HelpText
  Instantiation by way of private constructors from outside of the constructor's class often causes the
  generation of an accessor. A factory method, or non-privatization of the constructor can eliminate this
  situation. The generated class file is actually an interface.  It gives the accessing class the ability
  to invoke a new hidden package scope constructor that takes the interface as a supplementary parameter.
  This turns a private constructor effectively into one with package scope, and is challenging to discern.

  Example(s):

  ```java
  public class Outer {
   void method(){
    Inner ic = new Inner();//Causes generation of accessor class
   }
   public class Inner {
    private Inner(){}
   }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Minor


## PMD_ACGE
### Default
#### OriginalId=AvoidCatchingGenericException
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Catching Generic Exception
#### HelpText
  Avoid catching generic exceptions such as NullPointerException, RuntimeException, Exception in try-catch block

  Example(s):

  ``` java
  package com.igate.primitive;

  public class PrimitiveType {

      public void downCastPrimitiveType() {
          try {
              System.out.println(" i [" + i + "]");
          } catch(Exception e) {
              e.printStackTrace();
          } catch(RuntimeException e) {
              e.printStackTrace();
          } catch(NullPointerException e) {
              e.printStackTrace();
          }
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Major


## PMD_ACNPE
### Default
#### OriginalId=AvoidCatchingNPE
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Catching NPE
#### HelpText
  Code should never throw NullPointerExceptions under normal circumstances. A catch block may hide the original error, causing other, more subtle problems later on.

  Example(s):

  ``` java
  public class Foo {
      void bar() {
          try {
              // do something
          } catch (NullPointerException npe) {
          }
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_ACT
### Default
#### OriginalId=AvoidCatchingThrowable
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Catching Throwable
#### HelpText
  Catching Throwable errors is not recommended since its scope is very broad. It includes runtime issues such as OutOfMemoryError that should be exposed and managed separately.

  Example(s):

  ``` java
  public void bar() {
      try {
          // do something
      } catch (Throwable th) {  // should not catch Throwable
          th.printStackTrace();
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Major


## PMD_ACWAM
### Default
#### OriginalId=AbstractClassWithoutAbstractMethod
#### Enabled=true
#### Warning=true
#### DisplayName=Abstract Class Without Abstract Method
#### HelpText
  The abstract class does not contain any abstract methods. An abstract class suggests an incomplete implementation, which is to be completed by subclasses implementing the abstract methods. If the class is intended to be used as a base class only (not to be instantiated directly) a protected constructor can be provided prevent direct instantiation.

  Example(s):

  ``` java
  public abstract class Foo {
    void int method1() { ... }
    void int method2() { ... }
    // consider using abstract methods or removing
    // the abstract modifier and adding protected constructors
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Minor


## PMD_ACWC
### Default
#### OriginalId=AppendCharacterWithChar
#### Enabled=false
#### Warning=true
#### DisplayName=Append Character With Char
#### HelpText
  Avoid concatenating characters as strings in StringBuffer/StringBuilder.append methods.

  Example(s):

  ```java
  StringBuffer sb = new StringBuffer();
  sb.append("a");     // avoid this

  StringBuffer sb = new StringBuffer();
  sb.append('a');     // use this instead
  ```


#### Tags
- /tool/PMD
- /general/Performance Rules

#### Settings
- Priority=Minor


## PMD_ADL
### Default
#### OriginalId=AvoidDuplicateLiterals
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Duplicate Literals
#### HelpText
  Code containing duplicate String literals can usually be improved by declaring the String as a constant field.

  Example(s):

  ``` java
  private void bar() {
       buz("Howdy");
       buz("Howdy");
       buz("Howdy");
       buz("Howdy");
  }
  private void buz(String x) {}
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Major


## PMD_ADLIBDC
### Default
#### OriginalId=AvoidDecimalLiteralsInBigDecimalConstructor
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Decimal Literals In Big Decimal Constructor
#### HelpText
  One might assume that the result of “new BigDecimal(0.1)” is exactly equal to 0.1, but it is actually equal to .1000000000000000055511151231257827021181583404541015625. This is because 0.1 cannot be represented exactly as a double (or as a binary fraction of any finite length). Thus, the long value that is being passed in to the constructor is not exactly equal to 0.1, appearances notwithstanding.

  The (String) constructor, on the other hand, is perfectly predictable: ‘new BigDecimal(“0.1”)’ is exactly equal to 0.1, as one would expect. Therefore, it is generally recommended that the (String) constructor be used in preference to this one.

  Example(s):

  ``` java
  BigDecimal bd = new BigDecimal(1.123);       // loss of precision, this would trigger the rule

  BigDecimal bd = new BigDecimal("1.123");     // preferred approach

  BigDecimal bd = new BigDecimal(12);          // preferred approach, ok for integer values
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_ADNIS
### Default
#### OriginalId=AvoidDeeplyNestedIfStmts
#### Enabled=false
#### Warning=true
#### DisplayName=Avoid Deeply Nested If Stmts
#### HelpText
  Avoid creating deeply nested if-then statements since they are harder to read and error-prone to maintain.

  Example(s):

  ```java
  public class Foo {
    public void bar(int x, int y, int z) {
      if (x>y) {
        if (y>z) {
          if (z==x) {
           // !! too deep
          }
        }
      }
    }
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_ADS
### Default
#### OriginalId=AvoidDollarSigns
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Dollar Signs
#### HelpText
  Avoid using dollar signs in variable/method/class/interface names.

  Example(s):

  ``` java
  public class Fo$o {  // not a recommended name
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_AEAI
### Default
#### OriginalId=AvoidEnumAsIdentifier
#### Enabled=false
#### Warning=true
#### DisplayName=Avoid Enum As Identifier
#### HelpText
  Use of the term 'enum' will conflict with newer versions of Java since it is a reserved word.

  Example(s):

  ```java
  public class A {
      public class Foo {
          String enum = "foo";
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Minor


## PMD_AES
### Default
#### OriginalId=AddEmptyString
#### Enabled=true
#### Warning=true
#### DisplayName=Add Empty String
#### HelpText
  The conversion of literals to strings by concatenating them with empty strings is inefficient. It is much better to use one of the type-specific toString() methods instead.

  Example(s):

  ``` java
  String s = "" + 123;                // inefficient
  String t = Integer.toString(456);   // preferred approach
  ```


#### Tags
- /tool/PMD
- /general/Performance Rules

#### Settings
- Priority=Minor


## PMD_AFLV
### Default
#### OriginalId=AvoidFinalLocalVariable
#### Enabled=false
#### Warning=true
#### DisplayName=Avoid Final Local Variable
#### HelpText
  Avoid using final local variables, turn them into fields.

  Note that this is a controversial rule which is merely useful to enforce a certain code style
  (which is contradictory to good coding practices in most of the cases it's applied to) and
  avoid local literals being declared in a scope smaller than the class.

  Also note, that this rule is the opposite of {% rule "java/codestyle/LocalVariableCouldBeFinal" %}.
  Having both rules enabled results in contradictory violations being reported.

  This rule is deprecated and will be removed with PMD 7.0.0. There is no replacement planned.
  If the goal is to avoid defining constants in a scope smaller than the class, then the rule
  {% rule "java/errorprone/AvoidDuplicateLiterals" %} should be used instead.

  Example(s):

  ```java
  public class MyClass {
      public void foo() {
          final String finalLocalVariable;
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_AFNMMN
### Default
#### OriginalId=AvoidFieldNameMatchingMethodName
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Field Name Matching Method Name
#### HelpText
  It can be confusing to have a field name with the same name as a method. While this is permitted, having information (field) and actions (method) is not clear naming. Developers versed in Smalltalk often prefer this approach as the methods denote accessor methods.

  Example(s):

  ``` java
  public class Foo {
      Object bar;
      // bar is data or an action or both?
      void bar() {
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Minor


## PMD_AFNMTN
### Default
#### OriginalId=AvoidFieldNameMatchingTypeName
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Field Name Matching Type Name
#### HelpText
  It is somewhat confusing to have a field name matching the declaring class name. This probably means that type and/or field names should be chosen more carefully.

  Example(s):

  ``` java
  public class Foo extends Bar {
      int foo;    // There is probably a better name that can be used
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Minor


## PMD_AFS
### Default
#### OriginalId=AvoidFileStream
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid File Stream
#### HelpText
  The FileInputStream and FileOutputStream classes contains a finalizer method which will cause garbage collection pauses. See [JDK-8080225](https://bugs.openjdk.java.net/browse/JDK-8080225) for details.

  The FileReader and FileWriter constructors instantiate FileInputStream and FileOutputStream, again causing garbage collection issues while finalizer methods are called.

  -   Use `Files.newInputStream(Paths.get(fileName))` instead of `new FileInputStream(fileName)`.
  -   Use `Files.newOutputStream(Paths.get(fileName))` instead of `new FileOutputStream(fileName)`.
  -   Use `Files.newBufferedReader(Paths.get(fileName))` instead of `new FileReader(fileName)`.
  -   Use `Files.newBufferedWriter(Paths.get(fileName))` instead of `new FileWriter(fileName)`.

  Please note, that the `java.nio` API does not throw a `FileNotFoundException` anymore, instead it throws a `NoSuchFileException`. If your code dealt explicitly with a `FileNotFoundException`, then this needs to be adjusted. Both exceptions are subclasses of `IOException`, so catching that one covers both.

  Example(s):

  ``` java
  // these instantiations cause garbage collection pauses, even if properly closed

      FileInputStream fis = new FileInputStream(fileName);
      FileOutputStream fos = new FileOutputStream(fileName);
      FileReader fr = new FileReader(fileName);
      FileWriter fw = new FileWriter(fileName);

      // the following instantiations help prevent Garbage Collection pauses, no finalization

      try(InputStream is = Files.newInputStream(Paths.get(fileName))) {
      }
      try(OutputStream os = Files.newOutputStream(Paths.get(fileName))) {
      }
      try(BufferedReader br = Files.newBufferedReader(Paths.get(fileName), StandardCharsets.UTF_8)) {
      }
      try(BufferedWriter wr = Files.newBufferedWriter(Paths.get(fileName), StandardCharsets.UTF_8)) {
      }
  ```


#### Tags
- /tool/PMD
- /general/Performance Rules

#### Settings
- Priority=Critical


## PMD_AICICC
### Default
#### OriginalId=AvoidInstanceofChecksInCatchClause
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Instanceof Checks In Catch Clause
#### HelpText
  Each caught exception type should be handled in its own catch clause.

  Example(s):

  ``` java
  try { // Avoid this
      // do something
  } catch (Exception ee) {
      if (ee instanceof IOException) {
          cleanup();
      }
  }

  try {  // Prefer this:
      // do something
  } catch (IOException ee) {
      cleanup();
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Major


## PMD_AIO
### Default
#### OriginalId=AssignmentInOperand
#### Enabled=true
#### Warning=true
#### DisplayName=Assignment In Operand
#### HelpText
  Avoid assignments in operands; this can make code more complicated and harder to read.

  Example(s):

  ``` java
  public void bar() {
      int x = 2;
      if ((x = getX()) == 3) {
        System.out.println("3!");
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Minor


## PMD_AIOIL
### Default
#### OriginalId=AvoidInstantiatingObjectsInLoops
#### Enabled=false
#### Warning=true
#### DisplayName=Avoid Instantiating Objects In Loops
#### HelpText
  New objects created within loops should be checked to see if they can created outside them and reused.

  Example(s):

  ```java
  public class Something {
      public static void main( String as[] ) {
          for (int i = 0; i < 10; i++) {
              Foo f = new Foo(); // Avoid this whenever you can it's really expensive
          }
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Performance Rules

#### Settings
- Priority=Minor


## PMD_AISD
### Default
#### OriginalId=ArrayIsStoredDirectly
#### Enabled=true
#### Warning=true
#### DisplayName=Array Is Stored Directly
#### HelpText
  Constructors and methods receiving arrays should clone objects and store the copy. This prevents future changes from the user from affecting the original array.

  Example(s):

  ``` java
  public class Foo {
      private String [] x;
          public void foo (String [] param) {
          // Don't do this, make a copy of the array at least
          this.x=param;
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules
- /collection/SEI CERT/OBJ06-J

#### Settings
- Priority=Major


## PMD_ALEI
### Default
#### OriginalId=AvoidLosingExceptionInformation
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Losing Exception Information
#### HelpText
  Statements in a catch block that invoke accessors on the exception without using the information only add to code size. Either remove the invocation, or use the return result.

  Example(s):

  ``` java
  public void bar() {
      try {
          // do something
      } catch (SomeException se) {
          se.getMessage();
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Major


## PMD_ALIIC
### Default
#### OriginalId=AvoidLiteralsInIfCondition
#### Enabled=false
#### Warning=true
#### DisplayName=Avoid Literals In If Condition
#### HelpText
  Avoid using hard-coded literals in conditional statements. By declaring them as static variables
  or private members with descriptive names maintainability is enhanced. By default, the literals "-1" and "0" are ignored.
  More exceptions can be defined with the property "ignoreMagicNumbers".

  The rule doesn't consider deeper expressions by default, but this can be enabled via the property `ignoreExpressions`.
  With this property set to false, if-conditions like `i == 1 + 5` are reported as well. Note that in that case,
  the property ignoreMagicNumbers is not taken into account, if there are multiple literals involved in such an expression.

  Example(s):

  ```java
  private static final int MAX_NUMBER_OF_REQUESTS = 10;

  public void checkRequests() {

      if (i == 10) {                        // magic number, buried in a method
        doSomething();
      }

      if (i == MAX_NUMBER_OF_REQUESTS) {    // preferred approach
        doSomething();
      }

      if (aString.indexOf('.') != -1) {}     // magic number -1, by default ignored
      if (aString.indexOf('.') >= 0) { }     // alternative approach

      if (aDouble > 0.0) {}                  // magic number 0.0
      if (aDouble >= Double.MIN_VALUE) {}    // preferred approach

      // with rule property "ignoreExpressions" set to "false"
      if (i == pos + 5) {}  // violation: magic number 5 within an (additive) expression
      if (i == pos + SUFFIX_LENGTH) {} // preferred approach
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Minor


## PMD_ALOC
### Default
#### OriginalId=AtLeastOneConstructor
#### Enabled=false
#### Warning=true
#### DisplayName=At Least One Constructor
#### HelpText
  Each non-static class should declare at least one constructor.
  Classes with solely static members are ignored, refer to [UseUtilityClassRule](pmd_rules_java_design.html#useutilityclass) to detect those.

  Example(s):

  ```java
  public class Foo {
     // missing constructor
    public void doSomething() { ... }
    public void doOtherThing { ... }
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_AMDF
### Default
#### OriginalId=AvoidMessageDigestField
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Message Digest Field
#### HelpText
  Declaring a MessageDigest instance as a field make this instance directly available to multiple threads. Such sharing of MessageDigest instances should be avoided if possible since it leads to wrong results if the access is not synchronized correctly. Just create a new instance and use it locally, where you need it. Creating a new instance is easier than synchronizing access to a shared instance.

  Example(s):

  ``` java
  import java.security.MessageDigest;
  public class AvoidMessageDigestFieldExample {
      private final MessageDigest sharedMd;
      public AvoidMessageDigestFieldExample() throws Exception {
          sharedMd = MessageDigest.getInstance("SHA-256");
      }
      public byte[] calculateHashShared(byte[] data) {
          // sharing a MessageDigest like this without synchronizing access
          // might lead to wrong results
          sharedMd.reset();
          sharedMd.update(data);
          return sharedMd.digest();
      }

      // better
      public byte[] calculateHash(byte[] data) throws Exception {
          MessageDigest md = MessageDigest.getInstance("SHA-256");
          md.update(data);
          return md.digest();
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Major


## PMD_AMG
### Default
#### OriginalId=AccessorMethodGeneration
#### Enabled=true
#### Warning=true
#### DisplayName=Accessor Method Generation
#### HelpText
  When accessing private fields / methods from another class, the Java compiler will generate accessor methods with package-private visibility. This adds overhead, and to the dex method count on Android. This situation can be avoided by changing the visibility of the field / method from private to package-private.

  Example(s):

  ``` java
  public class OuterClass {
      private int counter;
      /* package */ int id;

      public class InnerClass {
          InnerClass() {
              OuterClass.this.counter++; // wrong accessor method will be generated
          }

          public int getOuterClassId() {
              return OuterClass.this.id; // id is package-private, no accessor method needed
          }
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Minor


## PMD_AMUO
### Default
#### OriginalId=AvoidMultipleUnaryOperators
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Multiple Unary Operators
#### HelpText
  The use of multiple unary operators may be problematic, and/or confusing. Ensure that the intended usage is not a bug, or consider simplifying the expression.

  Example(s):

  ``` java
  // These are typo bugs, or at best needlessly complex and confusing:
  int i = - -1;
  int j = + - +1;
  int z = ~~2;
  boolean b = !!true;
  boolean c = !!!true;

  // These are better:
  int i = 1;
  int j = -1;
  int z = 2;
  boolean b = true;
  boolean c = false;

  // And these just make your brain hurt:
  int i = ~-2;
  int j = -~7;
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Major


## PMD_AN
### Default
#### OriginalId=AbstractNaming
#### Enabled=false
#### Warning=true
#### DisplayName=Abstract Naming
#### HelpText
  Abstract classes should be named 'AbstractXXX'.

  This rule is deprecated and will be removed with PMD 7.0.0. The rule is replaced
  by [Class Naming Conventions](#PMD_CNC).

  Example(s):

  ```java
  public abstract class Foo { // should be AbstractFoo
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_APFIFC
### Default
#### OriginalId=AvoidProtectedFieldInFinalClass
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Protected Field In Final Class
#### HelpText
  Do not use protected fields in final classes since they cannot be subclassed. Clarify your intent by using private or package access modifiers instead.

  Example(s):

  ``` java
  public final class Bar {
    private int x;
    protected int y;  // bar cannot be subclassed, so is y really private or package visible?
    Bar() {}
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_APMIFCNE
### Default
#### OriginalId=AvoidProtectedMethodInFinalClassNotExtending
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Protected Method In Final Class Not Extending
#### HelpText
  Do not use protected methods in most final classes since they cannot be subclassed. This should only be allowed in final classes that extend other classes with protected methods (whose visibility cannot be reduced). Clarify your intent by using private or package access modifiers instead.

  Example(s):

  ``` java
  public final class Foo {
    private int bar() {}
    protected int baz() {} // Foo cannot be subclassed, and doesn't extend anything, so is baz() really private or package visible?
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_APMP
### Default
#### OriginalId=AvoidPrefixingMethodParameters
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Prefixing Method Parameters
#### HelpText
  Prefixing parameters by ‘in’ or ‘out’ pollutes the name of the parameters and reduces code readability. To indicate whether or not a parameter will be modify in a method, its better to document method behavior with Javadoc.

  This rule is deprecated and will be removed with PMD 7.0.0. The rule is replaced by the more general rule [Formal Parameter Naming Conventions](#PMD_FPNC).

  Example(s):

  ``` java
  // Not really clear
  public class Foo {
    public void bar(
        int inLeftOperand,
        Result outRightOperand) {
        outRightOperand.setValue(inLeftOperand * outRightOperand.getValue());
    }
  }
  ```

  ``` java
  // Far more useful
  public class Foo {
    /**
     *
     * @param leftOperand, (purpose), not modified by method.
     * @param rightOperand (purpose), will be modified by the method: contains the result.
     */
    public void bar(
          int leftOperand,
          Result rightOperand) {
          rightOperand.setValue(leftOperand * rightOperand.getValue());
    }
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_APST
### Default
#### OriginalId=AvoidPrintStackTrace
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Print Stack Trace
#### HelpText
  Avoid printStackTrace(); use a logger call instead.

  Example(s):

  ``` java
  class Foo {
      void bar() {
          try {
              // do something
          } catch (Exception e) {
              e.printStackTrace();
          }
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Major


## PMD_ARCV
### Default
#### OriginalId=AvoidReassigningCatchVariables
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Reassigning Catch Variables
#### HelpText
  Reassigning exception variables caught in a catch statement should be avoided because of:

  1.  If it is needed, multi catch can be easily added and code will still compile.

  2.  Following the principle of least surprise we want to make sure that a variable caught in a catch statement is always the one thrown in a try block.

  Example(s):

  ``` java
  public class Foo {
      public void foo() {
          try {
              // do something
          } catch (Exception e) {
              e = new NullPointerException(); // not recommended
          }

          try {
              // do something
          } catch (MyException | ServerException e) {
              e = new RuntimeException(); // won't compile
          }
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Minor


## PMD_ARE
### Default
#### OriginalId=AvoidRethrowingException
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Rethrowing Exception
#### HelpText
  Catch blocks that merely rethrow a caught exception only add to code size and runtime complexity.

  Example(s):

  ``` java
  public void bar() {
      try {
          // do something
      }  catch (SomeException se) {
         throw se;
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_ARLV
### Default
#### OriginalId=AvoidReassigningLoopVariables
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Reassigning Loop Variables
#### HelpText
  Reassigning loop variables can lead to hard-to-find bugs. Prevent or limit how these variables can be changed.

  In foreach-loops, configured by the `foreachReassign` property: - `deny`: Report any reassignment of the loop variable in the loop body. *This is the default.* - `allow`: Don’t check the loop variable. - `firstOnly`: Report any reassignments of the loop variable, except as the first statement in the loop body. *This is useful if some kind of normalization or clean-up of the value before using is permitted, but any other change of the variable is not.*

  In for-loops, configured by the `forReassign` property: - `deny`: Report any reassignment of the control variable in the loop body. *This is the default.* - `allow`: Don’t check the control variable. - `skip`: Report any reassignments of the control variable, except conditional increments/decrements (`++`, `--`, `+=`, `-=`). *This prevents accidental reassignments or unconditional increments of the control variable.*

  Example(s):

  ``` java
  public class Foo {
    private void foo() {
      for (String s : listOfStrings()) {
        s = s.trim(); // OK, when foreachReassign is "firstOnly" or "allow"
        doSomethingWith(s);

        s = s.toUpper(); // OK, when foreachReassign is "allow"
        doSomethingElseWith(s);
      }

      for (int i=0; i < 10; i++) {
        if (check(i)) {
          i++; // OK, when forReassign is "skip" or "allow"
        }

        i = 5;  // OK, when forReassign is "allow"

        doSomethingWith(i);
      }
    }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Minor


## PMD_ARP
### Default
#### OriginalId=AvoidReassigningParameters
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Reassigning Parameters
#### HelpText
  Reassigning values to incoming parameters is not recommended. Use temporary local variables instead.

  Example(s):

  ``` java
  public class Foo {
    private void foo(String bar) {
      bar = "something else";
    }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Minor


## PMD_ASAML
### Default
#### OriginalId=AvoidSynchronizedAtMethodLevel
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Synchronized At Method Level
#### HelpText
  Method-level synchronization can cause problems when new code is added to the method. Block-level synchronization helps to ensure that only the code that needs synchronization gets it.

  Example(s):

  ``` java
  public class Foo {
      // Try to avoid this:
      synchronized void foo() {
          // code, that doesn't need synchronization
          // ...
          // code, that requires synchronization
          if (!sharedData.has("bar")) {
              sharedData.add("bar");
          }
          // more code, that doesn't need synchronization
          // ...
      }
      // Prefer this:
      void bar() {
          // code, that doesn't need synchronization
          // ...
          synchronized(this) {
              if (!sharedData.has("bar")) {
                  sharedData.add("bar");
              }
          }
          // more code, that doesn't need synchronization
          // ...
      }

      // Try to avoid this for static methods:
      static synchronized void fooStatic() {
      }

      // Prefer this:
      static void barStatic() {
          // code, that doesn't need synchronization
          // ...
          synchronized(Foo.class) {
              // code, that requires synchronization
          }
          // more code, that doesn't need synchronization
          // ...
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Multithreading Rules

#### Settings
- Priority=Minor


## PMD_ASBF
### Default
#### OriginalId=AvoidStringBufferField
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid String Buffer Field
#### HelpText
  StringBuffers/StringBuilders can grow considerably, and so may become a source of memory leaks if held within objects with long lifetimes.

  Example(s):

  ``` java
  public class Foo {
      private StringBuffer buffer;    // potential memory leak as an instance variable;
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Minor


## PMD_ATG
### Default
#### OriginalId=AvoidThreadGroup
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Thread Group
#### HelpText
  Avoid using java.lang.ThreadGroup; although it is intended to be used in a threaded environment it contains methods that are not thread-safe.

  Example(s):

  ``` java
  public class Bar {
      void buz() {
          ThreadGroup tg = new ThreadGroup("My threadgroup");
          tg = new ThreadGroup(tg, "my thread group");
          tg = Thread.currentThread().getThreadGroup();
          tg = System.getSecurityManager().getThreadGroup();
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Multithreading Rules

#### Settings
- Priority=Critical


## PMD_ATNFS
### Default
#### OriginalId=AssignmentToNonFinalStatic
#### Enabled=true
#### Warning=true
#### DisplayName=Assignment To Non Final Static
#### HelpText
  Identifies a possible unsafe usage of a static field.

  Example(s):

  ``` java
  public class StaticField {
     static int x;
     public FinalFields(int y) {
      x = y; // unsafe
     }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_ATNIOSE
### Default
#### OriginalId=AvoidThrowingNewInstanceOfSameException
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Throwing New Instance Of Same Exception
#### HelpText
  Catch blocks that merely rethrow a caught exception wrapped inside a new instance of the same type only add to code size and runtime complexity.

  Example(s):

  ``` java
  public void bar() {
      try {
          // do something
      } catch (SomeException se) {
          // harmless comment
          throw new SomeException(se);
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_ATNPE
### Default
#### OriginalId=AvoidThrowingNullPointerException
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Throwing Null Pointer Exception
#### HelpText
  Avoid throwing NullPointerExceptions manually. These are confusing because most people will assume that the virtual machine threw it. To avoid a method being called with a null parameter, you may consider using an IllegalArgumentException instead, making it clearly seen as a programmer-initiated exception. However, there are better ways to handle this:

  > *Effective Java, 3rd Edition, Item 72: Favor the use of standard exceptions*
  >
  > Arguably, every erroneous method invocation boils down to an illegal argument or state, but other exceptions are standardly used for certain kinds of illegal arguments and states. If a caller passes null in some parameter for which null values are prohibited, convention dictates that NullPointerException be thrown rather than IllegalArgumentException.

  To implement that, you are encouraged to use `java.util.Objects.requireNonNull()` (introduced in Java 1.7). This method is designed primarily for doing parameter validation in methods and constructors with multiple parameters.

  Your parameter validation could thus look like the following:

      public class Foo {
          private String exampleValue;

          void setExampleValue(String exampleValue) {
            // check, throw and assignment in a single standard call
            this.exampleValue = Objects.requireNonNull(exampleValue, "exampleValue must not be null!");
          }
        }

  Example(s):

  ``` java
  public class Foo {
      void bar() {
          throw new NullPointerException();
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Critical


## PMD_ATRET
### Default
#### OriginalId=AvoidThrowingRawExceptionTypes
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Throwing Raw Exception Types
#### HelpText
  Avoid throwing certain exception types. Rather than throw a raw RuntimeException, Throwable, Exception, or Error, use a subclassed exception or error instead.

  Example(s):

  ``` java
  public class Foo {
      public void bar() throws Exception {
          throw new Exception();
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Major


## PMD_AUEIS
### Default
#### OriginalId=AvoidUncheckedExceptionsInSignatures
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Unchecked Exceptions In Signatures
#### HelpText
  A method or constructor should not explicitly declare unchecked exceptions in its `throws` clause. Java doesn’t force the caller to handle an unchecked exception, so it’s unnecessary except for documentation. A better practice is to document the exceptional cases with a `@throws` Javadoc tag, which allows being more descriptive.

  Example(s):

  ``` java
  public void foo() throws RuntimeException {
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_AUHCIP
### Default
#### OriginalId=AvoidUsingHardCodedIP
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Using Hard Coded IP
#### HelpText
  Application with hard-coded IP addresses can become impossible to deploy in some cases. Externalizing IP adresses is preferable.

  Example(s):

  ``` java
  public class Foo {
      private String ip = "127.0.0.1";     // not recommended
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules
- /collection/SEI CERT/MSC03-J

#### Settings
- Priority=Major


## PMD_AUNC
### Default
#### OriginalId=AvoidUsingNativeCode
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Using Native Code
#### HelpText
  Unnecessary reliance on Java Native Interface (JNI) calls directly reduces application portability and increases the maintenance burden.

  Example(s):

  ``` java
  public class SomeJNIClass {

       public SomeJNIClass() {
           System.loadLibrary("nativelib");
       }

       static {
           System.loadLibrary("nativelib");
       }

       public void invalidCallsInMethod() throws SecurityException, NoSuchMethodException {
           System.loadLibrary("nativelib");
       }
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Major


## PMD_AUOV
### Default
#### OriginalId=AvoidUsingOctalValues
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Using Octal Values
#### HelpText
  Integer literals should not start with zero since this denotes that the rest of literal will be interpreted as an octal value.

  Example(s):

  ``` java
  int i = 012;    // set i with 10 not 12
  int j = 010;    // set j with 8 not 10
  k = i * j;      // set k with 80 not 120
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_AUST
### Default
#### OriginalId=AvoidUsingShortType
#### Enabled=false
#### Warning=true
#### DisplayName=Avoid Using Short Type
#### HelpText
  Note: this rule is deprecated, as its rationale does not hold.

  Java uses the 'short' type to reduce memory usage, not to optimize calculation. In fact, the JVM does not have any
  arithmetic capabilities for the short type: the JVM must convert the short into an int, do the proper calculation
  and convert the int back to a short. Thus any storage gains found through use of the 'short' type may be offset by
  adverse impacts on performance.

  Example(s):

  ```java
  public class UsingShort {
     private short doNotUseShort = 0;

     public UsingShort() {
      short shouldNotBeUsed = 1;
      doNotUseShort += shouldNotBeUsed;
    }
  }
  ```


#### Tags
- /tool/PMD
- /general/Performance Rules

#### Settings
- Priority=Minor


## PMD_AUV
### Default
#### OriginalId=AvoidUsingVolatile
#### Enabled=false
#### Warning=true
#### DisplayName=Avoid Using Volatile
#### HelpText
  Use of the keyword 'volatile' is generally used to fine tune a Java application, and therefore, requires
  a good expertise of the Java Memory Model. Moreover, its range of action is somewhat misknown. Therefore,
  the volatile keyword should not be used for maintenance purpose and portability.

  Example(s):

  ```java
  public class ThrDeux {
    private volatile String var1; // not suggested
    private          String var2; // preferred
  }
  ```


#### Tags
- /tool/PMD
- /general/Multithreading Rules

#### Settings
- Priority=Minor


## PMD_AbCWAM
### Default
#### OriginalId=AbstractClassWithoutAnyMethod
#### Enabled=true
#### Warning=true
#### DisplayName=Abstract Class Without Any Method
#### HelpText
  If an abstract class does not provides any methods, it may be acting as a simple data container that is not meant to be instantiated. In this case, it is probably better to use a private or protected constructor in order to prevent instantiation than make the class misleadingly abstract.

  Example(s):

  ``` java
  public abstract class Example {
      String field;
      int otherField;
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_BC
### Default
#### OriginalId=BadComparison
#### Enabled=true
#### Warning=true
#### DisplayName=Bad Comparison
#### HelpText
  Avoid equality comparisons with Double.NaN. Due to the implicit lack of representation precision when comparing floating point numbers these are likely to cause logic errors.

  Example(s):

  ``` java
  boolean x = (y == Double.NaN);
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_BGMN
### Default
#### OriginalId=BooleanGetMethodName
#### Enabled=true
#### Warning=true
#### DisplayName=Boolean Get Method Name
#### HelpText
  Methods that return boolean results should be named as predicate statements to denote this. I.e, ‘isReady()’, ‘hasValues()’, ‘canCommit()’, ‘willFail()’, etc. Avoid the use of the ‘get’ prefix for these methods.

  Example(s):

  ``` java
  public boolean getFoo();            // bad
  public boolean isFoo();             // ok
  public boolean getFoo(boolean bar); // ok, unless checkParameterizedMethods=true
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_BI
### Default
#### OriginalId=BooleanInstantiation
#### Enabled=true
#### Warning=true
#### DisplayName=Boolean Instantiation
#### HelpText
  Avoid instantiating Boolean objects; you can reference Boolean.TRUE, Boolean.FALSE, or call Boolean.valueOf() instead. Note that new Boolean() is deprecated since JDK 9 for that reason.

  Example(s):

  ``` java
  Boolean bar = new Boolean("true");        // unnecessary creation, just reference Boolean.TRUE;
  Boolean buz = Boolean.valueOf(false);    // ...., just reference Boolean.FALSE;
  ```


#### Tags
- /tool/PMD
- /general/Performance Rules

#### Settings
- Priority=Minor


## PMD_BII
### Default
#### OriginalId=BigIntegerInstantiation
#### Enabled=true
#### Warning=true
#### DisplayName=Big Integer Instantiation
#### HelpText
  Don’t create instances of already existing BigInteger (BigInteger.ZERO, BigInteger.ONE) and for Java 1.5 onwards, BigInteger.TEN and BigDecimal (BigDecimal.ZERO, BigDecimal.ONE, BigDecimal.TEN)

  Example(s):

  ``` java
  BigInteger bi = new BigInteger(1);       // reference BigInteger.ONE instead
  BigInteger bi2 = new BigInteger("0");    // reference BigInteger.ZERO instead
  BigInteger bi3 = new BigInteger(0.0);    // reference BigInteger.ZERO instead
  BigInteger bi4;
  bi4 = new BigInteger(0);                 // reference BigInteger.ZERO instead
  ```


#### Tags
- /tool/PMD
- /general/Performance Rules

#### Settings
- Priority=Minor


## PMD_BMSS
### Default
#### OriginalId=BeanMembersShouldSerialize
#### Enabled=false
#### Warning=true
#### DisplayName=Bean Members Should Serialize
#### HelpText
  If a class is a bean, or is referenced by a bean directly or indirectly it needs to be serializable.
  Member variables need to be marked as transient, static, or have accessor methods in the class. Marking
  variables as transient is the safest and easiest modification. Accessor methods should follow the Java
  naming conventions, i.e. for a variable named foo, getFoo() and setFoo() accessor methods should be provided.

  Example(s):

  ```java
  private transient int someFoo;  // good, it's transient
  private static int otherFoo;    // also OK
  private int moreFoo;            // OK, has proper accessors, see below
  private int badFoo;             // bad, should be marked transient

  private void setMoreFoo(int moreFoo){
        this.moreFoo = moreFoo;
  }

  private int getMoreFoo(){
        return this.moreFoo;
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Minor


## PMD_BNC
### Default
#### OriginalId=BrokenNullCheck
#### Enabled=true
#### Warning=true
#### DisplayName=Broken Null Check
#### HelpText
  The null check is broken since it will throw a NullPointerException itself. It is likely that you used || instead of && or vice versa.

  Example(s):

  ``` java
  public String bar(String string) {
    // should be &&
      if (string!=null || !string.equals(""))
          return string;
    // should be ||
      if (string==null && string.equals(""))
          return string;
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_ByI
### Default
#### OriginalId=ByteInstantiation
#### Enabled=false
#### Warning=true
#### DisplayName=Byte Instantiation
#### HelpText
  Calling new Byte() causes memory allocation that can be avoided by the static Byte.valueOf().
  It makes use of an internal cache that recycles earlier instances making it more memory efficient.
  Note that new Byte() is deprecated since JDK 9 for that reason.

  Example(s):

  ```java
  public class Foo {
      private Byte i = new Byte(0); // change to Byte i = Byte.valueOf(0);
  }
  ```


#### Tags
- /tool/PMD
- /general/Performance Rules

#### Settings
- Priority=Minor


## PMD_CASR
### Default
#### OriginalId=ConsecutiveAppendsShouldReuse
#### Enabled=true
#### Warning=true
#### DisplayName=Consecutive Appends Should Reuse
#### HelpText
  Consecutive calls to StringBuffer/StringBuilder .append should be chained, reusing the target object. This can improve the performance by producing a smaller bytecode, reducing overhead and improving inlining. A complete analysis can be found [here](https://github.com/pmd/pmd/issues/202#issuecomment-274349067)

  Example(s):

  ``` java
  String foo = " ";

  StringBuffer buf = new StringBuffer();
  buf.append("Hello"); // poor
  buf.append(foo);
  buf.append("World");

  StringBuffer buf = new StringBuffer();
  buf.append("Hello").append(foo).append("World"); // good
  ```


#### Tags
- /tool/PMD
- /general/Performance Rules

#### Settings
- Priority=Minor


## PMD_CBO
### Default
#### OriginalId=CouplingBetweenObjects
#### Enabled=false
#### Warning=true
#### DisplayName=Coupling Between Objects
#### HelpText
  This rule counts the number of unique attributes, local variables, and return types within an object.
  A number higher than the specified threshold can indicate a high degree of coupling.

  Example(s):

  ```java
  import com.Blah;
  import org.Bar;
  import org.Bardo;

  public class Foo {
      private Blah var1;
      private Bar var2;

      //followed by many imports of unique objects
      ObjectC doWork() {
          Bardo var55;
          ObjectA var44;
          ObjectZ var93;
          return something();
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_CC
### Default
#### OriginalId=CyclomaticComplexity
#### Enabled=false
#### Warning=true
#### DisplayName=Cyclomatic Complexity
#### HelpText
  The complexity of methods directly affects maintenance costs and readability. Concentrating too much decisional logic
  in a single method makes its behaviour hard to read and change.

  Cyclomatic complexity assesses the complexity of a method by counting the number of decision points in a method,
  plus one for the method entry. Decision points are places where the control flow jumps to another place in the
  program. As such, they include all control flow statements, such as `if`, `while`, `for`, and `case`. For more
  details on the calculation, see the documentation of the [Cyclo metric](pmd_java_metrics_index.html#cyclomatic-complexity-cyclo).

  Generally, numbers ranging from 1-4 denote low complexity, 5-7 denote moderate complexity, 8-10 denote
  high complexity, and 11+ is very high complexity. By default, this rule reports methods with a complexity >= 10.
  Additionally, classes with many methods of moderate complexity get reported as well once the total of their
  methods' complexities reaches 80, even if none of the methods was directly reported.

  Reported methods should be broken down into several smaller methods. Reported classes should probably be broken down
  into subcomponents.

  Example(s):

  ```java
  class Foo {
    void baseCyclo() {                // Cyclo = 1
      highCyclo();
    }

    void highCyclo() {                // Cyclo = 10: reported!
      int x = 0, y = 2;
      boolean a = false, b = true;

      if (a && (y == 1 ? b : true)) { // +3
        if (y == x) {                 // +1
          while (true) {              // +1
            if (x++ < 20) {           // +1
              break;                  // +1
            }
          }
        } else if (y == t && !d) {    // +2
          x = a ? y : x;              // +1
        } else {
          x = 2;
        }
      }
    }
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_CCEWTA
### Default
#### OriginalId=ClassCastExceptionWithToArray
#### Enabled=true
#### Warning=true
#### DisplayName=Class Cast Exception With To Array
#### HelpText
  When deriving an array of a specific class from your Collection, one should provide an array of the same class as the parameter of the toArray() method. Doing otherwise you will will result in a ClassCastException.

  Example(s):

  ``` java
  Collection c = new ArrayList();
  Integer obj = new Integer(1);
  c.add(obj);

      // this would trigger the rule (and throw a ClassCastException if executed)
  Integer[] a = (Integer [])c.toArray();

     // this is fine and will not trigger the rule
  Integer[] b = (Integer [])c.toArray(new Integer[c.size()]);
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_CCOM
### Default
#### OriginalId=ConstructorCallsOverridableMethod
#### Enabled=true
#### Warning=true
#### DisplayName=Constructor Calls Overridable Method
#### HelpText
  Calling overridable methods during construction poses a risk of invoking methods on an incompletely constructed object and can be difficult to debug. It may leave the sub-class unable to construct its superclass or forced to replicate the construction process completely within itself, losing the ability to call super(). If the default constructor contains a call to an overridable method, the subclass may be completely uninstantiable. Note that this includes method calls throughout the control flow graph - i.e., if a constructor Foo() calls a private method bar() that calls a public method buz(), this denotes a problem.

  Example(s):

  ``` java
  public class SeniorClass {
    public SeniorClass(){
        toString(); //may throw NullPointerException if overridden
    }
    public String toString(){
      return "IAmSeniorClass";
    }
  }
  public class JuniorClass extends SeniorClass {
    private String name;
    public JuniorClass(){
      super(); //Automatic call leads to NullPointerException
      name = "JuniorClass";
    }
    public String toString(){
      return name.toUpperCase();
    }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_CDAM
### Default
#### OriginalId=CommentDefaultAccessModifier
#### Enabled=false
#### Warning=true
#### DisplayName=Comment Default Access Modifier
#### HelpText
  To avoid mistakes if we want that an Annotation, Class, Enum, Method, Constructor or Field have a default access modifier
  we must add a comment at the beginning of it's declaration.
  By default the comment must be `/* default */` or `/* package */`, if you want another, you have to provide a regular expression.
  This rule ignores by default all cases that have a @VisibleForTesting annotation. Use the
  property "ignoredAnnotations" to customize the recognized annotations.

  Example(s):

  ```java
  public class Foo {
      final String stringValue = "some string";
      String getString() {
         return stringValue;
      }

      class NestedFoo {
      }
  }

  // should be
  public class Foo {
      /* default */ final String stringValue = "some string";
      /* default */ String getString() {
         return stringValue;
      }

      /* default */ class NestedFoo {
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_CII
### Default
#### OriginalId=ConstantsInInterface
#### Enabled=true
#### Warning=true
#### DisplayName=Constants In Interface
#### HelpText
  Avoid constants in interfaces. Interfaces should define types, constants are implementation details better placed in classes or enums. See Effective Java, item 19.

  Example(s):

  ``` java
  public interface ConstantInterface {
      public static final int CONST1 = 1; // violation, no fields allowed in interface!
      static final int CONST2 = 1;        // violation, no fields allowed in interface!
      final int CONST3 = 1;               // violation, no fields allowed in interface!
      int CONST4 = 1;                     // violation, no fields allowed in interface!
  }

  // with ignoreIfHasMethods = false
  public interface AnotherConstantInterface {
      public static final int CONST1 = 1; // violation, no fields allowed in interface!

      int anyMethod();
  }

  // with ignoreIfHasMethods = true
  public interface YetAnotherConstantInterface {
      public static final int CONST1 = 1; // no violation

      int anyMethod();
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Minor


## PMD_CIS
### Default
#### OriginalId=CollapsibleIfStatements
#### Enabled=true
#### Warning=true
#### DisplayName=Collapsible If Statements
#### HelpText
  Sometimes two consecutive ‘if’ statements can be consolidated by separating their conditions with a boolean short-circuit operator.

  Example(s):

  ``` java
  void bar() {
      if (x) {            // original implementation
          if (y) {
              // do stuff
          }
      }
  }

  void bar() {
      if (x && y) {        // optimized implementation
          // do stuff
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_CLA
### Default
#### OriginalId=ConsecutiveLiteralAppends
#### Enabled=true
#### Warning=true
#### DisplayName=Consecutive Literal Appends
#### HelpText
  Consecutively calling StringBuffer/StringBuilder.append(…) with literals should be avoided. Since the literals are constants, they can already be combined into a single String literal and this String can be appended in a single method call.

  Example(s):

  ``` java
  StringBuilder buf = new StringBuilder();
  buf.append("Hello").append(" ").append("World");    // poor
  buf.append("Hello World");                          // good

  buf.append('h').append('e').append('l').append('l').append('o'); // poor
  buf.append("hello");                                             // good

  buf.append(1).append('m');  // poor
  buf.append("1m");           // good
  ```


#### Tags
- /tool/PMD
- /general/Performance Rules

#### Settings
- Priority=Minor


## PMD_CMMBP
### Default
#### OriginalId=CloneMethodMustBePublic
#### Enabled=true
#### Warning=true
#### DisplayName=Clone Method Must Be Public
#### HelpText
  The java Manual says “By convention, classes that implement this interface should override Object.clone (which is protected) with a public method.”

  Example(s):

  ``` java
  public class Foo implements Cloneable {
      @Override
      protected Object clone() throws CloneNotSupportedException { // Violation, must be public
      }
  }

  public class Foo implements Cloneable {
      @Override
      protected Foo clone() { // Violation, must be public
      }
  }

  public class Foo implements Cloneable {
      @Override
      public Object clone() // Ok
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Minor


## PMD_CMRTMMCN
### Default
#### OriginalId=CloneMethodReturnTypeMustMatchClassName
#### Enabled=true
#### Warning=true
#### DisplayName=Clone Method Return Type Must Match Class Name
#### HelpText
  If a class implements cloneable the return type of the method clone() must be the class name. That way, the caller of the clone method doesn’t need to cast the returned clone to the correct type.

  Note: This is only possible with Java 1.5 or higher.

  Example(s):

  ``` java
  public class Foo implements Cloneable {
      @Override
      protected Object clone() { // Violation, Object must be Foo
      }
  }

  public class Foo implements Cloneable {
      @Override
      public Foo clone() { //Ok
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Minor


## PMD_CNC
### Default
#### OriginalId=ClassNamingConventions
#### Enabled=false
#### Warning=true
#### DisplayName=Class Naming Conventions
#### HelpText
  Configurable naming conventions for type declarations. This rule reports
              type declarations which do not match the regex that applies to their
              specific kind (e.g. enum or interface). Each regex can be configured through
              properties.

              By default this rule uses the standard Java naming convention (Pascal case),
              and reports utility class names not ending with 'Util'.

  Example(s):

  ```java
  // This is Pascal case, the recommended naming convention in Java
  // Note that the default values of this rule don't allow underscores
  // or accented characters in type names
  public class FooBar {}

  // You may want abstract classes to be named 'AbstractXXX',
  // in which case you can customize the regex for abstract
  // classes to 'Abstract[A-Z]\w+'
  public abstract class Thing {}

  // This class doesn't respect the convention, and will be flagged
  public class Éléphant {}
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_COWE
### Default
#### OriginalId=CompareObjectsWithEquals
#### Enabled=false
#### Warning=true
#### DisplayName=Compare Objects With Equals
#### HelpText
  Use equals() to compare object references; avoid comparing them with ==.

  Example(s):

  ```java
  class Foo {
    boolean bar(String a, String b) {
      return a == b;
    }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_CR
### Default
#### OriginalId=CommentRequired
#### Enabled=false
#### Warning=true
#### DisplayName=Comment Required
#### HelpText
  Denotes whether javadoc (formal) comments are required (or unwanted) for specific language elements.

  Example(s):

  ```java
  /**
  *
  *
  * @author Jon Doe
  */
  ```


#### Tags
- /tool/PMD
- /general/Documentation Rules

#### Settings
- Priority=Minor


## PMD_CRS
### Default
#### OriginalId=CheckResultSet
#### Enabled=true
#### Warning=true
#### DisplayName=Check Result Set
#### HelpText
  Always check the return values of navigation methods (next, previous, first, last) of a ResultSet. If the value return is ‘false’, it should be handled properly.

  Example(s):

  ``` java
  Statement stat = conn.createStatement();
  ResultSet rst = stat.executeQuery("SELECT name FROM person");
  rst.next();     // what if it returns false? bad form
  String firstName = rst.getString(1);

  Statement stat = conn.createStatement();
  ResultSet rst = stat.executeQuery("SELECT name FROM person");
  if (rst.next()) {    // result is properly examined and used
      String firstName = rst.getString(1);
      } else  {
          // handle missing data
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Critical


## PMD_CS
### Default
#### OriginalId=CommentSize
#### Enabled=false
#### Warning=true
#### DisplayName=Comment Size
#### HelpText
  Determines whether the dimensions of non-header comments found are within the specified limits.

  Example(s):

  ```java
  /**
  *
  *   too many lines!
  *
  *
  *
  *
  *
  *
  *
  *
  *
  *
  *
  *
  */
  ```


#### Tags
- /tool/PMD
- /general/Documentation Rules

#### Settings
- Priority=Minor


## PMD_CSB
### Default
#### OriginalId=ControlStatementBraces
#### Enabled=true
#### Warning=true
#### DisplayName=Control Statement Braces
#### HelpText
  Enforce a policy for braces on control statements. It is recommended to use braces on ‘if … else’ statements and loop statements, even if they are optional. This usually makes the code clearer, and helps prepare the future when you need to add another statement. That said, this rule lets you control which statements are required to have braces via properties.

              From 6.2.0 on, this rule supersedes WhileLoopMustUseBraces, ForLoopMustUseBraces, IfStmtMustUseBraces,
              and IfElseStmtMustUseBraces.

  Example(s):

  ``` java
  while (true)    // not recommended
    x++;

  while (true) {  // preferred approach
    x++;
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_CSF
### Default
#### OriginalId=CallSuperFirst
#### Enabled=false
#### Warning=true
#### DisplayName=Call Super First
#### HelpText
  Super should be called at the start of the method

  Example(s):

  ```java
  public class DummyActivity extends Activity {
      public void onCreate(Bundle bundle) {
          // missing call to super.onCreate(bundle)
          foo();
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Minor


## PMD_CSIC
### Default
#### OriginalId=CallSuperInConstructor
#### Enabled=false
#### Warning=true
#### DisplayName=Call Super In Constructor
#### HelpText
  It is a good practice to call super() in a constructor. If super() is not called but
  another constructor (such as an overloaded constructor) is called, this rule will not report it.

  Example(s):

  ```java
  public class Foo extends Bar{
    public Foo() {
     // call the constructor of Bar
     super();
    }
   public Foo(int code) {
    // do something with code
     this();
     // no problem with this
    }
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_CSL
### Default
#### OriginalId=CallSuperLast
#### Enabled=false
#### Warning=true
#### DisplayName=Call Super Last
#### HelpText
  Super should be called at the end of the method

  Example(s):

  ```java
  public class DummyActivity extends Activity {
      public void onPause() {
          foo();
          // missing call to super.onPause()
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Minor


## PMD_CSR
### Default
#### OriginalId=CheckSkipResult
#### Enabled=true
#### Warning=true
#### DisplayName=Check Skip Result
#### HelpText
  The skip() method may skip a smaller number of bytes than requested. Check the returned value to find out if it was the case or not.

  Example(s):

  ``` java
  public class Foo {

     private FileInputStream _s = new FileInputStream("file");

     public void skip(int n) throws IOException {
        _s.skip(n); // You are not sure that exactly n bytes are skipped
     }

     public void skipExactly(int n) throws IOException {
        while (n != 0) {
           long skipped = _s.skip(n);
           if (skipped == 0)
              throw new EOFException();
           n -= skipped;
        }
     }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_CT
### Default
#### OriginalId=ConfusingTernary
#### Enabled=false
#### Warning=true
#### DisplayName=Confusing Ternary
#### HelpText
  Avoid negation within an "if" expression with an "else" clause.  For example, rephrase:
  `if (x != y) diff(); else same();` as: `if (x == y) same(); else diff();`.

  Most "if (x != y)" cases without an "else" are often return cases, so consistent use of this
  rule makes the code easier to read.  Also, this resolves trivial ordering problems, such
  as "does the error case go first?" or "does the common case go first?".

  Example(s):

  ```java
  boolean bar(int x, int y) {
      return (x != y) ? diff : same;
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_CTCNSE
### Default
#### OriginalId=CloneThrowsCloneNotSupportedException
#### Enabled=true
#### Warning=true
#### DisplayName=Clone Throws Clone Not Supported Exception
#### HelpText
  The method clone() should throw a CloneNotSupportedException.

  Example(s):

  ``` java
  public class MyClass implements Cloneable{
      public Object clone() { // will cause an error
           MyClass clone = (MyClass)super.clone();
           return clone;
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Major


## PMD_CWOPCSBF
### Default
#### OriginalId=ClassWithOnlyPrivateConstructorsShouldBeFinal
#### Enabled=true
#### Warning=true
#### DisplayName=Class With Only Private Constructors Should Be Final
#### HelpText
  A class with only private constructors should be final, unless the private constructor is invoked by a inner class.

  Example(s):

  ``` java
  public class Foo {  //Should be final
      private Foo() { }
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_ClMMIC
### Default
#### OriginalId=CloneMethodMustImplementCloneable
#### Enabled=true
#### Warning=true
#### DisplayName=Clone Method Must Implement Cloneable
#### HelpText
  The method clone() should only be implemented if the class implements the Cloneable interface with the exception of a final method that only throws CloneNotSupportedException.

  The rule can also detect, if the class implements or extends a Cloneable class.

  Example(s):

  ``` java
  public class MyClass {
   public Object clone() throws CloneNotSupportedException {
    return foo;
   }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Major


## PMD_ClR
### Default
#### OriginalId=CloseResource
#### Enabled=true
#### Warning=true
#### DisplayName=Close Resource
#### HelpText
  Ensure that resources (like `java.sql.Connection`, `java.sql.Statement`, and `java.sql.ResultSet` objects and any subtype of `java.lang.AutoCloseable`) are always closed after use. Failing to do so might result in resource leaks.

  Note: It suffices to configure the super type, e.g. `java.lang.AutoClosable`, so that this rule automatically triggers on any subtype (e.g. `java.io.FileInputStream`). Additionally specifying `java.sql.Connection` helps in detecting the types, if the type resolution / auxclasspath is not correctly setup.

  Note: Since PMD 6.16.0 the default value for the property `types` contains `java.lang.AutoCloseable` and detects now cases where the standard `java.io.*Stream` classes are involved. In order to restore the old behaviour, just remove “AutoCloseable” from the types.

  Example(s):

  ``` java
  public class Bar {
      public void withSQL() {
          Connection c = pool.getConnection();
          try {
              // do stuff
          } catch (SQLException ex) {
             // handle exception
          } finally {
              // oops, should close the connection using 'close'!
              // c.close();
          }
      }

      public void withFile() {
          InputStream file = new FileInputStream(new File("/tmp/foo"));
          try {
              int c = file.in();
          } catch (IOException e) {
              // handle exception
          } finally {
              // TODO: close file
          }
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_CoC
### Default
#### OriginalId=CommentContent
#### Enabled=false
#### Warning=true
#### DisplayName=Comment Content
#### HelpText
  A rule for the politically correct... we don't want to offend anyone.

  Example(s):

  ```java
  //OMG, this is horrible, Bob is an idiot !!!
  ```


#### Tags
- /tool/PMD
- /general/Documentation Rules

#### Settings
- Priority=Minor


## PMD_DAA
### Default
#### OriginalId=DataflowAnomalyAnalysis
#### Enabled=false
#### Warning=true
#### DisplayName=Dataflow Anomaly Analysis
#### HelpText
  The dataflow analysis tracks local definitions, undefinitions and references to variables on different paths on the data flow.
  From those informations there can be found various problems.

  1. DU - Anomaly: A recently defined variable is undefined. These anomalies may appear in normal source text.
  2. DD - Anomaly: A recently defined variable is redefined. This is ominous but don't have to be a bug.

  This rule is deprecated. Use {% rule "java/bestpractices/UnusedAssignment" %} in category bestpractices instead.

  Example(s):

  ```java
  public void foo() {
    int buz = 5;
    buz = 6; // redefinition of buz -> dd-anomaly
    foo(buz);
    buz = 2;
  } // buz is undefined when leaving scope -> du-anomaly
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Minor


## PMD_DBI
### Default
#### OriginalId=DoubleBraceInitialization
#### Enabled=true
#### Warning=true
#### DisplayName=Double Brace Initialization
#### HelpText
  Double brace initialisation is a pattern to initialise eg collections concisely. But it implicitly generates a new .class file, and the object holds a strong reference to the enclosing object. For those reasons, it is preferable to initialize the object normally, even though it’s verbose.

              This rule counts any anonymous class which only has a single initializer as an instance of double-brace
              initialization. There is currently no way to find out whether a method called in the initializer is not
              accessible from outside the anonymous class, and those legit cases should be suppressed for the time being.

  Example(s):

  ``` java
  // this is double-brace initialization
  return new ArrayList<String>(){{
      add("a");
      add("b");
      add("c");
  }};

  // the better way is to not create an anonymous class:
  List<String> a = new ArrayList<>();
  a.add("a");
  a.add("b");
  a.add("c");
  return a;
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Minor


## PMD_DC
### Default
#### OriginalId=DataClass
#### Enabled=true
#### Warning=true
#### DisplayName=Data Class
#### HelpText
  Data Classes are simple data holders, which reveal most of their state, and without complex functionality. The lack of functionality may indicate that their behaviour is defined elsewhere, which is a sign of poor data-behaviour proximity. By directly exposing their internals, Data Classes break encapsulation, and therefore reduce the system’s maintainability and understandability. Moreover, classes tend to strongly rely on their data representation, which makes for a brittle design.

  Refactoring a Data Class should focus on restoring a good data-behaviour proximity. In most cases, that means moving the operations defined on the data back into the class. In some other cases it may make sense to remove entirely the class and move the data into the former client classes.

  Example(s):

  ``` java
  public class DataClass {

    public int bar = 0;
    public int na = 0;
    private int bee = 0;

    public void setBee(int n) {
      bee = n;
    }
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_DCL
### Default
#### OriginalId=DoubleCheckedLocking
#### Enabled=true
#### Warning=true
#### DisplayName=Double Checked Locking
#### HelpText
  Partially created objects can be returned by the Double Checked Locking pattern when used in Java. An optimizing JRE may assign a reference to the baz variable before it calls the constructor of the object the reference points to.

  Note: With Java 5, you can make Double checked locking work, if you declare the variable to be `volatile`.

  For more details refer to: <a href="http://www.javaworld.com/javaworld/jw-02-2001/jw-0209-double.html" class="uri" class="uri">http://www.javaworld.com/javaworld/jw-02-2001/jw-0209-double.html</a> or <a href="http://www.cs.umd.edu/~pugh/java/memoryModel/DoubleCheckedLocking.html" class="uri" class="uri">http://www.cs.umd.edu/~pugh/java/memoryModel/DoubleCheckedLocking.html</a>

  Example(s):

  ``` java
  public class Foo {
      /*volatile */ Object baz = null; // fix for Java5 and later: volatile
      Object bar() {
          if (baz == null) { // baz may be non-null yet not fully created
              synchronized(this) {
                  if (baz == null) {
                      baz = new Object();
                  }
                }
          }
          return baz;
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Multithreading Rules

#### Settings
- Priority=Critical


## PMD_DCTR
### Default
#### OriginalId=DontCallThreadRun
#### Enabled=true
#### Warning=true
#### DisplayName=Dont Call Thread Run
#### HelpText
  Explicitly calling Thread.run() method will execute in the caller’s thread of control. Instead, call Thread.start() for the intended behavior.

  Example(s):

  ``` java
  Thread t = new Thread();
  t.run();            // use t.start() instead
  new Thread().run(); // same violation
  ```


#### Tags
- /tool/PMD
- /general/Multithreading Rules

#### Settings
- Priority=Critical


## PMD_DI
### Default
#### OriginalId=DuplicateImports
#### Enabled=true
#### Warning=true
#### DisplayName=Duplicate Imports
#### HelpText
  Duplicate or overlapping import statements should be avoided.

  Example(s):

  ``` java
  import java.lang.String;
  import java.lang.*;
  public class Foo {}
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_DIJL
### Default
#### OriginalId=DontImportJavaLang
#### Enabled=true
#### Warning=true
#### DisplayName=Dont Import Java Lang
#### HelpText
  Avoid importing anything from the package ‘java.lang’. These classes are automatically imported (JLS 7.5.3).

  Example(s):

  ``` java
  import java.lang.String;    // this is unnecessary

  public class Foo {}

  // --- in another source code file...

  import java.lang.*;         // this is bad

  public class Foo {}
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_DIS
### Default
#### OriginalId=DontImportSun
#### Enabled=true
#### Warning=true
#### DisplayName=Dont Import Sun
#### HelpText
  Avoid importing anything from the ’sun.\*’ packages. These packages are not portable and are likely to change.

  Example(s):

  ``` java
  import sun.misc.foo;
  public class Foo {}
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Major


## PMD_DLNLISS
### Default
#### OriginalId=DefaultLabelNotLastInSwitchStmt
#### Enabled=true
#### Warning=true
#### DisplayName=Default Label Not Last In Switch Stmt
#### HelpText
  By convention, the default label should be the last label in a switch statement.

  Example(s):

  ``` java
  public class Foo {
    void bar(int a) {
     switch (a) {
      case 1:  // do something
         break;
      default:  // the default case should be last, by convention
         break;
      case 2:
         break;
     }
    }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Minor


## PMD_DNCGCE
### Default
#### OriginalId=DoNotCallGarbageCollectionExplicitly
#### Enabled=true
#### Warning=true
#### DisplayName=Do Not Call Garbage Collection Explicitly
#### HelpText
  Calls to System.gc(), Runtime.getRuntime().gc(), and System.runFinalization() are not advised. Code should have the same behavior whether the garbage collection is disabled using the option -Xdisableexplicitgc or not. Moreover, “modern” jvms do a very good job handling garbage collections. If memory usage issues unrelated to memory leaks develop within an application, it should be dealt with JVM options rather than within the code itself.

  Example(s):

  ``` java
  public class GCCall {
      public GCCall() {
          // Explicit gc call !
          System.gc();
      }

      public void doSomething() {
          // Explicit gc call !
          Runtime.getRuntime().gc();
      }

      public explicitGCcall() {
          // Explicit gc call !
          System.gc();
      }

      public void doSomething() {
          // Explicit gc call !
          Runtime.getRuntime().gc();
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Major


## PMD_DNCSE
### Default
#### OriginalId=DoNotCallSystemExit
#### Enabled=false
#### Warning=true
#### DisplayName=Do Not Call System Exit
#### HelpText
  DoNotCallSystemExit

#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_DNEJLE
### Default
#### OriginalId=DoNotExtendJavaLangError
#### Enabled=true
#### Warning=true
#### DisplayName=Do Not Extend Java Lang Error
#### HelpText
  Errors are system exceptions. Do not extend them.

  Example(s):

  ``` java
  public class Foo extends Error { }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Critical


## PMD_DNEJLT
### Default
#### OriginalId=DoNotExtendJavaLangThrowable
#### Enabled=true
#### Warning=true
#### DisplayName=Do Not Extend Java Lang Throwable
#### HelpText
  Extend Exception or RuntimeException instead of Throwable.

  Example(s):

  ``` java
  public class Foo extends Throwable { }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_DNHCSDC
### Default
#### OriginalId=DoNotHardCodeSDCard
#### Enabled=false
#### Warning=true
#### DisplayName=Do Not Hard Code SDCard
#### HelpText
  Use Environment.getExternalStorageDirectory() instead of "/sdcard"

  Example(s):

  ```java
  public class MyActivity extends Activity {
      protected void foo() {
          String storageLocation = "/sdcard/mypackage";   // hard-coded, poor approach

         storageLocation = Environment.getExternalStorageDirectory() + "/mypackage"; // preferred approach
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Minor


## PMD_DNTEIF
### Default
#### OriginalId=DoNotThrowExceptionInFinally
#### Enabled=true
#### Warning=true
#### DisplayName=Do Not Throw Exception In Finally
#### HelpText
  Throwing exceptions within a ‘finally’ block is confusing since they may mask other exceptions or code defects. Note: This is a PMD implementation of the Lint4j rule “A throw in a finally block”

  Example(s):

  ``` java
  public class Foo {
      public void bar() {
          try {
              // Here do some stuff
          } catch( Exception e) {
              // Handling the issue
          } finally {
              // is this really a good idea ?
              throw new Exception();
          }
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_DNTVM
### Default
#### OriginalId=DoNotTerminateVM
#### Enabled=true
#### Warning=true
#### DisplayName=Do Not Terminate VM
#### HelpText
  Web applications should not call `System.exit()`, since only the web container or the application server should stop the JVM. Otherwise a web application would terminate all other applications running on the same application server.

  This rule also checks for the equivalent calls `Runtime.getRuntime().exit()` and `Runtime.getRuntime().halt()`.

  This rule was called *DoNotCallSystemExit* until PMD 6.29.0.

  Example(s):

  ``` java
  public void bar() {
      System.exit(0);                 // never call this when running in an application server!
  }
  public void foo() {
      Runtime.getRuntime().exit(0);   // never stop the JVM manually, the container will do this.
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_DNUT
### Default
#### OriginalId=DoNotUseThreads
#### Enabled=false
#### Warning=true
#### DisplayName=Do Not Use Threads
#### HelpText
  The J2EE specification explicitly forbids the use of threads. Threads are resources, that should be managed and monitored by the J2EE server.
  If the application creates threads on its own or uses own custom thread pools, then these threads are not managed, which could lead to resource exhaustion.
  Also EJB's might be moved between machines in a cluster and only managed resources can be moved along.

  Example(s):

  ```java
  // This is not allowed
  public class UsingThread extends Thread {

  }

  // Neither this,
  public class UsingExecutorService {

      public void methodX() {
          ExecutorService executorService = Executors.newFixedThreadPool(5);
      }
  }

  // Nor this,
  public class Example implements ExecutorService {

  }

  // Nor this,
  public class Example extends AbstractExecutorService {

  }

  // Nor this
  public class UsingExecutors {

      public void methodX() {
          Executors.newSingleThreadExecutor().submit(() -> System.out.println("Hello!"));
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Multithreading Rules

#### Settings
- Priority=Minor


## PMD_DP
### Default
#### OriginalId=DefaultPackage
#### Enabled=true
#### Warning=true
#### DisplayName=Default Package
#### HelpText
  Use explicit scoping instead of accidental usage of default package private level. The rule allows methods and fields annotated with Guava’s <span class="citation" data-cites="VisibleForTesting">@VisibleForTesting</span> and JUnit 5’s annotations.


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_DTC
### Default
#### OriginalId=DetachedTestCase
#### Enabled=true
#### Warning=true
#### DisplayName=Detached Test Case
#### HelpText
  The method appears to be a test case since it has public or default visibility, non-static access, no arguments, no return value, has no annotations, but is a member of a class that has one or more JUnit test cases. If it is a utility method, it should likely have private visibility. If it is an ignored test, it should be annotated with <span class="citation" data-cites="Test">@Test</span> and <span class="citation" data-cites="Ignore">@Ignore</span>.

  Example(s):

  ``` java
  public class MyTest {
      @Test
      public void someTest() {
      }

      // violation: Not annotated
      public void someOtherTest () {
      }

  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Minor


## PMD_DUFTFLI
### Default
#### OriginalId=DontUseFloatTypeForLoopIndices
#### Enabled=true
#### Warning=true
#### DisplayName=Dont Use Float Type For Loop Indices
#### HelpText
  Don’t use floating point for loop indices. If you must use floating point, use double unless you’re certain that float provides enough precision and you have a compelling performance need (space or time).

  Example(s):

  ``` java
  public class Count {
    public static void main(String[] args) {
      final int START = 2000000000;
      int count = 0;
      for (float f = START; f < START + 50; f++)
        count++;
        //Prints 0 because (float) START == (float) (START + 50).
        System.out.println(count);
        //The termination test misbehaves due to floating point granularity.
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_EAFC
### Default
#### OriginalId=ExceptionAsFlowControl
#### Enabled=true
#### Warning=true
#### DisplayName=Exception As Flow Control
#### HelpText
  Using Exceptions as form of flow control is not recommended as they obscure true exceptions when debugging. Either add the necessary validation or use an alternate control structure.

  Example(s):

  ``` java
  public void bar() {
      try {
          try {
          } catch (Exception e) {
              throw new WrapperException(e);
              // this is essentially a GOTO to the WrapperException catch block
          }
      } catch (WrapperException e) {
          // do some more stuff
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Major


## PMD_ECB
### Default
#### OriginalId=EmptyCatchBlock
#### Enabled=true
#### Warning=true
#### DisplayName=Empty Catch Block
#### HelpText
  Empty Catch Block finds instances where an exception is caught, but nothing is done. In most circumstances, this swallows an exception which should either be acted on or reported.

  Example(s):

  ``` java
  public void doSomething() {
      try {
          FileInputStream fis = new FileInputStream("/tmp/bugger");
      } catch (IOException ioe) {
          // not good
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_ECL
### Default
#### OriginalId=ExcessiveClassLength
#### Enabled=false
#### Warning=true
#### DisplayName=Excessive Class Length
#### HelpText
  Excessive class file lengths are usually indications that the class may be burdened with excessive
  responsibilities that could be provided by external classes or functions. In breaking these methods
  apart the code becomes more manageable and ripe for reuse.

  Example(s):

  ```java
  public class Foo {
      public void bar1() {
          // 1000 lines of code
      }
      public void bar2() {
          // 1000 lines of code
      }
      public void bar3() {
          // 1000 lines of code
      }

      public void barN() {
          // 1000 lines of code
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_EF
### Default
#### OriginalId=EmptyFinalizer
#### Enabled=true
#### Warning=true
#### DisplayName=Empty Finalizer
#### HelpText
  Empty finalize methods serve no purpose and should be removed. Note that Oracle has declared Object.finalize() as deprecated since JDK 9.

  Example(s):

  ``` java
  public class Foo {
     protected void finalize() {}
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Minor


## PMD_EFB
### Default
#### OriginalId=EmptyFinallyBlock
#### Enabled=true
#### Warning=true
#### DisplayName=Empty Finally Block
#### HelpText
  Empty finally blocks serve no purpose and should be removed.

  Example(s):

  ``` java
  public class Foo {
      public void bar() {
          try {
              int x=2;
          } finally {
              // empty!
          }
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Minor


## PMD_EI
### Default
#### OriginalId=ExcessiveImports
#### Enabled=false
#### Warning=true
#### DisplayName=Excessive Imports
#### HelpText
  A high number of imports can indicate a high degree of coupling within an object. This rule
  counts the number of unique imports and reports a violation if the count is above the
  user-specified threshold.

  Example(s):

  ```java
  import blah.blah.Baz;
  import blah.blah.Bif;
  // 28 others from the same package elided
  public class Foo {
      public void doWork() {}
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_EIS
### Default
#### OriginalId=EmptyIfStmt
#### Enabled=true
#### Warning=true
#### DisplayName=Empty If Stmt
#### HelpText
  Empty If Statement finds instances where a condition is checked but nothing is done about it.

  Example(s):

  ``` java
  public class Foo {
   void bar(int x) {
    if (x == 0) {
     // empty!
    }
   }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Major


## PMD_EMIACSBA
### Default
#### OriginalId=EmptyMethodInAbstractClassShouldBeAbstract
#### Enabled=true
#### Warning=true
#### DisplayName=Empty Method In Abstract Class Should Be Abstract
#### HelpText
  Empty or auto-generated methods in an abstract class should be tagged as abstract. This helps to remove their inapproprate usage by developers who should be implementing their own versions in the concrete subclasses.

  Example(s):

  ``` java
  public abstract class ShouldBeAbstract {
      public Object couldBeAbstract() {
          // Should be abstract method ?
          return null;
      }

      public void couldBeAbstract() {
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Major


## PMD_EML
### Default
#### OriginalId=ExcessiveMethodLength
#### Enabled=false
#### Warning=true
#### DisplayName=Excessive Method Length
#### HelpText
  When methods are excessively long this usually indicates that the method is doing more than its
  name/signature might suggest. They also become challenging for others to digest since excessive
  scrolling causes readers to lose focus.
  Try to reduce the method length by creating helper methods and removing any copy/pasted code.

  Example(s):

  ```java
  public void doSomething() {
      System.out.println("Hello world!");
      System.out.println("Hello world!");
      // 98 copies omitted for brevity.
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_EN
### Default
#### OriginalId=EqualsNull
#### Enabled=true
#### Warning=true
#### DisplayName=Equals Null
#### HelpText
  Tests for null should not use the equals() method. The ‘==’ operator should be used instead.

  Example(s):

  ``` java
  String x = "foo";

  if (x.equals(null)) {   // bad form
      doSomething();
  }

  if (x == null) {        // preferred
      doSomething();
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_EO
### Default
#### OriginalId=ExtendsObject
#### Enabled=true
#### Warning=true
#### DisplayName=Extends Object
#### HelpText
  No need to explicitly extend Object.

  Example(s):

  ``` java
  public class Foo extends Object {     // not required
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_EPC
### Default
#### OriginalId=ExcessivePublicCount
#### Enabled=false
#### Warning=true
#### DisplayName=Excessive Public Count
#### HelpText
  Classes with large numbers of public methods and attributes require disproportionate testing efforts
  since combinational side effects grow rapidly and increase risk. Refactoring these classes into
  smaller ones not only increases testability and reliability but also allows new variations to be
  developed easily.

  Example(s):

  ```java
  public class Foo {
      public String value;
      public Bar something;
      public Variable var;
      // [... more more public attributes ...]

      public void doWork() {}
      public void doMoreWork() {}
      public void doWorkAgain() {}
      // [... more more public methods ...]
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_EPL
### Default
#### OriginalId=ExcessiveParameterList
#### Enabled=false
#### Warning=true
#### DisplayName=Excessive Parameter List
#### HelpText
  Methods with numerous parameters are a challenge to maintain, especially if most of them share the
  same datatype. These situations usually denote the need for new objects to wrap the numerous parameters.

  Example(s):

  ```java
  public void addPerson(      // too many arguments liable to be mixed up
      int birthYear, int birthMonth, int birthDate, int height, int weight, int ssn) {

      . . . .
  }

  public void addPerson(      // preferred approach
      Date birthdate, BodyMeasurements measurements, int ssn) {

      . . . .
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_ESB
### Default
#### OriginalId=EmptySynchronizedBlock
#### Enabled=true
#### Warning=true
#### DisplayName=Empty Synchronized Block
#### HelpText
  Empty synchronized blocks serve no purpose and should be removed.

  Example(s):

  ``` java
  public class Foo {
      public void bar() {
          synchronized (this) {
              // empty!
          }
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Major


## PMD_ESNIL
### Default
#### OriginalId=EmptyStatementNotInLoop
#### Enabled=true
#### Warning=true
#### DisplayName=Empty Statement Not In Loop
#### HelpText
  An empty statement (or a semicolon by itself) that is not used as the sole body of a ‘for’ or ‘while’ loop is probably a bug. It could also be a double semicolon, which has no purpose and should be removed.

  Example(s):

  ``` java
  public void doit() {
        // this is probably not what you meant to do
        ;
        // the extra semicolon here this is not necessary
        System.out.println("look at the extra semicolon");;
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Minor


## PMD_ESS
### Default
#### OriginalId=EmptySwitchStatements
#### Enabled=true
#### Warning=true
#### DisplayName=Empty Switch Statements
#### HelpText
  Empty switch statements serve no purpose and should be removed.

  Example(s):

  ``` java
  public void bar() {
      int x = 2;
      switch (x) {
          // once there was code here
          // but it's been commented out or something
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Major


## PMD_ETB
### Default
#### OriginalId=EmptyTryBlock
#### Enabled=true
#### Warning=true
#### DisplayName=Empty Try Block
#### HelpText
  Avoid empty try blocks - what’s the point?

  Example(s):

  ``` java
  public class Foo {
      public void bar() {
          try {
          } catch (Exception e) {
              e.printStackTrace();
          }
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Major


## PMD_EWS
### Default
#### OriginalId=EmptyWhileStmt
#### Enabled=true
#### Warning=true
#### DisplayName=Empty While Stmt
#### HelpText
  Empty While Statement finds all instances where a while statement does nothing. If it is a timing loop, then you should use Thread.sleep() for it; if it is a while loop that does a lot in the exit expression, rewrite it to make it clearer.

  Example(s):

  ``` java
  void bar(int a, int b) {
      while (a == b) {
          // empty!
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_EmI
### Default
#### OriginalId=EmptyInitializer
#### Enabled=false
#### Warning=true
#### DisplayName=Empty Initializer
#### HelpText
  Empty initializers serve no purpose and should be removed.

  Example(s):

  ```java
  public class Foo {

     static {} // Why ?

     {} // Again, why ?

  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Minor


## PMD_EmSB
### Default
#### OriginalId=EmptyStatementBlock
#### Enabled=true
#### Warning=true
#### DisplayName=Empty Statement Block
#### HelpText
  Empty block statements serve no purpose and should be removed.

  Example(s):

  ``` java
  public class Foo {

     private int _bar;

     public void setBar(int bar) {
        { _bar = bar; } // Why not?
        {} // But remove this.
     }

  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Minor


## PMD_FDNCSF
### Default
#### OriginalId=FinalizeDoesNotCallSuperFinalize
#### Enabled=true
#### Warning=true
#### DisplayName=Finalize Does Not Call Super Finalize
#### HelpText
  If the finalize() is implemented, its last action should be to call super.finalize. Note that Oracle has declared Object.finalize() as deprecated since JDK 9.

  Example(s):

  ``` java
  protected void finalize() {
      something();
      // neglected to call super.finalize()
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_FDSBASOC
### Default
#### OriginalId=FieldDeclarationsShouldBeAtStartOfClass
#### Enabled=true
#### Warning=true
#### DisplayName=Field Declarations Should Be At Start Of Class
#### HelpText
  Fields should be declared at the top of the class, before any method declarations, constructors, initializers or inner classes.

  Example(s):

  ``` java
  public class HelloWorldBean {

    // Field declared before methods / inner classes - OK
    private String _thing;

    public String getMessage() {
      return "Hello World!";
    }

    // Field declared after methods / inner classes - avoid this
    private String _fieldInWrongLocation;
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_FFCBS
### Default
#### OriginalId=FinalFieldCouldBeStatic
#### Enabled=true
#### Warning=true
#### DisplayName=Final Field Could Be Static
#### HelpText
  If a final field is assigned to a compile-time constant, it could be made static, thus saving overhead in each object at runtime.

  Example(s):

  ``` java
  public class Foo {
    public final int BAR = 42; // this could be static and save some space
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_FLCBF
### Default
#### OriginalId=ForLoopCanBeForeach
#### Enabled=true
#### Warning=true
#### DisplayName=For Loop Can Be Foreach
#### HelpText
  Reports loops that can be safely replaced with the foreach syntax. The rule considers loops over lists, arrays and iterators. A loop is safe to replace if it only uses the index variable to access an element of the list or array, only has one update statement, and loops through *every* element of the list or array left to right.

  Example(s):

  ``` java
  public class MyClass {
    void loop(List<String> l) {
      for (int i = 0; i < l.size(); i++) { // pre Java 1.5
        System.out.println(l.get(i));
      }

      for (String s : l) {        // post Java 1.5
        System.out.println(s);
      }
    }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Minor


## PMD_FLMUB
### Default
#### OriginalId=ForLoopsMustUseBraces
#### Enabled=false
#### Warning=true
#### DisplayName=For Loops Must Use Braces
#### HelpText
  Avoid using 'for' statements without using curly braces. If the code formatting or
  indentation is lost then it becomes difficult to separate the code being controlled
  from the rest.

  This rule is deprecated and will be removed with PMD 7.0.0. The rule is replaced
  by the rule [Control Statement Braces](#PMD_CSB).

  Example(s):

  ```java
  for (int i = 0; i < 42; i++)
     foo();
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_FLSBWL
### Default
#### OriginalId=ForLoopShouldBeWhileLoop
#### Enabled=true
#### Warning=true
#### DisplayName=For Loop Should Be While Loop
#### HelpText
  Some for loops can be simplified to while loops, this makes them more concise.

  Example(s):

  ``` java
  public class Foo {
      void bar() {
          for (;true;) true; // No Init or Update part, may as well be: while (true)
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_FLVC
### Default
#### OriginalId=ForLoopVariableCount
#### Enabled=true
#### Warning=true
#### DisplayName=For Loop Variable Count
#### HelpText
  Having a lot of control variables in a ‘for’ loop makes it harder to see what range of values the loop iterates over. By default this rule allows a regular ‘for’ loop with only one variable.

  Example(s):

  ``` java
  // this will be reported with the default setting of at most one control variable in a for loop
  for (int i = 0, j = 0; i < 10; i++, j += 2) {
     foo();
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Minor


## PMD_FNC
### Default
#### OriginalId=FieldNamingConventions
#### Enabled=false
#### Warning=true
#### DisplayName=Field Naming Conventions
#### HelpText
  Configurable naming conventions for field declarations. This rule reports variable declarations
              which do not match the regex that applies to their specific kind ---e.g. constants (static final),
              enum constant, final field. Each regex can be configured through properties.

              By default this rule uses the standard Java naming convention (Camel case), and uses the ALL_UPPER
              convention for constants and enum constants.

  Example(s):

  ```java
  class Foo {
                  int myField = 1; // This is in camel case, so it's ok
                  int my_Field = 1; // This contains an underscore, it's not ok by default
                                    // but you may allow it, or even require the "my_" prefix

                  final int FinalField = 1; // you may configure a different convention for final fields,
                                            // e.g. here PascalCase: [A-Z][a-zA-Z0-9]*

                  interface Interface {
                      double PI = 3.14; // interface "fields" use the constantPattern property
                  }

                  enum AnEnum {
                      ORG, NET, COM; // These use a separate property but are set to ALL_UPPER by default
                  }
              }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_FO
### Default
#### OriginalId=FinalizeOverloaded
#### Enabled=true
#### Warning=true
#### DisplayName=Finalize Overloaded
#### HelpText
  Methods named finalize() should not have parameters. It is confusing and most likely an attempt to overload Object.finalize(). It will not be called by the VM.

  Note that Oracle has declared Object.finalize() as deprecated since JDK 9.

  Example(s):

  ``` java
  public class Foo {
      // this is confusing and probably a bug
      protected void finalize(int a) {
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_FOCSF
### Default
#### OriginalId=FinalizeOnlyCallsSuperFinalize
#### Enabled=true
#### Warning=true
#### DisplayName=Finalize Only Calls Super Finalize
#### HelpText
  If the finalize() is implemented, it should do something besides just calling super.finalize(). Note that Oracle has declared Object.finalize() as deprecated since JDK 9.

  Example(s):

  ``` java
  protected void finalize() {
      super.finalize();
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Minor


## PMD_FPNC
### Default
#### OriginalId=FormalParameterNamingConventions
#### Enabled=false
#### Warning=true
#### DisplayName=Formal Parameter Naming Conventions
#### HelpText
  Configurable naming conventions for formal parameters of methods and lambdas.
              This rule reports formal parameters which do not match the regex that applies to their
              specific kind (e.g. lambda parameter, or final formal parameter). Each regex can be
              configured through properties.

              By default this rule uses the standard Java naming convention (Camel case).

  Example(s):

  ```java
  class Foo {

                  abstract void bar(int myInt); // This is Camel case, so it's ok

                  void bar(int my_i) { // this will be reported

                  }

                  void lambdas() {

                      // lambdas parameters can be configured separately
                      Consumer<String> lambda1 = s_str -> { };

                      // lambda parameters with an explicit type can be configured separately
                      Consumer<String> lambda1 = (String str) -> { };

                  }

              }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_FSBP
### Default
#### OriginalId=FinalizeShouldBeProtected
#### Enabled=true
#### Warning=true
#### DisplayName=Finalize Should Be Protected
#### HelpText
  When overriding the finalize(), the new method should be set as protected. If made public, other classes may invoke it at inappropriate times.

  Note that Oracle has declared Object.finalize() as deprecated since JDK 9.

  Example(s):

  ``` java
  public void finalize() {
      // do something
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_GC
### Default
#### OriginalId=GodClass
#### Enabled=false
#### Warning=true
#### DisplayName=God Class
#### HelpText
  The God Class rule detects the God Class design flaw using metrics. God classes do too many things,
  are very big and overly complex. They should be split apart to be more object-oriented.
  The rule uses the detection strategy described in "Object-Oriented Metrics in Practice".
  The violations are reported against the entire class.

  See also the references:

  Michele Lanza and Radu Marinescu. Object-Oriented Metrics in Practice:
  Using Software Metrics to Characterize, Evaluate, and Improve the Design
  of Object-Oriented Systems. Springer, Berlin, 1 edition, October 2006. Page 80.

#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_GLS
### Default
#### OriginalId=GuardLogStatement
#### Enabled=true
#### Warning=true
#### DisplayName=Guard Log Statement
#### HelpText
  Whenever using a log level, one should check if the loglevel is actually enabled, or otherwise skip the associate String creation and manipulation.

  Example(s):

  ``` java
  // Add this for performance
      if (log.isDebugEnabled() { ...
          log.debug("log something" + " and " + "concat strings");
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Minor


## PMD_GN
### Default
#### OriginalId=GenericsNaming
#### Enabled=true
#### Warning=true
#### DisplayName=Generics Naming
#### HelpText
  Names for references to generic values should be limited to a single uppercase letter.

  Example(s):

  ``` java
  public interface GenericDao<E extends BaseModel, K extends Serializable> extends BaseDao {
      // This is ok...
  }

  public interface GenericDao<E extends BaseModel, K extends Serializable> {
      // Also this
  }

  public interface GenericDao<e extends BaseModel, K extends Serializable> {
      // 'e' should be an 'E'
  }

  public interface GenericDao<EF extends BaseModel, K extends Serializable> {
     // 'EF' is not ok.
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_HCCK
### Default
#### OriginalId=HardCodedCryptoKey
#### Enabled=true
#### Warning=true
#### DisplayName=Hard Coded Crypto Key
#### HelpText
  Do not use hard coded values for cryptographic operations. Please store keys outside of source code.

  Example(s):

  ``` java
  public class Foo {
      void good() {
          SecretKeySpec secretKeySpec = new SecretKeySpec(Properties.getKey(), "AES");
      }

      void bad() {
          SecretKeySpec secretKeySpec = new SecretKeySpec("my secret here".getBytes(), "AES");
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Security Rules

#### Settings
- Priority=Critical


## PMD_ICB
### Default
#### OriginalId=IdenticalCatchBranches
#### Enabled=true
#### Warning=true
#### DisplayName=Identical Catch Branches
#### HelpText
  Identical `catch` branches use up vertical space and increase the complexity of code without adding functionality. It’s better style to collapse identical branches into a single multi-catch branch.

  Example(s):

  ``` java
  try {
      // do something
  } catch (IllegalArgumentException e) {
      throw e;
  } catch (IllegalStateException e) { // Can be collapsed into the previous block
      throw e;
  }

  try {
      // do something
  } catch (IllegalArgumentException | IllegalStateException e) { // This is better
      throw e;
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_ICI
### Default
#### OriginalId=InsecureCryptoIv
#### Enabled=true
#### Warning=true
#### DisplayName=Insecure Crypto Iv
#### HelpText
  Do not use hard coded initialization vector in cryptographic operations. Please use a randomly generated IV.

  Example(s):

  ``` java
  public class Foo {
      void good() {
          SecureRandom random = new SecureRandom();
          byte iv[] = new byte[16];
          random.nextBytes(bytes);
      }

      void bad() {
          byte[] iv = new byte[] { 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, };
      }

      void alsoBad() {
          byte[] iv = "secret iv in here".getBytes();
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Security Rules

#### Settings
- Priority=Critical


## PMD_IESC
### Default
#### OriginalId=InefficientEmptyStringCheck
#### Enabled=false
#### Warning=true
#### DisplayName=Inefficient Empty String Check
#### HelpText
  String.trim().length() == 0 (or String.trim().isEmpty() for the same reason) is an inefficient
  way to check if a String is really blank, as it creates a new String object just to check its size.
  Consider creating a static function that loops through a string, checking Character.isWhitespace()
  on each character and returning false if a non-whitespace character is found. A Smarter code to
  check for an empty string would be:

  ```java
  private boolean checkTrimEmpty(String str) {
      for(int i = 0; i < str.length(); i++) {
          if(!Character.isWhitespace(str.charAt(i))) {
              return false;
          }
      }
      return true;
  }
  ```

  You can refer to Apache's StringUtils#isBlank (in commons-lang),
  Spring's StringUtils#hasText (in the Spring framework) or Google's
  CharMatcher#whitespace (in Guava) for existing implementations (some might
  include the check for != null).

  Example(s):

  ```java
  public void bar(String string) {
      if (string != null && string.trim().length() > 0) {
          doSomething();
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Performance Rules

#### Settings
- Priority=Minor


## PMD_IESMUB
### Default
#### OriginalId=IfElseStmtsMustUseBraces
#### Enabled=false
#### Warning=true
#### DisplayName=If Else Stmts Must Use Braces
#### HelpText
  Avoid using if..else statements without using surrounding braces. If the code formatting
  or indentation is lost then it becomes difficult to separate the code being controlled
  from the rest.

  This rule is deprecated and will be removed with PMD 7.0.0. The rule is replaced
  by the rule [Control Statement Braces](#PMD_CSB).

  Example(s):

  ```java
  // this is OK
  if (foo) x++;

     // but this is not
  if (foo)
         x = x+1;
     else
         x = x-1;
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_IF
### Default
#### OriginalId=ImmutableField
#### Enabled=true
#### Warning=true
#### DisplayName=Immutable Field
#### HelpText
  Identifies private fields whose values never change once object initialization ends either in the declaration of the field or by a constructor. This helps in converting existing classes to becoming immutable ones. Note that this rule does not enforce referenced object to be immutable itself. A class can still be mutable, even if all its member fields are declared final. This is referred to as shallow immutability. For more information on mutability, see Effective Java, 3rd Edition, Item 17: Minimize mutability.

  Example(s):

  ``` java
  public class Foo {
    private int x; // could be final
    public Foo() {
        x = 7;
    }
    public void foo() {
       int a = x + 2;
    }
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_IFSP
### Default
#### OriginalId=ImportFromSamePackage
#### Enabled=true
#### Warning=true
#### DisplayName=Import From Same Package
#### HelpText
  There is no need to import a type that lives in the same package.

  Example(s):

  ``` java
  package foo;

  import foo.Buz;     // no need for this
  import foo.*;       // or this

  public class Bar{}
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Minor


## PMD_II
### Default
#### OriginalId=IntegerInstantiation
#### Enabled=false
#### Warning=true
#### DisplayName=Integer Instantiation
#### HelpText
  Calling new Integer() causes memory allocation that can be avoided by the static Integer.valueOf().
  It makes use of an internal cache that recycles earlier instances making it more memory efficient.
  Note that new Integer() is deprecated since JDK 9 for that reason.

  Example(s):

  ```java
  public class Foo {
      private Integer i = new Integer(0); // change to Integer i = Integer.valueOf(0);
  }
  ```


#### Tags
- /tool/PMD
- /general/Performance Rules

#### Settings
- Priority=Minor


## PMD_ILMF
### Default
#### OriginalId=InvalidLogMessageFormat
#### Enabled=true
#### Warning=true
#### DisplayName=Invalid Log Message Format
#### HelpText
  Check for messages in slf4j and log4j2 (since 6.19.0) loggers with non matching number of arguments and placeholders.

  Since 6.32.0 in addition to parameterized message placeholders (`{}`) also format specifiers of string formatted messages are supported (`%s`).

  Example(s):

  ``` java
  LOGGER.error("forget the arg {}");
  LOGGER.error("forget the arg %s");
  LOGGER.error("too many args {}", "arg1", "arg2");
  LOGGER.error("param {}", "arg1", new IllegalStateException("arg")); //The exception is shown separately, so is correct.
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Minor


## PMD_IO
### Default
#### OriginalId=IdempotentOperations
#### Enabled=true
#### Warning=true
#### DisplayName=Idempotent Operations
#### HelpText
  Avoid idempotent operations - they have no effect.

  Example(s):

  ``` java
  public class Foo {
   public void bar() {
    int x = 2;
    x = x;
   }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Major


## PMD_IS4MF
### Default
#### OriginalId=InvalidSlf4jMessageFormat
#### Enabled=false
#### Warning=true
#### DisplayName=Invalid Slf4j Message Format
#### HelpText
  InvalidSlf4jMessageFormat

#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Minor


## PMD_ISB
### Default
#### OriginalId=InefficientStringBuffering
#### Enabled=true
#### Warning=true
#### DisplayName=Inefficient String Buffering
#### HelpText
  Avoid concatenating non-literals in a StringBuffer constructor or append() since intermediate buffers will need to be be created and destroyed by the JVM.

  Example(s):

  ``` java
  // Avoid this, two buffers are actually being created here
  StringBuffer sb = new StringBuffer("tmp = "+System.getProperty("java.io.tmpdir"));

  // do this instead
  StringBuffer sb = new StringBuffer("tmp = ");
  sb.append(System.getProperty("java.io.tmpdir"));
  ```


#### Tags
- /tool/PMD
- /general/Performance Rules

#### Settings
- Priority=Minor


## PMD_ISBD
### Default
#### OriginalId=InsufficientStringBufferDeclaration
#### Enabled=false
#### Warning=true
#### DisplayName=Insufficient String Buffer Declaration
#### HelpText
  Failing to pre-size a StringBuffer or StringBuilder properly could cause it to re-size many times
  during runtime. This rule attempts to determine the total number the characters that are actually
  passed into StringBuffer.append(), but represents a best guess "worst case" scenario. An empty
  StringBuffer/StringBuilder constructor initializes the object to 16 characters. This default
  is assumed if the length of the constructor can not be determined.

  Example(s):

  ```java
  StringBuffer bad = new StringBuffer();
  bad.append("This is a long string that will exceed the default 16 characters");

  StringBuffer good = new StringBuffer(41);
  good.append("This is a long string, which is pre-sized");
  ```


#### Tags
- /tool/PMD
- /general/Performance Rules

#### Settings
- Priority=Minor


## PMD_ISMUB
### Default
#### OriginalId=IfStmtsMustUseBraces
#### Enabled=false
#### Warning=true
#### DisplayName=If Stmts Must Use Braces
#### HelpText
  Avoid using if statements without using braces to surround the code block. If the code
  formatting or indentation is lost then it becomes difficult to separate the code being
  controlled from the rest.

  This rule is deprecated and will be removed with PMD 7.0.0. The rule is replaced
  by the rule [Control Statement Braces](#PMD_CSB).

  Example(s):

  ```java
  if (foo)    // not recommended
      x++;

  if (foo) {  // preferred approach
      x++;
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_ITGC
### Default
#### OriginalId=InstantiationToGetClass
#### Enabled=true
#### Warning=true
#### DisplayName=Instantiation To Get Class
#### HelpText
  Avoid instantiating an object just to call getClass() on it; use the .class public member instead.

  Example(s):

  ``` java
  // replace this
  Class c = new String().getClass();

  // with this:
  Class c = String.class;
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Major


## PMD_JI
### Default
#### OriginalId=JumbledIncrementer
#### Enabled=true
#### Warning=true
#### DisplayName=Jumbled Incrementer
#### HelpText
  Avoid jumbled loop incrementers - its usually a mistake, and is confusing even if intentional.

  Example(s):

  ``` java
  public class JumbledIncrementerRule1 {
      public void foo() {
          for (int i = 0; i < 10; i++) {          // only references 'i'
              for (int k = 0; k < 20; i++) {      // references both 'i' and 'k'
                  System.out.println("Hello");
              }
          }
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_JU4SSUSA
### Default
#### OriginalId=JUnit4SuitesShouldUseSuiteAnnotation
#### Enabled=false
#### Warning=true
#### DisplayName=JUnit4 Suites Should Use Suite Annotation
#### HelpText
  In JUnit 3, test suites are indicated by the suite() method. In JUnit 4, suites are indicated
  through the @RunWith(Suite.class) annotation.

  Example(s):

  ```java
  public class BadExample extends TestCase{

      public static Test suite(){
          return new Suite();
      }
  }

  @RunWith(Suite.class)
  @SuiteClasses( { TestOne.class, TestTwo.class })
  public class GoodTest {
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Minor


## PMD_JU4TSUAA
### Default
#### OriginalId=JUnit4TestShouldUseAfterAnnotation
#### Enabled=false
#### Warning=true
#### DisplayName=JUnit4 Test Should Use After Annotation
#### HelpText
  In JUnit 3, the tearDown method was used to clean up all data entities required in running tests.
  JUnit 4 skips the tearDown method and executes all methods annotated with @After after running each test.
  JUnit 5 introduced @AfterEach and @AfterAll annotations to execute methods after each test or after all tests in the class, respectively.

  Example(s):

  ```java
  public class MyTest {
      public void tearDown() {
          bad();
      }
  }
  public class MyTest2 {
      @After public void tearDown() {
          good();
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Minor


## PMD_JU4TSUBA
### Default
#### OriginalId=JUnit4TestShouldUseBeforeAnnotation
#### Enabled=false
#### Warning=true
#### DisplayName=JUnit4 Test Should Use Before Annotation
#### HelpText
  In JUnit 3, the setUp method was used to set up all data entities required in running tests.
  JUnit 4 skips the setUp method and executes all methods annotated with @Before before all tests.
  JUnit 5 introduced @BeforeEach and @BeforeAll annotations to execute methods before each test or before all tests in the class, respectively.

  Example(s):

  ```java
  public class MyTest {
      public void setUp() {
          bad();
      }
  }
  public class MyTest2 {
      @Before public void setUp() {
          good();
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Minor


## PMD_JU4TSUTA
### Default
#### OriginalId=JUnit4TestShouldUseTestAnnotation
#### Enabled=false
#### Warning=true
#### DisplayName=JUnit4 Test Should Use Test Annotation
#### HelpText
  In JUnit 3, the framework executed all methods which started with the word test as a unit test.
  In JUnit 4, only methods annotated with the @Test annotation are executed.
  In JUnit 5, one of the following annotations should be used for tests: @Test, @RepeatedTest, @TestFactory, @TestTemplate or @ParameterizedTest.

  Example(s):

  ```java
  public class MyTest {
      public void testBad() {
          doSomething();
      }

      @Test
      public void testGood() {
          doSomething();
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Minor


## PMD_JUASIM
### Default
#### OriginalId=JUnitAssertionsShouldIncludeMessage
#### Enabled=true
#### Warning=true
#### DisplayName=JUnit Assertions Should Include Message
#### HelpText
  JUnit assertions should include an informative message - i.e., use the three-argument version of assertEquals(), not the two-argument version.

  Example(s):

  ``` java
  public class Foo extends TestCase {
      public void testSomething() {
          assertEquals("foo", "bar");
          // Use the form:
          // assertEquals("Foo does not equals bar", "foo", "bar");
          // instead
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Minor


## PMD_JUS
### Default
#### OriginalId=JUnitSpelling
#### Enabled=true
#### Warning=true
#### DisplayName=JUnit Spelling
#### HelpText
  In JUnit 3, the setUp method is used to set up all data entities required in running tests. The tearDown method is used to clean up all data entities required in running tests. You should not misspell method name if you want your test to set up and clean up everything correctly.

  Example(s):

  ``` java
  import junit.framework.*;

  public class Foo extends TestCase {
      public void setup() {}    // oops, should be setUp
      public void TearDown() {} // oops, should be tearDown
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_JUSS
### Default
#### OriginalId=JUnitStaticSuite
#### Enabled=true
#### Warning=true
#### DisplayName=JUnit Static Suite
#### HelpText
  The suite() method in a JUnit test needs to be both public and static.

  Example(s):

  ``` java
  import junit.framework.*;

  public class Foo extends TestCase {
      public void suite() {}         // oops, should be static
      private static void suite() {} // oops, should be public
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_JUTCTMA
### Default
#### OriginalId=JUnitTestContainsTooManyAsserts
#### Enabled=true
#### Warning=true
#### DisplayName=JUnit Test Contains Too Many Asserts
#### HelpText
  Unit tests should not contain too many asserts. Many asserts are indicative of a complex test, for which it is harder to verify correctness. Consider breaking the test scenario into multiple, shorter test scenarios. Customize the maximum number of assertions used by this Rule to suit your needs.

  This rule checks for JUnit4, JUnit5 and TestNG Tests, as well as methods starting with “test”.

  Example(s):

  ``` java
  public class MyTestCase extends TestCase {
      // Ok
      public void testMyCaseWithOneAssert() {
          boolean myVar = false;
          assertFalse("should be false", myVar);
      }

      // Bad, too many asserts (assuming max=1)
      public void testMyCaseWithMoreAsserts() {
          boolean myVar = false;
          assertFalse("myVar should be false", myVar);
          assertEquals("should equals false", false, myVar);
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Minor


## PMD_JUTSIA
### Default
#### OriginalId=JUnitTestsShouldIncludeAssert
#### Enabled=true
#### Warning=true
#### DisplayName=JUnit Tests Should Include Assert
#### HelpText
  JUnit tests should include at least one assertion. This makes the tests more robust, and using assert with messages provide the developer a clearer idea of what the test does.

  Example(s):

  ``` java
  public class Foo extends TestCase {
     public void testSomething() {
        Bar b = findBar();
     // This is better than having a NullPointerException
     // assertNotNull("bar not found", b);
     b.work();
     }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Major


## PMD_JUUE
### Default
#### OriginalId=JUnitUseExpected
#### Enabled=false
#### Warning=true
#### DisplayName=JUnit Use Expected
#### HelpText
  In JUnit4, use the @Test(expected) annotation to denote tests that should throw exceptions.

  Example(s):

  ```java
  public class MyTest {
      @Test
      public void testBad() {
          try {
              doSomething();
              fail("should have thrown an exception");
          } catch (Exception e) {
          }
      }

      @Test(expected=Exception.class)
      public void testGood() {
          doSomething();
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Minor


## PMD_LFIC
### Default
#### OriginalId=LiteralsFirstInComparisons
#### Enabled=true
#### Warning=true
#### DisplayName=Literals First In Comparisons
#### HelpText
  Position literals first in all String comparisons, if the second argument is null then NullPointerExceptions can be avoided, they will just return false. Note that switching literal positions for compareTo and compareToIgnoreCase may change the result, see examples.

  Example(s):

  ``` java
  class Foo {
      boolean bar(String x) {
          return x.equals("2"); // should be "2".equals(x)
      }
      boolean bar(String x) {
          return x.equalsIgnoreCase("2"); // should be "2".equalsIgnoreCase(x)
      }
      boolean bar(String x) {
          return (x.compareTo("bar") > 0); // should be: "bar".compareTo(x) < 0
      }
      boolean bar(String x) {
          return (x.compareToIgnoreCase("bar") > 0); // should be: "bar".compareToIgnoreCase(x) < 0
      }
      boolean bar(String x) {
          return x.contentEquals("bar"); // should be "bar".contentEquals(x)
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Critical


## PMD_LHNC
### Default
#### OriginalId=LocalHomeNamingConvention
#### Enabled=true
#### Warning=true
#### DisplayName=Local Home Naming Convention
#### HelpText
  The Local Home interface of a Session EJB should be suffixed by ‘LocalHome’.

  Example(s):

  ``` java
  public interface MyBeautifulLocalHome extends javax.ejb.EJBLocalHome {} // proper name

  public interface MissingProperSuffix extends javax.ejb.EJBLocalHome {}  // non-standard name
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Major


## PMD_LI
### Default
#### OriginalId=LogicInversion
#### Enabled=true
#### Warning=true
#### DisplayName=Logic Inversion
#### HelpText
  Use opposite operator instead of negating the whole expression with a logic complement operator.

  Example(s):

  ``` java
  public boolean bar(int a, int b) {

      if (!(a == b)) { // use !=
           return false;
       }

      if (!(a < b)) { // use >=
           return false;
      }

      return true;
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_LINSF
### Default
#### OriginalId=LoggerIsNotStaticFinal
#### Enabled=true
#### Warning=true
#### DisplayName=Logger Is Not Static Final
#### HelpText
  In most cases, the Logger reference can be declared as static and final.

  This rule is deprecated and will be removed with PMD 7.0.0. The rule is replaced by [Proper Logger](#PMD_PL).

  Example(s):

  ``` java
  public class Foo{
      Logger log = Logger.getLogger(Foo.class.getName());                 // not recommended

      static final Logger log = Logger.getLogger(Foo.class.getName());    // preferred approach
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Minor


## PMD_LISNC
### Default
#### OriginalId=LocalInterfaceSessionNamingConvention
#### Enabled=true
#### Warning=true
#### DisplayName=Local Interface Session Naming Convention
#### HelpText
  The Local Interface of a Session EJB should be suffixed by ‘Local’.

  Example(s):

  ``` java
  public interface MyLocal extends javax.ejb.EJBLocalObject {}                // proper name

  public interface MissingProperSuffix extends javax.ejb.EJBLocalObject {}    // non-standard name
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Major


## PMD_LN
### Default
#### OriginalId=LinguisticNaming
#### Enabled=false
#### Warning=true
#### DisplayName=Linguistic Naming
#### HelpText
  This rule finds Linguistic Naming Antipatterns. It checks for fields, that are named, as if they should
              be boolean but have a different type. It also checks for methods, that according to their name, should
              return a boolean, but don't. Further, it checks, that getters return something and setters won't.
              Finally, it checks that methods, that start with "to" - so called transform methods - actually return
              something, since according to their name, they should convert or transform one object into another.
              There is additionally an option, to check for methods that contain "To" in their name - which are
              also transform methods. However, this is disabled by default, since this detection is prone to
              false positives.

              For more information, see [Linguistic Antipatterns - What They Are and How
  Developers Perceive Them](https://doi.org/10.1007/s10664-014-9350-8).

  Example(s):

  ```java
  public class LinguisticNaming {
      int isValid;    // the field name indicates a boolean, but it is an int.
      boolean isTrue; // correct type of the field

      void myMethod() {
          int hasMoneyLocal;      // the local variable name indicates a boolean, but it is an int.
          boolean hasSalaryLocal; // correct naming and type
      }

      // the name of the method indicates, it is a boolean, but the method returns an int.
      int isValid() {
          return 1;
      }
      // correct naming and return type
      boolean isSmall() {
          return true;
      }

      // the name indicates, this is a setter, but it returns something
      int setName() {
          return 1;
      }

      // the name indicates, this is a getter, but it doesn't return anything
      void getName() {
          // nothing to return?
      }

      // the name indicates, it transforms an object and should return the result
      void toDataType() {
          // nothing to return?
      }
      // the name indicates, it transforms an object and should return the result
      void grapeToWine() {
          // nothing to return?
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_LOD
### Default
#### OriginalId=LawOfDemeter
#### Enabled=false
#### Warning=true
#### DisplayName=Law Of Demeter
#### HelpText
  The Law of Demeter is a simple rule, that says "only talk to friends". It helps to reduce coupling between classes
  or objects.

  See also the references:

  *   Andrew Hunt, David Thomas, and Ward Cunningham. The Pragmatic Programmer. From Journeyman to Master. Addison-Wesley Longman, Amsterdam, October 1999.;
  *   K.J. Lieberherr and I.M. Holland. Assuring good style for object-oriented programs. Software, IEEE, 6(5):38–48, 1989.;
  *   <http://www.ccs.neu.edu/home/lieber/LoD.html>
  *   <http://en.wikipedia.org/wiki/Law_of_Demeter>

  Example(s):

  ```java
  public class Foo {
      /**
       * This example will result in two violations.
       */
      public void example(Bar b) {
          // this method call is ok, as b is a parameter of "example"
          C c = b.getC();

          // this method call is a violation, as we are using c, which we got from B.
          // We should ask b directly instead, e.g. "b.doItOnC();"
          c.doIt();

          // this is also a violation, just expressed differently as a method chain without temporary variables.
          b.getC().doIt();

          // a constructor call, not a method call.
          D d = new D();
          // this method call is ok, because we have create the new instance of D locally.
          d.doSomethingElse();
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_LPC
### Default
#### OriginalId=LoosePackageCoupling
#### Enabled=false
#### Warning=true
#### DisplayName=Loose Package Coupling
#### HelpText
  Avoid using classes from the configured package hierarchy outside of the package hierarchy,
  except when using one of the configured allowed classes.

  Example(s):

  ```java
  package some.package;

  import some.other.package.subpackage.subsubpackage.DontUseThisClass;

  public class Bar {
      DontUseThisClass boo = new DontUseThisClass();
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_LV
### Default
#### OriginalId=LongVariable
#### Enabled=false
#### Warning=true
#### DisplayName=Long Variable
#### HelpText
  Fields, formal arguments, or local variable names that are too long can make the code difficult to follow.

  Example(s):

  ```java
  public class Something {
      int reallyLongIntName = -3;             // VIOLATION - Field
      public static void main( String argumentsList[] ) { // VIOLATION - Formal
          int otherReallyLongName = -5;       // VIOLATION - Local
          for (int interestingIntIndex = 0;   // VIOLATION - For
               interestingIntIndex < 10;
               interestingIntIndex ++ ) {
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_LVCBF
### Default
#### OriginalId=LocalVariableCouldBeFinal
#### Enabled=false
#### Warning=true
#### DisplayName=Local Variable Could Be Final
#### HelpText
  A local variable assigned only once can be declared final.

  Example(s):

  ```java
  public class Bar {
      public void foo () {
      String txtA = "a";          // if txtA will not be assigned again it is better to do this:
      final String txtB = "b";
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_LVNC
### Default
#### OriginalId=LocalVariableNamingConventions
#### Enabled=false
#### Warning=true
#### DisplayName=Local Variable Naming Conventions
#### HelpText
  Configurable naming conventions for local variable declarations and other locally-scoped
              variables. This rule reports variable declarations which do not match the regex that applies to their
              specific kind (e.g. final variable, or catch-clause parameter). Each regex can be configured through
              properties.

              By default this rule uses the standard Java naming convention (Camel case).

  Example(s):

  ```java
  class Foo {
                  void bar() {
                      int localVariable = 1; // This is in camel case, so it's ok
                      int local_variable = 1; // This will be reported unless you change the regex

                      final int i_var = 1; // final local variables can be configured separately

                      try {
                          foo();
                      } catch (IllegalArgumentException e_illegal) {
                          // exception block parameters can be configured separately
                      }

                  }
              }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_LoC
### Default
#### OriginalId=LooseCoupling
#### Enabled=true
#### Warning=true
#### DisplayName=Loose Coupling
#### HelpText
  The use of implementation types (i.e., HashSet) as object references limits your ability to use alternate implementations in the future as requirements change. Whenever available, referencing objects by their interface types (i.e, Set) provides much more flexibility.

  Example(s):

  ``` java
  import java.util.ArrayList;
  import java.util.HashSet;

  public class Bar {
      // sub-optimal approach
      private ArrayList<SomeType> list = new ArrayList<>();

      public HashSet<SomeType> getFoo() {
          return new HashSet<SomeType>();
      }

      // preferred approach
      private List<SomeType> list = new ArrayList<>();

      public Set<SomeType> getFoo() {
          return new HashSet<SomeType>();
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Major


## PMD_LoI
### Default
#### OriginalId=LongInstantiation
#### Enabled=false
#### Warning=true
#### DisplayName=Long Instantiation
#### HelpText
  Calling new Long() causes memory allocation that can be avoided by the static Long.valueOf().
  It makes use of an internal cache that recycles earlier instances making it more memory efficient.
  Note that new Long() is deprecated since JDK 9 for that reason.

  Example(s):

  ```java
  public class Foo {
      private Long i = new Long(0); // change to Long i = Long.valueOf(0);
  }
  ```


#### Tags
- /tool/PMD
- /general/Performance Rules

#### Settings
- Priority=Minor


## PMD_MACBF
### Default
#### OriginalId=MethodArgumentCouldBeFinal
#### Enabled=false
#### Warning=true
#### DisplayName=Method Argument Could Be Final
#### HelpText
  A method argument that is never re-assigned within the method can be declared final.

  Example(s):

  ```java
  public void foo1 (String param) {       // do stuff with param never assigning it

  }

  public void foo2 (final String param) { // better, do stuff with param never assigning it

  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_MBIS
### Default
#### OriginalId=MissingBreakInSwitch
#### Enabled=true
#### Warning=true
#### DisplayName=Missing Break In Switch
#### HelpText
  Switch statements without break or return statements for each case option may indicate problematic behaviour. Empty cases are ignored as these indicate an intentional fall-through.

  Example(s):

  ``` java
  public void bar(int status) {
      switch(status) {
        case CANCELLED:
          doCancelled();
          // break; hm, should this be commented out?
        case NEW:
          doNew();
          // is this really a fall-through?
        case REMOVED:
          doRemoved();
          // what happens if you add another case after this one?
        case OTHER: // empty case - this is interpreted as an intentional fall-through
        case ERROR:
          doErrorHandling();
          break;
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_MCC
### Default
#### OriginalId=ModifiedCyclomaticComplexity
#### Enabled=false
#### Warning=true
#### DisplayName=Modified Cyclomatic Complexity
#### HelpText
  Complexity directly affects maintenance costs is determined by the number of decision points in a method
  plus one for the method entry.  The decision points include 'if', 'while', 'for', and 'case labels' calls.
  Generally, numbers ranging from 1-4 denote low complexity, 5-7 denote moderate complexity, 8-10 denote
  high complexity, and 11+ is very high complexity. Modified complexity treats switch statements as a single
  decision point.

  This rule is deprecated and will be removed with PMD 7.0.0. The rule is replaced
  by the rule [Cyclomatic Complexity](#PMD_CC).

  Example(s):

  ```java
  public class Foo {    // This has a Cyclomatic Complexity = 9
  1   public void example()  {
  2       if (a == b)  {
  3           if (a1 == b1) {
                  fiddle();
  4           } else if a2 == b2) {
                  fiddle();
              }  else {
                  fiddle();
              }
  5       } else if (c == d) {
  6           while (c == d) {
                  fiddle();
              }
  7        } else if (e == f) {
  8           for (int n = 0; n < h; n++) {
                  fiddle();
              }
          } else{
  9           switch (z) {
                  case 1:
                      fiddle();
                      break;
                  case 2:
                      fiddle();
                      break;
                  case 3:
                      fiddle();
                      break;
                  default:
                      fiddle();
                      break;
              }
          }
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_MDBASBNC
### Default
#### OriginalId=MDBAndSessionBeanNamingConvention
#### Enabled=true
#### Warning=true
#### DisplayName=MDBAnd Session Bean Naming Convention
#### HelpText
  The EJB Specification states that any MessageDrivenBean or SessionBean should be suffixed by ‘Bean’.

  Example(s):

  ``` java
  public class SomeBean implements SessionBean{}                  // proper name

  public class MissingTheProperSuffix implements SessionBean {}   // non-standard name
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Major


## PMD_MNC
### Default
#### OriginalId=MisplacedNullCheck
#### Enabled=true
#### Warning=true
#### DisplayName=Misplaced Null Check
#### HelpText
  The null check here is misplaced. If the variable is null a NullPointerException will be thrown. Either the check is useless (the variable will never be “null”) or it is incorrect.

  Example(s):

  ``` java
  public class Foo {
      void bar() {
          if (a.equals(baz) && a != null) {} // a could be null, misplaced null check

          if (a != null && a.equals(baz)) {} // correct null check
      }
  }
  ```

  ``` java
  public class Foo {
      void bar() {
          if (a.equals(baz) || a == null) {} // a could be null, misplaced null check

          if (a == null || a.equals(baz)) {} // correct null check
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_MO
### Default
#### OriginalId=MissingOverride
#### Enabled=true
#### Warning=true
#### DisplayName=Missing Override
#### HelpText
  Annotating overridden methods with <span class="citation" data-cites="Override">@Override</span> ensures at compile time that the method really overrides one, which helps refactoring and clarifies intent.

  Example(s):

  ``` java
  public class Foo implements Runnable {
                  // This method is overridden, and should have an @Override annotation
                  public void run() {

                  }
              }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Minor


## PMD_MRIA
### Default
#### OriginalId=MethodReturnsInternalArray
#### Enabled=true
#### Warning=true
#### DisplayName=Method Returns Internal Array
#### HelpText
  Exposing internal arrays to the caller violates object encapsulation since elements can be removed or replaced outside of the object that owns it. It is safer to return a copy of the array.

  Example(s):

  ``` java
  public class SecureSystem {
      UserData [] ud;
      public UserData [] getUserData() {
          // Don't return directly the internal array, return a copy
          return ud;
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules
- /collection/SEI CERT/OBJ05-J
- /collection/SEI CERT/OBJ08-J
- /collection/SEI CERT/OBJ13-J
- /collection/CWE/375
- /collection/CWE/607

#### Settings
- Priority=Major


## PMD_MSMINIC
### Default
#### OriginalId=MissingStaticMethodInNonInstantiatableClass
#### Enabled=true
#### Warning=true
#### DisplayName=Missing Static Method In Non Instantiatable Class
#### HelpText
  A class that has private constructors and does not have any static methods or fields cannot be used.

  When one of the private constructors is annotated with one of the annotations, then the class is not considered non-instantiatable anymore and no violation will be reported. See the property `annotations`.

  Example(s):

  ``` java
  // This class is unusable, since it cannot be
  // instantiated (private constructor),
  // and no static method can be called.

  public class Foo {
    private Foo() {}
    void foo() {}
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Minor


## PMD_MSVUID
### Default
#### OriginalId=MissingSerialVersionUID
#### Enabled=true
#### Warning=true
#### DisplayName=Missing Serial Version UID
#### HelpText
  Serializable classes should provide a serialVersionUID field. The serialVersionUID field is also needed for abstract base classes. Each individual class in the inheritance chain needs an own serialVersionUID field. See also [Should an abstract class have a serialVersionUID](https://stackoverflow.com/questions/893259/should-an-abstract-class-have-a-serialversionuid).

  Example(s):

  ``` java
  public class Foo implements java.io.Serializable {
      String name;
      // Define serialization id to avoid serialization related bugs
      // i.e., public static final long serialVersionUID = 4328743;
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Major


## PMD_MTOL
### Default
#### OriginalId=MoreThanOneLogger
#### Enabled=true
#### Warning=true
#### DisplayName=More Than One Logger
#### HelpText
  Normally only one logger is used in each class. This rule supports slf4j, log4j, Java Util Logging and log4j2 (since 6.19.0).

  Example(s):

  ``` java
  public class Foo {
      Logger log = Logger.getLogger(Foo.class.getName());
      // It is very rare to see two loggers on a class, normally
      // log information is multiplexed by levels
      Logger log2= Logger.getLogger(Foo.class.getName());
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Major


## PMD_MVN
### Default
#### OriginalId=MIsLeadingVariableName
#### Enabled=false
#### Warning=true
#### DisplayName=MIs Leading Variable Name
#### HelpText
  Detects when a non-field has a name starting with 'm_'.  This usually denotes a field and could be confusing.

  This rule is deprecated and will be removed with PMD 7.0.0. The rule is replaced
  by the more general rule
  [Local Variable Naming Conventions](#PMD_LVNC).

  Example(s):

  ```java
  public class Foo {
      private int m_foo; // OK
      public void bar(String m_baz) { // Bad
        int m_boz = 42; // Bad
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_MWSNAEC
### Default
#### OriginalId=MethodWithSameNameAsEnclosingClass
#### Enabled=true
#### Warning=true
#### DisplayName=Method With Same Name As Enclosing Class
#### HelpText
  Non-constructor methods should not have the same name as the enclosing class.

  Example(s):

  ``` java
  public class MyClass {

      public MyClass() {}         // this is OK because it is a constructor

      public void MyClass() {}    // this is bad because it is a method
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Minor


## PMD_MeNC
### Default
#### OriginalId=MethodNamingConventions
#### Enabled=false
#### Warning=true
#### DisplayName=Method Naming Conventions
#### HelpText
  Configurable naming conventions for method declarations. This rule reports
              method declarations which do not match the regex that applies to their
              specific kind (e.g. JUnit test or native method). Each regex can be
              configured through properties.

              By default this rule uses the standard Java naming convention (Camel case).

  Example(s):

  ```java
  public class Foo {
      public void fooStuff() {
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_NA
### Default
#### OriginalId=NullAssignment
#### Enabled=false
#### Warning=true
#### DisplayName=Null Assignment
#### HelpText
  Assigning a "null" to a variable (outside of its declaration) is usually bad form.  Sometimes, this type
  of assignment is an indication that the programmer doesn't completely understand what is going on in the code.

  NOTE: This sort of assignment may used in some cases to dereference objects and encourage garbage collection.

  Example(s):

  ```java
  public void bar() {
    Object x = null; // this is OK
    x = new Object();
       // big, complex piece of code here
    x = null; // this is not required
       // big, complex piece of code here
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Minor


## PMD_NCC
### Default
#### OriginalId=NcssConstructorCount
#### Enabled=false
#### Warning=true
#### DisplayName=Ncss Constructor Count
#### HelpText
  This rule uses the NCSS (Non-Commenting Source Statements) algorithm to determine the number of lines
  of code for a given constructor. NCSS ignores comments, and counts actual statements. Using this algorithm,
  lines of code that are split are counted as one.

  This rule is deprecated and will be removed with PMD 7.0.0. The rule is replaced
  by the rule [Ncss Count](#PMD_NCo).

  Example(s):

  ```java
  public class Foo extends Bar {
      public Foo() {
          super();





          //this constructor only has 1 NCSS lines
          super.foo();
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_NCLISS
### Default
#### OriginalId=NonCaseLabelInSwitchStatement
#### Enabled=true
#### Warning=true
#### DisplayName=Non Case Label In Switch Statement
#### HelpText
  A non-case label (e.g. a named break/continue label) was present in a switch statement. This legal, but confusing. It is easy to mix up the case labels and the non-case labels.

  Example(s):

  ``` java
  public class Foo {
    void bar(int a) {
     switch (a) {
       case 1:
         // do something
         break;
       mylabel: // this is legal, but confusing!
         break;
       default:
         break;
      }
    }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_NCo
### Default
#### OriginalId=NcssCount
#### Enabled=false
#### Warning=true
#### DisplayName=Ncss Count
#### HelpText
  This rule uses the NCSS (Non-Commenting Source Statements) metric to determine the number of lines
  of code in a class, method or constructor. NCSS ignores comments, blank lines, and only counts actual
  statements. For more details on the calculation, see the documentation of
  the [NCSS metric](pmd_java_metrics_index.html#non-commenting-source-statements-ncss).

  Example(s):

  ```java
  import java.util.Collections;       // +0
  import java.io.IOException;         // +0

  class Foo {                         // +1, total Ncss = 12

    public void bigMethod()           // +1
        throws IOException {
      int x = 0, y = 2;               // +1
      boolean a = false, b = true;    // +1

      if (a || b) {                   // +1
        try {                         // +1
          do {                        // +1
            x += 2;                   // +1
          } while (x < 12);

          System.exit(0);             // +1
        } catch (IOException ioe) {   // +1
          throw new PatheticFailException(ioe); // +1
        }
      } else {
        assert false;                 // +1
      }
    }
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_NMC
### Default
#### OriginalId=NcssMethodCount
#### Enabled=false
#### Warning=true
#### DisplayName=Ncss Method Count
#### HelpText
  This rule uses the NCSS (Non-Commenting Source Statements) algorithm to determine the number of lines
  of code for a given method. NCSS ignores comments, and counts actual statements. Using this algorithm,
  lines of code that are split are counted as one.

  This rule is deprecated and will be removed with PMD 7.0.0. The rule is replaced
  by the rule [Ncss Count](#PMD_NCo).

  Example(s):

  ```java
  public class Foo extends Bar {
      public int methd() {
          super.methd();






          //this method only has 1 NCSS lines
          return 1;
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_NP
### Default
#### OriginalId=NoPackage
#### Enabled=true
#### Warning=true
#### DisplayName=No Package
#### HelpText
  Detects when a class, interface, enum or annotation does not have a package definition.

  Example(s):

  ``` java
  // no package declaration
  public class ClassInDefaultPackage {
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_NPC
### Default
#### OriginalId=NPathComplexity
#### Enabled=false
#### Warning=true
#### DisplayName=NPath Complexity
#### HelpText
  The NPath complexity of a method is the number of acyclic execution paths through that method.
  While cyclomatic complexity counts the number of decision points in a method, NPath counts the number of
  full paths from the beginning to the end of the block of the method. That metric grows exponentially, as
  it multiplies the complexity of statements in the same block. For more details on the calculation, see the
  documentation of the [NPath metric](pmd_java_metrics_index.html#npath-complexity-npath).

  A threshold of 200 is generally considered the point where measures should be taken to reduce
  complexity and increase readability.

  Example(s):

  ```java
  public class Foo {
    public static void bar() { // Ncss = 252: reported!
      boolean a, b = true;
      try { // 2 * 2 + 2 = 6
        if (true) { // 2
          List buz = new ArrayList();
        }

        for(int i = 0; i < 19; i++) { // * 2
          List buz = new ArrayList();
        }
      } catch(Exception e) {
        if (true) { // 2
          e.printStackTrace();
        }
      }

      while (j++ < 20) { //  * 2
        List buz = new ArrayList();
      }

      switch(j) { // * 7
        case 1:
        case 2: break;
        case 3: j = 5; break;
        case 4: if (b && a) { bar(); } break;
        default: break;
      }

      do { // * 3
          List buz = new ArrayList();
      } while (a && j++ < 30);
    }
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_NSI
### Default
#### OriginalId=NonStaticInitializer
#### Enabled=true
#### Warning=true
#### DisplayName=Non Static Initializer
#### HelpText
  A non-static initializer block will be called any time a constructor is invoked (just prior to invoking the constructor). While this is a valid language construct, it is rarely used and is confusing.

  Example(s):

  ``` java
  public class MyClass {
    // this block gets run before any call to a constructor
    {
      System.out.println("I am about to construct myself");
    }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_NTC
### Default
#### OriginalId=NcssTypeCount
#### Enabled=false
#### Warning=true
#### DisplayName=Ncss Type Count
#### HelpText
  This rule uses the NCSS (Non-Commenting Source Statements) algorithm to determine the number of lines
  of code for a given type. NCSS ignores comments, and counts actual statements. Using this algorithm,
  lines of code that are split are counted as one.

  This rule is deprecated and will be removed with PMD 7.0.0. The rule is replaced
  by the rule [Ncss Count](#PMD_NCo).

  Example(s):

  ```java
  public class Foo extends Bar {
      public Foo() {
          //this class only has 6 NCSS lines
          super();





          super.foo();
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_NTSS
### Default
#### OriginalId=NonThreadSafeSingleton
#### Enabled=true
#### Warning=true
#### DisplayName=Non Thread Safe Singleton
#### HelpText
  Non-thread safe singletons can result in bad state changes. Eliminate static singletons if possible by instantiating the object directly. Static singletons are usually not needed as only a single instance exists anyway. Other possible fixes are to synchronize the entire method or to use an [initialize-on-demand holder class](https://en.wikipedia.org/wiki/Initialization-on-demand_holder_idiom).

  Refrain from using the double-checked locking pattern. The Java Memory Model doesn’t guarantee it to work unless the variable is declared as `volatile`, adding an uneeded performance penalty. [Reference](http://www.cs.umd.edu/~pugh/java/memoryModel/DoubleCheckedLocking.html)

  See Effective Java, item 48.

  Example(s):

  ``` java
  private static Foo foo = null;

  //multiple simultaneous callers may see partially initialized objects
  public static Foo getFoo() {
      if (foo==null) {
          foo = new Foo();
      }
      return foo;
  }
  ```


#### Tags
- /tool/PMD
- /general/Multithreading Rules

#### Settings
- Priority=Critical


## PMD_OBEAH
### Default
#### OriginalId=OverrideBothEqualsAndHashcode
#### Enabled=true
#### Warning=true
#### DisplayName=Override Both Equals And Hashcode
#### HelpText
  Override both public boolean Object.equals(Object other), and public int Object.hashCode(), or override neither. Even if you are inheriting a hashCode() from a parent class, consider implementing hashCode and explicitly delegating to your superclass.

  Example(s):

  ``` java
  public class Bar {        // poor, missing a hashcode() method
      public boolean equals(Object o) {
        // do some comparison
      }
  }

  public class Baz {        // poor, missing an equals() method
      public int hashCode() {
        // return some hash value
      }
  }

  public class Foo {        // perfect, both methods provided
      public boolean equals(Object other) {
        // do some comparison
      }
      public int hashCode() {
        // return some hash value
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_ODPL
### Default
#### OriginalId=OneDeclarationPerLine
#### Enabled=true
#### Warning=true
#### DisplayName=One Declaration Per Line
#### HelpText
  Java allows the use of several variables declaration of the same type on one line. However, it can lead to quite messy code. This rule looks for several declarations on the same line.

  Example(s):

  ``` java
  String name;            // separate declarations
  String lastname;

  String name, lastname;  // combined declaration, a violation

  String name,
         lastname;        // combined declaration on multiple lines, no violation by default.
                          // Set property strictMode to true to mark this as violation.
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Minor


## PMD_OOR
### Default
#### OriginalId=OnlyOneReturn
#### Enabled=false
#### Warning=true
#### DisplayName=Only One Return
#### HelpText
  A method should have only one exit point, and that should be the last statement in the method.

  Example(s):

  ```java
  public class OneReturnOnly1 {
    public String foo(int x) {
      if (x > 0) {
        return "hey";   // first exit
      }
      return "hi";    // second exit
    }
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_OTAC
### Default
#### OriginalId=OptimizableToArrayCall
#### Enabled=true
#### Warning=true
#### DisplayName=Optimizable To Array Call
#### HelpText
  Calls to a collection’s `toArray(E[])` method should specify a target array of zero size. This allows the JVM to optimize the memory allocation and copying as much as possible.

  Previous versions of this rule (pre PMD 6.0.0) suggested the opposite, but current JVM implementations perform always better, when they have full control over the target array. And allocation an array via reflection is nowadays as fast as the direct allocation.

  See also [Arrays of Wisdom of the Ancients](https://shipilev.net/blog/2016/arrays-wisdom-ancients/)

  Note: If you don’t need an array of the correct type, then the simple `toArray()` method without an array is faster, but returns only an array of type `Object[]`.

  Example(s):

  ``` java
  List<Foo> foos = getFoos();

  // much better; this one allows the jvm to allocate an array of the correct size and effectively skip
  // the zeroing, since each array element will be overridden anyways
  Foo[] fooArray = foos.toArray(new Foo[0]);

  // inefficient, the array needs to be zeroed out by the jvm before it is handed over to the toArray method
  Foo[] fooArray = foos.toArray(new Foo[foos.size()]);
  ```


#### Tags
- /tool/PMD
- /general/Performance Rules

#### Settings
- Priority=Major


## PMD_PC
### Default
#### OriginalId=PackageCase
#### Enabled=true
#### Warning=true
#### DisplayName=Package Case
#### HelpText
  Detects when a package definition contains uppercase characters.

  Example(s):

  ``` java
  package com.MyCompany;  // should be lowercase name

  public class SomeClass {
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_PCI
### Default
#### OriginalId=ProperCloneImplementation
#### Enabled=true
#### Warning=true
#### DisplayName=Proper Clone Implementation
#### HelpText
  Object clone() should be implemented with super.clone().

  Example(s):

  ``` java
  class Foo{
      public Object clone(){
          return new Foo(); // This is bad
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_PD
### Default
#### OriginalId=PrematureDeclaration
#### Enabled=false
#### Warning=true
#### DisplayName=Premature Declaration
#### HelpText
  Checks for variables that are defined before they might be used. A reference is deemed to be premature if it is created right before a block of code that doesn't use it that also has the ability to return or throw an exception.

  Example(s):

  ```java
  public int getLength(String[] strings) {

      int length = 0; // declared prematurely

      if (strings == null || strings.length == 0) return 0;

      for (String str : strings) {
          length += str.length();
      }

      return length;
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_PL
### Default
#### OriginalId=ProperLogger
#### Enabled=true
#### Warning=true
#### DisplayName=Proper Logger
#### HelpText
  A logger should normally be defined private static final and be associated with the correct class. `private final Log log;` is also allowed for rare cases where loggers need to be passed around, with the restriction that the logger needs to be passed into the constructor.

  Example(s):

  ``` java
  public class Foo {

      private static final Log LOG = LogFactory.getLog(Foo.class);    // proper way

      protected Log LOG = LogFactory.getLog(Testclass.class);         // wrong approach
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Minor


## PMD_PLFIC
### Default
#### OriginalId=PositionLiteralsFirstInComparisons
#### Enabled=false
#### Warning=true
#### DisplayName=Position Literals First In Comparisons
#### HelpText
  Position literals first in comparisons, if the second argument is null then NullPointerExceptions
  can be avoided, they will just return false.

  This rule is replaced by the more general rule {% rule "LiteralsFirstInComparisons" %}.

  Example(s):

  ```java
  class Foo {
    boolean bar(String x) {
      return x.equals("2"); // should be "2".equals(x)
    }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Critical


## PMD_PLFICIC
### Default
#### OriginalId=PositionLiteralsFirstInCaseInsensitiveComparisons
#### Enabled=false
#### Warning=true
#### DisplayName=Position Literals First In Case Insensitive Comparisons
#### HelpText
  Position literals first in comparisons, if the second argument is null then NullPointerExceptions
  can be avoided, they will just return false.

  This rule is replaced by the more general rule {% rule "LiteralsFirstInComparisons" %}.

  Example(s):

  ```java
  class Foo {
    boolean bar(String x) {
      return x.equalsIgnoreCase("2"); // should be "2".equalsIgnoreCase(x)
    }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Critical


## PMD_PST
### Default
#### OriginalId=PreserveStackTrace
#### Enabled=true
#### Warning=true
#### DisplayName=Preserve Stack Trace
#### HelpText
  Throwing a new exception from a catch block without passing the original exception into the new exception will cause the original stack trace to be lost making it difficult to debug effectively.

  Example(s):

  ``` java
  public class Foo {
      void good() {
          try{
              Integer.parseInt("a");
          } catch (Exception e) {
              throw new Exception(e); // first possibility to create exception chain
          }
          try {
              Integer.parseInt("a");
          } catch (Exception e) {
              throw (IllegalStateException)new IllegalStateException().initCause(e); // second possibility to create exception chain.
          }
      }
      void bad() {
          try{
              Integer.parseInt("a");
          } catch (Exception e) {
              throw new Exception(e.getMessage());
          }
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Major


## PMD_REARTN
### Default
#### OriginalId=ReturnEmptyArrayRatherThanNull
#### Enabled=true
#### Warning=true
#### DisplayName=Return Empty Array Rather Than Null
#### HelpText
  For any method that returns an array, it is a better to return an empty array rather than a null reference. This removes the need for null checking all results and avoids inadvertent NullPointerExceptions.

  Example(s):

  ``` java
  public class Example {
      // Not a good idea...
      public int[] badBehavior() {
          // ...
          return null;
      }

      // Good behavior
      public String[] bonnePratique() {
          //...
          return new String[0];
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Major


## PMD_REWI
### Default
#### OriginalId=ReplaceEnumerationWithIterator
#### Enabled=false
#### Warning=true
#### DisplayName=Replace Enumeration With Iterator
#### HelpText
  Consider replacing Enumeration usages with the newer java.util.Iterator

  Example(s):

  ```java
  public class Foo implements Enumeration {
      private int x = 42;
      public boolean hasMoreElements() {
          return true;
      }
      public Object nextElement() {
          return String.valueOf(i++);
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Minor


## PMD_RFFB
### Default
#### OriginalId=ReturnFromFinallyBlock
#### Enabled=true
#### Warning=true
#### DisplayName=Return From Finally Block
#### HelpText
  Avoid returning from a finally block, this can discard exceptions.

  Example(s):

  ``` java
  public class Bar {
      public String foo() {
          try {
              throw new Exception( "My Exception" );
          } catch (Exception e) {
              throw e;
          } finally {
              return "A. O. K."; // return not recommended here
          }
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_RFI
### Default
#### OriginalId=RedundantFieldInitializer
#### Enabled=true
#### Warning=true
#### DisplayName=Redundant Field Initializer
#### HelpText
  Java will initialize fields with known default values so any explicit initialization of those same defaults is redundant and results in a larger class file (approximately three additional bytecode instructions per field).

  Example(s):

  ``` java
  public class C {
      boolean b   = false;    // examples of redundant initializers
      byte by     = 0;
      short s     = 0;
      char c      = 0;
      int i       = 0;
      long l      = 0;

      float f     = .0f;    // all possible float literals
      doable d    = 0d;     // all possible double literals
      Object o    = null;

      MyClass mca[] = null;
      int i1 = 0, ia1[] = null;

      class Nested {
          boolean b = false;
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Performance Rules

#### Settings
- Priority=Minor


## PMD_RHWM
### Default
#### OriginalId=ReplaceHashtableWithMap
#### Enabled=false
#### Warning=true
#### DisplayName=Replace Hashtable With Map
#### HelpText
  Consider replacing Hashtable usage with the newer java.util.Map if thread safety is not required.

  Example(s):

  ```java
  public class Foo {
      void bar() {
          Hashtable h = new Hashtable();
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Minor


## PMD_RINC
### Default
#### OriginalId=RemoteInterfaceNamingConvention
#### Enabled=true
#### Warning=true
#### DisplayName=Remote Interface Naming Convention
#### HelpText
  Remote Interface of a Session EJB should not have a suffix.

  Example(s):

  ``` java
  /* Poor Session suffix */
  public interface BadSuffixSession extends javax.ejb.EJBObject {}

  /* Poor EJB suffix */
  public interface BadSuffixEJB extends javax.ejb.EJBObject {}

  /* Poor Bean suffix */
  public interface BadSuffixBean extends javax.ejb.EJBObject {}
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Major


## PMD_RSINC
### Default
#### OriginalId=RemoteSessionInterfaceNamingConvention
#### Enabled=true
#### Warning=true
#### DisplayName=Remote Session Interface Naming Convention
#### HelpText
  A Remote Home interface type of a Session EJB should be suffixed by ‘Home’.

  Example(s):

  ``` java
  public interface MyBeautifulHome extends javax.ejb.EJBHome {}       // proper name

  public interface MissingProperSuffix extends javax.ejb.EJBHome {}   // non-standard name
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Major


## PMD_RVWL
### Default
#### OriginalId=ReplaceVectorWithList
#### Enabled=false
#### Warning=true
#### DisplayName=Replace Vector With List
#### HelpText
  Consider replacing Vector usages with the newer java.util.ArrayList if expensive thread-safe operations are not required.

  Example(s):

  ```java
  public class Foo {
      void bar() {
          Vector v = new Vector();
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Minor


## PMD_SBA
### Default
#### OriginalId=SimplifyBooleanAssertion
#### Enabled=true
#### Warning=true
#### DisplayName=Simplify Boolean Assertion
#### HelpText
  Avoid negation in an assertTrue or assertFalse test.

  For example, rephrase:

      assertTrue(!expr);

  as:

      assertFalse(expr);

  Example(s):

  ``` java
  public class SimpleTest extends TestCase {
      public void testX() {
          assertTrue("not empty", !r.isEmpty());  // replace with assertFalse("not empty", r.isEmpty())
          assertFalse(!r.isEmpty());              // replace with assertTrue(r.isEmpty())
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_SBE
### Default
#### OriginalId=SimplifyBooleanExpressions
#### Enabled=true
#### Warning=true
#### DisplayName=Simplify Boolean Expressions
#### HelpText
  Avoid unnecessary comparisons in boolean expressions, they serve no purpose and impacts readability.

  Example(s):

  ``` java
  public class Bar {
    // can be simplified to
    // bar = isFoo();
    private boolean bar = (isFoo() == true);

    public isFoo() { return false;}
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_SBIWC
### Default
#### OriginalId=StringBufferInstantiationWithChar
#### Enabled=true
#### Warning=true
#### DisplayName=String Buffer Instantiation With Char
#### HelpText
  Individual character values provided as initialization arguments will be converted into integers. This can lead to internal buffer sizes that are larger than expected. Some examples:

      new StringBuffer()      //  16
      new StringBuffer(6)     //  6
      new StringBuffer("hello world")  // 11 + 16 = 27
      new StringBuffer('A')   //  chr(A) = 65
      new StringBuffer("A")   //  1 + 16 = 17

      new StringBuilder()     //  16
      new StringBuilder(6)    //  6
      new StringBuilder("hello world")  // 11 + 16 = 27
      new StringBuilder('C')   //  chr(C) = 67
      new StringBuilder("A")   //  1 + 16 = 17

  Example(s):

  ``` java
  // misleading instantiation, these buffers
  // are actually sized to 99 characters long
  StringBuffer  sb1 = new StringBuffer('c');
  StringBuilder sb2 = new StringBuilder('c');

  // in these forms, just single characters are allocated
  StringBuffer  sb3 = new StringBuffer("c");
  StringBuilder sb4 = new StringBuilder("c");
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_SBR
### Default
#### OriginalId=SimplifyBooleanReturns
#### Enabled=true
#### Warning=true
#### DisplayName=Simplify Boolean Returns
#### HelpText
  Avoid unnecessary if-then-else statements when returning a boolean. The result of the conditional test can be returned instead.

  Example(s):

  ``` java
  public boolean isBarEqualTo(int x) {
      if (bar == x) {      // this bit of code...
          return true;
      } else {
          return false;
      }
  }

  public boolean isBarEqualTo(int x) {
      return bar == x;    // can be replaced with this
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_SC
### Default
#### OriginalId=SimplifyConditional
#### Enabled=true
#### Warning=true
#### DisplayName=Simplify Conditional
#### HelpText
  No need to check for null before an instanceof; the instanceof keyword returns false when given a null argument.

  Example(s):

  ``` java
  class Foo {
    void bar(Object x) {
      if (x != null && x instanceof Bar) {
        // just drop the "x != null" check
      }
    }
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_SCC
### Default
#### OriginalId=StdCyclomaticComplexity
#### Enabled=false
#### Warning=true
#### DisplayName=Std Cyclomatic Complexity
#### HelpText
  Complexity directly affects maintenance costs is determined by the number of decision points in a method
  plus one for the method entry.  The decision points include 'if', 'while', 'for', and 'case labels' calls.
  Generally, numbers ranging from 1-4 denote low complexity, 5-7 denote moderate complexity, 8-10 denote
  high complexity, and 11+ is very high complexity.

  This rule is deprecated and will be removed with PMD 7.0.0. The rule is replaced
  by the rule [Cyclomatic Complexity](#PMD_CC).

  Example(s):

  ```java
  public class Foo {    // This has a Cyclomatic Complexity = 12
  1   public void example()  {
  2       if (a == b || (c == d && e == f))  { // Only one
  3           if (a1 == b1) {
                  fiddle();
  4           } else if a2 == b2) {
                  fiddle();
              }  else {
                  fiddle();
              }
  5       } else if (c == d) {
  6           while (c == d) {
                  fiddle();
              }
  7        } else if (e == f) {
  8           for (int n = 0; n < h; n++) {
                  fiddle();
              }
          } else{
              switch (z) {
  9               case 1:
                      fiddle();
                      break;
  10              case 2:
                      fiddle();
                      break;
  11              case 3:
                      fiddle();
                      break;
  12              default:
                      fiddle();
                      break;
              }
          }
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_SCFN
### Default
#### OriginalId=SuspiciousConstantFieldName
#### Enabled=true
#### Warning=true
#### DisplayName=Suspicious Constant Field Name
#### HelpText
  Field names using all uppercase characters - Sun’s Java naming conventions indicating constants - should be declared as final.

  This rule is deprecated and will be removed with PMD 7.0.0. The rule is replaced by the more general rule [Field Naming Conventions](#PMD_FNC).

  Example(s):

  ``` java
  public class Foo {
   // this is bad, since someone could accidentally
   // do PI = 2.71828; which is actually e
   // final double PI = 3.16; is ok
    double PI = 3.16;
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_SCN
### Default
#### OriginalId=ShortClassName
#### Enabled=true
#### Warning=true
#### DisplayName=Short Class Name
#### HelpText
  Short Classnames with fewer than e.g. five characters are not recommended.

  Example(s):

  ``` java
  public class Foo {
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_SCRNI
### Default
#### OriginalId=SingletonClassReturningNewInstance
#### Enabled=true
#### Warning=true
#### DisplayName=Singleton Class Returning New Instance
#### HelpText
  Some classes contain overloaded getInstance. The problem with overloaded getInstance methods is that the instance created using the overloaded method is not cached and so, for each call and new objects will be created for every invocation.

  Example(s):

  ``` java
  class Singleton {
      private static Singleton instance = null;
      public static Singleton getInstance() {
          synchronized(Singleton.class) {
              return new Singleton();
          }
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Major


## PMD_SD
### Default
#### OriginalId=SwitchDensity
#### Enabled=false
#### Warning=true
#### DisplayName=Switch Density
#### HelpText
  A high ratio of statements to labels in a switch statement implies that the switch statement
  is overloaded.  Consider moving the statements into new methods or creating subclasses based
  on the switch variable.

  Example(s):

  ```java
  public class Foo {
    public void bar(int x) {
      switch (x) {
        case 1: {
          // lots of statements
          break;
        } case 2: {
          // lots of statements
          break;
        }
      }
    }
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_SDFNL
### Default
#### OriginalId=SimpleDateFormatNeedsLocale
#### Enabled=true
#### Warning=true
#### DisplayName=Simple Date Format Needs Locale
#### HelpText
  Be sure to specify a Locale when creating SimpleDateFormat instances to ensure that locale-appropriate formatting is used.

  Example(s):

  ``` java
  public class Foo {
    // Should specify Locale.US (or whatever)
    private SimpleDateFormat sdf = new SimpleDateFormat("pattern");
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Minor


## PMD_SEJBFSBF
### Default
#### OriginalId=StaticEJBFieldShouldBeFinal
#### Enabled=true
#### Warning=true
#### DisplayName=Static EJBField Should Be Final
#### HelpText
  According to the J2EE specification, an EJB should not have any static fields with write access. However, static read-only fields are allowed. This ensures proper behavior especially when instances are distributed by the container on several JREs.

  Example(s):

  ``` java
  public class SomeEJB extends EJBObject implements EJBLocalHome {

      private static int CountA;          // poor, field can be edited

      private static final int CountB;    // preferred, read-only access
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_SEMN
### Default
#### OriginalId=SuspiciousEqualsMethodName
#### Enabled=true
#### Warning=true
#### DisplayName=Suspicious Equals Method Name
#### HelpText
  The method name and parameter number are suspiciously close to `Object.equals`, which can denote an intention to override it. However, the method does not override `Object.equals`, but overloads it instead. Overloading `Object.equals` method is confusing for other programmers, error-prone and hard to maintain, especially when using inheritance, because `@Override` annotations used in subclasses can provide a false sense of security. For more information on `Object.equals` method, see Effective Java, 3rd Edition, Item 10: Obey the general contract when overriding equals.

  Example(s):

  ``` java
  public class Foo {
     public int equals(Object o) {
       // oops, this probably was supposed to be boolean equals
     }
     public boolean equals(String s) {
       // oops, this probably was supposed to be equals(Object)
     }
     public boolean equals(Object o1, Object o2) {
       // oops, this probably was supposed to be equals(Object)
     }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_SF
### Default
#### OriginalId=SingularField
#### Enabled=true
#### Warning=true
#### DisplayName=Singular Field
#### HelpText
  Fields whose scopes are limited to just single methods do not rely on the containing object to provide them to other methods. They may be better implemented as local variables within those methods.

  Example(s):

  ``` java
  public class Foo {
      private int x;  // no reason to exist at the Foo instance level
      public void foo(int y) {
       x = y + 5;
       return x;
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Major


## PMD_SHMN
### Default
#### OriginalId=SuspiciousHashcodeMethodName
#### Enabled=true
#### Warning=true
#### DisplayName=Suspicious Hashcode Method Name
#### HelpText
  The method name and return type are suspiciously close to hashCode(), which may denote an intention to override the hashCode() method.

  Example(s):

  ``` java
  public class Foo {
      public int hashcode() { // oops, this probably was supposed to be 'hashCode'
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_SI
### Default
#### OriginalId=ShortInstantiation
#### Enabled=false
#### Warning=true
#### DisplayName=Short Instantiation
#### HelpText
  Calling new Short() causes memory allocation that can be avoided by the static Short.valueOf().
  It makes use of an internal cache that recycles earlier instances making it more memory efficient.
  Note that new Short() is deprecated since JDK 9 for that reason.

  Example(s):

  ```java
  public class Foo {
      private Short i = new Short(0); // change to Short i = Short.valueOf(0);
  }
  ```


#### Tags
- /tool/PMD
- /general/Performance Rules

#### Settings
- Priority=Minor


## PMD_SMN
### Default
#### OriginalId=ShortMethodName
#### Enabled=true
#### Warning=true
#### DisplayName=Short Method Name
#### HelpText
  Method names that are very short are not helpful to the reader.

  Example(s):

  ``` java
  public class ShortMethod {
      public void a( int i ) { // Violation
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_SMS
### Default
#### OriginalId=SingleMethodSingleton
#### Enabled=true
#### Warning=true
#### DisplayName=Single Method Singleton
#### HelpText
  Some classes contain overloaded getInstance. The problem with overloaded getInstance methods is that the instance created using the overloaded method is not cached and so, for each call and new objects will be created for every invocation.

  Example(s):

  ``` java
  public class Singleton {

      private static Singleton singleton = new Singleton( );

      private Singleton(){ }

      public static Singleton getInstance( ) {
          return singleton;
      }

      public static Singleton getInstance(Object obj){
          Singleton singleton = (Singleton) obj;
          return singleton;           //violation
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Major


## PMD_SOE
### Default
#### OriginalId=SuspiciousOctalEscape
#### Enabled=true
#### Warning=true
#### DisplayName=Suspicious Octal Escape
#### HelpText
  A suspicious octal escape sequence was found inside a String literal. The Java language specification (section 3.10.6) says an octal escape sequence inside a literal String shall consist of a backslash followed by:

      OctalDigit | OctalDigit OctalDigit | ZeroToThree OctalDigit OctalDigit

  Any octal escape sequence followed by non-octal digits can be confusing, e.g. “38” is interpreted as the octal escape sequence “3” followed by the literal character “8”.

  Example(s):

  ``` java
  public void foo() {
    // interpreted as octal 12, followed by character '8'
    System.out.println("suspicious: \128");
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Major


## PMD_SP
### Default
#### OriginalId=SystemPrintln
#### Enabled=true
#### Warning=true
#### DisplayName=System Println
#### HelpText
  References to System.(out|err).print are usually intended for debugging purposes and can remain in the codebase even in production code. By using a logger one can enable/disable this behaviour at will (and by priority) and avoid clogging the Standard out log.

  Example(s):

  ``` java
  class Foo{
      Logger log = Logger.getLogger(Foo.class.getName());
      public void testA () {
          System.out.println("Entering test");
          // Better use this
          log.fine("Entering test");
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Major


## PMD_SSSHD
### Default
#### OriginalId=SwitchStmtsShouldHaveDefault
#### Enabled=true
#### Warning=true
#### DisplayName=Switch Stmts Should Have Default
#### HelpText
  All switch statements should include a default option to catch any unspecified values.

  Example(s):

  ``` java
  public void bar() {
      int x = 2;
      switch (x) {
        case 1: int j = 6;
        case 2: int j = 8;
            // missing default: here
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Major


## PMD_SSW
### Default
#### OriginalId=SimplifyStartsWith
#### Enabled=false
#### Warning=true
#### DisplayName=Simplify Starts With
#### HelpText
  Note: this rule is deprecated for removal, as the optimization is insignificant.

  Calls to `string.startsWith("x")` with a string literal of length 1 can be rewritten using `string.charAt(0)`,
  at the expense of some readability. To prevent `IndexOutOfBoundsException` being thrown by the `charAt` method,
  ensure that the string is not empty by making an additional check first.

  Example(s):

  ```java
  public class Foo {

      boolean checkIt(String x) {
          return x.startsWith("a");   // suboptimal
      }

      boolean fasterCheckIt(String x) {
          return !x.isEmpty() && x.charAt(0) == 'a';  // faster approach
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Performance Rules

#### Settings
- Priority=Minor


## PMD_ST
### Default
#### OriginalId=SimplifiedTernary
#### Enabled=true
#### Warning=true
#### DisplayName=Simplified Ternary
#### HelpText
  Look for ternary operators with the form `condition ? literalBoolean : foo` or `condition ? foo : literalBoolean`.

  These expressions can be simplified respectively to `condition || foo` when the literalBoolean is true `!condition && foo` when the literalBoolean is false or `!condition || foo` when the literalBoolean is true `condition && foo` when the literalBoolean is false

  Example(s):

  ``` java
  public class Foo {
      public boolean test() {
          return condition ? true : something(); // can be as simple as return condition || something();
      }

      public void test2() {
          final boolean value = condition ? false : something(); // can be as simple as value = !condition && something();
      }

      public boolean test3() {
          return condition ? something() : true; // can be as simple as return !condition || something();
      }

      public void test4() {
          final boolean otherValue = condition ? something() : false; // can be as simple as condition && something();
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_STS
### Default
#### OriginalId=StringToString
#### Enabled=true
#### Warning=true
#### DisplayName=String To String
#### HelpText
  Avoid calling toString() on objects already known to be string instances; this is unnecessary.

  Example(s):

  ``` java
  private String baz() {
      String bar = "howdy";
      return bar.toString();
  }
  ```


#### Tags
- /tool/PMD
- /general/Performance Rules

#### Settings
- Priority=Minor


## PMD_SV
### Default
#### OriginalId=ShortVariable
#### Enabled=false
#### Warning=true
#### DisplayName=Short Variable
#### HelpText
  Fields, local variables, or parameter names that are very short are not helpful to the reader.

  Example(s):

  ```java
  public class Something {
      private int q = 15;                         // field - too short
      public static void main( String as[] ) {    // formal arg - too short
          int r = 20 + q;                         // local var - too short
          for (int i = 0; i < 10; i++) {          // not a violation (inside 'for' loop)
              r += q;
          }
          for (Integer i : numbers) {             // not a violation (inside 'for-each' loop)
              r += q;
          }
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_SiDTE
### Default
#### OriginalId=SignatureDeclareThrowsException
#### Enabled=true
#### Warning=true
#### DisplayName=Signature Declare Throws Exception
#### HelpText
  A method/constructor shouldn’t explicitly throw the generic java.lang.Exception, since it is unclear which exceptions that can be thrown from the methods. It might be difficult to document and understand such vague interfaces. Use either a class derived from RuntimeException or a checked exception.

  Example(s):

  ``` java
  public void foo() throws Exception {
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Major


## PMD_StI
### Default
#### OriginalId=StringInstantiation
#### Enabled=true
#### Warning=true
#### DisplayName=String Instantiation
#### HelpText
  Avoid instantiating String objects; this is usually unnecessary since they are immutable and can be safely shared.

  Example(s):

  ``` java
  private String bar = new String("bar"); // just do a String bar = "bar";
  ```


#### Tags
- /tool/PMD
- /general/Performance Rules

#### Settings
- Priority=Minor


## PMD_TCWTC
### Default
#### OriginalId=TestClassWithoutTestCases
#### Enabled=true
#### Warning=true
#### DisplayName=Test Class Without Test Cases
#### HelpText
  Test classes end with the suffix Test. Having a non-test class with that name is not a good practice, since most people will assume it is a test case. Test classes have test methods named testXXX.

  Example(s):

  ``` java
  //Consider changing the name of the class if it is not a test
  //Consider adding test methods if it is a test
  public class CarTest {
     public static void main(String[] args) {
      // do something
     }
     // code
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Minor


## PMD_TFBFASS
### Default
#### OriginalId=TooFewBranchesForASwitchStatement
#### Enabled=true
#### Warning=true
#### DisplayName=Too Few Branches For ASwitch Statement
#### HelpText
  Switch statements are intended to be used to support complex branching behaviour. Using a switch for only a few cases is ill-advised, since switches are not as easy to understand as if-then statements. In these cases use the if-then statement to increase code readability.

  Example(s):

  ``` java
  // With a minimumNumberCaseForASwitch of 3
  public class Foo {
      public void bar() {
          switch (condition) {
              case ONE:
                  instruction;
                  break;
              default:
                  break; // not enough for a 'switch' stmt, a simple 'if' stmt would have been more appropriate
          }
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Performance Rules

#### Settings
- Priority=Minor


## PMD_TMF
### Default
#### OriginalId=TooManyFields
#### Enabled=false
#### Warning=true
#### DisplayName=Too Many Fields
#### HelpText
  Classes that have too many fields can become unwieldy and could be redesigned to have fewer fields,
  possibly through grouping related fields in new objects.  For example, a class with individual
  city/state/zip fields could park them within a single Address field.

  Example(s):

  ```java
  public class Person {   // too many separate fields
     int birthYear;
     int birthMonth;
     int birthDate;
     float height;
     float weight;
  }

  public class Person {   // this is more manageable
     Date birthDate;
     BodyMeasurements measurements;
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_TMM
### Default
#### OriginalId=TooManyMethods
#### Enabled=false
#### Warning=true
#### DisplayName=Too Many Methods
#### HelpText
  A class with too many methods is probably a good suspect for refactoring, in order to reduce its
  complexity and find a way to have more fine grained objects.

#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_TMSI
### Default
#### OriginalId=TooManyStaticImports
#### Enabled=true
#### Warning=true
#### DisplayName=Too Many Static Imports
#### HelpText
  If you overuse the static import feature, it can make your program unreadable and unmaintainable, polluting its namespace with all the static members you import. Readers of your code (including you, a few months after you wrote it) will not know which class a static member comes from (Sun 1.5 Language Guide).

  Example(s):

  ``` java
  import static Lennon;
  import static Ringo;
  import static George;
  import static Paul;
  import static Yoko; // Too much !
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Major


## PMD_UA
### Default
#### OriginalId=UnusedAssignment
#### Enabled=true
#### Warning=true
#### DisplayName=Unused Assignment
#### HelpText
  Reports assignments to variables that are never used before the variable is overwritten, or goes out of scope. Unused assignments are those for which 1. The variable is never read after the assignment, or 2. The assigned value is always overwritten by other assignments before the next read of the variable.

              The rule doesn't consider assignments to fields except for those of `this` in a constructor,
              or static fields of the current class in static initializers.

              The rule may be suppressed with the standard `@SuppressWarnings("unused")` tag.

              The rule subsumes {% rule "UnusedLocalVariable" %}, and {% rule "UnusedFormalParameter" %}.
              Those violations are filtered
              out by default, in case you already have enabled those rules, but may be enabled with the property
              `reportUnusedVariables`. Variables whose name starts with `ignored` or `unused` are filtered out, as
              is standard practice for exceptions.

              Limitations:
              * The rule currently cannot know which method calls throw exceptions, or which exceptions they throw.
              In the body of a try block, every method or constructor call is assumed to throw.  This may cause false-negatives.
              The only other language construct that is assumed to throw is the `throw` statement, in particular,
              things like `assert` statements, or NullPointerExceptions on dereference are ignored.
              * The rule cannot resolve assignments across constructors, when they're called with the special
              `this(...)` syntax. This may cause false-negatives.

              Both of those limitations may be partly relaxed in PMD 7.

  Example(s):

  ``` java
  class A {
                  // this field initializer is redundant,
                  // it is always overwritten in the constructor
                  int f = 1;

                  A(int f) {
                      this.f = f;
                  }
              }
  ```

  ``` java
  class B {

      int method(int i, int j) {
          // this initializer is redundant,
          // it is overwritten in all branches of the `if`
          int k = 0;

          // Both the assignments to k are unused, because k is
          // not read after the if/else
          // This may hide a bug: the programmer probably wanted to return k
          if (i < j)
              k = i;
          else
              k = j;

          return j;
      }

  }
  ```

  ``` java
  class C {

      int method() {
          int i = 0;

          checkSomething(++i);
          checkSomething(++i);
          checkSomething(++i);
          checkSomething(++i);

          // That last increment is not reported unless
          // the property `checkUnusedPrefixIncrement` is
          // set to `true`
          // Technically it could be written (i+1), but it
          // is not very important
      }

  }
  ```

  ``` java
  class C {

      // variables that are truly unused (at most assigned to, but never accessed)
      // are only reported if property `reportUnusedVariables` is true

      void method(int param) { } // for example this method parameter

      // even then, you can suppress the violation with an annotation:

      void method(@SuppressWarning("unused") int param) { } // no violation, even if `reportUnusedVariables` is true

      // For catch parameters, or for resources which don't need to be used explicitly,
      // you can give a name that starts with "ignored" to ignore such warnings

      {
          try (Something ignored = Something.create()) {
              // even if ignored is unused, it won't be flagged
              // its purpose might be to side-effect in the create/close routines

          } catch (Exception e) { // this is unused and will cause a warning if `reportUnusedVariables` is true
              // you should choose a name that starts with "ignored"
              return;
          }
      }

  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Minor


## PMD_UAAL
### Default
#### OriginalId=UseArraysAsList
#### Enabled=true
#### Warning=true
#### DisplayName=Use Arrays As List
#### HelpText
  The java.util.Arrays class has a “asList” method that should be used when you want to create a new List from an array of objects. It is faster than executing a loop to copy all the elements of the array one by one.

  Note that the result of Arrays.asList() is backed by the specified array, changes in the returned list will result in the array to be modified. For that reason, it is not possible to add new elements to the returned list of Arrays.asList() (UnsupportedOperationException). You must use new ArrayList&lt;&gt;(Arrays.asList(…)) if that is inconvenient for you (e.g. because of concurrent access).

  Example(s):

  ``` java
  public class Test {
      public void foo(Integer[] ints) {
          // could just use Arrays.asList(ints)
          List<Integer> l= new ArrayList<>(100);
          for (int i=0; i< 100; i++) {
              l.add(ints[i]);
          }
          for (int i=0; i< 100; i++) {
              l.add(a[i].toString()); // won't trigger the rule
          }
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Performance Rules

#### Settings
- Priority=Major


## PMD_UAEIOAT
### Default
#### OriginalId=UseAssertEqualsInsteadOfAssertTrue
#### Enabled=true
#### Warning=true
#### DisplayName=Use Assert Equals Instead Of Assert True
#### HelpText
  This rule detects JUnit assertions in object equality. These assertions should be made by more specific methods, like assertEquals.

  Example(s):

  ``` java
  public class FooTest extends TestCase {
      void testCode() {
          Object a, b;
          assertTrue(a.equals(b));                    // bad usage
          assertEquals("a should equals b", a, b);    // good usage
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Major


## PMD_UALIOV
### Default
#### OriginalId=UseArrayListInsteadOfVector
#### Enabled=true
#### Warning=true
#### DisplayName=Use Array List Instead Of Vector
#### HelpText
  ArrayList is a much better Collection implementation than Vector if thread-safe operation is not required.

  Example(s):

  ``` java
  public class SimpleTest extends TestCase {
      public void testX() {
      Collection c1 = new Vector();
      Collection c2 = new ArrayList();    // achieves the same with much better performance
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Performance Rules

#### Settings
- Priority=Minor


## PMD_UANIOAT
### Default
#### OriginalId=UseAssertNullInsteadOfAssertTrue
#### Enabled=true
#### Warning=true
#### DisplayName=Use Assert Null Instead Of Assert True
#### HelpText
  This rule detects JUnit assertions in object references equality. These assertions should be made by more specific methods, like assertNull, assertNotNull.

  Example(s):

  ``` java
  public class FooTest extends TestCase {
      void testCode() {
          Object a = doSomething();
          assertTrue(a==null);    // bad usage
          assertNull(a);          // good usage
          assertTrue(a != null);  // bad usage
          assertNotNull(a);       // good usage
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Minor


## PMD_UASIOAT
### Default
#### OriginalId=UseAssertSameInsteadOfAssertTrue
#### Enabled=true
#### Warning=true
#### DisplayName=Use Assert Same Instead Of Assert True
#### HelpText
  This rule detects JUnit assertions in object references equality. These assertions should be made by more specific methods, like assertSame, assertNotSame.

  Example(s):

  ``` java
  public class FooTest extends TestCase {
      void testCode() {
          Object a, b;
          assertTrue(a == b); // bad usage
          assertSame(a, b);   // good usage
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Minor


## PMD_UATIOAE
### Default
#### OriginalId=UseAssertTrueInsteadOfAssertEquals
#### Enabled=true
#### Warning=true
#### DisplayName=Use Assert True Instead Of Assert Equals
#### HelpText
  When asserting a value is the same as a literal or Boxed boolean, use assertTrue/assertFalse, instead of assertEquals.

  Example(s):

  ``` java
  public class MyTestCase extends TestCase {
      public void testMyCase() {
          boolean myVar = true;
          // Ok
          assertTrue("myVar is true", myVar);
          // Bad
          assertEquals("myVar is true", true, myVar);
          // Bad
          assertEquals("myVar is false", false, myVar);
          // Bad
          assertEquals("myVar is true", Boolean.TRUE, myVar);
          // Bad
          assertEquals("myVar is false", Boolean.FALSE, myVar);
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Minor


## PMD_UAVE
### Default
#### OriginalId=UnnecessaryAnnotationValueElement
#### Enabled=true
#### Warning=true
#### DisplayName=Unnecessary Annotation Value Element
#### HelpText
  Avoid the use of value in annotations when it’s the only element.

  Example(s):

  ``` java
  @TestClassAnnotation(value = "TEST")
  public class Foo {

      @TestMemberAnnotation(value = "TEST")
      private String y;

      @TestMethodAnnotation(value = "TEST")
      public void bar() {
          int x = 42;
          return;
      }
  }

  // should be

  @TestClassAnnotation("TEST")
  public class Foo {

      @TestMemberAnnotation("TEST")
      private String y;

      @TestMethodAnnotation("TEST")
      public void bar() {
          int x = 42;
          return;
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_UBA
### Default
#### OriginalId=UnnecessaryBooleanAssertion
#### Enabled=true
#### Warning=true
#### DisplayName=Unnecessary Boolean Assertion
#### HelpText
  A JUnit test assertion with a boolean literal is unnecessary since it always will evaluate to the same thing. Consider using flow control (in case of assertTrue(false) or similar) or simply removing statements like assertTrue(true) and assertFalse(false). If you just want a test to halt after finding an error, use the fail() method and provide an indication message of why it did.

  Example(s):

  ``` java
  public class SimpleTest extends TestCase {
      public void testX() {
          assertTrue(true);       // serves no real purpose
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Minor


## PMD_UC
### Default
#### OriginalId=UnnecessaryConstructor
#### Enabled=true
#### Warning=true
#### DisplayName=Unnecessary Constructor
#### HelpText
  This rule detects when a constructor is not necessary; i.e., when there is only one constructor and the constructor is identical to the default constructor. The default constructor should has same access modifier as the declaring class. In an enum type, the default constructor is implicitly private.

  Example(s):

  ``` java
  public class Foo {
    public Foo() {}
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_UCC
### Default
#### OriginalId=UnnecessaryCaseChange
#### Enabled=true
#### Warning=true
#### DisplayName=Unnecessary Case Change
#### HelpText
  Using equalsIgnoreCase() is faster than using toUpperCase/toLowerCase().equals()

  Example(s):

  ``` java
  boolean answer1 = buz.toUpperCase().equals("baz");              // should be buz.equalsIgnoreCase("baz")

  boolean answer2 = buz.toUpperCase().equalsIgnoreCase("baz");    // another unnecessary toUpperCase()
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Minor


## PMD_UCEL
### Default
#### OriginalId=UseCorrectExceptionLogging
#### Enabled=true
#### Warning=true
#### DisplayName=Use Correct Exception Logging
#### HelpText
  To make sure the full stacktrace is printed out, use the logging statement with two arguments: a String and a Throwable.

  Example(s):

  ``` java
  public class Main {
      private static final Log _LOG = LogFactory.getLog( Main.class );
      void bar() {
          try {
          } catch( Exception e ) {
              _LOG.error( e ); //Wrong!
          } catch( OtherException oe ) {
              _LOG.error( oe.getMessage(), oe ); //Correct
          }
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Major


## PMD_UCHM
### Default
#### OriginalId=UseConcurrentHashMap
#### Enabled=false
#### Warning=true
#### DisplayName=Use Concurrent Hash Map
#### HelpText
  Since Java5 brought a new implementation of the Map designed for multi-threaded access, you can
  perform efficient map reads without blocking other threads.

  Example(s):

  ```java
  public class ConcurrentApp {
    public void getMyInstance() {
      Map map1 = new HashMap();           // fine for single-threaded access
      Map map2 = new ConcurrentHashMap(); // preferred for use with multiple threads

      // the following case will be ignored by this rule
      Map map3 = someModule.methodThatReturnMap(); // might be OK, if the returned map is already thread-safe
    }
  }
  ```


#### Tags
- /tool/PMD
- /general/Multithreading Rules

#### Settings
- Priority=Minor


## PMD_UCIE
### Default
#### OriginalId=UseCollectionIsEmpty
#### Enabled=true
#### Warning=true
#### DisplayName=Use Collection Is Empty
#### HelpText
  The isEmpty() method on java.util.Collection is provided to determine if a collection has any elements. Comparing the value of size() to 0 does not convey intent as well as the isEmpty() method.

  Example(s):

  ``` java
  public class Foo {
      void good() {
          List foo = getList();
          if (foo.isEmpty()) {
              // blah
          }
      }

      void bad() {
          List foo = getList();
          if (foo.size() == 0) {
              // blah
          }
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Major


## PMD_UCT
### Default
#### OriginalId=UnnecessaryConversionTemporary
#### Enabled=true
#### Warning=true
#### DisplayName=Unnecessary Conversion Temporary
#### HelpText
  Avoid the use temporary objects when converting primitives to Strings. Use the static conversion methods on the wrapper classes instead.

  Example(s):

  ``` java
  public String convert(int x) {
      String foo = new Integer(x).toString(); // this wastes an object

      return Integer.toString(x);             // preferred approach
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Minor


## PMD_UDO
### Default
#### OriginalId=UseDiamondOperator
#### Enabled=true
#### Warning=true
#### DisplayName=Use Diamond Operator
#### HelpText
  Use the diamond operator to let the type be inferred automatically. With the Diamond operator it is possible to avoid duplication of the type parameters. Instead, the compiler is now able to infer the parameter types for constructor calls, which makes the code also more readable.

  The diamond operator has been introduced with java 7. However, type inference has been improved further with java8, rendering more type parameters unnecessary. This is only possible with java8 and the resulting code won’t compile with java7. If you use java7, make sure to enable `java7Compatibility` for this rule to avoid false positives.

  Example(s):

  ``` java
  List<String> strings = new ArrayList<String>(); // unnecessary duplication of type parameters
  List<String> stringsWithDiamond = new ArrayList<>(); // using the diamond operator is more concise
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_UEC
### Default
#### OriginalId=UncommentedEmptyConstructor
#### Enabled=true
#### Warning=true
#### DisplayName=Uncommented Empty Constructor
#### HelpText
  Uncommented Empty Constructor finds instances where a constructor does not contain statements, but there is no comment. By explicitly commenting empty constructors it is easier to distinguish between intentional (commented) and unintentional empty constructors.

  Example(s):

  ``` java
  public Foo() {
    // This constructor is intentionally empty. Nothing special is needed here.
  }
  ```


#### Tags
- /tool/PMD
- /general/Documentation Rules

#### Settings
- Priority=Minor


## PMD_UEM
### Default
#### OriginalId=UncommentedEmptyMethodBody
#### Enabled=true
#### Warning=true
#### DisplayName=Uncommented Empty Method Body
#### HelpText
  Uncommented Empty Method Body finds instances where a method body does not contain statements, but there is no comment. By explicitly commenting empty method bodies it is easier to distinguish between intentional (commented) and unintentional empty methods.

  Example(s):

  ``` java
  public void doSomething() {
  }
  ```


#### Tags
- /tool/PMD
- /general/Documentation Rules

#### Settings
- Priority=Minor


## PMD_UETCS
### Default
#### OriginalId=UseEqualsToCompareStrings
#### Enabled=true
#### Warning=true
#### DisplayName=Use Equals To Compare Strings
#### HelpText
  Using ‘==’ or ‘!=’ to compare strings only works if intern version is used on both sides. Use the equals() method instead.

  Example(s):

  ``` java
  public boolean test(String s) {
      if (s == "one") return true;        // unreliable
      if ("two".equals(s)) return true;   // better
      return false;
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_UFP
### Default
#### OriginalId=UnusedFormalParameter
#### Enabled=false
#### Warning=true
#### DisplayName=Unused Formal Parameter
#### HelpText
  Reports parameters of methods and constructors that are not referenced them in the method body.
  Parameters whose name starts with `ignored` or `unused` are filtered out.

  Removing unused formal parameters from public methods could cause a ripple effect through the code base.
  Hence, by default, this rule only considers private methods. To include non-private methods, set the
  `checkAll` property to `true`.

  Example(s):

  ```java
  public class Foo {
      private void bar(String howdy) {
          // howdy is not used
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Minor


## PMD_UFQN
### Default
#### OriginalId=UnnecessaryFullyQualifiedName
#### Enabled=true
#### Warning=true
#### DisplayName=Unnecessary Fully Qualified Name
#### HelpText
  Import statements allow the use of non-fully qualified names. The use of a fully qualified name which is covered by an import statement is redundant. Consider using the non-fully qualified name.

  Example(s):

  ``` java
  import java.util.List;

  public class Foo {
      private java.util.List list1;   // Unnecessary FQN
      private List list2;             // More appropriate given import of 'java.util.List'
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_UIOC
### Default
#### OriginalId=UseIndexOfChar
#### Enabled=false
#### Warning=true
#### DisplayName=Use Index Of Char
#### HelpText
  Use String.indexOf(char) when checking for the index of a single character; it executes faster.

  Example(s):

  ```java
  String s = "hello world";
  // avoid this
  if (s.indexOf("d") {}
  // instead do this
  if (s.indexOf('d') {}
  ```


#### Tags
- /tool/PMD
- /general/Performance Rules

#### Settings
- Priority=Minor


## PMD_UIOSWACFI
### Default
#### OriginalId=UseIOStreamsWithApacheCommonsFileItem
#### Enabled=true
#### Warning=true
#### DisplayName=Use IOStreams With Apache Commons File Item
#### HelpText
  Problem: Use of [FileItem.get()](https://commons.apache.org/proper/commons-fileupload/apidocs/org/apache/commons/fileupload/FileItem.html#get--) and [FileItem.getString()](https://commons.apache.org/proper/commons-fileupload/apidocs/org/apache/commons/fileupload/FileItem.html#getString--) could exhaust memory since they load the entire file into memory.

  Solution: Use [FileItem.getInputStream()](https://commons.apache.org/proper/commons-fileupload/apidocs/org/apache/commons/fileupload/FileItem.html#getInputStream--) and buffering.

  Example(s):

  ``` java
  import org.apache.commons.fileupload.FileItem;

  public class FileStuff {
     private String bad(FileItem fileItem) {
          return fileItem.getString();
     }

     private InputStream good(FileItem fileItem) {
          return fileItem.getInputStream();
     }
  }
  ```


#### Tags
- /tool/PMD
- /general/Performance Rules

#### Settings
- Priority=Major


## PMD_UIS
### Default
#### OriginalId=UnconditionalIfStatement
#### Enabled=true
#### Warning=true
#### DisplayName=Unconditional If Statement
#### HelpText
  Do not use “if” statements whose conditionals are always true or always false.

  Example(s):

  ``` java
  public class Foo {
      public void close() {
          if (true) {        // fixed conditional, not recommended
              // ...
          }
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Major


## PMD_ULBR
### Default
#### OriginalId=UnnecessaryLocalBeforeReturn
#### Enabled=true
#### Warning=true
#### DisplayName=Unnecessary Local Before Return
#### HelpText
  Avoid the creation of unnecessary local variables

  Example(s):

  ``` java
  public class Foo {
     public int foo() {
       int x = doSomething();
       return x;  // instead, just 'return doSomething();'
     }
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_ULV
### Default
#### OriginalId=UnusedLocalVariable
#### Enabled=true
#### Warning=true
#### DisplayName=Unused Local Variable
#### HelpText
  Detects when a local variable is declared and/or assigned, but not used. Variables whose name starts with `ignored` or `unused` are filtered out.

  Example(s):

  ``` java
  public class Foo {
      public void doSomething() {
          int i = 5; // Unused
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Major


## PMD_ULWCC
### Default
#### OriginalId=UseLocaleWithCaseConversions
#### Enabled=true
#### Warning=true
#### DisplayName=Use Locale With Case Conversions
#### HelpText
  When doing `String::toLowerCase()/toUpperCase()` conversions, use an explicit locale argument to specify the case transformation rules.

              Using `String::toLowerCase()` without arguments implicitly uses `Locale::getDefault()`.
              The problem is that the default locale depends on the current JVM setup (and usually on the system in which it is running).
              Using the system default may be exactly what you want (e.g. if you are manipulating strings you got through standard input),
              but it may as well not be the case (e.g. if you are getting the string over the network or a file, and the encoding is well-defined
              and independent of the environment). In the latter case, using the default locale makes the case transformation brittle, as
              it may yield unexpected results on a machine whose locale has other case translation rules. For example, in Turkish, the
              uppercase form of `i` is `İ` (U+0130, not ASCII) and not `I` (U+0049) as in English.

              The rule is intended to *force* developers to think about locales when dealing with strings. By taking a conscious decision about
              the choice of locale at the time of writing, you reduce the risk of surprising behaviour down the line, and communicate your intent
              to future readers.

  Example(s):

  ``` java
  // violation - implicitly system-dependent conversion
  if (x.toLowerCase().equals("list")) {}

  // The above will not match "LIST" on a system with a Turkish locale.
  // It could be replaced with
  if (x.toLowerCase(Locale.US).equals("list")) { }
  // or simply
  if (x.equalsIgnoreCase("list")) { }

  // ok - system independent conversion
  String z = a.toLowerCase(Locale.ROOT);

  // ok - explicit system-dependent conversion
  String z2 = a.toLowerCase(Locale.getDefault());
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_UNAION
### Default
#### OriginalId=UseNotifyAllInsteadOfNotify
#### Enabled=true
#### Warning=true
#### DisplayName=Use Notify All Instead Of Notify
#### HelpText
  Thread.notify() awakens a thread monitoring the object. If more than one thread is monitoring, then only one is chosen. The thread chosen is arbitrary; thus its usually safer to call notifyAll() instead.

  Example(s):

  ``` java
  void bar() {
      x.notify();
      // If many threads are monitoring x, only one (and you won't know which) will be notified.
      // use instead:
      x.notifyAll();
    }
  ```


#### Tags
- /tool/PMD
- /general/Multithreading Rules

#### Settings
- Priority=Critical


## PMD_UNCIE
### Default
#### OriginalId=UnusedNullCheckInEquals
#### Enabled=true
#### Warning=true
#### DisplayName=Unused Null Check In Equals
#### HelpText
  After checking an object reference for null, you should invoke equals() on that object rather than passing it to another object’s equals() method.

  Example(s):

  ``` java
  public class Test {

      public String method1() { return "ok";}
      public String method2() { return null;}

      public void method(String a) {
          String b;
          // I don't know it method1() can be "null"
          // but I know "a" is not null..
          // I'd better write a.equals(method1())

          if (a!=null && method1().equals(a)) { // will trigger the rule
              //whatever
          }

          if (method1().equals(a) && a != null) { // won't trigger the rule
              //whatever
          }

          if (a!=null && method1().equals(b)) { // won't trigger the rule
              //whatever
          }

          if (a!=null && "LITERAL".equals(a)) { // won't trigger the rule
              //whatever
          }

          if (a!=null && !a.equals("go")) { // won't trigger the rule
              a=method2();
              if (method1().equals(a)) {
                  //whatever
              }
          }
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_UOFCAPI
### Default
#### OriginalId=UseObjectForClearerAPI
#### Enabled=false
#### Warning=true
#### DisplayName=Use Object For Clearer API
#### HelpText
  When you write a public method, you should be thinking in terms of an API. If your method is public, it means other class
  will use it, therefore, you want (or need) to offer a comprehensive and evolutive API. If you pass a lot of information
  as a simple series of Strings, you may think of using an Object to represent all those information. You'll get a simpler
  API (such as doWork(Workload workload), rather than a tedious series of Strings) and more importantly, if you need at some
  point to pass extra data, you'll be able to do so by simply modifying or extending Workload without any modification to
  your API.

  Example(s):

  ```java
  public class MyClass {
      public void connect(String username,
          String pssd,
          String databaseName,
          String databaseAdress)
          // Instead of those parameters object
          // would ensure a cleaner API and permit
          // to add extra data transparently (no code change):
          // void connect(UserData data);
      {

      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_UOM
### Default
#### OriginalId=UselessOverridingMethod
#### Enabled=true
#### Warning=true
#### DisplayName=Useless Overriding Method
#### HelpText
  The overriding method merely calls the same method defined in a superclass.

  Example(s):

  ``` java
  public void foo(String bar) {
      super.foo(bar);      // why bother overriding?
  }

  public String foo() {
      return super.foo();  // why bother overriding?
  }

  @Id
  public Long getId() {
      return super.getId();  // OK if 'ignoreAnnotations' is false, which is the default behavior
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_UOOI
### Default
#### OriginalId=UselessOperationOnImmutable
#### Enabled=true
#### Warning=true
#### DisplayName=Useless Operation On Immutable
#### HelpText
  An operation on an Immutable object (String, BigDecimal or BigInteger) won’t change the object itself since the result of the operation is a new object. Therefore, ignoring the operation result is an error.

  Example(s):

  ``` java
  import java.math.*;

  class Test {
      void method1() {
          BigDecimal bd=new BigDecimal(10);
          bd.add(new BigDecimal(5));      // this will trigger the rule
      }
      void method2() {
          BigDecimal bd=new BigDecimal(10);
          bd = bd.add(new BigDecimal(5)); // this won't trigger the rule
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Critical


## PMD_UPCL
### Default
#### OriginalId=UseProperClassLoader
#### Enabled=false
#### Warning=true
#### DisplayName=Use Proper Class Loader
#### HelpText
  In J2EE, the getClassLoader() method might not work as expected. Use
  Thread.currentThread().getContextClassLoader() instead.

  Example(s):

  ```java
  public class Foo {
      ClassLoader cl = Bar.class.getClassLoader();
  }
  ```


#### Tags
- /tool/PMD
- /general/Error Prone Rules

#### Settings
- Priority=Minor


## PMD_UPF
### Default
#### OriginalId=UnusedPrivateField
#### Enabled=true
#### Warning=true
#### DisplayName=Unused Private Field
#### HelpText
  Detects when a private field is declared and/or assigned a value, but not used.

  Example(s):

  ``` java
  public class Something {
      private static int FOO = 2; // Unused
      private int i = 5; // Unused
      private int j = 6;
      public int addOne() {
          return j++;
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Major


## PMD_UPM
### Default
#### OriginalId=UnusedPrivateMethod
#### Enabled=true
#### Warning=true
#### DisplayName=Unused Private Method
#### HelpText
  Unused Private Method detects when a private method is declared but is unused.

  Example(s):

  ``` java
  public class Something {
      private void foo() {} // unused
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Major


## PMD_UQT
### Default
#### OriginalId=UselessQualifiedThis
#### Enabled=true
#### Warning=true
#### DisplayName=Useless Qualified This
#### HelpText
  Reports qualified this usages in the same class.

  Example(s):

  ``` java
  public class Foo {
      final Foo otherFoo = Foo.this;  // use "this" directly

      public void doSomething() {
           final Foo anotherFoo = Foo.this;  // use "this" directly
      }

      private ActionListener returnListener() {
          return new ActionListener() {
              @Override
              public void actionPerformed(ActionEvent e) {
                  doSomethingWithQualifiedThis(Foo.this);  // This is fine
              }
          };
      }

      private class Foo3 {
          final Foo myFoo = Foo.this;  // This is fine
      }

      private class Foo2 {
          final Foo2 myFoo2 = Foo2.this;  // Use "this" direclty
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_UR
### Default
#### OriginalId=UnnecessaryReturn
#### Enabled=false
#### Warning=true
#### DisplayName=Unnecessary Return
#### HelpText
  Avoid the use of unnecessary return statements.

  Example(s):

  ```java
  public class Foo {
      public void bar() {
          int x = 42;
          return;
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_USAI
### Default
#### OriginalId=UseShortArrayInitializer
#### Enabled=true
#### Warning=true
#### DisplayName=Use Short Array Initializer
#### HelpText
  When declaring and initializing array fields or variables, it is not necessary to explicitly create a new array using `new`. Instead one can simply define the initial content of the array as a expression in curly braces.

  E.g. `int[] x = new int[] { 1, 2, 3 };` can be written as `int[] x = { 1, 2, 3 };`.

  Example(s):

  ``` java
  Foo[] x = new Foo[] { ... }; // Overly verbose
  Foo[] x = { ... }; //Equivalent to above line
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_USBFSA
### Default
#### OriginalId=UseStringBufferForStringAppends
#### Enabled=true
#### Warning=true
#### DisplayName=Use String Buffer For String Appends
#### HelpText
  The use of the ‘+=’ operator for appending strings causes the JVM to create and use an internal StringBuffer. If a non-trivial number of these concatenations are being used then the explicit use of a StringBuilder or threadsafe StringBuffer is recommended to avoid this.

  Example(s):

  ``` java
  public class Foo {
      void bar() {
          String a;
          a = "foo";
          a += " bar";
          // better would be:
          // StringBuilder a = new StringBuilder("foo");
          // a.append(" bar");
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Performance Rules

#### Settings
- Priority=Major


## PMD_USBL
### Default
#### OriginalId=UseStringBufferLength
#### Enabled=false
#### Warning=true
#### DisplayName=Use String Buffer Length
#### HelpText
  Use StringBuffer.length() to determine StringBuffer length rather than using StringBuffer.toString().equals("")
  or StringBuffer.toString().length() == ...

  Example(s):

  ```java
  StringBuffer sb = new StringBuffer();

  if (sb.toString().equals("")) {}        // inefficient

  if (sb.length() == 0) {}                // preferred
  ```


#### Tags
- /tool/PMD
- /general/Performance Rules

#### Settings
- Priority=Minor


## PMD_USDF
### Default
#### OriginalId=UnsynchronizedStaticDateFormatter
#### Enabled=true
#### Warning=true
#### DisplayName=Unsynchronized Static Date Formatter
#### HelpText
  SimpleDateFormat instances are not synchronized. Sun recommends using separate format instances for each thread. If multiple threads must access a static formatter, the formatter must be synchronized on block level.

  This rule has been deprecated in favor of the rule [Unsynchronized Static Formatter](#PMD_USF).

  Example(s):

  ``` java
  public class Foo {
      private static final SimpleDateFormat sdf = new SimpleDateFormat();
      void bar() {
          sdf.format(); // poor, no thread-safety
      }
      void foo() {
          synchronized (sdf) { // preferred
              sdf.format();
          }
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Multithreading Rules

#### Settings
- Priority=Critical


## PMD_USF
### Default
#### OriginalId=UnsynchronizedStaticFormatter
#### Enabled=true
#### Warning=true
#### DisplayName=Unsynchronized Static Formatter
#### HelpText
  Instances of `java.text.Format` are generally not synchronized. Sun recommends using separate format instances for each thread. If multiple threads must access a static formatter, the formatter must be synchronized on block level.

  Example(s):

  ``` java
  public class Foo {
      private static final SimpleDateFormat sdf = new SimpleDateFormat();
      void bar() {
          sdf.format(); // poor, no thread-safety
      }
      void foo() {
          synchronized (sdf) { // preferred
              sdf.format();
          }
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Multithreading Rules

#### Settings
- Priority=Minor


## PMD_USVO
### Default
#### OriginalId=UselessStringValueOf
#### Enabled=false
#### Warning=true
#### DisplayName=Useless String Value Of
#### HelpText
  No need to call String.valueOf to append to a string; just use the valueOf() argument directly.

  Example(s):

  ```java
  public String convert(int i) {
      String s;
      s = "a" + String.valueOf(i);    // not required
      s = "a" + i;                    // preferred approach
      return s;
  }
  ```


#### Tags
- /tool/PMD
- /general/Performance Rules

#### Settings
- Priority=Minor


## PMD_UTWR
### Default
#### OriginalId=UseTryWithResources
#### Enabled=true
#### Warning=true
#### DisplayName=Use Try With Resources
#### HelpText
  Java 7 introduced the try-with-resources statement. This statement ensures that each resource is closed at the end of the statement. It avoids the need of explicitly closing the resources in a finally block. Additionally exceptions are better handled: If an exception occurred both in the `try` block and `finally` block, then the exception from the try block was suppressed. With the `try`-with-resources statement, the exception thrown from the try-block is preserved.

  Example(s):

  ``` java
  public class TryWithResources {
      public void run() {
          InputStream in = null;
          try {
              in = openInputStream();
              int i = in.read();
          } catch (IOException e) {
              e.printStackTrace();
          } finally {
              try {
                  if (in != null) in.close();
              } catch (IOException ignored) {
                  // ignored
              }
          }

          // better use try-with-resources
          try (InputStream in2 = openInputStream()) {
              int i = in2.read();
          }
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Minor


## PMD_UUC
### Default
#### OriginalId=UseUtilityClass
#### Enabled=false
#### Warning=true
#### DisplayName=Use Utility Class
#### HelpText
  For classes that only have static methods, consider making them utility classes.
  Note that this doesn't apply to abstract classes, since their subclasses may
  well include non-static methods.  Also, if you want this class to be a utility class,
  remember to add a private constructor to prevent instantiation.
  (Note, that this use was known before PMD 5.1.0 as UseSingleton).

  Example(s):

  ```java
  public class MaybeAUtility {
    public static void foo() {}
    public static void bar() {}
  }
  ```


#### Tags
- /tool/PMD
- /general/Design Rules

#### Settings
- Priority=Minor


## PMD_UUINL
### Default
#### OriginalId=UseUnderscoresInNumericLiterals
#### Enabled=true
#### Warning=true
#### DisplayName=Use Underscores In Numeric Literals
#### HelpText
  Since Java 1.7, numeric literals can use underscores to separate digits. This rule enforces that numeric literals above a certain length use these underscores to increase readability.

              The rule only supports decimal (base 10) literals for now. The acceptable length under which literals
              are not required to have underscores is configurable via a property. Even under that length, underscores
              that are misplaced (not making groups of 3 digits) are reported.

  Example(s):

  ``` java
  public class Foo {
      private int num = 1000000; // should be 1_000_000
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_UV
### Default
#### OriginalId=UseVarargs
#### Enabled=true
#### Warning=true
#### DisplayName=Use Varargs
#### HelpText
  Java 5 introduced the varargs parameter declaration for methods and constructors. This syntactic sugar provides flexibility for users of these methods and constructors, allowing them to avoid having to deal with the creation of an array.

  Example(s):

  ``` java
  public class Foo {
      public void foo(String s, Object[] args) {
          // Do something here...
      }

      public void bar(String s, Object... args) {
          // Ahh, varargs tastes much better...
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Minor


## PMD_UWOC
### Default
#### OriginalId=UnnecessaryWrapperObjectCreation
#### Enabled=true
#### Warning=true
#### DisplayName=Unnecessary Wrapper Object Creation
#### HelpText
  Most wrapper classes provide static conversion methods that avoid the need to create intermediate objects just to create the primitive forms. Using these avoids the cost of creating objects that also need to be garbage-collected later.

  Example(s):

  ``` java
  public int convert(String s) {
      int i, i2;

      i = Integer.valueOf(s).intValue();  // this wastes an object
      i = Integer.parseInt(s);            // this is better

      i2 = Integer.valueOf(i).intValue(); // this wastes an object
      i2 = i;                             // this is better

      String s3 = Integer.valueOf(i2).toString(); // this wastes an object
      s3 = Integer.toString(i2);                  // this is better

      return i2;
  }
  ```


#### Tags
- /tool/PMD
- /general/Performance Rules

#### Settings
- Priority=Major


## PMD_UnC
### Default
#### OriginalId=UnnecessaryCast
#### Enabled=true
#### Warning=true
#### DisplayName=Unnecessary Cast
#### HelpText
  This rule detects when a cast is unnecessary while accessing collection elements. This rule is mostly useful for old java code before generics where introduced with java 1.5.

  Example(s):

  ``` java
  public class UnnecessaryCastSample {
      public void method() {
          List<String> stringList = Arrays.asList("a", "b");
          String element = (String) stringList.get(0); // this cast is unnecessary
          String element2 = stringList.get(0);
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_UnI
### Default
#### OriginalId=UnusedImports
#### Enabled=true
#### Warning=true
#### DisplayName=Unused Imports
#### HelpText
  Avoid unused import statements to prevent unwanted dependencies. This rule will also find unused on demand imports, i.e. import com.foo.\*.

  Example(s):

  ``` java
  import java.io.File;  // not referenced or required
  import java.util.*;   // not referenced or required

  public class Foo {}
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Minor


## PMD_UnM
### Default
#### OriginalId=UnnecessaryModifier
#### Enabled=true
#### Warning=true
#### DisplayName=Unnecessary Modifier
#### HelpText
  Fields in interfaces and annotations are automatically `public static final`, and methods are `public abstract`. Classes, interfaces or annotations nested in an interface or annotation are automatically `public static` (all nested interfaces and annotations are automatically static). Nested enums are automatically `static`. For historical reasons, modifiers which are implied by the context are accepted by the compiler, but are superfluous.

  Example(s):

  ``` java
  public @interface Annotation {
      public abstract void bar();     // both abstract and public are ignored by the compiler
      public static final int X = 0;  // public, static, and final all ignored
      public static class Bar {}      // public, static ignored
      public static interface Baz {}  // ditto
  }
  public interface Foo {
      public abstract void bar();     // both abstract and public are ignored by the compiler
      public static final int X = 0;  // public, static, and final all ignored
      public static class Bar {}      // public, static ignored
      public static interface Baz {}  // ditto
  }
  public class Bar {
      public static interface Baz {}  // static ignored
      public static enum FoorBar {    // static ignored
          FOO;
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_UsP
### Default
#### OriginalId=UselessParentheses
#### Enabled=false
#### Warning=true
#### DisplayName=Useless Parentheses
#### HelpText
  Useless parentheses should be removed.

  Example(s):

  ```java
  public class Foo {

      private int _bar1;
      private Integer _bar2;

      public void setBar(int n) {
          _bar1 = Integer.valueOf((n)); // here
          _bar2 = (n); // and here
      }
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_VNC
### Default
#### OriginalId=VariableNamingConventions
#### Enabled=false
#### Warning=true
#### DisplayName=Variable Naming Conventions
#### HelpText
  A variable naming conventions rule - customize this to your liking.  Currently, it
  checks for final variables that should be fully capitalized and non-final variables
  that should not include underscores.

  This rule is deprecated and will be removed with PMD 7.0.0. The rule is replaced
  by the more general rules [Field Naming Conventions](#PMD_FNC),
  [Formal Parameter Naming Conventions](#PMD_FPNC), and
  [Local Variable Naming Conventions](#PMD_LVNC).

  Example(s):

  ```java
  public class Foo {
      public static final int MY_NUM = 0;
      public String myTest = "";
      DataModule dmTest = new DataModule();
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_WLMUB
### Default
#### OriginalId=WhileLoopsMustUseBraces
#### Enabled=false
#### Warning=true
#### DisplayName=While Loops Must Use Braces
#### HelpText
  Avoid using 'while' statements without using braces to surround the code block. If the code
  formatting or indentation is lost then it becomes difficult to separate the code being
  controlled from the rest.

  This rule is deprecated and will be removed with PMD 7.0.0. The rule is replaced
  by the rule [Control Statement Braces](#PMD_CSB).

  Example(s):

  ```java
  while (true)    // not recommended
        x++;

  while (true) {  // preferred approach
        x++;
  }
  ```


#### Tags
- /tool/PMD
- /general/Code Style Rules

#### Settings
- Priority=Minor


## PMD_WLWLB
### Default
#### OriginalId=WhileLoopWithLiteralBoolean
#### Enabled=true
#### Warning=true
#### DisplayName=While Loop With Literal Boolean
#### HelpText
  `do {} while (true);` requires reading the end of the statement before it is apparent that it loops forever, whereas `while (true) {}` is easier to understand.

  `do {} while (false);` is redundant, and if an inner variable scope is required, a block `{}` is sufficient.

  `while (false) {}` will never execute the block and can be removed in its entirety.

  Example(s):

  ``` java
  public class Example {
    {
      while (true) { } // allowed
      while (false) { } // disallowed
      do { } while (true); // disallowed
      do { } while (false); // disallowed
    }
  }
  ```


#### Tags
- /tool/PMD
- /general/Best Practice Rules

#### Settings
- Priority=Minor
