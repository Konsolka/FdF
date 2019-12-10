/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 16:15:24 by mburl             #+#    #+#             */
/*   Updated: 2019/12/10 19:53:15 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void	ft_mlx_line(t_data *data, double *first, double *second)
{
	int		deltx;
	int		delty;
	int		signx;
	int		signy;
	int		error;
	long	color;
	int		i;

	int		x1;
	int		y1;
	int		x2;
	int		y2;

	x1 = first[0] + data->x_mid;
	y1 = first[1] + data->y_mid;
	x2 = second[0] + data->x_mid;
	y2 = second[1] + data->y_mid;

	deltx = abs(x2 - x1);
	delty = abs(y2 - y1);
	signx = x1 < x2 ? 1 : -1;
	signy = y1 < y2 ? 1 : -1;
	error = deltx - delty;
	color = 0x2AA2A5;
	if (first[3] == second[3])
	{
		if (first[3] == 1)
			color = 0xFFFFFF;
		else
			color = 0x008000;
	}
	if (!(x2 < 0 || y2 < 0 || x2 >= WIDTH || y2 >= HIEGHT))
	{
		data->data_addr[((x2 * data->bpp / 8) + (y2 * data->size_line))] = color;
		data->data_addr[(1 + (x2 * data->bpp / 8) + (y2 * data->size_line))] = color >> 8;
		data->data_addr[(2 + (x2 * data->bpp / 8) + (y2 * data->size_line))] = color >> 16;
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
		i = (x1 * data->bpp / 8) + (y1 * data->size_line);
		data->data_addr[i] = color;
		data->data_addr[++i] = color >> 8;
		data->data_addr[++i] = color >> 16;
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
	while (lst)
	{
		iter = 0;
		while (iter < lst->max_line)
		{
		color = 0x00FF00;
			y = lst->coords[iter][1] + HIEGHT / 2 - (int)(data->min_max[3] + data->min_max[1]) / 2;
			x = lst->coords[iter][0] + WIDTH / 2 - (int)(data->min_max[2] + data->min_max[0]) / 2;
			if (x < 0 || x >= WIDTH || y < 0 || y >= HIEGHT)
			{
				iter++;
				continue ;
			}
			i = (x * data->bpp / 8) + (y * data->size_line);
			if (lst->coords[iter][3] == 1)
				color = 0xFFFFFF;
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

	fdf_lst_begin(&lst);
	data->mlx->img = mlx_new_image(mlx_list->ptr, WIDTH, HIEGHT);
	if (!(data->data_addr = mlx_get_data_addr(data->mlx->img, &data->bpp, &data->size_line, &data->ed)))
	{
		free_fdf_lst(&lst);
		ft_putstr_err("ERROR [creating new image]{mlx_get_data_addr}");
	}
	data->y_mid = HIEGHT / 2 - (int)(min_max[3] + min_max[1]) / 2;
	data->x_mid = WIDTH / 2 - (int)(min_max[2] + min_max[0]) / 2;
	while (lst)
	{
		x = 0;
		while (x < lst->max_line)
		{
			if (x + 1 < lst->max_line)
				ft_mlx_line(data, lst->coords[x], lst->coords[x + 1]);
			if (lst->up)
				ft_mlx_line(data, lst->coords[x], lst->up->coords[x]);
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