/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 13:19:36 by mburl             #+#    #+#             */
/*   Updated: 2019/10/25 14:21:19 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

/*
**	b_data  = [i, j] where i is rows j is column
*/
double	**matrix_mul(double **a, double **b, int *b_data)
{
	int		i;
	int		j;
	int		k;
	double	**res;

	i = 0;
	res = (double **)malloc(sizeof(double *) * b_data[0]);
	while (i < b_data[0])
	{
		j = 0;
		res[i] = (double *)malloc(sizeof(double ) * b_data[1]);
		while (j < b_data[1])
		{
			res[i][j] = 0;
			k = 0;
			while (k < b_data[0])
			{
				res[i][j] += a[i][k] * b[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (res);
}

double	**f_matrix_a(double a)
{
	double	**matrix_a;
	int		i;
	int		j;

	i = 0;
	matrix_a = (double **)malloc(sizeof(double *) * 4);
	while (i < 4)
	{
		j = 0;
		matrix_a[i] = (double *)malloc(sizeof(double) * 4);
		while (j < 4)
		{
			matrix_a[i][j] = 0;
			j++;
		}
		i++;
	}
	matrix_a[0][0] = 1;
	matrix_a[1][1] = cos(a);
	matrix_a[1][2] = sin(a);
	matrix_a[2][1] = -sin(a);
	matrix_a[2][2] = cos(a);
	i = 0;
	while (i < 4)
		matrix_a[i++][3] = 1;
	return (matrix_a);
}

double	**f_matrix_b(double b)
{
	double	**matrix_b;
	int		i;
	int		j;

	i = 0;
	matrix_b = (double **)malloc(sizeof(double *) * 4);
	while (i < 4)
	{
		j = 0;
		matrix_b[i] = (double *)malloc(sizeof(double) * 4);
		while (j < 4)
		{
			matrix_b[i][j] = 0;
			j++;
		}
		i++;
	}
	matrix_b[0][0] = cos(b);
	matrix_b[0][2] = -sin(b);
	matrix_b[1][1] = 1;
	matrix_b[2][0] = sin(b);
	matrix_b[2][2] = cos(b);
	i = 0;
	while (i < 4)
		matrix_b[i++][3] = 1;
	return (matrix_b);
}