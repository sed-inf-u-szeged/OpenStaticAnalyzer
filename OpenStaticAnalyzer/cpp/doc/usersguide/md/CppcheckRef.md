## Reference of Cppcheck coding rule violations

Cppcheck is a static analysis tool for C/C++ code. Unlike C/C++ compilers and many other analysis tools it does not detect syntax errors in the code. Cppcheck primarily detects the types of bugs that the compilers normally do not detect. The goal is to detect only real errors in the code (i.e. have zero false positives).

OpenStaticAnalyzer uses Cppcheck "as is", without any guaranties that the results of Cppcheck are correct. All statements of the Cppcheck license apply here as well. All texts describing the rulesets and the individual rules are copied from the cppcheck with some minor grammatical fixes.

The list of rulesets and rules contained in each ruleset are the following:

- **API Rules:** The API Ruleset contains rules that find built in function usages that are wrong.

- **Boost Library Rules:** The Boost Library Ruleset contains rules for boost usage.

- **Buffer Overrun Rules:** The Buffer Overrun Ruleset contains rules that find mistakes about buffers usage and array indices.

- **Conditional Rules:** The Conditional Ruleset contains rules that find condition mistakes.

- **Division Rules:** The Division Ruleset contains rules about the division operator.

- **Exception Rules:** The Exception Ruleset contains rules about throwing and catching exceptions.

- **Initialization Rules:** The Initialization Ruleset contains rules about the initialization of allocated memory, variables and members.

- **Input Output Rules:** The Input Output Ruleset contains rules for input output operations.

- **Memory Handling Rules:** The Memory Handling Ruleset contains rules about memory leaks and common memory management problems.

- **Object Orientedness Rules:** The Object Orientedness Ruleset contains rules that find various mistakes about classes and other object orientedness related constructs.

- **Performance Rules:** The Performance Ruleset contains rules that find various performance issues.

- **Portability Rules:** The Portability Ruleset contains rules that find portability issues.

- **Readability and Consistency Rules:** The Readability and Consistency Ruleset contains rules about constructs that reduce the code readability.

- **STL Rules:** The STL Ruleset contains rules that find mistakes of STL usage (invalidation of iterators, mismatching containers, etc).

- **Side Effect Rules:** The Side Effect Ruleset contains rules that find suspicious constructs that can have side effects.

- **Simple Type Rules:** The Simple Type Ruleset contains rules that find simple type related issues.

- **Sizeof Operator Rules:** The Sizeof Operator Ruleset contains rules that check usage of sizeof operator.

- **Suspicious Construct Rules:** The Suspicious Construct Ruleset contains rules about constructs that are redundant or could lead to unexpected results.

- **Unnecessary and Unused Code Rules:** The Unnecessary and Unused Code Ruleset contains a collection of rules for unnecessary,unused or ineffective code.

- **Unreachable Code Rules:** The Unreachable Code Ruleset contains rules about code sections that can never be executed.

- **Variable Argument Related Rules:** The Variable Argument Related Ruleset contains rules about the usage of va_start and va_end functions.

