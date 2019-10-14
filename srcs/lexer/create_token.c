/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:03:37 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/20 13:55:39 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

t_token	*create_token(t_lexer *lexer, char *content,
												size_t len, t_token_type type)
{
	t_token *token;

	if (!lexer || !(token = (t_token *)malloc(sizeof(t_token))))
		return (NULL);
	if (!(token->content = ft_strndup(content, len)))
		return (NULL);
	token->len = len;
	token->type = type;
	token->next = NULL;
	if (lexer->tokens)
		push_token(lexer->tokens, token);
	else
		lexer->tokens = token;
	(lexer->size)++;
	lexer->last_token = token;
	return (token);
}
