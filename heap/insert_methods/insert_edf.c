#include "../../codexion.h"

void    insert_edf(heap *queue, heap_node *new_request)
{
    if (!queue || !new_request)
        return ;
    insert_last(queue, new_request);
    if (is_disordered(queue))
    {
        reset_priority(queue);
        bubble_sort(queue);
    }
}
