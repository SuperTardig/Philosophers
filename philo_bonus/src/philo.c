/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:44:06 by bperron           #+#    #+#             */
/*   Updated: 2022/07/27 10:55:06 by bperron          ###   ########.fr       */
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
		if (current > vars->ttd)
		{
			print_msg(&vars->philos[philo], "has died");
			return (1);
		}
		if (vars->rep != -2)
		{
			if (vars->nb_philo == vars->nb_eat)
				return (1);
		}
		philo++;
		if (philo == vars->nb_philo)
			philo = 0;
	}
	return (0);
}

void	end_philo(t_vars *vars)
{
	sem_close(vars->msg);
	sem_close(vars->check);
	sem_close(vars->forks);
	free(vars->philos);
}

int	main(int ac, char *av[])
{
	t_vars	vars;

	if (ac > 4 && ac < 7)
	{
		if (parsing(&vars, av, ac) == 0)
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
