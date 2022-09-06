# ToolDescription
## Default
### ID=FxCop
### Description
  OpenStaticAnalyzer incorporates the [FxCop] tool for coding rule violation checking and imports its results. OpenStaticAnalyzer also associates the issued rule violations with source code elements (i.e. methods, classes, namespaces, and components), and calculates metrics for the source code elements, which represent the amount of violations of each ruleset, rule, and priority groups, respectively.

  OpenStaticAnalyzer uses FxCop "as is", without any guaranties that the results of FxCop are correct. All statements of the FxCop license apply here as well. All texts describing the rulesets and the individual rules are copied from the documentation of FxCop.

  OpenStaticAnalyzer supports the rulesets of FxCop included with Visual Studio 2015 Enterprise edition. Older versions contain less rules, so in such cases the newer rules will not appear in OpenStaticAnalyzer's results. In case of using a newer version of FxCop, the eventual new rules will not be included.

  [FxCop]:https://msdn.microsoft.com/en-us/library/bb429476%28v=vs.80%29.aspx

# Includes
- FxCop.rul_metadata.md

# Metrics
## FXCOP_AAIE
### Default
#### OriginalId=CA5410
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=AnonymousAccessIsEnabled
#### HelpText
  Looks in the web.config file to see if the authorization section allows anonymous access.

#### Tags
- /general/ASP.NET.Security.Configuration
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_ACPM
### Default
#### OriginalId=CA2001
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Avoid calling problematic methods
#### HelpText
  Avoid making unnecessary and potentially dangerous method calls.

#### Tags
- /general/Reliability Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_ADA
### Default
#### OriginalId=CA1301
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Avoid duplicate accelerators
#### HelpText
  Controls should have unique accelerators for all items and sub-controls.

#### Tags
- /general/Globalization Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_AEC
### Default
#### OriginalId=CA1502
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Avoid excessive complexity
#### HelpText
  Method implementations that are exceedingly complex increase the challenge of understanding and maintaining code.

#### Tags
- /general/Maintainability Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_AECC
### Default
#### OriginalId=CA1506
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Avoid excessive class coupling
#### HelpText
  Types and methods with a high degree of class coupling can be difficult to maintain.

#### Tags
- /general/Maintainability Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_AEI
### Default
#### OriginalId=CA1040
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Avoid empty interfaces
#### HelpText
  Interfaces are meant to contain members that specify a set of behaviors. To mark or label a class, use an attribute instead of an empty interface.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_AEL
### Default
#### OriginalId=CA1809
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Avoid excessive locals
#### HelpText
  Method implementations should not contain more than 64 local variables. In order for the run-time to enregister local variables most efficiently, there should be 64 or fewer of them. Enregistering based on flow analysis will not occur for locals in excess of 64, which may result in slower performance.

#### Tags
- /general/Performance Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_AEPOGT
### Default
#### OriginalId=CA1005
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Avoid excessive parameters on generic types
#### HelpText
  Avoid generic types with more than two type parameters as users have difficulties understanding what type parameters represent in types with long type parameter lists.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_AFSNBRO
### Default
#### OriginalId=CA2105
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Array fields should not be read only
#### HelpText
  Read-only fields that reference arrays might not give the intended effect. Setting a field which references an array to read-only prevents the value of the field from being changed. Note that elements in the array can be changed. You can ignore this violation if protecting the contents of the array is not a concern.

#### Tags
- /general/Security Rules
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_AIF
### Default
#### OriginalId=CA1406
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Avoid Int64 arguments for Visual Basic 6 clients
#### HelpText
  COM visible types that might be accessed from Microsoft Visual Basic 6 clients should not expose methods with long arguments.

#### Tags
- /general/Interoperability Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_ALTSNBCV
### Default
#### OriginalId=CA1403
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Auto layout types should not be COM visible
#### HelpText
  Types that are automatically ordered by the runtime should not be visible to COM. Types that are automatically laid out by the runtime do not have a guaranteed order between versions. This can break COM clients of those types. To ensure compatibility between versions, the type should be explicitly or sequentially ordered.

#### Tags
- /general/Interoperability Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_AMSOCAM
### Default
#### OriginalId=CA2116
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=APTCA methods should only call APTCA methods
#### HelpText
  Methods with the AllowPartiallyTrustedCallersAttribute that call methods without that attribute might unintentionally expose functionality to partially trusted code. When a method has the AllowPartiallyTrustedCallersAttribute set, it is callable by partially trusted code. If it in turn calls methods without the attribute, a partially trusted caller is, in effect, being allowed to execute code that requires full trust. Depending on what full trust code is called and what parameter values are passed through from the partially trusted caller, malicious code might be able to exploit this security weakness.

#### Tags
- /general/Security Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_ANFICVVT
### Default
#### OriginalId=CA1413
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Avoid non-public fields in COM visible value types
#### HelpText
  COM visible value types should not expose non-public instance fields. COM visible value types have their non-public instance fields exposed to COM clients.

#### Tags
- /general/Interoperability Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_ANWFT
### Default
#### OriginalId=CA1020
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Avoid namespaces with few types
#### HelpText
  A namespace should generally have more than five types.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_AOICVI
### Default
#### OriginalId=CA1402
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Avoid overloads in COM visible interfaces
#### HelpText
  Interfaces that are visible to COM should not define overloads, as they will be renamed and cannot be implemented by Visual Basic 6 clients. COM interfaces cannot contain overloaded methods.

#### Tags
- /general/Interoperability Rules
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_AOP
### Default
#### OriginalId=CA1021
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Avoid out parameters
#### HelpText
  Using out parameters might indicate a design flaw. Although there are legitimate times to use out parameters, their use frequently indicates a design that does not conform to the design guidelines for managed code.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_ASHVSN
### Default
#### OriginalId=CA2210
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Assemblies should have valid strong names
#### HelpText
  Either the assembly has no strong name, an invalid one, or the strong name is valid only because of the computer configuration. The assembly should not be deployed in this state. The most common causes of this are: 1) The assembly's contents were modified after it was signed. 2) The signing process failed. 3) The assembly was delay-signed. 4) A registry key existed that allowed the check to pass (where it would not have otherwise).

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_ASLSPC
### Default
#### OriginalId=CA2243
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Attribute string literals should parse correctly
#### HelpText
  Literal strings used as attribute parameters that represent URLs, version numbers, or GUIDs, should have the appropriate format.

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_ASMICVT
### Default
#### OriginalId=CA1407
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Avoid static members in COM visible types
#### HelpText
  COM does not support static methods.

#### Tags
- /general/Interoperability Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_ATSNHC
### Default
#### OriginalId=CA1012
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Abstract types should not have constructors
#### HelpText
  Public constructors for abstract types do not make sense because you cannot create instances of abstract types.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_ATSOEABT
### Default
#### OriginalId=CA2117
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=APTCA types should only extend APTCA base types
#### HelpText
  Types with the AllowPartiallyTrustedCallersAttribute that extend types without that attribute might unintentionally expose functionality in the base type to partially trusted callers. When a type has the AllowPartiallyTrustedCallersAttribute set, it is callable by partially trusted code. If the base type does not have this attribute, it requires callers to be fully trusted. If the derived type exposes protected members in the base type, the base type's data is made accessible to partially trusted callers, creating an exploitable security weakness.

#### Tags
- /general/Security Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_AUA
### Default
#### OriginalId=CA1813
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Avoid unsealed attributes
#### HelpText
  Seal attribute types for improved performance. Sealing attribute types speeds up performance during reflection on custom attributes.

#### Tags
- /general/Performance Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_AUC
### Default
#### OriginalId=CA1505
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Avoid unmaintainable code
#### HelpText
  Types and methods with a high degree of class coupling, cyclomatic complexity and/or program length can be difficult to maintain.

#### Tags
- /general/Maintainability Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_AUIC
### Default
#### OriginalId=CA1812
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Avoid uninstantiated internal classes
#### HelpText
  An internal class was detected that is apparently never instantiated. This rule does not attempt to detect late-bound creation and will generate false positives if instances of a type are only created in this way (for example, by means of Activator.CreateInstance or by passing the type as an argument to a TypeConverter constructor).

#### Tags
- /general/Performance Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_AUPC
### Default
#### OriginalId=CA1811
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Avoid uncalled private code
#### HelpText
  There is uncalled code that is not externally visible and is not a known runtime entry point. If this violation fires in error, please send a problem report to the Visual Studio Code Analysis team.

#### Tags
- /general/Performance Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_AUPF
### Default
#### OriginalId=CA1823
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Avoid unused private fields
#### HelpText
  Private fields were detected that do not appear to be accessed within the assembly. If this violation fires in error, please send a problem report to the Visual Studio Code Analysis team.

#### Tags
- /general/Performance Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_AVEXIN
### Default
#### OriginalId=CA1501
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Avoid excessive inheritance
#### HelpText
  Object hierarchies that are deeply nested increase the challenge of understanding and maintaining code.

#### Tags
- /general/Maintainability Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_CASVI
### Default
#### OriginalId=CA5333
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=ControllerActionShouldValidateInput
#### HelpText
  Verifies if the ValidateInputAttribute is used properly to protect against XSS attacks.

#### Tags
- /general/ASP.NET MVC Security Rules
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_CAWUNR
### Default
#### OriginalId=CA2115
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Call GC.KeepAlive when using native resources
#### HelpText
  If a method uses an IntPtr or UIntPtr field in a class with a finalizer and does not call GC.KeepAlive, a race condition might be introduced.

#### Tags
- /general/Security Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_CBCMOT
### Default
#### OriginalId=CA2236
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Call base class methods on ISerializable types
#### HelpText
  Derived ISerializable types must call the base class magic constructor and the base class GetObjectData method.

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_CEMSBO
### Default
#### OriginalId=CA5419
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=CustomErrorsModeShouldBeOn
#### HelpText
  The rule verifies that the system.web.customErrors mode is set to On or RemoteOnly. This disable detailed error message returned by ASP.NET to remote users.

#### Tags
- /general/ASP.NET.Security.Configuration
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_CEPSBS
### Default
#### OriginalId=CA5401
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=CustomErrorPageShouldBeSpecified
#### HelpText
  Verifies that the CustomErrors section is configured to have a default url for redirecting uses in case of error.

#### Tags
- /general/ASP.NET.Security.Configuration
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_CFC
### Default
#### OriginalId=CA1816
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Call GC.SuppressFinalize correctly
#### HelpText
  Call GC.SuppressFinalize to suppress finalization of your instance once Dispose has been called. Objects that implement IDisposable should call SuppressFinalize from the IDisposable.Dispose method to prevent the garbage collector from calling Object.Finalize on an object that does not require it.

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_CGLEIA
### Default
#### OriginalId=CA1404
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Call GetLastError immediately after P/Invoke
#### HelpText
  The last Win32 error can be reset as a result of making managed calls, due to P/Invokes called by the runtime itself. In order to ensure the correctness of the value returned by GetLastWin32Error, place the call immediately after the relevant platform invoke call in your code.

