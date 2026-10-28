#include "../codexion.h"

static heap_request  create_request(coder_properties_struct *coder_p);

void    add_request(coder_properties_struct *coder_p)
{
    heap_request    new_request;

    new_request = create_request(coder_p);
    pthread_mutex_lock(&coder_p->monitor_ptr->shared_mutex);
    push(coder_p->monitor_ptr->min_heap, new_request);
    pthread_cond_signal(&coder_p->monitor_ptr->wake_monitor);
}

static heap_request  create_request(coder_properties_struct *coder_p)
{
    heap_request    new_request;

    new_request.coder = coder_p;
    new_request.timeof_request = get_timestamp();

    return new_request;
}
