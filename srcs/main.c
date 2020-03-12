/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 11:07:21 by mburl             #+#    #+#             */
/*   Updated: 2020/03/12 11:28:12 by mburl            ###   ########.fr       */
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

void		freeCoord(char **coord)
{
	int			i;

	i = 0;
	while (i < get_x(coord))
		free(coord[i++]);
	free(coord);
}

t_fdf		*read_file(int fd)
{
	t_fdf	*lst;
	char	*line;
	char	**coord;
	int		y;
	int		i;

	if (fd < 0)
		ft_putstr_err("fdf: No such file\n");
	lst = NULL;
	line = NULL;
	y = 0;
	while (get_next_line(fd, &line))
	{
		coord = ft_strsplit(line, ' ');
		i = 0;
		while (i < get_x(coord))
		{
			addNode(&lst, createNode(i, y, ft_atoi(coord[i])));
			i++;
		}
		free(line);
		freeCoord(coord);
		y++;
	}
	return (lst);
}

int			main(int ac, char **av)
{
	t_fdf	*lst;

	lst = NULL;
	if (ac != 2)
		fatalError("Usage:\n\t./fdf <fileName>");
	if (!(lst = read_file(open(av[1], O_RDONLY))))
		fatalError("Error in reading file");
	printList(lst);
	makeWindow(lst);
	// preparations(lst);
	// make_window(lst);
	// free_fdf_lst(&lst);
	return (0);
}
