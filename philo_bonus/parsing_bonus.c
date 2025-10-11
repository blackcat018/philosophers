/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:10:59 by moel-idr          #+#    #+#             */
/*   Updated: 2025/10/11 06:37:55 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int check_if_number(char **av)
{
	 int i = 1;
	 int j;
	 while(av[i])
	 {
		j = 0;
		while(av[i][j])
		{
			if (ft_isdigit(av[i][j]) != 1)
			{
				if(av[i][j] == '+' && 
					av[i][j - 1] != '+' && av[i][j+1])
				{
					j++;
					continue;
				}
				else
					return(-1);
			}
			j++;
		}
		i++;
	 }
	 return(1);
}

int check_input(char **av)
{
	int i = 0;
	long n;
	if(check_if_number(av) != 1)
		return(-1);
	while(av[i])
	{
		n = (long)ft_atoi(av[i]);
		if(n == -1)
		{
			return(-1);
		}
			
		i++;
	}
	return(1);
}
