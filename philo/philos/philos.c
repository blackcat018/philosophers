/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:15:14 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/08 23:01:41 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
int simulation_ended(t_data *data)
{
    int ended;
    pthread_mutex_lock(&data->end_mutex);
    ended = data->simulation_end;
    pthread_mutex_unlock(&data->end_mutex);
    return ended;
}


void *monitor_routine(void *arg)
{
    t_data *data = (t_data *)arg;
    int i;

    while (!simulation_ended(data))
    {
        usleep(1000);
        i = 0;
        while (i < data->philo_num)
        {
            pthread_mutex_lock(&data->meal_mutex);
            long last_meal = data->philos[i].last_meal_time;
            pthread_mutex_unlock(&data->meal_mutex);
            long current_time = get_time_in_ms(data);
            if (current_time - last_meal > data->time_to_die)
            {
                pthread_mutex_lock(&data->end_mutex);
                data->simulation_end = 1;
                pthread_mutex_unlock(&data->end_mutex);

                pthread_mutex_lock(&data->print_mutex);
                printf("%ld %d died\n", current_time, data->philos[i].id + 1);
                pthread_mutex_unlock(&data->print_mutex);
                return NULL;
            }
            i++;
        }
        if (data->must_eat_count > 0)
        {
            int all_full = 1;
            i = 0;
            while (i < data->philo_num)
            {
                pthread_mutex_lock(&data->meal_mutex);
                if (data->philos[i].meals_eaten < data->must_eat_count)
                    all_full = 0;
                pthread_mutex_unlock(&data->meal_mutex);
                i++;
            }
            if (all_full)
            {
                pthread_mutex_lock(&data->end_mutex);
                data->simulation_end = 1;
                pthread_mutex_unlock(&data->end_mutex);
                return NULL;
            }
        }
    }
    return NULL;
}

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    pthread_mutex_lock(&philo->data->meal_mutex);
    philo->last_meal_time = get_time_in_ms(philo->data);
    pthread_mutex_unlock(&philo->data->meal_mutex);
    if (philo->id % 2 == 0)
        usleep(1000);
    while (!simulation_ended(philo->data))
    {
        if (philo_take_forks(philo))
            break;
		philo_eat(philo);
        philo_sleep(philo, philo->data->time_to_sleep);
        philo_think(philo);
    }
    return NULL;
}


void philo_threading(t_philo *philo, t_data *data)
{
	int i = 0;
	while(i < data->philo_num)
	{
		pthread_create(&philo[i].thread,NULL,philo_routine,&philo[i]);
		i++;
	}
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
