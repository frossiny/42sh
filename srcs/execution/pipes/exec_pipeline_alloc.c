/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_alloc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 15:35:53 by frossiny          #+#    #+#             */
/*   Updated: 2020/02/13 14:00:21 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ast.h"
#include "execution.h"

t_pipel		*exec_pipeline_alloc(t_pipel *prev, t_cmd *cmd, t_shell *shell)
{
	t_pipel		*new;

	if (!cmd || !(new = (t_pipel *)malloc(sizeof(t_pipel))))
		return (NULL);
	if (ast_build_args(cmd, shell->vars) < 1)
	{
		free(new);
		return (NULL);
	}
	var_merge(&(cmd->tenv), g_shell.vars);
	new->cmd = cmd;
	new->previous = prev;
	new->pid = -1;
	new->next = NULL;
	return (new);
}
