/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 12:07:18 by mburl             #+#    #+#             */
/*   Updated: 2019/12/10 11:55:15 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include "libft.h"
# include "mlx.h"
# include "get_next_line.h"
# define HIEGHT 720
# define WIDTH 1280
# define FOV 90
# define F_NEAR 0.1
# define F_FAR 100.0

typedef struct		s_fdf // coords xyz [xyz, xyz], up, down
{
	double			**coords;
	int				max_line;
	struct s_fdf	*up;
	struct s_fdf	*down;

}					t_fdf;

typedef struct	s_map
{
	float		max_x;
	float		max_y;
}				t_map;

typedef struct	s_mlx
{
	void	*win;
	void	*ptr;
}				t_mlx;

typedef struct	s_vector
{
	double		x;
	double		y;
	double		z;
	double		w;
}				t_vector;

typedef struct	s_data
{
	t_mlx	*mlx;
	t_fdf	*lst;
}				t_data;




typedef struct	s_i
{
	int		x;
	int		y;
	int		z;
}				t_i;

void	ft_lst_add(t_fdf **alst, int x, int y, char **coords);
void	free_fdf_lst(t_fdf **alst);
void	fdf_lst_begin(t_fdf **alst);
void	make_window(t_fdf *lst);
void	draw_map(t_fdf *lst, t_mlx *mlx_list);
int		key_parse(int key, void *param);
void	scaling(t_fdf *lst, double scale_x, double scale_y, double scale_z);
double	**ft_matrix_rotation(double x, char axis);
void	preparations(t_fdf *lst);
void	ft_free_matrix(double **m);


#endif