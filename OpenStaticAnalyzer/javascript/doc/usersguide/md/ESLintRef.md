## Reference of ESLint coding rule violations

OpenStaticAnalyzer incorporates the [ESLint] tool for coding rule violation checking and imports its results. OpenStaticAnalyzer also associates the issued rule violations with source code elements (i.e. methods, classes, functions, and components), and calculates metrics for the source code elements, which represent the amount of violations of each ruleset, rule, and priority groups, respectively. 

OpenStaticAnalyzer uses ESLint "as is", without any guaranties that the results of ESLint are correct. All statements of the ESLint license apply here as well. All texts describing the rulesets and the individual rules are copied from its official home page with some minor grammatical fixes.

The list of rulesets and rules contained in each ruleset are the following:

- **Best Practices:** These are rules designed to prevent you from making mistakes. They either prescribe a better way of doing something or help you avoid footguns.

- **ECMAScript 6:** These rules are only relevant to ES6 environments.

- **Possible Errors:** These rules relate to possible syntax or logic errors in JavaScript code.

- **Stylistic Issues:** These rules are purely matters of style and are quite subjective.

- **Variables:** These rules have to do with variable declarations.

The following table contains the enabled rules and their priorities:

  Category          Name                      Abbreviation  Prio. 
  ----------------- ------------------------- ------------- ------
  Best Practices    eqeqeq                    ESLINT_E      Major 
                    no-case-declarations      ESLINT_NCD    Major 
                    no-empty-pattern          ESLINT_NEPA   Major 
                    no-fallthrough            ESLINT_NF     Major 
                    no-global-assign          ESLINT_NGA    Major 
                    no-iterator               ESLINT_NI     Major 
                    no-magic-numbers          ESLINT_NMN    Major 
                    no-new-wrappers           ESLINT_NNW    Major 
                    no-octal                  ESLINT_NO     Major 
                    no-redeclare              ESLINT_NR     Major 
                    no-self-assign            ESLINT_NSAS   Major 
                    no-unused-labels          ESLINT_NULA   Major 
                    no-useless-escape         ESLINT_NUES   Major 
  ECMAScript 6      constructor-super         ESLINT_CSU    Major 
                    no-class-assign           ESLINT_NCAS   Major 
                    no-const-assign           ESLINT_NCONS  Major 
                    no-dupe-class-members     ESLINT_NDCM   Major 
                    no-new-symbol             ESLINT_NNSY   Major 
                    no-this-before-super      ESLINT_NTBS   Major 
                    require-yield             ESLINT_RY     Major 
  Possible Errors   no-compare-neg-zero       ESLINT_NCNZ   Major 
                    no-cond-assign            ESLINT_NCA    Major 
                    no-console                ESLINT_NC     Major 
                    no-constant-condition     ESLINT_NCC    Major 
                    no-control-regex          ESLINT_NCR    Major 
                    no-debugger               ESLINT_ND     Major 
                    no-dupe-args              ESLINT_NDA    Major 
                    no-dupe-keys              ESLINT_NDK    Major 
                    no-duplicate-case         ESLINT_NDC    Major 
                    no-empty                  ESLINT_NE     Major 
                    no-empty-character-class  ESLINT_NECC   Major 
                    no-ex-assign              ESLINT_NEA    Major 
                    no-extra-boolean-cast     ESLINT_NEBC   Major 
                    no-extra-semi             ESLINT_NES    Major 
                    no-func-assign            ESLINT_NFA    Major 
                    no-inner-declarations     ESLINT_NID    Major 
                    no-invalid-regexp         ESLINT_NIR    Major 
                    no-irregular-whitespace   ESLINT_NIW    Major 
                    no-obj-calls              ESLINT_NOC    Major 
                    no-regex-spaces           ESLINT_NRS    Major 
                    no-sparse-arrays          ESLINT_NSA    Major 
                    no-unexpected-multiline   ESLINT_NUM    Major 
                    no-unreachable            ESLINT_NU     Major 
                    no-unsafe-finally         ESLINT_NUF    Major 
                    no-unsafe-negation        ESLINT_NUNEG  Major 
                    use-isnan                 ESLINT_UI     Major 
                    valid-typeof              ESLINT_VT     Major 
  Stylistic Issues  no-mixed-spaces-and-tabs  ESLINT_NMSAT  Major 
  Variables         no-delete-var             ESLINT_NDV    Major 
                    no-undef                  ESLINT_NUN    Major 
                    no-unused-vars            ESLINT_NUV    Major 

### Best Practices

#### eqeqeq {#ESLINT_E}
It is considered good practice to use the type-safe equality operators === and !== instead of their regular counterparts == and !=. The reason for this is that == and != do type coercion which follows the rather obscure Abstract Equality Comparison Algorithm. For instance, the following statements are all considered true: If one of those occurs in an innocent-looking statement such as a == b the actual problem is very difficult to spot.


