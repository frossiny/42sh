/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 17:41:06 by frossiny          #+#    #+#             */
/*   Updated: 2018/11/06 17:42:35 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char *dst;

	dst = s1 + ft_strlen(s1);
	while (*s2 && n--)
		*dst++ = *s2++;
	*dst = '\0';
	return (s1);
}
