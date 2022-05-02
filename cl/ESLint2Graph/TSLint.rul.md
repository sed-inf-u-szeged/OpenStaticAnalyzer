# ToolDescription
## Default
### ID=ESLINT
### Description


# Includes
- TSLint.rul_metadata.md

# Metrics
## ESLINT_ABN
### Default
#### OriginalId=array-bracket-newline
#### Enabled=false
#### Warning=true
#### DisplayName=array-bracket-newline
#### HelpText
  A number of style guides require or disallow line breaks inside of array brackets.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__={ "multiline": true, "minItems": 2 }


## ESLINT_ABS
### Default
#### OriginalId=array-bracket-spacing
#### Enabled=false
#### Warning=true
#### DisplayName=array-bracket-spacing
#### HelpText
  A number of style guides require or disallow spaces between array brackets and other tokens. This rule applies to both array literals and destructuring assignments (ECMAScript 6).


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="always"


## ESLINT_ABST
### Default
#### OriginalId=arrow-body-style
#### Enabled=false
#### Warning=true
#### DisplayName=arrow-body-style
#### HelpText
  Arrow functions can omit braces when there is a single statement in the body. This rule enforces the consistent use of braces in arrow functions. Additionally, this rule specifically warns against a possible developer error when the intention is to return an empty object literal but creates an empty block instead, returning undefined.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/ECMAScript 6

#### Settings
- Priority=Major
- __eslint_param__="as-needed"


## ESLINT_ACR
### Default
#### OriginalId=array-callback-return
#### Enabled=false
#### Warning=true
#### DisplayName=array-callback-return
#### HelpText
  Array has several methods for filtering, mapping, and folding. If we forget to write return statement in a callback of those, it’s probably a mistake.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major
- __eslint_param__={            "allowImplicit": false        }


## ESLINT_AEN
### Default
#### OriginalId=array-element-newline
#### Enabled=false
#### Warning=true
#### DisplayName=array-element-newline
#### HelpText
  A number of style guides require or disallow line breaks between array elements.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="always"


## ESLINT_AP
### Default
#### OriginalId=accessor-pairs
#### Enabled=false
#### Warning=true
#### DisplayName=accessor-pairs
#### HelpText
  It’s a common mistake in JavaScript to create an object with just a setter for a property but never have a corresponding getter defined for it. Without a getter, you cannot read the property, so it ends up not being used. Here are some examples: This rule warns if setters are defined without getters. Using an option getWithoutSet, it will warn if you have a getter without a setter also.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major
- __eslint_param__={            "setWithoutGet": true,			"getWithoutSet": false        }


## ESLINT_APA
### Default
#### OriginalId=arrow-parens
#### Enabled=false
#### Warning=true
#### DisplayName=arrow-parens
#### HelpText
  Arrow functions can omit parentheses when they have exactly one parameter. In all other cases the parameter(s) must be wrapped in parentheses. This rule enforces the consistent use of parentheses in arrow functions.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/ECMAScript 6

#### Settings
- Priority=Major
- __eslint_param__="always"


## ESLINT_AS
### Default
#### OriginalId=arrow-spacing
#### Enabled=false
#### Warning=true
#### DisplayName=arrow-spacing
#### HelpText
  This rule normalize style of spacing before/after an arrow function’s arrow(=&gt;). Fixable: This rule is automatically fixable using the –fix flag on the command line.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/ECMAScript 6

#### Settings
- Priority=Major
- __eslint_param__={"before": true, "after": true}


## ESLINT_JSBS
### Default
#### OriginalId=block-spacing
#### Enabled=false
#### Warning=true
#### DisplayName=block-spacing
#### HelpText
  This rule is for spacing style within single line blocks. Fixable: This rule is automatically fixable using the –fix flag on the command line.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="always"


## ESLINT_BST
### Default
#### OriginalId=brace-style
#### Enabled=false
#### Warning=true
#### DisplayName=brace-style
#### HelpText
  Brace style is closely related to indent style in programming and describes the placement of curly braces relative to their control statement and body. There are probably a dozen, if not more, brace styles in the world. The one true brace style is one of the most common brace styles in JavaScript, in which the opening curly brace of a block is placed on the same line as its corresponding statement or declaration. For example: One common variant of one true brace style is called Stroustrup, in which the else statements in an if-else construct, as well as catch and finally, must be on its own line after the preceding closing brace, as in this example: Another style is called Allman, in which all the braces are expected to be on their own lines without any extra indentation: While no style is considered better than the other, most developers agree that having a consistent style throughout a project is important for its long-term maintainability.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="1tbs"


## ESLINT_BSV
### Default
#### OriginalId=block-scoped-var
#### Enabled=false
#### Warning=true
#### DisplayName=block-scoped-var
#### HelpText
  The block-scoped-var rule generates warnings when variables are used outside of the block in which they were defined. This emulates C-style block scope.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_C
### Default
#### OriginalId=complexity
#### Enabled=false
#### Warning=true
#### DisplayName=complexity
#### HelpText
  Cyclomatic complexity measures the number of linearly independent paths through a program’s source code. This rule allows setting a cyclomatic complexity threshold.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major
- __eslint_param__={ "max": 2 }


## ESLINT_CA
### Default
#### OriginalId=camelcase
#### Enabled=false
#### Warning=true
#### DisplayName=camelcase
#### HelpText
  When it comes to naming variables, styleguides generally fall into one of two camps: camelcase (variableName) and underscores (variable\_name). This rule focuses on using the camelcase approach. If your styleguide calls for camelcasing your variable names, then this rule is for you!


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__={ "properties": "always" }


## ESLINT_CC
### Default
#### OriginalId=capitalized-comments
#### Enabled=false
#### Warning=true
#### DisplayName=capitalized-comments
#### HelpText
  Comments are useful for leaving information for future developers. In order for that information to be useful and not distracting, it is sometimes desirable for comments to follow a particular style. One element of comment formatting styles is whether the first word of a comment should be capitalized or lowercase. In general, no comment style is any more or less valid than any others, but many developers would agree that a consistent style can improve a project’s maintainability.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="always"


## ESLINT_JSCD
### Default
#### OriginalId=comma-dangle
#### Enabled=false
#### Warning=true
#### DisplayName=comma-dangle
#### HelpText
  Trailing commas in object literals are valid according to the ECMAScript 5 (and ECMAScript 3!) spec. However, IE8 (when not in IE8 document mode) and below will throw an error when it encounters trailing commas in JavaScript. On the other hand, trailing commas simplify adding and removing items to objects and arrays, since only the lines you are modifying must be touched.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Possible Errors

#### Settings
- Priority=Major
- __eslint_param__={                "arrays": "never",                "objects": "never",                "imports": "never",                "exports": "never",                "functions": "ignore"            }


## ESLINT_CMUT
### Default
#### OriginalId=class-methods-use-this
#### Enabled=false
#### Warning=true
#### DisplayName=class-methods-use-this
#### HelpText
  If a class method does not use this, it can sometimes be made into a static function. If you do convert the method into a static function, instances of the class that call that particular method have to be converted to a static call as well (MyClass.callStaticMethod())


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_CPS
### Default
#### OriginalId=computed-property-spacing
#### Enabled=false
#### Warning=true
#### DisplayName=computed-property-spacing
#### HelpText
  While formatting preferences are very personal, a number of style guides require or disallow spaces between computed properties in the following situations: Fixable: This rule is automatically fixable using the –fix flag on the command line.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="always"


## ESLINT_CR
### Default
#### OriginalId=consistent-return
#### Enabled=false
#### Warning=true
#### DisplayName=consistent-return
#### HelpText
  One of the confusing aspects of JavaScript is that any function may or may not return a value at any point in time. When a function exits without any return statement executing, the function returns undefined. Similarly, calling return without specifying any value will cause the function to return undefined. Only when return is called with a value is there a change in the function’s return value. Unlike statically-typed languages that will catch when a function doesn’t return the type of data expected, JavaScript has no such checks, meaning that it’s easy to make mistakes such as this: Here, one branch of the function returns true, a Boolean value, while the other exits without specifying any value (and so returns undefined). This may be an indicator of a coding error, especially if this pattern is found in larger functions.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major
- __eslint_param__={"treatUndefinedAsUnspecified": false}


## ESLINT_CRE
### Default
#### OriginalId=callback-return
#### Enabled=false
#### Warning=true
#### DisplayName=callback-return
#### HelpText
  The callback pattern is at the heart of most I/O and event-driven programming in JavaScript. To prevent calling the callback multiple times it is important to return anytime the callback is triggered outside of the main function body. Neglecting this technique often leads to issues where you do something more than once. For example, in the case of an HTTP request, you may try to send HTTP headers more than once leading node.js to throw a Can’t render headers after they are sent to the client. error.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Node.js and CommonJS

#### Settings
- Priority=Major


## ESLINT_CS
### Default
#### OriginalId=comma-spacing
#### Enabled=false
#### Warning=true
#### DisplayName=comma-spacing
#### HelpText
  Spacing around commas improve readability of a list of items. Although most of the style guidelines for languages prescribe adding a space after a comma and not before it, it is subjective to the preferences of a project.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__={            "before": false,            "after": true        }


## ESLINT_CST
### Default
#### OriginalId=comma-style
#### Enabled=false
#### Warning=true
#### DisplayName=comma-style
#### HelpText
  Comma Style rule enforces comma styles for a list of things separated by commas. There are two comma styles primarily in JavaScript. The standard one in which commas are placed at the end of the line. And Comma-First, in which, commas are placed at the start of the next line after the list item. One of the justifications for using Comma-First is that it helps tracking missing and trailing commas. In case linting is turned off, missing commas in variable declarations lead to leakage of global variables and trailing commas lead to errors in older versions of IE.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="last"


## ESLINT_CSU
### Default
#### OriginalId=constructor-super
#### Enabled=true
#### Warning=true
#### DisplayName=constructor-super
#### HelpText
  Constructors of derived classes must call super(). Constructors of non derived classes must not call super(). If this is not observed, the javascript engine will raise a runtime error. This rule checks whether or not there is a valid super() call.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/ECMAScript 6

#### Settings
- Priority=Major


## ESLINT_CT
### Default
#### OriginalId=consistent-this
#### Enabled=false
#### Warning=true
#### DisplayName=consistent-this
#### HelpText
  It is often necessary to capture the current execution context in order to make it available subsequently. A prominent example of this are jQuery callbacks: There are many commonly used aliases for this such as self, that or me. It is desirable to ensure that whichever alias the team agrees upon is used consistently throughout the application.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="that"


## ESLINT_CU
### Default
#### OriginalId=curly
#### Enabled=false
#### Warning=true
#### DisplayName=curly
#### HelpText
  JavaScript allows the omission of curly braces when a block contains only one statement. However, it is considered by many to be best practice to never omit curly braces around blocks, even when they are optional, because it can lead to bugs and reduces code clarity. So the following: Can be rewritten as: There are, however, some who prefer to only use braces when there is more than one statement to be executed.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major
- __eslint_param__="all"


## ESLINT_DC
### Default
#### OriginalId=default-case
#### Enabled=false
#### Warning=true
#### DisplayName=default-case
#### HelpText
  Some code conventions require that all switch statements have a default case, even if the default case is empty, such as: The thinking is that it’s better to always explicitly state what the default behavior should be so that it’s clear whether or not the developer forgot to include the default behavior by mistake. Other code conventions allow you to skip the default case so long as there is a comment indicating the omission is intentional, such as: Once again, the intent here is to show that the developer intended for there to be no default behavior.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major
- __eslint_param__={"commentPattern":"/^no default$/i"}


## ESLINT_DL
### Default
#### OriginalId=dot-location
#### Enabled=false
#### Warning=true
#### DisplayName=dot-location
#### HelpText
  JavaScript allows you to place newlines before or after a dot in a member expression. Consistency in placing a newline before or after the dot can greatly increase readability.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major
- __eslint_param__="object"


## ESLINT_JSDN
### Default
#### OriginalId=dot-notation
#### Enabled=false
#### Warning=true
#### DisplayName=dot-notation
#### HelpText
  In JavaScript, one can access properties using the dot notation (foo.bar) or square-bracket notation (foo\[“bar”\]). However, the dot notation is often preferred because it is easier to read, less verbose, and works better with aggressive JavaScript minimizers.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major
- __eslint_param__={                "allowKeywords": true            }


## ESLINT_E
### Default
#### OriginalId=eqeqeq
#### Enabled=true
#### Warning=true
#### DisplayName=eqeqeq
#### HelpText
  It is considered good practice to use the type-safe equality operators === and !== instead of their regular counterparts == and !=. The reason for this is that == and != do type coercion which follows the rather obscure Abstract Equality Comparison Algorithm. For instance, the following statements are all considered true: If one of those occurs in an innocent-looking statement such as a == b the actual problem is very difficult to spot.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major
- __eslint_param__="always"


## ESLINT_EL
### Default
#### OriginalId=eol-last
#### Enabled=false
#### Warning=true
#### DisplayName=eol-last
#### HelpText
  Trailing newlines in non-empty files are a common UNIX idiom. Benefits of trailing newlines include the ability to concatenate or append to files as well as output files to the terminal without interfering with shell prompts.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="always"


## ESLINT_JSFCS
### Default
#### OriginalId=func-call-spacing
#### Enabled=false
#### Warning=true
#### DisplayName=func-call-spacing
#### HelpText
  When calling a function, developers may insert optional whitespace between the function’s name and the parentheses that invoke it.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="never"


## ESLINT_FD
### Default
#### OriginalId=for-direction
#### Enabled=false
#### Warning=true
#### DisplayName=for-direction
#### HelpText
  A for loop with a stop condition that can never be reached, such as one with a counter that moves in the wrong direction, will run infinitely. While there are occasions when an infinite loop is intended, the convention is to construct such loops as while loops. More typically, an infinite for loop is a bug.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Possible Errors

#### Settings
- Priority=Major


## ESLINT_FN
### Default
#### OriginalId=func-names
#### Enabled=false
#### Warning=true
#### DisplayName=func-names
#### HelpText
  A pattern that’s becoming more common is to give function expressions names to aid in debugging, such as: Adding the second bar in the above example is optional. If you leave off the function name then when the function throws an exception you are likely to get something similar to anonymous function in the stack trace. If you provide the optional name for a function expression then you will get the name of the function expression in the stack trace.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="always"


## ESLINT_FNM
### Default
#### OriginalId=func-name-matching
#### Enabled=false
#### Warning=true
#### DisplayName=func-name-matching
#### HelpText
  This rule requires function names to match the name of the variable or property to which they are assigned. The rule will ignore property assignments where the property name is a literal that is not a valid identifier in the ECMAScript version specified in your configuration (default ES5).


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="always"


## ESLINT_FPN
### Default
#### OriginalId=function-paren-newline
#### Enabled=false
#### Warning=true
#### DisplayName=function-paren-newline
#### HelpText
  Many style guides require or disallow newlines inside of function parentheses.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="multiline"


## ESLINT_FS
### Default
#### OriginalId=func-style
#### Enabled=false
#### Warning=true
#### DisplayName=func-style
#### HelpText
  There are two ways of defining functions in JavaScript: function declarations and function expressions. Declarations have the function keyword first, followed by a name, followed by its arguments and the function body, such as: Equivalent function expressions begin with the var keyword, followed by a name, and then the function itself, such as: The primary difference between function declarations and function expressions is that declarations are hoisted to the top of the scope in which they are defined, which allows you to write code that uses the function before the declaration. For example: Although this code might seem like an error, it actually works fine because JavaScript engines hoist the function declarations to the top of the scope. That means this code is treated as if the declaration came before the invocation. For function expressions, you must define the function before it is used, otherwise it causes an error. Example: In this case, doSomething() is undefined at the time of invocation and so causes a runtime error. Due to these different behaviors, it is common to have guidelines as to which style of function should be used. There is really no correct or incorrect choice here, it is just a preference.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="expression"


## ESLINT_GFI
### Default
#### OriginalId=guard-for-in
#### Enabled=false
#### Warning=true
#### DisplayName=guard-for-in
#### HelpText
  Looping over objects with a for in loop will include properties that are inherited through the prototype chain. This behavior can lead to unexpected items in your for loop.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_GR
### Default
#### OriginalId=global-require
#### Enabled=false
#### Warning=true
#### DisplayName=global-require
#### HelpText
  In Node.js, module dependencies are included using the require() function, such as: While require() may be called anywhere in code, some style guide prescribe that it should be called only in the top-level scope of a module to make it easier to identify dependencies. For instance, it’s arguably harder to identify dependencies when they are deeply nested inside of functions and other statements: Since require() does a synchronous load, it can cause performance problems when used in other locations.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Node.js and CommonJS

#### Settings
- Priority=Major


## ESLINT_GRET
### Default
#### OriginalId=getter-return
#### Enabled=false
#### Warning=true
#### DisplayName=getter-return
#### HelpText
  The get syntax binds an object property to a function that will be called when that property is looked up. Note that every getter is expected to return a value. This rule enforces that a return statement is present in property getters.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Possible Errors

#### Settings
- Priority=Major
- __eslint_param__={ "allowImplicit": true }


## ESLINT_GSS
### Default
#### OriginalId=generator-star-spacing
#### Enabled=false
#### Warning=true
#### DisplayName=generator-star-spacing
#### HelpText
  Generators are a new type of function in ECMAScript 6 that can return multiple values over time. These special functions are indicated by placing an \* after the function keyword. Here is an example of a generator function: This is also valid: This is valid as well: To keep a sense of consistency when using generators this rule enforces a single position for the \*. Fixable: This rule is automatically fixable using the –fix flag on the command line.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/ECMAScript 6

#### Settings
- Priority=Major
- __eslint_param__={"before": true, "after": false}


## ESLINT_HCE
### Default
#### OriginalId=handle-callback-err
#### Enabled=false
#### Warning=true
#### DisplayName=handle-callback-err
#### HelpText
  In node, a common pattern for dealing with asynchronous behavior is called the callback pattern. This pattern expects an Error object or null as the first argument of the callback. Forgetting to handle these errors can lead to some really strange behavior in your application.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Node.js and CommonJS

#### Settings
- Priority=Major
- __eslint_param__="err"


## ESLINT_JSI
### Default
#### OriginalId=indent
#### Enabled=false
#### Warning=true
#### DisplayName=indent
#### HelpText
  There are several common guidelines which require specific indentation of nested blocks and statements.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__=2


## ESLINT_IAL
### Default
#### OriginalId=implicit-arrow-linebreak
#### Enabled=false
#### Warning=true
#### DisplayName=implicit-arrow-linebreak
#### HelpText
  An arrow function body can contain an implicit return as an expression instead of a block body. It can be useful to enforce a consistent location for the implicitly returned expression.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="beside"


