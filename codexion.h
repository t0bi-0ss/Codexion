/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsordo-o <tsordo-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 17:47:23 by tsordo-o          #+#    #+#             */
/*   Updated: 2026/10/29 21:39:34 by tsordo-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

#include <unistd.h>
#include <pthread.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
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

typedef struct monitor_struct monitor_struct;

typedef struct {
    int number_of_coders;
    unsigned int time_to_burnout;
    unsigned int time_to_compile;
    unsigned int time_to_debug;
    unsigned int time_to_refactor;
    unsigned int compiles_required;
    unsigned int dongle_cooldown;
    Scheduler   scheduler_config;
} config_struct;

typedef struct {
    int    id;
    unsigned int    times_compiled;
    int stop;
    int has_permission;
    struct  timespec last_compile;
    struct timespec to_burnout;
    pthread_cond_t  wake_coder;
    int dongle_1_index;
    int dongle_2_index;
    monitor_struct  *monitor_ptr;
} coder_properties_struct;

typedef struct {
    struct timespec timeof_request;
    coder_properties_struct *coder;
} queue_request;

typedef struct {
    int size;
    int capacity;
    queue_request   *requests;
    int (*cmp_f) (queue_request, queue_request);
} queue_struct;

typedef struct {
    int is_held;
    int is_wanted;
    int in_cd;
    struct timespec cooldown_end;
} dongle_struct;

struct monitor_struct{
    config_struct   loaded_config;
    pthread_t *coder_threads_arr;
    coder_properties_struct *coder_properties_arr;
    dongle_struct   *dongles_arr;
    queue_struct    *min_heap;
    int have_finished;
    struct timespec *earliest_deadline;
    struct timespec start_time;
    pthread_mutex_t   shared_mutex;
    pthread_mutex_t mutex_stdout;
    pthread_cond_t  wake_monitor;
};

// ARGS HANDLING

int get_and_validate_args(int argc, char **argv, monitor_struct *monitor_p);

// HEAP UTILS

queue_struct    *init_heap(config_struct *loaded_config);

// HEAP MANAGEMENT

void    swap(queue_request *child_request, queue_request *parent_request);
void    sift_up(queue_struct *p_queue, int index);
void    sift_down(queue_struct *p_queue, int index);
void    push(queue_struct *p_queue, queue_request new_request);
int    pop_at(queue_struct *p_queue, int index);

// HEAP CMP FUNCTIONS

int cmp_timeof_request(queue_request first_req, queue_request second_req);
int cmp_burnout(queue_request first_req, queue_request second_req);

// TIME UTILS

struct timespec get_timestamp();
int timespec_cmp(struct timespec *first_stamp, struct timespec *second_stamp);

// ROUTINES

void *coder_routine(void *properties);
void    *monitor_routine(void *properties);


// CODER UTILS

void    add_request(coder_properties_struct *coder_p);
void    init_coder_p(coder_properties_struct *coder_p, monitor_struct *monitor_p, int i);
void update_time_to_burnout(long burnout_time, struct timespec *time_to_burnout);
void    update_both_dongles(coder_properties_struct *coder_p);
void    log_and_sleep(coder_properties_struct *coder_p, Coder_actions action);

// MONITOR UTILS

int init_monitor(monitor_struct *monitor_ptr);
int burnout_check(monitor_struct *monitor_p, int index);
int cooldown_check(struct timespec cooldown_time);
int check_compilations_num(monitor_struct *monitor_ptr, int *curr_index);
void    stop_wake_all(coder_properties_struct *coders_arr,
    config_struct *loaded_config,
    pthread_mutex_t *shared_mutex);
int  handle_request(monitor_struct *monitor_p, queue_request *request, int *request_index);
void  earliest_dead_line(monitor_struct *monitor_ptr);

// GENERAL UTILS
void    free_all(monitor_struct *monitor_p);
void    log_event(monitor_struct *monitor_ptr, char *event, int id);
void    finish_simulation(monitor_struct *monitor_p);

# endif