#### no-case-declarations {#ESLINT_NCD}
This rule disallows lexical declarations (let, const, function and class) in case/default clauses. The reason is that the lexical declaration is visible in the entire switch block but it only gets initialized when it is assigned, which will only happen if the case where it is defined is reached. To ensure that the lexical declaration only applies to the current case clause wrap your clauses in blocks.


#### no-empty-pattern {#ESLINT_NEPA}
When using destructuring, it’s possible to create a pattern that has no effect. This happens when empty curly braces are used to the right of an embedded object destructuring pattern, such as: In this code, no new variables are created because a is just a location helper while the {} is expected to contain the variables to create, such as: In many cases, the empty object pattern is a mistake where the author intended to use a default value instead, such as: The difference between these two patterns is subtle, especially because the problematic empty pattern looks just like an object literal.


#### no-fallthrough {#ESLINT_NF}
The switch statement in JavaScript is one of the more error-prone constructs of the language thanks in part to the ability to “fall through” from one case to the next. For example: In this example, if foo is 1,then execution will flow through both cases, as the first falls through to the second. You can prevent this by using break, as in this example: That works fine when you don’t want a fallthrough, but what if the fallthrough is intentional, there is no way to indicate that in the language. It’s considered a best practice to always indicate when a fallthrough is intentional using a comment: In this example, there is no confusion as to the expected behavior. It is clear that the first case is meant to fall through to the second case.


#### no-global-assign {#ESLINT_NGA}
JavaScript environments contain a number of built-in global variables, such as window in browsers and process in Node.js. In almost all cases, you don’t want to assign a value to these global variables as doing so could result in losing access to important functionality. 


#### no-iterator {#ESLINT_NI}
The iterator property was a SpiderMonkey extension to JavaScript that could be used to create custom iterators that are compatible with JavaScript’s for in and for each constructs. However, this property is now obsolete, so it should not be used. Here’s an example of how this used to work: You should use ECMAScript 6 iterators and generators instead.


#### no-magic-numbers {#ESLINT_NMN}
‘Magic numbers’ are numbers that occur multiple time in code without an explicit meaning. They should preferably be replaced by named constants.


#### no-new-wrappers {#ESLINT_NNW}
There are three primitive types in JavaScript that have wrapper objects: string, number, and boolean. These are represented by the constructors String, Number, and Boolean, respectively. The primitive wrapper types are used whenever one of these primitive values is read, providing them with object-like capabilities such as methods. Behind the scenes, an object of the associated wrapper type is created and then destroyed, which is why you can call methods on primitive values, such as: Behind the scenes in this example, a String object is constructed. The substring() method exists on String.prototype and so is accessible to the string instance. It’s also possible to manually create a new wrapper instance: Although possible, there aren’t any good reasons to use these primitive wrappers as constructors. They tend to confuse other developers more than anything else because they seem like they should act as primitives, but they do not. For example: The first problem is that primitive wrapper objects are, in fact, objects. That means typeof will return “object” instead of “string”, “number”, or “boolean”. The second problem comes with boolean objects. Every object is truthy, that means an instance of Boolean always resolves to true even when its actual value is false. For these reasons, it’s considered a best practice to avoid using primitive wrapper types with new.


#### no-octal {#ESLINT_NO}
Octal literals are numerals that begin with a leading zero, such as: The leading zero to identify an octal literal has been a source of confusion and error in JavaScript. ECMAScript 5 deprecates the use of octal numeric literals in JavaScript and octal literals cause syntax errors in strict mode. It’s therefore recommended to avoid using octal literals in JavaScript code.


#### no-redeclare {#ESLINT_NR}
In JavaScript, it’s possible to redeclare the same variable name using var. This can lead to confusion as to where the variable is actually declared and initialized.


#### no-self-assign {#ESLINT_NSAS}
Self assignments have no effect, so probably those are an error due to incomplete refactoring. Those indicate that what you should do is still remaining.


#### no-unused-labels {#ESLINT_NULA}
The --fix option on the command line can automatically fix some of the problems reported by this rule. Labels that are declared and not used anywhere in the code are most likely an error due to incomplete refactoring.


#### no-useless-escape {#ESLINT_NUES}
Escaping non-special characters in strings, template literals, and regular expressions doesn’t have any effect, as demonstrated in the following example:


### ECMAScript 6

#### constructor-super {#ESLINT_CSU}
Constructors of derived classes must call super(). Constructors of non derived classes must not call super(). If this is not observed, the javascript engine will raise a runtime error. This rule checks whether or not there is a valid super() call.

#### no-class-assign {#ESLINT_NCAS}
ClassDeclaration creates a variable, and we can modify the variable. But the modification is a mistake in most cases.