## ESLINT_IB
### Default
#### OriginalId=id-blacklist
#### Enabled=false
#### Warning=true
#### DisplayName=id-blacklist
#### HelpText
  Bad names can lead to hard-to-decipher code. Generic names, such as data, don’t infer much about the code and the values it receives. This rule allows you to configure a blacklist of bad identifier names, that you don’t want to see in your code.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="data"


## ESLINT_JSID
### Default
#### OriginalId=init-declarations
#### Enabled=false
#### Warning=true
#### DisplayName=init-declarations
#### HelpText
  In JavaScript, variables can be assigned during declaration, or at any point afterwards using an assignment statement. For example, in the following code, foo is initialized during declaration, while bar is initialized later.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Variables

#### Settings
- Priority=Major
- __eslint_param__={ "ignoreForLoopInit": true }


## ESLINT_IL
### Default
#### OriginalId=id-length
#### Enabled=false
#### Warning=true
#### DisplayName=id-length
#### HelpText
  Very short identifier names like e, x, \_t or very long ones like hashGeneratorResultOutputContainerObject usually make the code harder to read and potentially less maintainable. To prevent this, one may enforce a minimum and/or maximum identifier length. (usually min 2-chars)


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__={                "min": 2,                "properties": "always"            }


## ESLINT_IM
### Default
#### OriginalId=id-match
#### Enabled=false
#### Warning=true
#### DisplayName=id-match
#### HelpText
  Naming things consistently in a project is an often underestimated aspect of code creation. When done right, it can save your team hours of unnecessary head scratching and misdirections. This rule allows you to precisely define and enforce the variables and function names on your team should use. No more limiting yourself to camelCase, snake\_case, PascalCase or oHungarianNotation. Id-match has all your needs covered!


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="^[a-z]+([A-Z][a-z]+)*$"


## ESLINT_JQ
### Default
#### OriginalId=jsx-quotes
#### Enabled=false
#### Warning=true
#### DisplayName=jsx-quotes
#### HelpText
  JSX attribute values can contain string literals, which are delimited with single or double quotes. Unlike string literals in JavaScript, string literals within JSX attributes can’t contain escaped quotes. If you want to have e.g. a double quote within a JSX attribute value, you have to use single quotes as string delimiter.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- preferDouble="prefer-double"


## ESLINT_JSKS
### Default
#### OriginalId=key-spacing
#### Enabled=false
#### Warning=true
#### DisplayName=key-spacing
#### HelpText
  This rule enforces spacing around the colon in object literal properties. It can verify each property individually, or it can ensure vertical alignment of groups of properties in an object literal.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__={                "beforeColon": false,                "afterColon": true,                "mode": "strict"            }


## ESLINT_KWS
### Default
#### OriginalId=keyword-spacing
#### Enabled=false
#### Warning=true
#### DisplayName=keyword-spacing
#### HelpText
  Keywords are syntax elements of JavaScript, such as function and if. These identifiers have special meaning to the language and so often appear in a different color in code editors. As an important part of the language, style guides often refer to the spacing that should be used around keywords. For example, you might have a style guide that says keywords should be always surrounded by spaces.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__={            "before": true,            "after": true,            "overrides":{}        }


## ESLINT_LAC
### Default
#### OriginalId=lines-around-comment
#### Enabled=false
#### Warning=true
#### DisplayName=lines-around-comment
#### HelpText
  Many style guides require empty lines before or after comments. The primary goal of these rules is to make the comments easier to read and improve readability of the code.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__={            "beforeBlockComment": true        }


## ESLINT_JSLBCM
### Default
#### OriginalId=lines-between-class-members
#### Enabled=false
#### Warning=true
#### DisplayName=lines-between-class-members
#### HelpText
  This rule improves readability by enforcing lines between class members. It will not check empty lines before the first member and after the last member, since that is already taken care of by padded-blocks.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="always"


## ESLINT_LCP
### Default
#### OriginalId=line-comment-position
#### Enabled=false
#### Warning=true
#### DisplayName=line-comment-position
#### HelpText
  Line comments can be positioned above or beside code. This rule helps teams maintain a consistent style.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__={ "position": "above" }


## ESLINT_LS
### Default
#### OriginalId=linebreak-style
#### Enabled=false
#### Warning=true
#### DisplayName=linebreak-style
#### HelpText
  When developing with a lot of people all having different editors, VCS applications and operating systems it may occur that different line endings are written by either of the mentioned (might especially happen when using the windows and mac versions of SourceTree together). The linebreaks (new lines) used in windows operating system are usually carriage returns (CR) followed by a line feed (LF) making it a carriage return line feed (CRLF) whereas Linux and Unix use a simple line feed (LF). The corresponding control sequences are “” (for LF) and “” for (CRLF). Many versioning systems (like git and subversion) can automatically ensure the correct ending. However to cover all contingencies you can activate this rule.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="unix"


## ESLINT_MCS
### Default
#### OriginalId=multiline-comment-style
#### Enabled=false
#### Warning=true
#### DisplayName=multiline-comment-style
#### HelpText
  Many style guides require a particular style for comments that span multiple lines. For example, some style guides prefer the use of a single block comment for multiline comments, whereas other style guides prefer consecutive line comments.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="starred-block"


## ESLINT_MD
### Default
#### OriginalId=max-depth
#### Enabled=false
#### Warning=true
#### DisplayName=max-depth
#### HelpText
  Many developers consider code difficult to read if blocks are nested beyond a certain depth.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__={ "max": 4 }


## ESLINT_ML
### Default
#### OriginalId=max-len
#### Enabled=false
#### Warning=true
#### DisplayName=max-len
#### HelpText
  Very long lines of code in any language can be difficult to read. In order to aid in readability and maintainability many coders have developed a convention to limit lines of code to X number of characters (traditionally 80 characters).


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__={                "code": 80,                "tabWidth": 4,                "comments": 65,                "ignoreComments": true,                "ignoreTrailingComments": true,                "ignoreUrls": true,                "ignoreStrings": true,                "ignoreTemplateLiterals": true,                "ignoreRegExpLiterals": true            }


## ESLINT_MLINES
### Default
#### OriginalId=max-lines
#### Enabled=false
#### Warning=true
#### DisplayName=max-lines
#### HelpText
  Some people consider large files a code smell. Large files tend to do a lot of things and can make it hard following what’s going. While there is not an objective maximum number of lines considered acceptable in a file, most people would agree it should not be in the thousands. Recommendations usually range from 100 to 500 lines.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__={                "max": 300,                "skipBlankLines": true,                "skipComments": true            }


## ESLINT_MNC
### Default
#### OriginalId=max-nested-callbacks
#### Enabled=false
#### Warning=true
#### DisplayName=max-nested-callbacks
#### HelpText
  Many JavaScript libraries use the callback pattern to manage asynchronous operations. A program of any complexity will most likely need to manage several asynchronous operations at various levels of concurrency. A common pitfall that is easy to fall into is nesting callbacks, which makes code more difficult to read the deeper the callbacks are nested.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__={ "max": 10 }


## ESLINT_MP
### Default
#### OriginalId=max-params
#### Enabled=false
#### Warning=true
#### DisplayName=max-params
#### HelpText
  Functions that take numerous parameters can be difficult to read and write because it requires the memorization of what each parameter is, its type, and the order they should appear in. As a result, many coders adhere to a convention that caps the number of parameters a function can take.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__={ "max": 3 }


## ESLINT_MS
### Default
#### OriginalId=max-statements
#### Enabled=false
#### Warning=true
#### DisplayName=max-statements
#### HelpText
  The max-statements rule allows you to specify the maximum number of statements allowed in a function.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__={ "max": 10 }


## ESLINT_MSPL
### Default
#### OriginalId=max-statements-per-line
#### Enabled=false
#### Warning=true
#### DisplayName=max-statements-per-line
#### HelpText
  A line of code containing too many statements can be difficult to read. Code is generally read from the top down, especially when scanning, so limiting the number of statements allowed on a single line can be very beneficial for readability and maintainability.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__={ "max": 1 }


## ESLINT_MT
### Default
#### OriginalId=multiline-ternary
#### Enabled=false
#### Warning=true
#### DisplayName=multiline-ternary
#### HelpText
  JavaScript allows operands of ternary expressions to be separated by newlines, which can improve the readability of your program.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="always"


## ESLINT_NA
### Default
#### OriginalId=no-alert
#### Enabled=false
#### Warning=true
#### DisplayName=no-alert
#### HelpText
  JavaScripts’ alert, confirm, and prompt functions are widely considered to be obtrusive as UI elements and should be replaced by a more appropriate custom UI implementation. Furthermore, alert is often used while debugging code, which should be removed before deployment to production.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_NAC
### Default
#### OriginalId=no-array-constructor
#### Enabled=false
#### Warning=true
#### DisplayName=no-array-constructor
#### HelpText
  Use of the Array constructor to construct a new array is generally discouraged in favour of array literal notation because of the single-argument pitfall and because the Array global may be redefined. The exception is when the Array constructor is used to intentionally create sparse arrays of a specified size by giving the constructor a single numeric argument.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major


## ESLINT_NAIL
### Default
#### OriginalId=no-await-in-loop
#### Enabled=false
#### Warning=true
#### DisplayName=no-await-in-loop
#### HelpText
  Performing an operation on each element of an iterable is a common task. However, performing an await as part of each operation is an indication that the program is not taking full advantage of the parallelization benefits of async/await.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Possible Errors

#### Settings
- Priority=Major


## ESLINT_NB
### Default
#### OriginalId=no-bitwise
#### Enabled=false
#### Warning=true
#### DisplayName=no-bitwise
#### HelpText
  The use of bitwise operators in JavaScript is very rare and often & or | is simply a mistyped && or ||, which will lead to unexpected behavior.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__={            "allow": ["~"],            "int32Hint": true            }


## ESLINT_NBC
### Default
#### OriginalId=no-buffer-constructor
#### Enabled=false
#### Warning=true
#### DisplayName=no-buffer-constructor
#### HelpText
  In Node.js, the behavior of the Buffer constructor is different depending on the type of its argument. Passing an argument from user input to Buffer() without validating its type can lead to security vulnerabilities such as remote memory disclosure and denial of service. As a result, the Buffer constructor has been deprecated and should not be used. Use the producer methods Buffer.from, Buffer.alloc, and Buffer.allocUnsafe instead.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Node.js and CommonJS

#### Settings
- Priority=Major
- __eslint_param__="err"


## ESLINT_JSNC
### Default
#### OriginalId=no-console
#### Enabled=true
#### Warning=true
#### DisplayName=no-console
#### HelpText
  In JavaScript that is designed to be executed in the browser, it’s considered a best practice to avoid using methods on console. Such messages are considered to be for debugging purposes and therefore not suitable to ship to the client. In general, calls using console should be stripped before being pushed to production.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Possible Errors

#### Settings
- Priority=Major
- __eslint_param__={ "allow": ["warn", "error"] }


## ESLINT_NCA
### Default
#### OriginalId=no-cond-assign
#### Enabled=true
#### Warning=true
#### DisplayName=no-cond-assign
#### HelpText
  In conditional statements, it is very easy to mistype a comparison operator (such as ==) as an assignment operator (such as =). For example: There are valid reasons to use assignment operators in conditional statements. However, it can be difficult to tell whether a specific assignment was intentional.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Possible Errors

#### Settings
- Priority=Major
- __eslint_param__="except-parens"


## ESLINT_NCAL
### Default
#### OriginalId=no-caller
#### Enabled=false
#### Warning=true
#### DisplayName=no-caller
#### HelpText
  The use of arguments.caller and arguments.callee make several code optimizations impossible. They have been deprecated in future versions of JavaScript and their use is forbidden in ECMAScript 5 while in strict mode.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_NCAP
### Default
#### OriginalId=new-cap
#### Enabled=false
#### Warning=true
#### DisplayName=new-cap
#### HelpText
  The new operator in JavaScript creates a new instance of a particular type of object. That type of object is represented by a constructor function. Since constructor functions are just regular functions, the only defining characteristic is that new is being used as part of the call. Native JavaScript functions begin with an uppercase letter to distinguish those functions that are to be used as constructors from functions that are not. Many style guides recommend following this pattern to more easily determine which functions are to be used as constructors.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__={                "newIsCap": true,                "capIsNew": true,                "properties": true            }


## ESLINT_NCAR
### Default
#### OriginalId=no-confusing-arrow
#### Enabled=false
#### Warning=true
#### DisplayName=no-confusing-arrow
#### HelpText
  Arrow functions (=&gt;) are similar in syntax to some comparison operators (&gt;, &lt;, &lt;=, and &gt;=). This rule warns against using the arrow function syntax in places where it could be confused with a comparison operator. Even if the arguments of the arrow function are wrapped with parens, this rule still warns about it unless allowParens is set to true.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/ECMAScript 6

#### Settings
- Priority=Major
- __eslint_param__={"allowParens": false}


## ESLINT_NCAS
### Default
#### OriginalId=no-class-assign
#### Enabled=true
#### Warning=true
#### DisplayName=no-class-assign
#### HelpText
  ClassDeclaration creates a variable, and we can modify the variable. But the modification is a mistake in most cases.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/ECMAScript 6

#### Settings
- Priority=Major


## ESLINT_NCC
### Default
#### OriginalId=no-constant-condition
#### Enabled=true
#### Warning=true
#### DisplayName=no-constant-condition
#### HelpText
  Comparing a literal expression in a condition is usually a typo or development trigger for a specific behavior. This pattern is most likely an error and should be avoided.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Possible Errors

#### Settings
- Priority=Major
- __eslint_param__={ "checkLoops": true }


## ESLINT_NCD
### Default
#### OriginalId=no-case-declarations
#### Enabled=true
#### Warning=true
#### DisplayName=no-case-declarations
#### HelpText
  This rule disallows lexical declarations (let, const, function and class) in case/default clauses. The reason is that the lexical declaration is visible in the entire switch block but it only gets initialized when it is assigned, which will only happen if the case where it is defined is reached. To ensure that the lexical declaration only applies to the current case clause wrap your clauses in blocks.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_NCNZ
### Default
#### OriginalId=no-compare-neg-zero
#### Enabled=true
#### Warning=true
#### DisplayName=no-compare-neg-zero
#### HelpText
  The rule should warn against code that tries to compare against -0, since that will not work as intended. That is, code like x === -0 will pass for both +0 and -0. The author probably intended Object.is(x, -0).


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Possible Errors

#### Settings
- Priority=Major


## ESLINT_NCO
### Default
#### OriginalId=no-continue
#### Enabled=false
#### Warning=true
#### DisplayName=no-continue
#### HelpText
  The continue statement terminates execution of the statements in the current iteration of the current or labeled loop, and continues execution of the loop with the next iteration. When used incorrectly it makes code less testable, less readable and less maintainable. Structured control flow statements such as if should be used instead.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major


## ESLINT_NCONS
### Default
#### OriginalId=no-const-assign
#### Enabled=true
#### Warning=true
#### DisplayName=no-const-assign
#### HelpText
  We cannot modify variables that are declared using const keyword. It will raise a runtime error. Under non ES2015 environment, it might be ignored merely.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/ECMAScript 6

#### Settings
- Priority=Major


## ESLINT_NCR
### Default
#### OriginalId=no-control-regex
#### Enabled=true
#### Warning=true
#### DisplayName=no-control-regex
#### HelpText
  Control characters are special, invisible characters in the ASCII range 0-31. These characters are rarely used in JavaScript strings so a regular expression containing these characters is most likely a mistake.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Possible Errors

#### Settings
- Priority=Major


## ESLINT_NCS
### Default
#### OriginalId=no-catch-shadow
#### Enabled=false
#### Warning=true
#### DisplayName=no-catch-shadow
#### HelpText
  In IE 8 and earlier, the catch clause parameter can overwrite the value of a variable in the outer scope, if that variable has the same name as the catch clause parameter.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Variables

#### Settings
- Priority=Major


## ESLINT_ND
### Default
#### OriginalId=no-debugger
#### Enabled=true
#### Warning=true
#### DisplayName=no-debugger
#### HelpText
  The debugger statement is used to tell the executing JavaScript environment to stop execution and start up a debugger at the current point in the code. This has fallen out of favor as a good practice with the advent of modern debugging and development tools. Production code should definitely not contain debugger, as it will cause the browser to stop executing code and open an appropriate debugger.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Possible Errors

#### Settings
- Priority=Major


## ESLINT_NDA
### Default
#### OriginalId=no-dupe-args
#### Enabled=true
#### Warning=true
#### DisplayName=no-dupe-args
#### HelpText
  If more than one parameter has the same name in a function definition, the last occurrence “shadows” the preceding occurrences. A duplicated name might be a typing error.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Possible Errors

#### Settings
- Priority=Major


## ESLINT_NDC
### Default
#### OriginalId=no-duplicate-case
#### Enabled=true
#### Warning=true
#### DisplayName=no-duplicate-case
#### HelpText
  A switch statements with duplicate case labels is normally an indication of a programmer error. In the following example the 3rd case label uses again the literal 1 that has already been used in the first case label. Most likely the case block was copied from above and it was forgotten to change the literal.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Possible Errors

#### Settings
- Priority=Major


## ESLINT_JSNDCM
### Default
#### OriginalId=no-dupe-class-members
#### Enabled=false
#### Warning=true
#### DisplayName=no-dupe-class-members
#### HelpText
  If there are declarations of the same name in class members, the last declaration overwrites other declarations silently. It can cause unexpected behaviors.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/ECMAScript 6

#### Settings
- Priority=Major


## ESLINT_NDIM
### Default
#### OriginalId=no-duplicate-imports
#### Enabled=false
#### Warning=true
#### DisplayName=no-duplicate-imports
#### HelpText
  Using a single import statement per module will make the code clearer because you can see everything being imported from that module on one line. In the following example the module import on line 1 is repeated on line 3. These can be combined to make the list of imports more succinct.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/ECMAScript 6

#### Settings
- Priority=Major
- __eslint_param__={"includeExports": false}


## ESLINT_NDK
### Default
#### OriginalId=no-dupe-keys
#### Enabled=true
#### Warning=true
#### DisplayName=no-dupe-keys
#### HelpText
  Multiple properties with the same key in object literals can cause unexpected behavior in your application.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Possible Errors

#### Settings
- Priority=Major


## ESLINT_NDR
### Default
#### OriginalId=no-div-regex
#### Enabled=false
#### Warning=true
#### DisplayName=no-div-regex
#### HelpText
  Require regex literals to escape division operators.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_NDV
### Default
#### OriginalId=no-delete-var
#### Enabled=true
#### Warning=true
#### DisplayName=no-delete-var
#### HelpText
  The purpose of the delete operator is to remove a property from an object. Using the delete operator on a variable might lead to unexpected behavior.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Variables

#### Settings
- Priority=Major


