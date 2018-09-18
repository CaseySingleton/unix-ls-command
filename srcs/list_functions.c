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

t_file				*new_file_link(void)
{
	t_file			*new;

	if (!(new = (t_file *)malloc(sizeof(t_file))))
		return (NULL);
	new->next = NULL;
	return (new);
}

/*
**	Appending to the end of a list is so nice
*/

void				file_add_end(t_file **afile, t_file *addition)
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

/*
**	Swaps the position of two nodes
**
**	ie. list: 1 2 3 4 5 >> swap 2 and 3 >> list: 1 3 2 4 5
*/

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
