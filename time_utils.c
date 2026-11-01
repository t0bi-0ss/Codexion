#include "codexion.h"

struct timespec get_timestamp()
{
    struct timeval now;
    struct timespec updated;

    gettimeofday(&now, NULL);
    updated.tv_sec = now.tv_sec;
    updated.tv_nsec = now.tv_usec * 1000;
    return (updated);
}

// Returns 1 if first_stamp occurs sooner than second_stamp
int timespec_cmp(struct timespec *first_stamp, struct timespec *second_stamp)
{
    if (!second_stamp || second_stamp->tv_sec == 0)
        return (1);
    if (!first_stamp)
        return (0);
    if (first_stamp->tv_sec != second_stamp->tv_sec)
        return (first_stamp->tv_sec < second_stamp->tv_sec);
    return (first_stamp->tv_nsec < second_stamp->tv_nsec);
}

void update_time_to_burnout(long burnout_time, struct timespec *time_to_burnout)
{
	struct timespec current_time;
	
    current_time = get_timestamp();
    // printf("CURRENT TIME %ld\n", current_time.tv_sec);
    // printf("TIME TO ADD %ld\n", burnout_time);
    timespec_add_time(&current_time, burnout_time);
    time_to_burnout->tv_sec = current_time.tv_sec;
    // printf("BRNT TIME %ld\n", time_to_burnout->tv_sec);
    time_to_burnout->tv_nsec = current_time.tv_nsec;
}

void    timespec_add_time(struct timespec *time_stamp, long time_ms)
{
    time_stamp->tv_sec += time_ms / 1000;
    time_stamp->tv_nsec += (time_ms % 1000) * 1000000;
    if (time_stamp->tv_nsec >= 1000000000)
    {
        time_stamp->tv_sec += time_stamp->tv_nsec / 1000000000;
        time_stamp->tv_nsec %= 1000000000;
    }
}
