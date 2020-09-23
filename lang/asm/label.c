// Noted: I still have not found a solution, this snippet cannot be compiled.
//
// This snippet is meant to test whether it is able to retrieve label address
// form asm, and how.

int main(void)
{
C_LABEL:
    asm volatile("ASM_LABEL:\n\t");
    void *addr_C_LABEL = &&C_LABEL;
    void *addr_ASM_LABEL = &&ASM_LABEL;
    return 0;
}
