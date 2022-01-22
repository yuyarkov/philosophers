/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirony <dirony@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 23:08:25 by dirony            #+#    #+#             */
/*   Updated: 2022/01/19 20:18:03 by dirony           ###   ########.fr       */
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
