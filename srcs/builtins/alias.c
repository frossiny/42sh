/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:16:26 by vsaltel           #+#    #+#             */
/*   Updated: 2020/02/05 14:20:31 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alias.h"
#include "libft.h"
#include "shell.h"
#include "builtins.h"

int				check_key_chain(char *key)
{
	size_t	i;

	i = 0;
	while (key[i])
	{
		if (key[i] == '`' || key[i] == '/' || key[i] == '\\'
			|| key[i] == '&' || key[i] == '$' || key[i] == ' '
			|| key[i] == '(' || key[i] == ')' || key[i] == ';'
			|| key[i] == '<' || key[i] == '>' || key[i] == '|'
			|| key[i] == 10)
			return (0);
		i++;
	}
	return (1);
}

void			add_alias(t_alias **alias, char *str)
{
	char	*key;
	char	*value;
	char	*tmp;

	if (!(tmp = ft_strchr(str, '=')))
		return ;
	key = ft_strndup(str, tmp - str);
	if (!check_key_chain(key))
	{
		ft_dprintf(2, "42sh: alias: `%s': invalid alias name\n", key);
		free(key);
		return ;
	}
	value = ft_strdup(tmp + 1);
	alias_new(alias, key, value);
}

int				b_alias(t_cmd *cmd, t_shell *shell)
{
	size_t	i;

	if (cmd->argc < 2)
		alias_display_all(shell->alias);
	else
	{
		i = 0;
		while (cmd->args[++i])
		{
			if (cmd->args[i][0] && cmd->args[i][1]
					&& ft_strchr(&(cmd->args[i][1]), '='))
				add_alias(&(shell->alias), cmd->args[i]);
			else
			{
				if (!alias_display_one(shell->alias, cmd->args[i]))
					return (EXIT_FAILURE);
			}
		}
	}
	return (0);
}
