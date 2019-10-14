/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 17:02:17 by frossiny          #+#    #+#             */
/*   Updated: 2019/03/01 15:05:05 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t len)
{
	char	*dest;

	if (!(dest = ft_strnew(len)))
		return (NULL);
	return (ft_strncpy(dest, s1, len));
}
