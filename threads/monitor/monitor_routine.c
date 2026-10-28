#include "../../codexion.h"

static int  check_requests(monitor_struct *monitor_p);

void    monitor_routine(void *properties)
{
    monitor_struct *monitor_p;

    monitor_p = (monitor_struct *) properties;
    while(1)
    {
        pthread_mutex_lock(&monitor_p->shared_mutex);
        if (monitor_p->have_finished == monitor_p->loaded_config.number_of_coders)
            return ((void) pthread_mutex_lock(&monitor_p->shared_mutex));
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

static int  check_requests(monitor_struct *monitor_p)
{
    int i;
    int dongle_1_index;
    int dongle_2_index;

    i = 0;
    while (i <= monitor_p->min_heap->size)
    {
        dongle_1_index = monitor_p->min_heap->requests[i].coder->dongle_1_index;
        dongle_2_index = monitor_p->min_heap->requests[i].coder->dongle_2_index;
        if (!monitor_p->dongles_arr[dongle_1_index].is_held &&
        !monitor_p->dongles_arr[dongle_2_index].is_held)
    }
}

