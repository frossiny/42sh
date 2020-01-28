/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 15:17:59 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/28 13:44:28 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "ast.h"
#include "shell.h"

static int	parse_tree(t_token *tokens, t_anode **ast)
{
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE || tokens->type == TOKEN_AND
											|| tokens->type == TOKEN_OR)
		{
			if (!*ast)
				return (0);
			tokens = create_ope_node(ast, tokens);
		}
		else if (tok_is_cmd_comp(tokens))
			tokens = create_cmd_node(ast, tokens);
		else if (tokens->type == TOKEN_SEMI)
			tokens = tokens->next;
		else
			break ;
	}
	return (1);
}

void print(t_anode *node)
{
	if (node->left)
		print(node->left);
	if (node->right)
		print(node->right);
	if (node->ope)
		ft_printf("OPE NODE: %p -> %p = %s\n", node->parent, node, node->ope->content);
	else
		ft_printf("CMD NODE: %p -> %p = %s\n", node->parent, node, node->cmd->tokens->content);
}

int			ast_build(t_shell *shell)
{
	g_child = 0;
	ast_free_cmd(g_shell.current_cmd);
	parse_tree(shell->lexer.tokens, &(shell->ast));

	t_anode *curr = g_shell.ast;
	print(curr);
	// while (curr)
	// 	curr = curr->left;

	return (0);
}
