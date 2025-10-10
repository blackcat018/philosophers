/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 06:50:47 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/10 18:26:49 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int main(int ac, char **av)
{
    t_data data;
	int i;
    
	i = 0;
    if (ac < 5 || ac > 6)
        return 1;
    if (check_input(av) != 1)
        return (printf("Error: Invalid input format\n"), 1);
    if (init_data(&data, av) == -1)
    {
        printf("Error: Invalid arguments or initialization failed\n");
        return 1;
    }
    sem_unlink("/sem_print");
    sem_unlink("/sem_forks");
    sem_unlink("/sem_meal");
    sem_unlink("/sem_start");
    data.sem_print = sem_open("/sem_print", O_CREAT, 0777, 1);
    data.sem_forks = sem_open("/sem_forks", O_CREAT, 0777, data.philo_num);
    data.sem_meal  = sem_open("/sem_meal",  O_CREAT, 0777, 1);
    data.sem_star = sem_open("/sem_start", O_CREAT, 0777, 0);
    forking(data.philos);
    data.start_time = get_time_in_ms(&data);
    while(i < data.philo_num)
    {
         sem_post(data.sem_star);
         i++;
    }
    wait_forking(data.philos, data.time_to_die);

    return 0;
}
