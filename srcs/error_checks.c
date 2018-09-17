/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 19:59:32 by csinglet          #+#    #+#             */
/*   Updated: 2018/09/15 19:59:32 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				check_dir(char *name)
{
	DIR			*d_stream;

	d_stream = opendir(name);
	if (d_stream == NULL)
		return (-1);
	closedir(d_stream);
	d_stream = NULL;
	return (0);
}

void			check_dir_all(int ac, char **av, int i)
{
	while (i < ac)
	{
		if (check_dir(av[i]) == -1)
		{
			ft_putstr("ft_ls: ");
			ft_putstr(av[i]);
			ft_putstr(": No such file or directory\n");
		}
		i++;
	}
}

int				manage_errors(int ac, char **av)
{
	int			i;

	i = 1;
	while (i != ac && av[i][0] == '-')
	{
		if (av[i][0] == '-' && av[i][1] == '-' && av[i][2] != '\0')
		{
			ft_putstr("illegal option -- -\nusage: ./ft_ls [-Ralrt]\n");
			return (-1);
		}
		i++;
	}
	return (i);
}
