#ifndef _LLIST_H_
# define _LLIST_H_

#include <stddef.h>

#define REALLOC_POOL (5)

typedef struct lnode_s {
	void *data;
	struct lnode_s *next;
	struct lnode_s *prev;
} lnode_t;

typedef struct llinked_list_s {
	size_t size;
	size_t unused_size;
	struct lnode_s *first;
	struct lnode_s *last;
	struct lnode_s *unused;
	void (* destructor)(void *);
} llist_t;

int llist_create(llist_t *list, size_t default_len, void (* default_destructor)(void *));
int llist_reserve(llist_t *list, size_t reserve_size);
int llist_shrink_to_fit(llist_t *list);
void llist_destroy(llist_t *list);

void llist_clear(llist_t *list);
void llist_erase(llist_t *list, void *data_to_delete);
void llist_remove(llist_t *list, lnode_t *node);

int llist_insert(llist_t *list, void *new_item, size_t position);
void llist_erase_at(llist_t *list, size_t position);

void *llist_pop_back(llist_t *list);
void *llist_pop_front(llist_t *list);

int llist_push_back(llist_t *list, void *new_item);
int llist_push_front(llist_t *list, void *new_item);

void llist_swap(llist_t *l1, llist_t *l2);

void *llist_get(llist_t *list, size_t position); /* TODO */

#endif /* !_LLIST_H_ */
