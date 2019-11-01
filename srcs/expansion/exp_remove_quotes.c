/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_remove_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 15:47:37 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/01 17:52:36 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"
#include "lexer.h"
#include "utils.h"

static void	fill_new(t_expansion *e, char *tmp)
{
	if (!tmp)
		return ;
	if (e->new)
	{
		if (e->isquote == 1)
			e->new = ft_strfjoin(e->new, tmp, e->new);
		else
			e->new = strjoin_escape(e->new, tmp);
	}
	else
	{
		if (e->isquote == 1)
			e->new = ft_strdup(tmp);
		else
			e->new = strdup_escape(tmp);
	}
	free(tmp);
}

static int	is_opening_quote(t_expansion *e)
{
	if (e->str[e->i] == '\'' && e->isquote == 0)
		return (1);
	if (e->str[e->i] == '"' && e->isquote == 0)
		return (1);
	return (0);
}

static int	is_closing_quote(t_expansion *e)
{
	if (e->str[e->i] == '\'' && e->isquote == 1)
		return (1);
	if (e->str[e->i] == '"' && e->isquote == 2)
		return (1);
	return (0);
}

int			exp_remove_quotes(t_expansion *e)
{
	while (e->str[++(e->i)])
	{
		if (is_opening_quote(e))
		{
			if (is_escaped(e->str, e->i, 0))
				continue ;
			fill_new(e, ft_strsub(e->str, e->li, e->i - e->li));
			e->li = e->i + 1;
			e->isquote = e->str[e->i] == '"' ? 2 : 1;
		}
		else if (is_closing_quote(e))
		{
			if (is_escaped(e->str, e->i, 0) && e->isquote != 1)
				continue ;
			fill_new(e, ft_strsub(e->str, e->li, e->i - e->li));
			e->li = e->i + 1;
			e->isquote = 0;
		}
	}
	if (e->i > e->li)
		fill_new(e, ft_strsub(e->str, e->li, e->i - e->li));
	return (1);
}
