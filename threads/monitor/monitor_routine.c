#include "../../codexion.h"

static struct timespec  earliest_dead_line(heap *p_queue);

void    monitor_routine(void *properties)
{
    int i;
    monitor_struct *monitor_p;

    monitor_p = (monitor_struct *) properties;
    pthread_mutex_lock(&monitor_p->shared_mutex);
    while(1)
    {
        i = 1;
        while (i <= monitor_p->min_heap->size)
        {
            if (monitor_p->have_finished == monitor_p->loaded_config.number_of_coders)
                return ((void) pthread_mutex_unlock(&monitor_p->shared_mutex));
            if (check_compilations_num(&monitor_p->min_heap->requests[i], &monitor_p->loaded_config))
            {
                monitor_p->min_heap->requests[i].coder->stop = 1;
                pop_at(monitor_p->min_heap, i);
            }
            else if (burnout_check(monitor_p->min_heap->requests[i].coder->to_burnout))
                stop_wake_all(monitor_p->coder_threads_arr, &monitor_p->loaded_config);
            else if (handle_request(monitor_p->dongles_arr,
                &monitor_p->min_heap->requests[i], i))
                pop_at(monitor_p->min_heap, i);
            i++;
        }
        pthread_cond_timedwait(&monitor_p->wake_monitor, &monitor_p->shared_mutex)
        // check requests
            // check requester's burnout
                // if burnout detected
                    // stop all coders
                    // wake them all
            // check compilation times
                // if max reached set coder's stop flag
                // increment own have_finished counter
                // continue to signal coder
            // check if dongles are available
                // if NOT mark them as requested
            // if available mark them as HELD
            // set coder's permission flag
            // signal coder
    }
}

static struct timespec  earliest_dead_line(heap *p_queue)
{
    int i;
    struct timespec early;

    i = 1;
    while (1 <= p_queue->size)

}
