/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:24:30 by nheo              #+#    #+#             */
/*   Updated: 2022/08/21 14:13:00 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, char *av[], int ac)
{
	int	error;

	error = 0;
	data->philo_num = ft_atoi(av[1]);
	data->ttd = ft_atoi(av[2]);
	data->tte = ft_atoi(av[3]);
	data->tts = ft_atoi(av[4]);
	if (ac == 6)
		data->must_eat_count = ft_atoi(av[5]);
	else
		data->must_eat_count = -2;
	data->is_dead = 0;
	data->full_philos = 0;
	if (check_data(data))
		error = 1;
	if (!error)
		error = init_mutex(data);
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
		data->philo[i].status = i % 2;
		data->philo[i].data = data;
		data->philo[i].eat_count = 0;
		data->philo[i].left = i;
		data->philo[i].last_eat_time = get_time();
		if (data->philo[i].last_eat_time < 0)
			return (1);
		if (i + 1 < data->philo_num)
			data->philo[i].right = i + 1;
		else
			data->philo[i].right = 0;
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

int	init_mutex(t_data *data)
{
	int	i;
	int	error;

	error = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!data->forks)
		error = 1;
	i = -1;
	while (!error && ++i < data->philo_num)
		error = pthread_mutex_init(&data->forks[i], NULL);
	if (!error)
		error = pthread_mutex_init(&data->eat_mutex, NULL);
	if (!error)
		error = pthread_mutex_init(&data->eat_count_mutex, NULL);
	if (!error)
		error = pthread_mutex_init(&data->check_mutex, NULL);
	if (!error)
		error = pthread_mutex_init(&data->print_mutex, NULL);
	return (error);
}

int	init_thread(t_data *data)
{
	int			i;
	int			error;

	i = -1;
	error = 0;
	while (++i < data->philo_num)
	{
		error = pthread_create(&data->philo[i].thread,
				NULL, &do_philo, &data->philo[i]);
		if (error != 0)
			break ;
	}
	i = -1;
	while (++i < data->philo_num)
		pthread_detach(data->philo[i].thread);
	return (error);
}
