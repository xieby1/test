#include <dlfcn.h>
#include <stdio.h>
int main(void)
{
    void *handle = dlopen("/home/xieby1/Codes/wine/dlls/winex11.drv/winex11.drv.so", RTLD_NOW);
    if(!handle)
        printf("%s\n", dlerror());
    return 0;
}

