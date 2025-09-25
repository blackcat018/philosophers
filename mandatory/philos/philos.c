/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:15:14 by moel-idr          #+#    #+#             */
/*   Updated: 2025/09/25 18:37:58 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void *philo_routine(void *arg)
{
	t_philo *philo = (t_philo*)arg;
	
	return(NULL);
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