#include "codexion.h"

int burnout_check(struct timespec compilation_last_time, long burnout_time)
{
    struct timespec now;
    long compilation_total_time;
    long current_total_time;

    now = get_timespec();
    compilation_total_time = compilation_last_time.tv_sec * 1000 + compilation_last_time.tv_nsec / 1000;
    current_total_time = now.tv_sec * 1000 + now.tv_nsec / 1000;
    if (burnout_time <= current_total_time - compilation_total_time)
        return (1);
    return (0);
}
