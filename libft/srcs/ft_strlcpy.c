/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 11:43:34 by frossiny          #+#    #+#             */
/*   Updated: 2018/11/09 12:08:56 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (!dst || !src)
		return (0);
	if (dstsize == 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] && i < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize <= ft_strlen(src))
		dst[i - 1] = '\0';
	else
		dst[i] = '\0';
	return (ft_strlen(src));
}
