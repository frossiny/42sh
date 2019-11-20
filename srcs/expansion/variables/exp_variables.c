/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 15:42:26 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/20 18:30:17 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"
#include "variables.h"
#include "expansion.h"
#include "utils.h"

static int	exp_var_loop(t_expansion *exp)
{
	while (exp->str[exp->i])
	{
		if (exp->str[exp->i] == '\'')
		{
			exp->isquote = !exp->isquote;
			exp->i++;
		}
		else if (exp->str[exp->i] == '$' && !exp->isquote && !is_escaped(exp->str, exp->i, 0))
		{
			if (exp->i > exp->li)
				exp_join(exp, ft_strsub(exp->str, exp->li, exp->i - exp->li), 1);
			exp->li = exp->i;
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
	if (exp->i > exp->li)
		exp_join(exp, ft_strsub(exp->str, exp->li, exp->i - exp->li), 1);
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