The following table contains the enabled rules and their priorities:

  Category                           Name                                              Abbreviation      Prio.    
  ---------------------------------- ------------------------------------------------- ----------------- ---------
  API Rules                          Invalid Function Argument Boolean                 CPPCHECK_IFAB     Blocker  
                                     Invalid Function Argument String                  CPPCHECK_IFAS     Blocker  
                                     Invalid Function Arguments                        CPPCHECK_IFA      Blocker  
                                     Invalid Length Modifier Error                     CPPCHECK_ILME     Critical 
                                     Memset Value Out Of Range                         CPPCHECK_MVOOR    Critical 
                                     Memset Zero Bytes                                 CPPCHECK_MZB      Critical 
                                     Race After Interlocked Decrement                  CPPCHECK_RAID     Blocker  
                                     Strncat Usage                                     CPPCHECK_STRCU    Critical 
                                     Unprecise Math Call                               CPPCHECK_UPMC     Minor    
                                     Wrong Math Call                                   CPPCHECK_WMC      Critical 
                                     Wrong Pipe Parameter Size                         CPPCHECK_WPPS     Blocker  
  Boost Library Rules                Boost Foreach Error                               CPPCHECK_BFE      Blocker  
  Buffer Overrun Rules               Argument Size                                     CPPCHECK_AS       Critical 
                                     Array Index Out Of Bounds                         CPPCHECK_AIOOB    Blocker  
                                     Array Index Out Of Bounds Cond                    CPPCHECK_AIOOBC   Critical 
                                     Array Index Then Check                            CPPCHECK_AITC     Minor    
                                     Buffer Access Out Of Bounds                       CPPCHECK_BAOOB    Blocker  
                                     Buffer Not Zero Terminated                        CPPCHECK_BNZT     Critical 
                                     Insecure Cmd Line Arguments                       CPPCHECK_ICLA     Blocker  
                                     Negative Array Size                               CPPCHECK_NAS      Blocker  
                                     Negative Index                                    CPPCHECK_NI       Blocker  
                                     Negative Memory Allocation Size                   CPPCHECK_NMAS     Blocker  
                                     Out Of Bounds                                     CPPCHECK_OOB      Blocker  
                                     Pointer Out Of Bounds                             CPPCHECK_POOB     Minor    
                                     Possible Buffer Access Out Of Bounds              CPPCHECK_PBAOOB   Critical 
                                     Size Argument As Char                             CPPCHECK_SAAC     Critical 
                                     Terminate Strncpy                                 CPPCHECK_TSTRC    Critical 
  Conditional Rules                  Assign If Error                                   CPPCHECK_AIE      Minor    
                                     Bad Bitmask Check                                 CPPCHECK_BBC      Critical 
                                     Clarify Condition                                 CPPCHECK_CCOND    Minor    
                                     Comparison Error                                  CPPCHECK_CE       Minor    
                                     Comparison Function Is Always True Or False       CPPCHECK_CFIATOF  Critical 
                                     Comparison Of Bool With Invalid Comparator        CPPCHECK_COBWIC   Critical 
                                     Condition is Always False                         CPPCHECK_CAF      Minor    
                                     Identical Condition After Early Exit              CPPCHECK_ICAEE    Critical 
                                     Identical Inner Condition                         CPPCHECK_IIC      Critical 
                                     Incorrect Logic Operator                          CPPCHECK_ILO      Critical 
                                     Invalid Test For Overflow                         CPPCHECK_ITFO     Critical 
                                     Mismatching Bit And                               CPPCHECK_MBA      Minor    
                                     Modulo Always True False                          CPPCHECK_MATF     Critical 
                                     Multi Condition                                   CPPCHECK_MCOND    Minor    
                                     Opposite Inner Condition                          CPPCHECK_OIC      Critical 
                                     Pointer Addition Null Check                       CPPCHECK_PANC     Critical 
                                     Redundant Condition                               CPPCHECK_RCOND    Minor    
  Division Rules                     Unsafe Class Can Divide By Zero                   CPPCHECK_UCCDBZ   Minor    
                                     Zerodiv                                           CPPCHECK_ZD       Blocker  
                                     Zerodivcond                                       CPPCHECK_ZDC      Blocker  
  Exception Rules                    Catch Exception By Value                          CPPCHECK_CEBV     Minor    
                                     Except Dealloc Throw                              CPPCHECK_EDT      Critical 
                                     Except Rethrow Copy                               CPPCHECK_ERC      Minor    
                                     Except Throw In Destructor                        CPPCHECK_ETID     Critical 
                                     Throw In Noexcept Function                        CPPCHECK_TINF     Blocker  
                                     Unhandled Exception Specification                 CPPCHECK_UES      Minor    
  Initialization Rules               Dangerous Use Of Strncpy                          CPPCHECK_DUOS     Blocker  
                                     Deadpointer                                       CPPCHECK_DP       Blocker  
                                     Uninit Struct Member                              CPPCHECK_UISM     Blocker  
                                     Uninitialized Data                                CPPCHECK_UID      Blocker  
                                     Uninitialized Variable                            CPPCHECK_UIV      Blocker  
  Input Output Rules                 Cout Cerr Misusage                                CPPCHECK_CCM      Blocker  
                                     Fflush On Input Stream                            CPPCHECK_FOIS     Minor    
                                     IO Without Positioning                            CPPCHECK_IOWP     Blocker  
                                     Invalid Printf Arg Type_float                     CPPCHECK_IPATF    Critical 
                                     Invalid Printf Arg Type_n                         CPPCHECK_IPATN    Critical 
                                     Invalid Printf Arg Type_p                         CPPCHECK_IPATP    Critical 
                                     Invalid Printf Arg Type_s                         CPPCHECK_IPATS    Critical 
                                     Invalid Printf Arg Type_sint                      CPPCHECK_IPATSI   Critical 
                                     Invalid Printf Arg Type_uint                      CPPCHECK_IPATUI   Critical 
                                     Invalid Scanf                                     CPPCHECK_IS       Critical 
                                     Invalid Scanf Arg Type_float                      CPPCHECK_ISATF    Critical 
                                     Invalid Scanf Arg Type_int                        CPPCHECK_ISATI    Critical 
                                     Invalid Scanf Arg Type_s                          CPPCHECK_ISATS    Critical 
                                     Invalid Scanf Format Width                        CPPCHECK_ISFW     Blocker  
                                     Read Write Only File                              CPPCHECK_RWOF     Blocker  
                                     Seek On Appended File                             CPPCHECK_SOAF     Critical 
                                     Use Closed File                                   CPPCHECK_UCF      Blocker  
                                     Write Read Only File                              CPPCHECK_WROF     Blocker  
                                     Wrong Printf Scanf Arg Num                        CPPCHECK_WPSAN    Blocker  
                                     Wrong Printf Scanf Parameter Position Error       CPPCHECK_WPSPPE   Critical 
  Memory Handling Rules              Access Forwarded                                  CPPCHECK_AF       Critical 
                                     Access Moved                                      CPPCHECK_AM       Critical 
                                     Auto Variables                                    CPPCHECK_AV       Blocker  
                                     Auto Variables Assign Global Pointer              CPPCHECK_AVAGP    Critical 
                                     Autovar Invalid Deallocation                      CPPCHECK_AID      Blocker  
                                     Dangling Lifetime                                 CPPCHECK_DL       Blocker  
                                     Dealloc Dealloc                                   CPPCHECK_DD       Blocker  
                                     Deallocret                                        CPPCHECK_DAR      Blocker  
                                     Deallocuse                                        CPPCHECK_DU       Blocker  
                                     Double Free                                       CPPCHECK_DF       Blocker  
                                     Ignored Return Value                              CPPCHECK_IRV      Critical 
                                     Incomplete Array Fill                             CPPCHECK_IAF      Critical 
                                     Invalid Free                                      CPPCHECK_IF       Blocker  
                                     Invalid Lifetime                                  CPPCHECK_ILT      Blocker  
                                     Leak No Var Function Call                         CPPCHECK_LNVFC    Blocker  
                                     Leak Return Val Not Used                          CPPCHECK_LRVNU    Blocker  
                                     Memleak                                           CPPCHECK_ML       Blocker  
                                     Memleak On Realloc                                CPPCHECK_MOR      Blocker  
                                     Mismatch Alloc Dealloc                            CPPCHECK_MAD      Blocker  
                                     Mismatch Size                                     CPPCHECK_MS       Blocker  
                                     NULL Pointer Dereference With Default Argument    CPPCHECK_NPDWDA   Critical 
                                     Null Pointer                                      CPPCHECK_NP       Blocker  
                                     Pointer Arithmetic With NULL                      CPPCHECK_PAWN     Blocker  
                                     Public Allocation Error                           CPPCHECK_PAE      Critical 
                                     Redundant NULL Pointer Check                      CPPCHECK_RNPC     Critical 
                                     Resource Leak                                     CPPCHECK_RL       Blocker  
                                     Return Address Of Auto Variable                   CPPCHECK_RAOAV    Blocker  
                                     Return Address Of Function Parameter              CPPCHECK_RAOFP    Blocker  
                                     Return Dangling Lifetime                          CPPCHECK_RDL      Blocker  
                                     Return Local Variable                             CPPCHECK_RLV      Blocker  
                                     Return Reference                                  CPPCHECK_RF       Blocker  
                                     Return Temp Reference                             CPPCHECK_RTF      Blocker  
                                     Unsafe Class Can Leak                             CPPCHECK_UCCL     Minor    
                                     Unsafe allocation                                 CPPCHECK_UA       Critical 
                                     Useless Assignment Arg                            CPPCHECK_UAA      Minor    
                                     Useless Assignment Ptr Arg                        CPPCHECK_UAPARG   Critical 
  Object Orientedness Rules          Assignment Operator Should Be Left Unimplemented  CPPCHECK_AOSBLU   Minor    
                                     Copy Constructor And Eq Operator                  CPPCHECK_CCAEO    Critical 
                                     Copy Ctor Pointer Copying                         CPPCHECK_CCPC     Minor    
                                     Dupl Inherited Member                             CPPCHECK_DIM      Critical 
                                     Function Const                                    CPPCHECK_FC       Minor    
                                     Function Static                                   CPPCHECK_FS       Major    
                                     Initializer List                                  CPPCHECK_IL       Minor    
                                     Malloc On Class Error                             CPPCHECK_MOCE     Blocker  
                                     Malloc On Class Warning                           CPPCHECK_MOCW     Critical 
                                     Memset Class                                      CPPCHECK_MC       Blocker  
                                     Memset Class Float                                CPPCHECK_MCF      Minor    
                                     Memset Class Reference                            CPPCHECK_MCR      Blocker  
                                     Missing Return From Assignement Operator          CPPCHECK_MRFAO    Blocker  
                                     No Assignment Operator                            CPPCHECK_NAO      Minor    
                                     No Constructor                                    CPPCHECK_NC       Minor    
                                     No Copy Constructor                               CPPCHECK_NCC      Minor    
                                     No Destructor                                     CPPCHECK_ND       Minor    
                                     No Explicit Constructor                           CPPCHECK_NEC      Minor    
                                     Operator Eq                                       CPPCHECK_OE       Minor    
                                     Operator Eq Ret Ref This                          CPPCHECK_OERRT    Minor    
                                     Operator Eq To Self                               CPPCHECK_OETS     Critical 
                                     Operator Eq Var Error                             CPPCHECK_OEVE     Critical 
                                     Pure Virtual Call                                 CPPCHECK_PVC      Critical 
                                     Self Initialization                               CPPCHECK_SI       Blocker  
                                     This Subtraction                                  CPPCHECK_TS       Critical 
                                     Uninitialized Member Variable                     CPPCHECK_UMV      Critical 
                                     Unused Private Function                           CPPCHECK_UPF      Minor    
                                     Use Initialization List                           CPPCHECK_UIL      Major    
                                     Virtual Call In Constructor                       CPPCHECK_VCIC     Critical 
                                     Virtual Destructor                                CPPCHECK_VD       Blocker  
  Performance Rules                  Assign Bool To Float                              CPPCHECK_ABTF     Minor    
                                     Passed By Value                                   CPPCHECK_PBV      Major    
                                     Postfix Operator                                  CPPCHECK_PO       Major    
                                     Redundant Assignment                              CPPCHECK_RA       Minor    
                                     Redundant Copy                                    CPPCHECK_RCPY     Major    
                                     Redundant Copy Local Const                        CPPCHECK_RCLC     Major    
                                     Same Iterator Expression                          CPPCHECK_SIE      Minor    
  Portability Rules                  Assignment Address To Integer                     CPPCHECK_AATI     Minor    
                                     Assignment Integer To Address                     CPPCHECK_AITA     Minor    
                                     Cast Address To Integer At Return                 CPPCHECK_CATIAR   Minor    
                                     Cast Integer To Address At Return                 CPPCHECK_CITAAR   Minor    
  Readability and Consistency Rules  Clarify Calculation                               CPPCHECK_CCALC    Minor    
                                     Clarify Statement                                 CPPCHECK_CSTAT    Critical 
                                     Comma Separated Return                            CPPCHECK_CSR      Minor    
                                     Cstyle Cast                                       CPPCHECK_CSC      Minor    
                                     Function Argument Names Different                 CPPCHECK_FAND     Minor    
                                     Function Argument Order Different                 CPPCHECK_FAOD     Critical 
                                     Missing Override                                  CPPCHECK_MO       Minor    
                                     Shadow Function                                   CPPCHECK_SF       Minor    
                                     Shadow Variable                                   CPPCHECK_SV       Minor    
                                     Suspicious Semicolon                              CPPCHECK_SS       Critical 
                                     Variable Scope                                    CPPCHECK_VS       Minor    
  STL Rules                          Comparing Iterators Of Different Containers1      CPPCHECK_CIODC1   Blocker  
                                     Comparing Iterators Of Different Containers2      CPPCHECK_CIODC2   Blocker  
                                     Container Out Of Bounds                           CPPCHECK_COOB     Blocker  
                                     Deref Invalid Iterator                            CPPCHECK_DII      Critical 
                                     Erase Dereference                                 CPPCHECK_ED       Blocker  
                                     Invalid Iterator1                                 CPPCHECK_IIT      Blocker  
                                     Invalid Iterator2                                 CPPCHECK_IIT2     Blocker  
                                     Invalid Pointer                                   CPPCHECK_IP       Blocker  
                                     Mismatching Containers                            CPPCHECK_MMC      Blocker  
                                     Read Empty Container                              CPPCHECK_REC      Minor    
                                     Redundant If Remove                               CPPCHECK_RIR      Minor    
                                     Same Iterator With Different Containers1          CPPCHECK_SIWDC1   Blocker  
                                     Same Iterator With Different Containers2          CPPCHECK_SIWDC2   Blocker  
                                     Stl Boundaries                                    CPPCHECK_STLB     Blocker  
                                     Stl If Find                                       CPPCHECK_STLIF    Critical 
                                     Stl If Str Find                                   CPPCHECK_STLISF   Major    
                                     Stl Missing Comparison                            CPPCHECK_STLMC    Critical 
                                     Stl Out Of Bounds                                 CPPCHECK_STLOOB   Blocker  
                                     Stl Size                                          CPPCHECK_STLS     Major    
                                     Stlcstr                                           CPPCHECK_STLC     Blocker  
                                     Stlcstr Param                                     CPPCHECK_SCP      Major    
                                     Stlcstr Return                                    CPPCHECK_SCR      Major    
                                     Stlcstr Throw                                     CPPCHECK_SCT      Blocker  
                                     Use Auto Pointer Array                            CPPCHECK_UAPA     Blocker  
                                     Use Auto Pointer Container                        CPPCHECK_UAPC     Blocker  
                                     Use Auto Pointer Copy                             CPPCHECK_UAPCPY   Minor    
                                     Use Auto Pointer Malloc                           CPPCHECK_UAPM     Blocker  
                                     Use STL Algorithm                                 CPPCHECK_USA      Minor    
                                     Useless Calls Compare                             CPPCHECK_UCC      Critical 
                                     Useless Calls Empty                               CPPCHECK_UCE      Critical 
                                     Useless Calls Remove                              CPPCHECK_UCR      Critical 
                                     Useless Calls Substr                              CPPCHECK_UCSS     Major    
                                     Useless Calls Swap                                CPPCHECK_UCS      Major    
  Side Effect Rules                  Assert With Side Effect                           CPPCHECK_AWSE     Critical 
                                     Assignment In Assert                              CPPCHECK_AIA      Critical 
                                     Unknown Evaluation Order                          CPPCHECK_UEO      Blocker  
  Simple Type Rules                  Assign Bool To Pointer                            CPPCHECK_ABTP     Blocker  
                                     Bitwise On Boolean                                CPPCHECK_BOB      Minor    
                                     Char Bit Op                                       CPPCHECK_CBO      Critical 
                                     Char Literal With Char Ptr Compare                CPPCHECK_CLWCPC   Critical 
                                     Character Array Index                             CPPCHECK_CAI      Minor    
                                     Check Cast Int To Char And Back                   CPPCHECK_CCITCAB  Critical 
                                     Compare Bool Expression With Int                  CPPCHECK_CBEWI    Critical 
                                     Comparison Of Bool With Bool Error                CPPCHECK_COBWBE   Minor    
                                     Comparison Of Func Returning Bool Error           CPPCHECK_COFRBE   Minor    
                                     Comparison Of Two Funcs Returning Bool Error      CPPCHECK_COTFRBE  Minor    
                                     Float Conversion Overflow                         CPPCHECK_FCO      Blocker  
                                     Incorrect Char Boolean Error                      CPPCHECK_ICBE     Critical 
                                     Incorrect String Boolean Error                    CPPCHECK_ISBE     Critical 
                                     Incorrect String Compare                          CPPCHECK_ISC      Critical 
                                     Increment Boolean                                 CPPCHECK_IB       Minor    
                                     Integer Overflow                                  CPPCHECK_IO       Blocker  
                                     Invalid Pointer Cast                              CPPCHECK_IPC      Minor    
                                     Memset Float                                      CPPCHECK_MF       Minor    
                                     Pointer Arith Bool                                CPPCHECK_PAB      Blocker  
                                     Pointer Less Than Zero                            CPPCHECK_PLTZ     Minor    
                                     Pointer Positive                                  CPPCHECK_PP       Minor    
                                     Shift By Negative                                 CPPCHECK_SBN      Blocker  
                                     Shift Negative                                    CPPCHECK_SN       Minor    
                                     Shift Too Many Bits                               CPPCHECK_STMB     Blocker  
                                     Shift Too Many Bits Signed                        CPPCHECK_STMBS    Blocker  
                                     Sign Conversion                                   CPPCHECK_SC       Critical 
                                     Signed Char Array Index                           CPPCHECK_SCAI     Critical 
                                     Sprintf Overlapping Data                          CPPCHECK_SOD      Blocker  
                                     Static String Compare                             CPPCHECK_SSC      Critical 
                                     Str Plus Char                                     CPPCHECK_SPC      Blocker  
                                     String Compare                                    CPPCHECK_STRCMP   Critical 
                                     String Literal Write                              CPPCHECK_SLW      Blocker  
                                     Trunc Long Cast Assignment                        CPPCHECK_TLCA     Minor    
                                     Trunc Long Cast Return                            CPPCHECK_TLCR     Minor    
                                     Unsigned Less Than Zero                           CPPCHECK_ULTZ     Minor    
                                     Unsigned Positive                                 CPPCHECK_UP       Minor    
                                     Variable Comparison With String Literal           CPPCHECK_VCWSL    Critical 
  Sizeof Operator Rules              Arithmetic Operations On Void Pointer             CPPCHECK_AOOVP    Minor    
                                     Divide Sizeof                                     CPPCHECK_DSO      Critical 
                                     Multiply Sizeof                                   CPPCHECK_MSO      Critical 
                                     Pointer Size                                      CPPCHECK_PS       Critical 
                                     Sizeof Calculation                                CPPCHECK_SOC      Critical 
                                     Sizeof Dereferenced Void Pointer                  CPPCHECK_SODVP    Minor    
                                     Sizeof Division Memfunc                           CPPCHECK_SODMF    Critical 
                                     Sizeof Function Call                              CPPCHECK_SOFC     Critical 
                                     Sizeof Sizeof                                     CPPCHECK_SOSO     Critical 
                                     Sizeof Void                                       CPPCHECK_SOV      Minor    
                                     Sizeof With Numeric Parameter                     CPPCHECK_SOWNP    Critical 
                                     Sizeof With Silent Array Pointer                  CPPCHECK_SOWSAP   Critical 
  Suspicious Construct Rules         Const Statement                                   CPPCHECK_CS       Critical 
                                     Duplicate Assign Expression                       CPPCHECK_DAE      Minor    
                                     Duplicate Branch                                  CPPCHECK_DBRANCH  Minor    
                                     Duplicate Expression                              CPPCHECK_DEXPR    Minor    
                                     Duplicate Expression Ternary                      CPPCHECK_DET      Minor    
                                     Duplicate Value Ternary                           CPPCHECK_DVT      Minor    
                                     Mismatching Container Expression                  CPPCHECK_MCE      Critical 
                                     Nan In Arithmetic Expression                      CPPCHECK_NIAE     Minor    
                                     Opposite Expression                               CPPCHECK_OPE      Minor    
                                     Overlapping Strcmp                                CPPCHECK_OS       Critical 
                                     Redundant Assign In Switch                        CPPCHECK_RAIS     Critical 
                                     Redundant Bitwise Operation In Switch             CPPCHECK_RBOIS    Critical 
                                     Redundant Copy In Switch                          CPPCHECK_RCIS     Critical 
                                     Redundant Pointer Operation                       CPPCHECK_RPO      Minor    
                                     Return Address Of Auto Variable                   CPPCHECK_RNBIBF   Minor    
                                     Self Assignment                                   CPPCHECK_SA       Critical 
                                     Suspicious Case                                   CPPCHECK_SUSPC    Critical 
                                     Suspicious Equality Comparison                    CPPCHECK_SEC      Critical 
                                     Unused Scoped Object                              CPPCHECK_UUSO     Minor    
  Unnecessary and Unused Code Rules  Unassigned Variable                               CPPCHECK_UAV      Minor    
                                     Unread Variable                                   CPPCHECK_URV      Minor    
                                     Unused Allocated Memory                           CPPCHECK_UUAM     Minor    
                                     Unused Function                                   CPPCHECK_UUF      Minor    
                                     Unused Label                                      CPPCHECK_UL       Minor    
                                     Unused Struct Member                              CPPCHECK_UUSM     Minor    
                                     Unused Switch Label                               CPPCHECK_USL      Critical 
                                     Unused Variable                                   CPPCHECK_UUV      Minor    
  Unreachable Code Rules             Duplicate Break                                   CPPCHECK_DBREAK   Minor    
                                     Unreachable Code                                  CPPCHECK_URC      Minor    
  Variable Argument Related Rules    Va_end Missing                                    CPPCHECK_VAEM     Blocker  
                                     Va_list Used Before Started                       CPPCHECK_VALUBS   Blocker  
                                     Va_start Reference Passed                         CPPCHECK_VASRP    Blocker  
                                     Va_start Subsequent Calls                         CPPCHECK_VASSC    Blocker  
                                     Va_start Wrong Parameter                          CPPCHECK_VASWP    Critical 
                                     Var Func Null UB                                  CPPCHECK_VFNUB    Minor    

