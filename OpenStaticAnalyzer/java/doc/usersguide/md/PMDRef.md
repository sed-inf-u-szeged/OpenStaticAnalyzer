## Reference of PMD coding rule violations

OpenStaticAnalyzer incorporates the [PMD] tool for coding rule violation checking and imports its results. OpenStaticAnalyzer also associates the issued rule violations with source code elements (i.e. methods, classes, packages, and components), and calculates metrics for the source code elements, which represent the amount of violations of each ruleset, rule, and priority groups, respectively. In addition, OpenStaticAnalyzer uses an optimized PMD setting, where the poorly performing PMD rule checks are disabled, and all other rules are reprioritized by our software developer and QA experts. 

OpenStaticAnalyzer uses PMD "as is", without any guaranties that the results of PMD are correct. All statements of the PMD license apply here as well. All texts describing the rulesets and the individual rules are copied from its official home page with some minor grammatical fixes.

The list of rulesets and rules contained in each ruleset are the following:

- **Best Practice Rules:** Rules which enforce generally accepted best practices.

- **Code Style Rules:** Rules which enforce a specific coding style.

- **Design Rules:** Rules that help you discover design issues.

- **Documentation Rules:** Rules that are related to code documentation.

- **Error Prone Rules:** Rules to detect constructs that are either broken, extremely confusing or prone to runtime errors.

- **Multithreading Rules:** Rules that flag issues when dealing with multiple threads of execution.

- **Performance Rules:** Rules that flag suboptimal code.

- **Security Rules:** Rules that flag potential security flaws.

The following table contains the enabled rules and their priorities:

  Category              Name                                                  Abbreviation   Prio.    
  --------------------- ----------------------------------------------------- -------------- ---------
  Best Practice Rules   Abstract Class Without Abstract Method                PMD_ACWAM      Minor    
                        Accessor Method Generation                            PMD_AMG        Minor    
                        Array Is Stored Directly                              PMD_AISD       Major    
                        Avoid Message Digest Field                            PMD_AMDF       Major    
                        Avoid Print Stack Trace                               PMD_APST       Major    
                        Avoid Reassigning Catch Variables                     PMD_ARCV       Minor    
                        Avoid Reassigning Loop Variables                      PMD_ARLV       Minor    
                        Avoid Reassigning Parameters                          PMD_ARP        Minor    
                        Avoid String Buffer Field                             PMD_ASBF       Minor    
                        Avoid Using Hard Coded IP                             PMD_AUHCIP     Major    
                        Check Result Set                                      PMD_CRS        Critical 
                        Constants In Interface                                PMD_CII        Minor    
                        Default Label Not Last In Switch Stmt                 PMD_DLNLISS    Minor    
                        Double Brace Initialization                           PMD_DBI        Minor    
                        For Loop Can Be Foreach                               PMD_FLCBF      Minor    
                        For Loop Variable Count                               PMD_FLVC       Minor    
                        Guard Log Statement                                   PMD_GLS        Minor    
                        JUnit Assertions Should Include Message               PMD_JUASIM     Minor    
                        JUnit Test Contains Too Many Asserts                  PMD_JUTCTMA    Minor    
                        JUnit Tests Should Include Assert                     PMD_JUTSIA     Major    
                        Literals First In Comparisons                         PMD_LFIC       Critical 
                        Loose Coupling                                        PMD_LoC        Major    
                        Method Returns Internal Array                         PMD_MRIA       Major    
                        Missing Override                                      PMD_MO         Minor    
                        One Declaration Per Line                              PMD_ODPL       Minor    
                        Preserve Stack Trace                                  PMD_PST        Major    
                        Switch Stmts Should Have Default                      PMD_SSSHD      Major    
                        System Println                                        PMD_SP         Major    
                        Unused Assignment                                     PMD_UA         Minor    
                        Unused Imports                                        PMD_UnI        Minor    
                        Unused Local Variable                                 PMD_ULV        Major    
                        Unused Private Field                                  PMD_UPF        Major    
                        Unused Private Method                                 PMD_UPM        Major    
                        Use Assert Equals Instead Of Assert True              PMD_UAEIOAT    Major    
                        Use Assert Null Instead Of Assert True                PMD_UANIOAT    Minor    
                        Use Assert Same Instead Of Assert True                PMD_UASIOAT    Minor    
                        Use Assert True Instead Of Assert Equals              PMD_UATIOAE    Minor    
                        Use Collection Is Empty                               PMD_UCIE       Major    
                        Use Try With Resources                                PMD_UTWR       Minor    
                        Use Varargs                                           PMD_UV         Minor    
                        While Loop With Literal Boolean                       PMD_WLWLB      Minor    
  Code Style Rules      Avoid Dollar Signs                                    PMD_ADS        Minor    
                        Avoid Prefixing Method Parameters                     PMD_APMP       Minor    
                        Avoid Protected Field In Final Class                  PMD_APFIFC     Minor    
                        Avoid Protected Method In Final Class Not Extending   PMD_APMIFCNE   Minor    
                        Avoid Using Native Code                               PMD_AUNC       Major    
                        Boolean Get Method Name                               PMD_BGMN       Minor    
                        Control Statement Braces                              PMD_CSB        Minor    
                        Default Package                                       PMD_DP         Minor    
                        Dont Import Java Lang                                 PMD_DIJL       Minor    
                        Duplicate Imports                                     PMD_DI         Minor    
                        Empty Method In Abstract Class Should Be Abstract     PMD_EMIACSBA   Major    
                        Extends Object                                        PMD_EO         Minor    
                        Field Declarations Should Be At Start Of Class        PMD_FDSBASOC   Minor    
                        For Loop Should Be While Loop                         PMD_FLSBWL     Minor    
                        Generics Naming                                       PMD_GN         Minor    
                        Identical Catch Branches                              PMD_ICB        Minor    
                        Local Home Naming Convention                          PMD_LHNC       Major    
                        Local Interface Session Naming Convention             PMD_LISNC      Major    
                        MDBAnd Session Bean Naming Convention                 PMD_MDBASBNC   Major    
                        No Package                                            PMD_NP         Minor    
                        Package Case                                          PMD_PC         Minor    
                        Remote Interface Naming Convention                    PMD_RINC       Major    
                        Remote Session Interface Naming Convention            PMD_RSINC      Major    
                        Short Class Name                                      PMD_SCN        Minor    
                        Short Method Name                                     PMD_SMN        Minor    
                        Suspicious Constant Field Name                        PMD_SCFN       Minor    
                        Too Many Static Imports                               PMD_TMSI       Major    
                        Unnecessary Annotation Value Element                  PMD_UAVE       Minor    
                        Unnecessary Cast                                      PMD_UnC        Minor    
                        Unnecessary Constructor                               PMD_UC         Minor    
                        Unnecessary Fully Qualified Name                      PMD_UFQN       Minor    
                        Unnecessary Local Before Return                       PMD_ULBR       Minor    
                        Unnecessary Modifier                                  PMD_UnM        Minor    
                        Use Diamond Operator                                  PMD_UDO        Minor    
                        Use Short Array Initializer                           PMD_USAI       Minor    
                        Use Underscores In Numeric Literals                   PMD_UUINL      Minor    
                        Useless Qualified This                                PMD_UQT        Minor    
  Design Rules          Abstract Class Without Any Method                     PMD_AbCWAM     Minor    
                        Avoid Catching Generic Exception                      PMD_ACGE       Major    
                        Avoid Rethrowing Exception                            PMD_ARE        Minor    
                        Avoid Throwing New Instance Of Same Exception         PMD_ATNIOSE    Minor    
                        Avoid Throwing Null Pointer Exception                 PMD_ATNPE      Critical 
                        Avoid Throwing Raw Exception Types                    PMD_ATRET      Major    
                        Avoid Unchecked Exceptions In Signatures              PMD_AUEIS      Minor    
                        Class With Only Private Constructors Should Be Final  PMD_CWOPCSBF   Minor    
                        Collapsible If Statements                             PMD_CIS        Minor    
                        Data Class                                            PMD_DC         Minor    
                        Do Not Extend Java Lang Error                         PMD_DNEJLE     Critical 
                        Exception As Flow Control                             PMD_EAFC       Major    
                        Final Field Could Be Static                           PMD_FFCBS      Minor    
                        Immutable Field                                       PMD_IF         Minor    
                        Logic Inversion                                       PMD_LI         Minor    
                        Signature Declare Throws Exception                    PMD_SiDTE      Major    
                        Simplified Ternary                                    PMD_ST         Minor    
                        Simplify Boolean Assertion                            PMD_SBA        Minor    
                        Simplify Boolean Expressions                          PMD_SBE        Minor    
                        Simplify Boolean Returns                              PMD_SBR        Minor    
                        Simplify Conditional                                  PMD_SC         Minor    
                        Singular Field                                        PMD_SF         Major    
                        Useless Overriding Method                             PMD_UOM        Minor    
  Documentation Rules   Uncommented Empty Constructor                         PMD_UEC        Minor    
                        Uncommented Empty Method Body                         PMD_UEM        Minor    
  Error Prone Rules     Assignment In Operand                                 PMD_AIO        Minor    
                        Assignment To Non Final Static                        PMD_ATNFS      Critical 
                        Avoid Accessibility Alteration                        PMD_AAA        Major    
                        Avoid Branching Statement As Last In Loop             PMD_ABSALIL    Major    
                        Avoid Calling Finalize                                PMD_ACF        Major    
                        Avoid Catching NPE                                    PMD_ACNPE      Critical 
                        Avoid Catching Throwable                              PMD_ACT        Major    
                        Avoid Decimal Literals In Big Decimal Constructor     PMD_ADLIBDC    Critical 
                        Avoid Duplicate Literals                              PMD_ADL        Major    
                        Avoid Field Name Matching Method Name                 PMD_AFNMMN     Minor    
                        Avoid Field Name Matching Type Name                   PMD_AFNMTN     Minor    
                        Avoid Instanceof Checks In Catch Clause               PMD_AICICC     Major    
                        Avoid Losing Exception Information                    PMD_ALEI       Major    
                        Avoid Multiple Unary Operators                        PMD_AMUO       Major    
                        Avoid Using Octal Values                              PMD_AUOV       Critical 
                        Bad Comparison                                        PMD_BC         Critical 
                        Broken Null Check                                     PMD_BNC        Critical 
                        Check Skip Result                                     PMD_CSR        Critical 
                        Class Cast Exception With To Array                    PMD_CCEWTA     Critical 
                        Clone Method Must Be Public                           PMD_CMMBP      Minor    
                        Clone Method Must Implement Cloneable                 PMD_ClMMIC     Major    
                        Clone Method Return Type Must Match Class Name        PMD_CMRTMMCN   Minor    
                        Clone Throws Clone Not Supported Exception            PMD_CTCNSE     Major    
                        Close Resource                                        PMD_ClR        Critical 
                        Constructor Calls Overridable Method                  PMD_CCOM       Critical 
                        Detached Test Case                                    PMD_DTC        Minor    
                        Do Not Call Garbage Collection Explicitly             PMD_DNCGCE     Major    
                        Do Not Extend Java Lang Throwable                     PMD_DNEJLT     Critical 
                        Do Not Terminate VM                                   PMD_DNTVM      Critical 
                        Do Not Throw Exception In Finally                     PMD_DNTEIF     Critical 
                        Dont Import Sun                                       PMD_DIS        Major    
                        Dont Use Float Type For Loop Indices                  PMD_DUFTFLI    Critical 
                        Empty Catch Block                                     PMD_ECB        Critical 
                        Empty Finalizer                                       PMD_EF         Minor    
                        Empty Finally Block                                   PMD_EFB        Minor    
                        Empty If Stmt                                         PMD_EIS        Major    
                        Empty Statement Block                                 PMD_EmSB       Minor    
                        Empty Statement Not In Loop                           PMD_ESNIL      Minor    
                        Empty Switch Statements                               PMD_ESS        Major    
                        Empty Synchronized Block                              PMD_ESB        Major    
                        Empty Try Block                                       PMD_ETB        Major    
                        Empty While Stmt                                      PMD_EWS        Critical 
                        Equals Null                                           PMD_EN         Critical 
                        Finalize Does Not Call Super Finalize                 PMD_FDNCSF     Critical 
                        Finalize Only Calls Super Finalize                    PMD_FOCSF      Minor    
                        Finalize Overloaded                                   PMD_FO         Critical 
                        Finalize Should Be Protected                          PMD_FSBP       Critical 
                        Idempotent Operations                                 PMD_IO         Major    
                        Import From Same Package                              PMD_IFSP       Minor    
                        Instantiation To Get Class                            PMD_ITGC       Major    
                        Invalid Log Message Format                            PMD_ILMF       Minor    
                        JUnit Spelling                                        PMD_JUS        Critical 
                        JUnit Static Suite                                    PMD_JUSS       Critical 
                        Jumbled Incrementer                                   PMD_JI         Critical 
                        Logger Is Not Static Final                            PMD_LINSF      Minor    
                        Method With Same Name As Enclosing Class              PMD_MWSNAEC    Minor    
                        Misplaced Null Check                                  PMD_MNC        Critical 
                        Missing Break In Switch                               PMD_MBIS       Critical 
                        Missing Serial Version UID                            PMD_MSVUID     Major    
                        Missing Static Method In Non Instantiatable Class     PMD_MSMINIC    Minor    
                        More Than One Logger                                  PMD_MTOL       Major    
                        Non Case Label In Switch Statement                    PMD_NCLISS     Critical 
                        Non Static Initializer                                PMD_NSI        Critical 
                        Override Both Equals And Hashcode                     PMD_OBEAH      Critical 
                        Proper Clone Implementation                           PMD_PCI        Critical 
                        Proper Logger                                         PMD_PL         Minor    
                        Return Empty Array Rather Than Null                   PMD_REARTN     Major    
                        Return From Finally Block                             PMD_RFFB       Critical 
                        Simple Date Format Needs Locale                       PMD_SDFNL      Minor    
                        Single Method Singleton                               PMD_SMS        Major    
                        Singleton Class Returning New Instance                PMD_SCRNI      Major    
                        Static EJBField Should Be Final                       PMD_SEJBFSBF   Critical 
                        String Buffer Instantiation With Char                 PMD_SBIWC      Critical 
                        Suspicious Equals Method Name                         PMD_SEMN       Critical 
                        Suspicious Hashcode Method Name                       PMD_SHMN       Critical 
                        Suspicious Octal Escape                               PMD_SOE        Major    
                        Test Class Without Test Cases                         PMD_TCWTC      Minor    
                        Unconditional If Statement                            PMD_UIS        Major    
                        Unnecessary Boolean Assertion                         PMD_UBA        Minor    
                        Unnecessary Case Change                               PMD_UCC        Minor    
                        Unnecessary Conversion Temporary                      PMD_UCT        Minor    
                        Unused Null Check In Equals                           PMD_UNCIE      Critical 
                        Use Correct Exception Logging                         PMD_UCEL       Major    
                        Use Equals To Compare Strings                         PMD_UETCS      Critical 
                        Use Locale With Case Conversions                      PMD_ULWCC      Critical 
                        Useless Operation On Immutable                        PMD_UOOI       Critical 
  Multithreading Rules  Avoid Synchronized At Method Level                    PMD_ASAML      Minor    
                        Avoid Thread Group                                    PMD_ATG        Critical 
                        Dont Call Thread Run                                  PMD_DCTR       Critical 
                        Double Checked Locking                                PMD_DCL        Critical 
                        Non Thread Safe Singleton                             PMD_NTSS       Critical 
                        Unsynchronized Static Date Formatter                  PMD_USDF       Critical 
                        Unsynchronized Static Formatter                       PMD_USF        Minor    
                        Use Notify All Instead Of Notify                      PMD_UNAION     Critical 
  Performance Rules     Add Empty String                                      PMD_AES        Minor    
                        Avoid Array Loops                                     PMD_AAL        Major    
                        Avoid Calendar Date Creation                          PMD_ACDC       Minor    
                        Avoid File Stream                                     PMD_AFS        Critical 
                        Big Integer Instantiation                             PMD_BII        Minor    
                        Boolean Instantiation                                 PMD_BI         Minor    
                        Consecutive Appends Should Reuse                      PMD_CASR       Minor    
                        Consecutive Literal Appends                           PMD_CLA        Minor    
                        Inefficient String Buffering                          PMD_ISB        Minor    
                        Optimizable To Array Call                             PMD_OTAC       Major    
                        Redundant Field Initializer                           PMD_RFI        Minor    
                        String Instantiation                                  PMD_StI        Minor    
                        String To String                                      PMD_STS        Minor    
                        Too Few Branches For ASwitch Statement                PMD_TFBFASS    Minor    
                        Unnecessary Wrapper Object Creation                   PMD_UWOC       Major    
                        Use Array List Instead Of Vector                      PMD_UALIOV     Minor    
                        Use Arrays As List                                    PMD_UAAL       Major    
                        Use IOStreams With Apache Commons File Item           PMD_UIOSWACFI  Major    
                        Use String Buffer For String Appends                  PMD_USBFSA     Major    
  Security Rules        Hard Coded Crypto Key                                 PMD_HCCK       Critical 
                        Insecure Crypto Iv                                    PMD_ICI        Critical 

