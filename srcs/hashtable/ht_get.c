/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 14:10:30 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/14 15:04:45 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "hashtable.h"

char	*ht_get(t_shell *shell, char *key)
{
	int hash;

	if (!shell->bin_ht.table)
		return (NULL);
	hash = ht_hash(shell->bin_ht.size, key);
	if (shell->bin_ht.table[hash].key)
	{
		if (access(shell->bin_ht.table[hash].value, F_OK)
						|| access(shell->bin_ht.table[hash].value, X_OK))
		{
			ht_delone(key, shell);
			return (NULL);
		}
		return (ft_strdup(shell->bin_ht.table[hash].value));
	}
	return (NULL);
}
