/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 15:36:57 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/17 15:05:35 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ast.h"

static void	free_node(t_anode *node)
{
	if (!node)
		return ;
	if (node->left)
		free_node(node->left);
	if (node->right)
		free_node(node->right);
	if (node->cmd)
		ast_free_cmd(node->cmd);
	free(node);
}

void		ast_free_cmd(t_cmd *cmd)
{
	t_redirect *next;

	free(cmd->args);
	var_destroy(&(cmd->tenv));
	if (cmd == g_shell.current_cmd)
		g_shell.current_cmd = NULL;
	while (cmd->redir)
	{
		next = cmd->redir->next;
		free(cmd->redir);
		cmd->redir = next;
	}
	free(cmd);
}

void		ast_destroy(t_shell *shell)
{
	if (!shell->ast)
		return ;
	free_node(shell->ast);
	shell->ast = NULL;
}
