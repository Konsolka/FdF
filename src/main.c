/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 11:07:21 by mburl             #+#    #+#             */
/*   Updated: 2019/10/18 16:24:43 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_list		*read_file(int fd)
{
	char	*line;
	char	**coord;
	t_list	*lst;
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
			ft_create_node(i, y, ft_atoi(coord[i]));
			i++;
		}
		node->y = y;
		ft_memdel((void **)node);
		y++;
	}
	return (lst);
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
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "fdf");
	while (lst)
	{
		i = 0;
		node = lst->content;
		x = 10;
		while (i < node->size - 1)
		{
			line = 0;
			while (line < 20)
			{
				mlx_pixel_put(mlx_ptr, win_ptr, x + 20 + line, node->y * 20 + 100, 0xFFFFFF);
				line++;
			}
			x += 20;
			i++;
		}
		lst = lst->next;
	}
	mlx_loop(mlx_ptr);
	return (0);
}

int			main(int ac, char **av)
{
	t_list	*lst;
	
	if (ac != 2)
		ft_putstr_err("Usage : ./fdf <filename> [ case_size z_size ]\n");
	if ((lst = read_file(open(av[1], O_RDONLY))) == NULL)
		ft_putstr_err("error\n");	
	print_map(lst);
	return (0);
}