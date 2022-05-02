# ToolDescription
## Default
### ID=PythonMigrationChecker

# Includes
- Migration.rul_metadata.md

# Metrics
## MIG_AMBIGUOUS_IMPORT
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=The only acceptable syntax for relative imports is from .[module] import name
#### HelpText
  The only acceptable syntax for relative imports is from .\[module\] import name. All import forms not starting with . are interpreted as absolute imports.

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=40
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_BASESTRING
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=The builtin basestring abstract type was removed
#### HelpText
  The builtin basestring abstract type was removed. Use str instead.

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=15
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_BUILTIN_APPLY
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=Removed: apply()
#### HelpText
  Removed: apply(). Instead of apply(f, args) use f(\*args).

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=20
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_BUILTIN_CALLABLE
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=Removed callable()
#### HelpText
  Removed callable(). Instead of callable(f) you can use hasattr(f, '\_\_call\_\_').

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=10
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_BUILTIN_CMP
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=The cmp() function should be treated as gone
#### HelpText
  The cmp() function should be treated as gone, and the \_\_cmp\_\_() special method is no longer supported. Use \_\_lt\_\_() for sorting, \_\_eq\_\_() with \_\_hash\_\_(), and other rich comparisons as needed.

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=60
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_BUILTIN_COERCE
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=Removed coerce()
#### HelpText
  Removed coerce(). This function no longer serves a purpose now that classic classes are gone.

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=30
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_BUILTIN_EXECFILE
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=Removed execfile()
#### HelpText
  Removed execfile(). Instead of execfile(fn) use exec(open(fn).read()).

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=20
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_BUILTIN_FILE
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=Removed file
#### HelpText
  Removed file. Use open().

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=10
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_BUILTIN_INPUT
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=Old behavior of input()
#### HelpText
  To get the old behavior of input(), use eval(input()).

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=10
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_BUILTIN_INTERN
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=Moved intern() to sys.intern()
#### HelpText
  Moved intern() to sys.intern().

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=10
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_BUILTIN_LONG
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=Long renamed to int
#### HelpText
  Long renamed to int. That is, there is only one built-in integral type, named int; but it behaves mostly like the old long type.

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=10
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_BUILTIN_NEXT
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=The standard next() method has been renamed to __next__()
#### HelpText
  The standard next() method has been renamed to \_\_next\_\_().

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=10
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_BUILTIN_RAW_INPUT
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=Raw_input() was renamed to input()
#### HelpText
  Raw\_input() was renamed to input().

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=10
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_BUILTIN_REDUCE
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=Removed reduce()
#### HelpText
  Removed reduce(). Use functools.reduce() if you really need it; however, 99 percent of the time an explicit for loop is more readable.

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=30
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_BUILTIN_RELOAD
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=Removed reload()
#### HelpText
  Removed reload(). Use imp.reload().

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=10
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_BUILTIN_UNICODE
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=Rename unicode to str
#### HelpText
  Rename unicode to str.

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=10
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_BUILTIN_XRANGE
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=The range() now behaves like xrange() used to behave
#### HelpText
  The range() now behaves like xrange() used to behave, except it works with values of arbitrary size. The latter no longer exists.

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=10
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_DELETED_MODULE
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=Deleted module
#### HelpText
  Deleted module. Instead of %, use %.

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=120
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_FR_ELLIPSIS
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=Ellipsis spelling
#### HelpText
  The ellipsis must now be spelled as .... (Previously it could also be spelled as . . ., by a mere accident of the grammar.)

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=10
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_FR_EXCEPT
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=Except notation
#### HelpText
  You must now use except SomeException as variable instead of except SomeException, variable.

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=10
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_FR_EXEC
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=Exec is no longer a keyword
#### HelpText
  Exec is no longer a keyword; it remains as a function.

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=10
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_FR_GEN
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=List comprehension
#### HelpText
  List comprehensions no longer support the syntactic form \[... for var in item1, item2, ...\]. Use \[... for var in (item1, item2, ...)\] instead.

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=10
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_FR_INT_LITERAL
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=Integer literals no longer support a trailing l or L
#### HelpText
  Integer literals no longer support a trailing l or L. Octal literals are no longer of the form 0720; use 0o720 instead.

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=5
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_FR_NOT_EQ
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=Not equal notation
#### HelpText
  Removed &lt;&gt; (use != instead).

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=10
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_FR_PRINT
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=Print statement
#### HelpText
  The print statement has been replaced with a print() function.

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=10
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_FR_STR_LITERAL
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=String literals no longer support a leading u or U
#### HelpText
  String literals no longer support a leading u or U.

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=5
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_FR_TUPLE
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=Tuple parameter unpacking removed
#### HelpText
  Tuple parameter unpacking removed. You can no longer write def foo(a, (b, c)): .... Use def foo(a, b\_c): b, c = b\_c instead.

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=20
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_MM_ITERTOOLS
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=Removed itertools.ifilter(), itertools.izip(), and itertools.imap()
#### HelpText
  Removed itertools.ifilter(), itertools.izip(), and itertools.imap(), use the builtin filter(), map(), zip() functions instad. Also change itertools.ifilterfalse() to itertools.filterfalse().

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=20
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_MM_OPERATOR_ISCALLABLE
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=Removed operator.isCallable()
#### HelpText
  Removed operator.isCallable().

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=10
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_MM_OPERATOR_SEQUENCEINCLUDES
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=Removed operator.sequenceIncludes()
#### HelpText
  Removed operator.sequenceIncludes().

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=10
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_MM_OS
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=The functions os.tmpnam(), os.tempnam() and os.tmpfile() have been removed
#### HelpText
  The functions os.tmpnam(), os.tempnam() and os.tmpfile() have been removed in favor of the tempfile module.

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=30
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_MM_OS_GETCWDU
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=Rename os.getcwdu() to os.getcwd()
#### HelpText
  Rename os.getcwdu() to os.getcwd().

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=10
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_MM_RANDOM_JUMPAHEAD
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=Cleanup of the random module
#### HelpText
  Cleanup of the random module: removed the jumpahead() API.

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=60
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_MM_STRING
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=The string.letters and its friends (string.lowercase and string.uppercase) are gone
#### HelpText
  The string.letters and its friends (string.lowercase and string.uppercase) are gone. Use string.ascii\_letters etc. instead.

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=10
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_MM_SYS_EXC
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=Cleanup of the sys module
#### HelpText
  Cleanup of the sys module: removed sys.exc\_type, sys.exc\_value, sys.exc\_traceback. Use sys.exc\_info() instead.

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=30
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_MM_SYS_EXC_CLEAR
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=Removed sys.exc_clear()
#### HelpText
  Removed sys.exc\_clear().

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=120
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_MM_SYS_MAXINT
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=The sys.maxint constant was removed
#### HelpText
  The sys.maxint constant was removed, since there is no longer a limit to the value of integers. However, sys.maxsize can be used instead of it.

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=10
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_MM_TOKENIZE_GENERATE_TOKENS
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=The tokenize module has been changed to work with bytes
#### HelpText
  The tokenize module has been changed to work with bytes. The main entry point is now tokenize.tokenize(), instead of generate\_tokens.

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=30
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_MM_TYPES
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=Deleted member of type module
#### HelpText
  Removed member of type module. Change types.% to %.

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=10
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_MODULE_LEVEL_IMPORT_FROM
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=The from module import * syntax is only allowed at the module level
#### HelpText
  The from module import \* syntax is only allowed at the module level, no longer inside functions.

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=30
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_OM_ARRAY_READ
### Default
#### Enabled=false
#### Warning=true
#### DisplayName=Cleanup of the array.array type
#### HelpText
#### Tags
  - /tool/PythonMigrationChecker
  - /general/Migration Rules

  #### Settings
  - Debt=10
  - Priority=Minor

  ### python -> Default
  #### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_OM_ARRAY_WRITE
