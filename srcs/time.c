/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 01:11:30 by csinglet          #+#    #+#             */
/*   Updated: 2018/09/06 01:11:31 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	All functions return a value (1 or -1) depending on if one parameter
**	is larger or smaller than the other. If equal 0 is returned
*/

int				compare_year(char *year1, char *year2)
{
	int		y1;
	int		y2;

	y1 = ft_atoi(year1);
	y2 = ft_atoi(year2);
	if (y1 == y2)
		return (0);
	return ((y1 < y2) ? 1 : -1);
}

/*
**	This funciton returns a number value for a specific month
**	so that a simple int comparison can be used
*/

static int		get_month_number(char *month)
{
	if (ft_strcmp(month, "Jan") == 0)
		return (1);
	if (ft_strcmp(month, "Feb") == 0)
		return (2);
	if (ft_strcmp(month, "Mar") == 0)
		return (3);
	if (ft_strcmp(month, "Apr") == 0)
		return (4);
	if (ft_strcmp(month, "May") == 0)
		return (5);
	if (ft_strcmp(month, "Jun") == 0)
		return (6);
	if (ft_strcmp(month, "Jul") == 0)
		return (7);
	if (ft_strcmp(month, "Aug") == 0)
		return (8);
	if (ft_strcmp(month, "Sep") == 0)
		return (9);
	if (ft_strcmp(month, "Oct") == 0)
		return (10);
	if (ft_strcmp(month, "Nov") == 0)
		return (11);
	if (ft_strcmp(month, "Dec") == 0)
		return (12);
	return (-1);
}

int				compare_month(char *m1, char *m2)
{
	int		month1;
	int		month2;

	month1 = get_month_number(m1);
	month2 = get_month_number(m2);
	if (month1 == month2)
		return (0);
	return ((month1 < month2) ? 1 : -1);
}

int				compare_day(char *day1, char *day2)
{
	int		d1;
	int		d2;

	d1 = ft_atoi(day1);
	d2 = ft_atoi(day2);
	if (d1 == d2)
		return (0);
	return ((d1 > d2) ? 1 : -1);
}

/*
**	I know that ft_strcmp() may have been a better choice than
**	ft_strsplit() but oh well...
*/

int				compare_clock_time(char *time1, char *time2)
{
	char	**t1;
	char	**t2;
	int		i;
	int		cmp1;
	int		cmp2;

	t1 = ft_strsplit(time1, ':');
	t2 = ft_strsplit(time2, ':');
	i = -1;
	while (t1[++i] && t2[i])
	{
		cmp1 = ft_atoi(t1[i]);
		cmp2 = ft_atoi(t2[i]);
		if (cmp1 != cmp2)
			break ;
	}
	ft_free_strsplit(&t1);
	ft_free_strsplit(&t2);
	if (cmp1 == cmp2)
		return (0);
	return ((cmp1 > cmp2) ? 1 : -1);
}
