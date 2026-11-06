/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_timeof_req.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsordo-o <tsordo-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 18:16:59 by tsordo-o          #+#    #+#             */
/*   Updated: 2026/11/06 18:41:21 by tsordo-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../codexion.h"

/* Returns 1 if first_req 'timeof' occurs sooner than second_req 'timeof'*/
int	cmp_timeof_request(t_queue_request first_req, t_queue_request second_req)
{
	struct timespec	*first_timeof;
	struct timespec	*second_timeof;

	first_timeof = NULL;
	second_timeof = NULL;
	first_timeof = &first_req.timeof_request;
	second_timeof = &second_req.timeof_request;
	return (timespec_cmp(first_timeof, second_timeof));
}
