/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beta <ade-beta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:00:38 by ade-beta          #+#    #+#             */
/*   Updated: 2022/07/22 11:53:29 by ade-beta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	peat(t_philo *p, int i, int j)
{	
	pthread_mutex_lock(&p->s->f[i]);
	prnt(p->s, p->id, "has taken a fork");
	pthread_mutex_lock(&p->s->f[j]);
	prnt(p->s, p->id, "has taken a fork");
	prnt(p->s, p->id, "is eating");
	p->last_eat = get_time(p->s);
	++p->eat_count;
	slp(p->s, 2);
	pthread_mutex_unlock(&p->s->f[i]);
	pthread_mutex_unlock(&p->s->f[j]);
}

void	*phread(void *a)
{
	t_philo	*p;

	p = a;
	while (!p->s->dead)
	//while (p->eat_count < p->s->rules[4])
	{
		if (p->id % 2 == 1)
			peat(p, p->lf, p->rf);
		else
			peat(p, p->rf, p->lf);
		prnt(p->s, p->id, "is sleeping");
		slp(p->s, 3);
		prnt(p->s, p->id, "is thinking");
	}
	return (NULL);
}

void	loop(t_set	*s)
{
	int	i;

	while (!s->dead)
	{
		i = -1;
		while (s->rules[4] != -1 && s->p[++i].eat_count >= s->rules[4])
			if (i + 1 == s->rules[0])
				s->dead = 1;
		i = -1;
		while (++i < s->rules[0] && !s->dead)
			if (get_time(s) - s->p[i].last_eat >= s->rules[1])
			{
				s->dead = 1;
				prnt(s, i + 1, "has died");
				return ;
			}
	}
}

int	main(int argc, char **argv)
{
	t_set	s;
	int		i;
	
	if (argc < 5 || argc > 6 || init(&s, argv))
		return (1);
	s.start = get_time(&s);
	i = -1;
	while (++i < s.rules[0])
	{
		if (pthread_create(&s.p[i].thr, NULL, phread, &s.p[i]))
			frexit(&s, s.rules[0]);
		s.p[i].last_eat = get_time(&s);
		//usleep(1000);
	}
	loop(&s);
	i = -1;
	while (++i < s.rules[0])
		pthread_join(s.p[s.rules[0] - 1].thr, NULL);
	frexit(&s, s.rules[0]);
}
