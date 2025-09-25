/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:10:57 by moel-idr          #+#    #+#             */
/*   Updated: 2025/09/25 17:10:58 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void init_philos(t_data *data)
{
    int i;

    i = 0;
    while(i < data->philo_num)
    {
        data->philos[i].id = i;
        data->philos[i].last_meal_time = 0;
        data->philos[i].meals_eaten = 0;
        data->philos[i].data = data;
        data->philos[i].left_fork = &data->forks[i];
        data->philos[i].right_fork = &data->forks[(i + 1) % data->philo_num];
        
        i++;
    }
}

int init_mutex(t_data *data)
{
	int i;

	i = 0;
	if(pthread_mutex_init(&data->print_mutex,NULL) != 0)
		return(-1);
	if(pthread_mutex_init(&data->meal_mutex,NULL) != 0)
		return(-1);
	if(pthread_mutex_init(&data->end_mutex,NULL) != 0)
		return(-1);	
	while(i < data->philo_num)
	{
		if(pthread_mutex_init(&data->forks[i].mutex,NULL))
			return(-1);
		i++;
	}
	return(1);
}

int init_data(t_data *data, char **av, int ac)
{
    data->philo_num = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
    if (av[5])
        data->must_eat_count = ft_atoi(av[5]);
    else 
        data->must_eat_count = -1;
    if (data->philo_num <= 0 || data->time_to_die <= 0 || 
        data->time_to_eat <= 0 || data->time_to_sleep <= 0 || 
        (data->must_eat_count <= 0 && data->must_eat_count != -1))
        return -1;
    data->start_time = 0;
    data->simulation_end = 0;
    data->forks = malloc(sizeof(t_fork) * data->philo_num);
    data->philos = malloc(sizeof(t_philo) * data->philo_num);
    if (!data->forks || !data->philos)
        return(-1);
    if (init_mutex(data) != 1)
        return(-1);
    
    init_philos(data);
    
    return(1);
}

void data_cleanup(t_data *data)
{
	int i;

	i = 0;
	pthread_mutex_destroy(&data->end_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	while(i < data->philo_num)
	{
		pthread_mutex_destroy(&data->forks[i].mutex);
		i++;
	}
	if(data->forks)
		free(data->forks);
	if(data->philos)
		free(data->philos);
}
