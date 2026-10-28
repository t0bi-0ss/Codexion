#include "../../codexion.h"

void    sift_down(heap *p_queue, int index)
{
    int child;
    heap_request    *req_ptr;

    req_ptr = p_queue->requests;
    if (req_ptr[1].coder == NULL)
        return ;
    while (2 * index <= p_queue->size)
    {
        child = 2 * index;
        if (child + 1 <= p_queue->size &&
            p_queue->cmp_f(req_ptr[child + 1], req_ptr[child])) // check if sibling is lesser
            child++;
        if (p_queue->cmp_f(req_ptr[child], req_ptr[index])) // check if child is lesser than parent
        {
            swap(&req_ptr[index], &req_ptr[child]);
            index = child;
        }
        else
            break;
    }
}
