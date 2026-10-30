/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsordo-o <tsordo-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 19:25:25 by tsordo-o          #+#    #+#             */
/*   Updated: 2026/10/29 21:27:42 by tsordo-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int main(int argc, char **argv)
{
    int i;
    pthread_t   monitor_thread;
    monitor_struct  monitor_p;

    if (get_and_validate_args(argc, argv, &monitor_p))
        return (1);
    if (init_monitor(&monitor_p))
        return (2);
    i = 0;
    pthread_create(&monitor_thread, NULL, monitor_routine, &monitor_p);
    while (i < monitor_p.loaded_config.number_of_coders)
    {
        init_coder_p(&monitor_p.coder_properties_arr[i], &monitor_p, i);
        pthread_create(&monitor_p.coder_threads_arr[i], NULL, coder_routine, &monitor_p.coder_properties_arr[i]);
        i++;
    }
    i = 0;
    while (i < monitor_p.loaded_config.number_of_coders)
    {
        pthread_join(monitor_p.coder_threads_arr[i], NULL);
        i++;
    }
    pthread_join(monitor_thread, NULL);
    finish_simulation(&monitor_p);
    return (0);
}
