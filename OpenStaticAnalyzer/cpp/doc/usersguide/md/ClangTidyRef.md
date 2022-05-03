## Reference of ClangTidy coding rule violations

clang-tidy is a clang-based C++ “linter” tool. Its purpose is to provide an extensible framework for diagnosing and fixing typical programming errors, like style violations, interface misuse, or bugs that can be deduced via static analysis. clang-tidy is modular and provides a convenient interface for writing new checks.

OpenStaticAnalyzer uses original clang-tidy checkers “as is”, without any guaranties that their results are correct. All statements of the clang-tidy license apply here as well.

The list of rulesets and rules contained in each ruleset are the following:

- **Abseil:** Checks related to Abseil library.

- **Altera:** Checks related to OpenCL programming for FPGAs.

- **Android:** Checks related to Android.

- **Boost:** Checks related to Boost library.

- **Bugprone:** Checks that target bugprone code constructs.

- **C++ Core Guidelines:** Checks related to C++ Core Guidelines.

- **Cert:** Checks related to CERT Secure Coding Guidelines.

- **Concurrency:** Checks related to concurrent programming (including threads, fibers, coroutines, etc.).

- **Darwin:** Checks related to Darwin coding conventions.

- **Fuchsia:** Checks related to Fuchsia coding conventions.

- **Google:** Checks related to Google coding conventions.

- **High Integrity C++:** Checks related to High Integrity C++ Coding Standard.

- **LLVM:** Checks related to the LLVM coding conventions.

- **LLVM-libc:** Checks related to the LLVM-libc coding standards.

- **Linux Kernel:** Checks related to the Linux Kernel coding conventions.

- **MPI:** Checks related to MPI (Message Passing Interface).

- **Miscellaneous:** Checks that we didn’t have a better category for.

- **Modernize:** Checks that advocate usage of modern (currently “modern” means “C++11”) language constructs.

- **Objective-C:** Checks related to Objective-C coding conventions.

- **OpenMP:** Checks related to OpenMP API.

- **Performance:** Checks that target performance-related issues.

- **Portability:** Checks that target portability-related issues that don’t relate to any particular coding style.

- **Readability:** Checks that target readability-related issues that don’t relate to any particular coding style

- **Static Analyzer - C++:** C++ checkers.

- **Static Analyzer - Core:** General-purpose checkers.

- **Static Analyzer - Core/Builtin:** Checkers for builtin functions.

- **Static Analyzer - Core/Uninitialized:** Checkers for initalization issues.

- **Static Analyzer - Dead Code:** Dead Code Checkers.

- **Static Analyzer - Fuchsia:** Checkers that can find various misuses of Fuchsia APIs.

- **Static Analyzer - Nullability:** Objective C checkers that warn for null pointer passing and dereferencing errors.

- **Static Analyzer - OptIn/C++:** Opt In C++ checkers.

- **Static Analyzer - OptIn/Cocoa Localizability:** Opt In macOS Cocoa localizability checkers.

- **Static Analyzer - OptIn/MPI:** Opt In MPI checkers.

- **Static Analyzer - OptIn/Performance:** Opt In performance checkers.

- **Static Analyzer - OptIn/Portability:** Opt In portability checkers.

- **Static Analyzer - OptIn/macOS:** Opt In macOS checkers.

- **Static Analyzer - Security:** Security related checkers.

- **Static Analyzer - Security/Insecure API:** Security related issues caused by inadequate API usage.

- **Static Analyzer - Unix:** POSIX/Unix checkers.

- **Static Analyzer - Unix/C string:** Checkers related to the C string.

- **Static Analyzer - Webkit:** Checkers that can find issues in WebKit codebase.

- **Static Analyzer - macOS:** macOS checkers.

- **Static Analyzer - macOS/Cocoa API:** macOS Cocoa API checkers

- **Static Analyzer - macOS/Core Foundation:** macOS Core Foundation checkers.

- **Static Analyzer - macOS/Core Foundation/Containers:** macOS Core Foundation container checkers.

- **Static Analyzer - va_list:** Checkers related to the usage of the va_list

- **Zircon:** Checks related to Zircon kernel coding conventions

The following table contains the enabled rules and their priorities:

  Category                                            Name                                             Abbreviation           Prio. 
  --------------------------------------------------- ------------------------------------------------ ---------------------- ------
  Abseil                                              Duration Addition                                CT_ABS_DA              Major 
                                                      Duration Comparison                              CT_ABS_DC              Major 
                                                      Duration Conversion Cast                         CT_ABS_DCC             Major 
                                                      Duration Division                                CT_ABS_DD              Major 
                                                      Duration Factory Float                           CT_ABS_DFF             Major 
                                                      Duration Factory Scale                           CT_ABS_DFS             Major 
                                                      Duration Subtraction                             CT_ABS_DS              Major 
                                                      Duration Unnecessary Conversion                  CT_ABS_DUC             Major 
                                                      Faster Strsplit Delimiter                        CT_ABS_FSD             Major 
                                                      No Internal Dependencies                         CT_ABS_NID             Major 
                                                      No Namespace                                     CT_ABS_NN              Major 
                                                      Redundant Strcat Calls                           CT_ABS_RSC             Major 
                                                      Str Cat Append                                   CT_ABS_SCA             Major 
                                                      String Find Startswith                           CT_ABS_SFS             Major 
                                                      String Find Str Contains                         CT_ABS_SFSC            Major 
                                                      Time Comparison                                  CT_ABS_TC              Major 
                                                      Time Subtraction                                 CT_ABS_TS              Major 
                                                      Upgrade Duration Conversions                     CT_ABS_UDC             Major 
  Altera                                              Kernel Name Restriction                          CT_ALT_KNR             Major 
                                                      Single Work Item Barrier                         CT_ALT_SWIB            Major 
                                                      Struct Pack Align                                CT_ALT_SPA             Major 
  Android                                             Cloexec Accept                                   CT_AND_CA2             Major 
                                                      Cloexec Accept4                                  CT_AND_CA              Major 
                                                      Cloexec Creat                                    CT_AND_CC              Major 
                                                      Cloexec Dup                                      CT_AND_CD              Major 
                                                      Cloexec Epoll Create                             CT_AND_CEC2            Major 
                                                      Cloexec Epoll Create1                            CT_AND_CEC             Major 
                                                      Cloexec Fopen                                    CT_AND_CF              Major 
                                                      Cloexec Inotify Init                             CT_AND_CII2            Major 
                                                      Cloexec Inotify Init1                            CT_AND_CII             Major 
                                                      Cloexec Memfd Create                             CT_AND_CMC             Major 
                                                      Cloexec Open                                     CT_AND_CO              Major 
                                                      Cloexec Pipe                                     CT_AND_CP2             Major 
                                                      Cloexec Pipe2                                    CT_AND_CP              Major 
                                                      Cloexec Socket                                   CT_AND_CS              Major 
                                                      Comparison In Temp Failure Retry                 CT_AND_CITFR           Major 
  Boost                                               Use To String                                    CT_BST_UTS             Major 
  Bugprone                                            Argument Comment                                 CT_BUG_AC              Major 
                                                      Assert Side Effect                               CT_BUG_ASE             Major 
                                                      Bad Signal To Kill Thread                        CT_BUG_BSTKT           Major 
                                                      Bool Pointer Implicit Conversion                 CT_BUG_BPIC            Major 
                                                      Branch Clone                                     CT_BUG_BC              Major 
                                                      Copy Constructor Init                            CT_BUG_CCI             Major 
                                                      Dangling Handle                                  CT_BUG_DH              Major 
                                                      Dynamic Static Initializers                      CT_BUG_DSI             Major 
                                                      Exception Escape                                 CT_BUG_EE              Major 
                                                      Fold Init Type                                   CT_BUG_FIT             Major 
                                                      Forward Declaration Namespace                    CT_BUG_FDN             Major 
                                                      Forwarding Reference Overload                    CT_BUG_FRO             Major 
                                                      Inaccurate Erase                                 CT_BUG_IE              Major 
                                                      Incorrect Roundings                              CT_BUG_IR              Major 
                                                      Infinite Loop                                    CT_BUG_IL              Major 
                                                      Integer Division                                 CT_BUG_ID              Major 
                                                      Lambda Function Name                             CT_BUG_LFN             Major 
                                                      Macro Parentheses                                CT_BUG_MP              Major 
                                                      Macro Repeated Side Effects                      CT_BUG_MRSE            Major 
                                                      Misplaced Operator In Strlen In Alloc            CT_BUG_MOISIA          Major 
                                                      Misplaced Pointer Arithmetic In Alloc            CT_BUG_MPAIA           Major 
                                                      Misplaced Widening Cast                          CT_BUG_MWC             Major 
                                                      Move Forwarding Reference                        CT_BUG_MFR             Major 
                                                      Multiple Statement Macro                         CT_BUG_MSM             Major 
                                                      Narrowing Conversions                            CT_BUG_NC              Major 
                                                      No Escape                                        CT_BUG_NE              Major 
                                                      Not Null Terminated Result                       CT_BUG_NNTR            Major 
                                                      Parent Virtual Call                              CT_BUG_PVC             Major 
                                                      Posix Return                                     CT_BUG_PR              Major 
                                                      Redundant Branch Condition                       CT_BUG_RBC             Major 
                                                      Reserved Identifier                              CT_BUG_RI              Major 
                                                      Signal Handler                                   CT_BUG_SH              Major 
                                                      Signed Char Misuse                               CT_BUG_SCM             Major 
                                                      Sizeof Container                                 CT_BUG_SC              Major 
                                                      Sizeof Expression                                CT_BUG_SE              Major 
                                                      Spuriously Wake Up Functions                     CT_BUG_SWUF            Major 
                                                      String Constructor                               CT_BUG_SC2             Major 
                                                      String Integer Assignment                        CT_BUG_SIA             Major 
                                                      String Literal With Embedded Nul                 CT_BUG_SLWEN           Major 
                                                      Suspicious Enum Usage                            CT_BUG_SEU             Major 
                                                      Suspicious Include                               CT_BUG_SI              Major 
                                                      Suspicious Memset Usage                          CT_BUG_SMU             Major 
                                                      Suspicious Missing Comma                         CT_BUG_SMC             Major 
                                                      Suspicious Semicolon                             CT_BUG_SS              Major 
                                                      Suspicious String Compare                        CT_BUG_SSC             Major 
                                                      Swapped Arguments                                CT_BUG_SA              Major 
                                                      Terminating Continue                             CT_BUG_TC              Major 
                                                      Throw Keyword Missing                            CT_BUG_TKM             Major 
                                                      Too Small Loop Variable                          CT_BUG_TSLV            Major 
                                                      Undefined Memory Manipulation                    CT_BUG_UMM             Major 
                                                      Undelegated Constructor                          CT_BUG_UC              Major 
                                                      Unhandled Self Assignment                        CT_BUG_USA             Major 
                                                      Unused Raii                                      CT_BUG_UR              Major 
                                                      Unused Return Value                              CT_BUG_URV             Major 
                                                      Use After Move                                   CT_BUG_UAM             Major 
                                                      Virtual Near Miss                                CT_BUG_VNM             Major 
  C++ Core Guidelines                                 Avoid C Arrays                                   CT_CPP_ACA             Major 
                                                      Avoid Goto                                       CT_CPP_AG              Major 
                                                      Avoid Magic Numbers                              CT_CPP_AMN             Major 
                                                      Avoid Non Const Global Variables                 CT_CPP_ANCGV           Major 
                                                      C Copy Assignment Signature                      CT_CPP_CCAS            Major 
                                                      Explicit Virtual Functions                       CT_CPP_EVF             Major 
                                                      Init Variables                                   CT_CPP_IV              Major 
                                                      Interfaces Global Init                           CT_CPP_IGI             Major 
                                                      Macro Usage                                      CT_CPP_MU              Major 
                                                      Narrowing Conversions                            CT_CPP_NC              Major 
                                                      No Malloc                                        CT_CPP_NM              Major 
                                                      Non Private Member Variables In Classes          CT_CPP_NPMVIC          Major 
                                                      Owning Memory                                    CT_CPP_OM              Major 
                                                      Prefer Member Initializer                        CT_CPP_PMI             Major 
                                                      Pro Bounds Array To Pointer Decay                CT_CPP_PBATPD          Major 
                                                      Pro Bounds Constant Array Index                  CT_CPP_PBCAI           Major 
                                                      Pro Bounds Pointer Arithmetic                    CT_CPP_PBPA            Major 
                                                      Pro Type Const Cast                              CT_CPP_PTCC            Major 
                                                      Pro Type Cstyle Cast                             CT_CPP_PTCC2           Major 
                                                      Pro Type Member Init                             CT_CPP_PTMI            Major 
                                                      Pro Type Reinterpret Cast                        CT_CPP_PTRC            Major 
                                                      Pro Type Static Cast Downcast                    CT_CPP_PTSCD           Major 
                                                      Pro Type Union Access                            CT_CPP_PTUA            Major 
                                                      Pro Type Vararg                                  CT_CPP_PTV             Major 
                                                      Slicing                                          CT_CPP_S               Major 
                                                      Special Member Functions                         CT_CPP_SMF             Major 
  Cert                                                Con36 C                                          CT_CRT_CON36_C         Major 
                                                      Con54 Cpp                                        CT_CRT_CON54_CPP       Major 
                                                      Dcl03 C                                          CT_CRT_DCL03_C         Major 
                                                      Dcl16 C                                          CT_CRT_DCL16_C         Major 
                                                      Dcl21 Cpp                                        CT_CRT_DCL21_CPP       Major 
                                                      Dcl37 C                                          CT_CRT_DCL37_C         Major 
                                                      Dcl50 Cpp                                        CT_CRT_DCL50_CPP       Major 
                                                      Dcl51 Cpp                                        CT_CRT_DCL51_CPP       Major 
                                                      Dcl54 Cpp                                        CT_CRT_DCL54_CPP       Major 
                                                      Dcl58 Cpp                                        CT_CRT_DCL58_CPP       Major 
                                                      Dcl59 Cpp                                        CT_CRT_DCL59_CPP       Major 
                                                      Env33 C                                          CT_CRT_ENV33_C         Major 
                                                      Err09 Cpp                                        CT_CRT_ERR09_CPP       Major 
                                                      Err34 C                                          CT_CRT_ERR34_C         Major 
                                                      Err52 Cpp                                        CT_CRT_ERR52_CPP       Major 
                                                      Err58 Cpp                                        CT_CRT_ERR58_CPP       Major 
                                                      Err60 Cpp                                        CT_CRT_ERR60_CPP       Major 
                                                      Err61 Cpp                                        CT_CRT_ERR61_CPP       Major 
                                                      Fio38 C                                          CT_CRT_FIO38_C         Major 
                                                      Flp30 C                                          CT_CRT_FLP30_C         Major 
                                                      Mem57 Cpp                                        CT_CRT_MEM57_CPP       Major 
                                                      Msc30 C                                          CT_CRT_MSC30_C         Major 
                                                      Msc32 C                                          CT_CRT_MSC32_C         Major 
                                                      Msc50 Cpp                                        CT_CRT_MSC50_CPP       Major 
                                                      Msc51 Cpp                                        CT_CRT_MSC51_CPP       Major 
                                                      Oop11 Cpp                                        CT_CRT_OOP11_CPP       Major 
                                                      Oop54 Cpp                                        CT_CRT_OOP54_CPP       Major 
                                                      Oop57 Cpp                                        CT_CRT_OOP57_CPP       Major 
                                                      Oop58 Cpp                                        CT_CRT_OOP58_CPP       Major 
                                                      Pos44 C                                          CT_CRT_POS44_C         Major 
                                                      Sig30 C                                          CT_CRT_SIG30_C         Major 
                                                      Str34 C                                          CT_CRT_STR34_C         Major 
  Concurrency                                         Mt Unsafe                                        CT_CON_MU              Major 
  Darwin                                              Avoid Spinlock                                   CT_DRW_AS              Major 
                                                      Dispatch Once Nonstatic                          CT_DRW_DON             Major 
  Fuchsia                                             Default Arguments Calls                          CT_FCS_DAC             Major 
                                                      Default Arguments Declarations                   CT_FCS_DAD             Major 
                                                      Header Anon Namespaces                           CT_FCS_HAN             Major 
                                                      Multiple Inheritance                             CT_FCS_MI              Major 
                                                      Overloaded Operator                              CT_FCS_OO              Major 
                                                      Statically Constructed Objects                   CT_FCS_SCO             Major 
                                                      Trailing Return                                  CT_FCS_TR              Major 
                                                      Virtual Inheritance                              CT_FCS_VI              Major 
  Google                                              Build Explicit Make Pair                         CT_GGL_BEMP            Major 
                                                      Build Namespaces                                 CT_GGL_BN              Major 
                                                      Build Using Namespace                            CT_GGL_BUN             Major 
                                                      Default Arguments                                CT_GGL_DA              Major 
                                                      Explicit Constructor                             CT_GGL_EC              Major 
                                                      Global Names In Headers                          CT_GGL_GNIH            Major 
                                                      Objc Avoid Nsobject New                          CT_GGL_OANN            Major 
                                                      Objc Avoid Throwing Exception                    CT_GGL_OATE            Major 
                                                      Objc Function Naming                             CT_GGL_OFN             Major 
                                                      Objc Global Variable Declaration                 CT_GGL_OGVD            Major 
                                                      Readability Avoid Underscore In Googletest Name  CT_GGL_RAUIGN          Major 
                                                      Readability Braces Around Statements             CT_GGL_RBAS            Major 
                                                      Readability Casting                              CT_GGL_RC              Major 
                                                      Readability Function Size                        CT_GGL_RFS             Major 
                                                      Readability Namespace Comments                   CT_GGL_RNC             Major 
                                                      Readability Todo                                 CT_GGL_RT              Major 
                                                      Runtime Int                                      CT_GGL_RI              Major 
                                                      Runtime Operator                                 CT_GGL_RO              Major 
                                                      Upgrade Googletest Case                          CT_GGL_UGC             Major 
  High Integrity C++                                  Avoid C Arrays                                   CT_HIC_ACA             Major 
                                                      Avoid Goto                                       CT_HIC_AG              Major 
                                                      Braces Around Statements                         CT_HIC_BAS             Major 
                                                      Deprecated Headers                               CT_HIC_DH              Major 
                                                      Exception Baseclass                              CT_HIC_EB              Major 
                                                      Explicit Conversions                             CT_HIC_EC              Major 
                                                      Function Size                                    CT_HIC_FS              Major 
                                                      Invalid Access Moved                             CT_HIC_IAM             Major 
                                                      Member Init                                      CT_HIC_MI              Major 
                                                      Move Const Arg                                   CT_HIC_MCA             Major 
                                                      Multiway Paths Covered                           CT_HIC_MPC             Major 
                                                      Named Parameter                                  CT_HIC_NP              Major 
                                                      New Delete Operators                             CT_HIC_NDO             Major 
                                                      No Array Decay                                   CT_HIC_NAD             Major 
                                                      No Assembler                                     CT_HIC_NA              Major 
                                                      No Malloc                                        CT_HIC_NM2             Major 
                                                      Noexcept Move                                    CT_HIC_NM              Major 
                                                      Signed Bitwise                                   CT_HIC_SB              Major 
                                                      Special Member Functions                         CT_HIC_SMF             Major 
                                                      Static Assert                                    CT_HIC_SA              Major 
                                                      Undelegated Constructor                          CT_HIC_UC              Major 
                                                      Uppercase Literal Suffix                         CT_HIC_ULS             Major 
                                                      Use Auto                                         CT_HIC_UA              Major 
                                                      Use Emplace                                      CT_HIC_UE              Major 
                                                      Use Equals Default                               CT_HIC_UED             Major 
                                                      Use Equals Delete                                CT_HIC_UED2            Major 
                                                      Use Noexcept                                     CT_HIC_UN              Major 
                                                      Use Nullptr                                      CT_HIC_UN2             Major 
                                                      Use Override                                     CT_HIC_UO              Major 
                                                      Vararg                                           CT_HIC_V               Major 
  LLVM                                                Else After Return                                CT_LLV_EAR             Major 
                                                      Header Guard                                     CT_LLV_HG              Major 
                                                      Include Order                                    CT_LLV_IO              Major 
                                                      Namespace Comment                                CT_LLV_NC              Major 
                                                      Prefer Isa Or Dyn Cast In Conditionals           CT_LLV_PIODCIC         Major 
                                                      Prefer Register Over Unsigned                    CT_LLV_PROU            Major 
                                                      Qualified Auto                                   CT_LLV_QA              Major 
                                                      Twine Local                                      CT_LLV_TL              Major 
  LLVM-libc                                           Callee Namespace                                 CT_LLC_CN              Major 
                                                      Implementation In Namespace                      CT_LLC_IIN             Major 
                                                      Restrict System Libc Headers                     CT_LLC_RSLH            Major 
  Linux Kernel                                        Must Check Errs                                  CT_KRN_MCE             Major 
  MPI                                                 Buffer Deref                                     CT_MPI_BD              Major 
                                                      Type Mismatch                                    CT_MPI_TM              Major 
  Miscellaneous                                       Definitions In Headers                           CT_MSC_DIH             Major 
                                                      Misplaced Const                                  CT_MSC_MC              Major 
                                                      New Delete Overloads                             CT_MSC_NDO             Major 
                                                      No Recursion                                     CT_MSC_NR              Major 
                                                      Non Copyable Objects                             CT_MSC_NCO             Major 
                                                      Non Private Member Variables In Classes          CT_MSC_NPMVIC          Major 
                                                      Redundant Expression                             CT_MSC_RE              Major 
                                                      Static Assert                                    CT_MSC_SA2             Major 
                                                      Throw By Value Catch By Reference                CT_MSC_TBVCBR          Major 
                                                      Unconventional Assign Operator                   CT_MSC_UAO             Major 
                                                      Uniqueptr Reset Release                          CT_MSC_URR             Major 
                                                      Unused Alias Decls                               CT_MSC_UAD             Major 
                                                      Unused Parameters                                CT_MSC_UP              Major 
                                                      Unused Using Decls                               CT_MSC_UUD             Major 
  Modernize                                           Avoid Bind                                       CT_MDR_AB              Major 
                                                      Avoid C Arrays                                   CT_MDR_ACA             Major 
                                                      Concat Nested Namespaces                         CT_MDR_CNN             Major 
                                                      Deprecated Headers                               CT_MDR_DH              Major 
                                                      Deprecated Ios Base Aliases                      CT_MDR_DIBA            Major 
                                                      Loop Convert                                     CT_MDR_LC              Major 
                                                      Make Shared                                      CT_MDR_MS              Major 
                                                      Make Unique                                      CT_MDR_MU              Major 
                                                      Pass By Value                                    CT_MDR_PBV             Major 
                                                      Raw String Literal                               CT_MDR_RSL             Major 
                                                      Redundant Void Arg                               CT_MDR_RVA             Major 
                                                      Replace Auto Ptr                                 CT_MDR_RAP             Major 
                                                      Replace Disallow Copy And Assign Macro           CT_MDR_RDCAAM          Major 
                                                      Replace Random Shuffle                           CT_MDR_RRS             Major 
                                                      Return Braced Init List                          CT_MDR_RBIL            Major 
                                                      Shrink To Fit                                    CT_MDR_STF             Major 
                                                      Unary Static Assert                              CT_MDR_USA             Major 
                                                      Use Auto                                         CT_MDR_UA              Major 
                                                      Use Bool Literals                                CT_MDR_UBL             Major 
                                                      Use Default Member Init                          CT_MDR_UDMI            Major 
                                                      Use Emplace                                      CT_MDR_UE              Major 
                                                      Use Equals Default                               CT_MDR_UED             Major 
                                                      Use Equals Delete                                CT_MDR_UED2            Major 
                                                      Use Nodiscard                                    CT_MDR_UN              Major 
                                                      Use Noexcept                                     CT_MDR_UN2             Major 
                                                      Use Nullptr                                      CT_MDR_UN3             Major 
                                                      Use Override                                     CT_MDR_UO              Major 
                                                      Use Trailing Return Type                         CT_MDR_UTRT            Major 
                                                      Use Transparent Functors                         CT_MDR_UTF             Major 
                                                      Use Uncaught Exceptions                          CT_MDR_UUE             Major 
                                                      Use Using                                        CT_MDR_UU              Major 
  Objective-C                                         Avoid Nserror Init                               CT_OBC_ANI             Major 
                                                      Dealloc In Category                              CT_OBC_DIC             Major 
                                                      Forbidden Subclassing                            CT_OBC_FS              Major 
                                                      Missing Hash                                     CT_OBC_MH              Major 
                                                      Nsinvocation Argument Lifetime                   CT_OBC_NAL             Major 
                                                      Property Declaration                             CT_OBC_PD              Major 
                                                      Super Self                                       CT_OBC_SS              Major 
  OpenMP                                              Exception Escape                                 CT_OMP_EE              Major 
                                                      Use Default None                                 CT_OMP_UDN             Major 
  Performance                                         Faster String Find                               CT_PRF_FSF             Major 
                                                      For Range Copy                                   CT_PRF_FRC             Major 
                                                      Implicit Conversion In Loop                      CT_PRF_ICIL            Major 
                                                      Inefficient Algorithm                            CT_PRF_IA              Major 
                                                      Inefficient String Concatenation                 CT_PRF_ISC             Major 
                                                      Inefficient Vector Operation                     CT_PRF_IVO             Major 
                                                      Move Const Arg                                   CT_PRF_MCA             Major 
                                                      Move Constructor Init                            CT_PRF_MCI             Major 
                                                      No Automatic Move                                CT_PRF_NAM             Major 
                                                      No Int To Ptr                                    CT_PRF_NITP            Major 
                                                      Noexcept Move Constructor                        CT_PRF_NMC             Major 
                                                      Trivially Destructible                           CT_PRF_TD              Major 
                                                      Type Promotion In Math Fn                        CT_PRF_TPIMF           Major 
                                                      Unnecessary Copy Initialization                  CT_PRF_UCI             Major 
                                                      Unnecessary Value Param                          CT_PRF_UVP             Major 
  Portability                                         Restrict System Includes                         CT_PRT_RSI             Major 
                                                      Simd Intrinsics                                  CT_PRT_SI              Major 
  Readability                                         Avoid Const Params In Decls                      CT_RDB_ACPID           Major 
                                                      Braces Around Statements                         CT_RDB_BAS             Major 
                                                      Const Return Type                                CT_RDB_CRT             Major 
                                                      Container Size Empty                             CT_RDB_CSE             Major 
                                                      Convert Member Functions To Static               CT_RDB_CMFTS           Major 
                                                      Delete Null Pointer                              CT_RDB_DNP             Major 
                                                      Deleted Default                                  CT_RDB_DD              Major 
                                                      Else After Return                                CT_RDB_EAR             Major 
                                                      Function Cognitive Complexity                    CT_RDB_FCC             Major 
                                                      Function Size                                    CT_RDB_FS              Major 
                                                      Identifier Naming                                CT_RDB_IN              Major 
                                                      Implicit Bool Conversion                         CT_RDB_IBC             Major 
                                                      Inconsistent Declaration Parameter Name          CT_RDB_IDPN            Major 
                                                      Isolate Declaration                              CT_RDB_ID              Major 
                                                      Magic Numbers                                    CT_RDB_MN              Major 
                                                      Make Member Function Const                       CT_RDB_MMFC            Major 
                                                      Misleading Indentation                           CT_RDB_MI              Major 
                                                      Misplaced Array Index                            CT_RDB_MAI             Major 
                                                      Named Parameter                                  CT_RDB_NP              Major 
                                                      Non Const Parameter                              CT_RDB_NCP             Major 
                                                      Qualified Auto                                   CT_RDB_QA              Major 
                                                      Redundant Access Specifiers                      CT_RDB_RAS             Major 
                                                      Redundant Control Flow                           CT_RDB_RCF             Major 
                                                      Redundant Declaration                            CT_RDB_RD              Major 
                                                      Redundant Function Ptr Dereference               CT_RDB_RFPD            Major 
                                                      Redundant Member Init                            CT_RDB_RMI             Major 
                                                      Redundant Preprocessor                           CT_RDB_RP              Major 
                                                      Redundant Smartptr Get                           CT_RDB_RSG             Major 
                                                      Redundant String Cstr                            CT_RDB_RSC             Major 
                                                      Redundant String Init                            CT_RDB_RSI             Major 
                                                      Simplify Boolean Expr                            CT_RDB_SBE             Major 
                                                      Simplify Subscript Expr                          CT_RDB_SSE             Major 
                                                      Static Accessed Through Instance                 CT_RDB_SATI            Major 
                                                      Static Definition In Anonymous Namespace         CT_RDB_SDIAN           Major 
                                                      String Compare                                   CT_RDB_SC              Major 
                                                      Uniqueptr Delete Release                         CT_RDB_UDR             Major 
                                                      Uppercase Literal Suffix                         CT_RDB_ULS             Major 
                                                      Use Anyofallof                                   CT_RDB_UA              Major 
  Static Analyzer - C++                               Inner Pointer                                    CT_SA_CPP_IP           Major 
                                                      Move                                             CT_SA_CPP_M            Major 
                                                      New Delete                                       CT_SA_CPP_ND           Major 
                                                      New Delete Leaks                                 CT_SA_CPP_NDL          Major 
                                                      Placement New Checker                            CT_SA_CPP_PNC          Major 
                                                      Pure Virtual Call                                CT_SA_CPP_PVC          Major 
                                                      Self Assignment                                  CT_SA_CPP_SA           Major 
  Static Analyzer - Core                              Call And Message                                 CT_SA_COR_CAM          Major 
                                                      Divide Zero                                      CT_SA_COR_DZ           Major 
                                                      Dynamic Type Propagation                         CT_SA_COR_DTP          Major 
                                                      Non Nil String Constants                         CT_SA_COR_NNSC         Major 
                                                      Non Null Param Checker                           CT_SA_COR_NNPC         Major 
                                                      Null Dereference                                 CT_SA_COR_ND           Major 
                                                      Stack Address Escape                             CT_SA_COR_SAE          Major 
                                                      Stack Address Escape Base                        CT_SA_COR_SAEB         Major 
                                                      Undefined Binary Operator Result                 CT_SA_COR_UBOR         Major 
                                                      VLA Size                                         CT_SA_COR_VS           Major 
  Static Analyzer - Core/Builtin                      Builtin Functions                                CT_SA_BLT_BF           Major 
                                                      No Return Functions                              CT_SA_BLT_NRF          Major 
  Static Analyzer - Core/Uninitialized                Array Subscript                                  CT_SA_UIN_AS           Major 
                                                      Assign                                           CT_SA_UIN_A            Major 
                                                      Branch                                           CT_SA_UIN_B            Major 
                                                      Captured Block Variable                          CT_SA_UIN_CBV          Major 
                                                      Undef Return                                     CT_SA_UIN_UR           Major 
  Static Analyzer - Dead Code                         Dead Stores                                      CT_SA_DCD_DS           Major 
  Static Analyzer - Fuchsia                           Handle Checker                                   CT_SA_FCS_HC           Major 
  Static Analyzer - Nullability                       Null Passed To Nonnull                           CT_SA_NUL_NPTN2        Major 
                                                      Null Returned From Nonnull                       CT_SA_NUL_NRFN2        Major 
                                                      Nullability Base                                 CT_SA_NUL_NB           Major 
                                                      Nullable Dereferenced                            CT_SA_NUL_ND           Major 
                                                      Nullable Passed To Nonnull                       CT_SA_NUL_NPTN         Major 
                                                      Nullable Returned From Nonnull                   CT_SA_NUL_NRFN         Major 
  Static Analyzer - OptIn/C++                         Uninitialized Object                             CT_SA_OI_CPP_UO        Major 
                                                      Virtual Call                                     CT_SA_OI_CPP_VC        Major 
  Static Analyzer - OptIn/Cocoa Localizability        Empty Localization Context Checker               CT_SA_OI_OSX_LOC_ELCC  Major 
                                                      Non Localized String Checker                     CT_SA_OI_OSX_LOC_NLSC  Major 
  Static Analyzer - OptIn/MPI                         MPI-Checker                                      CT_SA_OI_MPI_M         Major 
  Static Analyzer - OptIn/Performance                 GCD Antipattern                                  CT_SA_OI_PRF_GA        Major 
                                                      Padding                                          CT_SA_OI_PRF_P         Major 
  Static Analyzer - OptIn/Portability                 Unix API                                         CT_SA_OI_PRT_UA        Major 
  Static Analyzer - OptIn/macOS                       OSObject C-Style Cast                            CT_SA_OI_OSX_OCC       Major 
  Static Analyzer - Security                          Float Loop Counter                               CT_SA_SEC_FLC          Major 
  Static Analyzer - Security/Insecure API             Deprecated Or Unsafe Buffer Handling             CT_SA_SEC_DOUBH        Major 
                                                      Security Syntax Checker                          CT_SA_SEC_SSC          Major 
                                                      Unchecked Return                                 CT_SA_SEC_UR           Major 
                                                      bcmp                                             CT_SA_SEC_B            Major 
                                                      bcopy                                            CT_SA_SEC_B2           Major 
                                                      bzero                                            CT_SA_SEC_B3           Major 
                                                      decode Value Of ObjC Type                        CT_SA_SEC_DVOOT        Major 
                                                      getpw                                            CT_SA_SEC_G            Major 
                                                      gets                                             CT_SA_SEC_G2           Major 
                                                      mkstemp                                          CT_SA_SEC_M            Major 
                                                      mktemp                                           CT_SA_SEC_M2           Major 
                                                      rand                                             CT_SA_SEC_R            Major 
                                                      strcpy                                           CT_SA_SEC_S            Major 
                                                      vfork                                            CT_SA_SEC_V            Major 
  Static Analyzer - Unix                              API                                              CT_SA_UNX_A            Major 
                                                      Malloc                                           CT_SA_UNX_M            Major 
                                                      Malloc Sizeof                                    CT_SA_UNX_MS           Major 
                                                      Mismatched Deallocator                           CT_SA_UNX_MD           Major 
                                                      Vfork                                            CT_SA_UNX_V            Major 
  Static Analyzer - Unix/C string                     Bad Size Arg                                     CT_SA_UNX_BSA          Major 
                                                      Null Arg                                         CT_SA_UNX_NA           Major 
  Static Analyzer - Webkit                            No Uncounted Member Checker                      CT_SA_WBK_NUMC         Major 
                                                      Ref Cntbl Base Virtual Dtor                      CT_SA_WBK_RCBVD        Major 
                                                      Uncounted Lambda Captures Checker                CT_SA_WBK_ULCC         Major 
  Static Analyzer - macOS                             API                                              CT_SA_OSX_A            Major 
                                                      Mach Interface Generator Calling Convention      CT_SA_OSX_MIGCC        Major 
                                                      Ns Or CF Error Deref Checker                     CT_SA_OSX_NOCEDC       Major 
                                                      Number Object Conversion                         CT_SA_OSX_NOC          Major 
                                                      OSObject Retain Count                            CT_SA_OSX_ORC          Major 
                                                      Obj C Property                                   CT_SA_OSX_OCP          Major 
                                                      Sec Keychain API                                 CT_SA_OSX_SKA          Major 
  Static Analyzer - macOS/Cocoa API                   At Sync                                          CT_SA_OSX_CCA_AS       Major 
                                                      Autorelease Write                                CT_SA_OSX_CCA_AW       Major 
                                                      Class Release                                    CT_SA_OSX_CCA_CR       Major 
                                                      Dealloc                                          CT_SA_OSX_CCA_D        Major 
                                                      Incompatible Method Types                        CT_SA_OSX_CCA_IMT      Major 
                                                      Loops                                            CT_SA_OSX_CCA_L        Major 
                                                      Missing Super Call                               CT_SA_OSX_CCA_MSC      Major 
                                                      NS Autorelease Pool                              CT_SA_OSX_CCA_NAP      Major 
                                                      NS Error                                         CT_SA_OSX_CCA_NE       Major 
                                                      Nil Arg                                          CT_SA_OSX_CCA_NA       Major 
                                                      Non Nil Return Value                             CT_SA_OSX_CCA_NNRV     Major 
                                                      Obj C Generics                                   CT_SA_OSX_CCA_OCG      Major 
                                                      Retain Count                                     CT_SA_OSX_CCA_RC       Major 
                                                      Retain Count Base                                CT_SA_OSX_CCA_RCB      Major 
                                                      Run Loop Autorelease Leak                        CT_SA_OSX_CCA_RLAL     Major 
                                                      Self Init                                        CT_SA_OSX_CCA_SI       Major 
                                                      Super Dealloc                                    CT_SA_OSX_CCA_SD       Major 
                                                      Unused Ivars                                     CT_SA_OSX_CCA_UI       Major 
                                                      Variadic Method Types                            CT_SA_OSX_CCA_VMT      Major 
  Static Analyzer - macOS/Core Foundation             CF Error                                         CT_SA_OSX_CRF_CE       Major 
                                                      CF Number                                        CT_SA_OSX_CRF_CN       Major 
                                                      CF Retain Release                                CT_SA_OSX_CRF_CRR      Major 
  Static Analyzer - macOS/Core Foundation/Containers  Out Of Bounds                                    CT_SA_OSX_CRF_OOB      Major 
                                                      Pointer Sized Values                             CT_SA_OSX_CRF_PSV      Major 
  Static Analyzer - va_list                           Copy To Self                                     CT_SA_VAL_CTS          Major 
                                                      Uninitialized                                    CT_SA_VAL_U            Major 
                                                      Unterminated                                     CT_SA_VAL_U2           Major 
                                                      Valist Base                                      CT_SA_VAL_VB           Major 
  Zircon                                              Temporary Objects                                CT_ZRC_TO              Major 

### Abseil

#### Duration Addition {#CT_ABS_DA}
<p>Check for cases where addition should be performed in the absl::Time domain. When adding two values, and one is known to be an absl::Time, we can infer that the other should be interpreted as an absl::Duration of a similar scale, and make that inference explicit.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// Original - Addition in the integer domain</span>
<span class="dt">int</span> x;
absl::Time t;
<span class="dt">int</span> result = absl::ToUnixSeconds(t) + x;

<span class="co">// Suggestion - Addition in the absl::Time domain</span>
<span class="dt">int</span> result = absl::ToUnixSeconds(t + absl::Seconds(x));</code></pre></div>
<p>(Clang-Tidy original name: abseil-duration-addition)</p>


#### Duration Comparison {#CT_ABS_DC}
<p>Checks for comparisons which should be in the absl::Duration domain instead of the floating point or integer domains.</p>
<p>N.B.: In cases where a Duration was being converted to an integer and then compared against a floating-point value, truncation during the Duration conversion might yield a different result. In practice this is very rare, and still indicates a bug which should be fixed.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// Original - Comparison in the floating point domain</span>
<span class="dt">double</span> x;
absl::Duration d;
<span class="kw">if</span> (x &lt; absl::ToDoubleSeconds(d)) ...

<span class="co">// Suggested - Compare in the absl::Duration domain instead</span>
<span class="kw">if</span> (absl::Seconds(x) &lt; d) ...


<span class="co">// Original - Comparison in the integer domain</span>
<span class="dt">int</span> x;
absl::Duration d;
<span class="kw">if</span> (x &lt; absl::ToInt64Microseconds(d)) ...

<span class="co">// Suggested - Compare in the absl::Duration domain instead</span>
<span class="kw">if</span> (absl::Microseconds(x) &lt; d) ...</code></pre></div>
<p>(Clang-Tidy original name: abseil-duration-comparison)</p>


#### Duration Conversion Cast {#CT_ABS_DCC}
<p>Checks for casts of absl::Duration conversion functions, and recommends the right conversion function instead.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// Original - Cast from a double to an integer</span>
absl::Duration d;
<span class="dt">int</span> i = <span class="kw">static_cast</span>&lt;<span class="dt">int</span>&gt;(absl::ToDoubleSeconds(d));

<span class="co">// Suggested - Use the integer conversion function directly.</span>
<span class="dt">int</span> i = absl::ToInt64Seconds(d);


<span class="co">// Original - Cast from a double to an integer</span>
absl::Duration d;
<span class="dt">double</span> x = <span class="kw">static_cast</span>&lt;<span class="dt">double</span>&gt;(absl::ToInt64Seconds(d));

<span class="co">// Suggested - Use the integer conversion function directly.</span>
<span class="dt">double</span> x = absl::ToDoubleSeconds(d);</code></pre></div>
<p>Note: In the second example, the suggested fix could yield a different result, as the conversion to integer could truncate. In practice, this is very rare, and you should use absl::Trunc to perform this operation explicitly instead.</p>
<p>(Clang-Tidy original name: abseil-duration-conversion-cast)</p>


#### Duration Division {#CT_ABS_DD}
<p>absl::Duration arithmetic works like it does with integers. That means that division of two absl::Duration objects returns an int64 with any fractional component truncated toward 0. See <a href="https://github.com/abseil/abseil-cpp/blob/29ff6d4860070bf8fcbd39c8805d0c32d56628a3/absl/time/time.h#L137">this link</a> for more information on arithmetic with absl::Duration.</p>
<p>For example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">absl::Duration d = absl::Seconds(<span class="fl">3.5</span>);
int64 sec1 = d / absl::Seconds(<span class="dv">1</span>);     <span class="co">// Truncates toward 0.</span>
int64 sec2 = absl::ToInt64Seconds(d);  <span class="co">// Equivalent to division.</span>
assert(sec1 == <span class="dv">3</span> &amp;&amp; sec2 == <span class="dv">3</span>);

<span class="dt">double</span> dsec = d / absl::Seconds(<span class="dv">1</span>);  <span class="co">// WRONG: Still truncates toward 0.</span>
assert(dsec == <span class="fl">3.0</span>);</code></pre></div>
<p>If you want floating-point division, you should use either the absl::FDivDuration() function, or one of the unit conversion functions such as absl::ToDoubleSeconds(). For example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">absl::Duration d = absl::Seconds(<span class="fl">3.5</span>);
<span class="dt">double</span> dsec1 = absl::FDivDuration(d, absl::Seconds(<span class="dv">1</span>));  <span class="co">// GOOD: No truncation.</span>
<span class="dt">double</span> dsec2 = absl::ToDoubleSeconds(d);                 <span class="co">// GOOD: No truncation.</span>
assert(dsec1 == <span class="fl">3.5</span> &amp;&amp; dsec2 == <span class="fl">3.5</span>);</code></pre></div>
<p>This check looks for uses of absl::Duration division that is done in a floating-point context, and recommends the use of a function that returns a floating-point value.</p>
<p>(Clang-Tidy original name: abseil-duration-division)</p>


#### Duration Factory Float {#CT_ABS_DFF}
<p>Checks for cases where the floating-point overloads of various absl::Duration factory functions are called when the more-efficient integer versions could be used instead.</p>
<p>This check will not suggest fixes for literals which contain fractional floating point values or non-literals. It will suggest removing superfluous casts.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// Original - Providing a floating-point literal.</span>
absl::Duration d = absl::Seconds(<span class="fl">10.0</span>);

<span class="co">// Suggested - Use an integer instead.</span>
absl::Duration d = absl::Seconds(<span class="dv">10</span>);


<span class="co">// Original - Explicitly casting to a floating-point type.</span>
absl::Duration d = absl::Seconds(<span class="kw">static_cast</span>&lt;<span class="dt">double</span>&gt;(<span class="dv">10</span>));

<span class="co">// Suggested - Remove the explicit cast</span>
absl::Duration d = absl::Seconds(<span class="dv">10</span>);</code></pre></div>
<p>(Clang-Tidy original name: abseil-duration-factory-float)</p>


#### Duration Factory Scale {#CT_ABS_DFS}
<p>Checks for cases where arguments to absl::Duration factory functions are scaled internally and could be changed to a different factory function. This check also looks for arguments with a zero value and suggests using absl::ZeroDuration() instead.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// Original - Internal multiplication.</span>
<span class="dt">int</span> x;
absl::Duration d = absl::Seconds(<span class="dv">60</span> * x);

<span class="co">// Suggested - Use absl::Minutes instead.</span>
absl::Duration d = absl::Minutes(x);


<span class="co">// Original - Internal division.</span>
<span class="dt">int</span> y;
absl::Duration d = absl::Milliseconds(y / <span class="fl">1000.</span>);

<span class="co">// Suggested - Use absl:::Seconds instead.</span>
absl::Duration d = absl::Seconds(y);


<span class="co">// Original - Zero-value argument.</span>
absl::Duration d = absl::Hours(<span class="dv">0</span>);

<span class="co">// Suggested = Use absl::ZeroDuration instead</span>
absl::Duration d = absl::ZeroDuration();</code></pre></div>
<p>(Clang-Tidy original name: abseil-duration-factory-scale)</p>


#### Duration Subtraction {#CT_ABS_DS}
<p>Checks for cases where subtraction should be performed in the absl::Duration domain. When subtracting two values, and the first one is known to be a conversion from absl::Duration, we can infer that the second should also be interpreted as an absl::Duration, and make that inference explicit.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// Original - Subtraction in the double domain</span>
<span class="dt">double</span> x;
absl::Duration d;
<span class="dt">double</span> result = absl::ToDoubleSeconds(d) - x;

<span class="co">// Suggestion - Subtraction in the absl::Duration domain instead</span>
<span class="dt">double</span> result = absl::ToDoubleSeconds(d - absl::Seconds(x));

<span class="co">// Original - Subtraction of two Durations in the double domain</span>
absl::Duration d1, d2;
<span class="dt">double</span> result = absl::ToDoubleSeconds(d1) - absl::ToDoubleSeconds(d2);

<span class="co">// Suggestion - Subtraction in the absl::Duration domain instead</span>
<span class="dt">double</span> result = absl::ToDoubleSeconds(d1 - d2);</code></pre></div>
<p>Note: As with other clang-tidy checks, it is possible that multiple fixes may overlap (as in the case of nested expressions), so not all occurrences can be transformed in one run. In particular, this may occur for nested subtraction expressions. Running clang-tidy multiple times will find and fix these overlaps.</p>
<p>(Clang-Tidy original name: abseil-duration-subtraction)</p>


#### Duration Unnecessary Conversion {#CT_ABS_DUC}
<p>Finds and fixes cases where absl::Duration values are being converted to numeric types and back again.</p>
<p>Floating-point examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// Original - Conversion to double and back again</span>
absl::Duration d1;
absl::Duration d2 = absl::Seconds(absl::ToDoubleSeconds(d1));

<span class="co">// Suggestion - Remove unnecessary conversions</span>
absl::Duration d2 = d1;

<span class="co">// Original - Division to convert to double and back again</span>
absl::Duration d2 = absl::Seconds(absl::FDivDuration(d1, absl::Seconds(<span class="dv">1</span>)));

<span class="co">// Suggestion - Remove division and conversion</span>
absl::Duration d2 = d1;</code></pre></div>
<p>Integer examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// Original - Conversion to integer and back again</span>
absl::Duration d1;
absl::Duration d2 = absl::Hours(absl::ToInt64Hours(d1));

<span class="co">// Suggestion - Remove unnecessary conversions</span>
absl::Duration d2 = d1;

<span class="co">// Original - Integer division followed by conversion</span>
absl::Duration d2 = absl::Seconds(d1 / absl::Seconds(<span class="dv">1</span>));

<span class="co">// Suggestion - Remove division and conversion</span>
absl::Duration d2 = d1;</code></pre></div>
<p>Unwrapping scalar operations:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// Original - Multiplication by a scalar</span>
absl::Duration d1;
absl::Duration d2 = absl::Seconds(absl::ToInt64Seconds(d1) * <span class="dv">2</span>);

<span class="co">// Suggestion - Remove unnecessary conversion</span>
absl::Duration d2 = d1 * <span class="dv">2</span>;</code></pre></div>
<p>Note: Converting to an integer and back to an absl::Duration might be a truncating operation if the value is not aligned to the scale of conversion. In the rare case where this is the intended result, callers should use absl::Trunc to truncate explicitly.</p>
<p>(Clang-Tidy original name: abseil-duration-unnecessary-conversion)</p>


#### Faster Strsplit Delimiter {#CT_ABS_FSD}
<p>Finds instances of absl::StrSplit() or absl::MaxSplits() where the delimiter is a single character string literal and replaces with a character. The check will offer a suggestion to change the string literal into a character. It will also catch code using absl::ByAnyChar() for just a single character and will transform that into a single character as well.</p>
<p>These changes will give the same result, but using characters rather than single character string literals is more efficient and readable.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// Original - the argument is a string literal.</span>
<span class="kw">for</span> (<span class="kw">auto</span> piece : absl::StrSplit(str, <span class="st">&quot;B&quot;</span>)) {

<span class="co">// Suggested - the argument is a character, which causes the more efficient</span>
<span class="co">// overload of absl::StrSplit() to be used.</span>
<span class="kw">for</span> (<span class="kw">auto</span> piece : absl::StrSplit(str, <span class="st">&#39;B&#39;</span>)) {


<span class="co">// Original - the argument is a string literal inside absl::ByAnyChar call.</span>
<span class="kw">for</span> (<span class="kw">auto</span> piece : absl::StrSplit(str, absl::ByAnyChar(<span class="st">&quot;B&quot;</span>))) {

<span class="co">// Suggested - the argument is a character, which causes the more efficient</span>
<span class="co">// overload of absl::StrSplit() to be used and we do not need absl::ByAnyChar</span>
<span class="co">// anymore.</span>
<span class="kw">for</span> (<span class="kw">auto</span> piece : absl::StrSplit(str, <span class="st">&#39;B&#39;</span>)) {


<span class="co">// Original - the argument is a string literal inside absl::MaxSplits call.</span>
<span class="kw">for</span> (<span class="kw">auto</span> piece : absl::StrSplit(str, absl::MaxSplits(<span class="st">&quot;B&quot;</span>, <span class="dv">1</span>))) {

<span class="co">// Suggested - the argument is a character, which causes the more efficient</span>
<span class="co">// overload of absl::StrSplit() to be used.</span>
<span class="kw">for</span> (<span class="kw">auto</span> piece : absl::StrSplit(str, absl::MaxSplits(<span class="st">&#39;B&#39;</span>, <span class="dv">1</span>))) {</code></pre></div>
<p>(Clang-Tidy original name: abseil-faster-strsplit-delimiter)</p>


#### No Internal Dependencies {#CT_ABS_NID}
<p>Warns if code using Abseil depends on internal details. If something is in a namespace that includes the word “internal”, code is not allowed to depend upon it beaucse it’s an implementation detail. They cannot friend it, include it, you mention it or refer to it in any way. Doing so violates Abseil’s compatibility guidelines and may result in breakage. See <a href="https://abseil.io/about/compatibility" class="uri">https://abseil.io/about/compatibility</a> for more information.</p>
<p>The following cases will result in warnings:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">absl::strings_internal::foo();
<span class="co">// warning triggered on this line</span>
<span class="kw">class</span> foo {
  <span class="kw">friend</span> <span class="kw">struct</span> absl::container_internal::faa;
  <span class="co">// warning triggered on this line</span>
};
absl::memory_internal::MakeUniqueResult();
<span class="co">// warning triggered on this line</span></code></pre></div>
<p>(Clang-Tidy original name: abseil-no-internal-dependencies)</p>


#### No Namespace {#CT_ABS_NN}
<p>Ensures code does not open namespace absl as that violates Abseil’s compatibility guidelines. Code should not open namespace absl as that conflicts with Abseil’s compatibility guidelines and may result in breakage.</p>
<p>Any code that uses:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">namespace</span> absl {
 ...
}</code></pre></div>
<p>will be prompted with a warning.</p>
<p>See <a href="https://abseil.io/about/compatibility">the full Abseil compatibility guidelines</a> for more information.</p>
<p>(Clang-Tidy original name: abseil-no-namespace)</p>


#### Redundant Strcat Calls {#CT_ABS_RSC}
<p>Suggests removal of unnecessary calls to absl::StrCat when the result is being passed to another call to absl::StrCat or absl::StrAppend.</p>
<p>The extra calls cause unnecessary temporary strings to be constructed. Removing them makes the code smaller and faster.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::string s = absl::StrCat(<span class="st">&quot;A&quot;</span>, absl::StrCat(<span class="st">&quot;B&quot;</span>, absl::StrCat(<span class="st">&quot;C&quot;</span>, <span class="st">&quot;D&quot;</span>)));
<span class="co">//before</span>

std::string s = absl::StrCat(<span class="st">&quot;A&quot;</span>, <span class="st">&quot;B&quot;</span>, <span class="st">&quot;C&quot;</span>, <span class="st">&quot;D&quot;</span>);
<span class="co">//after</span>

absl::StrAppend(&amp;s, absl::StrCat(<span class="st">&quot;E&quot;</span>, <span class="st">&quot;F&quot;</span>, <span class="st">&quot;G&quot;</span>));
<span class="co">//before</span>

absl::StrAppend(&amp;s, <span class="st">&quot;E&quot;</span>, <span class="st">&quot;F&quot;</span>, <span class="st">&quot;G&quot;</span>);
<span class="co">//after</span></code></pre></div>
<p>(Clang-Tidy original name: abseil-redundant-strcat-calls)</p>


#### Str Cat Append {#CT_ABS_SCA}
<p>Flags uses of absl::StrCat() to append to a std::string. Suggests absl::StrAppend() should be used instead.</p>
<p>The extra calls cause unnecessary temporary strings to be constructed. Removing them makes the code smaller and faster.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">a = absl::StrCat(a, b); <span class="co">// Use absl::StrAppend(&amp;a, b) instead.</span></code></pre></div>
<p>Does not diagnose cases where absl::StrCat() is used as a template argument for a functor.</p>
<p>(Clang-Tidy original name: abseil-str-cat-append)</p>


#### String Find Startswith {#CT_ABS_SFS}
<p>Checks whether a std::string::find() result is compared with 0, and suggests replacing with absl::StartsWith(). This is both a readability and performance issue.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">string s = <span class="st">&quot;...&quot;</span>;
<span class="kw">if</span> (s.find(<span class="st">&quot;Hello World&quot;</span>) == <span class="dv">0</span>) { <span class="co">/* do something */</span> }</code></pre></div>
<p>becomes</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">string s = <span class="st">&quot;...&quot;</span>;
<span class="kw">if</span> (absl::StartsWith(s, <span class="st">&quot;Hello World&quot;</span>)) { <span class="co">/* do something */</span> }</code></pre></div>
<h5 id="options-72">Options</h5>
<p>StringLikeClasses</p>
<p>Semicolon-separated list of names of string-like classes. By default only std::basic_string is considered. The list of methods to considered is fixed.</p>
<p>IncludeStyle</p>
<p>A string specifying which include-style is used, llvm or google. Default is llvm.</p>
<p>AbseilStringsMatchHeader</p>
<p>The location of Abseil’s strings/match.h. Defaults to absl/strings/match.h.</p>
<p>(Clang-Tidy original name: abseil-string-find-startswith)</p>


#### String Find Str Contains {#CT_ABS_SFSC}
<p>Finds s.find(...) == string::npos comparisons (for various string-like types) and suggests replacing with absl::StrContains().</p>
<p>This improves readability and reduces the likelihood of accidentally mixing find() and npos from different string-like types.</p>
<p>By default, “string-like types” includes ::std::basic_string, ::std::basic_string_view, and ::absl::string_view. See the StringLikeClasses option to change this.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::string s = <span class="st">&quot;...&quot;</span>;
<span class="kw">if</span> (s.find(<span class="st">&quot;Hello World&quot;</span>) == std::string::npos) { <span class="co">/* do something */</span> }

absl::string_view a = <span class="st">&quot;...&quot;</span>;
<span class="kw">if</span> (absl::string_view::npos != a.find(<span class="st">&quot;Hello World&quot;</span>)) { <span class="co">/* do something */</span> }</code></pre></div>
<p>becomes</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::string s = <span class="st">&quot;...&quot;</span>;
<span class="kw">if</span> (!absl::StrContains(s, <span class="st">&quot;Hello World&quot;</span>)) { <span class="co">/* do something */</span> }

absl::string_view a = <span class="st">&quot;...&quot;</span>;
<span class="kw">if</span> (absl::StrContains(a, <span class="st">&quot;Hello World&quot;</span>)) { <span class="co">/* do something */</span> }</code></pre></div>
<h5 id="options-14">Options</h5>
<p>StringLikeClasses</p>
<p>Semicolon-separated list of names of string-like classes. By default includes ::std::basic_string, ::std::basic_string_view, and ::absl::string_view.</p>
<p>IncludeStyle</p>
<p>A string specifying which include-style is used, llvm or google. Default is llvm.</p>
<p>AbseilStringsMatchHeader</p>
<p>The location of Abseil’s strings/match.h. Defaults to absl/strings/match.h.</p>
<p>(Clang-Tidy original name: abseil-string-find-str-contains)</p>


#### Time Comparison {#CT_ABS_TC}
<p>Prefer comparisons in the absl::Time domain instead of the integer domain.</p>
<p>N.B.: In cases where an absl::Time is being converted to an integer, alignment may occur. If the comparison depends on this alignment, doing the comparison in the absl::Time domain may yield a different result. In practice this is very rare, and still indicates a bug which should be fixed.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// Original - Comparison in the integer domain</span>
<span class="dt">int</span> x;
absl::Time t;
<span class="kw">if</span> (x &lt; absl::ToUnixSeconds(t)) ...

<span class="co">// Suggested - Compare in the absl::Time domain instead</span>
<span class="kw">if</span> (absl::FromUnixSeconds(x) &lt; t) ...</code></pre></div>
<p>(Clang-Tidy original name: abseil-time-comparison)</p>


#### Time Subtraction {#CT_ABS_TS}
<p>Finds and fixes absl::Time subtraction expressions to do subtraction in the Time domain instead of the numeric domain.</p>
<p>There are two cases of Time subtraction in which deduce additional type information:</p>
<ul>
<li>When the result is an absl::Duration and the first argument is an absl::Time.</li>
<li>When the second argument is a absl::Time.</li>
</ul>
<p>In the first case, we must know the result of the operation, since without that the second operand could be either an absl::Time or an absl::Duration. In the second case, the first operand <em>must</em> be an absl::Time, because subtracting an absl::Time from an absl::Duration is not defined.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">int</span> x;
absl::Time t;

<span class="co">// Original - absl::Duration result and first operand is a absl::Time.</span>
absl::Duration d = absl::Seconds(absl::ToUnixSeconds(t) - x);

<span class="co">// Suggestion - Perform subtraction in the Time domain instead.</span>
absl::Duration d = t - absl::FromUnixSeconds(x);


<span class="co">// Original - Second operand is an absl::Time.</span>
<span class="dt">int</span> i = x - absl::ToUnixSeconds(t);

<span class="co">// Suggestion - Perform subtraction in the Time domain instead.</span>
<span class="dt">int</span> i = absl::ToInt64Seconds(absl::FromUnixSeconds(x) - t);</code></pre></div>
<p>(Clang-Tidy original name: abseil-time-subtraction)</p>


#### Upgrade Duration Conversions {#CT_ABS_UDC}
<p>Finds calls to absl::Duration arithmetic operators and factories whose argument needs an explicit cast to continue compiling after upcoming API changes.</p>
<p>The operators <em>=, /=, </em>, and / for absl::Duration currently accept an argument of class type that is convertible to an arithmetic type. Such a call currently converts the value to an int64_t, even in a case such as std::atomic<float> that would result in lossy conversion.</p>
<p>Additionally, the absl::Duration factory functions (absl::Hours, absl::Minutes, etc) currently accept an int64_t or a floating-point type. Similar to the arithmetic operators, calls with an argument of class type that is convertible to an arithmetic type go through the int64_t path.</p>
<p>These operators and factories will be changed to only accept arithmetic types to prevent unintended behavior. After these changes are released, passing an argument of class type will no longer compile, even if the type is implicitly convertible to an arithmetic type.</p>
<p>Here are example fixes created by this check:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::atomic&lt;<span class="dt">int</span>&gt; a;
absl::Duration d = absl::Milliseconds(a);
d *= a;</code></pre></div>
<p>becomes</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::atomic&lt;<span class="dt">int</span>&gt; a;
absl::Duration d = absl::Milliseconds(<span class="kw">static_cast</span>&lt;<span class="dt">int64_t</span>&gt;(a));
d *= <span class="kw">static_cast</span>&lt;<span class="dt">int64_t</span>&gt;(a);</code></pre></div>
<p>Note that this check always adds a cast to int64_t in order to preserve the current behavior of user code. It is possible that this uncovers unintended behavior due to types implicitly convertible to a floating-point type.</p>
<p>(Clang-Tidy original name: abseil-upgrade-duration-conversions)</p>


### Altera

#### Kernel Name Restriction {#CT_ALT_KNR}
<p>Finds kernel files and include directives whose filename is kernel.cl, Verilog.cl, or VHDL.cl. The check is case insensitive.</p>
<p>Such kernel file names cause the offline compiler to generate intermediate design files that have the same names as certain internal files, which leads to a compilation error.</p>
<p>Based on the Guidelines for Naming the Kernel section in the <a href="https://www.intel.com/content/www/us/en/programmable/documentation/mwh1391807965224.html#ewa1412973930963">Intel FPGA SDK for OpenCL Pro Edition: Programming Guide</a>.</p>
<p>(Clang-Tidy original name: altera-kernel-name-restriction)</p>


#### Single Work Item Barrier {#CT_ALT_SWIB}
<p>Finds OpenCL kernel functions that call a barrier function but do not call an ID function (get_local_id, get_local_id, get_group_id, or get_local_linear_id).</p>
<p>These kernels may be viable single work-item kernels, but will be forced to execute as NDRange kernels if using a newer version of the Altera Offline Compiler (&gt;= v17.01).</p>
<p>If using an older version of the Altera Offline Compiler, these kernel functions will be treated as single work-item kernels, which could be inefficient or lead to errors if NDRange semantics were intended.</p>
<p>Based on the <a href="https://www.altera.com/en_US/pdfs/literature/hb/opencl-sdk/aocl_optimization_guide.pdf">Altera SDK for OpenCL: Best Practices Guide</a>.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// error: function calls barrier but does not call an ID function.</span>
<span class="dt">void</span> __kernel barrier_no_id(__global <span class="dt">int</span> * foo, <span class="dt">int</span> size) {
  <span class="kw">for</span> (<span class="dt">int</span> i = <span class="dv">0</span>; i &lt; <span class="dv">100</span>; i++) {
    foo[i] += <span class="dv">5</span>;
  }
  barrier(CLK_GLOBAL_MEM_FENCE);
}

<span class="co">// ok: function calls barrier and an ID function.</span>
<span class="dt">void</span> __kernel barrier_with_id(__global <span class="dt">int</span> * foo, <span class="dt">int</span> size) {
  <span class="kw">for</span> (<span class="dt">int</span> i = <span class="dv">0</span>; i &lt; <span class="dv">100</span>; i++) {
    <span class="dt">int</span> tid = get_global_id(<span class="dv">0</span>);
    foo[tid] += <span class="dv">5</span>;
  }
  barrier(CLK_GLOBAL_MEM_FENCE);
}

<span class="co">// ok with AOC Version 17.01: the reqd_work_group_size turns this into</span>
<span class="co">// an NDRange.</span>
<span class="ot">__attribute__</span>((reqd_work_group_size(<span class="dv">2</span>,<span class="dv">2</span>,<span class="dv">2</span>)))
<span class="dt">void</span> __kernel barrier_with_id(__global <span class="dt">int</span> * foo, <span class="dt">int</span> size) {
  <span class="kw">for</span> (<span class="dt">int</span> i = <span class="dv">0</span>; i &lt; <span class="dv">100</span>; i++) {
    foo[tid] += <span class="dv">5</span>;
  }
  barrier(CLK_GLOBAL_MEM_FENCE);
}</code></pre></div>
<h5 id="options-44">Options</h5>
<p>AOCVersion</p>
<p>Defines the version of the Altera Offline Compiler. Defaults to 1600 (corresponding to version 16.00).</p>
<p>(Clang-Tidy original name: altera-single-work-item-barrier)</p>


#### Struct Pack Align {#CT_ALT_SPA}
<p>Finds structs that are inefficiently packed or aligned, and recommends packing and/or aligning of said structs as needed.</p>
<p>Structs that are not packed take up more space than they should, and accessing structs that are not well aligned is inefficient.</p>
<p>Fix-its are provided to fix both of these issues by inserting and/or amending relevant struct attributes.</p>
<p>Based on the <a href="https://www.altera.com/en_US/pdfs/literature/hb/opencl-sdk/aocl_optimization_guide.pdf">Altera SDK for OpenCL: Best Practices Guide</a>.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// The following struct is originally aligned to 4 bytes, and thus takes up</span>
<span class="co">// 12 bytes of memory instead of 10. Packing the struct will make it use</span>
<span class="co">// only 10 bytes of memory, and aligning it to 16 bytes will make it</span>
<span class="co">// efficient to access.</span>
<span class="kw">struct</span> example {
  <span class="dt">char</span> a;    <span class="co">// 1 byte</span>
  <span class="dt">double</span> b;  <span class="co">// 8 bytes</span>
  <span class="dt">char</span> c;    <span class="co">// 1 byte</span>
};

<span class="co">// The following struct is arranged in such a way that packing is not needed.</span>
<span class="co">// However, it is aligned to 4 bytes instead of 8, and thus needs to be</span>
<span class="co">// explicitly aligned.</span>
<span class="kw">struct</span> implicitly_packed_example {
  <span class="dt">char</span> a;  <span class="co">// 1 byte</span>
  <span class="dt">char</span> b;  <span class="co">// 1 byte</span>
  <span class="dt">char</span> c;  <span class="co">// 1 byte</span>
  <span class="dt">char</span> d;  <span class="co">// 1 byte</span>
  <span class="dt">int</span> e;   <span class="co">// 4 bytes</span>
};

<span class="co">// The following struct is explicitly aligned and packed.</span>
<span class="kw">struct</span> good_example {
  <span class="dt">char</span> a;    <span class="co">// 1 byte</span>
  <span class="dt">double</span> b;  <span class="co">// 8 bytes</span>
  <span class="dt">char</span> c;    <span class="co">// 1 byte</span>
} <span class="ot">__attribute__</span>((packed)) <span class="ot">__attribute__</span>((aligned(<span class="dv">16</span>));

<span class="co">// Explicitly aligning a struct to the wrong value will result in a warning.</span>
<span class="co">// The following example should be aligned to 16 bytes, not 32.</span>
<span class="kw">struct</span> badly_aligned_example {
  <span class="dt">char</span> a;    <span class="co">// 1 byte</span>
  <span class="dt">double</span> b;  <span class="co">// 8 bytes</span>
  <span class="dt">char</span> c;    <span class="co">// 1 byte</span>
} <span class="ot">__attribute__</span>((packed)) <span class="ot">__attribute__</span>((aligned(<span class="dv">32</span>)));</code></pre></div>
<p>(Clang-Tidy original name: altera-struct-pack-align)</p>


### Android

#### Cloexec Accept {#CT_AND_CA2}
<p>The usage of accept() is not recommended, it’s better to use accept4(). Without this flag, an opened sensitive file descriptor would remain open across a fork+exec to a lower-privileged SELinux domain.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">accept(sockfd, addr, addrlen);

<span class="co">// becomes</span>

accept4(sockfd, addr, addrlen, SOCK_CLOEXEC);</code></pre></div>
<p>(Clang-Tidy original name: android-cloexec-accept)</p>


#### Cloexec Accept4 {#CT_AND_CA}
<p>accept4() should include SOCK_CLOEXEC in its type argument to avoid the file descriptor leakage. Without this flag, an opened sensitive file would remain open across a fork+exec to a lower-privileged SELinux domain.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">accept4(sockfd, addr, addrlen, SOCK_NONBLOCK);

<span class="co">// becomes</span>

accept4(sockfd, addr, addrlen, SOCK_NONBLOCK | SOCK_CLOEXEC);</code></pre></div>
<p>(Clang-Tidy original name: android-cloexec-accept4)</p>


#### Cloexec Creat {#CT_AND_CC}
<p>The usage of creat() is not recommended, it’s better to use open().</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">int</span> fd = creat(path, mode);

<span class="co">// becomes</span>

<span class="dt">int</span> fd = open(path, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, mode);</code></pre></div>
<p>(Clang-Tidy original name: android-cloexec-creat)</p>


#### Cloexec Dup {#CT_AND_CD}
<p>The usage of dup() is not recommended, it’s better to use fcntl(), which can set the close-on-exec flag. Otherwise, an opened sensitive file would remain open across a fork+exec to a lower-privileged SELinux domain.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">int</span> fd = dup(oldfd);

<span class="co">// becomes</span>

<span class="dt">int</span> fd = fcntl(oldfd, F_DUPFD_CLOEXEC);</code></pre></div>
<p>(Clang-Tidy original name: android-cloexec-dup)</p>


#### Cloexec Epoll Create {#CT_AND_CEC2}
<p>The usage of epoll_create() is not recommended, it’s better to use epoll_create1(), which allows close-on-exec.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">epoll_create(size);

<span class="co">// becomes</span>

epoll_create1(EPOLL_CLOEXEC);</code></pre></div>
<p>(Clang-Tidy original name: android-cloexec-epoll-create)</p>


#### Cloexec Epoll Create1 {#CT_AND_CEC}
<p>epoll_create1() should include EPOLL_CLOEXEC in its type argument to avoid the file descriptor leakage. Without this flag, an opened sensitive file would remain open across a fork+exec to a lower-privileged SELinux domain.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">epoll_create1(<span class="dv">0</span>);

<span class="co">// becomes</span>

epoll_create1(EPOLL_CLOEXEC);</code></pre></div>
<p>(Clang-Tidy original name: android-cloexec-epoll-create1)</p>


#### Cloexec Fopen {#CT_AND_CF}
<p>fopen() should include e in their mode string; so re would be valid. This is equivalent to having set FD_CLOEXEC on that descriptor.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">fopen(<span class="st">&quot;fn&quot;</span>, <span class="st">&quot;r&quot;</span>);

<span class="co">// becomes</span>

fopen(<span class="st">&quot;fn&quot;</span>, <span class="st">&quot;re&quot;</span>);</code></pre></div>
<p>(Clang-Tidy original name: android-cloexec-fopen)</p>


#### Cloexec Inotify Init {#CT_AND_CII2}
<p>The usage of inotify_init() is not recommended, it’s better to use inotify_init1().</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">inotify_init();

<span class="co">// becomes</span>

inotify_init1(IN_CLOEXEC);</code></pre></div>
<p>(Clang-Tidy original name: android-cloexec-inotify-init)</p>


#### Cloexec Inotify Init1 {#CT_AND_CII}
<p>inotify_init1() should include IN_CLOEXEC in its type argument to avoid the file descriptor leakage. Without this flag, an opened sensitive file would remain open across a fork+exec to a lower-privileged SELinux domain.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">inotify_init1(IN_NONBLOCK);

<span class="co">// becomes</span>

inotify_init1(IN_NONBLOCK | IN_CLOEXEC);</code></pre></div>
<p>(Clang-Tidy original name: android-cloexec-inotify-init1)</p>


#### Cloexec Memfd Create {#CT_AND_CMC}
<p>memfd_create() should include MFD_CLOEXEC in its type argument to avoid the file descriptor leakage. Without this flag, an opened sensitive file would remain open across a fork+exec to a lower-privileged SELinux domain.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">memfd_create(name, MFD_ALLOW_SEALING);

<span class="co">// becomes</span>

memfd_create(name, MFD_ALLOW_SEALING | MFD_CLOEXEC);</code></pre></div>
<p>(Clang-Tidy original name: android-cloexec-memfd-create)</p>


#### Cloexec Open {#CT_AND_CO}
<p>A common source of security bugs is code that opens a file without using the O_CLOEXEC flag. Without that flag, an opened sensitive file would remain open across a fork+exec to a lower-privileged SELinux domain, leaking that sensitive data. Open-like functions including open(), openat(), and open64() should include O_CLOEXEC in their flags argument.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">open(<span class="st">&quot;filename&quot;</span>, O_RDWR);
open64(<span class="st">&quot;filename&quot;</span>, O_RDWR);
openat(<span class="dv">0</span>, <span class="st">&quot;filename&quot;</span>, O_RDWR);

<span class="co">// becomes</span>

open(<span class="st">&quot;filename&quot;</span>, O_RDWR | O_CLOEXEC);
open64(<span class="st">&quot;filename&quot;</span>, O_RDWR | O_CLOEXEC);
openat(<span class="dv">0</span>, <span class="st">&quot;filename&quot;</span>, O_RDWR | O_CLOEXEC);</code></pre></div>
<p>(Clang-Tidy original name: android-cloexec-open)</p>


#### Cloexec Pipe {#CT_AND_CP2}
<p>This check detects usage of pipe(). Using pipe() is not recommended, pipe2() is the suggested replacement. The check also adds the O_CLOEXEC flag that marks the file descriptor to be closed in child processes. Without this flag a sensitive file descriptor can be leaked to a child process, potentially into a lower-privileged SELinux domain.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">pipe(pipefd);</code></pre></div>
<p>Suggested replacement:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">pipe2(pipefd, O_CLOEXEC);</code></pre></div>
<p>(Clang-Tidy original name: android-cloexec-pipe)</p>


#### Cloexec Pipe2 {#CT_AND_CP}
<p>This checks ensures that pipe2() is called with the O_CLOEXEC flag. The check also adds the O_CLOEXEC flag that marks the file descriptor to be closed in child processes. Without this flag a sensitive file descriptor can be leaked to a child process, potentially into a lower-privileged SELinux domain.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">pipe2(pipefd, O_NONBLOCK);</code></pre></div>
<p>Suggested replacement:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">pipe2(pipefd, O_NONBLOCK | O_CLOEXEC);</code></pre></div>
<p>(Clang-Tidy original name: android-cloexec-pipe2)</p>


#### Cloexec Socket {#CT_AND_CS}
<p>socket() should include SOCK_CLOEXEC in its type argument to avoid the file descriptor leakage. Without this flag, an opened sensitive file would remain open across a fork+exec to a lower-privileged SELinux domain.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">socket(domain, type, SOCK_STREAM);

<span class="co">// becomes</span>

socket(domain, type, SOCK_STREAM | SOCK_CLOEXEC);</code></pre></div>
<p>(Clang-Tidy original name: android-cloexec-socket)</p>


#### Comparison In Temp Failure Retry {#CT_AND_CITFR}
<p>Diagnoses comparisons that appear to be incorrectly placed in the argument to the TEMP_FAILURE_RETRY macro. Having such a use is incorrect in the vast majority of cases, and will often silently defeat the purpose of the TEMP_FAILURE_RETRY macro.</p>
<p>For context, TEMP_FAILURE_RETRY is <a href="https://www.gnu.org/software/libc/manual/html_node/Interrupted-Primitives.html">a convenience macro</a> provided by both glibc and Bionic. Its purpose is to repeatedly run a syscall until it either succeeds, or fails for reasons other than being interrupted.</p>
<p>Example buggy usage looks like:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">char</span> cs[<span class="dv">1</span>];
<span class="kw">while</span> (TEMP_FAILURE_RETRY(read(STDIN_FILENO, cs, <span class="kw">sizeof</span>(cs)) != <span class="dv">0</span>)) {
  <span class="co">// Do something with cs.</span>
}</code></pre></div>
<p>Because TEMP_FAILURE_RETRY will check for whether the result <em>of the comparison</em> is -1, and retry if so.</p>
<p>If you encounter this, the fix is simple: lift the comparison out of the TEMP_FAILURE_RETRY argument, like so:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">char</span> cs[<span class="dv">1</span>];
<span class="kw">while</span> (TEMP_FAILURE_RETRY(read(STDIN_FILENO, cs, <span class="kw">sizeof</span>(cs))) != <span class="dv">0</span>) {
  <span class="co">// Do something with cs.</span>
}</code></pre></div>
<h5 id="options-50">Options</h5>
<p>RetryMacros</p>
<p>A comma-separated list of the names of retry macros to be checked.</p>
<p>(Clang-Tidy original name: android-comparison-in-temp-failure-retry)</p>


### Boost

#### Use To String {#CT_BST_UTS}
<p>This check finds conversion from integer type like int to std::string or std::wstring using boost::lexical_cast, and replace it with calls to std::to_string and std::to_wstring.</p>
<p>It doesn’t replace conversion from floating points despite the to_string overloads, because it would change the behaviour.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">auto</span> str = boost::lexical_cast&lt;std::string&gt;(<span class="dv">42</span>);
<span class="kw">auto</span> wstr = boost::lexical_cast&lt;std::wstring&gt;(<span class="dv">2137LL</span>);

<span class="co">// Will be changed to</span>
<span class="kw">auto</span> str = std::to_string(<span class="dv">42</span>);
<span class="kw">auto</span> wstr = std::to_wstring(<span class="dv">2137LL</span>);</code></pre></div>
<p>(Clang-Tidy original name: boost-use-to-string)</p>


### Bugprone

#### Argument Comment {#CT_BUG_AC}
<p>Checks that argument comments match parameter names.</p>
<p>The check understands argument comments in the form /<em>parameter_name=</em>/ that are placed right before the argument.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> f(<span class="dt">bool</span> foo);

...

f(<span class="co">/*bar=*/</span><span class="kw">true</span>);
<span class="co">// warning: argument name &#39;bar&#39; in comment does not match parameter name &#39;foo&#39;</span></code></pre></div>
<p>The check tries to detect typos and suggest automated fixes for them.</p>
<h5 id="options-49">Options</h5>
<p>StrictMode</p>
<p>When false (default value), the check will ignore leading and trailing underscores and case when comparing names – otherwise they are taken into account.</p>
<p>IgnoreSingleArgument</p>
<p>When true, the check will ignore the single argument.</p>
<p>CommentBoolLiterals</p>
<p>When true, the check will add argument comments in the format /<em>ParameterName=</em>/ right before the boolean literal argument.</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> foo(<span class="dt">bool</span> TurnKey, <span class="dt">bool</span> PressButton);

foo(<span class="kw">true</span>, <span class="kw">false</span>);</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> foo(<span class="dt">bool</span> TurnKey, <span class="dt">bool</span> PressButton);

foo(<span class="co">/*TurnKey=*/</span><span class="kw">true</span>, <span class="co">/*PressButton=*/</span><span class="kw">false</span>);</code></pre></div>
<p>CommentIntegerLiterals</p>
<p>When true, the check will add argument comments in the format /<em>ParameterName=</em>/ right before the integer literal argument.</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> foo(<span class="dt">int</span> MeaningOfLife);

foo(<span class="dv">42</span>);</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> foo(<span class="dt">int</span> MeaningOfLife);

foo(<span class="co">/*MeaningOfLife=*/</span><span class="dv">42</span>);</code></pre></div>
<p>CommentFloatLiterals</p>
<p>When true, the check will add argument comments in the format /<em>ParameterName=</em>/ right before the float/double literal argument.</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> foo(<span class="dt">float</span> Pi);

foo(<span class="fl">3.14159</span>);</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> foo(<span class="dt">float</span> Pi);

foo(<span class="co">/*Pi=*/</span><span class="fl">3.14159</span>);</code></pre></div>
<p>CommentStringLiterals</p>
<p>When true, the check will add argument comments in the format /<em>ParameterName=</em>/ right before the string literal argument.</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> foo(<span class="dt">const</span> <span class="dt">char</span> *String);
<span class="dt">void</span> foo(<span class="dt">const</span> <span class="dt">wchar_t</span> *WideString);

foo(<span class="st">&quot;Hello World&quot;</span>);
foo(<span class="st">L&quot;Hello World&quot;</span>);</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> foo(<span class="dt">const</span> <span class="dt">char</span> *String);
<span class="dt">void</span> foo(<span class="dt">const</span> <span class="dt">wchar_t</span> *WideString);

foo(<span class="co">/*String=*/</span><span class="st">&quot;Hello World&quot;</span>);
foo(<span class="co">/*WideString=*/</span><span class="st">L&quot;Hello World&quot;</span>);</code></pre></div>
<p>CommentCharacterLiterals</p>
<p>When true, the check will add argument comments in the format /<em>ParameterName=</em>/ right before the character literal argument.</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> foo(<span class="dt">char</span> *Character);

foo(<span class="st">&#39;A&#39;</span>);</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> foo(<span class="dt">char</span> *Character);

foo(<span class="co">/*Character=*/</span><span class="st">&#39;A&#39;</span>);</code></pre></div>
<p>CommentUserDefinedLiterals</p>
<p>When true, the check will add argument comments in the format /<em>ParameterName=</em>/ right before the user defined literal argument.</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> foo(<span class="dt">double</span> Distance);

<span class="dt">double</span> <span class="kw">operator</span><span class="st">&quot;&quot;</span> _km(<span class="dt">long</span> <span class="dt">double</span>);

foo(<span class="fl">402.0</span>_km);</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> foo(<span class="dt">double</span> Distance);

<span class="dt">double</span> <span class="kw">operator</span><span class="st">&quot;&quot;</span> _km(<span class="dt">long</span> <span class="dt">double</span>);

foo(<span class="co">/*Distance=*/</span><span class="fl">402.0</span>_km);</code></pre></div>
<p>CommentNullPtrs</p>
<p>When true, the check will add argument comments in the format /<em>ParameterName=</em>/ right before the nullptr literal argument.</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> foo(A* Value);

foo(<span class="kw">nullptr</span>);</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> foo(A* Value);

foo(<span class="co">/*Value=*/</span><span class="kw">nullptr</span>);</code></pre></div>
<p>(Clang-Tidy original name: bugprone-argument-comment)</p>


#### Assert Side Effect {#CT_BUG_ASE}
<p>Finds assert() with side effect.</p>
<p>The condition of assert() is evaluated only in debug builds so a condition with side effect can cause different behavior in debug / release builds.</p>
<h5 id="options-16">Options</h5>
<p>AssertMacros</p>
<p>A comma-separated list of the names of assert macros to be checked.</p>
<p>CheckFunctionCalls</p>
<p>Whether to treat non-const member and non-member functions as they produce side effects. Disabled by default because it can increase the number of false positive warnings.</p>
<p>(Clang-Tidy original name: bugprone-assert-side-effect)</p>


#### Bad Signal To Kill Thread {#CT_BUG_BSTKT}
<p>Finds pthread_kill function calls when a thread is terminated by raising SIGTERM signal and the signal kills the entire process, not just the individual thread. Use any signal except SIGTERM.</p>
<p>This check corresponds to the CERT C Coding Standard rule <a href="https://wiki.sei.cmu.edu/confluence/display/c/POS44-C.+Do+not+use+signals+to+terminate+threads">POS44-C. Do not use signals to terminate threads</a>.</p>
<p>(Clang-Tidy original name: bugprone-bad-signal-to-kill-thread)</p>


#### Bool Pointer Implicit Conversion {#CT_BUG_BPIC}
<p>Checks for conditions based on implicit conversion from a bool pointer to bool.</p>
<p>Example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">bool</span> *p;
<span class="kw">if</span> (p) {
  <span class="co">// Never used in a pointer-specific way.</span>
}</code></pre></div>
<p>(Clang-Tidy original name: bugprone-bool-pointer-implicit-conversion)</p>


#### Branch Clone {#CT_BUG_BC}
<p>Checks for repeated branches in if/else if/else chains, consecutive repeated branches in switch statements and identical true and false branches in conditional operators.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">if</span> (test_value(x)) {
  y++;
  do_something(x, y);
} <span class="kw">else</span> {
  y++;
  do_something(x, y);
}</code></pre></div>
<p>In this simple example (which could arise e.g. as a copy-paste error) the then and else branches are identical and the code is equivalent the following shorter and cleaner code:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">test_value(x); <span class="co">// can be omitted unless it has side effects</span>
y++;
do_something(x, y);</code></pre></div>
<p>If this is the intended behavior, then there is no reason to use a conditional statement; otherwise the issue can be solved by fixing the branch that is handled incorrectly.</p>
<p>The check also detects repeated branches in longer if/else if/else chains where it would be even harder to notice the problem.</p>
<p>In switch statements the check only reports repeated branches when they are consecutive, because it is relatively common that the case: labels have some natural ordering and rearranging them would decrease the readability of the code. For example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">switch</span> (ch) {
<span class="kw">case</span> <span class="st">&#39;a&#39;</span>:
  <span class="kw">return</span> <span class="dv">10</span>;
<span class="kw">case</span> <span class="st">&#39;A&#39;</span>:
  <span class="kw">return</span> <span class="dv">10</span>;
<span class="kw">case</span> <span class="st">&#39;b&#39;</span>:
  <span class="kw">return</span> <span class="dv">11</span>;
<span class="kw">case</span> <span class="st">&#39;B&#39;</span>:
  <span class="kw">return</span> <span class="dv">11</span>;
<span class="kw">default</span>:
  <span class="kw">return</span> <span class="dv">10</span>;
}</code></pre></div>
<p>Here the check reports that the 'a' and 'A' branches are identical (and that the 'b' and 'B' branches are also identical), but does not report that the default: branch is also identical to the first two branches. If this is indeed the correct behavior, then it could be implemented as:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">switch</span> (ch) {
<span class="kw">case</span> <span class="st">&#39;a&#39;</span>:
<span class="kw">case</span> <span class="st">&#39;A&#39;</span>:
  <span class="kw">return</span> <span class="dv">10</span>;
<span class="kw">case</span> <span class="st">&#39;b&#39;</span>:
<span class="kw">case</span> <span class="st">&#39;B&#39;</span>:
  <span class="kw">return</span> <span class="dv">11</span>;
<span class="kw">default</span>:
  <span class="kw">return</span> <span class="dv">10</span>;
}</code></pre></div>
<p>Here the check does not warn for the repeated return 10;, which is good if we want to preserve that 'a' is before 'b' and default: is the last branch.</p>
<p>Finally, the check also examines conditional operators and reports code like:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">return</span> test_value(x) ? x : x;</code></pre></div>
<p>Unlike if statements, the check does not detect chains of conditional operators.</p>
<p>Note: This check also reports situations where branches become identical only after preprocession.</p>
<p>(Clang-Tidy original name: bugprone-branch-clone)</p>


#### Copy Constructor Init {#CT_BUG_CCI}
<p>Finds copy constructors where the constructor doesn’t call the copy constructor of the base class.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> Copyable {
<span class="kw">public</span>:
  Copyable() = <span class="kw">default</span>;
  Copyable(<span class="dt">const</span> Copyable &amp;) = <span class="kw">default</span>;
};
<span class="kw">class</span> X2 : <span class="kw">public</span> Copyable {
  X2(<span class="dt">const</span> X2 &amp;other) {} <span class="co">// Copyable(other) is missing</span>
};</code></pre></div>
<p>Also finds copy constructors where the constructor of the base class don’t have parameter.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> X4 : <span class="kw">public</span> Copyable {
  X4(<span class="dt">const</span> X4 &amp;other) : Copyable() {} <span class="co">// other is missing</span>
};</code></pre></div>
<p>The check also suggests a fix-its in some cases.</p>
<p>(Clang-Tidy original name: bugprone-copy-constructor-init)</p>


#### Dangling Handle {#CT_BUG_DH}
<p>Detect dangling references in value handles like std::experimental::string_view. These dangling references can be a result of constructing handles from temporary values, where the temporary is destroyed soon after the handle is created.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">string_view View = string();  <span class="co">// View will dangle.</span>
string A;
View = A + <span class="st">&quot;A&quot;</span>;  <span class="co">// still dangle.</span>

vector&lt;string_view&gt; V;
V.push_back(string());  <span class="co">// V[0] is dangling.</span>
V.resize(<span class="dv">3</span>, string());  <span class="co">// V[1] and V[2] will also dangle.</span>

string_view f() {
  <span class="co">// All these return values will dangle.</span>
  <span class="kw">return</span> string();
  string S;
  <span class="kw">return</span> S;
  <span class="dt">char</span> Array[<span class="dv">10</span>]{};
  <span class="kw">return</span> Array;
}</code></pre></div>
<h5 id="options-4">Options</h5>
<p>HandleClasses</p>
<p>A semicolon-separated list of class names that should be treated as handles. By default only std::experimental::basic_string_view is considered.</p>
<p>(Clang-Tidy original name: bugprone-dangling-handle)</p>


#### Dynamic Static Initializers {#CT_BUG_DSI}
<p>Finds instances of static variables that are dynamically initialized in header files.</p>
<p>This can pose problems in certain multithreaded contexts. For example, when disabling compiler generated synchronization instructions for static variables initialized at runtime (e.g. by -fno-threadsafe-statics), even if a particular project takes the necessary precautions to prevent race conditions during initialization by providing their own synchronization, header files included from other projects may not. Therefore, such a check is helpful for ensuring that disabling compiler generated synchronization for static variable initialization will not cause problems.</p>
<p>Consider the following code:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">int</span> foo() {
  <span class="dt">static</span> <span class="dt">int</span> k = bar();
  <span class="kw">return</span> k;
}</code></pre></div>
<p>When synchronization of static initialization is disabled, if two threads both call foo for the first time, there is the possibility that k will be double initialized, creating a race condition.</p>
<p>(Clang-Tidy original name: bugprone-dynamic-static-initializers)</p>


#### Exception Escape {#CT_BUG_EE}
<p>Finds functions which may throw an exception directly or indirectly, but they should not. The functions which should not throw exceptions are the following:</p>
<ul>
<li>Destructors</li>
<li>Move constructors</li>
<li>Move assignment operators</li>
<li>The main() functions</li>
<li>swap() functions</li>
<li>Functions marked with throw() or noexcept</li>
<li>Other functions given as option</li>
</ul>
<p>A destructor throwing an exception may result in undefined behavior, resource leaks or unexpected termination of the program. Throwing move constructor or move assignment also may result in undefined behavior or resource leak. The swap() operations expected to be non throwing most of the cases and they are always possible to implement in a non throwing way. Non throwing swap() operations are also used to create move operations. A throwing main() function also results in unexpected termination.</p>
<p>WARNING! This check may be expensive on large source files.</p>
<h5 id="options-42">Options</h5>
<p>FunctionsThatShouldNotThrow</p>
<p>Comma separated list containing function names which should not throw. An example value for this parameter can be WinMain which adds function WinMain() in the Windows API to the list of the functions which should not throw. Default value is an empty string.</p>
<p>IgnoredExceptions</p>
<p>Comma separated list containing type names which are not counted as thrown exceptions in the check. Default value is an empty string.</p>
<p>(Clang-Tidy original name: bugprone-exception-escape)</p>


#### Fold Init Type {#CT_BUG_FIT}
<p>The check flags type mismatches in <a href="https://en.wikipedia.org/wiki/Fold_(higher-order_function)">folds</a> like std::accumulate that might result in loss of precision. std::accumulate folds an input range into an initial value using the type of the latter, with operator+ by default. This can cause loss of precision through:</p>
<ul>
<li>Truncation: The following code uses a floating point range and an int initial value, so trucation will happen at every application of operator+ and the result will be 0, which might not be what the user expected.</li>
</ul>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">auto</span> a = {<span class="fl">0.5f</span>, <span class="fl">0.5f</span>, <span class="fl">0.5f</span>, <span class="fl">0.5f</span>};
<span class="kw">return</span> std::accumulate(std::begin(a), std::end(a), <span class="dv">0</span>);</code></pre></div>
<ul>
<li>Overflow: The following code also returns 0.</li>
</ul>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">auto</span> a = {<span class="dv">65536LL</span> * <span class="dv">65536</span> * <span class="dv">65536</span>};
<span class="kw">return</span> std::accumulate(std::begin(a), std::end(a), <span class="dv">0</span>);</code></pre></div>
<p>(Clang-Tidy original name: bugprone-fold-init-type)</p>


#### Forward Declaration Namespace {#CT_BUG_FDN}
<p>Checks if an unused forward declaration is in a wrong namespace.</p>
<p>The check inspects all unused forward declarations and checks if there is any declaration/definition with the same name existing, which could indicate that the forward declaration is in a potentially wrong namespace.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">namespace</span> na { <span class="kw">struct</span> A; }
<span class="kw">namespace</span> nb { <span class="kw">struct</span> A {}; }
nb::A a;
<span class="co">// warning : no definition found for &#39;A&#39;, but a definition with the same name</span>
<span class="co">// &#39;A&#39; found in another namespace &#39;nb::&#39;</span></code></pre></div>
<p>This check can only generate warnings, but it can’t suggest a fix at this point.</p>
<p>(Clang-Tidy original name: bugprone-forward-declaration-namespace)</p>


#### Forwarding Reference Overload {#CT_BUG_FRO}
<p>The check looks for perfect forwarding constructors that can hide copy or move constructors. If a non const lvalue reference is passed to the constructor, the forwarding reference parameter will be a better match than the const reference parameter of the copy constructor, so the perfect forwarding constructor will be called, which can be confusing. For detailed description of this issue see: Scott Meyers, Effective Modern C++, Item 26.</p>
<p>Consider the following example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> Person {
<span class="kw">public</span>:
  <span class="co">// C1: perfect forwarding ctor</span>
  <span class="kw">template</span>&lt;<span class="kw">typename</span> T&gt;
  <span class="kw">explicit</span> Person(T&amp;&amp; n) {}

  <span class="co">// C2: perfect forwarding ctor with parameter default value</span>
  <span class="kw">template</span>&lt;<span class="kw">typename</span> T&gt;
  <span class="kw">explicit</span> Person(T&amp;&amp; n, <span class="dt">int</span> x = <span class="dv">1</span>) {}

  <span class="co">// C3: perfect forwarding ctor guarded with enable_if</span>
  <span class="kw">template</span>&lt;<span class="kw">typename</span> T, <span class="kw">typename</span> X = enable_if_t&lt;is_special&lt;T&gt;,<span class="dt">void</span>&gt;&gt;
  <span class="kw">explicit</span> Person(T&amp;&amp; n) {}

  <span class="co">// (possibly compiler generated) copy ctor</span>
  Person(<span class="dt">const</span> Person&amp; rhs);
};</code></pre></div>
<p>The check warns for constructors C1 and C2, because those can hide copy and move constructors. We suppress warnings if the copy and the move constructors are both disabled (deleted or private), because there is nothing the perfect forwarding constructor could hide in this case. We also suppress warnings for constructors like C3 that are guarded with an enable_if, assuming the programmer was aware of the possible hiding.</p>
<h5 id="background">Background</h5>
<p>For deciding whether a constructor is guarded with enable_if, we consider the default values of the type parameters and the types of the constructor parameters. If any part of these types is std::enable_if or std::enable_if_t, we assume the constructor is guarded.</p>
<p>(Clang-Tidy original name: bugprone-forwarding-reference-overload)</p>


#### Inaccurate Erase {#CT_BUG_IE}
<p>Checks for inaccurate use of the erase() method.</p>
<p>Algorithms like remove() do not actually remove any element from the container but return an iterator to the first redundant element at the end of the container. These redundant elements must be removed using the erase() method. This check warns when not all of the elements will be removed due to using an inappropriate overload.</p>
<p>For example, the following code erases only one element:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::vector&lt;<span class="dt">int</span>&gt; xs;
...
xs.erase(std::remove(xs.begin(), xs.end(), <span class="dv">10</span>));</code></pre></div>
<p>Call the two-argument overload of erase() to remove the subrange:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::vector&lt;<span class="dt">int</span>&gt; xs;
...
xs.erase(std::remove(xs.begin(), xs.end(), <span class="dv">10</span>), xs.end());</code></pre></div>
<p>(Clang-Tidy original name: bugprone-inaccurate-erase)</p>


#### Incorrect Roundings {#CT_BUG_IR}
<p>Checks the usage of patterns known to produce incorrect rounding. Programmers often use:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">(<span class="dt">int</span>)(double_expression + <span class="fl">0.5</span>)</code></pre></div>
<p>to round the double expression to an integer. The problem with this:</p>
<ol style="list-style-type: decimal">
<li>It is unnecessarily slow.</li>
<li>It is incorrect. The number 0.499999975 (smallest representable float number below 0.5) rounds to 1.0. Even worse behavior for negative numbers where both -0.5f and -1.4f both round to 0.0.</li>
</ol>
<p>(Clang-Tidy original name: bugprone-incorrect-roundings)</p>


#### Infinite Loop {#CT_BUG_IL}
<p>Finds obvious infinite loops (loops where the condition variable is not changed at all).</p>
<p>Finding infinite loops is well-known to be impossible (halting problem). However, it is possible to detect some obvious infinite loops, for example, if the loop condition is not changed. This check detects such loops. A loop is considered infinite if it does not have any loop exit statement (break, continue, goto, return, throw or a call to a function called as [[noreturn]]) and all of the following conditions hold for every variable in the condition:</p>
<ul>
<li>It is a local variable.</li>
<li>It has no reference or pointer aliases.</li>
<li>It is not a structure or class member.</li>
</ul>
<p>Furthermore, the condition must not contain a function call to consider the loop infinite since functions may return different values for different calls.</p>
<p>For example, the following loop is considered infinite i is not changed in the body:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">int</span> i = <span class="dv">0</span>, j = <span class="dv">0</span>;
<span class="kw">while</span> (i &lt; <span class="dv">10</span>) {
  ++j;
}</code></pre></div>
<p>(Clang-Tidy original name: bugprone-infinite-loop)</p>


#### Integer Division {#CT_BUG_ID}
<p>Finds cases where integer division in a floating point context is likely to cause unintended loss of precision.</p>
<p>No reports are made if divisions are part of the following expressions:</p>
<ul>
<li>operands of operators expecting integral or bool types,</li>
<li>call expressions of integral or bool types, and</li>
<li>explicit cast expressions to integral or bool types,</li>
</ul>
<p>as these are interpreted as signs of deliberateness from the programmer.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">float</span> floatFunc(<span class="dt">float</span>);
<span class="dt">int</span> intFunc(<span class="dt">int</span>);
<span class="dt">double</span> d;
<span class="dt">int</span> i = <span class="dv">42</span>;

<span class="co">// Warn, floating-point values expected.</span>
d = <span class="dv">32</span> * <span class="dv">8</span> / (<span class="dv">2</span> + i);
d = <span class="dv">8</span> * floatFunc(<span class="dv">1</span> + <span class="dv">7</span> / <span class="dv">2</span>);
d = i / (<span class="dv">1</span> &lt;&lt; <span class="dv">4</span>);

<span class="co">// OK, no integer division.</span>
d = <span class="dv">32</span> * <span class="fl">8.0</span> / (<span class="dv">2</span> + i);
d = <span class="dv">8</span> * floatFunc(<span class="dv">1</span> + <span class="fl">7.0</span> / <span class="dv">2</span>);
d = (<span class="dt">double</span>)i / (<span class="dv">1</span> &lt;&lt; <span class="dv">4</span>);

<span class="co">// OK, there are signs of deliberateness.</span>
d = <span class="dv">1</span> &lt;&lt; (i / <span class="dv">2</span>);
d = <span class="dv">9</span> + intFunc(<span class="dv">6</span> * i / <span class="dv">32</span>);
d = (<span class="dt">int</span>)(i / <span class="dv">32</span>) - <span class="dv">8</span>;</code></pre></div>
<p>(Clang-Tidy original name: bugprone-integer-division)</p>


#### Lambda Function Name {#CT_BUG_LFN}
<p>Checks for attempts to get the name of a function from within a lambda expression. The name of a lambda is always something like operator(), which is almost never what was intended.</p>
<p>Example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> FancyFunction() {
  [] { printf(<span class="st">&quot;Called from </span><span class="ch">%s\n</span><span class="st">&quot;</span>, <span class="ot">__func__</span>); }();
  [] { printf(<span class="st">&quot;Now called from </span><span class="ch">%s\n</span><span class="st">&quot;</span>, <span class="ot">__FUNCTION__</span>); }();
}</code></pre></div>
<p>Output:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">Called from <span class="kw">operator</span>()
Now called from <span class="kw">operator</span>()</code></pre></div>
<p>Likely intended output:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">Called from FancyFunction
Now called from FancyFunction</code></pre></div>
<p>(Clang-Tidy original name: bugprone-lambda-function-name)</p>


#### Macro Parentheses {#CT_BUG_MP}
<p>Finds macros that can have unexpected behaviour due to missing parentheses.</p>
<p>Macros are expanded by the preprocessor as-is. As a result, there can be unexpected behaviour; operators may be evaluated in unexpected order and unary operators may become binary operators, etc.</p>
<p>When the replacement list has an expression, it is recommended to surround it with parentheses. This ensures that the macro result is evaluated completely before it is used.</p>
<p>It is also recommended to surround macro arguments in the replacement list with parentheses. This ensures that the argument value is calculated properly.</p>
<p>(Clang-Tidy original name: bugprone-macro-parentheses)</p>
<p>subl.. title:: clang-tidy - abseil-no-internal-dependencies</p>


#### Macro Repeated Side Effects {#CT_BUG_MRSE}
<p>Checks for repeated argument with side effects in macros.</p>
<p>(Clang-Tidy original name: bugprone-macro-repeated-side-effects)</p>


#### Misplaced Operator In Strlen In Alloc {#CT_BUG_MOISIA}
<p>Finds cases where 1 is added to the string in the argument to strlen(), strnlen(), strnlen_s(), wcslen(), wcsnlen(), and wcsnlen_s() instead of the result and the value is used as an argument to a memory allocation function (malloc(), calloc(), realloc(), alloca()) or the new[] operator in C++. The check detects error cases even if one of these functions (except the new[] operator) is called by a constant function pointer. Cases where 1 is added both to the parameter and the result of the strlen()-like function are ignored, as are cases where the whole addition is surrounded by extra parentheses.</p>
<p>C example code:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> bad_malloc(<span class="dt">char</span> *str) {
  <span class="dt">char</span> *c = (<span class="dt">char</span>*) malloc(strlen(str + <span class="dv">1</span>));
}</code></pre></div>
<p>The suggested fix is to add 1 to the return value of strlen() and not to its argument. In the example above the fix would be</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">char</span> *c = (<span class="dt">char</span>*) malloc(strlen(str) + <span class="dv">1</span>);</code></pre></div>
<p>C++ example code:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> bad_new(<span class="dt">char</span> *str) {
  <span class="dt">char</span> *c = <span class="kw">new</span> <span class="dt">char</span>[strlen(str + <span class="dv">1</span>)];
}</code></pre></div>
<p>As in the C code with the malloc() function, the suggested fix is to add 1 to the return value of strlen() and not to its argument. In the example above the fix would be</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">char</span> *c = <span class="kw">new</span> <span class="dt">char</span>[strlen(str) + <span class="dv">1</span>];</code></pre></div>
<p>Example for silencing the diagnostic:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> bad_malloc(<span class="dt">char</span> *str) {
  <span class="dt">char</span> *c = (<span class="dt">char</span>*) malloc(strlen((str + <span class="dv">1</span>)));
}</code></pre></div>
<p>(Clang-Tidy original name: bugprone-misplaced-operator-in-strlen-in-alloc)</p>


#### Misplaced Pointer Arithmetic In Alloc {#CT_BUG_MPAIA}
<p>Finds cases where an integer expression is added to or subtracted from the result of a memory allocation function (malloc(), calloc(), realloc(), alloca()) instead of its argument. The check detects error cases even if one of these functions is called by a constant function pointer.</p>
<p>Example code:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> bad_malloc(<span class="dt">int</span> n) {
  <span class="dt">char</span> *p = (<span class="dt">char</span>*) malloc(n) + <span class="dv">10</span>;
}</code></pre></div>
<p>The suggested fix is to add the integer expression to the argument of malloc and not to its result. In the example above the fix would be</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">char</span> *p = (<span class="dt">char</span>*) malloc(n + <span class="dv">10</span>);</code></pre></div>
<p>(Clang-Tidy original name: bugprone-misplaced-pointer-arithmetic-in-alloc)</p>


#### Misplaced Widening Cast {#CT_BUG_MWC}
<p>This check will warn when there is a cast of a calculation result to a bigger type. If the intention of the cast is to avoid loss of precision then the cast is misplaced, and there can be loss of precision. Otherwise the cast is ineffective.</p>
<p>Example code:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">long</span> f(<span class="dt">int</span> x) {
    <span class="kw">return</span> (<span class="dt">long</span>)(x * <span class="dv">1000</span>);
}</code></pre></div>
<p>The result x * 1000 is first calculated using int precision. If the result exceeds int precision there is loss of precision. Then the result is casted to long.</p>
<p>If there is no loss of precision then the cast can be removed or you can explicitly cast to int instead.</p>
<p>If you want to avoid loss of precision then put the cast in a proper location, for instance:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">long</span> f(<span class="dt">int</span> x) {
    <span class="kw">return</span> (<span class="dt">long</span>)x * <span class="dv">1000</span>;
}</code></pre></div>
<h5 id="implicit-casts">Implicit casts</h5>
<p>Forgetting to place the cast at all is at least as dangerous and at least as common as misplacing it. If <a href="#cmdoption-arg-checkimplicitcasts">CheckImplicitCasts</a> is enabled the check also detects these cases, for instance:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">long</span> f(<span class="dt">int</span> x) {
    <span class="kw">return</span> x * <span class="dv">1000</span>;
}</code></pre></div>
<h5 id="floating-point">Floating point</h5>
<p>Currently warnings are only written for integer conversion. No warning is written for this code:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">double</span> f(<span class="dt">float</span> x) {
    <span class="kw">return</span> (<span class="dt">double</span>)(x * <span class="fl">10.0f</span>);
}</code></pre></div>
<h5 id="options-18">Options</h5>
<p>CheckImplicitCasts</p>
<p>If true, enables detection of implicit casts. Default is true.</p>
<p>(Clang-Tidy original name: bugprone-misplaced-widening-cast)</p>


#### Move Forwarding Reference {#CT_BUG_MFR}
<p>Warns if std::move is called on a forwarding reference, for example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">template</span> &lt;<span class="kw">typename</span> T&gt;
<span class="dt">void</span> foo(T&amp;&amp; t) {
  bar(std::move(t));
}</code></pre></div>
<p><a href="http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4164.pdf">Forwarding references</a> should typically be passed to std::forward instead of std::move, and this is the fix that will be suggested.</p>
<p>(A forwarding reference is an rvalue reference of a type that is a deduced function template argument.)</p>
<p>In this example, the suggested fix would be</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">bar(std::forward&lt;T&gt;(t));</code></pre></div>
<h5 id="background-1">Background</h5>
<p>Code like the example above is sometimes written with the expectation that T&amp;&amp; will always end up being an rvalue reference, no matter what type is deduced for T, and that it is therefore not possible to pass an lvalue to foo(). However, this is not true. Consider this example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::string s = <span class="st">&quot;Hello, world&quot;</span>;
foo(s);</code></pre></div>
<p>This code compiles and, after the call to foo(), s is left in an indeterminate state because it has been moved from. This may be surprising to the caller of foo() because no std::move was used when calling foo().</p>
<p>The reason for this behavior lies in the special rule for template argument deduction on function templates like foo() – i.e. on function templates that take an rvalue reference argument of a type that is a deduced function template argument. (See section [temp.deduct.call]/3 in the C++11 standard.)</p>
<p>If foo() is called on an lvalue (as in the example above), then T is deduced to be an lvalue reference. In the example, T is deduced to be std::string &amp;. The type of the argument t therefore becomes std::string&amp; &amp;&amp;; by the reference collapsing rules, this collapses to std::string&amp;.</p>
<p>This means that the foo(s) call passes s as an lvalue reference, and foo() ends up moving s and thereby placing it into an indeterminate state.</p>
<p>(Clang-Tidy original name: bugprone-move-forwarding-reference)</p>


#### Multiple Statement Macro {#CT_BUG_MSM}
<p>Detect multiple statement macros that are used in unbraced conditionals. Only the first statement of the macro will be inside the conditional and the other ones will be executed unconditionally.</p>
<p>Example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="ot">#define INCREMENT_TWO(x, y) (x)++; (y)++</span>
<span class="kw">if</span> (do_increment)
  INCREMENT_TWO(a, b);  <span class="co">// (b)++ will be executed unconditionally.</span></code></pre></div>
<p>(Clang-Tidy original name: bugprone-multiple-statement-macro)</p>


#### Narrowing Conversions {#CT_BUG_NC}
No documentation is available.

#### No Escape {#CT_BUG_NE}
<p>Finds pointers with the noescape attribute that are captured by an asynchronously-executed block. The block arguments in dispatch_async() and dispatch_after() are guaranteed to escape, so it is an error if a pointer with the noescape attribute is captured by one of these blocks.</p>
<p>The following is an example of an invalid use of the noescape attribute.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> foo(<span class="ot">__attribute__</span>((noescape)) <span class="dt">int</span> *p) {
  dispatch_async(queue, ^{
    *p = <span class="dv">123</span>;
  });
});</code></pre></div>
<p>(Clang-Tidy original name: bugprone-no-escape)</p>


#### Not Null Terminated Result {#CT_BUG_NNTR}
<p>Finds function calls where it is possible to cause a not null-terminated result. Usually the proper length of a string is strlen(src) + 1 or equal length of this expression, because the null terminator needs an extra space. Without the null terminator it can result in undefined behaviour when the string is read.</p>
<p>The following and their respective wchar_t based functions are checked:</p>
<p>memcpy, memcpy_s, memchr, memmove, memmove_s, strerror_s, strncmp, strxfrm</p>
<p>The following is a real-world example where the programmer forgot to increase the passed third argument, which is size_t length. That is why the length of the allocated memory is not enough to hold the null terminator.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">static</span> <span class="dt">char</span> *stringCpy(<span class="dt">const</span> std::string &amp;str) {
  <span class="dt">char</span> *result = <span class="kw">reinterpret_cast</span>&lt;<span class="dt">char</span> *&gt;(malloc(str.size()));
  memcpy(result, str.data(), str.size());
  <span class="kw">return</span> result;
}</code></pre></div>
<p>In addition to issuing warnings, fix-it rewrites all the necessary code. It also tries to adjust the capacity of the destination array:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">static</span> <span class="dt">char</span> *stringCpy(<span class="dt">const</span> std::string &amp;str) {
  <span class="dt">char</span> *result = <span class="kw">reinterpret_cast</span>&lt;<span class="dt">char</span> *&gt;(malloc(str.size() + <span class="dv">1</span>));
  strcpy(result, str.data());
  <span class="kw">return</span> result;
}</code></pre></div>
<p>Note: It cannot guarantee to rewrite every of the path-sensitive memory allocations.</p>
<h5 id="transformation-rules-of-memcpy">Transformation rules of ‘memcpy()’</h5>
<p>It is possible to rewrite the memcpy() and memcpy_s() calls as the following four functions: strcpy(), strncpy(), strcpy_s(), strncpy_s(), where the latter two are the safer versions of the former two. It rewrites the wchar_t based memory handler functions respectively.</p>
<h6 id="rewrite-based-on-the-destination-array">Rewrite based on the destination array</h6>
<ul>
<li>If copy to the destination array cannot overflow [1] the new function should be the older copy function (ending with cpy), because it is more efficient than the safe version.</li>
<li>If copy to the destination array can overflow [1] and <a href="#cmdoption-arg-wanttousesafefunctions">WantToUseSafeFunctions</a> is set to true and it is possible to obtain the capacity of the destination array then the new function could be the safe version (ending with cpy_s).</li>
<li>If the new function is could be safe version and C++ files are analysed and the destination array is plain char/wchar_t without un/signed then the length of the destination array can be omitted.</li>
<li>If the new function is could be safe version and the destination array is un/signed it needs to be casted to plain char <em>/wchar_t </em>.</li>
</ul>
<p>[1] It is possible to overflow:</p>
<ul>
<li>If the capacity of the destination array is unknown.</li>
<li>If the given length is equal to the destination array’s capacity.</li>
</ul>
<h6 id="rewrite-based-on-the-length-of-the-source-string">Rewrite based on the length of the source string</h6>
<ul>
<li>If the given length is strlen(source) or equal length of this expression then the new function should be the older copy function (ending with cpy), as it is more efficient than the safe version (ending with cpy_s).</li>
<li>Otherwise we assume that the programmer wanted to copy ‘N’ characters, so the new function is ncpy-like which copies ‘N’ characters.</li>
</ul>
<h5 id="transformations-with-strlen-or-equal-length-of-this-expression">Transformations with ‘strlen()’ or equal length of this expression</h5>
<p>It transforms the wchar_t based memory and string handler functions respectively (where only strerror_s does not have wchar_t based alias).</p>
<h6 id="memory-handler-functions">Memory handler functions</h6>
<p>memcpy Please visit the <a href="#memcpytransformation">Transformation rules of ‘memcpy()’</a> section.</p>
<p>memchr Usually there is a C-style cast and it is needed to be removed, because the new function strchr’s return type is correct. The given length is going to be removed.</p>
<p>memmove If safe functions are available the new function is memmove_s, which has a new second argument which is the length of the destination array, it is adjusted, and the length of the source string is incremented by one. If safe functions are not available the given length is incremented by one.</p>
<p>memmove_s The given length is incremented by one.</p>
<h6 id="string-handler-functions">String handler functions</h6>
<p>strerror_s The given length is incremented by one.</p>
<p>strncmp If the third argument is the first or the second argument’s length + 1 it has to be truncated without the + 1 operation.</p>
<p>strxfrm The given length is incremented by one.</p>
<h5 id="options-51">Options</h5>
<p>WantToUseSafeFunctions</p>
<p>The value true specifies that the target environment is considered to implement ‘_s’ suffixed memory and string handler functions which are safer than older versions (e.g. ‘memcpy_s()’). The default value is true.</p>
<p>(Clang-Tidy original name: bugprone-not-null-terminated-result)</p>


#### Parent Virtual Call {#CT_BUG_PVC}
<p>Detects and fixes calls to grand-…parent virtual methods instead of calls to overridden parent’s virtual methods.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">struct</span> A {
  <span class="dt">int</span> <span class="kw">virtual</span> foo() {...}
};

<span class="kw">struct</span> B: <span class="kw">public</span> A {
  <span class="dt">int</span> foo() <span class="kw">override</span> {...}
};

<span class="kw">struct</span> C: <span class="kw">public</span> B {
  <span class="dt">int</span> foo() <span class="kw">override</span> { A::foo(); }
<span class="co">//                     ^^^^^^^^</span>
<span class="co">// warning: qualified name A::foo refers to a member overridden in subclass; did you mean &#39;B&#39;?  [bugprone-parent-virtual-call]</span>
};</code></pre></div>
<p>(Clang-Tidy original name: bugprone-parent-virtual-call)</p>


#### Posix Return {#CT_BUG_PR}
<p>Checks if any calls to pthread_* or posix_* functions (except posix_openpt) expect negative return values. These functions return either 0 on success or an errno on failure, which is positive only.</p>
<p>Example buggy usage looks like:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">if</span> (posix_fadvise(...) &lt; <span class="dv">0</span>) {</code></pre></div>
<p>This will never happen as the return value is always non-negative. A simple fix could be:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">if</span> (posix_fadvise(...) &gt; <span class="dv">0</span>) {</code></pre></div>
<p>(Clang-Tidy original name: bugprone-posix-return)</p>


#### Redundant Branch Condition {#CT_BUG_RBC}
<p>Finds condition variables in nested if statements that were also checked in the outer if statement and were not changed.</p>
<p>Simple example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">bool</span> onFire = isBurning();
<span class="kw">if</span> (onFire) {
  <span class="kw">if</span> (onFire)
    scream();
}</code></pre></div>
<p>Here onFire is checked both in the outer if and the inner if statement without a possible change between the two checks. The check warns for this code and suggests removal of the second checking of variable onFire.</p>
<p>The checker also detects redundant condition checks if the condition variable is an operand of a logical “and” (&amp;&amp;) or a logical “or” (||) operator:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">bool</span> onFire = isBurning();
<span class="kw">if</span> (onFire) {
  <span class="kw">if</span> (onFire &amp;&amp; peopleInTheBuilding &gt; <span class="dv">0</span>)
    scream();
}</code></pre></div>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">bool</span> onFire = isBurning();
<span class="kw">if</span> (onFire) {
  <span class="kw">if</span> (onFire || isCollapsing())
    scream();
}</code></pre></div>
<p>In the first case (logical “and”) the suggested fix is to remove the redundant condition variable and keep the other side of the &amp;&amp;. In the second case (logical “or”) the whole if is removed similarily to the simple case on the top.</p>
<p>The condition of the outer if statement may also be a logical “and” (&amp;&amp;) expression:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">bool</span> onFire = isBurning();
<span class="kw">if</span> (onFire &amp;&amp; fireFighters &lt; <span class="dv">10</span>) {
  <span class="kw">if</span> (someOtherCondition()) {
    <span class="kw">if</span> (onFire)
      scream();
  }
}</code></pre></div>
<p>The error is also detected if both the outer statement is a logical “and” (&amp;&amp;) and the inner statement is a logical “and” (&amp;&amp;) or “or” (||). The inner if statement does not have to be a direct descendant of the outer one.</p>
<p>No error is detected if the condition variable may have been changed between the two checks:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">bool</span> onFire = isBurning();
<span class="kw">if</span> (onFire) {
  tryToExtinguish(onFire);
  <span class="kw">if</span> (onFire &amp;&amp; peopleInTheBuilding &gt; <span class="dv">0</span>)
    scream();
}</code></pre></div>
<p>Every possible change is considered, thus if the condition variable is not a local variable of the function, it is a volatile or it has an alias (pointer or reference) then no warning is issued.</p>
<h5 id="known-limitations-3">Known limitations</h5>
<p>The else branch is not checked currently for negated condition variable:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">bool</span> onFire = isBurning();
<span class="kw">if</span> (onFire) {
  scream();
} <span class="kw">else</span> {
  <span class="kw">if</span> (!onFire) {
    continueWork();
  }
}</code></pre></div>
<p>The checker currently only detects redundant checking of single condition variables. More complex expressions are not checked:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">if</span> (peopleInTheBuilding == <span class="dv">1</span>) {
  <span class="kw">if</span> (peopleInTheBuilding == <span class="dv">1</span>) {
    doSomething();
  }
}</code></pre></div>
<p>(Clang-Tidy original name: bugprone-redundant-branch-condition)</p>


#### Reserved Identifier {#CT_BUG_RI}
<p>cert-dcl37-c and cert-dcl51-cpp redirect here as an alias for this check.</p>
<p>Checks for usages of identifiers reserved for use by the implementation.</p>
<p>The C and C++ standards both reserve the following names for such use:</p>
<ul>
<li>identifiers that begin with an underscore followed by an uppercase letter;</li>
<li>identifiers in the global namespace that begin with an underscore.</li>
</ul>
<p>The C standard additionally reserves names beginning with a double underscore, while the C++ standard strengthens this to reserve names with a double underscore occurring anywhere.</p>
<p>Violating the naming rules above results in undefined behavior.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">namespace</span> NS {
  <span class="dt">void</span> __f(); <span class="co">// name is not allowed in user code</span>
  <span class="kw">using</span> _Int = <span class="dt">int</span>; <span class="co">// same with this</span>
  <span class="ot">#define cool__macro </span><span class="co">// also this</span>
}
<span class="dt">int</span> _g(); <span class="co">// disallowed in global namespace only</span></code></pre></div>
<p>The check can also be inverted, i.e. it can be configured to flag any identifier that is <em>not</em> a reserved identifier. This mode is for use by e.g. standard library implementors, to ensure they don’t infringe on the user namespace.</p>
<p>This check does not (yet) check for other reserved names, e.g. macro names identical to language keywords, and names specifically reserved by language standards, e.g. C++ ‘zombie names’ and C future library directions.</p>
<p>This check corresponds to CERT C Coding Standard rule <a href="https://wiki.sei.cmu.edu/confluence/display/c/DCL37-C.+Do+not+declare+or+define+a+reserved+identifier">DCL37-C. Do not declare or define a reserved identifier</a> as well as its C++ counterpart, <a href="https://wiki.sei.cmu.edu/confluence/display/cplusplus/DCL51-CPP.+Do+not+declare+or+define+a+reserved+identifier">DCL51-CPP. Do not declare or define a reserved identifier</a>.</p>
<h5 id="options-34">Options</h5>
<p>Invert</p>
<p>If true, inverts the check, i.e. flags names that are not reserved. Default is false.</p>
<p>AllowedIdentifiers</p>
<p>Semicolon-separated list of names that the check ignores. Default is an empty list.</p>
<p>(Clang-Tidy original name: bugprone-reserved-identifier)</p>


#### Signal Handler {#CT_BUG_SH}
<p>Finds functions registered as signal handlers that call non asynchronous-safe functions. Any function that cannot be determined to be an asynchronous-safe function call is assumed to be non-asynchronous-safe by the checker, including user functions for which only the declaration is visible. User function calls with visible definition are checked recursively. The check handles only C code.</p>
<p>The minimal list of asynchronous-safe system functions is: abort(), _Exit(), quick_exit() and signal() (for signal there are additional conditions that are not checked). The check accepts only these calls as asynchronous-safe.</p>
<p>This check corresponds to the CERT C Coding Standard rule <a href="https://www.securecoding.cert.org/confluence/display/c/SIG30-C.+Call+only+asynchronous-safe+functions+within+signal+handlers">SIG30-C. Call only asynchronous-safe functions within signal handlers</a>.</p>
<p>(Clang-Tidy original name: bugprone-signal-handler)</p>


#### Signed Char Misuse {#CT_BUG_SCM}
<p>cert-str34-c redirects here as an alias for this check. For the CERT alias, the DiagnoseSignedUnsignedCharComparisons option is set to false.</p>
<p>Finds those signed char -&gt; integer conversions which might indicate a programming error. The basic problem with the signed char, that it might store the non-ASCII characters as negative values. This behavior can cause a misunderstanding of the written code both when an explicit and when an implicit conversion happens.</p>
<p>When the code contains an explicit signed char -&gt; integer conversion, the human programmer probably expects that the converted value matches with the character code (a value from [0..255]), however, the actual value is in [-128..127] interval. To avoid this kind of misinterpretation, the desired way of converting from a signed char to an integer value is converting to unsigned char first, which stores all the characters in the positive [0..255] interval which matches the known character codes.</p>
<p>In case of implicit conversion, the programmer might not actually be aware that a conversion happened and char value is used as an integer. There are some use cases when this unawareness might lead to a functionally imperfect code. For example, checking the equality of a signed char and an unsigned char variable is something we should avoid in C++ code. During this comparison, the two variables are converted to integers which have different value ranges. For signed char, the non-ASCII characters are stored as a value in [-128..-1] interval, while the same characters are stored in the [128..255] interval for an unsigned char.</p>
<p>It depends on the actual platform whether plain char is handled as signed char by default and so it is caught by this check or not. To change the default behavior you can use -funsigned-char and -fsigned-char compilation options.</p>
<p>Currently, this check warns in the following cases: - signed char is assigned to an integer variable - signed char and unsigned char are compared with equality/inequality operator - signed char is converted to an integer in the array subscript</p>
<p>See also: <a href="https://wiki.sei.cmu.edu/confluence/display/c/STR34-C.+Cast+characters+to+unsigned+char+before+converting+to+larger+integer+sizes">STR34-C. Cast characters to unsigned char before converting to larger integer sizes</a></p>
<p>A good example from the CERT description when a char variable is used to read from a file that might contain non-ASCII characters. The problem comes up when the code uses the -1 integer value as EOF, while the 255 character code is also stored as -1 in two’s complement form of char type. See a simple example of this bellow. This code stops not only when it reaches the end of the file, but also when it gets a character with the 255 code.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="ot">#define EOF (-1)</span>

<span class="dt">int</span> read(<span class="dt">void</span>) {
  <span class="dt">char</span> CChar;
  <span class="dt">int</span> IChar = EOF;

  <span class="kw">if</span> (readChar(CChar)) {
    IChar = CChar;
  }
  <span class="kw">return</span> IChar;
}</code></pre></div>
<p>A proper way to fix the code above is converting the char variable to an unsigned char value first.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="ot">#define EOF (-1)</span>

<span class="dt">int</span> read(<span class="dt">void</span>) {
  <span class="dt">char</span> CChar;
  <span class="dt">int</span> IChar = EOF;

  <span class="kw">if</span> (readChar(CChar)) {
    IChar = <span class="kw">static_cast</span>&lt;<span class="dt">unsigned</span> <span class="dt">char</span>&gt;(CChar);
  }
  <span class="kw">return</span> IChar;
}</code></pre></div>
<p>Another use case is checking the equality of two char variables with different signedness. Inside the non-ASCII value range this comparison between a signed char and an unsigned char always returns false.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">bool</span> compare(<span class="dt">signed</span> <span class="dt">char</span> SChar, <span class="dt">unsigned</span> <span class="dt">char</span> USChar) {
  <span class="kw">if</span> (SChar == USChar)
    <span class="kw">return</span> <span class="kw">true</span>;
  <span class="kw">return</span> <span class="kw">false</span>;
}</code></pre></div>
<p>The easiest way to fix this kind of comparison is casting one of the arguments, so both arguments will have the same type.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">bool</span> compare(<span class="dt">signed</span> <span class="dt">char</span> SChar, <span class="dt">unsigned</span> <span class="dt">char</span> USChar) {
  <span class="kw">if</span> (<span class="kw">static_cast</span>&lt;<span class="dt">unsigned</span> <span class="dt">char</span>&gt;(SChar) == USChar)
    <span class="kw">return</span> <span class="kw">true</span>;
  <span class="kw">return</span> <span class="kw">false</span>;
}</code></pre></div>
<p>CharTypdefsToIgnore</p>
<p>A semicolon-separated list of typedef names. In this list, we can list typedefs for char or signed char, which will be ignored by the check. This is useful when a typedef introduces an integer alias like sal_Int8 or int8_t. In this case, human misinterpretation is not an issue.</p>
<p>DiagnoseSignedUnsignedCharComparisons</p>
<p>When true, the check will warn on signed char/unsigned char comparisons, otherwise these comparisons are ignored. By default, this option is set to true.</p>
<p>(Clang-Tidy original name: bugprone-signed-char-misuse)</p>


#### Sizeof Container {#CT_BUG_SC}
<p>The check finds usages of sizeof on expressions of STL container types. Most likely the user wanted to use .size() instead.</p>
<p>All class/struct types declared in namespace std:: having a const size() method are considered containers, with the exception of std::bitset and std::array.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::string s;
<span class="dt">int</span> a = <span class="dv">47</span> + <span class="kw">sizeof</span>(s); <span class="co">// warning: sizeof() doesn&#39;t return the size of the container. Did you mean .size()?</span>

<span class="dt">int</span> b = <span class="kw">sizeof</span>(std::string); <span class="co">// no warning, probably intended.</span>

std::string array_of_strings[<span class="dv">10</span>];
<span class="dt">int</span> c = <span class="kw">sizeof</span>(array_of_strings) / <span class="kw">sizeof</span>(array_of_strings[<span class="dv">0</span>]); <span class="co">// no warning, definitely intended.</span>

std::array&lt;<span class="dt">int</span>, <span class="dv">3</span>&gt; std_array;
<span class="dt">int</span> d = <span class="kw">sizeof</span>(std_array); <span class="co">// no warning, probably intended.</span></code></pre></div>
<p>(Clang-Tidy original name: bugprone-sizeof-container)</p>


#### Sizeof Expression {#CT_BUG_SE}
<p>The check finds usages of sizeof expressions which are most likely errors.</p>
<p>The sizeof operator yields the size (in bytes) of its operand, which may be an expression or the parenthesized name of a type. Misuse of this operator may be leading to errors and possible software vulnerabilities.</p>
<h5 id="suspicious-usage-of-sizeofk">Suspicious usage of ‘sizeof(K)’</h5>
<p>A common mistake is to query the sizeof of an integer literal. This is equivalent to query the size of its type (probably int). The intent of the programmer was probably to simply get the integer and not its size.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="ot">#define BUFLEN 42</span>
<span class="dt">char</span> buf[BUFLEN];
memset(buf, <span class="dv">0</span>, <span class="kw">sizeof</span>(BUFLEN));  <span class="co">// sizeof(42) ==&gt; sizeof(int)</span></code></pre></div>
<h5 id="suspicious-usage-of-sizeofexpr">Suspicious usage of ‘sizeof(expr)’</h5>
<p>In cases, where there is an enum or integer to represent a type, a common mistake is to query the sizeof on the integer or enum that represents the type that should be used by sizeof. This results in the size of the integer and not of the type the integer represents:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">enum</span> data_type {
  FLOAT_TYPE,
  DOUBLE_TYPE
};

<span class="kw">struct</span> data {
  data_type type;
  <span class="dt">void</span>* buffer;
  data_type get_type() {
    <span class="kw">return</span> type;
  }
};

<span class="dt">void</span> f(data d, <span class="dt">int</span> numElements) {
  <span class="co">// should be sizeof(float) or sizeof(double), depending on d.get_type()</span>
  <span class="dt">int</span> numBytes = numElements * <span class="kw">sizeof</span>(d.get_type());
  ...
}</code></pre></div>
<h5 id="suspicious-usage-of-sizeofthis">Suspicious usage of ‘sizeof(this)’</h5>
<p>The this keyword is evaluated to a pointer to an object of a given type. The expression sizeof(this) is returning the size of a pointer. The programmer most likely wanted the size of the object and not the size of the pointer.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> Point {
  [...]
  size_t size() { <span class="kw">return</span> <span class="kw">sizeof</span>(<span class="kw">this</span>); }  <span class="co">// should probably be sizeof(*this)</span>
  [...]
};</code></pre></div>
<h5 id="suspicious-usage-of-sizeofchar">Suspicious usage of ‘sizeof(char*)’</h5>
<p>There is a subtle difference between declaring a string literal with char* A = &quot;&quot; and char A[] = &quot;&quot;. The first case has the type char* instead of the aggregate type char[]. Using sizeof on an object declared with char* type is returning the size of a pointer instead of the number of characters (bytes) in the string literal.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">const</span> <span class="dt">char</span>* kMessage = <span class="st">&quot;Hello World!&quot;</span>;      <span class="co">// const char kMessage[] = &quot;...&quot;;</span>
<span class="dt">void</span> getMessage(<span class="dt">char</span>* buf) {
  memcpy(buf, kMessage, <span class="kw">sizeof</span>(kMessage));  <span class="co">// sizeof(char*)</span>
}</code></pre></div>
<h5 id="suspicious-usage-of-sizeofa">Suspicious usage of ‘sizeof(A*)’</h5>
<p>A common mistake is to compute the size of a pointer instead of its pointee. These cases may occur because of explicit cast or implicit conversion.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">int</span> A[<span class="dv">10</span>];
memset(A, <span class="dv">0</span>, <span class="kw">sizeof</span>(A + <span class="dv">0</span>));

<span class="kw">struct</span> Point point;
memset(point, <span class="dv">0</span>, <span class="kw">sizeof</span>(&amp;point));</code></pre></div>
<h5 id="suspicious-usage-of-sizeofsizeof">Suspicious usage of ‘sizeof(…)/sizeof(…)’</h5>
<p>Dividing sizeof expressions is typically used to retrieve the number of elements of an aggregate. This check warns on incompatible or suspicious cases.</p>
<p>In the following example, the entity has 10-bytes and is incompatible with the type int which has 4 bytes.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">char</span> buf[] = { <span class="dv">0</span>, <span class="dv">1</span>, <span class="dv">2</span>, <span class="dv">3</span>, <span class="dv">4</span>, <span class="dv">5</span>, <span class="dv">6</span>, <span class="dv">7</span>, <span class="dv">8</span>, <span class="dv">9</span> };  <span class="co">// sizeof(buf) =&gt; 10</span>
<span class="dt">void</span> getMessage(<span class="dt">char</span>* dst) {
  memcpy(dst, buf, <span class="kw">sizeof</span>(buf) / <span class="kw">sizeof</span>(<span class="dt">int</span>));  <span class="co">// sizeof(int) =&gt; 4  [incompatible sizes]</span>
}</code></pre></div>
<p>In the following example, the expression sizeof(Values) is returning the size of char<em>. One can easily be fooled by its declaration, but in parameter declaration the size ‘10’ is ignored and the function is receiving a char</em>.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">char</span> OrderedValues[<span class="dv">10</span>] = { <span class="dv">0</span>, <span class="dv">1</span>, <span class="dv">2</span>, <span class="dv">3</span>, <span class="dv">4</span>, <span class="dv">5</span>, <span class="dv">6</span>, <span class="dv">7</span>, <span class="dv">8</span>, <span class="dv">9</span> };
<span class="kw">return</span> CompareArray(<span class="dt">char</span> Values[<span class="dv">10</span>]) {
  <span class="kw">return</span> memcmp(OrderedValues, Values, <span class="kw">sizeof</span>(Values)) == <span class="dv">0</span>;  <span class="co">// sizeof(Values) ==&gt; sizeof(char*) [implicit cast to char*]</span>
}</code></pre></div>
<h5 id="suspicious-sizeof-by-sizeof-expression">Suspicious ‘sizeof’ by ‘sizeof’ expression</h5>
<p>Multiplying sizeof expressions typically makes no sense and is probably a logic error. In the following example, the programmer used * instead of /.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">const</span> <span class="dt">char</span> kMessage[] = <span class="st">&quot;Hello World!&quot;</span>;
<span class="dt">void</span> getMessage(<span class="dt">char</span>* buf) {
  memcpy(buf, kMessage, <span class="kw">sizeof</span>(kMessage) * <span class="kw">sizeof</span>(<span class="dt">char</span>));  <span class="co">//  sizeof(kMessage) / sizeof(char)</span>
}</code></pre></div>
<p>This check may trigger on code using the arraysize macro. The following code is working correctly but should be simplified by using only the sizeof operator.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">extern</span> Object objects[<span class="dv">100</span>];
<span class="dt">void</span> InitializeObjects() {
  memset(objects, <span class="dv">0</span>, arraysize(objects) * <span class="kw">sizeof</span>(Object));  <span class="co">// sizeof(objects)</span>
}</code></pre></div>
<h5 id="suspicious-usage-of-sizeofsizeof-1">Suspicious usage of ‘sizeof(sizeof(…))’</h5>
<p>Getting the sizeof of a sizeof makes no sense and is typically an error hidden through macros.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="ot">#define INT_SZ sizeof(int)</span>
<span class="dt">int</span> buf[] = { <span class="dv">42</span> };
<span class="dt">void</span> getInt(<span class="dt">int</span>* dst) {
  memcpy(dst, buf, <span class="kw">sizeof</span>(INT_SZ));  <span class="co">// sizeof(sizeof(int)) is suspicious.</span>
}</code></pre></div>
<h5 id="options-30">Options</h5>
<p>WarnOnSizeOfConstant</p>
<p>When true, the check will warn on an expression like sizeof(CONSTANT). Default is true.</p>
<p>WarnOnSizeOfIntegerExpression</p>
<p>When true, the check will warn on an expression like sizeof(expr) where the expression results in an integer. Default is false.</p>
<p>WarnOnSizeOfThis</p>
<p>When true, the check will warn on an expression like sizeof(this). Default is true.</p>
<p>WarnOnSizeOfCompareToConstant</p>
<p>When true, the check will warn on an expression like sizeof(epxr) &lt;= k for a suspicious constant k while k is 0 or greater than 0x8000. Default is true.</p>
<p>(Clang-Tidy original name: bugprone-sizeof-expression)</p>


#### Spuriously Wake Up Functions {#CT_BUG_SWUF}
<p>Finds cnd_wait, cnd_timedwait, wait, wait_for, or wait_until function calls when the function is not invoked from a loop that checks whether a condition predicate holds or the function has a condition parameter.</p>
<p>This check corresponds to the CERT C++ Coding Standard rule <a href="https://wiki.sei.cmu.edu/confluence/display/cplusplus/CON54-CPP.+Wrap+functions+that+can+spuriously+wake+up+in+a+loop">CON54-CPP. Wrap functions that can spuriously wake up in a loop</a>. and CERT C Coding Standard rule <a href="https://wiki.sei.cmu.edu/confluence/display/c/CON36-C.+Wrap+functions+that+can+spuriously+wake+up+in+a+loop">CON36-C. Wrap functions that can spuriously wake up in a loop</a>.</p>
<p>(Clang-Tidy original name: bugprone-spuriously-wake-up-functions)</p>


#### String Constructor {#CT_BUG_SC2}
<p>Finds string constructors that are suspicious and probably errors.</p>
<p>A common mistake is to swap parameters to the ‘fill’ string-constructor.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::string str(<span class="st">&#39;x&#39;</span>, <span class="dv">50</span>); <span class="co">// should be str(50, &#39;x&#39;)</span></code></pre></div>
<p>Calling the string-literal constructor with a length bigger than the literal is suspicious and adds extra random characters to the string.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::string(<span class="st">&quot;test&quot;</span>, <span class="dv">200</span>);   <span class="co">// Will include random characters after &quot;test&quot;.</span>
std::string_view(<span class="st">&quot;test&quot;</span>, <span class="dv">200</span>);</code></pre></div>
<p>Creating an empty string from constructors with parameters is considered suspicious. The programmer should use the empty constructor instead.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::string(<span class="st">&quot;test&quot;</span>, <span class="dv">0</span>);   <span class="co">// Creation of an empty string.</span>
std::string_view(<span class="st">&quot;test&quot;</span>, <span class="dv">0</span>);</code></pre></div>
<h5 id="options-77">Options</h5>
<p>WarnOnLargeLength</p>
<p>When true, the check will warn on a string with a length greater than <a href="#cmdoption-arg-largelengththreshold">LargeLengthThreshold</a>. Default is true.</p>
<p>LargeLengthThreshold</p>
<p>An integer specifying the large length threshold. Default is 0x800000.</p>
<p>StringNames</p>
<p>Default is ::std::basic_string;::std::basic_string_view.</p>
<p>Semicolon-delimited list of class names to apply this check to. By default ::std::basic_string applies to std::string and std::wstring. Set to e.g. ::std::basic_string;llvm::StringRef;QString to perform this check on custom classes.</p>
<p>(Clang-Tidy original name: bugprone-string-constructor)</p>


#### String Integer Assignment {#CT_BUG_SIA}
<p>The check finds assignments of an integer to std::basic_string<CharT> (std::string, std::wstring, etc.). The source of the problem is the following assignment operator of std::basic_string<CharT>:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">basic_string&amp; <span class="kw">operator</span>=( CharT ch );</code></pre></div>
<p>Numeric types can be implicitly casted to character types.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::string s;
<span class="dt">int</span> x = <span class="dv">5965</span>;
s = <span class="dv">6</span>;
s = x;</code></pre></div>
<p>Use the appropriate conversion functions or character literals.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::string s;
<span class="dt">int</span> x = <span class="dv">5965</span>;
s = <span class="st">&#39;6&#39;</span>;
s = std::to_string(x);</code></pre></div>
<p>In order to suppress false positives, use an explicit cast.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::string s;
s = <span class="kw">static_cast</span>&lt;<span class="dt">char</span>&gt;(<span class="dv">6</span>);</code></pre></div>
<p>(Clang-Tidy original name: bugprone-string-integer-assignment)</p>


#### String Literal With Embedded Nul {#CT_BUG_SLWEN}
<p>Finds occurrences of string literal with embedded NUL character and validates their usage.</p>
<h5 id="invalid-escaping">Invalid escaping</h5>
<p>Special characters can be escaped within a string literal by using their hexadecimal encoding like 42. A common mistake is to escape them like this x42 where the  stands for the NUL character.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">const</span> <span class="dt">char</span>* Example[] = <span class="st">&quot;Invalid character: \0x12 should be </span><span class="ch">\x12</span><span class="st">&quot;</span>;
<span class="dt">const</span> <span class="dt">char</span>* Bytes[] = <span class="st">&quot;</span><span class="ch">\x03</span><span class="st">\0x02\0x01\0x00\0xFF\0xFF\0xFF&quot;</span>;</code></pre></div>
<h5 id="truncated-literal">Truncated literal</h5>
<p>String-like classes can manipulate strings with embedded NUL as they are keeping track of the bytes and the length. This is not the case for a char* (NUL-terminated) string.</p>
<p>A common mistake is to pass a string-literal with embedded NUL to a string constructor expecting a NUL-terminated string. The bytes after the first NUL character are truncated.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::string str(<span class="st">&quot;abc\0def&quot;</span>);  <span class="co">// &quot;def&quot; is truncated</span>
str += <span class="st">&quot;\0&quot;</span>;                  <span class="co">// This statement is doing nothing</span>
<span class="kw">if</span> (str == <span class="st">&quot;\0abc&quot;</span>) <span class="kw">return</span>;   <span class="co">// This expression is always true</span></code></pre></div>
<p>(Clang-Tidy original name: bugprone-string-literal-with-embedded-nul)</p>


#### Suspicious Enum Usage {#CT_BUG_SEU}
<p>The checker detects various cases when an enum is probably misused (as a bitmask ).</p>
<ol style="list-style-type: decimal">
<li>When “ADD” or “bitwise OR” is used between two enum which come from different types and these types value ranges are not disjoint.</li>
</ol>
<p>The following cases will be investigated only using <a href="performance-inefficient-string-concatenation.html#cmdoption-arg-strictmode">StrictMode</a>. We regard the enum as a (suspicious) bitmask if the three conditions below are true at the same time:</p>
<ul>
<li>at most half of the elements of the enum are non pow-of-2 numbers (because of short enumerations)</li>
<li>there is another non pow-of-2 number than the enum constant representing all choices (the result “bitwise OR” operation of all enum elements)</li>
<li>enum type variable/enumconstant is used as an argument of a + or “bitwise OR ” operator</li>
</ul>
<p>So whenever the non pow-of-2 element is used as a bitmask element we diagnose a misuse and give a warning.</p>
<ol start="2" style="list-style-type: decimal">
<li>Investigating the right hand side of += and |= operator.</li>
<li>Check only the enum value side of a | and + operator if one of them is not enum val.</li>
<li>Check both side of | or + operator where the enum values are from the same enum type.</li>
</ol>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">enum</span> { A, B, C };
<span class="kw">enum</span> { D, E, F = <span class="dv">5</span> };
<span class="kw">enum</span> { G = <span class="dv">10</span>, H = <span class="dv">11</span>, I = <span class="dv">12</span> };

<span class="dt">unsigned</span> flag;
flag =
    A |
    H; <span class="co">// OK, disjoint value intervals in the enum types -&gt;probably good use.</span>
flag = B | F; <span class="co">// Warning, have common values so they are probably misused.</span>

<span class="co">// Case 2:</span>
<span class="kw">enum</span> Bitmask {
  A = <span class="dv">0</span>,
  B = <span class="dv">1</span>,
  C = <span class="dv">2</span>,
  D = <span class="dv">4</span>,
  E = <span class="dv">8</span>,
  F = <span class="dv">16</span>,
  G = <span class="dv">31</span> <span class="co">// OK, real bitmask.</span>
};

<span class="kw">enum</span> Almostbitmask {
  AA = <span class="dv">0</span>,
  BB = <span class="dv">1</span>,
  CC = <span class="dv">2</span>,
  DD = <span class="dv">4</span>,
  EE = <span class="dv">8</span>,
  FF = <span class="dv">16</span>,
  GG <span class="co">// Problem, forgot to initialize.</span>
};

<span class="dt">unsigned</span> flag = <span class="dv">0</span>;
flag |= E; <span class="co">// OK.</span>
flag |=
    EE; <span class="co">// Warning at the decl, and note that it was used here as a bitmask.</span></code></pre></div>
<h5 id="options-43">Options</h5>
<p>StrictMode</p>
<p>Default value: 0. When non-null the suspicious bitmask usage will be investigated additionally to the different enum usage check.</p>
<p>(Clang-Tidy original name: bugprone-suspicious-enum-usage)</p>


#### Suspicious Include {#CT_BUG_SI}
<p>The check detects various cases when an include refers to what appears to be an implementation file, which often leads to hard-to-track-down ODR violations.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="ot">#include &quot;Dinosaur.hpp&quot;     </span><span class="co">// OK, .hpp files tend not to have definitions.</span>
<span class="ot">#include &quot;Pterodactyl.h&quot;    </span><span class="co">// OK, .h files tend not to have definitions.</span>
<span class="ot">#include &quot;Velociraptor.cpp&quot; </span><span class="co">// Warning, filename is suspicious.</span>
<span class="ot">#include_next &lt;stdio.c&gt;     </span><span class="co">// Warning, filename is suspicious.</span></code></pre></div>
<h5 id="options-68">Options</h5>
<p>HeaderFileExtensions</p>
<p>Default value: &quot;;h;hh;hpp;hxx&quot; A semicolon-separated list of filename extensions of header files (the filename extensions should not contain a “.” prefix). For extension-less header files, use an empty string or leave an empty string between “;” if there are other filename extensions.</p>
<p>ImplementationFileExtensions</p>
<p>Default value: &quot;c;cc;cpp;cxx&quot; Likewise, a semicolon-separated list of filename extensions of implementation files.</p>
<p>(Clang-Tidy original name: bugprone-suspicious-include)</p>


#### Suspicious Memset Usage {#CT_BUG_SMU}
<p>This check finds memset() calls with potential mistakes in their arguments. Considering the function as void* memset(void* destination, int fill_value, size_t byte_count), the following cases are covered:</p>
<p><strong>Case 1: Fill value is a character <code>’0’</code></strong></p>
<p>Filling up a memory area with ASCII code 48 characters is not customary, possibly integer zeroes were intended instead. The check offers a replacement of '0' with 0. Memsetting character pointers with '0' is allowed.</p>
<p><strong>Case 2: Fill value is truncated</strong></p>
<p>Memset converts fill_value to unsigned char before using it. If fill_value is out of unsigned character range, it gets truncated and memory will not contain the desired pattern.</p>
<p><strong>Case 3: Byte count is zero</strong></p>
<p>Calling memset with a literal zero in its byte_count argument is likely to be unintended and swapped with fill_value. The check offers to swap these two arguments.</p>
<p>Corresponding cpplint.py check name: runtime/memset.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> foo() {
  <span class="dt">int</span> i[<span class="dv">5</span>] = {<span class="dv">1</span>, <span class="dv">2</span>, <span class="dv">3</span>, <span class="dv">4</span>, <span class="dv">5</span>};
  <span class="dt">int</span> *ip = i;
  <span class="dt">char</span> c = <span class="st">&#39;1&#39;</span>;
  <span class="dt">char</span> *cp = &amp;c;
  <span class="dt">int</span> v = <span class="dv">0</span>;

  <span class="co">// Case 1</span>
  memset(ip, <span class="st">&#39;0&#39;</span>, <span class="dv">1</span>); <span class="co">// suspicious</span>
  memset(cp, <span class="st">&#39;0&#39;</span>, <span class="dv">1</span>); <span class="co">// OK</span>

  <span class="co">// Case 2</span>
  memset(ip, <span class="bn">0xabcd</span>, <span class="dv">1</span>); <span class="co">// fill value gets truncated</span>
  memset(ip, <span class="bn">0x00</span>, <span class="dv">1</span>);   <span class="co">// OK</span>

  <span class="co">// Case 3</span>
  memset(ip, <span class="kw">sizeof</span>(<span class="dt">int</span>), v); <span class="co">// zero length, potentially swapped</span>
  memset(ip, <span class="dv">0</span>, <span class="dv">1</span>);           <span class="co">// OK</span>
}</code></pre></div>
<p>(Clang-Tidy original name: bugprone-suspicious-memset-usage)</p>


#### Suspicious Missing Comma {#CT_BUG_SMC}
<p>String literals placed side-by-side are concatenated at translation phase 6 (after the preprocessor). This feature is used to represent long string literal on multiple lines.</p>
<p>For instance, the following declarations are equivalent:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">const</span> <span class="dt">char</span>* A[] = <span class="st">&quot;This is a test&quot;</span>;
<span class="dt">const</span> <span class="dt">char</span>* B[] = <span class="st">&quot;This&quot;</span> <span class="st">&quot; is a &quot;</span>    <span class="st">&quot;test&quot;</span>;</code></pre></div>
<p>A common mistake done by programmers is to forget a comma between two string literals in an array initializer list.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">const</span> <span class="dt">char</span>* Test[] = {
  <span class="st">&quot;line 1&quot;</span>,
  <span class="st">&quot;line 2&quot;</span>     <span class="co">// Missing comma!</span>
  <span class="st">&quot;line 3&quot;</span>,
  <span class="st">&quot;line 4&quot;</span>,
  <span class="st">&quot;line 5&quot;</span>
};</code></pre></div>
<p>The array contains the string “line 2line3” at offset 1 (i.e. Test[1]). Clang won’t generate warnings at compile time.</p>
<p>This check may warn incorrectly on cases like:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">const</span> <span class="dt">char</span>* SupportedFormat[] = {
  <span class="st">&quot;Error </span><span class="ch">%s</span><span class="st">&quot;</span>,
  <span class="st">&quot;Code &quot;</span> PRIu64,   <span class="co">// May warn here.</span>
  <span class="st">&quot;Warning </span><span class="ch">%s</span><span class="st">&quot;</span>,
};</code></pre></div>
<h5 id="options-32">Options</h5>
<p>SizeThreshold</p>
<p>An unsigned integer specifying the minimum size of a string literal to be considered by the check. Default is 5U.</p>
<p>RatioThreshold</p>
<p>A string specifying the maximum threshold ratio [0, 1.0] of suspicious string literals to be considered. Default is &quot;.2&quot;.</p>
<p>MaxConcatenatedTokens</p>
<p>An unsigned integer specifying the maximum number of concatenated tokens. Default is 5U.</p>
<p>(Clang-Tidy original name: bugprone-suspicious-missing-comma)</p>


#### Suspicious Semicolon {#CT_BUG_SS}
<p>Finds most instances of stray semicolons that unexpectedly alter the meaning of the code. More specifically, it looks for if, while, for and for-range statements whose body is a single semicolon, and then analyzes the context of the code (e.g. indentation) in an attempt to determine whether that is intentional.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">if</span> (x &lt; y);
{
  x++;
}</code></pre></div>
<p>Here the body of the if statement consists of only the semicolon at the end of the first line, and x will be incremented regardless of the condition.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">while</span> ((line = readLine(file)) != NULL);
  processLine(line);</code></pre></div>
<p>As a result of this code, processLine() will only be called once, when the while loop with the empty body exits with line == NULL. The indentation of the code indicates the intention of the programmer.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">if</span> (x &gt;= y);
x -= y;</code></pre></div>
<p>While the indentation does not imply any nesting, there is simply no valid reason to have an if statement with an empty body (but it can make sense for a loop). So this check issues a warning for the code above.</p>
<p>To solve the issue remove the stray semicolon or in case the empty body is intentional, reflect this using code indentation or put the semicolon in a new line. For example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">while</span> (readWhitespace());
  Token t = readNextToken();</code></pre></div>
<p>Here the second line is indented in a way that suggests that it is meant to be the body of the while loop - whose body is in fact empty, because of the semicolon at the end of the first line.</p>
<p>Either remove the indentation from the second line:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">while</span> (readWhitespace());
Token t = readNextToken();</code></pre></div>
<p>… or move the semicolon from the end of the first line to a new line:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">while</span> (readWhitespace())
  ;

  Token t = readNextToken();</code></pre></div>
<p>In this case the check will assume that you know what you are doing, and will not raise a warning.</p>
<p>(Clang-Tidy original name: bugprone-suspicious-semicolon)</p>


#### Suspicious String Compare {#CT_BUG_SSC}
<p>Find suspicious usage of runtime string comparison functions. This check is valid in C and C++.</p>
<p>Checks for calls with implicit comparator and proposed to explicitly add it.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">if</span> (strcmp(...))       <span class="co">// Implicitly compare to zero</span>
<span class="kw">if</span> (!strcmp(...))      <span class="co">// Won&#39;t warn</span>
<span class="kw">if</span> (strcmp(...) != <span class="dv">0</span>)  <span class="co">// Won&#39;t warn</span></code></pre></div>
<p>Checks that compare function results (i,e, strcmp) are compared to valid constant. The resulting value is</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">&lt;  <span class="dv">0</span>    when lower than,
&gt;  <span class="dv">0</span>    when greater than,
== <span class="dv">0</span>    when equals.</code></pre></div>
<p>A common mistake is to compare the result to 1 or -1.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">if</span> (strcmp(...) == <span class="dv">-1</span>)  <span class="co">// Incorrect usage of the returned value.</span></code></pre></div>
<p>Additionally, the check warns if the results value is implicitly cast to a <em>suspicious</em> non-integer type. It’s happening when the returned value is used in a wrong context.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">if</span> (strcmp(...) &lt; <span class="fl">0.</span>)  <span class="co">// Incorrect usage of the returned value.</span></code></pre></div>
<h5 id="options-79">Options</h5>
<p>WarnOnImplicitComparison</p>
<p>When true, the check will warn on implicit comparison. true by default.</p>
<p>WarnOnLogicalNotComparison</p>
<p>When true, the check will warn on logical not comparison. false by default.</p>
<p>StringCompareLikeFunctions</p>
<p>A string specifying the comma-separated names of the extra string comparison functions. Default is an empty string. The check will detect the following string comparison functions: __builtin_memcmp, __builtin_strcasecmp, __builtin_strcmp, __builtin_strncasecmp, __builtin_strncmp, _mbscmp, _mbscmp_l, _mbsicmp, _mbsicmp_l, _mbsnbcmp, _mbsnbcmp_l, _mbsnbicmp, _mbsnbicmp_l, _mbsncmp, _mbsncmp_l, _mbsnicmp, _mbsnicmp_l, _memicmp, _memicmp_l, _stricmp, _stricmp_l, _strnicmp, _strnicmp_l, _wcsicmp, _wcsicmp_l, _wcsnicmp, _wcsnicmp_l, lstrcmp, lstrcmpi, memcmp, memicmp, strcasecmp, strcmp, strcmpi, stricmp, strncasecmp, strncmp, strnicmp, wcscasecmp, wcscmp, wcsicmp, wcsncmp, wcsnicmp, wmemcmp.</p>
<p>(Clang-Tidy original name: bugprone-suspicious-string-compare)</p>


#### Swapped Arguments {#CT_BUG_SA}
<p>Finds potentially swapped arguments by looking at implicit conversions.</p>
<p>(Clang-Tidy original name: bugprone-swapped-arguments)</p>


#### Terminating Continue {#CT_BUG_TC}
<p>Detects do while loops with a condition always evaluating to false that have a continue statement, as this continue terminates the loop effectively.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> f() {
<span class="kw">do</span> {
  <span class="co">// some code</span>
  <span class="kw">continue</span>; <span class="co">// terminating continue</span>
  <span class="co">// some other code</span>
} <span class="kw">while</span>(<span class="kw">false</span>);</code></pre></div>
<p>(Clang-Tidy original name: bugprone-terminating-continue)</p>


#### Throw Keyword Missing {#CT_BUG_TKM}
<p>Warns about a potentially missing throw keyword. If a temporary object is created, but the object’s type derives from (or is the same as) a class that has ‘EXCEPTION’, ‘Exception’ or ‘exception’ in its name, we can assume that the programmer’s intention was to throw that object.</p>
<p>Example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> f(<span class="dt">int</span> i) {
  <span class="kw">if</span> (i &lt; <span class="dv">0</span>) {
    <span class="co">// Exception is created but is not thrown.</span>
    std::runtime_error(<span class="st">&quot;Unexpected argument&quot;</span>);
  }
}</code></pre></div>
<p>(Clang-Tidy original name: bugprone-throw-keyword-missing)</p>


#### Too Small Loop Variable {#CT_BUG_TSLV}
<p>Detects those for loops that have a loop variable with a “too small” type which means this type can’t represent all values which are part of the iteration range.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">int</span> main() {
  <span class="dt">long</span> size = <span class="dv">294967296l</span>;
  <span class="kw">for</span> (<span class="dt">short</span> i = <span class="dv">0</span>; i &lt; size; ++i) {}
}</code></pre></div>
<p>This for loop is an infinite loop because the short type can’t represent all values in the [0..size] interval.</p>
<p>In a real use case size means a container’s size which depends on the user input.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">int</span> doSomething(<span class="dt">const</span> std::vector&amp; items) {
  <span class="kw">for</span> (<span class="dt">short</span> i = <span class="dv">0</span>; i &lt; items.size(); ++i) {}
}</code></pre></div>
<p>This algorithm works for small amount of objects, but will lead to freeze for a a larger user input.</p>
<p>MagnitudeBitsUpperLimit</p>
<p>Upper limit for the magnitude bits of the loop variable. If it’s set the check filters out those catches in which the loop variable’s type has more magnitude bits as the specified upper limit. The default value is 16. For example, if the user sets this option to 31 (bits), then a 32-bit unsigend int is ignored by the check, however a 32-bit int is not (A 32-bit signed int has 31 magnitude bits).</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">int</span> main() {
  <span class="dt">long</span> size = <span class="dv">294967296l</span>;
  <span class="kw">for</span> (<span class="dt">unsigned</span> i = <span class="dv">0</span>; i &lt; size; ++i) {} <span class="co">// no warning with MagnitudeBitsUpperLimit = 31 on a system where unsigned is 32-bit</span>
  <span class="kw">for</span> (<span class="dt">int</span> i = <span class="dv">0</span>; i &lt; size; ++i) {} <span class="co">// warning with MagnitudeBitsUpperLimit = 31 on a system where int is 32-bit</span>
}</code></pre></div>
<p>(Clang-Tidy original name: bugprone-too-small-loop-variable)</p>


#### Undefined Memory Manipulation {#CT_BUG_UMM}
<p>Finds calls of memory manipulation functions memset(), memcpy() and memmove() on not TriviallyCopyable objects resulting in undefined behavior.</p>
<p>(Clang-Tidy original name: bugprone-undefined-memory-manipulation)</p>


#### Undelegated Constructor {#CT_BUG_UC}
<p>Finds creation of temporary objects in constructors that look like a function call to another constructor of the same class.</p>
<p>The user most likely meant to use a delegating constructor or base class initializer.</p>
<p>(Clang-Tidy original name: bugprone-undelegated-constructor)</p>


#### Unhandled Self Assignment {#CT_BUG_USA}
<p>cert-oop54-cpp redirects here as an alias for this check. For the CERT alias, the WarnOnlyIfThisHasSuspiciousField option is set to false.</p>
<p>Finds user-defined copy assignment operators which do not protect the code against self-assignment either by checking self-assignment explicitly or using the copy-and-swap or the copy-and-move method.</p>
<p>By default, this check searches only those classes which have any pointer or C array field to avoid false positives. In case of a pointer or a C array, it’s likely that self-copy assignment breaks the object if the copy assignment operator was not written with care.</p>
<p>See also: <a href="https://wiki.sei.cmu.edu/confluence/display/cplusplus/OOP54-CPP.+Gracefully+handle+self-copy+assignment">OOP54-CPP. Gracefully handle self-copy assignment</a></p>
<p>A copy assignment operator must prevent that self-copy assignment ruins the object state. A typical use case is when the class has a pointer field and the copy assignment operator first releases the pointed object and then tries to assign it:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> T {
<span class="dt">int</span>* p;

<span class="kw">public</span>:
  T(<span class="dt">const</span> T &amp;rhs) : p(rhs.p ? <span class="kw">new</span> <span class="dt">int</span>(*rhs.p) : <span class="kw">nullptr</span>) {}
  ~T() { <span class="kw">delete</span> p; }

  <span class="co">// ...</span>

  T&amp; <span class="kw">operator</span>=(<span class="dt">const</span> T &amp;rhs) {
    <span class="kw">delete</span> p;
    p = <span class="kw">new</span> <span class="dt">int</span>(*rhs.p);
    <span class="kw">return</span> *<span class="kw">this</span>;
  }
};</code></pre></div>
<p>There are two common C++ patterns to avoid this problem. The first is the self-assignment check:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> T {
<span class="dt">int</span>* p;

<span class="kw">public</span>:
  T(<span class="dt">const</span> T &amp;rhs) : p(rhs.p ? <span class="kw">new</span> <span class="dt">int</span>(*rhs.p) : <span class="kw">nullptr</span>) {}
  ~T() { <span class="kw">delete</span> p; }

  <span class="co">// ...</span>

  T&amp; <span class="kw">operator</span>=(<span class="dt">const</span> T &amp;rhs) {
    <span class="kw">if</span>(<span class="kw">this</span> == &amp;rhs)
      <span class="kw">return</span> *<span class="kw">this</span>;

    <span class="kw">delete</span> p;
    p = <span class="kw">new</span> <span class="dt">int</span>(*rhs.p);
    <span class="kw">return</span> *<span class="kw">this</span>;
  }
};</code></pre></div>
<p>The second one is the copy-and-swap method when we create a temporary copy (using the copy constructor) and then swap this temporary object with this:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> T {
<span class="dt">int</span>* p;

<span class="kw">public</span>:
  T(<span class="dt">const</span> T &amp;rhs) : p(rhs.p ? <span class="kw">new</span> <span class="dt">int</span>(*rhs.p) : <span class="kw">nullptr</span>) {}
  ~T() { <span class="kw">delete</span> p; }

  <span class="co">// ...</span>

  <span class="dt">void</span> swap(T &amp;rhs) {
    <span class="kw">using</span> std::swap;
    swap(p, rhs.p);
  }

  T&amp; <span class="kw">operator</span>=(<span class="dt">const</span> T &amp;rhs) {
    T(rhs).swap(*<span class="kw">this</span>);
    <span class="kw">return</span> *<span class="kw">this</span>;
  }
};</code></pre></div>
<p>There is a third pattern which is less common. Let’s call it the copy-and-move method when we create a temporary copy (using the copy constructor) and then move this temporary object into this (needs a move assignment operator):</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> T {
<span class="dt">int</span>* p;

<span class="kw">public</span>:
  T(<span class="dt">const</span> T &amp;rhs) : p(rhs.p ? <span class="kw">new</span> <span class="dt">int</span>(*rhs.p) : <span class="kw">nullptr</span>) {}
  ~T() { <span class="kw">delete</span> p; }

  <span class="co">// ...</span>

  T&amp; <span class="kw">operator</span>=(<span class="dt">const</span> T &amp;rhs) {
    T t = rhs;
    *<span class="kw">this</span> = std::move(t);
    <span class="kw">return</span> *<span class="kw">this</span>;
  }

  T&amp; <span class="kw">operator</span>=(T &amp;&amp;rhs) {
    p = rhs.p;
    rhs.p = <span class="kw">nullptr</span>;
    <span class="kw">return</span> *<span class="kw">this</span>;
  }
};</code></pre></div>
<p>WarnOnlyIfThisHasSuspiciousField</p>
<p>When true, the check will warn only if the container class of the copy assignment operator has any suspicious fields (pointer or C array). This option is set to true by default.</p>
<p>(Clang-Tidy original name: bugprone-unhandled-self-assignment)</p>


#### Unused Raii {#CT_BUG_UR}
<p>Finds temporaries that look like RAII objects.</p>
<p>The canonical example for this is a scoped lock.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">{
  scoped_lock(&amp;global_mutex);
  critical_section();
}</code></pre></div>
<p>The destructor of the scoped_lock is called before the critical_section is entered, leaving it unprotected.</p>
<p>We apply a number of heuristics to reduce the false positive count of this check:</p>
<ul>
<li>Ignore code expanded from macros. Testing frameworks make heavy use of this.</li>
<li>Ignore types with trivial destructors. They are very unlikely to be RAII objects and there’s no difference when they are deleted.</li>
<li>Ignore objects at the end of a compound statement (doesn’t change behavior).</li>
<li>Ignore objects returned from a call.</li>
</ul>
<p>(Clang-Tidy original name: bugprone-unused-raii)</p>


#### Unused Return Value {#CT_BUG_URV}
<p>Warns on unused function return values. The checked functions can be configured.</p>
<h5 id="options-23">Options</h5>
<p>CheckedFunctions</p>
<p>Semicolon-separated list of functions to check. Defaults to ::std::async;::std::launder;::std::remove;::std::remove_if;::std::unique;::std::unique_ptr::release;::std::basic_string::empty;::std::vector::empty. This means that the calls to following functions are checked by default:</p>
<ul>
<li>std::async(). Not using the return value makes the call synchronous.</li>
<li>std::launder(). Not using the return value usually means that the function interface was misunderstood by the programmer. Only the returned pointer is “laundered”, not the argument.</li>
<li>std::remove(), std::remove_if() and std::unique(). The returned iterator indicates the boundary between elements to keep and elements to be removed. Not using the return value means that the information about which elements to remove is lost.</li>
<li>std::unique_ptr::release(). Not using the return value can lead to resource leaks if the same pointer isn’t stored anywhere else. Often, ignoring the release() return value indicates that the programmer confused the function with reset().</li>
<li>std::basic_string::empty() and std::vector::empty(). Not using the return value often indicates that the programmer confused the function with clear().</li>
</ul>
<p>(Clang-Tidy original name: bugprone-unused-return-value)</p>


#### Use After Move {#CT_BUG_UAM}
<p>Warns if an object is used after it has been moved, for example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::string str = <span class="st">&quot;Hello, world!</span><span class="ch">\n</span><span class="st">&quot;</span>;
std::vector&lt;std::string&gt; messages;
messages.emplace_back(std::move(str));
std::cout &lt;&lt; str;</code></pre></div>
<p>The last line will trigger a warning that str is used after it has been moved.</p>
<p>The check does not trigger a warning if the object is reinitialized after the move and before the use. For example, no warning will be output for this code:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">messages.emplace_back(std::move(str));
str = <span class="st">&quot;Greetings, stranger!</span><span class="ch">\n</span><span class="st">&quot;</span>;
std::cout &lt;&lt; str;</code></pre></div>
<p>The check takes control flow into account. A warning is only emitted if the use can be reached from the move. This means that the following code does not produce a warning:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">if</span> (condition) {
  messages.emplace_back(std::move(str));
} <span class="kw">else</span> {
  std::cout &lt;&lt; str;
}</code></pre></div>
<p>On the other hand, the following code does produce a warning:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">for</span> (<span class="dt">int</span> i = <span class="dv">0</span>; i &lt; <span class="dv">10</span>; ++i) {
  std::cout &lt;&lt; str;
  messages.emplace_back(std::move(str));
}</code></pre></div>
<p>(The use-after-move happens on the second iteration of the loop.)</p>
<p>In some cases, the check may not be able to detect that two branches are mutually exclusive. For example (assuming that i is an int):</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">if</span> (i == <span class="dv">1</span>) {
  messages.emplace_back(std::move(str));
}
<span class="kw">if</span> (i == <span class="dv">2</span>) {
  std::cout &lt;&lt; str;
}</code></pre></div>
<p>In this case, the check will erroneously produce a warning, even though it is not possible for both the move and the use to be executed.</p>
<p>An erroneous warning can be silenced by reinitializing the object after the move:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">if</span> (i == <span class="dv">1</span>) {
  messages.emplace_back(std::move(str));
  str = <span class="st">&quot;&quot;</span>;
}
<span class="kw">if</span> (i == <span class="dv">2</span>) {
  std::cout &lt;&lt; str;
}</code></pre></div>
<p>Subsections below explain more precisely what exactly the check considers to be a move, use, and reinitialization.</p>
<h5 id="unsequenced-moves-uses-and-reinitializations">Unsequenced moves, uses, and reinitializations</h5>
<p>In many cases, C++ does not make any guarantees about the order in which sub-expressions of a statement are evaluated. This means that in code like the following, it is not guaranteed whether the use will happen before or after the move:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> f(<span class="dt">int</span> i, std::vector&lt;<span class="dt">int</span>&gt; v);
std::vector&lt;<span class="dt">int</span>&gt; v = { <span class="dv">1</span>, <span class="dv">2</span>, <span class="dv">3</span> };
f(v[<span class="dv">1</span>], std::move(v));</code></pre></div>
<p>In this kind of situation, the check will note that the use and move are unsequenced.</p>
<p>The check will also take sequencing rules into account when reinitializations occur in the same statement as moves or uses. A reinitialization is only considered to reinitialize a variable if it is guaranteed to be evaluated after the move and before the use.</p>
<h5 id="move">Move</h5>
<p>The check currently only considers calls of std::move on local variables or function parameters. It does not check moves of member variables or global variables.</p>
<p>Any call of std::move on a variable is considered to cause a move of that variable, even if the result of std::move is not passed to an rvalue reference parameter.</p>
<p>This means that the check will flag a use-after-move even on a type that does not define a move constructor or move assignment operator. This is intentional. Developers may use std::move on such a type in the expectation that the type will add move semantics in the future. If such a std::move has the potential to cause a use-after-move, we want to warn about it even if the type does not implement move semantics yet.</p>
<p>Furthermore, if the result of std::move <em>is</em> passed to an rvalue reference parameter, this will always be considered to cause a move, even if the function that consumes this parameter does not move from it, or if it does so only conditionally. For example, in the following situation, the check will assume that a move always takes place:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::vector&lt;std::string&gt; messages;
<span class="dt">void</span> f(std::string &amp;&amp;str) {
  <span class="co">// Only remember the message if it isn&#39;t empty.</span>
  <span class="kw">if</span> (!str.empty()) {
    messages.emplace_back(std::move(str));
  }
}
std::string str = <span class="st">&quot;&quot;</span>;
f(std::move(str));</code></pre></div>
<p>The check will assume that the last line causes a move, even though, in this particular case, it does not. Again, this is intentional.</p>
<p>When analyzing the order in which moves, uses and reinitializations happen (see section <a href="#unsequenced-moves-uses-and-reinitializations">Unsequenced moves, uses, and reinitializations</a>), the move is assumed to occur in whichever function the result of the std::move is passed to.</p>
<h5 id="use">Use</h5>
<p>Any occurrence of the moved variable that is not a reinitialization (see below) is considered to be a use.</p>
<p>An exception to this are objects of type std::unique_ptr, std::shared_ptr and std::weak_ptr, which have defined move behavior (objects of these classes are guaranteed to be empty after they have been moved from). Therefore, an object of these classes will only be considered to be used if it is dereferenced, i.e. if operator*, operator-&gt; or operator[] (in the case of std::unique_ptr<T []>) is called on it.</p>
<p>If multiple uses occur after a move, only the first of these is flagged.</p>
<h5 id="reinitialization">Reinitialization</h5>
<p>The check considers a variable to be reinitialized in the following cases:</p>
<ul>
<li>The variable occurs on the left-hand side of an assignment.</li>
<li>The variable is passed to a function as a non-const pointer or non-const lvalue reference. (It is assumed that the variable may be an out-parameter for the function.)</li>
<li>clear() or assign() is called on the variable and the variable is of one of the standard container types basic_string, vector, deque, forward_list, list, set, map, multiset, multimap, unordered_set, unordered_map, unordered_multiset, unordered_multimap.</li>
<li>reset() is called on the variable and the variable is of type std::unique_ptr, std::shared_ptr or std::weak_ptr.</li>
<li>A member function marked with the [[clang::reinitializes]] attribute is called on the variable.</li>
</ul>
<p>If the variable in question is a struct and an individual member variable of that struct is written to, the check does not consider this to be a reinitialization – even if, eventually, all member variables of the struct are written to. For example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">struct</span> S {
  std::string str;
  <span class="dt">int</span> i;
};
S s = { <span class="st">&quot;Hello, world!</span><span class="ch">\n</span><span class="st">&quot;</span>, <span class="dv">42</span> };
S s_other = std::move(s);
s.str = <span class="st">&quot;Lorem ipsum&quot;</span>;
s.i = <span class="dv">99</span>;</code></pre></div>
<p>The check will not consider s to be reinitialized after the last line; instead, the line that assigns to s.str will be flagged as a use-after-move. This is intentional as this pattern of reinitializing a struct is error-prone. For example, if an additional member variable is added to S, it is easy to forget to add the reinitialization for this additional member. Instead, it is safer to assign to the entire struct in one go, and this will also avoid the use-after-move warning.</p>
<p>(Clang-Tidy original name: bugprone-use-after-move)</p>


#### Virtual Near Miss {#CT_BUG_VNM}
<p>Warn if a function is a near miss (ie. the name is very similar and the function signature is the same) to a virtual function from a base class.</p>
<p>Example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">struct</span> Base {
  <span class="kw">virtual</span> <span class="dt">void</span> func();
};

<span class="kw">struct</span> Derived : Base {
  <span class="kw">virtual</span> funk();
  <span class="co">// warning: &#39;Derived::funk&#39; has a similar name and the same signature as virtual method &#39;Base::func&#39;; did you mean to override it?</span>
};</code></pre></div>
<p>(Clang-Tidy original name: bugprone-virtual-near-miss)</p>


### C++ Core Guidelines

#### Avoid C Arrays {#CT_CPP_ACA}
<p>The cppcoreguidelines-avoid-c-arrays check is an alias, please see <a href="modernize-avoid-c-arrays.html">modernize-avoid-c-arrays</a> for more information.</p>
<p>(Clang-Tidy original name: cppcoreguidelines-avoid-c-arrays)</p>


#### Avoid Goto {#CT_CPP_AG}
<p>The usage of goto for control flow is error prone and should be replaced with looping constructs. Only forward jumps in nested loops are accepted.</p>
<p>This check implements <a href="https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#es76-avoid-goto">ES.76</a> from the CppCoreGuidelines and <a href="http://www.codingstandard.com/rule/6-3-1-ensure-that-the-labels-for-a-jump-statement-or-a-switch-condition-appear-later-in-the-same-or-an-enclosing-block/">6.3.1 from High Integrity C++</a>.</p>
<p>For more information on why to avoid programming with goto you can read the famous paper <a href="https://www.cs.utexas.edu/users/EWD/ewd02xx/EWD215.PDF">A Case against the GO TO Statement.</a>.</p>
<p>The check diagnoses goto for backward jumps in every language mode. These should be replaced with C/C++ looping constructs.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// Bad, handwritten for loop.</span>
<span class="dt">int</span> i = <span class="dv">0</span>;
<span class="co">// Jump label for the loop</span>
loop_start:
do_some_operation();

<span class="kw">if</span> (i &lt; <span class="dv">100</span>) {
  ++i;
  <span class="kw">goto</span> loop_start;
}

<span class="co">// Better</span>
<span class="kw">for</span>(<span class="dt">int</span> i = <span class="dv">0</span>; i &lt; <span class="dv">100</span>; ++i)
  do_some_operation();</code></pre></div>
<p>Modern C++ needs goto only to jump out of nested loops.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">for</span>(<span class="dt">int</span> i = <span class="dv">0</span>; i &lt; <span class="dv">100</span>; ++i) {
  <span class="kw">for</span>(<span class="dt">int</span> j = <span class="dv">0</span>; j &lt; <span class="dv">100</span>; ++j) {
    <span class="kw">if</span> (i * j &gt; <span class="dv">500</span>)
      <span class="kw">goto</span> early_exit;
  }
}

early_exit:
some_operation();</code></pre></div>
<p>All other uses of goto are diagnosed in C++.</p>
<p>(Clang-Tidy original name: cppcoreguidelines-avoid-goto)</p>


#### Avoid Magic Numbers {#CT_CPP_AMN}
<p>The cppcoreguidelines-avoid-magic-numbers check is an alias, please see <a href="readability-magic-numbers.html">readability-magic-numbers</a> for more information.</p>
<p>(Clang-Tidy original name: cppcoreguidelines-avoid-magic-numbers)</p>


#### Avoid Non Const Global Variables {#CT_CPP_ANCGV}
<p>Finds non-const global variables as described in <a href="https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#Ri-global">I.2 of C++ Core Guidelines</a> . As <a href="https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#Rr-global">R.6 of C++ Core Guidelines</a> is a duplicate of rule I.2 it also covers that rule.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">char</span> a;  <span class="co">// Warns!</span>
<span class="dt">const</span> <span class="dt">char</span> b =  <span class="dv">0</span>;

<span class="kw">namespace</span> some_namespace
{
    <span class="dt">char</span> c;  <span class="co">// Warns!</span>
    <span class="dt">const</span> <span class="dt">char</span> d = <span class="dv">0</span>;
}

<span class="dt">char</span> * c_ptr1 = &amp;some_namespace::c;  <span class="co">// Warns!</span>
<span class="dt">char</span> *<span class="dt">const</span> c_const_ptr = &amp;some_namespace::c;  <span class="co">// Warns!</span>
<span class="dt">char</span> &amp; c_reference = some_namespace::c;  <span class="co">// Warns!</span>

<span class="kw">class</span> Foo  <span class="co">// No Warnings inside Foo, only namespace scope is covered</span>
{
<span class="kw">public</span>:
    <span class="dt">char</span> e = <span class="dv">0</span>;
    <span class="dt">const</span> <span class="dt">char</span> f = <span class="dv">0</span>;
<span class="kw">protected</span>:
    <span class="dt">char</span> g = <span class="dv">0</span>;
<span class="kw">private</span>:
    <span class="dt">char</span> h = <span class="dv">0</span>;
};</code></pre></div>
<p>Variables: a, c, c_ptr1, c_ptr2, c_const_ptr and c_reference, will all generate warnings since they are either: a globally accessible variable and non-const, a pointer or reference providing global access to non-const data or both.</p>
<p>(Clang-Tidy original name: cppcoreguidelines-avoid-non-const-global-variables)</p>


#### C Copy Assignment Signature {#CT_CPP_CCAS}
<p>The cppcoreguidelines-c-copy-assignment-signature check is an alias, please see <a href="misc-unconventional-assign-operator.html">misc-unconventional-assign-operator</a> for more information.</p>
<p>(Clang-Tidy original name: cppcoreguidelines-c-copy-assignment-signature)</p>


#### Explicit Virtual Functions {#CT_CPP_EVF}
<p>The cppcoreguidelines-explicit-virtual-functions check is an alias, please see <a href="modernize-use-override.html">modernize-use-override</a> for more information.</p>
<p>(Clang-Tidy original name: cppcoreguidelines-explicit-virtual-functions)</p>


#### Init Variables {#CT_CPP_IV}
<p>Checks whether there are local variables that are declared without an initial value. These may lead to unexpected behaviour if there is a code path that reads the variable before assigning to it.</p>
<p>Only integers, booleans, floats, doubles and pointers are checked. The fix option initializes all detected values with the value of zero. An exception is float and double types, which are initialized to NaN.</p>
<p>As an example a function that looks like this:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> function() {
  <span class="dt">int</span> x;
  <span class="dt">char</span> *txt;
  <span class="dt">double</span> d;

  <span class="co">// Rest of the function.</span>
}</code></pre></div>
<p>Would be rewritten to look like this:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="ot">#include &lt;math.h&gt;</span>

<span class="dt">void</span> function() {
  <span class="dt">int</span> x = <span class="dv">0</span>;
  <span class="dt">char</span> *txt = <span class="kw">nullptr</span>;
  <span class="dt">double</span> d = NAN;

  <span class="co">// Rest of the function.</span>
}</code></pre></div>
<h5 id="options-57">Options</h5>
<p>IncludeStyle</p>
<p>A string specifying which include-style is used, llvm or google. Default is llvm.</p>
<p>MathHeader</p>
<p>A string specifying the header to include to get the definition of NAN. Default is <math.h>.</p>
<p>(Clang-Tidy original name: cppcoreguidelines-init-variables)</p>


#### Interfaces Global Init {#CT_CPP_IGI}
<p>This check flags initializers of globals that access extern objects, and therefore can lead to order-of-initialization problems.</p>
<p>This rule is part of the “Interfaces” profile of the C++ Core Guidelines, see <a href="https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#Ri-global-init" class="uri">https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#Ri-global-init</a></p>
<p>Note that currently this does not flag calls to non-constexpr functions, and therefore globals could still be accessed from functions themselves.</p>
<p>(Clang-Tidy original name: cppcoreguidelines-interfaces-global-init)</p>


#### Macro Usage {#CT_CPP_MU}
<p>Finds macro usage that is considered problematic because better language constructs exist for the task.</p>
<p>The relevant sections in the C++ Core Guidelines are <a href="https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#enum1-prefer-enumerations-over-macros">Enum.1</a>, <a href="https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#es30-dont-use-macros-for-program-text-manipulation">ES.30</a>, <a href="https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#es31-dont-use-macros-for-constants-or-functions">ES.31</a> and <a href="https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#es33-if-you-must-use-macros-give-them-unique-names">ES.33</a>.</p>
<h5 id="options-3">Options</h5>
<p>AllowedRegexp</p>
<p>A regular expression to filter allowed macros. For example DEBUG<em>|LIBTORRENT</em>|TORRENT<em>|UNI</em> could be applied to filter libtorrent. Default value is ^DEBUG_*.</p>
<p>CheckCapsOnly</p>
<p>Boolean flag to warn on all macros except those with CAPS_ONLY names. This option is intended to ease introduction of this check into older code bases. Default value is false.</p>
<p>IgnoreCommandLineMacros</p>
<p>Boolean flag to toggle ignoring command-line-defined macros. Default value is true.</p>
<p>(Clang-Tidy original name: cppcoreguidelines-macro-usage)</p>


#### Narrowing Conversions {#CT_CPP_NC}
<p>Checks for silent narrowing conversions, e.g: int i = 0; i += 0.1;. While the issue is obvious in this former example, it might not be so in the following: void MyClass::f(double d) { int_member_ += d; }.</p>
<p>This rule is part of the “Expressions and statements” profile of the C++ Core Guidelines, corresponding to rule ES.46. See</p>
<p><a href="https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#es46-avoid-lossy-narrowing-truncating-arithmetic-conversions" class="uri">https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#es46-avoid-lossy-narrowing-truncating-arithmetic-conversions</a>.</p>
<p>We enforce only part of the guideline, more specifically, we flag narrowing conversions from:</p>
<ul>
<li>an integer to a narrower integer (e.g. char to unsigned char),</li>
<li>an integer to a narrower floating-point (e.g. uint64_t to float),</li>
<li>a floating-point to an integer (e.g. double to int),</li>
<li>a floating-point to a narrower floating-point (e.g. double to float) if WarnOnFloatingPointNarrowingConversion Option is set.</li>
</ul>
<p>This check will flag:</p>
<ul>
<li>All narrowing conversions that are not marked by an explicit cast (c-style or static_cast). For example: int i = 0; i += 0.1;, void f(int); f(0.1);,</li>
<li>All applications of binary operators with a narrowing conversions. For example: int i; i+= 0.1;.</li>
</ul>
<h5 id="options-8">Options</h5>
<p>WarnOnFloatingPointNarrowingConversion</p>
<p>When true, the check will warn on narrowing floating point conversion (e.g. double to float). true by default.</p>
<p>PedanticMode</p>
<p>When true, the check will warn on assigning a floating point constant to an integer value even if the floating point value is exactly representable in the destination type (e.g. int i = 1.0;). false by default.</p>
<h5 id="faq">FAQ</h5>
<ul>
<li>What does “narrowing conversion from ‘int’ to ‘float’” mean?</li>
</ul>
<p>An IEEE754 Floating Point number can represent all integer values in the range [-2^PrecisionBits, 2^PrecisionBits] where PrecisionBits is the number of bits in the mantissa.</p>
<p>For float this would be [-2^23, 2^23], where int can represent values in the range [-2^31, 2^31-1].</p>
<ul>
<li>What does “implementation-defined” mean?</li>
</ul>
<p>You may have encountered messages like “narrowing conversion from ‘unsigned int’ to signed type ‘int’ is implementation-defined”. The C/C++ standard does not mandate two’s complement for signed integers, and so the compiler is free to define what the semantics are for converting an unsigned integer to signed integer. Clang’s implementation uses the two’s complement format.</p>
<p>(Clang-Tidy original name: cppcoreguidelines-narrowing-conversions)</p>


#### No Malloc {#CT_CPP_NM}
<p>This check handles C-Style memory management using malloc(), realloc(), calloc() and free(). It warns about its use and tries to suggest the use of an appropriate RAII object. Furthermore, it can be configured to check against a user-specified list of functions that are used for memory management (e.g. posix_memalign()). See <a href="https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#Rr-mallocfree">C++ Core Guidelines</a>.</p>
<p>There is no attempt made to provide fix-it hints, since manual resource management isn’t easily transformed automatically into RAII.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// Warns each of the following lines.</span>
<span class="co">// Containers like std::vector or std::string should be used.</span>
<span class="dt">char</span>* some_string = (<span class="dt">char</span>*) malloc(<span class="kw">sizeof</span>(<span class="dt">char</span>) * <span class="dv">20</span>);
<span class="dt">char</span>* some_string = (<span class="dt">char</span>*) realloc(<span class="kw">sizeof</span>(<span class="dt">char</span>) * <span class="dv">30</span>);
free(some_string);

<span class="dt">int</span>* int_array = (<span class="dt">int</span>*) calloc(<span class="dv">30</span>, <span class="kw">sizeof</span>(<span class="dt">int</span>));

<span class="co">// Rather use a smartpointer or stack variable.</span>
<span class="kw">struct</span> some_struct* s = (<span class="kw">struct</span> some_struct*) malloc(<span class="kw">sizeof</span>(<span class="kw">struct</span> some_struct));</code></pre></div>
<h5 id="options-52">Options</h5>
<p>Allocations</p>
<p>Semicolon-separated list of fully qualified names of memory allocation functions. Defaults to ::malloc;::calloc.</p>
<p>Deallocations</p>
<p>Semicolon-separated list of fully qualified names of memory allocation functions. Defaults to ::free.</p>
<p>Reallocations</p>
<p>Semicolon-separated list of fully qualified names of memory allocation functions. Defaults to ::realloc.</p>
<p>(Clang-Tidy original name: cppcoreguidelines-no-malloc)</p>


#### Non Private Member Variables In Classes {#CT_CPP_NPMVIC}
<p>The cppcoreguidelines-non-private-member-variables-in-classes check is an alias, please see <a href="misc-non-private-member-variables-in-classes.html">misc-non-private-member-variables-in-classes</a> for more information.</p>
<p>(Clang-Tidy original name: cppcoreguidelines-non-private-member-variables-in-classes)</p>


#### Owning Memory {#CT_CPP_OM}
<p>This check implements the type-based semantics of gsl::owner<T*>, which allows static analysis on code, that uses raw pointers to handle resources like dynamic memory, but won’t introduce RAII concepts.</p>
<p>The relevant sections in the <a href="https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md">C++ Core Guidelines</a> are I.11, C.33, R.3 and GSL.Views The definition of a gsl::owner<T*> is straight forward</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">namespace</span> gsl { <span class="kw">template</span> &lt;<span class="kw">typename</span> T&gt; owner = T; }</code></pre></div>
<p>It is therefore simple to introduce the owner even without using an implementation of the <a href="https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#gsl-guideline-support-library">Guideline Support Library</a>.</p>
<p>All checks are purely type based and not (yet) flow sensitive.</p>
<p>The following examples will demonstrate the correct and incorrect initializations of owners, assignment is handled the same way. Note that both new and malloc()-like resource functions are considered to produce resources.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// Creating an owner with factory functions is checked.</span>
gsl::owner&lt;<span class="dt">int</span>*&gt; function_that_returns_owner() { <span class="kw">return</span> gsl::owner&lt;<span class="dt">int</span>*&gt;(<span class="kw">new</span> <span class="dt">int</span>(<span class="dv">42</span>)); }

<span class="co">// Dynamic memory must be assigned to an owner</span>
<span class="dt">int</span>* Something = <span class="kw">new</span> <span class="dt">int</span>(<span class="dv">42</span>); <span class="co">// BAD, will be caught</span>
gsl::owner&lt;<span class="dt">int</span>*&gt; Owner = <span class="kw">new</span> <span class="dt">int</span>(<span class="dv">42</span>); <span class="co">// Good</span>
gsl::owner&lt;<span class="dt">int</span>*&gt; Owner = <span class="kw">new</span> <span class="dt">int</span>[<span class="dv">42</span>]; <span class="co">// Good as well</span>

<span class="co">// Returned owner must be assigned to an owner</span>
<span class="dt">int</span>* Something = function_that_returns_owner(); <span class="co">// Bad, factory function</span>
gsl::owner&lt;<span class="dt">int</span>*&gt; Owner = function_that_returns_owner(); <span class="co">// Good, result lands in owner</span>

<span class="co">// Something not a resource or owner should not be assigned to owners</span>
<span class="dt">int</span> Stack = <span class="dv">42</span>;
gsl::owner&lt;<span class="dt">int</span>*&gt; Owned = &amp;Stack; <span class="co">// Bad, not a resource assigned</span></code></pre></div>
<p>In the case of dynamic memory as resource, only gsl::owner<T*> variables are allowed to be deleted.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// Example Bad, non-owner as resource handle, will be caught.</span>
<span class="dt">int</span>* NonOwner = <span class="kw">new</span> <span class="dt">int</span>(<span class="dv">42</span>); <span class="co">// First warning here, since new must land in an owner</span>
<span class="kw">delete</span> NonOwner; <span class="co">// Second warning here, since only owners are allowed to be deleted</span>

<span class="co">// Example Good, Ownership correctly stated</span>
gsl::owner&lt;<span class="dt">int</span>*&gt; Owner = <span class="kw">new</span> <span class="dt">int</span>(<span class="dv">42</span>); <span class="co">// Good</span>
<span class="kw">delete</span> Owner; <span class="co">// Good as well, statically enforced, that only owners get deleted</span></code></pre></div>
<p>The check will furthermore ensure, that functions, that expect a gsl::owner<T*> as argument get called with either a gsl::owner<T*> or a newly created resource.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> expects_owner(gsl::owner&lt;<span class="dt">int</span>*&gt; o) { <span class="kw">delete</span> o; }

<span class="co">// Bad Code</span>
<span class="dt">int</span> NonOwner = <span class="dv">42</span>;
expects_owner(&amp;NonOwner); <span class="co">// Bad, will get caught</span>

<span class="co">// Good Code</span>
gsl::owner&lt;<span class="dt">int</span>*&gt; Owner = <span class="kw">new</span> <span class="dt">int</span>(<span class="dv">42</span>);
expects_owner(Owner); <span class="co">// Good</span>
expects_owner(<span class="kw">new</span> <span class="dt">int</span>(<span class="dv">42</span>)); <span class="co">// Good as well, recognized created resource</span>

<span class="co">// Port legacy code for better resource-safety</span>
gsl::owner&lt;FILE*&gt; File = fopen(<span class="st">&quot;my_file.txt&quot;</span>, <span class="st">&quot;rw+&quot;</span>);
FILE* BadFile = fopen(<span class="st">&quot;another_file.txt&quot;</span>, <span class="st">&quot;w&quot;</span>); <span class="co">// Bad, warned</span>

<span class="co">// ... use the file</span>

fclose(File); <span class="co">// Ok, File is annotated as &#39;owner&lt;&gt;&#39;</span>
fclose(BadFile); <span class="co">// BadFile is not an &#39;owner&lt;&gt;&#39;, will be warned</span></code></pre></div>
<h5 id="options-76">Options</h5>
<p>LegacyResourceProducers</p>
<p>Semicolon-separated list of fully qualified names of legacy functions that create resources but cannot introduce gsl::owner&lt;&gt;. Defaults to ::malloc;::aligned_alloc;::realloc;::calloc;::fopen;::freopen;::tmpfile.</p>
<p>LegacyResourceConsumers</p>
<p>Semicolon-separated list of fully qualified names of legacy functions expecting resource owners as pointer arguments but cannot introduce gsl::owner&lt;&gt;. Defaults to ::free;::realloc;::freopen;::fclose.</p>
<h5 id="limitations-4">Limitations</h5>
<p>Using gsl::owner<T*> in a typedef or alias is not handled correctly.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">using</span> heap_int = gsl::owner&lt;<span class="dt">int</span>*&gt;;
heap_int allocated = <span class="kw">new</span> <span class="dt">int</span>(<span class="dv">42</span>); <span class="co">// False positive!</span></code></pre></div>
<p>The gsl::owner<T*> is declared as a templated type alias. In template functions and classes, like in the example below, the information of the type aliases gets lost. Therefore using gsl::owner<T*> in a heavy templated code base might lead to false positives.</p>
<p>Known code constructs that do not get diagnosed correctly are:</p>
<ul>
<li>std::exchange</li>
<li>std::vector<gsl::owner<T*>&gt;</li>
</ul>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// This template function works as expected. Type information doesn&#39;t get lost.</span>
<span class="kw">template</span> &lt;<span class="kw">typename</span> T&gt;
<span class="dt">void</span> delete_owner(gsl::owner&lt;T*&gt; owned_object) {
  <span class="kw">delete</span> owned_object; <span class="co">// Everything alright</span>
}

gsl::owner&lt;<span class="dt">int</span>*&gt; function_that_returns_owner() { <span class="kw">return</span> gsl::owner&lt;<span class="dt">int</span>*&gt;(<span class="kw">new</span> <span class="dt">int</span>(<span class="dv">42</span>)); }

<span class="co">// Type deduction does not work for auto variables.</span>
<span class="co">// This is caught by the check and will be noted accordingly.</span>
<span class="kw">auto</span> OwnedObject = function_that_returns_owner(); <span class="co">// Type of OwnedObject will be int*</span>

<span class="co">// Problematic function template that looses the typeinformation on owner</span>
<span class="kw">template</span> &lt;<span class="kw">typename</span> T&gt;
<span class="dt">void</span> bad_template_function(T some_object) {
  <span class="co">// This line will trigger the warning, that a non-owner is assigned to an owner</span>
  gsl::owner&lt;T*&gt; new_owner = some_object;
}

<span class="co">// Calling the function with an owner still yields a false positive.</span>
bad_template_function(gsl::owner&lt;<span class="dt">int</span>*&gt;(<span class="kw">new</span> <span class="dt">int</span>(<span class="dv">42</span>)));


<span class="co">// The same issue occurs with templated classes like the following.</span>
<span class="kw">template</span> &lt;<span class="kw">typename</span> T&gt;
<span class="kw">class</span> OwnedValue {
<span class="kw">public</span>:
  <span class="dt">const</span> T getValue() <span class="dt">const</span> { <span class="kw">return</span> _val; }
<span class="kw">private</span>:
  T _val;
};

<span class="co">// Code, that yields a false positive.</span>
OwnedValue&lt;gsl::owner&lt;<span class="dt">int</span>*&gt;&gt; Owner(<span class="kw">new</span> <span class="dt">int</span>(<span class="dv">42</span>)); <span class="co">// Type deduction yield T -&gt; int *</span>
<span class="co">// False positive, getValue returns int* and not gsl::owner&lt;int*&gt;</span>
gsl::owner&lt;<span class="dt">int</span>*&gt; OwnedInt = Owner.getValue();</code></pre></div>
<p>Another limitation of the current implementation is only the type based checking. Suppose you have code like the following:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// Two owners with assigned resources</span>
gsl::owner&lt;<span class="dt">int</span>*&gt; Owner1 = <span class="kw">new</span> <span class="dt">int</span>(<span class="dv">42</span>);
gsl::owner&lt;<span class="dt">int</span>*&gt; Owner2 = <span class="kw">new</span> <span class="dt">int</span>(<span class="dv">42</span>);

Owner2 = Owner1; <span class="co">// Conceptual Leak of initial resource of Owner2!</span>
Owner1 = <span class="kw">nullptr</span>;</code></pre></div>
<p>The semantic of a gsl::owner<T*> is mostly like a std::unique_ptr<T>, therefore assignment of two gsl::owner<T*> is considered a move, which requires that the resource Owner2 must have been released before the assignment. This kind of condition could be caught in later improvements of this check with flowsensitive analysis. Currently, the Clang Static Analyzer catches this bug for dynamic memory, but not for general types of resources.</p>
<p>(Clang-Tidy original name: cppcoreguidelines-owning-memory)</p>


#### Prefer Member Initializer {#CT_CPP_PMI}
<p>Finds member initializations in the constructor body which can be converted into member initializers of the constructor instead. This not only improves the readability of the code but also positively affects its performance. Class-member assignments inside a control statement or following the first control statement are ignored.</p>
<p>This check implements <a href="https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#c49-prefer-initialization-to-assignment-in-constructors">C.49</a> from the CppCoreGuidelines.</p>
<p>If the language version is C++ 11 or above, the constructor is the default constructor of the class, the field is not a bitfield (only in case of earlier language version than C++ 20), furthermore the assigned value is a literal, negated literal or enum constant then the preferred place of the initialization is at the class member declaration.</p>
<p>This latter rule is <a href="https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#c48-prefer-in-class-initializers-to-member-initializers-in-constructors-for-constant-initializers">C.48</a> from CppCoreGuidelines.</p>
<p>Please note, that this check does not enforce this latter rule for initializations already implemented as member initializers. For that purpose see check <a href="modernize-use-default-member-init.html">modernize-use-default-member-init</a>.</p>
<h5 id="example-1">Example 1</h5>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> C {
  <span class="dt">int</span> n;
  <span class="dt">int</span> m;
<span class="kw">public</span>:
  C() {
    n = <span class="dv">1</span>; <span class="co">// Literal in default constructor</span>
    <span class="kw">if</span> (dice())
      <span class="kw">return</span>;
    m = <span class="dv">1</span>;
  }
};</code></pre></div>
<p>Here n can be initialized using a default member initializer, unlike m, as m’s initialization follows a control statement (if):</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> C {
  <span class="dt">int</span> n{<span class="dv">1</span>};
  <span class="dt">int</span> m;
<span class="kw">public</span>:
  C() {
    <span class="kw">if</span> (dice())
      <span class="kw">return</span>;
    m = <span class="dv">1</span>;
  }</code></pre></div>
<h5 id="example-2">Example 2</h5>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> C {
  <span class="dt">int</span> n;
  <span class="dt">int</span> m;
<span class="kw">public</span>:
  C(<span class="dt">int</span> nn, <span class="dt">int</span> mm) {
    n = nn; <span class="co">// Neither default constructor nor literal</span>
    <span class="kw">if</span> (dice())
      <span class="kw">return</span>;
    m = mm;
  }
};</code></pre></div>
<p>Here n can be initialized in the constructor initialization list, unlike m, as m’s initialization follows a control statement (if):</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">C(<span class="dt">int</span> nn, <span class="dt">int</span> mm) : n(nn) {
  <span class="kw">if</span> (dice())
    <span class="kw">return</span>;
  m = mm;
}</code></pre></div>
<p>UseAssignment</p>
<p>If this option is set to true (default is false), the check will initialize members with an assignment. In this case the fix of the first example looks like this:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> C {
  <span class="dt">int</span> n = <span class="dv">1</span>;
  <span class="dt">int</span> m;
<span class="kw">public</span>:
  C() {
    <span class="kw">if</span> (dice())
      <span class="kw">return</span>;
    m = <span class="dv">1</span>;
  }
};</code></pre></div>
<p>(Clang-Tidy original name: cppcoreguidelines-prefer-member-initializer)</p>


#### Pro Bounds Array To Pointer Decay {#CT_CPP_PBATPD}
<p>This check flags all array to pointer decays.</p>
<p>Pointers should not be used as arrays. span<T> is a bounds-checked, safe alternative to using pointers to access arrays.</p>
<p>This rule is part of the “Bounds safety” profile of the C++ Core Guidelines, see <a href="https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#Pro-bounds-decay" class="uri">https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#Pro-bounds-decay</a>.</p>
<p>(Clang-Tidy original name: cppcoreguidelines-pro-bounds-array-to-pointer-decay)</p>


#### Pro Bounds Constant Array Index {#CT_CPP_PBCAI}
<p>This check flags all array subscript expressions on static arrays and std::arrays that either do not have a constant integer expression index or are out of bounds (for std::array). For out-of-bounds checking of static arrays, see the -Warray-bounds Clang diagnostic.</p>
<p>This rule is part of the “Bounds safety” profile of the C++ Core Guidelines, see <a href="https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#Pro-bounds-arrayindex" class="uri">https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#Pro-bounds-arrayindex</a>.</p>
<h5 id="options-62">Options</h5>
<p>GslHeader</p>
<p>The check can generate fixes after this option has been set to the name of the include file that contains gsl::at(), e.g. “gsl/gsl.h”.</p>
<p>IncludeStyle</p>
<p>A string specifying which include-style is used, llvm or google. Default is llvm.</p>
<p>(Clang-Tidy original name: cppcoreguidelines-pro-bounds-constant-array-index)</p>


#### Pro Bounds Pointer Arithmetic {#CT_CPP_PBPA}
<p>This check flags all usage of pointer arithmetic, because it could lead to an invalid pointer. Subtraction of two pointers is not flagged by this check.</p>
<p>Pointers should only refer to single objects, and pointer arithmetic is fragile and easy to get wrong. span<T> is a bounds-checked, safe type for accessing arrays of data.</p>
<p>This rule is part of the “Bounds safety” profile of the C++ Core Guidelines, see <a href="https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#Pro-bounds-arithmetic" class="uri">https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#Pro-bounds-arithmetic</a>.</p>
<p>(Clang-Tidy original name: cppcoreguidelines-pro-bounds-pointer-arithmetic)</p>


#### Pro Type Const Cast {#CT_CPP_PTCC}
<p>This check flags all uses of const_cast in C++ code.</p>
<p>Modifying a variable that was declared const is undefined behavior, even with const_cast.</p>
<p>This rule is part of the “Type safety” profile of the C++ Core Guidelines, see <a href="https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#Pro-type-constcast" class="uri">https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#Pro-type-constcast</a>.</p>
<p>(Clang-Tidy original name: cppcoreguidelines-pro-type-const-cast)</p>


#### Pro Type Cstyle Cast {#CT_CPP_PTCC2}
<p>This check flags all use of C-style casts that perform a static_cast downcast, const_cast, or reinterpret_cast.</p>
<p>Use of these casts can violate type safety and cause the program to access a variable that is actually of type X to be accessed as if it were of an unrelated type Z. Note that a C-style (T)expression cast means to perform the first of the following that is possible: a const_cast, a static_cast, a static_cast followed by a const_cast, a reinterpret_cast, or a reinterpret_cast followed by a const_cast. This rule bans (T)expression only when used to perform an unsafe cast.</p>
<p>This rule is part of the “Type safety” profile of the C++ Core Guidelines, see <a href="https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#Pro-type-cstylecast" class="uri">https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#Pro-type-cstylecast</a>.</p>
<p>(Clang-Tidy original name: cppcoreguidelines-pro-type-cstyle-cast)</p>


#### Pro Type Member Init {#CT_CPP_PTMI}
<p>The check flags user-defined constructor definitions that do not initialize all fields that would be left in an undefined state by default construction, e.g. builtins, pointers and record types without user-provided default constructors containing at least one such type. If these fields aren’t initialized, the constructor will leave some of the memory in an undefined state.</p>
<p>For C++11 it suggests fixes to add in-class field initializers. For older versions it inserts the field initializers into the constructor initializer list. It will also initialize any direct base classes that need to be zeroed in the constructor initializer list.</p>
<p>The check takes assignment of fields in the constructor body into account but generates false positives for fields initialized in methods invoked in the constructor body.</p>
<p>The check also flags variables with automatic storage duration that have record types without a user-provided constructor and are not initialized. The suggested fix is to zero initialize the variable via {} for C++11 and beyond or = {} for older language versions.</p>
<h5 id="options-74">Options</h5>
<p>IgnoreArrays</p>
<p>If set to true, the check will not warn about array members that are not zero-initialized during construction. For performance critical code, it may be important to not initialize fixed-size array members. Default is false.</p>
<p>UseAssignment</p>
<p>If set to true, the check will provide fix-its with literal initializers ( int i = 0; ) instead of curly braces ( int i{}; ).</p>
<p>This rule is part of the “Type safety” profile of the C++ Core Guidelines, corresponding to rule Type.6. See <a href="https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#Pro-type-memberinit" class="uri">https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#Pro-type-memberinit</a>.</p>
<p>(Clang-Tidy original name: cppcoreguidelines-pro-type-member-init)</p>


#### Pro Type Reinterpret Cast {#CT_CPP_PTRC}
<p>This check flags all uses of reinterpret_cast in C++ code.</p>
<p>Use of these casts can violate type safety and cause the program to access a variable that is actually of type X to be accessed as if it were of an unrelated type Z.</p>
<p>This rule is part of the “Type safety” profile of the C++ Core Guidelines, see <a href="https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#Pro-type-reinterpretcast" class="uri">https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#Pro-type-reinterpretcast</a>.</p>
<p>(Clang-Tidy original name: cppcoreguidelines-pro-type-reinterpret-cast)</p>


#### Pro Type Static Cast Downcast {#CT_CPP_PTSCD}
<p>This check flags all usages of static_cast, where a base class is casted to a derived class. In those cases, a fix-it is provided to convert the cast to a dynamic_cast.</p>
<p>Use of these casts can violate type safety and cause the program to access a variable that is actually of type X to be accessed as if it were of an unrelated type Z.</p>
<p>This rule is part of the “Type safety” profile of the C++ Core Guidelines, see <a href="https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#Pro-type-downcast" class="uri">https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#Pro-type-downcast</a>.</p>
<p>(Clang-Tidy original name: cppcoreguidelines-pro-type-static-cast-downcast)</p>


#### Pro Type Union Access {#CT_CPP_PTUA}
<p>This check flags all access to members of unions. Passing unions as a whole is not flagged.</p>
<p>Reading from a union member assumes that member was the last one written, and writing to a union member assumes another member with a nontrivial destructor had its destructor called. This is fragile because it cannot generally be enforced to be safe in the language and so relies on programmer discipline to get it right.</p>
<p>This rule is part of the “Type safety” profile of the C++ Core Guidelines, see <a href="https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#Pro-type-unions" class="uri">https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#Pro-type-unions</a>.</p>
<p>(Clang-Tidy original name: cppcoreguidelines-pro-type-union-access)</p>


#### Pro Type Vararg {#CT_CPP_PTV}
<p>This check flags all calls to c-style vararg functions and all use of va_arg.</p>
<p>To allow for SFINAE use of vararg functions, a call is not flagged if a literal 0 is passed as the only vararg argument.</p>
<p>Passing to varargs assumes the correct type will be read. This is fragile because it cannot generally be enforced to be safe in the language and so relies on programmer discipline to get it right.</p>
<p>This rule is part of the “Type safety” profile of the C++ Core Guidelines, see <a href="https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#Pro-type-varargs" class="uri">https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#Pro-type-varargs</a>.</p>
<p>(Clang-Tidy original name: cppcoreguidelines-pro-type-vararg)</p>


#### Slicing {#CT_CPP_S}
<p>Flags slicing of member variables or vtable. Slicing happens when copying a derived object into a base object: the members of the derived object (both member variables and virtual member functions) will be discarded. This can be misleading especially for member function slicing, for example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">struct</span> B { <span class="dt">int</span> a; <span class="kw">virtual</span> <span class="dt">int</span> f(); };
<span class="kw">struct</span> D : B { <span class="dt">int</span> b; <span class="dt">int</span> f() <span class="kw">override</span>; };

<span class="dt">void</span> use(B b) {  <span class="co">// Missing reference, intended?</span>
  b.f();  <span class="co">// Calls B::f.</span>
}

D d;
use(d);  <span class="co">// Slice.</span></code></pre></div>
<p>See the relevant C++ Core Guidelines sections for details: <a href="https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#es63-dont-slice" class="uri">https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#es63-dont-slice</a> <a href="https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#c145-access-polymorphic-objects-through-pointers-and-references" class="uri">https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#c145-access-polymorphic-objects-through-pointers-and-references</a></p>
<p>(Clang-Tidy original name: cppcoreguidelines-slicing)</p>


#### Special Member Functions {#CT_CPP_SMF}
<p>The check finds classes where some but not all of the special member functions are defined.</p>
<p>By default the compiler defines a copy constructor, copy assignment operator, move constructor, move assignment operator and destructor. The default can be suppressed by explicit user-definitions. The relationship between which functions will be suppressed by definitions of other functions is complicated and it is advised that all five are defaulted or explicitly defined.</p>
<p>Note that defining a function with = delete is considered to be a definition.</p>
<p>This rule is part of the “Constructors, assignments, and destructors” profile of the C++ Core Guidelines, corresponding to rule C.21. See</p>
<p><a href="https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#c21-if-you-define-or-delete-any-default-operation-define-or-delete-them-all" class="uri">https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#c21-if-you-define-or-delete-any-default-operation-define-or-delete-them-all</a>.</p>
<h5 id="options-54">Options</h5>
<p>AllowSoleDefaultDtor</p>
<p>When set to true (default is false), this check doesn’t flag classes with a sole, explicitly defaulted destructor. An example for such a class is:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">struct</span> A {
  <span class="kw">virtual</span> ~A() = <span class="kw">default</span>;
};</code></pre></div>
<p>AllowMissingMoveFunctions</p>
<p>When set to true (default is false), this check doesn’t flag classes which define no move operations at all. It still flags classes which define only one of either move constructor or move assignment operator. With this option enabled, the following class won’t be flagged:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">struct</span> A {
  A(<span class="dt">const</span> A&amp;);
  A&amp; <span class="kw">operator</span>=(<span class="dt">const</span> A&amp;);
  ~A();
};</code></pre></div>
<p>AllowMissingMoveFunctionsWhenCopyIsDeleted</p>
<p>When set to true (default is false), this check doesn’t flag classes which define deleted copy operations but don’t define move operations. This flags is related to Google C++ Style Guide <a href="https://google.github.io/styleguide/cppguide.html\#Copyable_Movable_Types" class="uri">https://google.github.io/styleguide/cppguide.html\#Copyable_Movable_Types</a>. With this option enabled, the following class won’t be flagged:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">struct</span> A {
  A(<span class="dt">const</span> A&amp;) = <span class="kw">delete</span>;
  A&amp; <span class="kw">operator</span>=(<span class="dt">const</span> A&amp;) = <span class="kw">delete</span>;
  ~A();
};</code></pre></div>
<p>(Clang-Tidy original name: cppcoreguidelines-special-member-functions)</p>


### Cert

#### Con36 C {#CT_CRT_CON36_C}
<p>The cert-con36-c check is an alias, please see <a href="bugprone-spuriously-wake-up-functions.html">bugprone-spuriously-wake-up-functions</a> for more information.</p>
<p>(Clang-Tidy original name: cert-con36-c)</p>


#### Con54 Cpp {#CT_CRT_CON54_CPP}
<p>The cert-con54-cpp check is an alias, please see <a href="bugprone-spuriously-wake-up-functions.html">bugprone-spuriously-wake-up-functions</a> for more information.</p>
<p>(Clang-Tidy original name: cert-con54-cpp)</p>


#### Dcl03 C {#CT_CRT_DCL03_C}
<p>The cert-dcl03-c check is an alias, please see <a href="misc-static-assert.html">misc-static-assert</a> for more information.</p>
<p>(Clang-Tidy original name: cert-dcl03-c)</p>


#### Dcl16 C {#CT_CRT_DCL16_C}
<p>The cert-dcl16-c check is an alias, please see <a href="readability-uppercase-literal-suffix.html">readability-uppercase-literal-suffix</a> for more information.</p>
<p>(Clang-Tidy original name: cert-dcl16-c)</p>


#### Dcl21 Cpp {#CT_CRT_DCL21_CPP}
<p>This check flags postfix operator++ and operator-- declarations if the return type is not a const object. This also warns if the return type is a reference type.</p>
<p>The object returned by a postfix increment or decrement operator is supposed to be a snapshot of the object’s value prior to modification. With such an implementation, any modifications made to the resulting object from calling operator++(int) would be modifying a temporary object. Thus, such an implementation of a postfix increment or decrement operator should instead return a const object, prohibiting accidental mutation of a temporary object. Similarly, it is unexpected for the postfix operator to return a reference to its previous state, and any subsequent modifications would be operating on a stale object.</p>
<p>This check corresponds to the CERT C++ Coding Standard recommendation DCL21-CPP. Overloaded postfix increment and decrement operators should return a const object. However, all of the CERT recommendations have been removed from public view, and so their justification for the behavior of this check requires an account on their wiki to view.</p>
<p>(Clang-Tidy original name: cert-dcl21-cpp)</p>


#### Dcl37 C {#CT_CRT_DCL37_C}
<p>The cert-dcl37-c check is an alias, please see <a href="bugprone-reserved-identifier.html">bugprone-reserved-identifier</a> for more information.</p>
<p>(Clang-Tidy original name: cert-dcl37-c)</p>


#### Dcl50 Cpp {#CT_CRT_DCL50_CPP}
<p>This check flags all function definitions (but not declarations) of C-style variadic functions.</p>
<p>This check corresponds to the CERT C++ Coding Standard rule <a href="https://www.securecoding.cert.org/confluence/display/cplusplus/DCL50-CPP.+Do+not+define+a+C-style+variadic+function">DCL50-CPP. Do not define a C-style variadic function</a>.</p>
<p>(Clang-Tidy original name: cert-dcl50-cpp)</p>


#### Dcl51 Cpp {#CT_CRT_DCL51_CPP}
<p>The cert-dcl51-cpp check is an alias, please see <a href="bugprone-reserved-identifier.html">bugprone-reserved-identifier</a> for more information.</p>
<p>(Clang-Tidy original name: cert-dcl51-cpp)</p>


#### Dcl54 Cpp {#CT_CRT_DCL54_CPP}
<p>The cert-dcl54-cpp check is an alias, please see <a href="misc-new-delete-overloads.html">misc-new-delete-overloads</a> for more information.</p>
<p>(Clang-Tidy original name: cert-dcl54-cpp)</p>


#### Dcl58 Cpp {#CT_CRT_DCL58_CPP}
<p>Modification of the std or posix namespace can result in undefined behavior. This check warns for such modifications.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">namespace</span> std {
  <span class="dt">int</span> x; <span class="co">// May cause undefined behavior.</span>
}</code></pre></div>
<p>This check corresponds to the CERT C++ Coding Standard rule <a href="https://www.securecoding.cert.org/confluence/display/cplusplus/DCL58-CPP.+Do+not+modify+the+standard+namespaces">DCL58-CPP. Do not modify the standard namespaces</a>.</p>
<p>(Clang-Tidy original name: cert-dcl58-cpp)</p>


#### Dcl59 Cpp {#CT_CRT_DCL59_CPP}
<p>The cert-dcl59-cpp check is an alias, please see <a href="google-build-namespaces.html">google-build-namespaces</a> for more information.</p>
<p>(Clang-Tidy original name: cert-dcl59-cpp)</p>


#### Env33 C {#CT_CRT_ENV33_C}
<p>This check flags calls to system(), popen(), and _popen(), which execute a command processor. It does not flag calls to system() with a null pointer argument, as such a call checks for the presence of a command processor but does not actually attempt to execute a command.</p>
<p>This check corresponds to the CERT C Coding Standard rule <a href="https://www.securecoding.cert.org/confluence/pages/viewpage.action?pageId=2130132">ENV33-C. Do not call system()</a>.</p>
<p>(Clang-Tidy original name: cert-env33-c)</p>


#### Err09 Cpp {#CT_CRT_ERR09_CPP}
<p>The cert-err09-cpp check is an alias, please see <a href="misc-throw-by-value-catch-by-reference.html">misc-throw-by-value-catch-by-reference</a> for more information.</p>
<p>This check corresponds to the CERT C++ Coding Standard recommendation ERR09-CPP. Throw anonymous temporaries. However, all of the CERT recommendations have been removed from public view, and so their justification for the behavior of this check requires an account on their wiki to view.</p>
<p>(Clang-Tidy original name: cert-err09-cpp)</p>


#### Err34 C {#CT_CRT_ERR34_C}
<p>This check flags calls to string-to-number conversion functions that do not verify the validity of the conversion, such as atoi() or scanf(). It does not flag calls to strtol(), or other, related conversion functions that do perform better error checking.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="ot">#include &lt;stdlib.h&gt;</span>

<span class="dt">void</span> func(<span class="dt">const</span> <span class="dt">char</span> *buff) {
  <span class="dt">int</span> si;

  <span class="kw">if</span> (buff) {
    si = atoi(buff); <span class="co">/* &#39;atoi&#39; used to convert a string to an integer, but function will</span>
<span class="co">                         not report conversion errors; consider using &#39;strtol&#39; instead. */</span>
  } <span class="kw">else</span> {
    <span class="co">/* Handle error */</span>
  }
}</code></pre></div>
<p>This check corresponds to the CERT C Coding Standard rule <a href="https://www.securecoding.cert.org/confluence/display/c/ERR34-C.+Detect+errors+when+converting+a+string+to+a+number">ERR34-C. Detect errors when converting a string to a number</a>.</p>
<p>(Clang-Tidy original name: cert-err34-c)</p>


#### Err52 Cpp {#CT_CRT_ERR52_CPP}
<p>This check flags all call expressions involving setjmp() and longjmp().</p>
<p>This check corresponds to the CERT C++ Coding Standard rule <a href="https://www.securecoding.cert.org/confluence/pages/viewpage.action?pageId=1834">ERR52-CPP. Do not use setjmp() or longjmp()</a>.</p>
<p>(Clang-Tidy original name: cert-err52-cpp)</p>


#### Err58 Cpp {#CT_CRT_ERR58_CPP}
<p>This check flags all static or thread_local variable declarations where the initializer for the object may throw an exception.</p>
<p>This check corresponds to the CERT C++ Coding Standard rule <a href="https://www.securecoding.cert.org/confluence/display/cplusplus/ERR58-CPP.+Handle+all+exceptions+thrown+before+main%28%29+begins+executing">ERR58-CPP. Handle all exceptions thrown before main() begins executing</a>.</p>
<p>(Clang-Tidy original name: cert-err58-cpp)</p>


#### Err60 Cpp {#CT_CRT_ERR60_CPP}
<p>This check flags all throw expressions where the exception object is not nothrow copy constructible.</p>
<p>This check corresponds to the CERT C++ Coding Standard rule <a href="https://www.securecoding.cert.org/confluence/display/cplusplus/ERR60-CPP.+Exception+objects+must+be+nothrow+copy+constructible">ERR60-CPP. Exception objects must be nothrow copy constructible</a>.</p>
<p>(Clang-Tidy original name: cert-err60-cpp)</p>


#### Err61 Cpp {#CT_CRT_ERR61_CPP}
<p>The cert-err61-cpp check is an alias, please see <a href="misc-throw-by-value-catch-by-reference.html">misc-throw-by-value-catch-by-reference</a> for more information.</p>
<p>(Clang-Tidy original name: cert-err61-cpp)</p>


#### Fio38 C {#CT_CRT_FIO38_C}
<p>The cert-fio38-c check is an alias, please see <a href="misc-non-copyable-objects.html">misc-non-copyable-objects</a> for more information.</p>
<p>(Clang-Tidy original name: cert-fio38-c)</p>


#### Flp30 C {#CT_CRT_FLP30_C}
<p>This check flags for loops where the induction expression has a floating-point type.</p>
<p>This check corresponds to the CERT C Coding Standard rule <a href="https://www.securecoding.cert.org/confluence/display/c/FLP30-C.+Do+not+use+floating-point+variables+as+loop+counters">FLP30-C. Do not use floating-point variables as loop counters</a>.</p>
<p>(Clang-Tidy original name: cert-flp30-c)</p>


#### Mem57 Cpp {#CT_CRT_MEM57_CPP}
<p>This check flags uses of default operator new where the type has extended alignment (an alignment greater than the fundamental alignment). (The default operator new is guaranteed to provide the correct alignment if the requested alignment is less or equal to the fundamental alignment). Only cases are detected (by design) where the operator new is not user-defined and is not a placement new (the reason is that in these cases we assume that the user provided the correct memory allocation).</p>
<p>This check corresponds to the CERT C++ Coding Standard rule <a href="https://wiki.sei.cmu.edu/confluence/display/cplusplus/MEM57-CPP.+Avoid+using+default+operator+new+for+over-aligned+types">MEM57-CPP. Avoid using default operator new for over-aligned types</a>.</p>
<p>(Clang-Tidy original name: cert-mem57-cpp)</p>


#### Msc30 C {#CT_CRT_MSC30_C}
<p>The cert-msc30-c check is an alias, please see <a href="cert-msc50-cpp.html">cert-msc50-cpp</a> for more information.</p>
<p>(Clang-Tidy original name: cert-msc30-c)</p>


#### Msc32 C {#CT_CRT_MSC32_C}
<p>The cert-msc32-c check is an alias, please see <a href="cert-msc51-cpp.html">cert-msc51-cpp</a> for more information.</p>
<p>(Clang-Tidy original name: cert-msc32-c)</p>


#### Msc50 Cpp {#CT_CRT_MSC50_CPP}
<p>Pseudorandom number generators use mathematical algorithms to produce a sequence of numbers with good statistical properties, but the numbers produced are not genuinely random. The std::rand() function takes a seed (number), runs a mathematical operation on it and returns the result. By manipulating the seed the result can be predictable. This check warns for the usage of std::rand().</p>
<p>(Clang-Tidy original name: cert-msc50-cpp)</p>


#### Msc51 Cpp {#CT_CRT_MSC51_CPP}
<p>This check flags all pseudo-random number engines, engine adaptor instantiations and srand() when initialized or seeded with default argument, constant expression or any user-configurable type. Pseudo-random number engines seeded with a predictable value may cause vulnerabilities e.g. in security protocols. This is a CERT security rule, see <a href="https://wiki.sei.cmu.edu/confluence/display/cplusplus/MSC51-CPP.+Ensure+your+random+number+generator+is+properly+seeded">MSC51-CPP. Ensure your random number generator is properly seeded</a> and <a href="https://wiki.sei.cmu.edu/confluence/display/c/MSC32-C.+Properly+seed+pseudorandom+number+generators">MSC32-C. Properly seed pseudorandom number generators</a>.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> foo() {
  std::mt19937 engine1; <span class="co">// Diagnose, always generate the same sequence</span>
  std::mt19937 engine2(<span class="dv">1</span>); <span class="co">// Diagnose</span>
  engine1.seed(); <span class="co">// Diagnose</span>
  engine2.seed(<span class="dv">1</span>); <span class="co">// Diagnose</span>

  std::time_t t;
  engine1.seed(std::time(&amp;t)); <span class="co">// Diagnose, system time might be controlled by user</span>

  <span class="dt">int</span> x = atoi(argv[<span class="dv">1</span>]);
  std::mt19937 engine3(x);  <span class="co">// Will not warn</span>
}</code></pre></div>
<h5 id="options-71">Options</h5>
<p>DisallowedSeedTypes</p>
<p>A comma-separated list of the type names which are disallowed. Default values are time_t, std::time_t.</p>
<p>(Clang-Tidy original name: cert-msc51-cpp)</p>


#### Oop11 Cpp {#CT_CRT_OOP11_CPP}
<p>The cert-oop11-cpp check is an alias, please see <a href="performance-move-constructor-init.html">performance-move-constructor-init</a> for more information.</p>
<p>This check corresponds to the CERT C++ Coding Standard recommendation OOP11-CPP. Do not copy-initialize members or base classes from a move constructor. However, all of the CERT recommendations have been removed from public view, and so their justification for the behavior of this check requires an account on their wiki to view.</p>
<p>(Clang-Tidy original name: cert-oop11-cpp)</p>


#### Oop54 Cpp {#CT_CRT_OOP54_CPP}
<p>The cert-oop54-cpp check is an alias, please see <a href="bugprone-unhandled-self-assignment.html">bugprone-unhandled-self-assignment</a> for more information.</p>
<p>(Clang-Tidy original name: cert-oop54-cpp)</p>


#### Oop57 Cpp {#CT_CRT_OOP57_CPP}
<p>Flags use of the C standard library functions memset, memcpy and memcmp and similar derivatives on non-trivial types.</p>
<h5 id="options-58">Options</h5>
<p>MemSetNames</p>
<p>Specify extra functions to flag that act similarily to memset. Specify names in a semicolon delimited list. Default is an empty string. The check will detect the following functions: memset, std::memset.</p>
<p>MemCpyNames</p>
<p>Specify extra functions to flag that act similarily to memcpy. Specify names in a semicolon delimited list. Default is an empty string. The check will detect the following functions: std::memcpy, memcpy, std::memmove, memmove, std::strcpy, strcpy, memccpy, stpncpy, strncpy.</p>
<p>MemCmpNames</p>
<p>Specify extra functions to flag that act similarily to memcmp. Specify names in a semicolon delimited list. Default is an empty string. The check will detect the following functions: std::memcmp, memcmp, std::strcmp, strcmp, strncmp.</p>
<p>This check corresponds to the CERT C++ Coding Standard rule <a href="https://wiki.sei.cmu.edu/confluence/display/cplusplus/OOP57-CPP.+Prefer+special+member+functions+and+overloaded+operators+to+C+Standard+Library+functions">OOP57-CPP. Prefer special member functions and overloaded operators to C Standard Library functions</a>.</p>
<p>(Clang-Tidy original name: cert-oop57-cpp)</p>


#### Oop58 Cpp {#CT_CRT_OOP58_CPP}
<p>Finds assignments to the copied object and its direct or indirect members in copy constructors and copy assignment operators.</p>
<p>This check corresponds to the CERT C Coding Standard rule <a href="https://wiki.sei.cmu.edu/confluence/display/cplusplus/OOP58-CPP.+Copy+operations+must+not+mutate+the+source+object">OOP58-CPP. Copy operations must not mutate the source object</a>.</p>
<p>(Clang-Tidy original name: cert-oop58-cpp)</p>


#### Pos44 C {#CT_CRT_POS44_C}
<p>The cert-pos44-c check is an alias, please see <a href="bugprone-bad-signal-to-kill-thread.html">bugprone-bad-signal-to-kill-thread</a> for more information.</p>
<p>(Clang-Tidy original name: cert-pos44-c)</p>


#### Sig30 C {#CT_CRT_SIG30_C}
<p>The cert-sig30-c check is an alias, please see <a href="bugprone-signal-handler.html">bugprone-signal-handler</a> for more information.</p>
<p>(Clang-Tidy original name: cert-sig30-c)</p>


#### Str34 C {#CT_CRT_STR34_C}
<p>The cert-str34-c check is an alias, please see <a href="bugprone-signed-char-misuse.html">bugprone-signed-char-misuse</a> for more information.</p>
<p>(Clang-Tidy original name: cert-str34-c)</p>


### Concurrency

#### Mt Unsafe {#CT_CON_MU}
<p>Checks for some thread-unsafe functions against a black list of known-to-be-unsafe functions. Usually they access static variables without synchronization (e.g. gmtime(3)) or utilize signals in a racy way. The set of functions to check is specified with the FunctionSet option.</p>
<p>Note that using some thread-unsafe functions may be still valid in concurrent programming if only a single thread is used (e.g. setenv(3)), however, some functions may track a state in global variables which would be clobbered by subsequent (non-parallel, but concurrent) calls to a related function. E.g. the following code suffers from unprotected accesses to a global state:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// getnetent(3) maintains global state with DB connection, etc.</span>
<span class="co">// If a concurrent green thread calls getnetent(3), the global state is corrupted.</span>
netent = getnetent();
yield();
netent = getnetent();</code></pre></div>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">tm = gmtime(timep); <span class="co">// uses a global buffer</span>

sleep(<span class="dv">1</span>); <span class="co">// implementation may use SIGALRM</span></code></pre></div>
<p>FunctionSet</p>
<p>Specifies which functions in libc should be considered thread-safe, possible values are posix, glibc, or any.</p>
<p>posix means POSIX defined thread-unsafe functions. POSIX.1-2001 in “2.9.1 Thread-Safety” defines that all functions specified in the standard are thread-safe except a predefined list of thread-unsafe functions.</p>
<p>Glibc defines some of them as thread-safe (e.g. dirname(3)), but adds non-POSIX thread-unsafe ones (e.g. getopt_long(3)). Glibc’s list is compiled from GNU web documentation with a search for MT-Safe tag: <a href="https://www.gnu.org/software/libc/manual/html_node/POSIX-Safety-Concepts.html" class="uri">https://www.gnu.org/software/libc/manual/html_node/POSIX-Safety-Concepts.html</a></p>
<p>If you want to identify thread-unsafe API for at least one libc or unsure which libc will be used, use any (default).</p>
<p>(Clang-Tidy original name: concurrency-mt-unsafe)</p>


### Darwin

#### Avoid Spinlock {#CT_DRW_AS}
<p>Finds usages of OSSpinlock, which is deprecated due to potential livelock problems.</p>
<p>This check will detect following function invocations:</p>
<ul>
<li>OSSpinlockLock</li>
<li>OSSpinlockTry</li>
<li>OSSpinlockUnlock</li>
</ul>
<p>The corresponding information about the problem of OSSpinlock: <a href="https://blog.postmates.com/why-spinlocks-are-bad-on-ios-b69fc5221058" class="uri">https://blog.postmates.com/why-spinlocks-are-bad-on-ios-b69fc5221058</a></p>
<p>(Clang-Tidy original name: darwin-avoid-spinlock)</p>


#### Dispatch Once Nonstatic {#CT_DRW_DON}
<p>Finds declarations of dispatch_once_t variables without static or global storage. The behavior of using dispatch_once_t predicates with automatic or dynamic storage is undefined by libdispatch, and should be avoided.</p>
<p>It is a common pattern to have functions initialize internal static or global data once when the function runs, but programmers have been known to miss the static on the dispatch_once_t predicate, leading to an uninitialized flag value at the mercy of the stack.</p>
<p>Programmers have also been known to make dispatch_once_t variables be members of structs or classes, with the intent to lazily perform some expensive struct or class member initialization only once; however, this violates the libdispatch requirements.</p>
<p>See the discussion section of <a href="https://developer.apple.com/documentation/dispatch/1447169-dispatch_once">Apple’s dispatch_once documentation</a> for more information.</p>
<p>(Clang-Tidy original name: darwin-dispatch-once-nonstatic)</p>


### Fuchsia

#### Default Arguments Calls {#CT_FCS_DAC}
<p>Warns if a function or method is called with default arguments.</p>
<p>For example, given the declaration:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">int</span> foo(<span class="dt">int</span> value = <span class="dv">5</span>) { <span class="kw">return</span> value; }</code></pre></div>
<p>A function call expression that uses a default argument will be diagnosed. Calling it without defaults will not cause a warning:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">foo();  <span class="co">// warning</span>
foo(<span class="dv">0</span>); <span class="co">// no warning</span></code></pre></div>
<p>See the features disallowed in Fuchsia at <a href="https://fuchsia.googlesource.com/zircon/+/master/docs/cxx.md" class="uri">https://fuchsia.googlesource.com/zircon/+/master/docs/cxx.md</a></p>
<p>(Clang-Tidy original name: fuchsia-default-arguments-calls)</p>


#### Default Arguments Declarations {#CT_FCS_DAD}
<p>Warns if a function or method is declared with default parameters.</p>
<p>For example, the declaration:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">int</span> foo(<span class="dt">int</span> value = <span class="dv">5</span>) { <span class="kw">return</span> value; }</code></pre></div>
<p>will cause a warning.</p>
<p>See the features disallowed in Fuchsia at <a href="https://fuchsia.googlesource.com/zircon/+/master/docs/cxx.md" class="uri">https://fuchsia.googlesource.com/zircon/+/master/docs/cxx.md</a></p>
<p>(Clang-Tidy original name: fuchsia-default-arguments-declarations)</p>


#### Header Anon Namespaces {#CT_FCS_HAN}
<p>The fuchsia-header-anon-namespaces check is an alias, please see <a href="google-build-namespaces.html">google-build-namespace</a> for more information.</p>
<p>(Clang-Tidy original name: fuchsia-header-anon-namespaces)</p>


#### Multiple Inheritance {#CT_FCS_MI}
<p>Warns if a class inherits from multiple classes that are not pure virtual.</p>
<p>For example, declaring a class that inherits from multiple concrete classes is disallowed:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> Base_A {
<span class="kw">public</span>:
  <span class="kw">virtual</span> <span class="dt">int</span> foo() { <span class="kw">return</span> <span class="dv">0</span>; }
};

<span class="kw">class</span> Base_B {
<span class="kw">public</span>:
  <span class="kw">virtual</span> <span class="dt">int</span> bar() { <span class="kw">return</span> <span class="dv">0</span>; }
};

<span class="co">// Warning</span>
<span class="kw">class</span> Bad_Child1 : <span class="kw">public</span> Base_A, Base_B {};</code></pre></div>
<p>A class that inherits from a pure virtual is allowed:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> Interface_A {
<span class="kw">public</span>:
  <span class="kw">virtual</span> <span class="dt">int</span> foo() = <span class="dv">0</span>;
};

<span class="kw">class</span> Interface_B {
<span class="kw">public</span>:
  <span class="kw">virtual</span> <span class="dt">int</span> bar() = <span class="dv">0</span>;
};

<span class="co">// No warning</span>
<span class="kw">class</span> Good_Child1 : <span class="kw">public</span> Interface_A, Interface_B {
  <span class="kw">virtual</span> <span class="dt">int</span> foo() <span class="kw">override</span> { <span class="kw">return</span> <span class="dv">0</span>; }
  <span class="kw">virtual</span> <span class="dt">int</span> bar() <span class="kw">override</span> { <span class="kw">return</span> <span class="dv">0</span>; }
};</code></pre></div>
<p>See the features disallowed in Fuchsia at <a href="https://fuchsia.googlesource.com/zircon/+/master/docs/cxx.md" class="uri">https://fuchsia.googlesource.com/zircon/+/master/docs/cxx.md</a></p>
<p>(Clang-Tidy original name: fuchsia-multiple-inheritance)</p>


#### Overloaded Operator {#CT_FCS_OO}
<p>Warns if an operator is overloaded, except for the assignment (copy and move) operators.</p>
<p>For example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">int</span> <span class="kw">operator</span>+(<span class="dt">int</span>);     <span class="co">// Warning</span>

B &amp;<span class="kw">operator</span>=(<span class="dt">const</span> B &amp;Other);  <span class="co">// No warning</span>
B &amp;<span class="kw">operator</span>=(B &amp;&amp;Other) <span class="co">// No warning</span></code></pre></div>
<p>See the features disallowed in Fuchsia at <a href="https://fuchsia.googlesource.com/zircon/+/master/docs/cxx.md" class="uri">https://fuchsia.googlesource.com/zircon/+/master/docs/cxx.md</a></p>
<p>(Clang-Tidy original name: fuchsia-overloaded-operator)</p>


#### Statically Constructed Objects {#CT_FCS_SCO}
<p>Warns if global, non-trivial objects with static storage are constructed, unless the object is statically initialized with a constexpr constructor or has no explicit constructor.</p>
<p>For example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> A {};

<span class="kw">class</span> B {
<span class="kw">public</span>:
  B(<span class="dt">int</span> Val) : Val(Val) {}
<span class="kw">private</span>:
  <span class="dt">int</span> Val;
};

<span class="kw">class</span> C {
<span class="kw">public</span>:
  C(<span class="dt">int</span> Val) : Val(Val) {}
  <span class="kw">constexpr</span> C() : Val(<span class="dv">0</span>) {}

<span class="kw">private</span>:
  <span class="dt">int</span> Val;
};

<span class="dt">static</span> A a;         <span class="co">// No warning, as there is no explicit constructor</span>
<span class="dt">static</span> C c(<span class="dv">0</span>);      <span class="co">// No warning, as constructor is constexpr</span>

<span class="dt">static</span> B b(<span class="dv">0</span>);      <span class="co">// Warning, as constructor is not constexpr</span>
<span class="dt">static</span> C c2(<span class="dv">0</span>, <span class="dv">1</span>);  <span class="co">// Warning, as constructor is not constexpr</span>

<span class="dt">static</span> <span class="dt">int</span> i;       <span class="co">// No warning, as it is trivial</span>

<span class="dt">extern</span> <span class="dt">int</span> get_i();
<span class="dt">static</span> C(get_i())   <span class="co">// Warning, as the constructor is dynamically initialized</span></code></pre></div>
<p>See the features disallowed in Fuchsia at <a href="https://fuchsia.googlesource.com/zircon/+/master/docs/cxx.md" class="uri">https://fuchsia.googlesource.com/zircon/+/master/docs/cxx.md</a></p>
<p>(Clang-Tidy original name: fuchsia-statically-constructed-objects)</p>


#### Trailing Return {#CT_FCS_TR}
<p>Functions that have trailing returns are disallowed, except for those using decltype specifiers and lambda with otherwise unutterable return types.</p>
<p>For example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// No warning</span>
<span class="dt">int</span> add_one(<span class="dt">const</span> <span class="dt">int</span> arg) { <span class="kw">return</span> arg; }

<span class="co">// Warning</span>
<span class="kw">auto</span> get_add_one() -&gt; <span class="dt">int</span> (*)(<span class="dt">const</span> <span class="dt">int</span>) {
  <span class="kw">return</span> add_one;
}</code></pre></div>
<p>Exceptions are made for lambdas and decltype specifiers:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// No warning</span>
<span class="kw">auto</span> lambda = [](<span class="dt">double</span> x, <span class="dt">double</span> y) -&gt; <span class="dt">double</span> {<span class="kw">return</span> x + y;};

<span class="co">// No warning</span>
<span class="kw">template</span> &lt;<span class="kw">typename</span> T1, <span class="kw">typename</span> T2&gt;
<span class="kw">auto</span> fn(<span class="dt">const</span> T1 &amp;lhs, <span class="dt">const</span> T2 &amp;rhs) -&gt; <span class="kw">decltype</span>(lhs + rhs) {
  <span class="kw">return</span> lhs + rhs;
}</code></pre></div>
<p>See the features disallowed in Fuchsia at <a href="https://fuchsia.googlesource.com/zircon/+/master/docs/cxx.md" class="uri">https://fuchsia.googlesource.com/zircon/+/master/docs/cxx.md</a></p>
<p>(Clang-Tidy original name: fuchsia-trailing-return)</p>


#### Virtual Inheritance {#CT_FCS_VI}
<p>Warns if classes are defined with virtual inheritance.</p>
<p>For example, classes should not be defined with virtual inheritance:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> B : <span class="kw">public</span> <span class="kw">virtual</span> A {};   <span class="co">// warning</span></code></pre></div>
<p>See the features disallowed in Fuchsia at <a href="https://fuchsia.googlesource.com/zircon/+/master/docs/cxx.md" class="uri">https://fuchsia.googlesource.com/zircon/+/master/docs/cxx.md</a></p>
<p>(Clang-Tidy original name: fuchsia-virtual-inheritance)</p>


### Google

#### Build Explicit Make Pair {#CT_GGL_BEMP}
<p>Check that make_pair’s template arguments are deduced.</p>
<p>G++ 4.6 in C++11 mode fails badly if make_pair’s template arguments are specified explicitly, and such use isn’t intended in any case.</p>
<p>Corresponding cpplint.py check name: build/explicit_make_pair.</p>
<p>(Clang-Tidy original name: google-build-explicit-make-pair)</p>


#### Build Namespaces {#CT_GGL_BN}
<p>cert-dcl59-cpp redirects here as an alias for this check. fuchsia-header-anon-namespaces redirects here as an alias for this check.</p>
<p>Finds anonymous namespaces in headers.</p>
<p><a href="https://google.github.io/styleguide/cppguide.html\#Namespaces" class="uri">https://google.github.io/styleguide/cppguide.html\#Namespaces</a></p>
<p>Corresponding cpplint.py check name: build/namespaces.</p>
<h5 id="options-63">Options</h5>
<p>HeaderFileExtensions</p>
<p>A comma-separated list of filename extensions of header files (the filename extensions should not include “.” prefix). Default is “h,hh,hpp,hxx”. For header files without an extension, use an empty string (if there are no other desired extensions) or leave an empty element in the list. e.g., “h,hh,hpp,hxx,” (note the trailing comma).</p>
<p>(Clang-Tidy original name: google-build-namespaces)</p>


#### Build Using Namespace {#CT_GGL_BUN}
<p>Finds using namespace directives.</p>
<p>The check implements the following rule of the <a href="https://google.github.io/styleguide/cppguide.html#Namespaces">Google C++ Style Guide</a>:</p>
<p>You may not use a using-directive to make all names from a namespace available.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// Forbidden -- This pollutes the namespace.</span>
<span class="kw">using</span> <span class="kw">namespace</span> foo;</code></pre></div>
<p>Corresponding cpplint.py check name: build/namespaces.</p>
<p>(Clang-Tidy original name: google-build-using-namespace)</p>


#### Default Arguments {#CT_GGL_DA}
<p>Checks that default arguments are not given for virtual methods.</p>
<p>See <a href="https://google.github.io/styleguide/cppguide.html\#Default_Arguments" class="uri">https://google.github.io/styleguide/cppguide.html\#Default_Arguments</a></p>
<p>(Clang-Tidy original name: google-default-arguments)</p>


#### Explicit Constructor {#CT_GGL_EC}
<p>Checks that constructors callable with a single argument and conversion operators are marked explicit to avoid the risk of unintentional implicit conversions.</p>
<p>Consider this example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">struct</span> S {
  <span class="dt">int</span> x;
  <span class="kw">operator</span> <span class="dt">bool</span>() <span class="dt">const</span> { <span class="kw">return</span> <span class="kw">true</span>; }
};

<span class="dt">bool</span> f() {
  S a{<span class="dv">1</span>};
  S b{<span class="dv">2</span>};
  <span class="kw">return</span> a == b;
}</code></pre></div>
<p>The function will return true, since the objects are implicitly converted to bool before comparison, which is unlikely to be the intent.</p>
<p>The check will suggest inserting explicit before the constructor or conversion operator declaration. However, copy and move constructors should not be explicit, as well as constructors taking a single initializer_list argument.</p>
<p>This code:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">struct</span> S {
  S(<span class="dt">int</span> a);
  <span class="kw">explicit</span> S(<span class="dt">const</span> S&amp;);
  <span class="kw">operator</span> <span class="dt">bool</span>() <span class="dt">const</span>;
  ...</code></pre></div>
<p>will become</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">struct</span> S {
  <span class="kw">explicit</span> S(<span class="dt">int</span> a);
  S(<span class="dt">const</span> S&amp;);
  <span class="kw">explicit</span> <span class="kw">operator</span> <span class="dt">bool</span>() <span class="dt">const</span>;
  ...</code></pre></div>
<p>See <a href="https://google.github.io/styleguide/cppguide.html\#Explicit_Constructors" class="uri">https://google.github.io/styleguide/cppguide.html\#Explicit_Constructors</a></p>
<p>(Clang-Tidy original name: google-explicit-constructor)</p>


#### Global Names In Headers {#CT_GGL_GNIH}
<p>Flag global namespace pollution in header files. Right now it only triggers on using declarations and directives.</p>
<p>The relevant style guide section is <a href="https://google.github.io/styleguide/cppguide.html\#Namespaces" class="uri">https://google.github.io/styleguide/cppguide.html\#Namespaces</a>.</p>
<h5 id="options-64">Options</h5>
<p>HeaderFileExtensions</p>
<p>A comma-separated list of filename extensions of header files (the filename extensions should not contain “.” prefix). Default is “h”. For header files without an extension, use an empty string (if there are no other desired extensions) or leave an empty element in the list. e.g., “h,hh,hpp,hxx,” (note the trailing comma).</p>
<p>(Clang-Tidy original name: google-global-names-in-headers)</p>


#### Objc Avoid Nsobject New {#CT_GGL_OANN}
<p>Finds calls to +new or overrides of it, which are prohibited by the Google Objective-C style guide.</p>
<p>The Google Objective-C style guide forbids calling +new or overriding it in class implementations, preferring +alloc and -init methods to instantiate objects.</p>
<p>An example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">NSDate *now = [NSDate <span class="kw">new</span>];
Foo *bar = [Foo <span class="kw">new</span>];</code></pre></div>
<p>Instead, code should use +alloc/-init or class factory methods.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">NSDate *now = [NSDate date];
Foo *bar = [[<span class="kw">Foo</span> <span class="kw">alloc</span>] <span class="kw">init</span>];</code></pre></div>
<p>This check corresponds to the Google Objective-C Style Guide rule <a href="https://google.github.io/styleguide/objcguide.html#do-not-use-new">Do Not Use +new</a>.</p>
<p>(Clang-Tidy original name: google-objc-avoid-nsobject-new)</p>


#### Objc Avoid Throwing Exception {#CT_GGL_OATE}
<p>Finds uses of throwing exceptions usages in Objective-C files.</p>
<p>For the same reason as the Google C++ style guide, we prefer not throwing exceptions from Objective-C code.</p>
<p>The corresponding C++ style guide rule: <a href="https://google.github.io/styleguide/cppguide.html\#Exceptions" class="uri">https://google.github.io/styleguide/cppguide.html\#Exceptions</a></p>
<p>Instead, prefer passing in NSError ** and return BOOL to indicate success or failure.</p>
<p>A counterexample:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">- (<span class="dt">void</span>)readFile {
  <span class="kw">if</span> ([self isError]) {
    <span class="er">@</span>throw [NSException exceptionWithName:...];
  }
}</code></pre></div>
<p>Instead, returning an error via NSError ** is preferred:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">- (BOOL)readFileWithError:(NSError **)error {
  <span class="kw">if</span> ([self isError]) {
    *error = [NSError errorWithDomain:...];
    <span class="kw">return</span> NO;
  }
  <span class="kw">return</span> YES;
}</code></pre></div>
<p>The corresponding style guide rule: <a href="https://google.github.io/styleguide/objcguide.html\#avoid-throwing-exceptions" class="uri">https://google.github.io/styleguide/objcguide.html\#avoid-throwing-exceptions</a></p>
<p>(Clang-Tidy original name: google-objc-avoid-throwing-exception)</p>


#### Objc Function Naming {#CT_GGL_OFN}
<p>Finds function declarations in Objective-C files that do not follow the pattern described in the Google Objective-C Style Guide.</p>
<p>The corresponding style guide rule can be found here: <a href="https://google.github.io/styleguide/objcguide.html\#function-names" class="uri">https://google.github.io/styleguide/objcguide.html\#function-names</a></p>
<p>All function names should be in Pascal case. Functions whose storage class is not static should have an appropriate prefix.</p>
<p>The following code sample does not follow this pattern:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">static</span> <span class="dt">bool</span> is_positive(<span class="dt">int</span> i) { <span class="kw">return</span> i &gt; <span class="dv">0</span>; }
<span class="dt">bool</span> IsNegative(<span class="dt">int</span> i) { <span class="kw">return</span> i &lt; <span class="dv">0</span>; }</code></pre></div>
<p>The sample above might be corrected to the following code:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">static</span> <span class="dt">bool</span> IsPositive(<span class="dt">int</span> i) { <span class="kw">return</span> i &gt; <span class="dv">0</span>; }
<span class="dt">bool</span> *ABCIsNegative(<span class="dt">int</span> i) { <span class="kw">return</span> i &lt; <span class="dv">0</span>; }</code></pre></div>
<p>(Clang-Tidy original name: google-objc-function-naming)</p>


#### Objc Global Variable Declaration {#CT_GGL_OGVD}
<p>Finds global variable declarations in Objective-C files that do not follow the pattern of variable names in Google’s Objective-C Style Guide.</p>
<p>The corresponding style guide rule: <a href="https://google.github.io/styleguide/objcguide.html\#variable-names" class="uri">https://google.github.io/styleguide/objcguide.html\#variable-names</a></p>
<p>All the global variables should follow the pattern of g[A-Z].* (variables) or k[A-Z].* (constants). The check will suggest a variable name that follows the pattern if it can be inferred from the original name.</p>
<p>For code:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">static</span> NSString* myString = <span class="er">@</span><span class="st">&quot;hello&quot;</span>;</code></pre></div>
<p>The fix will be:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">static</span> NSString* gMyString = <span class="er">@</span><span class="st">&quot;hello&quot;</span>;</code></pre></div>
<p>Another example of constant:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">static</span> NSString* <span class="dt">const</span> myConstString = <span class="er">@</span><span class="st">&quot;hello&quot;</span>;</code></pre></div>
<p>The fix will be:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">static</span> NSString* <span class="dt">const</span> kMyConstString = <span class="er">@</span><span class="st">&quot;hello&quot;</span>;</code></pre></div>
<p>However for code that prefixed with non-alphabetical characters like:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">static</span> NSString* __anotherString = <span class="er">@</span><span class="st">&quot;world&quot;</span>;</code></pre></div>
<p>The check will give a warning message but will not be able to suggest a fix. The user needs to fix it on their own.</p>
<p>(Clang-Tidy original name: google-objc-global-variable-declaration)</p>


#### Readability Avoid Underscore In Googletest Name {#CT_GGL_RAUIGN}
<p>Checks whether there are underscores in googletest test and test case names in test macros:</p>
<ul>
<li>TEST</li>
<li>TEST_F</li>
<li>TEST_P</li>
<li>TYPED_TEST</li>
<li>TYPED_TEST_P</li>
</ul>
<p>The FRIEND_TEST macro is not included.</p>
<p>For example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">TEST(TestCaseName, Illegal_TestName) {}
TEST(Illegal_TestCaseName, TestName) {}</code></pre></div>
<p>would trigger the check. <a href="https://github.com/google/googletest/blob/master/googletest/docs/faq.md#why-should-test-suite-names-and-test-names-not-contain-underscore">Underscores are not allowed</a> in test names nor test case names.</p>
<p>The DISABLED_ prefix, which may be used to <a href="https://github.com/google/googletest/blob/master/googletest/docs/faq.md#why-should-test-suite-names-and-test-names-not-contain-underscore">disable individual tests</a>, is ignored when checking test names, but the rest of the rest of the test name is still checked.</p>
<p>This check does not propose any fixes.</p>
<p>(Clang-Tidy original name: google-readability-avoid-underscore-in-googletest-name)</p>


#### Readability Braces Around Statements {#CT_GGL_RBAS}
<p>The google-readability-braces-around-statements check is an alias, please see <a href="readability-braces-around-statements.html">readability-braces-around-statements</a> for more information.</p>
<p>(Clang-Tidy original name: google-readability-braces-around-statements)</p>


#### Readability Casting {#CT_GGL_RC}
<p>Finds usages of C-style casts.</p>
<p><a href="https://google.github.io/styleguide/cppguide.html\#Casting" class="uri">https://google.github.io/styleguide/cppguide.html\#Casting</a></p>
<p>Corresponding cpplint.py check name: readability/casting.</p>
<p>This check is similar to -Wold-style-cast, but it suggests automated fixes in some cases. The reported locations should not be different from the ones generated by -Wold-style-cast.</p>
<p>(Clang-Tidy original name: google-readability-casting)</p>


#### Readability Function Size {#CT_GGL_RFS}
<p>The google-readability-function-size check is an alias, please see <a href="readability-function-size.html">readability-function-size</a> for more information.</p>
<p>(Clang-Tidy original name: google-readability-function-size)</p>


#### Readability Namespace Comments {#CT_GGL_RNC}
<p>The google-readability-namespace-comments check is an alias, please see <a href="llvm-namespace-comment.html">llvm-namespace-comment</a> for more information.</p>
<p>(Clang-Tidy original name: google-readability-namespace-comments)</p>


#### Readability Todo {#CT_GGL_RT}
<p>Finds TODO comments without a username or bug number.</p>
<p>The relevant style guide section is <a href="https://google.github.io/styleguide/cppguide.html\#TODO_Comments" class="uri">https://google.github.io/styleguide/cppguide.html\#TODO_Comments</a>.</p>
<p>Corresponding cpplint.py check: readability/todo</p>
<p>(Clang-Tidy original name: google-readability-todo)</p>


#### Runtime Int {#CT_GGL_RI}
<p>Finds uses of short, long and long long and suggest replacing them with u?intXX(_t)?.</p>
<p>The corresponding style guide rule: <a href="https://google.github.io/styleguide/cppguide.html\#Integer_Types" class="uri">https://google.github.io/styleguide/cppguide.html\#Integer_Types</a>.</p>
<p>Corresponding cpplint.py check: runtime/int.</p>
<h5 id="options-45">Options</h5>
<p>UnsignedTypePrefix</p>
<p>A string specifying the unsigned type prefix. Default is uint.</p>
<p>SignedTypePrefix</p>
<p>A string specifying the signed type prefix. Default is int.</p>
<p>TypeSuffix</p>
<p>A string specifying the type suffix. Default is an empty string.</p>
<p>(Clang-Tidy original name: google-runtime-int)</p>


#### Runtime Operator {#CT_GGL_RO}
<p>Finds overloads of unary operator &amp;.</p>
<p><a href="https://google.github.io/styleguide/cppguide.html\#Operator_Overloading" class="uri">https://google.github.io/styleguide/cppguide.html\#Operator_Overloading</a></p>
<p>Corresponding cpplint.py check name: runtime/operator.</p>
<p>(Clang-Tidy original name: google-runtime-operator)</p>


#### Upgrade Googletest Case {#CT_GGL_UGC}
<p>Finds uses of deprecated Google Test version 1.9 APIs with names containing case and replaces them with equivalent APIs with suite.</p>
<p>All names containing case are being replaced to be consistent with the meanings of “test case” and “test suite” as used by the International Software Testing Qualifications Board and ISO 29119.</p>
<p>The new names are a part of Google Test version 1.9 (release pending). It is recommended that users update their dependency to version 1.9 and then use this check to remove deprecated names.</p>
<p>The affected APIs are:</p>
<ul>
<li>Member functions of testing::Test, testing::TestInfo, testing::TestEventListener, testing::UnitTest, and any type inheriting from these types</li>
<li>The macros TYPED_TEST_CASE, TYPED_TEST_CASE_P, REGISTER_TYPED_TEST_CASE_P, and INSTANTIATE_TYPED_TEST_CASE_P</li>
<li>The type alias testing::TestCase</li>
</ul>
<p>Examples of fixes created by this check:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> FooTest : <span class="kw">public</span> testing::Test {
<span class="kw">public</span>:
  <span class="dt">static</span> <span class="dt">void</span> SetUpTestCase();
  <span class="dt">static</span> <span class="dt">void</span> TearDownTestCase();
};

TYPED_TEST_CASE(BarTest, BarTypes);</code></pre></div>
<p>becomes</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> FooTest : <span class="kw">public</span> testing::Test {
<span class="kw">public</span>:
  <span class="dt">static</span> <span class="dt">void</span> SetUpTestSuite();
  <span class="dt">static</span> <span class="dt">void</span> TearDownTestSuite();
};

TYPED_TEST_SUITE(BarTest, BarTypes);</code></pre></div>
<p>For better consistency of user code, the check renames both virtual and non-virtual member functions with matching names in derived types. The check tries to provide a only warning when a fix cannot be made safely, as is the case with some template and macro uses.</p>
<p>(Clang-Tidy original name: google-upgrade-googletest-case)</p>


### High Integrity C++

#### Avoid C Arrays {#CT_HIC_ACA}
<p>The hicpp-avoid-c-arrays check is an alias, please see <a href="modernize-avoid-c-arrays.html">modernize-avoid-c-arrays</a> for more information.</p>
<p>(Clang-Tidy original name: hicpp-avoid-c-arrays)</p>


#### Avoid Goto {#CT_HIC_AG}
<p>The hicpp-avoid-goto check is an alias to <a href="cppcoreguidelines-avoid-goto.html">cppcoreguidelines-avoid-goto</a>. Rule <a href="http://www.codingstandard.com/rule/6-3-1-ensure-that-the-labels-for-a-jump-statement-or-a-switch-condition-appear-later-in-the-same-or-an-enclosing-block/">6.3.1 High Integrity C++</a> requires that goto only skips parts of a block and is not used for other reasons.</p>
<p>Both coding guidelines implement the same exception to the usage of goto.</p>
<p>(Clang-Tidy original name: hicpp-avoid-goto)</p>


#### Braces Around Statements {#CT_HIC_BAS}
<p>The hicpp-braces-around-statements check is an alias, please see <a href="readability-braces-around-statements.html">readability-braces-around-statements</a> for more information. It enforces the <a href="http://www.codingstandard.com/rule/6-1-1-enclose-the-body-of-a-selection-or-an-iteration-statement-in-a-compound-statement/">rule 6.1.1</a>.</p>
<p>(Clang-Tidy original name: hicpp-braces-around-statements)</p>


#### Deprecated Headers {#CT_HIC_DH}
<p>The hicpp-deprecated-headers check is an alias, please see <a href="modernize-deprecated-headers.html">modernize-deprecated-headers</a> for more information. It enforces the <a href="http://www.codingstandard.com/rule/1-3-3-do-not-use-the-c-standard-library-h-headers/">rule 1.3.3</a>.</p>
<p>(Clang-Tidy original name: hicpp-deprecated-headers)</p>


#### Exception Baseclass {#CT_HIC_EB}
<p>Ensure that every value that in a throw expression is an instance of std::exception.</p>
<p>This enforces <a href="http://www.codingstandard.com/section/15-1-throwing-an-exception/">rule 15.1</a> of the High Integrity C++ Coding Standard.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> custom_exception {};

<span class="dt">void</span> throwing() <span class="kw">noexcept</span>(<span class="kw">false</span>) {
  <span class="co">// Problematic throw expressions.</span>
  <span class="kw">throw</span> <span class="dt">int</span>(<span class="dv">42</span>);
  <span class="kw">throw</span> custom_exception();
}

<span class="kw">class</span> mathematical_error : <span class="kw">public</span> std::exception {};

<span class="dt">void</span> throwing2() <span class="kw">noexcept</span>(<span class="kw">false</span>) {
  <span class="co">// These kind of throws are ok.</span>
  <span class="kw">throw</span> mathematical_error();
  <span class="kw">throw</span> std::runtime_error();
  <span class="kw">throw</span> std::exception();
}</code></pre></div>
<p>(Clang-Tidy original name: hicpp-exception-baseclass)</p>


#### Explicit Conversions {#CT_HIC_EC}
<p>This check is an alias for <a href="google-explicit-constructor.html">google-explicit-constructor</a>. Used to enforce parts of <a href="http://www.codingstandard.com/rule/5-4-1-only-use-casting-forms-static_cast-excl-void-dynamic_cast-or-explicit-constructor-call/">rule 5.4.1</a>. This check will enforce that constructors and conversion operators are marked explicit. Other forms of casting checks are implemented in other places. The following checks can be used to check for more forms of casting:</p>
<ul>
<li><a href="cppcoreguidelines-pro-type-static-cast-downcast.html">cppcoreguidelines-pro-type-static-cast-downcast</a></li>
<li><a href="cppcoreguidelines-pro-type-reinterpret-cast.html">cppcoreguidelines-pro-type-reinterpret-cast</a></li>
<li><a href="cppcoreguidelines-pro-type-const-cast.html">cppcoreguidelines-pro-type-const-cast</a></li>
<li><a href="cppcoreguidelines-pro-type-cstyle-cast.html">cppcoreguidelines-pro-type-cstyle-cast</a></li>
</ul>
<p>(Clang-Tidy original name: hicpp-explicit-conversions)</p>


#### Function Size {#CT_HIC_FS}
<p>This check is an alias for <a href="readability-function-size.html">readability-function-size</a>. Useful to enforce multiple sections on function complexity.</p>
<ul>
<li><a href="http://www.codingstandard.com/rule/8-2-2-do-not-declare-functions-with-an-excessive-number-of-parameters/">rule 8.2.2</a></li>
<li><a href="http://www.codingstandard.com/rule/8-3-1-do-not-write-functions-with-an-excessive-mccabe-cyclomatic-complexity/">rule 8.3.1</a></li>
<li><a href="http://www.codingstandard.com/rule/8-3-2-do-not-write-functions-with-a-high-static-program-path-count/">rule 8.3.2</a></li>
</ul>
<p>(Clang-Tidy original name: hicpp-function-size)</p>


#### Invalid Access Moved {#CT_HIC_IAM}
<p>This check is an alias for <a href="bugprone-use-after-move.html">bugprone-use-after-move</a>.</p>
<p>Implements parts of the <a href="http://www.codingstandard.com/rule/8-4-1-do-not-access-an-invalid-object-or-an-object-with-indeterminate-value/">rule 8.4.1</a> to check if moved-from objects are accessed.</p>
<p>(Clang-Tidy original name: hicpp-invalid-access-moved)</p>


#### Member Init {#CT_HIC_MI}
<p>This check is an alias for <a href="cppcoreguidelines-pro-type-member-init.html">cppcoreguidelines-pro-type-member-init</a>. Implements the check for <a href="http://www.codingstandard.com/rule/12-4-2-ensure-that-a-constructor-initializes-explicitly-all-base-classes-and-non-static-data-members/">rule 12.4.2</a> to initialize class members in the right order.</p>
<p>(Clang-Tidy original name: hicpp-member-init)</p>


#### Move Const Arg {#CT_HIC_MCA}
<p>The hicpp-move-const-arg check is an alias, please see <a href="performance-move-const-arg.html">performance-move-const-arg</a> for more information. It enforces the <a href="http://www.codingstandard.com/rule/17-3-1-do-not-use-stdmove-on-objects-declared-with-const-or-const-type/">rule 17.3.1</a>.</p>
<p>(Clang-Tidy original name: hicpp-move-const-arg)</p>


#### Multiway Paths Covered {#CT_HIC_MPC}
<p>This check discovers situations where code paths are not fully-covered. It furthermore suggests using if instead of switch if the code will be more clear. The <a href="http://www.codingstandard.com/rule/6-1-2-explicitly-cover-all-paths-through-multi-way-selection-statements/">rule 6.1.2</a> and <a href="http://www.codingstandard.com/rule/6-1-4-ensure-that-a-switch-statement-has-at-least-two-case-labels-distinct-from-the-default-label/">rule 6.1.4</a> of the High Integrity C++ Coding Standard are enforced.</p>
<p>if-else if chains that miss a final else branch might lead to unexpected program execution and be the result of a logical error. If the missing else branch is intended you can leave it empty with a clarifying comment. This warning can be noisy on some code bases, so it is disabled by default.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> f1() {
  <span class="dt">int</span> i = determineTheNumber();

   <span class="kw">if</span>(i &gt; <span class="dv">0</span>) {
     <span class="co">// Some Calculation</span>
   } <span class="kw">else</span> <span class="kw">if</span> (i &lt; <span class="dv">0</span>) {
     <span class="co">// Precondition violated or something else.</span>
   }
   <span class="co">// ...</span>
}</code></pre></div>
<p>Similar arguments hold for switch statements which do not cover all possible code paths.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// The missing default branch might be a logical error. It can be kept empty</span>
<span class="co">// if there is nothing to do, making it explicit.</span>
<span class="dt">void</span> f2(<span class="dt">int</span> i) {
  <span class="kw">switch</span> (i) {
  <span class="kw">case</span> <span class="dv">0</span>: <span class="co">// something</span>
    <span class="kw">break</span>;
  <span class="kw">case</span> <span class="dv">1</span>: <span class="co">// something else</span>
    <span class="kw">break</span>;
  }
  <span class="co">// All other numbers?</span>
}

<span class="co">// Violates this rule as well, but already emits a compiler warning (-Wswitch).</span>
<span class="kw">enum</span> Color { Red, Green, Blue, Yellow };
<span class="dt">void</span> f3(<span class="kw">enum</span> Color c) {
  <span class="kw">switch</span> (c) {
  <span class="kw">case</span> Red: <span class="co">// We can&#39;t drive for now.</span>
    <span class="kw">break</span>;
  <span class="kw">case</span> Green:  <span class="co">// We are allowed to drive.</span>
    <span class="kw">break</span>;
  }
  <span class="co">// Other cases missing</span>
}</code></pre></div>
<p>The <a href="http://www.codingstandard.com/rule/6-1-4-ensure-that-a-switch-statement-has-at-least-two-case-labels-distinct-from-the-default-label/">rule 6.1.4</a> requires every switch statement to have at least two case labels other than a default label. Otherwise, the switch could be better expressed with an if statement. Degenerated switch statements without any labels are caught as well.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// Degenerated switch that could be better written as `if`</span>
<span class="dt">int</span> i = <span class="dv">42</span>;
<span class="kw">switch</span>(i) {
  <span class="kw">case</span> <span class="dv">1</span>: <span class="co">// do something here</span>
  <span class="kw">default</span>: <span class="co">// do somethe else here</span>
}

<span class="co">// Should rather be the following:</span>
<span class="kw">if</span> (i == <span class="dv">1</span>) {
  <span class="co">// do something here</span>
}
<span class="kw">else</span> {
  <span class="co">// do something here</span>
}</code></pre></div>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// A completely degenerated switch will be diagnosed.</span>
<span class="dt">int</span> i = <span class="dv">42</span>;
<span class="kw">switch</span>(i) {}</code></pre></div>
<h5 id="options-80">Options</h5>
<p>WarnOnMissingElse</p>
<p>Boolean flag that activates a warning for missing else branches. Default is false.</p>
<p>(Clang-Tidy original name: hicpp-multiway-paths-covered)</p>


#### Named Parameter {#CT_HIC_NP}
<p>This check is an alias for <a href="readability-named-parameter.html">readability-named-parameter</a>.</p>
<p>Implements <a href="http://www.codingstandard.com/rule/8-2-1-make-parameter-names-absent-or-identical-in-all-declarations/">rule 8.2.1</a>.</p>
<p>(Clang-Tidy original name: hicpp-named-parameter)</p>


#### New Delete Operators {#CT_HIC_NDO}
<p>This check is an alias for <a href="misc-new-delete-overloads.html">misc-new-delete-overloads</a>. Implements <a href="http://www.codingstandard.com/section/12-3-free-store/">rule 12.3.1</a> to ensure the new and delete operators have the correct signature.</p>
<p>(Clang-Tidy original name: hicpp-new-delete-operators)</p>


#### No Array Decay {#CT_HIC_NAD}
<p>The hicpp-no-array-decay check is an alias, please see <a href="cppcoreguidelines-pro-bounds-array-to-pointer-decay.html">cppcoreguidelines-pro-bounds-array-to-pointer-decay</a> for more information. It enforces the <a href="http://www.codingstandard.com/section/4-1-array-to-pointer-conversion/">rule 4.1.1</a>.</p>
<p>(Clang-Tidy original name: hicpp-no-array-decay)</p>


#### No Assembler {#CT_HIC_NA}
<p>Check for assembler statements. No fix is offered.</p>
<p>Inline assembler is forbidden by the <a href="http://www.codingstandard.com/section/7-5-the-asm-declaration/">High Intergrity C++ Coding Standard</a> as it restricts the portability of code.</p>
<p>(Clang-Tidy original name: hicpp-no-assembler)</p>


#### No Malloc {#CT_HIC_NM2}
<p>The hicpp-no-malloc check is an alias, please see <a href="cppcoreguidelines-no-malloc.html">cppcoreguidelines-no-malloc</a> for more information. It enforces the <a href="http://www.codingstandard.com/rule/5-3-2-allocate-memory-using-new-and-release-it-using-delete/">rule 5.3.2</a>.</p>
<p>(Clang-Tidy original name: hicpp-no-malloc)</p>


#### Noexcept Move {#CT_HIC_NM}
<p>This check is an alias for <a href="performance-noexcept-move-constructor.html">performance-noexcept-move-constructor</a>. Checks <a href="http://www.codingstandard.com/rule/12-5-4-declare-noexcept-the-move-constructor-and-move-assignment-operator">rule 12.5.4</a> to mark move assignment and move construction noexcept.</p>
<p>(Clang-Tidy original name: hicpp-noexcept-move)</p>


#### Signed Bitwise {#CT_HIC_SB}
<p>Finds uses of bitwise operations on signed integer types, which may lead to undefined or implementation defined behaviour.</p>
<p>The according rule is defined in the <a href="http://www.codingstandard.com/section/5-6-shift-operators/">High Integrity C++ Standard, Section 5.6.1</a>.</p>
<h5 id="options-6">Options</h5>
<p>IgnorePositiveIntegerLiterals</p>
<p>If this option is set to true, the check will not warn on bitwise operations with positive integer literals, e.g. ~0, 2 &lt;&lt; 1, etc. Default value is false.</p>
<p>(Clang-Tidy original name: hicpp-signed-bitwise)</p>


#### Special Member Functions {#CT_HIC_SMF}
<p>This check is an alias for <a href="cppcoreguidelines-special-member-functions.html">cppcoreguidelines-special-member-functions</a>. Checks that special member functions have the correct signature, according to <a href="http://www.codingstandard.com/rule/12-5-7-declare-assignment-operators-with-the-ref-qualifier/">rule 12.5.7</a>.</p>
<p>(Clang-Tidy original name: hicpp-special-member-functions)</p>


#### Static Assert {#CT_HIC_SA}
<p>The hicpp-static-assert check is an alias, please see <a href="misc-static-assert.html">misc-static-assert</a> for more information. It enforces the <a href="http://www.codingstandard.com/rule/6-1-1-enclose-the-body-of-a-selection-or-an-iteration-statement-in-a-compound-statement/">rule 7.1.10</a>.</p>
<p>(Clang-Tidy original name: hicpp-static-assert)</p>


#### Undelegated Constructor {#CT_HIC_UC}
<p>This check is an alias for <a href="bugprone-undelegated-constructor.html">bugprone-undelegated-constructor</a>. Partially implements <a href="http://www.codingstandard.com/rule/12-4-5-use-delegating-constructors-to-reduce-code-duplication/">rule 12.4.5</a> to find misplaced constructor calls inside a constructor.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">struct</span> Ctor {
  Ctor();
  Ctor(<span class="dt">int</span>);
  Ctor(<span class="dt">int</span>, <span class="dt">int</span>);
  Ctor(Ctor *i) {
    <span class="co">// All Ctor() calls result in a temporary object</span>
    Ctor(); <span class="co">// did you intend to call a delegated constructor?</span>
    Ctor(<span class="dv">0</span>); <span class="co">// did you intend to call a delegated constructor?</span>
    Ctor(<span class="dv">1</span>, <span class="dv">2</span>); <span class="co">// did you intend to call a delegated constructor?</span>
    foo();
  }
};</code></pre></div>
<p>(Clang-Tidy original name: hicpp-undelegated-constructor)</p>


#### Uppercase Literal Suffix {#CT_HIC_ULS}
<p>The hicpp-uppercase-literal-suffix check is an alias, please see <a href="readability-uppercase-literal-suffix.html">readability-uppercase-literal-suffix</a> for more information.</p>
<p>(Clang-Tidy original name: hicpp-uppercase-literal-suffix)</p>


#### Use Auto {#CT_HIC_UA}
<p>The hicpp-use-auto check is an alias, please see <a href="modernize-use-auto.html">modernize-use-auto</a> for more information. It enforces the <a href="http://www.codingstandard.com/rule/7-1-8-use-auto-id-expr-when-declaring-a-variable-to-have-the-same-type-as-its-initializer-function-call/">rule 7.1.8</a>.</p>
<p>(Clang-Tidy original name: hicpp-use-auto)</p>


#### Use Emplace {#CT_HIC_UE}
<p>The hicpp-use-emplace check is an alias, please see <a href="modernize-use-emplace.html">modernize-use-emplace</a> for more information. It enforces the <a href="http://www.codingstandard.com/rule/17-4-2-use-api-calls-that-construct-objects-in-place/">rule 17.4.2</a>.</p>
<p>(Clang-Tidy original name: hicpp-use-emplace)</p>


#### Use Equals Default {#CT_HIC_UED}
<p>This check is an alias for <a href="modernize-use-equals-default.html">modernize-use-equals-default</a>. Implements <a href="http://www.codingstandard.com/rule/12-5-1-define-explicitly-default-or-delete-implicit-special-member-functions-of-concrete-classes/">rule 12.5.1</a> to explicitly default special member functions.</p>
<p>(Clang-Tidy original name: hicpp-use-equals-default)</p>


#### Use Equals Delete {#CT_HIC_UED2}
<p>This check is an alias for <a href="modernize-use-equals-delete.html">modernize-use-equals-delete</a>. Implements <a href="http://www.codingstandard.com/rule/12-5-1-define-explicitly-default-or-delete-implicit-special-member-functions-of-concrete-classes/">rule 12.5.1</a> to explicitly default or delete special member functions.</p>
<p>(Clang-Tidy original name: hicpp-use-equals-delete)</p>


#### Use Noexcept {#CT_HIC_UN}
<p>The hicpp-use-noexcept check is an alias, please see <a href="modernize-use-noexcept.html">modernize-use-noexcept</a> for more information. It enforces the <a href="http://www.codingstandard.com/rule/1-3-5-do-not-use-throw-exception-specifications/">rule 1.3.5</a>.</p>
<p>(Clang-Tidy original name: hicpp-use-noexcept)</p>


#### Use Nullptr {#CT_HIC_UN2}
<p>The hicpp-use-nullptr check is an alias, please see <a href="modernize-use-nullptr.html">modernize-use-nullptr</a> for more information. It enforces the <a href="http://www.codingstandard.com/rule/2-5-3-use-nullptr-for-the-null-pointer-constant/">rule 2.5.3</a>.</p>
<p>(Clang-Tidy original name: hicpp-use-nullptr)</p>


#### Use Override {#CT_HIC_UO}
<p>This check is an alias for <a href="modernize-use-override.html">modernize-use-override</a>. Implements <a href="http://www.codingstandard.com/section/10-2-virtual-functions/">rule 10.2.1</a> to declare a virtual function override when overriding.</p>
<p>(Clang-Tidy original name: hicpp-use-override)</p>


#### Vararg {#CT_HIC_V}
<p>The hicpp-vararg check is an alias, please see <a href="cppcoreguidelines-pro-type-vararg.html">cppcoreguidelines-pro-type-vararg</a> for more information. It enforces the <a href="http://www.codingstandard.com/section/14-1-template-declarations/">rule 14.1.1</a>.</p>
<p>(Clang-Tidy original name: hicpp-vararg)</p>


### LLVM

#### Else After Return {#CT_LLV_EAR}
<p>The llvm-else-after-return check is an alias, please see <a href="readability-else-after-return.html">readability-else-after-return</a> for more information.</p>
<p>(Clang-Tidy original name: llvm-else-after-return)</p>


#### Header Guard {#CT_LLV_HG}
<p>Finds and fixes header guards that do not adhere to LLVM style.</p>
<h5 id="options-7">Options</h5>
<p>HeaderFileExtensions</p>
<p>A comma-separated list of filename extensions of header files (the filename extensions should not include “.” prefix). Default is “h,hh,hpp,hxx”. For header files without an extension, use an empty string (if there are no other desired extensions) or leave an empty element in the list. e.g., “h,hh,hpp,hxx,” (note the trailing comma).</p>
<p>(Clang-Tidy original name: llvm-header-guard)</p>


#### Include Order {#CT_LLV_IO}
<p>Checks the correct order of #includes.</p>
<p>See <a href="https://llvm.org/docs/CodingStandards.html\#include-style" class="uri">https://llvm.org/docs/CodingStandards.html\#include-style</a></p>
<p>(Clang-Tidy original name: llvm-include-order)</p>


#### Namespace Comment {#CT_LLV_NC}
<p>google-readability-namespace-comments redirects here as an alias for this check.</p>
<p>Checks that long namespaces have a closing comment.</p>
<p><a href="https://llvm.org/docs/CodingStandards.html\#namespace-indentation" class="uri">https://llvm.org/docs/CodingStandards.html\#namespace-indentation</a></p>
<p><a href="https://google.github.io/styleguide/cppguide.html\#Namespaces" class="uri">https://google.github.io/styleguide/cppguide.html\#Namespaces</a></p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">namespace</span> n1 {
<span class="dt">void</span> f();
}

<span class="co">// becomes</span>

<span class="kw">namespace</span> n1 {
<span class="dt">void</span> f();
}  <span class="co">// namespace n1</span></code></pre></div>
<h5 id="options-78">Options</h5>
<p>ShortNamespaceLines</p>
<p>Requires the closing brace of the namespace definition to be followed by a closing comment if the body of the namespace has more than ShortNamespaceLines lines of code. The value is an unsigned integer that defaults to 1U.</p>
<p>SpacesBeforeComments</p>
<p>An unsigned integer specifying the number of spaces before the comment closing a namespace definition. Default is 1U.</p>
<p>(Clang-Tidy original name: llvm-namespace-comment)</p>


#### Prefer Isa Or Dyn Cast In Conditionals {#CT_LLV_PIODCIC}
<p>Looks at conditionals and finds and replaces cases of cast&lt;&gt;, which will assert rather than return a null pointer, and dyn_cast&lt;&gt; where the return value is not captured. Additionally, finds and replaces cases that match the pattern var &amp;&amp; isa<X>(var), where var is evaluated twice.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// Finds these:</span>
<span class="kw">if</span> (<span class="kw">auto</span> x = cast&lt;X&gt;(y)) {}
<span class="co">// is replaced by:</span>
<span class="kw">if</span> (<span class="kw">auto</span> x = dyn_cast&lt;X&gt;(y)) {}

<span class="kw">if</span> (cast&lt;X&gt;(y)) {}
<span class="co">// is replaced by:</span>
<span class="kw">if</span> (isa&lt;X&gt;(y)) {}

<span class="kw">if</span> (dyn_cast&lt;X&gt;(y)) {}
<span class="co">// is replaced by:</span>
<span class="kw">if</span> (isa&lt;X&gt;(y)) {}

<span class="kw">if</span> (var &amp;&amp; isa&lt;T&gt;(var)) {}
<span class="co">// is replaced by:</span>
<span class="kw">if</span> (isa_and_nonnull&lt;T&gt;(var.foo())) {}

<span class="co">// Other cases are ignored, e.g.:</span>
<span class="kw">if</span> (<span class="kw">auto</span> f = cast&lt;Z&gt;(y)-&gt;foo()) {}
<span class="kw">if</span> (cast&lt;Z&gt;(y)-&gt;foo()) {}
<span class="kw">if</span> (X.cast(y)) {}</code></pre></div>
<p>(Clang-Tidy original name: llvm-prefer-isa-or-dyn-cast-in-conditionals)</p>


#### Prefer Register Over Unsigned {#CT_LLV_PROU}
<p>Finds historical use of unsigned to hold vregs and physregs and rewrites them to use Register.</p>
<p>Currently this works by finding all variables of unsigned integer type whose initializer begins with an implicit cast from Register to unsigned.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> example(MachineOperand &amp;MO) {
  <span class="dt">unsigned</span> Reg = MO.getReg();
  ...
}</code></pre></div>
<p>becomes:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> example(MachineOperand &amp;MO) {
  Register Reg = MO.getReg();
  ...
}</code></pre></div>
<p>(Clang-Tidy original name: llvm-prefer-register-over-unsigned)</p>


#### Qualified Auto {#CT_LLV_QA}
<p>The llvm-qualified-auto check is an alias, please see <a href="readability-qualified-auto.html">readability-qualified-auto</a> for more information.</p>
<p>(Clang-Tidy original name: llvm-qualified-auto)</p>


#### Twine Local {#CT_LLV_TL}
<p>Looks for local Twine variables which are prone to use after frees and should be generally avoided.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">static</span> Twine Moo = Twine(<span class="st">&quot;bark&quot;</span>) + <span class="st">&quot;bah&quot;</span>;

<span class="co">// becomes</span>

<span class="dt">static</span> std::string Moo = (Twine(<span class="st">&quot;bark&quot;</span>) + <span class="st">&quot;bah&quot;</span>).str();</code></pre></div>
<p>(Clang-Tidy original name: llvm-twine-local)</p>


### LLVM-libc

#### Callee Namespace {#CT_LLC_CN}
<p>Checks all calls resolve to functions within __llvm_libc namespace.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">namespace</span> __llvm_libc {

<span class="co">// Allow calls with the fully qualified name.</span>
__llvm_libc::strlen(<span class="st">&quot;hello&quot;</span>);

<span class="co">// Allow calls to compiler provided functions.</span>
(<span class="dt">void</span>)<span class="ot">__builtin_abs</span>(<span class="dv">-1</span>);

<span class="co">// Bare calls are allowed as long as they resolve to the correct namespace.</span>
strlen(<span class="st">&quot;world&quot;</span>);

<span class="co">// Disallow calling into functions in the global namespace.</span>
::strlen(<span class="st">&quot;!&quot;</span>);

} <span class="co">// namespace __llvm_libc</span></code></pre></div>
<p>(Clang-Tidy original name: llvmlibc-callee-namespace)</p>


#### Implementation In Namespace {#CT_LLC_IIN}
<p>Checks that all declarations in the llvm-libc implementation are within the correct namespace.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// Correct: implementation inside the correct namespace.</span>
<span class="kw">namespace</span> __llvm_libc {
    <span class="dt">void</span> LLVM_LIBC_ENTRYPOINT(strcpy)(<span class="dt">char</span> *dest, <span class="dt">const</span> <span class="dt">char</span> *src) {}
    <span class="co">// Namespaces within __llvm_libc namespace are allowed.</span>
    <span class="kw">namespace</span> inner{
        <span class="dt">int</span> localVar = <span class="dv">0</span>;
    }
    <span class="co">// Functions with C linkage are allowed.</span>
    <span class="dt">extern</span> <span class="st">&quot;C&quot;</span> <span class="dt">void</span> str_fuzz(){}
}

<span class="co">// Incorrect: implementation not in a namespace.</span>
<span class="dt">void</span> LLVM_LIBC_ENTRYPOINT(strcpy)(<span class="dt">char</span> *dest, <span class="dt">const</span> <span class="dt">char</span> *src) {}

<span class="co">// Incorrect: outer most namespace is not correct.</span>
<span class="kw">namespace</span> something_else {
    <span class="dt">void</span> LLVM_LIBC_ENTRYPOINT(strcpy)(<span class="dt">char</span> *dest, <span class="dt">const</span> <span class="dt">char</span> *src) {}
}</code></pre></div>
<p>(Clang-Tidy original name: llvmlibc-implementation-in-namespace)</p>


#### Restrict System Libc Headers {#CT_LLC_RSLH}
<p>Finds includes of system libc headers not provided by the compiler within llvm-libc implementations.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="ot">#include &lt;stdio.h&gt;            </span><span class="co">// Not allowed because it is part of system libc.</span>
<span class="ot">#include &lt;stddef.h&gt;           </span><span class="co">// Allowed because it is provided by the compiler.</span>
<span class="ot">#include &quot;internal/stdio.h&quot;   </span><span class="co">// Allowed because it is NOT part of system libc.</span></code></pre></div>
<p>This check is necessary because accidentally including system libc headers can lead to subtle and hard to detect bugs. For example consider a system libc whose dirent struct has slightly different field ordering than llvm-libc. While this will compile successfully, this can cause issues during runtime because they are ABI incompatible.</p>
<h5 id="options-22">Options</h5>
<p>Includes</p>
<p>A string containing a comma separated glob list of allowed include filenames. Similar to the -checks glob list for running clang-tidy itself, the two wildcard characters are * and -, to include and exclude globs, respectively. The default is -*, which disallows all includes.</p>
<p>This can be used to allow known safe includes such as Linux development headers. See <a href="portability-restrict-system-includes.html">portability-restrict-system-includes</a> for more details.</p>
<p>(Clang-Tidy original name: llvmlibc-restrict-system-libc-headers)</p>


### Linux Kernel

#### Must Check Errs {#CT_KRN_MCE}
<p>Checks Linux kernel code to see if it uses the results from the functions in linux/err.h. Also checks to see if code uses the results from functions that directly return a value from one of these error functions.</p>
<p>This is important in the Linux kernel because ERR_PTR, PTR_ERR, IS_ERR, IS_ERR_OR_NULL, ERR_CAST, and PTR_ERR_OR_ZERO return values must be checked, since positive pointers and negative error codes are being used in the same context. These functions are marked with <strong>attribute</strong>((warn_unused_result)), but some kernel versions do not have this warning enabled for clang.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">/* Trivial unused call to an ERR function */</span>
PTR_ERR_OR_ZERO(some_function_call());

<span class="co">/* A function that returns ERR_PTR. */</span>
<span class="dt">void</span> *fn() { ERR_PTR(-EINVAL); }

<span class="co">/* An invalid use of fn. */</span>
fn();</code></pre></div>
<p>(Clang-Tidy original name: linuxkernel-must-check-errs)</p>


### MPI

#### Buffer Deref {#CT_MPI_BD}
<p>This check verifies if a buffer passed to an MPI (Message Passing Interface) function is sufficiently dereferenced. Buffers should be passed as a single pointer or array. As MPI function signatures specify void * for their buffer types, insufficiently dereferenced buffers can be passed, like for example as double pointers or multidimensional arrays, without a compiler warning emitted.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// A double pointer is passed to the MPI function.</span>
<span class="dt">char</span> *buf;
MPI_Send(&amp;buf, <span class="dv">1</span>, MPI_CHAR, <span class="dv">0</span>, <span class="dv">0</span>, MPI_COMM_WORLD);

<span class="co">// A multidimensional array is passed to the MPI function.</span>
<span class="dt">short</span> buf[<span class="dv">1</span>][<span class="dv">1</span>];
MPI_Send(buf, <span class="dv">1</span>, MPI_SHORT, <span class="dv">0</span>, <span class="dv">0</span>, MPI_COMM_WORLD);

<span class="co">// A pointer to an array is passed to the MPI function.</span>
<span class="dt">short</span> *buf[<span class="dv">1</span>];
MPI_Send(buf, <span class="dv">1</span>, MPI_SHORT, <span class="dv">0</span>, <span class="dv">0</span>, MPI_COMM_WORLD);</code></pre></div>
<p>(Clang-Tidy original name: mpi-buffer-deref)</p>


#### Type Mismatch {#CT_MPI_TM}
<p>This check verifies if buffer type and MPI (Message Passing Interface) datatype pairs match for used MPI functions. All MPI datatypes defined by the MPI standard (3.1) are verified by this check. User defined typedefs, custom MPI datatypes and null pointer constants are skipped, in the course of verification.</p>
<p>Example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// In this case, the buffer type matches MPI datatype.</span>
<span class="dt">char</span> buf;
MPI_Send(&amp;buf, <span class="dv">1</span>, MPI_CHAR, <span class="dv">0</span>, <span class="dv">0</span>, MPI_COMM_WORLD);

<span class="co">// In the following case, the buffer type does not match MPI datatype.</span>
<span class="dt">int</span> buf;
MPI_Send(&amp;buf, <span class="dv">1</span>, MPI_CHAR, <span class="dv">0</span>, <span class="dv">0</span>, MPI_COMM_WORLD);</code></pre></div>
<p>(Clang-Tidy original name: mpi-type-mismatch)</p>


### Miscellaneous

#### Definitions In Headers {#CT_MSC_DIH}
<p>Finds non-extern non-inline function and variable definitions in header files, which can lead to potential ODR violations in case these headers are included from multiple translation units.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// Foo.h</span>
<span class="dt">int</span> a = <span class="dv">1</span>; <span class="co">// Warning: variable definition.</span>
<span class="dt">extern</span> <span class="dt">int</span> d; <span class="co">// OK: extern variable.</span>

<span class="kw">namespace</span> N {
  <span class="dt">int</span> e = <span class="dv">2</span>; <span class="co">// Warning: variable definition.</span>
}

<span class="co">// Warning: variable definition.</span>
<span class="dt">const</span> <span class="dt">char</span>* str = <span class="st">&quot;foo&quot;</span>;

<span class="co">// OK: internal linkage variable definitions are ignored for now.</span>
<span class="co">// Although these might also cause ODR violations, we can be less certain and</span>
<span class="co">// should try to keep the false-positive rate down.</span>
<span class="dt">static</span> <span class="dt">int</span> b = <span class="dv">1</span>;
<span class="dt">const</span> <span class="dt">int</span> c = <span class="dv">1</span>;
<span class="dt">const</span> <span class="dt">char</span>* <span class="dt">const</span> str2 = <span class="st">&quot;foo&quot;</span>;
<span class="kw">constexpr</span> <span class="dt">int</span> k = <span class="dv">1</span>;

<span class="co">// Warning: function definition.</span>
<span class="dt">int</span> g() {
  <span class="kw">return</span> <span class="dv">1</span>;
}

<span class="co">// OK: inline function definition is allowed to be defined multiple times.</span>
<span class="kw">inline</span> <span class="dt">int</span> e() {
  <span class="kw">return</span> <span class="dv">1</span>;
}

<span class="kw">class</span> A {
<span class="kw">public</span>:
  <span class="dt">int</span> f1() { <span class="kw">return</span> <span class="dv">1</span>; } <span class="co">// OK: implicitly inline member function definition is allowed.</span>
  <span class="dt">int</span> f2();

  <span class="dt">static</span> <span class="dt">int</span> d;
};

<span class="co">// Warning: not an inline member function definition.</span>
<span class="dt">int</span> A::f2() { <span class="kw">return</span> <span class="dv">1</span>; }

<span class="co">// OK: class static data member declaration is allowed.</span>
<span class="dt">int</span> A::d = <span class="dv">1</span>;

<span class="co">// OK: function template is allowed.</span>
<span class="kw">template</span>&lt;<span class="kw">typename</span> T&gt;
T f3() {
  T a = <span class="dv">1</span>;
  <span class="kw">return</span> a;
}

<span class="co">// Warning: full specialization of a function template is not allowed.</span>
<span class="kw">template</span> &lt;&gt;
<span class="dt">int</span> f3() {
  <span class="dt">int</span> a = <span class="dv">1</span>;
  <span class="kw">return</span> a;
}

<span class="kw">template</span> &lt;<span class="kw">typename</span> T&gt;
<span class="kw">struct</span> B {
  <span class="dt">void</span> f1();
};

<span class="co">// OK: member function definition of a class template is allowed.</span>
<span class="kw">template</span> &lt;<span class="kw">typename</span> T&gt;
<span class="dt">void</span> B&lt;T&gt;::f1() {}

<span class="kw">class</span> CE {
  <span class="kw">constexpr</span> <span class="dt">static</span> <span class="dt">int</span> i = <span class="dv">5</span>; <span class="co">// OK: inline variable definition.</span>
};

<span class="kw">inline</span> <span class="dt">int</span> i = <span class="dv">5</span>; <span class="co">// OK: inline variable definition.</span>

<span class="kw">constexpr</span> <span class="dt">int</span> f10() { <span class="kw">return</span> <span class="dv">0</span>; } <span class="co">// OK: constexpr function implies inline.</span>

<span class="co">// OK: C++14 variable templates are inline.</span>
<span class="kw">template</span> &lt;<span class="kw">class</span> T&gt;
<span class="kw">constexpr</span> T pi = T(<span class="fl">3.1415926L</span>);</code></pre></div>
<h5 id="options-73">Options</h5>
<p>HeaderFileExtensions</p>
<p>A comma-separated list of filename extensions of header files (the filename extensions should not include “.” prefix). Default is “h,hh,hpp,hxx”. For header files without an extension, use an empty string (if there are no other desired extensions) or leave an empty element in the list. e.g., “h,hh,hpp,hxx,” (note the trailing comma).</p>
<p>UseHeaderFileExtension</p>
<p>When true, the check will use the file extension to distinguish header files. Default is true.</p>
<p>(Clang-Tidy original name: misc-definitions-in-headers)</p>


#### Misplaced Const {#CT_MSC_MC}
<p>This check diagnoses when a const qualifier is applied to a typedef/ using to a pointer type rather than to the pointee, because such constructs are often misleading to developers because the const applies to the pointer rather than the pointee.</p>
<p>For instance, in the following code, the resulting type is int * const rather than const int *:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">typedef</span> <span class="dt">int</span> *int_ptr;
<span class="dt">void</span> f(<span class="dt">const</span> int_ptr ptr) {
  *ptr = <span class="dv">0</span>; <span class="co">// potentially quite unexpectedly the int can be modified here</span>
  ptr = <span class="dv">0</span>; <span class="co">// does not compile</span>
}</code></pre></div>
<p>The check does not diagnose when the underlying typedef/using type is a pointer to a const type or a function pointer type. This is because the const qualifier is less likely to be mistaken because it would be redundant (or disallowed) on the underlying pointee type.</p>
<p>(Clang-Tidy original name: misc-misplaced-const)</p>


#### New Delete Overloads {#CT_MSC_NDO}
<p>cert-dcl54-cpp redirects here as an alias for this check.</p>
<p>The check flags overloaded operator new() and operator delete() functions that do not have a corresponding free store function defined within the same scope. For instance, the check will flag a class implementation of a non-placement operator new() when the class does not also define a non-placement operator delete() function as well.</p>
<p>The check does not flag implicitly-defined operators, deleted or private operators, or placement operators.</p>
<p>This check corresponds to CERT C++ Coding Standard rule <a href="https://www.securecoding.cert.org/confluence/display/cplusplus/DCL54-CPP.+Overload+allocation+and+deallocation+functions+as+a+pair+in+the+same+scope">DCL54-CPP. Overload allocation and deallocation functions as a pair in the same scope</a>.</p>
<p>(Clang-Tidy original name: misc-new-delete-overloads)</p>


#### No Recursion {#CT_MSC_NR}
<p>Finds strongly connected functions (by analyzing the call graph for SCC’s (Strongly Connected Components) that are loops), diagnoses each function in the cycle, and displays one example of a possible call graph loop (recursion).</p>
<p>References:</p>
<ul>
<li>CERT C++ Coding Standard rule <a href="https://wiki.sei.cmu.edu/confluence/display/cplusplus/DCL56-CPP.+Avoid+cycles+during+initialization+of+static+objects">DCL56-CPP. Avoid cycles during initialization of static objects</a>.</li>
<li>JPL Institutional Coding Standard for the C Programming Language (JPL DOCID D-60411) rule 2.4 Do not use direct or indirect recursion.</li>
<li>OpenCL Specification, Version 1.2 rule <a href="https://www.khronos.org/registry/OpenCL/specs/opencl-1.2.pdf">6.9 Restrictions: i. Recursion is not supported.</a>.</li>
</ul>
<p>Limitations:</p>
<ul>
<li>The check does not handle calls done through function pointers</li>
<li>The check does not handle C++ destructors</li>
</ul>
<p>(Clang-Tidy original name: misc-no-recursion)</p>


#### Non Copyable Objects {#CT_MSC_NCO}
<p>cert-fio38-c redirects here as an alias for this check.</p>
<p>The check flags dereferences and non-pointer declarations of objects that are not meant to be passed by value, such as C FILE objects or POSIX pthread_mutex_t objects.</p>
<p>This check corresponds to CERT C++ Coding Standard rule <a href="https://www.securecoding.cert.org/confluence/display/c/FIO38-C.+Do+not+copy+a+FILE+object">FIO38-C. Do not copy a FILE object</a>.</p>
<p>(Clang-Tidy original name: misc-non-copyable-objects)</p>


#### Non Private Member Variables In Classes {#CT_MSC_NPMVIC}
<p>cppcoreguidelines-non-private-member-variables-in-classes redirects here as an alias for this check.</p>
<p>Finds classes that contain non-static data members in addition to user-declared non-static member functions and diagnose all data members declared with a non-public access specifier. The data members should be declared as private and accessed through member functions instead of exposed to derived classes or class consumers.</p>
<h5 id="options-2">Options</h5>
<p>IgnoreClassesWithAllMemberVariablesBeingPublic</p>
<p>Allows to completely ignore classes if <strong>all</strong> the member variables in that class a declared with a public access specifier.</p>
<p>IgnorePublicMemberVariables</p>
<p>Allows to ignore (not diagnose) <strong>all</strong> the member variables declared with a public access specifier.</p>
<p>(Clang-Tidy original name: misc-non-private-member-variables-in-classes)</p>


#### Redundant Expression {#CT_MSC_RE}
<p>Detect redundant expressions which are typically errors due to copy-paste.</p>
<p>Depending on the operator expressions may be</p>
<ul>
<li>redundant,</li>
<li>always true,</li>
<li>always false,</li>
<li>always a constant (zero or one).</li>
</ul>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">((x<span class="dv">+1</span>) | (x<span class="dv">+1</span>))             <span class="co">// (x+1) is redundant</span>
(p-&gt;x == p-&gt;x)              <span class="co">// always true</span>
(p-&gt;x &lt; p-&gt;x)               <span class="co">// always false</span>
(speed - speed + <span class="dv">1</span> == <span class="dv">12</span>)   <span class="co">// speed - speed is always zero</span></code></pre></div>
<p>(Clang-Tidy original name: misc-redundant-expression)</p>


#### Static Assert {#CT_MSC_SA2}
<p>cert-dcl03-c redirects here as an alias for this check.</p>
<p>Replaces assert() with static_assert() if the condition is evaluatable at compile time.</p>
<p>The condition of static_assert() is evaluated at compile time which is safer and more efficient.</p>
<p>(Clang-Tidy original name: misc-static-assert)</p>


#### Throw By Value Catch By Reference {#CT_MSC_TBVCBR}
<p>cert-err09-cpp redirects here as an alias for this check. cert-err61-cpp redirects here as an alias for this check.</p>
<p>Finds violations of the rule “Throw by value, catch by reference” presented for example in “C++ Coding Standards” by H. Sutter and A. Alexandrescu, as well as the CERT C++ Coding Standard rule <a href="https://wiki.sei.cmu.edu/confluence/display/cplusplus/ERR61-CPP.+Catch+exceptions+by+lvalue+reference">ERR61-CPP. Catch exceptions by lvalue reference</a>.</p>
<p>Exceptions:</p>
<ul>
<li>Throwing string literals will not be flagged despite being a pointer. They are not susceptible to slicing and the usage of string literals is idomatic.</li>
<li>Catching character pointers (char, wchar_t, unicode character types) will not be flagged to allow catching sting literals.</li>
<li>Moved named values will not be flagged as not throwing an anonymous temporary. In this case we can be sure that the user knows that the object can’t be accessed outside catch blocks handling the error.</li>
<li>Throwing function parameters will not be flagged as not throwing an anonymous temporary. This allows helper functions for throwing.</li>
<li>Re-throwing caught exception variables will not be flragged as not throwing an anonymous temporary. Although this can usually be done by just writing throw; it happens often enough in real code.</li>
</ul>
<h5 id="options-61">Options</h5>
<p>CheckThrowTemporaries</p>
<p>Triggers detection of violations of the CERT recommendation ERR09-CPP. Throw anonymous temporaries. Default is true.</p>
<p>WarnOnLargeObject</p>
<p>Also warns for any large, trivial object caught by value. Catching a large object by value is not dangerous but affects the performance negatively. The maximum size of an object allowed to be caught without warning can be set using the MaxSize option. Default is false.</p>
<p>MaxSize</p>
<p>Determines the maximum size of an object allowed to be caught without warning. Only applicable if <a href="#cmdoption-arg-warnonlargeobject">WarnOnLargeObject</a> is set to true. If the option is set by the user to std::numeric_limits<uint64_t>::max() then it reverts to the default value. Default is the size of size_t.</p>
<p>(Clang-Tidy original name: misc-throw-by-value-catch-by-reference)</p>


#### Unconventional Assign Operator {#CT_MSC_UAO}
<p>Finds declarations of assign operators with the wrong return and/or argument types and definitions with good return type but wrong return statements.</p>
<ul>
<li>The return type must be Class&amp;.</li>
<li>Works with move-assign and assign by value.</li>
<li>Private and deleted operators are ignored.</li>
<li>The operator must always return *this.</li>
</ul>
<p>(Clang-Tidy original name: misc-unconventional-assign-operator)</p>


#### Uniqueptr Reset Release {#CT_MSC_URR}
<p>Find and replace unique_ptr::reset(release()) with std::move().</p>
<p>Example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::unique_ptr&lt;Foo&gt; x, y;
x.reset(y.release()); -&gt; x = std::move(y);</code></pre></div>
<p>If y is already rvalue, std::move() is not added. x and y can also be std::unique_ptr<Foo>*.</p>
<p>(Clang-Tidy original name: misc-uniqueptr-reset-release)</p>


#### Unused Alias Decls {#CT_MSC_UAD}
<p>Finds unused namespace alias declarations.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">namespace</span> my_namespace {
<span class="kw">class</span> C {};
}
<span class="kw">namespace</span> unused_alias = ::my_namespace;</code></pre></div>
<p>(Clang-Tidy original name: misc-unused-alias-decls)</p>


#### Unused Parameters {#CT_MSC_UP}
<p>Finds unused function parameters. Unused parameters may signify a bug in the code (e.g. when a different parameter is used instead). The suggested fixes either comment parameter name out or remove the parameter completely, if all callers of the function are in the same translation unit and can be updated.</p>
<p>The check is similar to the -Wunused-parameter compiler diagnostic and can be used to prepare a codebase to enabling of that diagnostic. By default the check is more permissive (see <a href="performance-inefficient-string-concatenation.html#cmdoption-arg-strictmode">StrictMode</a>).</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> a(<span class="dt">int</span> i) { <span class="co">/*some code that doesn&#39;t use `i`*/</span> }

<span class="co">// becomes</span>

<span class="dt">void</span> a(<span class="dt">int</span>  <span class="co">/*i*/</span>) { <span class="co">/*some code that doesn&#39;t use `i`*/</span> }</code></pre></div>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">static</span> <span class="dt">void</span> staticFunctionA(<span class="dt">int</span> i);
<span class="dt">static</span> <span class="dt">void</span> staticFunctionA(<span class="dt">int</span> i) { <span class="co">/*some code that doesn&#39;t use `i`*/</span> }

<span class="co">// becomes</span>

<span class="dt">static</span> <span class="dt">void</span> staticFunctionA()
<span class="dt">static</span> <span class="dt">void</span> staticFunctionA() { <span class="co">/*some code that doesn&#39;t use `i`*/</span> }</code></pre></div>
<h5 id="options-12">Options</h5>
<p>StrictMode</p>
<p>When false (default value), the check will ignore trivially unused parameters, i.e. when the corresponding function has an empty body (and in case of constructors - no constructor initializers). When the function body is empty, an unused parameter is unlikely to be unnoticed by a human reader, and there’s basically no place for a bug to hide.</p>
<p>(Clang-Tidy original name: misc-unused-parameters)</p>


#### Unused Using Decls {#CT_MSC_UUD}
<p>Finds unused using declarations.</p>
<p>Example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">namespace</span> n { <span class="kw">class</span> C; }
<span class="kw">using</span> n::C;  <span class="co">// Never actually used.</span></code></pre></div>
<p>(Clang-Tidy original name: misc-unused-using-decls)</p>


### Modernize

#### Avoid Bind {#CT_MDR_AB}
<p>The check finds uses of std::bind and boost::bind and replaces them with lambdas. Lambdas will use value-capture unless reference capture is explicitly requested with std::ref or boost::ref.</p>
<p>It supports arbitrary callables including member functions, function objects, and free functions, and all variations thereof. Anything that you can pass to the first argument of bind should be diagnosable. Currently, the only known case where a fix-it is unsupported is when the same placeholder is specified multiple times in the parameter list.</p>
<p>Given:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">int</span> add(<span class="dt">int</span> x, <span class="dt">int</span> y) { <span class="kw">return</span> x + y; }</code></pre></div>
<p>Then:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> f() {
  <span class="dt">int</span> x = <span class="dv">2</span>;
  <span class="kw">auto</span> clj = std::bind(add, x, _1);
}</code></pre></div>
<p>is replaced by:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> f() {
  <span class="dt">int</span> x = <span class="dv">2</span>;
  <span class="kw">auto</span> clj = [=](<span class="kw">auto</span> &amp;&amp; arg1) { <span class="kw">return</span> add(x, arg1); };
}</code></pre></div>
<p>std::bind can be hard to read and can result in larger object files and binaries due to type information that will not be produced by equivalent lambdas.</p>
<h5 id="options-65">Options</h5>
<p>PermissiveParameterList</p>
<p>If the option is set to true, the check will append auto&amp;&amp;... to the end of every placeholder parameter list. Without this, it is possible for a fix-it to perform an incorrect transformation in the case where the result of the bind is used in the context of a type erased functor such as std::function which allows mismatched arguments. For example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">int</span> add(<span class="dt">int</span> x, <span class="dt">int</span> y) { <span class="kw">return</span> x + y; }
<span class="dt">int</span> foo() {
  std::function&lt;<span class="dt">int</span>(<span class="dt">int</span>,<span class="dt">int</span>)&gt; ignore_args = std::bind(add, <span class="dv">2</span>, <span class="dv">2</span>);
  <span class="kw">return</span> ignore_args(<span class="dv">3</span>, <span class="dv">3</span>);
}</code></pre></div>
<p>is valid code, and returns 4. The actual values passed to ignore_args are simply ignored. Without PermissiveParameterList, this would be transformed into</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">int</span> add(<span class="dt">int</span> x, <span class="dt">int</span> y) { <span class="kw">return</span> x + y; }
<span class="dt">int</span> foo() {
  std::function&lt;<span class="dt">int</span>(<span class="dt">int</span>,<span class="dt">int</span>)&gt; ignore_args = [] { <span class="kw">return</span> add(<span class="dv">2</span>, <span class="dv">2</span>); }
  <span class="kw">return</span> ignore_args(<span class="dv">3</span>, <span class="dv">3</span>);
}</code></pre></div>
<p>which will <em>not</em> compile, since the lambda does not contain an operator() that that accepts 2 arguments. With permissive parameter list, it instead generates</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">int</span> add(<span class="dt">int</span> x, <span class="dt">int</span> y) { <span class="kw">return</span> x + y; }
<span class="dt">int</span> foo() {
  std::function&lt;<span class="dt">int</span>(<span class="dt">int</span>,<span class="dt">int</span>)&gt; ignore_args = [](<span class="kw">auto</span>&amp;&amp;...) { <span class="kw">return</span> add(<span class="dv">2</span>, <span class="dv">2</span>); }
  <span class="kw">return</span> ignore_args(<span class="dv">3</span>, <span class="dv">3</span>);
}</code></pre></div>
<p>which is correct.</p>
<p>This check requires using C++14 or higher to run.</p>
<p>(Clang-Tidy original name: modernize-avoid-bind)</p>


#### Avoid C Arrays {#CT_MDR_ACA}
<p>cppcoreguidelines-avoid-c-arrays redirects here as an alias for this check.</p>
<p>hicpp-avoid-c-arrays redirects here as an alias for this check.</p>
<p>Finds C-style array types and recommend to use std::array&lt;&gt; / std::vector&lt;&gt;. All types of C arrays are diagnosed.</p>
<p>However, fix-it are potentially dangerous in header files and are therefore not emitted right now.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">int</span> a[] = {<span class="dv">1</span>, <span class="dv">2</span>}; <span class="co">// warning: do not declare C-style arrays, use std::array&lt;&gt; instead</span>

<span class="dt">int</span> b[<span class="dv">1</span>]; <span class="co">// warning: do not declare C-style arrays, use std::array&lt;&gt; instead</span>

<span class="dt">void</span> foo() {
  <span class="dt">int</span> c[b[<span class="dv">0</span>]]; <span class="co">// warning: do not declare C VLA arrays, use std::vector&lt;&gt; instead</span>
}

<span class="kw">template</span> &lt;<span class="kw">typename</span> T, <span class="dt">int</span> Size&gt;
<span class="kw">class</span> array {
  T d[Size]; <span class="co">// warning: do not declare C-style arrays, use std::array&lt;&gt; instead</span>

  <span class="dt">int</span> e[<span class="dv">1</span>]; <span class="co">// warning: do not declare C-style arrays, use std::array&lt;&gt; instead</span>
};

array&lt;<span class="dt">int</span>[<span class="dv">4</span>], <span class="dv">2</span>&gt; d; <span class="co">// warning: do not declare C-style arrays, use std::array&lt;&gt; instead</span>

<span class="kw">using</span> k = <span class="dt">int</span>[<span class="dv">4</span>]; <span class="co">// warning: do not declare C-style arrays, use std::array&lt;&gt; instead</span></code></pre></div>
<p>However, the extern &quot;C&quot; code is ignored, since it is common to share such headers between C code, and C++ code.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// Some header</span>
<span class="dt">extern</span> <span class="st">&quot;C&quot;</span> {

<span class="dt">int</span> f[] = {<span class="dv">1</span>, <span class="dv">2</span>}; <span class="co">// not diagnosed</span>

<span class="dt">int</span> j[<span class="dv">1</span>]; <span class="co">// not diagnosed</span>

<span class="kw">inline</span> <span class="dt">void</span> bar() {
  {
    <span class="dt">int</span> j[j[<span class="dv">0</span>]]; <span class="co">// not diagnosed</span>
  }
}

}</code></pre></div>
<p>Similarly, the main() function is ignored. Its second and third parameters can be either char* argv[] or char** argv, but can not be std::array&lt;&gt;.</p>
<p>(Clang-Tidy original name: modernize-avoid-c-arrays)</p>


#### Concat Nested Namespaces {#CT_MDR_CNN}
<p>Checks for use of nested namespaces such as namespace a { namespace b { ... } } and suggests changing to the more concise syntax introduced in C++17: namespace a::b { ... }. Inline namespaces are not modified.</p>
<p>For example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">namespace</span> n1 {
<span class="kw">namespace</span> n2 {
<span class="dt">void</span> t();
}
}

<span class="kw">namespace</span> n3 {
<span class="kw">namespace</span> n4 {
<span class="kw">namespace</span> n5 {
<span class="dt">void</span> t();
}
}
<span class="kw">namespace</span> n6 {
<span class="kw">namespace</span> n7 {
<span class="dt">void</span> t();
}
}
}</code></pre></div>
<p>Will be modified to:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">namespace</span> n1::n2 {
<span class="dt">void</span> t();
}

<span class="kw">namespace</span> n3 {
<span class="kw">namespace</span> n4::n5 {
<span class="dt">void</span> t();
}
<span class="kw">namespace</span> n6::n7 {
<span class="dt">void</span> t();
}
}</code></pre></div>
<p>(Clang-Tidy original name: modernize-concat-nested-namespaces)</p>


#### Deprecated Headers {#CT_MDR_DH}
<p>Some headers from C library were deprecated in C++ and are no longer welcome in C++ codebases. Some have no effect in C++. For more details refer to the C++ 14 Standard [depr.c.headers] section.</p>
<p>This check replaces C standard library headers with their C++ alternatives and removes redundant ones.</p>
<p>Important note: the Standard doesn’t guarantee that the C++ headers declare all the same functions in the global namespace. The check in its current form can break the code that uses library symbols from the global namespace.</p>
<ul>
<li><assert.h></li>
<li><complex.h></li>
<li><ctype.h></li>
<li><errno.h></li>
<li><fenv.h> // deprecated since C++11</li>
<li><float.h></li>
<li><inttypes.h></li>
<li><limits.h></li>
<li><locale.h></li>
<li><math.h></li>
<li><setjmp.h></li>
<li><signal.h></li>
<li><stdarg.h></li>
<li><stddef.h></li>
<li><stdint.h></li>
<li><stdio.h></li>
<li><stdlib.h></li>
<li><string.h></li>
<li><tgmath.h> // deprecated since C++11</li>
<li><time.h></li>
<li><uchar.h> // deprecated since C++11</li>
<li><wchar.h></li>
<li><wctype.h></li>
</ul>
<p>If the specified standard is older than C++11 the check will only replace headers deprecated before C++11, otherwise – every header that appeared in the previous list.</p>
<p>These headers don’t have effect in C++:</p>
<ul>
<li><iso646.h></li>
<li><stdalign.h></li>
<li><stdbool.h></li>
</ul>
<p>(Clang-Tidy original name: modernize-deprecated-headers)</p>


#### Deprecated Ios Base Aliases {#CT_MDR_DIBA}
<p>Detects usage of the deprecated member types of std::ios_base and replaces those that have a non-deprecated equivalent.</p>
<p>Deprecated member type | Replacement<br />
---|---<br />
std::ios_base::io_state | std::ios_base::iostate<br />
std::ios_base::open_mode | std::ios_base::openmode<br />
std::ios_base::seek_dir | std::ios_base::seekdir<br />
std::ios_base::streamoff |<br />
std::ios_base::streampos |</p>
<p>(Clang-Tidy original name: modernize-deprecated-ios-base-aliases)</p>


#### Loop Convert {#CT_MDR_LC}
<p>This check converts for(...; ...; ...) loops to use the new range-based loops in C++11.</p>
<p>Three kinds of loops can be converted:</p>
<ul>
<li>Loops over statically allocated arrays.</li>
<li>Loops over containers, using iterators.</li>
<li>Loops over array-like containers, using operator[] and at().</li>
</ul>
<h5 id="minconfidence-option">MinConfidence option</h5>
<h6 id="risky">risky</h6>
<p>In loops where the container expression is more complex than just a reference to a declared expression (a variable, function, enum, etc.), and some part of it appears elsewhere in the loop, we lower our confidence in the transformation due to the increased risk of changing semantics. Transformations for these loops are marked as risky, and thus will only be converted if the minimum required confidence level is set to risky.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">int</span> arr[<span class="dv">10</span>][<span class="dv">20</span>];
<span class="dt">int</span> l = <span class="dv">5</span>;

<span class="kw">for</span> (<span class="dt">int</span> j = <span class="dv">0</span>; j &lt; <span class="dv">20</span>; ++j)
  <span class="dt">int</span> k = arr[l][j] + l; <span class="co">// using l outside arr[l] is considered risky</span>

<span class="kw">for</span> (<span class="dt">int</span> i = <span class="dv">0</span>; i &lt; obj.getVector().size(); ++i)
  obj.foo(<span class="dv">10</span>); <span class="co">// using &#39;obj&#39; is considered risky</span></code></pre></div>
<p>See <a href="#incorrectriskytransformation">Range-based loops evaluate end() only once</a> for an example of an incorrect transformation when the minimum required confidence level is set to risky.</p>
<h6 id="reasonable-default">reasonable (Default)</h6>
<p>If a loop calls .end() or .size() after each iteration, the transformation for that loop is marked as reasonable, and thus will be converted if the required confidence level is set to reasonable (default) or lower.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// using size() is considered reasonable</span>
<span class="kw">for</span> (<span class="dt">int</span> i = <span class="dv">0</span>; i &lt; container.size(); ++i)
  cout &lt;&lt; container[i];</code></pre></div>
<h6 id="safe">safe</h6>
<p>Any other loops that do not match the above criteria to be marked as risky or reasonable are marked safe, and thus will be converted if the required confidence level is set to safe or lower.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">int</span> arr[] = {<span class="dv">1</span>,<span class="dv">2</span>,<span class="dv">3</span>};

<span class="kw">for</span> (<span class="dt">int</span> i = <span class="dv">0</span>; i &lt; <span class="dv">3</span>; ++i)
  cout &lt;&lt; arr[i];</code></pre></div>
<h5 id="example-8">Example</h5>
<p>Original:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">const</span> <span class="dt">int</span> N = <span class="dv">5</span>;
<span class="dt">int</span> arr[] = {<span class="dv">1</span>,<span class="dv">2</span>,<span class="dv">3</span>,<span class="dv">4</span>,<span class="dv">5</span>};
vector&lt;<span class="dt">int</span>&gt; v;
v.push_back(<span class="dv">1</span>);
v.push_back(<span class="dv">2</span>);
v.push_back(<span class="dv">3</span>);

<span class="co">// safe conversion</span>
<span class="kw">for</span> (<span class="dt">int</span> i = <span class="dv">0</span>; i &lt; N; ++i)
  cout &lt;&lt; arr[i];

<span class="co">// reasonable conversion</span>
<span class="kw">for</span> (vector&lt;<span class="dt">int</span>&gt;::iterator it = v.begin(); it != v.end(); ++it)
  cout &lt;&lt; *it;

<span class="co">// reasonable conversion</span>
<span class="kw">for</span> (<span class="dt">int</span> i = <span class="dv">0</span>; i &lt; v.size(); ++i)
  cout &lt;&lt; v[i];</code></pre></div>
<p>After applying the check with minimum confidence level set to reasonable (default):</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">const</span> <span class="dt">int</span> N = <span class="dv">5</span>;
<span class="dt">int</span> arr[] = {<span class="dv">1</span>,<span class="dv">2</span>,<span class="dv">3</span>,<span class="dv">4</span>,<span class="dv">5</span>};
vector&lt;<span class="dt">int</span>&gt; v;
v.push_back(<span class="dv">1</span>);
v.push_back(<span class="dv">2</span>);
v.push_back(<span class="dv">3</span>);

<span class="co">// safe conversion</span>
<span class="kw">for</span> (<span class="kw">auto</span> &amp; elem : arr)
  cout &lt;&lt; elem;

<span class="co">// reasonable conversion</span>
<span class="kw">for</span> (<span class="kw">auto</span> &amp; elem : v)
  cout &lt;&lt; elem;

<span class="co">// reasonable conversion</span>
<span class="kw">for</span> (<span class="kw">auto</span> &amp; elem : v)
  cout &lt;&lt; elem;</code></pre></div>
<h5 id="reverse-iterator-support">Reverse Iterator Support</h5>
<p>The converter is also capable of transforming iterator loops which use rbegin and rend for looping backwards over a container. Out of the box this will automatically happen in C++20 mode using the ranges library, however the check can be configured to work without C++20 by specifying a function to reverse a range and optionally the header file where that function lives.</p>
<p>UseCxx20ReverseRanges</p>
<p>When set to true convert loops when in C++20 or later mode using std::ranges::reverse_view. Default value is true.</p>
<p>MakeReverseRangeFunction</p>
<p>Specify the function used to reverse an iterator pair, the function should accept a class with rbegin and rend methods and return a class with begin and end methods methods that call the rbegin and rend methods respectively. Common examples are ranges::reverse_view and llvm::reverse. Default value is an empty string.</p>
<p>MakeReverseRangeHeader</p>
<p>Specifies the header file where <a href="#cmdoption-arg-makereverserangefunction">MakeReverseRangeFunction</a> is declared. For the previous examples this option would be set to range/v3/view/reverse.hpp and llvm/ADT/STLExtras.h respectively. If this is an empty string and <a href="#cmdoption-arg-makereverserangefunction">MakeReverseRangeFunction</a> is set, the check will proceed on the assumption that the function is already available in the translation unit. This can be wrapped in angle brackets to signify to add the include as a system include. Default value is an empty string.</p>
<p>IncludeStyle</p>
<p>A string specifying which include-style is used, llvm or google. Default is llvm.</p>
<h5 id="limitations-3">Limitations</h5>
<p>There are certain situations where the tool may erroneously perform transformations that remove information and change semantics. Users of the tool should be aware of the behaviour and limitations of the check outlined by the cases below.</p>
<h6 id="comments-inside-loop-headers">Comments inside loop headers</h6>
<p>Comments inside the original loop header are ignored and deleted when transformed.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">for</span> (<span class="dt">int</span> i = <span class="dv">0</span>; i &lt; N; <span class="co">/* This will be deleted */</span> ++i) { }</code></pre></div>
<h6 id="range-based-loops-evaluate-end-only-once">Range-based loops evaluate end() only once</h6>
<p>The C++11 range-based for loop calls .end() only once during the initialization of the loop. If in the original loop .end() is called after each iteration the semantics of the transformed loop may differ.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// The following is semantically equivalent to the C++11 range-based for loop,</span>
<span class="co">// therefore the semantics of the header will not change.</span>
<span class="kw">for</span> (iterator it = container.begin(), e = container.end(); it != e; ++it) { }

<span class="co">// Instead of calling .end() after each iteration, this loop will be</span>
<span class="co">// transformed to call .end() only once during the initialization of the loop,</span>
<span class="co">// which may affect semantics.</span>
<span class="kw">for</span> (iterator it = container.begin(); it != container.end(); ++it) { }</code></pre></div>
<p>As explained above, calling member functions of the container in the body of the loop is considered risky. If the called member function modifies the container the semantics of the converted loop will differ due to .end() being called only once.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">bool</span> flag = <span class="kw">false</span>;
<span class="kw">for</span> (vector&lt;T&gt;::iterator it = vec.begin(); it != vec.end(); ++it) {
  <span class="co">// Add a copy of the first element to the end of the vector.</span>
  <span class="kw">if</span> (!flag) {
    <span class="co">// This line makes this transformation &#39;risky&#39;.</span>
    vec.push_back(*it);
    flag = <span class="kw">true</span>;
  }
  cout &lt;&lt; *it;
}</code></pre></div>
<p>The original code above prints out the contents of the container including the newly added element while the converted loop, shown below, will only print the original contents and not the newly added element.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">bool</span> flag = <span class="kw">false</span>;
<span class="kw">for</span> (<span class="kw">auto</span> &amp; elem : vec) {
  <span class="co">// Add a copy of the first element to the end of the vector.</span>
  <span class="kw">if</span> (!flag) {
    <span class="co">// This line makes this transformation &#39;risky&#39;</span>
    vec.push_back(elem);
    flag = <span class="kw">true</span>;
  }
  cout &lt;&lt; elem;
}</code></pre></div>
<p>Semantics will also be affected if .end() has side effects. For example, in the case where calls to .end() are logged the semantics will change in the transformed loop if .end() was originally called after each iteration.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">iterator end() {
  num_of_end_calls++;
  <span class="kw">return</span> container.end();
}</code></pre></div>
<h6 id="overloaded-operator--with-side-effects">Overloaded operator-&gt;() with side effects</h6>
<p>Similarly, if operator-&gt;() was overloaded to have side effects, such as logging, the semantics will change. If the iterator’s operator-&gt;() was used in the original loop it will be replaced with <container element>.<member> instead due to the implicit dereference as part of the range-based for loop. Therefore any side effect of the overloaded operator-&gt;() will no longer be performed.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">for</span> (iterator it = c.begin(); it != c.end(); ++it) {
  it-&gt;func(); <span class="co">// Using operator-&gt;()</span>
}
<span class="co">// Will be transformed to:</span>
<span class="kw">for</span> (<span class="kw">auto</span> &amp; elem : c) {
  elem.func(); <span class="co">// No longer using operator-&gt;()</span>
}</code></pre></div>
<h6 id="pointers-and-references-to-containers">Pointers and references to containers</h6>
<p>While most of the check’s risk analysis is dedicated to determining whether the iterator or container was modified within the loop, it is possible to circumvent the analysis by accessing and modifying the container through a pointer or reference.</p>
<p>If the container were directly used instead of using the pointer or reference the following transformation would have only been applied at the risky level since calling a member function of the container is considered risky. The check cannot identify expressions associated with the container that are different than the one used in the loop header, therefore the transformation below ends up being performed at the safe level.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">vector&lt;<span class="dt">int</span>&gt; vec;

vector&lt;<span class="dt">int</span>&gt; *ptr = &amp;vec;
vector&lt;<span class="dt">int</span>&gt; &amp;ref = vec;

<span class="kw">for</span> (vector&lt;<span class="dt">int</span>&gt;::iterator it = vec.begin(), e = vec.end(); it != e; ++it) {
  <span class="kw">if</span> (!flag) {
    <span class="co">// Accessing and modifying the container is considered risky, but the risk</span>
    <span class="co">// level is not raised here.</span>
    ptr-&gt;push_back(*it);
    ref.push_back(*it);
    flag = <span class="kw">true</span>;
  }
}</code></pre></div>
<h6 id="openmp">OpenMP</h6>
<p>As range-based for loops are only available since OpenMP 5, this check should not been used on code with a compatibility requirements of OpenMP prior to version 5. It is <strong>intentional</strong> that this check does not make any attempts to exclude incorrect diagnostics on OpenMP for loops prior to OpenMP 5.</p>
<p>To prevent this check to be applied (and to break) OpenMP for loops but still be applied to non-OpenMP for loops the usage of NOLINT (see <a href="../index.html#clang-tidy-nolint">Suppressing Undesired Diagnostics</a>) on the specific for loops is recommended.</p>
<p>(Clang-Tidy original name: modernize-loop-convert)</p>


#### Make Shared {#CT_MDR_MS}
<p>This check finds the creation of std::shared_ptr objects by explicitly calling the constructor and a new expression, and replaces it with a call to std::make_shared.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">auto</span> my_ptr = std::shared_ptr&lt;MyPair&gt;(<span class="kw">new</span> MyPair(<span class="dv">1</span>, <span class="dv">2</span>));

<span class="co">// becomes</span>

<span class="kw">auto</span> my_ptr = std::make_shared&lt;MyPair&gt;(<span class="dv">1</span>, <span class="dv">2</span>);</code></pre></div>
<p>This check also finds calls to std::shared_ptr::reset() with a new expression, and replaces it with a call to std::make_shared.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">my_ptr.reset(<span class="kw">new</span> MyPair(<span class="dv">1</span>, <span class="dv">2</span>));

<span class="co">// becomes</span>

my_ptr = std::make_shared&lt;MyPair&gt;(<span class="dv">1</span>, <span class="dv">2</span>);</code></pre></div>
<h5 id="options-36">Options</h5>
<p>MakeSmartPtrFunction</p>
<p>A string specifying the name of make-shared-ptr function. Default is std::make_shared.</p>
<p>MakeSmartPtrFunctionHeader</p>
<p>A string specifying the corresponding header of make-shared-ptr function. Default is memory.</p>
<p>IncludeStyle</p>
<p>A string specifying which include-style is used, llvm or google. Default is llvm.</p>
<p>IgnoreMacros</p>
<p>If set to true, the check will not give warnings inside macros. Default is true.</p>
<p>IgnoreDefaultInitialization</p>
<p>If set to non-zero, the check does not suggest edits that will transform default initialization into value initialization, as this can cause performance regressions. Default is 1.</p>
<p>(Clang-Tidy original name: modernize-make-shared)</p>


#### Make Unique {#CT_MDR_MU}
<p>This check finds the creation of std::unique_ptr objects by explicitly calling the constructor and a new expression, and replaces it with a call to std::make_unique, introduced in C++14.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">auto</span> my_ptr = std::unique_ptr&lt;MyPair&gt;(<span class="kw">new</span> MyPair(<span class="dv">1</span>, <span class="dv">2</span>));

<span class="co">// becomes</span>

<span class="kw">auto</span> my_ptr = std::make_unique&lt;MyPair&gt;(<span class="dv">1</span>, <span class="dv">2</span>);</code></pre></div>
<p>This check also finds calls to std::unique_ptr::reset() with a new expression, and replaces it with a call to std::make_unique.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">my_ptr.reset(<span class="kw">new</span> MyPair(<span class="dv">1</span>, <span class="dv">2</span>));

<span class="co">// becomes</span>

my_ptr = std::make_unique&lt;MyPair&gt;(<span class="dv">1</span>, <span class="dv">2</span>);</code></pre></div>
<h5 id="options-47">Options</h5>
<p>MakeSmartPtrFunction</p>
<p>A string specifying the name of make-unique-ptr function. Default is std::make_unique.</p>
<p>MakeSmartPtrFunctionHeader</p>
<p>A string specifying the corresponding header of make-unique-ptr function. Default is <memory>.</p>
<p>IncludeStyle</p>
<p>A string specifying which include-style is used, llvm or google. Default is llvm.</p>
<p>IgnoreMacros</p>
<p>If set to true, the check will not give warnings inside macros. Default is true.</p>
<p>IgnoreDefaultInitialization</p>
<p>If set to non-zero, the check does not suggest edits that will transform default initialization into value initialization, as this can cause performance regressions. Default is 1.</p>
<p>(Clang-Tidy original name: modernize-make-unique)</p>


#### Pass By Value {#CT_MDR_PBV}
<p>With move semantics added to the language and the standard library updated with move constructors added for many types it is now interesting to take an argument directly by value, instead of by const-reference, and then copy. This check allows the compiler to take care of choosing the best way to construct the copy.</p>
<p>The transformation is usually beneficial when the calling code passes an <em>rvalue</em> and assumes the move construction is a cheap operation. This short example illustrates how the construction of the value happens:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> foo(std::string s);
std::string get_str();

<span class="dt">void</span> f(<span class="dt">const</span> std::string &amp;str) {
  foo(str);       <span class="co">// lvalue  -&gt; copy construction</span>
  foo(get_str()); <span class="co">// prvalue -&gt; move construction</span>
}</code></pre></div>
<p>Note</p>
<p>Currently, only constructors are transformed to make use of pass-by-value. Contributions that handle other situations are welcome!</p>
<h5 id="pass-by-value-in-constructors">Pass-by-value in constructors</h5>
<p>Replaces the uses of const-references constructor parameters that are copied into class fields. The parameter is then moved with std::move().</p>
<p>Since std::move() is a library function declared in <utility> it may be necessary to add this include. The check will add the include directive when necessary.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"> <span class="ot">#include &lt;string&gt;</span>

 <span class="kw">class</span> Foo {
 <span class="kw">public</span>:
-  Foo(<span class="dt">const</span> std::string &amp;Copied, <span class="dt">const</span> std::string &amp;ReadOnly)
-    : Copied(Copied), ReadOnly(ReadOnly)
+  Foo(std::string Copied, <span class="dt">const</span> std::string &amp;ReadOnly)
+    : Copied(std::move(Copied)), ReadOnly(ReadOnly)
   {}

 <span class="kw">private</span>:
   std::string Copied;
   <span class="dt">const</span> std::string &amp;ReadOnly;
 };

 std::string get_cwd();

 <span class="dt">void</span> f(<span class="dt">const</span> std::string &amp;Path) {
   <span class="co">// The parameter corresponding to &#39;get_cwd()&#39; is move-constructed. By</span>
   <span class="co">// using pass-by-value in the Foo constructor we managed to avoid a</span>
   <span class="co">// copy-construction.</span>
   Foo foo(get_cwd(), Path);
 }</code></pre></div>
<p>If the parameter is used more than once no transformation is performed since moved objects have an undefined state. It means the following code will be left untouched:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="ot">#include &lt;string&gt;</span>

<span class="dt">void</span> pass(<span class="dt">const</span> std::string &amp;S);

<span class="kw">struct</span> Foo {
  Foo(<span class="dt">const</span> std::string &amp;S) : Str(S) {
    pass(S);
  }

  std::string Str;
};</code></pre></div>
<h6 id="known-limitations">Known limitations</h6>
<p>A situation where the generated code can be wrong is when the object referenced is modified before the assignment in the init-list through a “hidden” reference.</p>
<p>Example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"> std::string s(<span class="st">&quot;foo&quot;</span>);

 <span class="kw">struct</span> Base {
   Base() {
     s = <span class="st">&quot;bar&quot;</span>;
   }
 };

 <span class="kw">struct</span> Derived : Base {
-  Derived(<span class="dt">const</span> std::string &amp;S) : Field(S)
+  Derived(std::string S) : Field(std::move(S))
   { }

   std::string Field;
 };

 <span class="dt">void</span> f() {
-  Derived d(s); <span class="co">// d.Field holds &quot;bar&quot;</span>
+  Derived d(s); <span class="co">// d.Field holds &quot;foo&quot;</span>
 }</code></pre></div>
<h6 id="note-about-delayed-template-parsing">Note about delayed template parsing</h6>
<p>When delayed template parsing is enabled, constructors part of templated contexts; templated constructors, constructors in class templates, constructors of inner classes of template classes, etc., are not transformed. Delayed template parsing is enabled by default on Windows as a Microsoft extension: <a href="https://clang.llvm.org/docs/UsersManual.html#microsoft-extensions">Clang Compiler User’s Manual - Microsoft extensions</a>.</p>
<p>Delayed template parsing can be enabled using the -fdelayed-template-parsing flag and disabled using -fno-delayed-template-parsing.</p>
<p>Example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">  <span class="kw">template</span> &lt;<span class="kw">typename</span> T&gt; <span class="kw">class</span> C {
    std::string S;

  <span class="kw">public</span>:
=  <span class="co">// using -fdelayed-template-parsing (default on Windows)</span>
=  C(<span class="dt">const</span> std::string &amp;S) : S(S) {}

+  <span class="co">// using -fno-delayed-template-parsing (default on non-Windows systems)</span>
+  C(std::string S) : S(std::move(S)) {}
  };</code></pre></div>
<p>See also</p>
<p>For more information about the pass-by-value idiom, read: <a href="https://web.archive.org/web/20140205194657/http://cpp-next.com/archive/2009/08/want-speed-pass-by-value/">Want Speed? Pass by Value</a>.</p>
<h5 id="options-13">Options</h5>
<p>IncludeStyle</p>
<p>A string specifying which include-style is used, llvm or google. Default is llvm.</p>
<p>ValuesOnly</p>
<p>When true, the check only warns about copied parameters that are already passed by value. Default is false.</p>
<p>(Clang-Tidy original name: modernize-pass-by-value)</p>


#### Raw String Literal {#CT_MDR_RSL}
<p>This check selectively replaces string literals containing escaped characters with raw string literals.</p>
<p>Example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">const</span> <span class="dt">char</span> *<span class="dt">const</span> Quotes{<span class="st">&quot;embedded </span><span class="ch">\&quot;</span><span class="st">quotes</span><span class="ch">\&quot;</span><span class="st">&quot;</span>};
<span class="dt">const</span> <span class="dt">char</span> *<span class="dt">const</span> Paragraph{<span class="st">&quot;Line one.</span><span class="ch">\n</span><span class="st">Line two.</span><span class="ch">\n</span><span class="st">Line three.</span><span class="ch">\n</span><span class="st">&quot;</span>};
<span class="dt">const</span> <span class="dt">char</span> *<span class="dt">const</span> SingleLine{<span class="st">&quot;Single line.</span><span class="ch">\n</span><span class="st">&quot;</span>};
<span class="dt">const</span> <span class="dt">char</span> *<span class="dt">const</span> TrailingSpace{<span class="st">&quot;Look here -&gt; </span><span class="ch">\n</span><span class="st">&quot;</span>};
<span class="dt">const</span> <span class="dt">char</span> *<span class="dt">const</span> Tab{<span class="st">&quot;One</span><span class="ch">\t</span><span class="st">Two</span><span class="ch">\n</span><span class="st">&quot;</span>};
<span class="dt">const</span> <span class="dt">char</span> *<span class="dt">const</span> Bell{<span class="st">&quot;Hello!</span><span class="ch">\a</span><span class="st">  And welcome!&quot;</span>};
<span class="dt">const</span> <span class="dt">char</span> *<span class="dt">const</span> Path{<span class="st">&quot;C:</span><span class="ch">\\</span><span class="st">Program Files</span><span class="ch">\\</span><span class="st">Vendor</span><span class="ch">\\</span><span class="st">Application.exe&quot;</span>};
<span class="dt">const</span> <span class="dt">char</span> *<span class="dt">const</span> RegEx{<span class="st">&quot;</span><span class="ch">\\</span><span class="st">w</span><span class="ch">\\</span><span class="st">([a-z]</span><span class="ch">\\</span><span class="st">)&quot;</span>};</code></pre></div>
<p>becomes</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">const</span> <span class="dt">char</span> *<span class="dt">const</span> Quotes{<span class="st">R&quot;(embedded &quot;quotes&quot;)&quot;};</span>
<span class="st">const char *const Paragraph{&quot;Line one.\nLine two.\nLine three.\n&quot;};</span>
<span class="st">const char *const SingleLine{&quot;Single line.\n&quot;};</span>
<span class="st">const char *const TrailingSpace{&quot;Look here -&gt; \n&quot;};</span>
<span class="st">const char *const Tab{&quot;One\tTwo\n&quot;};</span>
<span class="st">const char *const Bell{&quot;Hello!\a  And welcome!&quot;};</span>
<span class="st">const char *const Path{R&quot;(C:\Program Files\Vendor\Application.exe)&quot;};</span>
<span class="st">const char *const RegEx{R&quot;(\w\([a-z]\))&quot;};</span></code></pre></div>
<p>The presence of any of the following escapes can cause the string to be converted to a raw string literal: \, ', &quot;, ?, and octal or hexadecimal escapes for printable ASCII characters.</p>
<p>A string literal containing only escaped newlines is a common way of writing lines of text output. Introducing physical newlines with raw string literals in this case is likely to impede readability. These string literals are left unchanged.</p>
<p>An escaped horizontal tab, form feed, or vertical tab prevents the string literal from being converted. The presence of a horizontal tab, form feed or vertical tab in source code is not visually obvious.</p>
<p>(Clang-Tidy original name: modernize-raw-string-literal)</p>


#### Redundant Void Arg {#CT_MDR_RVA}
<p>Find and remove redundant void argument lists.</p>
<p>Examples: Initial code | Code with applied fixes<br />
---|---<br />
int f(void); | int f();<br />
int (<em>f(void))(void); | int (</em>f())();<br />
typedef int (<em>f_t(void))(void); | typedef int (</em>f_t())();<br />
void (C::<em>p)(void); | void (C::</em>p)();<br />
C::C(void) {} | C::C() {}<br />
C::~C(void) {} | C::~C() {}</p>
<p>(Clang-Tidy original name: modernize-redundant-void-arg)</p>


#### Replace Auto Ptr {#CT_MDR_RAP}
<p>This check replaces the uses of the deprecated class std::auto_ptr by std::unique_ptr (introduced in C++11). The transfer of ownership, done by the copy-constructor and the assignment operator, is changed to match std::unique_ptr usage by using explicit calls to std::move().</p>
<p>Migration example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">-<span class="dt">void</span> take_ownership_fn(std::auto_ptr&lt;<span class="dt">int</span>&gt; int_ptr);
+<span class="dt">void</span> take_ownership_fn(std::unique_ptr&lt;<span class="dt">int</span>&gt; int_ptr);

 <span class="dt">void</span> f(<span class="dt">int</span> x) {
-  std::auto_ptr&lt;<span class="dt">int</span>&gt; a(<span class="kw">new</span> <span class="dt">int</span>(x));
-  std::auto_ptr&lt;<span class="dt">int</span>&gt; b;
+  std::unique_ptr&lt;<span class="dt">int</span>&gt; a(<span class="kw">new</span> <span class="dt">int</span>(x));
+  std::unique_ptr&lt;<span class="dt">int</span>&gt; b;

-  b = a;
-  take_ownership_fn(b);
+  b = std::move(a);
+  take_ownership_fn(std::move(b));
 }</code></pre></div>
<p>Since std::move() is a library function declared in <utility> it may be necessary to add this include. The check will add the include directive when necessary.</p>
<h5 id="known-limitations-5">Known Limitations</h5>
<ul>
<li>If headers modification is not activated or if a header is not allowed to be changed this check will produce broken code (compilation error), where the headers’ code will stay unchanged while the code using them will be changed.</li>
<li>Client code that declares a reference to an std::auto_ptr coming from code that can’t be migrated (such as a header coming from a 3rd party library) will produce a compilation error after migration. This is because the type of the reference will be changed to std::unique_ptr but the type returned by the library won’t change, binding a reference to std::unique_ptr from an std::auto_ptr. This pattern doesn’t make much sense and usually std::auto_ptr are stored by value (otherwise what is the point in using them instead of a reference or a pointer?).</li>
</ul>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"> <span class="co">// &lt;3rd-party header...&gt;</span>
 std::auto_ptr&lt;<span class="dt">int</span>&gt; get_value();
 <span class="dt">const</span> std::auto_ptr&lt;<span class="dt">int</span>&gt; &amp; get_ref();

 <span class="co">// &lt;calling code (with migration)...&gt;</span>
-std::auto_ptr&lt;<span class="dt">int</span>&gt; a(get_value());
+std::unique_ptr&lt;<span class="dt">int</span>&gt; a(get_value()); <span class="co">// ok, unique_ptr constructed from auto_ptr</span>

-<span class="dt">const</span> std::auto_ptr&lt;<span class="dt">int</span>&gt; &amp; p = get_ptr();
+<span class="dt">const</span> std::unique_ptr&lt;<span class="dt">int</span>&gt; &amp; p = get_ptr(); <span class="co">// won&#39;t compile</span></code></pre></div>
<ul>
<li>Non-instantiated templates aren’t modified.</li>
</ul>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">template</span> &lt;<span class="kw">typename</span> X&gt;
<span class="dt">void</span> f() {
    std::auto_ptr&lt;X&gt; p;
}

<span class="co">// only &#39;f&lt;int&gt;()&#39; (or similar) will trigger the replacement.</span></code></pre></div>
<h5 id="options-69">Options</h5>
<p>IncludeStyle</p>
<p>A string specifying which include-style is used, llvm or google. Default is llvm.</p>
<p>(Clang-Tidy original name: modernize-replace-auto-ptr)</p>


#### Replace Disallow Copy And Assign Macro {#CT_MDR_RDCAAM}
<p>Finds macro expansions of DISALLOW_COPY_AND_ASSIGN(Type) and replaces them with a deleted copy constructor and a deleted assignment operator.</p>
<p>Before the delete keyword was introduced in C++11 it was common practice to declare a copy constructor and an assignment operator as a private members. This effectively makes them unusable to the public API of a class.</p>
<p>With the advent of the delete keyword in C++11 we can abandon the private access of the copy constructor and the assignment operator and delete the methods entirely.</p>
<p>When running this check on a code like this:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> Foo {
<span class="kw">private</span>:
  DISALLOW_COPY_AND_ASSIGN(Foo);
};</code></pre></div>
<p>It will be transformed to this:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> Foo {
<span class="kw">private</span>:
  Foo(<span class="dt">const</span> Foo &amp;) = <span class="kw">delete</span>;
  <span class="dt">const</span> Foo &amp;<span class="kw">operator</span>=(<span class="dt">const</span> Foo &amp;) = <span class="kw">delete</span>;
};</code></pre></div>
<h5 id="known-limitations-1">Known Limitations</h5>
<ul>
<li>Notice that the migration example above leaves the private access specification untouched. You might want to run the check <a href="modernize-use-equals-delete.html">modernize-use-equals-delete</a> to get warnings for deleted functions in private sections.</li>
</ul>
<h5 id="options-19">Options</h5>
<p>MacroName</p>
<p>A string specifying the macro name whose expansion will be replaced. Default is DISALLOW_COPY_AND_ASSIGN.</p>
<p>See: <a href="https://en.cppreference.com/w/cpp/language/function\#Deleted_functions" class="uri">https://en.cppreference.com/w/cpp/language/function\#Deleted_functions</a></p>
<p>(Clang-Tidy original name: modernize-replace-disallow-copy-and-assign-macro)</p>


#### Replace Random Shuffle {#CT_MDR_RRS}
<p>This check will find occurrences of std::random_shuffle and replace it with std::shuffle. In C++17 std::random_shuffle will no longer be available and thus we need to replace it.</p>
<p>Below are two examples of what kind of occurrences will be found and two examples of what it will be replaced with.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::vector&lt;<span class="dt">int</span>&gt; v;

<span class="co">// First example</span>
std::random_shuffle(vec.begin(), vec.end());

<span class="co">// Second example</span>
std::random_shuffle(vec.begin(), vec.end(), randomFunc);</code></pre></div>
<p>Both of these examples will be replaced with:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::shuffle(vec.begin(), vec.end(), std::mt19937(std::random_device()()));</code></pre></div>
<p>The second example will also receive a warning that randomFunc is no longer supported in the same way as before so if the user wants the same functionality, the user will need to change the implementation of the randomFunc.</p>
<p>One thing to be aware of here is that std::random_device is quite expensive to initialize. So if you are using the code in a performance critical place, you probably want to initialize it elsewhere. Another thing is that the seeding quality of the suggested fix is quite poor: std::mt19937 has an internal state of 624 32-bit integers, but is only seeded with a single integer. So if you require higher quality randomness, you should consider seeding better, for example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::shuffle(v.begin(), v.end(), []() {
  std::mt19937::result_type seeds[std::mt19937::state_size];
  std::random_device device;
  std::uniform_int_distribution&lt;<span class="kw">typename</span> std::mt19937::result_type&gt; dist;
  std::generate(std::begin(seeds), std::end(seeds), [&amp;] { <span class="kw">return</span> dist(device); });
  std::seed_seq seq(std::begin(seeds), std::end(seeds));
  <span class="kw">return</span> std::mt19937(seq);
}());</code></pre></div>
<p>(Clang-Tidy original name: modernize-replace-random-shuffle)</p>


#### Return Braced Init List {#CT_MDR_RBIL}
<p>Replaces explicit calls to the constructor in a return with a braced initializer list. This way the return type is not needlessly duplicated in the function definition and the return statement.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">Foo bar() {
  Baz baz;
  <span class="kw">return</span> Foo(baz);
}

<span class="co">// transforms to:</span>

Foo bar() {
  Baz baz;
  <span class="kw">return</span> {baz};
}</code></pre></div>
<p>(Clang-Tidy original name: modernize-return-braced-init-list)</p>


#### Shrink To Fit {#CT_MDR_STF}
<p>Replace copy and swap tricks on shrinkable containers with the shrink_to_fit() method call.</p>
<p>The shrink_to_fit() method is more readable and more effective than the copy and swap trick to reduce the capacity of a shrinkable container. Note that, the shrink_to_fit() method is only available in C++11 and up.</p>
<p>(Clang-Tidy original name: modernize-shrink-to-fit)</p>


#### Unary Static Assert {#CT_MDR_USA}
<p>The check diagnoses any static_assert declaration with an empty string literal and provides a fix-it to replace the declaration with a single-argument static_assert declaration.</p>
<p>The check is only applicable for C++17 and later code.</p>
<p>The following code:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> f_textless(<span class="dt">int</span> a) {
  <span class="kw">static_assert</span>(<span class="kw">sizeof</span>(a) &lt;= <span class="dv">10</span>, <span class="st">&quot;&quot;</span>);
}</code></pre></div>
<p>is replaced by:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> f_textless(<span class="dt">int</span> a) {
  <span class="kw">static_assert</span>(<span class="kw">sizeof</span>(a) &lt;= <span class="dv">10</span>);
}</code></pre></div>
<p>(Clang-Tidy original name: modernize-unary-static-assert)</p>


#### Use Auto {#CT_MDR_UA}
<p>This check is responsible for using the auto type specifier for variable declarations to <em>improve code readability and maintainability</em>. For example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::vector&lt;<span class="dt">int</span>&gt;::iterator I = my_container.begin();

<span class="co">// transforms to:</span>

<span class="kw">auto</span> I = my_container.begin();</code></pre></div>
<p>The auto type specifier will only be introduced in situations where the variable type matches the type of the initializer expression. In other words auto should deduce the same type that was originally spelled in the source. However, not every situation should be transformed:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">int</span> val = <span class="dv">42</span>;
InfoStruct &amp;I = SomeObject.getInfo();

<span class="co">// Should not become:</span>

<span class="kw">auto</span> val = <span class="dv">42</span>;
<span class="kw">auto</span> &amp;I = SomeObject.getInfo();</code></pre></div>
<p>In this example using auto for builtins doesn’t improve readability. In other situations it makes the code less self-documenting impairing readability and maintainability. As a result, auto is used only introduced in specific situations described below.</p>
<h5 id="iterators">Iterators</h5>
<p>Iterator type specifiers tend to be long and used frequently, especially in loop constructs. Since the functions generating iterators have a common format, the type specifier can be replaced without obscuring the meaning of code while improving readability and maintainability.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">for</span> (std::vector&lt;<span class="dt">int</span>&gt;::iterator I = my_container.begin(),
                                E = my_container.end();
     I != E; ++I) {
}

<span class="co">// becomes</span>

<span class="kw">for</span> (<span class="kw">auto</span> I = my_container.begin(), E = my_container.end(); I != E; ++I) {
}</code></pre></div>
<p>The check will only replace iterator type-specifiers when all of the following conditions are satisfied:</p>
<ul>
<li>The iterator is for one of the standard container in std namespace:
<ul>
<li>array</li>
<li>deque</li>
<li>forward_list</li>
<li>list</li>
<li>vector</li>
<li>map</li>
<li>multimap</li>
<li>set</li>
<li>multiset</li>
<li>unordered_map</li>
<li>unordered_multimap</li>
<li>unordered_set</li>
<li>unordered_multiset</li>
<li>queue</li>
<li>priority_queue</li>
<li>stack</li>
</ul></li>
<li>The iterator is one of the possible iterator types for standard containers:
<ul>
<li>iterator</li>
<li>reverse_iterator</li>
<li>const_iterator</li>
<li>const_reverse_iterator</li>
</ul></li>
<li>In addition to using iterator types directly, typedefs or other ways of referring to those types are also allowed. However, implementation-specific types for which a type like std::vector<int>::iterator is itself a typedef will not be transformed. Consider the following examples:</li>
</ul>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// The following direct uses of iterator types will be transformed.</span>
std::vector&lt;<span class="dt">int</span>&gt;::iterator I = MyVec.begin();
{
  <span class="kw">using</span> <span class="kw">namespace</span> std;
  list&lt;<span class="dt">int</span>&gt;::iterator I = MyList.begin();
}

<span class="co">// The type specifier for J would transform to auto since it&#39;s a typedef</span>
<span class="co">// to a standard iterator type.</span>
<span class="kw">typedef</span> std::map&lt;<span class="dt">int</span>, std::string&gt;::const_iterator map_iterator;
map_iterator J = MyMap.begin();

<span class="co">// The following implementation-specific iterator type for which</span>
<span class="co">// std::vector&lt;int&gt;::iterator could be a typedef would not be transformed.</span>
__gnu_cxx::__normal_iterator&lt;<span class="dt">int</span>*, std::vector&gt; K = MyVec.begin();</code></pre></div>
<ul>
<li>The initializer for the variable being declared is not a braced initializer list. Otherwise, use of auto would cause the type of the variable to be deduced as std::initializer_list.</li>
</ul>
<h5 id="new-expressions">New expressions</h5>
<p>Frequently, when a pointer is declared and initialized with new, the pointee type is written twice: in the declaration type and in the new expression. In this cases, the declaration type can be replaced with auto improving readability and maintainability.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">TypeName *my_pointer = <span class="kw">new</span> TypeName(my_param);

<span class="co">// becomes</span>

<span class="kw">auto</span> *my_pointer = <span class="kw">new</span> TypeName(my_param);</code></pre></div>
<p>The check will also replace the declaration type in multiple declarations, if the following conditions are satisfied:</p>
<ul>
<li>All declared variables have the same type (i.e. all of them are pointers to the same type).</li>
<li>All declared variables are initialized with a new expression.</li>
<li>The types of all the new expressions are the same than the pointee of the declaration type.</li>
</ul>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">TypeName *my_first_pointer = <span class="kw">new</span> TypeName, *my_second_pointer = <span class="kw">new</span> TypeName;

<span class="co">// becomes</span>

<span class="kw">auto</span> *my_first_pointer = <span class="kw">new</span> TypeName, *my_second_pointer = <span class="kw">new</span> TypeName;</code></pre></div>
<h5 id="cast-expressions">Cast expressions</h5>
<p>Frequently, when a variable is declared and initialized with a cast, the variable type is written twice: in the declaration type and in the cast expression. In this cases, the declaration type can be replaced with auto improving readability and maintainability.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">TypeName *my_pointer = <span class="kw">static_cast</span>&lt;TypeName&gt;(my_param);

<span class="co">// becomes</span>

<span class="kw">auto</span> *my_pointer = <span class="kw">static_cast</span>&lt;TypeName&gt;(my_param);</code></pre></div>
<p>The check handles static_cast, dynamic_cast, const_cast, reinterpret_cast, functional casts, C-style casts and function templates that behave as casts, such as llvm::dyn_cast, boost::lexical_cast and gsl::narrow_cast. Calls to function templates are considered to behave as casts if the first template argument is explicit and is a type, and the function returns that type, or a pointer or reference to it.</p>
<h5 id="known-limitations-2">Known Limitations</h5>
<ul>
<li>If the initializer is an explicit conversion constructor, the check will not replace the type specifier even though it would be safe to do so.</li>
<li>User-defined iterators are not handled at this time.</li>
</ul>
<h5 id="options-21">Options</h5>
<p>MinTypeNameLength</p>
<p>If the option is set to non-zero (default 5), the check will ignore type names having a length less than the option value. The option affects expressions only, not iterators. Spaces between multi-lexeme type names (long int) are considered as one. If the <a href="#cmdoption-arg-removestars">RemoveStars</a> option (see below) is set to true, then *s in the type are also counted as a part of the type name.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// MinTypeNameLength = 0, RemoveStars=0</span>

<span class="dt">int</span> a = <span class="kw">static_cast</span>&lt;<span class="dt">int</span>&gt;(foo());            <span class="co">// ---&gt; auto a = ...</span>
<span class="co">// length(bool *) = 4</span>
<span class="dt">bool</span> *b = <span class="kw">new</span> <span class="dt">bool</span>;                         <span class="co">// ---&gt; auto *b = ...</span>
<span class="dt">unsigned</span> c = <span class="kw">static_cast</span>&lt;<span class="dt">unsigned</span>&gt;(foo());  <span class="co">// ---&gt; auto c = ...</span>

<span class="co">// MinTypeNameLength = 5, RemoveStars=0</span>

<span class="dt">int</span> a = <span class="kw">static_cast</span>&lt;<span class="dt">int</span>&gt;(foo());                 <span class="co">// ---&gt; int  a = ...</span>
<span class="dt">bool</span> b = <span class="kw">static_cast</span>&lt;<span class="dt">bool</span>&gt;(foo());               <span class="co">// ---&gt; bool b = ...</span>
<span class="dt">bool</span> *pb = <span class="kw">static_cast</span>&lt;<span class="dt">bool</span>*&gt;(foo());            <span class="co">// ---&gt; bool *pb = ...</span>
<span class="dt">unsigned</span> c = <span class="kw">static_cast</span>&lt;<span class="dt">unsigned</span>&gt;(foo());       <span class="co">// ---&gt; auto c = ...</span>
<span class="co">// length(long &lt;on-or-more-spaces&gt; int) = 8</span>
<span class="dt">long</span> <span class="dt">int</span> d = <span class="kw">static_cast</span>&lt;<span class="dt">long</span> <span class="dt">int</span>&gt;(foo());       <span class="co">// ---&gt; auto d = ...</span>

<span class="co">// MinTypeNameLength = 5, RemoveStars=1</span>

<span class="dt">int</span> a = <span class="kw">static_cast</span>&lt;<span class="dt">int</span>&gt;(foo());                 <span class="co">// ---&gt; int  a = ...</span>
<span class="co">// length(int * * ) = 5</span>
<span class="dt">int</span> **pa = <span class="kw">static_cast</span>&lt;<span class="dt">int</span>**&gt;(foo());            <span class="co">// ---&gt; auto pa = ...</span>
<span class="dt">bool</span> b = <span class="kw">static_cast</span>&lt;<span class="dt">bool</span>&gt;(foo());               <span class="co">// ---&gt; bool b = ...</span>
<span class="dt">bool</span> *pb = <span class="kw">static_cast</span>&lt;<span class="dt">bool</span>*&gt;(foo());            <span class="co">// ---&gt; auto pb = ...</span>
<span class="dt">unsigned</span> c = <span class="kw">static_cast</span>&lt;<span class="dt">unsigned</span>&gt;(foo());       <span class="co">// ---&gt; auto c = ...</span>
<span class="dt">long</span> <span class="dt">int</span> d = <span class="kw">static_cast</span>&lt;<span class="dt">long</span> <span class="dt">int</span>&gt;(foo());       <span class="co">// ---&gt; auto d = ...</span></code></pre></div>
<p>RemoveStars</p>
<p>If the option is set to true (default is false), the check will remove stars from the non-typedef pointer types when replacing type names with auto. Otherwise, the check will leave stars. For example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">TypeName *my_first_pointer = <span class="kw">new</span> TypeName, *my_second_pointer = <span class="kw">new</span> TypeName;

<span class="co">// RemoveStars = 0</span>

<span class="kw">auto</span> *my_first_pointer = <span class="kw">new</span> TypeName, *my_second_pointer = <span class="kw">new</span> TypeName;

<span class="co">// RemoveStars = 1</span>

<span class="kw">auto</span> my_first_pointer = <span class="kw">new</span> TypeName, my_second_pointer = <span class="kw">new</span> TypeName;</code></pre></div>
<p>(Clang-Tidy original name: modernize-use-auto)</p>


#### Use Bool Literals {#CT_MDR_UBL}
<p>Finds integer literals which are cast to bool.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">bool</span> p = <span class="dv">1</span>;
<span class="dt">bool</span> f = <span class="kw">static_cast</span>&lt;<span class="dt">bool</span>&gt;(<span class="dv">1</span>);
std::ios_base::sync_with_stdio(<span class="dv">0</span>);
<span class="dt">bool</span> x = p ? <span class="dv">1</span> : <span class="dv">0</span>;

<span class="co">// transforms to</span>

<span class="dt">bool</span> p = <span class="kw">true</span>;
<span class="dt">bool</span> f = <span class="kw">true</span>;
std::ios_base::sync_with_stdio(<span class="kw">false</span>);
<span class="dt">bool</span> x = p ? <span class="kw">true</span> : <span class="kw">false</span>;</code></pre></div>
<h5 id="options-5">Options</h5>
<p>IgnoreMacros</p>
<p>If set to true, the check will not give warnings inside macros. Default is true.</p>
<p>(Clang-Tidy original name: modernize-use-bool-literals)</p>


#### Use Default Member Init {#CT_MDR_UDMI}
<p>This check converts a default constructor’s member initializers into the new default member initializers in C++11. Other member initializers that match the default member initializer are removed. This can reduce repeated code or allow use of ‘= default’.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">struct</span> A {
  A() : i(<span class="dv">5</span>), j(<span class="fl">10.0</span>) {}
  A(<span class="dt">int</span> i) : i(i), j(<span class="fl">10.0</span>) {}
  <span class="dt">int</span> i;
  <span class="dt">double</span> j;
};

<span class="co">// becomes</span>

<span class="kw">struct</span> A {
  A() {}
  A(<span class="dt">int</span> i) : i(i) {}
  <span class="dt">int</span> i{<span class="dv">5</span>};
  <span class="dt">double</span> j{<span class="fl">10.0</span>};
};</code></pre></div>
<p>Note</p>
<p>Only converts member initializers for built-in types, enums, and pointers. The readability-redundant-member-init check will remove redundant member initializers for classes.</p>
<h5 id="options-25">Options</h5>
<p>UseAssignment</p>
<p>If this option is set to true (default is false), the check will initialise members with an assignment. For example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">struct</span> A {
  A() {}
  A(<span class="dt">int</span> i) : i(i) {}
  <span class="dt">int</span> i = <span class="dv">5</span>;
  <span class="dt">double</span> j = <span class="fl">10.0</span>;
};</code></pre></div>
<p>IgnoreMacros</p>
<p>If this option is set to true (default is true), the check will not warn about members declared inside macros.</p>
<p>(Clang-Tidy original name: modernize-use-default-member-init)</p>


#### Use Emplace {#CT_MDR_UE}
<p>The check flags insertions to an STL-style container done by calling the push_back method with an explicitly-constructed temporary of the container element type. In this case, the corresponding emplace_back method results in less verbose and potentially more efficient code. Right now the check doesn’t support push_front and insert. It also doesn’t support insert functions for associative containers because replacing insert with emplace may result in <a href="https://htmlpreview.github.io/?https://github.com/HowardHinnant/papers/blob/master/insert_vs_emplace.html">speed regression</a>, but it might get support with some addition flag in the future.</p>
<p>By default only std::vector, std::deque, std::list are considered. This list can be modified using the <a href="#cmdoption-arg-containerswithpushback">ContainersWithPushBack</a> option.</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::vector&lt;MyClass&gt; v;
v.push_back(MyClass(<span class="dv">21</span>, <span class="dv">37</span>));

std::vector&lt;std::pair&lt;<span class="dt">int</span>, <span class="dt">int</span>&gt;&gt; w;

w.push_back(std::pair&lt;<span class="dt">int</span>, <span class="dt">int</span>&gt;(<span class="dv">21</span>, <span class="dv">37</span>));
w.push_back(std::make_pair(<span class="dv">21L</span>, <span class="dv">37L</span>));</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::vector&lt;MyClass&gt; v;
v.emplace_back(<span class="dv">21</span>, <span class="dv">37</span>);

std::vector&lt;std::pair&lt;<span class="dt">int</span>, <span class="dt">int</span>&gt;&gt; w;
w.emplace_back(<span class="dv">21</span>, <span class="dv">37</span>);
w.emplace_back(<span class="dv">21L</span>, <span class="dv">37L</span>);</code></pre></div>
<p>By default, the check is able to remove unnecessary std::make_pair and std::make_tuple calls from push_back calls on containers of std::pair and std::tuple. Custom tuple-like types can be modified by the <a href="#cmdoption-arg-tupletypes">TupleTypes</a> option; custom make functions can be modified by the <a href="#cmdoption-arg-tuplemakefunctions">TupleMakeFunctions</a> option.</p>
<p>The other situation is when we pass arguments that will be converted to a type inside a container.</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::vector&lt;boost::optional&lt;std::string&gt; &gt; v;
v.push_back(<span class="st">&quot;abc&quot;</span>);</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::vector&lt;boost::optional&lt;std::string&gt; &gt; v;
v.emplace_back(<span class="st">&quot;abc&quot;</span>);</code></pre></div>
<p>In some cases the transformation would be valid, but the code wouldn’t be exception safe. In this case the calls of push_back won’t be replaced.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::vector&lt;std::unique_ptr&lt;<span class="dt">int</span>&gt;&gt; v;
v.push_back(std::unique_ptr&lt;<span class="dt">int</span>&gt;(<span class="kw">new</span> <span class="dt">int</span>(<span class="dv">0</span>)));
<span class="kw">auto</span> *ptr = <span class="kw">new</span> <span class="dt">int</span>(<span class="dv">1</span>);
v.push_back(std::unique_ptr&lt;<span class="dt">int</span>&gt;(ptr));</code></pre></div>
<p>This is because replacing it with emplace_back could cause a leak of this pointer if emplace_back would throw exception before emplacement (e.g. not enough memory to add a new element).</p>
<p>For more info read item 42 - “Consider emplacement instead of insertion.” of Scott Meyers “Effective Modern C++”.</p>
<p>The default smart pointers that are considered are std::unique_ptr, std::shared_ptr, std::auto_ptr. To specify other smart pointers or other classes use the <a href="#cmdoption-arg-smartpointers">SmartPointers</a> option.</p>
<p>Check also doesn’t fire if any argument of the constructor call would be:</p>
<ul>
<li>a bit-field (bit-fields can’t bind to rvalue/universal reference)</li>
<li>a new expression (to avoid leak)</li>
<li>if the argument would be converted via derived-to-base cast.</li>
</ul>
<p>This check requires C++11 or higher to run.</p>
<h5 id="options">Options</h5>
<p>ContainersWithPushBack</p>
<p>Semicolon-separated list of class names of custom containers that support push_back.</p>
<p>IgnoreImplicitConstructors</p>
<p>When true, the check will ignore implicitly constructed arguments of push_back, e.g.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::vector&lt;std::string&gt; v;
v.push_back(<span class="st">&quot;a&quot;</span>); <span class="co">// Ignored when IgnoreImplicitConstructors is `true`.</span></code></pre></div>
<p>Default is false.</p>
<p>SmartPointers</p>
<p>Semicolon-separated list of class names of custom smart pointers.</p>
<p>TupleTypes</p>
<p>Semicolon-separated list of std::tuple-like class names.</p>
<p>TupleMakeFunctions</p>
<p>Semicolon-separated list of std::make_tuple-like function names. Those function calls will be removed from push_back calls and turned into emplace_back.</p>
<h6 id="example">Example</h6>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::vector&lt;MyTuple&lt;<span class="dt">int</span>, <span class="dt">bool</span>, <span class="dt">char</span>&gt;&gt; x;
x.push_back(MakeMyTuple(<span class="dv">1</span>, <span class="kw">false</span>, <span class="st">&#39;x&#39;</span>));</code></pre></div>
<p>transforms to:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::vector&lt;MyTuple&lt;<span class="dt">int</span>, <span class="dt">bool</span>, <span class="dt">char</span>&gt;&gt; x;
x.emplace_back(<span class="dv">1</span>, <span class="kw">false</span>, <span class="st">&#39;x&#39;</span>);</code></pre></div>
<p>when <a href="#cmdoption-arg-tupletypes">TupleTypes</a> is set to MyTuple and <a href="#cmdoption-arg-tuplemakefunctions">TupleMakeFunctions</a> is set to MakeMyTuple.</p>
<p>(Clang-Tidy original name: modernize-use-emplace)</p>


#### Use Equals Default {#CT_MDR_UED}
<p>This check replaces default bodies of special member functions with = default;. The explicitly defaulted function declarations enable more opportunities in optimization, because the compiler might treat explicitly defaulted functions as trivial.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">struct</span> A {
  A() {}
  ~A();
};
A::~A() {}

<span class="co">// becomes</span>

<span class="kw">struct</span> A {
  A() = <span class="kw">default</span>;
  ~A();
};
A::~A() = <span class="kw">default</span>;</code></pre></div>
<p>Note</p>
<p>Move-constructor and move-assignment operator are not supported yet.</p>
<h5 id="options-26">Options</h5>
<p>IgnoreMacros</p>
<p>If set to true, the check will not give warnings inside macros. Default is true.</p>
<p>(Clang-Tidy original name: modernize-use-equals-default)</p>


#### Use Equals Delete {#CT_MDR_UED2}
<p>This check marks unimplemented private special member functions with = delete. To avoid false-positives, this check only applies in a translation unit that has all other member functions implemented.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">struct</span> A {
<span class="kw">private</span>:
  A(<span class="dt">const</span> A&amp;);
  A&amp; <span class="kw">operator</span>=(<span class="dt">const</span> A&amp;);
};

<span class="co">// becomes</span>

<span class="kw">struct</span> A {
<span class="kw">private</span>:
  A(<span class="dt">const</span> A&amp;) = <span class="kw">delete</span>;
  A&amp; <span class="kw">operator</span>=(<span class="dt">const</span> A&amp;) = <span class="kw">delete</span>;
};</code></pre></div>
<p>IgnoreMacros</p>
<p>If this option is set to true (default is true), the check will not warn about functions declared inside macros.</p>
<p>(Clang-Tidy original name: modernize-use-equals-delete)</p>


#### Use Nodiscard {#CT_MDR_UN}
<p>Adds [[nodiscard]] attributes (introduced in C++17) to member functions in order to highlight at compile time which return values should not be ignored.</p>
<p>Member functions need to satisfy the following conditions to be considered by this check:</p>
<ul>
<li>no [[nodiscard]], [[noreturn]], <strong>attribute</strong>((warn_unused_result)), [[clang::warn_unused_result]] nor [[gcc::warn_unused_result]] attribute,</li>
<li>non-void return type,</li>
<li>non-template return types,</li>
<li>const member function,</li>
<li>non-variadic functions,</li>
<li>no non-const reference parameters,</li>
<li>no pointer parameters,</li>
<li>no template parameters,</li>
<li>no template function parameters,</li>
<li>not be a member of a class with mutable member variables,</li>
<li>no Lambdas,</li>
<li>no conversion functions.</li>
</ul>
<p>Such functions have no means of altering any state or passing values other than via the return type. Unless the member functions are altering state via some external call (e.g. I/O).</p>
<h5 id="example-6">Example</h5>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">bool</span> empty() <span class="dt">const</span>;
<span class="dt">bool</span> empty(<span class="dt">int</span> i) <span class="dt">const</span>;</code></pre></div>
<p>transforms to:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">[[<span class="kw">nodiscard</span>] <span class="kw">bool</span> <span class="kw">empty</span>() <span class="kw">const</span>;
[[<span class="kw">nodiscard</span>] <span class="kw">bool</span> <span class="kw">empty</span>(<span class="kw">int</span> <span class="kw">i</span>) <span class="kw">const</span>;</code></pre></div>
<h5 id="options-60">Options</h5>
<p>ReplacementString</p>
<p>Specifies a macro to use instead of [[nodiscard]]. This is useful when maintaining source code that needs to compile with a pre-C++17 compiler.</p>
<h6 id="example-7">Example</h6>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">bool</span> empty() <span class="dt">const</span>;
<span class="dt">bool</span> empty(<span class="dt">int</span> i) <span class="dt">const</span>;</code></pre></div>
<p>transforms to:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">NO_DISCARD <span class="dt">bool</span> empty() <span class="dt">const</span>;
NO_DISCARD <span class="dt">bool</span> empty(<span class="dt">int</span> i) <span class="dt">const</span>;</code></pre></div>
<p>if the <a href="modernize-use-noexcept.html#cmdoption-arg-replacementstring">ReplacementString</a> option is set to NO_DISCARD.</p>
<p>Note</p>
<p>If the <a href="modernize-use-noexcept.html#cmdoption-arg-replacementstring">ReplacementString</a> is not a C++ attribute, but instead a macro, then that macro must be defined in scope or the fix-it will not be applied.</p>
<p>Note</p>
<p>For alternative <strong>attribute</strong> syntax options to mark functions as [[nodiscard]] in non-c++17 source code. See <a href="https://clang.llvm.org/docs/AttributeReference.html\#nodiscard-warn-unused-result" class="uri">https://clang.llvm.org/docs/AttributeReference.html\#nodiscard-warn-unused-result</a></p>
<p>(Clang-Tidy original name: modernize-use-nodiscard)</p>


#### Use Noexcept {#CT_MDR_UN2}
<p>This check replaces deprecated dynamic exception specifications with the appropriate noexcept specification (introduced in C++11). By default this check will replace throw() with noexcept, and throw(<exception>[,...]) or throw(...) with noexcept(false).</p>
<h5 id="example-13">Example</h5>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> foo() <span class="kw">throw</span>();
<span class="dt">void</span> bar() <span class="kw">throw</span>(<span class="dt">int</span>) {}</code></pre></div>
<p>transforms to:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> foo() <span class="kw">noexcept</span>;
<span class="dt">void</span> bar() <span class="kw">noexcept</span>(<span class="kw">false</span>) {}</code></pre></div>
<h5 id="options-83">Options</h5>
<p>ReplacementString</p>
<p>Users can use <a href="#cmdoption-arg-replacementstring">ReplacementString</a> to specify a macro to use instead of noexcept. This is useful when maintaining source code that uses custom exception specification marking other than noexcept. Fix-it hints will only be generated for non-throwing specifications.</p>
<h6 id="example-14">Example</h6>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> bar() <span class="kw">throw</span>(<span class="dt">int</span>);
<span class="dt">void</span> foo() <span class="kw">throw</span>();</code></pre></div>
<p>transforms to:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> bar() <span class="kw">throw</span>(<span class="dt">int</span>);  <span class="co">// No fix-it generated.</span>
<span class="dt">void</span> foo() NOEXCEPT;</code></pre></div>
<p>if the <a href="#cmdoption-arg-replacementstring">ReplacementString</a> option is set to NOEXCEPT.</p>
<p>UseNoexceptFalse</p>
<p>Enabled by default, disabling will generate fix-it hints that remove throwing dynamic exception specs, e.g., throw(<something>), completely without providing a replacement text, except for destructors and delete operators that are noexcept(true) by default.</p>
<h6 id="example-15">Example</h6>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> foo() <span class="kw">throw</span>(<span class="dt">int</span>) {}

<span class="kw">struct</span> bar {
  <span class="dt">void</span> foobar() <span class="kw">throw</span>(<span class="dt">int</span>);
  <span class="dt">void</span> <span class="kw">operator</span> <span class="kw">delete</span>(<span class="dt">void</span> *ptr) <span class="kw">throw</span>(<span class="dt">int</span>);
  <span class="dt">void</span> <span class="kw">operator</span> <span class="kw">delete</span>[](<span class="dt">void</span> *ptr) <span class="kw">throw</span>(<span class="dt">int</span>);
  ~bar() <span class="kw">throw</span>(<span class="dt">int</span>);
}</code></pre></div>
<p>transforms to:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> foo() {}

<span class="kw">struct</span> bar {
  <span class="dt">void</span> foobar();
  <span class="dt">void</span> <span class="kw">operator</span> <span class="kw">delete</span>(<span class="dt">void</span> *ptr) <span class="kw">noexcept</span>(<span class="kw">false</span>);
  <span class="dt">void</span> <span class="kw">operator</span> <span class="kw">delete</span>[](<span class="dt">void</span> *ptr) <span class="kw">noexcept</span>(<span class="kw">false</span>);
  ~bar() <span class="kw">noexcept</span>(<span class="kw">false</span>);
}</code></pre></div>
<p>if the <a href="#cmdoption-arg-usenoexceptfalse">UseNoexceptFalse</a> option is set to false.</p>
<p>(Clang-Tidy original name: modernize-use-noexcept)</p>


#### Use Nullptr {#CT_MDR_UN3}
<p>The check converts the usage of null pointer constants (eg. NULL, 0) to use the new C++11 nullptr keyword.</p>
<h5 id="example-11">Example</h5>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> assignment() {
  <span class="dt">char</span> *a = NULL;
  <span class="dt">char</span> *b = <span class="dv">0</span>;
  <span class="dt">char</span> c = <span class="dv">0</span>;
}

<span class="dt">int</span> *ret_ptr() {
  <span class="kw">return</span> <span class="dv">0</span>;
}</code></pre></div>
<p>transforms to:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> assignment() {
  <span class="dt">char</span> *a = <span class="kw">nullptr</span>;
  <span class="dt">char</span> *b = <span class="kw">nullptr</span>;
  <span class="dt">char</span> c = <span class="dv">0</span>;
}

<span class="dt">int</span> *ret_ptr() {
  <span class="kw">return</span> <span class="kw">nullptr</span>;
}</code></pre></div>
<h5 id="options-82">Options</h5>
<p>NullMacros</p>
<p>Comma-separated list of macro names that will be transformed along with NULL. By default this check will only replace the NULL macro and will skip any similar user-defined macros.</p>
<h6 id="example-12">Example</h6>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="ot">#define MY_NULL (void*)0</span>
<span class="dt">void</span> assignment() {
  <span class="dt">void</span> *p = MY_NULL;
}</code></pre></div>
<p>transforms to:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="ot">#define MY_NULL NULL</span>
<span class="dt">void</span> assignment() {
  <span class="dt">int</span> *p = <span class="kw">nullptr</span>;
}</code></pre></div>
<p>if the <a href="#cmdoption-arg-nullmacros">NullMacros</a> option is set to MY_NULL.</p>
<p>(Clang-Tidy original name: modernize-use-nullptr)</p>


#### Use Override {#CT_MDR_UO}
<p>Adds override (introduced in C++11) to overridden virtual functions and removes virtual from those functions as it is not required.</p>
<p>virtual on non base class implementations was used to help indicate to the user that a function was virtual. C++ compilers did not use the presence of this to signify an overridden function.</p>
<p>In C++ 11 override and final keywords were introduced to allow overridden functions to be marked appropriately. Their presence allows compilers to verify that an overridden function correctly overrides a base class implementation.</p>
<p>This can be useful as compilers can generate a compile time error when:</p>
<ul>
<li>The base class implementation function signature changes.</li>
<li>The user has not created the override with the correct signature.</li>
</ul>
<h5 id="options-56">Options</h5>
<p>IgnoreDestructors</p>
<p>If set to true, this check will not diagnose destructors. Default is false.</p>
<p>AllowOverrideAndFinal</p>
<p>If set to true, this check will not diagnose override as redundant with final. This is useful when code will be compiled by a compiler with warning/error checking flags requiring override explicitly on overridden members, such as gcc -Wsuggest-override/gcc -Werror=suggest-override. Default is false.</p>
<p>OverrideSpelling</p>
<p>Specifies a macro to use instead of override. This is useful when maintaining source code that also needs to compile with a pre-C++11 compiler.</p>
<p>FinalSpelling</p>
<p>Specifies a macro to use instead of final. This is useful when maintaining source code that also needs to compile with a pre-C++11 compiler.</p>
<p>Note</p>
<p>For more information on the use of override see <a href="https://en.cppreference.com/w/cpp/language/override" class="uri">https://en.cppreference.com/w/cpp/language/override</a></p>
<p>(Clang-Tidy original name: modernize-use-override)</p>


#### Use Trailing Return Type {#CT_MDR_UTRT}
<p>Rewrites function signatures to use a trailing return type (introduced in C++11). This transformation is purely stylistic. The return type before the function name is replaced by auto and inserted after the function parameter list (and qualifiers).</p>
<h5 id="example-5">Example</h5>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">int</span> f1();
<span class="kw">inline</span> <span class="dt">int</span> f2(<span class="dt">int</span> arg) <span class="kw">noexcept</span>;
<span class="kw">virtual</span> <span class="dt">float</span> f3() <span class="dt">const</span> &amp;&amp; = <span class="kw">delete</span>;</code></pre></div>
<p>transforms to:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">auto</span> f1() -&gt; <span class="dt">int</span>;
<span class="kw">inline</span> <span class="kw">auto</span> f2(<span class="dt">int</span> arg) -&gt; <span class="dt">int</span> <span class="kw">noexcept</span>;
<span class="kw">virtual</span> <span class="kw">auto</span> f3() <span class="dt">const</span> &amp;&amp; -&gt; <span class="dt">float</span> = <span class="kw">delete</span>;</code></pre></div>
<h5 id="known-limitations-4">Known Limitations</h5>
<p>The following categories of return types cannot be rewritten currently:</p>
<ul>
<li>function pointers</li>
<li>member function pointers</li>
<li>member pointers</li>
</ul>
<p>Unqualified names in the return type might erroneously refer to different entities after the rewrite. Preventing such errors requires a full lookup of all unqualified names present in the return type in the scope of the trailing return type location. This location includes e.g. function parameter names and members of the enclosing class (including all inherited classes). Such a lookup is currently not implemented.</p>
<p>Given the following piece of code</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">struct</span> S { <span class="dt">long</span> <span class="dt">long</span> value; };
S f(<span class="dt">unsigned</span> S) { <span class="kw">return</span> {S * <span class="dv">2</span>}; }
<span class="kw">class</span> CC {
  <span class="dt">int</span> S;
  <span class="kw">struct</span> S m();
};
S CC::m() { <span class="kw">return</span> {<span class="dv">0</span>}; }</code></pre></div>
<p>a careless rewrite would produce the following output:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">struct</span> S { <span class="dt">long</span> <span class="dt">long</span> value; };
<span class="kw">auto</span> f(<span class="dt">unsigned</span> S) -&gt; S { <span class="kw">return</span> {S * <span class="dv">2</span>}; } <span class="co">// error</span>
<span class="kw">class</span> CC {
  <span class="dt">int</span> S;
  <span class="kw">auto</span> m() -&gt; <span class="kw">struct</span> S;
};
<span class="kw">auto</span> CC::m() -&gt; S { <span class="kw">return</span> {<span class="dv">0</span>}; } <span class="co">// error</span></code></pre></div>
<p>This code fails to compile because the S in the context of f refers to the equally named function parameter. Similarly, the S in the context of m refers to the equally named class member. The check can currently only detect and avoid a clash with a function parameter name.</p>
<p>(Clang-Tidy original name: modernize-use-trailing-return-type)</p>


#### Use Transparent Functors {#CT_MDR_UTF}
<p>Prefer transparent functors to non-transparent ones. When using transparent functors, the type does not need to be repeated. The code is easier to read, maintain and less prone to errors. It is not possible to introduce unwanted conversions.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// Non-transparent functor</span>
std::map&lt;<span class="dt">int</span>, std::string, std::greater&lt;<span class="dt">int</span>&gt;&gt; s;

<span class="co">// Transparent functor.</span>
std::map&lt;<span class="dt">int</span>, std::string, std::greater&lt;&gt;&gt; s;

<span class="co">// Non-transparent functor</span>
<span class="kw">using</span> MyFunctor = std::less&lt;MyType&gt;;</code></pre></div>
<p>It is not always a safe transformation though. The following case will be untouched to preserve the semantics.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// Non-transparent functor</span>
std::map&lt;<span class="dt">const</span> <span class="dt">char</span> *, std::string, std::greater&lt;std::string&gt;&gt; s;</code></pre></div>
<h5 id="options-55">Options</h5>
<p>SafeMode</p>
<p>If the option is set to true, the check will not diagnose cases where using a transparent functor cannot be guaranteed to produce identical results as the original code. The default value for this option is false.</p>
<p>This check requires using C++14 or higher to run.</p>
<p>(Clang-Tidy original name: modernize-use-transparent-functors)</p>


#### Use Uncaught Exceptions {#CT_MDR_UUE}
<p>This check will warn on calls to std::uncaught_exception and replace them with calls to std::uncaught_exceptions, since std::uncaught_exception was deprecated in C++17.</p>
<p>Below are a few examples of what kind of occurrences will be found and what they will be replaced with.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="ot">#define MACRO1 std::uncaught_exception</span>
<span class="ot">#define MACRO2 std::uncaught_exception</span>

<span class="dt">int</span> uncaught_exception() {
  <span class="kw">return</span> <span class="dv">0</span>;
}

<span class="dt">int</span> main() {
  <span class="dt">int</span> res;

  res = uncaught_exception();
  <span class="co">// No warning, since it is not the deprecated function from namespace std</span>

  res = MACRO2();
  <span class="co">// Warning, but will not be replaced</span>

  res = std::uncaught_exception();
  <span class="co">// Warning and replaced</span>

  <span class="kw">using</span> std::uncaught_exception;
  <span class="co">// Warning and replaced</span>

  res = uncaught_exception();
  <span class="co">// Warning and replaced</span>
}</code></pre></div>
<p>After applying the fixes the code will look like the following:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="ot">#define MACRO1 std::uncaught_exception</span>
<span class="ot">#define MACRO2 std::uncaught_exception</span>

<span class="dt">int</span> uncaught_exception() {
  <span class="kw">return</span> <span class="dv">0</span>;
}

<span class="dt">int</span> main() {
  <span class="dt">int</span> res;

  res = uncaught_exception();

  res = MACRO2();

  res = std::uncaught_exceptions();

  <span class="kw">using</span> std::uncaught_exceptions;

  res = uncaught_exceptions();
}</code></pre></div>
<p>(Clang-Tidy original name: modernize-use-uncaught-exceptions)</p>


#### Use Using {#CT_MDR_UU}
<p>The check converts the usage of typedef with using keyword.</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">typedef</span> <span class="dt">int</span> variable;

<span class="kw">class</span> Class{};
<span class="kw">typedef</span> <span class="dt">void</span> (Class::* MyPtrType)() <span class="dt">const</span>;

<span class="kw">typedef</span> <span class="kw">struct</span> { <span class="dt">int</span> a; } R_t, *R_p;</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">using</span> variable = <span class="dt">int</span>;

<span class="kw">class</span> Class{};
<span class="kw">using</span> MyPtrType = <span class="dt">void</span> (Class::*)() <span class="dt">const</span>;

<span class="kw">using</span> R_t = <span class="kw">struct</span> { <span class="dt">int</span> a; };
<span class="kw">using</span> R_p = R_t*;</code></pre></div>
<p>This check requires using C++11 or higher to run.</p>
<h5 id="options-28">Options</h5>
<p>IgnoreMacros</p>
<p>If set to true, the check will not give warnings inside macros. Default is true.</p>
<p>(Clang-Tidy original name: modernize-use-using)</p>


### Objective-C

#### Avoid Nserror Init {#CT_OBC_ANI}
<p>Finds improper initialization of NSError objects.</p>
<p>According to Apple developer document, we should always use factory method errorWithDomain:code:userInfo: to create new NSError objects instead of [NSError alloc] init]. Otherwise it will lead to a warning message during runtime.</p>
<p>The corresponding information about NSError creation: <a href="https://developer.apple.com/library/content/documentation/Cocoa/Conceptual/ErrorHandlingCocoa/CreateCustomizeNSError/CreateCustomizeNSError.html" class="uri">https://developer.apple.com/library/content/documentation/Cocoa/Conceptual/ErrorHandlingCocoa/CreateCustomizeNSError/CreateCustomizeNSError.html</a></p>
<p>(Clang-Tidy original name: objc-avoid-nserror-init)</p>


#### Dealloc In Category {#CT_OBC_DIC}
<p>Finds implementations of -dealloc in Objective-C categories. The category implementation will override any -dealloc in the class implementation, potentially causing issues.</p>
<p>Classes implement -dealloc to perform important actions to deallocate an object. If a category on the class implements -dealloc, it will override the class’s implementation and unexpected deallocation behavior may occur.</p>
<p>(Clang-Tidy original name: objc-dealloc-in-category)</p>


#### Forbidden Subclassing {#CT_OBC_FS}
<p>Finds Objective-C classes which are subclasses of classes which are not designed to be subclassed.</p>
<p>By default, includes a list of Objective-C classes which are publicly documented as not supporting subclassing.</p>
<p>Note</p>
<p>Instead of using this check, for code under your control, you should add <strong>attribute</strong>((objc_subclassing_restricted)) before your <span class="citation">@interface</span> declarations to ensure the compiler prevents others from subclassing your Objective-C classes. See <a href="https://clang.llvm.org/docs/AttributeReference.html\#objc-subclassing-restricted" class="uri">https://clang.llvm.org/docs/AttributeReference.html\#objc-subclassing-restricted</a></p>
<h5 id="options-39">Options</h5>
<p>ForbiddenSuperClassNames</p>
<p>Semicolon-separated list of names of Objective-C classes which do not support subclassing.</p>
<p>Defaults to ABNewPersonViewController;ABPeoplePickerNavigationController;ABPersonViewController;ABUnknownPersonViewController;NSHashTable;NSMapTable;NSPointerArray;NSPointerFunctions;NSTimer;UIActionSheet;UIAlertView;UIImagePickerController;UITextInputMode;UIWebView.</p>
<p>(Clang-Tidy original name: objc-forbidden-subclassing)</p>


#### Missing Hash {#CT_OBC_MH}
<p>Finds Objective-C implementations that implement -isEqual: without also appropriately implementing -hash.</p>
<p>Apple documentation highlights that objects that are equal must have the same hash value: <a href="https://developer.apple.com/documentation/objectivec/1418956-nsobject/1418795-isequal?language=objc" class="uri">https://developer.apple.com/documentation/objectivec/1418956-nsobject/1418795-isequal?language=objc</a></p>
<p>Note that the check only verifies the presence of -hash in scenarios where its omission could result in unexpected behavior. The verification of the implementation of -hash is the responsibility of the developer, e.g., through the addition of unit tests to verify the implementation.</p>
<p>(Clang-Tidy original name: objc-missing-hash)</p>


#### Nsinvocation Argument Lifetime {#CT_OBC_NAL}
<p>Finds calls to NSInvocation methods under ARC that don’t have proper argument object lifetimes. When passing Objective-C objects as parameters to the NSInvocation methods getArgument:atIndex: and getReturnValue:, the values are copied by value into the argument pointer, which leads to to incorrect releasing behavior if the object pointers are not declared __unsafe_unretained.</p>
<p>For code:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">id arg;
[invocation getArgument:&amp;arg atIndex:<span class="dv">2</span>];

__strong id returnValue;
[invocation getReturnValue:&amp;returnValue];</code></pre></div>
<p>The fix will be:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">__unsafe_unretained id arg;
[invocation getArgument:&amp;arg atIndex:<span class="dv">2</span>];

__unsafe_unretained id returnValue;
[invocation getReturnValue:&amp;returnValue];</code></pre></div>
<p>The check will warn on being passed instance variable references that have lifetimes other than __unsafe_unretained, but does not propose a fix:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// &quot;id _returnValue&quot; is declaration of instance variable of class.</span>
[invocation getReturnValue:&amp;self-&gt;_returnValue];</code></pre></div>
<p>(Clang-Tidy original name: objc-nsinvocation-argument-lifetime)</p>


#### Property Declaration {#CT_OBC_PD}
<p>Finds property declarations in Objective-C files that do not follow the pattern of property names in Apple’s programming guide. The property name should be in the format of Lower Camel Case.</p>
<p>For code:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="er">@</span>property(nonatomic, assign) <span class="dt">int</span> LowerCamelCase;</code></pre></div>
<p>The fix will be:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="er">@</span>property(nonatomic, assign) <span class="dt">int</span> lowerCamelCase;</code></pre></div>
<p>The check will only fix ‘CamelCase’ to ‘camelCase’. In some other cases we will only provide warning messages since the property name could be complicated. Users will need to come up with a proper name by their own.</p>
<p>This check also accepts special acronyms as prefixes or suffixes. Such prefixes or suffixes will suppress the Lower Camel Case check according to the guide: <a href="https://developer.apple.com/library/content/documentation/Cocoa/Conceptual/CodingGuidelines/Articles/NamingBasics.html\#//apple_ref/doc/uid/20001281-1002931-BBCFHEAB" class="uri">https://developer.apple.com/library/content/documentation/Cocoa/Conceptual/CodingGuidelines/Articles/NamingBasics.html\#//apple_ref/doc/uid/20001281-1002931-BBCFHEAB</a></p>
<p>For a full list of well-known acronyms: <a href="https://developer.apple.com/library/content/documentation/Cocoa/Conceptual/CodingGuidelines/Articles/APIAbbreviations.html\#//apple_ref/doc/uid/20001285-BCIHCGAE" class="uri">https://developer.apple.com/library/content/documentation/Cocoa/Conceptual/CodingGuidelines/Articles/APIAbbreviations.html\#//apple_ref/doc/uid/20001285-BCIHCGAE</a></p>
<p>The corresponding style rule: <a href="https://developer.apple.com/library/content/documentation/Cocoa/Conceptual/CodingGuidelines/Articles/NamingIvarsAndTypes.html\#//apple_ref/doc/uid/20001284-1001757" class="uri">https://developer.apple.com/library/content/documentation/Cocoa/Conceptual/CodingGuidelines/Articles/NamingIvarsAndTypes.html\#//apple_ref/doc/uid/20001284-1001757</a></p>
<p>The check will also accept property declared in category with a prefix of lowercase letters followed by a ‘_’ to avoid naming conflict. For example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="er">@</span>property(nonatomic, assign) <span class="dt">int</span> abc_lowerCamelCase;</code></pre></div>
<p>The corresponding style rule: <a href="https://developer.apple.com/library/content/qa/qa1908/_index.html" class="uri">https://developer.apple.com/library/content/qa/qa1908/_index.html</a></p>
<p>(Clang-Tidy original name: objc-property-declaration)</p>


#### Super Self {#CT_OBC_SS}
<p>Finds invocations of -self on super instances in initializers of subclasses of NSObject and recommends calling a superclass initializer instead.</p>
<p>Invoking -self on super instances in initializers is a common programmer error when the programmer’s original intent is to call a superclass initializer. Failing to call a superclass initializer breaks initializer chaining and can result in invalid object initialization.</p>
<p>(Clang-Tidy original name: objc-super-self)</p>


### OpenMP

#### Exception Escape {#CT_OMP_EE}
<p>Analyzes OpenMP Structured Blocks and checks that no exception escapes out of the Structured Block it was thrown in.</p>
<p>As per the OpenMP specification, a structured block is an executable statement, possibly compound, with a single entry at the top and a single exit at the bottom. Which means, throw may not be used to to ‘exit’ out of the structured block. If an exception is not caught in the same structured block it was thrown in, the behaviour is undefined.</p>
<p>FIXME: this check does not model SEH, setjmp/longjmp.</p>
<p>WARNING! This check may be expensive on large source files.</p>
<h5 id="options-20">Options</h5>
<p>IgnoredExceptions</p>
<p>Comma-separated list containing type names which are not counted as thrown exceptions in the check. Default value is an empty string.</p>
<p>(Clang-Tidy original name: openmp-exception-escape)</p>


#### Use Default None {#CT_OMP_UDN}
<p>Finds OpenMP directives that are allowed to contain a default clause, but either don’t specify it or the clause is specified but with the kind other than none, and suggests to use the default(none) clause.</p>
<p>Using default(none) clause forces developers to explicitly specify data sharing attributes for the variables referenced in the construct, thus making it obvious which variables are referenced, and what is their data sharing attribute, thus increasing readability and possibly making errors easier to spot.</p>
<h5 id="example-3">Example</h5>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// ``for`` directive can not have ``default`` clause, no diagnostics.</span>
<span class="dt">void</span> n0(<span class="dt">const</span> <span class="dt">int</span> a) {
<span class="ot">#pragma omp for</span>
  <span class="kw">for</span> (<span class="dt">int</span> b = <span class="dv">0</span>; b &lt; a; b++)
    ;
}

<span class="co">// ``parallel`` directive.</span>

<span class="co">// ``parallel`` directive can have ``default`` clause, but said clause is not</span>
<span class="co">// specified, diagnosed.</span>
<span class="dt">void</span> p0_0() {
<span class="ot">#pragma omp parallel</span>
  ;
  <span class="co">// WARNING: OpenMP directive ``parallel`` does not specify ``default``</span>
  <span class="co">//          clause. Consider specifying ``default(none)`` clause.</span>
}

<span class="co">// ``parallel`` directive can have ``default`` clause, and said clause is</span>
<span class="co">// specified, with ``none`` kind, all good.</span>
<span class="dt">void</span> p0_1() {
<span class="ot">#pragma omp parallel default(none)</span>
  ;
}

<span class="co">// ``parallel`` directive can have ``default`` clause, and said clause is</span>
<span class="co">// specified, but with ``shared`` kind, which is not ``none``, diagnose.</span>
<span class="dt">void</span> p0_2() {
<span class="ot">#pragma omp parallel default(shared)</span>
  ;
  <span class="co">// WARNING: OpenMP directive ``parallel`` specifies ``default(shared)``</span>
  <span class="co">//          clause. Consider using ``default(none)`` clause instead.</span>
}

<span class="co">// ``parallel`` directive can have ``default`` clause, and said clause is</span>
<span class="co">// specified, but with ``firstprivate`` kind, which is not ``none``, diagnose.</span>
<span class="dt">void</span> p0_3() {
<span class="ot">#pragma omp parallel default(firstprivate)</span>
  ;
  <span class="co">// WARNING: OpenMP directive ``parallel`` specifies ``default(firstprivate)``</span>
  <span class="co">//          clause. Consider using ``default(none)`` clause instead.</span>
}</code></pre></div>
<p>(Clang-Tidy original name: openmp-use-default-none)</p>


### Performance

#### Faster String Find {#CT_PRF_FSF}
<p>Optimize calls to std::string::find() and friends when the needle passed is a single character string literal. The character literal overload is more efficient.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">str.find(<span class="st">&quot;A&quot;</span>);

<span class="co">// becomes</span>

str.find(<span class="st">&#39;A&#39;</span>);</code></pre></div>
<h5 id="options-10">Options</h5>
<p>StringLikeClasses</p>
<p>Semicolon-separated list of names of string-like classes. By default only ::std::basic_string and ::std::basic_string_view are considered. The check will only consider member functions named find, rfind, find_first_of, find_first_not_of, find_last_of, or find_last_not_of within these classes.</p>
<p>(Clang-Tidy original name: performance-faster-string-find)</p>


#### For Range Copy {#CT_PRF_FRC}
<p>Finds C++11 for ranges where the loop variable is copied in each iteration but it would suffice to obtain it by const reference.</p>
<p>The check is only applied to loop variables of types that are expensive to copy which means they are not trivially copyable or have a non-trivial copy constructor or destructor.</p>
<p>To ensure that it is safe to replace the copy with a const reference the following heuristic is employed:</p>
<ol style="list-style-type: decimal">
<li>The loop variable is const qualified.</li>
<li>The loop variable is not const, but only const methods or operators are invoked on it, or it is used as const reference or value argument in constructors or function calls.</li>
</ol>
<h5 id="options-9">Options</h5>
<p>WarnOnAllAutoCopies</p>
<p>When true, warns on any use of auto as the type of the range-based for loop variable. Default is false.</p>
<p>AllowedTypes</p>
<p>A semicolon-separated list of names of types allowed to be copied in each iteration. Regular expressions are accepted, e.g. [Rr]ef(erence)?$ matches every type with suffix Ref, ref, Reference and reference. The default is empty.</p>
<p>(Clang-Tidy original name: performance-for-range-copy)</p>


#### Implicit Conversion In Loop {#CT_PRF_ICIL}
<p>This warning appears in a range-based loop with a loop variable of const ref type where the type of the variable does not match the one returned by the iterator. This means that an implicit conversion happens, which can for example result in expensive deep copies.</p>
<p>Example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">map&lt;<span class="dt">int</span>, vector&lt;string&gt;&gt; my_map;
<span class="kw">for</span> (<span class="dt">const</span> pair&lt;<span class="dt">int</span>, vector&lt;string&gt;&gt;&amp; p : my_map) {}
<span class="co">// The iterator type is in fact pair&lt;const int, vector&lt;string&gt;&gt;, which means</span>
<span class="co">// that the compiler added a conversion, resulting in a copy of the vectors.</span></code></pre></div>
<p>The easiest solution is usually to use const auto&amp; instead of writing the type manually.</p>
<p>(Clang-Tidy original name: performance-implicit-conversion-in-loop)</p>


#### Inefficient Algorithm {#CT_PRF_IA}
<p>Warns on inefficient use of STL algorithms on associative containers.</p>
<p>Associative containers implements some of the algorithms as methods which should be preferred to the algorithms in the algorithm header. The methods can take advantage of the order of the elements.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::set&lt;<span class="dt">int</span>&gt; s;
<span class="kw">auto</span> it = std::find(s.begin(), s.end(), <span class="dv">43</span>);

<span class="co">// becomes</span>

<span class="kw">auto</span> it = s.find(<span class="dv">43</span>);</code></pre></div>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::set&lt;<span class="dt">int</span>&gt; s;
<span class="kw">auto</span> c = std::count(s.begin(), s.end(), <span class="dv">43</span>);

<span class="co">// becomes</span>

<span class="kw">auto</span> c = s.count(<span class="dv">43</span>);</code></pre></div>
<p>(Clang-Tidy original name: performance-inefficient-algorithm)</p>


#### Inefficient String Concatenation {#CT_PRF_ISC}
<p>This check warns about the performance overhead arising from concatenating strings using the operator+, for instance:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::string a(<span class="st">&quot;Foo&quot;</span>), b(<span class="st">&quot;Bar&quot;</span>);
a = a + b;</code></pre></div>
<p>Instead of this structure you should use operator+= or std::string’s (std::basic_string) class member function append(). For instance:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::string a(<span class="st">&quot;Foo&quot;</span>), b(<span class="st">&quot;Baz&quot;</span>);
<span class="kw">for</span> (<span class="dt">int</span> i = <span class="dv">0</span>; i &lt; <span class="dv">20000</span>; ++i) {
    a = a + <span class="st">&quot;Bar&quot;</span> + b;
}</code></pre></div>
<p>Could be rewritten in a greatly more efficient way like:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::string a(<span class="st">&quot;Foo&quot;</span>), b(<span class="st">&quot;Baz&quot;</span>);
<span class="kw">for</span> (<span class="dt">int</span> i = <span class="dv">0</span>; i &lt; <span class="dv">20000</span>; ++i) {
    a.append(<span class="st">&quot;Bar&quot;</span>).append(b);
}</code></pre></div>
<p>And this can be rewritten too:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> f(<span class="dt">const</span> std::string&amp;) {}
std::string a(<span class="st">&quot;Foo&quot;</span>), b(<span class="st">&quot;Baz&quot;</span>);
<span class="dt">void</span> g() {
    f(a + <span class="st">&quot;Bar&quot;</span> + b);
}</code></pre></div>
<p>In a slightly more efficient way like:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> f(<span class="dt">const</span> std::string&amp;) {}
std::string a(<span class="st">&quot;Foo&quot;</span>), b(<span class="st">&quot;Baz&quot;</span>);
<span class="dt">void</span> g() {
    f(std::string(a).append(<span class="st">&quot;Bar&quot;</span>).append(b));
}</code></pre></div>
<h5 id="options-46">Options</h5>
<p>StrictMode</p>
<p>When false, the check will only check the string usage in while, for and for-range statements. Default is false.</p>
<p>(Clang-Tidy original name: performance-inefficient-string-concatenation)</p>


#### Inefficient Vector Operation {#CT_PRF_IVO}
<p>Finds possible inefficient std::vector operations (e.g. push_back, emplace_back) that may cause unnecessary memory reallocations.</p>
<p>It can also find calls that add element to protobuf repeated field in a loop without calling Reserve() before the loop. Calling Reserve() first can avoid unnecessary memory reallocations.</p>
<p>Currently, the check only detects following kinds of loops with a single statement body:</p>
<ul>
<li>Counter-based for loops start with 0:</li>
</ul>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::vector&lt;<span class="dt">int</span>&gt; v;
<span class="kw">for</span> (<span class="dt">int</span> i = <span class="dv">0</span>; i &lt; n; ++i) {
  v.push_back(n);
  <span class="co">// This will trigger the warning since the push_back may cause multiple</span>
  <span class="co">// memory reallocations in v. This can be avoid by inserting a &#39;reserve(n)&#39;</span>
  <span class="co">// statement before the for statement.</span>
}

SomeProto p;
<span class="kw">for</span> (<span class="dt">int</span> i = <span class="dv">0</span>; i &lt; n; ++i) {
  p.add_xxx(n);
  <span class="co">// This will trigger the warning since the add_xxx may cause multiple memory</span>
  <span class="co">// reallocations. This can be avoid by inserting a</span>
  <span class="co">// &#39;p.mutable_xxx().Reserve(n)&#39; statement before the for statement.</span>
}</code></pre></div>
<ul>
<li>For-range loops like for (range-declaration : range_expression), the type of range_expression can be std::vector, std::array, std::deque, std::set, std::unordered_set, std::map, std::unordered_set:</li>
</ul>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::vector&lt;<span class="dt">int</span>&gt; data;
std::vector&lt;<span class="dt">int</span>&gt; v;

<span class="kw">for</span> (<span class="kw">auto</span> element : data) {
  v.push_back(element);
  <span class="co">// This will trigger the warning since the &#39;push_back&#39; may cause multiple</span>
  <span class="co">// memory reallocations in v. This can be avoid by inserting a</span>
  <span class="co">// &#39;reserve(data.size())&#39; statement before the for statement.</span>
}</code></pre></div>
<h5 id="options-48">Options</h5>
<p>VectorLikeClasses</p>
<p>Semicolon-separated list of names of vector-like classes. By default only ::std::vector is considered.</p>
<p>EnableProto</p>
<p>When true, the check will also warn on inefficient operations for proto repeated fields. Otherwise, the check only warns on inefficient vector operations. Default is false.</p>
<p>(Clang-Tidy original name: performance-inefficient-vector-operation)</p>


#### Move Const Arg {#CT_PRF_MCA}
<p>The check warns</p>
<ul>
<li>if std::move() is called with a constant argument,</li>
<li>if std::move() is called with an argument of a trivially-copyable type,</li>
<li>if the result of std::move() is passed as a const reference argument.</li>
</ul>
<p>In all three cases, the check will suggest a fix that removes the std::move().</p>
<p>Here are examples of each of the three cases:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">const</span> string s;
<span class="kw">return</span> std::move(s);  <span class="co">// Warning: std::move of the const variable has no effect</span>

<span class="dt">int</span> x;
<span class="kw">return</span> std::move(x);  <span class="co">// Warning: std::move of the variable of a trivially-copyable type has no effect</span>

<span class="dt">void</span> f(<span class="dt">const</span> string &amp;s);
string s;
f(std::move(s));  <span class="co">// Warning: passing result of std::move as a const reference argument; no move will actually happen</span></code></pre></div>
<h5 id="options-81">Options</h5>
<p>CheckTriviallyCopyableMove</p>
<p>If true, enables detection of trivially copyable types that do not have a move constructor. Default is true.</p>
<p>(Clang-Tidy original name: performance-move-const-arg)</p>


#### Move Constructor Init {#CT_PRF_MCI}
<p>“cert-oop11-cpp” redirects here as an alias for this check.</p>
<p>The check flags user-defined move constructors that have a ctor-initializer initializing a member or base class through a copy constructor instead of a move constructor.</p>
<h5 id="options-70">Options</h5>
<p>IncludeStyle</p>
<p>A string specifying which include-style is used, llvm or google. Default is llvm.</p>
<p>(Clang-Tidy original name: performance-move-constructor-init)</p>


#### No Automatic Move {#CT_PRF_NAM}
<p>Finds local variables that cannot be automatically moved due to constness.</p>
<p>Under <a href="https://en.cppreference.com/w/cpp/language/return#automatic_move_from_local_variables_and_parameters">certain conditions</a>, local values are automatically moved out when returning from a function. A common mistake is to declare local lvalue variables const, which prevents the move.</p>
<p>Example <a href="https://godbolt.org/z/x7SYYA">[1]</a>:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">StatusOr&lt;std::vector&lt;<span class="dt">int</span>&gt;&gt; Cool() {
  std::vector&lt;<span class="dt">int</span>&gt; obj = ...;
  <span class="kw">return</span> obj;  <span class="co">// calls StatusOr::StatusOr(std::vector&lt;int&gt;&amp;&amp;)</span>
}

StatusOr&lt;std::vector&lt;<span class="dt">int</span>&gt;&gt; NotCool() {
  <span class="dt">const</span> std::vector&lt;<span class="dt">int</span>&gt; obj = ...;
  <span class="kw">return</span> obj;  <span class="co">// calls `StatusOr::StatusOr(const std::vector&lt;int&gt;&amp;)`</span>
}</code></pre></div>
<p>The former version (Cool) should be preferred over the latter (Uncool) as it will avoid allocations and potentially large memory copies.</p>
<h5 id="semantics">Semantics</h5>
<p>In the example above, StatusOr::StatusOr(T&amp;&amp;) have the same semantics as long as the copy and move constructors for T have the same semantics. Note that there is no guarantee that S::S(T&amp;&amp;) and S::S(const T&amp;) have the same semantics for any single S, so we’re not providing automated fixes for this check, and judgement should be exerted when making the suggested changes.</p>
<h5 id="wreturn-std-move">-Wreturn-std-move</h5>
<p>Another case where the move cannot happen is the following:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">StatusOr&lt;std::vector&lt;<span class="dt">int</span>&gt;&gt; Uncool() {
  std::vector&lt;<span class="dt">int</span>&gt;&amp;&amp; obj = ...;
  <span class="kw">return</span> obj;  <span class="co">// calls `StatusOr::StatusOr(const std::vector&lt;int&gt;&amp;)`</span>
}</code></pre></div>
<p>In that case the fix is more consensual: just return std::move(obj). This is handled by the -Wreturn-std-move warning.</p>
<p>(Clang-Tidy original name: performance-no-automatic-move)</p>


#### No Int To Ptr {#CT_PRF_NITP}
<p>Diagnoses every integer to pointer cast.</p>
<p>While casting an (integral) pointer to an integer is obvious - you just get the integral value of the pointer, casting an integer to an (integral) pointer is deceivingly different. While you will get a pointer with that integral value, if you got that integral value via a pointer-to-integer cast originally, the new pointer will lack the provenance information from the original pointer.</p>
<p>So while (integral) pointer to integer casts are effectively no-ops, and are transparent to the optimizer, integer to (integral) pointer casts are <em>NOT</em> transparent, and may conceal information from optimizer.</p>
<p>While that may be the intention, it is not always so. For example, let’s take a look at a routine to align the pointer up to the multiple of 16: The obvious, naive implementation for that is:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">char</span>* src(<span class="dt">char</span>* maybe_underbiased_ptr) {
  uintptr_t maybe_underbiased_intptr = (uintptr_t)maybe_underbiased_ptr;
  uintptr_t aligned_biased_intptr = maybe_underbiased_intptr + <span class="dv">15</span>;
  uintptr_t aligned_intptr = aligned_biased_intptr &amp; (~<span class="dv">15</span>);
  <span class="kw">return</span> (<span class="dt">char</span>*)aligned_intptr; <span class="co">// warning: avoid integer to pointer casts [performance-no-int-to-ptr]</span>
}</code></pre></div>
<p>The check will rightfully diagnose that cast.</p>
<p>But when provenance concealment is not the goal of the code, but an accident, this example can be rewritten as follows, without using integer to pointer cast:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">char</span>*
tgt(<span class="dt">char</span>* maybe_underbiased_ptr) {
    uintptr_t maybe_underbiased_intptr = (uintptr_t)maybe_underbiased_ptr;
    uintptr_t aligned_biased_intptr = maybe_underbiased_intptr + <span class="dv">15</span>;
    uintptr_t aligned_intptr = aligned_biased_intptr &amp; (~<span class="dv">15</span>);
    uintptr_t bias = aligned_intptr - maybe_underbiased_intptr;
    <span class="kw">return</span> maybe_underbiased_ptr + bias;
}</code></pre></div>
<p>(Clang-Tidy original name: performance-no-int-to-ptr)</p>


#### Noexcept Move Constructor {#CT_PRF_NMC}
<p>The check flags user-defined move constructors and assignment operators not marked with noexcept or marked with noexcept(expr) where expr evaluates to false (but is not a false literal itself).</p>
<p>Move constructors of all the types used with STL containers, for example, need to be declared noexcept. Otherwise STL will choose copy constructors instead. The same is valid for move assignment operations.</p>
<p>(Clang-Tidy original name: performance-noexcept-move-constructor)</p>


#### Trivially Destructible {#CT_PRF_TD}
<p>Finds types that could be made trivially-destructible by removing out-of-line defaulted destructor declarations.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">struct</span> A: TrivialType {
  ~A(); <span class="co">// Makes A non-trivially-destructible.</span>
  TrivialType trivial_fields;
};
A::~A() = <span class="kw">default</span>;</code></pre></div>
<p>(Clang-Tidy original name: performance-trivially-destructible)</p>


#### Type Promotion In Math Fn {#CT_PRF_TPIMF}
<p>Finds calls to C math library functions (from math.h or, in C++, cmath) with implicit float to double promotions.</p>
<p>For example, warns on ::sin(0.f), because this funciton’s parameter is a double. You probably meant to call std::sin(0.f) (in C++), or sinf(0.f) (in C).</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">float</span> a;
asin(a);

<span class="co">// becomes</span>

<span class="dt">float</span> a;
std::asin(a);</code></pre></div>
<p>(Clang-Tidy original name: performance-type-promotion-in-math-fn)</p>


#### Unnecessary Copy Initialization {#CT_PRF_UCI}
<p>Finds local variable declarations that are initialized using the copy constructor of a non-trivially-copyable type but it would suffice to obtain a const reference.</p>
<p>The check is only applied if it is safe to replace the copy by a const reference. This is the case when the variable is const qualified or when it is only used as a const, i.e. only const methods or operators are invoked on it, or it is used as const reference or value argument in constructors or function calls.</p>
<p>Example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">const</span> string&amp; constReference();
<span class="dt">void</span> Function() {
  <span class="co">// The warning will suggest making this a const reference.</span>
  <span class="dt">const</span> string UnnecessaryCopy = constReference();
}

<span class="kw">struct</span> Foo {
  <span class="dt">const</span> string&amp; name() <span class="dt">const</span>;
};
<span class="dt">void</span> Function(<span class="dt">const</span> Foo&amp; foo) {
  <span class="co">// The warning will suggest making this a const reference.</span>
  string UnnecessaryCopy1 = foo.name();
  UnnecessaryCopy1.find(<span class="st">&quot;bar&quot;</span>);

  <span class="co">// The warning will suggest making this a const reference.</span>
  string UnnecessaryCopy2 = UnnecessaryCopy1;
  UnnecessaryCopy2.find(<span class="st">&quot;bar&quot;</span>);
}</code></pre></div>
<h5 id="options-38">Options</h5>
<p>AllowedTypes</p>
<p>A semicolon-separated list of names of types allowed to be initialized by copying. Regular expressions are accepted, e.g. [Rr]ef(erence)?$ matches every type with suffix Ref, ref, Reference and reference. The default is empty.</p>
<p>(Clang-Tidy original name: performance-unnecessary-copy-initialization)</p>


#### Unnecessary Value Param {#CT_PRF_UVP}
<p>Flags value parameter declarations of expensive to copy types that are copied for each invocation but it would suffice to pass them by const reference.</p>
<p>The check is only applied to parameters of types that are expensive to copy which means they are not trivially copyable or have a non-trivial copy constructor or destructor.</p>
<p>To ensure that it is safe to replace the value parameter with a const reference the following heuristic is employed:</p>
<ol style="list-style-type: decimal">
<li>the parameter is const qualified;</li>
<li>the parameter is not const, but only const methods or operators are invoked on it, or it is used as const reference or value argument in constructors or function calls.</li>
</ol>
<p>Example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> f(<span class="dt">const</span> string Value) {
  <span class="co">// The warning will suggest making Value a reference.</span>
}

<span class="dt">void</span> g(ExpensiveToCopy Value) {
  <span class="co">// The warning will suggest making Value a const reference.</span>
  Value.ConstMethd();
  ExpensiveToCopy Copy(Value);
}</code></pre></div>
<p>If the parameter is not const, only copied or assigned once and has a non-trivial move-constructor or move-assignment operator respectively the check will suggest to move it.</p>
<p>Example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> setValue(string Value) {
  Field = Value;
}</code></pre></div>
<p>Will become:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="ot">#include &lt;utility&gt;</span>

<span class="dt">void</span> setValue(string Value) {
  Field = std::move(Value);
}</code></pre></div>
<h5 id="options-37">Options</h5>
<p>IncludeStyle</p>
<p>A string specifying which include-style is used, llvm or google. Default is llvm.</p>
<p>AllowedTypes</p>
<p>A semicolon-separated list of names of types allowed to be passed by value. Regular expressions are accepted, e.g. [Rr]ef(erence)?$ matches every type with suffix Ref, ref, Reference and reference. The default is empty.</p>
<p>(Clang-Tidy original name: performance-unnecessary-value-param)</p>


### Portability

#### Restrict System Includes {#CT_PRT_RSI}
<p>Checks to selectively allow or disallow a configurable list of system headers.</p>
<p>For example:</p>
<p>In order to <strong>only</strong> allow zlib.h from the system you would set the options to -*,zlib.h.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="ot">#include &lt;curses.h&gt;       </span><span class="co">// Bad: disallowed system header.</span>
<span class="ot">#include &lt;openssl/ssl.h&gt;  </span><span class="co">// Bad: disallowed system header.</span>
<span class="ot">#include &lt;zlib.h&gt;         </span><span class="co">// Good: allowed system header.</span>
<span class="ot">#include &quot;src/myfile.h&quot;   </span><span class="co">// Good: non-system header always allowed.</span></code></pre></div>
<p>In order to allow everything <strong>except</strong> zlib.h from the system you would set the options to *,-zlib.h.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="ot">#include &lt;curses.h&gt;       </span><span class="co">// Good: allowed system header.</span>
<span class="ot">#include &lt;openssl/ssl.h&gt;  </span><span class="co">// Good: allowed system header.</span>
<span class="ot">#include &lt;zlib.h&gt;         </span><span class="co">// Bad: disallowed system header.</span>
<span class="ot">#include &quot;src/myfile.h&quot;   </span><span class="co">// Good: non-system header always allowed.</span></code></pre></div>
<p>Since the options support globbing you can use wildcarding to allow groups of headers.</p>
<p>-<em>,openssl/</em>.h will allow all openssl headers but disallow any others.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="ot">#include &lt;curses.h&gt;       </span><span class="co">// Bad: disallowed system header.</span>
<span class="ot">#include &lt;openssl/ssl.h&gt;  </span><span class="co">// Good: allowed system header.</span>
<span class="ot">#include &lt;openssl/rsa.h&gt;  </span><span class="co">// Good: allowed system header.</span>
<span class="ot">#include &lt;zlib.h&gt;         </span><span class="co">// Bad: disallowed system header.</span>
<span class="ot">#include &quot;src/myfile.h&quot;   </span><span class="co">// Good: non-system header always allowed.</span></code></pre></div>
<h5 id="options-35">Options</h5>
<p>Includes</p>
<p>A string containing a comma separated glob list of allowed include filenames. Similar to the -checks glob list for running clang-tidy itself, the two wildcard characters are * and -, to include and exclude globs, respectively. The default is *, which allows all includes.</p>
<p>(Clang-Tidy original name: portability-restrict-system-includes)</p>


#### Simd Intrinsics {#CT_PRT_SI}
<p>Finds SIMD intrinsics calls and suggests std::experimental::simd (<a href="https://wg21.link/p0214">P0214</a>) alternatives.</p>
<p>If the option <a href="#cmdoption-arg-suggest">Suggest</a> is set to true, for</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">_mm_add_epi32(a, b); <span class="co">// x86</span>
vec_add(a, b);       <span class="co">// Power</span></code></pre></div>
<p>the check suggests an alternative: operator+ on std::experimental::simd objects.</p>
<p>Otherwise, it just complains the intrinsics are non-portable (and there are <a href="https://wg21.link/p0214">P0214</a> alternatives).</p>
<p>Many architectures provide SIMD operations (e.g. x86 SSE/AVX, Power AltiVec/VSX, ARM NEON). It is common that SIMD code implementing the same algorithm, is written in multiple target-dispatching pieces to optimize for different architectures or micro-architectures.</p>
<p>The C++ standard proposal <a href="https://wg21.link/p0214">P0214</a> and its extensions cover many common SIMD operations. By migrating from target-dependent intrinsics to <a href="https://wg21.link/p0214">P0214</a> operations, the SIMD code can be simplified and pieces for different targets can be unified.</p>
<p>Refer to <a href="https://wg21.link/p0214">P0214</a> for introduction and motivation for the data-parallel standard library.</p>
<h5 id="options-40">Options</h5>
<p>Suggest</p>
<p>If this option is set to true (default is false), the check will suggest <a href="https://wg21.link/p0214">P0214</a> alternatives, otherwise it only points out the intrinsic function is non-portable.</p>
<p>Std</p>
<p>The namespace used to suggest <a href="https://wg21.link/p0214">P0214</a> alternatives. If not specified, std:: for -std=c++20 and std::experimental:: for -std=c++11.</p>
<p>(Clang-Tidy original name: portability-simd-intrinsics)</p>


### Readability

#### Avoid Const Params In Decls {#CT_RDB_ACPID}
<p>Checks whether a function declaration has parameters that are top level const.</p>
<p>const values in declarations do not affect the signature of a function, so they should not be put there.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> f(<span class="dt">const</span> string);   <span class="co">// Bad: const is top level.</span>
<span class="dt">void</span> f(<span class="dt">const</span> string&amp;);  <span class="co">// Good: const is not top level.</span></code></pre></div>
<p>(Clang-Tidy original name: readability-avoid-const-params-in-decls)</p>


#### Braces Around Statements {#CT_RDB_BAS}
<p>google-readability-braces-around-statements redirects here as an alias for this check.</p>
<p>Checks that bodies of if statements and loops (for, do while, and while) are inside braces.</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">if</span> (condition)
  statement;</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">if</span> (condition) {
  statement;
}</code></pre></div>
<h5 id="options-33">Options</h5>
<p>ShortStatementLines</p>
<p>Defines the minimal number of lines that the statement should have in order to trigger this check.</p>
<p>The number of lines is counted from the end of condition or initial keyword (do/else) until the last line of the inner statement. Default value 0 means that braces will be added to all statements (not having them already).</p>
<p>(Clang-Tidy original name: readability-braces-around-statements)</p>


#### Const Return Type {#CT_RDB_CRT}
<p>Checks for functions with a const-qualified return type and recommends removal of the const keyword. Such use of const is usually superfluous, and can prevent valuable compiler optimizations. Does not (yet) fix trailing return types.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">const</span> <span class="dt">int</span> foo();
<span class="dt">const</span> Clazz foo();
Clazz *<span class="dt">const</span> foo();</code></pre></div>
<p>Note that this applies strictly to top-level qualification, which excludes pointers or references to const values. For example, these are fine:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">const</span> <span class="dt">int</span>* foo();
<span class="dt">const</span> <span class="dt">int</span>&amp; foo();
<span class="dt">const</span> Clazz* foo();</code></pre></div>
<p>(Clang-Tidy original name: readability-const-return-type)</p>


#### Container Size Empty {#CT_RDB_CSE}
<p>Checks whether a call to the size() method can be replaced with a call to empty().</p>
<p>The emptiness of a container should be checked using the empty() method instead of the size() method. It is not guaranteed that size() is a constant-time function, and it is generally more efficient and also shows clearer intent to use empty(). Furthermore some containers may implement the empty() method but not implement the size() method. Using empty() whenever possible makes it easier to switch to another container in the future.</p>
<p>The check issues warning if a container has size() and empty() methods matching following signatures:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">size_type size() <span class="dt">const</span>;
<span class="dt">bool</span> empty() <span class="dt">const</span>;</code></pre></div>
<p>size_type can be any kind of integer type.</p>
<p>(Clang-Tidy original name: readability-container-size-empty)</p>


#### Convert Member Functions To Static {#CT_RDB_CMFTS}
<p>Finds non-static member functions that can be made static because the functions don’t use this.</p>
<p>After applying modifications as suggested by the check, running the check again might find more opportunities to mark member functions static.</p>
<p>After making a member function static, you might want to run the check <a href="readability-static-accessed-through-instance.html">readability-static-accessed-through-instance</a> to replace calls like Instance.method() by Class::method().</p>
<p>(Clang-Tidy original name: readability-convert-member-functions-to-static)</p>


#### Delete Null Pointer {#CT_RDB_DNP}
<p>Checks the if statements where a pointer’s existence is checked and then deletes the pointer. The check is unnecessary as deleting a null pointer has no effect.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">int</span> *p;
<span class="kw">if</span> (p)
  <span class="kw">delete</span> p;</code></pre></div>
<p>(Clang-Tidy original name: readability-delete-null-pointer)</p>


#### Deleted Default {#CT_RDB_DD}
<p>Checks that constructors and assignment operators marked as = default are not actually deleted by the compiler.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> Example {
<span class="kw">public</span>:
  <span class="co">// This constructor is deleted because I is missing a default value.</span>
  Example() = <span class="kw">default</span>;
  <span class="co">// This is fine.</span>
  Example(<span class="dt">const</span> Example&amp; Other) = <span class="kw">default</span>;
  <span class="co">// This operator is deleted because I cannot be assigned (it is const).</span>
  Example&amp; <span class="kw">operator</span>=(<span class="dt">const</span> Example&amp; Other) = <span class="kw">default</span>;

<span class="kw">private</span>:
  <span class="dt">const</span> <span class="dt">int</span> I;
};</code></pre></div>
<p>(Clang-Tidy original name: readability-deleted-default)</p>


#### Else After Return {#CT_RDB_EAR}
<p><a href="https://llvm.org/docs/CodingStandards.html">LLVM Coding Standards</a> advises to reduce indentation where possible and where it makes understanding code easier. Early exit is one of the suggested enforcements of that. Please do not use else or else if after something that interrupts control flow - like return, break, continue, throw.</p>
<p>The following piece of code illustrates how the check works. This piece of code:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> foo(<span class="dt">int</span> Value) {
  <span class="dt">int</span> Local = <span class="dv">0</span>;
  <span class="kw">for</span> (<span class="dt">int</span> i = <span class="dv">0</span>; i &lt; <span class="dv">42</span>; i++) {
    <span class="kw">if</span> (Value == <span class="dv">1</span>) {
      <span class="kw">return</span>;
    } <span class="kw">else</span> {
      Local++;
    }

    <span class="kw">if</span> (Value == <span class="dv">2</span>)
      <span class="kw">continue</span>;
    <span class="kw">else</span>
      Local++;

    <span class="kw">if</span> (Value == <span class="dv">3</span>) {
      <span class="kw">throw</span> <span class="dv">42</span>;
    } <span class="kw">else</span> {
      Local++;
    }
  }
}</code></pre></div>
<p>Would be transformed into:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> foo(<span class="dt">int</span> Value) {
  <span class="dt">int</span> Local = <span class="dv">0</span>;
  <span class="kw">for</span> (<span class="dt">int</span> i = <span class="dv">0</span>; i &lt; <span class="dv">42</span>; i++) {
    <span class="kw">if</span> (Value == <span class="dv">1</span>) {
      <span class="kw">return</span>;
    }
    Local++;

    <span class="kw">if</span> (Value == <span class="dv">2</span>)
      <span class="kw">continue</span>;
    Local++;

    <span class="kw">if</span> (Value == <span class="dv">3</span>) {
      <span class="kw">throw</span> <span class="dv">42</span>;
    }
    Local++;
  }
}</code></pre></div>
<h5 id="options-75">Options</h5>
<p>WarnOnUnfixable</p>
<p>When true, emit a warning for cases where the check can’t output a Fix-It. These can occur with declarations inside the else branch that would have an extended lifetime if the else branch was removed. Default value is true.</p>
<p>WarnOnConditionVariables</p>
<p>When true, the check will attempt to refactor a variable defined inside the condition of the if statement that is used in the else branch defining them just before the if statement. This can only be done if the if statement is the last statement in its parents scope. Default value is true.</p>
<h5 id="llvm-alias">LLVM alias</h5>
<p>There is an alias of this check called llvm-else-after-return. In that version the options <a href="#cmdoption-arg-warnonunfixable">WarnOnUnfixable</a> and <a href="#cmdoption-arg-warnonconditionvariables">WarnOnConditionVariables</a> are both set to false by default.</p>
<p>This check helps to enforce this <a href="https://llvm.org/docs/CodingStandards.html#don-t-use-else-after-a-return">LLVM Coding Standards recommendation</a>.</p>
<p>(Clang-Tidy original name: readability-else-after-return)</p>


#### Function Cognitive Complexity {#CT_RDB_FCC}
<p>Checks function Cognitive Complexity metric.</p>
<p>The metric is implemented as per the <a href="https://www.sonarsource.com/docs/CognitiveComplexity.pdf">COGNITIVE COMPLEXITY by SonarSource</a> specification version 1.2 (19 April 2017).</p>
<h5 id="options-1">Options</h5>
<p>Threshold</p>
<p>Flag functions with Cognitive Complexity exceeding this number. The default is 25.</p>
<h5 id="building-blocks">Building blocks</h5>
<p>There are three basic building blocks of a Cognitive Complexity metric:</p>
<h6 id="increment">Increment</h6>
<p>The following structures increase the function’s Cognitive Complexity metric (by 1):</p>
<ul>
<li><p>Conditional operators:</p>
<ul>
<li>if()</li>
<li>else if()</li>
<li>else</li>
<li>cond ? true : false</li>
</ul></li>
<li><p>switch()</p></li>
<li><p>Loops:</p>
<ul>
<li>for()</li>
<li>C++11 range-based for()</li>
<li>while()</li>
<li>do while()</li>
</ul></li>
<li><p>catch ()</p></li>
<li><p>goto LABEL, goto *(&amp;&amp;LABEL)),</p></li>
<li><p>sequences of binary logical operators:</p>
<ul>
<li>boolean1 || boolean2</li>
<li>boolean1 &amp;&amp; boolean2</li>
</ul></li>
</ul>
<h6 id="nesting-level">Nesting level</h6>
<p>While by itself the nesting level not change the function’s Cognitive Complexity metric, it is tracked, and is used by the next, third building block. The following structures increase the nesting level (by 1):</p>
<ul>
<li><p>Conditional operators:</p>
<ul>
<li>if()</li>
<li>else if()</li>
<li>else</li>
<li>cond ? true : false</li>
</ul></li>
<li><p>switch()</p></li>
<li><p>Loops:</p>
<ul>
<li>for()</li>
<li>C++11 range-based for()</li>
<li>while()</li>
<li>do while()</li>
</ul></li>
<li><p>catch ()</p></li>
<li><p>Nested functions:</p>
<ul>
<li>C++11 Lambda</li>
<li>Nested class</li>
<li>Nested struct</li>
</ul></li>
<li><p>GNU statement expression</p></li>
<li><p>Apple Block Declaration</p></li>
</ul>
<h6 id="nesting-increment">Nesting increment</h6>
<p>This is where the previous basic building block, <a href="#nesting-level">Nesting level</a>, matters. The following structures increase the function’s Cognitive Complexity metric by the current <a href="#nesting-level">Nesting level</a>:</p>
<ul>
<li><p>Conditional operators:</p>
<ul>
<li>if()</li>
<li>cond ? true : false</li>
</ul></li>
<li><p>switch()</p></li>
<li><p>Loops:</p>
<ul>
<li>for()</li>
<li>C++11 range-based for()</li>
<li>while()</li>
<li>do while()</li>
</ul></li>
<li><p>catch ()</p></li>
</ul>
<h5 id="examples">Examples</h5>
<p>The simplest case. This function has Cognitive Complexity of 0.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> function0() {}</code></pre></div>
<p>Slightly better example. This function has Cognitive Complexity of 1.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">int</span> function1(<span class="dt">bool</span> var) {
  <span class="kw">if</span>(var) <span class="co">// +1, nesting level +1</span>
    <span class="kw">return</span> <span class="dv">42</span>;
  <span class="kw">return</span> <span class="dv">0</span>;
}</code></pre></div>
<p>Full example. This function has Cognitive Complexity of 3.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">int</span> function3(<span class="dt">bool</span> var1, <span class="dt">bool</span> var2) {
  <span class="kw">if</span>(var1) { <span class="co">// +1, nesting level +1</span>
    <span class="kw">if</span>(var2)  <span class="co">// +2 (1 + current nesting level of 1), nesting level +1</span>
      <span class="kw">return</span> <span class="dv">42</span>;
  }

  <span class="kw">return</span> <span class="dv">0</span>;
}</code></pre></div>
<h5 id="limitations">Limitations</h5>
<p>The metric is implemented with two notable exceptions:</p>
<ul>
<li>preprocessor conditionals (#ifdef, #if, #elif, #else, #endif) are not accounted for.</li>
<li>each method in a recursion cycle is not accounted for. It can’t be fully implemented, because cross-translational-unit analysis would be needed, which is currently not possible in clang-tidy.</li>
</ul>
<p>(Clang-Tidy original name: readability-function-cognitive-complexity)</p>


#### Function Size {#CT_RDB_FS}
<p>google-readability-function-size redirects here as an alias for this check.</p>
<p>Checks for large functions based on various metrics.</p>
<h5 id="options-31">Options</h5>
<p>LineThreshold</p>
<p>Flag functions exceeding this number of lines. The default is -1 (ignore the number of lines).</p>
<p>StatementThreshold</p>
<p>Flag functions exceeding this number of statements. This may differ significantly from the number of lines for macro-heavy code. The default is 800.</p>
<p>BranchThreshold</p>
<p>Flag functions exceeding this number of control statements. The default is -1 (ignore the number of branches).</p>
<p>ParameterThreshold</p>
<p>Flag functions that exceed a specified number of parameters. The default is -1 (ignore the number of parameters).</p>
<p>NestingThreshold</p>
<p>Flag compound statements which create next nesting level after NestingThreshold. This may differ significantly from the expected value for macro-heavy code. The default is -1 (ignore the nesting level).</p>
<p>VariableThreshold</p>
<p>Flag functions exceeding this number of variables declared in the body. The default is -1 (ignore the number of variables). Please note that function parameters and variables declared in lambdas, GNU Statement Expressions, and nested class inline functions are not counted.</p>
<p>(Clang-Tidy original name: readability-function-size)</p>


#### Identifier Naming {#CT_RDB_IN}
<p>Checks for identifiers naming style mismatch.</p>
<p>This check will try to enforce coding guidelines on the identifiers naming. It supports one of the following casing types and tries to convert from one to another if a mismatch is detected</p>
<p>Casing types include:</p>
<ul>
<li>lower_case,</li>
<li>UPPER_CASE,</li>
<li>camelBack,</li>
<li>CamelCase,</li>
<li>camel_Snake_Back,</li>
<li>Camel_Snake_Case,</li>
<li>aNy_CasE.</li>
</ul>
<p>It also supports a fixed prefix and suffix that will be prepended or appended to the identifiers, regardless of the casing.</p>
<p>Many configuration options are available, in order to be able to create different rules for different kinds of identifiers. In general, the rules are falling back to a more generic rule if the specific case is not configured.</p>
<p>The naming of virtual methods is reported where they occur in the base class, but not where they are overridden, as it can’t be fixed locally there. This also applies for pseudo-override patterns like CRTP.</p>
<h5 id="options-27">Options</h5>
<p>The following options are describe below:</p>
<ul>
<li><a href="#cmdoption-arg-abstractclasscase">AbstractClassCase</a>, <a href="#cmdoption-arg-abstractclassprefix">AbstractClassPrefix</a>, <a href="#cmdoption-arg-abstractclasssuffix">AbstractClassSuffix</a>, <a href="#cmdoption-arg-abstractclassignoredregexp">AbstractClassIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-aggressivedependentmemberlookup">AggressiveDependentMemberLookup</a></li>
<li><a href="#cmdoption-arg-classcase">ClassCase</a>, <a href="#cmdoption-arg-classprefix">ClassPrefix</a>, <a href="#cmdoption-arg-classsuffix">ClassSuffix</a>, <a href="#cmdoption-arg-classignoredregexp">ClassIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-classconstantcase">ClassConstantCase</a>, <a href="#cmdoption-arg-classconstantprefix">ClassConstantPrefix</a>, <a href="#cmdoption-arg-classconstantsuffix">ClassConstantSuffix</a>, <a href="#cmdoption-arg-classconstantignoredregexp">ClassConstantIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-classmembercase">ClassMemberCase</a>, <a href="#cmdoption-arg-classmemberprefix">ClassMemberPrefix</a>, <a href="#cmdoption-arg-classmembersuffix">ClassMemberSuffix</a>, <a href="#cmdoption-arg-classmemberignoredregexp">ClassMemberIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-classmethodcase">ClassMethodCase</a>, <a href="#cmdoption-arg-classmethodprefix">ClassMethodPrefix</a>, <a href="#cmdoption-arg-classmethodsuffix">ClassMethodSuffix</a>, <a href="#cmdoption-arg-classmethodignoredregexp">ClassMethodIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-constantcase">ConstantCase</a>, <a href="#cmdoption-arg-constantprefix">ConstantPrefix</a>, <a href="#cmdoption-arg-constantsuffix">ConstantSuffix</a>, <a href="#cmdoption-arg-constantignoredregexp">ConstantIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-constantmembercase">ConstantMemberCase</a>, <a href="#cmdoption-arg-constantmemberprefix">ConstantMemberPrefix</a>, <a href="#cmdoption-arg-constantmembersuffix">ConstantMemberSuffix</a>, <a href="#cmdoption-arg-constantmemberignoredregexp">ConstantMemberIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-constantparametercase">ConstantParameterCase</a>, <a href="#cmdoption-arg-constantparameterprefix">ConstantParameterPrefix</a>, <a href="#cmdoption-arg-constantparametersuffix">ConstantParameterSuffix</a>, <a href="#cmdoption-arg-constantparameterignoredregexp">ConstantParameterIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-constantpointerparametercase">ConstantPointerParameterCase</a>, <a href="#cmdoption-arg-constantpointerparameterprefix">ConstantPointerParameterPrefix</a>, <a href="#cmdoption-arg-constantpointerparametersuffix">ConstantPointerParameterSuffix</a>, <a href="#cmdoption-arg-constantpointerparameterignoredregexp">ConstantPointerParameterIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-constexprfunctioncase">ConstexprFunctionCase</a>, <a href="#cmdoption-arg-constexprfunctionprefix">ConstexprFunctionPrefix</a>, <a href="#cmdoption-arg-constexprfunctionsuffix">ConstexprFunctionSuffix</a>, <a href="#cmdoption-arg-constexprfunctionignoredregexp">ConstexprFunctionIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-constexprmethodcase">ConstexprMethodCase</a>, <a href="#cmdoption-arg-constexprmethodprefix">ConstexprMethodPrefix</a>, <a href="#cmdoption-arg-constexprmethodsuffix">ConstexprMethodSuffix</a>, <a href="#cmdoption-arg-constexprmethodignoredregexp">ConstexprMethodIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-constexprvariablecase">ConstexprVariableCase</a>, <a href="#cmdoption-arg-constexprvariableprefix">ConstexprVariablePrefix</a>, <a href="#cmdoption-arg-constexprvariablesuffix">ConstexprVariableSuffix</a>, <a href="#cmdoption-arg-constexprvariableignoredregexp">ConstexprVariableIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-enumcase">EnumCase</a>, <a href="#cmdoption-arg-enumprefix">EnumPrefix</a>, <a href="#cmdoption-arg-enumsuffix">EnumSuffix</a>, <a href="#cmdoption-arg-enumignoredregexp">EnumIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-enumconstantcase">EnumConstantCase</a>, <a href="#cmdoption-arg-enumconstantprefix">EnumConstantPrefix</a>, <a href="#cmdoption-arg-enumconstantsuffix">EnumConstantSuffix</a>, <a href="#cmdoption-arg-enumconstantignoredregexp">EnumConstantIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-functioncase">FunctionCase</a>, <a href="#cmdoption-arg-functionprefix">FunctionPrefix</a>, <a href="#cmdoption-arg-functionsuffix">FunctionSuffix</a>, <a href="#cmdoption-arg-functionignoredregexp">FunctionIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-getconfigperfile">GetConfigPerFile</a></li>
<li><a href="#cmdoption-arg-globalconstantcase">GlobalConstantCase</a>, <a href="#cmdoption-arg-globalconstantprefix">GlobalConstantPrefix</a>, <a href="#cmdoption-arg-globalconstantsuffix">GlobalConstantSuffix</a>, <a href="#cmdoption-arg-globalconstantignoredregexp">GlobalConstantIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-globalconstantpointercase">GlobalConstantPointerCase</a>, <a href="#cmdoption-arg-globalconstantpointerprefix">GlobalConstantPointerPrefix</a>, <a href="#cmdoption-arg-globalconstantpointersuffix">GlobalConstantPointerSuffix</a>, <a href="#cmdoption-arg-globalconstantpointerignoredregexp">GlobalConstantPointerIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-globalfunctioncase">GlobalFunctionCase</a>, <a href="#cmdoption-arg-globalfunctionprefix">GlobalFunctionPrefix</a>, <a href="#cmdoption-arg-globalfunctionsuffix">GlobalFunctionSuffix</a>, <a href="#cmdoption-arg-globalfunctionignoredregexp">GlobalFunctionIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-globalpointercase">GlobalPointerCase</a>, <a href="#cmdoption-arg-globalpointerprefix">GlobalPointerPrefix</a>, <a href="#cmdoption-arg-globalpointersuffix">GlobalPointerSuffix</a>, <a href="#cmdoption-arg-globalpointerignoredregexp">GlobalPointerIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-globalvariablecase">GlobalVariableCase</a>, <a href="#cmdoption-arg-globalvariableprefix">GlobalVariablePrefix</a>, <a href="#cmdoption-arg-globalvariablesuffix">GlobalVariableSuffix</a>, <a href="#cmdoption-arg-globalvariableignoredregexp">GlobalVariableIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-ignoremainlikefunctions">IgnoreMainLikeFunctions</a></li>
<li><a href="#cmdoption-arg-inlinenamespacecase">InlineNamespaceCase</a>, <a href="#cmdoption-arg-inlinenamespaceprefix">InlineNamespacePrefix</a>, <a href="#cmdoption-arg-inlinenamespacesuffix">InlineNamespaceSuffix</a>, <a href="#cmdoption-arg-inlinenamespaceignoredregexp">InlineNamespaceIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-localconstantcase">LocalConstantCase</a>, <a href="#cmdoption-arg-localconstantprefix">LocalConstantPrefix</a>, <a href="#cmdoption-arg-localconstantsuffix">LocalConstantSuffix</a>, <a href="#cmdoption-arg-localconstantignoredregexp">LocalConstantIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-localconstantpointercase">LocalConstantPointerCase</a>, <a href="#cmdoption-arg-localconstantpointerprefix">LocalConstantPointerPrefix</a>, <a href="#cmdoption-arg-localconstantpointersuffix">LocalConstantPointerSuffix</a>, <a href="#cmdoption-arg-localconstantpointerignoredregexp">LocalConstantPointerIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-localpointercase">LocalPointerCase</a>, <a href="#cmdoption-arg-localpointerprefix">LocalPointerPrefix</a>, <a href="#cmdoption-arg-localpointersuffix">LocalPointerSuffix</a>, <a href="#cmdoption-arg-localpointerignoredregexp">LocalPointerIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-localvariablecase">LocalVariableCase</a>, <a href="#cmdoption-arg-localvariableprefix">LocalVariablePrefix</a>, <a href="#cmdoption-arg-localvariablesuffix">LocalVariableSuffix</a>, <a href="#cmdoption-arg-localvariableignoredregexp">LocalVariableIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-macrodefinitioncase">MacroDefinitionCase</a>, <a href="#cmdoption-arg-macrodefinitionprefix">MacroDefinitionPrefix</a>, <a href="#cmdoption-arg-macrodefinitionsuffix">MacroDefinitionSuffix</a>, <a href="#cmdoption-arg-macrodefinitionignoredregexp">MacroDefinitionIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-membercase">MemberCase</a>, <a href="#cmdoption-arg-memberprefix">MemberPrefix</a>, <a href="#cmdoption-arg-membersuffix">MemberSuffix</a>, <a href="#cmdoption-arg-memberignoredregexp">MemberIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-methodcase">MethodCase</a>, <a href="#cmdoption-arg-methodprefix">MethodPrefix</a>, <a href="#cmdoption-arg-methodsuffix">MethodSuffix</a>, <a href="#cmdoption-arg-methodignoredregexp">MethodIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-namespacecase">NamespaceCase</a>, <a href="#cmdoption-arg-namespaceprefix">NamespacePrefix</a>, <a href="#cmdoption-arg-namespacesuffix">NamespaceSuffix</a>, <a href="#cmdoption-arg-namespaceignoredregexp">NamespaceIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-parametercase">ParameterCase</a>, <a href="#cmdoption-arg-parameterprefix">ParameterPrefix</a>, <a href="#cmdoption-arg-parametersuffix">ParameterSuffix</a>, <a href="#cmdoption-arg-parameterignoredregexp">ParameterIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-parameterpackcase">ParameterPackCase</a>, <a href="#cmdoption-arg-parameterpackprefix">ParameterPackPrefix</a>, <a href="#cmdoption-arg-parameterpacksuffix">ParameterPackSuffix</a>, <a href="#cmdoption-arg-parameterpackignoredregexp">ParameterPackIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-pointerparametercase">PointerParameterCase</a>, <a href="#cmdoption-arg-pointerparameterprefix">PointerParameterPrefix</a>, <a href="#cmdoption-arg-pointerparametersuffix">PointerParameterSuffix</a>, <a href="#cmdoption-arg-pointerparameterignoredregexp">PointerParameterIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-privatemembercase">PrivateMemberCase</a>, <a href="#cmdoption-arg-privatememberprefix">PrivateMemberPrefix</a>, <a href="#cmdoption-arg-privatemembersuffix">PrivateMemberSuffix</a>, <a href="#cmdoption-arg-privatememberignoredregexp">PrivateMemberIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-privatemethodcase">PrivateMethodCase</a>, <a href="#cmdoption-arg-privatemethodprefix">PrivateMethodPrefix</a>, <a href="#cmdoption-arg-privatemethodsuffix">PrivateMethodSuffix</a>, <a href="#cmdoption-arg-privatemethodignoredregexp">PrivateMethodIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-protectedmembercase">ProtectedMemberCase</a>, <a href="#cmdoption-arg-protectedmemberprefix">ProtectedMemberPrefix</a>, <a href="#cmdoption-arg-protectedmembersuffix">ProtectedMemberSuffix</a>, <a href="#cmdoption-arg-protectedmemberignoredregexp">ProtectedMemberIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-protectedmethodcase">ProtectedMethodCase</a>, <a href="#cmdoption-arg-protectedmethodprefix">ProtectedMethodPrefix</a>, <a href="#cmdoption-arg-protectedmethodsuffix">ProtectedMethodSuffix</a>, <a href="#cmdoption-arg-protectedmethodignoredregexp">ProtectedMethodIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-publicmembercase">PublicMemberCase</a>, <a href="#cmdoption-arg-publicmemberprefix">PublicMemberPrefix</a>, <a href="#cmdoption-arg-publicmembersuffix">PublicMemberSuffix</a>, <a href="#cmdoption-arg-publicmemberignoredregexp">PublicMemberIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-publicmethodcase">PublicMethodCase</a>, <a href="#cmdoption-arg-publicmethodprefix">PublicMethodPrefix</a>, <a href="#cmdoption-arg-publicmethodsuffix">PublicMethodSuffix</a>, <a href="#cmdoption-arg-publicmethodignoredregexp">PublicMethodIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-scopedenumconstantcase">ScopedEnumConstantCase</a>, <a href="#cmdoption-arg-scopedenumconstantprefix">ScopedEnumConstantPrefix</a>, <a href="#cmdoption-arg-scopedenumconstantsuffix">ScopedEnumConstantSuffix</a>, <a href="#cmdoption-arg-scopedenumconstantignoredregexp">ScopedEnumConstantIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-staticconstantcase">StaticConstantCase</a>, <a href="#cmdoption-arg-staticconstantprefix">StaticConstantPrefix</a>, <a href="#cmdoption-arg-staticconstantsuffix">StaticConstantSuffix</a>, <a href="#cmdoption-arg-staticconstantignoredregexp">StaticConstantIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-staticvariablecase">StaticVariableCase</a>, <a href="#cmdoption-arg-staticvariableprefix">StaticVariablePrefix</a>, <a href="#cmdoption-arg-staticvariablesuffix">StaticVariableSuffix</a>, <a href="#cmdoption-arg-staticvariableignoredregexp">StaticVariableIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-structcase">StructCase</a>, <a href="#cmdoption-arg-structprefix">StructPrefix</a>, <a href="#cmdoption-arg-structsuffix">StructSuffix</a>, <a href="#cmdoption-arg-structignoredregexp">StructIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-templateparametercase">TemplateParameterCase</a>, <a href="#cmdoption-arg-templateparameterprefix">TemplateParameterPrefix</a>, <a href="#cmdoption-arg-templateparametersuffix">TemplateParameterSuffix</a>, <a href="#cmdoption-arg-templateparameterignoredregexp">TemplateParameterIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-templatetemplateparametercase">TemplateTemplateParameterCase</a>, <a href="#cmdoption-arg-templatetemplateparameterprefix">TemplateTemplateParameterPrefix</a>, <a href="#cmdoption-arg-templatetemplateparametersuffix">TemplateTemplateParameterSuffix</a>, <a href="#cmdoption-arg-templatetemplateparameterignoredregexp">TemplateTemplateParameterIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-typealiascase">TypeAliasCase</a>, <a href="#cmdoption-arg-typealiasprefix">TypeAliasPrefix</a>, <a href="#cmdoption-arg-typealiassuffix">TypeAliasSuffix</a>, <a href="#cmdoption-arg-typealiasignoredregexp">TypeAliasIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-typedefcase">TypedefCase</a>, <a href="#cmdoption-arg-typedefprefix">TypedefPrefix</a>, <a href="#cmdoption-arg-typedefsuffix">TypedefSuffix</a>, <a href="#cmdoption-arg-typedefignoredregexp">TypedefIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-typetemplateparametercase">TypeTemplateParameterCase</a>, <a href="#cmdoption-arg-typetemplateparameterprefix">TypeTemplateParameterPrefix</a>, <a href="#cmdoption-arg-typetemplateparametersuffix">TypeTemplateParameterSuffix</a>, <a href="#cmdoption-arg-typetemplateparameterignoredregexp">TypeTemplateParameterIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-unioncase">UnionCase</a>, <a href="#cmdoption-arg-unionprefix">UnionPrefix</a>, <a href="#cmdoption-arg-unionsuffix">UnionSuffix</a>, <a href="#cmdoption-arg-unionignoredregexp">UnionIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-valuetemplateparametercase">ValueTemplateParameterCase</a>, <a href="#cmdoption-arg-valuetemplateparameterprefix">ValueTemplateParameterPrefix</a>, <a href="#cmdoption-arg-valuetemplateparametersuffix">ValueTemplateParameterSuffix</a>, <a href="#cmdoption-arg-valuetemplateparameterignoredregexp">ValueTemplateParameterIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-variablecase">VariableCase</a>, <a href="#cmdoption-arg-variableprefix">VariablePrefix</a>, <a href="#cmdoption-arg-variablesuffix">VariableSuffix</a>, <a href="#cmdoption-arg-variableignoredregexp">VariableIgnoredRegexp</a></li>
<li><a href="#cmdoption-arg-virtualmethodcase">VirtualMethodCase</a>, <a href="#cmdoption-arg-virtualmethodprefix">VirtualMethodPrefix</a>, <a href="#cmdoption-arg-virtualmethodsuffix">VirtualMethodSuffix</a>, <a href="#cmdoption-arg-virtualmethodignoredregexp">VirtualMethodIgnoredRegexp</a></li>
</ul>
<p>AbstractClassCase</p>
<p>When defined, the check will ensure abstract class names conform to the selected casing.</p>
<p>AbstractClassPrefix</p>
<p>When defined, the check will ensure abstract class names will add the prefixed with the given value (regardless of casing).</p>
<p>AbstractClassIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for abstract class names matching this regular expression.</p>
<p>AbstractClassSuffix</p>
<p>When defined, the check will ensure abstract class names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>AbstractClassCase of lower_case</li>
<li>AbstractClassPrefix of pre_</li>
<li>AbstractClassSuffix of _post</li>
</ul>
<p>Identifies and/or transforms abstract class names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> ABSTRACT_CLASS {
<span class="kw">public</span>:
  ABSTRACT_CLASS();
};</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> pre_abstract_class_post {
<span class="kw">public</span>:
  pre_abstract_class_post();
};</code></pre></div>
<p>AggressiveDependentMemberLookup</p>
<p>When set to true the check will look in dependent base classes for dependent member references that need changing. This can lead to errors with template specializations so the default value is false.</p>
<p>For example using values of:</p>
<ul>
<li>ClassMemberCase of lower_case</li>
</ul>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">template</span> &lt;<span class="kw">typename</span> T&gt;
<span class="kw">struct</span> Base {
  T BadNamedMember;
};

<span class="kw">template</span> &lt;<span class="kw">typename</span> T&gt;
<span class="kw">struct</span> Derived : Base&lt;T&gt; {
  <span class="dt">void</span> reset() {
    <span class="kw">this</span>-&gt;BadNamedMember = <span class="dv">0</span>;
  }
};</code></pre></div>
<p>After if AggressiveDependentMemberLookup is false:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">template</span> &lt;<span class="kw">typename</span> T&gt;
<span class="kw">struct</span> Base {
  T bad_named_member;
};

<span class="kw">template</span> &lt;<span class="kw">typename</span> T&gt;
<span class="kw">struct</span> Derived : Base&lt;T&gt; {
  <span class="dt">void</span> reset() {
    <span class="kw">this</span>-&gt;BadNamedMember = <span class="dv">0</span>;
  }
};</code></pre></div>
<p>After if AggressiveDependentMemberLookup is true:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">template</span> &lt;<span class="kw">typename</span> T&gt;
<span class="kw">struct</span> Base {
  T bad_named_member;
};

<span class="kw">template</span> &lt;<span class="kw">typename</span> T&gt;
<span class="kw">struct</span> Derived : Base&lt;T&gt; {
  <span class="dt">void</span> reset() {
    <span class="kw">this</span>-&gt;bad_named_member = <span class="dv">0</span>;
  }
};</code></pre></div>
<p>ClassCase</p>
<p>When defined, the check will ensure class names conform to the selected casing.</p>
<p>ClassPrefix</p>
<p>When defined, the check will ensure class names will add the prefixed with the given value (regardless of casing).</p>
<p>ClassIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for class names matching this regular expression.</p>
<p>ClassSuffix</p>
<p>When defined, the check will ensure class names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>ClassCase of lower_case</li>
<li>ClassPrefix of pre_</li>
<li>ClassSuffix of _post</li>
</ul>
<p>Identifies and/or transforms class names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> FOO {
<span class="kw">public</span>:
  FOO();
  ~FOO();
};</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> pre_foo_post {
<span class="kw">public</span>:
  pre_foo_post();
  ~pre_foo_post();
};</code></pre></div>
<p>ClassConstantCase</p>
<p>When defined, the check will ensure class constant names conform to the selected casing.</p>
<p>ClassConstantPrefix</p>
<p>When defined, the check will ensure class constant names will add the prefixed with the given value (regardless of casing).</p>
<p>ClassConstantIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for class constant names matching this regular expression.</p>
<p>ClassConstantSuffix</p>
<p>When defined, the check will ensure class constant names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>ClassConstantCase of lower_case</li>
<li>ClassConstantPrefix of pre_</li>
<li>ClassConstantSuffix of _post</li>
</ul>
<p>Identifies and/or transforms class constant names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> FOO {
<span class="kw">public</span>:
  <span class="dt">static</span> <span class="dt">const</span> <span class="dt">int</span> CLASS_CONSTANT;
};</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> FOO {
<span class="kw">public</span>:
  <span class="dt">static</span> <span class="dt">const</span> <span class="dt">int</span> pre_class_constant_post;
};</code></pre></div>
<p>ClassMemberCase</p>
<p>When defined, the check will ensure class member names conform to the selected casing.</p>
<p>ClassMemberPrefix</p>
<p>When defined, the check will ensure class member names will add the prefixed with the given value (regardless of casing).</p>
<p>ClassMemberIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for class member names matching this regular expression.</p>
<p>ClassMemberSuffix</p>
<p>When defined, the check will ensure class member names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>ClassMemberCase of lower_case</li>
<li>ClassMemberPrefix of pre_</li>
<li>ClassMemberSuffix of _post</li>
</ul>
<p>Identifies and/or transforms class member names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> FOO {
<span class="kw">public</span>:
  <span class="dt">static</span> <span class="dt">int</span> CLASS_CONSTANT;
};</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> FOO {
<span class="kw">public</span>:
  <span class="dt">static</span> <span class="dt">int</span> pre_class_constant_post;
};</code></pre></div>
<p>ClassMethodCase</p>
<p>When defined, the check will ensure class method names conform to the selected casing.</p>
<p>ClassMethodPrefix</p>
<p>When defined, the check will ensure class method names will add the prefixed with the given value (regardless of casing).</p>
<p>ClassMethodIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for class method names matching this regular expression.</p>
<p>ClassMethodSuffix</p>
<p>When defined, the check will ensure class method names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>ClassMethodCase of lower_case</li>
<li>ClassMethodPrefix of pre_</li>
<li>ClassMethodSuffix of _post</li>
</ul>
<p>Identifies and/or transforms class method names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> FOO {
<span class="kw">public</span>:
  <span class="dt">int</span> CLASS_MEMBER();
};</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> FOO {
<span class="kw">public</span>:
  <span class="dt">int</span> pre_class_member_post();
};</code></pre></div>
<p>ConstantCase</p>
<p>When defined, the check will ensure constant names conform to the selected casing.</p>
<p>ConstantPrefix</p>
<p>When defined, the check will ensure constant names will add the prefixed with the given value (regardless of casing).</p>
<p>ConstantIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for constant names matching this regular expression.</p>
<p>ConstantSuffix</p>
<p>When defined, the check will ensure constant names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>ConstantCase of lower_case</li>
<li>ConstantPrefix of pre_</li>
<li>ConstantSuffix of _post</li>
</ul>
<p>Identifies and/or transforms constant names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> function() { <span class="dt">unsigned</span> <span class="dt">const</span> MyConst_array[] = {<span class="dv">1</span>, <span class="dv">2</span>, <span class="dv">3</span>}; }</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> function() { <span class="dt">unsigned</span> <span class="dt">const</span> pre_myconst_array_post[] = {<span class="dv">1</span>, <span class="dv">2</span>, <span class="dv">3</span>}; }</code></pre></div>
<p>ConstantMemberCase</p>
<p>When defined, the check will ensure constant member names conform to the selected casing.</p>
<p>ConstantMemberPrefix</p>
<p>When defined, the check will ensure constant member names will add the prefixed with the given value (regardless of casing).</p>
<p>ConstantMemberIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for constant member names matching this regular expression.</p>
<p>ConstantMemberSuffix</p>
<p>When defined, the check will ensure constant member names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>ConstantMemberCase of lower_case</li>
<li>ConstantMemberPrefix of pre_</li>
<li>ConstantMemberSuffix of _post</li>
</ul>
<p>Identifies and/or transforms constant member names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> Foo {
  <span class="dt">char</span> <span class="dt">const</span> MY_ConstMember_string[<span class="dv">4</span>] = <span class="st">&quot;123&quot;</span>;
}</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> Foo {
  <span class="dt">char</span> <span class="dt">const</span> pre_my_constmember_string_post[<span class="dv">4</span>] = <span class="st">&quot;123&quot;</span>;
}</code></pre></div>
<p>ConstantParameterCase</p>
<p>When defined, the check will ensure constant parameter names conform to the selected casing.</p>
<p>ConstantParameterPrefix</p>
<p>When defined, the check will ensure constant parameter names will add the prefixed with the given value (regardless of casing).</p>
<p>ConstantParameterIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for constant parameter names matching this regular expression.</p>
<p>ConstantParameterSuffix</p>
<p>When defined, the check will ensure constant parameter names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>ConstantParameterCase of lower_case</li>
<li>ConstantParameterPrefix of pre_</li>
<li>ConstantParameterSuffix of _post</li>
</ul>
<p>Identifies and/or transforms constant parameter names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> GLOBAL_FUNCTION(<span class="dt">int</span> PARAMETER_1, <span class="dt">int</span> <span class="dt">const</span> CONST_parameter);</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> GLOBAL_FUNCTION(<span class="dt">int</span> PARAMETER_1, <span class="dt">int</span> <span class="dt">const</span> pre_const_parameter_post);</code></pre></div>
<p>ConstantPointerParameterCase</p>
<p>When defined, the check will ensure constant pointer parameter names conform to the selected casing.</p>
<p>ConstantPointerParameterPrefix</p>
<p>When defined, the check will ensure constant pointer parameter names will add the prefixed with the given value (regardless of casing).</p>
<p>ConstantPointerParameterIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for constant pointer parameter names matching this regular expression.</p>
<p>ConstantPointerParameterSuffix</p>
<p>When defined, the check will ensure constant pointer parameter names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>ConstantPointerParameterCase of lower_case</li>
<li>ConstantPointerParameterPrefix of pre_</li>
<li>ConstantPointerParameterSuffix of _post</li>
</ul>
<p>Identifies and/or transforms constant pointer parameter names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> GLOBAL_FUNCTION(<span class="dt">int</span> <span class="dt">const</span> *CONST_parameter);</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> GLOBAL_FUNCTION(<span class="dt">int</span> <span class="dt">const</span> *pre_const_parameter_post);</code></pre></div>
<p>ConstexprFunctionCase</p>
<p>When defined, the check will ensure constexpr function names conform to the selected casing.</p>
<p>ConstexprFunctionPrefix</p>
<p>When defined, the check will ensure constexpr function names will add the prefixed with the given value (regardless of casing).</p>
<p>ConstexprFunctionIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for constexpr function names matching this regular expression.</p>
<p>ConstexprFunctionSuffix</p>
<p>When defined, the check will ensure constexpr function names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>ConstexprFunctionCase of lower_case</li>
<li>ConstexprFunctionPrefix of pre_</li>
<li>ConstexprFunctionSuffix of _post</li>
</ul>
<p>Identifies and/or transforms constexpr function names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">constexpr</span> <span class="dt">int</span> CE_function() { <span class="kw">return</span> <span class="dv">3</span>; }</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">constexpr</span> <span class="dt">int</span> pre_ce_function_post() { <span class="kw">return</span> <span class="dv">3</span>; }</code></pre></div>
<p>ConstexprMethodCase</p>
<p>When defined, the check will ensure constexpr method names conform to the selected casing.</p>
<p>ConstexprMethodPrefix</p>
<p>When defined, the check will ensure constexpr method names will add the prefixed with the given value (regardless of casing).</p>
<p>ConstexprMethodIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for constexpr method names matching this regular expression.</p>
<p>ConstexprMethodSuffix</p>
<p>When defined, the check will ensure constexpr method names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>ConstexprMethodCase of lower_case</li>
<li>ConstexprMethodPrefix of pre_</li>
<li>ConstexprMethodSuffix of _post</li>
</ul>
<p>Identifies and/or transforms constexpr method names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> Foo {
<span class="kw">public</span>:
  <span class="kw">constexpr</span> <span class="dt">int</span> CST_expr_Method() { <span class="kw">return</span> <span class="dv">2</span>; }
}</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> Foo {
<span class="kw">public</span>:
  <span class="kw">constexpr</span> <span class="dt">int</span> pre_cst_expr_method_post() { <span class="kw">return</span> <span class="dv">2</span>; }
}</code></pre></div>
<p>ConstexprVariableCase</p>
<p>When defined, the check will ensure constexpr variable names conform to the selected casing.</p>
<p>ConstexprVariablePrefix</p>
<p>When defined, the check will ensure constexpr variable names will add the prefixed with the given value (regardless of casing).</p>
<p>ConstexprVariableIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for constexpr variable names matching this regular expression.</p>
<p>ConstexprVariableSuffix</p>
<p>When defined, the check will ensure constexpr variable names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>ConstexprVariableCase of lower_case</li>
<li>ConstexprVariablePrefix of pre_</li>
<li>ConstexprVariableSuffix of _post</li>
</ul>
<p>Identifies and/or transforms constexpr variable names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">constexpr</span> <span class="dt">int</span> ConstExpr_variable = MyConstant;</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">constexpr</span> <span class="dt">int</span> pre_constexpr_variable_post = MyConstant;</code></pre></div>
<p>EnumCase</p>
<p>When defined, the check will ensure enumeration names conform to the selected casing.</p>
<p>EnumPrefix</p>
<p>When defined, the check will ensure enumeration names will add the prefixed with the given value (regardless of casing).</p>
<p>EnumIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for enumeration names matching this regular expression.</p>
<p>EnumSuffix</p>
<p>When defined, the check will ensure enumeration names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>EnumCase of lower_case</li>
<li>EnumPrefix of pre_</li>
<li>EnumSuffix of _post</li>
</ul>
<p>Identifies and/or transforms enumeration names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">enum</span> FOO { One, Two, Three };</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">enum</span> pre_foo_post { One, Two, Three };</code></pre></div>
<p>EnumConstantCase</p>
<p>When defined, the check will ensure enumeration constant names conform to the selected casing.</p>
<p>EnumConstantPrefix</p>
<p>When defined, the check will ensure enumeration constant names will add the prefixed with the given value (regardless of casing).</p>
<p>EnumConstantIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for enumeration constant names matching this regular expression.</p>
<p>EnumConstantSuffix</p>
<p>When defined, the check will ensure enumeration constant names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>EnumConstantCase of lower_case</li>
<li>EnumConstantPrefix of pre_</li>
<li>EnumConstantSuffix of _post</li>
</ul>
<p>Identifies and/or transforms enumeration constant names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">enum</span> FOO { One, Two, Three };</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">enum</span> FOO { pre_One_post, pre_Two_post, pre_Three_post };</code></pre></div>
<p>FunctionCase</p>
<p>When defined, the check will ensure function names conform to the selected casing.</p>
<p>FunctionPrefix</p>
<p>When defined, the check will ensure function names will add the prefixed with the given value (regardless of casing).</p>
<p>FunctionIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for function names matching this regular expression.</p>
<p>FunctionSuffix</p>
<p>When defined, the check will ensure function names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>FunctionCase of lower_case</li>
<li>FunctionPrefix of pre_</li>
<li>FunctionSuffix of _post</li>
</ul>
<p>Identifies and/or transforms function names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">char</span> MY_Function_string();</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">char</span> pre_my_function_string_post();</code></pre></div>
<p>GetConfigPerFile</p>
<p>When true the check will look for the configuration for where an identifier is declared. Useful for when included header files use a different style. Default value is true.</p>
<p>GlobalConstantCase</p>
<p>When defined, the check will ensure global constant names conform to the selected casing.</p>
<p>GlobalConstantPrefix</p>
<p>When defined, the check will ensure global constant names will add the prefixed with the given value (regardless of casing).</p>
<p>GlobalConstantIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for global constant names matching this regular expression.</p>
<p>GlobalConstantSuffix</p>
<p>When defined, the check will ensure global constant names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>GlobalConstantCase of lower_case</li>
<li>GlobalConstantPrefix of pre_</li>
<li>GlobalConstantSuffix of _post</li>
</ul>
<p>Identifies and/or transforms global constant names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">unsigned</span> <span class="dt">const</span> MyConstGlobal_array[] = {<span class="dv">1</span>, <span class="dv">2</span>, <span class="dv">3</span>};</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">unsigned</span> <span class="dt">const</span> pre_myconstglobal_array_post[] = {<span class="dv">1</span>, <span class="dv">2</span>, <span class="dv">3</span>};</code></pre></div>
<p>GlobalConstantPointerCase</p>
<p>When defined, the check will ensure global constant pointer names conform to the selected casing.</p>
<p>GlobalConstantPointerPrefix</p>
<p>When defined, the check will ensure global constant pointer names will add the prefixed with the given value (regardless of casing).</p>
<p>GlobalConstantPointerIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for global constant pointer names matching this regular expression.</p>
<p>GlobalConstantPointerSuffix</p>
<p>When defined, the check will ensure global constant pointer names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>GlobalConstantPointerCase of lower_case</li>
<li>GlobalConstantPointerPrefix of pre_</li>
<li>GlobalConstantPointerSuffix of _post</li>
</ul>
<p>Identifies and/or transforms global constant pointer names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">int</span> *<span class="dt">const</span> MyConstantGlobalPointer = <span class="kw">nullptr</span>;</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">int</span> *<span class="dt">const</span> pre_myconstantglobalpointer_post = <span class="kw">nullptr</span>;</code></pre></div>
<p>GlobalFunctionCase</p>
<p>When defined, the check will ensure global function names conform to the selected casing.</p>
<p>GlobalFunctionPrefix</p>
<p>When defined, the check will ensure global function names will add the prefixed with the given value (regardless of casing).</p>
<p>GlobalFunctionIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for global function names matching this regular expression.</p>
<p>GlobalFunctionSuffix</p>
<p>When defined, the check will ensure global function names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>GlobalFunctionCase of lower_case</li>
<li>GlobalFunctionPrefix of pre_</li>
<li>GlobalFunctionSuffix of _post</li>
</ul>
<p>Identifies and/or transforms global function names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> GLOBAL_FUNCTION(<span class="dt">int</span> PARAMETER_1, <span class="dt">int</span> <span class="dt">const</span> CONST_parameter);</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> pre_global_function_post(<span class="dt">int</span> PARAMETER_1, <span class="dt">int</span> <span class="dt">const</span> CONST_parameter);</code></pre></div>
<p>GlobalPointerCase</p>
<p>When defined, the check will ensure global pointer names conform to the selected casing.</p>
<p>GlobalPointerPrefix</p>
<p>When defined, the check will ensure global pointer names will add the prefixed with the given value (regardless of casing).</p>
<p>GlobalPointerIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for global pointer names matching this regular expression.</p>
<p>GlobalPointerSuffix</p>
<p>When defined, the check will ensure global pointer names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>GlobalPointerCase of lower_case</li>
<li>GlobalPointerPrefix of pre_</li>
<li>GlobalPointerSuffix of _post</li>
</ul>
<p>Identifies and/or transforms global pointer names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">int</span> *GLOBAL3;</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">int</span> *pre_global3_post;</code></pre></div>
<p>GlobalVariableCase</p>
<p>When defined, the check will ensure global variable names conform to the selected casing.</p>
<p>GlobalVariablePrefix</p>
<p>When defined, the check will ensure global variable names will add the prefixed with the given value (regardless of casing).</p>
<p>GlobalVariableIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for global variable names matching this regular expression.</p>
<p>GlobalVariableSuffix</p>
<p>When defined, the check will ensure global variable names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>GlobalVariableCase of lower_case</li>
<li>GlobalVariablePrefix of pre_</li>
<li>GlobalVariableSuffix of _post</li>
</ul>
<p>Identifies and/or transforms global variable names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">int</span> GLOBAL3;</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">int</span> pre_global3_post;</code></pre></div>
<p>IgnoreMainLikeFunctions</p>
<p>When set to true functions that have a similar signature to main or wmain won’t enforce checks on the names of their parameters. Default value is false.</p>
<p>InlineNamespaceCase</p>
<p>When defined, the check will ensure inline namespaces names conform to the selected casing.</p>
<p>InlineNamespacePrefix</p>
<p>When defined, the check will ensure inline namespaces names will add the prefixed with the given value (regardless of casing).</p>
<p>InlineNamespaceIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for inline namespaces names matching this regular expression.</p>
<p>InlineNamespaceSuffix</p>
<p>When defined, the check will ensure inline namespaces names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>InlineNamespaceCase of lower_case</li>
<li>InlineNamespacePrefix of pre_</li>
<li>InlineNamespaceSuffix of _post</li>
</ul>
<p>Identifies and/or transforms inline namespaces names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">namespace</span> FOO_NS {
<span class="kw">inline</span> <span class="kw">namespace</span> InlineNamespace {
...
}
} <span class="co">// namespace FOO_NS</span></code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">namespace</span> FOO_NS {
<span class="kw">inline</span> <span class="kw">namespace</span> pre_inlinenamespace_post {
...
}
} <span class="co">// namespace FOO_NS</span></code></pre></div>
<p>LocalConstantCase</p>
<p>When defined, the check will ensure local constant names conform to the selected casing.</p>
<p>LocalConstantPrefix</p>
<p>When defined, the check will ensure local constant names will add the prefixed with the given value (regardless of casing).</p>
<p>LocalConstantIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for local constant names matching this regular expression.</p>
<p>LocalConstantSuffix</p>
<p>When defined, the check will ensure local constant names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>LocalConstantCase of lower_case</li>
<li>LocalConstantPrefix of pre_</li>
<li>LocalConstantSuffix of _post</li>
</ul>
<p>Identifies and/or transforms local constant names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> foo() { <span class="dt">int</span> <span class="dt">const</span> local_Constant = <span class="dv">3</span>; }</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> foo() { <span class="dt">int</span> <span class="dt">const</span> pre_local_constant_post = <span class="dv">3</span>; }</code></pre></div>
<p>LocalConstantPointerCase</p>
<p>When defined, the check will ensure local constant pointer names conform to the selected casing.</p>
<p>LocalConstantPointerPrefix</p>
<p>When defined, the check will ensure local constant pointer names will add the prefixed with the given value (regardless of casing).</p>
<p>LocalConstantPointerIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for local constant pointer names matching this regular expression.</p>
<p>LocalConstantPointerSuffix</p>
<p>When defined, the check will ensure local constant pointer names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>LocalConstantPointerCase of lower_case</li>
<li>LocalConstantPointerPrefix of pre_</li>
<li>LocalConstantPointerSuffix of _post</li>
</ul>
<p>Identifies and/or transforms local constant pointer names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> foo() { <span class="dt">int</span> <span class="dt">const</span> *local_Constant = <span class="dv">3</span>; }</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> foo() { <span class="dt">int</span> <span class="dt">const</span> *pre_local_constant_post = <span class="dv">3</span>; }</code></pre></div>
<p>LocalPointerCase</p>
<p>When defined, the check will ensure local pointer names conform to the selected casing.</p>
<p>LocalPointerPrefix</p>
<p>When defined, the check will ensure local pointer names will add the prefixed with the given value (regardless of casing).</p>
<p>LocalPointerIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for local pointer names matching this regular expression.</p>
<p>LocalPointerSuffix</p>
<p>When defined, the check will ensure local pointer names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>LocalPointerCase of lower_case</li>
<li>LocalPointerPrefix of pre_</li>
<li>LocalPointerSuffix of _post</li>
</ul>
<p>Identifies and/or transforms local pointer names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> foo() { <span class="dt">int</span> *local_Constant; }</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> foo() { <span class="dt">int</span> *pre_local_constant_post; }</code></pre></div>
<p>LocalVariableCase</p>
<p>When defined, the check will ensure local variable names conform to the selected casing.</p>
<p>LocalVariablePrefix</p>
<p>When defined, the check will ensure local variable names will add the prefixed with the given value (regardless of casing).</p>
<p>LocalVariableIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for local variable names matching this regular expression.</p>
<p>For example using values of:</p>
<ul>
<li>LocalVariableCase of CamelCase</li>
<li>LocalVariableIgnoredRegexp of </li>
</ul>
<p>Will exclude variables with a length less than or equal to 2 from the camel case check applied to other variables.</p>
<p>LocalVariableSuffix</p>
<p>When defined, the check will ensure local variable names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>LocalVariableCase of lower_case</li>
<li>LocalVariablePrefix of pre_</li>
<li>LocalVariableSuffix of _post</li>
</ul>
<p>Identifies and/or transforms local variable names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> foo() { <span class="dt">int</span> local_Constant; }</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> foo() { <span class="dt">int</span> pre_local_constant_post; }</code></pre></div>
<p>MacroDefinitionCase</p>
<p>When defined, the check will ensure macro definitions conform to the selected casing.</p>
<p>MacroDefinitionPrefix</p>
<p>When defined, the check will ensure macro definitions will add the prefixed with the given value (regardless of casing).</p>
<p>MacroDefinitionIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for macro definitions matching this regular expression.</p>
<p>MacroDefinitionSuffix</p>
<p>When defined, the check will ensure macro definitions will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>MacroDefinitionCase of lower_case</li>
<li>MacroDefinitionPrefix of pre_</li>
<li>MacroDefinitionSuffix of _post</li>
</ul>
<p>Identifies and/or transforms macro definitions as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="ot">#define MY_MacroDefinition</span></code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="ot">#define pre_my_macro_definition_post</span></code></pre></div>
<p>Note: This will not warn on builtin macros or macros defined on the command line using the -D flag.</p>
<p>MemberCase</p>
<p>When defined, the check will ensure member names conform to the selected casing.</p>
<p>MemberPrefix</p>
<p>When defined, the check will ensure member names will add the prefixed with the given value (regardless of casing).</p>
<p>MemberIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for member names matching this regular expression.</p>
<p>MemberSuffix</p>
<p>When defined, the check will ensure member names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>MemberCase of lower_case</li>
<li>MemberPrefix of pre_</li>
<li>MemberSuffix of _post</li>
</ul>
<p>Identifies and/or transforms member names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> Foo {
  <span class="dt">char</span> MY_ConstMember_string[<span class="dv">4</span>];
}</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> Foo {
  <span class="dt">char</span> pre_my_constmember_string_post[<span class="dv">4</span>];
}</code></pre></div>
<p>MethodCase</p>
<p>When defined, the check will ensure method names conform to the selected casing.</p>
<p>MethodPrefix</p>
<p>When defined, the check will ensure method names will add the prefixed with the given value (regardless of casing).</p>
<p>MethodIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for method names matching this regular expression.</p>
<p>MethodSuffix</p>
<p>When defined, the check will ensure method names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>MethodCase of lower_case</li>
<li>MethodPrefix of pre_</li>
<li>MethodSuffix of _post</li>
</ul>
<p>Identifies and/or transforms method names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> Foo {
  <span class="dt">char</span> MY_Method_string();
}</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> Foo {
  <span class="dt">char</span> pre_my_method_string_post();
}</code></pre></div>
<p>NamespaceCase</p>
<p>When defined, the check will ensure namespace names conform to the selected casing.</p>
<p>NamespacePrefix</p>
<p>When defined, the check will ensure namespace names will add the prefixed with the given value (regardless of casing).</p>
<p>NamespaceIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for namespace names matching this regular expression.</p>
<p>NamespaceSuffix</p>
<p>When defined, the check will ensure namespace names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>NamespaceCase of lower_case</li>
<li>NamespacePrefix of pre_</li>
<li>NamespaceSuffix of _post</li>
</ul>
<p>Identifies and/or transforms namespace names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">namespace</span> FOO_NS {
...
}</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">namespace</span> pre_foo_ns_post {
...
}</code></pre></div>
<p>ParameterCase</p>
<p>When defined, the check will ensure parameter names conform to the selected casing.</p>
<p>ParameterPrefix</p>
<p>When defined, the check will ensure parameter names will add the prefixed with the given value (regardless of casing).</p>
<p>ParameterIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for parameter names matching this regular expression.</p>
<p>ParameterSuffix</p>
<p>When defined, the check will ensure parameter names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>ParameterCase of lower_case</li>
<li>ParameterPrefix of pre_</li>
<li>ParameterSuffix of _post</li>
</ul>
<p>Identifies and/or transforms parameter names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> GLOBAL_FUNCTION(<span class="dt">int</span> PARAMETER_1, <span class="dt">int</span> <span class="dt">const</span> CONST_parameter);</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> GLOBAL_FUNCTION(<span class="dt">int</span> pre_parameter_post, <span class="dt">int</span> <span class="dt">const</span> CONST_parameter);</code></pre></div>
<p>ParameterPackCase</p>
<p>When defined, the check will ensure parameter pack names conform to the selected casing.</p>
<p>ParameterPackPrefix</p>
<p>When defined, the check will ensure parameter pack names will add the prefixed with the given value (regardless of casing).</p>
<p>ParameterPackIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for parameter pack names matching this regular expression.</p>
<p>ParameterPackSuffix</p>
<p>When defined, the check will ensure parameter pack names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>ParameterPackCase of lower_case</li>
<li>ParameterPackPrefix of pre_</li>
<li>ParameterPackSuffix of _post</li>
</ul>
<p>Identifies and/or transforms parameter pack names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">template</span> &lt;<span class="kw">typename</span>... TYPE_parameters&gt; {
  <span class="dt">void</span> FUNCTION(<span class="dt">int</span>... TYPE_parameters);
}</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">template</span> &lt;<span class="kw">typename</span>... TYPE_parameters&gt; {
  <span class="dt">void</span> FUNCTION(<span class="dt">int</span>... pre_type_parameters_post);
}</code></pre></div>
<p>PointerParameterCase</p>
<p>When defined, the check will ensure pointer parameter names conform to the selected casing.</p>
<p>PointerParameterPrefix</p>
<p>When defined, the check will ensure pointer parameter names will add the prefixed with the given value (regardless of casing).</p>
<p>PointerParameterIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for pointer parameter names matching this regular expression.</p>
<p>PointerParameterSuffix</p>
<p>When defined, the check will ensure pointer parameter names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>PointerParameterCase of lower_case</li>
<li>PointerParameterPrefix of pre_</li>
<li>PointerParameterSuffix of _post</li>
</ul>
<p>Identifies and/or transforms pointer parameter names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> FUNCTION(<span class="dt">int</span> *PARAMETER);</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> FUNCTION(<span class="dt">int</span> *pre_parameter_post);</code></pre></div>
<p>PrivateMemberCase</p>
<p>When defined, the check will ensure private member names conform to the selected casing.</p>
<p>PrivateMemberPrefix</p>
<p>When defined, the check will ensure private member names will add the prefixed with the given value (regardless of casing).</p>
<p>PrivateMemberIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for private member names matching this regular expression.</p>
<p>PrivateMemberSuffix</p>
<p>When defined, the check will ensure private member names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>PrivateMemberCase of lower_case</li>
<li>PrivateMemberPrefix of pre_</li>
<li>PrivateMemberSuffix of _post</li>
</ul>
<p>Identifies and/or transforms private member names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> Foo {
<span class="kw">private</span>:
  <span class="dt">int</span> Member_Variable;
}</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> Foo {
<span class="kw">private</span>:
  <span class="dt">int</span> pre_member_variable_post;
}</code></pre></div>
<p>PrivateMethodCase</p>
<p>When defined, the check will ensure private method names conform to the selected casing.</p>
<p>PrivateMethodPrefix</p>
<p>When defined, the check will ensure private method names will add the prefixed with the given value (regardless of casing).</p>
<p>PrivateMethodIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for private method names matching this regular expression.</p>
<p>PrivateMethodSuffix</p>
<p>When defined, the check will ensure private method names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>PrivateMethodCase of lower_case</li>
<li>PrivateMethodPrefix of pre_</li>
<li>PrivateMethodSuffix of _post</li>
</ul>
<p>Identifies and/or transforms private method names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> Foo {
<span class="kw">private</span>:
  <span class="dt">int</span> Member_Method();
}</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> Foo {
<span class="kw">private</span>:
  <span class="dt">int</span> pre_member_method_post();
}</code></pre></div>
<p>ProtectedMemberCase</p>
<p>When defined, the check will ensure protected member names conform to the selected casing.</p>
<p>ProtectedMemberPrefix</p>
<p>When defined, the check will ensure protected member names will add the prefixed with the given value (regardless of casing).</p>
<p>ProtectedMemberIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for protected member names matching this regular expression.</p>
<p>ProtectedMemberSuffix</p>
<p>When defined, the check will ensure protected member names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>ProtectedMemberCase of lower_case</li>
<li>ProtectedMemberPrefix of pre_</li>
<li>ProtectedMemberSuffix of _post</li>
</ul>
<p>Identifies and/or transforms protected member names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> Foo {
<span class="kw">protected</span>:
  <span class="dt">int</span> Member_Variable;
}</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> Foo {
<span class="kw">protected</span>:
  <span class="dt">int</span> pre_member_variable_post;
}</code></pre></div>
<p>ProtectedMethodCase</p>
<p>When defined, the check will ensure protected method names conform to the selected casing.</p>
<p>ProtectedMethodPrefix</p>
<p>When defined, the check will ensure protected method names will add the prefixed with the given value (regardless of casing).</p>
<p>ProtectedMethodIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for protected method names matching this regular expression.</p>
<p>ProtectedMethodSuffix</p>
<p>When defined, the check will ensure protected method names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>ProtectedMethodCase of lower_case</li>
<li>ProtectedMethodPrefix of pre_</li>
<li>ProtectedMethodSuffix of _post</li>
</ul>
<p>Identifies and/or transforms protect method names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> Foo {
<span class="kw">protected</span>:
  <span class="dt">int</span> Member_Method();
}</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> Foo {
<span class="kw">protected</span>:
  <span class="dt">int</span> pre_member_method_post();
}</code></pre></div>
<p>PublicMemberCase</p>
<p>When defined, the check will ensure public member names conform to the selected casing.</p>
<p>PublicMemberPrefix</p>
<p>When defined, the check will ensure public member names will add the prefixed with the given value (regardless of casing).</p>
<p>PublicMemberIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for public member names matching this regular expression.</p>
<p>PublicMemberSuffix</p>
<p>When defined, the check will ensure public member names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>PublicMemberCase of lower_case</li>
<li>PublicMemberPrefix of pre_</li>
<li>PublicMemberSuffix of _post</li>
</ul>
<p>Identifies and/or transforms public member names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> Foo {
<span class="kw">public</span>:
  <span class="dt">int</span> Member_Variable;
}</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> Foo {
<span class="kw">public</span>:
  <span class="dt">int</span> pre_member_variable_post;
}</code></pre></div>
<p>PublicMethodCase</p>
<p>When defined, the check will ensure public method names conform to the selected casing.</p>
<p>PublicMethodPrefix</p>
<p>When defined, the check will ensure public method names will add the prefixed with the given value (regardless of casing).</p>
<p>PublicMethodIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for public method names matching this regular expression.</p>
<p>PublicMethodSuffix</p>
<p>When defined, the check will ensure public method names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>PublicMethodCase of lower_case</li>
<li>PublicMethodPrefix of pre_</li>
<li>PublicMethodSuffix of _post</li>
</ul>
<p>Identifies and/or transforms public method names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> Foo {
<span class="kw">public</span>:
  <span class="dt">int</span> Member_Method();
}</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> Foo {
<span class="kw">public</span>:
  <span class="dt">int</span> pre_member_method_post();
}</code></pre></div>
<p>ScopedEnumConstantCase</p>
<p>When defined, the check will ensure scoped enum constant names conform to the selected casing.</p>
<p>ScopedEnumConstantPrefix</p>
<p>When defined, the check will ensure scoped enum constant names will add the prefixed with the given value (regardless of casing).</p>
<p>ScopedEnumConstantIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for scoped enum constant names matching this regular expression.</p>
<p>ScopedEnumConstantSuffix</p>
<p>When defined, the check will ensure scoped enum constant names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>ScopedEnumConstantCase of lower_case</li>
<li>ScopedEnumConstantPrefix of pre_</li>
<li>ScopedEnumConstantSuffix of _post</li>
</ul>
<p>Identifies and/or transforms enumeration constant names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">enum</span> <span class="kw">class</span> FOO { One, Two, Three };</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">enum</span> <span class="kw">class</span> FOO { pre_One_post, pre_Two_post, pre_Three_post };</code></pre></div>
<p>StaticConstantCase</p>
<p>When defined, the check will ensure static constant names conform to the selected casing.</p>
<p>StaticConstantPrefix</p>
<p>When defined, the check will ensure static constant names will add the prefixed with the given value (regardless of casing).</p>
<p>StaticConstantIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for static constant names matching this regular expression.</p>
<p>StaticConstantSuffix</p>
<p>When defined, the check will ensure static constant names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>StaticConstantCase of lower_case</li>
<li>StaticConstantPrefix of pre_</li>
<li>StaticConstantSuffix of _post</li>
</ul>
<p>Identifies and/or transforms static constant names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">static</span> <span class="dt">unsigned</span> <span class="dt">const</span> MyConstStatic_array[] = {<span class="dv">1</span>, <span class="dv">2</span>, <span class="dv">3</span>};</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">static</span> <span class="dt">unsigned</span> <span class="dt">const</span> pre_myconststatic_array_post[] = {<span class="dv">1</span>, <span class="dv">2</span>, <span class="dv">3</span>};</code></pre></div>
<p>StaticVariableCase</p>
<p>When defined, the check will ensure static variable names conform to the selected casing.</p>
<p>StaticVariablePrefix</p>
<p>When defined, the check will ensure static variable names will add the prefixed with the given value (regardless of casing).</p>
<p>StaticVariableIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for static variable names matching this regular expression.</p>
<p>StaticVariableSuffix</p>
<p>When defined, the check will ensure static variable names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>StaticVariableCase of lower_case</li>
<li>StaticVariablePrefix of pre_</li>
<li>StaticVariableSuffix of _post</li>
</ul>
<p>Identifies and/or transforms static variable names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">static</span> <span class="dt">unsigned</span> MyStatic_array[] = {<span class="dv">1</span>, <span class="dv">2</span>, <span class="dv">3</span>};</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">static</span> <span class="dt">unsigned</span> pre_mystatic_array_post[] = {<span class="dv">1</span>, <span class="dv">2</span>, <span class="dv">3</span>};</code></pre></div>
<p>StructCase</p>
<p>When defined, the check will ensure struct names conform to the selected casing.</p>
<p>StructPrefix</p>
<p>When defined, the check will ensure struct names will add the prefixed with the given value (regardless of casing).</p>
<p>StructIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for struct names matching this regular expression.</p>
<p>StructSuffix</p>
<p>When defined, the check will ensure struct names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>StructCase of lower_case</li>
<li>StructPrefix of pre_</li>
<li>StructSuffix of _post</li>
</ul>
<p>Identifies and/or transforms struct names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">struct</span> FOO {
  FOO();
  ~FOO();
};</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">struct</span> pre_foo_post {
  pre_foo_post();
  ~pre_foo_post();
};</code></pre></div>
<p>TemplateParameterCase</p>
<p>When defined, the check will ensure template parameter names conform to the selected casing.</p>
<p>TemplateParameterPrefix</p>
<p>When defined, the check will ensure template parameter names will add the prefixed with the given value (regardless of casing).</p>
<p>TemplateParameterIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for template parameter names matching this regular expression.</p>
<p>TemplateParameterSuffix</p>
<p>When defined, the check will ensure template parameter names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>TemplateParameterCase of lower_case</li>
<li>TemplateParameterPrefix of pre_</li>
<li>TemplateParameterSuffix of _post</li>
</ul>
<p>Identifies and/or transforms template parameter names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">template</span> &lt;<span class="kw">typename</span> T&gt; <span class="kw">class</span> Foo {};</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">template</span> &lt;<span class="kw">typename</span> pre_t_post&gt; <span class="kw">class</span> Foo {};</code></pre></div>
<p>TemplateTemplateParameterCase</p>
<p>When defined, the check will ensure template template parameter names conform to the selected casing.</p>
<p>TemplateTemplateParameterPrefix</p>
<p>When defined, the check will ensure template template parameter names will add the prefixed with the given value (regardless of casing).</p>
<p>TemplateTemplateParameterIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for template template parameter names matching this regular expression.</p>
<p>TemplateTemplateParameterSuffix</p>
<p>When defined, the check will ensure template template parameter names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>TemplateTemplateParameterCase of lower_case</li>
<li>TemplateTemplateParameterPrefix of pre_</li>
<li>TemplateTemplateParameterSuffix of _post</li>
</ul>
<p>Identifies and/or transforms template template parameter names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">template</span> &lt;<span class="kw">template</span> &lt;<span class="kw">typename</span>&gt; <span class="kw">class</span> TPL_parameter, <span class="dt">int</span> COUNT_params,
          <span class="kw">typename</span>... TYPE_parameters&gt;</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">template</span> &lt;<span class="kw">template</span> &lt;<span class="kw">typename</span>&gt; <span class="kw">class</span> pre_tpl_parameter_post, <span class="dt">int</span> COUNT_params,
          <span class="kw">typename</span>... TYPE_parameters&gt;</code></pre></div>
<p>TypeAliasCase</p>
<p>When defined, the check will ensure type alias names conform to the selected casing.</p>
<p>TypeAliasPrefix</p>
<p>When defined, the check will ensure type alias names will add the prefixed with the given value (regardless of casing).</p>
<p>TypeAliasIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for type alias names matching this regular expression.</p>
<p>TypeAliasSuffix</p>
<p>When defined, the check will ensure type alias names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>TypeAliasCase of lower_case</li>
<li>TypeAliasPrefix of pre_</li>
<li>TypeAliasSuffix of _post</li>
</ul>
<p>Identifies and/or transforms type alias names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">using</span> MY_STRUCT_TYPE = my_structure;</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">using</span> pre_my_struct_type_post = my_structure;</code></pre></div>
<p>TypedefCase</p>
<p>When defined, the check will ensure typedef names conform to the selected casing.</p>
<p>TypedefPrefix</p>
<p>When defined, the check will ensure typedef names will add the prefixed with the given value (regardless of casing).</p>
<p>TypedefIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for typedef names matching this regular expression.</p>
<p>TypedefSuffix</p>
<p>When defined, the check will ensure typedef names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>TypedefCase of lower_case</li>
<li>TypedefPrefix of pre_</li>
<li>TypedefSuffix of _post</li>
</ul>
<p>Identifies and/or transforms typedef names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">typedef</span> <span class="dt">int</span> MYINT;</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">typedef</span> <span class="dt">int</span> pre_myint_post;</code></pre></div>
<p>TypeTemplateParameterCase</p>
<p>When defined, the check will ensure type template parameter names conform to the selected casing.</p>
<p>TypeTemplateParameterPrefix</p>
<p>When defined, the check will ensure type template parameter names will add the prefixed with the given value (regardless of casing).</p>
<p>TypeTemplateParameterIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for type template names matching this regular expression.</p>
<p>TypeTemplateParameterSuffix</p>
<p>When defined, the check will ensure type template parameter names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>TypeTemplateParameterCase of lower_case</li>
<li>TypeTemplateParameterPrefix of pre_</li>
<li>TypeTemplateParameterSuffix of _post</li>
</ul>
<p>Identifies and/or transforms type template parameter names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">template</span> &lt;<span class="kw">template</span> &lt;<span class="kw">typename</span>&gt; <span class="kw">class</span> TPL_parameter, <span class="dt">int</span> COUNT_params,
          <span class="kw">typename</span>... TYPE_parameters&gt;</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">template</span> &lt;<span class="kw">template</span> &lt;<span class="kw">typename</span>&gt; <span class="kw">class</span> TPL_parameter, <span class="dt">int</span> COUNT_params,
          <span class="kw">typename</span>... pre_type_parameters_post&gt;</code></pre></div>
<p>UnionCase</p>
<p>When defined, the check will ensure union names conform to the selected casing.</p>
<p>UnionPrefix</p>
<p>When defined, the check will ensure union names will add the prefixed with the given value (regardless of casing).</p>
<p>UnionIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for union names matching this regular expression.</p>
<p>UnionSuffix</p>
<p>When defined, the check will ensure union names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>UnionCase of lower_case</li>
<li>UnionPrefix of pre_</li>
<li>UnionSuffix of _post</li>
</ul>
<p>Identifies and/or transforms union names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">union</span> FOO {
  <span class="dt">int</span> a;
  <span class="dt">char</span> b;
};</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">union</span> pre_foo_post {
  <span class="dt">int</span> a;
  <span class="dt">char</span> b;
};</code></pre></div>
<p>ValueTemplateParameterCase</p>
<p>When defined, the check will ensure value template parameter names conform to the selected casing.</p>
<p>ValueTemplateParameterPrefix</p>
<p>When defined, the check will ensure value template parameter names will add the prefixed with the given value (regardless of casing).</p>
<p>ValueTemplateParameterIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for value template parameter names matching this regular expression.</p>
<p>ValueTemplateParameterSuffix</p>
<p>When defined, the check will ensure value template parameter names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>ValueTemplateParameterCase of lower_case</li>
<li>ValueTemplateParameterPrefix of pre_</li>
<li>ValueTemplateParameterSuffix of _post</li>
</ul>
<p>Identifies and/or transforms value template parameter names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">template</span> &lt;<span class="kw">template</span> &lt;<span class="kw">typename</span>&gt; <span class="kw">class</span> TPL_parameter, <span class="dt">int</span> COUNT_params,
          <span class="kw">typename</span>... TYPE_parameters&gt;</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">template</span> &lt;<span class="kw">template</span> &lt;<span class="kw">typename</span>&gt; <span class="kw">class</span> TPL_parameter, <span class="dt">int</span> pre_count_params_post,
          <span class="kw">typename</span>... TYPE_parameters&gt;</code></pre></div>
<p>VariableCase</p>
<p>When defined, the check will ensure variable names conform to the selected casing.</p>
<p>VariablePrefix</p>
<p>When defined, the check will ensure variable names will add the prefixed with the given value (regardless of casing).</p>
<p>VariableIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for variable names matching this regular expression.</p>
<p>VariableSuffix</p>
<p>When defined, the check will ensure variable names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>VariableCase of lower_case</li>
<li>VariablePrefix of pre_</li>
<li>VariableSuffix of _post</li>
</ul>
<p>Identifies and/or transforms variable names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">unsigned</span> MyVariable;</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">unsigned</span> pre_myvariable_post;</code></pre></div>
<p>VirtualMethodCase</p>
<p>When defined, the check will ensure virtual method names conform to the selected casing.</p>
<p>VirtualMethodPrefix</p>
<p>When defined, the check will ensure virtual method names will add the prefixed with the given value (regardless of casing).</p>
<p>VirtualMethodIgnoredRegexp</p>
<p>Identifier naming checks won’t be enforced for virtual method names matching this regular expression.</p>
<p>VirtualMethodSuffix</p>
<p>When defined, the check will ensure virtual method names will add the suffix with the given value (regardless of casing).</p>
<p>For example using values of:</p>
<ul>
<li>VirtualMethodCase of lower_case</li>
<li>VirtualMethodPrefix of pre_</li>
<li>VirtualMethodSuffix of _post</li>
</ul>
<p>Identifies and/or transforms virtual method names as follows:</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> Foo {
<span class="kw">public</span>:
  <span class="kw">virtual</span> <span class="dt">int</span> MemberFunction();
}</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> Foo {
<span class="kw">public</span>:
  <span class="kw">virtual</span> <span class="dt">int</span> pre_member_function_post();
}</code></pre></div>
<p>(Clang-Tidy original name: readability-identifier-naming)</p>


#### Implicit Bool Conversion {#CT_RDB_IBC}
<p>This check can be used to find implicit conversions between built-in types and booleans. Depending on use case, it may simply help with readability of the code, or in some cases, point to potential bugs which remain unnoticed due to implicit conversions.</p>
<p>The following is a real-world example of bug which was hiding behind implicit bool conversion:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> Foo {
  <span class="dt">int</span> m_foo;

<span class="kw">public</span>:
  <span class="dt">void</span> setFoo(<span class="dt">bool</span> foo) { m_foo = foo; } <span class="co">// warning: implicit conversion bool -&gt; int</span>
  <span class="dt">int</span> getFoo() { <span class="kw">return</span> m_foo; }
};

<span class="dt">void</span> use(Foo&amp; foo) {
  <span class="dt">bool</span> value = foo.getFoo(); <span class="co">// warning: implicit conversion int -&gt; bool</span>
}</code></pre></div>
<p>This code is the result of unsuccessful refactoring, where type of m_foo changed from bool to int. The programmer forgot to change all occurrences of bool, and the remaining code is no longer correct, yet it still compiles without any visible warnings.</p>
<p>In addition to issuing warnings, fix-it hints are provided to help solve the reported issues. This can be used for improving readability of code, for example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> conversionsToBool() {
  <span class="dt">float</span> floating;
  <span class="dt">bool</span> boolean = floating;
  <span class="co">// ^ propose replacement: bool boolean = floating != 0.0f;</span>

  <span class="dt">int</span> integer;
  <span class="kw">if</span> (integer) {}
  <span class="co">// ^ propose replacement: if (integer != 0) {}</span>

  <span class="dt">int</span>* pointer;
  <span class="kw">if</span> (!pointer) {}
  <span class="co">// ^ propose replacement: if (pointer == nullptr) {}</span>

  <span class="kw">while</span> (<span class="dv">1</span>) {}
  <span class="co">// ^ propose replacement: while (true) {}</span>
}

<span class="dt">void</span> functionTakingInt(<span class="dt">int</span> param);

<span class="dt">void</span> conversionsFromBool() {
  <span class="dt">bool</span> boolean;
  functionTakingInt(boolean);
  <span class="co">// ^ propose replacement: functionTakingInt(static_cast&lt;int&gt;(boolean));</span>

  functionTakingInt(<span class="kw">true</span>);
  <span class="co">// ^ propose replacement: functionTakingInt(1);</span>
}</code></pre></div>
<p>In general, the following conversion types are checked:</p>
<ul>
<li>integer expression/literal to boolean (conversion from a single bit bitfield to boolean is explicitly allowed, since there’s no ambiguity / information loss in this case),</li>
<li>floating expression/literal to boolean,</li>
<li>pointer/pointer to member/nullptr/NULL to boolean,</li>
<li>boolean expression/literal to integer (conversion from boolean to a single bit bitfield is explicitly allowed),</li>
<li>boolean expression/literal to floating.</li>
</ul>
<p>The rules for generating fix-it hints are:</p>
<ul>
<li>in case of conversions from other built-in type to bool, an explicit comparison is proposed to make it clear what exactly is being compared:
<ul>
<li>bool boolean = floating; is changed to bool boolean = floating == 0.0f;,</li>
<li>for other types, appropriate literals are used (0, 0u, 0.0f, 0.0, nullptr),</li>
</ul></li>
<li>in case of negated expressions conversion to bool, the proposed replacement with comparison is simplified:
<ul>
<li>if (!pointer) is changed to if (pointer == nullptr),</li>
</ul></li>
<li>in case of conversions from bool to other built-in types, an explicit static_cast is proposed to make it clear that a conversion is taking place:
<ul>
<li>int integer = boolean; is changed to int integer = static_cast<int>(boolean);,</li>
</ul></li>
<li>if the conversion is performed on type literals, an equivalent literal is proposed, according to what type is actually expected, for example:
<ul>
<li>functionTakingBool(0); is changed to functionTakingBool(false);,</li>
<li>functionTakingInt(true); is changed to functionTakingInt(1);,</li>
<li>for other types, appropriate literals are used (false, true, 0, 1, 0u, 1u, 0.0f, 1.0f, 0.0, 1.0f).</li>
</ul></li>
</ul>
<p>Some additional accommodations are made for pre-C++11 dialects:</p>
<ul>
<li>false literal conversion to pointer is detected,</li>
<li>instead of nullptr literal, 0 is proposed as replacement.</li>
</ul>
<p>Occurrences of implicit conversions inside macros and template instantiations are deliberately ignored, as it is not clear how to deal with such cases.</p>
<h5 id="options-17">Options</h5>
<p>AllowIntegerConditions</p>
<p>When true, the check will allow conditional integer conversions. Default is false.</p>
<p>AllowPointerConditions</p>
<p>When true, the check will allow conditional pointer conversions. Default is false.</p>
<p>(Clang-Tidy original name: readability-implicit-bool-conversion)</p>


#### Inconsistent Declaration Parameter Name {#CT_RDB_IDPN}
<p>Find function declarations which differ in parameter names.</p>
<p>Example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// in foo.hpp:</span>
<span class="dt">void</span> foo(<span class="dt">int</span> a, <span class="dt">int</span> b, <span class="dt">int</span> c);

<span class="co">// in foo.cpp:</span>
<span class="dt">void</span> foo(<span class="dt">int</span> d, <span class="dt">int</span> e, <span class="dt">int</span> f); <span class="co">// warning</span></code></pre></div>
<p>This check should help to enforce consistency in large projects, where it often happens that a definition of function is refactored, changing the parameter names, but its declaration in header file is not updated. With this check, we can easily find and correct such inconsistencies, keeping declaration and definition always in sync.</p>
<p>Unnamed parameters are allowed and are not taken into account when comparing function declarations, for example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> foo(<span class="dt">int</span> a);
<span class="dt">void</span> foo(<span class="dt">int</span>); <span class="co">// no warning</span></code></pre></div>
<p>One name is also allowed to be a case-insensitive prefix/suffix of the other:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> foo(<span class="dt">int</span> count);
<span class="dt">void</span> foo(<span class="dt">int</span> count_input) { <span class="co">// no warning</span>
  <span class="dt">int</span> count = adjustCount(count_input);
}</code></pre></div>
<p>To help with refactoring, in some cases fix-it hints are generated to align parameter names to a single naming convention. This works with the assumption that the function definition is the most up-to-date version, as it directly references parameter names in its body. Example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> foo(<span class="dt">int</span> a); <span class="co">// warning and fix-it hint (replace &quot;a&quot; to &quot;b&quot;)</span>
<span class="dt">int</span> foo(<span class="dt">int</span> b) { <span class="kw">return</span> b + <span class="dv">2</span>; } <span class="co">// definition with use of &quot;b&quot;</span></code></pre></div>
<p>In the case of multiple redeclarations or function template specializations, a warning is issued for every redeclaration or specialization inconsistent with the definition or the first declaration seen in a translation unit.</p>
<p>IgnoreMacros</p>
<p>If this option is set to true (default is true), the check will not warn about names declared inside macros.</p>
<p>Strict</p>
<p>If this option is set to true (default is false), then names must match exactly (or be absent).</p>
<p>(Clang-Tidy original name: readability-inconsistent-declaration-parameter-name)</p>


#### Isolate Declaration {#CT_RDB_ID}
<p>Detects local variable declarations declaring more than one variable and tries to refactor the code to one statement per declaration.</p>
<p>The automatic code-transformation will use the same indentation as the original for every created statement and add a line break after each statement. It keeps the order of the variable declarations consistent, too.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> f() {
  <span class="dt">int</span> * pointer = <span class="kw">nullptr</span>, value = <span class="dv">42</span>, * <span class="dt">const</span> const_ptr = &amp;value;
  <span class="co">// This declaration will be diagnosed and transformed into:</span>
  <span class="co">// int * pointer = nullptr;</span>
  <span class="co">// int value = 42;</span>
  <span class="co">// int * const const_ptr = &amp;value;</span>
}</code></pre></div>
<p>The check excludes places where it is necessary or common to declare multiple variables in one statement and there is no other way supported in the language. Please note that structured bindings are not considered.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// It is not possible to transform this declaration and doing the declaration</span>
<span class="co">// before the loop will increase the scope of the variable &#39;Begin&#39; and &#39;End&#39;</span>
<span class="co">// which is undesirable.</span>
<span class="kw">for</span> (<span class="dt">int</span> Begin = <span class="dv">0</span>, End = <span class="dv">100</span>; Begin &lt; End; ++Begin);
<span class="kw">if</span> (<span class="dt">int</span> Begin = <span class="dv">42</span>, Result = some_function(Begin); Begin == Result);

<span class="co">// It is not possible to transform this declaration because the result is</span>
<span class="co">// not functionality preserving as &#39;j&#39; and &#39;k&#39; would not be part of the</span>
<span class="co">// &#39;if&#39; statement anymore.</span>
<span class="kw">if</span> (SomeCondition())
  <span class="dt">int</span> i = <span class="dv">42</span>, j = <span class="dv">43</span>, k = function(i,j);</code></pre></div>
<h5 id="limitations-2">Limitations</h5>
<p>Global variables and member variables are excluded.</p>
<p>The check currently does not support the automatic transformation of member-pointer-types.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">struct</span> S {
  <span class="dt">int</span> a;
  <span class="dt">const</span> <span class="dt">int</span> b;
  <span class="dt">void</span> f() {}
};

<span class="dt">void</span> f() {
  <span class="co">// Only a diagnostic message is emitted</span>
  <span class="dt">int</span> S::*p = &amp;S::a, S::*<span class="dt">const</span> q = &amp;S::a;
}</code></pre></div>
<p>Furthermore, the transformation is very cautious when it detects various kinds of macros or preprocessor directives in the range of the statement. In this case the transformation will not happen to avoid unexpected side-effects due to macros.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="ot">#define NULL 0</span>
<span class="ot">#define MY_NICE_TYPE int **</span>
<span class="ot">#define VAR_NAME(name) name##__LINE__</span>
<span class="ot">#define A_BUNCH_OF_VARIABLES int m1 = 42, m2 = 43, m3 = 44;</span>

<span class="dt">void</span> macros() {
  <span class="dt">int</span> *p1 = NULL, *p2 = NULL;
  <span class="co">// Will be transformed to</span>
  <span class="co">// int *p1 = NULL;</span>
  <span class="co">// int *p2 = NULL;</span>

  MY_NICE_TYPE p3, v1, v2;
  <span class="co">// Won&#39;t be transformed, but a diagnostic is emitted.</span>

  <span class="dt">int</span> VAR_NAME(v3),
      VAR_NAME(v4),
      VAR_NAME(v5);
  <span class="co">// Won&#39;t be transformed, but a diagnostic is emitted.</span>

  A_BUNCH_OF_VARIABLES
  <span class="co">// Won&#39;t be transformed, but a diagnostic is emitted.</span>

  <span class="dt">int</span> Unconditional,
<span class="ot">#if CONFIGURATION</span>
      IfConfigured = <span class="dv">42</span>,
<span class="ot">#else</span>
      IfConfigured = <span class="dv">0</span>;
<span class="ot">#endif</span>
  <span class="co">// Won&#39;t be transformed, but a diagnostic is emitted.</span>
}</code></pre></div>
<p>(Clang-Tidy original name: readability-isolate-declaration)</p>


#### Magic Numbers {#CT_RDB_MN}
<p>Detects magic numbers, integer or floating point literals that are embedded in code and not introduced via constants or symbols.</p>
<p>Many coding guidelines advise replacing the magic values with symbolic constants to improve readability. Here are a few references:</p>
<ul>
<li><a href="https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Res-magic">Rule ES.45: Avoid “magic constants”; use symbolic constants in C++ Core Guidelines</a></li>
<li><a href="http://www.codingstandard.com/rule/5-1-1-use-symbolic-names-instead-of-literal-values-in-code/">Rule 5.1.1 Use symbolic names instead of literal values in code in High Integrity C++</a></li>
<li>Item 17 in “C++ Coding Standards: 101 Rules, Guidelines and Best Practices” by Herb Sutter and Andrei Alexandrescu</li>
<li>Chapter 17 in “Clean Code - A handbook of agile software craftsmanship.” by Robert C. Martin</li>
<li>Rule 20701 in “TRAIN REAL TIME DATA PROTOCOL Coding Rules” by Armin-Hagen Weiss, Bombardier</li>
<li><a href="http://wiki.c2.com/?MagicNumber" class="uri">http://wiki.c2.com/?MagicNumber</a></li>
</ul>
<p>Examples of magic values:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">double</span> circleArea = <span class="fl">3.1415926535</span> * radius * radius;

<span class="dt">double</span> totalCharge = <span class="fl">1.08</span> * itemPrice;

<span class="dt">int</span> getAnswer() {
   <span class="kw">return</span> <span class="dv">-3</span>; <span class="co">// FILENOTFOUND</span>
}

<span class="kw">for</span> (<span class="dt">int</span> mm = <span class="dv">1</span>; mm &lt;= <span class="dv">12</span>; ++mm) {
   std::cout &lt;&lt; month[mm] &lt;&lt; <span class="st">&#39;</span><span class="ch">\n</span><span class="st">&#39;</span>;
}</code></pre></div>
<p>Example with magic values refactored:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">double</span> circleArea = M_PI * radius * radius;

<span class="dt">const</span> <span class="dt">double</span> TAX_RATE = <span class="fl">0.08</span>;  <span class="co">// or make it variable and read from a file</span>

<span class="dt">double</span> totalCharge = (<span class="fl">1.0</span> + TAX_RATE) * itemPrice;

<span class="dt">int</span> getAnswer() {
   <span class="kw">return</span> E_FILE_NOT_FOUND;
}

<span class="kw">for</span> (<span class="dt">int</span> mm = <span class="dv">1</span>; mm &lt;= MONTHS_IN_A_YEAR; ++mm) {
   std::cout &lt;&lt; month[mm] &lt;&lt; <span class="st">&#39;</span><span class="ch">\n</span><span class="st">&#39;</span>;
}</code></pre></div>
<p>For integral literals by default only 0 and 1 (and -1) integer values are accepted without a warning. This can be overridden with the <a href="#cmdoption-arg-ignoredintegervalues">IgnoredIntegerValues</a> option. Negative values are accepted if their absolute value is present in the <a href="#cmdoption-arg-ignoredintegervalues">IgnoredIntegerValues</a> list.</p>
<p>As a special case for integral values, all powers of two can be accepted without warning by enabling the <a href="#cmdoption-arg-ignorepowersof2integervalues">IgnorePowersOf2IntegerValues</a> option.</p>
<p>For floating point literals by default the 0.0 floating point value is accepted without a warning. The set of ignored floating point literals can be configured using the <a href="#cmdoption-arg-ignoredfloatingpointvalues">IgnoredFloatingPointValues</a> option. For each value in that set, the given string value is converted to a floating-point value representation used by the target architecture. If a floating-point literal value compares equal to one of the converted values, then that literal is not diagnosed by this check. Because floating-point equality is used to determine whether to diagnose or not, the user needs to be aware of the details of floating-point representations for any values that cannot be precisely represented for their target architecture.</p>
<p>For each value in the <a href="#cmdoption-arg-ignoredfloatingpointvalues">IgnoredFloatingPointValues</a> set, both the single-precision form and double-precision form are accepted (for example, if 3.14 is in the set, neither 3.14f nor 3.14 will produce a warning).</p>
<p>Scientific notation is supported for both source code input and option. Alternatively, the check for the floating point numbers can be disabled for all floating point values by enabling the <a href="#cmdoption-arg-ignoreallfloatingpointvalues">IgnoreAllFloatingPointValues</a> option.</p>
<p>Since values 0 and 0.0 are so common as the base counter of loops, or initialization values for sums, they are always accepted without warning, even if not present in the respective ignored values list.</p>
<h5 id="options-41">Options</h5>
<p>IgnoredIntegerValues</p>
<p>Semicolon-separated list of magic positive integers that will be accepted without a warning. Default values are {1, 2, 3, 4}, and 0 is accepted unconditionally.</p>
<p>IgnorePowersOf2IntegerValues</p>
<p>Boolean value indicating whether to accept all powers-of-two integer values without warning. Default value is false.</p>
<p>IgnoredFloatingPointValues</p>
<p>Semicolon-separated list of magic positive floating point values that will be accepted without a warning. Default values are {1.0, 100.0} and 0.0 is accepted unconditionally.</p>
<p>IgnoreAllFloatingPointValues</p>
<p>Boolean value indicating whether to accept all floating point values without warning. Default value is false.</p>
<p>IgnoreBitFieldsWidths</p>
<p>Boolean value indicating whether to accept magic numbers as bit field widths without warning. This is useful for example for register definitions which are generated from hardware specifications. Default value is true.</p>
<p>(Clang-Tidy original name: readability-magic-numbers)</p>


#### Make Member Function Const {#CT_RDB_MMFC}
<p>Finds non-static member functions that can be made const because the functions don’t use this in a non-const way.</p>
<p>This check tries to annotate methods according to <a href="https://isocpp.org/wiki/faq/const-correctness#logical-vs-physical-state">logical constness</a> (not physical constness). Therefore, it will suggest to add a const qualifier to a non-const method only if this method does something that is already possible though the public interface on a const pointer to the object:</p>
<ul>
<li>reading a public member variable</li>
<li>calling a public const-qualified member function</li>
<li>returning const-qualified this</li>
<li>passing const-qualified this as a parameter.</li>
</ul>
<p>This check will also suggest to add a const qualifier to a non-const method if this method uses private data and functions in a limited number of ways where logical constness and physical constness coincide:</p>
<ul>
<li>reading a member variable of builtin type</li>
</ul>
<p>Specifically, this check will not suggest to add a const to a non-const method if the method reads a private member variable of pointer type because that allows to modify the pointee which might not preserve logical constness. For the same reason, it does not allow to call private member functions or member functions on private member variables.</p>
<p>In addition, this check ignores functions that</p>
<ul>
<li>are declared virtual</li>
<li>contain a const_cast</li>
<li>are templated or part of a class template</li>
<li>have an empty body</li>
<li>do not (implicitly) use this at all (see <a href="readability-convert-member-functions-to-static.html">readability-convert-member-functions-to-static</a>).</li>
</ul>
<p>The following real-world examples will be preserved by the check:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> E1 {
  Pimpl &amp;getPimpl() <span class="dt">const</span>;
<span class="kw">public</span>:
  <span class="dt">int</span> &amp;get() {
    <span class="co">// Calling a private member function disables this check.</span>
    <span class="kw">return</span> getPimpl()-&gt;i;
  }
  ...
};

<span class="kw">class</span> E2 {
<span class="kw">public</span>:
  <span class="dt">const</span> <span class="dt">int</span> *get() <span class="dt">const</span>;
  <span class="co">// const_cast disables this check.</span>
  S *get() {
    <span class="kw">return</span> <span class="kw">const_cast</span>&lt;<span class="dt">int</span>*&gt;(<span class="kw">const_cast</span>&lt;<span class="dt">const</span> C*&gt;(<span class="kw">this</span>)-&gt;get());
  }
  ...
};</code></pre></div>
<p>After applying modifications as suggested by the check, running the check again might find more opportunities to mark member functions const.</p>
<p>(Clang-Tidy original name: readability-make-member-function-const)</p>


#### Misleading Indentation {#CT_RDB_MI}
<p>Correct indentation helps to understand code. Mismatch of the syntactical structure and the indentation of the code may hide serious problems. Missing braces can also make it significantly harder to read the code, therefore it is important to use braces.</p>
<p>The way to avoid dangling else is to always check that an else belongs to the if that begins in the same column.</p>
<p>You can omit braces when your inner part of e.g. an if statement has only one statement in it. Although in that case you should begin the next statement in the same column with the if.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// Dangling else:</span>
<span class="kw">if</span> (cond1)
  <span class="kw">if</span> (cond2)
    foo1();
<span class="kw">else</span>
  foo2();  <span class="co">// Wrong indentation: else belongs to if(cond2) statement.</span>

<span class="co">// Missing braces:</span>
<span class="kw">if</span> (cond1)
  foo1();
  foo2();  <span class="co">// Not guarded by if(cond1).</span></code></pre></div>
<h5 id="limitations-1">Limitations</h5>
<p>Note that this check only works as expected when the tabs or spaces are used consistently and not mixed.</p>
<p>(Clang-Tidy original name: readability-misleading-indentation)</p>


#### Misplaced Array Index {#CT_RDB_MAI}
<p>This check warns for unusual array index syntax.</p>
<p>The following code has unusual array index syntax:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> f(<span class="dt">int</span> *X, <span class="dt">int</span> Y) {
  Y[X] = <span class="dv">0</span>;
}</code></pre></div>
<p>becomes</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> f(<span class="dt">int</span> *X, <span class="dt">int</span> Y) {
  X[Y] = <span class="dv">0</span>;
}</code></pre></div>
<p>The check warns about such unusual syntax for readability reasons:</p>
<ul>
<li>There are programmers that are not familiar with this unusual syntax.</li>
<li>It is possible that variables are mixed up.</li>
</ul>
<p>(Clang-Tidy original name: readability-misplaced-array-index)</p>


#### Named Parameter {#CT_RDB_NP}
<p>Find functions with unnamed arguments.</p>
<p>The check implements the following rule originating in the Google C++ Style Guide:</p>
<p><a href="https://google.github.io/styleguide/cppguide.html\#Function_Declarations_and_Definitions" class="uri">https://google.github.io/styleguide/cppguide.html\#Function_Declarations_and_Definitions</a></p>
<p>All parameters should be named, with identical names in the declaration and implementation.</p>
<p>Corresponding cpplint.py check name: readability/function.</p>
<p>(Clang-Tidy original name: readability-named-parameter)</p>


#### Non Const Parameter {#CT_RDB_NCP}
<p>The check finds function parameters of a pointer type that could be changed to point to a constant type instead.</p>
<p>When const is used properly, many mistakes can be avoided. Advantages when using const properly:</p>
<ul>
<li>prevent unintentional modification of data;</li>
<li>get additional warnings such as using uninitialized data;</li>
<li>make it easier for developers to see possible side effects.</li>
</ul>
<p>This check is not strict about constness, it only warns when the constness will make the function interface safer.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// warning here; the declaration &quot;const char *p&quot; would make the function</span>
<span class="co">// interface safer.</span>
<span class="dt">char</span> f1(<span class="dt">char</span> *p) {
  <span class="kw">return</span> *p;
}

<span class="co">// no warning; the declaration could be more const &quot;const int * const p&quot; but</span>
<span class="co">// that does not make the function interface safer.</span>
<span class="dt">int</span> f2(<span class="dt">const</span> <span class="dt">int</span> *p) {
  <span class="kw">return</span> *p;
}

<span class="co">// no warning; making x const does not make the function interface safer</span>
<span class="dt">int</span> f3(<span class="dt">int</span> x) {
  <span class="kw">return</span> x;
}

<span class="co">// no warning; Technically, *p can be const (&quot;const struct S *p&quot;). But making</span>
<span class="co">// *p const could be misleading. People might think that it&#39;s safe to pass</span>
<span class="co">// const data to this function.</span>
<span class="kw">struct</span> S { <span class="dt">int</span> *a; <span class="dt">int</span> *b; };
<span class="dt">int</span> f3(<span class="kw">struct</span> S *p) {
  *(p-&gt;a) = <span class="dv">0</span>;
}</code></pre></div>
<p>(Clang-Tidy original name: readability-non-const-parameter)</p>


#### Qualified Auto {#CT_RDB_QA}
<p>Adds pointer qualifications to auto-typed variables that are deduced to pointers.</p>
<p><a href="https://llvm.org/docs/CodingStandards.html#beware-unnecessary-copies-with-auto">LLVM Coding Standards</a> advises to make it obvious if a auto typed variable is a pointer. This check will transform auto to auto * when the type is deduced to be a pointer.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">for</span> (<span class="kw">auto</span> Data : MutatablePtrContainer) {
  change(*Data);
}
<span class="kw">for</span> (<span class="kw">auto</span> Data : ConstantPtrContainer) {
  observe(*Data);
}</code></pre></div>
<p>Would be transformed into:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">for</span> (<span class="kw">auto</span> *Data : MutatablePtrContainer) {
  change(*Data);
}
<span class="kw">for</span> (<span class="dt">const</span> <span class="kw">auto</span> *Data : ConstantPtrContainer) {
  observe(*Data);
}</code></pre></div>
<p>Note const volatile qualified types will retain their const and volatile qualifiers. Pointers to pointers will not be fully qualified.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">const</span> <span class="kw">auto</span> Foo = cast&lt;<span class="dt">int</span> *&gt;(Baz1);
<span class="dt">const</span> <span class="kw">auto</span> Bar = cast&lt;<span class="dt">const</span> <span class="dt">int</span> *&gt;(Baz2);
<span class="dt">volatile</span> <span class="kw">auto</span> FooBar = cast&lt;<span class="dt">int</span> *&gt;(Baz3);
<span class="kw">auto</span> BarFoo = cast&lt;<span class="dt">int</span> **&gt;(Baz4);</code></pre></div>
<p>Would be transformed into:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">auto</span> *<span class="dt">const</span> Foo = cast&lt;<span class="dt">int</span> *&gt;(Baz1);
<span class="dt">const</span> <span class="kw">auto</span> *<span class="dt">const</span> Bar = cast&lt;<span class="dt">const</span> <span class="dt">int</span> *&gt;(Baz2);
<span class="kw">auto</span> *<span class="dt">volatile</span> FooBar = cast&lt;<span class="dt">int</span> *&gt;(Baz3);
<span class="kw">auto</span> *BarFoo = cast&lt;<span class="dt">int</span> **&gt;(Baz4);</code></pre></div>
<h5 id="options-15">Options</h5>
<p>AddConstToQualified</p>
<p>When set to true the check will add const qualifiers variables defined as auto * or auto &amp; when applicable. Default value is true.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">auto</span> Foo1 = cast&lt;<span class="dt">const</span> <span class="dt">int</span> *&gt;(Bar1);
<span class="kw">auto</span> *Foo2 = cast&lt;<span class="dt">const</span> <span class="dt">int</span> *&gt;(Bar2);
<span class="kw">auto</span> &amp;Foo3 = cast&lt;<span class="dt">const</span> <span class="dt">int</span> &amp;&gt;(Bar3);</code></pre></div>
<p>If AddConstToQualified is set to false, it will be transformed into:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">const</span> <span class="kw">auto</span> *Foo1 = cast&lt;<span class="dt">const</span> <span class="dt">int</span> *&gt;(Bar1);
<span class="kw">auto</span> *Foo2 = cast&lt;<span class="dt">const</span> <span class="dt">int</span> *&gt;(Bar2);
<span class="kw">auto</span> &amp;Foo3 = cast&lt;<span class="dt">const</span> <span class="dt">int</span> &amp;&gt;(Bar3);</code></pre></div>
<p>Otherwise it will be transformed into:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">const</span> <span class="kw">auto</span> *Foo1 = cast&lt;<span class="dt">const</span> <span class="dt">int</span> *&gt;(Bar1);
<span class="dt">const</span> <span class="kw">auto</span> *Foo2 = cast&lt;<span class="dt">const</span> <span class="dt">int</span> *&gt;(Bar2);
<span class="dt">const</span> <span class="kw">auto</span> &amp;Foo3 = cast&lt;<span class="dt">const</span> <span class="dt">int</span> &amp;&gt;(Bar3);</code></pre></div>
<p>Note in the LLVM alias, the default value is false.</p>
<p>(Clang-Tidy original name: readability-qualified-auto)</p>


#### Redundant Access Specifiers {#CT_RDB_RAS}
<p>Finds classes, structs, and unions containing redundant member (field and method) access specifiers.</p>
<h5 id="example-9">Example</h5>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> Foo {
<span class="kw">public</span>:
  <span class="dt">int</span> x;
  <span class="dt">int</span> y;
<span class="kw">public</span>:
  <span class="dt">int</span> z;
<span class="kw">protected</span>:
  <span class="dt">int</span> a;
<span class="kw">public</span>:
  <span class="dt">int</span> c;
}</code></pre></div>
<p>In the example above, the second public declaration can be removed without any changes of behavior.</p>
<h5 id="options-67">Options</h5>
<p>CheckFirstDeclaration</p>
<p>If set to true, the check will also diagnose if the first access specifier declaration is redundant (e.g. private inside class, or public inside struct or union). Default is false.</p>
<h6 id="example-10">Example</h6>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">struct</span> Bar {
<span class="kw">public</span>:
  <span class="dt">int</span> x;
}</code></pre></div>
<p>If CheckFirstDeclaration option is enabled, a warning about redundant access specifier will be emitted, because public is the default member access for structs.</p>
<p>(Clang-Tidy original name: readability-redundant-access-specifiers)</p>


#### Redundant Control Flow {#CT_RDB_RCF}
<p>This check looks for procedures (functions returning no value) with return statements at the end of the function. Such return statements are redundant.</p>
<p>Loop statements (for, while, do while) are checked for redundant continue statements at the end of the loop body.</p>
<p>Examples:</p>
<p>The following function f contains a redundant return statement:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">extern</span> <span class="dt">void</span> g();
<span class="dt">void</span> f() {
  g();
  <span class="kw">return</span>;
}</code></pre></div>
<p>becomes</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">extern</span> <span class="dt">void</span> g();
<span class="dt">void</span> f() {
  g();
}</code></pre></div>
<p>The following function k contains a redundant continue statement:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> k() {
  <span class="kw">for</span> (<span class="dt">int</span> i = <span class="dv">0</span>; i &lt; <span class="dv">10</span>; ++i) {
    <span class="kw">continue</span>;
  }
}</code></pre></div>
<p>becomes</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> k() {
  <span class="kw">for</span> (<span class="dt">int</span> i = <span class="dv">0</span>; i &lt; <span class="dv">10</span>; ++i) {
  }
}</code></pre></div>
<p>(Clang-Tidy original name: readability-redundant-control-flow)</p>


#### Redundant Declaration {#CT_RDB_RD}
<p>Finds redundant variable and function declarations.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">extern</span> <span class="dt">int</span> X;
<span class="dt">extern</span> <span class="dt">int</span> X;</code></pre></div>
<p>becomes</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">extern</span> <span class="dt">int</span> X;</code></pre></div>
<p>Such redundant declarations can be removed without changing program behaviour. They can for instance be unintentional left overs from previous refactorings when code has been moved around. Having redundant declarations could in worst case mean that there are typos in the code that cause bugs.</p>
<p>Normally the code can be automatically fixed, <strong>clang-tidy</strong> can remove the second declaration. However there are 2 cases when you need to fix the code manually:</p>
<ul>
<li>When the declarations are in different header files;</li>
<li>When multiple variables are declared together.</li>
</ul>
<h5 id="options-66">Options</h5>
<p>IgnoreMacros</p>
<p>If set to true, the check will not give warnings inside macros. Default is true.</p>
<p>(Clang-Tidy original name: readability-redundant-declaration)</p>


#### Redundant Function Ptr Dereference {#CT_RDB_RFPD}
<p>Finds redundant dereferences of a function pointer.</p>
<p>Before:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">int</span> f(<span class="dt">int</span>,<span class="dt">int</span>);
<span class="dt">int</span> (*p)(<span class="dt">int</span>, <span class="dt">int</span>) = &amp;f;

<span class="dt">int</span> i = (**p)(<span class="dv">10</span>, <span class="dv">50</span>);</code></pre></div>
<p>After:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">int</span> f(<span class="dt">int</span>,<span class="dt">int</span>);
<span class="dt">int</span> (*p)(<span class="dt">int</span>, <span class="dt">int</span>) = &amp;f;

<span class="dt">int</span> i = (*p)(<span class="dv">10</span>, <span class="dv">50</span>);</code></pre></div>
<p>(Clang-Tidy original name: readability-redundant-function-ptr-dereference)</p>


#### Redundant Member Init {#CT_RDB_RMI}
<p>Finds member initializations that are unnecessary because the same default constructor would be called if they were not present.</p>
<h5 id="example-16">Example</h5>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// Explicitly initializing the member s is unnecessary.</span>
<span class="kw">class</span> Foo {
<span class="kw">public</span>:
  Foo() : s() {}

<span class="kw">private</span>:
  std::string s;
};</code></pre></div>
<h5 id="options-84">Options</h5>
<p>IgnoreBaseInCopyConstructors</p>
<p>Default is false.</p>
<p>When true, the check will ignore unnecessary base class initializations within copy constructors, since some compilers issue warnings/errors when base classes are not explicitly intialized in copy constructors. For example, gcc with -Wextra or -Werror=extra issues warning or error base class 'Bar' should be explicitly initialized in the copy constructor if Bar() were removed in the following example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// Explicitly initializing member s and base class Bar is unnecessary.</span>
<span class="kw">struct</span> Foo : <span class="kw">public</span> Bar {
  <span class="co">// Remove s() below. If IgnoreBaseInCopyConstructors!=0, keep Bar().</span>
  Foo(<span class="dt">const</span> Foo&amp; foo) : Bar(), s() {}
  std::string s;
};</code></pre></div>
<p>(Clang-Tidy original name: readability-redundant-member-init)</p>


#### Redundant Preprocessor {#CT_RDB_RP}
<p>Finds potentially redundant preprocessor directives. At the moment the following cases are detected:</p>
<ul>
<li>#ifdef .. #endif pairs which are nested inside an outer pair with the same condition. For example:</li>
</ul>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="ot">#ifdef FOO</span>
<span class="ot">#ifdef FOO </span><span class="co">// inner ifdef is considered redundant</span>
<span class="dt">void</span> f();
<span class="ot">#endif</span>
<span class="ot">#endif</span></code></pre></div>
<ul>
<li>Same for #ifndef .. #endif pairs. For example:</li>
</ul>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="ot">#ifndef FOO</span>
<span class="ot">#ifndef FOO </span><span class="co">// inner ifndef is considered redundant</span>
<span class="dt">void</span> f();
<span class="ot">#endif</span>
<span class="ot">#endif</span></code></pre></div>
<ul>
<li>#ifndef inside an #ifdef with the same condition:</li>
</ul>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="ot">#ifdef FOO</span>
<span class="ot">#ifndef FOO </span><span class="co">// inner ifndef is considered redundant</span>
<span class="dt">void</span> f();
<span class="ot">#endif</span>
<span class="ot">#endif</span></code></pre></div>
<ul>
<li>#ifdef inside an #ifndef with the same condition:</li>
</ul>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="ot">#ifndef FOO</span>
<span class="ot">#ifdef FOO </span><span class="co">// inner ifdef is considered redundant</span>
<span class="dt">void</span> f();
<span class="ot">#endif</span>
<span class="ot">#endif</span></code></pre></div>
<ul>
<li>#if .. #endif pairs which are nested inside an outer pair with the same condition. For example:</li>
</ul>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="ot">#define FOO 4</span>
<span class="ot">#if FOO == 4</span>
<span class="ot">#if FOO == 4 </span><span class="co">// inner if is considered redundant</span>
<span class="dt">void</span> f();
<span class="ot">#endif</span>
<span class="ot">#endif</span></code></pre></div>
<p>(Clang-Tidy original name: readability-redundant-preprocessor)</p>


#### Redundant Smartptr Get {#CT_RDB_RSG}
<p>Find and remove redundant calls to smart pointer’s .get() method.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">ptr.get()-&gt;Foo()  ==&gt;  ptr-&gt;Foo()
*ptr.get()  ==&gt;  *ptr
*ptr-&gt;get()  ==&gt;  **ptr
<span class="kw">if</span> (ptr.get() == <span class="kw">nullptr</span>) ... =&gt; <span class="kw">if</span> (ptr == <span class="kw">nullptr</span>) ...</code></pre></div>
<p>IgnoreMacros</p>
<p>If this option is set to true (default is true), the check will not warn about calls inside macros.</p>
<p>(Clang-Tidy original name: readability-redundant-smartptr-get)</p>


#### Redundant String Cstr {#CT_RDB_RSC}
<p>Finds unnecessary calls to std::string::c_str() and std::string::data().</p>
<p>(Clang-Tidy original name: readability-redundant-string-cstr)</p>


#### Redundant String Init {#CT_RDB_RSI}
<p>Finds unnecessary string initializations.</p>
<h5 id="examples-1">Examples</h5>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// Initializing string with empty string literal is unnecessary.</span>
std::string a = <span class="st">&quot;&quot;</span>;
std::string b(<span class="st">&quot;&quot;</span>);

<span class="co">// becomes</span>

std::string a;
std::string b;

<span class="co">// Initializing a string_view with an empty string literal produces an</span>
<span class="co">// instance that compares equal to string_view().</span>
std::string_view a = <span class="st">&quot;&quot;</span>;
std::string_view b(<span class="st">&quot;&quot;</span>);

<span class="co">// becomes</span>
std::string_view a;
std::string_view b;</code></pre></div>
<h5 id="options-11">Options</h5>
<p>StringNames</p>
<p>Default is ::std::basic_string;::std::basic_string_view.</p>
<p>Semicolon-delimited list of class names to apply this check to. By default ::std::basic_string applies to std::string and std::wstring. Set to e.g. ::std::basic_string;llvm::StringRef;QString to perform this check on custom classes.</p>
<p>(Clang-Tidy original name: readability-redundant-string-init)</p>


#### Simplify Boolean Expr {#CT_RDB_SBE}
<p>Looks for boolean expressions involving boolean constants and simplifies them to use the appropriate boolean expression directly.</p>
<p>Examples:</p>
<table>
<thead>
<tr class="header">
<th align="left">Initial expression</th>
<th align="left">Result</th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td align="left">if (b == true)</td>
<td align="left">if (b)</td>
</tr>
<tr class="even">
<td align="left">if (b == false)</td>
<td align="left">if (!b)</td>
</tr>
<tr class="odd">
<td align="left">if (b &amp;&amp; true)</td>
<td align="left">if (b)</td>
</tr>
<tr class="even">
<td align="left">if (b &amp;&amp; false)</td>
<td align="left">if (false)</td>
</tr>
<tr class="odd">
<td align="left">if (b</td>
<td align="left"></td>
</tr>
<tr class="even">
<td align="left">if (b</td>
<td align="left"></td>
</tr>
<tr class="odd">
<td align="left">e ? true : false</td>
<td align="left">e</td>
</tr>
<tr class="even">
<td align="left">e ? false : true</td>
<td align="left">!e</td>
</tr>
<tr class="odd">
<td align="left">if (true) t(); else f();</td>
<td align="left">t();</td>
</tr>
<tr class="even">
<td align="left">if (false) t(); else f();</td>
<td align="left">f();</td>
</tr>
<tr class="odd">
<td align="left">if (e) return true; else return false;</td>
<td align="left">return e;</td>
</tr>
<tr class="even">
<td align="left">if (e) return false; else return true;</td>
<td align="left">return !e;</td>
</tr>
<tr class="odd">
<td align="left">if (e) b = true; else b = false;</td>
<td align="left">b = e;</td>
</tr>
<tr class="even">
<td align="left">if (e) b = false; else b = true;</td>
<td align="left">b = !e;</td>
</tr>
<tr class="odd">
<td align="left">if (e) return true; return false;</td>
<td align="left">return e;</td>
</tr>
<tr class="even">
<td align="left">if (e) return false; return true;</td>
<td align="left">return !e;</td>
</tr>
</tbody>
</table>
<p>The resulting expression e is modified as follows:</p>
<ol style="list-style-type: decimal">
<li>Unnecessary parentheses around the expression are removed.</li>
<li>Negated applications of ! are eliminated.</li>
<li>Negated applications of comparison operators are changed to use the opposite condition.</li>
<li>Implicit conversions of pointers, including pointers to members, to bool are replaced with explicit comparisons to nullptr in C++11 or NULL in C++98/03.</li>
<li>Implicit casts to bool are replaced with explicit casts to bool.</li>
<li>Object expressions with explicit operator bool conversion operators are replaced with explicit casts to bool.</li>
<li>Implicit conversions of integral types to bool are replaced with explicit comparisons to 0.</li>
</ol>
<p>Examples:</p>
<ol style="list-style-type: decimal">
<li><p>The ternary assignment bool b = (i &lt; 0) ? true : false; has redundant parentheses and becomes bool b = i &lt; 0;.</p></li>
<li><p>The conditional return if (!b) return false; return true; has an implied double negation and becomes return b;.</p></li>
<li><p>The conditional return if (i &lt; 0) return false; return true; becomes return i &gt;= 0;.</p></li>
</ol>
<p>The conditional return if (i != 0) return false; return true; becomes return i == 0;.</p>
<ol start="4" style="list-style-type: decimal">
<li>The conditional return if (p) return true; return false; has an implicit conversion of a pointer to bool and becomes return p != nullptr;.</li>
</ol>
<p>The ternary assignment bool b = (i &amp; 1) ? true : false; has an implicit conversion of i &amp; 1 to bool and becomes bool b = (i &amp; 1) != 0;.</p>
<ol start="5" style="list-style-type: decimal">
<li><p>The conditional return if (i &amp; 1) return true; else return false; has an implicit conversion of an integer quantity i &amp; 1 to bool and becomes return (i &amp; 1) != 0;</p></li>
<li><p>Given struct X { explicit operator bool(); };, and an instance x of struct X, the conditional return if (x) return true; return false; becomes return static_cast<bool>(x);</p></li>
</ol>
<h5 id="options-24">Options</h5>
<p>ChainedConditionalReturn</p>
<p>If true, conditional boolean return statements at the end of an if/else if chain will be transformed. Default is false.</p>
<p>ChainedConditionalAssignment</p>
<p>If true, conditional boolean assignments at the end of an if/else if chain will be transformed. Default is false.</p>
<p>(Clang-Tidy original name: readability-simplify-boolean-expr)</p>


#### Simplify Subscript Expr {#CT_RDB_SSE}
<p>This check simplifies subscript expressions. Currently this covers calling .data() and immediately doing an array subscript operation to obtain a single element, in which case simply calling operator[] suffice.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::string s = ...;
<span class="dt">char</span> c = s.data()[i];  <span class="co">// char c = s[i];</span></code></pre></div>
<h5 id="options-29">Options</h5>
<p>Types</p>
<p>The list of type(s) that triggers this check. Default is ::std::basic_string;::std::basic_string_view;::std::vector;::std::array</p>
<p>(Clang-Tidy original name: readability-simplify-subscript-expr)</p>


#### Static Accessed Through Instance {#CT_RDB_SATI}
<p>Checks for member expressions that access static members through instances, and replaces them with uses of the appropriate qualified-id.</p>
<p>Example:</p>
<p>The following code:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">struct</span> C {
  <span class="dt">static</span> <span class="dt">void</span> foo();
  <span class="dt">static</span> <span class="dt">int</span> x;
};

C *c1 = <span class="kw">new</span> C();
c1-&gt;foo();
c1-&gt;x;</code></pre></div>
<p>is changed to:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">C *c1 = <span class="kw">new</span> C();
C::foo();
C::x;</code></pre></div>
<p>(Clang-Tidy original name: readability-static-accessed-through-instance)</p>


#### Static Definition In Anonymous Namespace {#CT_RDB_SDIAN}
<p>Finds static function and variable definitions in anonymous namespace.</p>
<p>In this case, static is redundant, because anonymous namespace limits the visibility of definitions to a single translation unit.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">namespace</span> {
  <span class="dt">static</span> <span class="dt">int</span> a = <span class="dv">1</span>; <span class="co">// Warning.</span>
  <span class="dt">static</span> <span class="dt">const</span> b = <span class="dv">1</span>; <span class="co">// Warning.</span>
}</code></pre></div>
<p>The check will apply a fix by removing the redundant static qualifier.</p>
<p>(Clang-Tidy original name: readability-static-definition-in-anonymous-namespace)</p>


#### String Compare {#CT_RDB_SC}
<p>Finds string comparisons using the compare method.</p>
<p>A common mistake is to use the string’s compare method instead of using the equality or inequality operators. The compare method is intended for sorting functions and thus returns a negative number, a positive number or zero depending on the lexicographical relationship between the strings compared. If an equality or inequality check can suffice, that is recommended. This is recommended to avoid the risk of incorrect interpretation of the return value and to simplify the code. The string equality and inequality operators can also be faster than the compare method due to early termination.</p>
<p>Examples:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::string str1{<span class="st">&quot;a&quot;</span>};
std::string str2{<span class="st">&quot;b&quot;</span>};

<span class="co">// use str1 != str2 instead.</span>
<span class="kw">if</span> (str1.compare(str2)) {
}

<span class="co">// use str1 == str2 instead.</span>
<span class="kw">if</span> (!str1.compare(str2)) {
}

<span class="co">// use str1 == str2 instead.</span>
<span class="kw">if</span> (str1.compare(str2) == <span class="dv">0</span>) {
}

<span class="co">// use str1 != str2 instead.</span>
<span class="kw">if</span> (str1.compare(str2) != <span class="dv">0</span>) {
}

<span class="co">// use str1 == str2 instead.</span>
<span class="kw">if</span> (<span class="dv">0</span> == str1.compare(str2)) {
}

<span class="co">// use str1 != str2 instead.</span>
<span class="kw">if</span> (<span class="dv">0</span> != str1.compare(str2)) {
}

<span class="co">// Use str1 == &quot;foo&quot; instead.</span>
<span class="kw">if</span> (str1.compare(<span class="st">&quot;foo&quot;</span>) == <span class="dv">0</span>) {
}</code></pre></div>
<p>The above code examples shows the list of if-statements that this check will give a warning for. All of them uses compare to check if equality or inequality of two strings instead of using the correct operators.</p>
<p>(Clang-Tidy original name: readability-string-compare)</p>


#### Uniqueptr Delete Release {#CT_RDB_UDR}
<p>Replace delete <unique_ptr>.release() with <unique_ptr> = nullptr. The latter is shorter, simpler and does not require use of raw pointer APIs.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">std::unique_ptr&lt;<span class="dt">int</span>&gt; P;
<span class="kw">delete</span> P.release();

<span class="co">// becomes</span>

std::unique_ptr&lt;<span class="dt">int</span>&gt; P;
P = <span class="kw">nullptr</span>;</code></pre></div>
<p>(Clang-Tidy original name: readability-uniqueptr-delete-release)</p>


#### Uppercase Literal Suffix {#CT_RDB_ULS}
<p>cert-dcl16-c redirects here as an alias for this check. By default, only the suffixes that begin with l (l, ll, lu, llu, but not u, ul, ull) are diagnosed by that alias.</p>
<p>hicpp-uppercase-literal-suffix redirects here as an alias for this check.</p>
<p>Detects when the integral literal or floating point (decimal or hexadecimal) literal has a non-uppercase suffix and provides a fix-it hint with the uppercase suffix.</p>
<p>All valid combinations of suffixes are supported.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">auto</span> x = <span class="dv">1</span>;  <span class="co">// OK, no suffix.</span>

<span class="kw">auto</span> x = <span class="dv">1u</span>; <span class="co">// warning: integer literal suffix &#39;u&#39; is not upper-case</span>

<span class="kw">auto</span> x = <span class="dv">1U</span>; <span class="co">// OK, suffix is uppercase.</span>

...</code></pre></div>
<h5 id="options-53">Options</h5>
<p>NewSuffixes</p>
<p>Optionally, a list of the destination suffixes can be provided. When the suffix is found, a case-insensitive lookup in that list is made, and if a replacement is found that is different from the current suffix, then the diagnostic is issued. This allows for fine-grained control of what suffixes to consider and what their replacements should be.</p>
<h6 id="example-4">Example</h6>
<p>Given a list L;uL:</p>
<ul>
<li>l -&gt; L</li>
<li>L will be kept as is.</li>
<li>ul -&gt; uL</li>
<li>Ul -&gt; uL</li>
<li>UL -&gt; uL</li>
<li>uL will be kept as is.</li>
<li>ull will be kept as is, since it is not in the list</li>
<li>and so on.</li>
</ul>
<p>IgnoreMacros</p>
<p>If this option is set to true (default is true), the check will not warn about literal suffixes inside macros.</p>
<p>(Clang-Tidy original name: readability-uppercase-literal-suffix)</p>


#### Use Anyofallof {#CT_RDB_UA}
<p>Finds range-based for loops that can be replaced by a call to std::any_of or std::all_of. In C++ 20 mode, suggests std::ranges::any_of or std::ranges::all_of.</p>
<p>Example:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">bool</span> all_even(std::vector&lt;<span class="dt">int</span>&gt; V) {
  <span class="kw">for</span> (<span class="dt">int</span> I : V) {
    <span class="kw">if</span> (I % <span class="dv">2</span>)
      <span class="kw">return</span> <span class="kw">false</span>;
  }
  <span class="kw">return</span> <span class="kw">true</span>;
  <span class="co">// Replace loop by</span>
  <span class="co">// return std::ranges::all_of(V, [](int I) { return I % 2 == 0; });</span>
}</code></pre></div>
<p>(Clang-Tidy original name: readability-use-anyofallof)</p>


### Static Analyzer - C++

#### Inner Pointer {#CT_SA_CPP_IP}
<p>Check for inner pointers of C++ containers used after re/deallocation.</p>
<p>Many container methods in the C++ standard library are known to invalidate “references” (including actual references, iterators and raw pointers) to elements of the container. Using such references after they are invalidated causes undefined behavior, which is a common source of memory errors in C++ that this checker is capable of finding.</p>
<p>The checker is currently limited to std::string objects and doesn’t recognize some of the more sophisticated approaches to passing unowned pointers around, such as std::string_view.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> deref_after_assignment() {
  std::string s = <span class="st">&quot;llvm&quot;</span>;
  <span class="dt">const</span> <span class="dt">char</span> *c = s.data(); <span class="co">// note: pointer to inner buffer of &#39;std::string&#39; obtained here</span>
  s = <span class="st">&quot;clang&quot;</span>; <span class="co">// note: inner buffer of &#39;std::string&#39; reallocated by call to &#39;operator=&#39;</span>
  consume(c); <span class="co">// warn: inner pointer of container used after re/deallocation</span>
}

<span class="dt">const</span> <span class="dt">char</span> *return_temp(<span class="dt">int</span> x) {
  <span class="kw">return</span> std::to_string(x).c_str(); <span class="co">// warn: inner pointer of container used after re/deallocation</span>
  <span class="co">// note: pointer to inner buffer of &#39;std::string&#39; obtained here</span>
  <span class="co">// note: inner buffer of &#39;std::string&#39; deallocated by call to destructor</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-cplusplus.InnerPointer)</p>


#### Move {#CT_SA_CPP_M}
No documentation is available.

#### New Delete {#CT_SA_CPP_ND}
<p>Check for double-free and use-after-free problems. Traces memory managed by new/delete.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> f(<span class="dt">int</span> *p);

<span class="dt">void</span> testUseMiddleArgAfterDelete(<span class="dt">int</span> *p) {
  <span class="kw">delete</span> p;
  f(p); <span class="co">// warn: use after free</span>
}

<span class="kw">class</span> SomeClass {
<span class="kw">public</span>:
  <span class="dt">void</span> f();
};

<span class="dt">void</span> test() {
  SomeClass *c = <span class="kw">new</span> SomeClass;
  <span class="kw">delete</span> c;
  c-&gt;f(); <span class="co">// warn: use after free</span>
}

<span class="dt">void</span> test() {
  <span class="dt">int</span> *p = (<span class="dt">int</span> *)<span class="ot">__builtin_alloca</span>(<span class="kw">sizeof</span>(<span class="dt">int</span>));
  <span class="kw">delete</span> p; <span class="co">// warn: deleting memory allocated by alloca</span>
}

<span class="dt">void</span> test() {
  <span class="dt">int</span> *p = <span class="kw">new</span> <span class="dt">int</span>;
  <span class="kw">delete</span> p;
  <span class="kw">delete</span> p; <span class="co">// warn: attempt to free released</span>
}

<span class="dt">void</span> test() {
  <span class="dt">int</span> i;
  <span class="kw">delete</span> &amp;i; <span class="co">// warn: delete address of local</span>
}

<span class="dt">void</span> test() {
  <span class="dt">int</span> *p = <span class="kw">new</span> <span class="dt">int</span>[<span class="dv">1</span>];
  <span class="kw">delete</span>[] (++p);
    <span class="co">// warn: argument to &#39;delete[]&#39; is offset by 4 bytes</span>
    <span class="co">// from the start of memory allocated by &#39;new[]&#39;</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-cplusplus.NewDelete)</p>


#### New Delete Leaks {#CT_SA_CPP_NDL}
<p>Check for memory leaks. Traces memory managed by new/delete.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> test() {
  <span class="dt">int</span> *p = <span class="kw">new</span> <span class="dt">int</span>;
} <span class="co">// warn</span></code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-cplusplus.NewDeleteLeaks)</p>


#### Placement New Checker {#CT_SA_CPP_PNC}
<p>Check if default placement new is provided with pointers to sufficient storage capacity.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="ot">#include &lt;new&gt;</span>

<span class="dt">void</span> f() {
  <span class="dt">short</span> s;
  <span class="dt">long</span> *lp = ::<span class="kw">new</span> (&amp;s) <span class="dt">long</span>; <span class="co">// warn</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-cplusplus.PlacementNew)</p>


#### Pure Virtual Call {#CT_SA_CPP_PVC}
No documentation is available.

#### Self Assignment {#CT_SA_CPP_SA}
<p>Checks C++ copy and move assignment operators for self assignment.</p>
<p>(Clang-Tidy original name: clang-analyzer-cplusplus.SelfAssignment)</p>


### Static Analyzer - Core

#### Call And Message {#CT_SA_COR_CAM}
<p>Check for logical errors for function calls and Objective-C message expressions (e.g., uninitialized arguments, null function pointers).</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">//C</span>
<span class="dt">void</span> test() {
   <span class="dt">void</span> (*foo)(<span class="dt">void</span>);
   foo = <span class="dv">0</span>;
   foo(); <span class="co">// warn: function pointer is null</span>
 }

 <span class="co">// C++</span>
 <span class="kw">class</span> C {
 <span class="kw">public</span>:
   <span class="dt">void</span> f();
 };

 <span class="dt">void</span> test() {
   C *pc;
   pc-&gt;f(); <span class="co">// warn: object pointer is uninitialized</span>
 }

 <span class="co">// C++</span>
 <span class="kw">class</span> C {
 <span class="kw">public</span>:
   <span class="dt">void</span> f();
 };

 <span class="dt">void</span> test() {
   C *pc = <span class="dv">0</span>;
   pc-&gt;f(); <span class="co">// warn: object pointer is null</span>
 }

 <span class="co">// Objective-C</span>
 <span class="er">@</span>interface MyClass : NSObject
 <span class="er">@</span>property (readwrite,assign) id x;
 - (<span class="dt">long</span> <span class="dt">double</span>)longDoubleM;
 <span class="er">@</span>end

 <span class="dt">void</span> test() {
   MyClass *obj1;
   <span class="dt">long</span> <span class="dt">double</span> ld1 = [obj1 longDoubleM];
     <span class="co">// warn: receiver is uninitialized</span>
 }

 <span class="co">// Objective-C</span>
 <span class="er">@</span>interface MyClass : NSObject
 <span class="er">@</span>property (readwrite,assign) id x;
 - (<span class="dt">long</span> <span class="dt">double</span>)longDoubleM;
 <span class="er">@</span>end

 <span class="dt">void</span> test() {
   MyClass *obj1;
   id i = obj1.x; <span class="co">// warn: uninitialized object pointer</span>
 }

 <span class="co">// Objective-C</span>
 <span class="er">@</span>interface Subscriptable : NSObject
 - (id)objectAtIndexedSubscript:(<span class="dt">unsigned</span> <span class="dt">int</span>)index;
 <span class="er">@</span>end

 <span class="er">@</span>interface MyClass : Subscriptable
 <span class="er">@</span>property (readwrite,assign) id x;
 - (<span class="dt">long</span> <span class="dt">double</span>)longDoubleM;
 <span class="er">@</span>end

 <span class="dt">void</span> test() {
   MyClass *obj1;
   id i = obj1[<span class="dv">0</span>]; <span class="co">// warn: uninitialized object pointer</span>
 }</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-core.CallAndMessage)</p>


#### Divide Zero {#CT_SA_COR_DZ}
<p>Check for division by zero.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> test(<span class="dt">int</span> z) {
  <span class="kw">if</span> (z == <span class="dv">0</span>)
    <span class="dt">int</span> x = <span class="dv">1</span> / z; <span class="co">// warn</span>
}

<span class="dt">void</span> test() {
  <span class="dt">int</span> x = <span class="dv">1</span>;
  <span class="dt">int</span> y = x % <span class="dv">0</span>; <span class="co">// warn</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-core.DivideZero)</p>


#### Dynamic Type Propagation {#CT_SA_COR_DTP}
No documentation is available.

#### Non Nil String Constants {#CT_SA_COR_NNSC}
No documentation is available.

#### Non Null Param Checker {#CT_SA_COR_NNPC}
<p>Check for null pointers passed as arguments to a function whose arguments are references or marked with the ‘nonnull’ attribute.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">int</span> f(<span class="dt">int</span> *p) <span class="ot">__attribute__</span>((nonnull));

<span class="dt">void</span> test(<span class="dt">int</span> *p) {
  <span class="kw">if</span> (!p)
    f(p); <span class="co">// warn</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-core.NonNullParamChecker)</p>


#### Null Dereference {#CT_SA_COR_ND}
<p>Check for dereferences of null pointers.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// C</span>
<span class="dt">void</span> test(<span class="dt">int</span> *p) {
  <span class="kw">if</span> (p)
    <span class="kw">return</span>;

  <span class="dt">int</span> x = p[<span class="dv">0</span>]; <span class="co">// warn</span>
}

<span class="co">// C</span>
<span class="dt">void</span> test(<span class="dt">int</span> *p) {
  <span class="kw">if</span> (!p)
    *p = <span class="dv">0</span>; <span class="co">// warn</span>
}

<span class="co">// C++</span>
<span class="kw">class</span> C {
<span class="kw">public</span>:
  <span class="dt">int</span> x;
};

<span class="dt">void</span> test() {
  C *pc = <span class="dv">0</span>;
  <span class="dt">int</span> k = pc-&gt;x; <span class="co">// warn</span>
}

<span class="co">// Objective-C</span>
<span class="er">@</span>interface MyClass {
<span class="er">@</span>public
  <span class="dt">int</span> x;
}
<span class="er">@</span>end

<span class="dt">void</span> test() {
  MyClass *obj = <span class="dv">0</span>;
  obj-&gt;x = <span class="dv">1</span>; <span class="co">// warn</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-core.NullDereference)</p>


#### Stack Address Escape {#CT_SA_COR_SAE}
<p>Check that addresses to stack memory do not escape the function.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">char</span> <span class="dt">const</span> *p;

<span class="dt">void</span> test() {
  <span class="dt">char</span> <span class="dt">const</span> str[] = <span class="st">&quot;string&quot;</span>;
  p = str; <span class="co">// warn</span>
}

<span class="dt">void</span>* test() {
   <span class="kw">return</span> <span class="ot">__builtin_alloca</span>(<span class="dv">12</span>); <span class="co">// warn</span>
}

<span class="dt">void</span> test() {
  <span class="dt">static</span> <span class="dt">int</span> *x;
  <span class="dt">int</span> y;
  x = &amp;y; <span class="co">// warn</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-core.StackAddressEscape)</p>


#### Stack Address Escape Base {#CT_SA_COR_SAEB}
No documentation is available.

#### Undefined Binary Operator Result {#CT_SA_COR_UBOR}
<p>Check for undefined results of binary operators.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> test() {
  <span class="dt">int</span> x;
  <span class="dt">int</span> y = x + <span class="dv">1</span>; <span class="co">// warn: left operand is garbage</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-core.UndefinedBinaryOperatorResult)</p>


#### VLA Size {#CT_SA_COR_VS}
<p>Check for declarations of Variable Length Arrays of undefined or zero size.</p>
<p>Check for declarations of VLA of undefined or zero size.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> test() {
  <span class="dt">int</span> x;
  <span class="dt">int</span> vla1[x]; <span class="co">// warn: garbage as size</span>
}

<span class="dt">void</span> test() {
  <span class="dt">int</span> x = <span class="dv">0</span>;
  <span class="dt">int</span> vla2[x]; <span class="co">// warn: zero size</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-core.VLASize)</p>


### Static Analyzer - Core/Builtin

#### Builtin Functions {#CT_SA_BLT_BF}
No documentation is available.

#### No Return Functions {#CT_SA_BLT_NRF}
No documentation is available.

### Static Analyzer - Core/Uninitialized

#### Array Subscript {#CT_SA_UIN_AS}
<p>Check for uninitialized values used as array subscripts.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> test() {
  <span class="dt">int</span> i, a[<span class="dv">10</span>];
  <span class="dt">int</span> x = a[i]; <span class="co">// warn: array subscript is undefined</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-core.uninitialized.ArraySubscript)</p>


#### Assign {#CT_SA_UIN_A}
<p>Check for assigning uninitialized values.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> test() {
  <span class="dt">int</span> x;
  x |= <span class="dv">1</span>; <span class="co">// warn: left expression is uninitialized</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-core.uninitialized.Assign)</p>


#### Branch {#CT_SA_UIN_B}
<p>Check for uninitialized values used as branch conditions.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> test() {
  <span class="dt">int</span> x;
  <span class="kw">if</span> (x) <span class="co">// warn</span>
    <span class="kw">return</span>;
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-core.uninitialized.Branch)</p>


#### Captured Block Variable {#CT_SA_UIN_CBV}
<p>Check for blocks that capture uninitialized values.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> test() {
  <span class="dt">int</span> x;
  ^{ <span class="dt">int</span> y = x; }(); <span class="co">// warn</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-core.uninitialized.CapturedBlockVariable)</p>


#### Undef Return {#CT_SA_UIN_UR}
<p>Check for uninitialized values being returned to the caller.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">int</span> test() {
  <span class="dt">int</span> x;
  <span class="kw">return</span> x; <span class="co">// warn</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-core.uninitialized.UndefReturn)</p>


### Static Analyzer - Dead Code

#### Dead Stores {#CT_SA_DCD_DS}
<p>Check for values stored to variables that are never read afterwards.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> test() {
  <span class="dt">int</span> x;
  x = <span class="dv">1</span>; <span class="co">// warn</span>
}</code></pre></div>
<p>The WarnForDeadNestedAssignments option enables the checker to emit warnings for nested dead assignments. You can disable with the -analyzer-config deadcode.DeadStores:WarnForDeadNestedAssignments=false. <em>Defaults to true</em>.</p>
<p>Would warn for this e.g.: if ((y = make_int())) { }</p>
<p>(Clang-Tidy original name: clang-analyzer-deadcode.DeadStores)</p>


### Static Analyzer - Fuchsia

#### Handle Checker {#CT_SA_FCS_HC}
<p>Handles identify resources. Similar to pointers they can be leaked, double freed, or use after freed. This check attempts to find such problems.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> checkLeak08(<span class="dt">int</span> tag) {
  zx_handle_t sa, sb;
  zx_channel_create(<span class="dv">0</span>, &amp;sa, &amp;sb);
  <span class="kw">if</span> (tag)
    zx_handle_close(sa);
  use(sb); <span class="co">// Warn: Potential leak of handle</span>
  zx_handle_close(sb);
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-fuchsia.HandleChecker)</p>


### Static Analyzer - Nullability

#### Null Passed To Nonnull {#CT_SA_NUL_NPTN2}
<p>Warns when a null pointer is passed to a pointer which has a _Nonnull type.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">if</span> (name != nil)
  <span class="kw">return</span>;
<span class="co">// Warning: nil passed to a callee that requires a non-null 1st parameter</span>
NSString *greeting = [<span class="er">@</span><span class="st">&quot;Hello &quot;</span> stringByAppendingString:name];</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-nullability.NullPassedToNonnull)</p>


#### Null Returned From Nonnull {#CT_SA_NUL_NRFN2}
<p>Warns when a null pointer is returned from a function that has _Nonnull return type.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">- (nonnull id)firstChild {
  id result = nil;
  <span class="kw">if</span> ([_children count] &gt; <span class="dv">0</span>)
    result = _children[<span class="dv">0</span>];

  <span class="co">// Warning: nil returned from a method that is expected</span>
  <span class="co">// to return a non-null value</span>
  <span class="kw">return</span> result;
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-nullability.NullReturnedFromNonnull)</p>


#### Nullability Base {#CT_SA_NUL_NB}
No documentation is available.

#### Nullable Dereferenced {#CT_SA_NUL_ND}
<p>Warns when a nullable pointer is dereferenced.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">struct</span> LinkedList {
  <span class="dt">int</span> data;
  <span class="kw">struct</span> LinkedList *next;
};

<span class="kw">struct</span> LinkedList * _Nullable getNext(<span class="kw">struct</span> LinkedList *l);

<span class="dt">void</span> updateNextData(<span class="kw">struct</span> LinkedList *list, <span class="dt">int</span> newData) {
  <span class="kw">struct</span> LinkedList *next = getNext(list);
  <span class="co">// Warning: Nullable pointer is dereferenced</span>
  next-&gt;data = <span class="dv">7</span>;
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-nullability.NullableDereferenced)</p>


#### Nullable Passed To Nonnull {#CT_SA_NUL_NPTN}
<p>Warns when a nullable pointer is passed to a pointer which has a _Nonnull type.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">typedef</span> <span class="kw">struct</span> Dummy { <span class="dt">int</span> val; } Dummy;
Dummy *_Nullable returnsNullable();
<span class="dt">void</span> takesNonnull(Dummy *_Nonnull);

<span class="dt">void</span> test() {
  Dummy *p = returnsNullable();
  takesNonnull(p); <span class="co">// warn</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-nullability.NullablePassedToNonnull)</p>


#### Nullable Returned From Nonnull {#CT_SA_NUL_NRFN}
<p>Warns when a nullable pointer is returned from a function that has _Nonnull return type.</p>
<p>(Clang-Tidy original name: clang-analyzer-nullability.NullableReturnedFromNonnull)</p>


### Static Analyzer - OptIn/C++

#### Uninitialized Object {#CT_SA_OI_CPP_UO}
<p>This checker reports uninitialized fields in objects created after a constructor call. It doesn’t only find direct uninitialized fields, but rather makes a deep inspection of the object, analyzing all of it’s fields subfields. The checker regards inherited fields as direct fields, so one will receive warnings for uninitialized inherited data members as well.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// With Pedantic and CheckPointeeInitialization set to true</span>

<span class="kw">struct</span> A {
  <span class="kw">struct</span> B {
    <span class="dt">int</span> x; <span class="co">// note: uninitialized field &#39;this-&gt;b.x&#39;</span>
    <span class="co">// note: uninitialized field &#39;this-&gt;bptr-&gt;x&#39;</span>
    <span class="dt">int</span> y; <span class="co">// note: uninitialized field &#39;this-&gt;b.y&#39;</span>
    <span class="co">// note: uninitialized field &#39;this-&gt;bptr-&gt;y&#39;</span>
  };
  <span class="dt">int</span> *iptr; <span class="co">// note: uninitialized pointer &#39;this-&gt;iptr&#39;</span>
  B b;
  B *bptr;
  <span class="dt">char</span> *cptr; <span class="co">// note: uninitialized pointee &#39;this-&gt;cptr&#39;</span>

  A (B *bptr, <span class="dt">char</span> *cptr) : bptr(bptr), cptr(cptr) {}
};

<span class="dt">void</span> f() {
  A::B b;
  <span class="dt">char</span> c;
  A a(&amp;b, &amp;c); <span class="co">// warning: 6 uninitialized fields</span>
 <span class="co">//          after the constructor call</span>
}

<span class="co">// With Pedantic set to false and</span>
<span class="co">// CheckPointeeInitialization set to true</span>
<span class="co">// (every field is uninitialized)</span>

<span class="kw">struct</span> A {
  <span class="kw">struct</span> B {
    <span class="dt">int</span> x;
    <span class="dt">int</span> y;
  };
  <span class="dt">int</span> *iptr;
  B b;
  B *bptr;
  <span class="dt">char</span> *cptr;

  A (B *bptr, <span class="dt">char</span> *cptr) : bptr(bptr), cptr(cptr) {}
};

<span class="dt">void</span> f() {
  A::B b;
  <span class="dt">char</span> c;
  A a(&amp;b, &amp;c); <span class="co">// no warning</span>
}

<span class="co">// With Pedantic set to true and</span>
<span class="co">// CheckPointeeInitialization set to false</span>
<span class="co">// (pointees are regarded as initialized)</span>

<span class="kw">struct</span> A {
  <span class="kw">struct</span> B {
    <span class="dt">int</span> x; <span class="co">// note: uninitialized field &#39;this-&gt;b.x&#39;</span>
    <span class="dt">int</span> y; <span class="co">// note: uninitialized field &#39;this-&gt;b.y&#39;</span>
  };
  <span class="dt">int</span> *iptr; <span class="co">// note: uninitialized pointer &#39;this-&gt;iptr&#39;</span>
  B b;
  B *bptr;
  <span class="dt">char</span> *cptr;

  A (B *bptr, <span class="dt">char</span> *cptr) : bptr(bptr), cptr(cptr) {}
};

<span class="dt">void</span> f() {
  A::B b;
  <span class="dt">char</span> c;
  A a(&amp;b, &amp;c); <span class="co">// warning: 3 uninitialized fields</span>
 <span class="co">//          after the constructor call</span>
}</code></pre></div>
<p><strong>Options</strong></p>
<p>This checker has several options which can be set from command line (e.g. -analyzer-config optin.cplusplus.UninitializedObject:Pedantic=true):</p>
<ul>
<li>Pedantic (boolean). If to false, the checker won’t emit warnings for objects that don’t have at least one initialized field. Defaults to false.</li>
<li>NotesAsWarnings (boolean). If set to true, the checker will emit a warning for each uninitialized field, as opposed to emitting one warning per constructor call, and listing the uninitialized fields that belongs to it in notes. <em>Defaults to false</em>.</li>
<li>CheckPointeeInitialization (boolean). If set to false, the checker will not analyze the pointee of pointer/reference fields, and will only check whether the object itself is initialized. <em>Defaults to false</em>.</li>
<li>IgnoreRecordsWithField (string). If supplied, the checker will not analyze structures that have a field with a name or type name that matches the given pattern. <em>Defaults to “”</em>.</li>
</ul>
<p>(Clang-Tidy original name: clang-analyzer-optin.cplusplus.UninitializedObject)</p>


#### Virtual Call {#CT_SA_OI_CPP_VC}
<p>Check virtual function calls during construction or destruction.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> A {
<span class="kw">public</span>:
  A() {
    f(); <span class="co">// warn</span>
  }
  <span class="kw">virtual</span> <span class="dt">void</span> f();
};

<span class="kw">class</span> A {
<span class="kw">public</span>:
  ~A() {
    <span class="kw">this</span>-&gt;f(); <span class="co">// warn</span>
  }
  <span class="kw">virtual</span> <span class="dt">void</span> f();
};</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-optin.cplusplus.VirtualCall)</p>


### Static Analyzer - OptIn/Cocoa Localizability

#### Empty Localization Context Checker {#CT_SA_OI_OSX_LOC_ELCC}
<p>Check that NSLocalizedString macros include a comment for context.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">- (<span class="dt">void</span>)test {
  NSString *string = NSLocalizedString(<span class="er">@</span><span class="st">&quot;LocalizedString&quot;</span>, nil); <span class="co">// warn</span>
  NSString *string2 = NSLocalizedString(<span class="er">@</span><span class="st">&quot;LocalizedString&quot;</span>, <span class="er">@</span><span class="st">&quot; &quot;</span>); <span class="co">// warn</span>
  NSString *string3 = NSLocalizedStringWithDefaultValue(
    <span class="er">@</span><span class="st">&quot;LocalizedString&quot;</span>, nil, [[<span class="kw">NSBundle</span> <span class="kw">alloc</span>] <span class="kw">init</span>], <span class="kw">nil</span>,<span class="kw">@</span><span class="st">&quot;&quot;</span>); // <span class="kw">warn</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-optin.osx.cocoa.localizability.EmptyLocalizationContextChecker)</p>


#### Non Localized String Checker {#CT_SA_OI_OSX_LOC_NLSC}
<p>Warns about uses of non-localized NSStrings passed to UI methods expecting localized NSStrings.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">NSString *alarmText =
  NSLocalizedString(<span class="er">@</span><span class="st">&quot;Enabled&quot;</span>, <span class="er">@</span><span class="st">&quot;Indicates alarm is turned on&quot;</span>);
<span class="kw">if</span> (!isEnabled) {
  alarmText = <span class="er">@</span><span class="st">&quot;Disabled&quot;</span>;
}
UILabel *alarmStateLabel = [[<span class="kw">UILabel</span> <span class="kw">alloc</span>] <span class="kw">init</span>];

// <span class="kw">Warning:</span> <span class="kw">User</span>-<span class="kw">facing</span> <span class="kw">text</span> <span class="kw">should</span> <span class="kw">use</span> <span class="kw">localized</span> <span class="kw">string</span> <span class="kw">macro</span>
[<span class="kw">alarmStateLabel</span> <span class="kw">setText:alarmText</span>];</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-optin.osx.cocoa.localizability.NonLocalizedStringChecker)</p>


### Static Analyzer - OptIn/MPI

#### MPI-Checker {#CT_SA_OI_MPI_M}
<p>Checks MPI code.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> test() {
  <span class="dt">double</span> buf = <span class="dv">0</span>;
  MPI_Request sendReq1;
  MPI_Ireduce(MPI_IN_PLACE, &amp;buf, <span class="dv">1</span>, MPI_DOUBLE, MPI_SUM,
      <span class="dv">0</span>, MPI_COMM_WORLD, &amp;sendReq1);
} <span class="co">// warn: request &#39;sendReq1&#39; has no matching wait.</span>

<span class="dt">void</span> test() {
  <span class="dt">double</span> buf = <span class="dv">0</span>;
  MPI_Request sendReq;
  MPI_Isend(&amp;buf, <span class="dv">1</span>, MPI_DOUBLE, <span class="dv">0</span>, <span class="dv">0</span>, MPI_COMM_WORLD, &amp;sendReq);
  MPI_Irecv(&amp;buf, <span class="dv">1</span>, MPI_DOUBLE, <span class="dv">0</span>, <span class="dv">0</span>, MPI_COMM_WORLD, &amp;sendReq); <span class="co">// warn</span>
  MPI_Isend(&amp;buf, <span class="dv">1</span>, MPI_DOUBLE, <span class="dv">0</span>, <span class="dv">0</span>, MPI_COMM_WORLD, &amp;sendReq); <span class="co">// warn</span>
  MPI_Wait(&amp;sendReq, MPI_STATUS_IGNORE);
}

<span class="dt">void</span> missingNonBlocking() {
  <span class="dt">int</span> rank = <span class="dv">0</span>;
  MPI_Comm_rank(MPI_COMM_WORLD, &amp;rank);
  MPI_Request sendReq1[<span class="dv">10</span>][<span class="dv">10</span>][<span class="dv">10</span>];
  MPI_Wait(&amp;sendReq1[<span class="dv">1</span>][<span class="dv">7</span>][<span class="dv">9</span>], MPI_STATUS_IGNORE); <span class="co">// warn</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-optin.mpi.MPI-Checker)</p>


### Static Analyzer - OptIn/Performance

#### GCD Antipattern {#CT_SA_OI_PRF_GA}
<p>Check for performance anti-patterns when using Grand Central Dispatch.</p>
<p>(Clang-Tidy original name: clang-analyzer-optin.performance.GCDAntipattern)</p>


#### Padding {#CT_SA_OI_PRF_P}
<p>Check for excessively padded structs.</p>
<p>(Clang-Tidy original name: clang-analyzer-optin.performance.Padding)</p>


### Static Analyzer - OptIn/Portability

#### Unix API {#CT_SA_OI_PRT_UA}
<p>Finds implementation-defined behavior in UNIX/Posix functions.</p>
<p>(Clang-Tidy original name: clang-analyzer-optin.portability.UnixAPI)</p>


### Static Analyzer - OptIn/macOS

#### OSObject C-Style Cast {#CT_SA_OI_OSX_OCC}
No documentation is available.

### Static Analyzer - Security

#### Float Loop Counter {#CT_SA_SEC_FLC}
<p>Warn on using a floating point value as a loop counter (CERT: FLP30-C, FLP30-CPP).</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> test() {
  <span class="kw">for</span> (<span class="dt">float</span> x = <span class="fl">0.1f</span>; x &lt;= <span class="fl">1.0f</span>; x += <span class="fl">0.1f</span>) {} <span class="co">// warn</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-security.FloatLoopCounter)</p>


### Static Analyzer - Security/Insecure API

#### Deprecated Or Unsafe Buffer Handling {#CT_SA_SEC_DOUBH}
<p>Warn on occurrences of unsafe or deprecated buffer handling functions, which now have a secure variant: sprintf, vsprintf, scanf, wscanf, fscanf, fwscanf, vscanf, vwscanf, vfscanf, vfwscanf, sscanf, swscanf, vsscanf, vswscanf, swprintf, snprintf, vswprintf, vsnprintf, memcpy, memmove, strncpy, strncat, memset</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> test() {
  <span class="dt">char</span> buf [<span class="dv">5</span>];
  strncpy(buf, <span class="st">&quot;a&quot;</span>, <span class="dv">1</span>); <span class="co">// warn</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)</p>


#### Security Syntax Checker {#CT_SA_SEC_SSC}
No documentation is available.

#### Unchecked Return {#CT_SA_SEC_UR}
<p>Warn on uses of functions whose return values must be always checked.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> test() {
  setuid(<span class="dv">1</span>); <span class="co">// warn</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-security.insecureAPI.UncheckedReturn)</p>


#### bcmp {#CT_SA_SEC_B}
<p>Warn on uses of the ‘bcmp’ function.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> test() {
  bcmp(ptr0, ptr1, n); <span class="co">// warn</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-security.insecureAPI.bcmp)</p>


#### bcopy {#CT_SA_SEC_B2}
<p>Warn on uses of the ‘bcopy’ function.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> test() {
  bcopy(src, dst, n); <span class="co">// warn</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-security.insecureAPI.bcopy)</p>


#### bzero {#CT_SA_SEC_B3}
<p>Warn on uses of the ‘bzero’ function.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> test() {
  bzero(ptr, n); <span class="co">// warn</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-security.insecureAPI.bzero)</p>


#### decode Value Of ObjC Type {#CT_SA_SEC_DVOOT}
No documentation is available.

#### getpw {#CT_SA_SEC_G}
<p>Warn on uses of the ‘getpw’ function.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> test() {
  <span class="dt">char</span> buff[<span class="dv">1024</span>];
  getpw(<span class="dv">2</span>, buff); <span class="co">// warn</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-security.insecureAPI.getpw)</p>


#### gets {#CT_SA_SEC_G2}
<p>Warn on uses of the ‘gets’ function.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> test() {
  <span class="dt">char</span> buff[<span class="dv">1024</span>];
  gets(buff); <span class="co">// warn</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-security.insecureAPI.gets)</p>


#### mkstemp {#CT_SA_SEC_M}
<p>Warn when ‘mkstemp’ is passed fewer than 6 X’s in the format string.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> test() {
  mkstemp(<span class="st">&quot;XX&quot;</span>); <span class="co">// warn</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-security.insecureAPI.mkstemp)</p>


#### mktemp {#CT_SA_SEC_M2}
<p>Warn on uses of the mktemp function.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> test() {
  <span class="dt">char</span> *x = mktemp(<span class="st">&quot;/tmp/zxcv&quot;</span>); <span class="co">// warn: insecure, use mkstemp</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-security.insecureAPI.mktemp)</p>


#### rand {#CT_SA_SEC_R}
<p>Warn on uses of inferior random number generating functions (only if arc4random function is available): drand48, erand48, jrand48, lcong48, lrand48, mrand48, nrand48, random, rand_r.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> test() {
  random(); <span class="co">// warn</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-security.insecureAPI.rand)</p>


#### strcpy {#CT_SA_SEC_S}
<p>Warn on uses of the strcpy and strcat functions.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> test() {
  <span class="dt">char</span> x[<span class="dv">4</span>];
  <span class="dt">char</span> *y = <span class="st">&quot;abcd&quot;</span>;

  strcpy(x, y); <span class="co">// warn</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-security.insecureAPI.strcpy)</p>


#### vfork {#CT_SA_SEC_V}
<p>Warn on uses of the ‘vfork’ function.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> test() {
  vfork(); <span class="co">// warn</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-security.insecureAPI.vfork)</p>


### Static Analyzer - Unix

#### API {#CT_SA_UNX_A}
<p>Check calls to various UNIX/Posix functions: open, pthread_once, calloc, malloc, realloc, alloca.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">
<span class="co">// Currently the check is performed for apple targets only.</span>
<span class="dt">void</span> test(<span class="dt">const</span> <span class="dt">char</span> *path) {
  <span class="dt">int</span> fd = open(path, O_CREAT);
    <span class="co">// warn: call to &#39;open&#39; requires a third argument when the</span>
    <span class="co">// &#39;O_CREAT&#39; flag is set</span>
}

<span class="dt">void</span> f();

<span class="dt">void</span> test() {
  pthread_once_t pred = {<span class="bn">0x30B1BCBA</span>, {<span class="dv">0</span>}};
  pthread_once(&amp;pred, f);
    <span class="co">// warn: call to &#39;pthread_once&#39; uses the local variable</span>
}

<span class="dt">void</span> test() {
  <span class="dt">void</span> *p = malloc(<span class="dv">0</span>); <span class="co">// warn: allocation size of 0 bytes</span>
}

<span class="dt">void</span> test() {
  <span class="dt">void</span> *p = calloc(<span class="dv">0</span>, <span class="dv">42</span>); <span class="co">// warn: allocation size of 0 bytes</span>
}

<span class="dt">void</span> test() {
  <span class="dt">void</span> *p = malloc(<span class="dv">1</span>);
  p = realloc(p, <span class="dv">0</span>); <span class="co">// warn: allocation size of 0 bytes</span>
}

<span class="dt">void</span> test() {
  <span class="dt">void</span> *p = alloca(<span class="dv">0</span>); <span class="co">// warn: allocation size of 0 bytes</span>
}

<span class="dt">void</span> test() {
  <span class="dt">void</span> *p = valloc(<span class="dv">0</span>); <span class="co">// warn: allocation size of 0 bytes</span>
}
</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-unix.API)</p>


#### Malloc {#CT_SA_UNX_M}
<p>Check for memory leaks, double free, and use-after-free problems. Traces memory managed by malloc()/free().</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">
<span class="dt">void</span> test() {
  <span class="dt">int</span> *p = malloc(<span class="dv">1</span>);
  free(p);
  free(p); <span class="co">// warn: attempt to free released memory</span>
}

<span class="dt">void</span> test() {
  <span class="dt">int</span> *p = malloc(<span class="kw">sizeof</span>(<span class="dt">int</span>));
  free(p);
  *p = <span class="dv">1</span>; <span class="co">// warn: use after free</span>
}

<span class="dt">void</span> test() {
  <span class="dt">int</span> *p = malloc(<span class="dv">1</span>);
  <span class="kw">if</span> (p)
    <span class="kw">return</span>; <span class="co">// warn: memory is never released</span>
}

<span class="dt">void</span> test() {
  <span class="dt">int</span> a[] = { <span class="dv">1</span> };
  free(a); <span class="co">// warn: argument is not allocated by malloc</span>
}

<span class="dt">void</span> test() {
  <span class="dt">int</span> *p = malloc(<span class="kw">sizeof</span>(<span class="dt">char</span>));
  p = p - <span class="dv">1</span>;
  free(p); <span class="co">// warn: argument to free() is offset by -4 bytes</span>
}
</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-unix.Malloc)</p>


#### Malloc Sizeof {#CT_SA_UNX_MS}
<p>Check for dubious malloc arguments involving sizeof.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> test() {
  <span class="dt">long</span> *p = malloc(<span class="kw">sizeof</span>(<span class="dt">short</span>));
    <span class="co">// warn: result is converted to &#39;long *&#39;, which is</span>
    <span class="co">// incompatible with operand type &#39;short&#39;</span>
  free(p);
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-unix.MallocSizeof)</p>


#### Mismatched Deallocator {#CT_SA_UNX_MD}
<p>Check for mismatched deallocators.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="co">// C, C++</span>
<span class="dt">void</span> test() {
  <span class="dt">int</span> *p = (<span class="dt">int</span> *)malloc(<span class="kw">sizeof</span>(<span class="dt">int</span>));
  <span class="kw">delete</span> p; <span class="co">// warn</span>
}

<span class="co">// C, C++</span>
<span class="dt">void</span> __attribute((ownership_returns(malloc))) *user_malloc(size_t);

<span class="dt">void</span> test() {
  <span class="dt">int</span> *p = (<span class="dt">int</span> *)user_malloc(<span class="kw">sizeof</span>(<span class="dt">int</span>));
  <span class="kw">delete</span> p; <span class="co">// warn</span>
}

<span class="co">// C, C++</span>
<span class="dt">void</span> test() {
  <span class="dt">int</span> *p = <span class="kw">new</span> <span class="dt">int</span>;
  free(p); <span class="co">// warn</span>
}

<span class="co">// C, C++</span>
<span class="dt">void</span> test() {
  <span class="dt">int</span> *p = <span class="kw">new</span> <span class="dt">int</span>[<span class="dv">1</span>];
  realloc(p, <span class="kw">sizeof</span>(<span class="dt">long</span>)); <span class="co">// warn</span>
}

<span class="co">// C, C++</span>
<span class="kw">template</span> &lt;<span class="kw">typename</span> T&gt;
<span class="kw">struct</span> SimpleSmartPointer {
  T *ptr;

  <span class="kw">explicit</span> SimpleSmartPointer(T *p = <span class="dv">0</span>) : ptr(p) {}
  ~SimpleSmartPointer() {
    <span class="kw">delete</span> ptr; <span class="co">// warn</span>
  }
};

<span class="dt">void</span> test() {
  SimpleSmartPointer&lt;<span class="dt">int</span>&gt; a((<span class="dt">int</span> *)malloc(<span class="dv">4</span>));
}

<span class="co">// C++</span>
<span class="dt">void</span> test() {
  <span class="dt">int</span> *p = (<span class="dt">int</span> *)<span class="kw">operator</span> <span class="kw">new</span>(<span class="dv">0</span>);
  <span class="kw">delete</span>[] p; <span class="co">// warn</span>
}

<span class="co">// Objective-C, C++</span>
<span class="dt">void</span> test(NSUInteger dataLength) {
  <span class="dt">int</span> *p = <span class="kw">new</span> <span class="dt">int</span>;
  NSData *d = [NSData dataWithBytesNoCopy:p
               length:<span class="kw">sizeof</span>(<span class="dt">int</span>) freeWhenDone:<span class="dv">1</span>];
    <span class="co">// warn +dataWithBytesNoCopy:length:freeWhenDone: cannot take</span>
    <span class="co">// ownership of memory allocated by &#39;new&#39;</span>
}
</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-unix.MismatchedDeallocator)</p>


#### Vfork {#CT_SA_UNX_V}
<p>Check for proper usage of vfork.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">int</span> test(<span class="dt">int</span> x) {
  pid_t pid = vfork(); <span class="co">// warn</span>
  <span class="kw">if</span> (pid != <span class="dv">0</span>)
    <span class="kw">return</span> <span class="dv">0</span>;

  <span class="kw">switch</span> (x) {
  <span class="kw">case</span> <span class="dv">0</span>:
    pid = <span class="dv">1</span>;
    execl(<span class="st">&quot;&quot;</span>, <span class="st">&quot;&quot;</span>, <span class="dv">0</span>);
    _exit(<span class="dv">1</span>);
    <span class="kw">break</span>;
  <span class="kw">case</span> <span class="dv">1</span>:
    x = <span class="dv">0</span>; <span class="co">// warn: this assignment is prohibited</span>
    <span class="kw">break</span>;
  <span class="kw">case</span> <span class="dv">2</span>:
    foo(); <span class="co">// warn: this function call is prohibited</span>
    <span class="kw">break</span>;
  <span class="kw">default</span>:
    <span class="kw">return</span> <span class="dv">0</span>; <span class="co">// warn: return is prohibited</span>
  }

  <span class="kw">while</span>(<span class="dv">1</span>);
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-unix.Vfork)</p>


### Static Analyzer - Unix/C string

#### Bad Size Arg {#CT_SA_UNX_BSA}
<p>Check the size argument passed into C string functions for common erroneous patterns. Use -Wno-strncat-size compiler option to mute other strncat-related compiler warnings.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> test() {
  <span class="dt">char</span> dest[<span class="dv">3</span>];
  strncat(dest, <span class="st">&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;*&quot;</span>, <span class="kw">sizeof</span>(dest));
    <span class="co">// warn: potential buffer overflow</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-unix.cstring.BadSizeArg)</p>


#### Null Arg {#CT_SA_UNX_NA}
<p>Check for null pointers being passed as arguments to C string functions: strlen, strnlen, strcpy, strncpy, strcat, strncat, strcmp, strncmp, strcasecmp, strncasecmp.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">int</span> test() {
  <span class="kw">return</span> strlen(<span class="dv">0</span>); <span class="co">// warn</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-unix.cstring.NullArg)</p>


### Static Analyzer - Webkit

#### No Uncounted Member Checker {#CT_SA_WBK_NUMC}
<p>Raw pointers and references to uncounted types can’t be used as class members. Only ref-counted types are allowed.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">struct</span> RefCntbl {
  <span class="dt">void</span> ref() {}
  <span class="dt">void</span> deref() {}
};

<span class="kw">struct</span> Foo {
  RefCntbl * ptr; <span class="co">// warn</span>
  RefCntbl &amp; ptr; <span class="co">// warn</span>
  <span class="co">// ...</span>
};</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-webkit.NoUncountedMemberChecker)</p>


#### Ref Cntbl Base Virtual Dtor {#CT_SA_WBK_RCBVD}
<p>All uncounted types used as base classes must have a virtual destructor.</p>
<p>Ref-counted types hold their ref-countable data by a raw pointer and allow implicit upcasting from ref-counted pointer to derived type to ref-counted pointer to base type. This might lead to an object of (dynamic) derived type being deleted via pointer to the base class type which C++ standard defines as UB in case the base class doesn’t have virtual destructor [expr.delete].</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">struct</span> RefCntblBase {
  <span class="dt">void</span> ref() {}
  <span class="dt">void</span> deref() {}
};

<span class="kw">struct</span> Derived : RefCntblBase { }; <span class="co">// warn</span></code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-webkit.RefCntblBaseVirtualDtor)</p>


#### Uncounted Lambda Captures Checker {#CT_SA_WBK_ULCC}
No documentation is available.

### Static Analyzer - macOS

#### API {#CT_SA_OSX_A}
<p>Check for proper uses of various Apple APIs.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> test() {
  dispatch_once_t pred = <span class="dv">0</span>;
  dispatch_once(&amp;pred, ^(){}); <span class="co">// warn: dispatch_once uses local</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-osx.API)</p>


#### Mach Interface Generator Calling Convention {#CT_SA_OSX_MIGCC}
No documentation is available.

#### Ns Or CF Error Deref Checker {#CT_SA_OSX_NOCEDC}
No documentation is available.

#### Number Object Conversion {#CT_SA_OSX_NOC}
<p>Check for erroneous conversions of objects representing numbers into numbers.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">NSNumber *photoCount = [albumDescriptor objectForKey:<span class="er">@</span><span class="st">&quot;PhotoCount&quot;</span>];
<span class="co">// Warning: Comparing a pointer value of type &#39;NSNumber *&#39;</span>
<span class="co">// to a scalar integer value</span>
<span class="kw">if</span> (photoCount &gt; <span class="dv">0</span>) {
  [self displayPhotos];
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-osx.NumberObjectConversion)</p>


#### OSObject Retain Count {#CT_SA_OSX_ORC}
No documentation is available.

#### Obj C Property {#CT_SA_OSX_OCP}
<p>Check for proper uses of Objective-C properties.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">NSNumber *photoCount = [albumDescriptor objectForKey:<span class="er">@</span><span class="st">&quot;PhotoCount&quot;</span>];
<span class="co">// Warning: Comparing a pointer value of type &#39;NSNumber *&#39;</span>
<span class="co">// to a scalar integer value</span>
<span class="kw">if</span> (photoCount &gt; <span class="dv">0</span>) {
  [self displayPhotos];
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-osx.ObjCProperty)</p>


#### Sec Keychain API {#CT_SA_OSX_SKA}
<p>Check for proper uses of Secure Keychain APIs.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> test() {
  <span class="dt">unsigned</span> <span class="dt">int</span> *ptr = <span class="dv">0</span>;
  UInt32 length;

  SecKeychainItemFreeContent(ptr, &amp;length);
    <span class="co">// warn: trying to free data which has not been allocated</span>
}

<span class="dt">void</span> test() {
  <span class="dt">unsigned</span> <span class="dt">int</span> *ptr = <span class="dv">0</span>;
  UInt32 *length = <span class="dv">0</span>;
  <span class="dt">void</span> *outData;

  OSStatus st =
    SecKeychainItemCopyContent(<span class="dv">2</span>, ptr, ptr, length, outData);
    <span class="co">// warn: data is not released</span>
}

<span class="dt">void</span> test() {
  <span class="dt">unsigned</span> <span class="dt">int</span> *ptr = <span class="dv">0</span>;
  UInt32 *length = <span class="dv">0</span>;
  <span class="dt">void</span> *outData;

  OSStatus st =
    SecKeychainItemCopyContent(<span class="dv">2</span>, ptr, ptr, length, &amp;outData);

  SecKeychainItemFreeContent(ptr, outData);
    <span class="co">// warn: only call free if a non-NULL buffer was returned</span>
}

<span class="dt">void</span> test() {
  <span class="dt">unsigned</span> <span class="dt">int</span> *ptr = <span class="dv">0</span>;
  UInt32 *length = <span class="dv">0</span>;
  <span class="dt">void</span> *outData;

  OSStatus st =
    SecKeychainItemCopyContent(<span class="dv">2</span>, ptr, ptr, length, &amp;outData);

  st = SecKeychainItemCopyContent(<span class="dv">2</span>, ptr, ptr, length, &amp;outData);
    <span class="co">// warn: release data before another call to the allocator</span>

  <span class="kw">if</span> (st == noErr)
    SecKeychainItemFreeContent(ptr, outData);
}

<span class="dt">void</span> test() {
  SecKeychainItemRef itemRef = <span class="dv">0</span>;
  SecKeychainAttributeInfo *info = <span class="dv">0</span>;
  SecItemClass *itemClass = <span class="dv">0</span>;
  SecKeychainAttributeList *attrList = <span class="dv">0</span>;
  UInt32 *length = <span class="dv">0</span>;
  <span class="dt">void</span> *outData = <span class="dv">0</span>;

  OSStatus st =
    SecKeychainItemCopyAttributesAndData(itemRef, info,
                                         itemClass, &amp;attrList,
                                         length, &amp;outData);

  SecKeychainItemFreeContent(attrList, outData);
    <span class="co">// warn: deallocator doesn&#39;t match the allocator</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-osx.SecKeychainAPI)</p>


### Static Analyzer - macOS/Cocoa API

#### At Sync {#CT_SA_OSX_CCA_AS}
<p>Check for nil pointers used as mutexes for <span class="citation">@synchronized</span>.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> test(id x) {
  <span class="kw">if</span> (!x)
    <span class="er">@</span>synchronized(x) {} <span class="co">// warn: nil value used as mutex</span>
}

<span class="dt">void</span> test() {
  id y;
  <span class="er">@</span>synchronized(y) {} <span class="co">// warn: uninitialized value used as mutex</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-osx.cocoa.AtSync)</p>


#### Autorelease Write {#CT_SA_OSX_CCA_AW}
<p>Warn about potentially crashing writes to autoreleasing objects from different autoreleasing pools in Objective-C.</p>
<p>(Clang-Tidy original name: clang-analyzer-osx.cocoa.AutoreleaseWrite)</p>


#### Class Release {#CT_SA_OSX_CCA_CR}
<p>Check for sending ‘retain’, ‘release’, or ‘autorelease’ directly to a Class.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="er">@</span>interface MyClass : NSObject
<span class="er">@</span>end

<span class="dt">void</span> test(<span class="dt">void</span>) {
  [MyClass release]; <span class="co">// warn</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-osx.cocoa.ClassRelease)</p>


#### Dealloc {#CT_SA_OSX_CCA_D}
<p>Warn about Objective-C classes that lack a correct implementation of -dealloc</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="er">@</span>interface MyObject : NSObject {
  id _myproperty;
}
<span class="er">@</span>end

<span class="er">@</span>implementation MyObject <span class="co">// warn: lacks &#39;dealloc&#39;</span>
<span class="er">@</span>end

<span class="er">@</span>interface MyObject : NSObject {}
<span class="er">@</span>property(assign) id myproperty;
<span class="er">@</span>end

<span class="er">@</span>implementation MyObject <span class="co">// warn: does not send &#39;dealloc&#39; to super</span>
- (<span class="dt">void</span>)dealloc {
  self.myproperty = <span class="dv">0</span>;
}
<span class="er">@</span>end

<span class="er">@</span>interface MyObject : NSObject {
  id _myproperty;
}
<span class="er">@</span>property(retain) id myproperty;
<span class="er">@</span>end

<span class="er">@</span>implementation MyObject
<span class="er">@</span>synthesize myproperty = _myproperty;
  <span class="co">// warn: var was retained but wasn&#39;t released</span>
- (<span class="dt">void</span>)dealloc {
  [super dealloc];
}
<span class="er">@</span>end

<span class="er">@</span>interface MyObject : NSObject {
  id _myproperty;
}
<span class="er">@</span>property(assign) id myproperty;
<span class="er">@</span>end

<span class="er">@</span>implementation MyObject
<span class="er">@</span>synthesize myproperty = _myproperty;
  <span class="co">// warn: var wasn&#39;t retained but was released</span>
- (<span class="dt">void</span>)dealloc {
  [_myproperty release];
  [super dealloc];
}
<span class="er">@</span>end</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-osx.cocoa.Dealloc)</p>


#### Incompatible Method Types {#CT_SA_OSX_CCA_IMT}
<p>Warn about Objective-C method signatures with type incompatibilities.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="er">@</span>interface MyClass1 : NSObject
- (<span class="dt">int</span>)foo;
<span class="er">@</span>end

<span class="er">@</span>implementation MyClass1
- (<span class="dt">int</span>)foo { <span class="kw">return</span> <span class="dv">1</span>; }
<span class="er">@</span>end

<span class="er">@</span>interface MyClass2 : MyClass1
- (<span class="dt">float</span>)foo;
<span class="er">@</span>end

<span class="er">@</span>implementation MyClass2
- (<span class="dt">float</span>)foo { <span class="kw">return</span> <span class="fl">1.0</span>; } <span class="co">// warn</span>
<span class="er">@</span>end</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-osx.cocoa.IncompatibleMethodTypes)</p>


#### Loops {#CT_SA_OSX_CCA_L}
<p>Improved modeling of loops using Cocoa collection types.</p>
<p>(Clang-Tidy original name: clang-analyzer-osx.cocoa.Loops)</p>


#### Missing Super Call {#CT_SA_OSX_CCA_MSC}
<p>Warn about Objective-C methods that lack a necessary call to super.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="er">@</span>interface Test : UIViewController
<span class="er">@</span>end
<span class="er">@</span>implementation test
- (<span class="dt">void</span>)viewDidLoad {} <span class="co">// warn</span>
<span class="er">@</span>end</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-osx.cocoa.MissingSuperCall)</p>


#### NS Autorelease Pool {#CT_SA_OSX_CCA_NAP}
<p>Warn for suboptimal uses of NSAutoreleasePool in Objective-C GC mode.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> test() {
  NSAutoreleasePool *pool = [[<span class="kw">NSAutoreleasePool</span> <span class="kw">alloc</span>] <span class="kw">init</span>];
  [<span class="kw">pool</span> <span class="kw">release</span>]; // <span class="kw">warn</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-osx.cocoa.NSAutoreleasePool)</p>


#### NS Error {#CT_SA_OSX_CCA_NE}
<p>Check usage of NSError parameters.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="er">@</span>interface A : NSObject
- (<span class="dt">void</span>)foo:(NSError <span class="st">&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;</span>)error;
<span class="er">@</span>end

<span class="er">@</span>implementation A
- (<span class="dt">void</span>)foo:(NSError <span class="st">&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;</span>)error {
  <span class="co">// warn: method accepting NSError&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot; should have a non-void</span>
  <span class="co">// return value</span>
}
<span class="er">@</span>end

<span class="er">@</span>interface A : NSObject
- (BOOL)foo:(NSError <span class="st">&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;</span>)error;
<span class="er">@</span>end

<span class="er">@</span>implementation A
- (BOOL)foo:(NSError <span class="st">&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;</span>)error {
  *error = <span class="dv">0</span>; <span class="co">// warn: potential null dereference</span>
  <span class="kw">return</span> <span class="dv">0</span>;
}
<span class="er">@</span>end</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-osx.cocoa.NSError)</p>


#### Nil Arg {#CT_SA_OSX_CCA_NA}
<p>Check for prohibited nil arguments to ObjC method calls.</p>
<ul>
<li>caseInsensitiveCompare:</li>
<li>compare:</li>
<li>compare:options:</li>
<li>compare:options:range:</li>
<li>compare:options:range:locale:</li>
<li>componentsSeparatedByCharactersInSet:</li>
<li>initWithFormat:</li>
</ul>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">NSComparisonResult test(NSString *s) {
  NSString *aString = nil;
  <span class="kw">return</span> [s caseInsensitiveCompare:aString];
    <span class="co">// warn: argument to &#39;NSString&#39; method</span>
    <span class="co">// &#39;caseInsensitiveCompare:&#39; cannot be nil</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-osx.cocoa.NilArg)</p>


#### Non Nil Return Value {#CT_SA_OSX_CCA_NNRV}
<p>Models the APIs that are guaranteed to return a non-nil value.</p>
<p>(Clang-Tidy original name: clang-analyzer-osx.cocoa.NonNilReturnValue)</p>


#### Obj C Generics {#CT_SA_OSX_CCA_OCG}
<p>Check for type errors when using Objective-C generics.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">NSMutableArray *names = [NSMutableArray array];
NSMutableArray *birthDates = names;

<span class="co">// Warning: Conversion from value of type &#39;NSDate *&#39;</span>
<span class="co">// to incompatible type &#39;NSString *&#39;</span>
[birthDates addObject: [NSDate date]];</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-osx.cocoa.ObjCGenerics)</p>


#### Retain Count {#CT_SA_OSX_CCA_RC}
<p>Check for leaks and improper reference count management</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> test() {
  NSString *s = [[<span class="kw">NSString</span> <span class="kw">alloc</span>] <span class="kw">init</span>]; // <span class="kw">warn</span>
}

<span class="kw">CFStringRef</span> <span class="kw">test</span>(<span class="kw">char</span> *<span class="kw">bytes</span>) {
  <span class="kw">return</span> <span class="kw">CFStringCreateWithCStringNoCopy</span>(
           <span class="kw">0</span>, <span class="kw">bytes</span>, <span class="kw">NSNEXTSTEPStringEncoding</span>, <span class="kw">0</span>); // <span class="kw">warn</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-osx.cocoa.RetainCount)</p>


#### Retain Count Base {#CT_SA_OSX_CCA_RCB}
No documentation is available.

#### Run Loop Autorelease Leak {#CT_SA_OSX_CCA_RLAL}
<p>Check for leaked memory in autorelease pools that will never be drained.</p>
<p>(Clang-Tidy original name: clang-analyzer-osx.cocoa.RunLoopAutoreleaseLeak)</p>


#### Self Init {#CT_SA_OSX_CCA_SI}
<p>Check that ‘self’ is properly initialized inside an initializer method.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="er">@</span>interface MyObj : NSObject {
  id x;
}
- (id)init;
<span class="er">@</span>end

<span class="er">@</span>implementation MyObj
- (id)init {
  [super init];
  x = <span class="dv">0</span>; <span class="co">// warn: instance variable used while &#39;self&#39; is not</span>
         <span class="co">// initialized</span>
  <span class="kw">return</span> <span class="dv">0</span>;
}
<span class="er">@</span>end

<span class="er">@</span>interface MyObj : NSObject
- (id)init;
<span class="er">@</span>end

<span class="er">@</span>implementation MyObj
- (id)init {
  [super init];
  <span class="kw">return</span> self; <span class="co">// warn: returning uninitialized &#39;self&#39;</span>
}
<span class="er">@</span>end</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-osx.cocoa.SelfInit)</p>


#### Super Dealloc {#CT_SA_OSX_CCA_SD}
<p>Warn about improper use of ‘<a href="#CT_SA_OSX_CCA_SD">super dealloc</a>’ in Objective-C.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="er">@</span>interface SuperDeallocThenReleaseIvarClass : NSObject {
  NSObject *_ivar;
}
<span class="er">@</span>end

<span class="er">@</span>implementation SuperDeallocThenReleaseIvarClass
- (<span class="dt">void</span>)dealloc {
  [super dealloc];
  [_ivar release]; <span class="co">// warn</span>
}
<span class="er">@</span>end</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-osx.cocoa.SuperDealloc)</p>


#### Unused Ivars {#CT_SA_OSX_CCA_UI}
<p>Warn about private ivars that are never used.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="er">@</span>interface MyObj : NSObject {
<span class="er">@</span>private
  id x; <span class="co">// warn</span>
}
<span class="er">@</span>end

<span class="er">@</span>implementation MyObj
<span class="er">@</span>end</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-osx.cocoa.UnusedIvars)</p>


#### Variadic Method Types {#CT_SA_OSX_CCA_VMT}
<p>Check for passing non-Objective-C types to variadic collection initialization methods that expect only Objective-C types.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> test() {
  [NSSet setWithObjects:<span class="er">@</span><span class="st">&quot;Foo&quot;</span>, <span class="st">&quot;Bar&quot;</span>, nil];
    <span class="co">// warn: argument should be an ObjC pointer type, not &#39;char *&#39;</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-osx.cocoa.VariadicMethodTypes)</p>


### Static Analyzer - macOS/Core Foundation

#### CF Error {#CT_SA_OSX_CRF_CE}
<p>Check usage of CFErrorRef* parameters</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> test(CFErrorRef *error) {
  <span class="co">// warn: function accepting CFErrorRef* should have a</span>
  <span class="co">// non-void return</span>
}

<span class="dt">int</span> foo(CFErrorRef *error) {
  *error = <span class="dv">0</span>; <span class="co">// warn: potential null dereference</span>
  <span class="kw">return</span> <span class="dv">0</span>;
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-osx.coreFoundation.CFError)</p>


#### CF Number {#CT_SA_OSX_CRF_CN}
<p>Check for proper uses of CFNumber APIs.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">CFNumberRef test(<span class="dt">unsigned</span> <span class="dt">char</span> x) {
  <span class="kw">return</span> CFNumberCreate(<span class="dv">0</span>, kCFNumberSInt16Type, &amp;x);
   <span class="co">// warn: 8 bit integer is used to initialize a 16 bit integer</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-osx.coreFoundation.CFNumber)</p>


#### CF Retain Release {#CT_SA_OSX_CRF_CRR}
<p>Check for null arguments to CFRetain/CFRelease/CFMakeCollectable.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> test(CFTypeRef p) {
  <span class="kw">if</span> (!p)
    CFRetain(p); <span class="co">// warn</span>
}

<span class="dt">void</span> test(<span class="dt">int</span> x, CFTypeRef p) {
  <span class="kw">if</span> (p)
    <span class="kw">return</span>;

  CFRelease(p); <span class="co">// warn</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-osx.coreFoundation.CFRetainRelease)</p>


### Static Analyzer - macOS/Core Foundation/Containers

#### Out Of Bounds {#CT_SA_OSX_CRF_OOB}
<p>Checks for index out-of-bounds when using ‘CFArray’ API.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> test() {
  CFArrayRef A = CFArrayCreate(<span class="dv">0</span>, <span class="dv">0</span>, <span class="dv">0</span>, &amp;kCFTypeArrayCallBacks);
  CFArrayGetValueAtIndex(A, <span class="dv">0</span>); <span class="co">// warn</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-osx.coreFoundation.containers.OutOfBounds)</p>


#### Pointer Sized Values {#CT_SA_OSX_CRF_PSV}
<p>Warns if ‘CFArray’, ‘CFDictionary’, ‘CFSet’ are created with non-pointer-size values.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="dt">void</span> test() {
  <span class="dt">int</span> x[] = { <span class="dv">1</span> };
  CFArrayRef A = CFArrayCreate(<span class="dv">0</span>, (<span class="dt">const</span> <span class="dt">void</span> <span class="st">&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;&quot;</span>)x, <span class="dv">1</span>,
                               &amp;kCFTypeArrayCallBacks); <span class="co">// warn</span>
}</code></pre></div>
<p>(Clang-Tidy original name: clang-analyzer-osx.coreFoundation.containers.PointerSizedValues)</p>


### Static Analyzer - va_list

#### Copy To Self {#CT_SA_VAL_CTS}
No documentation is available.

#### Uninitialized {#CT_SA_VAL_U}
No documentation is available.

#### Unterminated {#CT_SA_VAL_U2}
No documentation is available.

#### Valist Base {#CT_SA_VAL_VB}
No documentation is available.

### Zircon

#### Temporary Objects {#CT_ZRC_TO}
<p>Warns on construction of specific temporary objects in the Zircon kernel. If the object should be flagged, If the object should be flagged, the fully qualified type name must be explicitly passed to the check.</p>
<p>For example, given the list of classes “Foo” and “NS::Bar”, all of the following will trigger the warning:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">Foo();
Foo F = Foo();
func(Foo());

<span class="kw">namespace</span> NS {

Bar();

}</code></pre></div>
<p>With the same list, the following will not trigger the warning:</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp">Foo F;                 <span class="co">// Non-temporary construction okay</span>
Foo F(param);          <span class="co">// Non-temporary construction okay</span>
Foo *F = <span class="kw">new</span> Foo();    <span class="co">// New construction okay</span>

Bar();                 <span class="co">// Not NS::Bar, so okay</span>
NS::Bar B;             <span class="co">// Non-temporary construction okay</span></code></pre></div>
<p>Note that objects must be explicitly specified in order to be flagged, and so objects that inherit a specified object will not be flagged.</p>
<p>This check matches temporary objects without regard for inheritance and so a prohibited base class type does not similarly prohibit derived class types.</p>
<div class="sourceCode"><pre class="sourceCode cpp"><code class="sourceCode cpp"><span class="kw">class</span> Derived : Foo {} <span class="co">// Derived is not explicitly disallowed</span>
Derived();             <span class="co">// and so temporary construction is okay</span></code></pre></div>
<h5 id="options-59">Options</h5>
<p>Names</p>
<p>A semi-colon-separated list of fully-qualified names of C++ classes that should not be constructed as temporaries. Default is empty.</p>
<p>(Clang-Tidy original name: zircon-temporary-objects)</p>


