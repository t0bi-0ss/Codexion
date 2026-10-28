#include "../../../codexion.h"

static struct timespec cd_n_brnt_cmp(dongle_struct *dongles_arr, heap_request *request);

struct timespec  earliest_dead_line(heap *p_queue, dongle_struct *dongles_arr)
{
    int i;
    struct timespec early;

    i = 1;
    while (1 <= p_queue->size)

}

static struct timespec cd_n_brnt_cmp(dongle_struct *dongles_arr, heap_request *request)
{
    int dongle_1_index;
    int dongle_2_index;
    dongle_struct   *dongles_arr;
    struct timespec *burnout_ptr;
    struct timespec *d1_cd_ptr;
    struct timespec *d2_cd_ptr;

    dongle_1_index = &request->coder->dongle_1_index;
    dongle_2_index = &request->coder->dongle_2_index;
    dongles_arr = request->coder->monitor_ptr->dongles_arr;
    burnout_ptr = &request->coder->to_burnout;
    d1_cd_ptr = &request->coder->dongle_1_index
    if (timespec_cmp())
}
