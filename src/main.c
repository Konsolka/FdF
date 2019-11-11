/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 11:07:21 by mburl             #+#    #+#             */
/*   Updated: 2019/11/11 17:22:33 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

t_fdf		*read_file(int fd, t_map **map)
{
	char	*line;
	char	**coord;
	t_fdf	*lst;
	int		y;
	int 	i;

	lst = NULL;
	line = NULL;
	y = 0;
	while (get_next_line(fd, &line))
	{
		coord = ft_strsplit(line, ' ');
		i = 0;
		if (lst)
			while (lst->prev)
				lst = lst->prev;
		while (coord[i] != '\0')
		{
			if (i == 0 && lst)
				ft_fdfdown(&lst, ft_create_node(i, y, -ft_atoi(coord[i])));
			else
				ft_fdfadd(&lst, ft_create_node(i, y, -ft_atoi(coord[i])));
			i++;
		}
		y++;
	}
	(*map)->max_x = i;
	(*map)->max_y = y;
	return (lst);
}

// int			print_map(t_fdf *lst)
// {
		
// 	return (0);
// }

/*	Projection:
**
**	1/ tan(O/2)				0				0										0
**	0						p/ tan(O/2)		0										0					p = ratio (16/9)(4/4)
**	0						0				n + f / n - f							2nf/ n - f
**	0						0				-1										0
**
*/
int			main(int ac, char **av)
{
	t_fdf	*lst;
	double	**T_matrix;
	int		temp[2];
	t_map	*map;
	
	if (ac != 2)
		ft_putstr_err("Usage : ./fdf <filename> [ case_size z_size ]\n");
	map = (t_map *)malloc(sizeof(t_map));
	if ((lst = read_file(open(av[1], O_RDONLY), &map)) == NULL)
	{
		free(map);
		ft_putstr_err("error\n");
	}
	temp[0] = 4;
	temp[1] = 4;
	T_matrix = matrix_mul(f_matrix_a(45), f_matrix_b(120), temp);
	temp[1] = 1;
	while (lst)
	{
		lst->coords = matrix_mul(translate_matrix(0, 0, 0), lst->coords, temp);
		lst->coords = matrix_mul(T_matrix, lst->coords, temp);
		lst->coords = matrix_mul(create4x4_matrix(), lst->coords, temp);
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
	make_window(lst);
	return (0);
}