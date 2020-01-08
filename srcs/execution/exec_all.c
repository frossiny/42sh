/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 15:17:59 by frossiny          #+#    #+#             */
/*   Updated: 2019/12/03 13:10:06 by frossiny         ###   ########.fr       */
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

static int	parse_condition(int *ret, t_anode *cond)
{
	if (cond->ope->type == TOKEN_AND)
	{
		if (*ret != 0)
			return (1);
		*ret = exec_command(cond->right->cmd);
		return (1);
	}
	else if (cond->ope->type == TOKEN_OR)
	{
		if (*ret == 0)
			return (1);
		*ret = exec_command(cond->right->cmd);
		return (1);
	}
	else
		return (1);
}

int			exec_all(t_shell *shell, t_anode *ast)
{
	int		ret;

	ret = 0;
	while (ast->left)
		ast = ast->left;
	while (ast)
	{
		if (!ast->ope && !is_pipe_node(ast->parent))
			ret = exec_command(ast->cmd);
		else if (is_pipe_node(ast->parent))
			ret = exec_pipes(ast, shell, &ast);
		else if (is_cond_node(ast))
		{
			if (!parse_condition(&ret, ast))
				return (ret);
		}
		ast ? ast = ast->parent : 0;
	}
	return (ret);
}
