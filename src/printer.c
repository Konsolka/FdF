/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:13:49 by mburl             #+#    #+#             */
/*   Updated: 2019/11/12 17:09:13 by mburl            ###   ########.fr       */
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
	
	data = (t_data *)param;
	lst = data->lst;
	//  window must be cleaned
	if (button == 4)
	{
		// scaling(lst, 1 / data->scale);
		scaling(lst, 1.2, 1.2, 1.2);
		mlx_clear_window(data->mlx->ptr, data->mlx->win);
		drawing_map(lst, data->mlx);
	}
	if (button == 5)
	{
		scaling(lst, 0.8, 0.8, 0.8);
		mlx_clear_window(data->mlx->ptr, data->mlx->win);
		drawing_map(lst, data->mlx);
	}
	(void)x;
	(void)y;
	return (0);	
}
//needs scaling matrix
// and scale to % of screen size

void	move(t_fdf *lst, double d, int vert)
{
	int	temp[2];
	double x;
	double y;

	ft_lst_begin(&lst);
	x = 0;
	y = 0;
	temp[0] = 4;
	temp[1] = 1;
	(void)vert;
	// if (vert)
	// 	y = d;
	// else
	// 	x = d;
	while (lst)
	{
		lst->coords[1][0] += 0;
		lst->coords[3][0] += d;
		if (!lst->next)
		{
			if (lst->down)
			{
				while (lst->prev)
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

int		key_parse(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key == 123)
		move(data->lst, -5, 0);
	mlx_clear_window(data->mlx->ptr, data->mlx->win);
	drawing_map(data->lst, data->mlx);
	return (0);
}
// down:125 up: 126 left:123 right" 124
void	make_window(t_fdf *lst)
{
	void	*mlx_ptr;
	void	*mlx_win;
	t_data	*data;
	t_mlx	*mlx_list;

	mlx_ptr = mlx_init();
	mlx_win = mlx_new_window(mlx_ptr, HIEGHT, WIDTH, "FdF");
	mlx_list = (t_mlx *)malloc(sizeof(t_mlx));
	mlx_list->ptr = mlx_ptr;
	mlx_list->win = mlx_win;
	data = (t_data *)malloc(sizeof(t_data));

	data->lst = lst;
	data->mlx = mlx_list;
	scaling(lst, 1.2, 1.2, 1.2);
	drawing_map(lst, mlx_list);
	////
	mlx_mouse_hook(mlx_win, move_obj, data);
	mlx_key_hook(mlx_win, key_parse, data);
	mlx_loop(mlx_ptr);
}