### API Rules

#### Invalid Function Argument Boolean {#CPPCHECK_IFAB}
Invalid func_name() argument nr 1. A non-boolean value is required.

#### Invalid Function Argument String {#CPPCHECK_IFAS}
Invalid func_name() argument nr 1. A nul-terminated string is required.

#### Invalid Function Arguments {#CPPCHECK_IFA}
Invalid func_name() argument nr 1. The value is 0 or 1 (boolean) but the valid values are '1:4'.

#### Invalid Length Modifier Error {#CPPCHECK_ILME}
'I' in format string (no. 1) is a length modifier and cannot be used without a conversion specifier.

#### Memset Value Out Of Range {#CPPCHECK_MVOOR}
The 2nd memset() argument 'varname' doesn't fit into an 'unsigned char'. The 2nd parameter is passed as an 'int', but the function fills the block of memory using the 'unsigned char' conversion of this value.

#### Memset Zero Bytes {#CPPCHECK_MZB}
memset() called to fill 0 bytes. The second and third arguments might be inverted. 
The function memset ( void \* ptr, int value, size_t num ) sets the first num bytes of the block of memory pointed by ptr to the specified value.

#### Race After Interlocked Decrement {#CPPCHECK_RAID}
Race condition: non-interlocked access after InterlockedDecrement(). Use InterlockedDecrement() return value instead.

#### Strncat Usage {#CPPCHECK_STRCU}
At most, strncat appends the 3rd parameter's amount of characters and adds a terminating null byte. The safe way to use strncat is to subtract one from the remaining space in the buffer and use it as 3rd parameter.

Source: <http://www.cplusplus.com/reference/cstring/strncat/>

Source: <http://www.opensource.apple.com/source/Libc/Libc-167/gen.subproj/i386.subproj/strncat.c>

#### Unprecise Math Call {#CPPCHECK_UPMC}
Expression '1 - erf(x)' can be replaced by 'erfc(x)' to avoid loss of precision.

#### Wrong Math Call {#CPPCHECK_WMC}
Passing value '\#' to \#() leads to implementation-defined result.

#### Wrong Pipe Parameter Size {#CPPCHECK_WPPS}
The pipe()/pipe2() system command takes an argument, which is an array of exactly two integers. The variable 'varname' is an array of size dimension, which does not match.

### Boost Library Rules

