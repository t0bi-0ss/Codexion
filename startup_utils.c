/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startup_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsordo-o <tsordo-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 17:55:05 by tsordo-o          #+#    #+#             */
/*   Updated: 2026/10/29 21:50:21 by tsordo-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int  allocate_all(monitor_struct *monitor_ptr);
static void    all_to_null(monitor_struct *monitor_ptr);
static void init_dongles(monitor_struct *monitor_p);

int init_monitor(monitor_struct *monitor_ptr)
{
    all_to_null(monitor_ptr);
    monitor_ptr->min_heap = init_heap(&monitor_ptr->loaded_config);
    if (!monitor_ptr->min_heap)
        return (1);
    if (allocate_all(monitor_ptr))
        return (2);
    monitor_ptr->have_finished = 0;
    monitor_ptr->start_time = get_timestamp();
    pthread_mutex_init(&monitor_ptr->shared_mutex, NULL);
    pthread_mutex_init(&monitor_ptr->mutex_stdout, NULL);
    pthread_cond_init(&monitor_ptr->wake_monitor, NULL);
    init_dongles(monitor_ptr);
    return (0);    
}
static int  allocate_all(monitor_struct *monitor_ptr)
{
    unsigned int    coders_num;

    coders_num = monitor_ptr->loaded_config.number_of_coders;
    monitor_ptr->coder_threads_arr = malloc(sizeof(pthread_t) * coders_num);
    if (!monitor_ptr->coder_threads_arr)
        return (free_all(monitor_ptr), 1);
    monitor_ptr->coder_properties_arr = malloc(sizeof(coder_properties_struct) * coders_num);
    if (!monitor_ptr->coder_properties_arr)
        return (free_all(monitor_ptr), 1);
    monitor_ptr->dongles_arr = malloc(sizeof(dongle_struct) * coders_num);
    if (!monitor_ptr->dongles_arr)
        return (free_all(monitor_ptr), 1);
    return (0);
}

static void    all_to_null(monitor_struct *monitor_ptr)
{
    monitor_ptr->coder_threads_arr = NULL;
    monitor_ptr->coder_properties_arr = NULL;
    monitor_ptr->dongles_arr = NULL;
    monitor_ptr->earliest_deadline = NULL;
    monitor_ptr->min_heap = NULL;
}

static void init_dongles(monitor_struct *monitor_p)
{
    int i;
    dongle_struct   *dongle_ptr;

    i = 0;
    dongle_ptr = NULL;
    while (i < monitor_p->loaded_config.number_of_coders)
    {
        dongle_ptr = &monitor_p->dongles_arr[i];
        dongle_ptr->cooldown_end = get_timestamp();
        dongle_ptr->in_cd = 0;
        dongle_ptr->is_held = 0;
        dongle_ptr->is_wanted = 0;
        i++;
    }
}
