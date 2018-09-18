/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 23:50:09 by csinglet          #+#    #+#             */
/*   Updated: 2018/09/17 16:29:13 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>

# include <uuid/uuid.h>
# include <sys/types.h>
# include <sys/stat.h>

typedef struct		s_flags
{
	int				l;
	int				rec;
	int				a;
	int				r;
	int				t;
}					t_flags;

typedef struct		s_file
{
	char			*name;
	char			*file_path;
	int				dir_flag;
	char			*permissions;
	int				links;
	char			*user_name;
	char			*group_name;
	long long		file_size;
	char			**split_time;
	struct s_file	*next;
}					t_file;

typedef struct		s_offsets
{
	int				link_offset;
	int				mem_offset;
	int				day_offset;
}					t_offsets;

/*
**	main.c (shouldn't be in main)
*/

int					print_dir(char *name, t_flags *flags);

/*
**	manage_flags.c
*/

t_flags				*get_flags(int argc, char **argv);

/*
**	utils.c
*/


/*
**	list_functions.c
*/

t_file				*new_file_link(void);
void				file_add_end(t_file **afile, t_file *addition);
void				swap_noodles(t_file **prev, t_file **n1, t_file **n2,
					t_file **head);

/*
**	file_info.c
*/

void				get_stats(t_file *file, char *file_path);
char				*get_permissions(const char *file_path);
char				*get_file_path(char *dir, char *file);
t_file				*get_all_files(char *name);

/*
**	manage_file.c
*/

void				free_file(t_file *file);
void				free_all_files(t_file *files);
t_offsets			*offsets_init(void);

/*
**	sorting.c
*/

void				alpha_sort(t_file **files, int rev);
void				time_sort(t_file **files, int rev);
int					compare_time(t_file *f1, t_file *f2);
void				sort(t_file **files, t_flags *flags);

/*
**	time.c
*/

int					compare_year(char *year1, char *year2);
int					compare_month(char *m1, char *m2);
int					compare_day(char *day1, char *day2);
int					compare_clock_time(char *time1, char *time2);

/*
**	printfing.c
*/

void				print_file(t_file *file, t_flags *flags, t_offsets
					*offsets);
void				print_everything(t_file *files, t_flags *flags);
void				print_recursive(t_file *files, t_flags *flags);
void				print_file_info(t_file *file, t_offsets *offsets);

/*
**	error_checks.c
*/

int					check_dir(char *name);
void				check_dir_all(int ac, char **av, int i);
int					manage_errors(int ac, char **av);

#endif
