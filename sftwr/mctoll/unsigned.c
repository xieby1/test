#include<stdint.h>

int main(void)
{
	int_least64_t uint1 = 0xffff0000ffff0000LL;
	int_least64_t uint2 = 0x77774444aaaa4444LL;

	return uint1<uint2;
}
