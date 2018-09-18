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

/*
**	Tries to open a directory using name. If name is in fact a directory
**	the return of opendir() will be a d_stream object.
**	If name is not a directory NULL will be returned.
*/

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

/*
**	Manages the semantics of inputting flags
**
**	Basically if '--' is entered, it's okay and no flags are run.
**	However if '--' is followed by any character other than a null terminator
**	it's considered an error.
*/

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
