## Reference of Pylint 2.x coding rule violations

OpenStaticAnalyzer incorporates the [Pylint] tool for coding rule violation checking and imports its results. OpenStaticAnalyzer also associates the issued rule violations with source code elements (i.e. methods, functions, classes, packages, and modules), and calculates metrics for the source code elements, which represent the amount of violations of each ruleset, rule, and priority groups, respectively.

OpenStaticAnalyzer uses Pylint "as is", without any guaranties that the results of Pylint are correct. All statements of the Pylint license apply here as well. All texts describing the rulesets and the individual rules are copied from Pylint with some minor grammatical fixes.
The list of rulesets and rules contained in each ruleset are the following:

- **Async Rules:** Async Rules

- **Basic Rules:** Basic Rules

- **Class Rules:** Class Rules

- **Design Rules:** Design Rules

- **Exception Rules:** Exception Rules

- **Format Rules:** Format Rules

- **Import Rules:** Import Rules

- **Logging Rules:** Logging Rules

- **Miscellaneous Rules:** Miscellaneous Rules

- **Newstyle Rules:** Newstyle Rules

- **Python3 Rules:** Python3 Rules

- **Refactoring Rules:** Refactoring Rules

- **Spelling Rules:** Spelling Rules

- **Stdlib Rules:** Stdlib Rules

- **String Rules:** String Rules

- **Typecheck Rules:** Typecheck Rules

- **Variable Rules:** Variable Rules

