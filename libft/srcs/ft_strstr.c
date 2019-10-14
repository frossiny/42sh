/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 18:56:29 by frossiny          #+#    #+#             */
/*   Updated: 2018/11/08 15:43:06 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	char	*hay;
	int		i;

	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	hay = ft_strchr(haystack, *needle);
	while (hay < haystack + ft_strlen(haystack))
	{
		if (!hay)
			return (NULL);
		i = 0;
		while (hay[i] && needle[i] && hay[i] == needle[i])
			i++;
		if (needle[i] == '\0')
			return (hay);
		hay = ft_strchr(hay + 1, *needle);
	}
	return (NULL);
}
