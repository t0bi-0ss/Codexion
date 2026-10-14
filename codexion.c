#include "codexion.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "routines.c"

#define COMPILE_TIMES 10
#define CODERS_NUM 10

long time_since_start(long start_time);

thrds_properties_struct *init_properties(long start_time, long id);

void get_args(args_struct *args_struct, char **argv);

long time_at_start();

void free_all(args_struct *args, pthread_t **coders);

int main(int argc, char **argv)
{
    all_structs_handler *structs_handler;
    long    start_time;

    start_time = time_at_start(); // Get time at start
    structs_handler = init_all_structs(argc, argv);
    if (!structs_handler)
        return (1);
    for (long i = 0; i < CODERS_NUM; i++) // Create threads
    {
        start_values = init_properties(start_time, i);
        pthread_create(&coders[i], NULL, thread_coder, (void *) start_values);
    }
    pthread_create(&monitor, NULL, thread_watchdog, NULL);
    for (int i = 0; i < CODERS_NUM; i++) // Wait for the threads to finish
        pthread_join(coders[i], NULL);
    pthread_join(monitor, NULL);
    pthread_cond_destroy(&all_signals.coders_cond); // Destroy variables
    pthread_mutex_destroy(&all_signals.quantum_mutex);
    
    return (0);
}

thrds_properties_struct *init_properties(long start_time, long id)
{
    thrds_properties_struct *element;

    element = (thrds_properties_struct *) malloc(sizeof(thrds_properties_struct));
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

void free_all(args_struct *args, pthread_t **coders)
{
    free(args);
    free(coders);
}
