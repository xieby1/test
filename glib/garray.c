#include <glib.h>  /* GArray */
#include <stdio.h> /* printf */

int main(void)
{
    GArray *prots;

    int host_page_size = 0x4000;
#define GUEST_PAGE_SIZE 0x1000
    int size = host_page_size / GUEST_PAGE_SIZE;

    // new array, without zero_terminated, clear, element 1 byte, with 'size'
    // elements
    prots = g_array_sized_new(FALSE, TRUE, 1, size);

    // write
    for (int i = 0; i < size; i++)
    {
        char *prot = &g_array_index(prots, char, i);
        *prot = 1 << i;
    }
    // read
    for (int i = 0; i < size; i++)
    {
        char *prot = &g_array_index(prots, char, i);
        printf("%d-th prot = %d\n", i, *prot);
    }

    return 0;
}
