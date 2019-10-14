/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 15:36:57 by frossiny          #+#    #+#             */
/*   Updated: 2019/04/16 14:20:54 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	free_cmd(t_cmd *cmd)
{
	t_redirect *next;

	free(cmd->args);
	while (cmd->redir)
	{
		next = cmd->redir->next;
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

void		destroy_ast(t_shell *shell)
{
	if (!shell->ast)
		return ;
	free_node(shell->ast);
	shell->ast = NULL;
}
