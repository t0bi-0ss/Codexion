#include "../../codexion.h"

void    swap(queue_request *req_1, queue_request *req_2)
{
    queue_request    tmp;

    tmp = *req_1;
    *req_1 = *req_2;
    *req_2 = tmp;
}
