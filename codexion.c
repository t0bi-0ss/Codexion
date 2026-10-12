#include "codexion.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "routines.c"

#define COMPILE_TIMES 10
#define CODERS_NUM 10

long time_since_start(long start_time);

thrds_properties *init_properties(long start_time, long id);

void get_args(all_args *args_struct, char **argv);

long time_at_start();

void init_signals(signals *signals_pointer);

void free_all(all_args *args, pthread_t **coders);

int main(int argc, char **argv)
{
    pthread_t **coders;
    pthread_t monitor;
    long    start_time;
    thrds_properties *start_values;
    signals all_signals;
    all_args input_args;

    if (validate_args(argc, argv, &input_args))
        return (1);
    init_signals(&all_signals); // Initialize signals
    coders = (pthread_t **) malloc(sizeof(pthread_t *) * CODERS_NUM); // Allocate memory for coders
    if (!coders)
        return (1);
    start_time = time_at_start(); // Get time at start
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

thrds_properties *init_properties(long start_time, long id)
{
    thrds_properties *element;

    element = (thrds_properties *) malloc(sizeof(thrds_properties));
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

void init_signals(signals *signals_pointer)
{
    pthread_mutex_init(&signals_pointer->quantum_mutex, NULL);
    pthread_cond_init(&signals_pointer->watchdog_cond, NULL);
    signals_pointer->can_compile = 0;
    signals_pointer->all_finished = 0;
    signals_pointer->terminate_all = 0;
}

long time_at_start()
{
    struct timeval now;

    gettimeofday(&now, NULL);
    return (now.tv_usec);
}

void free_all(all_args *args, pthread_t **coders)
{
    free(args);
    free(coders);
}
