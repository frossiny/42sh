/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_dup_escape.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 18:10:45 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/17 18:32:06 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	*exp_dup_escape(char *src, t_expansion *exp)
{
	char	*dst;
	size_t	i;

	if (!(dst = (char *)malloc(ft_strlen(src) * 2 + 1)))
		return (NULL);
	i = 0;
	while (*src)
	{
		if (!exp->isquote || *src == '\\')
			dst[i++] = '\\';
		dst[i++] = *src;
		src++;
	}
	dst[i] = '\0';
	return (dst);
}
