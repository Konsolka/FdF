/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 10:22:10 by mburl             #+#    #+#             */
/*   Updated: 2019/12/05 14:20:28 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int		main(void)
{
	double *lst;

	lst = (double *)malloc(sizeof(double) * 10);
	lst[0] = 10.5;
	lst[1] = 10.5;
	lst[2] = 10.5;
	lst[3] = 10.5;
	lst[4] = 10.5;
	lst[5] = 10.5;
	lst[6] = 10.5;
	lst[7] = 10.5;
	lst[8] = 10.5;
	lst[9] = 10.5;

	int i;
	i = 0;
	while (lst[i])
	{
		printf("%f\n", lst[i]);
		i++;
	}
	return (0);
}