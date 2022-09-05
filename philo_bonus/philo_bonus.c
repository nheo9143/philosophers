/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:24:28 by nheo              #+#    #+#             */
/*   Updated: 2022/08/30 12:50:31 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <sys/wait.h>

void	wait_process(t_data *data)
{
	int	i;
	int	status;

	i = -1;
	while (++i < data->philo_num)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			kill_pids(data, data->philo_num);
			usleep(10000);
			sem_post(data->check_sem);
			sem_post(data->print_sem);
			break ;
		}
	}
}

void	free_data(t_data *data)
{
	sem_close(data->check_sem);
	sem_close(data->print_sem);
	sem_close(data->eat_sem);
	sem_unlink("fork_sem");
	sem_unlink("eat_sem");
	sem_unlink("print_sem");
	sem_unlink("check_sem");
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
	wait_process(&data);
	free_data(&data);
	return (0);
}
