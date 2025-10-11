/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:10:53 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/08 22:36:02 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void philo_think(t_philo *philo)
{
    if(print_output(philo,"is thinking") == 1)
        return;
    usleep(500);
}

int philo_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->end_mutex);
	if(philo->data->simulation_end)
	{
		pthread_mutex_unlock(&philo->data->end_mutex);
		return(1);
	}
	pthread_mutex_unlock(&philo->data->end_mutex);
	if(philo->data->philo_num == 1)
	{
		one_philo_case(philo);
		return(1);
	}
	if(take_fork_even(philo) == -1)
			return(1);
	return(0);
}
void philo_put_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
}

void precise_sleep(long duration, t_data *data)
{
    long start = get_time_in_ms(data);
    while(get_time_in_ms(data) - start < duration)
	{
        if(data->simulation_end)
			return;
    }
}
void philo_sleep(t_philo *philo, long time)
{
    long start = get_time_in_ms(philo->data);
    if(print_output(philo, "is sleeping") == 1)
        return;
    while(get_time_in_ms(philo->data) - start < time)
    {
        pthread_mutex_lock(&philo->data->end_mutex);
        if(philo->data->simulation_end)
        {
            pthread_mutex_unlock(&philo->data->end_mutex);
            return;
        }
        pthread_mutex_unlock(&philo->data->end_mutex);
    }
}

void philo_eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->meal_mutex);
    philo->last_meal_time = get_time_in_ms(philo->data);
    pthread_mutex_unlock(&philo->data->meal_mutex);
    if (print_output(philo, "is eating") == 1)
    {
        philo_put_forks(philo);
        return;
    }
    pthread_mutex_lock(&philo->data->meal_mutex);
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->data->meal_mutex);
    precise_sleep(philo->data->time_to_eat, philo->data);
    philo_put_forks(philo);
}

