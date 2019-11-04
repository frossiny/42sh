/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:26:08 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/04 14:23:05 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"
#include "tokens_list.h"
#include "utils.h"

static char			*get_closing(const char *open)
{
	if (ft_strequ(open, "${"))
		return ("}");
	if (ft_strequ(open, "$(("))
		return ("))");
	return (NULL);
}

static t_token_type	get_tok_type(const char *op)
{
	if (ft_strequ(op, "$") || ft_strequ(op, "${"))
		return (TOKEN_VAR);
	if (ft_strequ(op, "$(("))
		return (TOKEN_ARITHMETIC);
	return (TOKEN_NAME);
}

static int			update_state(t_lexer *lexer, t_state state, int ret)
{
	lex_update_state(lexer, state);
	return (ret);
}

int					lex_state_expansions(t_lexer *lexer)
{
	t_ex_token	cur;
	char		*match;
	char		*str;

	if (!(cur = g_exp_list[lex_get_expansion(lexer)]).op)
		return (update_state(lexer, ST_GENERAL, 1));
	lexer->in += cur.len;
	if ((match = get_closing(cur.op)) && !ft_strequ(cur.op, "$"))
	{
		if (!(str = ft_strstr(lexer->in, match)))
			return (-5);
		str += ft_strlen(match);
	}
	else if (ft_strequ(cur.op, "$"))
	{
		while (lexer->in[0] && !lexer_search(lexer->in).op)
			lexer->in++;
		str = lexer->in;
	}
	else
		return (update_state(lexer, ST_GENERAL, 1));
	lexer->in = str;
	return (update_state(lexer, ST_GENERAL, 1));
}
