/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:44:06 by bperron           #+#    #+#             */
/*   Updated: 2022/07/28 14:24:51 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_status(t_vars *vars)
{
	long	current;
	int		philo;

	philo = 0;
	while (1)
	{
		current = get_time() - vars->begin_time - vars->philos[philo].last_eat;
		pthread_mutex_lock(&vars->check);
		if (current >= vars->ttd)
		{
			vars->status = DEAD;
			print_msg(&vars->philos[philo], "has died");
			pthread_mutex_lock(&vars->msg);
			return (1);
		}
		if (vars->rep != -2)
		{
			if (vars->nb_philo == vars->nb_eat)
				return (1);
		}
		pthread_mutex_unlock(&vars->check);
		philo++;
		if (philo == vars->nb_philo)
			philo = 0;
	}
	return (0);
}

void	end_philo(t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < vars->nb_philo)
		pthread_mutex_destroy(&vars->forks[i]);
	pthread_mutex_destroy(&vars->msg);
	pthread_mutex_destroy(&vars->check);
	free(vars->forks);
	free(vars->philos);
}

int	main(int ac, char *av[])
{
	t_vars	vars;

	if (ac > 4 && ac < 7)
	{
		if (parsing(&vars, av, ac) != 1)
			return (0);
		make_philos(&vars);
		if (check_status(&vars) == 1)
		{
			end_philo(&vars);
			return (0);
		}
	}
	else
	{
		printf("Error\nThe number of arguments entered is incorrect\n");
		return (0);
	}
	return (0);
}
