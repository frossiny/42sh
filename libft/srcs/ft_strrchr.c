/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 18:42:37 by frossiny          #+#    #+#             */
/*   Updated: 2018/11/08 17:46:48 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*src;

	src = (char *)s + ft_strlen(s);
	while (src >= s)
	{
		if (*src == (char)c)
			return (src);
		src--;
	}
	return (NULL);
}
