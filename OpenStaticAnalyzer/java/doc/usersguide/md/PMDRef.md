## Reference of PMD coding rule violations

OpenStaticAnalyzer incorporates the [PMD] tool for coding rule violation checking and imports its results. OpenStaticAnalyzer also associates the issued rule violations with source code elements (i.e. methods, classes, packages, and components), and calculates metrics for the source code elements, which represent the amount of violations of each ruleset, rule, and priority groups, respectively. In addition, OpenStaticAnalyzer uses an optimized PMD setting, where the poorly performing PMD rule checks are disabled, and all other rules are reprioritized by our software developer and QA experts. Please note that if a valid FaultHunter license key is available, then the reimplemented PMD rules will be swithed off automatically and FaultHunter will provide the results instead. If no license key is available (free version), then the original PMD rule violation checks will be executed.

OpenStaticAnalyzer uses PMD "as is", without any guaranties that the results of PMD are correct. All statements of the PMD license apply here as well. All texts describing the rulesets and the individual rules are copied from its official home page with some minor grammatical fixes.

The list of rulesets and rules contained in each ruleset are the following:

- **Basic Rules:** The Basic ruleset contains a collection of good practices, which should be followed.

- **Brace Rules:** The Braces ruleset contains rules regarding the use and placement of braces.

- **Clone Implementation Rules:** The Clone Implementation ruleset contains a collection of rules that find questionable usages of the clone() method.

- **Controversial Rules:** The Controversial ruleset contains rules that, for whatever reason, are considered controversial. They are held here to allow people to include them as they see fit within their custom rulesets.

- **Design Rules:** The Design ruleset contains rules that flag suboptimal code implementations. Alternate approaches are suggested.

- **Finalizer Rules:** These rules deal with different problems that can occur with finalizers.

- **Import Statement Rules:** These rules deal with different problems that can occur with import statements.

- **J2EE Rules:** Rules specific to the use of J2EE implementations.

- **JUnit Rules:** These rules deal with different problems that can occur with JUnit tests.

- **Jakarta Commons Logging Rules:** The Jakarta Commons Logging ruleset contains a collection of rules that find questionable usages of that framework.

- **Java Logging Rules:** The Java Logging ruleset contains a collection of rules that find questionable usages of the logger.

- **JavaBean Rules:** The JavaBeans Ruleset catches instances of bean rules not being followed.

- **Naming Rules:** The Naming Ruleset contains rules regarding preferred usage of names and identifiers.

- **Optimization Rules:** These rules deal with different optimizations that generally apply to best practices.

