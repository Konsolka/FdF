/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 12:07:18 by mburl             #+#    #+#             */
/*   Updated: 2019/12/11 14:05:54 by mburl            ###   ########.fr       */
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
# define MOVE 10

/*
**	coords xyz [xyz, xyz], up, down
*/

typedef struct		s_fdf
{
	double			**coords;
	int				max_line;
	struct s_fdf	*up;
	struct s_fdf	*down;

}					t_fdf;

/*
**	storing win, ptr, image
*/

typedef struct	s_mlx
{
	void	*win;
	void	*ptr;
	void	*img;
}				t_mlx;

/*
**	point x, y, z
*/

typedef struct	s_vector
{
	double		x;
	double		y;
	double		z;
	double		w;
}				t_vector;


/*
**	storing all stuff that will be needed
**	bpp - bits per pixel (using in mlx_get_data_addr)
**	ed - endian (using in mlx_get_data_addr)
**	x_mid - x axes middle of obj
**	y_mid - y axes middle of obj
**	dot - 
*/

typedef struct	s_data
{
	t_mlx	*mlx;
	t_fdf	*lst;
	int		bpp;
	int		size_line;
	int		ed;
	double	*min_max;
	char	*data_addr;
	int		dot;
	int		x_mid;
	int		y_mid;
}				t_data;

typedef struct	s_line
{
	int		deltx;
	int		delty;
	int		signx;
	int		signy;
	int		error;
	int		x1;
	int		y1;
	int		x2;
	int		y2;

}				t_line;

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
void	draw_map(t_fdf *lst, t_mlx *mlx_list, t_data *data);
int		key_parse(int key, void *param);
void	scaling(t_fdf *lst, double scale_x, double scale_y, double scale_z);
double	**ft_matrix_rotation(double x, char axis);
void	preparations(t_fdf *lst);
void	ft_free_matrix(double **m);
double	*min_max(t_fdf *lst);
double	**matrix_mul_b(double **a, double **b, int *b_data);
void	draw_dots(t_data *data, t_fdf *lst);
void	rotate_global(double *coords, double **rotate_matrix);
void	move(t_fdf *lst, double d, int vert);
void	ft_mlx_line(t_data *data, double *first, double *second);

#endif