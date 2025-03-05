/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:23:03 by dagudelo          #+#    #+#             */
/*   Updated: 2024/05/24 12:59:28 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	check_forks_taken(t_data *data, int i, bool *left_fork,
		bool *right_fork)
{
	pthread_mutex_lock(&data->philo[i].took_fork_mutex);
	*left_fork = data->philo[i].took_left_fork;
	*right_fork = data->philo[i].took_right_fork;
	pthread_mutex_unlock(&data->philo[i].took_fork_mutex);
	return (!(*left_fork) && !(*right_fork));
}

static void	mark_philosopher_dead(t_data *data, int i)
{
	philo_print(data, data->philo[i].id, "died");
	pthread_mutex_lock(&data->dead_mutex);
	data->philo_dead = true;
	pthread_mutex_unlock(&data->dead_mutex);
	pthread_mutex_lock(&data->finish_mutex);
	data->finished = true;
	pthread_mutex_unlock(&data->finish_mutex);
}

static bool	has_philosopher_died(t_data *data, int i)
{
	long	time_since_last_eat;
	bool	took_left_fork;
	bool	took_right_fork;

	pthread_mutex_lock(&data->philo[i].last_eat_mutex);
	time_since_last_eat = get_time() - data->philo[i].last_eat;
	pthread_mutex_unlock(&data->philo[i].last_eat_mutex);
	if (check_forks_taken(data, i, &took_left_fork, &took_right_fork)
		&& (time_since_last_eat > data->time_to_die) && !data->meals_count)
	{
		mark_philosopher_dead(data, i);
		return (true);
	}
	return (false);
}

static bool	have_all_philosophers_eaten(t_data *data)
{
	pthread_mutex_lock(&data->eat_count_mutex);
	if (data->meals_count && data->num_philos_ate_enough >= data->num_of_philos)
	{
		pthread_mutex_unlock(&data->eat_count_mutex);
		pthread_mutex_lock(&data->finish_mutex);
		data->finished = true;
		pthread_mutex_unlock(&data->finish_mutex);
		return (true);
	}
	pthread_mutex_unlock(&data->eat_count_mutex);
	return (false);
}

void	*check_death(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->num_of_philos)
		{
			if (has_philosopher_died(data, i))
				return (NULL);
			i++;
		}
		if (have_all_philosophers_eaten(data))
			return (NULL);
		usleep(500);
	}
	return (NULL);
}
