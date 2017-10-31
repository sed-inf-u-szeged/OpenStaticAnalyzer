## Reference of FindBugs coding rule violations

OpenStaticAnalyzer incorporates the [FindBugs] tool for coding rule violation checking and imports its results. OpenStaticAnalyzer also associates the issued rule violations with source code elements (i.e. methods, classes, packages, and components), and calculates metrics for the source code elements, which represent the amount of violations of each ruleset, rule, and priority groups, respectively.

OpenStaticAnalyzer uses FindBugs "as is", without any guaranties that the results of FindBugs are correct. All statements of the FindBugs license apply here as well. All texts describing the rulesets and the individual rules are copied from the configuration files of FindBugs with some minor grammatical fixes.

The list of rulesets and rules contained in each ruleset are the following:

- **Bad Practice Rules:** Violations of recommended and essential coding practice. Examples include hash code and equals problems, cloneable idiom, dropped exceptions, Serializable problems, and misuse of finalize. We strive to make this analysis accurate, although some groups may not care about some of the bad practices.

- **Correctness Rules:** Probable bug - an apparent coding mistake resulting in code that was probably not what the developer intended. We strive for a low false positive rate.

- **Dodgy Code Rules:** code that is confusing, anomalous, or written in a way that leads itself to errors. Examples include dead local stores, switch fall through, unconfirmed casts, and redundant null check of value known to be null. More false positives accepted. In previous versions of FindBugs, this category was known as Style.

- **Internationalization Rules:** code flaws having to do with internationalization and locale

- **Multithreaded Correctness Rules:** code flaws having to do with threads, locks, and volatiles

- **Optimization Rules:** These rules deal with different optimizations that generally apply to best practices.

- **Security Code Guideline Rules:** code that is vulnerable to attacks from untrusted code

- **Vulnerability Rules:** These rules deal with different security issues arise with tainting user inputs in web applications.

The following table contains the enabled rules and their priorities:

  Category                         Name                                                                     Abbreviation     Prio.    
  -------------------------------- ------------------------------------------------------------------------ ---------------- ---------
  Bad Practice Rules               Abstract Self                                                            FB_EAS           Major    
                                   Bad Field                                                                FB_SBF           Major    
                                   Bad Field Inner Class                                                    FB_SBFIC         Minor    
                                   Bad Field Store                                                          FB_SBFS          Critical 
                                   Boolean Return Null                                                      FB_NBRN          Major    
                                   Check For Operand Not Compatible With This                               FB_ECFONCWT      Major    
                                   Class Naming Convention                                                  FB_CNC           Major    
                                   Class Not Exception                                                      FB_NCNE          Major    
                                   Clone Could Return Null                                                  FB_REARTN        Critical 
                                   Comparator Should Be Serializable                                        FB_SCSBS         Major    
                                   Compareto Use Object Equals                                              FB_ECUOE         Critical 
                                   Comparing Parameter String With Eq                                       FB_ECPSWE        Major    
                                   Comparing Strings With Eq                                                FB_ECSWE         Major    
                                   Confusing                                                                FB_NC            Major    
                                   Creates Empty Jar File Entry                                             FB_ACEJFE        Major    
                                   Creates Empty Zip File Entry                                             FB_ACEZFE        Major    
                                   Dont Catch Imse                                                          FB_IDCI          Major    
                                   Dont Reuse Entry Objects In Iterators                                    FB_PDREOII       Major    
                                   Empty                                                                    FB_EF            Major    
                                   Entry Sets May Reuse Entry Objects                                       FB_DESMREO       Major    
                                   Equals Method Should Work For All Objects                                FB_BEMSWFAO      Critical 
                                   Equals No Hashcode                                                       FB_HENH          Major    
                                   Equals Should Handle Null Argument                                       FB_UNCIE         Critical 
                                   Equals Use Hashcode                                                      FB_HEUH          Critical 
                                   Exit                                                                     FB_DNCSE         Major    
                                   Explicit Invocation                                                      FB_ACF           Major    
                                   Field Isnt Final In Immutable Class                                      FB_JFIFIIC       Minor    
                                   Field Naming Convention                                                  FB_NFNC          Major    
                                   Finalizer Nulls Fields                                                   FB_FFNF          Major    
                                   Finalizer Only Nulls Fields                                              FB_FFONF         Major    
                                   Format String Uses Newline                                               FB_VFSUN         Major    
                                   Future Keyword Used As Identifier                                        FB_NFKUAI        Major    
                                   Future Keyword Used As Member Identifier                                 FB_NFKUAMI       Major    
                                   Getclass And Class Constant                                              FB_EGACC         Critical 
                                   Hashcode No Equals                                                       FB_HHNE          Critical 
                                   Hashcode Use Object Equals                                               FB_HHUOE         Critical 
                                   Idiom                                                                    FB_ClMMIC        Major    
                                   Idiom No Super Call                                                      FB_PCI           Major    
                                   Implements Clone But Not Cloneable                                       FB_CICBNC        Major    
                                   Inheritance Unsafe Getresource                                           FB_UIUG          Major    
                                   Inherits Equals Use Hashcode                                             FB_HIEUH         Critical 
                                   Inner Class                                                              FB_SIC           Major    
                                   Instance Before Finals Assigned                                          FB_SIBFA         Critical 
                                   Instantiate Static Class                                                 FB_IISC          Major    
                                   Method Naming Convention                                                 FB_MeNC          Major    
                                   Might Drop                                                               FB_DMD           Major    
                                   Might Ignore                                                             FB_DMI           Major    
                                   Missing Super Call                                                       FB_FDNCSF        Major    
                                   Negating Result Of Compareto                                             FB_RNROC         Minor    
                                   No Serialversionid                                                       FB_MSVUID        Major    
                                   No Such Element                                                          FB_INSE          Minor    
                                   No Suitable Constructor                                                  FB_SNSC          Major    
                                   No Suitable Constructor For Externalization                              FB_SNSCFE        Major    
                                   Nonfinal Serialversionid                                                 FB_SNS           Critical 
                                   Nonlong Serialversionid                                                  FB_SeNS          Major    
                                   Nonstatic Serialversionid                                                FB_SeNoS         Major    
                                   Not Checked                                                              FB_SNC           Major    
                                   Nullify Super                                                            FB_FNS           Critical 
                                   Open Database Resource                                                   FB_OODR          Critical 
                                   Open Database Resource Exception Path                                    FB_OODREP        Critical 
                                   Open Stream                                                              FB_OOS           Critical 
                                   Open Stream Exception Path                                               FB_OOSEP         Critical 
                                   Random Used Only Once                                                    FB_DRUOO         Critical 
                                   Read Resolve Must Return Object                                          FB_SRRMRO        Major    
                                   Ref Comparison Bad Practice                                              FB_RRCBP         Major    
                                   Ref Comparison Bad Practice Boolean                                      FB_RRCBPB        Major    
                                   Return Value Ignored Bad Practice                                        FB_RRVIBP        Major    
                                   Rough Constant Value                                                     FB_CRCV          Major    
                                   Run Finalizers On Exit                                                   FB_DRFOE         Major    
                                   Same Simple Name As Interface                                            FB_NSSNAI        Major    
                                   Same Simple Name As Superclass                                           FB_NSSNAS        Major    
                                   Self No Object                                                           FB_ESNO          Major    
                                   Signed Check                                                             FB_BSC           Critical 
                                   Store Of Non Serializable Object Into Session                            FB_JSONSOIS      Critical 
                                   Superclass Uses Subclass During Initialization                           FB_ISUSDI        Major    
                                   Swing Methods Invoked In Swing Thread                                    FB_SSMIIST       Major    
                                   Tostring Could Return Null                                               FB_NTCRN         Critical 
                                   Transient Field Not Restored                                             FB_STFNR         Major    
                                   Unchecked Type In Generic Call                                           FB_GUTIGC        Critical 
                                   Useless                                                                  FB_FU            Minor    
                                   Using Removeall To Clear Collection                                      FB_DURTCC        Critical 
                                   Very Confusing Intentional                                               FB_NVCI          Major    
                                   Wrong Package Intentional                                                FB_NWPI          Major    
  Correctness Rules                01 To Int                                                                FB_R0TI          Major    
                                   Absolute Value Of Hashcode                                               FB_RAVOH         Critical 
                                   Absolute Value Of Random Int                                             FB_RAVORI        Critical 
                                   Add Of Signed Byte                                                       FB_BAOSB         Critical 
                                   Always False                                                             FB_EAF           Blocker  
                                   Always Null                                                              FB_NAN           Critical 
                                   Always Null Exception                                                    FB_NANE          Critical 
                                   Always True                                                              FB_EAT           Blocker  
                                   Always Value Used Where Never Required                                   FB_TAVUWNR       Critical 
                                   And                                                                      FB_BA            Critical 
                                   And Zz                                                                   FB_BAZ           Critical 
                                   Annotation Is Not Visible To Reflection                                  FB_DAINVTR       Major    
                                   Appending To Object Output Stream                                        FB_IATOOS        Critical 
                                   Argument Might Be Null                                                   FB_NAMBN         Major    
                                   Arguments Wrong Order                                                    FB_DAWO          Minor    
                                   Array And Nonarray                                                       FB_EAAN          Critical 
                                   Assert Method Invoked From Run Method                                    FB_IAMIFRM       Critical 
                                   Bad Array Compare                                                        FB_EBAC          Critical 
                                   Bad Comparison With Int Value                                            FB_IBCWIV        Major    
                                   Bad Comparison With Nonnegative Value                                    FB_IBCWNV        Critical 
                                   Bad Comparison With Signed Byte                                          FB_IBCWSB        Critical 
                                   Bad Equal                                                                FB_NBE           Critical 
                                   Bad Month                                                                FB_DBM           Critical 
                                   Bad Prepared Statement Access                                            FB_SBPSA         Critical 
                                   Bad Resultset Access                                                     FB_SBRA          Critical 
                                   Bad Shift Amount                                                         FB_IBSA          Critical 
                                   Bad Suite Method                                                         FB_IBSM          Critical 
                                   Bad Syntax For Regular Expression                                        FB_RBSFRE        Critical 
                                   Badly Overridden Adapter                                                 FB_BBOA          Critical 
                                   Bigdecimal Constructed From Double                                       FB_ADLIBDC       Major    
                                   Calling Next From Hasnext                                                FB_DCNFH         Critical 
                                   Cant Use File Separator As Regular Expression                            FB_RCUFSARE      Critical 
                                   Check Compareto For Specific Return Value                                FB_RCCFSRV       Major    
                                   Class Masks Field                                                        FB_MCMF          Major    
                                   Closing Null                                                             FB_NCN           Blocker  
                                   Collections Should Not Contain Themselves                                FB_DCSNCT        Critical 
                                   Compareto Results Min Value                                              FB_CCRMV         Major    
                                   Comparing Class Names                                                    FB_ECCN          Major    
                                   Comparing Values With Incompatible Type Qualifiers                       FB_TCVWITQ       Major    
                                   Container Added To Itself                                                FB_ICATI         Critical 
                                   Dead Local Increment In Return                                           FB_UPF           Major    
                                   Dead Store Due To Switch Fallthrough                                     FB_SDSDTSF       Critical 
                                   Dead Store Due To Switch Fallthrough To Throw                            FB_SDSDTSFTT     Critical 
                                   Dead Store Of Class Literal                                              FB_DDSOCL        Critical 
                                   Doh                                                                      FB_DmD           Major    
                                   Dont Define Equals For Enum                                              FB_EDDEFE        Major    
                                   Exception Not Thrown                                                     FB_RENT          Critical 
                                   Field Self Assignment                                                    FB_SFSA          Critical 
                                   Field Self Comparison                                                    FB_SFSC          Critical 
                                   Field Self Computation                                                   FB_SaFSC         Critical 
                                   Format String Bad Argument                                               FB_VFSBA         Critical 
                                   Format String Bad Conversion                                             FB_VFSBC         Critical 
                                   Format String Bad Conversion From Array                                  FB_VFSBCFA       Major    
                                   Format String Expected Message Format Supplied                           FB_VFSEMFS       Major    
                                   Format String Extra Arguments Passed                                     FB_VFSEAP        Major    
                                   Format String Illegal                                                    FB_VFSI          Critical 
                                   Format String Missing Argument                                           FB_VFSMA         Critical 
                                   Format String No Previous Argument                                       FB_VFSNPA        Critical 
                                   Futile Attempt To Change Maxpool Size Of Scheduled Thread Pool Executor  FB_DFATCMSOSTPE  Minor    
                                   Guaranteed Deref                                                         FB_NGD           Blocker  
                                   Guaranteed Deref On Exception Path                                       FB_NGDOEP        Critical 
                                   Impossible Cast                                                          FB_BIC           Blocker  
                                   Impossible Downcast                                                      FB_BID           Blocker  
                                   Impossible Downcast Of Toarray                                           FB_CCEWTA        Blocker  
                                   Impossible Instanceof                                                    FB_BcII          Critical 
                                   Incompatible Array Compare                                               FB_EIAC          Blocker  
                                   Infinite Loop                                                            FB_IIL           Critical 
                                   Infinite Recursive Loop                                                  FB_IIRL          Critical 
                                   Int 2 Long As Instant                                                    FB_II2LAI        Major    
                                   Int Cast To Double Passed To Ceil                                        FB_IICTDPTC      Critical 
                                   Int Cast To Float Passed To Round                                        FB_IICTFPTR      Critical 
                                   Interrupted On Currentthread                                             FB_SIOC          Critical 
                                   Interrupted On Unknownthread                                             FB_SIOU          Critical 
                                   Invoking Hashcode On Array                                               FB_DIHOA         Critical 
                                   Invoking Tostring On Anonymous Array                                     FB_DITOAA        Critical 
                                   Invoking Tostring On Array                                               FB_DITOA         Critical 
                                   Ior                                                                      FB_BiI           Critical 
                                   Ior Of Signed Byte                                                       FB_BIOSB         Critical 
                                   Lcase Hashcode                                                           FB_SHMN          Critical 
                                   Lcase Tostring                                                           FB_NLT           Major    
                                   Local Self Assignment Instead Of Field                                   FB_SLSAIOF       Major    
                                   Local Self Comparison                                                    FB_SLSC          Critical 
                                   Local Self Computation                                                   FB_SaLSC         Critical 
                                   Long Bits To Double Invoked On Int                                       FB_DLBTDIOI      Critical 
                                   Math Using Float Precision                                               FB_FMUFP         Critical 
                                   Maybe Source Value Reaches Always Sink                                   FB_TMSVRAS       Critical 
                                   Maybe Source Value Reaches Never Sink                                    FB_TMSVRNS       Critical 
                                   Method Constructor Confusion                                             FB_MWSNAEC       Major    
                                   Method Masks Field                                                       FB_MMMF          Major    
                                   Method Must Be Private                                                   FB_SMMBP         Major    
                                   Missing Expected Warning                                                 FB_FMEW          Info     
                                   Multiplying Result Of Irem                                               FB_IMROI         Critical 
                                   Never Value Used Where Always Required                                   FB_TNVUWAR       Critical 
                                   No Tests                                                                 FB_INT           Critical 
                                   Nonnull Field Not Initialized In Constructor                             FB_NNFNIIC       Critical 
                                   Nonnull Param Violation                                                  FB_NNPV          Critical 
                                   Nonnull Return Violation                                                 FB_NNRV          Critical 
                                   Null Arg                                                                 FB_ENA           Critical 
                                   Null Field                                                               FB_UNF           Critical 
                                   Null Instanceof                                                          FB_NNI           Blocker  
                                   Null On Some Path                                                        FB_NNOSP         Critical 
                                   Null On Some Path Exception                                              FB_NNOSPE        Critical 
                                   Null Param Deref                                                         FB_NNPD          Critical 
                                   Null Param Deref All Targets Dangerous                                   FB_NNPDATD       Critical 
                                   Null Param Deref Nonvirtual                                              FB_NNPDN         Critical 
                                   Optional Return Null                                                     FB_NORN          Major    
                                   Other No Object                                                          FB_EONO          Major    
                                   Other Use Object                                                         FB_EOUO          Major    
                                   Overriding Equals Not Symmetric                                          FB_EOENS         Major    
                                   Overwritten Increment                                                    FB_DOI           Critical 
                                   Parameter Is Dead But Overwritten                                        FB_IPIDBO        Critical 
                                   Possible Unintended Pattern                                              FB_RPUP          Critical 
                                   Primitive Array Passed To Object Vararg                                  FB_VPAPTOV       Critical 
                                   Questionable Boolean Assignment                                          FB_QQBA          Critical 
                                   Read Resolve Is Static                                                   FB_SRRIS         Major    
                                   Redundant Nullcheck Would Have Been A Npe                                FB_RRNWHBAN      Critical 
                                   Ref Comparison                                                           FB_RRC           Critical 
                                   Repeated Conditional Test                                                FB_RRCT          Major    
                                   Return Value Ignored                                                     FB_RRVI          Minor    
                                   Scheduled Thread Pool Executor With Zero Core Threads                    FB_DSTPEWZCT     Minor    
                                   Self Use Object                                                          FB_ESUO          Major    
                                   Setup No Super                                                           FB_ISNS          Critical 
                                   Signature Declares Hashing Of Unhashable Class                           FB_HSDHOUC       Critical 
                                   Signed Check High Bit                                                    FB_BSCHB         Critical 
                                   Store Into Nonnull Field                                                 FB_NSINF         Critical 
                                   Suite Not Static                                                         FB_JUSS          Critical 
                                   Superfluous Instanceof                                                   FB_SSI           Critical 
                                   Teardown No Super                                                        FB_ITNS          Critical 
                                   Test If Equal To Not A Number                                            FB_BC            Critical 
                                   Threadlocal Deadly Embrace                                               FB_STDE          Major    
                                   Unboxed And Coerced For Ternary Operator                                 FB_BUACFTO       Major    
                                   Uncallable Method Of Anonymous Class                                     FB_UUMOAC        Critical 
                                   Unexpected Warning                                                       FB_FUW           Info     
                                   Uninit Read                                                              FB_UUR           Major    
                                   Uninit Read Called From Super Constructor                                FB_UURCFSC       Major    
                                   Unknown Value Used Where Always Strictly Required                        FB_TUVUWASR      Major    
                                   Unrelated Class And Interface                                            FB_EUCAI         Critical 
                                   Unrelated Interfaces                                                     FB_EUI           Critical 
                                   Unrelated Types                                                          FB_GUT           Critical 
                                   Unrelated Types Using Pointer Equality                                   FB_EUTUPE        Critical 
                                   Unwritten Field                                                          FB_UwUF          Minor    
                                   Use Of Unhashable Class                                                  FB_HUOUC         Critical 
                                   Vacuous Call To Easymock Method                                          FB_DVCTEM        Critical 
                                   Vacuous Self Collection Call                                             FB_DVSCC         Critical 
                                   Very Confusing                                                           FB_NVC           Major    
                                   Wrong Package                                                            FB_NWP           Major    
  Dodgy Code Rules                 Ambiguous Invocation Of Inherited Or Outer Method                        FB_IAIOIOOM      Major    
                                   Average Computation Could Overflow                                       FB_IACCO         Critical 
                                   Bad Cast To Abstract Collection                                          FB_BBCTAC        Major    
                                   Bad Cast To Concrete Collection                                          FB_BBCTCC        Critical 
                                   Bad Check For Odd                                                        FB_IBCFO         Critical 
                                   Bad Rem By 1                                                             FB_IBRB1         Critical 
                                   Catch Exception                                                          FB_RCE           Major    
                                   Check For Positive Indexof                                               FB_RCFPI         Minor    
                                   Confused Inheritance                                                     FB_APFIFC        Minor    
                                   Dangerous Non Short Circuit                                              FB_NDNSC         Critical 
                                   Dead Local Store                                                         FB_DDLS          Critical 
                                   Dead Local Store In Return                                               FB_DDLSIR        Critical 
                                   Dead Local Store Of Null                                                 FB_DDLSON        Critical 
                                   Dead Local Store Shadows Field                                           FB_DDLSSF        Major    
                                   Dereference Of Readline Value                                            FB_NDORV         Critical 
                                   Doesnt Override Equals                                                   FB_EDOE          Critical 
                                   Dont Just Null Check Readline                                            FB_RDJNCR        Major    
                                   Duplicate Branches                                                       FB_DDB           Critical 
                                   Duplicate Switch Clauses                                                 FB_DDSC          Critical 
                                   Explicit Unknown Source Value Reaches Always Sink                        FB_TEUSVRAS      Critical 
                                   Explicit Unknown Source Value Reaches Never Sink                         FB_TEUSVRNS      Critical 
                                   Field Double Assignment                                                  FB_SFDA          Critical 
                                   Field Not Initialized In Constructor                                     FB_UFNIIC        Minor    
                                   Floating Point Equality                                                  FB_FFPE          Critical 
                                   Format String Bad Conversion To Boolean                                  FB_VFSBCTB       Major    
                                   Hardcoded Absolute Filename                                              FB_DHAF          Critical 
                                   Idiv Cast To Double                                                      FB_IICTD         Critical 
                                   Immediate Dereference Of Readline                                        FB_NIDOR         Critical 
                                   Init Circularity                                                         FB_IIC           Critical 
                                   Integer Multiply Cast To Long                                            FB_IIMCTL        Critical 
                                   Load Of Known Null Value                                                 FB_NLOKNV        Critical 
                                   Local Double Assignment                                                  FB_SLDA          Critical 
                                   Local Self Assignment                                                    FB_SLSA          Critical 
                                   Method Parameter Tightens Annotation                                     FB_NMPTA         Major    
                                   Method Return Relaxing Annotation                                        FB_NMRRA         Major    
                                   Non Short Circuit                                                        FB_NNSC          Major    
                                   Nonserializable Object Written                                           FB_DNOW          Critical 
                                   Null On Some Path From Return Value                                      FB_NNOSPFRV      Critical 
                                   Null On Some Path Might Be Infeasible                                    FB_NNOSPMBI      Critical 
                                   Parameter Must Be Nonnull But Marked As Nullable                         FB_NPMBNBMAN     Critical 
                                   Prefer Zero Length Arrays                                                FB_PPZLA         Major    
                                   Private Read Resolve Not Inherited                                       FB_SPRRNI        Major    
                                   Public Semaphores                                                        FB_PPS           Critical 
                                   Questionable For Loop                                                    FB_QQFL          Critical 
                                   Questionable Unsigned Right Shift                                        FB_IQURS         Critical 
                                   Redundant Comparison Of Null And Nonnull Value                           FB_RRCONANV      Critical 
                                   Redundant Comparison Two Null Values                                     FB_RRCTNV        Critical 
                                   Redundant Interfaces                                                     FB_RRI           Major    
                                   Redundant Nullcheck Of Nonnull Value                                     FB_RRNONV        Critical 
                                   Redundant Nullcheck Of Null Value                                        FB_RcRNONV       Critical 
                                   Rem Of Hashcode                                                          FB_RROH          Critical 
                                   Rem Of Random Int                                                        FB_RRORI         Critical 
                                   Return Value Ignored Inferred                                            FB_RRVII         Minor    
                                   Suspect Servlet Instance Field                                           FB_MSSIF         Critical 
                                   Suspect Struts Instance Field                                            FB_MtSSIF        Critical 
                                   Switch Fallthrough                                                       FB_MBIS          Critical 
                                   Switch No Default                                                        FB_DLNLISS       Major    
                                   Thread Passed Where Runnable Expected                                    FB_DNUT          Major    
                                   Transient Field Of Nonserializable Class                                 FB_STFONC        Major    
                                   Unconfirmed Cast                                                         FB_BUC           Critical 
                                   Unconfirmed Cast Of Return Value                                         FB_BUCORV        Critical 
                                   Unread Public Or Protected Field                                         FB_UUPOPF        Info     
                                   Unsupported Method                                                       FB_DUM           Major    
                                   Unused Public Or Protected Field                                         FB_UuUPOPF       Info     
                                   Unusual                                                                  FB_EU            Minor    
                                   Unwritten Public Or Protected Field                                      FB_UwUPOPF       Minor    
                                   Useless Control Flow                                                     FB_UUCF          Critical 
                                   Useless Control Flow Next Line                                           FB_UUCFNL        Critical 
                                   Useless Substring                                                        FB_DUS           Critical 
                                   Vacuous Bit Operation                                                    FB_IVBO          Critical 
                                   Vacuous Comparison                                                       FB_IVC           Critical 
                                   Vacuous Instanceof                                                       FB_BVI           Critical 
                                   Write To Static From Instance Method                                     FB_SWTSFIM       Critical 
                                   Xml Factory Bypass                                                       FB_XXFB          Critical 
  Internationalization Rules       Convert Case                                                             FB_ULWCC         Info     
                                   Default Encoding                                                         FB_DDE           Major    
  Multithreaded Correctness Rules  Await Not In Loop                                                        FB_WANIL         Critical 
                                   Doublecheck                                                              FB_DCL           Major    
                                   Empty Sync                                                               FB_ESB           Major    
                                   Field Not Guarded                                                        FB_IFNG          Critical 
                                   Inconsistent Sync                                                        FB_IIS           Critical 
                                   Invoke On Static Calendar Instance                                       FB_SIOSCI        Critical 
                                   Invoke On Static Date Format Instance                                    FB_SIOSDFI       Critical 
                                   Invoke Run                                                               FB_DCTR          Major    
                                   Jsr166 Calling Wait Rather Than Await                                    FB_JJCWRTA       Major    
                                   Jsr166 Lock Monitorenter                                                 FB_JJLM          Critical 
                                   Jsr166 Utilconcurrent Monitorenter                                       FB_JJUM          Major    
                                   Lazy Init Static                                                         FB_LLIS          Critical 
                                   Lazy Init Update Static                                                  FB_LLIUS         Critical 
                                   Mismatched Notify                                                        FB_MMN           Critical 
                                   Mismatched Wait                                                          FB_MMW           Critical 
                                   Monitor Wait On Condition                                                FB_DMWOC         Major    
                                   Mutable Servlet Field                                                    FB_MMSF          Major    
                                   Naked Notify                                                             FB_NNN           Critical 
                                   Not In Loop                                                              FB_WNIL          Critical 
                                   Notify Not Notifyall                                                     FB_NNNN          Critical 
                                   Operation Sequence On Concurrent Abstraction                             FB_AOSOCA        Major    
                                   Readobject Sync                                                          FB_RRS           Critical 
                                   Return Value Of Putifabsent Ignored                                      FB_RRVOPI        Major    
                                   Sleep With Lock Held                                                     FB_SSWLH         Critical 
                                   Spin On Field                                                            FB_SSOF          Major    
                                   Start In Ctor                                                            FB_SSIC          Critical 
                                   Static Calendar Instance                                                 FB_SSCI          Critical 
                                   Static Simple Date Format Instance                                       FB_SSSDFI        Critical 
                                   Sync And Null Check Field                                                FB_NSANCF        Major    
                                   Sync On Field To Guard Changing That Field                               FB_MSOFTGCTF     Major    
                                   Sync On Updated Field                                                    FB_MSOUF         Major    
                                   Sync Set Unsync Get                                                      FB_USSUG         Major    
                                   Synchronization On Boolean                                               FB_DSOB          Critical 
                                   Synchronization On Boxed Primitive                                       FB_DSOBP         Critical 
                                   Synchronization On Shared Constant                                       FB_DSOSC         Critical 
                                   Synchronization On Unshared Boxed Primitive                              FB_DSOUBP        Critical 
                                   Two Lock Wait                                                            FB_TTLW          Major    
                                   Uncond Wait                                                              FB_UUW           Major    
                                   Unreleased Lock                                                          FB_UUL           Critical 
                                   Unreleased Lock Exception Path                                           FB_UULEP         Critical 
                                   Useless Thread                                                           FB_DUT           Major    
                                   Using Getclass Rather Than Class Literal                                 FB_WUGRTCL       Critical 
                                   Volatile Increment                                                       FB_VVI           Critical 
                                   Volatile Reference To Array                                              FB_VVRTA         Major    
                                   Writeobject Sync                                                         FB_WWS           Critical 
  Optimization Rules               Blocking Methods On Url                                                  FB_DBMOU         Blocker  
                                   Boolean Ctor                                                             FB_DBC           Major    
                                   Boxed Primitive For Parsing                                              FB_DBPFP         Major    
                                   Boxed Primitive Tostring                                                 FB_DBPT          Major    
                                   Boxing Immediately Unboxed                                               FB_BBIU          Major    
                                   Boxing Immediately Unboxed To Perform Coercion                           FB_BBIUTPC       Major    
                                   Collection Of Urls                                                       FB_DCOU          Blocker  
                                   Fp Number Ctor                                                           FB_DFNC          Major    
                                   Gc                                                                       FB_DNCGCE        Major    
                                   Huge Shared String Constant                                              FB_HHSSC         Critical 
                                   Inefficient Index Of                                                     FB_IIIO          Major    
                                   Inefficient Last Index Of                                                FB_IILIO         Major    
                                   Inefficient To Array                                                     FB_OTAC          Critical 
                                   Inner Should Be Static                                                   FB_SISBS         Major    
                                   Inner Should Be Static Anon                                              FB_SISBSA        Major    
                                   Inner Should Be Static Needs This                                        FB_SISBSNT       Major    
                                   New For Getclass                                                         FB_ITGC          Major    
                                   Nextint Via Nextdouble                                                   FB_DNVN          Major    
                                   Number Ctor                                                              FB_UWOC          Critical 
                                   Should Be Static                                                         FB_SSBS          Major    
                                   String Ctor                                                              FB_DSC           Major    
                                   String Tostring                                                          FB_STS           Info     
                                   String Void Ctor                                                         FB_DSVC          Major    
                                   Unboxing Immediately Reboxed                                             FB_BUIR          Major    
                                   Uncalled Private Method                                                  FB_UUPM          Critical 
                                   Unnecessary Math                                                         FB_UUM           Critical 
                                   Unread Field                                                             FB_UUF           Major    
                                   Unused Field                                                             FB_UuUF          Major    
                                   Use Stringbuffer Concatenation                                           FB_USBFSA        Critical 
                                   Wrong Map Iterator                                                       FB_WWMI          Critical 
  Security Code Guideline Rules    Cannot Be Final                                                          FB_MCBF          Major    
                                   Create Classloader Inside Do Privileged                                  FB_DCCIDP        Major    
                                   Do Inside Do Privileged                                                  FB_DDIDP         Major    
                                   Expose Rep                                                               FB_MRIA          Critical 
                                   Expose Rep2                                                              FB_EiER          Major    
                                   Expose Static Rep2                                                       FB_EESR          Major    
                                   Final Pkgprotect                                                         FB_MFP           Major    
                                   Mutable Array                                                            FB_MMA           Major    
                                   Mutable Hashtable                                                        FB_MMH           Major    
                                   Ooi Pkgprotect                                                           FB_MOP           Major    
                                   Pkgprotect                                                               FB_MP            Major    
                                   Public Should Be Protected                                               FB_FSBP          Major    
                                   Should Be Final                                                          FB_MSBF          Major    
                                   Should Be Refactored To Be Final                                         FB_MSBRTBF       Major    
  Vulnerability Rules              Absolute Path Traversal                                                  FB_PAPT          Major    
                                   Constant Db Password                                                     FB_DCDP          Blocker  
                                   Empty Db Password                                                        FB_DEDP          Critical 
                                   Nonconstant String Passed To Execute                                     FB_SNSPTE        Critical 
                                   Prepared Statement Generated From Nonconstant String                     FB_SPSGFNS       Critical 
                                   Relative Path Traversal                                                  FB_PRPT          Major    
                                   Request Parameter To Cookie                                              FB_HRPTC         Major    
                                   Request Parameter To Http Header                                         FB_HRPTHH        Major    
                                   Request Parameter To Jsp Writer                                          FB_XRPTJW        Critical 
                                   Request Parameter To Send Error                                          FB_XRPTSE        Critical 
                                   Request Parameter To Servlet Writer                                      FB_XRPTSW        Critical 

