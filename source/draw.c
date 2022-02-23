/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asippy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 23:18:02 by asippy            #+#    #+#             */
/*   Updated: 2022/02/21 23:13:27 by asippy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
*	Functions to perform all map painting
*	ft_draw_line - starting point to draw AA line
*	ft_draw_map - loop to draw map (if it is not the border,
*					draws line with next point of the map)
*	ft_correct_line - changes line's coordinates
*						for Xiaolin Wu's line algorithm
*	ft_correct_color - finds gradient step for neardy points
*	ft_draw_aa_line - Xiaolin Wu's line algorithm
*/

#include "fdf.h"

static void	ft_draw_aa_line(t_img *img, t_line *line, int steep)
{
	float	gradient;
	int		color;

	if (line->xn - line->xc == 0)
		gradient = 1;
	else
		gradient = (line->yn - line->yc) / (line->xn - line->xc);
	color = (int)line->ccr << 16 | (int)line->ccg << 8 | (int)line->ccb;
	while (line->xc <= line->xn)
	{
		if (steep)
			ft_put_yx_pair(img, line->yc, line->xc, color);
		else
			ft_put_xy_pair(img, line->xc, line->yc, color);
		ft_change_color(line, &color);
		line->yc += gradient;
		line->xc++;
	}
	return ;
}

static void	ft_correct_color(t_el *cur, t_el *next, t_line *line)
{
	float	length;

	line->ccr = (cur->color >> 16) & 0xFF;
	line->ccg = (cur->color >> 8) & 0xFF;
	line->ccb = cur->color & 0xFF;
	line->cnr = (next->color >> 16) & 0xFF;
	line->cng = (next->color >> 8) & 0xFF;
	line->cnb = next->color & 0xFF;
	length = sqrt(pow(line->xc - line->xn, 2) + pow(line->yc - line->yn, 2));
	ft_gradient(line->ccr, line->cnr, length, &line->cgr);
	ft_gradient(line->ccg, line->cng, length, &line->cgg);
	ft_gradient(line->ccb, line->cnb, length, &line->cgb);
	return ;
}

static int	ft_correct_line(t_line *line)
{
	int	steep;

	steep = 0;
	if (fabsf(line->yn - line->yc) > fabsf(line->xn - line->xc))
		steep = 1;
	if (steep)
	{
		ft_swap(&line->xc, &line->yc);
		ft_swap(&line->xn, &line->yn);
	}
	if (line->xc > line->xn)
	{
		ft_swap(&line->xc, &line->xn);
		ft_swap(&line->yc, &line->yn);
		ft_swap(&line->ccr, &line->cnr);
		ft_swap(&line->ccg, &line->cng);
		ft_swap(&line->ccb, &line->cnb);
		line->cgr *= -1;
		line->cgg *= -1;
		line->cgb *= -1;
	}
	return (steep);
}

static void	ft_draw_line(t_img *img, t_conf *conf, t_el *cur, t_el *next)
{
	t_line	line;
	int		steep;

	ft_correct_coords(conf, cur, &line.xc, &line.yc);
	ft_correct_coords(conf, next, &line.xn, &line.yn);
	ft_correct_color(cur, next, &line);
	steep = ft_correct_line(&line);
	ft_draw_aa_line(img, &line, steep);
	return ;
}

void	ft_draw_map(t_data *data)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < data->map.y_size)
	{
		x = 0;
		while (x < data->map.x_size)
		{
			if (y != data->map.y_size - 1)
				ft_draw_line(&data->img, &data->conf, &data->map.el[y][x],
					&data->map.el[y + 1][x]);
			if (x != data->map.x_size - 1)
				ft_draw_line(&data->img, &data->conf, &data->map.el[y][x],
					&data->map.el[y][x + 1]);
			x++;
		}
		y++;
	}
	return ;
}
