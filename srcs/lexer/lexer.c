/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 11:23:45 by frossiny          #+#    #+#             */
/*   Updated: 2019/07/29 15:33:29 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

const static t_state_func	g_state_funcs[] =
{
	{ ST_GENERAL, &lex_state_general },
	{ ST_QUOTES, &lex_state_quotes },
	{ ST_DQUOTES, &lex_state_quotes },
	{ ST_ESCAPED, &lex_state_escaped },
	{ ST_COMMENT, &lex_state_comment },
	{ ST_OPERATOR, &lex_state_operator },
	{ ST_SEMIC, &lex_state_semic },
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
			create_token(lexer, lexer->pin, lexer->in - lexer->pin, TOKEN_NAME);
	}
	else
	{
		if (lexer->state == ST_DQUOTES)
			return (-3);
		else if (lexer->state == ST_QUOTES)
			return (-2);
		else if (lexer->state == ST_SEMIC)
			return (1);
		else if (lexer->state == ST_COMMENT)
			return (1);
		else
			return (parse_error(lexer->pin, lexer->in - lexer->pin + 1, -1));
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
			return (parse_error("", 0, 0));
	}
	return (lex_end(lexer));
}

int					lex(char *s, t_lexer *lexer)
{
	size_t	last_char;

	if (!s)
		return (1);
	last_char = ft_strlen(s) - 1;
	if (*s && s[last_char] == '\\' && !is_escaped(s, last_char, 0))
		return (-4);
	lexer->in = s;
	lexer->pin = s;
	return (lex_loop(lexer));
}
