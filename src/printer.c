/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:13:49 by mburl             #+#    #+#             */
/*   Updated: 2019/12/10 18:37:32 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <unistd.h>

// 1: LMB		2:RMB		3:MMB		4:down		5:up
int		scale_obj(int button, int x, int y, void *param)
{
	t_data	*data;
	t_fdf	*lst;
	
	data = (t_data *)param;
	lst = data->lst;
	if (button == 4)
		scaling(lst, 1.2, 1.2, 1.2);
	if (button == 5)
		scaling(lst, 0.8, 0.8, 0.8);
	mlx_clear_window(data->mlx->ptr, data->mlx->win);
	if (data->dot)
		draw_dots(data, data->lst);
	else
		draw_map(lst, data->mlx, data->min_max, data);
	(void)x;
	(void)y;
	return (0);	
}
// //needs scaling matrix
// // and scale to % of screen size

void	move(t_fdf *lst, double d, int vert)
{
	int		i;

	fdf_lst_begin(&lst);
	while (lst)
	{
		i = 0;
		while (i < lst->max_line)
		{
			lst->coords[i][0] += (vert == 1 ? 0 : d);
			lst->coords[i][1] += (vert == 1 ? d : 0);
			i++;
		}
		if (lst->down)
			lst = lst->down;
		else
			break ;
	}
}

void	rotate(char x, double angle, t_fdf *lst)
{
	double	**matrix;
	int		i;

	matrix = ft_matrix_rotation(angle, x);
	fdf_lst_begin(&lst);
	while (lst)
	{
		i = 0;
		while (i < lst->max_line)
		{
			rotate_global(lst->coords[i], matrix);
			i++;
		}
		if (lst->down)
			lst = lst->down;
		else
			break ;
	}
}
// down:125 up: 126 left:123 right" 124

int		mlx_close(t_data *data)
{
	mlx_destroy_image(data->mlx->ptr, data->mlx->img);
	mlx_destroy_window(data->mlx->ptr, data->mlx->win);
	free_fdf_lst(&data->lst);
	free(data->min_max);
	free(data->mlx);
	free(data);
	exit(0);
}

int		key_parse(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key == 126)
	 	move(data->lst, -5, 1);
	else if (key == 125)
		move(data->lst, 5, 1);
	else if (key == 123)
		move(data->lst, -5, 0);
		// rotate('y', 0.1, data->lst);
	else if (key == 124)
		move(data->lst, 5, 0);
	else if (key == 53)
		mlx_close(data);
	// else if (key == 0)
	// 	rotate('y', 0.1, data->lst);
	if (key == 5 || data->dot)
	{
		if (key == 5 && data->dot)
			data->dot = 0;
		else
		{
		data->dot = 1;
		mlx_destroy_image(data->mlx->ptr, data->mlx->img);
		mlx_clear_window(data->mlx->ptr, data->mlx->win);
		draw_dots(data, data->lst);
		return (1);
		}
	}
	mlx_clear_window(data->mlx->ptr, data->mlx->win);
	draw_map(data->lst, data->mlx, data->min_max, data);
	return (1);
}
void	make_window(t_fdf *lst)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	data->mlx = (t_mlx *)malloc(sizeof(t_mlx));
	data->mlx->ptr = mlx_init();
	data->mlx->win = mlx_new_window(data->mlx->ptr, WIDTH, HIEGHT, "FdF");
	data->lst = lst;
	data->min_max = min_max(lst);
	if (data->min_max[2] * HIEGHT / (data->min_max[3] - data->min_max[1]) < WIDTH)
		scaling(lst, HIEGHT / (data->min_max[3] - data->min_max[1]), HIEGHT / (data->min_max[3] - data->min_max[1]), 20);
	else
		scaling(lst, WIDTH / data->min_max[2], WIDTH / data->min_max[2], 20);
	free(data->min_max);
	data->min_max = min_max(lst);
	data->dot = 0;
	int f;

	f = 0;
	while (f < 4)
	{
		printf("%f ", data->min_max[f]);
		f++;
	}
	draw_map(lst, data->mlx, data->min_max, data);
	mlx_mouse_hook(data->mlx->win, scale_obj, data);
	mlx_hook(data->mlx->win, 2, 0L, key_parse, data);
	mlx_loop(data->mlx->ptr);
}