#include "../codexion.h"

void    add_request(heap *queue, heap_node *new_request, char *scheduler)
{
    if (strncmp("fifo", scheduler, 5) == 0)
        insert_fifo(queue, new_request);
    else if (strncmp("edf", scheduler, 4) == 0)
        insert_edf(queue, new_request);
}
