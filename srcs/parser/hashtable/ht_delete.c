/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 14:09:30 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/01 14:09:52 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ht_delete(t_shell *shell)
{
	int		i;

	if (!shell->bin_ht.table)
		return ;
	i = -1;
	while (++i < shell->bin_ht.size)
	{
		free(shell->bin_ht.table[i].key);
		free(shell->bin_ht.table[i].value);
	}
	free(shell->bin_ht.table);
}
