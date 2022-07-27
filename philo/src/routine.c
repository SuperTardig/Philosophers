/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 11:22:35 by bperron           #+#    #+#             */
/*   Updated: 2022/07/27 12:51:20 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	check_rep(t_philo *philo, t_vars *vars)
{
	if (vars->rep != -2)
	{
		philo->nb_eat++;
		if (philo->nb_eat == vars->rep)
		{
			vars->nb_eat++;
			philo->status = MAX_REP;
		}
	}
}

void	check_fork(t_philo *philo, t_vars *vars)
{
	int	next;

	if (philo->philo_nb == vars->nb_philo)
		next = 1;
	else
		next = philo->philo_nb + 1;
	pthread_mutex_lock(&vars->forks[philo->philo_nb - 1]);
	print_msg(philo, "has taken a fork");
	pthread_mutex_lock(&vars->forks[next - 1]);
	print_msg(philo, "has taken a fork");
	print_msg(philo, "is eating");
	philo->last_eat = get_time() - vars->begin_time;
	check_rep(philo, vars);
	my_sleep(vars->tte);
	pthread_mutex_unlock(&vars->forks[philo->philo_nb - 1]);
	pthread_mutex_unlock(&vars->forks[next - 1]);
	print_msg(philo, "is sleeping");
	my_sleep(vars->tts);
}

void	*routine(void *temp)
{
	t_philo	*philo;
	t_vars	*vars;

	philo = (t_philo *) temp;
	vars = philo->vars;
	if (philo->philo_nb % 2 == 0)
		usleep(15000);
	while (philo->status != MAX_REP)
	{
		check_fork(philo, vars);
		print_msg(philo, "is thinking");
	}
	return (NULL);
}

void	make_philos(t_vars *vars)
{
	int	i;

	i = 0;
	vars->philos = malloc(sizeof(t_philo) * vars->nb_philo + 1);
	if (!vars->philos)
		return ;
	pthread_mutex_init(&vars->msg, NULL);
	pthread_mutex_init(&vars->check, NULL);
	vars->begin_time = get_time();
	while (i < vars->nb_philo)
	{
		vars->philos[i].vars = vars;
		vars->philos[i].philo_nb = i + 1;
		vars->philos[i].status = THINK;
		vars->philos[i].nb_eat = 0;
		pthread_mutex_init(&vars->forks[i], NULL);
		pthread_create(&vars->philos[i].thread, NULL,
			routine, (void *) &vars->philos[i]);
		i++;
	}
}
