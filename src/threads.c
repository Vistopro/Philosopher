/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:20:35 by vicrodri          #+#    #+#             */
/*   Updated: 2024/03/05 18:50:54 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	philo_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*philo_life(void *phil)
{
	t_philo	*philo;

	philo = (t_philo *)phil;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (philo_dead(philo) == 0)
	{
		philo_eat(philo);
		philo_think(philo);
		philo_sleep(philo);
	}
	return (0);
}

void	*monitor(void *phil)
{
	t_philo		*philos;
	int			i;
	int			j;

	philos = (t_philo *)phil;
	while (1)
	{
		if (check_death(philos) == 1 || check_all_meals(philos) == 1)
			break ;
	}
	return (NULL);
}

void	destroy_mutex(char *str, t_program *program, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (str)
		printf("%s\n", str);
	while (i < program->philos[0].num_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&program->dead_lock);
	pthread_mutex_destroy(&program->write_lock);
	pthread_mutex_destroy(&program->meal_lock);
}

void	*create_threads(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	observer;
	int			i;

	i = 0;
	if (pthread_create(&observer, NULL, &monitor, program->philos) != 0)
		destroy_mutex("Thread creation error", program, forks);
	while (i < program->philos[0].num_of_philos)
	{
		if (pthread_create(&program->philos[i].thread,
				NULL, &philo_life, &program->philos[i]) != 0)
			destroy_mutex("Thread creation error", program, forks);
		i++;
	}
	i = 0;
	if (pthread_join(observer, NULL) != 0)
		destroy_mutex("Thread join error", program, forks);
	while (i < program->philos[0].num_of_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
			destroy_mutex("Thread join error", program, forks);
		i++;
	}
	return (NULL);
}
