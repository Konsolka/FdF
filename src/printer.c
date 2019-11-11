/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:13:49 by mburl             #+#    #+#             */
/*   Updated: 2019/11/11 18:23:06 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <unistd.h>

// 1: LMB		2:RMB		3:MMB		4:down		5:up
int		move_obj(int button, int x, int y, void *param)
{
	t_data	*data;
	t_fdf	*lst;
	t_fdf	*temp;
	
	data = (t_data *)param;
	lst = data->lst;
	//  window must be cleaned
	if (button == 4)
	{
		data->scale += 1;
		temp = scaling(lst, data->scale);
		mlx_clear_window(data->mlx->ptr, data->mlx->win);
		drawing_map(lst, data->mlx);
	}
	(void)x;
	(void)y;
	return (0);	
}
//needs scaling matrix
// and scale to % of screen size
void	make_window(t_fdf *lst)
{
	void	*mlx_ptr;
	void	*mlx_win;
	t_data	*data;
	t_mlx	*mlx_list;
	t_fdf	*temp;

	mlx_ptr = mlx_init();
	mlx_win = mlx_new_window(mlx_ptr, HIEGHT, WIDTH, "FdF");
	mlx_list = (t_mlx *)malloc(sizeof(t_mlx));
	mlx_list->ptr = mlx_ptr;
	mlx_list->win = mlx_win;
	data = (t_data *)malloc(sizeof(t_data));

	data->lst = lst;
	data->mlx = mlx_list;
	data->scale = 5;
	temp = scaling(lst, data->scale);
	drawing_map(lst, mlx_list);
	////
	mlx_mouse_hook(mlx_win, move_obj, data);
	mlx_loop(mlx_ptr);
}