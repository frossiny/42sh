/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 15:36:57 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/17 16:43:29 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	free_cmd(t_cmd *cmd)
{
	t_redirect *next;

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

static void	free_node(t_anode *node)
{
	if (!node)
		return ;
	if (node->left)
		free_node(node->left);
	if (node->right)
		free_node(node->right);
	if (node->cmd)
		free_cmd(node->cmd);
	free(node);
}

void		ast_destroy(t_shell *shell)
{
	if (!shell->ast)
		return ;
	free_node(shell->ast);
	shell->ast = NULL;
}
