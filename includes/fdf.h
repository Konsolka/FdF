/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 12:07:18 by mburl             #+#    #+#             */
/*   Updated: 2019/10/21 19:22:36 by mburl            ###   ########.fr       */
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
	int			x;
	int			y;
	int			z;
	struct s_fdf	*next;
}					t_fdf;

typedef struct	s_map
{
	float		a;
	float		fov;
	float		q;
	
}				t_map;

void	ft_fdfadd(t_fdf **alst, t_fdf *new);

#endif