The following table contains the enabled rules and their priorities:

  Category             Name                                  Abbreviation  Prio.    
  -------------------- ------------------------------------- ------------- ---------
  Async Rules          Not Async Context Manager             PYLINT_NACM   Critical 
                       Yield Inside Async Function           PYLINT_YIAF   Critical 
  Basic Rules          Abstract Class Instantiated           PYLINT_ACI    Critical 
                       Assert On Tuple                       PYLINT_AOT    Major    
                       Assign To New Keyword                 PYLINT_ATNK   Major    
                       Bad Reversed Sequence                 PYLINT_BRS    Critical 
                       Blacklisted Name                      PYLINT_BN     Minor    
                       Comparison With Callable              PYLINT_CWC    Major    
                       Comparison With Itself                PYLINT_CWI    Minor    
                       Confusing With Statement              PYLINT_CWS    Major    
                       Continue In Finally                   PYLINT_CIF    Critical 
                       Dangerous Default Value               PYLINT_DDV    Major    
                       Duplicate Argument Name               PYLINT_DAN    Critical 
                       Duplicate Key                         PYLINT_DK     Major    
                       Empty Docstring                       PYLINT_ED     Minor    
                       Eval Used                             PYLINT_EU     Major    
                       Exec Used                             PYLINT_ExU    Major    
                       Expression Not Assigned               PYLINT_ENA    Major    
                       Function Redefined                    PYLINT_FR     Critical 
                       Init Is Generator                     PYLINT_IIG    Critical 
                       Invalid Name                          PYLINT_IN     Minor    
                       Invalid Star Assignment Target        PYLINT_ISAT   Critical 
                       Literal Comparison                    PYLINT_LC     Minor    
                       Lost Exception                        PYLINT_LoE    Major    
                       Misplaced Comparison Constant         PYLINT_MCC    Minor    
                       Misplaced Format Function             PYLINT_MFF    Critical 
                       Missing Docstring                     PYLINT_MD     Minor    
                       Nonexistent Operator                  PYLINT_NO     Critical 
                       Nonlocal And Global                   PYLINT_NAG    Critical 
                       Nonlocal Without Binding              PYLINT_NWB    Critical 
                       Not In Loop                           PYLINT_NIL    Critical 
                       Pointless Statement                   PYLINT_PS     Major    
                       Pointless String Statement            PYLINT_PSS    Major    
                       Return Arg In Generator               PYLINT_RAIG   Critical 
                       Return In Init                        PYLINT_RII    Critical 
                       Return Outside Function               PYLINT_ROF    Critical 
                       Singleton Comparison                  PYLINT_SC     Minor    
                       Star Needs Assignment Target          PYLINT_SNAT   Critical 
                       Too Many Star Expressions             PYLINT_TMSE   Critical 
                       Unidiomatic Typecheck                 PYLINT_UT     Minor    
                       Unnecessary Lambda                    PYLINT_UL     Major    
                       Unnecessary Pass                      PYLINT_UP     Major    
                       Unreachable                           PYLINT_U      Major    
                       Used Prior Global Declaration         PYLINT_UPGD   Critical 
                       Useless Else On Loop                  PYLINT_UEOL   Major    
                       Using Constant Test                   PYLINT_UCT    Major    
                       Yield Outside Function                PYLINT_YOF    Critical 
  Class Rules          Abstract Method                       PYLINT_AM     Major    
                       Access Member Before Definition       PYLINT_AMBD   Critical 
                       Arguments Differ                      PYLINT_AD     Major    
                       Assigning Non Slot                    PYLINT_ANS    Critical 
                       Attribute Defined Outside Init        PYLINT_ADOI   Major    
                       Bad Classmethod Argument              PYLINT_BCA    Minor    
                       Bad Mcs Classmethod Argument          PYLINT_BMCA   Minor    
                       Bad Mcs Method Argument               PYLINT_BMMA   Minor    
                       Bad Staticmethod Argument             PYLINT_BSA    Major    
                       Duplicate Bases                       PYLINT_DB     Critical 
                       Inconsistent Mro                      PYLINT_IM     Critical 
                       Inherit Non Class                     PYLINT_INC    Critical 
                       Invalid Length Returned               PYLINT_ILR    Critical 
                       Invalid Slots                         PYLINT_InS    Critical 
                       Invalid Slots Object                  PYLINT_ISO    Critical 
                       Method Hidden                         PYLINT_MH     Critical 
                       No Classmethod Decorator              PYLINT_NCD    Minor    
                       No Init                               PYLINT_NI     Major    
                       No Method Argument                    PYLINT_NMA    Critical 
                       No Self Argument                      PYLINT_NSA    Critical 
                       No Self Use                           PYLINT_NSU    Minor    
                       No Staticmethod Decorator             PYLINT_NSD    Minor    
                       Non Iterator Returned                 PYLINT_NIR    Critical 
                       Non Parent Init Called                PYLINT_NPIC   Major    
                       Protected Access                      PYLINT_PA     Major    
                       Signature Differs                     PYLINT_SD     Major    
                       Single String Used For Slots          PYLINT_SSUFS  Minor    
                       Super Init Not Called                 PYLINT_SINC   Major    
                       Unexpected Special Method Signature   PYLINT_USMS   Critical 
                       Useless Object Inheritance            PYLINT_UOI    Minor    
                       Useless Super Delegation              PYLINT_USD    Major    
  Design Rules         Too Few Public Methods                PYLINT_TFPM   Minor    
                       Too Many Ancestors                    PYLINT_TMA    Minor    
                       Too Many Arguments                    PYLINT_ToMA   Minor    
                       Too Many Boolean Expressions          PYLINT_TMBE   Minor    
                       Too Many Branches                     PYLINT_TMB    Minor    
                       Too Many Instance Attributes          PYLINT_TMIA   Minor    
                       Too Many Locals                       PYLINT_ToML   Minor    
                       Too Many Public Methods               PYLINT_TMPM   Minor    
                       Too Many Return Statements            PYLINT_TMRS   Minor    
                       Too Many Statements                   PYLINT_TMS    Minor    
  Exception Rules      Bad Except Order                      PYLINT_BEO    Critical 
                       Bad Exception Context                 PYLINT_BEC    Critical 
                       Bare Except                           PYLINT_BE     Major    
                       Binary Op Exception                   PYLINT_BOE    Major    
                       Broad Except                          PYLINT_BrE    Major    
                       Catching Non Exception                PYLINT_CNE    Critical 
                       Duplicate Except                      PYLINT_DE     Major    
                       Misplaced Bare Raise                  PYLINT_MBR    Critical 
                       Notimplemented Raised                 PYLINT_NR     Critical 
                       Raising Bad Type                      PYLINT_RBT    Critical 
                       Raising Format Tuple                  PYLINT_RFT    Major    
                       Raising Non Exception                 PYLINT_RNE    Critical 
                       Try Except Raise                      PYLINT_TER    Major    
                       Wrong Exception Operation             PYLINT_WEO    Major    
  Format Rules         Bad Continuation                      PYLINT_BC     Minor    
                       Bad Indentation                       PYLINT_BI     Major    
                       Bad Whitespace                        PYLINT_BW     Minor    
                       Line Too Long                         PYLINT_LTL    Minor    
                       Missing Final Newline                 PYLINT_MFN    Minor    
                       Mixed Indentation                     PYLINT_MI     Major    
                       Mixed Line Endings                    PYLINT_MLE    Minor    
                       Multiple Statements                   PYLINT_MS     Minor    
                       Superfluous Parens                    PYLINT_SP     Minor    
                       Too Many Lines                        PYLINT_TML    Minor    
                       Trailing Newlines                     PYLINT_TN     Minor    
                       Trailing Whitespace                   PYLINT_TW     Minor    
                       Unexpected Line Ending Format         PYLINT_ULEF   Minor    
                       Unnecessary Semicolon                 PYLINT_US     Major    
  Import Rules         Cyclic Import                         PYLINT_CI     Minor    
                       Deprecated Module                     PYLINT_DeM    Major    
                       Import Self                           PYLINT_IS     Major    
                       Misplaced Future                      PYLINT_MF     Major    
                       Multiple Imports                      PYLINT_MuI    Minor    
                       Reimported                            PYLINT_R      Major    
                       Relative Beyond Top Level             PYLINT_RBTL   Critical 
                       Relative Import                       PYLINT_RI     Major    
                       Ungrouped Imports                     PYLINT_UngI   Minor    
                       Useless Import Alias                  PYLINT_UIA    Minor    
                       Wildcard Import                       PYLINT_WI     Major    
                       Wrong Import Order                    PYLINT_WIO    Minor    
                       Wrong Import Position                 PYLINT_WIP    Minor    
  Logging Rules        Logging Format Interpolation          PYLINT_LFI    Major    
                       Logging Format Truncated              PYLINT_LFT    Critical 
                       Logging Fstring Interpolation         PYLINT_LoFI   Major    
                       Logging Not Lazy                      PYLINT_LNL    Major    
                       Logging Too Few Args                  PYLINT_LTFA   Critical 
                       Logging Too Many Args                 PYLINT_LTMA   Critical 
                       Logging Unsupported Format            PYLINT_LUF    Critical 
  Miscellaneous Rules  Fixme                                 PYLINT_Fi     Major    
                       Invalid Encoded Data                  PYLINT_IED    Major    
                       Use Symbolic Message Instead          PYLINT_USMI   Minor    
  Newstyle Rules       Bad Super Call                        PYLINT_BSC    Critical 
                       Missing Super Argument                PYLINT_MSA    Critical 
  Python3 Rules        Apply Builtin                         PYLINT_AB     Major    
                       Backtick                              PYLINT_B      Critical 
                       Bad Python3 Import                    PYLINT_BP3I   Major    
                       Basestring Builtin                    PYLINT_BaB    Major    
                       Buffer Builtin                        PYLINT_BuB    Major    
                       Cmp Builtin                           PYLINT_CB     Major    
                       Cmp Method                            PYLINT_CM     Major    
                       Coerce Builtin                        PYLINT_CoB    Major    
                       Coerce Method                         PYLINT_CoM    Major    
                       Comprehension Escape                  PYLINT_CE     Major    
                       Delslice Method                       PYLINT_DM     Major    
                       Deprecated Itertools Function         PYLINT_DIF    Major    
                       Deprecated Operator Function          PYLINT_DOF    Major    
                       Deprecated Str Translate Call         PYLINT_DSTC   Major    
                       Deprecated String Function            PYLINT_DSF    Major    
                       Deprecated Sys Function               PYLINT_DeSF   Major    
                       Deprecated Types Field                PYLINT_DTF    Major    
                       Deprecated Urllib Function            PYLINT_DUF    Major    
                       Dict Items Not Iterating              PYLINT_DINI   Major    
                       Dict Iter Method                      PYLINT_DIM    Major    
                       Dict Keys Not Iterating               PYLINT_DKNI   Major    
                       Dict Values Not Iterating             PYLINT_DVNI   Major    
                       Dict View Method                      PYLINT_DVM    Major    
                       Div Method                            PYLINT_DiM    Major    
                       Eq Without Hash                       PYLINT_EWH    Major    
                       Exception Escape                      PYLINT_EE     Major    
                       Exception Message Attribute           PYLINT_EMA    Major    
                       Execfile Builtin                      PYLINT_EB     Major    
                       File Builtin                          PYLINT_FB     Major    
                       Filter Builtin Not Iterating          PYLINT_FBNI   Major    
                       Getslice Method                       PYLINT_GM     Major    
                       Hex Method                            PYLINT_HM     Major    
                       Idiv Method                           PYLINT_IdM    Major    
                       Import Star Module Level              PYLINT_ISML   Critical 
                       Indexing Exception                    PYLINT_InE    Major    
                       Input Builtin                         PYLINT_IB     Major    
                       Intern Builtin                        PYLINT_InB    Major    
                       Invalid Str Codec                     PYLINT_ISC    Major    
                       Long Builtin                          PYLINT_LB     Major    
                       Long Suffix                           PYLINT_LS     Critical 
                       Map Builtin Not Iterating             PYLINT_MBNI   Major    
                       Metaclass Assignment                  PYLINT_MA     Major    
                       Next Method Called                    PYLINT_NMC    Major    
                       Next Method Defined                   PYLINT_NMD    Major    
                       No Absolute Import                    PYLINT_NAI    Major    
                       Non Ascii Bytes Literal               PYLINT_NABL   Critical 
                       Nonzero Method                        PYLINT_NoM    Major    
                       Oct Method                            PYLINT_OM     Major    
                       Old Division                          PYLINT_OD     Major    
                       Old Ne Operator                       PYLINT_ONO    Critical 
                       Old Octal Literal                     PYLINT_OOL    Critical 
                       Old Raise Syntax                      PYLINT_ORS    Critical 
                       Parameter Unpacking                   PYLINT_PU     Critical 
                       Print Statement                       PYLINT_PrS    Critical 
                       Raising String                        PYLINT_RS     Major    
                       Range Builtin Not Iterating           PYLINT_RBNI   Major    
                       Raw_input Builtin                     PYLINT_RB     Major    
                       Rdiv Method                           PYLINT_RM     Major    
                       Reduce Builtin                        PYLINT_RedB   Major    
                       Reload Builtin                        PYLINT_RelB   Major    
                       Round Builtin                         PYLINT_RoB    Major    
                       Setslice Method                       PYLINT_SM     Major    
                       Standarderror Builtin                 PYLINT_SB     Major    
                       Sys Max Int                           PYLINT_SMI    Major    
                       Unichr Builtin                        PYLINT_UnB    Major    
                       Unicode Builtin                       PYLINT_UB     Major    
                       Unpacking In Except                   PYLINT_UIE    Critical 
                       Using Cmp Argument                    PYLINT_UCA    Major    
                       Xrange Builtin                        PYLINT_XB     Major    
                       Xreadlines Attribute                  PYLINT_XA     Major    
                       Zip Builtin Not Iterating             PYLINT_ZBNI   Major    
  Refactoring Rules    Chained Comparison                    PYLINT_CC     Minor    
                       Consider Iterating Dictionary         PYLINT_CID    Minor    
                       Consider Merging Isinstance           PYLINT_CMI    Minor    
                       Consider Swap Variables               PYLINT_CSV    Minor    
                       Consider Using Dict Comprehension     PYLINT_CUDC   Minor    
                       Consider Using Enumerate              PYLINT_CUE    Minor    
                       Consider Using Get                    PYLINT_CUG    Minor    
                       Consider Using In                     PYLINT_CUI    Minor    
                       Consider Using Join                   PYLINT_CUJ    Minor    
                       Consider Using Set Comprehension      PYLINT_CUSC   Minor    
                       Consider Using Ternary                PYLINT_CUT    Minor    
                       Inconsistent Return Statements        PYLINT_IRS    Minor    
                       Len As Condition                      PYLINT_LAC    Minor    
                       No Else Raise                         PYLINT_NoER   Minor    
                       No Else Return                        PYLINT_NER    Minor    
                       Redefined Argument From Local         PYLINT_RAFL   Minor    
                       Simplifiable If Expression            PYLINT_SIE    Minor    
                       Simplifiable If Statement             PYLINT_SIS    Minor    
                       Simplify Boolean Expression           PYLINT_SBE    Minor    
                       Stop Iteration Return                 PYLINT_SIR    Minor    
                       Too Many Nested Blocks                PYLINT_TMNB   Minor    
                       Trailing Comma Tuple                  PYLINT_TCT    Minor    
                       Unneeded Not                          PYLINT_UN     Minor    
                       Useless Return                        PYLINT_UR     Minor    
  Spelling Rules       Invalid Characters In Docstring       PYLINT_ICID   Minor    
                       Wrong Spelling In Comment             PYLINT_WSIC   Minor    
                       Wrong Spelling In Docstring           PYLINT_WSID   Minor    
  Stdlib Rules         Bad Open Mode                         PYLINT_BOM    Major    
                       Bad Thread Instantiation              PYLINT_BTI    Major    
                       Boolean Datetime                      PYLINT_BD     Major    
                       Deprecated Method                     PYLINT_DepM   Major    
                       Invalid Envvar Default                PYLINT_InED   Major    
                       Invalid Envvar Value                  PYLINT_IEV    Critical 
                       Redundant Unittest Assert             PYLINT_RUA    Major    
                       Shallow Copy Environ                  PYLINT_SCE    Major    
                       Subprocess Popen Preexec Fn           PYLINT_SPPF   Major    
  String Rules         Anomalous Backslash In String         PYLINT_ABIS   Major    
                       Anomalous Unicode Escape In String    PYLINT_AUEIS  Major    
                       Bad Format Character                  PYLINT_BFC    Critical 
                       Bad Format String                     PYLINT_BFS    Major    
                       Bad Format String Key                 PYLINT_BFSK   Major    
                       Bad Str Strip Call                    PYLINT_BSSC   Critical 
                       Bad String Format Type                PYLINT_BSFT   Critical 
                       Duplicate String Formatting Argument  PYLINT_DSFA   Major    
                       Format Combined Specification         PYLINT_FCS    Major    
                       Format Needs Mapping                  PYLINT_FNM    Critical 
                       Implicit Str Concat In Sequence       PYLINT_ISCIS  Major    
                       Invalid Format Index                  PYLINT_IFI    Major    
                       Missing Format Argument Key           PYLINT_MFAK   Major    
                       Missing Format Attribute              PYLINT_MFA    Major    
                       Missing Format String Key             PYLINT_MFSK   Critical 
                       Mixed Format String                   PYLINT_MFS    Critical 
                       Too Few Format Args                   PYLINT_TFFA   Critical 
                       Too Many Format Args                  PYLINT_TMFA   Critical 
                       Truncated Format String               PYLINT_TFS    Critical 
                       Unused Format String Argument         PYLINT_UFSA   Major    
                       Unused Format String Key              PYLINT_UFSK   Major    
  Typecheck Rules      Assignment From No Return             PYLINT_AFNR   Critical 
                       Assignment From None                  PYLINT_AFN    Critical 
                       C Extension No Member                 PYLINT_CENM   Minor    
                       Invalid Metaclass                     PYLINT_InM    Critical 
                       Invalid Sequence Index                PYLINT_ISI    Critical 
                       Invalid Slice Index                   PYLINT_InSI   Critical 
                       Invalid Unary Operand Type            PYLINT_IUOT   Critical 
                       Keyword Arg Before Vararg             PYLINT_KABV   Major    
                       Missing Kwoa                          PYLINT_MK     Critical 
                       No Member                             PYLINT_NM     Critical 
                       No Value For Parameter                PYLINT_NVFP   Critical 
                       Not A Mapping                         PYLINT_NAM    Critical 
                       Not An Iterable                       PYLINT_NoAI   Critical 
                       Not Callable                          PYLINT_NC     Critical 
                       Not Context Manager                   PYLINT_NCM    Critical 
                       Redundant Keyword Arg                 PYLINT_RKA    Critical 
                       Repeated Keyword                      PYLINT_RK     Critical 
                       Too Many Function Args                PYLINT_ToMFA  Critical 
                       Unexpected Keyword Arg                PYLINT_UKA    Critical 
                       Unhashable Dict Key                   PYLINT_UDK    Critical 
                       Unsubscriptable Object                PYLINT_UO     Critical 
                       Unsupported Assignment Operation      PYLINT_UAO    Critical 
                       Unsupported Binary Operation          PYLINT_UBO    Critical 
                       Unsupported Delete Operation          PYLINT_UDO    Critical 
                       Unsupported Membership Test           PYLINT_UMT    Critical 
  Variable Rules       Cell Var From Loop                    PYLINT_CVFL   Major    
                       Global At Module Level                PYLINT_GAML   Major    
                       Global Statement                      PYLINT_GS     Major    
                       Global Variable Not Assigned          PYLINT_GVNA   Major    
                       Global Variable Undefined             PYLINT_GVU    Major    
                       Invalid All Object                    PYLINT_IAO    Critical 
                       No Name In Module                     PYLINT_NNIM   Critical 
                       Possibly Unused Variable              PYLINT_PUV    Major    
                       Redefine In Handler                   PYLINT_RIH    Major    
                       Redefined Builtin                     PYLINT_ReB    Major    
                       Redefined Outer Name                  PYLINT_RON    Major    
                       Self Cls Assignment                   PYLINT_SCA    Major    
                       Unbalanced Tuple Unpacking            PYLINT_UTU    Major    
                       Undefined All Variable                PYLINT_UAV    Critical 
                       Undefined Loop Variable               PYLINT_ULV    Major    
                       Undefined Variable                    PYLINT_UV     Critical 
                       Unpacking Non Sequence                PYLINT_UNS    Critical 
                       Unused Argument                       PYLINT_UA     Major    
                       Unused Import                         PYLINT_UnI    Major    
                       Unused Variable                       PYLINT_UnV    Major    
                       Unused Wildcard Import                PYLINT_UWI    Major    
                       Used Before Assignment                PYLINT_UBA    Critical 

