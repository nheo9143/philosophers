/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:24:38 by nheo              #+#    #+#             */
/*   Updated: 2022/08/21 14:11:37 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/_pthread/_pthread_mutex_t.h>
# include <sys/_pthread/_pthread_t.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define EAT 0
# define SLEEP 1
# define THINK 2

typedef struct s_philo
{
	int				num;
	int				left;
	int				right;
	int				status;
	int				eat_count;
	long			last_eat_time;
	struct s_data	*data;
	pthread_t		thread;
}	t_philo;

typedef struct s_data
{
	int				philo_num;
	int				ttd;
	int				tte;
	int				tts;
	int				must_eat_count;
	int				full_philos;
	int				is_dead;
	long			time;
	struct s_philo	*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	eat_count_mutex;
	pthread_mutex_t	check_mutex;
	pthread_mutex_t	print_mutex;
}	t_data;

int		ft_atoi(const char *str);
int		ft_error(void);
void	print_status(t_philo *philo, t_data *data, char *str1, char *str2);
void	print_result(t_philo *philo, t_data *data, char *str1, char *str2);
int		check_data(t_data *data);
int		ft_sleep(long wait_time);
long	get_time(void);
void	*do_philo(void *param);
int		init_data(t_data *data, char *av[], int ac);
int		init_philo(t_data *data);
int		init_time(t_data *data);
int		init_mutex(t_data *data);
int		init_thread(t_data *data);

#endif
