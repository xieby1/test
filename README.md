# xieby1's Test Repository

## Compilation and Testing

Here is an example of running all tests with tag *x86* with an i386 emulator (I call it "test command prefix") *qemu-i386*,

```shell
# Compiling
cmake -G "Unix Makefile" .
make
# test
TEST_CMD_PRE=qemu-i386 ctest -L "x86"
```

Currently **directly** using environment variables at CTest runtime seems impossible, because all variables has been expanded at the time CTestTestFile.cmake is generated. So I choose to add a `runtest.cmake` script to alleviate this problem, refer to [How to pass command-line arguments in CTest at runtime](https://stackoverflow.com/questions/28812533/how-to-pass-command-line-arguments-in-ctest-at-runtime), though it is not graceful. And here are two people met the same problem,

* [add_test : expand environment variable at running time](http://cmake.3232098.n2.nabble.com/add-test-expand-environment-variable-at-running-time-td5526918.html)
* [runtime env variables in ctest](http://cmake.3232098.n2.nabble.com/runtime-env-variables-in-ctest-td7589947.html)

## Naming&Categorization Convention

### Directory

**Snippets in General Use**:

* `include/`

**Test Categories**:

Test snippets are categorized by programming stack (programming abstraction layers, computer architectures, ...), from very low level hardware to very high level software,

* `sftwr/`: test software features
* `c.f/`: test C-family language features
  * `asm/`: test inline assembly features
* `glib/`: test glib features
* `libc/`: test libc(GNU implementation, glibc) features
* `asm/`: test instruction (assembly or machine code) features, **Noted**: Here contains **only** pure assembly snippets. C code inline assembly snippets are in `c.f/asm/`.
  * `mips/`
  * `x86/`

**Note**: the directory name suffix `.f` means family, indicating this directory containing a family of some kind of test. E.g. `print.f/` contains the tests for print family, like printf, sprintf, dprintf...

### File

The file name simply describes the test purpose.

### CTest Labels

* the goal of writing this test
  * `goal_test`: to test and determine XXX right or wrong.
  * `goal_learn`: to figure out and learn the features of XXX, it is like an experiment, not intended to prove XXX right or wrong.
* architecture
  * `arch_all`
  * `arch_x86`
* Programming Language
  * `lang_asm`: assembly, especially assembly without linking against standard libraries.
  * `lang_c`

## TODO: Content-Guided Categorization

* All kinds of `hello`