### Async Rules

#### Not Async Context Manager {#PYLINT_NACM}
Used when an async context manager is used with an object that does not implement the async context management protocol. This message can't be emitted when using Python \< 3.5.

#### Yield Inside Async Function {#PYLINT_YIAF}
Used when an `yield` or `yield from` statement is found inside an async function. This message can't be emitted when using Python \< 3.5.

### Basic Rules

#### Abstract Class Instantiated {#PYLINT_ACI}
Used when an abstract class with `abc.ABCMeta` as metaclass has abstract methods and is instantiated.

#### Assert On Tuple {#PYLINT_AOT}
A call of assert on a tuple will always evaluate to true if the tuple is not empty, and will always evaluate to false if it is.

#### Assign To New Keyword {#PYLINT_ATNK}
Used when assignment will become invalid in future Python release due to introducing new keyword.

#### Bad Reversed Sequence {#PYLINT_BRS}
Used when the first argument to reversed() builtin isn't a sequence (does not implement \_\_reversed\_\_, nor \_\_getitem\_\_ and \_\_len\_\_.

#### Blacklisted Name {#PYLINT_BN}
Used when the name is listed in the black list (unauthorized names).

#### Comparison With Callable {#PYLINT_CWC}
This message is emitted when pylint detects that a comparison with a callable was made, which might suggest that some parenthesis were omitted, resulting in potential unwanted behaviour.

#### Comparison With Itself {#PYLINT_CWI}
Used when something is compared against itself.

#### Confusing With Statement {#PYLINT_CWS}
Emitted when a `with` statement component returns multiple values and uses name binding with `as` only for a part of those values, as in with ctx() as a, b. This can be misleading, since it's not clear if the context manager returns a tuple or if the node without a name binding is another context manager.

#### Continue In Finally {#PYLINT_CIF}
Emitted when the `continue` keyword is found inside a finally clause, which is a SyntaxError.

#### Dangerous Default Value {#PYLINT_DDV}
Used when a mutable value as list or dictionary is detected in a default value for an argument.

#### Duplicate Argument Name {#PYLINT_DAN}
Duplicate argument names in function definitions are syntax errors.

#### Duplicate Key {#PYLINT_DK}
Used when a dictionary expression binds the same key multiple times.

#### Empty Docstring {#PYLINT_ED}
Used when a module, function, class or method has an empty docstring (it would be too easy ;).

#### Eval Used {#PYLINT_EU}
Used when you use the "eval" function, to discourage its usage. Consider using `ast.literal_eval` for safely evaluating strings containing Python expressions from untrusted sources.

#### Exec Used {#PYLINT_ExU}
Used when you use the "exec" statement (function for Python 3), to discourage its usage. That doesn't mean you cannot use it!

#### Expression Not Assigned {#PYLINT_ENA}
Used when an expression that is not a function call is assigned to nothing. Probably something else was intended.

#### Function Redefined {#PYLINT_FR}
Used when a function / class / method is redefined.

#### Init Is Generator {#PYLINT_IIG}
Used when the special class method \_\_init\_\_ is turned into a generator by a yield in its body.

#### Invalid Name {#PYLINT_IN}
Used when the name doesn't conform to naming rules associated to its type (constant, variable, class...).

#### Invalid Star Assignment Target {#PYLINT_ISAT}
Emitted when a star expression is used as a starred assignment target.

