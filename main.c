/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaure <mfaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 16:52:58 by mfaure            #+#    #+#             */
/*   Updated: 2026/02/02 16:56:19 by mfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void fill_up_philo(t_philo *philo, char **av, int ac)
{
	int i;

	philo->nbr_of_philo = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		philo->eat_nbr = ft_atoi(av[5]);
	philo->philo_array = malloc(sizeof(int) * philo->nbr_of_philo);
	philo->mutex = malloc(sizeof(pthread_mutex_t) * philo->nbr_of_philo);
	philo->thread = malloc(sizeof(pthread_t) * philo->nbr_of_philo);
	i = 0;
	while(i < philo->nbr_of_philo)
	{
		philo->philo_array[i] = i + 1;
		i++;
	}
	i = 0;
	while(i < philo->nbr_of_philo)
	{
		pthread_mutex_init(&philo->mutex[i], NULL);
		i++;
	}
}

void *behavior(t_philo *philo)
{
		pthread_mutex_lock(philo->mutex);
		printf("philosopher %i as taken fork \n", philo->philo_array[i]);
		pthread_mutex_lock(philo->mutex);
		printf("philosopher %i as taken fork \n", philo->philo_array[i]);
		printf("philosopher %i is eating\n", philo->philo_array[i]);
		while(philo->time_to_eat > 0);
		///if (philo->time_to_die == 0);
		///	{
		///		printf("philosopher %i died\n", philo->philo_array[i]);	
		///		exit;
		///	} a deplacer dans un autre process
	printf("philosopher %i is sleeping\n", philo->philo_array[i]);
	while(philo->time_to_sleep != 0);
	printf("philosopher %i is thinking\n", philo->philo_array[i]);	
}

void loop(t_philo *philo)
{
	int i = 0;
	while(i < philo->nbr_of_philo)
		pthread_create(philo->thread[i], NULL, behavior(), philo);
}

int main(int ac, char **av)
{
	int x = 0;
	int y = 0;
	t_philo **philo; //?

	if (ac != 5 && ac != 6)
	{
		printf("invalid number of arguments\n");
		return (0);
	}
	while(av[y]) 
	{
		while(av[x]) {
			if (!ft_isdigit(av[y][x]))
			{
				printf("invalid arguments\n");
				return (0);
			}
			x++;
		}
		y++;
	}
	fill_up_philo(&philo, av, ac);
	loop(&philo);
	return (0);
}