/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 16:15:24 by mburl             #+#    #+#             */
/*   Updated: 2019/12/05 17:16:23 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void	ft_mlx_line(int x1, int y1, int x2, int y2, t_mlx *lst)
{
	int		deltx;
	int		delty;
	int		signx;
	int		signy;
	int		error;

	deltx = abs(x2 - x1);
	delty = abs(y2 - y1);
	signx = x1 < x2 ? 1 : -1;
	signy = y1 < y2 ? 1 : -1;
	error = deltx - delty;
	mlx_pixel_put(lst->ptr, lst->win, x2, y2, 0xFFFFFF);
	while (x1 != x2 || y1 != y2)
	{
		mlx_pixel_put(lst->ptr, lst->win, x1, y1, 0xFFFFFF);
		double error2 = error * 2;
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

void	draw_map(t_fdf *lst, t_mlx *mlx_list)
{
	int		i;
	int		x;
	int		y;
	char	*data_addr;
	void	*img_ptr;
	int		bpp;
	int		size_line;
	int		ed;
	long	color;

	fdf_lst_begin(&lst);
	color = 255255255255;
	img_ptr = mlx_new_image(mlx_list->ptr, WIDTH, HIEGHT);
	if (!(data_addr = mlx_get_data_addr(img_ptr, &bpp, &size_line, &ed)))
	{
		free_fdf_lst(&lst);
		ft_putstr_err("Something goes wrong");
	}
	y = 0;
		ft_putnbr(size_line);
	while (lst)	
	{
		x = 0;
		while (x < lst->max_line)
		{
			i = ((int)(lst->coords[x][0] + 20) * bpp / 8) + ((int)(lst->coords[x][1] + 20) * size_line);
			if (i < 0 || i > 20)
			{
				x++;
				continue ;
			}
			data_addr[i] = color;
			data_addr[++i] = color >> 8;
			data_addr[++i] = color >> 16;
			x++;
		}
		data_addr[i] = color;
		if (lst->down)
		{
			lst = lst->down;
			y++;
		}
		else
			break ;
	}
	free(data_addr);
	mlx_put_image_to_window(mlx_list->ptr, mlx_list->win, img_ptr, 0, 0);
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