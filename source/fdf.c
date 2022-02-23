/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asippy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 19:21:24 by asippy            #+#    #+#             */
/*   Updated: 2022/02/21 22:09:58 by asippy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		ft_display_err("Count of arguments not equal 1");
	ft_create_map(argv[1], &data.map);
	ft_run_mlx(&data);
	return (0);
}