#### Literal Comparison {#PYLINT_LC}
Used when comparing an object to a literal, which is usually what you do not want to do, since you can compare to a different literal than what was expected altogether.

#### Lost Exception {#PYLINT_LoE}
Used when a break or a return statement is found inside the finally clause of a try...finally block: the exceptions raised in the try clause will be silently swallowed instead of being re-raised.

#### Misplaced Comparison Constant {#PYLINT_MCC}
Used when the constant is placed on the left side of a comparison. It is usually clearer in intent to place it in the right hand side of the comparison.

#### Misplaced Format Function {#PYLINT_MFF}
Emitted when format function is not called on str object. e.g doing print("value: \{\}").format(123) instead of print("value: \{\}".format(123)). This might not be what the user intended to do.

#### Missing Docstring {#PYLINT_MD}
Used when a module, function, class or method has no docstring.Some special methods like \_\_init\_\_ doesn't necessary require a docstring.

#### Nonexistent Operator {#PYLINT_NO}
Used when you attempt to use the C-style pre-increment or pre-decrement operator \-\- and ++, which doesn't exist in Python.

#### Nonlocal And Global {#PYLINT_NAG}
Emitted when a name is both nonlocal and global.

#### Nonlocal Without Binding {#PYLINT_NWB}
Emitted when a nonlocal variable does not have an attached name somewhere in the parent scopes.

#### Not In Loop {#PYLINT_NIL}
Used when break or continue keywords are used outside a loop.

#### Pointless Statement {#PYLINT_PS}
Used when a statement doesn't have (or at least seems to) any effect.

#### Pointless String Statement {#PYLINT_PSS}
Used when a string is used as a statement (which of course has no effect). This is a particular case of W0104 with its own message so you can easily disable it if you're using those strings as documentation, instead of comments.

#### Return Arg In Generator {#PYLINT_RAIG}
Used when a "return" statement with an argument is found outside in a generator function or method (e.g. with some "yield" statements). This message can't be emitted when using Python >= 3.3.

#### Return In Init {#PYLINT_RII}
Used when the special class method \_\_init\_\_ has an explicit return value.

#### Return Outside Function {#PYLINT_ROF}
Used when a "return" statement is found outside a function or method.

#### Singleton Comparison {#PYLINT_SC}
Used when an expression is compared to singleton values like True, False or None.

#### Star Needs Assignment Target {#PYLINT_SNAT}
Emitted when a star expression is not used in an assignment target.

#### Too Many Star Expressions {#PYLINT_TMSE}
Emitted when there are more than one starred expressions (`*x`) in an assignment. This is a SyntaxError.

#### Unidiomatic Typecheck {#PYLINT_UT}
The idiomatic way to perform an explicit typecheck in Python is to use isinstance(x, Y) rather than type(x) == Y, type(x) is Y. Though there are unusual situations where these give different results.

#### Unnecessary Lambda {#PYLINT_UL}
Used when the body of a lambda expression is a function call on the same argument list as the lambda itself; such lambda expressions are in all but a few cases replaceable with the function being called in the body of the lambda.

#### Unnecessary Pass {#PYLINT_UP}
Used when a "pass" statement that can be avoided is encountered.

#### Unreachable {#PYLINT_U}
Used when there is some code behind a "return" or "raise" statement, which will never be accessed.

#### Used Prior Global Declaration {#PYLINT_UPGD}
Emitted when a name is used prior a global declaration, which results in an error since Python 3.6. This message can't be emitted when using Python \< 3.6.

#### Useless Else On Loop {#PYLINT_UEOL}
Loops should only have an else clause if they can exit early with a break statement, otherwise the statements under else should be on the same scope as the loop itself.

#### Using Constant Test {#PYLINT_UCT}
Emitted when a conditional statement (If or ternary if) uses a constant value for its test. This might not be what the user intended to do.

#### Yield Outside Function {#PYLINT_YOF}
Used when a "yield" statement is found outside a function or method.

### Class Rules

#### Abstract Method {#PYLINT_AM}
Used when an abstract method (i.e. raise NotImplementedError) is not overridden in concrete class.

#### Access Member Before Definition {#PYLINT_AMBD}
Used when an instance member is accessed before it's actually assigned.

#### Arguments Differ {#PYLINT_AD}
Used when a method has a different number of arguments than in the implemented interface or in an overridden method.

#### Assigning Non Slot {#PYLINT_ANS}
Used when assigning to an attribute not defined in the class slots.

#### Attribute Defined Outside Init {#PYLINT_ADOI}
Used when an instance attribute is defined outside the \_\_init\_\_ method.

#### Bad Classmethod Argument {#PYLINT_BCA}
Used when a class method has a first argument named differently than the value specified in valid-classmethod-first-arg option (default to "cls"), recommended to easily differentiate them from regular instance methods.

#### Bad Mcs Classmethod Argument {#PYLINT_BMCA}
Used when a metaclass class method has a first argument named differently than the value specified in valid-metaclass-classmethod-first-arg option (default to "mcs"), recommended to easily differentiate them from regular instance methods.

#### Bad Mcs Method Argument {#PYLINT_BMMA}
Used when a metaclass method has a first argument named differently than the value specified in valid-classmethod-first-arg option (default to "cls"), recommended to easily differentiate them from regular instance methods.

#### Bad Staticmethod Argument {#PYLINT_BSA}
Used when a static method has "self" or a value specified in valid-classmethod-first-arg option or valid-metaclass-classmethod-first-arg option as first argument.

#### Duplicate Bases {#PYLINT_DB}
Used when a class has duplicate bases.

#### Inconsistent Mro {#PYLINT_IM}
Used when a class has an inconsistent method resolution order.

#### Inherit Non Class {#PYLINT_INC}
Used when a class inherits from something which is not a class.

#### Invalid Length Returned {#PYLINT_ILR}
Used when a \_\_len\_\_ method returns something which is not a non-negative integer.

#### Invalid Slots {#PYLINT_InS}
Used when an invalid \_\_slots\_\_ is found in class. Only a string, an iterable or a sequence is permitted.

#### Invalid Slots Object {#PYLINT_ISO}
Used when an invalid (non-string) object occurs in \_\_slots\_\_.

#### Method Hidden {#PYLINT_MH}
Used when a class defines a method which is hidden by an instance attribute from an ancestor class or set by some client code.

#### No Classmethod Decorator {#PYLINT_NCD}
Used when a class method is defined without using the decorator syntax.

#### No Init {#PYLINT_NI}
Used when a class has no \_\_init\_\_ method, neither its parent classes.

#### No Method Argument {#PYLINT_NMA}
Used when a method which should have the bound instance as first argument has no argument defined.

#### No Self Argument {#PYLINT_NSA}
Used when a method has an attribute different the "self" as first argument. This is considered as an error since this is a so common convention that you shouldn't break it!

#### No Self Use {#PYLINT_NSU}
Used when a method doesn't use its bound instance, and so could be written as a function.

#### No Staticmethod Decorator {#PYLINT_NSD}
Used when a static method is defined without using the decorator syntax.

#### Non Iterator Returned {#PYLINT_NIR}
Used when an \_\_iter\_\_ method returns something which is not an iterable (i.e. has no `__next__` method).

#### Non Parent Init Called {#PYLINT_NPIC}
Used when an \_\_init\_\_ method is called on a class which is not in the direct ancestors for the analysed class.

#### Protected Access {#PYLINT_PA}
Used when a protected member (i.e. class member with a name beginning with an underscore) is access outside the class or a descendant of the class where it's defined.

#### Signature Differs {#PYLINT_SD}
Used when a method signature is different than in the implemented interface or in an overridden method.

#### Single String Used For Slots {#PYLINT_SSUFS}
Used when a class \_\_slots\_\_ is a simple string, rather than an iterable.

#### Super Init Not Called {#PYLINT_SINC}
Used when an ancestor class method has an \_\_init\_\_ method which is not called by a derived class.

#### Unexpected Special Method Signature {#PYLINT_USMS}
Emitted when a special method was defined with an invalid number of parameters. If it has too few or too many, it might not work at all.

#### Useless Object Inheritance {#PYLINT_UOI}
Used when a class inherit from object, which under python3 is implicit, hence can be safely removed from bases.

#### Useless Super Delegation {#PYLINT_USD}
Used whenever we can detect that an overridden method is useless, relying on super() delegation to do the same thing as another method from the MRO.

### Design Rules

#### Too Few Public Methods {#PYLINT_TFPM}
Used when class has too few public methods, so be sure it's really worth it.

#### Too Many Ancestors {#PYLINT_TMA}
Used when class has too many parent classes, try to reduce this to get a simpler (and so easier to use) class.

#### Too Many Arguments {#PYLINT_ToMA}
Used when a function or method takes too many arguments.

