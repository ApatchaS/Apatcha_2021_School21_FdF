/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_math_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asippy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 20:15:04 by asippy            #+#    #+#             */
/*   Updated: 2022/02/21 22:58:15 by asippy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
*	Math functions for Anti-Aliasing line drawing algorithm
*	ft_swap - swaps two parameters
*	ft_ipart - gets integer part of a number
*	ft_round - rounding a a number
*	ft_fpart - gets fractional part of a number
*	ft_rfpart - gets reversed fractional part of a number
*/

#include "fdf.h"

void	ft_swap(float *x, float *y)
{
	float	tmp;

	tmp = *x;
	*x = *y;
	*y = tmp;
	return ;
}

int	ft_ipart(float x)
{
	return ((int)floor(x));
}

int	ft_round(float x)
{
	return ((int)round(x));
}

float	ft_fpart(float x)
{
	if (x > 0)
		return (x - ft_ipart(x));
	return (x - (ft_ipart(x) + 1));
}

float	ft_rfpart(float x)
{
	return (1 - ft_fpart(x));
}
