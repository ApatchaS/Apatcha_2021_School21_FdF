/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asippy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 16:08:28 by asippy            #+#    #+#             */
/*   Updated: 2022/02/23 19:21:02 by asippy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

/*
*	Functions to manage rotations, isometric, shifts and different angles
*	ft_correct_coords - changes coordinates depending on rotation by axes
*						and manage shift
*	ft_convert_to_iso - converts model to isometric projection
*/

static void	ft_convert_to_iso(float *x, float *y, float z, float angle)
{
	float	prev_x;
	float	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = (prev_x - prev_y) * cos(angle);
	*y = -z + (prev_x + prev_y) * sin(angle);
	return ;
}

void	ft_correct_coords(t_conf *conf, t_el *elem, float *x, float *y)
{	
	float	bufx;
	float	bufy;
	float	z;

	bufx = elem->x * conf->zoom;
	bufy = elem->y * conf->zoom;
	z = elem->z * conf->zoom * conf->z;
	*y = (bufy - conf->width) * cos(conf->rotx) - z * sin(conf->rotx);
	z = (bufy - conf->width) * sin(conf->rotx) + z * cos(conf->rotx);
	bufy = *y;
	*x = (bufx - conf->height) * cos(conf->roty) - z * sin(conf->roty);
	z = (bufx - conf->height) * sin(conf->roty) + z * cos(conf->roty);
	bufx = *x;
	*x = (bufx) * cos(conf->rotz) - (bufy) * sin(conf->rotz);
	*y = (bufx) * sin(conf->rotz) + (bufy) * cos(conf->rotz);
	if (conf->iso)
		ft_convert_to_iso(x, y, z, conf->angle);
	*x += conf->posx;
	*y += conf->posy;
	return ;
}
