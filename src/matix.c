/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 13:19:36 by mburl             #+#    #+#             */
/*   Updated: 2019/10/22 13:32:20 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

double	**matrix_a(t_fdf *lst, double a)
{
	double	matrix_a[3][3];
	int		i;
	int		j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
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
	retrun (matrix_a);
}

