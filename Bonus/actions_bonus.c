/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:10:53 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/08 01:05:12 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long get_time_in_ms(t_data *data)
{
	(void)data;
    struct timeval time;
    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void print_output(t_philo *philo, char *str)
{
    long relative_time;
    
    sem_wait(philo->data->sem_print);
    relative_time = get_time_in_ms(philo->data) - philo->data->start_time;
    printf("%ld %d %s\n", relative_time, philo->id + 1, str);
    sem_post(philo->data->sem_print);
}


void philo_eat(t_philo *philo)
{
    sem_wait(philo->data->sem_forks);
    print_output(philo,"has taken a fork");
	sem_wait(philo->data->sem_forks);
	print_output(philo,"has taken a fork");
	sem_wait(philo->data->sem_meal);
	philo->last_meal_time = get_time_in_ms(philo->data);
	sem_post(philo->data->sem_meal);
	print_output(philo,"is eating");
	philo->meals_eaten++;
	usleep(philo->data->time_to_eat * 1000);
	sem_post(philo->data->sem_forks);
	sem_post(philo->data->sem_forks);
}
void cleanup(t_philo *philo)
{
	sem_close(philo->data->sem_print);
	sem_close(philo->data->sem_forks);
	sem_close(philo->data->sem_meal);

	sem_unlink("/sem_print");
	sem_unlink("/sem_forks");
	sem_unlink("/sem_meal");
}

void forking(t_philo *philo)
{
    int i;
	pid_t pid;

	i = 0;
	while(i < philo->data->philo_num)
	{
		pid = fork();
		fflush(stdout);
		if(pid == 0)
		{
			philo_routine((void *)&philo[i]);
			exit(0);
		}
		else if(pid > 0)
		{
			philo[i].pid = pid;
			i++;
		}
		else
		{
			cleanup(philo);
			perror("fork");
			exit(1);
		}
			
	}
}
void wait_forking(t_philo *philo, long time)
{
	int stat;
	int i;

	i = 0;
	(void)time;
	wait(&stat);
	while(i < philo->data->philo_num)
	{
		kill(philo[i].pid,SIGKILL);
		i++;
	}
	i = 0;
	while(i < philo->data->philo_num)
	{
		waitpid(philo[i].pid,&stat,0);
		i++;
	}
	cleanup(philo);
	exit(0);
}
