/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asippy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 20:51:44 by asippy            #+#    #+#             */
/*   Updated: 2022/02/18 21:25:22 by asippy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
*	Utilities for map creation
*	ft_find_size - finds lengh of array as result of file split
*	ft_atoi_dec - converts char* to dec_int type with '-' handle
*	ft_atoi_hex - converts char* to hex_int type with two bases handle
*/

#include "fdf.h"

size_t	ft_find_size(char **str)
{
	size_t	res;

	res = 0;
	while (str[res] != (void *)0)
		res++;
	return (res);
}

long long	ft_atoi_dec(const char *str)
{
	long long	res;
	int			sign;
	size_t		iter;

	res = 0;
	sign = 1;
	iter = 0;
	if (str[iter] == '-')
	{
		iter++;
		sign = -1;
	}
	while (str[iter] != '\0')
	{
		res = 10 * res + (str[iter] - '0');
		iter++;
	}
	return (sign * res);
}

unsigned int	ft_atoi_hex(const char *str)
{
	char			*base;
	unsigned int	res;
	size_t			iter;
	size_t			ind;

	iter = 2;
	base = "0123456789abcdef0123456789ABCDEF";
	while (str[iter] != '\0')
	{
		ind = 0;
		while (str[iter] != base[ind])
			ind++;
		res = 16 * res + (ind % 16);
		iter++;
	}
	return (res);
}
