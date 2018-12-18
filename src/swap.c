#include "llist.h"

void llist_swap(llist_t *l1, llist_t *l2)
{
    llist_t temp;

    temp = *l1;
    *l1 = *l2;
    *l2 = temp;
}