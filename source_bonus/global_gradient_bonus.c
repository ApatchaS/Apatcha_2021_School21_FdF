/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_gradient_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asippy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 21:36:18 by asippy            #+#    #+#             */
/*   Updated: 2022/02/23 19:21:25 by asippy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
*	Functions for repainting points in map without color
*	ft_global_gradient_handle - finds length between max and min altitude
*			separete MIN_COLOR on RGB segments and finds step for gradient
*	ft_recolor_map - loop for each point in map
*	ft_define_color - finds relative color between MIN_COLOR and MAX_COLOR
*						for specific point and converts RGB segments to int
*/

#include "fdf_bonus.h"

static unsigned int	ft_define_color(t_map *map, size_t x, size_t y)
{
	int		length;
	float	r;
	float	g;
	float	b;

	length = abs(map->z_min - map->el[y][x].z);
	r = map->min_r + length * map->gr;
	g = map->min_g + length * map->gg;
	b = map->min_b + length * map->gb;
	return ((int)r << 16 | (int)g << 8 | (int)b);
}

static void	ft_recolor_map(t_map *map)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < map->y_size)
	{
		x = 0;
		while (x < map->x_size)
		{
			map->el[y][x].color = ft_define_color(map, x, y);
			x++;
		}
		y++;
	}
	return ;
}

void	ft_global_gradient_handle(t_map *map)
{
	int	length;

	length = abs(map->z_max - map->z_min);
	map->min_r = (MIN_COLOR >> 16) & 0xFF;
	map->min_g = (MIN_COLOR >> 8) & 0xFF;
	map->min_b = MIN_COLOR & 0xFF;
	ft_gradient(map->min_r, (MAX_COLOR >> 16) & 0xFF, length, &map->gr);
	ft_gradient(map->min_g, (MAX_COLOR >> 8) & 0xFF, length, &map->gg);
	ft_gradient(map->min_b, MAX_COLOR & 0xFF, length, &map->gb);
	ft_recolor_map(map);
	return ;
}
