// TODO: Working In Progress Warning: This snippet has not been finished yet.
//
// This snippet is meant to test how qemu fold 64-bit-guest memory space into
// 32-bit-host memory space. In my knowledgement **and imagination**, qemu
// calculates the lowest&highest memory address of the 64-bit ELF, the start
// of guest_base points at the lowest address, like below,
//
// 64-bit guest memory: [0, Lowest-1] [Lowest, Highest] [Highest, 2^64-1]
//                                    |               |
// 32-bit host memory:       [0, ...] [guest_base, ...] [..., 2^32-1]
//                                    |               |
//                                    V               V
//                                    if Lowest~Highest
//                                    cannot fit into
//                                    reserved space in
//                                    32-bit host, failed

#include <sys/mman.h> /* mmap */
#include <unistd.h>   /* getpagesize */

#include "../../include/xby_error.h"

void *lowest_segment_addr = (void *)0x400000;

int main(void)
{
    void *addr_expected = lowest_segment_addr - getpagesize();
    void *addr = mmap(addr_expected, getpagesize(), PROT_READ | PROT_WRITE,
                      MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1, 0);
    assert_msg_perror(addr != (void *)-1, "mmap");
    assert_msg(addr == addr_expected, "mmap not fixed");
    return 0;
}
