/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 11:21:37 by bperron           #+#    #+#             */
/*   Updated: 2022/08/01 12:46:39 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

void	print_msg(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->vars->msg);
	printf("%ld %d %s\n", (get_time() - philo->vars->begin_time),
		philo->philo_nb, str);
	pthread_mutex_unlock(&philo->vars->msg);
}
