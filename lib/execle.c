#include <stdio.h>
#include <unistd.h>

extern char **environ;
int main(int argc, char **argv, char **envp)
{
    printf("%d \n", argc);
    for(int i=0; i<argc; i++)
        printf("%s\n", argv[i]);

    char *path = "./execle2";
    argv[0] = path;
    environ = envp;
    execvp(path, argv);

    return 0;
}
