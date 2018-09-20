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

/*
**	Check for any erorrs
**	  if any errors are found, print error message and exit the program
**
**	Check if no arguments besides flags are given
**	  if the above is true, use the current directory as an argument
**
**	Sort arguments by ascii order
**
**	Check for any invalid directories given as arguments
**	  if invalid, print an error message and continue the program
**
**	If any files were given as an argument print
*/

static void		ft_ls(int argc, char **argv, t_flags *flags)
{
	int			start;

	start = 1;
	if ((start = manage_errors(argc, argv)) == -1)
		exit(-1);
	if (start == argc)
		print_dir(".", flags);
	ft_sort_list_ascii(&argv, start, argc);
	check_dir_all(argc, argv, start, flags);
	print_files(argv, argc, start, flags);
	print_dirs(argv, argc, start, flags);
}

int				main(int argc, char *argv[])
{
	t_flags		*flags;

	flags = get_flags(argc, argv);
	ft_ls(argc, argv, flags);
	free(flags);
	return (0);
}
