/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 13:19:36 by mburl             #+#    #+#             */
/*   Updated: 2019/12/11 12:40:12 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

/*
**	b_data  = [i, j] where i is rows j is column
**	multiplying matrix a * b matrix can be all types 1x2, 3x4
**	but should be valid
**	not valid matrix wouldn't multyplied
*/

double	**matrix_mul_b(double **a, double **b, int *b_data)
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
