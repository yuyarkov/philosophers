/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirony <dirony@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 15:22:48 by dirony            #+#    #+#             */
/*   Updated: 2022/01/29 13:36:19 by dirony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*man_life_cycle(t_man *man)
{
	int		flag;

	pthread_create(&man->monitoring, NULL, monitor_process, (void *)man);
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
	exit(REACHED_TIMES_TO_EAT);
}

void	get_fork_and_eat(t_man *man)
{
	sem_wait(man->forks);
	sem_wait(man->forks);
	man->is_eating = 1;
	man->last_meal_time = get_timestamp(man);
	print_status(man, TAKEN_FORK);
	ft_usleep(man->time_to_eat * 1000);
	man->meal_counter++;
	sem_post(man->forks);
	sem_post(man->forks);
	man->is_eating = 0;
}

void	sleep_and_think(t_man *man)
{
	if (man->number_of_meals == -1 || man->meal_counter < man->number_of_meals)
	{
		print_status(man, SLEEPING);
		ft_usleep(man->time_to_sleep * 1000);
		print_status(man, THINKING);
	}
}

void	clear_table(t_table *table, t_man *men)
{
	int	i;

	i = 0;
	while (i < table->number_of_men)
	{
		kill(men[i].pid, SIGTERM);
		i++;
	}
	sem_close(table->speaker);
	sem_close(table->forks);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_SPEAKER);
	free(men);
}

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}
