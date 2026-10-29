#include "../../../codexion.h"

void static    update_dongle(dongle_struct *dongle_ptr, long dongle_cooldown);
void static    update_cooldown(long dongle_cooldown, struct timespec *cooldown_end);

void    update_both_dongles(coder_properties_struct *coder_p)
{
    long    dongle_cooldown;
    dongle_struct   *dongles_arr;
    dongle_struct   *dongle_one;
    dongle_struct   *dongle_two;

    dongle_cooldown = coder_p->monitor_ptr->loaded_config.dongle_cooldown;
    dongles_arr = coder_p->monitor_ptr->dongles_arr;
    dongle_one = &dongles_arr[coder_p->dongle_1_index];
    dongle_two = &dongles_arr[coder_p->dongle_2_index];
    update_dongle(dongle_one, dongle_cooldown);
    update_dongle(dongle_two, dongle_cooldown);
}

void static    update_dongle(dongle_struct *dongle_ptr, long dongle_cooldown)
{
    dongle_ptr->is_held = 0;
    dongle_ptr->in_cd = 1;
    update_cooldown(dongle_cooldown, &dongle_ptr->cooldown_end);
}

void static    update_cooldown(long dongle_cooldown, struct timespec *cooldown_end)
{
    struct timespec updated;

    updated = get_timestamp();
    cooldown_end->tv_sec = updated.tv_sec + dongle_cooldown / 1000;
    cooldown_end->tv_nsec = updated.tv_nsec + dongle_cooldown % 1000 * 1000000;
}
