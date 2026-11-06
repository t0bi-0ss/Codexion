/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsordo-o <tsordo-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 19:25:25 by tsordo-o          #+#    #+#             */
/*   Updated: 2026/11/06 18:48:54 by tsordo-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	init_structs(t_monitor *monitor_p);
static void	start_threads_n_join(t_monitor *monitor_p,
				pthread_t *monitor_thread);

int	main(int argc, char **argv)
{
	pthread_t		monitor_thread;
	t_monitor		monitor_p;

	if (get_and_validate_args(argc, argv, &monitor_p))
		return (1);
	if (init_structs(&monitor_p))
		return (2);
	start_threads_n_join(&monitor_p, &monitor_thread);
	finish_simulation(&monitor_p);
	return (0);
}

static int	init_structs(t_monitor *monitor_p)
{
	int	i;

	if (init_monitor(monitor_p))
		return (1);
	i = 0;
	while (i < monitor_p->loaded_config.number_of_coders)
	{
		init_coder_p(&monitor_p->coder_properties_arr[i], monitor_p, i);
		i++;
	}
	return (0);
}

static void	start_threads_n_join(t_monitor *monitor_p,
		pthread_t *monitor_thread)
{
	int	i;

	i = 0;
	if (pthread_create(monitor_thread, NULL, monitor_routine, monitor_p))
		return (fprintf(stderr, "Error creating monitor thread\n"),
			(void) NULL);
	i = 0;
	while (i < monitor_p->loaded_config.number_of_coders)
	{
		if (pthread_create(&monitor_p->coder_threads_arr[i], NULL,
				coder_routine, &monitor_p->coder_properties_arr[i]))
			return (fprintf(stderr, "Error creating n%i coder thread\n", i),
				(void) NULL);
		i++;
	}
	i = 0;
	while (i < monitor_p->loaded_config.number_of_coders)
	{
		if (pthread_join(monitor_p->coder_threads_arr[i], NULL))
			fprintf(stderr, "Error joining n%i coder thread\n", i);
		i++;
	}
	if (pthread_join(*monitor_thread, NULL))
		fprintf(stderr, "Error joining monitor thread\n");
}
