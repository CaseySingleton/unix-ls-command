/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 21:04:36 by csinglet          #+#    #+#             */
/*   Updated: 2018/08/24 21:04:37 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				print_dir(char *name, t_flags *flags)
{
	t_file		*files;
	t_file		*temp;

	files = get_all_files(name);
	if (files == NULL)
		return (-1);
	sort(&files, flags);
	if (flags->R == 1)
		print_recursive(files, flags);
	else
		print_everything(files, flags);
	while (files != NULL && flags->R != 1)
	{
		temp = files->next;
		free_file(files);
		files = temp;
	}
	return (0);
}

static void		ft_ls(int argc, char **argv, t_flags *flags)
{
	int			i;

	i = 1;
	if ((i = manage_errors(argc, argv)) == -1)
		exit(-1);
	if (i == argc)
		print_dir(".", flags);
	check_dir_all(argc, argv, i);
	ft_sort_list_ascii(&argv, i, argc);
	if (i + 1 == argc)
		print_dir(argv[i++], flags);
	while (i < argc)
	{
		if (check_dir(argv[i]) != -1)
		{
			ft_putstr(argv[i]);
			ft_putstr(":\n");
		}
		print_dir(argv[i], flags);
		if (i + 1 < argc && check_dir(argv[i + 1]) != -1)
			ft_putstr("\n");
		i++;
	}
}

/*
**	FLAG DESCRIPTIONS
**
**	-l
**		List in long format. If the output is to a terminal, a total sum for
**		all the file sizes is output on a line before the long listing.
**
**	-R
**		Recursively list subdirectories encountered.
**
**	-a
**		Include directory entries whose names begin with a dot (.).
**
**	-r
**		Reverse the order of the sort to get reverse lexicographical order or
**		the oldest enteries first (or largest files last, if combined with sort
**		by size)
**
**	-t
**		Sort by time modified (most recently modified first) before sorting the
**		operands by lexicographical order.
*/

int				main(int argc, char *argv[])
{
	t_flags		*flags;

	flags = get_flags(argc, argv);
	ft_ls(argc, argv, flags);
	free(flags);
	return (0);
}
