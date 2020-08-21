// Qemu linux user host is 16k page, guest is 4k page.
// If the prot of 4x4k guest pages are different, the mapped
// 16 host page will hold the greatest common prot of the 4x4k
// pages. 
//
// This snippet is meant to test:
//     1. whether qemu is able to block the unauthorized access
//        e.g. [       rwx        ]    host 16k page
//             [r--][-w-][--x][---]    guest 4x4k pages
//                              ^
//                              read/write/exec in this page
//                              will qemu block these access?

#include <sys/mman.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "xby_error.h"
#include "4x4k_pages.h"

int prot[4] = {PROT_READ, PROT_WRITE, PROT_EXEC, PROT_NONE};

int main(void)
{
    ADDR start = mmap_16k_aligned();

    for(int i=0; i<4; i++)
    {
        void *ea = (void*)(start + PAGE_4K_SIZE*i); // Expected Address
        void *a = mmap(ea, PAGE_4K_SIZE, prot[i], 
                MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0);
        assert_msg_perror(a!=(void*)-1, "mmap %d-th 4k", i);
        assert_msg(a==ea, "mmap %d-th 4k not fixed", i);
    }

    printf("alloc successful\n");

    // try to wirte the 4st 4k page
    int *p =(int*)(start + PAGE_4K_SIZE*1);
    // use these non-trivial number, it is easy to grep qemu -d output
    // e.g. execute `qemu-i386 -d op ./THIS_PROGRAM 2> output`,
    // then in output search 3549 can easily locate the corresponding
    // TCG instructions
    *p = 0x1767;
    printf("write 2nd page, which is writable\n");
    p = (int*)(start + PAGE_4K_SIZE*3);
    *p = 0x3549;
    printf("write 4th page, supposed to throw out a Segmentation fault, but not\n");

    return 0;
}
