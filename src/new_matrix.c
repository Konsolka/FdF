/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_matrix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 13:06:02 by mburl             #+#    #+#             */
/*   Updated: 2019/12/05 15:18:25 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	ft_free_matrix(double **m)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(m[i]);
		++i;
	}
	free(m);
	m = NULL;
}

double	**ft_identity_matrix(int fill, int fill_diagonal)
{
	double	**m;
	t_i		i;

	if (!(m = (double**)malloc(sizeof(double*) * 4)))
		return (0);
	i.y = 0;
	while (i.y < 4)
	{
		if (!(m[i.y] = (double*)malloc(sizeof(double) * 4)))
			return (0);
		i.x = 0;
		while (i.x < 4)
		{
			m[i.y][i.x] = (i.x != i.y) ? fill : fill_diagonal;
			++i.x;
		}
		++i.y;
	}
	return (m);
}

double	**ft_matrix_rotation(double x, char axis)
{
	double	**m;

	m = ft_identity_matrix(0, 1);
	if (axis == 'x')
	{
		m[1][1] = cos(x);
		m[1][2] = -sin(x);
		m[2][2] = cos(x);
		m[2][1] = sin(x);
	}
	else if (axis == 'y')
	{
		m[0][0] = cos(x);
		m[0][2] = sin(x);
		m[2][0] = -sin(x);
		m[2][2] = cos(x);
	}
	else if (axis == 'z')
	{
		m[0][0] = cos(x);
		m[0][1] = -sin(x);
		m[1][0] = sin(x);
		m[1][1] = cos(x);
	}
	return (m);
}