#### Tags
- /general/Interoperability Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_CNCCEIGH
### Default
#### OriginalId=CA2102
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Catch non-CLSCompliant exceptions in general handlers
#### HelpText
  Exception handlers which are truly intended to catch all exceptions should handle non-CLSCompliant exceptions if there is a possibility one can be raised. If possible, catch handlers should only catch specific exceptions or exception base types. In circumstances where a handler is required to catch all exceptions (e.g., when a try block wraps arbitrary plug-in code), the handler should also include a generic catch handler (in C#, catch{ ... }) to handle non-CLSCompliant exceptions. It is possible to raise non-CLSCompliant exceptions by modifying and recompiling IL.

#### Tags
- /general/Security Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_CPBTAP
### Default
#### OriginalId=CA1011
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Consider passing base types as parameters
#### HelpText
  Using base types as parameters to methods improves re-use of these methods if you only use methods & properties from the parameter's base class. E.g. use Stream instead of FileStream as a parameter when only calling Stream.Read(), this makes the method work on all kind of streams instead of just File streams.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_CPSBRO
### Default
#### OriginalId=CA2227
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Collection properties should be read only
#### HelpText
  Properties that return collections should be read-only so that users cannot entirely replace the backing store. Users can still modify the contents of the collection by calling relevant methods on the collection. Note that the XmlSerializer class has special support for deserializing read-only collections. See the XmlSerializer overview for more information.

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_CRMSBM
### Default
#### OriginalId=CA1410
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=COM registration methods should be matched
#### HelpText
  If a COM registration method is provided, an unregistration method must also be provided to reverse the operations performed by the registration method. COM registration functions are static methods within a type that are marked with the ComRegisterFunction attribute. All COM registration functions should be matched by a static method within the same type that is marked with the ComUnregisterFunction attribute. This method should reverse any operations completed by the registration function.

#### Tags
- /general/Interoperability Rules
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_CRMSNBV
### Default
#### OriginalId=CA1411
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=COM registration methods should not be visible
#### HelpText
  COM registration and unregistration functions should be private or internal. COM registration and unregistration functions are called by the runtime when an assembly is registered or unregistered for use with COM. It is preferred that these methods are not externally visible.

#### Tags
- /general/Interoperability Rules
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_CSBT
### Default
#### OriginalId=CA2130
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Security critical constants should be transparent
#### HelpText
  Compilers inline accesses to constants, and as such transparency enforcement is not done for them since there is no runtime access to the field.  These fields should be security transparent so that code reviewers do not assume that transparent code cannot access the constant.

#### Tags
- /general/Security Transparency Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_CSIGI
### Default
#### OriginalId=CA1010
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Collections should implement generic interface
#### HelpText
  Non-generic strongly typed collections should implement one of the generic collection interfaces. This will allow better integration of the collection with generic API.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_CTMNPITE
### Default
#### OriginalId=CA2131
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Security critical types may not participate in type equivalence
#### HelpText
  Type equivalence requires that all participating types, as well as all methods and fields within those types, are transparent or security safe-critical.  The CLR will fail to load any type which violates this rule.

#### Tags
- /general/Security Transparency Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_CVTBTSBCV
### Default
#### OriginalId=CA1405
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=COM visible type base types should be COM visible
#### HelpText
  COM visible types should have an object hierarchy that is uniformly COM visible.

#### Tags
- /general/Interoperability Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_CVTSBC
### Default
#### OriginalId=CA1409
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=COM visible types should be creatable
#### HelpText
  Types with no public default constructor are not COM-creatable. COM does not support parameterized object construction. A type was detected with a public parameterized constructor but no public default constructor. This type is not creatable by COM. If there is an alternate method for creating and passing object instances to COM clients (through a method on another type, for example), this might not be a problem.

#### Tags
- /general/Interoperability Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_CWSBCC
### Default
#### OriginalId=CA1702
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Compound words should be cased correctly
#### HelpText
  Avoid creating compound words from terms which exist in the dictionary as discrete terms. Do not create a compound word such as 'StopWatch' or 'PopUp'. These terms are recognized in the dictionary and should be cased as 'Stopwatch' and 'Popup'.

#### Tags
- /general/Naming Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_DAFAA
### Default
#### OriginalId=CA1019
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Define accessors for attribute arguments
#### HelpText
  Provide accessors for both named and positional arguments. Each positional argument on an attribute should declare a read-only property with the same name (but different casing). Each named argument should provide a read/write property with the same name (but different casing).

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_DC
### Default
#### OriginalId=CA1415
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Declare P/Invokes correctly
#### HelpText
  P/Invoke methods should be declared correctly to ensure correct runtime behaviors.

#### Tags
- /general/Interoperability Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_DCMBD
### Default
#### OriginalId=CA5400
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=DebugCompilationMustBeDisabled
#### HelpText
  Verifies that debug compilation is turned off. This eliminates potential performance and security issues related to debug code enabled and additional extensive error messages being returned.

#### Tags
- /general/ASP.NET.Security.Configuration
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_DCMHCT
### Default
#### OriginalId=CA2132
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Default constructors must be at least as critical as base type default constructors
#### HelpText
  On CoreCLR, if a base type has a public or protected non-transparent default constructor than the derived type must obey default constructor inheritance rules.  The derived type must also have a default constructor and that constructor must be at least as critical as the base type's default constructor.  If the base type's default constructor is safe-critical, the derived type's default constructor must be safe-critical or critical.  If the base type's default constructor is critical, then the derived type's default constructor must also be critical.

#### Tags
- /general/Security Transparency Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_DEHC
### Default
#### OriginalId=CA1009
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Declare event handlers correctly
#### HelpText
  By convention, .NET events have two parameters that specify the event sender and event data. Event handler signatures should follow this form: void MyEventHandler(object sender, EventArgs e). The 'sender' parameter is always of type System.Object, even if it is possible to employ a more specific type. The 'e' parameter is always of type System.EventArgs. Events that do not provide event data should use the System.EventHandler delegate type. Event handlers return void so that they can send each event to multiple target methods. Any value returned by a target would be lost after the first call.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_DFSBD
### Default
#### OriginalId=CA2213
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Disposable fields should be disposed
#### HelpText
  If a type that implements IDisposable owns fields that also implement IDisposable, the encapsulating type's Dispose() implementation should call Dispose() on each disposable field.

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_DMBWCT
### Default
#### OriginalId=CA2133
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Delegates must bind to methods with consistent transparency
#### HelpText
  Delegate types and the methods that they bind to must have consistent transparency.  Transparent and safe-critical delegates may only bind to other transparent or safe-critical methods.  Similarly, critical delegates may only bind to critical methods.  These binding rules ensure that the only code which can invoke a method via a delegate could have also invoked the same method directly.  It prevents, for instance, transparent code from calling critical code directly via a transparent delegate.

#### Tags
- /general/Security Transparency Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_DNCGET
### Default
#### OriginalId=CA1031
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Do not catch general exception types
#### HelpText
  You should not catch Exception or SystemException. Catching generic exception types can hide run-time problems from the library user, and can complicate debugging. You should catch only those exceptions that you can handle gracefully.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_DNCOMIC
### Default
#### OriginalId=CA2214
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Do not call overridable methods in constructors
#### HelpText
  Virtual methods defined on the class should not be called from constructors. If a derived class has overridden the method, the derived class version will be called (before the derived class constructor is called).

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_DNCU
### Default
#### OriginalId=CA1800
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Do not cast unnecessarily
#### HelpText
  Avoid duplicate casts where possible, since there is a cost associated with them.

#### Tags
- /general/Performance Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_DNDIMV
### Default
#### OriginalId=CA2222
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Do not decrease inherited member visibility
#### HelpText
  It is incorrect to override a public method from an inherited class with a private implementation, unless the type is sealed or the method is marked final. It is considered bad form to hide a method signature halfway down an inheritance tree.

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_DNDPMIST
### Default
#### OriginalId=CA1047
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Do not declare protected members in sealed types
#### HelpText
  Sealed types cannot be extended, and protected members are only useful if you can extend the declaring type. Sealed types should not declare protected members.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_DNDROMRT
### Default
#### OriginalId=CA2104
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Do not declare read only mutable reference types
#### HelpText
  A read-only declaration for a mutable reference type does not prevent the field's instance data from being modified. For example, a read-only StringBuilder field declaration does not make sense, since the data encapsulated by the StringBuilder can be modified using the read-only reference.

#### Tags
- /general/Security Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_DNDSMOGT
### Default
#### OriginalId=CA1000
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Do not declare static members on generic types
#### HelpText
  The syntax for calling static members on generic types is complex as the type parameter has to be specified for each call.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_DNDVIF
### Default
#### OriginalId=CA1051
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Do not declare visible instance fields
#### HelpText
  Instance fields that are visible outside of the type that declares them, limit your ability to change the implementation details for those data items. Use properties instead. They do not compromise usability or performance and they do provide flexibility in that they conceal the implementation details of the underlying data.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_DNDVMIST
### Default
#### OriginalId=CA1048
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Do not declare virtual members in sealed types
#### HelpText
  Sealed types cannot be extended, and virtual members are only useful if you can extend the declaring type.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_DNEGL
### Default
#### OriginalId=CA1002
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Do not expose generic lists
#### HelpText
  Do not expose List<T> in object models. Use Collection<T>, ReadOnlyCollection<T> or KeyedCollection<K,V> instead. List<T> is meant to be used from implementation, not in object model API. List<T> is optimized for performance at the cost of long term versioning. For example, if you return List<T> to the client code, you will not ever be able to receive notifications when client code modifies the collection.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_DNHBCM
### Default
#### OriginalId=CA1061
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Do not hide base class methods
#### HelpText
  Defining a method in a derived class with the same name and parameters that are more weakly typed as one that is defined in the base class will obstruct access to the method defined in the base class.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_DNHLSS
### Default
#### OriginalId=CA1302
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Do not hardcode locale specific strings
#### HelpText
  Do not use string literals for system items that have locale-specific designations. Special system locations should be retrieved using provided API such as GetFolderPath. See the System.Environment.SpecialFolder enumeration for more information.

#### Tags
- /general/Globalization Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_DNIEMWLD
### Default
#### OriginalId=CA2122
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Do not indirectly expose methods with link demands
#### HelpText
  Do not wrap a method protected by a LinkDemand with a method that does not perform a security check. A LinkDemand checks the permissions of the immediate caller rather than checking the permissions of all callers in the call stack. In this case, the permissions of the wrapper method will be checked. If the wrapper method does not, itself, check the permissions of callers higher in the call stack, malicious code might be able to execute the wrapped function even though it lacks permission to do so.

#### Tags
- /general/Security Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_DNIMR
### Default
#### OriginalId=CA1806
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Do not ignore method results
#### HelpText
  The result of methods that return new instances of strings should be assigned to a variable and subsequently used. If the result of a method that creates a new object, such as String.ToLower(), is not assigned to a variable, the call is wasted.

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_DNLOOWWI
### Default
#### OriginalId=CA2002
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Do not lock on objects with weak identity
#### HelpText
  Don't take locks on objects that may bleed across AppDomains or that don't have a strong identity.

#### Tags
- /general/Reliability Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_DNMEWF
### Default
#### OriginalId=CA2217
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Do not mark enums with FlagsAttribute
#### HelpText
  The enumeration does not appear to contain a consistent set values that can be combined using  the OR (|) and AND (&amp;amp;) operators. Using the Flags attribute on an enumeration suggests that the enumeration values are meant to be combined using the AND and OR operators. Typically, a flags enumeration uses values that are either powers of two, or combine other values that are powers of two.

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_DNMSCWWM
### Default
#### OriginalId=CA2212
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Do not mark serviced components with WebMethod
#### HelpText
  Types that extend ServicedComponent should not have the WebMethod attribute applied to members. Marking members of types that extend ServicedComponent with WebMethod is not a supported scenario.

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_DNNEVR
### Default
#### OriginalId=CA1700
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Do not name enum values 'Reserved'
#### HelpText
  Avoid naming an enum value 'Reserved'. Adding 'Reserved' values will lead to a breaking change on removal when the value is actually used in a later version of the product.

#### Tags
- /general/Naming Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_DNNGTIMS
### Default
#### OriginalId=CA1006
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Do not nest generic types in member signatures
#### HelpText
  Avoid API that require users to instantiate a generic type with another generic type as type argument. The syntax gets too complex.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_DNOOEORT
### Default
#### OriginalId=CA1046
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Do not overload operator equals on reference types
#### HelpText
  Most reference types, including those that override System.Object.Equals, do not override the equality operator  (==). Most languages provide a default implementation of this operator.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_DNPEVWTN
### Default
#### OriginalId=CA1712
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Do not prefix enum values with type name
#### HelpText
  The individual values that make up an enumeration type should not be prefixed with the type name.

#### Tags
- /general/Naming Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_DNPTBR
### Default
#### OriginalId=CA1045
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Do not pass types by reference
#### HelpText
  Although there are legitimate times to use reference parameters, such use frequently indicates a design that does not conform to the design guidelines for managed code.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_DNREIEC
### Default
#### OriginalId=CA2219
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Do not raise exceptions in exception clauses
#### HelpText
  Raising exceptions in exception clauses greatly increases the difficulty of debugging. Exceptions raised in finally and fault clauses will hide any exceptions raised in the corresponding try block. If an exception is raised in a filter, it is ignored and treated as if the filter had returned false.

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_DNREIUL
### Default
#### OriginalId=CA1065
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Do not raise exceptions in unexpected locations
#### HelpText
  Do not explicitly raise exceptions from unexpected locations. There are some methods, such as Equals and GetHashCode, which users do not expect to raise exceptions. Therefore calls to these methods are not commonly wrapped in try catch blocks.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_DNRRET
### Default
#### OriginalId=CA2201
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Do not raise reserved exception types
#### HelpText
  User code should not create and raise exceptions of certain types that are reserved by the runtime or which are of a too general exception type. Exception types that are too general include Exception, SystemException, and ApplicationException. Exception types that are reserved by the runtime include ThreadAbortException, OutOfMemoryException, ExecutionEngineException, and IndexOutOfRangeException.

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_DNSURF
### Default
#### OriginalId=CA2228
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Do not ship unreleased resource formats
#### HelpText
  Resources generated by pre-release versions of the .NET Framework might contain incorrect or incomplete type references. Pre-release versions of the .NET Framework can generate partial or incomplete references to types. Resources built with pre-release software are not guaranteed to work correctly in released versions.

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_DNTFAT
### Default
#### OriginalId=CA2003
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Do not treat fibers as threads
#### HelpText
  Do not assume a managed thread is a Win32 thread - it could be a fiber. The runtime will run managed threads as fibers on top of real threads owned by SQL Server. These threads will be shared across AppDomains and even databases in the SQL Server process. Using managed thread local storage will work, but you may not use unmanaged thread local storage or assume your code will run on the current OS thread again. Do not change settings like the thread's locale. Do not call CreateCriticalSection or CreateMutex via P/Invoke because they require the thread that enters a lock also exit the lock. Since this will not be the case when using fibers, Win32 critical sections and mutexes will be useless in SQL Server.
  You may safely use most of the state on a managed System.Thread object, including managed thread local storage and the thread's current UI culture. For programming model reasons, you will not be able to change a thread's current culture when running in SQL Server though (this will be enforced through a new permission).

#### Tags
- /general/Reliability Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_DNUADCIT
### Default
#### OriginalId=CA1408
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Do not use AutoDual ClassInterfaceType
#### HelpText
  Classes that use the ClassInterfaceType.AutoDual setting might break in later versions if you change the member layout of the class or base classes. ClassInterfaceType.AutoDual should only be used when the versioning limitations are known to be acceptable.

#### Tags
- /general/Interoperability Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_DNUIPP
### Default
#### OriginalId=CA1600
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Do not use idle process priority
#### HelpText
  Do not set process priority to Idle. Processes with System.Diagnostics.ProcessPriorityClass.Idle will occupy the CPU when it would otherwise be idle, and thereby block standby.

#### Tags
- /general/Mobility Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_DNUTTPPSC
### Default
#### OriginalId=CA1601
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Do not use timers that prevent power state changes
#### HelpText
  Do not poll more often than or utilize timers that fire more frequently than once per second. Higher frequency periodic activity will keep the CPU busy and interfere with power-saving idle timers that turn off the display and hard disks.

#### Tags
- /general/Mobility Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_DPSNBU
### Default
#### OriginalId=CA1026
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Default parameters should not be used
#### HelpText
  Some programming languages do not support default parameters. Replace default parameters with method overloads that supply the default argument.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_DTIN
### Default
#### OriginalId=CA1050
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Declare types in namespaces
#### HelpText
  A type should be defined inside a namespace to avoid duplication.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_DTSDF
### Default
#### OriginalId=CA2216
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Disposable types should declare finalizer
#### HelpText
  If a type implements a Dispose method and has unmanaged resources, it should provide a Finalize method in case Dispose is not explicitly called. The runtime calls the Finalize method or destructor of an object prior to reclaiming its managed resources in a process known as garbage collection. The Finalize method should free any unmanaged resources before they become inaccessible.

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_ECARSBT
### Default
#### OriginalId=CA5403
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=EnableCrossAppRedirectsShouldBeTrue
#### HelpText
  The rule verifies that the system.web.authentication.forms enableCrossAppRedirects is set to true. The settings indicate if the user should be redirected to another application url after the authentication process. If the setting is false, the authentication process will not allow redirection to another application or host. This helps prevent an attacker to force the user to be redirected to another site during the authentication process. This attack is commonly called Open redirect and is used mostly during phishing attacks.

#### Tags
- /general/ASP.NET.Security.Configuration
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_EEVSBT
### Default
#### OriginalId=CA5327
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=EnableEventValidationShouldBeTrue
#### HelpText
  Rule that will identify if the EnableEventValidation is disabled on a certain page.

#### Tags
- /general/ASP.NET Security Rules
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_ESBP
### Default
#### OriginalId=CA1064
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Exceptions should be public
#### HelpText
  Exception classes should either be public, or have a non-generic public ancestor.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_ESBST
### Default
#### OriginalId=CA1038
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Enumerators should be strongly typed
#### HelpText
  Types that implement IEnumerator should also provide a version of the Current property that returns a type other than Object. Implement the interface member explicitly and make the strongly typed version public.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_ESHZV
### Default
#### OriginalId=CA1008
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Enums should have zero value
#### HelpText
  An enum should generally have a zero value. If the enum is not decorated with the Flags attribute, it should have a member with a value of zero that represents the empty state. Optionally, this value is named 'None'. For a Flags-attributed enum, a zero-valued member is optional and, if it exists, should always be named 'None'. This value should indicate that no values have been set in the enum. Using a zero-valued member for other purposes is contrary to the use of the Flags attribute in that the bitwise AND and OR operators are useless with the member.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_ESNHBOAP
### Default
#### OriginalId=CA1713
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Events should not have before or after prefix
#### HelpText
  Use present and past tense for pre-events and post-events, instead of using 'Before' and 'After'. For example, use Closing and Closed rather than BeforeClose and AfterClose.

#### Tags
- /general/Naming Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_ESSBI
### Default
#### OriginalId=CA1028
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Enum storage should be Int32
#### HelpText
  There is little or no benefit to using a type smaller than Int32. You might require a type that is larger than Int32 if: 1) the enumeration values are flags and there are or will be many (&amp;gt;32) values, or 2) the type needs to be different from Int32 for backward compatibility. Avoid using an underlying type that is not integral.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_EVSMSBT
