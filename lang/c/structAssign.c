// to test struct assignment
// struct A = struct B, are A and B the same struct?
#include <stdio.h>
struct Struct
{
    int i1;
    float f1;
};

int main(void)
{
    struct Struct A = {.i1 = 7, .f1 = 1.15};
    struct Struct B = A;
    printf("A @%p i1=%d, f1=%f\n", &A, A.i1, A.f1);
    printf("B @%p i1=%d, f1=%f\n", &B, B.i1, B.f1);

    return 0;
}
