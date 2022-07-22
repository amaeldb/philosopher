/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beta <ade-beta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:00:34 by ade-beta          #+#    #+#             */
/*   Updated: 2022/07/20 15:00:38 by ade-beta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

struct	s_set;

typedef struct s_philo
{
	int				id;
	long long		last_eat;
	pthread_t		thr;
	int				eat_count;
	int				lf;
	int				rf;
	struct s_set	*s;
}	t_philo;

typedef	struct s_set
{
	int				rules[5];
	int				done;
	int				dead;
	long long		start;
	t_philo			*p;
	pthread_mutex_t	*f;
	pthread_mutex_t	prnt;
}	t_set;

int			ft_atoi(const char *nptr);
int			init(t_set *s, char **str);
void		frexit(t_set *s, int i);
void		prnt(t_set *s, int id, char *str);
long long	get_time(t_set *s);
void		slp(t_set *s, int r);

#endif