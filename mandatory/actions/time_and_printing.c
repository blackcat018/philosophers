/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_and_printing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:10:53 by moel-idr          #+#    #+#             */
/*   Updated: 2025/09/26 21:21:43 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long  get_time_in_ms(t_data *data)
{
	struct timeval time;
	gettimeofday(&time,NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - data->start_time);
}

int print_output(t_philo *philo, char *str)
{
	if(!philo || !str)
		return(0);
	pthread_mutex_lock(&philo->data->end_mutex);
	if(philo->data->simulation_end)
	{
		pthread_mutex_unlock(&philo->data->end_mutex);
		return(1);
	}
	pthread_mutex_unlock(&philo->data->end_mutex);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d %s\n", get_time_in_ms(philo->data), philo->id + 1, str);
	pthread_mutex_unlock(&philo->data->print_mutex);
	return(0);
}