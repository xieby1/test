# xieby1's Test Repository

## Naming&Categorization Convention

### Directory

**Snippets in General Use**:

* `include/`

**Test Categories**:

* `lang/`: test programming language features
* `libc/`: test libc(GNU implementation, glibc) features
* `glib/`: test glib features
* `x86Inst/`: test x86 instruction (assembly and machine code) features

**Note**: the directory name suffix `.f` means family, indicating this directory containing a family of some kind of test. E.g. `print.f/` contains the tests for print family, like printf, sprintf, dprintf...

### File

The file name simply describes the test purpose.