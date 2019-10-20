/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_work.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 15:18:18 by mburl             #+#    #+#             */
/*   Updated: 2019/10/18 15:35:19 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_fdf	ft_create_node(int x, int y, int z)
{
	t_fdf	*node;

	node = (t_fdf *)malloc(sizeof(t_fdf));
	node->x = x;
	node->y = y;
	node->z = z;
	node->up = NULL;
	node->left = NULL;
	node->right = NULL;
	node->down = NULL;
	return (node);
}