/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:24:32 by nheo              #+#    #+#             */
/*   Updated: 2022/08/19 14:41:52 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_process(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->forks[philo->left]);
	print_status(philo, data, "has", "taken a fork");
	pthread_mutex_lock(&data->forks[philo->right]);
	print_status(philo, data, "has", "taken a fork");
	print_status(philo, data, "is", "eating");
	pthread_mutex_lock(&data->eat_count_mutex);
	philo->eat_count++;
	pthread_mutex_unlock(&data->eat_count_mutex);
	pthread_mutex_lock(&data->eat_mutex);
	philo->last_eat_time = get_time();
	pthread_mutex_unlock(&data->eat_mutex);
	ft_sleep(data->tte);
	pthread_mutex_unlock(&data->forks[philo->left]);
	pthread_mutex_unlock(&data->forks[philo->right]);
}

void	sleep_process(t_philo *philo, t_data *data)
{
	print_status(philo, data, "is", "sleeping");
	ft_sleep(data->tts);
}

void	is_full(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->eat_count_mutex);
	if (philo->eat_count == data->must_eat_count)
		data->full_philos++;
	pthread_mutex_unlock(&data->eat_count_mutex);
}

void	*do_philo(void *param)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)param;
	data = philo->data;
	if (philo->num % 2 == 0 || philo->num == data->philo_num)
		usleep((data->tte - 10) * 1000);
	while (1)
	{
		pthread_mutex_lock(&data->check_mutex);
		if (data->is_dead)
			break ;
		pthread_mutex_unlock(&data->check_mutex);
		eat_process(philo, data);
		if (philo->eat_count >= data->must_eat_count)
			break ;
		sleep_process(philo, data);
		print_status(philo, data, "is", "thinking");
	}
	pthread_mutex_unlock(&philo->data->check_mutex);
	is_full(philo, data);
	return (0);
}
