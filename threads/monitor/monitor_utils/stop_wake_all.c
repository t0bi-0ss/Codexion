/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_wake_all.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsordo-o <tsordo-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 18:18:17 by tsordo-o          #+#    #+#             */
/*   Updated: 2026/11/06 18:40:51 by tsordo-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../codexion.h"

void	stop_wake_all(t_cod_prts_struct *coders_arr,
		t_config_struct *loaded_config, pthread_mutex_t *shared_mutex)
{
	int	i;

	i = 0;
	while (i < loaded_config->number_of_coders)
	{
		if (!coders_arr[i].stop)
		{
			coders_arr[i].stop = 1;
			pthread_cond_broadcast(&coders_arr[i].wake_coder);
		}
		i++;
	}
	pthread_mutex_unlock(shared_mutex);
}
