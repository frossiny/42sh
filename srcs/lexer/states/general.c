/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:17:47 by frossiny          #+#    #+#             */
/*   Updated: 2019/07/29 19:30:41 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static int	is_redirection(char *str, t_ex_token *tok)
{
	int			i;
	t_ex_token	cur;

	i = 0;
	if (!ft_isdigit(*str))
		return (0);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	cur = lexer_search(str + i);
	if (cur.op && (cur.type == TOKEN_REDIRO || cur.type == TOKEN_REDIRI
												|| cur.type == TOKEN_AGGR))
	{
		*tok = cur;
		return (i + cur.len);
	}
	return (0);
}

static void	lex_state_general_else(t_lexer *lexer)
{
	if ((*(lexer->in) == '"' || *(lexer->in) == '\'')
						&& !is_escaped(lexer->pin, lexer->in - lexer->pin, 0))
	{
		update_state(lexer, *(lexer->in) == '"' ? ST_DQUOTES : ST_QUOTES);
	}
	else if (*(lexer->in) == '\\'
						&& !is_escaped(lexer->pin, lexer->in - lexer->pin, 0))
		update_state(lexer, ST_ESCAPED);
	else if (*(lexer->in) == '#'
						&& !is_escaped(lexer->pin, lexer->in - lexer->pin, 0))
	{
		create_token(lexer, lexer->pin, lexer->in - lexer->pin, TOKEN_NAME);
		lexer->pin = lexer->in;
		update_state(lexer, ST_COMMENT);
	}
	lexer->in++;
}

int			lex_state_general(t_lexer *lex)
{
	t_ex_token	cur;
	int			tmp;

	cur = lexer_search(lex->in);
	if (cur.op)
	{
		if (lex->in > lex->pin)
			create_token(lex, lex->pin, lex->in - lex->pin, TOKEN_NAME);
		if (cur.type != TOKEN_IGN)
			create_token(lex, lex->in, cur.len, cur.type);
		update_state(lex, cur.state);
		lex->pin = (lex->in += cur.len);
	}
	else if (ft_isdigit(*(lex->in)) && (tmp = is_redirection(lex->in, &cur)))
	{
		if (lex->in > lex->pin)
			create_token(lex, lex->pin, lex->in - lex->pin, TOKEN_NAME);
		create_token(lex, lex->in, tmp, cur.type);
		update_state(lex, ST_OPERATOR);
		lex->pin = (lex->in += tmp);
	}
	else
		lex_state_general_else(lex);
	return (1);
}
