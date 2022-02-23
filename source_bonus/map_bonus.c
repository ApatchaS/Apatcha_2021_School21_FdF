/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asippy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 20:11:59 by asippy            #+#    #+#             */
/*   Updated: 2022/02/23 19:21:28 by asippy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
*	Map creation functions
*	ft_create_map - starting point
*	ft_read_file - reads file and represent it as string
*	ft_convert_file_to_strings - splits file on strings by '\n'
*	ft_convert_strings_to_elements - splits string on el by ' ' as ..,..
*	ft_convert_elements_to_cc - splits element on coordinate and color
*								and write it to structure
*	If in map there no color define, will use standart colors, defined in header
*				as MIN_COLOR and MAX_COLOR with gradient
*	In other case will use DEFAULT_COLOR for points without defined color in map 
*/

#include "fdf_bonus.h"

static void	ft_convert_elements_to_cc(t_map *map, size_t x, size_t y, char *str)
{
	char	**cc;

	map->el[y][x].x = x;
	map->el[y][x].y = y;
	cc = split(str, ',');
	free(str);
	if (cc == (void *)0)
		ft_display_err("Parse element error");
	map->el[y][x].z = ft_atoi_dec(cc[0]);
	free (cc[0]);
	if (map->el[y][x].z > map->z_max)
		map->z_max = map->el[y][x].z;
	if (map->el[y][x].z < map->z_min)
		map->z_min = map->el[y][x].z;
	if (cc[1] == (void *)0)
		map->el[y][x].color = DEFAULT_COLOR;
	else
	{
		map->global_gradient = 0;
		map->el[y][x].color = ft_atoi_hex(cc[1]);
		free (cc[1]);
	}
	free (cc);
	return ;
}

static void	ft_convert_strings_to_elements(t_map *map, size_t y, char *sstr)
{
	char	**str;
	size_t	x;

	str = split(sstr, ' ');
	free (sstr);
	if (str == (void *)0)
		ft_display_err("Parse string error");
	map->x_size = ft_find_size(str);
	map->el[y] = (t_el *)malloc(sizeof(t_el) * map->x_size);
	if (map->el[y] == (void *)0)
		ft_display_err("Malloc error");
	x = 0;
	while (str[x] != (void *)0)
	{
		ft_convert_elements_to_cc(map, x, y, str[x]);
		x++;
	}
	free(str);
	return ;
}

static void	ft_convert_file_to_strings(char *file, t_map *map)
{
	char	**strs;
	size_t	y;

	strs = split(file, '\n');
	free(file);
	if (strs == (void *)0)
		ft_display_err("Parse file error");
	map->y_size = ft_find_size(strs);
	map->el = (t_el **)malloc(sizeof(t_el *) * map->y_size);
	if (map->el == (void *)0)
		ft_display_err("Malloc error");
	y = 0;
	while (strs[y] != (void *)0)
	{
		ft_convert_strings_to_elements(map, y, strs[y]);
		y++;
	}
	free(strs);
	return ;
}

static char	*ft_read_file(const char *file_name)
{
	int		open_status;
	int		close_status;
	char	*file;
	char	*buf;

	open_status = open(file_name, O_RDONLY);
	if (open_status == -1)
		ft_display_err(strerror(errno));
	file = get_next_line(open_status);
	buf = get_next_line(open_status);
	while (buf != (void *)0)
	{
		file = ft_push_all_buf(&file, buf);
		free(buf);
		buf = get_next_line(open_status);
	}
	close_status = close(open_status);
	if (close_status == -1)
		ft_display_err(strerror(errno));
	if (file == (void *)0)
		ft_display_err("Error reading file");
	return (file);
}

void	ft_create_map(const char *file_name, t_map *map)
{
	char	*file;

	file = ft_read_file(file_name);
	map->global_gradient = 1;
	map->z_max = -2147483648;
	map->z_min = 2147483647;
	ft_convert_file_to_strings(file, map);
	if (map->global_gradient)
		ft_global_gradient_handle(map);
	return ;
}
