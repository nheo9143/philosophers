/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:24:28 by nheo              #+#    #+#             */
/*   Updated: 2022/08/19 16:02:37 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	free_data(t_data *data)
{
	int	i;

	i = -1;
	if (data->philo_num == 1)
		pthread_detach(data->philo[i].thread);
	else
	{
		while (++i < data->philo_num)
			pthread_join(data->philo[i].thread, NULL);
	}
	while (++i < data->philo_num)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->eat_mutex);
	pthread_mutex_destroy(&data->eat_count_mutex);
	pthread_mutex_destroy(&data->check_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	free(data->forks);
	free(data->philo);
}

int	check_death(t_philo *philo, t_data *data)
{
	int		is_dead;
	long	now;

	is_dead = 0;
	now = get_time();
	pthread_mutex_lock(&data->eat_mutex);
	if (now - philo->last_eat_time >= data->ttd)
		is_dead = 1;
	pthread_mutex_unlock(&data->eat_mutex);
	pthread_mutex_lock(&data->check_mutex);
	if (is_dead)
		data->is_dead = 1;
	pthread_mutex_unlock(&data->check_mutex);
	return (is_dead);
}

void	mornitering(t_data *data)
{
	int	i;

	i = -1;
	while (1)
	{
		if (++i >= data->philo_num)
			i = 0;
		pthread_mutex_lock(&data->eat_count_mutex);
		if (data->full_philos == data->philo_num)
		{
			pthread_mutex_unlock(&data->check_mutex);
			break ;
		}
		else if (check_death(&data->philo[i], data) == 1)
		{
			print_result(&data->philo[i], data, "is", "dead");
			pthread_mutex_unlock(&data->eat_count_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->eat_count_mutex);
	}
}

int	main(int ac, char *av[])
{
	t_data	data;

	if (ac < 5)
		return (ft_error());
	if (init_data(&data, av, ac))
		return (ft_error());
	if (init_thread(&data))
		return (ft_error());
	mornitering(&data);
	free_data(&data);
	return (0);
}