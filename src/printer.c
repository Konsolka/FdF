/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:13:49 by mburl             #+#    #+#             */
/*   Updated: 2019/10/25 14:26:25 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	ft_mlx_line(double x1, double y1, double x2, double y2, t_mlx *lst)
{
	double	deltx;
	double	delty;
	double	signx;
	double	signy;
	double	error;

	deltx = fabs(x2 - x1);
	delty = fabs(y2 - y1);
	signx = x1 < x2 ? 1 : -1;
	signy = y1 < y2 ? 1 : -1;
	error = deltx - delty;
	mlx_pixel_put(lst->ptr, lst->win, x2, y2, 0xFFFFFF);
	while (x1 != x2 || y1 != y2)
	{
		mlx_pixel_put(lst->ptr, lst->win, x1, y1, 0xFFFFFF);
		double error2 = error * 2;
		if (error2 > delty)
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

void	print_map(t_fdf *lst)
{
	void	*mlx_ptr;
	void	*mlx_win;
	t_mlx	*mlx_list;
	double	scale_x;
	double	scale_y;

	scale_x = 0.5 * WIDTH;
	scale_y = 0.5 * HIEGHT;
	mlx_ptr = mlx_init();
	mlx_win = mlx_new_window(mlx_ptr, HIEGHT, WIDTH, "FdF");
	mlx_list = (t_mlx *)malloc(sizeof(t_mlx));
	mlx_list->ptr = mlx_ptr;
	mlx_list->win = mlx_win;
	lst = lst->next;
	while (lst->next || lst->down)
	{
		ft_mlx_line(lst->prev->coords[0][0], lst->prev->coords[1][0], lst->coords[0][0], lst->coords[1][0], mlx_list);
		if (!lst->next)
		{
			if (lst->down)
			{
				while (lst->prev->prev)
					lst = lst->prev;
				lst = lst->down;
			}
			else
				break ;
		}
		else
			lst = lst->next;
	}
	mlx_loop(mlx_ptr);
}