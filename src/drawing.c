/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 16:15:24 by mburl             #+#    #+#             */
/*   Updated: 2019/11/11 17:25:03 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_mlx_line(int x1, int y1, int x2, int y2, t_mlx *lst)
{
	int		deltx;
	int		delty;
	int		signx;
	int		signy;
	int		error;

	deltx = abs(x2 - x1);
	delty = abs(y2 - y1);
	signx = x1 < x2 ? 1 : -1;
	signy = y1 < y2 ? 1 : -1;
	error = deltx - delty;
	mlx_pixel_put(lst->ptr, lst->win, x2, y2, 0xFFFFFF);
	while (x1 != x2 || y1 != y2)
	{
		mlx_pixel_put(lst->ptr, lst->win, x1, y1, 0xFFFFFF);
		double error2 = error * 2;
		if (error2 > -delty)
		{
			error -= delty;
			x1 += signx;
		}
		if (error2 < deltx)
		{
			error += deltx;
			y1 += signy;
		}
	}
}

void	drawing_map(t_fdf *lst, t_mlx *mlx_list)
{
	int		temp[2];

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
	lst = lst->next;
	while (lst)
	{
		temp[0] = 4;
		temp[1] = 1;		
		ft_mlx_line((int)(lst->prev->coords[0][0]), (int)(lst->prev->coords[1][0]), (int)(lst->coords[0][0]), (int)(lst->coords[1][0]), mlx_list);
		if (lst->up)
		{
			ft_mlx_line((int)(lst->prev->up->coords[0][0]), (int)(lst->prev->up->coords[1][0]), (int)(lst->prev->coords[0][0]), (int)(lst->prev->coords[1][0]), mlx_list);
			ft_mlx_line((int)(lst->up->coords[0][0]), (int)(lst->up->coords[1][0]), (int)(lst->coords[0][0]), (int)(lst->coords[1][0]), mlx_list);
		}
			
		if (!lst->next)
		{
			if (lst->down)
			{
				while (lst->prev->prev)
					lst = lst->prev;
				lst = lst->down;
			}
			else
				break ;
		}
		else
			lst = lst->next;
	}
}