/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 11:07:21 by mburl             #+#    #+#             */
/*   Updated: 2019/11/13 20:16:58 by mburl            ###   ########.fr       */
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

int			main(int ac, char **av)
{
	t_fdf	*lst;
	t_map	*map;
	
	if (ac != 2)
		ft_putstr_err("Usage : ./fdf <filename> [ case_size z_size ]\n");
	map = (t_map *)malloc(sizeof(t_map));
	if ((lst = read_file(open(av[1], O_RDONLY), &map)) == NULL)
	{
		free(map);
		ft_putstr_err("error\n");
	}
	preparations(lst);
	free(map);
	make_window(lst);
	return (0);
}