/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 12:32:30 by frossiny          #+#    #+#             */
/*   Updated: 2018/11/06 16:47:32 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	void	*chr;
	int		len;

	if (n == 0)
		return (NULL);
	chr = ft_memchr(src, c, n);
	if (!chr)
	{
		ft_memcpy(dst, src, n);
		return (NULL);
	}
	len = (unsigned char *)chr - (unsigned char *)src + 1;
	ft_memcpy(dst, src, len);
	return (dst + len);
}
