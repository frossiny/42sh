/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stradd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 15:47:17 by lubenard          #+#    #+#             */
/*   Updated: 2020/01/26 15:48:23 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_stradd(char *s1, char s2)
{
	char	*dst;
	int		i;

	i = 0;
	if (!s1 || !s2 || !(dst = ft_strnew(ft_strlen(s1) + 1)))
		return (NULL);
	ft_strcpy(dst, s1);
	dst[ft_strlen(s1)] = s2;
	return (dst);
}
