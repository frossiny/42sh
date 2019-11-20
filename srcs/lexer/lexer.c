/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 11:23:45 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/20 18:53:59 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "lexer.h"
#include "utils.h"

const static t_state_func	g_state_funcs[] =
{
	{ ST_GENERAL, &lex_state_general },
	{ ST_QUOTES, &lex_state_quotes },
	{ ST_DQUOTES, &lex_state_quotes },
	{ ST_ESCAPED, &lex_state_escaped },
	{ ST_COMMENT, &lex_state_comment },
	{ ST_OPERATOR, &lex_state_operator },
	{ ST_EXPANSIONS, &lex_state_expansions},
	{ -1, NULL }
};

static t_state_func	get_func(t_state state)
{
	const t_state_func	null_state = { -1, NULL };
	int					i;

	i = 0;
	while (g_state_funcs[i].lex)
	{
		if (g_state_funcs[i].key == state)
			return (g_state_funcs[i]);
		i++;
	}
	return (null_state);
}

static int			lex_end(t_lexer *lexer)
{
	if (lexer->state == ST_GENERAL)
	{
		if (lexer->in > lexer->pin)
			tok_create(lexer, lexer->pin, lexer->in - lexer->pin, TOKEN_NAME);
	}
	else
	{
		if (lexer->state == ST_EXPANSIONS)
			return (-2);
		else if (lexer->state == ST_DQUOTES)
			return (-2);
		else if (lexer->state == ST_QUOTES)
			return (-2);
		else if (lexer->state == ST_ESCAPED)
			return (-3);
	}
	return (1);
}

static int			lex_loop(t_lexer *lexer)
{
	int				ret;
	t_state_func	cur;

	while (lexer->in && *(lexer->in))
	{
		cur = get_func(lexer->state);
		if (cur.lex)
		{
			if ((ret = cur.lex(lexer)) < 1)
				return (ret);
		}
		else
			return (-1);
	}
	return (lex_end(lexer));
}

int					lex(char *s, t_lexer *lexer)
{
	if (!s)
		return (1);
	lexer->in = s;
	lexer->pin = s;
	return (lex_loop(lexer));
}
