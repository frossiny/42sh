/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 11:53:12 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/07 17:34:23 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "lexer.h"
#include "ast.h"
#include "alias.h"
#include "termcaps.h"
#include "hashtable.h"

static int	check_arg(t_cmd *cmd)
{
	if (!ft_strisdigit(cmd->args[1]))
	{
		write(2, "exit: Numeric argument required\n", 32);
		return (0);
	}
	return (1);
}

int			b_exit(t_cmd *cmd, t_shell *shell)
{
	int		ret;

	if (cmd->argc > 2)
	{
		write(2, "exit: Too many arguments\n", 25);
		return (1);
	}
	ret = g_return;
	if (cmd->argc == 2 && !check_arg(cmd))
		ret = 1;
	else if (cmd->argc == 2)
		ret = ft_atoi(cmd->args[1]);
	ft_strdel(&g_pwd);
	var_destroy(&(shell->vars));
	alias_free_all(&(shell->alias));
	free_termcaps(shell);
	lexer_free(&(shell->lexer));
	ast_destroy(shell);
	ht_delete(shell);
	free(g_pwd);
	exit(ret);
	return (ret);
}
