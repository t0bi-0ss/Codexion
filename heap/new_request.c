#include "../codexion.h"

heap_node *new_request(struct timespec *burnout_time, pthread_cond_t *wake_coder)
{
    heap_node   *new_request;

    if (!burnout_time || !wake_coder)
        return (NULL);
        new_request = new_node();
        if (!new_request)
        return (NULL);
    new_request->burnout_time = burnout_time;
    new_request->wake_coder = wake_coder;
    return (new_request);
}
