/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 17:20:17 by frossiny          #+#    #+#             */
/*   Updated: 2018/11/08 14:42:59 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char	*s;
	char	*d;
	size_t	i;

	s = (char *)src;
	d = dst;
	i = -1;
	while (s[++i] != '\0' && i < len)
		d[i] = s[i];
	while (i < len)
		d[i++] = '\0';
	return (d);
}
