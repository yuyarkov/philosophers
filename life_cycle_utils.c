/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirony <dirony@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 15:22:48 by dirony            #+#    #+#             */
/*   Updated: 2022/01/22 15:51:01 by dirony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*man_life_cycle(void *man_info)
{
	t_man	*man;

	man = (t_man *)man_info;
	while (1)
	{
		get_fork_and_eat(man);
		sleep_and_think(man);
	}
	return (NULL);
}

void	get_fork_and_eat(t_man *man)
{
	if (man->first_meal && man->number % 2 == 0)
	{
		usleep(50);
		man->first_meal = 0;
	}	
	pthread_mutex_lock(man->left_fork);
	pthread_mutex_lock(man->right_fork);
	man->is_eating = 1;
	man->last_meal_time = get_timestamp(man);
	man->meal_counter++;
	pthread_mutex_lock(man->speaker);
	printf("%lld %d has taken a fork\n", get_timestamp(man), man->number);
	printf("%lld %d is eating\n", get_timestamp(man), man->number);
	pthread_mutex_unlock(man->speaker);
	usleep(man->time_to_eat * 1000);
	pthread_mutex_unlock(man->left_fork);
	pthread_mutex_unlock(man->right_fork);
	man->is_eating = 0;
}

void	sleep_and_think(t_man *man)
{
	pthread_mutex_lock(man->speaker);
	printf("%lld %d is sleeping\n", get_timestamp(man), man->number);
	pthread_mutex_unlock(man->speaker);
	usleep(man->time_to_sleep * 1000);
	pthread_mutex_lock(man->speaker);
	printf("%lld %d is thinking\n", get_timestamp(man), man->number);
	pthread_mutex_unlock(man->speaker);
}

int	check_everyone_has_eaten(t_table *table, t_man *men)
{
	int	i;
	int	result;

	i = 0;
	result = 1;
	while (result && i < table->number_of_men)
	{
		if (men[i].meal_counter >= table->number_of_meals && !men[i].is_eating)
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