### Best Practice Rules

#### Abstract Class Without Abstract Method {#PMD_ACWAM}
The abstract class does not contain any abstract methods. An abstract class suggests
an incomplete implementation, which is to be completed by subclasses implementing the
abstract methods. If the class is intended to be used as a base class only (not to be instantiated
directly) a protected constructor can be provided prevent direct instantiation.

Example(s):

```java
public abstract class Foo {
  void int method1() { ... }
  void int method2() { ... }
  // consider using abstract methods or removing
  // the abstract modifier and adding protected constructors
}
```


#### Accessor Method Generation {#PMD_AMG}
When accessing private fields / methods from another class, the Java compiler will generate accessor methods
with package-private visibility. This adds overhead, and to the dex method count on Android. This situation can
be avoided by changing the visibility of the field / method from private to package-private.

Example(s):

```java
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


#### Array Is Stored Directly {#PMD_AISD}
Constructors and methods receiving arrays should clone objects and store the copy.
This prevents future changes from the user from affecting the original array.

Example(s):

```java
public class Foo {
    private String [] x;
        public void foo (String [] param) {
        // Don't do this, make a copy of the array at least
        this.x=param;
    }
}
```


#### Avoid Message Digest Field {#PMD_AMDF}
Declaring a MessageDigest instance as a field make this instance directly available to multiple threads.
            Such sharing of MessageDigest instances should be avoided if possible since it leads to wrong results
            if the access is not synchronized correctly.
            Just create a new instance and use it locally, where you need it.
            Creating a new instance is easier than synchronizing access to a shared instance.

Example(s):

```java
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


#### Avoid Print Stack Trace {#PMD_APST}
Avoid printStackTrace(); use a logger call instead.

Example(s):

```java
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


#### Avoid Reassigning Catch Variables {#PMD_ARCV}
Reassigning exception variables caught in a catch statement should be avoided because of:

1) If it is needed, multi catch can be easily added and code will still compile.

2) Following the principle of least surprise we want to make sure that a variable caught in a catch statement
is always the one thrown in a try block.

Example(s):

```java
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


#### Avoid Reassigning Loop Variables {#PMD_ARLV}
Reassigning loop variables can lead to hard-to-find bugs. Prevent or limit how these variables can be changed.

In foreach-loops, configured by the `foreachReassign` property:
- `deny`: Report any reassignment of the loop variable in the loop body. _This is the default._
- `allow`: Don't check the loop variable.
- `firstOnly`: Report any reassignments of the loop variable, except as the first statement in the loop body.
            _This is useful if some kind of normalization or clean-up of the value before using is permitted, but any other change of the variable is not._

In for-loops, configured by the `forReassign` property:
- `deny`: Report any reassignment of the control variable in the loop body. _This is the default._
- `allow`: Don't check the control variable.
- `skip`: Report any reassignments of the control variable, except conditional increments/decrements (`++`, `--`, `+=`, `-=`).
            _This prevents accidental reassignments or unconditional increments of the control variable._

Example(s):

```java
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


#### Avoid Reassigning Parameters {#PMD_ARP}
Reassigning values to incoming parameters is not recommended.  Use temporary local variables instead.

Example(s):

```java
public class Foo {
  private void foo(String bar) {
    bar = "something else";
  }
}
```


#### Avoid String Buffer Field {#PMD_ASBF}
StringBuffers/StringBuilders can grow considerably, and so may become a source of memory leaks
if held within objects with long lifetimes.

Example(s):

```java
public class Foo {
    private StringBuffer buffer;    // potential memory leak as an instance variable;
}
```


#### Avoid Using Hard Coded IP {#PMD_AUHCIP}
Application with hard-coded IP addresses can become impossible to deploy in some cases.
Externalizing IP adresses is preferable.

Example(s):

```java
public class Foo {
    private String ip = "127.0.0.1";     // not recommended
}
```


#### Check Result Set {#PMD_CRS}
Always check the return values of navigation methods (next, previous, first, last) of a ResultSet.
If the value return is 'false', it should be handled properly.

Example(s):

```java
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


#### Constants In Interface {#PMD_CII}
Avoid constants in interfaces. Interfaces should define types, constants are implementation details
better placed in classes or enums. See Effective Java, item 19.

Example(s):

```java
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


#### Default Label Not Last In Switch Stmt {#PMD_DLNLISS}
By convention, the default label should be the last label in a switch statement.

Example(s):

```java
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


#### Double Brace Initialization {#PMD_DBI}
Double brace initialisation is a pattern to initialise eg collections concisely. But it implicitly
            generates a new .class file, and the object holds a strong reference to the enclosing object. For those
            reasons, it is preferable to initialize the object normally, even though it's verbose.

            This rule counts any anonymous class which only has a single initializer as an instance of double-brace
            initialization. There is currently no way to find out whether a method called in the initializer is not
            accessible from outside the anonymous class, and those legit cases should be suppressed for the time being.

Example(s):

```java
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


#### For Loop Can Be Foreach {#PMD_FLCBF}
Reports loops that can be safely replaced with the foreach syntax. The rule considers loops over
lists, arrays and iterators. A loop is safe to replace if it only uses the index variable to
access an element of the list or array, only has one update statement, and loops through *every*
element of the list or array left to right.

Example(s):

```java
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


#### For Loop Variable Count {#PMD_FLVC}
Having a lot of control variables in a 'for' loop makes it harder to see what range of values
the loop iterates over. By default this rule allows a regular 'for' loop with only one variable.

Example(s):

```java
// this will be reported with the default setting of at most one control variable in a for loop
for (int i = 0, j = 0; i < 10; i++, j += 2) {
   foo();
```


#### Guard Log Statement {#PMD_GLS}
Whenever using a log level, one should check if the loglevel is actually enabled, or
otherwise skip the associate String creation and manipulation.

Example(s):

```java
// Add this for performance
    if (log.isDebugEnabled() { ...
        log.debug("log something" + " and " + "concat strings");
```


#### JUnit Assertions Should Include Message {#PMD_JUASIM}
JUnit assertions should include an informative message - i.e., use the three-argument version of
assertEquals(), not the two-argument version.

Example(s):

```java
public class Foo extends TestCase {
    public void testSomething() {
        assertEquals("foo", "bar");
        // Use the form:
        // assertEquals("Foo does not equals bar", "foo", "bar");
        // instead
    }
}
```


#### JUnit Test Contains Too Many Asserts {#PMD_JUTCTMA}
Unit tests should not contain too many asserts. Many asserts are indicative of a complex test, for which
it is harder to verify correctness.  Consider breaking the test scenario into multiple, shorter test scenarios.
Customize the maximum number of assertions used by this Rule to suit your needs.

