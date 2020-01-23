/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 15:36:57 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/22 16:25:43 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ast.h"
#include "lexer.h"

static void	free_node(t_anode *node)
{
	if (!node)
		return ;
	if (node->left)
		free_node(node->left);
	if (node->right)
		free_node(node->right);
	if (node->cmd)
		g_shell.current_cmd != node->cmd ? ast_free_cmd(node->cmd) : 0;
	free(node);
}

void		ast_free_cmd(t_cmd *cmd)
{
	t_redirect *next;

	if (!cmd)
		return ;
	if (g_shell.current_cmd == cmd)
		tok_destroy(cmd->tokens);
	free(cmd->args);
	var_destroy(&(cmd->tenv));
	if (cmd == g_shell.current_cmd)
		g_shell.current_cmd = NULL;
	while (cmd->redir)
	{
		next = cmd->redir->next;
		if (cmd->redir->heredoc)
			ft_2dstrdel(&cmd->redir->heredoc);
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
