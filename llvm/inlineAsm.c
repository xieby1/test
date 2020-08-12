int main(void)
{
    asm("movq    $60, %rax");
    asm("movq    $1, %rdi");
    asm("syscall");
    return -1;
}
