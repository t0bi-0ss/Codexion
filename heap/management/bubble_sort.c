#include "../../codexion.h"

void    bubble_sort(heap *queue)
{
    int loops;
    heap_node   *tmp;

    if (!queue || !queue->head)
        return ;
    loops = queue->size;
    while (loops-- > 0)
    {
        tmp = queue->head;
        while (tmp != NULL)
        {
            if (timespec_min(tmp->burnout_time, tmp->next->burnout_time) == 1)
                swap_nodes(tmp, tmp->next);
            tmp = tmp->next;
        }
    }
}
