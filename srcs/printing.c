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

void			print_file(t_file *file, t_flags *flags, t_offsets *offsets)
{
	if (file == NULL)
		return ;
	if (file->name[0] != '.' || flags->a == 1)
	{
		if (flags->l == 1)
			print_file_info(file, offsets);
		if (check_dir(file->name) == 0)
		{
			ft_putstr("\x1b[36m");
			ft_putstr(file->name);
			ft_putstr("\x1b[0m");
		}
		else
			ft_putstr(file->name);
		ft_putchar('\n');
	}
}

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

void			print_everything(t_file *files, t_flags *flags)
{
	t_file		*cur_file;
	t_offsets	*offsets;

	cur_file = files;
	cur_file = files;
	offsets = offsets_init();
	if (flags->l == 1)
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
		print_file(cur_file, flags, offsets);
		cur_file = cur_file->next;
	}
	free(offsets);
}

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
