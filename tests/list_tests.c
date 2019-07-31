#include <criterion/criterion.h>
#include <stdlib.h>

#include "internal.h"

void displayer(void *data)
{
	lnode_t *node = data;

	cr_log(CR_LOG_ERROR, "{%p <- %p[%zu] -> %p}\n", (void *)node->prev, (void *)node,
	       *(size_t *)node->data, (void *)node->next);
}

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

Test(list_reserve, only_reserve)
{
	llist_t list;
	lnode_t *node;

	llist_create(&list, 10, NULL);
	cr_assert(llist_reserve(&list, 12) == 0);
	cr_assert(list.size == 0);
	cr_assert(list.unused_size == 12);
	node = list.unused;
	for (size_t i = 0; i < list.unused_size; ++i) {
		cr_assert(node != NULL);
		cr_assert(node->data == NULL);
		node = node->next;
	}
	cr_assert(node == NULL);
	llist_destroy(&list);
}

Test(list_clear, only_clear)
{
	llist_t list;
	lnode_t *node;

	llist_create(&list, 10, NULL);
	llist_clear(&list);
	cr_assert(list.size == 0);
	cr_assert(list.unused_size = 10);
	cr_assert(list.first == NULL);
	cr_assert(list.last == NULL);
	node = list.unused;
	for (size_t i = 0; i < list.unused_size; ++i) {
		cr_assert(node != NULL);
		node = node->next;
	}
	cr_assert(node == NULL);
	llist_destroy(&list);
}

Test(push_back, push)
{
	llist_t list;
	lnode_t *node;
	char *str;

	llist_create(&list, 10, free);
	for (int i = 0; i < 5; ++i) {
		str = strdup("testX");
		cr_assert(str != NULL);
		str[4] = i + '0';
		cr_assert(llist_push_back(&list, str) != -1);
	}
	cr_assert(list.first != NULL);
	cr_assert(list.first != list.last);
	cr_assert(list.size == 5);
	cr_assert(list.unused != NULL);
	cr_assert(list.unused_size == 5);
	for (int i = 0; i < 5; ++i) {
		str = strdup("testX");
		cr_assert(str != NULL);
		str[4] = i + '5';
		cr_assert(llist_push_back(&list, str) != -1);
	}
	cr_assert(list.first != NULL);
	cr_assert(list.first != list.last);
	cr_assert(list.size == 10);
	cr_assert(list.unused == NULL);
	cr_assert(list.unused_size == 0);
	node = list.first;
	for (size_t i = 0; i < list.size; ++i) {
		cr_assert(node != NULL);
		str = node->data;
		cr_assert(str[4] == ((char)i + '0'));
		cr_assert(node->data != NULL);
		if (node->next == NULL)
			cr_assert(node == list.last);
		node = node->next;
	}
}

Test(push_front, push)
{
	llist_t list;
	lnode_t *node;
	char *str;

	llist_create(&list, 10, free);
	for (size_t i = 0; i < 5; ++i) {
		str = strdup("testX");
		cr_assert(str != NULL);
		str[4] = i + '0';
		cr_assert(llist_push_front(&list, str) != -1);
	}
	cr_assert(list.first != NULL);
	cr_assert(list.first != list.last);
	cr_assert(list.size == 5);
	cr_assert(list.unused != NULL);
	cr_assert(list.unused_size == 5);
	for (size_t i = 0; i < 5; ++i) {
		str = strdup("testX");
		cr_assert(str != NULL);
		str[4] = i + '5';
		cr_assert(llist_push_front(&list, str) != -1);
	}
	cr_assert(list.first != NULL);
	cr_assert(list.first != list.last);
	cr_assert(list.size == 10);
	cr_assert(list.unused == NULL);
	cr_assert(list.unused_size == 0);
	node = list.first;
	for (size_t i = 0; i < list.size; ++i) {
		cr_assert(node != NULL);
		str = node->data;
		cr_assert(str[4] == ('9' - (char)i));
		cr_assert(node->data != NULL);
		if (node->next == NULL)
			cr_assert(node == list.last);
		node = node->next;
	}
}

