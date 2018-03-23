## Reference of FxCop coding rule violations

OpenStaticAnalyzer incorporates the [FxCop] tool for coding rule violation checking and imports its results. OpenStaticAnalyzer also associates the issued rule violations with source code elements (i.e. methods, classes, namespaces, and components), and calculates metrics for the source code elements, which represent the amount of violations of each ruleset, rule, and priority groups, respectively.

OpenStaticAnalyzer uses FxCop "as is", without any guaranties that the results of FxCop are correct. All statements of the FxCop license apply here as well. All texts describing the rulesets and the individual rules are copied from the documentation of FxCop.

OpenStaticAnalyzer supports the rulesets of FxCop included with Visual Studio 2015 Enterprise edition. Older versions contain less rules, so in such cases the newer rules will not appear in OpenStaticAnalyzer's results. In case of using a newer version of FxCop, the eventual new rules will not be included.

[FxCop]:https://msdn.microsoft.com/en-us/library/bb429476%28v=vs.80%29.aspx

The list of rulesets and rules contained in each ruleset are the following:

- **Design Warnings:** Support adherence to the .NET Framework Design Guidelines.

- **Globalization Warnings:** Support world-ready libraries and applications.

- **Interoperability Warnings:** Support interacting with COM clients.

- **Maintainability  Warnings:** Maintainability warnings support library and application maintenance.

- **Mobility Warnings:** Mobility warnings support efficient power usage.

- **Naming Warnings:** Support adherence to the naming conventions of the .NET Framework Design Guidelines.

- **Performance Warnings:** Support high performance libraries and applications.

- **Portability Warnings:** Portability warnings support portability across different operating systems.

- **Reliability Warnings:** Reliability warnings support library and application reliability, such as correct memory and thread usage.

- **Security Warnings:** Support safer libraries and applications.

- **Usage Warnings:** Support proper usage of the .NET Framework.

