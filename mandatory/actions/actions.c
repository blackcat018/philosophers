/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:10:53 by moel-idr          #+#    #+#             */
/*   Updated: 2025/09/26 02:09:19 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


long  get_time_in_ms(t_philo *philo)
{
	struct timeval time;
	gettimeofday(&time,NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - philo->data->start_time);
}

int print_output(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->end_mutex);
	if(philo->data->simulation_end)
	{
		pthread_mutex_unlock(&philo->data->end_mutex);
		return(1);
	}
	pthread_mutex_unlock(&philo->data->end_mutex);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d %s\n", get_time_in_ms(philo), philo->id + 1, str);
	pthread_mutex_unlock(&philo->data->print_mutex);
	return(0);
}

void philo_think(t_philo *philo)
{
	if(print_output(philo,"is thinking") == 1)
		return;
	usleep(50);	
}

int take_fork_even(t_philo *philo)
{
	if(pthread_mutex_lock(&philo->left_fork->mutex) != 0)
	{
		printf("error!\n");
		return(-1);
	}
	print_output(philo,"has taken fork");
	pthread_mutex_lock(&philo->data->end_mutex);
	if(philo->data->simulation_end)
	{
		pthread_mutex_unlock(&philo->left_fork->mutex);
		return(-1);
	}
	pthread_mutex_unlock(&philo->data->end_mutex);
	if(pthread_mutex_lock(&philo->right_fork->mutex) != 0)
	{
		printf("error!\n");
		pthread_mutex_unlock(&philo->left_fork->mutex);
		return(-1);
	}
	if(print_output(philo,"has taken fork") == 1)
	{
		pthread_mutex_unlock(&philo->left_fork->mutex);
		pthread_mutex_unlock(&philo->right_fork->mutex);
		return(-1);
	}
	return(1);
}

int take_fork_odd(t_philo *philo)
{
	if(pthread_mutex_lock(&philo->right_fork->mutex) != 0)
	{
		printf("error!\n");
		return (-1);
	}
	print_output(philo,"has taken fork");
	pthread_mutex_lock(&philo->data->end_mutex);
	if(philo->data->simulation_end)
	{
		pthread_mutex_unlock(&philo->right_fork->mutex);
		return (-1);
	}
	pthread_mutex_unlock(&philo->data->end_mutex);
	if(pthread_mutex_lock(&philo->left_fork->mutex) != 0)
	{
		printf("error!\n");
		pthread_mutex_unlock(&philo->right_fork->mutex);
		return (-1);
	}
	if(print_output(philo,"has taken fork") == 1)
	{
		pthread_mutex_unlock(&philo->left_fork->mutex);
		pthread_mutex_unlock(&philo->right_fork->mutex);
		return (-1);
	}
	return(1);
}

void one_philo_case(t_philo *philo)
{
		if(pthread_mutex_lock(&philo->right_fork->mutex) != 0)
		{
			printf("error!\n");
			return;
		}
		print_output(philo,"has taken fork");
		while (!philo->data->simulation_end)
    		usleep(10000);
		pthread_mutex_unlock(&philo->right_fork->mutex);
		return;
}

void philo_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->end_mutex);
	if(philo->data->simulation_end)
	{
		pthread_mutex_unlock(&philo->data->end_mutex);
		return;
	}
	pthread_mutex_unlock(&philo->data->end_mutex);
	if(philo->data->philo_num == 1)
	{
		one_philo_case(philo);
		return;
	}
	if((philo->id % 2) == 0)
	{
		if(take_fork_even(philo) == -1)
			return;
	}
	else
	{
		if(take_fork_odd(philo) == -1)
			return;
	}
}

void philo_eat(t_philo *philo)
{
	
}

void philo_put_forks(t_philo *philo)
{
	
}

void philo_sleep(t_philo *philo)
{
	
}