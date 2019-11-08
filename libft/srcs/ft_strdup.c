/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 17:02:17 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/01 16:27:28 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dest;

	if (!s1)
		return (NULL);
	if (!(dest = ft_strnew(ft_strlen(s1))))
		return (NULL);
	return (ft_strcpy(dest, s1));
}
