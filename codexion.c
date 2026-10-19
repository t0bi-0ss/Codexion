#include "codexion.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "routines.c"

#define COMPILE_TIMES 10
#define CODERS_NUM 10

long time_since_start(long start_time);

coder_properties_struct *init_properties(long start_time, long id);

void get_args(config_struct *config_struct, char **argv);

long time_at_start();

void free_all(config_struct *args, pthread_t **coders);

int main(int argc, char **argv)
{
    monitor_struct *structs_handler;
    long    start_time;

    start_time = time_at_start(); // Get time at start
    
    return (0);
}

int allocate_memory(monitor_struct *simulation_monitor_ptr, long number_of_coders)
{
    simulation_monitor_ptr->coder_threads_arr = malloc(sizeof(pthread_t) * number_of_coders);
    if (!simulation_monitor_ptr->coder_threads_arr)
        return (1);
    simulation_monitor_ptr->coder_properties_arr = malloc(sizeof(coder_properties_struct) * number_of_coders);
    if (!simulation_monitor_ptr->coder_properties_arr)
    {
        free(simulation_monitor_ptr->coder_threads_arr);
        return (1);
    }
    simulation_monitor_ptr->dongles_arr = malloc(sizeof(dongle_struct) * number_of_coders);
    if (!simulation_monitor_ptr->dongles_arr)
    {
        free(simulation_monitor_ptr->coder_threads_arr);
        free(simulation_monitor_ptr->coder_properties_arr);
        return (1);
    }
    simulation_monitor_ptr->threads_properties_arr = malloc(sizeof(coder_properties_struct) * number_of_coders);
    if (!simulation_monitor_ptr->threads_properties_arr)
    {
        free(simulation_monitor_ptr->coder_threads_arr);
        free(simulation_monitor_ptr->coder_properties_arr);
        free(simulation_monitor_ptr->threads_properties_arr);
        return (1);
    }
    return (0);
}

int init_dongle(int id, long cooldown, dongle_struct *dongle_ptr)
{
    dongle_ptr->id = id;
    dongle_ptr->is_available = 1;
    dongle_ptr->last_time_used = 0;
    dongle_ptr->dongle_cooldown = cooldown;
    if (pthread_mutex_init(&dongle_ptr->dongle_mutex, NULL))
        return (1);
    if (pthread_cond_init(&dongle_ptr->dongle_cond, NULL))
        return (1);
    return (0);
}

int init_all_dongles(monitor_struct *sim_mon_ptr)
{
    int i;

    i = 0;
    while (i < sim_mon_ptr->loaded_config->number_of_coders)
    {
        i++;
    }

}

int start_threads(monitor_struct *sim_mon_ptr)
{

}

void    work_simulation(long start_time, config_struct *loaded_config)
{
    monitor_struct  simulation_monitor;

    simulation_monitor.all_finished = 0;
    simulation_monitor.terminate_all = 0;
    simulation_monitor.start_time = start_time;
    simulation_monitor.loaded_config = loaded_config;
    allocate_memory(&simulation_monitor, loaded_config->number_of_coders);
}

coder_properties_struct *init_properties(long start_time, long id)
{
    coder_properties_struct *element;

    element = (coder_properties_struct *) malloc(sizeof(coder_properties_struct));
    if (!element)
        return (NULL);
    element->id = id;
    element->start_time = start_time;
    element->times_compiled = 0;

    return (element);
}

long time_since_start(long start_time)
{
    struct timeval now;
    long diff;

    gettimeofday(&now, NULL);
    diff = now.tv_usec - start_time;
    
    return (diff);
}

long time_at_start()
{
    struct timeval now;

    gettimeofday(&now, NULL);
    return (now.tv_usec);
}

void free_all(config_struct *args, pthread_t **coders)
{
    free(args);
    free(coders);
}
