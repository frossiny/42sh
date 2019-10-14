/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnfjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 14:21:20 by vsaltel           #+#    #+#             */
/*   Updated: 2019/05/06 13:01:21 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strfnjoin(char const *s1, char const *s2,
		size_t n, char const *f)
{
	char	*dst;

	if (!s1 || !s2 || !(dst = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	ft_strcpy(dst, s1);
	ft_strncat(dst, s2, n);
	free((char *)f);
	return (dst);
}
