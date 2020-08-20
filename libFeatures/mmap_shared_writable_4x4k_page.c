// This snippet is meant to test whether qemu is able to handle
// guest mmap a shared writable 4k page in 16k host.
//
// The qemu should run in 16k-page os, the guest application should
// compiled to run in 4k-page os.
//
// Compiled with -lrt -I../include/

#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

#include "xby_error.h"

typedef unsigned long ADDR;
#define PAGE_16K_SIZE 0x4000
#define PAGE_4K_SIZE 0x1000

const char *path = "/page.4k.size";

int main(void)
{
    // prepare a 4k file
    int fd = shm_open(path, O_RDWR|O_CREAT, S_IRWXU|S_IRWXG|S_IRWXO);
    assert_msg_perror( fd>=0, "shm_open");

    size_t len = 0x7000;
    ADDR start = (ADDR)mmap(0, len, PROT_NONE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    assert_msg_perror( start!=-1, "mmap" );

    size_t real_len = PAGE_16K_SIZE;
    ADDR real_start;
    {
        int is_aligned = start & (PAGE_16K_SIZE-1);
        real_start = start & ~(PAGE_16K_SIZE-1);
        real_start += is_aligned? 0:PAGE_16K_SIZE;
    }

    ADDR a = (ADDR)mmap((void*)real_start, PAGE_4K_SIZE, PROT_WRITE, MAP_SHARED|MAP_FIXED, fd, 0);
    assert_msg_perror(a!=-1, "mmap 4k shared writable page");
    assert_msg(a==real_start, "mmap allocates fixed memory failed, " \
            "expected %p, actual %p\n", (void*)real_start, (void*)a);

    /*
    pid_t forkpid = fork();
    if( forkpid<0 )
    {
        perror("fork");
        goto exit;
    }
    else if( forkpid==0 ) // child process
    {
        
    }
    else // parent process
    {

    }
    */
    printf("No problem\n");
    shm_unlink(path);
    return 0;
}
