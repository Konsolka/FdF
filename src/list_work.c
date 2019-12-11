/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_work.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 15:18:18 by mburl             #+#    #+#             */
/*   Updated: 2019/12/11 12:44:24 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			fdf_lst_begin(t_fdf **alst)
{
	t_fdf	*lst;

	lst = *alst;
	if (!lst->up)
		return ;
	while (1)
	{
		lst = lst->up;
		if (!lst->up)
			break ;
	}
	*alst = lst;
}

void			free_fdf_lst(t_fdf **alst)
{
	t_fdf	*lst;
	int		i;

	fdf_lst_begin(alst);
	lst = *alst;
	while (lst)
	{
		i = 0;
		while (i < lst->max_line)
		{
			free(lst->coords[i]);
			lst->coords[i] = NULL;
			i++;
		}
		if (!lst->down)
		{
			free(lst);
			lst = NULL;
			return ;
		}
		lst = lst->down;
		free(lst->up);
		lst->up = NULL;
	}
}

static void		place_coords(double **coords, char **str_coords,
								int max_line, int y)
{
	int i;
	int z;

	i = 0;
	while (i < max_line)
	{
		z = ft_atoi(str_coords[i]);
		coords[i] = (double *)malloc(sizeof(double) * 4);
		coords[i][0] = i;
		coords[i][1] = y;
		coords[i][2] = z;
		coords[i][3] = 0;
		if (z > 0)
			coords[i][3] = 1;
		i++;
	}
}

void			ft_lst_add(t_fdf **alst, int x, int y, char **coords)
{
	t_fdf	*new;
	t_fdf	*lst;

	lst = *alst;
	new = (t_fdf *)malloc(sizeof(t_fdf));
	new->coords = (double **)malloc(sizeof(double *) * x);
	place_coords(new->coords, coords, x, y);
	new->down = NULL;
	new->up = NULL;
	new->max_line = x;
	if (!lst)
		lst = new;
	else
	{
		lst->down = new;
		lst->down->up = lst;
		lst = lst->down;
	}
	*alst = lst;
}