Test(shrink, default_shrink)
{
	llist_t list;

	llist_create(&list, 10, free);
	for (int i = 0; i < 10; ++i) {
		llist_push_back(&list, strdup("toto"));
	}
	cr_assert(llist_shrink_to_fit(&list) == 0);
	cr_assert(list.unused_size == 0);
	cr_assert(list.unused == NULL);
}

Test(erase, default_erase)
{
	llist_t list;
	lnode_t *node;
	char *s;
	char *temp;
	;

	llist_create(&list, 10, free);
	for (int i = 0; i < 10; ++i) {
		s = strdup("testX");
		cr_assert(s != NULL);
		s[4] = '0' + (char)i;
		if (i == 4)
			temp = s;
		llist_push_back(&list, s);
	}
	llist_erase(&list, s);
	cr_assert(list.first != NULL);
	cr_assert(list.last != NULL);
	cr_assert(list.size == 9);
	cr_assert(list.unused_size == 1);
	cr_assert(list.unused != NULL);
	node = list.first;
	for (size_t i = 0; i < list.size; ++i) {
		s = node->data;
		cr_assert(s != NULL);
		cr_assert(s != temp);
	}
	llist_destroy(&list);
}

Test(erase, default_erase_at)
{
	llist_t list;
	lnode_t *node;
	char *s;

	llist_create(&list, 10, free);
	for (int i = 0; i < 10; ++i) {
		s = strdup("testX");
		cr_assert(s != NULL);
		s[4] = '0' + (char)i;
		llist_push_back(&list, s);
	}
	llist_erase_at(&list, 4);
	cr_assert(list.first != NULL);
	cr_assert(list.last != NULL);
	cr_assert(list.size == 9);
	cr_assert(list.unused_size == 1);
	cr_assert(list.unused != NULL);
	node = list.first;
	for (size_t i = 0; i < list.size; ++i) {
		s = node->data;
		cr_assert(s != NULL);
		cr_assert(s[4] != '4');
		node = node->next;
	}
	llist_destroy(&list);
}

Test(insert, default_insert)
{
	llist_t list;
	lnode_t *node;
	char *s;

	llist_create(&list, 10, free);
	cr_assert(llist_insert(&list, strdup("test1"), 0) == 0);
	cr_assert(list.size == 1);
	cr_assert(list.first != NULL);
	cr_assert(list.last != NULL);
	cr_assert(list.unused != NULL);
	cr_assert(list.unused_size == 9);
	cr_assert(llist_insert(&list, strdup("test2"), 1) == 0);
	cr_assert(list.size == 2);
	cr_assert(list.first != NULL);
	cr_assert(list.last != NULL);
	cr_assert(list.unused != NULL);
	cr_assert(list.unused_size == 8);
	cr_assert(llist_insert(&list, strdup("test0"), 0) == 0);
	cr_assert(list.size == 3);
	cr_assert(list.first != NULL);
	cr_assert(list.last != NULL);
	cr_assert(list.unused != NULL);
	cr_assert(list.unused_size == 7);
	node = list.first;
	for (size_t i = 0; i < list.size; ++i) {
		s = node->data;
		cr_assert(s[4] == '0' + (char)i);
		node = node->next;
	}
	llist_destroy(&list);
}

Test(pop_back, default_pop)
{
	llist_t list;
	char *s;

	llist_create(&list, 10, free);
	for (size_t i = 0; i < 10; ++i) {
		s = strdup("testX");
		cr_assert(s != NULL);
		s[4] = (char)i + '0';
		llist_push_back(&list, s);
	}
	for (size_t i = 0; i < 10; ++i) {
		cr_assert(list.first != NULL);
		cr_assert(list.last != NULL);
		if (i != 0)
			cr_assert(list.unused != NULL);
		s = llist_pop_back(&list);
		cr_assert(list.size == 10 - 1 - i);
		cr_assert(list.unused_size == i + 1);
		cr_assert(s[4] == '9' - (char)i);
	}
}

