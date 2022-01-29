/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirony <dirony@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 20:16:51 by dirony            #+#    #+#             */
/*   Updated: 2022/01/22 16:44:20 by dirony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char ch)
{
	if ((ch >= '0') && (ch <= '9'))
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	result = 0;
	sign = 1;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		result = result * 10;
		result = result + str[i] - 48;
		i++;
	}
	return ((int) result * sign);
}

int	check_args(int argc, char **argv)
{
	int	result;
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (0);
	result = 1;
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				result = 0;
			j++;
		}
		i++;
	}
	return (result);
}

int	parse_args(int argc, char **argv, t_table *table)
{
	if (!check_args(argc, argv))
		return (0);
	table->number_of_men = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->number_of_meals = ft_atoi(argv[5]);
	else
		table->number_of_meals = -1;
	if (table->number_of_meals == 0)
		return (0);
	return (1);
}
