#include "../../../codexion.h"

static int check_compilations_num(coder_properties_struct *coder_ptr);
static int are_dongles_available(dongle_struct *dongles_arr, int dong_1_index, int dong_2_index);
static void reserve_n_wake(heap_request *request, int dongle_1_index, int dongle_2_index);
static void mark_as_wanted(heap_request *request, int dongle_1_index, int dongle_2_index);

int  handle_request(dongle_struct *dongles_arr, heap_request *request, int request_index)
{
    int i;
    int dongle_1_index;
    int dongle_2_index;

    dongle_1_index = request->coder->dongle_1_index;
    dongle_2_index = request->coder->dongle_2_index;
    if (are_dongles_available(dongles_arr, dongle_1_index, dongle_2_index))
    {
        reserve_n_wake(request, dongle_1_index, dongle_2_index);
        return (1);
    }
    mark_as_wanted(request, dongle_1_index, dongle_2_index);
    return (0);
}
static int check_compilations_num(coder_properties_struct *coder_ptr)
{
    if (coder_ptr->times_compiled
    == coder_ptr->monitor_ptr->loaded_config.compiles_required)
    coder_ptr->stop = 1;
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

static void reserve_n_wake(heap_request *request, int dongle_1_index, int dongle_2_index)
{
    request->coder->monitor_ptr->dongles_arr[dongle_1_index].is_held = 1;
    request->coder->monitor_ptr->dongles_arr[dongle_2_index].is_held = 1;
    request->coder->has_permission = 1;
    pthread_cond_signal(&request->coder->wake_coder);
}

static void mark_as_wanted(heap_request *request, int dongle_1_index, int dongle_2_index)
{
    request->coder->monitor_ptr->dongles_arr[dongle_1_index].is_wanted = 1;
    request->coder->monitor_ptr->dongles_arr[dongle_2_index].is_wanted = 1;
}

