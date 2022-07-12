/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beta <ade-beta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:00:38 by ade-beta          #+#    #+#             */
/*   Updated: 2022/07/07 21:04:07 by ade-beta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	phread()
{
	
}

int	main(int argc, char **argv)
{
	t_set	s;
	
	if (argc < 5 || argc > 6 || init(&s, argv))
		return (1);
	s.start = get_time(&s);
	prnt(&s, 1, "has taken a fork");
	frexit(&s, s.rules[0]);
}
