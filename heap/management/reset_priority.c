#include "../../codexion.h"

void    reset_priority(heap *queue)
{
    heap_node   *tmp;

    if (!queue->head)
        return ;
    tmp = queue->head;
    while (tmp != NULL)
    {
        tmp->priority = -1;
        tmp = tmp->next;
    }
}
