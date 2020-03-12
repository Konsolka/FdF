/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 14:20:54 by mburl             #+#    #+#             */
/*   Updated: 2020/03/12 13:04:09 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// void			rotate(char x, double angle, t_fdf *lst)
// {
// 	double	**matrix;
// 	int		i;

// 	matrix = ft_matrix_rotation(angle, x);
// 	fdf_lst_begin(&lst);
// 	while (lst)
// 	{
// 		i = 0;
// 		while (i < lst->max_line)
// 		{
// 			rotate_global(lst->coords[i], matrix);
// 			i++;
// 		}
// 		if (lst->down)
// 			lst = lst->down;
// 		else
// 			break ;
// 	}
// 	ft_free_matrix(matrix);
// }

// void			rotate_global(double *coords, double **rotate_matrix)
// {
// 	t_vector	vec;

// 	vec.x = coords[0];
// 	vec.y = coords[1];
// 	vec.z = coords[2];
// 	matrix_mul(rotate_matrix, &vec);
// 	coords[0] = vec.x;
// 	coords[1] = vec.y;
// 	coords[2] = vec.z;
// }

// int				scale_obj(int button, int x, int y, void *param)
// {
// 	t_data	*data;
// 	t_fdf	*lst;

// 	data = (t_data *)param;
// 	lst = data->lst;
// 	if (button == 4)
// 		scaling(lst, 1.2, 1.2, 1.2);
// 	if (button == 5)
// 		scaling(lst, 0.8, 0.8, 0.8);
// 	mlx_clear_window(data->mlx->ptr, data->mlx->win);
// 	if (data->dot)
// 		draw_dots(data, data->lst);
// 	else
// 		draw_map(lst, data->mlx, data);
// 	(void)x;
// 	(void)y;
// 	return (0);
// }

void			move(t_fdf *lst, double d, int vert)
{
	while (lst)
	{
		lst->x += (vert == 1 ? 0 : d);
		lst->y += (vert == 1 ? d : 0);
		lst = lst->next;
	}
}
