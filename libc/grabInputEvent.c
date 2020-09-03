#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <linux/input.h>

int main(void)
{
    int fd = open("/dev/input/event0", O_RDONLY);
    if(fd<0)
    {
        perror("open");
	return fd;
    }

    int rc = ioctl(fd, EVIOCGRAB, 1);
    if(rc==0)
        ioctl(fd, EVIOCGRAB, 0);
    else
        perror("ioctl");
    return rc;
}
