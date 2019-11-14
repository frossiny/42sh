/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unalias.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:48:26 by vsaltel           #+#    #+#             */
/*   Updated: 2019/11/13 14:06:57 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "alias.h"
#include "shell.h"
#include "builtins.h"

void			alias_del_aft(t_alias *alias, char *key)
{
	t_alias *tmp;
	t_alias *bef;

	bef = NULL;
	while (alias)
	{
		if (bef && ft_strcmp(alias->key, key) == 0)
		{
			tmp = alias->next;
			alias_free_one(alias);
			bef->next = tmp;
			alias = bef;
		}
		bef = alias;
		alias = alias->next;
	}
}

void			alias_del(t_alias **list, char *key)
{
	t_alias *tmp;

	if (!list || !*list || !key)
		return ;
	if (ft_strcmp((*list)->key, key) == 0)
	{
		tmp = (*list)->next;
		alias_free_one(*list);
		*list = tmp;
		return ;
	}
	alias_del_aft(*list, key);
}

int				b_unalias(t_cmd *cmd, t_shell *shell)
{
	size_t	i;
	size_t	unfined;

	unfined = 0;
	i = 0;
	while (cmd->args[++i])
	{
		if (alias_get(shell->alias, cmd->args[i]))
			alias_del(&(shell->alias), cmd->args[i]);
		else
		{
			ft_printf("42sh: unalias: %s: not found\n", cmd->args[i]);
			unfined++;
		}
	}
	if (unfined)
		return (1);
	return (0);
}
