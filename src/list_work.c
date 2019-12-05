/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_work.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 15:18:18 by mburl             #+#    #+#             */
/*   Updated: 2019/12/05 14:30:17 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_lst_begin(t_fdf **alst)
{
	t_fdf	*lst;

	lst = *alst;
	if (!lst->up)
		return ;
	while (lst)
	{
		lst = lst->up;
		if (!lst->up)
			break ;
	}
	*alst = lst;
}
void	free_fdf_lst(t_fdf **alst)
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
void	ft_lst_add(t_fdf **alst, int x, int y, char **coords)
{
	t_fdf	*new;
	t_fdf	*lst;
	int		z;
	int		i;

	lst = *alst;
	new = (t_fdf *)malloc(sizeof(t_fdf));
	i = 0;
	new->coords = (double **)malloc(sizeof(double *) * x);
	while (i < x)
	{
		z = ft_atoi(coords[i]);
		new->coords[i] = (double *)malloc(sizeof(double) * 3);
		new->coords[i][0] = i; 
		new->coords[i][1] = y;
		new->coords[i][2] = z;
		i++;
	}
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