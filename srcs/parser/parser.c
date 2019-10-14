/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 15:17:59 by frossiny          #+#    #+#             */
/*   Updated: 2019/07/29 10:34:07 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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

static int	parse_condition(int *ret, t_anode *cond, t_shell *shell)
{
	if (cond->ope->type == TOKEN_AND)
	{
		if (*ret != 0)
			return (0);
		*ret = execute(cond->right->cmd, shell);
		return (1);
	}
	else if (cond->ope->type == TOKEN_OR)
	{
		if (*ret == 0)
			return (0);
		*ret = execute(cond->right->cmd, shell);
		return (1);
	}
	else
		return (1);
}

int			parse(t_shell *shell, t_anode *ast)
{
	while (ast->left)
		ast = ast->left;
	while (ast)
	{
		if (!ast->ope && !is_pipe_node(ast->parent))
			g_return = execute(ast->cmd, shell);
		else if (is_pipe_node(ast->parent))
			g_return = execute_pipes(ast, shell, &ast);
		else if (is_cond_node(ast))
		{
			if (!parse_condition(&g_return, ast, shell))
				return (g_return);
		}
		ast ? ast = ast->parent : 0;
	}
	return (g_return);
}
