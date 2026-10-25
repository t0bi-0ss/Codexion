#include "../../codexion.h"

void    swap(heap_request *child_request, heap_request *parent_request)
{
    heap_request    tmp;

    tmp = *child_request;
    *child_request = *parent_request;
    *parent_request = tmp;
}
