/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop_at.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsordo-o <tsordo-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 18:17:07 by tsordo-o          #+#    #+#             */
/*   Updated: 2026/11/06 18:41:46 by tsordo-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../codexion.h"

int	pop_at(t_queue_struct *p_queue, int index)
{
	if (p_queue->size == 0)
	{
		fprintf(stderr, "Heap underflow!\n");
		return (1);
	}
	if (index <= 0 || index > p_queue->size)
	{
		fprintf(stderr, "Invalid index!\n");
		return (2);
	}
	if (index == p_queue->size)
	{
		p_queue->size--;
		return (0);
	}
	p_queue->requests[index] = p_queue->requests[p_queue->size];
	p_queue->size--;
	sift_down(p_queue, index);
	sift_up(p_queue, index);
	return (0);
}