The following table contains the enabled rules and their priorities:


  Category                             Name                                                                                                            Abbreviation       Prio.
  ------------------------------------ --------------------------------------------------------------------------------------------------------------- ------------------ --------
  ASP.NET.MVC.Security Rules           [ControllerActionShouldValidateInput](#FXCOP_CASVI)                                                             FXCOP_CASVI        Major    
                                       [MarkVerbHandlersWithValidateAntiforgeryToken](#FXCOP_MVHWVAT)                                                  FXCOP_MVHWVAT      Major    
  ASP.NET.Security Rules               [EnableEventValidationShouldBeTrue](#FXCOP_EEVSBT)                                                              FXCOP_EEVSBT       Major    
                                       [EnableViewStateMacShouldBeTrue](#FXCOP_EVSMSBT)                                                                FXCOP_EVSMSBT      Major    
                                       [EnableViewStateShouldBeTrue](#FXCOP_EVSSBT)                                                                    FXCOP_EVSSBT       Info     
                                       [ValidateRequestShouldBeEnabled](#FXCOP_VRSBE)                                                                  FXCOP_VRSBE        Major    
                                       [ViewStateEncryptionModeShouldBeAlways](#FXCOP_VSEMSBA)                                                         FXCOP_VSEMSBA      Major    
                                       [ViewStateUserKeyShouldBeSet](#FXCOP_VSUKSBS)                                                                   FXCOP_VSUKSBS      Major    
  ASP.NET.Security.Configuration Rules [AnonymousAccessIsEnabled](#FXCOP_AAIE)                                                                         FXCOP_AAIE         Minor    
                                       [CustomErrorPageShouldBeSpecified](#FXCOP_CEPSBS)                                                               FXCOP_CEPSBS       Major    
                                       [CustomErrorsModeShouldBeOn](#FXCOP_CEMSBO)                                                                     FXCOP_CEMSBO       Major    
                                       [DebugCompilationMustBeDisabled](#FXCOP_DCMBD)                                                                  FXCOP_DCMBD        Blocker  
                                       [EnableCrossAppRedirectsShouldBeTrue](#FXCOP_ECARSBT)                                                           FXCOP_ECARSBT      Minor    
                                       [FormAuthenticationProtectionShouldBeAll](#FXCOP_FAPSBA)                                                        FXCOP_FAPSBA       Major    
                                       [FormAuthenticationRequireSSLShouldBeTrue](#FXCOP_FARBT)                                                        FXCOP_FARBT        Major    
                                       [FormAuthenticationShouldNotContainFormAuthenticationCredentials](#FXCOP_FASNCFAC)                              FXCOP_FASNCFAC     Blocker  
                                       [FormAuthenticationSlidingExpirationShouldBeFalse](#FXCOP_FASESBF)                                              FXCOP_FASESBF      Minor    
                                       [HttpCookiesHttpOnlyCookiesShouldBeTrue](#FXCOP_HCHOCSBT)                                                       FXCOP_HCHOCSBT     Major    
                                       [HttpCookiesRequireSSLShouldBeTrue](#FXCOP_HCRBT)                                                               FXCOP_HCRBT        Major    
                                       [HttpRuntimeEnableHeaderCheckingShouldBeTrue](#FXCOP_HREHCSBT)                                                  FXCOP_HREHCSBT     Major    
                                       [PagesEnableEventValidationMustBeTrue](#FXCOP_PEEVMBT)                                                          FXCOP_PEEVMBT      Major    
                                       [PagesEnableViewStateMacShouldBeTrue](#FXCOP_PEVSMSBT)                                                          FXCOP_PEVSMSBT     Major    
                                       [PagesValidateRequestShouldBeEnabled](#FXCOP_PVRSBE)                                                            FXCOP_PVRSBE       Major    
                                       [PagesViewStateEncryptionModeShouldBeAlways](#FXCOP_PVSEMSBA)                                                   FXCOP_PVSEMSBA     Critical 
                                       [RoleManagerCookieProtectionShouldBeAll](#FXCOP_RMCPSBA)                                                        FXCOP_RMCPSBA      Major    
                                       [RoleManagerCookieRequireSSLShouldBeTrue](#FXCOP_RMCRBT)                                                        FXCOP_RMCRBT       Major    
                                       [RoleManagerCookieSlidingExpirationShouldBeTrue](#FXCOP_RMCSESBF)                                               FXCOP_RMCSESBF     Minor    
                                       [TraceShouldBeDisabled](#FXCOP_TSBD)                                                                            FXCOP_TSBD         Major    
  Microsoft.Design Rules               [Abstract types should not have constructors](#FXCOP_ATSNHC)                                                    FXCOP_ATSNHC       Major    
                                       [Assemblies should have valid strong names](#FXCOP_ASHVSN)                                                      FXCOP_ASHVSN       Blocker  
                                       [Avoid empty interfaces](#FXCOP_AEI)                                                                            FXCOP_AEI          Minor    
                                       [Avoid excessive parameters on generic types](#FXCOP_AEPOGT)                                                    FXCOP_AEPOGT       Critical 
                                       [Avoid namespaces with few types](#FXCOP_ANWFT)                                                                 FXCOP_ANWFT        Minor    
                                       [Avoid out parameters](#FXCOP_AOP)                                                                              FXCOP_AOP          Minor    
                                       [Collections should implement generic interface](#FXCOP_CSIGI)                                                  FXCOP_CSIGI        Critical 
                                       [Consider passing base types as parameters](#FXCOP_CPBTAP)                                                      FXCOP_CPBTAP       Critical 
                                       [Declare event handlers correctly](#FXCOP_DEHC)                                                                 FXCOP_DEHC         Critical 
                                       [Declare types in namespaces](#FXCOP_DTIN)                                                                      FXCOP_DTIN         Critical 
                                       [Default parameters should not be used](#FXCOP_DPSNBU)                                                          FXCOP_DPSNBU       Critical 
                                       [Define accessors for attribute arguments](#FXCOP_DAFAA)                                                        FXCOP_DAFAA        Critical 
                                       [Do not catch general exception types](#FXCOP_DNCGET)                                                           FXCOP_DNCGET       Blocker  
                                       [Do not declare protected members in sealed types](#FXCOP_DNDPMIST)                                             FXCOP_DNDPMIST     Critical 
                                       [Do not declare static members on generic types](#FXCOP_DNDSMOGT)                                               FXCOP_DNDSMOGT     Critical 
                                       [Do not declare virtual members in sealed types](#FXCOP_DNDVMIST)                                               FXCOP_DNDVMIST     Critical 
                                       [Do not declare visible instance fields](#FXCOP_DNDVIF)                                                         FXCOP_DNDVIF       Critical 
                                       [Do not expose generic lists](#FXCOP_DNEGL)                                                                     FXCOP_DNEGL        Critical 
                                       [Do not hide base class methods](#FXCOP_DNHBCM)                                                                 FXCOP_DNHBCM       Major    
                                       [Do not nest generic types in member signatures](#FXCOP_DNNGTIMS)                                               FXCOP_DNNGTIMS     Blocker  
                                       [Do not overload operator equals on reference types](#FXCOP_DNOOEORT)                                           FXCOP_DNOOEORT     Minor    
                                       [Do not pass types by reference](#FXCOP_DNPTBR)                                                                 FXCOP_DNPTBR       Minor    
                                       [Do not raise exceptions in unexpected locations](#FXCOP_DNREIUL)                                               FXCOP_DNREIUL      Critical 
                                       [Enum storage should be Int32](#FXCOP_ESSBI)                                                                    FXCOP_ESSBI        Minor    
                                       [Enumerators should be strongly typed](#FXCOP_ESBST)                                                            FXCOP_ESBST        Critical 
                                       [Enums should have zero value](#FXCOP_ESHZV)                                                                    FXCOP_ESHZV        Blocker  
                                       [Exceptions should be public](#FXCOP_ESBP)                                                                      FXCOP_ESBP         Minor    
                                       [Generic methods should provide type parameter](#FXCOP_GMSPTP)                                                  FXCOP_GMSPTP       Minor    
                                       [ICollection implementations have strongly typed members](#FXCOP_IIHSTM)                                        FXCOP_IIHSTM       Critical 
                                       [Implement IDisposable correctly](#FXCOP_IC)                                                                    FXCOP_IC           Critical 
                                       [Implement standard exception constructors](#FXCOP_ISEC)                                                        FXCOP_ISEC         Critical 
                                       [Indexers should not be multidimensional](#FXCOP_ISNBM)                                                         FXCOP_ISNBM        Minor    
                                       [Interface methods should be callable by child types](#FXCOP_IMSBCBCT)                                          FXCOP_IMSBCBCT     Critical 
                                       [Lists are strongly typed](#FXCOP_LAST)                                                                         FXCOP_LAST         Critical 
                                       [Mark assemblies with AssemblyVersionAttribute](#FXCOP_MAWAV)                                                   FXCOP_MAWAV        Critical 
                                       [Mark assemblies with CLSCompliantAttribute](#FXCOP_MAWCC)                                                      FXCOP_MAWCC        Critical 
                                       [Mark assemblies with ComVisibleAttribute](#FXCOP_MAWCV)                                                        FXCOP_MAWCV        Blocker  
                                       [Mark attributes with AttributeUsageAttribute](#FXCOP_MAWAU)                                                    FXCOP_MAWAU        Critical 
                                       [Mark enums with FlagsAttribute](#FXCOP_MEWF)                                                                   FXCOP_MEWF         Minor    
                                       [Members should not expose certain concrete types](#FXCOP_MSNECCT)                                              FXCOP_MSNECCT      Critical 
                                       [Move P/Invokes to NativeMethods class](#FXCOP_MTNMC)                                                           FXCOP_MTNMC        Major    
                                       [Nested types should not be visible](#FXCOP_NTSNBV)                                                             FXCOP_NTSNBV       Critical 
                                       [Overload operator equals on overloading add and subtract](#FXCOP_OOEOOAAS)                                     FXCOP_OOEOOAAS     Critical 
                                       [Override methods on comparable types](#FXCOP_OMOCT)                                                            FXCOP_OMOCT        Critical 
                                       [Properties should not be write only](#FXCOP_PSNBWO)                                                            FXCOP_PSNBWO       Critical 
                                       [Provide ObsoleteAttribute message](#FXCOP_POAM)                                                                FXCOP_POAM         Critical 
                                       [Replace repetitive arguments with params array](#FXCOP_RRAWPA)                                                 FXCOP_RRAWPA       Minor    
                                       [Static holder types should be sealed](#FXCOP_SHTSBS)                                                           FXCOP_SHTSBS       Major    
                                       [Static holder types should not have constructors](#FXCOP_SHTSNHC)                                              FXCOP_SHTSNHC      Critical 
                                       [String URI overloads call System.Uri overloads](#FXCOP_SUOCSUO)                                                FXCOP_SUOCSUO      Critical 
                                       [Types should not extend certain base types](#FXCOP_TSNECBT)                                                    FXCOP_TSNECBT      Critical 
                                       [Types that own disposable fields should be disposable](#FXCOP_TTODFSBD)                                        FXCOP_TTODFSBD     Blocker  
                                       [Types that own native resources should be disposable](#FXCOP_TTONRSBD)                                         FXCOP_TTONRSBD     Blocker  
                                       [URI parameters should not be strings](#FXCOP_UPSNBS)                                                           FXCOP_UPSNBS       Critical 
                                       [URI properties should not be strings](#FXCOP_URPRSHNOBEST)                                                     FXCOP_URPRSHNOBEST Critical 
                                       [URI return values should not be strings](#FXCOP_URVSNBS)                                                       FXCOP_URVSNBS      Critical 
                                       [Use events where appropriate](#FXCOP_UEWA)                                                                     FXCOP_UEWA         Minor    
                                       [Use generic event handler instances](#FXCOP_UGEHI)                                                             FXCOP_UGEHI        Critical 
                                       [Use generics where appropriate](#FXCOP_UGWA)                                                                   FXCOP_UGWA         Blocker  
                                       [Use integral or string argument for indexers](#FXCOP_UIOSAFI)                                                  FXCOP_UIOSAFI      Critical 
                                       [Use properties where appropriate](#FXCOP_UPWA)                                                                 FXCOP_UPWA         Minor    
  Microsoft.Globalization Rules        [Avoid duplicate accelerators](#FXCOP_ADA)                                                                      FXCOP_ADA          Critical 
                                       [Do not hardcode locale specific strings](#FXCOP_DNHLSS)                                                        FXCOP_DNHLSS       Critical 
                                       [Normalize strings to uppercase](#FXCOP_NSTU)                                                                   FXCOP_NSTU         Critical 
                                       [Set locale for data types](#FXCOP_SLFDT)                                                                       FXCOP_SLFDT        Critical 
                                       [Specify CultureInfo](#FXCOP_SCI)                                                                               FXCOP_SCI          Critical 
                                       [Specify IFormatProvider](#FXCOP_SP)                                                                            FXCOP_SP           Critical 
                                       [Specify marshaling for P/Invoke string arguments](#FXCOP_SMFSA)                                                FXCOP_SMFSA        Critical 
                                       [Specify MessageBoxOptions](#FXCOP_SMBO)                                                                        FXCOP_SMBO         Critical 
                                       [Specify StringComparison](#FXCOP_SSC)                                                                          FXCOP_SSC          Critical 
                                       [Use ordinal StringComparison](#FXCOP_UOSC)                                                                     FXCOP_UOSC         Critical 
  Microsoft.Interoperability Rules     [Auto layout types should not be COM visible](#FXCOP_ALTSNBCV)                                                  FXCOP_ALTSNBCV     Critical 
                                       [Avoid Int64 arguments for Visual Basic 6 clients](#FXCOP_AIF)                                                  FXCOP_AIF          Minor    
                                       [Avoid non-public fields in COM visible value types](#FXCOP_ANFICVVT)                                           FXCOP_ANFICVVT     Minor    
                                       [Avoid overloads in COM visible interfaces](#FXCOP_AOICVI)                                                      FXCOP_AOICVI       Major    
                                       [Avoid static members in COM visible types](#FXCOP_ASMICVT)                                                     FXCOP_ASMICVT      Minor    
                                       [Call GetLastError immediately after P/Invoke](#FXCOP_CGLEIA)                                                   FXCOP_CGLEIA       Critical 
                                       [COM registration methods should be matched](#FXCOP_CRMSBM)                                                     FXCOP_CRMSBM       Major    
                                       [COM registration methods should not be visible](#FXCOP_CRMSNBV)                                                FXCOP_CRMSNBV      Major    
                                       [COM visible type base types should be COM visible](#FXCOP_CVTBTSBCV)                                           FXCOP_CVTBTSBCV    Critical 
                                       [COM visible types should be creatable](#FXCOP_CVTSBC)                                                          FXCOP_CVTSBC       Critical 
                                       [Declare P/Invokes correctly](#FXCOP_DC)                                                                        FXCOP_DC           Blocker  
                                       [Do not use AutoDual ClassInterfaceType](#FXCOP_DNUADCIT)                                                       FXCOP_DNUADCIT     Blocker  
                                       [Mark boolean P/Invoke arguments with MarshalAs](#FXCOP_MBAWMA)                                                 FXCOP_MBAWMA       Minor    
                                       [Mark ComSource interfaces as IDispatch](#FXCOP_MCSIA)                                                          FXCOP_MCSIA        Critical 
                                       [P/Invoke entry points should exist](#FXCOP_PEPSE)                                                              FXCOP_PEPSE        Major    
                                       [P/Invokes should not be visible](#FXCOP_PSNBV)                                                                 FXCOP_PSNBV        Blocker  
  Microsoft.Maintainability Rules      [Avoid excessive class coupling](#FXCOP_AECC)                                                                   FXCOP_AECC         Minor    
                                       [Avoid excessive complexity](#FXCOP_AEC)                                                                        FXCOP_AEC          Minor    
                                       [Avoid excessive inheritance](#FXCOP_AVEXIN)                                                                    FXCOP_AVEXIN       Minor    
                                       [Avoid unmaintainable code](#FXCOP_AUC)                                                                         FXCOP_AUC          Minor    
                                       [Review misleading field names](#FXCOP_RMFN)                                                                    FXCOP_RMFN         Minor    
                                       [Variable names should not match field names](#FXCOP_VNSNMFN)                                                   FXCOP_VNSNMFN      Critical 
  Microsoft.Mobility Rules             [Do not use idle process priority](#FXCOP_DNUIPP)                                                               FXCOP_DNUIPP       Critical 
                                       [Do not use timers that prevent power state changes](#FXCOP_DNUTTPPSC)                                          FXCOP_DNUTTPPSC    Critical 
  Microsoft.Naming Rules               [Compound words should be cased correctly](#FXCOP_CWSBCC)                                                       FXCOP_CWSBCC       Critical 
                                       [Do not name enum values 'Reserved'](#FXCOP_DNNEVR)                                                             FXCOP_DNNEVR       Critical 
                                       [Do not prefix enum values with type name](#FXCOP_DNPEVWTN)                                                     FXCOP_DNPEVWTN     Critical 
                                       [Events should not have before or after prefix](#FXCOP_ESNHBOAP)                                                FXCOP_ESNHBOAP     Critical 
                                       [Flags enums should have plural names](#FXCOP_FESHPN)                                                           FXCOP_FESHPN       Critical 
                                       [Identifiers should be cased correctly](#FXCOP_ISBCC)                                                           FXCOP_ISBCC        Critical 
                                       [Identifiers should be spelled correctly](#FXCOP_ISBSC)                                                         FXCOP_ISBSC        Major    
                                       [Identifiers should differ by more than case](#FXCOP_ISDBMTC)                                                   FXCOP_ISDBMTC      Critical 
                                       [Identifiers should have correct prefix](#FXCOP_ISHCP)                                                          FXCOP_ISHCP        Critical 
                                       [Identifiers should have correct suffix](#FXCOP_ISHCS)                                                          FXCOP_ISHCS        Critical 
                                       [Identifiers should not contain type names](#FXCOP_ISNCTN)                                                      FXCOP_ISNCTN       Critical 
                                       [Identifiers should not contain underscores](#FXCOP_ISNCU)                                                      FXCOP_ISNCU        Critical 
                                       [Identifiers should not have incorrect prefix](#FXCOP_ISNHIP)                                                   FXCOP_ISNHIP       Critical 
                                       [Identifiers should not have incorrect suffix](#FXCOP_ISNHIS)                                                   FXCOP_ISNHIS       Blocker  
                                       [Identifiers should not match keywords](#FXCOP_ISNMK)                                                           FXCOP_ISNMK        Critical 
                                       [Only FlagsAttribute enums should have plural names](#FXCOP_OFESHPN)                                            FXCOP_OFESHPN      Critical 
                                       [Parameter names should match base declaration](#FXCOP_PNSMBD)                                                  FXCOP_PNSMBD       Critical 
                                       [Parameter names should not match member names](#FXCOP_PNSNMMN)                                                 FXCOP_PNSNMMN      Critical 
                                       [Property names should not match get methods](#FXCOP_PNSNMGM)                                                   FXCOP_PNSNMGM      Critical 
                                       [Resource string compound words should be cased correctly](#FXCOP_RSCWSBCC)                                     FXCOP_RSCWSBCC     Critical 
                                       [Resource strings should be spelled correctly](#FXCOP_RSSBSC)                                                   FXCOP_RSSBSC       Major    
                                       [Type names should not match namespaces](#FXCOP_TNSNMN)                                                         FXCOP_TNSNMN       Critical 
                                       [Use preferred terms](#FXCOP_UPT)                                                                               FXCOP_UPT          Critical 
  Microsoft.Performance Rules          [Avoid excessive locals](#FXCOP_AEL)                                                                            FXCOP_AEL          Minor    
                                       [Avoid uncalled private code](#FXCOP_AUPC)                                                                      FXCOP_AUPC         Minor    
                                       [Avoid uninstantiated internal classes](#FXCOP_AUIC)                                                            FXCOP_AUIC         Minor    
                                       [Avoid unsealed attributes](#FXCOP_AUA)                                                                         FXCOP_AUA          Minor    
                                       [Avoid unused private fields](#FXCOP_AUPF)                                                                      FXCOP_AUPF         Minor    
                                       [Do not cast unnecessarily](#FXCOP_DNCU)                                                                        FXCOP_DNCU         Minor    
                                       [Initialize reference type static fields inline](#FXCOP_IRTSFI)                                                 FXCOP_IRTSFI       Major    
                                       [Mark assemblies with NeutralResourcesLanguageAttribute](#FXCOP_MAWNRL)                                         FXCOP_MAWNRL       Minor    
                                       [Mark members as static](#FXCOP_MMAS)                                                                           FXCOP_MMAS         Minor    
                                       [Override equals and operator equals on value types](#FXCOP_OEAOEOVT)                                           FXCOP_OEAOEOVT     Minor    
                                       [Prefer jagged arrays over multidimensional](#FXCOP_PJAOM)                                                      FXCOP_PJAOM        Minor    
                                       [Properties should not return arrays](#FXCOP_PSNRA)                                                             FXCOP_PSNRA        Minor    
                                       [Remove empty finalizers](#FXCOP_REF)                                                                           FXCOP_REF          Minor    
                                       [Remove unused locals](#FXCOP_RUL)                                                                              FXCOP_RUL          Minor    
                                       [Test for empty strings using string length](#FXCOP_TFESUSL)                                                    FXCOP_TFESUSL      Minor    
                                       [Use literals where appropriate](#FXCOP_ULWA)                                                                   FXCOP_ULWA         Minor    
  Microsoft.Portability Rules          [P/Invoke declarations should be portable](#FXCOP_PDSBP)                                                        FXCOP_PDSBP        Critical 
                                       [Use only API from targeted framework](#FXCOP_UOAFTF)                                                           FXCOP_UOAFTF       Critical 
                                       [Value type fields should be portable](#FXCOP_VTFSBP)                                                           FXCOP_VTFSBP       Blocker  
  Microsoft.Reliability Rules          [Avoid calling problematic methods](#FXCOP_ACPM)                                                                FXCOP_ACPM         Critical 
                                       [Do not lock on objects with weak identity](#FXCOP_DNLOOWWI)                                                    FXCOP_DNLOOWWI     Blocker  
                                       [Do not treat fibers as threads](#FXCOP_DNTFAT)                                                                 FXCOP_DNTFAT       Critical 
                                       [Remove calls to GC.KeepAlive](#FXCOP_RCTA)                                                                     FXCOP_RCTA         Major    
                                       [Use SafeHandle to encapsulate native resources](#FXCOP_USHTENR)                                                FXCOP_USHTENR      Major    
  Microsoft.Security Rules             [APTCA methods should only call APTCA methods](#FXCOP_AMSOCAM)                                                  FXCOP_AMSOCAM      Blocker  
                                       [APTCA types should only extend APTCA base types](#FXCOP_ATSOEABT)                                              FXCOP_ATSOEABT     Blocker  
                                       [Array fields should not be read only](#FXCOP_AFSNBRO)                                                          FXCOP_AFSNBRO      Major    
                                       [Call GC.KeepAlive when using native resources](#FXCOP_CAWUNR)                                                  FXCOP_CAWUNR       Minor    
                                       [Catch non-CLSCompliant exceptions in general handlers](#FXCOP_CNCCEIGH)                                        FXCOP_CNCCEIGH     Critical 
                                       [Default constructors must be at least as critical as base type default constructors](#FXCOP_DCMHCT)            FXCOP_DCMHCT       Blocker  
                                       [Delegates must bind to methods with consistent transparency](#FXCOP_DMBWCT)                                    FXCOP_DMBWCT       Blocker  
                                       [Do not declare read only mutable reference types](#FXCOP_DNDROMRT)                                             FXCOP_DNDROMRT     Critical 
                                       [Do not indirectly expose methods with link demands](#FXCOP_DNIEMWLD)                                           FXCOP_DNIEMWLD     Blocker  
                                       [Fields with critical types should be security critical.](#FXCOP_FWCTSBC)                                       FXCOP_FWCTSBC      Minor    
                                       [Level 2 assemblies should not contain LinkDemands](#FXCOP_SRSLSNBPWLD)                                         FXCOP_SRSLSNBPWLD  Major    
                                       [Members should not have conflicting transparency annotations](#FXCOP_TASNC)                                    FXCOP_TASNC        Minor    
                                       [Method security should be a superset of type](#FXCOP_MSSBOT)                                                   FXCOP_MSSBOT       Blocker  
                                       [Methods must keep consistent transparency when overriding base methods](#FXCOP_MMOWCT)                         FXCOP_MMOWCT       Blocker  
                                       [Override link demands should be identical to base](#FXCOP_OLDSBITB)                                            FXCOP_OLDSBITB     Blocker  
                                       [P/Invoke declarations should not be safe-critical.](#FXCOP_PSNBSC)                                             FXCOP_PSNBSC       Minor    
                                       [Pointers should not be visible](#FXCOP_POSHNOBEVI)                                                             FXCOP_POSHNOBEVI   Blocker  
                                       [Review declarative security on value types](#FXCOP_RDSOVT)                                                     FXCOP_RDSOVT       Critical 
                                       [Review deny and permit only usage](#FXCOP_RDAPOU)                                                              FXCOP_RDAPOU       Major    
                                       [Review imperative security](#FXCOP_RIS)                                                                        FXCOP_RIS          Blocker  
                                       [Review SuppressUnmanagedCodeSecurityAttribute usage](#FXCOP_RSUCSU)                                            FXCOP_RSUCSU       Blocker  
                                       [Review visible event handlers](#FXCOP_RVEH)                                                                    FXCOP_RVEH         Blocker  
                                       [Seal methods that satisfy private interfaces](#FXCOP_SMTSPI)                                                   FXCOP_SMTSPI       Critical 
                                       [Secure asserts](#FXCOP_SA)                                                                                     FXCOP_SA           Blocker  
                                       [Secure serialization constructors](#FXCOP_SESECO)                                                              FXCOP_SESECO       Blocker  
                                       [Secured types should not expose fields](#FXCOP_STSNEF)                                                         FXCOP_STSNEF       Blocker  
                                       [Security critical constants should be transparent](#FXCOP_CSBT)                                                FXCOP_CSBT         Minor    
                                       [Security critical types may not participate in type equivalence](#FXCOP_CTMNPITE)                              FXCOP_CTMNPITE     Blocker  
                                       [Static constructors should be private](#FXCOP_SCSBP)                                                           FXCOP_SCSBP        Critical 
                                       [Transparent code may not use security asserts](#FXCOP_TMMNUSA)                                                 FXCOP_TMMNUSA      Blocker  
                                       [Transparent code may not use security critical attributes](#FXCOP_TCMNUCA)                                     FXCOP_TCMNUCA      Critical 
                                       [Transparent code must not reference security critical items](#FXCOP_TMMNRCC)                                   FXCOP_TMMNRCC      Blocker  
                                       [Transparent code should not be protected with LinkDemands](#FXCOP_TMSNBPWLD)                                   FXCOP_TMSNBPWLD    Minor    
                                       [Transparent code should not load assemblies from byte arrays](#FXCOP_TMSNLAFBA)                                FXCOP_TMSNLAFBA    Minor    
                                       [Transparent methods may not use the HandleProcessCorruptingExceptions attribute](#FXCOP_TMMNHPCE)              FXCOP_TMMNHPCE     Critical 
                                       [Transparent methods must contain only verifiable IL](#FXCOP_TMMBV)                                             FXCOP_TMMBV        Critical 
                                       [Transparent methods must not call into native code](#FXCOP_TMMNCNC)                                            FXCOP_TMMNCNC      Critical 
                                       [Transparent methods must not call methods with the SuppressUnmanagedCodeSecurity attribute](#FXCOP_TMMNCSUCSM) FXCOP_TMMNCSUCSM   Critical 
                                       [Transparent methods must not satisfy LinkDemands](#FXCOP_TMMNSLD)                                              FXCOP_TMMNSLD      Critical 
                                       [Transparent methods should not be decorated with the SuppressUnmanagedCodeSecurityAttribute](#FXCOP_TMSNUSUCS) FXCOP_TMSNUSUCS    Minor    
                                       [Transparent methods should not use security demands](#FXCOP_TMSND)                                             FXCOP_TMSND        Major    
                                       [Type link demands require inheritance demands](#FXCOP_TLDRID)                                                  FXCOP_TLDRID       Blocker  
                                       [Types must be at least as critical as their base types and interfaces](#FXCOP_TMBALACABT)                      FXCOP_TMBALACABT   Blocker  
                                       [Wrap vulnerable finally clauses in outer try](#FXCOP_WVFCIOT)                                                  FXCOP_WVFCIOT      Critical 
  Microsoft.Usage Rules                [Attribute string literals should parse correctly](#FXCOP_ASLSPC)                                               FXCOP_ASLSPC       Minor    
                                       [Call base class methods on ISerializable types](#FXCOP_CBCMOT)                                                 FXCOP_CBCMOT       Critical 
                                       [Call GC.SuppressFinalize correctly](#FXCOP_CFC)                                                                FXCOP_CFC          Major    
                                       [Collection properties should be read only](#FXCOP_CPSBRO)                                                      FXCOP_CPSBRO       Minor    
                                       [Disposable fields should be disposed](#FXCOP_DFSBD)                                                            FXCOP_DFSBD        Minor    
                                       [Disposable types should declare finalizer](#FXCOP_DTSDF)                                                       FXCOP_DTSDF        Critical 
                                       [Do not call overridable methods in constructors](#FXCOP_DNCOMIC)                                               FXCOP_DNCOMIC      Major    
                                       [Do not decrease inherited member visibility](#FXCOP_DNDIMV)                                                    FXCOP_DNDIMV       Critical 
                                       [Do not ignore method results](#FXCOP_DNIMR)                                                                    FXCOP_DNIMR        Minor    
                                       [Do not mark enums with FlagsAttribute](#FXCOP_DNMEWF)                                                          FXCOP_DNMEWF       Critical 
                                       [Do not mark serviced components with WebMethod](#FXCOP_DNMSCWWM)                                               FXCOP_DNMSCWWM     Major    
                                       [Do not raise exceptions in exception clauses](#FXCOP_DNREIEC)                                                  FXCOP_DNREIEC      Critical 
                                       [Do not raise reserved exception types](#FXCOP_DNRRET)                                                          FXCOP_DNRRET       Critical 
                                       [Do not ship unreleased resource formats](#FXCOP_DNSURF)                                                        FXCOP_DNSURF       Critical 
                                       [Finalizers should be protected](#FXCOP_FSBP)                                                                   FXCOP_FSBP         Blocker  
                                       [Finalizers should call base class finalizer](#FXCOP_FSCBCF)                                                    FXCOP_FSCBCF       Blocker  
                                       [Implement ISerializable correctly](#FXCOP_IMCO)                                                                FXCOP_IMCO         Critical 
                                       [Implement serialization constructors](#FXCOP_ISC)                                                              FXCOP_ISC          Critical 
                                       [Implement serialization methods correctly](#FXCOP_ISMC)                                                        FXCOP_ISMC         Critical 
                                       [Initialize value type static fields inline](#FXCOP_IVTSFI)                                                     FXCOP_IVTSFI       Blocker  
                                       [Instantiate argument exceptions correctly](#FXCOP_IAEC)                                                        FXCOP_IAEC         Blocker  
                                       [Mark all non-serializable fields](#FXCOP_MANSF)                                                                FXCOP_MANSF        Critical 
                                       [Mark ISerializable types with SerializableAttribute](#FXCOP_MTWS)                                              FXCOP_MTWS         Minor    
                                       [Mark Windows Forms entry points with STAThread](#FXCOP_MWFEPWST)                                               FXCOP_MWFEPWST     Critical 
                                       [Members should differ by more than return type](#FXCOP_MSDBMTRT)                                               FXCOP_MSDBMTRT     Critical 
                                       [Non-constant fields should not be visible](#FXCOP_NCFSNBV)                                                     FXCOP_NCFSNBV      Minor    
                                       [Operations should not overflow](#FXCOP_OSNO)                                                                   FXCOP_OSNO         Major    
                                       [Operator overloads have named alternates](#FXCOP_OOHNA)                                                        FXCOP_OOHNA        Critical 
                                       [Operators should have symmetrical overloads](#FXCOP_OSHSO)                                                     FXCOP_OSHSO        Blocker  
                                       [Overload operator equals on overriding ValueType.Equals](#FXCOP_OOEOOVTE)                                      FXCOP_OOEOOVTE     Minor    
                                       [Override Equals on overloading operator equals](#FXCOP_OEOOOE)                                                 FXCOP_OEOOOE       Critical 
                                       [Override GetHashCode on overriding Equals](#FXCOP_OGHCOOE)                                                     FXCOP_OGHCOOE      Critical 
                                       [Pass System.Uri objects instead of strings](#FXCOP_PSUOIOS)                                                    FXCOP_PSUOIOS      Minor    
                                       [Provide deserialization methods for optional fields](#FXCOP_PDMFOF)                                            FXCOP_PDMFOF       Minor    
                                       [Rethrow to preserve stack details](#FXCOP_RTPSD)                                                               FXCOP_RTPSD        Critical 
                                       [Review unused parameters](#FXCOP_RUP)                                                                          FXCOP_RUP          Minor    
                                       [Test for NaN correctly](#FXCOP_TFN)                                                                            FXCOP_TFN          Blocker  
                                       [Use managed equivalents of Win32 API](#FXCOP_UMEOW)                                                            FXCOP_UMEOW        Critical 
                                       [Use params for variable arguments](#FXCOP_UPFVA)                                                               FXCOP_UPFVA        Critical 

### ASP.NET.MVC.Security Rules

#### ControllerActionShouldValidateInput (FXCOP_CASVI) {#FXCOP_CASVI}

Verifies if the ValidateInputAttribute is used properly to protect against XSS attacks.

#### MarkVerbHandlersWithValidateAntiforgeryToken (FXCOP_MVHWVAT) {#FXCOP_MVHWVAT}

Rule that verifies that if the ValidateAntiforgeryTokenAttribute is used to protect against Potential CSRF attack in MVC.

### ASP.NET.Security Rules

#### EnableEventValidationShouldBeTrue (FXCOP_EEVSBT) {#FXCOP_EEVSBT}

Rule that will identify if the EnableEventValidation is disabled on a certain page.

#### EnableViewStateMacShouldBeTrue (FXCOP_EVSMSBT) {#FXCOP_EVSMSBT}

Rule that will identify if the EnableViewStateMac is not set to false on a certain page.

#### EnableViewStateShouldBeTrue (FXCOP_EVSSBT) {#FXCOP_EVSSBT}

Rule that will identify if the EnableViewStateRule is not set to false on a certain page.

#### ValidateRequestShouldBeEnabled (FXCOP_VRSBE) {#FXCOP_VRSBE}

Rule that will identify if the ValidateRequest is disabled on a certain page.

#### ViewStateEncryptionModeShouldBeAlways (FXCOP_VSEMSBA) {#FXCOP_VSEMSBA}

Rule that will identify if the ViewStateEncryptionMode is not set to Never on a certain page.

#### ViewStateUserKeyShouldBeSet (FXCOP_VSUKSBS) {#FXCOP_VSUKSBS}

Verifies if the ViewStateEncryptionMode directive is not set to Never  on a certain page.

### ASP.NET.Security.Configuration Rules

#### AnonymousAccessIsEnabled (FXCOP_AAIE) {#FXCOP_AAIE}

Looks in the web.config file to see if the authorization section allows anonymous access.

#### CustomErrorPageShouldBeSpecified (FXCOP_CEPSBS) {#FXCOP_CEPSBS}

Verifies that the CustomErrors section is configured to have a default url for redirecting uses in case of error.

#### CustomErrorsModeShouldBeOn (FXCOP_CEMSBO) {#FXCOP_CEMSBO}

The rule verifies that the system.web.customErrors mode is set to On or RemoteOnly. This disable detailed error message returned by ASP.NET to remote users.

#### DebugCompilationMustBeDisabled (FXCOP_DCMBD) {#FXCOP_DCMBD}

Verifies that debug compilation is turned off. This eliminates potential performance and security issues related to debug code enabled and additional extensive error messages being returned.

#### EnableCrossAppRedirectsShouldBeTrue (FXCOP_ECARSBT) {#FXCOP_ECARSBT}

The rule verifies that the system.web.authentication.forms enableCrossAppRedirects is set to true. The settings indicate if the user should be redirected to another application url after the authentication process. If the setting is false, the authentication process will not allow redirection to another application or host. This helps prevent an attacker to force the user to be redirected to another site during the authentication process. This attack is commonly called Open redirect and is used mostly during phishing attacks.

#### FormAuthenticationProtectionShouldBeAll (FXCOP_FAPSBA) {#FXCOP_FAPSBA}

The rule verifies that the protection attribute on the system.web.authentication.forms protection is set to All which specifies that the application use both data validation and encryption to help protect the authentication cookie.

#### FormAuthenticationRequireSSLShouldBeTrue (FXCOP_FARBT) {#FXCOP_FARBT}

The rule verifies that the requireSSL attribute on the system.web.authentication.forms configuration element is set to True which force the authentication cookie to specify the secure attribute. This indicates the browser to only provide the cookie over SSL.

#### FormAuthenticationShouldNotContainFormAuthenticationCredentials (FXCOP_FASNCFAC) {#FXCOP_FASNCFAC}

The rule verifies that no credentials are specified under the form authentication configuration.

#### FormAuthenticationSlidingExpirationShouldBeFalse (FXCOP_FASESBF) {#FXCOP_FASESBF}

The rule verifies that if the system.web.authentication.forms slidingExpiration be set to false when the site is being serviced over HTTP. This will force the authentication cookie to have a fix timeout value instead of being refreshed by each request. Since the cookie will traverse over clear text network and can be sniffed, having a fix timeout value on the cookie will limit the amount of time the cookie can be replayed. If the cookie is traversing over HTTPS, it is less likely to be intercepted and having the slidingExpiration setting to True will cause the timeout to be refreshed after each request which gives a better user experience.

#### HttpCookiesHttpOnlyCookiesShouldBeTrue (FXCOP_HCHOCSBT) {#FXCOP_HCHOCSBT}

The rule verifies that the system.web.httpCookies httpOnlyCookies configuration is set to True which force all cookies to be sent with the HttpOnly attribute.

#### HttpCookiesRequireSSLShouldBeTrue (FXCOP_HCRBT) {#FXCOP_HCRBT}

The rule verifies that the system.web.httpCookies requireSSL configuration is set to True which force all cookies to be sent with the secure attribute. This indicates the browser to only provide the cookie over SSL.

#### HttpRuntimeEnableHeaderCheckingShouldBeTrue (FXCOP_HREHCSBT) {#FXCOP_HREHCSBT}

The rule verifies that the system.web.httpRuntime enableHeaderChecking attribute is set to true. From http://msdn.microsoft.com/en-us/library/e1f13641.aspx. The setting indicates whether ASP.NET should check the request header for potential injection attacks. If an attack is detected, ASP.NET responds with an error. This forces ASP.NET to apply the ValidateRequest protection to headers sent by the client. If an attack is detected the application throws HttpRequestValidationException.

#### PagesEnableEventValidationMustBeTrue (FXCOP_PEEVMBT) {#FXCOP_PEEVMBT}

Verify if event validation is enabled.

#### PagesEnableViewStateMacShouldBeTrue (FXCOP_PEVSMSBT) {#FXCOP_PEVSMSBT}

Verifies that the viewstate mac is enabled.

#### PagesValidateRequestShouldBeEnabled (FXCOP_PVRSBE) {#FXCOP_PVRSBE}

Verify that validateRequest is enabled.

#### PagesViewStateEncryptionModeShouldBeAlways (FXCOP_PVSEMSBA) {#FXCOP_PVSEMSBA}

Verify that the viewstate encryption mode is not configured to never encrypt.

#### RoleManagerCookieProtectionShouldBeAll (FXCOP_RMCPSBA) {#FXCOP_RMCPSBA}

The rule verifies that the system.web.rolemanager cookieProtection is set to All which enforce both the cookie to be encrypted and validated by the server.

#### RoleManagerCookieRequireSSLShouldBeTrue (FXCOP_RMCRBT) {#FXCOP_RMCRBT}

The rule verifies that the system.web.rolemanager cookieRequireSSL attribute is set to True which force the role manager cookie to specify the secure attribute. This indicates the browser to only provide the cookie over SSL.

#### RoleManagerCookieSlidingExpirationShouldBeTrue (FXCOP_RMCSESBF) {#FXCOP_RMCSESBF}

The rule verifies that if the system.web.rolemanager cookieSlidingExpiration is set to false when the site is being serviced over HTTP. This will force the authentication cookie to have a fix timeout value instead of being refreshed by each request. Since the cookie will traverse over clear text network and can be sniffed, having a fix timeout value on the cookie will limit the amount of time the cookie can be replayed. If the cookie is traversing over HTTPS, it is less likely to be intercepted and having the cookieSlidingExpiration setting to True will cause the timeout to be refreshed after each request which gives a better user experience.

#### TraceShouldBeDisabled (FXCOP_TSBD) {#FXCOP_TSBD}

The rule verifies that the system.web.trace enabled setting is set to false which disable tracing. It is recommended to disable tracing on production servers to make sure that an attacker cannot gain information from the trace about your application. Trace information can help an attacker probe and compromise your application.

### Microsoft.Design Rules

#### Abstract types should not have constructors (FXCOP_ATSNHC) {#FXCOP_ATSNHC}

Public constructors for abstract types do not make sense because you cannot create instances of abstract types.

#### Assemblies should have valid strong names (FXCOP_ASHVSN) {#FXCOP_ASHVSN}

Either the assembly has no strong name, an invalid one, or the strong name is valid only because of the computer configuration. The assembly should not be deployed in this state. The most common causes of this are: 1) The assembly's contents were modified after it was signed. 2) The signing process failed. 3) The assembly was delay-signed. 4) A registry key existed that allowed the check to pass (where it would not have otherwise).

#### Avoid empty interfaces (FXCOP_AEI) {#FXCOP_AEI}

Interfaces are meant to contain members that specify a set of behaviors. To mark or label a class, use an attribute instead of an empty interface.

#### Avoid excessive parameters on generic types (FXCOP_AEPOGT) {#FXCOP_AEPOGT}

Avoid generic types with more than two type parameters as users have difficulties understanding what type parameters represent in types with long type parameter lists.

#### Avoid namespaces with few types (FXCOP_ANWFT) {#FXCOP_ANWFT}

A namespace should generally have more than five types.

#### Avoid out parameters (FXCOP_AOP) {#FXCOP_AOP}

Using out parameters might indicate a design flaw. Although there are legitimate times to use out parameters, their use frequently indicates a design that does not conform to the design guidelines for managed code.

#### Collections should implement generic interface (FXCOP_CSIGI) {#FXCOP_CSIGI}

Non-generic strongly typed collections should implement one of the generic collection interfaces. This will allow better integration of the collection with generic API.

#### Consider passing base types as parameters (FXCOP_CPBTAP) {#FXCOP_CPBTAP}

Using base types as parameters to methods improves re-use of these methods if you only use methods & properties from the parameter's base class. E.g. use Stream instead of FileStream as a parameter when only calling Stream.Read(), this makes the method work on all kind of streams instead of just File streams.

#### Declare event handlers correctly (FXCOP_DEHC) {#FXCOP_DEHC}

By convention, .NET events have two parameters that specify the event sender and event data. Event handler signatures should follow this form: void MyEventHandler(object sender, EventArgs e). The 'sender' parameter is always of type System.Object, even if it is possible to employ a more specific type. The 'e' parameter is always of type System.EventArgs. Events that do not provide event data should use the System.EventHandler delegate type. Event handlers return void so that they can send each event to multiple target methods. Any value returned by a target would be lost after the first call.

#### Declare types in namespaces (FXCOP_DTIN) {#FXCOP_DTIN}

A type should be defined inside a namespace to avoid duplication.

#### Default parameters should not be used (FXCOP_DPSNBU) {#FXCOP_DPSNBU}

Some programming languages do not support default parameters. Replace default parameters with method overloads that supply the default argument.

#### Define accessors for attribute arguments (FXCOP_DAFAA) {#FXCOP_DAFAA}

Provide accessors for both named and positional arguments. Each positional argument on an attribute should declare a read-only property with the same name (but different casing). Each named argument should provide a read/write property with the same name (but different casing).

#### Do not catch general exception types (FXCOP_DNCGET) {#FXCOP_DNCGET}

You should not catch Exception or SystemException. Catching generic exception types can hide run-time problems from the library user, and can complicate debugging. You should catch only those exceptions that you can handle gracefully.

#### Do not declare protected members in sealed types (FXCOP_DNDPMIST) {#FXCOP_DNDPMIST}

Sealed types cannot be extended, and protected members are only useful if you can extend the declaring type. Sealed types should not declare protected members.

#### Do not declare static members on generic types (FXCOP_DNDSMOGT) {#FXCOP_DNDSMOGT}

The syntax for calling static members on generic types is complex as the type parameter has to be specified for each call.

#### Do not declare virtual members in sealed types (FXCOP_DNDVMIST) {#FXCOP_DNDVMIST}

Sealed types cannot be extended, and virtual members are only useful if you can extend the declaring type.

#### Do not declare visible instance fields (FXCOP_DNDVIF) {#FXCOP_DNDVIF}

Instance fields that are visible outside of the type that declares them, limit your ability to change the implementation details for those data items. Use properties instead. They do not compromise usability or performance and they do provide flexibility in that they conceal the implementation details of the underlying data.

#### Do not expose generic lists (FXCOP_DNEGL) {#FXCOP_DNEGL}

Do not expose List<T> in object models. Use Collection<T>, ReadOnlyCollection<T> or KeyedCollection<K,V> instead. List<T> is meant to be used from implementation, not in object model API. List<T> is optimized for performance at the cost of long term versioning. For example, if you return List<T> to the client code, you will not ever be able to receive notifications when client code modifies the collection.

#### Do not hide base class methods (FXCOP_DNHBCM) {#FXCOP_DNHBCM}

Defining a method in a derived class with the same name and parameters that are more weakly typed as one that is defined in the base class will obstruct access to the method defined in the base class.

#### Do not nest generic types in member signatures (FXCOP_DNNGTIMS) {#FXCOP_DNNGTIMS}

Avoid API that require users to instantiate a generic type with another generic type as type argument. The syntax gets too complex.

#### Do not overload operator equals on reference types (FXCOP_DNOOEORT) {#FXCOP_DNOOEORT}

Most reference types, including those that override System.Object.Equals, do not override the equality operator  (==). Most languages provide a default implementation of this operator.

#### Do not pass types by reference (FXCOP_DNPTBR) {#FXCOP_DNPTBR}

Although there are legitimate times to use reference parameters, such use frequently indicates a design that does not conform to the design guidelines for managed code.

#### Do not raise exceptions in unexpected locations (FXCOP_DNREIUL) {#FXCOP_DNREIUL}

Do not explicitly raise exceptions from unexpected locations. There are some methods, such as Equals and GetHashCode, which users do not expect to raise exceptions. Therefore calls to these methods are not commonly wrapped in try catch blocks.

#### Enum storage should be Int32 (FXCOP_ESSBI) {#FXCOP_ESSBI}

There is little or no benefit to using a type smaller than Int32. You might require a type that is larger than Int32 if: 1) the enumeration values are flags and there are or will be many (&amp;gt;32) values, or 2) the type needs to be different from Int32 for backward compatibility. Avoid using an underlying type that is not integral.

#### Enumerators should be strongly typed (FXCOP_ESBST) {#FXCOP_ESBST}

Types that implement IEnumerator should also provide a version of the Current property that returns a type other than Object. Implement the interface member explicitly and make the strongly typed version public.

#### Enums should have zero value (FXCOP_ESHZV) {#FXCOP_ESHZV}

An enum should generally have a zero value. If the enum is not decorated with the Flags attribute, it should have a member with a value of zero that represents the empty state. Optionally, this value is named 'None'. For a Flags-attributed enum, a zero-valued member is optional and, if it exists, should always be named 'None'. This value should indicate that no values have been set in the enum. Using a zero-valued member for other purposes is contrary to the use of the Flags attribute in that the bitwise AND and OR operators are useless with the member.

#### Exceptions should be public (FXCOP_ESBP) {#FXCOP_ESBP}

Exception classes should either be public, or have a non-generic public ancestor.

#### Generic methods should provide type parameter (FXCOP_GMSPTP) {#FXCOP_GMSPTP}

Methods where the type parameter cannot be inferred from the parameters and therefore has to be defined in the method call are too difficult to understand. Methods with a formal parameter typed as the generic method type parameter support inference. Methods with no formal parameter typed as the generic method type parameter don't support inference.

#### ICollection implementations have strongly typed members (FXCOP_IIHSTM) {#FXCOP_IIHSTM}

Types that implement ICollection should also provide a version of CopyTo with the first parameter set to a strong type, namely a type other than an array of objects or System.Array. Implement the interface member explicitly and make the strongly typed version public. It is safe to ignore violations of this rule when you are implementing a new object-based collection, such as a binary tree, where types based on your collection will determine what the strong type is. These types should expose strongly typed members.

#### Implement IDisposable correctly (FXCOP_IC) {#FXCOP_IC}

All IDisposable types should implement the Dispose pattern correctly.

#### Implement standard exception constructors (FXCOP_ISEC) {#FXCOP_ISEC}

Multiple constructors are required to correctly implement a custom exception. Missing constructors can make your exception unusable in certain scenarios. For example, the serialization constructor is required for handling exceptions in XML Web services.

#### Indexers should not be multidimensional (FXCOP_ISNBM) {#FXCOP_ISNBM}

Indexers (indexed properties) should use a single value (either an integer or string types) for indexing values. Multidimensional indexers can significantly reduce the usability of the library. For example, public object this [int index1, int index2] is a non-intuitive indexer.

#### Interface methods should be callable by child types (FXCOP_IMSBCBCT) {#FXCOP_IMSBCBCT}

Explicit method implementations are defined with private accessibility. Classes that derive from classes with explicit method implementations and choose to re-declare them on the class will not be able to call into the base class implementation unless the base class has provided an alternate method with appropriate accessibility. When overriding a base class method that has been hidden by explicit interface implementation, in order to call into the base class implementation, a derived class must cast the base pointer to the relevant interface. When calling through this reference, however, the derived class implementation will actually be invoked, resulting in recursion and an eventual stack overflow.

#### Lists are strongly typed (FXCOP_LAST) {#FXCOP_LAST}

IList implementations should also provide versions of the IList members that are strongly typed, namely they should specify types other than Object for method and property parameter and return types. Implement the interface members explicitly and make the strongly typed versions public. It is safe to ignore violations of this rule when you are implementing a new object-based collection, such as a linked list, where types based on your collection will determine what the strong type is. These types should expose strongly typed members.

#### Mark assemblies with AssemblyVersionAttribute (FXCOP_MAWAV) {#FXCOP_MAWAV}

Assemblies should use version numbers. The version number is considered part of an assembly's identity. Versioning is applied by means of the AssemblyVersion attribute.

#### Mark assemblies with CLSCompliantAttribute (FXCOP_MAWCC) {#FXCOP_MAWCC}

Assemblies should explicitly state their CLS compliance using the CLSCompliant attribute. An assembly without this attribute is not CLS-compliant. Assemblies, modules, and types can be CLS-compliant even if some parts of the assembly, module, or type are not CLS-compliant. The following rules apply: 1) If the element is marked CLSCompliant, any noncompliant members must have the CLSCompliant attribute present with its argument set to false. 2) A comparable CLS-compliant alternative member must be supplied for each member that is not CLS-compliant.

#### Mark assemblies with ComVisibleAttribute (FXCOP_MAWCV) {#FXCOP_MAWCV}

The System.Runtime.InteropServices.ComVisible attribute indicates whether COM clients can use the library. Good design dictates that developers explicitly indicate COM visibility. The default value for this attribute is 'true'. However, the best design is to mark the assembly ComVisible false, and then mark types, interfaces, and individual members as ComVisible true, as appropriate.

#### Mark attributes with AttributeUsageAttribute (FXCOP_MAWAU) {#FXCOP_MAWAU}

The AttributeUsage attribute specifies the targets that are valid for the attribute (see System.AttributeTargets), whether an attribute can appear on a target more than once, and whether the attribute is inheritable.

#### Mark enums with FlagsAttribute (FXCOP_MEWF) {#FXCOP_MEWF}

The enumeration appears to be made up of combinable flags. If this true, apply the Flags attribute to the enumeration.

#### Members should not expose certain concrete types (FXCOP_MSNECCT) {#FXCOP_MSNECCT}

Members should not expose certain concrete types.

#### Move P/Invokes to NativeMethods class (FXCOP_MTNMC) {#FXCOP_MTNMC}

This type contains members with the DllImport attribute. Members with the DllImport attribute should be contained in classes named NativeMethods, SafeNativeMethods, or UnsafeNativeMethods.

#### Nested types should not be visible (FXCOP_NTSNBV) {#FXCOP_NTSNBV}

Do not use public, protected or protected internal (Protected Friend) nested types as a way of grouping types. Use namespaces for this purpose. There are very limited scenarios where nested types are the best design. Also, nested type member accessibility is not clearly understood by all audiences. Enumerators are exempt from this rule.

#### Overload operator equals on overloading add and subtract (FXCOP_OOEOOAAS) {#FXCOP_OOEOOAAS}

When overloading the addition and subtraction operators, make sure that the equality operator (==) is defined in a consistent manner.

#### Override methods on comparable types (FXCOP_OMOCT) {#FXCOP_OMOCT}

Types that implement IComparable should redefine Equals and comparison operators to keep the meanings of less than, greater than, and equals consistent throughout the type.

#### Properties should not be write only (FXCOP_PSNBWO) {#FXCOP_PSNBWO}

Write-only properties usually indicate a flawed design.

#### Provide ObsoleteAttribute message (FXCOP_POAM) {#FXCOP_POAM}

The ObsoleteAttribute.Message property provides the text message displayed when an obsolete type or member is compiled. This message should provide information on the replacement for the obsolete element.

#### Replace repetitive arguments with params array (FXCOP_RRAWPA) {#FXCOP_RRAWPA}

Several instances of same-type arguments can be better implemented as a parameter array argument. Generally, if a member declares three or more arguments of the same type, consider using a parameter array.

#### Static holder types should be sealed (FXCOP_SHTSBS) {#FXCOP_SHTSBS}

Static holder types do not provide functionality that derived instances can extend. Inheriting from such a type indicates a flawed design.

#### Static holder types should not have constructors (FXCOP_SHTSNHC) {#FXCOP_SHTSNHC}

Instances of types that define only static members do not need to be created. Many compilers will automatically add a public default constructor if no constructor is specified. To prevent this, adding an empty private constructor may be required.

#### String URI overloads call System.Uri overloads (FXCOP_SUOCSUO) {#FXCOP_SUOCSUO}

If a method overloads another method by replacing a System.Uri parameter with a string, then the string overload should simply build a Uri object from the string, and pass the result to the string overload.

#### Types should not extend certain base types (FXCOP_TSNECBT) {#FXCOP_TSNECBT}

It is best not to extend some base types or to prefer extending better alternatives to those base types.

#### Types that own disposable fields should be disposable (FXCOP_TTODFSBD) {#FXCOP_TTODFSBD}

Types that declare disposable members should also implement IDisposable. If the type does not own any unmanaged resources, do not implement a finalizer on it.

#### Types that own native resources should be disposable (FXCOP_TTONRSBD) {#FXCOP_TTONRSBD}

Types that allocate unmanaged resources should implement IDisposable to allow callers to release those resources on demand. Failure to implement IDisposable can result in unmanaged resources being unavailable or underutilized.

#### URI parameters should not be strings (FXCOP_UPSNBS) {#FXCOP_UPSNBS}

If a parameter name contains "uri" or "url" or "urn", and it's typed as string, the parameter type should be changed to System.Uri, unless there is an overload method where the same parameter is typed as System.Uri.

#### URI properties should not be strings (FXCOP_URPRSHNOBEST) {#FXCOP_URPRSHNOBEST}

If a property name contains "uri" or "url" or "urn" and it's typed as string, it should be changed to System.Uri.

#### URI return values should not be strings (FXCOP_URVSNBS) {#FXCOP_URVSNBS}

If a function name contains "uri" or "url" or "urn" and the return type is string, the return type should be changed to System.Uri.

#### Use events where appropriate (FXCOP_UEWA) {#FXCOP_UEWA}

A method name suggestive of event functionality was encountered.

#### Use generic event handler instances (FXCOP_UGEHI) {#FXCOP_UGEHI}

Do not declare new delegates to be used as event handlers when targeting a version of the .NET Framework that supports generics. Use an instance EventHandler<T> instead.

#### Use generics where appropriate (FXCOP_UGWA) {#FXCOP_UGWA}

References passed to ref parameters must be the exact type of the parameter. Using generics enable the method for general use.

#### Use integral or string argument for indexers (FXCOP_UIOSAFI) {#FXCOP_UIOSAFI}

Indexers (indexed properties) should use either integer or string types for indexing values. These types are easy to use and commonly used for indexing data structures; using other types can significantly reduce the usability of the library. For example, public char this [int index] is the C# signature for the String type's indexer.

#### Use properties where appropriate (FXCOP_UPWA) {#FXCOP_UPWA}

Properties should be used instead of Get/Set methods in most situations. Methods are preferable to properties in the following situations: the operation is a conversion, is expensive or has an observable side-effect; the order of execution is important; calling the member twice in succession creates different results; a member is static but returns a mutable value; or the member returns an array.

### Microsoft.Globalization Rules

#### Avoid duplicate accelerators (FXCOP_ADA) {#FXCOP_ADA}

Controls should have unique accelerators for all items and sub-controls.

#### Do not hardcode locale specific strings (FXCOP_DNHLSS) {#FXCOP_DNHLSS}

Do not use string literals for system items that have locale-specific designations. Special system locations should be retrieved using provided API such as GetFolderPath. See the System.Environment.SpecialFolder enumeration for more information.

#### Normalize strings to uppercase (FXCOP_NSTU) {#FXCOP_NSTU}

Strings should be normalized to upper-case.

#### Set locale for data types (FXCOP_SLFDT) {#FXCOP_SLFDT}

In most cases, Locale should be explicitly set to CultureInfo.InvariantCulture on DataSet and DataTable instances. Upon creation of a DataSet or DataTable instance, the Locale is set to the current culture. In most cases, the Locale should be set to CultureInfo.InvariantCulture to guarantee proper sorting behavior in all cultures.

#### Specify CultureInfo (FXCOP_SCI) {#FXCOP_SCI}

If an overload exists that takes a CultureInfo argument, it should always be called in favor of an overload that does not. The CultureInfo type contains culture-specific information required for performing numeric and string operations, such as casing, formatting, and string comparisons. In scenarios where conversion and parsing behavior should never change between cultures, specify CultureInfo.InvariantCulture, otherwise, specify CultureInfo.CurrentCulture.

#### Specify IFormatProvider (FXCOP_SP) {#FXCOP_SP}

If an overload exists that takes an IFormatProvider argument, it should always be called in favor of an overload that does not. Some methods in the runtime convert a value to or from a string representation and take a string parameter that contains one or more characters, called format specifiers, which indicate how the value is to be converted. If the meaning of the format specifier varies by culture, a formatting object supplies the actual characters used in the string representation. In scenarios where sorting and comparison behavior should never change between cultures, specify CultureInfo.InvariantCulture, otherwise, specify CultureInfo.CurrentCulture.

#### Specify marshaling for P/Invoke string arguments (FXCOP_SMFSA) {#FXCOP_SMFSA}

When marshaling strings as ANSI (or as Auto on Win9x), some characters may be changed. If best-fit mapping is on, strings that appear different in Unicode will be marshaled to identical ANSI strings, which may lead to incorrect security decisions. Turning best-fit mapping off reduces this risk, as all characters without equivalents are mapped to '?'. Also, note that CharSet.Ansi is the default setting for all string marshaling; Unicode marshaling must be specified explicitly, either as a CharSet setting of DllImport or StructLayout, or as a MarshalAs attribute with a Unicode (or system-dependent) UnmanagedType.

#### Specify MessageBoxOptions (FXCOP_SMBO) {#FXCOP_SMBO}

In order to run correctly on right-to-left systems, all calls to MessageBox.Show should use the overload that specifies MessageBoxOptions as an argument. Programs should detect whether they are running on a right-to-left system at run-time and pass the appropriate MessageBoxOptions value in order to display correctly.

#### Specify StringComparison (FXCOP_SSC) {#FXCOP_SSC}

If an overload exists that takes a StringComparison argument, it should always be called in favor of an overload that does not.

#### Use ordinal StringComparison (FXCOP_UOSC) {#FXCOP_UOSC}

For non-linguistic comparisons, StringComparison.Ordinal or StringComparison.OrdinalIgnoreCase should be used instead of the linguistically-sensitive StringComparison.InvariantCulture.

### Microsoft.Interoperability Rules

#### Auto layout types should not be COM visible (FXCOP_ALTSNBCV) {#FXCOP_ALTSNBCV}

Types that are automatically ordered by the runtime should not be visible to COM. Types that are automatically laid out by the runtime do not have a guaranteed order between versions. This can break COM clients of those types. To ensure compatibility between versions, the type should be explicitly or sequentially ordered.

#### Avoid Int64 arguments for Visual Basic 6 clients (FXCOP_AIF) {#FXCOP_AIF}

COM visible types that might be accessed from Microsoft Visual Basic 6 clients should not expose methods with long arguments.

#### Avoid non-public fields in COM visible value types (FXCOP_ANFICVVT) {#FXCOP_ANFICVVT}

COM visible value types should not expose non-public instance fields. COM visible value types have their non-public instance fields exposed to COM clients.

#### Avoid overloads in COM visible interfaces (FXCOP_AOICVI) {#FXCOP_AOICVI}

Interfaces that are visible to COM should not define overloads, as they will be renamed and cannot be implemented by Visual Basic 6 clients. COM interfaces cannot contain overloaded methods.

#### Avoid static members in COM visible types (FXCOP_ASMICVT) {#FXCOP_ASMICVT}

COM does not support static methods.

#### Call GetLastError immediately after P/Invoke (FXCOP_CGLEIA) {#FXCOP_CGLEIA}

The last Win32 error can be reset as a result of making managed calls, due to P/Invokes called by the runtime itself. In order to ensure the correctness of the value returned by GetLastWin32Error, place the call immediately after the relevant platform invoke call in your code.

#### COM registration methods should be matched (FXCOP_CRMSBM) {#FXCOP_CRMSBM}

If a COM registration method is provided, an unregistration method must also be provided to reverse the operations performed by the registration method. COM registration functions are static methods within a type that are marked with the ComRegisterFunction attribute. All COM registration functions should be matched by a static method within the same type that is marked with the ComUnregisterFunction attribute. This method should reverse any operations completed by the registration function.

#### COM registration methods should not be visible (FXCOP_CRMSNBV) {#FXCOP_CRMSNBV}

COM registration and unregistration functions should be private or internal. COM registration and unregistration functions are called by the runtime when an assembly is registered or unregistered for use with COM. It is preferred that these methods are not externally visible.

#### COM visible type base types should be COM visible (FXCOP_CVTBTSBCV) {#FXCOP_CVTBTSBCV}

COM visible types should have an object hierarchy that is uniformly COM visible.

#### COM visible types should be creatable (FXCOP_CVTSBC) {#FXCOP_CVTSBC}

Types with no public default constructor are not COM-creatable. COM does not support parameterized object construction. A type was detected with a public parameterized constructor but no public default constructor. This type is not creatable by COM. If there is an alternate method for creating and passing object instances to COM clients (through a method on another type, for example), this might not be a problem.

#### Declare P/Invokes correctly (FXCOP_DC) {#FXCOP_DC}

P/Invoke methods should be declared correctly to ensure correct runtime behaviors.

#### Do not use AutoDual ClassInterfaceType (FXCOP_DNUADCIT) {#FXCOP_DNUADCIT}

Classes that use the ClassInterfaceType.AutoDual setting might break in later versions if you change the member layout of the class or base classes. ClassInterfaceType.AutoDual should only be used when the versioning limitations are known to be acceptable.

#### Mark boolean P/Invoke arguments with MarshalAs (FXCOP_MBAWMA) {#FXCOP_MBAWMA}

All boolean P/Invoke parameters and return types should be explicitly marked with the MarshalAs attribute. By default, the system will marshal all booleans as 4-byte UnmanagedType.Bool. This is the correct behavior for Win32 'BOOL' arguments but incorrect for C++ 'bool' arguments, which should be marshaled as 1-byte UnmanagedType.U1. For code maintainability reasons, always explicitly specify the marshaling information for boolean arguments and return values.

#### Mark ComSource interfaces as IDispatch (FXCOP_MCSIA) {#FXCOP_MCSIA}

COM source interfaces should be marked ComInterfaceType.InterfaceIsIDispatch. Visual Basic 6 clients cannot receive events with non-IDispatch interfaces.

#### P/Invoke entry points should exist (FXCOP_PEPSE) {#FXCOP_PEPSE}

Methods decorated with the DllImport attribute should point to existing unmanaged entry points. There is no compile-time check to ensure that methods decorated with the DllImport attribute actually exist in the referenced unmanaged dll. In the event that an entry point does not exist or the specified argument list is not correct, a runtime exception will be generated.

#### P/Invokes should not be visible (FXCOP_PSNBV) {#FXCOP_PSNBV}

Interop layer should not be public. The DllImport attribute should not be applied to publicly accessible members (public or protected).

### Microsoft.Maintainability Rules

#### Avoid excessive class coupling (FXCOP_AECC) {#FXCOP_AECC}

Types and methods with a high degree of class coupling can be difficult to maintain.

#### Avoid excessive complexity (FXCOP_AEC) {#FXCOP_AEC}

Method implementations that are exceedingly complex increase the challenge of understanding and maintaining code.

#### Avoid excessive inheritance (FXCOP_AVEXIN) {#FXCOP_AVEXIN}

Object hierarchies that are deeply nested increase the challenge of understanding and maintaining code.

#### Avoid unmaintainable code (FXCOP_AUC) {#FXCOP_AUC}

Types and methods with a high degree of class coupling, cyclomatic complexity and/or program length can be difficult to maintain.

#### Review misleading field names (FXCOP_RMFN) {#FXCOP_RMFN}

Review field names which, by convention, appear to indicate they are instance or static but, in fact, are not. This rule fires against instance fields which have names prefixed with "s_" and static fields which are prefixed with "m_".

#### Variable names should not match field names (FXCOP_VNSNMFN) {#FXCOP_VNSNMFN}

Instance field and variable names should not be identical within the same scope.

### Microsoft.Mobility Rules

#### Do not use idle process priority (FXCOP_DNUIPP) {#FXCOP_DNUIPP}

Do not set process priority to Idle. Processes with System.Diagnostics.ProcessPriorityClass.Idle will occupy the CPU when it would otherwise be idle, and thereby block standby.

#### Do not use timers that prevent power state changes (FXCOP_DNUTTPPSC) {#FXCOP_DNUTTPPSC}

Do not poll more often than or utilize timers that fire more frequently than once per second. Higher frequency periodic activity will keep the CPU busy and interfere with power-saving idle timers that turn off the display and hard disks.

### Microsoft.Naming Rules

#### Compound words should be cased correctly (FXCOP_CWSBCC) {#FXCOP_CWSBCC}

Avoid creating compound words from terms which exist in the dictionary as discrete terms. Do not create a compound word such as 'StopWatch' or 'PopUp'. These terms are recognized in the dictionary and should be cased as 'Stopwatch' and 'Popup'.

#### Do not name enum values 'Reserved' (FXCOP_DNNEVR) {#FXCOP_DNNEVR}

Avoid naming an enum value 'Reserved'. Adding 'Reserved' values will lead to a breaking change on removal when the value is actually used in a later version of the product.

#### Do not prefix enum values with type name (FXCOP_DNPEVWTN) {#FXCOP_DNPEVWTN}

The individual values that make up an enumeration type should not be prefixed with the type name.

#### Events should not have before or after prefix (FXCOP_ESNHBOAP) {#FXCOP_ESNHBOAP}

Use present and past tense for pre-events and post-events, instead of using 'Before' and 'After'. For example, use Closing and Closed rather than BeforeClose and AfterClose.

#### Flags enums should have plural names (FXCOP_FESHPN) {#FXCOP_FESHPN}

An enumeration marked with FlagsAttribute should have a plural name.

#### Identifiers should be cased correctly (FXCOP_ISBCC) {#FXCOP_ISBCC}

Type, namespace, and member identifiers are Pascal-cased. Parameter identifiers are camel-cased. Two letter acronyms within these identifiers should be upper-cased, for example, use System.IO instead of System.Io. Acronyms of three or more letters should be Pascal-cased, for example, use System.Xml instead of System.XML. The pascal-casing convention capitalizes the first letter of each word, as in BackColor. The camel-casing convention formats the first letter of the first word in lowercase and capitalizes the first letter of all subsequent words, as in backgroundColor. Although it may be common practice for some two letter acronyms to not be fully capitalized, violations of this rule should not be excluded for this reason. For example, 'DbConnection', is common but incorrect; use DBConnection. A violation of this rule might be required for compatibility with existing, non-managed symbol schemes. In general, however, these symbols should not be visible outside the assembly that uses them.

#### Identifiers should be spelled correctly (FXCOP_ISBSC) {#FXCOP_ISBSC}

The individual words that make up an identifier should not be abbreviated and should be spelled correctly. If this rule generates a false positive on a term that should be recognized, add the word to the FxCop custom dictionary.

#### Identifiers should differ by more than case (FXCOP_ISDBMTC) {#FXCOP_ISDBMTC}

Do not use names that require case sensitivity for uniqueness. Components must be fully usable from both case-sensitive and case-insensitive languages. Since case-insensitive languages cannot distinguish between two names within the same context that differ only by case, components must avoid this situation.

#### Identifiers should have correct prefix (FXCOP_ISHCP) {#FXCOP_ISHCP}

Prefix interface names with the letter 'I' to indicate that the type is an interface, as in IFormattable. Prefix generic type parameter names with the letter 'T' and provide them with descriptive names, as in Dictionary<TKey, TValue>, unless a single 'T' is completely self-explanatory, as in Collection<T>. Use Pascal casing for both interface and type parameter names. Use abbreviations sparingly. Do not use the underscore character. Do use similar names when defining a class/interface pair where the class is a standard implementation of the interface. The names should differ only by the letter I prefixed on the interface name, as with Component and IComponent.

#### Identifiers should have correct suffix (FXCOP_ISHCS) {#FXCOP_ISHCS}

Types that extend certain base types have specified name suffixes. Types that extend Attribute, for example, should be suffixed in 'Attribute', as in ObsoleteAttribute. This rules checks types that extend several base types, including Attribute, Exception, EventArgs, IMembershipPermission, Stream, and others.

#### Identifiers should not contain type names (FXCOP_ISNCTN) {#FXCOP_ISNCTN}

Avoid using language-specific types name in parameters and members and data type identifiers in parameters. Types names might not be intuitive for all developers. It is recommended that you select a generic name, such as 'value', instead. If this is not sufficient, be sure to use the type name as it is defined in the .NET Framework Library and avoid language-specific type names completely. Some examples of C#-specific type names are 'float' (use 'Single' if a generic name is not sufficient), and 'ulong' (use 'UInt64' if a generic name is not sufficient).

#### Identifiers should not contain underscores (FXCOP_ISNCU) {#FXCOP_ISNCU}

Do not use underscores when specifying identifiers. Some generated Visual Studio identifiers for applications contain underscore characters. Underscore characters should generally be avoided in public identifiers.

#### Identifiers should not have incorrect prefix (FXCOP_ISNHIP) {#FXCOP_ISNHIP}

Do not use 'C' as a prefix for type names. Do not use any prefix for naming types. Consider using the name of the base class as the suffix when naming derived types. For example: ApplicationException is a kind of Exception. SerializableAttribute is a kind of Attribute.

#### Identifiers should not have incorrect suffix (FXCOP_ISNHIS) {#FXCOP_ISNHIS}

Types that do not extend certain base types should not use reserved name suffixes. Types and members should not use 'Ex' or 'New' to distinguish them from an earlier version of the same API, instead, use a numeric suffix such as '2' or provide a more meaningful suffix. Concrete type implementations and members should not end 'Impl'. Members instead, should either consider using the suggested alternate 'Core' in replacement of 'Impl' or avoid any suffix at all.

#### Identifiers should not match keywords (FXCOP_ISNMK) {#FXCOP_ISNMK}

Identifiers which conflict with reserved language keywords should be avoided. Using a reserved keyword as an identifier makes it harder for consumers in other languages to use your API.

#### Only FlagsAttribute enums should have plural names (FXCOP_OFESHPN) {#FXCOP_OFESHPN}

Plural names indicate that the values of the enumeration can be combined. For example, an enumeration named 'Day' indicates a single day, and an enumeration named 'Days' indicates multiple days. Enumeration values should be combined using the bit-wise OR operator only if the Flags attribute is present on the enumeration.

#### Parameter names should match base declaration (FXCOP_PNSMBD) {#FXCOP_PNSMBD}

For usability reasons, parameter names in overridden methods should match those of the base declaration.

#### Parameter names should not match member names (FXCOP_PNSNMMN) {#FXCOP_PNSNMMN}

Parameter names should be distinct from member names.

#### Property names should not match get methods (FXCOP_PNSNMGM) {#FXCOP_PNSNMGM}

A Get method was found with the same name as a property. Get methods and properties should have names that clearly distinguish their function. See the design guidelines for information regarding choosing properties over methods.

#### Resource string compound words should be cased correctly (FXCOP_RSCWSBCC) {#FXCOP_RSCWSBCC}

Avoid creating compound words from terms which exist in the dictionary as discrete terms. Do not create a compound word such as 'StopWatch' or 'PopUp'. These terms are recognized in the dictionary and should be cased as 'Stopwatch' and 'Popup'.

#### Resource strings should be spelled correctly (FXCOP_RSSBSC) {#FXCOP_RSSBSC}

The individual words that make up a resource string should not be abbreviated and should be spelled correctly. If this rule generates a false positive on a term that should be recognized, add the word to the FxCop custom dictionary.

#### Type names should not match namespaces (FXCOP_TNSNMN) {#FXCOP_TNSNMN}

Identifiers which conflict in whole or in part with namespace names should be avoided. Names that describe the purpose or contents of a type are preferred.

#### Use preferred terms (FXCOP_UPT) {#FXCOP_UPT}

Use preferred terms over deprecated alternates.

### Microsoft.Performance Rules

#### Avoid excessive locals (FXCOP_AEL) {#FXCOP_AEL}

Method implementations should not contain more than 64 local variables. In order for the run-time to enregister local variables most efficiently, there should be 64 or fewer of them. Enregistering based on flow analysis will not occur for locals in excess of 64, which may result in slower performance.

#### Avoid uncalled private code (FXCOP_AUPC) {#FXCOP_AUPC}

There is uncalled code that is not externally visible and is not a known runtime entry point. If this violation fires in error, please send a problem report to the Visual Studio Code Analysis team.

#### Avoid uninstantiated internal classes (FXCOP_AUIC) {#FXCOP_AUIC}

An internal class was detected that is apparently never instantiated. This rule does not attempt to detect late-bound creation and will generate false positives if instances of a type are only created in this way (for example, by means of Activator.CreateInstance or by passing the type as an argument to a TypeConverter constructor).

#### Avoid unsealed attributes (FXCOP_AUA) {#FXCOP_AUA}

Seal attribute types for improved performance. Sealing attribute types speeds up performance during reflection on custom attributes.

#### Avoid unused private fields (FXCOP_AUPF) {#FXCOP_AUPF}

Private fields were detected that do not appear to be accessed within the assembly. If this violation fires in error, please send a problem report to the Visual Studio Code Analysis team.

#### Do not cast unnecessarily (FXCOP_DNCU) {#FXCOP_DNCU}

Avoid duplicate casts where possible, since there is a cost associated with them.

#### Initialize reference type static fields inline (FXCOP_IRTSFI) {#FXCOP_IRTSFI}

Static fields should be initialized when declared. Initializing static data in explicit static constructors results in less performant code.

#### Mark assemblies with NeutralResourcesLanguageAttribute (FXCOP_MAWNRL) {#FXCOP_MAWNRL}

The NeutralResourcesLanguage attribute informs the ResourceManager of the language used to render the neutral culture's resources for an assembly. When looking up resources in the same culture as the neutral resources language, the ResourceManager automatically uses the resources located in the main assembly, instead of searching for a satellite assembly with the current user interface culture for the current thread. This will improve lookup performance for the first resource you load and can reduce your working set.

#### Mark members as static (FXCOP_MMAS) {#FXCOP_MMAS}

Methods which do not access instance data or call instance methods can be marked as static (Shared in Visual Basic). After doing so, the compiler will emit non-virtual call sites to these members which will prevent a check at runtime for each call that ensures the current object pointer is non-null. This can result in a measurable performance gain for performance-sensitive code. In some cases, the failure to access the current object instance represents a correctness issue.

#### Override equals and operator equals on value types (FXCOP_OEAOEOVT) {#FXCOP_OEAOEOVT}

The default System.ValueType implementation might not perform as well as a custom implementation.

#### Prefer jagged arrays over multidimensional (FXCOP_PJAOM) {#FXCOP_PJAOM}

Multidimensional arrays can have a negative impact on performance. Use a jagged array if possible.

#### Properties should not return arrays (FXCOP_PSNRA) {#FXCOP_PSNRA}

Properties that return arrays are prone to code inefficiencies. Consider using a collection or making this a method. See the design guidelines for more information.

#### Remove empty finalizers (FXCOP_REF) {#FXCOP_REF}

Finalizers should be avoided where possible, to avoid the additional performance overhead involved in tracking object lifetime.

#### Remove unused locals (FXCOP_RUL) {#FXCOP_RUL}

Remove locals that are not used or are only assigned to in method implementations.

#### Test for empty strings using string length (FXCOP_TFESUSL) {#FXCOP_TFESUSL}

To test for empty strings, check if String.Length is equal to zero. Constructs such as "".Equals(someString) and String.Empty.Equals(someString) are less efficient than testing the string length. Replace these with checks for someString.Length == 0.

#### Use literals where appropriate (FXCOP_ULWA) {#FXCOP_ULWA}

Prefer literals over InitOnly fields if values do not have to be calculated at runtime.

### Microsoft.Portability Rules

#### P/Invoke declarations should be portable (FXCOP_PDSBP) {#FXCOP_PDSBP}

This rule fires on either of the following scenarios: The return value or parameter is typed as a fixed-size integer when it should be typed as an IntPtr or the return value or parameter is typed as an IntPtr when it should be typed as a fixed-size integer.

#### Use only API from targeted framework (FXCOP_UOAFTF) {#FXCOP_UOAFTF}



#### Value type fields should be portable (FXCOP_VTFSBP) {#FXCOP_VTFSBP}

Structures with explicit layout containing misaligned fields cause crashes on 64-bit platforms.

### Microsoft.Reliability Rules

#### Avoid calling problematic methods (FXCOP_ACPM) {#FXCOP_ACPM}

Avoid making unnecessary and potentially dangerous method calls.

#### Do not lock on objects with weak identity (FXCOP_DNLOOWWI) {#FXCOP_DNLOOWWI}

Don't take locks on objects that may bleed across AppDomains or that don't have a strong identity.

#### Do not treat fibers as threads (FXCOP_DNTFAT) {#FXCOP_DNTFAT}

Do not assume a managed thread is a Win32 thread - it could be a fiber. The runtime will run managed threads as fibers on top of real threads owned by SQL Server. These threads will be shared across AppDomains and even databases in the SQL Server process. Using managed thread local storage will work, but you may not use unmanaged thread local storage or assume your code will run on the current OS thread again. Do not change settings like the thread's locale. Do not call CreateCriticalSection or CreateMutex via P/Invoke because they require the thread that enters a lock also exit the lock. Since this will not be the case when using fibers, Win32 critical sections and mutexes will be useless in SQL Server.
You may safely use most of the state on a managed System.Thread object, including managed thread local storage and the thread's current UI culture. For programming model reasons, you will not be able to change a thread's current culture when running in SQL Server though (this will be enforced through a new permission).

#### Remove calls to GC.KeepAlive (FXCOP_RCTA) {#FXCOP_RCTA}

If converting to SafeHandle usage, remove all calls to GC.KeepAlive(object). Classes relying on SafeHandle do not require calls to GC.KeepAlive, and unnecessary calls can make code harder to maintain.

#### Use SafeHandle to encapsulate native resources (FXCOP_USHTENR) {#FXCOP_USHTENR}

Use of IntPtr in managed code may indicate a potential security and reliability problem. All uses of IntPtr must be reviewed to determine whether use of a SafeHandle (or similar technology) is required in its place. Problems will occur if the IntPtr represents some native resource (memory, file handle, socket etc.) that managed code is considered to own. I.e. managed code is expected to in some way release the resource and failure to do so would cause resource leakage. In such scenarios security or reliability problems will also exist if multithreaded access is allowed to the IntPtr and a means of releasing the resource represented by the IntPtr. These problems involve recycling of the IntPtr value on resource release while simultaneous use of the resource is being made on another thread, leading to race conditions where one thread can read or write data associated with the wrong resource. For example, if your type stores an OS handle as an IntPtr and allows users to call both Close and any other method using that handle simultaneously (without some kind of synchronization), your code has a handle recycling problem, which causes data corruption and often a security vulnerability. SafeHandle (and its sibling class CriticalHandle) provide a mechanism for encapsulating a native handle to a resource so that such threading problems can be avoided (along with other issues such as the need to carefully control the lifetime of managed objects that contain a copy of the native handle over calls to native methods; ie, you can often remove calls to GC.KeepAlive). There are performance overheads implicit in using SafeHandle (and, to a lesser degree, CriticalHandle) which can often be mitigated through careful design.

### Microsoft.Security Rules

#### APTCA methods should only call APTCA methods (FXCOP_AMSOCAM) {#FXCOP_AMSOCAM}

Methods with the AllowPartiallyTrustedCallersAttribute that call methods without that attribute might unintentionally expose functionality to partially trusted code. When a method has the AllowPartiallyTrustedCallersAttribute set, it is callable by partially trusted code. If it in turn calls methods without the attribute, a partially trusted caller is, in effect, being allowed to execute code that requires full trust. Depending on what full trust code is called and what parameter values are passed through from the partially trusted caller, malicious code might be able to exploit this security weakness.

#### APTCA types should only extend APTCA base types (FXCOP_ATSOEABT) {#FXCOP_ATSOEABT}

Types with the AllowPartiallyTrustedCallersAttribute that extend types without that attribute might unintentionally expose functionality in the base type to partially trusted callers. When a type has the AllowPartiallyTrustedCallersAttribute set, it is callable by partially trusted code. If the base type does not have this attribute, it requires callers to be fully trusted. If the derived type exposes protected members in the base type, the base type's data is made accessible to partially trusted callers, creating an exploitable security weakness.

#### Array fields should not be read only (FXCOP_AFSNBRO) {#FXCOP_AFSNBRO}

Read-only fields that reference arrays might not give the intended effect. Setting a field which references an array to read-only prevents the value of the field from being changed. Note that elements in the array can be changed. You can ignore this violation if protecting the contents of the array is not a concern.

#### Call GC.KeepAlive when using native resources (FXCOP_CAWUNR) {#FXCOP_CAWUNR}

If a method uses an IntPtr or UIntPtr field in a class with a finalizer and does not call GC.KeepAlive, a race condition might be introduced.

#### Catch non-CLSCompliant exceptions in general handlers (FXCOP_CNCCEIGH) {#FXCOP_CNCCEIGH}

Exception handlers which are truly intended to catch all exceptions should handle non-CLSCompliant exceptions if there is a possibility one can be raised. If possible, catch handlers should only catch specific exceptions or exception base types. In circumstances where a handler is required to catch all exceptions (e.g., when a try block wraps arbitrary plug-in code), the handler should also include a generic catch handler (in C#, catch{ ... }) to handle non-CLSCompliant exceptions. It is possible to raise non-CLSCompliant exceptions by modifying and recompiling IL.

#### Default constructors must be at least as critical as base type default constructors (FXCOP_DCMHCT) {#FXCOP_DCMHCT}

On CoreCLR, if a base type has a public or protected non-transparent default constructor than the derived type must obey default constructor inheritance rules.  The derived type must also have a default constructor and that constructor must be at least as critical as the base type's default constructor.  If the base type's default constructor is safe-critical, the derived type's default constructor must be safe-critical or critical.  If the base type's default constructor is critical, then the derived type's default constructor must also be critical.

#### Delegates must bind to methods with consistent transparency (FXCOP_DMBWCT) {#FXCOP_DMBWCT}

Delegate types and the methods that they bind to must have consistent transparency.  Transparent and safe-critical delegates may only bind to other transparent or safe-critical methods.  Similarly, critical delegates may only bind to critical methods.  These binding rules ensure that the only code which can invoke a method via a delegate could have also invoked the same method directly.  It prevents, for instance, transparent code from calling critical code directly via a transparent delegate.

#### Do not declare read only mutable reference types (FXCOP_DNDROMRT) {#FXCOP_DNDROMRT}

A read-only declaration for a mutable reference type does not prevent the field's instance data from being modified. For example, a read-only StringBuilder field declaration does not make sense, since the data encapsulated by the StringBuilder can be modified using the read-only reference.

#### Do not indirectly expose methods with link demands (FXCOP_DNIEMWLD) {#FXCOP_DNIEMWLD}

Do not wrap a method protected by a LinkDemand with a method that does not perform a security check. A LinkDemand checks the permissions of the immediate caller rather than checking the permissions of all callers in the call stack. In this case, the permissions of the wrapper method will be checked. If the wrapper method does not, itself, check the permissions of callers higher in the call stack, malicious code might be able to execute the wrapped function even though it lacks permission to do so.

#### Fields with critical types should be security critical. (FXCOP_FWCTSBC) {#FXCOP_FWCTSBC}

Fields which have a critical type cannot be used from transparent code, and should therefore be marked security critical.  This makes it obvious to the users of the field that they must also be critical.  Additionally, such fields frequently store sensitive information such as a handle value.

#### Level 2 assemblies should not contain LinkDemands (FXCOP_SRSLSNBPWLD) {#FXCOP_SRSLSNBPWLD}

LinkDemands are deprecated in the level 2 security rule set.  Instead of using LinkDemands to enforce JIT time security, SecurityCritical methods, types, and fields should be used instead.

#### Members should not have conflicting transparency annotations (FXCOP_TASNC) {#FXCOP_TASNC}

Transparency attributes are applied from larger scopes inward.  For instance, if a type is marked as entirely security critical, than all methods introduced by the type will also be security critical.  Members should not have transparency annotations which conflict with larger scoped annotations, as these smaller scoped annotations will be ignored by the CLR and can be misleading during a code review.  Methods not introduced by their type, such as virtual methods being overridden from a base type or interface methods being implemented, do have their annotations considered under the level 2 security rule set and are not considered by this rule.

#### Method security should be a superset of type (FXCOP_MSSBOT) {#FXCOP_MSSBOT}

A method has security set at both the type and method levels. This might not have the intended effect. Security actions on the type level are overridden by security actions on the method level. When employing both type-level and method-level security, type-level security actions that are not also on the method will be ignored when the method executes.

#### Methods must keep consistent transparency when overriding base methods (FXCOP_MMOWCT) {#FXCOP_MMOWCT}

Transparency visibility must be preserved between overriding methods and the methods that are being overridden.  If the virtual method being overridden or interface method being implemented is security safe-critical or security transparent, then the overriding method must also be either security safe-critical or security transparent.  Similarly, if the method being overridden is security critical, the overriding method must be security critical.

#### Override link demands should be identical to base (FXCOP_OLDSBITB) {#FXCOP_OLDSBITB}

If a virtual method has a LinkDemand, in many cases, so should any override of it, and if an override has a LinkDemand, so should the overridden virtual method. Because it is possible to call any of the overrides of a virtual method explicitly, they should all have the same LinkDemand status or, if not, should be reviewed. This also applies to LinkDemand security checks for methods that part of an interface implementation, because the caller might use an interface-typed reference to access the method.

#### P/Invoke declarations should not be safe-critical. (FXCOP_PSNBSC) {#FXCOP_PSNBSC}

Since P/Invokes may not be called by transparent code, they should not be marked as safe-critical methods.  Doing so can lead to confusion on the part of developers who may believe that their transparent code should be able to call the P/Invoke method since it is marked safe-critical.

#### Pointers should not be visible (FXCOP_POSHNOBEVI) {#FXCOP_POSHNOBEVI}

IntPtr and UIntPtr fields should be declared as private. Exposing non-private pointers can cause a security weakness.

#### Review declarative security on value types (FXCOP_RDSOVT) {#FXCOP_RDSOVT}

A Demand or a LinkDemand on a structure does not prevent creation of an instance of that structure.

#### Review deny and permit only usage (FXCOP_RDAPOU) {#FXCOP_RDAPOU}

Use of Deny or PermitOnly should be carefully reviewed. Use of Deny or PermitOnly should be carefully considered, as they are not useful in some cases. For example, permissions that are path-based (like FileIOPermission and RegistryPermission) should not be used with Deny, because different paths might actually point to the same location. If callers are granted the right to assert permissions by the security policy, then they can terminate a stack walk before it reaches your Deny or PermitOnly. If a caller has been granted powerful permissions (such as the ability to call unmanaged code), then calling Deny or PermitOnly cannot truly stop it from doing whatever it chooses. Also consider that Deny and PermitOnly do not affect a LinkDemand. For instance, if you deny some permission P and call a method with a LinkDemand for P, the Deny will not affect the result of the LinkDemand.

#### Review imperative security (FXCOP_RIS) {#FXCOP_RIS}

Use of imperative demands can lead to unforeseen security problems. The values used to construct a permission should not change within the scope of the demand call. For some components the scope spans from the demand call to end of the method; for others it spans from the demand call until the component is finalized. If the values used to construct the permission are fields or properties, they can be changed within the scope of the demand call. This can lead to race conditions, mutable read-only arrays, and problems with boxed value types.

#### Review SuppressUnmanagedCodeSecurityAttribute usage (FXCOP_RSUCSU) {#FXCOP_RSUCSU}

Calling a method with the SuppressUnmanagedCodeSecurityAttribute applied to it can create a security weakness. Unmanaged code security checks ensure that all callers in the call stack have permission to execute unmanaged code. Disabling code security for P/Invoke methods allows callers that do not have this permission to breach security. This is acceptable only if the code is completely harmless, or callers have no way to pass arbitrary arguments through to the unmanaged code.

#### Review visible event handlers (FXCOP_RVEH) {#FXCOP_RVEH}

It appears that an event handler is externally visible or that an EventArgs parameter is being exposed in a visible method decorated with a security demand. There can be problems exposing sensitive functionality in an event handler function; the security demand might not do what you expect.

#### Seal methods that satisfy private interfaces (FXCOP_SMTSPI) {#FXCOP_SMTSPI}

Externally visible types that implement non-public interfaces should not be extensible. Types that extend public types with non-public interfaces can override interface members. This can compromise object behavior or create a security vulnerability.

#### Secure asserts (FXCOP_SA) {#FXCOP_SA}

Asserting a security permission without performing any security checks can leave an exploitable security weakness in your code. A security stack walk stops when a security permission is asserted. If you assert a permission without performing any checks on the caller, the caller might be able to indirectly execute code using your permissions. Asserts without security checks are only permissible when you are certain that the assert cannot be used in a harmful fashion, namely, if the code you call is harmless, or users have no way to pass arbitrary information to code that you call.

#### Secure serialization constructors (FXCOP_SESECO) {#FXCOP_SESECO}

Serializable types that have a constructor protected by a security demand must apply the same security demands to the serialization constructor. Apply the demand using declarative security.

#### Secured types should not expose fields (FXCOP_STSNEF) {#FXCOP_STSNEF}

Fields must be secured with a security check other than LinkDemand.

#### Security critical constants should be transparent (FXCOP_CSBT) {#FXCOP_CSBT}

Compilers inline accesses to constants, and as such transparency enforcement is not done for them since there is no runtime access to the field.  These fields should be security transparent so that code reviewers do not assume that transparent code cannot access the constant.

#### Security critical types may not participate in type equivalence (FXCOP_CTMNPITE) {#FXCOP_CTMNPITE}

Type equivalence requires that all participating types, as well as all methods and fields within those types, are transparent or security safe-critical.  The CLR will fail to load any type which violates this rule.

#### Static constructors should be private (FXCOP_SCSBP) {#FXCOP_SCSBP}

Non-private static constructors can cause unexpected behaviors, particularly when executed multiple times. This violation can occur if a type declares static data but has not explicitly  declared a static constructor. In this case, some compilers will generate an externally visible static constructor.

#### Transparent code may not use security asserts (FXCOP_TMMNUSA) {#FXCOP_TMMNUSA}

Transparent code may not use security asserts, since asserting permissions can result in elevating the effective permissions of the call stack.  Transparent code which attempts to assert will receive an InvalidOperationException at runtime.

#### Transparent code may not use security critical attributes (FXCOP_TCMNUCA) {#FXCOP_TCMNUCA}

Transparent code must not use security critical attributes.  This includes using security critical constructors, properties, or fields of attributes.  Violations of this rule will result in an exception when code attempts to retrieve the custom attributes from the transparent target.

#### Transparent code must not reference security critical items (FXCOP_TMMNRCC) {#FXCOP_TMMNRCC}

Transparent code cannot refer to security critical methods, types, or fields.  At runtime these references will result in MemberAccessExceptions or TypeLoadExceptions.

#### Transparent code should not be protected with LinkDemands (FXCOP_TMSNBPWLD) {#FXCOP_TMSNBPWLD}

Security transparent code should not be responsible for verifying the security of an operation, and therefore should not be protected from partial trust callers with LinkDemands.

#### Transparent code should not load assemblies from byte arrays (FXCOP_TMSNLAFBA) {#FXCOP_TMSNLAFBA}

Assemblies loaded from byte arrays inherit the grant set of the loading assembly.  Since this means that the loaded assembly may be fully trusted, any calls to load from byte array from trusted code should be reviewed to ensure that it is secure.  Transparent code is not subjected to the same audit scrutiny as critical code, and therefore should not load assemblies from byte arrays.

#### Transparent methods may not use the HandleProcessCorruptingExceptions attribute (FXCOP_TMMNHPCE) {#FXCOP_TMMNHPCE}

The HandleProcessCorruptingExceptions attribute may only be used by security critical methods, and will not be honored if it is applied to a transparent method.

#### Transparent methods must contain only verifiable IL (FXCOP_TMMBV) {#FXCOP_TMMBV}

Transparent code must be fully verifiable.  This rule looks for any use of pointer types to check for unverifiable code, however it is not a complete verifier and PEVerify / transparent must be run on assemblies to ensure that all of their transparent code is verifiable.

#### Transparent methods must not call into native code (FXCOP_TMMNCNC) {#FXCOP_TMMNCNC}

Transparent code may not call native code directly.  This rule looks for any transparent code which calls a method stub (such as a P/Invoke declaration) which is really a direct call into native code.

#### Transparent methods must not call methods with the SuppressUnmanagedCodeSecurity attribute (FXCOP_TMMNCSUCSM) {#FXCOP_TMMNCSUCSM}

P/Invoke and COM interop methods with the SuppressUnmanagedCodeSecurity attribute result in a LinkDemand being done against the calling method.  Since security transparent code may not satisfy LinkDemands, it may also not call methods with SuppressUnmanagedCodeSecurity either on the method itself or on the type containing the method.

#### Transparent methods must not satisfy LinkDemands (FXCOP_TMMNSLD) {#FXCOP_TMMNSLD}

Satisfying a LinkDemand is a security sensitive operation which can cause unintentional elevation of privilege.  Security transparent code must not satisfy LinkDemands, since it is not subject to the same security audit requirements as security critical code.  Transparent methods is security rule set level 1 assemblies will cause all LinkDemands they satisfy to be converted to full demands at runtime, which can cause performance problems.  In security rule set level 2 assemblies, transparent methods will fail to JIT if they attempt to satisfy a LinkDemand.

#### Transparent methods should not be decorated with the SuppressUnmanagedCodeSecurityAttribute (FXCOP_TMSNUSUCS) {#FXCOP_TMSNUSUCS}

Methods decorated with the SuppressUnmanagedCodeSecurity attribute have an implicit LinkDemand placed upon all of their callers.  This LinkDemand requires that the calling code be security critical.  Marking the method which uses SuppressUnmanagedCodeSecurity as security critical makes this requirement more obvious for callers of the method.

#### Transparent methods should not use security demands (FXCOP_TMSND) {#FXCOP_TMSND}

Security transparent code should not be responsible for verifying the security of an operation, and therefore should not demand permissions.  Any code which is performing security checks, such as security demands, should be safe-critical instead.

#### Type link demands require inheritance demands (FXCOP_TLDRID) {#FXCOP_TLDRID}

Unsealed types secured by a LinkDemand should also specify an InheritanceDemand. Without an InheritanceDemand, the link demand can be circumvented by overriding a method in a derived class.

#### Types must be at least as critical as their base types and interfaces (FXCOP_TMBALACABT) {#FXCOP_TMBALACABT}

While any type may derive from a transparent type or interface, restrictions apply as to the types that can inherit from or implement safe-critical or critical types.  Only safe-critical or critical types may derive from or implement safe-critical interfaces and base types.  Only critical types may derive from or implement critical interfaces and base types.

#### Wrap vulnerable finally clauses in outer try (FXCOP_WVFCIOT) {#FXCOP_WVFCIOT}

Finally clauses that restore security-related state should be wrapped in an outer try block. This will prevent an exception filter further up the stack from executing before a secure environment can be restored. Exception filters that run code expressions in the first pass after the guarded try blocks and before the associated finally block represent a possible security vulnerability. Examples of vulnerable functionality in finally clauses that should be protected against this include: calls to RevertAssert on an asserted permission, undoing a temporary impersonation, reversing an internal flag that bypasses a security check, and restoring the culture associated with a thread.

### Microsoft.Usage Rules

#### Attribute string literals should parse correctly (FXCOP_ASLSPC) {#FXCOP_ASLSPC}

Literal strings used as attribute parameters that represent URLs, version numbers, or GUIDs, should have the appropriate format.

#### Call base class methods on ISerializable types (FXCOP_CBCMOT) {#FXCOP_CBCMOT}

Derived ISerializable types must call the base class magic constructor and the base class GetObjectData method.

#### Call GC.SuppressFinalize correctly (FXCOP_CFC) {#FXCOP_CFC}

Call GC.SuppressFinalize to suppress finalization of your instance once Dispose has been called. Objects that implement IDisposable should call SuppressFinalize from the IDisposable.Dispose method to prevent the garbage collector from calling Object.Finalize on an object that does not require it.

#### Collection properties should be read only (FXCOP_CPSBRO) {#FXCOP_CPSBRO}

Properties that return collections should be read-only so that users cannot entirely replace the backing store. Users can still modify the contents of the collection by calling relevant methods on the collection. Note that the XmlSerializer class has special support for deserializing read-only collections. See the XmlSerializer overview for more information.

#### Disposable fields should be disposed (FXCOP_DFSBD) {#FXCOP_DFSBD}

If a type that implements IDisposable owns fields that also implement IDisposable, the encapsulating type's Dispose() implementation should call Dispose() on each disposable field.

#### Disposable types should declare finalizer (FXCOP_DTSDF) {#FXCOP_DTSDF}

If a type implements a Dispose method and has unmanaged resources, it should provide a Finalize method in case Dispose is not explicitly called. The runtime calls the Finalize method or destructor of an object prior to reclaiming its managed resources in a process known as garbage collection. The Finalize method should free any unmanaged resources before they become inaccessible.

#### Do not call overridable methods in constructors (FXCOP_DNCOMIC) {#FXCOP_DNCOMIC}

Virtual methods defined on the class should not be called from constructors. If a derived class has overridden the method, the derived class version will be called (before the derived class constructor is called).

#### Do not decrease inherited member visibility (FXCOP_DNDIMV) {#FXCOP_DNDIMV}

It is incorrect to override a public method from an inherited class with a private implementation, unless the type is sealed or the method is marked final. It is considered bad form to hide a method signature halfway down an inheritance tree.

#### Do not ignore method results (FXCOP_DNIMR) {#FXCOP_DNIMR}

The result of methods that return new instances of strings should be assigned to a variable and subsequently used. If the result of a method that creates a new object, such as String.ToLower(), is not assigned to a variable, the call is wasted.

#### Do not mark enums with FlagsAttribute (FXCOP_DNMEWF) {#FXCOP_DNMEWF}

The enumeration does not appear to contain a consistent set values that can be combined using  the OR (|) and AND (&amp;amp;) operators. Using the Flags attribute on an enumeration suggests that the enumeration values are meant to be combined using the AND and OR operators. Typically, a flags enumeration uses values that are either powers of two, or combine other values that are powers of two.

#### Do not mark serviced components with WebMethod (FXCOP_DNMSCWWM) {#FXCOP_DNMSCWWM}

Types that extend ServicedComponent should not have the WebMethod attribute applied to members. Marking members of types that extend ServicedComponent with WebMethod is not a supported scenario.

#### Do not raise exceptions in exception clauses (FXCOP_DNREIEC) {#FXCOP_DNREIEC}

Raising exceptions in exception clauses greatly increases the difficulty of debugging. Exceptions raised in finally and fault clauses will hide any exceptions raised in the corresponding try block. If an exception is raised in a filter, it is ignored and treated as if the filter had returned false.

#### Do not raise reserved exception types (FXCOP_DNRRET) {#FXCOP_DNRRET}

User code should not create and raise exceptions of certain types that are reserved by the runtime or which are of a too general exception type. Exception types that are too general include Exception, SystemException, and ApplicationException. Exception types that are reserved by the runtime include ThreadAbortException, OutOfMemoryException, ExecutionEngineException, and IndexOutOfRangeException.

#### Do not ship unreleased resource formats (FXCOP_DNSURF) {#FXCOP_DNSURF}

Resources generated by pre-release versions of the .NET Framework might contain incorrect or incomplete type references. Pre-release versions of the .NET Framework can generate partial or incomplete references to types. Resources built with pre-release software are not guaranteed to work correctly in released versions.

#### Finalizers should be protected (FXCOP_FSBP) {#FXCOP_FSBP}

Finalize methods should be declared as protected.

#### Finalizers should call base class finalizer (FXCOP_FSCBCF) {#FXCOP_FSCBCF}

The Finalize method should call its base class' Finalize method. This is done automatically with the C# destructor syntax.

#### Implement ISerializable correctly (FXCOP_IMCO) {#FXCOP_IMCO}

If a type is assignable to ISerializable, it should implement GetObjectData. For unsealed types, the GetObjectData method should be callable and overridable by derived types.

#### Implement serialization constructors (FXCOP_ISC) {#FXCOP_ISC}

The constructor signature accepts the same arguments as ISerializable.GetObjectData, namely, a SerializationInfo instance and a StreamingContext instance. The constructor should be protected for non-sealed classes and private for sealed classes. Failure to implement a serialization constructor will cause deserialization to fail, and throw a SerializationException.

#### Implement serialization methods correctly (FXCOP_ISMC) {#FXCOP_ISMC}

Methods marked with OnSerializing, OnSerialized, OnDeserializing, or OnDeserialized, must be non-generic, private, return void (Sub in Visual Studio) and take a single parameter of type StreamingContext.

#### Initialize value type static fields inline (FXCOP_IVTSFI) {#FXCOP_IVTSFI}

Do not declare explicit static constructors on value types. Initializing static data in explicit static constructors results in a value type that is not marked in metadata as 'beforefieldinit'. In this case, the static constructor is not always guaranteed to be called before instance members on the value type are called.

#### Instantiate argument exceptions correctly (FXCOP_IAEC) {#FXCOP_IAEC}

String arguments passed to constructors of ArgumentException and its derived types should be correct. Types derived from ArgumentException have inconsistent constructor overloads with respect to the message and paramName parameters as compared to ArgumentException.

#### Mark all non-serializable fields (FXCOP_MANSF) {#FXCOP_MANSF}

All fields that cannot be serialized directly should have the NonSerializedAttribute. Types that have the SerializableAttribute should not have fields of types that do not have the SerializableAttribute unless the fields are marked with the NonSerializedAttribute.

#### Mark ISerializable types with SerializableAttribute (FXCOP_MTWS) {#FXCOP_MTWS}

The System.Runtime.Serialization.ISerializable interface allows the type to customize its serialization, while the Serializable attribute enables the runtime to recognize the type as being serializable.

#### Mark Windows Forms entry points with STAThread (FXCOP_MWFEPWST) {#FXCOP_MWFEPWST}

Assemblies that reference System.Windows.Forms should have the STAThreadAttribute. Failure to apply this attribute will most likely result in an application that does not work. Windows Forms relies on a number of components that use the STA model.

#### Members should differ by more than return type (FXCOP_MSDBMTRT) {#FXCOP_MSDBMTRT}

Methods in the same type that differ only by return type can be difficult for developers and tools to properly recognize. When extending a type, be sure not to define new methods that differ from base type methods only by type.

#### Non-constant fields should not be visible (FXCOP_NCFSNBV) {#FXCOP_NCFSNBV}

Static fields should be constant unless you carefully manage access to the field using locks. Using static variables without making them thread safe can compromise execution state. This rule applies to managed code libraries. If the analyzed assembly is an application, it is usually safe to exclude violations of this rule.

#### Operations should not overflow (FXCOP_OSNO) {#FXCOP_OSNO}

Arithmetic operations should not be done without first validating the operands to prevent overflow.

#### Operator overloads have named alternates (FXCOP_OOHNA) {#FXCOP_OOHNA}

When redefining operators, implement named methods to provide access to the operator functionality from languages that do not support operator overloading. For example, the functionality of the '+' operator should also be accessible using an 'Add' method.

#### Operators should have symmetrical overloads (FXCOP_OSHSO) {#FXCOP_OSHSO}

Overload operators that have related meanings so that their behavior is consistent. For example, when overloading the equality operator, you should also overload the inequality operator to ensure they return opposite results for the same input values.

#### Overload operator equals on overriding ValueType.Equals (FXCOP_OOEOOVTE) {#FXCOP_OOEOOVTE}

Value types that redefine System.ValueType.Equals should redefine the equality operator as well to ensure that these members return the same results. This helps ensure that types that rely on Equals (such as ArrayList and Hashtable) behave in a manner that is expected and consistent with the equality operator.

#### Override Equals on overloading operator equals (FXCOP_OEOOOE) {#FXCOP_OEOOOE}

Types that redefine the equality operator should redefine Equals as well to ensure that these members return the same results. This helps ensure that types that rely on Equals (such as ArrayList and Hashtable) behave in a manner that is expected and consistent with the equality operator.

#### Override GetHashCode on overriding Equals (FXCOP_OGHCOOE) {#FXCOP_OGHCOOE}

When overriding Equals, you must also override GetHashCode to guarantee correct behavior with hashtables.

#### Pass System.Uri objects instead of strings (FXCOP_PSUOIOS) {#FXCOP_PSUOIOS}

If there are two overloads one taking System.Uri and one taking System.String, library code should never call the string-based overload.

#### Provide deserialization methods for optional fields (FXCOP_PDMFOF) {#FXCOP_PDMFOF}

If a type contains fields attributed as OptionalField, then it should implement the corresponding special deserialization methods.

#### Rethrow to preserve stack details (FXCOP_RTPSD) {#FXCOP_RTPSD}

Use the IL rethrow instruction to preserve original stack details when re-raising a caught exception.

#### Review unused parameters (FXCOP_RUP) {#FXCOP_RUP}

Review parameters in non-virtual methods that are not used in the method body to ensure no correctness exists around failure to access them. Unused parameters incur maintenance and performance costs. Sometimes a violation of this rule can point to an implementation bug in the method (i.e. the parameter should actually have been used in the method body). Exclude warnings of this rule if the parameter has to exist because of backward compatibility.

#### Test for NaN correctly (FXCOP_TFN) {#FXCOP_TFN}

Direct comparisons against 'Single.NaN' or 'Double.NaN' (not a number) always return true for inequality and false for all other comparisons; use 'Single.IsNaN' or 'Double.IsNaN' to check if a floating point value is NaN.

#### Use managed equivalents of Win32 API (FXCOP_UMEOW) {#FXCOP_UMEOW}

Use managed equivalents to Win32 API whenever possible.

#### Use params for variable arguments (FXCOP_UPFVA) {#FXCOP_UPFVA}

Do not use the varargs calling convention to accept a variable number of arguments. In the managed world, the 'params' and 'ParamArray' keywords provide this functionality..

