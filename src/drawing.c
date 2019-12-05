/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 16:15:24 by mburl             #+#    #+#             */
/*   Updated: 2019/12/05 15:27:02 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void	ft_draw_line(t_fdf *lst, t_mlx *mlx_lst)
{

}

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

void	draw_map(t_fdf *lst, t_mlx *mlx_list)
{
	int		temp[2];
	int		i;

	fdf_lst_begin(&lst);
	while (lst)
	{
		i = 0;
		while(i + 1 < lst->max_line)
		{
			printf("-- x = %f -- y =  %f -- z = %f ===\n", lst->coords[i][0], lst->coords[i][1], lst->coords[i][2]);
			ft_mlx_line(lst->coords[i][0], lst->coords[i][1], lst->coords[i + 1][0], lst->coords[i + 1][1], mlx_list);
			if (i == 0 && lst->up)
				ft_mlx_line(lst->coords[i][0], lst->coords[i][1], lst->up->coords[i][0], lst->up->coords[i][1], mlx_list);
			if (lst->up)
				ft_mlx_line(lst->coords[i + 1][0], lst->coords[i + 1][1], lst->up->coords[i + 1][0], lst->up->coords[i + 1][1], mlx_list);
			i++;
		}
		lst = lst->down;
	}
}

/*
**	needs to fix lower scale
*/
void	scaling(t_fdf *lst, double scale_x, double scale_y, double scale_z)
{
	int i;

	fdf_lst_begin(&lst);
	while (lst)
	{
		i = 0;
		while (i < lst->max_line)
		{
			lst->coords[i][0] *= scale_x;
			lst->coords[i][1] *= scale_y;
			lst->coords[i][2] *= scale_z;
			i++;
		}
		if (lst->down)
			lst = lst->down;
		else
			break ;
	}
}