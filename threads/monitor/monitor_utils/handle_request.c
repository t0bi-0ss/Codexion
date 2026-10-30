#include "../../../codexion.h"

static int are_dongles_available(dongle_struct *dongles_arr, int dong_1_index, int dong_2_index);
static void reserve_n_wake(monitor_struct *monitor_p, queue_request *request, int dongle_1_index, int dongle_2_index);
static void mark_as_wanted(queue_request *request, int dongle_1_index, int dongle_2_index);

// Reserves dongles and wakes coder in case request is considered valid, otherwise marks dongles as requested
int  handle_request(monitor_struct *monitor_p, queue_request *request, int *curr_index)
{
    int dongle_1_index;
    int dongle_2_index;

    dongle_1_index = request->coder->dongle_1_index;
    dongle_2_index = request->coder->dongle_2_index;
    if (are_dongles_available(monitor_p->dongles_arr, dongle_1_index, dongle_2_index))
    {
        reserve_n_wake(monitor_p, request, dongle_1_index, dongle_2_index);
        pop_at(monitor_p->min_heap, *curr_index);
        return (1);
    }
    mark_as_wanted(request, dongle_1_index, dongle_2_index);
    return (0);
}

static int are_dongles_available(dongle_struct *dongles_arr, int dong_1_index, int dong_2_index)
{
    return (!dongles_arr[dong_1_index].is_held
        && !dongles_arr[dong_1_index].is_wanted
        && !dongles_arr[dong_2_index].is_held
        && !dongles_arr[dong_2_index].is_wanted
        && cooldown_check(dongles_arr[dong_1_index].cooldown_end)
        && cooldown_check(dongles_arr[dong_2_index].cooldown_end));
}

static void reserve_n_wake(monitor_struct *monitor_p, queue_request *request, int dongle_1_index, int dongle_2_index)
{
    request->coder->monitor_ptr->dongles_arr[dongle_1_index].is_held = 1;
    request->coder->monitor_ptr->dongles_arr[dongle_2_index].is_held = 1;
    request->coder->has_permission = 1;
    request->coder->times_compiled++;
    update_time_to_burnout(monitor_p->loaded_config.time_to_burnout, &request->coder->to_burnout);
    pthread_cond_signal(&request->coder->wake_coder);
}

static void mark_as_wanted(queue_request *request, int dongle_1_index, int dongle_2_index)
{
    dongle_struct   *f_dongle;
    dongle_struct   *s_dongle;

    f_dongle = &request->coder->monitor_ptr->dongles_arr[dongle_1_index];
    s_dongle = &request->coder->monitor_ptr->dongles_arr[dongle_2_index];
    if (f_dongle->is_wanted || s_dongle->is_wanted)
        return ;
    f_dongle->is_wanted = 1;
    s_dongle->is_wanted = 1;
}

