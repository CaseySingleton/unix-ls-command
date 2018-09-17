/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 23:45:29 by csinglet          #+#    #+#             */
/*   Updated: 2018/09/03 23:45:30 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char			*get_file_path(char *dir, char *item)
{
	char		*temp;
	char		*file_path;

	temp = NULL;
	file_path = NULL;
	if (dir[ft_strlen(dir) - 1] != '/')
	{
		temp = ft_strjoin(dir, "/");
		file_path = ft_strjoin(temp, item);
		free(temp);
	}
	else
		file_path = ft_strjoin(dir, item);
	return (file_path);
}

/*
**	Stats are seperated by at least two white spaces
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

/*
**	If the file has additional attributes then an @ symbol is displayed
**	after all the permissions have been displayed
*/

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

static int		ascii_time_sort(char *s1, char *s2)
{
	int			i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	if (s1[i] == '\0' && s2[i] == '\0')
		return (0);
	if (i > 0)
	{
		if (s1[i] == '\0')
			return (1);
		if (s2[i] == '\0')
			return (-1);
		if (s1[i + 1] == '\0' && s2[i + 1] != '\0')
			return (1);
		if (s1[i] > s2[i])
			return (1);
	}
	if (s1[i] > s2[i])
		return (1);
	return (-1);
}

int				compare_time(t_file *f1, t_file *f2)
{
	int			i;

	i = compare_year(f1->split_time[4], f2->split_time[4]);
	if (i != 0)
		return (i);
	i = compare_month(f1->split_time[1], f2->split_time[1]);
	if (i != 0)
		return (i);
	i = compare_day(f1->split_time[2], f2->split_time[2]);
	if (i != 0)
		return (i);
	i = compare_clock_time(f1->split_time[3], f2->split_time[3]);
	if (i != 0)
		return (i);
	i = ft_ascii_cmp(f1->name, f2->name);
	if (i != 0)
		return (i);
	while (1)
		;
	return (0);
}
