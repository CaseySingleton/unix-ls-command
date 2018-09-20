/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 01:06:54 by csinglet          #+#    #+#             */
/*   Updated: 2018/09/04 01:06:55 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		init_flags(t_flags *flags)
{
	flags->l = 0;
	flags->rec = 0;
	flags->a = 0;
	flags->r = 0;
	flags->t = 0;
	flags->not_a_dir = 0;
}

t_flags			*get_flags(int ac, char **av)
{
	t_flags		*flags;
	int			i;
	int			j;

	i = 0;
	if (!(flags = (t_flags *)malloc(sizeof(t_flags))))
		return (NULL);
	init_flags(flags);
	while (++i < ac && av[i][0] == '-' && (j = 0) == 0)
	{
		while (av[i][++j] != '\0')
		{
			if (av[i][j] == 'l')
				flags->l = 1;
			if (av[i][j] == 'R')
				flags->rec = 1;
			if (av[i][j] == 'a')
				flags->a = 1;
			if (av[i][j] == 'r')
				flags->r = 1;
			if (av[i][j] == 't')
				flags->t = 1;
		}
	}
	return (flags);
}
