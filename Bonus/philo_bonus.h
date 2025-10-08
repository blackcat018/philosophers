#ifndef PHILO_H
# define PHILO_H

# include "../mandatory/utils/libft/libft.h"
# include <limits.h>
#include <signal.h> 
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <sys/types.h>
# include <fcntl.h>
#include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>


typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;

	pid_t				pid;
	struct s_data	*data;
	pthread_t		die;
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

	t_philo			*philos;

	sem_t			*sem_forks;  
	sem_t			*sem_print;
	sem_t			*sem_meal;
	sem_t			*sem_stop;
}					t_data;

int check_input(char **av);
void *monitoring(void *arg);

		//--------- data initialization --------- //

void init_philos(t_data *data);
int					init_data(t_data *data, char **av);


		//--------------- actions --------------- //

long get_time_in_ms(t_data *data);
void print_output(t_philo *philo, char *str);
void philo_eat(t_philo *philo);
void forking(t_philo *philo);

		//-------- philosophers routien --------- //

void				philo_routine(void *arg); /* needs to be done */
void wait_forking(t_philo *philo, long time);
void cleanup(t_philo *philo);

#endif