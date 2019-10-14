/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 12:12:12 by frossiny          #+#    #+#             */
/*   Updated: 2019/07/29 15:22:48 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
