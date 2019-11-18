/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 13:23:37 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/18 16:11:21 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "expansion.h"

static void		parse_assignements(t_cmd *cmd, t_token **exe)
{
	char	**tmp;

	cmd->tenv = NULL;
	while (*exe && (*exe)->type == TOKEN_ASSIGNMENT)
	{
		if (!expand(*exe))
			break ;
		if (!(tmp = ft_strsplit((*exe)->content, '=')))
			break ;
		var_set(&(cmd->tenv), tmp[0], tmp[1], 1);
		ft_strddel(&tmp);
		(*exe) = (*exe)->next;
	}
}

t_cmd			*create_cmd(t_token *exe)
{
	t_cmd	*cmd;

	if (!(cmd = (t_cmd *)malloc(sizeof(t_cmd))))
		return (NULL);
	parse_assignements(cmd, &exe);
	cmd->exe = exe;
	cmd->argc = -1;
	cmd->args = NULL;
	cmd->redir = NULL;
	cmd->allow_builtins = 1;
	return (cmd);
}