- **Security Code Guideline Rules:** These rules check the security guidelines from Sun, published at [http://java.sun.com/security/seccodeguide.html\#gcg]

- **Strict Exception Rules:** These rules provide some strict guidelines about throwing and catching exceptions.

- **String and StringBuffer Rules:** These rules deal with different issues that can arise with manipulation of the String, StringBuffer, or StringBuilder instances.

- **Type Resolution Rules:** These are rules which resolve java Class files for comparison, as opposed to a String

- **Unnecessary and Unused Code Rules:** The Unnecessary and Unused Ruleset contains a collection of rules for unnecessary,unused or ineffective code.

The following table contains the enabled rules and their priorities:

  Category                           Name                                                     Abbreviation  Prio.    
  ---------------------------------- -------------------------------------------------------- ------------- ---------
  Basic Rules                        Avoid Branching Statement As Last In Loop                PMD_ABSALIL   Major    
                                     Avoid Decimal Literals In Big Decimal Constructor        PMD_ADLIBDC   Critical 
                                     Avoid Multiple Unary Operators                           PMD_AMUO      Major    
                                     Avoid Thread Group                                       PMD_ATG       Critical 
                                     Avoid Using Hard Coded IP                                PMD_AUHCIP    Major    
                                     Avoid Using Octal Values                                 PMD_AUOV      Critical 
                                     Big Integer Instantiation                                PMD_BII       Minor    
                                     Boolean Instantiation                                    PMD_BI        Minor    
                                     Broken Null Check                                        PMD_BNC       Critical 
                                     Check Result Set                                         PMD_CRS       Critical 
                                     Check Skip Result                                        PMD_CSR       Critical 
                                     Class Cast Exception With To Array                       PMD_CCEWTA    Critical 
                                     Collapsible If Statements                                PMD_CIS       Minor    
                                     Dont Call Thread Run                                     PMD_DCTR      Critical 
                                     Dont Use Float Type For Loop Indices                     PMD_DUFTFLI   Critical 
                                     Double Checked Locking                                   PMD_DCL       Critical 
                                     Empty Catch Block                                        PMD_ECB       Critical 
                                     Empty Finally Block                                      PMD_EFB       Minor    
                                     Empty If Stmt                                            PMD_EIS       Major    
                                     Empty Statement Block                                    PMD_EmSB      Minor    
                                     Empty Statement Not In Loop                              PMD_ESNIL     Minor    
                                     Empty Static Initializer                                 PMD_ESI       Minor    
                                     Empty Switch Statements                                  PMD_ESS       Major    
                                     Empty Synchronized Block                                 PMD_ESB       Major    
                                     Empty Try Block                                          PMD_ETB       Major    
                                     Empty While Stmt                                         PMD_EWS       Critical 
                                     Extends Object                                           PMD_EO        Minor    
                                     For Loop Should Be While Loop                            PMD_FLSBWL    Minor    
                                     Jumbled Incrementer                                      PMD_JI        Critical 
                                     Misplaced Null Check                                     PMD_MNC       Critical 
                                     Override Both Equals And Hashcode                        PMD_OBEAH     Critical 
                                     Return From Finally Block                                PMD_RFFB      Critical 
                                     Unconditional If Statement                               PMD_UIS       Major    
                                     Unnecessary Conversion Temporary                         PMD_UCT       Minor    
                                     Unused Null Check In Equals                              PMD_UNCIE     Critical 
                                     Useless Operation On Immutable                           PMD_UOOI      Critical 
                                     Useless Overriding Method                                PMD_UOM       Minor    
  Brace Rules                        For Loops Must Use Braces                                PMD_FLMUB     Minor    
                                     If Else Stmts Must Use Braces                            PMD_IESMUB    Minor    
                                     If Stmts Must Use Braces                                 PMD_ISMUB     Minor    
                                     While Loops Must Use Braces                              PMD_WLMUB     Minor    
  Clone Implementation Rules         Clone Throws Clone Not Supported Exception               PMD_CTCNSE    Major    
                                     Proper Clone Implementation                              PMD_PCI       Critical 
  Controversial Rules                Assignment In Operand                                    PMD_AIO       Minor    
                                     Avoid Accessibility Alteration                           PMD_AAA       Major    
                                     Avoid Prefixing Method Parameters                        PMD_APMP      Minor    
                                     Avoid Using Native Code                                  PMD_AUNC      Major    
                                     Default Package                                          PMD_DP        Minor    
                                     Do Not Call Garbage Collection Explicitly                PMD_DNCGCE    Major    
                                     Dont Import Sun                                          PMD_DIS       Major    
                                     One Declaration Per Line                                 PMD_ODPL      Minor    
                                     Suspicious Octal Escape                                  PMD_SOE       Major    
                                     Unnecessary Constructor                                  PMD_UC        Minor    
  Design Rules                       Abstract Class Without Abstract Method                   PMD_ACWAM     Minor    
                                     Abstract Class Without Any Method                        PMD_AbCWAM    Minor    
                                     Assignment To Non Final Static                           PMD_ATNFS     Critical 
                                     Avoid Constants Interface                                PMD_ACI       Minor    
                                     Avoid Instanceof Checks In Catch Clause                  PMD_AICICC    Major    
                                     Avoid Protected Field In Final Class                     PMD_APFIFC    Minor    
                                     Avoid Protected Method In Final Class Not Extending      PMD_APMIFCNE  Minor    
                                     Avoid Reassigning Parameters                             PMD_ARP       Minor    
                                     Avoid Synchronized At Method Level                       PMD_ASAML     Minor    
                                     Bad Comparison                                           PMD_BC        Critical 
                                     Class With Only Private Constructors Should Be Final     PMD_CWOPCSBF  Minor    
                                     Close Resource                                           PMD_ClR       Critical 
                                     Constructor Calls Overridable Method                     PMD_CCOM      Critical 
                                     Default Label Not Last In Switch Stmt                    PMD_DLNLISS   Minor    
                                     Empty Method In Abstract Class Should Be Abstract        PMD_EMIACSBA  Major    
                                     Equals Null                                              PMD_EN        Critical 
                                     Field Declarations Should Be At Start Of Class           PMD_FDSBASOC  Minor    
                                     Final Field Could Be Static                              PMD_FFCBS     Minor    
                                     Idempotent Operations                                    PMD_IO        Major    
                                     Immutable Field                                          PMD_IF        Minor    
                                     Instantiation To Get Class                               PMD_ITGC      Major    
                                     Logic Inversion                                          PMD_LI        Minor    
                                     Missing Break In Switch                                  PMD_MBIS      Critical 
                                     Missing Static Method In Non Instantiatable Class        PMD_MSMINIC   Minor    
                                     Non Case Label In Switch Statement                       PMD_NCLISS    Critical 
                                     Non Static Initializer                                   PMD_NSI       Critical 
                                     Non Thread Safe Singleton                                PMD_NTSS      Critical 
                                     Optimizable To Array Call                                PMD_OTAC      Major    
                                     Position Literals First In Case Insensitive Comparisons  PMD_PLFICIC   Critical 
                                     Position Literals First In Comparisons                   PMD_PLFIC     Critical 
                                     Preserve Stack Trace                                     PMD_PST       Major    
                                     Return Empty Array Rather Than Null                      PMD_REARTN    Major    
                                     Simple Date Format Needs Locale                          PMD_SDFNL     Minor    
                                     Simplify Boolean Expressions                             PMD_SBE       Minor    
                                     Simplify Boolean Returns                                 PMD_SBR       Minor    
                                     Simplify Conditional                                     PMD_SC        Minor    
                                     Singular Field                                           PMD_SF        Major    
                                     Switch Stmts Should Have Default                         PMD_SSSHD     Major    
                                     Too Few Branches For ASwitch Statement                   PMD_TFBFASS   Minor    
                                     Uncommented Empty Constructor                            PMD_UEC       Minor    
                                     Uncommented Empty Method                                 PMD_UEM       Minor    
                                     Unnecessary Local Before Return                          PMD_ULBR      Minor    
                                     Unsynchronized Static Date Formatter                     PMD_USDF      Critical 
                                     Use Collection Is Empty                                  PMD_UCIE      Major    
                                     Use Locale With Case Conversions                         PMD_ULWCC     Critical 
                                     Use Notify All Instead Of Notify                         PMD_UNAION    Critical 
                                     Use Varargs                                              PMD_UV        Minor    
  Finalizer Rules                    Avoid Calling Finalize                                   PMD_ACF       Major    
                                     Empty Finalizer                                          PMD_EF        Minor    
                                     Finalize Does Not Call Super Finalize                    PMD_FDNCSF    Critical 
                                     Finalize Only Calls Super Finalize                       PMD_FOCSF     Minor    
                                     Finalize Overloaded                                      PMD_FO        Critical 
                                     Finalize Should Be Protected                             PMD_FSBP      Critical 
  Import Statement Rules             Dont Import Java Lang                                    PMD_DIJL      Minor    
                                     Duplicate Imports                                        PMD_DI        Minor    
                                     Import From Same Package                                 PMD_IFSP      Minor    
                                     Too Many Static Imports                                  PMD_TMSI      Major    
                                     Unnecessary Fully Qualified Name                         PMD_UFQN      Minor    
  J2EE Rules                         Do Not Call System Exit                                  PMD_DNCSE     Critical 
                                     Local Home Naming Convention                             PMD_LHNC      Major    
                                     Local Interface Session Naming Convention                PMD_LISNC     Major    
                                     MDBAnd Session Bean Naming Convention                    PMD_MDBASBNC  Major    
                                     Remote Interface Naming Convention                       PMD_RINC      Major    
                                     Remote Session Interface Naming Convention               PMD_RSINC     Major    
                                     Static EJBField Should Be Final                          PMD_SEJBFSBF  Critical 
  JUnit Rules                        JUnit Assertions Should Include Message                  PMD_JUASIM    Minor    
                                     JUnit Spelling                                           PMD_JUS       Critical 
                                     JUnit Static Suite                                       PMD_JUSS      Critical 
                                     JUnit Test Contains Too Many Asserts                     PMD_JUTCTMA   Minor    
                                     JUnit Tests Should Include Assert                        PMD_JUTSIA    Major    
                                     Simplify Boolean Assertion                               PMD_SBA       Minor    
                                     Test Class Without Test Cases                            PMD_TCWTC     Minor    
                                     Unnecessary Boolean Assertion                            PMD_UBA       Minor    
                                     Use Assert Equals Instead Of Assert True                 PMD_UAEIOAT   Major    
                                     Use Assert Null Instead Of Assert True                   PMD_UANIOAT   Minor    
                                     Use Assert Same Instead Of Assert True                   PMD_UASIOAT   Minor    
                                     Use Assert True Instead Of Assert Equals                 PMD_UATIOAE   Minor    
  Jakarta Commons Logging Rules      Guard Debug Logging                                      PMD_GDL       Major    
                                     Guard Log Statement                                      PMD_GLS       Minor    
                                     Proper Logger                                            PMD_PL        Minor    
                                     Use Correct Exception Logging                            PMD_UCEL      Major    
  Java Logging Rules                 Avoid Print Stack Trace                                  PMD_APST      Major    
                                     Guard Log Statement Java Util                            PMD_GLSJU     Minor    
                                     Logger Is Not Static Final                               PMD_LINSF     Minor    
                                     More Than One Logger                                     PMD_MTOL      Major    
                                     System Println                                           PMD_SP        Major    
  JavaBean Rules                     Missing Serial Version UID                               PMD_MSVUID    Major    
  Naming Rules                       Avoid Dollar Signs                                       PMD_ADS       Minor    
                                     Avoid Field Name Matching Method Name                    PMD_AFNMMN    Minor    
                                     Avoid Field Name Matching Type Name                      PMD_AFNMTN    Minor    
                                     Boolean Get Method Name                                  PMD_BGMN      Minor    
                                     Class Naming Conventions                                 PMD_CNC       Minor    
                                     Generics Naming                                          PMD_GN        Minor    
                                     Method Naming Conventions                                PMD_MeNC      Minor    
                                     Method With Same Name As Enclosing Class                 PMD_MWSNAEC   Minor    
                                     No Package                                               PMD_NP        Minor    
                                     Package Case                                             PMD_PC        Minor    
                                     Short Class Name                                         PMD_SCN       Minor    
                                     Short Method Name                                        PMD_SMN       Minor    
                                     Suspicious Constant Field Name                           PMD_SCFN      Minor    
                                     Suspicious Equals Method Name                            PMD_SEMN      Critical 
                                     Suspicious Hashcode Method Name                          PMD_SHMN      Critical 
                                     Variable Naming Conventions                              PMD_VNC       Minor    
  Optimization Rules                 Add Empty String                                         PMD_AES       Minor    
                                     Avoid Array Loops                                        PMD_AAL       Major    
                                     Redundant Field Initializer                              PMD_RFI       Minor    
                                     Unnecessary Wrapper Object Creation                      PMD_UWOC      Major    
                                     Use Array List Instead Of Vector                         PMD_UALIOV    Minor    
                                     Use Arrays As List                                       PMD_UAAL      Major    
                                     Use String Buffer For String Appends                     PMD_USBFSA    Major    
  Security Code Guideline Rules      Array Is Stored Directly                                 PMD_AISD      Major    
                                     Method Returns Internal Array                            PMD_MRIA      Major    
  Strict Exception Rules             Avoid Catching Generic Exception                         PMD_ACGE      Major    
                                     Avoid Catching NPE                                       PMD_ACNPE     Critical 
                                     Avoid Catching Throwable                                 PMD_ACT       Major    
                                     Avoid Losing Exception Information                       PMD_ALEI      Major    
                                     Avoid Rethrowing Exception                               PMD_ARE       Minor    
                                     Avoid Throwing New Instance Of Same Exception            PMD_ATNIOSE   Minor    
                                     Avoid Throwing Null Pointer Exception                    PMD_ATNPE     Critical 
                                     Avoid Throwing Raw Exception Types                       PMD_ATRET     Major    
                                     Do Not Extend Java Lang Error                            PMD_DNEJLE    Critical 
                                     Do Not Throw Exception In Finally                        PMD_DNTEIF    Critical 
                                     Exception As Flow Control                                PMD_EAFC      Major    
  String and StringBuffer Rules      Avoid Duplicate Literals                                 PMD_ADL       Major    
                                     Avoid String Buffer Field                                PMD_ASBF      Minor    
                                     Consecutive Appends Should Reuse                         PMD_CASR      Minor    
                                     Consecutive Literal Appends                              PMD_CLA       Minor    
                                     Inefficient String Buffering                             PMD_ISB       Minor    
                                     String Buffer Instantiation With Char                    PMD_SBIWC     Critical 
                                     String Instantiation                                     PMD_StI       Minor    
                                     String To String                                         PMD_STS       Minor    
                                     Unnecessary Case Change                                  PMD_UCC       Minor    
                                     Use Equals To Compare Strings                            PMD_UETCS     Critical 
  Type Resolution Rules              Clone Method Must Implement Cloneable                    PMD_ClMMIC    Major    
                                     Loose Coupling                                           PMD_LoC       Major    
                                     Signature Declare Throws Exception                       PMD_SiDTE     Major    
                                     Unused Imports                                           PMD_UnI       Minor    
  Unnecessary and Unused Code Rules  Unused Local Variable                                    PMD_ULV       Major    
                                     Unused Private Field                                     PMD_UPF       Major    
                                     Unused Private Method                                    PMD_UPM       Major    

### Basic Rules

#### Avoid Branching Statement As Last In Loop {#PMD_ABSALIL}
Using a branching statement as the last part of a loop may be a bug, and/or is confusing. Ensure that the usage is not a bug, or consider using another approach.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
// unusual use of branching statement in a loop
for (int i = 0; i < 10; i++) {
  if (i*i <= 25) {
    continue;
  }
  break;
}

// this makes more sense ...
for (int i = 0; i < 10; i++) {
  if (i*i > 25) {
    break;
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Avoid Decimal Literals In Big Decimal Constructor {#PMD_ADLIBDC}
One might assume that the result of "new BigDecimal(0.1)" is exactly equal to 0.1, but it is actually equal to .1000000000000000055511151231257827021181583404541015625. This is because 0.1 cannot be represented exactly as a double (or as a binary fraction of any finite length). Thus, the long value that is being passed in to the constructor is not exactly equal to 0.1, appearances notwithstanding. The (String) constructor, on the other hand, is perfectly predictable: 'new BigDecimal("0.1")' is exactly equal to 0.1, as one would expect. Therefore, it is generally recommended that the (String) constructor be used in preference to this one.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
BigDecimal bd = new BigDecimal(1.123);    // loss of precision, this would trigger the rule
BigDecimal bd = new BigDecimal("1.123");  // preferred approach
BigDecimal bd = new BigDecimal(12);       // preferred approach, ok for integer values
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Avoid Multiple Unary Operators {#PMD_AMUO}
The use of multiple unary operators may be problematic, and/or confusing. Ensure that the intended usage is not a bug, or consider simplifying the expression.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
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
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Avoid Thread Group {#PMD_ATG}
Avoid using java.lang.ThreadGroup; although it is intended to be used in a threaded environment it contains methods that are not thread-safe.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Bar {
  void buz() {
    ThreadGroup tg = new ThreadGroup("My threadgroup");
    tg = new ThreadGroup(tg, "my thread group");
    tg = Thread.currentThread().getThreadGroup();
    tg = System.getSecurityManager().getThreadGroup();
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Avoid Using Hard Coded IP {#PMD_AUHCIP}
Application with hard-coded IP addresses can become impossible to deploy in some cases. Externalizing IP addresses is preferable.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  private String ip = "127.0.0.1"; // not recommended
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Avoid Using Octal Values {#PMD_AUOV}
Integer literals should not start with zero since this denotes that the rest of literal will be interpreted as an octal value.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
int i = 012;  // set i with 10 not 12
int j = 010;  // set j with 8 not 10
k = i * j;    // set k with 80 not 120
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Big Integer Instantiation {#PMD_BII}
Don't create instances of already existing BigInteger (BigInteger.ZERO, BigInteger.ONE) and for Java 1.5 onwards, BigInteger.TEN and BigDecimal (BigDecimal.ZERO, BigDecimal.ONE, BigDecimal.TEN)

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
BigInteger bi = new BigInteger(1);    // reference BigInteger.ONE instead
BigInteger bi2 = new BigInteger("0"); // reference BigInteger.ZERO instead
BigInteger bi3 = new BigInteger(0.0); // reference BigInteger.ZERO instead
BigInteger bi4;
bi4 = new BigInteger(0);              // reference BigInteger.ZERO instead
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Boolean Instantiation {#PMD_BI}
Avoid instantiating Boolean objects; you can reference Boolean.TRUE, Boolean.FALSE, or call Boolean.valueOf() instead.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
Boolean bar = new Boolean("true");    // unnecessary creation, just reference Boolean.TRUE;
Boolean buz = Boolean.valueOf(false); // ...., just reference Boolean.FALSE;
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Broken Null Check {#PMD_BNC}
The null check is broken since it will throw a NullPointerException itself. It is likely that you used || instead of && or vice versa.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public String bar(String string) {
  // should be &&
  if (string!=null || !string.equals(""))
    return string;
  // should be ||
  if (string==null && string.equals(""))
    return string;
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Check Result Set {#PMD_CRS}
Always check the return values of navigation methods (next, previous, first, last) of a ResultSet. If the value return is 'false', it should be handled properly.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
Statement stat = conn.createStatement();
ResultSet rst = stat.executeQuery("SELECT name FROM person");
rst.next(); // what if it returns false? bad form
String firstName = rst.getString(1);
Statement stat = conn.createStatement();
ResultSet rst = stat.executeQuery("SELECT name FROM person");
if (rst.next()) { // result is properly examined and used
  String firstName = rst.getString(1);
} else { // handle missing data
}
            
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Check Skip Result {#PMD_CSR}
The skip() method may skip a smaller number of bytes than requested. Check the returned value to find out if it was the case or not.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
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
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Class Cast Exception With To Array {#PMD_CCEWTA}
When deriving an array of a specific class from your Collection, one should provide an array of the same class as the parameter of the toArray() method. Doing otherwise you will result in a ClassCastException.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
Collection c = new ArrayList();
Integer obj = new Integer(1);
c.add(obj);
// this would trigger the rule (and throw a ClassCastException if executed)
Integer[] a = (Integer [])c.toArray();

// this is fine and will not trigger the rule
Integer[] b = (Integer [])c.toArray(new Integer[c.size()]);

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Collapsible If Statements {#PMD_CIS}
Sometimes two consecutive 'if' statements can be consolidated by separating their conditions with a boolean short-circuit operator.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
void bar() {
  if (x) {      // original implementation
    if (y) {
      // do stuff
    }
  }
}

void bar() {
  if (x && y) { // optimized implementation
    // do stuff
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Dont Call Thread Run {#PMD_DCTR}
Explicitly calling Thread.run() method will execute in the caller's thread of control. Instead, call Thread.start() for the intended behavior.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
Thread t = new Thread();
t.run();                 // use t.start() instead
new Thread().run();      // same violation
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Dont Use Float Type For Loop Indices {#PMD_DUFTFLI}
Don't use floating point for loop indices. If you must use floating point, use double unless you're certain that float provides enough precision and you have a compelling performance need (space or time).

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
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
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Double Checked Locking {#PMD_DCL}
Partially created objects can be returned by the Double Checked Locking pattern when used in Java. An optimizing JRE may assign a reference to the baz variable before it creates the object the reference is intended to point to. For more details refer to: [http://www.javaworld.com/javaworld/jw-02-2001/jw-0209-double.html] or [http://www.cs.umd.edu/\~pugh/java/memoryModel/DoubleCheckedLocking.html]

[http://www.javaworld.com/javaworld/jw-02-2001/jw-0209-double.html]:http://www.javaworld.com/javaworld/jw-02-2001/jw-0209-double.html

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  Object baz;

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
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Empty Catch Block {#PMD_ECB}
Empty Catch Block finds instances where an exception is caught, but nothing is done. In most circumstances, this swallows an exception which should either be acted on or reported.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public void doSomething() {
  try {
    FileInputStream fis = new FileInputStream("/tmp/bugger");
  } catch (IOException ioe) {
    // not good
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Empty Finally Block {#PMD_EFB}
Empty finally blocks serve no purpose and should be removed.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  public void bar() {
    try {
      int x=2;
    } finally {
      // empty!
    }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Empty If Stmt {#PMD_EIS}
Empty If Statement finds instances where a condition is checked but nothing is done about it.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
 void bar(int x) {
    if (x == 0) {
      // empty!
    }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Empty Statement Block {#PMD_EmSB}
Empty block statements serve no purpose and should be removed.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  private int _bar;

  public void setBar(int bar) {
    { _bar = bar; } // Why not?
    {}              // But remove this.
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Empty Statement Not In Loop {#PMD_ESNIL}
An empty statement (or a semicolon by itself) that is not used as the sole body of a 'for' or 'while' loop is probably a bug. It could also be a double semicolon, which has no purpose and should be removed.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public void doit() {
  // this is probably not what you meant to do
  ;
  // the extra semicolon here this is not necessary
  System.out.println("look at the extra semicolon");;
}

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Empty Static Initializer {#PMD_ESI}
An empty static initializer serves no purpose and should be removed.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  static {
    // empty
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Empty Switch Statements {#PMD_ESS}
Empty switch statements serve no purpose and should be removed.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public void bar() {
  int x = 2;
  switch (x) {
    // once there was code here
    // but it's been commented out or something
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Empty Synchronized Block {#PMD_ESB}
Empty synchronized blocks serve no purpose and should be removed.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  public void bar() {
    synchronized (this) {
      // empty!
    }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Empty Try Block {#PMD_ETB}
Avoid empty try blocks - what's the point?

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  public void bar() {
    try {
    } catch (Exception e) {
      e.printStackTrace();
    }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Empty While Stmt {#PMD_EWS}
Empty While Statement finds all instances where a while statement does nothing. If it is a timing loop, then you should use Thread.sleep() for it; if it is a while loop that does a lot in the exit expression, rewrite it to make it clearer.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
void bar(int a, int b) {
  while (a == b) {
    // empty!
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Extends Object {#PMD_EO}
No need to explicitly extend Object.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo extends Object { // not required
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### For Loop Should Be While Loop {#PMD_FLSBWL}
Some for loops can be simplified while loops, this makes them more concise.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  void bar() {
    for (;true;) true; // No Init or Update part, may as well be: while (true)
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Jumbled Incrementer {#PMD_JI}
Avoid jumbled loop incrementers - it's usually a mistake, and is confusing even if intentional.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class JumbledIncrementerRule1 {
  public void foo() {
    for (int i = 0; i < 10; i++) {      // only references 'i'
      for (int k = 0; k < 20; i++) {    // references both 'i' and 'k'
        System.out.println("Hello");
      }
    }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Misplaced Null Check {#PMD_MNC}
The null check here is misplaced. If the variable is null a NullPointerException will be thrown. Either the check is useless (the variable will never be "null") or it is incorrect.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  void bar() {
    if (a.equals(baz) && a != null) {}
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  void bar() {
    if (a.equals(baz) || a == null) {}
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Override Both Equals And Hashcode {#PMD_OBEAH}
Override both public boolean Object.equals(Object other), and public int Object.hashCode(), or override neither. Even if you are inheriting a hashCode() from a parent class, consider implementing hashCode and explicitly delegating to your superclass.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Bar { // poor, missing a hashCode() method
  public boolean equals(Object o) {
    // do some comparison
  }
}

public class Baz { // poor, missing an equals() method
  public int hashCode() {
    // return some hash value
  }
}

public class Foo { // perfect, both methods provided
  public boolean equals(Object other) {
    // do some comparison
  }
  public int hashCode() {
    // return some hash value
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Return From Finally Block {#PMD_RFFB}
Avoid returning from a finally block, this can discard exceptions.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
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
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Unconditional If Statement {#PMD_UIS}
Do not use "if" statements whose conditionals are always true or always false.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  public void close() {
    if (true) { // fixed conditional, not recommended
      // ...
    }
  }
}

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Unnecessary Conversion Temporary {#PMD_UCT}
Avoid the use temporary objects when converting primitives to Strings. Use the static conversion methods on the wrapper classes instead.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public String convert(int x) {
  String foo = new Integer(x).toString(); // this wastes an object
  return Integer.toString(x);             // preferred approach
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Unused Null Check In Equals {#PMD_UNCIE}
After checking an object reference for null, you should invoke equals() on that object rather than passing it to another object's equals() method.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Test {
  public String method1() {
    return "ok";
  }
  
  public String method2() {
    return null;
  }
  
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
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Useless Operation On Immutable {#PMD_UOOI}
An operation on an Immutable object (String, BigDecimal or BigInteger) won't change the object itself since the result of the operation is a new object. Therefore, ignoring the operation result is an error.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
import java.math.*;

class Test {
  void method1() {
    BigDecimal bd=new BigDecimal(10);
    bd.add(new BigDecimal(5)); // this will trigger the rule
  }

  void method2() {
    BigDecimal bd=new BigDecimal(10);
    bd = bd.add(new BigDecimal(5)); // this won't trigger the rule
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Useless Overriding Method {#PMD_UOM}
The overriding method merely calls the same method defined in a superclass.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public void foo(String bar) {
  super.foo(bar); // why bother overriding?
}

public String foo() {
  return super.foo(); // why bother overriding?
}

@Id
public Long getId() {
  return super.getId(); // OK if 'ignoreAnnotations' is false, which is the default behavior
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### Brace Rules

#### For Loops Must Use Braces {#PMD_FLMUB}
Avoid using 'for' statements without using curly braces. If the code formatting or indentation is lost then it becomes difficult to separate the code being controlled from the rest.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
for (int i = 0; i < 42; i++)
  foo();
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### If Else Stmts Must Use Braces {#PMD_IESMUB}
Avoid using if..else statements without using surrounding braces. If the code formatting or indentation is lost then it becomes difficult to separate the code being controlled from the rest.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
// this is OK
if (foo) x++;
   
// but this is not
if (foo)
  x = x+1;
else
  x = x-1;
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### If Stmts Must Use Braces {#PMD_ISMUB}
Avoid using if statements without using braces to surround the code block. If the code formatting or indentation is lost then it becomes difficult to separate the code being controlled from the rest.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
if (foo) // not recommended
  x++;

if (foo) { // preferred approach
  x++;
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### While Loops Must Use Braces {#PMD_WLMUB}
Avoid using 'while' statements without using braces to surround the code block. If the code formatting or indentation is lost then it becomes difficult to separate the code being controlled from the rest.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
while (true) // not recommended
  x++;

while (true) { // preferred approach
  x++;
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### Clone Implementation Rules

#### Clone Throws Clone Not Supported Exception {#PMD_CTCNSE}
The method clone() should throw a CloneNotSupportedException.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class MyClass implements Cloneable {
  public Object clone() { // will cause an error
    MyClass clone = (MyClass)super.clone();
    return clone;
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Proper Clone Implementation {#PMD_PCI}
Object clone() should be implemented with super.clone().

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
class Foo {
  public Object clone() {
    return new Foo(); // This is bad
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### Controversial Rules

#### Assignment In Operand {#PMD_AIO}
Avoid assignments in operands; this can make code more complicated and harder to read.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public void bar() {
  int x = 2;
  if ((x = getX()) == 3) {
    System.out.println("3!");
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Avoid Accessibility Alteration {#PMD_AAA}
Methods such as getDeclaredConstructors(), getDeclaredConstructor(Class[]) and setAccessible(), as the interface PrivilegedAction, allows for the runtime alteration of variable, class, or method visibility, even if they are private. This violates the principle of encapsulation.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
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
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Avoid Prefixing Method Parameters {#PMD_APMP}
Prefixing parameters by 'in' or 'out' pollutes the name of the parameters and reduces code readability. To indicate whether or not a parameter will be modify in a method, its better to document method behavior with Javadoc.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
// Not really clear
public class Foo {
  public void bar(int inLeftOperand, Result outRightOperand) {
    outRightOperand.setValue(inLeftOperand * outRightOperand.getValue());
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
// Far more useful
public class Foo {
  /**
   *
   * @param leftOperand, (purpose), not modified by method.
   * @param rightOperand (purpose), will be modified by the method: contains the result.
   */
  public void bar(int leftOperand, Result rightOperand) {
    rightOperand.setValue(leftOperand * rightOperand.getValue());
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Avoid Using Native Code {#PMD_AUNC}
Unnecessary reliance on Java Native Interface (JNI) calls directly reduces application portability and increases the maintenance burden.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
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
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Default Package {#PMD_DP}
Use explicit scoping instead of the default package private level.

#### Do Not Call Garbage Collection Explicitly {#PMD_DNCGCE}
Calls to System.gc(), Runtime.getRuntime().gc(), and System.runFinalization() are not advised. Code should have the same behavior whether the garbage collection is disabled using the option -Xdisableexplicitgc or not. Moreover, "modern" jvms do a very good job handling garbage collections. If memory usage issues unrelated to memory leaks develop within an application, it should be dealt with JVM options rather than within the code itself.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
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
    // Explicit gc call ! System.gc(); 
  }

  public void doSomething() { 
    // Explicit gc call ! Runtime.getRuntime().gc(); 
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Dont Import Sun {#PMD_DIS}
Avoid importing anything from the 'sun.*' packages. These packages are not portable and are likely to change.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
import sun.misc.foo;

public class Foo {}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### One Declaration Per Line {#PMD_ODPL}
Java allows the use of several variables declaration of the same type on one line. However, it can lead to quite messy code. This rule looks for several declarations on the same line.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
String name;            // separate declarations
String lastname;

String name, lastname;  // combined declaration, a violation

String name,
       lastname;        // combined declaration on multiple lines, no violation by default.
                        // Set property strictMode to true to mark this as violation.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Suspicious Octal Escape {#PMD_SOE}
A suspicious octal escape sequence was found inside a String literal. The Java language specification (section 3.10.6) says an octal escape sequence inside a literal String shall consist of a backslash followed by: OctalDigit | OctalDigit OctalDigit | ZeroToThree OctalDigit OctalDigitAny octal escape sequence followed by non-octal digits can be confusing, e.g. "\\038" is interpreted as the octal escape sequence "\\03" followed by the literal character "8".

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public void foo() {
  // interpreted as octal 12, followed by character '8'
  System.out.println("suspicious: \128");
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Unnecessary Constructor {#PMD_UC}
This rule detects when a constructor is not necessary; i.e., when there is only one constructor, its public, has an empty body, and takes no arguments.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  public Foo() {}
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### Design Rules

#### Abstract Class Without Abstract Method {#PMD_ACWAM}
The abstract class does not contain any abstract methods. An abstract class suggests an incomplete implementation, which is to be completed by subclasses implementing the abstract methods. If the class is intended to be used as a base class only (not to be instantiated directly) a protected constructor can be provided prevent direct instantiation.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public abstract class Foo {
  void int method1() { /*...*/ }
  void int method2() { /*...*/ }
  // consider using abstract methods or removing
  // the abstract modifier and adding protected constructors
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Abstract Class Without Any Method {#PMD_AbCWAM}
If an abstract class does not provide any methods, it may be acting as a simple data container that is not meant to be instantiated. In this case, it is probably better to use a private or protected constructor in order to prevent instantiation than make the class misleadingly abstract.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class abstract Example {
  String field;
  int otherField;
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Assignment To Non Final Static {#PMD_ATNFS}
Identifies a possible unsafe usage of a static field.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class StaticField {
  static int x;

  public FinalFields(int y) {
    x = y; // unsafe
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Avoid Constants Interface {#PMD_ACI}
An interface should be used only to characterize the external behavior of an implementing class: using an interface as a container of constants is a poor usage pattern and not recommended.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public interface ConstantsInterface {
  public static final int CONSTANT1=0;
  public static final String CONSTANT2="1";
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Avoid Instanceof Checks In Catch Clause {#PMD_AICICC}
Each caught exception type should be handled in its own catch clause.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
try { // Avoid this
  // do something
} catch (Exception ee) {
  if (ee instanceof IOException) {
    cleanup();
  }
}

try { // Prefer this:
  // do something
} catch (IOException ee) {
  cleanup();
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Avoid Protected Field In Final Class {#PMD_APFIFC}
Do not use protected fields in final classes since they cannot be subclassed. Clarify your intent by using private or package access modifiers instead.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public final class Bar {
  private int x;
  protected int y;  // bar cannot be subclassed, so is y really private or package visible?

  Bar() {}
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Avoid Protected Method In Final Class Not Extending {#PMD_APMIFCNE}
Do not use protected methods in most final classes since they cannot be subclassed. This should only be allowed in final classes that extend other classes with protected methods (whose visibility cannot be reduced). Clarify your intent by using private or package access modifiers instead.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public final class Foo {
  private int bar() {}

  protected int baz() {} // Foo cannot be subclassed, and doesn't extend anything, 
                         // so is baz() really private or package visible? 
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Avoid Reassigning Parameters {#PMD_ARP}
Reassigning values to incoming parameters is not recommended. Use temporary local variables instead.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  private void foo(String bar) {
    bar = "something else";
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Avoid Synchronized At Method Level {#PMD_ASAML}
Method-level synchronization can cause problems when new code is added to the method. Block-level synchronization helps to ensure that only the code that needs synchronization gets it.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  // Try to avoid this:
  synchronized void foo() {
  }
  // Prefer this:
  void bar() {
    synchronized(this) {
    }
  }

  // Try to avoid this for static methods:
  static synchronized void fooStatic() {
  }
  
  // Prefer this:
  static void barStatic() {
    synchronized(Foo.class) {
    }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Bad Comparison {#PMD_BC}
Avoid equality comparisons with Double.NaN. Due to the implicit lack of representation precision when comparing floating point numbers these are likely to cause logic errors.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
boolean x = (y == Double.NaN);
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Class With Only Private Constructors Should Be Final {#PMD_CWOPCSBF}
A class with only private constructors should be final, unless the private constructor is invoked by an inner class.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {  //Should be final
  private Foo() {}
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Close Resource {#PMD_ClR}
Ensure that resources (like Connection, Statement, and ResultSet objects) are always closed after use.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Bar {
  public void foo() {
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
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Constructor Calls Overridable Method {#PMD_CCOM}
Calling overridable methods during construction poses a risk of invoking methods on an incompletely constructed object and can be difficult to debug. It may leave the sub-class unable to construct its superclass or forced to replicate the construction process completely within itself, losing the ability to call super(). If the default constructor contains a call to an overridable method, the subclass may be completely uninstantiable. Note that this includes method calls throughout the control flow graph - i.e., if a constructor Foo() calls a private method bar() that calls a public method buz(), this denotes a problem.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
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
  
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Default Label Not Last In Switch Stmt {#PMD_DLNLISS}
By convention, the default label should be the last label in a switch statement.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
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
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Empty Method In Abstract Class Should Be Abstract {#PMD_EMIACSBA}
Empty methods in an abstract class should be tagged as abstract. This helps to remove their inappropriate usage by developers who should be implementing their own versions in the concrete subclasses.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public abstract class ShouldBeAbstract {
  public Object couldBeAbstract() {
    // Should be abstract method ?
    return null;
  }

  public void couldBeAbstract() {
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Equals Null {#PMD_EN}
Tests for null should not use the equals() method. The '==' operator should be used instead.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
String x = "foo";

if (x.equals(null)) { // bad form
  doSomething();
}

if (x == null) { // preferred
  doSomething();
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Field Declarations Should Be At Start Of Class {#PMD_FDSBASOC}
Fields should be declared at the top of the class, before any method declarations, constructors, initializers or inner classes.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class HelloWorldBean {

  // Field declared before methods / inner classes - OK
  private String _thing;

  public String getMessage() {
    return "Hello World!";
  }

  // Field declared after methods / inner classes - avoid this
  private String _fieldInWrongLocation;
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Final Field Could Be Static {#PMD_FFCBS}
If a final field is assigned to a compile-time constant, it could be made static, thus saving overhead in each object at runtime.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  public final int BAR = 42; // this could be static and save some space
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Idempotent Operations {#PMD_IO}
Avoid idempotent operations - they have no effect.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  public void bar() {
    int x = 2;
    x = x;
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Immutable Field {#PMD_IF}
Identifies private fields whose values never change once they are initialized either in the declaration of the field or by a constructor. This helps in converting existing classes to becoming immutable ones.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  private int x; // could be final

  public Foo() {
    x = 7;
  }

  public void foo() {
    int a = x + 2;
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Instantiation To Get Class {#PMD_ITGC}
Avoid instantiating an object just to call getClass() on it; use the .class public member instead.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
// replace this
Class c = new String().getClass();

// with this:
Class c = String.class;
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Logic Inversion {#PMD_LI}
Use opposite operator instead of negating the whole expression with a logic complement operator.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public boolean bar(int a, int b) {
  if (!(a == b)) // use !=
    return false;
  if (!(a < b)) // use >=
    return false;
  return true;
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Missing Break In Switch {#PMD_MBIS}
Switch statements without break or return statements for each case option may indicate problematic behavior. Empty cases are ignored as these indicate an intentional fall-through.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
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
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Missing Static Method In Non Instantiatable Class {#PMD_MSMINIC}
A class that has private constructors and does not have any static methods or fields cannot be used.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
// This class is unusable, since it cannot be
// instantiated (private constructor),
// and no static method can be called.

public class Foo {
  private Foo() {}
  void foo() {}
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Non Case Label In Switch Statement {#PMD_NCLISS}
A non-case label (e.g. a named break/continue label) was present in a switch statement. This legal, but confusing. It is easy to mix up the case labels and the non-case labels.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
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
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Non Static Initializer {#PMD_NSI}
A non-static initializer block will be called any time a constructor is invoked (just prior to invoking the constructor). While this is a valid language construct, it is rarely used and is confusing.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class MyClass {
  // this block gets run before any call to a constructor
  {
    System.out.println("I am about to construct myself");
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Non Thread Safe Singleton {#PMD_NTSS}
Non-thread safe singletons can result in bad state changes. Eliminate static singletons if possible by instantiating the object directly. Static singletons are usually not needed as only a single instance exists anyway. Other possible fixes are to synchronize the entire method or to use an initialize-on-demand holder class (do not use the double-check idiom). See Effective Java, item 48.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
private static Foo foo = null;

//multiple simultaneous callers may see partially initialized objects
public static Foo getFoo() {
  if (foo==null)
    foo = new Foo();
  return foo;
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Optimizable To Array Call {#PMD_OTAC}
Calls to a collection's toArray() method should specify target arrays sized to match the size of the collection. Initial arrays that are too small are discarded in favour of new ones that have to be created that are the proper size.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
List foos = getFoos();

// inefficient, the array will be discarded
Foo[] fooArray = foos.toArray(new Foo[0]);
   
// much better; this one sizes the destination array, 
// avoiding of a new one via reflection
Foo[] fooArray = foos.toArray(new Foo[foos.size()]);
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Position Literals First In Case Insensitive Comparisons {#PMD_PLFICIC}
Position literals first in comparisons, if the second argument is null then NullPointerExceptions can be avoided, they will just return false.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
class Foo {
  boolean bar(String x) {
    return x.equalsIgnoreCase("2"); // should be "2".equalsIgnoreCase(x)
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Position Literals First In Comparisons {#PMD_PLFIC}
Position literals first in comparisons, if the second argument is null then NullPointerExceptions can be avoided, they will just return false.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
class Foo {
  boolean bar(String x) {
    return x.equals("2"); // should be "2".equals(x)
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Preserve Stack Trace {#PMD_PST}
Throwing a new exception from a catch block without passing the original exception into the new exception will cause the original stack trace to be lost making it difficult to debug effectively.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
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
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Return Empty Array Rather Than Null {#PMD_REARTN}
For any method that returns an array, it is a better to return an empty array rather than a null reference. This removes the need for null checking all results and avoids inadvertent NullPointerExceptions.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
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
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Simple Date Format Needs Locale {#PMD_SDFNL}
Be sure to specify a Locale when creating SimpleDateFormat instances to ensure that locale-appropriate formatting is used.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  // Should specify Locale.US (or whatever)
  private SimpleDateFormat sdf = new SimpleDateFormat("pattern");
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Simplify Boolean Expressions {#PMD_SBE}
Avoid unnecessary comparisons in boolean expressions, they serve no purpose and impacts readability.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Bar {
  // can be simplified to
  // bar = isFoo();
  private boolean bar = (isFoo() == true);

  public isFoo() { return false;}
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Simplify Boolean Returns {#PMD_SBR}
Avoid unnecessary if-then-else statements when returning a boolean. The result of the conditional test can be returned instead.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public boolean isBarEqualTo(int x) {
  if (bar == x) { // this bit of code...
    return true;
  } else {
    return false;
  }
}

public boolean isBarEqualTo(int x) {
    return bar == x; // can be replaced with this
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Simplify Conditional {#PMD_SC}
No need to check for null before an instanceof; the instanceof keyword returns false when given a null argument.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
class Foo {
  void bar(Object x) {
    if (x != null && x instanceof Bar) {
      // just drop the "x != null" check
    }
  }
}      
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Singular Field {#PMD_SF}
Fields whose scopes are limited to just single methods do not rely on the containing object to provide them to other methods. They may be better implemented as local variables within those methods.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  private int x;  // no reason to exist at the Foo instance level

  public void foo(int y) {
    x = y + 5;
    return x;
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Switch Stmts Should Have Default {#PMD_SSSHD}
All switch statements should include a default option to catch any unspecified values.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public void bar() {
  int x = 2;
  switch (x) {
    case 1: int j = 6;
    case 2: int j = 8;
    // missing default: here
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Too Few Branches For ASwitch Statement {#PMD_TFBFASS}
Switch statements are intended to be used to support complex branching behavior. Using a switch for only a few cases is ill-advised, since switches are not as easy to understand as if-then statements. In these cases use the if-then statement to increase code readability.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
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
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Uncommented Empty Constructor {#PMD_UEC}
Uncommented Empty Constructor finds instances where a constructor does not contain statements, but there is no comment. By explicitly commenting empty constructors it is easier to distinguish between intentional (commented) and unintentional empty constructors.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public Foo() {
  // This constructor is intentionally empty. Nothing special is needed here.
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Uncommented Empty Method {#PMD_UEM}
Uncommented Empty Method finds instances where a method does not contain statements, but there is no comment. By explicitly commenting empty methods it is easier to distinguish between intentional (commented) and unintentional empty methods.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public void doSomething() {
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Unnecessary Local Before Return {#PMD_ULBR}
Avoid the creation of unnecessary local variables.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  public int foo() {
    int x = doSomething();
    return x;  // instead, just 'return doSomething();'
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Unsynchronized Static Date Formatter {#PMD_USDF}
SimpleDateFormat instances are not synchronized. Sun recommends using separate format instances for each thread. If multiple threads must access a static formatter, the formatter must be synchronized either on method or block level.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  private static final SimpleDateFormat sdf = new SimpleDateFormat();

  void bar() {
    sdf.format(); // poor, no thread-safety
  }

  synchronized void foo() {
    sdf.format(); // preferred
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Use Collection Is Empty {#PMD_UCIE}
The isEmpty() method on java.util.Collection is provided to determine if a collection has any elements. Comparing the value of size() to 0 does not convey intent as well as the isEmpty() method.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
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
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Use Locale With Case Conversions {#PMD_ULWCC}
When doing String.toLowerCase()/toUpperCase() conversions, use Locales to avoids problems with languages that have unusual conventions, i.e. Turkish.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
class Foo {
  // BAD
  if (x.toLowerCase().equals("list"))
    // ...

  /*
  This will not match "LIST" when in Turkish locale
  The above could be
  if (x.toLowerCase(Locale.US).equals("list")) ...
  or simply
  if (x.equalsIgnoreCase("list")) ...
  */

  // GOOD
  String z = a.toLowerCase(Locale.EN);
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Use Notify All Instead Of Notify {#PMD_UNAION}
Thread.notify() awakens a thread monitoring the object. If more than one thread is monitoring, then only one is chosen. The thread chosen is arbitrary; thus its usually safer to call notifyAll() instead.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
  void bar() {
    x.notify();
    // If many threads are monitoring x, only one (and you won't know which) will be notified.
    // use instead:
    x.notifyAll();
  }
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Use Varargs {#PMD_UV}
Java 5 introduced the varargs parameter declaration for methods and constructors. This syntactic sugar provides flexibility for users of these methods and constructors, allowing them to avoid having to deal with the creation of an array.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  public void foo(String s, Object[] args) {
    // Do something here...
  }

  public void bar(String s, Object... args) {
    // Ahh, varargs tastes much better...
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### Finalizer Rules

#### Avoid Calling Finalize {#PMD_ACF}
The method Object.finalize() is called by the garbage collector on an object when garbage collection determines that there are no more references to the object. It should not be invoked by application logic.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
void foo() {
  Bar b = new Bar();
  b.finalize();
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Empty Finalizer {#PMD_EF}
Empty finalize methods serve no purpose and should be removed.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  protected void finalize() {}
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Finalize Does Not Call Super Finalize {#PMD_FDNCSF}
If the finalize() is implemented, its last action should be to call super.finalize.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
protected void finalize() {
  something();
  // neglected to call super.finalize()
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Finalize Only Calls Super Finalize {#PMD_FOCSF}
If the finalize() is implemented, it should do something besides just calling super.finalize().

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
protected void finalize() {
  super.finalize();
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Finalize Overloaded {#PMD_FO}
Methods named finalize() should not have parameters. It is confusing and most likely an attempt to overload Object.finalize(). It will not be called by the VM.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  // this is confusing and probably a bug
  protected void finalize(int a) {
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Finalize Should Be Protected {#PMD_FSBP}
When overriding the finalize(), the new method should be set as protected. If made public, other classes may invoke it at inappropriate times.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public void finalize() {
  // do something
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### Import Statement Rules

#### Dont Import Java Lang {#PMD_DIJL}
Avoid importing anything from the package 'java.lang'. These classes are automatically imported (JLS 7.5.3).

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
import java.lang.String;  // this is unnecessary

public class Foo {}       // --- in another source code file...

import java.lang.*;       // this is bad

public class Foo {}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Duplicate Imports {#PMD_DI}
Duplicate or overlapping import statements should be avoided.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
import java.lang.String;
import java.lang.*;

public class Foo {}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Import From Same Package {#PMD_IFSP}
There is no need to import a type that lives in the same package.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
 package foo;
 
 import foo.Buz; // no need for this
 import foo.*; // or this
 
 public class Bar{}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Too Many Static Imports {#PMD_TMSI}
If you overuse the static import feature, it can make your program unreadable and unmaintainable, polluting its namespace with all the static members you import. Readers of your code (including you, a few months after you wrote it) will not know which class a static member comes from (Sun 1.5 Language Guide).

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
import static Lennon;
import static Ringo;
import static George;
import static Paul;
import static Yoko; // Too much !
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Unnecessary Fully Qualified Name {#PMD_UFQN}
Import statements allow the use of non-fully qualified names. The use of a fully qualified name which is covered by an import statement is redundant. Consider using the non-fully qualified name.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
import java.util.List;

public class Foo {
  private java.util.List list1; // Unnecessary FQN
  private List list2;           // More appropriate given import of 'java.util.List'
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### J2EE Rules

#### Do Not Call System Exit {#PMD_DNCSE}
Web applications should not call System.exit(), since only the web container or the application server should stop the JVM. This rule also checks for the equivalent call Runtime.getRuntime().exit().

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public void bar() {
    System.exit(0); // never call this when running in an application server!
}
public void foo() {
    Runtime.getRuntime().exit(0); // never stop the JVM manually, the container will do this.
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Local Home Naming Convention {#PMD_LHNC}
The Local Home interface of a Session EJB should be suffixed by 'LocalHome'.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public interface MyBeautifulLocalHome extends javax.ejb.EJBLocalHome {} // proper name
public interface MissingProperSuffix extends javax.ejb.EJBLocalHome {} // non-standard name
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Local Interface Session Naming Convention {#PMD_LISNC}
The Local Interface of a Session EJB should be suffixed by 'Local'.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public interface MyLocal extends javax.ejb.EJBLocalObject {} // proper name
public interface MissingProperSuffix extends javax.ejb.EJBLocalObject {} // non-standard name
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### MDBAnd Session Bean Naming Convention {#PMD_MDBASBNC}
The EJB Specification states that any MessageDrivenBean or SessionBean should be suffixed by 'Bean'.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class SomeBean implements SessionBean{} // proper name
public class MissingTheProperSuffix implements SessionBean {} // non-standard name
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Remote Interface Naming Convention {#PMD_RINC}
Remote Interface of a Session EJB should not have a suffix.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
/* Poor Session suffix */
public interface BadSuffixSession extends javax.ejb.EJBObject {}

/* Poor EJB suffix */
public interface BadSuffixEJB extends javax.ejb.EJBObject {}

/* Poor Bean suffix */
public interface BadSuffixBean extends javax.ejb.EJBObject {}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Remote Session Interface Naming Convention {#PMD_RSINC}
A Remote Home interface type of a Session EJB should be suffixed by 'Home'.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public interface MyBeautifulHome extends javax.ejb.EJBHome {} // proper name
public interface MissingProperSuffix extends javax.ejb.EJBHome {} // non-standard name
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Static EJBField Should Be Final {#PMD_SEJBFSBF}
According to the J2EE specification, an EJB should not have any static fields with write access. However, static read-only fields are allowed. This ensures proper behavior especially when instances are distributed by the container on several JREs.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class SomeEJB extends EJBObject implements EJBLocalHome {
  private static int CountA; // poor, field can be edited
  private static final int CountB; // preferred, read-only access
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### JUnit Rules

#### JUnit Assertions Should Include Message {#PMD_JUASIM}
JUnit assertions should include an informative message - i.e., use the three-argument version of assertEquals(), not the two-argument version.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo extends TestCase {
  public void testSomething() {
    assertEquals("foo", "bar");
    // Use the form:
    // assertEquals("Foo does not equals bar", "foo", "bar");
    // instead
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### JUnit Spelling {#PMD_JUS}
Some JUnit framework methods are easy to misspell.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
import junit.framework.*;

public class Foo extends TestCase {
  public void setup() {} // oops, should be setUp
  public void TearDown() {} // oops, should be tearDown
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### JUnit Static Suite {#PMD_JUSS}
The suite() method in a JUnit test needs to be both public and static.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
import junit.framework.*;

public class Foo extends TestCase {
  public void suite() {}         // oops, should be static
  private static void suite() {} // oops, should be public
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### JUnit Test Contains Too Many Asserts {#PMD_JUTCTMA}
JUnit tests should not contain too many asserts. Many asserts are indicative of a complex test, for which it is harder to verify correctness. Consider breaking the test scenario into multiple, shorter test scenarios. Customize the maximum number of assertions used by this Rule to suit your needs.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
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
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### JUnit Tests Should Include Assert {#PMD_JUTSIA}
JUnit tests should include at least one assertion. This makes the tests more robust, and using assert with messages provide the developer a clearer idea of what the test does.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo extends TestCase {
  public void testSomething() {
    Bar b = findBar();
    // This is better than having a NullPointerException
    // assertNotNull("bar not found", b);
    b.work();
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Simplify Boolean Assertion {#PMD_SBA}
Avoid negation in an assertTrue or assertFalse test. For example, rephrase: assertTrue(!expr); as: assertFalse(expr);

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class SimpleTest extends TestCase {
  public void testX() {
    assertTrue("not empty", !r.isEmpty()); // replace with assertFalse("not empty", r.isEmpty())
    assertFalse(!r.isEmpty()); // replace with assertTrue(r.isEmpty())
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Test Class Without Test Cases {#PMD_TCWTC}
Test classes end with the suffix Test. Having a non-test class with that name is not a good practice, since most people will assume it is a test case. Test classes have test methods named testXXX.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
//Consider changing the name of the class if it is not a test
//Consider adding test methods if it is a test
public class CarTest {
  public static void main(String[] args) {
    // do something
  }
  // code
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Unnecessary Boolean Assertion {#PMD_UBA}
A JUnit test assertion with a boolean literal is unnecessary since it always will evaluate to the same thing. Consider using flow control (in case of assertTrue(false) or similar) or simply removing statements like assertTrue(true) and assertFalse(false). If you just want a test to halt after finding an error, use the fail() method and provide an indication message of why it did.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class SimpleTest extends TestCase {
  public void testX() {
    assertTrue(true);  // serves no real purpose
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Use Assert Equals Instead Of Assert True {#PMD_UAEIOAT}
This rule detects JUnit assertions in object equality. These assertions should be made by more specific methods, like assertEquals.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class FooTest extends TestCase {
  void testCode() {
    Object a, b;
    assertTrue(a.equals(b));                  // bad usage
    assertEquals(?a should equals b?, a, b);  // good usage
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Use Assert Null Instead Of Assert True {#PMD_UANIOAT}
This rule detects JUnit assertions in object references equality. These assertions should be made by more specific methods, like assertNull, assertNotNull.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class FooTest extends TestCase {
  void testCode() {
    Object a = doSomething();
    assertTrue(a==null);        // bad usage
    assertNull(a);              // good usage
    assertTrue(a != null);      // bad usage
    assertNotNull(a);           // good usage
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Use Assert Same Instead Of Assert True {#PMD_UASIOAT}
This rule detects JUnit assertions in object references equality. These assertions should be made by more specific methods, like assertSame, assertNotSame.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class FooTest extends TestCase {
  void testCode() {
    Object a, b;
    assertTrue(a == b); // bad usage
    assertSame(a, b);   // good usage
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Use Assert True Instead Of Assert Equals {#PMD_UATIOAE}
When asserting a value is the same as a boolean literal, use assertTrue/assertFalse, instead of assertEquals.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class MyTestCase extends TestCase {
  public void testMyCase() {
    boolean myVar = true;
    // Ok
    assertTrue("myVar is true", myVar);
    // Bad
    assertEquals("myVar is true", true, myVar);
    // Bad
    assertEquals("myVar is false", false, myVar);
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### Jakarta Commons Logging Rules

#### Guard Debug Logging {#PMD_GDL}
When log messages are composed by concatenating strings, the whole section should be guarded by a isDebugEnabled() check to avoid performance and memory issues.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Test {
  private static final Log __log = LogFactory.getLog(Test.class);
  public void test() {
    // okay:
    __log.debug("log something");

    // okay:
    __log.debug("log something with exception", e);

    // bad:
    __log.debug("log something" + " and " + "concat strings");

    // bad:
    __log.debug("log something" + " and " + "concat strings", e);

    // good:
    if (__log.isDebugEnabled()) {
      __log.debug("bla" + "",e );
    }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Guard Log Statement {#PMD_GLS}
Whenever using a log level, one should check if the loglevel is actually enabled, or otherwise skip the associate String creation and manipulation.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
// Add this for performance
if (log.isDebugEnabled() { 
  // ...
  log.debug("log something" + " and " + "concat strings");
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Proper Logger {#PMD_PL}
A logger should normally be defined private static final and be associated with the correct class. Private final Log log; is also allowed for rare cases where loggers need to be passed around, with the restriction that the logger needs to be passed into the constructor.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  private static final Log LOG = LogFactory.getLog(Foo.class);  // proper way
  protected Log LOG = LogFactory.getLog(Testclass.class);       // wrong approach
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Use Correct Exception Logging {#PMD_UCEL}
To make sure the full stacktrace is printed out, use the logging statement with two arguments: a String and a Throwable.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
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
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### Java Logging Rules

#### Avoid Print Stack Trace {#PMD_APST}
Avoid printStackTrace(); use a logger call instead.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
class Foo {
  void bar() {
    try {
      // do something
    } catch (Exception e) {
      e.printStackTrace();
    }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Guard Log Statement Java Util {#PMD_GLSJU}
Whenever using a log level, one should check if the loglevel is actually enabled, or otherwise skip the associate String creation and manipulation.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
// Add this for performance
if (log.isLoggable(Level.FINE)) {
  // ...
  log.fine("log something" + " and " + "concat strings");
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Logger Is Not Static Final {#PMD_LINSF}
In most cases, the Logger reference can be declared as static and final.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  Logger log = Logger.getLogger(Foo.class.getName());               // not recommended
  static final Logger log = Logger.getLogger(Foo.class.getName());  // preferred approach
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### More Than One Logger {#PMD_MTOL}
Normally only one logger is used in each class.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  Logger log = Logger.getLogger(Foo.class.getName());
  // It is very rare to see two loggers on a class, normally
  // log information is multiplexed by levels
  Logger log2= Logger.getLogger(Foo.class.getName());
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### System Println {#PMD_SP}
References to System.(out|err).print are usually intended for debugging purposes and can remain in the codebase even in production code. By using a logger one can enable/disable this behavior at will (and by priority) and avoid clogging the Standard out log.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
class Foo {
  Logger log = Logger.getLogger(Foo.class.getName());
  public void testA () {
    System.out.println("Entering test");
    // Better use this
    log.fine("Entering test");
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### JavaBean Rules

#### Missing Serial Version UID {#PMD_MSVUID}
Serializable classes should provide a serialVersionUID field.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo implements java.io.Serializable {
  String name;
  // Define serialization id to avoid serialization related bugs
  // i.e., public static final long serialVersionUID = 4328743;
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### Naming Rules

#### Avoid Dollar Signs {#PMD_ADS}
Avoid using dollar signs in variable/method/class/interface names.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Fo$o { // not a recommended name
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Avoid Field Name Matching Method Name {#PMD_AFNMMN}
It can be confusing to have a field name with the same name as a method. While this is permitted, having information (field) and actions (method) is not clear naming. Developers versed in Smalltalk often prefer this approach as the methods denote accessor methods.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  Object bar;
  // bar is data or an action or both?
  void bar() {
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Avoid Field Name Matching Type Name {#PMD_AFNMTN}
It is somewhat confusing to have a field name matching the declaring class name. This probably means that type and/or field names should be chosen more carefully.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo extends Bar {
  int foo; // There is probably a better name that can be used
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Boolean Get Method Name {#PMD_BGMN}
Methods that return boolean results should be named as predicate statements to denote this. I.e, 'isReady()', 'hasValues()', 'canCommit()', 'willFail()', etc. Avoid the use of the 'get' prefix for these methods.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public boolean getFoo();              // bad
public boolean isFoo();               // ok
public boolean getFoo(boolean bar);   // ok, unless checkParameterizedMethods=true
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Class Naming Conventions {#PMD_CNC}
Class names should always begin with an upper case character.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Generics Naming {#PMD_GN}
Names for references to generic values should be limited to a single uppercase letter.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
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
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Method Naming Conventions {#PMD_MeNC}
Method names should always begin with a lower case character, and should not contain underscores.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  public void fooStuff() {
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Method With Same Name As Enclosing Class {#PMD_MWSNAEC}
Non-constructor methods should not have the same name as the enclosing class.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class MyClass {
  public MyClass() {}         // this is OK because it is a constructor
  public void MyClass() {}    // this is bad because it is a method
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### No Package {#PMD_NP}
Detects when a class or interface does not have a package definition.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
// no package declaration
public class ClassInDefaultPackage {
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Package Case {#PMD_PC}
Detects when a package definition contains uppercase characters.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
package com.MyCompany;  // should be lowercase name

public class SomeClass {
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Short Class Name {#PMD_SCN}
Class names with fewer than five characters are not recommended.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Short Method Name {#PMD_SMN}
Method names that are very short are not helpful to the reader.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class ShortMethod {
  public void a( int i ) { // Violation
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Suspicious Constant Field Name {#PMD_SCFN}
Field names using all uppercase characters - Sun's Java naming conventions indicating constants - should be declared as final.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  // this is bad, since someone could accidentally
  // do PI = 2.71828; which is actually e
  // final double PI = 3.14; is ok
  double PI = 3.14;
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Suspicious Equals Method Name {#PMD_SEMN}
The method name and parameter number are suspiciously close to equals(Object), which can denote an intention to override the equals(Object) method.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
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
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Suspicious Hashcode Method Name {#PMD_SHMN}
The method name and return type are suspiciously close to hashCode(), which may denote an intention to override the hashCode() method.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  public int hashcode() { // oops, this probably was supposed to be 'hashCode'
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Variable Naming Conventions {#PMD_VNC}
A variable naming conventions rule - customize this to your liking. Currently, it checks for final variables that should be fully capitalized and non-final variables that should not include underscores.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  public static final int MY_NUM = 0;
  public String myTest = "";
  DataModule dmTest = new DataModule();
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### Optimization Rules

#### Add Empty String {#PMD_AES}
The conversion of literals to strings by concatenating them with empty strings is inefficient. It is much better to use one of the type-specific toString() methods instead.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
String s = "" + 123;                // inefficient 
String t = Integer.toString(456);   // preferred approach
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Avoid Array Loops {#PMD_AAL}
Instead of manually copying data between two arrays, use the efficient System.arraycopy method instead.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Test {
  public void bar() {
    int[] a = new int[10];
    int[] b = new int[10];
    for (int i=0;i<10;i++) {
      b[i]=a[i];
    }
  }
}

// this will trigger the rule
for (int i=0;i<10;i++) {
  b[i]=a[c[i]];
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Redundant Field Initializer {#PMD_RFI}
Java will initialize fields with known default values so any explicit initialization of those same defaults is redundant and results in a larger class file (approximately three additional bytecode instructions per field).

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class C {
  boolean b = false; // examples of redundant initializers
  byte by   = 0;
  short s   = 0;
  char c    = 0;
  int i     = 0;
  long l    = 0;
  float f   = .0f;    // all possible float literals
  double d  = 0d;     // all possible double literals
  Object o  = null;
  MyClass mca[] = null;
  int i1 = 0, ia1[] = null;
  class Nested {
    boolean b = false;
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Unnecessary Wrapper Object Creation {#PMD_UWOC}
Most wrapper classes provide static conversion methods that avoid the need to create intermediate objects just to create the primitive forms. Using these avoids the cost of creating objects that also need to be garbage-collected later.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public int convert(String s) {
  int i, i2;

  i = Integer.valueOf(s).intValue();            // this wastes an object
  i = Integer.parseInt(s);                      // this is better

  i2 = Integer.valueOf(i).intValue();           // this wastes an object
  i2 = i;                                       // this is better

  String s3 = Integer.valueOf(i2).toString();   // this wastes an object
  s3 = Integer.toString(i2);                    // this is better

  return i2;
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Use Array List Instead Of Vector {#PMD_UALIOV}
ArrayList is a much better Collection implementation than Vector if thread-safe operation is not required.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class SimpleTest extends TestCase {
  public void testX() {
    Collection c1 = new Vector();
    Collection c2 = new ArrayList();  // achieves the same with much better performance
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Use Arrays As List {#PMD_UAAL}
The java.util.Arrays class has an "asList" method that should be used when you want to create a new List from an array of objects. It is faster than executing a loop to copy all the elements of the array one by one.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Test {
  public void foo(Integer[] ints) {
    // could just use Arrays.asList(ints)
    List l= new ArrayList(10);
    for (int i=0; i< 100; i++) {
      l.add(ints[i]);
    }
    for (int i=0; i< 100; i++) {
      l.add(a[i].toString()); // won't trigger the rule
    }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Use String Buffer For String Appends {#PMD_USBFSA}
The use of the '+=' operator for appending strings causes the JVM to create and use an internal StringBuffer. If a non-trivial number of these concatenations are being used then the explicit use of a StringBuilder or threadsafe StringBuffer is recommended to avoid this.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  void bar() {
    String a;
    a = "foo";
    a += " bar";
    // better would be:
    // StringBuilder a = new StringBuilder("foo");
    // a.append(" bar);
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### Security Code Guideline Rules

#### Array Is Stored Directly {#PMD_AISD}
Constructors and methods receiving arrays should clone objects and store the copy. This prevents future changes from the user from affecting the original array.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  private String [] x;
  public void foo (String [] param) {
    // Don't do this, make a copy of the array at least
    this.x=param;
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Method Returns Internal Array {#PMD_MRIA}
Exposing internal arrays to the caller violates object encapsulation since elements can be removed or replaced outside of the object that owns it. It is safer to return a copy of the array.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class SecureSystem {
  UserData [] ud;
  public UserData [] getUserData() {
    // Don't return directly the internal array, return a copy
    return ud;
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### Strict Exception Rules

#### Avoid Catching Generic Exception {#PMD_ACGE}
Avoid catching generic exceptions such as NullPointerException, RuntimeException, Exception in try-catch block.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
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
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Avoid Catching NPE {#PMD_ACNPE}
Code should never throw NullPointerExceptions under normal circumstances. A catch block may hide the original error, causing other, more subtle problems later on.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}  
public class Foo {
  void bar() {
    try {
      // do something
    } catch (NullPointerException npe) {
    }
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Avoid Catching Throwable {#PMD_ACT}
Catching Throwable errors is not recommended since its scope is very broad. It includes runtime issues such as OutOfMemoryError that should be exposed and managed separately.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public void bar() {
  try {
    // do something
  } catch (Throwable th) { // should not catch Throwable
    th.printStackTrace();
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Avoid Losing Exception Information {#PMD_ALEI}
Statements in a catch block that invoke accessors on the exception without using the information only add to code size. Either remove the invocation, or use the return result.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public void bar() {
  try {
    // do something
  } catch (SomeException se) {
    se.getMessage();
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Avoid Rethrowing Exception {#PMD_ARE}
Catch blocks that merely rethrow a caught exception only add to code size and runtime complexity.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}  
public void bar() {
  try {
    // do something
  } catch (SomeException se) {
    throw se;
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Avoid Throwing New Instance Of Same Exception {#PMD_ATNIOSE}
Catch blocks that merely rethrow a caught exception wrapped inside a new instance of the same type only add to code size and runtime complexity.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}  
public void bar() {
  try {
    // do something
  } catch (SomeException se) {
    // harmless comment      
    throw new SomeException(se);
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Avoid Throwing Null Pointer Exception {#PMD_ATNPE}
Avoid throwing NullPointerExceptions. These are confusing because most people will assume that the virtual machine threw it. Consider using an IllegalArgumentException instead; this will be clearly seen as a programmer-initiated exception.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  void bar() {
    throw new NullPointerException();
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Avoid Throwing Raw Exception Types {#PMD_ATRET}
Avoid throwing certain exception types. Rather than throw a raw RuntimeException, Throwable, Exception, or Error, use a subclassed exception or error instead.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  public void bar() throws Exception {
    throw new Exception();
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Do Not Extend Java Lang Error {#PMD_DNEJLE}
Errors are system exceptions. Do not extend them.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo extends Error { }
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Do Not Throw Exception In Finally {#PMD_DNTEIF}
Throwing exceptions within a 'finally' block is confusing since they may mask other exceptions or code defects. Note: This is a PMD implementation of the Lint4j rule "A throw in a finally block"

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
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
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Exception As Flow Control {#PMD_EAFC}
Using Exceptions as form of flow control is not recommended as they obscure true exceptions when debugging. Either add the necessary validation or use an alternate control structure.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
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
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### String and StringBuffer Rules

#### Avoid Duplicate Literals {#PMD_ADL}
Code containing duplicate String literals can usually be improved by declaring the String as a constant field.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
private void bar() {
  buz("Howdy");
  buz("Howdy");
  buz("Howdy");
  buz("Howdy");
}
private void buz(String x) {}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Avoid String Buffer Field {#PMD_ASBF}
StringBuffers/StringBuilders can grow considerably, and so may become a source of memory leaks if held within objects with long lifetimes.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  private StringBuffer buffer;  // potential memory leak as an instance variable;
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Consecutive Appends Should Reuse {#PMD_CASR}
Consecutively calls to StringBuffer/StringBuilder .append should reuse the target object. This can improve the performance.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
String foo = " ";

StringBuffer buf = new StringBuffer();
buf.append("Hello"); // poor
buf.append(foo);
buf.append("World");

StringBuffer buf = new StringBuffer();
buf.append("Hello").append(foo).append("World"); // good
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Consecutive Literal Appends {#PMD_CLA}
Consecutively calling StringBuffer/StringBuilder.append with String literals

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
StringBuffer buf = new StringBuffer();
buf.append("Hello").append(" ").append("World"); // poor
buf.append("Hello World"); // good
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Inefficient String Buffering {#PMD_ISB}
Avoid concatenating non-literals in a StringBuffer constructor or append() since intermediate buffers will need to be created and destroyed by the JVM.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
// Avoid this, two buffers are actually being created here
StringBuffer sb = new StringBuffer("tmp = "+System.getProperty("java.io.tmpdir"));
    
// do this instead
StringBuffer sb = new StringBuffer("tmp = ");
sb.append(System.getProperty("java.io.tmpdir"));
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### String Buffer Instantiation With Char {#PMD_SBIWC}
Individual character values provided as initialization arguments will be converted into integers. This can lead to internal buffer sizes that are larger than expected.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
// misleading instantiation, these buffers
// are actually sized to 99 characters long
StringBuffer  sb1 = new StringBuffer('c');   
StringBuilder sb2 = new StringBuilder('c');

// in these forms, just single characters are allocated
StringBuffer  sb3 = new StringBuffer("c");
StringBuilder sb4 = new StringBuilder("c");
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### String Instantiation {#PMD_StI}
Avoid instantiating String objects; this is usually unnecessary since they are immutable and can be safely shared.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
private String bar = new String("bar"); // just do a String bar = "bar";
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### String To String {#PMD_STS}
Avoid calling toString() on objects already known to be string instances; this is unnecessary.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
private String baz() {
  String bar = "howdy";
  return bar.toString();
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Unnecessary Case Change {#PMD_UCC}
Using equalsIgnoreCase() is faster than using toUpperCase/toLowerCase().equals()

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
boolean answer1 = buz.toUpperCase().equals("baz");            // should be buz.equalsIgnoreCase("baz")
boolean answer2 = buz.toUpperCase().equalsIgnoreCase("baz");  // another unnecessary toUpperCase()
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Use Equals To Compare Strings {#PMD_UETCS}
Using '==' or '!=' to compare strings only works if intern version is used on both sides. Use the equals() method instead.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public boolean test(String s) {
  if (s == "one") return true;        // unreliable
  if ("two".equals(s)) return true;   // better
  return false;
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### Type Resolution Rules

#### Clone Method Must Implement Cloneable {#PMD_ClMMIC}
The method clone() should only be implemented if the class implements the Cloneable interface with the exception of a final method that only throws CloneNotSupportedException. This version uses PMD's type resolution facilities, and can detect if the class implements or extends a Cloneable class.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}

public class MyClass {
  public Object clone() throws CloneNotSupportedException {
    return foo;
  }
}

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Loose Coupling {#PMD_LoC}
Avoid using implementation types (i.e., HashSet); use the interface (i.e, Set) instead

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
import java.util.ArrayList;
import java.util.HashSet;

public class Bar {
  // Use List instead
  private ArrayList list = new ArrayList();
  // Use Set instead
  public HashSet getFoo() {
    return new HashSet();
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Signature Declare Throws Exception {#PMD_SiDTE}
It is unclear which exceptions that can be thrown from the methods. It might be difficult to document and understand the vague interfaces. Use either a class derived from RuntimeException or a checked exception. JUnit classes are excluded.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public void methodThrowingException() throws Exception {
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Unused Imports {#PMD_UnI}
Avoid unused import statements. This rule will find unused on demand imports, i.e. import com.foo.\*.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
import java.io.*; // not referenced or required

public class Foo {}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### Unnecessary and Unused Code Rules

#### Unused Local Variable {#PMD_ULV}
Detects when a local variable is declared and/or assigned, but not used.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Foo {
  public void doSomething() {
    int i = 5; // Unused
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Unused Private Field {#PMD_UPF}
Detects when a private field is declared and/or assigned a value, but not used.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Something {
  private static int FOO = 2; // Unused
  private int i = 5; // Unused
  private int j = 6;
  public int addOne() {
    return j++;
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Unused Private Method {#PMD_UPM}
Unused Private Method detects when a private method is declared but is unused.

Example(s):

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class Something {
  private void foo() {} // unused
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