#### Boost Foreach Error {#CPPCHECK_BFE}
BOOST_FOREACH caches the end() iterator. It's undefined behavior if you modify the container inside.

### Buffer Overrun Rules

#### Argument Size {#CPPCHECK_AS}
The array 'array' is too small, the function 'function' expects a bigger one.

#### Array Index Out Of Bounds {#CPPCHECK_AIOOB}
Array 'array[2]' index array[1][1] out of bounds.

#### Array Index Out Of Bounds Cond {#CPPCHECK_AIOOBC}
Array 'x\[10\]' accessed at index 20, which is out of bounds. Otherwise condition 'y==20' is redundant.

#### Array Index Then Check {#CPPCHECK_AITC}
Defensive programming: The variable 'index' is used as an array index before it is checked that is within limits. This can mean that the array might be accessed out of bounds.
Reorder conditions such as '(a\[i\] && i \< 10)' to '(i \< 10 && a\[i\])'. That way the array will not be accessed if the index is out of limits.

#### Buffer Access Out Of Bounds {#CPPCHECK_BAOOB}
Buffer is accessed out of bounds: buffer

#### Buffer Not Zero Terminated {#CPPCHECK_BNZT}
The buffer 'buffer' is not null-terminated after the call to strncpy(). This will cause bugs later in the code if the code assumes the buffer is null-terminated.

#### Insecure Cmd Line Arguments {#CPPCHECK_ICLA}
Buffer overrun possible for long command line arguments.

#### Negative Array Size {#CPPCHECK_NAS}
Declaration of array '' with negative size is undefined behaviour

#### Negative Index {#CPPCHECK_NI}
Array index -1 is out of bounds.

#### Negative Memory Allocation Size {#CPPCHECK_NMAS}
Memory allocation size is negative.Negative allocation size has no specified behaviour.

#### Out Of Bounds {#CPPCHECK_OOB}
Index is out of bounds: Supplied size 2 is larger than actual size 1.

#### Pointer Out Of Bounds {#CPPCHECK_POOB}
Undefined behaviour, pointer arithmetic '' is out of bounds. From chapter 6.5.6 in the C specification: "When an expression that has integer type is added to or subtracted from a pointer, .." and then "If both the pointer operand and the result point to elements of the same array object, or one past the last element of the array object, the evaluation shall not produce an overflow; otherwise, the behavior is undefined."

#### Possible Buffer Access Out Of Bounds {#CPPCHECK_PBAOOB}
Possible buffer overflow if strlen(source) is larger than or equal to sizeof(destination). The source buffer is larger than the destination buffer so there is the potential for overflowing the destination buffer.

#### Size Argument As Char {#CPPCHECK_SAAC}
The size argument is given as a char constant.

#### Terminate Strncpy {#CPPCHECK_TSTRC}
The buffer 'buffer' may not be null-terminated after the call to strncpy(). If the source string's size fits or exceeds the given size, strncpy() does not add a zero at the end of the buffer. This causes bugs later in the code if the code assumes buffer is null-terminated.

### Conditional Rules

#### Assign If Error {#CPPCHECK_AIE}
Mismatching assignment and comparison, comparison '' is always false.

#### Bad Bitmask Check {#CPPCHECK_BBC}
Result of operator '|' is always true if one operand is non-zero. Did you intend to use '&'?

#### Clarify Condition {#CPPCHECK_CCOND}
Suspicious condition (assignment + comparison); Clarify expression with parentheses.

#### Comparison Error {#CPPCHECK_CE}
The expression '(X & 0x6) == 0x1' is always false. Check carefully constants and operators used, these errors might be hard to spot sometimes. In case of complex expression it might help to split it to separate expressions.

#### Comparison Function Is Always True Or False {#CPPCHECK_CFIATOF}
The function isless is designed to compare two variables. Calling this function with one variable (varName) for both parameters leads to a statement which is always false.

#### Comparison Of Bool With Invalid Comparator {#CPPCHECK_COBWIC}
The result of the expression 'expression' is of type 'bool'. Comparing 'bool' value using relational (<, >, <= or >=) operator could cause unexpected results.

#### Condition is Always False {#CPPCHECK_CAF}
Condition 'x' is always false

#### Identical Condition After Early Exit {#CPPCHECK_ICAEE}
Identical condition 'x', second condition is always false

#### Identical Inner Condition {#CPPCHECK_IIC}
Identical inner 'if' condition is always true (outer condition is 'x' and inner condition is 'x').

#### Incorrect Logic Operator {#CPPCHECK_ILO}
Logical disjunction always evaluates to true: foo > 3 && foo \< 4. Are these conditions necessary? Did you intend to use && instead? Are the numbers correct? Are you comparing the correct variables?

#### Invalid Test For Overflow {#CPPCHECK_ITFO}
Invalid test for overflow 'x + u < x'. Condition is always false unless there is overflow, and overflow is undefined behaviour.

#### Mismatching Bit And {#CPPCHECK_MBA}
Mismatching bitmasks. Result is always 0 (X = Y & 0xf0; Z = X & 0x1; => Z=0).

#### Modulo Always True False {#CPPCHECK_MATF}
Comparison of modulo result is predetermined, because it is always less than 1.

#### Multi Condition {#CPPCHECK_MCOND}
Expression is always false because 'else if' condition matches previous condition at line 1.

#### Opposite Inner Condition {#CPPCHECK_OIC}
Opposite inner 'if' condition leads to a dead code block (outer condition is 'x' and inner condition is '!x').

#### Pointer Addition Null Check {#CPPCHECK_PANC}
Comparison is wrong. Result of 'ptr+1' can't be 0 unless there is pointer overflow, and pointer overflow is undefined behaviour.

#### Redundant Condition {#CPPCHECK_RCOND}
Redundant condition: If x > 11 the condition x > 10 is always true.

### Division Rules

#### Unsafe Class Can Divide By Zero {#CPPCHECK_UCCDBZ}
Public interface of Class is not safe. When calling Class::dostuff(), if parameter x is 0 that leads to division by zero.

#### Zerodiv {#CPPCHECK_ZD}
Division by zero.

#### Zerodivcond {#CPPCHECK_ZDC}
Either the condition is redundant or there is division by zero.

### Exception Rules

#### Catch Exception By Value {#CPPCHECK_CEBV}
The exception is caught by value. It could be caught as a (const) reference which is usually recommended in C++.

#### Except Dealloc Throw {#CPPCHECK_EDT}
Exception thrown in invalid state, 'p' points at deallocated memory.

#### Except Rethrow Copy {#CPPCHECK_ERC}
Rethrowing an exception with 'throw varname;' creates an unnecessary copy of 'varname'. To rethrow the caught exception without unnecessary copying or slicing, use a bare 'throw;'.

#### Except Throw In Destructor {#CPPCHECK_ETID}
The class Class is not safe because its destructor throws an exception. If Class is used and an exception is thrown that is caught in an outer scope the program will terminate.

#### Throw In Noexcept Function {#CPPCHECK_TINF}
Exception thrown in function declared not to throw exceptions.

#### Unhandled Exception Specification {#CPPCHECK_UES}
Unhandled exception specification when calling function foo(). Either use a try/catch around the function call, or add a exception specification for funcname() also.

### Initialization Rules

