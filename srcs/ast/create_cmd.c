/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 13:23:37 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/08 15:43:40 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_cmd			*create_cmd(t_token *exe)
{
	t_cmd	*cmd;

	if (!(cmd = (t_cmd *)malloc(sizeof(t_cmd))))
		return (NULL);
	cmd->exe = exe;
	cmd->argc = -1;
	cmd->args = NULL;
	cmd->redir = NULL;
	cmd->allow_builtins = 1;
	return (cmd);
}