This rule checks for JUnit4, JUnit5 and TestNG Tests, as well as methods starting with "test".

Example(s):

```java
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


#### JUnit Tests Should Include Assert {#PMD_JUTSIA}
JUnit tests should include at least one assertion.  This makes the tests more robust, and using assert
with messages provide the developer a clearer idea of what the test does.

Example(s):

```java
public class Foo extends TestCase {
   public void testSomething() {
      Bar b = findBar();
   // This is better than having a NullPointerException
   // assertNotNull("bar not found", b);
   b.work();
   }
}
```


#### Literals First In Comparisons {#PMD_LFIC}
Position literals first in all String comparisons, if the second argument is null then NullPointerExceptions
            can be avoided, they will just return false. Note that switching literal positions for compareTo and
            compareToIgnoreCase may change the result, see examples.

Example(s):

```java
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


#### Loose Coupling {#PMD_LoC}
The use of implementation types (i.e., HashSet) as object references limits your ability to use alternate
implementations in the future as requirements change. Whenever available, referencing objects
by their interface types (i.e, Set) provides much more flexibility.

Example(s):

```java
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


#### Method Returns Internal Array {#PMD_MRIA}
Exposing internal arrays to the caller violates object encapsulation since elements can be
removed or replaced outside of the object that owns it. It is safer to return a copy of the array.

Example(s):

```java
public class SecureSystem {
    UserData [] ud;
    public UserData [] getUserData() {
        // Don't return directly the internal array, return a copy
        return ud;
    }
}
```


#### Missing Override {#PMD_MO}
Annotating overridden methods with @Override ensures at compile time that
            the method really overrides one, which helps refactoring and clarifies intent.

Example(s):

```java
public class Foo implements Runnable {
                // This method is overridden, and should have an @Override annotation
                public void run() {

                }
            }
```


#### One Declaration Per Line {#PMD_ODPL}
Java allows the use of several variables declaration of the same type on one line. However, it
can lead to quite messy code. This rule looks for several declarations on the same line.

Example(s):

```java
String name;            // separate declarations
String lastname;

String name, lastname;  // combined declaration, a violation

String name,
       lastname;        // combined declaration on multiple lines, no violation by default.
                        // Set property strictMode to true to mark this as violation.
```


#### Preserve Stack Trace {#PMD_PST}
Throwing a new exception from a catch block without passing the original exception into the
new exception will cause the original stack trace to be lost making it difficult to debug
effectively.

Example(s):

```java
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


#### Switch Stmts Should Have Default {#PMD_SSSHD}
All switch statements should include a default option to catch any unspecified values.

Example(s):

```java
public void bar() {
    int x = 2;
    switch (x) {
      case 1: int j = 6;
      case 2: int j = 8;
          // missing default: here
    }
}
```


#### System Println {#PMD_SP}
References to System.(out|err).print are usually intended for debugging purposes and can remain in
the codebase even in production code. By using a logger one can enable/disable this behaviour at
will (and by priority) and avoid clogging the Standard out log.

Example(s):

```java
class Foo{
    Logger log = Logger.getLogger(Foo.class.getName());
    public void testA () {
        System.out.println("Entering test");
        // Better use this
        log.fine("Entering test");
    }
}
```


#### Unused Assignment {#PMD_UA}
Reports assignments to variables that are never used before the variable is overwritten,
            or goes out of scope. Unused assignments are those for which
            1. The variable is never read after the assignment, or
            2. The assigned value is always overwritten by other assignments before the next read of
            the variable.

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

```java
class A {
                // this field initializer is redundant,
                // it is always overwritten in the constructor
                int f = 1;

                A(int f) {
                    this.f = f;
                }
            }
```

```java
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

```java
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

```java
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


#### Unused Imports {#PMD_UnI}
Avoid unused import statements to prevent unwanted dependencies.
This rule will also find unused on demand imports, i.e. import com.foo.*.

Example(s):

```java
import java.io.File;  // not referenced or required
import java.util.*;   // not referenced or required

public class Foo {}
```


#### Unused Local Variable {#PMD_ULV}
Detects when a local variable is declared and/or assigned, but not used.
Variables whose name starts with `ignored` or `unused` are filtered out.

Example(s):

```java
public class Foo {
    public void doSomething() {
        int i = 5; // Unused
    }
}
```


#### Unused Private Field {#PMD_UPF}
Detects when a private field is declared and/or assigned a value, but not used.

Example(s):

```java
public class Something {
    private static int FOO = 2; // Unused
    private int i = 5; // Unused
    private int j = 6;
    public int addOne() {
        return j++;
    }
}
```


#### Unused Private Method {#PMD_UPM}
Unused Private Method detects when a private method is declared but is unused.

Example(s):

```java
public class Something {
    private void foo() {} // unused
}
```


#### Use Assert Equals Instead Of Assert True {#PMD_UAEIOAT}
This rule detects JUnit assertions in object equality. These assertions should be made by more specific methods, like assertEquals.

Example(s):

```java
public class FooTest extends TestCase {
    void testCode() {
        Object a, b;
        assertTrue(a.equals(b));                    // bad usage
        assertEquals("a should equals b", a, b);    // good usage
    }
}
```


#### Use Assert Null Instead Of Assert True {#PMD_UANIOAT}
This rule detects JUnit assertions in object references equality. These assertions should be made by
more specific methods, like assertNull, assertNotNull.

Example(s):

```java
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


#### Use Assert Same Instead Of Assert True {#PMD_UASIOAT}
This rule detects JUnit assertions in object references equality. These assertions should be made
by more specific methods, like assertSame, assertNotSame.

Example(s):

```java
public class FooTest extends TestCase {
    void testCode() {
        Object a, b;
        assertTrue(a == b); // bad usage
        assertSame(a, b);   // good usage
    }
}
```


#### Use Assert True Instead Of Assert Equals {#PMD_UATIOAE}
When asserting a value is the same as a literal or Boxed boolean, use assertTrue/assertFalse, instead of assertEquals.

Example(s):

```java
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


#### Use Collection Is Empty {#PMD_UCIE}
The isEmpty() method on java.util.Collection is provided to determine if a collection has any elements.
Comparing the value of size() to 0 does not convey intent as well as the isEmpty() method.

Example(s):

```java
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


#### Use Try With Resources {#PMD_UTWR}
Java 7 introduced the try-with-resources statement. This statement ensures that each resource is closed at the end
of the statement. It avoids the need of explicitly closing the resources in a finally block. Additionally exceptions
are better handled: If an exception occurred both in the `try` block and `finally` block, then the exception from
the try block was suppressed. With the `try`-with-resources statement, the exception thrown from the try-block is
preserved.

Example(s):

```java
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


#### Use Varargs {#PMD_UV}
Java 5 introduced the varargs parameter declaration for methods and constructors.  This syntactic
sugar provides flexibility for users of these methods and constructors, allowing them to avoid
having to deal with the creation of an array.

Example(s):

```java
public class Foo {
    public void foo(String s, Object[] args) {
        // Do something here...
    }

    public void bar(String s, Object... args) {
        // Ahh, varargs tastes much better...
    }
}
```


#### While Loop With Literal Boolean {#PMD_WLWLB}
`do {} while (true);` requires reading the end of the statement before it is
apparent that it loops forever, whereas `while (true) {}` is easier to understand.

`do {} while (false);` is redundant, and if an inner variable scope is required,
a block `{}` is sufficient.

`while (false) {}` will never execute the block and can be removed in its entirety.

Example(s):

```java
public class Example {
  {
    while (true) { } // allowed
    while (false) { } // disallowed
    do { } while (true); // disallowed
    do { } while (false); // disallowed
  }
}
```


### Code Style Rules

#### Avoid Dollar Signs {#PMD_ADS}
Avoid using dollar signs in variable/method/class/interface names.

Example(s):

```java
public class Fo$o {  // not a recommended name
}
```


#### Avoid Prefixing Method Parameters {#PMD_APMP}
Prefixing parameters by 'in' or 'out' pollutes the name of the parameters and reduces code readability.
To indicate whether or not a parameter will be modify in a method, its better to document method
behavior with Javadoc.

This rule is deprecated and will be removed with PMD 7.0.0. The rule is replaced
by the more general rule [Formal Parameter Naming Conventions](#PMD_FPNC).

Example(s):

```java
// Not really clear
public class Foo {
  public void bar(
      int inLeftOperand,
      Result outRightOperand) {
      outRightOperand.setValue(inLeftOperand * outRightOperand.getValue());
  }
}
```

```java
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


#### Avoid Protected Field In Final Class {#PMD_APFIFC}
Do not use protected fields in final classes since they cannot be subclassed.
Clarify your intent by using private or package access modifiers instead.

Example(s):

```java
public final class Bar {
  private int x;
  protected int y;  // bar cannot be subclassed, so is y really private or package visible?
  Bar() {}
}
```


#### Avoid Protected Method In Final Class Not Extending {#PMD_APMIFCNE}
Do not use protected methods in most final classes since they cannot be subclassed. This should
only be allowed in final classes that extend other classes with protected methods (whose
visibility cannot be reduced). Clarify your intent by using private or package access modifiers instead.

Example(s):

```java
public final class Foo {
  private int bar() {}
  protected int baz() {} // Foo cannot be subclassed, and doesn't extend anything, so is baz() really private or package visible?
}
```


#### Avoid Using Native Code {#PMD_AUNC}
Unnecessary reliance on Java Native Interface (JNI) calls directly reduces application portability
and increases the maintenance burden.

Example(s):

```java
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


#### Boolean Get Method Name {#PMD_BGMN}
Methods that return boolean results should be named as predicate statements to denote this.
I.e, 'isReady()', 'hasValues()', 'canCommit()', 'willFail()', etc.   Avoid the use of the 'get'
prefix for these methods.

Example(s):

```java
public boolean getFoo();            // bad
public boolean isFoo();             // ok
public boolean getFoo(boolean bar); // ok, unless checkParameterizedMethods=true
```


#### Control Statement Braces {#PMD_CSB}
Enforce a policy for braces on control statements. It is recommended to use braces on 'if ... else'
            statements and loop statements, even if they are optional. This usually makes the code clearer, and
            helps prepare the future when you need to add another statement. That said, this rule lets you control
            which statements are required to have braces via properties.

            From 6.2.0 on, this rule supersedes WhileLoopMustUseBraces, ForLoopMustUseBraces, IfStmtMustUseBraces,
            and IfElseStmtMustUseBraces.

Example(s):

```java
while (true)    // not recommended
  x++;

while (true) {  // preferred approach
  x++;
}
```


#### Default Package {#PMD_DP}
Use explicit scoping instead of accidental usage of default package private level.
The rule allows methods and fields annotated with Guava's @VisibleForTesting and JUnit 5's annotations.

#### Dont Import Java Lang {#PMD_DIJL}
Avoid importing anything from the package 'java.lang'.  These classes are automatically imported (JLS 7.5.3).

Example(s):

```java
import java.lang.String;    // this is unnecessary

public class Foo {}

// --- in another source code file...

import java.lang.*;         // this is bad

public class Foo {}
```


#### Duplicate Imports {#PMD_DI}
Duplicate or overlapping import statements should be avoided.

Example(s):

```java
import java.lang.String;
import java.lang.*;
public class Foo {}
```


#### Empty Method In Abstract Class Should Be Abstract {#PMD_EMIACSBA}
Empty or auto-generated methods in an abstract class should be tagged as abstract. This helps to remove their inapproprate
usage by developers who should be implementing their own versions in the concrete subclasses.

Example(s):

```java
public abstract class ShouldBeAbstract {
    public Object couldBeAbstract() {
        // Should be abstract method ?
        return null;
    }

