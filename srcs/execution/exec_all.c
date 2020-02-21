/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 15:17:59 by frossiny          #+#    #+#             */
/*   Updated: 2020/02/21 14:26:10 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "execution.h"

static int	is_pipe_node(t_anode *node)
{
	if (!node || !node->ope)
		return (0);
	return (node->ope->type == TOKEN_PIPE);
}

static int	is_cond_node(t_anode *node)
{
	if (!node || !node->ope)
		return (0);
	return (node->ope->type == TOKEN_AND || node->ope->type == TOKEN_OR);
}

static int	parse_condition(int *ret, t_anode **ast, t_shell *shell)
{
	t_anode	*node;

	if ((*ast)->ope->type == TOKEN_AND && *ret != 0)
		return (1);
	if ((*ast)->ope->type == TOKEN_OR && *ret == 0)
		return (1);
	if (is_pipe_node((*ast)->right))
	{
		node = (*ast)->right;
		while (node->left)
			node = node->left;
		*ret = exec_pipes(node, shell, ast);
	}
	else
		*ret = exec_command((*ast)->right->cmd);
	return (1);
}

int			exec_all(t_shell *shell, t_anode *ast)
{
	while (ast->left)
		ast = ast->left;
	while (ast)
	{
		if (!ast->ope && !is_pipe_node(ast->parent))
			g_return = exec_command(ast->cmd);
		else if (is_cond_node(ast))
		{
			if (!parse_condition(&g_return, &ast, shell))
				return (g_return);
		}
		else if (is_pipe_node(ast->parent))
			g_return = exec_pipes(ast, shell, &ast);
		ast ? ast = ast->parent : 0;
	}
	g_child = 0;
	return (g_return);
}
