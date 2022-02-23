/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asippy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 07:35:43 by asippy            #+#    #+#             */
/*   Updated: 2022/02/23 19:21:22 by asippy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static	size_t	ft_slen(char *str)
{
	size_t	iter;

	iter = 0;
	while (str[iter] != '\0')
		iter++;
	return (iter);
}

static	size_t	ft_res_to_new(char **new, char **res)
{
	size_t	iter;

	iter = 0;
	while ((*res)[iter] != '\0')
	{
		(*new)[iter] = (*res)[iter];
		iter++;
	}
	free((*res));
	return (iter);
}

ssize_t	ft_find_line(char *buf)
{
	size_t	iter;

	iter = 0;
	while (buf[iter] != '\0' && buf[iter] != '\n')
		iter++;
	if (buf[iter] != '\n')
		return (-1);
	return (iter);
}

char	*ft_push_all_buf(char **res, char *buf)
{
	char	*new;
	size_t	iter1;
	size_t	iter2;

	new = (char *)malloc(sizeof(char) * (ft_slen(*res) + ft_slen(buf) + 1));
	if (new == (void *)0)
		return ((void *)0);
	iter1 = ft_res_to_new(&new, res);
	iter2 = 0;
	while (buf[iter2] != '\0')
	{
		new[iter1] = buf[iter2];
		iter1++;
		iter2++;
	}
	buf[0] = '\0';
	new[iter1] = '\0';
	return (new);
}

char	*ft_push_line(size_t lcntr, char **res, char *buf)
{
	char	*new;
	size_t	iter1;
	size_t	iter2;

	new = (char *)malloc(sizeof(char) * (ft_slen(*res) + lcntr + 2));
	if (new == (void *)0)
		return ((void *)0);
	iter1 = ft_res_to_new(&new, res);
	iter2 = 0;
	while (iter2 <= lcntr)
	{
		new[iter1] = buf[iter2];
		iter1++;
		iter2++;
	}
	new[iter1] = '\0';
	iter1 = 0;
	while (buf[iter2] != '\0')
	{
		buf[iter1] = buf[iter2];
		iter1++;
		iter2++;
	}
	buf[iter1] = '\0';
	return (new);
}
