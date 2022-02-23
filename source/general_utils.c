/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utilities.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asippy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 20:09:59 by asippy            #+#    #+#             */
/*   Updated: 2022/02/18 20:54:25 by asippy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
*	Utilities for project overall
*	ft_display_err - shows error message and exit
*/

#include "fdf.h"

void	ft_display_err(const char *str)
{
	size_t	iter;

	iter = 0;
	while (str[iter] != '\0')
	{
		write(2, &str[iter], 1);
		iter++;
	}
	write(2, "\n", 1);
	exit(1);
}
