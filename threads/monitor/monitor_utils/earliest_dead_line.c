#include "../../../codexion.h"

static struct timespec  *earliest_cd(dongle_struct *dongles_arr, int num);
static struct timespec *earliest_brnt(queue_struct *heap_ptr);

// Modifies earliest_dead_line monitor's property comparing all burnouts and cooldowns
void  earliest_dead_line(monitor_struct *monitor_ptr)
{
    struct timespec *early_brnt;
    struct timespec *early_cd;

    early_brnt = earliest_brnt(monitor_ptr->min_heap);
    early_cd = earliest_cd(monitor_ptr->dongles_arr, monitor_ptr->loaded_config.number_of_coders);
    if (timespec_cmp(early_cd, early_brnt))
        monitor_ptr->earliest_deadline = early_cd;
    else
        monitor_ptr->earliest_deadline = early_brnt;
}

// Returns earliest brnt found among requests array
static struct timespec *earliest_brnt(queue_struct *heap_ptr)
{
    int i;
    queue_request    *requests_arr;
    struct timespec *earliest_brnt_found;

    i = 1;
    requests_arr = heap_ptr->requests;
    earliest_brnt_found = NULL;
    while (i <= heap_ptr->size)
    {
        if (!earliest_brnt_found)
            earliest_brnt_found = &requests_arr[i].coder->to_burnout;
        else
            if (timespec_cmp(&requests_arr[i].coder->to_burnout, earliest_brnt_found))
                earliest_brnt_found = &requests_arr[i].coder->to_burnout;
        i++;
    }
    return (earliest_brnt_found);
}

// Returns earliest cd found among dongles array
static struct timespec  *earliest_cd(dongle_struct *dongles_arr, int num)
{
    int i;
    struct timespec *earliest_cd_found;
    
    i = 0;
    earliest_cd_found = NULL;
    while (i < num)
    {
        if (dongles_arr[i].in_cd)
        {
            if (!earliest_cd_found)
                earliest_cd_found = &dongles_arr[i].cooldown_end;
            else
                if (timespec_cmp(&dongles_arr[i].cooldown_end, earliest_cd_found))
                    earliest_cd_found = &dongles_arr[i].cooldown_end;
        }
        i++;
    }
    return (earliest_cd_found);
}
