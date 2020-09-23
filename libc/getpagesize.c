#include <stdio.h>  /* printf */
#include <unistd.h> /* getpagesize */

int main(void)
{
    printf("%x\n", getpagesize());
    return 0;
}
