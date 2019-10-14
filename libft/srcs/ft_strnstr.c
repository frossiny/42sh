/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 19:33:51 by frossiny          #+#    #+#             */
/*   Updated: 2018/11/08 15:45:16 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*hay;
	int		i;
	char	*n;

	n = (char *)needle;
	if (ft_strlen(n) == 0)
		return ((char *)haystack);
	hay = ft_strchr(haystack, *n);
	while (hay < haystack + ft_strlen(haystack) && haystack + len > hay)
	{
		if (!hay)
			return (NULL);
		i = 0;
		while (hay[i] && n[i] && hay[i] == n[i] && haystack + len > hay + i)
			i++;
		if (n[i] == '\0')
			return (hay);
		hay = ft_strchr(hay + 1, *n);
	}
	return (NULL);
}
