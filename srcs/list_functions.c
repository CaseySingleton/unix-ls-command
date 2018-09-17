/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 22:59:40 by csinglet          #+#    #+#             */
/*   Updated: 2018/09/04 22:59:41 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_file		*new_file_link(void)
{
	t_file			*new;

	if (!(new = (t_file *)malloc(sizeof(t_file))))
		return (NULL);
	new->next = NULL;
	return (new);
}

static void			file_add_end(t_file **afile, t_file *addition)
{
	t_file			*temp;

	if ((*afile) == NULL)
	{
		*afile = addition;
		return ;
	}
	temp = *afile;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = addition;
}

static t_file		*get_file_info(char *name, struct dirent *cur)
{
	t_file			*file;

	file = new_file_link();
	file->file_path = get_file_path(name, cur->d_name);
	file->name = ft_strdup(cur->d_name);
	file->permissions = get_permissions(file->file_path);
	get_stats(file, file->file_path);
	return (file);
}

t_file				*get_all_files(char *name)
{
	DIR				*d_stream;
	struct dirent	*cur;
	t_file			*files;

	files = NULL;
	d_stream = opendir(name);
	if (d_stream == NULL)
		return (NULL);
	while ((cur = readdir(d_stream)))
		file_add_end(&files, get_file_info(name, cur));
	closedir(d_stream);
	free(cur);
	return (files);
}

void				swap_noodles(t_file **prev, t_file **n1, t_file **n2,
					t_file **head)
{
	if (*prev != NULL)
	{
		(*prev)->next = (*n2);
		(*n1)->next = (*n2)->next;
		(*n2)->next = (*n1);
	}
	else
	{
		(*n1)->next = (*n2)->next;
		(*n2)->next = (*n1);
		(*n1) = (*n2);
		*head = *n2;
	}
}
