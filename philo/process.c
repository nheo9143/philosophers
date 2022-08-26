/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:24:32 by nheo              #+#    #+#             */
/*   Updated: 2022/08/21 14:27:49 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_process(t_philo *philo, t_data *data)
{
	if (philo->num % 2 == 0)
	{
		pthread_mutex_lock(&data->forks[philo->left]);
		print_status(philo, data, "has", "taken a fork");
		pthread_mutex_lock(&data->forks[philo->right]);
		print_status(philo, data, "has", "taken a fork");
	}
	else
	{
		pthread_mutex_lock(&data->forks[philo->right]);
		print_status(philo, data, "has", "taken a fork");
		pthread_mutex_lock(&data->forks[philo->left]);
		print_status(philo, data, "has", "taken a fork");
	}
	print_status(philo, data, "is", "eating");
	pthread_mutex_lock(&data->eat_mutex);
	philo->last_eat_time = get_time();
	pthread_mutex_unlock(&data->eat_mutex);
	philo->eat_count++;
	ft_sleep(data->tte);
	philo->status = SLEEP;
	pthread_mutex_unlock(&data->forks[philo->left]);
	pthread_mutex_unlock(&data->forks[philo->right]);
}

void	sleep_process(t_philo *philo, t_data *data)
{
	print_status(philo, data, "is", "sleeping");
	ft_sleep(data->tts);
	philo->status = THINK;
}

void	check_is_full(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->eat_count_mutex);
	if (philo->eat_count == data->must_eat_count)
		data->full_philos++;
	pthread_mutex_unlock(&data->eat_count_mutex);
}

void	think_process(t_philo *philo, t_data *data)
{
	print_status(philo, data, "is", "thinking");
	philo->status = EAT;
}

void	*do_philo(void *param)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)param;
	data = philo->data;
	while (1)
	{
		if (data->must_eat_count >= 0
			&& philo->eat_count >= data->must_eat_count)
			break ;
		pthread_mutex_lock(&data->check_mutex);
		if (data->is_dead)
			break ;
		pthread_mutex_unlock(&data->check_mutex);
		if (philo->status == EAT)
			eat_process(philo, data);
		else if (philo->status == SLEEP)
			sleep_process(philo, data);
		else if (philo->status == THINK)
			think_process(philo, data);
	}
	pthread_mutex_unlock(&philo->data->check_mutex);
	check_is_full(philo, data);
	return (0);
}