Test(pop_front, default_pop)
{
	llist_t list;
	char *s;

	llist_create(&list, 10, free);
	for (size_t i = 0; i < 10; ++i) {
		s = strdup("testX");
		cr_assert(s != NULL);
		s[4] = (char)i + '0';
		llist_push_back(&list, s);
	}
	for (size_t i = 0; i < 10; ++i) {
		cr_assert(list.first != NULL);
		cr_assert(list.last != NULL);
		if (i != 0)
			cr_assert(list.unused != NULL);
		s = llist_pop_front(&list);
		cr_assert(list.size == 10 - 1 - i);
		cr_assert(list.unused_size == i + 1);
		cr_assert(s[4] == '0' + (char)i);
	}
}

Test(swap, simple_swap)
{
	llist_t list1;
	llist_t list2;
	lnode_t *node;
	char *str;

	llist_create(&list1, 10, free);
	llist_create(&list2, 5, free);

	for (size_t i = 0; i < 10; ++i) {
		str = strdup("list1");
		cr_assert(str != NULL);
		llist_push_back(&list1, str);
	}
	for (size_t i = 0; i < 5; ++i) {
		str = strdup("list2");
		cr_assert(str != NULL);
		llist_push_back(&list2, str);
	}
	llist_swap(&list1, &list2);
	cr_assert(list1.first != NULL);
	cr_assert(list1.last != NULL);
	cr_assert(list1.size == 5);
	cr_assert(list1.unused == NULL);
	cr_assert(list1.unused_size == 0);
	node = list1.first;
	for (size_t i = 0; i < list1.size; ++i) {
		str = node->data;
		cr_assert(strcmp(str, "list2") == 0);
	}
	node = list2.first;
	for (size_t i = 0; i < list2.size; ++i) {
		str = node->data;
		cr_assert(strcmp(str, "list1") == 0);
	}
	cr_assert(list2.first != NULL);
	cr_assert(list2.last != NULL);
	cr_assert(list2.size == 10);
	cr_assert(list2.unused == NULL);
	cr_assert(list2.unused_size == 0);
}

Test(massive_tests, mutliple_tests)
{
	const size_t test_size = 1000;
	llist_t list;
	size_t *data;

	llist_create(&list, test_size, free);
	for (size_t i = 0; i < test_size; ++i) {
		data = malloc(sizeof(size_t));
		*data = i;
		llist_push_back(&list, data);
	}
	// 0 -> 999
	for (size_t i = 0; i < 20; ++i)
		llist_erase_at(&list, list.size - 1);
	// 0 -> 979
	for (size_t i = 0; i < 20; ++i) {
		data = malloc(sizeof(size_t));
		*data = i;
		llist_push_front(&list, data);
	}
	// 19 -> 0, 0 -> 979
	data = malloc(sizeof(size_t));
	*data = 12345;
	llist_insert(&list, data, 20);
	// 0 -> 19, 12345, 0 -> 979
	for (size_t i = 0; i < 20; ++i) {
		data = llist_pop_front(&list);
		cr_assert(*data == 19 - i);
		free(data);
	}
	data = llist_pop_front(&list);
	cr_assert(*data == 12345);
	free(data);
	for (size_t i = 0; i < 980; ++i) {
		data = llist_pop_front(&list);
		cr_assert(*data == i);
		free(data);
	}
	cr_assert(list.first == NULL);
	cr_assert(list.size == 0);
	cr_assert(list.unused != NULL);
	cr_assert(list.unused_size == 1005);
	llist_destroy(&list);
}

Test(get_node_at, simple_test)
{
	llist_t list;

	llist_create(&list, 10, free);
	for (char i = 'a'; i < 'j'; ++i) {
		char *str = calloc(2, sizeof(char));
		cr_assert(str != NULL);
		str[0] = i;
		llist_push_back(&list, str);
	}
	for (int i = 'a'; i < 'j'; ++i) {
		lnode_t *node = llist_get_node_at(&list, i - 'a');
		char *str = node->data;
		cr_assert(str[0] == i);
	}
}