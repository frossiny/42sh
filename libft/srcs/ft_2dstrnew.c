/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2dstrnew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 17:58:00 by pcharrie          #+#    #+#             */
/*   Updated: 2019/11/07 20:12:34 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_2dstrnew(int size)
{
	char **tab;

	if (!(tab = malloc(sizeof(char*) * (size + 1))))
		return (NULL);
	while (size >= 0)
		tab[size--] = NULL;
	return (tab);
}
