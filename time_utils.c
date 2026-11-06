/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsordo-o <tsordo-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 18:18:50 by tsordo-o          #+#    #+#             */
/*   Updated: 2026/11/06 18:21:11 by tsordo-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

struct timespec	get_timestamp(void)
{
	struct timeval	now;
	struct timespec	updated;

	gettimeofday(&now, NULL);
	updated.tv_sec = now.tv_sec;
	updated.tv_nsec = now.tv_usec * 1000;
	return (updated);
}

/*Returns 1 if first_stamp occurs sooner than second_stamp*/
int	timespec_cmp(struct timespec *first_stamp, struct timespec *second_stamp)
{
	if (!second_stamp || second_stamp->tv_sec == 0)
		return (1);
	if (!first_stamp)
		return (0);
	if (first_stamp->tv_sec != second_stamp->tv_sec)
		return (first_stamp->tv_sec < second_stamp->tv_sec);
	return (first_stamp->tv_nsec < second_stamp->tv_nsec);
}

void	timespec_add_time(struct timespec *time_stamp, long time_ms)
{
	time_stamp->tv_sec += time_ms / 1000;
	time_stamp->tv_nsec += (time_ms % 1000) * 1000000;
	if (time_stamp->tv_nsec >= 1000000000)
	{
		time_stamp->tv_sec += time_stamp->tv_nsec / 1000000000;
		time_stamp->tv_nsec %= 1000000000;
	}
}

long	time_until_now(struct timespec *time_stamp)
{
	long			nsecs;
	long			secs;
	struct timespec	now;

	now = get_timestamp();
	nsecs = (now.tv_nsec - time_stamp->tv_nsec) / 1000000;
	secs = (now.tv_sec - time_stamp->tv_sec) * 1000;
	return (nsecs + secs);
}

long	time_from_now(struct timespec *dead_line)
{
	long			nsecs;
	long			secs;
	struct timespec	now;

	now = get_timestamp();
	nsecs = (dead_line->tv_nsec - now.tv_nsec) / 1000000;
	secs = (dead_line->tv_sec - now.tv_sec) * 1000;
	return (nsecs + secs);
}
