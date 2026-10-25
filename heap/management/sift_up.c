#include "../../codexion.h"

void    sift_up(heap *queue, int index)
{
    int parent;

    while (index > 1)
    {
        parent =  index / 2;
        if (timespec_min(queue->requests[parent].time_stamp, queue->requests[index].time_stamp))
        {
            swap(&queue->requests[index], &queue->requests[parent]);
            index = parent;
        }
        else
            break;
    }
}