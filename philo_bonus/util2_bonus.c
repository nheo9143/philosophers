/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:24:36 by nheo              #+#    #+#             */
/*   Updated: 2022/08/30 12:47:45 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <signal.h>

void	print_result(t_philo *philo, t_data *data, char *str1, char *str2)
{
	printf("%ld %d %s %s\n", get_time() - data->time, philo->num, str1, str2);
}

void	print_status(t_philo *philo, t_data *data, char *str1, char *str2)
{
	sem_wait(data->print_sem);
	sem_wait(data->check_sem);
	if (data->is_dead)
	{
		sem_post(data->check_sem);
		sem_post(data->print_sem);
		exit(1);
	}
	sem_post(data->check_sem);
	printf("%ld %d %s %s\n", get_time() - data->time, philo->num, str1, str2);
	sem_post(data->print_sem);
}

int	ft_error(void)
{
	write(2, "error\n", 6);
	return (1);
}

void	kill_pids(t_data *data, int pid_num)
{
	int	i;

	i = -1;
	while (++i < pid_num)
		kill(data->pid[i], SIGINT);
	sem_post(data->check_sem);
}
