/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cod_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsordo-o <tsordo-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 18:17:37 by tsordo-o          #+#    #+#             */
/*   Updated: 2026/11/06 18:51:23 by tsordo-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../codexion.h"

void	add_request(t_cod_prts_struct *coder_p)
{
	t_queue_request	new_request;

	new_request.coder = coder_p;
	new_request.timeof_request = get_timestamp();
	push(coder_p->monitor_ptr->min_heap, new_request);
}

void	update_time_to_burnout(long burnout_time,
		struct timespec *time_to_burnout)
{
	struct timespec	current_time;

	current_time = get_timestamp();
	timespec_add_time(&current_time, burnout_time);
	time_to_burnout->tv_sec = current_time.tv_sec;
	time_to_burnout->tv_nsec = current_time.tv_nsec;
}