### Default
#### Enabled=false
#### Warning=true
#### DisplayName=Cleanup of the array.array type
#### HelpText
#### Tags
  - /tool/PythonMigrationChecker
  - /general/Migration Rules

  #### Settings
  - Debt=10
  - Priority=Minor

  ### python -> Default
  #### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_OM_DICT
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=Dict converted methods
#### HelpText
  The dict.iteritems() is converted to dict.items(), dict.iterkeys() to dict.keys(), and dict.itervalues() to dict.values(). Similarly, dict.viewitems(), dict.viewkeys() and dict.viewvalues() are converted respectively to dict.items(), dict.keys() and dict.values().

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=20
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_OM_DICT_HASKEY
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=Change the dict.has_key(key) to key in dict
#### HelpText
  Change the dict.has\_key(key) to key in dict.

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=10
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_OM_FUNCTION_OBJECT
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=The function attributes named func_X have been renamed to use the __X__ form
#### HelpText
  The function attributes named func\_X have been renamed to use the \_\_X\_\_ form. For example, func\_defaults renamed to \_\_defaults\_\_. Also meth.im\_func has been replaced to meth.\_\_func\_\_.

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=20
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_OM_GENERATOR_THROW
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=Fix the generator's throw() method
#### HelpText
  Fix the generator's throw() method.

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=60
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_OM_NONZERO
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=Rename __nonzero__() to __bool__()
#### HelpText
  Rename \_\_nonzero\_\_() to \_\_bool\_\_().

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=10
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_OM_TESTCASE
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=Deleted unittest methods
#### HelpText
  Replace the deprecated unittest method names with the correct ones: % to %

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=10
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_OM_WRAP_DICT
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=Dictionary methods dict.keys(), dict.items() and dict.values() return views instead of lists
#### HelpText
  Dictionary methods dict.keys(), dict.items() and dict.values() return views instead of lists. Wrap them in a call to list.

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=20
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_OS_METACLASS
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=Convert the old metaclass syntax to the new
#### HelpText
  Convert the old metaclass syntax (\_\_metaclass\_\_ = Meta in the class body) to the new (class X(metaclass=Meta)).

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=30
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_OS_RAISE
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=You must now use raise Exception(args) instead of raise Exception, args
#### HelpText
  You must now use raise Exception(args) instead of raise Exception, args.

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=10
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_STANDARD_ERROR
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=StandardError was removed
#### HelpText
  StandardError was removed.

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=60
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_STRING_CONVERSION
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=Removed backticks
#### HelpText
  Removed backticks (use repr() instead).

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=10
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_WRAP_FILTER
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=The filter() return iterator
#### HelpText
  The filter() return iterator. If you really need a list, a quick fix is e.g. list(filter(...)), but a better fix is often to use a list comprehension, or rewriting the code so it doesn't need a list at all.

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=60
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_WRAP_MAP
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=The map() returns an iterator
#### HelpText
  The map() returns an iterator. If you really need a list, a quick fix is e.g. list(map(...)), but a better fix is often to use a list comprehension, or rewriting the code so it doesn't need a list at all.

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=60
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_WRAP_RANGE
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=The range() returns an iterator
#### HelpText
  The range() returns an iterator. If you really need a list, a quick fix is e.g. list(range(...)), but a better fix is often to use a list comprehension, or rewriting the code so it doesn't need a list at all.

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=60
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker


## MIG_WRAP_ZIP
### Default
#### Enabled=true
#### Warning=true
#### DisplayName=The zip() now returns an iterator
#### HelpText
  The zip() now returns an iterator. If you really need a list, a quick fix is e.g. list(range(...)), but a better fix is often to use a list comprehension, or rewriting the code so it doesn't need a list at all.

#### Tags
- /tool/PythonMigrationChecker
- /general/Migration Rules

#### Settings
- Debt=60
- Priority=Minor

### python -> Default
#### Enabled=true
#### Tags
- /tool/PythonMigrationChecker
