/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 11:07:21 by mburl             #+#    #+#             */
/*   Updated: 2019/12/12 15:58:55 by mburl            ###   ########.fr       */
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

void		read_file(int fd, t_fdf **lst)
{
	char	*line;
	char	**coord;
	int		j;
	int		y;
	int		i;

	if (fd < 0)
		ft_putstr_err("Invalid file\n");
	line = NULL;
	y = 0;
	while (get_next_line(fd, &line))
	{
		j = 0;
		coord = ft_strsplit(line, ' ');
		i = 0;
		ft_lst_add(lst, get_x(coord), y, coord);
		y++;
		free(line);
		while (j < get_x(coord))
			free(coord[j++]);
		free(coord);
	}
}

int			main(int ac, char **av)
{
	t_fdf	*lst;

	lst = NULL;
	if (ac != 2)
		ft_putstr_err("Usage : ./fdf <filename> [ case_size z_size ]\n");
	read_file(open(av[1], O_RDONLY), &lst);
	if (!lst)
	{
		free_fdf_lst(&lst);
		ft_putstr_err("Error in reading file\n");
	}
	preparations(lst);
	make_window(lst);
	free_fdf_lst(&lst);
	return (0);
}
