// this snippet is meant to test 
//  1. whether int3 in user program will cause debugger to hist a breakpoint
//     Result: Yes
//  2. whether user program capture SIGTRAP(int3 cause it) before debugger,
//     that is the priority of ptrace or sigaction
//     Result: debugger > user program, that is, ptrace > sigaction

#include <signal.h>
#include <stdio.h>

void sigtrap_captured(int sig, siginfo_t *info, void *ucontext)
{
    printf("sig%d @%p\n", info->si_signo, info->si_addr);
}

int main(void)
{
    // register SIGTRAP sig action
    const struct sigaction act = {
        .sa_sigaction = sigtrap_captured,
        .sa_mask = SA_NODEFER,
        .sa_flags = SA_SIGINFO,
    };
    sigaction(SIGTRAP, &act, (void*)0);

    int a=1763;
    asm("int3");
    int b=a+3241;
    return b;
}
