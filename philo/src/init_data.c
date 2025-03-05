/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:23:03 by dagudelo          #+#    #+#             */
/*   Updated: 2024/05/24 13:31:54 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	check_arguments(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		ft_putstr_fd("Error: Invalid arguments\n", 2);
		return (1);
	}
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[1]) > 200 || ft_atoi(av[2]) < 0
		|| ft_atoi(av[3]) < 0 || ft_atoi(av[4]) < 0)
	{
		ft_putstr_fd("Error: Invalid arguments\n", 2);
		return (1);
	}
	if (ac == 6 && ft_atoi(av[5]) <= 0)
	{
		ft_putstr_fd("Error: Invalid number of times to eat\n", 2);
		return (1);
	}
	return (0);
}

static void	init_base_data(t_data *data, int ac, char **av)
{
	ft_bzero(data, sizeof(t_data));
	data->num_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->num_of_times_to_eat = -1;
	data->meals_count = false;
}

static void	init_meals_count(t_data *data, int ac, char **av)
{
	if (ac == 6)
	{
		data->num_of_times_to_eat = ft_atoi(av[5]);
		data->meals_count = true;
	}
}

int	init_data(t_data *data, int ac, char **av)
{
	if (check_arguments(ac, av))
		return (1);
	init_base_data(data, ac, av);
	init_meals_count(data, ac, av);
	return (0);
}
