/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirony <dirony@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 15:59:17 by dirony            #+#    #+#             */
/*   Updated: 2022/01/22 15:44:50 by dirony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor_threads(t_table *table, t_man *men)
{
	int	i;
	int	flag;

	flag = 1;
	while (flag)
	{
		i = 0;
		while (i < table->number_of_men && flag)
		{
			if (get_timestamp(&men[i]) - men[i].last_meal_time
				> men[i].time_to_die && !men[i].is_eating)
			{
				pthread_mutex_lock(table->speaker);
				printf("%lld %d died\n", get_timestamp(&men[i]), men[i].number);
				flag = 0;
			}
			if (table->number_of_meals != -1
				&& men[i].meal_counter >= table->number_of_meals)
			{
				if (check_everyone_has_eaten(table, men))
					flag = 0;
			}
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	t_table		table;
	t_man		*men;

	if (!parse_args(argc, argv, &table))
		return (0);
	create_table(&table);
	table.creation_time = get_creation_timestamp();
	men = create_men(&table);
	monitor_threads(&table, men);
	pthread_mutex_unlock(table.speaker);
	clear_table(&table);
	return (0);
}
