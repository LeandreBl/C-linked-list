#ifndef _LLIST_INTERNAL_H_
# define _LLIST_INTERNAL_H_

# include <stdio.h>

# include "llist.h"

__attribute__ ((visibility ("hidden"))) lnode_t *llist_pop_unused_node(llist_t *list) __THROW __nonnull((1));
__attribute__ ((visibility ("hidden"))) void llist_display(llist_t *list, void (* displayer)(void *data)) __THROW __nonnull((1, 2));
__attribute__ ((visibility ("hidden"))) void llist_move_to_unused_node(llist_t *list, lnode_t *node) __THROW __nonnull((1, 2));
__attribute__ ((visibility ("hidden"))) lnode_t *llist_get_node_at(llist_t *list, size_t position) __THROW __nonnull((1));

#endif /* !_LLIST_INTERNAL_H_ */