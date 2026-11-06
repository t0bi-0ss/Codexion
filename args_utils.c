/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsordo-o <tsordo-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 18:18:24 by tsordo-o          #+#    #+#             */
/*   Updated: 2026/11/06 19:09:34 by tsordo-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	get_args(t_config_struct *config_p, char **argv);
static int	validate_args(int argc, char **argv);
static int	ft_is_numeric(char *str);
static int	impossible_parameters(t_config_struct *loaded_config);

int	get_and_validate_args(int argc, char **argv, t_monitor *monitor_p)
{
	if (validate_args(argc, argv))
		return (1);
	else if (get_args(&monitor_p->loaded_config, argv))
		return (2);
	else if (impossible_parameters(&monitor_p->loaded_config))
		return (3);
	return (0);
}

static int	impossible_parameters(t_config_struct *loaded_config)
{
	if (loaded_config->number_of_coders > 5000)
	{
		fprintf(stderr, "Args error:"
			"number of coders can't be greater than 5000\n");
		return (1);
	}
	if (loaded_config->time_to_compile
		+ loaded_config->time_to_debug
		+ loaded_config->time_to_refactor
		+ loaded_config->dongle_cooldown
		> loaded_config->time_to_burnout)
	{
		fprintf(stderr, "Args error: the sum of <time_to_compile>"
			"<time_to_debug>"
			"<time_to_refactor> and <dongle_cooldown> can't be greater than"
			"<time_to_burnout>");
		return (2);
	}
	return (0);
}

static int	ft_is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			if (str[i] != '-' && str[i] != '+')
				return (1);
			else if ((--i) >= 0 && !((str[i] >= 9 && str[i] <= 13)
					|| str[i] == 32))
				return (1);
			else
				i++;
		}
		i++;
	}
	return (0);
}

static int	get_args(t_config_struct *config_p, char **argv)
{
	if (strncmp("fifo", argv[8], 5) == 0)
		config_p->scheduler_config = FIFO;
	else if (strncmp("edf", argv[8], 4) == 0)
		config_p->scheduler_config = EDF;
	else
	{
		fprintf(stderr, "Args error: 'scheduler' wrong input\n");
		return (1);
	}
	config_p->number_of_coders = atoi(argv[1]);
	config_p->time_to_burnout = atoi(argv[2]);
	config_p->time_to_compile = atoi(argv[3]);
	config_p->time_to_debug = atoi(argv[4]);
	config_p->time_to_refactor = atoi(argv[5]);
	config_p->compiles_required = atoi(argv[6]);
	config_p->dongle_cooldown = atoi(argv[7]);
	return (0);
}

static int	validate_args(int argc, char **argv)
{
	int	i;

	if (argc < 9)
		return (fprintf(stderr, "Args error: insufficient arguments\n"), 1);
	i = 1;
	while (i <= 7)
	{
		if (ft_is_numeric(argv[i]))
			return (fprintf(stderr,
					"Args error: arg [%i] is not a valid number\n", i), 2);
		if (overflow_check(argv[i]))
			return (fprintf(stderr, "Args error: arg [%i] overflowed\n", i), 3);
		if (i == 7)
		{
			if (atoi(argv[i++]) < 0)
				return (fprintf(stderr,
						"Args error: cooldown must not be negative\n"), 4);
			else
				continue ;
		}
		if (atoi(argv[i]) <= 0)
			return (fprintf(stderr, "Args error: arg [%i] is <= 0\n", i), 4);
		i++;
	}
	return (0);
}
