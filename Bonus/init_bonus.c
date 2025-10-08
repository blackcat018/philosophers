/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 06:51:45 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/08 03:46:49 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo_bonus.h"

int init_data(t_data *data, char **av)
{
    data->philo_num = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
    if (av[5])
        data->must_eat_count = ft_atoi(av[5]);
    else 
        data->must_eat_count = -1;
    if (data->philo_num <= 0 || data->time_to_die <= 0 || 
        data->time_to_eat <= 0 || data->time_to_sleep <= 0 || 
        (data->must_eat_count <= 0 && data->must_eat_count != -1))
        return -1;
    data->start_time = get_time_in_ms(data);
    data->simulation_end = 0;
    data->philos = malloc(sizeof(t_philo) * data->philo_num);
    if (!data->philos)
        return -1;
    init_philos(data);
    return 1;
}

void init_philos(t_data *data)
{
    int i;

    i = 0;
    while(i < data->philo_num)
    {
        data->philos[i].id = i;
        data->philos[i].last_meal_time = data->start_time;
        data->philos[i].meals_eaten = 0;
        data->philos[i].data = data;
        i++;
    }
}
