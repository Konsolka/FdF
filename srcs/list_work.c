/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_work.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 15:18:18 by mburl             #+#    #+#             */
/*   Updated: 2020/03/12 10:56:43 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_fdf			*createNode(double x, double y, double z)
{
	t_fdf	*node;

	if (!(node = (t_fdf *)malloc(sizeof(*node))))
		fatalError("Error in allocation node");
	node->next = NULL;
	node->x = x;
	node->y = y;
	node->z = z;
	return (node);
}

void			addNode(t_fdf **alst, t_fdf *node)
{
	node->next = *alst;
	*alst = node;
}
