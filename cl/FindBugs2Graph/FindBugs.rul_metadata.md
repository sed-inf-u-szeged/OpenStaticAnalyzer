# TagMetadata
## general
### Experimental Rules
##### Summarized=true
##### Description
  Experimental and not fully vetted bug patterns

### Internationalization Rules
##### Summarized=true
##### Description
  code flaws having to do with internationalization and locale

### Security Code Guideline Rules
##### Summarized=true
##### Description
  code that is vulnerable to attacks from untrusted code

### Optimization Rules
##### Summarized=true
##### Description
  code that is not necessarily incorrect but may be inefficient

### Dodgy Code Rules
##### Summarized=true
##### Description
  code that is confusing, anomalous, or written in a way that leads itself to errors. Examples include dead local stores, switch fall through, unconfirmed casts, and redundant null check of value known to be null. More false positives accepted. In previous versions of SpotBugs, this category was known as Style.

### Multithreaded Correctness Rules
##### Summarized=true
##### Description
  code flaws having to do with threads, locks, and volatiles

### Bad Practice Rules
##### Summarized=true
##### Description
  Violations of recommended and essential coding practice. Examples include hash code and equals problems, cloneable idiom, dropped exceptions, Serializable problems, and misuse of finalize. We strive to make this analysis accurate, although some groups may not care about some of the bad practices.

### Vulnerability Rules
##### Summarized=true
##### Description
  A use of untrusted input in a way that could create a remotely exploitable security vulnerability.

### Correctness Rules
##### Summarized=true
##### Description
  Probable bug - an apparent coding mistake resulting in code that was probably not what the developer intended. We strive for a low false positive rate.
