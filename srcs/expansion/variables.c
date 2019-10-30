/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 13:16:59 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/30 18:43:24 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "expansion.h"
#include "lexer.h"
#include "utils.h"

static char	*handle_var(t_var *vars, char *var_name)
{
	char	*ret;
	t_var	*var;

	ret = NULL;
	var = var_get(vars, var_name);
	if (var_name[0] == '?')
		ret = ft_itoa(g_return);
	else if (!var)
		ret = NULL;
	else
		ret = ft_strdup(var->value);
	free(var_name);
	return (ret);
}

static void	fill_new(char **new, char *tmp, int esc)
{
	if (!tmp)
		return ;
	if (*new)
		*new = esc ? strjoin_escape(*new, tmp) : ft_strfjoin(*new, tmp, *new);
	else
		*new = esc ? strdup_escape(tmp) : ft_strdup(tmp);
	free(tmp);
}

static int	handle_quotes(char **new, t_expansion *e)
{
	if ((e->str[e->i] == '\'' && e->isquote == 0)
			|| (e->str[e->i] == '"' && e->isquote == 0))
	{
		if (is_escaped(e->str, e->i, 0))
			return (0);
		fill_new(new, ft_strndup(e->str + e->li, e->i - e->li), 1);
		e->li = e->i + 1;
		e->isquote = e->str[e->i] == '"' ? 2 : 1;
		return (1);
	}
	if ((e->str[e->i] == '\'' && e->isquote == 1)
			|| (e->str[e->i] == '"' && e->isquote == 2))
	{
		if (is_escaped(e->str, e->i, 0))
			return (0);
		fill_new(new, ft_strndup(e->str + e->li, e->i - e->li), 1);
		e->li = e->i + 1;
		e->isquote = 0;
		return (1);
	}
	return (0);
}

static void	parse_token(t_token *token, t_expansion *e, t_var *vars)
{
	char	*new;
	char	*tmp;

	new = NULL;
	while (e->str[++(e->i)])
	{
		if (handle_quotes(&new, e))
			continue ;
		if (!(e->str[e->i] == '$' && !is_escaped(e->str, e->i, 0))
					|| e->isquote == 1)
			continue ;
		if (e->isquote != 1
			&& (e->str[e->i + 1] == '\0' || e->str[e->i + 1] == '"'))
			continue ;
		fill_new(&new, ft_strndup(e->str + e->li, e->i - e->li), 1);
		tmp = handle_var(vars,
			ft_strndup(e->str + e->i + 1, get_var_size(e->str + e->i)));
		(tmp) ? fill_new(&new, tmp, 0) : 0;
		e->i += get_var_size(e->str + e->i);
		e->li = e->i + 1;
	}
	(e->i > e->li)
		? fill_new(&new, ft_strndup(e->str + e->li, e->i - e->li), 1)
		: 0;
	tok_replace(token, new);
}

int			replace_vars(t_token *token, t_var *vars)
{
	t_expansion	exp;
	int			esc;

	while (token && token->type == TOKEN_VAR)
	{
		esc = (token->content[0] == '\\');
		exp.i = -1;
		exp.li = 0;
		exp.isquote = 0;
		exp.str = token->content;
		parse_token(token, &exp, vars);
		if (!esc && token->content[0] == '~')
			if (!(handle_home(token, vars)))
				return (0);
		token = token->next;
	}
	return (1);
}
