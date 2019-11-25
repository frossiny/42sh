/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_del_empty_tokens.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 10:27:05 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/25 10:32:09 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "expansion.h"

t_token		*exp_del_empty_tokens(t_token *token, t_cmd *cmd)
{
	t_token	*prev;
	t_token	*curr;
	t_token	*next;

	exp_tok_clean(token);
	if (cmd->exe == token)
		cmd->exe = token->next;
	else if (cmd->exe->next)
	{
		prev = NULL;
		curr = cmd->exe->next;
		while (curr)
		{
			next = curr->next;
			if (curr == token)
				prev->next = token->next;
			curr = next;
		}
	}
	next = token->next;
	tok_free(token);
	if (!next)
		return (next);
	else
		return (next->next);
}
