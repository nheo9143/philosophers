/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:24:38 by nheo              #+#    #+#             */
/*   Updated: 2022/08/21 14:42:01 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <sys/_pthread/_pthread_t.h>
# include <sys/_types/_pid_t.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				num;
	int				eat_count;
	long			last_eat_time;
	pthread_t		thread;
	struct s_data	*data;
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
	pid_t			*pid;
	struct s_philo	*philo;
	sem_t			*forks;
	sem_t			*eat_sem;
	sem_t			*eat_count_sem;
	sem_t			*check_sem;
	sem_t			*print_sem;
}	t_data;

int		ft_atoi(const char *str);
int		ft_error(void);
void	print_status(t_philo *philo, t_data *data, char *str1, char *str2);
void	print_result(t_philo *philo, t_data *data, char *str1, char *str2);
int		check_data(t_data *data);
void	ft_sleep(long wait_time);
long	get_time(void);
void	*do_philo(t_data *data, t_philo *philo);
int		init_data(t_data *data, char *av[], int ac);
int		init_philo(t_data *data);
int		init_time(t_data *data);
int		init_sem(t_data *data);
int		init_process(t_data *data);
void	kill_pids(t_data *data, int pid_num);

#endif
