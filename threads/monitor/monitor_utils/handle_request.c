#include "../../../codexion.h"

static int are_dongles_available(dongle_struct *dongles_arr, int dong_1_index, int dong_2_index);
static void reserve_n_wake(heap_request *request, int dongle_1_index, int dongle_2_index);
static void mark_as_wanted(heap_request *request, int dongle_1_index, int dongle_2_index);

void  handle_request(dongle_struct *dongles_arr, heap_request *request)
{
    int i;
    int dongle_1_index;
    int dongle_2_index;

    dongle_1_index = request->coder->dongle_1_index;
    dongle_2_index = request->coder->dongle_2_index;
    if (are_dongles_available(dongles_arr, dongle_1_index, dongle_2_index))
        reserve_n_wake(request, dongle_1_index, dongle_2_index);
    else
        mark_as_wanted(request, dongle_1_index, dongle_2_index);
}

static int are_dongles_available(dongle_struct *dongles_arr, int dong_1_index, int dong_2_index)
{
    return (!dongles_arr[dong_1_index].is_held
        && !dongles_arr[dong_1_index].is_wanted
        && !dongles_arr[dong_2_index].is_held
        && !dongles_arr[dong_2_index].is_wanted);
}

static void reserve_n_wake(heap_request *request, int dongle_1_index, int dongle_2_index)
{
    request->coder->monitor_ptr->dongles_arr[dongle_1_index].is_held = 1;
    request->coder->monitor_ptr->dongles_arr[dongle_2_index].is_held = 1;
    pthread_cond_signal(&request->coder->wake_coder);
}

static void mark_as_wanted(heap_request *request, int dongle_1_index, int dongle_2_index)
{
    request->coder->monitor_ptr->dongles_arr[dongle_1_index].is_wanted = 1;
    request->coder->monitor_ptr->dongles_arr[dongle_2_index].is_wanted = 1;
}

