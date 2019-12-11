/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:59:27 by mburl             #+#    #+#             */
/*   Updated: 2019/12/11 14:18:56 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static long		choose_color(int f, int s)
{
	long	color;

	color = 0x2AA2A5;
	if (f == s)
	{
		if (f == 1)
			color = 0xFFFFFF;
		else
			color = 0x008000;
	}
	return (color);
}

static void		second_point(long color, t_data *data, t_line line)
{
	if (!(line.x2 < 0 || line.y2 < 0 || line.x2 >= WIDTH || line.y2 >= HIEGHT))
	{
		data->data_addr[((line.x2 * data->bpp / 8) +
						(line.y2 * data->size_line))] = color;
		data->data_addr[(1 + (line.x2 * data->bpp / 8) +
						(line.y2 * data->size_line))] = color >> 8;
		data->data_addr[(2 + (line.x2 * data->bpp / 8) +
						(line.y2 * data->size_line))] = color >> 16;
	}
}

static void		first_point(long color, t_data *data, t_line *line)
{
	double	error2;
	int		i;

	while (line->x1 != line->x2 || line->y1 != line->y2)
	{
		error2 = line->error * 2;
		if (!(line->x1 < 0 || line->y1 < 0 ||
				line->x1 >= WIDTH || line->y1 >= HIEGHT))
		{
			i = (line->x1 * data->bpp / 8) + (line->y1 * data->size_line);
			data->data_addr[i] = color;
			data->data_addr[++i] = color >> 8;
			data->data_addr[++i] = color >> 16;
		}
		if (error2 > -line->delty)
		{
			line->error -= line->delty;
			line->x1 += line->signx;
		}
		if (error2 < line->deltx)
		{
			line->error += line->deltx;
			line->y1 += line->signy;
		}
	}
}

void			ft_mlx_line(t_data *data, double *first, double *second)
{
	t_line	line;
	long	color;

	line.x1 = first[0] + data->x_mid;
	line.y1 = first[1] + data->y_mid;
	line.x2 = second[0] + data->x_mid;
	line.y2 = second[1] + data->y_mid;
	line.deltx = abs(line.x2 - line.x1);
	line.delty = abs(line.y2 - line.y1);
	line.signx = line.x1 < line.x2 ? 1 : -1;
	line.signy = line.y1 < line.y2 ? 1 : -1;
	line.error = line.deltx - line.delty;
	color = choose_color(first[3], second[3]);
	second_point(color, data, line);
	first_point(color, data, &line);
}
