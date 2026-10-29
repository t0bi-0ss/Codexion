/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_simulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsordo-o <tsordo-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 20:57:33 by tsordo-o          #+#    #+#             */
/*   Updated: 2026/10/29 21:01:14 by tsordo-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void    finish_simulation(monitor_struct *monitor_p)
{
    int i;

    i = 0;
    while (i < monitor_p->loaded_config.number_of_coders)
    {
        pthread_cond_destroy(&monitor_p->coder_properties_arr[i].wake_coder);
        i++;
    }
    pthread_cond_destroy(&monitor_p->wake_monitor);
    pthread_mutex_destroy(&monitor_p->shared_mutex);
    pthread_mutex_destroy(&monitor_p->mutex_stdout);
    free_all(monitor_p);   
}
