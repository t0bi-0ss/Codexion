/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsordo-o <tsordo-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 18:17:12 by tsordo-o          #+#    #+#             */
/*   Updated: 2026/11/06 18:41:46 by tsordo-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../codexion.h"

void	push(t_queue_struct *p_queue, t_queue_request new_request)
{
	if (p_queue->size >= p_queue->capacity)
	{
		fprintf(stderr, "Heap overflow!\n");
		return ;
	}
	p_queue->requests[++p_queue->size] = new_request;
	sift_up(p_queue, p_queue->size);
}
