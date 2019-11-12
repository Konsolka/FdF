/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_work.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 15:18:18 by mburl             #+#    #+#             */
/*   Updated: 2019/11/12 16:55:14 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_fdf	*ft_create_node(int x, int y, int z)
{
	t_fdf	*node;

	node = (t_fdf *)malloc(sizeof(t_fdf));
	node->coords = (double **)malloc(sizeof(double *) * 3);
	node->coords[0] = (double *)malloc(sizeof(double));
	node->coords[0][0] = x;
	node->coords[1] = (double *)malloc(sizeof(double));
	node->coords[1][0] = y;
	node->coords[2] = (double *)malloc(sizeof(double));
	node->coords[2][0] = z;
	node->coords[3] = (double *)malloc(sizeof(double));
	node->coords[3][0] = 1;
	node->next = NULL;
	node->prev = NULL;
	node->up = NULL;
	node->down = NULL;
	return (node);
}

void	ft_fdfadd(t_fdf **alst, t_fdf *new)
{
	t_fdf *curr;

	curr = *alst;
	if (!curr)
		curr = new;
	else
	{
		if (curr->up)
		{
			if (curr->up->next)
			{
				new->up = curr->up->next;
				curr->up->next->down = new;
			}
		}
		new->prev = curr;
		curr->next = new;
		curr = curr->next;
	}
	*alst = curr;
}

void	ft_fdfdown(t_fdf **alst, t_fdf *new)
{
	t_fdf *curr;

	curr = *alst;
	curr->down = new;
	curr->down->up = curr;
	curr = curr->down;
	*alst = curr;
}

void	ft_lst_begin(t_fdf **alst)
{
	t_fdf	*lst;

	lst = *alst;
	while (lst)
	{
		if (lst->prev)
			lst = lst->prev;
		else
		{
			if (lst->up)
				lst = lst->up;
			else
				break ;
		}
	}
	*alst = lst;
}