### Default
#### OriginalId=CA5330
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=EnableViewStateMacShouldBeTrue
#### HelpText
  Rule that will identify if the EnableViewStateMac is not set to false on a certain page.

#### Tags
- /general/ASP.NET Security Rules
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_EVSSBT
### Default
#### OriginalId=CA5331
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=EnableViewStateShouldBeTrue
#### HelpText
  Rule that will identify if the EnableViewStateRule is not set to false on a certain page.

#### Tags
- /general/ASP.NET Security Rules
- /tool/FxCop

#### Settings
- Priority=Info


## FXCOP_FAPSBA
### Default
#### OriginalId=CA5404
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=FormAuthenticationProtectionShouldBeAll
#### HelpText
  The rule verifies that the protection attribute on the system.web.authentication.forms protection is set to All which specifies that the application use both data validation and encryption to help protect the authentication cookie.

#### Tags
- /general/ASP.NET.Security.Configuration
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_FARBT
### Default
#### OriginalId=CA5405
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=FormAuthenticationRequireSSLShouldBeTrue
#### HelpText
  The rule verifies that the requireSSL attribute on the system.web.authentication.forms configuration element is set to True which force the authentication cookie to specify the secure attribute. This indicates the browser to only provide the cookie over SSL.

#### Tags
- /general/ASP.NET.Security.Configuration
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_FASESBF
### Default
#### OriginalId=CA5406
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=FormAuthenticationSlidingExpirationShouldBeFalse
#### HelpText
  The rule verifies that if the system.web.authentication.forms slidingExpiration be set to false when the site is being serviced over HTTP. This will force the authentication cookie to have a fix timeout value instead of being refreshed by each request. Since the cookie will traverse over clear text network and can be sniffed, having a fix timeout value on the cookie will limit the amount of time the cookie can be replayed. If the cookie is traversing over HTTPS, it is less likely to be intercepted and having the slidingExpiration setting to True will cause the timeout to be refreshed after each request which gives a better user experience.

