/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_exists.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 14:10:53 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/01 14:11:03 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			ht_exists(t_shell *shell, char *key)
{
	int hash;

	if (shell->bin_ht.table == NULL)
		return (0);
	hash = ht_hash(shell->bin_ht.size, key);
	if (shell->bin_ht.table[hash].key)
		return (1);
	return (0);
}
