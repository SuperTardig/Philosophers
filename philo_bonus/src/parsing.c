/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 10:53:19 by bperron           #+#    #+#             */
/*   Updated: 2022/07/27 13:48:50 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	ft_atol(char *str)
{
	int		i;
	long	nbr;

	i = 0;
	nbr = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		i++;
	if (str[i] != '\0' || i > 12)
		return (-1);
	i = 0;
	while (str[i])
	{
		nbr *= 10;
		nbr += str[i] - '0';
		i++;
	}
	if (nbr > INT_MAX)
		return (-1);
	return (nbr);
}

int	parsing(t_vars *vars, char **av, int ac)
{
	vars->nb_philo = ft_atol(av[1]);
	vars->ttd = ft_atol(av[2]);
	vars->tte = ft_atol(av[3]);
	vars->tts = ft_atol(av[4]);
	vars->status = 0;
	vars->nb_eat = 0;
	if (ac == 6)
		vars->rep = ft_atol(av[5]);
	else
		vars->rep = -2;
	if (vars->tts == -1 || vars->tte == -1 || vars->ttd == -1
		|| vars->nb_philo == -1 || vars->rep == -1)
	{
		printf("Error\nA bad argument was passed\n");
		return (0);
	}
	if (vars->nb_philo > 200 || vars->nb_philo < 1)
	{
		printf("Error\nThe number of philo is wrong\n");
		return (0);
	}
	return (1);
}
