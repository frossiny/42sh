/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:47:58 by frossiny          #+#    #+#             */
/*   Updated: 2019/02/15 14:06:14 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	int		len;
	char	*str;

	len = 0;
	str = (char *)s;
	if (str == NULL)
		return (0);
	while (*str++ != '\0')
		len++;
	return (len);
}
