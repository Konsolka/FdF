/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburl <mburl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 19:29:20 by mburl             #+#    #+#             */
/*   Updated: 2019/10/21 19:56:35 by mburl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void BuildPerspProjMat(float *m, float fov, float aspect,
float znear, float zfar)
{
  float xymax = znear * tan(fov * PI_OVER_360);
  float width = xymax + xymax;
  float height = xymax + xymax;

  float depth = zfar - znear;
  float q = -(zfar + znear) / depth;
  float qn = -2 * (zfar * znear) / depth;

  float w = 2 * znear / width;
  w = w / aspect;
  float h = 2 * znear / height;

	m[0]  = w;
	m[1]  = 0;
	m[2]  = 0;
	m[3]  = 0;
	m[4]  = 0;
	m[5]  = h;
	m[6]  = 0;
	m[7]  = 0;
	m[8]  = 0;
	m[9]  = 0;
	m[10] = q;
	m[11] = -1;
	m[12] = 0;
	m[13] = 0;
	m[14] = qn;
	m[15] = 0;
}