### Bad Practice Rules

#### Abstract Self {#FB_EAS}

This class defines a covariant version of equals().  To correctly override the equals() method in java.lang.Object, the parameter of equals() must have type java.lang.Object.

#### Bad Field {#FB_SBF}

This Serializable class defines a non-primitive instance field which is neither transient, Serializable, or java.lang.Object, and does not appear to implement the Externalizable interface or the readObject() and writeObject() methods.  Objects of this class will not be deserialized correctly if a non-Serializable object is stored in this field.

#### Bad Field Inner Class {#FB_SBFIC}

This Serializable class is an inner class of a non-serializable class. Thus, attempts to serialize it will also attempt to associate instance of the outer class with which it is associated, leading to a runtime error.

If possible, making the inner class a static inner class should solve the problem. Making the outer class serializable might also work, but that would mean serializing an instance of the inner class would always also serialize the instance of the outer class, which it often not what you really want.

#### Bad Field Store {#FB_SBFS}

A non-serializable value is stored into a non-transient field of a serializable class.

#### Boolean Return Null {#FB_NBRN}

A method that returns either Boolean.TRUE, Boolean.FALSE or null is an accident waiting to happen. This method can be invoked as though it returned a value of type boolean, and the compiler will insert automatic unboxing of the Boolean value. If a null value is returned, this will result in a NullPointerException.

#### Check For Operand Not Compatible With This {#FB_ECFONCWT}

