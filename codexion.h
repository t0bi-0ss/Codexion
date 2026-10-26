/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsordo-o <tsordo-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 17:47:23 by tsordo-o          #+#    #+#             */
/*   Updated: 2026/10/26 18:14:01 by tsordo-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>

// CUSTOM STRUCTS
typedef struct {
    long    id;
    long    times_compiled;
    long    req_compiles;
    int stop;
    int has_permission;
    struct  timespec last_compile;
    struct timespec to_burnout;
    pthread_mutex_t coder_mutex;
    pthread_cond_t  wake_coder;
    dongle_struct *first_dongle;
    dongle_struct *second_dongle;
    pthread_mutex_t *stdout_mutex_ptr;
    pthread_cond_t  *monitor_condvar_ptr;
    pthread_mutex_t *shared_mutex_ptr;
} coder_properties_struct;

typedef struct {
    int number_of_coders;
    long time_to_burnout;
    long time_to_compile;
    long time_to_debug;
    long time_to_refactor;
    long compiles_required;
    long dongle_cooldown;
    char *scheduler;
} config_struct;

typedef struct {
    struct timespec *time_stamp;
    pthread_cond_t  *wake_coder;
} heap_request;

typedef struct {
    int size;
    int capacity;
    heap_request   requests[3];
    pthread_mutex_t mutex_queue;
} heap;

typedef struct {
    int is_held;
    int is_wanted;
    struct timespec cooldown_end;
    pthread_mutex_t dongle_mutex;
} dongle_struct;

typedef struct {
    config_struct   loaded_config;
    pthread_t *coder_threads_arr;
    coder_properties_struct *coder_properties_arr;
    dongle_struct   *dongles_arr;
    int terminate_all;
    int all_finished;
    long start_time;
    struct timespec earliest_cooldown;
    struct timespec earliest_burnout;
    pthread_mutex_t   shared_mutex;
    pthread_mutex_t mutex_stdout;
    pthread_cond_t  wake_monitor;
} monitor_struct;

// ARGS HANDLING
int get_and_validate_args(int argc, char **argv, monitor_struct *structs_handler);

// MEMORY MANAGEMENT
void    free_memory(monitor_struct *simulation_monitor);
int allocate_memory(monitor_struct *simulation_monitor_ptr, long number_of_coders);

// HEAP

// MANAGEMENT
void    swap(heap_request *child_request, heap_request *parent_request);
void    sift_up(heap *queue, int index);

// TIME UTILS
struct timespec get_timespec();

// SIMULATION
int start_simulation(monitor_struct *simulation_monitor);

// ROUTINES
void compile(long id, int compilations);
void debug(long id);
void refactor(long id);

// THREADS
void *thread_coder(void *coder_id);
void *thread_watchdog(void *id);

// ALL STRUCTS HANDLER
monitor_struct *init_all_structs(int argc, char **argv);

# endif
