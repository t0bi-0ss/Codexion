/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsordo-o <tsordo-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 17:47:23 by tsordo-o          #+#    #+#             */
/*   Updated: 2026/10/19 17:21:59 by tsordo-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>

// CUSTOM STRUCTS
typedef struct {
    long id;
    long times_compiled;
    int burned_out;
    int terminate;
    int finished_compiling;
    config_struct *config;
    dongle_struct *first_dongle;
    dongle_struct *second_dongle;
} coder_properties_struct;

typedef struct {
    long number_of_coders;
    long time_to_burnout;
    long time_to_compile;
    long time_to_debug;
    long time_to_refactor;
    long number_of_compiles_required;
    long dongle_cooldown;
    char *scheduler;
} config_struct;

typedef struct {
    int id;
    int is_available;
    long last_time_used;
    long dongle_cooldown;
    pthread_mutex_t dongle_mutex;
    pthread_cond_t dongle_cond;
} dongle_struct;

typedef struct {
    config_struct   *loaded_config;
    pthread_t *coder_threads_arr;
    coder_properties_struct *coder_properties_arr;
    dongle_struct   *dongles_arr;
    coder_properties_struct *threads_properties_arr;
    int terminate_all;
    int all_finished;
    long start_time;
} monitor_struct;

// ARGS HANDLING
int get_and_validate_args(int argc, char **argv);

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
