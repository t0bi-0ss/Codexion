#include "../../codexion.h"

int is_disordered(heap *queue)
{
    heap_node   *tmp;

    if (!queue || !queue->head)
        return (-1);
    if (queue->size == 1)
        return (0);
    tmp = queue->head;
    while (tmp->next != NULL)
    {
        if (timespec_min(tmp, tmp->next) == 1)
            return (1);
        tmp = tmp->next;
    }
    return (0);
}
