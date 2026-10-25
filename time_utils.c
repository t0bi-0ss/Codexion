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
