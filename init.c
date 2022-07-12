/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beta <ade-beta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:26:23 by ade-beta          #+#    #+#             */
/*   Updated: 2022/07/07 20:38:21 by ade-beta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_philo *p, int i, t_set *s)
{
	p->id = i + 1;
	p->eat_count = 0;
	p->s = s;
	p->lf = i;
	if ((i + 1) == s->rules[0])
		p->rf = 0;
	else
		p->rf = i + 1;
	if (pthread_mutex_init(&s->f[i], NULL))
		frexit(s, i);
}

int	setup(t_set *s)
{
	int	i;

	i = -1;
	s->p = malloc(sizeof(t_philo) * s->rules[0]);
	if (!s->p)
		return (1);
	s->f = malloc(sizeof(pthread_mutex_t) * s->rules[0]);
	if (!s->f)
	{
		free(s->p);
		return (1);
	}
	while (++i < s->rules[0])
		init_philo(&s->p[i], i, s);
	if (pthread_mutex_init(&s->prnt, NULL))
		frexit(s, i);
	return (0);
}

int	init(t_set *s, char **str)
{
	int	i;
	int	j;

	j = 0;
	s->rules[4] = -1;
	while (str[++j])
	{
		i = -1;
		while (str[j][++i])
			if (str[j][i] < '0' || str[j][i] > '9')
				return (1);
		s->rules[j - 1] = ft_atoi(str[j]);
	}
	return (setup(s));
}
