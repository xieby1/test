#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv, char **envp)
{
    printf("%d \n", argc);
    for(int i=0; i<argc; i++)
        printf("%s\n", argv[i]);
    
    return 0;
}
