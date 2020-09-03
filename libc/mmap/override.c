// This snippet tests the characteristics of mmap, to see what will
// happen when the to-be-allocated memory has been already allocated.
//
// Here are 4 allocating position cases need to be carefully examed:
// 1. Overlap:                       
//      [mapped memory 1]       |       [mapped memory 1]
//          [mapped memory 2]   |   [mapped memory 2]
// 2. Cover:
//          [mapped memory 1]
//      [mapped     memory     2]
// 3. Insert:
//      [mapped     memory     1]
//          [mapped memory 2]
// 4. Adjoin:
//      [mapped memory 1]
//                       [mapped memory 2]
//
// Besides, in each above case, the different prot and flags need to
// be carefully examed:
// 1. [1] and [2] are both ANON pages
//  1. with same prot
//  2. with different prot
// 2. [1] is ANON, [2] is not
// 3. [1] is not, [2] is ANON
// 4. [1] and [2] are both ANON
//
// Therefore, here are 3*4=12 tests.

#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

char command[256];

// Address Start|End|Length
void test(char* desc, size_t a2s_a1s, size_t a1l, size_t a2l,
        int p1, int p2, int f1, int f2)
{
    void *a1s, *a2s;
    printf("%s\n", desc);

    void *reserved = mmap(0, 0x10000, PROT_NONE, 
            MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);

    a1s = mmap(reserved+0x3000, a1l, p1, f1|MAP_FIXED, -1, 0);
    printf("Mapped memory 1 = [%p, %p]\n", a1s, a1s+a1l);
    if (a1s == (void*)-1)
        perror("mmap a1");
    a2s = mmap(a1s+a2s_a1s,     a2l, p2, f2|MAP_FIXED, -1, 0);
    printf("Mapped memory 2 = [%p, %p]\n", a2s, a2s+a2l);
    if (a2s == (void*)-1)
        perror("mmap a2");
    if(a2s != a1s+a2s_a1s)
        printf("a2s not expected\n");
    void *low = a1s<a2s? a1s:a2s;
    void *high = a1s+a1l>a2s+a2l? a1s+a1l:a2s+a2l;
    sprintf(command, "pmap --range %p,%p %d", low, high-1, getpid());
    if (system(command) == -1)
        perror("System command");
    munmap(a1s, a1l);
    munmap(a2s, a2l);
    printf("\n");  
}

int main(void)
{
    printf("pid = %d\n", getpid());
    sprintf(command, "pmap %d", getpid());
    //sprintf(command, "cat /proc/%d/maps", getpid());

    test("1.1.1. Overlap [ANON] [ANON] same prot",
            0x1000, 0x2000, 0x2000, PROT_READ, PROT_READ,
            MAP_PRIVATE|MAP_ANONYMOUS, MAP_PRIVATE|MAP_ANONYMOUS);

    test("1.1.2. Overlap [ANON] [ANON] diff prot",
            0x1000, 0x2000, 0x2000, PROT_READ, PROT_EXEC,
            MAP_PRIVATE|MAP_ANONYMOUS, MAP_PRIVATE|MAP_ANONYMOUS);

    test("2.1.1. Cover [ANON] [ANON] same prot",
            -0x1000, 0x1000, 0x3000, PROT_WRITE, PROT_WRITE,
            MAP_PRIVATE|MAP_ANONYMOUS, MAP_PRIVATE|MAP_ANONYMOUS);

    test("2.1.2. Cover [ANON] [ANON] diff prot",
            -0x1000, 0x1000, 0x3000, PROT_WRITE, PROT_EXEC,
            MAP_PRIVATE|MAP_ANONYMOUS, MAP_PRIVATE|MAP_ANONYMOUS);

    test("3.1.1. Insert [ANON] [ANON] same prot",
            0x1000, 0x3000, 0x1000, PROT_EXEC, PROT_EXEC,
            MAP_PRIVATE|MAP_ANONYMOUS, MAP_PRIVATE|MAP_ANONYMOUS);

    test("3.1.2. Insert [ANON] [ANON] diff prot",
            0x1000, 0x3000, 0x1000, PROT_EXEC, PROT_WRITE,
            MAP_PRIVATE|MAP_ANONYMOUS, MAP_PRIVATE|MAP_ANONYMOUS);

    test("4.1.1 Adjoin [ANON] [ANON] same prot",
            0x1000, 0x1000, 0x1000, PROT_EXEC, PROT_EXEC,
            MAP_PRIVATE|MAP_ANONYMOUS, MAP_PRIVATE|MAP_ANONYMOUS);
            
    return 0;
}
