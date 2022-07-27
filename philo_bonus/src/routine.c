/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 11:22:35 by bperron           #+#    #+#             */
/*   Updated: 2022/07/27 11:10:26 by bperron          ###   ########.fr       */
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
	sem_wait(vars->forks);
	print_msg(philo, "has taken a fork");
	sem_wait(vars->forks);
	print_msg(philo, "has taken a fork");
	print_msg(philo, "is eating");
	philo->last_eat = get_time() - vars->begin_time;
	check_rep(philo, vars);
	my_sleep(vars->tte);
	sem_post(vars->forks);
	sem_post(vars->forks);
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

void	create_sems(t_vars *vars)
{
	sem_unlink("/msg");
	sem_unlink("/check");
	sem_unlink("/forks");
	vars->msg = sem_open("/msg", O_CREAT | O_EXCL, S_IRWXU, 1);
	vars->check = sem_open("/check", O_CREAT | O_EXCL, S_IRWXU, 1);
	vars->forks = sem_open("/forks", O_CREAT | O_EXCL, S_IRWXU, vars->nb_philo);
}

void	make_philos(t_vars *vars)
{
	int	i;

	i = 0;
	vars->philos = malloc(sizeof(t_philo) * vars->nb_philo + 1);
	vars->begin_time = get_time();
	create_sems(vars);
	while (i < vars->nb_philo)
	{
		vars->philos[i].fork = 1;
		vars->philos[i].vars = vars;
		vars->philos[i].philo_nb = i + 1;
		vars->philos[i].status = THINK;
		vars->philos[i].nb_eat = 0;
		pthread_create(&vars->philos[i].thread, NULL,
			routine, (void *) &vars->philos[i]);
		i++;
	}
}
