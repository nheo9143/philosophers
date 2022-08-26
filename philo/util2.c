/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:24:36 by nheo              #+#    #+#             */
/*   Updated: 2022/08/19 14:24:36 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_result(t_philo *philo, t_data *data, char *str1, char *str2)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d %s %s\n", get_time() - data->time, philo->num, str1, str2);
}

void	print_status(t_philo *philo, t_data *data, char *str1, char *str2)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&data->check_mutex);
	if (data->is_dead == 1)
	{
		pthread_mutex_unlock(&data->check_mutex);
		pthread_mutex_unlock(&data->print_mutex);
		return ;
	}
	pthread_mutex_unlock(&data->check_mutex);
	printf("%ld %d %s %s\n", get_time() - data->time, philo->num, str1, str2);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	ft_error(void)
{
	write(2, "error\n", 6);
	return (1);
}
