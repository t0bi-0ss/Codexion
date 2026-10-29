#include "../../codexion.h"

void    push(queue_struct *p_queue, queue_request new_request)
{
    if (p_queue->size >= p_queue->capacity)
    {
        fprintf(stderr, "Heap overflow!\n");
        return ;
    }
    p_queue->requests[++p_queue->size] = new_request;
    sift_up(p_queue, p_queue->size);
}
