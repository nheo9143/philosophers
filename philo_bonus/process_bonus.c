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
	sem_wait(data->eat_sem);
	philo->last_eat_time = get_time();
	sem_post(data->eat_sem);
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
		if (get_time() - philo->last_eat_time >= data->ttd)
		{
			sem_post(data->check_sem);
			exit(1);
		}
		sem_post(data->check_sem);
		usleep(100);
	}
	return (0);
}

void	*do_philo(t_data *data, t_philo *philo)
{
	philo->last_eat_time = get_time();
	if (pthread_create(&philo->thread, NULL, &check_dead, philo) != 0)
		exit(1);
	pthread_detach(philo->thread);
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
	exit (0);
}
