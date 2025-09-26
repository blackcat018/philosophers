/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:15:14 by moel-idr          #+#    #+#             */
/*   Updated: 2025/09/25 18:43:02 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void *philo_routien(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    // last_meal init
    get_time_in_ms(philo);

    while (1/* philosopher 3ayech / maklach */)
    {
        // 1. Think
        philo_think(philo);

        // 2. Take forks
        take_forks(philo);

        // 3. Eat
        eat(philo);

        // 4. Release forks
        put_forks(philo);

        // 5. Sleep
        philo_sleep(philo);
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