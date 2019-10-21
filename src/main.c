/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 11:07:21 by mburl             #+#    #+#             */
/*   Updated: 2019/10/21 19:29:02 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

t_fdf		*read_file(int fd)
{
	char	*line;
	char	**coord;
	t_fdf	*node;
	int		y;
	int 	i;

	lst = NULL;
	line = NULL;
	y = 0;
	while (get_next_line(fd, &line))
	{
		coord = ft_strsplit(line, ' ');
		i = 0;
		node = (t_fdf *)malloc(sizeof(t_fdf));
		while (1)
		{
			if (coord[i])
				break ;
			ft_fdfadd(&node, ft_create_node(i, y, ft_atoi(coord[i])));
			i++;
		}
		y++;
	}
	return (node);
}

int			print_map(t_list *lst)
{
	t_fdf	*node;
	int		i;
	int		x;
	void	*mlx_ptr;
	void	*win_ptr;
	int		line;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, HIEGHT, WIDTH, "fdf");
	mlx_loop(mlx_ptr);
	return (0);
}

/*	Projection:
**
**	h/w * 1/ tan(O/2)		0				0										0
**	0						1/ tan(O/2)		0										0
**	0						0				z_far/(z_far - z_near)					1
**	0						0				-(z_far * z_near) / (z_far - z_near)	0
**
*/
int			main(int ac, char **av)
{
	t_fdf	*lst;
	t_map	*map;
	float	matrix4x4[4][4];
	
	matrix4x4 = {0};
	if (ac != 2)
		ft_putstr_err("Usage : ./fdf <filename> [ case_size z_size ]\n");
	if ((lst = read_file(open(av[1], O_RDONLY))) == NULL)
		ft_putstr_err("error\n");	
	map = (t_map *)malloc(sizeof(t_map));
	map->a = HIEGHT / WIDTH;
	map->fov = 1.0/ tanh(F_FOV, * 0.5/180 * M_PI);
	map->q = F_FAR / (F_FAR - F_NEAR);
	matrix4x4[0][0] = map->a * map->fov;
	matrix4x4[1][1] = map->fov;
	matrix4x4[2][2] = map->q;
	matrix4x4[3][2] = (-F_NEAR * F_FAR) / (F_FAR - F_NEAR);
	matrix4x4[2][3] = 1.0f;
	matrix4x4[3][3] = 0.0f;

	print_map(lst);
	return (0);
}