#### Tags
- /general/ASP.NET.Security.Configuration
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_FASNCFAC
### Default
#### OriginalId=CA5402
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=FormAuthenticationShouldNotContainFormAuthenticationCredentials
#### HelpText
  The rule verifies that no credentials are specified under the form authentication configuration.

#### Tags
- /general/ASP.NET.Security.Configuration
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_FESHPN
### Default
#### OriginalId=CA1714
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Flags enums should have plural names
#### HelpText
  An enumeration marked with FlagsAttribute should have a plural name.

#### Tags
- /general/Naming Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_FSBP
### Default
#### OriginalId=CA2221
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Finalizers should be protected
#### HelpText
  Finalize methods should be declared as protected.

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_FSCBCF
### Default
#### OriginalId=CA2220
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Finalizers should call base class finalizer
#### HelpText
  The Finalize method should call its base class' Finalize method. This is done automatically with the C# destructor syntax.

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_FWCTSBC
### Default
#### OriginalId=CA2151
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Fields with critical types should be security critical.
#### HelpText
  Fields which have a critical type cannot be used from transparent code, and should therefore be marked security critical.  This makes it obvious to the users of the field that they must also be critical.  Additionally, such fields frequently store sensitive information such as a handle value.

#### Tags
- /general/Security Transparency Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_GMSPTP
### Default
#### OriginalId=CA1004
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Generic methods should provide type parameter
#### HelpText
  Methods where the type parameter cannot be inferred from the parameters and therefore has to be defined in the method call are too difficult to understand. Methods with a formal parameter typed as the generic method type parameter support inference. Methods with no formal parameter typed as the generic method type parameter don't support inference.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_HCHOCSBT
### Default
#### OriginalId=CA5407
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=HttpCookiesHttpOnlyCookiesShouldBeTrue
#### HelpText
  The rule verifies that the system.web.httpCookies httpOnlyCookies configuration is set to True which force all cookies to be sent with the HttpOnly attribute.

#### Tags
- /general/ASP.NET.Security.Configuration
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_HCRBT
### Default
#### OriginalId=CA5408
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=HttpCookiesRequireSSLShouldBeTrue
#### HelpText
  The rule verifies that the system.web.httpCookies requireSSL configuration is set to True which force all cookies to be sent with the secure attribute. This indicates the browser to only provide the cookie over SSL.

#### Tags
- /general/ASP.NET.Security.Configuration
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_HREHCSBT
### Default
#### OriginalId=CA5416
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=HttpRuntimeEnableHeaderCheckingShouldBeTrue
#### HelpText
  The rule verifies that the system.web.httpRuntime enableHeaderChecking attribute is set to true. From http://msdn.microsoft.com/en-us/library/e1f13641.aspx. The setting indicates whether ASP.NET should check the request header for potential injection attacks. If an attack is detected, ASP.NET responds with an error. This forces ASP.NET to apply the ValidateRequest protection to headers sent by the client. If an attack is detected the application throws HttpRequestValidationException.

#### Tags
- /general/ASP.NET.Security.Configuration
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_IAEC
### Default
#### OriginalId=CA2208
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Instantiate argument exceptions correctly
#### HelpText
  String arguments passed to constructors of ArgumentException and its derived types should be correct. Types derived from ArgumentException have inconsistent constructor overloads with respect to the message and paramName parameters as compared to ArgumentException.

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_IC
### Default
#### OriginalId=CA2240
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Implement ISerializable correctly
#### HelpText
  If a type is assignable to ISerializable, it should implement GetObjectData. For unsealed types, the GetObjectData method should be callable and overridable by derived types.

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_IIHSTM
### Default
#### OriginalId=CA1035
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=ICollection implementations have strongly typed members
#### HelpText
  Types that implement ICollection should also provide a version of CopyTo with the first parameter set to a strong type, namely a type other than an array of objects or System.Array. Implement the interface member explicitly and make the strongly typed version public. It is safe to ignore violations of this rule when you are implementing a new object-based collection, such as a binary tree, where types based on your collection will determine what the strong type is. These types should expose strongly typed members.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_IMCO
### Default
#### OriginalId=CA1063
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Implement IDisposable correctly
#### HelpText
  All IDisposable types should implement the Dispose pattern correctly.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_IMSBCBCT
### Default
#### OriginalId=CA1033
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Interface methods should be callable by child types
#### HelpText
  Explicit method implementations are defined with private accessibility. Classes that derive from classes with explicit method implementations and choose to re-declare them on the class will not be able to call into the base class implementation unless the base class has provided an alternate method with appropriate accessibility. When overriding a base class method that has been hidden by explicit interface implementation, in order to call into the base class implementation, a derived class must cast the base pointer to the relevant interface. When calling through this reference, however, the derived class implementation will actually be invoked, resulting in recursion and an eventual stack overflow.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_IRTSFI
### Default
#### OriginalId=CA1810
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Initialize reference type static fields inline
#### HelpText
  Static fields should be initialized when declared. Initializing static data in explicit static constructors results in less performant code.

#### Tags
- /general/Performance Rules
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_ISBCC
### Default
#### OriginalId=CA1709
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Identifiers should be cased correctly
#### HelpText
  Type, namespace, and member identifiers are Pascal-cased. Parameter identifiers are camel-cased. Two letter acronyms within these identifiers should be upper-cased, for example, use System.IO instead of System.Io. Acronyms of three or more letters should be Pascal-cased, for example, use System.Xml instead of System.XML. The pascal-casing convention capitalizes the first letter of each word, as in BackColor. The camel-casing convention formats the first letter of the first word in lowercase and capitalizes the first letter of all subsequent words, as in backgroundColor. Although it may be common practice for some two letter acronyms to not be fully capitalized, violations of this rule should not be excluded for this reason. For example, 'DbConnection', is common but incorrect; use DBConnection. A violation of this rule might be required for compatibility with existing, non-managed symbol schemes. In general, however, these symbols should not be visible outside the assembly that uses them.

#### Tags
- /general/Naming Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_ISBSC
### Default
#### OriginalId=CA1704
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Identifiers should be spelled correctly
#### HelpText
  The individual words that make up an identifier should not be abbreviated and should be spelled correctly. If this rule generates a false positive on a term that should be recognized, add the word to the FxCop custom dictionary.

#### Tags
- /general/Naming Rules
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_ISC
### Default
#### OriginalId=CA2229
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Implement serialization constructors
#### HelpText
  The constructor signature accepts the same arguments as ISerializable.GetObjectData, namely, a SerializationInfo instance and a StreamingContext instance. The constructor should be protected for non-sealed classes and private for sealed classes. Failure to implement a serialization constructor will cause deserialization to fail, and throw a SerializationException.

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_ISDBMTC
### Default
#### OriginalId=CA1708
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Identifiers should differ by more than case
#### HelpText
  Do not use names that require case sensitivity for uniqueness. Components must be fully usable from both case-sensitive and case-insensitive languages. Since case-insensitive languages cannot distinguish between two names within the same context that differ only by case, components must avoid this situation.

#### Tags
- /general/Naming Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_ISEC
### Default
#### OriginalId=CA1032
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Implement standard exception constructors
#### HelpText
  Multiple constructors are required to correctly implement a custom exception. Missing constructors can make your exception unusable in certain scenarios. For example, the serialization constructor is required for handling exceptions in XML Web services.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_ISHCP
### Default
#### OriginalId=CA1715
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Identifiers should have correct prefix
#### HelpText
  Prefix interface names with the letter 'I' to indicate that the type is an interface, as in IFormattable. Prefix generic type parameter names with the letter 'T' and provide them with descriptive names, as in Dictionary<TKey, TValue>, unless a single 'T' is completely self-explanatory, as in Collection<T>. Use Pascal casing for both interface and type parameter names. Use abbreviations sparingly. Do not use the underscore character. Do use similar names when defining a class/interface pair where the class is a standard implementation of the interface. The names should differ only by the letter I prefixed on the interface name, as with Component and IComponent.

#### Tags
- /general/Naming Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_ISHCS
### Default
#### OriginalId=CA1710
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Identifiers should have correct suffix
#### HelpText
  Types that extend certain base types have specified name suffixes. Types that extend Attribute, for example, should be suffixed in 'Attribute', as in ObsoleteAttribute. This rules checks types that extend several base types, including Attribute, Exception, EventArgs, IMembershipPermission, Stream, and others.

#### Tags
- /general/Naming Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_ISMC
### Default
#### OriginalId=CA2238
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Implement serialization methods correctly
#### HelpText
  Methods marked with OnSerializing, OnSerialized, OnDeserializing, or OnDeserialized, must be non-generic, private, return void (Sub in Visual Studio) and take a single parameter of type StreamingContext.

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_ISNBM
### Default
#### OriginalId=CA1023
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Indexers should not be multidimensional
#### HelpText
  Indexers (indexed properties) should use a single value (either an integer or string types) for indexing values. Multidimensional indexers can significantly reduce the usability of the library. For example, public object this [int index1, int index2] is a non-intuitive indexer.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_ISNCTN
### Default
#### OriginalId=CA1720
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Identifiers should not contain type names
#### HelpText
  Avoid using language-specific types name in parameters and members and data type identifiers in parameters. Types names might not be intuitive for all developers. It is recommended that you select a generic name, such as 'value', instead. If this is not sufficient, be sure to use the type name as it is defined in the .NET Framework Library and avoid language-specific type names completely. Some examples of C#-specific type names are 'float' (use 'Single' if a generic name is not sufficient), and 'ulong' (use 'UInt64' if a generic name is not sufficient).

#### Tags
- /general/Naming Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_ISNCU
### Default
#### OriginalId=CA1707
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Identifiers should not contain underscores
#### HelpText
  Do not use underscores when specifying identifiers. Some generated Visual Studio identifiers for applications contain underscore characters. Underscore characters should generally be avoided in public identifiers.

#### Tags
- /general/Naming Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_ISNHIP
### Default
#### OriginalId=CA1722
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Identifiers should not have incorrect prefix
#### HelpText
  Do not use 'C' as a prefix for type names. Do not use any prefix for naming types. Consider using the name of the base class as the suffix when naming derived types. For example: ApplicationException is a kind of Exception. SerializableAttribute is a kind of Attribute.

#### Tags
- /general/Naming Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_ISNHIS
### Default
#### OriginalId=CA1711
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Identifiers should not have incorrect suffix
#### HelpText
  Types that do not extend certain base types should not use reserved name suffixes. Types and members should not use 'Ex' or 'New' to distinguish them from an earlier version of the same API, instead, use a numeric suffix such as '2' or provide a more meaningful suffix. Concrete type implementations and members should not end 'Impl'. Members instead, should either consider using the suggested alternate 'Core' in replacement of 'Impl' or avoid any suffix at all.

