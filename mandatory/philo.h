#ifndef PHILO_H
# define PHILO_H

# include "utils/libft/libft.h"
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}					t_fork;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;

	t_fork			*left_fork;
	t_fork			*right_fork;

	pthread_t		thread;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;

	long			start_time;
	int				simulation_end;

	t_fork			*forks;
	t_philo			*philos;

	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	end_mutex;
}					t_data;

void precise_sleep(long duration, t_data *data);
int check_input(char **av);
int simulation_ended(t_data *data);
void *monitor_routine(void *arg);
void *philo_routine(void *arg);

		//--------- data initialization --------- //

void				init_philos(t_data *data);
int					init_mutex(t_data *data);
int					init_data(t_data *data, char **av);
void				data_cleanup(t_data *data);


		//--------------- actions --------------- //

long  get_time_in_ms(t_data *data);
int print_output(t_philo *philo, char *str);
void philo_think(t_philo *philo);
int take_fork_even(t_philo *philo);
int take_fork_odd(t_philo *philo);
void one_philo_case(t_philo *philo);
int philo_take_forks(t_philo *philo);
void philo_eat(t_philo *philo);
void philo_put_forks(t_philo *philo);
void philo_sleep(t_philo *philo, long time);

		//-------- philosophers routien --------- //

void				*philo_routine(void *arg); /* needs to be done */
void				philo_threading(t_philo *philo, t_data *data);
void				wait_for_threads(t_philo *philo, t_data *data);


#endif