#include "codexion.h"

struct timespec get_timestamp()
{
    struct timeval now;
    struct timespec updated;

    gettimeofday(&now, NULL);
    updated.tv_sec = now.tv_sec;
    updated.tv_nsec = now.tv_usec;
    return (updated);
}

// Returns 1 if first_stamp occurs sooner than second_stamp
int timespec_cmp(struct timespec *first_stamp, struct timespec *second_stamp)
{
    long first_stamp_total;
    long second_stamp_total;

    if (!second_stamp)
        return (1);
    if (!first_stamp)
        return (0);
    first_stamp_total = first_stamp->tv_nsec / 1000 + first_stamp->tv_sec * 1000;
    second_stamp_total = second_stamp->tv_nsec / 1000 + second_stamp->tv_sec * 1000;
    return (first_stamp_total < second_stamp_total);
}

void update_time_to_burnout(long burnout_time, struct timespec *time_to_burnout)
{
	struct timespec current_time;
	
    current_time = get_timestamp();
    time_to_burnout->tv_sec = current_time.tv_sec + burnout_time / 1000;
    time_to_burnout->tv_nsec = current_time.tv_nsec;
}
