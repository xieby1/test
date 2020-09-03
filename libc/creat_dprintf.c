#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    char file_path[256];
    sprintf(file_path, "tmp/%s", __FILE__);
    int fd = creat(file_path, S_IRUSR|S_IWUSR);
    if (!fd)
        printf("ERROR\n");
    dprintf(fd, "test\n1\n2\n3\n");

    return 0;
}
