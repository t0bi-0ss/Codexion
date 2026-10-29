#include "../../codexion.h"

void    sift_up(queue_struct *p_queue, int index)
{
    int parent;
    queue_request *req_ptr;

    req_ptr = p_queue->requests;
    if (req_ptr[1].coder == NULL)
        return ;
    while (index > 1)
    {
        parent =  index / 2;
        if (p_queue->cmp_f(req_ptr[index], req_ptr[parent]))
        {
            swap(&p_queue->requests[index], &p_queue->requests[parent]);
            index = parent;
        }
        else
            break;
    }
}
