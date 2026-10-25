#include "../../../codexion.h"

void update_time_to_burnout(long burnout_time, struct timespec *time_to_burnout)
{
	struct timespec current_time;
	
    current_time = get_timespec();
    time_to_burnout->tv_sec = current_time.tv_sec + burnout_time / 1000;
    time_to_burnout->tv_nsec = current_time.tv_nsec + burnout_time % 1000 * 1000000;
}
