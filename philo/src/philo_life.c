/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:23:03 by dagudelo          #+#    #+#             */
/*   Updated: 2024/05/24 12:59:22 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	single_philosopher(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->forks[philo->left_fork]);
	philo_print(data, philo->id, "has taken a fork");
	ft_usleep(data->time_to_die);
	philo_print(data, philo->id, "died");
	pthread_mutex_lock(&data->dead_mutex);
	data->philo_dead = true;
	pthread_mutex_unlock(&data->dead_mutex);
	pthread_mutex_lock(&data->finish_mutex);
	data->finished = true;
	pthread_mutex_unlock(&data->finish_mutex);
	pthread_mutex_unlock(&data->forks[philo->left_fork]);
}

static bool	check_termination_conditions(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->dead_mutex);
	if (data->philo_dead)
	{
		pthread_mutex_unlock(&data->dead_mutex);
		return (true);
	}
	pthread_mutex_unlock(&data->dead_mutex);
	pthread_mutex_lock(&data->finish_mutex);
	if (data->meals_count && philo->eat_count >= data->num_of_times_to_eat)
	{
		pthread_mutex_unlock(&data->finish_mutex);
		return (true);
	}
	pthread_mutex_unlock(&data->finish_mutex);
	return (false);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2)
		usleep(15000);
	if (data->num_of_philos == 1)
	{
		single_philosopher(philo, data);
		return (NULL);
	}
	while (1)
	{
		if (check_termination_conditions(philo, data))
			break ;
		philo_eat(philo);
		philo_print(data, philo->id, "is sleeping");
		ft_usleep(data->time_to_sleep);
		philo_print(data, philo->id, "is thinking");
	}
	return (NULL);
}
