#include "../../codexion.h"

static void    finish_routine(monitor_struct *monitor_p);

void    *monitor_routine(void *properties)
{
    int i;
    monitor_struct *monitor_p;

    monitor_p = (monitor_struct *) properties;
    while(1)
    {
        pthread_mutex_lock(&monitor_p->shared_mutex);
        i = 1;
        while (i <= monitor_p->min_heap->size)
        {
            if (check_compilations_num(monitor_p, &i))
            {
                if (monitor_p->have_finished == monitor_p->loaded_config.number_of_coders)
                    return (log_event(monitor_p, "simulation finished succesfully", -1), pthread_mutex_unlock(&monitor_p->shared_mutex), NULL);
                else
                    continue;
            }
            else if (burnout_check(monitor_p, i))
                return (stop_wake_all(monitor_p->coder_properties_arr,
                    &monitor_p->loaded_config, &monitor_p->shared_mutex), NULL);
            else if (handle_request(monitor_p,
                &monitor_p->min_heap->requests[i], &i))
                continue;
            i++;
        }
        finish_routine(monitor_p);
        pthread_cond_timedwait(&monitor_p->wake_monitor, &monitor_p->shared_mutex, &monitor_p->earliest_deadline);
        pthread_mutex_unlock(&monitor_p->shared_mutex);
        monitor_p->earliest_deadline.tv_sec = 0;
        monitor_p->earliest_deadline.tv_nsec = 0;
    }
    return (NULL);
}

static void    finish_routine(monitor_struct *monitor_p)
{
    int i;

    i = 0;
    while (i < monitor_p->loaded_config.number_of_coders)
    {
        monitor_p->dongles_arr[i].is_wanted = 0;
        i++;
    }
    earliest_dead_line(monitor_p);
}
