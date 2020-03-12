/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 16:15:24 by mburl             #+#    #+#             */
/*   Updated: 2020/03/12 13:13:58 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// static void		draw_dots_h(t_data *data, int iter, t_fdf *lst)
// {
// 	long	color;
// 	int		x;
// 	int		y;
// 	int		i;

// 	color = 0x00FF00;
// 	if (lst->coords[iter][3] == 1)
// 		color = 0xFFFFFF;
// 	y = lst->coords[iter][1] + HIEGHT / 2;
// 	x = lst->coords[iter][0] + WIDTH / 2;
// 	if (!(x < 0 || x >= WIDTH || y < 0 || y >= HIEGHT))
// 	{
// 		i = (x * data->bpp / 8) + (y * data->size_line);
// 		data->data_addr[i] = color;
// 		data->data_addr[++i] = color >> 8;
// 		data->data_addr[++i] = color >> 16;
// 	}
// }

// void			draw_dots(t_data *data, t_fdf *lst)
// {
// 	int		iter;

// 	fdf_lst_begin(&lst);
// 	data->mlx->img = mlx_new_image(data->mlx->ptr, WIDTH, HIEGHT);
// 	data->data_addr = mlx_get_data_addr(data->mlx->img, &data->bpp,
// 									&data->size_line, &data->ed);
// 	while (lst)
// 	{
// 		iter = 0;
// 		while (iter < lst->max_line)
// 			draw_dots_h(data, iter++, lst);
// 		if (lst->down)
// 			lst = lst->down;
// 		else
// 			break ;
// 	}
// 	mlx_put_image_to_window(data->mlx->ptr, data->mlx->win,
// 							data->mlx->img, 0, 0);
// }

void			makeLine(t_data *data, t_point first, t_point second, int color)
{
	float		dx;
	float		dy;
	t_point		point;
	float		D;
	int			i;

	dx = second.x - first.x;
	dy = second.y - first.y;
	D = 2 * dy - dx;
	point.y = first.y;
	point.x = first.x;
	while (point.x <= second.x)
	{
		i = (point.x * data->bpp / 8) + (point.y * data->size_line);
		data->data_addr[i] = color;
		data->data_addr[++i] = color >> 8;
		data->data_addr[++i] = color >> 16;
		data->data_addr[++i] = 0;
		if (D > 0)
		{
			point.y++;
			D -= 2 * dx;
		}
		D += 2 * dy;
		point.x++;
	}
}

t_point			setPoint(float x, float y)
{
	t_point		p;

	p.x = x;
	p.y = y;
	return (p);
}

void			draw_map(t_fdf *lst, t_mlx *mlx_list, t_data *data)
{
	int		i;
	t_point	pointf;

	data->mlx->img = mlx_new_image(mlx_list->ptr, WIDTH, HIEGHT);
	data->data_addr = mlx_get_data_addr(data->mlx->img, &data->bpp,
										&data->size_line, &data->ed);
	data->y_mid = HIEGHT / 2;
	data->x_mid = WIDTH / 2;
	while (data->lst->next)
	{
		write(1, "1", 1);
		makeLine(data, setPoint(data->lst->x, data->lst->y), setPoint(data->lst->next->x, data->lst->next->y), 0xFFFFFF);
		data->lst = data->lst->next;
		write(1, " 1\n", 3);
	}
	mlx_put_image_to_window(mlx_list->ptr, mlx_list->win, data->mlx->img, 0, 0);
	mlx_destroy_image(mlx_list->ptr, mlx_list->img);
}

void			scaleCoords(t_fdf *lst, double scale_x,
						double scale_y, double scale_z)
{
	t_fdf	*save;

	save = lst;
	while (lst)
	{
		lst->x *= scale_x;
		lst->y *= scale_y;
		lst->z *= scale_z;
		lst = lst->next;		
	}
}
