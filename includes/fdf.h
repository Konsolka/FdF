/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 12:07:18 by mburl             #+#    #+#             */
/*   Updated: 2019/10/22 18:12:08 by mburl            ###   ########.fr       */
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
# define HIEGHT 500
# define WIDTH 500
# define F_NEAR 0.1f
# define F_FAR 1000.0f

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

t_fdf	*ft_create_node(int x, int y, int z);
void	ft_fdfadd(t_fdf **alst, t_fdf *new);
void	ft_fdfdown(t_fdf **alst, t_fdf *new);
double	**f_matrix_a(double a);
double	**f_matrix_b(double b);
void	print_map(t_fdf *lst);
double	**matrix_mul(double **a, double **b, int *b_data);

#endif