#### Tags
- /general/Naming Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_ISNMK
### Default
#### OriginalId=CA1716
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Identifiers should not match keywords
#### HelpText
  Identifiers which conflict with reserved language keywords should be avoided. Using a reserved keyword as an identifier makes it harder for consumers in other languages to use your API.

#### Tags
- /general/Naming Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_IVTSFI
### Default
#### OriginalId=CA2207
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Initialize value type static fields inline
#### HelpText
  Do not declare explicit static constructors on value types. Initializing static data in explicit static constructors results in a value type that is not marked in metadata as 'beforefieldinit'. In this case, the static constructor is not always guaranteed to be called before instance members on the value type are called.

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_LAST
### Default
#### OriginalId=CA1039
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Lists are strongly typed
#### HelpText
  IList implementations should also provide versions of the IList members that are strongly typed, namely they should specify types other than Object for method and property parameter and return types. Implement the interface members explicitly and make the strongly typed versions public. It is safe to ignore violations of this rule when you are implementing a new object-based collection, such as a linked list, where types based on your collection will determine what the strong type is. These types should expose strongly typed members.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_MANSF
### Default
#### OriginalId=CA2235
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Mark all non-serializable fields
#### HelpText
  All fields that cannot be serialized directly should have the NonSerializedAttribute. Types that have the SerializableAttribute should not have fields of types that do not have the SerializableAttribute unless the fields are marked with the NonSerializedAttribute.

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_MAWAU
### Default
#### OriginalId=CA1018
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Mark attributes with AttributeUsageAttribute
#### HelpText
  The AttributeUsage attribute specifies the targets that are valid for the attribute (see System.AttributeTargets), whether an attribute can appear on a target more than once, and whether the attribute is inheritable.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_MAWAV
### Default
#### OriginalId=CA1016
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Mark assemblies with AssemblyVersionAttribute
#### HelpText
  Assemblies should use version numbers. The version number is considered part of an assembly's identity. Versioning is applied by means of the AssemblyVersion attribute.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_MAWCC
### Default
#### OriginalId=CA1014
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Mark assemblies with CLSCompliantAttribute
#### HelpText
  Assemblies should explicitly state their CLS compliance using the CLSCompliant attribute. An assembly without this attribute is not CLS-compliant. Assemblies, modules, and types can be CLS-compliant even if some parts of the assembly, module, or type are not CLS-compliant. The following rules apply: 1) If the element is marked CLSCompliant, any noncompliant members must have the CLSCompliant attribute present with its argument set to false. 2) A comparable CLS-compliant alternative member must be supplied for each member that is not CLS-compliant.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_MAWCV
### Default
#### OriginalId=CA1017
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Mark assemblies with ComVisibleAttribute
#### HelpText
  The System.Runtime.InteropServices.ComVisible attribute indicates whether COM clients can use the library. Good design dictates that developers explicitly indicate COM visibility. The default value for this attribute is 'true'. However, the best design is to mark the assembly ComVisible false, and then mark types, interfaces, and individual members as ComVisible true, as appropriate.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_MAWNRL
### Default
#### OriginalId=CA1824
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Mark assemblies with NeutralResourcesLanguageAttribute
#### HelpText
  The NeutralResourcesLanguage attribute informs the ResourceManager of the language used to render the neutral culture's resources for an assembly. When looking up resources in the same culture as the neutral resources language, the ResourceManager automatically uses the resources located in the main assembly, instead of searching for a satellite assembly with the current user interface culture for the current thread. This will improve lookup performance for the first resource you load and can reduce your working set.

#### Tags
- /general/Performance Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_MBAWMA
### Default
#### OriginalId=CA1414
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Mark boolean P/Invoke arguments with MarshalAs
#### HelpText
  All boolean P/Invoke parameters and return types should be explicitly marked with the MarshalAs attribute. By default, the system will marshal all booleans as 4-byte UnmanagedType.Bool. This is the correct behavior for Win32 'BOOL' arguments but incorrect for C++ 'bool' arguments, which should be marshaled as 1-byte UnmanagedType.U1. For code maintainability reasons, always explicitly specify the marshaling information for boolean arguments and return values.

#### Tags
- /general/Interoperability Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_MCSIA
### Default
#### OriginalId=CA1412
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Mark ComSource interfaces as IDispatch
#### HelpText
  COM source interfaces should be marked ComInterfaceType.InterfaceIsIDispatch. Visual Basic 6 clients cannot receive events with non-IDispatch interfaces.

#### Tags
- /general/Interoperability Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_MEWF
### Default
#### OriginalId=CA1027
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Mark enums with FlagsAttribute
#### HelpText
  The enumeration appears to be made up of combinable flags. If this true, apply the Flags attribute to the enumeration.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_MMAS
### Default
#### OriginalId=CA1822
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Mark members as static
#### HelpText
  Methods which do not access instance data or call instance methods can be marked as static (Shared in Visual Basic). After doing so, the compiler will emit non-virtual call sites to these members which will prevent a check at runtime for each call that ensures the current object pointer is non-null. This can result in a measurable performance gain for performance-sensitive code. In some cases, the failure to access the current object instance represents a correctness issue.

#### Tags
- /general/Performance Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_MMOWCT
### Default
#### OriginalId=CA2134
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Methods must keep consistent transparency when overriding base methods
#### HelpText
  Transparency visibility must be preserved between overriding methods and the methods that are being overridden.  If the virtual method being overridden or interface method being implemented is security safe-critical or security transparent, then the overriding method must also be either security safe-critical or security transparent.  Similarly, if the method being overridden is security critical, the overriding method must be security critical.

#### Tags
- /general/Security Transparency Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_MSDBMTRT
### Default
#### OriginalId=CA2223
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Members should differ by more than return type
#### HelpText
  Methods in the same type that differ only by return type can be difficult for developers and tools to properly recognize. When extending a type, be sure not to define new methods that differ from base type methods only by type.

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_MSNECCT
### Default
#### OriginalId=CA1059
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Members should not expose certain concrete types
#### HelpText
  Members should not expose certain concrete types.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_MSSBOT
### Default
#### OriginalId=CA2114
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Method security should be a superset of type
#### HelpText
  A method has security set at both the type and method levels. This might not have the intended effect. Security actions on the type level are overridden by security actions on the method level. When employing both type-level and method-level security, type-level security actions that are not also on the method will be ignored when the method executes.

#### Tags
- /general/Security Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_MTNMC
### Default
#### OriginalId=CA1060
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Move P/Invokes to NativeMethods class
#### HelpText
  This type contains members with the DllImport attribute. Members with the DllImport attribute should be contained in classes named NativeMethods, SafeNativeMethods, or UnsafeNativeMethods.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_MTWS
### Default
#### OriginalId=CA2237
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Mark ISerializable types with SerializableAttribute
#### HelpText
  The System.Runtime.Serialization.ISerializable interface allows the type to customize its serialization, while the Serializable attribute enables the runtime to recognize the type as being serializable.

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_MVHWVAT
### Default
#### OriginalId=CA5332
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=MarkVerbHandlersWithValidateAntiforgeryToken
#### HelpText
  Rule that verifies that if the ValidateAntiforgeryTokenAttribute is used to protect against Potential CSRF attack in MVC.

#### Tags
- /general/ASP.NET MVC Security Rules
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_MWFEPWST
### Default
#### OriginalId=CA2232
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Mark Windows Forms entry points with STAThread
#### HelpText
  Assemblies that reference System.Windows.Forms should have the STAThreadAttribute. Failure to apply this attribute will most likely result in an application that does not work. Windows Forms relies on a number of components that use the STA model.

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_NCFSNBV
### Default
#### OriginalId=CA2211
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Non-constant fields should not be visible
#### HelpText
  Static fields should be constant unless you carefully manage access to the field using locks. Using static variables without making them thread safe can compromise execution state. This rule applies to managed code libraries. If the analyzed assembly is an application, it is usually safe to exclude violations of this rule.

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_NSTU
### Default
#### OriginalId=CA1308
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Normalize strings to uppercase
#### HelpText
  Strings should be normalized to upper-case.

#### Tags
- /general/Globalization Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_NTSNBV
### Default
#### OriginalId=CA1034
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Nested types should not be visible
#### HelpText
  Do not use public, protected or protected internal (Protected Friend) nested types as a way of grouping types. Use namespaces for this purpose. There are very limited scenarios where nested types are the best design. Also, nested type member accessibility is not clearly understood by all audiences. Enumerators are exempt from this rule.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_OEAOEOVT
### Default
#### OriginalId=CA1815
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Override equals and operator equals on value types
#### HelpText
  The default System.ValueType implementation might not perform as well as a custom implementation.

#### Tags
- /general/Performance Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_OEOOOE
### Default
#### OriginalId=CA2224
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Override Equals on overloading operator equals
#### HelpText
  Types that redefine the equality operator should redefine Equals as well to ensure that these members return the same results. This helps ensure that types that rely on Equals (such as ArrayList and Hashtable) behave in a manner that is expected and consistent with the equality operator.

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_OFESHPN
### Default
#### OriginalId=CA1717
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Only FlagsAttribute enums should have plural names
#### HelpText
  Plural names indicate that the values of the enumeration can be combined. For example, an enumeration named 'Day' indicates a single day, and an enumeration named 'Days' indicates multiple days. Enumeration values should be combined using the bit-wise OR operator only if the Flags attribute is present on the enumeration.

#### Tags
- /general/Naming Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_OGHCOOE
### Default
#### OriginalId=CA2218
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Override GetHashCode on overriding Equals
#### HelpText
  When overriding Equals, you must also override GetHashCode to guarantee correct behavior with hashtables.

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_OLDSBITB
### Default
#### OriginalId=CA2123
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Override link demands should be identical to base
#### HelpText
  If a virtual method has a LinkDemand, in many cases, so should any override of it, and if an override has a LinkDemand, so should the overridden virtual method. Because it is possible to call any of the overrides of a virtual method explicitly, they should all have the same LinkDemand status or, if not, should be reviewed. This also applies to LinkDemand security checks for methods that part of an interface implementation, because the caller might use an interface-typed reference to access the method.

#### Tags
- /general/Security Transparency Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_OMOCT
### Default
#### OriginalId=CA1036
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Override methods on comparable types
#### HelpText
  Types that implement IComparable should redefine Equals and comparison operators to keep the meanings of less than, greater than, and equals consistent throughout the type.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_OOEOOAAS
### Default
#### OriginalId=CA1013
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Overload operator equals on overloading add and subtract
#### HelpText
  When overloading the addition and subtraction operators, make sure that the equality operator (==) is defined in a consistent manner.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_OOEOOVTE
