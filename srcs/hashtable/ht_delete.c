/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 14:09:30 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/14 13:00:13 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ht_delete()
{
	int		i;

	if (!g_shell.bin_ht.table)
		return ;
	i = -1;
	while (++i < g_shell.bin_ht.size)
	{
		free(g_shell.bin_ht.table[i].key);
		free(g_shell.bin_ht.table[i].value);
	}
	free(g_shell.bin_ht.table);
}
