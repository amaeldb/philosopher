/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beta <ade-beta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:38:33 by ade-beta          #+#    #+#             */
/*   Updated: 2022/07/21 13:43:40 by ade-beta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	neg;
	int	ret;

	i = 0;
	ret = 0;
	neg = 1;
	while (nptr[i] == '\t' || nptr[i] == '\n' || nptr[i] == '\r'
		|| nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			neg = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		ret = (ret * 10) + (nptr[i] - '0');
		i++;
	}
	return (ret * neg);
}

void	frexit(t_set *s, int i)
{
	int	j;

	j = -1;
	if (s->p)
		free(s->p);
	if (s->f)
	{
		while (++j < i)
			(void)pthread_mutex_destroy(&s->f[j]);
		free(s->f);
	}
	(void)pthread_mutex_destroy(&s->prnt);
	exit (0);
}

long long	get_time(t_set *s)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		frexit(s, s->rules[0]);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	prnt(t_set *s, int id, char *str)
{
	if (s->dead && str[4] != 'd')
		return ;
	pthread_mutex_lock(&s->prnt);
	printf("%lld %d %s\n", (get_time(s) - s->start), id, str);
	pthread_mutex_unlock(&s->prnt);
}

void	slp(t_set *s, int r)
{
	long long	i;

	i = get_time(s);
	while (1)
	{
		if (get_time(s) - i >= s->rules[r])
			return ;
		usleep(50);
	}
}
