#include "../../../codexion.h"

int check_compilations_num(monitor_struct *monitor_ptr, int *curr_index)
{
    coder_properties_struct *curr_req_coder;

    curr_req_coder = monitor_ptr->min_heap->requests[*curr_index].coder;
    if (curr_req_coder->times_compiled == monitor_ptr->loaded_config.compiles_required)
    {
        curr_req_coder->stop = 1;
        pop_at(monitor_ptr->min_heap, *curr_index);
        monitor_ptr->have_finished++;
        pthread_cond_signal(&curr_req_coder->wake_coder);
        return (1);
    }
    return (0);
}

// Returns 1 if burnout is detected
int burnout_check(monitor_struct *monitor_p)
{
    int id;
    int i;
    int coders_num;
    struct timespec *burnout_time;
    struct timespec now;

    now = get_timestamp();
    i = 0;
    coders_num = monitor_p->loaded_config.number_of_coders;
    while (i < coders_num)
    {
        id = monitor_p->coder_properties_arr[i].id;
        burnout_time = &monitor_p->coder_properties_arr[i].to_burnout;
        if (!monitor_p->coder_properties_arr[i].stop && timespec_cmp(burnout_time, &now))
        {
            log_event(monitor_p, "burned out", id);
            stop_wake_all(monitor_p->coder_properties_arr,
                &monitor_p->loaded_config, &monitor_p->shared_mutex);
            return (1);
        }
        i++;
    }
    return (0);
}

int cooldown_check(struct timespec cooldown_time)
{
    struct timespec now;

    now = get_timestamp();
    if (timespec_cmp(&cooldown_time, &now))
        return (1);
    return (0);
}
