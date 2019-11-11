/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:13:49 by mburl             #+#    #+#             */
/*   Updated: 2019/11/11 16:34:21 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <unistd.h>

// 1: LMB		2:RMB		3:MMB		4:down		5:up
int		move_obj(int button, int x, int y, void *param)
{
	printf("\nb:%i, x = %i, y = %i", button, x, y);
	return (0);	
}
//needs scaling matrix
// and scale to % of screen size
void	make_window(t_fdf *lst)
{
	void	*mlx_ptr;
	void	*mlx_win;
	t_mlx	*mlx_list;
	int		temp[2];

	mlx_ptr = mlx_init();
	mlx_win = mlx_new_window(mlx_ptr, HIEGHT, WIDTH, "FdF");
	mlx_list = (t_mlx *)malloc(sizeof(t_mlx));
	mlx_list->ptr = mlx_ptr;
	mlx_list->win = mlx_win;

	while (lst)
	{
		if (lst->prev)
			lst = lst->prev;
		else
		{
			if (lst->up)
				lst = lst->up;
			else
				break ;
		}
	}
	lst = lst->next;
	while (lst->next || lst->down)
	{
		temp[0] = 4;
		temp[1] = 1;		
		matrix_mul(scaling_matrix(50))			
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
	////
	mlx_mouse_hook(mlx_win, move_obj, mlx_list);
	mlx_loop(mlx_ptr);
}