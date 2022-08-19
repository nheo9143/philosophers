/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:24:28 by nheo              #+#    #+#             */
/*   Updated: 2022/08/19 18:00:22 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdlib.h>
#include <sys/semaphore.h>
#include <sys/wait.h>

void	free_data(t_data *data)
{
	int	i;
	int	status;

	i = -1;
	while (++i < data->philo_num)
	{
		wait(&status);
		if (status == 0)
			sem_post(data->check_sem);
		else
		{
			sem_post(data->check_sem);
			if (data->is_dead == 0)
				print_result(&data->philo[i], data, "is", "dead");
			data->is_dead = 1;
			kill_pids(data, data->philo_num);
			sem_post(data->print_sem);
			break ;
		}
	}
	sem_close(data->check_sem);
	sem_close(data->print_sem);
	sem_close(data->eat_sem);
	free(data->philo);
	free(data->pid);
}

int	main(int ac, char *av[])
{
	t_data	data;

	if (ac < 5)
		return (ft_error());
	if (init_data(&data, av, ac))
		exit(1);
	if (init_process(&data))
		exit(1);
	free_data(&data);
	return (0);
}
