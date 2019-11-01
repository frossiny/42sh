/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 14:08:15 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/14 15:03:10 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ht_hash(size_t size, char *key)
{
	unsigned int	hash;
	unsigned int	g;
	register char	*p;

	hash = 0;
	p = key;
	while (*p)
	{
		hash = (hash << 4) + *p;
		if ((g = hash & 0xf0000000))
		{
			hash ^= g >> 24;
			hash ^= g;
		}
		p++;
	}
	return (hash % size);
}
