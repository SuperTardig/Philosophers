/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:44:06 by bperron           #+#    #+#             */
/*   Updated: 2022/08/03 11:07:11 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*check_kill(void *temp)
{
	t_vars	*vars;
	int		i;

	vars = temp;
	sem_wait(vars->kill);
	i = 0;
	while (i < vars->nb_philo)
		kill(vars->philos[i++].pid, SIGTERM);
	return (NULL);
}

void	end_philo(t_vars *vars)
{
	int	i;

	i = 0;
	pthread_create(&vars->thread, NULL,
		check_kill, (void *) vars);
	while (i < vars->nb_philo)
		waitpid(vars->philos[i++].pid, NULL, 0);
	sem_post(vars->kill);
	sem_close(vars->msg);
	sem_close(vars->kill);
	sem_close(vars->check);
	sem_close(vars->forks);
	sem_unlink("/msg");
	sem_unlink("/kill");
	sem_unlink("/check");
	sem_unlink("/forks");
	free(vars->philos);
	pthread_join(vars->thread, NULL);
	exit (0);
}

int	main(int ac, char *av[])
{
	t_vars	vars;
	int		i;

	i = 0;
	if (ac > 4 && ac < 7)
	{
		if (parsing(&vars, av, ac) == 0)
			return (0);
		make_philos(&vars);
	}
	else
	{
		printf("Error\nThe number of arguments entered is incorrect\n");
		return (0);
	}
	return (0);
}
