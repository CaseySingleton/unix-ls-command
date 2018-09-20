/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 20:13:22 by csinglet          #+#    #+#             */
/*   Updated: 2018/09/18 20:13:23 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					print_dir(char *name, t_flags *flags)
{
	t_file			*files;
	t_file			*temp;

	files = get_all_files(name);
	if (files == NULL)
		return (-1);
	sort(&files, flags);
	if (flags->rec == 1)
		print_recursive(files, flags);
	else
		print_everything(files, flags);
	while (files != NULL && flags->rec != 1)
	{
		temp = files->next;
		free_file(files);
		files = temp;
	}
	return (0);
}

void				print_dirs(char **av, int ac, int start, t_flags *flags)
{
	int				i;

	i = start - 1;
	while (++i < ac)
	{
		if (check_dir(av[i]) == 0)
		{
			ft_putstr(av[i]);
			ft_putstr(":\n");
			print_dir(av[i], flags);
		}
		if (i + 1 < ac && check_dir(av[i + 1]) != -1)
			ft_putstr("\n");
	}
}

int					print_file(char *name, t_flags *flags)
{
	t_file			*files;
	t_file			*temp;
	t_file			*item;

	files = get_all_files(".");
	if (files == NULL)
		return (-1);
	temp = files;
	while (ft_strcmp(temp->name, name) != 0)
		temp = temp->next;
	item = copy_node(temp);
	print_everything(item, flags);
	while (files != NULL && flags->rec != 1)
	{
		temp = files->next;
		free_file(files);
		files = temp;
	}
	return (0);
}

void				print_files(char **av, int ac, int start, t_flags *flags)
{
	int				dir_check;
	int				nl_check;
	int				i;

	dir_check = 0;
	nl_check = 0;
	i = start - 1;
	while (++i < ac)
	{
		if (check_file(av[i]) == 0 && check_dir(av[i]) == -1)
		{
			flags->not_a_dir = 1;
			print_file(av[i], flags);
			nl_check = 1;
			flags->not_a_dir = 0;
		}
		else
			dir_check = 1;
	}
	if (i + 1 == ac && nl_check == 1 && dir_check == 1)
		ft_putchar('\n');
}
