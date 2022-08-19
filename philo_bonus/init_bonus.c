/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:24:30 by nheo              #+#    #+#             */
/*   Updated: 2022/08/19 17:14:26 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <sys/_types/_pid_t.h>
#include <sys/fcntl.h>
#include <sys/semaphore.h>

int	init_data(t_data *data, char *av[], int ac)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	data->philo_num = ft_atoi(av[1]);
	data->ttd = ft_atoi(av[2]);
	data->tte = ft_atoi(av[3]);
	data->tts = ft_atoi(av[4]);
	if (ac == 6)
		data->must_eat_count = ft_atoi(av[5]);
	else
		data->must_eat_count = 2147483647;
	data->is_dead = 0;
	data->full_philos = 0;
	if (check_data(data))
		error = 1;
	if (!error)
		error = init_sem(data);
	if (!error)
		error = init_philo(data);
	if (!error)
		error = init_time(data);
	return (error);
}

int	init_philo(t_data *data)
{
	int	i;
	int	error;

	i = -1;
	error = 0;
	data->philo = (t_philo *)malloc(sizeof(t_philo) * data->philo_num);
	if (!data->philo)
		error = 1;
	while (!error && ++i < data->philo_num)
	{
		data->philo[i].num = i + 1;
		data->philo[i].data = data;
		data->philo[i].eat_count = 0;
		data->philo[i].left = i;
		data->philo[i].last_eat_time = get_time();
	}
	return (error);
}

int	init_time(t_data *data)
{
	int	error;

	error = 0;
	data->time = get_time();
	if (data->time < 0)
		error = 1;
	return (error);
}

int	init_sem(t_data *data)
{
	int	error;

	error = 0;
	sem_unlink("fork_sem");
	sem_unlink("eat_sem");
	sem_unlink("print_sem");
	sem_unlink("check_sem");
	data->forks = sem_open("fork_sem", O_CREAT, 0644, data->philo_num);
	if (data->forks == SEM_FAILED)
		error = 1;
	data->eat_sem = sem_open("eat_sem", O_CREAT, 0644, 1);
	if (data->eat_sem == SEM_FAILED)
		error = 1;
	data->check_sem = sem_open("check_sem", O_CREAT, 0644, 1);
	if (data->check_sem == SEM_FAILED)
		error = 1;
	data->print_sem = sem_open("print_sem", O_CREAT, 0644, 1);
	if (data->print_sem == SEM_FAILED)
		error = 1;
	return (error);
}

int	init_process(t_data *data)
{
	int			i;

	i = -1;
	data->pid = malloc(sizeof(pid_t) * data->philo_num);
	if (!data->pid)
		return (1);
	while (++i < data->philo_num)
	{
		data->pid[i] = fork();
		if (data->pid[i] < 0)
		{
			kill_pids(data, i);
			return (1);
		}
		if (data->pid[i] == 0)
			do_philo(data, &data->philo[i]);
	}
	return (0);
}
