/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 13:08:41 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/18 16:05:37 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "builtins.h"
#include "opt.h"
#include "hashtable.h"

int		display_hash_table(t_hashtable table)
{
	int i;

	i = 0;
	ft_putendl("hits    command");
	while (i != table.size)
	{
		if (table.table[i].key)
			ft_printf("%4zu    %s\n", table.table[i].occurence,
				table.table[i].value);
		i++;
	}
	return (0);
}

int		b_hash(t_cmd *cmd, t_shell *shell)
{
	t_options	*opts;

	opts = opt_parse(cmd, "r", "hash");
	if (opts->ret != 0)
		ft_putendl_fd("hash: usage: hash [-r]", 2);
	else if (shell->bin_ht.table && opts->last == 1)
		display_hash_table(shell->bin_ht);
	else if (opts->opts && !ft_strcmp(opts->opts->opt, "r"))
	{
		if (shell->bin_ht.table)
			ht_delete();
	}
	else
		ft_putendl("hash: hash table empty");
	opt_free(opts);
	return (0);
}
