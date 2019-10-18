/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 11:07:21 by mburl             #+#    #+#             */
/*   Updated: 2019/10/18 12:47:18 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "mlx.h"
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"
#include <stdio.h>

int		read_file(int fd)
{
	char *line;
	char	**coord;
	void	*mlx_ptr;
	void	*win_ptr;
	int		i = 0;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "fdf");
	line = NULL;
	while (get_next_line(fd, &line))
	{
		coord = ft_strsplit(line, ' ');
		while (i < 10)
		{
			printf("%s, ", coord[i]);
			i++;
		}
		free(coord);
		printf("\n");
	}
	return (0);
}

int		main(int ac, char **av)
{
	int		fd;

	if (ac != 2)
		ft_putstr_err("Usage : ./fdf <filename> [ case_size z_size ]\n");
	if ((fd = read_file(open(av[1], O_RDONLY))) == -1)
		ft_putstr_err("error\n");	
	return (0);
}