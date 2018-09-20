/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 16:33:42 by csinglet          #+#    #+#             */
/*   Updated: 2018/09/06 16:33:43 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** "Computer Gods, I beg of you to please bless me with the knowledge amd power
** of the keystroke so I may use it to MAKE THIS PROGRAM WORK!
**
** P.S. I will sacrafice my first born child and a virgin male if you help me
** out (just this once ;))
**
** Thanks CG!
**
** Regards
**
** Jor Jor Binks~"
*/

/*
**	The above was done by one of my friends. While it may not be professional
**	I have chosen to leave it in
*/

void			print_file_info(t_file *file, t_offsets *offsets)
{
	ft_putstr(file->permissions);
	ft_putspace(offsets->link_offset - ft_numlen(file->links) + 1);
	ft_putnbr(file->links);
	ft_putchar(' ');
	ft_putstr(file->user_name);
	ft_putspace(2);
	ft_putstr(file->group_name);
	ft_putspace(offsets->mem_offset - ft_numlen(file->file_size) + 2);
	ft_putnbr(file->file_size);
	ft_putchar(' ');
	ft_putstr(file->split_time[1]);
	ft_putspace(offsets->day_offset - ft_strlen(file->split_time[2]));
	ft_putstr(file->split_time[2]);
	ft_putchar(' ');
	ft_putstr(file->split_time[3]);
	ft_putchar(' ');
}

/*
**	Prints information of a single given file.
**
**	If the -a flag was used then hidden directories are shown.
**	If the -l flag was used then print_file_info() is called to print
**	  stats about the file as well.
**	Finally if the file is a directory the name is printed in cyan
*/

void			print_item(t_file *item, t_flags *flags, t_offsets *offsets)
{
	if (item == NULL)
		return ;
	if (item->name[0] != '.' || flags->a == 1)
	{
		if (flags->l == 1)
			print_file_info(item, offsets);
		if (check_dir(item->name) == 0)
		{
			ft_putstr("\x1b[36m");
			ft_putstr(item->name);
			ft_putstr("\x1b[0m");
		}
		else
			ft_putstr(item->name);
		ft_putchar('\n');
	}
}

/*
**	When the -l flag is used 'total (num)' is displayed before any
**	other info. num is the total number of 512 byte blocks used by
**	all files/directories in the current directory.
**
**	Basically it's the size of all of the files rounded up to the
**	nearest 512th(?) then divided by 512
**	Remember if you take up 1 byte of a 512 byte block that entire
**	block is considered used
*/

void			print_total_size(t_file *files, t_flags *flags)
{
	t_file		*cur_file;
	int			total;

	cur_file = files;
	total = 0;
	while (cur_file != NULL)
	{
		if (cur_file->name[0] != '.' || flags->a == 1)
		{
			if (cur_file->file_size % 512 != 0)
				total++;
			total += cur_file->file_size / 512;
		}
		cur_file = cur_file->next;
	}
	ft_putstr("total ");
	ft_putnbr(total);
	ft_putchar('\n');
}

/*
**	Prints info about all files inside of a directory
**
**	Currently I have not created ft_printf() so all of my
**	padding is calculated in the first while loop
*/

void			print_everything(t_file *files, t_flags *flags)
{
	t_file		*cur_file;
	t_offsets	*offsets;

	cur_file = files;
	cur_file = files;
	offsets = offsets_init();
	if (flags->l == 1 && flags->not_a_dir == 0)
		print_total_size(cur_file, flags);
	while (cur_file)
	{
		if (ft_numlen(cur_file->links) > offsets->link_offset)
			offsets->link_offset = ft_numlen(cur_file->links);
		if (ft_numlen(cur_file->file_size) > offsets->mem_offset)
			offsets->mem_offset = ft_numlen(cur_file->file_size);
		if (ft_strlen(cur_file->split_time[1]) > offsets->day_offset)
			offsets->day_offset = ft_strlen(cur_file->split_time[1]);
		cur_file = cur_file->next;
	}
	cur_file = files;
	while (cur_file != NULL)
	{
		print_item(cur_file, flags, offsets);
		cur_file = cur_file->next;
	}
	free(offsets);
}

/*
**	Prints recursivly all directories and sub directories
**
**	Prints everything about a directory using print_everything()
**	Then iterates through all items in the current directory
**	  If the given item is a directory
**		Information is gathered on the directory using
**		get_all_files() and is then put back into print_recursive()
**	Once finished, everything gets freed!
*/

void			print_recursive(t_file *files, t_flags *flags)
{
	t_file		*cur_file;
	t_file		*temp;

	cur_file = files;
	sort(&files, flags);
	cur_file = files;
	if (cur_file != NULL)
		print_everything(cur_file, flags);
	while (cur_file != NULL)
	{
		if (check_dir(cur_file->file_path) == 0 && cur_file->name[0] != '.')
		{
			ft_putchar('\n');
			ft_putstr("\x1b[36m");
			ft_putstr(cur_file->file_path);
			ft_putstr("\x1b[0m");
			ft_putstr(":\n");
			temp = get_all_files(cur_file->file_path);
			print_recursive(temp, flags);
		}
		cur_file = cur_file->next;
	}
	free_all_files(files);
}
