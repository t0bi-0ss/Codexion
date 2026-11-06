/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_heap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsordo-o <tsordo-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 18:17:30 by tsordo-o          #+#    #+#             */
/*   Updated: 2026/11/06 18:41:46 by tsordo-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../codexion.h"

static int		select_func(t_queue_struct *initiated_heap,
					t_Scheduler scheduler_config);

t_queue_struct	*init_heap(t_config_struct *loaded_config)
{
	int				coders_num;
	t_queue_struct	*initiated_heap;

	initiated_heap = (t_queue_struct *)malloc(sizeof(t_queue_struct));
	if (!initiated_heap)
		return (NULL);
	coders_num = loaded_config->number_of_coders;
	initiated_heap->capacity = coders_num;
	initiated_heap->size = 0;
	initiated_heap->requests = (t_queue_request *)malloc(sizeof(t_queue_request)
			* (coders_num + 1));
	if (!initiated_heap->requests)
		return (free(initiated_heap), NULL);
	if (select_func(initiated_heap, loaded_config->scheduler_config))
	{
		free(initiated_heap->requests);
		free(initiated_heap);
		return (NULL);
	}
	return (initiated_heap);
}

static int	select_func(t_queue_struct *initiated_heap,
		t_Scheduler scheduler_config)
{
	if (scheduler_config == FIFO)
		initiated_heap->cmp_f = &cmp_timeof_request;
	else if (scheduler_config == EDF)
		initiated_heap->cmp_f = &cmp_burnout;
	else
		return (1);
	return (0);
}
