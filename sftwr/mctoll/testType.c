#include<stdio.h>

void func(void){return;}

int main(void)
{
	char c = 'c';
	int i = 113;
	int *ptr = &i;
	void (*funcPtr)(void);
	funcPtr = &func;
	printf("%c, %d, 0x%lx, 0x%lx\n", c, i, ptr, funcPtr);
	return 0;
}
