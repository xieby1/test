#include <stdio.h>

int main(void)
{
    char file_path[256];
    sprintf(file_path, "/tmp/%s", __FILE__);
    printf("output in %s\n", file_path);
    FILE * stream = fopen(file_path, "w+");
    fprintf(stream, "1\n2\n3\n");
    return 0;
}
