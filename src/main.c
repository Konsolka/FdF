/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 11:07:21 by mburl             #+#    #+#             */
/*   Updated: 2019/10/22 13:19:31 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

t_fdf		*read_file(int fd)
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
				ft_fdfdown(&lst, ft_create_node(i, y, ft_atoi(coord[i])));
			else
				ft_fdfadd(&lst, ft_create_node(i, y, ft_atoi(coord[i])));
			i++;
		}
		y++;
	}
	return (lst);
}

int			print_map(t_fdf *lst)
{
	
	return (0);
}

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
	
	if (ac != 2)
		ft_putstr_err("Usage : ./fdf <filename> [ case_size z_size ]\n");
	if ((lst = read_file(open(av[1], O_RDONLY))) == NULL)
		ft_putstr_err("error\n");

	//print_map(lst);
	return (0);
}