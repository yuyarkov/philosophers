/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirony <dirony@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 20:26:14 by dirony            #+#    #+#             */
/*   Updated: 2022/01/22 15:27:19 by dirony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_table(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(t_mutex) * table->number_of_men);
	if (NULL == table->forks)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < table->number_of_men)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	table->threads = malloc(sizeof(pthread_t) * table->number_of_men);
	if (NULL == table->threads)
		exit(EXIT_FAILURE);
	table->speaker = malloc(sizeof(t_mutex));
	if (NULL == table->speaker)
		exit(EXIT_FAILURE);
	pthread_mutex_init(table->speaker, NULL);
}

void	init_man(t_table *table, t_man *man, int i)
{
	man->number = i + 1;
	man->time_to_die = table->time_to_die;
	man->time_to_eat = table->time_to_eat;
	man->time_to_sleep = table->time_to_sleep;
	man->number_of_meals = table->number_of_meals;
	man->creation_time = table->creation_time;
	man->speaker = table->speaker;
	man->first_meal = 1;
	man->last_meal_time = 0;
	man->meal_counter = 0;
	man->is_eating = 0;
	man->left_fork = &table->forks[i];
	if (i == table->number_of_men - 1)
		man->right_fork = &table->forks[0];
	else
		man->right_fork = &table->forks[i + 1];
}

t_man	*create_men(t_table *table)
{
	int		i;
	t_man	*men;

	men = malloc(sizeof(t_man) * table->number_of_men);
	if (NULL == men)
		exit (EXIT_FAILURE);
	i = 0;
	while (i < table->number_of_men)
	{
		init_man(table, &men[i], i);
		pthread_create(&table->threads[i], NULL,
			man_life_cycle, (void *)&men[i]);
		i++;
	}
	return (men);
}

long long	get_timestamp(t_man *man)
{
	struct timeval	time;
	long long		res;

	gettimeofday(&time, NULL);
	res = (time.tv_sec * 1000 + time.tv_usec / 1000) - man->creation_time;
	return (res);
}

long long	get_creation_timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
