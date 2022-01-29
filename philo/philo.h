/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirony <dirony@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 16:00:16 by dirony            #+#    #+#             */
/*   Updated: 2022/01/22 15:43:40 by dirony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef pthread_mutex_t	t_mutex;

typedef struct s_man
{
	int			number;
	long long	creation_time;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			number_of_meals;
	int			first_meal;
	int			is_eating;
	int			meal_counter;
	int			last_meal_time;
	t_mutex		*left_fork;
	t_mutex		*right_fork;
	t_mutex		*speaker;
}	t_man;

typedef struct s_table
{
	int			number_of_men;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			number_of_meals;
	long long	creation_time;
	t_mutex		*forks;
	t_mutex		*speaker;
	pthread_t	*threads;
}	t_table;

int			ft_isdigit(char ch);
int			ft_atoi(const char *str);

int			check_args(int argc, char **argv);
int			parse_args(int argc, char **argv, t_table *table);

void		create_table(t_table *table);
t_man		*create_men(t_table *table);
long long	get_creation_timestamp(void);

void		*man_life_cycle(void *man_info);
long long	get_timestamp(t_man *man);
void		get_fork_and_eat(t_man *man);
void		sleep_and_think(t_man *man);
int			check_everyone_has_eaten(t_table *table, t_man *men);
void		clear_table(t_table *table);

#endif