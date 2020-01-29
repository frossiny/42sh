/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 15:17:59 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/29 12:44:04 by frossiny         ###   ########.fr       */
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

int			ast_build(t_shell *shell)
{
	g_child = 0;
	ast_free_cmd(g_shell.current_cmd);
	return (parse_tree(shell->lexer.tokens, &(shell->ast)));
}