This equals method is checking to see if the argument is some incompatible type (i.e., a class that is neither a supertype nor subtype of the class that defines the equals method). For example, the Foo class might have an equals method that looks like:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public boolean equals(Object o) {
  if (o instanceof Foo)
    return name.equals(((Foo)o).name);
  else if (o instanceof String)
    return name.equals(o);
  else return false;
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This is considered bad practice, as it makes it very hard to implement an equals method that is symmetric and transitive. Without those properties, very unexpected behavoirs are possible.

#### Class Naming Convention {#FB_CNC}

Class names should be nouns, in mixed case with the first letter of each internal word capitalized. Try to keep your class names simple and descriptive. Use whole words-avoid acronyms and abbreviations (unless the abbreviation is much more widely used than the long form, such as URL or HTML).

#### Class Not Exception {#FB_NCNE}

This class is not derived from another exception, but ends with 'Exception'. This will be confusing to users of this class.

#### Clone Could Return Null {#FB_REARTN}

This clone method seems to return null in some circumstances, but clone is never allowed to return a null value. If you are convinced this path is unreachable, throw an AssertionError instead.

#### Comparator Should Be Serializable {#FB_SCSBS}

This class implements the Comparator interface. You should consider whether or not it should also implement the Serializable interface. If a comparator is used to construct an ordered collection such as a TreeMap, then the TreeMap will be serializable only if the comparator is also serializable. As most comparators have little or no state, making them serializable is generally easy and good defensive programming.

#### Compareto Use Object Equals {#FB_ECUOE}

This class defines a compareTo(...) method but inherits its equals() method from java.lang.Object. Generally, the value of compareTo should return zero if and only if equals returns true. If this is violated, weird and unpredictable failures will occur in classes such as PriorityQueue. In Java 5 the PriorityQueue.remove method uses the compareTo method, while in Java 6 it uses the equals method.

From the JavaDoc for the compareTo method in the Comparable interface:

It is strongly recommended, but not strictly required that (x.compareTo(y)==0) == (x.equals(y)). Generally speaking, any class that implements the Comparable interface and violates this condition should clearly indicate this fact. The recommended language is "Note: this class has a natural ordering that is inconsistent with equals."

#### Comparing Parameter String With Eq {#FB_ECPSWE}

This code compares a java.lang.String parameter for reference equality using the == or != operators. Requiring callers to pass only String constants or interned strings to a method is unnecessarily fragile, and rarely leads to measurable performance gains. Consider using the equals(Object) method instead.

#### Comparing Strings With Eq {#FB_ECSWE}

This code compares java.lang.String objects for reference equality using the == or != operators. Unless both strings are either constants in a source file, or have been interned using the String.intern() method, the same string value may be represented by two different String objects. Consider using the equals(Object) method instead.

#### Confusing {#FB_NC}

The referenced methods have names that differ only by capitalization.

#### Creates Empty Jar File Entry {#FB_ACEJFE}

The code calls putNextEntry(), immediately followed by a call to closeEntry(). This results in an empty JarFile entry. The contents of the entry should be written to the JarFile between the calls to putNextEntry() and closeEntry().

#### Creates Empty Zip File Entry {#FB_ACEZFE}

The code calls putNextEntry(), immediately followed by a call to closeEntry(). This results in an empty ZipFile entry. The contents of the entry should be written to the ZipFile between the calls to putNextEntry() and closeEntry().

#### Dont Catch Imse {#FB_IDCI}

IllegalMonitorStateException is generally only thrown in case of a design flaw in your code (calling wait or notify on an object you do not hold a lock on).

#### Dont Reuse Entry Objects In Iterators {#FB_PDREOII}

The entrySet() method is allowed to return a view of the underlying Map in which an Iterator and Map.Entry. This clever idea was used in several Map implementations, but introduces the possibility of nasty coding mistakes. If a map m returns such an iterator for an entrySet, then c.addAll(m.entrySet()) will go badly wrong. All of the Map implementations in OpenJDK 1.7 have been rewritten to avoid this, you should to.

#### Empty {#FB_EF}

Empty finalize() methods are useless, so they should be deleted.

#### Entry Sets May Reuse Entry Objects {#FB_DESMREO}

The entrySet() method is allowed to return a view of the underlying Map in which a single Entry object is reused and returned during the iteration. As of Java 1.6, both IdentityHashMap and EnumMap did so. When iterating through such a Map, the Entry value is only valid until you advance to the next iteration. If, for example, you try to pass such an entrySet to an addAll method, things will go badly wrong.

#### Equals Method Should Work For All Objects {#FB_BEMSWFAO}

The equals(Object o) method shouldn't make any assumptions about the type of o. It should simply return false if o is not the same type as this.

#### Equals No Hashcode {#FB_HENH}

This class overrides equals(Object), but does not override hashCode(). Therefore, the class may violate the invariant that equal objects must have equal hashcodes.

#### Equals Should Handle Null Argument {#FB_UNCIE}

This implementation of equals(Object) violates the contract defined by java.lang.Object.equals() because it does not check for null being passed as the argument. All equals() methods should return false if passed a null value.

#### Equals Use Hashcode {#FB_HEUH}

This class overrides equals(Object), but does not override hashCode(), and inherits the implementation of hashCode() from java.lang.Object (which returns the identity hash code, an arbitrary value assigned to the object by the VM).  Therefore, the class is very likely to violate the invariant that equal objects must have equal hashcodes.

If you don't think instances of this class will ever be inserted into a HashMap/HashTable, the recommended hashCode implementation to use is:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public int hashCode() {
  assert false : "hashCode not designed";
  return 42; // any arbitrary constant will do
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Exit {#FB_DNCSE}

Invoking System.exit shuts down the entire Java virtual machine. This should only been done when it is appropriate. Such calls make it hard or impossible for your code to be invoked by other code. Consider throwing a RuntimeException instead.

#### Explicit Invocation {#FB_ACF}

This method contains an explicit invocation of the finalize() method on  an object.  Because finalizer methods are supposed to be executed once, and only by the VM, this is a bad idea.

If a connected set of objects beings finalizable, then the VM will invoke the finalize method on all the finalizable object, possibly at  the same time in different threads. Thus, it is a particularly bad idea, in the finalize method for a class X, invoke finalize on objects referenced by X, because they may already be getting finalized in a separate thread. 


#### Field Isnt Final In Immutable Class {#FB_JFIFIIC}

The class is annotated with net.jcip.annotations.Immutable or javax.annotation.concurrent.Immutable, and the rules for those annotations require that all fields are final. .

#### Field Naming Convention {#FB_NFNC}

Names of fields that are not final should be in mixed case with a lowercase first letter and the first letters of subsequent words capitalized.

#### Finalizer Nulls Fields {#FB_FFNF}

This finalizer nulls out fields. This is usually an error, as it does not aid garbage collection, and the object is going to be garbage collected anyway.

#### Finalizer Only Nulls Fields {#FB_FFONF}

This finalizer does nothing except null out fields. This is completely pointless, and requires that the object be garbage collected, finalized, and then garbage collected again. You should just remove the finalize method.

#### Format String Uses Newline {#FB_VFSUN}

This format string include a newline character (\\n). In format strings, it is generally preferable better to use %n, which will produce the platform-specific line separator.

#### Future Keyword Used As Identifier {#FB_NFKUAI}

The identifier is a word that is reserved as a keyword in later versions of Java, and your code will need to be changed in order to compile it in later versions of Java.

#### Future Keyword Used As Member Identifier {#FB_NFKUAMI}

This identifier is used as a keyword in later versions of Java. This code, and any code that references this API, will need to be changed in order to compile it in later versions of Java.

#### Getclass And Class Constant {#FB_EGACC}

This class has an equals method that will be broken if it is inherited by subclasses. It compares a class literal with the class of the argument (e.g., in class Foo it might check if Foo.class == o.getClass()). It is better to check if this.getClass() == o.getClass().

#### Hashcode No Equals {#FB_HHNE}

This class defines a hashCode() method but not an equals() method. Therefore, the class may violate the invariant that equal objects must have equal hashcodes.

#### Hashcode Use Object Equals {#FB_HHUOE}

This class defines a hashCode() method but inherits its equals() method from java.lang.Object (which defines equality by comparing object references).  Although this will probably satisfy the contract that equal objects must have equal hashcodes, it is probably not what was intended by overriding the hashCode() method.  (Overriding hashCode() implies that the object's identity is based on criteria more complicated than simple reference equality.)

If you don't think instances of this class will ever be inserted into a HashMap/HashTable, the recommended hashCode implementation to use is:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public int hashCode() {
  assert false : "hashCode not designed";
  return 42; // any arbitrary constant will do
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Idiom {#FB_ClMMIC}

Class implements Cloneable but does not define or use the clone method.

#### Idiom No Super Call {#FB_PCI}

This non-final class defines a clone() method that does not call super.clone(). If this class ("*A*") is extended by a subclass ("*B*"), and the subclass *B* calls super.clone(), then it is likely that *B*'s clone() method will return an object of type *A*, which violates the standard contract for clone().

If all clone() methods call super.clone(), then they are guaranteed to use Object.clone(), which always returns an object of the correct type.

#### Implements Clone But Not Cloneable {#FB_CICBNC}

This class defines a clone() method but the class doesn't implement Cloneable. There are some situations in which this is OK (e.g., you want to control how subclasses can clone themselves), but just make sure that this is what you intended.

#### Inheritance Unsafe Getresource {#FB_UIUG}

Calling this.getClass().getResource(...) could give results other than expected if this class is extended by a class in another package.

#### Inherits Equals Use Hashcode {#FB_HIEUH}

This class inherits equals(Object) from an abstract superclass, and hashCode() from java.lang.Object (which returns the identity hash code, an arbitrary value assigned to the object by the VM).  Therefore, the class is very likely to violate the invariant that equal objects must have equal hashcodes.

If you don't want to define a hashCode method, and/or don't believe the object will ever be put into a HashMap/Hashtable, define the hashCode() method to throw UnsupportedOperationException.

#### Inner Class {#FB_SIC}

This Serializable class is an inner class. Any attempt to serialize it will also serialize the associated outer instance. The outer instance is serializable, so this won't fail, but it might serialize a lot more data than intended. If possible, making the inner class a static inner class (also known as a nested class) should solve the problem.

#### Instance Before Finals Assigned {#FB_SIBFA}

The class's static initializer creates an instance of the class before all of the static final fields are assigned.

#### Instantiate Static Class {#FB_IISC}

This class allocates an object that is based on a class that only supplies static methods. This object does not need to be created, just access the static methods directly using the class name as a qualifier.

#### Method Naming Convention {#FB_MeNC}

Methods should be verbs, in mixed case with the first letter lowercase, with the first letter of each internal word capitalized.

#### Might Drop {#FB_DMD}

This method might drop an exception.  In general, exceptions should be handled or reported in some way, or they should be thrown out of the method.

#### Might Ignore {#FB_DMI}

This method might ignore an exception.  In general, exceptions should be handled or reported in some way, or they should be thrown out of the method.

#### Missing Super Call {#FB_FDNCSF}

This finalize() method does not make a call to its superclass's finalize() method.  So, any finalizer actions defined for the superclass will not be performed.  Add a call to super.finalize().

#### Negating Result Of Compareto {#FB_RNROC}

This code negatives the return value of a compareTo or compare method. This is a questionable or bad programming practice, since if the return value is Integer.MIN\_VALUE, negating the return value won't negate the sign of the result. You can achieve the same intended result by reversing the order of the operands rather than by negating the results.

#### No Serialversionid {#FB_MSVUID}

This class implements the Serializable interface, but does not define a serialVersionUID field.  A change as simple as adding a reference to a .class object will add synthetic fields to the class, which will unfortunately change the implicit serialVersionUID (e.g., adding a reference to String.class will generate a static field class\$java\$lang\$String). Also, different source code to bytecode compilers may use different naming conventions for synthetic variables generated for references to class objects or inner classes. To ensure interoperability of Serializable across versions, consider adding an explicit serialVersionUID.

#### No Such Element {#FB_INSE}

This class implements the java.util.Iterator interface.  However, its next() method is not capable of throwing java.util.NoSuchElementException.  The next() method should be changed so it throws NoSuchElementException if is called when there are no more elements to return.

#### No Suitable Constructor {#FB_SNSC}

This class implements the Serializable interface and its superclass does not. When such an object is deserialized, the fields of the superclass need to be initialized by invoking the void constructor of the superclass. Since the superclass does not have one, serialization and deserialization will fail at runtime.

#### No Suitable Constructor For Externalization {#FB_SNSCFE}

This class implements the Externalizable interface, but does not define a void constructor. When Externalizable objects are deserialized, they first need to be constructed by invoking the void constructor. Since this class does not have one, serialization and deserialization will fail at runtime.

#### Nonfinal Serialversionid {#FB_SNS}

This class defines a serialVersionUID field that is not final. The field should be made final if it is intended to specify the version UID for purposes of serialization.

#### Nonlong Serialversionid {#FB_SeNS}

This class defines a serialVersionUID field that is not long.  The field should be made long if it is intended to specify the version UID for purposes of serialization.

#### Nonstatic Serialversionid {#FB_SeNoS}

This class defines a serialVersionUID field that is not static.  The field should be made static if it is intended to specify the version UID for purposes of serialization.

#### Not Checked {#FB_SNC}

This method ignores the return value of java.io.InputStream.skip() which can skip multiple bytes.  If the return value is not checked, the caller will not be able to correctly handle the case where fewer bytes were skipped than the caller requested.  This is a particularly insidious kind of bug, because in many programs, skips from input streams usually do skip the full amount of data requested, causing the program to fail only sporadically. With Buffered streams, however, skip() will only skip data in the buffer, and will routinely fail to skip the requested number of bytes.

#### Nullify Super {#FB_FNS}

This empty finalize() method explicitly negates the effect of any finalizer defined by its superclass.  Any finalizer actions defined for the superclass will not be performed.  Unless this is intended, delete this method.

#### Open Database Resource {#FB_OODR}

The method creates a database resource (such as a database connection or row set), does not assign it to any fields, pass it to other methods, or return it, and does not appear to close the object on all paths out of the method.  Failure to close database resources on all paths out of a method may result in poor performance, and could cause the application to have problems communicating with the database.

#### Open Database Resource Exception Path {#FB_OODREP}

The method creates a database resource (such as a database connection or row set), does not assign it to any fields, pass it to other methods, or return it, and does not appear to close the object on all exception paths out of the method.  Failure to close database resources on all paths out of a method may result in poor performance, and could cause the application to have problems communicating with the database.

#### Open Stream {#FB_OOS}

The method creates an IO stream object, does not assign it to any fields, pass it to other methods that might close it, or return it, and does not appear to close the stream on all paths out of the method. This may result in a file descriptor leak.  It is generally a good idea to use a finally block to ensure that streams are closed.

#### Open Stream Exception Path {#FB_OOSEP}

The method creates an IO stream object, does not assign it to any fields, pass it to other methods, or return it, and does not appear to close it on all possible exception paths out of the method.  This may result in a file descriptor leak.  It is generally a good idea to use a finally block to ensure that streams are closed.

#### Random Used Only Once {#FB_DRUOO}

This code creates a java.util.Random object, uses it to generate one random number, and then discards the Random object. This produces mediocre quality random numbers and is inefficient. If possible, rewrite the code so that the Random object is created once and saved, and each time a new random number is required invoke a method on the existing Random object to obtain it.

If it is important that the generated Random numbers not be guessable, you ***must*** not create a new Random for each random number; the values are too easily guessable. You should strongly consider using a java.security.SecureRandom instead (and avoid allocating a new SecureRandom for each random number needed).

#### Read Resolve Must Return Object {#FB_SRRMRO}

In order for the readResolve method to be recognized by the serialization mechanism, it must be declared to have a return type of Object.

#### Ref Comparison Bad Practice {#FB_RRCBP}

This method compares a reference value to a constant using the == or != operator, where the correct way to compare instances of this type is generally with the equals() method. It is possible to create distinct instances that are equal but do not compare as == since they are different objects. Examples of classes which should generally not be compared by reference are java.lang.Integer, java.lang.Float, etc.

#### Ref Comparison Bad Practice Boolean {#FB_RRCBPB}

This method compares two Boolean values using the == or != operator. Normally, there are only two Boolean values (Boolean.TRUE and Boolean.FALSE), but it is possible to create other Boolean objects using the new Boolean(b) constructor. It is best to avoid such objects, but if they do exist, then checking Boolean objects for equality using == or != will give results than are different than you would get using .equals(...)

#### Return Value Ignored Bad Practice {#FB_RRVIBP}

This method returns a value that is not checked. The return value should be checked since it can indicate an unusual or unexpected function execution. For example, the File.delete() method returns false if the file could not be successfully deleted (rather than throwing an Exception). If you don't check the result, you won't notice if the method invocation signals unexpected behavior by returning an atypical return value.

#### Rough Constant Value {#FB_CRCV}

It's recommended to use the predefined library constant for code clarity and better precision.

#### Run Finalizers On Exit {#FB_DRFOE}

***Never call System.runFinalizersOnExit or Runtime.runFinalizersOnExit for any reason: they are among the most dangerous methods in the Java libraries.*** -- Joshua Bloch

#### Same Simple Name As Interface {#FB_NSSNAI}

This class/interface has a simple name that is identical to that of an implemented/extended interface, except that the interface is in a different package (e.g., alpha.Foo extends beta.Foo). This can be exceptionally confusing, create lots of situations in which you have to look at import statements to resolve references and creates many opportunities to accidently define methods that do not override methods in their superclasses.

#### Same Simple Name As Superclass {#FB_NSSNAS}

This class has a simple name that is identical to that of its superclass, except that its superclass is in a different package (e.g., alpha.Foo extends beta.Foo). This can be exceptionally confusing, create lots of situations in which you have to look at import statements to resolve references and creates many opportunities to accidently define methods that do not override methods in their superclasses.

#### Self No Object {#FB_ESNO}

This class defines a covariant version of equals().  To correctly override the equals() method in java.lang.Object, the parameter of equals() must have type java.lang.Object.

#### Signed Check {#FB_BSC}

This method compares an expression such as ((event.detail & SWT.SELECTED) \> 0) Using bit arithmetic and then comparing with the greater than operator can lead to unexpected results (of course depending on the value of SWT.SELECTED). If SWT.SELECTED is a negative number, this is a candidate for a bug. Even when SWT.SELECTED is not negative, it seems good practice to use '!= 0' instead of '\> 0'.

***Boris Bokowski***

#### Store Of Non Serializable Object Into Session {#FB_JSONSOIS}

This code seems to be storing a non-serializable object into an HttpSession. If this session is passivated or migrated, an error will result.

#### Superclass Uses Subclass During Initialization {#FB_ISUSDI}

During the initialization of a class, the class makes an active use of a subclass. That subclass will not yet be initialized at the time of this use. For example, in the following code, foo will be null.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public class CircularClassInitialization {

  static class InnerClassSingleton extends CircularClassInitialization {
    static InnerClassSingleton singleton = new InnerClassSingleton();
  }

  static CircularClassInitialization foo = InnerClassSingleton.singleton;
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Swing Methods Invoked In Swing Thread {#FB_SSMIIST}

(*From JDC Tech Tip*): The Swing methods show(), setVisible(), and pack() will create the associated peer for the frame. With the creation of the peer, the system creates the event dispatch thread. This makes things problematic because the event dispatch thread could be notifying listeners while pack and validate are still processing. This situation could result in two threads going through the Swing component-based GUI -- it's a serious flaw that could result in deadlocks or other related threading issues. A pack call causes components to be realized. As they are being realized (that is, not necessarily visible), they could trigger listener notification on the event dispatch thread.

#### Tostring Could Return Null {#FB_NTCRN}

This toString method seems to return null in some circumstances. A liberal reading of the spec could be interpreted as allowing this, but it is probably a bad idea and could cause other code to break. Return the empty string or some other appropriate string rather than null.

#### Transient Field Not Restored {#FB_STFNR}

This class contains a field that is updated at multiple places in the class, thus it seems to be part of the state of the class. However, since the field is marked as transient and not set in readObject or readResolve, it will contain the default value in any deserialized instance of the class.

#### Unchecked Type In Generic Call {#FB_GUTIGC}

This call to a generic collection method passes an argument while compile type Object where a specific type from the generic type parameters is expected. Thus, neither the standard Java type system nor static analysis can provide useful information on whether the object being passed as a parameter is of an appropriate type.

#### Useless {#FB_FU}

The only thing this finalize() method does is call the superclass's finalize() method, making it redundant.  Delete it.

#### Using Removeall To Clear Collection {#FB_DURTCC}

If you want to remove all elements from a collection c, use c.clear, not c.removeAll(c). Calling c.removeAll(c) to clear a collection is less clear, susceptible to errors from typos, less efficient and for some collections, might throw a ConcurrentModificationException.

#### Very Confusing Intentional {#FB_NVCI}

The referenced methods have names that differ only by capitalization. This is very confusing because if the capitalization were identical then one of the methods would override the other. From the existence of other methods, it seems that the existence of both of these methods is intentional, but is sure is confusing. You should try hard to eliminate one of them, unless you are forced to have both due to frozen APIs.

#### Wrong Package Intentional {#FB_NWPI}

The method in the subclass doesn't override a similar method in a superclass because the type of a parameter doesn't exactly match the type of the corresponding parameter in the superclass. For example, if you have:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
import alpha.Foo;
public class A {
  public int f(Foo x) { return 17; }
}

//----

import beta.Foo;
public class B extends A {
  public int f(Foo x) { return 42; }
  public int f(alpha.Foo x) { return 27; }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The f(Foo) method defined in class B doesn't override the f(Foo) method defined in class A, because the argument types are Foo's from different packages.

In this case, the subclass does define a method with a signature identical to the method in the superclass, so this is presumably understood. However, such methods are exceptionally confusing. You should strongly consider removing or deprecating the method with the similar but not identical signature.

### Correctness Rules

#### 01 To Int {#FB_R0TI}

A random value from 0 to 1 is being coerced to the integer value 0. You probably want to multiple the random value by something else before coercing it to an integer, or use the Random.nextInt(n) method.

#### Absolute Value Of Hashcode {#FB_RAVOH}

This code generates a hashcode and then computes the absolute value of that hashcode. If the hashcode is Integer.MIN\_VALUE, then the result will be negative as well (since Math.abs(Integer.MIN\_VALUE) == Integer.MIN\_VALUE).

One out of 2\^32 strings have a hashCode of Integer.MIN\_VALUE, including "polygenelubricants" "GydZG\_" and ""DESIGNING WORKHOUSES".

#### Absolute Value Of Random Int {#FB_RAVORI}

This code generates a random signed integer and then computes the absolute value of that random integer. If the number returned by the random number generator is Integer.MIN\_VALUE, then the result will be negative as well (since Math.abs(Integer.MIN\_VALUE) == Integer.MIN\_VALUE). (Same problem arised for long values as well).

#### Add Of Signed Byte {#FB_BAOSB}

Adds a byte value and a value which is known to have the 8 lower bits clear. Values loaded from a byte array are sign extended to 32 bits before any any bitwise operations are performed on the value. Thus, if b[0] contains the value 0xff, and x is initially 0, then the code ((x \<\< 8) + b[0]) will sign extend 0xff to get 0xffffffff, and thus give the value 0xffffffff as the result.

In particular, the following code for packing a byte array into an int is badly wrong:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
int result = 0;
for(int i = 0; i < 4; i++)
  result = ((result << 8) + b[i]);

// The following idiom will work instead:

int result = 0;
for(int i = 0; i < 4; i++)
  result = ((result << 8) + (b[i] & 0xff));
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Always False {#FB_EAF}

This class defines an equals method that always returns false. This means that an object is not equal to itself, and it is impossible to create useful Maps or Sets of this class. More fundamentally, it means that equals is not reflexive, one of the requirements of the equals method.

The likely intended semantics are object identity: that an object is equal to itself. This is the behavior inherited from class Object. If you need to override an equals inherited from a different superclass, you can use use:

public boolean equals(Object o) { return this == o; }

#### Always Null {#FB_NAN}

A null pointer is dereferenced here.  This will lead to a NullPointerException when the code is executed.

#### Always Null Exception {#FB_NANE}

A pointer which is null on an exception path is dereferenced here.  This will lead to a NullPointerException when the code is executed.  Note that because FindBugs currently does not prune infeasible exception paths, this may be a false warning.

Also note that FindBugs considers the default case of a switch statement to be an exception path, since the default case is often infeasible.

#### Always True {#FB_EAT}

This class defines an equals method that always returns true. This is imaginative, but not very smart. Plus, it means that the equals method is not symmetric.

#### Always Value Used Where Never Required {#FB_TAVUWNR}

A value specified as carrying a type qualifier annotation is consumed in a location or locations requiring that the value not carry that annotation.

More precisely, a value annotated with a type qualifier specifying when=ALWAYS is guaranteed to reach a use or uses where the same type qualifier specifies when=NEVER.

For example, say that @NonNegative is a nickname for the type qualifier annotation @Negative(when=When.NEVER). The following code will generate this warning because the return statement requires a @NonNegative value,
but receives one that is marked as @Negative.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public @NonNegative Integer example(@Negative Integer value) {
  return value;
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### And {#FB_BA}

This method compares an expression of the form (e & C) to D, which will always compare unequal due to the specific values of constants C and D. This may indicate a logic error or typo.

#### And Zz {#FB_BAZ}

This method compares an expression of the form (e & 0) to 0, which will always compare equal. This may indicate a logic error or typo.

#### Annotation Is Not Visible To Reflection {#FB_DAINVTR}

Unless an annotation has itself been annotated with @Retention(RetentionPolicy.RUNTIME), the annotation can't be observed using reflection (e.g., by using the isAnnotationPresent method).

#### Appending To Object Output Stream {#FB_IATOOS}

This code opens a file in append mode and then wraps the result in an object output stream. This won't allow you to append to an existing object output stream stored in a file. If you want to be able to append to an object output stream, you need to keep the object output stream open.

The only situation in which opening a file in append mode and the writing an object output stream could work is if on reading the file you plan to open it in random access mode and seek to the byte offset where the append started.

#### Argument Might Be Null {#FB_NAMBN}

A parameter to this method has been identified as a value that should always be checked to see whether or not it is null, but it is being dereferenced without a preceding null check.

#### Arguments Wrong Order {#FB_DAWO}

The arguments to this method call seem to be in the wrong order. For example, a call Preconditions.checkNotNull("message", message) has reserved arguments: the value to be checked is the first argument.

#### Array And Nonarray {#FB_EAAN}

This method invokes the .equals(Object o) to compare an array and a reference that doesn't seem to be an array. If things being compared are of different types, they are guaranteed to be unequal and the comparison is almost certainly an error. Even if they are both arrays, the equals method on arrays only determines of the two arrays are the same object. To compare the contents of the arrays, use java.util.Arrays.equals(Object[], Object[]).

#### Assert Method Invoked From Run Method {#FB_IAMIFRM}

A JUnit assertion is performed in a run method. Failed JUnit assertions just result in exceptions being thrown. Thus, if this exception occurs in a thread other than the thread that invokes the test method, the exception will terminate the thread but not result in the test failing.

#### Bad Array Compare {#FB_EBAC}

This method invokes the .equals(Object o) method on an array. Since arrays do not override the equals method of Object, calling equals on an array is the same as comparing their addresses. To compare the contents of the arrays, use java.util.Arrays.equals(Object[], Object[]). To compare the addresses of the arrays, it would be less confusing to explicitly check pointer equality using ==.

#### Bad Comparison With Int Value {#FB_IBCWIV}

This code compares an int value with a long constant that is outside the range of values that can be represented as an int value. This comparison is vacuous and possibily to be incorrect.

#### Bad Comparison With Nonnegative Value {#FB_IBCWNV}

This code compares a value that is guaranteed to be non-negative with a negative constant.

#### Bad Comparison With Signed Byte {#FB_IBCWSB}

Signed bytes can only have a value in the range -128 to 127. Comparing a signed byte with a value outside that range is vacuous and likely to be incorrect. To convert a signed byte b to an unsigned value in the range 0..255, use 0xff & b

#### Bad Equal {#FB_NBE}

This class defines a method equal(Object).  This method does not override the equals(Object) method in java.lang.Object, which is probably what was intended.

#### Bad Month {#FB_DBM}

This code passes a constant month value outside the expected range of 0..11 to a method.

#### Bad Prepared Statement Access {#FB_SBPSA}

A call to a setXXX method of a prepared statement was made where the parameter index is 0. As parameter indexes start at index 1, this is always a mistake.

#### Bad Resultset Access {#FB_SBRA}

A call to getXXX or updateXXX methods of a result set was made where the field index is 0. As ResultSet fields start at index 1, this is always a mistake.

#### Bad Shift Amount {#FB_IBSA}

The code performs shift of a 32 bit int by a constant amount outside the range -31..31. The effect of this is to use the lower 5 bits of the integer value to decide how much to shift by (e.g., shifting by 40 bits is the same as shifting by 8 bits, and shifting by 32 bits is the same as shifting by zero bits). This probably isn't what was expected, and it is at least confusing.

#### Bad Suite Method {#FB_IBSM}

Class is a JUnit TestCase and defines a suite() method. However, the suite method needs to be declared as either

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public static junit.framework.Test suite()

// OR

public static junit.framework.TestSuite suite()
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


#### Bad Syntax For Regular Expression {#FB_RBSFRE}

The code here uses a regular expression that is invalid according to the syntax for regular expressions. This statement will throw a PatternSyntaxException when executed.

#### Badly Overridden Adapter {#FB_BBOA}

This method overrides a method found in a parent class, where that class is an Adapter that implements a listener defined in the java.awt.event or javax.swing.event package. As a result, this method will not get called when the event occurs.

#### Bigdecimal Constructed From Double {#FB_ADLIBDC}

This code creates a BigDecimal from a double value that doesn't translate well to a decimal number. For example, one might assume that writing new BigDecimal(0.1) in Java creates a BigDecimal which is exactly equal to 0.1 (an unscaled value of 1, with a scale of 1), but it is actually equal to 0.1000000000000000055511151231257827021181583404541015625. You probably want to use the BigDecimal.valueOf(double d) method, which uses the String representation of the double to create the BigDecimal (e.g., BigDecimal.valueOf(0.1) gives 0.1).

#### Calling Next From Hasnext {#FB_DCNFH}

The hasNext() method invokes the next() method. This is almost certainly wrong, since the hasNext() method is not supposed to change the state of the iterator, and the next method is supposed to change the state of the iterator.

#### Cant Use File Separator As Regular Expression {#FB_RCUFSARE}

The code here uses File.separator where a regular expression is required. This will fail on Windows platforms, where the File.separator is a backslash, which is interpreted in a regular expression as an escape character. Amoung other options, you can just use File.separatorChar=='\\\\' ? "\\\\\\\\" : File.separator instead of File.separator

#### Check Compareto For Specific Return Value {#FB_RCCFSRV}

This code invoked a compareTo or compare method, and checks to see if the return value is a specific value, such as 1 or -1. When invoking these methods, you should only check the sign of the result, not for any specific non-zero value. While many or most compareTo and compare methods only return -1, 0 or 1, some of them will return other values.

#### Class Masks Field {#FB_MCMF}

This class defines a field with the same name as a visible instance field in a superclass. This is confusing, and may indicate an error if methods update or access one of the fields when they wanted the other.

#### Closing Null {#FB_NCN}

close() is being invoked on a value that is always null. If this statement is executed, a null pointer exception will occur. But the big risk here you never close something that should be closed.

#### Collections Should Not Contain Themselves {#FB_DCSNCT}

This call to a generic collection's method would only make sense if a collection contained itself (e.g., if s.contains(s) were true). This is unlikely to be true and would cause problems if it were true (such as the computation of the hash code resulting in infinite recursion). It is likely that the wrong value is being passed as a parameter.

#### Compareto Results Min Value {#FB_CCRMV}

In some situation, this compareTo or compare method returns the constant Integer.MIN\_VALUE, which is an exceptionally bad practice. The only thing that matters about the return value of compareTo is the sign of the result. But people will sometimes negate the return value of compareTo, expecting that this will negate the sign of the result. And it will, except in the case where the value returned is Integer.MIN\_VALUE. So just return -1 rather than Integer.MIN\_VALUE.

#### Comparing Class Names {#FB_ECCN}

This method checks to see if two objects are the same class by checking to see if the names of their classes are equal. You can have different classes with the same name if they are loaded by different class loaders. Just check to see if the class objects are the same.

#### Comparing Values With Incompatible Type Qualifiers {#FB_TCVWITQ}

A value specified as carrying a type qualifier annotation is compared with a value that doesn't ever carry that qualifier.

More precisely, a value annotated with a type qualifier specifying when=ALWAYS is compared with a value that where the same type qualifier specifies when=NEVER.

For example, say that @NonNegative is a nickname for the type qualifier annotation @Negative(when=When.NEVER). The following code will generate this warning because the return statement requires a @NonNegative value, but receives one that is marked as @Negative.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public boolean example(@Negative Integer value1, @NonNegative Integer value2) {
  return value1.equals(value2);
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Container Added To Itself {#FB_ICATI}

A collection is added to itself. As a result, computing the hashCode of this set will throw a StackOverflowException.

#### Dead Local Increment In Return {#FB_UPF}

This statement has a return such as return x++;. A postfix increment/decrement does not impact the value of the expression, so this increment/decrement has no effect. Please verify that this statement does the right thing.

#### Dead Store Due To Switch Fallthrough {#FB_SDSDTSF}

A value stored in the previous switch case is overwritten here due to a switch fall through. It is likely that you forgot to put a break or return at the end of the previous case.

#### Dead Store Due To Switch Fallthrough To Throw {#FB_SDSDTSFTT}

A value stored in the previous switch case is ignored here due to a switch fall through to a place where an exception is thrown. It is likely that you forgot to put a break or return at the end of the previous case.

#### Dead Store Of Class Literal {#FB_DDSOCL}

This instruction assigns a class literal to a variable and then never uses it. *The behavior of this differs in Java 1.4 and in Java 5.* In Java 1.4 and earlier, a reference to Foo.class would force the static initializer for Foo to be executed, if it has not been executed already. In Java 5 and later, it does not.

See Sun's *article on Java SE compatibility* for more details and examples, and suggestions on how to force class initialization in Java 5.

#### Doh {#FB_DmD}

This partical method invocation doesn't make sense, for reasons that should be apparent from inspection.

#### Dont Define Equals For Enum {#FB_EDDEFE}

This class defines an enumeration, and equality on enumerations are defined using object identity. Defining a covariant equals method for an enumeration value is exceptionally bad practice, since it would likely result in having two different enumeration values that compare as equals using the covariant enum method, and as not equal when compared normally. Don't do it.

#### Exception Not Thrown {#FB_RENT}

This code creates an exception (or error) object, but doesn't do anything with it. For example, something like

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
if (x < 0)
  new IllegalArgumentException("x must be nonnegative");
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

It was probably the intent of the programmer to throw the created exception:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
if (x < 0)
  throw new IllegalArgumentException("x must be nonnegative");
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Field Self Assignment {#FB_SFSA}

This method contains a self assignment of a field; e.g.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
int x;

public void foo() {
  x = x;
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Such assignments are useless, and may indicate a logic error or typo.

#### Field Self Comparison {#FB_SFSC}

This method compares a field with itself, and may indicate a typo or a logic error. Make sure that you are comparing the right things.

#### Field Self Computation {#FB_SaFSC}

This method performs a nonsensical computation of a field with another reference to the same field (e.g., x&x or x-x). Because of the nature of the computation, this operation doesn't seem to make sense, and may indicate a typo or a logic error. Double check the computation.

#### Format String Bad Argument {#FB_VFSBA}

The format string placeholder is incompatible with the corresponding argument. For example, System.out.println("%d\\n", "hello");

The %d placeholder requires a numeric argument, but a string value is passed instead. A runtime exception will occur when this statement is executed.

#### Format String Bad Conversion {#FB_VFSBC}

One of the arguments is uncompatible with the corresponding format string specifier. As a result, this will generate a runtime exception when executed. For example, String.format("%d", "1") will generate an exception, since the String "1" is incompatible with the format specifier %d.

#### Format String Bad Conversion From Array {#FB_VFSBCFA}

One of the arguments being formatted with a format string is an array. This will be formatted using a fairly useless format, such as [I@304282, which doesn't actually show the contents of the array. Consider wrapping the array using Arrays.asList(...) before handling it off to a formatted.

#### Format String Expected Message Format Supplied {#FB_VFSEMFS}

A method is called that expects a Java printf format string and a list of arguments. However, the format string doesn't contain any format specifiers (e.g., %s) but does contain message format elements (e.g., {0}). It is likely that the code is supplying a MessageFormat string when a printf-style format string is required. At runtime, all of the arguments will be ignored and the format string will be returned exactly as provided without any formatting.

#### Format String Extra Arguments Passed {#FB_VFSEAP}

A format-string method with a variable number of arguments is called, but more arguments are passed than are actually used by the format string. This won't cause a runtime exception, but the code may be silently omitting information that was intended to be included in the formatted string.

#### Format String Illegal {#FB_VFSI}

The format string is syntactically invalid, and a runtime exception will occur when this statement is executed.

#### Format String Missing Argument {#FB_VFSMA}

Not enough arguments are passed to satisfy a placeholder in the format string. A runtime exception will occur when this statement is executed.

#### Format String No Previous Argument {#FB_VFSNPA}

The format string specifies a relative index to request that the argument for the previous format specifier be reused. However, there is no previous argument. For example,

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
formatter.format("%<s %s", "a", "b")
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

would throw a MissingFormatArgumentException when executed.

#### Futile Attempt To Change Maxpool Size Of Scheduled Thread Pool Executor {#FB_DFATCMSOSTPE}

(*Javadoc*) While ScheduledThreadPoolExecutor inherits from ThreadPoolExecutor, a few of the inherited tuning methods are not useful for it. In particular, because it acts as a fixed-sized pool using corePoolSize threads and an unbounded queue, adjustments to maximumPoolSize have no useful effect.

#### Guaranteed Deref {#FB_NGD}

There is a statement or branch that if executed guarantees that a value is null at this point, and that value that is guaranteed to be dereferenced (except on forward paths involving runtime exceptions).

Note that a check such as if (x == null) throw new NullPointerException(); is treated as a dereference of x.

#### Guaranteed Deref On Exception Path {#FB_NGDOEP}

There is a statement or branch on an exception path that if executed guarantees that a value is null at this point, and that value that is guaranteed to be dereferenced (except on forward paths involving runtime exceptions).

#### Impossible Cast {#FB_BIC}

This cast will always throw a ClassCastException. FindBugs tracks type information from instanceof checks, and also uses more precise information about the types of values returned from methods and loaded from fields. Thus, it may have more precise information that just the declared type of a variable, and can use this to determine that a cast will always throw an exception at runtime.

#### Impossible Downcast {#FB_BID}

This cast will always throw a ClassCastException. The analysis believes it knows the precise type of the value being cast, and the attempt to downcast it to a subtype will always fail by throwing a ClassCastException.

#### Impossible Downcast Of Toarray {#FB_CCEWTA}

This code is casting the result of calling toArray() on a collection to a type more specific than Object[], as in:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
String[] getAsArray(Collection<String> c) {
  return (String[]) c.toArray();
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This will usually fail by throwing a ClassCastException. The toArray() of almost all collections return an Object[]. They can't really do anything else, since the Collection object has no reference to the declared generic type of the collection.

The correct way to do get an array of a specific type from a collection is to use c.toArray(new String[]); or c.toArray(new String[c.size()]); the latter is slightly more efficient).

There is one common/known exception exception to this. The toArray() method of lists returned by Arrays.asList(...) will return a covariantly typed array. For example, Arrays.asArray(new String[] { "a" }).toArray() will return a String []. FindBugs attempts to detect and suppress such cases, but may miss some.

#### Impossible Instanceof {#FB_BcII}

This instanceof test will always return false. Although this is safe, make sure it isn't an indication of some misunderstanding or some other logic error.

#### Incompatible Array Compare {#FB_EIAC}

This method invokes the .equals(Object o) to compare two arrays, but the arrays of of incompatible types (e.g., String[] and StringBuffer[], or String[] and int[]). They will never be equal. In addition, when equals(...) is used to compare arrays it only checks to see if they are the same array, and ignores the contents of the arrays.

#### Infinite Loop {#FB_IIL}

This loop doesn't seem to have a way to terminate (other than by perhaps throwing an exception).

#### Infinite Recursive Loop {#FB_IIRL}

This method unconditionally invokes itself. This would seem to indicate an infinite recursive loop that will result in a stack overflow.

#### Int 2 Long As Instant {#FB_II2LAI}

This code converts a 32-bit int value to a 64-bit long value, and then passes that value for a method parameter that requires an absolute time value. An absolute time value is the number of milliseconds since the standard base time known as "the epoch", namely January 1, 1970, 00:00:00 GMT. For example, the following method, intended to convert seconds since the epoc into a Date, is badly broken:

Date getDate(int seconds) { return new Date(seconds \* 1000); }

The multiplication is done using 32-bit arithmetic, and then converted to a 64-bit value. When a 32-bit value is converted to 64-bits and used to express an absolute time value, only dates in December 1969 and January 1970 can be represented.

Correct implementations for the above method are:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
// Fails for dates after 2037
Date getDate(int seconds) { return new Date(seconds * 1000L); }

// better, works for all dates
Date getDate(long seconds) { return new Date(seconds * 1000); }
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Int Cast To Double Passed To Ceil {#FB_IICTDPTC}

This code converts an integral value (e.g., int or long) to a double precision floating point number and then passing the result to the Math.ceil() function, which rounds a double to the next higher integer value. This operation should always be a no-op, since the converting an integer to a double should give a number with no fractional part. It is likely that the operation that generated the value to be passed to Math.ceil was intended to be performed using double precision floating
point arithmetic.

#### Int Cast To Float Passed To Round {#FB_IICTFPTR}

This code converts an int value to a float precision floating point number and then passing the result to the Math.round() function, which returns the int/long closest to the argument. This operation should always be a no-op, since the converting an integer to a float should give a number with no fractional part. It is likely that the operation that generated the value to be passed to Math.round was intended to be performed using floating point arithmetic.

#### Interrupted On Currentthread {#FB_SIOC}

This method invokes the Thread.currentThread() call, just to call the interrupted() method. As interrupted() is a static method, is more simple and clear to use Thread.interrupted().

#### Interrupted On Unknownthread {#FB_SIOU}

This method invokes the Thread.interrupted() method on a Thread object that appears to be a Thread object that is not the current thread. As the interrupted() method is static, the interrupted method will be called on a different object than the one the author intended.

#### Invoking Hashcode On Array {#FB_DIHOA}

The code invokes hashCode on an array. Calling hashCode on an array returns the same value as System.identityHashCode, and ingores the contents and length of the array. If you need a hashCode that depends on the contents of an array a, use java.util.Arrays.hashCode(a).

#### Invoking Tostring On Anonymous Array {#FB_DITOAA}

The code invokes toString on an (anonymous) array. Calling toString on an array generates a fairly useless result such as [C@16f0472. Consider using Arrays.toString to convert the array into a readable String that gives the contents of the array. See Programming Puzzlers, chapter 3, puzzle 12.

#### Invoking Tostring On Array {#FB_DITOA}

The code invokes toString on an array, which will generate a fairly useless result such as [C@16f0472. Consider using Arrays.toString to convert the array into a readable String that gives the contents of the array. See Programming Puzzlers, chapter 3, puzzle 12.

#### Ior {#FB_BiI}

This method compares an expression of the form (e | C) to D. which will always compare unequal due to the specific values of constants C and D. This may indicate a logic error or typo.

Typically, this bug occurs because the code wants to perform a membership test in a bit set, but uses the bitwise OR operator ("|") instead of bitwise AND ("&").

#### Ior Of Signed Byte {#FB_BIOSB}

Loads a byte value (e.g., a value loaded from a byte array or returned by a method with return type byte) and performs a bitwise OR with that value. Byte values are sign extended to 32 bits before any any bitwise operations are performed on the value. Thus, if b[0] contains the value 0xff, and x is initially 0, then the code ((x \<\< 8) | b[0]) will sign extend 0xff to get 0xffffffff, and thus give the value 0xffffffff as the result.

In particular, the following code for packing a byte array into an int is badly wrong:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
int result = 0;
for(int i = 0; i < 4; i++)
  result = ((result << 8) | b[i]);

// The following idiom will work instead:

int result = 0;
for(int i = 0; i < 4; i++)
  result = ((result << 8) | (b[i] & 0xff));
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Lcase Hashcode {#FB_SHMN}

This class defines a method called hashcode().  This method does not override the hashCode() method in java.lang.Object, which is probably what was intended.

#### Lcase Tostring {#FB_NLT}

This class defines a method called tostring().  This method does not override the toString() method in java.lang.Object, which is probably what was intended.

#### Local Self Assignment Instead Of Field {#FB_SLSAIOF}

This method contains a self assignment of a local variable, and there is a field with an identical name. assignment appears to have been ; e.g.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
int foo;

public void setFoo(int foo) {
  foo = foo;
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The assignment is useless. Did you mean to assign to the field instead?

#### Local Self Comparison {#FB_SLSC}

This method compares a local variable with itself, and may indicate a typo or a logic error. Make sure that you are comparing the right things.

#### Local Self Computation {#FB_SaLSC}

This method performs a nonsensical computation of a local variable with another reference to the same variable (e.g., x&x or x-x). Because of the nature of the computation, this operation doesn't seem to make sense, and may indicate a typo or a logic error. Double check the computation.

#### Long Bits To Double Invoked On Int {#FB_DLBTDIOI}

The Double.longBitsToDouble method is invoked, but a 32 bit int value is passed as an argument. This almostly certainly is not intended and is unlikely to give the intended result.

#### Math Using Float Precision {#FB_FMUFP}

The method performs math operations using floating point precision. Floating point precision is very imprecise. For example, 16777216.0f + 1.0f = 16777216.0f. Consider using double math instead.

#### Maybe Source Value Reaches Always Sink {#FB_TMSVRAS}

A value that is annotated as possibility not being an instance of the values denoted by the type qualifier, and the value is guaranteed to be used in a way that requires values denoted by that type qualifier.

#### Maybe Source Value Reaches Never Sink {#FB_TMSVRNS}

A value that is annotated as possibility being an instance of the values denoted by the type qualifier, and the value is guaranteed to be used in a way that prohibits values denoted by that type qualifier.

#### Method Constructor Confusion {#FB_MWSNAEC}

This regular method has the same name as the class it is defined in. It is likely that this was intended to be a constructor. If it was intended to be a constructor, remove the declaration of a void return value. If you had accidently defined this method, realized the mistake, defined a proper constructor but can't get rid of this method due to backwards compatibility, deprecate the method.

#### Method Masks Field {#FB_MMMF}

This method defines a local variable with the same name as a field in this class or a superclass. This may cause the method to read an uninitialized value from the field, leave the field uninitialized, or both.

#### Method Must Be Private {#FB_SMMBP}

This class implements the Serializable interface, and defines a method for custom serialization/deserialization. But since that method isn't declared private, it will be silently ignored by the serialization/deserialization API.

#### Missing Expected Warning {#FB_FMEW}

FindBugs didn't generate generated a warning that, according to a @ExpectedWarning annotated, is expected or desired

#### Multiplying Result Of Irem {#FB_IMROI}

The code multiplies the result of an integer remaining by an integer constant. Be sure you don't have your operator precedence confused. For example i % 60 \* 1000 is (i % 60) \* 1000, not i % (60 \* 1000).

#### Never Value Used Where Always Required {#FB_TNVUWAR}

A value specified as not carrying a type qualifier annotation is guaranteed to be consumed in a location or locations requiring that the value does carry that annotation.

More precisely, a value annotated with a type qualifier specifying when=NEVER is guaranteed to reach a use or uses where the same type qualifier specifies when=ALWAYS.

#### No Tests {#FB_INT}

Class is a JUnit TestCase but has not implemented any test methods

#### Nonnull Field Not Initialized In Constructor {#FB_NNFNIIC}

The field is marked as nonnull, but isn't written to by the constructor. The field might be initialized elsewhere during constructor, or might always be initialized before use.

#### Nonnull Param Violation {#FB_NNPV}

This method passes a null value as the parameter of a method which must be nonnull. Either this parameter has been explicitly marked as @Nonnull, or analysis has determined that this parameter is always dereferenced.

#### Nonnull Return Violation {#FB_NNRV}

This method may return a null value, but the method (or a superclass method which it overrides) is declared to return @NonNull.

#### Null Arg {#FB_ENA}

This method calls equals(Object), passing a null value as the argument. According to the contract of the equals() method, this call should always return false.

#### Null Field {#FB_UNF}

All writes to this field are of the constant value null, and thus all reads of the field will return null. Check for errors, or remove it if it is useless.

#### Null Instanceof {#FB_NNI}

This instanceof test will always return false, since the value being checked is guaranteed to be null. Although this is safe, make sure it isn't an indication of some misunderstanding or some other logic error.

#### Null On Some Path {#FB_NNOSP}

There is a branch of statement that, ***if executed,*** guarantees that a null value will be dereferenced, which would generate a NullPointerException when the code is executed. Of course, the problem might be that the branch or statement is infeasible and that the null pointer exception can't ever be executed; deciding that is beyond the ability of FindBugs.

#### Null On Some Path Exception {#FB_NNOSPE}

A reference value which is null on some exception control path is dereferenced here.  This may lead to a NullPointerException when the code is executed.  Note that because FindBugs currently does not prune infeasible exception paths, this may be a false warning.

Also note that FindBugs considers the default case of a switch statement to be an exception path, since the default case is often infeasible.

#### Null Param Deref {#FB_NNPD}

This method call passes a null value for a nonnull method parameter. Either the parameter is annotated as a parameter that should always be nonnull, or analysis has shown that it will always be dereferenced.

#### Null Param Deref All Targets Dangerous {#FB_NNPDATD}

A possibly-null value is passed at a call site where all known target methods require the parameter to be nonnull. Either the parameter is annotated as a parameter that should always be nonnull, or analysis has
shown that it will always be dereferenced.

#### Null Param Deref Nonvirtual {#FB_NNPDN}

A possibly-null value is passed to a nonnull method parameter. Either the parameter is annotated as a parameter that should always be nonnull, or analysis has shown that it will always be dereferenced.

#### Optional Return Null {#FB_NORN}

The usage of Optional return type always mean that explicit null returns were not desired by design. Returning a null value in such case is a contract violation and will most likely break clients code.

#### Other No Object {#FB_EONO}

This class defines an equals() method, that doesn't override the normal equals(Object) method defined in the base java.lang.Object class.  Instead, it inherits an equals(Object) method from a superclass. The class should probably define a boolean equals(Object) method.

#### Other Use Object {#FB_EOUO}

This class defines an equals() method, that doesn't override the normal equals(Object) method defined in the base java.lang.Object class.  The class should probably define a boolean equals(Object) method. 

#### Overriding Equals Not Symmetric {#FB_EOENS}

This class defines an equals method that overrides an equals method in a superclass. Both equals methods methods use instanceof in the determination of whether two objects are equal. This is fraught with peril, since it is important that the equals method is symmetrical (in other words, a.equals(b) == b.equals(a)). If B is a subtype of A, and A's equals method checks that the argument is an instanceof A, and B's equals method checks that the argument is an instanceof B, it is quite likely that the equivalence relation defined by these methods is not symmetric.

#### Overwritten Increment {#FB_DOI}

The code performs an increment operation (e.g., i++) and then immediately overwrites it. For example, i = i++ immediately overwrites the incremented value with the original value.

#### Parameter Is Dead But Overwritten {#FB_IPIDBO}

The initial value of this parameter is ignored, and the parameter is overwritten here. This often indicates a mistaken belief that the write to the parameter will be conveyed back to the caller.

#### Possible Unintended Pattern {#FB_RPUP}

A String function is being invoked and "." or "|" is being passed to a parameter that takes a regular expression as an argument. Is this what you intended? For example

- s.replaceAll(".", "/") will return a String in which ***every*** character has been replaced by a '/' character

- s.split(".") ***always*** returns a zero length array of String

- "ab|cd".replaceAll("|", "/") will return "/a/b/|/c/d/"

- "ab|cd".split("|") will return array with six (!) elements: [, a, b, |, c, d]

#### Primitive Array Passed To Object Vararg {#FB_VPAPTOV}

This code passes a primitive array to a function that takes a variable number of object arguments. This creates an array of length one to hold the primitive array and passes it to the function.

#### Questionable Boolean Assignment {#FB_QQBA}

This method assigns a literal boolean value (true or false) to a boolean variable inside an if or while expression. Most probably this was supposed to be a boolean comparison using ==, not an assignment using =.

#### Read Resolve Is Static {#FB_SRRIS}

In order for the readResolve method to be recognized by the serialization mechanism, it must not be declared as a static method.

#### Redundant Nullcheck Would Have Been A Npe {#FB_RRNWHBAN}

A value is checked here to see whether it is null, but this value can't be null because it was previously dereferenced and if it were null a null pointer exception would have occurred at the earlier dereference. Essentially, this code and the previous dereference disagree as to whether this value is allowed to be null. Either the check is redundant or the previous dereference is erroneous.

#### Ref Comparison {#FB_RRC}

This method compares two reference values using the == or != operator, where the correct way to compare instances of this type is generally with the equals() method. It is possible to create distinct instances that are equal but do not compare as == since they are different objects. Examples of classes which should generally not be compared by reference are java.lang.Integer, java.lang.Float, etc.

#### Repeated Conditional Test {#FB_RRCT}

The code contains a conditional test is performed twice, one right after the other (e.g., x == 0 || x == 0). Perhaps the second occurrence is intended to be something else (e.g., x == 0 || y == 0).

#### Return Value Ignored {#FB_RRVI}

The return value of this method should be checked. One common cause of this warning is to invoke a method on an immutable object, thinking that it updates the object. For example, in the following code fragment,

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
String dateString = getHeaderField(name);
dateString.trim();
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

the programmer seems to be thinking that the trim() method will update the String referenced by dateString. But since Strings are immutable, the trim() function returns a new String value, which is being ignored here. The code should be corrected to:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
String dateString = getHeaderField(name);
dateString = dateString.trim();
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Scheduled Thread Pool Executor With Zero Core Threads {#FB_DSTPEWZCT}

(*Javadoc*) A ScheduledThreadPoolExecutor with zero core threads will never execute anything; changes to the max pool size are ignored.

#### Self Use Object {#FB_ESUO}

This class defines a covariant version of the equals() method, but inherits the normal equals(Object) method defined in the base java.lang.Object class.  The class should probably define a boolean equals(Object) method.

#### Setup No Super {#FB_ISNS}

Class is a JUnit TestCase and implements the setUp method. The setUp method should call super.setUp(), but doesn't.

#### Signature Declares Hashing Of Unhashable Class {#FB_HSDHOUC}

A method, field or class declares a generic signature where a non-hashable class is used in context where a hashable class is required. A class that declares an equals method but inherits a hashCode() method from Object is unhashable, since it doesn't fulfill the requirement that equal objects have equal hashCodes.

#### Signed Check High Bit {#FB_BSCHB}

This method compares an expression such as

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
((event.detail & SWT.SELECTED) > 0)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Using bit arithmetic and then comparing with the greater than operator can lead to unexpected results (of course depending on the value of SWT.SELECTED). If SWT.SELECTED is a negative number, this is a candidate for a bug. Even when SWT.SELECTED is not negative, it seems good practice to use '!= 0' instead of '\> 0'.

***Boris Bokowski***

#### Store Into Nonnull Field {#FB_NSINF}

A value that could be null is stored into a field that has been annotated as NonNull.

#### Suite Not Static {#FB_JUSS}

Class is a JUnit TestCase and implements the suite() method. The suite method should be declared as being static, but isn't.

#### Superfluous Instanceof {#FB_SSI}

Type check performed using the instanceof operator where it can be statically determined whether the object is of the type requested.

#### Teardown No Super {#FB_ITNS}

Class is a JUnit TestCase and implements the tearDown method. The tearDown method should call super.tearDown(), but doesn't.

#### Test If Equal To Not A Number {#FB_BC}

This code checks to see if a floating point value is equal to the special Not A Number value (e.g., if (x == Double.NaN)). However, because of the special semantics of NaN, no value is equal to Nan, including NaN. Thus, x == Double.NaN always evaluates to false. To check to see if a value contained in x is the special Not A Number value, use Double.isNaN(x) (or Float.isNaN(x) if x is floating point precision).

#### Threadlocal Deadly Embrace {#FB_STDE}

This class is an inner class, but should probably be a static inner class. As it is, there is a serious danger of a deadly embrace between the inner class and the thread local in the outer class. Because the inner class isn't static, it retains a reference to the outer class. If the thread local contains a reference to an instance of the inner class, the inner and outer instance will both be reachable and not eligible for garbage collection.

#### Unboxed And Coerced For Ternary Operator {#FB_BUACFTO}

A wrapped primitive value is unboxed and converted to another primitive type as part of the evaluation of a conditional ternary operator (the b ? e1 : e2 operator). The semantics of Java mandate that if e1 and e2 are wrapped numeric values, the values are unboxed and converted/coerced to their common type (e.g, if e1 is of type Integer and e2 is of type Float, then e1 is unboxed, converted to a floating point value, and boxed. See JLS Section 15.25.

#### Uncallable Method Of Anonymous Class {#FB_UUMOAC}

This anonymous class defined a method that is not directly invoked and does not override a method in a superclass. Since methods in other classes cannot directly invoke methods declared in an anonymous class, it seems that this method is uncallable. The method might simply be dead code, but it is also possible that the method is intended to override a method declared in a superclass, and due to an typo or other error the method does not, in fact, override the method it is intended to.

#### Unexpected Warning {#FB_FUW}

FindBugs generated a warning that, according to a @NoWarning annotated, is unexpected or undesired

#### Uninit Read {#FB_UUR}

This constructor reads a field which has not yet been assigned a value.  This is often caused when the programmer mistakenly uses the field instead of one of the constructor's parameters.

#### Uninit Read Called From Super Constructor {#FB_UURCFSC}

This method is invoked in the constructor of of the superclass. At this point, the fields of the class have not yet initialized.

To make this more concrete, consider the following classes:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
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
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

When a B is constructed, the constructor for the A class is invoked ***before*** the constructor for B sets value. Thus, when the constructor for A invokes getValue, an uninitialized value is read for value

#### Unknown Value Used Where Always Strictly Required {#FB_TUVUWASR}

A value is being used in a way that requires the value be annotation with a type qualifier. The type qualifier is strict, so the tool rejects any values that do not have the appropriate annotation.

To coerce a value to have a strict annotation, define an identity function where the return value is annotated with the strict annotation. This is the only way to turn a non-annotated value into a value with a strict type qualifier annotation.

#### Unrelated Class And Interface {#FB_EUCAI}

This method calls equals(Object) on two references, one of which is a class and the other an interface, where neither the class nor any of its non-abstract subclasses implement the interface. Therefore, the objects being compared are unlikely to be members of the same class at runtime (unless some application classes were not analyzed, or dynamic class loading can occur at runtime). According to the contract of equals(), objects of different classes should always compare as unequal; therefore, according to the contract defined by java.lang.Object.equals(Object), the result of this comparison will always be false at runtime.

#### Unrelated Interfaces {#FB_EUI}

This method calls equals(Object) on two references of unrelated interface types, where neither is a subtype of the other, and there are no known non-abstract classes which implement both interfaces. Therefore, the objects being compared are unlikely to be members of the same class at runtime (unless some application classes were not analyzed, or dynamic class loading can occur at runtime). According to the contract of equals(), objects of different classes should always compare as unequal; therefore, according to the contract defined by java.lang.Object.equals(Object), the result of this comparison will always be false at runtime.

#### Unrelated Types {#FB_GUT}

This call to a generic collection method contains an argument with an incompatible class from that of the collection's parameter (i.e., the type of the argument is neither a supertype nor a subtype of the corresponding generic type argument). Therefore, it is unlikely that the collection contains any objects that are equal to the method argument used here. Most likely, the wrong value is being passed to the method.

In general, instances of two unrelated classes are not equal. For example, if the Foo and Bar classes are not related by subtyping, then an instance of Foo should not be equal to an instance of Bar. Among other issues, doing so will likely result in an equals method that is not symmetrical. For example, if you define the Foo class so that a Foo can be equal to a String, your equals method isn't symmetrical since a String can only be equal to a String.

In rare cases, people do define nonsymmetrical equals methods and still manage to make their code work. Although none of the APIs document or guarantee it, it is typically the case that if you check if a Collection\<String\> contains a Foo, the equals method of argument (e.g., the equals method of the Foo class) used to perform the equality checks.

#### Unrelated Types Using Pointer Equality {#FB_EUTUPE}

This method uses using pointer equality to compare two references that seem to be of different types. The result of this comparison will always be false at runtime.

#### Unwritten Field {#FB_UwUF}

This field is never written.  All reads of it will return the default value. Check for errors (should it have been initialized?), or remove it if it is useless.

#### Use Of Unhashable Class {#FB_HUOUC}

A class defines an equals(Object) method but not a hashCode() method, and thus doesn't fulfill the requirement that equal objects have equal hashCodes. An instance of this class is used in a hash data structure, making the need to fix this problem of highest importance.

#### Vacuous Call To Easymock Method {#FB_DVCTEM}

This call doesn't pass any objects to the EasyMock method, so the call doesn't do anything.

#### Vacuous Self Collection Call {#FB_DVSCC}

This call doesn't make sense. For any collection c, calling c.containsAll(c) should always be true, and c.retainAll(c) should have no effect.

#### Very Confusing {#FB_NVC}

The referenced methods have names that differ only by capitalization. This is very confusing because if the capitalization were identical then one of the methods would override the other.

#### Wrong Package {#FB_NWP}

The method in the subclass doesn't override a similar method in a superclass because the type of a parameter doesn't exactly match the type of the corresponding parameter in the superclass. For example, if you have:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
import alpha.Foo;

public class A {
  public int f(Foo x) { return 17; }
}

----

import beta.Foo;

public class B extends A {
  public int f(Foo x) { return 42; }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The f(Foo) method defined in class B doesn't override the f(Foo) method defined in class A, because the argument types are Foo's from different packages.

### Dodgy Code Rules

#### Ambiguous Invocation Of Inherited Or Outer Method {#FB_IAIOIOOM}

An inner class is invoking a method that could be resolved to either a inherited method or a method defined in an outer class. For example, you invoke foo(17), which is defined in both a superclass and in an outer method. By the Java semantics, it will be resolved to invoke the inherited method, but this may not be want you intend.

If you really intend to invoke the inherited method, invoke it by invoking the method on super (e.g., invoke super.foo(17)), and thus it will be clear to other readers of your code and to FindBugs that you want to invoke the inherited method, not the method in the outer class.

If you call this.foo(17), then the inherited method will be invoked. However, since FindBugs only looks at classfiles, it can't tell the difference between an invocation of this.foo(17) and foo(17), it will still complain about a potential ambiguous invocation.

#### Average Computation Could Overflow {#FB_IACCO}

The code computes the average of two integers using either division or signed right shift, and then uses the result as the index of an array. If the values being averaged are very large, this can overflow (resulting in the computation of a negative average). Assuming that the result is intended to be nonnegative, you can use an unsigned right shift instead. In other words, rather that using (low+high)/2, use (low+high) \>\>\> 1  This bug exists in many earlier implementations of binary search and merge sort. Martin Buchholz *found and fixed it* in the JDK libraries, and Joshua Bloch *widely publicized the bug pattern*.

#### Bad Cast To Abstract Collection {#FB_BBCTAC}

This code casts a Collection to an abstract collection (such as List, Set, or Map). Ensure that you are guaranteed that the object is of the type you are casting to. If all you need is to be able to iterate through a collection, you don't need to cast it to a Set or List.

#### Bad Cast To Concrete Collection {#FB_BBCTCC}

This code casts an abstract collection (such as a Collection, List, or Set) to a specific concrete implementation (such as an ArrayList or HashSet). This might not be correct, and it may make your code fragile, since it makes it harder to switch to other concrete implementations at a future point. Unless you have a particular reason to do so, just use the abstract collection class.

#### Bad Check For Odd {#FB_IBCFO}

The code uses x % 2 == 1 to check to see if a value is odd, but this won't work for negative numbers (e.g., (-5) % 2 == -1). If this code is intending to check for oddness, consider using x & 1 == 1, or x % 2 != 0.

#### Bad Rem By 1 {#FB_IBRB1}

Any expression (exp % 1) is guaranteed to always return zero. Did you mean (exp & 1) or (exp % 2) instead?

#### Catch Exception {#FB_RCE}

This method uses a try-catch block that catches Exception objects, but Exception is not thrown within the try block, and RuntimeException is not explicitly caught. It is a common bug pattern to say try { ... } catch (Exception e) { something } as a shorthand for catching a number of types of exception each of whose catch blocks is identical, but this construct also accidentally catches RuntimeException as well, masking potential bugs.

A better approach is to either explicitly catch the specific exceptions that are thrown, or to explicitly catch RuntimeException exception, rethrow it, and then catch all non-Runtime Exceptions, as shown below:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
try {
  ...
} catch (RuntimeException e) {
  throw e;
} catch (Exception e) {
  ... deal with all non-runtime exceptions ...
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Check For Positive Indexof {#FB_RCFPI}

The method invokes String.indexOf and checks to see if the result is positive or non-positive. It is much more typical to check to see if the result is negative or non-negative. It is positive only if the substring checked for occurs at some place other than at the beginning of the String.

#### Confused Inheritance {#FB_APFIFC}

This class is declared to be final, but declares fields to be protected. Since the class is final, it can not be derived from, and the use of protected is confusing. The access modifier for the field should be changed to private or public to represent the true use for the field.

#### Dangerous Non Short Circuit {#FB_NDNSC}

This code seems to be using non-short-circuit logic (e.g., & or |) rather than short-circuit logic (&& or ||). In addition, it seem possible that, depending on the value of the left hand side, you might not want to evaluate the right hand side (because it would have side effects, could cause an exception or could be expensive.

Non-short-circuit logic causes both sides of the expression to be evaluated even when the result can be inferred from knowing the left-hand side. This can be less efficient and can result in errors if the left-hand side guards cases when evaluating the right-hand side can generate an error.

See *the Java Language Specification* for details

#### Dead Local Store {#FB_DDLS}

This instruction assigns a value to a local variable, but the value is not read or used in any subsequent instruction. Often, this indicates an error, because the value computed is never used.

Note that Sun's javac compiler often generates dead stores for final local variables. Because FindBugs is a bytecode-based tool, there is no easy way to eliminate these false positives.

#### Dead Local Store In Return {#FB_DDLSIR}

This statement assigns to a local variable in a return statement. This assignment has effect. Please verify that this statement does the right thing.

#### Dead Local Store Of Null {#FB_DDLSON}

The code stores null into a local variable, and the stored value is not read. This store may have been introduced to assist the garbage collector, but as of Java SE 6.0, this is no longer needed or useful.

#### Dead Local Store Shadows Field {#FB_DDLSSF}

This instruction assigns a value to a local variable, but the value is not read or used in any subsequent instruction. Often, this indicates an error, because the value computed is never used. There is a field with the same name as the local variable. Did you mean to assign to that variable instead?

#### Dereference Of Readline Value {#FB_NDORV}

The result of invoking readLine() is dereferenced without checking to see if the result is null. If there are no more lines of text to read, readLine() will return null and dereferencing that will generate a null pointer exception.

#### Doesnt Override Equals {#FB_EDOE}

This class extends a class that defines an equals method and adds fields, but doesn't define an equals method itself. Thus, equality on instances of this class will ignore the identity of the subclass and the added fields. Be sure this is what is intended, and that you don't need to override the equals method. Even if you don't need to override the equals method, consider overriding it anyway to document the fact that the equals method for the subclass just return the result of invoking super.equals(o).

#### Dont Just Null Check Readline {#FB_RDJNCR}

The value returned by readLine is discarded after checking to see if the return value is non-null. In almost all situations, if the result is non-null, you will want to use that non-null value. Calling readLine again will give you a different line.

#### Duplicate Branches {#FB_DDB}

This method uses the same code to implement two branches of a conditional branch. Check to ensure that this isn't a coding mistake.

#### Duplicate Switch Clauses {#FB_DDSC}

This method uses the same code to implement two clauses of a switch statement. This could be a case of duplicate code, but it might also indicate a coding mistake.

#### Explicit Unknown Source Value Reaches Always Sink {#FB_TEUSVRAS}

A value is used in a way that requires it to be always be a value denoted by a type qualifier, but there is an explicit annotation stating that it is not known where the value is required to have that type qualifier. Either the usage or the annotation is incorrect.

#### Explicit Unknown Source Value Reaches Never Sink {#FB_TEUSVRNS}

A value is used in a way that requires it to be never be a value denoted by a type qualifier, but there is an explicit annotation stating that it is not known where the value is prohibited from having that type qualifier. Either the usage or the annotation is incorrect.

#### Field Double Assignment {#FB_SFDA}

This method contains a double assignment of a field; e.g.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
int x,y;

public void foo() {
  x = x = 17;
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Assigning to a field twice is useless, and may indicate a logic error or typo.

#### Field Not Initialized In Constructor {#FB_UFNIIC}

This field is never initialized within any constructor, and is therefore could be null after the object is constructed. Elsewhere, it is loaded and dereferenced without a null check. This could be a either an error or a questionable design, since it means a null pointer exception will be generated if that field is dereferenced before being initialized.

#### Floating Point Equality {#FB_FFPE}

This operation compares two floating point values for equality. Because floating point calculations may involve rounding, calculated float and double values may not be accurate. For values that must be precise, such as monetary values, consider using a fixed-precision type such as BigDecimal. For values that need not be precise, consider comparing for equality within some range, for example: if ( Math.abs(x - y) \< .0000001 ). See the Java Language Specification, section 4.2.4.

#### Format String Bad Conversion To Boolean {#FB_VFSBCTB}

An argument not of type Boolean is being formatted with a %b format specifier. This won't throw an exception; instead, it will print true for any nonnull value, and false for null. This feature of format strings is strange, and may not be what you intended.

#### Hardcoded Absolute Filename {#FB_DHAF}

This code constructs a File object using a hard coded to an absolute pathname (e.g., new File("/home/dannyc/workspace/j2ee/src/share/com/sun/enterprise/deployment");

#### Idiv Cast To Double {#FB_IICTD}

This code casts the result of an integral division (e.g., int or long division) operation to double or float. Doing division on integers truncates the result to the integer value closest to zero. The fact that the result was cast to double suggests that this precision should have been retained. What was probably meant was to cast one or both of the operands to double ***before*** performing the division. Here is an example:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
int x = 2;
int y = 5;

// Wrong: yields result 0.0
double value1 = x / y;

// Right: yields result 0.4
double value2 = x / (double) y;
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Immediate Dereference Of Readline {#FB_NIDOR}

The result of invoking readLine() is immediately dereferenced. If there are no more lines of text to read, readLine() will return null and dereferencing that will generate a null pointer exception.

#### Init Circularity {#FB_IIC}

A circularity was detected in the static initializers of the two classes referenced by the bug instance.  Many kinds of unexpected behavior may arise from such circularity.

#### Integer Multiply Cast To Long {#FB_IIMCTL}

This code performs integer multiply and then converts the result to a long, as in:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
long convertDaysToMilliseconds(int days) { return 1000*3600*24*days; 
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If the multiplication is done using long arithmetic, you can avoid the possibility that the result will overflow. For example, you could fix the above code to:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
long convertDaysToMilliseconds(int days) { return 1000L*3600*24*days;
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

or

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
static final long MILLISECONDS_PER_DAY = 24L*3600*1000;

long convertDaysToMilliseconds(int days) { return days * MILLISECONDS_PER_DAY; }
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Load Of Known Null Value {#FB_NLOKNV}

The variable referenced at this point is known to be null due to an earlier check against null. Although this is valid, it might be a mistake (perhaps you intended to refer to a different variable, or perhaps the earlier check to see if the variable is null should have been a check to see if it was nonnull).

#### Local Double Assignment {#FB_SLDA}

This method contains a double assignment of a local variable; e.g.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public void foo() {
  int x,y;
  x = x = 17;
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Assigning the same value to a variable twice is useless, and may indicate a logic error or typo.

#### Local Self Assignment {#FB_SLSA}

This method contains a self assignment of a local variable; e.g.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
public void foo() {
  int x = 3;
  x = x;
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Such assignments are useless, and may indicate a logic error or typo.

#### Method Parameter Tightens Annotation {#FB_NMPTA}

A method should always implement the contract of a method it overrides. Thus, if a method takes a parameter that is marked as @Nullable, you shouldn't override that method in a subclass with a method where that parameter is @Nonnull. Doing so violates the contract that the method should handle a null parameter.

#### Method Return Relaxing Annotation {#FB_NMRRA}

A method should always implement the contract of a method it overrides. Thus, if a method takes is annotated as returning a @Nonnull value, you shouldn't override that method in a subclass with a method annotated as returning a @Nullable or @CheckForNull value. Doing so violates the contract that the method shouldn't return null.

#### Non Short Circuit {#FB_NNSC}

This code seems to be using non-short-circuit logic (e.g., & or |) rather than short-circuit logic (&& or ||). Non-short-circuit logic causes both sides of the expression to be evaluated even when the result can be inferred from knowing the left-hand side. This can be less efficient and can result in errors if the left-hand side guards cases when evaluating the right-hand side can generate an error.

See *the Java Language Specification* for details

#### Nonserializable Object Written {#FB_DNOW}

This code seems to be passing a non-serializable object to the ObjectOutput.writeObject method. If the object is, indeed, non-serializable, an error will result.

#### Null On Some Path From Return Value {#FB_NNOSPFRV}

The return value from a method is dereferenced without a null check, and the return value of that method is one that should generally be checked for null. This may lead to a NullPointerException when the code is executed.

#### Null On Some Path Might Be Infeasible {#FB_NNOSPMBI}

There is a branch of statement that, ***if executed,*** guarantees that a null value will be dereferenced, which would generate a NullPointerException when the code is executed. Of course, the problem might be that the branch or statement is infeasible and that the null pointer exception can't ever be executed; deciding that is beyond the ability of FindBugs. Due to the fact that this value had been previously tested for nullness, this is a definite possibility.

#### Parameter Must Be Nonnull But Marked As Nullable {#FB_NPMBNBMAN}

This parameter is always used in a way that requires it to be nonnull, but the parameter is explicitly annotated as being Nullable. Either the use of the parameter or the annotation is wrong.

#### Prefer Zero Length Arrays {#FB_PPZLA}

It is often a better design to return a length zero array rather than a null reference to indicate that there are no results (i.e., an empty list of results). This way, no explicit check for null is needed by clients of the method.

On the other hand, using null to indicate "there is no answer to this question" is probably appropriate. For example, File.listFiles() returns an empty list if given a directory containing no files, and returns null if the file is not a directory.

#### Private Read Resolve Not Inherited {#FB_SPRRNI}

This class defines a private readResolve method. Since it is private, it won't be inherited by subclasses. This might be intentional and OK, but should be reviewed to ensure it is what is intended.

#### Public Semaphores {#FB_PPS}

This class uses synchronization along with wait(), notify() or notifyAll() on itself (the this reference). Client classes that use this class, may, in addition, use an instance of this class as a synchronizing object. Because two classes are using the same object for synchronization, Multithread correctness is suspect. You should not synchronize nor call semaphore methods on a public reference. Consider using a internal private member variable to control synchronization.

#### Questionable For Loop {#FB_QQFL}

Are you sure this for loop is incrementing the correct variable? It appears that another variable is being initialized and checked by the for loop.

#### Questionable Unsigned Right Shift {#FB_IQURS}

The code performs an unsigned right shift, whose result is then cast to a short or byte, which discards the upper bits of the result. Since the upper bits are discarded, there may be no difference between a signed and unsigned right shift (depending upon the size of the shift).

#### Redundant Comparison Of Null And Nonnull Value {#FB_RRCONANV}

This method contains a reference known to be non-null with another reference known to be null.

#### Redundant Comparison Two Null Values {#FB_RRCTNV}

This method contains a redundant comparison of two references known to both be definitely null.

#### Redundant Interfaces {#FB_RRI}

This class declares that it implements an interface that is also implemented by a superclass. This is redundant because once a superclass implements an interface, all subclasses by default also implement this interface. It may point out that the inheritance hierarchy has changed since this class was created, and consideration should be given to the ownership of the interface's implementation.

#### Redundant Nullcheck Of Nonnull Value {#FB_RRNONV}

This method contains a redundant check of a known non-null value against the constant null.

#### Redundant Nullcheck Of Null Value {#FB_RcRNONV}

This method contains a redundant check of a known null value against the constant null.

#### Rem Of Hashcode {#FB_RROH}

This code computes a hashCode, and then computes the remainder of that value modulo another value. Since the hashCode can be negative, the result of the remainder operation can also be negative.

Assuming you want to ensure that the result of your computation is nonnegative, you may need to change your code. If you know the divisor is a power of 2, you can use a bitwise and operator instead (i.e., instead of using x.hashCode()%n, use x.hashCode()&(n-1). This is probably faster than computing the remainder as well. If you don't know that the divisor is a power of 2, take the absolute value of the result of the remainder operation (i.e., use Math.abs(x.hashCode()%n)

#### Rem Of Random Int {#FB_RRORI}

This code generates a random signed integer and then computes the remainder of that value modulo another value. Since the random number can be negative, the result of the remainder operation can also be negative. Be sure this is intended, and strongly consider using the Random.nextInt(int) method instead.

#### Return Value Ignored Inferred {#FB_RRVII}

This code calls a method and ignores the return value. The return value is the same type as the type the method is invoked on, and from our analysis it looks like the return value might be important (e.g., like ignoring the return value of String.toLowerCase()).

We are guessing that ignoring the return value might be a bad idea just from a simple analysis of the body of the method. You can use a @CheckReturnValue annotation to instruct FindBugs as to whether ignoring the return value of this method is important or acceptable.

Please investigate this closely to decide whether it is OK to ignore the return value.

#### Suspect Servlet Instance Field {#FB_MSSIF}

This class extends from a Servlet class, and uses an instance member variable. Since only one instance of a Servlet class is created by the J2EE framework, and used in a multithreaded way, this paradigm is highly discouraged and most likely problematic. Consider only using method local variables.

#### Suspect Struts Instance Field {#FB_MtSSIF}

This class extends from a Struts Action class, and uses an instance member variable. Since only one instance of a struts Action class is created by the Struts framework, and used in a multithreaded way, this paradigm is highly discouraged and most likely problematic. Consider only using method local variables. Only instance fields that are written outside of a monitor are reported.

#### Switch Fallthrough {#FB_MBIS}

This method contains a switch statement where one case branch will fall through to the next case. Usually you need to end this case with a break or return.

#### Switch No Default {#FB_DLNLISS}

This method contains a switch statement where default case is missing. Usually you need to provide a default case.

Because the analysis only looks at the generated bytecode, this warning can be incorrect triggered if the default case is at the end of the switch statement and doesn't end with a break statement.

#### Thread Passed Where Runnable Expected {#FB_DNUT}

A Thread object is passed as a parameter to a method where a Runnable is expected. This is rather unusual, and may indicate a logic error or cause unexpected behavior.

#### Transient Field Of Nonserializable Class {#FB_STFONC}

The field is marked as transient, but the class isn't Serializable, so marking it as transient has absolutely no effect. This may be leftover marking from a previous version of the code in which the class was transient, or it may indicate a misunderstanding of how serialization works.

#### Unconfirmed Cast {#FB_BUC}

This cast is unchecked, and not all instances of the type casted from can be cast to the type it is being cast to. Check that your program logic ensures that this cast will not fail.

#### Unconfirmed Cast Of Return Value {#FB_BUCORV}

This code performs an unchecked cast of the return value of a method. The code might be calling the method in such a way that the cast is guaranteed to be safe, but FindBugs is unable to verify that the cast is safe. Check that your program logic ensures that this cast will not fail.

#### Unread Public Or Protected Field {#FB_UUPOPF}

This field is never read.  The field is public or protected, so perhaps it is intended to be used with classes not seen as part of the analysis. If not, consider removing it from the class.

#### Unsupported Method {#FB_DUM}

All targets of this method invocation throw an UnsupportedOperationException.

#### Unused Public Or Protected Field {#FB_UuUPOPF}

This field is never used.  The field is public or protected, so perhaps it is intended to be used with classes not seen as part of the analysis. If not, consider removing it from the class.

#### Unusual {#FB_EU}

This class doesn't do any of the patterns we recognize for checking that the type of the argument is compatible with the type of the this object. There might not be anything wrong with this code, but it is worth reviewing.

#### Unwritten Public Or Protected Field {#FB_UwUPOPF}

No writes were seen to this public/protected field.  All reads of it will return the default value. Check for errors (should it have been initialized?), or remove it if it is useless.

#### Useless Control Flow {#FB_UUCF}

This method contains a useless control flow statement, where control flow continues onto the same place regardless of whether or not the branch is taken. For example, this is caused by having an empty statement block for an if statement:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
if (argv.length == 0) {
  // TODO: handle this case
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Useless Control Flow Next Line {#FB_UUCFNL}

This method contains a useless control flow statement in which control flow follows to the same or following line regardless of whether or not the branch is taken. Often, this is caused by inadvertently using an empty statement as the body of an if statement, e.g.:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
if (argv.length == 1);

System.out.println("Hello, " + argv[0]);
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Useless Substring {#FB_DUS}

This code invokes substring(0) on a String, which returns the original value.

#### Vacuous Bit Operation {#FB_IVBO}

This is an integer bit operation (and, or, or exclusive or) that doesn't do any useful work (e.g., v & 0xffffffff).

#### Vacuous Comparison {#FB_IVC}

There is an integer comparison that always returns the same value (e.g., x \<= Integer.MAX\_VALUE).

#### Vacuous Instanceof {#FB_BVI}

This instanceof test will always return true (unless the value being tested is null). Although this is safe, make sure it isn't an indication of some misunderstanding or some other logic error. If you really want to test the value for being null, perhaps it would be clearer to do better to do a null test rather than an instanceof test.

#### Write To Static From Instance Method {#FB_SWTSFIM}

This instance method writes to a static field. This is tricky to get correct if multiple instances are being manipulated, and generally bad practice.

#### Xml Factory Bypass {#FB_XXFB}

This method allocates a specific implementation of an xml interface. It is preferable to use the supplied factory classes to create these objects so that the implementation can be changed at runtime. See

- javax.xml.parsers.DocumentBuilderFactory

- javax.xml.parsers.SAXParserFactory

- javax.xml.transform.TransformerFactory

- org.w3c.dom.Document.create*XXXX*

for details.

### Internationalization Rules

#### Convert Case {#FB_ULWCC}

A String is being converted to upper or lowercase, using the platform's default encoding. This may result in improper conversions when used with international characters. Use the

- String.toUpperCase( Locale l )

- String.toLowerCase( Locale l )

versions instead.

#### Default Encoding {#FB_DDE}

Found a call to a method which will perform a byte to String (or String to byte) conversion, and will assume that the default platform encoding is suitable. This will cause the application behaviour to vary between platforms. Use an alternative API and specify a charset name or Charset object explicitly.

### Multithreaded Correctness Rules

#### Await Not In Loop {#FB_WANIL}

This method contains a call to java.util.concurrent.await() (or variants) which is not in a loop.  If the object is used for multiple conditions, the condition the caller intended to wait for might not be the one that actually occurred.

#### Doublecheck {#FB_DCL}

This method may contain an instance of double-checked locking.  This idiom is not correct according to the semantics of the Java memory model. For more information, see the web page [http://www.cs.umd.edu/\~pugh/java/memoryModel/DoubleCheckedLocking.html]

[http://www.cs.umd.edu/\~pugh/java/memoryModel/DoubleCheckedLocking.html]:http://www.cs.umd.edu/\~pugh/java/memoryModel/DoubleCheckedLocking.html

#### Empty Sync {#FB_ESB}

The code contains an empty synchronized block:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
synchronized() {}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Empty synchronized blocks are far more subtle and hard to use correctly than most people recognize, and empty synchronized blocks are almost never a better solution than less contrived solutions.

#### Field Not Guarded {#FB_IFNG}

This field is annotated with net.jcip.annotations.GuardedBy or javax.annotation.concurrent.GuardedBy, but can be accessed in a way that seems to violate those annotations.

#### Inconsistent Sync {#FB_IIS}

The fields of this class appear to be accessed inconsistently with respect to synchronization.  This bug report indicates that the bug pattern detector judged that

- The class contains a mix of locked and unlocked accesses,

- The class is **not** annotated as javax.annotation.concurrent.NotThreadSafe,

- At least one locked access was performed by one of the class's own methods, and

- The number of unsynchronized field accesses (reads and writes) was no more than one third of all accesses, with writes being weighed twice as high as reads

A typical bug matching this bug pattern is forgetting to synchronize one of the methods in a class that is intended to be thread-safe.

You can select the nodes labeled "Unsynchronized access" to show the code locations where the detector believed that a field was accessed without synchronization.

Note that there are various sources of inaccuracy in this detector; for example, the detector cannot statically detect all situations in which a lock is held.  Also, even when the detector is accurate in distinguishing locked vs. unlocked accesses, the code in question may still be correct.

#### Invoke On Static Calendar Instance {#FB_SIOSCI}

Even though the JavaDoc does not contain a hint about it, Calendars are inherently unsafe for multihtreaded use. The detector has found a call to an instance of Calendar that has been obtained via a static field. This looks suspicous.

For more information on this see *Sun Bug \#6231579* and *Sun Bug \#6178997*.

#### Invoke On Static Date Format Instance {#FB_SIOSDFI}

As the JavaDoc states, DateFormats are inherently unsafe for multithreaded use. The detector has found a call to an instance of DateFormat that has been obtained via a static field. This looks suspicous.

For more information on this see *Sun Bug \#6231579* and *Sun Bug \#6178997*.

#### Invoke Run {#FB_DCTR}

This method explicitly invokes run() on an object.  In general, classes implement the Runnable interface because they are going to have their run() method invoked in a new thread, in which case Thread.start() is the right method to call.

#### Jsr166 Calling Wait Rather Than Await {#FB_JJCWRTA}

This method calls wait(), notify() or notifyAll()() on an object that also provides an await(), signal(), signalAll() method (such as util.concurrent Condition objects). This probably isn't what you want, and even if you do want it, you should consider changing your design, as other developers will find it exceptionally confusing.

#### Jsr166 Lock Monitorenter {#FB_JJLM}

This method performs synchronization an object that implements java.util.concurrent.locks.Lock. Such an object is locked/unlocked using acquire()/release() rather than using the synchronized (...) construct.

#### Jsr166 Utilconcurrent Monitorenter {#FB_JJUM}

This method performs synchronization an object that is an instance of a class from the java.util.concurrent package (or its subclasses). Instances of these classes have their own concurrency control mechanisms that are orthogonal to the synchronization provided by the Java keyword synchronized. For example, synchronizing on an AtomicBoolean will not prevent other threads from modifying the AtomicBoolean.

Such code may be correct, but should be carefully reviewed and documented, and may confuse people who have to maintain the code at a later date.

#### Lazy Init Static {#FB_LLIS}

This method contains an unsynchronized lazy initialization of a non-volatile static field. Because the compiler or processor may reorder instructions, threads are not guaranteed to see a completely initialized object, ***if the method can be called by multiple threads***. You can make the field volatile to correct the problem. For more information, see the *Java Memory Model web site*.

#### Lazy Init Update Static {#FB_LLIUS}

This method contains an unsynchronized lazy initialization of a static field. After the field is set, the object stored into that location is further updated or accessed. The setting of the field is visible to other threads as soon as it is set. If the futher accesses in the method that set the field serve to initialize the object, then you have a ***very serious*** multithreading bug, unless something else prevents any other thread from accessing the stored object until it is fully initialized.

Even if you feel confident that the method is never called by multiple threads, it might be better to not set the static field until the value you are setting it to is fully populated/initialized.

#### Mismatched Notify {#FB_MMN}

This method calls Object.notify() or Object.notifyAll() without obviously holding a lock on the object.  Calling notify() or notifyAll() without a lock held will result in an IllegalMonitorStateException being thrown.

#### Mismatched Wait {#FB_MMW}

This method calls Object.wait() without obviously holding a lock on the object.  Calling wait() without a lock held will result in an IllegalMonitorStateException being thrown.

#### Monitor Wait On Condition {#FB_DMWOC}

This method calls wait() on a java.util.concurrent.locks.Condition object.  Waiting for a Condition should be done using one of the await() methods defined by the Condition interface.

#### Mutable Servlet Field {#FB_MMSF}

A web server generally only creates one instance of servlet or jsp class (i.e., treats the class as a Singleton), and will have multiple threads invoke methods on that instance to service multiple simultaneous requests. Thus, having a mutable instance field generally creates race conditions.

#### Naked Notify {#FB_NNN}

A call to notify() or notifyAll() was made without any (apparent) accompanying modification to mutable object state.  In general, calling a notify method on a monitor is done because some condition another thread is waiting for has become true.  However, for the condition to be meaningful, it must involve a heap object that is visible to both threads.

This bug does not necessarily indicate an error, since the change to mutable object state may have taken place in a method which then called the method containing the notification.

#### Not In Loop {#FB_WNIL}

This method contains a call to java.lang.Object.wait() which is not in a loop.  If the monitor is used for multiple conditions, the condition the caller intended to wait for might not be the one that actually occurred.

#### Notify Not Notifyall {#FB_NNNN}

This method calls notify() rather than notifyAll().  Java monitors are often used for multiple conditions.  Calling notify() only wakes up one thread, meaning that the thread woken up might not be the one waiting for the condition that the caller just satisfied.

#### Operation Sequence On Concurrent Abstraction {#FB_AOSOCA}

This code contains a sequence of calls to a concurrent abstraction (such as a concurrent hash map). These calls will not be executed atomically.

#### Readobject Sync {#FB_RRS}

This serializable class defines a readObject() which is synchronized.  By definition, an object created by deserialization is only reachable by one thread, and thus there is no need for readObject() to be synchronized.  If the readObject() method itself is causing the object to become visible to another thread, that is an example of very dubious coding style.

#### Return Value Of Putifabsent Ignored {#FB_RRVOPI}

The putIfAbsent method is typically used to ensure that a single value is associated with a given key (the first value for which put if absent succeeds). If you ignore the return value and retain a reference to the value passed in, you run the risk of retaining a value that is not the one that is associated with the key in the map. If it matters which one you use and you use the one that isn't stored in the map, your program will behave incorrectly.

#### Sleep With Lock Held {#FB_SSWLH}

This method calls Thread.sleep() with a lock held. This may result in very poor performance and scalability, or a deadlock, since other threads may be waiting to acquire the lock. It is a much better idea to call wait() on the lock, which releases the lock and allows other threads to run.

#### Spin On Field {#FB_SSOF}

This method spins in a loop which reads a field.  The compiler may legally hoist the read out of the loop, turning the code into an infinite loop.  The class should be changed so it uses proper synchronization (including wait and notify calls).

#### Start In Ctor {#FB_SSIC}

The constructor starts a thread. This is likely to be wrong if the class is ever extended/subclassed, since the thread will be started before the subclass constructor is started.

#### Static Calendar Instance {#FB_SSCI}

Even though the JavaDoc does not contain a hint about it, Calendars are inherently unsafe for multihtreaded use. Sharing a single instance across thread boundaries without proper synchronization will result in erratic behavior of the application. Under 1.4 problems seem to surface less often than under Java 5 where you will probably see random ArrayIndexOutOfBoundsExceptions or IndexOutOfBoundsExceptions in sun.util.calendar.BaseCalendar.getCalendarDateFromFixedDate().

You may also experience serialization problems.

Using an instance field is recommended.

For more information on this see *Sun Bug \#6231579* and *Sun Bug \#6178997*.

#### Static Simple Date Format Instance {#FB_SSSDFI}

As the JavaDoc states, DateFormats are inherently unsafe for multithreaded use. Sharing a single instance across thread boundaries without proper synchronization will result in erratic behavior of the application.

You may also experience serialization problems.

Using an instance field is recommended.

For more information on this see *Sun Bug \#6231579* and *Sun Bug \#6178997*.

#### Sync And Null Check Field {#FB_NSANCF}

Since the field is synchronized on, it seems not likely to be null. If it is null and then synchronized on a NullPointerException will be thrown and the check would be pointless. Better to synchronize on another field.

#### Sync On Field To Guard Changing That Field {#FB_MSOFTGCTF}

This method synchronizes on a field in what appears to be an attempt to guard against simultaneous updates to that field. But guarding a field gets a lock on the referenced object, not on the field. This may not provide the mutual exclusion you need, and other threads might be obtaining locks on the referenced objects (for other purposes). An example of this pattern would be:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
private Long myNtfSeqNbrCounter = new Long(0);

private Long getNotificationSequenceNumber() {
  Long result = null;
  synchronized(myNtfSeqNbrCounter) {
    result = new Long(myNtfSeqNbrCounter.longValue() + 1);
    myNtfSeqNbrCounter = new Long(result.longValue());
  }
  return result;
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Sync On Updated Field {#FB_MSOUF}

This method synchronizes on an object referenced from a mutable field. This is unlikely to have useful semantics, since different threads may be synchronizing on different objects.

#### Sync Set Unsync Get {#FB_USSUG}

This class contains similarly-named get and set methods where the set method is synchronized and the get method is not.  This may result in incorrect behavior at runtime, as callers of the get method will not necessarily see a consistent state for the object. The get method should be made synchronized.

#### Synchronization On Boolean {#FB_DSOB}

The code synchronizes on a boxed primitive constant, such as an Boolean.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
private static Boolean inited = Boolean.FALSE;
...
synchronized(inited) {
  if (!inited) {
    init();
    inited = Boolean.TRUE;
  }
}
...
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Since there normally exist only two Boolean objects, this code could be synchronizing on the same object as other, unrelated code, leading to unresponsiveness and possible deadlock

See CERT *CON08-J. Do not synchronize on objects that may be reused* for more information.

#### Synchronization On Boxed Primitive {#FB_DSOBP}

The code synchronizes on a boxed primitive constant, such as an Integer.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
private static Integer count = 0;
...
synchronized(count) {
  count++;
}
...
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Since Integer objects can be cached and shared, this code could be synchronizing on the same object as other, unrelated code, leading to unresponsiveness and possible deadlock

See CERT *CON08-J. Do not synchronize on objects that may be reused* for more information.

#### Synchronization On Shared Constant {#FB_DSOSC}

The code synchronizes on interned String.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
private static String LOCK = "LOCK";

...

synchronized(LOCK) { ...}

...
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Constant Strings are interned and shared across all other classes loaded by the JVM. Thus, this could is locking on something that other code might also be locking. This could result in very strange and hard to diagnose blocking and deadlock behavior. See [http://www.javalobby.org/java/forums/t96352.html] and [http://jira.codehaus.org/browse/JETTY-352].

[http://www.javalobby.org/java/forums/t96352.html]:http://www.javalobby.org/java/forums/t96352.html
[http://jira.codehaus.org/browse/JETTY-352]:http://jira.codehaus.org/browse/JETTY-352

See CERT *CON08-J. Do not synchronize on objects that may be reused* for more information.

#### Synchronization On Unshared Boxed Primitive {#FB_DSOUBP}

The code synchronizes on an apparently unshared boxed primitive, such as an Integer.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
private static final Integer fileLock = new Integer(1);

...

synchronized(fileLock) {

.. do something ..

}

...
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

It would be much better, in this code, to redeclare fileLock as

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
private static final Object fileLock = new Object();
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The existing code might be OK, but it is confusing and a future refactoring, such as the "Remove Boxing" refactoring in IntelliJ, might replace this with the use of an interned Integer object shared throughout the JVM, leading to very confusing behavior and potential deadlock.

#### Two Lock Wait {#FB_TTLW}

Waiting on a monitor while two locks are held may cause deadlock. Performing a wait only releases the lock on the object being waited on, not any other locks. This not necessarily a bug, but is worth examining closely.

#### Uncond Wait {#FB_UUW}

This method contains a call to java.lang.Object.wait() which is not guarded by conditional control flow.  The code should verify that condition it intends to wait for is not already satisfied before calling wait; any previous notifications will be ignored.

#### Unreleased Lock {#FB_UUL}

This method acquires a JSR-166 (java.util.concurrent) lock, but does not release it on all paths out of the method. In general, the correct idiom for using a JSR-166 lock is:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
Lock l = ...;
l.lock();
try {
  // do something
} finally {
  l.unlock();
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Unreleased Lock Exception Path {#FB_UULEP}

This method acquires a JSR-166 (java.util.concurrent) lock, but does not release it on all exception paths out of the method. In general, the correct idiom for using a JSR-166 lock is:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
Lock l = ...;
l.lock();
try {
  // do something
} finally {
  l.unlock();
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Useless Thread {#FB_DUT}

This method creates a thread without specifying a run method either by deriving from the Thread class, or by passing a Runnable object. This thread, then, does nothing but waste time.

#### Using Getclass Rather Than Class Literal {#FB_WUGRTCL}

This instance method synchronizes on this.getClass(). If this class is subclassed, subclasses will synchronize on the class object for the subclass, which isn't likely what was intended. For example, consider this code from java.awt.Label:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
private static final String base = "label";
private static int nameCounter = 0;

String constructComponentName() {
  synchronized (getClass()) {
    return base + nameCounter++;
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Subclasses of Label won't synchronize on the same subclass, giving rise to a datarace. Instead, this code should be synchronizing on Label.class

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
private static final String base = "label";
private static int nameCounter = 0;

String constructComponentName() {
  synchronized (Label.class) {
    return base + nameCounter++;
  }
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Bug pattern contributed by Jason Mehrens

#### Volatile Increment {#FB_VVI}

This code increments a volatile field. Increments of volatile fields aren't atomic. If more than one thread is incrementing the field at the same time, increments could be lost.

#### Volatile Reference To Array {#FB_VVRTA}

This declares a volatile reference to an array, which might not be what you want. With a volatile reference to an array, reads and writes of the reference to the array are treated as volatile, but the array elements are non-volatile. To get volatile array elements, you will need to use one of the atomic array classes in java.util.concurrent (provided in Java 5.0).

#### Writeobject Sync {#FB_WWS}

This class has a writeObject() method which is synchronized; however, no other method of the class is synchronized.

### Optimization Rules

#### Blocking Methods On Url {#FB_DBMOU}

The equals and hashCode method of URL perform domain name resolution, this can result in a big performance hit. See [http://michaelscharf.blogspot.com/2006/11/javaneturlequals-and-hashcode-make.html] for more information. Consider using java.net.URI instead.

[http://michaelscharf.blogspot.com/2006/11/javaneturlequals-and-hashcode-make.html]:http://michaelscharf.blogspot.com/2006/11/javaneturlequals-and-hashcode-make.html

#### Boolean Ctor {#FB_DBC}

Creating new instances of java.lang.Boolean wastes memory, since Boolean objects are immutable and there are only two useful values of this type.  Use the Boolean.valueOf() method (or Java 1.5 autoboxing) to create Boolean objects instead.

#### Boxed Primitive For Parsing {#FB_DBPFP}

A boxed primitive is created from a String, just to extract the unboxed primitive value. It is more efficient to just call the static parseXXX method.

#### Boxed Primitive Tostring {#FB_DBPT}

A boxed primitive is allocated just to call toString(). It is more effective to just use the static form of toString which takes the primitive value. So,

  **Replace...**                 **With this...**
  ------------------------------ ------------------------
  new Integer(1).toString()      Integer.toString(1)
  new Long(1).toString()         Long.toString(1)
  new Float(1.0).toString()      Float.toString(1.0)
  new Double(1.0).toString()     Double.toString(1.0)
  new Byte(1).toString()         Byte.toString(1)
  new Short(1).toString()        Short.toString(1)
  new Boolean(true).toString()   Boolean.toString(true)

#### Boxing Immediately Unboxed {#FB_BBIU}

A primitive is boxed, and then immediately unboxed. This probably is due to a manual boxing in a place where an unboxed value is required, thus forcing the compiler to immediately undo the work of the boxing.

#### Boxing Immediately Unboxed To Perform Coercion {#FB_BBIUTPC}

A primitive boxed value constructed and then immediately converted into a different primitive type (e.g., new Double(d).intValue()). Just perform direct primitive coercion (e.g., (int) d).

#### Collection Of Urls {#FB_DCOU}

This method or field is or uses a Map or Set of URLs. Since both the equals and hashCode method of URL perform domain name resolution, this can result in a big performance hit. See [http://michaelscharf.blogspot.com/2006/11/javaneturlequals-and-hashcode-make.html] for more information. Consider using java.net.URI instead.

#### Fp Number Ctor {#FB_DFNC}

Using new Double(double) is guaranteed to always result in a new object whereas Double.valueOf(double) allows caching of values to be done by the compiler, class library, or JVM. Using of cached values avoids object allocation and the code will be faster.

Unless the class must be compatible with JVMs predating Java 1.5, use either autoboxing or the valueOf() method when creating instances of Double and Float.

#### Gc {#FB_DNCGCE}

Code explicitly invokes garbage collection. Except for specific use in benchmarking, this is very dubious.

In the past, situations where people have explicitly invoked the garbage collector in routines such as close or finalize methods has led to huge performance black holes. Garbage collection can be expensive. Any situation that forces hundreds or thousands of garbage collections will bring the machine to a crawl.

#### Huge Shared String Constant {#FB_HHSSC}

A large String constant is duplicated across multiple class files. This is likely because a final field is initialized to a String constant, and the Java language mandates that all references to a final field from other classes be inlined into that classfile. See *JDK bug 6447475* for a description of an occurrence of this bug in the JDK and how resolving it reduced the size of the JDK by 1 megabyte.

#### Inefficient Index Of {#FB_IIIO}

This code passes a constant string of length 1 to String.indexOf(). It is more efficient to use the integer implementations of String.indexOf(). f. e. call myString.indexOf('.') instead of myString.indexOf(".")

#### Inefficient Last Index Of {#FB_IILIO}

This code passes a constant string of length 1 to String.lastIndexOf(). It is more efficient to use the integer implementations of String.lastIndexOf(). f. e. call myString.lastIndexOf('.') instead of myString.lastIndexOf(".")

#### Inefficient To Array {#FB_OTAC}

This method uses the toArray() method of a collection derived class, and passes in a zero-length prototype array argument. It is more efficient to use myCollection.toArray(new Foo[myCollection.size()]) If the array passed in is big enough to store all of the elements of the collection, then it is populated and returned directly. This avoids the need to create a second array (by reflection) to return as the result.

#### Inner Should Be Static {#FB_SISBS}

This class is an inner class, but does not use its embedded reference to the object which created it.  This reference makes the instances of the class larger, and may keep the reference to the creator object alive longer than necessary.  If possible, the class should be made static.

#### Inner Should Be Static Anon {#FB_SISBSA}

This class is an inner class, but does not use its embedded reference to the object which created it.  This reference makes the instances of the class larger, and may keep the reference to the creator object alive longer than necessary.  If possible, the class should be made into a ***static*** inner class. Since anonymous inner classes cannot be marked as static, doing this will require refactoring the inner class so that it is a named inner class.

#### Inner Should Be Static Needs This {#FB_SISBSNT}

This class is an inner class, but does not use its embedded reference to the object which created it except during construction of the inner object.  This reference makes the instances of the class larger, and may keep the reference to the creator object alive longer than necessary.  If possible, the class should be made into a ***static*** inner class. Since the reference to the outer object is required during construction of the inner instance, the inner class will need to be refactored so as to pass a reference to the outer instance to the constructor for the inner class.

#### New For Getclass {#FB_ITGC}

This method allocates an object just to call getClass() on it, in order to retrieve the Class object for it. It is simpler to just access the .class property of the class.

#### Nextint Via Nextdouble {#FB_DNVN}

If r is a java.util.Random, you can generate a random number from 0 to n-1 using r.nextInt(n), rather than using (int)(r.nextDouble() \* n).

The argument to nextInt must be positive. If, for example, you want to generate a random value from -99 to 0, use -r.nextInt(100).

#### Number Ctor {#FB_UWOC}

Using new Integer(int) is guaranteed to always result in a new object whereas Integer.valueOf(int) allows caching of values to be done by the compiler, class library, or JVM. Using of cached values avoids object allocation and the code will be faster.

Values between -128 and 127 are guaranteed to have corresponding cached instances and using valueOf is approximately 3.5 times faster than using constructor. For values outside the constant range the performance of both styles is the same.

Unless the class must be compatible with JVMs predating Java 1.5, use either autoboxing or the valueOf() method when creating instances of Long, Integer, Short, Character, and Byte.

#### Should Be Static {#FB_SSBS}

This class contains an instance final field that is initialized to a compile-time static value. Consider making the field static.

#### String Ctor {#FB_DSC}

Using the java.lang.String(String) constructor wastes memory because the object so constructed will be functionally indistinguishable from the String passed as a parameter.  Just use the argument String directly.

#### String Tostring {#FB_STS}

Calling String.toString() is just a redundant operation. Just use the String.

#### String Void Ctor {#FB_DSVC}

Creating a new java.lang.String object using the no-argument constructor wastes memory because the object so created will be functionally indistinguishable from the empty string constant "".  Java guarantees that identical string constants will be represented by the same String object.  Therefore, you should just use the empty string constant directly.

#### Unboxing Immediately Reboxed {#FB_BUIR}

A boxed value is unboxed and then immediately reboxed.

#### Uncalled Private Method {#FB_UUPM}

This private method is never called. Although it is possible that the method will be invoked through reflection, it is more likely that the method is never used, and should be removed.

#### Unnecessary Math {#FB_UUM}

This method uses a static method from java.lang.Math on a constant value. This method's result in this case, can be determined statically, and is faster and sometimes more accurate to just use the constant. Methods detected are:

  **Method**   **Parameter**
  ------------ ---------------
  abs          -any-
  acos         0.0 or 1.0
  asin         0.0 or 1.0
  atan         0.0 or 1.0
  atan2        0.0
  cbrt         0.0 or 1.0
  ceil         -any-
  cos          0.0
  cosh         0.0
  exp          0.0 or 1.0
  expm1        0.0
  floor        -any-
  log          0.0 or 1.0
  log10        0.0 or 1.0
  rint         -any-
  round        -any-
  sin          0.0
  sinh         0.0
  sqrt         0.0 or 1.0
  tan          0.0
  tanh         0.0
  toDegrees    0.0 or 1.0
  toRadians    0.0

#### Unread Field {#FB_UUF}

This field is never read. Consider removing it from the class.

#### Unused Field {#FB_UuUF}

This field is never used. Consider removing it from the class.

#### Use Stringbuffer Concatenation {#FB_USBFSA}

The method seems to be building a String using concatenation in a loop. In each iteration, the String is converted to a StringBuffer/StringBuilder, appended to, and converted back to a String. This can lead to a cost quadratic in the number of iterations, as the growing string is recopied in each iteration.

Better performance can be obtained by using a StringBuffer (or StringBuilder in Java 1.5) explicitly.

For example:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ {.java}
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
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Wrong Map Iterator {#FB_WWMI}

This method accesses the value of a Map entry, using a key that was retrieved from a keySet iterator. It is more efficient to use an iterator on the entrySet of the map, to avoid the Map.get(key) lookup.

### Security Code Guideline Rules

#### Cannot Be Final {#FB_MCBF}

A mutable static field could be changed by malicious code or by accident from another package. Unfortunately, the way the field is used doesn't allow any easy fix to this problem.

#### Create Classloader Inside Do Privileged {#FB_DCCIDP}

This code creates a classloader, which needs permission if a security manage is installed. If this code might be invoked by code that does not have security permissions, then the classloader creation needs to occur inside a doPrivileged block.

#### Do Inside Do Privileged {#FB_DDIDP}

This code invokes a method that requires a security permission check. If this code will be granted security permissions, but might be invoked by code that does not have security permissions, then the invocation needs to occur inside a doPrivileged block.

#### Expose Rep {#FB_MRIA}

A public static method returns a reference to an array that is part of the static state of the class. Any code that calls this method can freely modify the underlying array. One fix is to return a copy of the array.

#### Expose Rep2 {#FB_EiER}

This code stores a reference to an externally mutable object into the internal representation of the object.  If instances are accessed by untrusted code, and unchecked changes to the mutable object would compromise security or other important properties, you will need to do something different. Storing a copy of the object is better approach in many situations.

#### Expose Static Rep2 {#FB_EESR}

This code stores a reference to an externally mutable object into a static field. If unchecked changes to the mutable object would compromise security or other important properties, you will need to do something different. Storing a copy of the object is better approach in many situations.

#### Final Pkgprotect {#FB_MFP}

A mutable static field could be changed by malicious code or by accident from another package. The field could be made package protected and/or made final to avoid this vulnerability.

#### Mutable Array {#FB_MMA}

A final static field references an array and can be accessed by malicious code or by accident from another package. This code can freely modify the contents of the array.

#### Mutable Hashtable {#FB_MMH}

A final static field references a Hashtable and can be accessed by malicious code or by accident from another package. This code can freely modify the contents of the Hashtable.

#### Ooi Pkgprotect {#FB_MOP}

A final static field that is defined in an interface references a mutable object such as an array or hashtable. This mutable object could be changed by malicious code or by accident from another package. To solve this, the field needs to be moved to a class and made package protected to avoid this vulnerability.

#### Pkgprotect {#FB_MP}

A mutable static field could be changed by malicious code or by accident. The field could be made package protected to avoid this vulnerability.

#### Public Should Be Protected {#FB_FSBP}

A class's finalize() method should have protected access, not public.

#### Should Be Final {#FB_MSBF}

This static field public but not final, and could be changed by malicious code or by accident from another package. The field could be made final to avoid this vulnerability.

#### Should Be Refactored To Be Final {#FB_MSBRTBF}

This static field public but not final, and could be changed by malicious code or by accident from another package. The field could be made final to avoid this vulnerability. However, the static initializer contains more than one write to the field, so doing so will require some refactoring.

### Vulnerability Rules

#### Absolute Path Traversal {#FB_PAPT}

The software uses an HTTP request parameter to construct a pathname that should be within a restricted directory, but it does not properly neutralize absolute path sequences such as "/abs/path" that can resolve to a location that is outside of that directory. See [http://cwe.mitre.org/data/definitions/36.html] for more information.

[http://cwe.mitre.org/data/definitions/36.html]:http://cwe.mitre.org/data/definitions/36.html

FindBugs looks only for the most blatant, obvious cases of absolute path traversal. If FindBugs found ***any***, you ***almost certainly*** have more vulnerabilities that FindBugs doesn't report. If you are concerned about absolute path traversal, you should seriously consider using a commercial static analysis or pen-testing tool.

#### Constant Db Password {#FB_DCDP}

This code creates a database connect using a hardcoded, constant password. Anyone with access to either the source code or the compiled code can easily learn the password.

#### Empty Db Password {#FB_DEDP}

This code creates a database connect using a blank or empty password. This indicates that the database is not protected by a password.

#### Nonconstant String Passed To Execute {#FB_SNSPTE}

The method invokes the execute method on an SQL statement with a String that seems to be dynamically generated. Consider using a prepared statement instead. It is more efficient and less vulnerable to SQL injection attacks.

#### Prepared Statement Generated From Nonconstant String {#FB_SPSGFNS}

The code creates an SQL prepared statement from a nonconstant String. If unchecked, tainted data from a user is used in building this String, SQL injection could be used to make the prepared statement do something unexpected and undesirable.

#### Relative Path Traversal {#FB_PRPT}

The software uses an HTTP request parameter to construct a pathname that should be within a restricted directory, but it does not properly neutralize sequences such as ".." that can resolve to a location that is outside of that directory. See [http://cwe.mitre.org/data/definitions/23.html] for more information.

[http://cwe.mitre.org/data/definitions/23.html]:http://cwe.mitre.org/data/definitions/23.html

FindBugs looks only for the most blatant, obvious cases of relative path traversal. If FindBugs found ***any***, you ***almost certainly*** have more vulnerabilities that FindBugs doesn't report. If you are concerned about relative path traversal, you should seriously consider using a commercial static analysis or pen-testing tool.

#### Request Parameter To Cookie {#FB_HRPTC}

This code constructs an HTTP Cookie using an untrusted HTTP parameter. If this cookie is added to an HTTP response, it will allow a HTTP response splitting vulnerability. See *[http://en.wikipedia.org/wiki/HTTP\_response\_splitting]* for more information.

[http://en.wikipedia.org/wiki/HTTP\_response\_splitting]:http://en.wikipedia.org/wiki/HTTP\_response\_splitting

FindBugs looks only for the most blatant, obvious cases of HTTP response splitting. If FindBugs found ***any***, you ***almost certainly*** have more vulnerabilities that FindBugs doesn't report. If you are concerned about HTTP response splitting, you should seriously consider using a commercial static analysis or pen-testing tool.

#### Request Parameter To Http Header {#FB_HRPTHH}

This code directly writes an HTTP parameter to an HTTP header, which allows for a HTTP response splitting vulnerability. See [http://en.wikipedia.org/wiki/HTTP\_response\_splitting] for more information.

FindBugs looks only for the most blatant, obvious cases of HTTP response splitting. If FindBugs found ***any***, you ***almost certainly*** have more vulnerabilities that FindBugs doesn't report. If you are concerned about HTTP response splitting, you should seriously consider using a commercial static analysis or pen-testing tool.

#### Request Parameter To Jsp Writer {#FB_XRPTJW}

This code directly writes an HTTP parameter to JSP output, which allows for a cross site scripting vulnerability. See [http://en.wikipedia.org/wiki/Cross-site\_scripting] for more information.

[http://en.wikipedia.org/wiki/Cross-site\_scripting]:http://en.wikipedia.org/wiki/Cross-site\_scripting

FindBugs looks only for the most blatant, obvious cases of cross site scripting. If FindBugs found ***any***, you ***almost certainly*** have more cross site scripting vulnerabilities that FindBugs doesn't report. If you are concerned about cross site scripting, you should seriously consider using a commercial static analysis or pen-testing tool.

#### Request Parameter To Send Error {#FB_XRPTSE}

This code directly writes an HTTP parameter to a Server error page (using HttpServletResponse.sendError). Echoing this untrusted input allows for a reflected cross site scripting vulnerability. See [http://en.wikipedia.org/wiki/Cross-site\_scripting] for more information.

FindBugs looks only for the most blatant, obvious cases of cross site scripting. If FindBugs found ***any***, you ***almost certainly*** have more cross site scripting vulnerabilities that FindBugs doesn't report. If you are concerned about cross site scripting, you should seriously consider using a commercial static analysis or pen-testing tool.

#### Request Parameter To Servlet Writer {#FB_XRPTSW}

This code directly writes an HTTP parameter to Servlet output, which allows for a reflected cross site scripting vulnerability. See [http://en.wikipedia.org/wiki/Cross-site\_scripting] for more information.

FindBugs looks only for the most blatant, obvious cases of cross site scripting. If FindBugs found ***any***, you ***almost certainly*** have more cross site scripting vulnerabilities that FindBugs doesn't report. If you are concerned about cross site scripting, you should seriously consider using a commercial static analysis or pen-testing tool.