#### no-const-assign {#ESLINT_NCONS}
We cannot modify variables that are declared using const keyword. It will raise a runtime error. Under non ES2015 environment, it might be ignored merely.

#### no-dupe-class-members {#ESLINT_NDCM}
If there are declarations of the same name in class members, the last declaration overwrites other declarations silently. It can cause unexpected behaviors.

#### no-new-symbol {#ESLINT_NNSY}
Using a single import statement per module will make the code clearer because you can see everything being imported from that module on one line. In the following example the module import on line 1 is repeated on line 3. These can be combined to make the list of imports more succinct.

#### no-this-before-super {#ESLINT_NTBS}
In the constructor of derived classes, if this/super are used before super() calls, it raises a reference error. This rule checks this/super keywords in constructors, then reports those that are before super().

#### require-yield {#ESLINT_RY}
This rule generates warnings for generator functions that do not have the yield keyword.

### Possible Errors

#### no-compare-neg-zero {#ESLINT_NCNZ}
The rule should warn against code that tries to compare against -0, since that will not work as intended. That is, code like x === -0 will pass for both +0 and -0. The author probably intended Object.is(x, -0).

#### no-cond-assign {#ESLINT_NCA}
In conditional statements, it is very easy to mistype a comparison operator (such as ==) as an assignment operator (such as =). For example: There are valid reasons to use assignment operators in conditional statements. However, it can be difficult to tell whether a specific assignment was intentional.


#### no-console {#ESLINT_NC}
In JavaScript that is designed to be executed in the browser, it’s considered a best practice to avoid using methods on console. Such messages are considered to be for debugging purposes and therefore not suitable to ship to the client. In general, calls using console should be stripped before being pushed to production.


#### no-constant-condition {#ESLINT_NCC}
Comparing a literal expression in a condition is usually a typo or development trigger for a specific behavior. This pattern is most likely an error and should be avoided.


#### no-control-regex {#ESLINT_NCR}
Control characters are special, invisible characters in the ASCII range 0-31. These characters are rarely used in JavaScript strings so a regular expression containing these characters is most likely a mistake.


#### no-debugger {#ESLINT_ND}
The debugger statement is used to tell the executing JavaScript environment to stop execution and start up a debugger at the current point in the code. This has fallen out of favor as a good practice with the advent of modern debugging and development tools. Production code should definitely not contain debugger, as it will cause the browser to stop executing code and open an appropriate debugger.


#### no-dupe-args {#ESLINT_NDA}
If more than one parameter has the same name in a function definition, the last occurrence “shadows” the preceding occurrences. A duplicated name might be a typing error.


#### no-dupe-keys {#ESLINT_NDK}
Multiple properties with the same key in object literals can cause unexpected behavior in your application.


#### no-duplicate-case {#ESLINT_NDC}
A switch statements with duplicate case labels is normally an indication of a programmer error. In the following example the 3rd case label uses again the literal 1 that has already been used in the first case label. Most likely the case block was copied from above and it was forgotten to change the literal.


#### no-empty {#ESLINT_NE}
Empty block statements, while not technically errors, usually occur due to refactoring that wasn’t completed. They can cause confusion when reading code.


#### no-empty-character-class {#ESLINT_NECC}
Empty character classes in regular expressions do not match anything and can result in code that may not work as intended.


#### no-ex-assign {#ESLINT_NEA}
If a catch clause in a try statement accidentally (or purposely) assigns another value to the exception parameter, it impossible to refer to the error from that point on. Since there is no arguments object to offer alternative access to this data, assignment of the parameter is absolutely destructive.


#### no-extra-boolean-cast {#ESLINT_NEBC}
In contexts such as an if statement’s test where the result of the expression will already be coerced to a Boolean, casting to a Boolean via double negation (!!) is unnecessary. For example, these if statements are equivalent:


#### no-extra-semi {#ESLINT_NES}
Typing mistakes and misunderstandings about where semicolons are required can lead to semicolons that are unnecessary. While not technically an error, extra semicolons can cause confusion when reading code.


#### no-func-assign {#ESLINT_NFA}
JavaScript functions can be written as a FunctionDeclaration function foo() { … } or as a FunctionExpression var foo = function() { … };. While a JavaScript interpreter might tolerate it, overwriting/reassigning a function written as a FunctionDeclaration is often indicative of a mistake or issue.


#### no-inner-declarations {#ESLINT_NID}
In JavaScript, prior to ES6, a function declaration is only allowed in the first level of a program or the body of another function, though parsers sometimes erroneously accept them elsewhere. This only applies to function declarations; named or anonymous function expressions can occur anywhere an expression is permitted. A variable declaration is permitted anywhere a statement can go, even nested deeply inside other blocks. This is often undesirable due to variable hoisting, and moving declarations to the root of the program or function body can increase clarity. Note that block bindings (let, const) are not hoisted and therefore they are not affected by this rule.


