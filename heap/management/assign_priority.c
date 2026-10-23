#include "../../codexion.h"

void    assign_priority(heap *queue)
{
    heap_node *tmp;
    int priority;
    int loops;
    heap_node *curr_min;

    if (!queue->head)
        return ;
    curr_min = NULL;
    priority = 1;
    loops = queue->size;
    reset_priority(queue);
    while (loops-- > 0)
    {
        tmp = queue->head;
        while (tmp->next != NULL)
        {
            if (timespec_min(curr_min, tmp) == 1 && tmp->priority == -1)
                curr_min = tmp;
                tmp = tmp->next;
        }
        curr_min->priority = priority;
        priority++;
    }
}
