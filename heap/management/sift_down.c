/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sift_down.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsordo-o <tsordo-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 18:17:16 by tsordo-o          #+#    #+#             */
/*   Updated: 2026/11/06 18:41:46 by tsordo-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../codexion.h"

void	sift_down(t_queue_struct *p_queue, int index)
{
	int				child;
	t_queue_request	*req_ptr;

	req_ptr = p_queue->requests;
	if (req_ptr[1].coder == NULL)
		return ;
	while (2 * index <= p_queue->size)
	{
		child = 2 * index;
		if (child + 1 <= p_queue->size && p_queue->cmp_f(req_ptr[child + 1],
				req_ptr[child]))
			child++;
		if (p_queue->cmp_f(req_ptr[child], req_ptr[index]))
		{
			swap(&req_ptr[index], &req_ptr[child]);
			index = child;
		}
		else
			break ;
	}
}
