/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 15:17:59 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/28 13:44:55 by frossiny         ###   ########.fr       */
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
	if ((*ast)->ope->type == TOKEN_AND)
	{
		if (*ret != 0)
			return (1);
		if (is_pipe_node((*ast)->right))
			*ret = exec_pipes((*ast)->right, shell, ast);
		else
			*ret = exec_command((*ast)->right->cmd);
		return (1);
	}
	else if ((*ast)->ope->type == TOKEN_OR)
	{
		if (*ret == 0)
			return (1);
		*ret = exec_command((*ast)->right->cmd);
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
		ft_printf("AST EXE: %p | %p\n", ast->ope, ast->cmd);
		if (!ast->ope && !is_pipe_node(ast->parent))
			ret = exec_command(ast->cmd);
		else if (is_cond_node(ast))
		{
			if (!parse_condition(&ret, &ast, shell))
				return (ret);
		}
		else if (is_pipe_node(ast->parent))
			ret = exec_pipes(ast, shell, &ast);
		ast ? ast = ast->parent : 0;
	}
	return (ret);
}