## ESLINT_NE
### Default
#### OriginalId=no-empty
#### Enabled=true
#### Warning=true
#### DisplayName=no-empty
#### HelpText
  Empty block statements, while not technically errors, usually occur due to refactoring that wasn’t completed. They can cause confusion when reading code.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Possible Errors

#### Settings
- Priority=Major
- __eslint_param__={ "allowEmptyCatch": true }


## ESLINT_JSNEA
### Default
#### OriginalId=no-ex-assign
#### Enabled=true
#### Warning=true
#### DisplayName=no-ex-assign
#### HelpText
  If a catch clause in a try statement accidentally (or purposely) assigns another value to the exception parameter, it impossible to refer to the error from that point on. Since there is no arguments object to offer alternative access to this data, assignment of the parameter is absolutely destructive.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Possible Errors

#### Settings
- Priority=Major


## ESLINT_NEB
### Default
#### OriginalId=no-extra-bind
#### Enabled=false
#### Warning=true
#### DisplayName=no-extra-bind
#### HelpText
  The bind() method is used to create functions with specific this values and, optionally, binds arguments to specific values. When used to specify the value of this, it’s important that the function actually use this in its function body. For example: This code is an example of a good use of bind() for setting the value of this. Sometimes during the course of code maintenance, the this value is removed from the function body. In that case, you can end up with a call to bind() that doesn’t accomplish anything: In this code, the reference to this has been removed but bind() is still used. In this case, the bind() is unnecessary overhead (and a performance hit) and can be safely removed.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_NEBC
### Default
#### OriginalId=no-extra-boolean-cast
#### Enabled=true
#### Warning=true
#### DisplayName=no-extra-boolean-cast
#### HelpText
  In contexts such as an if statement’s test where the result of the expression will already be coerced to a Boolean, casting to a Boolean via double negation (!!) is unnecessary. For example, these if statements are equivalent:


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Possible Errors

#### Settings
- Priority=Major


## ESLINT_NECC
### Default
#### OriginalId=no-empty-character-class
#### Enabled=true
#### Warning=true
#### DisplayName=no-empty-character-class
#### HelpText
  Empty character classes in regular expressions do not match anything and can result in code that may not work as intended.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Possible Errors

#### Settings
- Priority=Major


## ESLINT_JSNEF
### Default
#### OriginalId=no-empty-function
#### Enabled=false
#### Warning=true
#### DisplayName=no-empty-function
#### HelpText
  Empty functions can reduce readability because readers need to guess whether it’s intentional or not. So writing a clear comment for empty functions is a good practice.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major
- __eslint_param__={"allow": []}


## ESLINT_NELA
### Default
#### OriginalId=no-extra-label
#### Enabled=false
#### Warning=true
#### DisplayName=no-extra-label
#### HelpText
  The --fix option on the command line can automatically fix some of the problems reported by this rule.If a loop contains no nested loops or switches, labeling the loop is unnecessary.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_NEN
### Default
#### OriginalId=no-eq-null
#### Enabled=false
#### Warning=true
#### DisplayName=no-eq-null
#### HelpText
  Comparing to null without a type-checking operator (== or !=), can have unintended results as the comparison will evaluate to true when comparing to not just a null, but also an undefined value.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_NENA
### Default
#### OriginalId=no-extend-native
#### Enabled=false
#### Warning=true
#### DisplayName=no-extend-native
#### HelpText
  In JavaScript, you can extend any object, including builtin or “native” objects. Sometimes people change the behavior of these native objects in ways that break the assumptions made about them in other parts of the code. For example here we are overriding a builtin method that will then affect all Objects, even other builtins. A common suggestion to avoid this problem would be to wrap the inside of the for loop with users.hasOwnProperty(id). However, if this rule is strictly enforced throughout your codebase you won’t need to take that step.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major
- __eslint_param__={"exceptions": []}


## ESLINT_JSNEP
### Default
#### OriginalId=no-extra-parens
#### Enabled=false
#### Warning=true
#### DisplayName=no-extra-parens
#### HelpText
  This rule restricts the use of parentheses to only where they are necessary. It may be restricted to report only function expressions.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Possible Errors

#### Settings
- Priority=Major
- __eslint_param__="all"


## ESLINT_NEPA
### Default
#### OriginalId=no-empty-pattern
#### Enabled=true
#### Warning=true
#### DisplayName=no-empty-pattern
#### HelpText
  When using destructuring, it’s possible to create a pattern that has no effect. This happens when empty curly braces are used to the right of an embedded object destructuring pattern, such as: In this code, no new variables are created because a is just a location helper while the {} is expected to contain the variables to create, such as: In many cases, the empty object pattern is a mistake where the author intended to use a default value instead, such as: The difference between these two patterns is subtle, especially because the problematic empty pattern looks just like an object literal.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_NER
### Default
#### OriginalId=no-else-return
#### Enabled=false
#### Warning=true
#### DisplayName=no-else-return
#### HelpText
  If an if block contains a return statement, the else block becomes unnecessary. Its contents can be placed outside of the block.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major
- __eslint_param__={"allowElseIf": true}


## ESLINT_JSNES
### Default
#### OriginalId=no-extra-semi
#### Enabled=false
#### Warning=true
#### DisplayName=no-extra-semi
#### HelpText
  Typing mistakes and misunderstandings about where semicolons are required can lead to semicolons that are unnecessary. While not technically an error, extra semicolons can cause confusion when reading code.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Possible Errors

#### Settings
- Priority=Major


## ESLINT_NEV
### Default
#### OriginalId=no-eval
#### Enabled=false
#### Warning=true
#### DisplayName=no-eval
#### HelpText
  JavaScript’s eval() function is potentially dangerous and is often misused. Using eval() on untrusted code can open a program up to several different injection attacks. The use of eval() in most contexts can be substituted for a better, alternative approach to a problem.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major
- __eslint_param__={"allowIndirect": true}


## ESLINT_NF
### Default
#### OriginalId=no-fallthrough
#### Enabled=true
#### Warning=true
#### DisplayName=no-fallthrough
#### HelpText
  The switch statement in JavaScript is one of the more error-prone constructs of the language thanks in part to the ability to “fall through” from one case to the next. For example: In this example, if foo is 1,then execution will flow through both cases, as the first falls through to the second. You can prevent this by using break, as in this example: That works fine when you don’t want a fallthrough, but what if the fallthrough is intentional, there is no way to indicate that in the language. It’s considered a best practice to always indicate when a fallthrough is intentional using a comment: In this example, there is no confusion as to the expected behavior. It is clear that the first case is meant to fall through to the second case.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major
- __eslint_param__={ "commentPattern": "break[\\s\\w]*omitted" }


## ESLINT_NFA
### Default
#### OriginalId=no-func-assign
#### Enabled=true
#### Warning=true
#### DisplayName=no-func-assign
#### HelpText
  JavaScript functions can be written as a FunctionDeclaration function foo() { … } or as a FunctionExpression var foo = function() { … };. While a JavaScript interpreter might tolerate it, overwriting/reassigning a function written as a FunctionDeclaration is often indicative of a mistake or issue.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Possible Errors

#### Settings
- Priority=Major


## ESLINT_NFD
### Default
#### OriginalId=no-floating-decimal
#### Enabled=false
#### Warning=true
#### DisplayName=no-floating-decimal
#### HelpText
  Float values in JavaScript contain a decimal point, and there is no requirement that the decimal point be preceded or followed by a number. For example, the following are all valid JavaScript numbers: Although not a syntax error, this format for numbers can make it difficult to distinguish between true decimal numbers and the dot operator. For this reason, some recommend that you should always include a number before and after a decimal point to make it clear the intent is to create a decimal number.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_NGA
### Default
#### OriginalId=no-global-assign
#### Enabled=true
#### Warning=true
#### DisplayName=no-global-assign
#### HelpText
  JavaScript environments contain a number of built-in global variables, such as window in browsers and process in Node.js. In almost all cases, you don’t want to assign a value to these global variables as doing so could result in losing access to important functionality.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major
- __eslint_param__={ "exceptions": ["Object"] }


## ESLINT_NI
### Default
#### OriginalId=no-iterator
#### Enabled=true
#### Warning=true
#### DisplayName=no-iterator
#### HelpText
  The **iterator** property was a SpiderMonkey extension to JavaScript that could be used to create custom iterators that are compatible with JavaScript’s for in and for each constructs. However, this property is now obsolete, so it should not be used. Here’s an example of how this used to work: You should use ECMAScript 6 iterators and generators instead.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_NIC
### Default
#### OriginalId=no-implicit-coercion
#### Enabled=false
#### Warning=true
#### DisplayName=no-implicit-coercion
#### HelpText
  In JavaScript, there are a lot of different ways to convert value types. Some of them might be hard to read and understand. Such as: Those can be replaced with the following code:


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major
- __eslint_param__={			"boolean": true,			"number": true,			"string": true,			"allow": []		}


## ESLINT_NICO
### Default
#### OriginalId=no-inline-comments
#### Enabled=false
#### Warning=true
#### DisplayName=no-inline-comments
#### HelpText
  Some style guides disallow a comments on the same line as code. If there are comments immediately following code, it can make it harder to read the code. On the other hand, it is sometimes faster and more obvious to put comments immediately following code.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major


## ESLINT_NID
### Default
#### OriginalId=no-inner-declarations
#### Enabled=true
#### Warning=true
#### DisplayName=no-inner-declarations
#### HelpText
  In JavaScript, prior to ES6, a function declaration is only allowed in the first level of a program or the body of another function, though parsers sometimes erroneously accept them elsewhere. This only applies to function declarations; named or anonymous function expressions can occur anywhere an expression is permitted. A variable declaration is permitted anywhere a statement can go, even nested deeply inside other blocks. This is often undesirable due to variable hoisting, and moving declarations to the root of the program or function body can increase clarity. Note that block bindings (let, const) are not hoisted and therefore they are not affected by this rule.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Possible Errors

#### Settings
- Priority=Major
- __eslint_param__="functions"


## ESLINT_JSNIE
### Default
#### OriginalId=no-implied-eval
#### Enabled=false
#### Warning=true
#### DisplayName=no-implied-eval
#### HelpText
  It’s considered a good practice to avoid using eval() in JavaScript. There are security and performance implications involved with doing so, which is why many linters (including ESLint) recommend disallowing eval(). However, there are some other ways to pass a string and have it interpreted as JavaScript code that have similar concerns. The first is using setTimeout(), setInterval() or execScript() (Internet Explorer only), both of which can accept a string of JavaScript code as their first argument. For example: This is considered an implied eval() because a string of JavaScript code is passed in to be interpreted. The same can be done with setInterval() and execScript(). Both interpret the JavaScript code in the global scope. For both setTimeout() and setInterval(), the first argument can also be a function, and that is considered safer and is more performant: The best practice is to always use a function for the first argument of setTimeout() and setInterval() (and avoid execScript()).


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_NIG
### Default
#### OriginalId=no-implicit-globals
#### Enabled=false
#### Warning=true
#### DisplayName=no-implicit-globals
#### HelpText
  When working with browser scripts, developers often forget that variable and function declarations at the top-level scope become global variables on the window object. As opposed to modules which have their own scope. Globals should be explicitly assigned to window or self if that is the intent. Otherwise variables intended to be local to the script should be wrapped in an IIFE.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_NIR
### Default
#### OriginalId=no-invalid-regexp
#### Enabled=true
#### Warning=true
#### DisplayName=no-invalid-regexp
#### HelpText
  An invalid pattern in a regular expression literal is a SyntaxError when the code is parsed, but an invalid string in RegExp constructors throws a SyntaxError only when the code is executed.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Possible Errors

#### Settings
- Priority=Major
- __eslint_param__={ "allowConstructorFlags": ["u", "y"] }


## ESLINT_JSNIT
### Default
#### OriginalId=no-invalid-this
#### Enabled=false
#### Warning=true
#### DisplayName=no-invalid-this
#### HelpText
  Under the strict mode, this keywords outside of classes or class-like objects might be undefined and raise a TypeError.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_NIW
### Default
#### OriginalId=no-irregular-whitespace
#### Enabled=true
#### Warning=true
#### DisplayName=no-irregular-whitespace
#### HelpText
  Invalid or irregular whitespace causes issues with ECMAScript 5 parsers and also makes code harder to debug in a similar nature to mixed tabs and spaces. Various whitespace characters can be inputted by programmers by mistake for example from copying or keyboard shortcuts. Pressing Alt + Space on OS X adds in a non breaking space character for example. Known issues these spaces cause:


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Possible Errors

#### Settings
- Priority=Major
- __eslint_param__={ "skipStrings": true }


## ESLINT_NL
### Default
#### OriginalId=no-labels
#### Enabled=false
#### Warning=true
#### DisplayName=no-labels
#### HelpText
  Labeled statements in JavaScript are used in conjunction with break and continue to control flow around multiple loops. For example: The break outer statement ensures that this code will not result in an infinite loop because control is returned to the next statement after the outer label was applied. If this statement was changed to be just break, control would flow back to the outer while statement and an infinite loop would result. While convenient in some cases, labels tend to be used only rarely and are frowned upon by some as a remedial form of flow control that is more error prone and harder to understand.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major
- __eslint_param__={"allowLoop": false, "allowSwitch": false}


## ESLINT_NLB
### Default
#### OriginalId=no-lone-blocks
#### Enabled=false
#### Warning=true
#### DisplayName=no-lone-blocks
#### HelpText
  In JavaScript, prior to ES6, standalone code blocks delimited by curly braces do not create a new scope and have no use. For example, these curly braces do nothing to foo: In ES6, code blocks may create a new scope if a block-level binding (let and const), a class declaration or a function declaration (in strict mode) are present. A block is not considered redundant in these cases.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_JSNLF
### Default
#### OriginalId=no-loop-func
#### Enabled=false
#### Warning=true
#### DisplayName=no-loop-func
#### HelpText
  Writing functions within loops tends to result in errors due to the way the function creates a closure around the loop. For example: In this case, you would expect each function created within the loop to return a different number. In reality, each function returns 10, because that was the last value of i in the scope. let or const mitigate this problem. In this case, each function created within the loop returns a different number as expected.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_NLI
### Default
#### OriginalId=no-lonely-if
#### Enabled=false
#### Warning=true
#### DisplayName=no-lonely-if
#### HelpText
  If an if statement is the only statement in the else block of a parent if statement, it is often clearer to combine the two to using else if form. should be rewritten as


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major


## ESLINT_NLV
### Default
#### OriginalId=no-label-var
#### Enabled=false
#### Warning=true
#### DisplayName=no-label-var
#### HelpText
  This rule aims to create clearer code by disallowing the bad practice of creating a label that shares a name with a variable that is in scope.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Variables

#### Settings
- Priority=Major


## ESLINT_NMA
### Default
#### OriginalId=no-multi-assign
#### Enabled=false
#### Warning=true
#### DisplayName=no-multi-assign
#### HelpText
  Chaining the assignment of variables can lead to unexpected results and be difficult to read.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major


## ESLINT_NMEL
### Default
#### OriginalId=no-multiple-empty-lines
#### Enabled=false
#### Warning=true
#### DisplayName=no-multiple-empty-lines
#### HelpText
  Some developers prefer to have multiple blank lines removed, while others feel that it helps improve readability. Whitespace is useful for separating logical sections of code, but excess whitespace takes up more of the screen.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__={ "max": 1 }


## ESLINT_JSNMN
### Default
#### OriginalId=no-magic-numbers
#### Enabled=false
#### Warning=true
#### DisplayName=no-magic-numbers
#### HelpText
  ‘Magic numbers’ are numbers that occur multiple time in code without an explicit meaning. They should preferably be replaced by named constants.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major
- __eslint_param__={			"ignore": [],			"ignoreArrayIndexes": false,			"enforceConst": false,			"detectObjects": false		}


## ESLINT_NMO
### Default
#### OriginalId=no-mixed-operators
#### Enabled=false
#### Warning=true
#### DisplayName=no-mixed-operators
#### HelpText
  Enclosing complex expressions by parentheses clarifies the developer’s intention, which makes the code more readable. This rule warns when different operators are used consecutively without parentheses in an expression.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__={            "groups": [                ["+", "-", "*", "/", "%", "**"],                ["&", "|", "^", "~", "<<", ">>", ">>>"],                ["==", "!=", "===", "!==", ">", ">=", "<", "<="],                ["&&", "||"],                ["in", "instanceof"]            ],            "allowSamePrecedence": true        }


## ESLINT_NMR
### Default
#### OriginalId=no-mixed-requires
#### Enabled=false
#### Warning=true
#### DisplayName=no-mixed-requires
#### HelpText
  In the Node.JS community it is often customary to separate the required modules from other variable declarations, sometimes also grouping them by their type. This rule helps you enforce this convention.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Node.js and CommonJS

#### Settings
- Priority=Major
- __eslint_param__={ "grouping": false, "allowCall": false }


## ESLINT_NMS
### Default
#### OriginalId=no-multi-spaces
#### Enabled=false
#### Warning=true
#### DisplayName=no-multi-spaces
#### HelpText
  Multiple spaces in a row that are not used for indentation are typically mistakes. For example: It’s hard to tell, but there are two spaces between foo and ===. Multiple spaces such as this are generally frowned upon in favor of single spaces: Fixable: This rule is automatically fixable using the –fix flag on the command line.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major
- __eslint_param__={			"ignoreEOLComments": false,			"exceptions": {}		}


## ESLINT_NMSAT
### Default
#### OriginalId=no-mixed-spaces-and-tabs
#### Enabled=true
#### Warning=true
#### DisplayName=no-mixed-spaces-and-tabs
#### HelpText
  Most code conventions require either tabs or spaces be used for indentation. As such, it’s usually an error if a single line of code is indented with both tabs and spaces.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__=


## ESLINT_NMST
### Default
#### OriginalId=no-multi-str
#### Enabled=false
#### Warning=true
#### DisplayName=no-multi-str
#### HelpText
  It’s possible to create multiline strings in JavaScript by using a slash before a newline, such as: Some consider this to be a bad practice as it was an undocumented feature of JavaScript that was only formalized later.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_JSNN
### Default
#### OriginalId=no-new
#### Enabled=false
#### Warning=true
#### DisplayName=no-new
#### HelpText
  The goal of using new with a constructor is typically to create an object of a particular type and store that object in a variable, such as: It’s less common to use new and not store the result, such as: In this case, the created object is thrown away because its reference isn’t stored anywhere, and in many cases, this means that the constructor should be replaced with a function that doesn’t require new to be used.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_NNC
### Default
#### OriginalId=no-negated-condition
#### Enabled=false
#### Warning=true
#### DisplayName=no-negated-condition
#### HelpText
  Negated conditions are more difficult to understand. Code can be made more readable by inverting the condition instead.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major


