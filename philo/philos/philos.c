/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:15:14 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/11 13:18:17 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


int check_philosopher_death(t_data *data)
{
    int i;
    long last_meal;
    long current_time;

    i = 0;
    while (i < data->philo_num)
    {
        pthread_mutex_lock(&data->meal_mutex);
        last_meal = data->philos[i].last_meal_time;
        pthread_mutex_unlock(&data->meal_mutex);
        current_time = get_time_in_ms(data);
        if (current_time - last_meal > data->time_to_die)
        {
            pthread_mutex_lock(&data->end_mutex);
            data->simulation_end = 1;
            pthread_mutex_unlock(&data->end_mutex);
            pthread_mutex_lock(&data->print_mutex);
            printf("%ld %d died\n", current_time, data->philos[i].id + 1);
            pthread_mutex_unlock(&data->print_mutex);
            return 1;
        }
        i++;
    }
    return 0;
}

int check_all_philosophers_full(t_data *data)
{
    int i;
    int all_full;

    if (data->must_eat_count <= 0)
        return 0;
    
    all_full = 1;
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
        return 1;
    }
    return 0;
}

void *monitor_routine(void *arg)
{
    t_data *data = (t_data *)arg;

    while (!simulation_ended(data))
    {
        usleep(1000);
        
        if (check_philosopher_death(data))
            return NULL;
        
        if (check_all_philosophers_full(data))
            return NULL;
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
