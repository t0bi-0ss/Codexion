#include "../../codexion.h"

void    swap(heap_request *req_1, heap_request *req_2)
{
    heap_request    tmp;

    tmp = *req_1;
    *req_1 = *req_2;
    *req_2 = tmp;
}
