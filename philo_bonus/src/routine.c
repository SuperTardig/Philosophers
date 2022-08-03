/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 11:22:35 by bperron           #+#    #+#             */
/*   Updated: 2022/08/03 11:15:00 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
	check_rep(philo, vars);
	my_sleep(vars->tte);
	philo->last_eat = get_time() - philo->vars->begin_time;
	sem_post(vars->forks);
	sem_post(vars->forks);
}

void	*check_life(void *temp)
{
	t_philo	*philo;
	long	diff;

	philo = temp;
	while (1)
	{
		sem_wait(philo->vars->check);
		diff = get_time() - philo->vars->begin_time - philo->last_eat;
		if (diff > philo->vars->ttd)
		{
			print_msg(philo, "has died");
			sem_post(philo->vars->kill);
			philo->status = DEAD;
			free(philo->vars->philos);
			exit (0);
		}
		sem_post(philo->vars->check);
	}
	return (NULL);
}

void	routine(t_philo *philo, t_vars *vars)
{
	pthread_create(&philo->thread, NULL,
		check_life, (void *) philo);
	if (philo->philo_nb % 2 == 0)
		usleep(15000);
	while (philo->status != MAX_REP)
	{
		check_fork(philo, vars);
		if (philo->status != DEAD)
		{
			print_msg(philo, "is sleeping");
			my_sleep(vars->tts);
		}
		if (philo->status != DEAD)
			print_msg(philo, "is thinking");
		if (philo->status == MAX_REP)
		{
			free(vars->philos);
			exit (0);
		}
	}
	pthread_join(philo->thread, NULL);
}

void	create_sems(t_vars *vars)
{
	sem_unlink("/msg");
	sem_unlink("/check");
	sem_unlink("/forks");
	sem_unlink("/kill");
	vars->msg = sem_open("/msg", O_CREAT | O_EXCL, S_IRWXU, 1);
	vars->kill = sem_open("/kill", O_CREAT | O_EXCL, S_IRWXU, 0);
	vars->check = sem_open("/check", O_CREAT | O_EXCL, S_IRWXU, 1);
	vars->forks = sem_open("/forks", O_CREAT | O_EXCL, S_IRWXU, vars->nb_philo);
}

void	make_philos(t_vars *vars)
{
	int	i;

	i = 0;
	vars->philos = malloc(sizeof(t_philo) * vars->nb_philo);
	if (!vars->philos)
		exit (1);
	create_sems(vars);
	vars->begin_time = get_time();
	while (i < vars->nb_philo)
	{
		vars->philos[i].vars = vars;
		vars->philos[i].philo_nb = i + 1;
		vars->philos[i].status = THINK;
		vars->philos[i].nb_eat = 0;
		vars->philos[i].pid = fork();
		if (vars->philos[i].pid == 0)
			routine (&vars->philos[i], vars);
		i++;
	}
	end_philo(vars);
}
