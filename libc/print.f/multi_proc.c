// This test is meant to test whether (forked) child is able to print to current
// terminal (which attaches to parent);
//
// Child is supposed to be able to print to current terminal, according to `man
// fork`,
// > The child inherits copies of the parent's set of open file descriptors That
// is to say, the parent's stdout is inherited by child.
//
// Result: Child is able to print to current terminal.

#include <stdio.h>  /* printf */
#include <unistd.h> /* fork */

#include "../../include/xby_error.h"

int main(void)
{
    pid_t pid = fork();
    assert_msg_perror(pid != -1, "fork");
    if (pid == 0)
    {
        printf("child\n");
    }
    else
    {
        printf("parent\n");
    }
    return 0;
}
