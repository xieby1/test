// This snippet is meant to learn how to use `mremap` to move a memory
// map from the old address to a new address

#define _GNU_SOURCE   /* mremap */
#include <stdio.h>    /* sprintf, printf */
#include <sys/mman.h> /* mmap, mremap */

#include "../../include/xby_error.h"

#define PAGE_SIZE 0x1000

int main(void)
{
    void *olda = mmap(NULL, PAGE_SIZE, PROT_WRITE | PROT_READ,
                      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    assert_msg_perror(olda != (void *)-1, "mmap olda");

    char *buf = (char *)olda;
    sprintf(buf, "this string is written at old address %p\n", olda);

    void *newa =
        mmap(NULL, PAGE_SIZE, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    assert_msg_perror(newa != (void *)-1, "reserve newa");

    {
        void *actual = mremap(olda, PAGE_SIZE, PAGE_SIZE,
                                   MREMAP_MAYMOVE | MREMAP_FIXED, newa);
        assert_msg_perror(actual != (void *)-1, "mremap");
        assert_msg(actual == newa, "mremap");
    }
    printf("currently move to new address %p\n", newa);
    buf = (char *)newa;
    printf("%s", buf);

    {
        void *actual = mremap(newa, PAGE_SIZE, PAGE_SIZE,
                MREMAP_MAYMOVE | MREMAP_FIXED, olda);
        assert_msg_perror(actual != (void *)-1, "mremap");
        assert_msg(actual == olda, "mremap");
    }
    printf("currently move back to old address %p\n", olda);

    return 0;
}
