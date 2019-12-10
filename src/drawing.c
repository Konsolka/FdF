/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 16:15:24 by mburl             #+#    #+#             */
/*   Updated: 2019/12/10 12:03:28 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void	ft_mlx_line(char **p_data_addr, int x1, int y1, int x2, int y2, int size_line, int bpp)
{
	int		deltx;
	int		delty;
	int		signx;
	int		signy;
	int		error;
	long	color;
	char	*data_addr;

	data_addr = *p_data_addr;
	color = 0xFFFFFF;
	deltx = abs(x2 - x1);
	delty = abs(y2 - y1);
	signx = x1 < x2 ? 1 : -1;
	signy = y1 < y2 ? 1 : -1;
	error = deltx - delty;
	data_addr[(x2 * bpp / 8) + (y2 * size_line)] = color;
	data_addr[1 + (x2 * bpp / 8) + (y2 * size_line)] = color >> 8;
	data_addr[2 + (x2 * bpp / 8) + (y2 * size_line)] = color >> 16;
	while (x1 != x2 || y1 != y2)
	{
		double error2 = error * 2;
		if (x1 < 0 || y1 < 0 || x1 > WIDTH || y1 > HIEGHT)
		{
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
			continue ;
		}
		data_addr[((x1) * bpp / 8) + ((y1) * size_line)] = color;
		data_addr[1 + ((x1) * bpp / 8) + ((y1) * size_line)] = color >> 8;
		data_addr[2 + ((x1) * bpp / 8) + ((y1) * size_line)] = color >> 16;
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
	*p_data_addr = data_addr;
}

void	draw_map(t_fdf *lst, t_mlx *mlx_list)
{
	int		i;
	int		x;
	int		y;
	char	*data_addr;
	void	*img_ptr;
	int		bpp;
	int		size_line;
	int		ed;

	fdf_lst_begin(&lst);
	img_ptr = mlx_new_image(mlx_list->ptr, WIDTH, HIEGHT);
	if (!(data_addr = mlx_get_data_addr(img_ptr, &bpp, &size_line, &ed)))
	{
		free_fdf_lst(&lst);
		ft_putstr_err("Something goes wrong");
	}
	y = 0;
	while (lst)	
	{
		x = 0;
		while (x + 1 < lst->max_line)
		{
			if (lst->coords[x][0] < 0 || lst->coords[x][1] + 500 < 0 || lst->coords[x][0] > WIDTH || lst->coords[x][1] + 500 > HIEGHT ||
				lst->coords[x + 1][0] < 0 || lst->coords[x + 1][1] + 500 < 0 || lst->coords[x + 1][0] > WIDTH || lst->coords[x + 1][1] + 500 > HIEGHT)
			{
				x++;
				continue ;
			}
			ft_mlx_line(&data_addr, lst->coords[x][0], lst->coords[x][1] + 500, lst->coords[x + 1][0], lst->coords[x + 1][1] + 500, size_line, bpp);
			if (lst->up)
			{
				if (!(lst->up->coords[x][0] < 0 || lst->up->coords[x][1] + 500 < 0 || lst->up->coords[x][0] > WIDTH || lst->up->coords[x][1] + 500 > HIEGHT ||
				lst->up->coords[x + 1][0] < 0 || lst->up->coords[x + 1][1] + 500 < 0 || lst->up->coords[x + 1][0] > WIDTH || lst->up->coords[x + 1][1] + 500 > HIEGHT))
				{
					ft_mlx_line(&data_addr, lst->coords[x][0], lst->coords[x][1] + 500, lst->up->coords[x][0], lst->up->coords[x][1] + 500, size_line, bpp);
				}
			}
			x++;
		}
		if (lst->down)
		{
			lst = lst->down;
			y++;
		}
		else
			break ;
	}
	mlx_put_image_to_window(mlx_list->ptr, mlx_list->win, img_ptr, 0, 0);
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