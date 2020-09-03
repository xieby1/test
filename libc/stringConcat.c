#include <stdio.h>

int main(void)
{
    char *a = "123";
    char *b = "asd";
    char c[] = {a, b};

    printf("%s\n", c);
    return 0;
}
