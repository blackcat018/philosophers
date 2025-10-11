/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:23:32 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/11 13:16:33 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void philo_threading(t_philo *philo, t_data *data)
{
	int i = 0;
	while(i < data->philo_num)
	{
		pthread_create(&philo[i].thread,NULL,philo_routine,&philo[i]);
		i++;
	}
}

int simulation_ended(t_data *data)
{
    int ended;
    pthread_mutex_lock(&data->end_mutex);
    ended = data->simulation_end;
    pthread_mutex_unlock(&data->end_mutex);
    return ended;
}

void wait_for_threads(t_philo *philo, t_data *data)
{
	int i = 0;
	while(i < data->philo_num)
	{
		pthread_join(philo[i].thread,NULL);
		i++;
	}
}

int main(int ac, char **av)
{
    t_data data;
	int i;
    pthread_t monitor;
    
	i = 0;
    if (ac < 5 || ac > 6)
        return 1;
    if (check_input(av) != 1)
    {
        printf("Error: Invalid input format\n");
        return 1;
    }
    if (init_data(&data, av) == -1)
    {
        printf("Error: Invalid arguments or initialization failed\n");
        return 1;
    }
    data.start_time = get_time_in_ms(&data);
    while( i < data.philo_num)
	{
        data.philos[i].last_meal_time = data.start_time;
		i++;
    }
    philo_threading(data.philos, &data);
    pthread_create(&monitor, NULL, monitor_routine, &data);
    wait_for_threads(data.philos, &data);
    pthread_join(monitor, NULL);
    data_cleanup(&data);
    return 0;
}
