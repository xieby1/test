// See xxx_common.h

#include "../../include/xby_error.h"
#include "./redirect_stderr_in_multi-proc_app_common.h"

#include <stdio.h>  /* sprintf, fprintf */
#include <stdlib.h> /* setenv */
#include <unistd.h> /* readlink, getpid, close, execv, fork */

int main(void)
{
    {
#define LEN 256
        char path[LEN];
        char buf[LEN];
        sprintf(path, "/proc/%d/fd/0", getpid()); // path of stdin
        ssize_t size = readlink(path, buf, LEN);
        assert_msg_perror(size != -1, "readlink");
        assert_msg(size != LEN, "buf may overflow");
        // accordin to man, readlink() does not append a null byte to buf.
        buf[size] = 0;
        setenv(ENV_PTS, buf, 1);
#undef LEN
    }

    fprintf(stderr, "foreground message\n");

    // execv new process will inherit fd0,1,2 implicitly,
    // to redirect stderr by ENV_PTS, so close these 3 fd
    close(0);
    close(1);
    close(2);

    pid_t pid = fork();
    assert_msg_perror(pid != -1, "fork");
    if (pid == 0) // child
    {
        char **argv_temp = {NULL};
        int ret =
            execv("./redirect_stderr_in_multi-proc_app_background", argv_temp);
        assert_msg_perror(ret != 0, "execv");
    }

    return 0;
}
