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
int burnout_check(monitor_struct *monitor_p, int index)
{
    int id;
    struct timespec *burnout_time;
    struct timespec now;

    id = monitor_p->min_heap->requests[index].coder->id;
    now = get_timestamp();
    burnout_time = &monitor_p->min_heap->requests[index].coder->to_burnout;
    if (timespec_cmp(burnout_time, &now))
    {
        log_event(monitor_p, "burned out", id);
        return (1);
    }
    return (0);
}

int cooldown_check(struct timespec cooldown_time)
{
    struct timespec now;

    now = get_timestamp();
    if (cooldown_time.tv_sec < now.tv_sec)
        return (1);
    if (cooldown_time.tv_sec == now.tv_sec)
        return (cooldown_time.tv_nsec <= now.tv_nsec);
    return (0);
}
