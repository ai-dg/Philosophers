/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:23:03 by dagudelo          #+#    #+#             */
/*   Updated: 2024/05/24 12:51:31 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	choose_forks(t_philo *philo, int *first_fork, int *second_fork)
{
	if (philo->left_fork < philo->right_fork)
	{
		*first_fork = philo->left_fork;
		*second_fork = philo->right_fork;
	}
	else
	{
		*first_fork = philo->right_fork;
		*second_fork = philo->left_fork;
	}
}

static void	lock_forks(t_philo *philo, t_data *data, int first_fork,
		int second_fork)
{
	pthread_mutex_lock(&data->forks[first_fork]);
	philo_print(data, philo->id, "has taken a fork");
	pthread_mutex_lock(&philo->took_fork_mutex);
	philo->took_left_fork = true;
	pthread_mutex_unlock(&philo->took_fork_mutex);
	pthread_mutex_lock(&data->forks[second_fork]);
	philo_print(data, philo->id, "has taken a fork");
	pthread_mutex_lock(&philo->took_fork_mutex);
	philo->took_right_fork = true;
	pthread_mutex_unlock(&philo->took_fork_mutex);
}

static void	unlock_forks(t_philo *philo, t_data *data, int first_fork,
		int second_fork)
{
	pthread_mutex_unlock(&data->forks[second_fork]);
	pthread_mutex_lock(&philo->took_fork_mutex);
	philo->took_right_fork = false;
	pthread_mutex_unlock(&philo->took_fork_mutex);
	pthread_mutex_unlock(&data->forks[first_fork]);
	pthread_mutex_lock(&philo->took_fork_mutex);
	philo->took_left_fork = false;
	pthread_mutex_unlock(&philo->took_fork_mutex);
}

void	philo_eat(t_philo *philo)
{
	t_data	*data;
	int		first_fork;
	int		second_fork;

	data = philo->data;
	choose_forks(philo, &first_fork, &second_fork);
	lock_forks(philo, data, first_fork, second_fork);
	philo_print(data, philo->id, "is eating");
	pthread_mutex_lock(&philo->last_eat_mutex);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->last_eat_mutex);
	ft_usleep(data->time_to_eat);
	pthread_mutex_lock(&philo->eat_count_mutex);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->eat_count_mutex);
	pthread_mutex_lock(&data->eat_count_mutex);
	if (data->meals_count && philo->eat_count == data->num_of_times_to_eat)
	{
		data->num_philos_ate_enough++;
	}
	pthread_mutex_unlock(&data->eat_count_mutex);
	unlock_forks(philo, data, first_fork, second_fork);
}
