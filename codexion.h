/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsordo-o <tsordo-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 17:47:23 by tsordo-o          #+#    #+#             */
/*   Updated: 2026/10/12 18:06:59 by tsordo-o         ###   ########.fr       */
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
    args_struct *all_args;
} thrds_properties_struct;

typedef struct {
    pthread_mutex_t quantum_mutex;
    pthread_mutex_t *dongles_mutex_arr;
    int quantum_available;
    int all_finished;
    int terminate_all;
    pthread_cond_t watchdog_cond;
    pthread_cond_t coders_general_cond;
    pthread_cond_t *dongles_cond_arr;
} signals_struct;

typedef struct {
    long number_of_coders;
    long time_to_burnout;
    long time_to_compile;
    long time_to_debug;
    long time_to_refactor;
    long number_of_compiles_required;
    long dongle_cooldown;
    char *scheduler;
} args_struct;

typedef struct {
    args_struct *all_args;
    signals_struct *signals;
    thrds_properties_struct *threads_properties_arr;
} all_structs_handler;

// ARGS HANDLING
int get_and_validate_args(int argc, char **argv);

// SIGNALS
signals_struct *init_signals(long coders_num);

// ROUTINES
void compile(long id, int compilations);
void debug(long id);
void refactor(long id);

// THREADS
void *thread_coder(void *coder_id);
void *thread_watchdog(void *id);

// ALL STRUCTS HANDLER
all_structs_handler *init_all_structs(int argc, char **argv);

# endif
