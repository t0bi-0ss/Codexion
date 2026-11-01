/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsordo-o <tsordo-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 18:03:15 by tsordo-o          #+#    #+#             */
/*   Updated: 2026/10/29 18:53:53 by tsordo-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void    free_all(monitor_struct *monitor_p)
{
    if (monitor_p->coder_threads_arr)
    {
        free(monitor_p->coder_threads_arr);
        monitor_p->coder_threads_arr = NULL;
    }
    if (monitor_p->coder_properties_arr)
    {
        free(monitor_p->coder_properties_arr);
        monitor_p->coder_properties_arr = NULL;
    }
    if (monitor_p->dongles_arr)
    {
        free(monitor_p->dongles_arr);
        monitor_p->dongles_arr = NULL;
    }
    if (monitor_p->min_heap)
    {
        if (monitor_p->min_heap->requests)
        {
            free(monitor_p->min_heap->requests);
            monitor_p->min_heap->requests = NULL;
        }
        free(monitor_p->min_heap);
        monitor_p->min_heap = NULL;
    }
}
