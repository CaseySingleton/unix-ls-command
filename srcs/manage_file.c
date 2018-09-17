/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 22:59:00 by csinglet          #+#    #+#             */
/*   Updated: 2018/09/04 22:59:00 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			free_file(t_file *file)
{
	int			i;

	free(file->name);
	free(file->file_path);
	free(file->permissions);
	free(file->user_name);
	free(file->group_name);
	i = -1;
	while (file->split_time[++i] != NULL)
		free(file->split_time[i]);
	free(file->split_time);
	free(file);
	file = NULL;
}

void			free_all_files(t_file *files)
{
	t_file		*temp;

	while (files != NULL)
	{
		temp = files->next;
		free_file(files);
		files = temp;
	}
}

t_offsets		*offsets_init(void)
{
	t_offsets	*offsets;

	if (!(offsets = (t_offsets *)malloc(sizeof(t_offsets))))
		return (NULL);
	offsets->link_offset = 0;
	offsets->mem_offset = 0;
	offsets->day_offset = 0;
	return (offsets);
}
