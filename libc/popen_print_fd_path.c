#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#define LEN 256

int main(void)
{
    char command[LEN];
    sprintf(command, "readlink /proc/%d/fd/0", getpid());
    printf("%s\n", command);
    FILE *pf = popen(command, "r");
    char output[LEN];
    fread(output, 1, LEN, pf);
    printf("%s\n", output);

    return 0;
}
#undef LEN

