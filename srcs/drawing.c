/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 16:15:24 by mburl             #+#    #+#             */
/*   Updated: 2019/12/11 14:01:21 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		draw_dots_h(t_data *data, int iter, t_fdf *lst)
{
	long	color;
	int		x;
	int		y;
	int		i;

	color = 0x00FF00;
	if (lst->coords[iter][3] == 1)
		color = 0xFFFFFF;
	y = lst->coords[iter][1] + HIEGHT / 2;
	x = lst->coords[iter][0] + WIDTH / 2;
	if (!(x < 0 || x >= WIDTH || y < 0 || y >= HIEGHT))
	{
		i = (x * data->bpp / 8) + (y * data->size_line);
		data->data_addr[i] = color;
		data->data_addr[++i] = color >> 8;
		data->data_addr[++i] = color >> 16;
	}
}

void			draw_dots(t_data *data, t_fdf *lst)
{
	int		iter;

	fdf_lst_begin(&lst);
	data->mlx->img = mlx_new_image(data->mlx->ptr, WIDTH, HIEGHT);
	data->data_addr = mlx_get_data_addr(data->mlx->img, &data->bpp,
									&data->size_line, &data->ed);
	while (lst)
	{
		iter = 0;
		while (iter < lst->max_line)
			draw_dots_h(data, iter++, lst);
		if (lst->down)
			lst = lst->down;
		else
			break ;
	}
	mlx_put_image_to_window(data->mlx->ptr, data->mlx->win,
							data->mlx->img, 0, 0);
}

void			draw_map(t_fdf *lst, t_mlx *mlx_list, t_data *data)
{
	int		x;

	fdf_lst_begin(&lst);
	data->mlx->img = mlx_new_image(mlx_list->ptr, WIDTH, HIEGHT);
	data->data_addr = mlx_get_data_addr(data->mlx->img, &data->bpp,
										&data->size_line, &data->ed);
	data->y_mid = HIEGHT / 2;
	data->x_mid = WIDTH / 2;
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

void			scaling(t_fdf *lst, double scale_x,
						double scale_y, double scale_z)
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
