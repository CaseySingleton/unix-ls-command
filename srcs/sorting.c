/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 13:57:35 by csinglet          #+#    #+#             */
/*   Updated: 2018/09/02 13:57:36 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			alpha_sort(t_file **files, int rev)
{
	t_file		*head;
	t_file		*next;
	t_file		*prev;

	head = *files;
	next = head->next;
	prev = NULL;
	while (head != NULL)
	{
		if (next != NULL && ft_ascii_cmp(head->name, next->name) == rev)
		{
			swap_noodles(&prev, &head, &next, files);
			head = *files;
			next = head->next;
			prev = NULL;
			continue ;
		}
		prev = head;
		head = head->next;
		if (head != NULL)
			next = head->next;
	}
}

void			time_sort(t_file **files, int rev)
{
	t_file		*head;
	t_file		*next;
	t_file		*prev;

	head = *files;
	next = head->next;
	prev = NULL;
	while (head != NULL)
	{
		if (next != NULL && compare_time(head, next) == rev)
		{
			swap_noodles(&prev, &head, &next, files);
			head = *files;
			next = head->next;
			prev = NULL;
			continue ;
		}
		prev = head;
		head = head->next;
		if (head != NULL)
			next = head->next;
	}
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

void			sort(t_file **files, t_flags *flags)
{
	if (flags->t == 1)
		time_sort(files, (flags->r == 1) ? 1 : -1);
	else
		alpha_sort(files, (flags->r == 1) ? 1 : -1);
}
