/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_color_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asippy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:34:16 by asippy            #+#    #+#             */
/*   Updated: 2022/02/23 19:21:08 by asippy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
*	Functions to manage color changes for point with gradient and incudes
*		part of Xiaolin Wu's line algorithm
*	ft_put_xy_pair - puts two pixels in case of small steep of line
*	ft_put_yx_pair - puts two pixels in case of small steep of line
*	ft_change_color - change color as RGB segments on one step of gradient
*						and converts it to int
*	ft_gradient - findes gradient step for segment of RGB model
*	ft_put_pixel - puts pixel to image
*/

#include "fdf_bonus.h"

static void	ft_put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->llength + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
	return ;
}

void	ft_gradient(int cur, int next, float length, float *res)
{
	if (length == 0)
	{
		*res = 0;
		return ;
	}
	*res = abs(cur - next) / length;
	if (cur > next)
		*res *= -1;
	return ;
}

void	ft_change_color(t_line *line, int *color)
{
	line->ccr += line->cgr;
	line->ccg += line->cgg;
	line->ccb += line->cgb;
	*color = (int)line->ccr << 16 | (int)line->ccg << 8 | (int)line->ccb;
	return ;
}

void	ft_put_yx_pair(t_img *img, float y, float x, int color)
{
	if (ft_ipart(y) <= 0 || ft_ipart(y) >= WIN_WIDTH
		|| ft_ipart(x) <= 0 || ft_ipart(x) >= WIN_HEIGHT)
		return ;
	ft_put_pixel(img, ft_ipart(y), x, (int)(255 * ft_rfpart(y)) << 24 | color);
	ft_put_pixel(img, ft_ipart(y) - 1, x,
		(int)(255 * ft_fpart(y)) << 24 | color);
	return ;
}

void	ft_put_xy_pair(t_img *img, float x, float y, int color)
{
	if (ft_ipart(x) <= 0 || ft_ipart(x) >= WIN_WIDTH
		|| ft_ipart(y) <= 0 || ft_ipart(y) >= WIN_HEIGHT)
		return ;
	ft_put_pixel(img, x, ft_ipart(y), (int)(255 * ft_rfpart(y)) << 24 | color);
	ft_put_pixel(img, x, ft_ipart(y) - 1,
		(int)(255 * ft_fpart(y)) << 24 | color);
	return ;
}