    public void couldBeAbstract() {
    }
}
```


#### Extends Object {#PMD_EO}
No need to explicitly extend Object.

Example(s):

```java
public class Foo extends Object {     // not required
}
```


#### Field Declarations Should Be At Start Of Class {#PMD_FDSBASOC}
Fields should be declared at the top of the class, before any method declarations, constructors, initializers or inner classes.

Example(s):

```java
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


#### For Loop Should Be While Loop {#PMD_FLSBWL}
Some for loops can be simplified to while loops, this makes them more concise.

Example(s):

```java
public class Foo {
    void bar() {
        for (;true;) true; // No Init or Update part, may as well be: while (true)
    }
}
```


#### Generics Naming {#PMD_GN}
Names for references to generic values should be limited to a single uppercase letter.

Example(s):

```java
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


#### Identical Catch Branches {#PMD_ICB}
Identical `catch` branches use up vertical space and increase the complexity of code without
            adding functionality. It's better style to collapse identical branches into a single multi-catch
            branch.

Example(s):

```java
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


#### Local Home Naming Convention {#PMD_LHNC}
The Local Home interface of a Session EJB should be suffixed by 'LocalHome'.

Example(s):

```java
public interface MyBeautifulLocalHome extends javax.ejb.EJBLocalHome {} // proper name

public interface MissingProperSuffix extends javax.ejb.EJBLocalHome {}  // non-standard name
```


#### Local Interface Session Naming Convention {#PMD_LISNC}
The Local Interface of a Session EJB should be suffixed by 'Local'.

Example(s):

```java
public interface MyLocal extends javax.ejb.EJBLocalObject {}                // proper name

public interface MissingProperSuffix extends javax.ejb.EJBLocalObject {}    // non-standard name
```


#### MDBAnd Session Bean Naming Convention {#PMD_MDBASBNC}
The EJB Specification states that any MessageDrivenBean or SessionBean should be suffixed by 'Bean'.

Example(s):

```java
public class SomeBean implements SessionBean{}                  // proper name

public class MissingTheProperSuffix implements SessionBean {}   // non-standard name
```


#### No Package {#PMD_NP}
Detects when a class, interface, enum or annotation does not have a package definition.

Example(s):

```java
// no package declaration
public class ClassInDefaultPackage {
}
```


#### Package Case {#PMD_PC}
Detects when a package definition contains uppercase characters.

Example(s):

```java
package com.MyCompany;  // should be lowercase name

public class SomeClass {
}
```


#### Remote Interface Naming Convention {#PMD_RINC}
Remote Interface of a Session EJB should not have a suffix.

Example(s):

```java
/* Poor Session suffix */
public interface BadSuffixSession extends javax.ejb.EJBObject {}

/* Poor EJB suffix */
public interface BadSuffixEJB extends javax.ejb.EJBObject {}

/* Poor Bean suffix */
public interface BadSuffixBean extends javax.ejb.EJBObject {}
```


#### Remote Session Interface Naming Convention {#PMD_RSINC}
A Remote Home interface type of a Session EJB should be suffixed by 'Home'.

Example(s):

```java
public interface MyBeautifulHome extends javax.ejb.EJBHome {}       // proper name

public interface MissingProperSuffix extends javax.ejb.EJBHome {}   // non-standard name
```


#### Short Class Name {#PMD_SCN}
Short Classnames with fewer than e.g. five characters are not recommended.

Example(s):

```java
public class Foo {
}
```


#### Short Method Name {#PMD_SMN}
Method names that are very short are not helpful to the reader.

Example(s):

```java
public class ShortMethod {
    public void a( int i ) { // Violation
    }
}
```


#### Suspicious Constant Field Name {#PMD_SCFN}
Field names using all uppercase characters - Sun's Java naming conventions indicating constants - should
be declared as final.

