// This snippet is meant to test whether qemu is able to handle
// guest mmap a shared writable 4k page in 16k host.
//
// The qemu should run in 16k-page os, the guest application should
// compiled to run in 4k-page os.
//
// *: not care, r/w/x: read/write/exec, s: shared, p: private
// [                          ]    host 4k page
// [*w* s][*** p][*** p][*** p]    guest 4x4k pages
// currently qemu(5.0.0) cannot handle mmap a writable shared page
// where host page size is greater than the one in host.
//
// Compiled with -lrt -I../include/

#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

#include "xby_error.h"
#include "4x4k_pages.h"

const char *path = "/page.4k.size";

int main(void)
{
    // prepare a 4k file
    int fd = shm_open(path, O_RDWR|O_CREAT, S_IRWXU|S_IRWXG|S_IRWXO);
    assert_msg_perror( fd>=0, "shm_open");

    size_t real_len = PAGE_16K_SIZE;
    ADDR real_start = mmap_16k_aligned();

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
