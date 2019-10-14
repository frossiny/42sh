/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 12:12:12 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/14 14:39:40 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	destroy_tokens(t_token *token)
{
	t_token *next;

	next = NULL;
	while (token)
	{
		next = token->next;
		free(token->content);
		free(token);
		token = next;
	}
}

void	destroy_lexer(t_lexer *lexer)
{
	destroy_tokens(lexer->tokens);
	lexer->tokens = NULL;
	lexer->size = 0;
	update_state(lexer, ST_GENERAL);
}
