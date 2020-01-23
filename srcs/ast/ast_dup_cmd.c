/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_dup_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 16:10:07 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/22 17:02:48 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "lexer.h"

static t_token	*dup_tokens(t_token *src)
{
	t_token	*start;
	t_token	*curr;

	start = tok_new(src->type, src->content);
	curr = start;
	src = src->next;
	while (src)
	{
		curr->next = tok_new(src->type, src->content);
		curr = curr->next;
		src = src->next;
	}
	return (start);
}

t_cmd			*ast_dup_cmd(t_cmd *src)
{
	t_cmd	*new;

	if (!src || !(new = (t_cmd *)malloc(sizeof(t_cmd))))
		return (NULL);
	new->tokens = dup_tokens(src->tokens);
	new->tenv = NULL;
	new->args = NULL;
	new->argc = 0;
	new->allow_builtins = 0;
	new->exe = NULL;
	new->is_bg = 0;
	new->redir = NULL;
	new->exe_found = src->exe_found;
	return (new);
}
