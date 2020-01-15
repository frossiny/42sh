/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unalias.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:48:26 by vsaltel           #+#    #+#             */
/*   Updated: 2020/01/15 13:42:54 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "alias.h"
#include "structs.h"
#include "builtins.h"
#include "opt.h"

static void		unalias_del_aft(t_alias *alias, char *key)
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

static void		unalias_del(t_alias **list, char *key)
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
	unalias_del_aft(*list, key);
}

static int		unalias_opt(t_cmd *cmd, t_shell *shell)
{
	t_options	*options;
	int			ret;

	options = opt_parse(cmd, "a", "unalias");
	if (options->ret != 0)
	{
		if (options->ret == -1)
			ft_dprintf(2, "unalias: usage: unalias [-a] name [name ...]\n");
		ret = 2;
	}
	else if (opt_get(options, "a"))
	{
		alias_free_all(&(shell->alias));
		ret = 0;
	}
	else
		ret = 1;
	opt_free(options);
	return (ret);
}

int				b_unalias(t_cmd *cmd, t_shell *shell)
{
	size_t		i;
	size_t		unfind;
	int			ret;

	unfind = 0;
	i = 0;
	ret = unalias_opt(cmd, shell);
	if (ret == 0 || ret == 2)
		return (ret);
	while (cmd->args[++i])
	{
		if (alias_get(shell->alias, cmd->args[i]))
			unalias_del(&(shell->alias), cmd->args[i]);
		else
		{
			ft_dprintf(2, "42sh: unalias: %s: not found\n", cmd->args[i]);
			unfind++;
		}
	}
	ret = unfind ? 1 : 0;
	return (ret);
}
