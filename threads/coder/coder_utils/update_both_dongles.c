/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_both_dongles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsordo-o <tsordo-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 18:17:53 by tsordo-o          #+#    #+#             */
/*   Updated: 2026/11/06 18:42:09 by tsordo-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../codexion.h"

static void	update_dongle(t_dongle_struct *dongle_ptr, long dongle_cooldown);

void	update_both_dongles(t_cod_prts_struct *coder_p)
{
	long			dongle_cooldown;
	t_dongle_struct	*dongles_arr;
	t_dongle_struct	*dongle_one;
	t_dongle_struct	*dongle_two;

	dongle_cooldown = coder_p->monitor_ptr->loaded_config.dongle_cooldown;
	dongles_arr = coder_p->monitor_ptr->dongles_arr;
	dongle_one = &dongles_arr[coder_p->dongle_1_index];
	dongle_two = &dongles_arr[coder_p->dongle_2_index];
	update_dongle(dongle_one, dongle_cooldown);
	update_dongle(dongle_two, dongle_cooldown);
	pthread_cond_broadcast(&coder_p->monitor_ptr->wake_monitor);
}

static void	update_dongle(t_dongle_struct *dongle_ptr, long dongle_cooldown)
{
	struct timespec	now;

	now = get_timestamp();
	dongle_ptr->is_held = 0;
	dongle_ptr->in_cd = 1;
	timespec_add_time(&now, dongle_cooldown);
	dongle_ptr->cooldown_end = now;
}
