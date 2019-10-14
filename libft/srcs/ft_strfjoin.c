/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 14:21:20 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/21 14:22:10 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strfjoin(char const *s1, char const *s2, char const *f)
{
	char	*dst;

	if (!s1 || !s2 || !(dst = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	ft_strcpy(dst, s1);
	ft_strcat(dst, s2);
	free((char *)f);
	return (dst);
}
