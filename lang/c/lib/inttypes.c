// 2021.07.13 copied from https://www.cplusplus.com/reference/cinttypes/
// and I add ptr test
/* example of <inttypes.h> */
#include <stdio.h>      /* printf, scanf, fgets, stdin, NULL */
#include <stdint.h>     /* intmax_t, uintptr_t */
#include <inttypes.h>   /* strtoimax, PRIdMAX, SCNdMAX */

int main ()
{
  char buffer[80];
//  intmax_t foo,bar;
//
//  printf ("Please, enter a number: ");
//  fgets (buffer,80,stdin);
//  foo = strtoimax (buffer,NULL,10);
//
//  printf ("Thanks for entering %" PRIdMAX ".\n", foo);
//
//  printf ("Please, enter another number: ");
//  scanf ("%" SCNdMAX,&bar);
//
//  printf ("%" PRIdMAX " by %" PRIdMAX " is %" PRIdMAX, foo, bar, foo*bar);

  uintptr_t p = (uintptr_t)buffer;
  printf ("%" PRIuPTR "\n", p);

  return 0;
}
