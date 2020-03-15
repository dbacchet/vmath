Compilation database support for Bazel
======================================

This folder contains rules and scripts to add support for generating the compile_commands.json using Bazel.

This is a modified version of the [bazel-compilation-database](https://github.com/grailbio/bazel-compilation-database) project, 
SHA:ad537aaf7fa96ecbd (Apache-2 license) and has been adapted to be used in our codebase.
Specifically:
* treat all `.h` files as C++
* replace the name of the compiler in case is a wrapper script (wrapped_clang --> clang)
