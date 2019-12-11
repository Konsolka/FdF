/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 11:07:21 by mburl             #+#    #+#             */
/*   Updated: 2019/12/11 12:33:01 by mburl            ###   ########.fr       */
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

t_fdf		*read_file(int fd)
{
	char	*line;
	char	**coord;
	t_fdf	*lst;
	int		y;
	int		i;

	lst = NULL;
	line = NULL;
	y = 0;
	while (get_next_line(fd, &line))
	{
		coord = ft_strsplit(line, ' ');
		i = 0;
		ft_lst_add(&lst, get_x(coord), y, coord);
		y++;
	}
	return (lst);
}

int			main(int ac, char **av)
{
	t_fdf	*lst;

	if (ac != 2)
		ft_putstr_err("Usage : ./fdf <filename> [ case_size z_size ]\n");
	if ((lst = read_file(open(av[1], O_RDONLY))) == NULL)
	{
		free_fdf_lst(&lst);
		ft_putstr_err("Error in reading file\n");
	}
	preparations(lst);
	make_window(lst);
	free_fdf_lst(&lst);
	return (0);
}