#### Dangerous Use Of Strncpy {#CPPCHECK_DUOS}
Dangerous usage of 'varname' (strncpy doesn't always null-terminate it).

#### Deadpointer {#CPPCHECK_DP}
Dead pointer usage. Pointer 'pointer' is dead if it has been assigned '&x' at line 0.

#### Uninit Struct Member {#CPPCHECK_UISM}
Uninitialized struct member: a.b

#### Uninitialized Data {#CPPCHECK_UID}
Memory is allocated but not initialized: varname

#### Uninitialized Variable {#CPPCHECK_UIV}
Uninitialized variable: varname

### Input Output Rules

#### Cout Cerr Misusage {#CPPCHECK_CCM}
Invalid usage of output stream: '\<\< std::cout'.

#### Fflush On Input Stream {#CPPCHECK_FOIS}
fflush() called on input stream 'stdin' may result in undefined behaviour on non-linux systems.

#### IO Without Positioning {#CPPCHECK_IOWP}
Read and write operations without a call to a positioning function (fseek, fsetpos or rewind) or fflush in between result in undefined behaviour.

#### Invalid Printf Arg Type_float {#CPPCHECK_IPATF}
%f in format string (no. 1) requires 'double' but the argument type is Unknown.

#### Invalid Printf Arg Type_n {#CPPCHECK_IPATN}
%n in format string (no. 1) requires 'int \*' but the argument type is Unknown.

#### Invalid Printf Arg Type_p {#CPPCHECK_IPATP}
%p in format string (no. 1) requires an address but the argument type is Unknown.

#### Invalid Printf Arg Type_s {#CPPCHECK_IPATS}
%s in format string (no. 1) requires 'char \*' but the argument type is Unknown.

#### Invalid Printf Arg Type_sint {#CPPCHECK_IPATSI}
%i in format string (no. 1) requires 'int' but the argument type is Unknown.

#### Invalid Printf Arg Type_uint {#CPPCHECK_IPATUI}
%u in format string (no. 1) requires 'unsigned int' but the argument type is Unknown.

#### Invalid Scanf {#CPPCHECK_IS}
scanf() without field width limits can crash with huge input data. Add a field width specifier to fix this problem.

Sample program that can crash:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.cpp}
#include <stdio.h>
int main()
{
  char c[5];
  scanf("%s", c);
  return 0;
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Typing in 5 or more characters may make the program crash. The correct usage here is 'scanf("%4s", c);', as the maximum field width does not include the terminating null byte.

Source: <http://linux.die.net/man/3/scanf>

Source: <http://www.opensource.apple.com/source/xnu/xnu-1456.1.26/libkern/stdio/scanf.c>

#### Invalid Scanf Arg Type_float {#CPPCHECK_ISATF}
%f in format string (no. 1) requires 'float \*' but the argument type is Unknown.

#### Invalid Scanf Arg Type_int {#CPPCHECK_ISATI}
%d in format string (no. 1) requires 'int \*' but the argument type is Unknown.

#### Invalid Scanf Arg Type_s {#CPPCHECK_ISATS}
%s in format string (no. 1) requires a 'char \*' but the argument type is Unknown.

#### Invalid Scanf Format Width {#CPPCHECK_ISFW}
Width 5 given in format string (no. 10) is larger than destination buffer '\[0\]', use %-1s to prevent overflowing it.

#### Read Write Only File {#CPPCHECK_RWOF}
Read operation on a file that was opened only for writing.

#### Seek On Appended File {#CPPCHECK_SOAF}
Repositioning operation performed on a file opened in append mode has no effect.

#### Use Closed File {#CPPCHECK_UCF}
Used file that is not opened.

#### Write Read Only File {#CPPCHECK_WROF}
Write operation on a file that was opened only for reading.

#### Wrong Printf Scanf Arg Num {#CPPCHECK_WPSAN}
printf format string requires 3 parameters but only 2 are given.

#### Wrong Printf Scanf Parameter Position Error {#CPPCHECK_WPSPPE}
printf: referencing parameter 2 while 1 arguments given

### Memory Handling Rules

#### Access Forwarded {#CPPCHECK_AF}
Access of forwarded variable 'v'.

#### Access Moved {#CPPCHECK_AM}
Access of moved variable 'v'.

#### Auto Variables {#CPPCHECK_AV}
Dangerous assignment - the function parameter is assigned the address of a local auto-variable. Local auto-variables are reserved from the stack which is freed when the function ends. So the pointer to a local variable is invalid after the function ends.

#### Auto Variables Assign Global Pointer {#CPPCHECK_AVAGP}
Address of local array array is assigned to global pointer pointer and not reassigned before array goes out of scope.

#### Autovar Invalid Deallocation {#CPPCHECK_AID}
The deallocation of an auto-variable results in undefined behaviour. You should only free memory that has been allocated dynamically.

#### Dangling Lifetime {#CPPCHECK_DL}
Non-local variable 'x' will use object.

#### Dealloc Dealloc {#CPPCHECK_DD}
Deallocating a deallocated pointer: varname

#### Deallocret {#CPPCHECK_DAR}
Returning/dereferencing 'p' after it is deallocated / released

#### Deallocuse {#CPPCHECK_DU}
Dereferencing 'varname' after it is deallocated / released

#### Double Free {#CPPCHECK_DF}
Memory pointed to by 'varname' is freed twice.

#### Ignored Return Value {#CPPCHECK_IRV}
Return value of function malloc() is not used.

#### Incomplete Array Fill {#CPPCHECK_IAF}
The array 'buffer' is filled incompletely. The function 'memset()' needs the size given in bytes, but an element of the given array is larger than one byte. Did you forget to multiply the size with 'sizeof(\*buffer)'?

#### Invalid Free {#CPPCHECK_IF}
Invalid memory address freed.

#### Invalid Lifetime {#CPPCHECK_ILT}
Using object that is out of scope.

#### Leak No Var Function Call {#CPPCHECK_LNVFC}
Allocation with funcName, funcName doesn't release it.

#### Leak Return Val Not Used {#CPPCHECK_LRVNU}
Return value of allocation function 'funcName' is not stored.

#### Memleak {#CPPCHECK_ML}
Memory leak: varname

#### Memleak On Realloc {#CPPCHECK_MOR}
Common realloc mistake: 'varname' nulled but not freed upon failure

#### Mismatch Alloc Dealloc {#CPPCHECK_MAD}
Mismatching allocation and deallocation: varname

#### Mismatch Size {#CPPCHECK_MS}
The allocated size sz is not a multiple of the underlying type's size.

#### NULL Pointer Dereference With Default Argument {#CPPCHECK_NPDWDA}
Possible null pointer dereference if the default parameter value is used: pointer

#### Null Pointer {#CPPCHECK_NP}
Null pointer dereference

#### Pointer Arithmetic With NULL {#CPPCHECK_PAWN}
Pointer arithmetic with NULL pointer.

#### Public Allocation Error {#CPPCHECK_PAE}
Possible leak in public function. The pointer 'varname' is not deallocated before it is allocated.

#### Redundant NULL Pointer Check {#CPPCHECK_RNPC}
Either the condition is redundant or there is possible null pointer dereference: pointer.

#### Resource Leak {#CPPCHECK_RL}
Resource leak: varname

#### Return Address Of Auto Variable {#CPPCHECK_RAOAV}
Address of an auto-variable returned.

#### Return Address Of Function Parameter {#CPPCHECK_RAOFP}
Address of the function parameter 'parameter' becomes invalid after the function exits because function parameters are stored on the stack which is freed when the function exits. Thus the returned value is invalid.

#### Return Dangling Lifetime {#CPPCHECK_RDL}
Returning object that will be invalid when returning.

#### Return Local Variable {#CPPCHECK_RLV}
Pointer to local array variable returned.

#### Return Reference {#CPPCHECK_RF}
Reference to auto variable returned.

#### Return Temp Reference {#CPPCHECK_RTF}
Reference to temporary returned.

#### Unsafe Class Can Leak {#CPPCHECK_UCCL}
The class 'class' is unsafe, wrong usage can cause memory/resource leaks for 'class::varname'. This can for instance be fixed by adding proper cleanup in the destructor.

#### Unsafe allocation {#CPPCHECK_UA}
Unsafe allocation. If funcName() throws, memory could be leaked. Use make_shared<int>() instead.

#### Useless Assignment Arg {#CPPCHECK_UAA}
Assignment of function parameter has no effect outside the function.

#### Useless Assignment Ptr Arg {#CPPCHECK_UAPARG}
Assignment of function parameter has no effect outside the function. Did you forget dereferencing it?

### Object Orientedness Rules

#### Assignment Operator Should Be Left Unimplemented {#CPPCHECK_AOSBLU}
'operator=' should either return reference to 'this' instance or be declared private and left unimplemented.

#### Copy Constructor And Eq Operator {#CPPCHECK_CCAEO}
The class 'class' has 'operator=' but lack of 'copy constructor'.

#### Copy Ctor Pointer Copying {#CPPCHECK_CCPC}
Value of pointer 'var', which points to allocated memory, is copied in copy constructor instead of allocating new memory.

#### Dupl Inherited Member {#CPPCHECK_DIM}
The class 'class' defines member variable with name 'variable' also defined in its parent class 'class'.

#### Function Const {#CPPCHECK_FC}
The member function 'class::function' can be made a const function. Making this function 'const' should not cause compiler errors. Even though the function can be made const function technically it may not make sense conceptually. Think about your design and the task of the function first - is it a function that must not change object internal state?

#### Function Static {#CPPCHECK_FS}
The member function 'class::function' can be made a static function. Making a function static can bring a performance benefit since no 'this' instance is passed to the function. This change should not cause compiler errors but it does not necessarily make sense conceptually. Think about your design and the task of the function first - is it a function that must not access members of class instances? And maybe it is more appropriate to move this function to a unnamed namespace.

#### Initializer List {#CPPCHECK_IL}
Member variable 'class::variable' is in the wrong place in the initializer list. Members are initialized in the order they are declared, not in the order they are in the initializer list. Keeping the initializer list in the same order that the members were declared prevents order dependent initialization errors.

#### Malloc On Class Error {#CPPCHECK_MOCE}
Memory for class instance allocated with malloc(), but class a std::string. This is unsafe, since no constructor is called and class members remain uninitialized. Consider using 'new' instead.

#### Malloc On Class Warning {#CPPCHECK_MOCW}
Memory for class instance allocated with malloc(), but class provides constructors. This is unsafe, since no constructor is called and class members remain uninitialized. Consider using 'new' instead.

#### Memset Class {#CPPCHECK_MC}
Using 'memfunc' on class that contains a classname is unsafe, because constructor, destructor and copy operator calls are omitted. These are necessary for this non-POD type to ensure that a valid object is created.

#### Memset Class Float {#CPPCHECK_MCF}
Using memset() on class which contains a floating point number. This is not portable because memset() sets each byte of a block of memory to a specific value and the actual representation of a floating-point value is implementation defined.

Note: In case of an IEEE754-1985 compatible implementation setting all bits to zero results in the value 0.0.

#### Memset Class Reference {#CPPCHECK_MCR}
Using 'memfunc' on class that contains a reference.

#### Missing Return From Assignement Operator {#CPPCHECK_MRFAO}
No 'return' statement in non-void function causes undefined behavior.

#### No Assignment Operator {#CPPCHECK_NAO}
Class 'class' does not have a operator= which is recommended since it has dynamic memory/resource allocation(s).

#### No Constructor {#CPPCHECK_NC}
The class 'classname' does not have a constructor although it has private member variables. Member variables of builtin types are left uninitialized when the class is instantiated. That may cause bugs or undefined behavior.

#### No Copy Constructor {#CPPCHECK_NCC}
Class 'class' does not have a copy constructor which is recommended since it has dynamic memory/resource allocation(s).

#### No Destructor {#CPPCHECK_ND}
Class 'class' does not have a destructor which is recommended since it has dynamic memory/resource allocation(s).

#### No Explicit Constructor {#CPPCHECK_NEC}
Class 'classname' has a constructor with 1 argument that is not explicit. Such constructors should in general be explicit for type safety reasons. Using the explicit keyword in the constructor means some mistakes when using the class can be avoided.

#### Operator Eq {#CPPCHECK_OE}
The class::operator= does not conform to standard C/C++ behaviour. To conform to standard C/C++ behaviour, return a reference to self (such as: 'class &class::operator=(..) { .. return *this; }'. For safety reasons it might be better to not fix this message. If you think that safety is always more important than conformance then please ignore/suppress this message. For more details about this topic, see the book "Effective C++" by Scott Meyers.

#### Operator Eq Ret Ref This {#CPPCHECK_OERRT}
'operator=' should return reference to 'this' instance.

#### Operator Eq To Self {#CPPCHECK_OETS}
'operator=' should check for assignment to self to ensure that each block of dynamically allocated memory is owned and managed by only one instance of the class.

#### Operator Eq Var Error {#CPPCHECK_OEVE}
Member variable 'classname::' is not assigned a value in 'classname::operator='.

#### Pure Virtual Call {#CPPCHECK_PVC}
Call of pure virtual function 'f' in constructor. The call will fail during runtime.

#### Self Initialization {#CPPCHECK_SI}
Member variable 'var' is initialized by itself.

#### This Subtraction {#CPPCHECK_TS}
Suspicious pointer subtraction. Did you intend to write '->'?

#### Uninitialized Member Variable {#CPPCHECK_UMV}
Member variable 'classname::varname' is not initialized in the constructor.

#### Unused Private Function {#CPPCHECK_UPF}
Unused private function: 'classname::funcname'

#### Use Initialization List {#CPPCHECK_UIL}
When an object of a class is created, the constructors of all member variables are called consecutively in the order the variables are declared, even if you don't explicitly write them to the initialization list. You could avoid assigning 'variable' a value by passing the value to the constructor in the initialization list.

#### Virtual Call In Constructor {#CPPCHECK_VCIC}
Virtual function 'f' is called from constructor '' at line 1. Dynamic binding is not used.

#### Virtual Destructor {#CPPCHECK_VD}
Class 'Base' which is inherited by class 'Derived' does not have a virtual destructor. If you destroy instances of the derived class by deleting a pointer that points to the base class, only the destructor of the base class is executed. Thus, dynamic memory that is managed by the derived class could leak. This can be avoided by adding a virtual destructor to the base class.

### Performance Rules

#### Assign Bool To Float {#CPPCHECK_ABTF}
Boolean value assigned to floating point variable.

#### Passed By Value {#CPPCHECK_PBV}
Parameter 'parametername' is passed by value. It could be passed as a const reference which is usually faster and recommended in C++.

#### Postfix Operator {#CPPCHECK_PO}
Prefix ++/-- operators should be preferred for non-primitive types. Pre-increment/decrement can be more efficient than post-increment/decrement. Post-increment/decrement usually involves keeping a copy of the previous value around and adds a little extra code.

#### Redundant Assignment {#CPPCHECK_RA}
Variable 'var' is reassigned a value before the old one has been used.

#### Redundant Copy {#CPPCHECK_RCPY}
Buffer 'var' is being written before its old content has been used.

#### Redundant Copy Local Const {#CPPCHECK_RCLC}
The const variable 'varname' is assigned a copy of the data. You can avoid the unnecessary data copying by converting 'varname' to const reference.

#### Same Iterator Expression {#CPPCHECK_SIE}
Same iterators expression are used for algorithm.

### Portability Rules

#### Assignment Address To Integer {#CPPCHECK_AATI}
Assigning a pointer to an integer (int/long/etc) is not portable across different platforms and compilers. For example in 32-bit Windows and linux they are same width, but in 64-bit Windows and linux they are of different width. In worst case you end up assigning 64-bit address to 32-bit integer. The safe way is to store addresses only in pointer types (or typedefs like uintptr_t).

#### Assignment Integer To Address {#CPPCHECK_AITA}
Assigning an integer (int/long/etc) to a pointer is not portable across different platforms and compilers. For example in 32-bit Windows and linux they are same width, but in 64-bit Windows and linux they are of different width. In worst case you end up assigning 64-bit integer to 32-bit pointer. The safe way is to store addresses only in pointer types (or typedefs like uintptr_t).

#### Cast Address To Integer At Return {#CPPCHECK_CATIAR}
Returning an address value in a function with integer (int/long/etc) return type is not portable across different platforms and compilers. For example in 32-bit Windows and Linux they are same width, but in 64-bit Windows and Linux they are of different width. In worst case you end up casting 64-bit address down to 32-bit integer. The safe way is to always return an integer.

#### Cast Integer To Address At Return {#CPPCHECK_CITAAR}
Returning an integer (int/long/etc) in a function with pointer return type is not portable across different platforms and compilers. For example in 32-bit Windows and Linux they are same width, but in 64-bit Windows and Linux they are of different width. In worst case you end up casting 64-bit integer down to 32-bit pointer. The safe way is to always return a pointer.

### Readability and Consistency Rules

#### Clarify Calculation {#CPPCHECK_CCALC}
Suspicious calculation. Please use parentheses to clarify the code. The code ''a+b?c:d'' should be written as either ''(a+b)?c:d'' or ''a+(b?c:d)''.

#### Clarify Statement {#CPPCHECK_CSTAT}
A statement like '\*A++;' might not do what you intended. Postfix 'operator++' is executed before 'operator\*'. Thus, the dereference is meaningless. Did you intend to write '(\*A)++;'?

#### Comma Separated Return {#CPPCHECK_CSR}
Comma is used in return statement. When comma is used in a return statement it can easily be misread as a semicolon.

For example in the code below the value of 'b' is returned if the condition is true, but it is easy to think that 'a+1' is returned:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.cpp}
    if (x)
        return a + 1,
    b++;
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

However it can be useful to use comma in macros. Cppcheck does not warn when such a macro is then used in a return statement, it is less likely such code is misunderstood.

#### Cstyle Cast {#CPPCHECK_CSC}
C-style pointer casting detected. C++ offers four different kinds of casts as replacements: static_cast, const_cast, dynamic_cast and reinterpret_cast. A C-style cast could evaluate to any of those automatically, thus it is considered safer if the programmer explicitly states which kind of cast is expected.

See also: <https://www.securecoding.cert.org/confluence/display/cplusplus/EXP05-CPP.+Do+not+use+C-style+casts>.

#### Function Argument Names Different {#CPPCHECK_FAND}
Function 'function' argument 2 names different: declaration 'A' definition 'B'.

#### Function Argument Order Different {#CPPCHECK_FAOD}
Function 'function' argument order different: declaration '' definition ''

#### Missing Override {#CPPCHECK_MO}
The function '' overrides a function in a base class but is not marked with a 'override' specifier.

#### Shadow Function {#CPPCHECK_SF}
Local variable f shadows outer function

#### Shadow Variable {#CPPCHECK_SV}
Local variable var shadows outer variable

#### Suspicious Semicolon {#CPPCHECK_SS}
Suspicious use of ; at the end of '' statement.

#### Variable Scope {#CPPCHECK_VS}
The scope of the variable 'varname' can be reduced. Warning: Be careful when fixing this message, especially when there are inner loops.

Here is an example where cppcheck will write that the scope for 'i' can be reduced:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.cpp}
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
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

