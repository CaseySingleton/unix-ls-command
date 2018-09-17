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

void			sort(t_file **files, t_flags *flags)
{
	if (flags->t == 1)
		time_sort(files, (flags->r == 1) ? 1 : -1);
	else
		alpha_sort(files, (flags->r == 1) ? 1 : -1);
}
