#include <criterion/criterion.h>

#include "llist.h"

Test(list_create, items5)
{
	llist_t list;
	lnode_t *node;

	cr_assert(llist_create(&list, 5, NULL) == 0);
	cr_assert(list.size == 0);
	cr_assert(list.unused_size == 5);
	cr_assert(list.first == NULL);
	cr_assert(list.last == NULL);
	node = list.unused;
	cr_assert(node->prev == NULL);
	for (size_t i = 0; i < 5; ++i) {
		cr_assert(node != NULL);
		cr_assert(node->data == NULL);
		node = node->next;
	}
	cr_assert(node == NULL);
	cr_assert(list.destructor == NULL);
	llist_destroy(&list);
}

Test(list_create, empty)
{
	llist_t list;
	lnode_t *node;

	cr_assert(llist_create(&list, 0, NULL) == 0);
	cr_assert(list.size == 0);
	cr_assert(list.unused_size == 0);
	cr_assert(list.first == NULL);
	cr_assert(list.last == NULL);
	node = list.unused;
	cr_assert(node == NULL);
	cr_assert(list.destructor == NULL);
	llist_destroy(&list);
}

