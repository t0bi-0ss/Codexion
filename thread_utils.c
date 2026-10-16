/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsordo-o <tsordo-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 18:21:29 by tsordo-o          #+#    #+#             */
/*   Updated: 2026/10/16 15:34:41 by tsordo-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int create_coder_threads(pthread_t **coders_arr)
{
    while (*coders_arr)
    {
        if (pthread_create(*coders_arr, NULL, thread_coder, NULL))
        {
            fprintf(2, "Threads error: an error occured while creating coder threads");
            return (1);
        }
        coders_arr++;
    }

    return (0);
}

static int create_watchdog_thread(pthread_t *watchdog_ptr)
{
    if (pthread_create(watchdog_ptr, NULL, thread_watchdog, NULL))
    {
        fprintf(2, "Threads error: an error occured while creating watchdog thread");
        return (1);
    }

    return (0);
}

static int allocate_for_coders_arr(pthread_t ***coders_arr, long coders_num)
{
    *coders_arr = (pthread_t **) malloc(sizeof(pthread_t *) * (coders_num + 1));
    if (!(*coders_arr))
    {
        fprint(2, "Memory error: an error occcured while allocating memory for coder threads array");
        return (1);
    }
    *coders_arr[coders_num] = NULL;

    return (0);
}

static int allocate_for_properties_arr(coder_properties_struct ***properties_arr, long coders_num)
{
    *properties_arr = (coder_properties_struct **) malloc(sizeof(coder_properties_struct) * (coders_num + 1));
    if (!(*properties_arr))
    {
        fprintf(2, "Memory error: an error occured while allocating memory for properties array");
        return (1);
    }
    *properties_arr[coders_num] = NULL;
    
    return (0);
}

static int start_all_threads(pthread_t **coders_arr, pthread_t *watchdog_ptr, coder_properties_struct **properties_arr, long coders_num)
{
    if (allocate_for_coders_arr(&coders_arr, coders_num))
        return (1);
    if (allocate_for_properties_arr(&properties_arr, coders_num))
        return (2);
    if (create_coder_threads(coders_arr))
        return (3);
    if (create_watchdog_thread(watchdog_ptr))
        return (4);
}
