/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:24:34 by nheo              #+#    #+#             */
/*   Updated: 2022/08/23 18:32:03 by heonamjun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) < 0)
		return (-1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_sleep(long wait_time)
{
	long	start;
	long	end;

	start = get_time();
	end = start + wait_time;
	while (start < end)
	{
		start = get_time();
		if (start < 0)
			return ;
		// usleep(100);
	}
}

int	check_data(t_data *data)
{
	if (data->must_eat_count < 0 || data->ttd < 0 || data->tte < 0
		|| data->tts < 0 || data->philo_num < 0)
		return (1);
	return (0);
}
