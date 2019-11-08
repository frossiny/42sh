/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:17:47 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/04 14:23:01 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"
#include "utils.h"

static void	lex_state_redirection(t_lexer *lex)
{
	int			i;
	t_ex_token	cur;

	i = 0;
	while (lex->in[i] && ft_isdigit(lex->in[i]))
		i++;
	cur = lexer_search(lex->in + i);
	if (cur.op && (cur.type == TOKEN_REDIRO || cur.type == TOKEN_REDIRI
												|| cur.type == TOKEN_AGGR))
	{
		tok_create(lex, lex->pin, lex->in + i - lex->pin, TOKEN_IO_FD);
		tok_create(lex, lex->in + i, cur.len, cur.type);
		lex->in += i + cur.len;
		lex->pin = lex->in;
	}
	else
		lex->in += i;
}

static void	lex_state_general_else(t_lexer *lexer)
{
	if ((lexer->in[0] == '"' || lexer->in[0] == '\'')
						&& !is_escaped(lexer->pin, lexer->in - lexer->pin, 0))
	{
		lex_update_state(lexer, lexer->in[0] == '"' ? ST_DQUOTES : ST_QUOTES);
	}
	else if (lexer->in[0] == '\\'
						&& !is_escaped(lexer->pin, lexer->in - lexer->pin, 0))
		lex_update_state(lexer, ST_ESCAPED);
	else if (lexer->in[0] == '#'
						&& !is_escaped(lexer->pin, lexer->in - lexer->pin, 0))
	{
		if (lexer->in > lexer->pin)
			tok_create(lexer, lexer->pin, lexer->in - lexer->pin, TOKEN_NAME);
		lexer->pin = lexer->in;
		lex_update_state(lexer, ST_COMMENT);
	}
	else if (lex_is_expansion(lexer))
	{
		lex_update_state(lexer, ST_EXPANSIONS);
		return ;
	}
	lexer->in++;
}

int			lex_state_general(t_lexer *lex)
{
	t_ex_token	cur;

	cur = lexer_search(lex->in);
	if (cur.op)
		lex_update_state(lex, cur.state);
	else if (lex->pin == lex->in && ft_isdigit(lex->in[0]))
		lex_state_redirection(lex);
	else
		lex_state_general_else(lex);
	return (1);
}
