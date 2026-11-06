/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sift_up.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsordo-o <tsordo-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 18:17:20 by tsordo-o          #+#    #+#             */
/*   Updated: 2026/11/06 18:41:46 by tsordo-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../codexion.h"

void	sift_up(t_queue_struct *p_queue, int index)
{
	int				parent;
	t_queue_request	*req_ptr;

	req_ptr = p_queue->requests;
	if (req_ptr[1].coder == NULL)
		return ;
	while (index > 1)
	{
		parent = index / 2;
		if (p_queue->cmp_f(req_ptr[index], req_ptr[parent]))
		{
			swap(&p_queue->requests[index], &p_queue->requests[parent]);
			index = parent;
		}
		else
			break ;
	}
}
