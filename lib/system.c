#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

char command[32];

int main(void)
{
    sprintf(command, "pmap %d", getpid());
    system(command);
    system(command);
}
