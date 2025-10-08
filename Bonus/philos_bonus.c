/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:15:14 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/08 03:45:31 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void *monitoring(void *arg)
{
    t_philo *philo;
    long diff;

    philo = (t_philo*)arg;
    while(1)
    {
        usleep(1000);
        sem_wait(philo->data->sem_meal);
        diff = get_time_in_ms(philo->data) - philo->last_meal_time;
        if(diff >= philo->data->time_to_die)
        {
            sem_post(philo->data->sem_meal);
            sem_wait(philo->data->sem_print);
            ft_putnbr_fd(get_time_in_ms(philo->data) - philo->data->start_time, 1);
            ft_putstr_fd(" ", 1);
            ft_putnbr_fd(philo->id + 1, 1);
            ft_putstr_fd(" died\n", 1);
            exit(1);
        }
        sem_post(philo->data->sem_meal);
    }
    return(NULL);
}

void philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo*)arg;
    pthread_create(&philo->die, NULL, monitoring, philo);
    pthread_detach(philo->die);
    if((philo->id % 2) == 0)
        usleep(philo->data->time_to_sleep * 1000);
    while(1)
    {
        philo_eat(philo);
        print_output(philo, "is sleeping");
        usleep(philo->data->time_to_sleep * 1000);
        print_output(philo, "is thinking");
    }
    return;
}