When you see this message it is always safe to reduce the variable scope 1 level.

### STL Rules

#### Comparing Iterators Of Different Containers1 {#CPPCHECK_CIODC1}
Comparison of iterators from containers 'container1' and 'container2'.

#### Comparing Iterators Of Different Containers2 {#CPPCHECK_CIODC2}
Comparison of iterators from containers 'container' that are defined in different scopes.

#### Container Out Of Bounds {#CPPCHECK_COOB}
Out of bounds access of item in container 'var'

#### Deref Invalid Iterator {#CPPCHECK_DII}
Possible dereference of an invalid iterator: i. Make sure to check that the iterator is valid before dereferencing it - not after.

#### Erase Dereference {#CPPCHECK_ED}
The iterator 'iter' is invalid before being assigned. Dereferencing or comparing it with another iterator is invalid operation.

#### Invalid Iterator1 {#CPPCHECK_IIT}
Invalid iterator: iterator

#### Invalid Iterator2 {#CPPCHECK_IIT2}
After push_back|push_front|insert(), the iterator 'iterator' may be invalid.

#### Invalid Pointer {#CPPCHECK_IP}
Invalid pointer 'pointer' after push_back().

#### Mismatching Containers {#CPPCHECK_MMC}
Iterators of different containers are used together.

#### Read Empty Container {#CPPCHECK_REC}
Reading from empty STL container 'var'

#### Redundant If Remove {#CPPCHECK_RIR}
Redundant checking of STL container element existence before removing it. It is safe to call the remove method on a non-existing element.

#### Same Iterator With Different Containers1 {#CPPCHECK_SIWDC1}
Same iterator is used with different containers 'container1' and 'container2'.

#### Same Iterator With Different Containers2 {#CPPCHECK_SIWDC2}
Same iterator is used with containers 'container' that are defined in different scopes.

#### Stl Boundaries {#CPPCHECK_STLB}
Iterator compared with operator\<. This is dangerous since the order of items in the container is not guaranteed. One should use operator!= instead to compare iterators.

#### Stl If Find {#CPPCHECK_STLIF}
Suspicious condition. The result of find() is an iterator, but it is not properly checked.

#### Stl If Str Find {#CPPCHECK_STLISF}
Either inefficient or wrong usage of string::find(). string::compare() will be faster if string::find's result is compared with 0, because it will not scan the whole string. If your intention is to check that there are no findings in the string, you should compare with std::string::npos.

