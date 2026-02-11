/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaure <mfaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 16:52:58 by mfaure            #+#    #+#             */
/*   Updated: 2026/02/11 21:12:28 by mfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaure <mfaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 16:52:58 by mfaure            #+#    #+#             */
/*   Updated: 2026/02/11 20:46:48 by mfaure           ###   ########.fr       */
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
	{
		philo->eat_nbr = ft_atoi(av[5]);
		philo->eat_count = 0;
	}
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

void *behavior(void *arg)
{
	int i = 0;
	t_philo *philo = (t_philo *)arg;

	while (philo->philo_array[i] != 0)
		i++;
	if (i - 1 < 0)
		pthread_mutex_lock(&philo->mutex[philo->nbr_of_philo - 1]);
	else {
		pthread_mutex_lock(&philo->mutex[i - 1]);
	}
	printf("philosopher %i as taken fork \n", i + 1);
	if (i + 1 == philo->nbr_of_philo)
		pthread_mutex_lock(&philo->mutex[0]);
	else {
		pthread_mutex_lock(&philo->mutex[i + 1]);
	}
	printf("philosopher %i as taken second fork \n", i + 1);
	printf("philosopher %i is eating\n", i + 1);
	philo->eat_count++;
	usleep(philo->time_to_eat);
	///if (philo->time_to_die == 0);
	///	{
	///		printf("philosopher %i died\n", philo->philo_array[i]);	
	///		exit;
	///	} a deplacer dans un autre process
	printf("philosopher %i is sleeping\n", i + 1);
	usleep(philo->time_to_sleep);
	printf("philosopher %i is thinking\n", i + 1);
	return (philo);
}

void loop(t_philo *philo)
{
	int i = 0;
	int tmp;
	while(i < philo->nbr_of_philo) {
		tmp = philo->philo_array[i];
		philo->philo_array[i] = 0;
		if (pthread_create(&philo->thread[i], NULL, behavior, philo) != 0 || philo->eat_count == philo->eat_nbr) {
    		perror("pthread_create() error");
			printf("error\n");
			exit(1);
  		}
		printf("lap\n");
		philo->philo_array[i] = tmp;
		i++;
	}
}

int main(int ac, char **av)
{
	int x;
	int y = 1;
	t_philo philo; //quelle form ?

	if (ac != 5 && ac != 6)
	{
		printf("invalid number of arguments\n");
		return (0);
	}
	while(av[y]) 
	{
		x = 0;
		while(av[y][x]) {
			if (!ft_isdigit(av[y][x]))
			{
				printf("invalid arguments : %c\n", av[y][x]);
				return (0);
			}
			x++;
		}
		y++;
	}
	fill_up_philo(&philo, av, ac);
	printf("filled up\n");
	loop(&philo);
	return (0);
}