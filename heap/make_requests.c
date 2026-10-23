#include "../codexion.h"

int    make_requests(coder_properties_struct *self_properties)
{
    heap_node   *request;
    char    *scheduler;
    heap    *first_d_queue;
    heap    *second_d_queue;

    request = new_request(&self_properties->time_to_burnout, &self_properties->wake_coder);
    if (!request)
        return (1);
    scheduler = self_properties->config->scheduler;
    first_d_queue = self_properties->first_dongle->queue;
    second_d_queue = self_properties->second_dongle->queue;
    pthread_mutex_lock(&first_d_queue->mutex_queue);
    add_request(&first_d_queue, request, scheduler);
    pthread_mutex_unlock(&first_d_queue->mutex_queue);
    pthread_mutex_lock(&second_d_queue->mutex_queue);
    add_request(&second_d_queue, request, scheduler);
    pthread_mutex_unlock(&second_d_queue->mutex_queue);

    return (0);
}