#### Stl Missing Comparison {#CPPCHECK_STLMC}
The iterator incrementing is suspicious - it is incremented at line  and then at line . The loop might unintentionally skip an element in the container. There is no comparison between these increments to prevent that the iterator is incremented beyond the end.

#### Stl Out Of Bounds {#CPPCHECK_STLOOB}
When i==foo.size(), foo\[i\] is out of bounds.

#### Stl Size {#CPPCHECK_STLS}
Checking for 'list' emptiness might be inefficient. Using list.empty() instead of list.size() can be faster. list.size() can take linear time but list.empty() is guaranteed to take constant time.

#### Stlcstr {#CPPCHECK_STLC}
Dangerous usage of c_str(). The c_str() return value is only valid until its string is deleted.

#### Stlcstr Param {#CPPCHECK_SCP}
The conversion from const char\* as returned by c_str() to std::string creates an unnecessary string copy. Solve that by directly passing the string.

#### Stlcstr Return {#CPPCHECK_SCR}
The conversion from const char\* as returned by c_str() to std::string creates an unnecessary string copy. Solve that by directly returning the string.

#### Stlcstr Throw {#CPPCHECK_SCT}
Dangerous usage of c_str(). The string is destroyed after the c_str() call so the thrown pointer is invalid.

#### Use Auto Pointer Array {#CPPCHECK_UAPA}
Object pointed by an 'auto_ptr' is destroyed using operator 'delete'. This means that you should only use 'auto_ptr' for pointers obtained with operator 'new'. This excludes arrays, which are allocated by operator 'new\[\]' and must be deallocated by operator 'delete\[\]'.

#### Use Auto Pointer Container {#CPPCHECK_UAPC}
An element of container must be able to be copied but 'auto_ptr' does not fulfill this requirement. You should consider to use 'shared_ptr' or 'unique_ptr'. It is suitable for use in containers, because they no longer copy their values, they move them.

#### Use Auto Pointer Copy {#CPPCHECK_UAPCPY}
'std::auto_ptr' has semantics of strict ownership, meaning that the 'auto_ptr' instance is the sole entity responsible for the object's lifetime. If an 'auto_ptr' is copied, the source looses the reference.

#### Use Auto Pointer Malloc {#CPPCHECK_UAPM}
Object pointed by an 'auto_ptr' is destroyed using operator 'delete'. You should not use 'auto_ptr' for pointers obtained with function 'malloc'. This means that you should only use 'auto_ptr' for pointers obtained with operator 'new'. This excludes use C library allocation functions (for example 'malloc'), which must be deallocated by the appropriate C library function.

#### Use STL Algorithm {#CPPCHECK_USA}
Consider using  algorithm instead of a raw loop.

#### Useless Calls Compare {#CPPCHECK_UCC}
'std::string::find()' returns zero when given itself as parameter (str.find(str)). As it is currently the code is inefficient. It is possible either the string searched ('str') or searched for ('str') is wrong.

#### Useless Calls Empty {#CPPCHECK_UCE}
Ineffective call of function 'empty()'. Did you intend to call 'clear()' instead?

#### Useless Calls Remove {#CPPCHECK_UCR}
The return value of std::remove() is ignored. This function returns an iterator to the end of the range containing those elements that should be kept. Elements past new end remain valid but with unspecified values. Use the erase method of the container to delete them.

#### Useless Calls Substr {#CPPCHECK_UCSS}
Ineffective call of function 'substr' because it returns a copy of the object. Use operator= instead.

#### Useless Calls Swap {#CPPCHECK_UCS}
The 'swap()' function has no logical effect when given itself as parameter (str.swap(str)). As it is currently the code is inefficient. Is the object or the parameter wrong here?

### Side Effect Rules

#### Assert With Side Effect {#CPPCHECK_AWSE}
Non-pure function: 'function' is called inside assert statement. Assert statements are removed from release builds so the code inside assert statement is not executed. If the code is needed also in release builds, this is a bug.

#### Assignment In Assert {#CPPCHECK_AIA}
Variable 'var' is modified insert assert statement. Assert statements are removed from release builds so the code inside assert statement is not executed. If the code is needed also in release builds, this is a bug.

#### Unknown Evaluation Order {#CPPCHECK_UEO}
Expression 'x = x++;' depends on order of evaluation of side effects

### Simple Type Rules

#### Assign Bool To Pointer {#CPPCHECK_ABTP}
Boolean value assigned to pointer.

#### Bitwise On Boolean {#CPPCHECK_BOB}
Boolean variable 'varname' is used in bitwise operation. Did you mean '&&'?

#### Char Bit Op {#CPPCHECK_CBO}
When using 'char' variables in bit operations, sign extension can generate unexpected results.

For example:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.cpp}
char c = 0x80;
int i = 0 | c;
if (i & 0x8000)
    printf("not expected");
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The "not expected" will be printed on the screen.

#### Char Literal With Char Ptr Compare {#CPPCHECK_CLWCPC}
Char literal compared with pointer 'foo'. Did you intend to dereference it?

#### Character Array Index {#CPPCHECK_CAI}
'char' type used as array index. Values greater that 127 will be treated depending on whether 'char' is signed or unsigned on target platform.

#### Check Cast Int To Char And Back {#CPPCHECK_CCITCAB}
When saving func_name() return value in char variable there is loss of precision.  When func_name() returns EOF this value is truncated. Comparing the char variable with EOF can have unexpected results. For instance a loop "while (EOF != (c = func_name());" loops forever on some compilers/platforms and on other compilers/platforms it will stop when the file contains a matching character.

#### Compare Bool Expression With Int {#CPPCHECK_CBEWI}
Comparison of a boolean expression with an integer other than 0 or 1.

#### Comparison Of Bool With Bool Error {#CPPCHECK_COBWBE}
The variable 'var_name' is of type 'bool' and comparing 'bool' value using relational (\<, >, \<= or >=) operator could cause unexpected results.

#### Comparison Of Func Returning Bool Error {#CPPCHECK_COFRBE}
The return type of function 'func_name' is 'bool' and result is of type 'bool'. Comparing 'bool' value using relational (\<, >, \<= or >=) operator could cause unexpected results.

#### Comparison Of Two Funcs Returning Bool Error {#CPPCHECK_COTFRBE}
The return type of function 'func_name1' and function 'func_name2' is 'bool' and result is of type 'bool'. Comparing 'bool' value using relational (\<, >, \<= or >=) operator could cause unexpected results.

#### Float Conversion Overflow {#CPPCHECK_FCO}
Undefined behaviour: float (1e+100) to integer conversion overflow.

#### Incorrect Char Boolean Error {#CPPCHECK_ICBE}
Conversion of char literal 'x' to bool always evaluates to true.

#### Incorrect String Boolean Error {#CPPCHECK_ISBE}
Conversion of string literal "Hello World" to bool always evaluates to true.

#### Incorrect String Compare {#CPPCHECK_ISC}
String literal "Hello World" doesn't match length argument for substr().

#### String Literal Write {#CPPCHECK_SLW}
Modifying string literal directly or indirectly is undefined behaviour.

#### Increment Boolean {#CPPCHECK_IB}
The operand of a postfix increment operator may be of type bool but it is deprecated by C++ Standard (Annex D-1) and the operand is always set to true. You should assign it the value 'true' instead.

#### Integer Overflow {#CPPCHECK_IO}
Signed integer overflow for expression ''.

#### Invalid Pointer Cast {#CPPCHECK_IPC}
Casting between float\* and double\* which have an incompatible binary data representation.

#### Memset Float {#CPPCHECK_MF}
The 2nd memset() argument 'varname' is a float, its representation is implementation defined. memset() is used to set each byte of a block of memory to a specific value and the actual representation of a floating-point value is implementation defined.

#### Pointer Arith Bool {#CPPCHECK_PAB}
Converting pointer arithmetic result to bool. The boolean result is always true unless there is pointer arithmetic overflow, and overflow is undefined behaviour. Probably a dereference is forgotten.

#### Pointer Less Than Zero {#CPPCHECK_PLTZ}
A pointer can not be negative so it is either pointless or an error to check if it is.

#### Pointer Positive {#CPPCHECK_PP}
A pointer can not be negative so it is either pointless or an error to check if it is not.

#### Shift By Negative {#CPPCHECK_SBN}
Shifting by a negative value is undefined behaviour

#### Shift Negative {#CPPCHECK_SN}
Shifting a negative value is technically undefined behaviour

#### Shift Too Many Bits {#CPPCHECK_STMB}
Shifting 32-bit value by 40 bits is undefined behaviour

#### Shift Too Many Bits Signed {#CPPCHECK_STMBS}
Shifting signed 32-bit value by 31 bits is undefined behaviour

#### Sign Conversion {#CPPCHECK_SC}
Suspicious code: sign conversion of var in calculation, even though var can have a negative value

#### Signed Char Array Index {#CPPCHECK_SCAI}
Signed 'char' type used as array index. If the value can be greater than 127 there will be a buffer underflow because of sign extension.

