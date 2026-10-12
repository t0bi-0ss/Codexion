
#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>

// CUSTOM STRUCTS
typedef struct {
    long start_time;
    long id;
    long times_compiled;
} thrds_properties;

typedef struct {
    long number_of_coders;
    long time_to_burnout;
    long time_to_compile;
    long time_to_debug;
    long time_to_refactor;
    long number_of_compiles_required;
    long dongle_cooldown;
    char *scheduler;
} coder_properties;

typedef struct {
    pthread_mutex_t quantum_mutex;
    int can_compile;
    int all_finished;
    int terminate_all;
    pthread_cond_t watchdog_cond;
    pthread_cond_t coders_cond;
} signals;

typedef struct {
    long number_of_coders;
    long time_to_burnout;
    long time_to_compile;
    long time_to_debug;
    long time_to_refactor;
    long number_of_compiles_required;
    long dongle_cooldown;
    char *scheduler;
} all_args;

// ARGS HANDLING
int validate_args(int argc, char **argv, all_args *args_struct);

// ROUTINES
void compile(long id, int compilations);
void debug(long id);
void refactor(long id);

// THREADS
void *thread_coder(void *coder_id);
void *thread_watchdog(void *id);

# endif