#include "../../codexion.h"

heap_node *new_node()
{
    heap_node   *the_new_node;

    the_new_node = malloc(sizeof(heap_node));
    if (!the_new_node)
        return (NULL);
    the_new_node->priority = 0;
    the_new_node->burnout_time = NULL;
    the_new_node->wake_coder = NULL;
    the_new_node->previous = NULL;
    the_new_node->next = NULL;

    return (the_new_node);
}
