#include "../../codexion.h"

void    insert_fifo(heap *queue, heap_node *new_request)
{
    if (!queue || !new_request)
        return ;
    insert_last(queue, new_request);
    new_request->priority = queue->size;
}
