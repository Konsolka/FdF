/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 19:29:20 by mburl             #+#    #+#             */
/*   Updated: 2019/12/10 11:19:39 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

/*
**	0 - lower x
**	1 - lower y
**	2 - max x
**	3 - max y
*/
// double	*min_max(t_fdf *lst)
// {
// 	double	*arr;

// 	if (!(arr = (double *)malloc(sizeof(double) * 4)))
// 		ft_putstr_err("error in memory allocation");
// 	ft_lst_begin(&lst);
// 	arr[0] = 0.0;
// 	arr[1] = 0.0;
// 	arr[2] = 0.0;
// 	arr[3] = 0.0;
// 	while (lst)
// 	{
// 		if (lst->coords[0][0] < arr[0])
// 			arr[0] = lst->coords[0][0];
// 		else if (lst->coords[0][0] > arr[2])
// 			arr[2] = lst->coords[0][0];
// 		if (lst->coords[1][0] < arr[1])
// 			arr[1] = lst->coords[1][0];
// 		else if (lst->coords[1][0] > arr[3])
// 			arr[3] = lst->coords[1][0];
// 		if (!lst->next)
// 		{
// 			if (lst->down)
// 			{
// 				while (lst->prev->prev)
// 					lst = lst->prev;
// 				lst = lst->down;
// 			}
// 			else
// 				break ;
// 		}
// 		else
// 			lst = lst->next;
// 	}
// 	return (arr);
// }

void		matrix_mul(double **rotate_matrix, t_vector *vec)
{
	vec->x = rotate_matrix[0][0] * vec->x + rotate_matrix[0][1] * vec->y +
				rotate_matrix[0][2] * vec->z;
	vec->y = rotate_matrix[1][0] * vec->x + rotate_matrix[1][1] * vec->y +
				rotate_matrix[1][2] * vec->z;
	vec->z = rotate_matrix[2][0] * vec->x + rotate_matrix[2][1] * vec->y +
				rotate_matrix[2][2] * vec->z;
}

void	rotate_global(double *coords, double **rotate_matrix)
{
	t_vector	vec;

	vec.x = coords[0];
	vec.y = coords[1];
	vec.z = coords[2];
	matrix_mul(rotate_matrix, &vec);
	coords[0] = vec.x;
	coords[1] = vec.y;
	coords[2] = vec.z;
	ft_free_matrix(rotate_matrix);
}

void	preparations(t_fdf *lst)
{
	int i;

	fdf_lst_begin(&lst);
	while (lst)
	{
		i = 0;
		while (i < lst->max_line)
		{
			rotate_global(lst->coords[i], ft_matrix_rotation(-0.5, 'z'));
			rotate_global(lst->coords[i], ft_matrix_rotation(1, 'x'));
			rotate_global(lst->coords[i], ft_matrix_rotation(0, 'y'));
			i++;
		}
		if (lst->down)
			lst = lst->down;
		else
			break ;
	}
}