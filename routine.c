/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoskun <scoskun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 13:13:13 by scoskun           #+#    #+#             */
/*   Updated: 2022/07/07 17:26:48 by scoskun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	go_kill(t_philo *ph)
{
	pthread_mutex_lock(ph->lock);
	if (!*ph->is_ph_dead)
	{
		printf("%ld %d is died\n", ph->start_time, ph->id);
		*ph->is_ph_dead = 1;
	}
	pthread_mutex_unlock(ph->lock);
}

void	*routine(t_philo *philo)
{
	if (philo->nbr_philo == 1)
	{
		gettime(philo);
		printf("%ld %d has taken a fork\n", philo->start_time, philo->id);
		*philo->is_ph_dead = 1;
		ft_usleep(philo, philo->time_to_die);
		printf("%ld %d is died\n", philo->time_to_die, philo->id);
		return (NULL);
	}
	while (1)
	{
		take_fork(philo);
		eat(philo);
		if (philo->hm_eat == philo->eat_keep)
			break ;
		ft_sleep(philo);
		ft_think(philo);
	}
	pthread_mutex_lock(philo->lock);
	*philo->is_full += 1;
	if (*philo->is_full == philo->nbr_philo)
		*philo->is_ph_dead = 1;
	pthread_mutex_unlock(philo->lock);
	return (NULL);
}
