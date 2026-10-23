#include "../../codexion.h"

void    insert_last(heap *queue, heap_node *new_node)
{
    heap_node   *tmp;

    if (!new_node || !queue)
        return ;
    if (!queue->head)
        queue->head = new_node;
    else
    {
        tmp = queue->head;
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = new_node;
        new_node->previous = tmp;
    }
    queue->size += 1;
}
