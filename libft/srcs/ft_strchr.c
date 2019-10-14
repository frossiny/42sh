/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 18:38:44 by frossiny          #+#    #+#             */
/*   Updated: 2018/11/15 17:20:29 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*src;

	src = (char *)s;
	while (*src)
	{
		if (*src == (char)c)
			return (src);
		src++;
	}
	if (*src == (char)c)
		return (src);
	return (NULL);
}
