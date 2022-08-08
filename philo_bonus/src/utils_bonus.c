/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 11:21:37 by bperron           #+#    #+#             */
/*   Updated: 2022/08/08 08:56:33 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

long	get_time(void)
{
	long			time;
	struct timeval	temp;

	gettimeofday(&temp, NULL);
	time = (temp.tv_sec * 1000) + (temp.tv_usec / 1000);
	return (time);
}

void	my_sleep(int ttw)
{
	long	start;
	long	tw;

	start = get_time();
	while (1)
	{
		tw = get_time() - start;
		if (tw >= ttw)
			break ;
		usleep(50);
	}
}

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

void	print_msg(t_philo *philo, char *str)
{
	sem_wait(philo->vars->msg);
	printf("%ld %d %s\n", (get_time() - philo->vars->begin_time),
		philo->philo_nb, str);
	sem_post(philo->vars->msg);
}
