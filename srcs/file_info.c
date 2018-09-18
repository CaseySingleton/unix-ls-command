/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 21:47:46 by csinglet          #+#    #+#             */
/*   Updated: 2018/09/17 21:47:47 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char			*get_permissions(const char *file_path)
{
	struct stat		file_stats;
	char			*permissions;
	char			*temp;

	temp = ft_strdup(file_path);
	permissions = ft_strnew(10);
	if ((lstat(temp, &file_stats)) < 0)
		return (NULL);
	permissions[0] = ((S_ISDIR(file_stats.st_mode)) ? 'd' : '-');
	permissions[1] = ((file_stats.st_mode & S_IRUSR) ? 'r' : '-');
	permissions[2] = ((file_stats.st_mode & S_IWUSR) ? 'w' : '-');
	permissions[3] = ((file_stats.st_mode & S_IXUSR) ? 'x' : '-');
	permissions[4] = ((file_stats.st_mode & S_IRGRP) ? 'r' : '-');
	permissions[5] = ((file_stats.st_mode & S_IWGRP) ? 'w' : '-');
	permissions[6] = ((file_stats.st_mode & S_IXGRP) ? 'x' : '-');
	permissions[7] = ((file_stats.st_mode & S_IROTH) ? 'r' : '-');
	permissions[8] = ((file_stats.st_mode & S_IWOTH) ? 'w' : '-');
	permissions[9] = ((file_stats.st_mode & S_IXOTH) ? 'x' : '-');
	free(temp);
	return (permissions);
}

/*
**	Gets all of the information displayed by the -l flag
*/

void			get_stats(t_file *file, char *file_path)
{
	struct stat		d_info;
	struct passwd	*p_info;
	struct group	*g_info;

	lstat(file_path, &d_info);
	file->split_time = ft_strsplit(ctime(&d_info.st_mtime), ' ');
	file->split_time[3][5] = '\0';
	p_info = getpwuid(d_info.st_uid);
	g_info = getgrgid(d_info.st_gid);
	file->links = d_info.st_nlink;
	file->user_name = ft_strdup(p_info->pw_name);
	file->group_name = ft_strdup(g_info->gr_name);
	file->file_size = d_info.st_size;
}

char			*get_file_path(char *dir, char *file)
{
	char		*temp;
	char		*file_path;

	temp = NULL;
	file_path = NULL;
	if (dir[ft_strlen(dir) - 1] != '/')
	{
		temp = ft_strjoin(dir, "/");
		file_path = ft_strjoin(temp, file);
		free(temp);
	}
	else
		file_path = ft_strjoin(dir, file);
	return (file_path);
}

/*
**	Gets the file path, name of file, and file permissions for the
**	given file
**
**	name - name of the file being looked at
**
**	cur - dirent variable that is used to gather info about name.
**	  information is parsed and then saved into a t_file variable
*/

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

/*
**	For each item in a directory, gets all info using get_file_info() and
**	stores results into a linked list
*/

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
