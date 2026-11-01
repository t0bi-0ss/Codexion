#include "../../../codexion.h"

static int are_dongles_available(coder_properties_struct *coder, dongle_struct *dongles_arr);
static void reserve_n_wake(monitor_struct *monitor_p, queue_request *request, int dongle_1_index, int dongle_2_index);
static void mark_as_wanted(dongle_struct *f_dongle, dongle_struct *s_dongle);
static long  evaluate_wait_time(coder_properties_struct *coder, dongle_struct *f_dongle, dongle_struct *s_dongle);

// Reserves dongles and wakes coder in case request is considered valid, otherwise marks dongles as requested
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
    mark_as_wanted(f_dongle, s_dongle);
    return (0);
}

static int are_dongles_available(coder_properties_struct *coder, dongle_struct *dongles_arr)
{
    dongle_struct *f_dongle;
    dongle_struct *s_dongle;

    f_dongle = &dongles_arr[coder->dongle_1_index];
    s_dongle = &dongles_arr[coder->dongle_2_index];
    if (f_dongle->is_wanted || s_dongle->is_wanted)
        return (evaluate_wait_time(coder, f_dongle, s_dongle)
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
    pthread_cond_signal(&request->coder->wake_coder);
}

static void mark_as_wanted(dongle_struct *f_dongle, dongle_struct *s_dongle)
{
    if (f_dongle->is_wanted || s_dongle->is_wanted)
        return ;
    f_dongle->is_wanted = 1;
    s_dongle->is_wanted = 1;
}

static long  evaluate_wait_time(coder_properties_struct *coder, dongle_struct *f_dongle, dongle_struct *s_dongle)
{
    long f_wait;
    long s_wait;
    long times_combined;
    long    time_to_burnout;
    config_struct   *loaded_config;

    f_wait = time_until_now(&f_dongle->last_time_used);
    s_wait = time_until_now(&s_dongle->last_time_used);
    loaded_config = &coder->monitor_ptr->loaded_config;
    times_combined = loaded_config->dongle_cooldown + loaded_config->time_to_compile + loaded_config->time_to_debug + loaded_config->time_to_refactor;
    time_to_burnout = time_from_now(&coder->to_burnout);
    times_combined += time_to_burnout;
    if (f_wait > s_wait)
        return (f_wait < times_combined);
    return (s_wait < times_combined);
}
