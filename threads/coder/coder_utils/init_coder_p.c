/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_coder_p.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsordo-o <tsordo-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 18:17:42 by tsordo-o          #+#    #+#             */
/*   Updated: 2026/11/06 18:45:57 by tsordo-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../codexion.h"

static void	set_dongles_index(t_cod_prts_struct *coder_p,
				t_config_struct *loaded_config);

void	init_coder_p(t_cod_prts_struct *coder_p,
		t_monitor *monitor_p, int i)
{
	coder_p->id = i;
	coder_p->times_compiled = 0;
	coder_p->stop = 0;
	coder_p->has_permission = 0;
	pthread_cond_init(&coder_p->wake_coder, NULL);
	set_dongles_index(coder_p, &monitor_p->loaded_config);
	update_time_to_burnout(monitor_p->loaded_config.time_to_burnout,
		&coder_p->to_burnout);
	coder_p->monitor_ptr = monitor_p;
}

static void	set_dongles_index(t_cod_prts_struct *coder_p,
		t_config_struct *loaded_config)
{
	coder_p->dongle_1_index = coder_p->id;
	if (coder_p->id == 0)
		coder_p->dongle_2_index = loaded_config->number_of_coders - 1;
	else
		coder_p->dongle_2_index = coder_p->id - 1;
}