### Default
#### OriginalId=CA2231
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Overload operator equals on overriding ValueType.Equals
#### HelpText
  Value types that redefine System.ValueType.Equals should redefine the equality operator as well to ensure that these members return the same results. This helps ensure that types that rely on Equals (such as ArrayList and Hashtable) behave in a manner that is expected and consistent with the equality operator.

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_OOHNA
### Default
#### OriginalId=CA2225
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Operator overloads have named alternates
#### HelpText
  When redefining operators, implement named methods to provide access to the operator functionality from languages that do not support operator overloading. For example, the functionality of the '+' operator should also be accessible using an 'Add' method.

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_OSHSO
### Default
#### OriginalId=CA2226
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Operators should have symmetrical overloads
#### HelpText
  Overload operators that have related meanings so that their behavior is consistent. For example, when overloading the equality operator, you should also overload the inequality operator to ensure they return opposite results for the same input values.

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_OSNO
### Default
#### OriginalId=CA2233
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Operations should not overflow
#### HelpText
  Arithmetic operations should not be done without first validating the operands to prevent overflow.

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_PDMFOF
### Default
#### OriginalId=CA2239
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Provide deserialization methods for optional fields
#### HelpText
  If a type contains fields attributed as OptionalField, then it should implement the corresponding special deserialization methods.

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_PDSBP
### Default
#### OriginalId=CA1901
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=P/Invoke declarations should be portable
#### HelpText
  .

#### Tags
- /general/Portability Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_PEEVMBT
### Default
#### OriginalId=CA5415
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=PagesEnableEventValidationMustBeTrue
#### HelpText
  Verify if event validation is enabled.

#### Tags
- /general/ASP.NET.Security.Configuration
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_PEPSE
### Default
#### OriginalId=CA1400
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=P/Invoke entry points should exist
#### HelpText
  Methods decorated with the DllImport attribute should point to existing unmanaged entry points. There is no compile-time check to ensure that methods decorated with the DllImport attribute actually exist in the referenced unmanaged dll. In the event that an entry point does not exist or the specified argument list is not correct, a runtime exception will be generated.

#### Tags
- /general/Interoperability Rules
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_PEVSMSBT
### Default
#### OriginalId=CA5414
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=PagesEnableViewStateMacShouldBeTrue
#### HelpText
  Verifies that the viewstate mac is enabled.

#### Tags
- /general/ASP.NET.Security.Configuration
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_PJAOM
### Default
#### OriginalId=CA1814
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Prefer jagged arrays over multidimensional
#### HelpText
  Multidimensional arrays can have a negative impact on performance. Use a jagged array if possible.

#### Tags
- /general/Performance Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_PNSMBD
### Default
#### OriginalId=CA1725
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Parameter names should match base declaration
#### HelpText
  For usability reasons, parameter names in overridden methods should match those of the base declaration.

#### Tags
- /general/Naming Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_PNSNMGM
### Default
#### OriginalId=CA1721
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Property names should not match get methods
#### HelpText
  A Get method was found with the same name as a property. Get methods and properties should have names that clearly distinguish their function. See the design guidelines for information regarding choosing properties over methods.

#### Tags
- /general/Naming Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_PNSNMMN
### Default
#### OriginalId=CA1719
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Parameter names should not match member names
#### HelpText
  Parameter names should be distinct from member names.

#### Tags
- /general/Naming Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_POAM
### Default
#### OriginalId=CA1041
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Provide ObsoleteAttribute message
#### HelpText
  The ObsoleteAttribute.Message property provides the text message displayed when an obsolete type or member is compiled. This message should provide information on the replacement for the obsolete element.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_POSHNOBEVI
### Default
#### OriginalId=CA2111
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Pointers should not be visible
#### HelpText
  IntPtr and UIntPtr fields should be declared as private. Exposing non-private pointers can cause a security weakness.

#### Tags
- /general/Security Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_PSNBSC
### Default
#### OriginalId=CA5122
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=P/Invoke declarations should not be safe-critical.
#### HelpText
  Since P/Invokes may not be called by transparent code, they should not be marked as safe-critical methods.  Doing so can lead to confusion on the part of developers who may believe that their transparent code should be able to call the P/Invoke method since it is marked safe-critical.

#### Tags
- /general/Security Transparency Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_PSNBV
### Default
#### OriginalId=CA1401
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=P/Invokes should not be visible
#### HelpText
  Interop layer should not be public. The DllImport attribute should not be applied to publicly accessible members (public or protected).

#### Tags
- /general/Interoperability Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_PSNBWO
### Default
#### OriginalId=CA1044
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Properties should not be write only
#### HelpText
  Write-only properties usually indicate a flawed design.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_PSNRA
### Default
#### OriginalId=CA1819
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Properties should not return arrays
#### HelpText
  Properties that return arrays are prone to code inefficiencies. Consider using a collection or making this a method. See the design guidelines for more information.

#### Tags
- /general/Performance Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_PSUOIOS
### Default
#### OriginalId=CA2234
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Pass System.Uri objects instead of strings
#### HelpText
  If there are two overloads one taking System.Uri and one taking System.String, library code should never call the string-based overload.

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_PVRSBE
### Default
#### OriginalId=CA5417
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=PagesValidateRequestShouldBeEnabled
#### HelpText
  Verify that validateRequest is enabled.

#### Tags
- /general/ASP.NET.Security.Configuration
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_PVSEMSBA
### Default
#### OriginalId=CA5418
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=PagesViewStateEncryptionModeShouldBeAlways
#### HelpText
  Verify that the viewstate encryption mode is not configured to never encrypt.

#### Tags
- /general/ASP.NET.Security.Configuration
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_RCTA
### Default
#### OriginalId=CA2004
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Remove calls to GC.KeepAlive
#### HelpText
  If converting to SafeHandle usage, remove all calls to GC.KeepAlive(object). Classes relying on SafeHandle do not require calls to GC.KeepAlive, and unnecessary calls can make code harder to maintain.

#### Tags
- /general/Reliability Rules
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_RDAPOU
### Default
#### OriginalId=CA2107
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Review deny and permit only usage
#### HelpText
  Use of Deny or PermitOnly should be carefully reviewed. Use of Deny or PermitOnly should be carefully considered, as they are not useful in some cases. For example, permissions that are path-based (like FileIOPermission and RegistryPermission) should not be used with Deny, because different paths might actually point to the same location. If callers are granted the right to assert permissions by the security policy, then they can terminate a stack walk before it reaches your Deny or PermitOnly. If a caller has been granted powerful permissions (such as the ability to call unmanaged code), then calling Deny or PermitOnly cannot truly stop it from doing whatever it chooses. Also consider that Deny and PermitOnly do not affect a LinkDemand. For instance, if you deny some permission P and call a method with a LinkDemand for P, the Deny will not affect the result of the LinkDemand.

#### Tags
- /general/Security Rules
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_RDSOVT
### Default
#### OriginalId=CA2108
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Review declarative security on value types
#### HelpText
  A Demand or a LinkDemand on a structure does not prevent creation of an instance of that structure.

#### Tags
- /general/Security Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_REF
### Default
#### OriginalId=CA1821
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Remove empty finalizers
#### HelpText
  Finalizers should be avoided where possible, to avoid the additional performance overhead involved in tracking object lifetime.

#### Tags
- /general/Performance Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_RIS
### Default
#### OriginalId=CA2103
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Review imperative security
#### HelpText
  Use of imperative demands can lead to unforeseen security problems. The values used to construct a permission should not change within the scope of the demand call. For some components the scope spans from the demand call to end of the method; for others it spans from the demand call until the component is finalized. If the values used to construct the permission are fields or properties, they can be changed within the scope of the demand call. This can lead to race conditions, mutable read-only arrays, and problems with boxed value types.

#### Tags
- /general/Security Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_RMCPSBA
### Default
#### OriginalId=CA5411
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=RoleManagerCookieProtectionShouldBeAll
#### HelpText
  The rule verifies that the system.web.rolemanager cookieProtection is set to All which enforce both the cookie to be encrypted and validated by the server.

#### Tags
- /general/ASP.NET.Security.Configuration
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_RMCRBT
### Default
#### OriginalId=CA5412
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=RoleManagerCookieRequireSSLShouldBeTrue
#### HelpText
  The rule verifies that the system.web.rolemanager cookieRequireSSL attribute is set to True which force the role manager cookie to specify the secure attribute. This indicates the browser to only provide the cookie over SSL.

#### Tags
- /general/ASP.NET.Security.Configuration
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_RMCSESBF
### Default
#### OriginalId=CA5413
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=RoleManagerCookieSlidingExpirationShouldBeTrue
#### HelpText
  
        The rule verifies that if the system.web.rolemanager cookieSlidingExpiration is set to false when the site is being serviced over HTTP. This will force the authentication cookie to have a fix timeout value instead of being refreshed by each request. Since the cookie will traverse over clear text network and can be sniffed, having a fix timeout value on the cookie will limit the amount of time the cookie can be replayed.
        If the cookie is traversing over HTTPS, it is less likely to be intercepted and having the cookieSlidingExpiration setting to True will cause the timeout to be refreshed after each request which gives a better user experience.
      

#### Tags
- /general/ASP.NET.Security.Configuration
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_RMFN
### Default
#### OriginalId=CA1504
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Review misleading field names
#### HelpText
  Review field names which, by convention, appear to indicate they are instance or static but, in fact, are not. This rule fires against instance fields which have names prefixed with "s_" and static fields which are prefixed with "m_".

#### Tags
- /general/Maintainability Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_RRAWPA
### Default
#### OriginalId=CA1025
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Replace repetitive arguments with params array
#### HelpText
  Several instances of same-type arguments can be better implemented as a parameter array argument. Generally, if a member declares three or more arguments of the same type, consider using a parameter array.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_RSCWSBCC
### Default
#### OriginalId=CA1701
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Resource string compound words should be cased correctly
#### HelpText
  Avoid creating compound words from terms which exist in the dictionary as discrete terms. Do not create a compound word such as 'StopWatch' or 'PopUp'. These terms are recognized in the dictionary and should be cased as 'Stopwatch' and 'Popup'.

#### Tags
- /general/Naming Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_RSSBSC
### Default
#### OriginalId=CA1703
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Resource strings should be spelled correctly
#### HelpText
  The individual words that make up a resource string should not be abbreviated and should be spelled correctly. If this rule generates a false positive on a term that should be recognized, add the word to the FxCop custom dictionary.

#### Tags
- /general/Naming Rules
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_RSUCSU
### Default
#### OriginalId=CA2118
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Review SuppressUnmanagedCodeSecurityAttribute usage
#### HelpText
  Calling a method with the SuppressUnmanagedCodeSecurityAttribute applied to it can create a security weakness. Unmanaged code security checks ensure that all callers in the call stack have permission to execute unmanaged code. Disabling code security for P/Invoke methods allows callers that do not have this permission to breach security. This is acceptable only if the code is completely harmless, or callers have no way to pass arbitrary arguments through to the unmanaged code.

#### Tags
- /general/Security Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_RTPSD
### Default
#### OriginalId=CA2200
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Rethrow to preserve stack details
#### HelpText
  Use the IL rethrow instruction to preserve original stack details when re-raising a caught exception.

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_RUL
### Default
#### OriginalId=CA1804
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Remove unused locals
#### HelpText
  Remove locals that are not used or are only assigned to in method implementations.

