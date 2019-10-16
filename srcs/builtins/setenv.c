/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 14:30:34 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/16 13:48:00 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static int	is_unique_key(t_var *vars, char *key, char *value)
{
	while (vars)
	{
		if (ft_strcmp(vars->key, key) == 0)
		{
			free(vars->value);
			if (!(vars->value = ft_strdup(value)))
				exit(1);
			return (1);
		}
		vars = vars->next;
	}
	return (0);
}

static int	is_key_valid(char *str)
{
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

int			b_setenv(t_cmd *cmd, t_shell *shell)
{
	if (cmd->argc == 1)
		return (var_display(shell->vars));
	else if (cmd->argc > 3)
	{
		write(2, "setenv: Too many arguments.\n", 28);
		return (1);
	}
	else if (!ft_isalpha(cmd->args[1][0]) && cmd->args[1][0] != '_')
	{
		write(2, "setenv: Variable name must begin with a letter.\n", 48);
		return (2);
	}
	else if (!is_key_valid(cmd->args[1]))
	{
		write(2,
		"setenv: Variable name must contain alphanumeric characters.\n", 60);
		return (3);
	}
	if (is_unique_key(shell->vars, cmd->args[1],
										cmd->argc == 3 ? cmd->args[2] : ""))
		return (0);
	if (!(var_set(&(shell->vars), cmd->args[1],
										cmd->argc > 2 ? cmd->args[2] : "", 0)))
		return (1);
	return (0);
}
