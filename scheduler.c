#include "codexion.h"

void    fifo_scheduler(monitor_struct *simulation_monitor);

void    scheduler(monitor_struct *simulation_monitor)
{
    char *schedule;

    schedule = simulation_monitor->loaded_config.scheduler;
    i = 0;
    if (!strncmp("fifo", schedule, 5))
        fifo_scheduler(simulation_monitor);
    else
        edf_scheduler(simulation_monitor);
}

void    fifo_scheduler(monitor_struct *simulation_monitor)
{
    int i;
    int coders_num;
    dongle_struct   *dongles_arr;

    dongles_arr = simulation_monitor->dongles_arr;
    coders_num = simulation_monitor->loaded_config.number_of_coders;
    while (continue_simulation(simulation_monitor))
    {
        i = 0;
        while (i < coders_num)
        {
            pthread_cond_signal(&dongles_arr[i].queue[0].wake_coder);
            i++;
        }
    }
}

void    edf_scheduler(monitor_struct *simulation_monitor)
{
    int i;
    int coders_num;
    dongle_struct   *dongles_arr;

    dongles_arr = simulation_monitor->dongles_arr;
    coders_num = simulation_monitor->loaded_config.number_of_coders;
    while (continue_simulation(simulation_monitor))
    {
        i = 0;
        while (i < coders_num)
        {
            pthread_cond_signal(&dongles_arr[i].queue[0].wake_coder);
            i++;
        }
    }
}

void    check_for_edf(dongle_struct dongle)
{
    pthread_cond_t  *wake_me;

    
}
