// See xxx_common.h

#include "./redirect_stderr_in_multi-proc_app_common.h"
#include "../../include/xby_error.h"

#include <stdlib.h> /* getenv */
#include <stdio.h> /* fprintf */
#include <fcntl.h> /* open, O_* constants */
#include <unistd.h> /* dup2 */

int main(void)
{
    char *pts_path = getenv(ENV_PTS);
    assert_msg(pts_path!=NULL, "empyt env " ENV_PTS);

    fprintf(stderr, "this message is not supposed to be displayed on terminal\n");

    {
        int fd = open(pts_path, O_WRONLY);
        assert_msg_perror(fd != -1, "open");
        // duplicate fd as 2 (stderr)
        int ret = dup2(fd, 2);
        assert_msg_perror(ret != -1, "dup2");
        ret = close(fd);
        assert_msg_perror(ret != -1, "close old fd");
    }

    fprintf(stderr, "background message\n");

    return 0;
}
