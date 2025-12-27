# README

### Brief
_Minuet_ is a small language for simple utility programs. Unlike shell scripting dialects across systems, this language aims to look and behave nicer for the programmer.

### Design Principles
 - Concise and semi-familiar syntax
 - Dynamic, _strong_, null-safe typing
 - Imperative & functional
    - First class functions
    - Higher order functions & some closures?
 - Built-in data structures
    - Lists
    - Tuples
 - Built-in helper functions
 - Requires a `main` function

### Other Documentation
 - [Usage](/docs/usage.md)
 - [Grammar](/docs/grammar.md)
 - [VM](/docs/vm.md)

### Roadmap
 - `0.10.0`: Add tuple destructuring?
 - `0.11.0`: Add simple lambdas as 1st-class objects.
   - Add `fun [] uses [...] {}` syntax.
 - `0.12.0`: Add simple x64 JIT for pure, global functions taking integers.
   - Uses the `AsmJIT` framework.
   - Prototype JIT compiler using CFG IR, regalloc, etc.
   - Create a JIT compilation thread which runs in the background, adding a JIT version of a function when finished.
   - Add JIT / bytecode dispatch in `call` instruction.
