/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:40:16 by vicrodri          #+#    #+#             */
/*   Updated: 2024/03/05 19:09:42 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_program(t_program *program, t_philo *philo)
{
	program->dead_flag = 0;
	program->philos = philo;
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
}

void	init_forks(pthread_mutex_t *forks, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}
void	init_philos(t_philo *philo, t_program *program,
			pthread_mutex_t	*forks, char **argv)
{
	int	i;

	i = -1;
	while (++i < ft_atoi(argv[1]))
	{
		philo[i].id = i + 1;
		philo[i].eating = 0;
		philo[i].meals_eaten = 0;
		philo[i].last_meal = get_current_time();
		philo[i].time_to_die = ft_atoi(argv[2]);
		philo[i].time_to_eat = ft_atoi(argv[3]);
		philo[i].time_to_sleep = ft_atoi(argv[4]);
		philo[i].num_of_philos = ft_atoi(argv[1]);
		philo[i].start_time = get_current_time();
	}
}

void	init_philos2(t_philo *philo, t_program *program,
			pthread_mutex_t	*forks, char **argv)
{
	int	i;

	i = -1;
	while (++i < ft_atoi(argv[1]))
	{
		if (argv[5])
			philo[i].num_times_to_eat = ft_atoi(argv[5]);
		else
			philo[i].num_times_to_eat = -1;
		philo[i].dead = &program->dead_flag;
		philo[i].l_fork = &forks[i];
		if (i == 0)
			philo[i].r_fork = &forks[ft_atoi(argv[1]) - 1];
		else
			philo[i].r_fork = &forks[i - 1];
		philo[i].write_lock = &program->write_lock;
		philo[i].dead_lock = &program->dead_lock;
		philo[i].meal_lock = &program->meal_lock;
	}
}

int	main(int argc, char **argv)
{
	t_program			program;
	t_philo				philo[300];
	pthread_mutex_t		forks[300];

	if (argc != 5 && argc != 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	if (check_number(argv))
	{
		printf("Error: wrong argument\n");
		return (1);
	}
	init_program(&program, philo);
	init_forks(forks, ft_atoi(argv[1]));
	init_philos(program.philos, &program, forks, argv);
	init_philos2(program.philos, &program, forks, argv);
	create_threads(&program, forks);
	destroy_mutex(NULL, &program, forks);
	return (0);
}
