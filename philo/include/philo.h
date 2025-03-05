/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:23:10 by dagudelo          #+#    #+#             */
/*   Updated: 2024/05/24 13:30:17 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

typedef struct s_philo
{
	int					id;
	int					left_fork;
	bool				took_left_fork;
	int					right_fork;
	bool				took_right_fork;
	int					eat_count;
	long				last_eat;
	pthread_t			thread;
	pthread_mutex_t		last_eat_mutex;
	pthread_mutex_t		eat_count_mutex;
	pthread_mutex_t		took_fork_mutex;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	int					num_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_of_times_to_eat;
	int					num_philos_ate_enough;
	long				start;
	bool				philo_dead;
	bool				finished;
	bool				meals_count;
	t_philo				*philo;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print;
	pthread_mutex_t		eat_count_mutex;
	pthread_mutex_t		finish_mutex;
	pthread_mutex_t		dead_mutex;
}						t_data;

/**
 * @brief List of utility functions
 */
int						ft_atoi(const char *nptr);
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char *s, int fd);
int						ft_strcmp(const char *s1, const char *s2);
void					ft_bzero(void *s, size_t n);
long					get_time(void);
void					ft_usleep(long time);

/**
 * @brief Main fonctions
 */
int						init_data(t_data *data, int ac, char **av);
int						init_philo(t_data *data);
void					init_mutex(t_data *data);
void					philo_start(t_data *data);
void					*philo_life(void *arg);
void					philo_print(t_data *data, int id, char *str);
void					philo_eat(t_philo *philo);
void					*check_death(void *arg);
void					destroy_philo(t_data *data);
void					destroy_mutex(t_data *data);

#endif
