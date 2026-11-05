#include "../../../codexion.h"

static int are_dongles_available(coder_properties_struct *coder, dongle_struct *dongles_arr);
static void reserve_n_wake(monitor_struct *monitor_p, queue_request *request, int dongle_1_index, int dongle_2_index);
static void mark_as_wanted(coder_properties_struct *coder, dongle_struct *f_dongle, dongle_struct *s_dongle);
static long  eval_requesters_brnt(config_struct *loaded_config, dongle_struct *f_dongle, dongle_struct *s_dongle);

/* Reserves dongles and wakes coder in case request is considered valid, otherwise marks dongles as requested */
int  handle_request(monitor_struct *monitor_p, queue_request *request, int *curr_index)
{
    int dongle_1_index;
    int dongle_2_index;
    dongle_struct   *f_dongle;
    dongle_struct   *s_dongle;

    dongle_1_index = request->coder->dongle_1_index;
    dongle_2_index = request->coder->dongle_2_index;
    f_dongle = &monitor_p->dongles_arr[dongle_1_index];
    s_dongle = &monitor_p->dongles_arr[dongle_2_index];
    if (are_dongles_available(request->coder, monitor_p->dongles_arr))
    {
        reserve_n_wake(monitor_p, request, dongle_1_index, dongle_2_index);
        pop_at(monitor_p->min_heap, *curr_index);
        return (1);
    }
    mark_as_wanted(request->coder, f_dongle, s_dongle);
    return (0);
}

static int are_dongles_available(coder_properties_struct *coder, dongle_struct *dongles_arr)
{
    dongle_struct *f_dongle;
    dongle_struct *s_dongle;

    f_dongle = &dongles_arr[coder->dongle_1_index];
    s_dongle = &dongles_arr[coder->dongle_2_index];
    if (f_dongle->is_wanted || s_dongle->is_wanted)
        return (!eval_requesters_brnt(&coder->monitor_ptr->loaded_config, f_dongle, s_dongle)
            && !f_dongle->is_held
            && !s_dongle->is_held
            && cooldown_check(f_dongle->cooldown_end)
            && cooldown_check(s_dongle->cooldown_end)
            && f_dongle != s_dongle);
    return (!f_dongle->is_held
        && !f_dongle->is_wanted
        && !s_dongle->is_held
        && !s_dongle->is_wanted
        && cooldown_check(f_dongle->cooldown_end)
        && cooldown_check(s_dongle->cooldown_end)
        && f_dongle != s_dongle);
}

static void reserve_n_wake(monitor_struct *monitor_p, queue_request *request, int dongle_1_index, int dongle_2_index)
{
    request->coder->monitor_ptr->dongles_arr[dongle_1_index].is_held = 1;
    request->coder->monitor_ptr->dongles_arr[dongle_2_index].is_held = 1;
    request->coder->monitor_ptr->dongles_arr[dongle_1_index].last_time_used = get_timestamp();
    request->coder->monitor_ptr->dongles_arr[dongle_2_index].last_time_used = get_timestamp();
    request->coder->has_permission = 1;
    request->coder->times_compiled++;
    update_time_to_burnout(monitor_p->loaded_config.time_to_burnout, &request->coder->to_burnout);
    pthread_cond_broadcast(&request->coder->wake_coder);
}

static void mark_as_wanted(coder_properties_struct *coder, dongle_struct *f_dongle, dongle_struct *s_dongle)
{
    if (f_dongle->is_wanted || s_dongle->is_wanted)
        return ;
    f_dongle->is_wanted = 1;
    s_dongle->is_wanted = 1;
    f_dongle->requesters_burnout = coder->to_burnout;
    s_dongle->requesters_burnout = coder->to_burnout;
}

static long  eval_requesters_brnt(config_struct *loaded_config, dongle_struct *f_dongle, dongle_struct *s_dongle)
{
    int res;
    long times_combined;

    res = 0;
    times_combined = loaded_config->time_to_compile + loaded_config->dongle_cooldown;
    if (f_dongle->is_wanted && time_from_now(&f_dongle->requesters_burnout) < times_combined)
        res++;
    if (s_dongle->is_wanted && time_from_now(&s_dongle->requesters_burnout) < times_combined)
        res++;
    return (res);
}
