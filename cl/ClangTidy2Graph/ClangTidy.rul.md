# ToolDescription
## Default
### ID=ClangTidy
### Description
  clang-tidy is a clang-based C++ “linter” tool. Its purpose is to provide an extensible framework for diagnosing and fixing typical programming errors, like style violations, interface misuse, or bugs that can be deduced via static analysis. clang-tidy is modular and provides a convenient interface for writing new checks.

  OpenStaticAnalyzer uses original clang-tidy checkers “as is”, without any guaranties that their results are correct. All statements of the clang-tidy license apply here as well.

# Includes
- ClangTidy.rul_metadata.md

# Metrics
## CT_ABS_DA
### Default
#### OriginalId=abseil-duration-addition
#### Enabled=false
#### Warning=true
#### DisplayName=Duration Addition
#### HelpText
  Check for cases where addition should be performed in the absl::Time domain. When adding two values, and one is known to be an absl::Time, we can infer that the other should be interpreted as an absl::Duration of a similar scale, and make that inference explicit.

  Examples:

  ``` cpp
  // Original - Addition in the integer domain
  int x;
  absl::Time t;
  int result = absl::ToUnixSeconds(t) + x;

  // Suggestion - Addition in the absl::Time domain
  int result = absl::ToUnixSeconds(t + absl::Seconds(x));

  ```


  (Clang-Tidy original name: abseil-duration-addition)

#### Tags
- /general/Abseil
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_ABS_DC
### Default
#### OriginalId=abseil-duration-comparison
#### Enabled=false
#### Warning=true
#### DisplayName=Duration Comparison
#### HelpText
  Checks for comparisons which should be in the absl::Duration domain instead of the floating point or integer domains.

  N.B.: In cases where a Duration was being converted to an integer and then compared against a floating-point value, truncation during the Duration conversion might yield a different result. In practice this is very rare, and still indicates a bug which should be fixed.

  Examples:

  ``` cpp
  // Original - Comparison in the floating point domain
  double x;
  absl::Duration d;
  if (x < absl::ToDoubleSeconds(d)) ...

  // Suggested - Compare in the absl::Duration domain instead
  if (absl::Seconds(x) < d) ...


  // Original - Comparison in the integer domain
  int x;
  absl::Duration d;
  if (x < absl::ToInt64Microseconds(d)) ...

  // Suggested - Compare in the absl::Duration domain instead
  if (absl::Microseconds(x) < d) ...

  ```


  (Clang-Tidy original name: abseil-duration-comparison)

#### Tags
- /general/Abseil
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_ABS_DCC
### Default
#### OriginalId=abseil-duration-conversion-cast
#### Enabled=false
#### Warning=true
#### DisplayName=Duration Conversion Cast
#### HelpText
  Checks for casts of absl::Duration conversion functions, and recommends the right conversion function instead.

  Examples:

  ``` cpp
  // Original - Cast from a double to an integer
  absl::Duration d;
  int i = static_cast<int>(absl::ToDoubleSeconds(d));

  // Suggested - Use the integer conversion function directly.
  int i = absl::ToInt64Seconds(d);


  // Original - Cast from a double to an integer
  absl::Duration d;
  double x = static_cast<double>(absl::ToInt64Seconds(d));

  // Suggested - Use the integer conversion function directly.
  double x = absl::ToDoubleSeconds(d);

  ```


  Note: In the second example, the suggested fix could yield a different result, as the conversion to integer could truncate. In practice, this is very rare, and you should use absl::Trunc to perform this operation explicitly instead.

  (Clang-Tidy original name: abseil-duration-conversion-cast)

#### Tags
- /general/Abseil
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_ABS_DD
### Default
#### OriginalId=abseil-duration-division
#### Enabled=false
#### Warning=true
#### DisplayName=Duration Division
#### HelpText
  absl::Duration arithmetic works like it does with integers. That means that division of two absl::Duration objects returns an int64 with any fractional component truncated toward 0. See [this link](https://github.com/abseil/abseil-cpp/blob/29ff6d4860070bf8fcbd39c8805d0c32d56628a3/absl/time/time.h\#L137) for more information on arithmetic with absl::Duration.

  For example:

  ``` cpp
  absl::Duration d = absl::Seconds(3.5);
  int64 sec1 = d / absl::Seconds(1);     // Truncates toward 0.
  int64 sec2 = absl::ToInt64Seconds(d);  // Equivalent to division.
  assert(sec1 == 3 && sec2 == 3);

  double dsec = d / absl::Seconds(1);  // WRONG: Still truncates toward 0.
  assert(dsec == 3.0);

  ```


  If you want floating-point division, you should use either the absl::FDivDuration() function, or one of the unit conversion functions such as absl::ToDoubleSeconds(). For example:

  ``` cpp
  absl::Duration d = absl::Seconds(3.5);
  double dsec1 = absl::FDivDuration(d, absl::Seconds(1));  // GOOD: No truncation.
  double dsec2 = absl::ToDoubleSeconds(d);                 // GOOD: No truncation.
  assert(dsec1 == 3.5 && dsec2 == 3.5);

  ```


  This check looks for uses of absl::Duration division that is done in a floating-point context, and recommends the use of a function that returns a floating-point value.

  (Clang-Tidy original name: abseil-duration-division)

#### Tags
- /general/Abseil
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_ABS_DFF
### Default
#### OriginalId=abseil-duration-factory-float
#### Enabled=false
#### Warning=true
#### DisplayName=Duration Factory Float
#### HelpText
  Checks for cases where the floating-point overloads of various absl::Duration factory functions are called when the more-efficient integer versions could be used instead.

  This check will not suggest fixes for literals which contain fractional floating point values or non-literals. It will suggest removing superfluous casts.

  Examples:

  ``` cpp
  // Original - Providing a floating-point literal.
  absl::Duration d = absl::Seconds(10.0);

  // Suggested - Use an integer instead.
  absl::Duration d = absl::Seconds(10);


  // Original - Explicitly casting to a floating-point type.
  absl::Duration d = absl::Seconds(static_cast<double>(10));

  // Suggested - Remove the explicit cast
  absl::Duration d = absl::Seconds(10);

  ```


  (Clang-Tidy original name: abseil-duration-factory-float)

#### Tags
- /general/Abseil
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_ABS_DFS
### Default
#### OriginalId=abseil-duration-factory-scale
#### Enabled=false
#### Warning=true
#### DisplayName=Duration Factory Scale
#### HelpText
  Checks for cases where arguments to absl::Duration factory functions are scaled internally and could be changed to a different factory function. This check also looks for arguments with a zero value and suggests using absl::ZeroDuration() instead.

  Examples:

  ``` cpp
  // Original - Internal multiplication.
  int x;
  absl::Duration d = absl::Seconds(60 * x);

  // Suggested - Use absl::Minutes instead.
  absl::Duration d = absl::Minutes(x);


  // Original - Internal division.
  int y;
  absl::Duration d = absl::Milliseconds(y / 1000.);

  // Suggested - Use absl:::Seconds instead.
  absl::Duration d = absl::Seconds(y);


  // Original - Zero-value argument.
  absl::Duration d = absl::Hours(0);

  // Suggested = Use absl::ZeroDuration instead
  absl::Duration d = absl::ZeroDuration();

  ```


  (Clang-Tidy original name: abseil-duration-factory-scale)

#### Tags
- /general/Abseil
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_ABS_DS
### Default
#### OriginalId=abseil-duration-subtraction
#### Enabled=false
#### Warning=true
#### DisplayName=Duration Subtraction
#### HelpText
  Checks for cases where subtraction should be performed in the absl::Duration domain. When subtracting two values, and the first one is known to be a conversion from absl::Duration, we can infer that the second should also be interpreted as an absl::Duration, and make that inference explicit.

  Examples:

  ``` cpp
  // Original - Subtraction in the double domain
  double x;
  absl::Duration d;
  double result = absl::ToDoubleSeconds(d) - x;

  // Suggestion - Subtraction in the absl::Duration domain instead
  double result = absl::ToDoubleSeconds(d - absl::Seconds(x));

  // Original - Subtraction of two Durations in the double domain
  absl::Duration d1, d2;
  double result = absl::ToDoubleSeconds(d1) - absl::ToDoubleSeconds(d2);

  // Suggestion - Subtraction in the absl::Duration domain instead
  double result = absl::ToDoubleSeconds(d1 - d2);

  ```


  Note: As with other clang-tidy checks, it is possible that multiple fixes may overlap (as in the case of nested expressions), so not all occurrences can be transformed in one run. In particular, this may occur for nested subtraction expressions. Running clang-tidy multiple times will find and fix these overlaps.

  (Clang-Tidy original name: abseil-duration-subtraction)

#### Tags
- /general/Abseil
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_ABS_DUC
### Default
#### OriginalId=abseil-duration-unnecessary-conversion
#### Enabled=false
#### Warning=true
#### DisplayName=Duration Unnecessary Conversion
#### HelpText
  Finds and fixes cases where absl::Duration values are being converted to numeric types and back again.

  Floating-point examples:

  ``` cpp
  // Original - Conversion to double and back again
  absl::Duration d1;
  absl::Duration d2 = absl::Seconds(absl::ToDoubleSeconds(d1));

  // Suggestion - Remove unnecessary conversions
  absl::Duration d2 = d1;

  // Original - Division to convert to double and back again
  absl::Duration d2 = absl::Seconds(absl::FDivDuration(d1, absl::Seconds(1)));

  // Suggestion - Remove division and conversion
  absl::Duration d2 = d1;

  ```


  Integer examples:

  ``` cpp
  // Original - Conversion to integer and back again
  absl::Duration d1;
  absl::Duration d2 = absl::Hours(absl::ToInt64Hours(d1));

  // Suggestion - Remove unnecessary conversions
  absl::Duration d2 = d1;

  // Original - Integer division followed by conversion
  absl::Duration d2 = absl::Seconds(d1 / absl::Seconds(1));

  // Suggestion - Remove division and conversion
  absl::Duration d2 = d1;

  ```


  Unwrapping scalar operations:

  ``` cpp
  // Original - Multiplication by a scalar
  absl::Duration d1;
  absl::Duration d2 = absl::Seconds(absl::ToInt64Seconds(d1) * 2);

  // Suggestion - Remove unnecessary conversion
  absl::Duration d2 = d1 * 2;

  ```


  Note: Converting to an integer and back to an absl::Duration might be a truncating operation if the value is not aligned to the scale of conversion. In the rare case where this is the intended result, callers should use absl::Trunc to truncate explicitly.

  (Clang-Tidy original name: abseil-duration-unnecessary-conversion)

#### Tags
- /general/Abseil
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_ABS_FSD
### Default
#### OriginalId=abseil-faster-strsplit-delimiter
#### Enabled=false
#### Warning=true
#### DisplayName=Faster Strsplit Delimiter
#### HelpText
  Finds instances of absl::StrSplit() or absl::MaxSplits() where the delimiter is a single character string literal and replaces with a character. The check will offer a suggestion to change the string literal into a character. It will also catch code using absl::ByAnyChar() for just a single character and will transform that into a single character as well.

  These changes will give the same result, but using characters rather than single character string literals is more efficient and readable.

  Examples:

  ``` cpp
  // Original - the argument is a string literal.
  for (auto piece : absl::StrSplit(str, "B")) {

  // Suggested - the argument is a character, which causes the more efficient
  // overload of absl::StrSplit() to be used.
  for (auto piece : absl::StrSplit(str, 'B')) {


  // Original - the argument is a string literal inside absl::ByAnyChar call.
  for (auto piece : absl::StrSplit(str, absl::ByAnyChar("B"))) {

  // Suggested - the argument is a character, which causes the more efficient
  // overload of absl::StrSplit() to be used and we do not need absl::ByAnyChar
  // anymore.
  for (auto piece : absl::StrSplit(str, 'B')) {


  // Original - the argument is a string literal inside absl::MaxSplits call.
  for (auto piece : absl::StrSplit(str, absl::MaxSplits("B", 1))) {

  // Suggested - the argument is a character, which causes the more efficient
  // overload of absl::StrSplit() to be used.
  for (auto piece : absl::StrSplit(str, absl::MaxSplits('B', 1))) {

  ```


  (Clang-Tidy original name: abseil-faster-strsplit-delimiter)

#### Tags
- /general/Abseil
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_ABS_NID
### Default
#### OriginalId=abseil-no-internal-dependencies
#### Enabled=false
#### Warning=true
#### DisplayName=No Internal Dependencies
#### HelpText
  Warns if code using Abseil depends on internal details. If something is in a namespace that includes the word “internal”, code is not allowed to depend upon it beaucse it’s an implementation detail. They cannot friend it, include it, you mention it or refer to it in any way. Doing so violates Abseil’s compatibility guidelines and may result in breakage. See <https://abseil.io/about/compatibility> for more information.

  The following cases will result in warnings:

  ``` cpp
  absl::strings_internal::foo();
  // warning triggered on this line
  class foo {
    friend struct absl::container_internal::faa;
    // warning triggered on this line
  };
  absl::memory_internal::MakeUniqueResult();
  // warning triggered on this line

  ```


  (Clang-Tidy original name: abseil-no-internal-dependencies)

#### Tags
- /general/Abseil
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_ABS_NN
### Default
#### OriginalId=abseil-no-namespace
#### Enabled=false
#### Warning=true
#### DisplayName=No Namespace
#### HelpText
  Ensures code does not open namespace absl as that violates Abseil’s compatibility guidelines. Code should not open namespace absl as that conflicts with Abseil’s compatibility guidelines and may result in breakage.

  Any code that uses:

  ``` cpp
  namespace absl {
   ...
  }

  ```


  will be prompted with a warning.

  See [the full Abseil compatibility guidelines](https://abseil.io/about/compatibility) for more information.

  (Clang-Tidy original name: abseil-no-namespace)

#### Tags
- /general/Abseil
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_ABS_RSC
### Default
#### OriginalId=abseil-redundant-strcat-calls
#### Enabled=false
#### Warning=true
#### DisplayName=Redundant Strcat Calls
#### HelpText
  Suggests removal of unnecessary calls to absl::StrCat when the result is being passed to another call to absl::StrCat or absl::StrAppend.

  The extra calls cause unnecessary temporary strings to be constructed. Removing them makes the code smaller and faster.

  Examples:

  ``` cpp
  std::string s = absl::StrCat("A", absl::StrCat("B", absl::StrCat("C", "D")));
  //before

  std::string s = absl::StrCat("A", "B", "C", "D");
  //after

  absl::StrAppend(&s, absl::StrCat("E", "F", "G"));
  //before

  absl::StrAppend(&s, "E", "F", "G");
  //after

  ```


  (Clang-Tidy original name: abseil-redundant-strcat-calls)

#### Tags
- /general/Abseil
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_ABS_SCA
### Default
#### OriginalId=abseil-str-cat-append
#### Enabled=false
#### Warning=true
#### DisplayName=Str Cat Append
#### HelpText
  Flags uses of absl::StrCat() to append to a std::string. Suggests absl::StrAppend() should be used instead.

  The extra calls cause unnecessary temporary strings to be constructed. Removing them makes the code smaller and faster.

  ``` cpp
  a = absl::StrCat(a, b); // Use absl::StrAppend(&a, b) instead.

  ```


  Does not diagnose cases where absl::StrCat() is used as a template argument for a functor.

  (Clang-Tidy original name: abseil-str-cat-append)

#### Tags
- /general/Abseil
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_ABS_SFS
### Default
#### OriginalId=abseil-string-find-startswith
#### Enabled=false
#### Warning=true
#### DisplayName=String Find Startswith
#### HelpText
  Checks whether a std::string::find() result is compared with 0, and suggests replacing with absl::StartsWith(). This is both a readability and performance issue.

  ``` cpp
  string s = "...";
  if (s.find("Hello World") == 0) { /* do something */ }

  ```


  becomes

  ``` cpp
  string s = "...";
  if (absl::StartsWith(s, "Hello World")) { /* do something */ }

  ```


  ##### Options

  StringLikeClasses     

  Semicolon-separated list of names of string-like classes. By default only std::basic_string is considered. The list of methods to considered is fixed.

  IncludeStyle     

  A string specifying which include-style is used, llvm or google. Default is llvm.

  AbseilStringsMatchHeader     

  The location of Abseil’s strings/match.h. Defaults to absl/strings/match.h.

  (Clang-Tidy original name: abseil-string-find-startswith)

#### Tags
- /general/Abseil
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_ABS_SFSC
### Default
#### OriginalId=abseil-string-find-str-contains
#### Enabled=false
#### Warning=true
#### DisplayName=String Find Str Contains
#### HelpText
  Finds s.find(...) == string::npos comparisons (for various string-like types) and suggests replacing with absl::StrContains().

  This improves readability and reduces the likelihood of accidentally mixing find() and npos from different string-like types.

  By default, “string-like types” includes ::std::basic_string, ::std::basic_string_view, and ::absl::string_view. See the StringLikeClasses option to change this.

  ``` cpp
  std::string s = "...";
  if (s.find("Hello World") == std::string::npos) { /* do something */ }

  absl::string_view a = "...";
  if (absl::string_view::npos != a.find("Hello World")) { /* do something */ }

  ```


  becomes

  ``` cpp
  std::string s = "...";
  if (!absl::StrContains(s, "Hello World")) { /* do something */ }

  absl::string_view a = "...";
  if (absl::StrContains(a, "Hello World")) { /* do something */ }

  ```


  ##### Options

  StringLikeClasses     

  Semicolon-separated list of names of string-like classes. By default includes ::std::basic_string, ::std::basic_string_view, and ::absl::string_view.

  IncludeStyle     

  A string specifying which include-style is used, llvm or google. Default is llvm.

  AbseilStringsMatchHeader     

  The location of Abseil’s strings/match.h. Defaults to absl/strings/match.h.

  (Clang-Tidy original name: abseil-string-find-str-contains)

#### Tags
- /general/Abseil
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_ABS_TC
### Default
#### OriginalId=abseil-time-comparison
#### Enabled=false
#### Warning=true
#### DisplayName=Time Comparison
#### HelpText
  Prefer comparisons in the absl::Time domain instead of the integer domain.

  N.B.: In cases where an absl::Time is being converted to an integer, alignment may occur. If the comparison depends on this alignment, doing the comparison in the absl::Time domain may yield a different result. In practice this is very rare, and still indicates a bug which should be fixed.

  Examples:

  ``` cpp
  // Original - Comparison in the integer domain
  int x;
  absl::Time t;
  if (x < absl::ToUnixSeconds(t)) ...

  // Suggested - Compare in the absl::Time domain instead
  if (absl::FromUnixSeconds(x) < t) ...

  ```


  (Clang-Tidy original name: abseil-time-comparison)

#### Tags
- /general/Abseil
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_ABS_TS
### Default
#### OriginalId=abseil-time-subtraction
#### Enabled=false
#### Warning=true
#### DisplayName=Time Subtraction
#### HelpText
  Finds and fixes absl::Time subtraction expressions to do subtraction in the Time domain instead of the numeric domain.

  There are two cases of Time subtraction in which deduce additional type information:

    * When the result is an absl::Duration and the first argument is an absl::Time.
    * When the second argument is a absl::Time.



  In the first case, we must know the result of the operation, since without that the second operand could be either an absl::Time or an absl::Duration. In the second case, the first operand _must_ be an absl::Time, because subtracting an absl::Time from an absl::Duration is not defined.

  Examples:

  ``` cpp
  int x;
  absl::Time t;

  // Original - absl::Duration result and first operand is a absl::Time.
  absl::Duration d = absl::Seconds(absl::ToUnixSeconds(t) - x);

  // Suggestion - Perform subtraction in the Time domain instead.
  absl::Duration d = t - absl::FromUnixSeconds(x);


  // Original - Second operand is an absl::Time.
  int i = x - absl::ToUnixSeconds(t);

  // Suggestion - Perform subtraction in the Time domain instead.
  int i = absl::ToInt64Seconds(absl::FromUnixSeconds(x) - t);

  ```


  (Clang-Tidy original name: abseil-time-subtraction)

#### Tags
- /general/Abseil
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_ABS_UDC
### Default
#### OriginalId=abseil-upgrade-duration-conversions
#### Enabled=false
#### Warning=true
#### DisplayName=Upgrade Duration Conversions
#### HelpText
  Finds calls to absl::Duration arithmetic operators and factories whose argument needs an explicit cast to continue compiling after upcoming API changes.

  The operators *=, /=, *, and / for absl::Duration currently accept an argument of class type that is convertible to an arithmetic type. Such a call currently converts the value to an int64_t, even in a case such as std::atomic<float> that would result in lossy conversion.

  Additionally, the absl::Duration factory functions (absl::Hours, absl::Minutes, etc) currently accept an int64_t or a floating-point type. Similar to the arithmetic operators, calls with an argument of class type that is convertible to an arithmetic type go through the int64_t path.

  These operators and factories will be changed to only accept arithmetic types to prevent unintended behavior. After these changes are released, passing an argument of class type will no longer compile, even if the type is implicitly convertible to an arithmetic type.

  Here are example fixes created by this check:

  ``` cpp
  std::atomic<int> a;
  absl::Duration d = absl::Milliseconds(a);
  d *= a;

  ```


  becomes

  ``` cpp
  std::atomic<int> a;
  absl::Duration d = absl::Milliseconds(static_cast<int64_t>(a));
  d *= static_cast<int64_t>(a);

  ```


  Note that this check always adds a cast to int64_t in order to preserve the current behavior of user code. It is possible that this uncovers unintended behavior due to types implicitly convertible to a floating-point type.

  (Clang-Tidy original name: abseil-upgrade-duration-conversions)

#### Tags
- /general/Abseil
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_ALT_KNR
### Default
#### OriginalId=altera-kernel-name-restriction
#### Enabled=false
#### Warning=true
#### DisplayName=Kernel Name Restriction
#### HelpText
  Finds kernel files and include directives whose filename is kernel.cl, Verilog.cl, or VHDL.cl. The check is case insensitive.

  Such kernel file names cause the offline compiler to generate intermediate design files that have the same names as certain internal files, which leads to a compilation error.

  Based on the Guidelines for Naming the Kernel section in the [Intel FPGA SDK for OpenCL Pro Edition: Programming Guide](https://www.intel.com/content/www/us/en/programmable/documentation/mwh1391807965224.html\#ewa1412973930963).

  (Clang-Tidy original name: altera-kernel-name-restriction)

#### Tags
- /general/Altera
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_ALT_SPA
### Default
#### OriginalId=altera-struct-pack-align
#### Enabled=false
#### Warning=true
#### DisplayName=Struct Pack Align
#### HelpText
  Finds structs that are inefficiently packed or aligned, and recommends packing and/or aligning of said structs as needed.

  Structs that are not packed take up more space than they should, and accessing structs that are not well aligned is inefficient.

  Fix-its are provided to fix both of these issues by inserting and/or amending relevant struct attributes.

  Based on the [Altera SDK for OpenCL: Best Practices Guide](https://www.altera.com/en_US/pdfs/literature/hb/opencl-sdk/aocl_optimization_guide.pdf).

  ``` cpp
  // The following struct is originally aligned to 4 bytes, and thus takes up
  // 12 bytes of memory instead of 10. Packing the struct will make it use
  // only 10 bytes of memory, and aligning it to 16 bytes will make it
  // efficient to access.
  struct example {
    char a;    // 1 byte
    double b;  // 8 bytes
    char c;    // 1 byte
  };

  // The following struct is arranged in such a way that packing is not needed.
  // However, it is aligned to 4 bytes instead of 8, and thus needs to be
  // explicitly aligned.
  struct implicitly_packed_example {
    char a;  // 1 byte
    char b;  // 1 byte
    char c;  // 1 byte
    char d;  // 1 byte
    int e;   // 4 bytes
  };

  // The following struct is explicitly aligned and packed.
  struct good_example {
    char a;    // 1 byte
    double b;  // 8 bytes
    char c;    // 1 byte
  } __attribute__((packed)) __attribute__((aligned(16));

  // Explicitly aligning a struct to the wrong value will result in a warning.
  // The following example should be aligned to 16 bytes, not 32.
  struct badly_aligned_example {
    char a;    // 1 byte
    double b;  // 8 bytes
    char c;    // 1 byte
  } __attribute__((packed)) __attribute__((aligned(32)));

  ```


  (Clang-Tidy original name: altera-struct-pack-align)

#### Tags
- /general/Altera
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_ALT_SWIB
### Default
#### OriginalId=altera-single-work-item-barrier
#### Enabled=false
#### Warning=true
#### DisplayName=Single Work Item Barrier
#### HelpText
  Finds OpenCL kernel functions that call a barrier function but do not call an ID function (get_local_id, get_local_id, get_group_id, or get_local_linear_id).

  These kernels may be viable single work-item kernels, but will be forced to execute as NDRange kernels if using a newer version of the Altera Offline Compiler (>= v17.01).

  If using an older version of the Altera Offline Compiler, these kernel functions will be treated as single work-item kernels, which could be inefficient or lead to errors if NDRange semantics were intended.

  Based on the [Altera SDK for OpenCL: Best Practices Guide](https://www.altera.com/en_US/pdfs/literature/hb/opencl-sdk/aocl_optimization_guide.pdf).

  Examples:

  ``` cpp
  // error: function calls barrier but does not call an ID function.
  void __kernel barrier_no_id(__global int * foo, int size) {
    for (int i = 0; i < 100; i++) {
      foo[i] += 5;
    }
    barrier(CLK_GLOBAL_MEM_FENCE);
  }

  // ok: function calls barrier and an ID function.
  void __kernel barrier_with_id(__global int * foo, int size) {
    for (int i = 0; i < 100; i++) {
      int tid = get_global_id(0);
      foo[tid] += 5;
    }
    barrier(CLK_GLOBAL_MEM_FENCE);
  }

  // ok with AOC Version 17.01: the reqd_work_group_size turns this into
  // an NDRange.
  __attribute__((reqd_work_group_size(2,2,2)))
  void __kernel barrier_with_id(__global int * foo, int size) {
    for (int i = 0; i < 100; i++) {
      foo[tid] += 5;
    }
    barrier(CLK_GLOBAL_MEM_FENCE);
  }

  ```


  ##### Options

  AOCVersion     

  Defines the version of the Altera Offline Compiler. Defaults to 1600 (corresponding to version 16.00).

  (Clang-Tidy original name: altera-single-work-item-barrier)

#### Tags
- /general/Altera
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_AND_CA
### Default
#### OriginalId=android-cloexec-accept4
#### Enabled=false
#### Warning=true
#### DisplayName=Cloexec Accept4
#### HelpText
  accept4() should include SOCK_CLOEXEC in its type argument to avoid the file descriptor leakage. Without this flag, an opened sensitive file would remain open across a fork+exec to a lower-privileged SELinux domain.

  Examples:

  ``` cpp
  accept4(sockfd, addr, addrlen, SOCK_NONBLOCK);

  // becomes

  accept4(sockfd, addr, addrlen, SOCK_NONBLOCK | SOCK_CLOEXEC);

  ```


  (Clang-Tidy original name: android-cloexec-accept4)

#### Tags
- /general/Android
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_AND_CA2
### Default
#### OriginalId=android-cloexec-accept
#### Enabled=false
#### Warning=true
#### DisplayName=Cloexec Accept
#### HelpText
  The usage of accept() is not recommended, it’s better to use accept4(). Without this flag, an opened sensitive file descriptor would remain open across a fork+exec to a lower-privileged SELinux domain.

  Examples:

  ``` cpp
  accept(sockfd, addr, addrlen);

  // becomes

  accept4(sockfd, addr, addrlen, SOCK_CLOEXEC);

  ```


  (Clang-Tidy original name: android-cloexec-accept)

#### Tags
- /general/Android
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_AND_CC
### Default
#### OriginalId=android-cloexec-creat
#### Enabled=false
#### Warning=true
#### DisplayName=Cloexec Creat
#### HelpText
  The usage of creat() is not recommended, it’s better to use open().

  Examples:

  ``` cpp
  int fd = creat(path, mode);

  // becomes

  int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, mode);

  ```


  (Clang-Tidy original name: android-cloexec-creat)

#### Tags
- /general/Android
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_AND_CD
### Default
#### OriginalId=android-cloexec-dup
#### Enabled=false
#### Warning=true
#### DisplayName=Cloexec Dup
#### HelpText
  The usage of dup() is not recommended, it’s better to use fcntl(), which can set the close-on-exec flag. Otherwise, an opened sensitive file would remain open across a fork+exec to a lower-privileged SELinux domain.

  Examples:

  ``` cpp
  int fd = dup(oldfd);

  // becomes

  int fd = fcntl(oldfd, F_DUPFD_CLOEXEC);

  ```


  (Clang-Tidy original name: android-cloexec-dup)

#### Tags
- /general/Android
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_AND_CEC
### Default
#### OriginalId=android-cloexec-epoll-create1
#### Enabled=false
#### Warning=true
#### DisplayName=Cloexec Epoll Create1
#### HelpText
  epoll_create1() should include EPOLL_CLOEXEC in its type argument to avoid the file descriptor leakage. Without this flag, an opened sensitive file would remain open across a fork+exec to a lower-privileged SELinux domain.

  Examples:

  ``` cpp
  epoll_create1(0);

  // becomes

  epoll_create1(EPOLL_CLOEXEC);

  ```


  (Clang-Tidy original name: android-cloexec-epoll-create1)

#### Tags
- /general/Android
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_AND_CEC2
### Default
#### OriginalId=android-cloexec-epoll-create
#### Enabled=false
#### Warning=true
#### DisplayName=Cloexec Epoll Create
#### HelpText
  The usage of epoll_create() is not recommended, it’s better to use epoll_create1(), which allows close-on-exec.

  Examples:

  ``` cpp
  epoll_create(size);

  // becomes

  epoll_create1(EPOLL_CLOEXEC);

  ```


  (Clang-Tidy original name: android-cloexec-epoll-create)

#### Tags
- /general/Android
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_AND_CF
### Default
#### OriginalId=android-cloexec-fopen
#### Enabled=false
#### Warning=true
#### DisplayName=Cloexec Fopen
#### HelpText
  fopen() should include e in their mode string; so re would be valid. This is equivalent to having set FD_CLOEXEC on that descriptor.

  Examples:

  ``` cpp
  fopen("fn", "r");

  // becomes

  fopen("fn", "re");

  ```


  (Clang-Tidy original name: android-cloexec-fopen)

#### Tags
- /general/Android
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_AND_CII
### Default
#### OriginalId=android-cloexec-inotify-init1
#### Enabled=false
#### Warning=true
#### DisplayName=Cloexec Inotify Init1
#### HelpText
  inotify_init1() should include IN_CLOEXEC in its type argument to avoid the file descriptor leakage. Without this flag, an opened sensitive file would remain open across a fork+exec to a lower-privileged SELinux domain.

  Examples:

  ``` cpp
  inotify_init1(IN_NONBLOCK);

  // becomes

  inotify_init1(IN_NONBLOCK | IN_CLOEXEC);

  ```


  (Clang-Tidy original name: android-cloexec-inotify-init1)

#### Tags
- /general/Android
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_AND_CII2
### Default
#### OriginalId=android-cloexec-inotify-init
#### Enabled=false
#### Warning=true
#### DisplayName=Cloexec Inotify Init
#### HelpText
  The usage of inotify_init() is not recommended, it’s better to use inotify_init1().

  Examples:

  ``` cpp
  inotify_init();

  // becomes

  inotify_init1(IN_CLOEXEC);

  ```


  (Clang-Tidy original name: android-cloexec-inotify-init)

#### Tags
- /general/Android
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_AND_CITFR
### Default
#### OriginalId=android-comparison-in-temp-failure-retry
#### Enabled=false
#### Warning=true
#### DisplayName=Comparison In Temp Failure Retry
#### HelpText
  Diagnoses comparisons that appear to be incorrectly placed in the argument to the TEMP_FAILURE_RETRY macro. Having such a use is incorrect in the vast majority of cases, and will often silently defeat the purpose of the TEMP_FAILURE_RETRY macro.

  For context, TEMP_FAILURE_RETRY is [a convenience macro](https://www.gnu.org/software/libc/manual/html_node/Interrupted-Primitives.html) provided by both glibc and Bionic. Its purpose is to repeatedly run a syscall until it either succeeds, or fails for reasons other than being interrupted.

  Example buggy usage looks like:

  ``` cpp
  char cs[1];
  while (TEMP_FAILURE_RETRY(read(STDIN_FILENO, cs, sizeof(cs)) != 0)) {
    // Do something with cs.
  }

  ```


  Because TEMP_FAILURE_RETRY will check for whether the result _of the comparison_ is -1, and retry if so.

  If you encounter this, the fix is simple: lift the comparison out of the TEMP_FAILURE_RETRY argument, like so:

  ``` cpp
  char cs[1];
  while (TEMP_FAILURE_RETRY(read(STDIN_FILENO, cs, sizeof(cs))) != 0) {
    // Do something with cs.
  }

  ```


  ##### Options

  RetryMacros     

  A comma-separated list of the names of retry macros to be checked.

  (Clang-Tidy original name: android-comparison-in-temp-failure-retry)

#### Tags
- /general/Android
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_AND_CMC
### Default
#### OriginalId=android-cloexec-memfd-create
#### Enabled=false
#### Warning=true
#### DisplayName=Cloexec Memfd Create
#### HelpText
  memfd_create() should include MFD_CLOEXEC in its type argument to avoid the file descriptor leakage. Without this flag, an opened sensitive file would remain open across a fork+exec to a lower-privileged SELinux domain.

  Examples:

  ``` cpp
  memfd_create(name, MFD_ALLOW_SEALING);

  // becomes

  memfd_create(name, MFD_ALLOW_SEALING | MFD_CLOEXEC);

  ```


  (Clang-Tidy original name: android-cloexec-memfd-create)

#### Tags
- /general/Android
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_AND_CO
### Default
#### OriginalId=android-cloexec-open
#### Enabled=false
#### Warning=true
#### DisplayName=Cloexec Open
#### HelpText
  A common source of security bugs is code that opens a file without using the O_CLOEXEC flag. Without that flag, an opened sensitive file would remain open across a fork+exec to a lower-privileged SELinux domain, leaking that sensitive data. Open-like functions including open(), openat(), and open64() should include O_CLOEXEC in their flags argument.

  Examples:

  ``` cpp
  open("filename", O_RDWR);
  open64("filename", O_RDWR);
  openat(0, "filename", O_RDWR);

  // becomes

  open("filename", O_RDWR | O_CLOEXEC);
  open64("filename", O_RDWR | O_CLOEXEC);
  openat(0, "filename", O_RDWR | O_CLOEXEC);

  ```


  (Clang-Tidy original name: android-cloexec-open)

#### Tags
- /general/Android
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_AND_CP
### Default
#### OriginalId=android-cloexec-pipe2
#### Enabled=false
#### Warning=true
#### DisplayName=Cloexec Pipe2
#### HelpText
  This checks ensures that pipe2() is called with the O_CLOEXEC flag. The check also adds the O_CLOEXEC flag that marks the file descriptor to be closed in child processes. Without this flag a sensitive file descriptor can be leaked to a child process, potentially into a lower-privileged SELinux domain.

  Examples:

  ``` cpp
  pipe2(pipefd, O_NONBLOCK);

  ```


  Suggested replacement:

  ``` cpp
  pipe2(pipefd, O_NONBLOCK | O_CLOEXEC);

  ```


  (Clang-Tidy original name: android-cloexec-pipe2)

#### Tags
- /general/Android
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_AND_CP2
### Default
#### OriginalId=android-cloexec-pipe
#### Enabled=false
#### Warning=true
#### DisplayName=Cloexec Pipe
#### HelpText
  This check detects usage of pipe(). Using pipe() is not recommended, pipe2() is the suggested replacement. The check also adds the O_CLOEXEC flag that marks the file descriptor to be closed in child processes. Without this flag a sensitive file descriptor can be leaked to a child process, potentially into a lower-privileged SELinux domain.

  Examples:

  ``` cpp
  pipe(pipefd);

  ```


  Suggested replacement:

  ``` cpp
  pipe2(pipefd, O_CLOEXEC);

  ```


  (Clang-Tidy original name: android-cloexec-pipe)

#### Tags
- /general/Android
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_AND_CS
### Default
#### OriginalId=android-cloexec-socket
#### Enabled=false
#### Warning=true
#### DisplayName=Cloexec Socket
#### HelpText
  socket() should include SOCK_CLOEXEC in its type argument to avoid the file descriptor leakage. Without this flag, an opened sensitive file would remain open across a fork+exec to a lower-privileged SELinux domain.

  Examples:

  ``` cpp
  socket(domain, type, SOCK_STREAM);

  // becomes

  socket(domain, type, SOCK_STREAM | SOCK_CLOEXEC);

  ```


  (Clang-Tidy original name: android-cloexec-socket)

#### Tags
- /general/Android
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BST_UTS
### Default
#### OriginalId=boost-use-to-string
#### Enabled=true
#### Warning=true
#### DisplayName=Use To String
#### HelpText
  This check finds conversion from integer type like int to std::string or std::wstring using boost::lexical_cast, and replace it with calls to std::to_string and std::to_wstring.

  It doesn’t replace conversion from floating points despite the to_string overloads, because it would change the behaviour.

  ``` cpp
  auto str = boost::lexical_cast<std::string>(42);
  auto wstr = boost::lexical_cast<std::wstring>(2137LL);

  // Will be changed to
  auto str = std::to_string(42);
  auto wstr = std::to_wstring(2137LL);

  ```


  (Clang-Tidy original name: boost-use-to-string)

#### Tags
- /general/Boost
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_AC
### Default
#### OriginalId=bugprone-argument-comment
#### Enabled=true
#### Warning=true
#### DisplayName=Argument Comment
#### HelpText
  Checks that argument comments match parameter names.

  The check understands argument comments in the form /*parameter_name=*/ that are placed right before the argument.

  ``` cpp
  void f(bool foo);

  ...

  f(/*bar=*/true);
  // warning: argument name 'bar' in comment does not match parameter name 'foo'

  ```


  The check tries to detect typos and suggest automated fixes for them.

  ##### Options

  StrictMode     

  When false (default value), the check will ignore leading and trailing underscores and case when comparing names – otherwise they are taken into account.

  IgnoreSingleArgument     

  When true, the check will ignore the single argument.

  CommentBoolLiterals     

  When true, the check will add argument comments in the format /*ParameterName=*/ right before the boolean literal argument.

  Before:

  ``` cpp
  void foo(bool TurnKey, bool PressButton);

  foo(true, false);

  ```


  After:

  ``` cpp
  void foo(bool TurnKey, bool PressButton);

  foo(/*TurnKey=*/true, /*PressButton=*/false);

  ```


  CommentIntegerLiterals     

  When true, the check will add argument comments in the format /*ParameterName=*/ right before the integer literal argument.

  Before:

  ``` cpp
  void foo(int MeaningOfLife);

  foo(42);

  ```


  After:

  ``` cpp
  void foo(int MeaningOfLife);

  foo(/*MeaningOfLife=*/42);

  ```


  CommentFloatLiterals     

  When true, the check will add argument comments in the format /*ParameterName=*/ right before the float/double literal argument.

  Before:

  ``` cpp
  void foo(float Pi);

  foo(3.14159);

  ```


  After:

  ``` cpp
  void foo(float Pi);

  foo(/*Pi=*/3.14159);

  ```


  CommentStringLiterals     

  When true, the check will add argument comments in the format /*ParameterName=*/ right before the string literal argument.

  Before:

  ``` cpp
  void foo(const char *String);
  void foo(const wchar_t *WideString);

  foo("Hello World");
  foo(L"Hello World");

  ```


  After:

  ``` cpp
  void foo(const char *String);
  void foo(const wchar_t *WideString);

  foo(/*String=*/"Hello World");
  foo(/*WideString=*/L"Hello World");

  ```


  CommentCharacterLiterals     

  When true, the check will add argument comments in the format /*ParameterName=*/ right before the character literal argument.

  Before:

  ``` cpp
  void foo(char *Character);

  foo('A');

  ```


  After:

  ``` cpp
  void foo(char *Character);

  foo(/*Character=*/'A');

  ```


  CommentUserDefinedLiterals     

  When true, the check will add argument comments in the format /*ParameterName=*/ right before the user defined literal argument.

  Before:

  ``` cpp
  void foo(double Distance);

  double operator"" _km(long double);

  foo(402.0_km);

  ```


  After:

  ``` cpp
  void foo(double Distance);

  double operator"" _km(long double);

  foo(/*Distance=*/402.0_km);

  ```


  CommentNullPtrs     

  When true, the check will add argument comments in the format /*ParameterName=*/ right before the nullptr literal argument.

  Before:

  ``` cpp
  void foo(A* Value);

  foo(nullptr);

  ```


  After:

  ``` cpp
  void foo(A* Value);

  foo(/*Value=*/nullptr);

  ```


  (Clang-Tidy original name: bugprone-argument-comment)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_ASE
### Default
#### OriginalId=bugprone-assert-side-effect
#### Enabled=true
#### Warning=true
#### DisplayName=Assert Side Effect
#### HelpText
  Finds assert() with side effect.

  The condition of assert() is evaluated only in debug builds so a condition with side effect can cause different behavior in debug / release builds.

  ##### Options

  AssertMacros     

  A comma-separated list of the names of assert macros to be checked.

  CheckFunctionCalls     

  Whether to treat non-const member and non-member functions as they produce side effects. Disabled by default because it can increase the number of false positive warnings.

  (Clang-Tidy original name: bugprone-assert-side-effect)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_BC
### Default
#### OriginalId=bugprone-branch-clone
#### Enabled=true
#### Warning=true
#### DisplayName=Branch Clone
#### HelpText
  Checks for repeated branches in if/else if/else chains, consecutive repeated branches in switch statements and identical true and false branches in conditional operators.

  ``` cpp
  if (test_value(x)) {
    y++;
    do_something(x, y);
  } else {
    y++;
    do_something(x, y);
  }

  ```


  In this simple example (which could arise e.g. as a copy-paste error) the then and else branches are identical and the code is equivalent the following shorter and cleaner code:

  ``` cpp
  test_value(x); // can be omitted unless it has side effects
  y++;
  do_something(x, y);

  ```


  If this is the intended behavior, then there is no reason to use a conditional statement; otherwise the issue can be solved by fixing the branch that is handled incorrectly.

  The check also detects repeated branches in longer if/else if/else chains where it would be even harder to notice the problem.

  In switch statements the check only reports repeated branches when they are consecutive, because it is relatively common that the case: labels have some natural ordering and rearranging them would decrease the readability of the code. For example:

  ``` cpp
  switch (ch) {
  case 'a':
    return 10;
  case 'A':
    return 10;
  case 'b':
    return 11;
  case 'B':
    return 11;
  default:
    return 10;
  }

  ```


  Here the check reports that the 'a' and 'A' branches are identical (and that the 'b' and 'B' branches are also identical), but does not report that the default: branch is also identical to the first two branches. If this is indeed the correct behavior, then it could be implemented as:

  ``` cpp
  switch (ch) {
  case 'a':
  case 'A':
    return 10;
  case 'b':
  case 'B':
    return 11;
  default:
    return 10;
  }

  ```


  Here the check does not warn for the repeated return 10;, which is good if we want to preserve that 'a' is before 'b' and default: is the last branch.

  Finally, the check also examines conditional operators and reports code like:

  ``` cpp
  return test_value(x) ? x : x;

  ```


  Unlike if statements, the check does not detect chains of conditional operators.

  Note: This check also reports situations where branches become identical only after preprocession.

  (Clang-Tidy original name: bugprone-branch-clone)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_BPIC
### Default
#### OriginalId=bugprone-bool-pointer-implicit-conversion
#### Enabled=true
#### Warning=true
#### DisplayName=Bool Pointer Implicit Conversion
#### HelpText
  Checks for conditions based on implicit conversion from a bool pointer to bool.

  Example:

  ``` cpp
  bool *p;
  if (p) {
    // Never used in a pointer-specific way.
  }

  ```


  (Clang-Tidy original name: bugprone-bool-pointer-implicit-conversion)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_BSTKT
### Default
#### OriginalId=bugprone-bad-signal-to-kill-thread
#### Enabled=true
#### Warning=true
#### DisplayName=Bad Signal To Kill Thread
#### HelpText
  Finds pthread_kill function calls when a thread is terminated by raising SIGTERM signal and the signal kills the entire process, not just the individual thread. Use any signal except SIGTERM.

  This check corresponds to the CERT C Coding Standard rule [POS44-C. Do not use signals to terminate threads](https://wiki.sei.cmu.edu/confluence/display/c/POS44-C.+Do+not+use+signals+to+terminate+threads).

  (Clang-Tidy original name: bugprone-bad-signal-to-kill-thread)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_CCI
### Default
#### OriginalId=bugprone-copy-constructor-init
#### Enabled=true
#### Warning=true
#### DisplayName=Copy Constructor Init
#### HelpText
  Finds copy constructors where the constructor doesn’t call the copy constructor of the base class.

  ``` cpp
  class Copyable {
  public:
    Copyable() = default;
    Copyable(const Copyable &) = default;
  };
  class X2 : public Copyable {
    X2(const X2 &other) {} // Copyable(other) is missing
  };

  ```


  Also finds copy constructors where the constructor of the base class don’t have parameter.

  ``` cpp
  class X4 : public Copyable {
    X4(const X4 &other) : Copyable() {} // other is missing
  };

  ```


  The check also suggests a fix-its in some cases.

  (Clang-Tidy original name: bugprone-copy-constructor-init)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_DH
### Default
#### OriginalId=bugprone-dangling-handle
#### Enabled=true
#### Warning=true
#### DisplayName=Dangling Handle
#### HelpText
  Detect dangling references in value handles like std::experimental::string_view. These dangling references can be a result of constructing handles from temporary values, where the temporary is destroyed soon after the handle is created.

  Examples:

  ``` cpp
  string_view View = string();  // View will dangle.
  string A;
  View = A + "A";  // still dangle.

  vector<string_view> V;
  V.push_back(string());  // V[0] is dangling.
  V.resize(3, string());  // V[1] and V[2] will also dangle.

  string_view f() {
    // All these return values will dangle.
    return string();
    string S;
    return S;
    char Array[10]{};
    return Array;
  }

  ```


  ##### Options

  HandleClasses     

  A semicolon-separated list of class names that should be treated as handles. By default only std::experimental::basic_string_view is considered.

  (Clang-Tidy original name: bugprone-dangling-handle)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_DSI
### Default
#### OriginalId=bugprone-dynamic-static-initializers
#### Enabled=true
#### Warning=true
#### DisplayName=Dynamic Static Initializers
#### HelpText
  Finds instances of static variables that are dynamically initialized in header files.

  This can pose problems in certain multithreaded contexts. For example, when disabling compiler generated synchronization instructions for static variables initialized at runtime (e.g. by -fno-threadsafe-statics), even if a particular project takes the necessary precautions to prevent race conditions during initialization by providing their own synchronization, header files included from other projects may not. Therefore, such a check is helpful for ensuring that disabling compiler generated synchronization for static variable initialization will not cause problems.

  Consider the following code:

  ``` cpp
  int foo() {
    static int k = bar();
    return k;
  }

  ```


  When synchronization of static initialization is disabled, if two threads both call foo for the first time, there is the possibility that k will be double initialized, creating a race condition.

  (Clang-Tidy original name: bugprone-dynamic-static-initializers)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_EE
### Default
#### OriginalId=bugprone-exception-escape
#### Enabled=true
#### Warning=true
#### DisplayName=Exception Escape
#### HelpText
  Finds functions which may throw an exception directly or indirectly, but they should not. The functions which should not throw exceptions are the following:

    * Destructors
    * Move constructors
    * Move assignment operators
    * The main() functions
    * swap() functions
    * Functions marked with throw() or noexcept
    * Other functions given as option



  A destructor throwing an exception may result in undefined behavior, resource leaks or unexpected termination of the program. Throwing move constructor or move assignment also may result in undefined behavior or resource leak. The swap() operations expected to be non throwing most of the cases and they are always possible to implement in a non throwing way. Non throwing swap() operations are also used to create move operations. A throwing main() function also results in unexpected termination.

  WARNING! This check may be expensive on large source files.

  ##### Options

  FunctionsThatShouldNotThrow     

  Comma separated list containing function names which should not throw. An example value for this parameter can be WinMain which adds function WinMain() in the Windows API to the list of the functions which should not throw. Default value is an empty string.

  IgnoredExceptions     

  Comma separated list containing type names which are not counted as thrown exceptions in the check. Default value is an empty string.

  (Clang-Tidy original name: bugprone-exception-escape)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_FDN
### Default
#### OriginalId=bugprone-forward-declaration-namespace
#### Enabled=true
#### Warning=true
#### DisplayName=Forward Declaration Namespace
#### HelpText
  Checks if an unused forward declaration is in a wrong namespace.

  The check inspects all unused forward declarations and checks if there is any declaration/definition with the same name existing, which could indicate that the forward declaration is in a potentially wrong namespace.

  ``` cpp
  namespace na { struct A; }
  namespace nb { struct A {}; }
  nb::A a;
  // warning : no definition found for 'A', but a definition with the same name
  // 'A' found in another namespace 'nb::'

  ```


  This check can only generate warnings, but it can’t suggest a fix at this point.

  (Clang-Tidy original name: bugprone-forward-declaration-namespace)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_FIT
### Default
#### OriginalId=bugprone-fold-init-type
#### Enabled=true
#### Warning=true
#### DisplayName=Fold Init Type
#### HelpText
  The check flags type mismatches in [folds](https://en.wikipedia.org/wiki/Fold_\(higher-order_function\)) like std::accumulate that might result in loss of precision. std::accumulate folds an input range into an initial value using the type of the latter, with operator+ by default. This can cause loss of precision through:

    * Truncation: The following code uses a floating point range and an int initial value, so trucation will happen at every application of operator+ and the result will be 0, which might not be what the user expected.



  ``` cpp
  auto a = {0.5f, 0.5f, 0.5f, 0.5f};
  return std::accumulate(std::begin(a), std::end(a), 0);

  ```


    * Overflow: The following code also returns 0.



  ``` cpp
  auto a = {65536LL * 65536 * 65536};
  return std::accumulate(std::begin(a), std::end(a), 0);

  ```


  (Clang-Tidy original name: bugprone-fold-init-type)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_FRO
### Default
#### OriginalId=bugprone-forwarding-reference-overload
#### Enabled=true
#### Warning=true
#### DisplayName=Forwarding Reference Overload
#### HelpText
  The check looks for perfect forwarding constructors that can hide copy or move constructors. If a non const lvalue reference is passed to the constructor, the forwarding reference parameter will be a better match than the const reference parameter of the copy constructor, so the perfect forwarding constructor will be called, which can be confusing. For detailed description of this issue see: Scott Meyers, Effective Modern C++, Item 26.

  Consider the following example:

  ``` cpp
  class Person {
  public:
    // C1: perfect forwarding ctor
    template<typename T>
    explicit Person(T&& n) {}

    // C2: perfect forwarding ctor with parameter default value
    template<typename T>
    explicit Person(T&& n, int x = 1) {}

    // C3: perfect forwarding ctor guarded with enable_if
    template<typename T, typename X = enable_if_t<is_special<T>,void>>
    explicit Person(T&& n) {}

    // (possibly compiler generated) copy ctor
    Person(const Person& rhs);
  };

  ```


  The check warns for constructors C1 and C2, because those can hide copy and move constructors. We suppress warnings if the copy and the move constructors are both disabled (deleted or private), because there is nothing the perfect forwarding constructor could hide in this case. We also suppress warnings for constructors like C3 that are guarded with an enable_if, assuming the programmer was aware of the possible hiding.

  ##### Background

  For deciding whether a constructor is guarded with enable_if, we consider the default values of the type parameters and the types of the constructor parameters. If any part of these types is std::enable_if or std::enable_if_t, we assume the constructor is guarded.

  (Clang-Tidy original name: bugprone-forwarding-reference-overload)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_ID
### Default
#### OriginalId=bugprone-integer-division
#### Enabled=true
#### Warning=true
#### DisplayName=Integer Division
#### HelpText
  Finds cases where integer division in a floating point context is likely to cause unintended loss of precision.

  No reports are made if divisions are part of the following expressions:

    * operands of operators expecting integral or bool types,
    * call expressions of integral or bool types, and
    * explicit cast expressions to integral or bool types,



  as these are interpreted as signs of deliberateness from the programmer.

  Examples:

  ``` cpp
  float floatFunc(float);
  int intFunc(int);
  double d;
  int i = 42;

  // Warn, floating-point values expected.
  d = 32 * 8 / (2 + i);
  d = 8 * floatFunc(1 + 7 / 2);
  d = i / (1 << 4);

  // OK, no integer division.
  d = 32 * 8.0 / (2 + i);
  d = 8 * floatFunc(1 + 7.0 / 2);
  d = (double)i / (1 << 4);

  // OK, there are signs of deliberateness.
  d = 1 << (i / 2);
  d = 9 + intFunc(6 * i / 32);
  d = (int)(i / 32) - 8;

  ```


  (Clang-Tidy original name: bugprone-integer-division)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_IE
### Default
#### OriginalId=bugprone-inaccurate-erase
#### Enabled=true
#### Warning=true
#### DisplayName=Inaccurate Erase
#### HelpText
  Checks for inaccurate use of the erase() method.

  Algorithms like remove() do not actually remove any element from the container but return an iterator to the first redundant element at the end of the container. These redundant elements must be removed using the erase() method. This check warns when not all of the elements will be removed due to using an inappropriate overload.

  For example, the following code erases only one element:

  ``` cpp
  std::vector<int> xs;
  ...
  xs.erase(std::remove(xs.begin(), xs.end(), 10));

  ```


  Call the two-argument overload of erase() to remove the subrange:

  ``` cpp
  std::vector<int> xs;
  ...
  xs.erase(std::remove(xs.begin(), xs.end(), 10), xs.end());

  ```


  (Clang-Tidy original name: bugprone-inaccurate-erase)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_IL
### Default
#### OriginalId=bugprone-infinite-loop
#### Enabled=true
#### Warning=true
#### DisplayName=Infinite Loop
#### HelpText
  Finds obvious infinite loops (loops where the condition variable is not changed at all).

  Finding infinite loops is well-known to be impossible (halting problem). However, it is possible to detect some obvious infinite loops, for example, if the loop condition is not changed. This check detects such loops. A loop is considered infinite if it does not have any loop exit statement (break, continue, goto, return, throw or a call to a function called as [[noreturn]]) and all of the following conditions hold for every variable in the condition:

    * It is a local variable.
    * It has no reference or pointer aliases.
    * It is not a structure or class member.



  Furthermore, the condition must not contain a function call to consider the loop infinite since functions may return different values for different calls.

  For example, the following loop is considered infinite i is not changed in the body:

  ``` cpp
  int i = 0, j = 0;
  while (i < 10) {
    ++j;
  }

  ```


  (Clang-Tidy original name: bugprone-infinite-loop)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_IR
### Default
#### OriginalId=bugprone-incorrect-roundings
#### Enabled=true
#### Warning=true
#### DisplayName=Incorrect Roundings
#### HelpText
  Checks the usage of patterns known to produce incorrect rounding. Programmers often use:

  ``` cpp
  (int)(double_expression + 0.5)

  ```


  to round the double expression to an integer. The problem with this:

    1. It is unnecessarily slow.
    2. It is incorrect. The number 0.499999975 (smallest representable float number below 0.5) rounds to 1.0. Even worse behavior for negative numbers where both -0.5f and -1.4f both round to 0.0.



  (Clang-Tidy original name: bugprone-incorrect-roundings)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_LFN
### Default
#### OriginalId=bugprone-lambda-function-name
#### Enabled=true
#### Warning=true
#### DisplayName=Lambda Function Name
#### HelpText
  Checks for attempts to get the name of a function from within a lambda expression. The name of a lambda is always something like operator(), which is almost never what was intended.

  Example:

  ``` cpp
  void FancyFunction() {
    [] { printf("Called from %s\n", __func__); }();
    [] { printf("Now called from %s\n", __FUNCTION__); }();
  }

  ```


  Output:

  ``` cpp
  Called from operator()
  Now called from operator()

  ```


  Likely intended output:

  ``` cpp
  Called from FancyFunction
  Now called from FancyFunction

  ```


  (Clang-Tidy original name: bugprone-lambda-function-name)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_MFR
### Default
#### OriginalId=bugprone-move-forwarding-reference
#### Enabled=true
#### Warning=true
#### DisplayName=Move Forwarding Reference
#### HelpText
  Warns if std::move is called on a forwarding reference, for example:

  ``` cpp
  template <typename T>
  void foo(T&& t) {
    bar(std::move(t));
  }

  ```


  [Forwarding references](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4164.pdf) should typically be passed to std::forward instead of std::move, and this is the fix that will be suggested.

  (A forwarding reference is an rvalue reference of a type that is a deduced function template argument.)

  In this example, the suggested fix would be

  ``` cpp
  bar(std::forward<T>(t));

  ```


  ##### Background

  Code like the example above is sometimes written with the expectation that T&& will always end up being an rvalue reference, no matter what type is deduced for T, and that it is therefore not possible to pass an lvalue to foo(). However, this is not true. Consider this example:

  ``` cpp
  std::string s = "Hello, world";
  foo(s);

  ```


  This code compiles and, after the call to foo(), s is left in an indeterminate state because it has been moved from. This may be surprising to the caller of foo() because no std::move was used when calling foo().

  The reason for this behavior lies in the special rule for template argument deduction on function templates like foo() – i.e. on function templates that take an rvalue reference argument of a type that is a deduced function template argument. (See section [temp.deduct.call]/3 in the C++11 standard.)

  If foo() is called on an lvalue (as in the example above), then T is deduced to be an lvalue reference. In the example, T is deduced to be std::string &. The type of the argument t therefore becomes std::string& &&; by the reference collapsing rules, this collapses to std::string&.

  This means that the foo(s) call passes s as an lvalue reference, and foo() ends up moving s and thereby placing it into an indeterminate state.

  (Clang-Tidy original name: bugprone-move-forwarding-reference)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_MOISIA
### Default
#### OriginalId=bugprone-misplaced-operator-in-strlen-in-alloc
#### Enabled=true
#### Warning=true
#### DisplayName=Misplaced Operator In Strlen In Alloc
#### HelpText
  Finds cases where 1 is added to the string in the argument to strlen(), strnlen(), strnlen_s(), wcslen(), wcsnlen(), and wcsnlen_s() instead of the result and the value is used as an argument to a memory allocation function (malloc(), calloc(), realloc(), alloca()) or the new[] operator in C++. The check detects error cases even if one of these functions (except the new[] operator) is called by a constant function pointer. Cases where 1 is added both to the parameter and the result of the strlen()-like function are ignored, as are cases where the whole addition is surrounded by extra parentheses.

  C example code:

  ``` cpp
  void bad_malloc(char *str) {
    char *c = (char*) malloc(strlen(str + 1));
  }

  ```


  The suggested fix is to add 1 to the return value of strlen() and not to its argument. In the example above the fix would be

  ``` cpp
  char *c = (char*) malloc(strlen(str) + 1);

  ```


  C++ example code:

  ``` cpp
  void bad_new(char *str) {
    char *c = new char[strlen(str + 1)];
  }

  ```


  As in the C code with the malloc() function, the suggested fix is to add 1 to the return value of strlen() and not to its argument. In the example above the fix would be

  ``` cpp
  char *c = new char[strlen(str) + 1];

  ```


  Example for silencing the diagnostic:

  ``` cpp
  void bad_malloc(char *str) {
    char *c = (char*) malloc(strlen((str + 1)));
  }

  ```


  (Clang-Tidy original name: bugprone-misplaced-operator-in-strlen-in-alloc)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_MP
### Default
#### OriginalId=bugprone-macro-parentheses
#### Enabled=true
#### Warning=true
#### DisplayName=Macro Parentheses
#### HelpText
  Finds macros that can have unexpected behaviour due to missing parentheses.

  Macros are expanded by the preprocessor as-is. As a result, there can be unexpected behaviour; operators may be evaluated in unexpected order and unary operators may become binary operators, etc.

  When the replacement list has an expression, it is recommended to surround it with parentheses. This ensures that the macro result is evaluated completely before it is used.

  It is also recommended to surround macro arguments in the replacement list with parentheses. This ensures that the argument value is calculated properly.

  (Clang-Tidy original name: bugprone-macro-parentheses)

  subl.. title:: clang-tidy - abseil-no-internal-dependencies

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_MPAIA
### Default
#### OriginalId=bugprone-misplaced-pointer-arithmetic-in-alloc
#### Enabled=true
#### Warning=true
#### DisplayName=Misplaced Pointer Arithmetic In Alloc
#### HelpText
  Finds cases where an integer expression is added to or subtracted from the result of a memory allocation function (malloc(), calloc(), realloc(), alloca()) instead of its argument. The check detects error cases even if one of these functions is called by a constant function pointer.

  Example code:

  ``` cpp
  void bad_malloc(int n) {
    char *p = (char*) malloc(n) + 10;
  }

  ```


  The suggested fix is to add the integer expression to the argument of malloc and not to its result. In the example above the fix would be

  ``` cpp
  char *p = (char*) malloc(n + 10);

  ```


  (Clang-Tidy original name: bugprone-misplaced-pointer-arithmetic-in-alloc)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_MRSE
### Default
#### OriginalId=bugprone-macro-repeated-side-effects
#### Enabled=true
#### Warning=true
#### DisplayName=Macro Repeated Side Effects
#### HelpText
  Checks for repeated argument with side effects in macros.

  (Clang-Tidy original name: bugprone-macro-repeated-side-effects)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_MSM
### Default
#### OriginalId=bugprone-multiple-statement-macro
#### Enabled=true
#### Warning=true
#### DisplayName=Multiple Statement Macro
#### HelpText
  Detect multiple statement macros that are used in unbraced conditionals. Only the first statement of the macro will be inside the conditional and the other ones will be executed unconditionally.

  Example:

  ``` cpp
  #define INCREMENT_TWO(x, y) (x)++; (y)++
  if (do_increment)
    INCREMENT_TWO(a, b);  // (b)++ will be executed unconditionally.

  ```


  (Clang-Tidy original name: bugprone-multiple-statement-macro)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_MWC
### Default
#### OriginalId=bugprone-misplaced-widening-cast
#### Enabled=true
#### Warning=true
#### DisplayName=Misplaced Widening Cast
#### HelpText
  This check will warn when there is a cast of a calculation result to a bigger type. If the intention of the cast is to avoid loss of precision then the cast is misplaced, and there can be loss of precision. Otherwise the cast is ineffective.

  Example code:

  ``` cpp
  long f(int x) {
      return (long)(x * 1000);
  }

  ```


  The result x * 1000 is first calculated using int precision. If the result exceeds int precision there is loss of precision. Then the result is casted to long.

  If there is no loss of precision then the cast can be removed or you can explicitly cast to int instead.

  If you want to avoid loss of precision then put the cast in a proper location, for instance:

  ``` cpp
  long f(int x) {
      return (long)x * 1000;
  }

  ```


  ##### Implicit casts

  Forgetting to place the cast at all is at least as dangerous and at least as common as misplacing it. If [CheckImplicitCasts](\#cmdoption-arg-checkimplicitcasts) is enabled the check also detects these cases, for instance:

  ``` cpp
  long f(int x) {
      return x * 1000;
  }

  ```


  ##### Floating point

  Currently warnings are only written for integer conversion. No warning is written for this code:

  ``` cpp
  double f(float x) {
      return (double)(x * 10.0f);
  }

  ```


  ##### Options

  CheckImplicitCasts     

  If true, enables detection of implicit casts. Default is true.

  (Clang-Tidy original name: bugprone-misplaced-widening-cast)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_NC
### Default
#### OriginalId=bugprone-narrowing-conversions
#### Enabled=true
#### Warning=true
#### DisplayName=Narrowing Conversions
#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_NE
### Default
#### OriginalId=bugprone-no-escape
#### Enabled=true
#### Warning=true
#### DisplayName=No Escape
#### HelpText
  Finds pointers with the noescape attribute that are captured by an asynchronously-executed block. The block arguments in dispatch_async() and dispatch_after() are guaranteed to escape, so it is an error if a pointer with the noescape attribute is captured by one of these blocks.

  The following is an example of an invalid use of the noescape attribute.

  ``` cpp
  void foo(__attribute__((noescape)) int *p) {
    dispatch_async(queue, ^{
      *p = 123;
    });
  });

  ```


  (Clang-Tidy original name: bugprone-no-escape)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_NNTR
### Default
#### OriginalId=bugprone-not-null-terminated-result
#### Enabled=true
#### Warning=true
#### DisplayName=Not Null Terminated Result
#### HelpText
  Finds function calls where it is possible to cause a not null-terminated result. Usually the proper length of a string is strlen(src) + 1 or equal length of this expression, because the null terminator needs an extra space. Without the null terminator it can result in undefined behaviour when the string is read.

  The following and their respective wchar_t based functions are checked:

  memcpy, memcpy_s, memchr, memmove, memmove_s, strerror_s, strncmp, strxfrm

  The following is a real-world example where the programmer forgot to increase the passed third argument, which is size_t length. That is why the length of the allocated memory is not enough to hold the null terminator.

  ``` cpp
  static char *stringCpy(const std::string &str) {
    char *result = reinterpret_cast<char *>(malloc(str.size()));
    memcpy(result, str.data(), str.size());
    return result;
  }

  ```


  In addition to issuing warnings, fix-it rewrites all the necessary code. It also tries to adjust the capacity of the destination array:

  ``` cpp
  static char *stringCpy(const std::string &str) {
    char *result = reinterpret_cast<char *>(malloc(str.size() + 1));
    strcpy(result, str.data());
    return result;
  }

  ```


  Note: It cannot guarantee to rewrite every of the path-sensitive memory allocations.

  ##### Transformation rules of ‘memcpy()’

  It is possible to rewrite the memcpy() and memcpy_s() calls as the following four functions: strcpy(), strncpy(), strcpy_s(), strncpy_s(), where the latter two are the safer versions of the former two. It rewrites the wchar_t based memory handler functions respectively.

  ###### Rewrite based on the destination array

    * If copy to the destination array cannot overflow [1] the new function should be the older copy function (ending with cpy), because it is more efficient than the safe version.
    * If copy to the destination array can overflow [1] and [WantToUseSafeFunctions](\#cmdoption-arg-wanttousesafefunctions) is set to true and it is possible to obtain the capacity of the destination array then the new function could be the safe version (ending with cpy_s).
    * If the new function is could be safe version and C++ files are analysed and the destination array is plain char/wchar_t without un/signed then the length of the destination array can be omitted.
    * If the new function is could be safe version and the destination array is un/signed it needs to be casted to plain char */wchar_t *.

  [1] It is possible to overflow:     

    * If the capacity of the destination array is unknown.
    * If the given length is equal to the destination array’s capacity.



  ###### Rewrite based on the length of the source string

    * If the given length is strlen(source) or equal length of this expression then the new function should be the older copy function (ending with cpy), as it is more efficient than the safe version (ending with cpy_s).
    * Otherwise we assume that the programmer wanted to copy ‘N’ characters, so the new function is ncpy-like which copies ‘N’ characters.



  ##### Transformations with ‘strlen()’ or equal length of this expression

  It transforms the wchar_t based memory and string handler functions respectively (where only strerror_s does not have wchar_t based alias).

  ###### Memory handler functions

  memcpy Please visit the [Transformation rules of ‘memcpy()’](\#memcpytransformation) section.

  memchr Usually there is a C-style cast and it is needed to be removed, because the new function strchr’s return type is correct. The given length is going to be removed.

  memmove If safe functions are available the new function is memmove_s, which has a new second argument which is the length of the destination array, it is adjusted, and the length of the source string is incremented by one. If safe functions are not available the given length is incremented by one.

  memmove_s The given length is incremented by one.

  ###### String handler functions

  strerror_s The given length is incremented by one.

  strncmp If the third argument is the first or the second argument’s length + 1 it has to be truncated without the + 1 operation.

  strxfrm The given length is incremented by one.

  ##### Options

  WantToUseSafeFunctions     

  The value true specifies that the target environment is considered to implement ‘_s’ suffixed memory and string handler functions which are safer than older versions (e.g. ‘memcpy_s()’). The default value is true.

  (Clang-Tidy original name: bugprone-not-null-terminated-result)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_PR
### Default
#### OriginalId=bugprone-posix-return
#### Enabled=true
#### Warning=true
#### DisplayName=Posix Return
#### HelpText
  Checks if any calls to pthread_* or posix_* functions (except posix_openpt) expect negative return values. These functions return either 0 on success or an errno on failure, which is positive only.

  Example buggy usage looks like:

  ``` cpp
  if (posix_fadvise(...) < 0) {

  ```


  This will never happen as the return value is always non-negative. A simple fix could be:

  ``` cpp
  if (posix_fadvise(...) > 0) {

  ```


  (Clang-Tidy original name: bugprone-posix-return)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_PVC
### Default
#### OriginalId=bugprone-parent-virtual-call
#### Enabled=true
#### Warning=true
#### DisplayName=Parent Virtual Call
#### HelpText
  Detects and fixes calls to grand-…parent virtual methods instead of calls to overridden parent’s virtual methods.

  ``` cpp
  struct A {
    int virtual foo() {...}
  };

  struct B: public A {
    int foo() override {...}
  };

  struct C: public B {
    int foo() override { A::foo(); }
  //                     ^^^^^^^^
  // warning: qualified name A::foo refers to a member overridden in subclass; did you mean 'B'?  [bugprone-parent-virtual-call]
  };

  ```


  (Clang-Tidy original name: bugprone-parent-virtual-call)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_RBC
### Default
#### OriginalId=bugprone-redundant-branch-condition
#### Enabled=true
#### Warning=true
#### DisplayName=Redundant Branch Condition
#### HelpText
  Finds condition variables in nested if statements that were also checked in the outer if statement and were not changed.

  Simple example:

  ``` cpp
  bool onFire = isBurning();
  if (onFire) {
    if (onFire)
      scream();
  }

  ```


  Here onFire is checked both in the outer if and the inner if statement without a possible change between the two checks. The check warns for this code and suggests removal of the second checking of variable onFire.

  The checker also detects redundant condition checks if the condition variable is an operand of a logical “and” (&&) or a logical “or” (||) operator:

  ``` cpp
  bool onFire = isBurning();
  if (onFire) {
    if (onFire && peopleInTheBuilding > 0)
      scream();
  }

  ```


  ``` cpp
  bool onFire = isBurning();
  if (onFire) {
    if (onFire || isCollapsing())
      scream();
  }

  ```


  In the first case (logical “and”) the suggested fix is to remove the redundant condition variable and keep the other side of the &&. In the second case (logical “or”) the whole if is removed similarily to the simple case on the top.

  The condition of the outer if statement may also be a logical “and” (&&) expression:

  ``` cpp
  bool onFire = isBurning();
  if (onFire && fireFighters < 10) {
    if (someOtherCondition()) {
      if (onFire)
        scream();
    }
  }

  ```


  The error is also detected if both the outer statement is a logical “and” (&&) and the inner statement is a logical “and” (&&) or “or” (||). The inner if statement does not have to be a direct descendant of the outer one.

  No error is detected if the condition variable may have been changed between the two checks:

  ``` cpp
  bool onFire = isBurning();
  if (onFire) {
    tryToExtinguish(onFire);
    if (onFire && peopleInTheBuilding > 0)
      scream();
  }

  ```


  Every possible change is considered, thus if the condition variable is not a local variable of the function, it is a volatile or it has an alias (pointer or reference) then no warning is issued.

  ##### Known limitations

  The else branch is not checked currently for negated condition variable:

  ``` cpp
  bool onFire = isBurning();
  if (onFire) {
    scream();
  } else {
    if (!onFire) {
      continueWork();
    }
  }

  ```


  The checker currently only detects redundant checking of single condition variables. More complex expressions are not checked:

  ``` cpp
  if (peopleInTheBuilding == 1) {
    if (peopleInTheBuilding == 1) {
      doSomething();
    }
  }

  ```


  (Clang-Tidy original name: bugprone-redundant-branch-condition)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_RI
### Default
#### OriginalId=bugprone-reserved-identifier
#### Enabled=true
#### Warning=true
#### DisplayName=Reserved Identifier
#### HelpText
  cert-dcl37-c and cert-dcl51-cpp redirect here as an alias for this check.

  Checks for usages of identifiers reserved for use by the implementation.

  The C and C++ standards both reserve the following names for such use:

    * identifiers that begin with an underscore followed by an uppercase letter;
    * identifiers in the global namespace that begin with an underscore.



  The C standard additionally reserves names beginning with a double underscore, while the C++ standard strengthens this to reserve names with a double underscore occurring anywhere.

  Violating the naming rules above results in undefined behavior.

  ``` cpp
  namespace NS {
    void __f(); // name is not allowed in user code
    using _Int = int; // same with this
    #define cool__macro // also this
  }
  int _g(); // disallowed in global namespace only

  ```


  The check can also be inverted, i.e. it can be configured to flag any identifier that is _not_ a reserved identifier. This mode is for use by e.g. standard library implementors, to ensure they don’t infringe on the user namespace.

  This check does not (yet) check for other reserved names, e.g. macro names identical to language keywords, and names specifically reserved by language standards, e.g. C++ ‘zombie names’ and C future library directions.

  This check corresponds to CERT C Coding Standard rule [DCL37-C. Do not declare or define a reserved identifier](https://wiki.sei.cmu.edu/confluence/display/c/DCL37-C.+Do+not+declare+or+define+a+reserved+identifier) as well as its C++ counterpart, [DCL51-CPP. Do not declare or define a reserved identifier](https://wiki.sei.cmu.edu/confluence/display/cplusplus/DCL51-CPP.+Do+not+declare+or+define+a+reserved+identifier).

  ##### Options

  Invert     

  If true, inverts the check, i.e. flags names that are not reserved. Default is false.

  AllowedIdentifiers     

  Semicolon-separated list of names that the check ignores. Default is an empty list.

  (Clang-Tidy original name: bugprone-reserved-identifier)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_SA
### Default
#### OriginalId=bugprone-swapped-arguments
#### Enabled=true
#### Warning=true
#### DisplayName=Swapped Arguments
#### HelpText
  Finds potentially swapped arguments by looking at implicit conversions.

  (Clang-Tidy original name: bugprone-swapped-arguments)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_SC
### Default
#### OriginalId=bugprone-sizeof-container
#### Enabled=true
#### Warning=true
#### DisplayName=Sizeof Container
#### HelpText
  The check finds usages of sizeof on expressions of STL container types. Most likely the user wanted to use .size() instead.

  All class/struct types declared in namespace std:: having a const size() method are considered containers, with the exception of std::bitset and std::array.

  Examples:

  ``` cpp
  std::string s;
  int a = 47 + sizeof(s); // warning: sizeof() doesn't return the size of the container. Did you mean .size()?

  int b = sizeof(std::string); // no warning, probably intended.

  std::string array_of_strings[10];
  int c = sizeof(array_of_strings) / sizeof(array_of_strings[0]); // no warning, definitely intended.

  std::array<int, 3> std_array;
  int d = sizeof(std_array); // no warning, probably intended.

  ```


  (Clang-Tidy original name: bugprone-sizeof-container)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_SC2
### Default
#### OriginalId=bugprone-string-constructor
#### Enabled=true
#### Warning=true
#### DisplayName=String Constructor
#### HelpText
  Finds string constructors that are suspicious and probably errors.

  A common mistake is to swap parameters to the ‘fill’ string-constructor.

  Examples:

  ``` cpp
  std::string str('x', 50); // should be str(50, 'x')

  ```


  Calling the string-literal constructor with a length bigger than the literal is suspicious and adds extra random characters to the string.

  Examples:

  ``` cpp
  std::string("test", 200);   // Will include random characters after "test".
  std::string_view("test", 200);

  ```


  Creating an empty string from constructors with parameters is considered suspicious. The programmer should use the empty constructor instead.

  Examples:

  ``` cpp
  std::string("test", 0);   // Creation of an empty string.
  std::string_view("test", 0);

  ```


  ##### Options

  WarnOnLargeLength     

  When true, the check will warn on a string with a length greater than [LargeLengthThreshold](\#cmdoption-arg-largelengththreshold). Default is true.

  LargeLengthThreshold     

  An integer specifying the large length threshold. Default is 0x800000.

  StringNames     

  Default is ::std::basic_string;::std::basic_string_view.

  Semicolon-delimited list of class names to apply this check to. By default ::std::basic_string applies to std::string and std::wstring. Set to e.g. ::std::basic_string;llvm::StringRef;QString to perform this check on custom classes.

  (Clang-Tidy original name: bugprone-string-constructor)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_SCM
### Default
#### OriginalId=bugprone-signed-char-misuse
#### Enabled=true
#### Warning=true
#### DisplayName=Signed Char Misuse
#### HelpText
  cert-str34-c redirects here as an alias for this check. For the CERT alias, the DiagnoseSignedUnsignedCharComparisons option is set to false.

  Finds those signed char -> integer conversions which might indicate a programming error. The basic problem with the signed char, that it might store the non-ASCII characters as negative values. This behavior can cause a misunderstanding of the written code both when an explicit and when an implicit conversion happens.

  When the code contains an explicit signed char -> integer conversion, the human programmer probably expects that the converted value matches with the character code (a value from [0..255]), however, the actual value is in [-128..127] interval. To avoid this kind of misinterpretation, the desired way of converting from a signed char to an integer value is converting to unsigned char first, which stores all the characters in the positive [0..255] interval which matches the known character codes.

  In case of implicit conversion, the programmer might not actually be aware that a conversion happened and char value is used as an integer. There are some use cases when this unawareness might lead to a functionally imperfect code. For example, checking the equality of a signed char and an unsigned char variable is something we should avoid in C++ code. During this comparison, the two variables are converted to integers which have different value ranges. For signed char, the non-ASCII characters are stored as a value in [-128..-1] interval, while the same characters are stored in the [128..255] interval for an unsigned char.

  It depends on the actual platform whether plain char is handled as signed char by default and so it is caught by this check or not. To change the default behavior you can use -funsigned-char and -fsigned-char compilation options.

  Currently, this check warns in the following cases: \- signed char is assigned to an integer variable \- signed char and unsigned char are compared with equality/inequality operator \- signed char is converted to an integer in the array subscript

  See also: [STR34-C. Cast characters to unsigned char before converting to larger integer sizes](https://wiki.sei.cmu.edu/confluence/display/c/STR34-C.+Cast+characters+to+unsigned+char+before+converting+to+larger+integer+sizes)

  A good example from the CERT description when a char variable is used to read from a file that might contain non-ASCII characters. The problem comes up when the code uses the -1 integer value as EOF, while the 255 character code is also stored as -1 in two’s complement form of char type. See a simple example of this bellow. This code stops not only when it reaches the end of the file, but also when it gets a character with the 255 code.

  ``` cpp
  #define EOF (-1)

  int read(void) {
    char CChar;
    int IChar = EOF;

    if (readChar(CChar)) {
      IChar = CChar;
    }
    return IChar;
  }

  ```


  A proper way to fix the code above is converting the char variable to an unsigned char value first.

  ``` cpp
  #define EOF (-1)

  int read(void) {
    char CChar;
    int IChar = EOF;

    if (readChar(CChar)) {
      IChar = static_cast<unsigned char>(CChar);
    }
    return IChar;
  }

  ```


  Another use case is checking the equality of two char variables with different signedness. Inside the non-ASCII value range this comparison between a signed char and an unsigned char always returns false.

  ``` cpp
  bool compare(signed char SChar, unsigned char USChar) {
    if (SChar == USChar)
      return true;
    return false;
  }

  ```


  The easiest way to fix this kind of comparison is casting one of the arguments, so both arguments will have the same type.

  ``` cpp
  bool compare(signed char SChar, unsigned char USChar) {
    if (static_cast<unsigned char>(SChar) == USChar)
      return true;
    return false;
  }

  ```


  CharTypdefsToIgnore     

  A semicolon-separated list of typedef names. In this list, we can list typedefs for char or signed char, which will be ignored by the check. This is useful when a typedef introduces an integer alias like sal_Int8 or int8_t. In this case, human misinterpretation is not an issue.

  DiagnoseSignedUnsignedCharComparisons     

  When true, the check will warn on signed char/unsigned char comparisons, otherwise these comparisons are ignored. By default, this option is set to true.

  (Clang-Tidy original name: bugprone-signed-char-misuse)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_SE
### Default
#### OriginalId=bugprone-sizeof-expression
#### Enabled=true
#### Warning=true
#### DisplayName=Sizeof Expression
#### HelpText
  The check finds usages of sizeof expressions which are most likely errors.

  The sizeof operator yields the size (in bytes) of its operand, which may be an expression or the parenthesized name of a type. Misuse of this operator may be leading to errors and possible software vulnerabilities.

  ##### Suspicious usage of ‘sizeof(K)’

  A common mistake is to query the sizeof of an integer literal. This is equivalent to query the size of its type (probably int). The intent of the programmer was probably to simply get the integer and not its size.

  ``` cpp
  #define BUFLEN 42
  char buf[BUFLEN];
  memset(buf, 0, sizeof(BUFLEN));  // sizeof(42) ==> sizeof(int)

  ```


  ##### Suspicious usage of ‘sizeof(expr)’

  In cases, where there is an enum or integer to represent a type, a common mistake is to query the sizeof on the integer or enum that represents the type that should be used by sizeof. This results in the size of the integer and not of the type the integer represents:

  ``` cpp
  enum data_type {
    FLOAT_TYPE,
    DOUBLE_TYPE
  };

  struct data {
    data_type type;
    void* buffer;
    data_type get_type() {
      return type;
    }
  };

  void f(data d, int numElements) {
    // should be sizeof(float) or sizeof(double), depending on d.get_type()
    int numBytes = numElements * sizeof(d.get_type());
    ...
  }

  ```


  ##### Suspicious usage of ‘sizeof(this)’

  The this keyword is evaluated to a pointer to an object of a given type. The expression sizeof(this) is returning the size of a pointer. The programmer most likely wanted the size of the object and not the size of the pointer.

  ``` cpp
  class Point {
    [...]
    size_t size() { return sizeof(this); }  // should probably be sizeof(*this)
    [...]
  };

  ```


  ##### Suspicious usage of ‘sizeof(char*)’

  There is a subtle difference between declaring a string literal with char* A = "" and char A[] = "". The first case has the type char* instead of the aggregate type char[]. Using sizeof on an object declared with char* type is returning the size of a pointer instead of the number of characters (bytes) in the string literal.

  ``` cpp
  const char* kMessage = "Hello World!";      // const char kMessage[] = "...";
  void getMessage(char* buf) {
    memcpy(buf, kMessage, sizeof(kMessage));  // sizeof(char*)
  }

  ```


  ##### Suspicious usage of ‘sizeof(A*)’

  A common mistake is to compute the size of a pointer instead of its pointee. These cases may occur because of explicit cast or implicit conversion.

  ``` cpp
  int A[10];
  memset(A, 0, sizeof(A + 0));

  struct Point point;
  memset(point, 0, sizeof(&point));

  ```


  ##### Suspicious usage of ‘sizeof(…)/sizeof(…)’

  Dividing sizeof expressions is typically used to retrieve the number of elements of an aggregate. This check warns on incompatible or suspicious cases.

  In the following example, the entity has 10-bytes and is incompatible with the type int which has 4 bytes.

  ``` cpp
  char buf[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };  // sizeof(buf) => 10
  void getMessage(char* dst) {
    memcpy(dst, buf, sizeof(buf) / sizeof(int));  // sizeof(int) => 4  [incompatible sizes]
  }

  ```


  In the following example, the expression sizeof(Values) is returning the size of char*. One can easily be fooled by its declaration, but in parameter declaration the size ‘10’ is ignored and the function is receiving a char*.

  ``` cpp
  char OrderedValues[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  return CompareArray(char Values[10]) {
    return memcmp(OrderedValues, Values, sizeof(Values)) == 0;  // sizeof(Values) ==> sizeof(char*) [implicit cast to char*]
  }

  ```


  ##### Suspicious ‘sizeof’ by ‘sizeof’ expression

  Multiplying sizeof expressions typically makes no sense and is probably a logic error. In the following example, the programmer used * instead of /.

  ``` cpp
  const char kMessage[] = "Hello World!";
  void getMessage(char* buf) {
    memcpy(buf, kMessage, sizeof(kMessage) * sizeof(char));  //  sizeof(kMessage) / sizeof(char)
  }

  ```


  This check may trigger on code using the arraysize macro. The following code is working correctly but should be simplified by using only the sizeof operator.

  ``` cpp
  extern Object objects[100];
  void InitializeObjects() {
    memset(objects, 0, arraysize(objects) * sizeof(Object));  // sizeof(objects)
  }

  ```


  ##### Suspicious usage of ‘sizeof(sizeof(…))’

  Getting the sizeof of a sizeof makes no sense and is typically an error hidden through macros.

  ``` cpp
  #define INT_SZ sizeof(int)
  int buf[] = { 42 };
  void getInt(int* dst) {
    memcpy(dst, buf, sizeof(INT_SZ));  // sizeof(sizeof(int)) is suspicious.
  }

  ```


  ##### Options

  WarnOnSizeOfConstant     

  When true, the check will warn on an expression like sizeof(CONSTANT). Default is true.

  WarnOnSizeOfIntegerExpression     

  When true, the check will warn on an expression like sizeof(expr) where the expression results in an integer. Default is false.

  WarnOnSizeOfThis     

  When true, the check will warn on an expression like sizeof(this). Default is true.

  WarnOnSizeOfCompareToConstant     

  When true, the check will warn on an expression like sizeof(epxr) <= k for a suspicious constant k while k is 0 or greater than 0x8000. Default is true.

  (Clang-Tidy original name: bugprone-sizeof-expression)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_SEU
### Default
#### OriginalId=bugprone-suspicious-enum-usage
#### Enabled=true
#### Warning=true
#### DisplayName=Suspicious Enum Usage
#### HelpText
  The checker detects various cases when an enum is probably misused (as a bitmask ).

    1. When “ADD” or “bitwise OR” is used between two enum which come from different types and these types value ranges are not disjoint.



  The following cases will be investigated only using [StrictMode](performance-inefficient-string-concatenation.html\#cmdoption-arg-strictmode). We regard the enum as a (suspicious) bitmask if the three conditions below are true at the same time:

    * at most half of the elements of the enum are non pow-of-2 numbers (because of short enumerations)
    * there is another non pow-of-2 number than the enum constant representing all choices (the result “bitwise OR” operation of all enum elements)
    * enum type variable/enumconstant is used as an argument of a + or “bitwise OR ” operator



  So whenever the non pow-of-2 element is used as a bitmask element we diagnose a misuse and give a warning.

    2. Investigating the right hand side of += and |= operator.
    3. Check only the enum value side of a | and + operator if one of them is not enum val.
    4. Check both side of | or + operator where the enum values are from the same enum type.



  Examples:

  ``` cpp
  enum { A, B, C };
  enum { D, E, F = 5 };
  enum { G = 10, H = 11, I = 12 };

  unsigned flag;
  flag =
      A |
      H; // OK, disjoint value intervals in the enum types ->probably good use.
  flag = B | F; // Warning, have common values so they are probably misused.

  // Case 2:
  enum Bitmask {
    A = 0,
    B = 1,
    C = 2,
    D = 4,
    E = 8,
    F = 16,
    G = 31 // OK, real bitmask.
  };

  enum Almostbitmask {
    AA = 0,
    BB = 1,
    CC = 2,
    DD = 4,
    EE = 8,
    FF = 16,
    GG // Problem, forgot to initialize.
  };

  unsigned flag = 0;
  flag |= E; // OK.
  flag |=
      EE; // Warning at the decl, and note that it was used here as a bitmask.

  ```


  ##### Options

  StrictMode     

  Default value: 0. When non-null the suspicious bitmask usage will be investigated additionally to the different enum usage check.

  (Clang-Tidy original name: bugprone-suspicious-enum-usage)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_SH
### Default
#### OriginalId=bugprone-signal-handler
#### Enabled=true
#### Warning=true
#### DisplayName=Signal Handler
#### HelpText
  Finds functions registered as signal handlers that call non asynchronous-safe functions. Any function that cannot be determined to be an asynchronous-safe function call is assumed to be non-asynchronous-safe by the checker, including user functions for which only the declaration is visible. User function calls with visible definition are checked recursively. The check handles only C code.

  The minimal list of asynchronous-safe system functions is: abort(), _Exit(), quick_exit() and signal() (for signal there are additional conditions that are not checked). The check accepts only these calls as asynchronous-safe.

  This check corresponds to the CERT C Coding Standard rule [SIG30-C. Call only asynchronous-safe functions within signal handlers](https://www.securecoding.cert.org/confluence/display/c/SIG30-C.+Call+only+asynchronous-safe+functions+within+signal+handlers).

  (Clang-Tidy original name: bugprone-signal-handler)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_SI
### Default
#### OriginalId=bugprone-suspicious-include
#### Enabled=true
#### Warning=true
#### DisplayName=Suspicious Include
#### HelpText
  The check detects various cases when an include refers to what appears to be an implementation file, which often leads to hard-to-track-down ODR violations.

  Examples:

  ``` cpp
  #include "Dinosaur.hpp"     // OK, .hpp files tend not to have definitions.
  #include "Pterodactyl.h"    // OK, .h files tend not to have definitions.
  #include "Velociraptor.cpp" // Warning, filename is suspicious.
  #include_next <stdio.c>     // Warning, filename is suspicious.

  ```


  ##### Options

  HeaderFileExtensions     

  Default value: ";h;hh;hpp;hxx" A semicolon-separated list of filename extensions of header files (the filename extensions should not contain a “.” prefix). For extension-less header files, use an empty string or leave an empty string between “;” if there are other filename extensions.

  ImplementationFileExtensions     

  Default value: "c;cc;cpp;cxx" Likewise, a semicolon-separated list of filename extensions of implementation files.

  (Clang-Tidy original name: bugprone-suspicious-include)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_SIA
### Default
#### OriginalId=bugprone-string-integer-assignment
#### Enabled=true
#### Warning=true
#### DisplayName=String Integer Assignment
#### HelpText
  The check finds assignments of an integer to std::basic_string<CharT> (std::string, std::wstring, etc.). The source of the problem is the following assignment operator of std::basic_string<CharT>:

  ``` cpp
  basic_string& operator=( CharT ch );

  ```


  Numeric types can be implicitly casted to character types.

  ``` cpp
  std::string s;
  int x = 5965;
  s = 6;
  s = x;

  ```


  Use the appropriate conversion functions or character literals.

  ``` cpp
  std::string s;
  int x = 5965;
  s = '6';
  s = std::to_string(x);

  ```


  In order to suppress false positives, use an explicit cast.

  ``` cpp
  std::string s;
  s = static_cast<char>(6);

  ```


  (Clang-Tidy original name: bugprone-string-integer-assignment)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_SLWEN
### Default
#### OriginalId=bugprone-string-literal-with-embedded-nul
#### Enabled=true
#### Warning=true
#### DisplayName=String Literal With Embedded Nul
#### HelpText
  Finds occurrences of string literal with embedded NUL character and validates their usage.

  ##### Invalid escaping

  Special characters can be escaped within a string literal by using their hexadecimal encoding like \x42. A common mistake is to escape them like this \0x42 where the \0 stands for the NUL character.

  ``` cpp
  const char* Example[] = "Invalid character: \0x12 should be \x12";
  const char* Bytes[] = "\x03\0x02\0x01\0x00\0xFF\0xFF\0xFF";

  ```


  ##### Truncated literal

  String-like classes can manipulate strings with embedded NUL as they are keeping track of the bytes and the length. This is not the case for a char* (NUL-terminated) string.

  A common mistake is to pass a string-literal with embedded NUL to a string constructor expecting a NUL-terminated string. The bytes after the first NUL character are truncated.

  ``` cpp
  std::string str("abc\0def");  // "def" is truncated
  str += "\0";                  // This statement is doing nothing
  if (str == "\0abc") return;   // This expression is always true

  ```


  (Clang-Tidy original name: bugprone-string-literal-with-embedded-nul)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_SMC
### Default
#### OriginalId=bugprone-suspicious-missing-comma
#### Enabled=true
#### Warning=true
#### DisplayName=Suspicious Missing Comma
#### HelpText
  String literals placed side-by-side are concatenated at translation phase 6 (after the preprocessor). This feature is used to represent long string literal on multiple lines.

  For instance, the following declarations are equivalent:

  ``` cpp
  const char* A[] = "This is a test";
  const char* B[] = "This" " is a "    "test";

  ```


  A common mistake done by programmers is to forget a comma between two string literals in an array initializer list.

  ``` cpp
  const char* Test[] = {
    "line 1",
    "line 2"     // Missing comma!
    "line 3",
    "line 4",
    "line 5"
  };

  ```


  The array contains the string “line 2line3” at offset 1 (i.e. Test[1]). Clang won’t generate warnings at compile time.

  This check may warn incorrectly on cases like:

  ``` cpp
  const char* SupportedFormat[] = {
    "Error %s",
    "Code " PRIu64,   // May warn here.
    "Warning %s",
  };

  ```


  ##### Options

  SizeThreshold     

  An unsigned integer specifying the minimum size of a string literal to be considered by the check. Default is 5U.

  RatioThreshold     

  A string specifying the maximum threshold ratio [0, 1.0] of suspicious string literals to be considered. Default is ".2".

  MaxConcatenatedTokens     

  An unsigned integer specifying the maximum number of concatenated tokens. Default is 5U.

  (Clang-Tidy original name: bugprone-suspicious-missing-comma)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_SMU
### Default
#### OriginalId=bugprone-suspicious-memset-usage
#### Enabled=true
#### Warning=true
#### DisplayName=Suspicious Memset Usage
#### HelpText
  This check finds memset() calls with potential mistakes in their arguments. Considering the function as void* memset(void* destination, int fill_value, size_t byte_count), the following cases are covered:

  **Case 1: Fill value is a character ``’0’``**

  Filling up a memory area with ASCII code 48 characters is not customary, possibly integer zeroes were intended instead. The check offers a replacement of '0' with 0. Memsetting character pointers with '0' is allowed.

  **Case 2: Fill value is truncated**

  Memset converts fill_value to unsigned char before using it. If fill_value is out of unsigned character range, it gets truncated and memory will not contain the desired pattern.

  **Case 3: Byte count is zero**

  Calling memset with a literal zero in its byte_count argument is likely to be unintended and swapped with fill_value. The check offers to swap these two arguments.

  Corresponding cpplint.py check name: runtime/memset.

  Examples:

  ``` cpp
  void foo() {
    int i[5] = {1, 2, 3, 4, 5};
    int *ip = i;
    char c = '1';
    char *cp = &c;
    int v = 0;

    // Case 1
    memset(ip, '0', 1); // suspicious
    memset(cp, '0', 1); // OK

    // Case 2
    memset(ip, 0xabcd, 1); // fill value gets truncated
    memset(ip, 0x00, 1);   // OK

    // Case 3
    memset(ip, sizeof(int), v); // zero length, potentially swapped
    memset(ip, 0, 1);           // OK
  }

  ```


  (Clang-Tidy original name: bugprone-suspicious-memset-usage)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_SS
### Default
#### OriginalId=bugprone-suspicious-semicolon
#### Enabled=true
#### Warning=true
#### DisplayName=Suspicious Semicolon
#### HelpText
  Finds most instances of stray semicolons that unexpectedly alter the meaning of the code. More specifically, it looks for if, while, for and for-range statements whose body is a single semicolon, and then analyzes the context of the code (e.g. indentation) in an attempt to determine whether that is intentional.

  ``` cpp
  if (x < y);
  {
    x++;
  }

  ```


  Here the body of the if statement consists of only the semicolon at the end of the first line, and x will be incremented regardless of the condition.

  ``` cpp
  while ((line = readLine(file)) != NULL);
    processLine(line);

  ```


  As a result of this code, processLine() will only be called once, when the while loop with the empty body exits with line == NULL. The indentation of the code indicates the intention of the programmer.

  ``` cpp
  if (x >= y);
  x -= y;

  ```


  While the indentation does not imply any nesting, there is simply no valid reason to have an if statement with an empty body (but it can make sense for a loop). So this check issues a warning for the code above.

  To solve the issue remove the stray semicolon or in case the empty body is intentional, reflect this using code indentation or put the semicolon in a new line. For example:

  ``` cpp
  while (readWhitespace());
    Token t = readNextToken();

  ```


  Here the second line is indented in a way that suggests that it is meant to be the body of the while loop - whose body is in fact empty, because of the semicolon at the end of the first line.

  Either remove the indentation from the second line:

  ``` cpp
  while (readWhitespace());
  Token t = readNextToken();

  ```


  … or move the semicolon from the end of the first line to a new line:

  ``` cpp
  while (readWhitespace())
    ;

    Token t = readNextToken();

  ```


  In this case the check will assume that you know what you are doing, and will not raise a warning.

  (Clang-Tidy original name: bugprone-suspicious-semicolon)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_SSC
### Default
#### OriginalId=bugprone-suspicious-string-compare
#### Enabled=true
#### Warning=true
#### DisplayName=Suspicious String Compare
#### HelpText
  Find suspicious usage of runtime string comparison functions. This check is valid in C and C++.

  Checks for calls with implicit comparator and proposed to explicitly add it.

  ``` cpp
  if (strcmp(...))       // Implicitly compare to zero
  if (!strcmp(...))      // Won't warn
  if (strcmp(...) != 0)  // Won't warn

  ```


  Checks that compare function results (i,e, strcmp) are compared to valid constant. The resulting value is

  ``` cpp
  <  0    when lower than,
  >  0    when greater than,
  == 0    when equals.

  ```


  A common mistake is to compare the result to 1 or -1.

  ``` cpp
  if (strcmp(...) == -1)  // Incorrect usage of the returned value.

  ```


  Additionally, the check warns if the results value is implicitly cast to a _suspicious_ non-integer type. It’s happening when the returned value is used in a wrong context.

  ``` cpp
  if (strcmp(...) < 0.)  // Incorrect usage of the returned value.

  ```


  ##### Options

  WarnOnImplicitComparison     

  When true, the check will warn on implicit comparison. true by default.

  WarnOnLogicalNotComparison     

  When true, the check will warn on logical not comparison. false by default.

  StringCompareLikeFunctions     

  A string specifying the comma-separated names of the extra string comparison functions. Default is an empty string. The check will detect the following string comparison functions: __builtin_memcmp, __builtin_strcasecmp, __builtin_strcmp, __builtin_strncasecmp, __builtin_strncmp, _mbscmp, _mbscmp_l, _mbsicmp, _mbsicmp_l, _mbsnbcmp, _mbsnbcmp_l, _mbsnbicmp, _mbsnbicmp_l, _mbsncmp, _mbsncmp_l, _mbsnicmp, _mbsnicmp_l, _memicmp, _memicmp_l, _stricmp, _stricmp_l, _strnicmp, _strnicmp_l, _wcsicmp, _wcsicmp_l, _wcsnicmp, _wcsnicmp_l, lstrcmp, lstrcmpi, memcmp, memicmp, strcasecmp, strcmp, strcmpi, stricmp, strncasecmp, strncmp, strnicmp, wcscasecmp, wcscmp, wcsicmp, wcsncmp, wcsnicmp, wmemcmp.

  (Clang-Tidy original name: bugprone-suspicious-string-compare)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_SWUF
### Default
#### OriginalId=bugprone-spuriously-wake-up-functions
#### Enabled=true
#### Warning=true
#### DisplayName=Spuriously Wake Up Functions
#### HelpText
  Finds cnd_wait, cnd_timedwait, wait, wait_for, or wait_until function calls when the function is not invoked from a loop that checks whether a condition predicate holds or the function has a condition parameter.

  This check corresponds to the CERT C++ Coding Standard rule [CON54-CPP. Wrap functions that can spuriously wake up in a loop](https://wiki.sei.cmu.edu/confluence/display/cplusplus/CON54-CPP.+Wrap+functions+that+can+spuriously+wake+up+in+a+loop). and CERT C Coding Standard rule [CON36-C. Wrap functions that can spuriously wake up in a loop](https://wiki.sei.cmu.edu/confluence/display/c/CON36-C.+Wrap+functions+that+can+spuriously+wake+up+in+a+loop).

  (Clang-Tidy original name: bugprone-spuriously-wake-up-functions)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_TC
### Default
#### OriginalId=bugprone-terminating-continue
#### Enabled=true
#### Warning=true
#### DisplayName=Terminating Continue
#### HelpText
  Detects do while loops with a condition always evaluating to false that have a continue statement, as this continue terminates the loop effectively.

  ``` cpp
  void f() {
  do {
    // some code
    continue; // terminating continue
    // some other code
  } while(false);

  ```


  (Clang-Tidy original name: bugprone-terminating-continue)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_TKM
### Default
#### OriginalId=bugprone-throw-keyword-missing
#### Enabled=true
#### Warning=true
#### DisplayName=Throw Keyword Missing
#### HelpText
  Warns about a potentially missing throw keyword. If a temporary object is created, but the object’s type derives from (or is the same as) a class that has ‘EXCEPTION’, ‘Exception’ or ‘exception’ in its name, we can assume that the programmer’s intention was to throw that object.

  Example:

  ``` cpp
  void f(int i) {
    if (i < 0) {
      // Exception is created but is not thrown.
      std::runtime_error("Unexpected argument");
    }
  }

  ```


  (Clang-Tidy original name: bugprone-throw-keyword-missing)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_TSLV
### Default
#### OriginalId=bugprone-too-small-loop-variable
#### Enabled=true
#### Warning=true
#### DisplayName=Too Small Loop Variable
#### HelpText
  Detects those for loops that have a loop variable with a “too small” type which means this type can’t represent all values which are part of the iteration range.

  ``` cpp
  int main() {
    long size = 294967296l;
    for (short i = 0; i < size; ++i) {}
  }

  ```


  This for loop is an infinite loop because the short type can’t represent all values in the [0..size] interval.

  In a real use case size means a container’s size which depends on the user input.

  ``` cpp
  int doSomething(const std::vector& items) {
    for (short i = 0; i < items.size(); ++i) {}
  }

  ```


  This algorithm works for small amount of objects, but will lead to freeze for a a larger user input.

  MagnitudeBitsUpperLimit     

  Upper limit for the magnitude bits of the loop variable. If it’s set the check filters out those catches in which the loop variable’s type has more magnitude bits as the specified upper limit. The default value is 16. For example, if the user sets this option to 31 (bits), then a 32-bit unsigend int is ignored by the check, however a 32-bit int is not (A 32-bit signed int has 31 magnitude bits).

  ``` cpp
  int main() {
    long size = 294967296l;
    for (unsigned i = 0; i < size; ++i) {} // no warning with MagnitudeBitsUpperLimit = 31 on a system where unsigned is 32-bit
    for (int i = 0; i < size; ++i) {} // warning with MagnitudeBitsUpperLimit = 31 on a system where int is 32-bit
  }

  ```


  (Clang-Tidy original name: bugprone-too-small-loop-variable)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_UAM
### Default
#### OriginalId=bugprone-use-after-move
#### Enabled=true
#### Warning=true
#### DisplayName=Use After Move
#### HelpText
  Warns if an object is used after it has been moved, for example:

  ``` cpp
  std::string str = "Hello, world!\n";
  std::vector<std::string> messages;
  messages.emplace_back(std::move(str));
  std::cout << str;

  ```


  The last line will trigger a warning that str is used after it has been moved.

  The check does not trigger a warning if the object is reinitialized after the move and before the use. For example, no warning will be output for this code:

  ``` cpp
  messages.emplace_back(std::move(str));
  str = "Greetings, stranger!\n";
  std::cout << str;

  ```


  The check takes control flow into account. A warning is only emitted if the use can be reached from the move. This means that the following code does not produce a warning:

  ``` cpp
  if (condition) {
    messages.emplace_back(std::move(str));
  } else {
    std::cout << str;
  }

  ```


  On the other hand, the following code does produce a warning:

  ``` cpp
  for (int i = 0; i < 10; ++i) {
    std::cout << str;
    messages.emplace_back(std::move(str));
  }

  ```


  (The use-after-move happens on the second iteration of the loop.)

  In some cases, the check may not be able to detect that two branches are mutually exclusive. For example (assuming that i is an int):

  ``` cpp
  if (i == 1) {
    messages.emplace_back(std::move(str));
  }
  if (i == 2) {
    std::cout << str;
  }

  ```


  In this case, the check will erroneously produce a warning, even though it is not possible for both the move and the use to be executed.

  An erroneous warning can be silenced by reinitializing the object after the move:

  ``` cpp
  if (i == 1) {
    messages.emplace_back(std::move(str));
    str = "";
  }
  if (i == 2) {
    std::cout << str;
  }

  ```


  Subsections below explain more precisely what exactly the check considers to be a move, use, and reinitialization.

  ##### Unsequenced moves, uses, and reinitializations

  In many cases, C++ does not make any guarantees about the order in which sub-expressions of a statement are evaluated. This means that in code like the following, it is not guaranteed whether the use will happen before or after the move:

  ``` cpp
  void f(int i, std::vector<int> v);
  std::vector<int> v = { 1, 2, 3 };
  f(v[1], std::move(v));

  ```


  In this kind of situation, the check will note that the use and move are unsequenced.

  The check will also take sequencing rules into account when reinitializations occur in the same statement as moves or uses. A reinitialization is only considered to reinitialize a variable if it is guaranteed to be evaluated after the move and before the use.

  ##### Move

  The check currently only considers calls of std::move on local variables or function parameters. It does not check moves of member variables or global variables.

  Any call of std::move on a variable is considered to cause a move of that variable, even if the result of std::move is not passed to an rvalue reference parameter.

  This means that the check will flag a use-after-move even on a type that does not define a move constructor or move assignment operator. This is intentional. Developers may use std::move on such a type in the expectation that the type will add move semantics in the future. If such a std::move has the potential to cause a use-after-move, we want to warn about it even if the type does not implement move semantics yet.

  Furthermore, if the result of std::move _is_ passed to an rvalue reference parameter, this will always be considered to cause a move, even if the function that consumes this parameter does not move from it, or if it does so only conditionally. For example, in the following situation, the check will assume that a move always takes place:

  ``` cpp
  std::vector<std::string> messages;
  void f(std::string &&str) {
    // Only remember the message if it isn't empty.
    if (!str.empty()) {
      messages.emplace_back(std::move(str));
    }
  }
  std::string str = "";
  f(std::move(str));

  ```


  The check will assume that the last line causes a move, even though, in this particular case, it does not. Again, this is intentional.

  When analyzing the order in which moves, uses and reinitializations happen (see section [Unsequenced moves, uses, and reinitializations](\#unsequenced-moves-uses-and-reinitializations)), the move is assumed to occur in whichever function the result of the std::move is passed to.

  ##### Use

  Any occurrence of the moved variable that is not a reinitialization (see below) is considered to be a use.

  An exception to this are objects of type std::unique_ptr, std::shared_ptr and std::weak_ptr, which have defined move behavior (objects of these classes are guaranteed to be empty after they have been moved from). Therefore, an object of these classes will only be considered to be used if it is dereferenced, i.e. if operator*, operator-> or operator[] (in the case of std::unique_ptr<T []>) is called on it.

  If multiple uses occur after a move, only the first of these is flagged.

  ##### Reinitialization

  The check considers a variable to be reinitialized in the following cases:

    * The variable occurs on the left-hand side of an assignment.
    * The variable is passed to a function as a non-const pointer or non-const lvalue reference. (It is assumed that the variable may be an out-parameter for the function.)
    * clear() or assign() is called on the variable and the variable is of one of the standard container types basic_string, vector, deque, forward_list, list, set, map, multiset, multimap, unordered_set, unordered_map, unordered_multiset, unordered_multimap.
    * reset() is called on the variable and the variable is of type std::unique_ptr, std::shared_ptr or std::weak_ptr.
    * A member function marked with the [[clang::reinitializes]] attribute is called on the variable.



  If the variable in question is a struct and an individual member variable of that struct is written to, the check does not consider this to be a reinitialization – even if, eventually, all member variables of the struct are written to. For example:

  ``` cpp
  struct S {
    std::string str;
    int i;
  };
  S s = { "Hello, world!\n", 42 };
  S s_other = std::move(s);
  s.str = "Lorem ipsum";
  s.i = 99;

  ```


  The check will not consider s to be reinitialized after the last line; instead, the line that assigns to s.str will be flagged as a use-after-move. This is intentional as this pattern of reinitializing a struct is error-prone. For example, if an additional member variable is added to S, it is easy to forget to add the reinitialization for this additional member. Instead, it is safer to assign to the entire struct in one go, and this will also avoid the use-after-move warning.

  (Clang-Tidy original name: bugprone-use-after-move)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_UC
### Default
#### OriginalId=bugprone-undelegated-constructor
#### Enabled=true
#### Warning=true
#### DisplayName=Undelegated Constructor
#### HelpText
  Finds creation of temporary objects in constructors that look like a function call to another constructor of the same class.

  The user most likely meant to use a delegating constructor or base class initializer.

  (Clang-Tidy original name: bugprone-undelegated-constructor)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_UMM
### Default
#### OriginalId=bugprone-undefined-memory-manipulation
#### Enabled=true
#### Warning=true
#### DisplayName=Undefined Memory Manipulation
#### HelpText
  Finds calls of memory manipulation functions memset(), memcpy() and memmove() on not TriviallyCopyable objects resulting in undefined behavior.

  (Clang-Tidy original name: bugprone-undefined-memory-manipulation)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_UR
### Default
#### OriginalId=bugprone-unused-raii
#### Enabled=true
#### Warning=true
#### DisplayName=Unused Raii
#### HelpText
  Finds temporaries that look like RAII objects.

  The canonical example for this is a scoped lock.

  ``` cpp
  {
    scoped_lock(&global_mutex);
    critical_section();
  }

  ```


  The destructor of the scoped_lock is called before the critical_section is entered, leaving it unprotected.

  We apply a number of heuristics to reduce the false positive count of this check:

    * Ignore code expanded from macros. Testing frameworks make heavy use of this.
    * Ignore types with trivial destructors. They are very unlikely to be RAII objects and there’s no difference when they are deleted.
    * Ignore objects at the end of a compound statement (doesn’t change behavior).
    * Ignore objects returned from a call.



  (Clang-Tidy original name: bugprone-unused-raii)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_URV
### Default
#### OriginalId=bugprone-unused-return-value
#### Enabled=true
#### Warning=true
#### DisplayName=Unused Return Value
#### HelpText
  Warns on unused function return values. The checked functions can be configured.

  ##### Options

  CheckedFunctions     

  Semicolon-separated list of functions to check. Defaults to ::std::async;::std::launder;::std::remove;::std::remove_if;::std::unique;::std::unique_ptr::release;::std::basic_string::empty;::std::vector::empty. This means that the calls to following functions are checked by default:

    * std::async(). Not using the return value makes the call synchronous.
    * std::launder(). Not using the return value usually means that the function interface was misunderstood by the programmer. Only the returned pointer is “laundered”, not the argument.
    * std::remove(), std::remove_if() and std::unique(). The returned iterator indicates the boundary between elements to keep and elements to be removed. Not using the return value means that the information about which elements to remove is lost.
    * std::unique_ptr::release(). Not using the return value can lead to resource leaks if the same pointer isn’t stored anywhere else. Often, ignoring the release() return value indicates that the programmer confused the function with reset().
    * std::basic_string::empty() and std::vector::empty(). Not using the return value often indicates that the programmer confused the function with clear().



  (Clang-Tidy original name: bugprone-unused-return-value)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_USA
### Default
#### OriginalId=bugprone-unhandled-self-assignment
#### Enabled=true
#### Warning=true
#### DisplayName=Unhandled Self Assignment
#### HelpText
  cert-oop54-cpp redirects here as an alias for this check. For the CERT alias, the WarnOnlyIfThisHasSuspiciousField option is set to false.

  Finds user-defined copy assignment operators which do not protect the code against self-assignment either by checking self-assignment explicitly or using the copy-and-swap or the copy-and-move method.

  By default, this check searches only those classes which have any pointer or C array field to avoid false positives. In case of a pointer or a C array, it’s likely that self-copy assignment breaks the object if the copy assignment operator was not written with care.

  See also: [OOP54-CPP. Gracefully handle self-copy assignment](https://wiki.sei.cmu.edu/confluence/display/cplusplus/OOP54-CPP.+Gracefully+handle+self-copy+assignment)

  A copy assignment operator must prevent that self-copy assignment ruins the object state. A typical use case is when the class has a pointer field and the copy assignment operator first releases the pointed object and then tries to assign it:

  ``` cpp
  class T {
  int* p;

  public:
    T(const T &rhs) : p(rhs.p ? new int(*rhs.p) : nullptr) {}
    ~T() { delete p; }

    // ...

    T& operator=(const T &rhs) {
      delete p;
      p = new int(*rhs.p);
      return *this;
    }
  };

  ```


  There are two common C++ patterns to avoid this problem. The first is the self-assignment check:

  ``` cpp
  class T {
  int* p;

  public:
    T(const T &rhs) : p(rhs.p ? new int(*rhs.p) : nullptr) {}
    ~T() { delete p; }

    // ...

    T& operator=(const T &rhs) {
      if(this == &rhs)
        return *this;

      delete p;
      p = new int(*rhs.p);
      return *this;
    }
  };

  ```


  The second one is the copy-and-swap method when we create a temporary copy (using the copy constructor) and then swap this temporary object with this:

  ``` cpp
  class T {
  int* p;

  public:
    T(const T &rhs) : p(rhs.p ? new int(*rhs.p) : nullptr) {}
    ~T() { delete p; }

    // ...

    void swap(T &rhs) {
      using std::swap;
      swap(p, rhs.p);
    }

    T& operator=(const T &rhs) {
      T(rhs).swap(*this);
      return *this;
    }
  };

  ```


  There is a third pattern which is less common. Let’s call it the copy-and-move method when we create a temporary copy (using the copy constructor) and then move this temporary object into this (needs a move assignment operator):

  ``` cpp
  class T {
  int* p;

  public:
    T(const T &rhs) : p(rhs.p ? new int(*rhs.p) : nullptr) {}
    ~T() { delete p; }

    // ...

    T& operator=(const T &rhs) {
      T t = rhs;
      *this = std::move(t);
      return *this;
    }

    T& operator=(T &&rhs) {
      p = rhs.p;
      rhs.p = nullptr;
      return *this;
    }
  };

  ```


  WarnOnlyIfThisHasSuspiciousField     

  When true, the check will warn only if the container class of the copy assignment operator has any suspicious fields (pointer or C array). This option is set to true by default.

  (Clang-Tidy original name: bugprone-unhandled-self-assignment)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_BUG_VNM
### Default
#### OriginalId=bugprone-virtual-near-miss
#### Enabled=true
#### Warning=true
#### DisplayName=Virtual Near Miss
#### HelpText
  Warn if a function is a near miss (ie. the name is very similar and the function signature is the same) to a virtual function from a base class.

  Example:

  ``` cpp
  struct Base {
    virtual void func();
  };

  struct Derived : Base {
    virtual funk();
    // warning: 'Derived::funk' has a similar name and the same signature as virtual method 'Base::func'; did you mean to override it?
  };

  ```


  (Clang-Tidy original name: bugprone-virtual-near-miss)

#### Tags
- /general/Bugprone
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CON_MU
### Default
#### OriginalId=concurrency-mt-unsafe
#### Enabled=true
#### Warning=true
#### DisplayName=Mt Unsafe
#### HelpText
  Checks for some thread-unsafe functions against a black list of known-to-be-unsafe functions. Usually they access static variables without synchronization (e.g. gmtime(3)) or utilize signals in a racy way. The set of functions to check is specified with the FunctionSet option.

  Note that using some thread-unsafe functions may be still valid in concurrent programming if only a single thread is used (e.g. setenv(3)), however, some functions may track a state in global variables which would be clobbered by subsequent (non-parallel, but concurrent) calls to a related function. E.g. the following code suffers from unprotected accesses to a global state:

  ``` cpp
  // getnetent(3) maintains global state with DB connection, etc.
  // If a concurrent green thread calls getnetent(3), the global state is corrupted.
  netent = getnetent();
  yield();
  netent = getnetent();

  ```


  Examples:

  ``` cpp
  tm = gmtime(timep); // uses a global buffer

  sleep(1); // implementation may use SIGALRM

  ```


  FunctionSet     

  Specifies which functions in libc should be considered thread-safe, possible values are posix, glibc, or any.

  posix means POSIX defined thread-unsafe functions. POSIX.1-2001 in “2.9.1 Thread-Safety” defines that all functions specified in the standard are thread-safe except a predefined list of thread-unsafe functions.

  Glibc defines some of them as thread-safe (e.g. dirname(3)), but adds non-POSIX thread-unsafe ones (e.g. getopt_long(3)). Glibc’s list is compiled from GNU web documentation with a search for MT-Safe tag: <https://www.gnu.org/software/libc/manual/html_node/POSIX-Safety-Concepts.html>

  If you want to identify thread-unsafe API for at least one libc or unsure which libc will be used, use any (default).

  (Clang-Tidy original name: concurrency-mt-unsafe)

#### Tags
- /general/Concurrency
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CPP_ACA
### Default
#### OriginalId=cppcoreguidelines-avoid-c-arrays
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid C Arrays
#### HelpText
  The cppcoreguidelines-avoid-c-arrays check is an alias, please see [modernize-avoid-c-arrays](modernize-avoid-c-arrays.html) for more information.

  (Clang-Tidy original name: cppcoreguidelines-avoid-c-arrays)

#### Tags
- /general/C++ Core Guidelines
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CPP_AG
### Default
#### OriginalId=cppcoreguidelines-avoid-goto
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Goto
#### HelpText
  The usage of goto for control flow is error prone and should be replaced with looping constructs. Only forward jumps in nested loops are accepted.

  This check implements [ES.76](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#es76-avoid-goto) from the CppCoreGuidelines and [6.3.1 from High Integrity C++](http://www.codingstandard.com/rule/6-3-1-ensure-that-the-labels-for-a-jump-statement-or-a-switch-condition-appear-later-in-the-same-or-an-enclosing-block/).

  For more information on why to avoid programming with goto you can read the famous paper [A Case against the GO TO Statement.](https://www.cs.utexas.edu/users/EWD/ewd02xx/EWD215.PDF).

  The check diagnoses goto for backward jumps in every language mode. These should be replaced with C/C++ looping constructs.

  ``` cpp
  // Bad, handwritten for loop.
  int i = 0;
  // Jump label for the loop
  loop_start:
  do_some_operation();

  if (i < 100) {
    ++i;
    goto loop_start;
  }

  // Better
  for(int i = 0; i < 100; ++i)
    do_some_operation();

  ```


  Modern C++ needs goto only to jump out of nested loops.

  ``` cpp
  for(int i = 0; i < 100; ++i) {
    for(int j = 0; j < 100; ++j) {
      if (i * j > 500)
        goto early_exit;
    }
  }

  early_exit:
  some_operation();

  ```


  All other uses of goto are diagnosed in C++.

  (Clang-Tidy original name: cppcoreguidelines-avoid-goto)

#### Tags
- /general/C++ Core Guidelines
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CPP_AMN
### Default
#### OriginalId=cppcoreguidelines-avoid-magic-numbers
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Magic Numbers
#### HelpText
  The cppcoreguidelines-avoid-magic-numbers check is an alias, please see [readability-magic-numbers](readability-magic-numbers.html) for more information.

  (Clang-Tidy original name: cppcoreguidelines-avoid-magic-numbers)

#### Tags
- /general/C++ Core Guidelines
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CPP_ANCGV
### Default
#### OriginalId=cppcoreguidelines-avoid-non-const-global-variables
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Non Const Global Variables
#### HelpText
  Finds non-const global variables as described in [I.2 of C++ Core Guidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#Ri-global) . As [R.6 of C++ Core Guidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#Rr-global) is a duplicate of rule I.2 it also covers that rule.

  ``` cpp
  char a;  // Warns!
  const char b =  0;

  namespace some_namespace
  {
      char c;  // Warns!
      const char d = 0;
  }

  char * c_ptr1 = &some_namespace::c;  // Warns!
  char *const c_const_ptr = &some_namespace::c;  // Warns!
  char & c_reference = some_namespace::c;  // Warns!

  class Foo  // No Warnings inside Foo, only namespace scope is covered
  {
  public:
      char e = 0;
      const char f = 0;
  protected:
      char g = 0;
  private:
      char h = 0;
  };

  ```


  Variables: a, c, c_ptr1, c_ptr2, c_const_ptr and c_reference, will all generate warnings since they are either: a globally accessible variable and non-const, a pointer or reference providing global access to non-const data or both.

  (Clang-Tidy original name: cppcoreguidelines-avoid-non-const-global-variables)

#### Tags
- /general/C++ Core Guidelines
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CPP_CCAS
### Default
#### OriginalId=cppcoreguidelines-c-copy-assignment-signature
#### Enabled=true
#### Warning=true
#### DisplayName=C Copy Assignment Signature
#### HelpText
  The cppcoreguidelines-c-copy-assignment-signature check is an alias, please see [misc-unconventional-assign-operator](misc-unconventional-assign-operator.html) for more information.

  (Clang-Tidy original name: cppcoreguidelines-c-copy-assignment-signature)

#### Tags
- /general/C++ Core Guidelines
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CPP_EVF
### Default
#### OriginalId=cppcoreguidelines-explicit-virtual-functions
#### Enabled=true
#### Warning=true
#### DisplayName=Explicit Virtual Functions
#### HelpText
  The cppcoreguidelines-explicit-virtual-functions check is an alias, please see [modernize-use-override](modernize-use-override.html) for more information.

  (Clang-Tidy original name: cppcoreguidelines-explicit-virtual-functions)

#### Tags
- /general/C++ Core Guidelines
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CPP_IGI
### Default
#### OriginalId=cppcoreguidelines-interfaces-global-init
#### Enabled=true
#### Warning=true
#### DisplayName=Interfaces Global Init
#### HelpText
  This check flags initializers of globals that access extern objects, and therefore can lead to order-of-initialization problems.

  This rule is part of the “Interfaces” profile of the C++ Core Guidelines, see <https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#Ri-global-init>

  Note that currently this does not flag calls to non-constexpr functions, and therefore globals could still be accessed from functions themselves.

  (Clang-Tidy original name: cppcoreguidelines-interfaces-global-init)

#### Tags
- /general/C++ Core Guidelines
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CPP_IV
### Default
#### OriginalId=cppcoreguidelines-init-variables
#### Enabled=true
#### Warning=true
#### DisplayName=Init Variables
#### HelpText
  Checks whether there are local variables that are declared without an initial value. These may lead to unexpected behaviour if there is a code path that reads the variable before assigning to it.

  Only integers, booleans, floats, doubles and pointers are checked. The fix option initializes all detected values with the value of zero. An exception is float and double types, which are initialized to NaN.

  As an example a function that looks like this:

  ``` cpp
  void function() {
    int x;
    char *txt;
    double d;

    // Rest of the function.
  }

  ```


  Would be rewritten to look like this:

  ``` cpp
  #include <math.h>

  void function() {
    int x = 0;
    char *txt = nullptr;
    double d = NAN;

    // Rest of the function.
  }

  ```


  ##### Options

  IncludeStyle     

  A string specifying which include-style is used, llvm or google. Default is llvm.

  MathHeader     

  A string specifying the header to include to get the definition of NAN. Default is <math.h>.

  (Clang-Tidy original name: cppcoreguidelines-init-variables)

#### Tags
- /general/C++ Core Guidelines
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CPP_MU
### Default
#### OriginalId=cppcoreguidelines-macro-usage
#### Enabled=true
#### Warning=true
#### DisplayName=Macro Usage
#### HelpText
  Finds macro usage that is considered problematic because better language constructs exist for the task.

  The relevant sections in the C++ Core Guidelines are [Enum.1](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#enum1-prefer-enumerations-over-macros), [ES.30](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#es30-dont-use-macros-for-program-text-manipulation), [ES.31](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#es31-dont-use-macros-for-constants-or-functions) and [ES.33](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#es33-if-you-must-use-macros-give-them-unique-names).

  ##### Options

  AllowedRegexp     

  A regular expression to filter allowed macros. For example DEBUG*|LIBTORRENT*|TORRENT*|UNI* could be applied to filter libtorrent. Default value is ^DEBUG_*.

  CheckCapsOnly     

  Boolean flag to warn on all macros except those with CAPS_ONLY names. This option is intended to ease introduction of this check into older code bases. Default value is false.

  IgnoreCommandLineMacros     

  Boolean flag to toggle ignoring command-line-defined macros. Default value is true.

  (Clang-Tidy original name: cppcoreguidelines-macro-usage)

#### Tags
- /general/C++ Core Guidelines
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CPP_NC
### Default
#### OriginalId=cppcoreguidelines-narrowing-conversions
#### Enabled=true
#### Warning=true
#### DisplayName=Narrowing Conversions
#### HelpText
  Checks for silent narrowing conversions, e.g: int i = 0; i += 0.1;. While the issue is obvious in this former example, it might not be so in the following: void MyClass::f(double d) { int_member_ += d; }.

  This rule is part of the “Expressions and statements” profile of the C++ Core Guidelines, corresponding to rule ES.46. See

  <https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#es46-avoid-lossy-narrowing-truncating-arithmetic-conversions>.

  We enforce only part of the guideline, more specifically, we flag narrowing conversions from:     

    * an integer to a narrower integer (e.g. char to unsigned char),
    * an integer to a narrower floating-point (e.g. uint64_t to float),
    * a floating-point to an integer (e.g. double to int),
    * a floating-point to a narrower floating-point (e.g. double to float) if WarnOnFloatingPointNarrowingConversion Option is set.


  This check will flag:     

    * All narrowing conversions that are not marked by an explicit cast (c-style or static_cast). For example: int i = 0; i += 0.1;, void f(int); f(0.1);,
    * All applications of binary operators with a narrowing conversions. For example: int i; i+= 0.1;.



  ##### Options

  WarnOnFloatingPointNarrowingConversion     

  When true, the check will warn on narrowing floating point conversion (e.g. double to float). true by default.

  PedanticMode     

  When true, the check will warn on assigning a floating point constant to an integer value even if the floating point value is exactly representable in the destination type (e.g. int i = 1.0;). false by default.

  ##### FAQ

    * What does “narrowing conversion from ‘int’ to ‘float’” mean?



  An IEEE754 Floating Point number can represent all integer values in the range [-2^PrecisionBits, 2^PrecisionBits] where PrecisionBits is the number of bits in the mantissa.

  For float this would be [-2^23, 2^23], where int can represent values in the range [-2^31, 2^31-1].

    * What does “implementation-defined” mean?



  You may have encountered messages like “narrowing conversion from ‘unsigned int’ to signed type ‘int’ is implementation-defined”. The C/C++ standard does not mandate two’s complement for signed integers, and so the compiler is free to define what the semantics are for converting an unsigned integer to signed integer. Clang’s implementation uses the two’s complement format.

  (Clang-Tidy original name: cppcoreguidelines-narrowing-conversions)

#### Tags
- /general/C++ Core Guidelines
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CPP_NM
### Default
#### OriginalId=cppcoreguidelines-no-malloc
#### Enabled=true
#### Warning=true
#### DisplayName=No Malloc
#### HelpText
  This check handles C-Style memory management using malloc(), realloc(), calloc() and free(). It warns about its use and tries to suggest the use of an appropriate RAII object. Furthermore, it can be configured to check against a user-specified list of functions that are used for memory management (e.g. posix_memalign()). See [C++ Core Guidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#Rr-mallocfree).

  There is no attempt made to provide fix-it hints, since manual resource management isn’t easily transformed automatically into RAII.

  ``` cpp
  // Warns each of the following lines.
  // Containers like std::vector or std::string should be used.
  char* some_string = (char*) malloc(sizeof(char) * 20);
  char* some_string = (char*) realloc(sizeof(char) * 30);
  free(some_string);

  int* int_array = (int*) calloc(30, sizeof(int));

  // Rather use a smartpointer or stack variable.
  struct some_struct* s = (struct some_struct*) malloc(sizeof(struct some_struct));

  ```


  ##### Options

  Allocations     

  Semicolon-separated list of fully qualified names of memory allocation functions. Defaults to ::malloc;::calloc.

  Deallocations     

  Semicolon-separated list of fully qualified names of memory allocation functions. Defaults to ::free.

  Reallocations     

  Semicolon-separated list of fully qualified names of memory allocation functions. Defaults to ::realloc.

  (Clang-Tidy original name: cppcoreguidelines-no-malloc)

#### Tags
- /general/C++ Core Guidelines
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CPP_NPMVIC
### Default
#### OriginalId=cppcoreguidelines-non-private-member-variables-in-classes
#### Enabled=true
#### Warning=true
#### DisplayName=Non Private Member Variables In Classes
#### HelpText
  The cppcoreguidelines-non-private-member-variables-in-classes check is an alias, please see [misc-non-private-member-variables-in-classes](misc-non-private-member-variables-in-classes.html) for more information.

  (Clang-Tidy original name: cppcoreguidelines-non-private-member-variables-in-classes)

#### Tags
- /general/C++ Core Guidelines
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CPP_OM
### Default
#### OriginalId=cppcoreguidelines-owning-memory
#### Enabled=true
#### Warning=true
#### DisplayName=Owning Memory
#### HelpText
  This check implements the type-based semantics of gsl::owner<T*>, which allows static analysis on code, that uses raw pointers to handle resources like dynamic memory, but won’t introduce RAII concepts.

  The relevant sections in the [C++ Core Guidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md) are I.11, C.33, R.3 and GSL.Views The definition of a gsl::owner<T*> is straight forward

  ``` cpp
  namespace gsl { template <typename T> owner = T; }

  ```


  It is therefore simple to introduce the owner even without using an implementation of the [Guideline Support Library](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#gsl-guideline-support-library).

  All checks are purely type based and not (yet) flow sensitive.

  The following examples will demonstrate the correct and incorrect initializations of owners, assignment is handled the same way. Note that both new and malloc()-like resource functions are considered to produce resources.

  ``` cpp
  // Creating an owner with factory functions is checked.
  gsl::owner<int*> function_that_returns_owner() { return gsl::owner<int*>(new int(42)); }

  // Dynamic memory must be assigned to an owner
  int* Something = new int(42); // BAD, will be caught
  gsl::owner<int*> Owner = new int(42); // Good
  gsl::owner<int*> Owner = new int[42]; // Good as well

  // Returned owner must be assigned to an owner
  int* Something = function_that_returns_owner(); // Bad, factory function
  gsl::owner<int*> Owner = function_that_returns_owner(); // Good, result lands in owner

  // Something not a resource or owner should not be assigned to owners
  int Stack = 42;
  gsl::owner<int*> Owned = &Stack; // Bad, not a resource assigned

  ```


  In the case of dynamic memory as resource, only gsl::owner<T*> variables are allowed to be deleted.

  ``` cpp
  // Example Bad, non-owner as resource handle, will be caught.
  int* NonOwner = new int(42); // First warning here, since new must land in an owner
  delete NonOwner; // Second warning here, since only owners are allowed to be deleted

  // Example Good, Ownership correctly stated
  gsl::owner<int*> Owner = new int(42); // Good
  delete Owner; // Good as well, statically enforced, that only owners get deleted

  ```


  The check will furthermore ensure, that functions, that expect a gsl::owner<T*> as argument get called with either a gsl::owner<T*> or a newly created resource.

  ``` cpp
  void expects_owner(gsl::owner<int*> o) { delete o; }

  // Bad Code
  int NonOwner = 42;
  expects_owner(&NonOwner); // Bad, will get caught

  // Good Code
  gsl::owner<int*> Owner = new int(42);
  expects_owner(Owner); // Good
  expects_owner(new int(42)); // Good as well, recognized created resource

  // Port legacy code for better resource-safety
  gsl::owner<FILE*> File = fopen("my_file.txt", "rw+");
  FILE* BadFile = fopen("another_file.txt", "w"); // Bad, warned

  // ... use the file

  fclose(File); // Ok, File is annotated as 'owner<>'
  fclose(BadFile); // BadFile is not an 'owner<>', will be warned

  ```


  ##### Options

  LegacyResourceProducers     

  Semicolon-separated list of fully qualified names of legacy functions that create resources but cannot introduce gsl::owner<>. Defaults to ::malloc;::aligned_alloc;::realloc;::calloc;::fopen;::freopen;::tmpfile.

  LegacyResourceConsumers     

  Semicolon-separated list of fully qualified names of legacy functions expecting resource owners as pointer arguments but cannot introduce gsl::owner<>. Defaults to ::free;::realloc;::freopen;::fclose.

  ##### Limitations

  Using gsl::owner<T*> in a typedef or alias is not handled correctly.

  ``` cpp
  using heap_int = gsl::owner<int*>;
  heap_int allocated = new int(42); // False positive!

  ```


  The gsl::owner<T*> is declared as a templated type alias. In template functions and classes, like in the example below, the information of the type aliases gets lost. Therefore using gsl::owner<T*> in a heavy templated code base might lead to false positives.

  Known code constructs that do not get diagnosed correctly are:

    * std::exchange
    * std::vector<gsl::owner<T*>>



  ``` cpp
  // This template function works as expected. Type information doesn't get lost.
  template <typename T>
  void delete_owner(gsl::owner<T*> owned_object) {
    delete owned_object; // Everything alright
  }

  gsl::owner<int*> function_that_returns_owner() { return gsl::owner<int*>(new int(42)); }

  // Type deduction does not work for auto variables.
  // This is caught by the check and will be noted accordingly.
  auto OwnedObject = function_that_returns_owner(); // Type of OwnedObject will be int*

  // Problematic function template that looses the typeinformation on owner
  template <typename T>
  void bad_template_function(T some_object) {
    // This line will trigger the warning, that a non-owner is assigned to an owner
    gsl::owner<T*> new_owner = some_object;
  }

  // Calling the function with an owner still yields a false positive.
  bad_template_function(gsl::owner<int*>(new int(42)));


  // The same issue occurs with templated classes like the following.
  template <typename T>
  class OwnedValue {
  public:
    const T getValue() const { return _val; }
  private:
    T _val;
  };

  // Code, that yields a false positive.
  OwnedValue<gsl::owner<int*>> Owner(new int(42)); // Type deduction yield T -> int *
  // False positive, getValue returns int* and not gsl::owner<int*>
  gsl::owner<int*> OwnedInt = Owner.getValue();

  ```


  Another limitation of the current implementation is only the type based checking. Suppose you have code like the following:

  ``` cpp
  // Two owners with assigned resources
  gsl::owner<int*> Owner1 = new int(42);
  gsl::owner<int*> Owner2 = new int(42);

  Owner2 = Owner1; // Conceptual Leak of initial resource of Owner2!
  Owner1 = nullptr;

  ```


  The semantic of a gsl::owner<T*> is mostly like a std::unique_ptr<T>, therefore assignment of two gsl::owner<T*> is considered a move, which requires that the resource Owner2 must have been released before the assignment. This kind of condition could be caught in later improvements of this check with flowsensitive analysis. Currently, the Clang Static Analyzer catches this bug for dynamic memory, but not for general types of resources.

  (Clang-Tidy original name: cppcoreguidelines-owning-memory)

#### Tags
- /general/C++ Core Guidelines
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CPP_PBATPD
### Default
#### OriginalId=cppcoreguidelines-pro-bounds-array-to-pointer-decay
#### Enabled=true
#### Warning=true
#### DisplayName=Pro Bounds Array To Pointer Decay
#### HelpText
  This check flags all array to pointer decays.

  Pointers should not be used as arrays. span<T> is a bounds-checked, safe alternative to using pointers to access arrays.

  This rule is part of the “Bounds safety” profile of the C++ Core Guidelines, see <https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#Pro-bounds-decay>.

  (Clang-Tidy original name: cppcoreguidelines-pro-bounds-array-to-pointer-decay)

#### Tags
- /general/C++ Core Guidelines
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CPP_PBCAI
### Default
#### OriginalId=cppcoreguidelines-pro-bounds-constant-array-index
#### Enabled=true
#### Warning=true
#### DisplayName=Pro Bounds Constant Array Index
#### HelpText
  This check flags all array subscript expressions on static arrays and std::arrays that either do not have a constant integer expression index or are out of bounds (for std::array). For out-of-bounds checking of static arrays, see the -Warray-bounds Clang diagnostic.

  This rule is part of the “Bounds safety” profile of the C++ Core Guidelines, see <https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#Pro-bounds-arrayindex>.

  ##### Options

  GslHeader     

  The check can generate fixes after this option has been set to the name of the include file that contains gsl::at(), e.g. “gsl/gsl.h”.

  IncludeStyle     

  A string specifying which include-style is used, llvm or google. Default is llvm.

  (Clang-Tidy original name: cppcoreguidelines-pro-bounds-constant-array-index)

#### Tags
- /general/C++ Core Guidelines
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CPP_PBPA
### Default
#### OriginalId=cppcoreguidelines-pro-bounds-pointer-arithmetic
#### Enabled=true
#### Warning=true
#### DisplayName=Pro Bounds Pointer Arithmetic
#### HelpText
  This check flags all usage of pointer arithmetic, because it could lead to an invalid pointer. Subtraction of two pointers is not flagged by this check.

  Pointers should only refer to single objects, and pointer arithmetic is fragile and easy to get wrong. span<T> is a bounds-checked, safe type for accessing arrays of data.

  This rule is part of the “Bounds safety” profile of the C++ Core Guidelines, see <https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#Pro-bounds-arithmetic>.

  (Clang-Tidy original name: cppcoreguidelines-pro-bounds-pointer-arithmetic)

#### Tags
- /general/C++ Core Guidelines
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CPP_PMI
### Default
#### OriginalId=cppcoreguidelines-prefer-member-initializer
#### Enabled=true
#### Warning=true
#### DisplayName=Prefer Member Initializer
#### HelpText
  Finds member initializations in the constructor body which can be converted into member initializers of the constructor instead. This not only improves the readability of the code but also positively affects its performance. Class-member assignments inside a control statement or following the first control statement are ignored.

  This check implements [C.49](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#c49-prefer-initialization-to-assignment-in-constructors) from the CppCoreGuidelines.

  If the language version is C++ 11 or above, the constructor is the default constructor of the class, the field is not a bitfield (only in case of earlier language version than C++ 20), furthermore the assigned value is a literal, negated literal or enum constant then the preferred place of the initialization is at the class member declaration.

  This latter rule is [C.48](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#c48-prefer-in-class-initializers-to-member-initializers-in-constructors-for-constant-initializers) from CppCoreGuidelines.

  Please note, that this check does not enforce this latter rule for initializations already implemented as member initializers. For that purpose see check [modernize-use-default-member-init](modernize-use-default-member-init.html).

  ##### Example 1

  ``` cpp
  class C {
    int n;
    int m;
  public:
    C() {
      n = 1; // Literal in default constructor
      if (dice())
        return;
      m = 1;
    }
  };

  ```


  Here n can be initialized using a default member initializer, unlike m, as m’s initialization follows a control statement (if):

  ``` cpp
  class C {
    int n{1};
    int m;
  public:
    C() {
      if (dice())
        return;
      m = 1;
    }

  ```


  ##### Example 2

  ``` cpp
  class C {
    int n;
    int m;
  public:
    C(int nn, int mm) {
      n = nn; // Neither default constructor nor literal
      if (dice())
        return;
      m = mm;
    }
  };

  ```


  Here n can be initialized in the constructor initialization list, unlike m, as m’s initialization follows a control statement (if):

  ``` cpp
  C(int nn, int mm) : n(nn) {
    if (dice())
      return;
    m = mm;
  }

  ```


  UseAssignment     

  If this option is set to true (default is false), the check will initialize members with an assignment. In this case the fix of the first example looks like this:

  ``` cpp
  class C {
    int n = 1;
    int m;
  public:
    C() {
      if (dice())
        return;
      m = 1;
    }
  };

  ```


  (Clang-Tidy original name: cppcoreguidelines-prefer-member-initializer)

#### Tags
- /general/C++ Core Guidelines
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CPP_PTCC
### Default
#### OriginalId=cppcoreguidelines-pro-type-const-cast
#### Enabled=true
#### Warning=true
#### DisplayName=Pro Type Const Cast
#### HelpText
  This check flags all uses of const_cast in C++ code.

  Modifying a variable that was declared const is undefined behavior, even with const_cast.

  This rule is part of the “Type safety” profile of the C++ Core Guidelines, see <https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#Pro-type-constcast>.

  (Clang-Tidy original name: cppcoreguidelines-pro-type-const-cast)

#### Tags
- /general/C++ Core Guidelines
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CPP_PTCC2
### Default
#### OriginalId=cppcoreguidelines-pro-type-cstyle-cast
#### Enabled=true
#### Warning=true
#### DisplayName=Pro Type Cstyle Cast
#### HelpText
  This check flags all use of C-style casts that perform a static_cast downcast, const_cast, or reinterpret_cast.

  Use of these casts can violate type safety and cause the program to access a variable that is actually of type X to be accessed as if it were of an unrelated type Z. Note that a C-style (T)expression cast means to perform the first of the following that is possible: a const_cast, a static_cast, a static_cast followed by a const_cast, a reinterpret_cast, or a reinterpret_cast followed by a const_cast. This rule bans (T)expression only when used to perform an unsafe cast.

  This rule is part of the “Type safety” profile of the C++ Core Guidelines, see <https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#Pro-type-cstylecast>.

  (Clang-Tidy original name: cppcoreguidelines-pro-type-cstyle-cast)

#### Tags
- /general/C++ Core Guidelines
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CPP_PTMI
### Default
#### OriginalId=cppcoreguidelines-pro-type-member-init
#### Enabled=true
#### Warning=true
#### DisplayName=Pro Type Member Init
#### HelpText
  The check flags user-defined constructor definitions that do not initialize all fields that would be left in an undefined state by default construction, e.g. builtins, pointers and record types without user-provided default constructors containing at least one such type. If these fields aren’t initialized, the constructor will leave some of the memory in an undefined state.

  For C++11 it suggests fixes to add in-class field initializers. For older versions it inserts the field initializers into the constructor initializer list. It will also initialize any direct base classes that need to be zeroed in the constructor initializer list.

  The check takes assignment of fields in the constructor body into account but generates false positives for fields initialized in methods invoked in the constructor body.

  The check also flags variables with automatic storage duration that have record types without a user-provided constructor and are not initialized. The suggested fix is to zero initialize the variable via {} for C++11 and beyond or = {} for older language versions.

  ##### Options

  IgnoreArrays     

  If set to true, the check will not warn about array members that are not zero-initialized during construction. For performance critical code, it may be important to not initialize fixed-size array members. Default is false.

  UseAssignment     

  If set to true, the check will provide fix-its with literal initializers ( int i = 0; ) instead of curly braces ( int i{}; ).

  This rule is part of the “Type safety” profile of the C++ Core Guidelines, corresponding to rule Type.6. See <https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#Pro-type-memberinit>.

  (Clang-Tidy original name: cppcoreguidelines-pro-type-member-init)

#### Tags
- /general/C++ Core Guidelines
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CPP_PTRC
### Default
#### OriginalId=cppcoreguidelines-pro-type-reinterpret-cast
#### Enabled=true
#### Warning=true
#### DisplayName=Pro Type Reinterpret Cast
#### HelpText
  This check flags all uses of reinterpret_cast in C++ code.

  Use of these casts can violate type safety and cause the program to access a variable that is actually of type X to be accessed as if it were of an unrelated type Z.

  This rule is part of the “Type safety” profile of the C++ Core Guidelines, see <https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#Pro-type-reinterpretcast>.

  (Clang-Tidy original name: cppcoreguidelines-pro-type-reinterpret-cast)

#### Tags
- /general/C++ Core Guidelines
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CPP_PTSCD
### Default
#### OriginalId=cppcoreguidelines-pro-type-static-cast-downcast
#### Enabled=true
#### Warning=true
#### DisplayName=Pro Type Static Cast Downcast
#### HelpText
  This check flags all usages of static_cast, where a base class is casted to a derived class. In those cases, a fix-it is provided to convert the cast to a dynamic_cast.

  Use of these casts can violate type safety and cause the program to access a variable that is actually of type X to be accessed as if it were of an unrelated type Z.

  This rule is part of the “Type safety” profile of the C++ Core Guidelines, see <https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#Pro-type-downcast>.

  (Clang-Tidy original name: cppcoreguidelines-pro-type-static-cast-downcast)

#### Tags
- /general/C++ Core Guidelines
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CPP_PTUA
### Default
#### OriginalId=cppcoreguidelines-pro-type-union-access
#### Enabled=true
#### Warning=true
#### DisplayName=Pro Type Union Access
#### HelpText
  This check flags all access to members of unions. Passing unions as a whole is not flagged.

  Reading from a union member assumes that member was the last one written, and writing to a union member assumes another member with a nontrivial destructor had its destructor called. This is fragile because it cannot generally be enforced to be safe in the language and so relies on programmer discipline to get it right.

  This rule is part of the “Type safety” profile of the C++ Core Guidelines, see <https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#Pro-type-unions>.

  (Clang-Tidy original name: cppcoreguidelines-pro-type-union-access)

#### Tags
- /general/C++ Core Guidelines
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CPP_PTV
### Default
#### OriginalId=cppcoreguidelines-pro-type-vararg
#### Enabled=true
#### Warning=true
#### DisplayName=Pro Type Vararg
#### HelpText
  This check flags all calls to c-style vararg functions and all use of va_arg.

  To allow for SFINAE use of vararg functions, a call is not flagged if a literal 0 is passed as the only vararg argument.

  Passing to varargs assumes the correct type will be read. This is fragile because it cannot generally be enforced to be safe in the language and so relies on programmer discipline to get it right.

  This rule is part of the “Type safety” profile of the C++ Core Guidelines, see <https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#Pro-type-varargs>.

  (Clang-Tidy original name: cppcoreguidelines-pro-type-vararg)

#### Tags
- /general/C++ Core Guidelines
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CPP_S
### Default
#### OriginalId=cppcoreguidelines-slicing
#### Enabled=true
#### Warning=true
#### DisplayName=Slicing
#### HelpText
  Flags slicing of member variables or vtable. Slicing happens when copying a derived object into a base object: the members of the derived object (both member variables and virtual member functions) will be discarded. This can be misleading especially for member function slicing, for example:

  ``` cpp
  struct B { int a; virtual int f(); };
  struct D : B { int b; int f() override; };

  void use(B b) {  // Missing reference, intended?
    b.f();  // Calls B::f.
  }

  D d;
  use(d);  // Slice.

  ```


  See the relevant C++ Core Guidelines sections for details: <https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#es63-dont-slice> <https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#c145-access-polymorphic-objects-through-pointers-and-references>

  (Clang-Tidy original name: cppcoreguidelines-slicing)

#### Tags
- /general/C++ Core Guidelines
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CPP_SMF
### Default
#### OriginalId=cppcoreguidelines-special-member-functions
#### Enabled=true
#### Warning=true
#### DisplayName=Special Member Functions
#### HelpText
  The check finds classes where some but not all of the special member functions are defined.

  By default the compiler defines a copy constructor, copy assignment operator, move constructor, move assignment operator and destructor. The default can be suppressed by explicit user-definitions. The relationship between which functions will be suppressed by definitions of other functions is complicated and it is advised that all five are defaulted or explicitly defined.

  Note that defining a function with = delete is considered to be a definition.

  This rule is part of the “Constructors, assignments, and destructors” profile of the C++ Core Guidelines, corresponding to rule C.21. See

  <https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md\#c21-if-you-define-or-delete-any-default-operation-define-or-delete-them-all>.

  ##### Options

  AllowSoleDefaultDtor     

  When set to true (default is false), this check doesn’t flag classes with a sole, explicitly defaulted destructor. An example for such a class is:

  ``` cpp
  struct A {
    virtual ~A() = default;
  };

  ```


  AllowMissingMoveFunctions     

  When set to true (default is false), this check doesn’t flag classes which define no move operations at all. It still flags classes which define only one of either move constructor or move assignment operator. With this option enabled, the following class won’t be flagged:

  ``` cpp
  struct A {
    A(const A&);
    A& operator=(const A&);
    ~A();
  };

  ```


  AllowMissingMoveFunctionsWhenCopyIsDeleted     

  When set to true (default is false), this check doesn’t flag classes which define deleted copy operations but don’t define move operations. This flags is related to Google C++ Style Guide <https://google.github.io/styleguide/cppguide.html\#Copyable_Movable_Types>. With this option enabled, the following class won’t be flagged:

  ``` cpp
  struct A {
    A(const A&) = delete;
    A& operator=(const A&) = delete;
    ~A();
  };

  ```


  (Clang-Tidy original name: cppcoreguidelines-special-member-functions)

#### Tags
- /general/C++ Core Guidelines
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CRT_CON36_C
### Default
#### OriginalId=cert-con36-c
#### Enabled=true
#### Warning=true
#### DisplayName=Con36 C
#### HelpText
  The cert-con36-c check is an alias, please see [bugprone-spuriously-wake-up-functions](bugprone-spuriously-wake-up-functions.html) for more information.

  (Clang-Tidy original name: cert-con36-c)

#### Tags
- /general/Cert
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CRT_CON54_CPP
### Default
#### OriginalId=cert-con54-cpp
#### Enabled=true
#### Warning=true
#### DisplayName=Con54 Cpp
#### HelpText
  The cert-con54-cpp check is an alias, please see [bugprone-spuriously-wake-up-functions](bugprone-spuriously-wake-up-functions.html) for more information.

  (Clang-Tidy original name: cert-con54-cpp)

#### Tags
- /general/Cert
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CRT_DCL03_C
### Default
#### OriginalId=cert-dcl03-c
#### Enabled=true
#### Warning=true
#### DisplayName=Dcl03 C
#### HelpText
  The cert-dcl03-c check is an alias, please see [misc-static-assert](misc-static-assert.html) for more information.

  (Clang-Tidy original name: cert-dcl03-c)

#### Tags
- /general/Cert
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CRT_DCL16_C
### Default
#### OriginalId=cert-dcl16-c
#### Enabled=true
#### Warning=true
#### DisplayName=Dcl16 C
#### HelpText
  The cert-dcl16-c check is an alias, please see [readability-uppercase-literal-suffix](readability-uppercase-literal-suffix.html) for more information.

  (Clang-Tidy original name: cert-dcl16-c)

#### Tags
- /general/Cert
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CRT_DCL21_CPP
### Default
#### OriginalId=cert-dcl21-cpp
#### Enabled=true
#### Warning=true
#### DisplayName=Dcl21 Cpp
#### HelpText
  This check flags postfix operator++ and operator-- declarations if the return type is not a const object. This also warns if the return type is a reference type.

  The object returned by a postfix increment or decrement operator is supposed to be a snapshot of the object’s value prior to modification. With such an implementation, any modifications made to the resulting object from calling operator++(int) would be modifying a temporary object. Thus, such an implementation of a postfix increment or decrement operator should instead return a const object, prohibiting accidental mutation of a temporary object. Similarly, it is unexpected for the postfix operator to return a reference to its previous state, and any subsequent modifications would be operating on a stale object.

  This check corresponds to the CERT C++ Coding Standard recommendation DCL21-CPP. Overloaded postfix increment and decrement operators should return a const object. However, all of the CERT recommendations have been removed from public view, and so their justification for the behavior of this check requires an account on their wiki to view.

  (Clang-Tidy original name: cert-dcl21-cpp)

#### Tags
- /general/Cert
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CRT_DCL37_C
### Default
#### OriginalId=cert-dcl37-c
#### Enabled=true
#### Warning=true
#### DisplayName=Dcl37 C
#### HelpText
  The cert-dcl37-c check is an alias, please see [bugprone-reserved-identifier](bugprone-reserved-identifier.html) for more information.

  (Clang-Tidy original name: cert-dcl37-c)

#### Tags
- /general/Cert
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CRT_DCL50_CPP
### Default
#### OriginalId=cert-dcl50-cpp
#### Enabled=true
#### Warning=true
#### DisplayName=Dcl50 Cpp
#### HelpText
  This check flags all function definitions (but not declarations) of C-style variadic functions.

  This check corresponds to the CERT C++ Coding Standard rule [DCL50-CPP. Do not define a C-style variadic function](https://www.securecoding.cert.org/confluence/display/cplusplus/DCL50-CPP.+Do+not+define+a+C-style+variadic+function).

  (Clang-Tidy original name: cert-dcl50-cpp)

#### Tags
- /general/Cert
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CRT_DCL51_CPP
### Default
#### OriginalId=cert-dcl51-cpp
#### Enabled=true
#### Warning=true
#### DisplayName=Dcl51 Cpp
#### HelpText
  The cert-dcl51-cpp check is an alias, please see [bugprone-reserved-identifier](bugprone-reserved-identifier.html) for more information.

  (Clang-Tidy original name: cert-dcl51-cpp)

#### Tags
- /general/Cert
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CRT_DCL54_CPP
### Default
#### OriginalId=cert-dcl54-cpp
#### Enabled=true
#### Warning=true
#### DisplayName=Dcl54 Cpp
#### HelpText
  The cert-dcl54-cpp check is an alias, please see [misc-new-delete-overloads](misc-new-delete-overloads.html) for more information.

  (Clang-Tidy original name: cert-dcl54-cpp)

#### Tags
- /general/Cert
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CRT_DCL58_CPP
### Default
#### OriginalId=cert-dcl58-cpp
#### Enabled=true
#### Warning=true
#### DisplayName=Dcl58 Cpp
#### HelpText
  Modification of the std or posix namespace can result in undefined behavior. This check warns for such modifications.

  Examples:

  ``` cpp
  namespace std {
    int x; // May cause undefined behavior.
  }
  ```

  This check corresponds to the CERT C++ Coding Standard rule [DCL58-CPP. Do not modify the standard namespaces](https://www.securecoding.cert.org/confluence/display/cplusplus/DCL58-CPP.+Do+not+modify+the+standard+namespaces).

  (Clang-Tidy original name: cert-dcl58-cpp)

#### Tags
- /general/Cert
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CRT_DCL59_CPP
### Default
#### OriginalId=cert-dcl59-cpp
#### Enabled=true
#### Warning=true
#### DisplayName=Dcl59 Cpp
#### HelpText
  The cert-dcl59-cpp check is an alias, please see [google-build-namespaces](google-build-namespaces.html) for more information.

  (Clang-Tidy original name: cert-dcl59-cpp)

#### Tags
- /general/Cert
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CRT_ENV33_C
### Default
#### OriginalId=cert-env33-c
#### Enabled=true
#### Warning=true
#### DisplayName=Env33 C
#### HelpText
  This check flags calls to system(), popen(), and \_popen(), which execute a command processor. It does not flag calls to system() with a null pointer argument, as such a call checks for the presence of a command processor but does not actually attempt to execute a command.

  This check corresponds to the CERT C Coding Standard rule [ENV33-C. Do not call system()](https://www.securecoding.cert.org/confluence/pages/viewpage.action?pageId=2130132).

  (Clang-Tidy original name: cert-env33-c)

#### Tags
- /general/Cert
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CRT_ERR09_CPP
### Default
#### OriginalId=cert-err09-cpp
#### Enabled=true
#### Warning=true
#### DisplayName=Err09 Cpp
#### HelpText
  The cert-err09-cpp check is an alias, please see [misc-throw-by-value-catch-by-reference](misc-throw-by-value-catch-by-reference.html) for more information.

  This check corresponds to the CERT C++ Coding Standard recommendation ERR09-CPP. Throw anonymous temporaries. However, all of the CERT recommendations have been removed from public view, and so their justification for the behavior of this check requires an account on their wiki to view.

  (Clang-Tidy original name: cert-err09-cpp)

#### Tags
- /general/Cert
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CRT_ERR34_C
### Default
#### OriginalId=cert-err34-c
#### Enabled=true
#### Warning=true
#### DisplayName=Err34 C
#### HelpText
  This check flags calls to string-to-number conversion functions that do not verify the validity of the conversion, such as atoi() or scanf(). It does not flag calls to strtol(), or other, related conversion functions that do perform better error checking.

  ``` cpp
  #include <stdlib.h>

  void func(const char *buff) {
    int si;

    if (buff) {
      si = atoi(buff); /* 'atoi' used to convert a string to an integer, but function will
                           not report conversion errors; consider using 'strtol' instead. */
    } else {
      /* Handle error */
    }
  }
  ```

  This check corresponds to the CERT C Coding Standard rule [ERR34-C. Detect errors when converting a string to a number](https://www.securecoding.cert.org/confluence/display/c/ERR34-C.+Detect+errors+when+converting+a+string+to+a+number).

  (Clang-Tidy original name: cert-err34-c)

#### Tags
- /general/Cert
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CRT_ERR52_CPP
### Default
#### OriginalId=cert-err52-cpp
#### Enabled=true
#### Warning=true
#### DisplayName=Err52 Cpp
#### HelpText
  This check flags all call expressions involving setjmp() and longjmp().

  This check corresponds to the CERT C++ Coding Standard rule [ERR52-CPP. Do not use setjmp() or longjmp()](https://www.securecoding.cert.org/confluence/pages/viewpage.action?pageId=1834).

  (Clang-Tidy original name: cert-err52-cpp)

#### Tags
- /general/Cert
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CRT_ERR58_CPP
### Default
#### OriginalId=cert-err58-cpp
#### Enabled=true
#### Warning=true
#### DisplayName=Err58 Cpp
#### HelpText
  This check flags all static or thread\_local variable declarations where the initializer for the object may throw an exception.

  This check corresponds to the CERT C++ Coding Standard rule [ERR58-CPP. Handle all exceptions thrown before main() begins executing](https://www.securecoding.cert.org/confluence/display/cplusplus/ERR58-CPP.+Handle+all+exceptions+thrown+before+main%28%29+begins+executing).

  (Clang-Tidy original name: cert-err58-cpp)

#### Tags
- /general/Cert
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CRT_ERR60_CPP
### Default
#### OriginalId=cert-err60-cpp
#### Enabled=true
#### Warning=true
#### DisplayName=Err60 Cpp
#### HelpText
  This check flags all throw expressions where the exception object is not nothrow copy constructible.

  This check corresponds to the CERT C++ Coding Standard rule [ERR60-CPP. Exception objects must be nothrow copy constructible](https://www.securecoding.cert.org/confluence/display/cplusplus/ERR60-CPP.+Exception+objects+must+be+nothrow+copy+constructible).

  (Clang-Tidy original name: cert-err60-cpp)

#### Tags
- /general/Cert
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CRT_ERR61_CPP
### Default
#### OriginalId=cert-err61-cpp
#### Enabled=true
#### Warning=true
#### DisplayName=Err61 Cpp
#### HelpText
  The cert-err61-cpp check is an alias, please see [misc-throw-by-value-catch-by-reference](misc-throw-by-value-catch-by-reference.html) for more information.

  (Clang-Tidy original name: cert-err61-cpp)

#### Tags
- /general/Cert
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CRT_FIO38_C
### Default
#### OriginalId=cert-fio38-c
#### Enabled=true
#### Warning=true
#### DisplayName=Fio38 C
#### HelpText
  The cert-fio38-c check is an alias, please see [misc-non-copyable-objects](misc-non-copyable-objects.html) for more information.

  (Clang-Tidy original name: cert-fio38-c)

#### Tags
- /general/Cert
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CRT_FLP30_C
### Default
#### OriginalId=cert-flp30-c
#### Enabled=true
#### Warning=true
#### DisplayName=Flp30 C
#### HelpText
  This check flags for loops where the induction expression has a floating-point type.

  This check corresponds to the CERT C Coding Standard rule [FLP30-C. Do not use floating-point variables as loop counters](https://www.securecoding.cert.org/confluence/display/c/FLP30-C.+Do+not+use+floating-point+variables+as+loop+counters).

  (Clang-Tidy original name: cert-flp30-c)

#### Tags
- /general/Cert
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CRT_MEM57_CPP
### Default
#### OriginalId=cert-mem57-cpp
#### Enabled=true
#### Warning=true
#### DisplayName=Mem57 Cpp
#### HelpText
  This check flags uses of default operator new where the type has extended alignment (an alignment greater than the fundamental alignment). (The default operator new is guaranteed to provide the correct alignment if the requested alignment is less or equal to the fundamental alignment). Only cases are detected (by design) where the operator new is not user-defined and is not a placement new (the reason is that in these cases we assume that the user provided the correct memory allocation).

  This check corresponds to the CERT C++ Coding Standard rule [MEM57-CPP. Avoid using default operator new for over-aligned types](https://wiki.sei.cmu.edu/confluence/display/cplusplus/MEM57-CPP.+Avoid+using+default+operator+new+for+over-aligned+types).

  (Clang-Tidy original name: cert-mem57-cpp)

#### Tags
- /general/Cert
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CRT_MSC30_C
### Default
#### OriginalId=cert-msc30-c
#### Enabled=true
#### Warning=true
#### DisplayName=Msc30 C
#### HelpText
  The cert-msc30-c check is an alias, please see [cert-msc50-cpp](cert-msc50-cpp.html) for more information.

  (Clang-Tidy original name: cert-msc30-c)

#### Tags
- /general/Cert
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CRT_MSC32_C
### Default
#### OriginalId=cert-msc32-c
#### Enabled=true
#### Warning=true
#### DisplayName=Msc32 C
#### HelpText
  The cert-msc32-c check is an alias, please see [cert-msc51-cpp](cert-msc51-cpp.html) for more information.

  (Clang-Tidy original name: cert-msc32-c)

#### Tags
- /general/Cert
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CRT_MSC50_CPP
### Default
#### OriginalId=cert-msc50-cpp
#### Enabled=true
#### Warning=true
#### DisplayName=Msc50 Cpp
#### HelpText
  Pseudorandom number generators use mathematical algorithms to produce a sequence of numbers with good statistical properties, but the numbers produced are not genuinely random. The std::rand() function takes a seed (number), runs a mathematical operation on it and returns the result. By manipulating the seed the result can be predictable. This check warns for the usage of std::rand().

  (Clang-Tidy original name: cert-msc50-cpp)

#### Tags
- /general/Cert
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CRT_MSC51_CPP
### Default
#### OriginalId=cert-msc51-cpp
#### Enabled=true
#### Warning=true
#### DisplayName=Msc51 Cpp
#### HelpText
  This check flags all pseudo-random number engines, engine adaptor instantiations and srand() when initialized or seeded with default argument, constant expression or any user-configurable type. Pseudo-random number engines seeded with a predictable value may cause vulnerabilities e.g. in security protocols. This is a CERT security rule, see [MSC51-CPP. Ensure your random number generator is properly seeded](https://wiki.sei.cmu.edu/confluence/display/cplusplus/MSC51-CPP.+Ensure+your+random+number+generator+is+properly+seeded) and [MSC32-C. Properly seed pseudorandom number generators](https://wiki.sei.cmu.edu/confluence/display/c/MSC32-C.+Properly+seed+pseudorandom+number+generators).

  Examples:

  ``` cpp
  void foo() {
    std::mt19937 engine1; // Diagnose, always generate the same sequence
    std::mt19937 engine2(1); // Diagnose
    engine1.seed(); // Diagnose
    engine2.seed(1); // Diagnose

    std::time_t t;
    engine1.seed(std::time(&t)); // Diagnose, system time might be controlled by user

    int x = atoi(argv[1]);
    std::mt19937 engine3(x);  // Will not warn
  }
  ```

  ##### Options

  DisallowedSeedTypes

  A comma-separated list of the type names which are disallowed. Default values are time\_t, std::time\_t.

  (Clang-Tidy original name: cert-msc51-cpp)

#### Tags
- /general/Cert
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CRT_OOP11_CPP
### Default
#### OriginalId=cert-oop11-cpp
#### Enabled=true
#### Warning=true
#### DisplayName=Oop11 Cpp
#### HelpText
  The cert-oop11-cpp check is an alias, please see [performance-move-constructor-init](performance-move-constructor-init.html) for more information.

  This check corresponds to the CERT C++ Coding Standard recommendation OOP11-CPP. Do not copy-initialize members or base classes from a move constructor. However, all of the CERT recommendations have been removed from public view, and so their justification for the behavior of this check requires an account on their wiki to view.

  (Clang-Tidy original name: cert-oop11-cpp)

#### Tags
- /general/Cert
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CRT_OOP54_CPP
### Default
#### OriginalId=cert-oop54-cpp
#### Enabled=true
#### Warning=true
#### DisplayName=Oop54 Cpp
#### HelpText
  The cert-oop54-cpp check is an alias, please see [bugprone-unhandled-self-assignment](bugprone-unhandled-self-assignment.html) for more information.

  (Clang-Tidy original name: cert-oop54-cpp)

#### Tags
- /general/Cert
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CRT_OOP57_CPP
### Default
#### OriginalId=cert-oop57-cpp
#### Enabled=true
#### Warning=true
#### DisplayName=Oop57 Cpp
#### HelpText
  Flags use of the C standard library functions memset, memcpy and memcmp and similar derivatives on non-trivial types.

  ##### Options

  MemSetNames

  Specify extra functions to flag that act similarily to memset. Specify names in a semicolon delimited list. Default is an empty string. The check will detect the following functions: memset, std::memset.

  MemCpyNames

  Specify extra functions to flag that act similarily to memcpy. Specify names in a semicolon delimited list. Default is an empty string. The check will detect the following functions: std::memcpy, memcpy, std::memmove, memmove, std::strcpy, strcpy, memccpy, stpncpy, strncpy.

  MemCmpNames

  Specify extra functions to flag that act similarily to memcmp. Specify names in a semicolon delimited list. Default is an empty string. The check will detect the following functions: std::memcmp, memcmp, std::strcmp, strcmp, strncmp.

  This check corresponds to the CERT C++ Coding Standard rule [OOP57-CPP. Prefer special member functions and overloaded operators to C Standard Library functions](https://wiki.sei.cmu.edu/confluence/display/cplusplus/OOP57-CPP.+Prefer+special+member+functions+and+overloaded+operators+to+C+Standard+Library+functions).

  (Clang-Tidy original name: cert-oop57-cpp)

#### Tags
- /general/Cert
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CRT_OOP58_CPP
### Default
#### OriginalId=cert-oop58-cpp
#### Enabled=true
#### Warning=true
#### DisplayName=Oop58 Cpp
#### HelpText
  Finds assignments to the copied object and its direct or indirect members in copy constructors and copy assignment operators.

  This check corresponds to the CERT C Coding Standard rule [OOP58-CPP. Copy operations must not mutate the source object](https://wiki.sei.cmu.edu/confluence/display/cplusplus/OOP58-CPP.+Copy+operations+must+not+mutate+the+source+object).

  (Clang-Tidy original name: cert-oop58-cpp)

#### Tags
- /general/Cert
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CRT_POS44_C
### Default
#### OriginalId=cert-pos44-c
#### Enabled=true
#### Warning=true
#### DisplayName=Pos44 C
#### HelpText
  The cert-pos44-c check is an alias, please see [bugprone-bad-signal-to-kill-thread](bugprone-bad-signal-to-kill-thread.html) for more information.

  (Clang-Tidy original name: cert-pos44-c)

#### Tags
- /general/Cert
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CRT_SIG30_C
### Default
#### OriginalId=cert-sig30-c
#### Enabled=true
#### Warning=true
#### DisplayName=Sig30 C
#### HelpText
  The cert-sig30-c check is an alias, please see [bugprone-signal-handler](bugprone-signal-handler.html) for more information.

  (Clang-Tidy original name: cert-sig30-c)

#### Tags
- /general/Cert
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_CRT_STR34_C
### Default
#### OriginalId=cert-str34-c
#### Enabled=true
#### Warning=true
#### DisplayName=Str34 C
#### HelpText
  The cert-str34-c check is an alias, please see [bugprone-signed-char-misuse](bugprone-signed-char-misuse.html) for more information.

  (Clang-Tidy original name: cert-str34-c)

#### Tags
- /general/Cert
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_DRW_AS
### Default
#### OriginalId=darwin-avoid-spinlock
#### Enabled=false
#### Warning=true
#### DisplayName=Avoid Spinlock
#### HelpText
  Finds usages of OSSpinlock, which is deprecated due to potential livelock problems.

  This check will detect following function invocations:

    * OSSpinlockLock
    * OSSpinlockTry
    * OSSpinlockUnlock



  The corresponding information about the problem of OSSpinlock: <https://blog.postmates.com/why-spinlocks-are-bad-on-ios-b69fc5221058>

  (Clang-Tidy original name: darwin-avoid-spinlock)

#### Tags
- /general/Darwin
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_DRW_DON
### Default
#### OriginalId=darwin-dispatch-once-nonstatic
#### Enabled=false
#### Warning=true
#### DisplayName=Dispatch Once Nonstatic
#### HelpText
  Finds declarations of dispatch_once_t variables without static or global storage. The behavior of using dispatch_once_t predicates with automatic or dynamic storage is undefined by libdispatch, and should be avoided.

  It is a common pattern to have functions initialize internal static or global data once when the function runs, but programmers have been known to miss the static on the dispatch_once_t predicate, leading to an uninitialized flag value at the mercy of the stack.

  Programmers have also been known to make dispatch_once_t variables be members of structs or classes, with the intent to lazily perform some expensive struct or class member initialization only once; however, this violates the libdispatch requirements.

  See the discussion section of [Apple’s dispatch_once documentation](https://developer.apple.com/documentation/dispatch/1447169-dispatch_once) for more information.

  (Clang-Tidy original name: darwin-dispatch-once-nonstatic)

#### Tags
- /general/Darwin
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_FCS_DAC
### Default
#### OriginalId=fuchsia-default-arguments-calls
#### Enabled=false
#### Warning=true
#### DisplayName=Default Arguments Calls
#### HelpText
  Warns if a function or method is called with default arguments.

  For example, given the declaration:

  ``` cpp
  int foo(int value = 5) { return value; }

  ```


  A function call expression that uses a default argument will be diagnosed. Calling it without defaults will not cause a warning:

  ``` cpp
  foo();  // warning
  foo(0); // no warning

  ```


  See the features disallowed in Fuchsia at <https://fuchsia.googlesource.com/zircon/+/master/docs/cxx.md>

  (Clang-Tidy original name: fuchsia-default-arguments-calls)

#### Tags
- /general/Fuchsia
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_FCS_DAD
### Default
#### OriginalId=fuchsia-default-arguments-declarations
#### Enabled=false
#### Warning=true
#### DisplayName=Default Arguments Declarations
#### HelpText
  Warns if a function or method is declared with default parameters.

  For example, the declaration:

  ``` cpp
  int foo(int value = 5) { return value; }

  ```


  will cause a warning.

  See the features disallowed in Fuchsia at <https://fuchsia.googlesource.com/zircon/+/master/docs/cxx.md>

  (Clang-Tidy original name: fuchsia-default-arguments-declarations)

#### Tags
- /general/Fuchsia
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_FCS_HAN
### Default
#### OriginalId=fuchsia-header-anon-namespaces
#### Enabled=false
#### Warning=true
#### DisplayName=Header Anon Namespaces
#### HelpText
  The fuchsia-header-anon-namespaces check is an alias, please see [google-build-namespace](google-build-namespaces.html) for more information.

  (Clang-Tidy original name: fuchsia-header-anon-namespaces)

#### Tags
- /general/Fuchsia
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_FCS_MI
### Default
#### OriginalId=fuchsia-multiple-inheritance
#### Enabled=false
#### Warning=true
#### DisplayName=Multiple Inheritance
#### HelpText
  Warns if a class inherits from multiple classes that are not pure virtual.

  For example, declaring a class that inherits from multiple concrete classes is disallowed:

  ``` cpp
  class Base_A {
  public:
    virtual int foo() { return 0; }
  };

  class Base_B {
  public:
    virtual int bar() { return 0; }
  };

  // Warning
  class Bad_Child1 : public Base_A, Base_B {};

  ```


  A class that inherits from a pure virtual is allowed:

  ``` cpp
  class Interface_A {
  public:
    virtual int foo() = 0;
  };

  class Interface_B {
  public:
    virtual int bar() = 0;
  };

  // No warning
  class Good_Child1 : public Interface_A, Interface_B {
    virtual int foo() override { return 0; }
    virtual int bar() override { return 0; }
  };

  ```


  See the features disallowed in Fuchsia at <https://fuchsia.googlesource.com/zircon/+/master/docs/cxx.md>

  (Clang-Tidy original name: fuchsia-multiple-inheritance)

#### Tags
- /general/Fuchsia
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_FCS_OO
### Default
#### OriginalId=fuchsia-overloaded-operator
#### Enabled=false
#### Warning=true
#### DisplayName=Overloaded Operator
#### HelpText
  Warns if an operator is overloaded, except for the assignment (copy and move) operators.

  For example:

  ``` cpp
  int operator+(int);     // Warning

  B &operator=(const B &Other);  // No warning
  B &operator=(B &&Other) // No warning

  ```


  See the features disallowed in Fuchsia at <https://fuchsia.googlesource.com/zircon/+/master/docs/cxx.md>

  (Clang-Tidy original name: fuchsia-overloaded-operator)

#### Tags
- /general/Fuchsia
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_FCS_SCO
### Default
#### OriginalId=fuchsia-statically-constructed-objects
#### Enabled=false
#### Warning=true
#### DisplayName=Statically Constructed Objects
#### HelpText
  Warns if global, non-trivial objects with static storage are constructed, unless the object is statically initialized with a constexpr constructor or has no explicit constructor.

  For example:

  ``` cpp
  class A {};

  class B {
  public:
    B(int Val) : Val(Val) {}
  private:
    int Val;
  };

  class C {
  public:
    C(int Val) : Val(Val) {}
    constexpr C() : Val(0) {}

  private:
    int Val;
  };

  static A a;         // No warning, as there is no explicit constructor
  static C c(0);      // No warning, as constructor is constexpr

  static B b(0);      // Warning, as constructor is not constexpr
  static C c2(0, 1);  // Warning, as constructor is not constexpr

  static int i;       // No warning, as it is trivial

  extern int get_i();
  static C(get_i())   // Warning, as the constructor is dynamically initialized

  ```


  See the features disallowed in Fuchsia at <https://fuchsia.googlesource.com/zircon/+/master/docs/cxx.md>

  (Clang-Tidy original name: fuchsia-statically-constructed-objects)

#### Tags
- /general/Fuchsia
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_FCS_TR
### Default
#### OriginalId=fuchsia-trailing-return
#### Enabled=false
#### Warning=true
#### DisplayName=Trailing Return
#### HelpText
  Functions that have trailing returns are disallowed, except for those using decltype specifiers and lambda with otherwise unutterable return types.

  For example:

  ``` cpp
  // No warning
  int add_one(const int arg) { return arg; }

  // Warning
  auto get_add_one() -> int (*)(const int) {
    return add_one;
  }

  ```


  Exceptions are made for lambdas and decltype specifiers:

  ``` cpp
  // No warning
  auto lambda = [](double x, double y) -> double {return x + y;};

  // No warning
  template <typename T1, typename T2>
  auto fn(const T1 &lhs, const T2 &rhs) -> decltype(lhs + rhs) {
    return lhs + rhs;
  }

  ```


  See the features disallowed in Fuchsia at <https://fuchsia.googlesource.com/zircon/+/master/docs/cxx.md>

  (Clang-Tidy original name: fuchsia-trailing-return)

#### Tags
- /general/Fuchsia
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_FCS_VI
### Default
#### OriginalId=fuchsia-virtual-inheritance
#### Enabled=false
#### Warning=true
#### DisplayName=Virtual Inheritance
#### HelpText
  Warns if classes are defined with virtual inheritance.

  For example, classes should not be defined with virtual inheritance:

  ``` cpp
  class B : public virtual A {};   // warning

  ```


  See the features disallowed in Fuchsia at <https://fuchsia.googlesource.com/zircon/+/master/docs/cxx.md>

  (Clang-Tidy original name: fuchsia-virtual-inheritance)

#### Tags
- /general/Fuchsia
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_GGL_BEMP
### Default
#### OriginalId=google-build-explicit-make-pair
#### Enabled=false
#### Warning=true
#### DisplayName=Build Explicit Make Pair
#### HelpText
  Check that make_pair’s template arguments are deduced.

  G++ 4.6 in C++11 mode fails badly if make_pair’s template arguments are specified explicitly, and such use isn’t intended in any case.

  Corresponding cpplint.py check name: build/explicit_make_pair.

  (Clang-Tidy original name: google-build-explicit-make-pair)

#### Tags
- /general/Google
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_GGL_BN
### Default
#### OriginalId=google-build-namespaces
#### Enabled=false
#### Warning=true
#### DisplayName=Build Namespaces
#### HelpText
  cert-dcl59-cpp redirects here as an alias for this check. fuchsia-header-anon-namespaces redirects here as an alias for this check.

  Finds anonymous namespaces in headers.

  <https://google.github.io/styleguide/cppguide.html\#Namespaces>

  Corresponding cpplint.py check name: build/namespaces.

  ##### Options

  HeaderFileExtensions     

  A comma-separated list of filename extensions of header files (the filename extensions should not include “.” prefix). Default is “h,hh,hpp,hxx”. For header files without an extension, use an empty string (if there are no other desired extensions) or leave an empty element in the list. e.g., “h,hh,hpp,hxx,” (note the trailing comma).

  (Clang-Tidy original name: google-build-namespaces)

#### Tags
- /general/Google
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_GGL_BUN
### Default
#### OriginalId=google-build-using-namespace
#### Enabled=false
#### Warning=true
#### DisplayName=Build Using Namespace
#### HelpText
  Finds using namespace directives.

  The check implements the following rule of the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html\#Namespaces):

  You may not use a using-directive to make all names from a namespace available.

  ``` cpp
  // Forbidden -- This pollutes the namespace.
  using namespace foo;

  ```


  Corresponding cpplint.py check name: build/namespaces.

  (Clang-Tidy original name: google-build-using-namespace)

#### Tags
- /general/Google
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_GGL_DA
### Default
#### OriginalId=google-default-arguments
#### Enabled=false
#### Warning=true
#### DisplayName=Default Arguments
#### HelpText
  Checks that default arguments are not given for virtual methods.

  See <https://google.github.io/styleguide/cppguide.html\#Default_Arguments>

  (Clang-Tidy original name: google-default-arguments)

#### Tags
- /general/Google
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_GGL_EC
### Default
#### OriginalId=google-explicit-constructor
#### Enabled=false
#### Warning=true
#### DisplayName=Explicit Constructor
#### HelpText
  Checks that constructors callable with a single argument and conversion operators are marked explicit to avoid the risk of unintentional implicit conversions.

  Consider this example:

  ``` cpp
  struct S {
    int x;
    operator bool() const { return true; }
  };

  bool f() {
    S a{1};
    S b{2};
    return a == b;
  }

  ```


  The function will return true, since the objects are implicitly converted to bool before comparison, which is unlikely to be the intent.

  The check will suggest inserting explicit before the constructor or conversion operator declaration. However, copy and move constructors should not be explicit, as well as constructors taking a single initializer_list argument.

  This code:

  ``` cpp
  struct S {
    S(int a);
    explicit S(const S&);
    operator bool() const;
    ...

  ```


  will become

  ``` cpp
  struct S {
    explicit S(int a);
    S(const S&);
    explicit operator bool() const;
    ...

  ```


  See <https://google.github.io/styleguide/cppguide.html\#Explicit_Constructors>

  (Clang-Tidy original name: google-explicit-constructor)

#### Tags
- /general/Google
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_GGL_GNIH
### Default
#### OriginalId=google-global-names-in-headers
#### Enabled=false
#### Warning=true
#### DisplayName=Global Names In Headers
#### HelpText
  Flag global namespace pollution in header files. Right now it only triggers on using declarations and directives.

  The relevant style guide section is <https://google.github.io/styleguide/cppguide.html\#Namespaces>.

  ##### Options

  HeaderFileExtensions     

  A comma-separated list of filename extensions of header files (the filename extensions should not contain “.” prefix). Default is “h”. For header files without an extension, use an empty string (if there are no other desired extensions) or leave an empty element in the list. e.g., “h,hh,hpp,hxx,” (note the trailing comma).

  (Clang-Tidy original name: google-global-names-in-headers)

#### Tags
- /general/Google
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_GGL_OANN
### Default
#### OriginalId=google-objc-avoid-nsobject-new
#### Enabled=false
#### Warning=true
#### DisplayName=Objc Avoid Nsobject New
#### HelpText
  Finds calls to +new or overrides of it, which are prohibited by the Google Objective-C style guide.

  The Google Objective-C style guide forbids calling +new or overriding it in class implementations, preferring +alloc and -init methods to instantiate objects.

  An example:

  ``` cpp
  NSDate *now = [NSDate new];
  Foo *bar = [Foo new];

  ```


  Instead, code should use +alloc/-init or class factory methods.

  ``` cpp
  NSDate *now = [NSDate date];
  Foo *bar = [[Foo alloc] init];

  ```


  This check corresponds to the Google Objective-C Style Guide rule [Do Not Use +new](https://google.github.io/styleguide/objcguide.html\#do-not-use-new).

  (Clang-Tidy original name: google-objc-avoid-nsobject-new)

#### Tags
- /general/Google
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_GGL_OATE
### Default
#### OriginalId=google-objc-avoid-throwing-exception
#### Enabled=false
#### Warning=true
#### DisplayName=Objc Avoid Throwing Exception
#### HelpText
  Finds uses of throwing exceptions usages in Objective-C files.

  For the same reason as the Google C++ style guide, we prefer not throwing exceptions from Objective-C code.

  The corresponding C++ style guide rule: <https://google.github.io/styleguide/cppguide.html\#Exceptions>

  Instead, prefer passing in NSError ** and return BOOL to indicate success or failure.

  A counterexample:

  ``` cpp
  - (void)readFile {
    if ([self isError]) {
      @throw [NSException exceptionWithName:...];
    }
  }

  ```


  Instead, returning an error via NSError ** is preferred:

  ``` cpp
  - (BOOL)readFileWithError:(NSError **)error {
    if ([self isError]) {
      *error = [NSError errorWithDomain:...];
      return NO;
    }
    return YES;
  }

  ```


  The corresponding style guide rule: <https://google.github.io/styleguide/objcguide.html\#avoid-throwing-exceptions>

  (Clang-Tidy original name: google-objc-avoid-throwing-exception)

#### Tags
- /general/Google
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_GGL_OFN
### Default
#### OriginalId=google-objc-function-naming
#### Enabled=false
#### Warning=true
#### DisplayName=Objc Function Naming
#### HelpText
  Finds function declarations in Objective-C files that do not follow the pattern described in the Google Objective-C Style Guide.

  The corresponding style guide rule can be found here: <https://google.github.io/styleguide/objcguide.html\#function-names>

  All function names should be in Pascal case. Functions whose storage class is not static should have an appropriate prefix.

  The following code sample does not follow this pattern:

  ``` cpp
  static bool is_positive(int i) { return i > 0; }
  bool IsNegative(int i) { return i < 0; }

  ```


  The sample above might be corrected to the following code:

  ``` cpp
  static bool IsPositive(int i) { return i > 0; }
  bool *ABCIsNegative(int i) { return i < 0; }

  ```


  (Clang-Tidy original name: google-objc-function-naming)

#### Tags
- /general/Google
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_GGL_OGVD
### Default
#### OriginalId=google-objc-global-variable-declaration
#### Enabled=false
#### Warning=true
#### DisplayName=Objc Global Variable Declaration
#### HelpText
  Finds global variable declarations in Objective-C files that do not follow the pattern of variable names in Google’s Objective-C Style Guide.

  The corresponding style guide rule: <https://google.github.io/styleguide/objcguide.html\#variable-names>

  All the global variables should follow the pattern of g[A-Z].* (variables) or k[A-Z].* (constants). The check will suggest a variable name that follows the pattern if it can be inferred from the original name.

  For code:

  ``` cpp
  static NSString* myString = @"hello";

  ```


  The fix will be:

  ``` cpp
  static NSString* gMyString = @"hello";

  ```


  Another example of constant:

  ``` cpp
  static NSString* const myConstString = @"hello";

  ```


  The fix will be:

  ``` cpp
  static NSString* const kMyConstString = @"hello";

  ```


  However for code that prefixed with non-alphabetical characters like:

  ``` cpp
  static NSString* __anotherString = @"world";

  ```


  The check will give a warning message but will not be able to suggest a fix. The user needs to fix it on their own.

  (Clang-Tidy original name: google-objc-global-variable-declaration)

#### Tags
- /general/Google
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_GGL_RAUIGN
### Default
#### OriginalId=google-readability-avoid-underscore-in-googletest-name
#### Enabled=false
#### Warning=true
#### DisplayName=Readability Avoid Underscore In Googletest Name
#### HelpText
  Checks whether there are underscores in googletest test and test case names in test macros:

    * TEST
    * TEST_F
    * TEST_P
    * TYPED_TEST
    * TYPED_TEST_P



  The FRIEND_TEST macro is not included.

  For example:

  ``` cpp
  TEST(TestCaseName, Illegal_TestName) {}
  TEST(Illegal_TestCaseName, TestName) {}

  ```


  would trigger the check. [Underscores are not allowed](https://github.com/google/googletest/blob/master/googletest/docs/faq.md\#why-should-test-suite-names-and-test-names-not-contain-underscore) in test names nor test case names.

  The DISABLED_ prefix, which may be used to [disable individual tests](https://github.com/google/googletest/blob/master/googletest/docs/faq.md\#why-should-test-suite-names-and-test-names-not-contain-underscore), is ignored when checking test names, but the rest of the rest of the test name is still checked.

  This check does not propose any fixes.

  (Clang-Tidy original name: google-readability-avoid-underscore-in-googletest-name)

#### Tags
- /general/Google
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_GGL_RBAS
### Default
#### OriginalId=google-readability-braces-around-statements
#### Enabled=false
#### Warning=true
#### DisplayName=Readability Braces Around Statements
#### HelpText
  The google-readability-braces-around-statements check is an alias, please see [readability-braces-around-statements](readability-braces-around-statements.html) for more information.

  (Clang-Tidy original name: google-readability-braces-around-statements)

#### Tags
- /general/Google
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_GGL_RC
### Default
#### OriginalId=google-readability-casting
#### Enabled=false
#### Warning=true
#### DisplayName=Readability Casting
#### HelpText
  Finds usages of C-style casts.

  <https://google.github.io/styleguide/cppguide.html\#Casting>

  Corresponding cpplint.py check name: readability/casting.

  This check is similar to -Wold-style-cast, but it suggests automated fixes in some cases. The reported locations should not be different from the ones generated by -Wold-style-cast.

  (Clang-Tidy original name: google-readability-casting)

#### Tags
- /general/Google
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_GGL_RFS
### Default
#### OriginalId=google-readability-function-size
#### Enabled=false
#### Warning=true
#### DisplayName=Readability Function Size
#### HelpText
  The google-readability-function-size check is an alias, please see [readability-function-size](readability-function-size.html) for more information.

  (Clang-Tidy original name: google-readability-function-size)

#### Tags
- /general/Google
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_GGL_RI
### Default
#### OriginalId=google-runtime-int
#### Enabled=false
#### Warning=true
#### DisplayName=Runtime Int
#### HelpText
  Finds uses of short, long and long long and suggest replacing them with u?intXX(_t)?.

  The corresponding style guide rule: <https://google.github.io/styleguide/cppguide.html\#Integer_Types>.

  Corresponding cpplint.py check: runtime/int.

  ##### Options

  UnsignedTypePrefix     

  A string specifying the unsigned type prefix. Default is uint.

  SignedTypePrefix     

  A string specifying the signed type prefix. Default is int.

  TypeSuffix     

  A string specifying the type suffix. Default is an empty string.

  (Clang-Tidy original name: google-runtime-int)

#### Tags
- /general/Google
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_GGL_RNC
### Default
#### OriginalId=google-readability-namespace-comments
#### Enabled=false
#### Warning=true
#### DisplayName=Readability Namespace Comments
#### HelpText
  The google-readability-namespace-comments check is an alias, please see [llvm-namespace-comment](llvm-namespace-comment.html) for more information.

  (Clang-Tidy original name: google-readability-namespace-comments)

#### Tags
- /general/Google
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_GGL_RO
### Default
#### OriginalId=google-runtime-operator
#### Enabled=false
#### Warning=true
#### DisplayName=Runtime Operator
#### HelpText
  Finds overloads of unary operator &.

  <https://google.github.io/styleguide/cppguide.html\#Operator_Overloading>

  Corresponding cpplint.py check name: runtime/operator.

  (Clang-Tidy original name: google-runtime-operator)

#### Tags
- /general/Google
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_GGL_RT
### Default
#### OriginalId=google-readability-todo
#### Enabled=false
#### Warning=true
#### DisplayName=Readability Todo
#### HelpText
  Finds TODO comments without a username or bug number.

  The relevant style guide section is <https://google.github.io/styleguide/cppguide.html\#TODO_Comments>.

  Corresponding cpplint.py check: readability/todo

  (Clang-Tidy original name: google-readability-todo)

#### Tags
- /general/Google
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_GGL_UGC
### Default
#### OriginalId=google-upgrade-googletest-case
#### Enabled=false
#### Warning=true
#### DisplayName=Upgrade Googletest Case
#### HelpText
  Finds uses of deprecated Google Test version 1.9 APIs with names containing case and replaces them with equivalent APIs with suite.

  All names containing case are being replaced to be consistent with the meanings of “test case” and “test suite” as used by the International Software Testing Qualifications Board and ISO 29119.

  The new names are a part of Google Test version 1.9 (release pending). It is recommended that users update their dependency to version 1.9 and then use this check to remove deprecated names.

  The affected APIs are:

    * Member functions of testing::Test, testing::TestInfo, testing::TestEventListener, testing::UnitTest, and any type inheriting from these types
    * The macros TYPED_TEST_CASE, TYPED_TEST_CASE_P, REGISTER_TYPED_TEST_CASE_P, and INSTANTIATE_TYPED_TEST_CASE_P
    * The type alias testing::TestCase



  Examples of fixes created by this check:

  ``` cpp
  class FooTest : public testing::Test {
  public:
    static void SetUpTestCase();
    static void TearDownTestCase();
  };

  TYPED_TEST_CASE(BarTest, BarTypes);

  ```


  becomes

  ``` cpp
  class FooTest : public testing::Test {
  public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
  };

  TYPED_TEST_SUITE(BarTest, BarTypes);

  ```


  For better consistency of user code, the check renames both virtual and non-virtual member functions with matching names in derived types. The check tries to provide a only warning when a fix cannot be made safely, as is the case with some template and macro uses.

  (Clang-Tidy original name: google-upgrade-googletest-case)

#### Tags
- /general/Google
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_HIC_ACA
### Default
#### OriginalId=hicpp-avoid-c-arrays
#### Enabled=false
#### Warning=true
#### DisplayName=Avoid C Arrays
#### HelpText
  The hicpp-avoid-c-arrays check is an alias, please see [modernize-avoid-c-arrays](modernize-avoid-c-arrays.html) for more information.

  (Clang-Tidy original name: hicpp-avoid-c-arrays)

#### Tags
- /general/High Integrity C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_HIC_AG
### Default
#### OriginalId=hicpp-avoid-goto
#### Enabled=false
#### Warning=true
#### DisplayName=Avoid Goto
#### HelpText
  The hicpp-avoid-goto check is an alias to [cppcoreguidelines-avoid-goto](cppcoreguidelines-avoid-goto.html). Rule [6.3.1 High Integrity C++](http://www.codingstandard.com/rule/6-3-1-ensure-that-the-labels-for-a-jump-statement-or-a-switch-condition-appear-later-in-the-same-or-an-enclosing-block/) requires that goto only skips parts of a block and is not used for other reasons.

  Both coding guidelines implement the same exception to the usage of goto.

  (Clang-Tidy original name: hicpp-avoid-goto)

#### Tags
- /general/High Integrity C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_HIC_BAS
### Default
#### OriginalId=hicpp-braces-around-statements
#### Enabled=false
#### Warning=true
#### DisplayName=Braces Around Statements
#### HelpText
  The hicpp-braces-around-statements check is an alias, please see [readability-braces-around-statements](readability-braces-around-statements.html) for more information. It enforces the [rule 6.1.1](http://www.codingstandard.com/rule/6-1-1-enclose-the-body-of-a-selection-or-an-iteration-statement-in-a-compound-statement/).

  (Clang-Tidy original name: hicpp-braces-around-statements)

#### Tags
- /general/High Integrity C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_HIC_DH
### Default
#### OriginalId=hicpp-deprecated-headers
#### Enabled=false
#### Warning=true
#### DisplayName=Deprecated Headers
#### HelpText
  The hicpp-deprecated-headers check is an alias, please see [modernize-deprecated-headers](modernize-deprecated-headers.html) for more information. It enforces the [rule 1.3.3](http://www.codingstandard.com/rule/1-3-3-do-not-use-the-c-standard-library-h-headers/).

  (Clang-Tidy original name: hicpp-deprecated-headers)

#### Tags
- /general/High Integrity C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_HIC_EB
### Default
#### OriginalId=hicpp-exception-baseclass
#### Enabled=false
#### Warning=true
#### DisplayName=Exception Baseclass
#### HelpText
  Ensure that every value that in a throw expression is an instance of std::exception.

  This enforces [rule 15.1](http://www.codingstandard.com/section/15-1-throwing-an-exception/) of the High Integrity C++ Coding Standard.

  ``` cpp
  class custom_exception {};

  void throwing() noexcept(false) {
    // Problematic throw expressions.
    throw int(42);
    throw custom_exception();
  }

  class mathematical_error : public std::exception {};

  void throwing2() noexcept(false) {
    // These kind of throws are ok.
    throw mathematical_error();
    throw std::runtime_error();
    throw std::exception();
  }

  ```


  (Clang-Tidy original name: hicpp-exception-baseclass)

#### Tags
- /general/High Integrity C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_HIC_EC
### Default
#### OriginalId=hicpp-explicit-conversions
#### Enabled=false
#### Warning=true
#### DisplayName=Explicit Conversions
#### HelpText
  This check is an alias for [google-explicit-constructor](google-explicit-constructor.html). Used to enforce parts of [rule 5.4.1](http://www.codingstandard.com/rule/5-4-1-only-use-casting-forms-static_cast-excl-void-dynamic_cast-or-explicit-constructor-call/). This check will enforce that constructors and conversion operators are marked explicit. Other forms of casting checks are implemented in other places. The following checks can be used to check for more forms of casting:

    * [cppcoreguidelines-pro-type-static-cast-downcast](cppcoreguidelines-pro-type-static-cast-downcast.html)
    * [cppcoreguidelines-pro-type-reinterpret-cast](cppcoreguidelines-pro-type-reinterpret-cast.html)
    * [cppcoreguidelines-pro-type-const-cast](cppcoreguidelines-pro-type-const-cast.html)
    * [cppcoreguidelines-pro-type-cstyle-cast](cppcoreguidelines-pro-type-cstyle-cast.html)



  (Clang-Tidy original name: hicpp-explicit-conversions)

#### Tags
- /general/High Integrity C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_HIC_FS
### Default
#### OriginalId=hicpp-function-size
#### Enabled=false
#### Warning=true
#### DisplayName=Function Size
#### HelpText
  This check is an alias for [readability-function-size](readability-function-size.html). Useful to enforce multiple sections on function complexity.

    * [rule 8.2.2](http://www.codingstandard.com/rule/8-2-2-do-not-declare-functions-with-an-excessive-number-of-parameters/)
    * [rule 8.3.1](http://www.codingstandard.com/rule/8-3-1-do-not-write-functions-with-an-excessive-mccabe-cyclomatic-complexity/)
    * [rule 8.3.2](http://www.codingstandard.com/rule/8-3-2-do-not-write-functions-with-a-high-static-program-path-count/)



  (Clang-Tidy original name: hicpp-function-size)

#### Tags
- /general/High Integrity C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_HIC_IAM
### Default
#### OriginalId=hicpp-invalid-access-moved
#### Enabled=false
#### Warning=true
#### DisplayName=Invalid Access Moved
#### HelpText
  This check is an alias for [bugprone-use-after-move](bugprone-use-after-move.html).

  Implements parts of the [rule 8.4.1](http://www.codingstandard.com/rule/8-4-1-do-not-access-an-invalid-object-or-an-object-with-indeterminate-value/) to check if moved-from objects are accessed.

  (Clang-Tidy original name: hicpp-invalid-access-moved)

#### Tags
- /general/High Integrity C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_HIC_MCA
### Default
#### OriginalId=hicpp-move-const-arg
#### Enabled=false
#### Warning=true
#### DisplayName=Move Const Arg
#### HelpText
  The hicpp-move-const-arg check is an alias, please see [performance-move-const-arg](performance-move-const-arg.html) for more information. It enforces the [rule 17.3.1](http://www.codingstandard.com/rule/17-3-1-do-not-use-stdmove-on-objects-declared-with-const-or-const-type/).

  (Clang-Tidy original name: hicpp-move-const-arg)

#### Tags
- /general/High Integrity C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_HIC_MI
### Default
#### OriginalId=hicpp-member-init
#### Enabled=false
#### Warning=true
#### DisplayName=Member Init
#### HelpText
  This check is an alias for [cppcoreguidelines-pro-type-member-init](cppcoreguidelines-pro-type-member-init.html). Implements the check for [rule 12.4.2](http://www.codingstandard.com/rule/12-4-2-ensure-that-a-constructor-initializes-explicitly-all-base-classes-and-non-static-data-members/) to initialize class members in the right order.

  (Clang-Tidy original name: hicpp-member-init)

#### Tags
- /general/High Integrity C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_HIC_MPC
### Default
#### OriginalId=hicpp-multiway-paths-covered
#### Enabled=false
#### Warning=true
#### DisplayName=Multiway Paths Covered
#### HelpText
  This check discovers situations where code paths are not fully-covered. It furthermore suggests using if instead of switch if the code will be more clear. The [rule 6.1.2](http://www.codingstandard.com/rule/6-1-2-explicitly-cover-all-paths-through-multi-way-selection-statements/) and [rule 6.1.4](http://www.codingstandard.com/rule/6-1-4-ensure-that-a-switch-statement-has-at-least-two-case-labels-distinct-from-the-default-label/) of the High Integrity C++ Coding Standard are enforced.

  if-else if chains that miss a final else branch might lead to unexpected program execution and be the result of a logical error. If the missing else branch is intended you can leave it empty with a clarifying comment. This warning can be noisy on some code bases, so it is disabled by default.

  ``` cpp
  void f1() {
    int i = determineTheNumber();

     if(i > 0) {
       // Some Calculation
     } else if (i < 0) {
       // Precondition violated or something else.
     }
     // ...
  }

  ```


  Similar arguments hold for switch statements which do not cover all possible code paths.

  ``` cpp
  // The missing default branch might be a logical error. It can be kept empty
  // if there is nothing to do, making it explicit.
  void f2(int i) {
    switch (i) {
    case 0: // something
      break;
    case 1: // something else
      break;
    }
    // All other numbers?
  }

  // Violates this rule as well, but already emits a compiler warning (-Wswitch).
  enum Color { Red, Green, Blue, Yellow };
  void f3(enum Color c) {
    switch (c) {
    case Red: // We can't drive for now.
      break;
    case Green:  // We are allowed to drive.
      break;
    }
    // Other cases missing
  }

  ```


  The [rule 6.1.4](http://www.codingstandard.com/rule/6-1-4-ensure-that-a-switch-statement-has-at-least-two-case-labels-distinct-from-the-default-label/) requires every switch statement to have at least two case labels other than a default label. Otherwise, the switch could be better expressed with an if statement. Degenerated switch statements without any labels are caught as well.

  ``` cpp
  // Degenerated switch that could be better written as `if`
  int i = 42;
  switch(i) {
    case 1: // do something here
    default: // do somethe else here
  }

  // Should rather be the following:
  if (i == 1) {
    // do something here
  }
  else {
    // do something here
  }

  ```


  ``` cpp
  // A completely degenerated switch will be diagnosed.
  int i = 42;
  switch(i) {}

  ```


  ##### Options

  WarnOnMissingElse     

  Boolean flag that activates a warning for missing else branches. Default is false.

  (Clang-Tidy original name: hicpp-multiway-paths-covered)

#### Tags
- /general/High Integrity C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_HIC_NA
### Default
#### OriginalId=hicpp-no-assembler
#### Enabled=false
#### Warning=true
#### DisplayName=No Assembler
#### HelpText
  Check for assembler statements. No fix is offered.

  Inline assembler is forbidden by the [High Intergrity C++ Coding Standard](http://www.codingstandard.com/section/7-5-the-asm-declaration/) as it restricts the portability of code.

  (Clang-Tidy original name: hicpp-no-assembler)

#### Tags
- /general/High Integrity C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_HIC_NAD
### Default
#### OriginalId=hicpp-no-array-decay
#### Enabled=false
#### Warning=true
#### DisplayName=No Array Decay
#### HelpText
  The hicpp-no-array-decay check is an alias, please see [cppcoreguidelines-pro-bounds-array-to-pointer-decay](cppcoreguidelines-pro-bounds-array-to-pointer-decay.html) for more information. It enforces the [rule 4.1.1](http://www.codingstandard.com/section/4-1-array-to-pointer-conversion/).

  (Clang-Tidy original name: hicpp-no-array-decay)

#### Tags
- /general/High Integrity C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_HIC_NDO
### Default
#### OriginalId=hicpp-new-delete-operators
#### Enabled=false
#### Warning=true
#### DisplayName=New Delete Operators
#### HelpText
  This check is an alias for [misc-new-delete-overloads](misc-new-delete-overloads.html). Implements [rule 12.3.1](http://www.codingstandard.com/section/12-3-free-store/) to ensure the new and delete operators have the correct signature.

  (Clang-Tidy original name: hicpp-new-delete-operators)

#### Tags
- /general/High Integrity C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_HIC_NM
### Default
#### OriginalId=hicpp-noexcept-move
#### Enabled=false
#### Warning=true
#### DisplayName=Noexcept Move
#### HelpText
  This check is an alias for [performance-noexcept-move-constructor](performance-noexcept-move-constructor.html). Checks [rule 12.5.4](http://www.codingstandard.com/rule/12-5-4-declare-noexcept-the-move-constructor-and-move-assignment-operator) to mark move assignment and move construction noexcept.

  (Clang-Tidy original name: hicpp-noexcept-move)

#### Tags
- /general/High Integrity C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_HIC_NM2
### Default
#### OriginalId=hicpp-no-malloc
#### Enabled=false
#### Warning=true
#### DisplayName=No Malloc
#### HelpText
  The hicpp-no-malloc check is an alias, please see [cppcoreguidelines-no-malloc](cppcoreguidelines-no-malloc.html) for more information. It enforces the [rule 5.3.2](http://www.codingstandard.com/rule/5-3-2-allocate-memory-using-new-and-release-it-using-delete/).

  (Clang-Tidy original name: hicpp-no-malloc)

#### Tags
- /general/High Integrity C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_HIC_NP
### Default
#### OriginalId=hicpp-named-parameter
#### Enabled=false
#### Warning=true
#### DisplayName=Named Parameter
#### HelpText
  This check is an alias for [readability-named-parameter](readability-named-parameter.html).

  Implements [rule 8.2.1](http://www.codingstandard.com/rule/8-2-1-make-parameter-names-absent-or-identical-in-all-declarations/).

  (Clang-Tidy original name: hicpp-named-parameter)

#### Tags
- /general/High Integrity C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_HIC_SA
### Default
#### OriginalId=hicpp-static-assert
#### Enabled=false
#### Warning=true
#### DisplayName=Static Assert
#### HelpText
  The hicpp-static-assert check is an alias, please see [misc-static-assert](misc-static-assert.html) for more information. It enforces the [rule 7.1.10](http://www.codingstandard.com/rule/6-1-1-enclose-the-body-of-a-selection-or-an-iteration-statement-in-a-compound-statement/).

  (Clang-Tidy original name: hicpp-static-assert)

#### Tags
- /general/High Integrity C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_HIC_SB
### Default
#### OriginalId=hicpp-signed-bitwise
#### Enabled=false
#### Warning=true
#### DisplayName=Signed Bitwise
#### HelpText
  Finds uses of bitwise operations on signed integer types, which may lead to undefined or implementation defined behaviour.

  The according rule is defined in the [High Integrity C++ Standard, Section 5.6.1](http://www.codingstandard.com/section/5-6-shift-operators/).

  ##### Options

  IgnorePositiveIntegerLiterals     

  If this option is set to true, the check will not warn on bitwise operations with positive integer literals, e.g. ~0, 2 << 1, etc. Default value is false.

  (Clang-Tidy original name: hicpp-signed-bitwise)

#### Tags
- /general/High Integrity C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_HIC_SMF
### Default
#### OriginalId=hicpp-special-member-functions
#### Enabled=false
#### Warning=true
#### DisplayName=Special Member Functions
#### HelpText
  This check is an alias for [cppcoreguidelines-special-member-functions](cppcoreguidelines-special-member-functions.html). Checks that special member functions have the correct signature, according to [rule 12.5.7](http://www.codingstandard.com/rule/12-5-7-declare-assignment-operators-with-the-ref-qualifier/).

  (Clang-Tidy original name: hicpp-special-member-functions)

#### Tags
- /general/High Integrity C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_HIC_UA
### Default
#### OriginalId=hicpp-use-auto
#### Enabled=false
#### Warning=true
#### DisplayName=Use Auto
#### HelpText
  The hicpp-use-auto check is an alias, please see [modernize-use-auto](modernize-use-auto.html) for more information. It enforces the [rule 7.1.8](http://www.codingstandard.com/rule/7-1-8-use-auto-id-expr-when-declaring-a-variable-to-have-the-same-type-as-its-initializer-function-call/).

  (Clang-Tidy original name: hicpp-use-auto)

#### Tags
- /general/High Integrity C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_HIC_UC
### Default
#### OriginalId=hicpp-undelegated-constructor
#### Enabled=false
#### Warning=true
#### DisplayName=Undelegated Constructor
#### HelpText
  This check is an alias for [bugprone-undelegated-constructor](bugprone-undelegated-constructor.html). Partially implements [rule 12.4.5](http://www.codingstandard.com/rule/12-4-5-use-delegating-constructors-to-reduce-code-duplication/) to find misplaced constructor calls inside a constructor.

  ``` cpp
  struct Ctor {
    Ctor();
    Ctor(int);
    Ctor(int, int);
    Ctor(Ctor *i) {
      // All Ctor() calls result in a temporary object
      Ctor(); // did you intend to call a delegated constructor?
      Ctor(0); // did you intend to call a delegated constructor?
      Ctor(1, 2); // did you intend to call a delegated constructor?
      foo();
    }
  };

  ```


  (Clang-Tidy original name: hicpp-undelegated-constructor)

#### Tags
- /general/High Integrity C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_HIC_UE
### Default
#### OriginalId=hicpp-use-emplace
#### Enabled=false
#### Warning=true
#### DisplayName=Use Emplace
#### HelpText
  The hicpp-use-emplace check is an alias, please see [modernize-use-emplace](modernize-use-emplace.html) for more information. It enforces the [rule 17.4.2](http://www.codingstandard.com/rule/17-4-2-use-api-calls-that-construct-objects-in-place/).

  (Clang-Tidy original name: hicpp-use-emplace)

#### Tags
- /general/High Integrity C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_HIC_UED
### Default
#### OriginalId=hicpp-use-equals-default
#### Enabled=false
#### Warning=true
#### DisplayName=Use Equals Default
#### HelpText
  This check is an alias for [modernize-use-equals-default](modernize-use-equals-default.html). Implements [rule 12.5.1](http://www.codingstandard.com/rule/12-5-1-define-explicitly-default-or-delete-implicit-special-member-functions-of-concrete-classes/) to explicitly default special member functions.

  (Clang-Tidy original name: hicpp-use-equals-default)

#### Tags
- /general/High Integrity C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_HIC_UED2
### Default
#### OriginalId=hicpp-use-equals-delete
#### Enabled=false
#### Warning=true
#### DisplayName=Use Equals Delete
#### HelpText
  This check is an alias for [modernize-use-equals-delete](modernize-use-equals-delete.html). Implements [rule 12.5.1](http://www.codingstandard.com/rule/12-5-1-define-explicitly-default-or-delete-implicit-special-member-functions-of-concrete-classes/) to explicitly default or delete special member functions.

  (Clang-Tidy original name: hicpp-use-equals-delete)

#### Tags
- /general/High Integrity C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_HIC_ULS
### Default
#### OriginalId=hicpp-uppercase-literal-suffix
#### Enabled=false
#### Warning=true
#### DisplayName=Uppercase Literal Suffix
#### HelpText
  The hicpp-uppercase-literal-suffix check is an alias, please see [readability-uppercase-literal-suffix](readability-uppercase-literal-suffix.html) for more information.

  (Clang-Tidy original name: hicpp-uppercase-literal-suffix)

#### Tags
- /general/High Integrity C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_HIC_UN
### Default
#### OriginalId=hicpp-use-noexcept
#### Enabled=false
#### Warning=true
#### DisplayName=Use Noexcept
#### HelpText
  The hicpp-use-noexcept check is an alias, please see [modernize-use-noexcept](modernize-use-noexcept.html) for more information. It enforces the [rule 1.3.5](http://www.codingstandard.com/rule/1-3-5-do-not-use-throw-exception-specifications/).

  (Clang-Tidy original name: hicpp-use-noexcept)

#### Tags
- /general/High Integrity C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_HIC_UN2
### Default
#### OriginalId=hicpp-use-nullptr
#### Enabled=false
#### Warning=true
#### DisplayName=Use Nullptr
#### HelpText
  The hicpp-use-nullptr check is an alias, please see [modernize-use-nullptr](modernize-use-nullptr.html) for more information. It enforces the [rule 2.5.3](http://www.codingstandard.com/rule/2-5-3-use-nullptr-for-the-null-pointer-constant/).

  (Clang-Tidy original name: hicpp-use-nullptr)

#### Tags
- /general/High Integrity C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_HIC_UO
### Default
#### OriginalId=hicpp-use-override
#### Enabled=false
#### Warning=true
#### DisplayName=Use Override
#### HelpText
  This check is an alias for [modernize-use-override](modernize-use-override.html). Implements [rule 10.2.1](http://www.codingstandard.com/section/10-2-virtual-functions/) to declare a virtual function override when overriding.

  (Clang-Tidy original name: hicpp-use-override)

#### Tags
- /general/High Integrity C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_HIC_V
### Default
#### OriginalId=hicpp-vararg
#### Enabled=false
#### Warning=true
#### DisplayName=Vararg
#### HelpText
  The hicpp-vararg check is an alias, please see [cppcoreguidelines-pro-type-vararg](cppcoreguidelines-pro-type-vararg.html) for more information. It enforces the [rule 14.1.1](http://www.codingstandard.com/section/14-1-template-declarations/).

  (Clang-Tidy original name: hicpp-vararg)

#### Tags
- /general/High Integrity C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_KRN_MCE
### Default
#### OriginalId=linuxkernel-must-check-errs
#### Enabled=false
#### Warning=true
#### DisplayName=Must Check Errs
#### HelpText
  Checks Linux kernel code to see if it uses the results from the functions in linux/err.h. Also checks to see if code uses the results from functions that directly return a value from one of these error functions.

  This is important in the Linux kernel because ERR_PTR, PTR_ERR, IS_ERR, IS_ERR_OR_NULL, ERR_CAST, and PTR_ERR_OR_ZERO return values must be checked, since positive pointers and negative error codes are being used in the same context. These functions are marked with __attribute__((warn_unused_result)), but some kernel versions do not have this warning enabled for clang.

  Examples:

  ``` cpp
  /* Trivial unused call to an ERR function */
  PTR_ERR_OR_ZERO(some_function_call());

  /* A function that returns ERR_PTR. */
  void *fn() { ERR_PTR(-EINVAL); }

  /* An invalid use of fn. */
  fn();

  ```


  (Clang-Tidy original name: linuxkernel-must-check-errs)

#### Tags
- /general/Linux Kernel
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_LLC_CN
### Default
#### OriginalId=llvmlibc-callee-namespace
#### Enabled=false
#### Warning=true
#### DisplayName=Callee Namespace
#### HelpText
  Checks all calls resolve to functions within __llvm_libc namespace.

  ``` cpp
  namespace __llvm_libc {

  // Allow calls with the fully qualified name.
  __llvm_libc::strlen("hello");

  // Allow calls to compiler provided functions.
  (void)__builtin_abs(-1);

  // Bare calls are allowed as long as they resolve to the correct namespace.
  strlen("world");

  // Disallow calling into functions in the global namespace.
  ::strlen("!");

  } // namespace __llvm_libc

  ```


  (Clang-Tidy original name: llvmlibc-callee-namespace)

#### Tags
- /general/LLVM-libc
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_LLC_IIN
### Default
#### OriginalId=llvmlibc-implementation-in-namespace
#### Enabled=false
#### Warning=true
#### DisplayName=Implementation In Namespace
#### HelpText
  Checks that all declarations in the llvm-libc implementation are within the correct namespace.

  ``` cpp
  // Correct: implementation inside the correct namespace.
  namespace __llvm_libc {
      void LLVM_LIBC_ENTRYPOINT(strcpy)(char *dest, const char *src) {}
      // Namespaces within __llvm_libc namespace are allowed.
      namespace inner{
          int localVar = 0;
      }
      // Functions with C linkage are allowed.
      extern "C" void str_fuzz(){}
  }

  // Incorrect: implementation not in a namespace.
  void LLVM_LIBC_ENTRYPOINT(strcpy)(char *dest, const char *src) {}

  // Incorrect: outer most namespace is not correct.
  namespace something_else {
      void LLVM_LIBC_ENTRYPOINT(strcpy)(char *dest, const char *src) {}
  }

  ```


  (Clang-Tidy original name: llvmlibc-implementation-in-namespace)

#### Tags
- /general/LLVM-libc
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_LLC_RSLH
### Default
#### OriginalId=llvmlibc-restrict-system-libc-headers
#### Enabled=false
#### Warning=true
#### DisplayName=Restrict System Libc Headers
#### HelpText
  Finds includes of system libc headers not provided by the compiler within llvm-libc implementations.

  ``` cpp
  #include <stdio.h>            // Not allowed because it is part of system libc.
  #include <stddef.h>           // Allowed because it is provided by the compiler.
  #include "internal/stdio.h"   // Allowed because it is NOT part of system libc.

  ```


  This check is necessary because accidentally including system libc headers can lead to subtle and hard to detect bugs. For example consider a system libc whose dirent struct has slightly different field ordering than llvm-libc. While this will compile successfully, this can cause issues during runtime because they are ABI incompatible.

  ##### Options

  Includes     

  A string containing a comma separated glob list of allowed include filenames. Similar to the -checks glob list for running clang-tidy itself, the two wildcard characters are * and -, to include and exclude globs, respectively. The default is -*, which disallows all includes.

  This can be used to allow known safe includes such as Linux development headers. See [portability-restrict-system-includes](portability-restrict-system-includes.html) for more details.

  (Clang-Tidy original name: llvmlibc-restrict-system-libc-headers)

#### Tags
- /general/LLVM-libc
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_LLV_EAR
### Default
#### OriginalId=llvm-else-after-return
#### Enabled=false
#### Warning=true
#### DisplayName=Else After Return
#### HelpText
  The llvm-else-after-return check is an alias, please see [readability-else-after-return](readability-else-after-return.html) for more information.

  (Clang-Tidy original name: llvm-else-after-return)

#### Tags
- /general/LLVM
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_LLV_HG
### Default
#### OriginalId=llvm-header-guard
#### Enabled=false
#### Warning=true
#### DisplayName=Header Guard
#### HelpText
  Finds and fixes header guards that do not adhere to LLVM style.

  ##### Options

  HeaderFileExtensions     

  A comma-separated list of filename extensions of header files (the filename extensions should not include “.” prefix). Default is “h,hh,hpp,hxx”. For header files without an extension, use an empty string (if there are no other desired extensions) or leave an empty element in the list. e.g., “h,hh,hpp,hxx,” (note the trailing comma).

  (Clang-Tidy original name: llvm-header-guard)

#### Tags
- /general/LLVM
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_LLV_IO
### Default
#### OriginalId=llvm-include-order
#### Enabled=false
#### Warning=true
#### DisplayName=Include Order
#### HelpText
  Checks the correct order of \#includes.

  See <https://llvm.org/docs/CodingStandards.html\#include-style>

  (Clang-Tidy original name: llvm-include-order)

#### Tags
- /general/LLVM
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_LLV_NC
### Default
#### OriginalId=llvm-namespace-comment
#### Enabled=false
#### Warning=true
#### DisplayName=Namespace Comment
#### HelpText
  google-readability-namespace-comments redirects here as an alias for this check.

  Checks that long namespaces have a closing comment.

  <https://llvm.org/docs/CodingStandards.html\#namespace-indentation>

  <https://google.github.io/styleguide/cppguide.html\#Namespaces>

  ``` cpp
  namespace n1 {
  void f();
  }

  // becomes

  namespace n1 {
  void f();
  }  // namespace n1

  ```


  ##### Options

  ShortNamespaceLines     

  Requires the closing brace of the namespace definition to be followed by a closing comment if the body of the namespace has more than ShortNamespaceLines lines of code. The value is an unsigned integer that defaults to 1U.

  SpacesBeforeComments     

  An unsigned integer specifying the number of spaces before the comment closing a namespace definition. Default is 1U.

  (Clang-Tidy original name: llvm-namespace-comment)

#### Tags
- /general/LLVM
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_LLV_PIODCIC
### Default
#### OriginalId=llvm-prefer-isa-or-dyn-cast-in-conditionals
#### Enabled=false
#### Warning=true
#### DisplayName=Prefer Isa Or Dyn Cast In Conditionals
#### HelpText
  Looks at conditionals and finds and replaces cases of cast<>, which will assert rather than return a null pointer, and dyn_cast<> where the return value is not captured. Additionally, finds and replaces cases that match the pattern var && isa<X>(var), where var is evaluated twice.

  ``` cpp
  // Finds these:
  if (auto x = cast<X>(y)) {}
  // is replaced by:
  if (auto x = dyn_cast<X>(y)) {}

  if (cast<X>(y)) {}
  // is replaced by:
  if (isa<X>(y)) {}

  if (dyn_cast<X>(y)) {}
  // is replaced by:
  if (isa<X>(y)) {}

  if (var && isa<T>(var)) {}
  // is replaced by:
  if (isa_and_nonnull<T>(var.foo())) {}

  // Other cases are ignored, e.g.:
  if (auto f = cast<Z>(y)->foo()) {}
  if (cast<Z>(y)->foo()) {}
  if (X.cast(y)) {}

  ```


  (Clang-Tidy original name: llvm-prefer-isa-or-dyn-cast-in-conditionals)

#### Tags
- /general/LLVM
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_LLV_PROU
### Default
#### OriginalId=llvm-prefer-register-over-unsigned
#### Enabled=false
#### Warning=true
#### DisplayName=Prefer Register Over Unsigned
#### HelpText
  Finds historical use of unsigned to hold vregs and physregs and rewrites them to use Register.

  Currently this works by finding all variables of unsigned integer type whose initializer begins with an implicit cast from Register to unsigned.

  ``` cpp
  void example(MachineOperand &MO) {
    unsigned Reg = MO.getReg();
    ...
  }

  ```


  becomes:

  ``` cpp
  void example(MachineOperand &MO) {
    Register Reg = MO.getReg();
    ...
  }

  ```


  (Clang-Tidy original name: llvm-prefer-register-over-unsigned)

#### Tags
- /general/LLVM
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_LLV_QA
### Default
#### OriginalId=llvm-qualified-auto
#### Enabled=false
#### Warning=true
#### DisplayName=Qualified Auto
#### HelpText
  The llvm-qualified-auto check is an alias, please see [readability-qualified-auto](readability-qualified-auto.html) for more information.

  (Clang-Tidy original name: llvm-qualified-auto)

#### Tags
- /general/LLVM
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_LLV_TL
### Default
#### OriginalId=llvm-twine-local
#### Enabled=false
#### Warning=true
#### DisplayName=Twine Local
#### HelpText
  Looks for local Twine variables which are prone to use after frees and should be generally avoided.

  ``` cpp
  static Twine Moo = Twine("bark") + "bah";

  // becomes

  static std::string Moo = (Twine("bark") + "bah").str();

  ```


  (Clang-Tidy original name: llvm-twine-local)

#### Tags
- /general/LLVM
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MDR_AB
### Default
#### OriginalId=modernize-avoid-bind
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Bind
#### HelpText
  The check finds uses of std::bind and boost::bind and replaces them with lambdas. Lambdas will use value-capture unless reference capture is explicitly requested with std::ref or boost::ref.

  It supports arbitrary callables including member functions, function objects, and free functions, and all variations thereof. Anything that you can pass to the first argument of bind should be diagnosable. Currently, the only known case where a fix-it is unsupported is when the same placeholder is specified multiple times in the parameter list.

  Given:

  ``` cpp
  int add(int x, int y) { return x + y; }

  ```


  Then:

  ``` cpp
  void f() {
    int x = 2;
    auto clj = std::bind(add, x, _1);
  }

  ```


  is replaced by:

  ``` cpp
  void f() {
    int x = 2;
    auto clj = [=](auto && arg1) { return add(x, arg1); };
  }

  ```


  std::bind can be hard to read and can result in larger object files and binaries due to type information that will not be produced by equivalent lambdas.

  ##### Options

  PermissiveParameterList     

  If the option is set to true, the check will append auto&&... to the end of every placeholder parameter list. Without this, it is possible for a fix-it to perform an incorrect transformation in the case where the result of the bind is used in the context of a type erased functor such as std::function which allows mismatched arguments. For example:

  ``` cpp
  int add(int x, int y) { return x + y; }
  int foo() {
    std::function<int(int,int)> ignore_args = std::bind(add, 2, 2);
    return ignore_args(3, 3);
  }

  ```


  is valid code, and returns 4. The actual values passed to ignore_args are simply ignored. Without PermissiveParameterList, this would be transformed into

  ``` cpp
  int add(int x, int y) { return x + y; }
  int foo() {
    std::function<int(int,int)> ignore_args = [] { return add(2, 2); }
    return ignore_args(3, 3);
  }

  ```


  which will _not_ compile, since the lambda does not contain an operator() that that accepts 2 arguments. With permissive parameter list, it instead generates

  ``` cpp
  int add(int x, int y) { return x + y; }
  int foo() {
    std::function<int(int,int)> ignore_args = [](auto&&...) { return add(2, 2); }
    return ignore_args(3, 3);
  }

  ```


  which is correct.

  This check requires using C++14 or higher to run.

  (Clang-Tidy original name: modernize-avoid-bind)

#### Tags
- /general/Modernize
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MDR_ACA
### Default
#### OriginalId=modernize-avoid-c-arrays
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid C Arrays
#### HelpText
  cppcoreguidelines-avoid-c-arrays redirects here as an alias for this check.

  hicpp-avoid-c-arrays redirects here as an alias for this check.

  Finds C-style array types and recommend to use std::array<> / std::vector<>. All types of C arrays are diagnosed.

  However, fix-it are potentially dangerous in header files and are therefore not emitted right now.

  ``` cpp
  int a[] = {1, 2}; // warning: do not declare C-style arrays, use std::array<> instead

  int b[1]; // warning: do not declare C-style arrays, use std::array<> instead

  void foo() {
    int c[b[0]]; // warning: do not declare C VLA arrays, use std::vector<> instead
  }

  template <typename T, int Size>
  class array {
    T d[Size]; // warning: do not declare C-style arrays, use std::array<> instead

    int e[1]; // warning: do not declare C-style arrays, use std::array<> instead
  };

  array<int[4], 2> d; // warning: do not declare C-style arrays, use std::array<> instead

  using k = int[4]; // warning: do not declare C-style arrays, use std::array<> instead

  ```


  However, the extern "C" code is ignored, since it is common to share such headers between C code, and C++ code.

  ``` cpp
  // Some header
  extern "C" {

  int f[] = {1, 2}; // not diagnosed

  int j[1]; // not diagnosed

  inline void bar() {
    {
      int j[j[0]]; // not diagnosed
    }
  }

  }

  ```


  Similarly, the main() function is ignored. Its second and third parameters can be either char* argv[] or char** argv, but can not be std::array<>.

  (Clang-Tidy original name: modernize-avoid-c-arrays)

#### Tags
- /general/Modernize
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MDR_CNN
### Default
#### OriginalId=modernize-concat-nested-namespaces
#### Enabled=true
#### Warning=true
#### DisplayName=Concat Nested Namespaces
#### HelpText
  Checks for use of nested namespaces such as namespace a { namespace b { ... } } and suggests changing to the more concise syntax introduced in C++17: namespace a::b { ... }. Inline namespaces are not modified.

  For example:

  ``` cpp
  namespace n1 {
  namespace n2 {
  void t();
  }
  }

  namespace n3 {
  namespace n4 {
  namespace n5 {
  void t();
  }
  }
  namespace n6 {
  namespace n7 {
  void t();
  }
  }
  }

  ```


  Will be modified to:

  ``` cpp
  namespace n1::n2 {
  void t();
  }

  namespace n3 {
  namespace n4::n5 {
  void t();
  }
  namespace n6::n7 {
  void t();
  }
  }

  ```


  (Clang-Tidy original name: modernize-concat-nested-namespaces)

#### Tags
- /general/Modernize
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MDR_DH
### Default
#### OriginalId=modernize-deprecated-headers
#### Enabled=true
#### Warning=true
#### DisplayName=Deprecated Headers
#### HelpText
  Some headers from C library were deprecated in C++ and are no longer welcome in C++ codebases. Some have no effect in C++. For more details refer to the C++ 14 Standard [depr.c.headers] section.

  This check replaces C standard library headers with their C++ alternatives and removes redundant ones.

  Important note: the Standard doesn’t guarantee that the C++ headers declare all the same functions in the global namespace. The check in its current form can break the code that uses library symbols from the global namespace.

    * <assert.h>
    * <complex.h>
    * <ctype.h>
    * <errno.h>
    * <fenv.h> // deprecated since C++11
    * <float.h>
    * <inttypes.h>
    * <limits.h>
    * <locale.h>
    * <math.h>
    * <setjmp.h>
    * <signal.h>
    * <stdarg.h>
    * <stddef.h>
    * <stdint.h>
    * <stdio.h>
    * <stdlib.h>
    * <string.h>
    * <tgmath.h> // deprecated since C++11
    * <time.h>
    * <uchar.h> // deprecated since C++11
    * <wchar.h>
    * <wctype.h>



  If the specified standard is older than C++11 the check will only replace headers deprecated before C++11, otherwise – every header that appeared in the previous list.

  These headers don’t have effect in C++:

    * <iso646.h>
    * <stdalign.h>
    * <stdbool.h>



  (Clang-Tidy original name: modernize-deprecated-headers)

#### Tags
- /general/Modernize
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MDR_DIBA
### Default
#### OriginalId=modernize-deprecated-ios-base-aliases
#### Enabled=true
#### Warning=true
#### DisplayName=Deprecated Ios Base Aliases
#### HelpText
  Detects usage of the deprecated member types of std::ios_base and replaces those that have a non-deprecated equivalent.

  Deprecated member type | Replacement  
  ---|---  
  std::ios_base::io_state | std::ios_base::iostate  
  std::ios_base::open_mode | std::ios_base::openmode  
  std::ios_base::seek_dir | std::ios_base::seekdir  
  std::ios_base::streamoff |   
  std::ios_base::streampos |   

   

  (Clang-Tidy original name: modernize-deprecated-ios-base-aliases)

#### Tags
- /general/Modernize
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MDR_LC
### Default
#### OriginalId=modernize-loop-convert
#### Enabled=true
#### Warning=true
#### DisplayName=Loop Convert
#### HelpText
  This check converts for(...; ...; ...) loops to use the new range-based loops in C++11.

  Three kinds of loops can be converted:

    * Loops over statically allocated arrays.
    * Loops over containers, using iterators.
    * Loops over array-like containers, using operator[] and at().



  ##### MinConfidence option

  ###### risky

  In loops where the container expression is more complex than just a reference to a declared expression (a variable, function, enum, etc.), and some part of it appears elsewhere in the loop, we lower our confidence in the transformation due to the increased risk of changing semantics. Transformations for these loops are marked as risky, and thus will only be converted if the minimum required confidence level is set to risky.

  ``` cpp
  int arr[10][20];
  int l = 5;

  for (int j = 0; j < 20; ++j)
    int k = arr[l][j] + l; // using l outside arr[l] is considered risky

  for (int i = 0; i < obj.getVector().size(); ++i)
    obj.foo(10); // using 'obj' is considered risky

  ```


  See [Range-based loops evaluate end() only once](\#incorrectriskytransformation) for an example of an incorrect transformation when the minimum required confidence level is set to risky.

  ###### reasonable (Default)

  If a loop calls .end() or .size() after each iteration, the transformation for that loop is marked as reasonable, and thus will be converted if the required confidence level is set to reasonable (default) or lower.

  ``` cpp
  // using size() is considered reasonable
  for (int i = 0; i < container.size(); ++i)
    cout << container[i];

  ```


  ###### safe

  Any other loops that do not match the above criteria to be marked as risky or reasonable are marked safe, and thus will be converted if the required confidence level is set to safe or lower.

  ``` cpp
  int arr[] = {1,2,3};

  for (int i = 0; i < 3; ++i)
    cout << arr[i];

  ```


  ##### Example

  Original:

  ``` cpp
  const int N = 5;
  int arr[] = {1,2,3,4,5};
  vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);

  // safe conversion
  for (int i = 0; i < N; ++i)
    cout << arr[i];

  // reasonable conversion
  for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
    cout << *it;

  // reasonable conversion
  for (int i = 0; i < v.size(); ++i)
    cout << v[i];

  ```


  After applying the check with minimum confidence level set to reasonable (default):

  ``` cpp
  const int N = 5;
  int arr[] = {1,2,3,4,5};
  vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);

  // safe conversion
  for (auto & elem : arr)
    cout << elem;

  // reasonable conversion
  for (auto & elem : v)
    cout << elem;

  // reasonable conversion
  for (auto & elem : v)
    cout << elem;

  ```


  ##### Reverse Iterator Support

  The converter is also capable of transforming iterator loops which use rbegin and rend for looping backwards over a container. Out of the box this will automatically happen in C++20 mode using the ranges library, however the check can be configured to work without C++20 by specifying a function to reverse a range and optionally the header file where that function lives.

  UseCxx20ReverseRanges     

  When set to true convert loops when in C++20 or later mode using std::ranges::reverse_view. Default value is true.

  MakeReverseRangeFunction     

  Specify the function used to reverse an iterator pair, the function should accept a class with rbegin and rend methods and return a class with begin and end methods methods that call the rbegin and rend methods respectively. Common examples are ranges::reverse_view and llvm::reverse. Default value is an empty string.

  MakeReverseRangeHeader     

  Specifies the header file where [MakeReverseRangeFunction](\#cmdoption-arg-makereverserangefunction) is declared. For the previous examples this option would be set to range/v3/view/reverse.hpp and llvm/ADT/STLExtras.h respectively. If this is an empty string and [MakeReverseRangeFunction](\#cmdoption-arg-makereverserangefunction) is set, the check will proceed on the assumption that the function is already available in the translation unit. This can be wrapped in angle brackets to signify to add the include as a system include. Default value is an empty string.

  IncludeStyle     

  A string specifying which include-style is used, llvm or google. Default is llvm.

  ##### Limitations

  There are certain situations where the tool may erroneously perform transformations that remove information and change semantics. Users of the tool should be aware of the behaviour and limitations of the check outlined by the cases below.

  ###### Comments inside loop headers

  Comments inside the original loop header are ignored and deleted when transformed.

  ``` cpp
  for (int i = 0; i < N; /* This will be deleted */ ++i) { }

  ```


  ###### Range-based loops evaluate end() only once

  The C++11 range-based for loop calls .end() only once during the initialization of the loop. If in the original loop .end() is called after each iteration the semantics of the transformed loop may differ.

  ``` cpp
  // The following is semantically equivalent to the C++11 range-based for loop,
  // therefore the semantics of the header will not change.
  for (iterator it = container.begin(), e = container.end(); it != e; ++it) { }

  // Instead of calling .end() after each iteration, this loop will be
  // transformed to call .end() only once during the initialization of the loop,
  // which may affect semantics.
  for (iterator it = container.begin(); it != container.end(); ++it) { }

  ```


  As explained above, calling member functions of the container in the body of the loop is considered risky. If the called member function modifies the container the semantics of the converted loop will differ due to .end() being called only once.

  ``` cpp
  bool flag = false;
  for (vector<T>::iterator it = vec.begin(); it != vec.end(); ++it) {
    // Add a copy of the first element to the end of the vector.
    if (!flag) {
      // This line makes this transformation 'risky'.
      vec.push_back(*it);
      flag = true;
    }
    cout << *it;
  }

  ```


  The original code above prints out the contents of the container including the newly added element while the converted loop, shown below, will only print the original contents and not the newly added element.

  ``` cpp
  bool flag = false;
  for (auto & elem : vec) {
    // Add a copy of the first element to the end of the vector.
    if (!flag) {
      // This line makes this transformation 'risky'
      vec.push_back(elem);
      flag = true;
    }
    cout << elem;
  }

  ```


  Semantics will also be affected if .end() has side effects. For example, in the case where calls to .end() are logged the semantics will change in the transformed loop if .end() was originally called after each iteration.

  ``` cpp
  iterator end() {
    num_of_end_calls++;
    return container.end();
  }

  ```


  ###### Overloaded operator->() with side effects

  Similarly, if operator->() was overloaded to have side effects, such as logging, the semantics will change. If the iterator’s operator->() was used in the original loop it will be replaced with <container element>.<member> instead due to the implicit dereference as part of the range-based for loop. Therefore any side effect of the overloaded operator->() will no longer be performed.

  ``` cpp
  for (iterator it = c.begin(); it != c.end(); ++it) {
    it->func(); // Using operator->()
  }
  // Will be transformed to:
  for (auto & elem : c) {
    elem.func(); // No longer using operator->()
  }

  ```


  ###### Pointers and references to containers

  While most of the check’s risk analysis is dedicated to determining whether the iterator or container was modified within the loop, it is possible to circumvent the analysis by accessing and modifying the container through a pointer or reference.

  If the container were directly used instead of using the pointer or reference the following transformation would have only been applied at the risky level since calling a member function of the container is considered risky. The check cannot identify expressions associated with the container that are different than the one used in the loop header, therefore the transformation below ends up being performed at the safe level.

  ``` cpp
  vector<int> vec;

  vector<int> *ptr = &vec;
  vector<int> &ref = vec;

  for (vector<int>::iterator it = vec.begin(), e = vec.end(); it != e; ++it) {
    if (!flag) {
      // Accessing and modifying the container is considered risky, but the risk
      // level is not raised here.
      ptr->push_back(*it);
      ref.push_back(*it);
      flag = true;
    }
  }

  ```


  ###### OpenMP

  As range-based for loops are only available since OpenMP 5, this check should not been used on code with a compatibility requirements of OpenMP prior to version 5. It is **intentional** that this check does not make any attempts to exclude incorrect diagnostics on OpenMP for loops prior to OpenMP 5.

  To prevent this check to be applied (and to break) OpenMP for loops but still be applied to non-OpenMP for loops the usage of NOLINT (see [Suppressing Undesired Diagnostics](../index.html\#clang-tidy-nolint)) on the specific for loops is recommended.

  (Clang-Tidy original name: modernize-loop-convert)

#### Tags
- /general/Modernize
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MDR_MS
### Default
#### OriginalId=modernize-make-shared
#### Enabled=true
#### Warning=true
#### DisplayName=Make Shared
#### HelpText
  This check finds the creation of std::shared_ptr objects by explicitly calling the constructor and a new expression, and replaces it with a call to std::make_shared.

  ``` cpp
  auto my_ptr = std::shared_ptr<MyPair>(new MyPair(1, 2));

  // becomes

  auto my_ptr = std::make_shared<MyPair>(1, 2);

  ```


  This check also finds calls to std::shared_ptr::reset() with a new expression, and replaces it with a call to std::make_shared.

  ``` cpp
  my_ptr.reset(new MyPair(1, 2));

  // becomes

  my_ptr = std::make_shared<MyPair>(1, 2);

  ```


  ##### Options

  MakeSmartPtrFunction     

  A string specifying the name of make-shared-ptr function. Default is std::make_shared.

  MakeSmartPtrFunctionHeader     

  A string specifying the corresponding header of make-shared-ptr function. Default is memory.

  IncludeStyle     

  A string specifying which include-style is used, llvm or google. Default is llvm.

  IgnoreMacros     

  If set to true, the check will not give warnings inside macros. Default is true.

  IgnoreDefaultInitialization     

  If set to non-zero, the check does not suggest edits that will transform default initialization into value initialization, as this can cause performance regressions. Default is 1.

  (Clang-Tidy original name: modernize-make-shared)

#### Tags
- /general/Modernize
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MDR_MU
### Default
#### OriginalId=modernize-make-unique
#### Enabled=true
#### Warning=true
#### DisplayName=Make Unique
#### HelpText
  This check finds the creation of std::unique_ptr objects by explicitly calling the constructor and a new expression, and replaces it with a call to std::make_unique, introduced in C++14.

  ``` cpp
  auto my_ptr = std::unique_ptr<MyPair>(new MyPair(1, 2));

  // becomes

  auto my_ptr = std::make_unique<MyPair>(1, 2);

  ```


  This check also finds calls to std::unique_ptr::reset() with a new expression, and replaces it with a call to std::make_unique.

  ``` cpp
  my_ptr.reset(new MyPair(1, 2));

  // becomes

  my_ptr = std::make_unique<MyPair>(1, 2);

  ```


  ##### Options

  MakeSmartPtrFunction     

  A string specifying the name of make-unique-ptr function. Default is std::make_unique.

  MakeSmartPtrFunctionHeader     

  A string specifying the corresponding header of make-unique-ptr function. Default is <memory>.

  IncludeStyle     

  A string specifying which include-style is used, llvm or google. Default is llvm.

  IgnoreMacros     

  If set to true, the check will not give warnings inside macros. Default is true.

  IgnoreDefaultInitialization     

  If set to non-zero, the check does not suggest edits that will transform default initialization into value initialization, as this can cause performance regressions. Default is 1.

  (Clang-Tidy original name: modernize-make-unique)

#### Tags
- /general/Modernize
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MDR_PBV
### Default
#### OriginalId=modernize-pass-by-value
#### Enabled=true
#### Warning=true
#### DisplayName=Pass By Value
#### HelpText
  With move semantics added to the language and the standard library updated with move constructors added for many types it is now interesting to take an argument directly by value, instead of by const-reference, and then copy. This check allows the compiler to take care of choosing the best way to construct the copy.

  The transformation is usually beneficial when the calling code passes an _rvalue_ and assumes the move construction is a cheap operation. This short example illustrates how the construction of the value happens:

  ``` cpp
  void foo(std::string s);
  std::string get_str();

  void f(const std::string &str) {
    foo(str);       // lvalue  -> copy construction
    foo(get_str()); // prvalue -> move construction
  }

  ```


  Note

  Currently, only constructors are transformed to make use of pass-by-value. Contributions that handle other situations are welcome!

  ##### Pass-by-value in constructors

  Replaces the uses of const-references constructor parameters that are copied into class fields. The parameter is then moved with std::move().

  Since std::move() is a library function declared in <utility> it may be necessary to add this include. The check will add the include directive when necessary.

  ``` cpp
   #include <string>

   class Foo {
   public:
  -  Foo(const std::string &Copied, const std::string &ReadOnly)
  -    : Copied(Copied), ReadOnly(ReadOnly)
  +  Foo(std::string Copied, const std::string &ReadOnly)
  +    : Copied(std::move(Copied)), ReadOnly(ReadOnly)
     {}

   private:
     std::string Copied;
     const std::string &ReadOnly;
   };

   std::string get_cwd();

   void f(const std::string &Path) {
     // The parameter corresponding to 'get_cwd()' is move-constructed. By
     // using pass-by-value in the Foo constructor we managed to avoid a
     // copy-construction.
     Foo foo(get_cwd(), Path);
   }

  ```


  If the parameter is used more than once no transformation is performed since moved objects have an undefined state. It means the following code will be left untouched:

  ``` cpp
  #include <string>

  void pass(const std::string &S);

  struct Foo {
    Foo(const std::string &S) : Str(S) {
      pass(S);
    }

    std::string Str;
  };

  ```


  ###### Known limitations

  A situation where the generated code can be wrong is when the object referenced is modified before the assignment in the init-list through a “hidden” reference.

  Example:

  ``` cpp
   std::string s("foo");

   struct Base {
     Base() {
       s = "bar";
     }
   };

   struct Derived : Base {
  -  Derived(const std::string &S) : Field(S)
  +  Derived(std::string S) : Field(std::move(S))
     { }

     std::string Field;
   };

   void f() {
  -  Derived d(s); // d.Field holds "bar"
  +  Derived d(s); // d.Field holds "foo"
   }

  ```


  ###### Note about delayed template parsing

  When delayed template parsing is enabled, constructors part of templated contexts; templated constructors, constructors in class templates, constructors of inner classes of template classes, etc., are not transformed. Delayed template parsing is enabled by default on Windows as a Microsoft extension: [Clang Compiler User’s Manual - Microsoft extensions](https://clang.llvm.org/docs/UsersManual.html\#microsoft-extensions).

  Delayed template parsing can be enabled using the -fdelayed-template-parsing flag and disabled using -fno-delayed-template-parsing.

  Example:

  ``` cpp
    template <typename T> class C {
      std::string S;

    public:
  =  // using -fdelayed-template-parsing (default on Windows)
  =  C(const std::string &S) : S(S) {}

  +  // using -fno-delayed-template-parsing (default on non-Windows systems)
  +  C(std::string S) : S(std::move(S)) {}
    };

  ```


  See also

  For more information about the pass-by-value idiom, read: [Want Speed? Pass by Value](https://web.archive.org/web/20140205194657/http://cpp-next.com/archive/2009/08/want-speed-pass-by-value/).

  ##### Options

  IncludeStyle     

  A string specifying which include-style is used, llvm or google. Default is llvm.

  ValuesOnly     

  When true, the check only warns about copied parameters that are already passed by value. Default is false.

  (Clang-Tidy original name: modernize-pass-by-value)

#### Tags
- /general/Modernize
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MDR_RAP
### Default
#### OriginalId=modernize-replace-auto-ptr
#### Enabled=true
#### Warning=true
#### DisplayName=Replace Auto Ptr
#### HelpText
  This check replaces the uses of the deprecated class std::auto_ptr by std::unique_ptr (introduced in C++11). The transfer of ownership, done by the copy-constructor and the assignment operator, is changed to match std::unique_ptr usage by using explicit calls to std::move().

  Migration example:

  ``` cpp
  -void take_ownership_fn(std::auto_ptr<int> int_ptr);
  +void take_ownership_fn(std::unique_ptr<int> int_ptr);

   void f(int x) {
  -  std::auto_ptr<int> a(new int(x));
  -  std::auto_ptr<int> b;
  +  std::unique_ptr<int> a(new int(x));
  +  std::unique_ptr<int> b;

  -  b = a;
  -  take_ownership_fn(b);
  +  b = std::move(a);
  +  take_ownership_fn(std::move(b));
   }

  ```


  Since std::move() is a library function declared in <utility> it may be necessary to add this include. The check will add the include directive when necessary.

  ##### Known Limitations

    * If headers modification is not activated or if a header is not allowed to be changed this check will produce broken code (compilation error), where the headers’ code will stay unchanged while the code using them will be changed.
    * Client code that declares a reference to an std::auto_ptr coming from code that can’t be migrated (such as a header coming from a 3rd party library) will produce a compilation error after migration. This is because the type of the reference will be changed to std::unique_ptr but the type returned by the library won’t change, binding a reference to std::unique_ptr from an std::auto_ptr. This pattern doesn’t make much sense and usually std::auto_ptr are stored by value (otherwise what is the point in using them instead of a reference or a pointer?).



  ``` cpp
   // <3rd-party header...>
   std::auto_ptr<int> get_value();
   const std::auto_ptr<int> & get_ref();

   // <calling code (with migration)...>
  -std::auto_ptr<int> a(get_value());
  +std::unique_ptr<int> a(get_value()); // ok, unique_ptr constructed from auto_ptr

  -const std::auto_ptr<int> & p = get_ptr();
  +const std::unique_ptr<int> & p = get_ptr(); // won't compile

  ```


    * Non-instantiated templates aren’t modified.



  ``` cpp
  template <typename X>
  void f() {
      std::auto_ptr<X> p;
  }

  // only 'f<int>()' (or similar) will trigger the replacement.

  ```


  ##### Options

  IncludeStyle     

  A string specifying which include-style is used, llvm or google. Default is llvm.

  (Clang-Tidy original name: modernize-replace-auto-ptr)

#### Tags
- /general/Modernize
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MDR_RBIL
### Default
#### OriginalId=modernize-return-braced-init-list
#### Enabled=true
#### Warning=true
#### DisplayName=Return Braced Init List
#### HelpText
  Replaces explicit calls to the constructor in a return with a braced initializer list. This way the return type is not needlessly duplicated in the function definition and the return statement.

  ``` cpp
  Foo bar() {
    Baz baz;
    return Foo(baz);
  }

  // transforms to:

  Foo bar() {
    Baz baz;
    return {baz};
  }

  ```


  (Clang-Tidy original name: modernize-return-braced-init-list)

#### Tags
- /general/Modernize
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MDR_RDCAAM
### Default
#### OriginalId=modernize-replace-disallow-copy-and-assign-macro
#### Enabled=true
#### Warning=true
#### DisplayName=Replace Disallow Copy And Assign Macro
#### HelpText
  Finds macro expansions of DISALLOW_COPY_AND_ASSIGN(Type) and replaces them with a deleted copy constructor and a deleted assignment operator.

  Before the delete keyword was introduced in C++11 it was common practice to declare a copy constructor and an assignment operator as a private members. This effectively makes them unusable to the public API of a class.

  With the advent of the delete keyword in C++11 we can abandon the private access of the copy constructor and the assignment operator and delete the methods entirely.

  When running this check on a code like this:

  ``` cpp
  class Foo {
  private:
    DISALLOW_COPY_AND_ASSIGN(Foo);
  };

  ```


  It will be transformed to this:

  ``` cpp
  class Foo {
  private:
    Foo(const Foo &) = delete;
    const Foo &operator=(const Foo &) = delete;
  };

  ```


  ##### Known Limitations

    * Notice that the migration example above leaves the private access specification untouched. You might want to run the check [modernize-use-equals-delete](modernize-use-equals-delete.html) to get warnings for deleted functions in private sections.



  ##### Options

  MacroName     

  A string specifying the macro name whose expansion will be replaced. Default is DISALLOW_COPY_AND_ASSIGN.

  See: <https://en.cppreference.com/w/cpp/language/function\#Deleted_functions>

  (Clang-Tidy original name: modernize-replace-disallow-copy-and-assign-macro)

#### Tags
- /general/Modernize
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MDR_RRS
### Default
#### OriginalId=modernize-replace-random-shuffle
#### Enabled=true
#### Warning=true
#### DisplayName=Replace Random Shuffle
#### HelpText
  This check will find occurrences of std::random_shuffle and replace it with std::shuffle. In C++17 std::random_shuffle will no longer be available and thus we need to replace it.

  Below are two examples of what kind of occurrences will be found and two examples of what it will be replaced with.

  ``` cpp
  std::vector<int> v;

  // First example
  std::random_shuffle(vec.begin(), vec.end());

  // Second example
  std::random_shuffle(vec.begin(), vec.end(), randomFunc);

  ```


  Both of these examples will be replaced with:

  ``` cpp
  std::shuffle(vec.begin(), vec.end(), std::mt19937(std::random_device()()));

  ```


  The second example will also receive a warning that randomFunc is no longer supported in the same way as before so if the user wants the same functionality, the user will need to change the implementation of the randomFunc.

  One thing to be aware of here is that std::random_device is quite expensive to initialize. So if you are using the code in a performance critical place, you probably want to initialize it elsewhere. Another thing is that the seeding quality of the suggested fix is quite poor: std::mt19937 has an internal state of 624 32-bit integers, but is only seeded with a single integer. So if you require higher quality randomness, you should consider seeding better, for example:

  ``` cpp
  std::shuffle(v.begin(), v.end(), []() {
    std::mt19937::result_type seeds[std::mt19937::state_size];
    std::random_device device;
    std::uniform_int_distribution<typename std::mt19937::result_type> dist;
    std::generate(std::begin(seeds), std::end(seeds), [&] { return dist(device); });
    std::seed_seq seq(std::begin(seeds), std::end(seeds));
    return std::mt19937(seq);
  }());

  ```


  (Clang-Tidy original name: modernize-replace-random-shuffle)

#### Tags
- /general/Modernize
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MDR_RSL
### Default
#### OriginalId=modernize-raw-string-literal
#### Enabled=true
#### Warning=true
#### DisplayName=Raw String Literal
#### HelpText
  This check selectively replaces string literals containing escaped characters with raw string literals.

  Example:

  ``` cpp
  const char *const Quotes{"embedded \"quotes\""};
  const char *const Paragraph{"Line one.\nLine two.\nLine three.\n"};
  const char *const SingleLine{"Single line.\n"};
  const char *const TrailingSpace{"Look here -> \n"};
  const char *const Tab{"One\tTwo\n"};
  const char *const Bell{"Hello!\a  And welcome!"};
  const char *const Path{"C:\\Program Files\\Vendor\\Application.exe"};
  const char *const RegEx{"\\w\\([a-z]\\)"};

  ```


  becomes

  ``` cpp
  const char *const Quotes{R"(embedded "quotes")"};
  const char *const Paragraph{"Line one.\nLine two.\nLine three.\n"};
  const char *const SingleLine{"Single line.\n"};
  const char *const TrailingSpace{"Look here -> \n"};
  const char *const Tab{"One\tTwo\n"};
  const char *const Bell{"Hello!\a  And welcome!"};
  const char *const Path{R"(C:\Program Files\Vendor\Application.exe)"};
  const char *const RegEx{R"(\w\([a-z]\))"};

  ```


  The presence of any of the following escapes can cause the string to be converted to a raw string literal: \\, \', \", \?, and octal or hexadecimal escapes for printable ASCII characters.

  A string literal containing only escaped newlines is a common way of writing lines of text output. Introducing physical newlines with raw string literals in this case is likely to impede readability. These string literals are left unchanged.

  An escaped horizontal tab, form feed, or vertical tab prevents the string literal from being converted. The presence of a horizontal tab, form feed or vertical tab in source code is not visually obvious.

  (Clang-Tidy original name: modernize-raw-string-literal)

#### Tags
- /general/Modernize
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MDR_RVA
### Default
#### OriginalId=modernize-redundant-void-arg
#### Enabled=true
#### Warning=true
#### DisplayName=Redundant Void Arg
#### HelpText
  Find and remove redundant void argument lists.

  Examples:      Initial code | Code with applied fixes  
  ---|---  
  int f(void); | int f();  
  int (*f(void))(void); | int (*f())();  
  typedef int (*f_t(void))(void); | typedef int (*f_t())();  
  void (C::*p)(void); | void (C::*p)();  
  C::C(void) {} | C::C() {}  
  C::~C(void) {} | C::~C() {}  

   

  (Clang-Tidy original name: modernize-redundant-void-arg)

#### Tags
- /general/Modernize
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MDR_STF
### Default
#### OriginalId=modernize-shrink-to-fit
#### Enabled=true
#### Warning=true
#### DisplayName=Shrink To Fit
#### HelpText
  Replace copy and swap tricks on shrinkable containers with the shrink_to_fit() method call.

  The shrink_to_fit() method is more readable and more effective than the copy and swap trick to reduce the capacity of a shrinkable container. Note that, the shrink_to_fit() method is only available in C++11 and up.

  (Clang-Tidy original name: modernize-shrink-to-fit)

#### Tags
- /general/Modernize
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MDR_UA
### Default
#### OriginalId=modernize-use-auto
#### Enabled=true
#### Warning=true
#### DisplayName=Use Auto
#### HelpText
  This check is responsible for using the auto type specifier for variable declarations to _improve code readability and maintainability_. For example:

  ``` cpp
  std::vector<int>::iterator I = my_container.begin();

  // transforms to:

  auto I = my_container.begin();

  ```


  The auto type specifier will only be introduced in situations where the variable type matches the type of the initializer expression. In other words auto should deduce the same type that was originally spelled in the source. However, not every situation should be transformed:

  ``` cpp
  int val = 42;
  InfoStruct &I = SomeObject.getInfo();

  // Should not become:

  auto val = 42;
  auto &I = SomeObject.getInfo();

  ```


  In this example using auto for builtins doesn’t improve readability. In other situations it makes the code less self-documenting impairing readability and maintainability. As a result, auto is used only introduced in specific situations described below.

  ##### Iterators

  Iterator type specifiers tend to be long and used frequently, especially in loop constructs. Since the functions generating iterators have a common format, the type specifier can be replaced without obscuring the meaning of code while improving readability and maintainability.

  ``` cpp
  for (std::vector<int>::iterator I = my_container.begin(),
                                  E = my_container.end();
       I != E; ++I) {
  }

  // becomes

  for (auto I = my_container.begin(), E = my_container.end(); I != E; ++I) {
  }

  ```


  The check will only replace iterator type-specifiers when all of the following conditions are satisfied:

    * The iterator is for one of the standard container in std namespace:
      * array
      * deque
      * forward_list
      * list
      * vector
      * map
      * multimap
      * set
      * multiset
      * unordered_map
      * unordered_multimap
      * unordered_set
      * unordered_multiset
      * queue
      * priority_queue
      * stack
    * The iterator is one of the possible iterator types for standard containers:
      * iterator
      * reverse_iterator
      * const_iterator
      * const_reverse_iterator
    * In addition to using iterator types directly, typedefs or other ways of referring to those types are also allowed. However, implementation-specific types for which a type like std::vector<int>::iterator is itself a typedef will not be transformed. Consider the following examples:



  ``` cpp
  // The following direct uses of iterator types will be transformed.
  std::vector<int>::iterator I = MyVec.begin();
  {
    using namespace std;
    list<int>::iterator I = MyList.begin();
  }

  // The type specifier for J would transform to auto since it's a typedef
  // to a standard iterator type.
  typedef std::map<int, std::string>::const_iterator map_iterator;
  map_iterator J = MyMap.begin();

  // The following implementation-specific iterator type for which
  // std::vector<int>::iterator could be a typedef would not be transformed.
  __gnu_cxx::__normal_iterator<int*, std::vector> K = MyVec.begin();

  ```


    * The initializer for the variable being declared is not a braced initializer list. Otherwise, use of auto would cause the type of the variable to be deduced as std::initializer_list.



  ##### New expressions

  Frequently, when a pointer is declared and initialized with new, the pointee type is written twice: in the declaration type and in the new expression. In this cases, the declaration type can be replaced with auto improving readability and maintainability.

  ``` cpp
  TypeName *my_pointer = new TypeName(my_param);

  // becomes

  auto *my_pointer = new TypeName(my_param);

  ```


  The check will also replace the declaration type in multiple declarations, if the following conditions are satisfied:

    * All declared variables have the same type (i.e. all of them are pointers to the same type).
    * All declared variables are initialized with a new expression.
    * The types of all the new expressions are the same than the pointee of the declaration type.



  ``` cpp
  TypeName *my_first_pointer = new TypeName, *my_second_pointer = new TypeName;

  // becomes

  auto *my_first_pointer = new TypeName, *my_second_pointer = new TypeName;

  ```


  ##### Cast expressions

  Frequently, when a variable is declared and initialized with a cast, the variable type is written twice: in the declaration type and in the cast expression. In this cases, the declaration type can be replaced with auto improving readability and maintainability.

  ``` cpp
  TypeName *my_pointer = static_cast<TypeName>(my_param);

  // becomes

  auto *my_pointer = static_cast<TypeName>(my_param);

  ```


  The check handles static_cast, dynamic_cast, const_cast, reinterpret_cast, functional casts, C-style casts and function templates that behave as casts, such as llvm::dyn_cast, boost::lexical_cast and gsl::narrow_cast. Calls to function templates are considered to behave as casts if the first template argument is explicit and is a type, and the function returns that type, or a pointer or reference to it.

  ##### Known Limitations

    * If the initializer is an explicit conversion constructor, the check will not replace the type specifier even though it would be safe to do so.
    * User-defined iterators are not handled at this time.



  ##### Options

  MinTypeNameLength     

  If the option is set to non-zero (default 5), the check will ignore type names having a length less than the option value. The option affects expressions only, not iterators. Spaces between multi-lexeme type names (long int) are considered as one. If the [RemoveStars](\#cmdoption-arg-removestars) option (see below) is set to true, then *s in the type are also counted as a part of the type name.

  ``` cpp
  // MinTypeNameLength = 0, RemoveStars=0

  int a = static_cast<int>(foo());            // ---> auto a = ...
  // length(bool *) = 4
  bool *b = new bool;                         // ---> auto *b = ...
  unsigned c = static_cast<unsigned>(foo());  // ---> auto c = ...

  // MinTypeNameLength = 5, RemoveStars=0

  int a = static_cast<int>(foo());                 // ---> int  a = ...
  bool b = static_cast<bool>(foo());               // ---> bool b = ...
  bool *pb = static_cast<bool*>(foo());            // ---> bool *pb = ...
  unsigned c = static_cast<unsigned>(foo());       // ---> auto c = ...
  // length(long <on-or-more-spaces> int) = 8
  long int d = static_cast<long int>(foo());       // ---> auto d = ...

  // MinTypeNameLength = 5, RemoveStars=1

  int a = static_cast<int>(foo());                 // ---> int  a = ...
  // length(int * * ) = 5
  int **pa = static_cast<int**>(foo());            // ---> auto pa = ...
  bool b = static_cast<bool>(foo());               // ---> bool b = ...
  bool *pb = static_cast<bool*>(foo());            // ---> auto pb = ...
  unsigned c = static_cast<unsigned>(foo());       // ---> auto c = ...
  long int d = static_cast<long int>(foo());       // ---> auto d = ...

  ```


  RemoveStars     

  If the option is set to true (default is false), the check will remove stars from the non-typedef pointer types when replacing type names with auto. Otherwise, the check will leave stars. For example:

  ``` cpp
  TypeName *my_first_pointer = new TypeName, *my_second_pointer = new TypeName;

  // RemoveStars = 0

  auto *my_first_pointer = new TypeName, *my_second_pointer = new TypeName;

  // RemoveStars = 1

  auto my_first_pointer = new TypeName, my_second_pointer = new TypeName;

  ```


  (Clang-Tidy original name: modernize-use-auto)

#### Tags
- /general/Modernize
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MDR_UBL
### Default
#### OriginalId=modernize-use-bool-literals
#### Enabled=true
#### Warning=true
#### DisplayName=Use Bool Literals
#### HelpText
  Finds integer literals which are cast to bool.

  ``` cpp
  bool p = 1;
  bool f = static_cast<bool>(1);
  std::ios_base::sync_with_stdio(0);
  bool x = p ? 1 : 0;

  // transforms to

  bool p = true;
  bool f = true;
  std::ios_base::sync_with_stdio(false);
  bool x = p ? true : false;

  ```


  ##### Options

  IgnoreMacros     

  If set to true, the check will not give warnings inside macros. Default is true.

  (Clang-Tidy original name: modernize-use-bool-literals)

#### Tags
- /general/Modernize
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MDR_UDMI
### Default
#### OriginalId=modernize-use-default-member-init
#### Enabled=true
#### Warning=true
#### DisplayName=Use Default Member Init
#### HelpText
  This check converts a default constructor’s member initializers into the new default member initializers in C++11. Other member initializers that match the default member initializer are removed. This can reduce repeated code or allow use of ‘= default’.

  ``` cpp
  struct A {
    A() : i(5), j(10.0) {}
    A(int i) : i(i), j(10.0) {}
    int i;
    double j;
  };

  // becomes

  struct A {
    A() {}
    A(int i) : i(i) {}
    int i{5};
    double j{10.0};
  };

  ```


  Note

  Only converts member initializers for built-in types, enums, and pointers. The readability-redundant-member-init check will remove redundant member initializers for classes.

  ##### Options

  UseAssignment     

  If this option is set to true (default is false), the check will initialise members with an assignment. For example:

  ``` cpp
  struct A {
    A() {}
    A(int i) : i(i) {}
    int i = 5;
    double j = 10.0;
  };

  ```


  IgnoreMacros     

  If this option is set to true (default is true), the check will not warn about members declared inside macros.

  (Clang-Tidy original name: modernize-use-default-member-init)

#### Tags
- /general/Modernize
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MDR_UE
### Default
#### OriginalId=modernize-use-emplace
#### Enabled=true
#### Warning=true
#### DisplayName=Use Emplace
#### HelpText
  The check flags insertions to an STL-style container done by calling the push_back method with an explicitly-constructed temporary of the container element type. In this case, the corresponding emplace_back method results in less verbose and potentially more efficient code. Right now the check doesn’t support push_front and insert. It also doesn’t support insert functions for associative containers because replacing insert with emplace may result in [speed regression](https://htmlpreview.github.io/?https://github.com/HowardHinnant/papers/blob/master/insert_vs_emplace.html), but it might get support with some addition flag in the future.

  By default only std::vector, std::deque, std::list are considered. This list can be modified using the [ContainersWithPushBack](\#cmdoption-arg-containerswithpushback) option.

  Before:

  ``` cpp
  std::vector<MyClass> v;
  v.push_back(MyClass(21, 37));

  std::vector<std::pair<int, int>> w;

  w.push_back(std::pair<int, int>(21, 37));
  w.push_back(std::make_pair(21L, 37L));

  ```


  After:

  ``` cpp
  std::vector<MyClass> v;
  v.emplace_back(21, 37);

  std::vector<std::pair<int, int>> w;
  w.emplace_back(21, 37);
  w.emplace_back(21L, 37L);

  ```


  By default, the check is able to remove unnecessary std::make_pair and std::make_tuple calls from push_back calls on containers of std::pair and std::tuple. Custom tuple-like types can be modified by the [TupleTypes](\#cmdoption-arg-tupletypes) option; custom make functions can be modified by the [TupleMakeFunctions](\#cmdoption-arg-tuplemakefunctions) option.

  The other situation is when we pass arguments that will be converted to a type inside a container.

  Before:

  ``` cpp
  std::vector<boost::optional<std::string> > v;
  v.push_back("abc");

  ```


  After:

  ``` cpp
  std::vector<boost::optional<std::string> > v;
  v.emplace_back("abc");

  ```


  In some cases the transformation would be valid, but the code wouldn’t be exception safe. In this case the calls of push_back won’t be replaced.

  ``` cpp
  std::vector<std::unique_ptr<int>> v;
  v.push_back(std::unique_ptr<int>(new int(0)));
  auto *ptr = new int(1);
  v.push_back(std::unique_ptr<int>(ptr));

  ```


  This is because replacing it with emplace_back could cause a leak of this pointer if emplace_back would throw exception before emplacement (e.g. not enough memory to add a new element).

  For more info read item 42 - “Consider emplacement instead of insertion.” of Scott Meyers “Effective Modern C++”.

  The default smart pointers that are considered are std::unique_ptr, std::shared_ptr, std::auto_ptr. To specify other smart pointers or other classes use the [SmartPointers](\#cmdoption-arg-smartpointers) option.

  Check also doesn’t fire if any argument of the constructor call would be:

    * a bit-field (bit-fields can’t bind to rvalue/universal reference)
    * a new expression (to avoid leak)
    * if the argument would be converted via derived-to-base cast.



  This check requires C++11 or higher to run.

  ##### Options

  ContainersWithPushBack     

  Semicolon-separated list of class names of custom containers that support push_back.

  IgnoreImplicitConstructors     

  When true, the check will ignore implicitly constructed arguments of push_back, e.g.

  ``` cpp
  std::vector<std::string> v;
  v.push_back("a"); // Ignored when IgnoreImplicitConstructors is `true`.

  ```


  Default is false.

  SmartPointers     

  Semicolon-separated list of class names of custom smart pointers.

  TupleTypes     

  Semicolon-separated list of std::tuple-like class names.

  TupleMakeFunctions     

  Semicolon-separated list of std::make_tuple-like function names. Those function calls will be removed from push_back calls and turned into emplace_back.

  ###### Example

  ``` cpp
  std::vector<MyTuple<int, bool, char>> x;
  x.push_back(MakeMyTuple(1, false, 'x'));

  ```


  transforms to:

  ``` cpp
  std::vector<MyTuple<int, bool, char>> x;
  x.emplace_back(1, false, 'x');

  ```


  when [TupleTypes](\#cmdoption-arg-tupletypes) is set to MyTuple and [TupleMakeFunctions](\#cmdoption-arg-tuplemakefunctions) is set to MakeMyTuple.

  (Clang-Tidy original name: modernize-use-emplace)

#### Tags
- /general/Modernize
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MDR_UED
### Default
#### OriginalId=modernize-use-equals-default
#### Enabled=true
#### Warning=true
#### DisplayName=Use Equals Default
#### HelpText
  This check replaces default bodies of special member functions with = default;. The explicitly defaulted function declarations enable more opportunities in optimization, because the compiler might treat explicitly defaulted functions as trivial.

  ``` cpp
  struct A {
    A() {}
    ~A();
  };
  A::~A() {}

  // becomes

  struct A {
    A() = default;
    ~A();
  };
  A::~A() = default;

  ```


  Note

  Move-constructor and move-assignment operator are not supported yet.

  ##### Options

  IgnoreMacros     

  If set to true, the check will not give warnings inside macros. Default is true.

  (Clang-Tidy original name: modernize-use-equals-default)

#### Tags
- /general/Modernize
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MDR_UED2
### Default
#### OriginalId=modernize-use-equals-delete
#### Enabled=true
#### Warning=true
#### DisplayName=Use Equals Delete
#### HelpText
  This check marks unimplemented private special member functions with = delete. To avoid false-positives, this check only applies in a translation unit that has all other member functions implemented.

  ``` cpp
  struct A {
  private:
    A(const A&);
    A& operator=(const A&);
  };

  // becomes

  struct A {
  private:
    A(const A&) = delete;
    A& operator=(const A&) = delete;
  };

  ```


  IgnoreMacros     

  If this option is set to true (default is true), the check will not warn about functions declared inside macros.

  (Clang-Tidy original name: modernize-use-equals-delete)

#### Tags
- /general/Modernize
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MDR_UN
### Default
#### OriginalId=modernize-use-nodiscard
#### Enabled=true
#### Warning=true
#### DisplayName=Use Nodiscard
#### HelpText
  Adds [[nodiscard]] attributes (introduced in C++17) to member functions in order to highlight at compile time which return values should not be ignored.

  Member functions need to satisfy the following conditions to be considered by this check:

    * no [[nodiscard]], [[noreturn]], __attribute__((warn_unused_result)), [[clang::warn_unused_result]] nor [[gcc::warn_unused_result]] attribute,
    * non-void return type,
    * non-template return types,
    * const member function,
    * non-variadic functions,
    * no non-const reference parameters,
    * no pointer parameters,
    * no template parameters,
    * no template function parameters,
    * not be a member of a class with mutable member variables,
    * no Lambdas,
    * no conversion functions.



  Such functions have no means of altering any state or passing values other than via the return type. Unless the member functions are altering state via some external call (e.g. I/O).

  ##### Example

  ``` cpp
  bool empty() const;
  bool empty(int i) const;

  ```


  transforms to:

  ``` cpp
  [[nodiscard] bool empty() const;
  [[nodiscard] bool empty(int i) const;

  ```


  ##### Options

  ReplacementString     

  Specifies a macro to use instead of [[nodiscard]]. This is useful when maintaining source code that needs to compile with a pre-C++17 compiler.

  ###### Example

  ``` cpp
  bool empty() const;
  bool empty(int i) const;

  ```


  transforms to:

  ``` cpp
  NO_DISCARD bool empty() const;
  NO_DISCARD bool empty(int i) const;

  ```


  if the [ReplacementString](modernize-use-noexcept.html\#cmdoption-arg-replacementstring) option is set to NO_DISCARD.

  Note

  If the [ReplacementString](modernize-use-noexcept.html\#cmdoption-arg-replacementstring) is not a C++ attribute, but instead a macro, then that macro must be defined in scope or the fix-it will not be applied.

  Note

  For alternative __attribute__ syntax options to mark functions as [[nodiscard]] in non-c++17 source code. See <https://clang.llvm.org/docs/AttributeReference.html\#nodiscard-warn-unused-result>

  (Clang-Tidy original name: modernize-use-nodiscard)

#### Tags
- /general/Modernize
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MDR_UN2
### Default
#### OriginalId=modernize-use-noexcept
#### Enabled=true
#### Warning=true
#### DisplayName=Use Noexcept
#### HelpText
  This check replaces deprecated dynamic exception specifications with the appropriate noexcept specification (introduced in C++11). By default this check will replace throw() with noexcept, and throw(<exception>[,...]) or throw(...) with noexcept(false).

  ##### Example

  ``` cpp
  void foo() throw();
  void bar() throw(int) {}

  ```


  transforms to:

  ``` cpp
  void foo() noexcept;
  void bar() noexcept(false) {}

  ```


  ##### Options

  ReplacementString     

  Users can use [ReplacementString](\#cmdoption-arg-replacementstring) to specify a macro to use instead of noexcept. This is useful when maintaining source code that uses custom exception specification marking other than noexcept. Fix-it hints will only be generated for non-throwing specifications.

  ###### Example

  ``` cpp
  void bar() throw(int);
  void foo() throw();

  ```


  transforms to:

  ``` cpp
  void bar() throw(int);  // No fix-it generated.
  void foo() NOEXCEPT;

  ```


  if the [ReplacementString](\#cmdoption-arg-replacementstring) option is set to NOEXCEPT.

  UseNoexceptFalse     

  Enabled by default, disabling will generate fix-it hints that remove throwing dynamic exception specs, e.g., throw(<something>), completely without providing a replacement text, except for destructors and delete operators that are noexcept(true) by default.

  ###### Example

  ``` cpp
  void foo() throw(int) {}

  struct bar {
    void foobar() throw(int);
    void operator delete(void *ptr) throw(int);
    void operator delete[](void *ptr) throw(int);
    ~bar() throw(int);
  }

  ```


  transforms to:

  ``` cpp
  void foo() {}

  struct bar {
    void foobar();
    void operator delete(void *ptr) noexcept(false);
    void operator delete[](void *ptr) noexcept(false);
    ~bar() noexcept(false);
  }

  ```


  if the [UseNoexceptFalse](\#cmdoption-arg-usenoexceptfalse) option is set to false.

  (Clang-Tidy original name: modernize-use-noexcept)

#### Tags
- /general/Modernize
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MDR_UN3
### Default
#### OriginalId=modernize-use-nullptr
#### Enabled=true
#### Warning=true
#### DisplayName=Use Nullptr
#### HelpText
  The check converts the usage of null pointer constants (eg. NULL, 0) to use the new C++11 nullptr keyword.

  ##### Example

  ``` cpp
  void assignment() {
    char *a = NULL;
    char *b = 0;
    char c = 0;
  }

  int *ret_ptr() {
    return 0;
  }

  ```


  transforms to:

  ``` cpp
  void assignment() {
    char *a = nullptr;
    char *b = nullptr;
    char c = 0;
  }

  int *ret_ptr() {
    return nullptr;
  }

  ```


  ##### Options

  NullMacros     

  Comma-separated list of macro names that will be transformed along with NULL. By default this check will only replace the NULL macro and will skip any similar user-defined macros.

  ###### Example

  ``` cpp
  #define MY_NULL (void*)0
  void assignment() {
    void *p = MY_NULL;
  }

  ```


  transforms to:

  ``` cpp
  #define MY_NULL NULL
  void assignment() {
    int *p = nullptr;
  }

  ```


  if the [NullMacros](\#cmdoption-arg-nullmacros) option is set to MY_NULL.

  (Clang-Tidy original name: modernize-use-nullptr)

#### Tags
- /general/Modernize
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MDR_UO
### Default
#### OriginalId=modernize-use-override
#### Enabled=true
#### Warning=true
#### DisplayName=Use Override
#### HelpText
  Adds override (introduced in C++11) to overridden virtual functions and removes virtual from those functions as it is not required.

  virtual on non base class implementations was used to help indicate to the user that a function was virtual. C++ compilers did not use the presence of this to signify an overridden function.

  In C++ 11 override and final keywords were introduced to allow overridden functions to be marked appropriately. Their presence allows compilers to verify that an overridden function correctly overrides a base class implementation.

  This can be useful as compilers can generate a compile time error when:

    * The base class implementation function signature changes.
    * The user has not created the override with the correct signature.



  ##### Options

  IgnoreDestructors     

  If set to true, this check will not diagnose destructors. Default is false.

  AllowOverrideAndFinal     

  If set to true, this check will not diagnose override as redundant with final. This is useful when code will be compiled by a compiler with warning/error checking flags requiring override explicitly on overridden members, such as gcc -Wsuggest-override/gcc -Werror=suggest-override. Default is false.

  OverrideSpelling     

  Specifies a macro to use instead of override. This is useful when maintaining source code that also needs to compile with a pre-C++11 compiler.

  FinalSpelling     

  Specifies a macro to use instead of final. This is useful when maintaining source code that also needs to compile with a pre-C++11 compiler.

  Note

  For more information on the use of override see <https://en.cppreference.com/w/cpp/language/override>

  (Clang-Tidy original name: modernize-use-override)

#### Tags
- /general/Modernize
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MDR_USA
### Default
#### OriginalId=modernize-unary-static-assert
#### Enabled=true
#### Warning=true
#### DisplayName=Unary Static Assert
#### HelpText
  The check diagnoses any static_assert declaration with an empty string literal and provides a fix-it to replace the declaration with a single-argument static_assert declaration.

  The check is only applicable for C++17 and later code.

  The following code:

  ``` cpp
  void f_textless(int a) {
    static_assert(sizeof(a) <= 10, "");
  }

  ```


  is replaced by:

  ``` cpp
  void f_textless(int a) {
    static_assert(sizeof(a) <= 10);
  }

  ```


  (Clang-Tidy original name: modernize-unary-static-assert)

#### Tags
- /general/Modernize
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MDR_UTF
### Default
#### OriginalId=modernize-use-transparent-functors
#### Enabled=true
#### Warning=true
#### DisplayName=Use Transparent Functors
#### HelpText
  Prefer transparent functors to non-transparent ones. When using transparent functors, the type does not need to be repeated. The code is easier to read, maintain and less prone to errors. It is not possible to introduce unwanted conversions.

  ``` cpp
  // Non-transparent functor
  std::map<int, std::string, std::greater<int>> s;

  // Transparent functor.
  std::map<int, std::string, std::greater<>> s;

  // Non-transparent functor
  using MyFunctor = std::less<MyType>;

  ```


  It is not always a safe transformation though. The following case will be untouched to preserve the semantics.

  ``` cpp
  // Non-transparent functor
  std::map<const char *, std::string, std::greater<std::string>> s;

  ```


  ##### Options

  SafeMode     

  If the option is set to true, the check will not diagnose cases where using a transparent functor cannot be guaranteed to produce identical results as the original code. The default value for this option is false.

  This check requires using C++14 or higher to run.

  (Clang-Tidy original name: modernize-use-transparent-functors)

#### Tags
- /general/Modernize
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MDR_UTRT
### Default
#### OriginalId=modernize-use-trailing-return-type
#### Enabled=true
#### Warning=true
#### DisplayName=Use Trailing Return Type
#### HelpText
  Rewrites function signatures to use a trailing return type (introduced in C++11). This transformation is purely stylistic. The return type before the function name is replaced by auto and inserted after the function parameter list (and qualifiers).

  ##### Example

  ``` cpp
  int f1();
  inline int f2(int arg) noexcept;
  virtual float f3() const && = delete;

  ```


  transforms to:

  ``` cpp
  auto f1() -> int;
  inline auto f2(int arg) -> int noexcept;
  virtual auto f3() const && -> float = delete;

  ```


  ##### Known Limitations

  The following categories of return types cannot be rewritten currently:

    * function pointers
    * member function pointers
    * member pointers



  Unqualified names in the return type might erroneously refer to different entities after the rewrite. Preventing such errors requires a full lookup of all unqualified names present in the return type in the scope of the trailing return type location. This location includes e.g. function parameter names and members of the enclosing class (including all inherited classes). Such a lookup is currently not implemented.

  Given the following piece of code

  ``` cpp
  struct S { long long value; };
  S f(unsigned S) { return {S * 2}; }
  class CC {
    int S;
    struct S m();
  };
  S CC::m() { return {0}; }

  ```


  a careless rewrite would produce the following output:

  ``` cpp
  struct S { long long value; };
  auto f(unsigned S) -> S { return {S * 2}; } // error
  class CC {
    int S;
    auto m() -> struct S;
  };
  auto CC::m() -> S { return {0}; } // error

  ```


  This code fails to compile because the S in the context of f refers to the equally named function parameter. Similarly, the S in the context of m refers to the equally named class member. The check can currently only detect and avoid a clash with a function parameter name.

  (Clang-Tidy original name: modernize-use-trailing-return-type)

#### Tags
- /general/Modernize
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MDR_UU
### Default
#### OriginalId=modernize-use-using
#### Enabled=true
#### Warning=true
#### DisplayName=Use Using
#### HelpText
  The check converts the usage of typedef with using keyword.

  Before:

  ``` cpp
  typedef int variable;

  class Class{};
  typedef void (Class::* MyPtrType)() const;

  typedef struct { int a; } R_t, *R_p;

  ```


  After:

  ``` cpp
  using variable = int;

  class Class{};
  using MyPtrType = void (Class::*)() const;

  using R_t = struct { int a; };
  using R_p = R_t*;

  ```


  This check requires using C++11 or higher to run.

  ##### Options

  IgnoreMacros     

  If set to true, the check will not give warnings inside macros. Default is true.

  (Clang-Tidy original name: modernize-use-using)

#### Tags
- /general/Modernize
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MDR_UUE
### Default
#### OriginalId=modernize-use-uncaught-exceptions
#### Enabled=true
#### Warning=true
#### DisplayName=Use Uncaught Exceptions
#### HelpText
  This check will warn on calls to std::uncaught_exception and replace them with calls to std::uncaught_exceptions, since std::uncaught_exception was deprecated in C++17.

  Below are a few examples of what kind of occurrences will be found and what they will be replaced with.

  ``` cpp
  #define MACRO1 std::uncaught_exception
  #define MACRO2 std::uncaught_exception

  int uncaught_exception() {
    return 0;
  }

  int main() {
    int res;

    res = uncaught_exception();
    // No warning, since it is not the deprecated function from namespace std

    res = MACRO2();
    // Warning, but will not be replaced

    res = std::uncaught_exception();
    // Warning and replaced

    using std::uncaught_exception;
    // Warning and replaced

    res = uncaught_exception();
    // Warning and replaced
  }

  ```


  After applying the fixes the code will look like the following:

  ``` cpp
  #define MACRO1 std::uncaught_exception
  #define MACRO2 std::uncaught_exception

  int uncaught_exception() {
    return 0;
  }

  int main() {
    int res;

    res = uncaught_exception();

    res = MACRO2();

    res = std::uncaught_exceptions();

    using std::uncaught_exceptions;

    res = uncaught_exceptions();
  }

  ```


  (Clang-Tidy original name: modernize-use-uncaught-exceptions)

#### Tags
- /general/Modernize
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MPI_BD
### Default
#### OriginalId=mpi-buffer-deref
#### Enabled=true
#### Warning=true
#### DisplayName=Buffer Deref
#### HelpText
  This check verifies if a buffer passed to an MPI (Message Passing Interface) function is sufficiently dereferenced. Buffers should be passed as a single pointer or array. As MPI function signatures specify void * for their buffer types, insufficiently dereferenced buffers can be passed, like for example as double pointers or multidimensional arrays, without a compiler warning emitted.

  Examples:

  ``` cpp
  // A double pointer is passed to the MPI function.
  char *buf;
  MPI_Send(&buf, 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);

  // A multidimensional array is passed to the MPI function.
  short buf[1][1];
  MPI_Send(buf, 1, MPI_SHORT, 0, 0, MPI_COMM_WORLD);

  // A pointer to an array is passed to the MPI function.
  short *buf[1];
  MPI_Send(buf, 1, MPI_SHORT, 0, 0, MPI_COMM_WORLD);

  ```


  (Clang-Tidy original name: mpi-buffer-deref)

#### Tags
- /general/MPI
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MPI_TM
### Default
#### OriginalId=mpi-type-mismatch
#### Enabled=true
#### Warning=true
#### DisplayName=Type Mismatch
#### HelpText
  This check verifies if buffer type and MPI (Message Passing Interface) datatype pairs match for used MPI functions. All MPI datatypes defined by the MPI standard (3.1) are verified by this check. User defined typedefs, custom MPI datatypes and null pointer constants are skipped, in the course of verification.

  Example:

  ``` cpp
  // In this case, the buffer type matches MPI datatype.
  char buf;
  MPI_Send(&buf, 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);

  // In the following case, the buffer type does not match MPI datatype.
  int buf;
  MPI_Send(&buf, 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);

  ```


  (Clang-Tidy original name: mpi-type-mismatch)

#### Tags
- /general/MPI
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MSC_DIH
### Default
#### OriginalId=misc-definitions-in-headers
#### Enabled=true
#### Warning=true
#### DisplayName=Definitions In Headers
#### HelpText
  Finds non-extern non-inline function and variable definitions in header files, which can lead to potential ODR violations in case these headers are included from multiple translation units.

  ``` cpp
  // Foo.h
  int a = 1; // Warning: variable definition.
  extern int d; // OK: extern variable.

  namespace N {
    int e = 2; // Warning: variable definition.
  }

  // Warning: variable definition.
  const char* str = "foo";

  // OK: internal linkage variable definitions are ignored for now.
  // Although these might also cause ODR violations, we can be less certain and
  // should try to keep the false-positive rate down.
  static int b = 1;
  const int c = 1;
  const char* const str2 = "foo";
  constexpr int k = 1;

  // Warning: function definition.
  int g() {
    return 1;
  }

  // OK: inline function definition is allowed to be defined multiple times.
  inline int e() {
    return 1;
  }

  class A {
  public:
    int f1() { return 1; } // OK: implicitly inline member function definition is allowed.
    int f2();

    static int d;
  };

  // Warning: not an inline member function definition.
  int A::f2() { return 1; }

  // OK: class static data member declaration is allowed.
  int A::d = 1;

  // OK: function template is allowed.
  template<typename T>
  T f3() {
    T a = 1;
    return a;
  }

  // Warning: full specialization of a function template is not allowed.
  template <>
  int f3() {
    int a = 1;
    return a;
  }

  template <typename T>
  struct B {
    void f1();
  };

  // OK: member function definition of a class template is allowed.
  template <typename T>
  void B<T>::f1() {}

  class CE {
    constexpr static int i = 5; // OK: inline variable definition.
  };

  inline int i = 5; // OK: inline variable definition.

  constexpr int f10() { return 0; } // OK: constexpr function implies inline.

  // OK: C++14 variable templates are inline.
  template <class T>
  constexpr T pi = T(3.1415926L);

  ```


  ##### Options

  HeaderFileExtensions     

  A comma-separated list of filename extensions of header files (the filename extensions should not include “.” prefix). Default is “h,hh,hpp,hxx”. For header files without an extension, use an empty string (if there are no other desired extensions) or leave an empty element in the list. e.g., “h,hh,hpp,hxx,” (note the trailing comma).

  UseHeaderFileExtension     

  When true, the check will use the file extension to distinguish header files. Default is true.

  (Clang-Tidy original name: misc-definitions-in-headers)

#### Tags
- /general/Miscellaneous
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MSC_MC
### Default
#### OriginalId=misc-misplaced-const
#### Enabled=true
#### Warning=true
#### DisplayName=Misplaced Const
#### HelpText
  This check diagnoses when a const qualifier is applied to a typedef/ using to a pointer type rather than to the pointee, because such constructs are often misleading to developers because the const applies to the pointer rather than the pointee.

  For instance, in the following code, the resulting type is int * const rather than const int *:

  ``` cpp
  typedef int *int_ptr;
  void f(const int_ptr ptr) {
    *ptr = 0; // potentially quite unexpectedly the int can be modified here
    ptr = 0; // does not compile
  }

  ```


  The check does not diagnose when the underlying typedef/using type is a pointer to a const type or a function pointer type. This is because the const qualifier is less likely to be mistaken because it would be redundant (or disallowed) on the underlying pointee type.

  (Clang-Tidy original name: misc-misplaced-const)

#### Tags
- /general/Miscellaneous
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MSC_NCO
### Default
#### OriginalId=misc-non-copyable-objects
#### Enabled=true
#### Warning=true
#### DisplayName=Non Copyable Objects
#### HelpText
  cert-fio38-c redirects here as an alias for this check.

  The check flags dereferences and non-pointer declarations of objects that are not meant to be passed by value, such as C FILE objects or POSIX pthread_mutex_t objects.

  This check corresponds to CERT C++ Coding Standard rule [FIO38-C. Do not copy a FILE object](https://www.securecoding.cert.org/confluence/display/c/FIO38-C.+Do+not+copy+a+FILE+object).

  (Clang-Tidy original name: misc-non-copyable-objects)

#### Tags
- /general/Miscellaneous
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MSC_NDO
### Default
#### OriginalId=misc-new-delete-overloads
#### Enabled=true
#### Warning=true
#### DisplayName=New Delete Overloads
#### HelpText
  cert-dcl54-cpp redirects here as an alias for this check.

  The check flags overloaded operator new() and operator delete() functions that do not have a corresponding free store function defined within the same scope. For instance, the check will flag a class implementation of a non-placement operator new() when the class does not also define a non-placement operator delete() function as well.

  The check does not flag implicitly-defined operators, deleted or private operators, or placement operators.

  This check corresponds to CERT C++ Coding Standard rule [DCL54-CPP. Overload allocation and deallocation functions as a pair in the same scope](https://www.securecoding.cert.org/confluence/display/cplusplus/DCL54-CPP.+Overload+allocation+and+deallocation+functions+as+a+pair+in+the+same+scope).

  (Clang-Tidy original name: misc-new-delete-overloads)

#### Tags
- /general/Miscellaneous
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MSC_NPMVIC
### Default
#### OriginalId=misc-non-private-member-variables-in-classes
#### Enabled=true
#### Warning=true
#### DisplayName=Non Private Member Variables In Classes
#### HelpText
  cppcoreguidelines-non-private-member-variables-in-classes redirects here as an alias for this check.

  Finds classes that contain non-static data members in addition to user-declared non-static member functions and diagnose all data members declared with a non-public access specifier. The data members should be declared as private and accessed through member functions instead of exposed to derived classes or class consumers.

  ##### Options

  IgnoreClassesWithAllMemberVariablesBeingPublic     

  Allows to completely ignore classes if **all** the member variables in that class a declared with a public access specifier.

  IgnorePublicMemberVariables     

  Allows to ignore (not diagnose) **all** the member variables declared with a public access specifier.

  (Clang-Tidy original name: misc-non-private-member-variables-in-classes)

#### Tags
- /general/Miscellaneous
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MSC_NR
### Default
#### OriginalId=misc-no-recursion
#### Enabled=true
#### Warning=true
#### DisplayName=No Recursion
#### HelpText
  Finds strongly connected functions (by analyzing the call graph for SCC’s (Strongly Connected Components) that are loops), diagnoses each function in the cycle, and displays one example of a possible call graph loop (recursion).

  References:

    * CERT C++ Coding Standard rule [DCL56-CPP. Avoid cycles during initialization of static objects](https://wiki.sei.cmu.edu/confluence/display/cplusplus/DCL56-CPP.+Avoid+cycles+during+initialization+of+static+objects).
    * JPL Institutional Coding Standard for the C Programming Language (JPL DOCID D-60411) rule 2.4 Do not use direct or indirect recursion.
    * OpenCL Specification, Version 1.2 rule [6.9 Restrictions: i. Recursion is not supported.](https://www.khronos.org/registry/OpenCL/specs/opencl-1.2.pdf).



  Limitations:

    * The check does not handle calls done through function pointers
    * The check does not handle C++ destructors



  (Clang-Tidy original name: misc-no-recursion)

#### Tags
- /general/Miscellaneous
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MSC_RE
### Default
#### OriginalId=misc-redundant-expression
#### Enabled=true
#### Warning=true
#### DisplayName=Redundant Expression
#### HelpText
  Detect redundant expressions which are typically errors due to copy-paste.

  Depending on the operator expressions may be

    * redundant,
    * always true,
    * always false,
    * always a constant (zero or one).



  Examples:

  ``` cpp
  ((x+1) | (x+1))             // (x+1) is redundant
  (p->x == p->x)              // always true
  (p->x < p->x)               // always false
  (speed - speed + 1 == 12)   // speed - speed is always zero

  ```


  (Clang-Tidy original name: misc-redundant-expression)

#### Tags
- /general/Miscellaneous
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MSC_SA2
### Default
#### OriginalId=misc-static-assert
#### Enabled=true
#### Warning=true
#### DisplayName=Static Assert
#### HelpText
  cert-dcl03-c redirects here as an alias for this check.

  Replaces assert() with static_assert() if the condition is evaluatable at compile time.

  The condition of static_assert() is evaluated at compile time which is safer and more efficient.

  (Clang-Tidy original name: misc-static-assert)

#### Tags
- /general/Miscellaneous
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MSC_TBVCBR
### Default
#### OriginalId=misc-throw-by-value-catch-by-reference
#### Enabled=true
#### Warning=true
#### DisplayName=Throw By Value Catch By Reference
#### HelpText
  cert-err09-cpp redirects here as an alias for this check. cert-err61-cpp redirects here as an alias for this check.

  Finds violations of the rule “Throw by value, catch by reference” presented for example in “C++ Coding Standards” by H. Sutter and A. Alexandrescu, as well as the CERT C++ Coding Standard rule [ERR61-CPP. Catch exceptions by lvalue reference](https://wiki.sei.cmu.edu/confluence/display/cplusplus/ERR61-CPP.+Catch+exceptions+by+lvalue+reference).

  Exceptions:     

    * Throwing string literals will not be flagged despite being a pointer. They are not susceptible to slicing and the usage of string literals is idomatic.
    * Catching character pointers (char, wchar_t, unicode character types) will not be flagged to allow catching sting literals.
    * Moved named values will not be flagged as not throwing an anonymous temporary. In this case we can be sure that the user knows that the object can’t be accessed outside catch blocks handling the error.
    * Throwing function parameters will not be flagged as not throwing an anonymous temporary. This allows helper functions for throwing.
    * Re-throwing caught exception variables will not be flragged as not throwing an anonymous temporary. Although this can usually be done by just writing throw; it happens often enough in real code.



  ##### Options

  CheckThrowTemporaries     

  Triggers detection of violations of the CERT recommendation ERR09-CPP. Throw anonymous temporaries. Default is true.

  WarnOnLargeObject     

  Also warns for any large, trivial object caught by value. Catching a large object by value is not dangerous but affects the performance negatively. The maximum size of an object allowed to be caught without warning can be set using the MaxSize option. Default is false.

  MaxSize     

  Determines the maximum size of an object allowed to be caught without warning. Only applicable if [WarnOnLargeObject](\#cmdoption-arg-warnonlargeobject) is set to true. If the option is set by the user to std::numeric_limits<uint64_t>::max() then it reverts to the default value. Default is the size of size_t.

  (Clang-Tidy original name: misc-throw-by-value-catch-by-reference)

#### Tags
- /general/Miscellaneous
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MSC_UAD
### Default
#### OriginalId=misc-unused-alias-decls
#### Enabled=true
#### Warning=true
#### DisplayName=Unused Alias Decls
#### HelpText
  Finds unused namespace alias declarations.

  ``` cpp
  namespace my_namespace {
  class C {};
  }
  namespace unused_alias = ::my_namespace;

  ```


  (Clang-Tidy original name: misc-unused-alias-decls)

#### Tags
- /general/Miscellaneous
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MSC_UAO
### Default
#### OriginalId=misc-unconventional-assign-operator
#### Enabled=true
#### Warning=true
#### DisplayName=Unconventional Assign Operator
#### HelpText
  Finds declarations of assign operators with the wrong return and/or argument types and definitions with good return type but wrong return statements.

    * The return type must be Class&.
    * Works with move-assign and assign by value.
    * Private and deleted operators are ignored.
    * The operator must always return *this.



  (Clang-Tidy original name: misc-unconventional-assign-operator)

#### Tags
- /general/Miscellaneous
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MSC_UP
### Default
#### OriginalId=misc-unused-parameters
#### Enabled=true
#### Warning=true
#### DisplayName=Unused Parameters
#### HelpText
  Finds unused function parameters. Unused parameters may signify a bug in the code (e.g. when a different parameter is used instead). The suggested fixes either comment parameter name out or remove the parameter completely, if all callers of the function are in the same translation unit and can be updated.

  The check is similar to the -Wunused-parameter compiler diagnostic and can be used to prepare a codebase to enabling of that diagnostic. By default the check is more permissive (see [StrictMode](performance-inefficient-string-concatenation.html\#cmdoption-arg-strictmode)).

  ``` cpp
  void a(int i) { /*some code that doesn't use `i`*/ }

  // becomes

  void a(int  /*i*/) { /*some code that doesn't use `i`*/ }

  ```


  ``` cpp
  static void staticFunctionA(int i);
  static void staticFunctionA(int i) { /*some code that doesn't use `i`*/ }

  // becomes

  static void staticFunctionA()
  static void staticFunctionA() { /*some code that doesn't use `i`*/ }

  ```


  ##### Options

  StrictMode     

  When false (default value), the check will ignore trivially unused parameters, i.e. when the corresponding function has an empty body (and in case of constructors - no constructor initializers). When the function body is empty, an unused parameter is unlikely to be unnoticed by a human reader, and there’s basically no place for a bug to hide.

  (Clang-Tidy original name: misc-unused-parameters)

#### Tags
- /general/Miscellaneous
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MSC_URR
### Default
#### OriginalId=misc-uniqueptr-reset-release
#### Enabled=true
#### Warning=true
#### DisplayName=Uniqueptr Reset Release
#### HelpText
  Find and replace unique_ptr::reset(release()) with std::move().

  Example:

  ``` cpp
  std::unique_ptr<Foo> x, y;
  x.reset(y.release()); -> x = std::move(y);

  ```


  If y is already rvalue, std::move() is not added. x and y can also be std::unique_ptr<Foo>*.

  (Clang-Tidy original name: misc-uniqueptr-reset-release)

#### Tags
- /general/Miscellaneous
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_MSC_UUD
### Default
#### OriginalId=misc-unused-using-decls
#### Enabled=true
#### Warning=true
#### DisplayName=Unused Using Decls
#### HelpText
  Finds unused using declarations.

  Example:

  ``` cpp
  namespace n { class C; }
  using n::C;  // Never actually used.

  ```


  (Clang-Tidy original name: misc-unused-using-decls)

#### Tags
- /general/Miscellaneous
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_OBC_ANI
### Default
#### OriginalId=objc-avoid-nserror-init
#### Enabled=false
#### Warning=true
#### DisplayName=Avoid Nserror Init
#### HelpText
  Finds improper initialization of NSError objects.

  According to Apple developer document, we should always use factory method errorWithDomain:code:userInfo: to create new NSError objects instead of [NSError alloc] init]. Otherwise it will lead to a warning message during runtime.

  The corresponding information about NSError creation: <https://developer.apple.com/library/content/documentation/Cocoa/Conceptual/ErrorHandlingCocoa/CreateCustomizeNSError/CreateCustomizeNSError.html>

  (Clang-Tidy original name: objc-avoid-nserror-init)

#### Tags
- /general/Objective-C
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_OBC_DIC
### Default
#### OriginalId=objc-dealloc-in-category
#### Enabled=false
#### Warning=true
#### DisplayName=Dealloc In Category
#### HelpText
  Finds implementations of -dealloc in Objective-C categories. The category implementation will override any -dealloc in the class implementation, potentially causing issues.

  Classes implement -dealloc to perform important actions to deallocate an object. If a category on the class implements -dealloc, it will override the class’s implementation and unexpected deallocation behavior may occur.

  (Clang-Tidy original name: objc-dealloc-in-category)

#### Tags
- /general/Objective-C
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_OBC_FS
### Default
#### OriginalId=objc-forbidden-subclassing
#### Enabled=false
#### Warning=true
#### DisplayName=Forbidden Subclassing
#### HelpText
  Finds Objective-C classes which are subclasses of classes which are not designed to be subclassed.

  By default, includes a list of Objective-C classes which are publicly documented as not supporting subclassing.

  Note

  Instead of using this check, for code under your control, you should add __attribute__((objc_subclassing_restricted)) before your @interface declarations to ensure the compiler prevents others from subclassing your Objective-C classes. See <https://clang.llvm.org/docs/AttributeReference.html\#objc-subclassing-restricted>

  ##### Options

  ForbiddenSuperClassNames     

  Semicolon-separated list of names of Objective-C classes which do not support subclassing.

  Defaults to ABNewPersonViewController;ABPeoplePickerNavigationController;ABPersonViewController;ABUnknownPersonViewController;NSHashTable;NSMapTable;NSPointerArray;NSPointerFunctions;NSTimer;UIActionSheet;UIAlertView;UIImagePickerController;UITextInputMode;UIWebView.

  (Clang-Tidy original name: objc-forbidden-subclassing)

#### Tags
- /general/Objective-C
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_OBC_MH
### Default
#### OriginalId=objc-missing-hash
#### Enabled=false
#### Warning=true
#### DisplayName=Missing Hash
#### HelpText
  Finds Objective-C implementations that implement -isEqual: without also appropriately implementing -hash.

  Apple documentation highlights that objects that are equal must have the same hash value: <https://developer.apple.com/documentation/objectivec/1418956-nsobject/1418795-isequal?language=objc>

  Note that the check only verifies the presence of -hash in scenarios where its omission could result in unexpected behavior. The verification of the implementation of -hash is the responsibility of the developer, e.g., through the addition of unit tests to verify the implementation.

  (Clang-Tidy original name: objc-missing-hash)

#### Tags
- /general/Objective-C
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_OBC_NAL
### Default
#### OriginalId=objc-nsinvocation-argument-lifetime
#### Enabled=false
#### Warning=true
#### DisplayName=Nsinvocation Argument Lifetime
#### HelpText
  Finds calls to NSInvocation methods under ARC that don’t have proper argument object lifetimes. When passing Objective-C objects as parameters to the NSInvocation methods getArgument:atIndex: and getReturnValue:, the values are copied by value into the argument pointer, which leads to to incorrect releasing behavior if the object pointers are not declared __unsafe_unretained.

  For code:

  ``` cpp
  id arg;
  [invocation getArgument:&arg atIndex:2];

  __strong id returnValue;
  [invocation getReturnValue:&returnValue];

  ```


  The fix will be:

  ``` cpp
  __unsafe_unretained id arg;
  [invocation getArgument:&arg atIndex:2];

  __unsafe_unretained id returnValue;
  [invocation getReturnValue:&returnValue];

  ```


  The check will warn on being passed instance variable references that have lifetimes other than __unsafe_unretained, but does not propose a fix:

  ``` cpp
  // "id _returnValue" is declaration of instance variable of class.
  [invocation getReturnValue:&self->_returnValue];

  ```


  (Clang-Tidy original name: objc-nsinvocation-argument-lifetime)

#### Tags
- /general/Objective-C
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_OBC_PD
### Default
#### OriginalId=objc-property-declaration
#### Enabled=false
#### Warning=true
#### DisplayName=Property Declaration
#### HelpText
  Finds property declarations in Objective-C files that do not follow the pattern of property names in Apple’s programming guide. The property name should be in the format of Lower Camel Case.

  For code:

  ``` cpp
  @property(nonatomic, assign) int LowerCamelCase;

  ```


  The fix will be:

  ``` cpp
  @property(nonatomic, assign) int lowerCamelCase;

  ```


  The check will only fix ‘CamelCase’ to ‘camelCase’. In some other cases we will only provide warning messages since the property name could be complicated. Users will need to come up with a proper name by their own.

  This check also accepts special acronyms as prefixes or suffixes. Such prefixes or suffixes will suppress the Lower Camel Case check according to the guide: <https://developer.apple.com/library/content/documentation/Cocoa/Conceptual/CodingGuidelines/Articles/NamingBasics.html\#//apple_ref/doc/uid/20001281-1002931-BBCFHEAB>

  For a full list of well-known acronyms: <https://developer.apple.com/library/content/documentation/Cocoa/Conceptual/CodingGuidelines/Articles/APIAbbreviations.html\#//apple_ref/doc/uid/20001285-BCIHCGAE>

  The corresponding style rule: <https://developer.apple.com/library/content/documentation/Cocoa/Conceptual/CodingGuidelines/Articles/NamingIvarsAndTypes.html\#//apple_ref/doc/uid/20001284-1001757>

  The check will also accept property declared in category with a prefix of lowercase letters followed by a ‘_’ to avoid naming conflict. For example:

  ``` cpp
  @property(nonatomic, assign) int abc_lowerCamelCase;

  ```


  The corresponding style rule: <https://developer.apple.com/library/content/qa/qa1908/_index.html>

  (Clang-Tidy original name: objc-property-declaration)

#### Tags
- /general/Objective-C
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_OBC_SS
### Default
#### OriginalId=objc-super-self
#### Enabled=false
#### Warning=true
#### DisplayName=Super Self
#### HelpText
  Finds invocations of -self on super instances in initializers of subclasses of NSObject and recommends calling a superclass initializer instead.

  Invoking -self on super instances in initializers is a common programmer error when the programmer’s original intent is to call a superclass initializer. Failing to call a superclass initializer breaks initializer chaining and can result in invalid object initialization.

  (Clang-Tidy original name: objc-super-self)

#### Tags
- /general/Objective-C
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_OMP_EE
### Default
#### OriginalId=openmp-exception-escape
#### Enabled=true
#### Warning=true
#### DisplayName=Exception Escape
#### HelpText
  Analyzes OpenMP Structured Blocks and checks that no exception escapes out of the Structured Block it was thrown in.

  As per the OpenMP specification, a structured block is an executable statement, possibly compound, with a single entry at the top and a single exit at the bottom. Which means, throw may not be used to to ‘exit’ out of the structured block. If an exception is not caught in the same structured block it was thrown in, the behaviour is undefined.

  FIXME: this check does not model SEH, setjmp/longjmp.

  WARNING! This check may be expensive on large source files.

  ##### Options

  IgnoredExceptions     

  Comma-separated list containing type names which are not counted as thrown exceptions in the check. Default value is an empty string.

  (Clang-Tidy original name: openmp-exception-escape)

#### Tags
- /general/OpenMP
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_OMP_UDN
### Default
#### OriginalId=openmp-use-default-none
#### Enabled=true
#### Warning=true
#### DisplayName=Use Default None
#### HelpText
  Finds OpenMP directives that are allowed to contain a default clause, but either don’t specify it or the clause is specified but with the kind other than none, and suggests to use the default(none) clause.

  Using default(none) clause forces developers to explicitly specify data sharing attributes for the variables referenced in the construct, thus making it obvious which variables are referenced, and what is their data sharing attribute, thus increasing readability and possibly making errors easier to spot.

  ##### Example

  ``` cpp
  // ``for`` directive can not have ``default`` clause, no diagnostics.
  void n0(const int a) {
  #pragma omp for
    for (int b = 0; b < a; b++)
      ;
  }

  // ``parallel`` directive.

  // ``parallel`` directive can have ``default`` clause, but said clause is not
  // specified, diagnosed.
  void p0_0() {
  #pragma omp parallel
    ;
    // WARNING: OpenMP directive ``parallel`` does not specify ``default``
    //          clause. Consider specifying ``default(none)`` clause.
  }

  // ``parallel`` directive can have ``default`` clause, and said clause is
  // specified, with ``none`` kind, all good.
  void p0_1() {
  #pragma omp parallel default(none)
    ;
  }

  // ``parallel`` directive can have ``default`` clause, and said clause is
  // specified, but with ``shared`` kind, which is not ``none``, diagnose.
  void p0_2() {
  #pragma omp parallel default(shared)
    ;
    // WARNING: OpenMP directive ``parallel`` specifies ``default(shared)``
    //          clause. Consider using ``default(none)`` clause instead.
  }

  // ``parallel`` directive can have ``default`` clause, and said clause is
  // specified, but with ``firstprivate`` kind, which is not ``none``, diagnose.
  void p0_3() {
  #pragma omp parallel default(firstprivate)
    ;
    // WARNING: OpenMP directive ``parallel`` specifies ``default(firstprivate)``
    //          clause. Consider using ``default(none)`` clause instead.
  }

  ```


  (Clang-Tidy original name: openmp-use-default-none)

#### Tags
- /general/OpenMP
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_PRF_FRC
### Default
#### OriginalId=performance-for-range-copy
#### Enabled=true
#### Warning=true
#### DisplayName=For Range Copy
#### HelpText
  Finds C++11 for ranges where the loop variable is copied in each iteration but it would suffice to obtain it by const reference.

  The check is only applied to loop variables of types that are expensive to copy which means they are not trivially copyable or have a non-trivial copy constructor or destructor.

  To ensure that it is safe to replace the copy with a const reference the following heuristic is employed:

    1. The loop variable is const qualified.
    2. The loop variable is not const, but only const methods or operators are invoked on it, or it is used as const reference or value argument in constructors or function calls.



  ##### Options

  WarnOnAllAutoCopies     

  When true, warns on any use of auto as the type of the range-based for loop variable. Default is false.

  AllowedTypes     

  A semicolon-separated list of names of types allowed to be copied in each iteration. Regular expressions are accepted, e.g. [Rr]ef(erence)?$ matches every type with suffix Ref, ref, Reference and reference. The default is empty.

  (Clang-Tidy original name: performance-for-range-copy)

#### Tags
- /general/Performance
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_PRF_FSF
### Default
#### OriginalId=performance-faster-string-find
#### Enabled=true
#### Warning=true
#### DisplayName=Faster String Find
#### HelpText
  Optimize calls to std::string::find() and friends when the needle passed is a single character string literal. The character literal overload is more efficient.

  Examples:

  ``` cpp
  str.find("A");

  // becomes

  str.find('A');

  ```


  ##### Options

  StringLikeClasses     

  Semicolon-separated list of names of string-like classes. By default only ::std::basic_string and ::std::basic_string_view are considered. The check will only consider member functions named find, rfind, find_first_of, find_first_not_of, find_last_of, or find_last_not_of within these classes.

  (Clang-Tidy original name: performance-faster-string-find)

#### Tags
- /general/Performance
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_PRF_IA
### Default
#### OriginalId=performance-inefficient-algorithm
#### Enabled=true
#### Warning=true
#### DisplayName=Inefficient Algorithm
#### HelpText
  Warns on inefficient use of STL algorithms on associative containers.

  Associative containers implements some of the algorithms as methods which should be preferred to the algorithms in the algorithm header. The methods can take advantage of the order of the elements.

  ``` cpp
  std::set<int> s;
  auto it = std::find(s.begin(), s.end(), 43);

  // becomes

  auto it = s.find(43);

  ```


  ``` cpp
  std::set<int> s;
  auto c = std::count(s.begin(), s.end(), 43);

  // becomes

  auto c = s.count(43);

  ```


  (Clang-Tidy original name: performance-inefficient-algorithm)

#### Tags
- /general/Performance
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_PRF_ICIL
### Default
#### OriginalId=performance-implicit-conversion-in-loop
#### Enabled=true
#### Warning=true
#### DisplayName=Implicit Conversion In Loop
#### HelpText
  This warning appears in a range-based loop with a loop variable of const ref type where the type of the variable does not match the one returned by the iterator. This means that an implicit conversion happens, which can for example result in expensive deep copies.

  Example:

  ``` cpp
  map<int, vector<string>> my_map;
  for (const pair<int, vector<string>>& p : my_map) {}
  // The iterator type is in fact pair<const int, vector<string>>, which means
  // that the compiler added a conversion, resulting in a copy of the vectors.

  ```


  The easiest solution is usually to use const auto& instead of writing the type manually.

  (Clang-Tidy original name: performance-implicit-conversion-in-loop)

#### Tags
- /general/Performance
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_PRF_ISC
### Default
#### OriginalId=performance-inefficient-string-concatenation
#### Enabled=true
#### Warning=true
#### DisplayName=Inefficient String Concatenation
#### HelpText
  This check warns about the performance overhead arising from concatenating strings using the operator+, for instance:

  ``` cpp
  std::string a("Foo"), b("Bar");
  a = a + b;

  ```


  Instead of this structure you should use operator+= or std::string’s (std::basic_string) class member function append(). For instance:

  ``` cpp
  std::string a("Foo"), b("Baz");
  for (int i = 0; i < 20000; ++i) {
      a = a + "Bar" + b;
  }

  ```


  Could be rewritten in a greatly more efficient way like:

  ``` cpp
  std::string a("Foo"), b("Baz");
  for (int i = 0; i < 20000; ++i) {
      a.append("Bar").append(b);
  }

  ```


  And this can be rewritten too:

  ``` cpp
  void f(const std::string&) {}
  std::string a("Foo"), b("Baz");
  void g() {
      f(a + "Bar" + b);
  }

  ```


  In a slightly more efficient way like:

  ``` cpp
  void f(const std::string&) {}
  std::string a("Foo"), b("Baz");
  void g() {
      f(std::string(a).append("Bar").append(b));
  }

  ```


  ##### Options

  StrictMode     

  When false, the check will only check the string usage in while, for and for-range statements. Default is false.

  (Clang-Tidy original name: performance-inefficient-string-concatenation)

#### Tags
- /general/Performance
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_PRF_IVO
### Default
#### OriginalId=performance-inefficient-vector-operation
#### Enabled=true
#### Warning=true
#### DisplayName=Inefficient Vector Operation
#### HelpText
  Finds possible inefficient std::vector operations (e.g. push_back, emplace_back) that may cause unnecessary memory reallocations.

  It can also find calls that add element to protobuf repeated field in a loop without calling Reserve() before the loop. Calling Reserve() first can avoid unnecessary memory reallocations.

  Currently, the check only detects following kinds of loops with a single statement body:

    * Counter-based for loops start with 0:



  ``` cpp
  std::vector<int> v;
  for (int i = 0; i < n; ++i) {
    v.push_back(n);
    // This will trigger the warning since the push_back may cause multiple
    // memory reallocations in v. This can be avoid by inserting a 'reserve(n)'
    // statement before the for statement.
  }

  SomeProto p;
  for (int i = 0; i < n; ++i) {
    p.add_xxx(n);
    // This will trigger the warning since the add_xxx may cause multiple memory
    // reallocations. This can be avoid by inserting a
    // 'p.mutable_xxx().Reserve(n)' statement before the for statement.
  }

  ```


    * For-range loops like for (range-declaration : range_expression), the type of range_expression can be std::vector, std::array, std::deque, std::set, std::unordered_set, std::map, std::unordered_set:



  ``` cpp
  std::vector<int> data;
  std::vector<int> v;

  for (auto element : data) {
    v.push_back(element);
    // This will trigger the warning since the 'push_back' may cause multiple
    // memory reallocations in v. This can be avoid by inserting a
    // 'reserve(data.size())' statement before the for statement.
  }

  ```


  ##### Options

  VectorLikeClasses     

  Semicolon-separated list of names of vector-like classes. By default only ::std::vector is considered.

  EnableProto     

  When true, the check will also warn on inefficient operations for proto repeated fields. Otherwise, the check only warns on inefficient vector operations. Default is false.

  (Clang-Tidy original name: performance-inefficient-vector-operation)

#### Tags
- /general/Performance
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_PRF_MCA
### Default
#### OriginalId=performance-move-const-arg
#### Enabled=true
#### Warning=true
#### DisplayName=Move Const Arg
#### HelpText
  The check warns

    * if std::move() is called with a constant argument,
    * if std::move() is called with an argument of a trivially-copyable type,
    * if the result of std::move() is passed as a const reference argument.



  In all three cases, the check will suggest a fix that removes the std::move().

  Here are examples of each of the three cases:

  ``` cpp
  const string s;
  return std::move(s);  // Warning: std::move of the const variable has no effect

  int x;
  return std::move(x);  // Warning: std::move of the variable of a trivially-copyable type has no effect

  void f(const string &s);
  string s;
  f(std::move(s));  // Warning: passing result of std::move as a const reference argument; no move will actually happen

  ```


  ##### Options

  CheckTriviallyCopyableMove     

  If true, enables detection of trivially copyable types that do not have a move constructor. Default is true.

  (Clang-Tidy original name: performance-move-const-arg)

#### Tags
- /general/Performance
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_PRF_MCI
### Default
#### OriginalId=performance-move-constructor-init
#### Enabled=true
#### Warning=true
#### DisplayName=Move Constructor Init
#### HelpText
  “cert-oop11-cpp” redirects here as an alias for this check.

  The check flags user-defined move constructors that have a ctor-initializer initializing a member or base class through a copy constructor instead of a move constructor.

  ##### Options

  IncludeStyle     

  A string specifying which include-style is used, llvm or google. Default is llvm.

  (Clang-Tidy original name: performance-move-constructor-init)

#### Tags
- /general/Performance
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_PRF_NAM
### Default
#### OriginalId=performance-no-automatic-move
#### Enabled=true
#### Warning=true
#### DisplayName=No Automatic Move
#### HelpText
  Finds local variables that cannot be automatically moved due to constness.

  Under [certain conditions](https://en.cppreference.com/w/cpp/language/return\#automatic_move_from_local_variables_and_parameters), local values are automatically moved out when returning from a function. A common mistake is to declare local lvalue variables const, which prevents the move.

  Example [[1]](https://godbolt.org/z/x7SYYA):

  ``` cpp
  StatusOr<std::vector<int>> Cool() {
    std::vector<int> obj = ...;
    return obj;  // calls StatusOr::StatusOr(std::vector<int>&&)
  }

  StatusOr<std::vector<int>> NotCool() {
    const std::vector<int> obj = ...;
    return obj;  // calls `StatusOr::StatusOr(const std::vector<int>&)`
  }

  ```


  The former version (Cool) should be preferred over the latter (Uncool) as it will avoid allocations and potentially large memory copies.

  ##### Semantics

  In the example above, StatusOr::StatusOr(T&&) have the same semantics as long as the copy and move constructors for T have the same semantics. Note that there is no guarantee that S::S(T&&) and S::S(const T&) have the same semantics for any single S, so we’re not providing automated fixes for this check, and judgement should be exerted when making the suggested changes.

  ##### -Wreturn-std-move

  Another case where the move cannot happen is the following:

  ``` cpp
  StatusOr<std::vector<int>> Uncool() {
    std::vector<int>&& obj = ...;
    return obj;  // calls `StatusOr::StatusOr(const std::vector<int>&)`
  }

  ```


  In that case the fix is more consensual: just return std::move(obj). This is handled by the -Wreturn-std-move warning.

  (Clang-Tidy original name: performance-no-automatic-move)

#### Tags
- /general/Performance
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_PRF_NITP
### Default
#### OriginalId=performance-no-int-to-ptr
#### Enabled=true
#### Warning=true
#### DisplayName=No Int To Ptr
#### HelpText
  Diagnoses every integer to pointer cast.

  While casting an (integral) pointer to an integer is obvious - you just get the integral value of the pointer, casting an integer to an (integral) pointer is deceivingly different. While you will get a pointer with that integral value, if you got that integral value via a pointer-to-integer cast originally, the new pointer will lack the provenance information from the original pointer.

  So while (integral) pointer to integer casts are effectively no-ops, and are transparent to the optimizer, integer to (integral) pointer casts are _NOT_ transparent, and may conceal information from optimizer.

  While that may be the intention, it is not always so. For example, let’s take a look at a routine to align the pointer up to the multiple of 16: The obvious, naive implementation for that is:

  ``` cpp
  char* src(char* maybe_underbiased_ptr) {
    uintptr_t maybe_underbiased_intptr = (uintptr_t)maybe_underbiased_ptr;
    uintptr_t aligned_biased_intptr = maybe_underbiased_intptr + 15;
    uintptr_t aligned_intptr = aligned_biased_intptr & (~15);
    return (char*)aligned_intptr; // warning: avoid integer to pointer casts [performance-no-int-to-ptr]
  }

  ```


  The check will rightfully diagnose that cast.

  But when provenance concealment is not the goal of the code, but an accident, this example can be rewritten as follows, without using integer to pointer cast:

  ``` cpp
  char*
  tgt(char* maybe_underbiased_ptr) {
      uintptr_t maybe_underbiased_intptr = (uintptr_t)maybe_underbiased_ptr;
      uintptr_t aligned_biased_intptr = maybe_underbiased_intptr + 15;
      uintptr_t aligned_intptr = aligned_biased_intptr & (~15);
      uintptr_t bias = aligned_intptr - maybe_underbiased_intptr;
      return maybe_underbiased_ptr + bias;
  }

  ```


  (Clang-Tidy original name: performance-no-int-to-ptr)

#### Tags
- /general/Performance
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_PRF_NMC
### Default
#### OriginalId=performance-noexcept-move-constructor
#### Enabled=true
#### Warning=true
#### DisplayName=Noexcept Move Constructor
#### HelpText
  The check flags user-defined move constructors and assignment operators not marked with noexcept or marked with noexcept(expr) where expr evaluates to false (but is not a false literal itself).

  Move constructors of all the types used with STL containers, for example, need to be declared noexcept. Otherwise STL will choose copy constructors instead. The same is valid for move assignment operations.

  (Clang-Tidy original name: performance-noexcept-move-constructor)

#### Tags
- /general/Performance
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_PRF_TD
### Default
#### OriginalId=performance-trivially-destructible
#### Enabled=true
#### Warning=true
#### DisplayName=Trivially Destructible
#### HelpText
  Finds types that could be made trivially-destructible by removing out-of-line defaulted destructor declarations.

  ``` cpp
  struct A: TrivialType {
    ~A(); // Makes A non-trivially-destructible.
    TrivialType trivial_fields;
  };
  A::~A() = default;

  ```


  (Clang-Tidy original name: performance-trivially-destructible)

#### Tags
- /general/Performance
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_PRF_TPIMF
### Default
#### OriginalId=performance-type-promotion-in-math-fn
#### Enabled=true
#### Warning=true
#### DisplayName=Type Promotion In Math Fn
#### HelpText
  Finds calls to C math library functions (from math.h or, in C++, cmath) with implicit float to double promotions.

  For example, warns on ::sin(0.f), because this funciton’s parameter is a double. You probably meant to call std::sin(0.f) (in C++), or sinf(0.f) (in C).

  ``` cpp
  float a;
  asin(a);

  // becomes

  float a;
  std::asin(a);

  ```


  (Clang-Tidy original name: performance-type-promotion-in-math-fn)

#### Tags
- /general/Performance
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_PRF_UCI
### Default
#### OriginalId=performance-unnecessary-copy-initialization
#### Enabled=true
#### Warning=true
#### DisplayName=Unnecessary Copy Initialization
#### HelpText
  Finds local variable declarations that are initialized using the copy constructor of a non-trivially-copyable type but it would suffice to obtain a const reference.

  The check is only applied if it is safe to replace the copy by a const reference. This is the case when the variable is const qualified or when it is only used as a const, i.e. only const methods or operators are invoked on it, or it is used as const reference or value argument in constructors or function calls.

  Example:

  ``` cpp
  const string& constReference();
  void Function() {
    // The warning will suggest making this a const reference.
    const string UnnecessaryCopy = constReference();
  }

  struct Foo {
    const string& name() const;
  };
  void Function(const Foo& foo) {
    // The warning will suggest making this a const reference.
    string UnnecessaryCopy1 = foo.name();
    UnnecessaryCopy1.find("bar");

    // The warning will suggest making this a const reference.
    string UnnecessaryCopy2 = UnnecessaryCopy1;
    UnnecessaryCopy2.find("bar");
  }

  ```


  ##### Options

  AllowedTypes     

  A semicolon-separated list of names of types allowed to be initialized by copying. Regular expressions are accepted, e.g. [Rr]ef(erence)?$ matches every type with suffix Ref, ref, Reference and reference. The default is empty.

  (Clang-Tidy original name: performance-unnecessary-copy-initialization)

#### Tags
- /general/Performance
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_PRF_UVP
### Default
#### OriginalId=performance-unnecessary-value-param
#### Enabled=true
#### Warning=true
#### DisplayName=Unnecessary Value Param
#### HelpText
  Flags value parameter declarations of expensive to copy types that are copied for each invocation but it would suffice to pass them by const reference.

  The check is only applied to parameters of types that are expensive to copy which means they are not trivially copyable or have a non-trivial copy constructor or destructor.

  To ensure that it is safe to replace the value parameter with a const reference the following heuristic is employed:

    1. the parameter is const qualified;
    2. the parameter is not const, but only const methods or operators are invoked on it, or it is used as const reference or value argument in constructors or function calls.



  Example:

  ``` cpp
  void f(const string Value) {
    // The warning will suggest making Value a reference.
  }

  void g(ExpensiveToCopy Value) {
    // The warning will suggest making Value a const reference.
    Value.ConstMethd();
    ExpensiveToCopy Copy(Value);
  }

  ```


  If the parameter is not const, only copied or assigned once and has a non-trivial move-constructor or move-assignment operator respectively the check will suggest to move it.

  Example:

  ``` cpp
  void setValue(string Value) {
    Field = Value;
  }

  ```


  Will become:

  ``` cpp
  #include <utility>

  void setValue(string Value) {
    Field = std::move(Value);
  }

  ```


  ##### Options

  IncludeStyle     

  A string specifying which include-style is used, llvm or google. Default is llvm.

  AllowedTypes     

  A semicolon-separated list of names of types allowed to be passed by value. Regular expressions are accepted, e.g. [Rr]ef(erence)?$ matches every type with suffix Ref, ref, Reference and reference. The default is empty.

  (Clang-Tidy original name: performance-unnecessary-value-param)

#### Tags
- /general/Performance
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_PRT_RSI
### Default
#### OriginalId=portability-restrict-system-includes
#### Enabled=true
#### Warning=true
#### DisplayName=Restrict System Includes
#### HelpText
  Checks to selectively allow or disallow a configurable list of system headers.

  For example:

  In order to **only** allow zlib.h from the system you would set the options to -*,zlib.h.

  ``` cpp
  #include <curses.h>       // Bad: disallowed system header.
  #include <openssl/ssl.h>  // Bad: disallowed system header.
  #include <zlib.h>         // Good: allowed system header.
  #include "src/myfile.h"   // Good: non-system header always allowed.

  ```


  In order to allow everything **except** zlib.h from the system you would set the options to *,-zlib.h.

  ``` cpp
  #include <curses.h>       // Good: allowed system header.
  #include <openssl/ssl.h>  // Good: allowed system header.
  #include <zlib.h>         // Bad: disallowed system header.
  #include "src/myfile.h"   // Good: non-system header always allowed.

  ```


  Since the options support globbing you can use wildcarding to allow groups of headers.

  -*,openssl/*.h will allow all openssl headers but disallow any others.

  ``` cpp
  #include <curses.h>       // Bad: disallowed system header.
  #include <openssl/ssl.h>  // Good: allowed system header.
  #include <openssl/rsa.h>  // Good: allowed system header.
  #include <zlib.h>         // Bad: disallowed system header.
  #include "src/myfile.h"   // Good: non-system header always allowed.

  ```


  ##### Options

  Includes     

  A string containing a comma separated glob list of allowed include filenames. Similar to the -checks glob list for running clang-tidy itself, the two wildcard characters are * and -, to include and exclude globs, respectively. The default is *, which allows all includes.

  (Clang-Tidy original name: portability-restrict-system-includes)

#### Tags
- /general/Portability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_PRT_SI
### Default
#### OriginalId=portability-simd-intrinsics
#### Enabled=true
#### Warning=true
#### DisplayName=Simd Intrinsics
#### HelpText
  Finds SIMD intrinsics calls and suggests std::experimental::simd ([P0214](https://wg21.link/p0214)) alternatives.

  If the option [Suggest](\#cmdoption-arg-suggest) is set to true, for

  ``` cpp
  _mm_add_epi32(a, b); // x86
  vec_add(a, b);       // Power

  ```


  the check suggests an alternative: operator+ on std::experimental::simd objects.

  Otherwise, it just complains the intrinsics are non-portable (and there are [P0214](https://wg21.link/p0214) alternatives).

  Many architectures provide SIMD operations (e.g. x86 SSE/AVX, Power AltiVec/VSX, ARM NEON). It is common that SIMD code implementing the same algorithm, is written in multiple target-dispatching pieces to optimize for different architectures or micro-architectures.

  The C++ standard proposal [P0214](https://wg21.link/p0214) and its extensions cover many common SIMD operations. By migrating from target-dependent intrinsics to [P0214](https://wg21.link/p0214) operations, the SIMD code can be simplified and pieces for different targets can be unified.

  Refer to [P0214](https://wg21.link/p0214) for introduction and motivation for the data-parallel standard library.

  ##### Options

  Suggest     

  If this option is set to true (default is false), the check will suggest [P0214](https://wg21.link/p0214) alternatives, otherwise it only points out the intrinsic function is non-portable.

  Std     

  The namespace used to suggest [P0214](https://wg21.link/p0214) alternatives. If not specified, std:: for -std=c++20 and std::experimental:: for -std=c++11.

  (Clang-Tidy original name: portability-simd-intrinsics)

#### Tags
- /general/Portability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_ACPID
### Default
#### OriginalId=readability-avoid-const-params-in-decls
#### Enabled=true
#### Warning=true
#### DisplayName=Avoid Const Params In Decls
#### HelpText
  Checks whether a function declaration has parameters that are top level const.

  const values in declarations do not affect the signature of a function, so they should not be put there.

  Examples:

  ``` cpp
  void f(const string);   // Bad: const is top level.
  void f(const string&);  // Good: const is not top level.

  ```


  (Clang-Tidy original name: readability-avoid-const-params-in-decls)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_BAS
### Default
#### OriginalId=readability-braces-around-statements
#### Enabled=true
#### Warning=true
#### DisplayName=Braces Around Statements
#### HelpText
  google-readability-braces-around-statements redirects here as an alias for this check.

  Checks that bodies of if statements and loops (for, do while, and while) are inside braces.

  Before:

  ``` cpp
  if (condition)
    statement;

  ```


  After:

  ``` cpp
  if (condition) {
    statement;
  }

  ```


  ##### Options

  ShortStatementLines     

  Defines the minimal number of lines that the statement should have in order to trigger this check.

  The number of lines is counted from the end of condition or initial keyword (do/else) until the last line of the inner statement. Default value 0 means that braces will be added to all statements (not having them already).

  (Clang-Tidy original name: readability-braces-around-statements)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_CMFTS
### Default
#### OriginalId=readability-convert-member-functions-to-static
#### Enabled=true
#### Warning=true
#### DisplayName=Convert Member Functions To Static
#### HelpText
  Finds non-static member functions that can be made static because the functions don’t use this.

  After applying modifications as suggested by the check, running the check again might find more opportunities to mark member functions static.

  After making a member function static, you might want to run the check [readability-static-accessed-through-instance](readability-static-accessed-through-instance.html) to replace calls like Instance.method() by Class::method().

  (Clang-Tidy original name: readability-convert-member-functions-to-static)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_CRT
### Default
#### OriginalId=readability-const-return-type
#### Enabled=true
#### Warning=true
#### DisplayName=Const Return Type
#### HelpText
  Checks for functions with a const-qualified return type and recommends removal of the const keyword. Such use of const is usually superfluous, and can prevent valuable compiler optimizations. Does not (yet) fix trailing return types.

  Examples:

  ``` cpp
  const int foo();
  const Clazz foo();
  Clazz *const foo();

  ```


  Note that this applies strictly to top-level qualification, which excludes pointers or references to const values. For example, these are fine:

  ``` cpp
  const int* foo();
  const int& foo();
  const Clazz* foo();

  ```


  (Clang-Tidy original name: readability-const-return-type)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_CSE
### Default
#### OriginalId=readability-container-size-empty
#### Enabled=true
#### Warning=true
#### DisplayName=Container Size Empty
#### HelpText
  Checks whether a call to the size() method can be replaced with a call to empty().

  The emptiness of a container should be checked using the empty() method instead of the size() method. It is not guaranteed that size() is a constant-time function, and it is generally more efficient and also shows clearer intent to use empty(). Furthermore some containers may implement the empty() method but not implement the size() method. Using empty() whenever possible makes it easier to switch to another container in the future.

  The check issues warning if a container has size() and empty() methods matching following signatures:

  ``` cpp
  size_type size() const;
  bool empty() const;

  ```


  size_type can be any kind of integer type.

  (Clang-Tidy original name: readability-container-size-empty)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_DD
### Default
#### OriginalId=readability-deleted-default
#### Enabled=true
#### Warning=true
#### DisplayName=Deleted Default
#### HelpText
  Checks that constructors and assignment operators marked as = default are not actually deleted by the compiler.

  ``` cpp
  class Example {
  public:
    // This constructor is deleted because I is missing a default value.
    Example() = default;
    // This is fine.
    Example(const Example& Other) = default;
    // This operator is deleted because I cannot be assigned (it is const).
    Example& operator=(const Example& Other) = default;

  private:
    const int I;
  };

  ```


  (Clang-Tidy original name: readability-deleted-default)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_DNP
### Default
#### OriginalId=readability-delete-null-pointer
#### Enabled=true
#### Warning=true
#### DisplayName=Delete Null Pointer
#### HelpText
  Checks the if statements where a pointer’s existence is checked and then deletes the pointer. The check is unnecessary as deleting a null pointer has no effect.

  ``` cpp
  int *p;
  if (p)
    delete p;

  ```


  (Clang-Tidy original name: readability-delete-null-pointer)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_EAR
### Default
#### OriginalId=readability-else-after-return
#### Enabled=true
#### Warning=true
#### DisplayName=Else After Return
#### HelpText
  [LLVM Coding Standards](https://llvm.org/docs/CodingStandards.html) advises to reduce indentation where possible and where it makes understanding code easier. Early exit is one of the suggested enforcements of that. Please do not use else or else if after something that interrupts control flow - like return, break, continue, throw.

  The following piece of code illustrates how the check works. This piece of code:

  ``` cpp
  void foo(int Value) {
    int Local = 0;
    for (int i = 0; i < 42; i++) {
      if (Value == 1) {
        return;
      } else {
        Local++;
      }

      if (Value == 2)
        continue;
      else
        Local++;

      if (Value == 3) {
        throw 42;
      } else {
        Local++;
      }
    }
  }

  ```


  Would be transformed into:

  ``` cpp
  void foo(int Value) {
    int Local = 0;
    for (int i = 0; i < 42; i++) {
      if (Value == 1) {
        return;
      }
      Local++;

      if (Value == 2)
        continue;
      Local++;

      if (Value == 3) {
        throw 42;
      }
      Local++;
    }
  }

  ```


  ##### Options

  WarnOnUnfixable     

  When true, emit a warning for cases where the check can’t output a Fix-It. These can occur with declarations inside the else branch that would have an extended lifetime if the else branch was removed. Default value is true.

  WarnOnConditionVariables     

  When true, the check will attempt to refactor a variable defined inside the condition of the if statement that is used in the else branch defining them just before the if statement. This can only be done if the if statement is the last statement in its parents scope. Default value is true.

  ##### LLVM alias

  There is an alias of this check called llvm-else-after-return. In that version the options [WarnOnUnfixable](\#cmdoption-arg-warnonunfixable) and [WarnOnConditionVariables](\#cmdoption-arg-warnonconditionvariables) are both set to false by default.

  This check helps to enforce this [LLVM Coding Standards recommendation](https://llvm.org/docs/CodingStandards.html\#don-t-use-else-after-a-return).

  (Clang-Tidy original name: readability-else-after-return)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_FCC
### Default
#### OriginalId=readability-function-cognitive-complexity
#### Enabled=true
#### Warning=true
#### DisplayName=Function Cognitive Complexity
#### HelpText
  Checks function Cognitive Complexity metric.

  The metric is implemented as per the [COGNITIVE COMPLEXITY by SonarSource](https://www.sonarsource.com/docs/CognitiveComplexity.pdf) specification version 1.2 (19 April 2017).

  ##### Options

  Threshold     

  Flag functions with Cognitive Complexity exceeding this number. The default is 25.

  ##### Building blocks

  There are three basic building blocks of a Cognitive Complexity metric:

  ###### Increment

  The following structures increase the function’s Cognitive Complexity metric (by 1):

    * Conditional operators:

      * if()
      * else if()
      * else
      * cond ? true : false

    * switch()

    * Loops:

      * for()
      * C++11 range-based for()
      * while()
      * do while()

    * catch ()

    * goto LABEL, goto *(&&LABEL)),

    * sequences of binary logical operators:

      * boolean1 || boolean2
      * boolean1 && boolean2




  ###### Nesting level

  While by itself the nesting level not change the function’s Cognitive Complexity metric, it is tracked, and is used by the next, third building block. The following structures increase the nesting level (by 1):

    * Conditional operators:

      * if()
      * else if()
      * else
      * cond ? true : false

    * switch()

    * Loops:

      * for()
      * C++11 range-based for()
      * while()
      * do while()

    * catch ()

    * Nested functions:

      * C++11 Lambda
      * Nested class
      * Nested struct

    * GNU statement expression

    * Apple Block Declaration




  ###### Nesting increment

  This is where the previous basic building block, [Nesting level](\#nesting-level), matters. The following structures increase the function’s Cognitive Complexity metric by the current [Nesting level](\#nesting-level):

    * Conditional operators:

      * if()
      * cond ? true : false

    * switch()

    * Loops:

      * for()
      * C++11 range-based for()
      * while()
      * do while()

    * catch ()




  ##### Examples

  The simplest case. This function has Cognitive Complexity of 0.

  ``` cpp
  void function0() {}

  ```


  Slightly better example. This function has Cognitive Complexity of 1.

  ``` cpp
  int function1(bool var) {
    if(var) // +1, nesting level +1
      return 42;
    return 0;
  }

  ```


  Full example. This function has Cognitive Complexity of 3.

  ``` cpp
  int function3(bool var1, bool var2) {
    if(var1) { // +1, nesting level +1
      if(var2)  // +2 (1 + current nesting level of 1), nesting level +1
        return 42;
    }

    return 0;
  }

  ```


  ##### Limitations

  The metric is implemented with two notable exceptions:     

    * preprocessor conditionals (\#ifdef, \#if, \#elif, \#else, \#endif) are not accounted for.
    * each method in a recursion cycle is not accounted for. It can’t be fully implemented, because cross-translational-unit analysis would be needed, which is currently not possible in clang-tidy.



  (Clang-Tidy original name: readability-function-cognitive-complexity)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_FS
### Default
#### OriginalId=readability-function-size
#### Enabled=true
#### Warning=true
#### DisplayName=Function Size
#### HelpText
  google-readability-function-size redirects here as an alias for this check.

  Checks for large functions based on various metrics.

  ##### Options

  LineThreshold     

  Flag functions exceeding this number of lines. The default is -1 (ignore the number of lines).

  StatementThreshold     

  Flag functions exceeding this number of statements. This may differ significantly from the number of lines for macro-heavy code. The default is 800.

  BranchThreshold     

  Flag functions exceeding this number of control statements. The default is -1 (ignore the number of branches).

  ParameterThreshold     

  Flag functions that exceed a specified number of parameters. The default is -1 (ignore the number of parameters).

  NestingThreshold     

  Flag compound statements which create next nesting level after NestingThreshold. This may differ significantly from the expected value for macro-heavy code. The default is -1 (ignore the nesting level).

  VariableThreshold     

  Flag functions exceeding this number of variables declared in the body. The default is -1 (ignore the number of variables). Please note that function parameters and variables declared in lambdas, GNU Statement Expressions, and nested class inline functions are not counted.

  (Clang-Tidy original name: readability-function-size)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_IBC
### Default
#### OriginalId=readability-implicit-bool-conversion
#### Enabled=true
#### Warning=true
#### DisplayName=Implicit Bool Conversion
#### HelpText
  This check can be used to find implicit conversions between built-in types and booleans. Depending on use case, it may simply help with readability of the code, or in some cases, point to potential bugs which remain unnoticed due to implicit conversions.

  The following is a real-world example of bug which was hiding behind implicit bool conversion:

  ``` cpp
  class Foo {
    int m_foo;

  public:
    void setFoo(bool foo) { m_foo = foo; } // warning: implicit conversion bool -> int
    int getFoo() { return m_foo; }
  };

  void use(Foo& foo) {
    bool value = foo.getFoo(); // warning: implicit conversion int -> bool
  }

  ```


  This code is the result of unsuccessful refactoring, where type of m_foo changed from bool to int. The programmer forgot to change all occurrences of bool, and the remaining code is no longer correct, yet it still compiles without any visible warnings.

  In addition to issuing warnings, fix-it hints are provided to help solve the reported issues. This can be used for improving readability of code, for example:

  ``` cpp
  void conversionsToBool() {
    float floating;
    bool boolean = floating;
    // ^ propose replacement: bool boolean = floating != 0.0f;

    int integer;
    if (integer) {}
    // ^ propose replacement: if (integer != 0) {}

    int* pointer;
    if (!pointer) {}
    // ^ propose replacement: if (pointer == nullptr) {}

    while (1) {}
    // ^ propose replacement: while (true) {}
  }

  void functionTakingInt(int param);

  void conversionsFromBool() {
    bool boolean;
    functionTakingInt(boolean);
    // ^ propose replacement: functionTakingInt(static_cast<int>(boolean));

    functionTakingInt(true);
    // ^ propose replacement: functionTakingInt(1);
  }

  ```


  In general, the following conversion types are checked:

    * integer expression/literal to boolean (conversion from a single bit bitfield to boolean is explicitly allowed, since there’s no ambiguity / information loss in this case),
    * floating expression/literal to boolean,
    * pointer/pointer to member/nullptr/NULL to boolean,
    * boolean expression/literal to integer (conversion from boolean to a single bit bitfield is explicitly allowed),
    * boolean expression/literal to floating.



  The rules for generating fix-it hints are:

    * in case of conversions from other built-in type to bool, an explicit comparison is proposed to make it clear what exactly is being compared:
      * bool boolean = floating; is changed to bool boolean = floating == 0.0f;,
      * for other types, appropriate literals are used (0, 0u, 0.0f, 0.0, nullptr),
    * in case of negated expressions conversion to bool, the proposed replacement with comparison is simplified:
      * if (!pointer) is changed to if (pointer == nullptr),
    * in case of conversions from bool to other built-in types, an explicit static_cast is proposed to make it clear that a conversion is taking place:
      * int integer = boolean; is changed to int integer = static_cast<int>(boolean);,
    * if the conversion is performed on type literals, an equivalent literal is proposed, according to what type is actually expected, for example:
      * functionTakingBool(0); is changed to functionTakingBool(false);,
      * functionTakingInt(true); is changed to functionTakingInt(1);,
      * for other types, appropriate literals are used (false, true, 0, 1, 0u, 1u, 0.0f, 1.0f, 0.0, 1.0f).



  Some additional accommodations are made for pre-C++11 dialects:

    * false literal conversion to pointer is detected,
    * instead of nullptr literal, 0 is proposed as replacement.



  Occurrences of implicit conversions inside macros and template instantiations are deliberately ignored, as it is not clear how to deal with such cases.

  ##### Options

  AllowIntegerConditions     

  When true, the check will allow conditional integer conversions. Default is false.

  AllowPointerConditions     

  When true, the check will allow conditional pointer conversions. Default is false.

  (Clang-Tidy original name: readability-implicit-bool-conversion)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_ID
### Default
#### OriginalId=readability-isolate-declaration
#### Enabled=true
#### Warning=true
#### DisplayName=Isolate Declaration
#### HelpText
  Detects local variable declarations declaring more than one variable and tries to refactor the code to one statement per declaration.

  The automatic code-transformation will use the same indentation as the original for every created statement and add a line break after each statement. It keeps the order of the variable declarations consistent, too.

  ``` cpp
  void f() {
    int * pointer = nullptr, value = 42, * const const_ptr = &value;
    // This declaration will be diagnosed and transformed into:
    // int * pointer = nullptr;
    // int value = 42;
    // int * const const_ptr = &value;
  }

  ```


  The check excludes places where it is necessary or common to declare multiple variables in one statement and there is no other way supported in the language. Please note that structured bindings are not considered.

  ``` cpp
  // It is not possible to transform this declaration and doing the declaration
  // before the loop will increase the scope of the variable 'Begin' and 'End'
  // which is undesirable.
  for (int Begin = 0, End = 100; Begin < End; ++Begin);
  if (int Begin = 42, Result = some_function(Begin); Begin == Result);

  // It is not possible to transform this declaration because the result is
  // not functionality preserving as 'j' and 'k' would not be part of the
  // 'if' statement anymore.
  if (SomeCondition())
    int i = 42, j = 43, k = function(i,j);

  ```


  ##### Limitations

  Global variables and member variables are excluded.

  The check currently does not support the automatic transformation of member-pointer-types.

  ``` cpp
  struct S {
    int a;
    const int b;
    void f() {}
  };

  void f() {
    // Only a diagnostic message is emitted
    int S::*p = &S::a, S::*const q = &S::a;
  }

  ```


  Furthermore, the transformation is very cautious when it detects various kinds of macros or preprocessor directives in the range of the statement. In this case the transformation will not happen to avoid unexpected side-effects due to macros.

  ``` cpp
  #define NULL 0
  #define MY_NICE_TYPE int **
  #define VAR_NAME(name) name##__LINE__
  #define A_BUNCH_OF_VARIABLES int m1 = 42, m2 = 43, m3 = 44;

  void macros() {
    int *p1 = NULL, *p2 = NULL;
    // Will be transformed to
    // int *p1 = NULL;
    // int *p2 = NULL;

    MY_NICE_TYPE p3, v1, v2;
    // Won't be transformed, but a diagnostic is emitted.

    int VAR_NAME(v3),
        VAR_NAME(v4),
        VAR_NAME(v5);
    // Won't be transformed, but a diagnostic is emitted.

    A_BUNCH_OF_VARIABLES
    // Won't be transformed, but a diagnostic is emitted.

    int Unconditional,
  #if CONFIGURATION
        IfConfigured = 42,
  #else
        IfConfigured = 0;
  #endif
    // Won't be transformed, but a diagnostic is emitted.
  }

  ```


  (Clang-Tidy original name: readability-isolate-declaration)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_IDPN
### Default
#### OriginalId=readability-inconsistent-declaration-parameter-name
#### Enabled=true
#### Warning=true
#### DisplayName=Inconsistent Declaration Parameter Name
#### HelpText
  Find function declarations which differ in parameter names.

  Example:

  ``` cpp
  // in foo.hpp:
  void foo(int a, int b, int c);

  // in foo.cpp:
  void foo(int d, int e, int f); // warning

  ```


  This check should help to enforce consistency in large projects, where it often happens that a definition of function is refactored, changing the parameter names, but its declaration in header file is not updated. With this check, we can easily find and correct such inconsistencies, keeping declaration and definition always in sync.

  Unnamed parameters are allowed and are not taken into account when comparing function declarations, for example:

  ``` cpp
  void foo(int a);
  void foo(int); // no warning

  ```


  One name is also allowed to be a case-insensitive prefix/suffix of the other:

  ``` cpp
  void foo(int count);
  void foo(int count_input) { // no warning
    int count = adjustCount(count_input);
  }

  ```


  To help with refactoring, in some cases fix-it hints are generated to align parameter names to a single naming convention. This works with the assumption that the function definition is the most up-to-date version, as it directly references parameter names in its body. Example:

  ``` cpp
  void foo(int a); // warning and fix-it hint (replace "a" to "b")
  int foo(int b) { return b + 2; } // definition with use of "b"

  ```


  In the case of multiple redeclarations or function template specializations, a warning is issued for every redeclaration or specialization inconsistent with the definition or the first declaration seen in a translation unit.

  IgnoreMacros     

  If this option is set to true (default is true), the check will not warn about names declared inside macros.

  Strict     

  If this option is set to true (default is false), then names must match exactly (or be absent).

  (Clang-Tidy original name: readability-inconsistent-declaration-parameter-name)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_IN
### Default
#### OriginalId=readability-identifier-naming
#### Enabled=true
#### Warning=true
#### DisplayName=Identifier Naming
#### HelpText
  Checks for identifiers naming style mismatch.

  This check will try to enforce coding guidelines on the identifiers naming. It supports one of the following casing types and tries to convert from one to another if a mismatch is detected

  Casing types include:

    * lower_case,
    * UPPER_CASE,
    * camelBack,
    * CamelCase,
    * camel_Snake_Back,
    * Camel_Snake_Case,
    * aNy_CasE.



  It also supports a fixed prefix and suffix that will be prepended or appended to the identifiers, regardless of the casing.

  Many configuration options are available, in order to be able to create different rules for different kinds of identifiers. In general, the rules are falling back to a more generic rule if the specific case is not configured.

  The naming of virtual methods is reported where they occur in the base class, but not where they are overridden, as it can’t be fixed locally there. This also applies for pseudo-override patterns like CRTP.

  ##### Options

  The following options are describe below:

    * [AbstractClassCase](\#cmdoption-arg-abstractclasscase), [AbstractClassPrefix](\#cmdoption-arg-abstractclassprefix), [AbstractClassSuffix](\#cmdoption-arg-abstractclasssuffix), [AbstractClassIgnoredRegexp](\#cmdoption-arg-abstractclassignoredregexp)
    * [AggressiveDependentMemberLookup](\#cmdoption-arg-aggressivedependentmemberlookup)
    * [ClassCase](\#cmdoption-arg-classcase), [ClassPrefix](\#cmdoption-arg-classprefix), [ClassSuffix](\#cmdoption-arg-classsuffix), [ClassIgnoredRegexp](\#cmdoption-arg-classignoredregexp)
    * [ClassConstantCase](\#cmdoption-arg-classconstantcase), [ClassConstantPrefix](\#cmdoption-arg-classconstantprefix), [ClassConstantSuffix](\#cmdoption-arg-classconstantsuffix), [ClassConstantIgnoredRegexp](\#cmdoption-arg-classconstantignoredregexp)
    * [ClassMemberCase](\#cmdoption-arg-classmembercase), [ClassMemberPrefix](\#cmdoption-arg-classmemberprefix), [ClassMemberSuffix](\#cmdoption-arg-classmembersuffix), [ClassMemberIgnoredRegexp](\#cmdoption-arg-classmemberignoredregexp)
    * [ClassMethodCase](\#cmdoption-arg-classmethodcase), [ClassMethodPrefix](\#cmdoption-arg-classmethodprefix), [ClassMethodSuffix](\#cmdoption-arg-classmethodsuffix), [ClassMethodIgnoredRegexp](\#cmdoption-arg-classmethodignoredregexp)
    * [ConstantCase](\#cmdoption-arg-constantcase), [ConstantPrefix](\#cmdoption-arg-constantprefix), [ConstantSuffix](\#cmdoption-arg-constantsuffix), [ConstantIgnoredRegexp](\#cmdoption-arg-constantignoredregexp)
    * [ConstantMemberCase](\#cmdoption-arg-constantmembercase), [ConstantMemberPrefix](\#cmdoption-arg-constantmemberprefix), [ConstantMemberSuffix](\#cmdoption-arg-constantmembersuffix), [ConstantMemberIgnoredRegexp](\#cmdoption-arg-constantmemberignoredregexp)
    * [ConstantParameterCase](\#cmdoption-arg-constantparametercase), [ConstantParameterPrefix](\#cmdoption-arg-constantparameterprefix), [ConstantParameterSuffix](\#cmdoption-arg-constantparametersuffix), [ConstantParameterIgnoredRegexp](\#cmdoption-arg-constantparameterignoredregexp)
    * [ConstantPointerParameterCase](\#cmdoption-arg-constantpointerparametercase), [ConstantPointerParameterPrefix](\#cmdoption-arg-constantpointerparameterprefix), [ConstantPointerParameterSuffix](\#cmdoption-arg-constantpointerparametersuffix), [ConstantPointerParameterIgnoredRegexp](\#cmdoption-arg-constantpointerparameterignoredregexp)
    * [ConstexprFunctionCase](\#cmdoption-arg-constexprfunctioncase), [ConstexprFunctionPrefix](\#cmdoption-arg-constexprfunctionprefix), [ConstexprFunctionSuffix](\#cmdoption-arg-constexprfunctionsuffix), [ConstexprFunctionIgnoredRegexp](\#cmdoption-arg-constexprfunctionignoredregexp)
    * [ConstexprMethodCase](\#cmdoption-arg-constexprmethodcase), [ConstexprMethodPrefix](\#cmdoption-arg-constexprmethodprefix), [ConstexprMethodSuffix](\#cmdoption-arg-constexprmethodsuffix), [ConstexprMethodIgnoredRegexp](\#cmdoption-arg-constexprmethodignoredregexp)
    * [ConstexprVariableCase](\#cmdoption-arg-constexprvariablecase), [ConstexprVariablePrefix](\#cmdoption-arg-constexprvariableprefix), [ConstexprVariableSuffix](\#cmdoption-arg-constexprvariablesuffix), [ConstexprVariableIgnoredRegexp](\#cmdoption-arg-constexprvariableignoredregexp)
    * [EnumCase](\#cmdoption-arg-enumcase), [EnumPrefix](\#cmdoption-arg-enumprefix), [EnumSuffix](\#cmdoption-arg-enumsuffix), [EnumIgnoredRegexp](\#cmdoption-arg-enumignoredregexp)
    * [EnumConstantCase](\#cmdoption-arg-enumconstantcase), [EnumConstantPrefix](\#cmdoption-arg-enumconstantprefix), [EnumConstantSuffix](\#cmdoption-arg-enumconstantsuffix), [EnumConstantIgnoredRegexp](\#cmdoption-arg-enumconstantignoredregexp)
    * [FunctionCase](\#cmdoption-arg-functioncase), [FunctionPrefix](\#cmdoption-arg-functionprefix), [FunctionSuffix](\#cmdoption-arg-functionsuffix), [FunctionIgnoredRegexp](\#cmdoption-arg-functionignoredregexp)
    * [GetConfigPerFile](\#cmdoption-arg-getconfigperfile)
    * [GlobalConstantCase](\#cmdoption-arg-globalconstantcase), [GlobalConstantPrefix](\#cmdoption-arg-globalconstantprefix), [GlobalConstantSuffix](\#cmdoption-arg-globalconstantsuffix), [GlobalConstantIgnoredRegexp](\#cmdoption-arg-globalconstantignoredregexp)
    * [GlobalConstantPointerCase](\#cmdoption-arg-globalconstantpointercase), [GlobalConstantPointerPrefix](\#cmdoption-arg-globalconstantpointerprefix), [GlobalConstantPointerSuffix](\#cmdoption-arg-globalconstantpointersuffix), [GlobalConstantPointerIgnoredRegexp](\#cmdoption-arg-globalconstantpointerignoredregexp)
    * [GlobalFunctionCase](\#cmdoption-arg-globalfunctioncase), [GlobalFunctionPrefix](\#cmdoption-arg-globalfunctionprefix), [GlobalFunctionSuffix](\#cmdoption-arg-globalfunctionsuffix), [GlobalFunctionIgnoredRegexp](\#cmdoption-arg-globalfunctionignoredregexp)
    * [GlobalPointerCase](\#cmdoption-arg-globalpointercase), [GlobalPointerPrefix](\#cmdoption-arg-globalpointerprefix), [GlobalPointerSuffix](\#cmdoption-arg-globalpointersuffix), [GlobalPointerIgnoredRegexp](\#cmdoption-arg-globalpointerignoredregexp)
    * [GlobalVariableCase](\#cmdoption-arg-globalvariablecase), [GlobalVariablePrefix](\#cmdoption-arg-globalvariableprefix), [GlobalVariableSuffix](\#cmdoption-arg-globalvariablesuffix), [GlobalVariableIgnoredRegexp](\#cmdoption-arg-globalvariableignoredregexp)
    * [IgnoreMainLikeFunctions](\#cmdoption-arg-ignoremainlikefunctions)
    * [InlineNamespaceCase](\#cmdoption-arg-inlinenamespacecase), [InlineNamespacePrefix](\#cmdoption-arg-inlinenamespaceprefix), [InlineNamespaceSuffix](\#cmdoption-arg-inlinenamespacesuffix), [InlineNamespaceIgnoredRegexp](\#cmdoption-arg-inlinenamespaceignoredregexp)
    * [LocalConstantCase](\#cmdoption-arg-localconstantcase), [LocalConstantPrefix](\#cmdoption-arg-localconstantprefix), [LocalConstantSuffix](\#cmdoption-arg-localconstantsuffix), [LocalConstantIgnoredRegexp](\#cmdoption-arg-localconstantignoredregexp)
    * [LocalConstantPointerCase](\#cmdoption-arg-localconstantpointercase), [LocalConstantPointerPrefix](\#cmdoption-arg-localconstantpointerprefix), [LocalConstantPointerSuffix](\#cmdoption-arg-localconstantpointersuffix), [LocalConstantPointerIgnoredRegexp](\#cmdoption-arg-localconstantpointerignoredregexp)
    * [LocalPointerCase](\#cmdoption-arg-localpointercase), [LocalPointerPrefix](\#cmdoption-arg-localpointerprefix), [LocalPointerSuffix](\#cmdoption-arg-localpointersuffix), [LocalPointerIgnoredRegexp](\#cmdoption-arg-localpointerignoredregexp)
    * [LocalVariableCase](\#cmdoption-arg-localvariablecase), [LocalVariablePrefix](\#cmdoption-arg-localvariableprefix), [LocalVariableSuffix](\#cmdoption-arg-localvariablesuffix), [LocalVariableIgnoredRegexp](\#cmdoption-arg-localvariableignoredregexp)
    * [MacroDefinitionCase](\#cmdoption-arg-macrodefinitioncase), [MacroDefinitionPrefix](\#cmdoption-arg-macrodefinitionprefix), [MacroDefinitionSuffix](\#cmdoption-arg-macrodefinitionsuffix), [MacroDefinitionIgnoredRegexp](\#cmdoption-arg-macrodefinitionignoredregexp)
    * [MemberCase](\#cmdoption-arg-membercase), [MemberPrefix](\#cmdoption-arg-memberprefix), [MemberSuffix](\#cmdoption-arg-membersuffix), [MemberIgnoredRegexp](\#cmdoption-arg-memberignoredregexp)
    * [MethodCase](\#cmdoption-arg-methodcase), [MethodPrefix](\#cmdoption-arg-methodprefix), [MethodSuffix](\#cmdoption-arg-methodsuffix), [MethodIgnoredRegexp](\#cmdoption-arg-methodignoredregexp)
    * [NamespaceCase](\#cmdoption-arg-namespacecase), [NamespacePrefix](\#cmdoption-arg-namespaceprefix), [NamespaceSuffix](\#cmdoption-arg-namespacesuffix), [NamespaceIgnoredRegexp](\#cmdoption-arg-namespaceignoredregexp)
    * [ParameterCase](\#cmdoption-arg-parametercase), [ParameterPrefix](\#cmdoption-arg-parameterprefix), [ParameterSuffix](\#cmdoption-arg-parametersuffix), [ParameterIgnoredRegexp](\#cmdoption-arg-parameterignoredregexp)
    * [ParameterPackCase](\#cmdoption-arg-parameterpackcase), [ParameterPackPrefix](\#cmdoption-arg-parameterpackprefix), [ParameterPackSuffix](\#cmdoption-arg-parameterpacksuffix), [ParameterPackIgnoredRegexp](\#cmdoption-arg-parameterpackignoredregexp)
    * [PointerParameterCase](\#cmdoption-arg-pointerparametercase), [PointerParameterPrefix](\#cmdoption-arg-pointerparameterprefix), [PointerParameterSuffix](\#cmdoption-arg-pointerparametersuffix), [PointerParameterIgnoredRegexp](\#cmdoption-arg-pointerparameterignoredregexp)
    * [PrivateMemberCase](\#cmdoption-arg-privatemembercase), [PrivateMemberPrefix](\#cmdoption-arg-privatememberprefix), [PrivateMemberSuffix](\#cmdoption-arg-privatemembersuffix), [PrivateMemberIgnoredRegexp](\#cmdoption-arg-privatememberignoredregexp)
    * [PrivateMethodCase](\#cmdoption-arg-privatemethodcase), [PrivateMethodPrefix](\#cmdoption-arg-privatemethodprefix), [PrivateMethodSuffix](\#cmdoption-arg-privatemethodsuffix), [PrivateMethodIgnoredRegexp](\#cmdoption-arg-privatemethodignoredregexp)
    * [ProtectedMemberCase](\#cmdoption-arg-protectedmembercase), [ProtectedMemberPrefix](\#cmdoption-arg-protectedmemberprefix), [ProtectedMemberSuffix](\#cmdoption-arg-protectedmembersuffix), [ProtectedMemberIgnoredRegexp](\#cmdoption-arg-protectedmemberignoredregexp)
    * [ProtectedMethodCase](\#cmdoption-arg-protectedmethodcase), [ProtectedMethodPrefix](\#cmdoption-arg-protectedmethodprefix), [ProtectedMethodSuffix](\#cmdoption-arg-protectedmethodsuffix), [ProtectedMethodIgnoredRegexp](\#cmdoption-arg-protectedmethodignoredregexp)
    * [PublicMemberCase](\#cmdoption-arg-publicmembercase), [PublicMemberPrefix](\#cmdoption-arg-publicmemberprefix), [PublicMemberSuffix](\#cmdoption-arg-publicmembersuffix), [PublicMemberIgnoredRegexp](\#cmdoption-arg-publicmemberignoredregexp)
    * [PublicMethodCase](\#cmdoption-arg-publicmethodcase), [PublicMethodPrefix](\#cmdoption-arg-publicmethodprefix), [PublicMethodSuffix](\#cmdoption-arg-publicmethodsuffix), [PublicMethodIgnoredRegexp](\#cmdoption-arg-publicmethodignoredregexp)
    * [ScopedEnumConstantCase](\#cmdoption-arg-scopedenumconstantcase), [ScopedEnumConstantPrefix](\#cmdoption-arg-scopedenumconstantprefix), [ScopedEnumConstantSuffix](\#cmdoption-arg-scopedenumconstantsuffix), [ScopedEnumConstantIgnoredRegexp](\#cmdoption-arg-scopedenumconstantignoredregexp)
    * [StaticConstantCase](\#cmdoption-arg-staticconstantcase), [StaticConstantPrefix](\#cmdoption-arg-staticconstantprefix), [StaticConstantSuffix](\#cmdoption-arg-staticconstantsuffix), [StaticConstantIgnoredRegexp](\#cmdoption-arg-staticconstantignoredregexp)
    * [StaticVariableCase](\#cmdoption-arg-staticvariablecase), [StaticVariablePrefix](\#cmdoption-arg-staticvariableprefix), [StaticVariableSuffix](\#cmdoption-arg-staticvariablesuffix), [StaticVariableIgnoredRegexp](\#cmdoption-arg-staticvariableignoredregexp)
    * [StructCase](\#cmdoption-arg-structcase), [StructPrefix](\#cmdoption-arg-structprefix), [StructSuffix](\#cmdoption-arg-structsuffix), [StructIgnoredRegexp](\#cmdoption-arg-structignoredregexp)
    * [TemplateParameterCase](\#cmdoption-arg-templateparametercase), [TemplateParameterPrefix](\#cmdoption-arg-templateparameterprefix), [TemplateParameterSuffix](\#cmdoption-arg-templateparametersuffix), [TemplateParameterIgnoredRegexp](\#cmdoption-arg-templateparameterignoredregexp)
    * [TemplateTemplateParameterCase](\#cmdoption-arg-templatetemplateparametercase), [TemplateTemplateParameterPrefix](\#cmdoption-arg-templatetemplateparameterprefix), [TemplateTemplateParameterSuffix](\#cmdoption-arg-templatetemplateparametersuffix), [TemplateTemplateParameterIgnoredRegexp](\#cmdoption-arg-templatetemplateparameterignoredregexp)
    * [TypeAliasCase](\#cmdoption-arg-typealiascase), [TypeAliasPrefix](\#cmdoption-arg-typealiasprefix), [TypeAliasSuffix](\#cmdoption-arg-typealiassuffix), [TypeAliasIgnoredRegexp](\#cmdoption-arg-typealiasignoredregexp)
    * [TypedefCase](\#cmdoption-arg-typedefcase), [TypedefPrefix](\#cmdoption-arg-typedefprefix), [TypedefSuffix](\#cmdoption-arg-typedefsuffix), [TypedefIgnoredRegexp](\#cmdoption-arg-typedefignoredregexp)
    * [TypeTemplateParameterCase](\#cmdoption-arg-typetemplateparametercase), [TypeTemplateParameterPrefix](\#cmdoption-arg-typetemplateparameterprefix), [TypeTemplateParameterSuffix](\#cmdoption-arg-typetemplateparametersuffix), [TypeTemplateParameterIgnoredRegexp](\#cmdoption-arg-typetemplateparameterignoredregexp)
    * [UnionCase](\#cmdoption-arg-unioncase), [UnionPrefix](\#cmdoption-arg-unionprefix), [UnionSuffix](\#cmdoption-arg-unionsuffix), [UnionIgnoredRegexp](\#cmdoption-arg-unionignoredregexp)
    * [ValueTemplateParameterCase](\#cmdoption-arg-valuetemplateparametercase), [ValueTemplateParameterPrefix](\#cmdoption-arg-valuetemplateparameterprefix), [ValueTemplateParameterSuffix](\#cmdoption-arg-valuetemplateparametersuffix), [ValueTemplateParameterIgnoredRegexp](\#cmdoption-arg-valuetemplateparameterignoredregexp)
    * [VariableCase](\#cmdoption-arg-variablecase), [VariablePrefix](\#cmdoption-arg-variableprefix), [VariableSuffix](\#cmdoption-arg-variablesuffix), [VariableIgnoredRegexp](\#cmdoption-arg-variableignoredregexp)
    * [VirtualMethodCase](\#cmdoption-arg-virtualmethodcase), [VirtualMethodPrefix](\#cmdoption-arg-virtualmethodprefix), [VirtualMethodSuffix](\#cmdoption-arg-virtualmethodsuffix), [VirtualMethodIgnoredRegexp](\#cmdoption-arg-virtualmethodignoredregexp)



  AbstractClassCase     

  When defined, the check will ensure abstract class names conform to the selected casing.

  AbstractClassPrefix     

  When defined, the check will ensure abstract class names will add the prefixed with the given value (regardless of casing).

  AbstractClassIgnoredRegexp     

  Identifier naming checks won’t be enforced for abstract class names matching this regular expression.

  AbstractClassSuffix     

  When defined, the check will ensure abstract class names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * AbstractClassCase of lower_case
    * AbstractClassPrefix of pre_
    * AbstractClassSuffix of _post



  Identifies and/or transforms abstract class names as follows:

  Before:

  ``` cpp
  class ABSTRACT_CLASS {
  public:
    ABSTRACT_CLASS();
  };

  ```


  After:

  ``` cpp
  class pre_abstract_class_post {
  public:
    pre_abstract_class_post();
  };

  ```


  AggressiveDependentMemberLookup     

  When set to true the check will look in dependent base classes for dependent member references that need changing. This can lead to errors with template specializations so the default value is false.

  For example using values of:

    * ClassMemberCase of lower_case



  Before:

  ``` cpp
  template <typename T>
  struct Base {
    T BadNamedMember;
  };

  template <typename T>
  struct Derived : Base<T> {
    void reset() {
      this->BadNamedMember = 0;
    }
  };

  ```


  After if AggressiveDependentMemberLookup is false:

  ``` cpp
  template <typename T>
  struct Base {
    T bad_named_member;
  };

  template <typename T>
  struct Derived : Base<T> {
    void reset() {
      this->BadNamedMember = 0;
    }
  };

  ```


  After if AggressiveDependentMemberLookup is true:

  ``` cpp
  template <typename T>
  struct Base {
    T bad_named_member;
  };

  template <typename T>
  struct Derived : Base<T> {
    void reset() {
      this->bad_named_member = 0;
    }
  };

  ```


  ClassCase     

  When defined, the check will ensure class names conform to the selected casing.

  ClassPrefix     

  When defined, the check will ensure class names will add the prefixed with the given value (regardless of casing).

  ClassIgnoredRegexp     

  Identifier naming checks won’t be enforced for class names matching this regular expression.

  ClassSuffix     

  When defined, the check will ensure class names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * ClassCase of lower_case
    * ClassPrefix of pre_
    * ClassSuffix of _post



  Identifies and/or transforms class names as follows:

  Before:

  ``` cpp
  class FOO {
  public:
    FOO();
    ~FOO();
  };

  ```


  After:

  ``` cpp
  class pre_foo_post {
  public:
    pre_foo_post();
    ~pre_foo_post();
  };

  ```


  ClassConstantCase     

  When defined, the check will ensure class constant names conform to the selected casing.

  ClassConstantPrefix     

  When defined, the check will ensure class constant names will add the prefixed with the given value (regardless of casing).

  ClassConstantIgnoredRegexp     

  Identifier naming checks won’t be enforced for class constant names matching this regular expression.

  ClassConstantSuffix     

  When defined, the check will ensure class constant names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * ClassConstantCase of lower_case
    * ClassConstantPrefix of pre_
    * ClassConstantSuffix of _post



  Identifies and/or transforms class constant names as follows:

  Before:

  ``` cpp
  class FOO {
  public:
    static const int CLASS_CONSTANT;
  };

  ```


  After:

  ``` cpp
  class FOO {
  public:
    static const int pre_class_constant_post;
  };

  ```


  ClassMemberCase     

  When defined, the check will ensure class member names conform to the selected casing.

  ClassMemberPrefix     

  When defined, the check will ensure class member names will add the prefixed with the given value (regardless of casing).

  ClassMemberIgnoredRegexp     

  Identifier naming checks won’t be enforced for class member names matching this regular expression.

  ClassMemberSuffix     

  When defined, the check will ensure class member names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * ClassMemberCase of lower_case
    * ClassMemberPrefix of pre_
    * ClassMemberSuffix of _post



  Identifies and/or transforms class member names as follows:

  Before:

  ``` cpp
  class FOO {
  public:
    static int CLASS_CONSTANT;
  };

  ```


  After:

  ``` cpp
  class FOO {
  public:
    static int pre_class_constant_post;
  };

  ```


  ClassMethodCase     

  When defined, the check will ensure class method names conform to the selected casing.

  ClassMethodPrefix     

  When defined, the check will ensure class method names will add the prefixed with the given value (regardless of casing).

  ClassMethodIgnoredRegexp     

  Identifier naming checks won’t be enforced for class method names matching this regular expression.

  ClassMethodSuffix     

  When defined, the check will ensure class method names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * ClassMethodCase of lower_case
    * ClassMethodPrefix of pre_
    * ClassMethodSuffix of _post



  Identifies and/or transforms class method names as follows:

  Before:

  ``` cpp
  class FOO {
  public:
    int CLASS_MEMBER();
  };

  ```


  After:

  ``` cpp
  class FOO {
  public:
    int pre_class_member_post();
  };

  ```


  ConstantCase     

  When defined, the check will ensure constant names conform to the selected casing.

  ConstantPrefix     

  When defined, the check will ensure constant names will add the prefixed with the given value (regardless of casing).

  ConstantIgnoredRegexp     

  Identifier naming checks won’t be enforced for constant names matching this regular expression.

  ConstantSuffix     

  When defined, the check will ensure constant names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * ConstantCase of lower_case
    * ConstantPrefix of pre_
    * ConstantSuffix of _post



  Identifies and/or transforms constant names as follows:

  Before:

  ``` cpp
  void function() { unsigned const MyConst_array[] = {1, 2, 3}; }

  ```


  After:

  ``` cpp
  void function() { unsigned const pre_myconst_array_post[] = {1, 2, 3}; }

  ```


  ConstantMemberCase     

  When defined, the check will ensure constant member names conform to the selected casing.

  ConstantMemberPrefix     

  When defined, the check will ensure constant member names will add the prefixed with the given value (regardless of casing).

  ConstantMemberIgnoredRegexp     

  Identifier naming checks won’t be enforced for constant member names matching this regular expression.

  ConstantMemberSuffix     

  When defined, the check will ensure constant member names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * ConstantMemberCase of lower_case
    * ConstantMemberPrefix of pre_
    * ConstantMemberSuffix of _post



  Identifies and/or transforms constant member names as follows:

  Before:

  ``` cpp
  class Foo {
    char const MY_ConstMember_string[4] = "123";
  }

  ```


  After:

  ``` cpp
  class Foo {
    char const pre_my_constmember_string_post[4] = "123";
  }

  ```


  ConstantParameterCase     

  When defined, the check will ensure constant parameter names conform to the selected casing.

  ConstantParameterPrefix     

  When defined, the check will ensure constant parameter names will add the prefixed with the given value (regardless of casing).

  ConstantParameterIgnoredRegexp     

  Identifier naming checks won’t be enforced for constant parameter names matching this regular expression.

  ConstantParameterSuffix     

  When defined, the check will ensure constant parameter names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * ConstantParameterCase of lower_case
    * ConstantParameterPrefix of pre_
    * ConstantParameterSuffix of _post



  Identifies and/or transforms constant parameter names as follows:

  Before:

  ``` cpp
  void GLOBAL_FUNCTION(int PARAMETER_1, int const CONST_parameter);

  ```


  After:

  ``` cpp
  void GLOBAL_FUNCTION(int PARAMETER_1, int const pre_const_parameter_post);

  ```


  ConstantPointerParameterCase     

  When defined, the check will ensure constant pointer parameter names conform to the selected casing.

  ConstantPointerParameterPrefix     

  When defined, the check will ensure constant pointer parameter names will add the prefixed with the given value (regardless of casing).

  ConstantPointerParameterIgnoredRegexp     

  Identifier naming checks won’t be enforced for constant pointer parameter names matching this regular expression.

  ConstantPointerParameterSuffix     

  When defined, the check will ensure constant pointer parameter names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * ConstantPointerParameterCase of lower_case
    * ConstantPointerParameterPrefix of pre_
    * ConstantPointerParameterSuffix of _post



  Identifies and/or transforms constant pointer parameter names as follows:

  Before:

  ``` cpp
  void GLOBAL_FUNCTION(int const *CONST_parameter);

  ```


  After:

  ``` cpp
  void GLOBAL_FUNCTION(int const *pre_const_parameter_post);

  ```


  ConstexprFunctionCase     

  When defined, the check will ensure constexpr function names conform to the selected casing.

  ConstexprFunctionPrefix     

  When defined, the check will ensure constexpr function names will add the prefixed with the given value (regardless of casing).

  ConstexprFunctionIgnoredRegexp     

  Identifier naming checks won’t be enforced for constexpr function names matching this regular expression.

  ConstexprFunctionSuffix     

  When defined, the check will ensure constexpr function names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * ConstexprFunctionCase of lower_case
    * ConstexprFunctionPrefix of pre_
    * ConstexprFunctionSuffix of _post



  Identifies and/or transforms constexpr function names as follows:

  Before:

  ``` cpp
  constexpr int CE_function() { return 3; }

  ```


  After:

  ``` cpp
  constexpr int pre_ce_function_post() { return 3; }

  ```


  ConstexprMethodCase     

  When defined, the check will ensure constexpr method names conform to the selected casing.

  ConstexprMethodPrefix     

  When defined, the check will ensure constexpr method names will add the prefixed with the given value (regardless of casing).

  ConstexprMethodIgnoredRegexp     

  Identifier naming checks won’t be enforced for constexpr method names matching this regular expression.

  ConstexprMethodSuffix     

  When defined, the check will ensure constexpr method names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * ConstexprMethodCase of lower_case
    * ConstexprMethodPrefix of pre_
    * ConstexprMethodSuffix of _post



  Identifies and/or transforms constexpr method names as follows:

  Before:

  ``` cpp
  class Foo {
  public:
    constexpr int CST_expr_Method() { return 2; }
  }

  ```


  After:

  ``` cpp
  class Foo {
  public:
    constexpr int pre_cst_expr_method_post() { return 2; }
  }

  ```


  ConstexprVariableCase     

  When defined, the check will ensure constexpr variable names conform to the selected casing.

  ConstexprVariablePrefix     

  When defined, the check will ensure constexpr variable names will add the prefixed with the given value (regardless of casing).

  ConstexprVariableIgnoredRegexp     

  Identifier naming checks won’t be enforced for constexpr variable names matching this regular expression.

  ConstexprVariableSuffix     

  When defined, the check will ensure constexpr variable names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * ConstexprVariableCase of lower_case
    * ConstexprVariablePrefix of pre_
    * ConstexprVariableSuffix of _post



  Identifies and/or transforms constexpr variable names as follows:

  Before:

  ``` cpp
  constexpr int ConstExpr_variable = MyConstant;

  ```


  After:

  ``` cpp
  constexpr int pre_constexpr_variable_post = MyConstant;

  ```


  EnumCase     

  When defined, the check will ensure enumeration names conform to the selected casing.

  EnumPrefix     

  When defined, the check will ensure enumeration names will add the prefixed with the given value (regardless of casing).

  EnumIgnoredRegexp     

  Identifier naming checks won’t be enforced for enumeration names matching this regular expression.

  EnumSuffix     

  When defined, the check will ensure enumeration names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * EnumCase of lower_case
    * EnumPrefix of pre_
    * EnumSuffix of _post



  Identifies and/or transforms enumeration names as follows:

  Before:

  ``` cpp
  enum FOO { One, Two, Three };

  ```


  After:

  ``` cpp
  enum pre_foo_post { One, Two, Three };

  ```


  EnumConstantCase     

  When defined, the check will ensure enumeration constant names conform to the selected casing.

  EnumConstantPrefix     

  When defined, the check will ensure enumeration constant names will add the prefixed with the given value (regardless of casing).

  EnumConstantIgnoredRegexp     

  Identifier naming checks won’t be enforced for enumeration constant names matching this regular expression.

  EnumConstantSuffix     

  When defined, the check will ensure enumeration constant names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * EnumConstantCase of lower_case
    * EnumConstantPrefix of pre_
    * EnumConstantSuffix of _post



  Identifies and/or transforms enumeration constant names as follows:

  Before:

  ``` cpp
  enum FOO { One, Two, Three };

  ```


  After:

  ``` cpp
  enum FOO { pre_One_post, pre_Two_post, pre_Three_post };

  ```


  FunctionCase     

  When defined, the check will ensure function names conform to the selected casing.

  FunctionPrefix     

  When defined, the check will ensure function names will add the prefixed with the given value (regardless of casing).

  FunctionIgnoredRegexp     

  Identifier naming checks won’t be enforced for function names matching this regular expression.

  FunctionSuffix     

  When defined, the check will ensure function names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * FunctionCase of lower_case
    * FunctionPrefix of pre_
    * FunctionSuffix of _post



  Identifies and/or transforms function names as follows:

  Before:

  ``` cpp
  char MY_Function_string();

  ```


  After:

  ``` cpp
  char pre_my_function_string_post();

  ```


  GetConfigPerFile     

  When true the check will look for the configuration for where an identifier is declared. Useful for when included header files use a different style. Default value is true.

  GlobalConstantCase     

  When defined, the check will ensure global constant names conform to the selected casing.

  GlobalConstantPrefix     

  When defined, the check will ensure global constant names will add the prefixed with the given value (regardless of casing).

  GlobalConstantIgnoredRegexp     

  Identifier naming checks won’t be enforced for global constant names matching this regular expression.

  GlobalConstantSuffix     

  When defined, the check will ensure global constant names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * GlobalConstantCase of lower_case
    * GlobalConstantPrefix of pre_
    * GlobalConstantSuffix of _post



  Identifies and/or transforms global constant names as follows:

  Before:

  ``` cpp
  unsigned const MyConstGlobal_array[] = {1, 2, 3};

  ```


  After:

  ``` cpp
  unsigned const pre_myconstglobal_array_post[] = {1, 2, 3};

  ```


  GlobalConstantPointerCase     

  When defined, the check will ensure global constant pointer names conform to the selected casing.

  GlobalConstantPointerPrefix     

  When defined, the check will ensure global constant pointer names will add the prefixed with the given value (regardless of casing).

  GlobalConstantPointerIgnoredRegexp     

  Identifier naming checks won’t be enforced for global constant pointer names matching this regular expression.

  GlobalConstantPointerSuffix     

  When defined, the check will ensure global constant pointer names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * GlobalConstantPointerCase of lower_case
    * GlobalConstantPointerPrefix of pre_
    * GlobalConstantPointerSuffix of _post



  Identifies and/or transforms global constant pointer names as follows:

  Before:

  ``` cpp
  int *const MyConstantGlobalPointer = nullptr;

  ```


  After:

  ``` cpp
  int *const pre_myconstantglobalpointer_post = nullptr;

  ```


  GlobalFunctionCase     

  When defined, the check will ensure global function names conform to the selected casing.

  GlobalFunctionPrefix     

  When defined, the check will ensure global function names will add the prefixed with the given value (regardless of casing).

  GlobalFunctionIgnoredRegexp     

  Identifier naming checks won’t be enforced for global function names matching this regular expression.

  GlobalFunctionSuffix     

  When defined, the check will ensure global function names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * GlobalFunctionCase of lower_case
    * GlobalFunctionPrefix of pre_
    * GlobalFunctionSuffix of _post



  Identifies and/or transforms global function names as follows:

  Before:

  ``` cpp
  void GLOBAL_FUNCTION(int PARAMETER_1, int const CONST_parameter);

  ```


  After:

  ``` cpp
  void pre_global_function_post(int PARAMETER_1, int const CONST_parameter);

  ```


  GlobalPointerCase     

  When defined, the check will ensure global pointer names conform to the selected casing.

  GlobalPointerPrefix     

  When defined, the check will ensure global pointer names will add the prefixed with the given value (regardless of casing).

  GlobalPointerIgnoredRegexp     

  Identifier naming checks won’t be enforced for global pointer names matching this regular expression.

  GlobalPointerSuffix     

  When defined, the check will ensure global pointer names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * GlobalPointerCase of lower_case
    * GlobalPointerPrefix of pre_
    * GlobalPointerSuffix of _post



  Identifies and/or transforms global pointer names as follows:

  Before:

  ``` cpp
  int *GLOBAL3;

  ```


  After:

  ``` cpp
  int *pre_global3_post;

  ```


  GlobalVariableCase     

  When defined, the check will ensure global variable names conform to the selected casing.

  GlobalVariablePrefix     

  When defined, the check will ensure global variable names will add the prefixed with the given value (regardless of casing).

  GlobalVariableIgnoredRegexp     

  Identifier naming checks won’t be enforced for global variable names matching this regular expression.

  GlobalVariableSuffix     

  When defined, the check will ensure global variable names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * GlobalVariableCase of lower_case
    * GlobalVariablePrefix of pre_
    * GlobalVariableSuffix of _post



  Identifies and/or transforms global variable names as follows:

  Before:

  ``` cpp
  int GLOBAL3;

  ```


  After:

  ``` cpp
  int pre_global3_post;

  ```


  IgnoreMainLikeFunctions     

  When set to true functions that have a similar signature to main or wmain won’t enforce checks on the names of their parameters. Default value is false.

  InlineNamespaceCase     

  When defined, the check will ensure inline namespaces names conform to the selected casing.

  InlineNamespacePrefix     

  When defined, the check will ensure inline namespaces names will add the prefixed with the given value (regardless of casing).

  InlineNamespaceIgnoredRegexp     

  Identifier naming checks won’t be enforced for inline namespaces names matching this regular expression.

  InlineNamespaceSuffix     

  When defined, the check will ensure inline namespaces names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * InlineNamespaceCase of lower_case
    * InlineNamespacePrefix of pre_
    * InlineNamespaceSuffix of _post



  Identifies and/or transforms inline namespaces names as follows:

  Before:

  ``` cpp
  namespace FOO_NS {
  inline namespace InlineNamespace {
  ...
  }
  } // namespace FOO_NS

  ```


  After:

  ``` cpp
  namespace FOO_NS {
  inline namespace pre_inlinenamespace_post {
  ...
  }
  } // namespace FOO_NS

  ```


  LocalConstantCase     

  When defined, the check will ensure local constant names conform to the selected casing.

  LocalConstantPrefix     

  When defined, the check will ensure local constant names will add the prefixed with the given value (regardless of casing).

  LocalConstantIgnoredRegexp     

  Identifier naming checks won’t be enforced for local constant names matching this regular expression.

  LocalConstantSuffix     

  When defined, the check will ensure local constant names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * LocalConstantCase of lower_case
    * LocalConstantPrefix of pre_
    * LocalConstantSuffix of _post



  Identifies and/or transforms local constant names as follows:

  Before:

  ``` cpp
  void foo() { int const local_Constant = 3; }

  ```


  After:

  ``` cpp
  void foo() { int const pre_local_constant_post = 3; }

  ```


  LocalConstantPointerCase     

  When defined, the check will ensure local constant pointer names conform to the selected casing.

  LocalConstantPointerPrefix     

  When defined, the check will ensure local constant pointer names will add the prefixed with the given value (regardless of casing).

  LocalConstantPointerIgnoredRegexp     

  Identifier naming checks won’t be enforced for local constant pointer names matching this regular expression.

  LocalConstantPointerSuffix     

  When defined, the check will ensure local constant pointer names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * LocalConstantPointerCase of lower_case
    * LocalConstantPointerPrefix of pre_
    * LocalConstantPointerSuffix of _post



  Identifies and/or transforms local constant pointer names as follows:

  Before:

  ``` cpp
  void foo() { int const *local_Constant = 3; }

  ```


  After:

  ``` cpp
  void foo() { int const *pre_local_constant_post = 3; }

  ```


  LocalPointerCase     

  When defined, the check will ensure local pointer names conform to the selected casing.

  LocalPointerPrefix     

  When defined, the check will ensure local pointer names will add the prefixed with the given value (regardless of casing).

  LocalPointerIgnoredRegexp     

  Identifier naming checks won’t be enforced for local pointer names matching this regular expression.

  LocalPointerSuffix     

  When defined, the check will ensure local pointer names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * LocalPointerCase of lower_case
    * LocalPointerPrefix of pre_
    * LocalPointerSuffix of _post



  Identifies and/or transforms local pointer names as follows:

  Before:

  ``` cpp
  void foo() { int *local_Constant; }

  ```


  After:

  ``` cpp
  void foo() { int *pre_local_constant_post; }

  ```


  LocalVariableCase     

  When defined, the check will ensure local variable names conform to the selected casing.

  LocalVariablePrefix     

  When defined, the check will ensure local variable names will add the prefixed with the given value (regardless of casing).

  LocalVariableIgnoredRegexp     

  Identifier naming checks won’t be enforced for local variable names matching this regular expression.

  For example using values of:

    * LocalVariableCase of CamelCase
    * LocalVariableIgnoredRegexp of \w{1,2}



  Will exclude variables with a length less than or equal to 2 from the camel case check applied to other variables.

  LocalVariableSuffix     

  When defined, the check will ensure local variable names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * LocalVariableCase of lower_case
    * LocalVariablePrefix of pre_
    * LocalVariableSuffix of _post



  Identifies and/or transforms local variable names as follows:

  Before:

  ``` cpp
  void foo() { int local_Constant; }

  ```


  After:

  ``` cpp
  void foo() { int pre_local_constant_post; }

  ```


  MacroDefinitionCase     

  When defined, the check will ensure macro definitions conform to the selected casing.

  MacroDefinitionPrefix     

  When defined, the check will ensure macro definitions will add the prefixed with the given value (regardless of casing).

  MacroDefinitionIgnoredRegexp     

  Identifier naming checks won’t be enforced for macro definitions matching this regular expression.

  MacroDefinitionSuffix     

  When defined, the check will ensure macro definitions will add the suffix with the given value (regardless of casing).

  For example using values of:

    * MacroDefinitionCase of lower_case
    * MacroDefinitionPrefix of pre_
    * MacroDefinitionSuffix of _post



  Identifies and/or transforms macro definitions as follows:

  Before:

  ``` cpp
  #define MY_MacroDefinition

  ```


  After:

  ``` cpp
  #define pre_my_macro_definition_post

  ```


  Note: This will not warn on builtin macros or macros defined on the command line using the -D flag.

  MemberCase     

  When defined, the check will ensure member names conform to the selected casing.

  MemberPrefix     

  When defined, the check will ensure member names will add the prefixed with the given value (regardless of casing).

  MemberIgnoredRegexp     

  Identifier naming checks won’t be enforced for member names matching this regular expression.

  MemberSuffix     

  When defined, the check will ensure member names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * MemberCase of lower_case
    * MemberPrefix of pre_
    * MemberSuffix of _post



  Identifies and/or transforms member names as follows:

  Before:

  ``` cpp
  class Foo {
    char MY_ConstMember_string[4];
  }

  ```


  After:

  ``` cpp
  class Foo {
    char pre_my_constmember_string_post[4];
  }

  ```


  MethodCase     

  When defined, the check will ensure method names conform to the selected casing.

  MethodPrefix     

  When defined, the check will ensure method names will add the prefixed with the given value (regardless of casing).

  MethodIgnoredRegexp     

  Identifier naming checks won’t be enforced for method names matching this regular expression.

  MethodSuffix     

  When defined, the check will ensure method names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * MethodCase of lower_case
    * MethodPrefix of pre_
    * MethodSuffix of _post



  Identifies and/or transforms method names as follows:

  Before:

  ``` cpp
  class Foo {
    char MY_Method_string();
  }

  ```


  After:

  ``` cpp
  class Foo {
    char pre_my_method_string_post();
  }

  ```


  NamespaceCase     

  When defined, the check will ensure namespace names conform to the selected casing.

  NamespacePrefix     

  When defined, the check will ensure namespace names will add the prefixed with the given value (regardless of casing).

  NamespaceIgnoredRegexp     

  Identifier naming checks won’t be enforced for namespace names matching this regular expression.

  NamespaceSuffix     

  When defined, the check will ensure namespace names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * NamespaceCase of lower_case
    * NamespacePrefix of pre_
    * NamespaceSuffix of _post



  Identifies and/or transforms namespace names as follows:

  Before:

  ``` cpp
  namespace FOO_NS {
  ...
  }

  ```


  After:

  ``` cpp
  namespace pre_foo_ns_post {
  ...
  }

  ```


  ParameterCase     

  When defined, the check will ensure parameter names conform to the selected casing.

  ParameterPrefix     

  When defined, the check will ensure parameter names will add the prefixed with the given value (regardless of casing).

  ParameterIgnoredRegexp     

  Identifier naming checks won’t be enforced for parameter names matching this regular expression.

  ParameterSuffix     

  When defined, the check will ensure parameter names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * ParameterCase of lower_case
    * ParameterPrefix of pre_
    * ParameterSuffix of _post



  Identifies and/or transforms parameter names as follows:

  Before:

  ``` cpp
  void GLOBAL_FUNCTION(int PARAMETER_1, int const CONST_parameter);

  ```


  After:

  ``` cpp
  void GLOBAL_FUNCTION(int pre_parameter_post, int const CONST_parameter);

  ```


  ParameterPackCase     

  When defined, the check will ensure parameter pack names conform to the selected casing.

  ParameterPackPrefix     

  When defined, the check will ensure parameter pack names will add the prefixed with the given value (regardless of casing).

  ParameterPackIgnoredRegexp     

  Identifier naming checks won’t be enforced for parameter pack names matching this regular expression.

  ParameterPackSuffix     

  When defined, the check will ensure parameter pack names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * ParameterPackCase of lower_case
    * ParameterPackPrefix of pre_
    * ParameterPackSuffix of _post



  Identifies and/or transforms parameter pack names as follows:

  Before:

  ``` cpp
  template <typename... TYPE_parameters> {
    void FUNCTION(int... TYPE_parameters);
  }

  ```


  After:

  ``` cpp
  template <typename... TYPE_parameters> {
    void FUNCTION(int... pre_type_parameters_post);
  }

  ```


  PointerParameterCase     

  When defined, the check will ensure pointer parameter names conform to the selected casing.

  PointerParameterPrefix     

  When defined, the check will ensure pointer parameter names will add the prefixed with the given value (regardless of casing).

  PointerParameterIgnoredRegexp     

  Identifier naming checks won’t be enforced for pointer parameter names matching this regular expression.

  PointerParameterSuffix     

  When defined, the check will ensure pointer parameter names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * PointerParameterCase of lower_case
    * PointerParameterPrefix of pre_
    * PointerParameterSuffix of _post



  Identifies and/or transforms pointer parameter names as follows:

  Before:

  ``` cpp
  void FUNCTION(int *PARAMETER);

  ```


  After:

  ``` cpp
  void FUNCTION(int *pre_parameter_post);

  ```


  PrivateMemberCase     

  When defined, the check will ensure private member names conform to the selected casing.

  PrivateMemberPrefix     

  When defined, the check will ensure private member names will add the prefixed with the given value (regardless of casing).

  PrivateMemberIgnoredRegexp     

  Identifier naming checks won’t be enforced for private member names matching this regular expression.

  PrivateMemberSuffix     

  When defined, the check will ensure private member names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * PrivateMemberCase of lower_case
    * PrivateMemberPrefix of pre_
    * PrivateMemberSuffix of _post



  Identifies and/or transforms private member names as follows:

  Before:

  ``` cpp
  class Foo {
  private:
    int Member_Variable;
  }

  ```


  After:

  ``` cpp
  class Foo {
  private:
    int pre_member_variable_post;
  }

  ```


  PrivateMethodCase     

  When defined, the check will ensure private method names conform to the selected casing.

  PrivateMethodPrefix     

  When defined, the check will ensure private method names will add the prefixed with the given value (regardless of casing).

  PrivateMethodIgnoredRegexp     

  Identifier naming checks won’t be enforced for private method names matching this regular expression.

  PrivateMethodSuffix     

  When defined, the check will ensure private method names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * PrivateMethodCase of lower_case
    * PrivateMethodPrefix of pre_
    * PrivateMethodSuffix of _post



  Identifies and/or transforms private method names as follows:

  Before:

  ``` cpp
  class Foo {
  private:
    int Member_Method();
  }

  ```


  After:

  ``` cpp
  class Foo {
  private:
    int pre_member_method_post();
  }

  ```


  ProtectedMemberCase     

  When defined, the check will ensure protected member names conform to the selected casing.

  ProtectedMemberPrefix     

  When defined, the check will ensure protected member names will add the prefixed with the given value (regardless of casing).

  ProtectedMemberIgnoredRegexp     

  Identifier naming checks won’t be enforced for protected member names matching this regular expression.

  ProtectedMemberSuffix     

  When defined, the check will ensure protected member names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * ProtectedMemberCase of lower_case
    * ProtectedMemberPrefix of pre_
    * ProtectedMemberSuffix of _post



  Identifies and/or transforms protected member names as follows:

  Before:

  ``` cpp
  class Foo {
  protected:
    int Member_Variable;
  }

  ```


  After:

  ``` cpp
  class Foo {
  protected:
    int pre_member_variable_post;
  }

  ```


  ProtectedMethodCase     

  When defined, the check will ensure protected method names conform to the selected casing.

  ProtectedMethodPrefix     

  When defined, the check will ensure protected method names will add the prefixed with the given value (regardless of casing).

  ProtectedMethodIgnoredRegexp     

  Identifier naming checks won’t be enforced for protected method names matching this regular expression.

  ProtectedMethodSuffix     

  When defined, the check will ensure protected method names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * ProtectedMethodCase of lower_case
    * ProtectedMethodPrefix of pre_
    * ProtectedMethodSuffix of _post



  Identifies and/or transforms protect method names as follows:

  Before:

  ``` cpp
  class Foo {
  protected:
    int Member_Method();
  }

  ```


  After:

  ``` cpp
  class Foo {
  protected:
    int pre_member_method_post();
  }

  ```


  PublicMemberCase     

  When defined, the check will ensure public member names conform to the selected casing.

  PublicMemberPrefix     

  When defined, the check will ensure public member names will add the prefixed with the given value (regardless of casing).

  PublicMemberIgnoredRegexp     

  Identifier naming checks won’t be enforced for public member names matching this regular expression.

  PublicMemberSuffix     

  When defined, the check will ensure public member names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * PublicMemberCase of lower_case
    * PublicMemberPrefix of pre_
    * PublicMemberSuffix of _post



  Identifies and/or transforms public member names as follows:

  Before:

  ``` cpp
  class Foo {
  public:
    int Member_Variable;
  }

  ```


  After:

  ``` cpp
  class Foo {
  public:
    int pre_member_variable_post;
  }

  ```


  PublicMethodCase     

  When defined, the check will ensure public method names conform to the selected casing.

  PublicMethodPrefix     

  When defined, the check will ensure public method names will add the prefixed with the given value (regardless of casing).

  PublicMethodIgnoredRegexp     

  Identifier naming checks won’t be enforced for public method names matching this regular expression.

  PublicMethodSuffix     

  When defined, the check will ensure public method names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * PublicMethodCase of lower_case
    * PublicMethodPrefix of pre_
    * PublicMethodSuffix of _post



  Identifies and/or transforms public method names as follows:

  Before:

  ``` cpp
  class Foo {
  public:
    int Member_Method();
  }

  ```


  After:

  ``` cpp
  class Foo {
  public:
    int pre_member_method_post();
  }

  ```


  ScopedEnumConstantCase     

  When defined, the check will ensure scoped enum constant names conform to the selected casing.

  ScopedEnumConstantPrefix     

  When defined, the check will ensure scoped enum constant names will add the prefixed with the given value (regardless of casing).

  ScopedEnumConstantIgnoredRegexp     

  Identifier naming checks won’t be enforced for scoped enum constant names matching this regular expression.

  ScopedEnumConstantSuffix     

  When defined, the check will ensure scoped enum constant names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * ScopedEnumConstantCase of lower_case
    * ScopedEnumConstantPrefix of pre_
    * ScopedEnumConstantSuffix of _post



  Identifies and/or transforms enumeration constant names as follows:

  Before:

  ``` cpp
  enum class FOO { One, Two, Three };

  ```


  After:

  ``` cpp
  enum class FOO { pre_One_post, pre_Two_post, pre_Three_post };

  ```


  StaticConstantCase     

  When defined, the check will ensure static constant names conform to the selected casing.

  StaticConstantPrefix     

  When defined, the check will ensure static constant names will add the prefixed with the given value (regardless of casing).

  StaticConstantIgnoredRegexp     

  Identifier naming checks won’t be enforced for static constant names matching this regular expression.

  StaticConstantSuffix     

  When defined, the check will ensure static constant names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * StaticConstantCase of lower_case
    * StaticConstantPrefix of pre_
    * StaticConstantSuffix of _post



  Identifies and/or transforms static constant names as follows:

  Before:

  ``` cpp
  static unsigned const MyConstStatic_array[] = {1, 2, 3};

  ```


  After:

  ``` cpp
  static unsigned const pre_myconststatic_array_post[] = {1, 2, 3};

  ```


  StaticVariableCase     

  When defined, the check will ensure static variable names conform to the selected casing.

  StaticVariablePrefix     

  When defined, the check will ensure static variable names will add the prefixed with the given value (regardless of casing).

  StaticVariableIgnoredRegexp     

  Identifier naming checks won’t be enforced for static variable names matching this regular expression.

  StaticVariableSuffix     

  When defined, the check will ensure static variable names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * StaticVariableCase of lower_case
    * StaticVariablePrefix of pre_
    * StaticVariableSuffix of _post



  Identifies and/or transforms static variable names as follows:

  Before:

  ``` cpp
  static unsigned MyStatic_array[] = {1, 2, 3};

  ```


  After:

  ``` cpp
  static unsigned pre_mystatic_array_post[] = {1, 2, 3};

  ```


  StructCase     

  When defined, the check will ensure struct names conform to the selected casing.

  StructPrefix     

  When defined, the check will ensure struct names will add the prefixed with the given value (regardless of casing).

  StructIgnoredRegexp     

  Identifier naming checks won’t be enforced for struct names matching this regular expression.

  StructSuffix     

  When defined, the check will ensure struct names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * StructCase of lower_case
    * StructPrefix of pre_
    * StructSuffix of _post



  Identifies and/or transforms struct names as follows:

  Before:

  ``` cpp
  struct FOO {
    FOO();
    ~FOO();
  };

  ```


  After:

  ``` cpp
  struct pre_foo_post {
    pre_foo_post();
    ~pre_foo_post();
  };

  ```


  TemplateParameterCase     

  When defined, the check will ensure template parameter names conform to the selected casing.

  TemplateParameterPrefix     

  When defined, the check will ensure template parameter names will add the prefixed with the given value (regardless of casing).

  TemplateParameterIgnoredRegexp     

  Identifier naming checks won’t be enforced for template parameter names matching this regular expression.

  TemplateParameterSuffix     

  When defined, the check will ensure template parameter names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * TemplateParameterCase of lower_case
    * TemplateParameterPrefix of pre_
    * TemplateParameterSuffix of _post



  Identifies and/or transforms template parameter names as follows:

  Before:

  ``` cpp
  template <typename T> class Foo {};

  ```


  After:

  ``` cpp
  template <typename pre_t_post> class Foo {};

  ```


  TemplateTemplateParameterCase     

  When defined, the check will ensure template template parameter names conform to the selected casing.

  TemplateTemplateParameterPrefix     

  When defined, the check will ensure template template parameter names will add the prefixed with the given value (regardless of casing).

  TemplateTemplateParameterIgnoredRegexp     

  Identifier naming checks won’t be enforced for template template parameter names matching this regular expression.

  TemplateTemplateParameterSuffix     

  When defined, the check will ensure template template parameter names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * TemplateTemplateParameterCase of lower_case
    * TemplateTemplateParameterPrefix of pre_
    * TemplateTemplateParameterSuffix of _post



  Identifies and/or transforms template template parameter names as follows:

  Before:

  ``` cpp
  template <template <typename> class TPL_parameter, int COUNT_params,
            typename... TYPE_parameters>

  ```


  After:

  ``` cpp
  template <template <typename> class pre_tpl_parameter_post, int COUNT_params,
            typename... TYPE_parameters>

  ```


  TypeAliasCase     

  When defined, the check will ensure type alias names conform to the selected casing.

  TypeAliasPrefix     

  When defined, the check will ensure type alias names will add the prefixed with the given value (regardless of casing).

  TypeAliasIgnoredRegexp     

  Identifier naming checks won’t be enforced for type alias names matching this regular expression.

  TypeAliasSuffix     

  When defined, the check will ensure type alias names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * TypeAliasCase of lower_case
    * TypeAliasPrefix of pre_
    * TypeAliasSuffix of _post



  Identifies and/or transforms type alias names as follows:

  Before:

  ``` cpp
  using MY_STRUCT_TYPE = my_structure;

  ```


  After:

  ``` cpp
  using pre_my_struct_type_post = my_structure;

  ```


  TypedefCase     

  When defined, the check will ensure typedef names conform to the selected casing.

  TypedefPrefix     

  When defined, the check will ensure typedef names will add the prefixed with the given value (regardless of casing).

  TypedefIgnoredRegexp     

  Identifier naming checks won’t be enforced for typedef names matching this regular expression.

  TypedefSuffix     

  When defined, the check will ensure typedef names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * TypedefCase of lower_case
    * TypedefPrefix of pre_
    * TypedefSuffix of _post



  Identifies and/or transforms typedef names as follows:

  Before:

  ``` cpp
  typedef int MYINT;

  ```


  After:

  ``` cpp
  typedef int pre_myint_post;

  ```


  TypeTemplateParameterCase     

  When defined, the check will ensure type template parameter names conform to the selected casing.

  TypeTemplateParameterPrefix     

  When defined, the check will ensure type template parameter names will add the prefixed with the given value (regardless of casing).

  TypeTemplateParameterIgnoredRegexp     

  Identifier naming checks won’t be enforced for type template names matching this regular expression.

  TypeTemplateParameterSuffix     

  When defined, the check will ensure type template parameter names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * TypeTemplateParameterCase of lower_case
    * TypeTemplateParameterPrefix of pre_
    * TypeTemplateParameterSuffix of _post



  Identifies and/or transforms type template parameter names as follows:

  Before:

  ``` cpp
  template <template <typename> class TPL_parameter, int COUNT_params,
            typename... TYPE_parameters>

  ```


  After:

  ``` cpp
  template <template <typename> class TPL_parameter, int COUNT_params,
            typename... pre_type_parameters_post>

  ```


  UnionCase     

  When defined, the check will ensure union names conform to the selected casing.

  UnionPrefix     

  When defined, the check will ensure union names will add the prefixed with the given value (regardless of casing).

  UnionIgnoredRegexp     

  Identifier naming checks won’t be enforced for union names matching this regular expression.

  UnionSuffix     

  When defined, the check will ensure union names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * UnionCase of lower_case
    * UnionPrefix of pre_
    * UnionSuffix of _post



  Identifies and/or transforms union names as follows:

  Before:

  ``` cpp
  union FOO {
    int a;
    char b;
  };

  ```


  After:

  ``` cpp
  union pre_foo_post {
    int a;
    char b;
  };

  ```


  ValueTemplateParameterCase     

  When defined, the check will ensure value template parameter names conform to the selected casing.

  ValueTemplateParameterPrefix     

  When defined, the check will ensure value template parameter names will add the prefixed with the given value (regardless of casing).

  ValueTemplateParameterIgnoredRegexp     

  Identifier naming checks won’t be enforced for value template parameter names matching this regular expression.

  ValueTemplateParameterSuffix     

  When defined, the check will ensure value template parameter names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * ValueTemplateParameterCase of lower_case
    * ValueTemplateParameterPrefix of pre_
    * ValueTemplateParameterSuffix of _post



  Identifies and/or transforms value template parameter names as follows:

  Before:

  ``` cpp
  template <template <typename> class TPL_parameter, int COUNT_params,
            typename... TYPE_parameters>

  ```


  After:

  ``` cpp
  template <template <typename> class TPL_parameter, int pre_count_params_post,
            typename... TYPE_parameters>

  ```


  VariableCase     

  When defined, the check will ensure variable names conform to the selected casing.

  VariablePrefix     

  When defined, the check will ensure variable names will add the prefixed with the given value (regardless of casing).

  VariableIgnoredRegexp     

  Identifier naming checks won’t be enforced for variable names matching this regular expression.

  VariableSuffix     

  When defined, the check will ensure variable names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * VariableCase of lower_case
    * VariablePrefix of pre_
    * VariableSuffix of _post



  Identifies and/or transforms variable names as follows:

  Before:

  ``` cpp
  unsigned MyVariable;

  ```


  After:

  ``` cpp
  unsigned pre_myvariable_post;

  ```


  VirtualMethodCase     

  When defined, the check will ensure virtual method names conform to the selected casing.

  VirtualMethodPrefix     

  When defined, the check will ensure virtual method names will add the prefixed with the given value (regardless of casing).

  VirtualMethodIgnoredRegexp     

  Identifier naming checks won’t be enforced for virtual method names matching this regular expression.

  VirtualMethodSuffix     

  When defined, the check will ensure virtual method names will add the suffix with the given value (regardless of casing).

  For example using values of:

    * VirtualMethodCase of lower_case
    * VirtualMethodPrefix of pre_
    * VirtualMethodSuffix of _post



  Identifies and/or transforms virtual method names as follows:

  Before:

  ``` cpp
  class Foo {
  public:
    virtual int MemberFunction();
  }

  ```


  After:

  ``` cpp
  class Foo {
  public:
    virtual int pre_member_function_post();
  }

  ```


  (Clang-Tidy original name: readability-identifier-naming)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_MAI
### Default
#### OriginalId=readability-misplaced-array-index
#### Enabled=true
#### Warning=true
#### DisplayName=Misplaced Array Index
#### HelpText
  This check warns for unusual array index syntax.

  The following code has unusual array index syntax:

  ``` cpp
  void f(int *X, int Y) {
    Y[X] = 0;
  }

  ```


  becomes

  ``` cpp
  void f(int *X, int Y) {
    X[Y] = 0;
  }

  ```


  The check warns about such unusual syntax for readability reasons:     

    * There are programmers that are not familiar with this unusual syntax.
    * It is possible that variables are mixed up.



  (Clang-Tidy original name: readability-misplaced-array-index)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_MI
### Default
#### OriginalId=readability-misleading-indentation
#### Enabled=true
#### Warning=true
#### DisplayName=Misleading Indentation
#### HelpText
  Correct indentation helps to understand code. Mismatch of the syntactical structure and the indentation of the code may hide serious problems. Missing braces can also make it significantly harder to read the code, therefore it is important to use braces.

  The way to avoid dangling else is to always check that an else belongs to the if that begins in the same column.

  You can omit braces when your inner part of e.g. an if statement has only one statement in it. Although in that case you should begin the next statement in the same column with the if.

  Examples:

  ``` cpp
  // Dangling else:
  if (cond1)
    if (cond2)
      foo1();
  else
    foo2();  // Wrong indentation: else belongs to if(cond2) statement.

  // Missing braces:
  if (cond1)
    foo1();
    foo2();  // Not guarded by if(cond1).

  ```


  ##### Limitations

  Note that this check only works as expected when the tabs or spaces are used consistently and not mixed.

  (Clang-Tidy original name: readability-misleading-indentation)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_MMFC
### Default
#### OriginalId=readability-make-member-function-const
#### Enabled=true
#### Warning=true
#### DisplayName=Make Member Function Const
#### HelpText
  Finds non-static member functions that can be made const because the functions don’t use this in a non-const way.

  This check tries to annotate methods according to [logical constness](https://isocpp.org/wiki/faq/const-correctness\#logical-vs-physical-state) (not physical constness). Therefore, it will suggest to add a const qualifier to a non-const method only if this method does something that is already possible though the public interface on a const pointer to the object:

    * reading a public member variable
    * calling a public const-qualified member function
    * returning const-qualified this
    * passing const-qualified this as a parameter.



  This check will also suggest to add a const qualifier to a non-const method if this method uses private data and functions in a limited number of ways where logical constness and physical constness coincide:

    * reading a member variable of builtin type



  Specifically, this check will not suggest to add a const to a non-const method if the method reads a private member variable of pointer type because that allows to modify the pointee which might not preserve logical constness. For the same reason, it does not allow to call private member functions or member functions on private member variables.

  In addition, this check ignores functions that

    * are declared virtual
    * contain a const_cast
    * are templated or part of a class template
    * have an empty body
    * do not (implicitly) use this at all (see [readability-convert-member-functions-to-static](readability-convert-member-functions-to-static.html)).



  The following real-world examples will be preserved by the check:

  ``` cpp
  class E1 {
    Pimpl &getPimpl() const;
  public:
    int &get() {
      // Calling a private member function disables this check.
      return getPimpl()->i;
    }
    ...
  };

  class E2 {
  public:
    const int *get() const;
    // const_cast disables this check.
    S *get() {
      return const_cast<int*>(const_cast<const C*>(this)->get());
    }
    ...
  };

  ```


  After applying modifications as suggested by the check, running the check again might find more opportunities to mark member functions const.

  (Clang-Tidy original name: readability-make-member-function-const)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_MN
### Default
#### OriginalId=readability-magic-numbers
#### Enabled=true
#### Warning=true
#### DisplayName=Magic Numbers
#### HelpText
  Detects magic numbers, integer or floating point literals that are embedded in code and not introduced via constants or symbols.

  Many coding guidelines advise replacing the magic values with symbolic constants to improve readability. Here are a few references:

    * [Rule ES.45: Avoid “magic constants”; use symbolic constants in C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines\#Res-magic)
    * [Rule 5.1.1 Use symbolic names instead of literal values in code in High Integrity C++](http://www.codingstandard.com/rule/5-1-1-use-symbolic-names-instead-of-literal-values-in-code/)
    * Item 17 in “C++ Coding Standards: 101 Rules, Guidelines and Best Practices” by Herb Sutter and Andrei Alexandrescu
    * Chapter 17 in “Clean Code - A handbook of agile software craftsmanship.” by Robert C. Martin
    * Rule 20701 in “TRAIN REAL TIME DATA PROTOCOL Coding Rules” by Armin-Hagen Weiss, Bombardier
    * <http://wiki.c2.com/?MagicNumber>



  Examples of magic values:

  ``` cpp
  double circleArea = 3.1415926535 * radius * radius;

  double totalCharge = 1.08 * itemPrice;

  int getAnswer() {
     return -3; // FILENOTFOUND
  }

  for (int mm = 1; mm <= 12; ++mm) {
     std::cout << month[mm] << '\n';
  }

  ```


  Example with magic values refactored:

  ``` cpp
  double circleArea = M_PI * radius * radius;

  const double TAX_RATE = 0.08;  // or make it variable and read from a file

  double totalCharge = (1.0 + TAX_RATE) * itemPrice;

  int getAnswer() {
     return E_FILE_NOT_FOUND;
  }

  for (int mm = 1; mm <= MONTHS_IN_A_YEAR; ++mm) {
     std::cout << month[mm] << '\n';
  }

  ```


  For integral literals by default only 0 and 1 (and -1) integer values are accepted without a warning. This can be overridden with the [IgnoredIntegerValues](\#cmdoption-arg-ignoredintegervalues) option. Negative values are accepted if their absolute value is present in the [IgnoredIntegerValues](\#cmdoption-arg-ignoredintegervalues) list.

  As a special case for integral values, all powers of two can be accepted without warning by enabling the [IgnorePowersOf2IntegerValues](\#cmdoption-arg-ignorepowersof2integervalues) option.

  For floating point literals by default the 0.0 floating point value is accepted without a warning. The set of ignored floating point literals can be configured using the [IgnoredFloatingPointValues](\#cmdoption-arg-ignoredfloatingpointvalues) option. For each value in that set, the given string value is converted to a floating-point value representation used by the target architecture. If a floating-point literal value compares equal to one of the converted values, then that literal is not diagnosed by this check. Because floating-point equality is used to determine whether to diagnose or not, the user needs to be aware of the details of floating-point representations for any values that cannot be precisely represented for their target architecture.

  For each value in the [IgnoredFloatingPointValues](\#cmdoption-arg-ignoredfloatingpointvalues) set, both the single-precision form and double-precision form are accepted (for example, if 3.14 is in the set, neither 3.14f nor 3.14 will produce a warning).

  Scientific notation is supported for both source code input and option. Alternatively, the check for the floating point numbers can be disabled for all floating point values by enabling the [IgnoreAllFloatingPointValues](\#cmdoption-arg-ignoreallfloatingpointvalues) option.

  Since values 0 and 0.0 are so common as the base counter of loops, or initialization values for sums, they are always accepted without warning, even if not present in the respective ignored values list.

  ##### Options

  IgnoredIntegerValues     

  Semicolon-separated list of magic positive integers that will be accepted without a warning. Default values are {1, 2, 3, 4}, and 0 is accepted unconditionally.

  IgnorePowersOf2IntegerValues     

  Boolean value indicating whether to accept all powers-of-two integer values without warning. Default value is false.

  IgnoredFloatingPointValues     

  Semicolon-separated list of magic positive floating point values that will be accepted without a warning. Default values are {1.0, 100.0} and 0.0 is accepted unconditionally.

  IgnoreAllFloatingPointValues     

  Boolean value indicating whether to accept all floating point values without warning. Default value is false.

  IgnoreBitFieldsWidths     

  Boolean value indicating whether to accept magic numbers as bit field widths without warning. This is useful for example for register definitions which are generated from hardware specifications. Default value is true.

  (Clang-Tidy original name: readability-magic-numbers)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_NCP
### Default
#### OriginalId=readability-non-const-parameter
#### Enabled=true
#### Warning=true
#### DisplayName=Non Const Parameter
#### HelpText
  The check finds function parameters of a pointer type that could be changed to point to a constant type instead.

  When const is used properly, many mistakes can be avoided. Advantages when using const properly:

    * prevent unintentional modification of data;
    * get additional warnings such as using uninitialized data;
    * make it easier for developers to see possible side effects.



  This check is not strict about constness, it only warns when the constness will make the function interface safer.

  ``` cpp
  // warning here; the declaration "const char *p" would make the function
  // interface safer.
  char f1(char *p) {
    return *p;
  }

  // no warning; the declaration could be more const "const int * const p" but
  // that does not make the function interface safer.
  int f2(const int *p) {
    return *p;
  }

  // no warning; making x const does not make the function interface safer
  int f3(int x) {
    return x;
  }

  // no warning; Technically, *p can be const ("const struct S *p"). But making
  // *p const could be misleading. People might think that it's safe to pass
  // const data to this function.
  struct S { int *a; int *b; };
  int f3(struct S *p) {
    *(p->a) = 0;
  }

  ```


  (Clang-Tidy original name: readability-non-const-parameter)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_NP
### Default
#### OriginalId=readability-named-parameter
#### Enabled=true
#### Warning=true
#### DisplayName=Named Parameter
#### HelpText
  Find functions with unnamed arguments.

  The check implements the following rule originating in the Google C++ Style Guide:

  <https://google.github.io/styleguide/cppguide.html\#Function_Declarations_and_Definitions>

  All parameters should be named, with identical names in the declaration and implementation.

  Corresponding cpplint.py check name: readability/function.

  (Clang-Tidy original name: readability-named-parameter)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_QA
### Default
#### OriginalId=readability-qualified-auto
#### Enabled=true
#### Warning=true
#### DisplayName=Qualified Auto
#### HelpText
  Adds pointer qualifications to auto-typed variables that are deduced to pointers.

  [LLVM Coding Standards](https://llvm.org/docs/CodingStandards.html\#beware-unnecessary-copies-with-auto) advises to make it obvious if a auto typed variable is a pointer. This check will transform auto to auto * when the type is deduced to be a pointer.

  ``` cpp
  for (auto Data : MutatablePtrContainer) {
    change(*Data);
  }
  for (auto Data : ConstantPtrContainer) {
    observe(*Data);
  }

  ```


  Would be transformed into:

  ``` cpp
  for (auto *Data : MutatablePtrContainer) {
    change(*Data);
  }
  for (const auto *Data : ConstantPtrContainer) {
    observe(*Data);
  }

  ```


  Note const volatile qualified types will retain their const and volatile qualifiers. Pointers to pointers will not be fully qualified.

  ``` cpp
  const auto Foo = cast<int *>(Baz1);
  const auto Bar = cast<const int *>(Baz2);
  volatile auto FooBar = cast<int *>(Baz3);
  auto BarFoo = cast<int **>(Baz4);

  ```


  Would be transformed into:

  ``` cpp
  auto *const Foo = cast<int *>(Baz1);
  const auto *const Bar = cast<const int *>(Baz2);
  auto *volatile FooBar = cast<int *>(Baz3);
  auto *BarFoo = cast<int **>(Baz4);

  ```


  ##### Options

  AddConstToQualified     

  When set to true the check will add const qualifiers variables defined as auto * or auto & when applicable. Default value is true.

  ``` cpp
  auto Foo1 = cast<const int *>(Bar1);
  auto *Foo2 = cast<const int *>(Bar2);
  auto &Foo3 = cast<const int &>(Bar3);

  ```


  If AddConstToQualified is set to false, it will be transformed into:

  ``` cpp
  const auto *Foo1 = cast<const int *>(Bar1);
  auto *Foo2 = cast<const int *>(Bar2);
  auto &Foo3 = cast<const int &>(Bar3);

  ```


  Otherwise it will be transformed into:

  ``` cpp
  const auto *Foo1 = cast<const int *>(Bar1);
  const auto *Foo2 = cast<const int *>(Bar2);
  const auto &Foo3 = cast<const int &>(Bar3);

  ```


  Note in the LLVM alias, the default value is false.

  (Clang-Tidy original name: readability-qualified-auto)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_RAS
### Default
#### OriginalId=readability-redundant-access-specifiers
#### Enabled=true
#### Warning=true
#### DisplayName=Redundant Access Specifiers
#### HelpText
  Finds classes, structs, and unions containing redundant member (field and method) access specifiers.

  ##### Example

  ``` cpp
  class Foo {
  public:
    int x;
    int y;
  public:
    int z;
  protected:
    int a;
  public:
    int c;
  }

  ```


  In the example above, the second public declaration can be removed without any changes of behavior.

  ##### Options

  CheckFirstDeclaration     

  If set to true, the check will also diagnose if the first access specifier declaration is redundant (e.g. private inside class, or public inside struct or union). Default is false.

  ###### Example

  ``` cpp
  struct Bar {
  public:
    int x;
  }

  ```


  If CheckFirstDeclaration option is enabled, a warning about redundant access specifier will be emitted, because public is the default member access for structs.

  (Clang-Tidy original name: readability-redundant-access-specifiers)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_RCF
### Default
#### OriginalId=readability-redundant-control-flow
#### Enabled=true
#### Warning=true
#### DisplayName=Redundant Control Flow
#### HelpText
  This check looks for procedures (functions returning no value) with return statements at the end of the function. Such return statements are redundant.

  Loop statements (for, while, do while) are checked for redundant continue statements at the end of the loop body.

  Examples:

  The following function f contains a redundant return statement:

  ``` cpp
  extern void g();
  void f() {
    g();
    return;
  }

  ```


  becomes

  ``` cpp
  extern void g();
  void f() {
    g();
  }

  ```


  The following function k contains a redundant continue statement:

  ``` cpp
  void k() {
    for (int i = 0; i < 10; ++i) {
      continue;
    }
  }

  ```


  becomes

  ``` cpp
  void k() {
    for (int i = 0; i < 10; ++i) {
    }
  }

  ```


  (Clang-Tidy original name: readability-redundant-control-flow)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_RD
### Default
#### OriginalId=readability-redundant-declaration
#### Enabled=true
#### Warning=true
#### DisplayName=Redundant Declaration
#### HelpText
  Finds redundant variable and function declarations.

  ``` cpp
  extern int X;
  extern int X;

  ```


  becomes

  ``` cpp
  extern int X;

  ```


  Such redundant declarations can be removed without changing program behaviour. They can for instance be unintentional left overs from previous refactorings when code has been moved around. Having redundant declarations could in worst case mean that there are typos in the code that cause bugs.

  Normally the code can be automatically fixed, **clang-tidy** can remove the second declaration. However there are 2 cases when you need to fix the code manually:

    * When the declarations are in different header files;
    * When multiple variables are declared together.



  ##### Options

  IgnoreMacros     

  If set to true, the check will not give warnings inside macros. Default is true.

  (Clang-Tidy original name: readability-redundant-declaration)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_RFPD
### Default
#### OriginalId=readability-redundant-function-ptr-dereference
#### Enabled=true
#### Warning=true
#### DisplayName=Redundant Function Ptr Dereference
#### HelpText
  Finds redundant dereferences of a function pointer.

  Before:

  ``` cpp
  int f(int,int);
  int (*p)(int, int) = &f;

  int i = (**p)(10, 50);

  ```


  After:

  ``` cpp
  int f(int,int);
  int (*p)(int, int) = &f;

  int i = (*p)(10, 50);

  ```


  (Clang-Tidy original name: readability-redundant-function-ptr-dereference)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_RMI
### Default
#### OriginalId=readability-redundant-member-init
#### Enabled=true
#### Warning=true
#### DisplayName=Redundant Member Init
#### HelpText
  Finds member initializations that are unnecessary because the same default constructor would be called if they were not present.

  ##### Example

  ``` cpp
  // Explicitly initializing the member s is unnecessary.
  class Foo {
  public:
    Foo() : s() {}

  private:
    std::string s;
  };

  ```


  ##### Options

  IgnoreBaseInCopyConstructors     

  Default is false.

  When true, the check will ignore unnecessary base class initializations within copy constructors, since some compilers issue warnings/errors when base classes are not explicitly intialized in copy constructors. For example, gcc with -Wextra or -Werror=extra issues warning or error base class 'Bar' should be explicitly initialized in the copy constructor if Bar() were removed in the following example:

  ``` cpp
  // Explicitly initializing member s and base class Bar is unnecessary.
  struct Foo : public Bar {
    // Remove s() below. If IgnoreBaseInCopyConstructors!=0, keep Bar().
    Foo(const Foo& foo) : Bar(), s() {}
    std::string s;
  };

  ```


  (Clang-Tidy original name: readability-redundant-member-init)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_RP
### Default
#### OriginalId=readability-redundant-preprocessor
#### Enabled=true
#### Warning=true
#### DisplayName=Redundant Preprocessor
#### HelpText
  Finds potentially redundant preprocessor directives. At the moment the following cases are detected:

    * \#ifdef .. \#endif pairs which are nested inside an outer pair with the same condition. For example:



  ``` cpp
  #ifdef FOO
  #ifdef FOO // inner ifdef is considered redundant
  void f();
  #endif
  #endif

  ```


    * Same for \#ifndef .. \#endif pairs. For example:



  ``` cpp
  #ifndef FOO
  #ifndef FOO // inner ifndef is considered redundant
  void f();
  #endif
  #endif

  ```


    * \#ifndef inside an \#ifdef with the same condition:



  ``` cpp
  #ifdef FOO
  #ifndef FOO // inner ifndef is considered redundant
  void f();
  #endif
  #endif

  ```


    * \#ifdef inside an \#ifndef with the same condition:



  ``` cpp
  #ifndef FOO
  #ifdef FOO // inner ifdef is considered redundant
  void f();
  #endif
  #endif

  ```


    * \#if .. \#endif pairs which are nested inside an outer pair with the same condition. For example:



  ``` cpp
  #define FOO 4
  #if FOO == 4
  #if FOO == 4 // inner if is considered redundant
  void f();
  #endif
  #endif

  ```


  (Clang-Tidy original name: readability-redundant-preprocessor)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_RSC
### Default
#### OriginalId=readability-redundant-string-cstr
#### Enabled=true
#### Warning=true
#### DisplayName=Redundant String Cstr
#### HelpText
  Finds unnecessary calls to std::string::c_str() and std::string::data().

  (Clang-Tidy original name: readability-redundant-string-cstr)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_RSG
### Default
#### OriginalId=readability-redundant-smartptr-get
#### Enabled=true
#### Warning=true
#### DisplayName=Redundant Smartptr Get
#### HelpText
  Find and remove redundant calls to smart pointer’s .get() method.

  Examples:

  ``` cpp
  ptr.get()->Foo()  ==>  ptr->Foo()
  *ptr.get()  ==>  *ptr
  *ptr->get()  ==>  **ptr
  if (ptr.get() == nullptr) ... => if (ptr == nullptr) ...

  ```


  IgnoreMacros     

  If this option is set to true (default is true), the check will not warn about calls inside macros.

  (Clang-Tidy original name: readability-redundant-smartptr-get)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_RSI
### Default
#### OriginalId=readability-redundant-string-init
#### Enabled=true
#### Warning=true
#### DisplayName=Redundant String Init
#### HelpText
  Finds unnecessary string initializations.

  ##### Examples

  ``` cpp
  // Initializing string with empty string literal is unnecessary.
  std::string a = "";
  std::string b("");

  // becomes

  std::string a;
  std::string b;

  // Initializing a string_view with an empty string literal produces an
  // instance that compares equal to string_view().
  std::string_view a = "";
  std::string_view b("");

  // becomes
  std::string_view a;
  std::string_view b;

  ```


  ##### Options

  StringNames     

  Default is ::std::basic_string;::std::basic_string_view.

  Semicolon-delimited list of class names to apply this check to. By default ::std::basic_string applies to std::string and std::wstring. Set to e.g. ::std::basic_string;llvm::StringRef;QString to perform this check on custom classes.

  (Clang-Tidy original name: readability-redundant-string-init)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_SATI
### Default
#### OriginalId=readability-static-accessed-through-instance
#### Enabled=true
#### Warning=true
#### DisplayName=Static Accessed Through Instance
#### HelpText
  Checks for member expressions that access static members through instances, and replaces them with uses of the appropriate qualified-id.

  Example:

  The following code:

  ``` cpp
  struct C {
    static void foo();
    static int x;
  };

  C *c1 = new C();
  c1->foo();
  c1->x;

  ```


  is changed to:

  ``` cpp
  C *c1 = new C();
  C::foo();
  C::x;

  ```


  (Clang-Tidy original name: readability-static-accessed-through-instance)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_SBE
### Default
#### OriginalId=readability-simplify-boolean-expr
#### Enabled=true
#### Warning=true
#### DisplayName=Simplify Boolean Expr
#### HelpText
  Looks for boolean expressions involving boolean constants and simplifies them to use the appropriate boolean expression directly.

  Examples:

  Initial expression | Result  
  ---|---  
  if (b == true) | if (b)  
  if (b == false) | if (!b)  
  if (b && true) | if (b)  
  if (b && false) | if (false)  
  if (b || true) | if (true)  
  if (b || false) | if (b)  
  e ? true : false | e  
  e ? false : true | !e  
  if (true) t(); else f(); | t();  
  if (false) t(); else f(); | f();  
  if (e) return true; else return false; | return e;  
  if (e) return false; else return true; | return !e;  
  if (e) b = true; else b = false; | b = e;  
  if (e) b = false; else b = true; | b = !e;  
  if (e) return true; return false; | return e;  
  if (e) return false; return true; | return !e;  

   The resulting expression e is modified as follows:     

    1. Unnecessary parentheses around the expression are removed.
    2. Negated applications of ! are eliminated.
    3. Negated applications of comparison operators are changed to use the opposite condition.
    4. Implicit conversions of pointers, including pointers to members, to bool are replaced with explicit comparisons to nullptr in C++11 or NULL in C++98/03.
    5. Implicit casts to bool are replaced with explicit casts to bool.
    6. Object expressions with explicit operator bool conversion operators are replaced with explicit casts to bool.
    7. Implicit conversions of integral types to bool are replaced with explicit comparisons to 0.


  Examples:     

    1. The ternary assignment bool b = (i < 0) ? true : false; has redundant parentheses and becomes bool b = i < 0;.

    2. The conditional return if (!b) return false; return true; has an implied double negation and becomes return b;.

    3. The conditional return if (i < 0) return false; return true; becomes return i >= 0;.

  The conditional return if (i != 0) return false; return true; becomes return i == 0;.

    4. The conditional return if (p) return true; return false; has an implicit conversion of a pointer to bool and becomes return p != nullptr;.

  The ternary assignment bool b = (i & 1) ? true : false; has an implicit conversion of i & 1 to bool and becomes bool b = (i & 1) != 0;.

    5. The conditional return if (i & 1) return true; else return false; has an implicit conversion of an integer quantity i & 1 to bool and becomes return (i & 1) != 0;

    6. Given struct X { explicit operator bool(); };, and an instance x of struct X, the conditional return if (x) return true; return false; becomes return static_cast<bool>(x);




  ##### Options

  ChainedConditionalReturn     

  If true, conditional boolean return statements at the end of an if/else if chain will be transformed. Default is false.

  ChainedConditionalAssignment     

  If true, conditional boolean assignments at the end of an if/else if chain will be transformed. Default is false.

  (Clang-Tidy original name: readability-simplify-boolean-expr)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_SC
### Default
#### OriginalId=readability-string-compare
#### Enabled=true
#### Warning=true
#### DisplayName=String Compare
#### HelpText
  Finds string comparisons using the compare method.

  A common mistake is to use the string’s compare method instead of using the equality or inequality operators. The compare method is intended for sorting functions and thus returns a negative number, a positive number or zero depending on the lexicographical relationship between the strings compared. If an equality or inequality check can suffice, that is recommended. This is recommended to avoid the risk of incorrect interpretation of the return value and to simplify the code. The string equality and inequality operators can also be faster than the compare method due to early termination.

  Examples:

  ``` cpp
  std::string str1{"a"};
  std::string str2{"b"};

  // use str1 != str2 instead.
  if (str1.compare(str2)) {
  }

  // use str1 == str2 instead.
  if (!str1.compare(str2)) {
  }

  // use str1 == str2 instead.
  if (str1.compare(str2) == 0) {
  }

  // use str1 != str2 instead.
  if (str1.compare(str2) != 0) {
  }

  // use str1 == str2 instead.
  if (0 == str1.compare(str2)) {
  }

  // use str1 != str2 instead.
  if (0 != str1.compare(str2)) {
  }

  // Use str1 == "foo" instead.
  if (str1.compare("foo") == 0) {
  }

  ```


  The above code examples shows the list of if-statements that this check will give a warning for. All of them uses compare to check if equality or inequality of two strings instead of using the correct operators.

  (Clang-Tidy original name: readability-string-compare)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_SDIAN
### Default
#### OriginalId=readability-static-definition-in-anonymous-namespace
#### Enabled=true
#### Warning=true
#### DisplayName=Static Definition In Anonymous Namespace
#### HelpText
  Finds static function and variable definitions in anonymous namespace.

  In this case, static is redundant, because anonymous namespace limits the visibility of definitions to a single translation unit.

  ``` cpp
  namespace {
    static int a = 1; // Warning.
    static const b = 1; // Warning.
  }

  ```


  The check will apply a fix by removing the redundant static qualifier.

  (Clang-Tidy original name: readability-static-definition-in-anonymous-namespace)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_SSE
### Default
#### OriginalId=readability-simplify-subscript-expr
#### Enabled=true
#### Warning=true
#### DisplayName=Simplify Subscript Expr
#### HelpText
  This check simplifies subscript expressions. Currently this covers calling .data() and immediately doing an array subscript operation to obtain a single element, in which case simply calling operator[] suffice.

  Examples:

  ``` cpp
  std::string s = ...;
  char c = s.data()[i];  // char c = s[i];

  ```


  ##### Options

  Types     

  The list of type(s) that triggers this check. Default is ::std::basic_string;::std::basic_string_view;::std::vector;::std::array

  (Clang-Tidy original name: readability-simplify-subscript-expr)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_UA
### Default
#### OriginalId=readability-use-anyofallof
#### Enabled=true
#### Warning=true
#### DisplayName=Use Anyofallof
#### HelpText
  Finds range-based for loops that can be replaced by a call to std::any_of or std::all_of. In C++ 20 mode, suggests std::ranges::any_of or std::ranges::all_of.

  Example:

  ``` cpp
  bool all_even(std::vector<int> V) {
    for (int I : V) {
      if (I % 2)
        return false;
    }
    return true;
    // Replace loop by
    // return std::ranges::all_of(V, [](int I) { return I % 2 == 0; });
  }

  ```


  (Clang-Tidy original name: readability-use-anyofallof)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_UDR
### Default
#### OriginalId=readability-uniqueptr-delete-release
#### Enabled=true
#### Warning=true
#### DisplayName=Uniqueptr Delete Release
#### HelpText
  Replace delete <unique_ptr>.release() with <unique_ptr> = nullptr. The latter is shorter, simpler and does not require use of raw pointer APIs.

  ``` cpp
  std::unique_ptr<int> P;
  delete P.release();

  // becomes

  std::unique_ptr<int> P;
  P = nullptr;

  ```


  (Clang-Tidy original name: readability-uniqueptr-delete-release)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_RDB_ULS
### Default
#### OriginalId=readability-uppercase-literal-suffix
#### Enabled=true
#### Warning=true
#### DisplayName=Uppercase Literal Suffix
#### HelpText
  cert-dcl16-c redirects here as an alias for this check. By default, only the suffixes that begin with l (l, ll, lu, llu, but not u, ul, ull) are diagnosed by that alias.

  hicpp-uppercase-literal-suffix redirects here as an alias for this check.

  Detects when the integral literal or floating point (decimal or hexadecimal) literal has a non-uppercase suffix and provides a fix-it hint with the uppercase suffix.

  All valid combinations of suffixes are supported.

  ``` cpp
  auto x = 1;  // OK, no suffix.

  auto x = 1u; // warning: integer literal suffix 'u' is not upper-case

  auto x = 1U; // OK, suffix is uppercase.

  ...

  ```


  ##### Options

  NewSuffixes     

  Optionally, a list of the destination suffixes can be provided. When the suffix is found, a case-insensitive lookup in that list is made, and if a replacement is found that is different from the current suffix, then the diagnostic is issued. This allows for fine-grained control of what suffixes to consider and what their replacements should be.

  ###### Example

  Given a list L;uL:

    * l -> L
    * L will be kept as is.
    * ul -> uL
    * Ul -> uL
    * UL -> uL
    * uL will be kept as is.
    * ull will be kept as is, since it is not in the list
    * and so on.

  IgnoreMacros     

  If this option is set to true (default is true), the check will not warn about literal suffixes inside macros.

  (Clang-Tidy original name: readability-uppercase-literal-suffix)

#### Tags
- /general/Readability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_BLT_BF
### Default
#### OriginalId=clang-analyzer-core.builtin.BuiltinFunctions
#### Enabled=true
#### Warning=true
#### DisplayName=Builtin Functions
#### Tags
- /general/Static Analyzer - Core\Builtin
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_BLT_NRF
### Default
#### OriginalId=clang-analyzer-core.builtin.NoReturnFunctions
#### Enabled=true
#### Warning=true
#### DisplayName=No Return Functions
#### Tags
- /general/Static Analyzer - Core\Builtin
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_COR_CAM
### Default
#### OriginalId=clang-analyzer-core.CallAndMessage
#### Enabled=true
#### Warning=true
#### DisplayName=Call And Message
#### HelpText
  Check for logical errors for function calls and Objective-C message expressions (e.g., uninitialized arguments, null function pointers).

  ``` cpp
  //C
  void test() {
     void (*foo)(void);
     foo = 0;
     foo(); // warn: function pointer is null
   }

   // C++
   class C {
   public:
     void f();
   };

   void test() {
     C *pc;
     pc->f(); // warn: object pointer is uninitialized
   }

   // C++
   class C {
   public:
     void f();
   };

   void test() {
     C *pc = 0;
     pc->f(); // warn: object pointer is null
   }

   // Objective-C
   @interface MyClass : NSObject
   @property (readwrite,assign) id x;
   - (long double)longDoubleM;
   @end

   void test() {
     MyClass *obj1;
     long double ld1 = [obj1 longDoubleM];
       // warn: receiver is uninitialized
   }

   // Objective-C
   @interface MyClass : NSObject
   @property (readwrite,assign) id x;
   - (long double)longDoubleM;
   @end

   void test() {
     MyClass *obj1;
     id i = obj1.x; // warn: uninitialized object pointer
   }

   // Objective-C
   @interface Subscriptable : NSObject
   - (id)objectAtIndexedSubscript:(unsigned int)index;
   @end

   @interface MyClass : Subscriptable
   @property (readwrite,assign) id x;
   - (long double)longDoubleM;
   @end

   void test() {
     MyClass *obj1;
     id i = obj1[0]; // warn: uninitialized object pointer
   }

  ```


  (Clang-Tidy original name: clang-analyzer-core.CallAndMessage)

#### Tags
- /general/Static Analyzer - Core
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_COR_DTP
### Default
#### OriginalId=clang-analyzer-core.DynamicTypePropagation
#### Enabled=true
#### Warning=true
#### DisplayName=Dynamic Type Propagation
#### Tags
- /general/Static Analyzer - Core
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_COR_DZ
### Default
#### OriginalId=clang-analyzer-core.DivideZero
#### Enabled=true
#### Warning=true
#### DisplayName=Divide Zero
#### HelpText
  Check for division by zero.

  ``` cpp
  void test(int z) {
    if (z == 0)
      int x = 1 / z; // warn
  }

  void test() {
    int x = 1;
    int y = x % 0; // warn
  }

  ```


  (Clang-Tidy original name: clang-analyzer-core.DivideZero)

#### Tags
- /general/Static Analyzer - Core
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_COR_ND
### Default
#### OriginalId=clang-analyzer-core.NullDereference
#### Enabled=true
#### Warning=true
#### DisplayName=Null Dereference
#### HelpText
  Check for dereferences of null pointers.

  ``` cpp
  // C
  void test(int *p) {
    if (p)
      return;

    int x = p[0]; // warn
  }

  // C
  void test(int *p) {
    if (!p)
      *p = 0; // warn
  }

  // C++
  class C {
  public:
    int x;
  };

  void test() {
    C *pc = 0;
    int k = pc->x; // warn
  }

  // Objective-C
  @interface MyClass {
  @public
    int x;
  }
  @end

  void test() {
    MyClass *obj = 0;
    obj->x = 1; // warn
  }

  ```


  (Clang-Tidy original name: clang-analyzer-core.NullDereference)

#### Tags
- /general/Static Analyzer - Core
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_COR_NNPC
### Default
#### OriginalId=clang-analyzer-core.NonNullParamChecker
#### Enabled=true
#### Warning=true
#### DisplayName=Non Null Param Checker
#### HelpText
  Check for null pointers passed as arguments to a function whose arguments are references or marked with the ‘nonnull’ attribute.

  ``` cpp
  int f(int *p) __attribute__((nonnull));

  void test(int *p) {
    if (!p)
      f(p); // warn
  }

  ```


  (Clang-Tidy original name: clang-analyzer-core.NonNullParamChecker)

#### Tags
- /general/Static Analyzer - Core
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_COR_NNSC
### Default
#### OriginalId=clang-analyzer-core.NonnilStringConstants
#### Enabled=true
#### Warning=true
#### DisplayName=Non Nil String Constants
#### Tags
- /general/Static Analyzer - Core
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_COR_SAE
### Default
#### OriginalId=clang-analyzer-core.StackAddressEscape
#### Enabled=true
#### Warning=true
#### DisplayName=Stack Address Escape
#### HelpText
  Check that addresses to stack memory do not escape the function.

  ``` cpp
  char const *p;

  void test() {
    char const str[] = "string";
    p = str; // warn
  }

  void* test() {
     return __builtin_alloca(12); // warn
  }

  void test() {
    static int *x;
    int y;
    x = &y; // warn
  }

  ```


  (Clang-Tidy original name: clang-analyzer-core.StackAddressEscape)

#### Tags
- /general/Static Analyzer - Core
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_COR_SAEB
### Default
#### OriginalId=clang-analyzer-core.StackAddrEscapeBase
#### Enabled=true
#### Warning=true
#### DisplayName=Stack Address Escape Base
#### Tags
- /general/Static Analyzer - Core
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_COR_UBOR
### Default
#### OriginalId=clang-analyzer-core.UndefinedBinaryOperatorResult
#### Enabled=true
#### Warning=true
#### DisplayName=Undefined Binary Operator Result
#### HelpText
  Check for undefined results of binary operators.

  ``` cpp
  void test() {
    int x;
    int y = x + 1; // warn: left operand is garbage
  }

  ```


  (Clang-Tidy original name: clang-analyzer-core.UndefinedBinaryOperatorResult)

#### Tags
- /general/Static Analyzer - Core
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_COR_VS
### Default
#### OriginalId=clang-analyzer-core.VLASize
#### Enabled=true
#### Warning=true
#### DisplayName=VLA Size
#### HelpText
  Check for declarations of Variable Length Arrays of undefined or zero size.

  Check for declarations of VLA of undefined or zero size.

  ``` cpp
  void test() {
    int x;
    int vla1[x]; // warn: garbage as size
  }

  void test() {
    int x = 0;
    int vla2[x]; // warn: zero size
  }

  ```


  (Clang-Tidy original name: clang-analyzer-core.VLASize)

#### Tags
- /general/Static Analyzer - Core
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_CPP_IP
### Default
#### OriginalId=clang-analyzer-cplusplus.InnerPointer
#### Enabled=true
#### Warning=true
#### DisplayName=Inner Pointer
#### HelpText
  Check for inner pointers of C++ containers used after re/deallocation.

  Many container methods in the C++ standard library are known to invalidate “references” (including actual references, iterators and raw pointers) to elements of the container. Using such references after they are invalidated causes undefined behavior, which is a common source of memory errors in C++ that this checker is capable of finding.

  The checker is currently limited to std::string objects and doesn’t recognize some of the more sophisticated approaches to passing unowned pointers around, such as std::string_view.

  ``` cpp
  void deref_after_assignment() {
    std::string s = "llvm";
    const char *c = s.data(); // note: pointer to inner buffer of 'std::string' obtained here
    s = "clang"; // note: inner buffer of 'std::string' reallocated by call to 'operator='
    consume(c); // warn: inner pointer of container used after re/deallocation
  }

  const char *return_temp(int x) {
    return std::to_string(x).c_str(); // warn: inner pointer of container used after re/deallocation
    // note: pointer to inner buffer of 'std::string' obtained here
    // note: inner buffer of 'std::string' deallocated by call to destructor
  }

  ```


  (Clang-Tidy original name: clang-analyzer-cplusplus.InnerPointer)

#### Tags
- /general/Static Analyzer - C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_CPP_M
### Default
#### OriginalId=clang-analyzer-cplusplus.Move
#### Enabled=true
#### Warning=true
#### DisplayName=Move
#### Tags
- /general/Static Analyzer - C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_CPP_ND
### Default
#### OriginalId=clang-analyzer-cplusplus.NewDelete
#### Enabled=true
#### Warning=true
#### DisplayName=New Delete
#### HelpText
  Check for double-free and use-after-free problems. Traces memory managed by new/delete.

  ``` cpp
  void f(int *p);

  void testUseMiddleArgAfterDelete(int *p) {
    delete p;
    f(p); // warn: use after free
  }

  class SomeClass {
  public:
    void f();
  };

  void test() {
    SomeClass *c = new SomeClass;
    delete c;
    c->f(); // warn: use after free
  }

  void test() {
    int *p = (int *)__builtin_alloca(sizeof(int));
    delete p; // warn: deleting memory allocated by alloca
  }

  void test() {
    int *p = new int;
    delete p;
    delete p; // warn: attempt to free released
  }

  void test() {
    int i;
    delete &i; // warn: delete address of local
  }

  void test() {
    int *p = new int[1];
    delete[] (++p);
      // warn: argument to 'delete[]' is offset by 4 bytes
      // from the start of memory allocated by 'new[]'
  }

  ```


  (Clang-Tidy original name: clang-analyzer-cplusplus.NewDelete)

#### Tags
- /general/Static Analyzer - C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_CPP_NDL
### Default
#### OriginalId=clang-analyzer-cplusplus.NewDeleteLeaks
#### Enabled=true
#### Warning=true
#### DisplayName=New Delete Leaks
#### HelpText
  Check for memory leaks. Traces memory managed by new/delete.

  ``` cpp
  void test() {
    int *p = new int;
  } // warn

  ```


  (Clang-Tidy original name: clang-analyzer-cplusplus.NewDeleteLeaks)

#### Tags
- /general/Static Analyzer - C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_CPP_PNC
### Default
#### OriginalId=clang-analyzer-cplusplus.PlacementNew
#### Enabled=true
#### Warning=true
#### DisplayName=Placement New Checker
#### HelpText
  Check if default placement new is provided with pointers to sufficient storage capacity.

  ``` cpp
  #include <new>

  void f() {
    short s;
    long *lp = ::new (&s) long; // warn
  }

  ```


  (Clang-Tidy original name: clang-analyzer-cplusplus.PlacementNew)

#### Tags
- /general/Static Analyzer - C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_CPP_PVC
### Default
#### OriginalId=clang-analyzer-cplusplus.PureVirtualCall
#### Enabled=true
#### Warning=true
#### DisplayName=Pure Virtual Call
#### Tags
- /general/Static Analyzer - C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_CPP_SA
### Default
#### OriginalId=clang-analyzer-cplusplus.SelfAssignment
#### Enabled=true
#### Warning=true
#### DisplayName=Self Assignment
#### HelpText
  Checks C++ copy and move assignment operators for self assignment.

  (Clang-Tidy original name: clang-analyzer-cplusplus.SelfAssignment)

#### Tags
- /general/Static Analyzer - C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_DCD_DS
### Default
#### OriginalId=clang-analyzer-deadcode.DeadStores
#### Enabled=true
#### Warning=true
#### DisplayName=Dead Stores
#### HelpText
  Check for values stored to variables that are never read afterwards.

  ``` cpp
  void test() {
    int x;
    x = 1; // warn
  }

  ```


  The WarnForDeadNestedAssignments option enables the checker to emit warnings for nested dead assignments. You can disable with the -analyzer-config deadcode.DeadStores:WarnForDeadNestedAssignments=false. _Defaults to true_.

  Would warn for this e.g.: if ((y = make_int())) { }

  (Clang-Tidy original name: clang-analyzer-deadcode.DeadStores)

#### Tags
- /general/Static Analyzer - Dead Code
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_FCS_HC
### Default
#### OriginalId=clang-analyzer-fuchsia.HandleChecker
#### Enabled=false
#### Warning=true
#### DisplayName=Handle Checker
#### HelpText
  Handles identify resources. Similar to pointers they can be leaked, double freed, or use after freed. This check attempts to find such problems.

  ``` cpp
  void checkLeak08(int tag) {
    zx_handle_t sa, sb;
    zx_channel_create(0, &sa, &sb);
    if (tag)
      zx_handle_close(sa);
    use(sb); // Warn: Potential leak of handle
    zx_handle_close(sb);
  }

  ```


  (Clang-Tidy original name: clang-analyzer-fuchsia.HandleChecker)

#### Tags
- /general/Static Analyzer - Fuchsia
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_NUL_NB
### Default
#### OriginalId=clang-analyzer-nullability.NullabilityBase
#### Enabled=true
#### Warning=true
#### DisplayName=Nullability Base
#### Tags
- /general/Static Analyzer - Nullability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_NUL_ND
### Default
#### OriginalId=clang-analyzer-nullability.NullableDereferenced
#### Enabled=true
#### Warning=true
#### DisplayName=Nullable Dereferenced
#### HelpText
  Warns when a nullable pointer is dereferenced.

  ``` cpp
  struct LinkedList {
    int data;
    struct LinkedList *next;
  };

  struct LinkedList * _Nullable getNext(struct LinkedList *l);

  void updateNextData(struct LinkedList *list, int newData) {
    struct LinkedList *next = getNext(list);
    // Warning: Nullable pointer is dereferenced
    next->data = 7;
  }

  ```


  (Clang-Tidy original name: clang-analyzer-nullability.NullableDereferenced)

#### Tags
- /general/Static Analyzer - Nullability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_NUL_NPTN
### Default
#### OriginalId=clang-analyzer-nullability.NullablePassedToNonnull
#### Enabled=true
#### Warning=true
#### DisplayName=Nullable Passed To Nonnull
#### HelpText
  Warns when a nullable pointer is passed to a pointer which has a _Nonnull type.

  ``` cpp
  typedef struct Dummy { int val; } Dummy;
  Dummy *_Nullable returnsNullable();
  void takesNonnull(Dummy *_Nonnull);

  void test() {
    Dummy *p = returnsNullable();
    takesNonnull(p); // warn
  }

  ```


  (Clang-Tidy original name: clang-analyzer-nullability.NullablePassedToNonnull)

#### Tags
- /general/Static Analyzer - Nullability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_NUL_NPTN2
### Default
#### OriginalId=clang-analyzer-nullability.NullPassedToNonnull
#### Enabled=true
#### Warning=true
#### DisplayName=Null Passed To Nonnull
#### HelpText
  Warns when a null pointer is passed to a pointer which has a _Nonnull type.

  ``` cpp
  if (name != nil)
    return;
  // Warning: nil passed to a callee that requires a non-null 1st parameter
  NSString *greeting = [@"Hello " stringByAppendingString:name];

  ```


  (Clang-Tidy original name: clang-analyzer-nullability.NullPassedToNonnull)

#### Tags
- /general/Static Analyzer - Nullability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_NUL_NRFN
### Default
#### OriginalId=clang-analyzer-nullability.NullableReturnedFromNonnull
#### Enabled=true
#### Warning=true
#### DisplayName=Nullable Returned From Nonnull
#### HelpText
  Warns when a nullable pointer is returned from a function that has _Nonnull return type.

  (Clang-Tidy original name: clang-analyzer-nullability.NullableReturnedFromNonnull)

#### Tags
- /general/Static Analyzer - Nullability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_NUL_NRFN2
### Default
#### OriginalId=clang-analyzer-nullability.NullReturnedFromNonnull
#### Enabled=true
#### Warning=true
#### DisplayName=Null Returned From Nonnull
#### HelpText
  Warns when a null pointer is returned from a function that has _Nonnull return type.

  ``` cpp
  - (nonnull id)firstChild {
    id result = nil;
    if ([_children count] > 0)
      result = _children[0];

    // Warning: nil returned from a method that is expected
    // to return a non-null value
    return result;
  }

  ```


  (Clang-Tidy original name: clang-analyzer-nullability.NullReturnedFromNonnull)

#### Tags
- /general/Static Analyzer - Nullability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OI_CPP_UO
### Default
#### OriginalId=clang-analyzer-optin.cplusplus.UninitializedObject
#### Enabled=true
#### Warning=true
#### DisplayName=Uninitialized Object
#### HelpText
  This checker reports uninitialized fields in objects created after a constructor call. It doesn’t only find direct uninitialized fields, but rather makes a deep inspection of the object, analyzing all of it’s fields subfields. The checker regards inherited fields as direct fields, so one will receive warnings for uninitialized inherited data members as well.

  ``` cpp
  // With Pedantic and CheckPointeeInitialization set to true

  struct A {
    struct B {
      int x; // note: uninitialized field 'this->b.x'
      // note: uninitialized field 'this->bptr->x'
      int y; // note: uninitialized field 'this->b.y'
      // note: uninitialized field 'this->bptr->y'
    };
    int *iptr; // note: uninitialized pointer 'this->iptr'
    B b;
    B *bptr;
    char *cptr; // note: uninitialized pointee 'this->cptr'

    A (B *bptr, char *cptr) : bptr(bptr), cptr(cptr) {}
  };

  void f() {
    A::B b;
    char c;
    A a(&b, &c); // warning: 6 uninitialized fields
   //          after the constructor call
  }

  // With Pedantic set to false and
  // CheckPointeeInitialization set to true
  // (every field is uninitialized)

  struct A {
    struct B {
      int x;
      int y;
    };
    int *iptr;
    B b;
    B *bptr;
    char *cptr;

    A (B *bptr, char *cptr) : bptr(bptr), cptr(cptr) {}
  };

  void f() {
    A::B b;
    char c;
    A a(&b, &c); // no warning
  }

  // With Pedantic set to true and
  // CheckPointeeInitialization set to false
  // (pointees are regarded as initialized)

  struct A {
    struct B {
      int x; // note: uninitialized field 'this->b.x'
      int y; // note: uninitialized field 'this->b.y'
    };
    int *iptr; // note: uninitialized pointer 'this->iptr'
    B b;
    B *bptr;
    char *cptr;

    A (B *bptr, char *cptr) : bptr(bptr), cptr(cptr) {}
  };

  void f() {
    A::B b;
    char c;
    A a(&b, &c); // warning: 3 uninitialized fields
   //          after the constructor call
  }

  ```


  **Options**

  This checker has several options which can be set from command line (e.g. -analyzer-config optin.cplusplus.UninitializedObject:Pedantic=true):

    * Pedantic (boolean). If to false, the checker won’t emit warnings for objects that don’t have at least one initialized field. Defaults to false.
    * NotesAsWarnings (boolean). If set to true, the checker will emit a warning for each uninitialized field, as opposed to emitting one warning per constructor call, and listing the uninitialized fields that belongs to it in notes. _Defaults to false_.
    * CheckPointeeInitialization (boolean). If set to false, the checker will not analyze the pointee of pointer/reference fields, and will only check whether the object itself is initialized. _Defaults to false_.
    * IgnoreRecordsWithField (string). If supplied, the checker will not analyze structures that have a field with a name or type name that matches the given pattern. _Defaults to “”_.



  (Clang-Tidy original name: clang-analyzer-optin.cplusplus.UninitializedObject)

#### Tags
- /general/Static Analyzer - OptIn\C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OI_CPP_VC
### Default
#### OriginalId=clang-analyzer-optin.cplusplus.VirtualCall
#### Enabled=true
#### Warning=true
#### DisplayName=Virtual Call
#### HelpText
  Check virtual function calls during construction or destruction.

  ``` cpp
  class A {
  public:
    A() {
      f(); // warn
    }
    virtual void f();
  };

  class A {
  public:
    ~A() {
      this->f(); // warn
    }
    virtual void f();
  };

  ```


  (Clang-Tidy original name: clang-analyzer-optin.cplusplus.VirtualCall)

#### Tags
- /general/Static Analyzer - OptIn\C++
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OI_MPI_M
### Default
#### OriginalId=clang-analyzer-optin.mpi.MPI-Checker
#### Enabled=true
#### Warning=true
#### DisplayName=MPI-Checker
#### HelpText
  Checks MPI code.

  ``` cpp
  void test() {
    double buf = 0;
    MPI_Request sendReq1;
    MPI_Ireduce(MPI_IN_PLACE, &buf, 1, MPI_DOUBLE, MPI_SUM,
        0, MPI_COMM_WORLD, &sendReq1);
  } // warn: request 'sendReq1' has no matching wait.

  void test() {
    double buf = 0;
    MPI_Request sendReq;
    MPI_Isend(&buf, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &sendReq);
    MPI_Irecv(&buf, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &sendReq); // warn
    MPI_Isend(&buf, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &sendReq); // warn
    MPI_Wait(&sendReq, MPI_STATUS_IGNORE);
  }

  void missingNonBlocking() {
    int rank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Request sendReq1[10][10][10];
    MPI_Wait(&sendReq1[1][7][9], MPI_STATUS_IGNORE); // warn
  }

  ```


  (Clang-Tidy original name: clang-analyzer-optin.mpi.MPI-Checker)

#### Tags
- /general/Static Analyzer - OptIn\MPI
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OI_OSX_LOC_ELCC
### Default
#### OriginalId=clang-analyzer-optin.osx.cocoa.localizability.EmptyLocalizationContextChecker
#### Enabled=false
#### Warning=true
#### DisplayName=Empty Localization Context Checker
#### HelpText
  Check that NSLocalizedString macros include a comment for context.

  ``` cpp
  - (void)test {
    NSString *string = NSLocalizedString(@"LocalizedString", nil); // warn
    NSString *string2 = NSLocalizedString(@"LocalizedString", @" "); // warn
    NSString *string3 = NSLocalizedStringWithDefaultValue(
      @"LocalizedString", nil, [[NSBundle alloc] init], nil,@""); // warn
  }

  ```


  (Clang-Tidy original name: clang-analyzer-optin.osx.cocoa.localizability.EmptyLocalizationContextChecker)

#### Tags
- /general/Static Analyzer - OptIn\Cocoa Localizability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OI_OSX_LOC_NLSC
### Default
#### OriginalId=clang-analyzer-optin.osx.cocoa.localizability.NonLocalizedStringChecker
#### Enabled=false
#### Warning=true
#### DisplayName=Non Localized String Checker
#### HelpText
  Warns about uses of non-localized NSStrings passed to UI methods expecting localized NSStrings.

  ``` cpp
  NSString *alarmText =
    NSLocalizedString(@"Enabled", @"Indicates alarm is turned on");
  if (!isEnabled) {
    alarmText = @"Disabled";
  }
  UILabel *alarmStateLabel = [[UILabel alloc] init];

  // Warning: User-facing text should use localized string macro
  [alarmStateLabel setText:alarmText];

  ```


  (Clang-Tidy original name: clang-analyzer-optin.osx.cocoa.localizability.NonLocalizedStringChecker)

#### Tags
- /general/Static Analyzer - OptIn\Cocoa Localizability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OI_OSX_OCC
### Default
#### OriginalId=clang-analyzer-optin.osx.OSObjectCStyleCast
#### Enabled=false
#### Warning=true
#### DisplayName=OSObject C-Style Cast
#### Tags
- /general/Static Analyzer - OptIn\macOS
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OI_PRF_GA
### Default
#### OriginalId=clang-analyzer-optin.performance.GCDAntipattern
#### Enabled=true
#### Warning=true
#### DisplayName=GCD Antipattern
#### HelpText
  Check for performance anti-patterns when using Grand Central Dispatch.

  (Clang-Tidy original name: clang-analyzer-optin.performance.GCDAntipattern)

#### Tags
- /general/Static Analyzer - OptIn\Performance
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OI_PRF_P
### Default
#### OriginalId=clang-analyzer-optin.performance.Padding
#### Enabled=true
#### Warning=true
#### DisplayName=Padding
#### HelpText
  Check for excessively padded structs.

  (Clang-Tidy original name: clang-analyzer-optin.performance.Padding)

#### Tags
- /general/Static Analyzer - OptIn\Performance
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OI_PRT_UA
### Default
#### OriginalId=clang-analyzer-optin.portability.UnixAPI
#### Enabled=true
#### Warning=true
#### DisplayName=Unix API
#### HelpText
  Finds implementation-defined behavior in UNIX/Posix functions.

  (Clang-Tidy original name: clang-analyzer-optin.portability.UnixAPI)

#### Tags
- /general/Static Analyzer - OptIn\Portability
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OSX_A
### Default
#### OriginalId=clang-analyzer-osx.API
#### Enabled=false
#### Warning=true
#### DisplayName=API
#### HelpText
  Check for proper uses of various Apple APIs.

  ``` cpp
  void test() {
    dispatch_once_t pred = 0;
    dispatch_once(&pred, ^(){}); // warn: dispatch_once uses local
  }

  ```


  (Clang-Tidy original name: clang-analyzer-osx.API)

#### Tags
- /general/Static Analyzer - macOS
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OSX_CCA_AS
### Default
#### OriginalId=clang-analyzer-osx.cocoa.AtSync
#### Enabled=false
#### Warning=true
#### DisplayName=At Sync
#### HelpText
  Check for nil pointers used as mutexes for @synchronized.

  ``` cpp
  void test(id x) {
    if (!x)
      @synchronized(x) {} // warn: nil value used as mutex
  }

  void test() {
    id y;
    @synchronized(y) {} // warn: uninitialized value used as mutex
  }

  ```


  (Clang-Tidy original name: clang-analyzer-osx.cocoa.AtSync)

#### Tags
- /general/Static Analyzer - macOS\Cocoa API
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OSX_CCA_AW
### Default
#### OriginalId=clang-analyzer-osx.cocoa.AutoreleaseWrite
#### Enabled=false
#### Warning=true
#### DisplayName=Autorelease Write
#### HelpText
  Warn about potentially crashing writes to autoreleasing objects from different autoreleasing pools in Objective-C.

  (Clang-Tidy original name: clang-analyzer-osx.cocoa.AutoreleaseWrite)

#### Tags
- /general/Static Analyzer - macOS\Cocoa API
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OSX_CCA_CR
### Default
#### OriginalId=clang-analyzer-osx.cocoa.ClassRelease
#### Enabled=false
#### Warning=true
#### DisplayName=Class Release
#### HelpText
  Check for sending ‘retain’, ‘release’, or ‘autorelease’ directly to a Class.

  ``` cpp
  @interface MyClass : NSObject
  @end

  void test(void) {
    [MyClass release]; // warn
  }

  ```


  (Clang-Tidy original name: clang-analyzer-osx.cocoa.ClassRelease)

#### Tags
- /general/Static Analyzer - macOS\Cocoa API
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OSX_CCA_D
### Default
#### OriginalId=clang-analyzer-osx.cocoa.Dealloc
#### Enabled=false
#### Warning=true
#### DisplayName=Dealloc
#### HelpText
  Warn about Objective-C classes that lack a correct implementation of -dealloc

  ``` cpp
  @interface MyObject : NSObject {
    id _myproperty;
  }
  @end

  @implementation MyObject // warn: lacks 'dealloc'
  @end

  @interface MyObject : NSObject {}
  @property(assign) id myproperty;
  @end

  @implementation MyObject // warn: does not send 'dealloc' to super
  - (void)dealloc {
    self.myproperty = 0;
  }
  @end

  @interface MyObject : NSObject {
    id _myproperty;
  }
  @property(retain) id myproperty;
  @end

  @implementation MyObject
  @synthesize myproperty = _myproperty;
    // warn: var was retained but wasn't released
  - (void)dealloc {
    [super dealloc];
  }
  @end

  @interface MyObject : NSObject {
    id _myproperty;
  }
  @property(assign) id myproperty;
  @end

  @implementation MyObject
  @synthesize myproperty = _myproperty;
    // warn: var wasn't retained but was released
  - (void)dealloc {
    [_myproperty release];
    [super dealloc];
  }
  @end

  ```


  (Clang-Tidy original name: clang-analyzer-osx.cocoa.Dealloc)

#### Tags
- /general/Static Analyzer - macOS\Cocoa API
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OSX_CCA_IMT
### Default
#### OriginalId=clang-analyzer-osx.cocoa.IncompatibleMethodTypes
#### Enabled=false
#### Warning=true
#### DisplayName=Incompatible Method Types
#### HelpText
  Warn about Objective-C method signatures with type incompatibilities.

  ``` cpp
  @interface MyClass1 : NSObject
  - (int)foo;
  @end

  @implementation MyClass1
  - (int)foo { return 1; }
  @end

  @interface MyClass2 : MyClass1
  - (float)foo;
  @end

  @implementation MyClass2
  - (float)foo { return 1.0; } // warn
  @end

  ```


  (Clang-Tidy original name: clang-analyzer-osx.cocoa.IncompatibleMethodTypes)

#### Tags
- /general/Static Analyzer - macOS\Cocoa API
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OSX_CCA_L
### Default
#### OriginalId=clang-analyzer-osx.cocoa.Loops
#### Enabled=false
#### Warning=true
#### DisplayName=Loops
#### HelpText
  Improved modeling of loops using Cocoa collection types.

  (Clang-Tidy original name: clang-analyzer-osx.cocoa.Loops)

#### Tags
- /general/Static Analyzer - macOS\Cocoa API
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OSX_CCA_MSC
### Default
#### OriginalId=clang-analyzer-osx.cocoa.MissingSuperCall
#### Enabled=false
#### Warning=true
#### DisplayName=Missing Super Call
#### HelpText
  Warn about Objective-C methods that lack a necessary call to super.

  ``` cpp
  @interface Test : UIViewController
  @end
  @implementation test
  - (void)viewDidLoad {} // warn
  @end

  ```


  (Clang-Tidy original name: clang-analyzer-osx.cocoa.MissingSuperCall)

#### Tags
- /general/Static Analyzer - macOS\Cocoa API
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OSX_CCA_NA
### Default
#### OriginalId=clang-analyzer-osx.cocoa.NilArg
#### Enabled=false
#### Warning=true
#### DisplayName=Nil Arg
#### HelpText
  Check for prohibited nil arguments to ObjC method calls.

    * caseInsensitiveCompare:
    * compare:
    * compare:options:
    * compare:options:range:
    * compare:options:range:locale:
    * componentsSeparatedByCharactersInSet:
    * initWithFormat:



  ``` cpp
  NSComparisonResult test(NSString *s) {
    NSString *aString = nil;
    return [s caseInsensitiveCompare:aString];
      // warn: argument to 'NSString' method
      // 'caseInsensitiveCompare:' cannot be nil
  }

  ```


  (Clang-Tidy original name: clang-analyzer-osx.cocoa.NilArg)

#### Tags
- /general/Static Analyzer - macOS\Cocoa API
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OSX_CCA_NAP
### Default
#### OriginalId=clang-analyzer-osx.cocoa.NSAutoreleasePool
#### Enabled=false
#### Warning=true
#### DisplayName=NS Autorelease Pool
#### HelpText
  Warn for suboptimal uses of NSAutoreleasePool in Objective-C GC mode.

  ``` cpp
  void test() {
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    [pool release]; // warn
  }

  ```


  (Clang-Tidy original name: clang-analyzer-osx.cocoa.NSAutoreleasePool)

#### Tags
- /general/Static Analyzer - macOS\Cocoa API
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OSX_CCA_NE
### Default
#### OriginalId=clang-analyzer-osx.cocoa.NSError
#### Enabled=false
#### Warning=true
#### DisplayName=NS Error
#### HelpText
  Check usage of NSError parameters.

  ``` cpp
  @interface A : NSObject
  - (void)foo:(NSError """""""""""""""""""""""")error;
  @end

  @implementation A
  - (void)foo:(NSError """""""""""""""""""""""")error {
    // warn: method accepting NSError"""""""""""""""""""""""" should have a non-void
    // return value
  }
  @end

  @interface A : NSObject
  - (BOOL)foo:(NSError """""""""""""""""""""""")error;
  @end

  @implementation A
  - (BOOL)foo:(NSError """""""""""""""""""""""")error {
    *error = 0; // warn: potential null dereference
    return 0;
  }
  @end

  ```


  (Clang-Tidy original name: clang-analyzer-osx.cocoa.NSError)

#### Tags
- /general/Static Analyzer - macOS\Cocoa API
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OSX_CCA_NNRV
### Default
#### OriginalId=clang-analyzer-osx.cocoa.NonNilReturnValue
#### Enabled=false
#### Warning=true
#### DisplayName=Non Nil Return Value
#### HelpText
  Models the APIs that are guaranteed to return a non-nil value.

  (Clang-Tidy original name: clang-analyzer-osx.cocoa.NonNilReturnValue)

#### Tags
- /general/Static Analyzer - macOS\Cocoa API
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OSX_CCA_OCG
### Default
#### OriginalId=clang-analyzer-osx.cocoa.ObjCGenerics
#### Enabled=false
#### Warning=true
#### DisplayName=Obj C Generics
#### HelpText
  Check for type errors when using Objective-C generics.

  ``` cpp
  NSMutableArray *names = [NSMutableArray array];
  NSMutableArray *birthDates = names;

  // Warning: Conversion from value of type 'NSDate *'
  // to incompatible type 'NSString *'
  [birthDates addObject: [NSDate date]];

  ```


  (Clang-Tidy original name: clang-analyzer-osx.cocoa.ObjCGenerics)

#### Tags
- /general/Static Analyzer - macOS\Cocoa API
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OSX_CCA_RC
### Default
#### OriginalId=clang-analyzer-osx.cocoa.RetainCount
#### Enabled=false
#### Warning=true
#### DisplayName=Retain Count
#### HelpText
  Check for leaks and improper reference count management

  ``` cpp
  void test() {
    NSString *s = [[NSString alloc] init]; // warn
  }

  CFStringRef test(char *bytes) {
    return CFStringCreateWithCStringNoCopy(
             0, bytes, NSNEXTSTEPStringEncoding, 0); // warn
  }

  ```


  (Clang-Tidy original name: clang-analyzer-osx.cocoa.RetainCount)

#### Tags
- /general/Static Analyzer - macOS\Cocoa API
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OSX_CCA_RCB
### Default
#### OriginalId=clang-analyzer-osx.cocoa.RetainCountBase
#### Enabled=false
#### Warning=true
#### DisplayName=Retain Count Base
#### Tags
- /general/Static Analyzer - macOS\Cocoa API
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OSX_CCA_RLAL
### Default
#### OriginalId=clang-analyzer-osx.cocoa.RunLoopAutoreleaseLeak
#### Enabled=false
#### Warning=true
#### DisplayName=Run Loop Autorelease Leak
#### HelpText
  Check for leaked memory in autorelease pools that will never be drained.

  (Clang-Tidy original name: clang-analyzer-osx.cocoa.RunLoopAutoreleaseLeak)

#### Tags
- /general/Static Analyzer - macOS\Cocoa API
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OSX_CCA_SD
### Default
#### OriginalId=clang-analyzer-osx.cocoa.SuperDealloc
#### Enabled=false
#### Warning=true
#### DisplayName=Super Dealloc
#### HelpText
  Warn about improper use of ‘[super dealloc]’ in Objective-C.

  ``` cpp
  @interface SuperDeallocThenReleaseIvarClass : NSObject {
    NSObject *_ivar;
  }
  @end

  @implementation SuperDeallocThenReleaseIvarClass
  - (void)dealloc {
    [super dealloc];
    [_ivar release]; // warn
  }
  @end

  ```


  (Clang-Tidy original name: clang-analyzer-osx.cocoa.SuperDealloc)

#### Tags
- /general/Static Analyzer - macOS\Cocoa API
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OSX_CCA_SI
### Default
#### OriginalId=clang-analyzer-osx.cocoa.SelfInit
#### Enabled=false
#### Warning=true
#### DisplayName=Self Init
#### HelpText
  Check that ‘self’ is properly initialized inside an initializer method.

  ``` cpp
  @interface MyObj : NSObject {
    id x;
  }
  - (id)init;
  @end

  @implementation MyObj
  - (id)init {
    [super init];
    x = 0; // warn: instance variable used while 'self' is not
           // initialized
    return 0;
  }
  @end

  @interface MyObj : NSObject
  - (id)init;
  @end

  @implementation MyObj
  - (id)init {
    [super init];
    return self; // warn: returning uninitialized 'self'
  }
  @end

  ```


  (Clang-Tidy original name: clang-analyzer-osx.cocoa.SelfInit)

#### Tags
- /general/Static Analyzer - macOS\Cocoa API
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OSX_CCA_UI
### Default
#### OriginalId=clang-analyzer-osx.cocoa.UnusedIvars
#### Enabled=false
#### Warning=true
#### DisplayName=Unused Ivars
#### HelpText
  Warn about private ivars that are never used.

  ``` cpp
  @interface MyObj : NSObject {
  @private
    id x; // warn
  }
  @end

  @implementation MyObj
  @end

  ```


  (Clang-Tidy original name: clang-analyzer-osx.cocoa.UnusedIvars)

#### Tags
- /general/Static Analyzer - macOS\Cocoa API
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OSX_CCA_VMT
### Default
#### OriginalId=clang-analyzer-osx.cocoa.VariadicMethodTypes
#### Enabled=false
#### Warning=true
#### DisplayName=Variadic Method Types
#### HelpText
  Check for passing non-Objective-C types to variadic collection initialization methods that expect only Objective-C types.

  ``` cpp
  void test() {
    [NSSet setWithObjects:@"Foo", "Bar", nil];
      // warn: argument should be an ObjC pointer type, not 'char *'
  }

  ```


  (Clang-Tidy original name: clang-analyzer-osx.cocoa.VariadicMethodTypes)

#### Tags
- /general/Static Analyzer - macOS\Cocoa API
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OSX_CRF_CE
### Default
#### OriginalId=clang-analyzer-osx.coreFoundation.CFError
#### Enabled=false
#### Warning=true
#### DisplayName=CF Error
#### HelpText
  Check usage of CFErrorRef* parameters

  ``` cpp
  void test(CFErrorRef *error) {
    // warn: function accepting CFErrorRef* should have a
    // non-void return
  }

  int foo(CFErrorRef *error) {
    *error = 0; // warn: potential null dereference
    return 0;
  }

  ```


  (Clang-Tidy original name: clang-analyzer-osx.coreFoundation.CFError)

#### Tags
- /general/Static Analyzer - macOS\Core Foundation
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OSX_CRF_CN
### Default
#### OriginalId=clang-analyzer-osx.coreFoundation.CFNumber
#### Enabled=false
#### Warning=true
#### DisplayName=CF Number
#### HelpText
  Check for proper uses of CFNumber APIs.

  ``` cpp
  CFNumberRef test(unsigned char x) {
    return CFNumberCreate(0, kCFNumberSInt16Type, &x);
     // warn: 8 bit integer is used to initialize a 16 bit integer
  }

  ```


  (Clang-Tidy original name: clang-analyzer-osx.coreFoundation.CFNumber)

#### Tags
- /general/Static Analyzer - macOS\Core Foundation
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OSX_CRF_CRR
### Default
#### OriginalId=clang-analyzer-osx.coreFoundation.CFRetainRelease
#### Enabled=false
#### Warning=true
#### DisplayName=CF Retain Release
#### HelpText
  Check for null arguments to CFRetain/CFRelease/CFMakeCollectable.

  ``` cpp
  void test(CFTypeRef p) {
    if (!p)
      CFRetain(p); // warn
  }

  void test(int x, CFTypeRef p) {
    if (p)
      return;

    CFRelease(p); // warn
  }

  ```


  (Clang-Tidy original name: clang-analyzer-osx.coreFoundation.CFRetainRelease)

#### Tags
- /general/Static Analyzer - macOS\Core Foundation
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OSX_CRF_OOB
### Default
#### OriginalId=clang-analyzer-osx.coreFoundation.containers.OutOfBounds
#### Enabled=false
#### Warning=true
#### DisplayName=Out Of Bounds
#### HelpText
  Checks for index out-of-bounds when using ‘CFArray’ API.

  ``` cpp
  void test() {
    CFArrayRef A = CFArrayCreate(0, 0, 0, &kCFTypeArrayCallBacks);
    CFArrayGetValueAtIndex(A, 0); // warn
  }

  ```


  (Clang-Tidy original name: clang-analyzer-osx.coreFoundation.containers.OutOfBounds)

#### Tags
- /general/Static Analyzer - macOS\Core Foundation\Containers
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OSX_CRF_PSV
### Default
#### OriginalId=clang-analyzer-osx.coreFoundation.containers.PointerSizedValues
#### Enabled=false
#### Warning=true
#### DisplayName=Pointer Sized Values
#### HelpText
  Warns if ‘CFArray’, ‘CFDictionary’, ‘CFSet’ are created with non-pointer-size values.

  ``` cpp
  void test() {
    int x[] = { 1 };
    CFArrayRef A = CFArrayCreate(0, (const void """""""""""""""""""""""")x, 1,
                                 &kCFTypeArrayCallBacks); // warn
  }

  ```


  (Clang-Tidy original name: clang-analyzer-osx.coreFoundation.containers.PointerSizedValues)

#### Tags
- /general/Static Analyzer - macOS\Core Foundation\Containers
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OSX_MIGCC
### Default
#### OriginalId=clang-analyzer-osx.MIG
#### Enabled=false
#### Warning=true
#### DisplayName=Mach Interface Generator Calling Convention
#### Tags
- /general/Static Analyzer - macOS
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OSX_NOC
### Default
#### OriginalId=clang-analyzer-osx.NumberObjectConversion
#### Enabled=false
#### Warning=true
#### DisplayName=Number Object Conversion
#### HelpText
  Check for erroneous conversions of objects representing numbers into numbers.

  ``` cpp
  NSNumber *photoCount = [albumDescriptor objectForKey:@"PhotoCount"];
  // Warning: Comparing a pointer value of type 'NSNumber *'
  // to a scalar integer value
  if (photoCount > 0) {
    [self displayPhotos];
  }

  ```


  (Clang-Tidy original name: clang-analyzer-osx.NumberObjectConversion)

#### Tags
- /general/Static Analyzer - macOS
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OSX_NOCEDC
### Default
#### OriginalId=clang-analyzer-osx.NSOrCFErrorDerefChecker
#### Enabled=false
#### Warning=true
#### DisplayName=Ns Or CF Error Deref Checker
#### Tags
- /general/Static Analyzer - macOS
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OSX_OCP
### Default
#### OriginalId=clang-analyzer-osx.ObjCProperty
#### Enabled=false
#### Warning=true
#### DisplayName=Obj C Property
#### HelpText
  Check for proper uses of Objective-C properties.

  ``` cpp
  NSNumber *photoCount = [albumDescriptor objectForKey:@"PhotoCount"];
  // Warning: Comparing a pointer value of type 'NSNumber *'
  // to a scalar integer value
  if (photoCount > 0) {
    [self displayPhotos];
  }

  ```


  (Clang-Tidy original name: clang-analyzer-osx.ObjCProperty)

#### Tags
- /general/Static Analyzer - macOS
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OSX_ORC
### Default
#### OriginalId=clang-analyzer-osx.OSObjectRetainCount
#### Enabled=false
#### Warning=true
#### DisplayName=OSObject Retain Count
#### Tags
- /general/Static Analyzer - macOS
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_OSX_SKA
### Default
#### OriginalId=clang-analyzer-osx.SecKeychainAPI
#### Enabled=false
#### Warning=true
#### DisplayName=Sec Keychain API
#### HelpText
  Check for proper uses of Secure Keychain APIs.

  ``` cpp
  void test() {
    unsigned int *ptr = 0;
    UInt32 length;

    SecKeychainItemFreeContent(ptr, &length);
      // warn: trying to free data which has not been allocated
  }

  void test() {
    unsigned int *ptr = 0;
    UInt32 *length = 0;
    void *outData;

    OSStatus st =
      SecKeychainItemCopyContent(2, ptr, ptr, length, outData);
      // warn: data is not released
  }

  void test() {
    unsigned int *ptr = 0;
    UInt32 *length = 0;
    void *outData;

    OSStatus st =
      SecKeychainItemCopyContent(2, ptr, ptr, length, &outData);

    SecKeychainItemFreeContent(ptr, outData);
      // warn: only call free if a non-NULL buffer was returned
  }

  void test() {
    unsigned int *ptr = 0;
    UInt32 *length = 0;
    void *outData;

    OSStatus st =
      SecKeychainItemCopyContent(2, ptr, ptr, length, &outData);

    st = SecKeychainItemCopyContent(2, ptr, ptr, length, &outData);
      // warn: release data before another call to the allocator

    if (st == noErr)
      SecKeychainItemFreeContent(ptr, outData);
  }

  void test() {
    SecKeychainItemRef itemRef = 0;
    SecKeychainAttributeInfo *info = 0;
    SecItemClass *itemClass = 0;
    SecKeychainAttributeList *attrList = 0;
    UInt32 *length = 0;
    void *outData = 0;

    OSStatus st =
      SecKeychainItemCopyAttributesAndData(itemRef, info,
                                           itemClass, &attrList,
                                           length, &outData);

    SecKeychainItemFreeContent(attrList, outData);
      // warn: deallocator doesn't match the allocator
  }

  ```


  (Clang-Tidy original name: clang-analyzer-osx.SecKeychainAPI)

#### Tags
- /general/Static Analyzer - macOS
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_SEC_B
### Default
#### OriginalId=clang-analyzer-security.insecureAPI.bcmp
#### Enabled=true
#### Warning=true
#### DisplayName=bcmp
#### HelpText
  Warn on uses of the ‘bcmp’ function.

  ``` cpp
  void test() {
    bcmp(ptr0, ptr1, n); // warn
  }

  ```


  (Clang-Tidy original name: clang-analyzer-security.insecureAPI.bcmp)

#### Tags
- /general/Static Analyzer - Security\Insecure API
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_SEC_B2
### Default
#### OriginalId=clang-analyzer-security.insecureAPI.bcopy
#### Enabled=true
#### Warning=true
#### DisplayName=bcopy
#### HelpText
  Warn on uses of the ‘bcopy’ function.

  ``` cpp
  void test() {
    bcopy(src, dst, n); // warn
  }

  ```


  (Clang-Tidy original name: clang-analyzer-security.insecureAPI.bcopy)

#### Tags
- /general/Static Analyzer - Security\Insecure API
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_SEC_B3
### Default
#### OriginalId=clang-analyzer-security.insecureAPI.bzero
#### Enabled=true
#### Warning=true
#### DisplayName=bzero
#### HelpText
  Warn on uses of the ‘bzero’ function.

  ``` cpp
  void test() {
    bzero(ptr, n); // warn
  }

  ```


  (Clang-Tidy original name: clang-analyzer-security.insecureAPI.bzero)

#### Tags
- /general/Static Analyzer - Security\Insecure API
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_SEC_DOUBH
### Default
#### OriginalId=clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling
#### Enabled=true
#### Warning=true
#### DisplayName=Deprecated Or Unsafe Buffer Handling
#### HelpText
  Warn on occurrences of unsafe or deprecated buffer handling functions, which now have a secure variant: sprintf, vsprintf, scanf, wscanf, fscanf, fwscanf, vscanf, vwscanf, vfscanf, vfwscanf, sscanf, swscanf, vsscanf, vswscanf, swprintf, snprintf, vswprintf, vsnprintf, memcpy, memmove, strncpy, strncat, memset

  ``` cpp
  void test() {
    char buf [5];
    strncpy(buf, "a", 1); // warn
  }

  ```


  (Clang-Tidy original name: clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)

#### Tags
- /general/Static Analyzer - Security\Insecure API
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_SEC_DVOOT
### Default
#### OriginalId=clang-analyzer-security.insecureAPI.decodeValueOfObjCType
#### Enabled=true
#### Warning=true
#### DisplayName=decode Value Of ObjC Type
#### Tags
- /general/Static Analyzer - Security\Insecure API
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_SEC_FLC
### Default
#### OriginalId=clang-analyzer-security.FloatLoopCounter
#### Enabled=true
#### Warning=true
#### DisplayName=Float Loop Counter
#### HelpText
  Warn on using a floating point value as a loop counter (CERT: FLP30-C, FLP30-CPP).

  ``` cpp
  void test() {
    for (float x = 0.1f; x <= 1.0f; x += 0.1f) {} // warn
  }

  ```


  (Clang-Tidy original name: clang-analyzer-security.FloatLoopCounter)

#### Tags
- /general/Static Analyzer - Security
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_SEC_G
### Default
#### OriginalId=clang-analyzer-security.insecureAPI.getpw
#### Enabled=true
#### Warning=true
#### DisplayName=getpw
#### HelpText
  Warn on uses of the ‘getpw’ function.

  ``` cpp
  void test() {
    char buff[1024];
    getpw(2, buff); // warn
  }

  ```


  (Clang-Tidy original name: clang-analyzer-security.insecureAPI.getpw)

#### Tags
- /general/Static Analyzer - Security\Insecure API
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_SEC_G2
### Default
#### OriginalId=clang-analyzer-security.insecureAPI.gets
#### Enabled=true
#### Warning=true
#### DisplayName=gets
#### HelpText
  Warn on uses of the ‘gets’ function.

  ``` cpp
  void test() {
    char buff[1024];
    gets(buff); // warn
  }

  ```


  (Clang-Tidy original name: clang-analyzer-security.insecureAPI.gets)

#### Tags
- /general/Static Analyzer - Security\Insecure API
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_SEC_M
### Default
#### OriginalId=clang-analyzer-security.insecureAPI.mkstemp
#### Enabled=true
#### Warning=true
#### DisplayName=mkstemp
#### HelpText
  Warn when ‘mkstemp’ is passed fewer than 6 X’s in the format string.

  ``` cpp
  void test() {
    mkstemp("XX"); // warn
  }

  ```


  (Clang-Tidy original name: clang-analyzer-security.insecureAPI.mkstemp)

#### Tags
- /general/Static Analyzer - Security\Insecure API
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_SEC_M2
### Default
#### OriginalId=clang-analyzer-security.insecureAPI.mktemp
#### Enabled=true
#### Warning=true
#### DisplayName=mktemp
#### HelpText
  Warn on uses of the mktemp function.

  ``` cpp
  void test() {
    char *x = mktemp("/tmp/zxcv"); // warn: insecure, use mkstemp
  }

  ```


  (Clang-Tidy original name: clang-analyzer-security.insecureAPI.mktemp)

#### Tags
- /general/Static Analyzer - Security\Insecure API
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_SEC_R
### Default
#### OriginalId=clang-analyzer-security.insecureAPI.rand
#### Enabled=true
#### Warning=true
#### DisplayName=rand
#### HelpText
  Warn on uses of inferior random number generating functions (only if arc4random function is available): drand48, erand48, jrand48, lcong48, lrand48, mrand48, nrand48, random, rand_r.

  ``` cpp
  void test() {
    random(); // warn
  }

  ```


  (Clang-Tidy original name: clang-analyzer-security.insecureAPI.rand)

#### Tags
- /general/Static Analyzer - Security\Insecure API
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_SEC_S
### Default
#### OriginalId=clang-analyzer-security.insecureAPI.strcpy
#### Enabled=true
#### Warning=true
#### DisplayName=strcpy
#### HelpText
  Warn on uses of the strcpy and strcat functions.

  ``` cpp
  void test() {
    char x[4];
    char *y = "abcd";

    strcpy(x, y); // warn
  }

  ```


  (Clang-Tidy original name: clang-analyzer-security.insecureAPI.strcpy)

#### Tags
- /general/Static Analyzer - Security\Insecure API
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_SEC_SSC
### Default
#### OriginalId=clang-analyzer-security.insecureAPI.SecuritySyntaxChecker
#### Enabled=true
#### Warning=true
#### DisplayName=Security Syntax Checker
#### Tags
- /general/Static Analyzer - Security\Insecure API
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_SEC_UR
### Default
#### OriginalId=clang-analyzer-security.insecureAPI.UncheckedReturn
#### Enabled=true
#### Warning=true
#### DisplayName=Unchecked Return
#### HelpText
  Warn on uses of functions whose return values must be always checked.

  ``` cpp
  void test() {
    setuid(1); // warn
  }

  ```


  (Clang-Tidy original name: clang-analyzer-security.insecureAPI.UncheckedReturn)

#### Tags
- /general/Static Analyzer - Security\Insecure API
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_SEC_V
### Default
#### OriginalId=clang-analyzer-security.insecureAPI.vfork
#### Enabled=true
#### Warning=true
#### DisplayName=vfork
#### HelpText
  Warn on uses of the ‘vfork’ function.

  ``` cpp
  void test() {
    vfork(); // warn
  }

  ```


  (Clang-Tidy original name: clang-analyzer-security.insecureAPI.vfork)

#### Tags
- /general/Static Analyzer - Security\Insecure API
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_UIN_A
### Default
#### OriginalId=clang-analyzer-core.uninitialized.Assign
#### Enabled=true
#### Warning=true
#### DisplayName=Assign
#### HelpText
  Check for assigning uninitialized values.

  ``` cpp
  void test() {
    int x;
    x |= 1; // warn: left expression is uninitialized
  }

  ```


  (Clang-Tidy original name: clang-analyzer-core.uninitialized.Assign)

#### Tags
- /general/Static Analyzer - Core\Uninitialized
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_UIN_AS
### Default
#### OriginalId=clang-analyzer-core.uninitialized.ArraySubscript
#### Enabled=true
#### Warning=true
#### DisplayName=Array Subscript
#### HelpText
  Check for uninitialized values used as array subscripts.

  ``` cpp
  void test() {
    int i, a[10];
    int x = a[i]; // warn: array subscript is undefined
  }

  ```


  (Clang-Tidy original name: clang-analyzer-core.uninitialized.ArraySubscript)

#### Tags
- /general/Static Analyzer - Core\Uninitialized
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_UIN_B
### Default
#### OriginalId=clang-analyzer-core.uninitialized.Branch
#### Enabled=true
#### Warning=true
#### DisplayName=Branch
#### HelpText
  Check for uninitialized values used as branch conditions.

  ``` cpp
  void test() {
    int x;
    if (x) // warn
      return;
  }

  ```


  (Clang-Tidy original name: clang-analyzer-core.uninitialized.Branch)

#### Tags
- /general/Static Analyzer - Core\Uninitialized
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_UIN_CBV
### Default
#### OriginalId=clang-analyzer-core.uninitialized.CapturedBlockVariable
#### Enabled=true
#### Warning=true
#### DisplayName=Captured Block Variable
#### HelpText
  Check for blocks that capture uninitialized values.

  ``` cpp
  void test() {
    int x;
    ^{ int y = x; }(); // warn
  }

  ```


  (Clang-Tidy original name: clang-analyzer-core.uninitialized.CapturedBlockVariable)

#### Tags
- /general/Static Analyzer - Core\Uninitialized
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_UIN_UR
### Default
#### OriginalId=clang-analyzer-core.uninitialized.UndefReturn
#### Enabled=true
#### Warning=true
#### DisplayName=Undef Return
#### HelpText
  Check for uninitialized values being returned to the caller.

  ``` cpp
  int test() {
    int x;
    return x; // warn
  }

  ```


  (Clang-Tidy original name: clang-analyzer-core.uninitialized.UndefReturn)

#### Tags
- /general/Static Analyzer - Core\Uninitialized
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_UNX_A
### Default
#### OriginalId=clang-analyzer-unix.API
#### Enabled=true
#### Warning=true
#### DisplayName=API
#### HelpText
  Check calls to various UNIX/Posix functions: open, pthread_once, calloc, malloc, realloc, alloca.

  ``` cpp

  // Currently the check is performed for apple targets only.
  void test(const char *path) {
    int fd = open(path, O_CREAT);
      // warn: call to 'open' requires a third argument when the
      // 'O_CREAT' flag is set
  }

  void f();

  void test() {
    pthread_once_t pred = {0x30B1BCBA, {0}};
    pthread_once(&pred, f);
      // warn: call to 'pthread_once' uses the local variable
  }

  void test() {
    void *p = malloc(0); // warn: allocation size of 0 bytes
  }

  void test() {
    void *p = calloc(0, 42); // warn: allocation size of 0 bytes
  }

  void test() {
    void *p = malloc(1);
    p = realloc(p, 0); // warn: allocation size of 0 bytes
  }

  void test() {
    void *p = alloca(0); // warn: allocation size of 0 bytes
  }

  void test() {
    void *p = valloc(0); // warn: allocation size of 0 bytes
  }


  ```


  (Clang-Tidy original name: clang-analyzer-unix.API)

#### Tags
- /general/Static Analyzer - Unix
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_UNX_BSA
### Default
#### OriginalId=clang-analyzer-unix.cstring.BadSizeArg
#### Enabled=true
#### Warning=true
#### DisplayName=Bad Size Arg
#### HelpText
  Check the size argument passed into C string functions for common erroneous patterns. Use -Wno-strncat-size compiler option to mute other strncat-related compiler warnings.

  ``` cpp
  void test() {
    char dest[3];
    strncat(dest, """""""""""""""""""""""""*", sizeof(dest));
      // warn: potential buffer overflow
  }

  ```


  (Clang-Tidy original name: clang-analyzer-unix.cstring.BadSizeArg)

#### Tags
- /general/Static Analyzer - Unix\C string
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_UNX_M
### Default
#### OriginalId=clang-analyzer-unix.Malloc
#### Enabled=true
#### Warning=true
#### DisplayName=Malloc
#### HelpText
  Check for memory leaks, double free, and use-after-free problems. Traces memory managed by malloc()/free().

  ``` cpp

  void test() {
    int *p = malloc(1);
    free(p);
    free(p); // warn: attempt to free released memory
  }

  void test() {
    int *p = malloc(sizeof(int));
    free(p);
    *p = 1; // warn: use after free
  }

  void test() {
    int *p = malloc(1);
    if (p)
      return; // warn: memory is never released
  }

  void test() {
    int a[] = { 1 };
    free(a); // warn: argument is not allocated by malloc
  }

  void test() {
    int *p = malloc(sizeof(char));
    p = p - 1;
    free(p); // warn: argument to free() is offset by -4 bytes
  }


  ```


  (Clang-Tidy original name: clang-analyzer-unix.Malloc)

#### Tags
- /general/Static Analyzer - Unix
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_UNX_MD
### Default
#### OriginalId=clang-analyzer-unix.MismatchedDeallocator
#### Enabled=true
#### Warning=true
#### DisplayName=Mismatched Deallocator
#### HelpText
  Check for mismatched deallocators.

  ``` cpp
  // C, C++
  void test() {
    int *p = (int *)malloc(sizeof(int));
    delete p; // warn
  }

  // C, C++
  void __attribute((ownership_returns(malloc))) *user_malloc(size_t);

  void test() {
    int *p = (int *)user_malloc(sizeof(int));
    delete p; // warn
  }

  // C, C++
  void test() {
    int *p = new int;
    free(p); // warn
  }

  // C, C++
  void test() {
    int *p = new int[1];
    realloc(p, sizeof(long)); // warn
  }

  // C, C++
  template <typename T>
  struct SimpleSmartPointer {
    T *ptr;

    explicit SimpleSmartPointer(T *p = 0) : ptr(p) {}
    ~SimpleSmartPointer() {
      delete ptr; // warn
    }
  };

  void test() {
    SimpleSmartPointer<int> a((int *)malloc(4));
  }

  // C++
  void test() {
    int *p = (int *)operator new(0);
    delete[] p; // warn
  }

  // Objective-C, C++
  void test(NSUInteger dataLength) {
    int *p = new int;
    NSData *d = [NSData dataWithBytesNoCopy:p
                 length:sizeof(int) freeWhenDone:1];
      // warn +dataWithBytesNoCopy:length:freeWhenDone: cannot take
      // ownership of memory allocated by 'new'
  }


  ```


  (Clang-Tidy original name: clang-analyzer-unix.MismatchedDeallocator)

#### Tags
- /general/Static Analyzer - Unix
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_UNX_MS
### Default
#### OriginalId=clang-analyzer-unix.MallocSizeof
#### Enabled=true
#### Warning=true
#### DisplayName=Malloc Sizeof
#### HelpText
  Check for dubious malloc arguments involving sizeof.

  ``` cpp
  void test() {
    long *p = malloc(sizeof(short));
      // warn: result is converted to 'long *', which is
      // incompatible with operand type 'short'
    free(p);
  }

  ```


  (Clang-Tidy original name: clang-analyzer-unix.MallocSizeof)

#### Tags
- /general/Static Analyzer - Unix
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_UNX_NA
### Default
#### OriginalId=clang-analyzer-unix.cstring.NullArg
#### Enabled=true
#### Warning=true
#### DisplayName=Null Arg
#### HelpText
  Check for null pointers being passed as arguments to C string functions: strlen, strnlen, strcpy, strncpy, strcat, strncat, strcmp, strncmp, strcasecmp, strncasecmp.

  ``` cpp
  int test() {
    return strlen(0); // warn
  }

  ```


  (Clang-Tidy original name: clang-analyzer-unix.cstring.NullArg)

#### Tags
- /general/Static Analyzer - Unix\C string
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_UNX_V
### Default
#### OriginalId=clang-analyzer-unix.Vfork
#### Enabled=true
#### Warning=true
#### DisplayName=Vfork
#### HelpText
  Check for proper usage of vfork.

  ``` cpp
  int test(int x) {
    pid_t pid = vfork(); // warn
    if (pid != 0)
      return 0;

    switch (x) {
    case 0:
      pid = 1;
      execl("", "", 0);
      _exit(1);
      break;
    case 1:
      x = 0; // warn: this assignment is prohibited
      break;
    case 2:
      foo(); // warn: this function call is prohibited
      break;
    default:
      return 0; // warn: return is prohibited
    }

    while(1);
  }

  ```


  (Clang-Tidy original name: clang-analyzer-unix.Vfork)

#### Tags
- /general/Static Analyzer - Unix
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_VAL_CTS
### Default
#### OriginalId=clang-analyzer-valist.CopyToSelf
#### Enabled=true
#### Warning=true
#### DisplayName=Copy To Self
#### Tags
- /general/Static Analyzer - va_list
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_VAL_U
### Default
#### OriginalId=clang-analyzer-valist.Uninitialized
#### Enabled=true
#### Warning=true
#### DisplayName=Uninitialized
#### Tags
- /general/Static Analyzer - va_list
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_VAL_U2
### Default
#### OriginalId=clang-analyzer-valist.Unterminated
#### Enabled=true
#### Warning=true
#### DisplayName=Unterminated
#### Tags
- /general/Static Analyzer - va_list
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_VAL_VB
### Default
#### OriginalId=clang-analyzer-valist.ValistBase
#### Enabled=true
#### Warning=true
#### DisplayName=Valist Base
#### Tags
- /general/Static Analyzer - va_list
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_WBK_NUMC
### Default
#### OriginalId=clang-analyzer-webkit.NoUncountedMemberChecker
#### Enabled=false
#### Warning=true
#### DisplayName=No Uncounted Member Checker
#### HelpText
  Raw pointers and references to uncounted types can’t be used as class members. Only ref-counted types are allowed.

  ``` cpp
  struct RefCntbl {
    void ref() {}
    void deref() {}
  };

  struct Foo {
    RefCntbl * ptr; // warn
    RefCntbl & ptr; // warn
    // ...
  };

  ```


  (Clang-Tidy original name: clang-analyzer-webkit.NoUncountedMemberChecker)

#### Tags
- /general/Static Analyzer - Webkit
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_WBK_RCBVD
### Default
#### OriginalId=clang-analyzer-webkit.RefCntblBaseVirtualDtor
#### Enabled=false
#### Warning=true
#### DisplayName=Ref Cntbl Base Virtual Dtor
#### HelpText
  All uncounted types used as base classes must have a virtual destructor.

  Ref-counted types hold their ref-countable data by a raw pointer and allow implicit upcasting from ref-counted pointer to derived type to ref-counted pointer to base type. This might lead to an object of (dynamic) derived type being deleted via pointer to the base class type which C++ standard defines as UB in case the base class doesn’t have virtual destructor [expr.delete].

  ``` cpp
  struct RefCntblBase {
    void ref() {}
    void deref() {}
  };

  struct Derived : RefCntblBase { }; // warn

  ```


  (Clang-Tidy original name: clang-analyzer-webkit.RefCntblBaseVirtualDtor)

#### Tags
- /general/Static Analyzer - Webkit
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_SA_WBK_ULCC
### Default
#### OriginalId=clang-analyzer-webkit.UncountedLambdaCapturesChecker
#### Enabled=false
#### Warning=true
#### DisplayName=Uncounted Lambda Captures Checker
#### HelpText
  Raw pointers and references to uncounted types can’t be captured in lambdas. Only ref-counted types are allowed.

  ``` cpp
  struct RefCntbl {
    void ref() {}
    void deref() {}
  };

  void foo(RefCntbl* a, RefCntbl& b) {
    [&, a](){ // warn about 'a'
      do_something(b); // warn about 'b'
    };
  };

  ```


  (Clang-Tidy original name: clang-analyzer-webkit.UncountedLambdaCapturesChecker)

#### Tags
- /general/Static Analyzer - Webkit
- /tool/ClangTidy

#### Settings
- Priority=Major


## CT_ZRC_TO
### Default
#### OriginalId=zircon-temporary-objects
#### Enabled=false
#### Warning=true
#### DisplayName=Temporary Objects
#### HelpText
  Warns on construction of specific temporary objects in the Zircon kernel. If the object should be flagged, If the object should be flagged, the fully qualified type name must be explicitly passed to the check.

  For example, given the list of classes “Foo” and “NS::Bar”, all of the following will trigger the warning:

  ``` cpp
  Foo();
  Foo F = Foo();
  func(Foo());

  namespace NS {

  Bar();

  }

  ```


  With the same list, the following will not trigger the warning:

  ``` cpp
  Foo F;                 // Non-temporary construction okay
  Foo F(param);          // Non-temporary construction okay
  Foo *F = new Foo();    // New construction okay

  Bar();                 // Not NS::Bar, so okay
  NS::Bar B;             // Non-temporary construction okay

  ```


  Note that objects must be explicitly specified in order to be flagged, and so objects that inherit a specified object will not be flagged.

  This check matches temporary objects without regard for inheritance and so a prohibited base class type does not similarly prohibit derived class types.

  ``` cpp
  class Derived : Foo {} // Derived is not explicitly disallowed
  Derived();             // and so temporary construction is okay

  ```


  ##### Options

  Names     

  A semi-colon-separated list of fully-qualified names of C++ classes that should not be constructed as temporaries. Default is empty.

  (Clang-Tidy original name: zircon-temporary-objects)

#### Tags
- /general/Zircon
- /tool/ClangTidy

#### Settings
- Priority=Major