#### Sprintf Overlapping Data {#CPPCHECK_SOD}
The variable 'varname' is used both as a parameter and as destination in s[n]printf(). The origin and destination buffers overlap.
Quote from glibc (C-library) documentation (<http://www.gnu.org/software/libc/manual/html_mono/libc.html#Formatted-Output-Functions>): "If copying takes place between objects that overlap as a result of a call to sprintf() or snprintf(), the results are undefined."

#### Static String Compare {#CPPCHECK_SSC}
The compared strings, 'str1' and 'str2', are always unequal. Therefore the comparison is unnecessary and looks suspicious.

#### Str Plus Char {#CPPCHECK_SPC}
Unusual pointer arithmetic. A value of type 'char' is added to a string literal.

#### String Compare {#CPPCHECK_STRCMP}
The compared strings, 'varname1' and 'varname2', are identical. This could be a logic bug.

#### Trunc Long Cast Assignment {#CPPCHECK_TLCA}
int result is assigned to long variable. If the variable is long to avoid loss of information, then there is loss of information. To avoid loss of information you must cast a calculation operand to long, for example 'l = a \* b;' => 'l = (long)a \* b;'.

#### Trunc Long Cast Return {#CPPCHECK_TLCR}
int result is returned as long value. If the return value is long to avoid loss of information, then there is loss of information. To avoid loss of information you must cast a calculation operand to long, for example 'return a\*b;' => 'return (long)a\*b'.

#### Unsigned Less Than Zero {#CPPCHECK_ULTZ}
The unsigned variable 'varname' will never be negative so it is either pointless or an error to check if it is.

#### Unsigned Positive {#CPPCHECK_UP}
Unsigned variable 'varname' can't be negative so it is unnecessary to test it.

#### Variable Comparison With String Literal {#CPPCHECK_VCWSL}
String literal compared with variable 'foo'. Did you intend to use strcmp() instead?

### Sizeof Operator Rules

#### Arithmetic Operations On Void Pointer {#CPPCHECK_AOOVP}
'varname' is of type 'vartype'. When using void pointers in calculations, the behaviour is undefined. Arithmetic operations on 'void \*' is a GNU C extension, which defines the 'sizeof(void)' to be 1.

#### Divide Sizeof {#CPPCHECK_DSO}
Division of result of sizeof() on pointer type. sizeof() returns the size of the pointer, not the size of the memory area it points to.

#### Multiply Sizeof {#CPPCHECK_MSO}
Multiplying sizeof() with sizeof() indicates a logic error.

#### Pointer Size {#CPPCHECK_PS}
Size of pointer 'varname' used instead of size of its data. This is likely to lead to a buffer overflow. You probably intend to write 'sizeof(\*varname)'.

#### Sizeof Calculation {#CPPCHECK_SOC}
Found calculation inside sizeof().

#### Sizeof Dereferenced Void Pointer {#CPPCHECK_SODVP}
'\*varname' is of type 'void', the behaviour of 'sizeof(void)' is not covered by the ISO C standard. A value for 'sizeof(void)' is defined only as part of a GNU C extension, which defines 'sizeof(void)' to be 1.

#### Sizeof Division Memfunc {#CPPCHECK_SODMF}
Division by result of sizeof(). memset() expects a size in bytes, did you intend to multiply instead?

#### Sizeof Function Call {#CPPCHECK_SOFC}
Found function call inside sizeof().

#### Sizeof Sizeof {#CPPCHECK_SOSO}
Calling sizeof for 'sizeof looks like a suspicious code and most likely there should be just one 'sizeof'. The current code is equivalent to 'sizeof(size_t)'

#### Sizeof Void {#CPPCHECK_SOV}
Behaviour of 'sizeof(void)' is not covered by the ISO C standard. A value for 'sizeof(void)' is defined only as part of a GNU C extension, which defines 'sizeof(void)' to be 1.

#### Sizeof With Numeric Parameter {#CPPCHECK_SOWNP}
It is unusual to use a constant value with sizeof. For example, 'sizeof(10)' returns 4 (in 32-bit systems) or 8 (in 64-bit systems) instead of 10. 'sizeof('A')' and 'sizeof(char)' can return different results.

#### Sizeof With Silent Array Pointer {#CPPCHECK_SOWSAP}
Using 'sizeof' for array given as function argument returns the size of a pointer. It does not return the size of the whole array in bytes as might be expected.

For example, this code:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.cpp}
int f(char a[100]) {
	return sizeof(a);
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

returns 4 (in 32-bit systems) or 8 (in 64-bit systems) instead of 100 (the size of the array in bytes).

### Suspicious Construct Rules

#### Const Statement {#CPPCHECK_CS}
Redundant code: Found a statement that begins with type constant.

#### Duplicate Assign Expression {#CPPCHECK_DAE}
Finding variables 'x' and 'x' that are assigned the same expression is suspicious and might indicate a cut and paste or logic error. Please examine this code carefully to determine if it is correct.

#### Duplicate Branch {#CPPCHECK_DBRANCH}
Finding the same code in an 'if' and related 'else' branch is suspicious and might indicate a cut and paste or logic error. Please examine this code carefully to determine if it is correct.

#### Duplicate Expression {#CPPCHECK_DEXPR}
Finding the same expression on both sides of an operator is suspicious and might indicate a cut and paste or logic error. Please examine this code carefully to determine if it is correct.

#### Duplicate Expression Ternary {#CPPCHECK_DET}
Finding the same expression in both branches of ternary operator is suspicious as the same code is executed regardless of the condition.

#### Duplicate Value Ternary {#CPPCHECK_DVT}
Finding the same value in both branches of ternary operator is suspicious as the same code is executed regardless of the condition.

#### Mismatching Container Expression {#CPPCHECK_MCE}
Iterators to containers from different expressions 'v1' and 'v2' are used together.

#### Nan In Arithmetic Expression {#CPPCHECK_NIAE}
Using NaN/Inf in a computation. Although nothing bad really happens, it is suspicious.

#### Opposite Expression {#CPPCHECK_OPE}
Finding the opposite expression on both sides of an operator is suspicious and might indicate a cut and paste or logic error. Please examine this code carefully to determine if it is correct.

#### Overlapping Strcmp {#CPPCHECK_OS}
The expression 'strcmp(x,"def") != 0' is suspicious. It overlaps 'strcmp(x,"abc") == 0'.

#### Redundant Assign In Switch {#CPPCHECK_RAIS}
Variable 'var' is reassigned a value before the old one has been used. 'break;' missing?

#### Redundant Bitwise Operation In Switch {#CPPCHECK_RBOIS}
Redundant bitwise operation on 'varname' in 'switch' statement. 'break;' missing?

#### Redundant Copy In Switch {#CPPCHECK_RCIS}
Buffer 'var' is being written before its old content has been used. 'break;' missing?

#### Redundant Pointer Operation {#CPPCHECK_RPO}
Redundant pointer operation on 'varname' - it's already a pointer.

#### Return Address Of Auto Variable {#CPPCHECK_RNBIBF}
Non-boolean value returned from function returning bool

#### Self Assignment {#CPPCHECK_SA}
Redundant assignment of 'varname' to itself.

#### Suspicious Case {#CPPCHECK_SUSPC}
Using an operator like '||' in a case label is suspicious. Did you intend to use a bitwise operator, multiple case labels or if/else instead?

#### Suspicious Equality Comparison {#CPPCHECK_SEC}
Found suspicious equality comparison. Did you intend to assign a value instead?

#### Unused Scoped Object {#CPPCHECK_UUSO}
Instance of 'varname' object is destroyed immediately.

### Unnecessary and Unused Code Rules

#### Unassigned Variable {#CPPCHECK_UAV}
Variable 'varname' is not assigned a value.

#### Unread Variable {#CPPCHECK_URV}
Variable 'varname' is assigned a value that is never used.

#### Unused Allocated Memory {#CPPCHECK_UUAM}
Variable 'varname' is allocated memory that is never used.

#### Unused Function {#CPPCHECK_UUF}
The function 'funcName' is never used.

#### Unused Label {#CPPCHECK_UL}
Label '' is not used.

#### Unused Struct Member {#CPPCHECK_UUSM}
struct member 'structname::variable' is never used.

#### Unused Switch Label {#CPPCHECK_USL}
Label '' is not used. Should this be a 'case' of the enclosing switch()?

#### Unused Variable {#CPPCHECK_UUV}
Unused variable: varname

### Unreachable Code Rules

#### Duplicate Break {#CPPCHECK_DBREAK}
Consecutive return, break, continue, goto or throw statements are unnecessary. The second statement can never be executed, and so should be removed.

#### Unreachable Code {#CPPCHECK_URC}
Statements following return, break, continue, goto or throw will never be executed.

### Variable Argument Related Rules

#### Va_end Missing {#CPPCHECK_VAEM}
va_list 'vl' was opened but not closed by va_end().

#### Va_list Used Before Started {#CPPCHECK_VALUBS}
va_list 'vl' used before va_start() was called.

#### Va_start Reference Passed {#CPPCHECK_VASRP}
Using reference 'arg1' as parameter for va_start() results in undefined behaviour.

#### Va_start Subsequent Calls {#CPPCHECK_VASSC}
va_start() or va_copy() called subsequently on 'vl' without va_end() in between.

#### Va_start Wrong Parameter {#CPPCHECK_VASWP}
'arg1' given to va_start() is not last named argument of the function. Did you intend to pass 'arg2'?

#### Var Func Null UB {#CPPCHECK_VFNUB}
Passing NULL after the last typed argument to a variadic function leads to undefined behaviour.

The C99 standard, in section 7.15.1.1, states that if the type used by va_arg() is not compatible with the type of the actual next argument (as promoted according to the default argument promotions), the behavior is undefined.
The value of the NULL macro is an implementation-defined null pointer constant (7.17), which can be any integer constant expression with the value 0, or such an expression casted to (void\*) (6.3.2.3).
This includes values like 0, 0L, or even 0LL.
In practice on common architectures, this will cause real crashes if sizeof(int) != sizeof(void\*), and NULL is defined to 0 or any other null pointer constant that promotes to int.
To reproduce you might be able to use this little code example on 64bit platforms. 
If the output includes "ERROR", the sentinel had only 4 out of 8 bytes initialized to zero and was not detected as the final argument to stop argument processing via va_arg().
Changing the 0 to (void\*)0 or 0L will make the "ERROR" output go away.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.cpp}
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

void h() 
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
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

