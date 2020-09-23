# xieby1's Test Repository

## Naming&Categorization Convention

### Directory

**Snippets in General Use**:

* `include/`

**Test Categories**:

* `c.f/`: test C-family language features
  * `asm/`: test inline assembly features
* `libc/`: test libc(GNU implementation, glibc) features
* `glib/`: test glib features
* `asm/`: test instruction (assembly or machine code) features, **Noted**: Here contains **only** pure assembly snippets. C code inline assembly snippets are in `c.f/asm/`.
  * `mips/`
  * `x86/`
* `sftwr/`: test software features

**Note**: the directory name suffix `.f` means family, indicating this directory containing a family of some kind of test. E.g. `print.f/` contains the tests for print family, like printf, sprintf, dprintf...

### File

The file name simply describes the test purpose.