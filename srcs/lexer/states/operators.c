/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:23:10 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/23 19:03:43 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

int		lex_state_operator(t_lexer *lex)
{
	t_ex_token	cur;

	cur = lexer_search(lex->in);
	if (cur.op)
	{
		if (lex->in > lex->pin)
			tok_create(lex, lex->pin, lex->in - lex->pin, TOKEN_NAME);
		if (cur.type != TOKEN_IGN)
			tok_create(lex, lex->in, cur.len, cur.type);
		lex->in += cur.len;
		lex->pin = lex->in;
	}
	else
		lex_update_state(lex, ST_GENERAL);
	return (1);
}
