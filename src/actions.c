/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:47:13 by vicrodri          #+#    #+#             */
/*   Updated: 2024/02/29 18:07:52 by vicrodri         ###   ########.fr       */
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
	print_philo("is eating", philo, philo->id);
	ft_usleep(philo->time_to_eat);
	philo->meals_eaten++;
	philo->last_meal = get_current_time();
}
