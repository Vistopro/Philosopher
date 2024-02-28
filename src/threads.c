/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:20:35 by vicrodri          #+#    #+#             */
/*   Updated: 2024/02/28 13:58:02 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*philo_life(void *phil)
{
	t_philo	*philo;

	philo = (t_philo *)phil;
	while (*philo->dead == 0)
	{
		philo_eat(philo);
		philo_think(philo);
		philo_sleep(philo);
	}
	return (0);
}

void	*monitor(void *prog)
{
	t_program	*program;
	int			i;
	int			j;

	program = (t_program *)prog;
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
