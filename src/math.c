/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 19:29:20 by mburl             #+#    #+#             */
/*   Updated: 2019/11/12 19:34:05 by mburl            ###   ########.fr       */
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
