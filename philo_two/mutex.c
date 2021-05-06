#include "philo.h"

void	loop_ckecking_dying_philo(t_philo *p)
{
	int	i;
	int	end;

	if (p->turns > 0)
		end = p->nb;
	else
		end = -1;
	while (p->die && p->finished != end)
	{
		i = -1;
		while (i++ < p->nb)
		{
			if (p->philo_last_meal[i] >= p->die)
			{
				sem_wait(p->print);
				p->die = 0;
				printf("%4ld %d %s", get_time(p), (i + 1), "died\n");
				usleep(50);
				sem_post(p->print);
				return ;
			}
		}
	}
}

static int	chosen_index(t_philo *p)
{
	int	i;

	i = 0;
	sem_wait(p->print);
	while (p->philo_need_to_eat[i] != 0 && i < (p->nb))
		i++;
	if (i != p->nb)
		p->philo_need_to_eat[i] = 2;
	sem_post(p->print);
	return (i);
}

static void	chosing_action_algo(t_philo *p, int philo_n, int *has_eat)
{
	int			i;
	int			philo;

	philo = philo_n - 1;
	p->philo_last_meal[philo] = get_time(p) - p->philo_last_meal_tmp[philo];
	if (p->philo_need_to_eat[philo] == 1)
	{
		sem_wait(&p->forks[philo_n - 1]);
		print_msg("has taken a fork\n", p, philo_n, E_FORK);
		i = p->nb;
		while (i == p->nb)
			i = chosen_index(p);
		sem_wait(&p->forks[i]);
		*has_eat = i;
	}
	else
		print_msg("is thinking\n", p, philo_n, E_THINK);
}

int	chosing_action(t_philo *p, int philo_n)
{
	int			has_eat;

	has_eat = -1;
	while (has_eat < 0)
	{
		if (!p->die)
			return (-1);
		chosing_action_algo(p, philo_n, &has_eat);
	}
	return (has_eat);
}