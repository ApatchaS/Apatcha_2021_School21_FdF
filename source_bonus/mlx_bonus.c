/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asippy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 22:13:00 by asippy            #+#    #+#             */
/*   Updated: 2022/02/23 19:21:35 by asippy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
*	Graphical maintenance: creates connection with MLX, creates window, image
*		menu and instructions for user, besides manage parameters changes
*	ft_run_mlx - connection with mlx and painting map
*	ft_destroy - gots exit from programm in case of closing window
*	ft_keyboard - manages users inputs and repaints map
*	ft_draw_menu - prints users instructions in window
*/

#include "fdf_bonus.h"

static void	ft_draw_menu(t_data *data)
{
	if (!data->conf.menu)
		return ;
	mlx_string_put(data->mlx.mlx, data->mlx.mlx_win, 10, 10, 0x00FF00,
		"OPEN/CLOSE MENU -> SPACE");
	mlx_string_put(data->mlx.mlx, data->mlx.mlx_win, 20, 40, 0xFFFFFF,
		"Isometric/Parallel projection -> I");
	mlx_string_put(data->mlx.mlx, data->mlx.mlx_win, 20, 60, 0xFFFFFF,
		"Defaults -> U");
	mlx_string_put(data->mlx.mlx, data->mlx.mlx_win, 20, 80, 0xFFFFFF,
		"Change angle (only for ISO) -> Q or E (TAB for default)");
	mlx_string_put(data->mlx.mlx, data->mlx.mlx_win, 20, 100, 0xFFFFFF,
		"Change zoom -> Z or C (X for default)");
	mlx_string_put(data->mlx.mlx, data->mlx.mlx_win, 20, 120, 0xFFFFFF,
		"Change location -> WASD or ARROWs (CAPS for default)");
	mlx_string_put(data->mlx.mlx, data->mlx.mlx_win, 20, 140, 0xFFFFFF,
		"Rotation by X -> 1 or 3 (2 for default)");
	mlx_string_put(data->mlx.mlx, data->mlx.mlx_win, 20, 160, 0xFFFFFF,
		"Rotation by Y -> 4 or 6 (5 for default)");
	mlx_string_put(data->mlx.mlx, data->mlx.mlx_win, 20, 180, 0xFFFFFF,
		"Rotation by Z -> 7 or 9 (8 for default)");
	mlx_string_put(data->mlx.mlx, data->mlx.mlx_win, 20, 200, 0xFFFFFF,
		"Change Z -> - or + (SHIFT for default)");
	return ;
}

static int	ft_keyboard(int keycode, t_data *data)
{
	size_t	flag;

	if (keycode == 53)
	{
		mlx_destroy_window(data->mlx.mlx, data->mlx.mlx_win);
		exit(0);
	}
	flag = ft_change_conf1(keycode, data) + ft_change_conf2(keycode, data)
		+ ft_change_conf3(keycode, data);
	if (flag)
	{
		mlx_clear_window(data->mlx.mlx, data->mlx.mlx_win);
		data->img.img = mlx_new_image(data->mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
		data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
				&data->img.llength, &data->img.end);
		ft_draw_map(data);
		mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win,
			data->img.img, 0, 0);
		ft_draw_menu(data);
	}
	return (0);
}

static int	ft_destroy(t_data *data)
{
	(void) data;
	exit(0);
}

void	ft_run_mlx(t_data *data)
{
	data->mlx.mlx = mlx_init();
	if (data->mlx.mlx == (void *)0)
		ft_display_err("MLX connection error");
	data->mlx.mlx_win = mlx_new_window(data->mlx.mlx, WIN_WIDTH, WIN_HEIGHT,
			"Let's celebrate and cook some ducks!");
	data->img.img = mlx_new_image(data->mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
			&data->img.llength, &data->img.end);
	ft_init_conf(data);
	ft_draw_map(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win,
		data->img.img, 0, 0);
	ft_draw_menu(data);
	mlx_hook(data->mlx.mlx_win, 17, 0, &ft_destroy, data);
	mlx_hook(data->mlx.mlx_win, 2, 0, &ft_keyboard, data);
	mlx_loop(data->mlx.mlx);
}
