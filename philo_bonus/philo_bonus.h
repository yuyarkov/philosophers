/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirony <dirony@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 16:00:16 by dirony            #+#    #+#             */
/*   Updated: 2022/01/29 13:36:01 by dirony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <signal.h>

# define SEM_FORKS "/sem_forks"
# define SEM_SPEAKER "/sem_speaker"
# define PHILOSOPHER_DIED 0
# define REACHED_TIMES_TO_EAT 1
# define TAKEN_FORK 100
# define EATING 101
# define SLEEPING 102
# define THINKING 103
# define DIED 104

typedef struct s_man
{
	pid_t		pid;
	pthread_t	monitoring;
	int			number_of_men;
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
	sem_t		*forks;
	sem_t		*speaker;
}	t_man;

typedef struct s_table
{
	int			number_of_men;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			number_of_meals;
	long long	creation_time;
	sem_t		*forks;
	sem_t		*speaker;
}	t_table;

int			ft_isdigit(char ch);
int			ft_atoi(const char *str);
int			ft_putnbr(long long n);
void		ft_putstr(char *s);

int			check_args(int argc, char **argv);
int			parse_args(int argc, char **argv, t_table *table);

void		create_table(t_table *table);
t_man		*create_men(t_table *table);
long long	get_creation_timestamp(void);
void		ft_usleep(int microsecs);
void		print_status(t_man *man, int status);

void		*man_life_cycle(t_man *man);
long long	get_timestamp(t_man *man);
void		get_fork_and_eat(t_man *man);
void		sleep_and_think(t_man *man);
void		*monitor_process(void *men);
void		clear_table(t_table *table, t_man *men);

#endif