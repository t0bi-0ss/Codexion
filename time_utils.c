#include "codexion.h"

struct timespec get_timespec()
{
    struct timeval now;
    struct timespec updated;

    gettimeofday(&now, NULL);
    updated.tv_sec = now.tv_sec;
    updated.tv_nsec = now.tv_usec;
    return (updated);
}

int timespec_min(struct timespec *curr_min, struct timespec *candidate)
{
    long curr_min_total;
    long candidate_total;

    if (!candidate)
        return (-1);
    if (!curr_min)
        return (1);
    curr_min_total = curr_min->tv_nsec / 1000 + curr_min->tv_sec * 1000;
    candidate_total = candidate->tv_nsec / 1000 + candidate->tv_sec * 1000;
    if (candidate_total < curr_min_total)
        return (1);
    return (0);
}

void update_time_to_burnout(long burnout_time, struct timespec *time_to_burnout)
{
	struct timespec current_time;
	
    current_time = get_timespec();
    time_to_burnout->tv_sec = current_time.tv_sec + burnout_time / 1000;
    time_to_burnout->tv_nsec = current_time.tv_nsec;
}
