#include "philo.h"

int	ft_atoi(const char *nptr)
{
	long long int	val;
	int				signe;

	signe = 1;
	val = 0;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\f' || *nptr == '\n' \
		 || *nptr == '\r' || *nptr == '\v')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			signe = -signe;
		nptr++;
	}
	while ('0' <= *nptr && *nptr <= '9')
		val = 10 * val + (*nptr++ - '0');
	return (signe * val);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	free_mallocs(t_philo *p)
{
	free(p->philo_need_to_eat);
	free(p->philo_last_action);
	free(p->philo_last_meal);
}

long int	get_time(t_philo *p)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	if (p->start == 0)
		return (time.tv_sec * 1000 + time.tv_usec / 1000);
	else
		return ((time.tv_sec * 1000 + time.tv_usec / 1000) - p->start);
}

void	print_msg(const char *s, t_philo *p, int philo_n, int action)
{
	sem_wait(p->print);
	if (p->philo_last_action[philo_n - 1] != action && p->die)
	{
		p->philo_last_action[philo_n - 1] = action;
		printf("%4ld %d %s", get_time(p), philo_n, s);
	}
	sem_post(p->print);
}