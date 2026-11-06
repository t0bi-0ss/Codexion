/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_burnout.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsordo-o <tsordo-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 18:16:48 by tsordo-o          #+#    #+#             */
/*   Updated: 2026/11/06 18:50:24 by tsordo-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../codexion.h"

/*Returns 1 if first_req coder's burnout is sooner
than second_req coder's burnout*/
int	cmp_burnout(t_queue_request first_req, t_queue_request second_req)
{
	struct timespec	*first_brnout;
	struct timespec	*second_brnout;

	first_brnout = &first_req.coder->to_burnout;
	second_brnout = &second_req.coder->to_burnout;
	return (timespec_cmp(first_brnout, second_brnout));
}
