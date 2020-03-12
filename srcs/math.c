/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 19:29:20 by mburl             #+#    #+#             */
/*   Updated: 2020/03/12 11:31:19 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void		compare_coords(t_fdf *lst, double *arr)
{
	while (lst)
	{
		if (lst->x < arr[0])
			arr[0] = lst->x;
		else if (lst->y < arr[1])
			arr[1] = lst->y;
		else if (lst->x > arr[2])
			arr[2] = lst->x;
		else if (lst->y > arr[3])
			arr[3] = lst->y;
		lst = lst->next;
	}
}

/*
**	0 - min x
**	1 - min y
**	2 - max x
**	3 - max y
*/

double			*min_max(t_fdf *lst)
{
	double	*arr;

	arr = (double *)malloc(sizeof(double) * 4);
	arr[0] = 0.0;
	arr[1] = 0.0;
	arr[2] = 0.0;
	arr[3] = 0.0;
	compare_coords(lst, arr);
	return (arr);
}

// void			matrix_mul(double **rotate_matrix, t_vector *vec)
// {
// 	vec->x = rotate_matrix[0][0] * vec->x + rotate_matrix[0][1] * vec->y +
// 				rotate_matrix[0][2] * vec->z;
// 	vec->y = rotate_matrix[1][0] * vec->x + rotate_matrix[1][1] * vec->y +
// 				rotate_matrix[1][2] * vec->z;
// 	vec->z = rotate_matrix[2][0] * vec->x + rotate_matrix[2][1] * vec->y +
// 				rotate_matrix[2][2] * vec->z;
// }

// void			preparations(t_fdf *lst)
// {
// 	int		i;
// 	double	**matrix_z;
// 	double	**matrix_x;

// 	fdf_lst_begin(&lst);
// 	matrix_x = ft_matrix_rotation(1, 'x');
// 	matrix_z = ft_matrix_rotation(-0.5, 'z');
// 	while (lst)
// 	{
// 		i = 0;
// 		while (i < lst->max_line)
// 		{
// 			rotate_global(lst->coords[i], matrix_z);
// 			rotate_global(lst->coords[i], matrix_x);
// 			i++;
// 		}
// 		if (lst->down)
// 			lst = lst->down;
// 		else
// 			break ;
// 	}
// 	ft_free_matrix(matrix_x);
// 	ft_free_matrix(matrix_z);
// }
