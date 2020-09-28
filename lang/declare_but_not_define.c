// This snippet is meant to test how compiler/linker will react when only
// declare a function but not define it.
//
// Results: linker reports "undefined reference"
// By the way, if add __attribute__((weak)) to declare_but_not_define_func
// the compiler and linker runs normally, the error, SIGSEGV, will be reported
// at runtime, which may be useful to mimic virtual function feature in C++.

int declare_but_not_define_func(void);

int main(void)
{
    declare_but_not_define_func();
    return 0;
}
