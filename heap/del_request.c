#include "../codexion.h"

void    del_request(coder_properties_struct *coder_p)
{
    int i;

    i = 1;
    pthread_mutex_lock(&coder_p->monitor_ptr->shared_mutex);
    while (i <= coder_p->monitor_ptr->loaded_config.number_of_coders)
    {
        if (coder_p->monitor_ptr->min_heap->requests[i].coder == coder_p)
        {
            pop_at(coder_p->monitor_ptr->min_heap, i);
            break;
        }
        i++;
    }
    pthread_mutex_unlock(&coder_p->monitor_ptr->shared_mutex);
    if (i > coder_p->monitor_ptr->loaded_config.number_of_coders)
        fprintf(stderr, "Could not find request to be deleted!\n");
}
