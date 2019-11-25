/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 15:42:26 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/25 10:49:51 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"
#include "variables.h"
#include "expansion.h"
#include "utils.h"

static void	new_tok(t_expansion *exp)
{
	if (exp->i > exp->li)
		exp_join(exp, ft_strsub(exp->str, exp->li, exp->i - exp->li), 1);
	exp->li = exp->i;
}

static void	quote(t_expansion *exp)
{
	exp->isquote = !exp->isquote;
	exp->i++;
}

static int	exp_var_loop(t_expansion *exp)
{
	while (exp->str[exp->i])
	{
		if (exp->str[exp->i] == '\'')
			quote(exp);
		else if (exp->str[exp->i] == '$' && !exp->isquote
					&& !is_escaped(exp->str, exp->i, 0))
		{
			new_tok(exp);
			if (ft_strnequ(exp->str + exp->i, "${", 2))
			{
				if (!exp_parameter(exp))
					return (0);
			}
			else if (!ft_strnequ(exp->str + exp->i, "$((", 3))
				exp_simple_var(exp);
			else
				exp->i++;
			if (exp->i >= ft_strlen(exp->str))
				break ;
		}
		else
			exp->i++;
	}
	new_tok(exp);
	return (1);
}

int			exp_variables(t_token *token)
{
	t_expansion	exp;

	if (!token || !token->content)
		return (0);
	exp_set_struct(&exp, token->content);
	exp.i = 0;
	if (!exp_var_loop(&exp))
		return (0);
	tok_replace(token, exp.new ? exp.new : ft_strdup(""));
	return (1);
}
