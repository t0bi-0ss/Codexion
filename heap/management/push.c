#include "../../codexion.h"

void    add_request(heap *queue, heap_request new_request)
{
    if (queue->size >= queue->capacity)
    {
        fprintf(stderr, "Heap overflow!\n");
        return ;
    }
    queue->requests[++queue->size] = new_request;
    
}