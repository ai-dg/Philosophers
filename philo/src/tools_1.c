/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:23:03 by dagudelo          #+#    #+#             */
/*   Updated: 2024/05/24 13:24:07 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long time)
{
	usleep(time * 1000);
}

static char	*trim_whitespace(char *str)
{
	while (*str == ' ' || (*str >= 9 && *str <= 13))
	{
		str++;
	}
	return (str);
}

static int	get_number(char *str)
{
	int	count;
	int	n;

	n = 0;
	count = 0;
	while (str[count] >= '0' && str[count] <= '9')
	{
		n = n * 10 + str[count] - '0';
		count++;
	}
	return (n);
}

int	ft_atoi(const char *nptr)
{
	int		sign;
	int		number;
	char	*str;

	str = (char *)nptr;
	sign = 1;
	str = trim_whitespace(str);
	if (str[0] == '+' || str[0] == '-')
	{
		if (str[0] == '-')
			sign *= -1;
		str++;
	}
	number = get_number(str) * sign;
	return (number);
}