## ESLINT_NNF
### Default
#### OriginalId=no-new-func
#### Enabled=false
#### Warning=true
#### DisplayName=no-new-func
#### HelpText
  It’s possible to create functions in JavaScript using the Function constructor, such as: This is considered by many to be a bad practice due to the difficult in debugging and reading these types of functions.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_NNO
### Default
#### OriginalId=no-new-object
#### Enabled=false
#### Warning=true
#### DisplayName=no-new-object
#### HelpText
  The Object constructor is used to create new generic objects in JavaScript, such as: However, this is no different from using the more concise object literal syntax: For this reason, many prefer to always use the object literal syntax and never use the Object constructor. While there are no performance differences between the two approaches, the byte savings and conciseness of the object literal form is what has made it the de facto way of creating new objects.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major


## ESLINT_NNRE
### Default
#### OriginalId=no-new-require
#### Enabled=false
#### Warning=true
#### DisplayName=no-new-require
#### HelpText
  The require function is used to include modules that exist in separate files, such as: Some modules return a constructor which can potentially lead to code such as: Unfortunately, this introduces a high potential for confusion since the code author likely meant to write: For this reason, it is usually best to disallow this particular expression.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Node.js and CommonJS

#### Settings
- Priority=Major


## ESLINT_NNSY
### Default
#### OriginalId=no-new-symbol
#### Enabled=true
#### Warning=true
#### DisplayName=no-new-symbol
#### HelpText
  Using a single import statement per module will make the code clearer because you can see everything being imported from that module on one line. In the following example the module import on line 1 is repeated on line 3. These can be combined to make the list of imports more succinct.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/ECMAScript 6

#### Settings
- Priority=Major


## ESLINT_NNT
### Default
#### OriginalId=no-nested-ternary
#### Enabled=false
#### Warning=true
#### DisplayName=no-nested-ternary
#### HelpText
  Nesting ternary expressions makes code unclear. The no-nested-ternary rule disallows the use of nested ternary expressions.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major


## ESLINT_NNW
### Default
#### OriginalId=no-new-wrappers
#### Enabled=true
#### Warning=true
#### DisplayName=no-new-wrappers
#### HelpText
  There are three primitive types in JavaScript that have wrapper objects: string, number, and boolean. These are represented by the constructors String, Number, and Boolean, respectively. The primitive wrapper types are used whenever one of these primitive values is read, providing them with object-like capabilities such as methods. Behind the scenes, an object of the associated wrapper type is created and then destroyed, which is why you can call methods on primitive values, such as: Behind the scenes in this example, a String object is constructed. The substring() method exists on String.prototype and so is accessible to the string instance. It’s also possible to manually create a new wrapper instance: Although possible, there aren’t any good reasons to use these primitive wrappers as constructors. They tend to confuse other developers more than anything else because they seem like they should act as primitives, but they do not. For example: The first problem is that primitive wrapper objects are, in fact, objects. That means typeof will return “object” instead of “string”, “number”, or “boolean”. The second problem comes with boolean objects. Every object is truthy, that means an instance of Boolean always resolves to true even when its actual value is false. For these reasons, it’s considered a best practice to avoid using primitive wrapper types with new.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_NO
### Default
#### OriginalId=no-octal
#### Enabled=true
#### Warning=true
#### DisplayName=no-octal
#### HelpText
  Octal literals are numerals that begin with a leading zero, such as: The leading zero to identify an octal literal has been a source of confusion and error in JavaScript. ECMAScript 5 deprecates the use of octal numeric literals in JavaScript and octal literals cause syntax errors in strict mode. It’s therefore recommended to avoid using octal literals in JavaScript code.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_NOC
### Default
#### OriginalId=no-obj-calls
#### Enabled=true
#### Warning=true
#### DisplayName=no-obj-calls
#### HelpText
  ECMAScript provides several global objects that are intended to be used as-is. Some of these objects look as if they could be constructors due their capitalization (such as Math and JSON) but will throw an error if you try to execute them as functions. The ECMAScript 5 specification makes it clear that both Math and JSON cannot be invoked:


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Possible Errors

#### Settings
- Priority=Major


## ESLINT_NOE
### Default
#### OriginalId=no-octal-escape
#### Enabled=false
#### Warning=true
#### DisplayName=no-octal-escape
#### HelpText
  As of version 5 of the ECMAScript specification, octal escape sequences are a deprecated feature and should not be used. It is recommended that Unicode escapes be used instead.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_NP
### Default
#### OriginalId=no-proto
#### Enabled=false
#### Warning=true
#### DisplayName=no-proto
#### HelpText
  **proto** property has been deprecated as of ECMAScript 3.1 and shouldn’t be used in the code. Use getPrototypeOf method instead.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_NPA
### Default
#### OriginalId=new-parens
#### Enabled=false
#### Warning=true
#### DisplayName=new-parens
#### HelpText
  JavaScript allows the omission of parentheses when invoking a function via the new keyword and the constructor has no arguments. However, some coders believe that omitting the parentheses is inconsistent with the rest of the language and thus makes code less clear.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major


## ESLINT_NPB
### Default
#### OriginalId=no-prototype-builtins
#### Enabled=false
#### Warning=true
#### DisplayName=no-prototype-builtins
#### HelpText
  In ECMAScript 5.1, Object.create was added, which enables the creation of objects with a specified \[\[Prototype\]\]. Object.create(null) is a common pattern used to create objects that will be used as a Map. This can lead to errors when it is assumed that objects will have properties from Object.prototype. This rule prevents calling Object.prototype methods directly from an object.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Possible Errors

#### Settings
- Priority=Major


## ESLINT_NPC
### Default
#### OriginalId=no-path-concat
#### Enabled=false
#### Warning=true
#### DisplayName=no-path-concat
#### HelpText
  In Node.js, the \_\_dirname and \_\_filename global variables contain the directory path and the file path of the currently executing script file, respectively. Sometimes, developers try to use these variables to create paths to other files, such as: However, there are a few problems with this. First, you can’t be sure what type of system the script is running on. Node.js can be run on any computer, including Windows, which uses a different path separator. It’s very easy, therefore, to create an invalid path using string concatenation and assuming Unix-style separators. There’s also the possibility of having double separators, or otherwise ending up with an invalid path. In order to avoid any confusion as to how to create the correct path, Node.js provides the path module. This module uses system-specific information to always return the correct value. So you can rewrite the previous example as: This example doesn’t need to include separators as path.join() will do it in the most appropriate manner. Alternately, you can use path.resolve() to retrieve the fully-qualified path: Both path.join() and path.resolve() are suitable replacements for string concatenation wherever file or directory paths are being created.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Node.js and CommonJS

#### Settings
- Priority=Major


## ESLINT_NPCC
### Default
#### OriginalId=newline-per-chained-call
#### Enabled=false
#### Warning=true
#### DisplayName=newline-per-chained-call
#### HelpText
  Chained method calls on a single line without line breaks are harder to read, so some developers place a newline character after each method call in the chain to make it more readable and easy to maintain.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__={ "ignoreChainWithDepth": 2 }


## ESLINT_NPE
### Default
#### OriginalId=no-process-env
#### Enabled=false
#### Warning=true
#### DisplayName=no-process-env
#### HelpText
  The process.env object in Node.js is used to store deployment/configuration parameters. Littering it through out a project could lead to maintenance issues as it’s another kind of global dependency. As such, it could lead to merge conflicts in a multi-user setup and deployment issues in a multi-server setup. Instead, one of the best practices is to define all those parameters in a single configuration/settings file which could be accessed throughout the project.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_NPEX
### Default
#### OriginalId=no-process-exit
#### Enabled=false
#### Warning=true
#### DisplayName=no-process-exit
#### HelpText
  The process.exit() method in Node.js is used to immediately stop the Node.js process and exit. This is a dangerous operation because it can occur in any method at any point in time, potentially stopping a Node.js application completely when an error occurs. For example: This code could appear in any module and will stop the entire application when somethingBadHappened is truthy. This doesn’t give the application any chance to respond to the error. It’s usually better to throw an error and allow the application to handle it appropriately: By throwing an error in this way, other parts of the application have an opportunity to handle the error rather than stopping the application altogether. If the error bubbles all the way up to the process without being handled, then the process will exit and a non-zero exit code will returned, so the end result is the same.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Node.js and CommonJS

#### Settings
- Priority=Major


## ESLINT_NPL
### Default
#### OriginalId=no-plusplus
#### Enabled=false
#### Warning=true
#### DisplayName=no-plusplus
#### HelpText
  Because the unary ++ and -- operators are subject to automatic semicolon insertion, differences in whitespace can change semantics of source code.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__={ "allowForLoopAfterthoughts": true }


## ESLINT_NPR
### Default
#### OriginalId=no-param-reassign
#### Enabled=false
#### Warning=true
#### DisplayName=no-param-reassign
#### HelpText
  Assignment to variables declared as function parameters can be misleading and lead to confusing behavior, as modifying function parameters will also mutate the arguments object. Often, assignment to function parameters is unintended and indicative of a mistake or programmer error.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major
- __eslint_param__={			"props": false,			"ignorePropertyModificationsFor": []		}


## ESLINT_JSNR
### Default
#### OriginalId=no-redeclare
#### Enabled=false
#### Warning=true
#### DisplayName=no-redeclare
#### HelpText
  In JavaScript, it’s possible to redeclare the same variable name using var. This can lead to confusion as to where the variable is actually declared and initialized.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major
- __eslint_param__={			"builtinGlobals": false		}


## ESLINT_NRA
### Default
#### OriginalId=no-return-await
#### Enabled=false
#### Warning=true
#### DisplayName=no-return-await
#### HelpText
  Inside an async function, return await is useless. Since the return value of an async function is always wrapped in Promise.resolve, return await doesn’t actually do anything except add extra time before the overarching Promise resolves or rejects. This pattern is almost certainly due to programmer ignorance of the return semantics of async functions.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major
- __eslint_param__="always"


## ESLINT_NRG
### Default
#### OriginalId=no-restricted-globals
#### Enabled=false
#### Warning=true
#### DisplayName=no-restricted-globals
#### HelpText
  Disallowing usage of specific global variables can be useful if you want to allow a set of global variables by enabling an environment, but still want to disallow some of those.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Variables

#### Settings
- Priority=Major
- __eslint_param__="event"


## ESLINT_NRIM
### Default
#### OriginalId=no-restricted-imports
#### Enabled=false
#### Warning=true
#### DisplayName=no-restricted-imports
#### HelpText
  Imports are an ES6/ES2015 standard for making the functionality of other modules available in your current module. In CommonJS this is implemented through the require() call which makes this ESLint rule roughly equivalent to its CommonJS counterpart no-restricted-modules.
  Why would you want to restrict imports?
  Some imports might not make sense in a particular environment. For example, Node.js’ fs module would not make sense in an environment that didn’t have a file system.
  Some modules provide similar or identical functionality, think lodash and underscore. Your project may have standardized on a module. You want to make sure that the other alternatives are not being used as this would unnecessarily bloat the project and provide a higher maintenance cost of two dependencies when one would suffice.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/ECMAScript 6

#### Settings
- Priority=Major
- __eslint_param__={"paths": ["exampleImport1", "exampleImport2"]}


## ESLINT_NRM
### Default
#### OriginalId=no-restricted-modules
#### Enabled=false
#### Warning=true
#### DisplayName=no-restricted-modules
#### HelpText
  Disallowing usage of specific node modules can be useful if you want to control the available methods, a developer can use, to implement a feature. This way you can block usage of the fs module if you want disallow file system access. Blocking the os module can be useful if you don’t want to allow any operating system specific code.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Node.js and CommonJS

#### Settings
- Priority=Major
- __eslint_param__={ "paths": [] }


## ESLINT_NRP
### Default
#### OriginalId=no-restricted-properties
#### Enabled=false
#### Warning=true
#### DisplayName=no-restricted-properties
#### HelpText
  Certain properties on objects may be disallowed in a codebase. This is useful for deprecating an API or restricting usage of a module’s methods. For example, you may want to disallow using describe.only when using Mocha or telling people to use Object.assign instead of \_.extend.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major
- __eslint_param__=


## ESLINT_NRS
### Default
#### OriginalId=no-regex-spaces
#### Enabled=true
#### Warning=true
#### DisplayName=no-regex-spaces
#### HelpText
  Regular expressions can be very complex and difficult to understand, which is why it’s important to keep them as simple as possible in order to avoid mistakes. One of the more error-prone things you can do with a regular expression is to use more than one space, such as: In this regular expression, it’s very hard to tell how many spaces are intended to be matched. It’s better to use only one space and then specify how many spaces are expected, such as: Now it is very clear that three spaces are expected to be matched.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Possible Errors

#### Settings
- Priority=Major


## ESLINT_NRSY
### Default
#### OriginalId=no-tabs
#### Enabled=false
#### Warning=true
#### DisplayName=no-tabs
#### HelpText
  Some style guides don’t allow the use of tab characters at all, including within comments.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__=


## ESLINT_JSNS
### Default
#### OriginalId=no-sequences
#### Enabled=false
#### Warning=true
#### DisplayName=no-sequences
#### HelpText
  The comma operator includes multiple expressions where only one is expected. It evaluates each operand from left to right and returns the value of the last operand. However, this frequently obscures side effects, and its use is often an accident. Here are some examples of its use:


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_NSA
### Default
#### OriginalId=no-sparse-arrays
#### Enabled=true
#### Warning=true
#### DisplayName=no-sparse-arrays
#### HelpText
  Sparse arrays contain empty slots, most frequently due to multiple commas being used in an array literal, such as: While the items array in this example has a length of 2, there are actually no values in items\[0\] or items\[1\]. The fact that the array literal is valid with only commas inside, coupled with the length being set and actual item values not being set, make sparse arrays confusing for many developers. Consider the following: In this example, the colors array has a length of 3. But did the developer intend for there to be an empty spot in the middle of the array? Or is it a typo? The confusion around sparse arrays defined in this manner is enough that it’s recommended to avoid using them unless you are certain that they are useful in your code.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Possible Errors

#### Settings
- Priority=Major


## ESLINT_NSAS
### Default
#### OriginalId=no-self-assign
#### Enabled=true
#### Warning=true
#### DisplayName=no-self-assign
#### HelpText
  Self assignments have no effect, so probably those are an error due to incomplete refactoring. Those indicate that what you should do is still remaining.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major
- __eslint_param__={"props":false}


## ESLINT_NSBP
### Default
#### OriginalId=nonblock-statement-body-position
#### Enabled=false
#### Warning=true
#### DisplayName=nonblock-statement-body-position
#### HelpText
  When writing if, else, while, do-while, and for statements, the body can be a single statement instead of a block. It can be useful to enforce a consistent location for these single statements.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="beside"


## ESLINT_NSC
### Default
#### OriginalId=no-self-compare
#### Enabled=false
#### Warning=true
#### DisplayName=no-self-compare
#### HelpText
  Comparing a variable against itself is usually an error, either an typo or refactoring error. It is confusing to the reader and may potentially introduce a runtime error. The only time you would compare a variable against itself is when you are testing for NaN. However, it is far more appropriate to use typeof x === ‘number’ && isNaN(x) or the Number.isNaN ES2015 function for that use case rather than leaving the reader of the code to determine the intent of self comparison.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_NSH
### Default
#### OriginalId=no-shadow
#### Enabled=false
#### Warning=true
#### DisplayName=no-shadow
#### HelpText
  Shadowing is the process by which a local variable shares the same name as a variable in its containing scope. For example: In this case, the variable a inside of b() is shadowing the variable a in the global scope. This can cause confusion while reading the code and it’s impossible to access the global variable.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Variables

#### Settings
- Priority={            "builtinGlobals": false,            "hoist": "functions",            "allow": []        }


## ESLINT_NSRN
### Default
#### OriginalId=no-shadow-restricted-names
#### Enabled=false
#### Warning=true
#### DisplayName=no-shadow-restricted-names
#### HelpText
  ES5 §15.1.1 Value Properties of the Global Object (NaN, Infinity, undefined) as well as strict mode restricted identifiers eval and arguments are considered to be restricted names in JavaScript. Defining them to mean something else can have unintended consequences and confuse others reading the code. For example, there’s nothing prevent you from writing: Then any code used within the same scope would not get the global undefined, but rather the local version with a very different meaning.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Variables

#### Settings
- Priority=Major


## ESLINT_NSU
### Default
#### OriginalId=no-script-url
#### Enabled=false
#### Warning=true
#### DisplayName=no-script-url
#### HelpText
  Using javascript: URLs is considered by some as a form of eval. Code passed in javascript: URLs has to be parsed and evaluated by the browser in the same way that eval is processed.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_NSY
### Default
#### OriginalId=no-sync
#### Enabled=false
#### Warning=true
#### DisplayName=no-sync
#### HelpText
  In Node.js, most I/O is done through asynchronous methods. However, there are often synchronous versions of the asynchronous methods. For example, fs.exists() and fs.existsSync(). In some contexts, using synchronous operations is okay (if, as with ESLint, you are writing a command line utility). However, in other contexts the use of synchronous operations is considered a bad practice that should be avoided. For example, if you are running a high-travel web server on Node.js, you should consider carefully if you want to allow any synchronous operations that could lock up the server.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Node.js and CommonJS

#### Settings
- Priority=Major
- __eslint_param__={ "allowAtRootLevel": false }


## ESLINT_NT
### Default
#### OriginalId=no-ternary
#### Enabled=false
#### Warning=true
#### DisplayName=no-ternary
#### HelpText
  The ternary operator is used to conditionally assign a value to a variable. Some believe that the use of ternary operators leads to unclear code.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major


## ESLINT_NTBS
### Default
#### OriginalId=no-this-before-super
#### Enabled=true
#### Warning=true
#### DisplayName=no-this-before-super
#### HelpText
  In the constructor of derived classes, if this/super are used before super() calls, it raises a reference error. This rule checks this/super keywords in constructors, then reports those that are before super().


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/ECMAScript 6

#### Settings
- Priority=Major


