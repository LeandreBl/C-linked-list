#ifndef _LLIST_INTERNAL_H_
# define _LLIST_INTERNAL_H_

#include <stdio.h>

#include "llist.h"

lnode_t *llist_pop_unused_node(llist_t *list);
void llist_display(llist_t *list, void (* displayer)(void *data));
void llist_move_to_unused_node(llist_t *list, lnode_t *node);
lnode_t *llist_get_node_at(llist_t *list, size_t position);

#endif /* !_LLIST_INTERNAL_H_ */