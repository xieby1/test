# xieby1's Test Repository

## Compilation and Testing

Here is an example of running all tests with tag *x86* with an i386 emulator (I call it "test command prefix") *qemu-i386*,

```shell
# Noted: if prefix command is needed,
# set TEST_CMD_PRE before run `cmake -G ...`
# if you want to know more details see section
# "Why env vars should set before run cmake?"
export TEST_CMD_PRE=qemu-i386
cmake -G "Unix Makefile" .
ctest -L "x86"
```

### Why env vars should set before run cmake?

Currently CTestTestFile.cmake cannot handle environment variables, 

* [add_test : expand environment variable at running time](http://cmake.3232098.n2.nabble.com/add-test-expand-environment-variable-at-running-time-td5526918.html)
* [runtime env variables in ctest](http://cmake.3232098.n2.nabble.com/runtime-env-variables-in-ctest-td7589947.html)
* [How to pass command-line arguments in CTest at runtime](https://stackoverflow.com/questions/28812533/how-to-pass-command-line-arguments-in-ctest-at-runtime)
  * [CTest: forwarding command-line arguments to test executables](https://gitlab.kitware.com/cmake/cmake/-/issues/20470)

as a result, environment variables will be expanded at cmake time. So if a new prefix command should be added to the test, the environment variable `TEST_CMD_PRE` should be changed and then re-run cmake to generate correct CTestTestFile.cmake script.

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

## TODO: Content-Guided Categorization

* All kinds of `hello`