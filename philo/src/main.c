/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:23:03 by dagudelo          #+#    #+#             */
/*   Updated: 2024/05/24 13:31:58 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_print(t_data *data, int id, char *str)
{
	long	time;

	pthread_mutex_lock(&data->print);
	time = get_time() - data->start;
	pthread_mutex_lock(&data->dead_mutex);
	if (!data->philo_dead)
		printf("%ld %d %s\n", time, id, str);
	pthread_mutex_unlock(&data->dead_mutex);
	pthread_mutex_unlock(&data->print);
}

int	init_philo(t_data *data)
{
	int	i;

	data->philo = (t_philo *)malloc(sizeof(t_philo) * data->num_of_philos);
	if (!data->philo)
	{
		ft_putstr_fd("Error: Malloc failed\n", 2);
		return (1);
	}
	i = 0;
	while (i < data->num_of_philos)
	{
		data->philo[i].id = i + 1;
		data->philo[i].eat_count = 0;
		data->philo[i].data = data;
		data->philo[i].left_fork = i;
		data->philo[i].right_fork = (i + 1) % data->num_of_philos;
		data->philo[i].took_left_fork = false;
		data->philo[i].took_right_fork = false;
		pthread_mutex_init(&data->philo[i].last_eat_mutex, NULL);
		pthread_mutex_init(&data->philo[i].eat_count_mutex, NULL);
		pthread_mutex_init(&data->philo[i].took_fork_mutex, NULL);
		i++;
	}
	return (0);
}

void	join_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
}

void	philo_start(t_data *data)
{
	int			i;
	pthread_t	death_thread;

	data->start = get_time();
	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_lock(&data->philo[i].last_eat_mutex);
		data->philo[i].last_eat = data->start;
		pthread_mutex_unlock(&data->philo[i].last_eat_mutex);
		pthread_create(&data->philo[i].thread, NULL, philo_life,
			&data->philo[i]);
		i++;
	}
	pthread_create(&death_thread, NULL, check_death, data);
	pthread_join(death_thread, NULL);
	join_thread(data);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (init_data(&data, ac, av))
		return (1);
	if (init_philo(&data) == 1)
		return (1);
	init_mutex(&data);
	philo_start(&data);
	destroy_mutex(&data);
	destroy_philo(&data);
	return (0);
}
