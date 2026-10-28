#include "../../codexion.h"

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
