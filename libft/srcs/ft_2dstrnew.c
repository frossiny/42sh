/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2dstrnew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 17:58:00 by pcharrie          #+#    #+#             */
/*   Updated: 2019/11/15 17:37:24 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_2dstrnew(int size)
{
	char	**tab;
	int		i;

	if (!(tab = malloc(sizeof(char*) * (size + 1))))
		return (NULL);
	i = 0;
	while (i < size + 1)
		tab[i++] = NULL;
	return (tab);
}
