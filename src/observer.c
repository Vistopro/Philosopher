/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:24:01 by vicrodri          #+#    #+#             */
/*   Updated: 2024/03/05 18:53:55 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_all_meals(t_philo *philos)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (philos[0].num_times_to_eat == -1)
		return (0);
	while (i < philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meals_eaten >= philos[i].num_times_to_eat)
			j++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (j == philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

int	philosopher_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time() - philo->last_meal >= time_to_die
		&& philo->eating == 0)
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	check_death(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].num_of_philos)
	{
		if (philosopher_dead(&philos[i], philos[i].time_to_die))
		{
			print_philo("died", philos, philos->id);
			pthread_mutex_lock(philos->dead_lock);
			*philos->dead = 1;
			pthread_mutex_unlock(philos->dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}
