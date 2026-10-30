#include "../../../codexion.h"

static struct timespec  earliest_cd(dongle_struct *dongles_arr, int num);
static struct timespec earliest_brnt(monitor_struct *monitor_p);

// Modifies earliest_dead_line monitor's property comparing all burnouts and cooldowns
void  earliest_dead_line(monitor_struct *monitor_ptr)
{
    struct timespec early_brnt;
    struct timespec early_cd;

    early_brnt = earliest_brnt(monitor_ptr);
    early_cd = earliest_cd(monitor_ptr->dongles_arr, monitor_ptr->loaded_config.number_of_coders);
    if (early_cd.tv_sec != 0 && timespec_cmp(&early_cd, &early_brnt))
        monitor_ptr->earliest_deadline = early_cd;
    else
        monitor_ptr->earliest_deadline = early_brnt;
}

// Returns earliest brnt found among requests array
static struct timespec earliest_brnt(monitor_struct *monitor_p)
{
    int i;
    int coders_num;
    coder_properties_struct *coders_arr;
    struct timespec earliest_brnt_found;

    coders_num = monitor_p->loaded_config.number_of_coders;
    coders_arr = monitor_p->coder_properties_arr;
    i = 0;
    while (i < coders_num)
    {
        if (earliest_brnt_found.tv_sec == 0)
            earliest_brnt_found = coders_arr[i].to_burnout;
        else
            if (timespec_cmp(&coders_arr[i].to_burnout, &earliest_brnt_found))
                earliest_brnt_found = coders_arr[i].to_burnout;
        i++;
    }
    return (earliest_brnt_found);
}

// Returns earliest cd found among dongles array
static struct timespec  earliest_cd(dongle_struct *dongles_arr, int num)
{
    int i;
    struct timespec now;
    struct timespec earliest_cd_found;
    
    i = 0;
    now = get_timestamp();
    while (i < num)
    {
        if (dongles_arr[i].in_cd)
        {
            if (earliest_cd_found.tv_sec == 0)
                earliest_cd_found = dongles_arr[i].cooldown_end;
            else
                if (timespec_cmp(&dongles_arr[i].cooldown_end, &earliest_cd_found)
                    && timespec_cmp(&now, &dongles_arr[i].cooldown_end))
                    earliest_cd_found = dongles_arr[i].cooldown_end;
        }
        i++;
    }
    return (earliest_cd_found);
}
