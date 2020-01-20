/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:26:08 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/20 10:15:36 by frossiny         ###   ########.fr       */
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

static int			update_state(t_lexer *lexer, t_state state, int ret)
{
	lex_update_state(lexer, state);
	return (ret);
}

int					lex_state_expansions(t_lexer *lexer)
{
	t_ex_token	cur;
	char		*closing;

	if ((cur = g_exp_list[lex_get_expansion(lexer)]).op)
	{
		lex_new_exp(lexer, cur.op);
		lexer->in += cur.len;
	}
	else if (!cur.op && !lexer->exps)
		return (update_state(lexer, ST_GENERAL, 1));
	else
	{
		closing = get_closing(lexer->exps->op);
		if (ft_strnequ(lexer->in, closing, ft_strlen(closing)) \
			&& !is_escaped(lexer->pin, lexer->in - lexer->pin, 0))
		{
			lex_exp_del(lexer);
			lexer->in += ft_strlen(closing);
			if (lexer->exps == NULL)
				return (update_state(lexer, ST_GENERAL, 1));
		}
		else
			lexer->in++;
	}
	return (1);
}
