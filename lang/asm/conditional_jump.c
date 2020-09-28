// This snippet is meant to test and learn:
//   * how to write conditional code in (x86 and mips) assembly
//   * how to write extended asm in c
//
// Expected output:
// jump taken
// jump not taken

#include <stdio.h> /* fprintf, printf */

__attribute__((used)) static void not_taken_output(void)
{
    printf("jump not taken\n");
}

__attribute__((used)) static void taken_output(void) { printf("jump taken\n"); }

__attribute__((noinline)) static void jump_equal(long a, long b)
{
    asm volatile(
#ifdef __x86_64__
        "cmp %0, %1\n\t"
        "jz JETAKEN\n\t"
        "call not_taken_output\n\t"
        "jmp JEEND\n\t"
        "JETAKEN:\n\t"
        "call taken_output\n\t"
        "JEEND:\n\t"
#elif defined __mips__
        /* save ra to stack */
        "daddi $sp, $sp, -8\n\t"
        "sd $ra, ($sp)\n\t"
        "beq %0, %1, JETAKEN\n\t"
        "jal not_taken_output\n\t"
        "j JEEND\n\t"
        "JETAKEN:\n\t"
        "jal taken_output\n\t"
        "JEEND:\n\t"
        /* restore ra from stack */
        "ld $ra, ($sp)\n\t"
        "daddi $sp, $sp, 8\n\t"
#else
#    define ARCH_NOT_SUPPORTED
        ""
#endif
        :                /* output */
        : "r"(a), "r"(b) /* input */
    );
}

#define DATA_1 67321
#define DATA_2 46733
int main(void)
{
#ifdef ARCH_NOT_SUPPORTED
    fprintf(stderr, "Arch not supported!\n");
    return -1;
#endif
    jump_equal(DATA_1, DATA_1);
    jump_equal(DATA_1, DATA_2);
    return 0;
}