#### Tags
- /general/Performance Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_RUP
### Default
#### OriginalId=CA1801
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Review unused parameters
#### HelpText
  Review parameters in non-virtual methods that are not used in the method body to ensure no correctness exists around failure to access them. Unused parameters incur maintenance and performance costs. Sometimes a violation of this rule can point to an implementation bug in the method (i.e. the parameter should actually have been used in the method body). Exclude warnings of this rule if the parameter has to exist because of backward compatibility.

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_RVEH
### Default
#### OriginalId=CA2109
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Review visible event handlers
#### HelpText
  It appears that an event handler is externally visible or that an EventArgs parameter is being exposed in a visible method decorated with a security demand. There can be problems exposing sensitive functionality in an event handler function; the security demand might not do what you expect.

#### Tags
- /general/Security Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_SA
### Default
#### OriginalId=CA2106
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Secure asserts
#### HelpText
  Asserting a security permission without performing any security checks can leave an exploitable security weakness in your code. A security stack walk stops when a security permission is asserted. If you assert a permission without performing any checks on the caller, the caller might be able to indirectly execute code using your permissions. Asserts without security checks are only permissible when you are certain that the assert cannot be used in a harmful fashion, namely, if the code you call is harmless, or users have no way to pass arbitrary information to code that you call.

#### Tags
- /general/Security Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_SCI
### Default
#### OriginalId=CA1304
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Specify CultureInfo
#### HelpText
  If an overload exists that takes a CultureInfo argument, it should always be called in favor of an overload that does not. The CultureInfo type contains culture-specific information required for performing numeric and string operations, such as casing, formatting, and string comparisons. In scenarios where conversion and parsing behavior should never change between cultures, specify CultureInfo.InvariantCulture, otherwise, specify CultureInfo.CurrentCulture.

#### Tags
- /general/Globalization Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_SCSBP
### Default
#### OriginalId=CA2121
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Static constructors should be private
#### HelpText
  Non-private static constructors can cause unexpected behaviors, particularly when executed multiple times. This violation can occur if a type declares static data but has not explicitly  declared a static constructor. In this case, some compilers will generate an externally visible static constructor.

#### Tags
- /general/Security Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_SESECO
### Default
#### OriginalId=CA2120
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Secure serialization constructors
#### HelpText
  Serializable types that have a constructor protected by a security demand must apply the same security demands to the serialization constructor. Apply the demand using declarative security.

#### Tags
- /general/Security Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_SHTSBS
### Default
#### OriginalId=CA1052
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Static holder types should be sealed
#### HelpText
  Static holder types do not provide functionality that derived instances can extend. Inheriting from such a type indicates a flawed design.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_SHTSNHC
### Default
#### OriginalId=CA1053
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Static holder types should not have constructors
#### HelpText
  Instances of types that define only static members do not need to be created. Many compilers will automatically add a public default constructor if no constructor is specified. To prevent this, adding an empty private constructor may be required.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_SLFDT
### Default
#### OriginalId=CA1306
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Set locale for data types
#### HelpText
  In most cases, Locale should be explicitly set to CultureInfo.InvariantCulture on DataSet and DataTable instances. Upon creation of a DataSet or DataTable instance, the Locale is set to the current culture. In most cases, the Locale should be set to CultureInfo.InvariantCulture to guarantee proper sorting behavior in all cultures.

#### Tags
- /general/Globalization Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_SMBO
### Default
#### OriginalId=CA1300
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Specify MessageBoxOptions
#### HelpText
  In order to run correctly on right-to-left systems, all calls to MessageBox.Show should use the overload that specifies MessageBoxOptions as an argument. Programs should detect whether they are running on a right-to-left system at run-time and pass the appropriate MessageBoxOptions value in order to display correctly.

#### Tags
- /general/Globalization Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_SMFSA
### Default
#### OriginalId=CA2101
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Specify marshaling for P/Invoke string arguments
#### HelpText
  When marshaling strings as ANSI (or as Auto on Win9x), some characters may be changed. If best-fit mapping is on, strings that appear different in Unicode will be marshaled to identical ANSI strings, which may lead to incorrect security decisions. Turning best-fit mapping off reduces this risk, as all characters without equivalents are mapped to '?'. Also, note that CharSet.Ansi is the default setting for all string marshaling; Unicode marshaling must be specified explicitly, either as a CharSet setting of DllImport or StructLayout, or as a MarshalAs attribute with a Unicode (or system-dependent) UnmanagedType.

#### Tags
- /general/Globalization Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_SMTSPI
### Default
#### OriginalId=CA2119
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Seal methods that satisfy private interfaces
#### HelpText
  Externally visible types that implement non-public interfaces should not be extensible. Types that extend public types with non-public interfaces can override interface members. This can compromise object behavior or create a security vulnerability.

#### Tags
- /general/Security Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_SP
### Default
#### OriginalId=CA1305
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Specify IFormatProvider
#### HelpText
  If an overload exists that takes an IFormatProvider argument, it should always be called in favor of an overload that does not. Some methods in the runtime convert a value to or from a string representation and take a string parameter that contains one or more characters, called format specifiers, which indicate how the value is to be converted. If the meaning of the format specifier varies by culture, a formatting object supplies the actual characters used in the string representation. In scenarios where sorting and comparison behavior should never change between cultures, specify CultureInfo.InvariantCulture, otherwise, specify CultureInfo.CurrentCulture.

#### Tags
- /general/Globalization Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_SRSLSNBPWLD
### Default
#### OriginalId=CA2135
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Level 2 assemblies should not contain LinkDemands
#### HelpText
  LinkDemands are deprecated in the level 2 security rule set.  Instead of using LinkDemands to enforce JIT time security, SecurityCritical methods, types, and fields should be used instead.

#### Tags
- /general/Security Transparency Rules
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_SSC
### Default
#### OriginalId=CA1307
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Specify StringComparison
#### HelpText
  If an overload exists that takes a StringComparison argument, it should always be called in favor of an overload that does not.

#### Tags
- /general/Globalization Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_STSNEF
### Default
#### OriginalId=CA2112
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Secured types should not expose fields
#### HelpText
  Fields must be secured with a security check other than LinkDemand.

#### Tags
- /general/Security Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_SUOCSUO
### Default
#### OriginalId=CA1057
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=String URI overloads call System.Uri overloads
#### HelpText
  If a method overloads another method by replacing a System.Uri parameter with a string, then the string overload should simply build a Uri object from the string, and pass the result to the string overload.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_TASNC
### Default
#### OriginalId=CA2136
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Members should not have conflicting transparency annotations
#### HelpText
  Transparency attributes are applied from larger scopes inward.  For instance, if a type is marked as entirely security critical, than all methods introduced by the type will also be security critical.  Members should not have transparency annotations which conflict with larger scoped annotations, as these smaller scoped annotations will be ignored by the CLR and can be misleading during a code review.  Methods not introduced by their type, such as virtual methods being overridden from a base type or interface methods being implemented, do have their annotations considered under the level 2 security rule set and are not considered by this rule.

#### Tags
- /general/Security Transparency Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_TCMNUCA
### Default
#### OriginalId=CA2150
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Transparent code may not use security critical attributes
#### HelpText
  Transparent code must not use security critical attributes.  This includes using security critical constructors, properties, or fields of attributes.  Violations of this rule will result in an exception when code attempts to retrieve the custom attributes from the transparent target.

#### Tags
- /general/Security Transparency Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_TFESUSL
### Default
#### OriginalId=CA1820
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Test for empty strings using string length
#### HelpText
  To test for empty strings, check if String.Length is equal to zero. Constructs such as "".Equals(someString) and String.Empty.Equals(someString) are less efficient than testing the string length. Replace these with checks for someString.Length == 0.

#### Tags
- /general/Performance Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_TFN
### Default
#### OriginalId=CA2242
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Test for NaN correctly
#### HelpText
  Direct comparisons against 'Single.NaN' or 'Double.NaN' (not a number) always return true for inequality and false for all other comparisons; use 'Single.IsNaN' or 'Double.IsNaN' to check if a floating point value is NaN.

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_TLDRID
### Default
#### OriginalId=CA2126
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Type link demands require inheritance demands
#### HelpText
  Unsealed types secured by a LinkDemand should also specify an InheritanceDemand. Without an InheritanceDemand, the link demand can be circumvented by overriding a method in a derived class.

#### Tags
- /general/Security Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_TMBALACABT
### Default
#### OriginalId=CA2146
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Types must be at least as critical as their base types and interfaces
#### HelpText
  While any type may derive from a transparent type or interface, restrictions apply as to the types that can inherit from or implement safe-critical or critical types.  Only safe-critical or critical types may derive from or implement safe-critical interfaces and base types.  Only critical types may derive from or implement critical interfaces and base types.

#### Tags
- /general/Security Transparency Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_TMMBV
### Default
#### OriginalId=CA2137
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Transparent methods must contain only verifiable IL
#### HelpText
  Transparent code must be fully verifiable.  This rule looks for any use of pointer types to check for unverifiable code, however it is not a complete verifier and PEVerify / transparent must be run on assemblies to ensure that all of their transparent code is verifiable.

#### Tags
- /general/Security Transparency Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_TMMNCNC
### Default
#### OriginalId=CA2149
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Transparent methods must not call into native code
#### HelpText
  Transparent code may not call native code directly.  This rule looks for any transparent code which calls a method stub (such as a P/Invoke declaration) which is really a direct call into native code.

#### Tags
- /general/Security Transparency Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_TMMNCSUCSM
### Default
#### OriginalId=CA2138
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Transparent methods must not call methods with the SuppressUnmanagedCodeSecurity attribute
#### HelpText
  P/Invoke and COM interop methods with the SuppressUnmanagedCodeSecurity attribute result in a LinkDemand being done against the calling method.  Since security transparent code may not satisfy LinkDemands, it may also not call methods with SuppressUnmanagedCodeSecurity either on the method itself or on the type containing the method.

#### Tags
- /general/Security Transparency Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_TMMNHPCE
### Default
#### OriginalId=CA2139
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Transparent methods may not use the HandleProcessCorruptingExceptions attribute
#### HelpText
  The HandleProcessCorruptingExceptions attribute may only be used by security critical methods, and will not be honored if it is applied to a transparent method.

#### Tags
- /general/Security Transparency Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_TMMNRCC
### Default
#### OriginalId=CA2140
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Transparent code must not reference security critical items
#### HelpText
  Transparent code cannot refer to security critical methods, types, or fields.  At runtime these references will result in MemberAccessExceptions or TypeLoadExceptions.

