/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 14:09:05 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/12 18:51:07 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ht_create(t_shell *shell, size_t size)
{
	t_hashval	*htab;
	size_t		i;

	if (shell->bin_ht.table)
		return (0);
	if (!(htab = (t_hashval *)malloc(sizeof(t_hashval) * size)))
		return (0);
	shell->bin_ht.size = size;
	i = -1;
	while (++i < size)
	{
		htab[i].key = NULL;
		htab[i].value = NULL;
		htab[i].occurence = 0;
	}
	shell->bin_ht.table = htab;
	return (1);
}
