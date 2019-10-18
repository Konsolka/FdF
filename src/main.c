/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 11:07:21 by mburl             #+#    #+#             */
/*   Updated: 2019/10/18 15:38:49 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_list		*read_file(int fd)
{
	char	*line;
	char	**coord;
	t_list	*lst;
	t_fdf	*node;
	int		size;
	int		y;
	int 	i;
	int		*values;

	lst = NULL;
	line = NULL;
	y = 0;
	while (get_next_line(fd, &line))
	{
		coord = ft_strsplit(line, ' ');
		size = 0;
		while (1)
		{
			if (coord[size] == NULL)
				break;
			size++;
		}
		i = 0;
		values = (int *)malloc(sizeof(int) * size);
		while (i < size)
		{
			values[i] = ft_atoi(coord[i]);
			i++;
		}
		node = (t_fdf *)malloc(sizeof(t_fdf));
		node->coords = values;
		node->y = y;
		ft_lstadd(&lst, ft_lstnew(node, sizeof(*node)));
		ft_memdel((void **)node);
		y++;
	}
	return (lst);
}

int			print_map(t_list *lst)
{
	
}

int			main(int ac, char **av)
{
	int		fd;
	t_list	*lst;
	
	if (ac != 2)
		ft_putstr_err("Usage : ./fdf <filename> [ case_size z_size ]\n");
	if ((lst = read_file(open(av[1], O_RDONLY))) == NULL)
		ft_putstr_err("error\n");	
	print_map(lst);
	return (0);
}