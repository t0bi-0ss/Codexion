#include "codexion.h"

void    init_monitor(monitor_struct *simulation_monitor)
{
    simulation_monitor->coder_threads_arr = NULL;
    simulation_monitor->coder_properties_arr = NULL;
    simulation_monitor->dongles_arr = NULL;

}

void    free_memory(monitor_struct *simulation_monitor)
{
    if (simulation_monitor->coder_threads_arr)
        free(simulation_monitor->coder_threads_arr);
    if (simulation_monitor->coder_properties_arr)
        free(simulation_monitor->coder_properties_arr);
    if (simulation_monitor->dongles_arr)
        free(simulation_monitor->dongles_arr);
}

int allocate_memory(monitor_struct *simulation_monitor_ptr, long number_of_coders)
{
    simulation_monitor_ptr->coder_threads_arr = malloc(sizeof(pthread_t) * number_of_coders);
    if (!simulation_monitor_ptr->coder_threads_arr)
        return (1);
    simulation_monitor_ptr->coder_properties_arr = malloc(sizeof(coder_properties_struct) * number_of_coders);
    if (!simulation_monitor_ptr->coder_properties_arr)
    {
        free_memory(simulation_monitor_ptr);
        return (1);
    }
    simulation_monitor_ptr->dongles_arr = malloc(sizeof(dongle_struct) * number_of_coders);
    if (!simulation_monitor_ptr->dongles_arr)
    {
        free_memory(simulation_monitor_ptr);
        return (1);
    }

    return (0);
}
