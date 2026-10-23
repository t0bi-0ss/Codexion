#include "../../codexion.h"

void    free_heap(heap *queue)
{
    heap_node   *tmp;
    heap_node   *to_be_freed;

    if (!queue || !queue->head)
        return ;
    tmp = queue->head;
    while (tmp != NULL)
    {
        to_be_freed = tmp;
        tmp = tmp->next;
        free(to_be_freed);
    }
}
