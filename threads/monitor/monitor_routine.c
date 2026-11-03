#include "../../codexion.h"

static void    finish_routine(monitor_struct *monitor_p);
static int  parse_requests(monitor_struct *monitor_p);

void    *monitor_routine(void *properties)
{
    monitor_struct *monitor_p;

    monitor_p = (monitor_struct *) properties;
    pthread_mutex_lock(&monitor_p->shared_mutex);
    while(1)
    {
        if (burnout_check(monitor_p))
            break ;
        if (parse_requests(monitor_p))
            break ;
        finish_routine(monitor_p);
        pthread_cond_timedwait(&monitor_p->wake_monitor, &monitor_p->shared_mutex, &monitor_p->earliest_deadline);
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

static int  parse_requests(monitor_struct *monitor_p)
{
    int i;

    i = 1;
    while (i <= monitor_p->min_heap->size)
        {
            if (check_compilations_num(monitor_p, &i))
            {
                if (monitor_p->have_finished == monitor_p->loaded_config.number_of_coders)
                {
                    log_event(monitor_p, "simulation finished succesfully", -1);
                    pthread_mutex_unlock(&monitor_p->shared_mutex);
                    return (1);
                }
                else
                    continue;
            }
            if (handle_request(monitor_p, &monitor_p->min_heap->requests[i], &i))
                continue;
            i++;
        }
    return (0);
}
