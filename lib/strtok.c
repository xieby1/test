#include <stdio.h>
#include <string.h>

int main(void)
{
    char s[] = "ab cd   efg     hi";
    char *t = strtok(s, " ");
    while(t)
    {
	printf("%s\n", t);
        t = strtok(NULL, " ");
    }
    return 0;
}
