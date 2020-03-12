/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_work.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:13:49 by mburl             #+#    #+#             */
/*   Updated: 2019/12/11 17:34:43 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <unistd.h>

/*
**	destrying image & window
**	freeing all data
*/

int			mlx_close(t_data *data)
{
	mlx_destroy_image(data->mlx->ptr, data->mlx->img);
	mlx_destroy_window(data->mlx->ptr, data->mlx->win);
	free_fdf_lst(&data->lst);
	free(data->min_max);
	free(data->mlx);
	free(data);
	exit(0);
}

/*
**	key	parser
**
**	126		up
**	125		down
**	123		left
**	124		right
**	53		ESC
**	5		G
*/

int			key_parse(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key == 126 || key == 125)
		move(data->lst, (key == 126) ? -MOVE : MOVE, 1);
	else if (key == 123 || key == 124)
		move(data->lst, (key == 123) ? -MOVE : MOVE, 0);
	else if (key == 53)
		mlx_close(data);
	mlx_destroy_image(data->mlx->ptr, data->mlx->img);
	mlx_clear_window(data->mlx->ptr, data->mlx->win);
	if (key == 5 || data->dot)
	{
		if (key == 5 && data->dot)
			data->dot = 0;
		else
		{
			data->dot = 1;
			draw_dots(data, data->lst);
			return (1);
		}
	}
	draw_map(data->lst, data->mlx, data);
	return (1);
}

/*
**	data initialization
**	see fdf.h
*/

t_data		*init_data(t_fdf *lst)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	data->mlx = (t_mlx *)malloc(sizeof(t_mlx));
	data->mlx->ptr = mlx_init();
	data->mlx->win = mlx_new_window(data->mlx->ptr, WIDTH, HIEGHT, "FdF");
	data->lst = lst;
	data->min_max = min_max(lst);
	data->dot = 0;
	return (data);
}

/*
**	initializating window
**	creating struct data and putting there all data
**	scaling obj to size of the screen
**	moving obj to the center
*/

void		make_window(t_fdf *lst)
{
	t_data	*data;

	data = init_data(lst);
	if (data->min_max[2] * HIEGHT /
			(data->min_max[3] - data->min_max[1]) < WIDTH)
		scaling(lst, HIEGHT / (data->min_max[3] - data->min_max[1]),
				HIEGHT / (data->min_max[3] - data->min_max[1]),
				HIEGHT / (data->min_max[3] - data->min_max[1]));
	else
		scaling(lst, WIDTH / data->min_max[2], WIDTH / data->min_max[2],
					WIDTH / data->min_max[2]);
	free(data->min_max);
	data->min_max = min_max(lst);
	move(lst, -data->min_max[2] / 2, 0);
	move(lst, -(data->min_max[3] + data->min_max[1]) / 2, 1);
	draw_map(lst, data->mlx, data);
	mlx_mouse_hook(data->mlx->win, scale_obj, data);
	mlx_hook(data->mlx->win, 2, 0L, key_parse, data);
	mlx_hook(data->mlx->win, 17, 0L, mlx_close, data);
	mlx_loop(data->mlx->ptr);
}
