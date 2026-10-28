#include "../../codexion.h"

int    pop_at(heap *p_queue, int index)
{
    if (p_queue->size == 0)
    {
        fprintf(stderr, "Heap underflow!\n");
        return (1);
    }
    if (index <= 0 || index > p_queue->size)
    {
        fprintf(stderr, "Invalid index!\n");
        return (2);
    }
    if (index == p_queue->size)
    {
        p_queue->size--;
        return (0);
    }
    p_queue->requests[index] = p_queue->requests[p_queue->size];
    p_queue->size--;
    sift_down(p_queue, index);
    sift_up(p_queue, index);
    return (0);
}
