/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsordo-o <tsordo-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 17:47:23 by tsordo-o          #+#    #+#             */
/*   Updated: 2026/11/06 18:48:21 by tsordo-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# define _XOPEN_SOURCE 500

# include <pthread.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

/*CONSTANTS*/

# define MAX_INT 2147483647
# define MIN_INT -2147483648

/*ENUMS*/
typedef enum scheduler
{
	FIFO,
	EDF
}								t_Scheduler;

typedef enum coder_actions
{
	COMPILE,
	DEBUG,
	REFACTOR,
	GRAB
}								t_Coder_actions;

/*CUSTOM STRUCTS*/

typedef struct s_monitor_struct	t_monitor;

typedef struct s_config_struct
{
	int							number_of_coders;
	unsigned int				time_to_burnout;
	unsigned int				time_to_compile;
	unsigned int				time_to_debug;
	unsigned int				time_to_refactor;
	unsigned int				compiles_required;
	unsigned int				dongle_cooldown;
	t_Scheduler					scheduler_config;
}								t_config_struct;

typedef struct s_cod_prts_struct
{
	int							id;
	unsigned int				times_compiled;
	int							stop;
	int							has_permission;
	struct timespec				to_burnout;
	pthread_cond_t				wake_coder;
	int							dongle_1_index;
	int							dongle_2_index;
	t_monitor					*monitor_ptr;
}								t_cod_prts_struct;

typedef struct s_queue_request
{
	struct timespec				timeof_request;
	t_cod_prts_struct			*coder;
}								t_queue_request;

typedef struct s_queue_struct
{
	int							size;
	int							capacity;
	t_queue_request				*requests;
	int							(*cmp_f)(t_queue_request, t_queue_request);
}								t_queue_struct;

typedef struct s_dongle_struct
{
	int							is_held;
	int							is_wanted;
	int							in_cd;
	struct timespec				cooldown_end;
	struct timespec				last_time_used;
	struct timespec				requesters_burnout;
}								t_dongle_struct;

struct							s_monitor_struct
{
	t_config_struct				loaded_config;
	pthread_t					*coder_threads_arr;
	t_cod_prts_struct			*coder_properties_arr;
	t_dongle_struct				*dongles_arr;
	t_queue_struct				*min_heap;
	int							have_finished;
	struct timespec				earliest_deadline;
	struct timespec				start_time;
	pthread_mutex_t				shared_mutex;
	pthread_mutex_t				mutex_stdout;
	pthread_cond_t				wake_monitor;
};

/*ARGS HANDLING*/

int								get_and_validate_args(int argc, char **argv,
									t_monitor *monitor_p);
int								overflow_check(const char *nptr);

/*HEAP UTILS*/

t_queue_struct					*init_heap(t_config_struct *loaded_config);

/*HEAP MANAGEMENT*/

void							swap(t_queue_request *child_request,
									t_queue_request *parent_request);
void							sift_up(t_queue_struct *p_queue, int index);
void							sift_down(t_queue_struct *p_queue, int index);
void							push(t_queue_struct *p_queue,
									t_queue_request new_request);
int								pop_at(t_queue_struct *p_queue, int index);

/*HEAP CMP FUNCTIONS*/

int								cmp_timeof_request(t_queue_request first_req,
									t_queue_request second_req);
int								cmp_burnout(t_queue_request first_req,
									t_queue_request second_req);

/*TIME UTILS*/

struct timespec					get_timestamp(void);
int								timespec_cmp(struct timespec *first_stamp,
									struct timespec *second_stamp);
void							timespec_add_time(struct timespec *time_stamp,
									long time_ms);
long							time_until_now(struct timespec *time_stamp);
long							time_from_now(struct timespec *dead_line);

/*ROUTINES*/

void							*coder_routine(void *properties);
void							*monitor_routine(void *properties);

/*CODER UTILS*/

void							add_request(t_cod_prts_struct *coder_p);
void							init_coder_p(t_cod_prts_struct *coder_p,
									t_monitor *monitor_p, int i);
void							update_time_to_burnout(long burnout_time,
									struct timespec *time_to_burnout);
void							update_both_dongles(t_cod_prts_struct *coder_p);
void							log_and_sleep(t_cod_prts_struct *coder_p,
									t_Coder_actions action);

/*MONITOR UTILS*/

int								init_monitor(t_monitor *monitor_ptr);
int								burnout_check(t_monitor *monitor_p);
int								cooldown_check(struct timespec cooldown_time);
int								check_compilations_num(t_monitor *monitor_ptr,
									int *curr_index);
void							stop_wake_all(t_cod_prts_struct *coders_arr,
									t_config_struct *loaded_config,
									pthread_mutex_t *shared_mutex);
int								handle_request(t_monitor *monitor_p,
									t_queue_request *request,
									int *request_index);
void							earliest_dead_line(t_monitor *monitor_ptr);

/*GENERAL UTILS*/
void							free_all(t_monitor *monitor_p);
void							log_event(t_monitor *monitor_ptr,
									char *event, int id);
void							finish_simulation(t_monitor *monitor_p);

#endif
