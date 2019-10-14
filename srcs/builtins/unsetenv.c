/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:29:33 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/15 14:57:06 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static void	free_link(t_env *link)
{
	free(link->key);
	free(link->value);
	free(link);
}

int			delete_env(t_env **env, char *key)
{
	t_env *prev;
	t_env *current;
	t_env *next;

	current = *env;
	if (!current)
		return (1);
	prev = NULL;
	while (current && ft_strcmp(current->key, key))
	{
		prev = current;
		current = current->next;
	}
	if (!current)
		return (0);
	next = current->next;
	free_link(current);
	if (prev)
		prev->next = next;
	else
		*env = next;
	return (1);
}

int			b_unsetenv(t_cmd *cmd, t_shell *shell)
{
	int		i;

	if (cmd->argc < 2)
	{
		write(2, "setenv: Too few arguments.\n", 27);
		return (1);
	}
	i = 1;
	while (i < cmd->argc)
	{
		if (!cmd->args[i])
			break ;
		delete_env(&(shell->env), cmd->args[i++]);
	}
	return (0);
}
