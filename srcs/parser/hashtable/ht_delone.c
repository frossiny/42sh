/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_delone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 15:18:09 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/07 15:35:07 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ht_delone(char *key, t_shell *shell)
{
	int hash;

	if (!shell->bin_ht.table)
		return (0);
	hash = ht_hash(shell->bin_ht.size, key);
	if (shell->bin_ht.table[hash].key)
	{
		free(shell->bin_ht.table[hash].key);
		shell->bin_ht.table[hash].key = NULL;
		free(shell->bin_ht.table[hash].value);
		shell->bin_ht.table[hash].value = NULL;
		return (1);
	}
	return (0);
}
