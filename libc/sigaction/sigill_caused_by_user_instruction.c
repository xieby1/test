// this snippet is indent to execute an ill instruction creating a
// SIGILL signal, then try to capture it.
//
// References:
//  * https://codegolf.stackexchange.com/questions/100532/shortest-code-to-throw-sigill
//      "The only byte sequence that's guaranteed to decode as an
//      illegal instruction on all future x86 CPUs is the 2 byte UD2: 0F 0B."

#include <signal.h> /* sigaction */
#include <stdio.h>  /* printf */
#include <stdlib.h> /* exit */

#if defined(__i386__) || defined(__x86_64__)
#    define INVALID_OP ".byte 0x0f, 0x0b" /* ud2 */
#    define INVALID_OP_LEN 2
#elif defined(__mips__)
/* no intended-reserved invalid op,
 * the undefined opcode which may be defined in future */
#    define INVALID_OP_LEN 4
#endif

void sigill_captured(int sig, siginfo_t *info, void *ucontext)
{
    printf("sig%d @%p:", info->si_signo, info->si_addr);
    for (char *addr = info->si_addr;
         addr < (char *)(info->si_addr) + INVALID_OP_LEN; addr++)
        printf(" %.2x", *addr);
    printf("\n exiting with return value 1\n");
    exit(1);
}

int main(void)
{
#ifndef INVALID_OP
    printf("current Architecture not supported by this snippet\n");
    exit(-1);
#endif
    const struct sigaction act = {
        .sa_sigaction = sigill_captured,
        .sa_mask = SA_NODEFER,
        .sa_flags = SA_SIGINFO,
    };
    sigaction(SIGILL, &act, (void *)0);
#ifdef INVALID_OP
    asm(INVALID_OP);
#endif
    return 0;
}
