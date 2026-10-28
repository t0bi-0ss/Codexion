/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsordo-o <tsordo-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 17:47:23 by tsordo-o          #+#    #+#             */
/*   Updated: 2026/10/28 18:40:44 by tsordo-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

// ENUMS
typedef enum scheduler {
    FIFO, EDF
} Scheduler;

typedef enum coder_actions {
    COMPILE, DEBUG, REFACTOR, GRAB
} Coder_actions;

// CUSTOM STRUCTS
typedef struct {
    int number_of_coders;
    long time_to_burnout;
    useconds_t time_to_compile;
    useconds_t time_to_debug;
    useconds_t time_to_refactor;
    long compiles_required;
    long dongle_cooldown;
    Scheduler   scheduler_config;
} config_struct;

typedef struct {
    long    id;
    long    times_compiled;
    int stop;
    int has_permission;
    struct  timespec last_compile;
    struct timespec to_burnout;
    pthread_mutex_t coder_mutex;
    pthread_cond_t  wake_coder;
    int dongle_1_index;
    int dongle_2_index;
    monitor_struct  *monitor_ptr;
} coder_properties_struct;

typedef struct {
    struct timespec timeof_request;
    coder_properties_struct *coder;
} heap_request;

typedef struct {
    int size;
    int capacity;
    heap_request   *requests;
    int (*cmp_f) (heap_request, heap_request);
} heap;

typedef struct {
    int is_held;
    int is_wanted;
    struct timespec cooldown_end;
} dongle_struct;

typedef struct {
    config_struct   loaded_config;
    pthread_t *coder_threads_arr;
    coder_properties_struct *coder_properties_arr;
    dongle_struct   *dongles_arr;
    heap    *min_heap;
    int have_finished;
    struct timespec start_time;
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

// REQUESTS
void    add_request(coder_properties_struct *coder_p);
void    del_request(coder_properties_struct *coder_p);

// HEAP UTILS
heap    *init_heap(config_struct *loaded_config);

// HEAP MANAGEMENT
void    swap(heap_request *child_request, heap_request *parent_request);
void    sift_up(heap *p_queue, int index);
void    sift_down(heap *p_queue, int index);
void    push(heap *p_queue, heap_request new_request);
int    pop_at(heap *p_queue, int index);

// HEAP CMP FUNCTIONS
int cmp_timeof_request(heap_request first_req, heap_request second_req);
int cmp_burnout(heap_request first_req, heap_request second_req);

// TIME UTILS
struct timespec get_timestamp();
int timespec_cmp(struct timespec *first_stamp, struct timespec *second_stamp);

// SIMULATION
int start_simulation(monitor_struct *simulation_monitor);

// ROUTINES

// CODER ROUTINE UTILS
void update_time_to_burnout(long burnout_time, struct timespec *time_to_burnout);
void    update_both_dongles(coder_properties_struct *coder_p);

// MONITOR ROUTINE UTILS
int burnout_check(struct timespec burnout_time);
int cooldown_check(struct timespec cooldown_time);
int check_compilations_num(heap_request *request, config_struct *loaded_config);
void    stop_wake_all(coder_properties_struct *coders_arr, config_struct *loaded_config);
int  handle_request(dongle_struct *dongles_arr, heap_request *request, int request_index);

// ALL STRUCTS HANDLER
monitor_struct *init_all_structs(int argc, char **argv);

// GENERAL UTILS
void    log_and_sleep(coder_properties_struct *coder_p, Coder_actions action);

# endif
