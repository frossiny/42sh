/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:55:33 by vsaltel           #+#    #+#             */
/*   Updated: 2020/02/18 14:43:41 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alias.h"
#include "shell.h"
#include "structs.h"
#include "lexer.h"

static void		free_empty_tok(t_token **tok)
{
	t_token		*token;
	t_token		*prev;
	t_token		*tmp;

	token = *tok;
	prev = NULL;
	while (token)
	{
		tmp = token->next;
		if (token->content && !token->content[0])
		{
			if (token == *tok)
				*tok = tmp;
			else if (prev)
				prev->next = token->next;
			tok_free(token);
			token = NULL;
		}
		prev = token;
		token = tmp;
	}
}

int				alias_exec(t_shell *shell)
{
	int		ret;

	if (!shell->alias)
		return (1);
	ret = alias_recursive(shell->alias, shell->lexer.tokens, NULL, NULL);
	free_empty_tok(&shell->lexer.tokens);
	return (ret);
}
