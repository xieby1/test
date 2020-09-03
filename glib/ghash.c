// This snippet is meant to test how to utilize GHashTable implement frag_map,
// the prots are implement by GArray
//
// Expected output 3 lines, first line and second line are the same

#include <glib.h>   /* GHashTable, GArray */
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */

int host_page_size = 0x4000;
#define GUEST_PAGE_SIZE 0x1000

typedef struct FragDesc
{
    unsigned long shd; // shared page virtual address
    unsigned long nbr; // private neighbor page virtual address
    GArray *prots;
} FragDesc;

FragDesc *FragDesc_new(void)
{
    FragDesc *ret = (FragDesc *)malloc(sizeof(FragDesc));
    ret->prots =
        g_array_sized_new(FALSE, TRUE, 1, host_page_size / GUEST_PAGE_SIZE);
    return ret;
}

void FragDesc_delete(void *p)
{
    FragDesc *fd = (FragDesc *)p;
    g_array_free(fd->prots, TRUE);
    free(fd);
}

#define TEST_SIZE 3
unsigned long olda[TEST_SIZE] = {
    0xa000,
    0xa000, // intend to test same key
    0xa001,
};
unsigned long newa[TEST_SIZE][2] = {
    {0xb000, 0xc000},
    {0xb001, 0xc001},
    {0xb002, 0xc002},
};

int main(void)
{
    GHashTable *frag_map;

    frag_map = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL,
                                     FragDesc_delete);
    // insert key-value pairs into hash table
    for (int i = 0; i < TEST_SIZE; i++)
    {
        FragDesc *fd_temp = FragDesc_new();
        fd_temp->shd = newa[i][0];
        fd_temp->nbr = newa[i][1];
        g_hash_table_insert(frag_map, (void *)olda[i], fd_temp);
    }
    // lookup value by key
    for (int i = 0; i < TEST_SIZE; i++)
    {
        FragDesc *fd = g_hash_table_lookup(frag_map, (void *)olda[i]);
        printf("%p: %p, %p\n", (void *)olda[i], (void *)fd->shd,
               (void *)fd->nbr);
    }

    return 0;
}
