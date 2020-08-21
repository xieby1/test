#ifndef _4X4K_PAGES_H
#define _4X4K_PAGES_H

#include <sys/mman.h>

#include "xby_error.h"

typedef unsigned long ADDR;
#define PAGE_16K_SIZE 0x4000
#define PAGE_4K_SIZE 0x1000

ADDR mmap_16k_aligned(void)
{
    ADDR start = (ADDR)mmap(0, 0x7000, PROT_NONE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    assert_msg_perror( start!=-1, "mmap" );

    ADDR real_start;
    { // align upward, e.g. 0x1000/0x2000/0x3000/0x4000=>0x4000
        int is_aligned = start & (PAGE_16K_SIZE-1);
        real_start = start & ~(PAGE_16K_SIZE-1);
        real_start += is_aligned? 0:PAGE_16K_SIZE;
    }

    return real_start;
}

#endif // _4X4K_PAGES_H
