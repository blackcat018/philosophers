/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:10:53 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/08 18:29:56 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int take_fork_even(t_philo *philo)
{
    if(pthread_mutex_lock(&philo->left_fork->mutex) != 0)
        return -1;
    
    if(print_output(philo,"has taken fork") == 1)
    {
        pthread_mutex_unlock(&philo->left_fork->mutex);
        return -1;
    }
    
    if(pthread_mutex_lock(&philo->right_fork->mutex) != 0)
    {
        pthread_mutex_unlock(&philo->left_fork->mutex);
        return -1;
    }
    
    if(print_output(philo,"has taken fork") == 1)
    {
        pthread_mutex_unlock(&philo->left_fork->mutex);
        pthread_mutex_unlock(&philo->right_fork->mutex);
        return -1;
    }
    return 1;
}

int take_fork_odd(t_philo *philo)
{
    if(pthread_mutex_lock(&philo->right_fork->mutex) != 0)
        return -1;
    
    if(print_output(philo,"has taken fork") == 1)
    {
        pthread_mutex_unlock(&philo->right_fork->mutex);
        return -1;
    }
    
    if(pthread_mutex_lock(&philo->left_fork->mutex) != 0)
    {
        pthread_mutex_unlock(&philo->right_fork->mutex);
        return -1;
    }
    
    if(print_output(philo,"has taken fork") == 1)
    {
        pthread_mutex_unlock(&philo->left_fork->mutex);
        pthread_mutex_unlock(&philo->right_fork->mutex);
        return -1;
    }
    return 1;
}

void one_philo_case(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_mutex);
philo->last_meal_time = get_time_in_ms(philo->data);
pthread_mutex_unlock(&philo->data->meal_mutex);
		if(pthread_mutex_lock(&philo->right_fork->mutex) != 0)
		{
			printf("error!\n");
			return;
		}
		print_output(philo,"has taken fork");
		while (!philo->data->simulation_end)
    		usleep(1000);
		pthread_mutex_unlock(&philo->right_fork->mutex);
		return;
}
