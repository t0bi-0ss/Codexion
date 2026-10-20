#include "codexion.h"

int start_simulation(monitor_struct *simulation_monitor)
{
    long    coders_num;

    simulation_monitor->terminate_all = 0;
    simulation_monitor->all_finished = 0;
    coders_num = simulation_monitor->loaded_config.number_of_coders;
    if (pthread_mutex_init(&simulation_monitor->mutex_stdout, NULL))
        return (1);
    while (!simulation_monitor->terminate_all && simulation_monitor->all_finished != coders_num)
        scheduler(simulation_monitor);

    return (0);
}
