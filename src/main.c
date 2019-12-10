/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 11:07:21 by mburl             #+#    #+#             */
/*   Updated: 2019/12/10 13:10:44 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

int			get_x(char **coords)
{
	int		i;

	i = 0;
	while (coords[i])
		i++;
	return (i);
}

t_fdf		*read_file(int fd, t_map **map)
{
	char	*line;
	char	**coord;
	t_fdf	*lst;
	int		y;
	int 	i;
	int		x;

	lst = NULL;
	line = NULL;
	y = 0;
	while (get_next_line(fd, &line))
	{
		coord = ft_strsplit(line, ' ');
		i = 0;
		x = get_x(coord);
		ft_lst_add(&lst, x, y, coord);
		y++;
	}
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
	free_fdf_lst(&lst);
	return (0);
}