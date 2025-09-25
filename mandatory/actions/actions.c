/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:10:53 by moel-idr          #+#    #+#             */
/*   Updated: 2025/09/25 18:38:16 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


void  get_time_in_ms(t_philo *philo)
{
	struct timeval time;
	gettimeofday(&time,NULL);
	philo->last_meal_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
}