This rule is deprecated and will be removed with PMD 7.0.0. The rule is replaced
by the more general rule [Field Naming Conventions](#PMD_FNC).

Example(s):

```java
public class Foo {
 // this is bad, since someone could accidentally
 // do PI = 2.71828; which is actually e
 // final double PI = 3.16; is ok
  double PI = 3.16;
}
```


#### Too Many Static Imports {#PMD_TMSI}
If you overuse the static import feature, it can make your program unreadable and
unmaintainable, polluting its namespace with all the static members you import.
Readers of your code (including you, a few months after you wrote it) will not know
which class a static member comes from (Sun 1.5 Language Guide).

Example(s):

```java
import static Lennon;
import static Ringo;
import static George;
import static Paul;
import static Yoko; // Too much !
```


#### Unnecessary Annotation Value Element {#PMD_UAVE}
Avoid the use of value in annotations when it's the only element.

Example(s):

```java
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


#### Unnecessary Cast {#PMD_UnC}
This rule detects when a cast is unnecessary while accessing collection elements. This rule is mostly useful
for old java code before generics where introduced with java 1.5.

Example(s):

```java
public class UnnecessaryCastSample {
    public void method() {
        List<String> stringList = Arrays.asList("a", "b");
        String element = (String) stringList.get(0); // this cast is unnecessary
        String element2 = stringList.get(0);
    }
}
```


#### Unnecessary Constructor {#PMD_UC}
This rule detects when a constructor is not necessary; i.e., when there is only one constructor and the
constructor is identical to the default constructor. The default constructor should has same access
modifier as the declaring class. In an enum type, the default constructor is implicitly private.

Example(s):

```java
public class Foo {
  public Foo() {}
}
```


#### Unnecessary Fully Qualified Name {#PMD_UFQN}
Import statements allow the use of non-fully qualified names.  The use of a fully qualified name
which is covered by an import statement is redundant.  Consider using the non-fully qualified name.

Example(s):

```java
import java.util.List;

public class Foo {
    private java.util.List list1;   // Unnecessary FQN
    private List list2;             // More appropriate given import of 'java.util.List'
}
```


#### Unnecessary Local Before Return {#PMD_ULBR}
Avoid the creation of unnecessary local variables

Example(s):

```java
public class Foo {
   public int foo() {
     int x = doSomething();
     return x;  // instead, just 'return doSomething();'
   }
}
```


#### Unnecessary Modifier {#PMD_UnM}
Fields in interfaces and annotations are automatically `public static final`, and methods are `public abstract`.
Classes, interfaces or annotations nested in an interface or annotation are automatically `public static`
(all nested interfaces and annotations are automatically static).
Nested enums are automatically `static`.
For historical reasons, modifiers which are implied by the context are accepted by the compiler, but are superfluous.

Example(s):

```java
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


#### Use Diamond Operator {#PMD_UDO}
Use the diamond operator to let the type be inferred automatically. With the Diamond operator it is possible
to avoid duplication of the type parameters.
Instead, the compiler is now able to infer the parameter types for constructor calls,
which makes the code also more readable.

The diamond operator has been introduced with java 7. However, type inference has been improved further
with java8, rendering more type parameters unnecessary. This is only possible with java8 and the resulting
code won't compile with java7. If you use java7, make sure to enable `java7Compatibility` for this rule to avoid
false positives.

Example(s):

```java
List<String> strings = new ArrayList<String>(); // unnecessary duplication of type parameters
List<String> stringsWithDiamond = new ArrayList<>(); // using the diamond operator is more concise
```


#### Use Short Array Initializer {#PMD_USAI}
When declaring and initializing array fields or variables, it is not necessary to explicitly create a new array
using `new`. Instead one can simply define the initial content of the array as a expression in curly braces.

E.g. `int[] x = new int[] { 1, 2, 3 };` can be written as `int[] x = { 1, 2, 3 };`.

Example(s):

```java
Foo[] x = new Foo[] { ... }; // Overly verbose
Foo[] x = { ... }; //Equivalent to above line
```


#### Use Underscores In Numeric Literals {#PMD_UUINL}
Since Java 1.7, numeric literals can use underscores to separate digits. This rule enforces that
            numeric literals above a certain length use these underscores to increase readability.

            The rule only supports decimal (base 10) literals for now. The acceptable length under which literals
            are not required to have underscores is configurable via a property. Even under that length, underscores
            that are misplaced (not making groups of 3 digits) are reported.

Example(s):

```java
public class Foo {
    private int num = 1000000; // should be 1_000_000
}
```


#### Useless Qualified This {#PMD_UQT}
Reports qualified this usages in the same class.

Example(s):

```java
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


### Design Rules

#### Abstract Class Without Any Method {#PMD_AbCWAM}
If an abstract class does not provides any methods, it may be acting as a simple data container
that is not meant to be instantiated. In this case, it is probably better to use a private or
protected constructor in order to prevent instantiation than make the class misleadingly abstract.

Example(s):

```java
public abstract class Example {
    String field;
    int otherField;
}
```


#### Avoid Catching Generic Exception {#PMD_ACGE}
Avoid catching generic exceptions such as NullPointerException, RuntimeException, Exception in try-catch block

Example(s):

```java
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


#### Avoid Rethrowing Exception {#PMD_ARE}
Catch blocks that merely rethrow a caught exception only add to code size and runtime complexity.

Example(s):

```java
public void bar() {
    try {
        // do something
    }  catch (SomeException se) {
       throw se;
    }
}
```


#### Avoid Throwing New Instance Of Same Exception {#PMD_ATNIOSE}
Catch blocks that merely rethrow a caught exception wrapped inside a new instance of the same type only add to
code size and runtime complexity.

Example(s):

```java
public void bar() {
    try {
        // do something
    } catch (SomeException se) {
        // harmless comment
        throw new SomeException(se);
    }
}
```


#### Avoid Throwing Null Pointer Exception {#PMD_ATNPE}
Avoid throwing NullPointerExceptions manually. These are confusing because most people will assume that the
virtual machine threw it.  To avoid a method being called with a null parameter, you may consider
using an IllegalArgumentException instead, making it clearly seen as a programmer-initiated exception.
However, there are better ways to handle this:

>*Effective Java, 3rd Edition, Item 72: Favor the use of standard exceptions*
>
>Arguably, every erroneous method invocation boils down to an illegal argument or state,
but other exceptions are standardly used for certain kinds of illegal arguments and states.
If a caller passes null in some parameter for which null values are prohibited, convention dictates that
NullPointerException be thrown rather than IllegalArgumentException.

To implement that, you are encouraged to use `java.util.Objects.requireNonNull()`
(introduced in Java 1.7). This method is designed primarily for doing parameter
validation in methods and constructors with multiple parameters.

Your parameter validation could thus look like the following:
```
public class Foo {
    private String exampleValue;

    void setExampleValue(String exampleValue) {
      // check, throw and assignment in a single standard call
      this.exampleValue = Objects.requireNonNull(exampleValue, "exampleValue must not be null!");
    }
  }
```

Example(s):

```java
public class Foo {
    void bar() {
        throw new NullPointerException();
    }
}
```


#### Avoid Throwing Raw Exception Types {#PMD_ATRET}
Avoid throwing certain exception types. Rather than throw a raw RuntimeException, Throwable,
Exception, or Error, use a subclassed exception or error instead.

Example(s):

```java
public class Foo {
    public void bar() throws Exception {
        throw new Exception();
    }
}
```


#### Avoid Unchecked Exceptions In Signatures {#PMD_AUEIS}
A method or constructor should not explicitly declare unchecked exceptions in its
`throws` clause. Java doesn't force the caller to handle an unchecked exception,
so it's unnecessary except for documentation. A better practice is to document the
exceptional cases with a `@throws` Javadoc tag, which allows being more descriptive.

Example(s):

```java
public void foo() throws RuntimeException {
}
```


#### Class With Only Private Constructors Should Be Final {#PMD_CWOPCSBF}
A class with only private constructors should be final, unless the private constructor
is invoked by a inner class.

Example(s):

```java
public class Foo {  //Should be final
    private Foo() { }
}
```


#### Collapsible If Statements {#PMD_CIS}
Sometimes two consecutive 'if' statements can be consolidated by separating their conditions with a boolean short-circuit operator.

Example(s):

```java
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


#### Data Class {#PMD_DC}
Data Classes are simple data holders, which reveal most of their state, and
without complex functionality. The lack of functionality may indicate that
their behaviour is defined elsewhere, which is a sign of poor data-behaviour
proximity. By directly exposing their internals, Data Classes break encapsulation,
and therefore reduce the system's maintainability and understandability. Moreover,
classes tend to strongly rely on their data representation, which makes for a brittle
design.

Refactoring a Data Class should focus on restoring a good data-behaviour proximity. In
most cases, that means moving the operations defined on the data back into the class.
In some other cases it may make sense to remove entirely the class and move the data
into the former client classes.

Example(s):

```java
public class DataClass {

  public int bar = 0;
  public int na = 0;
  private int bee = 0;

  public void setBee(int n) {
    bee = n;
  }
}
```


#### Do Not Extend Java Lang Error {#PMD_DNEJLE}
Errors are system exceptions. Do not extend them.

Example(s):

```java
public class Foo extends Error { }
```


#### Exception As Flow Control {#PMD_EAFC}
Using Exceptions as form of flow control is not recommended as they obscure true exceptions when debugging.
Either add the necessary validation or use an alternate control structure.

Example(s):

```java
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


#### Final Field Could Be Static {#PMD_FFCBS}
If a final field is assigned to a compile-time constant, it could be made static, thus saving overhead
in each object at runtime.

Example(s):

```java
public class Foo {
  public final int BAR = 42; // this could be static and save some space
}
```


#### Immutable Field {#PMD_IF}
Identifies private fields whose values never change once object initialization ends either in the declaration
of the field or by a constructor. This helps in converting existing classes to becoming immutable ones.
Note that this rule does not enforce referenced object to be immutable itself. A class can still be mutable, even
if all its member fields are declared final. This is referred to as shallow immutability. For more information on
mutability, see Effective Java, 3rd Edition, Item 17: Minimize mutability.

Example(s):

```java
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


#### Logic Inversion {#PMD_LI}
Use opposite operator instead of negating the whole expression with a logic complement operator.

Example(s):

```java
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


#### Signature Declare Throws Exception {#PMD_SiDTE}
A method/constructor shouldn't explicitly throw the generic java.lang.Exception, since it
is unclear which exceptions that can be thrown from the methods. It might be
difficult to document and understand such vague interfaces. Use either a class
derived from RuntimeException or a checked exception.

Example(s):

```java
public void foo() throws Exception {
}
```


#### Simplified Ternary {#PMD_ST}
Look for ternary operators with the form `condition ? literalBoolean : foo`
or `condition ? foo : literalBoolean`.

These expressions can be simplified respectively to
`condition || foo`  when the literalBoolean is true
`!condition && foo` when the literalBoolean is false
or
`!condition || foo` when the literalBoolean is true
`condition && foo`  when the literalBoolean is false

Example(s):

```java
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


#### Simplify Boolean Assertion {#PMD_SBA}
Avoid negation in an assertTrue or assertFalse test.

For example, rephrase:

    assertTrue(!expr);

as:

    assertFalse(expr);

Example(s):

```java
public class SimpleTest extends TestCase {
    public void testX() {
        assertTrue("not empty", !r.isEmpty());  // replace with assertFalse("not empty", r.isEmpty())
        assertFalse(!r.isEmpty());              // replace with assertTrue(r.isEmpty())
    }
}
```


#### Simplify Boolean Expressions {#PMD_SBE}
Avoid unnecessary comparisons in boolean expressions, they serve no purpose and impacts readability.

Example(s):

```java
public class Bar {
  // can be simplified to
  // bar = isFoo();
  private boolean bar = (isFoo() == true);

  public isFoo() { return false;}
}
```


#### Simplify Boolean Returns {#PMD_SBR}
Avoid unnecessary if-then-else statements when returning a boolean. The result of
the conditional test can be returned instead.

Example(s):

```java
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


#### Simplify Conditional {#PMD_SC}
No need to check for null before an instanceof; the instanceof keyword returns false when given a null argument.

Example(s):

```java
class Foo {
  void bar(Object x) {
    if (x != null && x instanceof Bar) {
      // just drop the "x != null" check
    }
  }
}
```


#### Singular Field {#PMD_SF}
Fields whose scopes are limited to just single methods do not rely on the containing
object to provide them to other methods. They may be better implemented as local variables
within those methods.

Example(s):

```java
public class Foo {
    private int x;  // no reason to exist at the Foo instance level
    public void foo(int y) {
     x = y + 5;
     return x;
    }
}
```


#### Useless Overriding Method {#PMD_UOM}
The overriding method merely calls the same method defined in a superclass.

Example(s):

```java
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


### Documentation Rules

#### Uncommented Empty Constructor {#PMD_UEC}
Uncommented Empty Constructor finds instances where a constructor does not
contain statements, but there is no comment. By explicitly commenting empty
constructors it is easier to distinguish between intentional (commented)
and unintentional empty constructors.

Example(s):

```java
public Foo() {
  // This constructor is intentionally empty. Nothing special is needed here.
}
```


#### Uncommented Empty Method Body {#PMD_UEM}
Uncommented Empty Method Body finds instances where a method body does not contain
statements, but there is no comment. By explicitly commenting empty method bodies
it is easier to distinguish between intentional (commented) and unintentional
empty methods.

Example(s):

```java
public void doSomething() {
}
```


### Error Prone Rules

#### Assignment In Operand {#PMD_AIO}
Avoid assignments in operands; this can make code more complicated and harder to read.

Example(s):

```java
public void bar() {
    int x = 2;
    if ((x = getX()) == 3) {
      System.out.println("3!");
    }
}
```


#### Assignment To Non Final Static {#PMD_ATNFS}
Identifies a possible unsafe usage of a static field.

Example(s):

```java
public class StaticField {
   static int x;
   public FinalFields(int y) {
    x = y; // unsafe
   }
}
```


#### Avoid Accessibility Alteration {#PMD_AAA}
Methods such as getDeclaredConstructors(), getDeclaredConstructor(Class[]) and setAccessible(),
as the interface PrivilegedAction, allow for the runtime alteration of variable, class, or
method visibility, even if they are private. This violates the principle of encapsulation.

Example(s):

```java
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


#### Avoid Branching Statement As Last In Loop {#PMD_ABSALIL}
Using a branching statement as the last part of a loop may be a bug, and/or is confusing.
Ensure that the usage is not a bug, or consider using another approach.

Example(s):

```java
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


#### Avoid Calling Finalize {#PMD_ACF}
The method Object.finalize() is called by the garbage collector on an object when garbage collection determines
that there are no more references to the object. It should not be invoked by application logic.

Note that Oracle has declared Object.finalize() as deprecated since JDK 9.

Example(s):

```java
void foo() {
    Bar b = new Bar();
    b.finalize();
}
```


#### Avoid Catching NPE {#PMD_ACNPE}
Code should never throw NullPointerExceptions under normal circumstances.  A catch block may hide the
original error, causing other, more subtle problems later on.

Example(s):

```java
public class Foo {
    void bar() {
        try {
            // do something
        } catch (NullPointerException npe) {
        }
    }
}
```


#### Avoid Catching Throwable {#PMD_ACT}
Catching Throwable errors is not recommended since its scope is very broad. It includes runtime issues such as
OutOfMemoryError that should be exposed and managed separately.

Example(s):

```java
public void bar() {
    try {
        // do something
    } catch (Throwable th) {  // should not catch Throwable
        th.printStackTrace();
    }
}
```


#### Avoid Decimal Literals In Big Decimal Constructor {#PMD_ADLIBDC}
One might assume that the result of "new BigDecimal(0.1)" is exactly equal to 0.1, but it is actually
equal to .1000000000000000055511151231257827021181583404541015625.
This is because 0.1 cannot be represented exactly as a double (or as a binary fraction of any finite
length). Thus, the long value that is being passed in to the constructor is not exactly equal to 0.1,
appearances notwithstanding.

The (String) constructor, on the other hand, is perfectly predictable: 'new BigDecimal("0.1")' is
exactly equal to 0.1, as one would expect.  Therefore, it is generally recommended that the
(String) constructor be used in preference to this one.

Example(s):

```java
BigDecimal bd = new BigDecimal(1.123);       // loss of precision, this would trigger the rule

BigDecimal bd = new BigDecimal("1.123");     // preferred approach

BigDecimal bd = new BigDecimal(12);          // preferred approach, ok for integer values
```


#### Avoid Duplicate Literals {#PMD_ADL}
Code containing duplicate String literals can usually be improved by declaring the String as a constant field.

Example(s):

```java
private void bar() {
     buz("Howdy");
     buz("Howdy");
     buz("Howdy");
     buz("Howdy");
}
private void buz(String x) {}
```


#### Avoid Field Name Matching Method Name {#PMD_AFNMMN}
It can be confusing to have a field name with the same name as a method. While this is permitted,
having information (field) and actions (method) is not clear naming. Developers versed in
Smalltalk often prefer this approach as the methods denote accessor methods.

Example(s):

```java
public class Foo {
    Object bar;
    // bar is data or an action or both?
    void bar() {
    }
}
```


#### Avoid Field Name Matching Type Name {#PMD_AFNMTN}
It is somewhat confusing to have a field name matching the declaring class name.
This probably means that type and/or field names should be chosen more carefully.

Example(s):

```java
public class Foo extends Bar {
    int foo;    // There is probably a better name that can be used
}
```


#### Avoid Instanceof Checks In Catch Clause {#PMD_AICICC}
Each caught exception type should be handled in its own catch clause.

Example(s):

```java
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


#### Avoid Losing Exception Information {#PMD_ALEI}
Statements in a catch block that invoke accessors on the exception without using the information
only add to code size.  Either remove the invocation, or use the return result.

Example(s):

```java
public void bar() {
    try {
        // do something
    } catch (SomeException se) {
        se.getMessage();
    }
}
```


#### Avoid Multiple Unary Operators {#PMD_AMUO}
The use of multiple unary operators may be problematic, and/or confusing.
Ensure that the intended usage is not a bug, or consider simplifying the expression.

Example(s):

```java
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


#### Avoid Using Octal Values {#PMD_AUOV}
Integer literals should not start with zero since this denotes that the rest of literal will be
interpreted as an octal value.

Example(s):

```java
int i = 012;    // set i with 10 not 12
int j = 010;    // set j with 8 not 10
k = i * j;      // set k with 80 not 120
```


#### Bad Comparison {#PMD_BC}
Avoid equality comparisons with Double.NaN. Due to the implicit lack of representation
precision when comparing floating point numbers these are likely to cause logic errors.

Example(s):

```java
boolean x = (y == Double.NaN);
```


#### Broken Null Check {#PMD_BNC}
The null check is broken since it will throw a NullPointerException itself.
It is likely that you used || instead of && or vice versa.

Example(s):

```java
public String bar(String string) {
  // should be &&
    if (string!=null || !string.equals(""))
        return string;
  // should be ||
    if (string==null && string.equals(""))
        return string;
}
```


#### Check Skip Result {#PMD_CSR}
The skip() method may skip a smaller number of bytes than requested. Check the returned value to find out if it was the case or not.

Example(s):

```java
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


#### Class Cast Exception With To Array {#PMD_CCEWTA}
When deriving an array of a specific class from your Collection, one should provide an array of
the same class as the parameter of the toArray() method. Doing otherwise you will will result
in a ClassCastException.

Example(s):

```java
Collection c = new ArrayList();
Integer obj = new Integer(1);
c.add(obj);

    // this would trigger the rule (and throw a ClassCastException if executed)
Integer[] a = (Integer [])c.toArray();

   // this is fine and will not trigger the rule
Integer[] b = (Integer [])c.toArray(new Integer[c.size()]);
```


#### Clone Method Must Be Public {#PMD_CMMBP}
The java Manual says "By convention, classes that implement this interface should override
Object.clone (which is protected) with a public method."

Example(s):

```java
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


#### Clone Method Must Implement Cloneable {#PMD_ClMMIC}
The method clone() should only be implemented if the class implements the Cloneable interface with the exception of
a final method that only throws CloneNotSupportedException.

The rule can also detect, if the class implements or extends a Cloneable class.

Example(s):

```java
public class MyClass {
 public Object clone() throws CloneNotSupportedException {
  return foo;
 }
}
```


#### Clone Method Return Type Must Match Class Name {#PMD_CMRTMMCN}
If a class implements cloneable the return type of the method clone() must be the class name. That way, the caller
of the clone method doesn't need to cast the returned clone to the correct type.

Note: This is only possible with Java 1.5 or higher.

Example(s):

```java
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


#### Clone Throws Clone Not Supported Exception {#PMD_CTCNSE}
The method clone() should throw a CloneNotSupportedException.

Example(s):

```java
public class MyClass implements Cloneable{
    public Object clone() { // will cause an error
         MyClass clone = (MyClass)super.clone();
         return clone;
    }
}
```


#### Close Resource {#PMD_ClR}
Ensure that resources (like `java.sql.Connection`, `java.sql.Statement`, and `java.sql.ResultSet` objects
and any subtype of `java.lang.AutoCloseable`) are always closed after use.
Failing to do so might result in resource leaks.

Note: It suffices to configure the super type, e.g. `java.lang.AutoClosable`, so that this rule automatically triggers
on any subtype (e.g. `java.io.FileInputStream`). Additionally specifying `java.sql.Connection` helps in detecting
the types, if the type resolution / auxclasspath is not correctly setup.

Note: Since PMD 6.16.0 the default value for the property `types` contains `java.lang.AutoCloseable` and detects
now cases where the standard `java.io.*Stream` classes are involved. In order to restore the old behaviour,
just remove "AutoCloseable" from the types.

Example(s):

```java
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


#### Constructor Calls Overridable Method {#PMD_CCOM}
Calling overridable methods during construction poses a risk of invoking methods on an incompletely
constructed object and can be difficult to debug.
It may leave the sub-class unable to construct its superclass or forced to replicate the construction
process completely within itself, losing the ability to call super().  If the default constructor
contains a call to an overridable method, the subclass may be completely uninstantiable.   Note that
this includes method calls throughout the control flow graph - i.e., if a constructor Foo() calls a
private method bar() that calls a public method buz(), this denotes a problem.

Example(s):

```java
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


#### Detached Test Case {#PMD_DTC}
The method appears to be a test case since it has public or default visibility,
non-static access, no arguments, no return value, has no annotations, but is a
member of a class that has one or more JUnit test cases. If it is a utility
method, it should likely have private visibility. If it is an ignored test, it
should be annotated with @Test and @Ignore.

Example(s):

```java
public class MyTest {
    @Test
    public void someTest() {
    }

    // violation: Not annotated
    public void someOtherTest () {
    }

}
```


#### Do Not Call Garbage Collection Explicitly {#PMD_DNCGCE}
Calls to System.gc(), Runtime.getRuntime().gc(), and System.runFinalization() are not advised. Code should have the
same behavior whether the garbage collection is disabled using the option -Xdisableexplicitgc or not.
Moreover, "modern" jvms do a very good job handling garbage collections. If memory usage issues unrelated to memory
leaks develop within an application, it should be dealt with JVM options rather than within the code itself.

Example(s):

```java
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


#### Do Not Extend Java Lang Throwable {#PMD_DNEJLT}
Extend Exception or RuntimeException instead of Throwable.

Example(s):

```java
public class Foo extends Throwable { }
```


#### Do Not Terminate VM {#PMD_DNTVM}
Web applications should not call `System.exit()`, since only the web container or the
application server should stop the JVM. Otherwise a web application would terminate all other applications
running on the same application server.

This rule also checks for the equivalent calls `Runtime.getRuntime().exit()` and `Runtime.getRuntime().halt()`.

This rule was called *DoNotCallSystemExit* until PMD 6.29.0.

Example(s):

```java
public void bar() {
    System.exit(0);                 // never call this when running in an application server!
}
public void foo() {
    Runtime.getRuntime().exit(0);   // never stop the JVM manually, the container will do this.
}
```


#### Do Not Throw Exception In Finally {#PMD_DNTEIF}
Throwing exceptions within a 'finally' block is confusing since they may mask other exceptions
or code defects.
Note: This is a PMD implementation of the Lint4j rule "A throw in a finally block"

Example(s):

```java
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


#### Dont Import Sun {#PMD_DIS}
Avoid importing anything from the 'sun.*' packages.  These packages are not portable and are likely to change.

Example(s):

```java
import sun.misc.foo;
public class Foo {}
```


#### Dont Use Float Type For Loop Indices {#PMD_DUFTFLI}
Don't use floating point for loop indices. If you must use floating point, use double
unless you're certain that float provides enough precision and you have a compelling
performance need (space or time).

Example(s):

```java
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


#### Empty Catch Block {#PMD_ECB}
Empty Catch Block finds instances where an exception is caught, but nothing is done.
In most circumstances, this swallows an exception which should either be acted on
or reported.

Example(s):

```java
public void doSomething() {
    try {
        FileInputStream fis = new FileInputStream("/tmp/bugger");
    } catch (IOException ioe) {
        // not good
    }
}
```


#### Empty Finalizer {#PMD_EF}
Empty finalize methods serve no purpose and should be removed. Note that Oracle has declared Object.finalize() as deprecated since JDK 9.

Example(s):

```java
public class Foo {
   protected void finalize() {}
}
```


#### Empty Finally Block {#PMD_EFB}
Empty finally blocks serve no purpose and should be removed.

Example(s):

```java
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


#### Empty If Stmt {#PMD_EIS}
Empty If Statement finds instances where a condition is checked but nothing is done about it.

Example(s):

```java
public class Foo {
 void bar(int x) {
  if (x == 0) {
   // empty!
  }
 }
}
```


#### Empty Statement Block {#PMD_EmSB}
Empty block statements serve no purpose and should be removed.

Example(s):

```java
public class Foo {

   private int _bar;

   public void setBar(int bar) {
      { _bar = bar; } // Why not?
      {} // But remove this.
   }

}
```


#### Empty Statement Not In Loop {#PMD_ESNIL}
An empty statement (or a semicolon by itself) that is not used as the sole body of a 'for'
or 'while' loop is probably a bug.  It could also be a double semicolon, which has no purpose
and should be removed.

Example(s):

```java
public void doit() {
      // this is probably not what you meant to do
      ;
      // the extra semicolon here this is not necessary
      System.out.println("look at the extra semicolon");;
}
```


#### Empty Switch Statements {#PMD_ESS}
Empty switch statements serve no purpose and should be removed.

Example(s):

```java
public void bar() {
    int x = 2;
    switch (x) {
        // once there was code here
        // but it's been commented out or something
    }
}
```


#### Empty Synchronized Block {#PMD_ESB}
Empty synchronized blocks serve no purpose and should be removed.

Example(s):

```java
public class Foo {
    public void bar() {
        synchronized (this) {
            // empty!
        }
    }
}
```


#### Empty Try Block {#PMD_ETB}
Avoid empty try blocks - what's the point?

Example(s):

```java
public class Foo {
    public void bar() {
        try {
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
```


#### Empty While Stmt {#PMD_EWS}
Empty While Statement finds all instances where a while statement does nothing.
If it is a timing loop, then you should use Thread.sleep() for it; if it is
a while loop that does a lot in the exit expression, rewrite it to make it clearer.

Example(s):

```java
void bar(int a, int b) {
    while (a == b) {
        // empty!
    }
}
```


#### Equals Null {#PMD_EN}
Tests for null should not use the equals() method. The '==' operator should be used instead.

Example(s):

```java
String x = "foo";

if (x.equals(null)) {   // bad form
    doSomething();
}

if (x == null) {        // preferred
    doSomething();
}
```


#### Finalize Does Not Call Super Finalize {#PMD_FDNCSF}
If the finalize() is implemented, its last action should be to call super.finalize. Note that Oracle has declared Object.finalize() as deprecated since JDK 9.

Example(s):

```java
protected void finalize() {
    something();
    // neglected to call super.finalize()
}
```


#### Finalize Only Calls Super Finalize {#PMD_FOCSF}
If the finalize() is implemented, it should do something besides just calling super.finalize(). Note that Oracle has declared Object.finalize() as deprecated since JDK 9.

Example(s):

```java
protected void finalize() {
    super.finalize();
}
```


#### Finalize Overloaded {#PMD_FO}
Methods named finalize() should not have parameters.  It is confusing and most likely an attempt to
overload Object.finalize(). It will not be called by the VM.

Note that Oracle has declared Object.finalize() as deprecated since JDK 9.

Example(s):

```java
public class Foo {
    // this is confusing and probably a bug
    protected void finalize(int a) {
    }
}
```


#### Finalize Should Be Protected {#PMD_FSBP}
When overriding the finalize(), the new method should be set as protected.  If made public,
other classes may invoke it at inappropriate times.

Note that Oracle has declared Object.finalize() as deprecated since JDK 9.

Example(s):

```java
public void finalize() {
    // do something
}
```


#### Idempotent Operations {#PMD_IO}
Avoid idempotent operations - they have no effect.

Example(s):

```java
public class Foo {
 public void bar() {
  int x = 2;
  x = x;
 }
}
```


#### Import From Same Package {#PMD_IFSP}
There is no need to import a type that lives in the same package.

Example(s):

```java
package foo;

import foo.Buz;     // no need for this
import foo.*;       // or this

public class Bar{}
```


#### Instantiation To Get Class {#PMD_ITGC}
Avoid instantiating an object just to call getClass() on it; use the .class public member instead.

Example(s):

```java
// replace this
Class c = new String().getClass();

// with this:
Class c = String.class;
```


#### Invalid Log Message Format {#PMD_ILMF}
Check for messages in slf4j and log4j2 (since 6.19.0) loggers with non matching number of arguments and placeholders.

Since 6.32.0 in addition to parameterized message placeholders (`{}`) also format specifiers of string formatted
messages are supported (`%s`).

Example(s):

```java
LOGGER.error("forget the arg {}");
LOGGER.error("forget the arg %s");
LOGGER.error("too many args {}", "arg1", "arg2");
LOGGER.error("param {}", "arg1", new IllegalStateException("arg")); //The exception is shown separately, so is correct.
```


#### JUnit Spelling {#PMD_JUS}
In JUnit 3, the setUp method is used to set up all data entities required in running tests.
            The tearDown method is used to clean up all data entities required in running tests.
            You should not misspell method name if you want your test to set up and clean up everything correctly.

Example(s):

```java
import junit.framework.*;

public class Foo extends TestCase {
    public void setup() {}    // oops, should be setUp
    public void TearDown() {} // oops, should be tearDown
}
```


#### JUnit Static Suite {#PMD_JUSS}
The suite() method in a JUnit test needs to be both public and static.

Example(s):

```java
import junit.framework.*;

public class Foo extends TestCase {
    public void suite() {}         // oops, should be static
    private static void suite() {} // oops, should be public
}
```


#### Jumbled Incrementer {#PMD_JI}
Avoid jumbled loop incrementers - its usually a mistake, and is confusing even if intentional.

Example(s):

```java
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


#### Logger Is Not Static Final {#PMD_LINSF}
In most cases, the Logger reference can be declared as static and final.

This rule is deprecated and will be removed with PMD 7.0.0.
The rule is replaced by [Proper Logger](#PMD_PL).

Example(s):

```java
public class Foo{
    Logger log = Logger.getLogger(Foo.class.getName());                 // not recommended

    static final Logger log = Logger.getLogger(Foo.class.getName());    // preferred approach
}
```


#### Method With Same Name As Enclosing Class {#PMD_MWSNAEC}
Non-constructor methods should not have the same name as the enclosing class.

Example(s):

```java
public class MyClass {

    public MyClass() {}         // this is OK because it is a constructor

    public void MyClass() {}    // this is bad because it is a method
}
```


#### Misplaced Null Check {#PMD_MNC}
The null check here is misplaced. If the variable is null a NullPointerException will be thrown.
Either the check is useless (the variable will never be "null") or it is incorrect.

Example(s):

```java
public class Foo {
    void bar() {
        if (a.equals(baz) && a != null) {} // a could be null, misplaced null check

        if (a != null && a.equals(baz)) {} // correct null check
    }
}
```

```java
public class Foo {
    void bar() {
        if (a.equals(baz) || a == null) {} // a could be null, misplaced null check

        if (a == null || a.equals(baz)) {} // correct null check
    }
}
```


#### Missing Break In Switch {#PMD_MBIS}
Switch statements without break or return statements for each case option
may indicate problematic behaviour. Empty cases are ignored as these indicate an intentional fall-through.

Example(s):

```java
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


#### Missing Serial Version UID {#PMD_MSVUID}
Serializable classes should provide a serialVersionUID field.
The serialVersionUID field is also needed for abstract base classes. Each individual class in the inheritance
chain needs an own serialVersionUID field. See also [Should an abstract class have a serialVersionUID](https://stackoverflow.com/questions/893259/should-an-abstract-class-have-a-serialversionuid).

Example(s):

```java
public class Foo implements java.io.Serializable {
    String name;
    // Define serialization id to avoid serialization related bugs
    // i.e., public static final long serialVersionUID = 4328743;
}
```


#### Missing Static Method In Non Instantiatable Class {#PMD_MSMINIC}
A class that has private constructors and does not have any static methods or fields cannot be used.

When one of the private constructors is annotated with one of the annotations, then the class is not considered
non-instantiatable anymore and no violation will be reported.
See the property `annotations`.

Example(s):

```java
// This class is unusable, since it cannot be
// instantiated (private constructor),
// and no static method can be called.

public class Foo {
  private Foo() {}
  void foo() {}
}
```


#### More Than One Logger {#PMD_MTOL}
Normally only one logger is used in each class. This rule supports slf4j, log4j, Java Util Logging and
log4j2 (since 6.19.0).

Example(s):

```java
public class Foo {
    Logger log = Logger.getLogger(Foo.class.getName());
    // It is very rare to see two loggers on a class, normally
    // log information is multiplexed by levels
    Logger log2= Logger.getLogger(Foo.class.getName());
}
```


#### Non Case Label In Switch Statement {#PMD_NCLISS}
A non-case label (e.g. a named break/continue label) was present in a switch statement.
This legal, but confusing. It is easy to mix up the case labels and the non-case labels.

Example(s):

```java
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


#### Non Static Initializer {#PMD_NSI}
A non-static initializer block will be called any time a constructor is invoked (just prior to
invoking the constructor).  While this is a valid language construct, it is rarely used and is
confusing.

Example(s):

```java
public class MyClass {
  // this block gets run before any call to a constructor
  {
    System.out.println("I am about to construct myself");
  }
}
```


#### Override Both Equals And Hashcode {#PMD_OBEAH}
Override both public boolean Object.equals(Object other), and public int Object.hashCode(), or override neither.  Even if you are inheriting a hashCode() from a parent class, consider implementing hashCode and explicitly delegating to your superclass.

Example(s):

```java
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


#### Proper Clone Implementation {#PMD_PCI}
Object clone() should be implemented with super.clone().

Example(s):

```java
class Foo{
    public Object clone(){
        return new Foo(); // This is bad
    }
}
```


#### Proper Logger {#PMD_PL}
A logger should normally be defined private static final and be associated with the correct class.
`private final Log log;` is also allowed for rare cases where loggers need to be passed around,
with the restriction that the logger needs to be passed into the constructor.

Example(s):

```java
public class Foo {

    private static final Log LOG = LogFactory.getLog(Foo.class);    // proper way

    protected Log LOG = LogFactory.getLog(Testclass.class);         // wrong approach
}
```


#### Return Empty Array Rather Than Null {#PMD_REARTN}
For any method that returns an array, it is a better to return an empty array rather than a
null reference. This removes the need for null checking all results and avoids inadvertent
NullPointerExceptions.

Example(s):

```java
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


#### Return From Finally Block {#PMD_RFFB}
Avoid returning from a finally block, this can discard exceptions.

Example(s):

```java
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


#### Simple Date Format Needs Locale {#PMD_SDFNL}
Be sure to specify a Locale when creating SimpleDateFormat instances to ensure that locale-appropriate
formatting is used.

Example(s):

```java
public class Foo {
  // Should specify Locale.US (or whatever)
  private SimpleDateFormat sdf = new SimpleDateFormat("pattern");
}
```


#### Single Method Singleton {#PMD_SMS}
Some classes contain overloaded getInstance. The problem with overloaded getInstance methods
is that the instance created using the overloaded method is not cached and so,
for each call and new objects will be created for every invocation.

Example(s):

```java
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


#### Singleton Class Returning New Instance {#PMD_SCRNI}
Some classes contain overloaded getInstance. The problem with overloaded getInstance methods
is that the instance created using the overloaded method is not cached and so,
for each call and new objects will be created for every invocation.

Example(s):

```java
class Singleton {
    private static Singleton instance = null;
    public static Singleton getInstance() {
        synchronized(Singleton.class) {
            return new Singleton();
        }
    }
}
```


#### Static EJBField Should Be Final {#PMD_SEJBFSBF}
According to the J2EE specification, an EJB should not have any static fields
with write access. However, static read-only fields are allowed. This ensures proper
behavior especially when instances are distributed by the container on several JREs.

Example(s):

```java
public class SomeEJB extends EJBObject implements EJBLocalHome {

    private static int CountA;          // poor, field can be edited

    private static final int CountB;    // preferred, read-only access
}
```


#### String Buffer Instantiation With Char {#PMD_SBIWC}
Individual character values provided as initialization arguments will be converted into integers.
This can lead to internal buffer sizes that are larger than expected. Some examples:

```
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
```

Example(s):

```java
// misleading instantiation, these buffers
// are actually sized to 99 characters long
StringBuffer  sb1 = new StringBuffer('c');
StringBuilder sb2 = new StringBuilder('c');

// in these forms, just single characters are allocated
StringBuffer  sb3 = new StringBuffer("c");
StringBuilder sb4 = new StringBuilder("c");
```


#### Suspicious Equals Method Name {#PMD_SEMN}
The method name and parameter number are suspiciously close to `Object.equals`, which can denote an
intention to override it. However, the method does not override `Object.equals`, but overloads it instead.
Overloading `Object.equals` method is confusing for other programmers, error-prone and hard to maintain,
especially when using inheritance, because `@Override` annotations used in subclasses can provide a false
sense of security. For more information on `Object.equals` method, see Effective Java, 3rd Edition,
Item 10: Obey the general contract when overriding equals.

Example(s):

```java
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


#### Suspicious Hashcode Method Name {#PMD_SHMN}
The method name and return type are suspiciously close to hashCode(), which may denote an intention
to override the hashCode() method.

Example(s):

```java
public class Foo {
    public int hashcode() { // oops, this probably was supposed to be 'hashCode'
    }
}
```


#### Suspicious Octal Escape {#PMD_SOE}
A suspicious octal escape sequence was found inside a String literal.
The Java language specification (section 3.10.6) says an octal
escape sequence inside a literal String shall consist of a backslash
followed by:

    OctalDigit | OctalDigit OctalDigit | ZeroToThree OctalDigit OctalDigit

Any octal escape sequence followed by non-octal digits can be confusing,
e.g. "\038" is interpreted as the octal escape sequence "\03" followed by
the literal character "8".

Example(s):

```java
public void foo() {
  // interpreted as octal 12, followed by character '8'
  System.out.println("suspicious: \128");
}
```


#### Test Class Without Test Cases {#PMD_TCWTC}
Test classes end with the suffix Test. Having a non-test class with that name is not a good practice,
since most people will assume it is a test case. Test classes have test methods named testXXX.

Example(s):

```java
//Consider changing the name of the class if it is not a test
//Consider adding test methods if it is a test
public class CarTest {
   public static void main(String[] args) {
    // do something
   }
   // code
}
```


#### Unconditional If Statement {#PMD_UIS}
Do not use "if" statements whose conditionals are always true or always false.

Example(s):

```java
public class Foo {
    public void close() {
        if (true) {        // fixed conditional, not recommended
            // ...
        }
    }
}
```


#### Unnecessary Boolean Assertion {#PMD_UBA}
A JUnit test assertion with a boolean literal is unnecessary since it always will evaluate to the same thing.
Consider using flow control (in case of assertTrue(false) or similar) or simply removing
statements like assertTrue(true) and assertFalse(false).  If you just want a test to halt after finding
an error, use the fail() method and provide an indication message of why it did.

Example(s):

```java
public class SimpleTest extends TestCase {
    public void testX() {
        assertTrue(true);       // serves no real purpose
    }
}
```


#### Unnecessary Case Change {#PMD_UCC}
Using equalsIgnoreCase() is faster than using toUpperCase/toLowerCase().equals()

Example(s):

```java
boolean answer1 = buz.toUpperCase().equals("baz");              // should be buz.equalsIgnoreCase("baz")

boolean answer2 = buz.toUpperCase().equalsIgnoreCase("baz");    // another unnecessary toUpperCase()
```


#### Unnecessary Conversion Temporary {#PMD_UCT}
Avoid the use temporary objects when converting primitives to Strings. Use the static conversion methods
on the wrapper classes instead.

Example(s):

```java
public String convert(int x) {
    String foo = new Integer(x).toString(); // this wastes an object

    return Integer.toString(x);             // preferred approach
}
```


#### Unused Null Check In Equals {#PMD_UNCIE}
After checking an object reference for null, you should invoke equals() on that object rather than passing it to another object's equals() method.

Example(s):

```java
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


#### Use Correct Exception Logging {#PMD_UCEL}
To make sure the full stacktrace is printed out, use the logging statement with two arguments: a String and a Throwable.

Example(s):

```java
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


#### Use Equals To Compare Strings {#PMD_UETCS}
Using '==' or '!=' to compare strings only works if intern version is used on both sides.
Use the equals() method instead.

Example(s):

```java
public boolean test(String s) {
    if (s == "one") return true;        // unreliable
    if ("two".equals(s)) return true;   // better
    return false;
}
```


#### Use Locale With Case Conversions {#PMD_ULWCC}
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

```java
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


#### Useless Operation On Immutable {#PMD_UOOI}
An operation on an Immutable object (String, BigDecimal or BigInteger) won't change the object itself
since the result of the operation is a new object. Therefore, ignoring the operation result is an error.

Example(s):

```java
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


### Multithreading Rules

#### Avoid Synchronized At Method Level {#PMD_ASAML}
Method-level synchronization can cause problems when new code is added to the method.
Block-level synchronization helps to ensure that only the code that needs synchronization
gets it.

Example(s):

```java
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


#### Avoid Thread Group {#PMD_ATG}
Avoid using java.lang.ThreadGroup; although it is intended to be used in a threaded environment
it contains methods that are not thread-safe.

Example(s):

```java
public class Bar {
    void buz() {
        ThreadGroup tg = new ThreadGroup("My threadgroup");
        tg = new ThreadGroup(tg, "my thread group");
        tg = Thread.currentThread().getThreadGroup();
        tg = System.getSecurityManager().getThreadGroup();
    }
}
```


#### Dont Call Thread Run {#PMD_DCTR}
Explicitly calling Thread.run() method will execute in the caller's thread of control.  Instead, call Thread.start() for the intended behavior.

Example(s):

```java
Thread t = new Thread();
t.run();            // use t.start() instead
new Thread().run(); // same violation
```


#### Double Checked Locking {#PMD_DCL}
Partially created objects can be returned by the Double Checked Locking pattern when used in Java.
An optimizing JRE may assign a reference to the baz variable before it calls the constructor of the object the
reference points to.

Note: With Java 5, you can make Double checked locking work, if you declare the variable to be `volatile`.

For more details refer to: <http://www.javaworld.com/javaworld/jw-02-2001/jw-0209-double.html>
or <http://www.cs.umd.edu/~pugh/java/memoryModel/DoubleCheckedLocking.html>

Example(s):

```java
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


#### Non Thread Safe Singleton {#PMD_NTSS}
Non-thread safe singletons can result in bad state changes. Eliminate
static singletons if possible by instantiating the object directly. Static
singletons are usually not needed as only a single instance exists anyway.
Other possible fixes are to synchronize the entire method or to use an
[initialize-on-demand holder class](https://en.wikipedia.org/wiki/Initialization-on-demand_holder_idiom).

Refrain from using the double-checked locking pattern. The Java Memory Model doesn't
guarantee it to work unless the variable is declared as `volatile`, adding an uneeded
performance penalty. [Reference](http://www.cs.umd.edu/~pugh/java/memoryModel/DoubleCheckedLocking.html)

See Effective Java, item 48.

Example(s):

```java
private static Foo foo = null;

//multiple simultaneous callers may see partially initialized objects
public static Foo getFoo() {
    if (foo==null) {
        foo = new Foo();
    }
    return foo;
}
```


#### Unsynchronized Static Date Formatter {#PMD_USDF}
SimpleDateFormat instances are not synchronized. Sun recommends using separate format instances
for each thread. If multiple threads must access a static formatter, the formatter must be
synchronized on block level.

This rule has been deprecated in favor of the rule [Unsynchronized Static Formatter](#PMD_USF).

Example(s):

```java
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


#### Unsynchronized Static Formatter {#PMD_USF}
Instances of `java.text.Format` are generally not synchronized.
Sun recommends using separate format instances for each thread.
If multiple threads must access a static formatter, the formatter must be
synchronized on block level.

Example(s):

```java
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


#### Use Notify All Instead Of Notify {#PMD_UNAION}
Thread.notify() awakens a thread monitoring the object. If more than one thread is monitoring, then only
one is chosen.  The thread chosen is arbitrary; thus its usually safer to call notifyAll() instead.

Example(s):

```java
void bar() {
    x.notify();
    // If many threads are monitoring x, only one (and you won't know which) will be notified.
    // use instead:
    x.notifyAll();
  }
```


### Performance Rules

#### Add Empty String {#PMD_AES}
The conversion of literals to strings by concatenating them with empty strings is inefficient.
It is much better to use one of the type-specific toString() methods instead.

Example(s):

```java
String s = "" + 123;                // inefficient
String t = Integer.toString(456);   // preferred approach
```


#### Avoid Array Loops {#PMD_AAL}
Instead of manually copying data between two arrays, use the efficient Arrays.copyOf or System.arraycopy method instead.

Example(s):

```java
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


#### Avoid Calendar Date Creation {#PMD_ACDC}
Problem: A Calendar is a heavyweight object and expensive to create.

Solution: Use `new Date()`, Java 8+ `java.time.LocalDateTime.now()` or `ZonedDateTime.now()`.

Example(s):

```java
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


#### Avoid File Stream {#PMD_AFS}
The FileInputStream and FileOutputStream classes contains a finalizer method which will cause garbage
collection pauses.
See [JDK-8080225](https://bugs.openjdk.java.net/browse/JDK-8080225) for details.

The FileReader and FileWriter constructors instantiate FileInputStream and FileOutputStream,
again causing garbage collection issues while finalizer methods are called.

* Use `Files.newInputStream(Paths.get(fileName))` instead of `new FileInputStream(fileName)`.
* Use `Files.newOutputStream(Paths.get(fileName))` instead of `new FileOutputStream(fileName)`.
* Use `Files.newBufferedReader(Paths.get(fileName))` instead of `new FileReader(fileName)`.
* Use `Files.newBufferedWriter(Paths.get(fileName))` instead of `new FileWriter(fileName)`.

Please note, that the `java.nio` API does not throw a `FileNotFoundException` anymore, instead
it throws a `NoSuchFileException`. If your code dealt explicitly with a `FileNotFoundException`,
then this needs to be adjusted. Both exceptions are subclasses of `IOException`, so catching
that one covers both.

Example(s):

```java
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


#### Big Integer Instantiation {#PMD_BII}
Don't create instances of already existing BigInteger (BigInteger.ZERO, BigInteger.ONE) and
for Java 1.5 onwards, BigInteger.TEN and BigDecimal (BigDecimal.ZERO, BigDecimal.ONE, BigDecimal.TEN)

Example(s):

```java
BigInteger bi = new BigInteger(1);       // reference BigInteger.ONE instead
BigInteger bi2 = new BigInteger("0");    // reference BigInteger.ZERO instead
BigInteger bi3 = new BigInteger(0.0);    // reference BigInteger.ZERO instead
BigInteger bi4;
bi4 = new BigInteger(0);                 // reference BigInteger.ZERO instead
```


#### Boolean Instantiation {#PMD_BI}
Avoid instantiating Boolean objects; you can reference Boolean.TRUE, Boolean.FALSE, or call Boolean.valueOf() instead.
Note that new Boolean() is deprecated since JDK 9 for that reason.

Example(s):

```java
Boolean bar = new Boolean("true");        // unnecessary creation, just reference Boolean.TRUE;
Boolean buz = Boolean.valueOf(false);    // ...., just reference Boolean.FALSE;
```


#### Consecutive Appends Should Reuse {#PMD_CASR}
Consecutive calls to StringBuffer/StringBuilder .append should be chained, reusing the target object. This can improve the performance
by producing a smaller bytecode, reducing overhead and improving inlining. A complete analysis can be found [here](https://github.com/pmd/pmd/issues/202#issuecomment-274349067)

Example(s):

```java
String foo = " ";

StringBuffer buf = new StringBuffer();
buf.append("Hello"); // poor
buf.append(foo);
buf.append("World");

StringBuffer buf = new StringBuffer();
buf.append("Hello").append(foo).append("World"); // good
```


#### Consecutive Literal Appends {#PMD_CLA}
Consecutively calling StringBuffer/StringBuilder.append(...) with literals should be avoided.
Since the literals are constants, they can already be combined into a single String literal and this String
can be appended in a single method call.

Example(s):

```java
StringBuilder buf = new StringBuilder();
buf.append("Hello").append(" ").append("World");    // poor
buf.append("Hello World");                          // good

buf.append('h').append('e').append('l').append('l').append('o'); // poor
buf.append("hello");                                             // good

buf.append(1).append('m');  // poor
buf.append("1m");           // good
```


#### Inefficient String Buffering {#PMD_ISB}
Avoid concatenating non-literals in a StringBuffer constructor or append() since intermediate buffers will
need to be be created and destroyed by the JVM.

Example(s):

```java
// Avoid this, two buffers are actually being created here
StringBuffer sb = new StringBuffer("tmp = "+System.getProperty("java.io.tmpdir"));

// do this instead
StringBuffer sb = new StringBuffer("tmp = ");
sb.append(System.getProperty("java.io.tmpdir"));
```


#### Optimizable To Array Call {#PMD_OTAC}
Calls to a collection's `toArray(E[])` method should specify a target array of zero size. This allows the JVM
to optimize the memory allocation and copying as much as possible.

Previous versions of this rule (pre PMD 6.0.0) suggested the opposite, but current JVM implementations
perform always better, when they have full control over the target array. And allocation an array via
reflection is nowadays as fast as the direct allocation.

See also [Arrays of Wisdom of the Ancients](https://shipilev.net/blog/2016/arrays-wisdom-ancients/)

Note: If you don't need an array of the correct type, then the simple `toArray()` method without an array
is faster, but returns only an array of type `Object[]`.

Example(s):

```java
List<Foo> foos = getFoos();

// much better; this one allows the jvm to allocate an array of the correct size and effectively skip
// the zeroing, since each array element will be overridden anyways
Foo[] fooArray = foos.toArray(new Foo[0]);

// inefficient, the array needs to be zeroed out by the jvm before it is handed over to the toArray method
Foo[] fooArray = foos.toArray(new Foo[foos.size()]);
```


#### Redundant Field Initializer {#PMD_RFI}
Java will initialize fields with known default values so any explicit initialization of those same defaults
is redundant and results in a larger class file (approximately three additional bytecode instructions per field).

Example(s):

```java
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


#### String Instantiation {#PMD_StI}
Avoid instantiating String objects; this is usually unnecessary since they are immutable and can be safely shared.

Example(s):

```java
private String bar = new String("bar"); // just do a String bar = "bar";
```


#### String To String {#PMD_STS}
Avoid calling toString() on objects already known to be string instances; this is unnecessary.

Example(s):

```java
private String baz() {
    String bar = "howdy";
    return bar.toString();
}
```


#### Too Few Branches For ASwitch Statement {#PMD_TFBFASS}
Switch statements are intended to be used to support complex branching behaviour. Using a switch for only a few
cases is ill-advised, since switches are not as easy to understand as if-then statements. In these cases use the
if-then statement to increase code readability.

Example(s):

```java
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


#### Unnecessary Wrapper Object Creation {#PMD_UWOC}
Most wrapper classes provide static conversion methods that avoid the need to create intermediate objects
just to create the primitive forms. Using these avoids the cost of creating objects that also need to be
garbage-collected later.

Example(s):

```java
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


#### Use Array List Instead Of Vector {#PMD_UALIOV}
ArrayList is a much better Collection implementation than Vector if thread-safe operation is not required.

Example(s):

```java
public class SimpleTest extends TestCase {
    public void testX() {
    Collection c1 = new Vector();
    Collection c2 = new ArrayList();    // achieves the same with much better performance
    }
}
```


#### Use Arrays As List {#PMD_UAAL}
The java.util.Arrays class has a "asList" method that should be used when you want to create a new List from
an array of objects. It is faster than executing a loop to copy all the elements of the array one by one.

Note that the result of Arrays.asList() is backed by the specified array,
changes in the returned list will result in the array to be modified.
For that reason, it is not possible to add new elements to the returned list of Arrays.asList() (UnsupportedOperationException).
You must use new ArrayList<>(Arrays.asList(...)) if that is inconvenient for you (e.g. because of concurrent access).

Example(s):

```java
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


#### Use IOStreams With Apache Commons File Item {#PMD_UIOSWACFI}
Problem: Use of [FileItem.get()](https://commons.apache.org/proper/commons-fileupload/apidocs/org/apache/commons/fileupload/FileItem.html#get--)
and [FileItem.getString()](https://commons.apache.org/proper/commons-fileupload/apidocs/org/apache/commons/fileupload/FileItem.html#getString--)
could exhaust memory since they load the entire file into memory.

Solution: Use [FileItem.getInputStream()](https://commons.apache.org/proper/commons-fileupload/apidocs/org/apache/commons/fileupload/FileItem.html#getInputStream--)
and buffering.

Example(s):

```java
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


#### Use String Buffer For String Appends {#PMD_USBFSA}
The use of the '+=' operator for appending strings causes the JVM to create and use an internal StringBuffer.
If a non-trivial number of these concatenations are being used then the explicit use of a StringBuilder or
threadsafe StringBuffer is recommended to avoid this.

Example(s):

```java
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


### Security Rules

#### Hard Coded Crypto Key {#PMD_HCCK}
Do not use hard coded values for cryptographic operations. Please store keys outside of source code.

Example(s):

```java
public class Foo {
    void good() {
        SecretKeySpec secretKeySpec = new SecretKeySpec(Properties.getKey(), "AES");
    }

    void bad() {
        SecretKeySpec secretKeySpec = new SecretKeySpec("my secret here".getBytes(), "AES");
    }
}
```


#### Insecure Crypto Iv {#PMD_ICI}
Do not use hard coded initialization vector in cryptographic operations. Please use a randomly generated IV.

Example(s):

```java
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


