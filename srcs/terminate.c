/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 10:33:09 by mburl             #+#    #+#             */
/*   Updated: 2020/03/12 11:05:21 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

void		fatalError(char *str)
{
	ft_putstr_err(str);
	ft_putstr_err("\n");
	exit(-1);
}

void		printList(t_fdf *lst) //////////
{
	while (lst)
	{
		printf("%f\t%f\t%f\n", lst->x, lst->y, lst->z); //////     PRINTF
		lst = lst->next;
	}
}