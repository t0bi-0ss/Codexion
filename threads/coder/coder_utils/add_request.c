#include "../../../codexion.h"

void    add_request(coder_properties_struct *coder_p)
{
    queue_request    new_request;

    new_request.coder = coder_p;
    new_request.timeof_request = get_timestamp();
    push(coder_p->monitor_ptr->min_heap, new_request);
}
