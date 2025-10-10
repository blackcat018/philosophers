/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:15:14 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/10 18:28:58 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void *monitoring(void *arg)
{
    t_philo *philo;
    long current_time;
    long last_meal;

    philo = (t_philo*)arg;
    while(1)
    {
        usleep(1000);
        sem_wait(philo->data->sem_meal);
        current_time = get_time_in_ms(philo->data);
        last_meal = philo->last_meal_time;
        sem_post(philo->data->sem_meal);
        
        if(current_time - last_meal > philo->data->time_to_die)
        {
            sem_wait(philo->data->sem_print);
            printf("%ld %d died\n", current_time - philo->data->start_time, philo->id + 1);
            exit(1);
        }
    }
    return(NULL);
}

void precise_usleep(t_data *data,long microseconds)
{
    long start_time = get_time_in_ms(data) * 1000;
    long current_time;
    
    while (1)
    {
        current_time = get_time_in_ms(data) * 1000;
        if (current_time - start_time >= microseconds)
            break;
        usleep(100);
    }
}

void philo_routine(t_philo *philo)
{
    sem_wait(philo->data->sem_star);
    pthread_t monitor_thread;

    sem_wait(philo->data->sem_star);
    philo->data->start_time = get_time_in_ms(philo->data);
    philo->last_meal_time = philo->data->start_time;

    pthread_create(&monitor_thread, NULL, monitoring, philo);
    pthread_detach(monitor_thread);    
    if (philo->id % 2 == 0)
        usleep(1000);
    while(1)
    {
        philo_eat(philo);        
        if (philo->data->must_eat_count != -1 && 
            philo->meals_eaten >= philo->data->must_eat_count)
            exit(0);
            
        print_output(philo, "is sleeping");
        precise_usleep(philo->data, philo->data->time_to_sleep * 1000);
        print_output(philo, "is thinking");
    }
}
