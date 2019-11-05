/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:16:26 by vsaltel           #+#    #+#             */
/*   Updated: 2019/11/05 18:21:55 by vsaltel          ###   ########.fr       */
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
		if (key[i] == '`' || key[i] == '/' || key[i] == '\\' || key[i] == '$')
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
	{
		ft_printf("42sh: alias: %s: not found\n", str);
		return ;
	}
	key = ft_strndup(str, tmp - str);
	if (!check_key_chain(key))
	{
		ft_printf("42sh: alias: %s: invalid alias name\n", key);
		free(key);
		return ;
	}
	if (ft_strchr(key, '/') || ft_strchr(key, '/'))
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
			add_alias(&(shell->alias), cmd->args[i]);
	}
	return (0);
}
