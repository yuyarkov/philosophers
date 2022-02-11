/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirony <dirony@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 20:26:14 by dirony            #+#    #+#             */
/*   Updated: 2022/01/29 13:37:55 by dirony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	create_table(t_table *table)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_SPEAKER);
	table->forks = sem_open(SEM_FORKS, O_CREAT, 777, table->number_of_men);
	if (table->forks == SEM_FAILED)
	{
		perror("sem_open failed\n");
		exit(EXIT_FAILURE);
	}
	table->speaker = sem_open(SEM_SPEAKER, O_CREAT, 777, 1);
	if (table->speaker == SEM_FAILED)
	{
		perror("sem_open failed\n");
		exit(EXIT_FAILURE);
	}
}

void	init_man(t_table *table, t_man *man, int i)
{
	man->number = i + 1;
	man->number_of_men = table->number_of_men;
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
	man->forks = table->forks;
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
		men[i].pid = fork();
		if (men[i].pid == 0)
			man_life_cycle(&men[i]);
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
