/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:36:46 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/26 11:15:00 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

const static t_type_func	g_type_funcs[] =
{
	{ TOKEN_NAME, &par_type_name },
	{ TOKEN_IO_FD, &par_type_io_fd },
	{ TOKEN_SEMI, &par_type_semic },
	{ TOKEN_AND, &par_type_conditions },
	{ TOKEN_OR, &par_type_conditions },
	{ TOKEN_REDIRI, &par_type_redir },
	{ TOKEN_REDIRO, &par_type_redir },
	{ TOKEN_PIPE, &par_type_conditions },
	{ TOKEN_AGGR, &par_type_redir },
	{ TOKEN_VAR, &par_type_name },
	{ TOKEN_ASSIGNMENT, NULL },
	{ TOKEN_NULL, NULL }
};

static t_type_func	get_func(t_token_type type)
{
	const t_type_func	null_state = { TOKEN_NULL, NULL };
	int					i;

	i = 0;
	while (g_type_funcs[i].key != TOKEN_NULL)
	{
		if (g_type_funcs[i].key == type)
			return (g_type_funcs[i]);
		i++;
	}
	return (null_state);
}

static int			parse_error(int err, t_token *tokens, int i)
{
	while (tokens->next && i)
	{
		tokens = tokens->next;
		i--;
	}
	if (err == 0)
		ft_dprintf(2, "42sh: syntax error near unexpected token: %s\n", \
			tokens->content);
	return (err);
}

int					parse(t_token *tokens)
{
	t_type_func	cur;
	t_parser	parser;
	int			ret;

	parser.i = 0;
	parser.can_var = 1;
	parser.tokens = tokens;
	while (parser.tokens)
	{
		if (parser.tokens->type == TOKEN_SEMI \
					|| parser.tokens->type == TOKEN_PIPE)
			parser.can_var = 1;
		cur = get_func(parser.tokens->type);
		if (cur.fnc)
		{
			if ((ret = cur.fnc(&parser)) < 1)
				return (parse_error(ret, tokens, parser.i));
		}
		else if (cur.key != TOKEN_NULL)
			par_next(&parser, 1);
		else
			return (parse_error(ret, tokens, parser.i));
	}
	return (1);
}
