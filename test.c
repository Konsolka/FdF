/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 10:22:10 by mburl             #+#    #+#             */
/*   Updated: 2019/10/18 10:58:12 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_params
{
	void	*mlx_ptr;
	void	*mlx_win;
}				t_params;

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int		deal_key(int key, void *param)
{
	ft_putchar('x');
	t_params *ptr;
	ptr = param;
	mlx_pixel_put(ptr->mlx_ptr, ptr->mlx_win, key, key, 0xFFFFFF);
	return (0);
}

int		main(void)
{
	void	*ptr_mlx;
	void	*ptr_window;
	t_params	*param;

	param = (t_params *)(malloc(sizeof(*param)));
	ptr_mlx = mlx_init();
	ptr_window = mlx_new_window(ptr_mlx, 500, 500, "test");
	param->mlx_ptr = ptr_mlx;
	param->mlx_win = ptr_window;
	mlx_pixel_put(ptr_mlx, ptr_window, 250, 250, 0xFFFFFF);
	mlx_key_hook(ptr_window, deal_key, param);
	mlx_loop(ptr_mlx);
	return (0);
}