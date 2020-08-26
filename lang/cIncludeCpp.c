#include "cIncludeCpp.h"
#include <stdio.h>

void printNT(int new, int typename)
{
    printf("new=%d, typename=%d\n", new, typename);
}

int main(void)
{
    printClass();
    printNT(13,17);
    return 0;
}
