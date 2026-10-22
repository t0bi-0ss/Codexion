#include "codexion.h"

void update_time_to_burnout(long burnout_time, struct timespec *time_to_burnout)
{
	struct timespec current_time;
	
    current_time = get_timespec();
    time_to_burnout->tv_sec = current_time.tv_sec + burnout_time / 1000;
    time_to_burnout->tv_nsec = current_time.tv_nsec;
}

void *thread_coder(void *properties)
{
    coder_properties_struct *start_values;

    start_values = (coder_properties_struct *) properties;
    update_time_to_burnout(start_values->config->time_to_burnout, &start_values->time_to_burnout);
    while (start_values->times_compiled < start_values->config->number_of_compiles_required)
    {

    }
    free(properties);
    return (NULL);
}