## ESLINT_NTCIS
### Default
#### OriginalId=no-template-curly-in-string
#### Enabled=false
#### Warning=true
#### DisplayName=no-template-curly-in-string
#### HelpText
  ECMAScript 6 allows programmers to create strings containing variable or expressions using template literals, instead of string concatenation, by writing expressions like ${variable} between two backtick quotes (\`). It can be easy to use the wrong quotes when wanting to use template literals, by writing "${variable}", and end up with the literal value "${variable}" instead of a string containing the value of the injected expressions.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Possible Errors

#### Settings
- Priority=Major


## ESLINT_JSNTL
### Default
#### OriginalId=no-throw-literal
#### Enabled=false
#### Warning=true
#### DisplayName=no-throw-literal
#### HelpText
  It is considered good practice to only throw the Error object itself or an object using the Error object as base objects for user-defined exceptions. The fundamental benefit of Error objects is that they automatically keep track of where they were built and originated. This rule restricts what can be thrown as an exception. When it was first created, it only prevented literals from being thrown (hence the name), but it has now been expanded to only allow expressions which have a possibility of being an Error object.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_NTS
### Default
#### OriginalId=no-trailing-spaces
#### Enabled=false
#### Warning=true
#### DisplayName=no-trailing-spaces
#### HelpText
  Sometimes in the course of editing files, you can end up with extra whitespace at the end of lines. These whitespace differences can be picked up by source control systems and flagged as diffs, causing frustration for developers. While this extra whitespace causes no functional issues, many code conventions require that trailing spaces be removed before checkin. Fixable: This rule is automatically fixable using the –fix flag on the command line.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__={            "skipBlankLines": false,            "ignoreComments": false        }


## ESLINT_NU
### Default
#### OriginalId=no-unreachable
#### Enabled=true
#### Warning=true
#### DisplayName=no-unreachable
#### HelpText
  Because the return, throw, break, and continue statements unconditionally exit a block of code, any statements after them cannot be executed. Unreachable statements are usually a mistake.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Possible Errors

#### Settings
- Priority=Major


## ESLINT_JSNUBD
### Default
#### OriginalId=no-use-before-define
#### Enabled=false
#### Warning=true
#### DisplayName=no-use-before-define
#### HelpText
  In JavaScript, prior to ES6, variable and function declarations are hoisted to the top of a scope, so it’s possible to use identifiers before their formal declarations in code. This can be confusing and some believe it is best to always declare variables and functions before using them. In ES6, block-level bindings (let and const) introduce a “temporal dead zone” where a ReferenceError will be thrown with any attempt to access the variable before its declaration.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Variables

#### Settings
- Priority=Major
- __eslint_param__={            "functions": true,            "classes": true,            "variables": true        }


## ESLINT_JSNUC
### Default
#### OriginalId=no-useless-call
#### Enabled=false
#### Warning=true
#### DisplayName=no-useless-call
#### HelpText
  The function invocation can be written by Function.prototype.call() and Function.prototype.apply(). But Function.prototype.call() and Function.prototype.apply() are slower than the normal function invocation.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_NUCK
### Default
#### OriginalId=no-useless-computed-key
#### Enabled=false
#### Warning=true
#### DisplayName=no-useless-computed-key
#### HelpText
  The --fix option on the command line can automatically fix some of the problems reported by this rule.
  It’s unnecessary to use computed properties with literals such as:
  var foo = {\["a"\]: "b"};
  The code can be rewritten as:
  var foo = {"a": "b"};


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/ECMAScript 6

#### Settings
- Priority=Major


## ESLINT_NUCO
### Default
#### OriginalId=no-useless-concat
#### Enabled=false
#### Warning=true
#### DisplayName=no-useless-concat
#### HelpText
  It’s unnecessary to concatenate two strings together, such as: This code is likely the result of refactoring where a variable was removed from the concatenation (such as “a” + b + “b”). In such a case, the concatenation isn’t important and the code can be rewritten as:


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_NUD
### Default
#### OriginalId=no-underscore-dangle
#### Enabled=false
#### Warning=true
#### DisplayName=no-underscore-dangle
#### HelpText
  As far as naming conventions for identifiers go, dangling underscores may be the most polarizing in JavaScript. Dangling underscores are underscores at either the beginning or end of an identifier, such as: There is actually a long history of using dangling underscores to indicate “private” members of objects in JavaScript (though JavaScript doesn’t have truly private members, this convention served as a warning). This began with SpiderMonkey adding nonstandard methods such as **defineGetter**(). The intent with the underscores was to make it obvious that this method was special in some way. Since that time, using a single underscore prefix has become popular as a way to indicate “private” members of objects. Whether or not you choose to allow dangling underscores in identifiers is purely a convention and has no effect on performance, readability, or complexity. It’s purely a preference.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__={ "allow": [] }


## ESLINT_JSNUE
### Default
#### OriginalId=no-unused-expressions
#### Enabled=false
#### Warning=true
#### DisplayName=no-unused-expressions
#### HelpText
  Unused expressions are those expressions that evaluate to a value but are never used. For example: This string is a valid JavaScript expression, but isn’t actually used. Even though it’s not a syntax error it is clearly a logic error and it has no effect on the code being executed.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major
- __eslint_param__={			"allowShortCircuit": false,			"allowTernary": false,			"allowTaggedTemplates": false		}


## ESLINT_NUES
### Default
#### OriginalId=no-useless-escape
#### Enabled=true
#### Warning=true
#### DisplayName=no-useless-escape
#### HelpText
  Escaping non-special characters in strings, template literals, and regular expressions doesn’t have any effect, as demonstrated in the following example:


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_NUF
### Default
#### OriginalId=no-unsafe-finally
#### Enabled=true
#### Warning=true
#### DisplayName=no-unsafe-finally
#### HelpText
  JavaScript suspends the control flow statements of try and catch blocks until the execution of finally block finishes. So, when return, throw, break, or continue is used in finally, control flow statements inside try and catch are overwritten, which is considered as unexpected behavior.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Possible Errors

#### Settings
- Priority=Major


## ESLINT_NUI
### Default
#### OriginalId=no-undef-init
#### Enabled=false
#### Warning=true
#### DisplayName=no-undef-init
#### HelpText
  In JavaScript, a variable that is declared and not initialized to any value automatically gets the value of undefined. For example: It’s therefore unnecessary to initialize a variable to undefined, such as: It’s considered a best practice to avoid initializing variables to undefined.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Variables

#### Settings
- Priority=Major


## ESLINT_NULA
### Default
#### OriginalId=no-unused-labels
#### Enabled=true
#### Warning=true
#### DisplayName=no-unused-labels
#### HelpText
  The --fix option on the command line can automatically fix some of the problems reported by this rule. Labels that are declared and not used anywhere in the code are most likely an error due to incomplete refactoring.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_NULC
### Default
#### OriginalId=no-unmodified-loop-condition
#### Enabled=false
#### Warning=true
#### DisplayName=no-unmodified-loop-condition
#### HelpText
  Variables in a loop condition often are modified in the loop. If not, it’s possibly a mistake.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_NUM
### Default
#### OriginalId=no-unexpected-multiline
#### Enabled=true
#### Warning=true
#### DisplayName=no-unexpected-multiline
#### HelpText
  Semicolons are optional in JavaScript, via a process called automatic semicolon insertion (ASI). See the documentation for semi for a fuller discussion of that feature. The rules for ASI are relatively straightforward: In short, as once described by Isaac Schlueter, a character always ends a statement (just like a semicolon) unless one of the following is true: This particular rule aims to spot scenarios where a newline looks like it is ending a statement, but is not.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Possible Errors

#### Settings
- Priority=Major


## ESLINT_NUN
### Default
#### OriginalId=no-undef
#### Enabled=true
#### Warning=true
#### DisplayName=no-undef
#### HelpText
  This rule can help you locate potential ReferenceErrors resulting from misspellings of variable and parameter names, or accidental implicit globals (for example, from forgetting the var keyword in a for loop initializer).


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Variables

#### Settings
- Priority=Major
- __eslint_param__={ "typeof": false }


## ESLINT_NUND
### Default
#### OriginalId=no-undefined
#### Enabled=false
#### Warning=true
#### DisplayName=no-undefined
#### HelpText
  The undefined variable is unique in JavaScript because it is actually a property of the global object. As such, in ECMAScript 3 it was possible to overwrite the value of undefined. While ECMAScript 5 disallows overwriting undefined, it’s still possible to shadow undefined, such as: This represents a problem for undefined that doesn’t exist for null, which is a keyword and primitive value that can neither be overwritten nor shadowed. All uninitialized variables automatically get the value of undefined: For this reason, it’s not necessary to explicitly initialize a variable to undefined. Taking all of this into account, some style guides forbid the use of undefined, recommending instead:


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Variables

#### Settings
- Priority=Major


## ESLINT_NUNEG
### Default
#### OriginalId=no-unsafe-negation
#### Enabled=true
#### Warning=true
#### DisplayName=no-unsafe-negation
#### HelpText
  Just as developers might type -a + b when they mean -(a + b) for the negative of a sum, they might type !key in object by mistake when they almost certainly mean !(key in object) to test that a key is not in an object. !obj instanceof Ctor is similar.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Possible Errors

#### Settings
- Priority=Major


## ESLINT_NURE
### Default
#### OriginalId=no-useless-return
#### Enabled=false
#### Warning=true
#### DisplayName=no-useless-return
#### HelpText
  A return; statement with nothing after it is redundant, and has no effect on the runtime behavior of a function. This can be confusing, so it’s better to disallow these redundant statements.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_NUREN
### Default
#### OriginalId=no-useless-rename
#### Enabled=false
#### Warning=true
#### DisplayName=no-useless-rename
#### HelpText
  ES2015 provides a default class constructor if one is not specified. As such, it is unnecessary to provide an empty constructor or one that simply delegates into its parent class


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/ECMAScript 6

#### Settings
- Priority=Major
- __eslint_param__={			"ignoreDestructing": false,			"ignoreImport": false,			"ignoreExport": false		}


## ESLINT_NUT
### Default
#### OriginalId=no-unneeded-ternary
#### Enabled=false
#### Warning=true
#### DisplayName=no-unneeded-ternary
#### HelpText
  It’s a common mistake in JavaScript to use a conditional expression to select between two Boolean values instead of using ! to convert the test to a Boolean. Here are some examples: This rule disallows the use of ‘Boolean’ literals inside conditional expressions. Another common mistake is using a single variable as both the conditional test and the consequent. In such cases, the logical OR can be used to provide the same functionality. Here is an example: This rule disallows the conditional expression as a default assignment pattern when the defaultAssignment option is set to false.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__={            "defaultAssignment": true        }


## ESLINT_JSNUV
### Default
#### OriginalId=no-unused-vars
#### Enabled=false
#### Warning=true
#### DisplayName=no-unused-vars
#### HelpText
  Variables that are declared and not used anywhere in the code are most likely an error due to incomplete refactoring. Such variables take up space in the code and can lead to confusion by readers.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Variables

#### Settings
- Priority=Major
- __eslint_param__={			"vars": "all",			"args": "after-used"		}


## ESLINT_NV
### Default
#### OriginalId=no-void
#### Enabled=false
#### Warning=true
#### DisplayName=no-void
#### HelpText
  The void operator takes an operand and returns undefined: void expression will evaluate expression and return undefined. It can be used to ignore any side effects expression may produce: The common case of using void operator is to get a “pure” undefined value as prior to ES5 the undefined variable was mutable: Another common case is to minify code as void 0 is shorter than undefined: When used with IIFE (immediately-invoked function expression) void can be used to force the function keyword to be treated as an expression instead of a declaration: Some code styles prohibit void operator marking it as non-obvious and hard to read.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_NVA
### Default
#### OriginalId=no-var
#### Enabled=false
#### Warning=true
#### DisplayName=no-var
#### HelpText
  ECMAScript 6 allows programmers to create variables with block scope instead of function scope using the let and const keywords. Block scope is common in many other programming languages and helps programmers avoid mistakes such as:


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/ECMAScript 6

#### Settings
- Priority=Major


## ESLINT_NW
### Default
#### OriginalId=no-with
#### Enabled=false
#### Warning=true
#### DisplayName=no-with
#### HelpText
  The with statement is potentially problematic because it adds members of an object to the current scope, making it impossible to tell what a variable inside the block actually refers to. Additionally, the with statement cannot be used in strict mode.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_NWBP
### Default
#### OriginalId=no-whitespace-before-property
#### Enabled=false
#### Warning=true
#### DisplayName=no-whitespace-before-property
#### HelpText
  JavaScript allows whitespace between objects and their properties. However, inconsistent spacing can make code harder to read and can lead to errors.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major


## ESLINT_NWC
### Default
#### OriginalId=no-warning-comments
#### Enabled=false
#### Warning=true
#### DisplayName=no-warning-comments
#### HelpText
  Often code is marked during development process for later work on it or with additional thoughts. Examples are typically // TODO: do something or // FIXME: this is not a good idea. These comments are a warning signal, that there is something not production ready in your code. Most likely you want to fix it or remove the comments before you roll out your code with a good feeling.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major
- __eslint_param__={                "terms": [ "todo", "fixme", "xxx" ],                "location": "start"            }


## ESLINT_OA
### Default
#### OriginalId=operator-assignment
#### Enabled=false
#### Warning=true
#### DisplayName=operator-assignment
#### HelpText
  JavaScript provides shorthand operators that combine variable assignment and some simple mathematical operations. For example, x = x + 4 can be shortened to x += 4. The supported shorthand forms are as follows:


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="always"


## ESLINT_OCN
### Default
#### OriginalId=object-curly-newline
#### Enabled=false
#### Warning=true
#### DisplayName=object-curly-newline
#### HelpText
  A number of style guides require or disallow line breaks inside of object braces and other tokens.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__={ "multiline": true }


## ESLINT_JSOCS
### Default
#### OriginalId=object-curly-spacing
#### Enabled=false
#### Warning=true
#### DisplayName=object-curly-spacing
#### HelpText
  While formatting preferences are very personal, a number of style guides require or disallow spaces between curly braces.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="never"


## ESLINT_OL
### Default
#### OriginalId=operator-linebreak
#### Enabled=false
#### Warning=true
#### DisplayName=operator-linebreak
#### HelpText
  When a statement is too long to fit on a single line, line breaks are generally inserted next to the operators separating expressions. The first style coming to mind would be to place the operator at the end of the line, following the english punctuation rules. Some developers find that placing operators at the beginning of the line makes the code more readable.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__=


## ESLINT_OPN
### Default
#### OriginalId=object-curly-spacing
#### Enabled=false
#### Warning=true
#### DisplayName=object-curly-spacing
#### HelpText
  This rule permits you to restrict the locations of property specifications in object literals. You may prohibit any part of any property specification from appearing on the same line as any part of any other property specification. You may make this prohibition absolute, or, by invoking an object option, you may allow an exception, permitting an object literal to have all parts of all of its property specifications on a single line.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major


## ESLINT_OS
### Default
#### OriginalId=object-shorthand
#### Enabled=false
#### Warning=true
#### DisplayName=object-shorthand
#### HelpText
  EcmaScript 6 provides a concise form for defining object literal methods and properties. This syntax can make defining complex object literals much cleaner. Here are a few common examples using the ES5 syntax: Now here are ES6 equivalents:


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/ECMAScript 6

#### Settings
- Priority=Major
- __eslint_param__="always"


## ESLINT_OV
### Default
#### OriginalId=one-var
#### Enabled=false
#### Warning=true
#### DisplayName=one-var
#### HelpText
  Variables can be declared at any point in JavaScript code using var, let, or const. There are many styles and preferences related to the declaration of variables, and one of those is deciding on how many variable declarations should be allowed in a single function. There are two schools of thought in this regard: For instance: The single-declaration school of thought is based in pre-ECMAScript 6 behaviors, where there was no such thing as block scope, only function scope. Since all var statements are hoisted to the top of the function anyway, some believe that declaring all variables in a single declaration at the top of the function removes confusion around scoping rules.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="always"


## ESLINT_OVPL
### Default
#### OriginalId=one-var-declaration-per-line
#### Enabled=false
#### Warning=true
#### DisplayName=one-var-declaration-per-lines
#### HelpText
  Some developers declare multiple var statements on the same line, others prefer to declare one var per line. Keeping to one of these styles across a project’s codebase can help with maintaining code consistency.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="initializations"


## ESLINT_JSPAC
### Default
#### OriginalId=prefer-arrow-callback
#### Enabled=false
#### Warning=true
#### DisplayName=prefer-arrow-callback
#### HelpText
  Arrow functions are suited to callbacks, because:


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/ECMAScript 6

#### Settings
- Priority=Major
- __eslint_param__={"allowNamedFunction": false, "allowUnboundThis": true}


## ESLINT_PB
### Default
#### OriginalId=padded-blocks
#### Enabled=false
#### Warning=true
#### DisplayName=padded-blocks
#### HelpText
  Some style guides require block statements to start and end with blank lines. The goal is to improve readability by visually separating the block content and the surrounding code. Since it’s good to have a consistent code style, you should either always write padded blocks or never do it.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="always"


## ESLINT_PC
### Default
#### OriginalId=prefer-const
#### Enabled=false
#### Warning=true
#### DisplayName=prefer-const
#### HelpText
  If a variable is never modified, using the const declaration is better. const declaration tells readers, “this variable is never modified,” reducing cognitive load and improving maintainability.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/ECMAScript 6

#### Settings
- Priority=Major
- __eslint_param__={			"destructing": "any",			"ignoreReadBeforeAssign": false		}


## ESLINT_JSPLBS
### Default
#### OriginalId=padding-line-between-statements
#### Enabled=false
#### Warning=true
#### DisplayName=padding-line-between-statements
#### HelpText
  This rule requires or disallows blank lines between the given 2 kinds of statements. Properly blank lines help developers to understand the code. For example, the following configuration requires a blank line between a variable declaration and a return statement.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major


## ESLINT_PNLI
### Default
#### OriginalId=prefer-numeric-literals
#### Enabled=false
#### Warning=true
#### DisplayName=prefer-numeric-literals
#### HelpText
  The parseInt() and Number.parseInt() functions can be used to turn binary, octal, and hexadecimal strings into integers. As binary, octal, and hexadecimal literals are supported in ES6, this rule encourages use of those numeric literals instead of parseInt() or Number.parseInt()


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/ECMAScript 6

#### Settings
- Priority=Major


## ESLINT_PPRE
### Default
#### OriginalId=prefer-promise-reject-errors
#### Enabled=false
#### Warning=true
#### DisplayName=prefer-promise-reject-errors
#### HelpText
  It is considered good practice to only pass instances of the built-in Error object to the reject() function for user-defined errors in Promises. Error objects automatically store a stack trace, which can be used to debug an error by determining where it came from. If a Promise is rejected with a non-Error value, it can be difficult to determine where the rejection occurred.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_PRED
### Default
#### OriginalId=prefer-destructing
#### Enabled=false
#### Warning=true
#### DisplayName=prefer-destructing
#### HelpText
  With JavaScript ES6, a new syntax was added for creating variables from an array index or object property, called destructuring. This rule enforces usage of destructuring instead of accessing a property through a member expression.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/ECMAScript 6

#### Settings
- Priority=Major
- __eslint_param__=[{				"array": true,				"object": true			}, {				"enforceForRenamedProperties": false			}]


## ESLINT_PRRP
### Default
#### OriginalId=prefer-rest-params
#### Enabled=false
#### Warning=true
#### DisplayName=prefer-rest-params
#### HelpText
  There are rest parameters in ES2015. We can use that feature for variadic functions instead of the arguments variable. Arguments does not have methods of Array.prototype, so it’s a bit of an inconvenience.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/ECMAScript 6

#### Settings
- Priority=Major


## ESLINT_PS
### Default
#### OriginalId=prefer-spread
#### Enabled=false
#### Warning=true
#### DisplayName=prefer-spread
#### HelpText
  Before ES2015, one must use Function.prototype.apply() to call variadic functions. In ES2015, one can use the spread operator to call variadic functions.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/ECMAScript 6

#### Settings
- Priority=Major


## ESLINT_PTEM
### Default
#### OriginalId=prefer-template
#### Enabled=false
#### Warning=true
#### DisplayName=prefer-template
#### HelpText
  In ES2015 (ES6), we can use template literals instead of string concatenation.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/ECMAScript 6

#### Settings
- Priority=Major


## ESLINT_JSQ
### Default
#### OriginalId=quotes
#### Enabled=false
#### Warning=true
#### DisplayName=quotes
#### HelpText
  JavaScript allows you to define strings in one of three ways: double quotes, single quotes, and backticks (as of ECMAScript 6). For example: Each of these lines creates a string and, in some cases, can be used interchangeably. The choice of how to define strings in a codebase is a stylistic one outside of template literals (which allow embedded of expressions to be interpreted). Many codebases require strings to be defined in a consistent manner.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="double"


## ESLINT_QP
### Default
#### OriginalId=quote-props
#### Enabled=false
#### Warning=true
#### DisplayName=quote-props
#### HelpText
  Object literal property names can be defined in two ways: using literals or using strings. For example, these two objects are equivalent: In many cases, it doesn’t matter if you choose to use an identifier instead of a string or vice-versa. Even so, you might decide to enforce a consistent style in your code. There are, however, some occasions when you must use quotes: Another example where quotes do matter is when using numeric literals as property keys: This may look alright at first sight, but this code in fact throws a syntax error in ECMAScript 5 strict mode. This happens because 1e2 and 100 are coerced into strings before getting used as the property name. Both String(1e2) and String(100) happen to be equal to “100”, which causes the “Duplicate data property in object literal not allowed in strict mode” error. Issues like that can be tricky to debug, so some prefer to require quotes around all property names.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="always"


## ESLINT_R
### Default
#### OriginalId=radix
#### Enabled=false
#### Warning=true
#### DisplayName=radix
#### HelpText
  When using the parseInt() function it is common to omit the second argument, the radix, and let the function try to determine from the first argument what type of number it is. By default, parseInt() will autodetect decimal and hexadecimal (via 0x prefix). Prior to ECMAScript 5, parseInt() also autodetected octal literals, which caused problems because many developers assumed a leading 0 would be ignored. This confusion led to the suggestion that you always use the radix parameter to parseInt() to eliminate unintended consequences. So instead of doing this: Do this: ECMAScript 5 changed the behavior of parseInt() so that it no longer autodetects octal literals and instead treats them as decimal literals. However, the differences between hexadecimal and decimal interpretation of the first parameter causes many developers to continue using the radix parameter to ensure the string is interpreted in the intended way. On the other hand, if the code is targeting only ES5-compliant environments passing the radix 10 may be redundant. In such a case you might want to disallow using such a radix.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major
- __eslint_param__="always"


## ESLINT_JSRA
### Default
#### OriginalId=require-await
#### Enabled=false
#### Warning=true
#### DisplayName=require-await
#### HelpText
  Async functions which have no await expression may be the unintentional result of refactoring.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_RJ
### Default
#### OriginalId=require-jsdoc
#### Enabled=false
#### Warning=true
#### DisplayName=require-jsdoc
#### HelpText
  JSDoc is a JavaScript API documentation generator. It uses specially-formatted comments inside of code to generate API documentation automatically. For example, this is what a JSDoc comment looks like for a function: Some style guides require JSDoc comments for all functions as a way of explaining function behavior.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__={            "require": {                "FunctionDeclaration": true,                "MethodDefinition": false,                "ClassDeclaration": false,                "ArrowFunctionExpression": false,                "FunctionExpression": false            }        }


## ESLINT_RSSP
### Default
#### OriginalId=rest-spread-spacing
#### Enabled=false
#### Warning=true
#### DisplayName=rest-spread-spacing
#### HelpText
  ES2015 introduced the rest and spread operators, which expand an iterable structure into its individual parts. Some examples of their usage are as follows.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/ECMAScript 6

#### Settings
- Priority=Major
- __eslint_param__="never"


## ESLINT_RY
### Default
#### OriginalId=require-yield
#### Enabled=true
#### Warning=true
#### DisplayName=require-yield
#### HelpText
  This rule generates warnings for generator functions that do not have the yield keyword.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/ECMAScript 6

#### Settings
- Priority=Major


## ESLINT_JSS
### Default
#### OriginalId=strict
#### Enabled=false
#### Warning=true
#### DisplayName=strict
#### HelpText
  A Use Strict Directive at the beginning of a script or function body enables strict mode semantics: When used globally, as in the preceding example, the entire script, including all contained functions, are strict mode code. It is also possible to specify function-level strict mode, such that strict mode applies only to the function in which the directive occurs:


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Strict Mode

#### Settings
- Priority=Major
- __eslint_param__="safe"


## ESLINT_SBB
### Default
#### OriginalId=space-before-blocks
#### Enabled=false
#### Warning=true
#### DisplayName=space-before-blocks
#### HelpText
  Consistency is an important part of any style guide. While it is a personal preference where to put the opening brace of blocks, it should be consistent across a whole project. Having an inconsistent style distracts the reader from seeing the important parts of the code. Fixable: This rule is automatically fixable using the –fix flag on the command line.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="always"


## ESLINT_JSSBFP
### Default
#### OriginalId=space-before-function-paren
#### Enabled=false
#### Warning=true
#### DisplayName=space-before-function-paren
#### HelpText
  When formatting a function, whitespace is allowed between the function name or function keyword and the opening paren. Named functions also require a space between the function keyword and the function name, but anonymous functions require no whitespace. For example: Style guides may require a space after the function keyword for anonymous functions, while others specify no whitespace. Similarly, the space after a function name may or may not be required. Fixable: This rule is automatically fixable using the –fix flag on the command line.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="always"


## ESLINT_SC
### Default
#### OriginalId=spaced-comment
#### Enabled=false
#### Warning=true
#### DisplayName=spaced-comment
#### HelpText
  Some style guides require or disallow a whitespace immediately after the initial // or /\* of a comment. Whitespace after the // or /\* makes it easier to read text in comments. On the other hand, commenting out code is easier without having to put a whitespace right after the // or /\*.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="always"


## ESLINT_SCS
### Default
#### OriginalId=switch-colon-spacing
#### Enabled=false
#### Warning=true
#### DisplayName=switch-colon-spacing
#### HelpText
  Spacing around colons improves readability of case/default clauses.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__={                "after": true,                "before": false            }


## ESLINT_SE
### Default
#### OriginalId=semi
#### Enabled=false
#### Warning=true
#### DisplayName=semi
#### HelpText
  JavaScript is unique amongst the C-like languages in that it doesn’t require semicolons at the end of each statement. In many cases, the JavaScript engine can determine that a semicolon should be in a certain spot and will automatically add it. This feature is known as automatic semicolon insertion (ASI) and is considered one of the more controversial features of JavaScript. For example, the following lines are both valid: On the first line, the JavaScript engine will automatically insert a semicolon, so this is not considered a syntax error. The JavaScript engine still knows how to interpret the line and knows that the line end indicates the end of the statement. In the debate over ASI, there are generally two schools of thought. The first is that we should treat ASI as if it didn’t exist and always include semicolons manually. The rationale is that it’s easier to always include semicolons than to try to remember when they are or are not required, and thus decreases the possibility of introducing an error. However, the ASI mechanism can sometimes be tricky to people who are using semicolons. For example, consider this code: This may look like a return statement that returns an object literal, however, the JavaScript engine will interpret this code as: Effectively, a semicolon is inserted after the return statement, causing the code below it (a labeled literal inside a block) to be unreachable. This rule and the no-unreachable rule will protect your code from such cases. On the other side of the argument are those who says that since semicolons are inserted automatically, they are optional and do not need to be inserted manually. However, the ASI mechanism can also be tricky to people who don’t use semicolons. For example, consider this code: In this example, a semicolon will not be inserted after the first line, causing a run-time error (because an empty object is called as if it’s a function). The no-unexpected-multiline rule can protect your code from such cases. Although ASI allows for more freedom over your coding style, it can also make your code behave in an unexpected way, whether you use semicolons or not. Therefore, it is best to know when ASI takes place and when it does not, and have ESLint protect your code from these potentially unexpected cases. In short, as once described by Isaac Schlueter, a character always ends a statement (just like a semicolon) unless one of the following is true:


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="always"


## ESLINT_SIMD
### Default
#### OriginalId=symbol-description
#### Enabled=false
#### Warning=true
#### DisplayName=symbol-description
#### HelpText
  The Symbol function may have optional description. Using description promotes easier debugging: when a symbol is logged the description is used.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/ECMAScript 6

#### Settings
- Priority=Major


## ESLINT_SIMP
### Default
#### OriginalId=sort-imports
#### Enabled=false
#### Warning=true
#### DisplayName=sort-imports
#### HelpText
  The import statement is used to import members (functions, objects or primitives) that have been exported from an external module. Using a specific member syntax:


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/ECMAScript 6

#### Settings
- Priority=Major
- __eslint_param__={			"ignoreCase": false,			"ignoreMemberSort": false,			"memberSyntaxSortOrder": ["none", "all", "multiple", "single"]		}


## ESLINT_JSSIO
### Default
#### OriginalId=space-infix-ops
#### Enabled=false
#### Warning=true
#### DisplayName=space-infix-ops
#### HelpText
  While formatting preferences are very personal, a number of style guides require spaces around operators, such as: The proponents of these extra spaces believe it make the code easier to read and can more easily highlight potential errors, such as: While this is valid JavaScript syntax, it is hard to determine what the author intended. Fixable: This rule is automatically fixable using the –fix flag on the command line.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__={            "int32Hint": false        }


## ESLINT_SIP
### Default
#### OriginalId=space-in-parens
#### Enabled=false
#### Warning=true
#### DisplayName=space-in-parens
#### HelpText
  Some style guides require or disallow spaces inside of parentheses:


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="never"


## ESLINT_SK
### Default
#### OriginalId=sort-keys
#### Enabled=false
#### Warning=true
#### DisplayName=sort-keys
#### HelpText
  This rule checks all property definitions of object expressions and verifies that all variables are sorted alphabetically.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="asc"


## ESLINT_SS
### Default
#### OriginalId=semi-spacing
#### Enabled=false
#### Warning=true
#### DisplayName=semi-spacing
#### HelpText
  JavaScript allows you to place unnecessary spaces before or after a semicolon. Disallowing or enforcing space around a semicolon can improve the readability of your program.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__={                "before": false,                "after": true            }


## ESLINT_SSTYLE
### Default
#### OriginalId=semi-style
#### Enabled=false
#### Warning=true
#### DisplayName=semi-style
#### HelpText
  Generally, semicolons are at the end of lines. However, in semicolon-less style, semicolons are at the beginning of lines. This rule enforces that semicolons are at the configured location.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="last"


## ESLINT_SUO
### Default
#### OriginalId=space-unary-ops
#### Enabled=false
#### Warning=true
#### DisplayName=space-unary-ops
#### HelpText
  Some styleguides require or disallow spaces before or after unary operators. This is mainly a stylistic issue, however, some JavaScript expressions can be written without spacing which makes it harder to read and maintain. Fixable: This rule is automatically fixable using the –fix flag on the command line.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__={                "words": true,                "nonwords": false            }


## ESLINT_SV
### Default
#### OriginalId=sort-vars
#### Enabled=false
#### Warning=true
#### DisplayName=sort-vars
#### HelpText
  When declaring multiple variables within the same block, some developers prefer to sort variable names alphabetically to be able to find necessary variable easier at the later time. Others feel that it adds complexity and becomes burden to maintain.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__={            "ignoreCase": true        }


## ESLINT_TECS
### Default
#### OriginalId=template-curly-spacing
#### Enabled=false
#### Warning=true
#### DisplayName=template-curly-spacing
#### HelpText
  We can embed expressions in template strings with using a pair of ${ and }. This rule can force usage of spacing within the curly brace pair according to style guides.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/ECMAScript 6

#### Settings
- Priority=Major
- __eslint_param__="never"


## ESLINT_TTS
### Default
#### OriginalId=template-tag-spacing
#### Enabled=false
#### Warning=true
#### DisplayName=template-tag-spacing
#### HelpText
  This rule aims to maintain consistency around the spacing between template tag functions and their template literals.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="never"


## ESLINT_UB
### Default
#### OriginalId=unicode-bom
#### Enabled=false
#### Warning=true
#### DisplayName=unicode-bom
#### HelpText
  The Unicode Byte Order Mark (BOM) is used to specify whether code units are big endian or little endian. That is, whether the most significant or least significant bytes come first. UTF-8 does not require a BOM because byte ordering does not matter when characters are a single byte. Since UTF-8 is the dominant encoding of the web, we make "never" the default option.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="never"


## ESLINT_UI
### Default
#### OriginalId=use-isnan
#### Enabled=true
#### Warning=true
#### DisplayName=use-isnan
#### HelpText
  In JavaScript, NaN is a special value of the Number type. It’s used to represent any of the “not-a-number” values represented by the double-precision 64-bit format as specified by the IEEE Standard for Binary Floating-Point Arithmetic. NaN has the unique property of not being equal to anything, including itself. That is to say, that the condition NaN !== NaN evaluates to true.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Possible Errors

#### Settings
- Priority=Major


## ESLINT_VJ
### Default
#### OriginalId=valid-jsdoc
#### Enabled=false
#### Warning=true
#### DisplayName=valid-jsdoc
#### HelpText
  JSDoc is a JavaScript API documentation generator. It uses specially-formatted comments inside of code to generate API documentation automatically. For example, this is what a JSDoc comment looks like for a function: The JSDoc comments have a syntax all their own, and it is easy to mistakenly mistype a comment because comments aren’t often checked for correctness in editors. Further, it’s very easy for the function definition to get out of sync with the comments, making the comments a source of confusion and error.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Possible Errors

#### Settings
- Priority=Major
- __eslint_param__={            "requireReturn": false        }


## ESLINT_VOT
### Default
#### OriginalId=vars-on-top
#### Enabled=false
#### Warning=true
#### DisplayName=vars-on-top
#### HelpText
  The vars-on-top rule generates warnings when variable declarations are not used serially at the top of a function scope or the top of a program. By default variable declarations are always moved (“hoisted”) invisibly to the top of their containing scope by the JavaScript interpreter. This rule forces the programmer to represent that behaviour by manually moving the variable declaration to the top of its containing scope.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major


## ESLINT_VT
### Default
#### OriginalId=valid-typeof
#### Enabled=true
#### Warning=true
#### DisplayName=valid-typeof
#### HelpText
  For a vast majority of use-cases, the only valid results of the typeof operator will be one of the following: “undefined”, “object”, “boolean”, “number”, “string”, and “function”. When the result of a typeof operation is compared against a string that is not one of these strings, it is usually a typo. This rule ensures that when the result of a typeof operation is compared against a string, that string is in the aforementioned set.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Possible Errors

#### Settings
- Priority=Major
- __eslint_param__={ "requireStringLiterals": true }


## ESLINT_WI
### Default
#### OriginalId=wrap-iife
#### Enabled=false
#### Warning=true
#### DisplayName=wrap-iife
#### HelpText
  Require immediate function invocation to be wrapped in parentheses.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major
- __eslint_param__="outside"


## ESLINT_WR
### Default
#### OriginalId=wrap-regex
#### Enabled=false
#### Warning=true
#### DisplayName=wrap-regex
#### HelpText
  When a regular expression is used in certain situations, it can end up looking like a division operator. For example:


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Stylistic Issues

#### Settings
- Priority=Major


## ESLINT_Y
### Default
#### OriginalId=yoda
#### Enabled=false
#### Warning=true
#### DisplayName=yoda
#### HelpText
  Yoda conditions are so named because the literal value of the condition comes first while the variable comes second. For example, the following is a Yoda condition: This is called a Yoda condition because it reads as, “red is the color”, similar to the way the Star Wars character Yoda speaks. Compare to the other way of arranging the operands: This typically reads, “color is red”, which is arguably a more natural way to describe the comparison. Proponents of Yoda conditions highlight that it is impossible to mistakenly use = instead of == because you cannot assign to a literal value. Doing so will cause a syntax error and you will be informed of the mistake early on. This practice was therefore very common in early programming where tools were not yet available. Opponents of Yoda conditions point out that tooling has made us better programmers because tools will catch the mistaken use of = instead of == (ESLint will catch this for you). Therefore, they argue, the utility of the pattern doesn’t outweigh the readability hit the code takes while using Yoda conditions.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/Best Practices

#### Settings
- Priority=Major
- __eslint_param__="never"


## ESLINT_YSSP
### Default
#### OriginalId=yield-star-spacing
#### Enabled=false
#### Warning=true
#### DisplayName=yield-star-spacing
#### HelpText
  This rule enforces spacing around the \* in yield\* expressions. To use this rule you either need to use the es6 environment or set ecmaVersion to 6 in parserOptions.


#### Tags
- /language/JavaScript
- /tool/ESLINT
- /general/ECMAScript 6

#### Settings
- Priority=Major
- __eslint_param__={"before": true, "after": false}










## ESLINT_TSAOS
### Default
#### OriginalId=@typescript-eslint/adjacent-overload-signatures
#### Enabled=true
#### Warning=true
#### DisplayName=adjacent-overload-signatures
#### HelpText
  This rule aims to standardize the way overloaded members are organized.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Stylistic Issues

#### Settings
- Priority=Major


## ESLINT_TSAT
### Default
#### OriginalId=@typescript-eslint/array-type
#### Enabled=true
#### Warning=true
#### DisplayName=array-type
#### HelpText
  This rule aims to standardize usage of array types within your codebase.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__={"array-type": [true, "generic"]}


## ESLINT_TSATH
### Default
#### OriginalId=@typescript-eslint/await-thenable
#### Enabled=true
#### Warning=true
#### DisplayName=await-thenable
#### HelpText
  \-


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSBS
### Default
#### OriginalId=@typescript-eslint/brace-style
#### Enabled=false
#### Warning=true
#### DisplayName=brace-style
#### HelpText
  This rule extends the base eslint/brace-style rule. It adds support for enum, interface, namespace and module declarations.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="1tbs"


## ESLINT_TSBT
### Default
#### OriginalId=@typescript-eslint/ban-types
#### Enabled=true
#### Warning=true
#### DisplayName=ban-types
#### HelpText
  This rule bans specific types and can suggest alternatives. Note that it does not ban the corresponding runtime objects from being used.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSBTC
### Default
#### OriginalId=@typescript-eslint/ban-ts-comment
#### Enabled=true
#### Warning=true
#### DisplayName=ban-ts-comment
#### HelpText
  This rule lets you set which directive comments you want to allow in your codebase. By default, only @ts-check is allowed, as it enables rather than suppresses errors.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSBTSC
### Default
#### OriginalId=@typescript-eslint/ban-tslint-comment
#### Enabled=false
#### Warning=true
#### DisplayName=ban-tslint-comment
#### HelpText
  \-


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSCD
### Default
#### OriginalId=@typescript-eslint/comma-dangle
#### Enabled=false
#### Warning=true
#### DisplayName=comma-dangle
#### HelpText
  This rule extends the base eslint/comma-dangle rule. It adds support for TypeScript syntax.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Possible Errors

#### Settings
- Priority=Major
- __eslint_param__={ "arrays": "never","objects": "never","imports": "never","exports": "never","functions": "ignore","enums":  "never","generics": "never","tuples": "never"}


## ESLINT_TSCIOS
### Default
#### OriginalId=@typescript-eslint/consistent-indexed-object-style
#### Enabled=false
#### Warning=true
#### DisplayName=consistent-indexed-object-style
#### HelpText
  This rule enforces a consistent way to define records.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Stylistic Issues

#### Settings
- Priority=Major


## ESLINT_TSCLPS
### Default
#### OriginalId=@typescript-eslint/class-literal-property-style
#### Enabled=false
#### Warning=true
#### DisplayName=class-literal-property-style
#### HelpText
  This rule aims to ensure that literals exposed by classes are done so consistently, in one of the two style described above. By default this rule prefers the fields style as it means JS doesn't have to setup and teardown a function closure. Note that this rule only checks for constant literal values (string, template string, number, bigint, boolean, regexp, null). It does not check objects or arrays, because a readonly field behaves differently to a getter in those cases. It also does not check functions, as it is a common pattern to use readonly fields with arrow function values as auto-bound methods. This is because these types can be mutated and carry with them more complex implications about their usage.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Stylistic Issues

#### Settings
- Priority=Major


## ESLINT_TSCTA
### Default
#### OriginalId=@typescript-eslint/consistent-type-assertions
#### Enabled=false
#### Warning=true
#### DisplayName=consistent-type-assertions
#### HelpText
  This rule aims to standardize the use of type assertion style across the codebase. Type assertions are also commonly referred as "type casting" in TypeScript (even though it is technically slightly different to what is understood by type casting in other languages), so you can think of type assertions and type casting referring to the same thing. It is essentially you saying to the TypeScript compiler, "in this case, I know better than you!".


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Stylistic Issues

#### Settings
- Priority=Major


## ESLINT_TSCTD
### Default
#### OriginalId=@typescript-eslint/consistent-type-definitions
#### Enabled=false
#### Warning=true
#### DisplayName=consistent-type-definitions
#### HelpText
  \-


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSCTI
### Default
#### OriginalId=@typescript-eslint/consistent-type-imports
#### Enabled=false
#### Warning=true
#### DisplayName=consistent-type-imports
#### HelpText
  This rule aims to standardize the use of type imports style across the codebase.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSDN
### Default
#### OriginalId=@typescript-eslint/dot-notation
#### Enabled=false
#### Warning=true
#### DisplayName=dot-notation
#### HelpText
  This rule extends the base eslint/dot-notation rule. It adds: Support for optionally ignoring computed private and/or protected member access andompatibility with TypeScript's noPropertyAccessFromIndexSignature option.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major
- __eslint_param__={ "allowKeywords": true }


## ESLINT_TSEFRT
### Default
#### OriginalId=@typescript-eslint/explicit-function-return-type
#### Enabled=false
#### Warning=true
#### DisplayName=explicit-function-return-type
#### HelpText
  This rule aims to ensure that the values returned from functions are of the expected type.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSEMA
### Default
#### OriginalId=@typescript-eslint/explicit-member-accessibility
#### Enabled=false
#### Warning=true
#### DisplayName=explicit-member-accessibility
#### HelpText
  This rule aims to make code more readable and explicit about who can use which properties.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSEMBT
### Default
#### OriginalId=@typescript-eslint/explicit-module-boundary-types
#### Enabled=false
#### Warning=true
#### DisplayName=explicit-module-boundary-types
#### HelpText
  This rule aims to ensure that the values returned from a module are of the expected type.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSFCS
### Default
#### OriginalId=@typescript-eslint/func-call-spacing
#### Enabled=false
#### Warning=true
#### DisplayName=func-call-spacing
#### HelpText
  This rule extends the base eslint/func-call-spacing rule. It adds support for generic type parameters on function calls.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Possible Errors

#### Settings
- Priority=Major
- __eslint_param__="never"


## ESLINT_TSI
### Default
#### OriginalId=@typescript-eslint/indent
#### Enabled=false
#### Warning=true
#### DisplayName=indent
#### HelpText
  This rule extends the base eslint/indent rule. It adds support for TypeScript nodes.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__=2


## ESLINT_TSID
### Default
#### OriginalId=@typescript-eslint/init-declarations
#### Enabled=false
#### Warning=true
#### DisplayName=init-declarations
#### HelpText
  This rule extends the base eslint/init-declarations rule. It adds support for TypeScript's declare variables.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Variables

#### Settings
- Priority=Major
- __eslint_param__={ "ignoreForLoopInit": true }


## ESLINT_TSKS
### Default
#### OriginalId=@typescript-eslint/keyword-spacing
#### Enabled=false
#### Warning=true
#### DisplayName=keyword-spacing
#### HelpText
  This rule extends the base eslint/keyword-spacing rule. This version adds support for generic type parameters on function calls.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__={ "before": true, "after": true, "overrides": {} }


## ESLINT_TSLBCM
### Default
#### OriginalId=@typescript-eslint/lines-between-class-members
#### Enabled=false
#### Warning=true
#### DisplayName=lines-between-class-members
#### HelpText
  This rule extends the base eslint/lines-between-class-members rule. It adds support for ignoring overload methods in a class.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="always"


## ESLINT_TSMDS
### Default
#### OriginalId=@typescript-eslint/member-delimiter-style
#### Enabled=false
#### Warning=true
#### DisplayName=member-delimiter-style
#### HelpText
  This rule aims to standardize the way interface and type literal members are delimited.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Stylistic Issues

#### Settings
- Priority=Major


## ESLINT_TSMO
### Default
#### OriginalId=@typescript-eslint/member-ordering
#### Enabled=false
#### Warning=true
#### DisplayName=member-ordering
#### HelpText
  This rule aims to standardize the way class declarations, class expressions, interfaces and type literals are structured and ordered.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Stylistic Issues

#### Settings
- Priority=Major


## ESLINT_TSMSS
### Default
#### OriginalId=@typescript-eslint/method-signature-style
#### Enabled=false
#### Warning=true
#### DisplayName=method-signature-style
#### HelpText
  \-


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Stylistic Issues

#### Settings
- Priority=Major


## ESLINT_TSNAR
### Default
#### OriginalId=@typescript-eslint/no-array-constructor
#### Enabled=false
#### Warning=true
#### DisplayName=no-array-constructor
#### HelpText
  This rule extends the base eslint/no-array-constructor rule. It adds support for the generically typed Array constructor.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Stylistic Issues

#### Settings
- Priority=Major


## ESLINT_TSNBTS
### Default
#### OriginalId=@typescript-eslint/no-base-to-string
#### Enabled=false
#### Warning=true
#### DisplayName=no-base-to-string
#### HelpText
  This rule prevents accidentally defaulting to the base Object .toString() method.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Possible Errors

#### Settings
- Priority=Major


## ESLINT_TSNC
### Default
#### OriginalId=@typescript-eslint/naming-convention
#### Enabled=false
#### Warning=true
#### DisplayName=naming-convention
#### HelpText
  This rule allows you to enforce conventions for any identifier, using granular selectors to create a fine-grained style guide.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSNCNNA
### Default
#### OriginalId=@typescript-eslint/no-confusing-non-null-assertion
#### Enabled=false
#### Warning=true
#### DisplayName=no-confusing-non-null-assertion
#### HelpText
  Using a non-null assertion (!) next to an assign or equals check (= or == or ===) creates code that is confusing as it looks similar to a not equals check (!= !==).


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSNCVE
### Default
#### OriginalId=@typescript-eslint/no-confusing-void-expression
#### Enabled=false
#### Warning=true
#### DisplayName=no-confusing-void-expression
#### HelpText
  This rule provides automatic fixes for most common cases.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Possible Errors

#### Settings
- Priority=Major


## ESLINT_TSNDCM
### Default
#### OriginalId=@typescript-eslint/no-dupe-class-members
#### Enabled=true
#### Warning=true
#### DisplayName=no-dupe-class-members
#### HelpText
  This rule extends the base eslint/no-dupe-class-members rule. It adds support for TypeScript's method overload definitions.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Possible Errors

#### Settings
- Priority=Major


## ESLINT_TSNDD
### Default
#### OriginalId=@typescript-eslint/no-dynamic-delete
#### Enabled=false
#### Warning=true
#### DisplayName=no-dynamic-delete
#### HelpText
  Using the delete operator on keys that aren't runtime constants could be a sign that you're using the wrong data structures. Using Objects with added and removed keys can cause occasional edge case bugs, such as if a key is named "hasOwnProperty". Consider using a Map or Set if you’re storing collections of objects.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Possible Errors

#### Settings
- Priority=Major


## ESLINT_TSNDI
### Default
#### OriginalId=@typescript-eslint/no-duplicate-imports
#### Enabled=false
#### Warning=true
#### DisplayName=no-duplicate-imports
#### HelpText
  This rule extends the base eslint/no-duplicate-imports rule. This version adds support for type-only import and export.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Possible Errors

#### Settings
- Priority=Major
- __eslint_param__={ "includeExports": false }


## ESLINT_TSNEA
### Default
#### OriginalId=@typescript-eslint/no-explicit-any
#### Enabled=true
#### Warning=true
#### DisplayName=no-explicit-any
#### HelpText
  This rule doesn't allow any types to be defined. It aims to keep TypeScript maximally useful. TypeScript has a compiler flag for --noImplicitAny that will prevent an any type from being implied by the compiler, but doesn't prevent any from being explicitly used.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSNEC
### Default
#### OriginalId=@typescript-eslint/no-extraneous-class
#### Enabled=false
#### Warning=true
#### DisplayName=no-extraneous-class
#### HelpText
  Forbids the use of classes as namespaces. This rule warns when a class is accidentally used as a namespace.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Stylistic Issues

#### Settings
- Priority=Major


## ESLINT_TSNEF
### Default
#### OriginalId=@typescript-eslint/no-empty-function
#### Enabled=false
#### Warning=true
#### DisplayName=no-empty-function
#### HelpText
  This rule extends the base eslint/no-empty-function rule. It adds support for handling TypeScript specific code that would otherwise trigger the rule.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major
- __eslint_param__={ "allow": [] }


## ESLINT_TSNEI
### Default
#### OriginalId=@typescript-eslint/no-empty-interface
#### Enabled=true
#### Warning=true
#### DisplayName=no-empty-interface
#### HelpText
  This rule aims to ensure that only meaningful interfaces are declared in the code.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Possible Errors

#### Settings
- Priority=Major


## ESLINT_TSNENNA
### Default
#### OriginalId=@typescript-eslint/no-extra-non-null-assertion
#### Enabled=true
#### Warning=true
#### DisplayName=no-extra-non-null-assertion
#### HelpText
  Disallow extra non-null assertion.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSNEP
### Default
#### OriginalId=@typescript-eslint/no-extra-parens
#### Enabled=true
#### Warning=true
#### DisplayName=no-extra-parens
#### HelpText
  This rule extends the base eslint/no-extra-parens rule. It adds support for TypeScript type assertions.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Possible Errors

#### Settings
- Priority=Major
- __eslint_param__="all"


## ESLINT_TSNES
### Default
#### OriginalId=@typescript-eslint/no-extra-semi
#### Enabled=true
#### Warning=true
#### DisplayName=no-extra-semi
#### HelpText
  This rule extends the base eslint/no-extra-semi rule. It adds support for class properties.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Possible Errors

#### Settings
- Priority=Major


## ESLINT_TSNFIA
### Default
#### OriginalId=@typescript-eslint/no-for-in-array
#### Enabled=true
#### Warning=true
#### DisplayName=no-for-in-array
#### HelpText
  A for-in loop (for (var k in o)) iterates over the properties of an Object. While it is legal to use for-in loops with array types, it is not common. for-in will iterate over the indices of the array as strings, omitting any "holes" in the array. More common is to use for-of, which iterates over the values of an array.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Possible Errors

#### Settings
- Priority=Major


## ESLINT_TSNFP
### Default
#### OriginalId=@typescript-eslint/no-floating-promises
#### Enabled=true
#### Warning=true
#### DisplayName=no-floating-promises
#### HelpText
  Requires Promise-like values to be handled appropriately. This rule forbids usage of Promise-like values in statements without handling their errors appropriately. Unhandled promises can cause several issues, such as improperly sequenced operations, ignored Promise rejections and more. Valid ways of handling a Promise-valued statement include awaiting, returning, and either calling .then() with two arguments or .catch() with one argument.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Possible Errors

#### Settings
- Priority=Major


## ESLINT_TSNIAC
### Default
#### OriginalId=@typescript-eslint/no-implicit-any-catch
#### Enabled=true
#### Warning=true
#### DisplayName=no-implicit-any-catch
#### HelpText
  This rule requires an explicit type to be declared on a catch clause variable.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Possible Errors

#### Settings
- Priority=Major


## ESLINT_TSNIE
### Default
#### OriginalId=@typescript-eslint/no-implied-eval
#### Enabled=false
#### Warning=true
#### DisplayName=no-implied-eval
#### HelpText
  It's considered a good practice to avoid using eval(). There are security and performance implications involved with doing so, which is why many linters recommend disallowing eval(). However, there are some other ways to pass a string and have it interpreted as JavaScript code that have similar concerns.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSNIT
### Default
#### OriginalId=@typescript-eslint/no-inferrable-types
#### Enabled=false
#### Warning=true
#### DisplayName=no-inferrable-types
#### HelpText
  This rule disallows explicit type declarations on parameters, variables and properties where the type can be easily inferred from its value.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSNIVT
### Default
#### OriginalId=@typescript-eslint/no-invalid-void-type
#### Enabled=false
#### Warning=true
#### DisplayName=no-invalid-void-type
#### HelpText
  This rule aims to ensure that the void type is only used in valid places.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Variables

#### Settings
- Priority=Major


## ESLINT_TSNLF
### Default
#### OriginalId=@typescript-eslint/no-loop-func
#### Enabled=false
#### Warning=true
#### DisplayName=no-loop-func
#### HelpText
  This rule extends the base eslint/no-loop-func rule. It adds support for TypeScript types.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSNMN
### Default
#### OriginalId=@typescript-eslint/no-magic-numbers
#### Enabled=true
#### Warning=true
#### DisplayName=no-magic-numbers
#### HelpText
  This rule extends the base eslint/no-magic-numbers rule. It adds support for: numeric literal types, enum members, and readonly class properties.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major
- __eslint_param__={ "ignore": [  ],"ignoreArrayIndexes": false,"enforceConst": false,"detectObjects": false }


## ESLINT_TSNMP
### Default
#### OriginalId=@typescript-eslint/no-misused-promises
#### Enabled=true
#### Warning=true
#### DisplayName=no-misused-promises
#### HelpText
  This rule forbids using promises in places where the TypeScript compiler allows them but they are not handled properly. These situations can often arise due to a missing await keyword or just a misunderstanding of the way async functions are handled/awaited.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Possible Errors

#### Settings
- Priority=Major


## ESLINT_TSNMVO
### Default
#### OriginalId=@typescript-eslint/no-meaningless-void-operator
#### Enabled=false
#### Warning=true
#### DisplayName=no-meaningless-void-operator
#### HelpText
  The void operator is a useful tool to convey the programmer's intent to discard a value. For example, it is recommended as one way of suppressing @typescript-eslint/no-floating-promises instead of adding .catch() to a promise.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Variables

#### Settings
- Priority=Major


## ESLINT_TSNMW
### Default
#### OriginalId=@typescript-eslint/no-misused-new
#### Enabled=true
#### Warning=true
#### DisplayName=no-misused-new
#### HelpText
  Warns on apparent attempts to define constructors for interfaces or new for classes.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Variables

#### Settings
- Priority=Major


## ESLINT_TSNN
### Default
#### OriginalId=@typescript-eslint/no-namespace
#### Enabled=true
#### Warning=true
#### DisplayName=no-namespace
#### HelpText
  This rule aims to standardize the way modules are declared.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSNNNA
### Default
#### OriginalId=@typescript-eslint/no-non-null-assertion
#### Enabled=false
#### Warning=true
#### DisplayName=no-non-null-assertion
#### HelpText
  Using non-null assertions cancels the benefits of the strict null-checking mode.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSNNNANC
### Default
#### OriginalId=@typescript-eslint/no-non-null-asserted-nullish-coalescing
#### Enabled=true
#### Warning=true
#### DisplayName=no-non-null-asserted-nullish-coalescing
#### HelpText
  The nullish coalescing operator is designed to provide a default value when dealing with null or undefined. Using non-null assertions in the left operand of the nullish coalescing operator is redundant.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSNNNAOC
### Default
#### OriginalId=@typescript-eslint/no-non-null-asserted-optional-chain
#### Enabled=true
#### Warning=true
#### DisplayName=no-non-null-asserted-optional-chain
#### HelpText
  Optional chain expressions are designed to return undefined if the optional property is nullish. Using non-null assertions after an optional chain expression is wrong, and introduces a serious type safety hole into your code.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Possible Errors

#### Settings
- Priority=Major


## ESLINT_TSNNTAS
### Default
#### OriginalId=@typescript-eslint/non-nullable-type-assertion-style
#### Enabled=false
#### Warning=true
#### DisplayName=non-nullable-type-assertion-style
#### HelpText
  This rule detects when an as cast is doing the same job as a ! would, and suggests fixing the code to be an !.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Possible Errors

#### Settings
- Priority=Major


## ESLINT_TSNPP
### Default
#### OriginalId=@typescript-eslint/no-parameter-properties
#### Enabled=false
#### Warning=true
#### DisplayName=no-parameter-properties
#### HelpText
  This rule disallows the use of parameter properties in constructors, forcing the user to explicitly declare all properties in the class.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSNR
### Default
#### OriginalId=@typescript-eslint/no-redeclare
#### Enabled=true
#### Warning=true
#### DisplayName=no-redeclare
#### HelpText
  This rule extends the base eslint/no-redeclare rule. It adds support for TypeScript function overloads, and declaration merging.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major
- __eslint_param__={ "builtinGlobals": false }


## ESLINT_TSNRI
### Default
#### OriginalId=@typescript-eslint/no-restricted-imports
#### Enabled=false
#### Warning=true
#### DisplayName=no-restricted-imports
#### HelpText
  This rule extends the base eslint/no-restricted-imports rule.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Possible Errors

#### Settings
- Priority=Major
- __eslint_param__={ "paths": [ "exampleImport1", "exampleImport2" ] }


## ESLINT_TSNS
### Default
#### OriginalId=@typescript-eslint/no-shadow
#### Enabled=false
#### Warning=true
#### DisplayName=no-shadow
#### HelpText
  This rule extends the base eslint/no-shadow rule. It adds support for TypeScript's this parameters and global augmentation, and adds options for TypeScript features.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Variables

#### Settings
- Priority=Major


## ESLINT_TSNTA
### Default
#### OriginalId=@typescript-eslint/no-this-alias
#### Enabled=true
#### Warning=true
#### DisplayName=no-this-alias
#### HelpText
  This rule prohibits assigning variables to this.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Variables

#### Settings
- Priority=Major


## ESLINT_TSNTAL
### Default
#### OriginalId=@typescript-eslint/no-type-alias
#### Enabled=false
#### Warning=true
#### DisplayName=no-type-alias
#### HelpText
  Disallow the use of type aliases.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Variables

#### Settings
- Priority=Major


## ESLINT_TSNTL
### Default
#### OriginalId=@typescript-eslint/no-throw-literal
#### Enabled=false
#### Warning=true
#### DisplayName=no-throw-literal
#### HelpText
  This rule is aimed at maintaining consistency when throwing exception by disallowing to throw literals and other expressions which cannot possibly be an Error object.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSNUA
### Default
#### OriginalId=@typescript-eslint/no-unsafe-argument
#### Enabled=true
#### Warning=true
#### DisplayName=no-unsafe-argument
#### HelpText
  This rule disallows calling a function with any in its arguments, and it will disallow spreading any\[\]. This rule also disallows spreading a tuple type with one of its elements typed as any. This rule also compares the argument's type to the variable's type to ensure you don't pass an unsafe any in a generic position to a receiver that's expecting a specific type. For example, it will error if you assign Set any to an argument declared as Set string.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Possible Errors

#### Settings
- Priority=Major


## ESLINT_TSNUAS
### Default
#### OriginalId=@typescript-eslint/no-unsafe-assignment
#### Enabled=true
#### Warning=true
#### DisplayName=no-unsafe-assignment
#### HelpText
  This rule disallows assigning any to a variable, and assigning any\[\] to an array destructuring. This rule also compares the assigned type to the variable's type to ensure you don't assign an unsafe any in a generic position to a receiver that's expecting a specific type. For example, it will error if you assign Set any to a variable declared as Set string.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Possible Errors

#### Settings
- Priority=Major


## ESLINT_TSNUBD
### Default
#### OriginalId=@typescript-eslint/no-use-before-define
#### Enabled=false
#### Warning=true
#### DisplayName=no-use-before-define
#### HelpText
  This rule extends the base eslint/no-use-before-define rule. It adds support for type, interface and enum declarations.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Variables

#### Settings
- Priority=Major
- __eslint_param__={ "functions": true,"classes": true,"variables": true,"enums": true,"typedefs": true,"ignoreTypeReferences": true}


## ESLINT_TSNUBLC
### Default
#### OriginalId=@typescript-eslint/no-unnecessary-boolean-literal-compare
#### Enabled=false
#### Warning=true
#### DisplayName=no-unnecessary-boolean-literal-compares
#### HelpText
  This rule ensures that you do not include unnecessary comparisons with boolean literals. A comparison is considered unnecessary if it checks a boolean literal against any variable with just the boolean type. A comparison is not considered unnecessary if the type is a union of booleans (string | boolean, someObject | boolean).


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSNUC
### Default
#### OriginalId=@typescript-eslint/no-unnecessary-condition
#### Enabled=false
#### Warning=true
#### DisplayName=no-unnecessary-condition
#### HelpText
  Any expression being used as a condition must be able to evaluate as truthy or falsy in order to be considered "necessary". Conversely, any expression that always evaluates to truthy or always evaluates to falsy, as determined by the type of the expression, is considered unnecessary and will be flagged by this rule.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Variables

#### Settings
- Priority=Major


## ESLINT_TSNUCA
### Default
#### OriginalId=@typescript-eslint/no-unsafe-call
#### Enabled=true
#### Warning=true
#### DisplayName=no-unsafe-call
#### HelpText
  This rule disallows calling any variable that is typed as any.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Possible Errors

#### Settings
- Priority=Major


## ESLINT_TSNUE
### Default
#### OriginalId=@typescript-eslint/no-unused-expressions
#### Enabled=false
#### Warning=true
#### DisplayName=no-unused-expressions
#### HelpText
  This rule extends the base eslint/no-unused-expressions rule. It adds support for optional call expressions x?.(), and directive in module declarations.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major
- __eslint_param__={ "allowShortCircuit": false,"allowTernary": false,"allowTaggedTemplates": false }


## ESLINT_TSNUMA
### Default
#### OriginalId=@typescript-eslint/no-unsafe-member-access
#### Enabled=true
#### Warning=true
#### DisplayName=no-unsafe-member-access
#### HelpText
  This rule disallows member access on any variable that is typed as any.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Possible Errors

#### Settings
- Priority=Major


## ESLINT_TSNUQ
### Default
#### OriginalId=@typescript-eslint/no-unnecessary-qualifier
#### Enabled=false
#### Warning=true
#### DisplayName=no-unnecessary-qualifier
#### HelpText
  This rule aims to let users know when a namespace or enum qualifier is unnecessary, whether used for a type or for a value.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Variables

#### Settings
- Priority=Major


## ESLINT_TSNUR
### Default
#### OriginalId=@typescript-eslint/no-unsafe-return
#### Enabled=true
#### Warning=true
#### DisplayName=no-unsafe-return
#### HelpText
  This rule disallows returning any or any\[\] from a function. This rule also compares the return type to the function's declared/inferred return type to ensure you don't return an unsafe any in a generic position to a receiver that's expecting a specific type. For example, it will error if you return Set any from a function declared as returning Set string.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Possible Errors

#### Settings
- Priority=Major


## ESLINT_TSNUTA
### Default
#### OriginalId=@typescript-eslint/no-unnecessary-type-arguments
#### Enabled=true
#### Warning=true
#### DisplayName=no-unnecessary-type-arguments
#### HelpText
  Type parameters in TypeScript may specify a default value.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Variables

#### Settings
- Priority=Major


## ESLINT_TSNUTAS
### Default
#### OriginalId=@typescript-eslint/no-unnecessary-type-assertion
#### Enabled=true
#### Warning=true
#### DisplayName=no-unnecessary-type-assertion
#### HelpText
  This rule aims to prevent unnecessary type assertions.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Variables

#### Settings
- Priority=Major


## ESLINT_TSNUTC
### Default
#### OriginalId=@typescript-eslint/no-unnecessary-type-constraint
#### Enabled=true
#### Warning=true
#### DisplayName=no-unnecessary-type-constraint
#### HelpText
  \-


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Variables

#### Settings
- Priority=Major


## ESLINT_TSNUV
### Default
#### OriginalId=@typescript-eslint/no-unused-vars
#### Enabled=true
#### Warning=true
#### DisplayName=no-unused-vars
#### HelpText
  This rule extends the base eslint/no-unused-vars rule. It adds support for TypeScript features, such as types.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Variables

#### Settings
- Priority=Major
- __eslint_param__={ "vars": "all", "args": "after-used" }


## ESLINT_TSNVR
### Default
#### OriginalId=@typescript-eslint/no-var-requires
#### Enabled=true
#### Warning=true
#### DisplayName=no-var-requires
#### HelpText
  \-


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Stylistic Issues

#### Settings
- Priority=Major


## ESLINT_TSOCS
### Default
#### OriginalId=@typescript-eslint/object-curly-spacing
#### Enabled=false
#### Warning=true
#### DisplayName=object-curly-spacing
#### HelpText
  This rule extends the base eslint/object-curly-spacing rule. It adds support for TypeScript's object types.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Stylistic Issues

#### Settings
- Priority=Major


## ESLINT_TSPAC
### Default
#### OriginalId=@typescript-eslint/prefer-as-const
#### Enabled=true
#### Warning=true
#### DisplayName=prefer-as-const
#### HelpText
  This rule recommends usage of const assertion when type primitive value is equal to type.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Possible Errors

#### Settings
- Priority=Major


## ESLINT_TSPEI
### Default
#### OriginalId=@typescript-eslint/prefer-enum-initializers
#### Enabled=false
#### Warning=true
#### DisplayName=prefer-enum-initializers
#### HelpText
  This rule recommends having each enums member value explicitly initialized.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Variables

#### Settings
- Priority=Major


## ESLINT_TSPFA
### Default
#### OriginalId=@typescript-eslint/promise-function-async
#### Enabled=false
#### Warning=true
#### DisplayName=promise-function-async
#### HelpText
  Requires any function or method that returns a Promise to be marked async.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Possible Errors

#### Settings
- Priority=Major


## ESLINT_TSPFO
### Default
#### OriginalId=@typescript-eslint/prefer-for-of
#### Enabled=false
#### Warning=true
#### DisplayName=prefer-for-of
#### HelpText
  For cases where the index is only used to read from the array being iterated, a for-of loop is easier to read and write.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSPFT
### Default
#### OriginalId=@typescript-eslint/prefer-function-type
#### Enabled=false
#### Warning=true
#### DisplayName=prefer-function-type
#### HelpText
  This rule suggests using a function type instead of an interface or object type literal with a single call signature.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSPI
### Default
#### OriginalId=@typescript-eslint/prefer-includes
#### Enabled=false
#### Warning=true
#### DisplayName=prefer-includes
#### HelpText
  This rule is aimed at suggesting includes method if indexOf method was used to check whether an object contains an arbitrary value or not. If the receiver object of the indexOf method call has includes method and the two methods have the same parameters, this rule does suggestion. There are such types: String, Array, ReadonlyArray, and typed arrays.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSPLBS
### Default
#### OriginalId=@typescript-eslint/padding-line-between-statements
#### Enabled=false
#### Warning=true
#### DisplayName=padding-line-between-statements
#### HelpText
  This rule extends the base eslint/padding-line-between-statements rule. It adds support for TypeScript constructs such as interface and type.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Stylistic Issues

#### Settings
- Priority=Major


## ESLINT_TSPLEM
### Default
#### OriginalId=@typescript-eslint/prefer-literal-enum-member
#### Enabled=false
#### Warning=true
#### DisplayName=prefer-literal-enum-member
#### HelpText
  This rule is meant to prevent unexpected results in code by requiring the use of literal values as enum members to prevent unexpected runtime behavior. Template literals, arrays, objects, constructors, and all other expression types can end up using a variable from its scope or the parent scope, which can result in the same unexpected behavior at runtime.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSPNC
### Default
#### OriginalId=@typescript-eslint/prefer-nullish-coalescing
#### Enabled=false
#### Warning=true
#### DisplayName=prefer-nullish-coalescing
#### HelpText
  TypeScript 3.7 added support for the nullish coalescing operator. This operator allows you to safely cascade a value when dealing with null or undefined.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSPNK
### Default
#### OriginalId=@typescript-eslint/prefer-namespace-keyword
#### Enabled=true
#### Warning=true
#### DisplayName=prefer-namespace-keyword
#### HelpText
  This rule aims to standardize the way modules are declared.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSPOC
### Default
#### OriginalId=@typescript-eslint/prefer-optional-chain
#### Enabled=false
#### Warning=true
#### DisplayName=prefer-optional-chain
#### HelpText
  This rule aims enforce the usage of the safer operator.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSPR
### Default
#### OriginalId=@typescript-eslint/prefer-readonly
#### Enabled=false
#### Warning=true
#### DisplayName=prefer-readonly
#### HelpText
  Member variables with the privacy private are never permitted to be modified outside of their declaring class. If that class never modifies their value, they may safely be marked as readonly.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSPRE
### Default
#### OriginalId=@typescript-eslint/prefer-regexp-exec
#### Enabled=false
#### Warning=true
#### DisplayName=prefer-regexp-exec
#### HelpText
  This rule is aimed at enforcing a consistent way to apply regular expressions to strings.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSPRPT
### Default
#### OriginalId=@typescript-eslint/prefer-readonly-parameter-types
#### Enabled=false
#### Warning=true
#### DisplayName=prefer-readonly-parameter-types
#### HelpText
  This rule allows you to enforce that function parameters resolve to readonly types.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSPRTP
### Default
#### OriginalId=@typescript-eslint/prefer-reduce-type-parameter
#### Enabled=false
#### Warning=true
#### DisplayName=prefer-reduce-type-parameter
#### HelpText
  This rule looks for calls to Array\#reduce, and warns if an initial value is being passed and casted, suggesting instead to pass the cast type to Array\#reduce as its generic parameter.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSPRTT
### Default
#### OriginalId=@typescript-eslint/prefer-return-this-type
#### Enabled=false
#### Warning=true
#### DisplayName=prefer-return-this-type
#### HelpText
  \-


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSPSSEW
### Default
#### OriginalId=@typescript-eslint/prefer-string-starts-ends-with
#### Enabled=false
#### Warning=true
#### DisplayName=prefer-string-starts-ends-with
#### HelpText
  This rule is aimed at enforcing a consistent way to check whether a string starts or ends with a specific string.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSPTEE
### Default
#### OriginalId=@typescript-eslint/prefer-ts-expect-error
#### Enabled=false
#### Warning=true
#### DisplayName=prefer-ts-expect-error
#### HelpText
  This rule looks for usages of @ts-ignore, and flags them to be replaced with @ts-expect-error.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSQ
### Default
#### OriginalId=@typescript-eslint/quotes
#### Enabled=false
#### Warning=true
#### DisplayName=quotes
#### HelpText
  This rule extends the base eslint/quotes rule. It adds support for TypeScript features which allow quoted names, but not backtick quoted names.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="double"


## ESLINT_TSRA
### Default
#### OriginalId=@typescript-eslint/require-await
#### Enabled=false
#### Warning=true
#### DisplayName=require-await
#### HelpText
  This rule extends the base eslint/require-await rule. It uses type information to add support for async functions that return a Promise.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSRASC
### Default
#### OriginalId=@typescript-eslint/require-array-sort-compare
#### Enabled=false
#### Warning=true
#### DisplayName=require-array-sort-compare
#### HelpText
  This rule aims to ensure all calls of the native Array\#sort method provide a compareFunction, while ignoring calls to user-defined sort methods.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Possible Errors

#### Settings
- Priority=Major


## ESLINT_TSRPO
### Default
#### OriginalId=@typescript-eslint/restrict-plus-operands
#### Enabled=true
#### Warning=true
#### DisplayName=restrict-plus-operands
#### HelpText
  \-


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Possible Errors

#### Settings
- Priority=Major


## ESLINT_TSRTE
### Default
#### OriginalId=@typescript-eslint/restrict-template-expressions
#### Enabled=false
#### Warning=true
#### DisplayName=restrict-template-expressions
#### HelpText
  \-


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSS
### Default
#### OriginalId=@typescript-eslint/semi
#### Enabled=false
#### Warning=true
#### DisplayName=semi
#### HelpText
  This rule extends the base eslint/semi rule. It adds support for TypeScript features that require semicolons.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="always"


## ESLINT_TSSBE
### Default
#### OriginalId=@typescript-eslint/strict-boolean-expressions
#### Enabled=false
#### Warning=true
#### DisplayName=strict-boolean-expressions
#### HelpText
  Forbids usage of non-boolean types in expressions where a boolean is expected. boolean and never types are always allowed. Additional types which are considered safe in a boolean context can be configured via options.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSSBFP
### Default
#### OriginalId=@typescript-eslint/space-before-function-paren
#### Enabled=false
#### Warning=true
#### DisplayName=space-before-function-paren
#### HelpText
  This rule extends the base eslint/space-before-function-paren rule. It adds support for generic type parameters on function calls.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__="always"


## ESLINT_TSSEC
### Default
#### OriginalId=@typescript-eslint/switch-exhaustiveness-check
#### Enabled=false
#### Warning=true
#### DisplayName=switch-exhaustiveness-check
#### HelpText
  Union type may have a lot of parts. It's easy to forget to consider all cases in switch. This rule reminds which parts are missing. If domain of the problem requires to have only a partial switch, developer may explicitly add a default clause.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSSIO
### Default
#### OriginalId=@typescript-eslint/space-infix-ops
#### Enabled=false
#### Warning=true
#### DisplayName=space-infix-ops
#### HelpText
  This rule extends the base eslint/space-infix-ops rule. It also add support for enum members.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Stylistic Issues

#### Settings
- Priority=Major
- __eslint_param__={ "int32Hint": false }


## ESLINT_TSSTUIM
### Default
#### OriginalId=@typescript-eslint/sort-type-union-intersection-members
#### Enabled=false
#### Warning=true
#### DisplayName=sort-type-union-intersection-members
#### HelpText
  \-


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Variables

#### Settings
- Priority=Major


## ESLINT_TST
### Default
#### OriginalId=@typescript-eslint/typedef
#### Enabled=false
#### Warning=true
#### DisplayName=typedef
#### HelpText
  This rule can enforce type annotations in locations regardless of whether they're required. This is typically used to maintain consistency for element types that sometimes require them.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Stylistic Issues

#### Settings
- Priority=Major


## ESLINT_TSTAS
### Default
#### OriginalId=@typescript-eslint/type-annotation-spacing
#### Enabled=false
#### Warning=true
#### DisplayName=type-annotation-spacing
#### HelpText
  This rule aims to enforce specific spacing patterns around type annotations and function types in type literals.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Stylistic Issues

#### Settings
- Priority=Major


## ESLINT_TSTSR
### Default
#### OriginalId=@typescript-eslint/triple-slash-reference
#### Enabled=true
#### Warning=true
#### DisplayName=triple-slash-reference
#### HelpText
  \-


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSUM
### Default
#### OriginalId=@typescript-eslint/unbound-method
#### Enabled=true
#### Warning=true
#### DisplayName=unbound-method
#### HelpText
  Warns when a method is used outside of a method call.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Best Practices

#### Settings
- Priority=Major


## ESLINT_TSUS
### Default
#### OriginalId=@typescript-eslint/unified-signatures
#### Enabled=true
#### Warning=true
#### DisplayName=unified-signatures
#### HelpText
  This rule aims to keep the source code as maintainable as possible by reducing the amount of overloads.


#### Tags
- /language/TypeScript
- /tool/ESLINT
- /general/TS Stylistic Issues

#### Settings
- Priority=Major
