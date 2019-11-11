/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 12:07:18 by mburl             #+#    #+#             */
/*   Updated: 2019/11/11 18:47:48 by mburl            ###   ########.fr       */
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
# define WIDTH 480
# define FOV 90
# define F_NEAR 0.1
# define F_FAR 100.0

typedef struct		s_fdf
{
	double			**coords;
	struct s_fdf	*next;
	struct s_fdf	*prev;
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

typedef struct	s_data
{
	t_mlx	*mlx;
	t_fdf	*lst;
	int		scale;
}				t_data;
t_fdf	*ft_create_node(int x, int y, int z);
void	ft_fdfadd(t_fdf **alst, t_fdf *new);
void	ft_fdfdown(t_fdf **alst, t_fdf *new);
double	**f_matrix_a(double a);
double	**f_matrix_b(double b);
void	make_window(t_fdf *lst);
double	**matrix_mul(double **a, double **b, int *b_data);
double		**create4x4_matrix(void);
double		**translate_matrix(double x, double y, double z);
void	ft_mlx_line(int x1, int y1, int x2, int y2, t_mlx *lst);
void	drawing_map(t_fdf *lst, t_mlx *mlx_list);
double		**scaling_matrix(double	pers);
void	scaling(t_fdf *lst, double scale);

#endif