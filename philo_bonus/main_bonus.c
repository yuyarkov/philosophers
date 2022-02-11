/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirony <dirony@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 15:59:17 by dirony            #+#    #+#             */
/*   Updated: 2022/01/29 13:43:23 by dirony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_status(t_man *man, int status)
{
	sem_wait(man->speaker);
	ft_putnbr(get_timestamp(man));
	ft_putstr(" ");
	ft_putnbr(man->number);
	if (status == TAKEN_FORK)
	{
		ft_putstr(" has taken a fork\n");
		ft_putnbr(get_timestamp(man));
		ft_putstr(" ");
		ft_putnbr(man->number);
		ft_putstr(" is eating\n");
	}
	if (status == SLEEPING)
		ft_putstr(" is sleeping\n");
	if (status == THINKING)
		ft_putstr(" is thinking\n");
	if (status == DIED)
		ft_putstr(" died\n");
	sem_post(man->speaker);
}

void	*monitor_process(void *man_info)
{
	t_man	*man;
	int		flag;

	man = (t_man *)man_info;
	flag = 1;
	while (flag)
	{
		if (get_timestamp(man) - man->last_meal_time
			> man->time_to_die && !man->is_eating)
		{
			sem_wait(man->speaker);
			printf("%lld %d died\n", get_timestamp(man), man->number);
			exit(PHILOSOPHER_DIED);
		}
		if (man->number_of_meals != -1
			&& man->meal_counter >= man->number_of_meals)
			exit(REACHED_TIMES_TO_EAT);
		ft_usleep(500);
	}
	return (NULL);
}

void	ft_usleep(int microsecs)
{
	long long	stamp1;
	long long	wait;

	wait = (long long) microsecs * 0.9f;
	stamp1 = get_creation_timestamp();
	usleep(wait);
	while (get_creation_timestamp() - stamp1 < microsecs / 1000)
		usleep(100);
}

int	main(int argc, char **argv)
{
	t_table		table;
	t_man		*men;
	int			signal;
	int			i;

	if (!parse_args(argc, argv, &table))
		return (0);
	create_table(&table);
	table.creation_time = get_creation_timestamp();
	men = create_men(&table);
	i = 0;
	while (i < table.number_of_men)
	{
		waitpid(-1, &signal, 0);
		if (signal == PHILOSOPHER_DIED)
		{
			clear_table(&table, men);
			return (0);
		}
		i++;
	}
	clear_table(&table, men);
	return (0);
}
