/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpathfile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 18:43:46 by vsaltel           #+#    #+#             */
/*   Updated: 2020/01/27 16:06:50 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	strl_pathfile(const char *s1, const char *s2)
{
	size_t i;
	size_t y;

	i = 0;
	y = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i])
		i++;
	if (s1[i - 1] != '/')
		i++;
	while (s2[y])
		y++;
	y++;
	return (i + y);
}

char			*ft_strpathfile(const char *s1, const char *s2)
{
	size_t	i;
	char	*dst;

	if (!s1 || !s2)
		return (0);
	if (!(dst = malloc(sizeof(char) * strl_pathfile(s1, s2))))
		return (0);
	i = 0;
	while (*s1)
		dst[i++] = *s1++;
	if (dst[i - 1] != '/')
		dst[i++] = '/';
	while (*s2)
		dst[i++] = *s2++;
	dst[i] = '\0';
	return (dst);
}
