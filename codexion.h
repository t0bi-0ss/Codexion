/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsordo-o <tsordo-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 17:47:23 by tsordo-o          #+#    #+#             */
/*   Updated: 2026/10/22 17:05:39 by tsordo-o         ###   ########.fr       */
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
    long id;
    long times_compiled;
    struct timespec time_to_burnout;
    pthread_cond_t  wake_coder;
    config_struct *config;
    dongle_struct *first_dongle;
    dongle_struct *second_dongle;
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
    struct timespec available_time;
    long dongle_cooldown;
    heap    queue;
    pthread_mutex_t dongle_mutex;
} dongle_struct;

typedef struct {
    int priority;
    struct timespec *burnout_time;
    pthread_cond_t  *wake_coder;
    heap_node   *previous;
    heap_node   *next;
} heap_node;

typedef struct {
    int size;
    heap_node   *head;
    pthread_mutex_t mutex_queue;
} heap;

typedef struct {
    config_struct   loaded_config;
    pthread_t *coder_threads_arr;
    coder_properties_struct *coder_properties_arr;
    dongle_struct   *dongles_arr;
    int terminate_all;
    int all_finished;
    long start_time;
    pthread_mutex_t mutex_stdout;
} monitor_struct;

// ARGS HANDLING
int get_and_validate_args(int argc, char **argv, monitor_struct *structs_handler);

// MEMORY MANAGEMENT
void    free_memory(monitor_struct *simulation_monitor);
int allocate_memory(monitor_struct *simulation_monitor_ptr, long number_of_coders);

// HEAP

// MAIN UTILS
heap_node *new_request(struct timespec *burnout_time, pthread_cond_t *wake_coder);
void    add_request(heap *queue, heap_node *new_request, char *scheduler);
int    make_requests(coder_properties_struct *self_properties);

// MANAGEMENT
void    reset_priority(heap *queue);
int timespec_min(struct timespec *curr_min, struct timespec *candidate);
int is_disordered(heap *queue);
void    assign_priority(heap *queue);
void    insert_last(heap *queue, heap_node *new_node);
heap_node *new_node();
void    swap_nodes(heap_node *first_node, heap_node *second_node);
void    bubble_sort(heap *queue);

// INSERT METHODS
void    insert_edf(heap *queue, heap_node *new_request);
void    insert_fifo(heap *queue, heap_node *new_request);

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
