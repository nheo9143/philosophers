/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:24:32 by nheo              #+#    #+#             */
/*   Updated: 2022/08/21 14:45:40 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat_process(t_philo *philo, t_data *data)
{
	sem_wait(data->forks);
	print_status(philo, data, "has", "taken a fork");
	sem_wait(data->forks);
	print_status(philo, data, "has", "taken a fork");
	print_status(philo, data, "is", "eating");
	philo->eat_count++;
	pthread_mutex_lock(&philo->eat_mutex);
	philo->last_eat_time = get_time();
	pthread_mutex_unlock(&philo->eat_mutex);
	ft_sleep(data->tte);
	philo->status = SLEEP;
	sem_post(data->forks);
	sem_post(data->forks);
}

void	sleep_process(t_philo *philo, t_data *data)
{
	print_status(philo, data, "is", "sleeping");
	ft_sleep(data->tts);
	philo->status = THINK;
}

void	think_process(t_philo *philo, t_data *data)
{
	print_status(philo, data, "is", "thinking");
	philo->status = EAT;
}

void	*check_dead(void *param)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)param;
	data = philo->data;
	while (1)
	{
		sem_wait(data->check_sem);
		pthread_mutex_lock(&philo->eat_mutex);
		if (get_time() - philo->last_eat_time >= data->ttd)
		{
			sem_wait(data->print_sem);
			printf("%ld %d %s %s\n", get_time() - data->time, philo->num, "is", "dead");
			pthread_mutex_unlock(&philo->eat_mutex);
			pthread_mutex_destroy(&philo->eat_mutex);
			exit(1);
		}
		pthread_mutex_unlock(&philo->eat_mutex);
		sem_post(data->check_sem);
		usleep(100);
	}
	return (0);
}

void	*do_philo(t_data *data, t_philo *philo)
{
	if (pthread_create(&philo->thread, NULL, &check_dead, philo) != 0)
		exit(1);
	pthread_mutex_init(&philo->eat_mutex, NULL);
	while (1)
	{
		if (data->must_eat_count >= 0
			&& philo->eat_count >= data->must_eat_count)
			break ;
		if (philo->status == EAT)
			eat_process(philo, data);
		else if (philo->status == SLEEP)
			sleep_process(philo, data);
		else if (philo->status == THINK)
			think_process(philo, data);
	}
	pthread_mutex_unlock(&philo->eat_mutex);
	pthread_mutex_destroy(&philo->eat_mutex);
	exit (0);
}