#### Too Many Boolean Expressions {#PYLINT_TMBE}
Used when an if statement contains too many boolean expressions.

#### Too Many Branches {#PYLINT_TMB}
Used when a function or method has too many branches, making it hard to follow.

#### Too Many Instance Attributes {#PYLINT_TMIA}
Used when class has too many instance attributes, try to reduce this to get a simpler (and so easier to use) class.

#### Too Many Locals {#PYLINT_ToML}
Used when a function or method has too many local variables.

#### Too Many Public Methods {#PYLINT_TMPM}
Used when class has too many public methods, try to reduce this to get a simpler (and so easier to use) class.

#### Too Many Return Statements {#PYLINT_TMRS}
Used when a function or method has too many return statement, making it hard to follow.

#### Too Many Statements {#PYLINT_TMS}
Used when a function or method has too many statements. You should then split it in smaller functions / methods.

### Exception Rules

#### Bad Except Order {#PYLINT_BEO}
Used when except clauses are not in the correct order (from the more specific to the more generic). If you don't fix the order, some exceptions may not be caught by the most specific handler.

#### Bad Exception Context {#PYLINT_BEC}
Used when using the syntax "raise ... from ...", where the exception context is not an exception, nor None.

#### Bare Except {#PYLINT_BE}
Used when an except clause doesn't specify exceptions type to catch.

#### Binary Op Exception {#PYLINT_BOE}
Used when the exception to catch is of the form "except A or B:". If intending to catch multiple, rewrite as "except (A, B):".

#### Broad Except {#PYLINT_BrE}
Used when an except catches a too general exception, possibly burying unrelated errors.

#### Catching Non Exception {#PYLINT_CNE}
Used when a class which doesn't inherit from Exception is used as an exception in an except clause.

#### Duplicate Except {#PYLINT_DE}
Used when an except catches a type that was already caught by a previous handler.

#### Misplaced Bare Raise {#PYLINT_MBR}
Used when a bare raise is not used inside an except clause. This generates an error, since there are no active exceptions to be reraised. An exception to this rule is represented by a bare raise inside a finally clause, which might work, as long as an exception is raised inside the try block, but it is nevertheless a code smell that must not be relied upon.

#### Notimplemented Raised {#PYLINT_NR}
Used when NotImplemented is raised instead of NotImplementedError.

#### Raising Bad Type {#PYLINT_RBT}
Used when something which is neither a class, an instance or a string is raised (i.e. a `TypeError` will be raised).

#### Raising Format Tuple {#PYLINT_RFT}
Used when passing multiple arguments to an exception constructor, the first of them a string literal containing what appears to be placeholders intended for formatting.

#### Raising Non Exception {#PYLINT_RNE}
Used when a new style class which doesn't inherit from BaseException is raised.

#### Try Except Raise {#PYLINT_TER}
Used when an except handler uses raise as its first or only operator. This is useless because it raises back the exception immediately. Remove the raise operator or the entire try-except-raise block!

#### Wrong Exception Operation {#PYLINT_WEO}
Used when an operation is done against an exception, but the operation is not valid for the exception in question. Usually emitted when having binary operations between exceptions in except handlers.

### Format Rules

#### Bad Continuation {#PYLINT_BC}
TODO

#### Bad Indentation {#PYLINT_BI}
Used when an unexpected number of indentation's tabulations or spaces has been found.

#### Bad Whitespace {#PYLINT_BW}
Used when a wrong number of spaces is used around an operator, bracket or block opener.

#### Line Too Long {#PYLINT_LTL}
Used when a line is longer than a given number of characters.

#### Missing Final Newline {#PYLINT_MFN}
Used when the last line in a file is missing a newline.

#### Mixed Indentation {#PYLINT_MI}
Used when there are some mixed tabs and spaces in a module.

#### Mixed Line Endings {#PYLINT_MLE}
Used when there are mixed (LF and CRLF) newline signs in a file.

#### Multiple Statements {#PYLINT_MS}
Used when more than on statement are found on the same line.

#### Superfluous Parens {#PYLINT_SP}
Used when a single item in parentheses follows an if, for, or other keyword.

#### Too Many Lines {#PYLINT_TML}
Used when a module has too many lines, reducing its readability.

#### Trailing Newlines {#PYLINT_TN}
Used when there are trailing blank lines in a file.

#### Trailing Whitespace {#PYLINT_TW}
Used when there is whitespace between the end of a line and the newline.

#### Unexpected Line Ending Format {#PYLINT_ULEF}
Used when there is different newline than expected.

#### Unnecessary Semicolon {#PYLINT_US}
Used when a statement is ended by a semi-colon (";"), which isn't necessary (that's python, not C ;).

### Import Rules

#### Cyclic Import {#PYLINT_CI}
Used when a cyclic import between two or more modules is detected.

#### Deprecated Module {#PYLINT_DeM}
Used a module marked as deprecated is imported.

#### Import Self {#PYLINT_IS}
Used when a module is importing itself.

#### Misplaced Future {#PYLINT_MF}
Python 2.5 and greater require \_\_future\_\_ import to be the first non docstring statement in the module.

#### Multiple Imports {#PYLINT_MuI}
Used when import statement importing multiple modules is detected.

#### Reimported {#PYLINT_R}
Used when a module is reimported multiple times.

#### Relative Beyond Top Level {#PYLINT_RBTL}
Used when a relative import tries to access too many levels in the current package.

#### Relative Import {#PYLINT_RI}
Used when an import relative to the package directory is detected. This message can't be emitted when using Python >= 3.0.

#### Ungrouped Imports {#PYLINT_UngI}
Used when imports are not grouped by packages.

#### Useless Import Alias {#PYLINT_UIA}
Used when an import alias is same as original package.e.g using import numpy as numpy instead of import numpy as np.

#### Wildcard Import {#PYLINT_WI}
Used when `from module import *` is detected.

#### Wrong Import Order {#PYLINT_WIO}
Used when PEP8 import order is not respected (standard imports first, then third-party libraries, then local imports).

#### Wrong Import Position {#PYLINT_WIP}
Used when code and imports are mixed.

### Logging Rules

#### Logging Format Interpolation {#PYLINT_LFI}
Used when a logging statement has a call form of "logging.\<logging method>(format\_string.format(format\_args...))". Such calls should use % formatting instead, but leave interpolation to the logging function by passing the parameters as arguments.

#### Logging Format Truncated {#PYLINT_LFT}
Used when a logging statement format string terminates before the end of a conversion specifier.

#### Logging Fstring Interpolation {#PYLINT_LoFI}
Used when a logging statement has a call form of "logging.method(f"..."))". Such calls should use % formatting instead, but leave interpolation to the logging function by passing the parameters as arguments.

#### Logging Not Lazy {#PYLINT_LNL}
Used when a logging statement has a call form of "logging.\<logging method>(format\_string % (format\_args...))". Such calls should leave string interpolation to the logging method itself and be written "logging.\<logging method>(format\_string, format\_args...)" so that the program may avoid incurring the cost of the interpolation in those cases in which no message will be logged. For more, see <http://www.python.org/dev/peps/pep-0282/>.

#### Logging Too Few Args {#PYLINT_LTFA}
Used when a logging format string is given too few arguments.

#### Logging Too Many Args {#PYLINT_LTMA}
Used when a logging format string is given too many arguments.

#### Logging Unsupported Format {#PYLINT_LUF}
Used when an unsupported format character is used in a logging statement format string.

### Miscellaneous Rules

#### Fixme {#PYLINT_Fi}
Used when a warning note as FIXME or XXX is detected.

#### Invalid Encoded Data {#PYLINT_IED}
Used when a source line cannot be decoded using the specified source file encoding. This message can't be emitted when using Python >= 3.0.

#### Use Symbolic Message Instead {#PYLINT_USMI}
Used when a message is enabled or disabled by id.

### Newstyle Rules

#### Bad Super Call {#PYLINT_BSC}
Used when another argument than the current class is given as first argument of the super builtin.

#### Missing Super Argument {#PYLINT_MSA}
Used when the super builtin didn't receive an argument. This message can't be emitted when using Python >= 3.0.

### Python3 Rules

#### Apply Builtin {#PYLINT_AB}
Used when the apply built-in function is referenced (missing from Python 3).

#### Backtick {#PYLINT_B}
Used when the deprecated "``" (backtick) operator is used instead of the str() function.

#### Bad Python3 Import {#PYLINT_BP3I}
Used when importing a module that no longer exists in Python 3.

#### Basestring Builtin {#PYLINT_BaB}
Used when the basestring built-in function is referenced (missing from Python 3).

#### Buffer Builtin {#PYLINT_BuB}
Used when the buffer built-in function is referenced (missing from Python 3).

