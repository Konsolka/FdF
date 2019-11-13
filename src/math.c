/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 19:29:20 by mburl             #+#    #+#             */
/*   Updated: 2019/11/13 20:44:17 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

double		**create4x4_matrix(void)
{
	double	**matrix;
	int		i;
	int		j;

	i = 0;
	matrix = (double **)malloc(sizeof(double *) * 4);
	while (i < 4)
	{
		j = 0;
		matrix[i] = (double *)malloc(sizeof(double) * 4);
		while (j < 4)
		{
			matrix[i][j] = 0;
			j++;
		}
		i++;
	}
	matrix[0][0] = 1 / tan(FOV / 2);
	matrix[1][1] = (HIEGHT / WIDTH) / tan(FOV * 0.5);
	matrix[2][2] = (F_NEAR + F_FAR) / (F_NEAR - F_FAR);
	matrix[3][2] = (2 * F_NEAR * F_FAR)/ (F_NEAR - F_FAR);
	matrix[2][3] = 	-1.0;
	return (matrix);
}

/*
**	0 - lower x
**	1 - lower y
**	2 - max x
**	3 - max y
*/
double	*min_max(t_fdf *lst)
{
	double	*arr;

	if (!(arr = (double *)malloc(sizeof(double) * 4)))
		ft_putstr_err("error in memory allocation");
	ft_lst_begin(&lst);
	arr[0] = 0.0;
	arr[1] = 0.0;
	arr[2] = 0.0;
	arr[3] = 0.0;
	while (lst)
	{
		if (lst->coords[0][0] < arr[0])
			arr[0] = lst->coords[0][0];
		else if (lst->coords[0][0] > arr[2])
			arr[2] = lst->coords[0][0];
		if (lst->coords[1][0] < arr[1])
			arr[1] = lst->coords[1][0];
		else if (lst->coords[1][0] > arr[3])
			arr[3] = lst->coords[1][0];
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
	return (arr);
}

void	preparations(t_fdf *lst)
{
	int		temp[2];
	double	**T_matrix;
	double	**matrix_temp0;
	double	**matrix_temp1;

	temp[0] = 4;
	temp[1] = 4;
	matrix_temp0 = f_matrix_a(1);
	matrix_temp1 = f_matrix_b(0);
	T_matrix = matrix_mul(matrix_temp0, matrix_temp1, temp);
	// ft_del_double_arr(matrix_temp0, 4);
	// ft_del_double_arr(matrix_temp1, 4);
	matrix_temp0 = f_matrix_z(-0.5);
	T_matrix = matrix_mul(T_matrix, matrix_temp0, temp);
	temp[1] = 1;
	// ft_del_double_arr(matrix_temp0, 4);
	matrix_temp0 = create4x4_matrix();
	while (lst)
	{
		lst->coords = matrix_mul(T_matrix, lst->coords, temp);
		lst->coords = matrix_mul(matrix_temp0, lst->coords, temp);
		if (!lst->prev)
		{
			if (lst->up)
			{
				while (lst->next)
					lst = lst->next;
				lst = lst->up;
			}
			else
				break ;
		}
		else
			lst = lst->prev;
	}
	// ft_del_double_arr(matrix_temp0, 4);
	ft_del_double_arr(T_matrix, 4);
}