#### no-invalid-regexp {#ESLINT_NIR}
An invalid pattern in a regular expression literal is a SyntaxError when the code is parsed, but an invalid string in RegExp constructors throws a SyntaxError only when the code is executed.


#### no-irregular-whitespace {#ESLINT_NIW}
Invalid or irregular whitespace causes issues with ECMAScript 5 parsers and also makes code harder to debug in a similar nature to mixed tabs and spaces. Various whitespace characters can be inputted by programmers by mistake for example from copying or keyboard shortcuts. Pressing Alt + Space on OS X adds in a non breaking space character for example. Known issues these spaces cause:


#### no-obj-calls {#ESLINT_NOC}
ECMAScript provides several global objects that are intended to be used as-is. Some of these objects look as if they could be constructors due their capitalization (such as Math and JSON) but will throw an error if you try to execute them as functions. The ECMAScript 5 specification makes it clear that both Math and JSON cannot be invoked:


#### no-regex-spaces {#ESLINT_NRS}
Regular expressions can be very complex and difficult to understand, which is why it’s important to keep them as simple as possible in order to avoid mistakes. One of the more error-prone things you can do with a regular expression is to use more than one space, such as: In this regular expression, it’s very hard to tell how many spaces are intended to be matched. It’s better to use only one space and then specify how many spaces are expected, such as: Now it is very clear that three spaces are expected to be matched.


#### no-sparse-arrays {#ESLINT_NSA}
Sparse arrays contain empty slots, most frequently due to multiple commas being used in an array literal, such as: While the items array in this example has a length of 2, there are actually no values in items[0] or items[1]. The fact that the array literal is valid with only commas inside, coupled with the length being set and actual item values not being set, make sparse arrays confusing for many developers. Consider the following: In this example, the colors array has a length of 3. But did the developer intend for there to be an empty spot in the middle of the array? Or is it a typo? The confusion around sparse arrays defined in this manner is enough that it’s recommended to avoid using them unless you are certain that they are useful in your code.


#### no-unexpected-multiline {#ESLINT_NUM}
Semicolons are optional in JavaScript, via a process called automatic semicolon insertion (ASI). See the documentation for semi for a fuller discussion of that feature. The rules for ASI are relatively straightforward: In short, as once described by Isaac Schlueter, a character always ends a statement (just like a semicolon) unless one of the following is true: This particular rule aims to spot scenarios where a newline looks like it is ending a statement, but is not.


#### no-unreachable {#ESLINT_NU}
Because the return, throw, break, and continue statements unconditionally exit a block of code, any statements after them cannot be executed. Unreachable statements are usually a mistake.


#### no-unsafe-finally {#ESLINT_NUF}
JavaScript suspends the control flow statements of try and catch blocks until the execution of finally block finishes. So, when return, throw, break, or continue is used in finally, control flow statements inside try and catch are overwritten, which is considered as unexpected behavior.


#### no-unsafe-negation {#ESLINT_NUNEG}
Just as developers might type -a + b when they mean -(a + b) for the negative of a sum, they might type !key in object by mistake when they almost certainly mean !(key in object) to test that a key is not in an object. !obj instanceof Ctor is similar.


#### use-isnan {#ESLINT_UI}
In JavaScript, NaN is a special value of the Number type. It’s used to represent any of the “not-a-number” values represented by the double-precision 64-bit format as specified by the IEEE Standard for Binary Floating-Point Arithmetic. NaN has the unique property of not being equal to anything, including itself. That is to say, that the condition NaN !== NaN evaluates to true.


#### valid-typeof {#ESLINT_VT}
For a vast majority of use-cases, the only valid results of the typeof operator will be one of the following: “undefined”, “object”, “boolean”, “number”, “string”, and “function”. When the result of a typeof operation is compared against a string that is not one of these strings, it is usually a typo. This rule ensures that when the result of a typeof operation is compared against a string, that string is in the aforementioned set.


### Stylistic Issues

#### no-mixed-spaces-and-tabs {#ESLINT_NMSAT}
Most code conventions require either tabs or spaces be used for indentation. As such, it’s usually an error if a single line of code is indented with both tabs and spaces.


### Variables

#### no-delete-var {#ESLINT_NDV}
The purpose of the delete operator is to remove a property from an object. Using the delete operator on a variable might lead to unexpected behavior.


#### no-undef {#ESLINT_NUN}
This rule can help you locate potential ReferenceErrors resulting from misspellings of variable and parameter names, or accidental implicit globals (for example, from forgetting the var keyword in a for loop initializer).


#### no-unused-vars {#ESLINT_NUV}
Variables that are declared and not used anywhere in the code are most likely an error due to incomplete refactoring. Such variables take up space in the code and can lead to confusion by readers.


