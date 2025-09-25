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

		//--------- data initialization --------- //

void				init_philos(t_data *data);
int					init_mutex(t_data *data);
int					init_data(t_data *data, char **av, int ac);
void				data_cleanup(t_data *data);

		//-------- philosophers routien --------- //

void				*philo_routine(void *arg); /* needs to be done */
void				philo_threading(t_philo *philo, t_data *data);
void				wait_for_threads(t_philo *philo, t_data *data);


#endif