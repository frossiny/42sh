/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:23:10 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/14 14:53:23 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

int		lex_state_operator(t_lexer *lexer)
{
	t_ex_token	cur;

	cur = lexer_search(lexer->in);
	if (cur.op && cur.type != TOKEN_IGN)
		return (parse_error(cur.op, cur.len, 0));
	else if (cur.op)
	{
		lexer->in += cur.len;
		lexer->pin += cur.len;
	}
	else
		update_state(lexer, ST_GENERAL);
	return (1);
}

int		lex_state_semic(t_lexer *lexer)
{
	t_ex_token	cur;

	cur = lexer_search(lexer->in);
	if (cur.op && cur.type != TOKEN_IGN)
		return (parse_error(cur.op, cur.len, 0));
	else
		update_state(lexer, ST_GENERAL);
	return (1);
}
