/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirony <dirony@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 15:22:48 by dirony            #+#    #+#             */
/*   Updated: 2022/01/26 20:47:36 by dirony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*man_life_cycle(void *man_info)
{
	t_man	*man;
	int		flag;

	man = (t_man *)man_info;
	flag = 1;
	while (flag)
	{
		if (man->number_of_meals == -1
			|| man->meal_counter < man->number_of_meals)
		{
			get_fork_and_eat(man);
			sleep_and_think(man);
		}
		else
			flag = 0;
	}
	return (NULL);
}

void	get_fork_and_eat(t_man *man)
{
	if (man->first_meal && man->number % 2 == 0)
	{
		usleep(10);
		man->first_meal = 0;
	}	
	pthread_mutex_lock(man->left_fork);
	pthread_mutex_lock(man->right_fork);
	man->is_eating = 1;
	man->last_meal_time = get_timestamp(man);
	pthread_mutex_lock(man->speaker);
	printf("%lld %d has taken a fork\n", get_timestamp(man), man->number);
	printf("%lld %d is eating\n", get_timestamp(man), man->number);
	pthread_mutex_unlock(man->speaker);
	usleep(man->time_to_eat * 1000);
	man->meal_counter++;
	pthread_mutex_unlock(man->left_fork);
	pthread_mutex_unlock(man->right_fork);
	man->is_eating = 0;
}

void	sleep_and_think(t_man *man)
{
	if (man->number_of_meals == -1 || man->meal_counter < man->number_of_meals)
	{
		pthread_mutex_lock(man->speaker);
		printf("%lld %d is sleeping\n", get_timestamp(man), man->number);
		pthread_mutex_unlock(man->speaker);
		usleep(man->time_to_sleep * 1000);
		pthread_mutex_lock(man->speaker);
		printf("%lld %d is thinking\n", get_timestamp(man), man->number);
		pthread_mutex_unlock(man->speaker);
	}
}

int	check_everyone_has_eaten(t_table *table, t_man *men)
{
	int	i;
	int	result;

	i = 0;
	result = 1;
	while (result && i < table->number_of_men)
	{
		if (men[i].meal_counter >= table->number_of_meals)
			result = 1;
		else
			result = 0;
		i++;
	}
	return (result);
}

void	clear_table(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_men)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
	free(table->threads);
	pthread_mutex_destroy(table->speaker);
	free(table->speaker);
}
