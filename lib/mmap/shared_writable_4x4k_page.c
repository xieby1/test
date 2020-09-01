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
const int prot[4] = {PROT_WRITE|PROT_READ, PROT_READ, PROT_EXEC, PROT_NONE};

int main(void)
{
    // prepare a 4k file
    int fd = shm_open(path, O_RDWR|O_CREAT, S_IRWXU|S_IRWXG|S_IRWXO);
    assert_msg_perror( fd>=0, "shm_open");

    {
        int ret = ftruncate(fd, PAGE_4K_SIZE);
        assert_msg_perror( ret==0, "ftruncate" );
    }

    ADDR start = mmap_16k_aligned();

    for ( int i=1; i<4; i++)
    {
        void *ea = (void*)(start + PAGE_4K_SIZE*i);
        void *a = mmap(ea, PAGE_4K_SIZE, prot[i],
                MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0);
        assert_msg_perror(a!=(void*)-1, "mmap %d-th 4k", i);
        assert_msg(a==ea, "mmap %d-th 4k not fixed", i);
    }

    ADDR a = (ADDR)mmap((void*)start, PAGE_4K_SIZE, prot[0],
            MAP_SHARED|MAP_FIXED, fd, 0);
    assert_msg_perror(a!=-1, "mmap 4k shared writable page");
    assert_msg(a==start, "mmap allocates fixed memory failed, " \
            "expected %p, actual %p\n", (void*)start, (void*)a);

    int *p;
    // try to read the readable 4k page
    p = (int*)(start + PAGE_4K_SIZE*1);
    {
        int temp = *p;
        printf("neighbor reabable page is able to be read, %d\n", temp);
    }
    // try to write the writable 4k page
    p = (int*)(start);
    *p = 0x7893;
    printf("shared writable page is able to be written\n");
    {
        int temp = *p;
        printf("the written value %x\n", temp);
    }
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
