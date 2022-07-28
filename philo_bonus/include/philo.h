/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:43:09 by bperron           #+#    #+#             */
/*   Updated: 2022/07/28 11:42:58 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/stat.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>

# define THINK 1
# define MAX_REP 4
# define DEAD 3

typedef struct s_vars	t_vars;

typedef struct s_philo
{
	int			status;
	int			nb_eat;
	int			philo_nb;
	long		last_eat;
	pid_t		pid;
	t_vars		*vars;
	pthread_t	thread;
}	t_philo;

typedef struct s_vars
{
	int			ttd;
	int			tte;
	int			tts;
	int			rep;
	int			status;
	int			nb_eat;
	int			nb_philo;
	long		begin_time;
	sem_t		*msg;
	sem_t		*kill;
	sem_t		*check;
	sem_t		*forks;
	t_philo		*philos;
	pthread_t	thread;
}	t_vars;

long	ft_atol(char *str);
int		parsing(t_vars *vars, char **av, int ac);
void	print_msg(t_philo *philo, char *str);
long	get_time(void);
void	make_philos(t_vars *vars);
void	my_sleep(int ttw);
void	end_philo(t_vars *vars);

#endif
