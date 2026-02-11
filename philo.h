/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaure <mfaure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 19:04:00 by mfaure            #+#    #+#             */
/*   Updated: 2026/02/11 21:12:44 by mfaure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H


# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_philo
{
	int		nbr_of_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		eat_nbr;
	int		eat_count;
	int		*philo_array;
	pthread_mutex_t *mutex;
	pthread_t *thread;
}			t_philo;

int	ft_isdigit(int c);
int	ft_atoi(const char *nptr);

#endif