#### Cmp Builtin {#PYLINT_CB}
Used when the cmp built-in function is referenced (missing from Python 3).

#### Cmp Method {#PYLINT_CM}
Used when a \_\_cmp\_\_ method is defined (method is not used by Python 3).

#### Coerce Builtin {#PYLINT_CoB}
Used when the coerce built-in function is referenced (missing from Python 3).

#### Coerce Method {#PYLINT_CoM}
Used when a \_\_coerce\_\_ method is defined (method is not used by Python 3).

#### Comprehension Escape {#PYLINT_CE}
Emitted when using a variable, that was bound in a comprehension handler, outside of the comprehension itself. On Python 3 these variables will be deleted outside of the comprehension.

#### Delslice Method {#PYLINT_DM}
Used when a \_\_delslice\_\_ method is defined (method is not used by Python 3).

#### Deprecated Itertools Function {#PYLINT_DIF}
Used when accessing a function on itertools that has been removed in Python 3.

#### Deprecated Operator Function {#PYLINT_DOF}
Used when accessing a field on operator module that has been removed in Python 3.

#### Deprecated Str Translate Call {#PYLINT_DSTC}
Used when using the deprecated deletechars parameters from str.translate. Use re.sub to remove the desired characters.

#### Deprecated String Function {#PYLINT_DSF}
Used when accessing a string function that has been deprecated in Python 3.

#### Deprecated Sys Function {#PYLINT_DeSF}
Used when accessing a field on sys module that has been removed in Python 3.

#### Deprecated Types Field {#PYLINT_DTF}
Used when accessing a field on types that has been removed in Python 3.

#### Deprecated Urllib Function {#PYLINT_DUF}
Used when accessing a field on urllib module that has been removed or moved in Python 3.

#### Dict Items Not Iterating {#PYLINT_DINI}
Used when dict.items is referenced in a non-iterating context (returns an iterator in Python 3).

#### Dict Iter Method {#PYLINT_DIM}
Used for calls to dict.iterkeys(), itervalues() or iteritems() (Python 3 lacks these methods).

#### Dict Keys Not Iterating {#PYLINT_DKNI}
Used when dict.keys is referenced in a non-iterating context (returns an iterator in Python 3).

#### Dict Values Not Iterating {#PYLINT_DVNI}
Used when dict.values is referenced in a non-iterating context (returns an iterator in Python 3).

#### Dict View Method {#PYLINT_DVM}
Used for calls to dict.viewkeys(), viewvalues() or viewitems() (Python 3 lacks these methods).

#### Div Method {#PYLINT_DiM}
Used when a \_\_div\_\_ method is defined. Using `__truediv__` and setting\_\_div\_\_ = \_\_truediv\_\_ should be preferred.(method is not used by Python 3).

#### Eq Without Hash {#PYLINT_EWH}
Used when a class implements \_\_eq\_\_ but not \_\_hash\_\_. In Python 2, objects get object.\_\_hash\_\_ as the default implementation, in Python 3 objects get None as their default \_\_hash\_\_ implementation if they also implement \_\_eq\_\_.

#### Exception Escape {#PYLINT_EE}
Emitted when using an exception, that was bound in an except handler, outside of the except handler. On Python 3 these exceptions will be deleted once they get out of the except handler.

#### Exception Message Attribute {#PYLINT_EMA}
Used when the message attribute is accessed on an Exception. Use str(exception) instead.

#### Execfile Builtin {#PYLINT_EB}
Used when the execfile built-in function is referenced (missing from Python 3).

#### File Builtin {#PYLINT_FB}
Used when the file built-in function is referenced (missing from Python 3).

#### Filter Builtin Not Iterating {#PYLINT_FBNI}
Used when the filter built-in is referenced in a non-iterating context (returns an iterator in Python 3).

#### Getslice Method {#PYLINT_GM}
Used when a \_\_getslice\_\_ method is defined (method is not used by Python 3).

#### Hex Method {#PYLINT_HM}
Used when a \_\_hex\_\_ method is defined (method is not used by Python 3).

#### Idiv Method {#PYLINT_IdM}
Used when an \_\_idiv\_\_ method is defined. Using `__itruediv__` and setting\_\_idiv\_\_ = \_\_itruediv\_\_ should be preferred.(method is not used by Python 3).

#### Import Star Module Level {#PYLINT_ISML}
Used when the import star syntax is used somewhere else than the module level. This message can't be emitted when using Python >= 3.0.

#### Indexing Exception {#PYLINT_InE}
Indexing exceptions will not work on Python 3. Use `exception.args[index]` instead.

#### Input Builtin {#PYLINT_IB}
Used when the input built-in is referenced (backwards-incompatible semantics in Python 3).

#### Intern Builtin {#PYLINT_InB}
Used when the intern built-in is referenced (Moved to sys.intern in Python 3).

#### Invalid Str Codec {#PYLINT_ISC}
Used when using str.encode or str.decode with a non-text encoding. Use codecs module to handle arbitrary codecs.

#### Long Builtin {#PYLINT_LB}
Used when the long built-in function is referenced (missing from Python 3).

#### Long Suffix {#PYLINT_LS}
Used when "l" or "L" is used to mark a long integer. This will not work in Python 3, since `int` and `long` types have merged. This message can't be emitted when using Python >= 3.0.

#### Map Builtin Not Iterating {#PYLINT_MBNI}
Used when the map built-in is referenced in a non-iterating context (returns an iterator in Python 3).

#### Metaclass Assignment {#PYLINT_MA}
Used when a metaclass is specified by assigning to \_\_metaclass\_\_ (Python 3 specifies the metaclass as a class statement argument).

#### Next Method Called {#PYLINT_NMC}
Used when an object's next() method is called (Python 3 uses the next() built-in function).

#### Next Method Defined {#PYLINT_NMD}
Used when a next method is defined that would be an iterator in Python 2 but is treated as a normal function in Python 3.

#### No Absolute Import {#PYLINT_NAI}
Used when an import is not accompanied by ``from __future__ import absolute_import`` (default behaviour in Python 3).

#### Non Ascii Bytes Literal {#PYLINT_NABL}
Used when non-ascii bytes literals are found in a program. They are no longer supported in Python 3. This message can't be emitted when using Python >= 3.0.

#### Nonzero Method {#PYLINT_NoM}
Used when a \_\_nonzero\_\_ method is defined (method is not used by Python 3).

#### Oct Method {#PYLINT_OM}
Used when an \_\_oct\_\_ method is defined (method is not used by Python 3).

#### Old Division {#PYLINT_OD}
Used for non-floor division w/o a float literal or ``from __future__ import division`` (Python 3 returns a float for int division unconditionally).

#### Old Ne Operator {#PYLINT_ONO}
Used when the deprecated "\<>" operator is used instead of "!=". This is removed in Python 3. This message can't be emitted when using Python >= 3.0.

#### Old Octal Literal {#PYLINT_OOL}
Used when encountering the old octal syntax, removed in Python 3. To use the new syntax, prepend 0o on the number. This message can't be emitted when using Python >= 3.0.

#### Old Raise Syntax {#PYLINT_ORS}
Used when the alternate raise syntax 'raise foo, bar' is used instead of 'raise foo(bar)'.