#### Tags
- /general/Security Transparency Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_TMMNSLD
### Default
#### OriginalId=CA2141
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Transparent methods must not satisfy LinkDemands
#### HelpText
  Satisfying a LinkDemand is a security sensitive operation which can cause unintentional elevation of privilege.  Security transparent code must not satisfy LinkDemands, since it is not subject to the same security audit requirements as security critical code.  Transparent methods is security rule set level 1 assemblies will cause all LinkDemands they satisfy to be converted to full demands at runtime, which can cause performance problems.  In security rule set level 2 assemblies, transparent methods will fail to JIT if they attempt to satisfy a LinkDemand.

#### Tags
- /general/Security Transparency Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_TMMNUSA
### Default
#### OriginalId=CA2147
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Transparent code may not use security asserts
#### HelpText
  Transparent code may not use security asserts, since asserting permissions can result in elevating the effective permissions of the call stack.  Transparent code which attempts to assert will receive an InvalidOperationException at runtime.

#### Tags
- /general/Security Transparency Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_TMSNBPWLD
### Default
#### OriginalId=CA2142
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Transparent code should not be protected with LinkDemands
#### HelpText
  Security transparent code should not be responsible for verifying the security of an operation, and therefore should not be protected from partial trust callers with LinkDemands.

#### Tags
- /general/Security Transparency Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_TMSND
### Default
#### OriginalId=CA2143
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Transparent methods should not use security demands
#### HelpText
  Security transparent code should not be responsible for verifying the security of an operation, and therefore should not demand permissions.  Any code which is performing security checks, such as security demands, should be safe-critical instead.

#### Tags
- /general/Security Transparency Rules
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_TMSNLAFBA
### Default
#### OriginalId=CA2144
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Transparent code should not load assemblies from byte arrays
#### HelpText
  Assemblies loaded from byte arrays inherit the grant set of the loading assembly.  Since this means that the loaded assembly may be fully trusted, any calls to load from byte array from trusted code should be reviewed to ensure that it is secure.  Transparent code is not subjected to the same audit scrutiny as critical code, and therefore should not load assemblies from byte arrays.

#### Tags
- /general/Security Transparency Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_TMSNUSUCS
### Default
#### OriginalId=CA2145
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Transparent methods should not be decorated with the SuppressUnmanagedCodeSecurityAttribute
#### HelpText
  Methods decorated with the SuppressUnmanagedCodeSecurity attribute have an implicit LinkDemand placed upon all of their callers.  This LinkDemand requires that the calling code be security critical.  Marking the method which uses SuppressUnmanagedCodeSecurity as security critical makes this requirement more obvious for callers of the method.

#### Tags
- /general/Security Transparency Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_TNSNMN
### Default
#### OriginalId=CA1724
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Type names should not match namespaces
#### HelpText
  Identifiers which conflict in whole or in part with namespace names should be avoided. Names that describe the purpose or contents of a type are preferred.

#### Tags
- /general/Naming Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_TSBD
### Default
#### OriginalId=CA5409
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=TraceShouldBeDisabled
#### HelpText
  The rule verifies that the system.web.trace enabled setting is set to false which disable tracing. It is recommended to disable tracing on production servers to make sure that an attacker cannot gain information from the trace about your application. Trace information can help an attacker probe and compromise your application.

#### Tags
- /general/ASP.NET.Security.Configuration
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_TSNECBT
### Default
#### OriginalId=CA1058
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Types should not extend certain base types
#### HelpText
  It is best not to extend some base types or to prefer extending better alternatives to those base types.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_TTODFSBD
### Default
#### OriginalId=CA1001
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Types that own disposable fields should be disposable
#### HelpText
  Types that declare disposable members should also implement IDisposable. If the type does not own any unmanaged resources, do not implement a finalizer on it.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_TTONRSBD
### Default
#### OriginalId=CA1049
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Types that own native resources should be disposable
#### HelpText
  Types that allocate unmanaged resources should implement IDisposable to allow callers to release those resources on demand. Failure to implement IDisposable can result in unmanaged resources being unavailable or underutilized.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_UEWA
### Default
#### OriginalId=CA1030
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Use events where appropriate
#### HelpText
  A method name suggestive of event functionality was encountered.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_UGEHI
### Default
#### OriginalId=CA1003
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Use generic event handler instances
#### HelpText
  Do not declare new delegates to be used as event handlers when targeting a version of the .NET Framework that supports generics. Use an instance EventHandler<T> instead.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_UGWA
### Default
#### OriginalId=CA1007
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Use generics where appropriate
#### HelpText
  References passed to ref parameters must be the exact type of the parameter. Using generics enable the method for general use.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_UIOSAFI
### Default
#### OriginalId=CA1043
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Use integral or string argument for indexers
#### HelpText
  Indexers (indexed properties) should use either integer or string types for indexing values. These types are easy to use and commonly used for indexing data structures; using other types can significantly reduce the usability of the library. For example, public char this [int index] is the C# signature for the String type's indexer.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_ULWA
### Default
#### OriginalId=CA1802
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Use literals where appropriate
#### HelpText
  Prefer literals over InitOnly fields if values do not have to be calculated at runtime.

#### Tags
- /general/Performance Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_UMEOW
### Default
#### OriginalId=CA2205
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Use managed equivalents of Win32 API
#### HelpText
  Use managed equivalents to Win32 API whenever possible.

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_UOAFTF
### Default
#### OriginalId=CA1903
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Use only API from targeted framework
#### HelpText
  

#### Tags
- /general/Portability Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_UOSC
### Default
#### OriginalId=CA1309
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Use ordinal StringComparison
#### HelpText
  For non-linguistic comparisons, StringComparison.Ordinal or StringComparison.OrdinalIgnoreCase should be used instead of the linguistically-sensitive StringComparison.InvariantCulture.

#### Tags
- /general/Globalization Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_UPFVA
### Default
#### OriginalId=CA2230
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Use params for variable arguments
#### HelpText
  Do not use the varargs calling convention to accept a variable number of arguments. In the managed world, the 'params' and 'ParamArray' keywords provide this functionality..

#### Tags
- /general/Usage Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_UPSNBS
### Default
#### OriginalId=CA1054
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=URI parameters should not be strings
#### HelpText
  If a parameter name contains "uri" or "url" or "urn", and it's typed as string, the parameter type should be changed to System.Uri, unless there is an overload method where the same parameter is typed as System.Uri.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_UPT
### Default
#### OriginalId=CA1726
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Use preferred terms
#### HelpText
  Use preferred terms over deprecated alternates.

#### Tags
- /general/Naming Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_UPWA
### Default
#### OriginalId=CA1024
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Use properties where appropriate
#### HelpText
  Properties should be used instead of Get/Set methods in most situations. Methods are preferable to properties in the following situations: the operation is a conversion, is expensive or has an observable side-effect; the order of execution is important; calling the member twice in succession creates different results; a member is static but returns a mutable value; or the member returns an array.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Minor


## FXCOP_URPRSHNOBEST
### Default
#### OriginalId=CA1056
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=URI properties should not be strings
#### HelpText
  If a property name contains "uri" or "url" or "urn" and it's typed as string, it should be changed to System.Uri.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_URVSNBS
### Default
#### OriginalId=CA1055
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=URI return values should not be strings
#### HelpText
  If a function name contains "uri" or "url" or "urn" and the return type is string, the return type should be changed to System.Uri.

#### Tags
- /general/Design Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_USHTENR
### Default
#### OriginalId=CA2006
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Use SafeHandle to encapsulate native resources
#### HelpText
  Use of IntPtr in managed code may indicate a potential security and reliability problem. All uses of IntPtr must be reviewed to determine whether use of a SafeHandle (or similar technology) is required in its place. Problems will occur if the IntPtr represents some native resource (memory, file handle, socket etc.) that managed code is considered to own. I.e. managed code is expected to in some way release the resource and failure to do so would cause resource leakage. In such scenarios security or reliability problems will also exist if multithreaded access is allowed to the IntPtr and a means of releasing the resource represented by the IntPtr. These problems involve recycling of the IntPtr value on resource release while simultaneous use of the resource is being made on another thread, leading to race conditions where one thread can read or write data associated with the wrong resource. For example, if your type stores an OS handle as an IntPtr and allows users to call both Close and any other method using that handle simultaneously (without some kind of synchronization), your code has a handle recycling problem, which causes data corruption and often a security vulnerability. SafeHandle (and its sibling class CriticalHandle) provide a mechanism for encapsulating a native handle to a resource so that such threading problems can be avoided (along with other issues such as the need to carefully control the lifetime of managed objects that contain a copy of the native handle over calls to native methods; ie, you can often remove calls to GC.KeepAlive). There are performance overheads implicit in using SafeHandle (and, to a lesser degree, CriticalHandle) which can often be mitigated through careful design.

#### Tags
- /general/Reliability Rules
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_VNSNMFN
### Default
#### OriginalId=CA1500
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Variable names should not match field names
#### HelpText
  Instance field and variable names should not be identical within the same scope.

#### Tags
- /general/Maintainability Rules
- /tool/FxCop

#### Settings
- Priority=Critical


## FXCOP_VRSBE
### Default
#### OriginalId=CA5328
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=ValidateRequestShouldBeEnabled
#### HelpText
  Rule that will identify if the ValidateRequest is disabled on a certain page.

#### Tags
- /general/ASP.NET Security Rules
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_VSEMSBA
### Default
#### OriginalId=CA5329
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=ViewStateEncryptionModeShouldBeAlways
#### HelpText
  Rule that will identify if the ViewStateEncryptionMode is not set to Never on a certain page.

#### Tags
- /general/ASP.NET Security Rules
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_VSUKSBS
### Default
#### OriginalId=CA5332
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=ViewStateUserKeyShouldBeSet
#### HelpText
  Verifies if the ViewStateEncryptionMode directive is not set to Never  on a certain page.

#### Tags
- /general/ASP.NET Security Rules
- /tool/FxCop

#### Settings
- Priority=Major


## FXCOP_VTFSBP
### Default
#### OriginalId=CA1900
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Value type fields should be portable
#### HelpText
  Structures with explicit layout containing misaligned fields cause crashes on 64-bit platforms.

#### Tags
- /general/Portability Rules
- /tool/FxCop

#### Settings
- Priority=Blocker


## FXCOP_WVFCIOT
### Default
#### OriginalId=CA2124
#### Enabled=true
#### NumericType=true
#### Warning=true
#### DisplayName=Wrap vulnerable finally clauses in outer try
#### HelpText
  Finally clauses that restore security-related state should be wrapped in an outer try block. This will prevent an exception filter further up the stack from executing before a secure environment can be restored. Exception filters that run code expressions in the first pass after the guarded try blocks and before the associated finally block represent a possible security vulnerability. Examples of vulnerable functionality in finally clauses that should be protected against this include: calls to RevertAssert on an asserted permission, undoing a temporary impersonation, reversing an internal flag that bypasses a security check, and restoring the culture associated with a thread.

#### Tags
- /general/Security Rules
- /tool/FxCop

#### Settings
- Priority=Critical
