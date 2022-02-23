/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asippy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 22:07:39 by asippy            #+#    #+#             */
/*   Updated: 2022/02/21 22:52:53 by asippy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
*	Functions to handle users inputs and creation of starting parameters
*	ft_init_zoom - starting zoom
*	ft_init_conf - starting parameters
*	ft_change_conf1 - changing parameters (norm is bummer) 
*	ft_change_conf2 - changing parameters (norm is bummer)
*	ft_change_conf3 - changing parameters (norm is bummer)
*/

#include "fdf.h"

static void	ft_init_zoom(t_map *map, float *zoom)
{	
	*zoom = 0;
	while (*zoom * map->x_size < WIN_WIDTH && *zoom * map->y_size < WIN_HEIGHT)
		*zoom += ZOOM;
	*zoom /= 2;
	return ;
}

void	ft_init_conf(t_data *data)
{
	data->conf.menu = 1;
	data->conf.iso = 1;
	data->conf.angle = 0.523599;
	ft_init_zoom(&data->map, &data->conf.zoom);
	data->conf.width = data->map.x_size * data->conf.zoom / 2;
	data->conf.height = data->map.y_size * data->conf.zoom / 2;
	data->conf.posx = WIN_WIDTH / 2;
	data->conf.posy = WIN_HEIGHT / 2;
	data->conf.z = 0.1;
	data->conf.rotx = 0;
	data->conf.roty = 0;
	data->conf.rotz = 0;
	return ;
}

size_t	ft_change_conf1(int keycode, t_data *data)
{
	size_t	flag;

	flag = 1;
	if (keycode == 49)
		data->conf.menu = abs(data->conf.menu - 1);
	else if (keycode == 34)
		data->conf.iso = abs(data->conf.iso - 1);
	else if (keycode == 32)
		ft_init_conf(data);
	else if (keycode == 12)
		data->conf.angle -= ANGLE;
	else if (keycode == 48)
		data->conf.angle = 0.523599;
	else if (keycode == 14)
		data->conf.angle += ANGLE;
	else if (keycode == 27)
		data->conf.z -= Z_VAL;
	else if (keycode == 257)
		data->conf.z = 0.1;
	else if (keycode == 24)
		data->conf.z += Z_VAL;
	else
		flag = 0;
	return (flag);
}

size_t	ft_change_conf2(int keycode, t_data *data)
{
	size_t	flag;

	flag = 1;
	if (keycode == 6)
		data->conf.zoom -= ZOOM;
	else if (keycode == 7)
		ft_init_zoom(&data->map, &data->conf.zoom);
	else if (keycode == 8)
		data->conf.zoom += ZOOM;
	else if (keycode == 13 || keycode == 126)
		data->conf.posy -= HEIGHT;
	else if (keycode == 1 || keycode == 125)
		data->conf.posy += HEIGHT;
	else if (keycode == 0 || keycode == 123)
		data->conf.posx -= WIDTH;
	else if (keycode == 2 || keycode == 124)
		data->conf.posx += WIDTH;
	else if (keycode == 264)
	{
		data->conf.posx = WIN_WIDTH / 2;
		data->conf.posy = WIN_HEIGHT / 2;
	}
	else
		flag = 0;
	return (flag);
}

size_t	ft_change_conf3(int keycode, t_data *data)
{
	size_t	flag;

	flag = 1;
	if (keycode == 18)
		data->conf.rotx -= ROT;
	else if (keycode == 19)
		data->conf.rotx = 0;
	else if (keycode == 20)
		data->conf.rotx += ROT;
	else if (keycode == 21)
		data->conf.roty -= ROT;
	else if (keycode == 23)
		data->conf.roty = 0;
	else if (keycode == 22)
		data->conf.roty += ROT;
	else if (keycode == 26)
		data->conf.rotz -= ROT;
	else if (keycode == 28)
		data->conf.rotz = 0;
	else if (keycode == 25)
		data->conf.rotz += ROT;
	else
		flag = 0;
	return (flag);
}
