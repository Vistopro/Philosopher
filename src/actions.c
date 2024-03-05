/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:47:13 by vicrodri          #+#    #+#             */
/*   Updated: 2024/03/05 18:54:13 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_think(t_philo *philo)
{
	print_philo("is thinking", philo, philo->id);
}

void	philo_sleep(t_philo *philo)
{
	print_philo("is sleeping", philo, philo->id);
	ft_usleep(philo->time_to_sleep);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_philo("has taken a fork", philo, philo->id);
	if (philo->num_of_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	print_philo("has taken a fork", philo, philo->id);
	philo->eating = 1;
	print_philo("is eating", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
