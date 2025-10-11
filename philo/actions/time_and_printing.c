/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_and_printing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:10:53 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/11 16:45:51 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long get_time_in_ms(t_data *data)
{
    struct timeval now;
    gettimeofday(&now, NULL);
    return ((now.tv_sec - data->start_time_tv.tv_sec) * 1000
            + (now.tv_usec - data->start_time_tv.tv_usec) / 1000);
}

int print_output(t_philo *philo, char *str)
{
    if(!philo || !str)
        return(0);
    
    pthread_mutex_lock(&philo->data->print_mutex);
    pthread_mutex_lock(&philo->data->end_mutex);
    
    if(philo->data->simulation_end)
    {
        pthread_mutex_unlock(&philo->data->end_mutex);
        pthread_mutex_unlock(&philo->data->print_mutex);
        return(1);
    }
    
    printf("%ld %d %s\n", get_time_in_ms(philo->data), philo->id + 1, str);
    pthread_mutex_unlock(&philo->data->end_mutex);
    pthread_mutex_unlock(&philo->data->print_mutex);
    return(0);
}