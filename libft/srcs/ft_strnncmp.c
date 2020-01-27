/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnncmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 12:46:30 by lubenard          #+#    #+#             */
/*   Updated: 2020/01/27 14:37:08 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int		ft_strnncmp(char *dest, char *src, int start, int end)
{
	int		i;

	i = 0;
	if (start < 0 || end < 0)
		return (0);
	//printf("je suis la je vais comparer %c avec %c \n", dest[start], src[i]);
	while (dest[start] && src[i] && dest[start] == src[i] && start != end)
	{
		//printf("Je regarde %c\n", dest[start]);
		start++;
		i++;
	}
	//printf("Je vais retourner %d\n\
//Les dernier chars a avoir ete compare sont %c / %c \n",(unsigned char)dest[start] - (unsigned char)src[i], dest[start], src[i]);
	return ((unsigned char)dest[start] - (unsigned char)src[i]);
}