#### Parameter Unpacking {#PYLINT_PU}
Used when parameter unpacking is specified for a function(Python 3 doesn't allow it).

#### Print Statement {#PYLINT_PrS}
Used when a print statement is used (`print` is a function in Python 3).

#### Raising String {#PYLINT_RS}
Used when a string exception is raised. This will not work on Python 3.

#### Range Builtin Not Iterating {#PYLINT_RBNI}
Used when the range built-in is referenced in a non-iterating context (returns an iterator in Python 3).

#### Raw_input Builtin {#PYLINT_RB}
Used when the raw\_input built-in function is referenced (missing from Python 3).

#### Rdiv Method {#PYLINT_RM}
Used when a \_\_rdiv\_\_ method is defined. Using `__rtruediv__` and setting\_\_rdiv\_\_ = \_\_rtruediv\_\_ should be preferred.(method is not used by Python 3).

#### Reduce Builtin {#PYLINT_RedB}
Used when the reduce built-in function is referenced (missing from Python 3).

#### Reload Builtin {#PYLINT_RelB}
Used when the reload built-in function is referenced (missing from Python 3). You can use instead imp.reload or importlib.reload.

#### Round Builtin {#PYLINT_RoB}
Used when the round built-in is referenced (backwards-incompatible semantics in Python 3).

#### Setslice Method {#PYLINT_SM}
Used when a \_\_setslice\_\_ method is defined (method is not used by Python 3).

#### Standarderror Builtin {#PYLINT_SB}
Used when the StandardError built-in function is referenced (missing from Python 3).

#### Sys Max Int {#PYLINT_SMI}
Used when accessing sys.maxint. Use sys.maxsize instead.

#### Unichr Builtin {#PYLINT_UnB}
Used when the unichr built-in is referenced (Use chr in Python 3).

#### Unicode Builtin {#PYLINT_UB}
Used when the unicode built-in function is referenced (missing from Python 3).

#### Unpacking In Except {#PYLINT_UIE}
Python3 will not allow implicit unpacking of exceptions in except clauses. See <http://www.python.org/dev/peps/pep-3110/>.

#### Using Cmp Argument {#PYLINT_UCA}
Using the cmp argument for list.sort or the sorted builtin should be avoided, since it was removed in Python 3. Using either `key` or `functools.cmp_to_key` should be preferred.

#### Xrange Builtin {#PYLINT_XB}
Used when the xrange built-in function is referenced (missing from Python 3).

#### Xreadlines Attribute {#PYLINT_XA}
Used when accessing the xreadlines() function on a file stream, removed in Python 3.

#### Zip Builtin Not Iterating {#PYLINT_ZBNI}
Used when the zip built-in is referenced in a non-iterating context (returns an iterator in Python 3).

### Refactoring Rules

#### Chained Comparison {#PYLINT_CC}
This message is emitted when pylint encounters boolean operation like"a \< b and b \< c", suggesting instead to refactor it to "a \< b \< c".

#### Consider Iterating Dictionary {#PYLINT_CID}
Emitted when the keys of a dictionary are iterated through the .keys() method. It is enough to just iterate through the dictionary itself, as in "for key in dictionary".

#### Consider Merging Isinstance {#PYLINT_CMI}
Used when multiple consecutive isinstance calls can be merged into one.

#### Consider Swap Variables {#PYLINT_CSV}
You do not have to use a temporary variable in order to swap variables. Using "tuple unpacking" to directly swap variables makes the intention more clear.

#### Consider Using Dict Comprehension {#PYLINT_CUDC}
Although there is nothing syntactically wrong with this code, it is hard to read and can be simplified to a dict comprehension.Also it is faster since you don't need to create another transient list.

#### Consider Using Enumerate {#PYLINT_CUE}
Emitted when code that iterates with range and len is encountered. Such code can be simplified by using the enumerate builtin.

#### Consider Using Get {#PYLINT_CUG}
Using the builtin dict.get for getting a value from a dictionary if a key is present or a default if not, is simpler and considered more idiomatic, although sometimes a bit slower.

#### Consider Using In {#PYLINT_CUI}
To check if a variable is equal to one of many values,combine the values into a tuple and check if the variable is contained "in" it instead of checking for equality against each of the values.This is faster and less verbose.

#### Consider Using Join {#PYLINT_CUJ}
Using str.join(sequence) is faster, uses less memory and increases readability compared to for-loop iteration.

#### Consider Using Set Comprehension {#PYLINT_CUSC}
Although there is nothing syntactically wrong with this code, it is hard to read and can be simplified to a set comprehension.Also it is faster since you don't need to create another transient list.

#### Consider Using Ternary {#PYLINT_CUT}
Used when one of known pre-python 2.5 ternary syntax is used.

#### Inconsistent Return Statements {#PYLINT_IRS}
According to PEP8, if any return statement returns an expression, any return statements where no value is returned should explicitly state this as return None, and an explicit return statement should be present at the end of the function (if reachable).

#### Len As Condition {#PYLINT_LAC}
Used when Pylint detects that len(sequence) is being used inside a condition to determine if a sequence is empty. Instead of comparing the length to 0, rely on the fact that empty sequences are false.

#### No Else Raise {#PYLINT_NoER}
Used in order to highlight an unnecessary block of code following an if containing a raise statement. As such, it will warn when it encounters an else following a chain of ifs, all of them containing a raise statement.

#### No Else Return {#PYLINT_NER}
Used in order to highlight an unnecessary block of code following an if containing a return statement. As such, it will warn when it encounters an else following a chain of ifs, all of them containing a return statement.

#### Redefined Argument From Local {#PYLINT_RAFL}
Used when a local name is redefining an argument, which might suggest a potential error. This is taken in account only for a handful of name binding operations, such as for iteration, with statement assignment and exception handler assignment.

#### Simplifiable If Expression {#PYLINT_SIE}
Used when an if expression can be replaced with 'bool(test)'.

#### Simplifiable If Statement {#PYLINT_SIS}
Used when an if statement can be replaced with 'bool(test)'.

#### Simplify Boolean Expression {#PYLINT_SBE}
Emitted when redundant pre-python 2.5 ternary syntax is used.

#### Stop Iteration Return {#PYLINT_SIR}
According to PEP479, the raise of StopIteration to end the loop of a generator may lead to hard to find bugs. This PEP specify that raise StopIteration has to be replaced by a simple return statement.

#### Too Many Nested Blocks {#PYLINT_TMNB}
Used when a function or a method has too many nested blocks. This makes the code less understandable and maintainable.

#### Trailing Comma Tuple {#PYLINT_TCT}
In Python, a tuple is actually created by the comma symbol, not by the parentheses. Unfortunately, one can actually create a tuple by misplacing a trailing comma, which can lead to potential weird bugs in your code. You should always use parentheses explicitly for creating a tuple.

#### Unneeded Not {#PYLINT_UN}
Used when a boolean expression contains an unneeded negation.

#### Useless Return {#PYLINT_UR}
Emitted when a single "return" or "return None" statement is found at the end of function or method definition. This statement can safely be removed because Python will implicitly return None.

### Spelling Rules

#### Invalid Characters In Docstring {#PYLINT_ICID}
Used when a word in docstring cannot be checked by enchant.

#### Wrong Spelling In Comment {#PYLINT_WSIC}
Used when a word in comment is not spelled correctly.

#### Wrong Spelling In Docstring {#PYLINT_WSID}
Used when a word in docstring is not spelled correctly.

### Stdlib Rules

#### Bad Open Mode {#PYLINT_BOM}
Python supports: r, w, a\[, x\] modes with b, +, and U (only with r) options. See <http://docs.python.org/2/library/functions.html#open>.

#### Bad Thread Instantiation {#PYLINT_BTI}
The warning is emitted when a threading.Thread class is instantiated without the target function being passed. By default, the first parameter is the group param, not the target param.

#### Boolean Datetime {#PYLINT_BD}
Using datetime.time in a boolean context can hide subtle bugs when the time they represent matches midnight UTC. This behaviour was fixed in Python 3.5. See <http://bugs.python.org/issue13936> for reference. This message can't be emitted when using Python >= 3.5.

#### Deprecated Method {#PYLINT_DepM}
The method is marked as deprecated and will be removed in a future version of Python. Consider looking for an alternative in the documentation.

#### Invalid Envvar Default {#PYLINT_InED}
Env manipulation functions return None or str values. Supplying anything different as a default may cause bugs. See <https://docs.python.org/3/library/os.html#os.getenv>.

#### Invalid Envvar Value {#PYLINT_IEV}
Env manipulation functions support only string type arguments. See <https://docs.python.org/3/library/os.html#os.getenv>.

#### Redundant Unittest Assert {#PYLINT_RUA}
The first argument of assertTrue and assertFalse is a condition. If a constant is passed as parameter, that condition will be always true. In this case a warning should be emitted.

#### Shallow Copy Environ {#PYLINT_SCE}
os.environ is not a dict object but proxy object, so shallow copy has still effects on original object. See <https://bugs.python.org/issue15373> for reference.

#### Subprocess Popen Preexec Fn {#PYLINT_SPPF}
The preexec\_fn parameter is not safe to use in the presence of threads in your application. The child process could deadlock before exec is called. If you must use it, keep it trivial! Minimize the number of libraries you call into.<https://docs.python.org/3/library/subprocess.html#popen-constructor>.

### String Rules

#### Anomalous Backslash In String {#PYLINT_ABIS}
Used when a backslash is in a literal string but not as an escape.

#### Anomalous Unicode Escape In String {#PYLINT_AUEIS}
Used when an escape like \\u is encountered in a byte string where it has no effect.

#### Bad Format Character {#PYLINT_BFC}
Used when an unsupported format character is used in a format string.

#### Bad Format String {#PYLINT_BFS}
Used when a PEP 3101 format string is invalid.

#### Bad Format String Key {#PYLINT_BFSK}
Used when a format string that uses named conversion specifiers is used with a dictionary whose keys are not all strings.

#### Bad Str Strip Call {#PYLINT_BSSC}
The argument to a str.\{l,r,\}strip call contains a duplicate character.

#### Bad String Format Type {#PYLINT_BSFT}
Used when a type required by format string is not suitable for actual argument type.

#### Duplicate String Formatting Argument {#PYLINT_DSFA}
Used when we detect that a string formatting is repeating an argument instead of using named string arguments.

#### Format Combined Specification {#PYLINT_FCS}
Used when a PEP 3101 format string contains both automatic field numbering (e.g. '\{\}') and manual field specification (e.g. '\{0\}').

#### Format Needs Mapping {#PYLINT_FNM}
Used when a format string that uses named conversion specifiers is used with an argument that is not a mapping.

#### Implicit Str Concat In Sequence {#PYLINT_ISCIS}
String literals are implicitly concatenated in a literal iterable definition : maybe a comma is missing ?.

#### Invalid Format Index {#PYLINT_IFI}
Used when a PEP 3101 format string uses a lookup specifier (\{a\[1\]\}), but the argument passed for formatting doesn't contain or doesn't have that key as an attribute.

#### Missing Format Argument Key {#PYLINT_MFAK}
Used when a PEP 3101 format string that uses named fields doesn't receive one or more required keywords.

#### Missing Format Attribute {#PYLINT_MFA}
Used when a PEP 3101 format string uses an attribute specifier (\{0.length\}), but the argument passed for formatting doesn't have that attribute.

#### Missing Format String Key {#PYLINT_MFSK}
Used when a format string that uses named conversion specifiers is used with a dictionary that doesn't contain all the keys required by the format string.

#### Mixed Format String {#PYLINT_MFS}
Used when a format string contains both named (e.g. '%(foo)d') and unnamed (e.g. '%d') conversion specifiers. This is also used when a named conversion specifier contains * for the minimum field width and/or precision.

#### Too Few Format Args {#PYLINT_TFFA}
Used when a format string that uses unnamed conversion specifiers is given too few arguments.

#### Too Many Format Args {#PYLINT_TMFA}
Used when a format string that uses unnamed conversion specifiers is given too many arguments.

#### Truncated Format String {#PYLINT_TFS}
Used when a format string terminates before the end of a conversion specifier.

#### Unused Format String Argument {#PYLINT_UFSA}
Used when a PEP 3101 format string that uses named fields is used with an argument that is not required by the format string.

#### Unused Format String Key {#PYLINT_UFSK}
Used when a format string that uses named conversion specifiers is used with a dictionary that contains keys not required by the format string.

### Typecheck Rules

#### Assignment From No Return {#PYLINT_AFNR}
Used when an assignment is done on a function call but the inferred function doesn't return anything.

#### Assignment From None {#PYLINT_AFN}
Used when an assignment is done on a function call but the inferred function returns nothing but None.

#### C Extension No Member {#PYLINT_CENM}
Used when a variable is accessed for non-existent member of C extension. Due to unavailability of source static analysis is impossible, but it may be performed by introspecting living objects in run-time.

#### Invalid Metaclass {#PYLINT_InM}
Emitted whenever we can detect that a class is using, as a metaclass, something which might be invalid for using as a metaclass.

#### Invalid Sequence Index {#PYLINT_ISI}
Used when a sequence type is indexed with an invalid type. Valid types are ints, slices, and objects with an \_\_index\_\_ method.

#### Invalid Slice Index {#PYLINT_InSI}
Used when a slice index is not an integer, None, or an object with an \_\_index\_\_ method.

#### Invalid Unary Operand Type {#PYLINT_IUOT}
Emitted when a unary operand is used on an object which does not support this type of operation.

#### Keyword Arg Before Vararg {#PYLINT_KABV}
When defining a keyword argument before variable positional arguments, one can end up in having multiple values passed for the aforementioned parameter in case the method is called with keyword arguments.

#### Missing Kwoa {#PYLINT_MK}
Used when a function call does not pass a mandatory keyword-only argument.

#### No Member {#PYLINT_NM}
Used when a variable is accessed for an unexistent member.

#### No Value For Parameter {#PYLINT_NVFP}
Used when a function call passes too few arguments.

#### Not A Mapping {#PYLINT_NAM}
Used when a non-mapping value is used in place where mapping is expected.

#### Not An Iterable {#PYLINT_NoAI}
Used when a non-iterable value is used in place where iterable is expected.

#### Not Callable {#PYLINT_NC}
Used when an object being called has been inferred to a non callable object.

#### Not Context Manager {#PYLINT_NCM}
Used when an instance in a with statement doesn't implement the context manager protocol(\_\_enter\_\_/\_\_exit\_\_).

#### Redundant Keyword Arg {#PYLINT_RKA}
Used when a function call would result in assigning multiple values to a function parameter, one value from a positional argument and one from a keyword argument.

#### Repeated Keyword {#PYLINT_RK}
Emitted when a function call got multiple values for a keyword.

#### Too Many Function Args {#PYLINT_ToMFA}
Used when a function call passes too many positional arguments.

#### Unexpected Keyword Arg {#PYLINT_UKA}
Used when a function call passes a keyword argument that doesn't correspond to one of the function's parameter names.

#### Unhashable Dict Key {#PYLINT_UDK}
Emitted when a dict key is not hashable (i.e. doesn't define \_\_hash\_\_ method).

#### Unsubscriptable Object {#PYLINT_UO}
Emitted when a subscripted value doesn't support subscription (i.e. doesn't define \_\_getitem\_\_ method or \_\_class\_getitem\_\_ for a class).

#### Unsupported Assignment Operation {#PYLINT_UAO}
Emitted when an object does not support item assignment (i.e. doesn't define \_\_setitem\_\_ method).

#### Unsupported Binary Operation {#PYLINT_UBO}
Emitted when a binary arithmetic operation between two operands is not supported.

#### Unsupported Delete Operation {#PYLINT_UDO}
Emitted when an object does not support item deletion (i.e. doesn't define \_\_delitem\_\_ method).

#### Unsupported Membership Test {#PYLINT_UMT}
Emitted when an instance in membership test expression doesn't implement membership protocol (\_\_contains\_\_/\_\_iter\_\_/\_\_getitem\_\_).

### Variable Rules

#### Cell Var From Loop {#PYLINT_CVFL}
A variable used in a closure is defined in a loop. This will result in all closures using the same value for the closed-over variable.

#### Global At Module Level {#PYLINT_GAML}
Used when you use the "global" statement at the module level since it has no effect.

#### Global Statement {#PYLINT_GS}
Used when you use the "global" statement to update a global variable. Pylint just try to discourage this usage. That doesn't mean you cannot use it!

#### Global Variable Not Assigned {#PYLINT_GVNA}
Used when a variable is defined through the "global" statement but no assignment to this variable is done.

#### Global Variable Undefined {#PYLINT_GVU}
Used when a variable is defined through the "global" statement but the variable is not defined in the module scope.

#### Invalid All Object {#PYLINT_IAO}
Used when an invalid (non-string) object occurs in \_\_all\_\_.

#### No Name In Module {#PYLINT_NNIM}
Used when a name cannot be found in a module.

#### Possibly Unused Variable {#PYLINT_PUV}
Used when a variable is defined but might not be used. The possibility comes from the fact that locals() might be used, which could consume or not the said variable.

#### Redefine In Handler {#PYLINT_RIH}
Used when an exception handler assigns the exception to an existing name.

#### Redefined Builtin {#PYLINT_ReB}
Used when a variable or function override a built-in.

#### Redefined Outer Name {#PYLINT_RON}
Used when a variable's name hides a name defined in the outer scope.

#### Self Cls Assignment {#PYLINT_SCA}
Invalid assignment to self or cls in instance or class method respectively.

#### Unbalanced Tuple Unpacking {#PYLINT_UTU}
Used when there is an unbalanced tuple unpacking in assignment.

#### Undefined All Variable {#PYLINT_UAV}
Used when an undefined variable name is referenced in \_\_all\_\_.

#### Undefined Loop Variable {#PYLINT_ULV}
Used when a loop variable (i.e. defined by a for loop or a list comprehension or a generator expression) is used outside the loop.

#### Undefined Variable {#PYLINT_UV}
Used when an undefined variable is accessed.

#### Unpacking Non Sequence {#PYLINT_UNS}
Used when something which is not a sequence is used in an unpack assignment.

#### Unused Argument {#PYLINT_UA}
Used when a function or method argument is not used.

#### Unused Import {#PYLINT_UnI}
Used when an imported module or variable is not used.

#### Unused Variable {#PYLINT_UnV}
Used when a variable is defined but not used.

#### Unused Wildcard Import {#PYLINT_UWI}
Used when an imported module or variable is not used from a `'from X import *'` style import.

#### Used Before Assignment {#PYLINT_UBA}
Used when a local variable is accessed before its assignment.

