/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 16:15:24 by mburl             #+#    #+#             */
/*   Updated: 2019/12/10 17:01:02 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void	ft_mlx_line(char *data_addr, int x1, int y1, int x2, int y2, int size_line, int bpp)
{
	int		deltx;
	int		delty;
	int		signx;
	int		signy;
	int		error;
	long	color;
	int		i;

	color = 0xFFFFFF;
	deltx = abs(x2 - x1);
	delty = abs(y2 - y1);
	signx = x1 < x2 ? 1 : -1;
	signy = y1 < y2 ? 1 : -1;
	error = deltx - delty;
	if (!(x2 < 0 || y2 < 0 || x2 >= WIDTH || y2 >= HIEGHT))
	{
		data_addr[(x2 * bpp / 8) + (y2 * size_line)] = color;
		data_addr[1 + (x2 * bpp / 8) + (y2 * size_line)] = color >> 8;
		data_addr[2 + (x2 * bpp / 8) + (y2 * size_line)] = color >> 16;
	}
	while (x1 != x2 || y1 != y2)
	{
		double error2 = error * 2;
		if (x1 < 0 || y1 < 0 || x1 >= WIDTH || y1 >= HIEGHT)
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
		i = (x1 * bpp / 8) + (y1 * size_line);
		data_addr[i] = color;
		data_addr[++i] = color >> 8;
		data_addr[++i] = color >> 16;
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

void	draw_dots(t_data *data, t_fdf *lst)
{
	int		i;
	int		iter;
	long	color;
	int		x;
	int		y;

	fdf_lst_begin(&lst);
	data->mlx->img = mlx_new_image(data->mlx->ptr, WIDTH, HIEGHT);
	data->data_addr = mlx_get_data_addr(data->mlx->img, &data->bpp, &data->size_line, &data->ed);
	color = 0xFFFFFF;
	while (lst)
	{
		iter = 0;
		while (iter < lst->max_line)
		{
			y = lst->coords[iter][1] + HIEGHT / 2 - (int)(data->min_max[3] + data->min_max[1]) / 2;
			x = lst->coords[iter][0] + WIDTH / 2 - (int)(data->min_max[2] + data->min_max[0]) / 2;
			if (x < 0 || x >= WIDTH || y < 0 || y >= HIEGHT)
			{
				iter++;
				continue ;
			}
			i = (x * data->bpp / 8) + (y * data->size_line);
			data->data_addr[i] = color;
			data->data_addr[++i] = color >> 8;
			data->data_addr[++i] = color >> 16;
			iter++;
		}
		if (lst->down)
			lst = lst->down;
		else
			break ;
	}
	mlx_put_image_to_window(data->mlx->ptr, data->mlx->win, data->mlx->img, 0, 0);
}

void	draw_map(t_fdf *lst, t_mlx *mlx_list, double *min_max, t_data *data)
{
	int		x;
	int		y_mid;
	int		x_mid;

	fdf_lst_begin(&lst);
	data->mlx->img = mlx_new_image(mlx_list->ptr, WIDTH, HIEGHT);
	if (!(data->data_addr = mlx_get_data_addr(data->mlx->img, &data->bpp, &data->size_line, &data->ed)))
	{
		free_fdf_lst(&lst);
		ft_putstr_err("ERROR [creating new image]{mlx_get_data_addr}");
	}
	y_mid = HIEGHT / 2 - (int)(min_max[3] + min_max[1]) / 2;
	x_mid = WIDTH / 2 - (int)(min_max[2] + min_max[0]) / 2;
	while (lst)
	{
		x = 0;
		while (x < lst->max_line)
		{
			if (x + 1 < lst->max_line)
				ft_mlx_line(data->data_addr, lst->coords[x][0] + x_mid,
										lst->coords[x][1] + y_mid,
										lst->coords[x + 1][0] + x_mid,
										lst->coords[x + 1][1] + y_mid,
										data->size_line,
										data->bpp);
			if (lst->up)
				ft_mlx_line(data->data_addr, lst->coords[x][0] + x_mid,
										lst->coords[x][1] + y_mid,
										lst->up->coords[x][0] + x_mid,
										lst->up->coords[x][1] + y_mid,
										data->size_line,
										data->bpp);
			x++;
		}
		if (lst->down)
			lst = lst->down;
		else
			break ;
	}
	mlx_put_image_to_window(mlx_list->ptr, mlx_list->win, data->mlx->img, 0, 0);
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