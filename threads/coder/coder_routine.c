/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsordo-o <tsordo-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 18:17:58 by tsordo-o          #+#    #+#             */
/*   Updated: 2026/11/06 18:40:51 by tsordo-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../codexion.h"

static int	coder_compilation(t_cod_prts_struct *coder_p);
static int	coder_action(t_cod_prts_struct *coder_p,
				t_Coder_actions action);

void	*coder_routine(void *properties)
{
	t_cod_prts_struct	*coder_p;

	coder_p = (t_cod_prts_struct *)properties;
	while (1)
	{
		pthread_mutex_lock(&coder_p->monitor_ptr->shared_mutex);
		add_request(coder_p);
		coder_p->has_permission = 0;
		pthread_cond_broadcast(&coder_p->monitor_ptr->wake_monitor);
		while (!coder_p->has_permission && !coder_p->stop)
			pthread_cond_wait(&coder_p->wake_coder,
				&coder_p->monitor_ptr->shared_mutex);
		pthread_mutex_unlock(&coder_p->monitor_ptr->shared_mutex);
		if (coder_action(coder_p, GRAB))
			break ;
		if (coder_compilation(coder_p))
			break ;
		if (coder_action(coder_p, DEBUG))
			break ;
		if (coder_action(coder_p, REFACTOR))
			break ;
	}
	return (NULL);
}

static int	coder_compilation(t_cod_prts_struct *coder_p)
{
	pthread_mutex_lock(&coder_p->monitor_ptr->shared_mutex);
	if (coder_p->stop)
	{
		pthread_mutex_unlock(&coder_p->monitor_ptr->shared_mutex);
		return (1);
	}
	pthread_mutex_unlock(&coder_p->monitor_ptr->shared_mutex);
	log_and_sleep(coder_p, COMPILE);
	pthread_mutex_lock(&coder_p->monitor_ptr->shared_mutex);
	update_both_dongles(coder_p);
	pthread_mutex_unlock(&coder_p->monitor_ptr->shared_mutex);
	return (0);
}

static int	coder_action(t_cod_prts_struct *coder_p, t_Coder_actions action)
{
	pthread_mutex_lock(&coder_p->monitor_ptr->shared_mutex);
	if (coder_p->stop)
	{
		pthread_mutex_unlock(&coder_p->monitor_ptr->shared_mutex);
		return (1);
	}
	pthread_mutex_unlock(&coder_p->monitor_ptr->shared_mutex);
	log_and_sleep(coder_p, action);
	return (0);
}
